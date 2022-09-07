/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26440) // For VS2019, at least, the linter and compiler disagree over signatures of noexcept on virtual
#endif // _MSC_VER

struct attribute_base
{   bool deprecated_ = false;
    bool excluded_ = false;
    attribute_base () = default;
    attribute_base (const attribute_base& ) = default;
    attribute_base (attribute_base&& ) = default;
    attribute_base& operator = (const attribute_base& ) = default;
    attribute_base& operator = (attribute_base&& ) = default;
    virtual ~attribute_base () = default;
    void swap (attribute_base& b) noexcept
    {   ::std::swap (deprecated_, b.deprecated_);
        ::std::swap (excluded_, b.excluded_); }
    virtual void reset ()
    {   deprecated_ = excluded_ = false; }
    virtual void parse (nitpick& , const html_version& , const attribute_node& ) { }
    virtual bool verify_version (nitpick& , const html_version& , const e_element ) { return false; }
    virtual void set_value (nitpick& , const html_version& , const ::std::string& ) { }
    virtual void verify_attribute (nitpick& , const html_version& , const elem& , element* , const ::std::string& ) { }
    virtual bool verify_url (nitpick& , const html_version& , element& ) { return true; }
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
    virtual void verify_id (element& ) { }
    virtual e_status status () const { return s_unset; }
    virtual void status (const e_status ) { }
    virtual bool unknown () const { return true; }
    virtual ::std::size_t type () const { return 0; }
    virtual vurl_t get_urls () const { return vurl_t (); }
    virtual int get_int () const { return 0; }
    virtual ::std::size_t size () const { return 1; }
    element* box () noexcept { return nullptr; }
    element* box () const noexcept { return nullptr; }
    void box (const element* ) noexcept { }
    virtual void shadow (::std::stringstream& , const html_version& , element* ) { }
    virtual ::std::string report () const { return ::std::string (); } };


#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26435) // For VS2019, the linter wants override on a member function which already has override (I've since taken them out to avoid confusion)
#endif // _MSC_VER

