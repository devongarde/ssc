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

#define SSC_LU "ssc.lu"
#define DYLANHARRIS_ORG "dylanharris.org"

#define PROG "ssc"
#define TESTPROG PROG "-test"
#define FULLNAME "Static Site Checker"
#define WEBADDR "https://" SSC_LU "/"

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_RELEASE 113
#define VERSION_STRING "0.0.113"

#define NBSP "&nbsp;"
#define COPYRIGHT_SYMBOL "(c)"
#define COPYRIGHT_FORENAME "Dylan"
#define COPYRIGHT_SURNAME "Harris"
#define COPYRIGHT_YEAR "2020,2021"
#define COPYRIGHT_TEXT COPYRIGHT_SYMBOL " " COPYRIGHT_YEAR " " COPYRIGHT_FORENAME " " COPYRIGHT_SURNAME
#define COPYRIGHT_HTML "&copy;" NBSP COPYRIGHT_YEAR NBSP COPYRIGHT_FORENAME NBSP COPYRIGHT_SURNAME
#define COPYRIGHT_WEBADDR "https://" DYLANHARRIS_ORG "/"
#define COPYRIGHT_BRADDR " (" COPYRIGHT_WEBADDR ")"
#define COPYRIGHT COPYRIGHT_TEXT COPYRIGHT_BRADDR
#define COPYRIGHT_HTML_FULL "&copy;" NBSP COPYRIGHT_YEAR NBSP COPYRIGHT_FORENAME NBSP COPYRIGHT_SURNAME COPYRIGHT_BRADDR

#define SIMPLE_TITLE_D \
            FULLNAME " " VERSION_STRING \
            "D (" __DATE__ " " __TIME__ ")" \
            ", " WEBADDR "\n" COPYRIGHT "\n\n"
#define SIMPLE_TITLE_N \
            FULLNAME " " VERSION_STRING \
            ", " WEBADDR "\n" COPYRIGHT "\n\n"

#ifdef DEBUG
#define SIMPLE_TITLE SIMPLE_TITLE_D
#else // DEBUG
#define SIMPLE_TITLE SIMPLE_TITLE_N
#endif // DEBUG

#ifdef __clang__
#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#define CONSTEXPR constexpr
#define NOEXCEPT noexcept
#endif // __clang__

#ifdef __GNUC__
#define CONSTEXPR constexpr
#define NOEXCEPT noexcept
#endif // __GNUC__

#ifdef _MSC_VER
#include <codeanalysis\warnings.h>
#ifdef WIN32
#define X32
#define SMALLINT
#else // WIN32
#define X64
#endif // WIN32
#define NOLYNX
#pragma warning (push,3)
#pragma warning ( disable : 4244 ) // boost
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS ) // boost
#if defined (VS2019)
#define _WIN32_WINNT 0x0A00 // 10
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS // boost
#define _CRT_SECURE_NO_WARNINGS // boost
#define CONSTEXPR constexpr
#define NOEXCEPT noexcept
#define VS 19
#define CLEAN_SHAREDPTR_ARRAY
#elif defined (VS2017)
#define _WIN32_WINNT 0x0603 // 8.1
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS // boost
#define _CRT_SECURE_NO_WARNINGS // boost
#define CONSTEXPR constexpr
#define NOEXCEPT noexcept
#define VS 17
#define CLEAN_SHAREDPTR_ARRAY
#define SMALLINT
#else // VS...
#error ssc only builds with VS 2017 / 2019.
#endif // VS...
#endif // _MSC_VER

#ifdef FUDDYDUDDY
#define BOOVAR 2
#define ORDERED
#endif // FUDDYDUDDY

#include <iostream>
#include <vector>
#include <set>
#include <assert.h>
#include <map>

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
#include <boost/locale.hpp>
#ifndef NO_PROCESS
#include <boost/process.hpp>
#endif // NO_PROCESS
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/string_path.hpp>
#include <boost/log/trivial.hpp>

#ifdef _MSC_VER
#pragma warning ( disable : 4701 ) // CRC
#endif

#include <boost/crc.hpp>

#endif // SSC_TEST

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#ifndef SSC_TEST
#include <unicode/ucsdet.h>
#include <unicode/ucnv.h>
#ifdef _MSC_VER
#pragma comment (lib, "icudt.lib")
#pragma comment (lib, "icuin.lib")
#pragma comment (lib, "icuio.lib")
#pragma comment (lib, "icutu.lib")
#pragma comment (lib, "icuuc.lib")
#endif // _MSC_VER
#endif // SSC_TEST

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning (pop)
#endif

#if defined (DEBUG) || defined (_DEBUG) || defined (SSC_ASSERTS)
#  ifndef DEBUG
#  define DEBUG
#  endif // DEBUG
#else // debug
#  ifndef NDEBUG
#  define NDEBUG
#  endif // NDEBUG
#endif // debug

#ifdef DEBUG
// prefer the macros below (PRESUME, etc.)
#define DBG_ASSERT(x) assert (x)
#else // DEBUG
#define DBG_ASSERT(x)
#endif // DEBUG

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
#define DECIMAL DDD "+"
#define POSITIVE DENARY "+."
#define OCTAL "01234567"
#define HEX DENARY "abcdefABCDEF"
#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define ALPHABET UPPERCASE LOWERCASE
#define ALPHADDD ALPHABET DDD
#define B64BIN ALPHADDD "+/= "
#define IDS ALPHADDD "_:"
#define TEL HEX "+*()-.#*_!~'[]/ "
#define REAL DECIMAL "Ee"
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

#define DISGUSTING "nonce" // Why The F*ck the standards have to reference paedophiles, I have no clue, but I do NOT like it

#define MAX_IDEAL_TITLE_LENGTH 32

#define MICROFORMATS_ORG    "microformats.org"
#define SCHEMA_ORG          "schema.org"
#define PURL_ORG            "purl.org"
#define N_WHATWG_ORG        "n.whatwg.org"
#define RDFS_ORG            "rdfs.org"
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
