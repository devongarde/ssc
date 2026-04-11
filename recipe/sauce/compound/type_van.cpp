/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "element/element.h"
#include "type/type.h"

bool invalid_context_menu_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe, element* box, const ::std::string& s)
{   type_master < t_idref > t (box);
    t.set_value (nits, v, s);
    if (t.invalid_id (nits, v, ids, pe)) return true;
    if (! ids.has_id (s)) return true;
    if (v != html_5_1) return false;
    const e_element e (ids.get_tag (s));
    if (e == elem_menu) return false;
    nits.pick (nit_bad_contextmenu, ed_51, "4.11.5. Context menus", es_error, ec_attribute, quote (s), " is <", elem::name (e), ">, not <MENU>");
    return true; }

bool type_master < t_imcastr > :: parse (nitpick& nits, const html_version& v, const ::std::string& s)
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

bool type_master < t_srcset > :: parse (nitpick& nits, const html_version& v, const ::std::string& s)
{   string_value < t_srcset > :: set_value (nits, v, s);
    const ::std::string& ss = tidy_string < t_srcset > :: get_string ();
    if (tidy_string < t_srcset > :: empty ())
    {   nits.pick (nit_bad_srcset, ed_jul20, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "a SRCSET attribute cannot be empty");
        return false; }
    if (! tidy_string < t_srcset > :: good ()) return false;
    vstr_t xs (split_by_charset (ss, PLAINSEP));
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

e_status set_clear30_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s, element* box)
{   VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "CLEAR requires a value");
    else if (es == s_good )
    {   vstr_t args (split_by_space (s));
        PRESUME (args.size () > 0, __FILE__, __LINE__);
        ::std::string::size_type start = 0;
        if ((s.at (0) < '0') || (s.at (0) > '9'))
        {   type_master < t_lraalign > lra (box);
            lra.set_value (nits, v, args.at (0));
            if (! lra.good ()) return s_invalid;
            if (args.size () == 1) return s_good;
            start = s.find (GSL_AT (args, 1)); }
        type_master < t_measure > m (box);
        m.set_value (nits, v, s.substr (0, start));
        if (m.good ()) return s_good; }
    return s_invalid; }

e_status set_css_text_align_4_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "missing whitespace value");
    else if (es == s_good )
    {   if (v.css_module (c_text) >= 4)
        {   nitpick nuts;
            if (test_value < t_char > (nuts, v, s))
            {   nits.merge (nuts); return s_good; } }
        if (test_value < t_css_text_align > (nits, v, s)) return s_good; }
    return s_invalid; }

e_status set_css_text_resizes_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "CLEAR requires a value");
    else if (es == s_good )
    {   nitpick nuts;
        if (v.css_module (c_overflow) >= 4)
        {   if (test_value < t_css_text_resizes_4 > (nuts, v, s))
            { nits.merge (nuts); return s_good; } }
        if (test_value < t_css_text_resize > (nits, v, s)) return s_good;
        nits.merge (nuts); }
    return s_invalid; }

e_status set_css_vertal_2_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "CLEAR requires a value");
    else if (es == s_good )
    {   nitpick nuts; bool tested = false;
        if (v.css_module (c_inline_layout) > 0)
        {   if (test_value < t_css_vertal_inline > (nuts, v, s)) return s_good;
            tested = true; }
        if (v.svg () || v.is_css_2 ())
        {   if (test_value < t_css_vertal > (nits, v, s)) return s_good;
            tested = true; }
        if (tested) nits.merge (nuts);
        else nits.pick (nit_version, es_error, ec_type, "VERTICAL-ALIGN requires SVG or CSS 2 or later"); }
    return s_invalid; }

e_status set_css_whitespace_2_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "CLEAR requires a value");
    else if (es == s_good )
    {   nitpick nuts;
        if (v.css_module (c_text) >= 4)
        {   if (test_value < t_css_whitespace_4 > (nuts, v, s))
            { nits.merge (nuts); return s_good; } }
        if (test_value < t_css_whitespace > (nits, v, s)) return s_good;
        nits.merge (nuts); }
    return s_invalid; }

