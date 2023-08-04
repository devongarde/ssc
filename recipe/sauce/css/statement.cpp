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
#include "css/arguments.h"
#include "css/statement.h"
#include "element/elem.h"
#include "webpage/page.h"
#include "webpage/directory.h"
#include "utility/cache.h"
#include "utility/quote.h"
#include "parser/parse_abb.h"
#include "simple/type_media.h"

void statement::parse_charset (arguments& args, nitpick& nits, const int from, const int to)
{   if ((args.v_.css_version () == css_1) || (args.v_.css_syntax () > 0))
        nits.pick (nit_css_version, ed_css_syntax, "9.3. The '@charset' Rule", es_error, ec_css, "@charset requires CSS 2");
    else
    {   const int i = next_non_whitespace (args.t_, from, to); 
        if ((i < 0) || (args.t_.at (i).t_ != ct_string))
            nits.pick (nit_charset, es_error, ec_css, "expecting string after @charset");
        else test_value < t_charset > (nits, context.html_ver (), args.t_.at (i).val_); } }

void statement::parse_colour_profile (arguments& args, nitpick& nits, const int from, const int to)
{   if (args.v_.css_colour () < 5)
    {   if (args.snippet_)
            if (! args.eb_.test (elem_svg))
            {   nits.pick (nit_css_svg, ed_svg_1_1, "12.3.4 The CSS @color-profile rule", es_warning, ec_css, "@color-profile expects an ancestral <SVG>, or CSS Colour 5");
                return; }
        if ((args.v_.svg_version () != sv_none) && (args.v_.svg_version () != sv_1_1))
        {   nits.pick (nit_svg_version, ed_svg_1_1, "12.3.4 The CSS @color-profile rule", es_warning, ec_css, "@color-profile requires SVG 1.1 or CSS Colour 5");
            return; } }
    if ((to < 0) || (args.t_.at (to).t_ != ct_curly_brac))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting { property... } after @color-profile");
    else
    {   PRESUME (args.t_.at (to).child_ > 0, __FILE__, __LINE__);
        if ((from != to) && (from > 0))
        {   const int i = next_non_whitespace (args.t_, from, to);
            if ((i > 0) && (i < to))
                if ((args.t_.at (i).t_ == ct_identifier) || (args.t_.at (i).t_ == ct_keyword))
                {   ::std::string s (args.t_.at (i).val_);
                    if ((s.size () > 2) && (s.substr (0, 2) == "--"))
                        if (args.g_.custom_prop ().find (s) != args.g_.custom_prop ().cend ())
                            nits.pick (nit_css_custom, es_warning, ec_css, "@color-profile identifier ", s, " previously encountered");
                        else
                        {   nits.pick (nit_css_custom, es_info, ec_css, "noting @color-profile ", s);
                            args.g_.custom_prop ().emplace (s, 1); } } }
        fiddlesticks < statement > f (&args.st_, this);
        prop_.parse (args, args.t_.at (to).child_); } }

void statement::parse_counter_style (arguments& args, nitpick& nits, const int from, const int to)
{   const int i = next_non_whitespace (args.t_, from, to); 
    if (context.html_ver ().css_counter_style () < 3)
        nits.pick (nit_css_version, es_error, ec_css, "@counter-style requires CSS Counter Style 3");
    else if ((i < 0) || ((args.t_.at (i).t_ != ct_string) && (args.t_.at (i).t_ != ct_identifier) && (args.t_.at (i).t_ != ct_number) && (args.t_.at (i).t_ != ct_keyword)))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting an identifier after @counter-style");
    else if ((to < 0) || (args.t_.at (to).t_ != ct_curly_brac))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting { descriptor... } after @counter-style");
    else
    {   enum_n < t_css_counter_style, e_css_counter_style > cs;
        nitpick nuts;
        const ::std::string name (tart (args.t_.at (i).val_));
        cs.set_value (nuts, args.v_, name);
        if (cs.empty ()) nits.merge (nuts);
        else if (cs.good ())
        {   nits.merge (nuts);
            if ((cs.get () & CF_CS_NAUGHTY) == CF_CS_NAUGHTY)
                nits.pick (nit_counter_style, ed_css_cs_3, "3. Defining Custom Counter Styles: the @counter-style rule", es_error, ec_css, quote (args.t_.at (i).val_), " cannot be used with @counter-style");
            if ((cs.get () & CF_CS_CASCADE) == CF_CS_CASCADE)
                nits.pick (nit_counter_style, ed_css_cascade_5, "7.3. Explicit Defaulting", es_error, ec_css, quote (args.t_.at (i).val_), ": no CSS wide keyword can be used with @counter-style");
            if ((cs.get () & CF_CS_PREDEFINED) == CF_CS_PREDEFINED)
                nits.pick (nit_counter_style, ed_css_cs_3, "6. Simple Predefined Counter Styles", es_warning, ec_css, quote (args.t_.at (i).val_), " is a predefined @counter-style"); }
        else if (args.g_.counter_style ().find (name) != args.g_.counter_style ().cend ())
            nits.pick (nit_counter_style, ed_css_cs_3, "3. Defining Custom Counter Styles: the @counter-style rule", es_warning, ec_css, quote (args.t_.at (i).val_), ": defined earlier");
        else    
        {   nits.pick (nit_counter_style, es_comment, ec_css, "noted ", quote (name));
            args.g_.counter_style ().insert (name); }
        PRESUME (args.t_.at (to).child_ > 0, __FILE__, __LINE__);
        fiddlesticks < statement > f (&args.st_, this);
        dsc_.parse (args, css_counter_style, args.t_.at (to).child_); } }

