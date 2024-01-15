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
#include "enum/type_enum.h"

typedef ::std::vector < e_autocomplete > vaco_t;

bool set_autocomplete_value (vaco_t& vaco, nitpick& nits, const html_version& v, const ::std::string& s);
bool invalid_autocomplete (nitpick& nits, const html_version& v, const element* e, const vaco_t& vaco);

template < > struct type_master < t_autocompletes > : tidy_string < t_autocompletes >
{   vaco_t vaco_;
    using tidy_string < t_autocompletes > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_autocompletes > :: set_value (nits, v, s);
        const ::std::string& ss (tidy_string < t_autocompletes > :: get_string ());
        if (ss.empty ()) nits.pick (nit_empty, ed_52, "4.10.18.7.1. ... the autocomplete attribute", es_error, ec_type, "AUTOCOMPLETE cannot be empty");
        else if (good ())
            if (! set_autocomplete_value (vaco_, nits, v, ss))
                tidy_string < t_autocompletes > :: status (s_invalid); }
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& , element* e)
    {   VERIFY_NOT_NULL (e, __FILE__, __LINE__);
        if (good ())
            if (! invalid_autocomplete (nits, v, e, vaco_))
                tidy_string < t_autocompletes > :: status (s_invalid);
        return false; }
    void reset () noexcept
    {   value_.clear (); } };
