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
#include "utility/common.h"
#include "utility/filesystem.h"
#include "utility/byteorder.h"
#include "utility/lexical.h"
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
        else if (! is_normal_file (p)) nits.pick (nit_cannot_open, es_catastrophic, ec_io, name.string (), " is not a normal file");
        else
        {   mz = file_size (p);
            if ((context.max_file_size () == 0) || (mz <= context.max_file_size ())) return true;
            nits.pick (nit_too_big, es_catastrophic, ec_io, name.string (), " is too big (reconfigure with " GENERAL MAXFILESIZE ")"); } }
    catch (...) { }
    return false; }

::std::string read_text_file (nitpick& nits, const ::boost::filesystem::path& name, bool& borked)
{   borked = false;
    try
    {   ::boost::filesystem::path p (name);
        uintmax_t mz = 0;
        if (test_file (nits, p, mz))
            if (mz == 0) nits.pick (nit_empty, es_comment, ec_io, name.string (), " is empty");
            else
            {   BOOST_IFSTREAM_CNSTRO (f, name, ::std::ios_base::in);
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
                                borked = true;
                                res.clear (); } }
#ifndef NOICU
                        else if (encoding == cc_utf8)
                        {   nitpick nuts;
                            ::std::string norm = normalise_utf8 (nuts, res);
                            if (norm != res)
                            {   nits.pick (nit_normalise, es_warning, ec_icu, quote (p.string ()), " does not appear to be normalised UTF-8");
                                nits.pick (nit_normalise, es_debug, ec_icu, "differences: ", string_diff (res, norm, true));
                                res = norm; } }
                        else
                        {   res.clear ();
                            uintmax_t sz = 0;
                            void_ptr vp (read_binary_file (nits, p, sz));
                            if (sz != 0)
                            {   VERIFY_NOT_NULL (vp.get (), __FILE__, __LINE__);
                                res = convert_to_utf8 (nits, p.string (), vp, sz);
                                if (res.empty ())
                                {   nits.pick (nit_convert, es_error, ec_file, PROG " cannot analyse ", p.string (), " because it's in a weird format; " PROG " likes ASCII, ANSI, UTF-8, & UTF-16");
                                    borked = true; }
                                else
                                    nits.pick (nit_convert, es_comment, ec_page, "Converted ", p.string (), " to UTF-8 internally"); } }
#endif // NOICU
                    return res; } } }
    catch (const ::std::exception& e)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "exception when reading ", name.string (), ": ", e.what ()); }
    catch (...)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "unknown exception when reading ", name.string ()); }
    borked = true;
    return ::std::string (); }

::std::string read_text_file (nitpick& nits, const ::std::string& name, bool& borked)
{   return read_text_file (nits, ::boost::filesystem::path (name), borked); }

