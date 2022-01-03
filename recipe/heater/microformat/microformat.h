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
#include "type/type.h"
#include "microformat/microformat_properties.h"
#include "element/elem.h"

// categories
constexpr int c_generic = 0;
constexpr int c_html3 = 0x00000001;
constexpr int c_microformat = 0x00000002;
constexpr int c_html4 = 0x00000004;
constexpr int c_xfn = 0x00000008;
constexpr int c_its = 0x00000010;
constexpr int c_grddl = 0x00000020;
constexpr int c_vcs = 0x00000040;
constexpr int c_atom = 0x00000080;  // RFC 4287
constexpr int c_amp_html = 0x00000100;
constexpr int c_safari = 0x00000200;
constexpr int c_indieauth = 0x00000400;
constexpr int c_dcterms = 0x00000800;
constexpr int c_lightbox = 0x00001000;
constexpr int c_openid = 0x00002000;
constexpr int c_hcal = 0x00004000;
constexpr int c_cc = 0x00008000;
constexpr int c_mf1 = 0x00010000;
constexpr int c_rejected = 0x10000000;
constexpr int c_dropped = 0x20000000;
constexpr int c_draft = 0x40000000;

// effects on link, a, area
typedef enum
{   ela_no, ela_ok, ela_external, ela_hyperlink, ela_popup, c_annotation, ela_external_contextual }
e_linkaarea;

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26440 26433) // For VS2019, at least, the linter and compiler disagree over signatures of noexcept on virtual
#endif // _MSC_VER

class microformat_base
{   ::std::string text_;
protected:
    bool declared_ = false;
public:
    microformat_base () : declared_ (false) {}
    microformat_base (const microformat_base&) = default;
    microformat_base (microformat_base&&) = default;
    microformat_base& operator = (const microformat_base&) = default;
    microformat_base& operator = (microformat_base&&) = default;
    virtual ~microformat_base () = default;
    explicit microformat_base (bool b) noexcept : declared_ (b) {}

    virtual bool has () const { return false; }
    virtual void get (void** ) { }
    virtual void get (const void** ) const { }
    virtual bool is_known_name () { return false; }
    virtual bool declared () const { return declared_; }
    virtual void declare (bool b = true) { declared_ = b; }

    virtual bool is_relational () const { return false; }
    virtual void verify_attribute (nitpick& , const html_version& , const elem& , element* ) { }
    virtual void set_mf_value (nitpick& , const html_version& , const e_property , element& ) { }
    virtual ::std::string get_string (const e_property ) { return ::std::string (); }
    virtual bool has_prop (const e_property ) const { return false; }
    virtual void reset () { declared_ = false; }
    void swap (microformat_base& mf) noexcept
    {   ::std::swap (declared_, mf.declared_); }
    virtual bool invalid () const { return true; }
    virtual bool has_url () const { return false; }
    virtual bool verify_url (nitpick& , const html_version& , element& ) { return true; }
    virtual void verify (nitpick& , const html_version& ) { }
    virtual bool empty () const { return true; }
    virtual bool unknown () const { return true; }
    void text (const ::std::string& s) { text_ = s; }
    ::std::string text () const { return text_; }
    virtual ::std::string report () const { return ::std::string (); } };

