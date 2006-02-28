/* Name: ''globals.cpp''
  Project: HTML Include
 Copyright (C) 2002,2005,2006 Robert Lange <robert.lange@s1999.tu-chemnitz.de>

 Created: 25.03.2k5 (from main.h)
 last Modification: $LastChangedDate$
 Function: Globals and Constants;
           Copyright, Helptext and Name of Command Options
           Also some settings

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include "config.h"         // Settings from configure
#include "globals.h"        // Header

namespace setup {  // Messages and Settings


// Copyright message
const char* const Copyright =
"        " PACKAGE_STRING " - (C) 2002,2005 Robert Lange\n"
"        robert.lange@s1999.tu-chemnitz.de, Licensed under GPL";


// Default Include Directory: current dir
const char* const Default_Inc_Dir = "./";


// HTML-Tags for the Include
const std::string Include_Tag_Start_s = "<!--INCLUDE=\""; // tag's beginning
const std::string Include_Tag_Start_e = "\"-->"; // tag's ending
  // Between tag's beginning and ending: filename of the include
  // Example: <!--INCLUDE="greetings.inc"-->
const std::string Include_Tag_End = "<!--ENDINC-->"; // complete tag

// HTML-Tags for Date Tags
const std::string Datetag_Tag_Start_s = "<!--INCLUDEDATE-->"; // tag's beginning
const std::string Datetag_Tag_Start_e;
  // no start-end tag means no parameter included
const std::string Datetag_Tag_End = "<!--ENDINC-->"; // complete tag

// HTML-Tags for Embedded Meta Date Tag
const std::string Datemeta_Tag_Start_s = "<meta name=\"date\" content=\""; // tag's beginning
const std::string Datemeta_Tag_Start_e;
  // no start-end tag means no parameter included
const std::string Datemeta_Tag_End = "\">"; // complete tag


// various settings
structures::msg_level Message_Level = structures::NORMAL;  // the Message Level to Use


}  // Ende namespace setup
