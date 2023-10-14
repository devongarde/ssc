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

#define ARGLEN_MAX  4096

#define CORPUS_     "corpus"
#define CSS_        "css"
#define ENVIRONMENT_ "environment"
#define GENERAL_    "general"
#define HTML_       "html"
#define JSONLD_     "jsonld"
#define LINK_      "link"
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
#define CSS         CSS_ JOIN
#define ENVIRONMENT ENVIRONMENT_ JOIN
#define GENERAL     GENERAL_ JOIN
#define HTML        HTML_ JOIN
#define JSONLD      JSONLD_ JOIN
#define LINKS       LINK_ JOIN
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

#define ABHORRENT   "abhorrent"
#define ACCEPT      "accept"
#define ALL         "all"
#define ADJUST      "adjust"
#define ANIMATION   "animation"
#define ARTICLE     "article"
#define ATTRIB      "attribute"
#define BACKGROUND  "background"
#define BODY        "body"
#define BOX_ALIGN   "box-align"
#define BOX_MODEL   "box-model"
#define BOX_SIZING  "box-sizing"
#define BUILD       "build"
#define CACHE       "cache"
#define CASED       "case"
#define CASCADE     "cascade"
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
#define COMPOSITING "compositing"
#define COND_RULE   "cond-rule"
#define CONFIG      "config"
#define CONTAIN     "contain"
#define COPY        "copy"
#define CORE        "core"
#define COUNTRY     "country"
#define CSS_OPTION  "css"
#define CURRENCY    "currency"
#define CS          "cs"
#define CUSTOM      "custom"
#define DATAPATH    "datapath"
#define DATETIME    "datetime"
#define DC          "dc"
#define DBG         "debug"
#define DEFCONF     "defconf"
#define DEFTHRD     "defthrd"
#define DETAIL      "detail"
#define DEVICE      "device"
#define DICT        "dict"
#define DINGBATARG  "dingbat"
#define DISPLAY     "display"
#define DONT        "no-"
#define DRAFT       "draft"
#define EASE        "ease"
#define ELEMENT     "element"
#define ELEMATTR    ELEMENT "-" ATTRIB
#define ENABLE      "enable"
#define ENDPOINT    "endpoint"
#define ERR         "error"
#define EXAMPLE     "example"
#define EXCLUDE     "exclude"
#define EXPORT      "export"
#define EXTENSION   "extension"
#define EXTERNAL    "external"
#define EXTRA       "extra"
#define FBL         "fbl"
#define FICHIER     "file"
#define FILTER      "filter"
#define FF          "ff"
#define FOAF        "foaf"
#define FORCE       "force"
#define FORWARD     "301"
#define FORMAT      "format"
#define FONT        "font"
#define FRAG        "frag"
#define FV          "fv"
#define GIT         "git"
#define GRID        "grid"
#define HEADER      "header"
#define HELP        "help"
#define HTTPEQUIV   "httpequiv"
#define HOOK        "hook"
#define ICU         "icu"
#define IE          "ie"
#define IGNORED     "ignore"
#define IMAGE       "image"
#define INDEX       "index"
#define INFO        "info"
#define INLINE      "inline"
#define INPUT       "input"
#define LANG        "lang"
#define LINE_GRID   "line-grid"
#define LIST        "list"
#define LOCAL       "local"
#define LOGIC       "logic"
#define MAIN        "main"
#define MASKING     "masking"
#define MAXFILESIZE "maxfilesize"
#define MEDIA       "media"
#define MENTIONS    MENTION_ "s"
#define META        "meta"
#define METANAME    "metaname"
#define MICRODATAARG "microdata"
#define MINOR       "minor"
#define MIMETYPE    "mimetype"
#define MOBILE      "mobile"
#define MODE        "mode"
#define MSG         "msg"
#define MULTI_COLUMN "multi-column"
#define NAMESPACE   "namespace"
#define NIDS        "nids"
#define ONCE        "once"
#define OUTPUT      "output"
#define OVERFLOH    "overflow"
#define OVERRIDE    "override"
#define PATH        "path"
#define PAGE        "page"
#define POSITION    "position"
#define PRETEND     "pretend"
#define PRINT       "print"
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
#define SAFARI      "safari"
#define SCROLLBAR   "scrollbar"
#define SECRET      "secret"
#define SENDER      "sender"
#define SELECTOR    "selector"
#define SGML        "sgml"
#define SHAPE       "shape"
#define SNAP        "snap"
#define SILENCE     "silence"
#define SITE        "domain"
#define SLOB        "slob"
#define SOURCE      "source"
#define SPACING     "space"
#define SPEC        "spec"
#define SPEECH      "speech"
#define SPLURGE     "splurge"
#define SSI         "ssi"
#define STRUCTURE   "struct"
#define STYLE       "style"
#define SUBSTITUTE  "substitute"
#define SUMMARY     "summary"
#define SYNTAX      "syntax"
#define TABLE       "table"
#define TAGS        "tags"
#define TARGET      "target"
#define TEST        "test"
#define TEXT_ARG    "text"
#define TEXT_DEC    "text-dec"
#define TITLE       "title"
#define THREAD      "thread"
#define TRANSFORM   "transform"
#define TRANSITION  "transition"
#define TV          "tv"
#define UNIQUE      "unique"
#define UPDATE      "update"
#define UI          "ui"
#define USER        "user"
#define VALUE       "value"
#define VARIABLE    "variable"
#define VERBOSE     "verbose"
#define VERIFY      "verify"
#define VER         "version"
#define VERSION     "version"
#define VIRTUAL     "virtual"
#define WARNING     "warning"
#define WATCH       "watch"
#define WC          "wc"
#define WRITING     "writing"
#define XSD         "xsd"
#define XXX         "xxx"

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
