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
#include "includes.h"
#include "config.h"  // Settings from configure
#include "auxfunc.h" // for copyfile function
#include "globals.h" // get Settings



// *** Constructor ***
includes::includes(const std::string &incdir) : incdir_(incdir)   // C'tor
     // Argument: Include-Directory
{}



// *** check the includes ***
struct structures::ret includes::operator()
  (list_type_ & source, list_type_::iterator &itr,
   const std::string &file, bool &modified)      { // check include
     // Argument 1: the List containing the source file
     // Argument 2: Iterator pointing to the first line of the include
     // Argument 3: file name of the given include file
     // Argument 4: set to 'true' if list was changed

    // local variables
    structures::ret returnvalues;       // create return 'stack'

    // check, if the include is already stored
    if (incmap_.find(file) == incmap_.end() ) {
      // not stored yet
      if (!store_include_(file)) { // error storing the new include
	returnvalues.val = structures::ERR_LOADING_INC; // Type of error
	returnvalues.text = incdir_ + file;           // encountered with this file
	return returnvalues;       // go back
      }
      // else: OK: one can continue
      if (setup::Message_Level >= structures::DEBUG) {    // Debug
	const storage_type_::const_iterator inc_pos = incmap_.find(file);
	      // shortcut to specific include
	std::cout << "Debug (I): new include file stored: " << file << " ("
		  << distance( (inc_pos->second).begin(),
			       (inc_pos->second).end()) 
		  << " lines)\n";
      }
    }

    // more local variables
    const storage_type_::const_iterator inc_pos = incmap_.find(file);
           // shortcut to specific include
    inc_type_::const_iterator incitr =  ((*inc_pos).second).begin();
          // Iterator through the specivic include file
    const inc_type_::const_iterator inc_begin = incitr;
          // keep beginning of this include file
    const inc_type_::const_iterator inc_end = (inc_pos->second).end();
          // keep end of this include file
    const list_type_::iterator ende = source.end();
    const list_type_::iterator src_begin = itr;   // keep start in source list
    bool changed = false;   // true if include is changed

    // now check, if the includes was changed
    while (incitr != inc_end) { // first of all: compare all lines
      if (itr == ende) {  // ERR: end of source file reached before include file ended
	returnvalues.val = structures::ERR_MISSING_ENDTAG; // error cause
	returnvalues.text = incdir_ + file;   // name of the include
	returnvalues.line = distance(source.begin(), src_begin);
	                    // line of the start tag
	return returnvalues;      // signal error
      }
      if ( (*itr) != (*incitr) ) {    // not the same
	changed = true;    // save this
	break;       // and exit while
      }
      ++incitr; ++itr;   // increment both iterators
    }
    if (!changed) {  // check if last line is an End Tag
      if (itr == ende) {  // ERR: no End Tag found
	returnvalues.val = structures::ERR_MISSING_ENDTAG; // error cause
	returnvalues.text = file;   // name of the include
	returnvalues.line = distance(source.begin(), src_begin); // line of start tag
	return returnvalues;      // signal error
      } // else
      if ( (*itr) == setup::Include_Tag_End) {  // it is so
	++itr; // last increment
	if (setup::Message_Level >= structures::DEBUG) {    // Debug
	  std::cout << "Debug (I): tested include file was not modified\n";
	}
	returnvalues.val = structures::OK;     // everything OK
	return returnvalues;       // and go back
      }
    }
    // else: include was changed and has to be replaced

    // first of all: find end tag in source file
    itr = find(itr, ende, setup::Include_Tag_End);
    if (itr == ende) {  // ERR: end of source file reached before include file ended
      returnvalues.val = structures::ERR_MISSING_ENDTAG; // error cause
      returnvalues.text = file;   // name of the include
      returnvalues.line = distance(source.begin(), src_begin);// line of the start tag
      return returnvalues;      // signal error
    }
    // else: itr points to end tag
    modified = true;    // source list will now be modified
    if (setup::Message_Level >= structures::NORMAL) {    // print modified include
      std::cout << "   include file \""
		<< file
		<< "\" was changed (modify file)\n";
    }

    // clear all in-between elements
    source.erase(src_begin, itr);

    // now insert new elements
    source.insert(itr, inc_begin, inc_end);

    // increment Iterator to next line (after End Tag)
    ++itr;

    // return with everything OK
    returnvalues.val = structures::OK;
    return returnvalues;
}



// *** private: store new include files ***
bool includes::store_include_(const std::string &fil) {
     // Argument: file name of the given include file


  std::ifstream file((incdir_ + fil).c_str());   // open file for Input
  
  if ( !(file) || !(file.is_open()) ) {
    return false;   // file could not be opened
  }


  return copyfile(file, incmap_[fil]); // insert element and delegate task
}
