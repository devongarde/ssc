/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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

/*  version build info chars

a
b
c
d   DEBUG
e
f   FUDDY
g
h
i   ICU
j   JSNIC
k
l   LEAK_SEEK  
m
n   NPS_GEN
o
p
q   SIGNING
r
s   SPELT
t
u   UGLY_TEXT
v
w
x   WXS
y
z

*/

#define SSC_LU "ssc.lu"
#define DYLANHARRIS_ORG "dylanharris.org"

#define PROG "ssc"
#define TESTPROG PROG "-test"
#define FULLNAME "Static Site Checker"
#define FORMALNAME "The " FULLNAME
#define WEBADDR "https://" SSC_LU "/"

#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_RELEASE 22
#define VERSION_STRING "0.2.22"

#define NBSP "&nbsp;"
#define COPYRIGHT_SYMBOL "(c)"
#define COPYRIGHT_FORENAME "Dylan"
#define COPYRIGHT_SURNAME "Harris"
#define COPYRIGHT_YEAR "2020-2025"
#define COPYRIGHT_TEXT COPYRIGHT_SYMBOL " " COPYRIGHT_YEAR " " COPYRIGHT_FORENAME " " COPYRIGHT_SURNAME
#define COPYRIGHT_HTML "&copy;" NBSP COPYRIGHT_YEAR NBSP COPYRIGHT_FORENAME NBSP COPYRIGHT_SURNAME
#define COPYRIGHT_WEBADDR "https://" DYLANHARRIS_ORG "/"
#define COPYRIGHT_BRADDR " (" COPYRIGHT_WEBADDR ")"
#define COPYRIGHT COPYRIGHT_TEXT COPYRIGHT_BRADDR
#define COPYRIGHT_HTML_FULL "&copy;" NBSP COPYRIGHT_YEAR NBSP COPYRIGHT_FORENAME NBSP COPYRIGHT_SURNAME COPYRIGHT_BRADDR

#define SSC_PUBLIC_KEY ""

#define UPDATE_URL_1 "https://ssc.lu/ssc.ver.txt"
#define UPDATE_URL_2 "https://dylanharris.org/ssc/ssc.ver.txt"

#define DEFAULT_LINE_LENGTH 72
#define DESCRIPTION_LENGTH 60

#define DEFAULT_MAX_FILE_SIZE 4
#define DMFS_BYTES (DEFAULT_MAX_FILE_SIZE * 1024 * 1024)

#ifdef __clang__
#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#define COMPILER "c"
#define COMPNAME "clang"
#define MSVC_NOEXCEPT
#define PROCSIZE "64"
#define STR_IT_BYTE
#elif defined (__GNUC__)
#define COMPILER "g"
#define COMPNAME "gcc"
#define MSVC_NOEXCEPT
#define PROCSIZE "64"
#define STR_IT_BYTE
#elif ! defined (_MSC_VER)
#error Only clang, gcc, and msvc are supported. Should you get an additional compiler working, please submit an appropriate pull request.
#else //  __clang__
#define COMPILER "m"
#define COMPNAME "msvc"
#define NOLYNX
#define BORKED_BITSET_OPS
#define MSVC_NOEXCEPT noexcept
#define CLEAN_SHAREDPTR_ARRAY
#include <codeanalysis\warnings.h>

#ifdef _MSC_VER
#define WINDOZE // WINDOZE? Will rename this once VS 2022 stops trying to enforce its inefficient source layout.
#endif

#ifdef WIN32
#define X32
#define SMALLINT
#define PROCSIZE "32"
#else // WIN32
#define X64
#define PROCSIZE "64"
#endif // WIN32

