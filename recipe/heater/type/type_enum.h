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
#include "type/type_case.h"

e_namespace map_xmlns_to_namespace (const e_xmlns x);

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
    explicit enum_base (element* box) : type_base < TYPE, E > (box) { }
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
    flags_t flags () const { return 0; }
    static flags_t flags (const TYPE ) { return 0; }
    ::std::string original () const { return original_; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void post_set_value (nitpick& nits, const html_version& v);
    void verify_attribute (nitpick& , const html_version& , const elem& , element* , const ::std::string& );
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

template < typename TYPE, e_type E > void enum_base < TYPE, E > :: verify_attribute (nitpick& , const html_version& , const elem& , element* , const ::std::string& ) { }
template < typename TYPE, e_type E > void enum_base < TYPE, E > :: post_set_value (nitpick& , const html_version& ) { }

template < > inline void enum_base < e_dir, t_dir > :: verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
{   if (type_base < e_dir, t_dir > :: good ())
        if (e.is_math ())
            if (v.math_version () > math_2)
                if ((value_ != di_ltr) && (value_ != di_rtl))
                {   nits.pick (nit_dir_rtl_ltr, ed_math_3, "3.2.2 Mathematics style attributes common to token elements", es_error, ec_attribute, "the DIR attribute can be 'ltr' or 'rtl' on a MathML 3 element");
                    type_base < e_dir, t_dir > :: status (s_invalid); } }

template < > inline void enum_base < e_inputtype, t_inputtype > :: post_set_value (nitpick& nits, const html_version& v)
{   if (type_base < e_inputtype, t_inputtype > :: good ())
        if ((get () == it_file) && (v == html_2) && ! context.rfc_1867 ())
        {   nits.pick (nit_rfc_1867, es_error, ec_type, "INPUT=file in ", v.report (), " requires RFC 1867, which has been disabled");
            type_base < e_inputtype, t_inputtype > :: status (s_invalid); } }

template < > inline void enum_base < e_linebreak, t_linebreak > :: verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* , const ::std::string& )
{   if (type_base < e_linebreak, t_linebreak > :: good ())
        if (e.is_math ())
            if (v.math_version () > math_2)
                if (value_ == lb_indentingnewline)
                {   nits.pick (nit_dir_rtl_ltr, ed_math_3, "3.2.5.2 Attributes", es_error, ec_attribute, "the value 'indentingnewline' for LINEBREAK is not valid in MathML 3");
                    type_base < e_linebreak, t_linebreak > :: status (s_invalid); } }

template < e_type E, typename ENUM, typename CATEGORY = ident_t, CATEGORY INIT = ns_default, class LC = sz_true > struct enum_n :
    public symbol < html_version, ENUM, CATEGORY, INIT, LC >, public enum_base < ENUM, E >
{   typedef typename enum_base < ENUM, E > :: value_type value_type;
    enum_n () = default;
    enum_n (const enum_n& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	enum_n (enum_n&&) = default;
#endif
    explicit enum_n (element* box) : enum_base < ENUM, E > (box) { }
	~enum_n() = default;
    enum_n& operator = (const enum_n& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	enum_n& operator = (enum_n&&) = default;
#endif
    static void init (nitpick& nits, const symbol_entry < html_version, ENUM, CATEGORY, INIT > table [], const ::std::size_t size, const bool wildcards = false)
    {   symbol < html_version, ENUM, CATEGORY, INIT, LC > :: init (nits, table, size, wildcards); }
    static void extend (const ::std::string& extension, const ::std::size_t e = 0)
    {   symbol < html_version, ENUM, CATEGORY, INIT, LC > :: extend (extension, e); }
    static void extend (const vstr_t& extension, const ::std::size_t e = 0)
    {   for (auto ext : extension) extend (ext, e); }
	static e_animation_type animation_type () { return at_other; }
    void swap (enum_n& t) NOEXCEPT
    {   type_base < ENUM, E >::swap (t);
        symbol < html_version, ENUM, CATEGORY, INIT, LC > :: swap (t); }
    void reset ()
    {   enum_n tmp;
        swap (tmp); }
    void reset (const enum_n& n)
    {   enum_n tmp (n);
        swap (tmp); }
    ENUM get () const { return enum_base < ENUM, E > :: value_; }
    void set (const value_type v) { enum_base < ENUM, E > :: value_ = v; }
    static ::std::string values (const html_version& v)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: value_list (v); }
    ::std::string get_string () const
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: name (enum_base < ENUM, E > :: value_); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   const ::std::string r = get_string ();
        if (r.empty ()) ss << '=' << original ();
        else ss << '=' << r; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void verify_attribute (nitpick& , const html_version& , const elem& , element* , const ::std::string& ) { }
    bool invalid () const { return enum_base < ENUM, E > :: invalid (); }
    bool unknown () const { return enum_base < ENUM, E > :: unknown (); }
    ::std::string name () const
    {   return get_string (); }
    static ::std::string name (const ENUM e)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: name (e); }
    ::std::string original () const
    {   return enum_base < ENUM, E > :: original (); }
    flags_t flags ()
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: flags (enum_base < ENUM, E > :: value_); }
    static flags_t flags (const ENUM e)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: flags (e); }
    html_version first () const { return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: first (); }
    html_version last () const { return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: last (); }
    static ::std::size_t value_count ()
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: value_count (); } };

