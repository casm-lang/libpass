//
//  Copyright (C) 2015-2023 CASM Organization <https://casm-lang.org>
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

#ifndef _LIBPASS_LOAD_FILE_PASS_H_
#define _LIBPASS_LOAD_FILE_PASS_H_

#include <libpass/Pass>
#include <libpass/PassData>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/data/file/TextDocument>

#include <ios>
#include <sstream>
#include <streambuf>

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

        class Input : public PassData
        {
          public:
            using Ptr = std::shared_ptr< Input >;

            Input( const std::string& filename, const std::ios::openmode mode = std::ios::in );

            std::string filename( void ) const;

            const std::ios::openmode mode( void ) const;

            void setWritable( const u1 enable );
            u1 isWritable( void ) const;

            void setOverwrite( const u1 enable );
            u1 isOverwrite( void ) const;

            void setAppend( const u1 enable );
            u1 isAppend( void ) const;

            void setBinary( const u1 enable );
            u1 isBinary( void ) const;

          private:
            std::string m_filename;
            std::ios::openmode m_mode;
        };

        class Output : public Input
        {
          public:
            using Ptr = std::shared_ptr< Output >;

            Output( const std::string& filename, const std::ios::openmode mode = std::ios::in );

            Output( const libstdhl::File::TextDocument& file );

            std::iostream& stream( void );

            void close( void );

          private:
            std::fstream m_fstream;
            std::iostream m_stream;
            u1 m_internal;
        };
    };
}

#endif  // _LIBPASS_LOAD_FILE_PASS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
