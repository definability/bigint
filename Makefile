ARCH:=$(shell getconf LONG_BIT)

CC=g++
CPPFLAGS_=-mtune=native# -Wall
CPPFLAGS_64=-m64
CPPFLAGS_32=-m32
CPPFLAGS=$(CPPFLAGS_) $(CPPFLAGS_$(ARCH))

SRCDIR=src
OBJDIR=obj
BINDIR=bin
TSTDIR=tests
SOURCE_FILES=base.cpp boolean.cpp arithmetics.cpp mul.cpp div.cpp modular.cpp
SOURCES=$(SOURCE_FILES:%=$(SRCDIR)/%)
OBJECTS=$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
COMPILATION_PREFIX=$(CC) $(CPPFLAGS) $(OBJECTS)
TEST_COMPILATION_SUFFIX=-lboost_system -lboost_thread -lboost_unit_test_framework
MAIN_SRC=$(SRCDIR)/main.cpp
MAIN_OBJ=$(MAIN_SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TESTS=config
TESTS_PARAMETERS=--log_level=all

objects:
	echo $(OBJECTS)

all: $(OBJECTS)
	mkdir -p $(BINDIR)
	$(COMPILATION_PREFIX) $(MAIN_OBJ) -o $(BINDIR)/bigint

clean:
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(MAIN_SRC): $(SRCDIR)/bigint.cpp

arch:
	echo $(ARCH)
flags:
	echo $(CPPFLAGS)


test_config: $(OBJECTS) $(TSTDIR)/config.cpp
	$(COMPILATION_PREFIX) $(TSTDIR)/config.cpp -o $(TSTDIR)/config $(TEST_COMPILATION_SUFFIX)
	$(TSTDIR)/config $(TESTS_PARAMETERS)

$(TSTDIR)/bigint.cpp: $(SRCDIR)/bigint.cpp

test_bigint: $(OBJECTS)
	$(COMPILATION_PREFIX) $(TSTDIR)/bigint.cpp -o $(TSTDIR)/bigint $(TEST_COMPILATION_SUFFIX)
	$(TSTDIR)/bigint $(TESTS_PARAMETERS)


test_bigint_errors: $(OBJECTS)
	$(COMPILATION_PREFIX) $(TSTDIR)/bigint.cpp -o $(TSTDIR)/bigint $(TEST_COMPILATION_SUFFIX)
	$(TSTDIR)/bigint --log_level=error