// https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
#if _MSC_VER >= 1930
#pragma warning (disable : 26812)
#define _WIN32_WINNT 0x0A00 // 10
#define WINICU
#define GETUSERNAMEEX
#ifndef VS2022
#define VS2022
#endif // VS2022
#undef VS2019
#undef VS2017
#elif _MSC_VER >= 1920
#define WINICU
#define _WIN32_WINNT 0x0A00 // 10
#ifndef VS2019
#define VS2019
#endif // VS2019
#undef VS2022
#undef VS2017
#elif _MSC_VER >= 1910
#define NOICU
#define _WIN32_WINNT 0x0603 // 8.1
#define SMALLINT
#define NOMERGE
#define SULKINGSTRINGVIEW
#ifndef VS2017
#define VS2017
#endif // VS2017
#undef VS2019
#undef VS2022
#else // _MSC_VER
#error ssc only builds with VS 2019 / 2022.
#endif // _MSC_VER

    // The MSVC linter is generally useful, but it has (had?) some serious problems.
    // General problem 1: the msvc linter provides no clean mechanism to suppress a spurious warning in place, except through the #...
    //      mechanism. Those #... have to be wrapped in #ifdefs to avoid confusing other compilers. In the worst case, this requires 7 #...
    //      statements to suppress one spurious warning. That is ridiculously clunky, and I'm most definitely NOT going there for specific
    //      warnings which are many times spurious, even if those warnings are useful elsewhere. I think this is a design error with
    //      VC++'s linter, or quite possibly a documentation issue given I couldn't find a reference to easily suppressing spurious
    //      warnings. The norm with other linters is a recognisable comment. Warnings in this category: 26409, 264621, 26485.
    // General program 2: the msvc linter just doesn't suss template metaprogramming. It often suggests changes to function signatures that
    //      ignore the detail of other template variants, which, if followed, results in code that cannot compile. If it suggests a template
    //      signature change, it should do so in the metaprogramming context, e.g. ensure it applies to ALL such functions, not just one
    //      or two of them.
    // ... 'X::Y' hides a non-virtual ... 'XX::Y'
    // ...: default constructor may not throw, mark it noexcept .... except if I mark it noexcept, it no longer fits the default constructor signature...
    // 6330: plus using wchar calls with chars ... actually, those chars are (or should be) utf-8.
    // 26439: comes up on standard class functions; following the suggestion means they no longer fit the signature, so breaks stuff
    // 26410/5/8: correct, in that particular place. So what? Smart pointers are indeed pointers. By convention, an unwrapped pointer means
    //      the code doesn't own it.
    // 26493: the warning against c-style casts would be useful if VS could tell the difference between a cast and a switch statement
#pragma warning (disable : 6330 26409 26410 26415 26418 26434 26439 26455 26456 26461 26485 26493)

#pragma warning (push, 3)
#pragma warning (disable : ALL_CODE_ANALYSIS_WARNINGS)

// mostly for boost
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#endif // __clang__

#ifdef SSC_TEST
#undef NOICU // get rid of value
#define NOICU
#define NO_GSL
#elif ! defined (NOSPELL) && ! defined (HUNSPELL) && ! defined (WINSPELL)
#undef NOSPELL
#define NOSPELL
#endif // SSC_TEST

#if defined (DEBUG) || defined (_DEBUG) || defined (SSC_ASSERTS)
#  ifndef DEBUG
#  define DEBUG
#  endif // DEBUG
#endif // debug...

#ifdef NOICU
#define ICU_CHAR
#undef NOICU // get rid of value
#define NOICU
#undef NOSPELL
#define NOSPELL
#else // NOICU
#define ICU_CHAR "i"
#define BOOST_HAS_ICU
#endif // NOICU

#ifdef WX
#define EDITION "/g"
#else // WX
#define EDITION
#endif // WX

#ifdef NOSPELL
#ifdef WINSPELL
#undef WINSPELL
#endif // WINSPELL
#ifdef HUNSPELL
#undef HUNSPELL
#endif // HUNSPELL
#define SPELT
#elif defined (WINSPELL) && defined (HUNSPELL)
#error Define only one of WINSPELL or HUNSPELL
#elif defined (WINSPELL) && ! defined (_MSC_VER)
#error WINSPELL requires Windows & Visual Studio
#else // NOSPELL
#define SPELT "s"
#endif // NOSPELL

#ifdef NOCONSTEXPR
#define CONSTEXPR const
#else // NOCONSTEXPR
#define CONSTEXPR constexpr
#endif // NOCONSTEXPR

#define LIMITED_META_COMPLEXITY

// mostly for my sanity
#define BOOST_LIB_DIAGNOSTIC

#ifdef FUDDYDUDDY
#define BOOVAR 2
#define FUDDY "f"
#else // FUDDYDUDDY
#define FUDDY
#endif // FUDDYDUDDY

#if (defined (__unix__) || defined (unix) || defined (UNIX)) && ! defined (USG)
#include <sys/param.h>
#endif

#ifdef LEAK_SEEK
#define LEAKY "l"
#ifndef VS2022
#pragma message("LEAK_SEEK only tested with VC2022")
#else // VS2022
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // VS2022
#else // LEAK_SEEK
#define LEAKY
#endif // LEAK_SEEK

#ifdef SIGNING
#define SIGNCHAR "q"
#else // SIGNING
#define SIGNCHAR
#endif // SIGNING

