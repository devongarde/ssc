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
bool invalid_id_result (nitpick& nits, const html_version& v, const ::std::string& s, element* e);

template < > struct type_master < t_id > : tidy_string < t_id >
{   bool tested_ = false, predefined_ = false;
    type_master () = default;
    void swap (type_master < t_id >& t) NOEXCEPT
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
                    tidy_string < t_id > :: status (s_invalid); } }
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
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_idref > :: set_value (nits, v, s);
        if (s.empty ())
        {   nits.pick (nit_bad_id, es_error, ec_type, "an id cannot be empty");
            tidy_string < t_idref > :: status (s_invalid); }
        else if (::std::find_if (s.cbegin (), s.cend (), ::std::iswspace) != s.cend ())
        {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " contains a space");
            tidy_string < t_idref > :: status (s_invalid); } }
    bool verify_id (nitpick& nits, const html_version& , ids_t& ids, const attribute_bitset& state, const vit_t& )
    {   if (! tidy_string < t_idref > :: good ()) return false;
        const ::std::string s (tidy_string < t_idref > :: get_string ());
        if (! ids.has_id (s))
            nits.pick (nit_unknown, es_error, ec_type, quote (s), " is not an existing identifier");
        else if (! ids.compatible_state (s, state.test (a_hidden)))
            nits.pick (nit_id_hidden, es_error, ec_type, quote (s), " is hidden");
        else return false;
        tidy_string < t_idref > :: status (s_invalid);
        return true; } };

template < > struct type_master < t_idrefs > : string_vector < t_idrefs, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_idrefs, sz_space > :: set_value (nits, v, s);
        if (string_vector < t_idrefs, sz_space > :: empty ())
        {   nits.pick (nit_bad_id, es_error, ec_type, "the ID list is empty");
            string_vector < t_idrefs, sz_space > :: status (s_invalid); } }
    bool verify_id (nitpick& nits, const html_version& , ids_t& ids, const attribute_bitset& state, const vit_t& )
    {   if (! string_vector < t_idrefs, sz_space > :: good ()) return false;
        bool allgood = true;
        for (auto m : string_vector < t_idrefs, sz_space > :: get ())
        {   if (! ids.has_id (m))
            {   allgood = false;
                nits.pick (nit_bad_id, es_error, ec_type, quote (m), " is not a recognised ID"); }
            else if (! ids.compatible_state (m, state.test (a_hidden)))
            {   allgood = false;
                nits.pick (nit_id_hidden, es_error, ec_type, quote (m), " is hidden"); } }
        if (! allgood)
        {   tidy_string < t_idrefs > :: status (s_invalid);
            value_.clear (); }
        return true; } };

template < > struct type_master < t_navigation > : tidy_string < t_navigation >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_navigation > :: set_value (nits, v, s);
        if (s.empty ())
        {   nits.pick (nit_bad_id, es_error, ec_type, "an id cannot be empty");
            tidy_string < t_navigation > :: status (s_invalid); }
        else if (::std::find_if (s.cbegin (), s.cend (), ::std::iswspace) != s.cend ())
        {   nits.pick (nit_bad_id, es_error, ec_type, quote (s), " contains a space");
            tidy_string < t_navigation > :: status (s_invalid); } }
    bool verify_id (nitpick& nits, const html_version& , ids_t& ids, const attribute_bitset& state, const vit_t& )
    {   if (! tidy_string < t_navigation > :: good ()) return false;
        const ::std::string s (tidy_string < t_navigation > :: get_string ());
        if (compare_no_case (s, "auto") || compare_no_case (s, "self")) return false;
        if (! ids.has_id (s))
            nits.pick (nit_unknown, es_error, ec_type, quote (s), " is not an existing identifier");
        else if (! ids.compatible_state (s, state.test (a_hidden)))
            nits.pick (nit_id_hidden, es_error, ec_type, quote (s), " is hidden");
        else return false;
        tidy_string < t_navigation > :: status (s_invalid);
        return true; } };

template < > struct type_master < t_result > : tidy_string < t_result >
{   typedef true_type has_int_type;
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    { return invalid_id_result (nits, v, string_value < t_result > :: value_, e); } };