void statement::parse_custom_media (arguments& args, nitpick& nits, const int from, const int to)
{   int i = next_non_whitespace (args.t_, from, to); 
    if (context.html_ver ().css_media () < 5)
        nits.pick (nit_css_version, es_error, ec_css, "@custom-media requires CSS Media 5");
    else if ((i < 0) || ((args.t_.at (i).t_ != ct_string) && (args.t_.at (i).t_ != ct_identifier) && (args.t_.at (i).t_ != ct_number) && (args.t_.at (i).t_ != ct_keyword)))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting an identifier after @custom-media");
    else
    {   ::std::string name (args.t_.at (i).val_);
        i = next_non_whitespace (args.t_, i, to);
        if (i < 0) nits.pick (nit_css_syntax, es_error, ec_css, "missing @custom-media definition after ", quote (name));
        else
        {   ::std::string def (assemble_string (args.t_, i, to, true));
            args.custom_media ().insert (::std::pair (name, def)); } } }

void statement::parse_feature_value (arguments& args, nitpick& nits, const int to, const e_css_statement cs, font_features& ffv)
{   if (context.css_font () < 4)
        nits.pick (nit_css_version, ed_css_font_4, "6.9.1. Basic syntax", es_error, ec_css, "@", type_master < t_css_statement > :: name (cs), " requires CSS Font 4 or higher");
    else if ((args.st_ == nullptr) || (args.st_ -> st_.get () != css_font_feature_values))
        nits.pick (nit_css_font_feature, ed_css_font_4, "6.9.1. Basic syntax", es_error, ec_css, "@", type_master < t_css_statement > :: name (cs), " must be a child of @font-feature-values");
    else if ((to < 0) || (args.t_.at (to).t_ != ct_curly_brac))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting { declaration... } after @", type_master < t_css_statement > :: name (cs));
    else
    {   PRESUME (args.t_.at (to).child_ > 0, __FILE__, __LINE__);
        fiddlesticks < statement > f (&args.st_, this);
        ffv.parse (args, cs, args.t_.at (to).child_); } }

void statement::parse_font_feature_values (arguments& args, nitpick& nits, const int from, const int to)
{   PRESUME (to > 0, __FILE__, __LINE__);
    int i = next_non_whitespace (args.t_, from, to); 
    if (context.html_ver ().css_font () < 4)
        nits.pick (nit_css_version, es_error, ec_css, "@font-feature-values requires CSS Font 4");
    else if ((i < 0) || ((args.t_.at (i).t_ != ct_string) && (args.t_.at (i).t_ != ct_identifier) && (args.t_.at (i).t_ != ct_number) && (args.t_.at (i).t_ != ct_keyword)))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting a name after @font-feature-values (1)");
    else
    {   if (i == to) nits.pick (nit_css_syntax, es_error, ec_css, "expecting a name after @font-feature-values (2)");
        else
        {   ::std::string name (assemble_string (args.t_, i, to, false));
            if (args.font_family ().find (name) != args.font_family ().cend ())
                nits.pick (nit_css_font_feature, es_comment, ec_css, quote (name), " previously named.");
            else 
            {   if (! enum_n < t_fontname, e_fontname > :: exists (name))
                    enum_n < t_fontname, e_fontname > :: extend (name, fn_bespoke); 
                args.font_family ().insert (name); }
            i = next_non_whitespace (args.t_, i, to);
            if (i < 0) nits.pick (nit_css_font_feature, es_error, ec_css, "missing @font-feature-values properties after ", quote (name)); }
        if ((to < 0) || (args.t_.at (to).t_ != ct_curly_brac))
            nits.pick (nit_css_font_feature, es_error, ec_css, "expecting { descriptor... } after @font-feature-values");
        else if (args.t_.at (to).child_ > 0)
        {   fiddlesticks < statement > f (&args.st_, this);
            vst_.emplace_back (pst_t (new statements (args, args.t_.at (to).child_))); } } }

void statement::parse_font_face (arguments& args, nitpick& nits, const int to)
{   if ((context.html_ver ().css_version () != css_2_0) && (context.css_font () < 3))
        nits.pick (nit_css_version, es_error, ec_css, "@font-face requires CSS 2.0, or CSS Font 3 or higher");
    else if ((to < 0) || (args.t_.at (to).t_ != ct_curly_brac))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting { descriptor... } after @font-face");
    else
    {   PRESUME (args.t_.at (to).child_ > 0, __FILE__, __LINE__);
        fiddlesticks < statement > f (&args.st_, this);
        dsc_.parse (args, css_font_face, args.t_.at (to).child_); } }

