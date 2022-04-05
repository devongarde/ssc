/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "utility/common.h"
#include "utility/filesystem.h"
#include "utility/byteorder.h"
#include "main/context.h"
#include "main/args.h"
#include "icu/converter.h"

#define APP "app"
#define CONTEXT "context"
#define V "version"

::std::size_t which_one_of (const ::std::string& s, const vstr_t& v)
{   for (::std::size_t x = 0; x < v.size (); ++x)
        if (compare_no_case (s, v.at (x))) return x;
    return ::std::string::npos; }

bool is_one_of (const ::std::string& s, const vstr_t& v)
{   return (which_one_of (s, v) != ::std::string::npos); }

bool test_file (nitpick& nits, const ::boost::filesystem::path& name, uintmax_t& mz)
{   using namespace boost::filesystem;
    try
    {   path p (name);
        if (! exists (p)) nits.pick (nit_cannot_open, es_catastrophic, ec_io, PROG " cannot access ", name.string ());
        else if (! is_regular_file (p)) nits.pick (nit_cannot_open, es_catastrophic, ec_io, name.string (), " is not a normal file");
        else
        {   mz = file_size (p);
            if ((context.max_file_size () == 0) || (mz <= context.max_file_size ())) return true;
            nits.pick (nit_too_big, es_catastrophic, ec_io, name.string (), " is too big (reconfigure with " GENERAL MAXFILESIZE ")"); } }
    catch (...) { }
    return false; }

::std::string read_text_file (nitpick& nits, const ::boost::filesystem::path& name)
{   try
    {   ::boost::filesystem::path p (name);
        uintmax_t mz = 0;
        if (test_file (nits, p, mz))
            if (mz == 0) nits.pick (nit_empty, es_comment, ec_io, name.string (), " is empty");
            else
            {   ::boost::filesystem::ifstream f (name, ::std::ios_base::in);
                if (! f.bad ())
                {   ::std::stringstream sss;
                    sss << f.rdbuf ();
                    f.close ();
                    ::std::string res (sss.str ());
                    const e_charcode encoding = bom_to_encoding (get_byte_order (res));
                    if (encoding != cc_ansi)
#ifndef NOICU
                        if (! context.icu ())
#endif // NOICU
                        {   if (encoding != cc_utf8)
                            {   if (encoding == cc_fkd) nits.pick (nit_convert, es_error, ec_file, p.string (), " is in a strange format, so " PROG " cannot process it; " PROG " likes ASCII, ANSI & UTF-8");
                                else nits.pick (nit_convert, es_error, ec_file,  PROG " cannot convert ", p.string (), " to UTF-8, so cannot to process it");
                                res.clear (); } }
#ifndef NOICU
                        else if (encoding == cc_utf8)
                        {   nitpick nuts;
                            ::std::string norm = normalise_utf8 (nuts, res);
                            if (norm != res)
                            {   nits.pick (nit_normalise, es_warning, ec_icu, quote (p.string ()), " is not normalised.");
                                res = norm; } }
                        else
                        {   res.clear ();
                            uintmax_t sz = 0;
                            void_ptr vp (read_binary_file (nits, p, sz));
                            if (sz != 0)
                            {   VERIFY_NOT_NULL (vp.get (), __FILE__, __LINE__);
                                res = convert_to_utf8 (nits, p.string (), vp.get (), sz);
                                if (res.empty ())
                                    nits.pick (nit_convert, es_error, ec_file, PROG " cannot analyse ", p.string (), " because it's in a weird format; " PROG " likes ASCII, ANSI, UTF-8, & UTF-16");
                                else
                                    nits.pick (nit_convert, es_comment, ec_page, "Converted ", p.string (), " to UTF-8 internally"); } }
#endif // NOICU
                    return res; } } }
    catch (const ::std::exception& e)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "exception when reading ", name.string (), ": ", e.what ()); }
    catch (...)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "unknown exception when reading ", name.string ()); }
    return ::std::string (); }

::std::string read_text_file (nitpick& nits, const ::std::string& name)
{   return read_text_file (nits, ::boost::filesystem::path (name)); }

