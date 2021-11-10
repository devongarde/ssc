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
#include "url/url_protocol.h"

e_status parse_prefixes (nitpick& nits, const html_version& v, const ::std::string ss, const prefixes_t* up, vabb_t& vpre, const bool vrai);
e_status parse_prefixes (nitpick& nits, const html_version& v, const ::std::string ss, const element* box, vabb_t& vpre, const bool vrai);

template < > struct type_master < t_curie > : tidy_string < t_curie >
{   using tidy_string < t_curie > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_url; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_curie > :: set_value (nits, v, s); } };

template < > struct type_master < t_curie_safe > : tidy_string < t_curie_safe >
{   using tidy_string < t_curie_safe > :: tidy_string;
    static e_animation_type animation_type () noexcept { return at_url; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_curie_safe > :: set_value (nits, v, s); } };

template < > struct type_master < t_curies > : string_vector < t_curies, sz_space >
{   using string_vector < t_curies, sz_space > :: string_vector;
    static e_animation_type animation_type () noexcept { return at_url; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   string_vector < t_curies, sz_space > :: set_value (nits, v, s); } };

template < > struct type_master < t_inlist > : tidy_string < t_inlist >
{   using tidy_string < t_inlist > :: tidy_string;
    void set_value (nitpick& nits, const html_version& , const ::std::string& s)
    {   if (s.empty ()) tidy_string < t_inlist > :: status (s_good);
        else
        {   nits.pick (nit_inlist, ed_rdfa, "5. Attributes and Syntax", es_error, ec_rdfa, "never give INLIST a value");
            tidy_string < t_inlist > :: status (s_invalid); } } };

template < > struct type_master < t_prefix > : string_vector < t_prefix, sz_space >
{   using string_vector < t_prefix, sz_space > :: string_vector;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& ss)
    {   ::std::string s (tart (ss));
        string_vector < t_prefix, sz_space > :: set_value (nits, v, s);
        if (! string_vector < t_prefix, sz_space > :: good ()) return;
        vabb_t vpre;
        nitpick nuts;
        string_vector < t_prefix, sz_space > :: status (parse_prefixes (nuts, v, s, box (), vpre, false));
        string_vector < t_prefix, sz_space > :: value_.clear ();
        for (auto p : vpre)
            string_vector < t_prefix, sz_space > :: value_.push_back (p.short_ + ": " + p.long_); } };

template < > struct type_master < t_rdfa_typeof > : tidy_string < t_rdfa_typeof >
{   using tidy_string < t_rdfa_typeof > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_rdfa_typeof > :: set_value (nits, v, s); } };

template < > struct type_master < t_vocab > : tidy_string < t_vocab >
{   using tidy_string < t_vocab > :: tidy_string;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_vocab > :: set_value (nits, v, s); } };
