/* Name: ''date.h''
 Project: HTML Include
 Copyright (C) 2002,2005,2006 Robert Lange <robert.lange@s1999.tu-chemnitz.de>

 Created: 03.12.2k5
 last Modification: $LastChangedDate$
 Function: Declaration of Date Object


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
#ifndef DATE__H
#define DATE__H

// Headers
#include <string>         // Strings

#include "tagprocessor.h"  // base class for date object

// Derive from base class tagprocessor
class date : public tagprocessor {
private:

  // private variables
  const std::string date_string_;    // the date string

public:

  explicit date(const std::string &);   // C'tor
     // Argument: Date String

  struct structures::ret operator()
      (structures::file &,
       list_type_::iterator &, const list_type_::iterator &,
       const std::string &, bool &, int &);
     // Argument 1: the List and Line Number Obj.  containing the source file
     // Argument 2: Iterator pointing to the first character of the include
     //             It is adjusted in the case of a removal to avoid
     //             iterator invalidation
     // Argument 3: Iterator pointing after the last character of the include
     //             Is still valid after exit
     // Argument 4: file name of the given include file
     // Argument 5: set to 'true' if list was changed (otherwise don't touch)
     // Argument 6: number of characters inserted in place of include range

};    // End class date

#endif     // End Header Guard
