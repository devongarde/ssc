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

// important: this template does not retain vector guarantees, such as data continuity

#pragma once

/*
ATTRIBUTE=element attribute value
ELEMENT=element value
MICROFORMAT=class property value
ONTOLOGY=ontology type property value
NEVER=value
*/

class html_version;
class nitpick;

const unsigned int naughty_type_shift = 14;
const unsigned int naughty_elem_shift = 8;

class wblist
{   szreg_t naughty_, nice_;
    misd_t  dim_;
    bool communal_ = false, elemental_ = false, attributal_ = false, microformulaic_ = false, ontological_ = false, typical_ = false;
    ::std::size_t get_n (const e_element e) const
    {   return (static_cast < ::std::size_t > (fus_element) << naughty_type_shift) + (static_cast < ::std::size_t > (e) << naughty_elem_shift); }
    ::std::size_t get_n (const e_element e, const e_attribute a) const
    {   return (static_cast < ::std::size_t > (fus_attribute) << naughty_type_shift) + (static_cast < ::std::size_t > (e) << naughty_elem_shift) + a; }
    ::std::size_t get_n (const e_ontology_property p) const
    {   return (static_cast < ::std::size_t > (fus_ontology) << naughty_type_shift) + static_cast < ::std::size_t > (p); }
    ::std::size_t get_n (const e_property c) const
    {   return (static_cast < ::std::size_t > (fus_microformat) << naughty_type_shift) + static_cast < ::std::size_t > (c); }
    ::std::size_t get_n (const e_type t) const
    {   return (static_cast < ::std::size_t > (fus_type) << naughty_type_shift) + static_cast < ::std::size_t > (t); }
    ::std::string inner_sub (::std::size_t n) const;
    void init_nn (const html_version& v, nitpick& nits, szreg_t& reg, const ::std::string& s);
    void init_dim (const html_version& v, nitpick& nits, misd_t& ms, const ::std::string& s);
    bool test_element (const html_version& v, nitpick& nits, const e_element e, const ::std::string& s, const ::std::string& ss, const bool no_close) const;
    ::std::size_t init_params (const html_version& v, nitpick& nits, const ::std::string& ss, ::std::string& value);
    bool inner_test (const ::std::size_t n, const ::std::string& s) const;
public:
    void init (const html_version& v, nitpick& nits, const vstr_t& naughty, const vstr_t& nice, const vstr_t& note);
    bool empty () const
    {   return naughty_.empty () && nice_.empty (); }
    bool test (const ::std::string& s) const
    {   if (! communal_) return false;
        return inner_test (0, s); }
    bool test (const e_element e, const ::std::string& s) const
    {   if (! elemental_) return false;
        return inner_test (get_n (e), s); }
    bool test (const e_element e, const e_attribute a, const ::std::string& s) const
    {   if (! attributal_) return false;
        return inner_test (get_n (e, a), s); }
    bool test (const e_ontology_property p, const ::std::string& s) const
    {   if (! ontological_) return false;
        return inner_test (get_n (p), s); }
    bool test (const e_property c, const ::std::string& s) const 
    {   if (! microformulaic_) return false;
        return inner_test (get_n (c), s); }
    bool test (const e_type t, const ::std::string& s) const 
    {   if (! typical_) return false;
        return inner_test (get_n (t), s); }
    ::std::string sub () const
    {   if (! communal_) return ::std::string ();
        return inner_sub (0); }
    ::std::string sub (const e_element e) const
    {   if (! elemental_) return ::std::string ();
        return inner_sub (get_n (e)); }
    ::std::string sub (const e_element e, const e_attribute a) const 
    {   if (! attributal_) return ::std::string ();
        return inner_sub (get_n (e, a)); }
    ::std::string sub (const e_ontology_property p) const
    {   if (! ontological_) return ::std::string ();
        return inner_sub (get_n (p)); }
    ::std::string sub (const e_property c) const
    {   if (! microformulaic_) return ::std::string ();
        return inner_sub (get_n (c)); }
    ::std::string sub (const e_type t) const
    {   if (! typical_) return ::std::string ();
        return inner_sub (get_n (t)); } };