#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <assert.h>
#include <map>

#ifdef UNIX
#include <unistd.h>
#include <pwd.h>
#endif // UNIX

#ifndef SSC_TEST
#include <algorithm>
#include <array>
#ifndef NO_FRED
#include <atomic>
#endif // NO_FRED
#include <bitset>
#include <chrono>
#ifndef VS2017  // https://social.msdn.microsoft.com/Forums/azure/en-US/999a5b68-a1d3-4a76-8f3b-65655257c301/vs2017-stdcodecvt-linker-error?forum=vcgeneral
#include <codecvt>
#endif // VS2017
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <locale>
#include <memory>
#include <set>
#ifndef NO_FRED
#include <shared_mutex>
#endif // NO_FRED
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#ifndef NO_FRED
#include <thread>
#endif // NO_FRED
#include <tuple>
#include <type_traits>
#include <utility>

#ifdef _MSC_VER
#include <direct.h>
#endif // _MSC_VER

#if defined (NO_FRED) || defined (FUDDYDUDDY) || defined (VS2017) || defined (VS2019)
#define NOSERV
#endif // ...

#ifndef NOICU
#ifdef WINICU
#include <icu.h>
#else WINICU
#include <unicode/ucsdet.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/errorcode.h>
#include <unicode/normalizer2.h>
#include <unicode/brkiter.h>
#include <unicode/ustring.h>
#endif // WINICU
#endif // NOICU

#endif // SSC_TEST

#include <boost/version.hpp>
#include <boost/static_assert.hpp>

#define BOOST_MAJOR ( BOOST_VERSION / 100000 )
#define BOOST_MINOR ( BOOST_VERSION / 100 % 1000 )
#define BOOST_RELEASE ( BOOST_VERSION % 100 )

BOOST_STATIC_ASSERT (BOOST_MAJOR == 1);

#if BOOST_MINOR < 67
#define NO_PCF_STR
#endif // BOOST_MINOR

#if BOOST_MINOR < 72
#define NO_DIROPTS
#endif // 1.72

#if BOOST_MINOR < 73
#define FS_THROWS
#endif // 1.73

#if BOOST_MINOR > 78
#define BOOST_FILESYSTEM_VERSION 4
#endif // BOOST_MINOR

#if BOOST_MINOR > 84
#define NO_JSON_ERR
#endif

#if BOOST_FILESYSTEM_VERSION == 4
#define BOOST_COPY_OPTION ::boost::filesystem::copy_options
#define BOOST_OVERWRITE overwrite_existing
#define BOOST_PSTR(P) P.c_str ()
#define BOOST_FSTREAM ::std::fstream
#define BOOST_IFSTREAM ::std::ifstream
#define BOOST_OFSTREAM ::std::ofstream
#define BOOST_EXTENSION(P) P.extension ()
#else // BOOST_FILESYSTEM_VERSION
#define BOOST_COPY_OPTION ::boost::filesystem::copy_option
#define BOOST_OVERWRITE overwrite_if_exists
#define BOOST_PSTR(P) P
#define BOOST_FSTREAM ::boost::filesystem::fstream
#define BOOST_IFSTREAM ::boost::filesystem::ifstream
#define BOOST_OFSTREAM ::boost::filesystem::ofstream
#define BOOST_EXTENSION(P) ::boost::filesystem::extension (d)
#endif // BOOST_FILESYSTEM_VERSION

#define BOOST_FSTREAM_CNSTR(F,P) BOOST_FSTREAM F (BOOST_PSTR (P))
#define BOOST_FSTREAM_CNSTRO(F,P,O) BOOST_FSTREAM F (BOOST_PSTR (P), O)
#define BOOST_IFSTREAM_CNSTR(F,P) BOOST_IFSTREAM F (BOOST_PSTR (P))
#define BOOST_IFSTREAM_CNSTRO(F,P,O) BOOST_IFSTREAM F (BOOST_PSTR (P), O)
#define BOOST_OFSTREAM_CNSTR(F,P) BOOST_OFSTREAM F (BOOST_PSTR (P))
#define BOOST_OFSTREAM_CNSTRO(F,P,O) BOOST_OFSTREAM F (BOOST_PSTR (P), O)

#ifndef SSC_TEST

#if defined (_MSC_VER) && defined (HUNSPELL)
#define HUNSPELL_STATIC
#pragma comment (lib, "libhunspell.lib")
#endif // _MSC_VER && HUNSPELL

