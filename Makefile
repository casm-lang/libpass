#   
#   Copyright (c) 2015-2016 Philipp Paulweber
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


CC=clang
CCFLAG += -std=c11
CCFLAG += -g
CCFLAG += -Wall

CPP=clang
CPPFLAG += -std=c++11
CPPFLAG += -g
CPPFLAG += -Wall
#CPPFLAG += -Wextra

#TARGET
INCLUDE += -I ./
INCLUDE += -I ../

default: obj # $(TARGET)

obj:
	mkdir -p obj

clean:
	@echo "RM  " obj
	@rm -rf obj
#	@echo "RM  " $(TARGET)
#	@rm -f $(TARGET)
	@rm -f test


TEST_FILES   = $(shell find uts -name '*.cpp' | cut -d'.' -f1)
TEST_OBJECTS = $(TEST_FILES:%=obj/%.o)

TEST_INCLUDE  = -I ../gtest/googletest/include
TEST_INCLUDE += -I ../gtest/googletest

TEST_LIBRARY  = -lstdc++
TEST_LIBRARY += -lm
TEST_LIBRARY += -lpthread

obj/uts/%.o: uts/%.cpp
	@mkdir -p `dirname $@`
	@echo "CPP " $<
	@$(CPP) $(CPPFLAG) $(TEST_INCLUDE) $(INCLUDE) -c $< -o $@

test: default obj $(TEST_OBJECTS)
	@rm -f $@
	@echo "LD  " $@
	@$(CPP) $(CPPFLAG) $(TEST_INCLUDE) $(INCLUDE) $(TEST_LIBRARY) -o $@ $(filter %.o,$^) ../gtest/googletest/src/gtest-all.cc ../gtest/googletest/src/gtest_main.cc
#	@$(CPP) $(CPPFLAG) $(TEST_INCLUDE) $(INCLUDE) $(TEST_LIBRARY) -o $@ $(filter %.o,$^) $(TARGET) ../gtest/googletest/src/gtest-all.cc ../gtest/googletest/src/gtest_main.cc
	@echo "RUN " $@
	@./$@
