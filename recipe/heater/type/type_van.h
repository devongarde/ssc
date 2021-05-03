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
#include "type/type_autocomplete.h"
#include "microdata/microdata_itemtype.h"

template < > struct type_master < t_1_more_i > : type_or_string < t_1_more_i, t_1_more, sz_inherit > { };
template < > struct type_master < t_animate > : type_or_either_string < t_animate, t_url, sz_none, sz_inherit > { };
template < > struct type_master < t_bandwidth > : type_or_string < t_bandwidth, t_real, sz_auto > { };
template < > struct type_master < t_bools > : type_at_least_one < t_bools, sz_space, t_bool > { };
template < > struct type_master < t_charspacing > : type_or_any_string < t_charspacing, t_measure, sz_loose, sz_medium, sz_tight > { };

template < > struct type_master < t_clear30 > : tidy_string < t_clear30 >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_clear30 > :: set_value (nits, v, s);
        ::std::string arg (tidy_string < t_clear30 > :: get_string ());
        if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "CLEAR requires a value");
        else if (good ())
        {   vstr_t args (split_by_space (arg));
            DBG_ASSERT (args.size () > 0);
            ::std::string::size_type start = 0;
            if ((arg.at (0) < '0') || (arg.at (0) > '9'))
            {   type_master < t_lraalign > lra;
                lra.set_value (nits, v, args.at (0));
                if (! lra.good ())
                {   tidy_string < t_clear30 > :: status (s_invalid);
                    return; }
                if (args.size () == 1) return;
                start = arg.find (args [1]); }
            type_master < t_measure > m;
            m.set_value (nits, v, arg.substr (0, start));
            if (m.good ()) return; }
        tidy_string < t_clear30 > :: status (s_invalid); } };

template < > struct type_master < t_colour_i > : type_or_string < t_colour_i, t_colour, sz_inherit > { };
template < > struct type_master < t_colour_ci > : type_or_string < t_colour_ci, t_colour_i, sz_currentcolour > { };
template < > struct type_master < t_colour_cii > : type_or_either_string < t_colour_cii, t_colour_i, sz_currentcolour, sz_inherit > { };
template < > struct type_master < t_colour_ni > : type_or_either_string < t_colour_ni, t_colour, sz_none, sz_inherit > { };

template < > struct type_master < t_context_menu > : tidy_string < t_context_menu >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_context_menu > :: set_value (nits, v, s);
        if (tidy_string < t_context_menu > :: empty ())
        {   nits.pick (nit_bad_contextmenu, ed_51, "4.11.5. Context menus", es_error, ec_attribute, "CONTEXTMENU cannot be empty");
            tidy_string < t_context_menu > :: status (s_invalid); } }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
    {   type_master < t_idref > t;
        ::std::string s (tidy_string < t_context_menu > :: get_string ());
        t.set_value (nits, v, s);
        if (t.invalid_id (nits, v, ids, pe)) return true;
        if (! ids.has_id (s)) return true;
        if (v != html_5_1) return false;
        e_element e (ids.get_tag (s));
        if (e == elem_menu) return false;
        nits.pick (nit_bad_contextmenu, ed_51, "4.11.5. Context menus", es_error, ec_attribute, quote (s), " is <", elem::name (e), ">, not <MENU>");
        string_value < t_context_menu > :: status (s_invalid);
        return true; } };

template < > struct type_master < t_duration_media > : tidy_string < t_duration_media >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_duration_media > :: set_value (nits, v, s);
        if (tidy_string < t_duration_media > :: good ())
        {   ::std::string ss (tidy_string < t_duration_media > :: get_string ());
            if (compare_complain (nits, v, "media", ss)) return;
            if (test_value < t_svg_duration > (nits, v, ss)) return; }
        nits.pick (nit_dur, ed_svg_1_1, "19.2.8 Attributes to control the timing of the animation", es_error, ec_type, "a duration, or 'media', is expected");
        tidy_string < t_duration_media > :: status (s_invalid); } };

