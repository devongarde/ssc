/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "base/type_master.h"
#include "base/type_case.h"
#include "spell/spell.h"

::std::size_t enum_base_count (const e_type t);

template < typename TYPE, e_type E > struct enum_base : public type_base < TYPE, E >
{   typedef typename type_base < TYPE, E > :: value_type value_type;
    typedef typename type_base < TYPE, E > :: base_type base_type;
    typedef true_type has_int_type;
    value_type value_ = GSL_NARROW_CAST < value_type > (0);
    ::std::string original_;
    DEFAULT_CONSTRUCTORS (enum_base);
    explicit enum_base (const html_version& v, const ::std::string& s);
    explicit enum_base (element* box) noexcept : type_base < TYPE, E > (box) { }
    static ::std::string values (const html_version& ) { return ::std::string (); }
    static ::std::size_t value_count () { return 0; }
    void swap (enum_base& t) noexcept;
    ::std::string get_string () const { return ::std::string (); }
    ::std::string name () const { return ::std::string (); }
    static ::std::string name (const TYPE ) { return ::std::string (); }
    flags_t flags () const { return 0; }
    static flags_t flags (const TYPE ) { return 0; }
    ::std::string original () const { return original_; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void post_set_value (nitpick& nits, const html_version& v);
    void verify_attribute (nitpick& , const html_version& , const elem& , element* , const ::std::string& );
    static value_type default_value () noexcept { return static_cast <value_type> (0); }
    value_type get () const noexcept { return value_; }
    int get_int () const noexcept { return static_cast < int > (value_); }
    void accumulate (stats_t* ) const { }
    void accumulate (stats_t* , const e_element ) const { }
    void accumulate (stats_t* , const element_bitset& ) const { }
    bool has_value (const value_type& b) const { return type_base < TYPE, E > :: good () && (value_ == b); }
    ::std::size_t type () const noexcept { return static_cast < ::std::size_t > (get ()); } };

template < typename TYPE, e_type E > enum_base < TYPE, E > :: enum_base (const html_version& v, const ::std::string& )
{   enum_base e;
    e.set_value (v, e);
    if (e.good ()) swap (e); }

template < typename TYPE, e_type E > void enum_base < TYPE, E > :: swap (enum_base& t) noexcept
{   ::std::swap (value_, t.value_);
    original_.swap (t.original_);
    type_base < TYPE, E >::swap (t); }

template < typename TYPE, e_type E > void enum_base < TYPE, E > :: set_value (nitpick& nits, const html_version& , const ::std::string& s)
{   original_ = s;
    value_ = default_value ();
    nits.pick (nit_missing_set_value, es_catastrophic, ec_type, "Internal error: an enum is missing its setvalue (", type_name (E), ")");
    type_base < TYPE, E > :: status (s_invalid); }

template < typename TYPE, e_type E > void enum_base < TYPE, E > :: verify_attribute (nitpick& , const html_version& , const elem& , element* , const ::std::string& ) { }

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26440)
#endif // _MSC_VER
template < typename TYPE, e_type E > void enum_base < TYPE, E > :: post_set_value (nitpick& , const html_version& ) { }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

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
    DEFAULT_CONSTRUCTORS (enum_n);
    explicit enum_n (element* box) noexcept : enum_base < ENUM, E > (box) { }
    static void init (nitpick& nits, const symbol_entry < html_version, ENUM, CATEGORY, INIT > table [], const ::std::size_t size, const bool wildcards = false)
    {   eleanor f (lox_eleanor);
        symbol < html_version, ENUM, CATEGORY, INIT, LC > :: init (nits, table, size, wildcards); }
    static void extend (const ::std::string& extension, const ::std::size_t e = 0)
    {   eleanor f (lox_eleanor);
        symbol < html_version, ENUM, CATEGORY, INIT, LC > :: extend (extension, e); }
    static void extend (const vstr_t& extension, const ::std::size_t e = 0)
    {   for (auto& ext : extension) extend (ext, e); }
    static bool exists (const ::std::string& x)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: exists (x); }
    static e_animation_type animation_type () noexcept { return at_other; }
    void swap (enum_n& t) noexcept
    {   type_base < ENUM, E >::swap (t);
        symbol < html_version, ENUM, CATEGORY, INIT, LC > :: swap (t); }
    void reset ()
    {   enum_n tmp;
        swap (tmp); }
    void reset (const enum_n& n)
    {   enum_n tmp (n);
        swap (tmp); }
    ENUM get () const noexcept { return enum_base < ENUM, E > :: value_; }
    void set (const value_type v) noexcept { enum_base < ENUM, E > :: value_ = v; }
    static ::std::string values (const html_version& v)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: value_list (v); }
    static ::std::size_t extra_values ()
    {   const ::std::size_t vc = symbol < html_version, ENUM, CATEGORY, INIT, LC >::value_count ();
        const ::std::size_t bc = enum_base_count (E);
        PRESUME (bc <= vc, __FILE__, __LINE__);
        return vc - bc; }
    static void remove_any_extras ()
    {   eleanor f (lox_eleanor);
        symbol < html_version, ENUM, CATEGORY, INIT, LC >::remove_any_extras (enum_base_count (E)); }
    ::std::string get_string () const
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: name (enum_base < ENUM, E > :: value_); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   const ::std::string r = get_string ();
        if (r.empty ()) ss << '=' << original ();
        else ss << '=' << r; }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    void verify_attribute (nitpick& , const html_version& , const elem& , element* , const ::std::string& ) { }
    bool invalid () const noexcept { return enum_base < ENUM, E > :: invalid (); }
    bool unknown () const noexcept { return enum_base < ENUM, E > :: unknown (); }
    ::std::string name () const
    {   return get_string (); }
    static ::std::string base_name (const ENUM e)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: base_name (e); }
    static ::std::string name (const ENUM e)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: name (e); }
    ::std::string original () const
    {   return enum_base < ENUM, E > :: original (); }
    flags_t flags ()
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: flags (enum_base < ENUM, E > :: value_); }
    static flags_t flags (const ENUM e)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: flags (e); }
    flags_t ext2 ()
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: flags2 (enum_base < ENUM, E > :: value_); }
    static flags_t ext2 (const ENUM x)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: flags2 (x); }
    static html_version first_version (const ENUM x)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: first_version (x); }
    static html_version final_version (const ENUM x)
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: final_version (x); }
    void accumulate (stats_t* st) const
    {   enum_base < ENUM, E > :: accumulate (st); }
    void accumulate (stats_t* st, const e_element e) const
    {   enum_base < ENUM, E > :: accumulate (st, e); }
    void accumulate (stats_t* st, const element_bitset& e) const
    {   enum_base < ENUM, E > :: accumulate (st, e); }
    html_version first () const noexcept { return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: first (); }
    html_version last () const { return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: last (); }
    html_version first (const ::std::size_t e) { return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: first (e); }
    html_version last (const ::std::size_t e) { return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: last (e); }
    static ::std::size_t value_count ()
    {   return symbol < html_version, ENUM, CATEGORY, INIT, LC > :: value_count (); } };

template < e_type E, typename ENUM, typename CATEGORY, CATEGORY INIT, class LC >
    void enum_n < E, ENUM, CATEGORY, INIT, LC > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   enum_base < ENUM, E > :: original_ = s;
    ::std::string pret (uq0 (trim_the_lot_off (s)));
    ::std::string t (careless_case < LC >::lower (pret));
    nitpick knots;
    if (t.empty ())
        nits.pick (nit_empty, es_error, ec_type, "empty value (", type_name (E), ")");
    else if (! symbol < html_version, ENUM, CATEGORY, INIT, LC > :: parse (nits, v, t))