template < e_type E, typename ENUM, typename CATEGORY, CATEGORY INIT, class LC >
    void enum_n < E, ENUM, CATEGORY, INIT, LC > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   //e_namespace examine_namespace (nitpick& nits, const html_version& v, ::std::string& s, ::std::string& ns);
    enum_base < ENUM, E > :: original_ = s;
    ::std::string pret (trim_the_lot_off (s));
    ::std::string t (careless_case < LC >::lower (pret));
    nitpick knots;
    if (t.empty ()) nits.pick (nit_empty, es_error, ec_type, "empty value");
    else
    {   bool parsed = symbol < html_version, ENUM, CATEGORY, INIT, LC > :: parse (nits, v, t);
        if (parsed)
        {   enum_base < ENUM, E > :: value_ = symbol < html_version, ENUM, CATEGORY, INIT, LC > :: get (); // ooops, two values :-(
            careless_case < LC > :: validate (nits, v, get_string (), pret);
            const html_version f = symbol < html_version, ENUM, CATEGORY, INIT, LC > :: first ();
            if (! may_apply (v, f, symbol < html_version, ENUM, CATEGORY, INIT, LC > :: last ()))
            {   v.check_math_svg (nits, f, name ());
                nits.pick (nit_wrong_version, es_error, ec_type, quote (s), " is invalid here in ", v.report ()); }
            else if (f.reject ())
                nits.pick (nit_rejected, es_error, ec_type, quote (s), " is valid but incompatible with ", v.report ());
            else
            {   if (f.deprecated (v))
                    nits.pick (nit_deprecated_value, es_warning, ec_type, quote (s), " is deprecated in ", v.report ());
                else if ((f.ext () & HE_M3_NONSTAND) != 0)
                    nits.pick (nit_non_standard_value, es_warning, ec_type, quote (s), " is non-standard in ", v.report (), ", and unlikely to be supported by many browsers.");
                enum_base < ENUM, E > :: status (s_good);
                enum_base < ENUM, E > :: post_set_value (nits, v);
                return; } }
        else
        {   check_spelling (nits, v, t);
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), " is invalid here"); } }
    enum_base < ENUM, E > :: status (s_invalid); }

template < > class type_master < t_accrual_method > : public enum_n < t_accrual_method, e_accrual_method >
{ using enum_n < t_accrual_method, e_accrual_method > :: enum_n; };

template < > class type_master < t_accrual_periodicity > : public enum_n < t_accrual_periodicity, e_accrual_periodicity >
{ using enum_n < t_accrual_periodicity, e_accrual_periodicity > :: enum_n; };

