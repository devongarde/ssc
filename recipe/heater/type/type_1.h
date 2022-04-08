/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "type/sz.h"

template < e_type TYPE, class SZ > struct one_value : public type_base < mono, TYPE >
{   using type_base < mono, TYPE > :: type_base;
    static e_animation_type animation_type () noexcept { return at_other; }
    ::std::string get_string () const
    {   if (! type_base < mono, TYPE > :: unknown ()) return SZ::sz (); return ::std::string (); }
    void shadow (::std::stringstream& ss, const html_version& , element* )
    {   ss << '=' << get_string (); }
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s);
    static mono default_value () { return static_cast <mono> (0); }
    bool has_value (const mono& ) const { return type_base < mono, TYPE > :: known (); }
    int get_int () const { return 0; }
    mono get () const { return static_cast <mono> (0); } };

template < > struct type_master < t_1 > : one_value < t_1, sz_1 >
{ using one_value < t_1, sz_1 > :: one_value; };

template < > struct type_master < t_bb > : one_value < t_bb, sz_makeapp >
{ using one_value < t_bb, sz_makeapp > :: one_value; };

template < > struct type_master < t_blocking > : one_value < t_blocking, sz_render >
{ using one_value < t_blocking, sz_render > :: one_value; };

template < > struct type_master < t_cc_prohibits > : one_value < t_cc_prohibits, sz_cc_commercialuse >
{ using one_value < t_cc_prohibits, sz_cc_commercialuse > :: one_value; };

template < > struct type_master < t_html_boolean > : one_value < t_html_boolean, sz_true >
{ using one_value < t_html_boolean, sz_true > :: one_value; };

template < > struct type_master < t_keygentype > : one_value < t_keygentype, sz_rsa >
{ using one_value < t_keygentype, sz_rsa > :: one_value; };

template < > struct type_master < t_svg_content > : one_value < t_svg_content, sz_structured_text >
{ using one_value < t_svg_content, sz_structured_text > :: one_value; };

template < > struct type_master < t_svg_phase > : one_value < t_svg_phase, sz_default >
{ using one_value < t_svg_phase, sz_default > :: one_value; };

template < > struct type_master < t_xmllink > : one_value < t_xmllink, sz_simple >
{ using one_value < t_xmllink, sz_simple > :: one_value; };

template < e_type TYPE, class SZ > void one_value < TYPE, SZ > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   ::std::string t (trim_the_lot_off (s));
    if (t.empty ()) type_base < mono, TYPE > :: status (s_empty);
    else
    {   if (v.xhtml () && ! v.svg () && (t.find_first_of (UPPERCASE) != ::std::string::npos))
            nits.pick (nit_xhtml_enum_lc, ed_x1, "4.11. Attributes with pre-defined value sets", es_warning, ec_type, "enumerations must be lower cased in ", v.report ());
        ::boost::to_lower (t);
        if ((t == SZ::sz ())) type_base < mono, TYPE > :: status (s_good);
        else
        {   type_base < mono, TYPE > :: status (s_invalid);
            nits.pick (nit_unrecognised_value, es_error, ec_type, quote (t), " is invalid here; the only valid value is ", quote (SZ::sz ())); } } }
