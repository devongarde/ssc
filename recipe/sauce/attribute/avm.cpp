/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "attribute/avm.h"
#include "attribute/avm_data.h"
#include "main/context.h"

typedef ::std::multimap < uint64_t, hav_t* > avm_t;
avm_t avm;

inline uint64_t avm_key (const e_element tag, const e_attribute a)
{   return (static_cast < uint64_t > (tag) << 32) + static_cast < uint64_t > (a); }

void avm_init (nitpick& )
{   for (int index = 0; havt_abc [index].tag_ != elem_error; ++index)
        avm.insert (avm_t::value_type (avm_key (havt_abc [index].tag_, havt_abc [index].a_), &havt_abc [index]));
    for (int index = 0; havt_defgh [index].tag_ != elem_error; ++index)
        avm.insert (avm_t::value_type (avm_key (havt_defgh [index].tag_, havt_defgh [index].a_), &havt_defgh [index]));
    for (int index = 0; havt_ijkl [index].tag_ != elem_error; ++index)
        avm.insert (avm_t::value_type (avm_key (havt_ijkl [index].tag_, havt_ijkl [index].a_), &havt_ijkl [index]));
    for (int index = 0; havt_mnopqr [index].tag_ != elem_error; ++index)
        avm.insert (avm_t::value_type (avm_key (havt_mnopqr [index].tag_, havt_mnopqr [index].a_), &havt_mnopqr [index]));
    for (int index = 0; havt_stuvwxyz [index].tag_ != elem_error; ++index)
        avm.insert (avm_t::value_type (avm_key (havt_stuvwxyz [index].tag_, havt_stuvwxyz [index].a_), &havt_stuvwxyz [index])); }

bool is_invalid_attribute_version (const html_version& v, const e_element tag, const e_attribute a)
{   if (! v.known () || is_custom_attribute (a) || is_custom_element (tag)) return false;
    for (   avm_t::const_iterator i = avm.find (avm_key (tag, a));
            (i != avm.cend ()) && (i -> second != nullptr) && (i -> second -> tag_ == tag) && (i -> second -> a_ == a);
            ++i)
        if (may_apply (v, i -> second -> first_, i -> second -> last_)) return false;
    for (   avm_t::const_iterator i = avm.find (avm_key (elem_undefined, a));
            (i != avm.cend ()) && (i -> second != nullptr)  && (i -> second -> tag_ == elem_undefined) && (i -> second -> a_ == a);
            ++i)
        if (may_apply (v, i -> second -> first_, i -> second ->last_)) return false;
    return true; }

bool is_deprecated_attribute_version (const html_version& v, const e_element tag, const e_attribute a)
{   if (! v.known () || is_custom_attribute (a) || is_custom_element (tag)) return false;
    for (   avm_t::const_iterator i = avm.find (avm_key (tag, a));
            (i != avm.cend ()) && (i -> second != nullptr) && (i -> second-> tag_ == tag) && (i -> second-> a_ == a);
            ++i)
        if (may_apply (v, i -> second -> first_, i -> second -> last_)) return i -> second -> first_.deprecated (v);
    for (   avm_t::const_iterator i = avm.find (avm_key (elem_undefined, a));
            (i != avm.cend ()) && (i -> second != nullptr) && (i -> second -> tag_ == elem_undefined) && (i -> second -> a_ == a);
            ++i)
        if (may_apply (v, i -> second -> first_, i -> second -> last_)) return i -> second -> first_.deprecated (v);
    return false; }

bool not_production_attribute (const html_version& v, const e_element tag, const e_attribute a)
{   if (v.known () && v.is_5 () && (! is_custom_attribute (a)) && (! is_custom_element (tag)))
        for (   avm_t::const_iterator i = avm.find (avm_key (tag, a));
                (i != avm.cend ()) && (i -> second != nullptr) && (i -> second -> tag_ == tag) && (i -> second -> a_ == a);
                ++i)
            if (may_apply (v, i -> second -> first_, i -> second -> last_)) return i -> second -> first_.not_production ();
    return false; }

bool is_attribute_required (const html_version& v, const e_element tag, const e_attribute a)
{   if (v.known () && (! is_custom_attribute (a)) && (! is_custom_element (tag)))
        for (   avm_t::const_iterator i = avm.find (avm_key (tag, a));
                (i != avm.cend ()) && (i -> second != nullptr) && (i -> second -> tag_ == tag) && (i -> second -> a_ == a);
                ++i)
            if (may_apply (v, i -> second -> first_, i -> second -> last_)) return i -> second -> first_.required ();
    return false; }

bool is_attribute_rejected (const html_version& v, const e_element tag, const e_attribute a)
{   if (v.known () && (! is_custom_attribute (a)) && (! is_custom_element (tag)))
        for (   avm_t::const_iterator i = avm.find (avm_key (tag, a));
                (i != avm.cend ()) && (i -> second != nullptr) && (i -> second -> tag_ == tag) && (i -> second -> a_ == a);
                ++i)
            if (may_apply (v, i -> second -> first_, i -> second -> last_)) return i -> second -> first_.reject ();
    return false; }

#ifdef DEBUG
void avm_elem_crosscheck ()
{   void avm_class_crosscheck (const e_element e, const e_attribute a);
    for (auto a : avm)
        avm_class_crosscheck (a.second -> tag_, a.second -> a_); }
#endif // DEBUG
