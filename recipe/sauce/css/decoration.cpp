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
#include "css/decoration.h"
#include "type/type_enum.h"

void decoration::parse (nitpick& nits, arguments& args, const ::std::string& sep, const ::std::string& s)
{   if (sep.empty ())
        nits.pick (nit_css_syntax, ed_css_20, "5 Selectors", es_error, ec_css, quote (s), ": missing selector");
    else if (sep.length () != 1)
        nits.pick (nit_css_syntax, ed_css_20, "5 Selectors", es_error, ec_css, quote (s), ": a single selector expected");
    else switch (sep.at (0))
    {   case '.' :
            if (s.empty ())
                nits.pick (nit_css_syntax, ed_css_20, "5 Selectors", es_error, ec_css, quote (s), ": empty class");
            else sparkle_ = css_class (args, s); 
            break;
        case '#' :
            if (s.empty ())
                nits.pick (nit_css_syntax, ed_css_20, "5 Selectors", es_error, ec_css, quote (s), ": empty id");
            else sparkle_ = css_id (args, s); 
            break;
        case ':' :
            if (s.empty ())
                nits.pick (nit_css_syntax, ed_css_20, "5 Selectors", es_error, ec_css, quote (s), ": empty pseudo");
            else sparkle_ = css_fn (nits, args, s);
            break;
        case '[' :
            if (s.length () < 2)
                nits.pick (nit_css_syntax, ed_css_20, "5 Selectors", es_error, ec_css, quote (s), ": incomplete attribute decoration: [ is alone");
            else if (s.at (s.length () - 1) != ']')
                nits.pick (nit_css_syntax, ed_css_20, "5 Selectors", es_error, ec_css, quote (s), ": borked attribute decoration: missing ]");
            else
            {   ::std::string ssss (trim_the_lot_off (s.substr (0, s.length () - 1)));
                if (ssss.empty ())
                    nits.pick (nit_css_syntax, ed_css_20, "5 Selectors", es_error, ec_css, quote (s), ": empty attribute decoration; nothing inside []");
                else
                    sparkle_ = css_attribute (nits, args, ssss); }
            break;
        default :
            GRACEFUL_CRASH (__FILE__, __LINE__); } }

void decoration::accumulate (stats_t* s, const e_element e) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    switch (sparkle_.index ())
    {   case dt_unset :
            break;
        case dt_attribute :
            ssc_get < css_attribute > (sparkle_).accumulate (s, e);
            break;
        case dt_class :
            s -> dcl_class (ssc_get < css_class > (sparkle_).s_);
            s -> dcl_element_class (elem::name (e) + "." + ssc_get < css_class > (sparkle_).s_);
            break;
        case dt_fn :
            ssc_get < css_fn > (sparkle_).accumulate (s);
            break;
        case dt_id :
            s -> dcl_id (ssc_get < css_id > (sparkle_).s_);
            s -> dcl_element_id (elem::name (e) + "#" + ssc_get < css_id > (sparkle_).s_);
            break;
        default : GRACEFUL_CRASH (__FILE__, __LINE__); } }

::std::string decoration::rpt () const
{   if (! sparkle_.valueless_by_exception ())
        switch (static_cast < e_dec > (sparkle_.index ()))
        {   case dt_class : return ::std::get < css_class > (sparkle_).rpt (); 
            case dt_id : return ::std::get < css_id > (sparkle_).rpt (); 
            case dt_attribute : return ::std::get < css_attribute > (sparkle_).rpt (); 
            case dt_fn : return ::std::get < css_fn > (sparkle_).rpt ();
            case dt_unset : break;
            default : GRACEFUL_CRASH (__FILE__, __LINE__); break; }
    return ::std::string (); } 
