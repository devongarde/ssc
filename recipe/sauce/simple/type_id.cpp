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
#include "type/type.h"
#include "element/element.h"
#include "webpage/page.h"

bool note_id_usage (element* p, const ::std::string& s)
{   VERIFY_NOT_NULL (p, __FILE__, __LINE__);
    return p -> get_page ().css ().note_id (p -> id ().get (), s); }

e_status set_id_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "an ID cannot be empty");
    else
    {   bool res = true;
        if (note_id_usage (box, s))
            nits.pick (nit_spotted_id, es_comment, ec_css, "CSS id ", quote (s), " recognised");
        switch (v.mjr ())
        {   case 3 :
                if (v.mnr () == 2)
                {   if (::std::string (ALPHABET).find (s.at (0)) == ::std::string::npos)
                    {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " does not start with a letter");
                        res = false; } }
                break;
            case 4 :
                if (::std::string (ALPHABET).find (s.at (0)) == ::std::string::npos)
                {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " does not start with a letter");
                    res = false; }
                else if (s.find_first_not_of (IDS) != ::std::string::npos)
                {   nits.pick (nit_bad_id, ed_4, "6.2 SGML basic types", es_error, ec_type, quote (s), " may only contain letters, digits, '-', '_', ':', and '.'");
                    res = false; }
                break;
            case 5 :
                if (find_if (s.cbegin (), s.cend (), ::std::iswspace) != s.cend ())
                {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " may not contain a space");
                    res = false;; }
                break;
            default : break; }
        if (res) return s_good; }
    return s_invalid; }

e_status set_idref_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "an id cannot be empty");
    else if (::std::find_if (s.cbegin (), s.cend (), ::std::iswspace) == s.cend ())
        return s_good;
    else nits.pick (nit_bad_id, es_error, ec_type, quote (s), " contains a space");
    return s_invalid; }

e_status set_uid_value (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.empty ()) return s_empty;
    const ::std::string::size_type pos = s.find (':');
    if (pos == ::std::string::npos)
    {   if (s.find_first_not_of (HEX "-") == ::std::string::npos) return s_good; }
    else if ((pos > 0) && (pos < (s.length () - 1)))
    {   if ((pos != 3) || ! compare_no_case ("UID", s.substr (0, 3))) return s_good;
        if (s.substr (pos+1).find_first_not_of (HEX "-") == ::std::string::npos) return s_good; }
    nits.pick (nit_bad_uid, es_warning, ec_type, "expecting 'UID:' followed by a long hexadecimal number");
    return s_invalid; }
