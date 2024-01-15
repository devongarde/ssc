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

#pragma once
#include "base/type_master.h"
struct arguments;

bool parse_media_query (nitpick& nits, const html_version& v, const ::std::string& s, element* e);

template < > struct type_master < t_mql > : tidy_string < t_mql >
{   using tidy_string < t_mql > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_mql > :: set_value (nits, v, s);
        if (tidy_string < t_mql > :: empty ())
            nits.pick (nit_mq_syntax, ed_mql, "3. Syntax", es_warning, ec_mql, "is the empty media value intentional?");
        else if (tidy_string < t_mql > :: good ())
            if (parse_media_query (nits, v, tidy_string < t_mql > :: get_string (), box ())) return;
        tidy_string < t_mql > :: status (s_invalid);
        return; } };

template < > struct type_master < t_mqls > : tidy_string < t_mqls >
{   using tidy_string < t_mqls > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_mqls > :: set_value (nits, v, s);
        if (tidy_string < t_mqls > :: empty ())
            nits.pick (nit_mq_syntax, ed_rfc_7231, "5.3.2. Accept", es_warning, ec_mql, "are the empty media values intentional?");
        else
        if (tidy_string < t_mqls > :: good ())
        {   vstr_t mql (split_by_charset (s, ";"));
            bool whoops = false;
            for (auto ss : mql)
                if (! parse_media_query (nits, v, ss, box ()))
                    whoops = true;
            if (! whoops) return; }
        tidy_string < t_mqls > :: status (s_invalid);
        return; } };

