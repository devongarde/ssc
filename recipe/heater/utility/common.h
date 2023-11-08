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
#include "main/enum.h"
#include "parser/html_version.h"

struct true_type { };
struct false_type { };

typedef uint64_t ident_t;
typedef uint32_t uid_t;
CONSTEXPR uid_t uid_max = UINT32_MAX;

typedef ::std::vector < int > vint_t;
typedef ::std::vector < double > vdbl_t;
typedef ::std::vector < ::std::string > vstr_t;
typedef ::std::vector < vstr_t > vvstr_t;
typedef ssc_set < ::std::string > sstr_t;
typedef ssc_map < ::std::string, ::std::string > ustr_t;
typedef ssc_map < ::std::string, ::std::size_t > msid_t;
typedef ::std::map < ::std::string, ::std::size_t > smsid_t;
typedef ssc_map < ::std::size_t, ::std::string > misd_t;
typedef ustr_t::value_type ustrv_t;
typedef ::std::basic_string < char32_t > string32;
typedef ::std::basic_stringstream < char32_t > stringstream32;
#ifndef NO_BOOST_REGEX
typedef ::boost::basic_regex < char > wild_t;
typedef ::std::vector < wild_t > vwild_t;
#endif // NO_BOOST_REGEX

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26408)
#endif // _MSC_VER
typedef ::std::shared_ptr < void > void_ptr;
struct really_free { void operator () (void *p) noexcept { free (p); } };
inline void_ptr alloc_void_ptr (const ::std::size_t sz) { return void_ptr (malloc (sz), really_free ()); }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

CONSTEXPR uint32_t uint32_category_shift =  28;
CONSTEXPR uint32_t uint32_item_mask =       0x0FFFFFFF;
CONSTEXPR uint32_t uint32_category_mask =   0xF0000000;

#define TALLY_TO_MAX(tot,inc,mx) \
    {   if (tot < mx) \
            if (mx - tot <= inc) tot = mx; \
            else tot += inc; }

template < class T > class reverter
{   T& p_;
    const T t_;
public:
    reverter () = delete;
    NO_COPY_CONSTRUCTORS (reverter);
    explicit reverter (T& t) : p_ (t), t_ (t) { }
    ~reverter () { if (p_ != t_) p_ = t_; } };

CONSTEXPR inline uint32_t ndx_category (const uint32_t x) noexcept { return (x & uint32_category_mask) >> uint32_category_shift; }
CONSTEXPR inline uint32_t ndx_item (const uint32_t x) noexcept { return (x & uint32_item_mask); }

::std::string trim_the_lot_off (const ::std::string& s);
bool remove_tail (::std::string& s, ::std::string& tail, const char ch);
bool remove_head (::std::string& s, ::std::string& head, const char ch);
::std::string remove_tail (::std::string& s, const char ch);
::std::string remove_head (::std::string& s, const char ch);
::std::string unify_whitespace (const ::std::string& s);
bool separate_first (const ::std::string& s, ::std::string& head, ::std::string& tail, const char ch);
bool separate_last (const ::std::string& s, ::std::string& head, ::std::string& tail, const char ch);
bool separate (const ::std::string& s, ::std::string& head, ::std::string& tail, const char ch);
bool one_of_domain (const ::std::string& s, const vstr_t& v);

inline ::std::string tart (const ::std::string& s)
{   return unify_whitespace (trim_the_lot_off (s)); }

vstr_t split_by_charset (const ::std::string& s, const char* charset);
vstr_t split_by_whitespace_and (const ::std::string& s, const char* charset = nullptr);
inline vstr_t split_quoted_by_space (const ::std::string& s)
{   return split_by_whitespace_and (s); }
inline vstr_t split_by_comma_space (const ::std::string& s)
{   return split_by_whitespace_and (s, ","); }
inline vstr_t split_by_space (const ::std::string& s)
{   return split_by_charset (s, " "); }
inline vstr_t split_by_newline (const ::std::string& s)
{   return split_by_charset (s, "\n"); }
vstr_t split_by_string (const ::std::string& s, const ::std::string& splitter);
vstr_t separate_by_whitespace_and (const ::std::string& s, const char* charset);