template < > class type_master < t_accrual_policy > : public enum_n < t_accrual_policy, e_accrual_policy >
{ using enum_n < t_accrual_policy, e_accrual_policy > :: enum_n; };

template < > struct type_master < t_action > : enum_n < t_action, e_action >
{ using enum_n < t_action, e_action > :: enum_n; };

template < > struct type_master < t_align3 > : enum_n < t_align3, e_align3 >
{ using enum_n < t_align3, e_align3 > :: enum_n; };

template < > struct type_master < t_alignment_baseline > : enum_n < t_alignment_baseline, e_alignment_baseline >
{ using enum_n < t_alignment_baseline, e_alignment_baseline > :: enum_n; };

template < > struct type_master < t_alignplus > : enum_n < t_alignplus, e_alignplus >
{ using enum_n < t_alignplus, e_alignplus > :: enum_n; };

template < > struct type_master < t_as > : enum_n < t_as, e_as >
{ using enum_n < t_as, e_as > :: enum_n; };

template < > struct type_master < t_autocapitalise > : enum_n < t_autocapitalise, e_autocapitalise >
{ using enum_n < t_autocapitalise, e_autocapitalise > :: enum_n; };

template < > struct type_master < t_autocomplete > : enum_n < t_autocomplete, e_autocomplete >
{ using enum_n < t_autocomplete, e_autocomplete > :: enum_n; };

template < > struct type_master < t_baselineshift > : enum_n < t_baselineshift, e_baselineshift >
{ using enum_n < t_baselineshift, e_baselineshift > :: enum_n; };

template < > struct type_master < t_beginfn > : enum_n < t_beginfn, e_beginfn >
{ using enum_n < t_beginfn, e_beginfn > :: enum_n; };

template < > struct type_master < t_cachekey > : enum_n < t_cachekey, e_cachekey >
{ using enum_n < t_cachekey, e_cachekey > :: enum_n; };

template < > struct type_master < t_charset > : enum_n < t_charset, e_charset >
{ using enum_n < t_charset, e_charset > :: enum_n; };

template < > struct type_master < t_citype > : enum_n < t_citype, e_citype >
{ using enum_n < t_citype, e_citype > :: enum_n; };

template < > struct type_master < t_colour_interpolation > : enum_n < t_colour_interpolation, e_colour_interpolation >
{ using enum_n < t_colour_interpolation, e_colour_interpolation > :: enum_n; };

template < > struct type_master < t_colour_rendering > : enum_n < t_colour_rendering, e_colour_rendering >
{ using enum_n < t_colour_rendering, e_colour_rendering > :: enum_n; };

template < > struct type_master < t_cookieid > : enum_n < t_cookieid, e_cookieid >
{ using enum_n < t_cookieid, e_cookieid > :: enum_n; };

template < > struct type_master < t_cntype > : enum_n < t_cntype, e_cntype >
{ using enum_n < t_cntype, e_cntype > :: enum_n; };

template < > struct type_master < t_comp_op > : enum_n < t_comp_op, e_comp_op >
{ using enum_n < t_comp_op, e_comp_op > :: enum_n; };

template < > struct type_master < t_composite_operator > : enum_n < t_composite_operator, e_composite_operator >
{ using enum_n < t_composite_operator, e_composite_operator > :: enum_n; };

template < > struct type_master < t_crossout > : enum_n < t_crossout, e_crossout >
{ using enum_n < t_crossout, e_crossout > :: enum_n; };

template < > struct type_master < t_csp_directive > : enum_n < t_csp_directive, e_csp_directive >
{ using enum_n < t_csp_directive, e_csp_directive > :: enum_n; };

template < > struct type_master < t_csp_keyword > : enum_n < t_csp_keyword, e_csp_keyword >
{ using enum_n < t_csp_keyword, e_csp_keyword > :: enum_n; };

template < > struct type_master < t_currency > : enum_n < t_currency, e_currency >
{ using enum_n < t_currency, e_currency > :: enum_n; };

