/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
https://dylanharris.org/

this program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence,  or
(at your option) any later version.

this program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

// this is godawful mess; were it more than it is, ....

// parameters: either names of test specification files, or -f file, where file contains a list of filenames
// -h and -V do the usual

// 1. find test info, which specifies switches to use and expected results
// 2. Run ssc and receive results; include timeout mechanism
// 3. Check: (a) version [ must correspond to test program ]
//           (b) results
// 4. report PASS, FAIL or MIXED (no tests listed failed, but there were extra results)

// expected results format:
// first line switches to use
// remaining lines each contain
// line number, error name

#include "main/include.h"
#include "feedback/nitnames.h"

#define MAXOUTPUTFILESIZE 1024 * 1024 *64
#define FAUX_CMD "---xxx---"
#define ERROR_EXIT 3

typedef ::std::vector < ::boost::filesystem::path > filelist;
typedef ::std::vector < ::std::string > vstr_t;

typedef ::std::vector < e_nit > nits;
typedef ::std::map < size_t, nits > nitted;
struct nitwit
{   nitted          nits_;
    unsigned        flags_ = 0; };
typedef ::std::map < ::std::string, nitwit > knotted;

typedef ::std::map < ::std::string, int > classic_t;
typedef ::std::set < ::std::string > sstr_t;
typedef ::std::map < ::std::string, vstr_t > mvstr_t;

#define NW_FAIL     1
#define NW_IGNORE   2

unsigned verbose = 0;
bool numbers = false, easy_in = false, only_check_exports = false;
::std::string expected_lynx, expected_shadow, expected_export_errors, examinations;
//classic_t expected_classes;
// sstr_t expected_itemids;
// vstr_t correct_export, created_export, grand_stats;
//mvstr_t page_stats;
::boost::filesystem::path grand_stats_fn;

vstr_t readlines (const ::std::string& name)
{   vstr_t res;
    if (verbose > 1) ::std::cout << "\n>>> " << name << ":\n";
    ::std::ifstream ifs (name);
    if (ifs.bad ())
    {   ::std::cerr << "cannot open " << name << "\n"; return res; }
    else
    {   constexpr int maxlen = 8191;
        char sz [maxlen+1] = { 0 };
        while (! ifs.fail ())
        {   ifs.getline (sz, maxlen);
            sz [maxlen] = 0;
            if (verbose > 1)
                ::std::cout << sz << "\n";
            res.push_back (sz); } }
    if (verbose > 1) ::std::cout << ">>>\n\n";
    return res; }

bool testfile (const ::boost::filesystem::path& s, const ::std::string& context = ::std::string ())
{   if (only_check_exports || (s == SNIPPET)) return true;
    if (! ::boost::filesystem::exists (s))
    {   ::std::cerr << "cannot find " << s << ::std::endl << context << "\n"; return false; }
    else if (! ::boost::filesystem::is_regular_file (s))
    {   ::std::cerr << "cannot load " << s << ::std::endl << context << "\n"; return false; }
    return true; }

bool testxeq (const ::boost::filesystem::path& s, const ::std::string& context = ::std::string ())
{   if (! ::boost::filesystem::exists (s))
    {   ::std::cerr << "cannot find " << s << ::std::endl << context << "\n"; return false; }
    return true; }

bool load_file_list (char* name, filelist& specs)
{   if (! testfile (name)) return false;
    vstr_t lines (readlines (name));
    if (lines.empty ()) return true;
    for (auto s : lines)
        if (! s.empty ())
            if (! testfile (s, ::std::string (" (in ") +  name + ")")) return false;
            else specs.push_back (s);
    return true; }

::std::string tim (const e_nit nit)
{   if (! numbers)
    {   const ::std::string& s = lookup_name (nit);
        if (! s.empty ())
            if (verbose < 2) return s;
            else
            {   ::std::string res (s + " (");
                res += ::boost::lexical_cast < ::std::string > (static_cast < size_t > (nit));
                return res + ")"; } }
    return ::boost::lexical_cast < ::std::string > (static_cast < size_t > (nit)); }

