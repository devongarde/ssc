/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "type/type_httpequiv.h"
#include "type/type_cookie.h"
#include "utility/quote.h"
#include "webpage/page.h"

struct symbol_entry < html_version, e_httpequiv > httpequiv_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF },  "context", he_context },

    // sources:
    // mozilla (2020) https://developer.mozilla.org/en-US/docs/Web/HTML/Element/meta
    // standardista (2008) http://www.standardista.com/html5/http-equiv-the-meta-attribute-explained/
    // whatwg (??) (https://html.spec.whatwg.org/multipage/semantics.html#pragma-directives)
    // HTML 4.01 spec
    // RFC 1866
    // Living standard (Jan 2021 and earlier)

    { { HTML_JAN15 }, { HTML_UNDEF }, "accept", he_accept },
    { { HTML_JAN15 }, { HTML_UNDEF }, "accept-language", he_accept_language },
    { { HTML_JAN05 }, { HTML_UNDEF }, "allow", he_allow },
    { { HTML_2_0 }, { HTML_UNDEF }, "cache-control", he_cache_control },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "content-disposition", he_content_disposition },
    { { HTML_JAN05 }, { HTML_UNDEF }, "content-encoding", he_content_encoding },
    { { HTML_2_0 }, { HTML_UNDEF }, "content-language", he_content_language },
    { { HTML_JAN15 }, { HTML_UNDEF }, "content-location", he_content_location },
    { { HTML_4_0 }, { HTML_UNDEF }, "content-script-type", he_content_script_type },
    { { CSP_1 }, { HTML_UNDEF }, "content-security-policy", he_content_security_policy },
    { { CSP_1 }, { HTML_UNDEF }, "content-security-policy-report-only", he_content_security_policy_report_only },
    { { HTML_2_0 }, { HTML_UNDEF }, "content-type", he_content_type },
    { { HTML_4_0 }, { HTML_UNDEF }, "content-style-type", he_content_style_type },
    { { HTML_JAN15 }, { HTML_UNDEF }, "cookie", he_cookie },
    { { HTML_JAN15 }, { HTML_UNDEF }, "cross-origin-resource-policy", he_corp },
    { { HTML_JAN05 }, { HTML_UNDEF }, "date", he_date },
    { { HTML_4_0 }, { HTML_UNDEF }, "default-style", he_default_style },
    { { HTML_2_0 }, { HTML_UNDEF }, "expires", he_expires },
    { { HTML_2_0 }, { HTML_UNDEF }, "ext-cache", he_ext_cache },
    { { HTML_JAN05 }, { HTML_UNDEF }, "imagetoolbar", he_imagetoolbar },
    { { HTML_2_0 }, { HTML_3_0 }, "keywords", he_keywords },
    { { HTML_JAN05 }, { HTML_UNDEF }, "last-modified", he_last_modified },
    { { HTML_NOV17 }, { HTML_UNDEF }, "link", he_link },
    { { HTML_JAN05 }, { HTML_UNDEF }, "location", he_location },
    { { HTML_JAN15 }, { HTML_UNDEF }, "origin", he_origin },
    { { HTML_3_2 }, { HTML_UNDEF }, "page-enter", he_page_enter },
    { { HTML_3_2 }, { HTML_UNDEF }, "page-exit", he_page_exit },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_UNDEF }, "pics-label", he_pics_label },
    { { HTML_2_0 }, { HTML_UNDEF }, "pragma", he_pragma },
    { { HTML_JAN15 }, { HTML_UNDEF }, "referer", he_referrer },
    { { HTML_JAN15 }, { HTML_UNDEF }, "referrer-policy", he_referrer_policy },
    { { HTML_2_0 }, { HTML_UNDEF }, "refresh", he_refresh },
    { { HTML_2_0 }, { HTML_3_0 }, "reply-to", he_reply_to },
    { { HTML_2_0 }, { HTML_5_2 }, "set-cookie", he_set_cookie },
    { { HTML_3_2 }, { HTML_UNDEF }, "site-enter", he_site_enter },
    { { HTML_3_2 }, { HTML_UNDEF }, "site-exit", he_site_exit },
    { { HTML_2_0 }, { HTML_5_2 }, "vary", he_vary },
    { { HTML_4_0 }, { HTML_UNDEF }, "window-target", he_window_target },
    { { HTML_JAN05 }, { HTML_UNDEF }, "www-authenticate", he_www_authenticate },
    { { HTML_JAN11 }, { HTML_AUG13 }, "x-content-security-policy", he_x_content_security_policy },
    { { HTML_JAN15 }, { HTML_UNDEF }, "x-content-type-options", he_x_content_type_options },
    { { HTML_JAN11 }, { HTML_FEB13 }, "x-webkit-csp", he_webkit_csp },
    { { HTML_JAN05 }, { HTML_UNDEF }, "x-ua-compatible", he_x_ua_compatible } };

