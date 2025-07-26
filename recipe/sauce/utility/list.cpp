/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "utility/list.h"

sstr_t empty_sstr;

const sstr_t& wblist::get (const ::std::string& s) const
{   const strss_t::const_iterator i = list_.find (s);
    if (i == list_.cend ()) return empty_sstr;
    return i -> second; }

bool wblist::set (const ::std::string& k, const ::std::string v)
{   const strss_t::iterator i = list_.find (k);
    if (i == list_.end ())
    {   sstr_t l;
        l.insert (v);
        list_.insert (strss_t::value_type (k, l));
        return true; }
    i -> second.insert (v);
    return false; }
