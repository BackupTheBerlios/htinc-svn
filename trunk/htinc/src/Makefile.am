# Makefile template for the program

# program generated
bin_PROGRAMS = htinc
# all input files to htinc
htinc_SOURCES = auxfunc.h examine.h includes.h \
     examine.cpp includes.cpp main.cpp structs.h \
     globals.h globals.cpp \
     utils/cmdargs.h

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
