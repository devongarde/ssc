/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "type/type_enum.h"

#define MIME_SCRIPT         0x00000001
#define NOT_SCRIPT          0x00000002
#define MIME_STYLE          0x00000004
#define MIME_FAUX           0x00000008

#define MIME_APPLICATION    0x00000010
#define MIME_AUDIO          0x00000020
#define MIME_FONT           0x00000040
#define MIME_IMAGE          0x00000080
#define MIME_MESSAGE        0x00000100
#define MIME_MODEL          0x00000200
#define MIME_MULTIPART      0x00000400
#define MIME_TEXT           0x00000800
#define MIME_VIDEO          0x00001000

#define MIME_UNOFFICIAL     0x00002000
#define MIME_WINDOWS        0x00004000
#define MIME_MACOS          0x00008000
#define MIME_IOS            0x00010000
#define MIME_ANDROID        0x00020000

#define MIME_VULNERABLE     0x00040000
#define MIME_WITHDRAWN      0x00080000

#define MIME_PAGE           0x00100000

#define MIME_JSON           0x01000000
#define MIME_ZIP            0x02000000
#define MIME_CBOR           0x04000000
#define MIME_XML            0x08000000
#define MIME_COMMON_MASK    0x0F000000

template < > inline void enum_n < t_mime, e_mimetype > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
    {   nits.pick (nit_mime, es_error, ec_type, "a mime type cannot be empty");
        enum_base < e_mimetype, t_mime > :: status (s_invalid); return; }
    original_ = s;
    if (v.is_5 () && compare_complain (nits, v, "module", s))
    {   enum_base < e_mimetype, t_mime > :: status (s_good);
        enum_base < e_mimetype, t_mime > :: value_ = mime_faux_module;
        return; }
    ::std::string::size_type pos = s.find ('/');
    if (pos == ::std::string::npos)
    {   nits.pick (nit_mime, es_error, ec_type, "bad mime type");
        enum_base < e_mimetype, t_mime > :: status (s_invalid); return; }
    if (s.substr (0, pos) == "example")  // don't complain about examples, just as example.org etc..
    {   nits.pick (nit_mime, es_info, ec_type, "avoid 'example' mime types on a live site");
        enum_base < e_mimetype, t_mime > :: status (s_good); return; }
    pos = s.find (';');
    if (pos == ::std::string::npos)
    {   if (symbol < html_version, e_mimetype > :: parse (nits, v, s, enum_base < e_mimetype, t_mime > :: value_))
        {   enum_base < e_mimetype, t_mime > :: status (s_good);
            return; } }
    else
    {   if (symbol < html_version, e_mimetype > :: parse (nits, v, s.substr (0, pos), enum_base < e_mimetype, t_mime > :: value_))
        {   enum_base < e_mimetype, t_mime > :: status (s_good);
            return; } }
    check_spelling (nits, v, s);
    nits.pick (nit_mime, es_warning, ec_type, quote (s), " is not a mimetype known to " PROG);
    enum_base < e_mimetype, t_mime > :: status (s_invalid); }

template < > inline void enum_n < t_mime, e_mimetype > :: verify_attribute (nitpick& nits, const html_version& v, const elem& , element* , const ::std::string& )
{   ::std::string s (quote (original_));
    if (enum_base < e_mimetype, t_mime > :: good ())
    {   if (context.tell (e_info))
            switch (enum_base < e_mimetype, t_mime > :: value_)
            {   case mime_application_font_sfnt :
                case mime_application_font_woff :
                case mime_application_vnd_gmx :
                case mime_audio_vnd_qcelp :
                case mime_image_xemf :
                case mime_image_xwmf :
                case mime_text_directory :
                    if (v >= html_5_0) nits.pick (nit_mime, es_warning, ec_type, quote (s), " is deprecated");
                    break;
                case mime_text_ecmascript :
                case mime_text_javascript :
                case mime_text_javascript_x :
                    if (v >= html_5_0) nits.pick (nit_mime, es_warning, ec_type, quote (s), " is obsoleted by the corresponding 'application/' mime type");
                    break;
                case mime_application_smil :
                case mime_application_vnd_3gpp_mcvideo_affiliation_info_xml :
                case mime_application_vnd_arastra_swi :
                case mime_application_vnd_geo_json :
                case mime_application_vnd_geocube_xml :
                case mime_application_vnd_ibm_afplinedata :
                case mime_application_vnd_ibm_modcap :
                case mime_application_vnd_informix_visionary :
                case mime_application_vnd_nokia_n_gage_symbian_install :
                case mime_application_vnd_youtube_yt :
                case mime_message_news :
                case mime_message_vnd_si_simp :
                case mime_text_vnd_si_uricatalogue :
                    if (v >= html_5_0) nits.pick (nit_mime, es_warning, ec_type, quote (s), " is obsolete");
                default: break; } } }

