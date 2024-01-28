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

#include "../main.h"

using namespace libpass;

TEST( libpass_analyze_LoadFilePass, instance )
{
    LoadFilePass p;
}

TEST( libpass_analyze_LoadFilePass, run_and_log )
{
    std::string filename = TEST_NAME + ".txt";

    PassResult r;
    r.setInput< LoadFilePass >( filename );

    LoadFilePass p;

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

    const auto input = libstdhl::Memory::make< LoadFilePass::Input >( filename );
    input->setWritable( true );

    PassResult r;
    r.setInputData< LoadFilePass >( input );

    LoadFilePass p;

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

    const auto input = libstdhl::Memory::make< LoadFilePass::Input >( filename );
    input->setWritable( true );
    input->setOverwrite( true );

    LoadFilePass p;
    PassResult r;
    r.setInputData< LoadFilePass >( input );

    EXPECT_EQ( r.hasInput< LoadFilePass >(), true );
    EXPECT_EQ( r.hasOutput< LoadFilePass >(), false );
    EXPECT_EQ( libstdhl::File::exists( filename ), false );

    EXPECT_EQ( p.run( r ), true );

    EXPECT_EQ( r.hasInput< LoadFilePass >(), true );
    EXPECT_EQ( r.hasOutput< LoadFilePass >(), true );
    EXPECT_EQ( libstdhl::File::exists( filename ), true );

    r.output< LoadFilePass >()->close();
    libstdhl::File::remove( filename );
    EXPECT_EQ( libstdhl::File::exists( filename ), false );

    libstdhl::Log::StringFormatter f;
    libstdhl::Log::OutputStreamSink c( std::cerr, f );
    p.stream().flush( c );
}
