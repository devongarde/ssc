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
#include "utility/common.h"

typedef ::std::pair < ::std::string, ::std::size_t > symbol_key;

inline bool operator == (const symbol_key& lhs, const symbol_key& rhs) noexcept
{   return (lhs.second == rhs.second) && (lhs.first == rhs.first); }

inline bool operator != (const symbol_key& lhs, const symbol_key& rhs) noexcept
{   return ! (lhs == rhs); }

inline bool operator < (const symbol_key& lhs, const symbol_key& rhs) noexcept
{   if (lhs.second < rhs.second) return true;
    if (lhs.second > rhs.second) return false;
    return (lhs.first < rhs.first); }

inline bool operator >= (const symbol_key& lhs, const symbol_key& rhs) noexcept
{   return ! (lhs < rhs); }

inline bool operator > (const symbol_key& lhs, const symbol_key& rhs) noexcept
{   return (lhs >= rhs) && (lhs != rhs); }

inline bool operator <= (const symbol_key& lhs, const symbol_key& rhs) noexcept
{   return ! (lhs > rhs); }

template < > struct std::hash < symbol_key >
{   ::std::size_t operator() (const symbol_key& k) const noexcept
    {   const ::std::size_t h = ::std::hash < ::std::string > () (k.first);
        return ::std::hash <::std::size_t> () (h ^ static_cast < ::std::size_t > (k.second)); } };
