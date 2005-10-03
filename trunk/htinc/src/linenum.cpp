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
#include "linenum.h"

#include <algorithm>  // find

// *** initialise object with character stream ***
void linenum::init(const structures::filelist_type &in) {
  // object is also cleared beforehand

  // Variables
  structures::filelist_type::const_iterator start = in.begin();
  structures::filelist_type::const_iterator pos;
  structures::filelist_type::const_iterator end = in.end();

  // clear container
  lines_.clear();

  // now add all newlines from the filelist
  while (1) {
    pos = std::find(start, end, '\n');
    if (pos == end) {
      break;           // found all newlines
    }
    // add new newline
    lines_.push_back(std::distance(start, pos)+1);// plus newline character
    start = ++pos;   // adjust new start position
  }
}




// *** remove range (e.g. for changing file content) ***
// CONT: noch komplett fehlerhaft und totaler Unsinn
void linenum::remove(const int start, const int count) {
  // remove range (e.g. for changing file content)
     // Argument 1: Start-Position (including)
     // Argument 2: number of characters removed

  // *** Variables
  int startline, endline;    // Starting- and Endlines
  lnums_type_::iterator itr = lines_.begin();  // iterator
  int cutcount;             // count of removed characters
  int schl;                 // loop counter
  int tmp=0;                  // temp variable

  // *** get start- and endline
  startline = (*this)(start);
  endline = (*this)(start+count);


  // *** just move all newlines in this range to the starting line
  std::advance(itr, startline-1); // advance to starting line

  if (startline == endline) {
    // just cut number of characters; no newline was removed
    *itr -= count;
    return;
  }
  //else: newlines were removed

  // first line: only remove difference to next linebreak
  // find characters before line in question
  {
    tmp=0;                  // temp variable
    lnums_type_::const_iterator itr2 = lines_.begin();
    for (schl=0;
	 schl < startline; ++schl) {
      // get number of characters
      tmp += *itr2++;
    }
  }
  // in the starting line we cut as many characters as ...
  cutcount =  (tmp - start);
  *itr++ -= cutcount;   // adjust

  // following lines: move completely out of the way
  for (schl=startline+1; schl < endline; ++schl) {
    // do the adjustment
    cutcount += *itr;
    *itr++ = 0;
  }

  // last line: only remove difference to last linebreak
  *itr -= (count - cutcount);

  return;    // finished
}


// *** insert range (e.g. for changing file content) ***
void linenum::insert(const int start, const int count) {
  // Argument 1: Start-Position (including)
  // Argument 2: number of characters inserted

  // *** Variables
  int startline;    // starting lines
  lnums_type_::iterator itr = lines_.begin();  // iterator

  // *** get startline
  startline = (*this)(start);

  // *** just insert character count in this line
  std::advance(itr, startline-1); // advance to starting line
  *itr += count;
}


// *** translates position to line number  (starting from 1) ***
int linenum::operator() (const int pos) const {
     // Argument 1: Position, starting from zero

  // Variables
  lnums_type_::const_iterator itr = lines_.begin();
  lnums_type_::const_iterator end = lines_.end();
  int line = 1;          // line: starting line is 1st
  int charcount = 0;     // Character count from beginning of the file

  // iterate through lines and find correct one
  for(; itr != end; ++itr) {
    charcount += *itr;           // adjust character count
    if (pos < charcount) {
      // it is in this line
      break;
    } // else
    // increment line
    ++line;
  }

  // Return result
  return line;
}


// *** return number of lines ***
//int linenum::linecount () const {
//  return 0;  // Dummy
//}
