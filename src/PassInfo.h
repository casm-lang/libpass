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

#ifndef _LIBPASS_PASS_INFO_H_
#define _LIBPASS_PASS_INFO_H_

#include <libpass/Pass>

#include <cassert>
#include <functional>
#include <unordered_map>

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class PassInfo
    {
      public:
        PassInfo(
            const Pass::Id passID,
            const std::string& passName,
            const std::string& passDescription,
            Pass::Constructor passConstructor,
            Pass::Constructor passInternalCtor,
            const char* passArgStr,
            const char passArgChar,
            std::function< i32( const char* ) > passArgAction );

        PassInfo(
            const Pass::Id passID,
            const std::string& passName,
            const std::string& passDescription,
            Pass::Constructor passConstructor,
            Pass::Constructor passInternalCtor,
            const char* passArgStr,
            const char passArgChar );

        const Pass::Id id( void ) const;

        std::string name( void ) const;

        std::string description( void ) const;

        const char* argString( void ) const;

        const char argChar( void ) const;

        const std::function< i32( const char* ) >& argAction( void ) const;

        const u1 isArgSelected( void ) const;

        u1 isPassId( const Pass::Id passID ) const;

        void addChanges( u64 change );

        u64 changes( void );

      private:
        const Pass::Id m_id;
        const std::string m_name;
        const std::string m_description;
        Pass::Constructor m_constructor;
        Pass::Constructor m_internal_ctor;

        const char* const m_arg_str;
        const char m_arg_char;
        std::function< i32( const char* ) > m_arg_action;
        u1 m_arg_selected;

        u64 m_changes;

      public:
        auto constructPass( void ) const -> decltype( m_constructor() )
        {
            auto p = m_constructor();
            assert( p and "unable to create pass" );
            return p;
        }

        auto constructInternalPass( void ) const -> decltype( m_internal_ctor() )
        {
            auto p = m_internal_ctor();
            assert( p and "unable to create pass" );
            return p;
        }
    };
}

#endif  // _LIBPASS_PASS_INFO_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
