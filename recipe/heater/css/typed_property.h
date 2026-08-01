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
#include "type/type.h"
#include "css/arguments.h"
#include "css/flags.h"
#include "css/value.h"

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26440)
#endif // _MSC_VER

struct property_base
{   DEFAULT_CONSTRUCTORS_VIRTUAL_DESTRUCTOR (property_base);
    virtual void set_value (arguments& , const int , const int , nitpick& , const ::std::string& ) { }
    virtual e_css_property get () const { return ec_unknown; }
    virtual bool empty () const noexcept { return true; }
    virtual bool good () const noexcept { return false; }
    virtual bool bad () const noexcept { return true; }
    virtual bool invalid () const noexcept { return true; }
    virtual bool invalid_id (arguments& , nitpick& ) const { return true; }
    virtual void verify (nitpick& , const elem& ) { }
    virtual void validate (arguments& ) { }
    virtual void accumulate (stats_t* , const element_bitset& ) const { }
    virtual void shadow (::std::stringstream& , arguments&, element* ) { }
    virtual int fin () const noexcept { return -1; }
    virtual ::std::string naam () const { return ::std::string (); }
    virtual ::std::string rpt () const { return ::std::string (); } };

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26435)
#endif // _MSC_VER

bool examine_custom_property (arguments& args, nitpick& nits, const int from, const int to);
bool check_constants (arguments& args, nitpick& nits, const int i);
bool call_fn (arguments& args, nitpick& nits, int& i, const int to, bool& res, e_css_val_fn& e, bool& params);
bool test_cascade (const arguments& args, const ::std::string& s, e_iiu& iiu);

