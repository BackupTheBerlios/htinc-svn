/* Name: ''structs.h''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

 Created: 13.10.2k2
 last Modification: $LastChangedDate$
 Function: Declaration of globally used structures, enumerations and Typedefs
 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#ifndef STRUCTS__H
#define STRUCTS__H

#include <string>    // String
#include <list>      // STL List

#include "linenum.h" // Line Number Object

namespace structures {

  // *** Typedefs
  // TODO: replace maybe by slist?
  typedef std::list<char> filelist_type;  // List of the file's characters


  // File Stream and Line Number Object, passed to Examine Object
  struct file {
    filelist_type chars;         // the File itself as stream
    class linenum line;           // Line Number Object associated with stream
  };

  // Return Values used by the Examine Object
  enum return_val {  // in Parenteses: variables used from struct ret
    OK,       // everything is done without error
    ERR_OPEN_FILE, // File could not be opened
    ERR_READFILE,  // Filestream could not be read
    ERR_WRITEFILE,  // changed file could not be written back to filestream
    ERR_MISSING_INCNAME, // Include Tag lacks an file name (line)
    ERR_MISSING_ENDTAG,  // no end tag found (text: Include's name)
                         // (line: Start Tag's line)
    ERR_LOADING_INC // Include file could not be loaded (text: Include's name)
  };

  // Return Structure: Contains Return Value and additional information
  struct ret {
    enum return_val val;
    unsigned int line;  // Error encountered in this line
    std::string text;  // messages in error
  };

  // Pass tag formats to the examine object
  struct tags {
    std::string start_prefix;   // Beginning of Start Tag
    std::string start_suffix;  // End of Start Tag
         // if zero length, then start tag has no parameter
    std::string end;            // End-Tag
  };


  // declare Message-Level enumeration
  // a higher number represents more output
  enum msg_level {  // Usage: Compare against values
    // e.g. if (msg_level <= QUIET) // do not output
    QUIET = 10,
    NORMAL = 50,
    DEBUG = 100
  };

  // Return Codes
  enum exit_codes {
    NO_ERR = 0,      // No error
    WRONG_PARAS=1,   // wrong parameters or options
    ERR_OPEN=2,      // error opening a file
    BAD_FILE=3,      // bad file
    NO_INC_NAME=4,   // Start Tag lacks an include file name
    BAKA=99          // internal (i. e. unexpected) error
  };

} // End namespace structures 

#endif
