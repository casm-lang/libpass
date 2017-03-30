//
//  Copyright (c) 2015-2017 Philipp Paulweber
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libpass
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

#ifndef _LIB_PASS_PASS_MANAGER_H_
#define _LIB_PASS_PASS_MANAGER_H_

#include "PassRegistry.h"
#include "PassUsage.h"

#include "../stdhl/cpp/log/Chronograph.h"

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
        void add( std::function< void( T& ) > action = nullptr )
        {
            if( action )
            {
                PassRegistry::passSetup< T >( action );
            }

            add( PassRegistry::passInfo< T >().id() );
        }

        template < typename T >
        void setDefaultPass( void )
        {
            setDefaultPass( PassRegistry::passInfo< T >().id() );
        }

      private:
        void add( Pass::Id info );

        void setDefaultPass( Pass::Id defaultPass );

      public:
        void run( std::function< void( void ) > flush = nullptr );

      private:
        std::unordered_set< Pass::Id > m_managed;
        std::unordered_set< Pass::Id > m_selected;
        std::unordered_set< Pass::Id > m_start_points;
        std::unordered_map< Pass::Id, PassUsage > m_usages;
        std::unordered_map< Pass::Id, std::unordered_set< Pass::Id > >
            m_provides;
        Pass::Id m_default_pass;

        u1 run( PassResult& pr ) override;
    };
}

#endif // _LIB_PASS_PASS_MANAGER_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