void statement::parse_font_palette_values (arguments& args, nitpick& nits, const int from, const int to)
{   PRESUME (to > 0, __FILE__, __LINE__);
    int i = next_non_whitespace (args.t_, from, to); 
    if (context.html_ver ().css_font () < 4)
        nits.pick (nit_css_version, es_error, ec_css, "@font-palette-values requires CSS Font 4");
    else if ((i < 0) || ((args.t_.at (i).t_ != ct_string) && (args.t_.at (i).t_ != ct_identifier) && (args.t_.at (i).t_ != ct_number) && (args.t_.at (i).t_ != ct_keyword)))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting a name after @font-palette-values (1)");
    else
    {   if (i == to) nits.pick (nit_css_syntax, es_error, ec_css, "expecting a name after @font-palette-values (2)");
        else
        {   ::std::string name (assemble_string (args.t_, i, to, false));
            if (args.palette ().find (name) != args.palette ().cend ())
                nits.pick (nit_css_palette, es_comment, ec_css, quote (name), " previously named.");
            else args.palette ().insert (name);
            i = next_non_whitespace (args.t_, i, to);
            if (i < 0) nits.pick (nit_css_palette, es_error, ec_css, "missing @font-palette-values properties after ", quote (name)); }
        if ((to < 0) || (args.t_.at (to).t_ != ct_curly_brac))
            nits.pick (nit_css_palette, es_error, ec_css, "expecting { descriptor... } after @font-palette-values");
        else if (args.t_.at (to).child_ > 0)
        {   fiddlesticks < statement > f (&args.st_, this);
            dsc_.parse (args, css_font_palette_values, args.t_.at (to).child_); } } }

void statement::bracketed_property (arguments& args, nitpick& nits, const int to, int& i)
{   int child = next_non_whitespace (args.t_, i, to);
    if ((child < 0) || ((args.t_.at (child).t_ != ct_keyword) && (args.t_.at (child).t_ != ct_identifier) && (args.t_.at (child).t_ != ct_round_brac)))
    {   nits.pick (nit_bad_import, es_error, ec_css, "expecting a bracketed condition"); i = -1; }
    int brackets = 1;
    int j = child;
    for (; (child > 0) && ((to < 0) || (child <= to)); child = next_non_whitespace (args.t_, child, to))
        switch (args.t_.at (child).t_)
        {   case ct_round_brac :
                ++brackets; 
                break;
            case ct_round_ket :
                if (--brackets == 0)
                {   fiddlesticks < statement > f (&args.st_, this);
                    prop_.parse (args, j, child-1);
                    child = next_non_whitespace (args.t_, child, to); }
                break;
            default :
                break; }
    if (child > 0) i = child; else i = to; }

void statement::parse_import (arguments& args, nitpick& nits, const int from, const int to)
{   url u;
    int i = next_non_whitespace (args.t_, from, to);
    int mql = -1; 
    if (args.had_rule_)
        nits.pick (nit_bad_import, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, "@import must precede all rules");
    if (args.st_ != nullptr)
        nits.pick (nit_bad_import, ed_css_20, "4.1.5 At-rules", es_error, ec_css, "@import cannot appear inside blocks");
    if (i < 0)
        nits.pick (nit_bad_import, es_error, ec_css, "expecting string or url () after @import");
    else if ((args.t_.at (i).t_ == ct_string) || (args.t_.at (i).t_ == ct_identifier))
        u = examine_value < t_url > (nits, context.html_ver (), args.t_.at (i).val_);
    else if (args.t_.at (i).t_ != ct_keyword)
        nits.pick (nit_bad_import, es_error, ec_css, "expecting a string or a url (...) after @import");
    else
    {   if (compare_no_case (args.t_.at (i).val_, "url"))
        {   i = next_non_whitespace (args.t_, i, to);
            if ((i < 0) || (args.t_.at (i).t_ != ct_round_brac))
            {   nits.pick (nit_bad_import, es_error, ec_css, "expecting an argument after @import url");
                return; }
            const int child = next_non_whitespace (args.t_, i, to);
            if ((child < 0) || ((args.t_.at (child).t_ != ct_keyword) && (args.t_.at (child).t_ != ct_string) && (args.t_.at (child).t_ != ct_identifier)))
            {   nits.pick (nit_bad_import, es_error, ec_css, "the argument given to @import url (...) should be a URL");
                return; }
            ::std::string wot (args.t_.at (child).val_);
            if ((args.t_.at (child).t_ == ct_keyword) || (args.t_.at (child).t_ == ct_identifier) || (args.t_.at (child).t_ == ct_string))
            {   const int ket = token_find (args.t_, ct_round_ket, child, to);
                if (ket < 0)
                {   nits.pick (nit_bad_import, es_error, ec_css, "missing ket following @import url(");
                    return; }
                wot = assemble_string (args.t_, child, (ket < 0) ? to : ket);
                i = next_non_whitespace (args.t_, ket, to); }
            else i = next_non_whitespace (args.t_, child, to);
            u = examine_value < t_url > (nits, context.html_ver (), wot); }
        if ((i > 0) && (compare_no_case (args.t_.at (i).val_, "layer")))
        {   if (args.v_.css_cascade () < 5)
            {   nits.pick (nit_css_version, es_error, ec_css, "supports requires CSS Cascade 5 or later");
                return; }
            const int j = next_non_whitespace (args.t_, i, to);
            if (j < 0) return;
            if (args.t_.at (j).t_ != ct_round_brac)
                i = j;
            else
            {   const int child = next_non_whitespace (args.t_, j, to);
                if ((child < 0) || ((args.t_.at (child).t_ != ct_round_ket) && (args.t_.at (child).t_ != ct_keyword) && (args.t_.at (child).t_ != ct_identifier)))
                {   nits.pick (nit_bad_import, es_error, ec_css, "the argument given to @import layer (...) should be a layer name");
                    return; }
                if (args.t_.at (child).t_ == ct_round_ket)
                {   nits.pick (nit_empty, es_comment, ec_css, "empty layer name");
                    i = next_non_whitespace (args.t_, child, to); }
                else
                {   const int ket = token_find (args.t_, ct_round_ket, child, to);
                    if (ket < 0)
                    {   nits.pick (nit_bad_import, es_error, ec_css, "missing ket following @import layer(");
                        return; }
                    i = next_non_whitespace (args.t_, ket, to); } } }
        if ((i > 0) && (compare_no_case (args.t_.at (i).val_, "supports")))
        {   if (args.v_.css_cascade () < 4)
            {   nits.pick (nit_css_version, es_error, ec_css, "supports requires CSS Cascade 4 or later");
                return; }
            i = next_non_whitespace (args.t_, i, to);
            if ((i < 0) || (args.t_.at (i).t_ != ct_round_brac))
            {   nits.pick (nit_bad_import, es_error, ec_css, "expecting an argument after @import supports");
                return; }
            else bracketed_property (args, nits, to, i); }
        mql = i; }
    if (! u.invalid ())
    {   ::std::string content;
        ::std::time_t when = 0;
        bool borked = false;
        if (! u.is_local ())
            nits.pick (nit_reputation, es_warning, ec_css, "the security, integrity, presentation and reputation of your site is dependent on that of ", quote (u.get ()));
        if (! cached_url (nits, context.html_ver (), args.g_.get_page ().get_directory (), u, content, when, borked))
            nits.pick (nit_cannot_access, es_error, ec_css, "cannot access ", quote (u.get ()), ", so cannot verify it.");
        else if (borked || content.empty ())
            nits.pick (nit_empty, es_comment, ec_css, quote (u.get ()), " appears unencumbered by content");
        else
        {   nitpick knots;
            args.g_.get_page ().css ().parse_file (knots, args.ns_, u, true, true, true);
            nits.merge (knots); } }
    if ((mql > 0) && ((to < 0) || (mql < to)))
    {   fiddlesticks < statement > f (&args.st_, this);
        media_.parse (args, css_media, mql, to); } }

