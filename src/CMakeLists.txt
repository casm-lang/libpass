#
#   Copyright (c) 2015-2017 Philipp Paulweber
#   All rights reserved.
#
#   Developed by: Philipp Paulweber
#                 https://github.com/ppaulweber/libpass
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

include_directories(
  ${LIBSTDHL_INCLUDE_DIR}
  )


add_library( ${PROJECT}-cpp OBJECT
  PassLogger.cpp
  PassManager.cpp
  PassUsage.cpp
  analyze/LoadFilePass.cpp
  )


configure_file(
  Version.in.h
  ${PROJECT}/Version
)


ecm_generate_headers( ${PROJECT}_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    Pass
    PassData
    PassInfo
    PassLogger
    PassManager
    PassRegistry
    PassResult
    PassUsage
    libpass
  PREFIX
    ${PROJECT}
  REQUIRED_HEADERS
    ${PROJECT}_HEADERS
  )
install(
  FILES
    ${${PROJECT}_HEADERS}
    ${${PROJECT}_HEADERS_CPP}
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}/Version
  DESTINATION
    "include/${PROJECT}"
  )


ecm_generate_headers( ${PROJECT}_ANALYZE_HEADERS_CPP
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    LoadFilePass
  PREFIX
    ${PROJECT}/analyze
  RELATIVE
    analyze
  REQUIRED_HEADERS
    ${PROJECT}_ANALYZE_HEADERS
)
install(
  FILES
    ${${PROJECT}_ANALYZE_HEADERS}
    ${${PROJECT}_ANALYZE_HEADERS_CPP}
  DESTINATION
    "include/${PROJECT}/analyze"
)
