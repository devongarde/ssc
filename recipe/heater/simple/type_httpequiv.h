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

#pragma once
#include "enum/type_enum.h"
#include "type/type_csp.h"

::std::string validate_httpequiv_content (nitpick& nits, const html_version& v, const e_httpequiv he, const ::std::string& content, page& p);
vstr_t split_sides_at_semi (nitpick& nits, const ::std::string& s, const ::std::size_t min_args = 2, const ::std::size_t max_args = 2);

template < > struct type_master < t_cache > : public tidy_string < t_cache >
{   using tidy_string < t_cache > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   tidy_string < t_cache > :: set_value (nits, v, ss);
        ::std::string s = tidy_string < t_cache > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "cache value required");
            tidy_string < t_cache > :: status (s_invalid); }
        else if (good ())
        {   const ::std::string::size_type pos = s.find ('=');
            ::std::string arg;
            bool booboo = false;
            if (pos != ::std::string::npos)
            {   if ((pos == 0) || (pos == s.length () - 1)) booboo = true;
                else
                {   arg = s.substr (pos+1);
                    s = s.substr (0, pos);
                    if (arg.find_first_not_of (DENARY) != ::std::string::npos) booboo = true; }
                if (booboo) nits.pick (nit_bad_cache, ed_rfc_7234, "5.2.1. Request Cache-Control Directives", es_error, ec_type, "bad syntax or bad integer"); }
            if (! booboo)
                if (! test_value < t_cachekey > (nits, v, s))
                    nits.pick (nit_bad_cache, ed_rfc_7234, "5.2.1. Request Cache-Control Directives", es_error, ec_type, quote (s), " is not a valid cache keyword");
                else switch (examine_value < t_cachekey > (nits, v, s))
                {   case ck_maxage :
                    case ck_minfresh :
                        if (arg.empty ())
                        {   nits.pick (nit_bad_cache, ed_rfc_7234, "5.2.1. Request Cache-Control Directives", es_error, ec_type, quote (s), " requires an integer argument (for example, 'max-sausages=5')");
                            booboo = true; }
                        break;
                    case ck_nocache :
                    case ck_nostore :
                    case ck_notransform :
                    case ck_onlyifcached :
                        if (! arg.empty ())
                        {   nits.pick (nit_bad_cache, ed_rfc_7234, "5.2.1. Request Cache-Control Directives", es_error, ec_type, quote (s), " takes no argument");
                            booboo = true; }
                        break;
                    default : break; }
            if (! booboo) return; }
        tidy_string < t_cache > :: status (s_invalid); } };


template < > struct type_master < t_content_type > : tidy_string < t_content_type >
{   ::std::string charset_;
    using tidy_string < t_content_type > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_content_type > :: set_value (nits, v, s);
        if (tidy_string < t_content_type > :: good ())
        {   vstr_t sides (split_sides_at_semi (nits, tidy_string < t_content_type > :: get_string ()));
            if (sides.size () > 0)
            {   if (! compare_no_case (sides.at (0), HTML_TYPE))
                    nits.pick (nit_text_html_expected, es_error, ec_type, "content type should be '" HTML_TYPE ";charset=...'");
                if (sides.size () == 1)
                    nits.pick (nit_charset_missing, es_error, ec_type, "the charset is missing");
                else
                {   ::std::string ss (trim_the_lot_off (sides.at (1)));
                    const ::std::string::size_type pos = ss.find ('=');
                    if ((pos != ::std::string::npos) && compare_no_case (ss.substr (0, pos), "charset"))
                    {   type_master < t_charset > cs;
                        ::std::string sss (ss.substr (pos+1));
                        cs.set_value (nits, v, sss);
                        if (cs.good ())
                        {   charset_ = sss; return; } } }
        tidy_string < t_content_type > :: status (s_invalid); } } }
    ::std::string get_charset () const { return charset_; } };