template < > struct type_master < t_mimelist > : public string_value < t_mimelist >
{   using string_value < t_mimelist > :: string_value;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   if ((v == html_2) && ! context.rfc_1867 ())
            nits.pick (nit_rfc_1867, es_error, ec_type, "ACCEPT in ", v.report (), " requires RFC 1867, which has been disabled");
        else if (! s.empty ())
        {   vstr_t ms = split_by_charset (s, ",");
            for (auto m : ms)
            {   enum_n < t_mime, e_mimetype > tm;
                tm.set_value (nits, v, m);
                if (tm.invalid ())
                {   nits.pick (nit_mime_list, es_error, ec_type, "a comma separated list of mime types is expected");
                    string_value < t_mimelist > :: status (s_invalid); return; } } } } };

template < > struct type_master < t_mimestar > : public string_value < t_mimestar >
{   using string_value < t_mimestar > :: string_value;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_mimestar > :: set_value (nits, v, s);
        if (string_value < t_mimestar > :: good ())
        {   if (string_value < t_mimestar > :: get_string ().find_first_of ('*') != ::std::string::npos) return;
            if (test_value < t_mime > (nits, v, s)) return;
            string_value < t_mimestar > :: status (s_invalid); return; } } };

template < > struct type_master < t_format > : enum_n < t_format, e_format >
{ using enum_n < t_format, e_format > :: enum_n; };

template < > struct type_master < t_mimemodule > : type_or_string < t_mimemodule, t_mime, sz_module >
{ using type_or_string < t_mimemodule, t_mime, sz_module > :: type_or_string; };

template < > struct type_master < t_mimeq > : type_one_or_both < t_mimeq, t_mimestar, sz_semicolon, t_q >
{ using type_one_or_both < t_mimeq, t_mimestar, sz_semicolon, t_q > :: type_one_or_both; };

template < > struct type_master < t_mimeqs > : type_at_least_one < t_mimeqs, sz_comma, t_mimeq >
{ using type_at_least_one < t_mimeqs, sz_comma, t_mimeq > :: type_at_least_one; };


e_format extension_format (nitpick& nits, const html_version& v, const ::std::string& ext, flags_t& flags);
bool is_compatible_extension (const html_version& v, const e_mimetype em, const ::std::string& ext);
bool has_external_vulnerability (nitpick& nits, const html_version& v, const e_mimetype em);
bool has_embed_vulnerability (nitpick& nits, const html_version& v, const e_mimetype em);
bool has_extension_incompatibility (nitpick& nits, const html_version& v, const e_mimetype em, const ::std::string& ext);
void check_extension_compatibility (nitpick& nits, const html_version& v, const e_mimetype em, const vurl_t& u, const bool src);
void check_extension_compatibility (nitpick& nits, const html_version& v, const ::std::string& s, const vurl_t& u, const bool src);
void check_extension_compatibility (nitpick& nits, const html_version& v, const vurl_t& u, const e_mimetype mt);
void check_extension_compatibility (nitpick& nits, const html_version& v, const vurl_t& u, const flags_t family);
void check_extension_vulnerability (nitpick& nits, const html_version& v, const ::std::string& ext, const bool local);
void check_extension_vulnerability (nitpick& nits, const html_version& v, const vurl_t& vu);
void check_mimetype_vulnerability (nitpick& nits, const html_version& v, const e_mimetype em, const bool local, const bool specified, const ::std::string& ref);
void check_mimetype_vulnerability (nitpick& nits, const html_version& v, const ::std::string& s, const bool local, const bool specified);
void check_vulnerability (nitpick& nits, const html_version& v, const e_mimetype em, const ::std::string& ext, const bool local);
void check_vulnerability (nitpick& nits, const html_version& v, const e_mimetype em, const vurl_t& u, const bool src);
void check_vulnerability (nitpick& nits, const html_version& v, const ::std::string& s, const vurl_t& u, const bool src);
void check_mimetype_family (nitpick& nits, const html_version& v, const e_mimetype em, const flags_t family, const ::std::string& ref);
void check_mimetype_family (nitpick& nits, const html_version& v, const ::std::string& s, const flags_t family);
