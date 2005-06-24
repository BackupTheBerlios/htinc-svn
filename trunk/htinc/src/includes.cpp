/* Name: ''includes.cpp''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

 Created: 13.10.2k2
 last Modification: $LastChangedDate$
 Function: check if Include file was changed and replace the Include in
           this chase

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
#include <fstream>
#include <algorithm>   // equal

#include "includes.h"
#include "config.h"  // Settings from configure
#include "auxfunc.h" // for copyfile function
#include "globals.h" // get Settings

// *** Constructor ***
includes::includes(const std::string &incdir) : incdir_(incdir)   // C'tor
     // Argument: Include-Directory
{}



// *** check the includes ***
struct structures::ret includes::operator() (structures::file & file,
       const list_type_::iterator & itr,
       const list_type_::iterator &itrend,
       const std::string &incname, bool &modified,
       int &writecount ) {
     // Argument 1: the List and Line Number Obj.  containing the source file
     // Argument 2: Iterator pointing to the first character of the include
     // Argument 3: Iterator pointing after the last character of the include
     // Argument 4: file name of the given include file
     // Argument 5: set to 'true' if list was changed (otherwise don't touch)
     // Argument 6: number of characters inserted in place of include range

    // *** local variables
    structures::ret returnvalues;       // create return 'stack'

    // *** construct file name with path
    std::string incfile(incdir_);       // declare variable
    // do we need to add path separator inbetween?
    if ( (incdir_[incdir_.size()-1] != '/') &&
	 (incfile[0] != '/') ) {
      incfile.push_back('/');          // yes
    }
    incfile += incname;         // append name


    // check, if the include is already stored
    if (incmap_.find(incfile) == incmap_.end() ) {
      // not stored yet

      if (!store_include_(incfile)) { // error storing the new include
	returnvalues.val = structures::ERR_LOADING_INC; // Type of error
	returnvalues.text = incfile;           // encountered with this file
	return returnvalues;       // go back
      }
      // else: OK: one can continue
      if (setup::Message_Level >= structures::DEBUG) {    // Debug
	const storage_type_::const_iterator inc_pos = incmap_.find(incfile);
	      // shortcut to specific include
	std::cout << "Debug (I): new include file stored: " << incfile << " ("
		  << distance( (inc_pos->second).begin(),
			       (inc_pos->second).end()) 
		  << " characters)\n";
      }
    }

    // more local variables
    const storage_type_::const_iterator inc_pos = incmap_.find(incfile);
              // shortcut to specific include
    const inc_type_::const_iterator inc_begin = (*inc_pos).second.begin();
             // keep beginning of this include file
    const inc_type_::const_iterator inc_end = (inc_pos->second).end();
             // keep end of this include file

    bool changed;   // true if include is changed

    // now check, if the include was changed
    if (std::distance(itr, itrend) != 
	std::distance(inc_begin, inc_end) ) {
      // One: equal length - failed
      changed = true;
    } else {
      // Two: real comparision
      changed = !(std::equal(inc_begin, inc_end, itr) );
    }

    if (!changed) {  // identical
      if (setup::Message_Level >= structures::DEBUG) {    // Debug
	std::cout << "Debug (I): tested include file was not modified\n";
      }
      returnvalues.val = structures::OK;     // everything OK
      return returnvalues;       // and go back
    }
    // else: include was changed and has to be replaced
    modified = true;    // source list will now be modified
    if (setup::Message_Level >= structures::NORMAL) {    // print modified include
      std::cout << "   include file \""
		<< incfile
		<< "\" was changed (modify file)\n";
    }

    // one more time local variables
    list_type_::iterator itr_pref = itr;  // position one before start
    --itr_pref;                           // to escape invalidation at erase

    // clear all in-between elements
    file.chars.erase(itr, itrend);

    // now insert new elements at the same position
    file.chars.insert(++itr_pref, inc_begin, inc_end);

    // return number of charcters written
    writecount = (*inc_pos).second.size();

    // return with everything OK
    returnvalues.val = structures::OK;
    return returnvalues;
}



// *** private: store new include files ***
bool includes::store_include_(const std::string &fil) {
     // Argument: file name (with path) of the given include file

  std::ifstream file(fil.c_str() );   // open file for Input
  
  if ( !(file) || !(file.is_open()) ) {
    return false;   // file could not be opened
  }


  // insert element and delegate task
  return copyfile(file, incmap_[fil]); 
}
