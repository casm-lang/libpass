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

#include "gtest/gtest.h"

#include "libpass.h"

using namespace libpass;

TEST( libpass, loadfilepass )
{
    LoadFilePass p;
}

TEST( libpass, loadfilepass_run_and_log )
{
    PassResult r;

    LoadFilePass p;

    p.run( r );

#ifndef NDEBUG
    libstdhl::Log::StringFormatter f;
#else
    libstdhl::Log::ConsoleFormatter f;
#endif

    libstdhl::Log::OutputStreamSink c( std::cerr, f );
    p.stream().flush( c );
}
