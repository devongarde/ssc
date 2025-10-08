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

   /*   a ask & answer   A reports params & exit
        b
        c persist file   C prog dir
        d dump corpus    D dump progress
        e external check E severity error exit
        f config         F load config file from .ssc/config
        g website root   G Check spelling
        h help           H html snippet
        i index file     I server side includes
        j GENERAL SPEC   J GENERAL INFO
        k
        l link check     L virtual directory
        m microdata      M microformat
        n              
        o output         O rpt ext once
        p                P NIT OVERRIDE
        q shell          Q
        r no revoke chks R HTML revision
        s domain name    S stats
        t                T test mode
        u                U unique
        v verbose        V version
        w                W cgi
        x extensions     X check cross-linked ids
        y GENERAL THREAD Y GENERAL DEFTHRD              
        z title max      Z
        0 dont ask
        1
        2
        3 report http 30*
        4
        5 HTML minor
        6
        7 original analysis
        8
        9 */

#define DONTASK_SW_ "0"
#define FORWARD_SW_ "3"
#define MINOR_SW_   "5"
#define ANAL_SW_    "7"
#define ASK_SW_     "a"
#define SWITCH_SW_  "A"
#define PERSIST_SW_ "c"
#define DTPTH_SW_   "C"
#define DUMP_SW_    "d"
#define PRGRSS_SW_  "D"
#define EXTERN_SW_  "e"
#define ERREXT_SW_  "E"
#define FILE_SW_    "f"
#define DEFCONF_SW_ "F"
#define ROOT_SW_    "g"
#define SPELL_SW_   "G"
#define HELP_SW_    "h"
#define SNIPPET_SW_ "H"
#define INDEX_SW_   "i"
#define SSI_SW_     "I"
#define SPEC_SW_    "j"
#define INFO_SW_    "J"
#define CHECK_SW_   "l"
#define VIRTUAL_SW_ "L"
#define MDATA_SW_   "m"
#define MFVER_SW_   "M"
#define OUTPUT_SW_  "o"
#define ONCE_SW_    "O"
#define OVRRD_SW_   "P"
#define SHELL_SW_   "q"
#define REVOKE_SW_  "r"
#define HTMLVER_SW_ "R"
#define SITE_SW_    "s"
#define SUMMARY_SW_ "S"
#define TEST_SW_    "T"
#define UNIQUE_SW_  "U"
#define VERBOSE_SW_ "v"
#define VERSION_SW_ "V"
#define CGI_SW_     "W"
#define EXT_SW_     "x"
#define XLINK_SW_   "X"
#define THREAD_SW_  "y"
#define DFTHRD_SW_  "Y"
#define TITLE_SW_   "z"

#define SMPLSWTCH   "-"
#define FNCYSWTCH   "--"

#define DFTHRD_SW   SMPLSWTCH DFTHRD_SW_
#define FILE_SW     SMPLSWTCH FILE_SW_
#define PERSIST_SW  SMPLSWTCH PERSIST_SW_
#define PRGRSS_SW   SMPLSWTCH PRGRSS_SW_
#define ROOT_SW     SMPLSWTCH ROOT_SW_
#define SNIPPET_SW  SMPLSWTCH SNIPPET_SW_
#define VERBOSE_SW  SMPLSWTCH VERBOSE_SW_

#define ATOMIC_     "atom"
#define CORPUS_     "corpus"
#define CSS_        "css"
#define ENVIRONMENT_ "environment"
#define GENERAL_    "general"
#define HTML_       "html"
#define JSONLD_     "jsonld"
#define LINK_       "link"
#define MATH_       "math"
#define MENTION_    "mention"
#define MF_         "microformat"
#define MICRODATA_  "microdata"
#define NITS_       "nits"
#define ONTOLOGY_   "ontology"
#define OUTPUT_     "output"
#define RSL_        "rsl"
#define RSS_        "rss"
#define SERVER_     "server"
#define SP          "shadow"
#define SHADOW_     SP
#define SPELL_      "spell"
#define SSI_        "ssi"
#define STATS_      "stats"
#define SVG_        "svg"
#define VALIDATION_ "validation"
#define VTT_        "vtt"
#define WEBSITE_    "site"