void statement::parse_keyframes (arguments& args, nitpick& nits, const int from, const int to)
{   if (context.html_ver ().css_animation () < 3)
        nits.pick (nit_css_version, ed_css_animation_3, "3. Keyframes", es_error, ec_css, "@keyframes requires CSS Animation level 3 or higher");
    int i = next_non_whitespace (args.t_, from, to); 
    if ((i < 0) || ((args.t_.at (i).t_ != ct_string) && (args.t_.at (i).t_ != ct_identifier) && (args.t_.at (i).t_ != ct_keyword)))
        nits.pick (nit_css_syntax, ed_css_animation_3, "3. Keyframes", es_error, ec_css, "expecting an identifier after @keyframes");
    else
    {   ::std::string name (args.t_.at (i).val_);
        nitpick nuts;
        if (test_value < t_css_wide > (nuts, args.v_, name))
            nits.pick (nit_css_keyframes, ed_css_animation_3, "3. Keyframes", es_error, ec_css, quote (name), " is a CSS wide keyword, so cannot be used as a @keyframes name");
        else if (args.g_.keyframe ().find (name) == args.g_.keyframe ().cend ()) args.g_.keyframe ().insert (name);
        else nits.pick (nit_css_keyframes, ed_css_animation_3, "3. Keyframes", es_warning, ec_css, "@keyframes ", quote (name), " previously defined");
        i = next_non_whitespace (args.t_, i, to);
        int num = 0;
        sstr_t pcnts;
        if (i < 0) nits.pick (nit_css_keyframes, ed_css_animation_3, "3. Keyframes", es_error, ec_css, "missing @keyframes definition after ", quote (name));
        else if (args.t_.at (i).t_ != ct_curly_brac)
            nits.pick (nit_css_syntax, ed_css_animation_3, "3. Keyframes", es_error, ec_css, "expecting '{' after ", quote (name));
        else
        {   PRESUME (args.t_.at (i).child_ > 0, __FILE__, __LINE__);
            const int mx = args.t_.at (i).next_;
            i = first_non_whitespace (args.t_, args.t_.at (i).child_, mx);
            for (; i > 0; i = next_non_whitespace (args.t_, i, mx))
            {   if (args.t_.at (i).t_ == ct_curly_ket)
                {   if (num == 0) nits.pick (nit_css_keyframes, ed_css_animation_3, "3. Keyframes", es_warning, ec_css, quote (name), " appears a little minimalistic");
                    break; }
                else if (args.t_.at (i).t_ == ct_curly_brac)
                    nits.pick (nit_css_syntax, ed_css_animation_3, "3. Keyframes", es_error, ec_css, "missing keyframe selector(s) after ", quote (name));
                else
                {   bool more = true;
                    for (; more && (i > 0); i = next_non_whitespace (args.t_, i, mx))
                        switch (args.t_.at (i).t_)
                        {   case ct_identifier:
                            case ct_keyword :
                            case ct_number :
                                {   const ::std::string& x = args.t_.at (i).val_;
                                    if (compare_no_case (x, "from"))
                                    {   if (pcnts.find ("from") == pcnts.cend ()) pcnts.insert ("from");
                                        else nits.pick (nit_css_keyframes, ed_css_animation_3, "3. Keyframes", es_warning, ec_css, "'from' repeated"); }
                                    else if (compare_no_case (x, "to"))
                                    {   if (pcnts.find ("to") == pcnts.cend ()) pcnts.insert ("to");
                                        else nits.pick (nit_css_keyframes, ed_css_animation_3, "3. Keyframes", es_warning, ec_css, "'to' repeated"); }
                                    else if ((x.length () < 2) || (x.at (x.length () - 1) != '%'))
                                        nits.pick (nit_css_keyframes, ed_css_animation_3, "3. Keyframes", es_error, ec_css, "Expecting a percentage, 'from', or 'to', not ", quote (x));
                                    else
                                    {   const int n = lexical < int > :: cast (x.substr (0, x.length () - 1));
                                        if ((n < 0) || (n > 100))
                                            nits.pick (nit_css_keyframes, ed_css_animation_3, "3. Keyframes", es_warning, ec_css, quote (x), " will be ignored"); } }
                                break;
                            case ct_comma : 
                                break;
                            case ct_curly_brac :
                                {   PRESUME (args.t_.at (i).child_ > 0, __FILE__, __LINE__);
                                    fiddlesticks < statement > f (&args.st_, this);
                                    prop_.parse (args, args.t_.at (i).child_, mx);
                                    ++num; }
                                break;
                            case ct_curly_ket :
                                more = false;
                                break;
                            default :
                                nits.pick (nit_css_syntax, ed_css_animation_3, "3. Keyframes", es_error, ec_css, "unexpected ", quote (args.t_.at (i).val_));
                                break; }
                    switch (num)
                    {   case 0 :
                            nits.pick (nit_css_syntax, ed_css_animation_3, "3. Keyframes", es_warning, ec_css, "an unexpected slight absence of @keyframes content");
                            break;
                        case 1 :
                            nits.pick (nit_css_syntax, ed_css_animation_3, "3. Keyframes", es_comment, ec_css, "that's rather minimalistic, given it's @keyframes with an 's'");
                            break;
                        default :
                            break; } } } } } }

