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

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26440)
#endif // _MSC_VER

struct property_base
{   DEFAULT_CONSTRUCTORS_VIRTUAL_DESTRUCTOR (property_base);
    virtual void set_value (arguments& , const int , const int , nitpick& , const ::std::string& ) { }
    virtual e_css_property get () const { return ec_unknown; }
    virtual void verify (nitpick& nits, const elem& e) { }
    virtual void validate (arguments& ) { }
    virtual void accumulate (stats_t* , const element_bitset& ) const { }
    virtual void shadow (::std::stringstream& , arguments&, element* ) { }
    virtual ::std::string rpt () const { return ::std::string (); } };

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26435)
#endif // _MSC_VER

bool examine_custom_property (arguments& args, nitpick& nits, const int from, const int to);
int check_formula (arguments& args, const int start, const int to, nitpick& nits, const e_css_val_fn c, const bool percent);

//template < e_type TYPE, e_css_property IDENTITY, e_css_val_fn CALC > struct formulaic
//{   static int check (arguments& , const int i, const int , nitpick& )
//    {    return i; } };

//template < e_type TYPE, e_css_property IDENTITY > struct formulaic < TYPE, IDENTITY, cvf_calc >
//{   static int check (arguments& args, const int start, const int to, nitpick& nits)
//    {   return check_formula (args, start, to, nits, cvf_calc, true); } }; 

template < e_type TYPE, e_css_property IDENTITY, e_css_val_fn FN = cvf_none > struct typed_property : public property_base, public type_master < TYPE >
{   typedef type_master < TYPE > base_type;
    typedef enum { iiu_none, iiu_inherit, iiu_initial, iiu_revert, iiu_revert_layer, iiu_unset } t_iiu;
    t_iiu iiu_ = iiu_none;
    static ::std::string name () { return type_master < t_css_property > :: name (IDENTITY); }
    CONSTEXPR static e_css_property whoami () { return IDENTITY; }
    CONSTEXPR static e_type whatami () { return TYPE; }
    virtual e_css_property get () const override { return whoami (); }
    bool empty () const noexcept { return type_master < TYPE > :: empty (); }
    bool good () const noexcept { return type_master < TYPE > :: good (); }
    bool bad () const noexcept { return type_master < TYPE > :: bad (); }
    bool invalid () const noexcept { return type_master < TYPE > :: invalid (); }
    bool check_calc (arguments& args, const int start, const int to, nitpick& nits)
    {    return check_formula (args, start, to, nits, FN, false); }
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
    virtual void set_value (arguments& args, const int start, const int to, nitpick& nits, const ::std::string& s) override
    {   if (s.length () >= 3)
        {   PRESUME ((start > 0) && (start < GSL_NARROW_CAST < int > (args.t_.size ())), __FILE__, __LINE__);
            if ((args.t_.at (start).t_ == ct_keyword) || (args.t_.at (start).t_ == ct_identifier))
                if (compare_no_case (args.t_.at (start).val_, "var"))
                {   const int b = next_non_whitespace (args.t_, start, to);
                    if ((b > 0) && (args.t_.at (b).t_ == ct_round_brac))
                    {   if (context.css_custom () != 3)
                            nits.pick (nit_css_custom, es_error, ec_css, "'var (...)' requires CSS Custom");
                        else if (examine_custom_property (args, nits, next_non_whitespace (args.t_, b, to), to))
                        {   type_master < TYPE > :: status (s_good);
                            return; }
                        type_master < TYPE > :: status (s_invalid);
                        return; } }
            switch (context.css_cascade ())
            {   case 6 :
                case 5 :
                    switch (s.at (0))
                    {   case 'r' :
                        case 'R' :
                            if (compare_no_case (s, "revert-layer"))
                                {   base_type :: status (s_good);
                                    iiu_ = iiu_revert;
                                    return; } }
                    FALLTHROUGH;   
                case 4 :
                    switch (s.at (0))
                    {   case 'r' :
                        case 'R' :
                            if (compare_no_case (s, "revert"))
                                {   base_type :: status (s_good);
                                    iiu_ = iiu_revert;
                                    return; } }
                    FALLTHROUGH;   
                case 3 :
                    switch (s.at (0))
                    {   case 'i' :
                        case 'I' :
                            if (s.length () == 7)
                                if (compare_no_case (s, "inherit"))
                                {   base_type :: status (s_good);
                                    iiu_ = iiu_inherit;
                                    return; }
                                if (compare_no_case (s, "initial"))
                                {   base_type :: status (s_good);
                                    iiu_ = iiu_initial;
                                    return; }
                            break;
                        case 'u' :
                        case 'U' :
                            if (compare_no_case (s, "unset"))
                            {   base_type :: status (s_good);
                                iiu_ = iiu_unset;
                                return; } }
                    break;
                default :
                    PRESUME (context.css_version () < css_3, __FILE__, __LINE__);
                    if (context.css_version () != css_1)
                        if (compare_no_case (s, "inherit"))
                        {   base_type :: status (s_good);
                            iiu_ = iiu_inherit;
                            return; }
                    break; }
            for (auto i = start ; (i > 0) && (i < to); i = next_non_whitespace (args.t_, i, to))
                if ((args.t_.at (i).t_ == ct_keyword) || (args.t_.at (i).t_ == ct_identifier))
                {   nitpick nets, nuts;
                    if (test_value < t_css_val_con > (nets, args.v_, args.t_.at (i).val_))
                    {   nits.merge (nuts);
                        if (args.v_.css_value () < 4)
                            nits.pick (nit_css_value, ed_css_value_4, "10.7 Numeric Constants", es_error, ec_css,
                                quote (args.t_.at (i).val_), " requires CSS Values 4");
                        continue; }
                    type_master < t_css_val_fn > cvf;
                    cvf.set_value (nuts, args.v_, args.t_.at (i).val_);
                    if (cvf.good ())
                    {   nits.merge (nuts);
                        switch (context.css_value ())
                        {   case 4 :
                                i = check_formula (args, i, to, nits, cvf.get (), false);
                                break;
                            case 3 :
                                if (cvf.get () == cvf_calc) i = check_formula (args, i, to, nits, cvf_calc, false);
                                else nits.pick (nit_css_value, es_error, ec_css, quote (args.t_.at (i).val_), " requires CSS Values 4");
                                break;
                            default :
                                nits.pick (nit_css_value, es_error, ec_css, quote (args.t_.at (i).val_), " requires CSS Values");
                                break; }
                        continue; } } }
        type_master < TYPE > :: set_value (nits, context.html_ver (), s); }
    virtual ::std::string rpt () const override
    {   const ::std::string res (name () + ": ");
        if (iiu_ == iiu_none) return res + type_master < TYPE > :: get_string ();
        return res + iiu (); } };

typedef ::std::shared_ptr < property_base > property_v_ptr;
property_v_ptr make_property_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const css_token t);

#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
