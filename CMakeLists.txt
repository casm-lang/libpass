#
#   Copyright (C) 2015-2024 CASM Organization <https://casm-lang.org>
#   All rights reserved.
#
#   Developed by: Philipp Paulweber et al.
#   <https://github.com/casm-lang/libpass/graphs/contributors>
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

set( PROJECT libpass )

cmake_minimum_required( VERSION ${CMAKE_VERSION} )

project( ${PROJECT} LANGUAGES CXX )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_VERSION 3.2 )
set( CMAKE_MODULE_PATH ${${PROJECT}_SOURCE_DIR}/.cmake )
include( ${CMAKE_CONFIG_PATH}/LibPackage.cmake )

package_git( ${PROJECT} )
package_git_submodule( libstdhl master REQUIRED obj   ../stdhl lib/stdhl )
package_git_submodule( libgtest master REQUIRED build ../gtest lib/gtest )
package_git_submodule( libhayai master REQUIRED build ../hayai lib/hayai )
package_git_deps()

find_package( Threads REQUIRED )

include( ECMGenerateHeaders )
include( FeatureSummary )
include( GenerateExportHeader )
include( CPack )

add_subdirectory( src )
add_subdirectory( etc
  EXCLUDE_FROM_ALL
  )

#
#
# library
#

set( ${PROJECT}_VERSION ${GIT_REVTAG} )
set_property( TARGET ${PROJECT}-cpp PROPERTY POSITION_INDEPENDENT_CODE 1 )

add_library( ${PROJECT} SHARED
  $<TARGET_OBJECTS:${PROJECT}-cpp>
  )

set_property( TARGET ${PROJECT} PROPERTY OUTPUT_NAME ${PROJECT} )
set_property( TARGET ${PROJECT} PROPERTY VERSION ${${PROJECT}_VERSION} )
set_property( TARGET ${PROJECT} PROPERTY PREFIX  "" )

if( ${LIBSTDHL_FOUND} )
  target_link_libraries( ${PROJECT}
    ${LIBSTDHL_LIBRARY}
    )
endif()

add_library( ${PROJECT}-ar STATIC
  $<TARGET_OBJECTS:${PROJECT}-cpp>
  )

set_property( TARGET ${PROJECT}-ar PROPERTY OUTPUT_NAME ${PROJECT} )
set_property( TARGET ${PROJECT}-ar PROPERTY VERSION ${${PROJECT}_VERSION} )
set_property( TARGET ${PROJECT}-ar PROPERTY PREFIX  "" )

if( ${LIBSTDHL_FOUND} )
  target_link_libraries( ${PROJECT}-ar
    ${LIBSTDHL_ARCHIVE}
    )
endif()

add_dependencies( ${PROJECT}
  ${PROJECT}-ar
  )

#
#
# test
# 

add_executable( ${PROJECT}-check
  EXCLUDE_FROM_ALL
  $<TARGET_OBJECTS:${PROJECT}-test>
  )

if( ${LIBGTEST_FOUND} )
  target_link_libraries( ${PROJECT}-check
    ${PROJECT}-ar
    ${LIBGTEST_LIBRARY}
    ${LIBGTEST_MAIN}
    Threads::Threads
    )
endif()

#
#
# benchmark
#

add_executable( ${PROJECT}-run
  EXCLUDE_FROM_ALL
  $<TARGET_OBJECTS:${PROJECT}-benchmark>
  )

if( ${LIBHAYAI_FOUND} )
  target_link_libraries( ${PROJECT}-run
    ${PROJECT}-ar
    ${LIBHAYAI_LIBRARY}
    )
endif()

#
#
# install
#

install(
  TARGETS  ${PROJECT} ${PROJECT}-ar
  EXPORT   ${PROJECT}Targets
  LIBRARY  DESTINATION lib
  ARCHIVE  DESTINATION lib
  RUNTIME  DESTINATION bin
  INCLUDES DESTINATION include
  )

generate_export_header(
  ${PROJECT}
  )

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}_export.h"
  DESTINATION
    "include/${PROJECT}"
  )

export(
  TARGETS
    ${PROJECT}
  FILE
    ${PROJECT}Config.cmake
  )

#
#
# cmake
#

install(
  FILES
    .cmake/Find${PROJECT}.cmake
  DESTINATION
    "share/cmake/Module/${PROJECT}"
  )

#
#
# build features and checks
#

include( LibCompile )
compile_flags( CXX )
compile_check()

feature_summary( WHAT
  PACKAGES_NOT_FOUND
  DISABLED_FEATURES
  )
