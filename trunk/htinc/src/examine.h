/* Name: ''examine.h''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

 Created: 12.10.2k2
 last Modification: $LastChangedDate$
 Function: Declaration of Examine Object

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

// Header-Guard
#ifndef EXAMINE__H
#define EXAMINE__H

// Headers
#include <string>    // String
#include <list>      // STL List

#include "includes.h"   // Declaration of the Include Object
#include "structs.h"    // including the return struct



class examine {
private:
  // Typedefs
  typedef std::list<std::string> filelist_type_;  // List of the file's lines
                 // correspond to: includes::list_type_

  // local variables
  includes inc_;       // Inc-Object
  filelist_type_ file_;     // the file's representation
  const filelist_type_::size_type Include_Tag_Start_s_Len;
        // Length of Include_Tag_Start_s
  const filelist_type_::size_type Include_Tag_Start_e_Len;
        // Length of Include_Tag_Start_e

  bool writebackfile(const std::string &);  // Copy the list back to the file
      // Argument: File name

public:

  explicit examine(const std::string &);   // C'tor
     // Argument: Include-Directory
  struct structures::ret operator() (const std::string &);    // do examination
     // Argument: file which should be examined
  //  inline void clear() { file_.clear(); };  // clear the storage variables



};    // End class examine

#endif     // End Header Guard
