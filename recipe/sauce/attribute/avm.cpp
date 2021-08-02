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

#define AVM_INIT(X) \
    for (int index = 0; havt_##X [index].tag_ != elem_error; ++index) \
        avm.insert (avm_t::value_type (avm_key (havt_##X [index].tag_, havt_##X [index].a_), &havt_##X [index]))

void avm_init (nitpick& )
{   // these havt_? declarations written as one seriously bollox gcc. vc++ and clang are fine.
    extern hav_t    havt_a [], havt_b [], havt_c [], havt_d [], havt_e [], havt_f [], havt_g [], havt_h [], havt_i [],
                    havt_k [], havt_l [], havt_m [], havt_n [], havt_o [], havt_p [], havt_q [], havt_r [], havt_s [],
                    havt_t [], havt_u [], havt_v [], havt_w [], havt_x [],
                    havt_cc [], havt_dc [], havt_dct [], havt_rdf [];

    AVM_INIT(a);
    AVM_INIT(b);
    AVM_INIT(c);
    AVM_INIT(cc);
    AVM_INIT(d);
    AVM_INIT(dc);
    AVM_INIT(dct);
    AVM_INIT(e);
    AVM_INIT(f);
    AVM_INIT(g);
    AVM_INIT(h);
    AVM_INIT(i);
    AVM_INIT(k);
    AVM_INIT(l);
    AVM_INIT(m);
    AVM_INIT(n);
    AVM_INIT(o);
    AVM_INIT(p);
    AVM_INIT(q);
    AVM_INIT(r);
    AVM_INIT(rdf);
    AVM_INIT(s);
    AVM_INIT(t);
    AVM_INIT(u);
    AVM_INIT(v);
    AVM_INIT(w);
    AVM_INIT(x); }

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