void statement::parse_layer (arguments& args, nitpick& nits, const int from, const int to)
{   if (context.html_ver ().css_cascade () < 5)
        nits.pick (nit_css_version, es_error, ec_css, "@layer requires CSS cascade 5 or later");
    else 
    {   int i = from;
        bool got = false;
        do
        {   ::std::string name;
            i = next_non_whitespace (args.t_, i, to);
            if ((i < 0) || ((args.t_.at (i).t_ != ct_identifier) && (args.t_.at (i).t_ != ct_keyword))) break;
            got = true;
            name = args.t_.at (i).val_;
            if (args.g_.layer ().find (name) != args.g_.layer ().cend ())
                nits.pick (nit_css_layer, es_info, ec_css, "layer ", name, " previously mentioned");
            else args.g_.layer ().insert (name);
            i = next_non_whitespace (args.t_, i, to);
            if ((i <= 0) || (args.t_.at (i).t_ != ct_comma)) break;
            i = next_non_whitespace (args.t_, i, to); }
        while (i > 0);
        if ((i > 0) && (args.t_.at (i).t_ == ct_curly_brac))
        {   PRESUME (args.t_.at (i).child_ > 0, __FILE__, __LINE__);
            fiddlesticks < statement > f (&args.st_, this);
            vst_.emplace_back (pst_t (new statements (args, args.t_.at (to).child_))); }
        else if (! got) nits.pick (nit_css_layer, es_error, ec_css, "neither @layer name nor { ... } defined"); } }

void statement::parse_media (arguments& args, nitpick& nits, const int from, const int to)
{   if (context.html_ver ().css_version () == css_1)
        nits.pick (nit_css_version, es_error, ec_css, "@media requires CSS 2.0 or later");
    else
    {   const int i = next_non_whitespace (args.t_, from, to);
        if (i < 0) nits.pick (nit_empty, es_error, ec_css, "@media empty");
        else
        {   int prev = -1;
            const int st = token_find (args.t_, ct_curly_brac, i, to, &prev);
            if (st < 0) nits.pick (nit_css_syntax, es_error, ec_css, "@media expects a condition, then { ... }");
            else
            {   PRESUME (args.t_.at (st).child_ > 0, __FILE__, __LINE__);
#ifdef DEBUG
                const ::std::string s (assemble_string (args.t_, i, prev, true));
#endif // DEBUG
                fiddlesticks < statement > f (&args.st_, this);
                if (st == i) nits.pick (nit_css_syntax, es_info, ec_css, "no @media condition, all presumed");
                else media_.parse (args, css_media, i, prev);
                vst_.emplace_back (pst_t (new statements (args, args.t_.at (st).child_))); } } } }

