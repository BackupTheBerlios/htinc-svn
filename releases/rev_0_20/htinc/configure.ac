#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
# Copyright (C) 2005 Robert Lange <robert.lange@s1999.tu-chemnitz.de>
# last Modification: $LastChangedDate$


# *** Initialization
# Autoconf
AC_INIT(HTML Include, 0.20, robert.lange@s1999.tu-chemnitz.de, htinc)
# where to put and find the temporary configuration files
AC_CONFIG_AUX_DIR(config)
# Autoconf Version not below:
AC_PREREQ(2.59)
# Automake: create distribution with bzip2, no GNU program
AM_INIT_AUTOMAKE(dist-bzip2 no-dist-gzip foreign)


# *** Some Configurations
# some file that is in the package's source directory
AC_CONFIG_SRCDIR(src/examine.h)
# Set CXXFLAGS for C++ compiler manually (to avoid debug switch -g)
# all warnings enabled
# Do not set "-pedantic" here because of known libc::argp bug in
# combination with -Ox options. See src/Makefile.am
AC_SUBST(CXXFLAGS, "-Wall -ansi")

# *** Checks for programs.
# C++ Compiler
AC_PROG_CXX
# Install Program
AC_PROG_INSTALL

# *** Add Debug Option for Configure
AC_ARG_ENABLE(debug,
   AS_HELP_STRING([--enable-debug], [Compile with debugging support]),
   [case "${enableval}" in
     yes) debug=true ;;
     no)  debug=false ;;
     *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
   esac],[debug=false])
AM_CONDITIONAL(DEBUG, test x$debug = xtrue)


# *** Add Disable Optimize Option for Configure
AC_ARG_ENABLE(optimize,
   AS_HELP_STRING([--disable-optimize], [Compile without Optimization]),
   [case "${enableval}" in
     yes) optimize=true ;;
     no)  optimize=false ;;
     *) AC_MSG_ERROR(bad value ${enableval} for --enable-optimize) ;;
   esac],[optimize=true])
AM_CONDITIONAL(OPTIMIZE, test x$optimize = xtrue)




# *** Checks for libraries.
# none
# *** Checks for header files.
# none

# *** Checks for typedefs, structures, and compiler characteristics.
# none
#AC_C_CONST
#AC_C_INLINE
#AC_TYPE_SIZE_T

# *** Check for known argp.h bug w/ -O and -pedantic in libc(6)-dev
# Define Test: Use C and provide the right options, change CXXFLAGS
AC_DEFUN([AC_C_ARGP_O_PEDANTIC],
[ AC_CACHE_CHECK( [whether argp.h works with -pedantic and -O ], [ac_cv_argp_o_pedantic],
[  AC_LANG_PUSH(C++)
  CXXFLAGS_org=$CXXFLAGS
  AC_SUBST(CXXFLAGS, "-pedantic -O")
  AC_COMPILE_IFELSE( AC_LANG_SOURCE( [[#include <argp.h>]] ),
   ac_cv_argp_o_pedantic=yes,
   ac_cv_argp_o_pedantic=no ) ] )
  AC_SUBST(CXXFLAGS, $CXXFLAGS_org)
  AC_LANG_POP(C++)
  AM_CONDITIONAL(ARGP_O_PEDANTIC, test x$ac_cv_argp_o_pedantic = xyes)
] )
# Execute Test
AC_C_ARGP_O_PEDANTIC


# *** Checks for library functions.
# none

# *** outputting files
# Place configuration items in this file
AC_CONFIG_HEADER([src/config.h])
# Automake Makefiles
AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile])


# Do output
AC_OUTPUT
