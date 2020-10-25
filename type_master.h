/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "type_core.h"
#include "symbol.h"
#include "quote.h"
#include "parse_elements.h"
#include "args.h"
#include "microdata_itemid.h"

class element;
bool invalid_id_result (nitpick& nits, const html_version& v, const ::std::string& s, element* e);
bool parse_d (nitpick& nits, const html_version& v, const ::std::string& d);
bool parse_paint (nitpick& nits, const html_version& v, const ::std::string& d, bool recheck = false);
bool parse_transform (nitpick& nits, const html_version& v, const ::std::string& d);
bool test_animation_timing (nitpick& nits, const html_version& v, const ::std::string& d, const bool begin);

template < e_type TYPE > class type_master : public string_value < TYPE > { };

template < > struct type_master < t_attributename > : tidy_string < t_attributename >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_attributename > :: set_value (nits, v, s);
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "ATTRIBUTENAME should have a name");
            string_value < t_attributename > :: status (s_invalid); }
        else
        {   e_attribute ea = attr :: find (tidy_string < t_attributename > :: get_string ());
            if (ea != a_unknown) return;
            nits.pick (nit_empty, es_warning, ec_type, quote (tidy_string < t_attributename > :: get_string ()), " is an unrecognised ATTRIBUTENAME");
            tidy_string < t_attributename > :: status (s_invalid); } } };

template < > struct type_master < t_beginvaluelist > : tidy_string < t_beginvaluelist >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_beginvaluelist > :: set_value (nits, v, s);
        bool good = true;
        if (tidy_string < t_beginvaluelist > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a comma separated list of animation timings is expected");
        else if (tidy_string < t_beginvaluelist > :: good ())
        {   vstr_t ve (split_by_charset (tidy_string < t_beginvaluelist > :: get_string (), ";"));
            if (ve.empty ())
                nits.pick (nit_empty, es_error, ec_type, "a comma separated list of animation timings is expected");
            else for (auto sss : ve)
                if (! test_animation_timing (nits, v, sss, true)) good = false;
            if (good) return; }
        tidy_string < t_beginvaluelist > :: status (s_invalid); } };

template < > struct type_master < t_compact > : tidy_string < t_compact >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_compact > :: set_value (nits, v, s);
        if (s.empty ())
        {   string_value < t_compact > :: status (s_good); return; }
        if (v.major () == 1)
        {   string_value < t_compact > :: status (s_invalid);
            nits.pick (nit_bad_compact, es_error, ec_type, "in ", v.report (), ", compact has no value"); }
        if (! compare_no_case (string_value < t_compact > :: get_string (), "compact"))
        {   string_value < t_compact > :: status (s_invalid);
            nits.pick (nit_bad_border, es_error, ec_type, "if compact is given a value, it must be \"compact\""); } } };

template < > struct type_master < t_char > : string_value < t_char >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string val (trim_the_lot_off (s));
        if (s.length () == 1) string_value < t_char > :: set_value (nits, v, s);
        else
        {   nits.pick (nit_single_character, es_error, ec_type, quote(s), " is not a single character");
            string_value < t_char > :: status (s_invalid); } } };

template < > struct type_master < t_coords > : tidy_string < t_coords >
{   typedef vint_t value_type;
    value_type value_;
    type_master () = default;
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

template < > struct type_master < t_d > : tidy_string < t_d >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_d > :: set_value (nits, v, s);
        if (tidy_string < t_d > :: empty ())
            nits.pick (nit_path_spec, ed_svg_1_0, "11.2.1 General information about path data", es_error, ec_type, "a D attribute cannot be empty");
        else if (tidy_string < t_d > :: good ())
            if (parse_d (nits, v, tidy_string < t_d > :: get_string ())) return;
        tidy_string < t_d > :: status (s_invalid); } };

template < > struct type_master < t_email > : tidy_string < t_email >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_email > :: set_value (nits, v, s);
        if (string_value < t_email > :: empty ())
            nits.pick (nit_bad_email, es_error, ec_type, "an email address is expected");
        else if (string_value < t_email > :: good ())
        {   url u (nits, v, tidy_string < t_email > :: get_string (), pr_mailto);
            if (! u.invalid ())
                if (! u.has_protocol () || (u.get_protocol () == pr_mailto)) return;
                else nits.pick (nit_bad_email, es_error, ec_type, quote (tidy_string < t_email > :: get_string ()), "is not an email address"); }
    string_value < t_email > :: status (s_invalid); } };

template < > struct type_master < t_emails > : tidy_string < t_emails >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_emails > :: set_value (nits, v, s);
        bool good = true;
        if (tidy_string < t_emails > :: empty ())
            nits.pick (nit_nuts, es_error, ec_type, "a comma separated list of email address is expected");
        else if (tidy_string < t_emails > :: good ())
        {   vstr_t ve (split_by_charset (tidy_string < t_emails > :: get_string (), ","));
            if (ve.empty ())
                nits.pick (nit_bad_email, es_error, ec_type, "a comma separated list of email address is expected");
            else for (auto sss : ve)
            {   type_master < t_email > e;
                e.set_value (nits, v, sss);
                if (! e.good ()) good = false; }
            if (good) return; }
        tidy_string < t_emails > :: status (s_invalid); } };

