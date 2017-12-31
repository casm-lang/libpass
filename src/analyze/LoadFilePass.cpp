//
//  Copyright (c) 2015-2017 CASM Organization https://casm-lang.org
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                https://github.com/casm-lang/libpass
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

#include "LoadFilePass.h"

#include <libpass/PassInfo>
#include <libpass/PassLogger>
#include <libpass/PassRegistry>

#include <libstdhl/File>
#include <libstdhl/Log>
#include <libstdhl/Memory>

using namespace libpass;

char LoadFilePass::id = 0;

static PassRegistration< LoadFilePass > PASS(
    "LoadFilePass", "checks if a file name exists and opens a file stream", 0, 0 );

u1 LoadFilePass::run( libpass::PassResult& pr )
{
    PassLogger log( &id, stream() );

    if( not pr.hasInput< LoadFilePass >() )
    {
        log.error( "cannot found input data" );
        return false;
    }

    try
    {
        const auto input = pr.input< LoadFilePass >();
        pr.setOutput< LoadFilePass >( input->filename(), input->mode() );
    }
    catch( const std::exception& e )
    {
        log.error( e.what() );
        return false;
    }

    return true;
}

//
//
// LoadFilePass::Input
//

LoadFilePass::Input::Input( const std::string& filename, const std::ios::openmode mode )
: m_filename( filename )
, m_mode( mode )
{
}

std::string LoadFilePass::Input::filename( void ) const
{
    return m_filename;
}

const std::ios::openmode LoadFilePass::Input::mode( void ) const
{
    return m_mode;
}

void LoadFilePass::Input::setWritable( const u1 enable )
{
    if( enable )
    {
        m_mode |= std::ios::out;
    }
    else
    {
        m_mode &= ~std::ios::out;
    }
}
u1 LoadFilePass::Input::isWritable( void ) const
{
    return m_mode & std::ios::out;
}

void LoadFilePass::Input::setOverwrite( const u1 enable )
{
    if( enable )
    {
        m_mode |= std::ios::trunc;
    }
    else
    {
        m_mode &= ~std::ios::trunc;
    }
}
u1 LoadFilePass::Input::isOverwrite( void ) const
{
    return m_mode & std::ios::trunc;
}

void LoadFilePass::Input::setAppend( const u1 enable )
{
    if( enable )
    {
        m_mode |= std::ios::app;
    }
    else
    {
        m_mode &= ~std::ios::app;
    }
}
u1 LoadFilePass::Input::isAppend( void ) const
{
    return m_mode & std::ios::app;
}

void LoadFilePass::Input::setBinary( const u1 enable )
{
    if( enable )
    {
        m_mode |= std::ios::binary;
    }
    else
    {
        m_mode &= ~std::ios::binary;
    }
}
u1 LoadFilePass::Input::isBinary( void ) const
{
    return m_mode & std::ios::binary;
}

//
//
// LoadFilePass::Output
//

LoadFilePass::Output::Output( const std::string& filename, const std::ios::openmode mode )
: Input( filename, mode )
, m_fstream( libstdhl::File::open( filename, mode ) )
, m_stream( m_fstream.rdbuf() )
{
}

LoadFilePass::Output::Output( const libstdhl::File::TextDocument& file )
: Input( file.path().toString(), std::ios::in )
, m_fstream()
, m_stream( file.buffer() )
{
}

std::iostream& LoadFilePass::Output::stream( void )
{
    m_stream.seekg( 0 );
    return m_stream;
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
