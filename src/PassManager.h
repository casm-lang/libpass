//
//  Copyright (C) 2015-2023 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libpass/graphs/contributors>
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

#ifndef _LIBPASS_PASS_MANAGER_H_
#define _LIBPASS_PASS_MANAGER_H_

#include <libpass/Pass>
#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <unordered_map>
#include <unordered_set>

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class PassManager : public Pass
    {
      public:
        static char id;

        PassManager( void );

        template < typename T >
        void add( void )
        {
            add( PassRegistry::passInfo< T >().id() );
        }

        template < typename T >
        void set( std::function< void( T& ) > action )
        {
            PassRegistry::passSetup< T >( action );
        }

        const std::unordered_set< Pass::Id >& passes( void ) const;

        template < typename T >
        void setDefaultPass( void )
        {
            setDefaultPass( PassRegistry::passInfo< T >().id() );
        }

        void setDefaultResult( const PassResult& pr );

        const PassResult& result( void ) const;

        u1 run( const std::function< void( void ) >& flush = nullptr );

      private:
        void add( Pass::Id info );

        void setDefaultPass( Pass::Id defaultPass );

        void process( const Pass::Id passSelectionId, const Pass::Id passDependecyId );

        void schedule( const Pass::Id passId );

        u1 runPass( const Pass::Id passId, const std::function< void( void ) >& flush );

        u1 run( PassResult& pr ) override;

        Pass::Id m_defaultPass;
        PassResult m_defaultResult;
        PassResult m_result;

        std::unordered_set< Pass::Id > m_passes;
        std::unordered_set< Pass::Id > m_selected;
        std::unordered_map< Pass::Id, std::unordered_set< Pass::Id > > m_paths;
        std::unordered_map< Pass::Id, PassUsage > m_passUsages;
        std::unordered_map< Pass::Id, i64 > m_passWeights;
        std::vector< std::tuple< Pass::Id, i64 > > m_schedule;
    };
}

#endif  // _LIBPASS_PASS_MANAGER_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
