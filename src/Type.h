//
//  Copyright (c) 2015-2016 Philipp Paulweber
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

#ifndef _LIB_PASS_TYPE_H_
#define _LIB_PASS_TYPE_H_

#include "cpp/Type.h"

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class Pass;
    class PassInfo;

    typedef Pass* ( *PassConstructor )();
    typedef void* PassId;
    typedef void* Ptr;

    typedef unordered_map< libpass::PassId, PassInfo* > PassId2PassInfo;
    typedef unordered_map< libpass::PassId, void* > PassId2Ptr;
    typedef unordered_map< libpass::PassId, u64 > PassId2u64;

    // class Type
    // {
    // public:

    // };
}

#endif /* _LIB_PASS_TYPE_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