bool load_expected (const ::boost::filesystem::path& f, knotted& expected, ::std::string& cmdline, classic_t& expected_classes, sstr_t& expected_itemids, mvstr_t& page_stats, vstr_t& correct_export, vstr_t& created_export, vstr_t& grand_stats)
{   correct_export.clear ();
    created_export.clear ();
    if (! testfile (f)) return false;
    vstr_t spec (readlines (f.string ()));
    if (spec.empty ())
    {   ::std::cerr << "no content found in " << f << "\n"; return false; }
    cmdline.clear ();
    if (grand_stats_fn.empty ()) grand_stats_fn = f.parent_path () / "grand.stats";
    nits_init ();
    nitwit expect;
    ::std::string previous;
    int line = 0;
    bool lynx = false;
    bool classed = false;
    bool itemid = false;
    bool exports = false;
    bool examine = false;
    bool exporterrors = false;
    bool file_stats = false;
    bool only = false;
    bool overall_stats = false;
    bool shadow = false;
    sstr_t correct_set, created_set;
    vstr_t stats;
    size_t last_line = static_cast < size_t > (-1);
    nits last_nits;
    for (auto ss : spec)
    {   ++line;
        ::std::string s (::boost::trim_copy (ss));
        bool done = s.empty ();
        if (file_stats || overall_stats)
        {   done = (s == END_OF_STATS); }
        if (done)
        {   if (! last_nits.empty ()) expect.nits_.insert (::nitted::value_type (last_line, last_nits));
            last_line = static_cast < size_t > (-1);
            last_nits.clear ();
            if (file_stats && ! stats.empty () && ! previous.empty ())
            {   page_stats.insert (mvstr_t::value_type (previous, stats));
                stats.clear (); }
            exports = itemid = file_stats = overall_stats = false;
            continue; }
        if (overall_stats)
        {   grand_stats.push_back (s);
            continue; }
        if (file_stats)
        {   stats.push_back (s);
            continue; }
        if ((! itemid) && (s.at (0) == '#')) continue;
        if (lynx)
        {   lynx = false;
            expected_lynx = s;
            continue; }
        if (shadow)
        {   shadow = false;
            expected_shadow = s;
            continue; }
        if (exporterrors)
        {   exporterrors = false;
            expected_export_errors = s;
            continue; }
        if (itemid)
        {   expected_itemids.insert (s);
            continue; }
        if (examine)
        {   examine = false;
            examinations = s;
            continue; }
        const ::std::string::size_type spaced = s.find (' ');
        if (exports || only)
        {   if ((spaced == ::std::string::npos) || spaced == (s.length () - 1))
            {   ::std::cerr << "missing created filename among " << s << " on line "<< line << " of " << f.string () << "\n"; return false; }
            if (spaced == 0)
            {   ::std::cerr << "missing correct filename among " << s << " on line "<< line << " of " << f.string () << "\n"; return false; }
            ::std::string lhs (s.substr (0, spaced));
            ::std::string rhs (s.substr (spaced+1));
            if (correct_set.find (lhs) != correct_set.cend ())
            {   ::std::cerr << "duplicate correct filename " << lhs << " on line "<< line << " of " << f.string () << "\n"; return false; }
            if (created_set.find (rhs) != created_set.cend ())
            {   ::std::cerr << "duplicate created filename " << rhs << " on line "<< line << " of " << f.string () << "\n"; return false; }
            if (! ::boost::filesystem::exists (lhs))
            {   ::std::cerr << "missing correct file " << lhs << " on line "<< line << " of " << f.string () << "\n"; return false; }
            if (! ::boost::filesystem::is_regular_file (lhs))
            {   if (verbose) ::std::cout << "correct " << lhs << " is not a normal file\n"; return false; }
            correct_set.insert (lhs);
            created_set.insert (rhs);
            correct_export.push_back (lhs);
            created_export.push_back (rhs);
            continue; }
        if (classed)
        {   if ((spaced == ::std::string::npos) || spaced == (s.length () - 1))
            {   ::std::cerr << "missing class count on line "<< line << " of " << f.string () << "\n"; return false; }
            if (spaced == 0)
            {   ::std::cerr << "missing class name on line "<< line << " of " << f.string () << "\n"; return false; }
            ::std::string n (s.substr (0, spaced));
            int c = -1;
            try
            {   c = ::boost::lexical_cast < int > (s.substr (spaced + 1)); }
            catch (...) { }
            if (c < 0)
            {   ::std::cerr << "bad class count on line "<< line << " of " << f.string () << "\n"; return false; }
            auto res = expected_classes.insert (::classic_t::value_type (n, c));
            if (! res.second)
            {   ::std::cerr << "class '" << n << "' repeated on line "<< line << " of " << f.string () << "\n"; return false; }
            continue; }
        if (cmdline.empty ()) { cmdline = s; continue; }
        else switch (s.at (0))
        {   case 'C' :  classed = true; examine = exporterrors = shadow = lynx = itemid = exports = file_stats = only = overall_stats = false; continue;
            case 'E' :  exports = true; examine = exporterrors = shadow = classed = lynx = itemid = file_stats = only = overall_stats = false; continue;
            case 'e' :  exporterrors = true; examine = exports = shadow = classed = lynx = itemid = file_stats = only = overall_stats = false; continue;
            case 'G' :  overall_stats = true; examine = exporterrors = shadow = classed = lynx = exports = itemid = file_stats = only = false; continue;
            case 'i' :  itemid = true; examine = exporterrors = shadow = classed = lynx = exports = file_stats = only = overall_stats = false; continue;
            case 'L' :  lynx = true; examine = exporterrors = shadow = classed = itemid = exports = file_stats = only = overall_stats = false; continue;
            case 'S' :  file_stats = true; stats.clear (); examine = exporterrors = shadow = classed = lynx = exports = itemid = only = overall_stats = false; continue;
            case 's' :  shadow = true; examine = exporterrors = lynx = classed = itemid = exports = file_stats = only = overall_stats = false; continue;
            case 'u' :  examine = true; exporterrors = exports = shadow = classed = lynx = itemid = file_stats = only = overall_stats = false; continue;
            case 'O' :  only_check_exports = only = true; examine = exporterrors = exports = shadow = classed = lynx = itemid = file_stats = overall_stats = false; continue;
            case 'I' :
            case 'F' :
            case 'P' :
            case '*' :
                {   examine = exporterrors = exports = shadow = classed = lynx = itemid = only = file_stats = overall_stats = false;
                    if (! previous.empty ()) expected.insert (knotted::value_type (previous, expect));
                    if (spaced == ::std::string::npos)
                    {   ::std::cerr << "missing filename " << s << " at line "<< line << " of " << f.string () << "\n"; return false; }
                    ::std::string fn (::boost::trim_copy (s.substr (spaced)));
                    if (! testfile (fn)) return false;
                    expect.flags_ = (s.at (0) == 'F') ? NW_FAIL : 0;
                    expect.flags_ += (s.at (0) == 'I') ? NW_IGNORE : 0;
                    previous = fn;
                    expect.nits_.clear (); }
                continue;
            default : break; }
        if (spaced == ::std::string::npos)
        {   ::std::cerr << "unexpected content " << s << " at line "<< line << " of " << f.string () << "\n"; return false; }
        size_t lno = 0;
        try
        {   lno = ::boost::lexical_cast < size_t > (s.substr (0, spaced)); }
        catch (...)
        {   ::std::cerr << "invalid line number " << s << " at line "<< line << " of " << f.string () << "\n"; return false; }
        vstr_t v;
        ::std::string sss (s.substr (spaced));
        ::boost::algorithm::split (v, sss, ::boost::algorithm::is_space (), ::boost::algorithm::token_compress_on);
        if (v.empty ())
        {   ::std::cerr << s << " has no feedback list (line "<< line << " of " << f.string () << ")\n"; return false; }
        if (last_line != lno)
        {   if (! last_nits.empty ()) expect.nits_.insert (::nitted::value_type (last_line, last_nits));
            last_line = lno; last_nits.clear (); }
        for (auto n : v)
        {   if (n.empty ()) continue;
            ::boost::trim (n);
            const e_nit en = lookup_code (n);
            if (en == nit_off) ::std::cerr << "no such feedback as '" << n << "' (line "<< line << " of " << f.string () << ")\n";
            else last_nits.push_back (en); } }
    if (! last_nits.empty ()) expect.nits_.insert (::nitted::value_type (last_line, last_nits));
    if (! expect.nits_.empty () && ! previous.empty ())
        expected.insert (knotted::value_type (previous, expect));
    if (file_stats && ! stats.empty () && ! previous.empty ())
        page_stats.insert (mvstr_t::value_type (previous, stats));
    return true; }