e_status set_custom_element_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "missing custom element value");
    else if (es == s_good)
    {   if (v >= html_jul25)
        {   if (test_value < t_custom_element_new > (nits, v, s)) return s_good; }
        else if (test_value < t_custom_element_old > (nits, v, s)) return s_good; }
    return s_invalid; }

e_status set_duration_media_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_good)
    {   ::std::string ss (trim_the_lot_off (s));
        if (compare_complain (nits, v, "media", ss)) return s_good;
        if (test_value < t_svg_duration > (nits, v, ss)) return s_good; }
    nits.pick (nit_dur, ed_svg_1_1, "19.2.8 Attributes to control the timing of the animation", es_error, ec_type, "a duration, or 'media', is expected");
    return s_invalid; }

e_status set_enable_background_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_empty) nits.pick (nit_background, es_error, ec_type, "a value is required");
    else if (es == s_good)
    {   vstr_t ss (split_by_space (s));
        const size_t sz = ss.size ();
        if (sz > 0)
        {   if (compare_complain (nits, v, "accumulate", ss.at (0)) ||
                compare_complain (nits, v, "inherit", ss.at (0)))
            {   if (sz == 1) return s_good;
                nits.pick (nit_background, es_error, ec_type, "neither 'accumulate' nor 'inherit' take arguments"); }
            else if (compare_complain (nits, v, "new", ss.at (0)))
            {   if (sz == 1) return s_good;
                if (sz != 5)
                    nits.pick (nit_background, es_error, ec_type, "'new' requires zero or four arguments");
                else
                    if (test_value < t_real > (nits, v, ss.at (1)) &&
                        test_value < t_real > (nits, v, ss.at (2)) &&
                        test_value < t_real > (nits, v, ss.at (3)) &&
                        test_value < t_real > (nits, v, ss.at (4))) return s_good; }
            else nits.pick (nit_background, es_error, ec_type, "'accumulate', 'new', or 'inherit' expected"); } }
    return s_invalid; }

e_status set_hidden_ex_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s, element* box)
{   VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    if (es == s_empty) return s_good;
    type_master < t_hidden > hh (box);
    hh.set_value (nits, v, s);
    if (hh.good ())
        if ((hh.get_int () == eh_hidden) || (v >= html_apr22))
            return s_good;
    nits.pick (nit_hidden, es_error, ec_type, "invalid HIDDEN attribute value");
    return s_invalid; }

e_status set_inputaccept_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s, element* )
{   if (es == s_empty) nits.pick (nit_unacceptable, es_error, ec_type, "ACCEPT cannot be empty");
    else if (es == s_good)
    {   vstr_t vac (split_by_charset (s, PLAINSEP));
        if (vac.empty ()) nits.pick (nit_unacceptable, es_error, ec_type, "ACCEPT cannot be empty");
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
            if (ok) return s_good; } }
    return s_invalid; }

e_status set_lcrdss_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   ::std::string ss (trim_the_lot_off (s));
    ::boost::replace_all (ss, "{", " ");
    ::boost::replace_all (ss, "}", " ");
    if (test_value < t_lcrds > (nits, v, trim_the_lot_off (ss))) return s_good;
    return s_invalid; }

e_status set_linethickness_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (v.math () >= math_2)
        if (es == s_empty) nits.pick (nit_empty, ed_math_2, "3.3.2.2 Attributes of mfrac", es_error, ec_type, "thin, medium, thick, or a measurement expected");
        else if (es == s_good)
        {   ::std::string ss (trim_the_lot_off (s));
            switch (ss.at (0))
            {   case 'M' :
                case 'm' :
                    if (compare_complain (nits, v, ss, "medium")) return s_good;
                    break;
                case 'T' :
                case 't' :
                    if (compare_complain (nits, v, ss, "thin")) return s_good;
                    if (compare_complain (nits, v, ss, "thick")) return s_good;
                    break;
                default : break; } }
    if (test_value < t_vunit > (nits, v, s)) return s_good;
    return s_invalid; }

