/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
    virtual void verify (nitpick& , const elem& ) { }
    virtual void validate (arguments& ) { }
    virtual void accumulate (stats_t* , const element_bitset& ) const { }
    virtual void shadow (::std::stringstream& , arguments&, element* ) { }
    virtual int fin () const noexcept { return -1; }
    virtual ::std::string rpt () const { return ::std::string (); } };

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26435)
#endif // _MSC_VER

bool examine_custom_property (arguments& args, nitpick& nits, const int from, const int to);
bool check_constants (arguments& args, nitpick& nits, const int i);
bool call_fn (arguments& args, nitpick& nits, int& i, const int to, bool& res, e_css_val_fn& e);
bool test_cascade (const ::std::string& s, e_iiu& iiu);

template < e_type TYPE, e_css_property IDENTITY > struct typed_property : public property_base, public type_master < TYPE >
{   typedef type_master < TYPE > base_type;
    e_iiu iiu_ = iiu_none;
    int fin_ = -1;
    static ::std::string name () { return type_master < t_css_property > :: name (IDENTITY); }
    CONSTEXPR static e_css_property whoami () { return IDENTITY; }
    CONSTEXPR static e_type whatami () { return TYPE; }
    virtual e_css_property get () const override { return whoami (); }
    virtual bool empty () const noexcept override { return type_master < TYPE > :: empty (); }
    virtual bool good () const noexcept override { return type_master < TYPE > :: good (); }
    virtual bool bad () const noexcept override { return type_master < TYPE > :: bad (); }
    virtual bool invalid () const noexcept override { return type_master < TYPE > :: invalid (); }
    virtual int fin () const noexcept override { return fin_; } 
    static bool check_fn (arguments& args, int& start, const int to, nitpick& nits, const bool ok)
    {   bool res = ok;
        e_css_val_fn e = cvf_none;
        for (auto i = start ; (i > 0) && ((i < to) || (to < 0)); i = next_non_whitespace (args.t_, i, to))
            if ((args.t_.at (i).t_ == ct_keyword) || (args.t_.at (i).t_ == ct_identifier))
                if (! check_constants (args, nits, i))
                {   nitpick nuts;
                    if (! call_fn (args, nuts, i, to, res, e))
                    {   if (! ok)
                        {   nits.merge (nuts);
                            test_value < TYPE > (nits, args.v_, args.t_.at (i).val_); } }
                    else if (e != cvf_none)
                    {   if (ok && listed < cvf_url, cvf_colour, cvf_hsl, cvf_hsla, cvf_hwb, cvf_lab, cvf_lch, cvf_oklab, cvf_oklch, cvf_rgb, cvf_rgba > :: yes (e)) return res;
                        nits.merge (nuts);
                        start = i = test_value_fns (args, i, to, nits, TYPE, e, IDENTITY); } }
        return res; }
    virtual void verify (nitpick& nits, const elem& e) override
    {   if (iiu_ == iiu_none) type_master < TYPE > :: verify_attribute (nits, context.html_ver (), e, nullptr, name ()); }
    virtual void validate (arguments& ) override
    {   if (iiu_ == iiu_none) type_master < TYPE > :: validate (); }
    virtual void accumulate (stats_t* s, const element_bitset& e) const override
    {   if (iiu_ == iiu_none) type_master < TYPE > :: accumulate (s, e); }
    ::std::string iiu () const
    {   switch (iiu_)
        {   case iiu_inherit : return "inherit";
            case iiu_initial : return "initial";
            case iiu_revert : return "revert";
            case iiu_revert_layer : return "revert-layer";
            case iiu_unset : return "unset";
            default : return ""; } }
    virtual void shadow (::std::stringstream& ss, arguments& args, element* e) override
    {   if (iiu_ == iiu_none) type_master < TYPE > ::shadow (ss, args.v_, e);
        else ss << iiu (); }
    int set_value_ex (arguments& args, const int start, const int to, nitpick& nits, const ::std::string& s)
    {   nitpick nuts, nets;
        type_master < TYPE > :: set_value (nuts, args.v_, s);
        const bool ok = type_master < TYPE> :: good ();
        if (ok) nits.merge (nuts);
        else if (s.length () >= 3)
        {   PRESUME ((start > 0) && (start < GSL_NARROW_CAST < int > (args.t_.size ())), __FILE__, __LINE__);
            if ((args.t_.at (start).t_ == ct_keyword) || (args.t_.at (start).t_ == ct_identifier))
                if (test_cascade (s, iiu_))
                {   base_type :: status (s_good);
                    return start; } }
        int i = start;
        if (check_fn (args, i, to, nits, ok))
        {   base_type :: status (s_good);
            return i; }
        if (! ok) nits.merge (nuts);
        return start; }
    virtual void set_value (arguments& args, const int start, const int to, nitpick& nits, const ::std::string& s) override
    {   fin_ = set_value_ex (args, start, to, nits, s); }
    virtual ::std::string rpt () const override
    {   const ::std::string res (name () + ": ");
        if (iiu_ == iiu_none) return res + type_master < TYPE > :: get_string ();
        return res + iiu (); } };

template < > inline void typed_property < t_css_anim_base, ec_animation_name > :: validate (arguments& args)
{   void validate_animation_name (type_master < t_css_anim_base >& cab, arguments& args);
    if (iiu_ == iiu_none) validate_animation_name (*this, args); }

typedef ::std::shared_ptr < property_base > property_v_ptr;
property_v_ptr make_property_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const css_token t);
property_v_ptr make_property_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const css_token t);

#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
