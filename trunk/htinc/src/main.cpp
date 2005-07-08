/* Name: ''main.cpp''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

 Created: 12.10.2k2
 last Modification: $LastChangedDate$
 Function: examines the Command Line Arguments, calls the Examine Object
           with the given file and process its return value

 Command Line Parameters: see help text (in globals.cpp)

 Return Codes: see structs.h


    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

/* Erweiterungen:
- mehrere Include-Verzeichnisse angebbar
- mehrere Dateinamen angebbar
*/


#include <iostream>
#include <string>
#include <fstream>          // file stream
#include <algorithm>        // copy, count
#include <iterator>         // ostream_iterator

#include "config.h"         // Settings from configure
#include "structs.h"        // including the return struct und return values
#include "globals.h"        // Settings and Command Line Options
#include "examine.h"        // Header for the examine object
#include "includes.h"       // Header for the Include Object
#include "parseargs.h"      // command line arguments parser
#include "auxfunc.h"        // for copyfile function


// we wanna use this:
using std::cout;
using std::cerr;
using std::endl;

namespace {     // anonymous namespace
  // does the whole loading and examining of the file
  struct structures::ret analysefile(const std::string &,
				     const std::string &);
      // Argument 1: File Name
      // Argument 2: Include Directory
      // return: Return Value

  // Copy the list back to the file
  bool writebackfile(const structures::file &, 
		     const std::string &);
      // Argument 1: List of File Characters and Line Number Object
      // Argument 2: File name to copy to
}

int main(int argc, char **argv) {

  // "global" variables
  std::string dateiname;          // the file to read
  std::string incdir;             // include directory
  structures::ret retval;         // return variable


  // *** command line parsing
  {
    parseargs::arguments options;   // program options
    parseargs::getcommandline(argc, argv, options);  // parsing

    // Option Quiet found?
    if ( options.quiet ) {
      setup::Message_Level = structures::QUIET;   // set new message level
    }

    // Option Debug found?
    if ( options.debug ) { // can override Quiet
      setup::Message_Level = structures::DEBUG;   // set new message level
    }

    // Option Include not found?
    if ( options.incdir == NULL ) {
      // set to default directory
      incdir = setup::Default_Inc_Dir;
    } else {
    // the include directory supplied
    incdir = options.incdir;    
    }

    // everything OK!
    // now get also the file name
    dateiname = options.file;
  } // End of Command Line space


  if (setup::Message_Level > structures::QUIET)    // issue Copyright
    cout << setup::Copyright << endl << endl;


  // *** do the whole examination
  retval = analysefile(dateiname, incdir);
  cout.flush();        // and flush cout, just in case of following error


  // *** parse return values
  switch ( retval.val ) {
  case structures::OK:
    if (setup::Message_Level >= structures::DEBUG)    // issue Finish
      cout << "Finished\n";
    return structures::exit_codes(structures::NO_ERR); // No Error
    break;
  case structures::ERR_OPEN_FILE:  // file could not be opened
     cerr << "Error: invalid input file; unable to open file "
          << dateiname << "!\n\n";
     // Error: file could not be opened
     return structures::exit_codes(structures::ERR_OPEN);
     break;
  case structures::ERR_READFILE:  // file could not be read
     cerr << "Error: unable to read from input file "
          << dateiname << "!\n\n";
     // Error: bad file
     return structures::exit_codes(structures::BAD_FILE);
     break;
  case structures::ERR_WRITEFILE:  // could not write to file
     cerr << "Error: unable to write to file "
          << dateiname << "!\n\n";
     // Error: bad file
     return structures::exit_codes(structures::BAD_FILE);
     break;
  case structures::ERR_MISSING_INCNAME:  // Include Tag lacks a file name
    cerr << "Error: Include-Tag in line "<< retval.line
	 << " lacks an file name!\n\n";
    // Error: Tags invalid
     return structures::exit_codes(structures::NO_INC_NAME);
     break;
  case structures::ERR_MISSING_ENDTAG:  // no End Tag
    cerr << "Error: No End-Tag found for Include-Tag in line "<< retval.line
	 << "!\n\n";
    // Error: Tags invalid
     return structures::exit_codes(structures::NO_INC_NAME);
     break;
  case structures::ERR_LOADING_INC:  // Include could not be opened
     cerr << "Error: unable to load include File "
          << retval.text << "!\n\n";
     // Error: file could not be opened
     return structures::exit_codes(structures::ERR_OPEN);
     break;

  default:  // unexpected error
    cerr << "internal Error encountered!"
	 << "\n(unexpected return value from examine object)\n"
	 << "Please contact programmer about this issue.\n";
    // internal error
    return structures::exit_codes(structures::BAKA);
    break;
  } // End switch


}  // End main