template < > struct type_master < t_endvaluelist > : tidy_string < t_endvaluelist >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_endvaluelist > :: set_value (nits, v, s);
        bool good = true;
        if (tidy_string < t_endvaluelist > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "a comma separated list of animation timings is expected");
        else if (tidy_string < t_endvaluelist > :: good ())
        {   vstr_t ve (split_by_charset (tidy_string < t_endvaluelist > :: get_string (), ";"));
            if (ve.empty ())
                nits.pick (nit_empty, es_error, ec_type, "a comma separated list of animation timings is expected");
            else for (auto sss : ve)
                if (! test_animation_timing (nits, v, sss, false)) good = false;
            if (good) return; }
        tidy_string < t_endvaluelist > :: status (s_invalid); } };

template < > struct type_master < t_existential > : type_base < mono, t_existential >
{   static bool is_existential () { return true; }
    void set_value (nitpick& , const html_version& , const ::std::string& )
    {   type_base < mono, t_existential > :: status (s_good); } };

template < > struct type_master < t_fixedpoint > : type_base < double, t_fixedpoint >
{   double value_ = 0.0;
    type_master () = default;
    void swap (type_master < t_fixedpoint >& t) noexcept
    {   ::std::swap (value_, t.value_);
        type_base < double, t_fixedpoint >::swap (t); }
    ::std::string get_string () const { return ::boost::lexical_cast < ::std::string > (value_); }
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   value_ = lexical < double > :: cast (trim_the_lot_off (s), 0.0);
        if ((s.find_first_not_of (DECIMAL) == ::std::string::npos) && (lexical < double > :: test (s)))
            type_base < double, t_fixedpoint > :: status (s_good);
        else
        {   nits.pick (nit_sunk, es_error, ec_type, quote (s), " is not a decimal number consisting of denary digit(s) and maybe an anglophone decimal point ('.' not ',')");
            type_base < double, t_fixedpoint > :: status (s_invalid); } }
    static double default_value () { return 0.0; }
    bool has_value (const double& b) const { return good () && (value_ == b); }
    int get_int () const { return static_cast < int > (value_  + 0.5); }
    double get () const { return value_; } };

template < > struct type_master < t_html > : tidy_string < t_html >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_html > :: set_value (nits, v, s);
        if (tidy_string < t_html > :: empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "a SRCDOC value cannot be empty");
            string_value < t_html > :: status (s_invalid); }
        else
        {   elements_node nodes;
            if (nodes.parse (nits, tidy_string < t_html > :: get_string ()))
                if (! nodes.has_element (elem_html))
                    nits.pick (nit_requires_html, ed_50, "4.7.2 The iframe element", es_error, ec_attribute, "the HTML snippet in a SRCDOC attribute must include an <HTML> element");
            nodes.harvest_nits (nits); } } };

template < > struct type_master < t_icccolour > : tidy_string < t_icccolour >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_icccolour > :: set_value (nits, v, s);
        if (tidy_string < t_icccolour > :: empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "a colour specification cannot be empty");
            string_value < t_icccolour > :: status (s_invalid); }
        else if (tidy_string < t_icccolour > :: good ())
        {   ::std::string icc (tidy_string < t_icccolour > :: get_string ());
            ::std::string ought ("icc-color(");
            if ((icc.length () < ought.length ()) || icc.substr (0, ought.length ()) != ought)
                nits.pick (nit_icc_colour, ed_svg_1_1, "4.2 Basic data types", es_error, ec_attribute, "a colour specification should be ", quote (ought), " ... values ... )");
            else if (icc.at (icc.length () - 1) != ')')
                nits.pick (nit_icc_colour, ed_svg_1_1, "4.2 Basic data types", es_error, ec_attribute, "a colour specification should be ", quote (ought), " ... values ... )");
            else return;
            tidy_string < t_icccolour > :: status (s_invalid); } } };

template < > struct type_master < t_id > : tidy_string < t_id >
{   bool tested_ = false, predefined_ = false;
    type_master () = default;
    void swap (type_master < t_id >& t) noexcept
    {   ::std::swap (tested_, t.tested_);
        ::std::swap (predefined_, t.predefined_);
        tidy_string < t_id >::swap (t); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& arg)
    {   tidy_string < t_id > :: set_value (nits, v, arg);
        const ::std::string& s = tidy_string < t_id > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_bad_id, es_error, ec_type, "an ID cannot be empty");
            tidy_string < t_id > :: status (s_invalid); }
        switch (v.major ())
        {   case 3 :
                if (v.minor () == 2)
                {   if (::std::string (ALPHABET).find (s.at (0)) == ::std::string::npos)
                    {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " does not start with a letter");
                        tidy_string < t_id > :: status (s_invalid); } }
                break;
            case 4 :
                if (::std::string (ALPHABET).find (s.at (0)) == ::std::string::npos)
                {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " does not start with a letter");
                    tidy_string < t_id > :: status (s_invalid); }
                else if (v.minor () == 0)
                {   if (s.find_first_not_of (ALPHABET DDD) != ::std::string::npos)
                    {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " may only contain letters or digits");
                        tidy_string < t_id > :: status (s_invalid); } }
                else if (s.find_first_not_of (IDS) != ::std::string::npos)
                {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " may only contain letters, digits, '_', and ':'");
                    tidy_string < t_id > :: status (s_invalid); }
                break;
            case 5 :
                if (s.find (' ') != ::std::string::npos)
                {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " may not contain a space");
                    tidy_string < t_id > :: status (s_invalid); } }
        tested_ = predefined_ = false; }
   bool invalid_id (nitpick& nits, const html_version& , ids_t& ids, element* pe)
   {    if (bad ()) return false;
        if (! tested_)
        {   ::std::string s (tidy_string < t_id > :: get_string ());
            predefined_ = ids.has_id (s);
            if (! predefined_) ids.insert_id (s, pe);
            else
            {   nits.pick (nit_id_exists, es_error, ec_type, quote (s), " is defined elsewhere");
                tidy_string < t_id > :: status (s_invalid); }
            tested_ = true; }
        return predefined_; } };

