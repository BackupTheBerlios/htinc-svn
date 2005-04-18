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

// includes
#include <iostream>  // for printing debug messages

#include "config.h"  // Settings from configure
#include "globals.h" // Message-Level et al
#include "examine.h"



// *** Examine the file ***
struct structures::ret examine::operator() (
				   structures::filelist_type &file,
				   includes &inc,
				   const structures::tags &tags,
				   bool &changed,
				   std::string & upincs) {
     // Argument 1: file which should be examined (as loaded list)
     // Argument 2: Includes Object
     // Argument 3: Structures with parsing definitions
     // Argument 4: true, if file was changed
     // Argument 5: Name of changed include files, if Arg.4 is true


  // Constants
  const structures::filelist_type::size_type Start_Prefix_Size
                        = tags.start_prefix.size();
        // Length of Include_Tag_Start_s
  const structures::filelist_type::size_type Start_Suffix_Size
                        = tags.start_suffix.size();
        // Length of Include_Tag_Start_e

  // return structure
  struct structures::ret returnvalues;

  // local variables
  structures::filelist_type::iterator itr
            = file.begin();  // Iterator variable
  std::string incname;       // Name of the include file
  bool first_upinc = true;   // true: insert first include into string upincs
  bool loc_changed;          // local change marker (to detect which include files
                             // were updated)

  // changed is false on first
  changed = false;
  upincs.clear();            // clear return string

  // scan list, until a Include Start-Tag is found
  while (itr != file.end() ) {
    if ((*itr).compare(0, Start_Prefix_Size, tags.start_prefix) == 0) {
      // Found the Beginning of a Start Tag!
      if (setup::Message_Level >= structures::DEBUG) {    // Debug
	std::cout << "Debug (E): found start tag's beginning\n";
      }
      // Now check: End of Start-Tag present?
      if (itr->compare( itr->size()-Start_Suffix_Size, 
			Start_Suffix_Size, tags.start_suffix) != 0) {
	// no End of Start-Tag found: It's no valid Start Tag
	++itr; // just increment iterator
      } else { // Valid Tag - now extract the include's name
	if (setup::Message_Level >= structures::DEBUG) {    // Debug
	  std::cout << "Debug (E): ... and start tag's ending\n";
	}
	incname.assign(*itr, Start_Prefix_Size,
	       itr->size() - Start_Prefix_Size - Start_Suffix_Size);
	// Check: no empty string?
	if (incname.empty() == true) { // Error: include name is empty
	  // fill return structure
	  returnvalues.val = structures::ERR_MISSING_INCNAME;
	  returnvalues.line = distance(file.begin(), itr) + 1; // Error in line xxx
	  return returnvalues;    // and exit
	}
	// else: OK - Call Includes Object
	++itr;    // increment iterator to next line after Start Tag
	if (setup::Message_Level >= structures::DEBUG) {    // Debug
	  std::cout << "Debug (E): include name: " << incname << '\n';
	}
	loc_changed = false;
	returnvalues = inc(file, itr, incname, loc_changed);
	if (loc_changed == true) {  // include file was modified
	  changed = true;      // save this
          if (upincs.find(incname) == upincs.npos) { // name not yet saved
	    if (first_upinc == true) // first time
	      first_upinc = false;   // save this call
	    else
	      upincs += ' ';          // add a space
	    upincs += incname;    // add include name to changelist
	  }  // End if (upincs.find(incname) == upincs.npos)
	} // End if (loc_changed == true)
	if (returnvalues.val  != structures::OK) { // some error was encountered
	  return returnvalues;    // just pass the error code back to caller
	}
      } // End if (itr->compare( itr->size()-Start_Prefix_Size, ...
    } else {
      ++itr;     // only increment
    } // End if ((*itr).compare(0, Start_Prefix_Size, ...
  } // End while


  returnvalues.val = structures::OK;   // no errors
  return returnvalues;     // go back
}