void_ptr read_binary_file (nitpick& nits, const ::boost::filesystem::path& name, uintmax_t& sz, const bool zero_ok)
{   using namespace boost::filesystem;
    if (name.empty ())
    {   outstr.err ("No filename to read\n");
        nits.pick (nit_cannot_open, es_catastrophic, ec_io, "No filename to read"); } 
    else
    {   FILE* fp = nullptr;
        sz = 0;
        try
        {   path p (name);
            uintmax_t mz = 0;
            if (test_file (nits, p, mz))
                if (mz == 0)
                    if (zero_ok) nits.pick (nit_empty, es_comment, ec_io, name.string (), " is empty");
                    else nits.pick (nit_empty, es_error, ec_io, name.string (), " is empty");
                else
                {   void_ptr vp (alloc_void_ptr (GSL_NARROW_CAST < ::std::size_t > (mz)));
                    if (vp.get () == nullptr) nits.pick (nit_out_of_memory, es_catastrophic, ec_io, "out of memory reading ", name.string ());
                    else
                    {   fp = fopen (name.string ().c_str (), "rb");
                        if (fp == nullptr) nits.pick (nit_cannot_open, es_catastrophic, ec_io, "cannot open ", quote (name.string ()), " [1]");
                        else
                        {   const ::std::size_t rd = fread (vp.get (), 1, GSL_NARROW_CAST < ::std::size_t > (mz), fp);
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
        if (fp != nullptr) fclose (fp); }
    return void_ptr (); }

bool write_text_file (nitpick& nits, const ::boost::filesystem::path& n, const ::std::string& content)
{   using namespace boost::filesystem;
    if (n.empty ())
    {   outstr.err ("No filename to write\n");
        nits.pick (nit_cannot_open, es_catastrophic, ec_io, "No filename to write"); }
    else
    {   path p (n);
        p += ".tmp";
        try
        {   BOOST_OFSTREAM_CNSTR (f, p);
            if (f.bad ())
            {   outstr.err ("Cannot open temporary file ", p.string (), "\n");
                nits.pick (nit_cannot_open, es_catastrophic, ec_io, "Cannot open temporary file ", p.string ()); 
                return false; }
            try
            {   f << content; }
            catch (...)
            {   outstr.err ("Cannot write to temporary file ", p.string (), "\n");
                nits.pick (nit_cannot_write, es_catastrophic, ec_io, "Cannot write to temporary file ", p.string ());
                return false; }
            f.close ();
            if (file_exists (n))
                if (! delete_file (n))
                {   outstr.err ("Cannot delete existing file ", p.string (), "\n");
                    nits.pick (nit_cannot_delete, es_catastrophic, ec_io, "Cannot delete existing file ", p.string ());
                    return false; }
            rename_file (p, n);
            return true; }
        catch (...) { }
        if (file_exists (p)) delete_file (p);
        if (context.tell (es_error))
        {   outstr.err ("Cannot update ", p.string (), "\n");
            nits.pick (nit_cannot_update, es_catastrophic, ec_io, "Cannot update ", p.string ()); } }
    return false; }

bool write_text_file (nitpick& nits, const ::std::string& name, const ::std::string& content)
{   return write_text_file (nits, ::boost::filesystem::path (name), content); }

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

int pos_de (const ::std::string& s, const char* charset, vint_t& vf, vint_t& vt, const bool empties)
{   const ::std::string cs (charset);
    const int len = GSL_NARROW_CAST < int > (s.length ());
    int prev = 0;
    vf.clear (); vt.clear ();
    for (int i = 0; i < len; ++i)
    {   const char ch = s.at (i);
        if (cs.find (ch))
        {   if (i - 1 != prev)
            {   vf.push_back (prev);
                vt.push_back (i - 1); }
            else if (empties)
            {   vf.push_back (-1);
                vt.push_back (-1); }
            prev = i+1; } }
    if (prev < len)
    {   vf.push_back (prev);
        vt.push_back (len); }
    return GSL_NARROW_CAST < int  > (vf.size ()); }

vstr_t split_by_whitespace_and (const ::std::string& s, const char* charset, const bool blank)
{   ::std::string cs;
    if (charset != nullptr) cs.assign (charset);
    PRESUME (cs.find_first_of ("\"\\") == ::std::string::npos, __FILE__, __LINE__);
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
        if (*i == '"')
        {   if (! started) started = true;
            if (! quoted) { quoted = true; continue; }
            if (quoted)
            {   started = quoted = false;
                deadzone = true;
                v.push_back (current);
                current.clear ();
                continue; } }
        else if (whitespace || ((charset != nullptr) && (cs.find (*i) != ::std::string::npos)))
        {   deadzone = false;
            if (! started) continue;
            if (! quoted)
            {   started = quoted = false;
                if (blank || ! current.empty ()) v.push_back (current);
                current.clear ();
                continue; } }
        if (deadzone) continue;
        if (! started) { started = true; quoted = false; }
        current += *i; }
    if (blank || ! current.empty ()) v.push_back (current);
    return v; }

vstr_t separate_by_whitespace_and (const ::std::string& s, const char* charset, const bool blank)
{   ::std::string cs;
    if (charset != nullptr) cs.assign (charset);
    PRESUME (cs.find_first_of ("\"\\") == ::std::string::npos, __FILE__, __LINE__);
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
        if (*i == '"')
        {   if (! started) started = true;
            if (! quoted) { quoted = true; continue; }
            if (quoted)
            {   started = quoted = false; 
                deadzone = true;
                v.push_back (current);
                current.clear ();
                continue; } }
        else if (whitespace)
        {   deadzone = false;
            if (! started) continue;
            if (! quoted)
            {   started = quoted = false;
                if (blank || ! current.empty ()) v.push_back (current);
                current.clear ();
                continue; } }
        else if ((charset != nullptr) && (cs.find (*i) != ::std::string::npos))
        {   deadzone = false;
            if (! quoted)
            {   started = quoted = false;
                if (blank || ! current.empty ()) v.push_back (current);
                current.clear ();
                v.push_back (::std::string (1, *i));
                continue; } }
        if (deadzone) continue;
        if (! started) { started = true; quoted = false; }
        current += *i; }
    if (blank || ! current.empty ()) v.push_back (current);
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
    model += JOIN DEF_TEMP_EXT;
    return absolute_name (model); }

bool read_header (nitpick& nits, const ::boost::property_tree::ptree& json, const ::std::string& expected, ::std::string& version, const ::std::string& filename)
{   ::std::string prog = read_field < ::std::string > (json, APP);
    if (context.test ()) version = VERSION_STRING;
    else version = read_field < ::std::string > (json, VERSION);
    ::std::string con = read_field < ::std::string > (json, CONTEXT);
    if ((prog != PROG) || (version.substr (0, 3) != "0.0"))
    {   if (context.tell (es_error))
        {   outstr.err (filename, " is not an " PROG " file, or this copy of " PROG " (v" VERSION_STRING ") is too old to read it\n");
            nits.pick (nit_not_ssc, es_error, ec_io, filename, " is not an " PROG " file, or this copy of " PROG " (v" VERSION_STRING ") is too old to read it"); }
        return false; }
    if (! expected.empty ())
        if (con != expected)
        {   if (context.tell (es_error))
            {   ::std::ostringstream ss;
                ss << filename << " is not an " PROG " " << expected << " file\n";
                outstr.err (ss.str ());
                nits.pick (nit_not_ssc, es_error, ec_io, ss.str ()); }
            return false; }
    return true; }

void write_header (::boost::property_tree::ptree& json, const char* k)
{   write_field < ::std::string > (json, APP, PROG);
    if (! context.test ()) write_field < ::std::string > (json, VERSION, VERSION_STRING);
    write_field < ::std::string > (json, CONTEXT, k); }

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
{   if (! file_exists (p)) p.replace_extension ("nit");
    if (! file_exists (p)) p.replace_extension ("tpl");
    if (! is_normal_file (p)) return "";
    bool borked = false;
    return read_text_file (nits, p.string (), borked); }

::std::string template_path (nitpick& nits, const ::std::string& fn)
{   PRESUME (! fn.empty (), __FILE__, __LINE__);
    ::boost::filesystem::path p (fn);
    const bool abs (p.is_absolute ());
    if (! abs) p = absolute_name (p);
    ::std::string res (test_template_path (nits, p));
    if (abs || ! res.empty ()) return res;
    if (! context.not_root ())
    {   p = absolute_name (fn, context.rootp ());
        res = test_template_path (nits, p);
        if (! res.empty ()) return res; }
    p = absolute_name (fn, ::boost::filesystem::path (context.path ()));
    return test_template_path (nits, p); }

::std::string template_path (nitpick& nits, const ::std::string& def, const ::std::string& arg)
{   if (arg.empty ()) return template_path (nits, def);
    return template_path (nits, arg); }

::std::string delined (::std::string::const_iterator b, ::std::string::const_iterator e)
{   ::std::string res;
    for (auto i = b; i < e; ++i)
        switch (*i)
        {   case '\n' :
            case ' ' :
            case '\t' :
            case '\v' : res += ' '; break;
            case '\a' :
            case '\b' :
            case '\r' : break;
            default :
                if (*i < 127)
                    if (*i >= ' ')
                        if (::std::isgraph (*i) || ! ::std::iscntrl (*i))
                            res += *i; }
    return res; }

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator from, ::std::string::const_iterator to)
{   BOOST_STATIC_ASSERT (DEFAULT_LINE_LENGTH - 16 <= INT8_MAX);
    CONSTEXPR int maxish = DEFAULT_LINE_LENGTH - 16;
    if ((to - from) > INT8_MAX) return ::std::string (from, to);
    const int len = GSL_NARROW_CAST < int > (to - from);
    if (len >= maxish) return ::std::string (from, to);
    const int halfish = (maxish - len) / 2;
    ::std::string pre, post;
    ::std::string::const_iterator mb, me;
    if ((e - b) <= maxish) { me = e; mb = b; }
    else
    {   if ((b + halfish) >= from) mb = b; else { mb = from - halfish; pre =ELLIPSES; }
        if ((e - halfish) <= to) me = e; else { me = to + halfish; post = ELLIPSES; } }
    if (from == to) return pre + delined (mb, me) + post;
    return pre + delined (mb, from) + " " BEFORE_MOTE " " + delined (from, to) + " " AFTER_MOTE " " + delined (to, me) + post; }

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i)
{   return near_here (b, e, i, i); }

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i, const ::std::string& msg, const e_severity level)
{   if (msg.empty () || ! context.tell (level)) return ::std::string ();
    ::std::string res (near_here (b, e, i));
    if (! res.empty ()) res += "\n";
    res += fyi () + msg + "\n";
    return res; }