template < > struct type_master < t_cursor > : enum_n < t_cursor, e_cursor >
{ using enum_n < t_cursor, e_cursor > :: enum_n; };

template < > class type_master < t_dcmitype > : public enum_n < t_dcmitype, e_dcmitype >
{ using enum_n < t_dcmitype, e_dcmitype > :: enum_n; };

template < > struct type_master < t_decalign > : enum_n < t_decalign, e_decalign >
{ using enum_n < t_decalign, e_decalign > :: enum_n; };

template < > struct type_master < t_dingbat > : enum_n < t_dingbat, e_dingbat >
{ using enum_n < t_dingbat, e_dingbat > :: enum_n; };

template < > struct type_master < t_dir > : enum_n < t_dir, e_dir >
{ using enum_n < t_dir, e_dir > :: enum_n; };

template < > struct type_master < t_display_align > : enum_n < t_display_align, e_display_align >
{ using enum_n < t_display_align, e_display_align > :: enum_n; };

template < > struct type_master < t_dominantbaseline > : enum_n < t_dominantbaseline, e_dominantbaseline >
{ using enum_n < t_dominantbaseline, e_dominantbaseline > :: enum_n; };

template < > struct type_master < t_enterkeyhint > : enum_n < t_enterkeyhint, e_enterkeyhint >
{ using enum_n < t_enterkeyhint, e_enterkeyhint > :: enum_n; };

template < > struct type_master < t_figalign > : enum_n < t_figalign, e_figalign >
{ using enum_n < t_figalign, e_figalign > :: enum_n; };

template < > struct type_master < t_filter_in > : enum_n < t_filter_in, e_filter_in >
{ using enum_n < t_filter_in, e_filter_in > :: enum_n; };

template < > struct type_master < t_fixedcolour > : enum_n < t_fixedcolour, e_fixedcolour >
{ using enum_n < t_fixedcolour, e_fixedcolour > :: enum_n; };

template < > struct type_master < t_fontname > : enum_n < t_fontname, e_fontname >
{ using enum_n < t_fontname, e_fontname > :: enum_n; };

template < > struct type_master < t_font_enum > : enum_n < t_font_enum, e_font_enum >
{ using enum_n < t_font_enum, e_font_enum > :: enum_n; };

template < > struct type_master < t_font_variant_2 > : enum_n < t_font_variant_2, e_font_variant_2 >
{ using enum_n < t_font_variant_2, e_font_variant_2 > :: enum_n; };

template < > struct type_master < t_font_variant_caps > : enum_n < t_font_variant_caps, e_font_variant_caps >
{ using enum_n < t_font_variant_caps, e_font_variant_caps > :: enum_n; };

template < > struct type_master < t_font_variant_east_asian > : enum_n < t_font_variant_east_asian, e_font_variant_east_asian >
{ using enum_n < t_font_variant_east_asian, e_font_variant_east_asian > :: enum_n; };

template < > struct type_master < t_font_variant_ligature > : enum_n < t_font_variant_ligature, e_font_variant_ligature >
{ using enum_n < t_font_variant_ligature, e_font_variant_ligature > :: enum_n; };

template < > struct type_master < t_font_variant_numeric > : enum_n < t_font_variant_numeric, e_font_variant_numeric >
{ using enum_n < t_font_variant_numeric, e_font_variant_numeric > :: enum_n; };

template < > struct type_master < t_halign > : enum_n < t_halign, e_halign >
{ using enum_n < t_halign, e_halign > :: enum_n; };

template < > struct type_master < t_httpequiv > : enum_n < t_httpequiv, e_httpequiv >
{ using enum_n < t_httpequiv, e_httpequiv > :: enum_n; };

template < > struct type_master < t_image_rendering > : enum_n < t_image_rendering, e_image_rendering >
{ using enum_n < t_image_rendering, e_image_rendering > :: enum_n; };

template < > struct type_master < t_icc > : enum_n < t_icc, e_icc >
{ using enum_n < t_icc, e_icc > :: enum_n; };

