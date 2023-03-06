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

#include "main/standard.h"
#include "css/decoration.h"
#include "type/type.h"

void decoration::parse (arguments& args, const int from, const int to)
{   PRESUME ((from <= to) || (to < 0), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST < int > (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME ((to < len) || (to < 0), __FILE__, __LINE__);
    int b = first_non_whitespace (args.t_, from, to);
    if (b == -1) return;
    nitpick& nits = args.t_.at (b).nits_;
    switch (args.t_.at (b).t_)
    {   case ct_square_brac :
            if (args.t_.at (from).child_ < 0)
                nits.pick (nit_selector, ed_css_20, "5 Selectors", es_error, ec_css, ": [...] is incomplete");
            else sparkle_ = css_attribute (args, args.t_.at (from).child_);
            break;
        case ct_dot :
            b = next_non_whitespace (args.t_, b, to);
            if ((b < 0) || ((args.t_.at (b).t_ != ct_keyword) && (args.t_.at (b).t_ != ct_identifier)))
                nits.pick (nit_selector, ed_css_20, "5 Selectors", es_error, ec_css, "missing or invalid class name");
            else sparkle_ = css_class (args, b, args.t_.at (b).val_);
            break; 
        case ct_hash :
            b = next_non_whitespace (args.t_, b, to);
            if ((b < 0) || ((args.t_.at (b).t_ != ct_keyword) && (args.t_.at (b).t_ != ct_identifier)))
                nits.pick (nit_selector, ed_css_20, "5 Selectors", es_error, ec_css, "missing or invalid id");
            else sparkle_ = css_id (args, args.t_.at (b).val_);
            break; 
        case ct_colon :
            b = next_non_whitespace (args.t_, b, to);
            if ((b < 0) || ((args.t_.at (b).t_ != ct_keyword) && (args.t_.at (b).t_ != ct_identifier)))
                nits.pick (nit_selector, ed_css_20, "5 Selectors", es_error, ec_css, "missing or invalid pseudo element");
            else sparkle_ = css_fn (args, b, to);
            break;
        default :
            ::std::cout << "decoration " << args.t_.at (b).t_ << " unexpected.\n";
            GRACEFUL_CRASH (__FILE__, __LINE__); } }

bool decoration::bef_aft () const
{   if (sparkle_.index () != dt_fn) return false;
    switch (ssc_get < css_fn > (sparkle_).get ())
    {   case efn_after :
        case efn_before : return true;
        default : return false; } }

void decoration::accumulate (stats_t* s, const e_element e) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    if (! sparkle_.valueless_by_exception ())
        switch (sparkle_.index ())
        {   case dt_unset :
                break;
            case dt_attribute :
                ssc_get < css_attribute > (sparkle_).accumulate (s, e);
                break;
            case dt_class :
                ssc_get < css_class > (sparkle_).accumulate (s, e);
                break;
            case dt_fn :
                ssc_get < css_fn > (sparkle_).accumulate (s);
                break;
            case dt_id :
                ssc_get < css_id > (sparkle_).accumulate (s, e);
                break;
            default : GRACEFUL_CRASH (__FILE__, __LINE__); } }

::std::string decoration::rpt () const
{   if (! sparkle_.valueless_by_exception ())
        switch (static_cast < e_dec > (sparkle_.index ()))
        {   case dt_class : return ::std::get < css_class > (sparkle_).rpt (); 
            case dt_id : return ::std::get < css_id > (sparkle_).rpt (); 
            case dt_attribute : return ::std::get < css_attribute > (sparkle_).rpt (); 
            case dt_fn : return ::std::get < css_fn > (sparkle_).rpt ();
            case dt_unset : break;
            default : GRACEFUL_CRASH (__FILE__, __LINE__); break; }
    return ::std::string (); } 

void decoration::validate (arguments& args)
{   switch (sparkle_.index ())
    {   case dt_unset :
            break;
        case dt_attribute :
            ssc_get < css_attribute > (sparkle_).validate (args);
            break;
        case dt_class :
            ssc_get < css_class > (sparkle_).validate (args);
            break;
        case dt_fn :
            ssc_get < css_fn > (sparkle_).validate (args);
            break;
        case dt_id :
            ssc_get < css_id > (sparkle_).validate (args);
            break;
        default : GRACEFUL_CRASH (__FILE__, __LINE__); } }

void decoration::shadow (::std::stringstream& ss, arguments& args)
{   switch (sparkle_.index ())
    {   case dt_unset :
            break;
        case dt_attribute :
            ssc_get < css_attribute > (sparkle_).shadow (ss, args);
            break;
        case dt_class :
            ssc_get < css_class > (sparkle_).shadow (ss, args);
            break;
        case dt_fn :
            ssc_get < css_fn > (sparkle_).shadow (ss, args);
            break;
        case dt_id :
            ssc_get < css_id > (sparkle_).shadow (ss, args);
            break;
        default : GRACEFUL_CRASH (__FILE__, __LINE__); } }
