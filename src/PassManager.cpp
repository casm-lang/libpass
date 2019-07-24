//
//  Copyright (C) 2015-2019 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                <https://github.com/casm-lang/libpass>
//
//  This file is part of libpass.
//
//  libpass is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libpass is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libpass. If not, see <http://www.gnu.org/licenses/>.
//
//  Additional permission under GNU GPL version 3 section 7
//
//  libpass is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libpass
//  statically or dynamically with other modules is making a combined work
//  based on libpass. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libpass give you permission to link libpass
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libpass. If you modify libpass, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "PassManager.h"

#include <libpass/PassLogger>

#include <libstdhl/data/log/Chronograph>

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace libpass;

char PassManager::id = 0;

static PassRegistration< PassManager > PASS(
    "PassManager", "calculates the pass pipeline dependency graph", "pm-calc", 0 );

PassManager::PassManager( void )
: m_defaultPass( nullptr )
, m_defaultResult()
{
}

const std::unordered_set< Pass::Id >& PassManager::passes( void ) const
{
    return m_passes;
}

void PassManager::add( Pass::Id id )
{
    auto result = m_passes.emplace( id );
    if( not result.second )
    {
        const auto pass = PassRegistry::passInfo( id );
        throw std::domain_error( "'" + pass.name() + "' already managed" );
    }
}

void PassManager::setDefaultResult( const PassResult& pr )
{
    m_defaultResult = pr;
}

const PassResult& PassManager::result( void ) const
{
    return m_result;
}

void PassManager::setDefaultPass( Pass::Id defaultPass )
{
    m_defaultPass = defaultPass;
}

void PassManager::process( const Pass::Id passId, const Pass::Id pathId )
{
    auto it = m_passUsages.emplace( passId, PassUsage() );
    auto& passUsage = it.first->second;
    if( it.second )
    {
        // only create pass to fetch the internal usage info and release it
        const auto pass = PassRegistry::passInfo( passId );
        pass.constructInternalPass()->usage( passUsage );
    }

    if( passUsage.repeatsUntil() )
    {
        process( passUsage.repeatsUntil(), passUsage.repeatsUntil() );
    }

    std::vector< Pass::Id > dependencies;
    std::set_union(
        passUsage.requires().begin(),
        passUsage.requires().end(),
        passUsage.schedulesAfter().begin(),
        passUsage.schedulesAfter().end(),
        std::back_inserter( dependencies ) );

    for( auto dependencyId : dependencies )
    {
        m_paths[ pathId ].emplace( dependencyId );
        process( dependencyId, pathId );
    }

    std::vector< Pass::Id > features;
    std::set_union(
        passUsage.provides().begin(),
        passUsage.provides().end(),
        passUsage.schedulesBefore().begin(),
        passUsage.schedulesBefore().end(),
        std::back_inserter( features ) );

    for( auto featureId : features )
    {
        m_paths[ featureId ].emplace( pathId );
        process( featureId, pathId );
    }
}

void PassManager::schedule( const Pass::Id passId )
{
    const auto& passUsage = m_passUsages[ passId ];

    for( auto scheduleAfterId : passUsage.schedulesAfter() )
    {
        m_passWeights[ scheduleAfterId ] +=
            m_passWeights[ passId ] + passUsage.schedulesAfter().size();
        schedule( scheduleAfterId );
    }

    for( auto requireId : passUsage.requires() )
    {
        m_passWeights[ requireId ] += m_passWeights[ passId ] + passUsage.requires().size();
        schedule( requireId );
    }
}

u1 PassManager::runPass( const Pass::Id passId, const std::function< void( void ) >& flush )
{
    PassLogger log( &id, stream() );
    libstdhl::Log::Chronograph swatch( true );
    const auto pass = PassRegistry::passInfo( passId );

    m_result.setStatus( passId, false );

    auto p = pass.constructPass();
    p->setStream( stream() );

    p->initialize();

    log.debug( "'" + pass.name() + "': running" );

    if( flush )
    {
        flush();
    }

    const u1 statusRun = p->run( m_result );

    log.debug( "'" + pass.name() + "': done (took: " + std::string( swatch ) + ")" );

    u1 statusVerify = false;

    if( statusRun )
    {
        statusVerify = p->verify();
    }

    p->finalize();

    if( not statusRun or not statusVerify )
    {
        if( flush )
        {
            flush();
        }

        return false;
    }

    m_result.setStatus( passId, true );

    return true;
}

