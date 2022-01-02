#
#   Copyright (C) 2015-2022 CASM Organization <https://casm-lang.org>
#   All rights reserved.
#
#   Developed by: Philipp Paulweber et al.
#                 <https://github.com/casm-lang/libpass/graphs/contributors>
#
#   This file is part of libpass.
#
#   libpass is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   libpass is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with libpass. If not, see <http://www.gnu.org/licenses/>.
#
#   Additional permission under GNU GPL version 3 section 7
#
#   libpass is distributed under the terms of the GNU General Public License
#   with the following clarification and special exception: Linking libpass
#   statically or dynamically with other modules is making a combined work
#   based on libpass. Thus, the terms and conditions of the GNU General
#   Public License cover the whole combination. As a special exception,
#   the copyright holders of libpass give you permission to link libpass
#   with independent modules to produce an executable, regardless of the
#   license terms of these independent modules, and to copy and distribute
#   the resulting executable under terms of your choice, provided that you
#   also meet, for each linked independent module, the terms and conditions
#   of the license of that module. An independent module is a module which
#   is not derived from or based on libpass. If you modify libpass, you
#   may extend this exception to your version of the library, but you are
#   not obliged to do so. If you do not wish to do so, delete this exception
#   statement from your version.
#

# LIBPASS_FOUND        - system has found the package
# LIBPASS_INCLUDE_DIR  - the package include directory
# LIBPASS_LIBRARY      - the package shared library
# LIBPASS_ARCHIVE      - the package static library

include( LibPackage )

libfind_pkg_check_modules( LIBPASS_PKGCONF libpass )

find_path( LIBPASS_INCLUDE_DIR
  NAMES libpass/libpass.h
  PATHS ${LIBPASS_PKGCONF_INCLUDE_DIRS}
  )

find_library( LIBPASS_LIBRARY
  NAMES libpass.so libpass.dylib libpass.dll
  PATHS ${LIBPASS_PKGCONF_LIBRARY_DIRS}
  )

find_library( LIBPASS_ARCHIVE
  NAMES libpass.a
  PATHS ${LIBPASS_PKGCONF_LIBRARY_DIRS}
  )

set( LIBPASS_PROCESS_INCLUDES LIBPASS_INCLUDE_DIR )
set( LIBPASS_PROCESS_LIBS     LIBPASS_LIBRARY LIBPASS_ARCHIVE )

libfind_process( LIBPASS )

if( EXISTS "${LIBPASS_LIBRARY}" AND ${LIBPASS_LIBRARY} AND
    EXISTS "${LIBPASS_ARCHIVE}" AND ${LIBPASS_ARCHIVE} )
  set( LIBPASS_FOUND TRUE PARENT_SCOPE )
else()
  set( LIBPASS_FOUND FALSE PARENT_SCOPE )
endif()
