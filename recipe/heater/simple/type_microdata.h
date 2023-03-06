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
#include "base/type_master.h"
#include "microdata/microdata_itemid.h"

template < > struct type_master < t_itemid > : tidy_string < t_itemid >
{   typedef true_type has_int_type;
    using tidy_string < t_itemid > :: tidy_string;
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    { return invalid_itemid (nits, v, string_value < t_itemid > :: value_, e); } };

template < > struct type_master < t_itemprop > : string_vector < t_itemprop, sz_space >
{   using string_vector < t_itemprop, sz_space > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_itemprop, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_itemprop, sz_space > :: empty ())
        {   nits.pick (nit_bad_itemprop, ed_jul20, "5.2.2 Items", es_error, ec_type, "ITEMPROP requires a value");
            string_value < t_itemprop > :: status (s_invalid); }
        else if (string_vector < t_itemprop, sz_space > :: good ())
            if (v.mjr () >= 10)
                for (auto t : string_vector < t_itemprop, sz_space > :: get ())
                    if (t.find_first_of (":.") != ::std::string::npos)
                    {   nitpick nuts;
                        url u (nuts, v, t);
                        if (u.invalid ())
                        {   nits.merge (nuts);
                            tidy_string < t_itemprop > :: status (s_invalid); }
                        else if (u.is_local () || ! u.has_absolute_path ())
                        {   nits.pick (nit_bad_itemprop, es_error, ec_type, quote (t), " is neither an absolute url nor an identifier that has no colons, no full stops");
                            tidy_string < t_itemprop > :: status (s_invalid); } } } };

template < > struct type_master < t_itemtype > : string_vector < t_itemtype, sz_space >
{   using string_vector < t_itemtype, sz_space > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_itemtype, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_itemtype, sz_space > :: empty ())
        {   nits.pick (nit_empty, ed_jul20, "5.2.2 Items", es_error, ec_type, "ITEMTYPE requires a value");
            string_vector < t_itemtype, sz_space > :: status (s_invalid); }
        else if (string_vector < t_itemtype, sz_space > :: good ())
        {   if (v.mjr () < 10) return;
            bool allgood = true;
            for (auto arg : string_vector < t_itemtype, sz_space > :: get ())
                if (find_itemtype_index (nits, v, arg) == invalid_itemtype)
                    allgood = false;
            if (allgood) return; }
        string_vector < t_itemtype, sz_space > :: status (s_invalid); } };

template < > struct type_master < t_sha256 > : tidy_string < t_sha256 >
{    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_sha256 > :: set_value (nits, v, s);
        if (tidy_string < t_sha256 > :: empty ())
        {   nits.pick (nit_bad_sha, es_error, ec_type, "A sha256 hash cannot be empty");
            tidy_string < t_sha256 > :: status (s_invalid); }
        else if (tidy_string < t_sha256 > :: good ())
        {   ::std::string ss (tidy_string < t_sha256 > :: get_string ());
            if (ss.find_first_not_of (HEX) != ::std::string::npos)
                nits.pick (nit_bad_sha, es_error, ec_type, quote (s), " is not hexadecimal");
            else if (ss.length () != 56)
                nits.pick (nit_bad_sha, es_error, ec_type, quote (s), " is not precisely 56 characters long");
            else return;
            tidy_string < t_sha256 > :: status (s_invalid); } } };