#if BOOVAR == 1
#include <boost/variant.hpp>
#define ssc_variant ::boost::variant
#define ssc_get ::boost::variant::get
#elif BOOVAR == 2
#include <boost/variant2/variant.hpp>
#define ssc_variant ::boost::variant2::variant
#define ssc_get ::boost::variant2::get
#else // BOOVAR
#include <variant>
#define ssc_variant ::std::variant
#define ssc_get ::std::get
#endif // BOOVAR

#ifdef ORDERED
#define ssc_set ::std::set
#define ssc_map ::std::map
#define ssc_mm ::std::multimap
#else // ORDERED
#include <unordered_set>
#include <unordered_map>
#define ssc_set ::std::unordered_set
#define ssc_map ::std::unordered_map
#define ssc_mm ::std::unordered_multimap
#endif // ORDERED

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/chrono.hpp>
#include <boost/date_time.hpp>
#include <boost/format.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/string_path.hpp>
#include <boost/log/trivial.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/regex.hpp>
#include <boost/scoped_ptr.hpp>

#if BOOST_MINOR > 76
#include <boost/system.hpp>
#else // BOOST_MINOR
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#endif // BOOST_MINOR

#include <boost/thread.hpp>

#ifdef _MSC_VER
#pragma warning (disable : 4701) // CRC
#endif // _MSC_VER

#include <boost/crc.hpp>

#ifndef NO_JSONIC
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : ALL_CODE_ANALYSIS_WARNINGS) // boost
#endif // _MSC_VER
#include <boost/json.hpp>
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
#endif // NO_JSONIC

#ifdef WX
#define WXS "x"
#define wxUSE_GUI 1
#define wxUSE_WXHTML_HELP 1
#ifdef _MSC_VER
#define __WXMSW__
#endif // _MSC_VER
#include <wx/wx.h>
#include <wx/dataview.h>
#include <wx/dirctrl.h>
#include <wx/filedlg.h>
#include <wx/textctrl.h>
#include <wx/fdrepdlg.h>
#include <wx/filepicker.h>
#include <wx/fs_zip.h>
#include <wx/helphtml.h>
#include <wx/html/htmlwin.h>
#include <wx/html/htmprint.h>
#include <wx/notebook.h>
#include <wx/print.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/stc/stc.h>
#include <wx/dlimpexp.h>
#include <wx/wizard.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/choicebk.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/timectrl.h>

// FFS
#ifdef DARWIN
#define FANCY_TEXT_CTRL wxTextCtrl
#define UGLY_TEXT "u"
#define UGLITUDE
#else // FFS
#define FANCY_TEXT_CTRL wxStyledTextCtrl
#endif // FFS

#endif // WX

#endif // SSC_TEST

#ifdef _MSC_VER
#define SECURITY_WIN32
#include <windows.h>
#include <process.h>
#include <Security.h>
#endif // _MSC_VER

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#ifdef SIGNING
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#endif // SIGNING

#ifndef NO_GSL
#include <gsl/gsl>
#define GSL_SPAN(ARRAY, MAXLEN) ::gsl::span (ARRAY, MAXLEN)
#define GSL_NARROW_CAST ::gsl::narrow_cast
#define GSL_AT(ARRAY, ENTRY) ::gsl::at (ARRAY, ENTRY)
#define GSL_OWNER(TYPE) ::gsl::owner < TYPE * >
#define GSL_OWNER_PT(TYPE) ::gsl::owner < TYPE >
#define GSL_NOT_NULL(TYPE) ::gsl::not_null < TYPE >
#else // NO_GSL
#define GSL_SPAN(ARRAY, MAXLEN) ARRAY
#define GSL_NARROW_CAST static_cast
#define GSL_AT(ARRAY, ENTRY) ARRAY [ENTRY]
#define GSL_OWNER(TYPE)
#define GSL_OWNER_PT(TYPE) TYPE
#define GSL_NOT_NULL(TYPE) TYPE
#endif // NO_GSL

#ifndef NO_FALLTHROUGH
#define FALLTHROUGH [[fallthrough]]
#else // NO_FALLTHROUGH
#define FALLTHROUGH
#endif // NO_FALLTHROUGH

#if defined (_DEBUG) && defined (_MSC_VER)
#define DEBUG_BREAK ::DebugBreak ()
#else
#define DEBUG_BREAK
#endif // _DEBUG ...

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning (pop)
#endif

#define END_OF_STATS "==="
#define START_OF_SECTION "***"
#define START_OF_SUBSECTION "**"
#define BEFORE_MOTE "**"
#define AFTER_MOTE "**"
#define SNIPPET "snippet"
#define CONFIGURE "Configuration"

