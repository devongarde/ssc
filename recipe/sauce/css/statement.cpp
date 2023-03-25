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
{   const int i = next_non_whitespace (args.t_, from, to); 
    if (context.html_ver ().css_version () == css_1)
        nits.pick (nit_css_version, es_error, ec_css, "@charset requires CSS 2.0 or later");
    else if ((i < 0) || (args.t_.at (i).t_ != ct_string))
        nits.pick (nit_charset, es_error, ec_css, "expecting string after @charset");
    else test_value < t_charset > (nits, context.html_ver (), args.t_.at (i).val_); }

void statement::parse_colour_profile (arguments& args, nitpick& nits, const int to)
{   if (args.snippet_)
        if (! args.eb_.test (elem_svg))
            nits.pick (nit_css_svg, ed_svg_1_1, "12.3.4 The CSS @color-profile rule", es_warning, ec_css, "@color-profile expects an ancestral <SVG>");
    if ((args.v_.svg_version () != sv_none) && (args.v_.svg_version () != sv_1_1))
        nits.pick (nit_svg_version, ed_svg_1_1, "12.3.4 The CSS @color-profile rule", es_warning, ec_css, "@color-profile requires SVG 1.1");
    if ((to < 0) || (args.t_.at (to).t_ != ct_curly_brac))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting { property... } after @color-profile");
    else
    {   PRESUME (args.t_.at (to).child_ > 0, __FILE__, __LINE__);
        fiddlesticks < statement > f (&args.st_, this);
        prop_.parse (args, args.t_.at (to).child_); } }

void statement::parse_font_face (arguments& args, nitpick& nits, const int to)
{   if (context.html_ver ().css_version () != css_2_0)
        nits.pick (nit_css_version, es_error, ec_css, "@font-face requires CSS 2.0 (only)");
    if ((to < 0) || (args.t_.at (to).t_ != ct_curly_brac))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting { property... } after @font-face");
    else
    {   PRESUME (args.t_.at (to).child_ > 0, __FILE__, __LINE__);
        fiddlesticks < statement > f (&args.st_, this);
        prop_.parse (args, args.t_.at (to).child_); } }

void statement::parse_import (arguments& args, nitpick& nits, const int from, const int to)
{   url u;
    const int i = next_non_whitespace (args.t_, from, to); 
    if (args.had_rule_)
        nits.pick (nit_bad_import, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, "@import must precede all rules");
    if (args.st_ != nullptr)
        nits.pick (nit_bad_import, ed_css_20, "4.1.5 At-rules", es_error, ec_css, "@import cannot appear inside blocks");
    if (i < 0)
        nits.pick (nit_bad_import, es_error, ec_css, "expecting string or url () after @import");
    else if ((args.t_.at (i).t_ == ct_string) || (args.t_.at (i).t_ == ct_identifier))
        u = examine_value < t_url > (nits, context.html_ver (), args.t_.at (i).val_);
    else if ((args.t_.at (i).t_ != ct_keyword) || ! compare_no_case (args.t_.at (i).val_, "url"))
        nits.pick (nit_bad_import, es_error, ec_css, "expecting a string or a url (...) after @import");
    else
    {   const int j = next_non_whitespace (args.t_, i, to);
        if ((j < 0) || (args.t_.at (j).t_ != ct_round_brac))
            nits.pick (nit_bad_import, es_error, ec_css, "expecting an argument after @import url");
        else
        {   const int child = next_non_whitespace (args.t_, j, to);
            if ((child < 0) || ((args.t_.at (child).t_ != ct_keyword) && (args.t_.at (child).t_ != ct_string) && (args.t_.at (child).t_ != ct_identifier)))
                nits.pick (nit_bad_import, es_error, ec_css, "the argument given to @import url (...) should be a URL");
            else
            {   ::std::string wot (args.t_.at (child).val_);
                if ((args.t_.at (child).t_ == ct_keyword) || (args.t_.at (child).t_ == ct_identifier))
                {   const int ket = token_find (args.t_, ct_round_ket, child, to);
                    wot = assemble_string (args.t_, child, (ket < 0) ? to : ket); }
                u = examine_value < t_url > (nits, context.html_ver (), wot); } } }
    if (! u.invalid ())
    {   ::std::string content;
        ::std::time_t when;
        if (! u.is_local ())
            nits.pick (nit_reputation, es_warning, ec_css, "the security, integrity, presentation and reputation of your site is dependent on that of ", quote (u.get ()));
        if (! cached_url (nits, context.html_ver (), args.g_.get_page ().get_directory (), u, content, when))
            nits.pick (nit_cannot_access, es_error, ec_css, "cannot access ", quote (u.get ()), ", so cannot verify it.");
        else if (content.empty ())
            nits.pick (nit_empty, es_comment, ec_css, quote (u.get ()), " appears unencumbered by content");
        else
        {   nitpick knots;
            args.g_.get_page ().css ().parse_file (knots, args.ns_, u, true);
            nits.merge (knots); } } }

