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

#include "PassLogger.h"

using namespace libpass;
using namespace libstdhl;

PassLogger::PassLogger(
    const PassInfo& passinfo, libstdhl::Log::Stream& stream )
: m_passinfo( passinfo )
, m_stream( stream )
{
}

void PassLogger::error( const char* format, ... )
{
    va_list args;
    va_start( args, format );
    c_log( Log::Level::ERROR, format, args );
    va_end( args );
}

void PassLogger::error( const std::string& text )
{
    log( Log::Level::ERROR, text );
}

void PassLogger::warning( const std::string& text )
{
    log( Log::Level::WARNING, text );
}

void PassLogger::warning( const char* format, ... )
{
    va_list args;
    va_start( args, format );
    c_log( Log::Level::WARNING, format, args );
    va_end( args );
}

void PassLogger::info( const std::string& text )
{
    log( Log::Level::INFORMATIONAL, text );
}

void PassLogger::info( const char* format, ... )
{
    va_list args;
    va_start( args, format );
    c_log( Log::Level::INFORMATIONAL, format, args );
    va_end( args );
}

void PassLogger::hint( const std::string& text )
{
    log( Log::Level::NOTICE, text );
}

void PassLogger::hint( const char* format, ... )
{
    va_list args;
    va_start( args, format );
    c_log( Log::Level::NOTICE, format, args );
    va_end( args );
}

void PassLogger::debug( const std::string& text )
{
    log( Log::Level::DEBUG, text );
}

void PassLogger::debug( const char* format, ... )
{
    va_list args;
    va_start( args, format );
    c_log( Log::Level::DEBUG, format, args );
    va_end( args );
}

void PassLogger::c_log( Log::Level::ID level, const char* format, va_list args )
{
    char buffer[ 4096 ];
    vsprintf( buffer, format, args );
    log( level, std::string( buffer ) );
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
