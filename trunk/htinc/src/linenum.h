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


class linenum {
private:

  // now, only placeholder for the 'real' functionality

public:

  explicit linenum() {};   // C'tor

  // The position count in the stream starts with Zero

  // clear content and start new
  void clear();

  // add newline at this position
  void add(const int);
     // Argument 1: Position

  // remove range (e.g. for changing file content)
  void remove(const int, const int);
     // Argument 1: Start-Position (including)
     // Argument 2: Number of characters removed

  // insert range (e.g. for changing file content)
  void insert(const int, const int);
     // Argument 1: Start-Position (including)
     // Argument 2: number of characters inserted

  // translates position to line number
  int operator() (const int) const;
     // Argument 1: Position

  // return number of lines
  int linecount () const;


};          // class


#endif