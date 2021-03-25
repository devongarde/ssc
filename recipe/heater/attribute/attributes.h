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
#include "attribute/attribute.h"
#include "webpage/id.h"

class page;
class element;

class attributes
{   aar_t aar_;
    ::std::string unrecognised_;
    const e_element tag_ = elem_undefined;
public:
    attributes () = delete;
    explicit attributes (const e_element e, const aar_t& ptr) : aar_ (ptr), tag_ (e) { }
    explicit attributes (element_node& en) : tag_ (en.tag ()) { }
    void reset ()
    {   aar_.fill (attribute_v_ptr ());
        unrecognised_.clear (); }
    void swap (attributes& w) NOEXCEPT
    {   aar_.swap (w.aar_);
        unrecognised_.swap (w.unrecognised_); }
    void reconstruct (element_node& en)
    {   parse (en.nits (), en.version (), en.attributes ()); }
    e_element tag () const { return tag_; }
    bool has (const e_attribute a) const
    {   return aar_.at (a).get () != nullptr; }

    bool set_value (nitpick& nits, const html_version& v, const e_attribute a, const ::std::string& s);
    bool parse (nitpick& nits, const html_version& v, const attributes_node& an);

    ::std::string get_string (const e_attribute a) const
    {   if (! has (a)) return ::std::string ();
        return aar_.at (a) -> get_string (); }
    vurl_t get_urls (const e_attribute a) const
    {   if (! has (a)) return vurl_t ();
        return aar_.at (a) -> get_urls (); }
    bool invalid (const e_attribute a) const
    {   if (! has (a)) return true;
        return aar_.at (a) -> invalid (); }
    bool valid (const e_attribute a) const
    {   return ! invalid (a); }
    bool known (const e_attribute a) const
    {   if (! has (a)) return false;
        return ! aar_.at (a) -> unknown (); }
    bool empty (const e_attribute a) const
    {   if (! has (a)) return true;
        return aar_.at (a) -> empty (); }
    bool good (const e_attribute a) const
    {   if (! has (a)) return false;
        return aar_.at (a) -> good (); }
    ::std::size_t type (const e_attribute a) const
    {   if (! has (a) || ! good (a)) return 0;
        return aar_.at (a) -> type (); }
    int get_int (const e_attribute a) const
    {   if (! has (a)) return 0;
        return aar_.at (a) -> get_int (); }
    ::std::size_t size (const e_attribute a) const
    {   if (! has (a)) return 0;
        return aar_.at (a) -> size (); }
    template < class ATTRIBUTE > typename ATTRIBUTE::value_type get_x () const
    {   if (! has (ATTRIBUTE::whoami ())) return ATTRIBUTE::default_value ();
        ATTRIBUTE* ap = static_cast < ATTRIBUTE* > (aar_.at (ATTRIBUTE::whoami ()).get ());
        assert (ap != nullptr);
        return ap -> get (); }
    const attribute_v_ptr get (const e_attribute a) const { return aar_.at (a); }
    attribute_v_ptr get (const e_attribute a) { return aar_.at (a); }
    template < class ATTRIBUTE > bool has_value (const typename ATTRIBUTE :: base_type& v) const
    {   if (! has (ATTRIBUTE::whoami ())) return false;
        return get_x < ATTRIBUTE > () == v; }

    bool empty () const;
    bool invalid () const;
    bool valid () const;
    void verify (nitpick& nits, const html_version& v, ids_t& ids, const attribute_bitset& flags, const vit_t& itemtypes);
    bool invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe);
    bool invalid_access (nitpick& nits, const html_version& v, sstr_t* ids);
    bool has_url () const;
    bool verify_url (nitpick& nits, const html_version& v, const directory& d, const ::boost::filesystem::path& pagename, const int line, const attribute_bitset& flags, const vit_t& itemtypes);
    void verify_attributes (nitpick& nits, const html_version& v, attribute_bitset& state);
    void mark (page& p, const e_attribute a);
    void mark (page& p);
    void shadow (::std::stringstream& ss, const html_version& v, element* e);
    ::std::string report () const; };
