// CMDARGS.H
// -----------------------------------------------------------------------------
// Copyright (C) 2002 Jan Langer, All Rights Reserved
// -----------------------------------------------------------------------------
// Permission to use, copy, modify, distribute and sell this software for any
// purpose is hereby granted without fee, provided that the above copyright
// notice appears in all copies and that both that copyright notice and this
// permission notice appear in supporting documentation. The author makes no
// representations about the suitability of this software for any purpose. It is
// provided as is without express or implied warranty.
// -----------------------------------------------------------------------------
// last Modified: 26.05.2k2 (by Robert Lange)

#ifndef CMDARGS_H
#define CMDARGS_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

namespace tools 
{
  
  // ------------------------------------------------------
  // class for parsing command line options
 	
  class cmd_args 
  {
      typedef std::vector <std::string> string_list;
      typedef std::pair <std::string, std::string> argument;
      typedef std::vector <std::pair <std::string, std::string> > argument_list;

      static const string_list::size_type inf = 9999; // very high number (infinity)  

      class option 
      {
       public:
          std::string long_str;
          std::string short_str;
          std::size_t arg_count;
          
          bool flag;
          string_list args;
          
          option (
              std::string const &l, 
              std::string const &s, 
              std::size_t const &a)

              : long_str (l), short_str (s), 
                arg_count (a), flag (false) 
          {}
      };

      typedef std::vector <option> option_list;

      option_list opts_;
      string_list args_;

      int find_short (std::string const &s) const 
      {
          typedef option_list::const_iterator Ci;
          for (Ci i = opts_.begin (); i != opts_.end (); ++i)
          {
              if (i->short_str == s)
              {
                return std::distance (opts_.begin (), i);
              }
          }
          return -1;
      }
      int find_long (std::string const &l) const 
      {
          typedef option_list::const_iterator Ci;
          for (Ci i = opts_.begin (); i != opts_.end (); ++i)
          {
              if (i->long_str == l)
              {
                return std::distance (opts_.begin (), i);
              }
          }
          return -1;
      }
   
   public:
      // --------------------------------------------------
      // init
      
      void add_option (
          std::string const &l,      // long option
          std::string const &s,      // short option
          std::size_t const &a = 0)  // no of arguments    
      {
          opts_.push_back (option (l, s, a));
      }

      // --------------------------------------------------
      // parse

      bool parse (std::size_t argc, char *argv []) 
      {
          std::size_t i = 0;

          while (++i < argc) 
          {
              int o = find_short (argv [i]);
              if (o == -1) 
              {
                o = find_long (argv [i]);
              }

              if (o != -1) 
              {
		option &ro = opts_ [o];
		if (ro.flag == true)
		{ 
	          return false;         // fount option twice
		}
                ro.flag = true;
                std::size_t b = i++;
                for (; i < argc && i - b <= ro.arg_count; ++i)
                {
                    ro.args.push_back (argv [i]);
                }
                if (i - b <= ro.arg_count && ro.arg_count != inf)
                {
                  return false;
                }
                --i;
              }
              else
              {
                args_.push_back (argv [i]);
              }
          }
          return true;
      }

      // --------------------------------------------------
      // getter

      std::size_t count () const 
      {
          return args_.size ();
      }

      std::string arg (std::size_t const &p) const 
      {
          return (p < args_.size () && p >= 0)
                  ? args_ [p]
                  : std::string ();
      }

      bool is_option (std::string const &o) const 
      {
          int p = find_short (o);
          if (p == - 1)
          {
            p = find_long (o);
          }
          return (p != -1) ? opts_ [p].flag : false;
      }

      std::string option_arg 
          (std::string const &o, std::size_t const &p = 0) const 
      {
          int s = find_short (o);
          if (s == - 1)
          {
            s = find_long (o);
          }
          if (s == -1) 
          {
            return std::string ();
          }
          if (opts_ [s].flag && p < opts_ [s].args.size () && p >= 0)
          {
            return opts_ [s].args [p];	
          }
          return std::string ();
      }
  };

  // ------------------------------------------------------
  
} // namespace tools

#endif // CMDARGS_H
