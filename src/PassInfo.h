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

#ifndef _LIBPASS_PASSINFO_H_
#define _LIBPASS_PASSINFO_H_

#include <libpass/Pass>

#include <cassert>
#include <unordered_map>

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class PassInfo
    {
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
        PassInfo( const Pass::Id passID, const std::string& passName,
            const std::string& passDescription,
            Pass::Constructor passConstructor,
            Pass::Constructor passInternalCtor, const char* passArgStr,
            const char passArgChar,
            std::function< i32( const char* ) > passArgAction )
        : m_id( passID )
        , m_name( passName )
        , m_description( passDescription )
        , m_constructor( passConstructor )
        , m_internal_ctor( passInternalCtor )
        , m_arg_str( passArgStr )
        , m_arg_char( passArgChar )
        , m_arg_action( passArgAction )
        , m_arg_selected( false )
        , m_changes( 0 )
        {
        }

        PassInfo( const Pass::Id passID, const std::string& passName,
            const std::string& passDescription,
            Pass::Constructor passConstructor,
            Pass::Constructor passInternalCtor, const char* passArgStr,
            const char passArgChar )
        : m_id( passID )
        , m_name( passName )
        , m_description( passDescription )
        , m_constructor( passConstructor )
        , m_internal_ctor( passInternalCtor )
        , m_arg_str( passArgStr )
        , m_arg_char( passArgChar )
        , m_arg_selected( false )
        , m_changes( 0 )
        {
            m_arg_action = [this]( const char* arg ) {
                this->m_arg_selected = true;
                return 0;
            };
        }

        const Pass::Id id( void ) const
        {
            return m_id;
        }

        std::string name( void ) const
        {
            return m_name;
        }

        std::string description( void ) const
        {
            return m_description;
        }

        const char* argString( void ) const
        {
            return m_arg_str;
        }

        const char argChar( void ) const
        {
            return m_arg_char;
        }

        const std::function< i32( const char* ) >& argAction( void ) const
        {
            return m_arg_action;
        }

        const u1 isArgSelected( void ) const
        {
            return m_arg_selected;
        }

        u1 isPassId( const Pass::Id passID ) const
        {
            return m_id == passID;
        }

        void addChanges( u64 change )
        {
            m_changes += change;
        }

        u64 changes( void )
        {
            return m_changes;
        }

        auto constructPass( void ) const -> decltype( m_constructor() )
        {
            auto p = m_constructor();
            assert( p and "unable to create pass" );
            return p;
        }

        auto constructInternalPass( void ) const
            -> decltype( m_internal_ctor() )
        {
            auto p = m_internal_ctor();
            assert( p and "unable to create pass" );
            return p;
        }

        friend std::ostream& operator<<( std::ostream& os, PassInfo& pi )
        {
            return os; // << pi.getPassName() << ": ";
        }
    };
}

#endif // _LIBPASS_PASSINFO_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
