#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
# Copyright (C) 2005 Robert Lange <robert.lange@s1999.tu-chemnitz.de>
# last Modification: $LastChangedDate$


# *** Initialization
# Autoconf
AC_INIT(HTML Include, 0.10.1devel, robert.lange@s1999.tu-chemnitz.de, htinc)
# where to put and find the temporary configuration files
AC_CONFIG_AUX_DIR(config)
# Autoconf Version not below:
AC_PREREQ(2.59)
# Automake: create distribution with bzip2, no GNU program
AM_INIT_AUTOMAKE(dist-bzip2 no-dist-gzip foreign)

# *** Some Configurations
# some file that is in the package's source directory
AC_CONFIG_SRCDIR(src/examine.h)
# set CXXFLAGS for C++ compiler manually (to avoid debug switch -g)
# all warnings enabled
AC_SUBST(CXXFLAGS, "-Wall -pedantic -ansi")

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




# Checks for libraries.
# none
# Checks for header files.
# none
# *** Checks for typedefs, structures, and compiler characteristics.
# none
#AC_C_CONST
#AC_C_INLINE
#AC_TYPE_SIZE_T
# *** Checks for library functions.
# none

# *** outputting files
# place configuration items in this file
AC_CONFIG_HEADER([src/config.h])
# automake Makefiles
AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile])

# do output
AC_OUTPUT
