//
//  Copyright (C) 2015-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libpass/graphs/contributors>
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

#include "PassResult.h"

#include <libpass/PassRegistry>

using namespace libpass;

PassResult::PassResult( void )
: m_statuses()
, m_changes()
, m_inputs()
, m_outputs()
, m_previousPass( nullptr )
{
}

u1 PassResult::hasStatus( const Pass::Id id ) const
{
    return m_statuses.find( id ) != m_statuses.cend();
}

void PassResult::setStatus( Pass::Id id, u1 status )
{
    m_statuses[ id ] = status;

    if( status )
    {
        m_previousPass = id;
    }
}

const std::unordered_map< Pass::Id, u1 >& PassResult::statuses( void ) const
{
    return m_statuses;
}

u1 PassResult::hasChange( const Pass::Id id ) const
{
    return m_changes.find( id ) != m_changes.cend();
}

const std::unordered_map< Pass::Id, u64 >& PassResult::changes( void ) const
{
    return m_changes;
}

u1 PassResult::hasInput( const Pass::Id id ) const
{
    return m_inputs.find( id ) != m_inputs.cend();
}

const std::unordered_map< Pass::Id, PassData::Ptr >& PassResult::inputs( void ) const
{
    return m_inputs;
}

u1 PassResult::hasOutput( const Pass::Id id ) const
{
    return m_outputs.find( id ) != m_outputs.cend();
}

const std::unordered_map< Pass::Id, PassData::Ptr >& PassResult::outputs( void ) const
{
    return m_outputs;
}

u1 PassResult::hasPreviousPass( void ) const
{
    return m_previousPass != nullptr;
}

Pass::Id PassResult::previousPass( void ) const
{
    if( not hasPreviousPass() )
    {
        throw std::domain_error( "no previous pass has used this pass result" );
    }

    return m_previousPass;
}

//

u1 PassResult::status( const Pass::Id id )
{
    const auto it = m_statuses.find( id );
    if( it == m_statuses.cend() )
    {
        throw std::domain_error(
            "no pass result 'state' for '" + PassRegistry::passInfo( id ).name() + "' found" );
    }
    return it->second;
}

u64 PassResult::change( const Pass::Id id )
{
    const auto it = m_changes.find( id );
    if( it == m_changes.cend() )
    {
        throw std::domain_error(
            "no pass result 'change' for '" + PassRegistry::passInfo( id ).name() + "' found" );
    }
    return it->second;
}

void PassResult::setChange( Pass::Id id, u64 passChanges )
{
    m_changes[ id ] = passChanges;
}

PassData::Ptr PassResult::input( const Pass::Id id ) const
{
    const auto it = m_inputs.find( id );
    if( it == m_inputs.cend() )
    {
        throw std::domain_error(
            "no pass result 'input' for '" + PassRegistry::passInfo( id ).name() + "' found" );
    }
    return it->second;
}

void PassResult::setInput( const Pass::Id id, const PassData::Ptr& data )
{
    m_inputs[ id ] = data;
}

PassData::Ptr PassResult::output( const Pass::Id id ) const
{
    const auto it = m_outputs.find( id );
    if( it == m_outputs.cend() )
    {
        throw std::domain_error(
            "no pass result 'output' for '" + PassRegistry::passInfo( id ).name() + "' found" );
    }
    return it->second;
}

void PassResult::setOutput( const Pass::Id id, const PassData::Ptr& data )
{
    m_outputs[ id ] = data;
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