template < > struct type_master < t_enablebackground > : tidy_string < t_enablebackground >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_enablebackground > :: set_value (nits, v, s);
        if (tidy_string < t_enablebackground > :: empty ())
            nits.pick (nit_background, es_error, ec_type, "a value is required");
        else if (tidy_string < t_enablebackground > :: good ())
        {   vstr_t ss (split_by_space (tidy_string < t_enablebackground > :: get_string ()));
            size_t sz = ss.size ();
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
        tidy_string < t_enablebackground > :: status (s_invalid); } };

template < > struct type_master < t_fontfamilies > : type_at_least_one < t_fontfamilies, sz_comma, t_fontfamily > { };
template < > struct type_master < t_indentalign2 > : type_or_string < t_indentalign2, t_indentalign, sz_indentalign > { };
template < > struct type_master < t_indentshift2 > : type_or_string < t_indentshift2, t_measure, sz_indentshift > { };
template < > struct type_master < t_lcraligns > : type_at_least_one < t_lcraligns, sz_space, t_lcralign > { };
template < > struct type_master < t_lcrds > : type_at_least_one < t_lcrds, sz_space, t_lcrd > { };

template < > struct type_master < t_lcrdss > : string_vector < t_lcrdss, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   ::std::string ss (trim_the_lot_off (s));
        ::boost::replace_all (ss, "{", " ");
        ::boost::replace_all (ss, "}", " ");
        if (test_value < t_lcrds > (nits, v, trim_the_lot_off (ss))) return;
        string_vector < t_lcrdss, sz_space > :: status (s_invalid); } };

template < > struct type_master < t_length > : type_either_or < t_length, t_length_absolute, t_length_relative > { };

template < > struct type_master < t_linethickness > : tidy_string < t_linethickness >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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

template < > struct type_master < t_mathalign_n > : string_vector < t_mathalign_n, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_mathalign_n, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_mathalign_n, sz_space > :: empty ())
            nits.pick (nit_empty, es_error, ec_type, "TYPE requires a value");
        else if (string_vector < t_mathalign_n, sz_space > :: good ())
        {   vstr_t args (string_vector < t_mathalign_n, sz_space > :: get ());
            if (test_value < t_mathalign > (nits, v, args.at (0)))
                if (args.size () == 1) return;
                else if (test_value < t_integer > (nits, v, args.at (1)))
                    if (args.size () == 2) return;
                    else nits.pick (nit_too_many, ed_math_2, "3.5.1 Table or Matrix (mtable)", es_error, ec_type, "expecting one position and, optionally one number"); }
        string_vector < t_mathalign_n, sz_space > :: status (s_invalid); } };

template < > struct type_master < t_mathaligns > : type_at_least_one < t_mathaligns, sz_space, t_mathalign > { };
template < > struct type_master < t_mathnotations > : type_at_least_one < t_mathnotations, sz_space, t_mathnotation > { };

template < > struct type_master < t_mathsize > : tidy_string < t_mathsize >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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

template < > struct type_master < t_mathspace > : type_either_or < t_mathspace, t_namedspace, t_hunit > { };
template < > struct type_master < t_mathspaceauto > : type_or_string < t_mathspaceauto, t_mathspace, sz_auto > { };
template < > struct type_master < t_mathspacefit > : type_or_either_string < t_mathspacefit, t_mathspace, sz_auto, sz_fit > { };
template < > struct type_master < t_mathspaceinfinity > : type_or_string < t_mathspaceinfinity, t_mathspace, sz_infinity > { };

template < > struct type_master < t_pseudonamedspace > : tidy_string < t_pseudonamedspace >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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
                case math_4 :
                    {   ::std::string::size_type len = ss.length ();
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
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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
                    type_master < t_mime > m;
                    m.set_value (nits, v, sss);
                    if (! m.good ()) ok = false; }
                if (ok) return; } }
        tidy_string < t_inputaccept > :: status (s_invalid); } };

template < > struct type_master < t_nsds > : type_at_least_one < t_nsds, sz_space, t_nsd > { };

