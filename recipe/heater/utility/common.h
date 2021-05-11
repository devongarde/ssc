/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "type/enum.h"
#include "parser/html_version.h"

struct true_type { };
struct false_type { };

typedef uint32_t uid_t;
const uid_t uid_max = UINT32_MAX;

typedef ::std::vector < int > vint_t;
typedef ::std::vector < double > vdbl_t;
typedef ::std::vector < ::std::string > vstr_t;
typedef ssc_set < ::std::string > sstr_t;
typedef ssc_map < ::std::string, ::std::string > ustr_t;
typedef ssc_map < ::std::string, ::std::size_t > msid_t;
typedef ::std::map < ::std::string, ::std::size_t > smsid_t;
typedef ssc_map < ::std::size_t, ::std::string > misd_t;
typedef ustr_t::value_type ustrv_t;
typedef ::std::basic_string < char32_t > string32;
typedef ::std::basic_stringstream < char32_t > stringstream32;

typedef ::std::shared_ptr < void > void_ptr;
struct really_free { void operator () (void *p) { free (p); } };
inline void_ptr alloc_void_ptr (const ::std::size_t sz) { return void_ptr (malloc (sz), really_free ()); }

const uint32_t uint32_category_shift =  28;
const uint32_t uint32_item_mask =       0x0FFFFFFF;
const uint32_t uint32_category_mask =   0xF0000000;

inline uint32_t ndx_category (const uint32_t x) { return (x & uint32_category_mask) >> uint32_category_shift; }
inline uint32_t ndx_item (const uint32_t x) { return (x & uint32_item_mask); }

::std::string trim_the_lot_off (const ::std::string& s);
bool remove_tail (::std::string& s, ::std::string& tail, const char ch);
bool remove_head (::std::string& s, ::std::string& head, const char ch);
::std::string remove_tail (::std::string& s, const char ch);
::std::string remove_head (::std::string& s, const char ch);
::std::string unify_whitespace (const ::std::string& s);
bool separate_first (const ::std::string& s, ::std::string& head, ::std::string& tail, const char ch);
bool separate_last (const ::std::string& s, ::std::string& head, ::std::string& tail, const char ch);
bool separate (const ::std::string& s, ::std::string& head, ::std::string& tail, const char ch);
bool ends_with_example (const ::std::string& s);

inline ::std::string tart (const ::std::string& s)
{   return unify_whitespace (trim_the_lot_off (s)); }

vstr_t split_by_charset (const ::std::string& s, const char* charset);
vstr_t split_quoted_by_space (const ::std::string& s);
::std::string read_text_file (const ::boost::filesystem::path& name);
::std::string read_text_file (const ::std::string& name);
void_ptr read_binary_file (nitpick& nits, const ::boost::filesystem::path& name, uintmax_t& sz, const bool zero_ok = false);
bool write_text_file (const ::std::string& name, const ::std::string& content);
::boost::filesystem::path get_tmp_filename ();
bool contains (const vstr_t& con, const ::std::string& val);

inline bool cnc_test (unsigned char a, unsigned char b)
{ return ::std::tolower (a) == ::std::tolower (b); }

inline bool compare_no_case (const std::string& a, const std::string& b)
{   if (a.length () != b.length ()) return false;
    return ::std::equal (b.begin (), b.end (), a.begin (), cnc_test); }

bool is_one_of (const ::std::string& s, const vstr_t& v);
::std::size_t which_one_of (const ::std::string& s, const vstr_t& v);
bool is_whitespace (const ::std::string::const_iterator b, const ::std::string::const_iterator e);
inline bool is_whitespace (const ::std::string& s) { return is_whitespace (s.cbegin (), s.cend ()); }

inline vstr_t split_by_space (const ::std::string& s)
{   return split_by_charset (s, " "); }

inline vstr_t split_by_newline (const ::std::string& s)
{   return split_by_charset (s, "\n"); }

template < class T > T read_field (::boost::property_tree::ptree& tree, const char* field)
{   return tree.get (field, T ()); }

template < class T > T read_field (::boost::property_tree::ptree& tree, const ::std::string& container, const char* field)
{   ::std::string name (container);
    name += SEP;
    name += field;
    return tree.get (name, T ()); }

template < class T > void write_field (::boost::property_tree::ptree& tree, const char* field, const T& value)
{   tree.put (field, value); }

template < class T > void write_field (::boost::property_tree::ptree& tree, const ::std::string& container, const char* field, const T& value)
{   ::std::string name (container);
    name += SEP;
    name += field;
    tree.put (name, value); }

bool read_header (::boost::property_tree::ptree& json, const ::std::string& expected, ::std::string& version, const ::std::string& filename);
void write_header (::boost::property_tree::ptree& json, const char* context);
bool replace_file (::boost::property_tree::ptree& json, ::boost::filesystem::path& filename);

inline ::std::string slash_dot (const ::std::string& slash)
{   ::std::string dot (slash);
    for (auto i = dot.begin (); i != dot.end (); ++i)
        if (*i == '/') *i = '.';
    return dot; }

::std::string fyi ();
::std::string ln (const int line);

inline void append (::std::string& base, const ::std::string& sep, const ::std::string& xtr, const ::std::string& explain = ::std::string ())
{   if (! xtr.empty ())
    {   if (! base.empty ()) base += sep;
        base += explain + xtr; }}

inline void prepend (::std::string& base, const ::std::string& sep, const ::std::string& xtr, const ::std::string& explain = ::std::string ())
{   if (! xtr.empty ())
        if (base.empty ()) base = xtr;
        else base = xtr + sep + explain + base; }

bool check_spelling (nitpick& nits, const html_version& v, const ::std::string& s);
bool ends_with_letters (const html_version& v,const ::std::string& s, const ::std::string& with);

inline bool is_hex (const ::std::string::const_iterator& x, const ::std::string::const_iterator& e)
{   if (x == e) return false;
    return ((*x >= '0') && (*x <= '9')) || ((*x >= 'A') && (*x <= 'F')) || ((*x >= 'a') && (*x <= 'f')); }

inline ::std::string substitute_char (::std::string& s, const char from, const char to)
{   ::std::string res;
    res.reserve (s.length ());
    for (::std::string::iterator i = s.begin (); i != s.end (); ++i)
        if (*i == from) res += to; else res += *i;
    return res; }