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

e_status set_css_background_attachments_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box)
{   if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
    else
    {   if (v.css_module (c_background_border) < 3)
        {   type_master < t_css_background_attachment > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; }
        else
        {   type_master < t_css_background_attachment_3 > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; } }
    return s_invalid; }

e_status set_css_background_position_3_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box)
{   if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
    else
    {   if (v.css_module (c_background_border) < 3)
        {   type_master < t_css_background_position > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; }
        else
        {   type_master < t_css_background_positions > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; } }
    return s_invalid; }

e_status set_css_background_repeat_3_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box)
{   if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
    else
    {   if (v.css_module (c_background_border) < 3)
        {   type_master < t_css_background_repeat > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; }
        else if (v.css_module (c_background_border) >= 4)
        {   type_master < t_css_repeat_styles > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; }
        else
        {   type_master < t_css_background_repeats > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; } }
    return s_invalid; }

e_status set_css_background_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
    else
    {   if (v.css_module (c_background_border) < 3)
        {   type_master < t_css_background_0 > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; }
        else
        {   type_master < t_svg_src > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; } }
    return s_invalid; }

e_status set_css_col_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "a colour expected");
    else
    {   nitpick nuts, nets, nots, nats;
        const int m = (v.css_module (c_hdr) > 0) ? 5 : v.css_module (c_colour);
        switch (m)
        {   case 6 :
            case 5 :
                if (test_value < t_css_colour_5 > (nuts, v, s))
                {   nits.merge (nuts);
                    return s_good; }
                FALLTHROUGH;
            case 4 :
                if (test_value < t_css_colour_4 > (nuts, v, s))
                {   nits.merge (nuts);
                    return s_good; }
                FALLTHROUGH;
            case 3 :
                if (test_value < t_css_colour_3 > (nets, v, s))
                {   nits.merge (nets);
                    return s_good; }
                FALLTHROUGH;
            default :
                if (test_value < t_css_colour > (nots, v, s))
                {   nits.merge (nots);
                    return s_good; }
                if (test_value < t_colour > (nats, v, s))
                {   nits.merge (nats);
                    return s_good; }
                if (compare_no_case (s, "inherit"))
                    return s_good;
                break; }
        nits.pick (nit_css_colour, es_error, ec_css, quote (s), " is invalid in CSS ", v.long_css_version_name ());
        if (context.extra () || context.tell (es_debug))
        {   nits.merge (nuts);
            nits.merge (nets);
            nits.merge (nots);
            nits.merge (nats); } }
    return s_invalid; }

e_status set_css_cmx_value_0 (nitpick& nits, const html_version& v, const ::std::string& ss)
{   e_status res = s_invalid;
    const ::std::string s (trim_the_lot_off (ss));
    if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "arguments required");
    else if (v.css_module (c_colour) < 5)
        nits.pick (nit_css_version, es_error, ec_css, "color-mix () requires CSS Colour 5");
    else if (! s.empty ())
    {   vstr_t vr (split_by_space (s));
        if (vr.size () > 1)
            if (! compare_no_case (vr.at (0), "in"))
                nits.pick (nit_gradient, es_error, ec_type, vr.at (0), " is not 'in'");
            else
            {   res = s_good;
                for (::std::size_t i = 1; i < vr.size (); ++i)
                {   nitpick gnats, nets, knots, nuts;
                    const ::std::string& vs (vr.at (i));
                    if (test_value < t_css_rect > (gnats, v, vs))
                        nits.merge (gnats);
                    else if (test_value < t_css_polar > (nets, v, vs))
                        nits.merge (nets);
                    else if (test_value < t_css_id > (knots, v, vs))
                        nits.merge (knots);
                    else if (test_value < t_css_hue_interpolation > (nuts, v, vs))
                        nits.merge (nuts);
                    else if (compare_no_case ("hue", vs))
                        break;
                    else
                    {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid color-mix syntax");
                        if (context.extra ())
                        {   nits.merge (gnats);
                            nits.merge (nets);
                            nits.merge (knots);
                            nits.merge (nuts); }
                        res = s_invalid; } } } }                        
    return res; }