u1 PassManager::run( const std::function< void( void ) >& flush )
{
    PassLogger log( &id, stream() );
    libstdhl::Log::Chronograph swatch( true );

    m_result = m_defaultResult;

    // determine the pass pipeline schedule
    const u1 statusScheduling = run( m_result );

    if( not statusScheduling )
    {
        return false;
    }

    auto start = m_schedule.cbegin();
    for( auto passIt = m_schedule.cbegin(); passIt != m_schedule.cend(); passIt++ )
    {
        const auto passId = std::get< 0 >( *passIt );
        const auto pass = PassRegistry::passInfo( passId );

        if( m_result.hasOutput( passId ) )
        {
            passIt++;
            start = passIt;
            log.debug( "'" + pass.name() + "': skipping, result already present!" );
            break;
        }
        else
        {
            log.debug( "'" + pass.name() + "': result not present!" );
        }
    }

    std::unordered_map< Pass::Id, Pass::Id > repeatUntil;
    for( auto passIt = start; passIt != m_schedule.cend(); passIt++ )
    {
        const auto passId = std::get< 0 >( *passIt );
        const auto pass = PassRegistry::passInfo( passId );

        if( not runPass( passId, flush ) )
        {
            return false;
        }

        auto it = repeatUntil.begin();
        while( it != repeatUntil.end() )
        {
            if( not runPass( it->first, flush ) )
            {
                return false;
            }

            if( it->second == passId )
            {
                repeatUntil.erase( it++ );
            }
            else
            {
                it++;
            }
        }

        const auto& passUsage = m_passUsages[ passId ];
        if( passUsage.repeatsUntil() )
        {
            repeatUntil.emplace( passId, passUsage.repeatsUntil() );
        }
    }

    log.debug( "running passes: done (took: " + std::string( swatch ) + ")" );

    if( flush )
    {
        flush();
    }

    return true;
}

u1 PassManager::run( PassResult& pr )
{
    PassLogger log( &id, stream() );
    libstdhl::Log::Chronograph swatch( true );

    // find all selected passes and calculate 'usage graph'
    for( auto pi : passes() )
    {
        const auto pass = PassRegistry::passInfo( pi );

        if( pass.isArgSelected() )
        {
            log.debug( pass.name() + ": selected" );

            auto result = m_selected.emplace( pi );
            if( not result.second )
            {
                throw std::domain_error(
                    "already processed '" + std::string( pass.argString() ) + "'" );
            }
        }

        process( pi, pi );
    }

    if( m_selected.size() == 0 )
    {
        if( m_defaultPass )
        {
            m_selected.emplace( m_defaultPass );
            process( m_defaultPass, m_defaultPass );
        }
        else
        {
            log.error( "no pass was selected" );
            return false;
        }
    }

    log.debug( "selection: done" );

    auto passId = *m_selected.begin();
    const auto passUsage = m_passUsages[ passId ];
    if( passUsage.repeatsUntil() )
    {
        m_passWeights.emplace( passId, 10 );
        passId = passUsage.repeatsUntil();
    }

    m_passWeights.emplace( passId, 0 );
    for( auto id : m_paths[ passId ] )
    {
        m_passWeights.emplace( id, 0 );
    }

    schedule( passId );

    for( auto it : m_passWeights )
    {
        const auto passId = it.first;
        const auto passWeight = it.second;
        m_schedule.emplace_back( std::make_tuple( passId, passWeight ) );
    }

    std::sort(
        m_schedule.begin(),
        m_schedule.end(),
        []( const std::tuple< Pass::Id, i64 >& a, const std::tuple< Pass::Id, i64 >& b ) {
            return std::get< 1 >( a ) > std::get< 1 >( b );
        } );

    for( auto element : m_schedule )
    {
        const auto passId = std::get< 0 >( element );
        const auto edgeWeight = std::get< 1 >( element );
        const auto pass = PassRegistry::passInfo( passId );
        log.debug( "%4i: %s", edgeWeight, pass.name().c_str() );
    }

    log.debug( "scheduling: done" );

    return true;
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
