/* Name: ''examine.cpp''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

 Created: 12.10.2k2
 last Modification (UTC): $LastChangedDate$
 Function: loads the file into memory and search for Include Start Tags,
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
#include <fstream>   // file stream
#include <iostream>  // for printing debug messages

#include "config.h"  // Settings from configure
#include "examine.h"
#include "auxfunc.h" // for copyfile function


// get Settings from main.h
namespace setup {
  extern const std::string Include_Tag_Start_s; // tag's beginning
  extern const std::string Include_Tag_Start_e; // tag's ending
  extern structures::msg_level Message_Level;        // the type of output
}

// *** Constructor ***
examine::examine(const std::string &incdir) : inc_(incdir),  // Init Include Object
	 Include_Tag_Start_s_Len(setup::Include_Tag_Start_s.size()),// Size of Strings
	 Include_Tag_Start_e_Len(setup::Include_Tag_Start_e.size())
     // Argument: Include-Directory
{}



// *** Examine the file ***
structures::ret examine::operator() (const std::string &filename) {  // do examination
     // Argument: file name which should be examined

  // return structure
  struct structures::ret returnvalues;

  { // space for filestream
    std::ifstream filestream(filename.c_str());   // open file for Input
    if ( !(filestream) || !(filestream.is_open()) ) { // file could not be opened
      returnvalues.val = structures::ERR_OPEN_FILE;  // signal error type
      return returnvalues;  // and go back
    }
    
    // first of all: Copy the file into the list
    if (copyfile(filestream, file_) == false ) {
      returnvalues.val = structures::ERR_READFILE;
      return returnvalues;     // Return the failure
    }
    // else: File copied into list
    filestream.close();    // now close file stream
  } // End space for filestream

  if (setup::Message_Level >= structures::NORMAL) {    // print processed file
    std::cout << "process file: " << filename << " ("
	      << distance(file_.begin(), file_.end())
	      << " lines)\n";
  }

  // local variables
  filelist_type_::iterator itr = file_.begin();  // Iterator variable
  std::string incname;       // Name of the include file
  std::string upincs;        // contain the name of all upates include files
  bool first_upinc = true;   // true: insert first include into string upincs
  bool changed = false;      // True is file has to be written back
  bool loc_changed;          // local change marker (to detect which include files
                             // were updated)

  // scan list, until a Include Start-Tag is found
  while (itr != file_.end() ) {
    if ((*itr).compare(0, Include_Tag_Start_s_Len, setup::Include_Tag_Start_s) == 0) {
      // Found the Beginning of a Start Tag!
      if (setup::Message_Level >= structures::DEBUG) {    // Debug
	std::cout << "Debug (E): found start tag's beginning\n";
      }
      // Now check: End of Start-Tag present?
      if (itr->compare( itr->size()-Include_Tag_Start_e_Len, 
			Include_Tag_Start_e_Len, setup::Include_Tag_Start_e) != 0) {
	// no End of Start-Tag found: It's no valid Start Tag
	++itr; // just increment iterator
      } else { // Valid Tag - now extract the include's name
	if (setup::Message_Level >= structures::DEBUG) {    // Debug
	  std::cout << "Debug (E): ... and start tag's ending\n";
	}
	incname.assign(*itr, Include_Tag_Start_s_Len,
		itr->size() - Include_Tag_Start_s_Len - Include_Tag_Start_e_Len);
	// Check: no empty string?
	if (incname.empty() == true) { // Error: include name is empty
	  // fill return structure
	  returnvalues.val = structures::ERR_MISSING_INCNAME;
	  returnvalues.line = distance(file_.begin(), itr) + 1; // Error in line xxx
	  return returnvalues;    // and exit
	}
	// else: OK - Call Includes Object
	++itr;    // increment iterator to next line after Start Tag
	if (setup::Message_Level >= structures::DEBUG) {    // Debug
	  std::cout << "Debug (E): include name: " << incname << '\n';
	}
	loc_changed = false;
	returnvalues = inc_(file_, itr, incname, loc_changed);
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
      } // End if (itr->compare( itr->size()-Include_Tag_Start_s_Len, ...
    } else {
      ++itr;     // only increment
    } // End if ((*itr).compare(0, Include_Tag_Start_s_Len, ...
  } // End while

  // check if file was changed
  if (changed == true) { // yes - write it back
    if (writebackfile(filename) == false ) {
      returnvalues.val = structures::ERR_WRITEFILE;
      return returnvalues;     // Return the failure
    }
    if (setup::Message_Level >= structures::NORMAL) {    // Status message
      std::cout << "   Updated Includes: " << upincs << std::endl; // updated includes
      std::cout << "   file modified: "  // file modified
		<< distance(file_.begin(), file_.end())
		<< " lines written\n";
    }
  }

  returnvalues.val = structures::OK;   // no errors
  return returnvalues;     // go back
}


// *** Copy list to stream ***
bool examine::writebackfile(const std::string &fname) { 
  // Copy the list back to the file

  // first of all: Clear file
  std::ofstream fs(fname.c_str(), std::ios::out|std::ios::trunc);
    // open file for Output and truncate it
  if ( !(fs) || !(fs.is_open()) ) { // file could not be opened
    return false;                  // signal error
  }

  // local variables
  filelist_type_::const_iterator itr = file_.begin();
  const filelist_type_::const_iterator itr_end = file_.end();

  // Assumption: list can't be empty, because for writing back it
  // has to be modified. And for modification it has at least
  // two lines (start and end tag)


  // copy
  for (;;) {  // see assumption: first line can be dereferenced without danger
    fs << *itr;     // put back
    ++itr;  // increment
    if (itr == itr_end)   // if the last line was written
      break;  // break before writing (invalid) additional endline into file
    fs << '\n';     // add line break
    if ( !fs || !(fs.good()) )  // something went wrong!
      return false;        // Error
  } // End while
  
  if (setup::Message_Level >= structures::DEBUG) {    // Debug
    std::cout << "Debug (E): " << distance(file_.begin(), file_.end())
	      << " lines written back\n";
  }
  return true;  // no error
}
