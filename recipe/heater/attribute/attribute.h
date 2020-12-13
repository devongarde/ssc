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
#include "utility/common.h"
#include "type/type.h"
#include "attribute/avm.h"
#include "parser/parse_attribute.h"

struct attribute_base
{   bool deprecated_ = false;
    bool excluded_ = false;
    void swap (attribute_base& b) NOEXCEPT
    {   ::std::swap (deprecated_, b.deprecated_);
        ::std::swap (excluded_, b.excluded_); }
    virtual void reset ()
    { deprecated_ = excluded_ = false; }
    virtual void parse (nitpick& , const html_version& , const attribute_node& ) { }
    virtual bool verify_version (nitpick& , const html_version& , const e_element ) { return false; }
    virtual void set_value (nitpick& , const html_version& , const ::std::string& ) { }
    virtual void validate (nitpick& , const html_version& , const elem& , const ::std::string& ) { }
    virtual bool verify_url (nitpick& , const html_version& , const directory& , const ::boost::filesystem::path& , const int , const attribute_bitset& , const vit_t& ) { return true; }
    virtual ::std::string get_string () const { return ::std::string (); }
    virtual ::std::string original () const { return get_string (); }
    virtual e_attribute id () const { return a_unknown; }
    virtual ::std::string get_id () const { return ::std::string (); }
    virtual void set_id (const ::std::string& ) {  }
    virtual bool invalid_id (nitpick& , const html_version& , ids_t& , element* ) { return false; }
    virtual bool invalid_access (nitpick& , const html_version& , sstr_t* ) { return false; }
    virtual bool has_id () const { return false; }
    virtual bool empty () const { return true; }
    virtual bool good () const { return false; }
    virtual bool bad () const { return ! good (); }
    virtual bool invalid () const { return true; }
    virtual bool is_url () const { return false; }
    virtual void verify_id (nitpick& , const html_version& , ids_t& , const attribute_bitset& , const vit_t& ) { }
    virtual e_status status () const { return s_unset; }
    virtual void status (const e_status ) { }
    virtual bool unknown () const { return true; }
    virtual ::std::size_t type () const { return 0; }
    virtual vurl_t get_urls () const { return vurl_t (); }
    virtual int get_int () const { return 0; }
    virtual void shadow (::std::stringstream& , const html_version& , element* ) { }
    virtual ::std::string report () const { return ::std::string (); } };

