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

#ifndef _LIBPASS_PASSRESULT_H_
#define _LIBPASS_PASSRESULT_H_

#include <libpass/PassData>

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

        PassResult( void )
        {
        }

        ~PassResult( void )
        {
            m_results.clear();
            m_changes.clear();
        }

        template < typename PassName >
        typename PassName::Data::Ptr result( void ) const
        {
            return std::static_pointer_cast< typename PassName::Data >(
                result( &PassName::id ) );
        }

        PassData::Ptr result( const Pass::Id id ) const
        {
            const auto it = m_results.find( id );
            return ( it != m_results.cend() ) ? it->second : nullptr;
        }

        template < typename PassName >
        void setResult( const typename PassName::Data::Ptr& result )
        {
            m_results[&PassName::id ] = result;
        }

        const std::unordered_map< Pass::Id, PassData::Ptr >& results(
            void ) const
        {
            return m_results;
        }

        void printAllResults( void )
        {
            // TODO
        }

        template < typename PassName >
        u64 change( void )
        {
            return change( &PassName::id );
        }

        u64 change( const Pass::Id id )
        {
            return m_changes[ id ];
        }

        template < typename PassName >
        void setChange( u64 passChanges )
        {
            setChange( &PassName::id, passChanges );
        }

        void setChange( Pass::Id id, u64 passChanges )
        {
            m_changes[ id ] = passChanges;
        }

        friend std::ostream& operator<<( std::ostream& os, PassResult& pr )
        {
            // TODO
            return os;
        }

      private:
        std::unordered_map< Pass::Id, PassData::Ptr > m_results;

        std::unordered_map< Pass::Id, u64 > m_changes;
    };
}

#endif // _LIBPASS_PASSRESULT_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
