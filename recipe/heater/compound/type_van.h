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

#pragma once
#include "base/type_master.h"
#include "simple/type_autocomplete.h"
#include "microdata/microdata_itemtype.h"
#include "compound/compound.h"

template < > struct type_master < t_1_more_i > : type_or_string < t_1_more_i, t_1_more, sz_inherit >
{ using type_or_string < t_1_more_i, t_1_more, sz_inherit > :: type_or_string; };

template < > struct type_master < t_10_int > : type_exactly_n < t_10_int, sz_space_char, t_integer, 10 >
{ using type_exactly_n < t_10_int, sz_space_char, t_integer, 10 > :: type_exactly_n; };

template < > struct type_master < t_2string > : type_exactly_n < t_2string, sz_space_char, t_text, 2 >
{ using type_exactly_n < t_2string, sz_space_char, t_text, 2 > :: type_exactly_n; };

template < > struct type_master < t_4string > : type_exactly_n < t_4string, sz_space_char, t_text, 4 >
{ using type_exactly_n < t_4string, sz_space_char, t_text, 4 > :: type_exactly_n; };

template < > struct type_master < t_4string_ni > : one_of_three_or_string < t_4string_ni, t_4string, t_2string, t_css_inherit, sz_none >
{ using one_of_three_or_string < t_4string_ni, t_4string, t_2string, t_css_inherit, sz_none > :: one_of_three_or_string; };

template < > struct type_master < t_bandwidth > : type_or_string < t_bandwidth, t_real, sz_auto >
{ using type_or_string < t_bandwidth, t_real, sz_auto > :: type_or_string; };

template < > struct type_master < t_bools > : type_at_least_one < t_bools, sz_space_char, t_bool >
{ using type_at_least_one < t_bools, sz_space_char, t_bool > :: type_at_least_one; };

template < > struct type_master < t_charspacing > : type_or_any_string < t_charspacing, t_measure, sz_loose, sz_medium, sz_tight >
{ using type_or_any_string < t_charspacing, t_measure, sz_loose, sz_medium, sz_tight > :: type_or_any_string; };

template < > struct type_master < t_clear30 > : tidy_string < t_clear30 >
{   using tidy_string < t_clear30 > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_colour; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_clear30 > :: set_value (nits, v, s);
        ::std::string arg (tidy_string < t_clear30 > :: get_string ());
        if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "CLEAR requires a value");
        else if (good ())
        {   vstr_t args (split_by_space (arg));
            PRESUME (args.size () > 0, __FILE__, __LINE__);
            ::std::string::size_type start = 0;
            if ((arg.at (0) < '0') || (arg.at (0) > '9'))
            {   type_master < t_lraalign > lra (box ());
                lra.set_value (nits, v, args.at (0));
                if (! lra.good ())
                {   tidy_string < t_clear30 > :: status (s_invalid);
                    return; }
                if (args.size () == 1) return;
                start = arg.find (GSL_AT (args, 1)); }
            type_master < t_measure > m (box ());
            m.set_value (nits, v, arg.substr (0, start));
            if (m.good ()) return; }
        tidy_string < t_clear30 > :: status (s_invalid); } };

template < > struct type_master < t_colour_a > : type_or_string < t_colour_a, t_colour, sz_auto >
{ using type_or_string < t_colour_a, t_colour, sz_auto > :: type_or_string; };

template < > struct type_master < t_colour_i > : type_or_string < t_colour_i, t_colour, sz_inherit >
{ using type_or_string < t_colour_i, t_colour, sz_inherit > :: type_or_string; };

template < > struct type_master < t_colour_ci > : type_or_string < t_colour_ci, t_colour_i, sz_currentcolour >
{ using type_or_string < t_colour_ci, t_colour_i, sz_currentcolour > :: type_or_string; };

