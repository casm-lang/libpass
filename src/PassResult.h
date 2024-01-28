//
//  Copyright (C) 2015-2024 CASM Organization <https://casm-lang.org>
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

#ifndef _LIBPASS_PASS_RESULT_H_
#define _LIBPASS_PASS_RESULT_H_

#include <libpass/PassData>

#include <libstdhl/Memory>

#include <unordered_map>

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class PassResult
    {
      public:
        using Ptr = std::shared_ptr< PassResult >;

        PassResult( void );

        ~PassResult( void ) = default;

        template < typename PassName >
        inline u1 status( void )
        {
            return status( &PassName::id );
        }

        template < typename PassName >
        inline u1 hasStatus( void ) const
        {
            return hasStatus( &PassName::id );
        }

        u1 hasStatus( const Pass::Id id ) const;

        template < typename PassName >
        inline void setStatus( u1 status )
        {
            setStatus( &PassName::id, status );
        }

        void setStatus( Pass::Id id, u1 status );

        const std::unordered_map< Pass::Id, u1 >& statuses( void ) const;

        template < typename PassName >
        inline u64 change( void )
        {
            return change( &PassName::id );
        }

        template < typename PassName >
        inline u1 hasChange( void ) const
        {
            return hasChange( &PassName::id );
        }

        u1 hasChange( const Pass::Id id ) const;

        template < typename PassName >
        inline void setChange( u64 passChanges )
        {
            setChange( &PassName::id, passChanges );
        }

        const std::unordered_map< Pass::Id, u64 >& changes( void ) const;

        template < typename PassName >
        typename PassName::Input::Ptr input( void ) const
        {
            return std::static_pointer_cast< typename PassName::Input >( input( &PassName::id ) );
        }

        template < typename PassName >
        inline u1 hasInput( void ) const
        {
            return hasInput( &PassName::id );
        }

        u1 hasInput( const Pass::Id id ) const;

        template < typename PassName, typename... Args >
        inline void setInput( Args&&... args )
        {
            const auto data = libstdhl::Memory::make< typename PassName::Input >(
                std::forward< Args >( args )... );
            setInputData< PassName >( data );
        }

        template < typename PassName >
        inline void setInputData( const typename PassName::Input::Ptr& data )
        {
            setInput( &PassName::id, data );
        }

        const std::unordered_map< Pass::Id, PassData::Ptr >& inputs( void ) const;

        template < typename PassName >
        typename PassName::Output::Ptr output( void ) const
        {
            return std::static_pointer_cast< typename PassName::Output >( output( &PassName::id ) );
        }

        template < typename PassName >
        inline u1 hasOutput( void ) const
        {
            return hasOutput( &PassName::id );
        }

        u1 hasOutput( const Pass::Id id ) const;

        template < typename PassName, typename... Args >
        inline void setOutput( Args&&... args )
        {
            const auto data = libstdhl::Memory::make< typename PassName::Output >(
                std::forward< Args >( args )... );
            setOutputData< PassName >( data );
        }

        template < typename PassName >
        inline void setOutputData( const typename PassName::Output::Ptr& data )
        {
            setOutput( &PassName::id, data );
        }

        const std::unordered_map< Pass::Id, PassData::Ptr >& outputs( void ) const;

        u1 hasPreviousPass( void ) const;

        Pass::Id previousPass( void ) const;

      private:
        u1 status( const Pass::Id id );

        u64 change( const Pass::Id id );
        void setChange( Pass::Id id, u64 passChanges );

        PassData::Ptr input( const Pass::Id id ) const;
        void setInput( const Pass::Id id, const PassData::Ptr& data );

        PassData::Ptr output( const Pass::Id id ) const;
        void setOutput( const Pass::Id id, const PassData::Ptr& data );

        std::unordered_map< Pass::Id, u1 > m_statuses;
        std::unordered_map< Pass::Id, u64 > m_changes;
        std::unordered_map< Pass::Id, PassData::Ptr > m_inputs;
        std::unordered_map< Pass::Id, PassData::Ptr > m_outputs;
        Pass::Id m_previousPass;
    };
}

#endif  // _LIBPASS_PASS_RESULT_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