void merge_smsid (smsid_t& a, const smsid_t& b, bool sum)
{   for (auto id : b)
    {   auto i = a.find (id.first);
        if (sum && (i != a.cend ())) i -> second += id.second;
        else a.insert (id); } }

void merge_smsid (smsid_t& a, const sstr_t& b, const ::std::size_t n)
{   for (auto id : b)
    {   auto i = a.find (id);
        if (i != a.cend ()) i -> second += n;
        else a.insert (smsid_t::value_type (id, n)); } }

void insert_smsid (smsid_t& a, const ::std::string& s, const ::std::size_t n)
{   auto i = a.find (s);
    if (i != a.cend ()) i -> second += n;
    else a.insert (smsid_t::value_type (s, n)); }

sstr_t smsid_set (const smsid_t& s)
{   sstr_t res;
    for (auto i : s)
        res.emplace (i.first);
    return res; }

// from https://stackoverflow.com/questions/55271662/c11-how-to-convert-a-hex-string-into-unicode-string
int hex_value (const ::std::string_view str) {
    ::std::stringstream stream {};
    stream << ::std::hex << str;
    int res;
    stream >> res;
    return res; }

::std::string enhtml (const ::std::string& s)
{   ::std::string res;
    for (::std::string::const_iterator i = s.begin (); i != s.end (); ++i)
        switch (*i)
        {   case '<' : res += "&lt;"; break;
            case '>' : res += "&gt;"; break;
            case '&' : res += "&amp;"; break;
            case ' ' : res += "&nbsp;"; break;
            default :  res += *i; break; }
    return res; }