#ifdef VS2022
#pragma warning (push, 3)
#pragma warning (disable : 4127)
#endif // VS2022
    {   if (E != t_class) check_identifier_spelling (nits, v, t);
#ifdef VS2022
#pragma warning (pop)
#endif // VS2022
        nits.pick (nit_unrecognised_value, es_error, ec_type, quote (s), " is not a valid ", type_name (E), " value (10)"); }
    else
    {   enum_base < ENUM, E > :: value_ = symbol < html_version, ENUM, CATEGORY, INIT, LC > :: get (); // ooops, two values :-(
        careless_case < LC > :: validate (nits, v, get_string (), pret);
        const html_version f = symbol < html_version, ENUM, CATEGORY, INIT, LC > :: first ();
        if (! may_apply (v, f, symbol < html_version, ENUM, CATEGORY, INIT, LC > :: last ()))
        {   v.check_math_svg (nits, f, name ());
            nits.pick (nit_wrong_version, es_error, ec_type, quote (s), " is invalid here in ", v.report (), " (3)"); }
        else if (! v.is_css_compatible (f.ext2 (), f.ext3 (), f.ext4 (), f.ext5 ()))
            nits.pick (nit_css_version, es_error, ec_type, quote (s), " is invalid here, but valid with, for example, CSS ", f.long_css_version_name ());
        else if (f.reject ())
            nits.pick (nit_rejected, es_error, ec_type, quote (s), " is valid but incompatible with ", v.report ());
        else if (f.out_of_scope ())
            nits.pick (nit_out_of_scope, es_error, ec_type, quote (s), " is out of scope for an HTML server");
        else
        {   f.check_status (nits, symbol < html_version, ENUM, CATEGORY, INIT, LC > :: name ());
            if (f.known_insecure ())
                nits.pick (nit_known_insecure, es_warning, ec_type, quote (s), " has known insecurities, so, if it must be used, do so with great care.");
            if (f.deprecated (v))
                nits.pick (nit_deprecated_value, es_warning, ec_type, quote (s), " is deprecated in ", v.report (), " (2)");
            if ((f.ext () & HE_M3_NONSTAND) != 0)
                nits.pick (nit_non_standard_value, es_warning, ec_type, quote (s), " is non-standard in ", v.report (), ", and unlikely to be supported by many browsers");
            else if (f.bespoke ())
                nits.pick (nit_bespoke_obsolete, es_comment, ec_type, quote (s), " is bespoke, obsolete, or both, so is unlikely to be supported by every browser.");
            enum_base < ENUM, E > :: status (s_good);
            enum_base < ENUM, E > :: post_set_value (nits, v);
            return; } }
    enum_base < ENUM, E > :: status (s_invalid); }

#define ENUM_N(XXX) enum_n < t_##XXX, e_##XXX >

template < > class type_master < t_abfmt > : public ENUM_N (abfmt)
{ using ENUM_N (abfmt) :: enum_n; };

template < > class type_master < t_accrual_method > : public ENUM_N (accrual_method)
{ using ENUM_N (accrual_method) :: enum_n; };

template < > class type_master < t_accrual_periodicity > : public ENUM_N (accrual_periodicity)
{ using ENUM_N (accrual_periodicity) :: enum_n; };

template < > class type_master < t_accrual_policy > : public ENUM_N (accrual_policy)
{ using ENUM_N (accrual_policy) :: enum_n; };

template < > struct type_master < t_action > : ENUM_N (action)
{ using ENUM_N (action) :: enum_n; };

template < > struct type_master < t_advar > : ENUM_N (advar)
{ using ENUM_N (advar) :: enum_n; };

template < > struct type_master < t_align3 > : ENUM_N (align3)
{ using ENUM_N (align3) :: enum_n; };

template < > struct type_master < t_alignment_baseline > : ENUM_N (alignment_baseline)
{ using ENUM_N (alignment_baseline) :: enum_n; };

template < > struct type_master < t_alignplus > : ENUM_N (alignplus)
{ using ENUM_N (alignplus) :: enum_n; };

template < > struct type_master < t_aria_current > : ENUM_N (aria_current)
{ using ENUM_N (aria_current) :: enum_n; };

template < > struct type_master < t_aria_popup > : ENUM_N (aria_popup)
{ using ENUM_N (aria_popup) :: enum_n; };

template < > struct type_master < t_as > : ENUM_N (as)
{ using ENUM_N (as) :: enum_n; };

template < > struct type_master < t_as_units > : ENUM_N (as_units)
{ using ENUM_N (as_units) :: enum_n; };

template < > struct type_master < t_attr_unit > : ENUM_N (attr_unit)
{ using ENUM_N (attr_unit) :: enum_n; };

template < > struct type_master < t_autocapitalise > : ENUM_N (autocapitalise)
{ using ENUM_N (autocapitalise) :: enum_n; };

template < > struct type_master < t_autocomplete > : ENUM_N (autocomplete)
{ using ENUM_N (autocomplete) :: enum_n; };

template < > struct type_master < t_baselineshift > : ENUM_N (baselineshift)
{ using ENUM_N (baselineshift) :: enum_n; };

template < > struct type_master < t_bcess > : ENUM_N (bcess)
{ using ENUM_N (bcess) :: enum_n; };

template < > struct type_master < t_cachekey > : ENUM_N (cachekey)
{ using ENUM_N (cachekey) :: enum_n; };

template < > struct type_master < t_celnrs > : ENUM_N (celnrs)
{ using ENUM_N (celnrs) :: enum_n; };

template < > struct type_master < t_celrs > : ENUM_N (celrs)
{ using ENUM_N (celrs) :: enum_n; };

template < > struct type_master < t_charset > : ENUM_N (charset)
{ using ENUM_N (charset) :: enum_n; };

template < > struct type_master < t_citype > : ENUM_N (citype)
{ using ENUM_N (citype) :: enum_n; };

template < > struct type_master < t_colour_interpolation > : ENUM_N (colour_interpolation)
{ using ENUM_N (colour_interpolation) :: enum_n; };

template < > struct type_master < t_colour_rendering > : ENUM_N (colour_rendering)
{ using ENUM_N (colour_rendering) :: enum_n; };

template < > struct type_master < t_cookieid > : ENUM_N (cookieid)
{ using ENUM_N (cookieid) :: enum_n; };

template < > struct type_master < t_cntype > : ENUM_N (cntype)
{ using ENUM_N (cntype) :: enum_n; };

template < > struct type_master < t_comp_op > : ENUM_N (comp_op)
{ using ENUM_N (comp_op) :: enum_n; };

template < > struct type_master < t_command2 > : ENUM_N (command2)
{ using ENUM_N (command2) :: enum_n; };

template < > struct type_master < t_composite_operator > : ENUM_N (composite_operator)
{ using ENUM_N (composite_operator) :: enum_n; };

template < > struct type_master < t_conlit > : ENUM_N (conlit)
{ using ENUM_N (conlit) :: enum_n; };

template < > struct type_master < t_container_condition > : ENUM_N (container_condition)
{ using ENUM_N (container_condition) :: enum_n; };

template < > struct type_master < t_country > : ENUM_N (country)
{ using ENUM_N (country) :: enum_n; };

template < > struct type_master < t_copy > : ENUM_N (copy)
{ using ENUM_N (copy) :: enum_n; };

template < > struct type_master < t_cr_fileproperty > : ENUM_N (cr_fileproperty)
{ using ENUM_N (cr_fileproperty) :: enum_n; };

template < > struct type_master < t_crossout > : ENUM_N (crossout)
{ using ENUM_N (crossout) :: enum_n; };

template < > struct type_master < t_csp_directive > : ENUM_N (csp_directive)
{ using ENUM_N (csp_directive) :: enum_n; };

template < > struct type_master < t_csp_keyword > : ENUM_N (csp_keyword)
{ using ENUM_N (csp_keyword) :: enum_n; };

template < > struct type_master < t_css_aaalri > : ENUM_N (css_aaalri)
{ using ENUM_N (css_aaalri) :: enum_n; };

template < > struct type_master < t_css_absolute_size > : ENUM_N (css_absolute_size)
{ using ENUM_N (css_absolute_size) :: enum_n; };

template < > struct type_master < t_css_align_content > : ENUM_N (css_align_content)
{ using ENUM_N (css_align_content) :: enum_n; };

template < > struct type_master < t_css_align_items > : ENUM_N (css_align_items)
{ using ENUM_N (css_align_items) :: enum_n; };

template < > struct type_master < t_css_all_2 > : ENUM_N (css_all_2)
{ using ENUM_N (css_all_2) :: enum_n; };

template < > struct type_master < t_css_anchor_side_e > : ENUM_N (css_anchor_side_e)
{ using ENUM_N (css_anchor_side_e) :: enum_n; };

template < > struct type_master < t_css_anchor_size_e > : ENUM_N (css_anchor_size_e)
{ using ENUM_N (css_anchor_size_e) :: enum_n; };

