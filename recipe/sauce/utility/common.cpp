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
#include "utility/common.h"
#include "main/context.h"
#include "main/args.h"

#define TEMP_FILE_MASK "%%%%-%%%%-%%%%-%%%%.tmp"

#define APP "app"
#define CONTEXT "context"
#define V "version"

bool compare_no_case (const std::string& a, const std::string& b)
{   if (a.length () != b.length ()) return false;
    return ::std::equal (b.begin (), b.end (), a.begin (), cnc_test); }

::std::size_t which_one_of (const ::std::string& s, const vstr_t& v)
{   for (::std::size_t x = 0; x < v.size (); ++x)
        if (compare_no_case (s, v [x])) return x;
    return ::std::string::npos; }

bool is_one_of (const ::std::string& s, const vstr_t& v)
{   return (which_one_of (s, v) != ::std::string::npos); }

uintmax_t test_file (const ::boost::filesystem::path& name)
{   using namespace boost::filesystem;
    try
    {   path p (name);
        if (exists (p) && is_regular_file (p))
        {   if (context.max_file_size () != 0)
            {   uintmax_t sz = file_size (p);
                if (sz < context.max_file_size ()) return sz; } } }
    catch (...) { }
    return 0; }

::std::string read_text_file (const ::boost::filesystem::path& name)
{   using namespace boost::filesystem;
    try
    {   path p (name);
        if (test_file (p) == 0) ::std::string ();
        ifstream f (name);
        if (! f.bad ())
        {   ::std::stringstream res;
            res << f.rdbuf ();
            f.close ();
            return res.str (); } }
    catch (...) { }
    return ::std::string (); }

::std::string read_text_file (const ::std::string& name)
{   return read_text_file (::boost::filesystem::path (name)); }

void_ptr read_binary_file (nitpick& nits, const ::boost::filesystem::path& name, uintmax_t& sz, const bool zero_ok)
{   using namespace boost::filesystem;
    FILE* fp = nullptr;
    sz = 0;
    try
    {   path p (name);
        uintmax_t mz = 0;
        if (! exists (p)) nits.pick (nit_cannot_open, es_catastrophic, ec_io, name.string (), " either does not exist or " PROG " cannot access it");
        else if (! is_regular_file (p)) nits.pick (nit_cannot_open, es_catastrophic, ec_io, name.string (), " is not a standard file");
        else
        {   mz = file_size (p);
            if (mz == 0)
                if (zero_ok) nits.pick (nit_empty, es_comment, ec_io, name.string (), " is empty");
                else nits.pick (nit_empty, es_error, ec_io, name.string (), " is empty");
            else if ((context.max_file_size () != 0) && (mz > context.max_file_size ()))
                nits.pick (nit_too_big, es_catastrophic, ec_io, name.string (), " is too big (reconfigure with " GENERAL MAXFILESIZE ")");
            else
            {   void_ptr vp (alloc_void_ptr (static_cast < ::std::size_t > (mz)));
                if (vp.get () == nullptr) nits.pick (nit_out_of_memory, es_catastrophic, ec_io, "out of memory reading ", name.string ());
                else
                {   fp = fopen (name.string ().c_str (), "rb");
                    if (fp == nullptr) nits.pick (nit_cannot_open, es_catastrophic, ec_io, "cannot open ", name.string ());
                    else
                    {   ::std::size_t rd = fread (vp.get (), 1, static_cast < ::std::size_t > (mz), fp);
                        fclose (fp); // if this fails there's sod all we can do about it, so ... :-)
                        fp = nullptr;
                        if (rd == mz) { sz = mz; return vp; }
                        if (rd == 0) nits.pick (nit_cannot_read, es_catastrophic, ec_io, "cannot read any of ", name.string ());
                        else nits.pick (nit_cannot_read, es_catastrophic, ec_io, "cannot read all of ", name.string ()); } } } } }
    catch (const ::std::exception& e)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "cannot open ", name.string (), ": ", e.what ());
        return void_ptr (); }
    catch (...)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "cannot open ", name.string ());
        return void_ptr (); }
    if (fp != nullptr) fclose (fp);
    return void_ptr (); }


