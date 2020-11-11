/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "type/enum.h"

typedef ::std::bitset < static_cast < ::std::size_t > (last_element_tag) > element_bitset;
typedef ::std::bitset < static_cast < ::std::size_t > (last_attribute) > attribute_bitset;

extern const element_bitset empty_element_bitset;
extern const element_bitset autocapitalise_bitset;
extern const element_bitset faux_bitset;
extern const element_bitset form_bitset;
extern const element_bitset header_bitset;
extern const element_bitset interactive_bitset;
extern const element_bitset label_bitset;
extern const element_bitset listed_bitset;
extern const element_bitset media_bitset;
extern const element_bitset non_standard_bitset;
extern const element_bitset sectioning_bitset;

extern const attribute_bitset empty_attribute_bitset;

inline element_bitset element_bit_set (const e_element e)
{   element_bitset bs;
    bs.set (e);
    return bs; }

inline attribute_bitset attribute_bit_set (const e_attribute e)
{   attribute_bitset bs;
    bs.set (e);
    return bs; }

inline element_bitset operator | (const element_bitset& bs, const e_element e)
{   element_bitset res (bs);
    res.set (e);
    return res; }

inline element_bitset operator & (const element_bitset& bs, const e_element e)
{   if (! bs.test (e)) return element_bitset ();
    return element_bitset (e); }

inline element_bitset& operator |= (element_bitset& bs, const e_element e)
{   bs.set (static_cast < ::std::size_t > (e));
    return bs; }

inline element_bitset& operator &= (element_bitset& bs, const e_element e)
{   if (bs.test (e)) bs = element_bitset (e);
    else bs = element_bitset ();
    return bs; }

inline attribute_bitset operator | (const attribute_bitset& bs, const e_attribute e)
{   attribute_bitset res (bs);
    res.set (e);
    return res; }

inline attribute_bitset operator & (const attribute_bitset& bs, const e_attribute e)
{   if (! bs.test (e)) return attribute_bitset ();
    return attribute_bitset (e); }

inline attribute_bitset& operator |= (attribute_bitset& bs, const e_attribute e)
{   bs.set (static_cast < ::std::size_t > (e));
    return bs; }

inline attribute_bitset& operator &= (attribute_bitset& bs, const e_attribute e)
{   if (bs.test (e)) bs = attribute_bitset (e);
    else bs = attribute_bitset ();
    return bs; }

inline bool any (const element_bitset& lhs, const element_bitset& rhs)
{   element_bitset tst (lhs & rhs);
    return tst.any (); }

inline bool all (const element_bitset& lhs, const element_bitset& rhs)
{   element_bitset tst (lhs & rhs);
    return tst == rhs; }

inline bool any (const attribute_bitset& lhs, const attribute_bitset& rhs)
{   attribute_bitset tst (lhs & rhs);
    return tst.any (); }

inline bool all (const attribute_bitset& lhs, const attribute_bitset& rhs)
{   attribute_bitset tst (lhs & rhs);
    return tst == rhs; }

::std::string nameset (const element_bitset& bs);
::std::string nameset (const attribute_bitset& bs);
