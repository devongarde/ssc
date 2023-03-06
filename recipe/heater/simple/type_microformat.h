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

template < > struct type_master < t_email > : tidy_string < t_email >
{   using tidy_string < t_email > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_email > :: set_value (nits, v, s);
        if (string_value < t_email > :: empty ())
            nits.pick (nit_bad_email, es_error, ec_type, "an email address is expected");
        else if (string_value < t_email > :: good ())
        {   url u (nits, v, tidy_string < t_email > :: get_string (), pr_mailto);
            if (! u.invalid ())
                if (! u.has_protocol () || (u.get_protocol () == pr_mailto)) return;
                else nits.pick (nit_bad_email, es_error, ec_type, quote (tidy_string < t_email > :: get_string ()), "is not an email address"); }
    string_value < t_email > :: status (s_invalid); } };

template < > struct type_master < t_rating > : numeric_value < t_rating, int >
{   typedef true_type has_int_type;
    using numeric_value < t_rating, int > :: numeric_value;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   numeric_value < t_rating, int > :: set_value (nits, v, s);
        if (numeric_value < t_rating, int > :: good ())
            if ((numeric_value < t_rating, int > :: value_ < 1) || (numeric_value < t_rating, int > :: value_ > 5))
            {   nits.pick (nit_bad_rating, es_error, ec_type, quote (s), " is not a digit between 1 and 5");
                numeric_value < t_rating, int > :: status (s_invalid); } } };

template < > struct type_master < t_sex > : tidy_string < t_sex >
{   char sex_ = 0;
    ::std::string gender_;
    using tidy_string < t_sex > :: tidy_string;
    void swap (type_master < t_sex >& t) noexcept
    {   ::std::swap (sex_, t.sex_);
        gender_.swap (t.gender_);
        tidy_string < t_sex >::swap (t); }
    bool parse (const html_version& , const ::std::string& s)
    {   const ::std::size_t pos = s.find (';');
        switch (pos)
        {   case 0 :
                sex_ = 0;
                gender_ = s.substr (1);
                return true;
            case 1 :
                sex_ = GSL_AT (s, 0);
                gender_ = s.substr (2);
                break;
            case ::std::string::npos :
                if (s.length () != 1) return false;
                sex_ = GSL_AT (s, 0);
                break;
            default:
                return false; }
        return (s.substr (0, 1).find_first_of ("FfMmNnOoUu") != s.npos); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_sex > :: set_value (nits, v, s);
        if (! parse (v, tidy_string < t_sex > :: get_string ()))
        {   nits.pick (nit_sex, es_error, ec_type, quote (s), " should be one of 'F', 'M', 'N', 'O', 'U', or otherwise conform to RFC 6350");
            tidy_string < t_sex > :: status (s_invalid); } }
    char sex () const noexcept { return sex_; }
    ::std::string gender () const { return gender_; } };

template < > struct type_master < t_tel > : public tidy_string < t_tel >
{   using tidy_string < t_tel > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_value < t_tel > :: set_value (nits, v, s);
        ::std::string val = tidy_string < t_tel > :: get_string ();
        if (tidy_string < t_tel > :: good ())
        {   if (val.substr (0, 4) != "tel:")
                nits.pick (nit_no_tel, ed_rfc_3966, "3. URI Syntax", es_info, ec_type, quote (s), " should start with 'tel:'");
            else val = val.substr (4);
            const ::std::string::size_type pos = val.find (';');
            if (pos != ::std::string::npos) val = val.substr (0, pos);
            if (val.find_first_not_of (TEL) != ::std::string::npos)
            {   nits.pick (nit_phone, ed_rfc_3966, "3. URI Syntax", es_error, ec_type, quote (s), " does not appear to be a phone number");
                tidy_string < t_tel > :: status (s_invalid); } } } };