::std::string list_feedback (const nits& ns)
{   ::std::string res;
    for (auto n : ns)
    {   if (! res.empty ()) res += ", ";
        res += tim (n); }
    return res; }

bool examine_results_header (vstr_t& results, const ::boost::filesystem::path& tmp)
{   if (results.size () < 3)
    {   if (verbose) ::std::cout << "too little output ( " << tmp.string () << ")\n"; return false; }
    if (results.at (0) != PROG)
    {   if (verbose) ::std::cout << "not " PROG ": expected '" PROG "', got '" << results.at (0) << "' (" << tmp.string () << ")\n"; return false; }
    if (results.at (1) != VERSION_STRING)
    {   if (verbose) ::std::cout << "this copy of " TESTPROG " can only test " PROG " version " VERSION_STRING ", not version " << results.at (1) << " (" << tmp.string () << ")\n"; return false; }
    return true; }

bool examine_results_one_file (const ::std::string& fn, nitted& expect, nitted& got)
{   nitted::const_iterator ie = expect.begin ();
    nitted::const_iterator ig = got.begin ();
    bool res = true;
    while ((ie != expect.cend ()) || (ig != got.cend ()))
    {   if ((ig == got.cend ()) || (( ie != expect.cend ()) && (ig -> first > ie -> first)))
        {   if (verbose) ::std::cout << PROG " does not report expected errors in " << fn << " on line " << ie -> first << ": " << list_feedback (ie -> second) << "\n";
            res = false; ++ie; }
        else if ((ie == expect.cend ()) || ((ig != got.cend ()) && (ie -> first > ig -> first)))
        {   if (verbose) ::std::cout << PROG " has found unexpected errors in " << fn << " on line " << ig -> first << ": " << list_feedback (ig -> second) << "\n";
            res = false; ++ig; }
        else
        {   nits::const_iterator e = ie -> second.cbegin ();
            nits::const_iterator g = ig -> second.cbegin ();
            nits::const_iterator ee = ie -> second.cend ();
            nits::const_iterator eg = ig -> second.cend ();
            ::std::string unexpected, unreported, ei;
            while ((e != ee) && (g != eg))
            {   if (easy_in)
                {   if (! ei.empty ()) ei += " ";
                    ei += tim (*g); }
                if ((g == eg) || (*g > *e))
                {   if (! unreported.empty ()) unreported += " ";
                    unreported += tim (*e);
                    ++e; res = false; }
                else if ((e == ee) || (*e > *g))
                {   if (! unexpected.empty ()) unexpected += " ";
                    unexpected += tim (*g);
                    ++g; res = false; }
                else if (*e == *g)
                {   ++e; ++g; } }
            while (e != ee)
            {   if (! unreported.empty ()) unreported += " ";
                unreported += tim (*e);
                ++e; res = false; }
            while (g != eg)
            {   if (easy_in)
                {   if (! ei.empty ()) ei += " ";
                    ei += tim (*g); }
                if (! unexpected.empty ()) unexpected += " ";
                unexpected += tim (*g);
                ++g; res = false; }
            ::std::string nbr = ::boost::lexical_cast < ::std::string > (ie -> first);
            if (! unreported.empty ())
                if (verbose) ::std::cout << PROG " does not report error(s) in " << fn << " on line " << nbr << ": " << unreported << "\n";
            if (! unexpected.empty ())
                if (verbose) ::std::cout << PROG " reports unexpected error(s) in " << fn << " on line " << nbr << ": " << unexpected << "\n";
            if (easy_in && ! ei.empty ())
                if (! unexpected.empty () || ! unreported.empty ())
                    ::std::cout << nbr << " " << ei << "\n";
            ++ie; ++ig; } }
    return res; }

