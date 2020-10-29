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
#include "type/type_master.h"

template < > struct type_master < t_curie > : tidy_string < t_curie >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_curie > :: set_value (nits, v, s); } };

template < > struct type_master < t_curie_safe > : tidy_string < t_curie_safe >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_curie_safe > :: set_value (nits, v, s); } };

template < > struct type_master < t_curies > : string_vector < t_curies, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_curies, sz_space > :: set_value (nits, v, s); } };

template < > struct type_master < t_inlist > : tidy_string < t_inlist >
{   void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   if (s.empty ()) tidy_string < t_inlist > :: status (s_good);
        else
        {   nits.pick (nit_inlist, ed_rdf, "5. Attributes and Syntax", es_error, ec_rdf, "never give INLIST a value");
            tidy_string < t_inlist > :: status (s_invalid); } } };

template < > struct type_master < t_prefix > : string_vector < t_prefix, sz_space >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_prefix, sz_space > :: set_value (nits, v, s); } };

template < > struct type_master < t_vocab > : tidy_string < t_curie >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_curie > :: set_value (nits, v, s); } };
