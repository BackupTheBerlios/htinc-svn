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

#include "config.h"         // Settings from configure
#include "structs.h"        // including the return struct und return values
#include "globals.h"        // Settings and Command Line Options
#include "examine.h"        // Header for the examine object
#include "utils/cmdargs.h"  // der command line parser


// we wanna use this:
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char **argv) {

  // "global" variables
  std::string dateiname;          // the file to read
  std::string incdir;         // include directory

  // command line parsing
  {  // spans space for command line parser object
    tools::cmd_args cl;    // Command Line

    // register options
    cl.add_option(setup::Option_Help_l, setup::Option_Help_s); // Help
    cl.add_option(setup::Option_Version_l, setup::Option_Version_s); // Version
    cl.add_option(setup::Option_Quiet_l, setup::Option_Quiet_s); // Quiet
    cl.add_option(setup::Option_Debug_l, setup::Option_Debug_s); // Quiet
    cl.add_option(setup::Option_Include_l, setup::Option_Include_s, 1); // Include

    // start parsing
    cl.parse(argc, argv);

    // help text wanted?
    if ( cl.is_option(setup::Option_Help_s) ) {
      cout << setup::Helptext;
      return structures::exit_codes(structures::NO_ERR);
    }

    // version wanted?
    if ( cl.is_option(setup::Option_Version_s) ) {
      cout << setup::Copyright << endl;
      return structures::exit_codes(structures::NO_ERR);
    }

    // Option Quiet found?
    if ( cl.is_option(setup::Option_Quiet_s) ) {
      setup::Message_Level = structures::QUIET;   // set new message level
    }

    // Option Debug found?
    if ( cl.is_option(setup::Option_Debug_s) ) { // can override Quiet
      setup::Message_Level = structures::DEBUG;   // set new message level
    }

    if ( (cl.count() < 1 ) || (cl.count() > 2) ) {
      // too few or too many parameters
      cerr << "Error: No or too many input files!\n"
	   << "Help text with \"htinc -h\"\n\n";
      // Error: wrong parameters or options
      return structures::exit_codes(structures::WRONG_PARAS);
    }

    // Option Include not found?
    if ( !(cl.is_option(setup::Option_Include_s)) ) {
      // no
      cerr << "Error: option \"" << setup::Option_Include_s << "\" not found!\n"
	   << "Help text with \"htinc -h\"\n\n";
      // Error: wrong parameters or options
      return structures::exit_codes(structures::WRONG_PARAS);
    }

    // get Option Include argument
    incdir = cl.option_arg(setup::Option_Include_s);
    if (incdir.empty()  ) {
      // no content
      cerr << "Error: Missing Include directory after option \""
	   << setup::Option_Include_s << "\"!\n"
	   << "Help text with \"htinc -h\"\n\n";
      // Error: wrong parameters or options
      return structures::exit_codes(structures::WRONG_PARAS);
    }

    // everything OK!
    // now get also the file name
    dateiname = cl.arg(0);
  } // End of Command Line space


  if (setup::Message_Level > structures::QUIET)    // issue Copyright
    cout << setup::Copyright << endl << endl;

  // return variable
  structures::ret retval;

  // examine object
  {  // space for the examine object
    examine ex(incdir);   // initialise with Include Directory

    // do examination
    retval = ex(dateiname);
  } // End space examine object

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