template < > struct type_master < t_css_anim_act > : ENUM_N (css_anim_act)
{ using ENUM_N (css_anim_act) :: enum_n; };

template < > struct type_master < t_css_appearance > : ENUM_N (css_appearance)
{ using ENUM_N (css_appearance) :: enum_n; };

template < > struct type_master < t_css_atf_ky > : ENUM_N (css_atf_ky)
{ using ENUM_N (css_atf_ky) :: enum_n; };

template < > struct type_master < t_css_azimuth_e > : ENUM_N (css_azimuth_e)
{ using ENUM_N (css_azimuth_e) :: enum_n; };

template < > struct type_master < t_css_background_attachment > : ENUM_N (css_background_attachment)
{ using ENUM_N (css_background_attachment) :: enum_n; };

template < > struct type_master < t_css_background_repeat > : ENUM_N (css_background_repeat)
{ using ENUM_N (css_background_repeat) :: enum_n; };

template < > struct type_master < t_css_bespoker > : ENUM_N (css_bespoker)
{ using ENUM_N (css_bespoker) :: enum_n; };

template < > struct type_master < t_css_blend_mode > : ENUM_N (css_blend_mode)
{ using ENUM_N (css_blend_mode) :: enum_n; };

template < > struct type_master < t_css_border_style > : ENUM_N (css_border_style)
{ using ENUM_N (css_border_style) :: enum_n; };

template < > struct type_master < t_css_border_width > : ENUM_N (css_border_width)
{ using ENUM_N (css_border_width) :: enum_n; };

template < > struct type_master < t_css_box_alignself_mess > : ENUM_N (css_box_alignself_mess)
{ using ENUM_N (css_box_alignself_mess) :: enum_n; };

template < > struct type_master < t_css_box_snap > : ENUM_N (css_box_snap)
{ using ENUM_N (css_box_snap) :: enum_n; };

template < > struct type_master < t_css_break > : ENUM_N (css_break)
{ using ENUM_N (css_break) :: enum_n; };

template < > struct type_master < t_css_break_inside > : ENUM_N (css_break_inside)
{ using ENUM_N (css_break_inside) :: enum_n; };

template < > struct type_master < t_css_caret_shape > : ENUM_N (css_caret_shape)
{ using ENUM_N (css_caret_shape) :: enum_n; };

template < > struct type_master < t_css_clear > : ENUM_N (css_clear)
{ using ENUM_N (css_clear) :: enum_n; };

template < > struct type_master < t_css_composite_mode > : ENUM_N (css_composite_mode)
{ using ENUM_N (css_composite_mode) :: enum_n; };

template < > struct type_master < t_css_contain_e > : ENUM_N (css_contain_e)
{ using ENUM_N (css_contain_e) :: enum_n; };

template < > struct type_master < t_css_container_feature > : ENUM_N (css_container_feature)
{ using ENUM_N (css_container_feature) :: enum_n; };

template < > struct type_master < t_css_continue > : ENUM_N (css_continue)
{ using ENUM_N (css_continue) :: enum_n; };

template < > struct type_master < t_css_control_break > : ENUM_N (css_control_break)
{ using ENUM_N (css_control_break) :: enum_n; };

template < > struct type_master < t_css_cursor_e > : ENUM_N (css_cursor_e)
{ using ENUM_N (css_cursor_e) :: enum_n; };

template < > struct type_master < t_css_colour > : ENUM_N (css_colour)
{   static bool is_colourful () { return true; }
    using ENUM_N (css_colour) :: enum_n; };

template < > struct type_master < t_css_container_state > : ENUM_N (css_container_state)
{ using ENUM_N (css_container_state) :: enum_n; };

template < > struct type_master < t_css_content_enum > : ENUM_N (css_content_enum)
{ using ENUM_N (css_content_enum) :: enum_n; };

template < > struct type_master < t_css_content_position > : ENUM_N (css_content_position)
{ using ENUM_N (css_content_position) :: enum_n; };

template < > struct type_master < t_css_coord_box > : ENUM_N (css_coord_box)
{ using ENUM_N (css_coord_box) :: enum_n; };

template < > struct type_master < t_css_corner_shape_name > : ENUM_N (css_corner_shape_name)
{ using ENUM_N (css_corner_shape_name) :: enum_n; };

template < > struct type_master < t_css_counter_style > : ENUM_N (css_counter_style)
{ using ENUM_N (css_counter_style) :: enum_n; };

template < > struct type_master < t_css_display > : ENUM_N (css_display)
{ using ENUM_N (css_display) :: enum_n; };

template < > struct type_master < t_css_display_inside > : ENUM_N (css_display_inside)
{ using ENUM_N (css_display_inside) :: enum_n; };

template < > struct type_master < t_css_display_internal > : ENUM_N (css_display_internal)
{ using ENUM_N (css_display_internal) :: enum_n; };

template < > struct type_master < t_css_elevation_e > : ENUM_N (css_elevation_e)
{ using ENUM_N (css_elevation_e) :: enum_n; };

template < > struct type_master < t_css_ellipse_pos_e > : ENUM_N (css_ellipse_pos_e)
{ using ENUM_N (css_ellipse_pos_e) :: enum_n; };

template < > struct type_master < t_css_ellipse_pos_x_2_e > : ENUM_N (css_ellipse_pos_x_2_e)
{ using ENUM_N (css_ellipse_pos_x_2_e) :: enum_n; };

template < > struct type_master < t_css_ellipse_pos_y_2_e > : ENUM_N (css_ellipse_pos_y_2_e)
{ using ENUM_N (css_ellipse_pos_y_2_e) :: enum_n; };

template < > struct type_master < t_css_env_var_predef > : ENUM_N (css_env_var_predef)
{ using ENUM_N (css_env_var_predef) :: enum_n; };

template < > struct type_master < t_css_etee > : ENUM_N (css_etee)
{ using ENUM_N (css_etee) :: enum_n; };

template < > struct type_master < t_css_float > : ENUM_N (css_float)
{ using ENUM_N (css_float) :: enum_n; };

template < > struct type_master < t_css_fn > : ENUM_N (css_fn)
{ using ENUM_N (css_fn) :: enum_n; };

template < > struct type_master < t_css_font_display > : ENUM_N (css_font_display)
{ using ENUM_N (css_font_display) :: enum_n; };

template < > struct type_master < t_css_font_feature > : ENUM_N (css_font_feature)
{ using ENUM_N (css_font_feature) :: enum_n; };

template < > struct type_master < t_css_font_format > : ENUM_N (css_font_format)
{ using ENUM_N (css_font_format) :: enum_n; };

template < > struct type_master < t_css_font_size_adjust_e > : ENUM_N (css_font_size_adjust_e)
{ using ENUM_N (css_font_size_adjust_e) :: enum_n; };

template < > struct type_master < t_css_font_tech > : ENUM_N (css_font_tech)
{ using ENUM_N (css_font_tech) :: enum_n; };

template < > struct type_master < t_css_font_variation > : ENUM_N (css_font_variation)
{ using ENUM_N (css_font_variation) :: enum_n; };

template < > struct type_master < t_css_font_weight > : ENUM_N (css_font_weight)
{ using ENUM_N (css_font_weight) :: enum_n; };

template < > struct type_master < t_css_generic_family > : ENUM_N (css_generic_family)
{ using ENUM_N (css_generic_family) :: enum_n; };

template < > struct type_master < t_css_hll > : ENUM_N (css_hll)
{ using ENUM_N (css_hll) :: enum_n; };

template < > struct type_master < t_css_inline_bem_1 > : ENUM_N (css_inline_bem_1)
{ using ENUM_N (css_inline_bem_1) :: enum_n; };

template < > struct type_master < t_css_inline_bem_2 > : ENUM_N (css_inline_bem_2)
{ using ENUM_N (css_inline_bem_2) :: enum_n; };

template < > struct type_master < t_css_justify_content > : ENUM_N (css_justify_content)
{ using ENUM_N (css_justify_content) :: enum_n; };

template < > struct type_master < t_css_layout_box > : ENUM_N (css_layout_box)
{ using ENUM_N (css_layout_box) :: enum_n; };