void httpequiv_init (nitpick& nits)
{   type_master < t_httpequiv > :: init (nits, httpequiv_symbol_table, sizeof (httpequiv_symbol_table) / sizeof (symbol_entry < html_version, e_httpequiv >)); }

template < e_type TYPE > ::std::string validate_he_content (nitpick& nits, const html_version& v, const ::std::string& content, page& )
{   type_master < TYPE > t;
    t.set_value (nits, v, content);
    if (! t.good ()) return ::std::string ();
    return t.get_string (); }

template < > ::std::string validate_he_content < t_content_type > (nitpick& nits, const html_version& v, const ::std::string& content, page& p)
{   type_master < t_content_type > t;
    t.set_value (nits, v, content);
    if (! t.good ()) return ::std::string ();
    ::std::string cs (t.get_charset ());
    p.charset (nits, v, cs);
    return t.get_string (); }

template < > ::std::string validate_he_content < t_lang > (nitpick& nits, const html_version& v, const ::std::string& content, page& p)
{   type_master < t_lang > t;
    t.set_value (nits, v, content);
    if (! t.good ()) return ::std::string ();
    ::std::string l (t.get_string ());
    p.lang (nits, v, l);
    return t.get_string (); }

::std::string validate_httpequiv_content (nitpick& nits, const html_version& v, const e_httpequiv he, const ::std::string& content, page& p)
{   p.mark_meta (he);
    switch (he)
    {   case he_accept : return validate_he_content < t_mimeqs > (nits, v, content, p);
        case he_accept_language : return validate_he_content < t_langqs > (nits, v, content, p);
        case he_cache_control : return validate_he_content < t_cache > (nits, v, content, p);
        case he_content_encoding : return validate_he_content < t_content_encoding > (nits, v, content, p);
        case he_content_disposition : break;
        case he_content_language : return validate_he_content < t_lang > (nits, v, content, p);
        case he_content_location :
        case he_referrer : return validate_he_content < t_url > (nits, v, content, p);
        case he_content_script_type : return validate_he_content < t_mime > (nits, v, content, p);
        case he_content_security_policy :
        case he_content_security_policy_report_only :
        case he_x_content_security_policy :
        case he_webkit_csp : return validate_he_content < t_csp > (nits, v, content, p);
        case he_cookie :
        case he_set_cookie : return validate_he_content < t_cookies > (nits, v, content, p);
        case he_content_style_type : return validate_he_content < t_mime > (nits, v, content, p);
        case he_content_type : return validate_he_content < t_content_type > (nits, v, content, p);
        case he_context : break;
        case he_corp : return validate_he_content < t_corp > (nits, v, content, p);
        case he_date :
        case he_expires :
        case he_last_modified : return validate_he_content < t_datetime > (nits, v, content, p);
        case he_default_style :  return validate_he_content < t_compact > (nits, v, content, p);
        case he_ext_cache : break;
        case he_imagetoolbar : return validate_he_content < t_yesno > (nits, v, content,p);
        case he_keywords :
        case he_reply_to :
            nits.pick (nit_use_metaname, es_warning, ec_type, "use the NAME attribute, not HTTP-EQUIV, for this information");
            break;
        case he_link :
            if (! content.empty () && (content.find ("rel=") == ::std::string::npos))
                nits.pick (nit_bad_link_pragma, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_error, ec_type, "rel is required");
            return validate_he_content < t_links > (nits, v, content, p);
        case he_location : return validate_he_content < t_location > (nits, v, content, p);
        case he_origin : return validate_he_content < t_root_url > (nits, v, content, p);
        case he_page_enter :
        case he_page_exit :
        case he_site_enter :
        case he_site_exit : return validate_he_content < t_reveal_trans > (nits, v, content, p);
        case he_pics_label : return validate_he_content < t_pics > (nits, v, content, p);
        case he_pragma : return validate_he_content < t_pragma > (nits, v, content, p);
        case he_referrer_policy :
            if (content.empty ()) break;
            return validate_he_content < t_referrer > (nits, v, content, p);
        case he_refresh : return validate_he_content < t_refresh > (nits, v, content, p);
        case he_www_authenticate : return validate_he_content < t_existential > (nits, v, content, p);
        case he_window_target : break;
        case he_x_content_type_options : return validate_he_content < t_x_content_type_options > (nits, v, content, p);
        case he_x_ua_compatible : return validate_he_content < t_x_ua_compatible > (nits, v, content, p);
        case he_vary : break;
        default : nits.pick (nit_equiv_error, es_error, ec_program, "missing http_equiv type check for ", static_cast < int > (he)); }
    return ::std::string (); }