bool is_plain_old_integer (const ::std::string& ss)
{   if (ss.find_first_not_of (SIGNEDINTEGER " ") != ::std::string::npos) return false;
    if ((ss.length () > 1) && (ss.substr (1).find_first_of (PLUSMINUS) == ::std::string::npos)) return false;
    if ((ss.length () == 1) && (ss.at (0) != SIGNPLUS) && (ss.at (0) != SIGNMINUS)) return false;
    return true; }

bool is_plain_old_decimal (const ::std::string& ss)
{   if (ss.find_first_not_of (SIGNEDDECIMAL " ") != ::std::string::npos) return false;
    if ((ss.length () > 1) && (ss.substr (1).find_first_of (PLUSMINUS) == ::std::string::npos)) return false;
    if (ss.length () == 1)
        switch (ss.at (0))
        {   case SIGNPLUS :
            case SIGNMINUS :
            case DOT :
                return false;
            default :
                break; }
    return true; }

::std::string sweeten (const ::std::string& s)
{   ::std::string res;
    for (auto ch : s)
        if ((ch >= ' ') && (ch < 127))
            res += ch;
    return res; }

::std::string get_account ()
{   static ::std::string u;
    if (! context.account ().empty ())
        return context.account ();
    if (! u.empty ()) return u;
#ifdef _MSC_VER
    char uname [ARGLEN_MAX] = { 0 };
    DWORD umax = ARGLEN_MAX-1;
#ifdef GETUSERNAMEEX
    if (    ::GetUserNameExA (NameUserPrincipal, uname, &umax) ||
            ::GetUserNameExA (NameSamCompatible, uname, &umax) ||
            ::GetUserNameA (uname, &umax))
#else // GETUSERNAMEEX
    if (::GetUserNameA (uname, &umax))
#endif // GETUSERNAMEEX
    {   GSL_AT (uname, umax) = 0; 
        u = uname; }
#else // _MSC_VER
    // https://stackoverflow.com/questions/8953424/how-to-get-the-username-in-c-c-in-linux
    uid_t uid = geteuid ();
    struct passwd *pw = getpwuid (uid);
    if (pw != nullptr)
        u = pw -> pw_name;
#endif // _MSC_VER
    return u; }

