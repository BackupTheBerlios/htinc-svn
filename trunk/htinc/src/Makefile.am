# Makefile template for the program
#
# Copyright (C) 2005 Robert Lange <robert.lange@s1999.tu-chemnitz.de>
# last Modification: $LastChangedDate$

# program generated
bin_PROGRAMS = htinc
# all input files to htinc
htinc_SOURCES = auxfunc.h \
     examine.h examine.cpp main.cpp structs.h typedefs.h \
     globals.h globals.cpp \
     parseargs.h parseargs.cpp \
     linenum.h linenum.cpp \
     tagprocessor.h includes.h includes.cpp date.h date.cpp

# include debugging code if wanted (DEBUG comes from configure)
if DEBUG
     # Debugging code, no stripping, always pedantic warnings
     htinc_CXXFLAGS = -g -pedantic
else
     # no debug wanted
     # turn on optimisation, if wanted
if OPTIMIZE
if ARGP_O_PEDANTIC
     # also add -pedantic when it's working with -Ox parameters
     htinc_CXXFLAGS = -pedantic -O3
else
     # otherwise only Optimisation
     htinc_CXXFLAGS = -O3
endif
endif
     # additional flags to linker: strip
     htinc_LDFLAGS = -s
endif
