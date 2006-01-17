/* Name: ''examine.cpp''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

 Created: 12.10.2k2
 last Modification: $LastChangedDate$
 Function: search the loaded file Include Start Tags,
           passes the name of found include tags and the position to
	   the Includes Object

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

/* TODO
- issue warning (or react in any other way) if we overrun another valid start
  tag while replacing text
  - reason: most likely we did something not wanted because of a missing/
            typo in a End-Tag


*/

// includes
#include <iostream>   // for printing debug messages
#include <algorithm>  // search
#include <iterator>   // advance

#include "config.h"  // Settings from configure
#include "globals.h" // Message-Level et al
#include "examine.h"



// *** Examine the file ***
struct structures::ret examine::operator() (
				   structures::file &f,
				   tagprocessor &process,
				   const structures::tags &tags,
				   bool &changed,
				   std::string & upara) {
     // Argument 1: file which should be examined (as loaded list)
     // Argument 2: Tag processing object 
     // Argument 3: Structures with parsing definitions
     // Argument 4: Set to true when file was changed,
     //             otherwise not touched
     // Argument 5: Space separated Names of changed parameters

  // return structure
  struct structures::ret returnvalues;

  // local variables
  structures::filelist_type & file = f.chars;  // Shortcut to the List itself
  const structures::filelist_type::iterator itrstart
            = file.begin();  // Iterator variable, list start
  const structures::filelist_type::iterator itrend
            = file.end();  // Iterator variable, list end
  structures::filelist_type::iterator itr = itrstart;
                                     // Iterator variable, current position
  structures::filelist_type::iterator
            ipref, // Iterator, found start tag prefix
            isuf,  // Iterator, found start tag suffix
            ietag; // Iterator, end tag
  std::string pname;       // Name of the parameter
  bool first_upara = true;   // true: insert first parameter into string upara
  bool loc_changed;          // local change marker (to detect which include files
                             // were updated)
  int insertcount;           // number of chars inserted upon include change
  int removecount;           // number of chars removed upon include change

  upara.clear();            // clear return string

  // scan list, until a Include Start-Tag is found (save pos as ipref)
  while (itrend != (ipref = std::search(itr, itrend,
		    tags.start_prefix.begin(), tags.start_prefix.end() ))
	 ) {
    // Found the Beginning of a Start Tag!
    if (setup::Message_Level >= structures::DEBUG) {    // Debug
      std::cout << "Debug (E): found start tag's beginning\n";
    }
    // make ipref pointing after start tag's prefix
    std::advance(ipref, tags.start_prefix.size() );

    // Case 1: We do expect a parameter along with a tag suffix
    if (! tags.start_suffix.empty() ) {
      // Now check: End of Start-Tag present?
      isuf = std::search(ipref, itrend,
	     tags.start_suffix.begin(), tags.start_suffix.end() );
      if (isuf == itrend) {
	// no End of Start-Tag found: It's no valid Start Tag
	if (setup::Message_Level >= structures::DEBUG) {    // Debug
	  std::cout << "Debug (E): ... but no tag suffix, therfore ignoring\n";
	}
	itr = ipref; // just assign iterator to next character
	++itr;
	continue;
      } // else: Valid Tag
      if (setup::Message_Level >= structures::DEBUG) {    // Debug
	std::cout << "Debug (E): ... and start tag's ending\n";
      }
      // now extract the include's name
      pname.assign(ipref, isuf);
      // Check 1: no empty string?
      if (pname.empty() == true) { // Error: parameter name is empty
	// fill return structure
	returnvalues.val = structures::ERR_MISSING_PARANAME;
	// Error in line xxx
	returnvalues.line = f.line(std::distance(itrstart, --ipref) );
	return returnvalues;    // and exit
      }
      // Check 2: no newline character included
      if (pname.find('\n') != pname.npos) {
	// means not valid, just continue
	if (setup::Message_Level >= structures::DEBUG) {    // Debug
	  std::cout << "Debug (E): ... newline in parameter encountered, therefore ignoring\n";
	}
	itr = ipref; // just assign iterator to next character
	++itr;
	continue;
      } // else: All checks passed
      if (setup::Message_Level >= structures::DEBUG) {    // Debug
	std::cout << "Debug (E): parameter name: " << pname << '\n';
      }
      // let isuf point after the start tag suffix
      std::advance(isuf, tags.start_suffix.size() );
    } else {   // we have no parameter
      pname.clear();       // it's empty, of course
      // let isuf point after the start tag prefix
      isuf = ipref;
    }

    // now find end tag
    ietag = std::search(isuf, itrend,
		       tags.end.begin(), tags.end.end() );
    if (ietag == itrend) {
      // ERR: end of source file reached before include file ended
	returnvalues.val = structures::ERR_MISSING_ENDTAG; // error cause
	returnvalues.line = f.line(std::distance(itrstart, --ipref));
	return returnvalues;      // signal error
    } // else: Valid Endtag

    // else: OK - Call Processing Object
    loc_changed = false;
    removecount = std::distance(isuf, ietag);// removed characters, if changed
    returnvalues = process(f, isuf, ietag, pname, loc_changed, insertcount);

    if (loc_changed == true) {  // include file was modified
      changed = true;      // save this

      // first of all, transmit changes to linenum object
      {
	int tmp = std::distance(itrstart, isuf);        // start-position
	f.line.remove(tmp, removecount);    // removed range
	f.line.insert(tmp, insertcount);   // added characters
      }

      if (upara.find(pname) == upara.npos) { // name not yet saved
	if (first_upara == true) // first time
	  first_upara = false;   // save this call
	else
	  upara += ' ';          // add a space
	upara += pname;    // add include name to changelist
      }  // End if (upara.find(pname) == upara.npos)
    } // End if (loc_changed == true)
    if (returnvalues.val  != structures::OK) { // some error was encountered
      return returnvalues;    // just pass the error code back to caller
    }
    // Update Iterator
    itr = ietag;
    advance(itr, tags.end.size() );
  } // End while

  returnvalues.val = structures::OK;   // no errors
  return returnvalues;     // go back
}
