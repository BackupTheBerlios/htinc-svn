#!/usr/bin/perl
# File name: ''update_includes.pl''
# Function:
#   Call HTML Include for files which are marked as "modified"
#   by Subversion. The base directory is the current directory,
#   which must be an Subversion branch.
#   By default includes are searched unter "include/" - modify
#   the program call to change this.
#
#      created: 24.02.2k5
#  (c) by Robert Lange (robert.lange@s1999.tu-chemnitz.de)
#  Licensed under the GNU General Public License

# *** packes to use ***
use strict;
use warnings;

# *** subroutine declarations ***
# main routine without any arguments
sub main ();

# *** "body" of the program ***
main();


# *** main routine ***
sub main() {

  # get files from svn stat
  # But only with html in text
  # And only consider Modified or Added file
  my @vars = grep(/^[MA].*html/, split("\n", `svn stat`) );

  # Complain when files which match "mosfat" are modified
  # ---> Uncomment and adjust when you want to use this
  #  die "Mosfat is considered being static! Cannot update this!"
  #    if grep (/mosfat/, @vars);

  foreach (@vars) {
    /^.{7}(.+)$/;  # weed status message
    print "htinc -i include $1\n";
    # Call HTML Include - Change parameters here
    system ("htinc -i include $1") == 0
      or die "Call failed: $?";

  }

  # exit without error
  exit 0;
}