template < > struct type_master < t_indentalign > : enum_n < t_indentalign, e_indentalign >
{ using enum_n < t_indentalign, e_indentalign > :: enum_n; };

template < > struct type_master < t_inky > : enum_n < t_inky, e_inky >
{ using enum_n < t_inky, e_inky > :: enum_n; };

template < > struct type_master < t_inputmode > : enum_n < t_inputmode, e_inputmode >
{ using enum_n < t_inputmode, e_inputmode > :: enum_n; };

template < > struct type_master < t_inputplus > : enum_n < t_inputplus, e_inputplus >
{ using enum_n < t_inputplus, e_inputplus > :: enum_n; };

template < > struct type_master < t_inputtype > : enum_n < t_inputtype, e_inputtype >
{ using enum_n < t_inputtype, e_inputtype > :: enum_n; };

template < > struct type_master < t_inputtype3 > : enum_n < t_inputtype3, e_inputtype3 >
{ using enum_n < t_inputtype3, e_inputtype3 > :: enum_n; };

template < > struct type_master < t_inputtype32 > : enum_n < t_inputtype32, e_inputtype32 >
{ using enum_n < t_inputtype32, e_inputtype32 > :: enum_n; };

template < > struct type_master < t_inputtype4 > : enum_n < t_inputtype4, e_inputtype4 >
{ using enum_n < t_inputtype4, e_inputtype4 > :: enum_n; };

template < > struct type_master < t_inputtype5 > : enum_n < t_inputtype5, e_inputtype5 >
{ using enum_n < t_inputtype5, e_inputtype5 > :: enum_n; };

template < > struct type_master < t_kind > : enum_n < t_kind, e_kind >
{ using enum_n < t_kind, e_kind > :: enum_n; };

template < > struct type_master < t_lang > : enum_n < t_lang, e_lang >
{ using enum_n < t_lang, e_lang > :: enum_n; };

template < > struct type_master < t_length_absolute > : enum_n < t_length, e_length_absolute >
{ using enum_n < t_length, e_length_absolute > :: enum_n; };

template < > struct type_master < t_length_relative > : enum_n < t_length, e_length_relative >
{ using enum_n < t_length, e_length_relative > :: enum_n; };

template < > struct type_master < t_linebreak > : enum_n < t_linebreak, e_linebreak >
{ using enum_n < t_linebreak, e_linebreak > :: enum_n; };

template < > struct type_master < t_linkparam > : enum_n < t_linkparam, e_linkparam >
{ using enum_n < t_linkparam, e_linkparam > :: enum_n; };

template < > struct type_master < t_listtype > : enum_n < t_listtype, e_listtype, ident_t, ns_default, sz_false >
{ using enum_n < t_listtype, e_listtype, ident_t, ns_default, sz_false > :: enum_n; };

template < > struct type_master < t_longdivstyle > : enum_n < t_longdivstyle, e_longdivstyle >
{ using enum_n < t_longdivstyle, e_longdivstyle > :: enum_n; };

template < > struct type_master < t_mah > : enum_n < t_mah, e_mah >
{ using enum_n < t_mah, e_mah > :: enum_n; };

template < > struct type_master < t_mathalign > : enum_n < t_mathalign, e_mathalign >
{ using enum_n < t_mathalign, e_mathalign > :: enum_n; };

template < > struct type_master < t_mathlocation > : enum_n < t_mathlocation, e_mathlocation >
{ using enum_n < t_mathlocation, e_mathlocation > :: enum_n; };

template < > struct type_master < t_mathnotation > : enum_n < t_mathnotation, e_mathnotation >
{ using enum_n < t_mathnotation, e_mathnotation > :: enum_n; };

template < > struct type_master < t_mathoverflow > : enum_n < t_mathoverflow, e_mathoverflow >
{ using enum_n < t_mathoverflow, e_mathoverflow > :: enum_n; };

template < > struct type_master < t_mathvariant > : enum_n < t_mathvariant, e_mathvariant >
{ using enum_n < t_mathvariant, e_mathvariant > :: enum_n; };

