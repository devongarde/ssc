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
#include "parser/parse_element.h"
#include "parser/parse_bras_ket.h"
#include "utility/bigvector.h"

class elements_node
{   typedef big_vector < element_node, 8192 > ven_t;
    ven_t ven_;
    bool invalid_ = true;
    html_version version_;
    void parse (const html_version& v, bras_ket& elements);
    element_node* find_corresponding_open (const elem& id, element_node* parent);
    void report_missing_closures (const html_version& v, element_node* parent, element_node* ancestor);
    element_node* insert_family_tree (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id, const bool presumed);
    element_node* find_permitted_parent (const html_version& v, const elem& id, element_node* parent);
    void repair_invalid_parents (nitpick& nits, const html_version& v, const elem& id, element_node* parent, const element_node* ancestor, const bra_element_ket& ket, const bool closing);
    void hook_up (element_node* current, element_node*& previous, element_node*& parent, const bool closure, const bool open);
    element_node* insert_closure (const html_version& v,  element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id, const bool presumed);
    element_node* insert_non_closure (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id, const bool open);
    element_node* insert_closed (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id);
    element_node* insert_open (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& id);
    element_node* insert (const html_version& v, element_node*& previous, element_node*& parent, bra_element_ket& ket, const elem& idz);
public:
    elements_node () = default;
    elements_node (const elements_node& en) = default;
	elements_node(elements_node&& en) = default;
	elements_node (nitpick& nits, const ::std::string& content)
    {   invalid_ = ! parse (nits, content); }
    ~elements_node () = default;
    elements_node& operator = (const elements_node& en) = default;
	elements_node& operator = (elements_node&& en) = default;
	void swap (elements_node& en) noexcept;
    void reset () noexcept;
    void reset (const elements_node& en);
    bool parse (nitpick& nits, const ::std::string& content);
    void harvest_nits (nitpick& nits);
    element_node* faux_node ();
    bool has_element (const e_element e) const;
    const element_node& top () const
    {   PRESUME (! invalid (), __FILE__, __LINE__);
        return ven_.at (0); }
    element_node& top ()
    {   PRESUME (! invalid (), __FILE__, __LINE__);
        return ven_.at (0); }
    html_version version () const noexcept { return version_; }
    ::std::string text ();
    ::std::string rpt ();
    vstr_t words (nitpick& nits, const html_version& v) const;
    uint64_t size () const noexcept { return ven_.size (); }
    bool invalid () const noexcept { return (invalid_ && (size () > 0)); } };