bool examine_results_once (knotted& expected, nitwit& expect, nitted& got, const ::std::string& fn, unsigned& passed, unsigned& failed)
{   bool res = true;
    if (! expect.nits_.empty () || ! got.empty ())
    {   if (examine_results_one_file (fn, expect.nits_, got) != (expect.flags_ == 0))
        {   ++failed; res = false; } else ++passed;
        expect.nits_.clear ();
        got.clear ();
        if (! fn.empty ()) expected.erase (fn); }
    return res; }

bool crosslinks (const vstr_t& line)
{   vstr_t expected;
    bool blooper = false;
    ::boost::algorithm::split (expected, expected_lynx, ::boost::algorithm::is_space (), ::boost::algorithm::token_compress_on);
    expected_lynx.clear ();
    if (line.size () == expected.size ())
    {   for (size_t x = 1; x < line.size () && ! blooper; ++x)
            if (line.at (x) != expected.at (x))
            {   blooper = true;
                if (verbose) ::std::cout << "crosslink " << x << " differs (expected " << expected.at (x) << ", got " << line.at (x) << ")\n"; }
        if (! blooper) return true; }
    else if (verbose) ::std::cout << "crosslink counts differ (expected " << expected.size () - 1 << ", got " << line.size () - 1 << ")\n";
    return false; }

bool shadowcheck (const vstr_t& line)
{   vstr_t expected;
    bool blooper = false;
    ::boost::algorithm::split (expected, expected_shadow, ::boost::algorithm::is_space (), ::boost::algorithm::token_compress_on);
    expected_shadow.clear ();
    if (line.size () == expected.size ())
    {   for (size_t x = 1; x < line.size () && ! blooper; ++x)
        {   ::std::string n (expected.at (x));
            ::boost::trim (n);
            const e_nit en = lookup_code (n);
            if (en == nit_off) ::std::cerr << "no such feedback as '" << n << "' (in shadow)\n";
            else if (::boost::lexical_cast < int > (line.at (x)) != static_cast < int > (en))
            {   blooper = true;
                if (verbose) ::std::cout << "shadow " << x << " differs (expected " << static_cast < int > (en) << ", got  " << line.at (x) << ")\n"; } }
        if (! blooper) return true; }
    else if (verbose) ::std::cout << "shadows differ (expected " << expected.size () - 1 << ", got " << line.size () - 1 << ")\n";
    return false; }

bool exporterrorcheck (const vstr_t& line)
{   vstr_t expected;
    bool blooper = false;
    ::boost::algorithm::split (expected, expected_export_errors, ::boost::algorithm::is_space (), ::boost::algorithm::token_compress_on);
    expected_export_errors.clear ();
    if (line.size () == expected.size ())
    {   for (size_t x = 1; x < line.size () && ! blooper; ++x)
        {   ::std::string n (expected.at (x));
            ::boost::trim (n);
            const e_nit en = lookup_code (n);
            if (en == nit_off) ::std::cerr << "no such feedback as '" << n << "' (in exports expected)\n";
            else if (::boost::lexical_cast < int > (line.at (x)) != static_cast < int > (en))
            {   blooper = true;
                if (verbose) ::std::cout << "export errors " << x << " differs (expected " << expected.at (x) << ", got  " << line.at (x) << ")\n"; } }
        if (! blooper) return true; }
    else if (verbose) ::std::cout << "export errors differ (expected " << expected.size () - 1 << ", got " << line.size () - 1 << ")\n";
    return false; }

bool classcheck (vstr_t& line, classic_t& expected_classes)
{   classic_t::iterator i = expected_classes.find (line.at (0));
    if (i == expected_classes.end ())
    {   if (verbose) ::std::cout << "unexpected class " << line.at (0) << " encountered\n"; return false; }
    const int e = i -> second;
    int c = -1;
    try
    {   c = ::boost::lexical_cast < int > (line.at (1)); }
    catch (...) { }
    expected_classes.erase (i);
    if (c < 0)
    {   if (verbose) ::std::cout << "program error: bad count '" << line.at (1) << "' for class " << line.at (0) << " encountered\n"; return false; }
    if (c != e)
    {   if (verbose) ::std::cout << "class " << line.at (0) << ": expected " << e << ", got " << c << "\n"; return false; }
    return true; }

