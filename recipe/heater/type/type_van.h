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
#include "type/type_master.h"
#include "type/type_autocomplete.h"
#include "microdata/microdata_itemtype.h"

template < > struct type_master < t_1_more_i > : tidy_string < t_1_more_i >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_1_more_i > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_1_more_i > :: get_string ();
        if (ss.empty ())
            nits.pick (nit_empty, es_error, ec_type, "a value is expected");
        else if (good ())
        {   if (compare_no_case ("inherit", ss)) return;
            if (test_value < t_1_more > (nits, v, ss)) return; }
        tidy_string < t_1_more_i > :: status (s_invalid); } };

template < > struct type_master < t_clear30 > : tidy_string < t_clear30 >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_clear30 > :: set_value (nits, v, s);
        ::std::string arg (tidy_string < t_clear30 > :: get_string ());
        if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "CLEAR requires a value");
        else if (good ())
        {   vstr_t args (split_by_space (arg));
            assert (args.size () > 0);
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

template < > struct type_master < t_colour_i > : tidy_string < t_colour_i >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_colour_i > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_colour_i > :: get_string ();
        if (ss.empty ())
            nits.pick (nit_empty, es_error, ec_type, "a value is expected");
        else if (good ())
        {   if (compare_no_case ("inherit", ss)) return;
            if (test_value < t_colour > (nits, v, ss)) return; }
        tidy_string < t_colour_i > :: status (s_invalid); } };

template < > struct type_master < t_colour_ci > : tidy_string < t_colour_ci >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_colour_ci > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_colour_ci > :: get_string ();
        if (ss.empty ())
            nits.pick (nit_empty, es_error, ec_type, "a value is expected");
        else if (good ())
        {   if (compare_no_case ("currentcolor", ss)) return;
            if (test_value < t_colour_i > (nits, v, ss)) return; }
        tidy_string < t_colour_ci > :: status (s_invalid); } };

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

template < > struct type_master < t_cursor_f > : tidy_string < t_cursor_f >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_cursor_f > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_cursor_f > :: get_string ();
        if (ss.empty ())
            nits.pick (nit_empty, es_error, ec_type, "a value is expected");
        else if (good ())
        {   if (compare_no_case (ss.substr (0, 3), "url"))
            {   ::std::string::size_type bra = ss.find_first_of ("(");
                ::std::string::size_type ket = ss.find_last_of (")");
                if ((bra != ::std::string::npos) && (ket != ::std::string::npos))
                    if (++bra < ket) if (test_value < t_url > (nits, v, ss.substr (bra, ket-bra))) return; }
            else if (test_value < t_cursor > (nits, v, ss)) return;
            nits.pick (nit_curses, ed_svg_1_1, "16.8.2 The cursor property", es_error, ec_type, "a valid cursor value is expected"); }
        tidy_string < t_cursor_f > :: status (s_invalid); } };

template < > struct type_master < t_dashes > : tidy_string < t_dashes >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_dashes > :: set_value (nits, v, s);
        if (tidy_string < t_dashes > :: empty ())
            nits.pick (nit_dashed, ed_svg_1_1, "11.4 Stroke Properties", es_error, ec_type, "a sequence of numbers is expected");
        else if (tidy_string < t_dashes > :: good ())
        {   ::std::string ss (tidy_string < t_dashes > :: get_string ());
            if (compare_no_case (ss, "none")) return;
            if (compare_no_case (ss, "inherit")) return;
            vstr_t sss (split_by_charset (ss, ", "));
            bool ok = true;
            for (auto arg : sss)
                if (! test_value < t_measure > (nits, v, arg)) ok = false;
            if (ok) return; }
        tidy_string < t_dashes > :: status (s_invalid); } };

template < > struct type_master < t_dur_repeat > : tidy_string < t_dur_repeat >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_dur_repeat > :: set_value (nits, v, s);
        if (tidy_string < t_dur_repeat > :: good ())
        {   ::std::string ss (tidy_string < t_dur_repeat > :: get_string ());
            if (compare_no_case (ss, "indefinite")) return;
            if (test_value < t_svg_duration > (nits, v, ss)) return; }
        nits.pick (nit_dur, ed_svg_1_1, "19.2.8 Attributes to control the timing of the animation", es_error, ec_type, "a duration, 'media' or 'indefinite' is expected");
        tidy_string < t_dur_repeat > :: status (s_invalid); } };

