/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "type/type_enum.h"
#include "css/property.h"
#include "css/arguments.h"

void property::parse (nitpick& nits, arguments& args, const ::std::string& s)
{   const ::std::string::size_type pos = s.find (':');
    if (pos == ::std::string::npos)
        nits.pick (nit_css_syntax, es_error, ec_css, quote (s), ": expecting to find PROPERTY : VALUE");
    else
    {   ::std::string name (trim_the_lot_off (s.substr (0, pos)));
        ::std::string value (trim_the_lot_off (s.substr (pos+1)));
        if (name.empty ())
            nits.pick (nit_css_syntax, es_error, ec_css, quote (s), ": missing property name");
        else if (value.empty ())
            nits.pick (nit_css_syntax, es_error, ec_css, quote (s), ": missing property value");
        else
        {   vstr_t vw (uq2 (value, UQ_DQ | UQ_SQ | UQ_BS | UQ_TRIM, "!"));
            PRESUME (vw.size () > 0, __FILE__, __LINE__);
            if (vw.size () > 1)
            {   if (vw.size () > 2) nits.pick (nit_css_syntax, es_error, ec_css, quote (s), ": too many weights ('!')");
                w_.parse (nits, args, vw.at (1)); } 
            prop_ = make_property_v_ptr (nits, args.v_, name, vw.at (0)); 
            if (prop_.get () == nullptr)
                nits.pick (nit_css_syntax, es_error, ec_css, "Unknown property ", quote (name)); } } }

void property::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    if (prop_.get () != nullptr)
    {   s -> mark (prop_ -> get ());
        prop_ -> accumulate (s); }
    w_.accumulate (s); }

::std::string property::rpt () const
{   if (prop_.get () == nullptr) return ::std::string ();
    return prop_ -> rpt (); }  