template < > struct type_master < t_preserveaspectratio > : tidy_string < t_preserveaspectratio >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_preserveaspectratio > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_preserveaspectratio > :: get_string ();
        if (string_value < t_preserveaspectratio > :: invalid ()) return;
        vstr_t args (split_by_space (ss));
        if (args.empty ()) nits.pick (nit_bad_aspect_ratio, ed_svg_1_0, "Section 8.4", es_error, ec_type, "preserve-aspect-ratio cannot be empty");
        else
        {   type_master < t_svg_align > a;
            a.set_value (nits, v, args.at (0));
            if (a.good ())
            {   if (args.size () < 2) return;
                size_t par = 0;
                if ((v.svg () == sv_1_1) || (v.svg () == sv_1_2_tiny))
                    if (args.at (0) == "defer") par = 1;
                type_master < t_svg_align > sa;
                sa.set_value (nits, v, args.at (par));
                if (sa.good ())
                    if (args.size () == par) return;
                    else
                    {   type_master < t_meetslice > m;
                        m.set_value (nits, v, args.at (par));
                        if (m.good ()) ++par;
                        if (args.size () >= par)
                            nits.pick (nit_bad_aspect_ratio, ed_svg_1_0, "Section 8.4", es_warning, ec_type, "additional preserve-aspect-ratio values ignored");
                        return; } } }
        tidy_string < t_preserveaspectratio > :: status (s_invalid); } };

template < > struct type_master < t_real_1_2 > : type_one_or_both < t_real_1_2, t_real, sz_commaspace, t_real > { };

template < > struct type_master < t_roles > : string_vector < t_roles, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_roles, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_roles, sz_space > :: empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "TYPE requires a value");
            string_vector < t_roles, sz_space > :: status (s_invalid); }
        else if (string_vector < t_roles, sz_space > :: good ())
        {   bool allgood = true;
            for (auto arg : string_vector < t_roles, sz_space > :: get ())
            {   type_master < t_role > ar;
                ar.set_value (nits, v, arg);
                if (! ar.good ()) allgood = false; }
            if (allgood) return; }
        string_vector < t_roles, sz_space > :: status (s_invalid); } };

template < > struct type_master < t_sandboxen > : string_vector < t_sandboxen, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_sandboxen, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_sandboxen, sz_space > :: good ())
        {   bool allgood = true, script = false, origin = false, topnav = false, topnavuser = false;
            for (auto arg : string_vector < t_sandboxen, sz_space > :: get ())
            {   type_master < t_sandbox > sb;
                sb.set_value (nits, v, arg);
                if (! sb.good ()) allgood = false;
                else switch (sb.get ())
                {   case s_scripts : script = true; break;
                    case s_origin : origin = true; break;
                    case s_navigation : topnav = true; break;
                    case s_atnbua : topnavuser = true; break;
                    default : break; } }
            if (script && origin)
                nits.pick (nit_overallowed, ed_50, "4.7.2 The iframe element", es_warning, ec_attribute, "'allow-scripts' and 'allow-same-origin', used together, defeat the sandbox");
            if (topnav && topnavuser)
                nits.pick (nit_overallowed, ed_jan21, "4.8.5 The iframe element", es_warning, ec_attribute, "it is redundant to specify both 'allow-top-navigation' and 'allow-top-navigation-by-user-activation' in SANDBOX");
            if (allgood) return; }
        string_vector < t_sandboxen, sz_space > :: status (s_invalid); } };

template < > struct type_master < t_schema > : tidy_string < t_schema >
{   e_microdata_root mdr_ = mdr_none;
    e_schema_type st_ = sty_illegal;
    ::std::string vocab_;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_schema > :: set_value (nits, v, s);
        if (tidy_string < t_schema > :: good ()) try
        {   ::std::string name (tidy_string < t_schema > :: get_string ());
            if (name.find (':') == ::std::string::npos)
                nits.pick (nit_schema_url, ed_jul20, "5.2.2 Items", es_error, ec_type, quote (s), " must be an absolute URL identifying a standard microdata type (for example, http://" SCHEMA_ORG "/...)");
            else if ((name.length () < 6) || (name.substr (0, 4) != "http"))
                nits.pick (nit_schema_domain, es_error, ec_type, quote (s), " is neither 'http://' nor 'https://', so is unknown to " PROG);
            else
            {   ::std::string::size_type ends_at = 0;
                mdr_ = type_master < t_microdata_root > :: starts_with (name, &ends_at);
                if (mdr_ == mdr_none)
                    nits.pick (nit_schema_domain, es_error, ec_type, quote (s), " is a microdata domain unknown to " PROG);
                else
                {   if (ends_at > 0) vocab_ = name.substr (ends_at);
                    if (vocab_.empty ())
                        nits.pick (nit_unrecognised_schema, es_warning, ec_type, quote (s), " is incomplete");
                    else
                    {   st_ = sch :: parse (nits, v, vocab_, mdr_);
                        if (st_ != sty_illegal) return;
                        nits.pick (nit_unrecognised_schema, es_warning, ec_type, quote (s), " is unrecognised by " PROG); } } } }
            catch (...) { }
        tidy_string < t_schema > :: status (s_invalid); }
    e_schema_type schema_type () const { return st_; }
    e_microdata_root root () const { return mdr_; }
    ::std::string vocab () const { return vocab_; } };