bool examinecheck (vstr_t& line)
{   vstr_t expected;
    bool blooper = false;
    ::boost::algorithm::split (expected, examinations, ::boost::algorithm::is_space (), ::boost::algorithm::token_compress_on);
    examinations.clear ();
    if (line.size () == expected.size ())
    {   for (size_t x = 1; x < line.size () && ! blooper; ++x)
        {   ::std::string n (expected.at (x));
            ::boost::trim (n);
            const e_nit en = lookup_code (n);
            if (en == nit_off) ::std::cerr << "no such feedback as '" << n << "' (in shadow)\n";
            else if (::boost::lexical_cast < int > (line.at (x)) != static_cast < int > (en))
            {   blooper = true;
                if (verbose) ::std::cout << "update " << x << " differs (expected " << static_cast < int > (en) << ", got " << line.at (x) << ")\n"; } }
        if (! blooper) return true; }
    else if (verbose) ::std::cout << "update counts differ (expected " << expected.size () - 1 << ", got " << line.size () - 1 << ")\n";
    return false; }

bool itemidcheck (vstr_t& line, sstr_t& expected_itemids)
{   sstr_t::iterator i = expected_itemids.find (line.at (0));
    if (i == expected_itemids.end ())
    {   if (verbose) ::std::cout << "unexpected itemid " << line.at (0) << " encountered\n"; return false; }
    expected_itemids.erase (i);
    return true; }

int check_exports (vstr_t& correct_export, vstr_t& created_export)
{   if (created_export.size () != correct_export.size ())
    {   ::std::cout << "internal error: created and correct exports have a different count ("
            << created_export.size () << ", " << correct_export.size () << ")\n";
        return 1; }
    int res = 0;
    for (size_t x = 0; x < correct_export.size (); ++x)
    {   if (! ::boost::filesystem::exists (created_export.at (x)))
        {   if (verbose) ::std::cout << "export " << created_export.at (x) << " not created\n";
            ++res; continue; }
        if (! ::boost::filesystem::exists (correct_export.at (x)))
        {   if (verbose) ::std::cout << "correct " << created_export.at (x) << " deleted\n";
            ++res; continue; }
        if (! ::boost::filesystem::is_regular_file (created_export.at (x)))
        {   if (verbose) ::std::cout << "export " << created_export.at (x) << " is not a normal file\n";
            ++res; continue; }
        if (! ::boost::filesystem::is_regular_file (correct_export.at (x)))
        {   if (verbose) ::std::cout << "correct " << created_export.at (x) << " is no longer a normal file\n";
            ++res; continue; }
        uintmax_t created_size (::boost::filesystem::file_size (created_export.at (x)));
        uintmax_t correct_size (::boost::filesystem::file_size (correct_export.at (x)));
        if (created_size !=  correct_size)
        {   if (verbose) ::std::cout << created_export.at (x) << " file size incorrect ("
                         << created_size << ", should be "<< correct_size << ")\n";
            ++res; continue; }
        if (created_size > 0)
        {   vstr_t created_lines (readlines (created_export.at (x)));
            vstr_t correct_lines (readlines (correct_export.at (x)));
            if (created_lines.size () != correct_lines.size ())
            {   if (verbose) ::std::cout << created_export.at (x) << " has wrong line count ("
                             << created_lines.size () << ", should be "<< correct_lines.size () << ")\n";
                ++res; continue; }
            for (size_t y = 0; y < created_lines.size (); ++y)
                if (created_lines.at (y) != correct_lines.at (y))
                {   if (verbose) ::std::cout << created_export.at (x) << " has wrong content at line " << y << "\n";
                    ++res; break; } } }
    return res; }

bool compare_stats (const vstr_t& expected, const vstr_t& got, const ::std::string& name)
{   if (expected.empty ())
    {   if (verbose) ::std::cout << name << " has no stats\n"; return false; }
    if (got.empty ())
    {   if (verbose) ::std::cout << name << " has unexpected stats\n"; return false; }
    vstr_t::const_iterator master = expected.cbegin ();
    vstr_t::const_iterator test = got.cbegin ();
    int n = 1;
    while ((master != expected.cend ()) && (test != got.cend ()))
    {   ::std::string trim_master = ::boost::trim_copy (*master);
        if (trim_master.empty ()) { ++master; continue; }
        ::std::string trim_test = ::boost::trim_copy (*test);
        if (trim_test.empty ()) { ++test; continue; }
        if (trim_master != trim_test)
        {   if (verbose) ::std::cout << name << " stats differ on line " << n << " (expected '" << *master << "', got '" << *test <<"')\n"; return false; }
        ++master; ++test; ++n; }
    while (master != expected.cend ())
    {   ::std::string trim_master = ::boost::trim_copy (*master);
        if (! trim_master.empty ()) break;
        ++master; }
    while (test != got.cend ())
    {   ::std::string trim_test = ::boost::trim_copy (*test);
        if (! trim_test.empty ()) break;
        ++test; }
    if (master != expected.cend ())
    {   if (verbose) ::std::cout << name << " stats too short (expected lines " << expected.size () << ", got lines " << got.size () <<")\n"; return false; }
    if (test != got.cend ())
    {   if (verbose) ::std::cout << name << " stats too long (expected lines " << expected.size () << ", got lines " << got.size () <<")\n"; return false; }
   return true; }

bool check_file_stats (const ::boost::filesystem::path& fn, const vstr_t& file, mvstr_t& page_stats)
{   mvstr_t::const_iterator i = page_stats.find (fn.string ());
    if (i == page_stats.cend ())
    {   if (verbose) ::std::cout << "no stats expected for " << fn << "\n";
        return false; }
    return compare_stats (i -> second, file, fn.string ()); }