template < e_type TYPE, e_attribute IDENTITY > struct typed_attribute : public attribute_base, public typed_value < e_attribute, TYPE, IDENTITY >
{   typed_attribute () = default;
    explicit typed_attribute (element* box) noexcept : typed_value < e_attribute, TYPE, IDENTITY > (box) { }
    static ::std::string name () { return attr :: name (IDENTITY); }
    CONSTEXPR static e_attribute whoami () { return IDENTITY; }
    CONSTEXPR static e_type whatami () { return TYPE; }
    void swap (typed_attribute& t) noexcept
    {   attribute_base :: swap (t);
        typed_value < e_attribute, TYPE, IDENTITY > :: swap (t); }
    void reset () override
    {   attribute_base :: reset ();
        typed_value < e_attribute, TYPE, IDENTITY > :: reset (); }
    void parse (nitpick& nits, const html_version& v, const attribute_node& node) override
    {   set_value (nits, v, node.get_string ()); }
    bool verify_version (nitpick& nits, const html_version& v, const e_element tag) override
    {   if (typed_value < e_attribute, TYPE, IDENTITY > :: unknown ()) return true;
        if (! v.check_math_svg (nits, attr :: first_version (IDENTITY), name ())) excluded_ = true;
        if (is_invalid_attribute_version (v, tag, IDENTITY))
        {   nits.pick (nit_invalid_attribute_version, es_error, ec_attribute, quote (name ()), " is invalid in ", v.report ());
            return false; }
        if (! excluded_)
        {   excluded_ = attr :: first_version (IDENTITY).invalid_addendum (v);
            if (excluded_) nits.pick (nit_excluded_attribute, es_warning, ec_attribute, "the attribute ", quote (name ()), " is invalid in pure ", v.report ()); }
        deprecated_ = is_deprecated_attribute_version (v, tag, IDENTITY);
        if (deprecated_) nits.pick (nit_deprecated_attribute, es_warning, ec_attribute, name (), " is deprecated in ", v.report ());
        else if (not_production_attribute (v, tag, IDENTITY))
            nits.pick (nit_prototype, ed_jan21, "1.11.1 Presentational markup", es_comment, ec_attribute, name (), " is best not used in production in ", v.report ());
        return true; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s) override
    {   typed_value < e_attribute, TYPE, IDENTITY > :: set_value (nits, v, s);
        if (! typed_value < e_attribute, TYPE, IDENTITY > :: is_existential ()) return;
        ::std::string ss (trim_the_lot_off (s));
        if (ss.empty ())
        {   if (v.xhtml ())
            {   nits.pick (nit_xhtml_existential_makework, es_error, ec_type, "in ", v.report (), ", the attribute ", quote (name ()), " must be assigned ", quote (name ()));
                typed_value < e_attribute, TYPE, IDENTITY > :: status (s_invalid); } }
        else if (typed_value < e_attribute, TYPE, IDENTITY > :: good ())
            if (v.is_b4_2 ())
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
    virtual void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* pe, const ::std::string& s) override
    {   typed_value < e_attribute, TYPE, IDENTITY > :: verify_attribute (nits, v, e, pe, s); }
    virtual bool verify_url (nitpick& nits, const html_version& v, element& e) override
    {   return typed_value < e_attribute, TYPE, IDENTITY > :: verify_url (nits, v, e); }
    virtual ::std::string get_string () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: get_string (); }
    virtual ::std::string original () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: original (); }
    virtual e_attribute id () const override { return IDENTITY; }
    virtual ::std::string get_id () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: get_id (); }
    virtual void set_id (const ::std::string& s) override { typed_value < e_attribute, TYPE, IDENTITY > :: set_id (s); }
    virtual bool invalid_id (nitpick& nits, const html_version& v, ids_t& i, element* e) override
    {   return typed_value < e_attribute, TYPE, IDENTITY > :: invalid_id (nits, v, i, e); }
    virtual bool invalid_access (nitpick& nits, const html_version& v, sstr_t* ss) override
    {   return typed_value < e_attribute, TYPE, IDENTITY > :: invalid_access (nits, v, ss); }
    virtual bool has_id () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: has_id (); }
    virtual bool empty () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: empty (); }
    virtual bool good () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: good (); }
    virtual bool bad () const override { return ! good (); }
    virtual bool invalid () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: invalid (); }
    virtual bool is_url () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: is_url (); }
    virtual void verify_id (element& e) override
    {   typed_value < e_attribute, TYPE, IDENTITY > :: verify_id (e); }
    virtual e_status status () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: status (); }
    virtual void status (const e_status s) override { typed_value < e_attribute, TYPE, IDENTITY > :: status (s); }
    virtual bool unknown () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: unknown (); }
    virtual ::std::size_t type () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: type (); }
    virtual vurl_t get_urls () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: get_urls (); }
    static typename typed_value < e_attribute, TYPE, IDENTITY > :: value_type default_value () { return typed_value < e_attribute, TYPE, IDENTITY > :: default_value (); }
    typename typed_value < e_attribute, TYPE, IDENTITY > :: value_type get () const { return typed_value < e_attribute, TYPE, IDENTITY > :: get (); }
    bool has_value (const typename typed_value < e_attribute, TYPE, IDENTITY > :: value_type t) const { return typed_value < e_attribute, TYPE, IDENTITY > :: has_value (t); }
    virtual int get_int () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: get_int (); }
    virtual ::std::size_t size () const override { return typed_value < e_attribute, TYPE, IDENTITY > :: size (); }
    virtual element* box () noexcept { return typed_value < e_attribute, TYPE, IDENTITY > :: box (); }
    virtual element* box () const noexcept { return typed_value < e_attribute, TYPE, IDENTITY > :: box (); }
    virtual void box (element* b) noexcept { typed_value < e_attribute, TYPE, IDENTITY > :: box (b); }
    virtual void shadow (::std::stringstream& ss, const html_version& v, element* e) override
    {   if (typed_value < e_attribute, TYPE, IDENTITY > :: unknown () || typed_value < e_attribute, TYPE, IDENTITY > :: invalid ()) return;
        ss << " " << name ();
        typed_value < e_attribute, TYPE, IDENTITY > :: shadow (ss, v, e); }
    static e_animation_type animation_type () noexcept { return typed_value < e_attribute, TYPE, IDENTITY > :: animation_type (); }
    virtual ::std::string report () const override
    {   return typed_value < e_attribute, TYPE, IDENTITY > :: report (name ()); } };

typedef ::std::shared_ptr < attribute_base > attribute_v_ptr;
attribute_v_ptr make_attribute_v_ptr (nitpick& nits, const html_version& v, element* box, const attribute_node& node);
e_animation_type get_animation_type (const e_attribute ea);

CONSTEXPR size_t aar_size = last_attribute + 1;
typedef ::std::array < attribute_v_ptr, aar_size > aar_t;

#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
