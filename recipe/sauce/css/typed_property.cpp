/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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

#include "main/standard.h"
#include "feedback/nitpick.h"
#include "css/typed_property.h"
#include "css/property_classes.h"
#include "css/arguments.h"
#include "css/group.h"

bool examine_custom_property (arguments& args, nitpick& nits, const int from, const int to)
{   bool res = true;
    if (from > 0)
    {   ::std::string prop;
        const int comma = token_find (args.t_, ct_comma, from, to);
        const int ket = token_find (args.t_, ct_round_ket, from, to);
        int next = to;
        if ((comma > 0) && ((comma < ket) || (ket <= 0))) next = comma;
        else if (ket > 0) next = ket;
        if ((args.t_.at (from).t_ == ct_identifier) || (args.t_.at (from).t_ == ct_string) || (args.t_.at (from).t_ == ct_keyword))
        {   prop = args.t_.at (from).val_;
            const int k = next_non_whitespace (args.t_, from, to);
            if ((k > 0) && (k != next))
            {   nits.pick (nit_css_custom, ed_css_custom, "2. Defining Custom Properties", es_error, ec_css, "Junk found after ", quote (prop));
                res = false; } }
        else prop = assemble_string (args.t_, from, next, false);
               
        if (args.has (cic_custom_property, prop))
            args.use (cic_custom_property, prop);
        else if ((args.v_.css_module (c_mixin) == 0) || (args.dst_.get () == nullptr) || (! args.dst_ -> has (cic_fn_param, prop)))
        {   if (comma < 0)
            {   nits.pick (nit_css_custom, es_warning, ec_css, quote (prop), " is not a known custom property");
                res = false; }
            else
            {   args.dcl (cic_custom_property, prop);
                nits.pick (nit_css_custom, es_comment, ec_css, quote (prop), " noted (with fallback value)"); }
                res = false; } }
    return res; }

bool check_custom_property (const arguments& args, const ::std::string& s)
{   if (! args.has (cic_custom_property, s)) return false;
    args.use (cic_custom_property, s);
    return true; }

void validate_anchor_id (const ::std::string& s, arguments& args)
{   VERIFY_NOT_NULL (args.dst_, __FILE__, __LINE__);
    const auto pear = args.anchors_.insert (s);
    if (! pear.second)
        args.t_.at (0).nits_.pick ( nit_anchor, ed_css_anchor, "2.1. Creating an Anchor: the anchor-name property",
                                    es_comment, ec_type, quote (s), ": has multiple declarations."); }

void validate_anchor_idref (nitpick& nits, type_master < t_css_anchor_idref >& cai, arguments& args, const ::std::string& s)
{   VERIFY_NOT_NULL (args.dst_, __FILE__, __LINE__);
    if (cai.status () == s_good)
        if (args.anchors_.find (s) == args.anchors_.cend ())
        {   nits.pick ( nit_anchor, ed_css_anchor, "2.1. Creating an Anchor: the anchor-name property",
                        es_error, ec_type, quote (s), ": has not been declared (with anchor-name).");
            cai.status (s_invalid); } }

void validate_animation_name (type_master < t_css_anim_base >& cab, arguments& args)
{   VERIFY_NOT_NULL (args.dst_, __FILE__, __LINE__);
    sstr_t sstr (args.g_.get_strs (gst_keyframe));
    cab.invalid_access (args.t_.at (0).nits_, args.v_, &sstr); }

void validate_counter_style_name (type_master < t_css_counter_style_name >& cab, arguments& args)
{   VERIFY_NOT_NULL (args.dst_, __FILE__, __LINE__);
    sstr_t sstr (args.g_.get_strs (gst_counter_style));
    cab.invalid_access (args.t_.at (0).nits_, args.v_, &sstr); }

void validate_palette (type_master < t_css_palette >& cab, arguments& args)
{   VERIFY_NOT_NULL (args.dst_, __FILE__, __LINE__);
    sstr_t sstr (args.g_.get_strs (gst_palette));
    cab.invalid_access (args.t_.at (0).nits_, args.v_, &sstr); }

bool check_constants (arguments& args, nitpick& nits, const int i)
{   nitpick nets;
    if (! test_value < t_css_val_con > (nets, args.v_, args.t_.at (i).val_)) return false;
    nits.merge (nets);
    if (args.v_.css_module (c_value_unit) < 4)
        nits.pick (nit_css_value, ed_css_value_4, "10.7 Numeric Constants", es_warning, ec_css, "if ", quote (args.t_.at (i).val_), " refers to the mathematical constant, then it requires CSS Values 4");
    return true; }

