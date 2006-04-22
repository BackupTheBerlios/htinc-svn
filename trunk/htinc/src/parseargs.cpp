/*
file name: ''parseargs.h''
  project: HTML Include
 Copyright (C) 2005,2006 Robert Lange <robert.lange@s1999.tu-chemnitz.de>

 Created: 26.03.2k5 (from project CNSIM)
 last Modification: $LastChangedDate$
 Function: Command Line Argument Parser

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include <argp.h>           // LibC argument parser

#include "config.h"         // Settings from configure
#include "parseargs.h"      // Header
#include "globals.h"        // Settings
#include "structs.h"        // including the return struct und return values


namespace {  // anonymous namespace

/* derived from libc-example:
   http://www.gnu.org/software/libc/manual/html_node/Argp-Example-3.html#Argp%20Example%203

   This program uses the same features as example 2, and uses options and
   arguments.
     
   We now use the first four fields in ARGP, so here's a description of them:
   OPTIONS  - A pointer to a vector of struct argp_option (see below)
   PARSER   - A function to parse a single option, called by argp
   ARGS_DOC - A string describing how the non-option arguments should look
   DOC      - A descriptive string about this program; if it contains a
   vertical tab character (\v), the part after it will be
   printed *following* the options
     
   The function PARSER takes the following arguments:
   KEY  - An integer specifying which option this is (taken
   from the KEY field in each struct argp_option), or
   a special key specifying something else; the only
   special keys we use here are ARGP_KEY_ARG, meaning
   a non-option argument, and ARGP_KEY_END, meaning
   that all arguments have been parsed
   ARG  - For an option KEY, the string value of its
   argument, or NULL if it has none
   STATE- A pointer to a struct argp_state, containing
   various useful information about the parsing state; used here
   are the INPUT field, which reflects the INPUT argument to
   argp_parse, and the ARG_NUM field, which is the number of the
   current non-option argument being parsed
   It should return either 0, meaning success, ARGP_ERR_UNKNOWN, meaning the
   given KEY wasn't recognized, or an errno value indicating some other
   error.
     
   Note that in this example, main uses a structure to communicate with the
   parse_opt function, a pointer to which it passes in the INPUT argument to
   argp_parse.  Of course, it's also possible to use global variables
   instead, but this is somewhat more flexible.
     
   The OPTIONS field contains a pointer to a vector of struct argp_option's;
   that structure has the following fields (if you assign your option
   structures using array initialization like this example, unspecified
   fields will be defaulted to 0, and need not be specified):
   NAME   - The name of this option's long option (may be zero)
   KEY    - The KEY to pass to the PARSER function when parsing this option,
   *and* the name of this option's short option, if it is a
   printable ascii character
   ARG    - The name of this option's argument, if any
   FLAGS  - Flags describing this option; some of them are:
   OPTION_ARG_OPTIONAL - The argument to this option is optional
   OPTION_ALIAS        - This option is an alias for the
   previous option
   OPTION_HIDDEN       - Don't show this option in -help output
   DOC    - A documentation string for this option, shown in -help output
     
   An options vector should be terminated by an option with all fields zero. */
     
     
     
/* program documentation. */
static char doc[] =
"HTML Include handles Include files in HTML Source files. It checks\n"
"the given source file for Start and End Tags (special-styled comments) and\n"
"replace the content of the embraced area with the content in the\n"
"associated include file, if the content differs.\n"
  "\v"              // separate pre-arguments text from past-arguments text
// add doc of the Tags here?
"Example: htinc index.html -i ../includes/\n"
;
     
/* name of the arguments we accept. */
static char args_doc[] = "file(s)_to_process";

/* The options we understand. */
static struct argp_option options[] = {
  {"debug",    'd', 0,      0,  "Enable debug messages" },
  {"quiet",    'q', 0,      0,  "Print only error messages" },
  {"include",  'i', "incdir", 0, 
   "Directory (relative to current directory) where the include "
   "files should be searched (with slash at the end). "
   "Default is include/"  }, // globals.cpp/setup::Default_Inc_Dir
  // we automatically understand shortings of long options
  { 0 }
};
     

  /* Parse a single option. */
  static error_t
  parse_opt (int key, char *arg, struct argp_state *state)
  {
    /* Get the input argument from argp_parse, which we
       know is a pointer to our arguments structure. */
    struct parseargs::arguments *arguments =
           static_cast<struct parseargs::arguments*>(state->input);
     
    switch (key)
      {
      case 'd':
	arguments->debug = true;
	break;
      case 'q':
	arguments->quiet = true;
	break;
      case 'i':
	arguments->incdir = arg;
	break;
     
      case ARGP_KEY_ARG:
	// add file to files to process - list
     	arguments->file.push_back(arg);
     	break;
     
      case ARGP_KEY_END: // tests
	if (state->arg_num < 1)
	  /* Not enough arguments. */
	  argp_usage (state);
	break;
     
      default:
	return ARGP_ERR_UNKNOWN;
      }
    return 0;
  }



}  // anonymous namespace

// for argp:
const char * argp_program_version = setup::Copyright; // --version Parameter
const char * argp_program_bug_address =               // Report Bugs to:
                   PACKAGE_BUGREPORT ;
error_t argp_err_exit_status =              // exit code due parsing errors
        structures::exit_codes(structures::WRONG_PARAS);

namespace parseargs {
// *** parse command line *************************************
// return: true: success, false: error
// argc, argv: command line (from main)
// pargs: parsed options and arguments
  void getcommandline(const int & argc, char *argv[], arguments & pargs) {


     // variables
     /* Our argp parser. */
     static struct argp argp = { options, parse_opt, args_doc, doc };
     
     /* Parse our arguments; every option seen by parse_opt will
	be reflected in arguments. */
     argp_parse (&argp, argc, argv, 0, 0, &pargs);

     return;
  }

} // namespace
