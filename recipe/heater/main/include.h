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

#define SSC_LU "ssc.lu"
#define DYLANHARRIS_ORG "dylanharris.org"

#define PROG "ssc"
#define TESTPROG PROG "-test"
#define FULLNAME "Static Site Checker"
#define WEBADDR "https://" SSC_LU "/"

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_RELEASE 28
#define VERSION_STRING "0.1.28"

#define NBSP "&nbsp;"
#define COPYRIGHT_SYMBOL "(c)"
#define COPYRIGHT_FORENAME "Dylan"
#define COPYRIGHT_SURNAME "Harris"
#define COPYRIGHT_YEAR "2020-2023"
#define COPYRIGHT_TEXT COPYRIGHT_SYMBOL " " COPYRIGHT_YEAR " " COPYRIGHT_FORENAME " " COPYRIGHT_SURNAME
#define COPYRIGHT_HTML "&copy;" NBSP COPYRIGHT_YEAR NBSP COPYRIGHT_FORENAME NBSP COPYRIGHT_SURNAME
#define COPYRIGHT_WEBADDR "https://" DYLANHARRIS_ORG "/"
#define COPYRIGHT_BRADDR " (" COPYRIGHT_WEBADDR ")"
#define COPYRIGHT COPYRIGHT_TEXT COPYRIGHT_BRADDR
#define COPYRIGHT_HTML_FULL "&copy;" NBSP COPYRIGHT_YEAR NBSP COPYRIGHT_FORENAME NBSP COPYRIGHT_SURNAME COPYRIGHT_BRADDR

#define DEFAULT_LINE_LENGTH 72
#define DESCRIPTION_LENGTH 60

#if defined (DEBUG) || defined (_DEBUG) || defined (SSC_ASSERTS)
#  ifndef DEBUG
#  define DEBUG
#  endif // DEBUG
#define DBG_ASSERT(x) assert (x)
#else // debug
#  ifndef NDEBUG
#  define NDEBUG
#  endif // NDEBUG
#define DBG_ASSERT(x)
#endif // debug

#ifdef SSC_TEST
#define NOICU
#define NO_GSL
#elif ! defined (NOSPELL) && ! defined (HUNSPELL) && ! defined (WINSPELL)
#define NOSPELL
#endif // SSC_TEST

#ifdef NOICU
#define NOSPELL
#else // NOICU
#define BOOST_HAS_ICU
#endif // NOICU

#ifdef NOSPELL
#if defined (WINSPELL) || defined (HUNSPELL)
#error Define only one of NOICU, NOSPELL, WINSPELL, or HUNSPELL
#endif // ...SPELL
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

#ifdef __clang__
#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#define COMPILER "c"
#define MSVC_NOEXCEPT
#define PROCSIZE "64"
#define STR_IT_BYTE
#elif ! defined (_MSC_VER)
#define COMPILER "g"
#define MSVC_NOEXCEPT
#define PROCSIZE "64"
#define STR_IT_BYTE
#else
#define COMPILER "m"
#define NOLYNX
#define BORKED_BITSET_OPS
#define MSVC_NOEXCEPT noexcept
#define CLEAN_SHAREDPTR_ARRAY
#include <codeanalysis\warnings.h>

#ifdef WIN32
#define X32
#define SMALLINT
#define PROCSIZE "32"
#else // WIN32
#define X64
#define PROCSIZE "64"
#endif // WIN32

    // The MSVC linter is generally useful, but it has some serious problems.
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
#pragma warning (disable : 6330 26409 26410 26415 26418 26434 26439 26455 26456 26461 26485)

// https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
#if _MSC_VER >= 1930
#pragma warning (disable : 26812)
#define _WIN32_WINNT 0x0A00 // 10
#elif _MSC_VER >= 1920
#define _WIN32_WINNT 0x0A00 // 10
#elif _MSC_VER >= 1910
#define _WIN32_WINNT 0x0603 // 8.1
#define SMALLINT
#define NOMERGE
#else // _MSC_VER
#error ssc only builds with VS 2017 / 2019 / 2022.
#endif // _MSC_VER

#pragma warning (push, 3)
#pragma warning (disable : ALL_CODE_ANALYSIS_WARNINGS)

// mostly for boost
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#endif // __clang__

#ifdef FUDDYDUDDY
#define BOOVAR 2
#define FUDDY "f"
#else // FUDDYDUDDY
#define FUDDY
#endif // FUDDYDUDDY

#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <assert.h>
#include <map>

#ifdef UNIX
#include <unistd.h>
#endif // UNIX

#ifdef _MSC_VER
#include <windows.h>
#endif // _MSC_VER

#ifndef SSC_TEST
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>
#include <memory>
#include <cstddef>
#include <utility>
#include <type_traits>
#include <stdexcept>
#include <chrono>
#include <ctime>
#include <functional>
#include <array>
#include <bitset>
#include <set>
#include <array>
#include <codecvt>
#include <locale>
#ifndef NO_FRED
#include <shared_mutex>
#include <thread>
#include <atomic>
#endif // NO_FRED