bool check_overall_stats (const vstr_t& overall, vstr_t& grand_stats)
{   return compare_stats (grand_stats, overall, "grand"); }

bool examine_results (knotted& expected, vstr_t& results, unsigned& passed, unsigned& failed, classic_t& expected_classes, const ::boost::filesystem::path& tmp, sstr_t& expected_itemids, mvstr_t page_stats, vstr_t& correct_export, vstr_t& created_export, vstr_t& grand_stats)
{   bool res = true;
    if (! only_check_exports)
    {   if (! examine_results_header (results, tmp)) return false;
        nitted got;
        nitwit expect;
        ::std::string fn, previous;
        bool shush = false;
        bool shadow = false;
        bool examine = false;
        bool exporterrors = false;
        bool classes = false;
        bool lynx = false;
        bool oops = false;
        bool itemid = false;
        bool file_stats = false;
        bool overall_stats = false;
        vstr_t overall, file;
        for (size_t r = 3; r < results.size (); ++r)
        {   vstr_t line;
            bool done = results.at (r).empty ();
            if (file_stats || overall_stats)
            {   done = (results.at (r) == END_OF_STATS); }
            if (done)
            {   if (! file.empty ())
                {   if (! previous.empty ()) if (! check_file_stats (previous, file, page_stats)) { ++failed; res = false; }
                    file.clear (); }
                file_stats = overall_stats = false; continue; }
            if (overall_stats) { overall.push_back (results.at (r)); continue; }
            if (file_stats) { file.push_back (results.at (r)); continue; }
            ::boost::algorithm::split (line, results.at (r), ::boost::algorithm::is_space (), ::boost::algorithm::token_compress_on);
            if (line.empty ())
            {   if (! file.empty ())
                {   if (! previous.empty ()) if (! check_file_stats (previous, file, page_stats)) { ++failed; res = false; }
                    file.clear (); }
                file_stats = overall_stats = false; continue; }
            if (line.size () < 2)
            {   if (verbose) ::std::cout << "missing content in output " << results.at (0) << "\n"; res = false; }
            if (results.at (r).at (0) != '*')
            {   if (shush) continue;
                if (lynx)
                {   if (! crosslinks (line)) { oops = true; res = false; }
                    lynx = false; shush = true; continue; }
                if (shadow)
                {   if (! shadowcheck (line)) { oops = true; res = false; }
                    shadow = false; shush = true; continue; }
                if (exporterrors)
                {   if (! exporterrorcheck (line)) { oops = true; res = false; }
                    exporterrors = false; shush = true; continue; }
                if (classes)
                {   if (! classcheck (line, expected_classes)) { oops = true; res = false; }
                    continue; }
                if (examine)
                {   if (! examinecheck (line)) { oops = true; res = false; }
                    continue; }
                if (itemid)
                {   if (! itemidcheck (line, expected_itemids)) { oops = true; res = false; }
                    continue; }
                if (fn.empty ())
                {   if (verbose) ::std::cout << "expecting filename near beginning of output file\n"; res = false; }
                size_t ln;
                try
                {   ln = ::boost::lexical_cast < size_t > (line.at (0)); }
                catch (...)
                {   if (verbose) ::std::cout << "in " << fn << ", expecting line number in " << results.at (r) << "\n";
                    res = false; }
                nits ns;
                auto ii = got.find (ln);
                if (ii != got.cend ())
                {   ns = ii -> second;
                    got.erase (ii); }
                for (size_t n = 1; n < line.size (); ++n)
                {   e_nit en = nit_off;
                    try
                    {   en = static_cast < e_nit > (::boost::lexical_cast < size_t > (line.at (n))); }
                    catch (...)
                    {   if (verbose) ::std::cout << "in " << fn << ", expecting error codes in " << results.at (r) << "\n";
                        res = false; }
                    if (en >= nit_off)
                    {   if (verbose)
                            ::std::cout <<  "in " << fn << ", unexpected error code " << static_cast < size_t > (en) <<
                                            " in " << results.at (r) << "; is " TESTPROG " up to date?\n";
                        res = false; }
                    ns.push_back (en); }
                got.insert (nitted::value_type (ln, ns)); }
            else
            {   if (! file.empty ())
                {   if (! fn.empty ()) if (! check_file_stats (fn, file, page_stats)) { ++failed; res = false; }
                    file.clear (); }
                classes = lynx = itemid = file_stats = overall_stats = false;
                if (shush) shush = false;
                else if (! examine_results_once (expected, expect, got, fn, passed, failed)) res = false;
                else if (oops) { oops = false; ++failed; }
                fn = ::boost::trim_copy (line.at (1));
                if (fn.empty ())
                {   if (verbose) ::std::cout << "missing filename in output\n"; res =  false; ++failed; }
                knotted::const_iterator i = expected.find (fn);
                if (i == expected.end ())
                {   if (fn == "classes") classes = true;
                    else if (fn == "link") lynx = true;
                    else if (fn == "itemids") itemid = true;
                    else if (fn == "update") examine = true;
                    else if (fn == "shadow") shadow = true;
                    else if (fn == "exports") exporterrors = true;
                    else if (fn == "Statistics") file_stats = true;
                    else if (fn == "Grand") overall_stats = true;
                    else
                    {   if (verbose) ::std::cout << "results for unexpected file " << fn << " found\n";
                        res = false; ++failed;
                        fn.clear (); shush = true; } }
                else
                {   previous = fn;
                    expect = i -> second;
                    if ((expect.flags_ & NW_IGNORE) != 0) shush = true; } } }
        if (! file.empty ()) if (! previous.empty ()) if (! check_file_stats (previous, file, page_stats)) { ++failed; res = false; }
        if (! overall.empty () || ! grand_stats.empty ())
        {   if (! check_overall_stats (overall, grand_stats)) { ++failed; res = false; }
            overall.clear (); grand_stats.clear (); }
        page_stats.clear ();
        if (! examine_results_once (expected, expect, got, fn, passed, failed)) res = false;
        else if (oops) { ++failed; oops = false; }
        for (knotted::const_iterator i = expected.begin (); i != expected.end (); ++i)
        {   if (verbose) ::std::cout << "results for " << i -> first << " not found\n";
            res = false; ++failed; }
        if (! expected_classes.empty ())
        {   res = false;
            oops = true;
            if (verbose)
                for (auto i : expected_classes)
                    ::std::cout << "class " << i.first << " missing\n"; }
        if (! expected_itemids.empty ())
        {   res = false;
            oops = true;
            if (verbose) 
                for (auto i : expected_itemids)
                    ::std::cout << "itemid " << i << " missing\n"; }
        if (oops) ++failed; }
    int x = check_exports (correct_export, created_export);
    if (x != 0)
    {   res = false; failed += x; }
    return res; }

