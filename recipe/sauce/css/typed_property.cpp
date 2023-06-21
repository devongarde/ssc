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
#include "feedback/nitpick.h"
#include "css/typed_property.h"
#include "css/property_classes.h"
#include "css/arguments.h"
#include "css/group.h"

bool examine_custom_property (arguments& args, nitpick& nits, const int from, const int to)
{   bool res = true;
    if (from > 0)
    {   ::std::string prop;
        const int comma = token_find (args.t_, ct_comma, from, to);
        const int ket = token_find (args.t_, ct_round_ket, from, to);
        int next = ket;
        if ((comma > 0) && (comma < ket)) next = comma;
        if (args.t_.at (from).t_ == ct_string)
        {   prop = args.t_.at (from).val_;
            const int k = next_non_whitespace (args.t_, from, to);
            if (k != next)
            {   nits.pick (nit_css_custom, ed_css_custom, "2. Defining Custom Properties", es_error, ec_css, "Junk found after ", quote (prop));
                res = false; } }
        else prop = assemble_string (args.t_, from, next, false);
        auto i = args.g_.custom_prop ().find (prop);
        if (i == args.g_.custom_prop ().cend ())
        {   if (comma < 0)
            {   nits.pick (nit_css_custom, es_warning, ec_css, quote (prop), " is not a known customer property");
                res = false; }
            else
            {   args.g_.custom_prop ().emplace (prop, 1);
                nits.pick (nit_css_custom, es_info, ec_css, quote (prop), " noted (with fallback value)"); }
            res = false; }
        else i -> second += 1; }
    return res; }

bool check_custom_property (arguments& args, const ::std::string& s)
{   auto i = args.g_.custom_prop ().find (s);
    if (i == args.g_.custom_prop ().cend ()) return false;
    i -> second += 1;
    return true; }

void validate_animation_name (type_master < t_css_anim_base >& cab, arguments& args)
{   cab.invalid_access (args.t_.at (0).nits_, args.v_, &args.g_.keyframe ()); }

bool check_constants (arguments& args, nitpick& nits, const int i)
{   nitpick nets;
    if (! test_value < t_css_val_con > (nets, args.v_, args.t_.at (i).val_)) return false;
    nits.merge (nets);
    if (args.v_.css_value () < 4)
        nits.pick (nit_css_value, ed_css_value_4, "10.7 Numeric Constants", es_error, ec_css, quote (args.t_.at (i).val_), " requires CSS Values 4");
    return true; }

bool call_fn (arguments& args, nitpick& nits, int& i, const int to, bool& res, e_css_val_fn& e)
{   nitpick nuts;
    type_master < t_css_val_fn > cvf;
    e = cvf_none;
    cvf.set_value (nuts, args.v_, args.t_.at (i).val_);
    if (! cvf.good ()) return false;
    nits.merge (nuts);
    i = next_non_whitespace (args.t_, i, to);
    if ((i < 0) || (args.t_.at (i).t_ != ct_round_brac))
        nits.pick (nit_css_syntax, es_error, ec_css, "expecting '(' after ", quote (cvf.name ()));
    else
    {   i = next_non_whitespace (args.t_, i, to);
        if (i > 0)
        {   res = true;
            switch (context.css_value ())
            {   case 4 :
                    if ((cvf.get () == cvf_colour_mix) && (context.css_colour () < 5))
                        nits.pick (nit_css_colour, es_error, ec_css, quote (cvf.name ()), " requires CSS Colour 5 (1)");
                    else e = cvf.get ();
                    break;
                case 3 :
                    switch (cvf.get ())
                    {   case cvf_calc :
                            e = cvf_calc; break;
                        case cvf_url:
                            e = cvf_url; break;
                        case cvf_colour_mix :
                            if (context.css_colour () < 5)
                                nits.pick (nit_css_colour, es_error, ec_css, quote (cvf.name ()), " requires CSS Colour 5 (2)");
                            else e = cvf_colour_mix;
                            break;
                        default :
                            nits.pick (nit_css_value, es_error, ec_css, quote (cvf.name ()), " requires CSS Values 4"); }
                    break;
                default :
                    if (cvf.get () == cvf_url) e = cvf_url;
                    else nits.pick (nit_css_value, es_error, ec_css, quote (cvf.name ()), " requires CSS Values");
                    break; } } }
    return true; }

bool test_cascade (const ::std::string& s, e_iiu& iiu)
{   switch (context.css_cascade ())
    {   case 6 :
        case 5 :
            switch (s.at (0))
            {   case 'r' :
                case 'R' :
                    if (compare_no_case (s, "revert-layer"))
                        {   iiu = iiu_revert_layer;
                            return true; }
                    break;
                default: break; }
            FALLTHROUGH;   
        case 4 :
            switch (s.at (0))
            {   case 'r' :
                case 'R' :
                    if (compare_no_case (s, "revert"))
                        {   iiu = iiu_revert;
                            return true; }
                    break;
                default: break; }
            FALLTHROUGH;   
        case 3 :
            switch (s.at (0))
            {   case 'i' :
                case 'I' :
                    if (s.length () == 7)
                        if (compare_no_case (s, "inherit"))
                        {   iiu = iiu_inherit;
                            return true; }
                        if (compare_no_case (s, "initial"))
                        {   iiu = iiu_initial;
                            return true; }
                    break;
                case 'u' :
                case 'U' :
                    if (compare_no_case (s, "unset"))
                    {   iiu = iiu_unset;
                        return true; }
                    break;
                default: break; }
            break;
        default :
            PRESUME (context.css_version () < css_3, __FILE__, __LINE__);
            if (context.css_version () != css_1)
                if (compare_no_case (s, "inherit"))
                {   iiu = iiu_inherit;
                    return true; }
            break; }
    return false; }