#ifndef NOICU
#include <unicode/ucsdet.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/errorcode.h>
#include <unicode/normalizer2.h>
#include <unicode/brkiter.h>
#include <unicode/ustring.h>

#ifdef _MSC_VER
#pragma comment (lib, "icudt.lib")
#if defined (_DEBUG) && (_MSC_VER >= 1920) && (_MSC_VER < 1930)
#pragma comment (lib, "icuind.lib")
#pragma comment (lib, "icuiod.lib")
#pragma comment (lib, "icutud.lib")
#pragma comment (lib, "icuucd.lib")
#else // _DEBUG
#pragma comment (lib, "icuin.lib")
#pragma comment (lib, "icuio.lib")
#pragma comment (lib, "icutu.lib")
#pragma comment (lib, "icuuc.lib")
#endif // _DEBUG
#endif // _MSC_VER

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

#if BOOST_MINOR < 76
#define NO_BOOST_REGEX
#endif // 1.75

#if BOOST_MINOR < 77
#define NO_BOOST_DATE_FACET
#endif

#if BOOST_MINOR > 78
#define BOOST_FILESYSTEM_VERSION 4
#endif // BOOST_MINOR

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
#ifndef NO_BOOST_REGEX   
#include <boost/regex.hpp>
#endif

#if BOOST_MINOR > 76
#include <boost/system.hpp>
#else // BOOST_MINOR
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#endif // BOOST_MINOR

#include <boost/thread.hpp>

#ifdef _MSC_VER
#pragma warning ( disable : 4701 ) // CRC
#endif

#include <boost/crc.hpp>

#ifndef NO_JSONIC
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS ) // boost
#endif // _MSC_VER
#include <boost/json.hpp>
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
#endif // NO_JSONIC

#ifndef NOCURL
#include <curl/curl.h>
#endif // NOCURL
#endif // SSC_TEST

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#ifndef NO_GSL
#include <gsl/gsl>
#define GSL_SPAN(ARRAY, MAXLEN) ::gsl::span (ARRAY, MAXLEN)
#define GSL_NARROW_CAST ::gsl::narrow_cast
#define GSL_AT(ARRAY, ENTRY) ::gsl::at (ARRAY, ENTRY)
#define GSL_OWNER(TYPE) ::gsl::owner < TYPE * >
#define GSL_NOT_NULL(TYPE) ::gsl::not_null < TYPE >
#else // NO_GSL
#define GSL_SPAN(ARRAY, MAXLEN) ARRAY
#define GSL_NARROW_CAST static_cast
#define GSL_AT(ARRAY, ENTRY) ARRAY [ENTRY]
#define GSL_NOT_NULL(TYPE) TYPE
#define GSL_OWNER(TYPE) TYPE
#endif // NO_GSL

#ifndef NO_FALLTHROUGH
#define FALLTHROUGH [[fallthrough]]
#else // NO_FALLTHROUGH
#define FALLTHROUGH
#endif // NO_FALLTHROUGH

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

#define WEBMENTION "webmention"
#define SEP "."

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
#define DENARY "0123456789"
#define DDD DENARY "-."
#define SIGNEDDECIMAL DDD "+"
#define EXPONENTIAL SIGNEDDECIMAL "Ee"
#define POSITIVE DENARY "+."
#define OCTAL "01234567"
#define HEX DENARY "abcdefABCDEF"
#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define ALPHABET UPPERCASE LOWERCASE
#define ALPHANUMERIC ALPHABET DENARY
#define ALPHADDD ALPHABET DDD
#define B64BIN ALPHADDD "+/= "
#define IDS ALPHADDD "_:"
#define HYPHENATED ALPHANUMERIC "-"
#define DOMAINNAME ALPHANUMERIC ".-_"
#define TEL HEX "+*()-.#*_!~'[]/ "
#define REAL SIGNEDDECIMAL "Ee"
#define LINE_SEPARATORS "\n\r\f\v"

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

#define MAX_IDEAL_TITLE_LENGTH 32

#define MICROFORMATS_ORG    "microformats.org"
#define SCHEMA_ORG          "schema.org"
#define PURL_ORG            "purl.org"
#define N_WHATWG_ORG        "n.whatwg.org"
#define RDFS_ORG            "rdfs.org"
#define OGP_ME              "ogp.me"
#define W3_ORG              "www.w3.org"
#define SVG_2000            W3_ORG "/2000/svg"
#define XMLNS               "xmlns"
#define XHTMLNS             "xml"
#define XLINK               "xlink"

#define CC "creativecommons.org"
#define DBPEDIA "dbpedia.org"
#define OGC "www.ogc.org"
#define XCOM XMLNS ".com"
#define XOT XMLNS "xmlns.opentechnology.org/xslt-extensions"

#define HTTP_W3 HTTP W3_ORG
#define HTTPS_W3 HTTPS W3_ORG

