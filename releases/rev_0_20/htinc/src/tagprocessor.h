/* Name: ''tagprocessor.h''
  Project: HTML Include
 Copyright (C) 2005,2006 Robert Lange <robert.lange@s1999.tu-chemnitz.de>

 Created: 20.11.2k5
 last Modification: $LastChangedDate$
 Function: Virtual Base Class for Tag-modifying objects
 

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
#ifndef TAGPROCESSOR__H
#define TAGPROCESSOR__H

// Headers

#include "structs.h"   // including the return struct



class tagprocessor {

public:

  // typedef as shortcut
  typedef structures::filelist_type list_type_;

  // Empty virtual destructor
  virtual ~tagprocessor() {};

  // Pure Virtual Operation Function
  virtual struct structures::ret operator()
      (structures::file &,
       list_type_::iterator &, const list_type_::iterator &,
       const std::string &, bool &, int &) = 0;
     // Argument 1: the List and Line Number Obj.  containing the source file
     // Argument 2: Iterator pointing to the first character of the embedded data
     //             It is adjusted in the case of a removal to avoid
     //             iterator invalidation
     // Argument 3: Iterator pointing after the last character of the data
     //             Is still valid after exit
     // Argument 4: Tag parameter, zero when not present
     // Argument 5: set to 'true' if list was changed (otherwise don't touch)
     // Argument 6: number of characters inserted in place of include range

};    // End class tagprocessor



#endif     // End Header Guard