typedef ::std::shared_ptr < microformat_base > microformat_base_ptr;

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES > class microformat : public microformat_base
{   typedef ::std::tuple < PROPERTIES... > property_t;
    property_t p_;
public:
    microformat () = default;
    microformat (const microformat&) = default;
    microformat (microformat&&) = default;
    microformat& operator = (const microformat&) = default;
    microformat& operator = (microformat&&) = default;
    virtual ~microformat () = default;
    explicit microformat (bool b) : microformat_base (b) {}
    virtual void reset ();
    void swap (microformat& mf);
    constexpr static typename ENUM :: value_type whoami () { return VOCAB; }
    constexpr static typename ENUM :: value_type html_class () { return VOCAB; }
    template < class PROPERTY > bool has () const
    {   return has_property < PROPERTY, PROPERTIES... > (); }
    template < class PROPERTY > void get (PROPERTY** p)
    {   get_property < PROPERTY, PROPERTIES... > (p_, p); }
    template < class PROPERTY > void get (const PROPERTY** p) const
    {   get_property < PROPERTY, PROPERTIES... > (p_, p); }
    template < class PROPERTY > PROPERTY* get ()
    {   PROPERTY* p = nullptr; get_property < PROPERTY, PROPERTIES... > (p_, &p); return p; }
    template < class PROPERTY > const PROPERTY* get () const
    {   PROPERTY* p = nullptr; get_property < PROPERTY, PROPERTIES... > (p_, &p); return p; }
    static ::std::string name () { return ENUM::name (VOCAB); }
    template < e_property PROP > bool is_known_name ()
    {   bool res = false;
        for_each_attribute (p_, [&](auto& p)
            {   if (! res) res = p.whoami () == PROP; } );
        return res; }
    virtual bool is_relational () const;
    virtual void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* pe);
    virtual void set_mf_value (nitpick& nits, const html_version& v, const e_property pp, element& e);
    virtual ::std::string get_string (const e_property pp);
    virtual bool has_prop (const e_property p) const;
    virtual bool invalid () const;
    virtual bool has_url () const;
    virtual bool verify_url (nitpick& nits, const html_version& v, element& e);
    virtual void verify (nitpick& nits, const html_version& v);
    virtual bool empty () const;
    virtual bool unknown () const;
    virtual ::std::string report () const; };

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    bool microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: has_prop (const e_property p) const  // I can do better here
{   bool res = false;
    for_each_attribute (p_, [&](auto t)
    {   res = res || (t.whoami () == p); } );
    return res; }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    void microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: reset ()
{   microformat_base::reset ();
    microformat mf;
    swap (mf); }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    void microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: swap (microformat& mf)
{   ::std::swap (p_, mf.p_);
    microformat_base::swap (mf); }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    bool microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: is_relational () const
{   bool res = false;
    for_each_attribute (p_, [&](auto& p)
    {   res = res || p.is_relational (); } );
    return res; }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    void microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* pe)
{   for_each_attribute (p_, [&](auto& p)
    {   p.verify_attribute (nits, v, e, pe, p.name ()); } ); }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    void microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: set_mf_value (nitpick& nits, const html_version& v, const e_property pp, element& e)
{   for_each_attribute (p_, [&](auto& p)
    {   if (p.whoami () == pp) p.set_mf_value (nits, v, e); } ); }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    ::std::string microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: get_string (const e_property pp)
{   ::std::string res;
    for_each_attribute (p_, [&](auto& p)
    {   if (p.whoami () == pp) res = p.get_string (); } );
    return res; }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    bool microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: invalid () const
{   if (! declared_) return true;
    bool res = false;
    for_each_attribute (p_, [&](auto& p)
    {   res = res || p.invalid (); } );
    return res; }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    bool microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: has_url () const
{   bool res = false;
    for_each_attribute (p_, [&](auto& p)
    {   res = res || p.is_url (); } );
    return res; }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    bool microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > ::
        verify_url (nitpick& nits, const html_version& v, element& e)
{   bool res = true;
    for_each_attribute (p_, [&](auto& p)
    {   res = res && p.verify_url (nits, v, e); } );
    return res; }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    bool microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: empty () const
{   if (! declared_) return true;
    bool res = true;
    for_each_attribute (p_, [&](auto& p)
    {   res = res && p.empty (); } );
    return res; }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    bool microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: unknown () const
{   if (! declared_) return true;
    bool res = true;
    for_each_attribute (p_, [&](auto& p)
        {   res = res && p.unknown (); } );
    return res; }

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    ::std::string microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: report () const
{   if (! context.tell (e_comment)) return ::std::string ();
    ::std::string res (fyi ());
    const bool xtra = context.tell (e_detail);
    res += name ();
    if (xtra)
    {   res += " (";
        res += ENUM::name (VOCAB);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (VOCAB);
        res += ")"; }
    bool first = true;
    for_each_attribute (p_, [&](auto& p)
    {   if (! p.unknown () || context.tell (e_splurge))
        {   if (first) first = false; else res += ",";
            res += " ";
            res += p.report (); } } );
    if (first) res += ": (empty)";
    res += "\n";
    return res; }

template < class ENUM, typename ENUM :: value_type VOCAB > struct verify_mf
{   static void hcard (nitpick& , const html_version& , const ::std::string& , fn_at1*, n_at1*, given_name_at1*, family_name_at1*, org_at1*, organisation_name_at1*, nickname_at1*) noexcept
    {  } };