#ifndef SSC_TEST
#define PR_FILE "file"
#define PR_FTP "ftp"
#define PR_FTPS "ftps"
#define PR_GEO "geo"
#define PR_HTTP "http"
#define PR_HTTPS "https"
#define PR_LDAP "ldap"
#define PR_MAILTO "mailto"
#define PR_NEWS "news"
#define PR_RTSP "rtsp"
#define PR_SFTP "sftp"
#define PR_SSH "ssh"
#define PR_TELNET "telnet"
#define PR_TEL "tel"
#define PR_URN "urn"

#define UNKNOWN "(unknown)"

#define WEBMENTION "webmention"
#define SEP "."
#define WELL_KNOWN ".well-known"
#define WELL_KNOWN_PATH "/" WELL_KNOWN "/"

#define COLON_SLASH_SLASH "://"
#define HTTP PR_HTTP COLON_SLASH_SLASH
#define HTTPS PR_HTTPS COLON_SLASH_SLASH
#define SPACE ' '
#define AMPERSAND '&'
#define COLON ':'
#define SEMICOLON ';'
#define DOT '.'
#define SLASH '/'
#define HASH '#'
#define HASHES "#"
#define QUESTION '?'
#define AT '@'
#define EQUAL '='
#define PERCENT '%'
#define BRCLOSE ')'
#define BROPEN '('
#define SQCLOSE ']'
#define SQOPEN '['
#define CUCLOSE '}'
#define CUOPEN '{'
#define SIGNPLUS '+'
#define SIGNMINUS '-'
#define DENARY "0123456789"
#define DDD DENARY "-."
#define SIGNEDDECIMAL DDD "+"
#define PLUSMINUS "+-"
#define SIGNEDINTEGER DENARY PLUSMINUS
#define EXPONENTIAL SIGNEDDECIMAL "Ee"
#define POSITIVE DENARY "+."
#define OCTAL "01234567"
#define HEX DENARY "abcdefABCDEF"
#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define WHITESPACE " \n\t\r\f"
#define ALPHABET UPPERCASE LOWERCASE
#define ALPHANUMERIC ALPHABET DENARY
#define ALPHADDD ALPHABET DDD
#define B64BIN ALPHADDD "+/= "
#define IDS ALPHADDD "_:"
#define HYPHENATED ALPHANUMERIC "-"
#define DOMAINNAME ALPHANUMERIC ".-_"
#define URL_TEMPLATE_VAR ALPHANUMERIC "_%."
#define TEL HEX "+*()-.#*_!~'[]/ "
#define REAL SIGNEDDECIMAL "Ee"
#define LINE_SEPARATORS "\n\r\f\v"
#define ELLIPSES "..."
#define WILDCHARS DOMAINNAME " *?\\[]{},!^|"

#define DEFAULT_DOMAIN "example.org"
#define CSS_TYPE "text/css"
#define HTML_TYPE "text/html"
#define PLAIN_TYPE "text/plain"

#define EXPORT_EXTENSION ".json"
#define QNONE "'none'"

#define US_ASCII "US-ASCII"
#define LATIN_1 "ISO-8859-1"
#define UTF_8 "UTF-8"
#define STANDARD_ENGLISH "en-GB"
#define WEB_ENGLISH "en-US"

#define EVIL "nonce" // Why the f*ck the powers that be decided to embed a word for paedophile in the standards, I have no clue, but I do not like it.

#define JOIN                "."
#define HIDDENISH           "."

#define DEF_CONF_EXT        "conf"
#define DEF_CONF_FILE       PROG JOIN DEF_CONF_EXT
#define DEF_PERSIST_EXT     "ndx"
#define DEF_PERSIST_FILE    PROG JOIN DEF_PERSIST_EXT
#define DEF_TEMP_EXT        PROG
#define DEF_DATAPATH        HIDDENISH PROG

#define MAX_IDEAL_TITLE_LENGTH 32

#define ADOBE_COM           "ns.adobe.com"
#define CC                  "creativecommons.org"
#define DBPEDIA             "dbpedia.org"
#define EXAMPLE_ORG         DEFAULT_DOMAIN
#define MICROFORMATS_ORG    "microformats.org"
#define SCHEMA_ORG          "schema.org"
#define N_WHATWG_ORG        "n.whatwg.org"
#define OGC                 "www.ogc.org"
#define OGP_ME              "ogp.me"
#define PURL_ORG            "purl.org"
#define PRISM_ORG           "prismstandard.org"
#define RDFS_ORG            "rdfs.org"
#define RSS_BOARD           "www.rssboard.org"
#define SPECIAL_PRIVACY     "www.specialprivacy.eu"
#define W3_ORG              "www.w3.org"
#define W3ID_ORG            "w3id.org"
#define XMLNS               "xmlns"
#define XHTMLNS             "xml"
#define XLINK               "xlink"

