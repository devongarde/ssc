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

#pragma once
#include "utility/common.h"
#include "base/sz.h"

template < class LC > struct enlc
{   static ::std::string to (const ::std::string& from) { return ::boost::to_lower_copy (from); } };

template < > struct enlc < sz_false >
{   static ::std::string to (const ::std::string& from) { return from; } };

template < class V, typename VALUE, typename CATEGORY = ident_t, CATEGORY INIT = 0 > struct symbol_entry
{   V               first_, last_;
    const char*     sz_ = nullptr;
    VALUE           v_ = static_cast < VALUE > (0);
    CATEGORY        ns_ = INIT;
    flags_t         flags_ = 0;
    flags_t         flags2_ = 0; };

template < class V, typename CATEGORY = ident_t, CATEGORY INIT = 0 > struct symbol_entry_t
{   V               first_, last_;
    const char*     sz_ = nullptr;
    ::std::size_t   v_ = 0;
    CATEGORY        ns_ = INIT;
    flags_t         flags_ = 0;
    flags_t         flags2_ = 0; };
