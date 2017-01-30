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

#ifndef _LIB_PASS_PASSRESULT_H_
#define _LIB_PASS_PASSRESULT_H_

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class PassResult
    {
      private:
        std::unordered_map< Pass::Id, Pass::Ptr > m_results;

        std::unordered_map< Pass::Id, u64 > m_changes;

      public:
        PassResult()
        {
        }

        ~PassResult()
        {
            m_results.clear();
            m_changes.clear();
        }

        template < class PassName >
        void* result( void )
        {
            return result( &PassName::id );
        }

        void* result( Pass::Id id )
        {
            return m_results[ id ];
        }

        template < class PassName >
        void setResult( void* passResult )
        {
            m_results[&PassName::id ] = passResult;
        }

        std::unordered_map< Pass::Id, Pass::Ptr >& results( void )
        {
            return m_results;
        }

        void printAllResults( void )
        {
        }

        template < class PassName >
        u64 change( void )
        {
            return change( &PassName::id );
        }

        u64 change( Pass::Id id )
        {
            return m_changes[ id ];
        }

        template < class PassName >
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
            return os;
        }
    };
}

#endif /* _LIB_PASS_PASSRESULT_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
