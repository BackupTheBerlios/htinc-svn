# Makefile template for the program

# program generated
bin_PROGRAMS = htinc
# all input files to htinc
htinc_SOURCES = auxfunc.h examine.h includes.h main.h \
     examine.cpp includes.cpp main.cpp structs.h \
     utils/cmdargs.h

# include debugging code if wanted (DEBUG comes from configure)
if DEBUG
     # Debugging code, no stripping
     htinc_CXXFLAGS = -g
else
     # no debug wanted
     # turn on optimisation
     htinc_CXXFLAGS = -O2
     # additional flags to linker: strip
     htinc_LDFLAGS = -s
endif
