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

#ifndef _LIBPASS_PASS_REGISTRY_H_
#define _LIBPASS_PASS_REGISTRY_H_

#include <libpass/PassInfo>

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class PassRegistry
    {
      public:
        PassRegistry( void );

        static void registerPass( PassInfo* passInfo );

        static std::unordered_map< Pass::Id, PassInfo* >& registeredPasses( void );

        template < typename T >
        static PassInfo& passInfo( void )
        {
            return passInfo( &T::id );
        }

        static PassInfo& passInfo( Pass::Id id );

        template < typename T >
        static std::function< void( T& ) >& passSetup(
            const std::function< void( T& ) >& action = nullptr )
        {
            static std::function< void( T& ) > cache = []( T& ) {};

            if( action )
            {
                cache = action;
            }

            return cache;
        }

      private:
        static std::unordered_map< Pass::Id, PassInfo* >& m_registeredPasses( void )
        {
            static std::unordered_map< Pass::Id, PassInfo* > cache;
            return cache;
        }
    };

    template < typename T >
    std::shared_ptr< Pass > defaultConstructor()
    {
        auto pass = std::make_shared< T >();
        PassRegistry::passSetup< T >()( *pass );
        return pass;
    }

    template < typename T >
    std::shared_ptr< Pass > internalConstructor()
    {
        return std::make_shared< T >();
    }

    template < typename T >
    class PassRegistration : public PassInfo
    {
      public:
        PassRegistration(
            const char* passName,
            const char* passDescription,
            const char* passArgStr,
            const char passArgChar )
        : PassInfo(
              &T::id,
              passName,
              passDescription,
              Pass::Constructor( defaultConstructor< T > ),
              Pass::Constructor( internalConstructor< T > ),
              passArgStr,
              passArgChar )
        {
            PassRegistry::registerPass( this );
        }
    };
}

#endif  // _LIBPASS_PASS_REGISTRY_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
