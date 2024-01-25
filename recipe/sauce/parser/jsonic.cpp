/*
ssc (static site checker)
File Info
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "parser/jsonic.h"

#ifndef NO_JSONIC
#include "main/context.h"

::std::string jsonic::rpt_base (const ::boost::json::value& val, const int indent)
{   ::std::string res;
    switch (val.kind ())
    {   case ::boost::json::kind::null :
            return res + "NULL\n";
        case ::boost::json::kind::bool_ :
            if (val.as_bool ()) return res + "true\n";
            return res + "false\n";
        case ::boost::json::kind::int64 :
            return res + ::boost::lexical_cast < ::std::string > (val.as_int64 ()) + "\n";
        case ::boost::json::kind::uint64 :
            return res + ::boost::lexical_cast < ::std::string > (val.as_uint64 ()) + "\n";
        case ::boost::json::kind::double_ :
            return res + ::boost::lexical_cast < ::std::string > (val.as_double ()) + "\n";
        case ::boost::json::kind::string :
            return res + quote (val.as_string ().c_str ()) + "\n";
        case ::boost::json::kind::array :
            res += "ARRAY\n";
            for (::boost::json::array::const_iterator i = val.as_array ().cbegin (); i != val.as_array ().cend (); ++i)
                res += rpt (*i, indent+1);
            break;
        case ::boost::json::kind::object :
            res += "OBJECT\n";
            for (::boost::json::object::const_iterator i = val.as_object ().cbegin (); i != val.as_object ().cend (); ++i)
            {   const int dent = indent + 1;
                res += ::std::string (dent*2, ' ');
                res += quote (i -> key_c_str ());
                res += ": ";
                res += rpt_base (i -> value (), dent); }
            break;
        default :
            return "*** UNDOCUMENTED TYPE ***\n"; }
    return res; }

bool jsonic::parse (nitpick& nits, const ::std::string& s, const e_charcode encoding)
{   if ((encoding != cc_utf8) && (encoding != cc_ansi))
        nits.pick (nit_jsonld_encoding, es_error, ec_json, "JSON-LD parsing requires ASCII, ANSI or UTF-8.");
    else try {
        ::boost::json::error_code jec;
        ::boost::json::parse_options po;
        po.allow_comments = true;
        po.allow_trailing_commas = true;
        po.allow_invalid_utf8 = (encoding == cc_utf8);
        value_ = ::boost::json::parse (s, jec, ::boost::json::storage_ptr (), po);
        if (jec) nits.pick (nit_json_error, es_error, ec_json, "JSON error: ", jec.message ());
        else
        {   if (context.tell (es_structure)) outstr.out (rpt (value_));
            return true; } }
    catch (const ::std::exception& x)
    {   nits.pick (nit_json_error, es_error, ec_json, "JSON exception: ", x.what ()); }
    catch (...)
    {   nits.pick (nit_json_error, es_error, ec_json, "unknown JSON exception"); }
    value_.emplace_null ();
    return false; }

#endif // NO_JSONIC
