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

#include "LoadFilePass.h"

#include "../stdhl/cpp/Default.h"
#include "../stdhl/cpp/File.h"
#include "../stdhl/cpp/Log.h"

using namespace libpass;

char LoadFilePass::id = 0;

static PassRegistration< LoadFilePass > PASS( "Load File Pass",
    "checks if a file name exists and opens a file stream", 0, 0 );

u1 LoadFilePass::run( libpass::PassResult& pr )
{
    PassLogger log( &id, stream() );

    if( not libstdhl::File::exists( m_filename ) )
    {
        log.error( "file '%s' does not exist!", m_filename.c_str() );
        return false;
    }

    pr.setResult< LoadFilePass >( libstdhl::make< Data >( m_filename ) );

    return true;
}

void LoadFilePass::setFilename( const std::string& filename )
{
    m_filename = filename;
}

LoadFilePass::Data::Data( const std::string& filename )
: m_filename( filename )
{
}

const char* LoadFilePass::Data::filename( void ) const
{
    return m_filename.c_str();
}

std::string LoadFilePass::Data::str_filename( void ) const
{
    return m_filename;
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