int pos_de (const ::std::string& s, const char* charset, vint_t& vf, vint_t& vt, const bool empties = false);

::std::string read_text_file (nitpick& nits, const ::boost::filesystem::path& name, bool& borked);
::std::string read_text_file (nitpick& nits, const ::std::string& name, bool& borked);
void_ptr read_binary_file (nitpick& nits, const ::boost::filesystem::path& name, uintmax_t& sz, const bool zero_ok = false);
bool write_text_file (const ::boost::filesystem::path& n, const ::std::string& content);
bool write_text_file (const ::std::string& name, const ::std::string& content);
::boost::filesystem::path get_tmp_filename ();
bool contains (const vstr_t& con, const ::std::string& val);

inline bool cnc_test (unsigned char a, unsigned char b) noexcept
{ return ::std::tolower (a) == ::std::tolower (b); }

inline bool compare_no_case (const std::string& a, const std::string& b)
{   if (a.length () != b.length ()) return false;
    return ::std::equal (b.begin (), b.end (), a.begin (), cnc_test); }

bool is_one_of (const ::std::string& s, const vstr_t& v);
::std::size_t which_one_of (const ::std::string& s, const vstr_t& v);
bool is_whitespace (const ::std::string::const_iterator b, const ::std::string::const_iterator e) noexcept;
inline bool is_whitespace (const ::std::string& s) noexcept { return is_whitespace (s.cbegin (), s.cend ()); }

template < class T > T read_field (const ::boost::property_tree::ptree& tree, const char* field)
{   return tree.get (field, T ()); }

template < class T > T read_field (const ::boost::property_tree::ptree& tree, const ::std::string& container, const char* field)
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

bool read_header (const ::boost::property_tree::ptree& json, const ::std::string& expected, ::std::string& version, const ::std::string& filename);
void write_header (::boost::property_tree::ptree& json, const char* context);
bool replace_file (const ::boost::property_tree::ptree& json, const ::boost::filesystem::path& filename);

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

inline ::std::string prepend (const ::std::string& pre, const ::std::string& base)
{   return pre + base; }

inline ::std::string wrap (const ::std::string& pre, const ::std::string& base, const ::std::string& post)
{   return pre + base + post; }

bool ends_with_letters (const html_version& v,const ::std::string& s, const ::std::string& with);

inline bool is_hex (const ::std::string::const_iterator& x, const ::std::string::const_iterator& e) noexcept
{   if (x == e) return false;
    return ((*x >= '0') && (*x <= '9')) || ((*x >= 'A') && (*x <= 'F')) || ((*x >= 'a') && (*x <= 'f')); }

inline ::std::string substitute_char (::std::string& s, const char from, const char to)
{   ::std::string res;
    res.reserve (s.length ());
    for (::std::string::iterator i = s.begin (); i != s.end (); ++i)
        if (*i == from) res += to; else res += *i;
    return res; }

::std::string split_at_first_of (::std::string& sauce, const ::std::string& chars);

inline ::std::string decolonise (::std::string& sauce)
{   return split_at_first_of (sauce, ":"); }

::std::string template_path (nitpick& nits, const ::std::string& fn);
::std::string template_path (nitpick& nits, const ::std::string& def, const ::std::string& arg);

template < class T, T MAX = UINT_MAX > ::std::string once_twice_thrice (const T x)
{   switch (x)
    {   case 1 : return "once";
        case 2 : return "twice";
        case 3 : return "thrice";
        default :
            if (x >= MAX) return "many times";
            return ::boost::lexical_cast < ::std::string > (x) + " times"; } }

inline ::std::string x_dot_y (int x, int y)
{   ::std::string res;
    res += ::boost::lexical_cast < ::std::string > (x);
    res += ".";
    res += ::boost::lexical_cast < ::std::string > (y);
    return res; }

