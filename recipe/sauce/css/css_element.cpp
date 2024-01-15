/*
ssc (static site checker)
File Info
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
#include "css/css_element.h"
#include "css/arguments.h"
#include "main/enum.h"
#include "type/type.h"
#include "element/state.h"
#include "css/statements.h"

#define SEL_SEPS ":.#["

void css_element::parse (arguments& args, const int from, const int to, const bool knotted)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST < int > (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    nitpick& nits = args.t_.at (from).nits_;
    int b = first_non_whitespace (args.t_, from, to);
    if (b < 0) return;
    ::std::string ns, wo (assemble_string (args.t_, b, to));
    bool no_ns = true, all_ns = false;
    int b4 = -1;
    const int n = token_find (args.t_, ct_bar, b, to, &b4);
    if (n > 0)
    {   b = next_non_whitespace (args.t_, n, to);
        if (args.v_.css_namespace () < 3)
            nits.pick (nit_css_version, es_error, ec_css, quote (wo), ": namespaces requires CSS Namespace 3 or better");
        else if ((b < 0) && (b4 < 0))
            nits.pick (nit_css_syntax, es_error, ec_css, quote (wo), ": a namespace andor an element must be given");
        else if (b4 > 0)
        {   no_ns = false;
            PRESUME (b4 < n, __FILE__, __LINE__);
            switch (args.t_.at (b4).t_)
            {   case ct_splat :
                    ns = "*"; all_ns = true; break;
                case ct_keyword :
                case ct_identifier :
                    ns = args.t_.at (b4).val_; break;
                default :
                    nits.pick (nit_css_namespace, es_error, ec_css, tkn_rpt (args.t_.at (b4)), ": namespace name expected"); } } }
    if (b < 0)
    {   if (ns.empty ())
        {   css_element e (elem_css_all);
            ::std::swap (*this, e); }
        else
        {   css_element e (nits, args.v_, args.ns_, ns + ":*");
            ::std::swap (*this, e); }
        return; }
    bool pseudo = true;
    switch (args.t_.at (b).t_)
    {   case ct_ampersand :
        case ct_round_brac :
            pseudo = false;
            if (context.css_nesting () < 3)
                nits.pick (nit_css_version, es_error, ec_css, quote (wo), " here requires CSS Nesting");
            else
            {   css_element e (elem_css_child);
                ::std::swap (*this, e); }
            break;
         case ct_barbar :
            pseudo = false;
            if (context.html_ver ().css_selector () < 4)
                nits.pick (nit_css_version, es_error, ec_css, quote (wo), ": || requires CSS Selector 4");
            else
            {   css_element e (elem_css_cell);
                ::std::swap (*this, e); }
            break;
        case ct_at :
            if (context.css_nesting () < 3)
                nits.pick (nit_nesting, es_error, ec_css, "'@' here requires CSS Nesting");
            else
            {   const int kw = next_non_whitespace (args.t_, b, to);
                if (kw < 0)
                {   nits.pick (nit_nesting, ed_css_nesting, "2.2. Nesting Other At-Rules", es_error, ec_css, "missing keyword after '@'");
                    return; }
                if ((args.t_.at (kw).t_ != ct_keyword) || (args.t_.at (kw).t_ != ct_identifier))
                {   nits.pick (nit_nesting, ed_css_nesting, "2.2. Nesting Other At-Rules", es_error, ec_css, "@", tkn_rpt (args.t_.at (kw)), "??");
                    return; }
                enum_n < t_css_statement, e_css_statement > cst;
                cst.set_value (nits, args.v_, args.t_.at (kw).val_);
                const e_css_statement st = cst.get ();
                switch (st)
                {   case css_media :
                    case css_supports :
                    case css_scope :
                    case css_layer :
                    case css_container :
                        break;
                    case css_context :
                    case css_error :
                        nits.pick (nit_nesting, es_error, ec_css, "@", tkn_rpt (args.t_.at (kw)), " is unrecognised");
                        return;
                    default :
                        nits.pick (nit_nesting, ed_css_nesting, "2.2. Nesting Other At-Rules", es_error, ec_css, "@", tkn_rpt (args.t_.at (kw)), " cannot be nested");
                        return; }
                if (! cst.first ().is_css_compatible (context.html_ver ()))
                {   nits.pick (nit_nesting, es_error, ec_css, "@", tkn_rpt (args.t_.at (kw)), " is not available in ", context.html_ver ().long_css_version_name ());
                    return; }
                if (duff_ == nullptr) duff_ = ps_t (new statement ());
                fiddlesticks < statement > f (&args.st_, duff_.get ());
                fiddlesticks < bool > nb (&args.nested_, true);
                st_.emplace_back (pst_t (new statements (args, b, to))); }
            return;
        case ct_coco :
        case ct_colon :
        case ct_dot :
        case ct_hash :
        case ct_square_brac :
            {   css_element e (elem_css_all);
                ::std::swap (*this, e); }
            break;
        case ct_gt :
            pseudo = false;
            if (context.html_ver ().css_version () == css_1)
                nits.pick (nit_css_version, es_error, ec_css, quote (wo), ": > requires CSS 2.0 or better");
            else
            {   css_element e (elem_css_child);
                ::std::swap (*this, e); }
            break;
        case ct_gtgt :
            pseudo = false;
            if (context.html_ver ().css_cascade () >= 6)
            {   css_element e (elem_css_child);
                ::std::swap (*this, e); }
            break;
        case ct_identifier :
        case ct_keyword :
            {   PRESUME (! args.styled (), __FILE__, __LINE__);
                if (no_ns || (! args.snippet_))
                {   css_element e (nits, args.v_, namespaces_ptr (), args.t_.at (b).val_);
                    ::std::swap (*this, e); }
                else
                {   ::std::string el;
                    if (! all_ns) el = ns + ":" + args.t_.at (b).val_;
                    else el = args.t_.at (b).val_;
                    css_element e (nits, args.v_, args.ns_, el);
                    ::std::swap (*this, e); }
                b = next_non_whitespace (args.t_, b, to); }
            break;
        case ct_plus :
            pseudo = false;
            if (context.html_ver ().css_version () == css_1)
                nits.pick (nit_css_version, es_error, ec_css, quote (wo), ": + requires CSS 2.0 or better");
            else
            {   if (context.tv_profile ())
                    nits.pick (nit_profile, es_warning, ec_css, "The '+' adjacent selector may be ignored by the CSS TV profile");   
                css_element e (elem_css_precede_immediate);
                ::std::swap (*this, e); }
            break;
        case ct_splat :
            if (context.html_ver ().css_version () == css_1)
                nits.pick (nit_css_version, es_error, ec_css, quote (wo), ": * requires CSS 2.0 or better");
            else
            {   css_element e (elem_css_all);
                ::std::swap (*this, e);
                b = next_non_whitespace (args.t_, b, to); }
            break;
        case ct_squiggle :
            pseudo = false;
            if (context.css_selector () < 3)
                nits.pick (nit_css_version, es_error, ec_css, quote (wo), ": ~ requires CSS 3 selectors or better");
            else
            {   css_element e (elem_css_precede);
                ::std::swap (*this, e); }
            break;
        case ct_round_ket :
        case ct_square_ket :
        case ct_curly_ket :
        case ct_semicolon :
            if (context.css_nesting () >= 3) return;
            FALLTHROUGH;
        default :
            nits.pick (nit_css_element, es_error, ec_css, quote (tkn_rpt (args.t_.at (from))), ": element expected");
            return; }
    if (! pseudo)
    {   if ((b > 0) && (b < to))
        {   b = next_non_whitespace (args.t_, b, to);
            if (b < 0) nits.pick (nit_css_syntax, es_error, ec_css, "I believe that's technically termed an 'orrible mess");
            else switch (args.t_.at (b).t_)
            {   case ct_hash :
                case ct_dot :
                case ct_coco :
                case ct_colon :
                case ct_square_brac :
                    if (context.css_nesting () < 3)
                        nits.pick (nit_naughty_decoration, es_error, ec_css, quote (tkn_rpt (args.t_.at (b))), " cannot be decorated");
                    break;
                default:
                    parse (args, b, to);
                    break; } }
        return; }
    if (b < 0) return;
    for (int i = b; (i >= 0) && (i <= to); )
        switch (args.t_.at (i).t_)
        {   case ct_square_brac :
                if (context.html_ver ().css_version () == css_1)
                    nits.pick (nit_css_version, es_error, ec_css, quote (wo), ": [...] requires CSS 2.0 or better");
                else
                {   if (context.print_profile ())
                        nits.pick (nit_profile, es_warning, ec_css, "Attribute selectors may be ignored by the CSS Print profile");   
                    if (context.tv_profile ())
                        nits.pick (nit_profile, es_warning, ec_css, "Attribute selectors may be ignored by the CSS TV profile");   
                    decore_.emplace_back (args, b); }
                i =  next_non_whitespace (args.t_, i, to);
                break;
            case ct_dot :
            case ct_hash :
                {   int j = next_non_whitespace (args.t_, i, to);
                    if (j < 0) nits.pick (nit_css_syntax, es_error, ec_css, quote (wo), ": missing class or ID");
                    else decore_.emplace_back (args, i, j);
                    i = next_non_whitespace (args.t_, j, to); }
                break;
            case ct_coco :
            case ct_colon :
                {   int j = next_non_whitespace (args.t_, i, to);
                    if (j < 0)
                        nits.pick (nit_css_syntax, es_error, ec_css, quote (wo), ": unexpected here");
                    else if ((args.t_.at (j).t_ != ct_identifier) && (args.t_.at (j).t_ != ct_keyword))
                        nits.pick (nit_css_syntax, es_error, ec_css, quote (wo), ": missing pseudo name");
                    else
                    {   j = next_non_whitespace (args.t_, j, to);
                        if (j > 0)
                        {   if (args.t_.at (j).t_ == ct_round_brac)
                            {   j = token_find (args.t_, ct_round_ket, j, to);
                                if (j < 0) nits.pick (nit_css_syntax, es_error, ec_css, quote (wo), ": missing close bracket"); }
                            else --j; }
                        decore_.emplace_back (args, i, j, knotted);
                        if (j > 0)
                        {   i = next_non_whitespace (args.t_, j, to); break; } }
                    i = j; }
                break;                    
            case ct_plus :
            case ct_gt :
            case ct_squiggle :
                parse (args, i, to);
                return;
            case ct_comma :
            case ct_round_ket :
            case ct_square_ket :
            case ct_semicolon :
                if (context.css_nesting () >= 3) return;
                FALLTHROUGH;
            default :
                nits.pick (nit_css_syntax, es_error, ec_css, quote (tkn_rpt (args.t_.at (i))), ": unexpected (4)");
                return; } }

bool css_element::bef_aft () const
{   for (auto d : decore_)
        if (d.bef_aft ())
            return true;
    return false; }

void css_element::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    s -> mark (e_);
    for (auto d : decore_)
        d.accumulate (s, e_.get ()); }

::std::string css_element::rpt () const
{   ::std::string res (e_.name ());
    for (auto d : decore_)
        res += d.rpt ();
    return res; }

void css_element::validate (arguments& args)
{   for (auto i : decore_)
        i.validate (args); }

void css_element::shadow (::std::stringstream& ss, arguments& args)
{   for (auto i : decore_)
        i.shadow (ss, args); }
