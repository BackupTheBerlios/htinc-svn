# Makefile template for the program

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
     # Debugging code, no stripping
     htinc_CXXFLAGS = -g
else
     # no debug wanted
     # turn on optimisation, if wanted
if OPTIMIZE
        htinc_CXXFLAGS = -O2
endif
     # additional flags to linker: strip
     htinc_LDFLAGS = -s
endif
