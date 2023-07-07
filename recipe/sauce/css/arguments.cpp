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

#include "main/standard.h"
#include "type/type.h"
#include "css/flags.h"
#include "css/arguments.h"
#include "css/selectors.h"
#include "css/statement.h"
#include "css/group.h"
#include "webpage/page.h"

arguments::arguments (const html_version& v, const namespaces_ptr& namespaces, css_group& g)
    : g_ (g), v_ (v)
{   ns_.reset (new namespaces_t ());
    ns_ -> up (namespaces.get ()); }

arguments::arguments (const html_version& v, const namespaces_ptr& namespaces, css_group& g, bool sv, bool snippet, const e_element styled, const element_bitset eb)
    : g_ (g), v_ (v), sv_ (sv), snippet_ (snippet), styled_ (styled), eb_ (eb)
{   ns_.reset (new namespaces_t ());
    ns_ -> up (namespaces.get ()); }

arguments::arguments (const html_version& v, const namespaces_ptr& namespaces, css_group& g, bool sv, bool snippet, const ::std::string& abs, dst_ptr dst, const e_element styled, const element_bitset eb)
    : g_ (g), v_ (v), sv_ (sv), snippet_ (snippet), styled_ (styled), abs_ (abs), dst_ (dst), eb_ (eb)
{   ns_.reset (new namespaces_t ());
    ns_ -> up (namespaces.get ()); }

bool arguments::prep_for_make (nitpick& nits, const int from, int& b, const int to, int& var, int& bang, css_token& p, bool& xs, bool& xk, bool& xn, bool& xi, bool& fn, bool& clean, int& kc, ::std::string& val)
{   int pre = to;
    var = b;
    bang = token_find (t_, ct_bang, b, to, &pre);
    if (bang < 0) pre = to;
    xs = false; xk = false; xn = false; xi = false; fn = false; clean = true;
    const bool nff = (st_ == nullptr) || (st_ -> get () != css_font_face);
    kc = 0;
    while (((to == -1) || (b <= pre)) && (b > 0) && (t_.at (b).t_ != ct_curly_ket))
    {   if ((p == ct_error) || (p <= ct_comment)) p = t_.at (b).t_;
        switch (t_.at (b).t_)
        {   case ct_keyword : xk = true; break;
            case ct_identifier : xi = true; break;
            case ct_number : xn = true; break;
            case ct_string : xs = true; break;
            case ct_round_brac : fn = true; break;
            case ct_comma: clean = nff; break;
            default : break; }                    
        if (clean) val += tkn_rpt (t_.at (b));
        b = next_token_at (t_, b, pre);
        ++kc; }
    if (val.length () >= 5)
        if (val.at (0) == '-')
            if (    ((val.length () >= 6) && (val.substr (1, 5) == "khtml")) ||
                    ((val.length () >= 5) && (val.substr (1, 4) == "atsc")))
            {   nits.pick (nit_bespoke_property, es_warning, ec_css, quote (val), ": apologies, but " PROG " cannot verify the bespoke");
                return false; }
    return true; }

void arguments::check_flags (nitpick& nits, const flags_t f, const ::std::string& s) const
{   if ((f & CF_DEPRECATED) == CF_DEPRECATED)
        nits.pick (nit_deprecated, es_warning, ec_css, s, " is deprecated, so unlikely to be supported by many browsers");
    if ((f & CF_FACE_OR_PROFILE) == CF_FACE_OR_PROFILE)
    {   if ((st_ == nullptr) || ((st_ -> get () != css_font_face) && (st_ -> get () != css_colour_profile)))
            nits.pick (nit_naughty_page, es_error, ec_css, s, " requires @colour-profile or @font-face"); }
    else if ((f & CF_MUST_FONT_FACE) == CF_MUST_FONT_FACE)
        if ((st_ == nullptr) || (st_ -> get () != css_font_face))
            nits.pick (nit_naughty_page, es_error, ec_css, s, " requires @font-face");
    if ((f & CF_BEF_AFT) == CF_BEF_AFT)
        if ((ss_ == nullptr) || (! ss_ -> bef_aft ()))
            if (context.css_version () > css_2_2)
                nits.pick (nit_naughty_content, ed_css_21, "12.2 The 'content' p. 182 property", es_error, ec_css, s, " requires an element with ::before andor ::after");
            else nits.pick (nit_naughty_content, ed_css_21, "12.2 The 'content' p. 182 property", es_error, ec_css, s, " requires an element with :before andor :after"); }