inline ::std::string x_dot_y (const unsigned short mjr, const unsigned short mnr)
{   ::std::string res (::boost::lexical_cast < ::std::string > (static_cast < int > (mjr)));
    res += ".";
    res += ::boost::lexical_cast < ::std::string > (static_cast < int > (mnr));
    return res; }

inline ::std::string x_dot_y_ish (const unsigned short mjr, const unsigned short mnr)
{   ::std::string res (::boost::lexical_cast < ::std::string > (static_cast < int > (mjr)));
    if (mnr > 0)
    {   res += ".";
        res += ::boost::lexical_cast < ::std::string > (static_cast < int > (mnr)); }
    return res; }

inline void extend (vstr_t& v, const vstr_t& w)
{   for (auto s : w) v.emplace_back (s); }

#ifdef NOMERGE
template < class T > inline void merge_stuff (T& o, const T& s)
{   for (auto a : s)  o.insert (a); }
#endif // NOMERGE

::std::string delined (::std::string::const_iterator b, ::std::string::const_iterator e);
inline ::std::string delined (const ::std::string& s)
{   return delined (s.cbegin (), s.cend ()); }

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i);
::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator from, ::std::string::const_iterator to);
::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i, const ::std::string& msg, const e_severity level = es_comment);

void merge_smsid (smsid_t& a, const smsid_t& b, bool sum = true);
void merge_smsid (smsid_t& a, const sstr_t& b, const ::std::size_t n = 0);
void insert_smsid (smsid_t& a, const ::std::string& s, const ::std::size_t n = 0);
sstr_t smsid_set (const smsid_t& s);

template < class P > struct fiddlesticks
{   P** p_ = nullptr;
    P* twas_ = nullptr;
    fiddlesticks () = delete;
    DEFAULT_NO_COPY_NO_MOVE (fiddlesticks);
    explicit fiddlesticks (P** p, P* x) : p_ (p)
    {   VERIFY_NOT_NULL (p, __FILE__, __LINE__);
        twas_ = *p_;
        *p_ = x; }
    ~fiddlesticks () { *p_ = twas_; } };

template < > struct fiddlesticks < bool >
{   bool twas_ = false;
    bool* b_ = nullptr;
    fiddlesticks () = delete;
    DEFAULT_NO_COPY_NO_MOVE (fiddlesticks);
    explicit fiddlesticks (bool* b, const bool x)
    {   VERIFY_NOT_NULL (b, __FILE__, __LINE__);
        b_ = b;
        twas_ = *b_;
        *b_ = x; }
    ~fiddlesticks () { *b_ = twas_; } };

int hex_value (const ::std::string_view str);

inline constexpr ::std::size_t stp (const int i, const int n = 1)
{   const ::std::size_t res (i);
    return res + n; }

inline constexpr ::std::size_t stm (const int i, const int n = 1)
{   const ::std::size_t res (i);
    return res - n; }

inline constexpr ::std::size_t stt (const int i, const int n = 2)
{   const ::std::size_t res (i);
    return res * n; }

template < e_css_val_fn K, e_css_val_fn T, e_css_val_fn... TS > struct in_list
{   static bool yes ()
    {   return in_list < K, T > :: yes () || in_list < K, TS... > :: yes (); } }; 

template < e_css_val_fn K, e_css_val_fn T > struct in_list < K, T >
{   static bool yes ()
    {   return false; } };

template < e_css_val_fn K > struct in_list < K, K >
{   static bool yes ()
    {   return true; } };

template < e_css_val_fn T, e_css_val_fn... TS > struct listed
{   static bool yes (const e_css_val_fn t)
    {   if (T == t) return true;
        return listed < TS... > :: yes (t); } };

template < e_css_val_fn T > struct listed < T >
{   static bool yes (e_css_val_fn t)
    {   return T == t; } };

inline ::std::string::size_type find_no_case (const ::std::string& s, const ::std::string& x)
{   if (s.empty () || x.empty ()) return ::std::string::npos;
    return ::boost::to_lower_copy (s).find (::boost::to_lower_copy (x)); }