void statement::parse_namespace (arguments& args, nitpick& nits, const int from, const int to)
{   if (context.html_ver ().css_namespace () < 3)
        nits.pick (nit_css_version, ed_css_namespaces_3, "CSS Namespaces 3, September 2011", es_error, ec_css, "@namespace requires CSS 3 or later");
    else
    if (args.had_rule_)
        nits.pick (nit_css_namespace, ed_css_namespaces_3, "3 Declaring namespaces", es_error, ec_css, "@namespace must follow @import and @charset, and precede all rules");
    else
    {   int i = next_non_whitespace (args.t_, from, to);
        if (i < 0)
        {   nits.pick (nit_css_namespace, ed_css_namespaces_3, "3 Declaring namespaces", es_error, ec_css, "@namespace requires a namespace name");
            return; }
        ::std::string prefix, name;
        if ((args.t_.at (i).t_ == ct_identifier) || (args.t_.at (i).t_ == ct_keyword))
        {   prefix = args.t_.at (i).val_;
            i = next_non_whitespace (args.t_, i, to); }
        if (i < 0)
        {   nits.pick (nit_css_namespace, ed_css_namespaces_3, "3 Declaring namespaces", es_error, ec_css, "@namespace requires a string after the prefix");
            return; }
        if (((args.t_.at (i).t_ == ct_identifier) || (args.t_.at (i).t_ == ct_keyword)) && compare_no_case (args.t_.at (i).val_, "url"))
        {   int k = next_non_whitespace (args.t_, i, to);
            if (args.t_.at (k).t_ != ct_round_brac)   
            {   nits.pick (nit_css_namespace, ed_css_namespaces_3, "3 Declaring namespaces", es_error, ec_css, "bad @namespace url ()");
                return; }
            k = next_non_whitespace (args.t_, k, to);
            const int z = token_find (args.t_, ct_round_ket, k, to);
            if (z < k)
            {   nits.pick (nit_css_namespace, ed_css_namespaces_3, "3 Declaring namespaces", es_error, ec_css, "bad @namespace url argument");
                return; }
            name = assemble_string (args.t_, k, z); }
        else
        {   if ((args.t_.at (i).t_ != ct_string))
            {   nits.pick (nit_css_namespace, ed_css_namespaces_3, "3 Declaring namespaces", es_error, ec_css, "@namespace name expected (it should be a string)");
                return; }
            name = args.t_.at (i).val_; }
        if (prefix.empty () && name.empty ())
            nits.pick (nit_empty, ed_css_namespaces_3, "2 Terminology", es_warning, ec_css, "Ignoring @namespace with empty short and long form");
        else
        {   if (name.empty ())
                nits.pick (nit_empty, es_warning, ec_css, quote (prefix), ": the @namespace long form is empty");
            VERIFY_NOT_NULL (args.ns_, __FILE__, __LINE__);
            args.ns_ -> declare (nits, args.v_, empty_namespace_names, prefix, name); } } }

void statement::parse_page (arguments& args, nitpick& nits, const int from, const int to)
{   if (context.html_ver ().css_version () == css_1)
        nits.pick (nit_css_dubious, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, "@page was undefined in the CSS 1 specification, although it did get a mention");
    else
    {   int i = from;
        if ((from < to) && (from > 0) && (to > 0)) i = next_non_whitespace (args.t_, i, to); 
        if ((i > 0) && (args.t_.at (i).t_ == ct_colon))
        {   fiddlesticks < statement > f (&args.st_, this);
            rules_.parse (args, i, to);
            return; }
        if ((i > 0) && ((args.t_.at (i).t_ == ct_keyword) || (args.t_.at (i).t_ == ct_identifier)))
        {   const ::std::string n (::boost::to_lower_copy (args.t_.at (i).val_));
            if (args.g_.page_name ().find (n) != args.g_.page_name ().cend ())
                nits.pick (nit_page_name_again, es_error, ec_css, quote (args.t_.at (i).val_), " previously used.");
            else args.g_.page_name ().insert (n);
            i = next_non_whitespace (args.t_, i, to);
            if (i != to) nits.pick (nit_css_syntax, es_error, ec_css, "unexpected content after ", quote (args.t_.at (i).val_)); }
        if ((to < 0) || (args.t_.at (to).t_ != ct_curly_brac))
            nits.pick (nit_bad_page, es_error, ec_css, "expecting { property... } after @page");
        else
        {   PRESUME (args.t_.at (to).child_ > 0, __FILE__, __LINE__);
            fiddlesticks < statement > f (&args.st_, this);
            prop_.parse (args, args.t_.at (to).child_); } } }