vstr_t split_sides_at_semi (nitpick& nits, const ::std::string& s, const ::std::size_t min_args, const ::std::size_t max_args)
{   vstr_t res (split_by_charset (s, ";"));
    if ((min_args > 0) && (res.size () < min_args))
        nits.pick (nit_missing_content, es_warning, ec_type, "at least ", min_args, " arguments expected in content");
    else if ((max_args > 0) && (res.size () > max_args))
        nits.pick (nit_ignoring_extra_content, es_warning, ec_type, "ignoring excess arguments in content (no more than ", max_args, " expected)");
    return res; }

bool linkarg_set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   const ::std::string::size_type pos = s.find ('=');
    if ((pos == ::std::string::npos) || (pos == s.length () - 1))
        nits.pick (nit_bad_link_pragma, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_error, ec_type, "missing argument");
    else if (pos == 0)
        nits.pick (nit_bad_link_pragma, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_error, ec_type, "missing keyword");
    else
    {   ::std::string param (s.substr (0, pos));
        ::std::string arg (uq (s.substr (pos+1)));
        if (! test_value < t_linkparam > (nits, v, param))
        {   nits.pick (nit_nocando, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_info, ec_type, quote (param), " is not recognised, so is not verified");
            return true; }
        switch (examine_value < t_linkparam > (nits, v, param))
        {   case lp_rev :
                nits.pick (nit_bad_link_pragma, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_warning, ec_type, "rev is deprecated");
                [[fallthrough]];
            case lp_rel :
                if (arg.find_first_not_of (ALPHADDD) != ::std::string::npos)
                {   nits.pick (nit_nocando, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_info, ec_type, "apologies, but ", PROG, " cannot verify this rel/rev");
                    return true; }
                if (test_value < t_rel > (nits, v, arg)) return true;
                break;
            case lp_anchor :
                if (test_value < t_url > (nits, v, arg)) return true;
                break;
            case lp_hreflang :
                if (test_value < t_lang > (nits, v, arg)) return true;
                break;
            case lp_media :
                if (test_value < t_mql > (nits, v, arg)) return true;
                break;
            case lp_type :
                if (test_value < t_mime > (nits, v, arg)) return true;
                break;
            default : return true; } }
    return false; }
