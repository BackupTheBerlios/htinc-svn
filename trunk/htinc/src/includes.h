/* Name: ''includes.h''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

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
#include "structs.h"    // including the return struct



class includes {
private:
  // typedef's
  typedef std::vector<std::string> inc_type_;  // List of the file's lines
  typedef std::string key_type_;       // Key for keeping the include's in the map
  typedef std::map<key_type_, inc_type_> storage_type_; // storing alle the includes

  typedef std::list<std::string> list_type_;  // List used withing the examine object
                                              // (for calling the operator() )
                 // correspond to: examine::filelist_type_

  // private variables
  std::string incdir_;      // the include directory
  storage_type_ incmap_;    // map storing the include file's content

  // private functions
  bool store_include_(const std::string &);
     // Argument: file name of the given include file

public:

  explicit includes(const std::string &);   // C'tor
     // Argument: Include-Directory

    struct structures::ret operator()
      (list_type_ &, list_type_::iterator &, const std::string &, bool &);
     // Argument 1: the List containing the source file
     // Argument 2: Iterator pointing to the first line of the include
     // Argument 3: file name of the given include file
     // Argument 4: set to 'true' if list was changed


};    // End class includes

// #include "includes.n"   /// just include the template definition

#endif     // End Header Guard