template < > struct type_master < t_css_line_break > : ENUM_N (css_line_break)
{ using ENUM_N (css_line_break) :: enum_n; };

template < > struct type_master < t_css_list_style_position > : ENUM_N (css_list_style_position)
{ using ENUM_N (css_list_style_position) :: enum_n; };

template < > struct type_master < t_css_list_style_type > : ENUM_N (css_list_style_type)
{ using ENUM_N (css_list_style_type) :: enum_n; };

template < > struct type_master < t_css_mask_composite > : ENUM_N (css_mask_composite)
{ using ENUM_N (css_mask_composite) :: enum_n; };

template < > struct type_master < t_css_module > : enum_n < t_css_module, e_css_module, e_nit_macro, nm_none >
{ using enum_n < t_css_module, e_css_module, e_nit_macro, nm_none > :: enum_n; };

template < > struct type_master < t_css_navigation_keyword > : ENUM_N (css_navigation_keyword)
{ using ENUM_N (css_navigation_keyword) :: enum_n; };

template < > struct type_master < t_css_overflow > : ENUM_N (css_overflow)
{ using ENUM_N (css_overflow) :: enum_n; };

template < > struct type_master < t_css_overflow_style > : ENUM_N (css_overflow_style)
{ using ENUM_N (css_overflow_style) :: enum_n; };

template < > struct type_master < t_css_pa_left > : ENUM_N (css_pa_left)
{ using ENUM_N (css_pa_left) :: enum_n; };

template < > struct type_master < t_css_pa_top > : ENUM_N (css_pa_top)
{ using ENUM_N (css_pa_top) :: enum_n; };

template < > struct type_master < t_css_pa_block > : ENUM_N (css_pa_block)
{ using ENUM_N (css_pa_block) :: enum_n; };

template < > struct type_master < t_css_pa_inline > : ENUM_N (css_pa_inline)
{ using ENUM_N (css_pa_inline) :: enum_n; };

template < > struct type_master < t_css_pa_self_block > : ENUM_N (css_pa_self_block)
{ using ENUM_N (css_pa_self_block) :: enum_n; };

template < > struct type_master < t_css_pa_self_inline > : ENUM_N (css_pa_self_inline)
{ using ENUM_N (css_pa_self_inline) :: enum_n; };

template < > struct type_master < t_css_pa_start > : ENUM_N (css_pa_start)
{ using ENUM_N (css_pa_start) :: enum_n; };

template < > struct type_master < t_css_pa_self > : ENUM_N (css_pa_self)
{ using ENUM_N (css_pa_self) :: enum_n; };

template < > struct type_master < t_css_paint_box > : ENUM_N (css_paint_box)
{ using ENUM_N (css_paint_box) :: enum_n; };

template < > struct type_master < t_css_pause_3_e > : ENUM_N (css_pause_3_e)
{ using ENUM_N (css_pause_3_e) :: enum_n; };

template < > struct type_master < t_css_pitch_e > : ENUM_N (css_pitch_e)
{ using ENUM_N (css_pitch_e) :: enum_n; };

template < > struct type_master < t_css_position > : ENUM_N (css_position)
{ using ENUM_N (css_position) :: enum_n; };

template < > struct type_master < t_css_print_status > : ENUM_N (css_print_status)
{ using ENUM_N (css_print_status) :: enum_n; };

template < > struct type_master < t_css_property > : ENUM_N (css_property)
{ using ENUM_N (css_property) :: enum_n; };

template < > struct type_master < t_css_ray_size > : ENUM_N (css_ray_size)
{ using ENUM_N (css_ray_size) :: enum_n; };

template < > struct type_master < t_css_reading_flow > : ENUM_N (css_reading_flow)
{ using ENUM_N (css_reading_flow) :: enum_n; };

template < > struct type_master < t_css_rect > : ENUM_N (css_rect)
{ using ENUM_N (css_rect) :: enum_n; };

template < > struct type_master < t_css_rgb_xyz > : ENUM_N (css_rgb_xyz)
{ using ENUM_N (css_rgb_xyz) :: enum_n; };

template < > struct type_master < t_css_relative_size > : ENUM_N (css_relative_size)
{ using ENUM_N (css_relative_size) :: enum_n; };

template < > struct type_master < t_css_resize > : ENUM_N (css_resize)
{ using ENUM_N (css_resize) :: enum_n; };

template < > struct type_master < t_css_scroll_button > : ENUM_N (css_scroll_button)
{ using ENUM_N (css_scroll_button) :: enum_n; };

template < > struct type_master < t_css_self_position > : ENUM_N (css_self_position)
{ using ENUM_N (css_self_position) :: enum_n; };

template < > struct type_master < t_css_shape_box > : ENUM_N (css_shape_box)
{ using ENUM_N (css_shape_box) :: enum_n; };

template < > struct type_master < t_css_size_e > : ENUM_N (css_size_e)
{ using ENUM_N (css_size_e) :: enum_n; };

template < > struct type_master < t_css_sizing > : ENUM_N (css_sizing)
{ using ENUM_N (css_sizing) :: enum_n; };

template < > struct type_master < t_css_speak_as_e > : ENUM_N (css_speak_as_e)
{ using ENUM_N (css_speak_as_e) :: enum_n; };

template < > struct type_master < t_css_speech_rate_e > : ENUM_N (css_speech_rate_e)
{ using ENUM_N (css_speech_rate_e) :: enum_n; };

template < > struct type_master < t_css_ss_scroll > : ENUM_N (css_ss_scroll)
{ using ENUM_N (css_ss_scroll) :: enum_n; };

template < > struct type_master < t_css_ss_snapped > : ENUM_N (css_ss_snapped)
{ using ENUM_N (css_ss_snapped) :: enum_n; };

template < > struct type_master < t_css_ss_stuck > : ENUM_N (css_ss_stuck)
{ using ENUM_N (css_ss_stuck) :: enum_n; };

template < > struct type_master < t_css_ss_type_e > : ENUM_N (css_ss_type_e)
{ using ENUM_N (css_ss_type_e) :: enum_n; };

template < > struct type_master < t_css_statement > : ENUM_N (css_statement)
{ using ENUM_N (css_statement) :: enum_n; };

template < > struct type_master < t_css_system_e > : ENUM_N (css_system_e)
{ using ENUM_N (css_system_e) :: enum_n; };

template < > struct type_master < t_css_text_align > : ENUM_N (css_text_align)
{ using ENUM_N (css_text_align) :: enum_n; };

template < > struct type_master < t_css_text_align_all > : ENUM_N (css_text_align_all)
{ using ENUM_N (css_text_align_all) :: enum_n; };

template < > struct type_master < t_css_text_align_last > : ENUM_N (css_text_align_last)
{ using ENUM_N (css_text_align_last) :: enum_n; };

template < > struct type_master < t_css_text_autospace > : ENUM_N (css_text_autospace)
{ using ENUM_N (css_text_autospace) :: enum_n; };

template < > struct type_master < t_css_text_decoration > : ENUM_N (css_text_decoration)
{ using ENUM_N (css_text_decoration) :: enum_n; };

template < > struct type_master < t_css_textdec_skip > : ENUM_N (css_textdec_skip)
{ using ENUM_N (css_textdec_skip) :: enum_n; };

template < > struct type_master < t_css_text_justify > : ENUM_N (css_text_justify)
{ using ENUM_N (css_text_justify) :: enum_n; };

template < > struct type_master < t_css_text_transform > : ENUM_N (css_text_transform)
{ using ENUM_N (css_text_transform) :: enum_n; };

template < > struct type_master < t_css_textdec_line_e > : ENUM_N (css_textdec_line_e)
{ using ENUM_N (css_textdec_line_e) :: enum_n; };

template < > struct type_master < t_css_textdec_style > : ENUM_N (css_textdec_style)
{ using ENUM_N (css_textdec_style) :: enum_n; };

template < > struct type_master < t_css_textemph_shape > : ENUM_N (css_textemph_shape)
{ using ENUM_N (css_textemph_shape) :: enum_n; };

template < > struct type_master < t_css_text_spacing_trim > : ENUM_N (css_text_spacing_trim)
{ using ENUM_N (css_text_spacing_trim) :: enum_n; };

template < > struct type_master < t_css_touch_action > : ENUM_N (css_touch_action)
{ using ENUM_N (css_touch_action) :: enum_n; };

