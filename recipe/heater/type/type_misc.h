/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

#pragma once
#include "type/type_master.h"
#include "parser/pattern.h"

template < > struct type_master < t_coords > : tidy_string < t_coords >
{   typedef vint_t value_type;
    value_type value_;
    type_master () = default;
    static e_animation_type animation_type () { return at_coordinate; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_coords > :: set_value (nits, v, s);
        if (tidy_string < t_coords > :: empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "COORDS cannot be empty");
            string_value < t_coords > :: status (s_invalid); }
        else
        {   vstr_t coords (split_by_charset (tidy_string < t_coords > :: get_string (), ","));
            ::std::size_t csz = coords.size ();
            if (csz < 3)
                nits.pick (nit_bad_coords, es_error, ec_attribute, "COORDS is too short");
            else if ((csz > 4) && (csz % 2 != 0))
                nits.pick (nit_bad_coords, es_error, ec_attribute, "COORDS has an odd number of values");
            else
            {   bool whoops = false;
                ::std::string okch (DENARY "-");
                if (v < html_5_0) okch += "%";
#ifndef FUDDYDUDDY
                value_.reserve (csz);
#endif // FUDDYDUDDY
                for (auto c : coords)
                    if (c.find_first_not_of (okch) != ::std::string::npos)
                    {   nits.pick (nit_bad_coords, es_error, ec_attribute, quote (c), " is not a valid value");
                        whoops = true; }
                    else value_.push_back (lexical < int > :: cast (c));
                if (! whoops)
                    switch (csz)
                    {   case 3 :
                            if (value_.at (2) < 0)
                            {   nits.pick (nit_bad_coords, es_error, ec_attribute, "the radius of a circle cannot be negative");
                                whoops = true; }
                            break;
                        case 4 :
                            if ((value_.at (0) >= value_.at (2)) || (value_.at (1) >= value_.at (3)))
                            {   nits.pick (nit_bad_coords, es_error, ec_attribute, "the x and y values of a rectangle's first coordinate must be less than those of the second");
                                whoops = true; }
                            break; }
                if (! whoops) return; }
                tidy_string < t_coords > :: status (s_invalid); } }
    static vint_t default_value () { return vint_t (); }
    vint_t get () const { return value_; } };

template < > struct type_master < t_font_family > : tidy_string < t_font_family >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_font_family > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_font_family > :: get_string ();
        if (tidy_string < t_font_family > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a font name or font family is expected");
        else if (tidy_string < t_font_family > :: good ())
        {   nitpick knots;
            if (test_value < t_fontname > (knots, v, ss)) nits.merge (knots);
            else nits.pick (nit_fontname, es_info, ec_type, quote (ss), " is not a font " PROG " recognises; some browsers may substitute another");
            return; }
        tidy_string < t_font_family > :: status (s_invalid); } };

template < > struct type_master < t_imgsizes > : tidy_string < t_imgsizes >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_imgsizes > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_imgsizes > :: get_string ();
        if (tidy_string < t_imgsizes > :: empty ())
        {   nits.pick (nit_nuts, es_error, ec_type, "SIZES cannot be empty");
            tidy_string < t_imgsizes > :: status (s_invalid); }
        else if (tidy_string < t_imgsizes > :: good ())
            if (! compare_complain (nits, v, "any", ss))
            {   vstr_t vs (split_by_charset (ss, ","));
                for (auto sss : vs)
                {   vstr_t srcsz (split_by_space (sss));
                    ::std::string& ssz (srcsz.at (srcsz.size () - 1));
                    PRESUME (! ssz.empty (), __FILE__, __LINE__);
                    if (ssz.at (ssz.length () - 1) != ')')
                        if (    (ssz.length () < 3) ||
                                (! compare_no_case (ssz.substr (ssz.length () - 2), "vw")) ||
                                (ssz.substr (0, ssz.length () - 2).find_first_not_of (POSITIVE) != ::std::string::npos))
                            {   ::std::string::size_type pos = ssz.find_last_of (POSITIVE);
                                if (pos == ::std::string::npos)
                                    tidy_string < t_imgsizes > :: status (s_invalid);
                                else if (pos != ssz.length () - 1)
                                    if (! test_value < t_length > (nits, v, ssz.substr (++pos)))
                                    {   tidy_string < t_imgsizes > :: status (s_invalid);
                                        break; } } } } } };

template < > struct type_master < t_is > : tidy_string < t_is >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_is > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_is > :: get_string ();
        if (tidy_string < t_is > :: empty ())
        {   nits.pick (nit_nuts, es_error, ec_type, "IS expects the name of a custom element");
            tidy_string < t_is > :: status (s_invalid); }
        else if (tidy_string < t_is > :: good ())
        {   vstr_t ce (context.custom_elements ());
            if (ce.empty ())
                nits.pick ( nit_nuts, ed_apr21, "4.13.3 Core concepts", es_info, ec_type,
                            "no customised built-in elements are defined, so ", quote (ss), " cannot be verified (see the  --" GENERAL CUSTOM " switch, '" PROG " --" HELP " for gen')");
            else if (! is_one_of (ss, ce))
            {   nits.pick ( nit_nuts, ed_apr21, "4.13.3 Core concepts", es_warning, ec_type,
                            quote (ss), " is not specified as a customised built-in element (see the --" GENERAL CUSTOM " switch, '" PROG " --" HELP " for gen')");
                tidy_string < t_is > :: status (s_invalid); } } } };