template < > struct type_master < t_idref > : tidy_string < t_idref >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_idref > :: set_value (nits, v, s);
        if (s.empty () || s.find (' ') != s.npos)
        {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " can neither be empty nor contain a space");
            tidy_string < t_idref > :: status (s_invalid); } }
    bool verify_id (nitpick& nits, const html_version& , ids_t& ids, const attribute_bitset& state, const vit_t& )
    {   if (! tidy_string < t_idref > :: good ()) return false;
        const ::std::string s (tidy_string < t_idref > :: get_string ());
        if (! ids.has_id (s))
            nits.pick (nit_unknown, es_error, ec_type, quote (s), " is not an existing identifier");
        else if (! ids.compatible_state (s, state.test (a_hidden)))
            nits.pick (nit_id_hidden, es_error, ec_type, quote (s), " is hidden");
        else return false;
        tidy_string < t_idref > :: status (s_invalid);
        return true; } };

template < > struct type_master < t_idrefs > : string_vector < t_idrefs, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_idrefs, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_idrefs, sz_space > :: empty ())
        {   nits.pick (nit_bad_id, es_error, ec_type, "the ID list is empty");
            string_vector < t_idrefs, sz_space > :: status (s_invalid); } }
    bool verify_id (nitpick& nits, const html_version& , ids_t& ids, const attribute_bitset& state, const vit_t& )
    {   if (! string_vector < t_idrefs, sz_space > :: good ()) return false;
        bool allgood = true;
        for (auto m : string_vector < t_idrefs, sz_space > :: get ())
        {   if (! ids.has_id (m))
            {   allgood = false;
                nits.pick (nit_bad_id, es_error, ec_type, quote (m), " is not a recognised ID"); }
            else if (! ids.compatible_state (m, state.test (a_hidden)))
            {   allgood = false;
                nits.pick (nit_id_hidden, es_error, ec_type, quote (m), " is hidden"); } }
        if (! allgood)
        {   tidy_string < t_idrefs > :: status (s_invalid);
            value_.clear (); }
        return true; } };

template < > struct type_master < t_illegal > : type_base < mono, t_illegal >
{   void set_value (nitpick& nits, const html_version& , const ::std::string& )
    {   nits.pick (nit_evermore, es_error, ec_type, "always illegal"); }
    static mono default_value () { return static_cast <mono> (0); }
    mono get () const { assert (false); return static_cast <mono> (0); } };

template < > struct type_master < t_integer > : numeric_value < t_integer, int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_integer, int > :: set_value (nits, v, s);
        if (numeric_value < t_integer, int > :: invalid ())
            nits.pick (nit_not_an_integer, es_error, ec_type, quote (s), " is not an integer"); } };

template < > struct type_master < t_is > : tidy_string < t_is >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_is > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_is > :: get_string ();
        if (tidy_string < t_is > :: empty ())
        {   nits.pick (nit_nuts, es_error, ec_type, quote (ss), " is not the name of a custom element is expected");
            tidy_string < t_is > :: status (s_invalid); }
        else if (tidy_string < t_is > :: good ())
        {   vstr_t ce (context.custom_elements ());
            if (ce.empty ())
                nits.pick (nit_nuts, es_info, ec_type, "no custom elements are defined, so ", quote (ss), " cannot be verified (see the  --" GENERAL CUSTOM " switch, '" PROG " --" HELP " for gen')");
            else if (! is_one_of (ss, ce))
            {   nits.pick (nit_nuts, es_warning, ec_type, quote (ss), " is not specified (see the --" GENERAL CUSTOM " switch, '" PROG " --" HELP " for gen')");
                tidy_string < t_is > :: status (s_invalid); } } } };

template < > struct type_master < t_itemid > : tidy_string < t_itemid >
{   typedef true_type has_int_type;
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    { return invalid_itemid (nits, v, string_value < t_itemid > :: value_, e); } };