template < > struct type_master < t_css_trn > : ENUM_N (css_trn)
{ using ENUM_N (css_trn) :: enum_n; };

template < > struct type_master < t_css_try_tactic > : ENUM_N (css_try_tactic)
{ using ENUM_N (css_try_tactic) :: enum_n; };

template < > struct type_master < t_css_text_wrap > : ENUM_N (css_text_wrap)
{ using ENUM_N (css_text_wrap) :: enum_n; };

template < > struct type_master < t_css_text_wrap_style > : ENUM_N (css_text_wrap_style)
{ using ENUM_N (css_text_wrap_style) :: enum_n; };

template < > struct type_master < t_css_transform_box > : ENUM_N (css_transform_box)
{ using ENUM_N (css_transform_box) :: enum_n; };

template < > struct type_master < t_css_type > : ENUM_N (css_type)
{ using ENUM_N (css_type) :: enum_n; };

template < > struct type_master < t_css_user_select > : ENUM_N (css_user_select)
{ using ENUM_N (css_user_select) :: enum_n; };

template < > struct type_master < t_css_val_fn > : ENUM_N (css_val_fn)
{ using ENUM_N (css_val_fn) :: enum_n; };

template < > struct type_master < t_css_version > : ENUM_N (css_version)
{ using ENUM_N (css_version) :: enum_n; };

template < > struct type_master < t_css_vertical_align > : ENUM_N (css_vertical_align)
{ using ENUM_N (css_vertical_align) :: enum_n; };

template < > struct type_master < t_css_visual_box > : ENUM_N (css_visual_box)
{ using ENUM_N (css_visual_box) :: enum_n; };

template < > struct type_master < t_css_voice_balance_e > : ENUM_N (css_voice_balance_e)
{ using ENUM_N (css_voice_balance_e) :: enum_n; };

template < > struct type_master < t_css_volume_e > : ENUM_N (css_volume_e)
{ using ENUM_N (css_volume_e) :: enum_n; };

template < > struct type_master < t_css_whitespace > : ENUM_N (css_whitespace)
{ using ENUM_N (css_whitespace) :: enum_n; };

template < > struct type_master < t_css_wide > : ENUM_N (css_wide)
{ using ENUM_N (css_wide) :: enum_n; };

template < > struct type_master < t_css_win_shad > : ENUM_N (css_win_shad)
{ using ENUM_N (css_win_shad) :: enum_n; };

template < > struct type_master < t_css_word_break > : ENUM_N (css_word_break)
{ using ENUM_N (css_word_break) :: enum_n; };

template < > struct type_master < t_css_wrap_flow > : ENUM_N (css_wrap_flow)
{ using ENUM_N (css_wrap_flow) :: enum_n; };

template < > struct type_master < t_css_wsc > : ENUM_N (css_wsc)
{ using ENUM_N (css_wsc) :: enum_n; };

template < > struct type_master < t_css_wst > : ENUM_N (css_wst)
{ using ENUM_N (css_wst) :: enum_n; };

template < > struct type_master < t_currency > : ENUM_N (currency)
{ using ENUM_N (currency) :: enum_n; };

template < > struct type_master < t_cursor > : ENUM_N (cursor)
{ using ENUM_N (cursor) :: enum_n; };

template < > struct type_master < t_decalign > : ENUM_N (decalign)
{ using ENUM_N (decalign) :: enum_n; };

template < > struct type_master < t_dcmitype > : ENUM_N (dcmitype)
{ using ENUM_N (dcmitype) :: enum_n; };

template < > struct type_master < t_determiner > : ENUM_N (determiner)
{ using ENUM_N (determiner) :: enum_n; };

template < > struct type_master < t_dingbat > : ENUM_N (dingbat)
{ using ENUM_N (dingbat) :: enum_n; };

template < > struct type_master < t_dir > : ENUM_N (dir)
{ using ENUM_N (dir) :: enum_n; };

template < > struct type_master < t_directive > : ENUM_N (directive)
{ using ENUM_N (directive) :: enum_n; };

template < > struct type_master < t_display_align > : ENUM_N (display_align)
{ using ENUM_N (display_align) :: enum_n; };

template < > struct type_master < t_dominantbaseline > : ENUM_N (dominantbaseline)
{ using ENUM_N (dominantbaseline) :: enum_n; };

template < > struct type_master < t_enterkeyhint > : ENUM_N (enterkeyhint)
{ using ENUM_N (enterkeyhint) :: enum_n; };

template < > struct type_master < t_evt_action > : ENUM_N (evt_action)
{ using ENUM_N (evt_action) :: enum_n; };

template < > struct type_master < t_figalign > : ENUM_N (figalign)
{ using ENUM_N (figalign) :: enum_n; };

template < > struct type_master < t_filter_in > : ENUM_N (filter_in)
{ using ENUM_N (filter_in) :: enum_n; };

template < > struct type_master < t_fixedcolour > : ENUM_N (fixedcolour)
{   static bool is_colourful () { return true; }
    using ENUM_N (fixedcolour) :: enum_n; };

template < > struct type_master < t_fontname > : ENUM_N (fontname)
{ using ENUM_N (fontname) :: enum_n; };

template < > struct type_master < t_font_enum > : ENUM_N (font_enum)
{ using ENUM_N (font_enum) :: enum_n; };

template < > struct type_master < t_font_variant_2 > : ENUM_N (font_variant_2)
{ using ENUM_N (font_variant_2) :: enum_n; };

template < > struct type_master < t_font_variant_caps > : ENUM_N (font_variant_caps)
{ using ENUM_N (font_variant_caps) :: enum_n; };

template < > struct type_master < t_font_variant_east_asian > : ENUM_N (font_variant_east_asian)
{ using ENUM_N (font_variant_east_asian) :: enum_n; };

template < > struct type_master < t_font_variant_ligature > : ENUM_N (font_variant_ligature)
{ using ENUM_N (font_variant_ligature) :: enum_n; };

template < > struct type_master < t_font_variant_numeric > : ENUM_N (font_variant_numeric)
{ using ENUM_N (font_variant_numeric) :: enum_n; };

template < > struct type_master < t_formaturi > : ENUM_N (formaturi)
{ using ENUM_N (formaturi) :: enum_n; };

template < > struct type_master < t_halign > : ENUM_N (halign)
{ using ENUM_N (halign) :: enum_n; };

template < > struct type_master < t_httpequiv > : ENUM_N (httpequiv)
{ using ENUM_N (httpequiv) :: enum_n; };

template < > struct type_master < t_icalfreq > : ENUM_N (icalfreq)
{ using ENUM_N (icalfreq) :: enum_n; };

template < > struct type_master < t_image_rendering > : ENUM_N (image_rendering)
{ using ENUM_N (image_rendering) :: enum_n; };

template < > struct type_master < t_icc > : ENUM_N (icc)
{ using ENUM_N (icc) :: enum_n; };

template < > struct type_master < t_iiu > : ENUM_N (iiu)
{ using ENUM_N (iiu) :: enum_n; };

template < > struct type_master < t_indentalign > : ENUM_N (indentalign)
{ using ENUM_N (indentalign) :: enum_n; };

template < > struct type_master < t_inky > : ENUM_N (inky)
{ using ENUM_N (inky) :: enum_n; };

template < > struct type_master < t_inputmode > : ENUM_N (inputmode)
{ using ENUM_N (inputmode) :: enum_n; };

template < > struct type_master < t_inputplus > : ENUM_N (inputplus)
{ using ENUM_N (inputplus) :: enum_n; };

template < > struct type_master < t_inputtype > : ENUM_N (inputtype)
{ using ENUM_N (inputtype) :: enum_n; };

template < > struct type_master < t_inputtype3 > : ENUM_N (inputtype3)
{ using ENUM_N (inputtype3) :: enum_n; };

template < > struct type_master < t_inputtype32 > : ENUM_N (inputtype32)
{ using ENUM_N (inputtype32) :: enum_n; };

template < > struct type_master < t_inputtype4 > : ENUM_N (inputtype4)
{ using ENUM_N (inputtype4) :: enum_n; };

template < > struct type_master < t_inputtype5 > : ENUM_N (inputtype5)
{ using ENUM_N (inputtype5) :: enum_n; };