#define SVG_2000            W3_ORG "/2000/svg"
#define XCOM                XMLNS ".com"
#define XOT                 XMLNS "xmlns.opentechnology.org/xslt-extensions"

#define HTTP_W3 HTTP W3_ORG
#define HTTPS_W3 HTTPS W3_ORG

#define HTTP_MF HTTP MICROFORMATS_ORG
#define HTTPS_MF HTTPS MICROFORMATS_ORG

#define NOFLAGS 0
typedef uint64_t flags_t; // at least 64 bits

#include "main/abort.h"

typedef uint64_t ident_t;
typedef uint32_t uid_t;
CONSTEXPR uid_t uid_max = UINT32_MAX;

typedef ::std::vector < int > vint_t;
typedef ::std::vector < double > vdbl_t;
typedef ::std::vector < ::std::string > vstr_t;
typedef ::std::vector < ::boost::filesystem::path > vbp_t;
typedef ::std::vector < vstr_t > vvstr_t;
typedef ssc_set < ::std::string > sstr_t;
typedef ::std::vector < sstr_t > vsstr_t;
typedef ssc_set < unsigned int > sui_t;
typedef ::std::vector < sui_t > vsui_t;
typedef ::std::vector < unsigned char > vuc_t;
typedef ssc_map < ::std::string, ::std::string > ustr_t;
typedef ssc_map < ::std::string, ::std::size_t > msid_t;
typedef ::std::map < ::std::string, ::std::size_t > smsid_t;
typedef ssc_map < ::std::size_t, ::std::string > misd_t;
typedef ustr_t::value_type ustrv_t;
typedef ::std::basic_string < char32_t > string32;
typedef ::std::basic_stringstream < char32_t > stringstream32;
typedef ssc_map < ::std::size_t, sstr_t > szreg_t;
typedef ::std::unique_ptr < ::std::fstream > fstr_p;
typedef ::std::vector < ::boost::regex > vreg_t;

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

CONSTEXPR uint32_t itemprop_category_shift =  28;
CONSTEXPR uint32_t itemprop_item_mask =       0x0FFFFFFF;
CONSTEXPR uint32_t itemprop_category_mask =   0xF0000000;

#ifdef WX
typedef ::std::vector < wxString > vws_t;
#endif // WX

#endif // SCC_TEST

#ifdef REALLY_BUGGY_VECTOR_BOOL
typedef ::std::vector < int > faux_vb_t;
#else // REALLY_BUGGY_VECTOR_BOOL
typedef ::std::vector < bool > faux_vb_t;
#endif // REALLY_BUGGY_VECTOR_BOOL

#define COMMENT_CHAR '/'
#define COMMENT_STRCHAR "/"

#ifdef NO_PCF_STR
#define NPS_GEN
#else
#define NPS_GEN "n"
#endif

#ifdef NO_JSONIC
#define JSNIC
#else // NO_JSONIC
#define JSNIC "j"
#endif // NO_JSONIC

#ifndef TARGET_OS
#ifdef _MSC_VER
#ifdef _WIN32
#define TARGET_OS "wnd_x86"
#elif defined (_WIN64)
#define TARGET_OS "wnd_x64"
#elif defined (_M_ARM64) || defined (_M_ARM64EC)
#define TARGET_OS "wnd_a64"
#elif defined (_M_ARM32)
#define TARGET_OS "wnd_a32"
#else // _WIN32
#define TARGET_OS "wnd_???"
#endif // _WIN32
#else // _MSC_VER
#ifndef OS_VER
#define TARGET_OS "???"
#else // OS_VER
#define TARGET_OS OS_VER
#endif // OS_VER
#endif // _MSC_VER
#endif // TARGET_OS

#ifdef NOICU
#define ICU_VER
#else // NOICU
#ifndef U_ICU_VERSION
#define U_ICU_VERSION "w"
#endif U_ICU_VERSION
#define ICU_VER ":" U_ICU_VERSION
#endif // NOICU

#ifdef DEBUG
#define DBG_STATUS "d"
#else // DEBUG
#define DBG_STATUS
#endif // DEBUG