template < > struct type_master < t_itemprop > : string_vector < t_itemprop, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_itemprop, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_itemprop, sz_space > :: empty ())
        {   nits.pick (nit_bad_itemprop, es_error, ec_type, "ITEMPROP requires a value");
            string_value < t_itemprop > :: status (s_invalid); }
        else if (string_vector < t_itemprop, sz_space > :: good ())
            for (auto t : string_vector < t_itemprop, sz_space > :: get ())
                if (t.find_first_of (":.") != ::std::string::npos)
                {   nitpick nuts;
                    url u (nuts, v, t);
                    if (u.invalid ())
                    {   nits.merge (nuts);
                        tidy_string < t_itemprop > :: status (s_invalid); }
                    else if (u.is_local () || ! u.has_absolute_path ())
                    {   nits.pick (nit_bad_itemprop, es_error, ec_type, quote (t), " is neither an absolute url nor an identifier that has no colons, no full stops");
                        tidy_string < t_itemprop > :: status (s_invalid); } } } };

template < > struct type_master < t_key > : string_vector < t_key, sz_space >
{   bool tested_ = false, predefined_ = false;
    type_master () = default;
    void swap (type_master < t_key >& t) noexcept
    {   ::std::swap (tested_, t.tested_);
        ::std::swap (predefined_, t.predefined_);
        string_vector < t_key, sz_space > :: swap (t); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_key, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_key, sz_space > :: empty ())
            nits.pick (nit_key, es_error, ec_type, "a key cannot be empty");
        else if (string_vector < t_key, sz_space > :: good ())
            if (v.major () >= 5)
            {   sstr_t check;
                for (auto k : string_vector < t_key, sz_space > :: get ())
                    if (k.length () != 1)
                        nits.pick (nit_key, ed_41, "17.11.2 Access keys", es_error, ec_type, quote (k), " is not a single character");
                    else if (check.find (k) != check.cend ())
                        nits.pick (nit_key, ed_July2020, "6.6.2 The accesskey attribute", es_error, ec_type, "access keys must be unique, yet ", quote (k), " is repeated");
                    else check.insert (k);
                if (string_vector < t_key, sz_space > :: size () == check.size ()) return; }
            else if ((s.length () == 1) || (s [0] > ' ')) return;
            else nits.pick (nit_single_character, ed_41, "17.11.2 Access keys", es_error, ec_type, quote (tidy_string < t_key > :: get_string ()), " is not a single character (which cannot be a space)");
        string_vector < t_key, sz_space > :: status (s_invalid); }
   bool invalid_access (nitpick& nits, const html_version& , sstr_t* keys)
   {    assert (keys != nullptr);
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

template < > struct type_master < t_loopie > : tidy_string < t_loopie >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_loopie > :: set_value (nits, v, s);
        const ::std::string& x = tidy_string < t_loopie > :: get_string ();
        if (x.empty ()) return;
        if ((x.find_first_not_of (DENARY) == ::std::string::npos) || compare_no_case (x, "infinite") || (x == "-1"))
           tidy_string < t_loopie > :: status (s_good);
        else
        {   nits.pick (nit_infinite_number, es_error, ec_type, quote (s), "should be an unsigned integer, -1, or the keyword 'infinite'");
            tidy_string < t_loopie > :: status (s_invalid); } } };

template < > struct type_master < t_measure > : tidy_string < t_measure > // verify against HTML 5.0, 2.4.4.4
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_measure > :: set_value (nits, v, s);
        if (! tidy_string < t_measure > :: empty ())
            if (tidy_string < t_measure > :: good ())
            {   const ::std::string& ss = tidy_string < t_measure > :: get_string ();
                ::std::string::size_type pos = ss.find_first_not_of (DECIMAL " ");
                if (pos == ::std::string::npos) return;
                ::std::string units (ss.substr (pos));
                if (units.length () == 1)
                {   if ((units [0] == '%') || (units [0] == '*')) return; }
                else
                switch (units.length ())
                    {   case 2 :
                            switch (units [0])
                            {   case 'c' :
                                case 'e' :
                                case 'm' :
                                    if (units [1] == 'm') return;
                                    break;
                                case 'i' :
                                    if (units [1] == 'n') return;
                                    break;
                                case 'p' :
                                    if ((units [1] == 'i') || (units [1] == 't') || (units [1] == 'x')) return;
                                    break;
                                default :
                                    break; }
                            break;
                        case 3 :
                            if (units == "dpi") return;
                            break;
                        case 4 :
                            if (units == "dpcm") return;
                            break;
                        default :
                            break; } }
        nits.pick (nit_immeasurable, es_error, ec_type, quote (s), ": a length is an integer or a real, optionally followed immediately by one of '%', '*', 'cm', 'dpi', 'dpcm', 'em', 'in', 'mm', 'pt', 'pi', or 'px'");
        tidy_string < t_measure > :: status (s_invalid); } };

template < > struct type_master < t_measures > : string_vector < t_measures, sz_comma >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_measures, sz_comma > :: set_value (nits, v, s);
        if (string_vector < t_measures, sz_comma > :: good ())
            for (auto m : string_vector < t_measures, sz_comma > :: get ())
            {   type_master < t_measure > tm;
                tm.set_value (nits, v, m);
                if (tm.invalid ())
                {   nits.pick (nit_immeasurable, es_error, ec_type, quote (s), " is not a comma separated list of measurements");
                    tidy_string < t_measures > :: status (s_invalid); return; } } } };

