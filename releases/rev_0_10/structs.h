/* Name: ''includes.h''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

 Created: 13.10.2k2
 last Modification (UTC): $Date: 2002/11/03 17:38:03 $
 Function: Declaration of globally used structures and enumerations
 

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

namespace structures {

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


  // declare Message-Level enumeration
  // a higher number represents more output
  enum msg_level {  // Usage: Compare against values
    // e.g. if (msg_level <= QUIET) // do not output
    QUIET = 10,
    NORMAL = 50,
    DEBUG = 100
  };

} // End namespace
#endif
