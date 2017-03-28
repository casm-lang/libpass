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

#ifndef _LIB_PASS_PASSREGISTRY_H_
#define _LIB_PASS_PASSREGISTRY_H_

#include "PassInfo.h"

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class PassRegistry
    {
      private:
        static std::unordered_map< Pass::Id, PassInfo* >& m_registeredPasses(
            void )
        {
            static std::unordered_map< Pass::Id, PassInfo* > cache;
            return cache;
        }

      public:
        PassRegistry()
        {
            assert(
                0 && "PassRegistry class is a static-only non-object class!" );
        }

        static void registerPass( PassInfo* passInfo )
        {
            assert( passInfo != 0 && "invalid pass info object pointer" );
            assert
            ( passInfo and
              "invalid pass info object, "
              "tried to registered null pointer pass info!"
            );

            registeredPasses()[ passInfo->id() ] = passInfo;

            // TODO: add checks for redundant argument names etc.
        }

        static std::unordered_map< Pass::Id, PassInfo* >& registeredPasses(
            void )
        {
            return m_registeredPasses();
        }

        static PassInfo& passInfo( Pass::Id id )
        {
            PassInfo* pi = static_cast< PassInfo* >( registeredPasses()[ id ] );

            assert
            ( pi and
              "invalid pass info object, "
              "tried to access an unregistered pass!"
            );

            return *pi;
        }

        template < typename PassName >
        static PassInfo& passInfo( void )
        {
            return passInfo( &PassName::id );
        }
    };

    template < typename PassName >
    std::shared_ptr< Pass > defaultConstructor()
    {
        return std::make_shared< PassName >();
    }

    template < typename PassName >
    class PassRegistration : public PassInfo
    {
      public:
        PassRegistration( const char* passName, const char* passDescription,
            const char* passArgStr, const char passArgChar )
        : PassInfo( &PassName::id, passName, passDescription,
              Pass::Constructor( defaultConstructor< PassName > ), passArgStr,
              passArgChar )
        {
            PassRegistry::registerPass( this );
        }
    };
}

#endif // _LIB_PASS_PASSREGISTRY_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
