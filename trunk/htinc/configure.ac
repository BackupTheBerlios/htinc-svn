#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


# *** Initialization
# Autoconf
AC_INIT(HTML Include, 0.10DEVEL, robert.lange@s1999.tu-chemnitz.de , htinc)
# where to put and find the temporary configuration files
AC_CONFIG_AUX_DIR(config)
# Autoconf Version not below:
AC_PREREQ(2.59)
# Automake
AM_INIT_AUTOMAKE

# *** Some Configurations
# some file that is in the package's source directory
AC_CONFIG_SRCDIR(src/examine.h)
# set CXXFLAGS for C++ compiler manually (to avoid debug switch -g)
AC_SUBST(CXXFLAGS, -O2)

# *** Checks for programs.
# C++ Compiler
AC_PROG_CXX
# Install Program
AC_PROG_INSTALL

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


# *** outputting files
# place configuration items in this file
AC_CONFIG_HEADER([src/config.h])
# automake Makefiles
AC_CONFIG_FILES([Makefile src/Makefile])

# do output
AC_OUTPUT
