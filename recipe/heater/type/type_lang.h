/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

template < > inline void enum_n < t_lang, e_lang > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty () || (s.length () > 8))
    {   enum_base < e_lang, t_lang > :: status (s_invalid); return; }
    original_ = s;
    ::std::string lang (s);
    ::std::string::size_type pos = s.find ('-');
    if (pos != ::std::string::npos) lang = lang.substr (0, pos);
    if ((lang.length () >= 1) && (lang.length () <= 3))
        if (symbol < e_lang >  :: parse (nits, v, lang, enum_base < e_lang, t_lang > :: value_))
        {   enum_base < e_lang, t_lang > :: status (s_good);
            return; }
    nits.pick (nit_lingo, es_warning, ec_type, quote (s), " is a rare or invalid language code");
    enum_base < e_lang, t_lang > :: status (s_invalid); }

template < > struct type_master < t_langs > : string_vector < t_langs, sz_comma >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_langs, sz_comma > :: set_value (nits, v, s);
        if (string_vector < t_langs, sz_comma > :: empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "a comma separated list of languages is expected");
            string_vector < t_langs, sz_comma > :: status (s_invalid); }
        else if (string_vector < t_langs, sz_comma > :: good ())
        {   bool allgood = true;
            for (auto arg : string_vector < t_langs, sz_comma > :: get ())
            {   type_master < t_lang > ar;
                ar.set_value (nits, v, arg);
                if (! ar.good ()) allgood = false; }
            if (allgood) return; }
        string_vector < t_langs, sz_comma > :: status (s_invalid); } };
