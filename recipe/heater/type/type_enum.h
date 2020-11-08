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

template < typename TYPE, e_type E > struct enum_base : public type_base < TYPE, E >
{   typedef typename type_base < TYPE, E > :: value_type value_type;
    typedef typename type_base < TYPE, E > :: base_type base_type;
    typedef true_type has_int_type;
    value_type value_ = static_cast < value_type > (0);
    ::std::string original_;
    enum_base () = default;
    enum_base (const enum_base& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	enum_base(enum_base&&) = default;
#endif
	explicit enum_base (const html_version& v, const ::std::string& s);
    enum_base& operator = (const enum_base&) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	enum_base& operator = (enum_base&&) = default;
#endif
	~enum_base () = default;
    static ::std::string values (const html_version& ) { return ::std::string (); }
    static ::std::size_t value_count () { return 0; }
    void swap (enum_base& t) NOEXCEPT;
    ::std::string get_string () const { return ::std::string (); }
    ::std::string name () const { return ::std::string (); }
    static ::std::string name (const TYPE ) { return ::std::string (); }
    uint64_t flags () const { return 0; }
    static uint64_t flags (const TYPE ) { return 0; }
    ::std::string original () const { return original_; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void post_set_value (nitpick& nits, const html_version& v);
    void validate (nitpick& , const html_version& , const elem& , const ::std::string& );
    static value_type default_value () { return static_cast <value_type> (0); }
    value_type get () const { return value_; }
    int get_int () const { return static_cast < int > (value_); }
    bool has_value (const value_type& b) const { return type_base < TYPE, E > :: good () && (value_ == b); }
    ::std::size_t type () const { return static_cast < ::std::size_t > (get ()); } };

template < typename TYPE, e_type E > enum_base < TYPE, E > :: enum_base (const html_version& v, const ::std::string& )
{   enum_base e;
    e.set_value (v, e);
    if (e.good ()) swap (e); }

template < typename TYPE, e_type E > void enum_base < TYPE, E > :: swap (enum_base& t) NOEXCEPT
{   ::std::swap (value_, t.value_);
    original_.swap (t.original_);
    type_base < TYPE, E >::swap (t); }

template < typename TYPE, e_type E > void enum_base < TYPE, E > :: set_value (nitpick& nits, const html_version& , const ::std::string& s)
{   original_ = s;
    value_ = default_value ();
    nits.pick (nit_missing_set_value, es_catastrophic, ec_type, "Internal error: an enum is missing its setvalue");
    type_base < TYPE, E > :: status (s_invalid); }

template < typename TYPE, e_type E > void enum_base < TYPE, E > :: validate (nitpick& , const html_version& , const elem& , const ::std::string& )
{ }

template < typename TYPE, e_type E > void enum_base < TYPE, E > :: post_set_value (nitpick& , const html_version& )
{ }

template < > inline void enum_base < e_inputtype, t_inputtype > :: post_set_value (nitpick& nits, const html_version& v)
{   if (type_base < e_inputtype, t_inputtype > :: good ())
        if ((get () == it_file) && (v == html_2) && ! context.rfc_1867 ())
        {   nits.pick (nit_rfc_1867, es_error, ec_type, "INPUT=file in ", v.report (), " requires RFC 1867, which has been disabled");
            type_base < e_inputtype, t_inputtype > :: status (s_invalid); } }

template < e_type E, typename ENUM, class LC = sz_true > struct enum_n : public symbol < ENUM, LC >, public enum_base < ENUM, E >
{   typedef typename enum_base < ENUM, E > :: value_type value_type;
    static void init (nitpick& nits, const symbol_entry < ENUM > table [], const ::std::size_t size, const bool wildcards = false)
    {   symbol < ENUM, LC > :: init (nits, table, size, wildcards); }
    static void extend (const ::std::string& extension, const ::std::size_t e = 0)
    {   symbol < ENUM, LC > :: extend (extension, e); }
    static void extend (const vstr_t& extension, const ::std::size_t e = 0)
    {   for (auto ext : extension) extend (ext, e); }
    enum_n () = default;
    enum_n (const enum_n& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	enum_n(enum_n&&) = default;
#endif
	~enum_n() = default;
    enum_n& operator = (const enum_n& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	enum_n& operator = (enum_n&&) = default;
#endif
	void swap (enum_n& t) NOEXCEPT
    {   type_base < ENUM, E >::swap (t);
        symbol < ENUM, LC > :: swap (t); }
    void reset ()
    {   enum_n tmp;
        swap (tmp); }
    void reset (const enum_n& n)
    {   enum_n tmp (n);
        swap (tmp); }
    ENUM get () const { return enum_base < ENUM, E > :: value_; }
    static ::std::string values (const html_version& v)
    {   return symbol < ENUM, LC > :: value_list (v); }
    ::std::string get_string () const
    {   return symbol < ENUM, LC > :: name (enum_base < ENUM, E > :: value_); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void validate (nitpick& , const html_version& , const elem& , const ::std::string& ) { }
    bool invalid () const { return enum_base < ENUM, E > :: invalid (); }
    bool unknown () const { return enum_base < ENUM, E > :: unknown (); }
    ::std::string name () const
    {   return get_string (); }
    static ::std::string name (const ENUM e)
    {   return symbol < ENUM, LC > :: name (e); }
    uint64_t flags ()
    {   return symbol < ENUM, LC > :: flags (enum_base < ENUM, E > :: value_); }
    static uint64_t flags (const ENUM e)
    {   return symbol < ENUM, LC > :: flags (e); }
    html_version first () const { return symbol < ENUM, LC > :: first (); }
    html_version last () const { return symbol < ENUM, LC > :: last (); }
    static ::std::size_t value_count ()
    {   return symbol < ENUM, LC > :: value_count (); } };

template < e_type E, typename ENUM, class LC > void enum_n < E, ENUM, LC > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   e_namespace examine_namespace (nitpick& nits, const html_version& v, ::std::string& s);
    enum_base < ENUM, E > :: original_ = s;
    if (v.xhtml () && ! v.svg () && (s.find_first_of (UPPERCASE) != ::std::string::npos))
        nits.pick (nit_xhtml_enum_lc, ed_x1, "4.11. Attributes with pre-defined value sets", es_warning, ec_type, "enumerations must be lower cased in ", v.report ());
    nitpick knots;
    ::std::string t (s);
    if (t.empty ()) nits.pick (nit_empty, es_error, ec_type, "empty value");
    else
    {   bool parsed = symbol < ENUM, LC > :: parse (knots, v, t);
        if (parsed || (v < html_4_0)) nits.merge (knots);
        else
        {   e_namespace n = examine_namespace (nits, v, t);
            if (n == ns_error) nits.pick (nit_bad_namespace, es_warning, ec_namespace, "unknown namespace");
            else if (n == ns_default) nits.merge (knots);
            else parsed = symbol < ENUM, LC > :: parse (nits, v, t, n); }
        if (parsed)
        {   enum_base < ENUM, E > :: value_ = symbol < ENUM, LC > :: get (); // ooops, two values :-(
            const html_version f = symbol < ENUM, LC > :: first ();
            if (! may_apply (v, f, symbol < ENUM, LC > :: last ()))
                nits.pick (nit_wrong_version, es_error, ec_type, quote (s), " is invalid here in ", v.report ());
            else if (f.reject ())
                nits.pick (nit_rejected, es_error, ec_type, quote (s), " is valid but incompatible with ", v.report ());
            else
            {   if (f.deprecated (v)) nits.pick (nit_deprecated_value, es_warning, ec_type, quote (s), " is deprecated in ", v.report ());
                enum_base < ENUM, E > :: status (s_good);
                enum_base < ENUM, E > :: post_set_value (nits, v);
                return; } }
        else
        {   check_spelling (nits, v, t);
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), " is invalid here"); } }
    enum_base < ENUM, E > :: status (s_invalid); }

template < > class type_master < t_action > : public enum_n < t_action, e_action > { };
template < > class type_master < t_align3 > : public enum_n < t_align3, e_align3 > { };
template < > class type_master < t_alignmentbaseline > : public enum_n < t_alignmentbaseline, e_alignmentbaseline > { };
template < > class type_master < t_alignplus > : public enum_n < t_alignplus, e_alignplus > { };
template < > class type_master < t_as > : public enum_n < t_as, e_as > { };
template < > class type_master < t_autocapitalise > : public enum_n < t_autocapitalise, e_autocapitalise > { };
template < > class type_master < t_autocomplete > : public enum_n < t_autocomplete, e_autocomplete > { };
template < > class type_master < t_charset > : public enum_n < t_charset, e_charset > { };
template < > class type_master < t_composite_operator > : public enum_n < t_composite_operator, e_composite_operator > { };
template < > class type_master < t_currency > : public enum_n < t_currency, e_currency > { };
template < > class type_master < t_cursor > : public enum_n < t_cursor, e_cursor > { };
template < > class type_master < t_decalign > : public enum_n < t_decalign, e_decalign > { };
template < > class type_master < t_dingbat > : public enum_n < t_dingbat, e_dingbat > { };
template < > class type_master < t_dir > : public enum_n < t_dir, e_dir > { };
template < > class type_master < t_display > : public enum_n < t_display, e_display > { };
template < > class type_master < t_dominantbaseline > : public enum_n < t_dominantbaseline, e_dominantbaseline > { };
template < > class type_master < t_enterkeyhint > : public enum_n < t_enterkeyhint, e_enterkeyhint > { };
template < > class type_master < t_figalign > : public enum_n < t_figalign, e_figalign > { };
template < > class type_master < t_fixedcolour > : public enum_n < t_fixedcolour, e_fixedcolour > { };
template < > class type_master < t_halign > : public enum_n < t_halign, e_halign > { };
template < > class type_master < t_httpequiv > : public enum_n < t_httpequiv, e_httpequiv > { };
template < > class type_master < t_inky > : public enum_n < t_inky, e_inky > { };
template < > class type_master < t_inputmode > : public enum_n < t_inputmode, e_inputmode > { };
template < > class type_master < t_inputplus > : public enum_n < t_inputplus, e_inputplus > { };
template < > class type_master < t_inputtype > : public enum_n < t_inputtype, e_inputtype > { };
template < > class type_master < t_inputtype3 > : public enum_n < t_inputtype3, e_inputtype3 > { };
template < > class type_master < t_inputtype32 > : public enum_n < t_inputtype32, e_inputtype32 > { };
template < > class type_master < t_inputtype4 > : public enum_n < t_inputtype4, e_inputtype4 > { };
template < > class type_master < t_inputtype5 > : public enum_n < t_inputtype5, e_inputtype5 > { };
template < > class type_master < t_kind > : public enum_n < t_kind, e_kind > { };
template < > class type_master < t_linebreak > : public enum_n < t_linebreak, e_linebreak > { };
template < > class type_master < t_lang > : public enum_n < t_lang, e_lang > { };
template < > class type_master < t_listtype > : public enum_n < t_listtype, e_listtype, sz_false > { };
template < > class type_master < t_mah > : public enum_n < t_mah, e_mah > { };
template < > class type_master < t_mathalign > : public enum_n < t_mathalign, e_mathalign > { };
template < > class type_master < t_mathvariant > : public enum_n < t_mathvariant, e_mathvariant > { };
template < > class type_master < t_matrix_type > : public enum_n < t_matrix_type, e_matrix_type > { };
template < > class type_master < t_media > : public enum_n < t_media, e_media > { };
template < > class type_master < t_media_feature > : public enum_n < t_media_feature, e_media_feature > { };
template < > class type_master < t_media_keyword > : public enum_n < t_media_keyword, e_media_keyword > { };
template < > class type_master < t_metaname > : public enum_n < t_metaname, e_metaname > { };
template < > class type_master < t_method > : public enum_n < t_method, e_method > { };
template < > class type_master < t_microdata_domain > : public enum_n < t_microdata_domain, e_microdata_domain > { };
template < > class type_master < t_mime > : public enum_n < t_mime, e_mimetype > { };
template < > class type_master < t_namedspace > : public enum_n < t_namedspace, e_namedspace > { };
template < > class type_master < t_namespace > : public enum_n < t_namespace, e_namespace > { };
template < > class type_master < t_mathnotation > : public enum_n < t_mathnotation, e_mathnotation > { };
template < > class type_master < t_paintkeyword > : public enum_n < t_paintkeyword, e_paintkeyword > { };
template < > class type_master < t_print > : public enum_n < t_print, e_print > { };
template < > class type_master < t_pointerevents > : public enum_n < t_pointerevents, e_pointerevents > { };
template < > class type_master < t_referrer > : public enum_n < t_referrer, e_referrer > { };
template < > class type_master < t_renderingintent > : public enum_n < t_renderingintent, e_renderingintent > { };
template < > class type_master < t_role > : public enum_n < t_role, e_aria_role > { };
template < > class type_master < t_rules > : public enum_n < t_rules, e_rules > { };
template < > class type_master < t_sandbox > : public enum_n < t_sandbox, e_sandbox > { };
template < > class type_master < t_shape7 > : public enum_n < t_shape7, e_shape7 > { };
template < > class type_master < t_ssi > : public enum_n < t_ssi, e_ssi > { };
template < > class type_master < t_sgml > : public enum_n < t_sgml, e_sgml > { };
template < > class type_master < t_shaperendering > : public enum_n < t_shaperendering, e_shaperendering > { };
template < > class type_master < t_textrendering > : public enum_n < t_textrendering, e_textrendering > { };
template < > class type_master < t_ssi_comparison > : public enum_n < t_ssi_comparison, e_ssi_comparison > { };
template < > class type_master < t_ssi_encoding > : public enum_n < t_ssi_encoding, e_ssi_encoding > { };
template < > class type_master < t_ssi_env > : public enum_n < t_ssi_env, e_ssi_env > { };
template < > class type_master < t_svg_align > : public enum_n < t_svg_align, e_svg_align > { };
template < > class type_master < t_svg_feature > : public enum_n < t_svg_feature, e_svg_feature > { };
template < > class type_master < t_svg_fontstretch > : public enum_n < t_svg_fontstretch, e_svg_fontstretch > { };
template < > class type_master < t_svg_fontstretch_ff > : public enum_n < t_svg_fontstretch_ff, e_svg_fontstretch_ff > { };
template < > class type_master < t_svg_fontweight > : public enum_n < t_svg_fontweight, e_svg_fontweight > { };
template < > class type_master < t_svg_fontweight_ff > : public enum_n < t_svg_fontweight_ff, e_svg_fontweight_ff > { };
template < > class type_master < t_svg_mode > : public enum_n < t_svg_mode, e_svg_mode > { };
template < > class type_master < t_svg_overflow > : public enum_n < t_svg_overflow, e_svg_overflow > { };
template < > class type_master < t_svg_version > : public enum_n < t_svg_version, e_svg_version > { };
template < > class type_master < t_tableframe > : public enum_n < t_tableframe, e_tableframe > { };
template < > class type_master < t_textdecoration > : public enum_n < t_textdecoration, e_textdecoration > { };
template < > class type_master < t_transform_anim > : public enum_n < t_transform_anim, e_transform_anim > { };
template < > class type_master < t_transform_fn > : public enum_n < t_transform_fn, e_transform_fn > { };
template < > class type_master < t_turbulence_type > : public enum_n < t_turbulence_type, e_turbulence_type > { };
template < > class type_master < t_vectoreffect_2 > : public enum_n < t_vectoreffect_2, e_vectoreffect_2 > { };
template < > class type_master < t_writingmode > : public enum_n < t_writingmode, e_writingmode > { };
template < > class type_master < t_xlinkshow > : public enum_n < t_xlinkshow, e_xlinkshow > { };
template < > class type_master < t_xmlns > : public enum_n < t_xmlns, e_xmlns > { };