#define ATOMIC      ATOMIC_ JOIN
#define BLACKLIST   BLACKLIST_ JOIN
#define BLUELIST    BLUELIST_ JOIN
#define CORPUS      CORPUS_ JOIN
#define CSS         CSS_ JOIN
#define ENVIRONMENT ENVIRONMENT_ JOIN
#define GENERAL     GENERAL_ JOIN
#define HTML        HTML_ JOIN
#define JSONLD      JSONLD_ JOIN
#define LINKS       LINK_ JOIN
#define MF          MF_ JOIN
#define MATH        MATH_ JOIN
#define MENTION     MENTION_ JOIN
#define MICRODATA   MICRODATA_ JOIN
#define NITS        NITS_ JOIN
#define ONTOLOGY    ONTOLOGY_ JOIN
#define OUTPUT      OUTPUT_ JOIN
#define RSL         RSL_ JOIN
#define RSS         RSS_ JOIN
#define SERVER      SERVER_ JOIN
#define SHADOW      SHADOW_ JOIN
#define SPELL       SPELL_ JOIN
#define SSC         PROG JOIN
#define SSI         SSI_ JOIN
#define STATS       STATS_ JOIN
#define SVG         SVG_ JOIN
#define VALIDATION  VALIDATION_ JOIN
#define VTT         VTT_ JOIN
#define WEBSITE     WEBSITE_ JOIN
#define WHITELIST   WHITELIST_ JOIN