template < > struct type_master < t_csp_sauce > : tidy_string < t_csp_sauce >
{   using tidy_string < t_csp_sauce > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_csp_sauce > :: set_value (nits, v, s);
        if (! tidy_string < t_csp_sauce > :: good ()) return;
        ::std::string ss (tidy_string < t_csp_sauce > :: get_string ());
        const ::std::string::size_type len = ss.length ();
        if (! ss.empty ())
            if ((len > 1) && (ss.at (0) == '\'') && (ss.at (len - 1) == '\''))
            {   if (v >= csp_c2)
                {   ss = ss.substr (1, len - 2);
                    const ::std::string::size_type pos = ss.find ('-');
                    if (pos != ::std::string::npos)
                    {   if ((pos == 5) && compare_no_case (EVIL, ss.substr (0, 5)))
                        {   if (ss.substr (6).find_first_not_of (ALPHABET DENARY "+/-_*") == ::std::string::npos) return;
                            nits.pick (nit_bad_number_once, ed_csp, "Content Security Policy Directives", es_error, ec_attribute, "invalid number once"); }
                        else if (pos != 6)
                            nits.pick (nit_bad_csp_source, ed_csp, "Content Security Policy Directives", es_error, ec_attribute, quote (ss.substr (0, pos)), " is an unrecognised source");
                        else
                        {   ::std::string algo (ss.substr (0, 6));
                            if (compare_no_case (algo, "sha256") ||
                                compare_no_case (algo, "sha384") ||
                                compare_no_case (algo, "sha512")) return;
                            nits.pick (nit_invalid_algorithm, ed_csp, "Content Security Policy Directives", es_error, ec_attribute, quote (ss.substr (0, 6)), " is an unrecognised digest"); } } } }
            else
            if (ss.at (len - 1) == ':')
            {   e_protocol prot;
                if (symbol < html_version, e_protocol > :: parse (nits, v, ss.substr (0, len - 1), prot)) return; }
            else
            {   if (ss.find ('*') != ::std::string::npos) return;
                url u (nits, v, ss, pr_https);
                if (! u.invalid ()) return; }
        tidy_string < t_csp_sauce > :: status (s_invalid); } };

template < > struct type_master < t_csp > : tidy_string < t_csp >
{   using tidy_string < t_csp > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_csp > :: set_value (nits, v, s);
        if (tidy_string < t_csp > :: good ())
        {   vstr_t sides (split_sides_at_semi (nits, tidy_string < t_csp > :: get_string (), 1, 0));
            for (auto ss : sides)
            {   ::std::string sss (trim_the_lot_off (ss));
                if (! sss.empty ())
                {   vstr_t csp (split_by_space (trim_the_lot_off (sss)));
                    if (csp.size () > 0)
                        if (! test_value < t_csp_directive > (nits, v, csp.at (0)))
                            tidy_string < t_csp > :: status (s_invalid);
                        else
                        {   const e_csp_directive cd = examine_value < t_csp_directive > (nits, v, csp.at (0));
                            switch (cd)
                            {   case csp_plugin_types :
                                    if (! compare_no_case (csp.at (1), QNONE))
                                        for (::std::size_t i = 1; i < csp.size (); ++i)
                                            if (! test_value < t_mime > (nits, v, csp.at (i)))
                                                 tidy_string < t_csp > :: status (s_invalid);
                                    break;
                                case csp_sandbox :
                                    for (::std::size_t i = 10; i < csp.size (); ++i)
                                        if (! test_value < t_sandbox > (nits, v, csp.at (i)))
                                             tidy_string < t_csp > :: status (s_invalid);
                                    break;
                                case csp_frame_ancestors :
                                    if (csp.size () < 2)
                                        nits.pick (nit_bad_csp_directive, ed_csp, "Content Security Policy Directives", es_error, ec_type, quote (csp.at (0)), " requires arguments");
                                    else for (::std::size_t i = 1; i < csp.size (); ++i)
                                        if (! test_value < t_csp_ancestor > (nits, v, csp.at (i)))
                                            tidy_string < t_csp > :: status (s_invalid);
                                    break;
                                case csp_report_uri :
                                    for (::std::size_t i = 10; i < csp.size (); ++i)
                                        if (! test_value < t_url > (nits, v, csp.at (i)))
                                             tidy_string < t_csp > :: status (s_invalid);
                                    break;
                                case csp_report_to :
                                case csp_block_all_mixed_content :
                                case csp_update_insecure_requests :
                                case csp_require_sri_for :
                                    break;
                                default :
                                    if (csp.size () < 2)
                                        nits.pick (nit_bad_csp_directive, ed_csp, "Content Security Policy Directives", es_error, ec_type, quote (csp.at (0)), " requires arguments");
                                    else if ((csp.size () != 2) || ! compare_no_case (csp.at (1), QNONE))
                                        for (::std::size_t i = 1; i < csp.size (); ++i)
                                            if (! test_value < t_csp_source > (nits, v, csp.at (i)))
                                                tidy_string < t_csp > :: status (s_invalid); } } } } } } };

