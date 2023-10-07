/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "stats/stats.h"

void mark_font (stats_t* s, const ::std::string& font)
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    s -> mark_font (font); }

bool set_arxiv_value (nitpick& nits, const html_version& , const ::std::string& s)
{   const ::std::size_t len = s.length ();
    bool oops = true;
    if ((len > 6) && compare_no_case (s.substr (0, 6), "arxiv:"))
        if ((s.size () == 15) || (s.size () == 16))
            if (GSL_AT (s, 11) == '.')
                if (s.substr (7).find_first_not_of (DENARY ".") == ::std::string::npos)
                {   bool ok = true;
                    if (((s.at (9) == '0') && (s.at (10) == '0')) || ((s.at (9) == '1') && (s.at (10) > '2')) || (s.at (9) > '1'))
                    {   nits.pick (nit_arxiv, es_error, ec_type, "months are numbered between '01' and '12' inclusive");
                        ok = false; }
                    if (((s.at (7) == '0') || ((s.at (7) == '1') && (s.at (8) <= '4'))) && (s.length () != 15))
                    {   nits.pick (nit_arxiv, es_error, ec_type, "arXiv identifiers between 2007 to 2014 have 15 characters");
                        ok = false; }
                    if (((s.at (7) > '1') || ((s.at (7) == '1') && (s.at (8) > '4'))) && (s.length () != 16))
                    {   nits.pick (nit_arxiv, es_error, ec_type, "arXiv identifiers after 2015 have 16 characters");
                        ok = false; }
                    if (ok) return true;
                    oops = false; }
    else if (len > 8)
    {   const ::std::string::size_type slash = s.find ('/');
        if (slash == len - 8)
        {   const ::std::string::size_type Yy = slash+1;
            const ::std::string::size_type yY = slash+2;
            const ::std::string::size_type Mm = slash+3;
            const ::std::string::size_type mM = slash+4;
            if (s.substr (slash+1).find_first_not_of (DENARY) == ::std::string::npos)
            {   if (((s.at (Yy) < '9') && (s.at (yY) == '0')) && ((s.at (Yy) != '0') || (s.at (yY) > '3')))
                    nits.pick (nit_arxiv, es_error, ec_type, "years in early arXiv identifiers lie between '91' and '03'");
                else if (((s.at (Mm) != '0') || (s.at (mM) == '0')) && ((s.at (Mm) != '1') || (s.at (mM) > '2')))
                    nits.pick (nit_arxiv, es_error, ec_type, "months are numbered between '01' and '12' inclusive");
                else return true;
                oops = false; } } }
    if (oops)
        nits.pick (nit_arxiv, es_error, ec_type, "expecting \"ARCHIVE/YYMMNNN\",  \"ARCHIVE.CLASS/YYMMNNN\", \"arXiv:YYMM.NNNN\", or \"arXiv:YYMM.NNNNN\", where YY is year, MM is month, and N... are digits");
    return false; }

// set_cookie_value
e_status set_cookie_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
       nits.pick (nit_empty, es_error, ec_type, "cookie value required");
    else
    {   const ::std::string::size_type pos = s.find ('=');
        nitpick nuts;
        if (pos == ::std::string::npos)
            switch (examine_value < t_cookieid > (nuts, v, s))
            {   case coo_secure :
                case coo_httponly :
                    return s_good;
                default :
                    nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_comment, ec_type, quote (s), " is unknown to " PROG);
                    return s_good; }
        if (pos > 0)
        {   ::std::string id (s.substr (0, pos));
            ::std::string arg (s.substr (pos+1));
            if (! test_value < t_cookieid > (nuts, v, id))
            {   nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_comment, ec_type, quote (s), " is unknown to " PROG " here");
                return s_good; }
            switch (examine_value < t_cookieid > (nuts, v, id))
            {   case coo_expires :
                    if (! test_value < t_datetime > (nuts, v, arg))
                        nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_warning, ec_type, quote (arg), " may not be a valid date");
                    return s_good;
                case coo_maxage :
                    if (arg.find_first_not_of (DENARY) == ::std::string::npos) return s_good;
                    nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_error, ec_type, quote (arg), " is not an integer");
                    break;
                case coo_domain :
                    if (arg.find_first_not_of (ALPHABET DENARY "-.") == ::std::string::npos) return s_good;
                    nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_error, ec_type, quote (arg), " is an invalid domain");
                    break;
                case coo_path :
                    if (arg.find_first_of (";") == ::std::string::npos) return s_good;
                    nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_error, ec_type, quote (arg), " is an invalid path");
                    break;
                case coo_secure :
                case coo_httponly :
                    nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_error, ec_type, id, " takes no argument");
                    break;
                default :
                    PRESUME (false, __FILE__, __LINE__); // should not get here; unexpected cookie type
                    nits.pick (nit_internal_parsing_error, ed_rfc_6265, "4.1.1. Syntax", es_warning, ec_type, quote (arg), " is unexpected and unverified");
                    break; } } }
    return s_invalid; }

bool set_coords_value (nitpick& nits, const html_version& v, const ::std::string& s, vint_t& val)
{   vstr_t coords (split_by_charset (s, ","));
    const ::std::size_t csz = coords.size ();
    if (csz < 3)
        nits.pick (nit_bad_coords, es_error, ec_attribute, "COORDS is too short");
    else if ((csz > 4) && (csz % 2 != 0))
        nits.pick (nit_bad_coords, es_error, ec_attribute, "COORDS has an odd number of values");
    else
    {   bool whoops = false;
        ::std::string okch (DENARY "-");
        if (v < html_5_0) okch += "%";
#ifndef FUDDYDUDDY
        val.reserve (csz);
#endif // FUDDYDUDDY
        for (auto c : coords)
        {   const ::std::string ss (trim_the_lot_off (c));
            if (ss.find_first_not_of (okch) != ::std::string::npos)
            {   nits.pick (nit_bad_coords, es_error, ec_attribute, quote (ss), " is not a valid value");
                whoops = true; }
            else val.push_back (lexical < int > :: cast (ss)); }
        if (! whoops)
            switch (csz)
            {   case 3 :
                    if (val.at (2) < 0)
                    {   nits.pick (nit_bad_coords, es_error, ec_attribute, "the radius of a circle cannot be negative");
                        whoops = true; }
                    break;
                case 4 :
                    if ((val.at (0) >= val.at (2)) || (val.at (1) >= val.at (3)))
                    {   nits.pick (nit_bad_coords, es_error, ec_attribute, "the x and y values of a rectangle's first coordinate must be less than those of the second");
                        whoops = true; }
                    break;
                default : break; }
        if (! whoops) return true; }
    return false; }

bool set_imgsizes_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   bool good = true;
    if (compare_complain (nits, v, "any", s)) return true;
    vstr_t vs (split_by_charset (s, ","));
    for (auto sss : vs)
    {   vstr_t srcsz (split_by_space (sss));
        ::std::string& ssz (srcsz.at (srcsz.size () - 1));
        if (! ssz.empty ())
            if (ssz.at (ssz.length () - 1) != ')')
                if (    (ssz.length () < 3) ||
                        (! compare_no_case (ssz.substr (ssz.length () - 2), "vw")) ||
                        (ssz.substr (0, ssz.length () - 2).find_first_not_of (POSITIVE) != ::std::string::npos))
                    {   ::std::string::size_type pos = ssz.find_last_of (POSITIVE);
                        if (pos == ::std::string::npos) good = false;
                        else if (pos != ssz.length () - 1)
                            if (! test_value < t_length > (nits, v, ssz.substr (++pos)))
                                return false; } }
    return good; }