template < > struct type_master < t_colour_cii > : type_or_either_string < t_colour_cii, t_colour_i, sz_currentcolour, sz_inherit >
{ using type_or_either_string < t_colour_cii, t_colour_i, sz_currentcolour, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_colour_ni > : type_or_any_string < t_colour_ni, t_colour, sz_none, sz_inherit, sz_currentcolour >
{ using type_or_any_string < t_colour_ni, t_colour, sz_none, sz_inherit, sz_currentcolour > :: type_or_any_string; };

template < > struct type_master < t_colour_trans > : either_type_or_string < t_colour_trans, t_css_colour, t_colour, sz_transparent >
{ using either_type_or_string < t_colour_trans, t_css_colour, t_colour, sz_transparent > :: either_type_or_string; };

template < > struct type_master < t_colour_trans_i > : type_or_string < t_colour_trans_i, t_colour_trans, sz_inherit >
{ using type_or_string < t_colour_trans_i, t_colour_trans, sz_inherit > :: type_or_string; };

template < > struct type_master < t_colour_ii > : type_or_either_string < t_colour_ii, t_colour, sz_invert, sz_inherit >
{ using type_or_either_string < t_colour_ii, t_colour, sz_invert, sz_inherit > :: type_or_either_string; };

template < > struct type_master < t_context_menu > : tidy_string < t_context_menu >
{   using tidy_string < t_context_menu > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_other; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_context_menu > :: set_value (nits, v, s);
        if (tidy_string < t_context_menu > :: empty ())
        {   nits.pick (nit_bad_contextmenu, ed_51, "4.11.5. Context menus", es_error, ec_attribute, "CONTEXTMENU cannot be empty");
            tidy_string < t_context_menu > :: status (s_invalid); } }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   type_master < t_idref > t (box ());
        ::std::string s (tidy_string < t_context_menu > :: get_string ());
        t.set_value (nits, v, s);
        if (t.invalid_id (nits, v, ids, pe)) return true;
        if (! ids.has_id (s)) return true;
        if (v != html_5_1) return false;
        const e_element e (ids.get_tag (s));
        if (e == elem_menu) return false;
        nits.pick (nit_bad_contextmenu, ed_51, "4.11.5. Context menus", es_error, ec_attribute, quote (s), " is <", elem::name (e), ">, not <MENU>");
        string_value < t_context_menu > :: status (s_invalid);
        return true; } };

template < > struct type_master < t_duration_media > : tidy_string < t_duration_media >
{   using tidy_string < t_duration_media > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_duration_media > :: set_value (nits, v, s);
        if (tidy_string < t_duration_media > :: good ())
        {   ::std::string ss (tidy_string < t_duration_media > :: get_string ());
            if (compare_complain (nits, v, "media", ss)) return;
            if (test_value < t_svg_duration > (nits, v, ss)) return; }
        nits.pick (nit_dur, ed_svg_1_1, "19.2.8 Attributes to control the timing of the animation", es_error, ec_type, "a duration, or 'media', is expected");
        tidy_string < t_duration_media > :: status (s_invalid); } };

template < > struct type_master < t_enable_background > : tidy_string < t_enable_background >
{   using tidy_string < t_enable_background > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_enable_background > :: set_value (nits, v, s);
        if (tidy_string < t_enable_background > :: empty ())
            nits.pick (nit_background, es_error, ec_type, "a value is required");
        else if (tidy_string < t_enable_background > :: good ())
        {   vstr_t ss (split_by_space (tidy_string < t_enable_background > :: get_string ()));
            const size_t sz = ss.size ();
            if (sz > 0)
            {   if (compare_complain (nits, v, "accumulate", ss.at (0)) ||
                    compare_complain (nits, v, "inherit", ss.at (0)))
                {   if (sz == 1) return;
                    nits.pick (nit_background, es_error, ec_type, "neither 'accumulate' nor 'inherit' take arguments"); }
                else if (compare_complain (nits, v, "new", ss.at (0)))
                {   if (sz == 1) return;
                    if (sz != 5)
                        nits.pick (nit_background, es_error, ec_type, "'new' requires zero or four arguments");
                    else
                        if (test_value < t_real > (nits, v, ss.at (1)) &&
                            test_value < t_real > (nits, v, ss.at (2)) &&
                            test_value < t_real > (nits, v, ss.at (3)) &&
                            test_value < t_real > (nits, v, ss.at (4))) return; }
                else nits.pick (nit_background, es_error, ec_type, "'accumulate', 'new', or 'inherit' expected"); } }
        tidy_string < t_enable_background > :: status (s_invalid); } };