bool linkarg_set_value (nitpick& nits, const html_version& v, const ::std::string& s);

template < > struct type_master < t_linkarg > : public tidy_string < t_linkarg >
{   using tidy_string < t_linkarg > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   tidy_string < t_linkarg > :: set_value (nits, v, ss);
        ::std::string s = tidy_string < t_linkarg > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "value required (", type_name (t_linkarg), ")");
            tidy_string < t_linkarg > :: status (s_invalid); }
        else if (good ())
            if (! linkarg_set_value (nits, v, s))
                tidy_string < t_linkarg > :: status (s_invalid); } };

template < > struct type_master < t_linkitself > : tidy_string < t_linkitself >
{   using tidy_string < t_linkitself > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& ss) // sanity test only
    {   tidy_string < t_linkitself > :: set_value (nits, v, ss);
        ::std::string s = tidy_string < t_linkitself > :: get_string ();
        if (s.empty ())
            nits.pick (nit_bad_link_pragma, es_error, ec_type, "oddly, a link pragma needs a link");
        else if (good ())
        if (tidy_string < t_linkitself > :: good ())
            if ((s.length () < 3) || (s.at (0) != '<') || (s.at (s.length () -1) != '>'))
                nits.pick (nit_bad_link_pragma, es_error, ec_type, "the URL must be enclosed in angular brackets");
            else if (test_value < t_url > (nits, v, s.substr (1, s.length ()-2))) return;
        tidy_string < t_linkitself > :: status (s_invalid); } };

template < > struct type_master < t_location > : tidy_string < t_location >
{   using tidy_string < t_location > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_location > :: set_value (nits, v, s);
        if (tidy_string < t_location > :: good ())
        {   vstr_t sides (split_sides_at_semi (nits, tidy_string < t_location > :: get_string ()));
            if (sides.size () > 0)
            {   if (! compare_no_case (sides.at (0), "0"))
                    nits.pick (nit_text_html_expected, ed_w3, HTTPS_W3 "/TR/2016/NOTE-WCAG20-TECHS-20161007/F41", es_error, ec_type, "do not use location with any period but zero, to avoid causing some users significant problems");
                if (sides.size () == 1)
                    nits.pick (nit_url_empty, es_error, ec_type, "the url is missing");
                else
                {   url u (nits, v, trim_the_lot_off (sides.at (2)));
                    if (! u.invalid ()) { string_value < t_location > :: set_value (nits, v, u.original ()); return; } } }
            tidy_string < t_location > :: status (s_invalid); } } };

template < > struct type_master < t_refresh > : tidy_string < t_refresh >
{   using tidy_string < t_refresh > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_refresh > :: set_value (nits, v, s);
        if (tidy_string < t_refresh > :: good ())
        {   vstr_t sides (split_sides_at_semi (nits, tidy_string < t_refresh > :: get_string (), 1));
            if (sides.size () > 1)
            {   if (! compare_no_case (sides.at (0), "0"))
                    nits.pick (nit_refresh_zero, ed_w3, HTTPS_W3 "/TR/2016/NOTE-WCAG20-TECHS-20161007/F41", es_error, ec_type, "do not use refresh with any period but zero, to avoid causing some users significant problems");
                ::std::string x (trim_the_lot_off (sides.at (1)));
                if (x.length () < 5 || ! compare_no_case (x.substr (0, 4), "url="))
                    nits.pick (nit_url_empty, es_error, ec_type, "the url, if present, must be preceded by 'url='");
                else
                {   url u (nits, v, x.substr (0, 5));
                    if (! u.invalid ())
                    {   string_value < t_refresh > :: set_value (nits, v, u.original ()); return; } } }
            tidy_string < t_refresh > :: status (s_invalid); } } };

template < > struct type_master < t_x_ua_compatible > : tidy_string < t_x_ua_compatible >
{   using tidy_string < t_x_ua_compatible > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s) // sanity test only
    {   tidy_string < t_x_ua_compatible > :: set_value (nits, v, s);
        if (! compare_no_case (tidy_string < t_x_ua_compatible > :: get_string (), "IE=edge"))
        {   tidy_string < t_x_ua_compatible > :: status (s_invalid);
            nits.pick (nit_x_ua_compatible, es_error, ec_type, quote (s), ": only 'IE=edge' is valid"); } } };
