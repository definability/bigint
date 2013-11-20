ARCH:=$(shell getconf LONG_BIT)

CC=g++
CPPFLAGS_=-mtune=native# -Wall
CPPFLAGS_64=-m64
CPPFLAGS_32=-m32
CPPFLAGS=$(CPPFLAGS_) $(CPPFLAGS_$(ARCH))

SOURCES=base.cpp boolean.cpp arithmetics.cpp mul.cpp div.cpp modular.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o bigint

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

main.cpp: bigint.cpp

arch:
	echo $(ARCH)
flags:
	echo $(CPPFLAGS)
