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

#ifndef _LIB_PASS_PASS_H_
#define _LIB_PASS_PASS_H_

#include "../stdhl/cpp/Type.h"

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class PassUsage;
    class PassResult;

    class Pass
    {
      public:
        using Id = void*;
        using Ptr = void*;

        typedef std::shared_ptr< Pass > ( *Constructor )();

        virtual ~Pass() = default;

        virtual void usage( PassUsage& pu )
        {
        }

        virtual void initialize( void )
        {
        }

        virtual u1 run( PassResult& pr ) = 0;

        virtual u1 verify( void )
        {
            return true;
        }

        virtual void finalize( void )
        {
        }

        virtual void dealloc( void* result )
        {
        }
    };
}

#endif /* _LIB_PASS_PASS_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