#define HTTP_MF HTTP MICROFORMATS_ORG
#define HTTPS_MF HTTPS MICROFORMATS_ORG

#define NOFLAGS 0
typedef uint64_t flags_t; // at least 64 bits

#include "main/abort.h"

#endif // SCC_TEST

#define COMMENT_CHAR '/'
#define COMMENT_STRCHAR "/"

#ifdef NOCURL
#define CURLY
#else // NO_JSONIC
#define CURLY "c"
#endif // NO_JSONIC

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

#ifdef _MSC_VER
#ifndef OS
#define OS "Windows x64"
#endif // OS
#else
#ifndef OS_VER
#define OS "???"
#else // OS_VER
#define OS OS_VER
#endif // OS_VER
#endif // _MSC_VER

#ifdef NOICU
#define ICU_VER
#else // NOICU
#define ICU_VER ":" U_ICU_VERSION
#endif // NOICU

#ifdef DEBUG
#define DBG_STATUS "d"
#else // DEBUG
#define DBG_STATUS
#endif // DEBUG

#define BUILD_INFO   DBG_STATUS FUDDY CURLY JSNIC NPS_GEN SPELT ":" OS ":" COMPILER PROCSIZE ":" BOOST_LIB_VERSION ICU_VER
#define BASE_TITLE   FULLNAME " v" VERSION_STRING " (" WEBADDR ")\n"
#define SIMPLE_TITLE BASE_TITLE COPYRIGHT_TEXT "\n"
#define FULL_TITLE   BASE_TITLE COPYRIGHT "\n" "[" __DATE__ " " __TIME__  "] [" BUILD_INFO "]" "\n"
#define TEST_TITLE   FULLNAME " v" VERSION_STRING "\n" "(" __DATE__ " " __TIME__ ")\n" WEBADDR "\n" COPYRIGHT "\n\n"

// Enable this to see full messages that would otherwise be generated when using -T switch, roughly speaking
// #define EXPAND_TEST

#define TYPE_HELP "Type '" PROG " -h' for help."

extern const char* build_info;
extern const char* test_title;
extern const char* simple_title;
extern const char* full_title;

// I can't remember where these are! These macros do seem to confuse VC++, which is not useful.

#define DEFAULT_COPY(XXX, DDD) \
    XXX (const XXX & xxx) = DDD; \
    XXX& operator = (const XXX & xxx) = DDD; \

#define DEFAULT_MOVE(XXX, DDD) \
    XXX (XXX && xxx) = DDD; \
    XXX& operator = (XXX && xxx) = DDD

#define DEFAULT_COPY_MOVE(XXX) \
    DEFAULT_COPY (XXX, default) \
    DEFAULT_MOVE (XXX, default)

#define DEFAULT_COPY_NO_MOVE(XXX) \
    DEFAULT_COPY (XXX, default) \
    DEFAULT_MOVE (XXX, delete)

#define DEFAULT_NO_COPY_NO_MOVE(XXX) \
    DEFAULT_COPY (XXX, delete) \
    DEFAULT_MOVE (XXX, delete)

#define CONSTRUCT_DEFAULT(XXX) \
    XXX () = default; \
    DEFAULT_COPY_MOVE (XXX); \
    ~XXX () = default

#define CONSTRUCT_NO_COPY(XXX) \
    XXX () = default; \
    DEFAULT_NO_COPY_NO_MOVE (XXX); \
    ~XXX () = default

#define CONSTRUCT_DELETE(XXX) \
    XXX () = delete; \
    DEFAULT_NO_COPY_NO_MOVE (XXX); \
    ~XXX () = default

#define DEFAULT_CONSTRUCTORS(XXX) CONSTRUCT_DEFAULT (XXX)
#define DEFAULT_COPY_CONSTRUCTORS(XXX) DEFAULT_COPY_MOVE (XXX)
#define DEFAULT_NO_MOVE_CONSTRUCTORS(XXX) DEFAULT_COPY_NO_MOVE (XXX)
#define DEFAULT_NO_COPY_NO_MOVE_CONSTRUCTORS(XXX) DEFAULT_NO_COPY_NO_MOVE (XXX)
#define DEFAULT_NO_COPY_CONSTRUCTORS(XXX) CONSTRUCT_NO_COPY (XXX)

#define DEFAULT_CONSTRUCTORS_NO_EMPTY(XXX) \
    XXX () = delete; \
    DEFAULT_COPY_MOVE (XXX); \
    ~XXX () = default

#define DEFAULT_CONSTRUCTORS_VIRTUAL_DESTRUCTOR(XXX) \
    XXX () = default; \
    DEFAULT_COPY_MOVE (XXX); \
    virtual ~XXX () = default

#define NO_COPY_CONSTRUCTORS(XXX) DEFAULT_NO_COPY_NO_MOVE (XXX)
#define DELETE_CONSTRUCTORS(XXX) CONSTRUCT_DELETE (XXX)
