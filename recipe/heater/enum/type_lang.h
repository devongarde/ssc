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
#include "base/type_master.h"

template < > inline void enum_n < t_lang, e_lang > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty () || (s.length () > 8))
    {   enum_base < e_lang, t_lang > :: status (s_invalid); return; }
    original_ = s;
    ::std::string lang (s);
    const ::std::string::size_type pos = lang.find ('-');
    if (pos != ::std::string::npos) lang = lang.substr (0, pos);
    if ((lang.length () >= 1) && (lang.length () <= 3))
    {   if (! symbol < html_version, e_lang >  :: parse (nits, v, lang, enum_base < e_lang, t_lang > :: value_))
            nits.pick (nit_lingo, es_warning, ec_type, quote (lang), " is not a language code known to " PROG);
        enum_base < e_lang, t_lang > :: status (s_good);
        return; }
    nits.pick (nit_lingo, es_error, ec_type, quote (s), " appears to be an invalid language code");
    enum_base < e_lang, t_lang > :: status (s_invalid); };

template < > struct type_master < t_css_lang > : public tidy_string < t_css_lang >
{   using tidy_string < t_css_lang > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_css_lang > :: set_value (nits, v, s);
        if (tidy_string < t_css_lang > :: good ())
        {   ::std::string lang (tidy_string < t_css_lang > :: get_string ());
            if (lang.length () <= 8)
            {   ::std::string stub (lang);
                const ::std::string::size_type pos = stub.find ('-');
                if (pos != ::std::string::npos) stub = stub.substr (0, pos);
                if ((stub != "*") && ! test_value < t_lang > (nits, v, lang))
                    nits.pick (nit_lingo, es_warning, ec_type, quote (stub), " is not a language code known to " PROG);
                tidy_string < t_css_lang > :: status (s_good);
                return; } }
        nits.pick (nit_lingo, es_error, ec_type, quote (s), " appears to be an invalid language code");
        tidy_string < t_css_lang > :: status (s_invalid); } };
