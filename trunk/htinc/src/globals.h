/* Name: ''globals.h''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

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

// Help text
extern const char* const Helptext;

// Command Line Options
extern  const char* const Option_Help_l;
extern  const char* const Option_Help_s;
extern  const char* const Option_Version_s;
extern  const char* const Option_Version_l;
extern  const char* const Option_Quiet_s;
extern  const char* const Option_Quiet_l;
extern  const char* const Option_Debug_s;
extern  const char* const Option_Debug_l;
extern  const char* const Option_Include_s;
extern  const char* const Option_Include_l;


// HTML-Tags for the Include
extern const std::string Include_Tag_Start_s;
extern const std::string Include_Tag_Start_e;
  // Between tag's beginning and ending: filename of the include
  // Example: <!--INCLUDE="greetings.inc"-->
extern const std::string Include_Tag_End; // complete tag
// Remark: Start/End - Tags need to be placed on a separate line

// *** various settings
// Message Level can be modified by command line
extern structures::msg_level Message_Level;  // the Message Level to Use


}  // Ende namespace setup

#endif