void statement::parse_scope (arguments& args, nitpick& nits, const int from, const int to)
{   if (context.html_ver ().css_cascade () < 6)
        nits.pick (nit_css_version, es_error, ec_css, "@scope requires CSS cascade 6");
    else
    {   int i = next_non_whitespace (args.t_, from, to);
        if (i < 0)
            nits.pick (nit_css_scope, ed_css_cascade_6, "2.5.2. Syntax of @scope", es_error, ec_css, "@scope: scope missing");
        else
        {   if (args.t_.at (i).t_ == ct_round_brac)
            {   i = next_non_whitespace (args.t_, i, to);
                const int z = token_find (args.t_, ct_round_ket, i, to);
                if (z < 0)
                {   nits.pick (nit_css_scope, ed_css_cascade_6, "2.5.2. Syntax of @scope", es_error, ec_css, "@scope found '(' but not ')'");
                    return; }
                PRESUME (args.t_.at (to).child_ > 0, __FILE__, __LINE__);
                fiddlesticks < statement > f (&args.st_, this);
                sel_.parse (args, i, z);
                i = next_non_whitespace (args.t_, z, to);
                if (i < 0)
                {   nits.pick (nit_css_scope, ed_css_cascade_6, "2.5.2. Syntax of @scope", es_error, ec_css, "@scope expects {...} after any selectors");
                    return; } }
            if ((args.t_.at (i).t_ == ct_keyword) || (args.t_.at (i).t_ == ct_identifier))
                if (compare_no_case (args.t_.at (i).val_, "to")) 
                {   i = next_non_whitespace (args.t_, i, to);
                    if (args.t_.at (i).t_ != ct_round_brac)
                    {   nits.pick (nit_css_scope, ed_css_cascade_6, "2.5.2. Syntax of @scope", es_error, ec_css, "@scope expects ( selectors ) after 'to'");
                        return; }
                    i = next_non_whitespace (args.t_, i, to);
                    const int z = token_find (args.t_, ct_round_ket, i, to);
                    if (z < 0)
                    {   nits.pick (nit_css_scope, ed_css_cascade_6, "2.5.2. Syntax of @scope", es_error, ec_css, "@scope found 'to (' but not a subsequent ')'");
                        return; }
                    PRESUME (args.t_.at (to).child_ > 0, __FILE__, __LINE__);
                    fiddlesticks < statement > f (&args.st_, this);
                    sel_.parse (args, i, z);
                    i = next_non_whitespace (args.t_, z, to);
                    if (i < 0)
                    {   nits.pick (nit_css_scope, ed_css_cascade_6, "2.5.2. Syntax of @scope", es_error, ec_css, "@scope expects {...} after any selectors");
                        return; } }
            if (args.t_.at (i).t_ != ct_curly_brac)
                nits.pick (nit_css_scope, ed_css_cascade_6, "2.5.2. Syntax of @scope", es_error, ec_css, "@scope requires {...}");
            else
            {   PRESUME (args.t_.at (i).child_ > 0, __FILE__, __LINE__);
                fiddlesticks < statement > f (&args.st_, this);
                vst_.emplace_back (pst_t (new statements (args, args.t_.at (i).child_))); } } } }

void statement::parse_supports (arguments& args, nitpick& nits, const int from, const int to)
{   if ((args.v_.css_cascade () < 4) && (args.v_.css_conditional_rule () < 3))
        nits.pick (nit_css_version, es_error, ec_css, "@supports requires CSS Cascade 4, or CSS Conditional Rules 3");
    else
    {   int i = next_non_whitespace (args.t_, from, to);
        if (args.st_ != nullptr)
            nits.pick (nit_bad_supports, ed_css_20, "4.1.5 At-rules", es_error, ec_css, "@supports cannot appear inside blocks");
        if (i < 0)
            nits.pick (nit_bad_supports, es_error, ec_css, "expecting a media condition after @supports");
        else if ((args.t_.at (i).t_ != ct_keyword) && (args.t_.at (i).t_ != ct_identifier) && (args.t_.at (i).t_ != ct_round_brac))
            nits.pick (nit_bad_supports, es_error, ec_css, "expecting a keyword or a bracketed media condition");
        else
        {   const int ket = token_find (args.t_, ct_curly_brac, i, to);
            if (ket < 0)
                nits.pick (nit_css_scope, es_error, ec_css, "@supports requires { ... }");
            else
            {   fiddlesticks < statement > f (&args.st_, this);
//                media_.parse (args, css_supports, i, ket);
                if (args.t_.at (i).t_ != ct_round_brac) prop_.parse (args, i, ket);
                else if (i < ket-1) bracketed_property (args, nits, ket-1, i);
                vst_.emplace_back (pst_t (new statements (args, args.t_.at (ket).child_))); } } } }

void statement::parse (arguments& args, const int from, const int to)
{   PRESUME (from <= to, __FILE__, __LINE__);
    PRESUME (from + 1 < GSL_NARROW_CAST < int > (args.t_.size ()), __FILE__, __LINE__);
    PRESUME (args.t_.at (from).t_ == ct_at, __FILE__, __LINE__);
    int b = first_non_whitespace (args.t_, from, to);
    nitpick& nits = args.t_.at (b).nits_;
    if ((b < 0) || (args.t_.at (b).t_ != ct_at))
    {   nits.pick (nit_css_syntax, es_error, ec_css, "expecting '@'");
        return; }
    b = next_non_whitespace (args.t_, b, to);
    if ((b < 0) || (args.t_.at (b).t_ != ct_keyword))
        nits.pick (nit_statement, es_error, ec_css, "expecting keyword after '@'");
    else if (! args.v_.is_css_compatible (st_.first ()))
        nits.pick (nit_css_version, es_error, ec_css, st_.name (), " requires CSS ", st_.first ().long_css_version_name ());
    else
    {   st_.set_value (nits, args.v_, args.t_.at (b).val_);
        switch (st_.get_int ())
        {   case css_annotation :
                parse_feature_value (args, nits, to, st_.get (), stylistic_);
                break;
            case css_character_variant :
                parse_feature_value (args, nits, to, st_.get (), character_variant_);
                break;
            case css_historical_forms :
                parse_feature_value (args, nits, to, st_.get (), historical_form_);
                break;
            case css_ornaments :
                parse_feature_value (args, nits, to, st_.get (), ornament_);
                break;
            case css_swash :
                parse_feature_value (args, nits, to, st_.get (), swash_);
                break;
            case css_styleset :
                parse_feature_value (args, nits, to, st_.get (), styleset_);
                break;
            case css_stylistic :
                parse_feature_value (args, nits, to, st_.get (), stylistic_);
                break;
            case css_charset :
                parse_charset (args, nits, b, to);
                break;
            case css_colour_profile :
                parse_colour_profile (args, nits, b, to);
                break;
            case css_counter_style :
                parse_counter_style (args, nits, b, to);
                break;
            case css_custom_media :
                parse_custom_media (args, nits, b, to);
                break;
            case css_font_feature_values :
                parse_font_feature_values (args, nits, b, to);
                break;
            case css_font_face :
                parse_font_face (args, nits, to);
                break;
            case css_font_palette_values :
                parse_font_palette_values (args, nits, b, to);
                break;
            case css_import :
                parse_import (args, nits, b, to);
                break;
            case css_keyframes :
                parse_keyframes (args, nits, b, to);
                break;
            case css_layer :
                parse_layer (args, nits, b, to);
                break;
            case css_media :
                parse_media (args, nits, b, to);
                break;
            case css_namespace :
                parse_namespace (args, nits, b, to);
                break;
            case css_page :
                parse_page (args, nits, b, to);
                break;
            case css_scope :
                parse_scope (args, nits, b, to);
                break;
            case css_supports :
                parse_supports (args, nits, b, to);
                break;
            case css_bottom_centre :
            case css_bottom_left :
            case css_bottom_left_corner :
            case css_bottom_right :
            case css_bottom_right_corner :
            case css_top_centre :
            case css_top_left :
            case css_top_left_corner :
            case css_top_right :
            case css_top_right_corner :
                break;
            case css_document :
            case css_viewport :
                break;
            case css_else :
            case css_when :
                break;
            default :
                break; } } }