int run_test (const ::boost::filesystem::path& f, const ::boost::filesystem::path& xeq, bool rmtmp, const ::std::string& tmppath, const ::std::string& pre, unsigned& passed, unsigned& failed)
{   knotted expected;
    classic_t expected_classes;
    sstr_t expected_itemids;
    mvstr_t page_stats;
    vstr_t correct_export, created_export, grand_stats;
    if (verbose && ! ::boost::filesystem::exists (xeq))
    {   ::std::cout << "Current path: " << ::boost::filesystem::current_path ().string () << "\n";
        ::std::cout << "Cannot see " << xeq.string () << " as specified\n"; }
    ::std::string cmdline;
    if (! load_expected (f, expected, cmdline, expected_classes, expected_itemids, page_stats, correct_export, created_export, grand_stats))
    {   ::std::cerr << "cannot interpret " << f << "\n";
        return ERROR_EXIT; }
    if ((cmdline == FAUX_CMD) && pre.empty ())
    {   ::std::cerr << f << " is intended for " << TESTPROG << " testing, and requires a previously prepared input file (e.g. use -i switch)";
        return false; }
    ::boost::filesystem::path tmp;
    int post_res = 0, pre_res = 0;
    if (! pre.empty ()) tmp = pre;
    else
    {   if (tmppath.empty ()) tmp = ::boost::filesystem::temp_directory_path ();
        else tmp = tmppath;
        tmp /= ::boost::filesystem::unique_path ();
        tmp += "." PROG;
        ::boost::filesystem::path prepare = canonical (absolute (f));
        prepare.remove_filename ();
        ::boost::filesystem::path clean = prepare;
        ::std::string switched = xeq.string () + ::std::string (" -T ");
        if (! only_check_exports)
        {   switched += "-o "; switched += tmp.string () + " "; }
        cmdline = switched + cmdline;
#if defined (UNIX)
        prepare /= "pre.sh";
        clean /= "post.sh";
        ::boost::filesystem::file_status stat;
        if (::boost::filesystem::exists (prepare))
        {   stat = ::boost::filesystem::status (prepare);
            if ((stat.permissions () & ::boost::filesystem::perms::owner_exe) == 0)
                ::boost::filesystem::permissions (prepare, ::boost::filesystem::perms::owner_exe | ::boost::filesystem::perms::add_perms); }
        if (::boost::filesystem::exists (clean))
        {   stat = ::boost::filesystem::status (clean);
            if ((stat.permissions () & ::boost::filesystem::perms::owner_exe) == 0)
                ::boost::filesystem::permissions (clean, ::boost::filesystem::perms::owner_exe | ::boost::filesystem::perms::add_perms); }
#else // UNIX
        prepare /= "pre.bat";
        clean /= "post.bat";
#endif // UNIX
        if (::boost::filesystem::exists (prepare))
        {   if (verbose) ::std::cout << prepare.string () << "\n";
            pre_res = system (prepare.string ().c_str ());
            if (pre_res > 0)
            {   ::std::cerr << "test prepare script '" << prepare.string () << "' exited with code " << pre_res << "\n";
                if (pre_res >= 3) return ERROR_EXIT; } }
        if (verbose) ::std::cout << cmdline << "\n";
        system (cmdline.c_str ());
        if (::boost::filesystem::exists (clean))
        {   if (verbose) ::std::cout << clean.string () << "\n";
            post_res = system (clean.string ().c_str ());
            if (post_res > 0)
            {   ::std::cerr << "test clean up script '" << clean.string () << "' exited with code " << post_res << "\n";
                if (post_res >= 3) return ERROR_EXIT; } }
        if (! only_check_exports)
        {   if (! testfile (tmp)) return ERROR_EXIT;
            if (::boost::filesystem::file_size (tmp) > MAXOUTPUTFILESIZE)
            {   ::std::cerr << "too much output\n";
                if (rmtmp) ::boost::filesystem::remove (tmp);
                return ERROR_EXIT; } } }
    vstr_t results;
    if (! only_check_exports)
    {   if (! ::boost::filesystem::exists (tmp))
        {   ::std::cout << "no results file (" << tmp.string () << ")\n";
            return ERROR_EXIT; }
        results = readlines (tmp.string ());
        if (verbose >= 3)
        {   ::std::cout << "results (" << tmp.string () << "):\n";
            for (auto s : results) ::std::cout << s << "\n";
            ::std::cout << "\n"; }
        if (rmtmp && pre.empty ()) ::boost::filesystem::remove (tmp); }
    if (! examine_results (expected, results, passed, failed, expected_classes, tmp, expected_itemids, page_stats, correct_export, created_export, grand_stats)) return ERROR_EXIT;
    return 0; }

