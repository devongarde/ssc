/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "enum/type_mime.h"
#include "compound/type_compound.h"

bool good_for_actual_mime (const element* const e);
bool good_for_faux_mime (const element* const e);

template < > struct type_master < t_mimemodule > : type_or_string < t_mimemodule, t_mime, sz_module >
{ using type_or_string < t_mimemodule, t_mime, sz_module > :: type_or_string; };

template < > struct type_master < t_mimeq > : type_one_or_both < t_mimeq, t_mimestar, sz_semicolon, t_q >
{ using type_one_or_both < t_mimeq, t_mimestar, sz_semicolon, t_q > :: type_one_or_both; };

template < > struct type_master < t_mimeqs > : type_at_least_one < t_mimeqs, sz_comma, t_mimeq >
{ using type_at_least_one < t_mimeqs, sz_comma, t_mimeq > :: type_at_least_one; };

template < > struct type_master < t_atom_mime > : tidy_string < t_atom_mime >
{   using tidy_string < t_atom_mime > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_atom_mime > :: set_value (nits, v, s);
        ::std::string arg (tidy_string < t_atom_mime > :: get_string ());
        if (s.empty ()) nits.pick (nit_empty, es_error, ec_type, "TYPE requires a value");
        else if (good ())
        {   nitpick nuts;
            if (good_for_faux_mime (tidy_string < t_atom_mime > :: box ()))
                if (test_value < t_atom_type > (nuts, v, arg))
                {   nits.merge (nuts); return; }
            if (good_for_actual_mime (tidy_string < t_atom_mime > :: box ()))
                if (test_value < t_mime > (nits, v, arg)) return;
            nits.merge (nuts); }
        tidy_string < t_atom_mime > :: status (s_invalid); } };
