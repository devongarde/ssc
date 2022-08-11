/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "main/output.h"
#include "main/context.h"
#include "parser/text.h"

output_streams_t outstr;

void output_streams_t::init (nitpick& nits, const ::std::string& s)
{   name_ = s;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> set (nm_general_output, s);
    fos_.reset (new ::std::ofstream (s));
    if (fos_ -> fail ())
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_init, "cannot open ", s, " for output.");
        fos_.reset (); } }

::std::string output_streams_t::ensane (const ::std::string& s) const
{   if (context.cgi ()) return enwotsit (s);
    return s; }