bool write_text_file (const ::std::string& name, const ::std::string& content)
{   using namespace boost::filesystem;
    path n (name);
    path p (n);
    p += ".tmp";
    try
    {   ofstream f (p);
        if (f.bad ())
        {   if (context.tell (e_severe)) context.err () << "Cannot open temporary file " << p << "\n";
            return false; }
        try
        {   f << content; }
        catch (...)
        {   if (context.tell (e_severe)) context.err () << "Cannot write to temporary file " << p << "\n";
            return false; }
        f.close ();
        if (::boost::filesystem::exists (n))
            if (! ::boost::filesystem::remove (n))
            {   if (context.tell (e_severe)) context.err () << "Cannot delete existing file " << n << "\n";
                return false; }
        ::boost::filesystem::rename (p, n);
        return true; }
    catch (...) { }
    try
    {   if (::boost::filesystem::exists (p))
            ::boost::filesystem::remove (p); }
    catch (...) { }
    if (context.tell (e_error)) context.err () << "Cannot update " << n << "\n";
    return false; }

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

vstr_t split_quoted_by_space (const ::std::string& s)
{   vstr_t v;
    ::std::string current;
    bool started = false;
    bool quoted = false;
    bool slashed = false;
    bool deadzone = false;
    for (::std::string::const_iterator i = s.begin (); i != s.end (); ++i)
    {   if (::std::iswcntrl (*i)) continue;
        if (slashed) { current += *i; slashed = false; continue; }
        if (*i == '\\') { slashed = started = true; continue; }
        else if (*i == '"')
        {   if (! started) started = true;
            if (! quoted) { quoted = true; continue; }
            if (quoted) { started = quoted = false; deadzone = true; v.push_back (current); current.clear (); continue; } }
        else if (::std::iswspace (*i))
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


::boost::filesystem::path get_tmp_filename ()
{   ::boost::system::error_code ec;
#ifdef FS_THROWS
	::boost::filesystem::path model;
    try
	{	model = ::boost::filesystem::temp_directory_path(ec); }
	catch (...)
	{ return ::boost::filesystem::path(); }
#else
    ::boost::filesystem::path model (::boost::filesystem::temp_directory_path (ec));
    if (ec.failed ()) return ::boost::filesystem::path ();
#endif
    model /= TEMP_FILE_MASK;
    return ::boost::filesystem::unique_path (model); }

bool read_header (::boost::property_tree::ptree& json, const ::std::string& expected, ::std::string& version, const ::std::string& filename)
{   ::std::string prog = read_field < ::std::string > (json, APP);
    version = read_field < ::std::string > (json, V);
    ::std::string con = read_field < ::std::string > (json, CONTEXT);
    if ((prog != PROG) || (version.substr (0, 3) != "0.0"))
    {   if (context.tell (e_error)) context.err () << filename << " is not an " PROG " file, or this copy of " PROG " (v" VERSION_STRING ") is too old to read it\n";
        return false; }
    if (! expected.empty ())
        if (con != expected)
        {   if (context.tell (e_error)) context.err () << filename << " is not an " PROG " " << expected << " file\n";
            return false; }
    return true; }

void write_header (::boost::property_tree::ptree& json, const char* k)
{   write_field < ::std::string > (json, APP, PROG);
    write_field < ::std::string > (json, V, VERSION_STRING);
    write_field < ::std::string > (json, CONTEXT, k); }

bool replace_file (::boost::property_tree::ptree& json, ::boost::filesystem::path& filename)
{   ::boost::filesystem::path tmp (filename), old (filename);
    tmp += ".tmp";
    old += ".old";
    if (! ::boost::filesystem::exists (filename))
    {   try
        {   ::boost::property_tree::write_json (filename.string (), json); }
        catch (...)
        {   ::boost::filesystem::remove (filename);
            if (context.tell (e_severe)) context.err () << "Cannot write " << filename << "\n";
            return false; } }
    else
    {   try
        {   ::boost::property_tree::write_json (tmp.string (), json);
            ::boost::filesystem::rename (filename, old); }
        catch (...)
        {   ::boost::filesystem::remove (tmp);
            if (context.tell (e_severe)) context.err () << "Cannot write " << tmp << "\n";
            return false; }
        try
        {   ::boost::filesystem::rename (tmp, filename); }
        catch (...)
        {   ::boost::filesystem::rename (old, filename);
            ::boost::filesystem::remove (tmp);
            if (context.tell (e_severe)) context.err () << "Cannot replace " << filename << " with " << tmp << "\n";
            return false; }
       try
        {   ::boost::filesystem::remove (old); }
        catch (...) { } }
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

// for those who habitually spell correctly (unlike me)
bool check_spelling (nitpick& nits, const html_version& , const ::std::string& s)
{   typedef enum { d_none, d_johnson, d_anaesthesia, d_oz, d_collins, d_wiki } e_dictionary;
    const char* dictionary [] =
    {   nullptr,
        "Samuel Johnson, A Dictionary of the English Language, first edition, Longman etc., MDCCLV",
        "A Dictionary of Anaesthesia, second edition, Oxford University Press, 2017",
        "Australian Oxford Dictionary, second edition, Oxford University Press, 2004",
        "Collins English Dictionary",
        "wikipedia, https://en.wikipedia.org/" };
    struct spellings
    {   const char* spell_;
        e_dictionary dict_;
        const char* ref_; };
    spellings word [] =
    {   { "centre", d_johnson, "348" },
        { "colour", d_johnson, "409" },
        { "organisation", d_none, nullptr },

        { "alternative", d_none, nullptr },
        { "anaesthesia", d_anaesthesia, nullptr },
        { "autocapitalise", d_none, nullptr },
        { "authorise", d_oz, nullptr },
        { "behaviour", d_johnson, "225" },
        { "catalogue", d_johnson, "340" },
        { "colourist", d_none, nullptr },
        { "coworker", d_none, nullptr },
        { "dialogue", d_johnson, "585" },
        { "grey", d_collins, nullptr },
        { "gynaecologic", d_wiki, "https://en.wikipedia.org/wiki/Gynaecology" },
        { "haematologic", d_none, nullptr },
        { "honour", d_none, nullptr },
        { "licence", d_none, nullptr },
        { "motorised", d_none, nullptr },
        { "neighbour", d_johnson, "1356" },
        { "optimise", d_none, nullptr },
        { "organisation", d_none, nullptr },
        { "organiser", d_none, nullptr },
        { "organise", d_none, nullptr },
        { "paediatric", d_none, nullptr },
        { "parlour", d_johnson, "1452" },
        { "penciller", d_none, nullptr },
        { "randomised", d_none, nullptr },
        { "referrer", d_wiki, "https://en.wikipedia.org/wiki/HTTP_referer#Etymology" },
        { "speciality", d_johnson, "1895" },
        { "sought", d_none, nullptr },
        { "theatre", d_johnson, "2042" },
        { "tyre", d_none, nullptr },
        { nullptr, d_none, nullptr } };
    typedef ssc_map < ::std::string, spellings > map_of_correctness;
    static map_of_correctness ms;
    if (ms.empty ())
        for (::std::size_t i = 0; word [i].spell_ != nullptr; ++i)
            ms.insert (map_of_correctness::value_type (word [i].spell_, word [i]));
    ::std::string ss (::boost::algorithm::to_lower_copy (trim_the_lot_off (s)));
    map_of_correctness::const_iterator i = ms.find (ss);
    if (i != ms.cend ())
    {   if (i -> second.dict_ != d_none)
        {   ::std::string ref (dictionary [i -> second.dict_]);
            if (i -> second.ref_ != nullptr)
            {   ref += ", page ";
                ref += i -> second.ref_; }
            nits.pick (nit_correct_spelling, ed_dict, ref, es_info, ec_incorrectness, i -> second.spell_, " is spelt correctly"); }
        else nits.pick (nit_correct_spelling, es_info, ec_incorrectness, i -> second.spell_, " is spelt correctly");
        return true; }
    for (::std::size_t x = 0; word [x].spell_ != nullptr; ++x)
        if (ss.find (word [x].spell_) != ::std::string::npos)
        {   if (word [x].dict_ != d_none)
            {   ::std::string ref (dictionary [word [x].dict_]);
                if (word [x].ref_ != nullptr)
                {   ref += ", page ";
                    ref += word [x].ref_; }
                nits.pick (nit_correct_spelling, ed_dict, ref, es_info, ec_incorrectness, ss, " contains '", word [x].spell_, "', which is spelt correctly"); }
            else nits.pick (nit_correct_spelling, es_info, ec_incorrectness, ss, " contains '", word [x].spell_, "', which is spelt correctly");
            return true; }
    return false; }

bool is_whitespace (const ::std::string::const_iterator b, const ::std::string::const_iterator e)
{   for (::std::string::const_iterator i = b; i != e; ++i)
        if (! ::std::iswspace (*i)) return false;
    return true; }

bool contains (const vstr_t& con, const ::std::string& val)
{   for (auto s : con)
        if (s == val) return true;
    return false; }

bool ends_with_letters (const ::std::string& s, const ::std::string& with)
{   if (s.empty ()) return false;
    if (with.empty ()) return true;
    ::std::string::size_type len = s.length ();
    ::std::string::size_type wl = with.length ();
    if (wl > len) return false;
    if (! ::boost::ends_with (s, with)) return false;
    if (wl == len) return true;
    auto ch = s.at (len - wl - 1);
    return ! (((ch >= 'A') && (ch <= 'Z')) || ((ch >= 'a') && (ch <= 'z'))); }