#define ABBR        "abbreviation"
#define ABHORRENT   "abhorrent"
#define APATH       "absolute-path"
#define ACCEPT      "accept"
#define ACCOUNT     "account"
#define ADDRESS     "address"
#define ADJUST      "adjust"
#define ALL         "all"
#define ADVLAY      "adv-lay"
#define ANALYSIS    "analysis"
#define ANCHOR      "anchor"
#define ANCHOR_POS  "anchor-pos"
#define ANIMATION   "animation"
#define ANNOTATION  "annotation"
#define ARIA        "aria"
#define ARTICLE     "article"
#define ASK         "ask"
#define ATTRIB      "attribute"
#define BACK        "back"
#define BACKGROUND  "background"
#define BODY        "body"
#define BOX_ALIGN   "box-align"
#define BOX_MODEL   "box-model"
#define BOX_SIZING  "box-sizing"
#define BUILD       "build"
#define CACHE       "cache"
#define CASED       "case"
#define CASCADE     "cascade"
#define CAT         "category"
#define CATASTROPHE "catastrophe"
#define CGI         "cgi"
#define CHARVAR     "character-variant"
#define CHARSET     "charset"
#define CHANGED     "changed"
#define CHECK       "check"
#define CHROME      "chrome"
#define CLASS       "class"
#define CLASSIC     "classic"
#define CODES       "codes"
#define COLOUR      "colour"
#define COLOR       "color"
#define COMMENT     "comment"
#define COMMON      "common"
#define COMMS       "comms"
#define COMPOSITING "compositing"
#define COND_RULE   "cond-rule"
#define CONFIG      "config"
#define CONTAIN     "contain"
#define CON_TENT    "content"
#define CONNAME     "content-name"
#define COPY        "copy"
#define CORE        "core"
#define COUNTRY     "country"
#define COUSTYLE    "counter-style"
#define CS          "cs"
#define CSS_OPTION  "css"
#define CSSPROP     "css-property"
#define CURRENCY    "currency"
#define CUSTMED     "custom-media"
#define CUSTPROP    "custom-property"
#define CUSTOM      "custom"
#define DATAPATH    "datapath"
#define DATETIME    "datetime"
#define DBG         "debug"
#define DDICT       "ddict"
#define DEFCONF     "defconf"
#define DEFTHRD     "defthrd"
#define DESCRIPTION "description"
#define DETAIL      "detail"
#define DEVICE      "device"
#define DFN         "definition"
#define DICT        "dict"
#define DLANG       "dlang"
#define DINGBATARG  "dingbat"
#define DISPLAY     "display"
#define DOCARGS     "docargs"
#define DONT        "no-"
#define DRAFT       "draft"
#define DTDD        "name-value"
#define EDE         "ede"
#define EASE        "ease"
#define ECHOMSG     "echomsg"
#define EFFICIENT   "efficient"
#define ELEMENT     "element"
#define ELEMATTR    ELEMENT "-" ATTRIB
#define ENABLE      "enable"
#define ENDPOINT    "endpoint"
#define ERRMSG      "errmsg"
#define WHOOPS      "error"
#define ERROREXIT   "errorexit"
#define EXAMPLE     "example"
#define EXCLUDE     "exclude"
#define EXECRUN     "exec-run"
#define EXECTEXT    "exec-text"
#define EXPAND      "expand"
#define EXPORT      "export"
#define EXTENSION   "extension"
#define EXTERNAL    "external"
#define EXTRA       "extra"
#define FBL         "fbl"
#define FICHIER     "file"
#define FILTER      "filter"
#define FF          "ff"
#define FILL        "fill"
#define FLOAT       "float"
#define FONT        "font"
#define FONT_FAMILY "font-family"
#define FORCE       "force"
#define FORWARD     "301"
#define FORMAT      "format"
#define FRAG        "frag"
#define FV          "fv"
#define GIT         "git"
#define GRID        "grid"
#define HEADER      "header"
#define HELP        "help"
#define HELPSITE    "helpsite"
#define HIGHLIGHT   "highlight"
#define HISTFORM    "historical-form"
#define HTTPEQUIV   "httpequiv"
#define HOME        "home"
#define HOOK        "hook"
#define HYPERLINK   "hyperlink"
#define ICU         "icu"
#define ID          "id"
#define IE          "ie"
#define IGNORED     "ignore"
#define IMAGE       "image"
#define INDEX       "index"
#define INFO        "info"
#define INFORMATION "information"
#define INLINE      "inline"
#define INPUT       "input"
#define ITEMID      "itemid"
#define KEYFRAME    "keyframe"
#define LANG        "lang"
#define LASTMOD     "lastmod"
#define LAYER       "layer"
#define LINE_GRID   "line-grid"
#define LIST        "list"
#define LOCAL       "local"
#define LOGIC       "logic"
#define MAIN        "main"
#define MARQUEE     "marquee"
#define MATHCORE    "mathcore"
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
#define MOTION      "motion"
#define MOZILLA     "mozilla"
#define MSG         "msg"
#define MULTI_COLUMN "multi-column"
#define NAMESPACE   "namespace"
#define NES         "nes"
#define NESTING     "nesting"
#define NETSCAPE    "netscape"
#define NAUGHTY     "naughty"
#define NICE        "nice"
#define NIDS        "nids"
#define NOTE        "note"
#define ONCE        "once"
#define ONT         "ontology"
#define OPERA       "opera"
#define OPERATOR    "operator"
#define OPTBOOST    "boost"
#define OPTCOMP     "compiler"
#define OPTDEBUG    "debug"
#define OPTFUDDY    "fuddy"
#define OPTGUI      "gui"
#define OPTICU      "icu"
#define OPTJSON     "jsonic"
#define OPTNPS      "nps"
#define OPTOS       "os"
#define OPTPROC     "proc"
#define OPTSERVER   "server"
#define OPTSPELL    "spell"
#define ORNAMENT    "ornament"
#define OVERFLOH    "overflow"
#define OVERRIDE    "override"
#define OVERSCROLL  "overscroll"
#define PATH        "path"
#define PAGE        "page"
#define PAGE_NAME   "page-name"
#define PALETTE     "palette"
#define PARAMETERS  "parameters"
#define PASSFILE    "passfile"
#define PASSWORD    "password"
#define PORT        "port"
#define POSITION    "position"
#define PRESENT     "present"
#define PRETEND     "pretend"
#define PRETTY      "pretty"
#define PRINT       "print"
#define PRIVATE     "private"
#define PROGRESS    "progress"
#define PROPER      "property"
#define PSEUDO      "pseudo"
#define PUBLIC      "public"
#define QUERYSTRING "querystring"
#define QUOTE       "quote"
#define RDFA        "rdfa"
#define REFERENCE   "reference"
#define REGION      "region"
#define REL         "rel"
#define RPATH       "relative-path"
#define REPLACE     "replace"
#define REPORT      "report"
#define REQUIRED    "required"
#define REVOKE      "no-revoke"
#define RFC1867     "rfc1867"
#define RFC1942     "rfc1942"
#define RFC1980     "rfc1980"
#define RFC2070     "rfc2070"
#define RHYTHM      "rhythm"
#define ROUND       "round"
#define ROOT        "root"
#define RPT         "rpt"
#define RUBY        "ruby"
#define SAFARI      "safari"
#define SCOPE       "scope"
#define SCROLL_ANIM "scroll-anim"
#define SCROLLBAR   "scrollbar"
#define SDA         "sda"
#define SENDER      "sender"
#define SELECTED    "selected"
#define SELECTOR    "selector"
#define SGML        "sgml"
#define SHAPE       "shape"
#define SHELL       "shell"
#define SIGN        "sign"
#define SIGNATURE   "signature"
#define SILENCE     "silence"
#define SITE        "domain"
#define SLOVEN      "sloven"
#define SNAP        "snap"
#define SNAP_POINTS "snap-points"
#define SOURCE      "source"
#define SPACING     "space"
#define SPATIAL     "spatial"
#define SPEC        "spec"
#define SPECIAL     "special"
#define SPEECH      "speech"
#define SPLURGE     "splurge"
#define STATEMENT   "statement"
#define STRUCTURE   "struct"
#define STRUCTURE2  "structure"
#define STYLE       "style"
#define STYLESET    "styleset"
#define STYLESHEET  "stylesheet"
#define STYLISTIC   "stylistic"
#define SUBSTITUTE  "substitute"
#define SUMMARY     "summary"
#define SWASH       "swash"
#define SWITCHES    "switches"
#define SYSTEM      "system"
#define SYNTAX      "syntax"
#define TABLE       "table"
#define TAGS        "tags"
#define TARGET      "target"
#define TEST        "test"
#define TEXT_ARG    "text"
#define TEXT_DEC    "text-dec"
#define TIME        "time"
#define TITLE       "title"
#define THREAD      "thread"
#define TIMEFMT     "timefmt"
#define TRANSFORM   "transform"
#define TRANSITION  "transition"
#define TV          "tv"
#define UI          "ui"
#define UNIQUE      "unique"
#define UPDATE      "update"
#define URL_VAR     "url-var"
#define USER        "user"
#define USERNAME    "username"
#define VAL         "value"
#define VARIABLE    "variable"
#define VCS         "vcs"
#define VERBOSE     "verbose"
#define VERIFY      "verify"
#define VERSION     "version"
#define VIEW        "view"
#define VIEWPORT    "viewport"
#define VIRTUAL     "virtual"
#define WARNING     "warning"
#define WATCH       "watch"
#define WC          "wc"
#define WRITING     "writing"
#define WXARG       "wx"
#define WX_SNIPPET  "wx-snippet"
#define XXX         "xxx"
#define YGGDRISIL   "yggdrisil"

