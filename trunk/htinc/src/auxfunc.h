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
template<class LIST>
bool copyfile(std::ifstream &fs, LIST & list) {  // Copy a file into the list
  // Argument: File stream to read from

  list.clear();    // clear the list
  //  fs.clear();       // clear filestream error bits
  fs.seekg(0);      // go to the beginning

  // local variable
  std::string tmp;  // storage buffer
  char tchar;

  // copy

  for(;;) {
    tmp.clear();      // clear storage string
    for(;;) {
      fs.get(tchar);
      if ( fs.eof() || tchar == '\n')
	break;       // stream ended or newline detected
      // else
      tmp.push_back(tchar);  // add char to string
    } 
    
    if ( fs.bad() )
      return false;        // Reading went wrong
    // else
    if (fs.eof()) {   // end reached
      if (!(tmp.empty()) ) {
	list.push_back(tmp);   // insert last tmp into list
      }
      return true;  // no error
    } // else
    list.push_back(tmp);   // insert tmp into list
  }
}