template < > struct type_master < t_dur > : tidy_string < t_dur >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_dur > :: set_value (nits, v, s);
        if (tidy_string < t_dur > :: good ())
        {   ::std::string ss (tidy_string < t_dur > :: get_string ());
            if (compare_no_case (ss, "media")) return;
            if (test_value < t_dur_repeat > (nits, v, ss)) return; }
        nits.pick (nit_dur, ed_svg_1_1, "19.2.8 Attributes to control the timing of the animation", es_error, ec_type, "a duration, 'media' or 'indefinite' is expected");
        tidy_string < t_dur > :: status (s_invalid); } };

template < > struct type_master < t_duration_media > : tidy_string < t_duration_media >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_duration_media > :: set_value (nits, v, s);
        if (tidy_string < t_duration_media > :: good ())
        {   ::std::string ss (tidy_string < t_duration_media > :: get_string ());
            if (compare_no_case (ss, "media")) return;
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
            {   if (compare_no_case (ss.at (0), "accumulate") ||
                    compare_no_case (ss.at (0), "inherit"))
                {   if (sz == 1) return;
                    nits.pick (nit_background, es_error, ec_type, "neither 'accumulate' nor 'inherit' take arguments"); }
                else if (compare_no_case (ss.at (0), "new"))
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

template < > struct type_master < t_linethickness > : tidy_string < t_linethickness >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_linethickness > :: set_value (nits, v, s);
        if (v.math () >= math_2)
        {   if (tidy_string < t_linethickness > :: empty ())
                nits.pick (nit_empty, ed_math_2, "3.3.2.2 Attributes of mfrac", es_error, ec_type, "thin, medium, thick, or a measurement expected");
            else if (tidy_string < t_linethickness > :: good ())
            {   ::std::string ss (tidy_string < t_linethickness > :: get_string ());
                if (compare_no_case (ss, "thin")) return;
                if (compare_no_case (ss, "medium")) return;
                if (compare_no_case (ss, "thick")) return; } }
        if (test_value < t_measure > (nits, v, s)) return;
        tidy_string < t_linethickness > :: status (s_invalid); } };

template < > struct type_master < t_marker > : tidy_string < t_marker >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_marker > :: set_value (nits, v, s);
        if (tidy_string < t_marker > :: empty ())
            nits.pick (nit_marker, ed_svg_1_1, "11.6.3 Marker properties", es_error, ec_type, "none, inherit, or url(...) expected");
        else if (tidy_string < t_marker > :: good ())
        {   ::std::string ss (tidy_string < t_marker > :: get_string ());
            if (compare_no_case (ss, "none")) return;
            if (compare_no_case (ss, "inherit")) return;
            if (compare_no_case (ss.substr (0, 3), "url"))
            {   ::std::string::size_type bra = ss.find_first_of ("(");
                ::std::string::size_type ket = ss.find_last_of (")");
                if ((bra != ::std::string::npos) && (ket != ::std::string::npos))
                    if (++bra < ket) if (test_value < t_url > (nits, v, ss.substr (bra, ket-bra))) return; } }
        tidy_string < t_marker > :: status (s_invalid); } };

template < > struct type_master < t_mathsize > : tidy_string < t_mathsize >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_mathsize > :: set_value (nits, v, s);
        if (tidy_string < t_mathsize > :: empty ())
            nits.pick (nit_empty, ed_math_2, "3.2.2 Mathematics style attributes common to token elements", es_error, ec_type, "small, normal, big, or a measurement expected");
        else if (tidy_string < t_mathsize > :: good ())
        {   ::std::string ss (tidy_string < t_mathsize > :: get_string ());
            if (compare_no_case (ss, "small")) return;
            if (compare_no_case (ss, "normal")) return;
            if (compare_no_case (ss, "big")) return;
            if (test_value < t_measure > (nits, v, ss)) return; }
        tidy_string < t_mathsize > :: status (s_invalid); } };

