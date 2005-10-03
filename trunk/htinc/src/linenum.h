/* Name: ''linenum.h''
  Project: HTML Include
 Copyright (C) 2005 MadDog/Robert Lange

 Created: 21.04.2k5
 last Modification: $LastChangedDate$
 Function: Declaration of Line-Number Object
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

// Header-Guard
#ifndef LINENUM__H
#define LINENUM__H

#include "typedefs.h"    // type definitions

#include <list>  // single linked list


class linenum {
private:

  // *** Typedefs
  // the line number container
  // TODO: slist sufficient?
  typedef std::list<unsigned int> lnums_type_;
  


  // *** Variables
  // List of line numbers
  // Every index denotes a new line, the content
  // is the offset to the previous lines in characters
  // (including the newline in every line)
  lnums_type_ lines_;


public:

  explicit linenum() {};   // C'tor

  // The position count in the stream starts with Zero.
  // The linenum object reflects the line number in the
  // source file, before modifications.
  // This should be noted in usage of the insert and
  // remove members.

  // initialise object with character stream
  void init(const structures::filelist_type &in);

  // remove range (e.g. for changing file content)
  void remove(const int, const int);
     // Argument 1: Start-Position (including)
     // Argument 2: number of characters removed

  // insert range (e.g. for changing file content)
  void insert(const int, const int);
     // Argument 1: Start-Position (including)
     // Argument 2: number of characters inserted

  // translates position to line number (starting from 1)
  int operator() (const int) const;
     // Argument 1: Position, starting from zero

  // return number of lines
  //  int linecount () const;


};          // class


#endif