template < > struct type_master < t_font_families > : type_at_least_one < t_font_families, sz_comma, t_font_family >
{ using type_at_least_one < t_font_families, sz_comma, t_font_family > :: type_at_least_one; };

template < > struct type_master < t_css_font_families > : type_either_or < t_css_font_families, t_css_inherit, t_font_families >
{ using type_either_or < t_css_font_families, t_css_inherit, t_font_families > :: type_either_or; };

template < > struct type_master < t_hidden_ex > : public tidy_string < t_hidden_ex >
{   using tidy_string < t_hidden_ex > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_hidden_ex > :: set_value (nits, v, s);
        if (tidy_string < t_hidden_ex > :: empty ())
            tidy_string < t_hidden_ex > :: status (s_good);
        else
        {   type_master < t_hidden > hh (box ());
            hh.set_value (nits, v, s);
            if (hh.good ())
            {   if ((hh.get_int () == eh_hidden) || (v >= html_apr22))
                {   tidy_string < t_hidden_ex > :: status (s_good);
                    return; } }
            nits.pick (nit_hidden, es_error, ec_type, "invalid HIDDEN attribute value");
            tidy_string < t_hidden_ex > :: status (s_invalid); }} };

template < > struct type_master < t_indentalign2 > : type_or_string < t_indentalign2, t_indentalign, sz_indentalign >
{ using type_or_string < t_indentalign2, t_indentalign, sz_indentalign > :: type_or_string; };

template < > struct type_master < t_indentshift2 > : type_or_string < t_indentshift2, t_measure, sz_indentshift >
{ using type_or_string < t_indentshift2, t_measure, sz_indentshift > :: type_or_string; };

template < > struct type_master < t_lcraligns > : type_at_least_one < t_lcraligns, sz_space_char, t_lcralign >
{ using type_at_least_one < t_lcraligns, sz_space_char, t_lcralign > :: type_at_least_one; };

template < > struct type_master < t_lcrds > : type_at_least_one < t_lcrds, sz_space_char, t_lcrd >
{ using type_at_least_one < t_lcrds, sz_space_char, t_lcrd > :: type_at_least_one; };

template < > struct type_master < t_lcrdss > : string_vector < t_lcrdss, sz_space_char >
{   using string_vector < t_lcrdss, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        ::boost::replace_all (ss, "{", " ");
        ::boost::replace_all (ss, "}", " ");
        if (test_value < t_lcrds > (nits, v, trim_the_lot_off (ss))) return;
        string_vector < t_lcrdss, sz_space_char > :: status (s_invalid); } };

template < > struct type_master < t_length > : type_either_or < t_length, t_length_absolute, t_length_relative >
{ using type_either_or < t_length, t_length_absolute, t_length_relative > :: type_either_or; };

template < > struct type_master < t_linethickness > : tidy_string < t_linethickness >
{   using tidy_string < t_linethickness > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_linethickness > :: set_value (nits, v, s);
        if (v.math () >= math_2)
        {   if (tidy_string < t_linethickness > :: empty ())
                nits.pick (nit_empty, ed_math_2, "3.3.2.2 Attributes of mfrac", es_error, ec_type, "thin, medium, thick, or a measurement expected");
            else if (tidy_string < t_linethickness > :: good ())
            {   ::std::string ss (tidy_string < t_linethickness > :: get_string ());
                switch (ss.at (0))
                {   case 'M' :
                    case 'm' :
                        if (compare_complain (nits, v, ss, "medium")) return;
                        break;
                    case 'T' :
                    case 't' :
                        if (compare_complain (nits, v, ss, "thin")) return;
                        if (compare_complain (nits, v, ss, "thick")) return;
                        break;
                    default : break; } } }
        if (test_value < t_vunit > (nits, v, s)) return;
        tidy_string < t_linethickness > :: status (s_invalid); } };