template < > struct type_master < t_navigation > : tidy_string < t_navigation >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_navigation > :: set_value (nits, v, s);
        if (s.empty () || s.find (' ') != s.npos)
        {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " can neither be empty nor contain a space");
            tidy_string < t_navigation > :: status (s_invalid); } }
    bool verify_id (nitpick& nits, const html_version& , ids_t& ids, const attribute_bitset& state, const vit_t& )
    {   if (! tidy_string < t_navigation > :: good ()) return false;
        const ::std::string s (tidy_string < t_navigation > :: get_string ());
        if (compare_no_case (s, "auto") || compare_no_case (s, "self")) return false;
        if (! ids.has_id (s))
            nits.pick (nit_unknown, es_error, ec_type, quote (s), " is not an existing identifier");
        else if (! ids.compatible_state (s, state.test (a_hidden)))
            nits.pick (nit_id_hidden, es_error, ec_type, quote (s), " is hidden");
        else return false;
        tidy_string < t_navigation > :: status (s_invalid);
        return true; } };

template < > struct type_master < t_negative > : numeric_value < t_negative, int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_negative, int > :: set_value (nits, v, s);
        if (! numeric_value < t_negative, int > :: good () || (value_ > 0))
        {   nits.pick (nit_positive, es_error, ec_type, quote (s), " is neither zero nor a negative integer");
            numeric_value < t_negative, int > :: status (s_invalid); } } };

template < > struct type_master < t_not_empty > : string_value < t_not_empty >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_not_empty > :: set_value (nits, v, s);
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "value should not be empty");
            string_value < t_not_empty > :: status (s_invalid); } } };

template < > struct type_master < t_paint > : tidy_string < t_paint >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_paint > :: set_value (nits, v, s);
        if (tidy_string < t_paint > :: empty ())
            nits.pick (nit_paint, ed_svg_1_1, "11.2 Specifying paint", es_error, ec_type, "a paint specification should not be empty");
        else if (tidy_string < t_paint > :: good ())
            if (parse_paint (nits, v, tidy_string < t_paint > :: get_string ())) return;
        tidy_string < t_paint > :: status (s_invalid); } };

template < > struct type_master < t_positive > : numeric_value < t_positive, int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_positive, int > :: set_value (nits, v, s);
        if (! numeric_value < t_positive, int > :: good () || (value_ <= 0))
        {   nits.pick (nit_positive, es_error, ec_type, quote (s), " is not an integer greater than zero");
            numeric_value < t_positive, int > :: status (s_invalid); } } };

template < > struct type_master < t_rating > : numeric_value < t_rating, int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_rating, int > :: set_value (nits, v, s);
        if (numeric_value < t_rating, int > :: good ())
            if ((numeric_value < t_rating, int > :: value_ < 1) || (numeric_value < t_rating, int > :: value_ > 5))
            {   nits.pick (nit_bad_rating, es_error, ec_type, quote (s), " is not a digit between 1 and 5");
                numeric_value < t_rating, int > :: status (s_invalid); } } };

template < > struct type_master < t_real > : type_base < double, t_real >
{   double value_ = 0.0;
    type_master () = default;
    void swap (type_master < t_real >& t) noexcept
    {   ::std::swap (value_, t.value_);
        type_base < double, t_real >::swap (t); }
    ::std::string get_string () const { return ::boost::lexical_cast < ::std::string > (value_); }
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   value_ = lexical < double > :: cast (trim_the_lot_off (s), 0.0);
        if ((s.find_first_not_of (REAL) == ::std::string::npos) && (lexical < double > :: test (s)))
            type_base < double, t_real > :: status (s_good);
        else
        {   nits.pick (nit_sunk, ed_50, "2.4.4.3 Floating-point numbers", es_error, ec_type, quote (s), " is not a floating point number");
            type_base < double, t_real > :: status (s_invalid); } }
    static double default_value () { return 0.0; }
    bool has_value (const double& b) const { return good () && (value_ == b); }
    int get_int () const { return static_cast < int > (value_ + 0.5); }
    double get () const { return value_; } };

template < > struct type_master < t_angle > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (::boost::to_lower_copy (ss) == "auto")
            type_master < t_real > :: status (s_good);
        else
        {   float max = 360.0; ::std::string::size_type len = ss.length ();
            bool units = false;
            if (ends_with_letters (ss, "grad")) { max = 400.0; len -= 4; units = true; }
            else if (ends_with_letters (ss, "rad")) { max = static_cast < float > (3.141592653589*2); len -= 3; units = true; }
            else if (ends_with_letters (ss, "deg")) { len -= 3; units = true; }
            if (ss.substr (0, len).find_first_not_of (DECIMAL) != ::std::string::npos)
                nits.pick (nit_angle, es_error, ec_type, quote (s), " contains unexpected characters (units are 'deg', 'grad', or 'rad')");
            else
            if (units && (v.svg () < sv_1_1))
                nits.pick (nit_angle, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, "angular units require SVG 1.1 or better.");
            else
            {   type_master < t_real > :: set_value (nits, v, s);
                if (good ())
                    if ((value_ >= max) || (value_ <= (-1 * max)))
                        nits.pick (nit_angle, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (s), " should be less that ", ::boost::lexical_cast < ::std::string > (max));
                    else return; }
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_angle_i > : type_master < t_angle >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (compare_no_case (ss, "inherit")) type_master < t_angle > :: status (s_good);
        else type_master < t_angle > :: set_value (nits, v, s); } };

