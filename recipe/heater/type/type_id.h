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
#include "type/type_master.h"
bool invalid_id_result (nitpick& nits, const html_version& v, const ::std::string& s, const element* const e);

template < > struct type_master < t_id > : tidy_string < t_id >
{   bool tested_ = false, predefined_ = false;
    using tidy_string < t_id > :: tidy_string;
    void swap (type_master < t_id >& t) noexcept
    {   ::std::swap (tested_, t.tested_);
        ::std::swap (predefined_, t.predefined_);
        tidy_string < t_id >::swap (t); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& arg)
    {   tidy_string < t_id > :: set_value (nits, v, arg);
        const ::std::string& s = tidy_string < t_id > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_bad_id, es_error, ec_type, "an ID cannot be empty");
            tidy_string < t_id > :: status (s_invalid); }
        switch (v.mjr ())
        {   case 3 :
                if (v.mnr () == 2)
                {   if (::std::string (ALPHABET).find (s.at (0)) == ::std::string::npos)
                    {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " does not start with a letter");
                        tidy_string < t_id > :: status (s_invalid); } }
                break;
            case 4 :
                if (::std::string (ALPHABET).find (s.at (0)) == ::std::string::npos)
                {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " does not start with a letter");
                    tidy_string < t_id > :: status (s_invalid); }
                else if (v.mnr () == 0)
                {   if (s.find_first_not_of (ALPHADDD) != ::std::string::npos)
                    {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " may only contain letters or digits");
                        tidy_string < t_id > :: status (s_invalid); } }
                else if (s.find_first_not_of (IDS) != ::std::string::npos)
                {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " may only contain letters, digits, '_', and ':'");
                    tidy_string < t_id > :: status (s_invalid); }
                break;
            case 5 :
                if (find_if (s.cbegin (), s.cend (), ::std::iswspace) != s.cend ())
                {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " may not contain a space");
                    tidy_string < t_id > :: status (s_invalid); }
                break;
            default : break; }
        tested_ = predefined_ = false; }
   bool invalid_id (nitpick& nits, const html_version& , ids_t& ids, element* pe)
   {    if (bad ()) return false;
        if (! tested_)
        {   ::std::string s (tidy_string < t_id > :: get_string ());
            predefined_ = ids.has_id (s);
            if (! predefined_) ids.insert_id (s, pe);
            else if (ids.unique ())
            {   nits.pick (nit_id_exists, es_error, ec_type, quote (s), " is defined elsewhere");
                tidy_string < t_id > :: status (s_invalid); }
            tested_ = true; }
        return predefined_; } };

template < > struct type_master < t_idref > : tidy_string < t_idref >
{   using tidy_string < t_idref > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_idref > :: set_value (nits, v, s);
        if (s.empty ())
        {   nits.pick (nit_bad_id, es_error, ec_type, "an id cannot be empty");
            tidy_string < t_idref > :: status (s_invalid); }
        else if (::std::find_if (s.cbegin (), s.cend (), ::std::iswspace) != s.cend ())
        {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " contains a space");
            tidy_string < t_idref > :: status (s_invalid); } }
    void verify_id (element& e)
    {   if (! tidy_string < t_idref > :: good ()) return;
        if (! ids_t::is_good_id (e, tidy_string < t_idref > :: get_string (), ec_type, nit_unknown, true))
            tidy_string < t_idref > :: status (s_invalid); } };

template < bool HIDES > struct many_ids : string_vector < t_idrefs, sz_space >
{   using string_vector < t_idrefs, sz_space > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_idrefs, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_idrefs, sz_space > :: empty ())
        {   nits.pick (nit_bad_id, es_error, ec_type, "the identifier list is empty");
            string_vector < t_idrefs, sz_space > :: status (s_invalid); } }
    void verify_id (element& e)
    {   if (! string_vector < t_idrefs, sz_space > :: good ()) return;
        bool allgood = true;
        for (auto m : string_vector < t_idrefs, sz_space > :: get ())
            if (! ids_t::is_good_id (e, m, ec_type, nit_bad_id, HIDES)) allgood = false;
        if (! allgood)
        {   tidy_string < t_idrefs > :: status (s_invalid);
            value_.clear (); } } };

template < > struct type_master < t_idrefs > : many_ids < true >
{ using many_ids < true > :: many_ids; };

template < > struct type_master < t_itemref > : many_ids < false >
{ using many_ids < false > :: many_ids; };

template < > struct type_master < t_result > : tidy_string < t_result >
{   typedef true_type has_int_type;
    using tidy_string < t_result > :: tidy_string;
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    { return invalid_id_result (nits, v, tidy_string < t_result > :: value_, e); } };