template < > struct type_master < t_mathalign_n > : string_vector < t_mathalign_n, sz_space_char >
{   using string_vector < t_mathalign_n, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_mathalign_n, sz_space_char > :: set_value (nits, v, s);
        if (string_vector < t_mathalign_n, sz_space_char > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "TYPE requires a value");
        else if (string_vector < t_mathalign_n, sz_space_char > :: good ())
        {   vstr_t args (string_vector < t_mathalign_n, sz_space_char > :: get ());
            if (test_value < t_mathalign > (nits, v, args.at (0)))
                if (args.size () == 1) return;
                else if (test_value < t_integer > (nits, v, args.at (1)))
                    if (args.size () == 2) return;
                    else nits.pick (nit_too_many, ed_math_2, "3.5.1 Table or Matrix (mtable)", es_error, ec_type, "expecting one position and, optionally one number"); }
        string_vector < t_mathalign_n, sz_space_char > :: status (s_invalid); } };

template < > struct type_master < t_mathaligns > : type_at_least_one < t_mathaligns, sz_space_char, t_mathalign >
{ using type_at_least_one < t_mathaligns, sz_space_char, t_mathalign > :: type_at_least_one; };

template < > struct type_master < t_mathnotations > : type_at_least_one < t_mathnotations, sz_space_char, t_mathnotation >
{ using type_at_least_one < t_mathnotations, sz_space_char, t_mathnotation > :: type_at_least_one; };

template < > struct type_master < t_mathsize > : tidy_string < t_mathsize >
{   using tidy_string < t_mathsize > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_mathsize > :: set_value (nits, v, s);
        if (tidy_string < t_mathsize > :: empty ())
            nits.pick (nit_empty, ed_math_2, "3.2.2 Mathematics style attributes common to token elements", es_error, ec_type, "small, normal, big, or a measurement expected");
        else if (tidy_string < t_mathsize > :: good ())
        {   ::std::string ss (tidy_string < t_mathsize > :: get_string ());
            if (compare_complain (nits, v, ss, "small")) return;
            if (compare_complain (nits, v, ss, "normal")) return;
            if (compare_complain (nits, v, ss, "big")) return;
            if (test_value < t_vunit > (nits, v, ss)) return; }
        tidy_string < t_mathsize > :: status (s_invalid); } };

template < > struct type_master < t_mathspace > : type_either_or < t_mathspace, t_namedspace, t_hunit >
{ using type_either_or < t_mathspace, t_namedspace, t_hunit > :: type_either_or; };

template < > struct type_master < t_mathspaceauto > : type_or_string < t_mathspaceauto, t_mathspace, sz_auto >
{ using type_or_string < t_mathspaceauto, t_mathspace, sz_auto > :: type_or_string; };

template < > struct type_master < t_mathspacefit > : type_or_either_string < t_mathspacefit, t_mathspace, sz_auto, sz_fit >
{ using type_or_either_string < t_mathspacefit, t_mathspace, sz_auto, sz_fit > :: type_or_either_string; };

template < > struct type_master < t_mathspaceinfinity > : type_or_string < t_mathspaceinfinity, t_mathspace, sz_infinity >
{ using type_or_string < t_mathspaceinfinity, t_mathspace, sz_infinity > :: type_or_string; };

template < > struct type_master < t_og > : type_either_or < t_og, t_url, t_ogtype >
{   using type_either_or < t_og, t_url, t_ogtype > :: type_either_or;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_either_or < t_og, t_url, t_ogtype > :: set_value (nits, v, s);
        if (type_either_or < t_og, t_url, t_ogtype > :: good ())
        {   nitpick nuts;
            if (v >= html_jan14)
            {   url u (nuts, v, s, pr_other);
                if (! u.invalid () && u.has_absolute_path () && u.is_usable () && ! u.deduced_path ())
                {   nits.merge (nuts); return; } }
            if (test_value < t_ogtype > (nits, v, s)) return;
            nits.merge (nuts); }
        type_either_or < t_og, t_url, t_ogtype > :: status (s_invalid); } };

template < > struct type_master < t_ogdet > : type_or_null < t_ogdet, t_determiner >
{   using type_or_null < t_ogdet, t_determiner > :: type_or_null; };