template < > struct type_master < t_key > : string_vector < t_key, sz_space >
{   bool tested_ = false, predefined_ = false;
    type_master () = default;
    void swap (type_master < t_key >& t) NOEXCEPT
    {   ::std::swap (tested_, t.tested_);
        ::std::swap (predefined_, t.predefined_);
        string_vector < t_key, sz_space > :: swap (t); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_key, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_key, sz_space > :: empty ())
            nits.pick (nit_key, es_error, ec_type, "a key cannot be empty");
        else if (string_vector < t_key, sz_space > :: good ())
            if (v.is_5 ())
            {   sstr_t check;
                for (auto k : string_vector < t_key, sz_space > :: get ())
                    if (k.length () != 1)
                        nits.pick (nit_key, ed_41, "17.11.2 Access keys", es_error, ec_type, quote (k), " is not a single character");
                    else if (check.find (k) != check.cend ())
                        nits.pick (nit_key, ed_jul20, "6.6.2 The accesskey attribute", es_error, ec_type, "access keys must be unique, yet ", quote (k), " is repeated");
                    else check.insert (k);
                if (string_vector < t_key, sz_space > :: size () == check.size ()) return; }
            else if ((s.length () == 1) || (! ::std::iswspace (s.at (0)) && ! ::std::iswcntrl (s.at (0)))) return;
            else nits.pick (nit_single_character, ed_41, "17.11.2 Access keys", es_error, ec_type, quote (tidy_string < t_key > :: get_string ()), " is not a single character (which cannot be a space)");
        string_vector < t_key, sz_space > :: status (s_invalid); }
   bool invalid_access (nitpick& nits, const html_version& , sstr_t* keys)
   {    VERIFY_NOT_NULL (keys, __FILE__, __LINE__);
        if (! good ()) return false;
        if (! tested_)
        {   for (auto k : string_vector < t_key, sz_space > :: get ())
            {   predefined_ = (keys -> find (k) != keys -> cend ());
                if (! predefined_) keys -> insert (k);
                else
                {   nits.pick (nit_key, ed_41, "17.11.2 Access keys", es_error, ec_type, "access key ", quote (k), " is used elsewhere");
                    tidy_string < t_key > :: status (s_invalid);
                    break; } }
            tested_ = true; }
        return predefined_; } };

template < > struct type_master < t_q > : public tidy_string < t_q >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   tidy_string < t_q > :: set_value (nits, v, ss);
        const ::std::string& s = tidy_string < t_q > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "value required");
            tidy_string < t_q > :: status (s_invalid); }
        else if (good ())
        {   if ((s.length () >= 3) && (s.length () <= 7))
                if ((s.at (0) == 'q') || (s.at (0) == 'Q'))
                    if (s.at (1) == '=')
                    {   if (s.at (2) == '1')
                        {   if (s.length () == 3) return;
                            if (s.at (3) == '.')
                                if (s.length () > 4)
                                    if (s.substr (4).find_first_not_of ("0") == ::std::string::npos) return; }
                        else if (s.at (2) == '0')
                        {   if (s.length () == 3) return;
                            if (s.at (3) == '.')
                                if (s.length () > 4)
                                    if (s.substr (4).find_first_not_of (DENARY) == ::std::string::npos) return; }
                        nits.pick (nit_bad_q, ed_rfc_7231, "5.3.1. Quality Values", es_error, ec_type, quote (s), " weight is 'q=' with a value between 0.000 and 1.0"); } }
        tidy_string < t_q > :: status (s_invalid); } };

template < > struct type_master < t_regex > : public tidy_string < t_regex >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_regex > :: set_value (nits, v, s);
        if (tidy_string < t_regex > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "PATTERN requires a regular expression");
        else if (verify_pattern (nits, v, tidy_string < t_regex > :: get_string ())) return;
        string_value < t_regex > :: status (s_invalid); } };

template < > struct type_master < t_sym > : public tidy_string < t_sym >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   extern void examine_character_code (const html_version& v, const ::std::string& text, bool& known, bool& invalid);
        tidy_string < t_sym > :: set_value (nits, v, ss);
        const ::std::string& s = tidy_string < t_sym > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "SYM requires a value");
            tidy_string < t_sym > :: status (s_invalid); }
        else if (good ())
        {   if (s.at (0) == '&')
                nits.pick (nit_unrecognised_character_code, es_error, ec_type, quote (s), " is not a standard character code (do not include the ampersand)");
            else
            {   bool known = false, invalid = false;
                examine_character_code (v, s, known, invalid);
                if (! known) nits.pick (nit_unrecognised_character_code, es_error, ec_type, quote (s), " is not a standard character code");
                else if (invalid)  nits.pick (nit_invalid_character_code, es_error, ec_type, quote (s), " is not valid in ", v.report ());
                else return; }
            tidy_string < t_sym > :: status (s_invalid); } } };

template < > struct type_master < t_target > : public tidy_string < t_target >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_target > :: set_value (nits, v, s);
        const ::std::string& val = tidy_string < t_target > :: get_string ();
        if (tidy_string < t_target > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "TARGET requires a value");
        else
        {   if (val [0] != '_') return;
            if ((v.svg_version () >= sv_1_1) && (val == "_replace")) return;
            if ((val == "_blank") || (val == "_self") || (val == "_parent") || (val == "_top")) return;
            nits.pick (nit_badtarget, es_error, ec_type, quote (s), " starts with '_', but is not a standard target"); }
        string_value < t_target > :: status (s_invalid); } };

template < > struct type_master < t_xlinktype > : type_must_be < t_xlinktype, sz_simple > { };