e_status set_css_conic_value_0 (nitpick& nits, const html_version& v, const ::std::string& ss)
{   e_status res = s_empty;
    const ::std::string s (trim_the_lot_off (ss));
    if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "arguments required");
    else if (v.css_module (c_image) < 4)
        nits.pick (nit_css_version, es_error, ec_css, "Conic functions require CSS Images 4");
    else
    {   res = s_good;
        if (! s.empty ())
        {   vstr_t vr (split_by_space (s));
            int step = 0;
            for (auto vs : vr)
            {   nitpick gnats, nets, knots, nuts;
                if (step < 3)
                {   if (compare_no_case (vs, "from"))
                    {   step = 1; continue; }
                    if (compare_no_case (vs, "at"))
                    {   step = 2; continue; }
                    if (compare_no_case (vs, "in"))
                    {   step = 3; continue; }
                    if (step == 0)
                    {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for first parameter in conic gradient function (0)");
                        res = s_invalid;
                        continue; } }
                switch (step)
                {   case 1 :
                        if (vs != "0")
                            if (! test_value < t_angle > (nits, v, vs))
                                res = s_invalid;
                        break;
                    case 2 :
                    {   nitpick gnats1, nets1, knots1;
                        if (test_value < t_css_length_percent > (gnats1, v, vs))
                            nits.merge (gnats1);
                        else if (test_value < t_css_ellipse_pos > (nets1, v, vs))
                            nits.merge (nets1);
                        else if (test_value < t_ces > (knots1, v, vs))
                            nits.merge (knots1);
                        else
                        {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for first parameter in conic gradient function (1)");
                            if (context.extra ())
                            {   nits.merge (gnats1);
                                nits.merge (nets1);
                                nits.merge (knots1); }
                            res = s_invalid; }
                        break; }
                    case 3 :
                    {   nitpick gnats2, nets2, knots2, nuts2;
                        if (test_value < t_css_rgb_xyz > (gnats2, v, vs))
                            nits.merge (gnats2);
                        else if (test_value < t_css_polar > (nets2, v, vs))
                            nits.merge (nets2);
                        else if (test_value < t_css_id > (knots2, v, vs))
                            nits.merge (knots2);
                        else if (test_value < t_css_hue_interpolation > (nuts2, v, vs))
                            nits.merge (nuts2);
                        else if (compare_no_case ("hue", vs))
                            break;
                        else
                        {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for first parameter in conic gradient function (2)");
                            if (context.extra ())
                            {   nits.merge (gnats2);
                                nits.merge (nets2);
                                nits.merge (knots2);
                                nits.merge (nuts2); }
                            res = s_invalid; } }
                    default :
                        nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for first parameter in conic gradient function (3)");
                        return s_invalid; } } } }
    return res; }

e_status set_css_conic_value_n (nitpick& nits, const html_version& v, const ::std::string& ss)
{   e_status res = s_empty;
    const ::std::string s (trim_the_lot_off (ss));
    if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "arguments required");
    else if (v.css_module (c_image) < 4)
        nits.pick (nit_css_version, es_error, ec_css, "Conic functions require CSS Images 4");
    else
    {   res = s_good;
        vstr_t vr (split_by_space (s));
        for (auto vs : vr)
        {   nitpick gnats, nets;
            if (test_value < t_css_col > (gnats, v, vs))
                nits.merge (gnats);
            else if (test_value < t_angle_p > (nets, v, vs))
                nits.merge (nets);
            else if (vs != "0")
            {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for subsequent parameter in conic function");
                if (context.extra ())
                {   nits.merge (gnats);
                    nits.merge (nets); }
                res = s_invalid; } } }
    return res; }

e_status set_css_display_1_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ()) nits.pick (nit_key, es_error, ec_type, "display cannot be empty");
    nitpick nuts;
    if ((v.css_module (c_display) >= 3) || (v.css_module (c_math_core) >= 3))
    {   if (test_value < t_css_display_3 > (nuts, v, s))
        {   nits.merge (nuts); return s_good; } }
    if (test_value < t_css_display > (nits, v, s)) return s_good;
    return s_invalid; }

e_status set_css_font_size_4_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ()) nits.pick (nit_key, es_error, ec_type, "font-size cannot be empty");
    else
    {   if ((context.css_module (c_font) >= 4) && compare_no_case (s, "math")) return s_good;
        if (test_value < t_css_font_size > (nits, v, s)) return s_good; }
    return s_invalid; }

e_status set_css_font_size_adjust_value (nitpick& nits, const html_version& v, const vstr_t& vs)
{   if (vs.empty ()) nits.pick (nit_key, es_error, ec_type, "font-size-adjust cannot be empty");
    else
    {   const ::std::size_t len (vs.size ());
        PRESUME (len > 0, __FILE__, __LINE__);  
        if (v.css_module (c_font) < 5)
        {   if (len > 1) nits.pick (nit_css_syntax, es_warning, ec_css, "ignoring unexpected junk following ", quote (vs.at (0)), " (2)"); 
            if (test_value < t_real_ni > (nits, v, vs.at (0))) return s_good; }
        else if (compare_no_case (vs.at (0), "none"))
        {   if (len > 1) nits.pick (nit_css_syntax, es_warning, ec_css, "ignoring unexpected junk following ", quote (vs.at (0)), " (3)"); 
            return s_good; }
        else
        {   ::std::size_t pos = 0;
            nitpick nuts;
            if (test_value < t_css_font_size_adjust_e > (nuts, v, vs.at (0)))
            {   nits.merge (nuts);
                ++pos; }
            if ((len > pos) && compare_no_case (vs.at (pos), "from-font"))
                if (len == ++pos) return s_good;
            if ((len > pos) && test_value < t_real > (nits, v, vs.at (pos)))
            {   if (len > ++pos) nits.pick (nit_css_syntax, es_warning, ec_css, "ignoring unexpected junk following ", quote (vs.at (pos)), " (4)"); 
                return s_good; }
            nits.pick (nit_css_syntax, es_error, ec_css, "number expected after ", quote (vs.at (pos-1))); } }
    return s_invalid; }

e_status set_css_gap_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
    else if (v.css_module (c_gap) >= 3)
    {   if (test_value < t_css_gap_3 > (nits, v, s))  return s_good; }
    else
    {   if (test_value < t_css_gap > (nits, v, s))  return s_good; }
    return s_invalid; }

