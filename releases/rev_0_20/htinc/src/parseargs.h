/*
file name: ''parseargs.h''
  project: HTML Include
 Copyright (C) 2005,2006 Robert Lange <robert.lange@s1999.tu-chemnitz.de>

 Created: 26.03.2k5 (from project CNSIM)
 last Modification: $LastChangedDate$
 Function: Command Line Argument Parser

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/


#ifndef PARSEARGS__H
#define PARSEARGS__H

#include <string>
#include <vector>

namespace parseargs {

// *** Argument-Structure (Klasse)
// pass parameters to main, also used by  parse_opt - function
struct arguments
{
  // constructor (clears everything)
  arguments() : debug(false),quiet(false) {};
  // typedef: File(s) to Process
  typedef std::vector<std::string> file_type;

  // variables
  bool debug;
  bool quiet;
  // values
  file_type file;                // file(s), mantadory
  std::string incdir;            // include directory
};



// *** functions
//  parse command line, exits on error
// argc, argv: command line (from main)
// pargs: parsed arguments
  void getcommandline(const int & argc, char *argv[], arguments & pargs);

} // namespace

#endif