template < > struct type_master < t_mathspace > : tidy_string < t_mathspace >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_mathspace > :: set_value (nits, v, s);
        if (tidy_string < t_mathspace > :: empty ())
            nits.pick (nit_empty, ed_math_2, "3.2.2 Mathematics style attributes common to token elements", es_error, ec_type, "small, normal, big, or a measurement expected");
        else if (tidy_string < t_mathspace > :: good ())
        {   ::std::string ss (tidy_string < t_mathspace > :: get_string ());
            nitpick nuts;
            if ((v.math_version () > math_1) && test_value < t_namedspace > (nuts, v, ss))
            {   nits.merge (nuts); return; }
            if (test_value < t_measure > (nits, v, ss)) return; }
        tidy_string < t_mathspace > :: status (s_invalid); } };

template < > struct type_master < t_mathspaceinfinity > : tidy_string < t_mathspaceinfinity >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_mathspaceinfinity > :: set_value (nits, v, s);
        if (tidy_string < t_mathspaceinfinity > :: empty ())
            nits.pick (nit_empty, ed_math_2, "3.2.2 Mathematics style attributes common to token elements", es_error, ec_type, "small, normal, big, or a measurement expected");
        else if (tidy_string < t_mathspaceinfinity > :: good ())
        {   ::std::string ss (tidy_string < t_mathspaceinfinity > :: get_string ());
            if (v.math_version () > math_1)
            {   if (compare_no_case (ss, "infinity")) return;
                nitpick nuts;
                if (test_value < t_namedspace > (nuts, v, ss))
                {   nits.merge (nuts); return; } }
            if (test_value < t_measure > (nits, v, ss)) return; }
        tidy_string < t_mathspaceinfinity > :: status (s_invalid); } };

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
                        case 'a' :  if (compare_no_case (sss, "audio/*")) continue;
                                    break;
                        case 'i' :  if (compare_no_case (sss, "image/*")) continue;
                                    break;
                        case 'v' :  if (compare_no_case (sss, "video/*")) continue;
                                    break;
                        default: break; }
                    type_master < t_mime > m;
                    m.set_value (nits, v, sss);
                    if (! m.good ()) ok = false; }
                if (ok) return; } }
        tidy_string < t_inputaccept > :: status (s_invalid); } };

template < > struct type_master < t_panose1 > : tidy_string < t_panose1 >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_panose1 > :: set_value (nits, v, s);
        if ( tidy_string < t_panose1 > :: empty ())
            nits.pick (nit_panose_1, es_error, ec_type, "a panose value consists of ten integers");
        else if ( tidy_string < t_panose1 > :: good ())
        {   ::std::string ss (tidy_string < t_panose1 > :: get_string ());
            if (ss == "10") return;
            vstr_t xs (split_by_space (ss));
            if (xs.size () != 10)
                nits.pick (nit_panose_1, es_error, ec_type, "a panose value consists of ten integers");
            else
            {   bool bad = false;
                for (auto sss : xs)
                    if (! test_value < t_integer > (nits, v, sss)) bad = true;
                if (! bad) return; } }
        tidy_string < t_panose1 > :: status (s_invalid); } };

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

template < > struct type_master < t_measure_i > : tidy_string < t_measure_i >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_measure_i > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_measure_i > :: get_string ();
        if (ss.empty ())
            nits.pick (nit_empty, es_error, ec_type, "a value is expected");
        else if (good ())
        {   if (compare_no_case ("inherit", ss)) return;
            if (test_value < t_measure > (nits, v, ss)) return; }
        tidy_string < t_measure_i > :: status (s_invalid); } };

template < > struct type_master < t_measure_ai > : tidy_string < t_measure_ai >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_measure_ai > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_measure_ai > :: get_string ();
        if (ss.empty ())
            nits.pick (nit_empty, es_error, ec_type, "a value is expected");
        else if (good ())
        {   if (compare_no_case ("auto", ss)) return;
            if (test_value < t_measure_i > (nits, v, ss)) return; }
        tidy_string < t_measure_ai > :: status (s_invalid); } };

template < > struct type_master < t_opacity > : tidy_string < t_opacity >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_opacity > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_opacity > :: get_string ();
        if (ss.empty ())
            nits.pick (nit_empty, es_error, ec_type, "a value is expected");
        else if (good ())
        {   if (compare_no_case ("inherit", ss)) return;
            if (test_value < t_normalised > (nits, v, ss)) return; }
        tidy_string < t_opacity > :: status (s_invalid); } };

