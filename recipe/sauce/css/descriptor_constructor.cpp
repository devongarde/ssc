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
#include "css/descriptor_classes.h"
#include "css/arguments.h"
#include "css/group.h"

template < class PROPERTY, class ... X > struct descriptor_constructor : public descriptor_constructor < X ... >
{   static property_v_ptr make (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
    {   if (p != PROPERTY :: whoami ()) return descriptor_constructor < X... > :: make (args, start, to, nits, p, s, t);
        auto ptr = property_v_ptr (new PROPERTY ());
        ptr -> set_value (args, start, to, nits, s);
        return ptr; } };

template < > struct descriptor_constructor < desc_unknown >
{   static property_v_ptr make (arguments& args, const int start, const int to, nitpick& nits, e_css_property , const ::std::string& s, const css_token )
    {   auto ptr = property_v_ptr (new desc_unknown ());
        ptr -> set_value (args, start, to, nits, s);
        return ptr; } };

property_v_ptr make_descriptor_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
{   switch (args.v_.css_font ())
    {   case 5 :  return descriptor_constructor < DESCRIPTORS_5, desc_unknown > :: make (args, start, to, nits, p, s, t);
        case 4 :  return descriptor_constructor < DESCRIPTORS_4, desc_unknown > :: make (args, start, to, nits, p, s, t);
        case 3 :  return descriptor_constructor < DESCRIPTORS_3, desc_unknown > :: make (args, start, to, nits, p, s, t);
        default : break; }
    if (args.v_.css_version () == css_2_0) return descriptor_constructor < DESCRIPTORS_2, desc_unknown > :: make (args, start, to, nits, p, s, t);
    nits.pick (nit_css_version, es_error, ec_css, "CSS descriptors require CSS 2.0 or CSS Fonts");
    return property_v_ptr (new desc_unknown ()); }

property_v_ptr make_descriptor_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const css_token t)
{   PRESUME ((i >= 0) && (i < GSL_NARROW_CAST < int > (args.t_.size ())), __FILE__, __LINE__);
    ::std::string n (args.t_.at (i).val_);
    return make_descriptor_v_ptr (args, start, to, nits, examine_value < t_css_property > (nits, args.v_, n), value, t); }

property_v_ptr make_counter_style_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
{   return descriptor_constructor < COUNTER_DESCRIPTORS, desc_unknown > :: make (args, start, to, nits, p, s, t); }

property_v_ptr make_counter_style_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const css_token t)
{   PRESUME ((i >= 0) && (i < GSL_NARROW_CAST < int > (args.t_.size ())), __FILE__, __LINE__);
    ::std::string n (args.t_.at (i).val_);
    return make_counter_style_v_ptr (args, start, to, nits, examine_value < t_css_property > (nits, args.v_, n), value, t); }

property_v_ptr make_feature_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
{   return descriptor_constructor < FEATURE_DESCRIPTORS, desc_unknown > :: make (args, start, to, nits, p, s, t); }

property_v_ptr make_feature_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const css_token t)
{   PRESUME ((i >= 0) && (i < GSL_NARROW_CAST < int > (args.t_.size ())), __FILE__, __LINE__);
    ::std::string n (args.t_.at (i).val_);
    return make_feature_v_ptr (args, start, to, nits, examine_value < t_css_property > (nits, args.v_, n), value, t); }

property_v_ptr make_palette_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
{   return descriptor_constructor < PALETTE_DESCRIPTORS, desc_unknown > :: make (args, start, to, nits, p, s, t); }

property_v_ptr make_palette_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const css_token t)
{   PRESUME ((i >= 0) && (i < GSL_NARROW_CAST < int > (args.t_.size ())), __FILE__, __LINE__);
    ::std::string n (args.t_.at (i).val_);
    return make_palette_v_ptr (args, start, to, nits, examine_value < t_css_property > (nits, args.v_, n), value, t); }

property_v_ptr make_viewport_v_ptr (arguments& args, const int start, const int to, nitpick& nits, e_css_property p, const ::std::string& s, const css_token t)
{   return descriptor_constructor < VIEWPORT_DESCRIPTORS, desc_unknown > :: make (args, start, to, nits, p, s, t); }

property_v_ptr make_viewport_v_ptr (arguments& args, const int start, const int to, nitpick& nits, const int i, const ::std::string& value, const css_token t)
{   PRESUME ((i >= 0) && (i < GSL_NARROW_CAST < int > (args.t_.size ())), __FILE__, __LINE__);
    ::std::string n (args.t_.at (i).val_);
    return make_palette_v_ptr (args, start, to, nits, examine_value < t_css_property > (nits, args.v_, n), value, t); }