e_status set_css_lang_value (nitpick& nits, const html_version& v, const vstr_t& vs)
{   if (vs.empty ())
        nits.pick (nit_bad_itemprop, es_error, ec_type, "lang() requires a parameter");
    else
    {   bool ok = true;
        for (auto t : vs)
            if (! test_value < t_css_lang > (nits, v, t))
                ok = false;
        if (ok) return s_good; }
    return s_invalid; }

e_status set_css_linear_value_0 (nitpick& nits, const html_version& v, const ::std::string& ss)
{   e_status res = s_empty;
    const ::std::string s (trim_the_lot_off (ss));
    if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "arguments required");
    else if (v.css_module (c_image) < 3)
        nits.pick (nit_css_version, es_error, ec_css, "Radial functions require CSS Images 3");
    else
    {   res = s_good;
        if (! s.empty ())
        {   vstr_t vr (split_by_space (s));
            int step = 0;
            for (auto vs : vr)
            {   nitpick gnats;
                if (step == 0)
                    if (test_value < t_css_angle > (gnats, v, vs))
                    {   nits.merge (gnats); continue; }
                    if (compare_no_case (vs, "0")) continue;
                if (step < 2)
                {   if (compare_no_case (vs, "to"))
                    {   step = 1; continue; }
                    if (compare_no_case (vs, "in"))
                    {   step = 2; continue; }
                    if (step == 0)
                    {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for first parameter in linear gradient function (0)");
                        if (context.extra ())
                            nits.merge (gnats);
                        res = s_invalid;
                        continue; } }
                if (step == 1)
                {   if (! test_value < t_blrt > (nits, v, vs))
                        res = s_invalid;
                    continue; }
                PRESUME (step == 2, __FILE__, __LINE__);
                nitpick gnats2, nets2, knots2, nuts2;
                if (test_value < t_css_rect > (gnats2, v, vs))
                    nits.merge (gnats2);
                else if (test_value < t_css_polar > (nets2, v, vs))
                    nits.merge (nets2);
                else if (test_value < t_css_id > (knots2, v, vs))
                    nits.merge (knots2);
                else if (test_value < t_css_hue_interpolation > (nuts2, v, vs))
                    nits.merge (nuts2);
                else if (compare_no_case ("hue", vs))
                    break;
                else
                {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for first parameter in linear gradient function (2)");
                    if (context.extra ())
                    {   nits.merge (gnats2);
                        nits.merge (nets2);
                        nits.merge (knots2);
                        nits.merge (nuts2); }
                    res = s_invalid; } } } }
    return res; }

e_status set_css_linear_value_n (nitpick& nits, const html_version& v, const ::std::string& s)
{   return set_css_radial_value_n (nits, v, s); }

bool pos_test (nitpick& nits, const html_version& v, bool& b, ::std::string& pos)
{   if (pos.empty ()) return true;
    nitpick nuts;
    const bool res = test_value < t_position > (nuts, v, pos);
    if (! res) nits.pick (nit_mask, es_error, ec_css, quote (pos), " is unrecognised (1)");
    else
    {   if (b) nits.pick (nit_mask, es_error, ec_css, quote (pos), ": already had a position"); 
        nits.merge (nuts);
        b = true; }
    pos.clear ();
    return res; }   

e_status set_css_mask_value (nitpick& nits, const html_version& v, const ::std::string& sss)
{   if (sss.empty ()) nits.pick (nit_empty, es_error, ec_type, "a mask cannot be empty");
    else if (context.css_module (c_masking) < 3)
    {   if (test_value < t_urifn_ni > (nits, v, sss)) return s_good; }
    else
    {   nitpick gnats;
        ::std::string gs (sss);
        if (test_value < t_font_enum > (gnats, v, gs))
        {   nits.merge (gnats);
            return s_good; }
        vstr_t ss (split_by_space (gs));
        ::std::string pos_pos;
        PRESUME (! ss.empty (), __FILE__, __LINE__);
        bool res = true, ref = false, pos = false, bg = false, must_bg = false, rep = false, geo1 = false, geo2 = false, comp = false, mode = false;
        for (auto s : ss)
        {   nitpick nuts, knits, goats, nots, nets;
            if (s == "/")
            {   if (! pos_pos.empty ()) res = pos_test (nits, v, pos, pos_pos) && res;
                else
                {   nits.pick (nit_mask, es_error, ec_css, quote (s), " must follow a position");
                    res = false; }
                if (bg)
                {   nits.pick (nit_mask, es_error, ec_css, quote (s), " is repeated");
                    res = false; }
                must_bg = true; }
            else if (must_bg)
            {   test_value < t_css_background_size > (nits, v, s);
                bg = true; must_bg = false; }
            else if (compare_no_case (s, "no-clip"))
            {   if (! pos_test (nits, v, pos, pos_pos)) res = false;
                if (geo2)
                {   nits.pick (nit_mask, es_error, ec_css, quote (s), ": already had a no-clip andor both boxen");
                    res = false; }
                geo2 = true; }
            else if (test_value < t_css_mask_ref > (nuts, v, s))
            {   if (! pos_test (nits, v, pos, pos_pos)) res = false;
                if (ref)
                {   nits.pick (nit_mask, es_error, ec_css, quote (s), ": already had a mask image");
                    res = false; }
                nits.merge (nuts);
                ref = true; }
            else if (test_value < t_css_background_repeat_3 > (knits, v, s))
            {   if (! pos_test (nits, v, pos, pos_pos)) res = false;
                if (rep)
                {   nits.pick (nit_mask, es_error, ec_css, quote (s), ": already had a repeat style");
                    res = false; }
                nits.merge (knits);
                rep = true; }
            else if (test_value < t_css_clip_path_shape > (goats, v, s))
            {   if (! pos_test (nits, v, pos, pos_pos)) res = false;
                if (geo1 && geo2)
                {   nits.pick (nit_mask, es_error, ec_css, quote (s), ": already had both boxen");
                    res = false; }
                else if (! geo1) geo1 = true; else geo2 = true;
                nits.merge (goats); }
            else if (test_value < t_css_composite > (nots, v, s))
            {   if (! pos_test (nits, v, pos, pos_pos)) res = false;
                if (comp)
                {   nits.pick (nit_mask, es_error, ec_css, quote (s), ": already had a mask composite");
                    res = false; }
                nits.merge (nots);
                comp = true; }
            else if (test_value < t_css_masking_mode > (nets, v, s))
            {   if (! pos_test (nits, v, pos, pos_pos)) res = false;
                if (mode)
                {   nits.pick (nit_mask, es_error, ec_css, quote (s), ": already had a mask mode");
                    res = false; }
                nits.merge (nets);
                mode = true; }
            else
            {   if (! pos_pos.empty ()) pos_pos += ' ';
                pos_pos += s; } }
        if (! pos_test (nits, v, pos, pos_pos)) res = false;
        if (res) return s_good; }
    return s_invalid; }