template < > struct type_master < t_reals > : tidy_string < t_reals >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_reals > :: set_value (nits, v, s);
        if (tidy_string < t_reals > :: good ())
        {   vstr_t sss (split_by_charset (tidy_string < t_reals > :: get_string (), ", "));
            bool ok = true;
            for (auto arg : sss)
                if (! test_value < t_real > (nits, v, arg)) ok = false;
            if (ok) return; }
        tidy_string < t_reals > :: status (s_invalid); } };

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

template < > struct type_master < t_repeatcount > : tidy_string < t_repeatcount >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_repeatcount > :: set_value (nits, v, s);
        if (tidy_string < t_repeatcount > :: good ())
        {   ::std::string ss (tidy_string < t_repeatcount > :: get_string ());
            if (compare_no_case (ss, "indefinite")) return;
            if (test_value < t_real > (nits, v, ss)) return; }
        nits.pick (nit_dur, ed_svg_1_1, "19.2.8 Attributes to control the timing of the animation", es_error, ec_type, "a duration, 'media' or 'indefinite' is expected");
        tidy_string < t_repeatcount > :: status (s_invalid); } };

template < > struct type_master < t_sandboxen > : string_vector < t_sandboxen, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_sandboxen, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_sandboxen, sz_space > :: good ())
        {   bool allgood = true, script = false, origin = false;
            for (auto arg : string_vector < t_sandboxen, sz_space > :: get ())
            {   type_master < t_sandbox > sb;
                sb.set_value (nits, v, arg);
                if (! sb.good ()) allgood = false;
                else switch (sb.get ())
                {   case s_scripts : script = true; break;
                    case s_origin : origin = true; break;
                    default : break; } }
            if (script && origin)
                nits.pick (nit_overallowed, ed_50, "4.7.2 The iframe element", es_warning, ec_attribute, "allow-scripts and allow-same-origin, used together, defeat the sandbox");
            if (allgood) return; }
        string_vector < t_sandboxen, sz_space > :: status (s_invalid); } };

template < > struct type_master < t_itemtype > : string_vector < t_itemtype, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_itemtype, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_itemtype, sz_space > :: empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "ITEMTYPE requires a value");
            string_vector < t_itemtype, sz_space > :: status (s_invalid); }
        else if (string_vector < t_itemtype, sz_space > :: good ())
        {   bool allgood = true;
            for (auto arg : string_vector < t_itemtype, sz_space > :: get ())
                if (find_itemtype_index (nits, v, arg) == invalid_itemtype)
                    allgood = false;
            if (allgood) return; }
        string_vector < t_itemtype, sz_space > :: status (s_invalid); } };

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

template < > struct type_master < t_fontsize > : tidy_string < t_fontsize >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_fontsize > :: set_value (nits, v, s);
        if (tidy_string < t_fontsize > :: good () || tidy_string < t_fontsize > :: empty ())
        {   ::std::string ss (tidy_string < t_fontsize > :: get_string ());
            if (compare_no_case (ss, "inherit")) return;
            if (test_value < t_measure > (nits, v, ss)) return;
            tidy_string < t_fontsize > :: status (s_invalid); } } };

template < > struct type_master < t_fontsizeadjust > : tidy_string < t_fontsizeadjust >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_fontsizeadjust > :: set_value (nits, v, s);
        if (tidy_string < t_fontsizeadjust > :: good () || tidy_string < t_fontsizeadjust > :: empty ())
        {   ::std::string ss (tidy_string < t_fontsizeadjust > :: get_string ());
            if (compare_no_case (ss, "inherit")) return;
            if (compare_no_case (ss, "none")) return;
            if (test_value < t_real > (nits, v, ss)) return;
            tidy_string < t_fontsizeadjust > :: status (s_invalid); } } };

template < > struct type_master < t_svg_baselineshift > : tidy_string < t_svg_baselineshift >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (test_value < t_baselineshift > (nits, v, s) || test_value < t_measure > (nits, v, s))
            tidy_string < t_svg_baselineshift > :: status (s_good);
        else
            tidy_string < t_svg_baselineshift > :: status (s_invalid); } };

