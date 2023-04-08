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

template < class PROPERTY, class ... X > struct property_constructor : public property_constructor < X ... >
{   static property_v_ptr make (arguments& args, const int start, const int to,nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
    {   if (p != PROPERTY :: whoami ()) return property_constructor < X... > :: make (args, start, to, nits, p, s, t);
        auto ptr = property_v_ptr (new PROPERTY ());
        ptr -> set_value (args, start, to, nits, s);
        return ptr; } };

template < class ... X > struct property_constructor < prop_text_align, X ... > : public property_constructor < X ... >
{   static property_v_ptr make (arguments& args, const int start, const int to,nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
    {   if (p != prop_text_align :: whoami ()) return property_constructor < X... > :: make (args, start, to, nits, p, s, t);
        if ((context.html_ver ().is_css_2_0 ()) && (t == ct_string))
        {   auto ptr = property_v_ptr (new prop_context ());
            ptr -> set_value (args, start, to, nits, s);
            return ptr; } 
        auto ptr = property_v_ptr (new prop_text_align ());
        ptr -> set_value (args, start, to, nits, s);
        return ptr; } };

template < > struct property_constructor < prop_unknown >
{   static property_v_ptr make (arguments& args, const int start, const int to,nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
    {   auto ptr = property_v_ptr (new prop_unknown ());
        ptr -> set_value (args, start, to, nits, s);
        return ptr; } };

property_v_ptr make_property_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
{   if (p < LAST_CSS_1_PROP) return property_constructor < CSS_PROPERTIES_1 > :: make (args, start, to, nits, p, s, t);
    if (p < LAST_CSS_2_PROP) return property_constructor < CSS_PROPERTIES_2 > :: make (args, start, to, nits, p, s, t);
    return property_constructor < CSS_PROPERTIES_3 > :: make (args, start, to, nits, p, s, t); }

property_v_ptr make_property_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const css_token t)
{   PRESUME ((i >= 0) && (i < GSL_NARROW_CAST < int > (args.t_.size ())), __FILE__, __LINE__);
    ::std::string n (args.t_.at (i).val_);
    if ((n.length () >= 2) && (n.substr (0, 2) == "--"))
    {   if (! args.v_.css_custom ())
        {   nits.pick (nit_css_custom, es_error, ec_css, "Custom properties, such as ", n, ", require CSS Custom");
            return make_property_v_ptr (args, start, to, nits, ec_unknown, value, t); }   
        if (n.length () == 2)
        {   nits.pick (nit_css_custom, ed_css_custom, "2. Defining Custom Properties", es_error, ec_css, "Custom property '--' is \"reserved for future use\"");   
            return make_property_v_ptr (args, start, to, nits, ec_unknown, value, t); }   
        return make_property_v_ptr (args, start, to, nits, ec_custom, value, t); }
    return make_property_v_ptr (args, start, to, nits, examine_value < t_css_property > (nits, args.v_, n), value, t); }

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