bool bmtest (nitpick& nits, const html_version& v, ::std::string& buf, bool& slice, bool& sliced, bool& width, bool& widened, bool& must_width, bool& outset, bool& outsetted, bool& must_outset)
{   sliced = false;
    if (buf.empty ()) return true;
    bool res = true;
    nitpick nuts;
    if (must_width)
    {   if (width)
        {   nits.pick (nit_mask_border, es_error, ec_css, quote (buf), ": already had a border width");
            res = false; } 
        if (! test_value < t_css_mask_border_widths > (nits, v, buf))    
        {   nits.pick (nit_mask_border, es_error, ec_css, quote (buf), ": bad border width");
            res = false; }
        must_width = outsetted = sliced = false;
        width = widened = true; }
    else if (must_outset)
    {   if (outset)
        {   nits.pick (nit_mask_border, es_error, ec_css, quote (buf), ": already had a border outset");
            res = false; } 
        if (! test_value < t_css_mask_border_outsets > (nits, v, buf))    
        {   nits.pick (nit_mask_border, es_error, ec_css, quote (buf), ": bad border outset");
            res = false; }
        must_outset = widened = sliced = false;
        outset = outsetted = true; }
    else if (! test_value < t_css_mask_border_slice > (nuts, v, buf))
    {   nits.pick (nit_mask_border, es_error, ec_css, quote (buf), " is unrecognised (2)");
        res = false; }
    else
    {   if (slice)
        {   nits.pick (nit_mask_border, es_error, ec_css, quote (buf), ": already sliced");
            res = false; } 
        nits.merge (nuts);
        buf.clear ();
        widened = outsetted = false;
        slice = sliced = true; }
    buf.clear ();
    return res; }   

e_status set_css_mask_border_value (nitpick& nits, const html_version& v, const ::std::string& sss)
{   if (sss.empty ()) nits.pick (nit_empty, es_error, ec_type, "a mask border cannot be empty");
    else
    {   nitpick gnats;
        vstr_t ss (split_by_space (sss));
        ::std::string buf;
        PRESUME (! ss.empty (), __FILE__, __LINE__);
        bool res = true, border = false, rep = false, mode = false,
                slice = false, sliced = false,
                width = false, widened = false, must_width = false,
                outset = false, outsetted = false, must_outset = false;
        for (auto s : ss)
        {   nitpick nuts, knits, goats, nots, nets;
            if (test_value < t_css_mask_border_mode > (nuts, v, s))
            {   if (! bmtest (nits, v, buf, slice, sliced, width, widened, must_width, outset, outsetted, must_outset)) res = false;
                if (mode)
                {   nits.pick (nit_mask_border, es_error, ec_css, quote (s), ": already had a mode");
                    res = false; }
                nits.merge (nuts);
                mode = true; }
            else if (test_value < t_css_mask_border_repeat > (knits, v, s))
            {   if (! bmtest (nits, v, buf, slice, sliced, width, widened, must_width, outset, outsetted, must_outset)) res = false;
                if (rep)
                {   nits.pick (nit_mask_border, es_error, ec_css, quote (s), ": already had a repeat");
                    res = false; }
                nits.merge (knits);
                rep = true; }
            else if (test_value < t_css_val_fn_n > (nots, v, s))
            {   if (! bmtest (nits, v, buf, slice, sliced, width, widened, must_width, outset, outsetted, must_outset)) res = false;
                if (border)
                {   nits.pick (nit_mask_border, es_error, ec_css, quote (s), ": already had a source");
                    res = false; }
                nits.merge (nots);
                border = true; }
            else if (s == "/")
            {   if (! bmtest (nits, v, buf, slice, sliced, width, widened, must_width, outset, outsetted, must_outset)) res = false;
                if (sliced) must_width = true;
                else if (widened) must_outset = true;
                else nits.pick (nit_mask_border, es_error, ec_css, quote (s), " is unexpected"); }
            else 
            {   if (! buf.empty ()) buf += ' ';
                buf += s; } }
        if (! bmtest (nits, v, buf, slice, sliced, width, widened, must_width, outset, outsetted, must_outset)) res = false;
        if (res) return s_good; }
    return s_invalid; }

