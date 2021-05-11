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
#include "parser/parse_attribute.h"
#include "utility/quote.h"

attribute_node::attribute_node (nitpick& nits, const html_version& v, ns_ptr& nss, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end, const ::std::string::const_iterator value_start, const ::std::string::const_iterator value_end)
{   has_key_ = has_value_ = true;
    key_ = ::std::string (name_start, name_end);
    value_ = ::std::string (value_start, value_end);
    parse (nits, v, nss); }

attribute_node::attribute_node (nitpick& nits, const html_version& v, ns_ptr& nss, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end)
{   has_key_ = true;
    has_value_ = false;
    key_ = ::std::string (name_start, name_end);
    parse (nits, v, nss); }

void attribute_node::swap (attribute_node& an)
{   key_.swap (an.key_);
    value_.swap (an.value_);
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

void attribute_node::parse (nitpick& nits, const html_version& v, ns_ptr& nss)
{   ::std::string ns;
    id_ = attr :: parse (nits, v, nss, key_, ns);
    if (id_ == a_xmlns)
    {   DBG_ASSERT (nss.get () != nullptr);
        nss -> add (nits, v, ns, value_); } }