template < e_type TYPE, e_attribute IDENTITY > struct typed_attribute : public attribute_base, public typed_value < e_attribute, TYPE, IDENTITY >
{   static ::std::string name () { return attr :: name (IDENTITY); }
    CONSTEXPR static e_attribute whoami () { return IDENTITY; }
    typed_attribute (nitpick& nits, const html_version& v, const attribute_node& node)
    {   parse (nits, v, node); }
    void swap (typed_attribute& t) NOEXCEPT
    {   attribute_base :: swap (t);
        typed_value < e_attribute, TYPE, IDENTITY > :: swap (t); }
    void reset ()
    {   attribute_base :: reset ();
        typed_value < e_attribute, TYPE, IDENTITY > :: reset (); }
    void parse (nitpick& nits, const html_version& v, const attribute_node& node)
    {   set_value (nits, v, node.get_string ()); }
    bool verify_version (nitpick& nits, const html_version& v, const e_element tag)
    {   if (typed_value < e_attribute, TYPE, IDENTITY > :: unknown ()) return true;
        if (is_invalid_attribute_version (v, tag, IDENTITY))
        {   nits.pick (nit_invalid_attribute_version, es_error, ec_attribute, quote (name ()), " is invalid in ", v.report ());
            return false; }
        if (! v.check_math_svg (nits, attr :: first_version (IDENTITY), name ())) excluded_ = true;
        else
        {   excluded_ = attr :: first_version (IDENTITY).invalid_addendum (v);
            if (excluded_) nits.pick (nit_excluded_attribute, es_warning, ec_attribute, "the attribute ", quote (name ()), " is part of extension to ", v.report (), " that is not being applied"); }
        deprecated_ = is_deprecated_attribute_version (v, tag, IDENTITY);
        if (deprecated_) nits.pick (nit_deprecated_attribute, es_warning, ec_attribute, name (), " is deprecated in ", v.report ());
        return true; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   typed_value < e_attribute, TYPE, IDENTITY > :: set_value (nits, v, s);
        if (! typed_value < e_attribute, TYPE, IDENTITY > :: is_existential ()) return;
        ::std::string ss (trim_the_lot_off (s));
        if (ss.empty ())
        {   if (v.xhtml ())
            {   nits.pick (nit_xhtml_existential_makework, es_error, ec_type, "in ", v.report (), ", the attribute ", quote (name ()), " must be assigned ", quote (name ()));
                typed_value < e_attribute, TYPE, IDENTITY > :: status (s_invalid); } }
        else if (typed_value < e_attribute, TYPE, IDENTITY > :: good ())
            if (v.mjr () < 2)
            {   nits.pick (nit_existential_value, es_warning, ec_type, "in ", v.report (), ", ", name (), " cannot be given a value");
                typed_value < e_attribute, TYPE, IDENTITY > :: status (s_invalid); }
            else
            if (v.xhtml ())
            {   if (ss != name ())
                {   nits.pick (nit_xhtml_existential_makework, es_error, ec_type, "in ", v.report (), ", the value of ", name (), " must be ", quote (name ()));
                    typed_value < e_attribute, TYPE, IDENTITY > :: status (s_invalid); } }
            else if (! compare_no_case (ss, name ()))
            {   nits.pick (nit_existential_value, es_warning, ec_type, "if ", name (), " has a value, it must be ", quote (name ()));
                typed_value < e_attribute, TYPE, IDENTITY > :: status (s_invalid); } }

    virtual void validate (nitpick& nits, const html_version& v, const elem& e, const ::std::string& s)
    {   typed_value < e_attribute, TYPE, IDENTITY > :: validate (nits, v, e, s); }
    virtual bool verify_url (nitpick& nits, const html_version& v, const directory& d, const ::boost::filesystem::path& p, const int n, const attribute_bitset& bs, const vit_t& vit)
    {   return typed_value < e_attribute, TYPE, IDENTITY > :: verify_url (nits, v, d, p, n, bs, vit); }
    virtual ::std::string get_string () const { return typed_value < e_attribute, TYPE, IDENTITY > :: get_string (); }
    virtual ::std::string original () const { return typed_value < e_attribute, TYPE, IDENTITY > :: original (); }
    virtual e_attribute id () const { return IDENTITY; }
    virtual ::std::string get_id () const { return typed_value < e_attribute, TYPE, IDENTITY > :: get_id (); }
    virtual void set_id (const ::std::string& s) { typed_value < e_attribute, TYPE, IDENTITY > :: set_id (s); }
    virtual bool invalid_id (nitpick& nits, const html_version& v, ids_t& i, element* e)
    {   return typed_value < e_attribute, TYPE, IDENTITY > :: invalid_id (nits, v, i, e); }
    virtual bool invalid_access (nitpick& nits, const html_version& v, sstr_t* ss) { return typed_value < e_attribute, TYPE, IDENTITY > :: invalid_access (nits, v, ss); }
    virtual bool has_id () const { return typed_value < e_attribute, TYPE, IDENTITY > :: has_id (); }
    virtual bool empty () const { return typed_value < e_attribute, TYPE, IDENTITY > :: empty (); }
    virtual bool good () const { return typed_value < e_attribute, TYPE, IDENTITY > :: good (); }
    virtual bool bad () const { return ! good (); }
    virtual bool invalid () const { return typed_value < e_attribute, TYPE, IDENTITY > :: invalid (); }
    virtual bool is_url () const { return typed_value < e_attribute, TYPE, IDENTITY > :: is_url (); }
    virtual void verify_id (nitpick& nits, const html_version& v, ids_t& i, const attribute_bitset& bs, const vit_t& vit)
    {   typed_value < e_attribute, TYPE, IDENTITY > :: verify_id (nits, v, i, bs, vit); }
    virtual e_status status () const { return typed_value < e_attribute, TYPE, IDENTITY > :: status (); }
    virtual void status (const e_status s) { typed_value < e_attribute, TYPE, IDENTITY > :: status (s); }
    virtual bool unknown () const { return typed_value < e_attribute, TYPE, IDENTITY > :: unknown (); }
    virtual ::std::size_t type () const { return typed_value < e_attribute, TYPE, IDENTITY > :: type (); }
    virtual vurl_t get_urls () const { return typed_value < e_attribute, TYPE, IDENTITY > :: get_urls (); }
    static typename typed_value < e_attribute, TYPE, IDENTITY > :: value_type default_value () { return typed_value < e_attribute, TYPE, IDENTITY > :: default_value (); }
    typename typed_value < e_attribute, TYPE, IDENTITY > :: value_type get () const { return typed_value < e_attribute, TYPE, IDENTITY > :: get (); }
    bool has_value (const typename typed_value < e_attribute, TYPE, IDENTITY > :: value_type t) const { return typed_value < e_attribute, TYPE, IDENTITY > :: has_value (t); }
    virtual int get_int () const { return typed_value < e_attribute, TYPE, IDENTITY > :: get_int (); }
    virtual void shadow (::std::stringstream& ss, const html_version& v, element* e)
    {   if (typed_value < e_attribute, TYPE, IDENTITY > :: unknown () || typed_value < e_attribute, TYPE, IDENTITY > :: invalid ()) return;
        ss << " " << name ();
        typed_value < e_attribute, TYPE, IDENTITY > :: shadow (ss, v, e); }

    virtual ::std::string report () const
    {   return typed_value < e_attribute, TYPE, IDENTITY > :: report (name ()); } };

typedef ::std::shared_ptr < attribute_base > attribute_v_ptr;
attribute_v_ptr make_attribute_v_ptr (nitpick& nits, const html_version& v, const attribute_node& node);

const size_t aar_size = last_attribute + 1;
typedef ::std::array < attribute_v_ptr, aar_size > aar_t;