bool call_fn (arguments& args, nitpick& nits, int& i, const int to, bool& res, e_css_val_fn& e, bool& params)
{   nitpick nuts;
    type_master < t_css_val_fn > cvf;
    const bool easing = context.css_module (c_easing_function);
    e = cvf_none;
    cvf.set_value (nuts, args.v_, args.t_.at (i).val_);
    if (! cvf.good ()) return false;
    nits.merge (nuts);
    if ((cvf.flags () & CF_NO_PARAMS) == CF_NO_PARAMS)
    {   i = next_non_whitespace (args.t_, i, to);
        if (easing)
        {   e = cvf.get (); params = false; return true; }
        nits.pick (nit_css_ease, ed_css_ease, "", es_error, ec_css, quote (cvf.name ()), " requires CSS Easing Functions");
        return false; }
    i = next_non_whitespace (args.t_, i, to);
    if ((i < 0) || (args.t_.at (i).t_ != ct_round_brac))
    {   if (easing && ((cvf.flags () & CF_MAYBE_NO_PARAMS) == CF_MAYBE_NO_PARAMS))
        {   if (args.v_.any_ext5 (H5_CSS_EASE_4))
            {   e = cvf.get (); params = false; return true; }
            nits.pick (nit_css_ease, ed_css_ease, "", es_error, ec_css, quote (cvf.name ()), " requires CSS Easing Functions level 2");
            return false; } }
    else
    {   i = next_non_whitespace (args.t_, i, to);
        params = true;
        if (i > 0)
        {   switch (cvf.get ()) // dear visual studio, I do understand the dislike of C style casts, but would you care to point out where one is on this line?
            {   case cvf_anchor :
                case cvf_anchor_size :
                    if (context.css_module (c_anchor_pos) < 3)
                        nits.pick (nit_css_version, es_error, ec_css, quote (cvf.name ()), " requires CSS Anchor Positioning");
                    else e = cvf.get ();
                    break;
                case cvf_annotation :
                case cvf_character_variant :
                case cvf_ornaments :
                case cvf_styleset :
                case cvf_stylistic :
                case cvf_swash :
                    if (context.css_module (c_font) < 4)
                        nits.pick (nit_css_font, es_error, ec_css, quote (cvf.name ()), " requires CSS Fonts 4");
                    else e = cvf.get ();
                    break;
                case cvf_attr :
                    if ((context.css_module (c_value_unit) < 5) && (context.css_module (c_generated_content) < 3))
                        nits.pick (nit_css_value, es_error, ec_css, quote (cvf.name ()), " requires CSS Generated Content or CSS Values and Units 5");
                    else e = cvf.get ();
                    break;
                case cvf_colour :
                case cvf_hwb :
                case cvf_lab :
                case cvf_lch :
                case cvf_oklab :
                case cvf_oklch :
                    if (context.css_module (c_colour) < 4)
                        nits.pick (nit_css_colour, es_error, ec_css, quote (cvf.name ()), " requires CSS Colour 4");
                    else e = cvf.get ();
                    break;
                case cvf_colour_mix :
                case cvf_device_cmyk :
                    if (context.css_module (c_colour) < 5)
                        nits.pick (nit_css_colour, es_error, ec_css, quote (cvf.name ()), " requires CSS Colour 5");
                    else e = cvf.get ();
                    break;
                case cvf_env :
                    if (context.css_module (c_linked_parameters) < 3)
                        nits.pick (nit_css_version, es_error, ec_css, quote (cvf.name ()), " requires CSS Linked Parameters");
                    else e = cvf.get ();
                    break;
                case cvf_format :
                    if (context.css_module (c_font) < 3)
                        nits.pick (nit_css_font, es_error, ec_css, quote (cvf.name ()), " requires CSS Font 3");
                    else e = cvf.get ();
                    break;
                case cvf_hsl :
                case cvf_hsla :
                case cvf_rgba :
                    if (context.css_module (c_colour) < 3)
                        nits.pick (nit_css_colour, es_error, ec_css, quote (cvf.name ()), " requires CSS Colour 3");
                    else e = cvf.get ();
                    break;
                case cvf_linear :
                    if (! easing)
                        nits.pick (nit_css_ease, es_error, ec_css, quote (cvf.name ()), " requires CSS Easing Functions");
                    else e = cvf.get ();
                    break;
                case cvf_rgb :
                case cvf_url :
                    e = cvf.get ();
                    break;
                case cvf_url_pattern :
                    if (context.css_module (c_route) < 3)
                        nits.pick (nit_css_colour, es_error, ec_css, quote (cvf.name ()), " requires CSS Route 3");
                    else e = cvf.get ();
                    break;
                case cvf_superellipse :
                    if (context.css_module (c_border_box) < 4)
                        nits.pick (nit_css_version, es_error, ec_css, quote (cvf.name ()), " requires CSS Borders and Box Decorations 4");
                    else e = cvf.get ();
                    break;
                case cvf_tech :
                    if (context.css_module (c_font) < 4)
                        nits.pick (nit_css_font, es_error, ec_css, quote (cvf.name ()), " requires CSS Font 4");
                    else e = cvf.get ();
                    break;
                case cvf_var :
                    if (context.css_module (c_custom_property) < 3)
                        nits.pick (nit_css_custom, es_error, ec_css, quote (cvf.name ()), " requires CSS Custom");
                    else e = cvf_var;
                    break;
                case cvf_moz_calc :
                case cvf_moz_image_rect :
                    nits.pick ( nit_bespoke_obsolete, es_warning, ec_type, quote (cvf.name ()),
                                " is bespoke, obsolete, or both, so is unlikely to be supported by every browser.");
                    e = cvf.get ();
                    break;
                default :
                    switch (context.css_module (c_value_unit))
                    {   case 3 :
                            if (cvf.get () == cvf_calc) e = cvf_calc;
                            else nits.pick (nit_css_value, es_error, ec_css, quote (cvf.name ()), " requires CSS Values 4");
                            break;
                        case 4 :
                        case 5 :
                        case 6 :
                            e = cvf.get ();
                            break;
                        default :
                            nits.pick (nit_css_value, es_error, ec_css, quote (cvf.name ()), " requires CSS Values");
                            break; } } }
        res = (e != cvf_none); }
    return true; }