template < > struct type_master < t_shape3 > : tidy_string < t_shape3 >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_shape3 > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_shape3 > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "SHAPE requires a value");
            tidy_string < t_shape3 > :: status (s_invalid); }
        else if (good ())
        {   vstr_t args (split_by_space (ss));
            if (args.size () > 0)
                if (test_value < t_shape4 > (nits, v, args.at (0))) return; // should check coordinates too
            tidy_string < t_shape3 > :: status (s_invalid); } } };

template < > struct type_master < t_roman_dsc > : tidy_string < t_roman_dsc >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_roman_dsc > :: set_value (nits, v, s);
        const ::std::string& arg = tidy_string < t_roman_dsc > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "TYPE ad valorem requirit");
            tidy_string < t_roman_dsc > :: status (s_invalid); }
        else if (good ())
        {   if (arg.length () == 1)
            {   type_master < t_listtype > tst;
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            else
            {   type_master < t_dsc > tst;
                tst.set_value (nits, v, arg);
                if (tst.good ()) return; }
            tidy_string < t_roman_dsc > :: status (s_invalid); } } };

template < > struct type_master < t_imcastr > : tidy_string < t_imcastr >
{   url u_;
    int width_ = 0;
    float density_ = 1.0;
    bool has_width_ = false, has_density_ = false;
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
        type_master < t_url > u;
        u.set_value (nits, v, args.at (0));
        if (u.invalid ()) return false;
        if (args.size () == 1) return true;
        ::std::string::size_type pos = args.at (1).length ();
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
    bool has_width () const { return has_width_; }
    bool has_density () const { return has_density_; }
    void reset ()
    {   u_.reset (); width_ = 0; density_ = 1.0;
        tidy_string < t_imcastr > :: reset (); }
    static ::std::string default_value () { return ::std::string (); } };

template < > struct type_master < t_srcset > : tidy_string < t_srcset >
{   typedef ::std::vector < type_master < t_imcastr > > vix_t;
    vix_t value_;
    bool has_width_ = false, has_density_ = false;
    void swap (type_master < t_srcset >& t)
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
        ::std::size_t max = xs.size ();
        for (::std::size_t n = 0; n < max; ++n)
        {   value_ [n].set_value (nits, v, xs [n]);
            if (value_ [n].invalid ()) res = false;
            else if (value_ [n].good ())
            {   if (value_ [n].has_width ()) has_width_ = true;
                if (value_ [n].has_density ()) has_density_ = true; } }
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
                        if ((value_ [x].density_ > 0.0) && (value_ [x].density_ == value_ [y].density_))
                            if (value_ [x].density_ == 1.0)
                            {   nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "in a SRCSET the default density is 1.0, which may only occur once");
                                return false; }
                            else
                            {   nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "each density in a SRCSET must be unique (", value_ [x].density_, " is repeated)");
                                return false; }
            if (has_width_)
                for (::std::size_t x = 0; x < max - 1; ++x)
                    for (::std::size_t y = x+1; y < max; ++y)
                        if ((value_ [x].width_ > 0) && (value_ [x].width_ == value_ [y].width_))
                        {   nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "each width in a SRCSET must be unique (", value_ [x].width_, " is repeated)");
                            return false; } }
        return res; }
    bool has_width () const { return has_width_; }
    bool has_density () const { return has_density_; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) string_value < t_srcset > :: status (s_good);
        else tidy_string < t_srcset > :: status (s_invalid); }
    void reset ()
    {   value_.clear ();
        tidy_string < t_srcset > :: reset (); } };