e_status set_css_font_style_a_value (nitpick& nits, const html_version& v, const vstr_t& vs)
{   if (vs.empty ()) nits.pick (nit_key, es_error, ec_type, "font-style cannot be empty");
    else
    {   type_master < t_css_font_style > cf;
        cf.set_value (nits, v, vs.at (0));
        if (cf.good ())
        {   if (vs.size () == 1) return s_good;
            if (compare_no_case (vs.at (0), "oblique"))
            {   if (vs.size () > 2) nits.pick (nit_css_syntax, es_warning, ec_css, "junk found after ", quote (vs.at (1)));
                if (test_value < t_angle > (nits, v, vs.at (1))) return s_good; }
            else nits.pick (nit_css_syntax, es_warning, ec_css, "junk found after ", quote (vs.at (0))); } }
    return s_invalid; }

e_status set_css_list_style_type_cs_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   nitpick nuts;
    if (test_value < t_css_list_style_type > (nuts, v, s))
    {   nits.merge (nuts);
        return s_good; }
    if ((v.css_module (c_counter_style) >= 3) || (v.css_module (c_list_counter) >= 3))
    {   if (! test_value < t_css_counter_style_name > (nuts, v, s))
            nits.pick (nit_counter_style, es_comment, ec_css, quote (s), ": not a recognised counter style or list value");
        return s_good; }
    nits.merge (nuts);
    return s_invalid; }

e_status set_css_offset_value (nitpick& nits, const html_version& v, const ::std::string& sss)
{   vstr_t ss (split_by_space (sss));
    if (ss.empty ()) return s_empty;
    typedef enum { of_position, of_path, of_distance, of_rotate, of_anchor, of_over } offset_state;
    offset_state state = of_position;
    bool slashed = false;
    e_status jolly = s_good;
    for (auto s : ss)
    {   nitpick nuts, gnats, knots, nets;
        if (s == "/")
            if (slashed)
            {   nits.pick (nit_naughty_offset, es_error, ec_type, "additional slash unexpected");
                jolly = s_invalid; }
            else
            {   slashed = true;
                state = of_anchor; }
        else switch (state)
        {   case of_position :
                if (test_value < t_css_position_a > (nuts, v, s))
                {   nits.merge (nuts); state = of_path; break; }
                FALLTHROUGH;
            case of_path :
                if (test_value < t_css_offset_path_n > (gnats, v, s))
                {   nits.merge (gnats); state = of_distance; break; }
                FALLTHROUGH;
            case of_distance :
                if (test_value < t_css_length > (knots, v, s))
                {   nits.merge (knots); state = of_rotate; break; }
                FALLTHROUGH;
            case of_rotate :
                if (test_value < t_angle_ar > (nets, v, s))
                {   nits.merge (nets); state = of_over; break; }
                jolly = s_invalid;
#ifdef DEBUG
                nits.merge (nuts);
                nits.merge (gnats);
                nits.merge (knots);
                nits.merge (nets);
#endif // DEBUG
                nits.pick (nit_naughty_offset, es_error, ec_type, quote (s), " is not an OFFSET value");
                break;
            case of_anchor :
                if (! test_value < t_css_position_a > (nits, v, s)) jolly = s_invalid;
                state = of_over;
                break;
            case of_over :
                nits.pick (nit_naughty_offset, es_error, ec_type, quote (s), ": unexpected additional value");
                jolly = s_invalid;
                break;
            default :
                GRACEFUL_CRASH (__FILE__, __LINE__);
                break; } }
    return jolly; }    

e_status set_css_quotes_3_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   nitpick nuts;
    if (context.css_module (c_generated_content) >= 3)
        if (test_value < t_css_quotes > (nuts, v, s))
        {   nits.merge (nuts); return s_good; }
    if (test_value < t_4string_ni > (nits, v, s)) return s_good;
    nits.merge (nuts);
    return s_invalid; }

