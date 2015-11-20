#
# [The "BSD license"]
# Copyright (c) 2012-2015 Rainer Mueller
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

#
# pearl runtime system tests

# overwiew of liste:
# targets - list of test application to build
# GTEST_SRC        - list of module to be added to the google testframe 
#                    for data type tests
# GTEST_DATION_SRC - list of module to be added to the google testframe 
#                    for dation tests
# TEST_SRCS        - list of modules for standalone tests

targets +=  \
	tests/DataTypeTests \
	tests/log_test tests/api  tests/lot_of_tasks  \
	tests/susp_cont_test \
	tests/sched_demo \
	tests/interruptTest \
	tests/SampleBasicDationTests \
	tests/sematest tests/sematerminate  \
	tests/signalTest\
	tests/DationTests \
	tests/DationSuspendTerminateTests 
	

GTEST_SRCS = tests/gtest_main.cc 
GTEST_DATION_SRCS = tests/gtest_main.cc 

TEST_SRCS +=  tests/log_test.cc 

GTEST_SRCS += tests/PrioTests.cc
GTEST_SRCS += tests/PrioMapperTests.cc


GTEST_DATION_SRCS += tests/gtest_main.cc tests/myTests.cc  \
  tests/DiscTests.cc tests/PipeTests.cc \
  tests/UserDationNBTests.cc\
  tests/StdStreamTests.cc \
  tests/DationRWTests.cc tests/DationPGTests.cc

ifeq ($(CONFIG_LINUX_Octopus),y)
  GTEST_DATION_SRCS += OctopusDigitalOutTest.cc
  GTEST_DATION_SRCS += OctopusDigitalInOutTest.cc
endif

# ----------------------------------------
# include test application code from the common stuff
include ../common/tests/Files
TEST_SRCS += $(addprefix ../common/tests/,$(CXX_COMMON_TESTS))

# ----------------------------------------
GTEST_OBJS =$(GTEST_SRCS:.cc=.o)

GTEST_DATION_OBJS =$(GTEST_DATION_SRCS:.cc=.o)

# ----------------------------------------
# define rules to build the targets
#  due to problems von implicit rules, the link command is 
#  given as explicit rule

tests/signalTest: tests/signalTest.o plib.a
	$(LINK)

tests/interruptTest: ../common/tests/interruptTest.o plib.a
	$(LINK)

tests/SampleBasicDationTests: ../common/tests/SampleBasicDationTests.o plib.a
	$(LINK)

tests/api: tests/api.o plib.a
	$(LINK)

tests/sched_demo: ../common/tests/sched_demo.o \
	../common/tests/round_robin_test.o plib.a
	$(LINK)

tests/susp_cont_test: ../common/tests/susp_cont_test.o plib.a
	$(LINK)

tests/lot_of_tasks: tests/lot_of_tasks.o plib.a
	$(LINK)

tests/DataTypeTests: $(GTEST_OBJS) plib.a /usr/local/lib/libgtest.a
	$(LINK)

tests/DationTests: $(GTEST_DATION_OBJS) plib.a /usr/local/lib/libgtest.a
	$(LINK)

tests/log_test: tests/log_test.o plib.a
	$(LINK)

tests/sematest: ../common/tests/sematest.o plib.a
	$(LINK)

tests/sematerminate: ../common/tests/sematerminate.o plib.a
	$(LINK)

tests/DationSuspendTerminateTests: tests/DationSuspendTerminateTests.o plib.a
	$(LINK)