void statement::parse_media (arguments& args, nitpick& nits, const int from, const int to)
{   if (context.html_ver ().css_version () == css_1)
        nits.pick (nit_css_version, es_error, ec_css, "@media requires CSS 2.0 or later");
    else
    {   bool tick = false;
        ::std::string twas;
        if (args.v_.css_media () >= 3)
        {   int prev = -1;
            const int i = next_non_whitespace (args.t_, from, to);
            token_find (args.t_, ct_curly_brac, i, to, &prev);
            twas = assemble_string (args.t_, i, prev);
            parse_media_query (nits, args.v_, twas); } 
        else for (int i = from; i != to; )
        {   i = next_non_whitespace (args.t_, i, to);
            if ((i < 0) || (i >= to)) break;
            if (tick)
            {   if (args.t_.at (i).t_ != ct_comma)
                    nits.pick (nit_bad_media, es_error, ec_css, "expecting comma after ", twas);
                tick = false; }
            else if ((args.t_.at (i).t_ != ct_keyword) && (args.t_.at (i).t_ != ct_identifier))
                nits.pick (nit_bad_media, es_error, ec_css, quote (tkn_rpt (args.t_.at (i))), ": expecting media type");
            else
            {   twas = args.t_.at (i).val_;
                test_value < t_media > (nits, context.html_ver (), ::boost::to_lower_copy (twas));
                tick = true; } }
        if ((to < 0) || (args.t_.at (to).t_ != ct_curly_brac))
            nits.pick (nit_bad_media, es_error, ec_css, "expecting { ... } after @media");
        else
        {   PRESUME (args.t_.at (to).child_ > 0, __FILE__, __LINE__);
            fiddlesticks < statement > f (&args.st_, this);
            vst_.emplace_back (pst_t (new statements (args, args.t_.at (to).child_))); } } }

void statement::parse_namespace (arguments& args, nitpick& nits, const int from, const int to)
{   if (context.html_ver ().css_version () < css_3)
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
    else
    {   st_.set_value (nits, context.html_ver (), args.t_.at (b).val_);
        switch (st_.get_int ())
        {   case css_charset :
                parse_charset (args, nits, b, to);
                break;
            case css_colour_profile :
                parse_colour_profile (args, nits, to);
                break;
            case css_font_face :
                parse_font_face (args, nits, to);
                break;
            case css_import :
                parse_import (args, nits, b, to);
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
            case css_keyframes :
            case css_supports :
            case css_scope :
            case css_viewport :
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
            pst -> accumulate (s); }

::std::string statement::rpt () const
{   ::std::string res;
    switch (st_.get_int ())
    {   case css_charset :
            res = "@charset ();";
            break;
        case css_font_face :
            res = "@font-face ();";
            break;
        case css_import :
            res = "@import ();";
            break;
        case css_media :
            res = "@media ();";
            break;
        case css_page :
            res = "@page ();";
            break;
        case css_colour_profile :
            res = "@color-profile;";
            break;
        case css_document :
            res = "@document;";
            break;
        case css_keyframes :
            res = "@keyframes;";
            break;
        case css_namespace :
            res = "@namespace;";
            break;
        case css_supports :
            res = "@supports;";
            break;
        case css_scope :
            res = "@scope;";
            break;
        case css_viewport :
            res = "@viewport;";
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
    for (auto i : vst_)
        i -> validate (args); }

void statement::shadow (::std::stringstream& ss, arguments& )
{   ss << rpt (); }
