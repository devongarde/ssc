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

#define SCRIPT      0x00000001
#define NOT_SCRIPT  0x00000002
#define STYLE       0x00000004

template < > inline void enum_n < t_mime, e_mimetype > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
    {   nits.pick (nit_mime, es_error, ec_type, "a mime type cannot be empty");
        enum_base < e_mimetype, t_mime > :: status (s_invalid); return; }
    original_ = s;
    ::std::string::size_type pos = s.find ('/');
    if (pos == ::std::string::npos)
    {   nits.pick (nit_mime, es_error, ec_type, "bad mime type");
        enum_base < e_mimetype, t_mime > :: status (s_invalid); return; }
    if (s.substr (0, pos) == "example")  // don't complain about examples, just as example.org etc..
    {   nits.pick (nit_mime, es_info, ec_type, "avoid 'example' mime types on a live site");
        enum_base < e_mimetype, t_mime > :: status (s_good); return; }
    pos = s.find (';');
    if (pos == ::std::string::npos)
    {   if (symbol < e_mimetype > :: parse (nits, v, s, enum_base < e_mimetype, t_mime > :: value_))
        {   enum_base < e_mimetype, t_mime > :: status (s_good);
            return; } }
    else
    {   if (symbol < e_mimetype > :: parse (nits, v, s.substr (0, pos), enum_base < e_mimetype, t_mime > :: value_))
        {   enum_base < e_mimetype, t_mime > :: status (s_good);
            return; } }
    check_spelling (nits, v, s);
    nits.pick (nit_mime, es_error, ec_type, quote (s), " is not a standard mimetype");
    enum_base < e_mimetype, t_mime > :: status (s_invalid); }

template < > inline void enum_n < t_mime, e_mimetype > :: validate (nitpick& nits, const html_version& v, const elem& , const ::std::string& )
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
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
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
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_mimestar > :: set_value (nits, v, s);
        if (string_value < t_mimestar > :: good ())
        {   if (string_value < t_mimestar > :: get_string ().find_first_of ('*') != ::std::string::npos) return;
            if (test_value < t_mime > (nits, v, s)) return;
            string_value < t_mimestar > :: status (s_invalid); return; } } };

template < > struct type_master < t_mimeq > : type_one_or_both < t_mimeq, t_mimestar, sz_semicolon, t_q > { };
template < > struct type_master < t_mimeqs > : type_at_least_one < t_mimeqs, sz_comma, t_mimeq > { };