template < > struct verify_mf < html_class, h1_card >
{   static void hcard (nitpick& nits, const html_version& v, const ::std::string& s, fn_at1* fn, n_at1* n, given_name_at1* given_name, family_name_at1* family_name, const org_at1* const org, organisation_name_at1* organisation_name, nickname_at1* nickname)
    {   VERIFY_NOT_NULL (org, __FILE__, __LINE__);
        VERIFY_NOT_NULL (organisation_name, __FILE__, __LINE__);
        if (org -> good () && ! organisation_name -> good ())
            organisation_name -> set_value (nits, v, org -> get_string ());
        bool non = false;
        VERIFY_NOT_NULL (fn, __FILE__, __LINE__);
        if (! fn -> good ())
        {   if (! s.empty ())
            {   nits.pick (nit_hcard_infer, es_info, ec_microformat, "hcard property fn set to ", enquote (s));
                fn -> set_value (nits, v, s); }
            else nits.pick (nit_no_fn, ed_microformats, "http://" MICROFORMATS_ORG "/wiki/hCard", es_error, ec_microformat, "hcard property fn is required but not supplied"); }
        VERIFY_NOT_NULL (n, __FILE__, __LINE__);
        if (fn -> good () && (org -> get_string () == fn -> get_string ()))
        {   if (n -> good ())
                nits.pick (nit_n_fn, ed_microformats, "http://" MICROFORMATS_ORG "/wiki/hCard", es_warning, ec_microformat, "when hcard org and fn are the same (e.g. ", quote (org -> get_string ()), "), n should be omitted");
            non = true; }
        else
        {   ::std::string content (fn -> get_string ());
            vstr_t components;
            ::boost::algorithm::split (components, content, ::boost::algorithm::is_any_of (" "), ::boost::algorithm::token_compress_on);
            VERIFY_NOT_NULL (family_name, __FILE__, __LINE__);
            VERIFY_NOT_NULL (given_name, __FILE__, __LINE__);
            if (! n -> good () && (components.size () == 2))
            {   const ::std::string::size_type len = ::gsl::at (components, 0).length ();
                if (::gsl::at (components, 0).at (len - 1) == ',')
                {   family_name -> set_value (nits, v, ::gsl::at (components, 0).substr (0, len - 1));
                    given_name -> set_value (nits, v, ::gsl::at (components, 1)); }
                else
                {   family_name -> set_value (nits, v, ::gsl::at (components, 1));
                    given_name -> set_value (nits, v, ::gsl::at (components, 0)); }
                ::std::string naam = given_name -> get_string () + " " + family_name -> get_string ();
                n -> set_value (nits, v, naam);
                if (context.tell (e_info)) nits.pick (nit_hcard_infer, ed_microformats, "http://" MICROFORMATS_ORG "g/wiki/hCard", es_info, ec_microformat, "hcard n set to ", quote (naam));
                return; }
            VERIFY_NOT_NULL (nickname, __FILE__, __LINE__);
            if (! nickname -> good () && (components.size () == 1) && ! ::gsl::at (components, 0).empty ())
            {   nickname -> set_value (nits, v, ::gsl::at (components, 0));
                nits.pick (nit_hcard_infer, ed_microformats, "http://" MICROFORMATS_ORG "/wiki/hCard", es_info, ec_microformat, "hcard nickname set to ", quote (::gsl::at (components, 0))); } }
        if (! n -> good () && ! non)
            if (! s.empty ())
            {   nits.pick (nit_hcard_infer, es_info, ec_microformat, "hcard property n set to ", enquote (s));
                n -> set_value (nits, v, s); }
            else nits.pick (nit_no_n, ed_microformats, "http://" MICROFORMATS_ORG "/wiki/hCard", es_error, ec_microformat, "hcard property n is required but neither supplied nor can be deduced"); } };

template < class ENUM, typename ENUM :: value_type VOCAB, int CATEGORY, e_linkaarea LINK, e_linkaarea A_AREA, class... PROPERTIES >
    void microformat < ENUM, VOCAB, CATEGORY, LINK, A_AREA, PROPERTIES... > :: verify (nitpick& nits, const html_version& v)
{   if (ENUM :: is_rel ()) return;
    if (! declared_) return;
    if (unknown () && ! text ().empty ())
        if (has < name_at > ())
        {   name_at* n = get < name_at > ();
            VERIFY_NOT_NULL (n, __FILE__, __LINE__);
            if (n -> unknown ())
            {   n -> set_value (nits, v, text ());
                nits.pick (nit_mf_infer, es_comment, ec_microformat, name (), " property ", n -> name (), " set to ", enquote (text ())); } }
    verify_mf < ENUM, VOCAB > :: hcard (nits, v, text (),
        get < fn_at1 > (), get < n_at1 > (), get < given_name_at1 > (), get < family_name_at1 > (), get < org_at1 > (), get < organisation_name_at1 > (), get < nickname_at1 > ());
    if (unknown ())
        nits.pick (nit_mf_empty, es_warning, ec_microformat, name (), " is empty; no properties were found or deduced"); };

#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
