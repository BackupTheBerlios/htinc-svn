## Makefile for HTML Include
## Copyright (C) 2002 MadDog/Robert Lange

## possible Targets:
## all (default): build program
## debug: build program with Debug-Support
## opt: build program with optimization and strips it
##
## install: installs HTML Include
##	    Linux: ~/bin/	DJGPP: C:/dienst/ (see Makefile.def)
##
## clean: removes object files
## bakclean: removes also the Backup files
## ultraclean: removes also the result files

##  This program is free software; you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation; either version 2 of the License, or
##  (at your option) any later version.

##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.


include Makefile.def


## the implizit rule for building C++ Sources
%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(CXXINCLUDES) -c -o $@ $<


all : $(RESULTFILE)

## Debug-Target: append Debug parameters
debug : CXXFLAGS += -g -ggdb
debug : $(RESULTFILE)

## Optimize-Target: append Optimize und Strip parameter 
opt : CXXFLAGS += -O2
opt : LDFLAGS += -s
opt : $(RESULTFILE)

$(RESULTFILE) : main.o examine.o includes.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS) $(LDFILTER)

main.o : main.cpp main.h examine.h			  ## use implizit rule
examine.o : examine.cpp examine.h includes.h auxfunc.h	  ## use implizit rule
includes.o : includes.cpp includes.h examine.h	auxfunc.h ## use implizit rule


.PHONY : INSTALL
install :
	$(CP) $(RESULTFILE) $(INSTALLDIR) 

.PHONY : CLEAN
clean : 
	$(RM) *.o

.PHONY : BAKCLEAN
bakclean : clean
	$(RM) *.bak
	$(RM) *~

.PHONE : ULTRACLEAN
ultraclean : bakclean
	$(RM) $(RESULTFILE)
