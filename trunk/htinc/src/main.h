/* Name: ''main.h''
  Project: HTML Include
 Copyright (C) 2002 MadDog/Robert Lange

 Created: 12.10.2k2
 last Modification (UTC): $LastChangedDate$
 Function: Header for main.cpp; Copyright, Helptext and Name of Command Options
           Also some settings
 Remark: This file is only to be included by main.h; other modules can
         get access to variables defined here by using the extern directive

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include <string>    // needed for setup's


namespace setup {  // Messages and Settings


// Copyright message
const char* const Copyright =
"             " PACKAGE_STRING " - (C) 2002 MadDog/Robert Lange\n"
"      robert.lange@s1999.tu-chemnitz.de, Command Line Parser by Jan Langer";


// Help text
const char* const Helptext =
"HTML Include handles Include files in HTML Source files. It checks\n"
"the given source file for Start and End Tags (special-styled comments) and\n"
"replace the content of the embraced area with the content in the\n"
"associated include file, if the content differs.\n"
"\n"
"Usage: htinc [filename|-h|-v] -i include_dir {-q}\n"
"-h/--help - shows this help screen\n"
"-v/--version - prints version\n"
"-q/-quiet - prints only error messages\n"
"-d/-debug - enable debug messages\n"
"filename - the file which should be processed\n"
"-i/-inc - directory (relative to current directory) where the include\n"
"          files should be searched (with slash at the end)\n"
"\n"
"Example: htinc index.html -i ../includes/\n"
"\n"
"Send bug reports to: " PACKAGE_BUGREPORT
"\n"
;

// Command Line Options
const char* const Option_Help_l = "--help"; // Help
const char* const Option_Help_s = "-h";
const char* const Option_Version_s = "-v"; // Version
const char* const Option_Version_l = "--version";
const char* const Option_Quiet_s = "-q"; // Quiet
const char* const Option_Quiet_l = "-quiet";
const char* const Option_Debug_s = "-d"; // Debug
const char* const Option_Debug_l = "-debug";
const char* const Option_Include_s = "-i"; // Include Dir
const char* const Option_Include_l = "-inc";


// HTML-Tags for the Include
extern const std::string Include_Tag_Start_s = "<!--INCLUDE=\""; // tag's beginning
extern const std::string Include_Tag_Start_e = "\"-->"; // tag's ending
  // Between tag's beginning and ending: filename of the include
  // Example: <!--INCLUDE="greetings.inc"-->
extern const std::string Include_Tag_End = "<!--ENDINC-->"; // complete tag
// Remark: Start/End - Tags need to be placed on a separate line



// various settings
structures::msg_level Message_Level = structures::NORMAL;  // the Message Level to Use


}  // Ende namespace setup