void arguments::check_flags (nitpick& nits, const flags_t f, const ::std::string& s, const bool xk, const bool xi, const bool xn, const bool xs, const bool fn, const bool clean, const int kc, const ::std::string& item, const ::std::string& val) const
{   if (! fn)
    {   if (xs && ((f & CF_NOT_STRING) == CF_NOT_STRING))
            nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, quote (val), ": should not be a string");
        if (((f & CF_EXPECT_FN) == CF_EXPECT_FN))
            nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, quote (val), ": function expected"); }
    if (((f & CF_EXPECT_FN) != CF_EXPECT_FN) || ! fn)
    {   if ((kc > 1) && ((f & (CF_EXPECT_STRING | CF_EXPECT_NUMBER)) != 0))
            nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, "a single value is sought");
        if (xs) if ((f & CF_EXPECT_KEYWORDS) == CF_EXPECT_KEYWORDS)
            nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, quote (val), ": should be a keyword");
        if (xk || xn || xi) if ((f & CF_EXPECT_STRING) == CF_EXPECT_STRING)
            nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, quote (val), ": should be a string");
        if (! xn) if ((f & CF_EXPECT_NUMBER) == CF_EXPECT_NUMBER)
            nits.pick (nit_css_syntax, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, quote (val), ": should be a number"); }
    if (snippet_ && ((f & CF_SVG) == CF_SVG))
        if (! eb_.test (elem_svg))
            nits.pick (nit_svg_version, ed_svg_1_1, "Appendix N: Property Index", es_warning, ec_css, quote (item), " is an SVG property, which requires at least an ancestral <SVG> element");
    const e_css_statement st = cs ();
    switch (st)
    {   case css_font_face :
            if ((f & (CF_MUST_FONT_FACE | CF_MAY_FONT_FACE)) == 0)
                nits.pick (nit_not_here, es_error, ec_css, quote (item), " cannot be used with @font-face");
            break;
        case css_font_feature_values :
            if ((f & (CF_MUST_FONT_FV | CF_MAY_FONT_FV)) == 0)
                nits.pick (nit_not_here, es_error, ec_css, quote (item), " cannot be used with @font-feature-values");
            break;
        case css_font_palette_values :
            if ((f & (CF_MUST_PALETTE | CF_MAY_PALETTE)) == 0)
                nits.pick (nit_not_here, es_error, ec_css, quote (item), " cannot be used with @font-palette-values");
            break;
        default :
            break; }
   if (((f & CF_MUST_FONT_FACE) == CF_MUST_FONT_FACE) && (st != css_font_face))
        nits.pick (nit_not_here, es_error, ec_css, quote (item), " can only be used with @font-face");
    if (((f & CF_MUST_FONT_FV) == CF_MUST_FONT_FV) && (st != css_font_feature_values))
        nits.pick (nit_not_here, ed_css_font_4, "6. Font Feature Properties", es_error, ec_css, quote (item), " can only be used with @font-feature-values");
    if (((f & CF_MUST_PALETTE) == CF_MUST_PALETTE) && (st != css_font_palette_values))
        nits.pick (nit_not_here, ed_css_font_4, "9. Colour Font Support", es_error, ec_css, quote (item), " can only be used with @font-palette-values"); }

const ustr_t& arguments::custom_media () const
{ return g_.custom_media_; }
 
ustr_t& arguments::custom_media ()
{ return g_.custom_media_; }

const sstr_t& arguments::font_feature (const e_css_statement st) const
{   switch (st)
    {   case css_annotation :
            return g_.annotation_;
        case css_character_variant :
            return g_.character_variant_;
        case css_historical_forms :
            return g_.historical_form_;
        case css_ornaments :
            return g_.ornament_;
        case css_swash :
            return g_.swash_;
        case css_styleset :
            return g_.styleset_;
        case css_stylistic :
            return g_.stylistic_;
        default :
            GRACEFUL_CRASH (__FILE__, __LINE__); } }
 
const sstr_t& arguments::font_family () const
{   return g_.font_family_; }
 
sstr_t& arguments::font_family ()
{   return g_.font_family_; }

sstr_t& arguments::font_feature (const e_css_statement st)
{   switch (st)
    {   case css_annotation :
            return g_.annotation_;
        case css_character_variant :
            return g_.character_variant_;
        case css_historical_forms :
            return g_.historical_form_;
        case css_ornaments :
            return g_.ornament_;
        case css_swash :
            return g_.swash_;
        case css_styleset :
            return g_.styleset_;
        case css_stylistic :
            return g_.stylistic_;
        default :
            GRACEFUL_CRASH (__FILE__, __LINE__); } }

const sstr_t& arguments::palette () const
{   return g_.palette_; }
 
sstr_t& arguments::palette ()
{   return g_.palette_; }

void arguments::validate (nitpick& nits, const flags_t f, const ::std::string& p, const ::std::string& vl) const
{   if ((f & CF_PAGE) == CF_PAGE)
        if (! ps_ -> state ().test (ec_page_property))
            if ((st_ == nullptr) || ((st_ -> get () != css_page) && (st_ -> get () != css_media)))
                nits.pick (nit_naughty_page, es_error, ec_css, p, " requires @page, @media, or the page property");
    if ((f & CF_NOT_LV_STD_JUL23) == CF_NOT_LV_STD_JUL23)
        if (v_ >= html_jul23)
            nits.pick (nit_css_living_standard, es_warning, ec_css, p, " is incompatible with the living standard after April 2023");
    if ((f & CF_LV_STD_JUL23) == CF_LV_STD_JUL23)
        if (v_ < html_jul23)
            nits.pick (nit_css_living_standard, es_warning, ec_css, p, " requires the living standard mid-2023 or later");
    if ((f & CF_PAGE_NAME) == CF_PAGE_NAME)
    {   const sstr_t& pn (g_.page_name ());
        ::std::string vll (trim_the_lot_off (vl));
        if (pn.find (::boost::to_lower_copy (vll)) == pn.cend ())
            nits.pick (nit_no_such_page, es_error, ec_css, quote (vll), " is not a known page name"); } }

e_css_statement arguments::cs () const
{   if (st_ == nullptr) return css_error;
    return st_ -> get (); }
 