e_status set_css_radial_value_0 (nitpick& nits, const html_version& v, const ::std::string& ss)
{   e_status res = s_empty;
    const ::std::string s (trim_the_lot_off (ss));
    if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "arguments required");
    else if (v.css_module (c_image) < 3)
        nits.pick (nit_css_version, es_error, ec_css, "Radial functions require CSS Images 3");
    else
    {   res = s_good;
        if (! s.empty ())
        {   vstr_t vr (split_by_space (s));
            int step = 0;
            for (auto vs : vr)
            {   nitpick gnats, nets, knots, nuts;
                if (step == 0)
                {   if (test_value < t_circle_ellipse > (gnats, v, vs))
                    {   nits.merge (gnats); continue; }
                    if (test_value < t_css_radial_size > (nets, v, vs))
                    {   nits.merge (nets); continue; }
                    if (test_value < t_css_length_inf > (knots, v, vs))
                    {   nits.merge (knots); continue; }
                    if (test_value < t_css_length_percent_inf_a > (nuts, v, vs))
                    {   nits.merge (nuts); continue; } }
                if (step < 2)
                {   if (compare_no_case (vs, "at"))
                    {   step = 1; continue; }
                    if (compare_no_case (vs, "in"))
                    {   step = 2; continue; }
                    if (step == 0)
                    {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for first parameter in radial gradient function (0)");
                        if (context.extra ())
                        {   nits.merge (gnats);
                            nits.merge (nets);
                            nits.merge (knots);
                            nits.merge (nuts); }
                        res = s_invalid;
                        continue; } }
                if (step == 1)
                {   nitpick gnats1, nets1, knots1;
                    if (test_value < t_css_length_percent > (gnats1, v, vs))
                        nits.merge (gnats1);
                    else if (test_value < t_css_ellipse_pos > (nets1, v, vs))
                        nits.merge (nets1);
                    else if (test_value < t_ces > (knots1, v, vs))
                        nits.merge (knots1);
                    else
                    {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for first parameter in radial gradient function (1)");
                        if (context.extra ())
                        {   nits.merge (gnats1);
                            nits.merge (nets1);
                            nits.merge (knots1); }
                        res = s_invalid; }
                    continue; }
                PRESUME (step == 2, __FILE__, __LINE__);
                nitpick gnats2, nets2, knots2, nuts2;
                if (test_value < t_css_rgb_xyz > (gnats2, v, vs))
                    nits.merge (gnats2);
                else if (test_value < t_css_polar > (nets2, v, vs))
                    nits.merge (nets2);
                else if (test_value < t_css_id > (knots2, v, vs))
                    nits.merge (knots2);
                else if (test_value < t_css_hue_interpolation > (nuts2, v, vs))
                    nits.merge (nuts2);
                else if (compare_no_case ("hue", vs))
                    break;
                else
                {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for first parameter in radial gradient function (2)");
                    if (context.extra ())
                    {   nits.merge (gnats2);
                        nits.merge (nets2);
                        nits.merge (knots2);
                        nits.merge (nuts2); }
                    res = s_invalid; } } } }
    return res; }

e_status set_css_radial_value_n (nitpick& nits, const html_version& v, const ::std::string& ss)
{   e_status res = s_empty;
    const ::std::string s (trim_the_lot_off (ss));
    if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "arguments required");
    else if (v.css_module (c_image) < 3)
        nits.pick (nit_css_version, es_error, ec_css, "Radial functions require CSS Images 3");
    else
    {   res = s_good;
        vstr_t vr (split_by_space (s));
        for (auto vs : vr)
        {   nitpick gnats, nets;
            if (test_value < t_css_col > (gnats, v, vs))
                nits.merge (gnats);
            else if (test_value < t_css_length_percent > (nets, v, vs))
                nits.merge (nets);
            else
            {   nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid syntax for subsequent parameter in gradient function");
                if (context.extra ())
                {   nits.merge (gnats);
                    nits.merge (nets); }
                res = s_invalid; } } }
    return res; }

e_status set_css_ray_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   e_status res = s_empty;
    const ::std::string s (trim_the_lot_off (ss));
    if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "arguments required");
    else if (v.css_module (c_motion_path) < 3)
        nits.pick (nit_css_version, es_error, ec_css, "Ray require CSS Motion Path");
    else
    {   res = s_good;
        if (! s.empty ())
        {   vstr_t vr (split_by_space (s));
            bool at = false, angled = false;
            for (auto vs : vr)
            {   nitpick gnats, nets,  gnats1, nets1, knots1;
                if (at)
                {   if (test_value < t_css_length_percent > (gnats1, v, vs))
                    {   nits.merge (gnats1); continue; }
                    if (test_value < t_css_ellipse_pos > (nets1, v, vs))
                    {   nits.merge (nets1); continue; }
                    if (test_value < t_ces > (knots1, v, vs))
                    {   nits.merge (knots1); continue; }
                    at = false; }
                else if (compare_no_case (vs, "at"))
                {   at = true; continue; }
                if (compare_no_case (vs, "contain")) continue;
                if (test_value < t_angle > (gnats, v, vs))
                {   nits.merge (gnats); angled = true; continue; }
                if (test_value < t_css_ray_size > (nets, v, vs))
                {   nits.merge (nets); continue; }
                nits.pick (nit_gradient, es_error, ec_type, quote (vs), ": invalid ray () parameter");
                if (context.extra ())
                {   nits.merge (gnats);
                    nits.merge (nets);
                    nits.merge (gnats1);
                    nits.merge (nets1);
                    nits.merge (knots1); }
                res = s_invalid; }
            if (! angled)
            {   nits.pick (nit_gradient, es_error, ec_type, quote (s), ": ray () require an angle");
                res = s_invalid; } } }
    return res; }