e_status set_mathalign_n_value (const e_status es, nitpick& nits, const html_version& v, const vstr_t& args)
{   if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "TYPE requires a value");
    else if (es == s_good)
        if (test_value < t_mathalign > (nits, v, args.at (0)))
            if (args.size () == 1) return s_good;
            else if (test_value < t_integer > (nits, v, args.at (1)))
                if (args.size () == 2) return s_good;
                else nits.pick (nit_too_many, ed_math_2, "3.5.1 Table or Matrix (mtable)", es_error, ec_type, "expecting one position and, optionally one number");
    return s_invalid; }

e_status set_og_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_good)
    {   nitpick nuts;
        if (v >= html_jan14)
        {   url u (nuts, v, s, pr_other);
            if (! u.invalid () && u.has_absolute_path () && u.is_usable () && ! u.deduced_path ())
            {   nits.merge (nuts); return s_good; } }
        if (test_value < t_ogtype > (nits, v, s)) return s_good;
        nits.merge (nuts); }
    return s_invalid; }

void type_master < t_ontology > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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
                    if ((st_ != ont_illegal) && ((mdr_ == s_none) || (sch::root (st_) == s_none) || (sch::root (st_) == mdr_))) return;                        
                    else nits.pick (nit_unrecognised_ontology, es_warning, ec_type, quote (s), " is unrecognised by " PROG " (3)"); } } } }
        catch (...) { }
    tidy_string < t_ontology > :: status (s_invalid); }

e_status set_pseudonamedspace_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_empty) nits.pick (nit_empty, ed_math_2, ".3.6.2 Attributes", es_error, ec_type, "value missing");
    else if (es == s_good)
    {   ::std::string ss (trim_the_lot_off (s));
        nitpick nuts;
        switch (v.math_version ())
        {   case math_2 :
                if (test_value < t_namedspace > (nuts, v, ss))
                {   nits.merge (nuts); return s_good; }
                break;
            case math_3 :
            case math_4 :
            case math_core :
                {   const ::std::string::size_type len = ss.length ();
                    if (len >= 5)
                        if ((ss.substr (len - 5) == "width") || (ss.substr (len - 5) == "depth"))
                            ss = ss.substr (0, len - 5);
                        else if (len >= 6)
                        if (ss.substr (len - 6) == "height")
                            ss = ss.substr (0, len - 6); }
                break;
            default : break; }
        if (test_value < t_pseudo > (nits, v, ss)) return s_good; }
    return s_invalid; }

e_status set_ratio_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "ratio expected");
    else if (es == s_good)
    {   const ::std::string::size_type pos = s.find ('/');
        if ((pos == 0) || (pos == s.size () - 1))
            nits.pick (nit_bad_aspect_ratio, es_error, ec_type, quote (s), ": expecting width / height");
        else
        {   ::std::string numerator;
            double w = 0.0, h = 1.0;
            if (pos == ::std::string::npos)
                numerator = trim_the_lot_off (s);
            else
            {   numerator = trim_the_lot_off (s.substr (0, pos));
                const ::std::string demoninator = trim_the_lot_off (s.substr (pos+1));
                if (! demoninator.empty ())
                {   nitpick nuts;
                    if (test_value < t_css_fn_trans_args > (nuts, v, demoninator))
                    {   nits.merge (nuts); h = 1.0; }
                    else h = lexical < double > :: cast (demoninator); } }
            if (! numerator.empty ())
            {   nitpick nuts;
                if (test_value < t_css_fn_trans_args > (nuts, v, numerator))
                {   nits.merge (nuts); w = 1.0; }
                else w = lexical < double > :: cast (numerator); }
            if ((w < 0.0) || (h < 0.0))
                nits.pick (nit_bad_aspect_ratio, es_error, ec_type, quote (s), ": all ratio values must be positive");
            else if ((w == 0.0) || (h == 0.0))
                nits.pick (nit_bad_aspect_ratio, es_error, ec_type, quote (s), ": degenerate ratios are ignored");
            else return s_good; } }
    return s_invalid; }