void_ptr read_binary_file (nitpick& nits, const ::boost::filesystem::path& name, uintmax_t& sz, const bool zero_ok)
{   using namespace boost::filesystem;
    FILE* fp = nullptr;
    sz = 0;
    try
    {   path p (name);
        uintmax_t mz = 0;
        if (test_file (nits, p, mz))
            if (mz == 0)
                if (zero_ok) nits.pick (nit_empty, es_comment, ec_io, name.string (), " is empty");
                else nits.pick (nit_empty, es_error, ec_io, name.string (), " is empty");
            else
            {   void_ptr vp (alloc_void_ptr (::gsl::narrow_cast < ::std::size_t > (mz)));
                if (vp.get () == nullptr) nits.pick (nit_out_of_memory, es_catastrophic, ec_io, "out of memory reading ", name.string ());
                else
                {   fp = fopen (name.string ().c_str (), "rb");
                    if (fp == nullptr) nits.pick (nit_cannot_open, es_catastrophic, ec_io, "cannot open ", name.string ());
                    else
                    {   const ::std::size_t rd = fread (vp.get (), 1, ::gsl::narrow_cast < ::std::size_t > (mz), fp);
                        fclose (fp); // if this fails there's sod all we can do about it, so ... :-)
                        fp = nullptr;
                        if (rd == mz) { sz = mz; return vp; }
                        if (rd == 0) nits.pick (nit_cannot_read, es_catastrophic, ec_io, "cannot read any of ", name.string ());
                        else nits.pick (nit_cannot_read, es_catastrophic, ec_io, "cannot read all of ", name.string ()); } } } }
    catch (const ::std::exception& e)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "exception when reading ", name.string (), ": ", e.what ());
        return void_ptr (); }
    catch (...)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "unknown exception when reading ", name.string ());
        return void_ptr (); }
    if (fp != nullptr) fclose (fp);
    return void_ptr (); }

bool write_text_file (const ::boost::filesystem::path& n, const ::std::string& content)
{   using namespace boost::filesystem;
    path p (n);
    p += ".tmp";
    try
    {   ofstream f (p);
        if (f.bad ())
        {   if (context.tell (es_catastrophic))
            {   context.err ("Cannot open temporary file ");
                context.err (p.string ());
                context.err ("\n"); }
            return false; }
        try
        {   f << content; }
        catch (...)
        {   if (context.tell (es_catastrophic))
            {   context.err ("Cannot write to temporary file ");
                context.err (p.string ());
                context.err ("\n"); }
            return false; }
        f.close ();
        if (file_exists (n))
            if (! delete_file (n))
            {   if (context.tell (es_catastrophic))
                {   context.err ("Cannot delete existing file ");
                    context.err (p.string ());
                    context.err ("\n"); }
                return false; }
        rename_file (p, n);
        return true; }
    catch (...) { }
    if (file_exists (p)) delete_file (p);
    if (context.tell (es_error))
    {   context.err ("Cannot update ");
        context.err (p.string ());
        context.err ("\n"); }
    return false; }

bool write_text_file (const ::std::string& name, const ::std::string& content)
{   return write_text_file (::boost::filesystem::path (name), content); }

::std::string trim_the_lot_off (const ::std::string& s)
{   return ::boost::trim_copy (s); }

::std::string unify_whitespace (const ::std::string& s)
{   bool whitespace = false;
    ::std::string res;
    for (auto ch : s)
        if (! ::std::iswspace (ch))
        {   whitespace = false; res += ::std::string (1, ch); }
        else if (! whitespace)
        {   whitespace = true; res += ::std::string (1, ' '); }
    return res; }

vstr_t split_by_charset (const ::std::string& s, const char* charset)
{   vstr_t v;
    ::boost::algorithm::split (v, s, ::boost::algorithm::is_any_of (charset), ::boost::algorithm::token_compress_on);
    return v; }

vstr_t split_by_string (const ::std::string& s, const ::std::string& splitter)
{   vstr_t v;
    ::boost::algorithm::find_all (v, s, splitter);
    return v; }

vstr_t split_by_whitespace_and (const ::std::string& s, const char* charset)
{   ::std::string cs;
    if (charset != nullptr) cs.assign (charset);
    vstr_t v;
    ::std::string current;
    bool started = false;
    bool quoted = false;
    bool slashed = false;
    bool deadzone = false;
    for (::std::string::const_iterator i = s.begin (); i != s.end (); ++i)
    {   const bool whitespace = ::std::iswspace (*i);
        if (::std::iswcntrl (*i) && ! whitespace) continue;
        if (slashed) { current += *i; slashed = false; continue; }
        if (*i == '\\') { slashed = started = true; continue; }
        else if (*i == '"')
        {   if (! started) started = true;
            if (! quoted) { quoted = true; continue; }
            if (quoted) { started = quoted = false; deadzone = true; v.push_back (current); current.clear (); continue; } }
        else if (whitespace || ((charset != nullptr) && (cs.find (*i) != ::std::string::npos)))
        {   deadzone = false;
            if (! started) continue;
            if (! quoted) { started = quoted = false; if (! current.empty ()) v.push_back (current); current.clear (); continue; } }
        if (deadzone) continue;
        if (! started) { started = true; quoted = false; }
        current += *i; }
    if (! current.empty ()) v.push_back (current);
    return v; }

