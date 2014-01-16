ARCH:=$(shell getconf LONG_BIT)

CC=g++
CPPFLAGS_=-mtune=native -Wall -g -std=c++0x -O3
CPPFLAGS_64=-m64
CPPFLAGS_32=-m32
CPPFLAGS=$(CPPFLAGS_) $(CPPFLAGS_$(ARCH))

SRCDIR=src
OBJDIR=obj
BINDIR=bin
TSTDIR=tests
TSBDIR=tests/bin
SOURCE_FILES=base.cpp boolean.cpp arithmetics.cpp mul.cpp div.cpp barrett.cpp modular.cpp
SOURCES=$(SOURCE_FILES:%=$(SRCDIR)/%)
OBJECTS=$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
COMPILATION_PREFIX=$(CC) $(CPPFLAGS) $(OBJECTS)
TEST_COMPILATION_SUFFIX=#-lboost_system -lboost_thread -lboost_unit_test_framework
MAIN_SRC=$(SRCDIR)/main.cpp
MAIN_OBJ=$(MAIN_SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TESTS=config bigint bigint_advanced time
TEST_SOURCES=$(TESTS:%=$(TSTDIR)/%.cpp)
TEST_OBJECTS=$(TESTS:%=$(OBJDIR)/test_%.o)
TEST_EXECUTABLES=$(TESTS:%=$(TSBDIR)/%)
TEST_RUNNERS=$(TESTS:%=test_%)
TEST_RUNNERS_DETAILED=$(TESTS:%=test_%_detailed)
TEST_RUNNERS_ERRORS=$(TESTS:%=test_%_errors)
TESTS_PARAMETERS=--log_level=all

all: $(OBJECTS) $(MAIN_OBJ)
	mkdir -p $(BINDIR)
	$(COMPILATION_PREFIX) $(MAIN_OBJ) -o $(BINDIR)/bigint

clean:
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)
	rm -rf $(TSBDIR)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(SRCDIR)/bigint.cpp: $(SRCDIR)/config.h
$(MAIN_SRC): $(SRCDIR)/bigint.cpp
$(MAIN_OBJ): $(MAIN_SRC)
	mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

arch:
	@echo $(ARCH)

available_tests:
	@echo $(TESTS)

$(TSTDIR)/bigint.cpp: $(SRCDIR)/bigint.cpp
$(TSTDIR)/modular.cpp: $(SRCDIR)/bigint.cpp
$(TSTDIR)/config.cpp: $(SRCDIR)/config.h

$(TEST_OBJECTS): $(OBJDIR)/test_%.o : $(TSTDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -c $< -o $@ $(TEST_COMPILATION_SUFFIX)

$(TEST_EXECUTABLES): $(TSBDIR)/% : $(OBJDIR)/test_%.o $(OBJECTS)
	mkdir -p $(TSBDIR)
	$(COMPILATION_PREFIX) $< -o $@ $(TEST_COMPILATION_SUFFIX)

$(TEST_RUNNERS): test_%: $(TSBDIR)/%
	$<

$(TEST_RUNNERS_ERRORS): test_%_errors: $(TSBDIR)/%
	$< --log_level=error

$(TEST_RUNNERS_DETAILED): test_%_detailed: $(TSBDIR)/%
	$< --log_level=all