template < > struct type_master < t_angle_ai > : type_master < t_angle_i >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (compare_no_case (ss, "auto")) type_master < t_angle_i > :: status (s_good);
        else type_master < t_angle_i > :: set_value (nits, v, s); } };

template < > struct type_master < t_frequency > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (! ends_with_letters (ss, "kHz") && ! ends_with_letters (ss, "Hz"))
            nits.pick (nit_bad_frequency, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (s), " contains unexpected characters (units are 'kHz' or 'Hz')");
        else if (v.svg () < sv_1_1)
            nits.pick (nit_bad_frequency, es_error, ec_type, "frequencies require SVG 1.1 or better.");
        else
        {   type_master < t_real > :: set_value (nits, v, s);
            if (good ()) return; }
        type_master < t_real > :: status (s_invalid); } };

template < > struct type_master < t_normalised > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_real > :: set_value (nits, v, s);
        if (type_master < t_real > :: good ())
        {   if ((type_master < t_real > ::value_ >= 0.0) &&
                (type_master < t_real > ::value_ <= 1.0)) return;
            nits.pick (nit_0_1, es_error, ec_type, "a normalised value must lie between 0 and 1 inclusive");
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_1_more > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_real > :: set_value (nits, v, s);
        if (type_master < t_real > :: good ())
        {   if ((type_master < t_real > ::value_ >= 1.0)) return;
            nits.pick (nit_1_more, es_error, ec_type, "a limit must equal or exceed 1.0");
            type_master < t_real > :: status (s_invalid); } } };

template < > struct type_master < t_origin > : tidy_string < t_origin >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_origin > :: set_value (nits, v, s);
        if (tidy_string < t_origin > :: good ())
        {   ::std::string ss (tidy_string < t_origin > :: get_string ());
            if (compare_no_case (ss, "origin")) return; }
        nits.pick (nit_origin, ed_svg_1_1, "19.2.14 The 'animateMotion' element", es_error, ec_attribute, "ORIGIN must be set to 'default'");
        tidy_string < t_origin > :: status (s_invalid); } };

template < > struct type_master < t_refx > : type_master < t_measure >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (compare_no_case (ss, "left") || compare_no_case (ss, "center") || compare_no_case (ss, "right"))
            type_master < t_measure > :: status (s_good);
        else type_master < t_measure > :: set_value (nits, v, s); } };

template < > struct type_master < t_refy > : type_master < t_measure >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (compare_no_case (ss, "top") || compare_no_case (ss, "center") || compare_no_case (ss, "bottom"))
            type_master < t_measure > :: status (s_good);
        else type_master < t_measure > :: set_value (nits, v, s); } };

template < > struct type_master < t_result > : tidy_string < t_result >
{   typedef true_type has_int_type;
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    { return invalid_id_result (nits, v, string_value < t_result > :: value_, e); } };

template < > struct type_master < t_svg_time > : type_master < t_real >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (v.svg () < sv_1_1)
            nits.pick (nit_bad_frequency, es_error, ec_type, "time requires SVG 1.1 or better.");
        else if ((ss.find_first_not_of (REAL) != ::std::string::npos) && (! ends_with_letters (ss, "ms")) && (! ends_with_letters (ss, "s")))
            nits.pick (nit_bad_frequency, ed_svg_1_1, "4.2 Basic data types", es_error, ec_type, quote (s), " must be a number, optionally followed by 'ms' or 's'");
        else
        {   type_master < t_real > :: set_value (nits, v, s);
            if (good ()) return; }
        type_master < t_real > :: status (s_invalid); } };

template < > struct type_master < t_svg_snapshottime > : type_master < t_svg_time >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (compare_no_case (ss, "none")) type_master < t_svg_time > :: status (s_good);
        else type_master < t_svg_time > :: set_value (nits, v, s); } };

template < > struct type_master < t_sex > : tidy_string < t_sex >
{   char sex_ = 0;
    ::std::string gender_;
    type_master () = default;
    void swap (type_master < t_sex >& t) noexcept
    {   ::std::swap (sex_, t.sex_);
        gender_.swap (t.gender_);
        tidy_string < t_sex >::swap (t); }
    bool parse (const html_version& , const ::std::string& s)
    {   ::std::size_t pos = s.find (';');
        switch (pos)
        {   case 0 :
                sex_ = 0;
                gender_ = s.substr (1);
                return true;
            case 1 :
                sex_ = s [0];
                gender_ = s.substr (2);
                break;
            case ::std::string::npos :
                if (s.length () != 1) return false;
                sex_ = s [0];
                break;
            default:
                return false; }
        return (s.substr (0, 1).find_first_of ("FfMmNnOoUu") != s.npos); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_sex > :: set_value (nits, v, s);
        if (! parse (v, tidy_string < t_sex > :: get_string ()))
        {   nits.pick (nit_sex, es_error, ec_type, quote (s), " should be one of 'F', 'M', 'N', 'O', 'U', or otherwise conform to RFC 6350");
            tidy_string < t_sex > :: status (s_invalid); } }
    char sex () const { return sex_; }
    ::std::string gender () const { return gender_; } };