bool remove_tail (::std::string& s, ::std::string& tail, const char ch)
{   const ::std::string::size_type pos = s.find (ch);
    tail.clear ();
    if (pos == ::std::string::npos) return false;
    if (pos < s.length () - 1) tail = trim_the_lot_off (s.substr (pos + 1));
    if (pos == 0) s.clear ();
    else s = trim_the_lot_off (s.substr (0, pos));
    return true; }

::std::string remove_tail (::std::string& s, const char ch)
{   ::std::string tail;
    const ::std::string::size_type pos = s.find (ch);
    if (pos != ::std::string::npos)
    {   if (pos < s.length () - 1) tail = trim_the_lot_off (s.substr (pos + 1));
        if (pos == 0) s.clear ();
        else s = trim_the_lot_off (s.substr (0, pos)); }
    return tail; }

bool remove_head (::std::string& s, ::std::string& head, const char ch)
{   const ::std::string::size_type pos = s.find_first_of (ch);
    head.clear ();
    if (pos == ::std::string::npos) return false;
    if (pos > 0) head = trim_the_lot_off (s.substr (0, pos));
    if (pos < s.length () - 1) s = trim_the_lot_off (s.substr (pos + 1));
    else s.clear ();
    return true; }

::std::string remove_head (::std::string& s, const char ch)
{   ::std::string head;
    const ::std::string::size_type pos = s.find_first_of (ch);
    if (pos != ::std::string::npos)
    {   if (pos > 0) head = trim_the_lot_off (s.substr (0, pos));
        if (pos < s.length () - 1) trim_the_lot_off (s = s.substr (pos + 1));
        else s.clear (); }
    return head; }

bool separate_last (const ::std::string& s, ::std::string& head, ::std::string& tail, const char ch)
{   tail.clear ();
    const ::std::string::size_type pos = s.find_last_of (ch);
    if (pos == ::std::string::npos) { head = s; return false; }
    if (pos > 0) head = trim_the_lot_off (s.substr (0, pos)); else head.clear ();
    if (pos < s.length () - 1) tail = trim_the_lot_off (s.substr (pos + 1));
    return true; }

bool separate_first (const ::std::string& s, ::std::string& head, ::std::string& tail, const char ch)
{   tail.clear ();
    const ::std::string::size_type pos = s.find_first_of (ch);
    if (pos == ::std::string::npos) { head = s; return false; }
    if (pos > 0) head = trim_the_lot_off (s.substr (0, pos)); else head.clear ();
    if (pos < s.length () - 1) tail = trim_the_lot_off (s.substr (pos + 1));
    return true; }

bool separate (const ::std::string& s, ::std::string& head, ::std::string& tail, const char ch)
{   return separate_last (s, head, tail, ch); }

bool one_of_domain (const ::std::string& s, const vstr_t& v)
{   if (s.empty () || v.empty ()) return false;
    if (s.at (s.length () - 1) != '/')
    {   for (auto d : v)
            if (::boost::algorithm::iends_with (s, d))
                return true;
        return false; }
    ::std::string ss (s.substr (0, s.length () - 1));
    for (auto d : v)
            if (::boost::algorithm::iends_with (s, d))
                return true;
    return false; }

::boost::filesystem::path get_tmp_filename ()
{   ::boost::filesystem::path model (temp_dir ());
    if (model.string ().empty ()) return ::boost::filesystem::path ();
    model /= ::boost::filesystem::unique_path ();
    model += "." PROG;
    return absolute_name (model); }

bool read_header (const ::boost::property_tree::ptree& json, const ::std::string& expected, ::std::string& version, const ::std::string& filename)
{   ::std::string prog = read_field < ::std::string > (json, APP);
    if (context.test ()) version = VERSION_STRING;
    else version = read_field < ::std::string > (json, VER);
    ::std::string con = read_field < ::std::string > (json, CONTEXT);
    if ((prog != PROG) || (version.substr (0, 3) != "0.0"))
    {   if (context.tell (es_error))
        {   context.err (filename);
            context.err (" is not an " PROG " file, or this copy of " PROG " (v" VERSION_STRING ") is too old to read it\n"); }
        return false; }
    if (! expected.empty ())
        if (con != expected)
        {   if (context.tell (es_error))
            {   ::std::ostringstream ss;
                ss << filename << " is not an " PROG " " << expected << " file\n";
                context.err (ss.str ()); }
            return false; }
    return true; }

void write_header (::boost::property_tree::ptree& json, const char* k)
{   write_field < ::std::string > (json, APP, PROG);
    if (! context.test ()) write_field < ::std::string > (json, VER, VERSION_STRING);
    write_field < ::std::string > (json, CONTEXT, k); }

