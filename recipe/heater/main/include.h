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

#define SSC_LU "ssc.lu"
#define DYLANHARRIS_ORG "dylanharris.org"

#define PROG "ssc"
#define TESTPROG PROG "-test"
#define FULLNAME "Static Site Checker"
#define WEBADDR "https://" SSC_LU "/"

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_RELEASE 126
#define VERSION_STRING "0.0.126"

#define NBSP "&nbsp;"
#define COPYRIGHT_SYMBOL "(c)"
#define COPYRIGHT_FORENAME "Dylan"
#define COPYRIGHT_SURNAME "Harris"
#define COPYRIGHT_YEAR "2020-2022"
#define COPYRIGHT_TEXT COPYRIGHT_SYMBOL " " COPYRIGHT_YEAR " " COPYRIGHT_FORENAME " " COPYRIGHT_SURNAME
#define COPYRIGHT_HTML "&copy;" NBSP COPYRIGHT_YEAR NBSP COPYRIGHT_FORENAME NBSP COPYRIGHT_SURNAME
#define COPYRIGHT_WEBADDR "https://" DYLANHARRIS_ORG "/"
#define COPYRIGHT_BRADDR " (" COPYRIGHT_WEBADDR ")"
#define COPYRIGHT COPYRIGHT_TEXT COPYRIGHT_BRADDR
#define COPYRIGHT_HTML_FULL "&copy;" NBSP COPYRIGHT_YEAR NBSP COPYRIGHT_FORENAME NBSP COPYRIGHT_SURNAME COPYRIGHT_BRADDR

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

#if ! defined (NOSPELL) && ! defined (HUNSPELL) && ! defined (WINSPELL)
#define NOSPELL
#endif

#ifdef NOICU
#define NOSPELL
#endif // NOICU

#if defined (NOSPELL)
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

#ifdef __clang__
#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#define COMPILER "c"
#define MSVC_NOEXCEPT
#define PROCSIZE "64"
#elif ! defined (_MSC_VER)
#define COMPILER "g"
#define MSVC_NOEXCEPT
#define PROCSIZE "64"
#else // __clang__
#define COMPILER "m"

#define NOLYNX
#define NO_BOOST_PROCESS            // it crashed the MSVC 2019 linter, on my system at least
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
    // 26410/5/8: correct, in that particular place. So what? Smart pointers are indeed pointers. An unwrapped pointer (usually) means
    //      the code doesn't own it, by convention.
#pragma warning (disable : 6330 26409 26410 26415 26418 26434 26439 26455 26456 26461 26485)

// https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
#if _MSC_VER >= 1930
#pragma warning (disable : 26812)
#define _WIN32_WINNT 0x0A00 // 10
#define STRINGPIECE_BIZARRO
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
#define ORDERED
#define FUDDY "f"
#else // FUDDYDUDDY
#define FUDDY
#endif // FUDDYDUDDY

#include <iostream>
#include <vector>
#include <set>
#include <assert.h>
#include <map>

#ifndef SSC_TEST
#include <string>
#include <string_view>
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

#ifndef NOICU
#include <unicode/uvernum.h>
#include <unicode/umachine.h>
#include <unicode/utf.h>
#include <unicode/utypes.h>
#include <unicode/uenum.h>
#include <unicode/utypes.h>
#include <unicode/putil.h>
#include <unicode/uiter.h>
#include <unicode/uloc.h>
#include <unicode/utext.h>
#include <unicode/localpointer.h>
#include <unicode/parseerr.h>
#include <unicode/stringoptions.h>
#include <unicode/ucpmap.h>
#include <unicode/ucsdet.h>
#include <unicode/ucnv.h>
#include <unicode/unistr.h>
#include <unicode/errorcode.h>
#include <unicode/normalizer2.h>
#include <unicode/localematcher.h>
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

#if defined (_MSC_VER) && defined (HUNSPELL)
#define HUNSPELL_STATIC
#pragma comment (lib, "libhunspell.lib")
#endif // _MSC_VER && HUNSPELL

#endif // SSC_TEST

#include <boost/version.hpp>
#include <boost/static_assert.hpp>

