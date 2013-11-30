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
TEST_COMPILATION_PREFIX=$(CC) $(CPPFLAGS) $(OBJECTS)
TEST_COMPILATION_SUFFIX=-lboost_system -lboost_thread -lboost_unit_test_framework
MAIN_SRC=$(SRCDIR)/main.cpp
MAIN_OBJ=$(MAIN_SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

objects:
	echo $(OBJECTS)

all: $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) $(CPPFLAGS) $(OBJECTS) $(MAIN_OBJ) -o $(BINDIR)/bigint

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