::std::string diff_snippet (const ::std::string& s, const ::std::string::size_type from, const ::std::string::size_type to, const ::std::string::size_type len, const bool numeric)
{   ::std::string res;
    constexpr ::std::string::size_type sweet = 5;
    if (from < sweet) res += s.substr (0, from);
    else
    {   res += "... ";
        res += s.substr (from-sweet, sweet); }
    res += " >>> ";
    if (numeric)
    {   bool next = false;
        for (auto ch : s.substr (from, to-from))
        {   if (next) res += ","; else next = true;
            res += ::boost::lexical_cast < ::std::string > (static_cast < unsigned > (ch)); } }  
    else res += s.substr (from, to-from);
    res += " <<< ";
    if (to + sweet >= len) res += s.substr (to);
    else
    {   res += s.substr (to, sweet);
        res += " ..."; }
    return res; }

::std::string report_diff (
                    const ::std::string& lhs, const ::std::string::size_type lfrom, const ::std::string::size_type lto, const ::std::string::size_type llen,
                    const ::std::string& rhs, const ::std::string::size_type rfrom, const ::std::string::size_type rto, const ::std::string::size_type rlen,
                    const bool knew, const bool numeric)
{   ::std::string res;
    if (! knew) res += ";";
    res += diff_snippet (lhs, lfrom, lto, llen, numeric);
    res += ",";
    res += diff_snippet (rhs, rfrom, rto, rlen, numeric);
    return res; }       

::std::string string_diff (const ::std::string& lhs, const ::std::string& rhs, const bool numeric)
{   ::std::string res;
    const ::std::string::size_type llen (lhs.length ());
    const ::std::string::size_type rlen (rhs.length ());
    ::std::string::size_type ls = ::std::string::npos, rs = ::std::string::npos, ns = ::std::string::npos;
    ::std::string::size_type l = 0, r = 0;
    while ((l < llen) && (r < rlen))
        if (lhs.at (l) != rhs.at (r))
        {   if (ls == ::std::string::npos)
            {   ns = ls = l++;
                rs = r; }
            else if (++l == llen)
            {   if (++r == rlen) return res + report_diff (lhs, ls, llen, llen, rhs, rs, rlen, rlen, res.empty (), numeric);
                l = ns++; } } 
        else 
        {   if (ls != ::std::string::npos)
            {   res += report_diff (lhs, ls, l, llen, rhs, rs, r, rlen, res.empty (), numeric);
                ls = rs = ns = ::std::string::npos; }
            ++l; ++r; }
    if (ls != ::std::string::npos)
        return res + report_diff (lhs, ls, l, llen, rhs, rs, r, rlen, res.empty (), numeric);
    if ((l < llen) || (r < rlen))
        return res + report_diff (lhs, ls, llen, llen, rhs, rs, rlen, rlen, res.empty (), numeric);
    return res; }