namespace {         // anonymous namespace

// *** does the whole loading and examining of the file ***
struct structures::ret analysefile(const std::string &dateiname,
				   const std::string &incdir) {
      // Argument 1: File Name
      // Argument 2: Include Directory
      // return: Return Value


  // "global" variables
  std::string upincs;             // contain the name of all updated
                            // include files (from examine object)
  structures::file file;    // the file's representation with line numbers
  
  structures::ret retval;         // return variable
  structures::tags tags;          // Tags to work with
  bool changed=false;             // Record whether file was modified

  // set default error return
  retval.val = structures::OK;       // no error


  // *** load file into list
  { // space for filestream
    std::ifstream filestream(dateiname.c_str());   // open file for Input
    if ( !(filestream) || !(filestream.is_open()) ) { // file could not be opened
      retval.val = structures::ERR_OPEN_FILE;  // signal error type
      return retval;
    } // else
      // could open file
    
      // first of all: Copy the file into the list
    if (copyfile(filestream, file.chars) == false ) {
      retval.val = structures::ERR_READFILE;
      return retval;
    } // else: File copied into list
    filestream.close();    // now close file stream
    file.line.init(file.chars); // now initialise line number object
    if (setup::Message_Level >= structures::NORMAL) {    // print processed file
      std::cout << "process file: " << dateiname << " ("
		<< distance(file.chars.begin(), file.chars.end())
		<< " characters)\n";
    }
  } // End space for filestream
  


  // *** examine object
  {  // space for the examination
    examine ex;   // create examine object

    // create includes object
    includes inc(incdir);
    // Fill Tags structure
    tags.start_prefix=setup::Include_Tag_Start_s;
    tags.start_suffix=setup::Include_Tag_Start_e;
    tags.end=setup::Include_Tag_End;

    // do examination with includes object
    retval = ex(file, inc, tags, changed, upincs);
  } // End space examine object


  // *** Write back file, if needed
  // and no error occured before
  if ( (retval.val == structures::OK) && (changed)  ) {
    // yes - write it back
    if (writebackfile(file, dateiname) == false ) {
      retval.val = structures::ERR_WRITEFILE;    // error writing back!
      return retval;
    } // else: // okay
    if (setup::Message_Level >= structures::NORMAL) {    // Status message
      std::cout << "   Updated Includes: " << upincs << std::endl; // updated includes
      std::cout << "   file modified: "  // file modified
		<< 1+std::count(file.chars.begin(), file.chars.end(), '\n')
		<< " lines written\n";
    }
  }

  return retval;
}



// *** Copy list to stream ***
bool writebackfile(const structures::file &file, 
		   const std::string &fname) {
      // Argument 1: List of File Characters and Line Number Object
      // Argument 2: File name to copy to

  // first of all: Clear file
  std::ofstream fs(fname.c_str(), std::ios::out|std::ios::trunc);
    // open file for Output and truncate it
  if ( !(fs) || !(fs.is_open()) ) { // file could not be opened
    return false;                  // signal error
  }


  // local variables
  structures::filelist_type::const_iterator itr = file.chars.begin();
  const structures::filelist_type::const_iterator itr_end = file.chars.end();
  std::ostream_iterator<char> oo(fs); // output-iterator

  // copy
  std::copy(itr, itr_end, oo);
  
  return true;  // no error
}


}         // anonymous namespace