bool test_cascade (const arguments& args, const ::std::string& s, e_iiu& iiu)
{   switch (context.css_module (c_cascade_inheritance))
    {   case 6 :
        case 5 :
            switch (s.at (0))
            {   case 'r' :
                case 'R' :
                    if (compare_no_case (s, "revert-layer"))
                    {   iiu = iiu_revert_layer;
                        return true; }
                    if (compare_no_case (s, "revert-rule"))
                    {   iiu = iiu_revert_rule;
                        return true; }
                    break;
                default: break; }
            FALLTHROUGH;   
        case 4 :
            switch (s.at (0))
            {   case 'r' :
                case 'R' :
                    if (compare_no_case (s, "revert"))
                    {   iiu = iiu_revert;
                        return true; }
                    break;
                default: break; }
            FALLTHROUGH;   
        case 3 :
            switch (s.at (0))
            {   case 'i' :
                case 'I' :
                    if (compare_no_case (s, "initial"))
                    {   iiu = iiu_initial;
                        return true; }
                    break;
                case 'u' :
                case 'U' :
                    if (compare_no_case (s, "unset"))
                    {   iiu = iiu_unset;
                        return true; }
                    break;
                default: break; }
            FALLTHROUGH;   
        default :
            if (context.css_version () != css_1)
                switch (s.at (0))
                {   case 'i' :
                    case 'I' :
                        if (compare_no_case (s, "inherit"))
                        {   iiu = iiu_inherit;
                            return true; }
                        break;
                    case '-' :
                        if (compare_no_case (s, "-moz-initial"))
                        {   iiu = iiu_moz_initial;
                            return true; }
                        break;
                default: break; }
            break; }
    if (args.v_.css_module (c_mixin) > 0)
        if (args.dst_.get () != nullptr)
        {   ::std::string fn (s);
            const ::std::string::size_type pos = fn.find_first_of ('(');
            if (pos != ::std::string::npos)
                fn = trim_the_lot_off (fn.substr (0, pos));
            if (args.dst_ -> has (cic_fn_name, fn))
            {   iiu = iiu_fn;
                args.dst_ -> use (cic_fn_name, fn);
                return true; } }
    return false; }
