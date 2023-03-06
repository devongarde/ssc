/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "parser/parse_attribute.h"
#include "parser/parse_attributes.h"
#include "parser/parse_element.h"
#include "utility/quote.h"
#include "type/type.h"

attribute_node::attribute_node (nitpick& nits, const html_version& v, attributes_node* box, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end,
                                const ::std::string::const_iterator value_start, const ::std::string::const_iterator value_end, const bool normal)
    :   box_ (box)
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    has_key_ = has_value_ = true;
    key_ = ::std::string (name_start, name_end);
    value_ = ::std::string (value_start, value_end);
    parse (nits, v, normal); }

attribute_node::attribute_node (nitpick& nits, const html_version& v, attributes_node* box, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end, const bool normal)
    :   box_ (box)
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    has_key_ = true;
    has_value_ = false;
    key_ = ::std::string (name_start, name_end);
    parse (nits, v, normal); }

attribute_node::attribute_node (attributes_node* box)
    :   box_ (box)
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__); }

void attribute_node::swap (attribute_node& an) noexcept
{   key_.swap (an.key_);
    value_.swap (an.value_);
    ::std::swap (box_, an.box_);
    ::std::swap (id_, an.id_);
    ::std::swap (has_key_, an.has_key_);
    ::std::swap (has_value_, an.has_value_); }

::std::string attribute_node::rpt () const
{   ::std::string res;
    res = " ";
    res += key_;
    if (id_ == a_unknown) res += "(?)";
    if (has_value_)
    {   res += "=";
        res += quote (value_); }
    return res; }

void attribute_node::parse (nitpick& nits, const html_version& v, const bool normal)
{   ::std::string ns;
    nitpick nuts;
    id_ = attr :: parse (nuts, v, namespaces (), key_, ns);
    switch (id_)
    {   case a_xmlns :
            if ((! normal) && has_key_ && has_value_)
            {   prepare_namespaces ();
                declare_namespace (nits, v, ns, value_, namespaces (), true); }
            break;
        case a_prefix :
            if (context.rdfa ())
            {   if (normal && has_key_ && has_value_)
                {   vabb_t vpre;
                    prepare_prefixes ();
                    parse_prefixes (nits, v, value_, prefixes () -> up (), vpre, true);
                    for (auto pr : vpre)
                        prefixes () -> declare (v, schema_names, pr.short_, pr.long_); }
                return; }
            if (normal) nits.merge (nuts);
            break;
        default :
            if (normal) nits.merge (nuts);
            break; } }

prefixes_ptr attribute_node::prefixes () const
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    return box_ -> prefixes (); }

void attribute_node::prepare_prefixes ()
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    return box_ -> prepare_prefixes (); }

namespaces_ptr attribute_node::namespaces () const
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    return box_ -> namespaces (); }

void attribute_node::prepare_namespaces ()
{   VERIFY_NOT_NULL (box_, __FILE__, __LINE__);
    return box_ -> prepare_namespaces (); }