#define BOOST_MAJOR ( BOOST_VERSION / 100000 )
#define BOOST_MINOR ( BOOST_VERSION / 100 % 1000 )
#define BOOST_RELEASE ( BOOST_VERSION % 100 )

BOOST_STATIC_ASSERT (BOOST_MAJOR == 1);

#if BOOST_MINOR < 73
#define FS_THROWS
#endif // 1.73

#if BOOST_MINOR < 72
#define NO_DIROPTS
#endif // 1.72

#ifndef SSC_TEST
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

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/string_path.hpp>
#include <boost/log/trivial.hpp>
#include <boost/logic/tribool.hpp>

#ifdef _MSC_VER
#pragma warning ( disable : 4701 ) // CRC
#endif

#include <boost/crc.hpp>

#ifndef NO_BOOST_PROCESS
#include <boost/process.hpp>
#endif // NO_BOOST_PROCESS

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

#endif // SSC_TEST

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <gsl/gsl>

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

#define CSS "://"
#define HTTP PR_HTTP CSS
#define HTTPS PR_HTTPS CSS
#define SPACE ' '
#define COLON ':'
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
#define POSITIVE DENARY "+."
#define OCTAL "01234567"
#define HEX DENARY "abcdefABCDEF"
#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define ALPHABET UPPERCASE LOWERCASE
#define ALPHANUMERIC ALPHABET DDD
#define B64BIN ALPHANUMERIC "+/= "
#define IDS ALPHANUMERIC "_:"
#define TEL HEX "+*()-.#*_!~'[]/ "
#define REAL SIGNEDDECIMAL "Ee"
#define LINE_SEPARATORS "\n\r\f\v"

#define DEFAULT_DOMAIN "example.org"
#define CSS_TYPE "text/css"
#define HTML_TYPE "text/html"

#define NOFLAGS 0
#define EXPORT_EXTENSION ".json"
#define QNONE "'none'"

#define US_ASCII "US-ASCII"
#define LATIN_1 "ISO-8859-1"
#define UTF_8 "UTF-8"
#define STANDARD_ENGLISH "en-GB"
#define WEB_ENGLISH "en-US"

#define DISGUSTING "nonce" // Why The F*ck the standards have to reference paedophiles, I have no clue, but I do NOT like it

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

typedef uint64_t flags_t; // at least 64 bits

#include "main/abort.h"

#endif // SCC_TEST

#ifdef NO_BOOST_PROCESS
#define BP_VER
#else  // NO_BOOST_PROCESS
#define BP_VER "p"
#endif // NO_BOOST_PROCESS

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

#ifndef MACOS
#define MAC_VER
#elif defined (MONETERY)
#define MAC_VER "M"
#elif defined (BIG_SUR)
#define MAC_VER "B"
#elif defined (CATALINA)
#define MAC_VER "C"
#elif defined (MOJAVE)
#define MAC_VER "m"
#elif defined (HIGH_SIERRA)
#define MAC_VER "H"
#else
#define MAC_VER "?"
#endif

#ifdef O68
#define OBSD_VER "8"
#elif defined (O69)
#define OBSD_VER "9"
#elif defined (HIGH_SIERRA)
#define OBSD_VER "0"
#elif defined (OPENBSD)
#define OBSD_VER "O"
#else
#define OBSD_VER
#endif // O68

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

#define BUILD_INFO BP_VER DBG_STATUS FUDDY JSNIC NPS_GEN SPELT MAC_VER OBSD_VER ":" COMPILER PROCSIZE ":" BOOST_LIB_VERSION ICU_VER

#define BASE_TITLE \
            FULLNAME " " VERSION_STRING "\n" \
            WEBADDR "\n" \
            COPYRIGHT "\n"

#define SIMPLE_TITLE BASE_TITLE

#define FULL_TITLE \
        BASE_TITLE \
        "[" __DATE__ " " __TIME__  "] [" BUILD_INFO "]" \
        "\n"

#define TEST_TITLE \
            FULLNAME " " VERSION_STRING "\n" \
            "(" __DATE__ " " __TIME__ ")\n" \
            WEBADDR "\n" \
            COPYRIGHT "\n\n"
