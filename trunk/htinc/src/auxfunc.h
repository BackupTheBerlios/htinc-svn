/* Name: ''auxfunc.h''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

 Created: 13.10.2k2
 last Modification: $LastChangedDate$
 Function: auxiliary template functions
           copyfile - copies a file into an container

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/


// *** Copy stream to list ***
// Character by Character
template<class LIST>
bool copyfile(std::ifstream &fs, LIST & list, class linenum *line = NULL) {
  // Argument 1: File stream to read from
  // Argument 2: List to copy into
  // Argument 3: Line Number Object to record the positions of
  //             newlines, if it is not NULL

  list.clear();    // clear the list
  //  fs.clear();       // clear filestream error bits
  fs.seekg(0);      // go to the beginning

  // local variable
  char tchar;

  // copy

  for(;;) {
    fs.get(tchar);
    if ( fs.eof() )   {     // stream ended
	return true;        // no error
    }   // else
    if ( fs.bad() ) {
      return false;        // Reading went wrong
    }
    if ( (line!=NULL) && (tchar == '\n') ) {     // record endline position
      line->add(list.size() );
    }
    list.push_back(tchar);  // add char
  } 

}