template < > struct type_master < t_pseudonamedspace > : tidy_string < t_pseudonamedspace >
{   using tidy_string < t_pseudonamedspace > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_pseudonamedspace > :: set_value (nits, v, s);
        if (tidy_string < t_pseudonamedspace > :: empty ())
            nits.pick (nit_empty, ed_math_2, ".3.6.2 Attributes", es_error, ec_type, "value missing");
        else if (tidy_string < t_pseudonamedspace > :: good ())
        {   ::std::string ss (tidy_string < t_pseudonamedspace > :: get_string ());
            nitpick nuts;
            switch (v.math_version ())
            {   case math_2 :
                    if (test_value < t_namedspace > (nuts, v, ss))
                    {   nits.merge (nuts); return; }
                    break;
                case math_3 :
                case math_4_20 :
                case math_core :
                case math_4_22 :
                    {   const ::std::string::size_type len = ss.length ();
                        if (len >= 5)
                            if ((ss.substr (len - 5) == "width") || (ss.substr (len - 5) == "depth"))
                                ss = ss.substr (0, len - 5);
                            else if (len >= 6)
                            if (ss.substr (len - 6) == "height")
                                ss = ss.substr (0, len - 6); }
                    break;
                default : break; }
            if (test_value < t_pseudo > (nits, v, ss)) return; }
        tidy_string < t_pseudonamedspace > :: status (s_invalid); } };

template < > struct type_master < t_inputaccept > : tidy_string < t_inputaccept >
{   using tidy_string < t_inputaccept > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_inputaccept > :: set_value (nits, v, s);
        if (tidy_string < t_inputaccept > :: empty ())
            nits.pick (nit_unacceptable, es_error, ec_type, "ACCEPT cannot be empty");
        else if (tidy_string < t_inputaccept > :: good ())
        {   vstr_t vac (split_by_charset (tidy_string < t_inputaccept > :: get_string (), ","));
            if (vac.empty ())
               nits.pick (nit_unacceptable, es_error, ec_type, "ACCEPT cannot be empty");
            else
            {   bool ok = true;
                for (auto sss : vac)
                {   switch (sss.at (0))
                    {   case '.' :  continue;
                        case 'A' :
                        case 'a' :  if (compare_complain (nits, v, sss, "audio/*")) continue;
                                    break;
                        case 'I' :
                        case 'i' :  if (compare_complain (nits, v, sss, "image/*")) continue;
                                    break;
                        case 'V' :
                        case 'v' :  if (compare_complain (nits, v, sss, "video/*")) continue;
                                    break;
                        default: break; }
                    type_master < t_mime > m (box ());
                    m.set_value (nits, v, sss);
                    if (! m.good ()) ok = false; }
                if (ok) return; } }
        tidy_string < t_inputaccept > :: status (s_invalid); } };

template < > struct type_master < t_nsds > : type_at_least_one < t_nsds, sz_space_char, t_nsd >
{ using type_at_least_one < t_nsds, sz_space_char, t_nsd > :: type_at_least_one; };

template < > struct type_master < t_real_1_2 > : type_one_or_both < t_real_1_2, t_real, sz_commaspace, t_real >
{   using type_one_or_both < t_real_1_2, t_real, sz_commaspace, t_real > :: type_one_or_both;
    static e_animation_type animation_type () noexcept { return at_number; } };

template < > struct type_master < t_roles > : string_vector < t_roles, sz_space_char >
{   using string_vector < t_roles, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_roles, sz_space_char > :: set_value (nits, v, s);
        if (string_vector < t_roles, sz_space_char > :: empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "TYPE requires a value");
            string_vector < t_roles, sz_space_char > :: status (s_invalid); }
        else if (string_vector < t_roles, sz_space_char > :: good ())
        {   bool allgood = true;
            for (auto arg : string_vector < t_roles, sz_space_char > :: get ())
            {   type_master < t_role > ar (box ());
                ar.set_value (nits, v, arg);
                if (! ar.good ()) allgood = false; }
            if (allgood) return; }
        string_vector < t_roles, sz_space_char > :: status (s_invalid); } };