e_css_statement statement::get () const
{   return st_.get (); }

void statement::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    s -> mark (st_.get ());
    rules_.accumulate (s);
    prop_.accumulate (s, rules_.get_elements ());
    for (auto pst : vst_)
        if (pst.get () != nullptr)
            pst -> accumulate (s);
    dsc_.accumulate (s, rules_.get_elements ());
    media_.accumulate (s); }

::std::string statement::rpt () const
{   ::std::string res;
    switch (st_.get_int ())
    {   case css_annotation :
            res = "@annotation ();";
            break;
        case css_bottom_centre :
            res = "@bottom-centre ();";
            break;
        case css_bottom_left :
            res = "@bottom-left ();";
            break;
        case css_bottom_left_corner :
            res = "@bottom-left-corner ();";
            break;
        case css_bottom_right :
            res = "@bottom-right ();";
            break;
        case css_bottom_right_corner :
            res = "@bottom-right-corner ();";
            break;
        case css_character_variant :
            res = "@character-variant ();";
            break;
        case css_charset :
            res = "@charset ();";
            break;
        case css_colour_profile :
            res = "@color-profile;";
            break;
        case css_counter_style :
            res = "@counter-style;";
            break;
        case css_custom_media :
            res = "@custom-media;";
            break;
        case css_document :
            res = "@document;";
            break;
        case css_else :
            res = "@else;";
            break;
        case css_font_feature_values :
            res = "@font-feature-values ();";
            break;
        case css_font_face :
            res = "@font-face ();";
            break;
        case css_font_palette_values :
            res = "@font-paletteivalues ();";
            break;
        case css_historical_forms :
            res = "@historicaliforms ();";
            break;
        case css_import :
            res = "@import ();";
            break;
        case css_keyframes :
            res = "@keyframes;";
            break;
        case css_layer :
            res = "@layer ();";
            break;
        case css_media :
            res = "@media ();";
            break;
        case css_namespace :
            res = "@namespace;";
            break;
        case css_ornaments :
            res = "@ornaments ();";
            break;
        case css_page :
            res = "@page ();";
            break;
        case css_supports :
            res = "@supports;";
            break;
        case css_scope :
            res = "@scope;";
            break;
        case css_swash :
            res = "@swash ()";
            break;
        case css_styleset :
            res = "@styleset ()";
            break;
        case css_stylistic :
            res = "@stylistic ()";
            break;
        case css_top_centre :
            res = "@top-center ()";
            break;
        case css_top_left :
            res = "@top-left ()";
            break;
        case css_top_left_corner :
            res = "@top-left-corner ()";
            break;
        case css_top_right :
            res = "@top-right ()";
            break;
        case css_top_right_corner :
            res = "@top-right-corner ()";
            break;
        case css_viewport :
            res = "@viewport;";
            break;
        case css_when :
            res = "@when;";
            break;
        case css_error :
            res = "@??? ();";
            break;
        default :
            GRACEFUL_CRASH (__FILE__, __LINE__);
            break; }
    return res; }

void statement::validate (arguments& args)
{   fiddlesticks < statement > f (&args.st_, this);
    prop_.validate (args);
    rules_.validate (args);
    dsc_.validate (args);
    media_.validate (args);
    annotation_.validate (args, args.font_feature (css_annotation), "annotation");
    character_variant_.validate (args, args.font_feature (css_character_variant), "character variant");
    historical_form_.validate (args, args.font_feature (css_historical_forms), "historical form");
    ornament_.validate (args, args.font_feature (css_ornaments), "ornament");
    swash_.validate (args, args.font_feature (css_swash), "swash");
    styleset_.validate (args, args.font_feature (css_styleset), "styleset");
    stylistic_.validate (args, args.font_feature (css_stylistic), "stylistic");
    for (auto i : vst_)
        i -> validate (args); }

void statement::shadow (::std::stringstream& ss, arguments& )
{   ss << rpt (); }
