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

#include "PassUsage.h"

using namespace libpass;

PassUsage::PassUsage( void )
: m_terminate( false )
, m_requires()
, m_provides()
, m_schedulesBefore()
, m_schedulesAfter()
, m_repeatUntil( nullptr )
{
}

u1 PassUsage::terminate( void ) const
{
    return m_terminate;
}

void PassUsage::setTerminate( u1 terminate )
{
    m_terminate = terminate;
}

PassUsage::Set PassUsage::requires( void ) const
{
    return m_requires;
}

PassUsage::Set PassUsage::provides( void ) const
{
    return m_provides;
}

PassUsage::Set PassUsage::schedulesAfter( void ) const
{
    return m_schedulesAfter;
}

PassUsage::Set PassUsage::schedulesBefore( void ) const
{
    return m_schedulesBefore;
}

Pass::Id PassUsage::repeatsUntil( void ) const
{
    return m_repeatUntil;
}

void PassUsage::require( Pass::Id id )
{
    m_requires.insert( id );
}

void PassUsage::provide( Pass::Id id )
{
    m_provides.insert( id );
}

void PassUsage::scheduleAfter( Pass::Id id )
{
    m_schedulesAfter.insert( id );
}

void PassUsage::scheduleBefore( Pass::Id id )
{
    m_schedulesBefore.insert( id );
}

void PassUsage::repeatUntil( Pass::Id id )
{
    m_repeatUntil = id;
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