void type_master < t_roles > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   string_vector < t_roles, sz_space_char > :: set_value (nits, v, s);
    if (string_vector < t_roles, sz_space_char > :: empty ())
    {   nits.pick (nit_empty, es_error, ec_type, "TYPE requires a value");
        string_vector < t_roles, sz_space_char > :: status (s_invalid); }
    else if (string_vector < t_roles, sz_space_char > :: good ())
    {   bool allgood = true;
        for (auto arg : string_vector < t_roles, sz_space_char > :: get ())
        {   type_master < t_role > ar (box ());
            ar.set_value (nits, v, arg);
            vr_.push_back (ar.get_int ());
            if (! ar.good ()) allgood = false; }
        if (allgood) return; }
    string_vector < t_roles, sz_space_char > :: status (s_invalid); }

void type_master < t_roles > :: verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* p, const ::std::string& s)
{   for (auto r : vr_)
    {   enum_n < t_role, e_aria_role > emr;
        emr.set (static_cast < e_aria_role > (r));
        emr.verify_attribute (nits, v, e, p, s); } }


e_status set_roman_dsc_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s, element* box)
{   VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "TYPE ad valorem requirit");
    else if (es == s_good)
    {   if (s.length () == 1)
        {   type_master < t_listtype > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; }
        else
        {   type_master < t_dsc > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; } }
    return s_invalid; }

e_status set_sandboxen_value (const e_status es, nitpick& nits, const html_version& v, const vstr_t& args, element* box)
{   VERIFY_NOT_NULL (box, __FILE__, __LINE__);
    if (es == s_empty) return s_empty;
    if (es == s_good)
    {   bool allgood = true, script = false, origin = false, topnav = false, topnavuser = false, topnavprot = false;
        for (auto arg : args)
        {   type_master < t_sandbox > sb (box);
            sb.set_value (nits, v, arg);
            if (! sb.good ()) allgood = false;
            else switch (sb.get ()) // dearest visual studio, so where is that dreadful C style cast?!
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
        else if (allgood) return s_good; }
    return s_invalid; }

e_status set_shape3_value (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "SHAPE requires a value");
    else if (es == s_good)
    {   vstr_t args (split_by_space (s));
        if (args.size () > 0)
            if (test_value < t_shape4 > (nits, v, args.at (0))) return s_good; } // should check coordinates too
    return s_invalid; }

void type_master < t_imcastr > :: swap (type_master < t_imcastr >& t)
{   ::std::swap (u_, t.u_);
    ::std::swap (width_, t.width_);
    ::std::swap (density_, t.density_);
    ::std::swap (has_width_, t.has_width_);
    ::std::swap (has_density_, t.has_density_);
    tidy_string < t_imcastr > :: swap (t); }

bool is_baseline (nitpick& nits, const html_version& v, const vstr_t& vs, ::std::size_t& from)
{   nitpick nuts;
    PRESUME (from < vs.size (), __FILE__, __LINE__);
    if (compare_no_case (vs.at (from), sz_baseline :: sz ()))
        return true;
    if (vs.size () > from + 1)
        if (test_value < t_first_last > (nuts, v, vs.at (from)))
            if (compare_no_case (vs.at (from+1), sz_baseline :: sz ()))
            {   nits.merge (nuts);
                ++from;
                return true; }
    return false; }

template < e_type A, e_type B > e_status set_css_place (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   if (es == s_empty) nits.pick (nit_empty, es_error, ec_type, "value expected");
    else if (es == s_good)
    {   vstr_t args (split_by_space (s));
        if (args.size () == 0) nits.pick (nit_empty, es_error, ec_type, "value expected");
        else
        {   ::std::size_t from = 0;
            if (is_baseline (nits, v, args, from) || test_value < A > (nits, v, args.at (0)))
            {   if (++from == args.size ()) return s_good; }
                if (args.size () > 3)
                    nits.pick (nit_too_many, es_warning, ec_type, "too many values");
                if (test_value < B > (nits, v, args.at (from))) return s_good; } }
    return s_invalid; }

e_status set_css_place_content (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   return set_css_place < t_css_align_content, t_css_justify_content > (es, nits, v, s); }

e_status set_css_place_items (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   return set_css_place < t_css_box_alignself_acs, t_css_box_justitems_ns > (es, nits, v, s); }

e_status set_css_place_self (const e_status es, nitpick& nits, const html_version& v, const ::std::string& s)
{   return set_css_place < t_css_box_alignself_acs, t_css_box_justself > (es, nits, v, s); }