#define CLEAR       "clear"
#define MACROSTART  "macrostart"
#define MACROEND    "macroend"
#define NOTIFY      "notify"
#define RESET       "reset"
#define STUB        "stub"
#define TEMPLATE    "template"
#define WRITE       "write"

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

#define DEFAULT_ECHOMSG     "[Value Undefined]"
#define DEFAULT_ERRMSG      "[Oops, something broke.]"

#define NIT_HTML        "HTML"
#define NIT_SPEC        "SPEC"
#define NIT_STYLESHEET  "STYLESHEET"
#define NIT_TEST        "TEST"
#define NIT_TEXT        "TEXT"
#define NIT_XHTML       "XHTML"

#define ELEM_FEED       "feed"
#define ELEM_RSL        "rsl"
#define ELEM_RSS        "rss"
#define MAX_NODOC_LEN   4

#define NS_ATOM         "atom"
#define NS_RSL          ELEM_RSL
#define NS_RSS          ELEM_RSS
#define NSL_ATOM        HTTP_W3 "/2005/Atom"
#define NSLS_ATOM       HTTPS_W3 "/2005/Atom"
#define NSLS_RSL        HTTPS "rslstandard.org/rsl"
#define NSL_RSS         HTTP PURL_ORG "/rss/1.0/"
#define NSLS_RSS        HTTPS PURL_ORG "/rss/1.0/"


#define ARGLEN_MAX  4096