template < > struct type_master < t_jtoken > : ENUM_N (jtoken)
{ using ENUM_N (jtoken) :: enum_n; };

template < > struct type_master < t_keycode > : ENUM_N (keycode)
{ using ENUM_N (keycode) :: enum_n; };

template < > struct type_master < t_kind > : ENUM_N (kind)
{ using ENUM_N (kind) :: enum_n; };

template < > struct type_master < t_lang > : ENUM_N (lang)
{ using ENUM_N (lang) :: enum_n; };

template < > struct type_master < t_length_absolute > : ENUM_N (length_absolute)
{ using ENUM_N (length_absolute) :: enum_n; };

template < > struct type_master < t_length_relative > : ENUM_N (length_relative)
{ using ENUM_N (length_relative) :: enum_n; };

template < > struct type_master < t_linebreak > : ENUM_N (linebreak)
{ using ENUM_N (linebreak) :: enum_n; };

template < > struct type_master < t_linkparam > : ENUM_N (linkparam)
{ using ENUM_N (linkparam) :: enum_n; };

template < > struct type_master < t_listtype > : enum_n < t_listtype, e_listtype, ident_t, ns_default, sz_false >
{ using enum_n < t_listtype, e_listtype, ident_t, ns_default, sz_false > :: enum_n; };

template < > struct type_master < t_lrnialign > : ENUM_N (lrnialign)
{ using ENUM_N (lrnialign) :: enum_n; };

template < > struct type_master < t_locale > : ENUM_N (locale)
{ using ENUM_N (locale) :: enum_n; };

template < > struct type_master < t_longdivstyle > : ENUM_N (longdivstyle)
{ using ENUM_N (longdivstyle) :: enum_n; };

template < > struct type_master < t_mah > : ENUM_N (mah)
{ using ENUM_N (mah) :: enum_n; };

template < > struct type_master < t_mathalign > : ENUM_N (mathalign)
{ using ENUM_N (mathalign) :: enum_n; };

template < > struct type_master < t_math_constant > : ENUM_N (math_constant)
{ using ENUM_N (math_constant) :: enum_n; };

template < > struct type_master < t_mathlocation > : ENUM_N (mathlocation)
{ using ENUM_N (mathlocation) :: enum_n; };

template < > struct type_master < t_mathnotation > : ENUM_N (mathnotation)
{ using ENUM_N (mathnotation) :: enum_n; };

template < > struct type_master < t_mathoverflow > : ENUM_N (mathoverflow)
{ using ENUM_N (mathoverflow) :: enum_n; };

template < > struct type_master < t_mathvariant > : ENUM_N (mathvariant)
{ using ENUM_N (mathvariant) :: enum_n; };

template < > struct type_master < t_math_version > : ENUM_N (math_version)
{ using ENUM_N (math_version) :: enum_n; };

template < > struct type_master < t_matrixtype > : ENUM_N (matrixtype)
{ using ENUM_N (matrixtype) :: enum_n; };

template < > struct type_master < t_media > : ENUM_N (media)
{ using ENUM_N (media) :: enum_n; };

template < > struct type_master < t_metaname > : ENUM_N (metaname)
{ using ENUM_N (metaname) :: enum_n; };

template < > struct type_master < t_method > : ENUM_N (method)
{ using ENUM_N (method) :: enum_n; };

template < > struct type_master < t_mf_identifier > : ENUM_N (mf_identifier)
{ using ENUM_N (mf_identifier) :: enum_n; };

template < > struct type_master < t_mf_itemtype > : ENUM_N (mf_itemtype)
{ using ENUM_N (mf_itemtype) :: enum_n; };

template < > struct type_master < t_mf_listing_action > : ENUM_N (mf_listing_action)
{ using ENUM_N (mf_listing_action) :: enum_n; };

template < > struct type_master < t_mf_method > : ENUM_N (mf_method)
{ using ENUM_N (mf_method) :: enum_n; };

template < > struct type_master < t_mf_relationship > : ENUM_N (mf_relationship)
{ using ENUM_N (mf_relationship) :: enum_n; };

template < > struct type_master < t_mf_reviewtype > : ENUM_N (mf_reviewtype)
{ using ENUM_N (mf_reviewtype) :: enum_n; };

template < > struct type_master < t_mf_tel > : ENUM_N (mf_tel)
{ using ENUM_N (mf_tel) :: enum_n; };

template < > struct type_master < t_mime > : enum_n < t_mime, e_mimetype >
{ using enum_n < t_mime, e_mimetype > :: enum_n; };

template < > struct type_master < t_month_english_long > : ENUM_N (month_english_long)
{ using ENUM_N (month_english_long) :: enum_n; };

template < > struct type_master < t_month_english_short > : ENUM_N (month_english_short)
{ using ENUM_N (month_english_short) :: enum_n; };

template < > struct type_master < t_mrss_medium > : ENUM_N (mrss_medium)
{ using ENUM_N (mrss_medium) :: enum_n; };

template < > struct type_master < t_mrss_role > : ENUM_N (mrss_role)
{ using ENUM_N (mrss_role) :: enum_n; };

template < > struct type_master < t_musickey > : ENUM_N (musickey)
{ using ENUM_N (musickey) :: enum_n; };

template < > struct type_master < t_myersbriggs > : ENUM_N (myersbriggs)
{ using ENUM_N (myersbriggs) :: enum_n; };

template < > struct type_master < t_namedspace > : ENUM_N (namedspace)
{ using ENUM_N (namedspace) :: enum_n; };

template < > struct type_master < t_namespace > : ENUM_N (namespace)
{ using ENUM_N (namespace) :: enum_n; };

template < > struct type_master < t_nit_macro > : ENUM_N (nit_macro)
{ using ENUM_N (nit_macro) :: enum_n; };

template < > struct type_master < t_nit_section > : ENUM_N (nit_section)
{ using ENUM_N (nit_section) :: enum_n; };

template < > struct type_master < t_ogtype > : ENUM_N (ogtype)
{ using ENUM_N (ogtype) :: enum_n; };

template < > struct type_master < t_output_template > : ENUM_N (output_template)
{ using ENUM_N (output_template) :: enum_n; };

template < > struct type_master < t_page_orientation > : ENUM_N (page_orientation)
{ using ENUM_N (page_orientation) :: enum_n; };

template < > struct type_master < t_paintkeyword > : ENUM_N (paintkeyword)
{ using ENUM_N (paintkeyword) :: enum_n; };

template < > struct type_master < t_pam_ccv > : ENUM_N (pam_ccv)
{ using ENUM_N (pam_ccv) :: enum_n; };

template < > struct type_master < t_pcmm_status > : ENUM_N (pcmm_status)
{ using ENUM_N (pcmm_status) :: enum_n; };

template < > struct type_master < t_pointer_events > : ENUM_N (pointer_events)
{ using ENUM_N (pointer_events) :: enum_n; };

template < > struct type_master < t_pri_img_colour > : ENUM_N (pri_img_colour)
{ using ENUM_N (pri_img_colour) :: enum_n; };

template < > struct type_master < t_pri_img_technique > : ENUM_N (pri_img_technique)
{ using ENUM_N (pri_img_technique) :: enum_n; };

template < > struct type_master < t_pri_img_viewpoint > : ENUM_N (pri_img_viewpoint)
{ using ENUM_N (pri_img_viewpoint) :: enum_n; };

template < > struct type_master < t_print > : ENUM_N (print)
{ using ENUM_N (print) :: enum_n; };

template < > struct type_master < t_prism_ad_pos > : ENUM_N (prism_ad_pos)
{ using ENUM_N (prism_ad_pos) :: enum_n; };

template < > struct type_master < t_prism_ad_type > : ENUM_N (prism_ad_type)
{ using ENUM_N (prism_ad_type) :: enum_n; };

template < > struct type_master < t_prism_ag_type > : ENUM_N (prism_ag_type)
{ using ENUM_N (prism_ag_type) :: enum_n; };

template < > struct type_master < t_prism_audience_sector > : ENUM_N (prism_audience_sector)
{ using ENUM_N (prism_audience_sector) :: enum_n; };

template < > struct type_master < t_prism_ccv > : ENUM_N (prism_ccv)
{ using ENUM_N (prism_ccv) :: enum_n; };

