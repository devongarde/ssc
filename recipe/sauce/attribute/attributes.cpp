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
#include "attribute/attributes.h"
#include "webpage/page.h"
#include "element/element_classes.h"
#include "spell/spell.h"

void attributes :: swap (attributes& w) noexcept
{   aar_.swap (w.aar_);
    unrecognised_.swap (w.unrecognised_);
    box_.swap (w.box_);
    rebox (); }

e_element attributes :: tag () const noexcept
{   return box_.tag (); }

bool attributes :: parse (nitpick& nits, const html_version& v, const attributes_node& an)
{   bool res = false;
    for (auto a : an.get_attributes ())
        if (a.has_key ())
        {   if (has_attribute (tag (), a.id ()))
            {   if (is_attribute_rejected (v, tag (), a.id ()))
                {   nits.pick (nit_attribute_barred, es_error, ec_attribute, ::boost::to_upper_copy (a.get_key ()), " is not permitted here (", v.report (), ")");
                    continue; }
                aar_.at (a.id ()) = make_attribute_v_ptr (nits, v, &box_, a);
                if (aar_.at (a.id ()).get () != nullptr)
                {   res = true;
                    continue; } }
            else if (elem (tag ()).wild_attributes (v))
            {   nits.pick (nit_wild_attribute, es_info, ec_attribute, "apologies, but ", PROG, " cannot validate ", ::boost::to_upper_copy (a.get_key ()));
                continue; }
            if (tag () == elem_undefined)
                nits.pick (nit_custom, es_comment, ec_attribute, PROG, " cannot check attributes of custom elements");
            else if (a.id () == a_custom)
                nits.pick (nit_custom, es_comment, ec_attribute, PROG, " cannot verify that ", ::boost::to_upper_copy (a.get_key ()), " is valid here");
            else if (a.id () != a_unknown)
                nits.pick (nit_attribute_barred, es_error, ec_attribute, ::boost::to_upper_copy (a.get_key ()), " does not belong here (", v.report (), ")");
            else
            {   nits.pick (nit_unrecognised_attribute, es_warning, ec_attribute, quote (a.get_key ()), " is not recognised (", v.report (), ")");
                append (unrecognised_, ", ", quote (a.get_key ())); } }
    return res; }

bool attributes :: set_value (nitpick& nits, const html_version& v, const e_attribute a, const ::std::string& s)
{   if (! has (a)) return false;
    VERIFY_NOT_NULL (aar_.at (a), __FILE__, __LINE__);
    aar_.at (a) -> set_value (nits, v, s);
    return true;}

bool attributes :: empty () const noexcept // better if aar_t is more sophisticated, and knows its current state (e.g. count of members with values)
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

void attributes :: verify_id (element& e)
{   for (auto a : aar_)
        if (a.get () != nullptr)
            a -> verify_id (e); }

bool attributes :: invalid_id (nitpick& nits, const html_version& v, ids_t& ids, element* pe)
{   bool res = false;
    for (auto a : aar_)
        if (a.get () != nullptr)
            if (! a -> unknown () && ! a -> empty ())
                if (a -> invalid_id (nits, v, ids, pe)) res = true;
    return res; }

bool attributes :: invalid_access (nitpick& nits, const html_version& v, sstr_t* ids)
{   bool res = false;
    VERIFY_NOT_NULL (ids, __FILE__, __LINE__);
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

bool attributes :: verify_url (nitpick& nits, const html_version& v, element& e)
{   bool res = true;
    for (auto a : aar_)
        if (a.get () != nullptr)
            if (a -> is_url ())
                if (! a -> unknown () && ! a -> empty ())
                    if (! a -> verify_url (nits, v, e))
                        res = false; // this way, all URL errors are reported, not just the first
    return res; }

void attributes :: verify_attributes (nitpick& nits, const html_version& v, element* pe, const lingo& lang)
{   VERIFY_NOT_NULL (pe, __FILE__, __LINE__);
    for (size_t i = 0; i < aar_.size (); ++i)
        if ((aar_.at (i).get () == nullptr) || aar_.at (i) -> unknown ())
        {   if (is_attribute_required (v, tag (), static_cast < e_attribute > (i)))
                nits.pick (nit_attribute_required, es_error, ec_element, "<", ::boost::to_upper_copy (elem::name (box_.tag ())), "> requires ", ::boost::to_upper_copy (attr::name (static_cast < e_attribute > (i))), " in ", v.report ()); }
        else
        {   const elem e (tag ());
            if (aar_.at (i) -> good () || aar_.at (i) -> empty ()) aar_.at (i) -> verify_attribute (nits, v, pe -> node ().id (), pe, attr::name (static_cast < e_attribute > (i)));
            if (aar_.at (i) -> verify_version (nits, v, e)) pe -> own_attributes ().set (aar_.at (i) -> id ());
            else nits.pick (nit_wrong_version, es_error, ec_element, ::boost::to_upper_copy (attr::name (static_cast < e_attribute > (i))), " is invalid with <", ::boost::to_upper_copy (elem::name (e)), "> in ", v.report ());
            if (context.spell () && attr::spellcheck (static_cast < e_attribute > (i)))
                check_spelling (nits, v, lang, aar_.at (i) -> get_string ()); } }

void attributes :: mark (page& p, const e_attribute a)
{   if (has_attribute (box_.tag (), a)) p.mark (box_.tag (), a); }

void attributes :: mark (page& p)
{   for (auto a : aar_)
        if ((a.get () != nullptr) && ! a -> unknown ())
            p.mark (box_.tag (), a -> id ()); }

void attributes :: shadow (::std::stringstream& ss, const html_version& v, element* e)
{   for (auto a : aar_)
        if (a.get () != nullptr)
            a -> shadow (ss, v, e); }

::std::string attributes :: report () const
{   if (! context.tell (es_debug)) return ::std::string ();
    if (box_.tag () == elem_undefined)
        if (! context.tell (es_splurge))
            return ::std::string ();
    ::std::string res;
    res += elem::name (box_.tag ());
    bool first = true;
    for (auto a : aar_)
        if (a.get () != nullptr)
            if (! a -> unknown () || context.tell (es_splurge))
            {   if (first) { res += ": "; first = false; }
                else res += ", ";
                res += a -> report (); }
    res += "\n";
    return res; }