template < e_type TYPE, e_css_property IDENTITY > struct typed_property : public property_base, public type_master < TYPE >
{   typedef type_master < TYPE > base_type;
    e_iiu iiu_ = iiu_none;
    int fin_ = -1;
    bool ok_ = false;
    ::std::string s_;
    static ::std::string name () { return type_master < t_css_property > :: name (IDENTITY); }
    virtual ::std::string naam () const override { return name (); }
    CONSTEXPR static e_css_property whoami () { return IDENTITY; }
    CONSTEXPR static e_type whatami () { return TYPE; }
    virtual e_css_property get () const override { return whoami (); }
    virtual bool empty () const noexcept override { return type_master < TYPE > :: empty (); }
    virtual bool good () const noexcept override { return type_master < TYPE > :: good (); }
    virtual bool bad () const noexcept override { return type_master < TYPE > :: bad (); }
    virtual bool invalid () const noexcept override { return type_master < TYPE > :: invalid (); }
    virtual int fin () const noexcept override { return fin_; } 
    static bool check_fn (arguments& args, int& start, const int to, nitpick& nits, const bool ok)
    {   bool maybefn = false, res = false;
        e_css_val_fn e = cvf_none;
        int bk = 0, fns = 0, bro = 0;
        for (auto i = start ; (i > 0) && ((i <= to) || (to < 0)); i = next_non_whitespace (args.t_, i, to))
            switch (args.t_.at (i).t_)
            {   case ct_keyword :
                case ct_identifier :
                    if ((bk == 0) && (! check_constants (args, nits, i))) 
                    {   nitpick nuts;
                        type_master < t_css_val_fn > cvf;
                        const ::std::string& naam (args.t_.at (i).val_);
                        cvf.set_value (nuts, args.v_, naam);
                        if (cvf.good () && (e != cvf_none))
                        {   if ((cvf.flags () & CF_NO_PARAMS) == CF_NO_PARAMS)
                            {   if (! context.css_module (c_easing_function))
                                    nits.pick (nit_css_ease, ed_css_ease, "", es_error, ec_css, quote (cvf.name ()), " requires CSS Easing Functions");
                                nits.merge (nuts);
                                args.use (cic_fn_name, naam);
                                res = true;
                                continue; } }
                        fns = i; }
                    break;
                case ct_round_brac :
                    if (bk == 0)
                    {   bro = i+1;
                        maybefn = fns > 0; }
                    ++bk;
                    break;
                case ct_round_ket :
                    if (--bk < 0) bk = 0;
                    if ((bk == 0) && (fns > 0) && maybefn)
                    {   PRESUME ((args.t_.at (fns).t_ == ct_keyword) || (args.t_.at (fns).t_ == ct_identifier), __FILE__, __LINE__)
                        nitpick nuts;
                        bool params = false;
                        const ::std::string& s = args.t_.at (fns).val_;
                        res = true;
                        if (context.html_ver ().any_ext2 (H2_CSS_CUSTOM) && (s.length () >= 2) && (s.at (0) == '-') && (s.at (1) == '-') && args.has (cic_fn_name, s))
                            args.use (cic_fn_name, s);
                        else if (! call_fn (args, nuts, fns, i, res, e, params))
                        {   if (! ok)
                            {   nits.merge (nuts);
                                test_value < TYPE > (nits, args.v_, s); } }
                        else if (e != cvf_none)
                        {   args.use (cic_fn_name, s);
                            if (ok && ((! params) || listed < cvf_url, cvf_colour, cvf_hsl, cvf_hsla, cvf_hwb, cvf_lab, cvf_lch, cvf_oklab, cvf_oklch, cvf_rgb, cvf_rgba > :: yes (e))) return true;
                            nits.merge (nuts);
                            start = i = test_value_fns (args, fns, i, nits, TYPE, e, IDENTITY); }
                        if ((bro > start) && (bro < i-1))
                            check_fn (args, bro, i-1, nits, ok);
                        maybefn = false;
                        fns = bro = 0; }
                    break;
                default :
                    break; }
        return res; }
    virtual void verify (nitpick& nits, const elem& e) override
    {   if ((iiu_ == iiu_none) && ! base_type :: fn ())
            type_master < TYPE > :: verify_attribute (nits, context.html_ver (), e, nullptr, name ()); }
    void verify_attribute (nitpick& nits, const html_version& v, const elem& e, element* ep, const ::std::string& s)
    {   if ((iiu_ == iiu_none) && ! base_type :: fn ())
            type_master < TYPE > :: verify_attribute (nits, v, e, ep, s); }
    virtual void validate (arguments& args) override
    {   if ((iiu_ == iiu_none) && ! base_type :: fn ())
        {   type_master < TYPE > :: validate ();
            type_master < TYPE > :: argue (args.t_.at (0).nits_, &args); } }
    virtual void accumulate (stats_t* s, const element_bitset& e) const override
    {   if (iiu_ == iiu_none)
            type_master < TYPE > :: accumulate (s, e); }
    ::std::string iiu () const
    {   switch (iiu_)
        {   case iiu_if : return "if";
            case iiu_inherit : return "inherit";
            case iiu_initial : return "initial";
            case iiu_moz_initial : return "-moz-initial";
            case iiu_revert : return "revert";
            case iiu_revert_layer : return "revert-layer";
            case iiu_revert_rule : return "revert-rule";
            case iiu_unset : return "unset";
            case iiu_fn : return "@function";
            default : return ""; } }
    virtual void shadow (::std::stringstream& ss, arguments& args, element* e) override
    {   if (iiu_ == iiu_none)
            type_master < TYPE > :: shadow (ss, args.v_, e);
        else ss << iiu (); }
    int set_value_ex (arguments& args, const int start, const int to, nitpick& nits, const ::std::string& s)
    {   nitpick nuts, nets;
        if (! args.v_.is_css_compatible (type_master < t_css_property > :: first_version (IDENTITY)))
        {   nits.pick (nit_css_version, es_error, ec_css, name (), " requires CSS ", type_master < t_css_property > :: first_version (IDENTITY).long_css_version_name ());
            base_type :: status (s_invalid); }
        else
        {   if (s.length () >= 3)
            {   PRESUME ((start > 0) && (start < GSL_NARROW_CAST < int > (args.t_.size ())), __FILE__, __LINE__);
                if ((args.t_.at (start).t_ == ct_keyword) || (args.t_.at (start).t_ == ct_identifier))
                    if (test_cascade (args, s, iiu_))
                    {   base_type :: status (s_good);
                        return start+1; } }
            type_master < TYPE > :: set_value (nuts, args.v_, s);
            ok_ = type_master < TYPE > :: good ();
            if (ok_)
            {   s_ = s;
                const html_version f (type_master < TYPE > :: first (type_master < TYPE > :: get_int ()));
                f.check_status (nits, name ());
                if (! args.v_.is_css_compatible (f))
                {   nits.pick (nit_css_version, es_error, ec_css, quote (s), " requires CSS ", f.long_css_version_name ());
                    base_type :: status (s_invalid);
                    ok_ = false; }
                else nits.merge (nuts); }
            int i = start;
            if ((args.st_ == nullptr) || (args.cs () != css_font_face))
                if (check_fn (args, i, to, nits, ok_))
                {   base_type :: status (s_good);
                    base_type :: fn (true);
                    return i; }
            if (! ok_) nits.merge (nuts); }
        return start; }
    virtual bool invalid_id (arguments& args, nitpick& nits) const override
    {   if (! ok_) return true;
        nitpick nuts;
        type_master < TYPE > pt;
        pt.set_value (nuts, args.v_, s_);
        ids_t i;
        return pt.invalid_id (nits, args.v_, i, args.get_document ()); }
    virtual void set_value (arguments& args, const int start, const int to, nitpick& nits, const ::std::string& s) override
    {   fin_ = set_value_ex (args, start, to, nits, s); }
    virtual ::std::string rpt () const override
    {   const ::std::string res (name () + ": ");
        if (iiu_ == iiu_none) return res + type_master < TYPE > :: get_string ();
        return res + iiu (); } };