template < > struct type_master < t_svg_fontstyle_ff > : public tidy_string < t_svg_fontstyle_ff >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font style requires SVG or MathML");
        else
        {   tidy_string < t_svg_fontstyle_ff > :: set_value (nits, v, s);
            if (tidy_string < t_svg_fontstyle_ff > :: empty ())
                nits.pick (nit_fontstyle, es_error, ec_type, "font style cannot be empty");
            else if (tidy_string < t_svg_fontstyle_ff > :: good ())
            {   ::std::string ss (tidy_string < t_svg_fontstyle_ff > :: get_string ());
                if (compare_no_case (ss, "all")) return;
                ::std::string::size_type comma = ss.find (",");
                if (comma != ::std::string::npos) ss.replace (comma, comma+1, " ");
                vstr_t fs (split_by_space (ss));
                if (fs.size () == 0)
                    nits.pick (nit_fontstyle, es_error, ec_type, "font style is effectively empty");
                else if (fs.size () > 2)
                    nits.pick (nit_fontstyle, es_error, ec_type, "too many font style keywords");
                else
                {   bool bad = false;
                    for (auto sss : fs)
                        if (! test_value < t_fontnia > (nits, v, sss)) bad = true;
                    if (! bad) return; } } }
        nits.pick (nit_fontstyle, ed_svg_1_1, "20.8.3 The 'font-face' element", es_info, ec_type, "an SVG font style can be 'all', or one or two of 'normal', 'italic', 'oblique'");
        tidy_string < t_svg_fontstyle_ff > :: status (s_invalid); } };

template < > struct type_master < t_fontstretches > : public tidy_string < t_fontstretches >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font stretch requires SVG");
        else
        {   tidy_string < t_fontstretches > :: set_value (nits, v, s);
            if (tidy_string < t_fontstretches > :: empty ())
                nits.pick (nit_fontstyle, es_error, ec_type, "font stretch cannot be empty");
            else if (tidy_string < t_fontstretches > :: good ())
            {   ::std::string ss (tidy_string < t_fontstretches > :: get_string ());
                if (compare_no_case (ss, "all")) return;
                ::std::string::size_type comma = ss.find (",");
                if (comma != ::std::string::npos) ss.replace (comma, comma+1, " ");
                vstr_t fs (split_by_space (ss));
                if (fs.size () == 0)
                    nits.pick (nit_fontstyle, es_error, ec_type, "font stretch is effectively empty");
                else
                {   bool bad = false;
                    for (auto sss : fs)
                        if (! test_value < t_svg_fontstretch_ff > (nits, v, sss)) bad = true;
                    if (! bad) return; } } }
        nits.pick (nit_fontstyle, ed_svg_1_1, "20.8.3 The 'font-face' element", es_info, ec_type, "an SVG font stretch can be 'all', or one or more condensed and/or expanded values");
        tidy_string < t_fontstretches > :: status (s_invalid); } };

template < > struct type_master < t_fontvariants > : public tidy_string < t_fontvariants >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font variant requires SVG");
        else
        {   tidy_string < t_fontvariants > :: set_value (nits, v, s);
            if (tidy_string < t_fontvariants > :: empty ())
                nits.pick (nit_fontvariant, es_error, ec_type, "font variant cannot be empty");
            else if (tidy_string < t_fontvariants > :: good ())
            {   ::std::string ss (tidy_string < t_fontvariants > :: get_string ());
                ::std::string::size_type comma = ss.find (",");
                if (comma != ::std::string::npos) ss.replace (comma, comma+1, " ");
                vstr_t fs (split_by_space (ss));
                if (fs.size () == 0)
                    nits.pick (nit_fontvariant, es_error, ec_type, "font variant is effectively empty");
                else if (fs.size () > 2)
                    nits.pick (nit_fontvariant, es_error, ec_type, "too many font variant keywords");
                else
                {   bool bad = false;
                    for (auto sss : fs)
                        if (! test_value < t_svg_fontvariant_ff > (nits, v, sss)) bad = true;
                    if (! bad) return; } } }
        nits.pick (nit_fontvariant, ed_svg_1_1, "20.8.3 The 'font-face' element", es_info, ec_type, "an SVG font variant can be'normal', 'small-caps', or both of them");
        tidy_string < t_fontvariants > :: status (s_invalid); } };

