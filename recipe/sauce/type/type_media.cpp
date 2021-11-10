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
#include "type/type_media.h"
#include "type/type_enum.h"

// need to revisit media queries
bool parse_media_query (nitpick& nits, const html_version& v, const ::std::string& sss)
{   ::std::string ss (trim_the_lot_off (sss));
    if (ss.empty ()) return true;
    vstr_t vm (split_by_charset (trim_the_lot_off (ss), ","));
    PRESUME (! vm.empty (), __FILE__, __LINE__);
    for (auto mq : vm)
    {   ::boost::algorithm::replace_all (mq, ":", " : ");
        ::boost::algorithm::replace_all (mq, "(", " ( ");
        ::boost::algorithm::replace_all (mq, ")", " ) ");
        ::boost::algorithm::replace_all (mq, "/", " / ");
        vstr_t kw (split_by_space (trim_the_lot_off (mq)));
        PRESUME (! kw.empty (), __FILE__, __LINE__);
        bool feature = false, measure = false, first = true, slash = false, lhs = false, digit = false;
        for (auto s : kw)
        {   bool fail = false;
            PRESUME (! s.empty (), __FILE__, __LINE__);
            if (s.length () == 1)
            {   switch (s.at (0))
                {   case '(' :
                        if (! feature) feature = true;
                        break;
                    case ')' :
                        if (feature) feature = lhs = measure = slash = false;
                        break;
                    case '/' :
                        if (lhs) slash = true;
                        else fail = true;
                        break;
                    case ':' :
                        if (feature && ! measure) measure = true;
                        else fail = true;
                        break;
                    default :
                        digit = (s.at (0) >= '0') && (s.at (0) <= '9');
                        fail = ! digit;
                        break; }
                if (fail)
                {   nits.pick (nit_mq_syntax, ed_mql, "3. Syntax", es_warning, ec_mql, "unexpected ", quote (s), " in the media query");
                    return false; }
                if (! digit) continue;
                digit = false; }
            if (feature)
            {   if (measure)
                {   switch (s.at (0))
                    {   case 'c' :
                        case 'C' :
                            if (compare_complain (nits, v, s, "coarse")) continue;
                            break;
                        case 'f' :
                        case 'F' :
                            if (compare_complain (nits, v, s, "fine") ||
                                compare_complain (nits, v, s, "fast")) continue;
                            break;
                        case 'h' :
                        case 'H' :
                           if (compare_complain (nits, v, s, "hover")) continue;
                            break;
                        case 'i' :
                        case 'I' :
                            if (compare_complain (nits, v, s, "interlace")) continue;
                            break;
                        case 'n' :
                        case 'N' :
                            if (compare_complain (nits, v, s, "none")) continue;
                            break;
                        case 'p' :
                        case 'P' :
                            if (compare_complain (nits, v, s, "p3") ||
                                compare_complain (nits, v, s, "progressive") ||
                                compare_complain (nits, v, s, "paged")) continue;
                            break;
                        case 'r' :
                        case 'R' :
                            if (compare_complain (nits, v, s, "rec2020")) continue;
                            break;
                        case 's' :
                        case 'S' :
                            if (compare_complain (nits, v, s, "srgb") ||
                                compare_complain (nits, v, s, "scroll") ||
                                compare_complain (nits, v, s, "slow")) continue;
                            break;
                        default : break; }
                    type_master < t_measure > m;
                    m.set_value (nits, v, s);
                    if (! m.good ()) return false;
                    if (! slash) lhs = true;
                    else { lhs = false; slash = false; } }
                else
                {   type_master < t_mediafeature > f;
                    f.set_value (nits, v, s);
                    if (! f.good ()) return false; }
                continue; }
            type_master < t_mediakeyword > key;
            nitpick knots;
            key.set_value (knots, v, s);
            if (key.good ())
            {   switch (key.get ())
                {   case mk_not :
                    case mk_only :
                        if (! first)
                        {   nits.pick (nit_mq_syntax, ed_mql, "3. Syntax", es_warning, ec_mql, "NOT and ONLY can only start a media query");
                            return false; }
                        break;
                    case mk_ident :
                        if (! first || (kw.size () != 1))
                        {   nits.pick (nit_mq_syntax, ed_mql, "3. Syntax", es_warning, ec_mql, "IDENT must be alone");
                            return false; }
                        break;
                    default : break; }
                first = false;
                continue; }
            type_master < t_media > f;
            f.set_value (nits, v, s);
            if (! f.good ()) return false;
            first = false; } }
    return true; }