template < > struct type_master < t_sandboxen > : string_vector < t_sandboxen, sz_space_char >
{   using string_vector < t_sandboxen, sz_space_char > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_sandboxen, sz_space_char > :: set_value (nits, v, s);
        if (string_vector < t_sandboxen, sz_space_char > :: good ())
        {   bool allgood = true, script = false, origin = false, topnav = false, topnavuser = false, topnavprot = false;
            for (auto arg : string_vector < t_sandboxen, sz_space_char > :: get ())
            {   type_master < t_sandbox > sb (box ());
                sb.set_value (nits, v, arg);
                if (! sb.good ()) allgood = false;
                else switch (sb.get ())
                {   case sand_scripts : script = true; break;
                    case sand_origin : origin = true; break;
                    case sand_navigation : topnav = true; break;
                    case sand_atnbua : topnavuser = true; break;
                    case sand_atntcp : topnavprot = true; break;
                    default : break; } }
            if (script && origin)
                nits.pick (nit_overallowed, ed_50, "4.7.2 The iframe element", es_warning, ec_attribute, "'allow-scripts' and 'allow-same-origin', used together, defeat the sandbox");
            if (topnav && topnavuser)
                nits.pick (nit_overallowed, ed_jan21, "4.8.5 The iframe element", es_warning, ec_attribute, "it is redundant to specify both 'allow-top-navigation' and 'allow-top-navigation-by-user-activation' in SANDBOX");
            if (topnavprot && (topnavuser || topnav))
                nits.pick (nit_overallowed, ed_apr22, "4.8.5 The iframe element", es_error, ec_attribute, "'allow-top-navigation-to-custom-protocols' can be combined with neither 'allow-top-navigation' nor 'allow-top-navigation-by-user-activation' in SANDBOX");
            if (allgood) return; }
        string_vector < t_sandboxen, sz_space_char > :: status (s_invalid); } };

template < > struct type_master < t_ontology > : tidy_string < t_ontology >
{   e_ontology mdr_ = s_none;
    e_ontology_type st_ = ont_illegal;
    ::std::string vocab_;
    using tidy_string < t_ontology > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_ontology > :: set_value (nits, v, s);
        if (tidy_string < t_ontology > :: good ()) try
        {   ::std::string name (tidy_string < t_ontology > :: get_string ());
            if (name.find (':') == ::std::string::npos)
                nits.pick (nit_ontology_url, ed_jul20, "5.2.2 Items", es_error, ec_type, quote (s), " must be an absolute URL identifying a standard type (for example, 'http://" SCHEMA_ORG "/TypeName')");
            else if ((name.length () < 6) || (name.substr (0, 4) != "http"))
                nits.pick (nit_ontology_domain, es_error, ec_type, quote (s), " is neither 'http://' nor 'https://', so is unknown to " PROG);
            else
            {   ::std::string::size_type ends_at = 0;
                mdr_ = ontology_names.starts_with (ONTOLOGY_CURIE, ! v.xhtml (), name, &ends_at);
                if (mdr_ == s_error)
                    nits.pick (nit_ontology_domain, es_error, ec_type, quote (s), " is a domain unknown to " PROG);
                else
                {   if (ends_at > 0) vocab_ = name.substr (ends_at);
                    if (vocab_.empty ())
                        nits.pick (nit_unrecognised_ontology, es_warning, ec_type, quote (s), " is incomplete");
                    else
                    {   st_ = sch :: parse (nits, v, vocab_, mdr_);
                        if (st_ != ont_illegal) return;
                        nits.pick (nit_unrecognised_ontology, es_warning, ec_type, quote (s), " is unrecognised by " PROG); } } } }
            catch (...) { }
        tidy_string < t_ontology > :: status (s_invalid); }
    e_ontology_type ontology_type () const noexcept { return st_; }
    e_ontology root () const noexcept { return mdr_; }
    ::std::string vocab () const { return vocab_; } };

template < > struct type_master < t_shape3 > : tidy_string < t_shape3 >
{   using tidy_string < t_shape3 > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_paint; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_shape3 > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_shape3 > :: get_string ();
        if (ss.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "SHAPE requires a value");
            tidy_string < t_shape3 > :: status (s_invalid); }
        else if (good ())
        {   vstr_t args (split_by_space (ss));
            if (args.size () > 0)
                if (test_value < t_shape4 > (nits, v, args.at (0))) return; // should check coordinates too
            tidy_string < t_shape3 > :: status (s_invalid); } } };

