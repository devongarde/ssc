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

void statement::parse (nitpick& nits, arguments& args, const ::std::string& s)
{   reset ();
    vstr_t vs (uq2 (s, UQ_DQ | UQ_SQ | UQ_BS | UQ_ROUND | UQ_SQUARE | UQ_BRACE | UQ_TRIM, " "));
    if (vs.size () == 0)
        nits.pick (nit_css_version, es_error, ec_css, "expected statement keyword after '@'");
    else
    {   st_.set_value (nits, args.v_, vs.at (0));
        switch (st_.get_int ())
        {   case css_charset :
                if (args.v_.css_version () == css_1)
                    nits.pick (nit_css_version, es_error, ec_css, "@charset requires CSS 2.0 or later");
                break;
            case css_font_face :
                if (args.v_.css_version () == css_1)
                    nits.pick (nit_css_version, es_error, ec_css, "@font-face requires CSS 2.0 or later");
                break;
            case css_import :
                if (args.had_rule_)
                    nits.pick (nit_bad_import, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, "@import must precede all rules");
                {   type_master < t_css_url > u;
                    u.set_value (nits, args.v_, vs.at (1));
                    if (! u.invalid ())
                    {   ::std::string wot (vs.at (1));
                        if (compare_no_case (wot.substr (0, 3), "url"))
                        {   ::std::string::size_type pos = wot.find ('(');
                            if (pos != ::std::string::npos)
                            {   wot = wot.substr (pos + 1);
                                pos = wot.find (')');
                                if (pos != ::std::string::npos)
                                    wot = wot.substr (0, pos); } }
                        url uu (nits, args.v_, wot);
                        if (uu.valid ())
                        {   ::std::string content;
                            ::std::time_t when;
                            if (! uu.is_local ())
                                nits.pick (nit_reputation, es_warning, ec_css, quote (wot), ": the security, integrity, presentation and reputation of your site is dependent on the good practice and intent of the external site");
                            if (! cached_url (nits, args.v_, args.p_ -> get_directory (), uu, content, when))
                                nits.pick (nit_cannot_access, es_error, ec_css, "cannot access ", quote (wot), ", so cannot check it.");
                            else if (content.empty ())
                                nits.pick (nit_empty, es_warning, ec_css, quote (wot), " appears unencumbered by content");
                            else
                            {   nitpick knots;
                                VERIFY_NOT_NULL (args.p_, __FILE__, __LINE__);
                                args.p_ -> css ().parse_file (knots, args.ns_, *(args.p_), uu, true);
                                nits.merge (knots); } } } } 
                break;
            case css_media :
                if (args.v_.css_version () == css_1)
                    nits.pick (nit_css_version, es_error, ec_css, "@media requires CSS 2.0 or later");
                break;
            case css_page :
                if (args.v_.css_version () == css_1)
                    nits.pick (nit_css_dubious, ed_css_1, "7.1 Forward-compatible parsing", es_error, ec_css, "@page was undefined in the CSS 1 specification, although it did get a mention in a dubious example");
                break;
            default :
                break; } } }

void statement::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    s -> mark (st_.get ()); }

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
        case css_error :
            res = "@??? ();";
            break;
        default :
            GRACEFUL_CRASH (__FILE__, __LINE__);
            break; }
    return res; }  
