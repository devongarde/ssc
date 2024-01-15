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

#pragma once
#include "base/type_case.h"
#include "base/type_core.h"
#include "utility/quote.h"
#include "parser/parse_elements.h"
#include "main/args.h"

class element;

bool test_many (const vtype_t& vty, nitpick& nits, const html_version& v, const vstr_t& vs);

template < e_type TYPE > struct type_master : public string_value < TYPE >
{   using string_value < TYPE > :: string_value; };

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26440) // By the same logic: dalmations are dogs, dalmations have spots, therefore all dogs have spots.
#endif // _MSC_VER
template < e_type T > bool test_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box = nullptr)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (t.good () && (box != nullptr))
    {   ids_t i;
        t.invalid_id (nits, v, i, box); }
    return t.good (); }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

template < e_type T > bool test_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& id, element* box = nullptr)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (! t.good ()) return false;
    id = t.get_id ();
    if (t.good () && (box != nullptr))
    {   ids_t i;
        t.invalid_id (nits, v, i, box); }
    return true; }

template < e_type T > typename type_master < T > :: value_type examine_value (nitpick& nits, const html_version& v, const ::std::string& s, element* box = nullptr)
{   type_master < T > t;
    t.set_value (nits, v, s);
    if (! t.good ()) return static_cast < typename type_master < T > :: value_type > (type_master < T > :: default_value ());
    if (box != nullptr)
    {   ids_t i;
        t.invalid_id (nits, v, i, box); }
    return static_cast < typename type_master < T > :: value_type > (t.get ()); }

template < e_type T > e_animation_type grab_animation_type () noexcept
{   type_master < T > t;
    return t.animation_type (); }

template < flags_t F > struct flagify
{   static bool accept (const flags_t& v)
    {   return ((F & v) != NOFLAGS); }
    static bool reject (const flags_t& v)
    {   return accept (v); } };  

template < > struct flagify < NOFLAGS >
{   static bool accept (const flags_t& )
    {   return true; }
    static bool reject (const flags_t& )
    {   return false; } };  

template < e_type T, flags_t HV, flags_t HE = NOFLAGS, flags_t H2 = NOFLAGS, flags_t H3 = NOFLAGS, flags_t H4 = NOFLAGS > struct required : public type_master < T >
{   using type_master < T > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s, const ::std::string& burble)
    {   if (flagify < HV > :: accept (v.flags ()) &&    
            flagify < HE > :: accept (v.ext ()) &&     
            flagify < H2 > :: accept (v.ext2 ()) &&     
            flagify < H3 > :: accept (v.ext3 ()) &&     
            flagify < H4 > :: accept (v.ext4 ()))
                type_master < T > :: set_value (nits, v, s);
        else
        {   nits.pick (nit_version, es_error, ec_type, burble);
            type_master < T > status (s_invalid); } } };

template < e_type T, flags_t HV, flags_t HE = NOFLAGS, flags_t H2 = NOFLAGS, flags_t H3 = NOFLAGS, flags_t H4 = NOFLAGS > struct barred : public type_master < T >
{   using type_master < T > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s, const ::std::string& burble)
    {   if (flagify < HV > :: reject (v.flags ()) ||    
            flagify < HE > :: reject (v.ext ()) ||     
            flagify < H2 > :: reject (v.ext2 ()) ||     
            flagify < H3 > :: reject (v.ext3 ()) ||     
            flagify < H4 > :: reject (v.ext4 ()))
        {   nits.pick (nit_version, es_error, ec_type, burble);
            type_master < T > status (s_invalid); } 
        else type_master < T > :: set_value (nits, v, s); } };

template < e_type T, flags_t H2, flags_t H3, flags_t H4 > struct css_req : public required < T, NOFLAGS, NOFLAGS, H2, H3, H4 >
{   using required < T, NOFLAGS, NOFLAGS, H2, H3, H4 > :: required; };

template < e_type T, flags_t H2, flags_t H3, flags_t H4 > struct css_bar : public barred < T, NOFLAGS, NOFLAGS, H2, H3, H4 >
{   using barred < T, NOFLAGS, NOFLAGS, H2, H3, H4 > :: barred; };
