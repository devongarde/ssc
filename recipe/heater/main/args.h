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

#define ARGLEN_MAX  4096

#define CORPUS_     "corpus"
#define ENVIRONMENT_ "environment"
#define GENERAL_    "general"
#define HTML_       "html"
#define JSONLD_     "jsonld"
#define LINKS_      "link"
#define MATH_       "math"
#define MENTION_    "mention"
#define MF_         "microformat"
#define MICRODATA_  "microdata"
#define NITS_       "nits"
#define ONTOLOGY_   "ontology"
#define RDFA_       "rdfa"
#define SHADOW_     "shadow"
#define SPELL_      "spell"
#define STATS_      "stats"
#define SVG_        "svg"
#define VALIDATION_ "validation"
#define WEBSITE_    "site"

#define JOIN        "."

#define CORPUS      CORPUS_ JOIN
#define ENVIRONMENT ENVIRONMENT_ JOIN
#define GENERAL     GENERAL_ JOIN
#define HTML        HTML_ JOIN
#define JSONLD      JSONLD_ JOIN
#define LINKS       LINKS_ JOIN
#define MF          MF_ JOIN
#define MATH        MATH_ JOIN
#define MICRODATA   MICRODATA_ JOIN
#define NITS        NITS_ JOIN
#define ONTOLOGY    ONTOLOGY_ JOIN
#define RDFA        RDFA_ JOIN
#define SHADOW      SHADOW_ JOIN
#define SPELL       SPELL_ JOIN
#define STATS       STATS_ JOIN
#define SVG         SVG_ JOIN
#define VALIDATION  VALIDATION_ JOIN
#define WEBSITE     WEBSITE_ JOIN
#define MENTION     MENTION_ JOIN

#define ACCEPT      "accept"
#define ALL         "all"
#define ARTICLE     "article"
#define ATTRIB      "attribute"
#define BODY        "body"
#define BUILD       "build"
#define CASED       "case"
#define CATASTROPHE "catastrophe"
#define CGI         "cgi"
#define CHARSET     "charset"
#define CHANGED     "changed"
#define CHECK       "check"
#define CLASS       "class"
#define CLASSIC     "classic"
#define CODES       "codes"
#define COLOUR      "colour"
#define COLOR       "color"
#define COMMENT     "comment"
#define CONFIG      "config"
#define COPY        "copy"
#define CORE        "core"
#define COUNTRY     "country"
#define CSS_OPTION  "css"
#define CURRENCY    "currency"
#define CUSTOM      "custom"
#define DATAPATH    "datapath"
#define DATETIME    "datetime"
#define DBG         "debug"
#define DC          "dc"
#define DEFCONF     "defconf"
#define DETAIL      "detail"
#define DICT        "dict"
#define DINGBATARG  "dingbat"
#define DONT        "no-"
#define DRAFT       "draft"
#define ERR         "error"
#define ELEMENT     "element"
#define ELEMATTR    ELEMENT "-" ATTRIB
#define ENABLE      "enable"
#define ENDPOINT    "endpoint"
#define EXAMPLE     "example"
#define EXCLUDE     "exclude"
#define EXPORT      "export"
#define EXTENSION   "extension"
#define EXTERNAL    "external"
#define FICHIER     "file"
#define FOAF        "foaf"
#define FORWARD     "301"
#define FORMAT      "format"
#define GIT         "git"
#define HEADER      "header"
#define HELP        "help"
#define HTTPEQUIV   "httpequiv"
#define HOOK        "hook"
#define ICU         "icu"
#define IGNORED     "ignore"
#define INDEX       "index"
#define INFO        "info"
#define INPUT       "input"
#define LANG        "lang"
#define LIST        "list"
#define LOCAL       "local"
#define MAIN        "main"
#define MAXFILESIZE "maxfilesize"
#define MENTIONS    MENTION_ "s"
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
#define OVERRIDE    "override"
#define PATH        "path"
#define PAGE        "page"
#define PROGRESS    "progress"
#define QUOTE       "quote"
#define REL         "rel"
#define REPORT      "report"
#define REVOKE      "no-revoke"
#define RFC1867     "rfc1867"
#define RFC1942     "rfc1942"
#define RFC1980     "rfc1980"
#define RFC2070     "rfc2070"
#define ROOT        "root"
#define RPT         "rpt"
#define SECRET      "secret"
#define SENDER      "sender"
#define SGML        "sgml"
#define SILENCE     "silence"
#define SITE        "domain"
#define SLOB        "slob"
#define SOURCE      "source"
#define SPACING     "space"
#define SPEC        "spec"
#define SPLURGE     "splurge"
#define SSI         "ssi"
#define STRUCTURE   "struct"
#define SUBSTITUTE  "substitute"
#define SUMMARY     "summary"
#define TAGS        "tags"
#define TARGET      "target"
#define TEST        "test"
#define TITLE       "title"
#define THREAD      "thread"
#define UNIQUE      "unique"
#define UPDATE      "update"
#define USER        "user"
#define VARIABLE    "variable"
#define VERBOSE     "verbose"
#define VERIFY      "verify"
#define VER         "version"
#define VERSION     "version"
#define VIRTUAL     "virtual"
#define WARNING     "warning"
#define WATCH       "watch"
#define XSD         "xsd"

#define CLEAR       "clear"
#define MACROSTART  "macrostart"
#define MACROEND    "macroend"
#define NOTIFY      "notify"
#define RESET       "reset"
#define STUB        "stub"
#define TEMPLATE    "template"
#define WRITE       "write"

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
