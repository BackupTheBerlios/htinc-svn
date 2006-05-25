/* Name: ''globals.h''
  Project: HTML Include
 Copyright (C) 2002,2005 Robert Lange <robert.lange@s1999.tu-chemnitz.de>

 Created: 25.03.2k5
 last Modification: $LastChangedDate: 2005-03-23 18:51:35 +0100 (Wed, 23 Mar 2005) $
 Function: Globals and Constants; extern declaration

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/


#ifndef GLOBALS__H
#define GLOBALS__H


#include <string>    // needed for setup's

#include "structs.h"         // global Structures and Enums



namespace setup {  // Messages and Settings

// Copyright message
extern const char* const Copyright;

// Default Include Directory: current dir
extern const char* const Default_Inc_Dir;

// command line arguments are directly defined in parseargs.cpp

// HTML-Tags for the Include
extern const std::string Include_Tag_Start_s;
extern const std::string Include_Tag_Start_e;
  // Between tag's beginning and ending: filename of the include
  // Example: <!--INCLUDE="greetings.inc"-->
extern const std::string Include_Tag_End; // complete tag

// HTML-Tags for Date Tags
extern const std::string Datetag_Tag_Start_s;
extern const std::string Datetag_Tag_Start_e;
  // no parameter included
extern const std::string Datetag_Tag_End; // complete tag

// HTML-Tags for Embedded Meta Date Tag
extern const std::string Datemeta_Tag_Start_s;
extern const std::string Datemeta_Tag_Start_e;
  // no parameter included
extern const std::string Datemeta_Tag_End; // complete tag


// *** various settings
// Message Level can be modified by command line
extern structures::msg_level Message_Level;  // the Message Level to Use


}  // Ende namespace setup

#endif