e_status set_css_shape_value_0 (nitpick& nits, const html_version& v, const ::std::string& ss)
{   e_status res = s_invalid;
    const ::std::string s (trim_the_lot_off (ss));
    if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "arguments required");
    else if (v.css_module (c_shape) < 3)
        nits.pick (nit_css_version, es_error, ec_css, "Shape functions require CSS Shapes");
    else
    {   res = s_good;
        if (! s.empty ())
        {   vstr_t vr (split_by_space (s));
            bool step = true, fillrule = false;
            ::std::string pos;
            for (auto vs : vr)
            {   if (step)
                {   if (compare_no_case (vs, "from"))
                    {   step = false; continue; }
                    if (compare_no_case (vs, "nonzero") || compare_no_case (vs, "evenodd"))
                    {   if (! fillrule) fillrule = true;
                        else
                        {   nits.pick (nit_shape, es_error, ec_type, quote (vs), ": only one of 'nonzero' or 'evenodd'.");
                            res = s_invalid; }
                        continue; }
                    nits.pick (nit_shape, es_error, ec_type, quote (vs), ": invalid syntax for first parameter in shape function");
                    res = s_invalid;
                    continue; }
                if (! pos.empty ()) pos += " ";
                pos += vs; }
            if (pos.empty ())
            {   nits.pick (nit_shape, es_error, ec_type, "position expected after 'from'");
                res = s_invalid; }
            else
            {   nitpick nuts, knots;
                if (test_value < t_css_length_percent_2 > (nuts, v, pos))
                    nits.merge (nuts);
                else if (test_value < t_css_ellipse_pos > (knots, v, pos))
                    nits.merge (knots);
                else
                {   nits.merge (nuts); nits.merge (knots); res = s_invalid; } } } }
    return res; }

e_status set_css_shape_value_n (nitpick& nits, const html_version& v, const ::std::string& ss)
{   e_status res = s_invalid;
    const ::std::string s (trim_the_lot_off (ss));
    if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "arguments required");
    else if (v.css_module (c_shape) < 3)
        nits.pick (nit_css_version, es_error, ec_css, "Shape functions require CSS Shapes");
    else
    {   res = s_good;
        int count = 0;
        ::std::string pos;
        e_byto ebyto = bt_by;
        nitpick nets, nuts;
        typedef enum {  ss_context,
                        ss_arc, ss_close, ss_curve, ss_hline, ss_line, ss_move, ss_smooth, ss_vline, // these MUST correspond to e_shape_cmd + 1
                        ss_lm_by, ss_lm_to,
                        ss_hvl_by, ss_hl_to, ss_vl_to,
                        ss_done,
                        ss_error } sh_status;
        sh_status stage = ss_context;
        if (! s.empty ())
        {   vstr_t vr (split_by_space (s));
            for (auto vs : vr)
                switch (stage)
                {   case ss_context :
                    {   const e_shape_cmd shape = examine_value < t_shape_cmd > (nits, v, vr.at (0));
                        if (nits.worst () <= es_error) return s_invalid;
                        stage = static_cast < sh_status > (static_cast < int > (shape) + 1);
                        break; }
                    case ss_done :
                        nits.pick (nit_shape, es_error, ec_type, quote (vs), ": too many parameters");
                        return s_invalid;
                    case ss_close :
                        nits.pick (nit_shape, es_error, ec_type, quote (vs), ": 'close' takes no parameters");
                        return s_invalid;
                    case ss_line :
                    case ss_move :
                        ebyto = examine_value < t_byto > (nits, v, vs);
                        if (nits.worst () <= es_error) return s_invalid;
                        if (ebyto == bt_by) stage = ss_lm_by;
                        else stage = ss_lm_to;
                        count = 0;
                        break;
                    case ss_lm_by :
                        if (! test_value < t_css_length_percent > (nits, v, vs)) return s_invalid;
                        if (count++ == 2) stage = ss_done;
                        break;
                    case ss_lm_to :
                        if (! pos.empty ()) pos += " ";
                        pos += vs;
                        break;
                    case ss_hline :
                        ebyto = examine_value < t_byto > (nits, v, vs);
                        if (nits.worst () <= es_error) return s_invalid;
                        if (ebyto == bt_by) stage = ss_hvl_by;
                        else stage = ss_hl_to;
                        break;
                    case ss_vline :
                        ebyto = examine_value < t_byto > (nits, v, vs);
                        if (nits.worst () <= es_error) return s_invalid;
                        if (ebyto == bt_by) stage = ss_hvl_by;
                        else stage = ss_vl_to;
                        break;
                    case ss_hvl_by :
                        if (! test_value < t_css_length_percent > (nits, v, vs)) return s_invalid;
                        stage = ss_done;
                        break;
                    case ss_hl_to :
                        if (! test_value < t_hline > (nets, v, vs))
                            if (! test_value < t_css_length_percent > (nuts, v, vs))
                            {   nits.merge (nets); nits.merge (nuts); return s_invalid; }
                        stage = ss_done;
                        break;
                    case ss_vl_to :
                        if (! test_value < t_vline > (nets, v, vs))
                            if (! test_value < t_css_length_percent > (nuts, v, vs))
                            {   nits.merge (nets); nits.merge (nuts); return s_invalid; }
                        stage = ss_done;
                        break;
                    case ss_arc :
                    case ss_curve :
                    case ss_smooth :
                        return s_good;
                    default :
                        GRACEFUL_CRASH (__FILE__, __LINE__);
                        break; } 
            if (! pos.empty ())
                if (! test_value < t_css_ellipse_pos > (nits, v, pos))
                    res = s_invalid; } }
    return res; }