template < > struct type_master < t_matrixtype > : enum_n < t_matrixtype, e_matrixtype >
{ using enum_n < t_matrixtype, e_matrixtype > :: enum_n; };

template < > struct type_master < t_media > : enum_n < t_media, e_media >
{ using enum_n < t_media, e_media > :: enum_n; };

template < > struct type_master < t_mediafeature > : enum_n < t_mediafeature, e_mediafeature >
{ using enum_n < t_mediafeature, e_mediafeature > :: enum_n; };

template < > struct type_master < t_mediakeyword > : enum_n < t_mediakeyword, e_mediakeyword >
{ using enum_n < t_mediakeyword, e_mediakeyword > :: enum_n; };

template < > struct type_master < t_metaname > : enum_n < t_metaname, e_metaname >
{ using enum_n < t_metaname, e_metaname > :: enum_n; };

template < > struct type_master < t_method > : enum_n < t_method, e_method >
{ using enum_n < t_method, e_method > :: enum_n; };

template < > struct type_master < t_mf_identifier > : enum_n < t_mf_identifier, e_mf_identifier >
{ using enum_n < t_mf_identifier, e_mf_identifier > :: enum_n; };

template < > struct type_master < t_mf_itemtype > : enum_n < t_mf_itemtype, e_mf_itemtype >
{ using enum_n < t_mf_itemtype, e_mf_itemtype > :: enum_n; };

template < > struct type_master < t_mf_listing_action > : enum_n < t_mf_listing_action, e_mf_listing_action >
{ using enum_n < t_mf_listing_action, e_mf_listing_action > :: enum_n; };

template < > struct type_master < t_mf_method > : enum_n < t_mf_method, e_mf_method >
{ using enum_n < t_mf_method, e_mf_method > :: enum_n; };

template < > struct type_master < t_mf_reviewtype > : enum_n < t_mf_reviewtype, e_mf_reviewtype >
{ using enum_n < t_mf_reviewtype, e_mf_reviewtype > :: enum_n; };

template < > struct type_master < t_microdata_domain > : enum_n < t_microdata_domain, e_microdata_domain >
{ using enum_n < t_microdata_domain, e_microdata_domain > :: enum_n; };

template < > struct type_master < t_microdata_root > : enum_n < t_microdata_root, e_microdata_root >
{ using enum_n < t_microdata_root, e_microdata_root > :: enum_n; };

template < > struct type_master < t_mime > : enum_n < t_mime, e_mimetype >
{ using enum_n < t_mime, e_mimetype > :: enum_n; };

template < > struct type_master < t_namedspace > : enum_n < t_namedspace, e_namedspace >
{ using enum_n < t_namedspace, e_namedspace > :: enum_n; };

template < > struct type_master < t_namespace > : enum_n < t_namespace, e_namespace >
{ using enum_n < t_namespace, e_namespace > :: enum_n; };

template < > struct type_master < t_ogtype > : enum_n < t_ogtype, e_ogtype >
{ using enum_n < t_ogtype, e_ogtype > :: enum_n; };

template < > struct type_master < t_page_orientation > : enum_n < t_page_orientation, e_page_orientation >
{ using enum_n < t_page_orientation, e_page_orientation > :: enum_n; };

template < > struct type_master < t_paintkeyword > : enum_n < t_paintkeyword, e_paintkeyword >
{ using enum_n < t_paintkeyword, e_paintkeyword > :: enum_n; };

template < > struct type_master < t_rdfa_context > : enum_n < t_rdfa_context, e_rdfa_context >
{ using enum_n < t_rdfa_context, e_rdfa_context > :: enum_n; };

template < > struct type_master < t_print > : enum_n < t_print, e_print >
{ using enum_n < t_print, e_print > :: enum_n; };

template < > struct type_master < t_pointer_events > : enum_n < t_pointer_events, e_pointer_events >
{ using enum_n < t_pointer_events, e_pointer_events > :: enum_n; };

