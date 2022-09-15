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

#include "main/standard.h"
#include "main/options.h"
#include "type/type.h"
#include "main/args.h"
#include "utility/filesystem.h"
#include "utility/lexical.h"
#include "feedback/nitpick.h"
#include "schema/schema_version.h"
#include "attribute/attributes.h"
#include "element/elem.h"
#include "element/element_classes.h"
#include "url/url_sanitise.h"
#include "type/type_master.h"
#include "parser/html_version.h"
#include "spell/spell.h"

#define GOTCHA  "WARNING: The examination of RDFa and ontologies (but for schema.org &\n" \
                "the living standard), is experimental and even less trustworthy than\n" \
                PROG " per se."

::std::string env_mapper (::std::string env)
{
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 4244)
#endif // _MSC_VER
    ::std::transform (env.begin (), env.end (), env.begin (), ::toupper);
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

    static sstr_t o;
    if (o.empty ())
    {   o.insert (ENV_CONFIG);
        o.insert (ENV_ARGS);
        o.insert (SERVER_SOFTWARE);
        o.insert (SERVER_NAME);
        o.insert (GATEWAY_INTERFACE);
        o.insert (SERVER_PROTOCOL);
        o.insert (SERVER_PORT);
        o.insert (REQUEST_METHOD);
        o.insert (HTTP_ACCEPT);
        o.insert (PATH_INFO);
        o.insert (PATH_TRANSLATED);
        o.insert (SCRIPT_NAME);
        o.insert (QUERY_STRING);
        o.insert (REMOTE_HOST);
        o.insert (REMOTE_ADDR);
        o.insert (REMOTE_USER);
        o.insert (AUTH_TYPE);
        o.insert (CONTENT_TYPE);
        o.insert (CONTENT_LENGTH); }
    if (o.find (env) != o.cend ()) return env;
    return ::std::string (); }

::std::string path_in_context (const ::std::string& file)
{   ::boost::filesystem::path res (context.path ());
    res /= file;
    return res.string (); }

void options::help (const ::boost::program_options::options_description& aid) const
{   ::std::string res;
    res =   PROG " [switch...] path.\n\n"
            PROG " is an opinionated HTML nit-picker. It notes broken links, dubious syntax,\n"
            "bad semantics, odd ontology, etc.. It highlights legal but untidy code.\n";
    ::std::ostringstream waste_of_space;
    waste_of_space << aid;
    res +=  waste_of_space.str ();
    res +=  "\n\n"
            "Configuration file section names precede each switch dot above (e.g.\n"
            GENERAL_ ", " LINKS_ "," WEBSITE_ "\n"
            ", etc.). Option names follow them. For example:\n\n"
            "[" GENERAL_ "]\n"
            VERBOSE "=2\n\n"
            "[" LINKS_ "]\n"
            CHECK "=1\n\n"
            "[" WEBSITE_ "]\n"
            EXTENSION "=html\n"
            INDEX "=index.shtml\n"
            SITE "=" DEFAULT_DOMAIN "\n\n"
            GOTCHA "\n\n";
    context.todo (do_simple);
    context.domsg (res); }

::std::string query_to_switches (const ::std::string& query)
{   ::std::string res;
    vstr_t args (split_by_charset (query, "&"));
    for (auto arg : args)
    {   vstr_t assignment (split_by_charset (arg, "="));
        if (assignment.size () == 0) continue;
        if (! res.empty ()) res += " ";
        res += "--";
        res += assignment.at (0);
        if (assignment.size () > 0)
        {   res += " ";
            res += slash_quote (decode (substitute_char (assignment.at (1), '+', ' '))); } }
    return res; }

e_severity decode_severity (nitpick& nits, const ::std::string& s)
{   nitpick nuts;
    e_severity sev = examine_value < t_severity > (nuts, html_tags, s);
    if (sev == es_undefined)
        if (s.length () == 1)
            if ((s.at (0) >= '0') && (s.at (0) <= '9'))
                sev = static_cast < e_severity > (s.at (0) - '0');
            else if ((s.at (0) >= 'A') && (s.at (0) <= 'C'))
                sev = static_cast < e_severity > (s.at (0) - 'A' + 10);
            else if ((s.at (0) >= 'a') && (s.at (0) <= 'c'))
                sev = static_cast < e_severity > (s.at (0) - 'a' + 10);
    if (sev == es_undefined)
        nits.pick (nit_configuration, es_error, ec_init, "invalid severity");
    return sev; }

void options::yea_nay (context_t& (context_t::*fn) (const bool ), nitpick& nits, const char* yea, const char* nay)
{   const bool on = var_ [yea].as <bool> ();
    const bool off = var_ [nay].as <bool> ();
    if (off)
    {   if (on) nits.pick (nit_yea_nay, es_info, ec_init, "when both ", nay, " and ", yea, " are used, ", nay, " applies");
        (context.*fn) (false); }
    else if (on) (context.*fn) (true); }

