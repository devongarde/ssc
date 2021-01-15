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

attribute_node::attribute_node (nitpick& nits, const html_version& v, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end, const ::std::string::const_iterator value_start, const ::std::string::const_iterator value_end)
        :   name_start_ (name_start), name_end_ (name_end), value_start_ (value_start), value_end_ (value_end)
{   has_key_ = has_value_ = true;
    parse (nits, v); }

attribute_node::attribute_node (nitpick& nits, const html_version& v, const ::std::string::const_iterator name_start, const ::std::string::const_iterator name_end)
        :   name_start_ (name_start), name_end_ (name_end), value_start_ (name_end), value_end_ (name_end)
{   has_key_ = true;
    has_value_ = false;
    parse (nits, v); }

void attribute_node::swap (attribute_node& an)
{   ::std::swap (name_start_, an.name_start_);
    ::std::swap (name_end_, an.name_end_);
    ::std::swap (value_start_, an.value_start_);
    ::std::swap (value_end_, an.value_end_);
    ::std::swap (id_, an.id_);
    ::std::swap (has_key_, an.has_key_);
    ::std::swap (has_value_, an.has_value_); }

::std::string attribute_node::rpt () const
{   ::std::string res;
    if (has_key_)
    {   res = " ";
        res += ::std::string (name_start_, name_end_);
        if (id_ == a_unknown) res += "(?)";
        if (has_value_)
        {   res += "=";
            res += quote (::std::string (value_start_, value_end_)); } }
    return res; }