template < > struct type_master < t_prism_class > : ENUM_N (prism_class)
{ using ENUM_N (prism_class) :: enum_n; };

template < > struct type_master < t_prism_contenttype > : ENUM_N (prism_contenttype)
{ using ENUM_N (prism_contenttype) :: enum_n; };

template < > struct type_master < t_prism_cvp > : ENUM_N (prism_cvp)
{ using ENUM_N (prism_cvp) :: enum_n; };

template < > struct type_master < t_prism_genre > : ENUM_N (prism_genre)
{ using ENUM_N (prism_genre) :: enum_n; };

template < > struct type_master < t_prism_icv > : ENUM_N (prism_icv)
{ using ENUM_N (prism_icv) :: enum_n; };

template < > struct type_master < t_prism_pasv > : ENUM_N (prism_pasv)
{ using ENUM_N (prism_pasv) :: enum_n; };

template < > struct type_master < t_prism_pcv > : ENUM_N (prism_pcv)
{ using ENUM_N (prism_pcv) :: enum_n; };

template < > struct type_master < t_prism_pfv > : ENUM_N (prism_pfv)
{ using ENUM_N (prism_pfv) :: enum_n; };

template < > struct type_master < t_prism_ptv > : ENUM_N (prism_ptv)
{ using ENUM_N (prism_ptv) :: enum_n; };

template < > struct type_master < t_prism_rcv > : ENUM_N (prism_rcv)
{ using ENUM_N (prism_rcv) :: enum_n; };

template < > struct type_master < t_prism_role > : ENUM_N (prism_role)
{ using ENUM_N (prism_role) :: enum_n; };

template < > struct type_master < t_prs_action > : ENUM_N (prs_action)
{ using ENUM_N (prs_action) :: enum_n; };

template < > struct type_master < t_quote_style > : ENUM_N (quote_style)
{ using ENUM_N (quote_style) :: enum_n; };

template < > struct type_master < t_recipe_content > : ENUM_N (recipe_content)
{ using ENUM_N (recipe_content) :: enum_n; };

template < > struct type_master < t_recipe_course > : ENUM_N (recipe_course)
{ using ENUM_N (recipe_course) :: enum_n; };

template < > struct type_master < t_recipe_cuisine > : ENUM_N (recipe_cuisine)
{ using ENUM_N (recipe_cuisine) :: enum_n; };

template < > struct type_master < t_recipe_dietary > : ENUM_N (recipe_dietary)
{ using ENUM_N (recipe_dietary) :: enum_n; };

template < > struct type_master < t_recipe_dish > : ENUM_N (recipe_dish)
{ using ENUM_N (recipe_dish) :: enum_n; };

template < > struct type_master < t_recipe_exclusion > : ENUM_N (recipe_exclusion)
{ using ENUM_N (recipe_exclusion) :: enum_n; };

template < > struct type_master < t_recipe_kit > : ENUM_N (recipe_kit)
{ using ENUM_N (recipe_kit) :: enum_n; };

template < > struct type_master < t_recipe_meal > : ENUM_N (recipe_meal)
{ using ENUM_N (recipe_meal) :: enum_n; };

template < > struct type_master < t_recipe_method > : ENUM_N (recipe_method)
{ using ENUM_N (recipe_method) :: enum_n; };

template < > struct type_master < t_recipe_source > : ENUM_N (recipe_source)
{ using ENUM_N (recipe_source) :: enum_n; };

template < > struct type_master < t_recipe_special > : ENUM_N (recipe_special)
{ using ENUM_N (recipe_special) :: enum_n; };

template < > struct type_master < t_recipe_time > : ENUM_N (recipe_time)
{ using ENUM_N (recipe_time) :: enum_n; };

template < > struct type_master < t_referrer > : ENUM_N (referrer)
{ using ENUM_N (referrer) :: enum_n; };

template < > struct type_master < t_rendering_in_tents > : ENUM_N (rendering_in_tents)
{ using ENUM_N (rendering_in_tents) :: enum_n; };

template < > struct type_master < t_report > : enum_n < t_report, e_report, e_nit_macro, nm_none >
{ using enum_n < t_report, e_report, e_nit_macro, nm_none > :: enum_n; };

template < > struct type_master < t_rfc822_zone > : ENUM_N (rfc822_zone)
{ using ENUM_N (rfc822_zone) :: enum_n; };

template < > struct type_master < t_robotic > : ENUM_N (robotic)
{ using ENUM_N (robotic) :: enum_n; };

template < > struct type_master < t_role > : enum_n < t_role, e_aria_role >
{ using enum_n < t_role, e_aria_role > :: enum_n; };

template < > struct type_master < t_rsl_disclaimer > : ENUM_N (rsl_disclaimer)
{ using ENUM_N (rsl_disclaimer) :: enum_n; };

template < > struct type_master < t_rsl_payment > : ENUM_N (rsl_payment)
{ using ENUM_N (rsl_payment) :: enum_n; };

template < > struct type_master < t_rsl_usage > : ENUM_N (rsl_usage)
{ using ENUM_N (rsl_usage) :: enum_n; };

template < > struct type_master < t_rsl_user > : ENUM_N (rsl_user)
{ using ENUM_N (rsl_user) :: enum_n; };

template < > struct type_master < t_rsl_warranty > : ENUM_N (rsl_warranty)
{ using ENUM_N (rsl_warranty) :: enum_n; };

template < > struct type_master < t_rss_version > : ENUM_N (rss_version)
{ using ENUM_N (rss_version) :: enum_n; };

template < > struct type_master < t_rules > : ENUM_N (rules)
{ using ENUM_N (rules) :: enum_n; };

template < > struct type_master < t_sandbox > : ENUM_N (sandbox)
{ using ENUM_N (sandbox) :: enum_n; };

template < > struct type_master < t_scei > : ENUM_N (scei)
{ using ENUM_N (scei) :: enum_n; };

template < > struct type_master < t_security > : ENUM_N (security)
{ using ENUM_N (security) :: enum_n; };

template < > struct type_master < t_severity > : ENUM_N (severity)
{ using ENUM_N (severity) :: enum_n; };

template < > struct type_master < t_shadow > : ENUM_N (shadow)
{ using ENUM_N (shadow) :: enum_n; };

template < > struct type_master < t_shape7 > : ENUM_N (shape7)
{ using ENUM_N (shape7) :: enum_n; };

template < > struct type_master < t_sgml > : ENUM_N (sgml)
{ using ENUM_N (sgml) :: enum_n; };

template < > struct type_master < t_shape_rendering > : ENUM_N (shape_rendering)
{ using ENUM_N (shape_rendering) :: enum_n; };

template < > struct type_master < t_css_slider_orientation > : ENUM_N (css_slider_orientation)
{ using ENUM_N (css_slider_orientation) :: enum_n; };

template < > struct type_master < t_smei > : ENUM_N (smei)
{ using ENUM_N (smei) :: enum_n; };

template < > struct type_master < t_speculationrules > : ENUM_N (speculationrules)
{ using ENUM_N (speculationrules) :: enum_n; };

template < > struct type_master < t_step_position > : ENUM_N (step_position)
{ using ENUM_N (step_position) :: enum_n; };

template < > struct type_master < t_ssi > : ENUM_N (ssi)
{ using ENUM_N (ssi) :: enum_n; };

template < > struct type_master < t_ssi_comparison > : ENUM_N (ssi_comparison)
{ using ENUM_N (ssi_comparison) :: enum_n; };

template < > struct type_master < t_ssi_config > : ENUM_N (ssi_config)
{ using ENUM_N (ssi_config) :: enum_n; };

template < > struct type_master < t_ssi_encoding > : ENUM_N (ssi_encoding)
{ using ENUM_N (ssi_encoding) :: enum_n; };

template < > struct type_master < t_ssi_env > : ENUM_N (ssi_env)
{ using ENUM_N (ssi_env) :: enum_n; };

template < > struct type_master < t_stress > : ENUM_N (stress)
{ using ENUM_N (stress) :: enum_n; };

template < > struct type_master < t_supports > : ENUM_N (supports)
{ using ENUM_N (supports) :: enum_n; };

template < > struct type_master < t_svg_align > : ENUM_N (svg_align)
{ using ENUM_N (svg_align) :: enum_n; };