void options::process (nitpick& nits, int argc, char* const * argv)
{   /*  a
        b
        c persist file
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
        n GENERAL THREAD N GENERAL DEFTHRD              
        o output         O rpt ext once
        p prog dir       P NIT OVERRIDE
        q
        r no revoke chks
        s domain name    S stats
        t template       T test mode
        u update         U unique
        v verbose        V version
        w                W cgi
        x extensions     X check crosslinked ids
        y
        z title max      Z spec
        0
        1
        2
        3 report http 30*
        4
        5 HTML 5 mnr
        6
        7
        8
        9
*/

    ::boost::program_options::options_description
        aid (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        basic ("Command line options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        cgi (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        cmd (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        config (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        env (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        hidden,
        ontology ("Set default ontology version", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        primary ("General options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        valid ("Add common attribute values", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH);
    ::boost::program_options::positional_options_description pos;
    pos.add (WEBSITE ROOT, 1);
    basic.add_options ()
        (CONFIG ",f", ::boost::program_options::value < ::std::string > (), "Load configuration from this file.")
        (DEFCONF ",F", ::boost::program_options::bool_switch (), "Load configuration from " CONFIGURATION ".")
        (HELP ",h", ::boost::program_options::bool_switch (), "Output this information and exit.")
        (HTML SNIPPET ",H", ::boost::program_options::value < ::std::string > (), "Only nitpick the given snippet of HTML.")
        (ONTOLOGY LIST, ::boost::program_options::bool_switch (), "List known ontology schema for microdata and/or RDFa, then exit.")
        (VALIDATION_, ::boost::program_options::bool_switch (), "List attribute types that can be given additional 'valid' values, then exit.")
        (VERSION ",V", ::boost::program_options::bool_switch (), "Display version and copyright gen, then exit.")
        ;
    cgi.add_options ()
        (ENVIRONMENT SERVER_SOFTWARE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_SOFTWARE ".")
        (ENVIRONMENT SERVER_NAME, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_NAME ".")
        (ENVIRONMENT GATEWAY_INTERFACE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " GATEWAY_INTERFACE ".")
        (ENVIRONMENT SERVER_PROTOCOL, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_PROTOCOL ".")
        (ENVIRONMENT SERVER_PORT, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_PORT ".")
        (ENVIRONMENT REQUEST_METHOD, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REQUEST_METHOD ".")
        (ENVIRONMENT HTTP_ACCEPT, ::boost::program_options::value < ::std::string > (), "CGI environment variable " HTTP_ACCEPT ".")
        (ENVIRONMENT PATH_INFO, ::boost::program_options::value < ::std::string > (), "CGI environment variable " PATH_INFO ".")
        (ENVIRONMENT PATH_TRANSLATED, ::boost::program_options::value < ::std::string > (), "CGI environment variable " PATH_TRANSLATED ".")
        (ENVIRONMENT SCRIPT_NAME, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SCRIPT_NAME ".")
        (ENVIRONMENT QUERY_STRING, ::boost::program_options::value < ::std::string > (), "CGI environment variable " QUERY_STRING ".")
        (ENVIRONMENT REMOTE_HOST, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_HOST ".")
        (ENVIRONMENT REMOTE_ADDR, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_ADDR ".")
        (ENVIRONMENT REMOTE_USER, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_USER ".")
        (ENVIRONMENT AUTH_TYPE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " AUTH_TYPE ".")
        (ENVIRONMENT CONTENT_TYPE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " CONTENT_TYPE ".")
        (ENVIRONMENT CONTENT_LENGTH, ::boost::program_options::value < ::std::string > (), "CGI environment variable " CONTENT_LENGTH ".")
        ;
    env.add_options ()
        (SERVER_SOFTWARE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_SOFTWARE ".")
        (SERVER_NAME, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_NAME ".")
        (GATEWAY_INTERFACE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " GATEWAY_INTERFACE ".")
        (SERVER_PROTOCOL, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_PROTOCOL ".")
        (SERVER_PORT, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_PORT ".")
        (REQUEST_METHOD, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REQUEST_METHOD ".")
        (HTTP_ACCEPT, ::boost::program_options::value < ::std::string > (), "CGI environment variable " HTTP_ACCEPT ".")
        (PATH_INFO, ::boost::program_options::value < ::std::string > (), "CGI environment variable " PATH_INFO ".")
        (PATH_TRANSLATED, ::boost::program_options::value < ::std::string > (), "CGI environment variable " PATH_TRANSLATED ".")
        (SCRIPT_NAME, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SCRIPT_NAME ".")
        (QUERY_STRING, ::boost::program_options::value < ::std::string > (), "CGI environment variable " QUERY_STRING ".")
        (REMOTE_HOST, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_HOST ".")
        (REMOTE_ADDR, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_ADDR ".")
        (REMOTE_USER, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_USER ".")
        (AUTH_TYPE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " AUTH_TYPE ".")
        (CONTENT_TYPE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " CONTENT_TYPE ".")
        (CONTENT_LENGTH, ::boost::program_options::value < ::std::string > (), "CGI environment variable " CONTENT_LENGTH ".")
        (ENV_CONFIG, ::boost::program_options::value < ::std::string > (), "load configuration from this file.")
        (ENV_ARGS, ::boost::program_options::value < ::std::string > (), "alternative command line parameters.")
        ;
    hidden.add_options ()
#ifdef NO_BOOST_REGEX
        (GENERAL EXCLUDE, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore files that match this posix regular expression; may be repeated.")
#endif // NO_BOOST_REGEX
#ifdef NO_FRED
        (GENERAL THREAD ",n", ::boost::program_options::value < int > (), "Number of threads (default appropriate for the hardware).")
#endif // NO_FRED
        (GENERAL MACROSTART, ::boost::program_options::value < ::std::string > () -> default_value ("{{"), "Start of template macro (by default, the '{{' in '{{macro}}').")
        (GENERAL MACROEND, ::boost::program_options::value < ::std::string > () -> default_value ("}}"), "End of template macro (by default, the '}}' in '{{macro}}').")

        (JSONLD EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "Extension for JSON-LD files; may be repeated.")
        (JSONLD VERIFY, ::boost::program_options::bool_switch (), "Experimental: Verify JSON-LD.")
        (JSONLD DONT VERIFY, ::boost::program_options::bool_switch (), "Do not verify JSON-LD.")
        (JSONLD VERSION, ::boost::program_options::value < ::std::string > (), "Presume this version of JSON-LD (1.0 or 1.1, default 1.0).")

        (NITS SPEC, ::boost::program_options::bool_switch (), "Output nits in test spec format (requires -T).")
        (NITS DONT SPEC, ::boost::program_options::bool_switch (), "Do not output nits in test spec format.")

#ifdef NOSPELL
        (SPELL ACCEPT, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore this word in spell checks; may be repeated.")
        (SPELL CASED, ::boost::program_options::bool_switch (), "Nitpick wrongly cased but correctly spelt words.")
        (SPELL DONT CASED, ::boost::program_options::bool_switch (), "Ignore case when checking spelling.")
        (SPELL CHECK ",G", ::boost::program_options::bool_switch (), "Check spelling (see also --" GENERAL LANG ").")
        (SPELL DONT CHECK, ::boost::program_options::bool_switch (), "Do not check spelling.")
        (SPELL DICT, ::boost::program_options::value < vstr_t > () -> composing (), "LANG,DICT: associate (hunspell) dictionary with language, e.g. 'en-US,en_US-large'; may be repeated (ignored in Windows).")
        (SPELL ICU, ::boost::program_options::bool_switch (), "Use the International Components for Unicode (ICU) text libraries (high quality but slow).")
        (SPELL DONT ICU, ::boost::program_options::bool_switch (), "Use standard text libraries (fast but inaccurate).")
        (SPELL LIST, ::boost::program_options::value < vstr_t > () -> composing (), "FILE,LANG: FILE contains additional valid spellings in LANG; may be repeated.")
        (SPELL PATH, ::boost::program_options::value < ::std::string > (), "Path to (hunspell) dictionaries (ignored in Windows).")
#endif // NOSPELL
    ;

    primary.add_options ()
        (GENERAL CLASS, ::boost::program_options::bool_switch (), "Report unrecognised classes (consider --" GENERAL CSS ".")
        (GENERAL DONT CLASS, ::boost::program_options::bool_switch (), "Do not report unrecognised classes.")
        (GENERAL CLASSIC, ::boost::program_options::bool_switch (), "Report all classes used, not just those in .CSS files (requires --" GENERAL CLASS ".")
        (GENERAL DONT CLASSIC, ::boost::program_options::bool_switch (), "Do not report all classes used.")
        (GENERAL CGI ",W", ::boost::program_options::bool_switch (), "Process HTML snippets (for OpenBSD's httpd <FORM METHOD=GET ...>; disables most features).")
        (GENERAL DONT CGI, ::boost::program_options::bool_switch (), "Process a local static website.")
        (GENERAL CSS_OPTION, ::boost::program_options::bool_switch (), "Process .css files (for class names only).")
        (GENERAL DEFTHRD ",N", ::boost::program_options::value < int > (), "If no setting specifies the thread count, set it to this.")
        (GENERAL DONT CSS_OPTION, ::boost::program_options::bool_switch (), "Do not process .css files.")
        (GENERAL CUSTOM, ::boost::program_options::value < vstr_t > () -> composing (), "Define a custom element for checking the 'is' attribute; may be repeated.")
        (GENERAL DATAPATH ",p", ::boost::program_options::value < ::std::string > () -> default_value ("." PROG), "Root directory for most " PROG " files.")
        (GENERAL ERR ",E", ::boost::program_options::value < ::std::string > () -> composing (), "Exit with an error if nits of this severity or worse are generated. Values: '"
            CATASTROPHE "', '" ERR "' (default), '" WARNING "', '" INFO  "', or '" COMMENT  "'.")
#ifndef NO_BOOST_REGEX
        (GENERAL EXCLUDE, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore files that match this posix regular expression; may be repeated.")
#endif // NO_BOOST_REGEX
        (GENERAL FICHIER ",c", ::boost::program_options::value < ::std::string > () -> default_value (PROG EXT), "File for persistent data, requires -N (note --" GENERAL DATAPATH ").")
        (GENERAL GIT, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore git internal files.")
        (GENERAL IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore attributes and content of specified element; may be repeated.")
        (GENERAL INFO ",J", ::boost::program_options::bool_switch (), "Report " PROG " launch context at startup.")
        (GENERAL LANG, ::boost::program_options::value < ::std::string > () -> composing (), "Default language (such as 'en_GB', 'lb_LU', etc.).")
        (GENERAL MAXFILESIZE, ::boost::program_options::value < int > (), "Maximum file size to read, in megabytes (zero for no limit).")
        (GENERAL OUTPUT ",o", ::boost::program_options::value < ::std::string > (), "Output file (default to the console).")
        (GENERAL PROGRESS ",D", ::boost::program_options::bool_switch (), "Report progress")
        (GENERAL DONT PROGRESS, ::boost::program_options::bool_switch (), "Don't be quite so noisy.")
        (GENERAL RDFA_, ::boost::program_options::bool_switch (), "Check RDFa attributes.")
        (GENERAL DONT RDFA_, ::boost::program_options::bool_switch (), "Do not check RDFa attributes.")
        (GENERAL REL, ::boost::program_options::bool_switch (), "Ignore recognised but non-standard <LINK> REL values.")
        (GENERAL DONT REL, ::boost::program_options::bool_switch (), "Nitpick recognised but non-standard <LINK> REL values.")
        (GENERAL RPT, ::boost::program_options::bool_switch (), "Report when CSS files opened.")
        (GENERAL DONT RPT, ::boost::program_options::bool_switch (), "Say nowt when CSS files opened.")
        (GENERAL SPEC ",j", ::boost::program_options::bool_switch (), "Reset default values of most switches to false.")
        (GENERAL SLOB, ::boost::program_options::bool_switch (), "Do not nitpick untidy HTML such as missing closures.")
        (GENERAL DONT SLOB, ::boost::program_options::bool_switch (), "Point out slovenly HTML such as missing closures.")
        (GENERAL SSI ",I", ::boost::program_options::bool_switch (), "Process (simple) Server Side Includes.")
        (GENERAL DONT SSI, ::boost::program_options::bool_switch (), "Do not process Server Side Includes.")
        (GENERAL TEST ",T", ::boost::program_options::bool_switch (), "Output in format useful for automated tests.")
        (GENERAL DONT TEST, ::boost::program_options::bool_switch (), "Output in format specified by other switches.")
#ifndef NO_FRED
        (GENERAL THREAD ",n", ::boost::program_options::value < int > (), "Number of threads (default appropriate for the hardware).")
#endif // NO_FRED
        (GENERAL VERBOSE ",v", ::boost::program_options::value < ::std::string > (), "Output these nits and worse. Values: '"
            CATASTROPHE "', '" ERR "', '" WARNING "' (default), '" INFO  "', '" COMMENT  "', or 0 for silence.")

        (CORPUS ARTICLE, ::boost::program_options::bool_switch (), "Prefer the content of <ARTICLE> when gather page corpus.")
        (CORPUS DONT ARTICLE, ::boost::program_options::bool_switch (), "Avoid the content of <ARTICLE> when gather page corpus.")
        (CORPUS BODY, ::boost::program_options::bool_switch (), "Prefer the content of <BODY> when gather page corpus.")
        (CORPUS DONT BODY, ::boost::program_options::bool_switch (), "Avoid the content of <BODY> when gather page corpus.")
        (CORPUS MAIN, ::boost::program_options::bool_switch (), "Prefer the content of <MAIN> when gather page corpus.")
        (CORPUS DONT MAIN, ::boost::program_options::bool_switch (), "Avoid the content of <MAIN> when gather page corpus.")
        (CORPUS OUTPUT ",d", ::boost::program_options::value < ::std::string > (), "Dump corpus of site content to specified file.")

        (HTML RFC1867, ::boost::program_options::bool_switch (), "Consider RFC 1867 (INPUT=FILE) when processing HTML 2.0.")
        (HTML DONT RFC1867, ::boost::program_options::bool_switch (), "Ignore RFC 1867 (INPUT=FILE) when processing HTML 2.0.")
        (HTML RFC1942, ::boost::program_options::bool_switch (), "Consider RFC 1867 RFC 1942 (tables) when processing HTML 2.0.")
        (HTML DONT RFC1942, ::boost::program_options::bool_switch (), "Ignore RFC 1867 RFC 1942 (tables) when processing HTML 2.0.")
        (HTML RFC1980, ::boost::program_options::bool_switch (), "Consider RFC 1867 RFC 1980 (client side image maps) when processing HTML 2.0.")
        (HTML DONT RFC1980, ::boost::program_options::bool_switch (), "Ignore RFC 1867 RFC 1980 (client side image maps) when processing HTML 2.0.")
        (HTML RFC2070, ::boost::program_options::bool_switch (), "Consider RFC 1867 RFC 2070 (internationalisation) when processing HTML 2.0.")
        (HTML DONT RFC2070, ::boost::program_options::bool_switch (), "Ignore RFC 1867 RFC 2070 (internationalisation) when processing HTML 2.0.")
        (HTML TAGS, ::boost::program_options::bool_switch (), "Presume HTML with no DOCTYPE is HTML Tags (CERN version).")
        (HTML DONT TAGS, ::boost::program_options::bool_switch (), "Presume HTML with no DOCTYPE is HTML 1.0.")
        (HTML TITLE ",z", ::boost::program_options::value < int > () -> default_value (MAX_IDEAL_TITLE_LENGTH), "Maximum advisable length of <TITLE> text.")
        (HTML VERSION, ::boost::program_options::value < ::std::string > (),
            "Set the specific version of HTML with DOCTYPE (default '2022/7/1'), or if no DOCTYPE found (default '1.0'). "
            "For a W3 standard, give its version (e.g. '5.2'). "
            "For a WhatWG living standard, give its date (e.g. '2015/7/1'). "
            "For XHTML, use XHTML plus version, e.g. 'XHTML 1.0'. "
            "For HTML+, use '+'. For HTML tags, use 'tags'.")

        (LINKS CHECK ",l", ::boost::program_options::bool_switch (), "Check internal links.")
        (LINKS DONT CHECK, ::boost::program_options::bool_switch (), "Ignore internal links.")
        (LINKS EXAMPLE, ::boost::program_options::bool_switch (), "Issue warning if link to faux domain, such as example.com, found.")
        (LINKS DONT EXAMPLE, ::boost::program_options::bool_switch (), "Say nothing if link to faux domain, such as example.com, found.")
        (LINKS EXTERNAL ",e", ::boost::program_options::bool_switch (), "Check external links (sets --" LINKS CHECK ").")
        (LINKS DONT EXTERNAL, ::boost::program_options::bool_switch (), "Ignore external links.")
        (LINKS FORWARD ",3", ::boost::program_options::bool_switch (), "Report http forwarding errors, e.g. 301 and 308 (sets --" LINKS EXTERNAL ").")
        (LINKS DONT FORWARD, ::boost::program_options::bool_switch (), "Ignore http forwarding errors, e.g. 301 and 308.")
        (LINKS IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "When checking external links, ignore this domain; may be repeated.")
        (LINKS LOCAL, ::boost::program_options::bool_switch (), "Issue warning if link to local domain, such as ???.lan or ???.corp, found.")
        (LINKS DONT LOCAL, ::boost::program_options::bool_switch (), "Don't mention links to local domains.")
        (LINKS ONCE ",O", ::boost::program_options::bool_switch (), "Report each broken external link once (sets --" LINKS EXTERNAL ").")
        (LINKS DONT ONCE, ::boost::program_options::bool_switch (), "Report broken links whenever they are found.")
        (LINKS REPORT, ::boost::program_options::value < vstr_t > () -> composing (), "Report links to this domain and its descendants; may be repeated.")
        (LINKS REVOKE ",r", ::boost::program_options::bool_switch (), "Do not check whether https certificates have been revoked (sets --" LINKS EXTERNAL ").")
        (LINKS DONT REVOKE, ::boost::program_options::bool_switch (), "Check whether https certificates have been revoked (sets --" LINKS EXTERNAL ").")
        (LINKS XLINK ",X", ::boost::program_options::bool_switch (), "Check crosslink IDs.")
        (LINKS DONT XLINK, ::boost::program_options::bool_switch (), "Do not check crosslink IDs.")

        (MATH CORE, ::boost::program_options::bool_switch (), "MathML Core (May 2022 draft).")
        (MATH DRAFT, ::boost::program_options::value < int > () -> default_value (0), "For MathML 4 only, which draft (2020 or 2022).")
        (MATH VERSION, ::boost::program_options::value < int > () -> default_value (0), "preferred version of MathML (default (0): determine by HTML version).")

        (MICRODATA EXPORT, ::boost::program_options::bool_switch (), "Export microformat data (only verified data if --" MICRODATA VERIFY " is set).")
        (MICRODATA DONT EXPORT, ::boost::program_options::bool_switch (), "Do not export microformat data.")
        (MICRODATA VERIFY ",m", ::boost::program_options::bool_switch (), "Check microdata (" PROG " only understands certain microdata schemas).")
        (MICRODATA DONT VERIFY, ::boost::program_options::bool_switch (), "Do not check microdata.")
        (MICRODATA ROOT, ::boost::program_options::value < ::std::string > (), "Microdata export root directory (requires --" MICRODATA EXPORT ").")
        (MICRODATA VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "Export virtual directory, syntax virtual=directory. Must correspond to --" WEBSITE VIRTUAL ".")

        (MF VERIFY ",M", ::boost::program_options::bool_switch (), "Check microformats in class and rel attributes (see https://" MICROFORMATS_ORG "/).")
        (MF DONT VERIFY, ::boost::program_options::bool_switch (), "Do not check microformats in class and rel attributes.")
        (MF VERSION, ::boost::program_options::value < int > (), "Check this version of microformats (1, 2, or 3 for both).")
        (MF EXPORT, ::boost::program_options::bool_switch (), "Export microformat data (requires --" MF VERIFY ").")
        (MF DONT EXPORT, ::boost::program_options::bool_switch (), "Do not export microformat data.")

        (NITS CATASTROPHE, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a catastrophe; may be repeated.")
        (NITS COMMENT, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a comment; may be repeated.")
        (NITS DBG, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a debug message; may be repeated.")
        (NITS ERR, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as an error; may be repeated.")
        (NITS FORMAT, ::boost::program_options::value < ::std::string > (), "Output nits in this format (\"html\" or \"text\", default text).")
        (NITS INFO, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as info; may be repeated.")
        (NITS NIDS, ::boost::program_options::bool_switch (), "Output nit identifiers (used to recategorise nits).")
        (NITS DONT NIDS, ::boost::program_options::bool_switch (), "Do not output nit identifiers.")
        (NITS OVERRIDE ",P", ::boost::program_options::value < ::std::string > (), "Output nits in this format (overrides " NITS FORMAT "; for automation).")
        (NITS QUOTE, ::boost::program_options::value < ::std::string > (), "Quote nits in this format (\"html\" or \"text\", default text).")
        (NITS ROOT, ::boost::program_options::bool_switch (), "By default, seek nit output template files in --" WEBSITE ROOT ".")
        (NITS DONT ROOT, ::boost::program_options::bool_switch (), "Do not seek nit output template files in --" WEBSITE ROOT ", unless explicitly specified.")
        (NITS SILENCE, ::boost::program_options::value < vstr_t > () -> composing (), "Silence nit; may be repeated.")
        (NITS UNIQUE ",U", ::boost::program_options::bool_switch (), "Do not report repeated nits, even if they give more information.")
        (NITS DONT UNIQUE, ::boost::program_options::bool_switch (), "Report repeated nits.")
        (NITS WARNING, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine specified nit as a warning; may be repeated.")
        (NITS WATCH, ::boost::program_options::bool_switch (), "Output debug nits (for automation).")
        (NITS DONT WATCH, ::boost::program_options::bool_switch (), "Do not output debug nits.")

        (RDFA VERSION, ::boost::program_options::value < ::std::string > () -> default_value ("1.1.3"), "Version of RDFa (default 1.1.3) (experimental).")

        (SHADOW CHANGED, ::boost::program_options::bool_switch (),
#ifndef NOLYNX
                            "link/"
#endif // NOLYNX
                            "Only copy shadow files when the target doesn't exist, or is older than the original.")
        (SHADOW DONT CHANGED, ::boost::program_options::bool_switch (), "Overwrite "
#ifndef NOLYNX
                            "link/"
#endif // NOLYNX
                            "Copy shadow files whether or not the target is younger than the original.")
        (SHADOW COMMENT, ::boost::program_options::bool_switch (), "Do NOT remove comments from shadow pages.")
        (SHADOW DONT COMMENT, ::boost::program_options::bool_switch (), "Remove comments from shadow pages.")
        (SHADOW COPY, ::boost::program_options::value < ::std::string > (),  "Copy site: 'no' (default), "
#ifndef NOLYNX
                                                                    "'hard' (links), 'soft' (links), "
#endif // NOLYNX
                                                                    "'pages', 'all', 'dedu' (deduplicate), 'report'.")
        (SHADOW FICHIER, ::boost::program_options::value < ::std::string > (), "File for persisting deduplication and update data.")
        (SHADOW ENABLE, ::boost::program_options::bool_switch (), "Enable shadowing (set by all other SHADOW options).")
        (SHADOW DONT ENABLE, ::boost::program_options::bool_switch (), "Disable shadowing.")
        (SHADOW IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore files with this extension; may be repeated.")
        (SHADOW INFO, ::boost::program_options::bool_switch (), "Insert the generation time in a comment at the top of shadowed pages (after --" SHADOW MSG ").")
        (SHADOW DONT INFO, ::boost::program_options::bool_switch (), "Do not insert the generation time in a comment at the top of shadowed pages.")
        (SHADOW MSG, ::boost::program_options::value < ::std::string > (), "Insert this text in a comment at the top of shadowed pages.")
        (SHADOW ROOT, ::boost::program_options::value < ::std::string > (), "Shadow output root directory.")
        (SHADOW SPACING, ::boost::program_options::bool_switch (), "Merge whitespace on shadow pages. Without this option, nit line-numbers may not match shadow pages.")
        (SHADOW DONT SPACING, ::boost::program_options::bool_switch (), "Do not merge whitespace on shadow pages.")
        (SHADOW SSI, ::boost::program_options::bool_switch (), "Resolve SSIs on shadow pages when --" GENERAL SSI " is set.")
        (SHADOW DONT SSI, ::boost::program_options::bool_switch (), "Do not resolve SSIs on shadow pages.")
        (SHADOW UPDATE, ::boost::program_options::bool_switch (), "Only examine changed pages, or pages with changed dependencies (requires --" SHADOW FICHIER ")")
        (SHADOW DONT UPDATE, ::boost::program_options::bool_switch (), "Examine all pages.")
        (SHADOW VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "Shadow virtual directory, syntax virtual=shadow; must correspond to --" WEBSITE VIRTUAL "; may be repeated.")

        (WEBSITE EXTENSION ",x", ::boost::program_options::value < vstr_t > () -> composing (), "Check files with this extension (default html); may be repeated.")
        (WEBSITE INDEX ",i", ::boost::program_options::value < ::std::string > (), "Index file in directories (default: none).")
        (WEBSITE ROOT ",g", ::boost::program_options::value < ::std::string > (), "Website root directory (default: current directory).")
        (WEBSITE SITE ",s", ::boost::program_options::value < vstr_t > () -> composing (), "Domain name(s) for local site (default none); may be repeated.")
        (WEBSITE VIRTUAL ",L", ::boost::program_options::value < vstr_t > () -> composing (), "Define virtual directory, arg syntax virtual=physical; may be repeated.")

#ifndef NOSPELL
        (SPELL ACCEPT, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore this word in spell checks; may be repeated.")
        (SPELL CASED, ::boost::program_options::bool_switch (), "Nitpick wrongly cased but correctly spelt words.")
        (SPELL DONT CASED, ::boost::program_options::bool_switch (), "Ignore case when checking spelling.")
        (SPELL CHECK ",G", ::boost::program_options::bool_switch (), "Check spelling (see also --" GENERAL LANG ").")
        (SPELL DONT CHECK, ::boost::program_options::bool_switch (), "Do not check spelling.")
        (SPELL DICT, ::boost::program_options::value < vstr_t > () -> composing (), "LANG,DICT: associate (hunspell) dictionary with language, e.g. 'en-US,en_US-large'; may be repeated (ignored in Windows).")
        (SPELL ICU, ::boost::program_options::bool_switch (), "Use the International Components for Unicode (ICU) text libraries (high quality but slow).")
        (SPELL DONT ICU, ::boost::program_options::bool_switch (), "Use standard text libraries (fast but inaccurate).")
        (SPELL LIST, ::boost::program_options::value < vstr_t > () -> composing (), "FILE,LANG: FILE contains additional valid spellings in LANG; may be repeated.")
        (SPELL PATH, ::boost::program_options::value < ::std::string > (), "Path to (hunspell) dictionaries (ignored in Windows).")
#endif // NOSPELL

        (STATS EXPORT, ::boost::program_options::value < ::std::string > (), "Export collected statistical data here.")
        (STATS META, ::boost::program_options::bool_switch (), "Report on <META> data.")
        (STATS DONT META, ::boost::program_options::bool_switch (), "Do not report <META> data.")
        (STATS PAGE, ::boost::program_options::bool_switch (), "Report individual page statistics.")
        (STATS DONT PAGE, ::boost::program_options::bool_switch (), "Do not report individual page statistics.")
        (STATS SUMMARY ",S", ::boost::program_options::bool_switch (), "Report overall statistics.")
        (STATS DONT SUMMARY, ::boost::program_options::bool_switch (), "Do not report overall statistics.")

        (SVG VERSION, ::boost::program_options::value < ::std::string > (), "Presumed this version of SVG if version attribute missing (requires HTML 4 or greater).")

        (VALIDATION MINOR ",m", ::boost::program_options::value < int > (), "Validate HTML 5 with this w3 minor version (e.g. 2 for HTML 5.2).")
        (VALIDATION MICRODATAARG, ::boost::program_options::bool_switch (), "Validate HTML5 microdata.")
        (VALIDATION DONT MICRODATAARG, ::boost::program_options::bool_switch (), "Do not validate HTML5 microdata.")
        	;

    for (int i = s_none + 1; i < s_error; ++i)
    {   const e_schema es = static_cast < e_schema > (i);
        if (is_faux_schema (es)) continue;
        if (get_schema_version_count (es) < 2) continue;
        ::std::string naam (schema_names.get (es, SCHEMA_NAME));
        ::std::string arg = ONTOLOGY;
        arg += naam;
        ::std::string desc (schema_names.get (es, SCHEMA_DESCRIPTION));
        desc += ", ";
        if (get_schema_version_count (es) == 2)
        {   desc += "either ";
            desc += get_first_schema_version (es).ver ();
            desc += " or "; }
        else
        {   desc += "between ";
            desc += get_first_schema_version (es).ver ();
            desc += " and "; }
        desc += get_last_schema_version (es).ver ();
        desc += " (experimental)";
        ontology.add_options ()
            (arg.c_str (), ::boost::program_options::value < ::std::string > (), desc.c_str ()); }

    valid.add_options ()
        (VALIDATION ATTRIB, ::boost::program_options::value < vstr_t > () -> composing (), "Add a custom attribute (name namespace flags ext).")
        (VALIDATION CHARSET, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid charset.")
        (VALIDATION CLASS, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid class.")
        (VALIDATION COLOR, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid colour.")
        (VALIDATION COLOUR, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid colour.")
        (VALIDATION COUNTRY, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid two-letter country code.")
        (VALIDATION CURRENCY, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid currency.")
        (VALIDATION ELEMENT, ::boost::program_options::value < vstr_t > () -> composing (), "Add a custom element (name namespace flags ext).")
        (VALIDATION ELEMATTR, ::boost::program_options::value < vstr_t > () -> composing (), "Add an attribute to an element (element attribute).")
        (VALIDATION EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "Add a mimetype file extension.")
        (VALIDATION HTTPEQUIV, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid meta httpequiv.")
        (VALIDATION LANG, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid language code (such as 'ma' for Marain).")
        (VALIDATION METANAME, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid meta name.")
        (VALIDATION MIMETYPE, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid mimetype.")
        (VALIDATION REL, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid rel.")
        (VALIDATION SGML, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid SGML schema identification.")
        ;
    valid.add (context.validation ());

    cmd.add (basic).add (primary).add (ontology).add (valid).add (hidden);
    config.add (primary).add (ontology).add (valid).add (hidden).add (cgi);
    aid.add (basic).add (primary).add (ontology);
    ::std::string loaded;

    nits.set_context (0, "Environment");
    try
    {   ::boost::program_options::store (::boost::program_options::parse_environment (env, ::boost::function1 < ::std::string, ::std::string> (env_mapper)), env_);
        if (env_.count (ENV_ARGS))
        {   ::std::string e (env_ [ENV_ARGS].as < ::std::string > ());
            vstr_t env_args (split_by_space (e));
            if (! env_args.empty ())
            {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
                macro -> set (nm_run_environment, e);
                ::boost::program_options::store (::boost::program_options::command_line_parser (env_args).options (cmd).positional (pos).run (), var_); } } }
    catch (const ::boost::program_options::error& err)
    {   nits.pick (nit_configuration, es_error, ec_init, "Environment error: ", err.what ());
        nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
        return; }
    catch (...)
    {   nits.pick (nit_configuration, es_error, ec_init, "Environment error");
        nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
        return; }

    ::boost::program_options::notify (env_);

    if (env_.count (ENV_CONFIG)) context.environment (env_config, env_ [ENV_CONFIG].as < ::std::string > ());
    if (env_.count (ENV_ARGS)) context.environment (env_args, env_ [ENV_ARGS].as < ::std::string > ());

    if (env_.count (QUERY_STRING))
    {   ::std::string qu (env_ [QUERY_STRING].as < ::std::string > ());
        context.environment (env_query_string, qu);
        if (! context.environment (env_query_string).empty ()) try
        {   context.cgi (true).article (false).body (false).cased (false).classic (false).crosslinks (false).example (false)
                .external (false).forwarded (false).icu (true).info (true).jsonld (false).links (false).load_css (false).main (false)
                .md_export (false).meta (true).mf_verify (true).microdata (true).not_root (false).once (true).presume_tags (false).progress (false)
                .rdfa (false).rel (true).revoke (false).rfc_1867 (true).rfc_1942 (true).rfc_1980 (true).rfc_2070 (true).rpt_opens (false).schema (true)
                .shadow_changed (false).shadow_comment (false).shadow_enable (false).shadow_space (false).shadow_ssi (false).spell (false).ssi (false)
                .stats_page (false).stats_summary (false).unknown_class (false).update (false);
            VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
            macro -> set (nm_query, qu);
            if (env_.count (SERVER_SOFTWARE)) context.environment (env_server_software, env_ [SERVER_SOFTWARE].as < ::std::string > ());
            if (env_.count (SERVER_NAME)) context.environment (env_server_name, env_ [SERVER_NAME].as < ::std::string > ());
            if (env_.count (GATEWAY_INTERFACE)) context.environment (env_gateway_interface, env_ [GATEWAY_INTERFACE].as < ::std::string > ());
            if (env_.count (SERVER_PROTOCOL)) context.environment (env_server_protocol, env_ [SERVER_PROTOCOL].as < ::std::string > ());
            if (env_.count (SERVER_PORT)) context.environment (env_server_port, env_ [SERVER_PORT].as < ::std::string > ());
            if (env_.count (REQUEST_METHOD)) context.environment (env_request_method, env_ [REQUEST_METHOD].as < ::std::string > ());
            if (env_.count (HTTP_ACCEPT)) context.environment (env_http_accept, env_ [HTTP_ACCEPT].as < ::std::string > ());
            if (env_.count (PATH_INFO)) context.environment (env_path_info, env_ [PATH_INFO].as < ::std::string > ());
            if (env_.count (PATH_TRANSLATED)) context.environment (env_path_translated, env_ [PATH_TRANSLATED].as < ::std::string > ());
            if (env_.count (SCRIPT_NAME)) context.environment (env_script_name, env_ [SCRIPT_NAME].as < ::std::string > ());
            if (env_.count (REMOTE_HOST)) context.environment (env_remote_host, env_ [REMOTE_HOST].as < ::std::string > ());
            if (env_.count (REMOTE_ADDR)) context.environment (env_remote_addr, env_ [REMOTE_ADDR].as < ::std::string > ());
            if (env_.count (REMOTE_USER)) context.environment (env_remote_user, env_ [REMOTE_USER].as < ::std::string > ());
            if (env_.count (AUTH_TYPE)) context.environment (env_auth_type, env_ [AUTH_TYPE].as < ::std::string > ());
            if (env_.count (CONTENT_TYPE)) context.environment (env_content_type, env_ [CONTENT_TYPE].as < ::std::string > ());
            if (env_.count (CONTENT_LENGTH)) context.environment (env_content_length, env_ [CONTENT_LENGTH].as < ::std::string > ());
            ::std::string q (query_to_switches (context.environment (env_query_string)));
#ifdef XTRA_DEBUG
            ::std::cout << "Environment: " << q << "\n";
#endif // XTRA_DEBUG
            vstr_t query (split_quoted_by_space (q));
            ::boost::program_options::store (::boost::program_options::command_line_parser (query).options (cmd).positional (pos).run (), var_);
            if (! var_.count (HTML SNIPPET))
            {   nits.pick (nit_configuration, es_error, ec_init, "An environment " QUERY_STRING " must include html.snippet.");
                nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
                return; } }
#ifdef DEBUG
        catch (const ::boost::program_options::error& err)
        {   nits.pick (nit_configuration, es_error, ec_init, "Query error: ", err.what ());
            nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
            return; }
#endif // DEBUG
        catch (...)
        {   nits.pick (nit_configuration, es_error, ec_init, "Environment query exception.");
            nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
            return; } }

    nits.set_context (0, "Command Line");

    try
    {   ::boost::program_options::store (::boost::program_options::command_line_parser (argc, argv).options (cmd).positional (pos).run (), var_); }
    catch (const ::boost::program_options::error& err)
    {   nits.pick (nit_configuration, es_error, ec_init, "Command line parameter exception: ", err.what ());
        nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
        return; }
    catch (...)
    {   nits.pick (nit_configuration, es_error, ec_init, "Command line parameter error.");
        nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
        return; }

    if (var_.count (CONFIG) || var_ [DEFCONF].as <bool > () || env_.count (ENV_CONFIG))
    {   ::boost::filesystem::path file (CONFIGURATION);
        if (var_.count (CONFIG)) file = var_ [CONFIG].as < ::std::string > ();
        else if ((! var_ [DEFCONF].as <bool > ()) && env_.count (ENV_CONFIG)) file = env_ [ENV_CONFIG].as < ::std::string > ();
        nits.set_context (0, file.string ());
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (nm_config, file.string ());
        if (file_exists (file))
        {   nits.pick (nit_configuration, es_debug, ec_init, ::std::string ("Loading configuration ") + file.string () + "...");
            try
            {   context.config (canonical_name (absolute_name (file))); }
            catch (...)
            {   nits.pick (nit_configuration, es_error, ec_init, ::std::string ("Cannot canonise ") + file.string ());
                return; } }
        else
        {   nits.pick (nit_configuration, es_error, ec_init, ::std::string ("Cannot find ") + file.string ());
            return; }
        vstr_t unrecognised;
        try
#ifdef  NO_PCF_STR
        {   ::std::ifstream fis (file.string ().c_str ());
            auto opt = ::boost::program_options::parse_config_file (fis, config, true);
#else
        {   auto opt = ::boost::program_options::parse_config_file (file.string ().c_str (), config, true);
#endif
            ::boost::program_options::store (opt, var_);
            unrecognised = ::boost::program_options::collect_unrecognized (opt.options, ::boost::program_options::include_positional); }
        catch (const ::boost::program_options::error& err)
        {   nits.pick (nit_configuration, es_error, ec_init, "Exception ", quote (err.what ()), " when processing ", file.string ());
            return; }
        catch (...)
        {   nits.pick (nit_configuration, es_error, ec_init, "Unknown exception when processing ", file.string ());
            return; }
        for (auto u : unrecognised)
            nits.pick (nit_unknown_option, es_warning, ec_init, "Unknown configuration option ", quote (u), " ignored"); }
    ::boost::program_options::notify (var_);
    if (var_ [GENERAL INFO].as <bool > ())
        ::std::cout << context.general_info () << "\n";
    if (var_ [VERSION].as < bool > ())
    {   context.todo (do_simple);
        return; }
    if (var_ [HELP].as < bool > ())
    {   help (aid);
        return; }
    if (var_ [VALIDATION_].as < bool > ())
    {   ::std::ostringstream waste_of_space;
        waste_of_space << valid;
        context.domsg (waste_of_space.str ());
        context.todo (do_simple);
        return; }
    if (var_ [ONTOLOGY LIST].as < bool > ())
    {   ::std::string res;
        for (int i = s_none + 1; i < s_error; ++i)
        {   const e_schema es = static_cast < e_schema > (i);
            if (is_faux_schema (es)) continue;
            res += schema_names.get (es, SCHEMA_NAME);
            const schema_version x (get_first_schema_version (es));
            const schema_version y (get_last_schema_version (es));
            const int count = get_schema_version_count (es);
            PRESUME (count >= 1, __FILE__, __LINE__);
            if (count == 1)
            {   PRESUME (x == y, __FILE__, __LINE__);
                res += " ";
                res += x_dot_y (x.mjr (), x.mnr ()); }
            if (count > 1)
            {   PRESUME (x != y, __FILE__, __LINE__);
                res += " ";
                res += x_dot_y (x.mjr (), x.mnr ());
                if (count == 2) res += ","; else res += "-";
                res += x_dot_y (y.mjr (), y.mnr ()); }
            res += "\n"; }
        context.domsg (res);
        context.todo (do_simple);
        return; }

    if (! context.cgi () && var_.count (ENVIRONMENT QUERY_STRING))
    {   nits.set_context (0, "Environment");
        context.environment (env_query_string, var_ [ENVIRONMENT QUERY_STRING].as < ::std::string > ());
        if (! context.environment (env_query_string).empty ()) try
        {   context.cgi (true);
            if (var_.count (ENVIRONMENT SERVER_SOFTWARE)) context.environment (env_server_software, var_ [ENVIRONMENT SERVER_SOFTWARE].as < ::std::string > ());
            if (var_.count (ENVIRONMENT SERVER_NAME)) context.environment (env_server_name, var_ [ENVIRONMENT SERVER_NAME].as < ::std::string > ());
            if (var_.count (ENVIRONMENT GATEWAY_INTERFACE)) context.environment (env_gateway_interface, var_ [ENVIRONMENT GATEWAY_INTERFACE].as < ::std::string > ());
            if (var_.count (ENVIRONMENT SERVER_PROTOCOL)) context.environment (env_server_protocol, var_ [ENVIRONMENT SERVER_PROTOCOL].as < ::std::string > ());
            if (var_.count (ENVIRONMENT SERVER_PORT)) context.environment (env_server_port, var_ [ENVIRONMENT SERVER_PORT].as < ::std::string > ());
            if (var_.count (ENVIRONMENT REQUEST_METHOD)) context.environment (env_request_method, var_ [ENVIRONMENT REQUEST_METHOD].as < ::std::string > ());
            if (var_.count (ENVIRONMENT HTTP_ACCEPT)) context.environment (env_http_accept, var_ [ENVIRONMENT HTTP_ACCEPT].as < ::std::string > ());
            if (var_.count (ENVIRONMENT PATH_INFO)) context.environment (env_path_info, var_ [ENVIRONMENT PATH_INFO].as < ::std::string > ());
            if (var_.count (ENVIRONMENT PATH_TRANSLATED)) context.environment (env_path_translated, var_ [ENVIRONMENT PATH_TRANSLATED].as < ::std::string > ());
            if (var_.count (ENVIRONMENT SCRIPT_NAME)) context.environment (env_script_name, var_ [ENVIRONMENT SCRIPT_NAME].as < ::std::string > ());
            if (var_.count (ENVIRONMENT REMOTE_HOST)) context.environment (env_remote_host, var_ [ENVIRONMENT REMOTE_HOST].as < ::std::string > ());
            if (var_.count (ENVIRONMENT REMOTE_ADDR)) context.environment (env_remote_addr, var_ [ENVIRONMENT REMOTE_ADDR].as < ::std::string > ());
            if (var_.count (ENVIRONMENT REMOTE_USER)) context.environment (env_remote_user, var_ [ENVIRONMENT REMOTE_USER].as < ::std::string > ());
            if (var_.count (ENVIRONMENT AUTH_TYPE)) context.environment (env_auth_type, var_ [ENVIRONMENT AUTH_TYPE].as < ::std::string > ());
            if (var_.count (ENVIRONMENT CONTENT_TYPE)) context.environment (env_content_type, var_ [ENVIRONMENT CONTENT_TYPE].as < ::std::string > ());
            if (var_.count (ENVIRONMENT CONTENT_LENGTH)) context.environment (env_content_length, var_ [ENVIRONMENT CONTENT_LENGTH].as < ::std::string > ());
            ::std::string q (query_to_switches (context.environment (env_query_string)));
#ifdef XTRA_DEBUG
            ::std::cout << "Config: " << q << "\n";
#endif // XTRA_DEBUG
            vstr_t query (split_quoted_by_space (q));
            ::boost::program_options::store (::boost::program_options::command_line_parser (query).options (cmd).positional (pos).run (), var_);
            if (! var_.count (HTML SNIPPET))
            {   nits.pick (nit_configuration, es_error, ec_init, ENVIRONMENT QUERY_STRING " must include html.snippet.");
                nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
                return; }
            ::boost::program_options::notify (var_); }
        catch (const ::boost::program_options::error& err)
        {   nits.pick (nit_configuration, es_error, ec_init, "Configuration " ENVIRONMENT_ " error: ", err.what ());
            nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
            return; }
        catch (...)
        {   nits.pick (nit_configuration, es_error, ec_init, "Configuration " ENVIRONMENT_ " query exception.");
            nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
            return; } }

    if (! context.cgi ()) yea_nay (&context_t::cgi, nits, GENERAL CGI, GENERAL DONT CGI);
    nits.set_context (0, "Configuration");

    if (context.cgi ()) context.todo (do_cgi);
    else if (! var_.count (WEBSITE ROOT))
    {   context.domsg ("\n" TYPE_HELP "\n");
        context.todo (do_simple);
        return; }
    else context.todo (do_examine); }

void options::contextualise (nitpick& nits)
{   yea_nay (&context_t::test, nits, GENERAL TEST, GENERAL DONT TEST);
    yea_nay (&context_t::spec, nits, NITS SPEC, NITS DONT SPEC);

    if (context.test () || var_ [GENERAL SPEC].as <bool> ())
        context.article (false).body (false).cased (false).classic (false).crosslinks (false).example (false).external (false).forwarded (false)
            .icu (true).info (false).jsonld (false).links (false).load_css (true).main (false).md_export (false).meta (false).mf_verify (false)
            .microdata (false).nids (true).nits (false) .nits_nits_nits (true).not_root (false).once (false).presume_tags (false).progress (false)
            .rdfa (false) .rel (false).revoke (false).rfc_1867 (true).rfc_1942 (true).rfc_1980 (true).rfc_2070 (true).rpt_opens (false).schema (true)
            .shadow_changed (false).shadow_comment (false).shadow_enable (false).shadow_space (false).shadow_ssi (false).spell (false).ssi (false)
            .stats_page (false).stats_summary (false).unknown_class (false).update (false);

#ifndef NO_FRED
    if (var_.count (GENERAL THREAD)) context.fred (var_ [GENERAL THREAD].as < int > ());
    else if (var_.count (GENERAL DEFTHRD)) context.fred (var_ [GENERAL DEFTHRD].as < int > ());
    else context.fred (0);
#endif // NO_FRED

    if (! context.cgi ())
    {   if (var_.count (NITS FORMAT)) context.nit_format (var_ [NITS FORMAT].as < ::std::string > ());
        if (var_.count (NITS OVERRIDE)) context.nit_override (var_ [NITS OVERRIDE].as < ::std::string > ()); }

    if (var_.count (GENERAL VERBOSE)) context.verbose (decode_severity (nits, var_ [GENERAL VERBOSE].as < ::std::string > ()));
    if (var_.count (HTML SNIPPET)) context.snippet (var_ [HTML SNIPPET].as < ::std::string > ());
    yea_nay (&context_t::mf_verify, nits, MF VERIFY, MF DONT VERIFY);

    if (context.test () || ! context.cgi ())
    {   if (var_.count (GENERAL OUTPUT))
        {   outstr.init (nits, nix_path_to_local (var_ [GENERAL OUTPUT].as < ::std::string > ()));
#ifndef EXPAND_TEST
            if (! context.test ())
                nits.pick (nit_configuration, es_debug, ec_init, ::std::string ("Writing to ") + var_ [GENERAL OUTPUT].as < ::std::string > ());
#endif // EXPAND_TEST
        }
        if ((! var_ [GENERAL DONT PROGRESS].as <bool > ()) && var_ [GENERAL PROGRESS].as <bool > ())
            if (context.test ()) ::std::cout << test_title;
            else if (context.tell (es_info)) ::std::cout << full_title;
            else ::std::cout << simple_title;
        if (! context.cgi ())
        {   context.path (nix_path_to_local (var_ [GENERAL DATAPATH].as < ::std::string > ()));
            if (! file_exists (context.path ()))
            {   nits.pick (nit_create_folder, es_comment, ec_init, "creating ", context.path ());
                if (! make_directories (context.path ()))
                    nits.pick (nit_cannot_create_file, es_catastrophic, ec_init, "cannot create ", context.path ()); } } }

    if (var_.count (MF VERSION))
    {   int n = ::boost::lexical_cast < int > (var_ [MF VERSION].as < int > ());
        if ((n < 1) || (n > 3))
        {   nits.pick (nit_mf_version, es_warning, ec_init, "invalid microformats version ", quote (n), "; presuming version 2");
            n = 2; }
        context.mf_version (GSL_NARROW_CAST < unsigned char > (n)); }

    if (var_.count (HTML VERSION) > 0)
    {   ::std::string ver (var_ [HTML VERSION].as < ::std::string > ());
        if (! ver.empty ())
        {   bool xhtml = false;
            if (ver.length () >= 4)
                if (compare_no_case (ver.substr (0, 4), "html")) ver = trim_the_lot_off (ver.substr (4));
                else if (compare_no_case (ver.substr (0, 5), "xhtml")) { ver = trim_the_lot_off (ver.substr (5)); xhtml = true; }
            const ::std::string::size_type pos = ver.find ('.');
            if (pos != ::std::string::npos)
            {   int mjr = 1, mnr = USHRT_MAX;
                if (pos == ver.length () - 1) mjr = lexical < int > :: cast (ver.substr (0, pos));
                else if (pos == 0) { mjr = 0; mnr = 1; }
                else
                {   mjr = lexical < int > :: cast (ver.substr (0, pos));
                    mnr = lexical < int > :: cast (ver.substr (pos+1)); }
                if (xhtml)
                    switch (mjr)
                    {   case 1 :
                            if (mnr == 0) { mjr = 4; mnr = 2; }
                            else if (mnr == 1) { mjr = 4; mnr = 3; }
                            else
                            {   mjr = 4; mnr = 3;
                                nits.pick ( nit_config_version, es_warning, ec_init,
                                            "unknown version of XHTML; presuming XHTML 1.1"); }
                            break;
                        case 2 :
                            if (mnr > 0)
                                nits.pick ( nit_config_version, es_warning, ec_init,
                                            "unknown version of XHTML; presuming XHTML 2.0");
                            mjr = 4; mnr = 4;
                            break;
                        case 5 :
                            if (mnr > 3)
                            {   mnr = 2;
                                nits.pick ( nit_config_version, es_warning, ec_init,
                                            "unknown version of XHTML, presuming XHTML 5.2"); }
                            break;
                        default :
                            mjr = 5; mnr = 2;
                                nits.pick ( nit_config_version, es_warning, ec_init,
                                            "unknown version of XHTML; presuming XHTML 5.2");
                            break;  }
                context.html_ver (mjr, mnr);
                if (xhtml) context.html_ver ().set_flags (HV_XHTML); }
            else if (ver.find ('/') != ::std::string::npos)
                if ((ver.length () != 10) || (ver.at (4) != '/') || (ver.at (7) != '/') || (ver.find_first_not_of (DENARY "/") != ::std::string::npos))
                    nits.pick (nit_config_date, es_warning, ec_init, "bad date ", quote (ver), " ignored ('YYYY/MM/DD' expected)");
                else
                {   const ::boost::gregorian::date d (::boost::gregorian::from_string (ver));
                    if (d.is_not_a_date ())
                        nits.pick (nit_config_date, es_warning, ec_init, "invalid date ", quote (ver), " ignored");
                    else
                    {   int y = d.year ();
                        const int m = d.month ();
                        if (y > 2000) y -= 2000;
                        else if (y > 99) y = 99;
                        if ((y < HTML_5_EARLIEST_YEAR) || ((y == HTML_5_EARLIEST_YEAR) && (m < HTML_5_EARLIEST_MONTH)))
                        {   nits.pick (nit_config_date, es_warning, ec_init, quote (ver) + " is too early, presuming ", HTML_5_EARLIEST_YEAR, "/", HTML_5_EARLIEST_MONTH, "/1");
                            context.html_ver (html_jan05); }
                        else if ((y > HTML_LATEST_YEAR) || ((y == HTML_LATEST_YEAR) && (m > HTML_LATEST_MONTH)))
                        {   nits.pick (nit_config_date, es_warning, ec_init, quote (ver), " is too recent, presuming ", HTML_LATEST_YEAR, "/", HTML_LATEST_MONTH, "/1");
                            context.html_ver (html_current); }
                        else context.html_ver (d);
                        if (xhtml)
                            context.html_ver ().set_flags (HV_XHTML); } }
            else if (ver == "+") context.html_ver (html_plus);
            else if (compare_no_case (ver, "plus")) context.html_ver (html_plus);
            else if (compare_no_case (ver, "tags")) context.html_ver (html_tags);
            else nits.pick (nit_config_version, es_warning, ec_init, "bad version ", quote (ver)," ignored"); } }

    if (! context.cgi ())
    {   PRESUME (var_.count (WEBSITE ROOT) > 0, __FILE__, __LINE__);
        const ::std::string arg = trim_the_lot_off (var_ [WEBSITE ROOT].as < ::std::string > ());
        if (arg.empty ()) nits.pick (nit_no_such_folder, es_error, ec_init, "that --" WEBSITE ROOT " is a little too spaced out for " PROG);
        else
        {   const ::std::string local = nix_path_to_local (arg);
            if (! ::boost::filesystem::exists (local)) nits.pick (nit_no_such_folder, es_error, ec_init, PROG " cannot access the directory ", quote (local));
            else if (::boost::filesystem::is_directory (local)) context.root (local);
            else nits.pick (nit_not_directory, es_error, ec_init, "expecting a directory containing a static website, not ", quote (local)); } }

    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> load_template (nits, context.html_ver ());

    for (int i = s_none + 1; i < s_error; ++i)
    {   const e_schema es = static_cast < e_schema > (i);
        if (is_faux_schema (es)) continue;
        if (get_schema_version_count (es) < 2) continue;
        const ::std::string naam (schema_names.get (es, SCHEMA_NAME));
        ::std::string arg (ONTOLOGY);
        arg += naam;
        if (var_.count (arg))
        {   ::std::string ver (trim_the_lot_off (var_ [arg].as < ::std::string > ()));
            const ::std::string::size_type pos = ver.find ('.');
            // boost lexical cast, bless its little cotton socks, doesn't process unsigned char as a number
            schema_version x (error_schema);
            if (pos == ::std::string::npos)
                x = schema_version (es, GSL_NARROW_CAST < unsigned char > (lexical < unsigned int > :: cast (ver)), 0);
            else if (pos == 0)
                nits.pick (nit_config_version, es_warning, ec_init, "missing ontology major version");
            else if (pos == ver.length () - 1)
                x = schema_version (es, GSL_NARROW_CAST < unsigned char > (lexical < unsigned int > :: cast (ver.substr (0, pos))), 0);
            else if (pos > 0)
                x = schema_version (es, GSL_NARROW_CAST < unsigned char > (lexical < unsigned int > :: cast (ver.substr (0, pos))),
                                                              GSL_NARROW_CAST < unsigned char > (lexical < unsigned int > :: cast (ver.substr (pos+1))));
            if (x.invalid ())
                nits.pick (nit_config_version, es_error, ec_init, "invalid ontology ", quote (x.name ()), " version; use " ONTOLOGY LIST " to get a list of known versions.");
            else if (! set_default_schema_version (x.root (), x.mjr (), x.mnr ()))
                nits.pick (nit_config_version, es_error, ec_init, PROG " dislikes the ", quote (x.name ()), " version specified; use " ONTOLOGY LIST " to get a list of known versions."); } }

    if (var_.count (VALIDATION MICRODATAARG)) context.microdata (true);
    if (var_.count (VALIDATION DONT MICRODATAARG)) context.microdata (false);

    if (! context.cgi ())
    {   yea_nay (&context_t::unknown_class, nits, GENERAL CLASS, GENERAL DONT CLASS);
        yea_nay (&context_t::classic, nits, GENERAL CLASSIC, GENERAL DONT CLASSIC);
        yea_nay (&context_t::load_css, nits, GENERAL CSS_OPTION, GENERAL DONT CSS_OPTION);
        yea_nay (&context_t::progress, nits, GENERAL PROGRESS, GENERAL DONT PROGRESS);
        yea_nay (&context_t::rdfa, nits, GENERAL RDFA_, GENERAL DONT RDFA_);
        yea_nay (&context_t::rel, nits, GENERAL REL, GENERAL DONT REL);
        yea_nay (&context_t::rpt_opens, nits, GENERAL RPT, GENERAL DONT RPT);
        yea_nay (&context_t::slob, nits, GENERAL SLOB, GENERAL DONT SLOB);
        yea_nay (&context_t::ssi, nits, GENERAL SSI, GENERAL DONT SSI);
        context.persisted (path_in_context (nix_path_to_local (var_ [GENERAL FICHIER].as < ::std::string > ())));

        CONSTEXPR long meg = 1024*1024;

        if (! var_.count (GENERAL MAXFILESIZE))
            context.max_file_size (4 * meg);
        else
        {   long max = static_cast < long > (var_ [GENERAL MAXFILESIZE].as < int > ());
            if (max < 0 || (max > (LONG_MAX / meg))) max = DEFAULT_MAX_FILE_SIZE;
            context.max_file_size (max * meg); }

        if (var_.count (GENERAL CUSTOM)) context.custom_elements ( var_ [GENERAL CUSTOM].as < vstr_t > ());
        if (var_.count (GENERAL ERR))
        {   e_severity sev = decode_severity (nits, var_ [GENERAL ERR].as < ::std::string > ());
            if (sev != es_undefined) context.report_error (sev); }
#ifndef NO_BOOST_REGEX
        if (var_.count (GENERAL EXCLUDE)) context.exclude (nits, var_ [GENERAL EXCLUDE].as < vstr_t > ());
#endif // NO_BOOST_REGEX
        if (var_.count (GENERAL GIT)) context.exclude (nits, ".git");
        if (var_.count (GENERAL IGNORED)) context.ignore (nits, var_ [GENERAL IGNORED].as < vstr_t > ());
        if (var_.count (GENERAL LANG)) context.lang (var_ [GENERAL LANG].as < ::std::string > ());
        if (var_.count (GENERAL MACROEND)) context.macro_end (var_ [GENERAL MACROEND].as < ::std::string > ());
        if (var_.count (GENERAL MACROSTART)) context.macro_start (var_ [GENERAL MACROSTART].as < ::std::string > ());

        if (var_.count (CORPUS OUTPUT)) context.corpus (nix_path_to_local (var_ [CORPUS OUTPUT].as < ::std::string > ()));
        yea_nay (&context_t::article, nits, CORPUS ARTICLE, CORPUS DONT ARTICLE);
        yea_nay (&context_t::body, nits, CORPUS BODY, CORPUS DONT BODY);
        yea_nay (&context_t::main, nits, CORPUS MAIN, CORPUS DONT MAIN);

        yea_nay (&context_t::rfc_1867, nits, HTML RFC1867, HTML DONT RFC1867);
        yea_nay (&context_t::rfc_1942, nits, HTML RFC1942, HTML DONT RFC1942);
        yea_nay (&context_t::rfc_1980, nits, HTML RFC1980, HTML DONT RFC1980);
        yea_nay (&context_t::rfc_2070, nits, HTML RFC2070, HTML DONT RFC2070);
        yea_nay (&context_t::presume_tags, nits, HTML TAGS, HTML DONT TAGS);
        if (var_.count (HTML TITLE)) context.title (static_cast < unsigned char > (var_ [HTML TITLE].as < int > ()));

        yea_nay (&context_t::jsonld, nits, JSONLD VERIFY, JSONLD DONT VERIFY);
        if (var_.count (JSONLD EXTENSION)) context.jsonld_extension (var_ [JSONLD EXTENSION].as < vstr_t > ());

        if (var_.count (JSONLD VERSION))
        {   ::std::string ver (var_ [JSONLD VERSION].as < ::std::string > ());
            if (ver.empty ())
                nits.pick (nit_config_version, es_warning, ec_init, "missing json-ld version");
            else
            {   if (ver == "1.0") context.jsonld_version (jsonld_1_0);
                else if (ver == "1.1") context.jsonld_version (jsonld_1_1);
                else nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid json-ld version"); } }

        yea_nay (&context_t::links, nits, LINKS CHECK, LINKS DONT CHECK);
        yea_nay (&context_t::example, nits, LINKS EXAMPLE, LINKS DONT EXAMPLE);
        yea_nay (&context_t::external, nits, LINKS EXTERNAL, LINKS DONT EXTERNAL);
        yea_nay (&context_t::forwarded, nits, LINKS FORWARD, LINKS DONT FORWARD);
        if (var_.count (LINKS IGNORED)) context.no_ex_check (var_ [LINKS IGNORED].as < vstr_t > ());
        yea_nay (&context_t::local, nits, LINKS LOCAL, LINKS DONT LOCAL);
        yea_nay (&context_t::once, nits, LINKS ONCE, LINKS DONT ONCE);
        if (var_.count (LINKS REPORT)) context.report (var_ [LINKS REPORT].as < vstr_t > ());
        yea_nay (&context_t::revoke, nits, LINKS REVOKE, LINKS DONT REVOKE);
        yea_nay (&context_t::crosslinks, nits, LINKS XLINK, LINKS DONT XLINK);

        if (var_.count (MATH VERSION))
        {   int n = var_ [MATH VERSION].as < int > ();
            switch (n)
            {   case 0 : break;
                case 1 : context.math_version (math_1); break;
                case 2 : context.math_version (math_2); break;
                case 3 : context.math_version (math_3); break;
                case 4 : context.math_version (math_4_22); break;
                default : nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid MathML version"); context.math_version (math_none); } }

        if (var_ [MATH CORE].as < bool > ()) context.math_version (math_core);

        if (var_.count (MATH DRAFT))
        {   int n = var_ [MATH DRAFT].as < int > ();
            switch (n)
            {   case 0 : break;
                case 2020: case 20 : if (context.math_version () > math_3) context.math_version (math_4_20); break;
                case 2022: case 22 : if (context.math_version () > math_3) context.math_version (math_4_22); break;
                default : nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid MathML 4 draft"); break; } }

        yea_nay (&context_t::mf_export, nits, MF EXPORT, MF DONT EXPORT);

        yea_nay (&context_t::md_export, nits, MICRODATA EXPORT, MICRODATA DONT EXPORT);
        yea_nay (&context_t::schema, nits, MICRODATA VERIFY, MICRODATA DONT VERIFY);
        if (var_.count (MICRODATA ROOT)) context.export_root (nix_path_to_local (var_ [MICRODATA ROOT].as < ::std::string > ()));
        if (var_.count (MICRODATA VIRTUAL)) context.exports (var_ [MICRODATA VIRTUAL].as < vstr_t > ());

        yea_nay (&context_t::nids, nits, NITS NIDS, NITS DONT NIDS);
        if (var_.count (NITS FORMAT)) context.nit_format (var_ [NITS FORMAT].as < ::std::string > ());
        if (var_.count (NITS QUOTE))
        {   e_quote_style qs = examine_value < t_quote_style > (nits, html_default, var_ [NITS QUOTE].as < ::std::string > ());
            context.quote_style (qs); }
        yea_nay (&context_t::nits_nits_nits, nits, NITS UNIQUE, NITS DONT UNIQUE);
        yea_nay (&context_t::not_root, nits, NITS DONT ROOT, NITS ROOT); // note reversal
        yea_nay (&context_t::nits, nits, NITS WATCH, NITS DONT WATCH);

        if (var_.count (NITS CATASTROPHE))
            for (auto s : var_ [NITS CATASTROPHE].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_catastrophic))
                    nits.pick (nit_config_nit, es_error, ec_init, quote (s), ": no such nit.");

        if (var_.count (NITS COMMENT))
            for (auto s : var_ [NITS COMMENT].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_comment))
                    nits.pick (nit_config_nit, es_error, ec_init, quote (s), ": no such nit.");

        if (var_.count (NITS DBG))
            for (auto s : var_ [NITS DBG].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_debug))
                    nits.pick (nit_config_nit, es_error, ec_init, quote (s), ": no such nit.");

        if (var_.count (NITS ERR))
            for (auto s : var_ [NITS ERR].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_error))
                    nits.pick (nit_config_nit, es_error, ec_init, quote (s), ": no such nit.");

        if (var_.count (NITS INFO))
            for (auto s : var_ [NITS INFO].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_info))
                    nits.pick (nit_config_nit, es_error, ec_init, quote (s), ": no such nit.");

        if (var_.count (NITS SILENCE))
            for (auto s : var_ [NITS SILENCE].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_illegal))
                    nits.pick (nit_config_nit, es_error, ec_init, quote (s), ": no such nit.");

        if (var_.count (NITS WARNING))
            for (auto s : var_ [NITS WARNING].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_warning))
                    nits.pick (nit_config_nit, es_error, ec_init, quote (s), ": no such nit.");

//      TO BE REACTIVATED!!! Hopefully.
//        if (var_.count (RDFA VERSION))
//        {   ::std::string rv = var_ [RDFA VERSION].as < ::std::string > ();
//            if (rv != "1.0") && (rv != "1.1") && (rv != "1.1.1") && (rv != "1.1.2") && (rv != "1.1.3")
//            context.rdfa_version (n); }

        yea_nay (&context_t::shadow_changed, nits, SHADOW CHANGED, SHADOW DONT CHANGED);
        yea_nay (&context_t::shadow_comment, nits, SHADOW COMMENT, SHADOW DONT COMMENT);

        if (var_.count (SHADOW COPY))
        {   nitpick nuts;
            ::std::string s (var_ [SHADOW COPY].as < ::std::string  > ());
            e_shadow sh = examine_value < t_shadow > (nuts, html_tags, s);
            if (sh == sh_error)
                if ((s.length () == 1) && (GSL_AT (s, 0) >= '0') && (GSL_AT (s, 0) <= '7'))
                {   sh = static_cast < e_shadow > (GSL_AT (s, 0) - '0' + 1);
#ifdef NOLYNX
                    if ((sh == sh_hard) || (sh == sh_soft)) sh = sh_copy;
#endif // NOLYNX
                                                                           }
            if (sh != sh_error) context.copy (static_cast < int > (sh) - 1);
            else nits.pick (nit_config_shadow, es_error, ec_init, "invalid " SHADOW COPY " option"); }

        yea_nay (&context_t::shadow_enable, nits, SHADOW ENABLE, SHADOW DONT ENABLE);
        if (var_.count (SHADOW FICHIER)) context.shadow_persist (nix_path_to_local (var_ [SHADOW FICHIER].as < ::std::string > ()));
        if (var_.count (SHADOW IGNORED)) context.shadow_ignore (var_ [SHADOW IGNORED].as < vstr_t > ());
        yea_nay (&context_t::info, nits, SHADOW INFO, SHADOW DONT INFO);
        if (var_.count (SHADOW MSG)) context.msg (var_ [SHADOW MSG].as < ::std::string > ());
        if (var_.count (SHADOW ROOT)) context.shadow_root (nix_path_to_local (var_ [SHADOW ROOT].as < ::std::string > ()));
        yea_nay (&context_t::shadow_space, nits, SHADOW SPACING, SHADOW DONT SPACING);
        yea_nay (&context_t::shadow_ssi, nits, SHADOW SSI, SHADOW DONT SSI);
        yea_nay (&context_t::update, nits, SHADOW UPDATE, SHADOW DONT UPDATE);
        if (var_.count (SHADOW VIRTUAL)) context.shadows (var_ [SHADOW VIRTUAL].as < vstr_t > ());

        if (var_.count (WEBSITE INDEX)) context.index (var_ [WEBSITE INDEX].as < ::std::string > ());
        if (var_.count (WEBSITE EXTENSION)) context.extensions (var_ [WEBSITE EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back ("html"); context.extensions (ex); }
        if (var_.count (WEBSITE SITE)) context.site (var_ [WEBSITE SITE].as < vstr_t > ());
        if (var_.count (WEBSITE VIRTUAL)) context.virtuals (var_ [WEBSITE VIRTUAL].as < vstr_t > ());

#ifdef NOSPELL
        context.spell (false);
#else // NOSPELL
        yea_nay (&context_t::spell, nits, SPELL CHECK, SPELL DONT CHECK);
        yea_nay (&context_t::cased, nits, SPELL CASED, SPELL DONT CASED);
        yea_nay (&context_t::icu, nits, SPELL ICU, SPELL DONT ICU);
        if (context.spell ())
        {   if (var_.count (SPELL ACCEPT)) context.spellings (var_ [SPELL ACCEPT].as < vstr_t > ());
            if (var_.count (SPELL LIST))
            {   vstr_t lists (var_ [SPELL LIST].as < vstr_t > ());
                for (auto fl : lists)
                {   ::std::string lang;
                    ::boost::filesystem::path fn;
                    const ::std::string::size_type pos = fl.find (',');
                    if (pos == ::std::string::npos) fn = tart (fl);
                    else
                    {   if (pos == 0)
                        {   nits.pick (nit_bad_list, es_error, ec_init, "filename missing in ", SPELL LIST, "=", quote (fl));
                            continue; }
                        fn = tart (fl.substr (0, pos));
                        if (pos < fl.size () - 1) lang = tart (fl.substr (pos+1)); }
                    add_spell_list (nits, lang, fn); } }
#ifdef HUNSPELL
            if (var_.count (SPELL PATH))
            {   ::boost::filesystem::path hunspell (var_ [SPELL PATH].as < ::std::string > ());
                if (! ::boost::filesystem::exists (hunspell)) { nits.pick (nit_no_spell, es_error, ec_init, "Cannot find ", hunspell.string ()); context.spell (false); }
                else if (! ::boost::filesystem::is_directory (hunspell)) { nits.pick (nit_no_spell, es_error, ec_init, hunspell.string (), " is not a directory"); context.spell (false); }
                else context.spell_path (hunspell); }
            else
            {   bool found = false;
                vstr_t check =
                {   "/usr/local/share/mozilla-dicts", // OpenBSD
                    "/opt/local/share/hunspell", // macports
                    "/opt/local/share/myspell",
                    "/opt/local/share/mozilla-dicts",
                    "/usr/share/mozilla-dicts",
                    "/usr/share/hunspell", // SuSE
                    "/usr/share/doc/hunspell", // ubuntu
                    "/usr/share/myspell",
                    "/usr/local/share/hunspell",
                    "/usr/local/share/myspell",
                    "/usr/share/doc/hunspell-en",
                    "/usr/share/doc/hunspell-en-GB",
                    "/usr/share/doc/hunspell-en-gb",
                    "/usr/share/doc/hunspell-en-US",
                    "/usr/share/doc/hunspell-en-us",
                    "/usr/share/doc/hunspell-fr",
                    "/usr/share/doc/hunspell-de",
                    "/usr/share/doc/hunspell-de-de",
                    "/usr/share/doc/hunspell-de-DE",
                    "/usr/share/doc/hunspell-nl",
                    "/usr/share/doc/hunspell-lb" };
                for (auto dd : check)
                    if (::boost::filesystem::exists (dd))
                        if (::boost::filesystem::is_directory (dd))
                        {   context.spell_path (dd);
                            found = true; }
                if (found) context.spell_deduced (true);
                else
                {   nits.pick (nit_no_spell, es_error, ec_init, "Cannot find dictionaries");
                    context.spell (false); } }
            if (context.spell () && var_.count (SPELL DICT))
            {   vstr_t lists (var_ [SPELL DICT].as < vstr_t > ());
                for (auto ld : lists)
                {   ::std::string lang, dict;
                    const ::std::string::size_type pos = ld.find (',');
                    if ((pos == ::std::string::npos) || (pos == ld.size () - 1))
                    {   nits.pick (nit_bad_dict, es_error, ec_init, "dictionary missing in ", SPELL DICT, "=", quote (ld));
                        continue; }
                    if (pos == 0)
                    {   nits.pick (nit_bad_dict, es_error, ec_init, "lang missing in ", SPELL DICT, "=", quote (ld));
                        continue; }
                    lang = tart (ld.substr (0, pos));
                    dict = tart (ld.substr (pos+1));
                    add_dict (lang, dict); } }
#endif // HUNSPELL
            lingo::identify_dialects (nits); }
#endif // NOSPELL

        if (var_.count (STATS EXPORT)) context.stats (var_ [STATS EXPORT].as < ::std::string > ());
        yea_nay (&context_t::meta, nits, STATS META, STATS DONT META);
        yea_nay (&context_t::stats_page, nits, STATS PAGE, STATS DONT PAGE);
        yea_nay (&context_t::stats_summary, nits, STATS SUMMARY, STATS DONT SUMMARY);

        if (var_.count (SVG VERSION))
        {   ::std::string ver (var_ [SVG VERSION].as < ::std::string > ());
            {   const ::std::string::size_type slash = ver.find ('/');
                ::std::string ps;
                if (slash != ::std::string::npos)
                {   ps = ver.substr (slash+1);
                    ver = ver.substr (0, slash); }
                const ::std::string::size_type pos = ver.find ('.');
                if (pos == ::std::string::npos)
                    if (ver.length () == 1) context.svg_version (sv_none);
                    else context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), 0);
                else if (pos == ver.length () - 1) context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), 0);
                else if (pos == 0) context.svg_version (sv_none);
                else context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), lexical < int > :: cast (ver.substr (pos+1)));
                if ((slash != ::std::string::npos) && (context.svg_version () == sv_1_2_tiny) && compare_no_case (ps, "full")) context.svg_version (sv_1_2_full); } }

        if (var_.count (VALIDATION ATTRIB)) add_attributes (var_ [VALIDATION ATTRIB].as < vstr_t > ());
        if (var_.count (VALIDATION CHARSET)) type_master < t_charset > :: extend (var_ [VALIDATION CHARSET].as < vstr_t > ());
        if (var_.count (VALIDATION CLASS)) type_master < t_class > :: extend (var_ [VALIDATION CLASS].as < vstr_t > ());
        if (var_.count (VALIDATION COLOR)) type_master < t_fixedcolour > :: extend (var_ [VALIDATION COLOR].as < vstr_t > ());
        if (var_.count (VALIDATION COLOUR)) type_master < t_fixedcolour > :: extend (var_ [VALIDATION COLOUR].as < vstr_t > ());
        if (var_.count (VALIDATION COUNTRY)) type_master < t_country > :: extend (var_ [VALIDATION COUNTRY].as < vstr_t > ());
        if (var_.count (VALIDATION CURRENCY)) type_master < t_currency > :: extend (var_ [VALIDATION CURRENCY].as < vstr_t > ());
        if (var_.count (VALIDATION DINGBATARG)) type_master < t_dingbat > :: extend (var_ [VALIDATION DINGBATARG].as < vstr_t > ());
        if (var_.count (VALIDATION ELEMENT)) add_elements (var_ [VALIDATION ELEMENT].as < vstr_t > ());
        if (var_.count (VALIDATION ELEMATTR)) add_element_attributes (var_ [VALIDATION ELEMATTR].as < vstr_t > ());
        if (var_.count (VALIDATION EXTENSION)) type_master < t_format > :: extend (var_ [VALIDATION EXTENSION].as < vstr_t > ());
        if (var_.count (VALIDATION HTTPEQUIV)) type_master < t_httpequiv > :: extend (var_ [VALIDATION HTTPEQUIV].as < vstr_t > ());
        if (var_.count (VALIDATION LANG)) type_master < t_lang > :: extend (var_ [VALIDATION LANG].as < vstr_t > ());
        if (var_.count (VALIDATION REL)) type_master < t_rel > :: extend (var_ [VALIDATION REL].as < vstr_t > ());
        if (var_.count (VALIDATION METANAME)) type_master < t_metaname  > :: extend (var_ [VALIDATION METANAME].as < vstr_t > ());
        if (var_.count (VALIDATION MIMETYPE)) type_master < t_mime > :: extend (var_ [VALIDATION MIMETYPE].as < vstr_t > ());
        if (var_.count (VALIDATION SGML)) type_master < t_sgml > :: extend (var_ [VALIDATION SGML].as < vstr_t > (), static_cast < ::std::size_t > (doc_context));

#define TEST_VAR(XX) if (var_.count (VALIDATION #XX)) type_master < t_##XX > :: extend (var_ [VALIDATION #XX].as < vstr_t > ())
        TEST_VAR (accrual_method);
        TEST_VAR (accrual_periodicity);
        TEST_VAR (accrual_policy);
        TEST_VAR (action);
        TEST_VAR (align3);
        TEST_VAR (alignplus);
        TEST_VAR (as);
        TEST_VAR (as_units);
        TEST_VAR (autocapitalise);
        TEST_VAR (autocomplete);
        TEST_VAR (beginfn);
        TEST_VAR (baselineshift);
        TEST_VAR (citype);
        TEST_VAR (cntype);
        TEST_VAR (composite_operator);
        TEST_VAR (dcmitype);
        TEST_VAR (decalign);
        TEST_VAR (dingbat);
        TEST_VAR (dir);
        TEST_VAR (display_align);
        TEST_VAR (dominantbaseline);
        TEST_VAR (enterkeyhint);
        TEST_VAR (figalign);
        TEST_VAR (fontname);
        TEST_VAR (halign);
        TEST_VAR (icc);
        TEST_VAR (inputmode);
        TEST_VAR (inputplus);
        TEST_VAR (inputtype);
        TEST_VAR (inputtype3);
        TEST_VAR (inputtype32);
        TEST_VAR (inputtype4);
        TEST_VAR (inputtype5);
        TEST_VAR (kind);
        TEST_VAR (linebreak);
        TEST_VAR (listtype);
        TEST_VAR (mah);
        TEST_VAR (mathalign);
        TEST_VAR (mathvariant);
        TEST_VAR (matrixtype);
        TEST_VAR (media);
        TEST_VAR (mediafeature);
        TEST_VAR (mediakeyword);
        TEST_VAR (method);
        TEST_VAR (mf_identifier);
        TEST_VAR (mf_itemtype);
        TEST_VAR (mf_listing_action);
        TEST_VAR (mf_method);
        TEST_VAR (mf_reviewtype);
        TEST_VAR (namedspace);
        TEST_VAR (mathnotation);
        TEST_VAR (ogtype);
        TEST_VAR (paintkeyword);
        TEST_VAR (plusstyle);
        TEST_VAR (pointer_events);
        TEST_VAR (print);
        TEST_VAR (referrer);
        TEST_VAR (rendering_in_tents);
        TEST_VAR (rules);
        TEST_VAR (sandbox);
        TEST_VAR (shape7);
        TEST_VAR (shape_rendering);
        TEST_VAR (ssi);
        TEST_VAR (ssi_comparison);
        TEST_VAR (ssi_encoding);
        TEST_VAR (ssi_env);
        TEST_VAR (svg_align);
        TEST_VAR (svg_display);
        TEST_VAR (svg_feature);
        TEST_VAR (svg_fontstretch);
        TEST_VAR (svg_fontstretch_ff);
        TEST_VAR (svg_fontstyle);
        TEST_VAR (svg_fontweight);
        TEST_VAR (svg_fontweight_ff);
        TEST_VAR (svg_mode);
        TEST_VAR (svg_overflow);
        TEST_VAR (svg_version);
        TEST_VAR (svg_version_grand);
        TEST_VAR (tableframe);
        TEST_VAR (text_decoration);
        TEST_VAR (text_rendering);
        TEST_VAR (transform_anim);
        TEST_VAR (transform_fn);
        TEST_VAR (turbulence_type);
        TEST_VAR (unicode_bidi);
        TEST_VAR (vector_effect_2);
        TEST_VAR (xmlns);
#undef TEST_VAR

        }
    context.consolidate_jsonld ();
#ifdef NOCURL
    if (context.external ())
        nits.pick (nit_no_curl, es_warning, ec_init, "Unfortunately, this build of " PROG " cannot verify external links");
#endif // NOCURL
}

void pvs (::std::ostringstream& res, const vstr_t& data)
{   for (auto i : data)
        res << i << " "; }

::std::string options::report () const
{   ::std::ostringstream res;
#ifndef EXPAND_TEST
    if (context.test ()) return res.str ();
#endif // EXPAND_TEST

    ::std::ostringstream e;

    if (env_.count (ENV_CONFIG)) e << ENV_CONFIG ": " << env_ [ENV_CONFIG].as < ::std::string > () << "\n";
    if (env_.count (ENV_ARGS)) e << ENV_ARGS ": " << env_ [ENV_ARGS].as < ::std::string > () << "\n";

    if (env_.count (QUERY_STRING))
    {   if (env_.count (SERVER_SOFTWARE)) e << SERVER_SOFTWARE ": " << env_ [SERVER_SOFTWARE].as < ::std::string > () << "\n";
        if (env_.count (SERVER_NAME)) e << SERVER_NAME ": " << env_ [SERVER_NAME].as < ::std::string > () << "\n";
        if (env_.count (GATEWAY_INTERFACE)) e << GATEWAY_INTERFACE ": " << env_ [GATEWAY_INTERFACE].as < ::std::string > () << "\n";
        if (env_.count (SERVER_PROTOCOL)) e << SERVER_PROTOCOL ": " << env_ [SERVER_PROTOCOL].as < ::std::string > () << "\n";
        if (env_.count (SERVER_PORT)) e << SERVER_PORT ": " << env_ [SERVER_PORT].as < ::std::string > () << "\n";
        if (env_.count (REQUEST_METHOD)) e << REQUEST_METHOD ": " << env_ [REQUEST_METHOD].as < ::std::string > () << "\n";
        if (env_.count (HTTP_ACCEPT)) e << HTTP_ACCEPT ": " << env_ [HTTP_ACCEPT].as < ::std::string > () << "\n";
        if (env_.count (PATH_INFO)) e << PATH_INFO ": " << env_ [PATH_INFO].as < ::std::string > () << "\n";
        if (env_.count (PATH_TRANSLATED)) e << PATH_TRANSLATED ": " << env_ [PATH_TRANSLATED].as < ::std::string > () << "\n";
        if (env_.count (SCRIPT_NAME)) e << SCRIPT_NAME ": " << env_ [SCRIPT_NAME].as < ::std::string > () << "\n";
        if (env_.count (REMOTE_HOST)) e << REMOTE_HOST ": " << env_ [REMOTE_HOST].as < ::std::string > () << "\n";
        if (env_.count (REMOTE_ADDR)) e << REMOTE_ADDR ": " << env_ [REMOTE_ADDR].as < ::std::string > () << "\n";
        if (env_.count (REMOTE_USER)) e << REMOTE_USER ": " << env_ [REMOTE_USER].as < ::std::string > () << "\n";
        if (env_.count (AUTH_TYPE)) e << AUTH_TYPE ": " << env_ [AUTH_TYPE].as < ::std::string > () << "\n";
        if (env_.count (CONTENT_TYPE)) e << CONTENT_TYPE ": " << env_ [CONTENT_TYPE].as < ::std::string > () << "\n";
        if (env_.count (CONTENT_LENGTH)) e << CONTENT_LENGTH ": " << env_ [CONTENT_LENGTH].as < ::std::string > () << "\n";

        ::std::string qs (env_ [QUERY_STRING].as < ::std::string > ());
        e << QUERY_STRING ": " << qs << "\n            : " << query_to_switches (qs) << "\n"; }

    ::std::string x (e.str ());
    if (! x.empty ()) res << "\n" START_OF_SUBSECTION " Environment:\n" << x << "\n";

    res << "\n" START_OF_SUBSECTION " Arguments:\n";

    if (var_ [HELP].as < bool > ()) res << HELP "\n";
    if (var_ [VERSION].as < bool > ()) res << VERSION "\n";

    if (var_ [CORPUS ARTICLE].as < bool > ()) res << CORPUS ARTICLE "\n";
    if (var_ [CORPUS DONT ARTICLE].as < bool > ()) res << CORPUS DONT ARTICLE "\n";
    if (var_ [CORPUS BODY].as < bool > ()) res << CORPUS BODY "\n";
    if (var_ [CORPUS DONT BODY].as < bool > ()) res << CORPUS DONT BODY "\n";
    if (var_ [CORPUS MAIN].as < bool > ()) res << CORPUS MAIN "\n";
    if (var_ [CORPUS DONT MAIN].as < bool > ()) res << CORPUS DONT MAIN "\n";
    if (var_.count (CORPUS OUTPUT)) res << CORPUS OUTPUT ": " << var_ [CORPUS OUTPUT].as < ::std::string > () << "\n";

    if (var_.count (ENVIRONMENT QUERY_STRING))
    {   if (var_.count (ENVIRONMENT SERVER_SOFTWARE)) res << ENVIRONMENT SERVER_SOFTWARE ": " << var_ [ENVIRONMENT SERVER_SOFTWARE].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT SERVER_NAME)) res << ENVIRONMENT SERVER_NAME ": " << var_ [ENVIRONMENT SERVER_NAME].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT GATEWAY_INTERFACE)) res << ENVIRONMENT GATEWAY_INTERFACE ": " << var_ [ENVIRONMENT GATEWAY_INTERFACE].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT SERVER_PROTOCOL)) res << ENVIRONMENT SERVER_PROTOCOL ": " << var_ [ENVIRONMENT SERVER_PROTOCOL].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT SERVER_PORT)) res << ENVIRONMENT SERVER_PORT ": " << var_ [ENVIRONMENT SERVER_PORT].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT REQUEST_METHOD)) res << ENVIRONMENT REQUEST_METHOD ": " << var_ [ENVIRONMENT REQUEST_METHOD].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT HTTP_ACCEPT)) res << ENVIRONMENT HTTP_ACCEPT ": " << var_ [ENVIRONMENT HTTP_ACCEPT].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT PATH_INFO)) res << ENVIRONMENT PATH_INFO ": " << var_ [ENVIRONMENT PATH_INFO].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT PATH_TRANSLATED)) res << ENVIRONMENT PATH_TRANSLATED ": " << var_ [ENVIRONMENT PATH_TRANSLATED].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT SCRIPT_NAME)) res << ENVIRONMENT SCRIPT_NAME ": " << var_ [ENVIRONMENT SCRIPT_NAME].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT REMOTE_HOST)) res << ENVIRONMENT REMOTE_HOST ": " << var_ [ENVIRONMENT REMOTE_HOST].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT REMOTE_ADDR)) res << ENVIRONMENT REMOTE_ADDR ": " << var_ [ENVIRONMENT REMOTE_ADDR].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT REMOTE_USER)) res << ENVIRONMENT REMOTE_USER ": " << var_ [ENVIRONMENT REMOTE_USER].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT AUTH_TYPE)) res << ENVIRONMENT AUTH_TYPE ": " << var_ [ENVIRONMENT AUTH_TYPE].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT CONTENT_TYPE)) res << ENVIRONMENT CONTENT_TYPE ": " << var_ [ENVIRONMENT CONTENT_TYPE].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT CONTENT_LENGTH)) res << ENVIRONMENT CONTENT_LENGTH ": " << var_ [ENVIRONMENT CONTENT_LENGTH].as < ::std::string > () << "\n";

        ::std::string qs (var_ [ENVIRONMENT QUERY_STRING].as < ::std::string > ());
        res << ENVIRONMENT QUERY_STRING ": " << qs << "\n            : " << query_to_switches (qs) << "\n"; }

    if (var_ [GENERAL CGI].as < bool > ()) res << GENERAL CGI "\n";
    if (var_ [GENERAL DONT CGI].as < bool > ()) res << GENERAL DONT CGI "\n";
    if (var_ [GENERAL CLASS].as < bool > ()) res << GENERAL CLASS "\n";
    if (var_ [GENERAL DONT CLASS].as < bool > ()) res << GENERAL DONT CLASS "\n";
    if (var_ [GENERAL CLASSIC].as < bool > ()) res << GENERAL CLASSIC "\n";
    if (var_ [GENERAL DONT CLASSIC].as < bool > ()) res << GENERAL DONT CLASSIC "\n";
    if (var_.count (GENERAL CSS_OPTION)) res << GENERAL CSS_OPTION "\n";
    if (var_.count (GENERAL DONT CSS_OPTION)) res << GENERAL DONT CSS_OPTION "\n";
    if (var_.count (GENERAL CUSTOM)) { res << GENERAL CUSTOM ": "; pvs (res, var_ [GENERAL CUSTOM].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL DATAPATH)) res << GENERAL DATAPATH ": " << var_ [GENERAL DATAPATH].as < ::std::string > () << "\n";
    if (var_.count (GENERAL DEFTHRD)) res << GENERAL DEFTHRD ": " << var_ [GENERAL DEFTHRD].as < int > () << "\n";
    if (var_.count (GENERAL ERR)) res << GENERAL ERR ": " << var_ [GENERAL ERR].as < ::std::string > () << "\n";
    if (var_.count (GENERAL ENVIRONMENT)) { res << GENERAL ENVIRONMENT ": "; pvs (res, var_ [GENERAL ENVIRONMENT].as < vstr_t > ()); res << "\n"; }
#ifndef NO_BOOST_REGEX
    if (var_.count (GENERAL EXCLUDE)) { res << GENERAL EXCLUDE ": "; pvs (res, var_ [GENERAL EXCLUDE].as < vstr_t > ()); res << "\n"; }
#endif // NO_BOOST_REGEX
    if (var_.count (GENERAL FICHIER)) res << GENERAL FICHIER ": " << var_ [GENERAL FICHIER].as < ::std::string > () << "\n";
    if (var_ [GENERAL INFO].as < bool > ()) res << GENERAL INFO "\n";
    if (var_.count (GENERAL IGNORED)) { res << GENERAL IGNORED ": "; pvs (res, var_ [GENERAL IGNORED].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL LANG)) res << GENERAL LANG ": " << var_ [GENERAL LANG].as < ::std::string > () << "\n";
    if (var_.count (GENERAL MACROEND)) res << GENERAL MACROEND ": " << var_ [GENERAL MACROEND].as < ::std::string > () << "\n";
    if (var_.count (GENERAL MACROSTART)) res << GENERAL MACROSTART ": " << var_ [GENERAL MACROSTART].as < ::std::string > () << "\n";
    if (var_.count (GENERAL MAXFILESIZE)) res << GENERAL MAXFILESIZE ": " << var_ [GENERAL MAXFILESIZE].as < int > () << "\n";
    if (var_ [GENERAL PROGRESS].as < bool > ()) res << GENERAL PROGRESS "\n";
    if (var_ [GENERAL DONT PROGRESS].as < bool > ()) res << GENERAL DONT PROGRESS "\n";
    if (var_.count (GENERAL RDFA_)) res << GENERAL RDFA_ "\n";
    if (var_.count (GENERAL DONT RDFA_)) res << GENERAL DONT RDFA_ "\n";
    if (var_ [GENERAL REL].as < bool > ()) res << GENERAL REL "\n";
    if (var_ [GENERAL DONT REL].as < bool > ()) res << GENERAL DONT REL "\n";
    if (var_ [GENERAL RPT].as < bool > ()) res << GENERAL RPT "\n";
    if (var_ [GENERAL DONT RPT].as < bool > ()) res << GENERAL DONT RPT "\n";
    if (var_ [GENERAL SLOB].as < bool > ()) res << GENERAL SLOB "\n";
    if (var_ [GENERAL DONT SLOB].as < bool > ()) res << GENERAL DONT SLOB "\n";
    if (var_ [GENERAL SPEC].as < bool > ()) res << GENERAL SPEC "\n";
    if (var_ [GENERAL SSI].as < bool > ()) res << GENERAL SSI "\n";
    if (var_ [GENERAL DONT SSI].as < bool > ()) res << GENERAL DONT SSI "\n";
    if (var_ [GENERAL TEST].as < bool > ()) res << GENERAL TEST "\n";
    if (var_ [GENERAL DONT TEST].as < bool > ()) res << GENERAL DONT TEST "\n";
#ifndef NO_FRED
    if (var_.count (GENERAL THREAD)) res << GENERAL THREAD ": " << var_ [GENERAL THREAD].as < int > () << "\n";
#endif // NO_FRED
    if (var_.count (GENERAL VERBOSE)) res << GENERAL VERBOSE ": " << var_ [GENERAL VERBOSE].as < ::std::string > () << "\n";

    if (var_.count (HTML RFC1867)) res << HTML RFC1867 "\n";
    if (var_.count (HTML DONT RFC1867)) res << HTML DONT RFC1867 "\n";
    if (var_.count (HTML RFC1942)) res << HTML RFC1942 "\n";
    if (var_.count (HTML DONT RFC1942)) res << HTML DONT RFC1942 "\n";
    if (var_.count (HTML RFC1980)) res << HTML RFC1980 "\n";
    if (var_.count (HTML DONT RFC1980)) res << HTML DONT RFC1980 "\n";
    if (var_.count (HTML RFC2070)) res << HTML RFC2070 "\n";
    if (var_.count (HTML DONT RFC2070)) res << HTML DONT RFC2070 "\n";
    if (var_.count (HTML SNIPPET)) res << HTML SNIPPET ": " << var_ [HTML SNIPPET].as < ::std::string > () << "\n";
    if (var_ [HTML TAGS].as < bool > ()) res << HTML TAGS "\n";
    if (var_ [HTML DONT TAGS].as < bool > ()) res << HTML DONT TAGS "\n";
    if (var_.count (HTML TITLE)) res << HTML TITLE ": " << var_ [HTML TITLE].as < int > () << "\n";
    if (var_.count (HTML VERSION)) res << HTML VERSION ": " << var_ [HTML VERSION].as < ::std::string > () << "\n";

    if (var_.count (JSONLD EXTENSION)) { res << JSONLD EXTENSION ": "; pvs (res, var_ [JSONLD EXTENSION].as < vstr_t > ()); res << "\n"; }
    if (var_ [JSONLD VERIFY].as < bool > ()) res << JSONLD VERIFY "\n";
    if (var_ [JSONLD DONT VERIFY].as < bool > ()) res << JSONLD DONT VERIFY "\n";
    if (var_.count (JSONLD VERSION)) res << JSONLD VERSION ": " << var_ [JSONLD VERSION].as < ::std::string > () << "\n";

    if (var_ [LINKS CHECK].as < bool > ()) res << LINKS CHECK "\n";
    if (var_ [LINKS DONT CHECK].as < bool > ()) res << LINKS DONT CHECK "\n";
    if (var_ [LINKS EXAMPLE].as < bool > ()) res << LINKS EXAMPLE "\n";
    if (var_ [LINKS DONT EXAMPLE].as < bool > ()) res << LINKS DONT EXAMPLE "\n";
    if (var_ [LINKS EXTERNAL].as < bool > ()) res << LINKS EXTERNAL "\n";
    if (var_ [LINKS DONT EXTERNAL].as < bool > ()) res << LINKS DONT EXTERNAL "\n";
    if (var_ [LINKS FORWARD].as < bool > ()) res << LINKS FORWARD "\n";
    if (var_ [LINKS DONT FORWARD].as < bool > ()) res << LINKS DONT FORWARD "\n";
    if (var_.count (LINKS IGNORED)) { res << LINKS IGNORED ": "; pvs (res, var_ [LINKS IGNORED].as < vstr_t > ()); res << "\n"; }
    if (var_ [LINKS LOCAL].as < bool > ()) res << LINKS LOCAL "\n";
    if (var_ [LINKS DONT LOCAL].as < bool > ()) res << LINKS DONT LOCAL "\n";
    if (var_ [LINKS ONCE].as < bool > ()) res << LINKS ONCE "\n";
    if (var_ [LINKS DONT ONCE].as < bool > ()) res << LINKS DONT ONCE "\n";
    if (var_.count (LINKS REPORT)) { res << LINKS REPORT ": "; pvs (res, var_ [LINKS REPORT].as < vstr_t > ()); res << "\n"; }
    if (var_ [LINKS REVOKE].as < bool > ()) res << LINKS REVOKE "\n";
    if (var_ [LINKS DONT REVOKE].as < bool > ()) res << LINKS DONT REVOKE "\n";
    if (var_ [LINKS XLINK].as < bool > ()) res << LINKS XLINK "\n";
    if (var_ [LINKS DONT XLINK].as < bool > ()) res << LINKS DONT XLINK "\n";

    if (var_.count (MATH CORE)) res << MATH CORE ": " << var_ [MATH CORE].as < bool > () << "\n";
    if (var_.count (MATH DRAFT)) res << MATH DRAFT ": " << var_ [MATH DRAFT].as < int > () << "\n";
    if (var_.count (MATH VERSION)) res << MATH VERSION ": " << var_ [MATH VERSION].as < int > () << "\n";

    if (var_ [MICRODATA EXPORT].as < bool > ()) res << MICRODATA EXPORT "\n";
    if (var_ [MICRODATA DONT EXPORT].as < bool > ()) res << MICRODATA DONT EXPORT "\n";
    if (var_ [MICRODATA VERIFY].as < bool > ()) res << MICRODATA VERIFY "\n";
    if (var_ [MICRODATA DONT VERIFY].as < bool > ()) res << MICRODATA DONT VERIFY "\n";
    if (var_.count (MICRODATA ROOT)) res << MICRODATA ROOT ": " << var_ [MICRODATA ROOT].as < ::std::string > () << "\n";
    if (var_.count (MICRODATA VIRTUAL)) { res << MICRODATA VIRTUAL ": "; pvs (res, var_ [MICRODATA VIRTUAL].as < vstr_t > ()); res << "\n"; }

    if (var_.count (NITS CATASTROPHE)) { res << NITS CATASTROPHE ": "; pvs (res, var_ [NITS CATASTROPHE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS COMMENT)) { res << NITS COMMENT ": "; pvs (res, var_ [NITS COMMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS DBG)) { res << NITS DBG ": "; pvs (res, var_ [NITS DBG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS ERR)) { res << NITS ERR ": "; pvs (res, var_ [NITS ERR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS FORMAT)) res << NITS FORMAT ": " << var_ [NITS FORMAT].as < ::std::string > () << "\n";
    if (var_.count (NITS INFO)) { res << NITS INFO ": "; pvs (res, var_ [NITS INFO].as < vstr_t > ()); res << "\n"; }
    if (var_ [NITS NIDS].as < bool > ()) res << NITS NIDS "\n";
    if (var_ [NITS DONT NIDS].as < bool > ()) res << NITS DONT NIDS "\n";
    if (var_.count (NITS OVERRIDE)) res << NITS OVERRIDE ": " << var_ [NITS OVERRIDE].as < ::std::string > () << "\n";
    if (var_.count (NITS SILENCE)) { res << NITS SILENCE ": "; pvs (res, var_ [NITS SILENCE].as < vstr_t > ()); res << "\n"; }
    if (var_ [NITS SPEC].as < bool > ()) res << NITS SPEC "\n";
    if (var_ [NITS DONT SPEC].as < bool > ()) res << NITS DONT SPEC "\n";
    if (var_ [NITS UNIQUE].as < bool > ()) res << NITS UNIQUE "\n";
    if (var_ [NITS DONT UNIQUE].as < bool > ()) res << NITS DONT UNIQUE "\n";
    if (var_.count (NITS WARNING)) { res << NITS WARNING ": "; pvs (res, var_ [NITS WARNING].as < vstr_t > ()); res << "\n"; }
    if (var_ [NITS WATCH].as < bool > ()) res << NITS WATCH "\n";
    if (var_ [NITS DONT WATCH].as < bool > ()) res << NITS DONT WATCH "\n";

    if (var_ [MF EXPORT].as < bool > ()) res << MF EXPORT "\n";
    if (var_ [MF DONT EXPORT].as < bool > ()) res << MF DONT EXPORT "\n";
    if (var_ [MF VERIFY].as < bool > ()) res << MF VERIFY "\n";
    if (var_ [MF DONT VERIFY].as < bool > ()) res << MF DONT VERIFY "\n";
    if (var_.count (MF VERSION)) res << MF VERSION ": " << var_ [MF VERSION].as < int > () << "\n";

    if (var_.count (RDFA DC)) res << RDFA DC ": " << var_ [RDFA DC].as < int > () <<  "\n";
    if (var_.count (RDFA FOAF)) res << RDFA FOAF ": " << var_ [RDFA FOAF].as < int > () <<  "\n";
    if (var_.count (RDFA VERSION)) res << RDFA VERSION ": " << var_ [RDFA VERSION].as < ::std::string > () <<  "\n";
    if (var_.count (RDFA XSD)) res << RDFA XSD ": " << var_ [RDFA XSD].as < int > () <<  "\n";

    if (var_.count (ONTOLOGY LIST)) res << ONTOLOGY LIST ": " << var_ [ONTOLOGY LIST].as < bool > () << "\n";

    for (int i = s_none + 1; i < s_error; ++i)
    {   const e_schema es = static_cast < e_schema > (i);
        if (is_faux_schema (es)) continue;
        if (get_schema_version_count (es) < 2) continue;
        const ::std::string naam (schema_names.get (es, SCHEMA_NAME));
        ::std::string arg (ONTOLOGY);
        arg += naam;
        if (var_.count (arg))
            res << arg << ": " << var_ [arg].as < ::std::string > () << "\n"; }

    if (var_ [SHADOW CHANGED].as < bool > ()) res << SHADOW CHANGED "\n";
    if (var_ [SHADOW DONT CHANGED].as < bool > ()) res << SHADOW DONT CHANGED "\n";
    if (var_ [SHADOW COMMENT].as < bool > ()) res << SHADOW COMMENT "\n";
    if (var_ [SHADOW DONT COMMENT].as < bool > ()) res << SHADOW DONT COMMENT "\n";
    if (var_.count (SHADOW COPY)) res << SHADOW COPY ": " << var_ [SHADOW COPY].as < ::std::string > () << "\n";
    if (var_ [SHADOW ENABLE].as < bool > ()) res << SHADOW ENABLE "\n";
    if (var_ [SHADOW DONT ENABLE].as < bool > ()) res << SHADOW DONT ENABLE "\n";
    if (var_.count (SHADOW FICHIER)) res << SHADOW FICHIER ": " << var_ [SHADOW FICHIER].as < ::std::string > () << "\n";
    if (var_.count (SHADOW IGNORED)) { res << SHADOW IGNORED ": "; pvs (res, var_ [SHADOW IGNORED].as < vstr_t > ()); res << "\n"; }
    if (var_ [SHADOW INFO].as < bool > ()) res << SHADOW INFO "\n";
    if (var_ [SHADOW DONT INFO].as < bool > ()) res << SHADOW DONT INFO "\n";
    if (var_.count (SHADOW MSG)) res << SHADOW MSG ": " << var_ [SHADOW MSG].as < ::std::string > () << "\n";
    if (var_.count (SHADOW ROOT)) res << SHADOW ROOT ": " << var_ [SHADOW ROOT].as < ::std::string > () << "\n";
    if (var_ [SHADOW SPACING].as < bool > ()) res << SHADOW SPACING "\n";
    if (var_ [SHADOW DONT SPACING].as < bool > ()) res << SHADOW DONT SPACING "\n";
    if (var_ [SHADOW SSI].as < bool > ()) res << SHADOW SSI "\n";
    if (var_ [SHADOW DONT SSI].as < bool > ()) res << SHADOW DONT SSI "\n";
    if (var_ [SHADOW UPDATE].as < bool > ()) res << SHADOW UPDATE "\n";
    if (var_ [SHADOW DONT UPDATE].as < bool > ()) res << SHADOW DONT UPDATE "\n";
    if (var_.count (SHADOW VIRTUAL)) { res << SHADOW VIRTUAL ": "; pvs (res, var_ [SHADOW VIRTUAL].as < vstr_t > ()); res << "\n"; }

    if (var_.count (WEBSITE EXTENSION)) { res << WEBSITE EXTENSION ": "; pvs (res, var_ [WEBSITE EXTENSION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WEBSITE INDEX)) res << WEBSITE INDEX ": " << var_ [WEBSITE INDEX].as < ::std::string > () << "\n";
    if (var_.count (WEBSITE SITE)) { res << WEBSITE SITE ": "; pvs (res, var_ [WEBSITE SITE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WEBSITE ROOT)) res << WEBSITE ROOT ": " << var_ [WEBSITE ROOT].as < ::std::string > () << "\n";
    if (var_.count (WEBSITE VIRTUAL)) { res << WEBSITE VIRTUAL ": "; pvs (res, var_ [WEBSITE VIRTUAL].as < vstr_t > ()); res << "\n"; }

#ifndef NOSPELL
    if (var_.count (SPELL ACCEPT)) { res << SPELL ACCEPT ": "; pvs (res, var_ [SPELL ACCEPT].as < vstr_t > ()); res << "\n"; }
    if (var_ [SPELL CASED].as < bool > ()) res << SPELL CASED "\n";
    if (var_ [SPELL DONT CASED].as < bool > ()) res << SPELL DONT CASED "\n";
    if (var_ [SPELL CHECK].as < bool > ()) res << SPELL CHECK "\n";
    if (var_ [SPELL DONT CHECK].as < bool > ()) res << SPELL DONT CHECK "\n";
    if (var_.count (SPELL DICT)) { res << SPELL DICT ": "; pvs (res, var_ [SPELL DICT].as < vstr_t > ()); res << "\n"; }
    if (var_ [SPELL ICU].as < bool > ()) res << SPELL ICU "\n";
    if (var_ [SPELL DONT ICU].as < bool > ()) res << SPELL DONT ICU "\n";
    if (var_.count (SPELL LIST)) { res << SPELL LIST ": "; pvs (res, var_ [SPELL LIST].as < vstr_t > ()); res << "\n"; }
    if (var_.count (SPELL PATH)) res << SPELL PATH ": " << var_ [SPELL PATH].as < ::std::string > () << "\n";
#endif // NOSPELL

    if (var_.count (STATS EXPORT)) res << STATS EXPORT ": " << var_ [STATS EXPORT].as < ::std::string > () << "\n";
    if (var_ [STATS META].as < bool > ()) res << STATS META "\n";
    if (var_ [STATS DONT META].as < bool > ()) res << STATS DONT META "\n";
    if (var_ [STATS PAGE].as < bool > ()) res << STATS PAGE "\n";
    if (var_ [STATS DONT PAGE].as < bool > ()) res << STATS DONT PAGE "\n";
    if (var_ [STATS SUMMARY].as < bool > ()) res << STATS SUMMARY "\n";
    if (var_ [STATS DONT SUMMARY].as < bool > ()) res << STATS DONT SUMMARY "\n";

    if (var_.count (SVG VERSION)) res << SVG VERSION ": " << var_ [SVG VERSION].as < ::std::string > () << "\n";

    if (var_.count (VALIDATION ATTRIB)) { res << VALIDATION ATTRIB ": "; pvs (res, var_ [VALIDATION ATTRIB].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION CHARSET)) { res << VALIDATION CHARSET ": "; pvs (res, var_ [VALIDATION CHARSET].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION CLASS)) { res << VALIDATION CLASS ": "; pvs (res, var_ [VALIDATION CLASS].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION COLOR)) { res << VALIDATION COLOUR ": "; pvs (res, var_ [VALIDATION COLOR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION COLOUR)) { res << VALIDATION COLOUR ": "; pvs (res, var_ [VALIDATION COLOUR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION COUNTRY)) { res << VALIDATION COUNTRY ": "; pvs (res, var_ [VALIDATION COUNTRY].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION CURRENCY)) { res << VALIDATION CURRENCY ": "; pvs (res, var_ [VALIDATION CURRENCY].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION DINGBATARG)) { res << VALIDATION DINGBATARG ": "; pvs (res, var_ [VALIDATION DINGBATARG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION ELEMENT)) { res << VALIDATION ELEMENT ": "; pvs (res, var_ [VALIDATION ELEMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION ELEMATTR)) { res << VALIDATION ELEMATTR ": "; pvs (res, var_ [VALIDATION ELEMATTR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION HTTPEQUIV)) { res << VALIDATION HTTPEQUIV ": "; pvs (res, var_ [VALIDATION HTTPEQUIV].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION LANG)) { res << VALIDATION LANG ": "; pvs (res, var_ [VALIDATION LANG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION MINOR)) res << VALIDATION MINOR ": " << var_ [VALIDATION MINOR].as < int > () << "\n";
    if (var_.count (VALIDATION METANAME)) { res << VALIDATION METANAME ": "; pvs (res, var_ [VALIDATION MIMETYPE].as < vstr_t > ()); res << "\n"; }
    if (var_ [VALIDATION MICRODATAARG].as < bool > ()) res << VALIDATION MICRODATAARG "\n";
    if (var_ [VALIDATION DONT MICRODATAARG].as < bool > ()) res << VALIDATION DONT MICRODATAARG "\n";
    if (var_.count (VALIDATION MIMETYPE)) { res << VALIDATION MIMETYPE ": "; pvs (res, var_ [VALIDATION METANAME].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION REL)) { res << VALIDATION REL ": "; pvs (res, var_ [VALIDATION REL].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION SGML)) { res << VALIDATION SGML ": "; pvs (res, var_ [VALIDATION SGML].as < vstr_t > ()); res << "\n"; }

#define RPT_VAR(XX) if (var_.count (VALIDATION #XX)) { res << VALIDATION #XX ": "; pvs (res, var_ [VALIDATION #XX].as < vstr_t > ()); res << "\n"; }
    RPT_VAR (accrual_method);
    RPT_VAR (accrual_periodicity);
    RPT_VAR (accrual_policy);
    RPT_VAR (action);
    RPT_VAR (align3);
    RPT_VAR (alignplus);
    RPT_VAR (as);
    RPT_VAR (as_units);
    RPT_VAR (autocapitalise);
    RPT_VAR (autocomplete);
    RPT_VAR (baselineshift);
    RPT_VAR (beginfn);
    RPT_VAR (citype);
    RPT_VAR (cntype);
    RPT_VAR (composite_operator);
    RPT_VAR (dcmitype);
    RPT_VAR (decalign);
    RPT_VAR (dingbat);
    RPT_VAR (dir);
    RPT_VAR (display_align);
    RPT_VAR (dominantbaseline);
    RPT_VAR (enterkeyhint);
    RPT_VAR (figalign);
    RPT_VAR (fontname);
    RPT_VAR (halign);
    RPT_VAR (icc);
    RPT_VAR (inputmode);
    RPT_VAR (inputplus);
    RPT_VAR (inputtype);
    RPT_VAR (inputtype3);
    RPT_VAR (inputtype32);
    RPT_VAR (inputtype4);
    RPT_VAR (inputtype5);
    RPT_VAR (kind);
    RPT_VAR (linebreak);
    RPT_VAR (listtype);
    RPT_VAR (mah);
    RPT_VAR (mathalign);
    RPT_VAR (mathvariant);
    RPT_VAR (matrixtype);
    RPT_VAR (media);
    RPT_VAR (mediafeature);
    RPT_VAR (mediakeyword);
    RPT_VAR (method);
    RPT_VAR (mf_identifier);
    RPT_VAR (mf_itemtype);
    RPT_VAR (mf_listing_action);
    RPT_VAR (mf_method);
    RPT_VAR (mf_reviewtype);
    RPT_VAR (namedspace);
    RPT_VAR (namespace);
    RPT_VAR (mathnotation);
    RPT_VAR (ogtype);
    RPT_VAR (paintkeyword);
    RPT_VAR (plusstyle);
    RPT_VAR (pointer_events);
    RPT_VAR (print);
    RPT_VAR (referrer);
    RPT_VAR (rendering_in_tents);
    RPT_VAR (rules);
    RPT_VAR (sandbox);
    RPT_VAR (schema);
    RPT_VAR (shape7);
    RPT_VAR (shape_rendering);
    RPT_VAR (ssi);
    RPT_VAR (ssi_comparison);
    RPT_VAR (ssi_encoding);
    RPT_VAR (ssi_env);
    RPT_VAR (svg_align);
    RPT_VAR (svg_display);
    RPT_VAR (svg_feature);
    RPT_VAR (svg_fontstretch);
    RPT_VAR (svg_fontstretch_ff);
    RPT_VAR (svg_fontstyle);
    RPT_VAR (svg_fontweight);
    RPT_VAR (svg_fontweight_ff);
    RPT_VAR (svg_mode);
    RPT_VAR (svg_overflow);
    RPT_VAR (svg_version);
    RPT_VAR (svg_version_grand);
    RPT_VAR (tableframe);
    RPT_VAR (text_decoration);
    RPT_VAR (text_rendering);
    RPT_VAR (transform_anim);
    RPT_VAR (transform_fn);
    RPT_VAR (turbulence_type);
    RPT_VAR (unicode_bidi);
    RPT_VAR (vector_effect_2);
    RPT_VAR (xmlns);
#undef RPT_VAR

    return res.str (); }
