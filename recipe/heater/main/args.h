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

#define ARGLEN_MAX  4096

#define CORPUS_     "corpus"
#define ENVIRONMENT_ "environment"
#define GENERAL_    "general"
#define HTML_       "html"
#define LINKS_      "link"
#define MATH_       "math"
#define MF_         "microformat"
#define MICRODATA_  "microdata"
#define NITS_       "nits"
#define SHADOW_     "shadow"
#define STATS_      "stats"
#define SVG_        "svg"
#define VALIDATION_ "validation"
#define WEBSITE_    "site"
#define WMIN_       "webmention_in"
#define WMOUT_      "webmention_out"

#define JOIN        "."

#define CORPUS      CORPUS_ JOIN
#define ENVIRONMENT ENVIRONMENT_ JOIN
#define GENERAL     GENERAL_ JOIN
#define HTML        HTML_ JOIN
#define LINKS       LINKS_ JOIN
#define MF          MF_ JOIN
#define MATH        MATH_ JOIN
#define MICRODATA   MICRODATA_ JOIN
#define NITS        NITS_ JOIN
#define SHADOW      SHADOW_ JOIN
#define STATS       STATS_ JOIN
#define SVG         SVG_ JOIN
#define VALIDATION  VALIDATION_ JOIN
#define WEBSITE     WEBSITE_ JOIN
#define WMIN        WMIN_ JOIN
#define WMOUT       WMOUT_ JOIN

#define ALL         "all"
#define ARTICLE     "article"
#define ATTRIB      "attribute"
#define BODY        "body"
#define CATASTROPHE "catastrophe"
#define CGI         "cgi"
#define CHARSET     "charset"
#define CHANGED     "changed"
#define CHECK       "check"
#define CLASS       "class"
#define CODES       "codes"
#define COLOUR      "colour"
#define COLOR       "color"
#define COMMENT     "comment"
#define CONFIG      "config"
#define COPY        "copy"
#define CSS_OPTION  "css"
#define CURRENCY    "currency"
#define CUSTOM      "custom"
#define DBG         "debug"
#define DEFCONF     "defconf"
#define DETAIL      "detail"
#define DINGBATARG  "dingbat"
#define ERR         "error"
#define ELEMENT     "element"
#define ELEMATTR    ELEMENT "-" ATTRIB
#define EXPORT      "export"
#define EXTENSION   "extension"
#define EXTERNAL    "external"
#define FICHIER     "file"
#define FORWARD     "301"
#define HELP        "help"
#define HTTPEQUIV   "httpequiv"
#define HOOK        "hook"
#define IGNORED     "ignore"
#define INDEX       "index"
#define INFO        "info"
#define LANG        "lang"
#define MAIN        "main"
#define MAXFILESIZE "maxfilesize"
#define META        "meta"
#define METANAME    "metaname"
#define MICRODATAARG "microdata"
#define MINOR       "minor"
#define MIMETYPE    "mimetype"
#define MODE        "mode"
#define MSG         "msg"
#define NIDS        "nids"
#define ONCE        "once"
#define OUTPUT      "output"
#define PATH        "datapath"
#define PAGE        "page"
#define RDF         "rdf"
#define REL         "rel"
#define REVOKE      "no-revoke"
#define RFC1867     "rfc1867"
#define RFC1942     "rfc1942"
#define RFC1980     "rfc1980"
#define RFC2070     "rfc2070"
#define ROOT        "root"
#define RPT         "rpt"
#define SECRET      "secret"
#define SGML        "sgml"
#define SILENCE     "silence"
#define SITE        "domain"
#define SLOB        "slob"
#define SNIPPET     "snippet"
#define SPACING     "space"
#define SPEC        "spec"
#define SPLURGE      "splurge"
#define SSI         "ssi"
#define SUMMARY     "summary"
#define TAGS        "tags"
#define TEST        "test"
#define TITLE       "title"
#define UPDATE      "update"
#define USER        "user"
#define VERBOSE     "verbose"
#define VERIFY      "verify"
#define VERSION     "version"
#define VIRTUAL     "virtual"
#define WARNING     "warning"
#define WATCH       "watch"

#define CLEAR       "clear"
#define MACROSTART  "macrostart"
#define MACROEND    "macroend"
#define MENTION     "mention"
#define NOCHANGE    "nochange"
#define NOTIFY      "notify"
#define RESET       "reset"
#define STUB        "stub"
#define TEMPLATE    "template"
#define WRITE       "write"

#define TEST_HEADER "test-header"

#define EXT         ".ssc"
#define CFG         "config"

#define CONFIGURATION "." PROG "/" CFG

// environment
#define ENV_CONFIG          PROG "_" CONFIG
#define ENV_ARGS            PROG "_ARGS"
// OpenBSD httpd CGI environment variables (and probably many other www servers)
#define SERVER_SOFTWARE     "SERVER_SOFTWARE"
#define SERVER_NAME         "SERVER_NAME"
#define GATEWAY_INTERFACE   "GATEWAY_INTERFACE"
#define SERVER_PROTOCOL     "SERVER_PROTOCOL"
#define SERVER_PORT         "SERVER_PORT"
#define REQUEST_METHOD      "REQUEST_METHOD"
#define HTTP_ACCEPT         "HTTP_ACCEPT"
#define PATH_INFO           "PATH_INFO"
#define PATH_TRANSLATED     "PATH_TRANSLATED"
#define SCRIPT_NAME         "SCRIPT_NAME"
#define QUERY_STRING        "QUERY_STRING"
#define REMOTE_HOST         "REMOTE_HOST"
#define REMOTE_ADDR         "REMOTE_ADDR"
#define REMOTE_USER         "REMOTE_USER"
#define AUTH_TYPE           "AUTH_TYPE"
#define CONTENT_TYPE        "CONTENT_TYPE"
#define CONTENT_LENGTH      "CONTENT_LENGTH"