#ifndef UGLY_TEXT
#define UGLY_TEXT
#endif

#ifndef WXS
#define WXS
#endif // WXS

// Enable this to see full messages that would otherwise be generated when using -T switch, roughly speaking
// #define EXPAND_TEST "t"

#define BUILD_INFO   DBG_STATUS FUDDY ICU_CHAR JSNIC LEAKY NPS_GEN SIGNCHAR SPELT UGLY_TEXT WXS ":" TARGET_OS ":" COMPILER PROCSIZE ":" BOOST_LIB_VERSION ICU_VER
#define BASE_TITLE   FULLNAME " v" VERSION_STRING EDITION " (" WEBADDR ")\n"
#define SIMPLE_TITLE BASE_TITLE COPYRIGHT_TEXT "\n"
#define FULL_TITLE_1 BASE_TITLE COPYRIGHT "\n"
#define FULL_TITLE_2 "[" __DATE__ " " __TIME__  "] [" BUILD_INFO "]" "\n"
#define FULL_TITLE   FULL_TITLE_1 FULL_TITLE_2
#define TEST_TITLE   FULLNAME " v" VERSION_STRING EDITION "\n(" __DATE__ " " __TIME__ ")\n" WEBADDR "\n" COPYRIGHT "\n\n"

#ifdef FIBBING_AGENT
#define SSC_USER_AGENT   "Mozilla/5.0"
#else // FIBBING_AGENT
#define SSC_USER_AGENT PROG "/" VERSION_STRING " (" BUILD_INFO ") " BOOST_BEAST_VERSION_STRING
#endif // FIBBING_AGENT

#define TYPE_HELP "Type '" PROG " -h' for help."

#define CONSTRUCT_COPY(XXX, DDD) \
    XXX (const XXX & xxx) = DDD; \
    XXX& operator = (const XXX & xxx) = DDD; \

#define CONSTRUCT_MOVE(XXX, DDD) \
    XXX (XXX && xxx) = DDD; \
    XXX& operator = (XXX && xxx) = DDD

#define COPY_MOVE(XXX) \
    CONSTRUCT_COPY (XXX, default) \
    CONSTRUCT_MOVE (XXX, default)

#define COPY_NO_MOVE(XXX) \
    CONSTRUCT_COPY (XXX, default) \
    CONSTRUCT_MOVE (XXX, delete)

#define NO_COPY_NO_MOVE(XXX) \
    CONSTRUCT_COPY (XXX, delete) \
    CONSTRUCT_MOVE (XXX, delete)

#define NO_COPY_MOVE(XXX) \
    CONSTRUCT_COPY (XXX, delete) \
    CONSTRUCT_MOVE (XXX, default)

#define BASE_DEFAULT(XXX) \
    XXX () = default; \
    ~XXX () = default;

#define CONSTRUCT_DEFAULT(XXX) \
    BASE_DEFAULT (XXX); \
    COPY_MOVE (XXX);

#define CONSTRUCT_NO_COPY(XXX) \
    BASE_DEFAULT (XXX); \
    NO_COPY_MOVE (XXX);

#define CONSTRUCT_DELETE(XXX) \
    XXX () = delete; \
    NO_COPY_NO_MOVE (XXX); \
    ~XXX () = default

#define COPY_MOVE_NO_DEFCON(XXX) \
    XXX () = delete; \
    COPY_MOVE (XXX); \
    ~XXX () = default

#define DEFAULT_CONSTRUCTORS(XXX) CONSTRUCT_DEFAULT (XXX)
#define DEFAULT_COPY_CONSTRUCTORS(XXX) COPY_MOVE (XXX)
#define DEFAULT_NO_MOVE_CONSTRUCTORS(XXX) BASE_DEFAULT (XXX) COPY_NO_MOVE (XXX)
#define DEFAULT_NO_COPY_NO_MOVE_CONSTRUCTORS(XXX) BASE_DEFAULT (XXX) NO_COPY_NO_MOVE (XXX)
#define DEFAULT_NO_COPY_CONSTRUCTORS(XXX) CONSTRUCT_NO_COPY (XXX)
#define DEFAULT_CONSTRUCTORS_NO_DESTRUCTORS(XXX) NO_COPY_NO_MOVE (XXX)

#define DEFAULT_CONSTRUCTORS_NO_EMPTY(XXX) \
    XXX () = delete; \
    COPY_MOVE (XXX); \
    ~XXX () = default