template < > struct type_master < t_svg_fontweights > : public tidy_string < t_svg_fontweights >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (! v.svg ()) nits.pick (nit_svg_math, es_error, ec_type, "font weight requires SVG or MathML");
        else
        {   tidy_string < t_svg_fontweights > :: set_value (nits, v, s);
            if (tidy_string < t_svg_fontweights > :: empty ())
                nits.pick (nit_fontweight, es_error, ec_type, "font style cannot be empty");
            else if (tidy_string < t_svg_fontweights > :: good ())
            {   ::std::string ss (tidy_string < t_svg_fontweights > :: get_string ());
                if (compare_no_case (ss, "all")) return;
                ::std::string::size_type comma = ss.find (",");
                if (comma != ::std::string::npos) ss.replace (comma, comma+1, " ");
                vstr_t fs (split_by_space (ss));
                if (fs.size () == 0)
                    nits.pick (nit_fontweight, es_error, ec_type, "font style is effectively empty");
                else
                {   bool bad = false;
                    for (auto sss : fs)
                        if (! test_value < t_svg_fontweight_ff > (nits, v, sss)) bad = true;
                    if (! bad) return; } } }
        nits.pick (nit_fontweight, ed_svg_1_1, "20.8.3 The 'font-face' element", es_info, ec_type, "an SVG font weight can be 'all', or one or more of 'normal', 'bold', and / or specific weights");
        tidy_string < t_svg_fontweights > :: status (s_invalid); } };

template < > struct type_master < t_svg_transform > : tidy_string < t_svg_transform >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_svg_transform > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_svg_transform > :: get_string ();
        if (s.empty ())
            nits.pick (nit_empty, es_error, ec_type, "SVG:TRANSFORM requires a value");
        else if (good ())
        {   if (compare_no_case ("none", ss)) return;
            if (test_value < t_transform > (nits, v, ss)) return; }
        tidy_string < t_svg_transform > :: status (s_invalid); } };

template < > struct type_master < t_svg_values > : tidy_string < t_svg_values >
{   vdbl_t value_;
    void swap (type_master < t_svg_values >& t)
    {   value_.swap (t.value_);
        tidy_string < t_svg_values >::swap (t); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_svg_values > :: set_value (nits, v, s);
        if (tidy_string < t_svg_values > :: good ())
        {   vstr_t ss (split_by_charset (tidy_string < t_svg_values > :: get_string (), ";"));
            if (ss.size () > 0)
            {   bool ok = true;
                for (auto sss : ss)
                    if (! test_value < t_real > (nits, v, sss))
                        ok = false;
                if (ok) return; } }
        nits.pick (nit_svg_values, ed_svg_1_1, "19.2.9 Attributes that define animation values over time", es_error, ec_attribute, "a semi-colon separated series of numbers expected");
        tidy_string < t_svg_values > :: status (s_invalid); }
    void reset ()
    {   value_.clear ();
        tidy_string < t_svg_values > :: reset (); }
    static ::std::string default_value () { return ""; }
    ::std::string get () const { return get_string (); } };

