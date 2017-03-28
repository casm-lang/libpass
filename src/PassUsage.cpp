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

#include "PassUsage.h"

using namespace libpass;

PassUsage::PassUsage( void )
: m_terminate( false )
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

void PassUsage::require( Pass::Id id )
{
    m_requires.insert( id );
}

PassUsage::Set PassUsage::requires( void ) const
{
    return m_requires;
}

void PassUsage::provide( Pass::Id id )
{
    m_provides.insert( id );
}

PassUsage::Set PassUsage::provides( void ) const
{
    return m_provides;
}

void PassUsage::scheduleBefore( Pass::Id id )
{
    m_schedulesBefore.insert( id );
}

PassUsage::Set PassUsage::schedulesBefore( void ) const
{
    return m_schedulesBefore;
}

void PassUsage::scheduleAfter( Pass::Id id )
{
    m_schedulesAfter.insert( id );
}

PassUsage::Set PassUsage::schedulesAfter( void ) const
{
    return m_schedulesAfter;
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