#define DEFAULT_CONSTRUCTORS_VIRTUAL_DESTRUCTOR(XXX) \
    XXX () = default; \
    COPY_MOVE (XXX); \
    virtual ~XXX () = default

#define NO_COPY_CONSTRUCTORS(XXX) NO_COPY_NO_MOVE (XXX)
#define DELETE_CONSTRUCTORS(XXX) CONSTRUCT_DELETE (XXX)
#define NO_DEFCON(XXX) COPY_MOVE_NO_DEFCON (XXX)

#define HIDE_ME                   ".--" PROG "_HIDE_ME"

#define REPORT_ABRREVIATION       "Abbreviation"
#define REPORT_ATTRIBUTE          "Attribute"
#define REPORT_CLASS              "Class"
#define REPORT_CUSTARD_MEDIA      "Custom-Media"
#define REPORT_CUSTARD_PROPERTY   "Custom-Property"
#define REPORT_DEFINITION         "Definition"
#define REPORT_ELEMENT            "Element"
#define REPORT_ELEMENT_CLASS      "Class/Element"
#define REPORT_ELEMENT_ID         "Id/Element"
#define REPORT_EXPORT             "Export"
#define REPORT_GRAND              "Grand"
#define REPORT_ID                 "Id"
#define REPORT_ITEMID             "ItemId"
#define REPORT_LINK               "Link"
#define REPORT_NAME_VALUE         "Name/Value"
#define REPORT_ONTOLOGY           "Ontology"
#define REPORT_NITS               "Nits"
#define REPORT_PROPERTY           "Property"
#define REPORT_SHADOW             "Shadow"
#define REPORT_STATEMENT          "Statement"
#define REPORT_STAT               "Statistic"
#define REPORT_UPDATE             "Update"
#define REPORT_VERSION            "Version"

#define REPORT_ANNOTATION         "Annotation"
#define REPORT_CAREGORY           "Category"
#define REPORT_CHARACTER          "Character"
#define REPORT_CONTENT            "Content-Name"
#define REPORT_COUNTER            "Counter-Style"
#define REPORT_FAMILY             "Font-Family"
#define REPORT_FONT               "Font"
#define REPORT_HEADER             "Header"
#define REPORT_HIGHLIGHT          "Highlight"
#define REPORT_HISTORICAL         "Historical-Form"
#define REPORT_KEYFRAME           "Keyframe"
#define REPORT_LAYER              "Layer"
#define REPORT_ORNAMENT           "Ornament"
#define REPORT_PAGE               "Page"
#define REPORT_PAGE_NAME          "Page-Name"
#define REPORT_PALETTE            "Palette"
#define REPORT_REFERENCE          "Reference"
#define REPORT_REGION             "Region"
#define REPORT_SCROLL             "Scroll-Anim"
#define REPORT_STYLESET           "Styleset"
#define REPORT_STYLISTIC          "Stylistic"
#define REPORT_SWASH              "Swash"
#define REPORT_VIEW               "View"

#define ATOMIC_EXT                "atom"
#define CSS_EXT                   "css"
#define HTML_EXT                  "html"
#define JSONLD_EXT                "jld"
#define RSL_EXT                   "rsl"
#define RSS_EXT                   "rss"
#define VTT_EXT                   "vtt"
#define XHTML_EXT                 "xhtml"

#ifdef DARWIN
#define REPERTOIRE                "folder"
#define RREPERTOIRE               "Folder"
#define REPERTOIRES               "folders"
#define RREPERTOIRES              "Folders"
#else // DARWIN
#define REPERTOIRE                "directory"
#define RREPERTOIRE               "Directory"
#define REPERTOIRES               "directories"
#define RREPERTOIRES              "Directories"
#endif // DARWIN

#define STOP_NOW -1
#define VALID_RESULT 0
#define STOP_OK 1
#define NOTHING_TO_DO 2
#define ERROR_STATE 3
#define CATASTROPHIC_STATE 4

#include "main/enum.h"

#ifdef REALLY_BUGGY_VECTOR_BOOL
// probably quite innocent, but I'm not wasting my time testing what is already known to be a flawed implementation
typedef ::std::array < int, rcb_max > aset_t;
#else // REALLY_BUGGY_VECTOR_BOOL
typedef ::std::array < bool, rcb_max > aset_t;
#endif // REALLY_BUGGY_VECTOR_BOOL

// Hearty thanks given for these coding guidelines:
// https://cs.fit.edu/~kgallagher/Schtick/How%20To%20Write%20Unmaintainable%20Code.html
