/* Name: ''includes.h''
  Project: HTML Include
 Copyright (C) 2002,2005,2006 Robert Lange <robert.lange@s1999.tu-chemnitz.de>

 Created: 13.10.2k2
 last Modification: $LastChangedDate$
 Function: Declaration of Includes Object
 

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
#ifndef INCLUDES__H
#define INCLUDES__H

// Headers
#include <vector>            // storing the single includes
#include <list>             // for accessing the examine's data storage
#include <string>          // all-purposes
#include <map>            // Storing the Include files
#include <iostream>      // Debug Messages

#include "tagprocessor.h"  // base class for includes object

// Derive from base class tagprocessor
class includes : public tagprocessor {
private:
  // typedef's
  typedef std::vector<char> inc_type_;  // List of the file's lines
  typedef std::string key_type_;       // Key for keeping the include's in the map
  typedef std::map<key_type_, inc_type_> storage_type_; // storing alle the includes

  // private variables
  std::string incdir_;      // the include directory
  storage_type_ incmap_;    // map storing the include file's content
                            // the key is the include file with path

  // private functions
  bool store_include_(const std::string &);
     // Argument: file name (with path) of the given include file

public:

  explicit includes(const std::string &);   // C'tor
     // Argument: Include-Directory

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

};    // End class includes

#endif     // End Header Guard