template < > inline void typed_property < t_css_anchor_none, ec_anchor_name > :: set_value (arguments& args, const int start, const int to, nitpick& nits, const ::std::string& s)
{   void validate_anchor_id (const ::std::string& s, arguments& args);
    fin_ = set_value_ex (args, start, to, nits, s);
    if (ok_) validate_anchor_id (get_string (), args); }

template < > inline void typed_property < t_css_anim_base, ec_animation_name > :: validate (arguments& args)
{   void validate_animation_name (type_master < t_css_anim_base >& cab, arguments& args);
    if (iiu_ == iiu_none) validate_animation_name (*this, args); }

template < > inline void typed_property < t_css_counter_style_name, ec_system > :: validate (arguments& args)
{   void validate_counter_style_name (type_master < t_css_counter_style_name >& cab, arguments& args);
    validate_counter_style_name (*this, args); }

template < > inline void typed_property < t_css_palette, ec_font_palette > :: validate (arguments& args)
{   void validate_palette (type_master < t_css_palette >& cab, arguments& args);
    validate_palette (*this, args); }

template < > inline void typed_property < t_css_font_size_4, ec_font_size > :: set_value (arguments& args, const int start, const int to, nitpick& nits, const ::std::string& s)
{   if ((args.v_.css_version () == css_2_0) && (args.cs () == css_font_face))
    {   fin_ = to; return; }
    fin_ = set_value_ex (args, start, to, nits, s); }

typedef ::std::shared_ptr < property_base > property_v_ptr;
property_v_ptr make_property_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_property_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_counter_style_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_counter_style_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_descriptor_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_descriptor_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_custard_prop_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_custard_prop_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_custard_sel_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_custard_sel_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_feature_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_feature_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_function_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_function_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_margin_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_margin_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_page_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_page_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_palette_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_palette_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_position_try_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_position_try_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_route_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_route_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_viewport_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_viewport_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);
property_v_ptr make_view_transition_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const e_token t);
property_v_ptr make_view_transition_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const e_token t);

#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