template < > struct type_master < t_referrer > : enum_n < t_referrer, e_referrer >
{ using enum_n < t_referrer, e_referrer > :: enum_n; };

template < > struct type_master < t_rendering_in_tents > : enum_n < t_rendering_in_tents, e_rendering_in_tents >
{ using enum_n < t_rendering_in_tents, e_rendering_in_tents > :: enum_n; };

template < > struct type_master < t_role > : enum_n < t_role, e_aria_role >
{ using enum_n < t_role, e_aria_role > :: enum_n; };

template < > struct type_master < t_rules > : enum_n < t_rules, e_rules >
{ using enum_n < t_rules, e_rules > :: enum_n; };

template < > struct type_master < t_sandbox > : enum_n < t_sandbox, e_sandbox >
{ using enum_n < t_sandbox, e_sandbox > :: enum_n; };

template < > struct type_master < t_scei > : enum_n < t_scei, e_scei >
{ using enum_n < t_scei, e_scei > :: enum_n; };

template < > struct type_master < t_severity > : enum_n < t_severity, e_severity >
{ using enum_n < t_severity, e_severity > :: enum_n; };

template < > struct type_master < t_shadow > : enum_n < t_shadow, e_shadow >
{ using enum_n < t_shadow, e_shadow > :: enum_n; };

template < > struct type_master < t_shape7 > : enum_n < t_shape7, e_shape7 >
{ using enum_n < t_shape7, e_shape7 > :: enum_n; };

template < > struct type_master < t_ssi > : enum_n < t_ssi, e_ssi >
{ using enum_n < t_ssi, e_ssi > :: enum_n; };

template < > struct type_master < t_sgml > : enum_n < t_sgml, e_sgml >
{ using enum_n < t_sgml, e_sgml > :: enum_n; };

template < > struct type_master < t_shape_rendering > : enum_n < t_shape_rendering, e_shape_rendering >
{ using enum_n < t_shape_rendering, e_shape_rendering > :: enum_n; };

template < > struct type_master < t_smei > : enum_n < t_smei, e_smei >
{ using enum_n < t_smei, e_smei > :: enum_n; };

template < > struct type_master < t_ssi_comparison > : enum_n < t_ssi_comparison, e_ssi_comparison >
{ using enum_n < t_ssi_comparison, e_ssi_comparison > :: enum_n; };

template < > struct type_master < t_ssi_encoding > : enum_n < t_ssi_encoding, e_ssi_encoding >
{ using enum_n < t_ssi_encoding, e_ssi_encoding > :: enum_n; };

template < > struct type_master < t_ssi_env > : enum_n < t_ssi_env, e_ssi_env >
{ using enum_n < t_ssi_env, e_ssi_env > :: enum_n; };

template < > struct type_master < t_svg_align > : enum_n < t_svg_align, e_svg_align >
{ using enum_n < t_svg_align, e_svg_align > :: enum_n; };

template < > struct type_master < t_svg_display > : enum_n < t_svg_display, e_svg_display >
{ using enum_n < t_svg_display, e_svg_display > :: enum_n; };

template < > struct type_master < t_svg_feature > : enum_n < t_svg_feature, e_svg_feature >
{ using enum_n < t_svg_feature, e_svg_feature > :: enum_n; };

template < > struct type_master < t_svg_fontstretch > : enum_n < t_svg_fontstretch, e_svg_fontstretch >
{ using enum_n < t_svg_fontstretch, e_svg_fontstretch > :: enum_n; };

template < > struct type_master < t_svg_fontstretch_ff > : enum_n < t_svg_fontstretch_ff, e_svg_fontstretch_ff >
{ using enum_n < t_svg_fontstretch_ff, e_svg_fontstretch_ff > :: enum_n; };

template < > struct type_master < t_svg_fontstyle > : enum_n < t_svg_fontstyle, e_svg_fontstyle >
{ using enum_n < t_svg_fontstyle, e_svg_fontstyle > :: enum_n; };

