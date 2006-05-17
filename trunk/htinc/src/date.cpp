/* Name: ''date.cpp''
 Project: HTML Include
 Copyright (C) 2002,2005,2006 Robert Lange <robert.lange@s1999.tu-chemnitz.de>

 Created: 03.12.2k5
 last Modification: $LastChangedDate$
 Function: Replaces a date tag with the current date
           (or any other string given by the constructor)


    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

// includes
#include <algorithm>   // equal
#include <iostream>      // Debug Messages

#include "date.h"
#include "config.h"  // Settings from configure
#include "globals.h" // get Settings

// *** Constructor ***
date::date(const std::string &ds) : date_string_(ds)   // C'tor
     // Argument: Date String
{}

// *** check the includes ***
struct structures::ret date::operator() (structures::file & file,
       list_type_::iterator & itr,
       const list_type_::iterator &itrend,
       const std::string &,
       bool &modified,
       int &writecount ) {
     // Argument 1: the List and Line Number Obj.  containing the source file
     // Argument 2: Iterator pointing to the first character of the include
     //             It is adjusted in the case of a removal to avoid
     //             iterator invalidation
     // Argument 3: Iterator pointing after the last character of the include
     //             Is still valid after exit
     // Argument 4: not present (tag parameter)
     // Argument 5: set to 'true' if list was changed (otherwise don't touch)
     // Argument 6: number of characters inserted in place of include range

    // *** local variables
    structures::ret returnvalues;       // create return 'stack'
    bool changed;   // true if include is changed

    // now check, if the date text was changed
    changed = !(std::equal(date_string_.begin(),date_string_.end(), itr) );

    if (!changed) {  // identical
      if (setup::Message_Level >= structures::DEBUG) {    // Debug
	std::cout << "Debug (D): date string was not modified\n";
      }
      returnvalues.val = structures::OK;     // everything OK
      return returnvalues;       // and go back
    }
    // else: date was changed and has to be replaced
    modified = true;    // source list will now be modified
    if (setup::Message_Level >= structures::NORMAL) {    // print modified date
      std::cout << "   Updated date entry in line "
		<< file.line(std::distance(file.chars.begin(), itr) )
		<< std::endl;
    }

    // once more local variables
    list_type_::iterator itr_pref = itr;  // position one before start
    --itr_pref;                           // to escape invalidation at erase
    list_type_::iterator itr_pref_ret = itr_pref; // for returning itr

    // clear all in-between elements
    file.chars.erase(itr, itrend);

    // now insert new elements at the same position
    file.chars.insert(++itr_pref, date_string_.begin(), date_string_.end() );

    // revalidate itr
    itr = ++itr_pref_ret;

    // return number of charcters written
    writecount = date_string_.size();

    // return with everything OK
    returnvalues.val = structures::OK;
    return returnvalues;
}

