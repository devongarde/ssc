/*
ssc (static site checker)
File Info
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
#include "type/type.h"
#include "css/ffv.h"
#include "css/arguments.h"
#include "css/selectors.h"
#include "css/statement.h"
#include "css/flags.h"
#include "css/group.h"

void font_feature::parse (arguments& args, const e_css_statement cs, const int from, const int to)
{   PRESUME ((to < 0) || (from <= to), __FILE__, __LINE__);
    const int len = GSL_NARROW_CAST <int> (args.t_.size ());
    PRESUME (from < len, __FILE__, __LINE__);
    PRESUME (to < len, __FILE__, __LINE__);
    int b = first_non_whitespace (args.t_, from, to);
    name_.clear (); val_.clear ();
    if ((b < 0) || (args.t_.at (b).t_ == ct_curly_ket)) return;
    VERIFY_NOT_NULL (args.st_, __FILE__, __LINE__);
    const bool cv = (args.st_ -> get () == css_character_variant);
    nitpick& nits = args.t_.at (b).nits_;
    if ((args.t_.at (b).t_ != ct_keyword) && (args.t_.at (b).t_ != ct_identifier) && (args.t_.at (b).t_ != ct_string))
        nits.pick (nit_property, es_error, ec_css, quote (tkn_rpt (args.t_.at (b))), ": feature name expected");
    else
    {   name_ = args.t_.at (b).val_;
        args.note_font_feature (cs, name_);
        n_ = b;
        b = next_non_whitespace (args.t_, b, to);
        if ((b > 0) && (args.t_.at (b).t_ == ct_colon)) b = next_token_at (args.t_, b, to);
        else nits.pick (nit_css_syntax, es_error, ec_css, "missing colon after ", quote (name_));
        b = first_non_whitespace (args.t_, b, to);
        if ((b < 0) || ((b > 0) && (args.t_.at (b).t_ == ct_curly_ket)))
            nits.pick (nit_css_font_feature, ed_css_font_4, "6.9.1. Basic syntax", es_error, ec_css, "missing value for ", quote (name_));
        else 
        {   int x = 0;
            for (int i = b; (i > 0) && (i <= to); i = next_non_whitespace (args.t_, i, to))
            {   if (args.t_.at (i).t_ != ct_number)
                    nits.pick (nit_css_font_feature, ed_css_font_4, "6.9.1. Basic syntax", es_error, ec_css, quote (name_), ": ", args.t_.at (i).val_, " is no integer");
                else
                {   const int n = lexical < int > :: cast (args.t_.at (i).val_);
                    if (n < 0)
                        nits.pick (nit_css_font_feature, ed_css_font_4, "6.9.1. Basic syntax", es_error, ec_css, quote (name_), ": ", args.t_.at (i).val_, " must be +ve");
                    else if (cv && (x == 0) && ((n == 0) || (n > 100)))
                        nits.pick (nit_css_font_feature, ed_css_font_4, "6.9.1. Basic syntax", es_error, ec_css, quote (name_), ": ", args.t_.at (i).val_, " must lie between 1 and 100 inclusive");
                    else append (val_, " ", args.t_.at (i).val_); }
                ++x; } } } }
    
::std::string font_feature::rpt () const
{   return name_ + ": " + val_; }

void font_feature::validate (arguments& args, const sstr_t& valid, const char* const r)
{   PRESUME (n_ < args.t_.size (), __FILE__, __LINE__);
    VERIFY_NOT_NULL (r, __FILE__, __LINE__);
    if (! name_.empty ())
        if (valid.find (name_) == valid.cend ())
            args.t_.at (n_).nits_.pick (nit_css_font_feature, es_warning, ec_css, quote (name_), ": is not a recognised @", r); }

void font_feature::shadow (::std::stringstream& ss, arguments& )
{   if (! name_.empty ()) ss << name_ << ": " << val_; }
