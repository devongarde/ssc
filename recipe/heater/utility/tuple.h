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

#pragma once

// from https://codereview.stackexchange.com/questions/51407/stdtuple-foreach-implementation/67394#67394, Louis Dionne


#if defined (VS) && (VS <= 13)
// adapted from more recent VS libraries
template <class _Ty, _Ty... _Vals> struct integer_sequence
{   using value_type = _Ty;
    static size_t size () { return sizeof...(_Vals); } };
template <size_t... _Vals> using index_sequence = integer_sequence <size_t, _Vals...>;

template < typename TUPLE, typename F, ::std::size_t... INDICES >
    void for_each_impl (TUPLE&& tuple, F&& f, index_sequence < INDICES... >)
#else // VS
template < typename TUPLE, typename F, ::std::size_t... INDICES >
    void for_each_impl (TUPLE&& tuple, F&& f, ::std::index_sequence < INDICES... >)
#endif // VS
{   using swallow = int [];
    (void) swallow { 1,
        (f (::std::get < INDICES > (::std::forward < TUPLE > (tuple))), void (), int {}) ... }; }

template < typename TUPLE, typename F >
void for_each_attribute (TUPLE&& tuple, F&& f)
{   const ::std::size_t N = ::std::tuple_size <::std::remove_reference_t < TUPLE > >::value;
    for_each_impl (::std::forward < TUPLE > (tuple), ::std::forward < F > (f), ::std::make_index_sequence < N > {}); }

// based on https://stackoverflow.com/questions/25958259/how-do-i-find-out-if-a-tuple-contains-a-type

template < typename ATTRIBUTE, typename... ATTRIBUTES>
struct has_type;

template < typename ATTRIBUTE, typename... ATTRIBUTES >
struct has_type < ATTRIBUTE, ATTRIBUTE, ATTRIBUTES... > : ::std::true_type {};

template < typename ATTRIBUTE >
struct has_type < ATTRIBUTE, ATTRIBUTE > : ::std::true_type {};

template < typename ATTRIBUTE, typename OTHER, typename... ATTRIBUTES>
struct has_type < ATTRIBUTE, OTHER, ATTRIBUTES... > : has_type < ATTRIBUTE, ATTRIBUTES... > {};

template < typename ATTRIBUTE, typename OTHER >
struct has_type < ATTRIBUTE, OTHER > : ::std::false_type {};