template < > struct type_master < t_svg_fontweight > : enum_n < t_svg_fontweight, e_svg_fontweight >
{ using enum_n < t_svg_fontweight, e_svg_fontweight > :: enum_n; };

template < > struct type_master < t_svg_fontweight_ff > : enum_n < t_svg_fontweight_ff, e_svg_fontweight_ff >
{ using enum_n < t_svg_fontweight_ff, e_svg_fontweight_ff > :: enum_n; };

template < > struct type_master < t_svg_mode > : enum_n < t_svg_mode, e_svg_mode >
{ using enum_n < t_svg_mode, e_svg_mode > :: enum_n; };

template < > struct type_master < t_svg_overflow > : enum_n < t_svg_overflow, e_svg_overflow >
{ using enum_n < t_svg_overflow, e_svg_overflow > :: enum_n; };

template < > struct type_master < t_svg_type > : enum_n < t_svg_type, e_svg_type >
{ using enum_n < t_svg_type, e_svg_type > :: enum_n; };

template < > struct type_master < t_svg_version > : enum_n < t_svg_version, e_svg_version >
{ using enum_n < t_svg_version, e_svg_version > :: enum_n; };

template < > struct type_master < t_svg_version_grand > : enum_n < t_svg_version_grand, e_svg_version_grand >
{ using enum_n < t_svg_version_grand, e_svg_version_grand > :: enum_n; };

template < > struct type_master < t_tableframe > : enum_n < t_tableframe, e_tableframe >
{ using enum_n < t_tableframe, e_tableframe > :: enum_n; };

template < > struct type_master < t_text_decoration > : enum_n < t_text_decoration, e_text_decoration >
{ using enum_n < t_text_decoration, e_text_decoration > :: enum_n; };

template < > struct type_master < t_text_rendering > : enum_n < t_text_rendering, e_text_rendering >
{ using enum_n < t_text_rendering, e_text_rendering > :: enum_n; };

template < > struct type_master < t_transform_anim > : enum_n < t_transform_anim, e_transform_anim >
{ using enum_n < t_transform_anim, e_transform_anim > :: enum_n; };

template < > struct type_master < t_transformbehaviour > : enum_n < t_transformbehaviour, e_transformbehaviour >
{ using enum_n < t_transformbehaviour, e_transformbehaviour > :: enum_n; };

template < > struct type_master < t_transform_fn > : enum_n < t_transform_fn, e_transform_fn >
{ using enum_n < t_transform_fn, e_transform_fn > :: enum_n; };

template < > struct type_master < t_turbulence_type > : enum_n < t_turbulence_type, e_turbulence_type >
{ using enum_n < t_turbulence_type, e_turbulence_type > :: enum_n; };

template < > struct type_master < t_unit > : enum_n < t_unit, e_unit >
{ using enum_n < t_unit, e_unit > :: enum_n; };

template < > struct type_master < t_unicode_bidi > : enum_n < t_unicode_bidi, e_unicode_bidi >
{ using enum_n < t_unicode_bidi, e_unicode_bidi > :: enum_n; };

template < > struct type_master < t_vector_effect_2 > : enum_n < t_vector_effect_2, e_vector_effect_2 >
{ using enum_n < t_vector_effect_2, e_vector_effect_2 > :: enum_n; };

template < > struct type_master < t_vertical_align_enum > : enum_n < t_vertical_align_enum, e_vertical_align_enum >
{ using enum_n < t_vertical_align_enum, e_vertical_align_enum > :: enum_n; };

template < > struct type_master < t_whitespace > : enum_n < t_whitespace, e_whitespace >
{ using enum_n < t_whitespace, e_whitespace > :: enum_n; };

template < > struct type_master < t_writingmode > : enum_n < t_writingmode, e_writingmode >
{ using enum_n < t_writingmode, e_writingmode > :: enum_n; };

template < > struct type_master < t_xmlns > : enum_n < t_xmlns, e_xmlns >
{ using enum_n < t_xmlns, e_xmlns > :: enum_n; };