template < > struct type_master < t_normalisations > : tidy_string < t_normalisations >
{   vdbl_t value_;
    void swap (type_master < t_normalisations >& t)
    {   value_.swap (t.value_);
        tidy_string < t_normalisations >::swap (t); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_normalisations > :: set_value (nits, v, s);
        if (tidy_string < t_normalisations > :: good ())
        {   vstr_t ss (split_by_charset (tidy_string < t_normalisations > :: get_string (), ";"));
            if (ss.size () > 0)
            {   bool ok = true;
                for (auto sss : ss)
                    if (! test_value < t_normalisations > (nits, v, sss))
                        ok = false;
                if (ok) return; } }
        nits.pick (nit_svg_values, ed_svg_1_1, "19.2.9 Attributes that define animation values over time", es_error, ec_attribute, "a semi-colon separated series of numbers expected");
        tidy_string < t_normalisations > :: status (s_invalid); }
    void reset ()
    {   value_.clear ();
        tidy_string < t_normalisations > :: reset (); }
    static ::std::string default_value () { return ""; }
    ::std::string get () const { return get_string (); } };

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
    float density_ = 0.0;
    void swap (type_master < t_imcastr >& t)
    {   ::std::swap (u_, t.u_);
        ::std::swap (width_, t.width_);
        ::std::swap (density_, t.density_);
        tidy_string < t_imcastr > :: swap (t); }
    bool parse (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_imcastr > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_imcastr > :: get_string ();
        if (! string_value < t_imcastr > :: good ()) return false;
        vstr_t args (split_by_space (ss));
        if ((args.size () == 0) || (args.size () > 2))
        {   nits.pick (nit_bad_srcset, ed_July2020, "4.8.4.2.1 Srcset attributes", es_error, ec_attribute,
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
                    if (width_ > 0) return true;
                    break;
                case 'x' :
                case 'X' :
                    density_ = lexical < float > :: cast (args.at (1).substr (0, pos-1));
                    if (density_ > 0.0) return true;
                    break;
                default : break; }
        nits.pick (nit_bad_srcset, ed_July2020, "4.8.4.2.1 Srcset attributes", es_error, ec_attribute,
            quote (args.at (1)), ": the second part of a SRCSET, if present, is a positive integer width immediately followed by 'w', or a positive real density immediately followed by 'x'");
        return false; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) tidy_string < t_imcastr > :: status (s_good);
        else tidy_string < t_imcastr > :: status (s_invalid); }
    void reset ()
    {   u_.reset (); width_ = 0; density_ = 0.0;
        tidy_string < t_imcastr > :: reset (); }
    static ::std::string default_value () { return ::std::string (); } };

template < > struct type_master < t_rotate_anim > : tidy_string < t_rotate_anim >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_rotate_anim > :: set_value (nits, v, s);
        if (tidy_string < t_rotate_anim > :: good ())
        {   ::std::string ss (tidy_string < t_rotate_anim > :: get_string ());
            if (compare_no_case (ss, "auto")) return;
            if (compare_no_case (ss, "auto-reverse")) return;
            if (test_value < t_real > (nits, v, ss)) return; }
        nits.pick (nit_rotate, ed_svg_1_1, "19.2.14 The 'animateMotion' element", es_error, ec_attribute, "expected 'auto', 'auto-reverse', or a number");
        tidy_string < t_rotate_anim > :: status (s_invalid); } };

template < > struct type_master < t_srcset > : tidy_string < t_srcset >
{   typedef ::std::vector < type_master < t_imcastr > > vix_t;
    vix_t value_;
    void swap (type_master < t_srcset >& t)
    {   value_.swap (t.value_);
        tidy_string < t_srcset >::swap (t); }
    bool parse (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_srcset > :: set_value (nits, v, s);
        const ::std::string& ss = tidy_string < t_srcset > :: get_string ();
        if (tidy_string < t_srcset > :: empty ())
        {   nits.pick (nit_bad_srcset, ed_July2020, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "a SRCSET attribute cannot be empty");
            return false; }
        if (! tidy_string < t_srcset > :: good ()) return false;
        vstr_t xs (split_by_charset (ss, ","));
        value_.resize (xs.size ());
        bool res = true;
        ::std::size_t max = xs.size ();
        for (::std::size_t n = 0; n < max; ++n)
        {   value_ [n].set_value (nits, v, xs [n]);
            if (value_ [n].invalid ()) res = false; }
        if (max > 1)
            for (::std::size_t x = 0; x < max - 1; ++x)
                for (::std::size_t y = x+1; y < max; ++y)
                {   if ((value_ [x].width_ > 0) && (value_ [x].width_ == value_ [y].width_))
                    {   nits.pick (nit_bad_srcset, ed_July2020, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "each width in a SRCSET attribute must be unique (", value_ [x].width_, " is repeated)");
                        return false; }
                    if ((value_ [x].density_ > 0.0) && (value_ [x].density_ == value_ [y].density_))
                    {   nits.pick (nit_bad_srcset, ed_July2020, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "each density in a SRCSET attribute must be unique");
                        return false; } }
        return res; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if (parse (nits, v, s)) string_value < t_srcset > :: status (s_good);
        else
        {   nits.pick (nit_bad_srcset, ed_July2020, "4.8.4.2.1 Srcset attributes", es_error, ec_type, "SRCSET takes a comma separated list of values, each a url then optionally a space with either a width or a density");
            tidy_string < t_srcset > :: status (s_invalid); } }
    void reset ()
    {   value_.clear ();
        tidy_string < t_srcset > :: reset (); } };
