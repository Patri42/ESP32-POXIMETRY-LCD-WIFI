# Pointers to the root and main directories
ROOT_DIR = ..
MAIN_DIR = $(ROOT_DIR)/main

# Source files to be tested
SRC_FILES = $(MAIN_DIR)/thingspeak-manager.c 

# Test files
TEST_FILES = thingspeak-manager_test.cpp

# Google Test source
GTEST_DIR = googletest/googletest
GTEST_LIB = $(GTEST_DIR)

# Flags passed to the C++ compiler.
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C compiler
CFLAGS +=

# All tests produced by this Makefile.
TESTS = run_tests

# House-keeping build targets.
all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o

# Builds gtest.a.
gtest-all.o : $(GTEST_LIB)/src/gtest-all.cc
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -c $^ -o $@

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

# Builds the main test.
run_tests : $(SRC_FILES) $(TEST_FILES) gtest.a
	$(CXX) $(CPPFLAGS) $(CFLAGS) -L. -lgtest -lpthread $^ -o $@

test: all
	./run_tests