template < > struct type_master < t_roman_dsc > : tidy_string < t_roman_dsc >
{   using tidy_string < t_roman_dsc > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_roman_dsc > :: set_value (nits, v, s);
        const ::std::string& arg = tidy_string < t_roman_dsc > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "TYPE ad valorem requirit");
            tidy_string < t_roman_dsc > :: status (s_invalid); }
        else if (good ())
        {   if (arg.length () == 1)
            {   type_master < t_listtype > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            else
            {   type_master < t_dsc > tst (box ());
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            tidy_string < t_roman_dsc > :: status (s_invalid); } } };

template < > struct type_master < t_imcastr > : tidy_string < t_imcastr >
{   url u_;
    int width_ = 0;
    float density_ = 1.0;
    bool has_width_ = false, has_density_ = false;
    using tidy_string < t_imcastr > :: tidy_string;
    void swap (type_master < t_imcastr >& t)
    {   ::std::swap (u_, t.u_);
        ::std::swap (width_, t.width_);
        ::std::swap (density_, t.density_);
        ::std::swap (has_width_, t.has_width_);
        ::std::swap (has_density_, t.has_density_);
        tidy_string < t_imcastr > :: swap (t); }
    bool parse (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_imcastr > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_imcastr > :: get_string ();
        if (! string_value < t_imcastr > :: good ()) return false;
        vstr_t args (split_by_space (ss));
        if ((args.size () == 0) || (args.size () > 2))
        {   nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_attribute,
                "one SRCSET entry is a URL optionally followed by a width (integer 'w') or a density descriptor (x.y 'x')");
            return false; }
        type_master < t_url > u (box ());
        u.set_value (nits, v, args.at (0));
        if (u.invalid ()) return false;
        if (args.size () == 1) return true;
        const ::std::string::size_type pos = args.at (1).length ();
        if (pos > 1)
            switch (args.at (1).at (pos-1))
            {   case 'w' :
                case 'W' :
                    width_ = lexical < int > :: cast (args.at (1).substr (0, pos-1));
                    if (width_ > 0) { has_width_ = true; return true; }
                    break;
                case 'x' :
                case 'X' :
                    density_ = lexical < float > :: cast (args.at (1).substr (0, pos-1));
                    if (density_ > 0.0) { has_density_ = true; return true; }
                    break;
                default : break; }
        nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_attribute,
            quote (args.at (1)), ": the second part of a SRCSET, if present, is a positive integer width immediately followed by 'w', or a positive real density immediately followed by 'x'");
        return false; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) tidy_string < t_imcastr > :: status (s_good);
        else tidy_string < t_imcastr > :: status (s_invalid); }
    bool has_width () const noexcept { return has_width_; }
    bool has_density () const noexcept { return has_density_; }
    void reset () noexcept
    {   u_.reset (); width_ = 0; density_ = 1.0;
        tidy_string < t_imcastr > :: reset (); }
    static ::std::string default_value () noexcept { return ::std::string (); } };

template < > struct type_master < t_srcset > : tidy_string < t_srcset >
{   typedef ::std::vector < type_master < t_imcastr > > vix_t;
    vix_t value_;
    bool has_width_ = false, has_density_ = false;
    using tidy_string < t_srcset > :: tidy_string;
    void swap (type_master < t_srcset >& t) noexcept
    {   value_.swap (t.value_);
        tidy_string < t_srcset >::swap (t); }
    bool parse (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_srcset > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_srcset > :: get_string ();
        if (tidy_string < t_srcset > :: empty ())
        {   nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "a SRCSET attribute cannot be empty");
            return false; }
        if (! tidy_string < t_srcset > :: good ()) return false;
        vstr_t xs (split_by_charset (ss, ","));
        value_.resize (xs.size ());
        bool res = true;
        const ::std::size_t max = xs.size ();
        for (::std::size_t n = 0; n < max; ++n)
        {   GSL_AT (value_, n).set_value (nits, v, GSL_AT (xs, n));
            if (GSL_AT (value_, n).invalid ()) res = false;
            else if (GSL_AT (value_, n).good ())
            {   if (GSL_AT (value_, n).has_width ()) has_width_ = true;
                if (GSL_AT (value_, n).has_density ()) has_density_ = true; } }
        if (! res)
        {   if (max < 2) nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "SRCSET takes a comma separated list of values, each a url followed by, optionally, a space and a width or a density");
            return false; }
        if (max > 1)
        {   if (has_density_)
                if (has_width_)
                {   nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "do not mix widths and densities in a SRCSET");
                    return false; }
                else for (::std::size_t x = 0; x < max - 1; ++x)
                    for (::std::size_t y = x+1; y < max; ++y)
                        if ((GSL_AT (value_, x).density_ > 0.0) && (GSL_AT (value_, x).density_ == GSL_AT (value_, y).density_))
                            if (GSL_AT (value_, x).density_ == 1.0)
                            {   nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "in a SRCSET the default density is 1.0, which may only occur once");
                                return false; }
                            else
                            {   nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "each density in a SRCSET must be unique (", GSL_AT (value_, x).density_, " is repeated)");
                                return false; }
            if (has_width_)
                for (::std::size_t x = 0; x < max - 1; ++x)
                    for (::std::size_t y = x+1; y < max; ++y)
                        if ((GSL_AT (value_, x).width_ > 0) && (GSL_AT (value_, x).width_ == GSL_AT (value_, y).width_))
                        {   nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "each width in a SRCSET must be unique (", GSL_AT (value_, x).width_, " is repeated)");
                            return false; } }
        return res; }
    bool has_width () const noexcept { return has_width_; }
    bool has_density () const noexcept { return has_density_; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) string_value < t_srcset > :: status (s_good);
        else tidy_string < t_srcset > :: status (s_invalid); }
    void reset () noexcept
    {   value_.clear ();
        tidy_string < t_srcset > :: reset (); } };

