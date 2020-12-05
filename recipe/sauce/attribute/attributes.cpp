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

#include "main/standard.h"
#include "attribute/attributes.h"
#include "webpage/page.h"
#include "element/element_classes.h"

bool attributes :: parse (nitpick& nits, const html_version& v, const attributes_node& an)
{   bool res = false;
    for (auto a : an.get_attributes ())
        if (a.has_key ())
        {   if (has_attribute (tag_, a.id ()))
            {   if (is_attribute_rejected (v, tag_, a.id ()))
                {   nits.pick (nit_attribute_barred, es_error, ec_attribute, ::boost::to_upper_copy (a.get_key ()), " is not permitted here");
                    continue; }
                aar_.at (a.id ()) = make_attribute_v_ptr (nits, v, a);
                if (aar_.at (a.id ()).get () != nullptr)
                {   res = true;
                    continue; }
                else if (elem (tag_).wild_attributes (v))
                {   nits.pick (nit_wild_attribute, es_info, ec_attribute, "apologies, but ", PROG, " cannot validate ", ::boost::to_upper_copy (a.get_key ()));
                    continue; } }
            if (a.id () != a_unknown)
                nits.pick (nit_attribute_barred, es_error, ec_attribute, ::boost::to_upper_copy (a.get_key ()), " does not belong here");
            else
            {   nits.pick (nit_unrecognised_attribute, es_warning, ec_attribute, quote (a.get_key ()), " is not recognised");
                append (unrecognised_, ", ", quote (a.get_key ())); } }
    return res; }

bool attributes :: set_value (nitpick& nits, const html_version& v, const e_attribute a, const ::std::string& s)
{   if (! has (a)) return false;
    aar_.at (a) -> set_value (nits, v, s);
    return true;}

bool attributes :: empty () const // better if aar_t is more sophisticated, and knows its current state (e.g. count of members with values)
{   for (auto a : aar_)
        if (a.get () != nullptr)
            return false;
    return true; }

bool attributes :: invalid () const // better if aar_t keeps state when attributes are asssigned
{   bool zilch = false;
    for (auto a : aar_)
        if (a.get () != nullptr)
        {   zilch = true;
            if (! a -> invalid ())
                return false; }
    return zilch; }

bool attributes :: valid () const // better if aar_t keeps state when attributes are asssigned
{   for (auto a : aar_)
        if (a.get () != nullptr)
            if (a -> invalid ())
                return false;
    return true; }

void attributes :: verify (nitpick& nits, const html_version& v, ids_t& ids, const attribute_bitset& flags, const vit_t& itemtypes)
{   for (auto a : aar_)
        if (a.get () != nullptr)
            a -> verify_id (nits, v, ids, flags, itemtypes); }

bool attributes :: invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
{   bool res = false;
    for (auto a : aar_)
        if (a.get () != nullptr)
            if (! a -> unknown () && ! a -> empty ())
                if (a -> invalid_id (nits, v, ids, pe)) res = true;
    return res; }

bool attributes :: invalid_access (nitpick& nits, const html_version& v, sstr_t* ids)
{   bool res = false;
    assert (ids != nullptr);
    for (auto a : aar_)
        if (a.get () != nullptr)
            if (! a -> unknown () && ! a -> empty ())
                if (a -> invalid_access (nits, v, ids)) res = true;
    return res; }

bool attributes :: has_url () const  // better as attribute_bitset AND (one for element attributes, one for URL attributes)
{   for (auto a : aar_)
        if (a.get () != nullptr)
            if (a -> is_url ()) return true;
    return false; }

bool attributes :: verify_url (nitpick& nits, const html_version& v, const directory& d, const ::boost::filesystem::path& pagename, const int line, const attribute_bitset& flags, const vit_t& itemtypes)
{   bool res = true;
    for (auto a : aar_)
        if (a.get () != nullptr)
            if (a -> is_url ())
                if (! a -> unknown () && ! a -> empty ())
                    if (! a -> verify_url (nits, v, d, pagename, line, flags, itemtypes))
                        res = false; // this way, all URL errors are reported, not just the first
    return res; }

void attributes :: verify_attributes (nitpick& nits, const html_version& v, attribute_bitset& state)
{   for (size_t i = 0; i < aar_.size (); ++i)
        if ((aar_.at (i).get () == nullptr) || aar_.at (i) -> unknown ())
        {   if (is_attribute_required (v, tag_, static_cast < e_attribute > (i)))
                nits.pick (nit_attribute_required, es_error, ec_element, "<", ::boost::to_upper_copy (elem::name (tag_)), "> requires ", ::boost::to_upper_copy (attr::name (static_cast < e_attribute > (i))), " in ", v.report ()); }
        else
        {   elem e (tag_);
            if (aar_.at (i) -> good () || aar_.at (i) -> empty ()) aar_.at (i) -> validate (nits, v, e, attr::name (static_cast < e_attribute > (i)));
            if (aar_.at (i) -> verify_version (nits, v, e)) state.set (aar_.at (i) -> id ());
            else nits.pick (nit_wrong_version, es_error, ec_element, ::boost::to_upper_copy (attr::name (static_cast < e_attribute > (i))), " is invalid with <", ::boost::to_upper_copy (elem::name (e)), "> in ", v.detailed_report ()); } }

void attributes :: mark (page& p, const e_attribute a)
{   if (has_attribute (tag_, a)) p.mark (tag_, a); }

void attributes :: mark (page& p)
{   for (auto a : aar_)
        if ((a.get () != nullptr) && ! a -> unknown ())
            p.mark (tag_, a -> id ()); }

void attributes :: shadow (::std::stringstream& ss, const html_version& v)
{   for (auto a : aar_)
        if (a.get () != nullptr)
            a -> shadow (ss, v); }

::std::string attributes :: report () const
{   if (! context.tell (e_debug)) return ::std::string ();
    if (tag_ == elem_undefined)
        if (! context.tell (e_splurge))
            return ::std::string ();
    ::std::string res;
    res += elem::name (tag_);
    bool first = true;
    for (auto a : aar_)
        if (a.get () != nullptr)
            if (! a -> unknown () || context.tell (e_splurge))
            {   if (first) { res += ": "; first = false; }
                else res += ", ";
                res += a -> report (); }
    res += "\n";
    return res; }
