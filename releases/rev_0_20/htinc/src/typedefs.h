/* Name: ''typedefs.h''
  Project: HTML Include
 Copyright (C) 2005 Robert Lange <robert.lange@s1999.tu-chemnitz.de>

 Created: 26.06.2k5
 last Modification: $LastChangedDate$
 Function: Declaration of globally used Typedefs
           In separate file, to break deadlock between structs.h
	   (where is was put before) and linenum.h
 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#ifndef TYPEDEFS__H
#define TYPEDEFS__H

#include <list>      // STL List

namespace structures {

  // *** Typedefs
  // TODO: replace maybe by slist?
  typedef std::list<char> filelist_type;  // List of the file's characters

}


#endif