template < > struct type_master < t_sizex > : type_base < ::std::string, t_sizex >
{   bool any_ = false;
    int x_ = 0, y_ = 0;
    type_master () = default;
    void swap (type_master < t_sizex >& t)
    {   ::std::swap (any_, t.any_);
        ::std::swap (x_, t.x_);
        ::std::swap (y_, t.y_);
        type_base < ::std::string, t_sizex >::swap (t); }
    bool parse (nitpick& nits, const html_version& , const ::std::string& s)
    {   any_ = (s == "any");
        if (any_) return true;
        ::std::size_t sep = s.find_first_of ("Xx");
        if (sep == s.npos) return false;
        if ((sep < 1) || (sep >= (s.length () - 1))) return false;
        if ((s.at (0) == '0') || (s.at (sep + 1) == '0'))
            nits.pick (nit_sizes, ed_52, "4.2.4. The link element", es_warning, ec_type, quote (s), ": no integer can start with a '0'");
        else if ((s.at (0) < '1') || (s.at (1) > '9') || (s.at (sep + 1) < '1') || (s.at (sep + 1) > '9'))
            nits.pick (nit_sizes, ed_52, "4.2.4. The link element", es_warning, ec_type, quote (s), " is not two unsigned positive integers separated by 'x'");
        bool b = false;
        x_ = lexical < int > :: cast2 (s.substr (0, sep), b);
        if (b) y_ = lexical < int > :: cast2 (s.substr (sep + 1), b);
        return b; }
    ::std::string get_string () const
    {   if (any_) return "any";
        ::std::string s (::boost::lexical_cast < ::std::string > (x_));
        s += "x";
        s = ::boost::lexical_cast < ::std::string > (y_);
        return s; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) type_base < ::std::string, t_sizex > :: status (s_good);
        else
        {   nits.pick (nit_sizes, es_error, ec_type, quote (s), " is neither 'any' nor a pair of positive integers separated by 'x'");
            type_base < ::std::string, t_sizex > :: status (s_invalid); } }
    void reset () { any_ = false; x_ = y_ = 0; type_base < ::std::string, t_sizex > :: reset (); }
    static ::std::string default_value () { return ::std::string (); }
    ::std::string get () const { return get_string (); } };

template < > struct type_master < t_sizes > : type_base < ::std::string, t_sizes >
{   typedef ::std::vector < type_master < t_sizex > > vx_t;
    vx_t value_;
    void swap (type_master < t_sizes >& t)
    {   value_.swap (t.value_);
        type_base < ::std::string, t_sizes >::swap (t); }
    bool parse (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        if (ss.empty ())
        {   nits.pick (nit_sizes, es_error, ec_type, "a sizes attribute cannot be empty");
            return false; }
        vstr_t xs (split_by_space (ss));
        value_.resize (xs.size ());
        bool res = true;
        for (::std::size_t n = 0; n < xs.size (); ++n)
        {   value_ [n].set_value (nits, v, xs [n]);
            if (value_ [n].invalid ()) res = false; }
        return res; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) type_base < ::std::string, t_sizes > :: status (s_good);
        else
        {   nits.pick (nit_sizes, es_error, ec_type, "SIZES takes a space separated sequence of values, each of which are 'any' or two positive integers separated by an 'x'");
            type_base < ::std::string, t_sizes > :: status (s_invalid); } }
    void reset ()
    {   value_.clear ();
        type_base < ::std::string, t_sizes > :: reset (); }
    static ::std::string default_value () { return "any"; }
    ::std::string get () const { return get_string (); } };

template < > struct type_master < t_sym > : public tidy_string < t_sym >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   extern void examine_character_code (const html_version& v, const ::std::string& text, bool& known, bool& invalid);
        tidy_string < t_sym > :: set_value (nits, v, ss);
        const ::std::string& s = tidy_string < t_sym > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "sym requires a value");
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
            nits.pick (nit_empty, es_error, ec_type, "target requires a value");
        else
        {   if (val [0] != '_') return;
            if ((v.svg () >= sv_1_1) && (val == "_replace")) return;
            if ((val == "_blank") || (val == "_self") || (val == "_parent") || (val == "_top")) return;
            nits.pick (nit_badtarget, es_error, ec_type, quote (s), " starts with '_', but is not a standard target"); }
        string_value < t_target > :: status (s_invalid); } };

template < > struct type_master < t_tel > : public tidy_string < t_tel >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_tel > :: set_value (nits, v, s);
        ::std::string val = tidy_string < t_tel > :: get_string ();
        if (tidy_string < t_tel > :: good ())
        {   if (val.substr (0, 4) != "tel:")
                nits.pick (nit_no_tel, es_warning, ec_type, quote (s), " should start with 'tel:' (see RFC 3966)");
            else val = val.substr (4);
            ::std::string::size_type pos = val.find (';');
            if (pos != ::std::string::npos) val = val.substr (0, pos);
            if (val.find_first_not_of (TEL) != ::std::string::npos)
            {   nits.pick (nit_phone, es_error, ec_type, quote (s), " does not appear to be a phone number (see RFC 3966)");
                tidy_string < t_tel > :: status (s_invalid); } } } };