bool replace_file (const ::boost::property_tree::ptree& json, const ::boost::filesystem::path& filename)
{   ::boost::filesystem::path tmp (filename), old (filename);
    tmp += ".tmp";
    old += ".old";
    if (! file_exists (filename))
    {   try
        {   ::boost::property_tree::write_json (filename.string (), json); }
        catch (...)
        {   delete_file (filename);
            if (context.tell (es_catastrophic))
            {   context.err ("Cannot write ");
                context.err (filename.string ());
                context.err ("\n"); }
            return false; } }
    else
    {   try
        {   ::boost::property_tree::write_json (tmp.string (), json);
            rename_file (filename, old); }
        catch (...)
        {   delete_file (tmp);
            if (context.tell (es_catastrophic))
            {   context.err ("Cannot write ");
                context.err (tmp.string ());
                context.err ("\n"); }
            return false; }
        if (! rename_file (tmp, filename))
        {   rename_file (old, filename);
            delete_file (tmp);
            if (context.tell (es_catastrophic))
            {   context.err ("Cannot replace ");
                context.err (filename.string ());
                context.err (" with ");
                context.err (tmp.string ());
                context.err ("\n"); }
            return false; }
       delete_file (old); }
    return true; }

::std::string fyi ()
{   return "    "; }

::std::string ln (const int line)
{   ::std::string res;
    if (line > 0)
    {   res = "[";
        res += ::boost::lexical_cast < ::std::string > (line);
        res += "] "; }
    return res; }


bool is_whitespace (const ::std::string::const_iterator b, const ::std::string::const_iterator e) noexcept
{   for (::std::string::const_iterator i = b; i != e; ++i)
        if (! ::std::iswspace (*i)) return false;
    return true; }

bool contains (const vstr_t& con, const ::std::string& val)
{   for (auto s : con)
        if (s == val) return true;
    return false; }

bool ends_with_letters (const html_version& v, const ::std::string& s, const ::std::string& with)
{   if (s.empty ()) return false;
    if (with.empty ()) return true;
    const ::std::string::size_type len = s.length ();
    const ::std::string::size_type wl = with.length ();
    if (wl > len) return false;
    if (v.xhtml ())
    {   if (! ::boost::ends_with (s, with)) return false; }
    else if (! ::boost::ends_with (::boost::to_lower_copy (s), ::boost::to_lower_copy (with))) return false;
    if (wl == len) return true;
    auto ch = s.at (len - wl - 1);
    return ! (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z'))); }

::std::string split_at_first_of (::std::string& sauce, const ::std::string& chars)
{   sauce = trim_the_lot_off (unify_whitespace (sauce));
    const ::std::string::size_type pos = sauce.find_first_of (chars);
    ::std::string res;
    if (pos != ::std::string::npos)
        if (pos == 0)
            sauce = sauce.substr (1);
        else if (pos == (sauce.length () - 1))
        {   res = trim_the_lot_off (sauce.substr (0, pos));
            sauce.clear (); }
        else
        {   res = trim_the_lot_off (sauce.substr (0, pos));
            sauce = trim_the_lot_off (sauce.substr (pos+1)); }
    return res; }

::std::string test_template_path (nitpick& nits, ::boost::filesystem::path p)
{   if (! ::boost::filesystem::exists (p))
        p.replace_extension ("nit");
    if (! ::boost::filesystem::exists (p))
        p.replace_extension ("tpl");
    if (! ::boost::filesystem::is_regular_file (p))
        return "";
    return read_text_file (nits, p.string ()); }

::std::string template_path (nitpick& nits, const ::std::string& fn)
{   PRESUME (! fn.empty (), __FILE__, __LINE__);
    ::boost::filesystem::path p (fn);
    const bool abs (p.is_absolute ());
    if (! abs) p = ::boost::filesystem::absolute (p);
    ::std::string res (test_template_path (nits, p));
    if (abs || ! res.empty ()) return res;
    if (! context.not_root ())
    {   p = ::boost::filesystem::absolute (fn, ::boost::filesystem::path (context.root ()));
        res = test_template_path (nits, p);
        if (! res.empty ()) return res; }
    p = ::boost::filesystem::absolute (fn, ::boost::filesystem::path (context.path ()));
    return test_template_path (nits, p); }

::std::string template_path (nitpick& nits, const ::std::string& def, const ::std::string& arg)
{   if (arg.empty ()) return template_path (nits, def);
    return template_path (nits, arg); }

::std::string once_twice_thrice (const ::std::size_t x)
{   switch (x)
    {   case 0 :
            return "unused";
        case 1 :
            return "once";
        case 2 :
            return "twice";
        case 3 :
            return "thrice";
        default :
            if (x >= UINT_MAX) return "many";
            return ::boost::lexical_cast < ::std::string > (x); } }