template < > struct type_master < t_svg_display > : ENUM_N (svg_display)
{ using ENUM_N (svg_display) :: enum_n; };

template < > struct type_master < t_svg_feature > : ENUM_N (svg_feature)
{ using ENUM_N (svg_feature) :: enum_n; };

template < > struct type_master < t_svg_fontstretch > : ENUM_N (svg_fontstretch)
{ using ENUM_N (svg_fontstretch) :: enum_n; };

template < > struct type_master < t_svg_fontstretch_ff > : ENUM_N (svg_fontstretch_ff)
{ using ENUM_N (svg_fontstretch_ff) :: enum_n; };

template < > struct type_master < t_svg_fontstyle > : ENUM_N (svg_fontstyle)
{ using ENUM_N (svg_fontstyle) :: enum_n; };

template < > struct type_master < t_svg_fontweight > : ENUM_N (svg_fontweight)
{ using ENUM_N (svg_fontweight) :: enum_n; };

template < > struct type_master < t_svg_fontweight_ff > : ENUM_N (svg_fontweight_ff)
{ using ENUM_N (svg_fontweight_ff) :: enum_n; };

template < > struct type_master < t_svg_mode > : ENUM_N (svg_mode)
{ using ENUM_N (svg_mode) :: enum_n; };

template < > struct type_master < t_svg_overflow > : ENUM_N (svg_overflow)
{ using ENUM_N (svg_overflow) :: enum_n; };

template < > struct type_master < t_svg_rendering_intent > : ENUM_N (svg_rendering_intent)
{ using ENUM_N (svg_rendering_intent) :: enum_n; };

template < > struct type_master < t_svg_type > : ENUM_N (svg_type)
{ using ENUM_N (svg_type) :: enum_n; };

template < > struct type_master < t_svg_version > : ENUM_N (svg_version)
{ using ENUM_N (svg_version) :: enum_n; };

template < > struct type_master < t_svg_version_grand > : ENUM_N (svg_version_grand)
{ using ENUM_N (svg_version_grand) :: enum_n; };

template < > struct type_master < t_tableframe > : ENUM_N (tableframe)
{ using ENUM_N (tableframe) :: enum_n; };

template < > struct type_master < t_tblri > : ENUM_N (tblri)
{ using ENUM_N (tblri) :: enum_n; };

template < > struct type_master < t_text_decoration > : ENUM_N (text_decoration)
{ using ENUM_N (text_decoration) :: enum_n; };

template < > struct type_master < t_text_rendering > : ENUM_N (text_rendering)
{ using ENUM_N (text_rendering) :: enum_n; };

template < > struct type_master < t_tld > : ENUM_N (tld)
{ using ENUM_N (tld) :: enum_n; };

template < > struct type_master < t_transform_anim > : ENUM_N (transform_anim)
{ using ENUM_N (transform_anim) :: enum_n; };

template < > struct type_master < t_transformbehaviour > : ENUM_N (transformbehaviour)
{ using ENUM_N (transformbehaviour) :: enum_n; };

template < > struct type_master < t_transform_fn > : ENUM_N (transform_fn)
{ using ENUM_N (transform_fn) :: enum_n; };

template < > struct type_master < t_turbulence_type > : ENUM_N (turbulence_type)
{ using ENUM_N (turbulence_type) :: enum_n; };

template < > struct type_master < t_unit > : ENUM_N (unit)
{ using ENUM_N (unit) :: enum_n; };

template < > struct type_master < t_unit_abs_len > : ENUM_N (unit_abs_len)
{ using ENUM_N (unit_abs_len) :: enum_n; };

template < > struct type_master < t_unit_angle > : ENUM_N (unit_angle)
{ using ENUM_N (unit_angle) :: enum_n; };

template < > struct type_master < t_unit_freq > : ENUM_N (unit_freq)
{ using ENUM_N (unit_freq) :: enum_n; };

template < > struct type_master < t_unit_rel_len > : ENUM_N (unit_rel_len)
{ using ENUM_N (unit_rel_len) :: enum_n; };

template < > struct type_master < t_unit_res > : ENUM_N (unit_res)
{ using ENUM_N (unit_res) :: enum_n; };

template < > struct type_master < t_unit_time > : ENUM_N (unit_time)
{ using ENUM_N (unit_time) :: enum_n; };

template < > struct type_master < t_unicode_bidi > : ENUM_N (unicode_bidi)
{ using ENUM_N (unicode_bidi) :: enum_n; };

template < > struct type_master < t_url_temp_exp > : ENUM_N (url_temp_exp)
{ using ENUM_N (url_temp_exp) :: enum_n; };

template < > struct type_master < t_vctelecomms > : ENUM_N (vctelecomms)
{ using ENUM_N (vctelecomms) :: enum_n; };

template < > struct type_master < t_vector_effect_2 > : ENUM_N (vector_effect_2)
{ using ENUM_N (vector_effect_2) :: enum_n; };

template < > struct type_master < t_vertical_align_enum > : ENUM_N (vertical_align_enum)
{ using ENUM_N (vertical_align_enum) :: enum_n; };

template < > struct type_master < t_vgender > : ENUM_N (vgender)
{ using ENUM_N (vgender) :: enum_n; };

template < > struct type_master < t_vrel > : ENUM_N (vrel)
{ using ENUM_N (vrel) :: enum_n; };

template < > struct type_master < t_vtt_token > : enum_n < t_vtt_token, e_vtt_token, ident_t, ns_default, sz_false >
{ using enum_n < t_vtt_token, e_vtt_token, ident_t, ns_default, sz_false > :: enum_n; };

template < > struct type_master < t_weekday_english_long > : ENUM_N (weekday_english_long)
{ using ENUM_N (weekday_english_long) :: enum_n; };

template < > struct type_master < t_weekday_english_short > : ENUM_N (weekday_english_short)
{ using ENUM_N (weekday_english_short) :: enum_n; };

template < > struct type_master < t_whitespace > : ENUM_N (whitespace)
{ using ENUM_N (whitespace) :: enum_n; };

template < > struct type_master < t_writingmode > : ENUM_N (writingmode)
{ using ENUM_N (writingmode) :: enum_n; };

template < > struct type_master < t_xmlns > : ENUM_N (xmlns)
{ using ENUM_N (xmlns) :: enum_n; };

template < > struct type_master < t_xmpdm_audio_channel > : ENUM_N (xmpdm_audio_channel)
{ using ENUM_N (xmpdm_audio_channel) :: enum_n; };

template < > struct type_master < t_xmpdm_audio_sample > : ENUM_N (xmpdm_audio_sample)
{ using ENUM_N (xmpdm_audio_sample) :: enum_n; };

template < > struct type_master < t_xmpdm_camera_angle > : ENUM_N (xmpdm_camera_angle)
{ using ENUM_N (xmpdm_camera_angle) :: enum_n; };

template < > struct type_master < t_xmpdm_camera_move > : ENUM_N (xmpdm_camera_move)
{ using ENUM_N (xmpdm_camera_move) :: enum_n; };

template < > struct type_master < t_xmpdm_pulldown > : ENUM_N (xmpdm_pulldown)
{ using ENUM_N (xmpdm_pulldown) :: enum_n; };

template < > struct type_master < t_xmpdm_shotsize > : ENUM_N (xmpdm_shotsize)
{ using ENUM_N (xmpdm_shotsize) :: enum_n; };

template < > struct type_master < t_xmpdm_stretchmode > : ENUM_N (xmpdm_stretchmode)
{ using ENUM_N (xmpdm_stretchmode) :: enum_n; };

template < > struct type_master < t_xmpdm_time_format > : ENUM_N (xmpdm_time_format)
{ using ENUM_N (xmpdm_time_format) :: enum_n; };

template < > struct type_master < t_xmpdm_time_signature > : ENUM_N (xmpdm_time_signature)
{ using ENUM_N (xmpdm_time_signature) :: enum_n; };

template < > struct type_master < t_xmpdm_video_pixeldepth > : ENUM_N (xmpdm_video_pixeldepth)
{ using ENUM_N (xmpdm_video_pixeldepth) :: enum_n; };

template < > struct type_master < t_crs_whitebalance > : ENUM_N (crs_whitebalance)
{ using ENUM_N (crs_whitebalance) :: enum_n; };

#undef ENUM_N