template < > struct type_master < t_transform > : tidy_string < t_transform >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_transform > :: set_value (nits, v, s);
        if (tidy_string < t_transform > :: empty ())
            nits.pick (nit_transform, ed_svg_1_0, "8.5 Modifying the User Coordinate System: the transform attribute", es_warning, ec_type, "a TRANSFORM value ought to transform");
        else if (tidy_string < t_transform > :: good ())
            if (parse_transform (nits, v, tidy_string < t_transform > :: get_string ())) return;
        tidy_string < t_transform > :: status (s_invalid); } };

template < > struct type_master < t_unsigned > : public numeric_value < t_unsigned, unsigned int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_unsigned, unsigned int > :: set_value (nits, v, s);
        if (! numeric_value < t_unsigned, unsigned int > :: good ())
        {   nits.pick (nit_unsigned, es_error, ec_type, quote (s), " is not an unsigned integer");
            numeric_value < t_unsigned, unsigned int > :: status (s_invalid); } } };

template < > struct type_master < t_un_ex > : public numeric_value < t_un_ex, unsigned int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (s.empty ()) numeric_value < t_un_ex, unsigned int > :: status (s_good);
        else
        {   numeric_value < t_un_ex, unsigned int > :: set_value (nits, v, s);
            if (! numeric_value < t_un_ex, unsigned int > :: good ())
            {   nits.pick (nit_unsigned, es_error, ec_type, quote (s), " is not an unsigned integer, or completely omitted");
                numeric_value < t_un_ex, unsigned int > :: status (s_invalid); } } } };

template < > struct type_master < t_wanted > : public tidy_string < t_wanted >
{   void validate (nitpick& nits, const html_version& , const elem& , const ::std::string& situation)
    {   if (tidy_string < t_wanted > :: unknown ())
            nits.pick (nit_value_expected, es_warning, ec_type, "a value ought to be supplied (", situation, ")"); } };

template < > struct type_master < t_xlinktype > : public tidy_string < t_xlinktype >
{   void validate (nitpick& nits, const html_version& , const elem& , const ::std::string& )
    {   if (tidy_string < t_xlinktype > :: good ())
            if (compare_no_case (tidy_string < t_xlinktype > :: get_string (), "simple")) return;
            else nits.pick (nit_xlinktype, es_warning, ec_type, "xlink:type must be set to 'simple'");
        tidy_string < t_xlinktype > :: status (s_invalid); } };

template < > struct type_master < t_border > : public tidy_string < t_border >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_border > :: set_value (nits, v, s);
        ::std::string arg = string_value < t_border > :: get_string ();
        switch (v.major ())
        {   case 1 :
            case 3 :    if (s.empty ())
                        {   tidy_string < t_border > :: status (s_good); return; }
                        if ((v.minor () == 2) && (arg.find_first_not_of (DENARY) == ::std::string::npos))
                        {   tidy_string < t_border > :: status (s_good); return; }
                        break;
            case 2 :    if (s.empty ()) tidy_string < t_border > :: status (s_good);
                        else
                        {   type_master < t_measure > val;
                            val.set_value (nits, v, arg);
                            tidy_string < t_border > :: status (val.status ()); }
                        return;
            default :   break; }
        if ((v.major () >= 5) && (arg != "1"))
        {   tidy_string < t_border > :: status (s_invalid);
            nits.pick (nit_bad_border, es_error, ec_type, "a BORDER value must be \"1\""); } } };

template < > struct type_master < t_1_to_7 > : public numeric_value < t_1_to_7, unsigned int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_1_to_7, unsigned int > :: set_value (nits, v, s);
        if (! numeric_value < t_1_to_7, unsigned int > :: good () || (value_ < 1) || (value_ > 7))
        {   nits.pick (nit_1_to_7, es_error, ec_type, quote (s), " does not lie between 1 and 7 (inclusive)");
            numeric_value < t_1_to_7, unsigned int > :: status (s_invalid); } } };

template < > struct type_master < t_plus_1_7 > : public numeric_value < t_plus_1_7, unsigned int >
{   typedef true_type has_int_type;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string arg (trim_the_lot_off (s));
        numeric_value < t_plus_1_7, unsigned int > :: set_value (nits, v, arg);
        if (numeric_value < t_plus_1_7, unsigned int > :: good ())
        {   unsigned n = 0;
            numeric_value < t_plus_1_7, unsigned int > :: get_number (n);
            if ((n > 0) && (n <= 99)) return;
            nits.pick (nit_plus_1_7, es_error, ec_type, quote (s), " does not lie between 1 and 99 (inclusive)");
            numeric_value < t_plus_1_7, unsigned int > :: status (s_invalid); } } };

template < e_type T > bool test_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   type_master < T > t;
    t.set_value (nits, v, s);
    return t.good (); }

template < e_type T > typename type_master < T > :: value_type examine_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (! t.good ()) return type_master < T > :: default_value ();
    return static_cast < typename type_master < T > :: value_type > (t.get ()); }
