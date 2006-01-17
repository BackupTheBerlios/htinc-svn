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
#include <string>

#include "includes.h"   // Declaration of the Include Object
#include "structs.h"    // including the return struct
#include "tagprocessor.h"  // base class for tag processing objects



class examine {
private:


public:

  explicit examine() {};   // C'tor

  // do examination
  struct structures::ret operator() (structures::file &,
				     tagprocessor &,
				     const structures::tags &,
				     bool &,
				     std::string &);
     // Argument 1: file which should be examined (as loaded list)
     // Argument 2: Tag processing object 
     // Argument 3: Structures with parsing definitions
     // Argument 4: Set to true when file was changed,
     //             otherwise not touched
     // Argument 5: Space separated Names of changed parameters




};    // End class examine

#endif     // End Header Guard
