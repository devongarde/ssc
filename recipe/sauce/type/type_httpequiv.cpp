/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

struct symbol_entry < e_httpequiv > httpequiv_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF },  "context", he_context },

    // sources:
    // mozilla (2020) https://developer.mozilla.org/en-US/docs/Web/HTML/Element/meta
    // standardista (2008) http://www.standardista.com/html5/http-equiv-the-meta-attribute-explained/
    // whatwg (??) (https://html.spec.whatwg.org/multipage/semantics.html#pragma-directives)
    // HTML 4.01 spec
    // RFC 1866

    { { HTML_5_0 }, { HTML_UNDEF }, "allow", he_allow },
    { { HTML_2_0 }, { HTML_UNDEF }, "cache-control", he_cache_control },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "content-disposition", he_content_disposition },
    { { HTML_5_0 }, { HTML_UNDEF }, "content-encoding", he_content_encoding },
    { { HTML_2_0 }, { HTML_UNDEF }, "content-language", he_content_language },
    { { HTML_4_0 }, { HTML_UNDEF }, "content-script-type", he_content_script_type },
    { { HTML_5_0 }, { HTML_UNDEF }, "content-security-policy", he_content_security_policy },
    { { HTML_2_0 }, { HTML_UNDEF }, "content-type", he_content_type },
    { { HTML_4_0 }, { HTML_UNDEF }, "content-style-type", he_content_style_type },
    { { HTML_5_0 }, { HTML_UNDEF }, "date", he_date },
    { { HTML_4_0 }, { HTML_UNDEF }, "default-style", he_default_style },
    { { HTML_2_0 }, { HTML_UNDEF }, "expires", he_expires },
    { { HTML_2_0 }, { HTML_UNDEF }, "ext-cache", he_ext_cache },
    { { HTML_5_0 }, { HTML_UNDEF }, "imagetoolbar", he_imagetoolbar },
    { { HTML_2_0 }, { HTML_3_0 }, "keywords", he_keywords },
    { { HTML_5_0 }, { HTML_UNDEF }, "last-modified", he_last_modified },
    { { HTML_5_0 }, { HTML_UNDEF }, "location", he_location },
    { { HTML_3_2 }, { HTML_UNDEF }, "page-enter", he_page_enter },
    { { HTML_3_2 }, { HTML_UNDEF }, "page-exit", he_page_exit },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_UNDEF }, "pics-label", he_pics_label },
    { { HTML_2_0 }, { HTML_UNDEF }, "pragma", he_pragma },
    { { HTML_2_0 }, { HTML_UNDEF }, "refresh", he_refresh },
    { { HTML_2_0 }, { HTML_3_0 }, "reply-to", he_reply_to },
    { { HTML_2_0 }, { HTML_5_2 }, "set-cookie", he_set_cookie },
    { { HTML_3_2 }, { HTML_UNDEF }, "site-enter", he_site_enter },
    { { HTML_3_2 }, { HTML_UNDEF }, "site-exit", he_site_exit },
    { { HTML_2_0 }, { HTML_5_2 }, "vary", he_vary },
    { { HTML_4_0 }, { HTML_UNDEF }, "window-target", he_window_target },
    { { HTML_5_0 }, { HTML_UNDEF }, "www-authenticate", he_www_authenticate },
    { { HTML_5_0 }, { HTML_UNDEF }, "x-ua-compatible", he_x_ua_compatible } };

void httpequiv_init (nitpick& nits)
{   type_master < t_httpequiv > :: init (nits, httpequiv_symbol_table, sizeof (httpequiv_symbol_table) / sizeof (symbol_entry < e_httpequiv >)); }

template < e_type TYPE > ::std::string validate_he_content (nitpick& nits, const html_version& v, const ::std::string& content)
{   type_master < TYPE > t;
    t.set_value (nits, v, content);
    if (! t.good ()) return ::std::string ();
    return t.get_string (); }

::std::string validate_httpequiv_content (nitpick& nits, const html_version& v, const e_httpequiv he, const ::std::string& content)
{   switch (he)
    {   case he_cache_control :
        case he_content_encoding : return validate_he_content < t_content_encoding > (nits, v, content);
        case he_content_disposition : break;
        case he_content_language : return validate_he_content < t_lang > (nits, v, content);
        case he_content_script_type : return validate_he_content < t_mime > (nits, v, content);
        case he_content_style_type : return validate_he_content < t_mime > (nits, v, content);
        case he_content_type : return validate_he_content < t_content_type > (nits, v, content);
        case he_context : break;
        case he_default_style :  return validate_he_content < t_compact > (nits, v, content);
        case he_date :
        case he_expires : return validate_he_content < t_datetime > (nits, v, content);
        case he_ext_cache : break;
        case he_imagetoolbar : return validate_he_content < t_yesno > (nits, v, content);
        case he_location : return validate_he_content < t_location > (nits, v, content);
        case he_site_enter :
        case he_site_exit :
        case he_page_enter :
        case he_page_exit : return validate_he_content < t_reveal_trans > (nits, v, content);
        case he_pics_label : return validate_he_content < t_pics > (nits, v, content);
        case he_pragma : return validate_he_content < t_pragma > (nits, v, content);
        case he_refresh : return validate_he_content < t_refresh > (nits, v, content);
        case he_set_cookie : return validate_he_content < t_setcookie > (nits, v, content);
        case he_window_target : break;
        case he_keywords :
        case he_reply_to :  nits.pick (nit_use_metaname, es_warning, ec_type, "use the NAME attribute, not HTTP-EQUIV, for this information");
                            break;
        case he_vary : break;
        default : nits.pick (nit_equiv_error, es_error, ec_program, "missing http_equiv type check for ", static_cast < int > (he)); }
    return ::std::string (); }

vstr_t split_sides_at_semi (nitpick& nits, const ::std::string& s, const ::std::size_t min_args, const ::std::size_t max_args)
{   vstr_t res (split_by_charset (s, ";"));
    if (res.size () < min_args)
        nits.pick (nit_ignoring_extra_content, es_warning, ec_type, "at least ", min_args, " arguments expected in content");
    else if (res.size () > max_args)
        nits.pick (nit_ignoring_extra_content, es_warning, ec_type, "ignoring excess arguments in content (no more than ", max_args, " expected)");
    return res; }
