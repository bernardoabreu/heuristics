# We’ll use gcc for C compilation and g++ for C++ compilation

CXX = g++

# Let’s leave a place holder for additional include directories

INCLUDES =

# Compilation options:
# -g for debugging info and -Wall enables all warnings

CXXFLAGS = -g -Wall --std=c++11 $(INCLUDES)

# Linking options:
# -g for debugging info

LDFLAGS = -g

# List the libraries you need to link with in LDLIBS
# For example, use "-lm" for the math library

LDLIBS =

MAIN = tsp

OBJS = main.o io_util.o util.o

# The 1st target gets built when you type "make".
# It’s usually your executable.  ("main" in this case.)
#
# Note that we did not specify the linking rule.
#
# Instead, we rely on one of make’s implicit rules:
#
#     $(CC) $(LDFLAGS) <all-dependent-.o-files> $(LDLIBS)
#
# Also note that make assumes that main depends on main.o,
# so we can omit it if we want to.

default: $(MAIN)
	@echo  Done.


$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS)	-o $(MAIN) $(OBJS) $(LDFLAGS) $(LDLIBS)


# make uses the following implicit rule to compile a .c file into a .o
# file:
#
#     $(CC) -c $(CFLAGS) <the-.c-file>
#

main.o: main.cpp io_util.h

io_util.o: io_util.cpp io_util.h util.h

util.o: util.h

# Always provide the "clean" target that removes intermediate files.
# What you remove depend on your choice of coding tools
# (different editors generate different backup files for example).
#
# And the "clean" target is not a file name, so we tell make that
# it’s a "phony" target.

.PHONY: clean
clean:
	rm -f *.o a.out core $(MAIN)

# "all" target is useful if your Makefile builds multiple programs.
# Here we’ll have it first do "clean", and rebuild the main target.

.PHONY: all
all: clean $(MAIN)