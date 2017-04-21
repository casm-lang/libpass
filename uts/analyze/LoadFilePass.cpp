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

#include "uts/main.h"

using namespace libpass;

TEST( libpass_analyze_LoadFilePass, instance )
{
    LoadFilePass p;
}

TEST( libpass_analyze_LoadFilePass, run_and_log )
{
    std::string filename = TEST_NAME + ".txt";

    PassResult r;

    LoadFilePass p;
    p.setFilename( filename );

    EXPECT_EQ( libstdhl::File::exists( filename ), false );

    EXPECT_EQ( p.run( r ), false );

    EXPECT_EQ( libstdhl::File::exists( filename ), false );

    libstdhl::Log::StringFormatter f;
    libstdhl::Log::OutputStreamSink c( std::cerr, f );
    p.stream().flush( c );
}

TEST( libpass_analyze_LoadFilePass, writable_run_log )
{
    std::string filename = TEST_NAME + ".txt";

    PassResult r;

    LoadFilePass p;
    p.setFilename( filename );
    p.setWritable( true );

    EXPECT_EQ( libstdhl::File::exists( filename ), false );

    EXPECT_EQ( p.run( r ), false );

    EXPECT_EQ( libstdhl::File::exists( filename ), false );

    libstdhl::Log::StringFormatter f;
    libstdhl::Log::OutputStreamSink c( std::cerr, f );
    p.stream().flush( c );
}

TEST( libpass_analyze_LoadFilePass, writable_overwrite_run_log )
{
    std::string filename = TEST_NAME + ".txt";

    PassResult r;

    LoadFilePass p;
    p.setFilename( filename );
    p.setWritable( true );
    p.setOverwrite( true );

    EXPECT_EQ( libstdhl::File::exists( filename ), false );

    EXPECT_EQ( p.run( r ), true );

    EXPECT_EQ( libstdhl::File::exists( filename ), true );
    libstdhl::File::remove( filename );
    EXPECT_EQ( libstdhl::File::exists( filename ), false );

    libstdhl::Log::StringFormatter f;
    libstdhl::Log::OutputStreamSink c( std::cerr, f );
    p.stream().flush( c );
}