template < > struct type_master < t_css_text_align_4 > : tidy_string < t_css_text_align_4 >
{   using tidy_string < t_css_text_align_4 > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_text_align_4 > :: set_value (nits, v, s);
        if (tidy_string < t_css_text_align_4 > :: empty ()) nits.pick (nit_empty, es_error, ec_type, "missing whitespace value");
        else if (tidy_string < t_css_text_align_4 > :: good ())
        {   ::std::string ss (tidy_string < t_css_text_align_4 > :: get_string ());
            if (v.css_text () >= 4)
            {   nitpick nuts;
                if (test_value < t_char > (nuts, v, ss))
                {   nits.merge (nuts); return; } }
            if (test_value < t_css_text_align > (nits, v, ss)) return; }
        tidy_string < t_css_text_align_4 > :: status (s_invalid); } };

template < > struct type_master < t_css_vertal_2 > : tidy_string < t_css_vertal_2 >
{   using tidy_string < t_css_vertal_2 > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_vertal_2 > :: set_value (nits, v, s);
        if (tidy_string < t_css_vertal_2 > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "missing vertical align value");
        else if (tidy_string < t_css_vertal_2 > :: good ())
        {   ::std::string ss (tidy_string < t_css_vertal_2 > :: get_string ());
            nitpick nuts; bool tested = false;
            if (v.css_inline () > 0)
            {   if (test_value < t_css_vertal_inline > (nuts, v, ss)) return;
                tested = true; }
            if (v.svg () || v.is_css_2 ())
            {   if (test_value < t_css_vertal > (nits, v, ss)) return;
                tested = true; }
            if (tested) nits.merge (nuts);
            else nits.pick (nit_version, es_error, ec_type, "VERTICAL-ALIGN requires SVG or CSS 2 or later"); }
        tidy_string < t_css_vertal_2 > :: status (s_invalid); } };

template < > struct type_master < t_css_whitespace_2 > : tidy_string < t_css_whitespace_2 >
{   using tidy_string < t_css_whitespace_2 > :: tidy_string;
	static e_animation_type animation_type () noexcept { return at_none; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_whitespace_2 > :: set_value (nits, v, s);
        if (tidy_string < t_css_whitespace_2 > :: empty ()) nits.pick (nit_empty, es_error, ec_type, "missing whitespace value");
        else if (tidy_string < t_css_whitespace_2 > :: good ())
        {   ::std::string ss (tidy_string < t_css_whitespace_2 > :: get_string ());
            nitpick nuts;
            if (v.css_text () >= 4)
            {   if (test_value < t_css_whitespace_4 > (nuts, v, ss))
                { nits.merge (nuts); return; } }
            if (test_value < t_css_whitespace > (nits, v, ss)) return; }
        tidy_string < t_css_whitespace_2 > :: status (s_invalid); } };
