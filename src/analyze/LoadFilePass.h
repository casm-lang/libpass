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

#ifndef _LIB_PASS_LOADFILEPASS_H_
#define _LIB_PASS_LOADFILEPASS_H_

#include "libpass.h"

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class LoadFilePass final : public Pass
    {
      public:
        static char id;

        u1 run( libpass::PassResult& pr ) override;

        void setFilename( const std::string& filename );

        class Data : public PassData
        {
          public:
            using Ptr = std::shared_ptr< Data >;

            Data( const std::string& filename );

            const char* filename( void ) const;

            std::string str_filename( void ) const;

          private:
            std::string m_filename;
        };

      private:
        std::string m_filename;
    };
}

#endif // _LIB_PASS_LOADFILEPASS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