e_status set_css_speak_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box)
{   if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "must be empty ... NOT");
    else
    {   if (v.css_module (c_speech) >= 3)
        {   type_master < t_always_auto_never > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; }
        else if ((v.css_version () == css_2_1) || (v.css_version () == css_2_2))
        {   type_master < t_css_speak_2 > tst (box);
            tst.set_value (nits, v, s);
            if (tst.good ()) return s_good; }
        else nits.pick (nit_css_version, es_error, ec_css, "CSS Speak requires CSS 2.1, 2.2, or CSS Speech"); }
    return s_invalid; }

e_status set_css_src_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (context.css_module (c_font) >= 4)
    {   if (test_value < t_css_src_4 > (nits, v, s)) return s_good; }
    else if (context.css_module (c_font) == 3)  
    {   if (test_value < t_css_src_3 > (nits, v, s)) return s_good; }
    else if (context.css_version () == css_2_0)
    {   if (test_value < t_css_src_2 > (nits, v, s)) return s_good; }
    else nits.pick (nit_css_version, es_error, ec_css, "@font-face requires CSS Fonts or CSS 2.0"); 
    return s_invalid; }

e_status set_css_container_value (nitpick& nits, const html_version& v, const ::std::string& sss)
{   if (sss.empty ()) nits.pick (nit_empty, es_error, ec_type, "a container specification cannot be empty");
    else
    {   vstr_t ss (split_by_space (sss));
        PRESUME (! ss.empty (), __FILE__, __LINE__);
        bool res = true, slashed = false;
        typedef enum { cs_name, cs_slash, cs_type, cs_done } con_state;
        con_state state = cs_name;
        for (auto s : ss)
        {   nitpick nuts, knits;
            switch (state)
            {   case cs_name :
                    if (test_value < t_css_container_name > (nuts, v, s))
                    {   nits.merge (nuts); state = cs_slash; break; }
                    FALLTHROUGH;
                case cs_slash :
                    if (s == "/")
                    {   state = cs_type; slashed = true; break; }
                    FALLTHROUGH;
                case cs_type :
                    if (test_value < t_css_container_type > (nits, v, s))
                        if (state == cs_name)
                            nits.pick (nit_container, es_error, ec_type, "missing container name");
                        else if (! slashed)
                            nits.pick (nit_container, es_error, ec_type, "missing '/'");
                    else res = false;
                    state = cs_done;
                    break;
                case cs_done :
                    nits.pick (nit_container, es_error, ec_type, quote (s), ": unexpected (1)");
                    res = false; break;
                default :
                    nits.pick (nit_container, es_error, ec_type, quote (s), " is not a known container property value");
                    res = false; break; } }
        if (res && (state == cs_type))
            nits.pick (nit_container, es_error, ec_type, "missing container type");
        else if (res) return s_good; }
    return s_invalid; }

e_status set_css_content_3_value (nitpick& nits, const html_version& v, const ::std::string& sss)
{   vstr_t ss (split_by_space (sss));
    if (ss.empty ()) return s_empty;
    bool res = true;
    typedef enum { con_rep, con_list, con_slash, con_str, con_count, con_done } con_state;
    con_state state = con_rep;
    for (auto s : ss)
    {   nitpick nuts, knits, knots, nets;
        switch (state)
        {   case con_rep :
                if (test_value < t_css_image > (nuts, v, s))
                {   nits.merge (nuts); state = con_list; break; }
                FALLTHROUGH;
            case con_list :
                if (test_value < t_css_content_list > (knits, v, s))
                {   nits.merge (knits); state = con_list; break; }
                FALLTHROUGH;
            case con_slash :
                if (s == "/")
                {   state = con_str; break; }
                nits.merge (nuts);
                nits.merge (knits);
                nits.pick (nit_content, es_error, ec_type, quote (s), ": unexpected (2)");
                state = con_list;
                res = false; break;
            case con_str :
                if (test_value < t_text > (knots, v, s))
                {   nits.merge (knots); state = con_count; break; }
                FALLTHROUGH;
            case con_count :
                if (test_value < t_css_fn > (nets, v, s))
                {   nits.merge (nets); state = con_done; break; }
                FALLTHROUGH;
            case con_done :
                nits.merge (knots);
                nits.merge (nets);
                nits.pick (nit_content, es_error, ec_type, quote (s), ": unexpected (3)");
                res = false; break;
            default :
                nits.pick (nit_content, es_error, ec_type, quote (s), " is not a known container property value");
                res = false; break; } }
    if (! res) return s_good;
    return s_invalid; }

e_status set_css_content_x_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if ((context.css_module (c_generated_content) >= 3) && (test_value < t_css_content_3nn > (nits, v, s))) return s_good;
    if (test_value < t_css_content > (nits, v, s)) return s_good;
    return s_invalid; }
