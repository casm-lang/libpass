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

#ifndef _LIB_PASS_PASS_LOGGER_H_
#define _LIB_PASS_PASS_LOGGER_H_

#include "PassInfo.h"

#include "../stdhl/cpp/Log.h"

/**
   @brief    TODO

   TODO
*/

namespace libpass
{
    class PassLogger
    {
      public:
        PassLogger( const PassInfo& passinfo, libstdhl::Log::Stream& stream );

        void error( const std::string& text );
        void error( const char* format, ... );

        void warning( const std::string& text );
        void warning( const char* format, ... );

        void info( const std::string& text );
        void info( const char* format, ... );

        void hint( const std::string& text );
        void hint( const char* format, ... );

        void debug( const std::string& text );
        void debug( const char* format, ... );

        void c_log(
            libstdhl::Log::Level::ID level, const char* format, va_list args );

        template < typename... Args >
        void log( Args&&... args )
        {
            m_stream.add( std::forward< Args >( args )... );
        }

        libstdhl::Log::Stream& stream( void )
        {
            return m_stream;
        }

      private:
        const PassInfo& m_passinfo;

        libstdhl::Log::Stream& m_stream;
    };
}

#endif // _LIB_PASS_PASS_LOGGER_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
