/* Name: ''linenum.cpp''
  Project: HTML Include
 Copyright (C) 2005 MadDog/Robert Lange

 Created: 21.04.2k5
 last Modification: $LastChangedDate$
 Function: Translates stream position to line number in the file
            Because the file at work is stored charcter-by-characters,
	    line numbers cannot be determined explicitely. This class
	    records the positions of the newline characters and can thus
	    determine the line number of any position.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/


// Includes

#include "config.h"  // Settings from configure
//#include "globals.h" // Message-Level et al
#include "linenum.h"

// *** add newline at this position ***
void linenum::add(const int pos) {
     // Argument 1: Position

  // now, only placeholder for the 'real' functionality

}



// *** remove range (e.g. for changing file content) ***
void linenum::remove(const int start, const int end) {
     // Argument 1: Start-Position (including)
     // Argument 2: End-Position (not included)


  // now, only placeholder for the 'real' functionality
}


// *** translates position to line number ***
int linenum::operator() (const int pos) const {
     // Argument 1: Position

  // now, only placeholder for the 'real' functionality

  return 0; // Dummy
}


// *** return number of lines ***
int linenum::linecount () const {

  return 0;  // Dummy
}
