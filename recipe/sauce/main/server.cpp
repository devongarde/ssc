/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence,  or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "main/context.h"
#include "main/server.h"
#include "base/type_master.h"
#include "type/type.h"
#include "utility/filesystem.h"

/*
Commands:
a
b
c       configure
d
e
f
g
h       help
i
j
k
l
m
n
o
p       print
q       quit
r       run
s
t
u
v       version
w
x
y
z

QUIT            Dance around the nearest ash tree without any clothes on
RUN             Run using the current configuration
PRINT           Show the current configuration
CONFIGURATION   A configuration follows. The configuration consists of lines of text terminated by a single dot on a line by itself.
  ...
.

Replies:
OK              All good
FAIL message    Something went wrong. That something is described by the message.
OUTPUT          Here is the output of a run, following by a dot line to indicate that's all folks.
  ...
.
HELP            this info, basically
*/

server_t server;

void server_t::init (nitpick& ) { }
void server_t::reinit () { }
void server_t::teardown () { }

int server_t::help ()
{   outstr.console ("c   configure: enter a series of " PROG " command line options,\n"
                    "    then a full stop on a line by itself\n"
                    "C   clear the current configuration\n"
                    "h   this text\n"
                    "p   print the current configuration\n"
                    "q   quit\n"
                    "r   run using the current configuration\n");
    return NOTHING_TO_DO; }

int server_t::print ()
{   outstr.console (o_ + "\n");
    return NOTHING_TO_DO; }

int server_t::run ()
{   if (o_.empty ()) return NOTHING_TO_DO; 
    return VALID_RESULT; }

const vstr_t server_t::cmd () const
{   const vstr_t sep = { " ", "\n" };
    return uq2 (o_, UQ_TRIM | UQ_SQ | UQ_DQ | UQ_BS | UQ_REPEATQ | UQ_UNIFY, sep); }

int server_t::process_and_progress ()
{   ::std::string s;
    int res = NOTHING_TO_DO;
    try
    {   if (! conf_) outstr.console ("\n" PROG " >> ");
        if (! ::std::getline (::std::cin, s)) return STOP_NOW; }
    catch (...)
    {   return STOP_NOW; }
    ::std::string t (trim_the_lot_off (s));
    if (! t.empty ())
        if (conf_)
            if ((t.length () == 1) && (t.at (0) == '.')) conf_ = false;
            else o_ += t + "\n";
        else switch (t.at (0))
        {   case 'C' : o_.clear (); break;
            case 'c' : conf_ = true; break;
            case '?' :
            case 'h' : res = help (); break;
            case 'p' : res = print (); break;
            case 'q' : res = STOP_NOW; break;
            case 'r' : res = run (); break;
            default : outstr.console ("Unknown command; type h for help.\n"); }
    return res; }