void print_version ()
{   ::std::cout << TESTPROG " version " VERSION_STRING " (" __DATE__ " " __TIME__ ")\n" COPYRIGHT "\n";
    ::std::cout << "To test " PROG " version " VERSION_STRING " only\n\n";
    ::std::cout << TESTPROG " -h for help\n"; }

void print_help ()
{   ::std::cout << TESTPROG << " tests the same version of " PROG "\n\n";
    ::std::cout << TESTPROG << " [switch...] FILE...\nSwitches:\n";
    ::std::cout << "-d    do not delete intermediate output files\n";
    ::std::cout << "-e    suggest test configuration for erroneous lines\n";
    ::std::cout << "-f X  load test specification filenames from file X (browse ssc/toast/... for examples)\n";
    ::std::cout << "-h    print this text and exit\n";
    ::std::cout << "-i X  import " PROG " test results from this file\n";
    ::std::cout << "-n    only report error numbers, not error codes\n";
    ::std::cout << "-N f  nit template file for " PROG "\n";
    ::std::cout << "-t D  temporary file directory (default " <<::boost::filesystem::temp_directory_path ().string () << ")\n";
    ::std::cout << "-T    FAIL is PASS. Bad is good. Ignorance is strength.\n";
    ::std::cout << "-v    verbose output (repeat for greater verbosity)\n";
    ::std::cout << "-V    print version information and exit\n";
    ::std::cout << "-x X  path of executable to test (default " PROG ")\n";
    ::std::cout << "FILE  name of file containing test specification; may be repeated (# for comments, blank lines ignored)\n\n";
    ::std::cout << "Result codes (of tests): 0 PASS, 3 FAIL\n"; }

int main (int argc, char** argv)
{   bool file = false;
    bool rmtmp = true;
    bool tmpdir = false;
    bool rst = false;
    bool xn = false;
    bool trump = false;
    ::std::string xeq (PROG);
    ::std::string tmppath, results;
    filelist specs;

    if (argv == nullptr) return 4; // WTF
    if (argc < 2) { print_version (); return 0; }

#ifdef UNIX
    // kludge for CMakeLists.txt move, itself a kludge to appease build packaging
    ::boost::filesystem::path tea (::boost::filesystem::current_path ());
    tea /= "recipe";
    tea /= "tea";
    if (::boost::filesystem::exists (tea))
        if (::boost::filesystem::is_directory (tea))
            chdir (tea.c_str ());
#endif // UNIX

    for (int a = 1; a < argc; ++a)
    {   if (argv [a] == nullptr) continue;
        const size_t len = strlen (argv [a]);
        if (len == 0) continue;
        if (argv [a][0] == '-')
        {   if (len == 2)
                switch (argv [a][1])
                {   case 'h' : print_help (); return 0;
                    case 'V' : print_version (); return 0;
                    case 'd' : rmtmp = false; continue;
                    case 'e' : easy_in = true; continue;
                    case 'i' : rst = true; continue;
                    case 'n' : numbers = true; continue;
                    case 't' : tmpdir = true; continue;
                    case 'T' : trump = true; continue;
                    case 'v' : ++verbose; continue;
                    case 'x' : xn = true; continue;
                    case 'f' : file = true; continue;
                    default : break; }
            ::std::cerr << "unknown switch " << argv [a] << "\n" << argv [0] << " -h for help\n\n";
            return ERROR_EXIT; }
        if (file)
        {   if (! testfile (argv [a]) || ! load_file_list (argv [a], specs)) return ERROR_EXIT; file = false; }
        else if (xn)
        {   xeq = argv [a]; if (! testxeq (xeq)) return ERROR_EXIT; xn = false; }
        else if (rst)
        {   results = argv [a]; if (! testfile (results)) return ERROR_EXIT; rst = false; }
        else if (tmpdir)
        {   tmppath = argv [a];
            if (! ::boost::filesystem::is_directory (tmppath))
            {   ::std::cerr << tmppath << " doesn't exist or is not a directory\n";
                return ERROR_EXIT; }
            tmpdir = false; }
        else specs.push_back (argv [a]); }

    int res = 0;
    unsigned passed = 0, failed = 0;

    for (auto s : specs)
    {   int x = run_test (s, xeq, rmtmp, tmppath, results, passed, failed);
        if (x > res) res = x; }

    if (passed + failed > 1)
        ::std::cout << passed << " passed, " << failed << " failed: ";

    if (trump || (res == 0)) ::std::cout << "pass\n";
    else ::std::cout << "FAIL\n";
    exit (0); }
