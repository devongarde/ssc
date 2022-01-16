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
#include "main/context.h"
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

#define TYPE_HELP "Type '" PROG " -h' for help."

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
            PROG " is an opinionated HTML nit-picker. It notes broken links, dubious syntax, bad semantics,\n"
            "odd ontology, etc.. It highlights legal but untidy code.\n";
    ::std::ostringstream waste_of_space;
    waste_of_space << aid;
    res +=  waste_of_space.str ();
    res +=  "\n\n"
            "Configuration file section names precede each switch dot above (e.g. " GENERAL_ ", " LINKS_ ",\n"
            WEBSITE_ ", etc.). Option names follow them. For example:\n\n"
            "[" GENERAL_ "]\n"
            VERBOSE "=2\n\n"
            "[" LINKS_ "]\n"
            CHECK "=1\n\n"
            "[" WEBSITE_ "]\n"
            EXTENSION "=html\n"
            INDEX "=index.shtml\n"
            SITE "=" DEFAULT_DOMAIN "\n\n";
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
        if ((s.length () == 1) && (s.at (0) >= '0') && (s.at (0) <= '9'))
            sev = static_cast < e_severity > (s.at (0) - '0');
    if (sev == es_undefined)
        nits.pick (nit_configuration, es_error, ec_init, "invalid severity");
    return sev; }

bool onoff (nitpick& nits, const ::std::string& ss)
{   if (ss.empty ()) return true;
    ::std::string s (trim_the_lot_off (ss));
    if (s.empty ()) return true;
    switch (s.at (0))
    {   case '0' :
            return false;
        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
        case '8' :
        case '9' :
            return true;
        case 'b' :
            if (compare_no_case (s, "bu")) return false;
            break;
        case 'f' :
            if (compare_no_case (s, "false")) return false;
            if (compare_no_case (s, "f")) return false;
            break;
        case 'j' :
            if (compare_no_case (s, "ja")) return false;
            if (compare_no_case (s, "j")) return false;
            break;
        case 'n' :
            if (compare_no_case (s, "no")) return false;
            if (compare_no_case (s, "n")) return false;
            if (compare_no_case (s, "non")) return false;
            if (compare_no_case (s, "nee")) return false;
            if (compare_no_case (s, "nein")) return false;
            break;
        case 'o' :
            if (compare_no_case (s, "off")) return false;
            if (compare_no_case (s, "on")) return true;
            if (compare_no_case (s, "oui")) return true;
            break;
        case 's' :
            if (compare_no_case (s, "si")) return true;
            break;
        case 't' :
            if (compare_no_case (s, "true")) return true;
            if (compare_no_case (s, "t")) return true;
            break;
        case 'y' :
            if (compare_no_case (s, "yes")) return true;
            if (compare_no_case (s, "y")) return true;
            break;
        default :
            break; }
    nits.pick (nit_configuration, es_error, ec_init, PROG " does not recognise ", quote (s));
    return true; }

void options::process (nitpick& nits, int argc, char* const * argv)
{   /*  a
        b
        c persist file   C clear webmention
        d dump corpus    D dump progress
        e external check E severity error exit
        f config         F load config file from .ssc/config
        g website root
        h help           H html snippet
        i index file     I server side includes
        j
        k
        l link check     L virtual directory
        m microdata      M microformat
        n what if        N notify webmention
        o output         O rpt ext once
        p prog dir       P nit output format
        q
        r no revoke chks R reset webmention
        s domain name    S stats
        t template       T test mode
        u update         U unique
        v verbose        V version
        w webmention     W cgi
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
        (DEFCONF ",F", "Load configuration from " CONFIGURATION ".")
        (HELP ",h", "Output this information and exit.")
        (HTML SNIPPET ",H", ::boost::program_options::value < ::std::string > (), "Only nitpick the given snippet of HTML.")
        (ONTOLOGY LIST, "List known ontology schema for microdata and/or RDFa, then exit.")
        (VALIDATION_, "List attribute types that can be given additional valid values, then exit.")
        (VERSION ",V", "Display version and copyright gen, then exit.")
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
        (GENERAL CGI ",W", ::boost::program_options::value < ::std::string > (), "Process OpenBSD httpd <FORM METHOD=GET ...> (incompatible with " GENERAL WEBMENTION ").")
        (GENERAL CLASS, ::boost::program_options::value < ::std::string > (), "Report unrecognised classes.")
        (GENERAL FICHIER ",c", ::boost::program_options::value < ::std::string > () -> default_value (PROG EXT), "File for persistent data, requires -N (note " GENERAL DATAPATH ").")
        (GENERAL MACROSTART, ::boost::program_options::value < ::std::string > () -> default_value ("{{"), "Start of template macro (by default, the '{{' in '{{macro}}').")
        (GENERAL MACROEND, ::boost::program_options::value < ::std::string > () -> default_value ("}}"), "End of template macro (by default, the '}}' in '{{macro}}').")
        (GENERAL RPT, ::boost::program_options::value < ::std::string > (), "Report when CSS files opened.")
        (GENERAL TEST ",T", ::boost::program_options::value < ::std::string > (), "Output format for automated tests.")
        (GENERAL USER, ::boost::program_options::value < ::std::string > () -> default_value ("scroggins"), "User name to supply when requested (for webmentions).")
        (GENERAL WEBMENTION, ::boost::program_options::value < ::std::string > (), "Process webmentions (experimental, incompatible with " GENERAL CGI ").")
        (JSONLD EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "Extension for JSON-LD files; may be repeated.")
        (JSONLD VERIFY, ::boost::program_options::value < ::std::string > (), "Verify JSON-LD.")
        (JSONLD VERSION, ::boost::program_options::value < ::std::string > (), "Presume this version of JSON-LD (1.0 or 1.1, default 1.0).")
        (MICRODATA MICRODATAARG, ::boost::program_options::value < ::std::string > (), "Check microdata (" PROG " only understands certain microdata schemas).")
        (NITS OVERRIDE ",P", ::boost::program_options::value < ::std::string > (), "Output nits in this format (overrides " NITS FORMAT ".")
        (NITS SPEC ",Z", ::boost::program_options::value < ::std::string > (), "Output nit codes, not numbers, in tests (scc-test rejects this format).")
        (NITS WATCH, ::boost::program_options::value < ::std::string > (), "Output debug nits, which you'll need to manage particular error messages.")
        (WMIN TEST_HEADER, ::boost::program_options::value < ::std::string > (), "Use this file to test header parsing code.")
        (WMIN DATAPATH, ::boost::program_options::value < ::std::string > () -> default_value (MENTION), "Path for incoming web mention data files (note " GENERAL DATAPATH ").") // not yet noted below
        (WMIN HOOK, ::boost::program_options::value < ::std::string > (), "Process incoming " WEBMENTION ", in JSON format, in specified file.")
        (WMIN STUB, ::boost::program_options::value < ::std::string > () -> default_value ("_" PROG), "Mask for file containing " WEBMENTION " HTML snippet.")
        (WMIN WRITE , ::boost::program_options::value < ::std::string > (), "When writing " WEBMENTION " includes, write them to this path (default: site.root).")
        (WMIN MENTION, ::boost::program_options::value < vstr_t > () -> composing (), "A " WEBMENTION ", string must be source=url,target=url; may be repeated.")
        (WMIN TEMPLATE ",t", ::boost::program_options::value < vstr_t > () -> composing (), "HTML snippets for adding mentions (new, changed, deleted, unchanged, unknown); may be repeated.")
        (WMOUT CLEAR ",C", ::boost::program_options::value < ::std::string > (), "Clear out all web mention data.")
        (WMOUT NOTIFY ",N", ::boost::program_options::value < ::std::string > (), "Notify appropriate servers of web mention updates.")
        (WMOUT RESET ",R", ::boost::program_options::value < ::std::string > (), "Reset web mention data.")
        (WMOUT SECRET, ::boost::program_options::value < ::std::string > (), WEBMENTION " secret.")
        ;
    primary.add_options ()
        (GENERAL CSS_OPTION, ::boost::program_options::value < ::std::string > (), "Process .css files.")
        (GENERAL CUSTOM, ::boost::program_options::value < vstr_t > () -> composing (), "Define a custom element for checking the 'is' attribute; may be repeated.")
        (GENERAL DATAPATH ",p", ::boost::program_options::value < ::std::string > () -> default_value ("." PROG), "Root directory for all " PROG " files.")
        (GENERAL ERR ",E", ::boost::program_options::value < ::std::string > () -> composing (), "Exit with an error if nits of this severity or worse are generated. Values: '"
            CATASTROPHE "', '" ERR "' (default), '" WARNING "', '" INFO  "', or '" COMMENT  "'.")
        (GENERAL IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore attributes and content of specified element; may be repeated.")
        (GENERAL LANG, ::boost::program_options::value < ::std::string > () -> composing (), "Default language (such as 'en_GB', 'lb_LU', etc.).")
        (GENERAL MAXFILESIZE, ::boost::program_options::value < int > (), "Maximum file size to read, in megabytes (zero for no limit).")
        (GENERAL NOCHANGE ",n", ::boost::program_options::value < ::std::string > (), "Report what " PROG "will do, but do not do it.")
        (GENERAL OUTPUT ",o", ::boost::program_options::value < ::std::string > (), "Output file (default to the console).")
        (GENERAL PROGRESS ",D", ::boost::program_options::value < ::std::string > (), "Dump progress to standard output.")
        (GENERAL RDFA_, ::boost::program_options::value < ::std::string > (), "Check RDFa attributes.")
        (GENERAL REL, ::boost::program_options::value < ::std::string > (), "Ignore recognised but non-standard <LINK> REL values.")
        (GENERAL SLOB, ::boost::program_options::value < ::std::string > (), "Do not nitpick untidy HTML such as missing closures.")
        (GENERAL SSI ",I", ::boost::program_options::value < ::std::string > (), "Process (simple) Server Side Includes.")
        (GENERAL VERBOSE ",v", ::boost::program_options::value < ::std::string > (), "Output these nits and worse. Values: '"
            CATASTROPHE "', '" ERR "', '" WARNING "' (default), '" INFO  "', '" COMMENT  "', or 0 for silence.")

        (CORPUS ARTICLE, ::boost::program_options::value < ::std::string > (), "Prefer the content of <ARTICLE> when gather page corpus.")
        (CORPUS BODY, ::boost::program_options::value < ::std::string > (), "Prefer the content of <BODY> when gather page corpus.")
        (CORPUS MAIN, ::boost::program_options::value < ::std::string > (), "Prefer the content of <MAIN> when gather page corpus.")
        (CORPUS OUTPUT ",d", ::boost::program_options::value < ::std::string > (), "Dump corpus of site content to specified file.")

        (HTML RFC1867, ::boost::program_options::value < ::std::string > (), "Consider RFC 1867 (INPUT=FILE) when processing HTML 2.0.")
        (HTML RFC1942, ::boost::program_options::value < ::std::string > (), "Consider RFC 1867 RFC 1942 (tables) when processing HTML 2.0.")
        (HTML RFC1980, ::boost::program_options::value < ::std::string > (), "Consider RFC 1867 RFC 1980 (client side image maps) when processing HTML 2.0.")
        (HTML RFC2070, ::boost::program_options::value < ::std::string > (), "Consider RFC 1867 RFC 2070 (internationalisation) when processing HTML 2.0.")
        (HTML TAGS, ::boost::program_options::value < ::std::string > (), "Presume HTML files with no DOCTYPE declaration are HTML Tags (CERN version), not HTML 1.0.")
        (HTML TITLE ",z", ::boost::program_options::value < int > () -> default_value (MAX_IDEAL_TITLE_LENGTH), "Maximum advisable length of <TITLE> text.")
        (HTML VERSION, ::boost::program_options::value < ::std::string > (),
            "Set the specific version of HTML with DOCTYPE (default '5.2'), or if no DOCTYPE found (default: '1.0'). "
            "For specific WhatWG living standard, give date (e.g. '2021/4/1'). "
            "For XHTML, use XHTML plus version, e.g. 'XHTML 1.0'. "
            "For HTML+, use '+'. For HTML tags, use 'tags'.")

        (LINKS EXTERNAL ",e", ::boost::program_options::value < ::std::string > (), "Check external links (requires curl, sets " LINKS CHECK ").")
        (LINKS FORWARD ",3", ::boost::program_options::value < ::std::string > (), "Report http forwarding errors, e.g. 301 and 308 (sets " LINKS EXTERNAL ").")
        (LINKS CHECK ",l", ::boost::program_options::value < ::std::string > (), "Check internal links.")
        (LINKS ONCE ",O", ::boost::program_options::value < ::std::string > (), "Report each broken external link once (sets " LINKS EXTERNAL ").")
        (LINKS REVOKE ",r", ::boost::program_options::value < ::std::string > (), "Do not check whether https certificates have been revoked (sets " LINKS EXTERNAL ").")
        (LINKS XLINK ",X", ::boost::program_options::value < ::std::string > (), "Check crosslink IDs.")

        (MF VERIFY ",M", ::boost::program_options::value < ::std::string > (), "Check microformats in class and rel attributes (see https://" MICROFORMATS_ORG "/).")
        (MF VERSION, ::boost::program_options::value < int > () -> default_value (3), "Check this version of microformats (1, 2, or 3 for both).")
        (MF EXPORT, ::boost::program_options::value < ::std::string > (), "Export microformat data (requires " MF VERIFY ").")

        (MATH VERSION, ::boost::program_options::value < int > () -> default_value (0), "preferred version of MathML (default (0): determine by HTML version).")

        (MICRODATA EXPORT, ::boost::program_options::value < ::std::string > (), "Export microformat data (only verified data if " MICRODATA MICRODATAARG " is set).")
        (MICRODATA VERIFY ",m", ::boost::program_options::value < ::std::string > (), "Check microdata (" PROG " only understands certain microdata schemas).")
        (MICRODATA ROOT, ::boost::program_options::value < ::std::string > (), "Microdata export root directory (requires " MICRODATA EXPORT ").")
        (MICRODATA VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "Export virtual directory, syntax virtual=directory. Must correspond to " WEBSITE VIRTUAL ".")

        (NITS CATASTROPHE, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a catastrophe; may be repeated.")
        (NITS CODES, ::boost::program_options::value < ::std::string > (), "Output nit codes")
        (NITS COMMENT, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a comment; may be repeated.")
        (NITS DBG, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a debug message; may be repeated.")
        (NITS ERR, ::boost::program_options::value < vstr_t > () -> composing (), "redefiRedefinene nit as an error; may be repeated.")
        (NITS FORMAT, ::boost::program_options::value < ::std::string > (), "Output nits in this format (\"html\" or \"text\", default text).")
        (NITS INFO, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as info; may be repeated.")
        (NITS NIDS, ::boost::program_options::value < ::std::string > (), "Output nit identifiers (used to recategorise nits)")
        (NITS ROOT, ::boost::program_options::value < ::std::string > (), "Do not search for configuration files in " WEBSITE ROOT " unless explicitly specified.")
        (NITS QUOTE, ::boost::program_options::value < ::std::string > (), "Output nits in this format (\"html\" or \"text\", default text).")
        (NITS SILENCE, ::boost::program_options::value < vstr_t > () -> composing (), "Silence nit; may be repeated.")
        (NITS UNIQUE ",U", ::boost::program_options::value < ::std::string > (), "Do not report repeated nits, even if they give more information")
        (NITS WARNING, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine specified nit as a warning; may be repeated.")

        (RDFA VERSION, ::boost::program_options::value < ::std::string > () -> default_value ("1.1.3"), "version of RDFa (default 1.1.3).")

        (SHADOW CHANGED, ::boost::program_options::value < ::std::string > (),    "Only "
#ifndef NOLYNX
                            "link/"
#endif // NOLYNX
                            "copy shadow files when the target doesn't exist, or is older than the original.")
        (SHADOW COMMENT, ::boost::program_options::value < ::std::string > (), "Do NOT remove comments from shadow pages.")
        (SHADOW COPY, ::boost::program_options::value < ::std::string > (),  "Copy site: 'no' (default), "
#ifndef NOLYNX
                                                                    "'hard' (links), 'soft' (links), "
#endif // NOLYNX
                                                                    "'pages', 'all', 'dedu' (deduplicate), 'report'.")
        (SHADOW FICHIER, ::boost::program_options::value < ::std::string > (), "Where to persist deduplication and update data.")
        (SHADOW ENABLE, ::boost::program_options::value < ::std::string > (), "Enable shadowing (set by all other SHADOW options)")
        (SHADOW IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore files with this extension; may be repeated.")
        (SHADOW INFO, ::boost::program_options::value < ::std::string > (), "Insert the generation time in a comment at the top of shadowed pages (after " SHADOW MSG ").")
        (SHADOW MSG, ::boost::program_options::value < ::std::string > (), "Insert this text in a comment at the top of shadowed pages.")
        (SHADOW ROOT, ::boost::program_options::value < ::std::string > (), "Shadow output root directory.")
        (SHADOW SSI, ::boost::program_options::value < ::std::string > (), "Resolve SSIs on shadow pages when " GENERAL SSI " is set.")
        (SHADOW SPACING, ::boost::program_options::value < ::std::string > (), "Merge whitespace on shadow pages. Without this option, nit line-numbers may not match shadow pages.")
        (SHADOW UPDATE, ::boost::program_options::value < ::std::string > (), "Only examine changed pages, or pages with changed dependencies (requires " SHADOW FICHIER ")")
        (SHADOW VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "Shadow virtual directory, syntax virtual=shadow; must correspond to " WEBSITE VIRTUAL "; may be repeated.")

        (SPELL ACCEPT, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore word when reporting spelling errors; may be repeated.")
        (SPELL CHECK, ::boost::program_options::value < ::std::string > (), "Check spelling (see also " GENERAL LANG ").")
#ifdef GENNIX
        (SPELL DICT, ::boost::program_options::value < vstr_t > () -> composing (), "LANG,DICT: associate (hunspell) dictionary with language, e.g. 'en-US,en_US-large'; may be repeated.")
#endif // GENNIX
        (SPELL LIST, ::boost::program_options::value < vstr_t > () -> composing (), "X,Y: File X contains valid spellings for language Y, one per line; may be repeated")
#ifdef GENNIX
        (SPELL PATH, ::boost::program_options::value < ::std::string > (), "Path to (hunspell) dictionaries.")
#endif // GENNIX

        (WEBSITE ROOT ",g", ::boost::program_options::value < ::std::string > (), "Website root directory (default: current directory).")
        (WEBSITE EXTENSION ",x", ::boost::program_options::value < vstr_t > () -> composing (), "Check files with this extension (default html); may be repeated.")
        (WEBSITE INDEX ",i", ::boost::program_options::value < ::std::string > (), "Index file in directories (default: none).")
        (WEBSITE SITE ",s", ::boost::program_options::value < vstr_t > () -> composing (), "Domain name(s) for local site (default none); may be repeated.")
        (WEBSITE VIRTUAL ",L", ::boost::program_options::value < vstr_t > () -> composing (), "Define virtual directory, arg syntax virtual=physical; may be repeated.")

        (STATS EXPORT, ::boost::program_options::value < ::std::string > (), "Export collected statistical data.")
        (STATS META, ::boost::program_options::value < ::std::string > (), "Report on <META> data.")
        (STATS PAGE, ::boost::program_options::value < ::std::string > (), "Report individual page statistics.")
        (STATS SUMMARY ",S", ::boost::program_options::value < ::std::string > (), "Report overall statistics.")

        (SVG VERSION, ::boost::program_options::value < ::std::string > (), "Presumed this version of SVG if version attribute missing (requires HTML 4 or greater).")

        (VALIDATION MINOR ",m", ::boost::program_options::value < int > (), "Validate HTML 5 with this w3 minor version (e.g. 3 for HTML 5.3).")
        (VALIDATION MICRODATAARG, ::boost::program_options::value < ::std::string > (), "Validate HTML5 microdata.")
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
        ontology.add_options ()
            (arg.c_str (), ::boost::program_options::value < ::std::string > (), desc.c_str ()); }

    valid.add_options ()
        (VALIDATION ATTRIB, ::boost::program_options::value < vstr_t > () -> composing (), "Add a custom attribute (name namespace flags ext).")
        (VALIDATION CHARSET, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid charset.")
        (VALIDATION CLASS, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid class.")
        (VALIDATION COLOUR, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid colour.")
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

    try
    {   ::boost::program_options::store (::boost::program_options::parse_environment (env, ::boost::function1 < ::std::string, ::std::string> (env_mapper)), env_);
        if (env_.count (ENV_ARGS))
        {   ::std::string e (env_ [ENV_ARGS].as < ::std::string > ());
            vstr_t env_args (split_by_space (e));
            if (! env_args.empty ())
            {   context.macros ().emplace (nm_run_environment, e);
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
        {   context.cgi (true);
            context.macros ().emplace (nm_query, qu);
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
    if (var_.count (CONFIG) || var_.count (DEFCONF) || env_.count (ENV_CONFIG))
    {   ::boost::filesystem::path file (CONFIGURATION);
        if (var_.count (CONFIG)) file = var_ [CONFIG].as < ::std::string > ();
        else if ((var_.count (DEFCONF) == 0) && env_.count (ENV_CONFIG)) file = env_ [ENV_CONFIG].as < ::std::string > ();
        context.macros ().emplace (nm_config, file.string ());
        if (file_exists (file))
        {   nits.pick (nit_configuration, es_comment, ec_init, ::std::string ("Loading configuration ") + file.string () + "...");
            context.config (canonical (file)); }
        else
        {   nits.pick (nit_configuration, es_error, ec_init, ::std::string ("Cannot find ") + file.string ());
            return; }
        try
#ifdef  NO_PCF_STR
        {   ::std::ifstream fis (file.string ().c_str ());
            ::boost::program_options::store (::boost::program_options::parse_config_file (fis, config, true), var_); }
#else
        {   ::boost::program_options::store (::boost::program_options::parse_config_file (file.string ().c_str (), config, true), var_); }
#endif
        catch (const ::boost::program_options::error& err)
        {   nits.pick (nit_configuration, es_error, ec_init, err.what (), " in ", file.string ());
            return; }
        catch (...)
        {   nits.pick (nit_configuration, es_error, ec_init, "Exception when processing ", file.string ());
            return; } }
    ::boost::program_options::notify (var_);
    if (var_.count (VERSION))
    {   context.todo (do_simple);
        return; }
    if (var_.count (HELP))
    {   help (aid);
        return; }
    if (var_.count (VALIDATION_))
    {   ::std::ostringstream waste_of_space;
        waste_of_space << valid;
        context.domsg (waste_of_space.str ());
        context.todo (do_simple);
        return; }
    if (var_.count (ONTOLOGY LIST))
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
    {   context.environment (env_query_string, var_ [ENVIRONMENT QUERY_STRING].as < ::std::string > ());
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

    if (! context.cgi ()) if (var_.count (GENERAL CGI)) context.cgi (onoff (nits, var_ [GENERAL CGI].as < ::std::string > ()));

    if (context.cgi ()) context.todo (do_cgi);
    else if (! var_.count (WEBSITE ROOT))
    {   nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
        return; }
    else context.todo (do_examine); }

void options::contextualise (nitpick& nits)
{   bool progress = false;
    if (var_.count (GENERAL TEST))
        if (! onoff (nits, var_ [GENERAL TEST].as < ::std::string > ())) context.test (false);
        else context.test (true).article (false).body (false).codes (false).crosslinks (false).external (false).forwarded (false).info (false).jsonld (false).links (false).load_css (true)
                    .main (false).md_export (false).meta (false).mf_verify (false).microdata (false).nids (true).nits (false).nits_nits_nits (true).nochange (false).not_root (false)
                    .notify (false).once (false).presume_tags (false) .process_webmentions (false).progress (false).rdfa (false).rel (false).reset (false).revoke (false).rfc_1867 (true)
                    .rfc_1942 (true).rfc_1980 (true).rfc_2070 (true).rpt_opens (false).schema (true).shadow_changed (false).shadow_comment (false).shadow_enable (false).shadow_space (false)
                    .shadow_ssi (false).spec (false).spell (false).ssi (false).stats_page (false).stats_summary (false).unknown_class (false).update (false);

    if (var_.count (WMOUT CLEAR)) context.clear (onoff (nits, var_ [WMOUT CLEAR].as < ::std::string > ()));

    if (! context.cgi ())
    {   if (var_.count (NITS FORMAT)) context.nit_format (var_ [NITS FORMAT].as < ::std::string > ());
        if (var_.count (NITS OVERRIDE)) context.nit_override (var_ [NITS OVERRIDE].as < ::std::string > ()); }

    if (context.test () || ! context.cgi ())
    {   if (var_.count (GENERAL OUTPUT))
        {   context.output (nits, nix_path_to_local (var_ [GENERAL OUTPUT].as < ::std::string > ()));
            if (! context.test ())
                nits.pick (nit_configuration, es_comment, ec_init, ::std::string ("Writing to ") + var_ [GENERAL OUTPUT].as < ::std::string > ()); }
        if (var_.count (GENERAL PROGRESS)) progress = onoff (nits, var_ [GENERAL PROGRESS].as < ::std::string > ());
        if (progress) ::std::cout << SIMPLE_TITLE;
        if (! context.cgi ())
        {   context.path (nix_path_to_local (var_ [GENERAL DATAPATH].as < ::std::string > ()));
            if (! file_exists (context.path ()))
            {   nits.pick (nit_create_folder, es_info, ec_init, context.path (), " does not exist, am creating it.");
                if (! make_directories (context.path ()))
                    nits.pick (nit_cannot_create_file, es_catastrophic, ec_init, "cannot create ", context.path ()); } } }

    if (var_.count (GENERAL VERBOSE)) context.verbose (static_cast < e_verbose> (decode_severity (nits, var_ [GENERAL VERBOSE].as < ::std::string > ())));
    if (var_.count (HTML SNIPPET)) context.snippet (var_ [HTML SNIPPET].as < ::std::string > ());

    if (var_.count (MF VERIFY)) context.mf_verify (onoff (nits, var_ [MF VERIFY].as < ::std::string > ()));
    if (var_.count (MF VERSION)) context.mf_version (static_cast < unsigned char > (var_ [MF VERSION].as < int > ()));

    if (var_.count (HTML VERSION))
    {   ::std::string ver (var_ [HTML VERSION].as < ::std::string > ());
        if (! ver.empty ())
        {   bool xhtml = false;
            if (ver.length () >= 4)
                if (compare_no_case (ver.substr (0, 4), "html")) ver = trim_the_lot_off (ver.substr (4));
                else if (compare_no_case (ver.substr (0, 5), "xhtml")) { ver = trim_the_lot_off (ver.substr (5)); xhtml = true; }
            const ::std::string::size_type pos = ver.find ('.');
            if (pos != ::std::string::npos)
            {   int mjr = 1, mnr = 0xFF;
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
        if (var_.count (WEBSITE ROOT)) context.root (nix_path_to_local (var_ [WEBSITE ROOT].as < ::std::string > ()));

    load_template (nits, context.html_ver ());

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
                x = schema_version (es, ::gsl::narrow_cast < unsigned char > (lexical < unsigned int > :: cast (ver)), 0);
            else if (pos == 0)
                nits.pick (nit_config_version, es_warning, ec_init, "missing ontology major version");
            else if (pos == ver.length () - 1)
                x = schema_version (es, ::gsl::narrow_cast < unsigned char > (lexical < unsigned int > :: cast (ver.substr (0, pos))), 0);
            else if (pos > 0)
                x = schema_version (es, ::gsl::narrow_cast < unsigned char > (lexical < unsigned int > :: cast (ver.substr (0, pos))),
                                                              ::gsl::narrow_cast < unsigned char > (lexical < unsigned int > :: cast (ver.substr (pos+1))));
            if (x.invalid ())
                nits.pick (nit_config_version, es_error, ec_init, "invalid ontology ", quote (x.name ()), " version; use " ONTOLOGY LIST " to get a list of known versions.");
            else if (! set_default_schema_version (x.root (), x.mjr (), x.mnr ()))
                nits.pick (nit_config_version, es_error, ec_init, PROG " dislikes the ", quote (x.name ()), " version specified; use " ONTOLOGY LIST " to get a list of known versions."); } }

    if (var_.count (VALIDATION MICRODATAARG)) context.microdata (onoff (nits, var_ [VALIDATION MICRODATAARG].as < ::std::string > ()));

    if (! context.cgi ())
    {   if (var_.count (GENERAL CSS_OPTION)) context.load_css (onoff (nits, var_ [GENERAL CSS_OPTION].as < ::std::string > ()));
        if (var_.count (GENERAL NOCHANGE)) context.nochange (onoff (nits, var_ [GENERAL NOCHANGE].as < ::std::string > ()));
        if (var_.count (GENERAL PROGRESS)) context.progress (onoff (nits, var_ [GENERAL PROGRESS].as < ::std::string > ()));
        if (var_.count (GENERAL RDFA_)) context.rdfa (onoff (nits, var_ [GENERAL RDFA_].as < ::std::string > ()));
        if (var_.count (GENERAL REL)) context.rel (onoff (nits, var_ [GENERAL REL].as < ::std::string > ()));
        if (var_.count (GENERAL RPT)) context.rpt_opens (onoff (nits, var_ [GENERAL RPT].as < ::std::string > ()));
        if (var_.count (GENERAL SSI)) context.ssi (onoff (nits, var_ [GENERAL SSI].as < ::std::string > ()));
        context.persisted (path_in_context (nix_path_to_local (var_ [GENERAL FICHIER].as < ::std::string > ())));

        constexpr long meg = 1024*1024;

        if (! var_.count (GENERAL MAXFILESIZE))
            context.max_file_size (4 * meg);
        else
        {   long max = static_cast < long > (var_ [GENERAL MAXFILESIZE].as < int > ());
            if (max < 0 || (max > (LONG_MAX / meg))) max = DEFAULT_MAX_FILE_SIZE;
            context.max_file_size (max * meg); }

        if (var_.count (GENERAL CLASS)) context.unknown_class (onoff (nits, var_ [GENERAL CLASS].as < ::std::string > ()));
        if (var_.count (GENERAL CUSTOM)) context.custom_elements ( var_ [GENERAL CUSTOM].as < vstr_t > ());
        if (var_.count (GENERAL ERR))
        {   e_severity sev = decode_severity (nits, var_ [GENERAL ERR].as < ::std::string > ());
            if (sev != es_undefined) context.report_error (sev); }
        if (var_.count (GENERAL IGNORED)) context.ignore (nits, var_ [GENERAL IGNORED].as < vstr_t > ());
        if (var_.count (GENERAL LANG)) context.lang (var_ [GENERAL LANG].as < ::std::string > ());
        if (var_.count (GENERAL MACROEND)) context.macro_end (var_ [GENERAL MACROEND].as < ::std::string > ());
        if (var_.count (GENERAL MACROSTART)) context.macro_start (var_ [GENERAL MACROSTART].as < ::std::string > ());
        if (var_.count (GENERAL USER)) context.user (var_ [GENERAL USER].as < ::std::string > ());
        if (var_.count (GENERAL WEBMENTION)) context.process_webmentions (onoff (nits, var_ [GENERAL WEBMENTION].as < ::std::string > ()));

        if (var_.count (CORPUS OUTPUT)) context.corpus (nix_path_to_local (var_ [CORPUS OUTPUT].as < ::std::string > ()));
        if (var_.count (CORPUS ARTICLE)) context.article (onoff (nits, var_ [CORPUS ARTICLE].as < ::std::string > ()));
        if (var_.count (CORPUS BODY)) context.body (onoff (nits, var_ [CORPUS BODY].as < ::std::string > ()));
        if (var_.count (CORPUS MAIN)) context.main (onoff (nits, var_ [CORPUS MAIN].as < ::std::string > ()));

        if (var_.count (HTML RFC1867)) context.rfc_1867 (onoff (nits, var_ [HTML RFC1867].as < ::std::string > ()));
        if (var_.count (HTML RFC1942)) context.rfc_1942 (onoff (nits, var_ [HTML RFC1942].as < ::std::string > ()));
        if (var_.count (HTML RFC1980)) context.rfc_1980 (onoff (nits, var_ [HTML RFC1980].as < ::std::string > ()));
        if (var_.count (HTML RFC2070)) context.rfc_2070 (onoff (nits, var_ [HTML RFC2070].as < ::std::string > ()));
        if (var_.count (HTML TAGS)) context.presume_tags (onoff (nits, var_ [HTML TAGS].as < ::std::string > ()));
        if (var_.count (HTML TITLE)) context.title (static_cast < unsigned char > (var_ [HTML TITLE].as < int > ()));

        if (var_.count (JSONLD VERIFY)) context.jsonld (onoff (nits, var_ [JSONLD VERIFY].as < ::std::string > ()));
        if (var_.count (JSONLD EXTENSION)) context.jsonld_extension (var_ [JSONLD EXTENSION].as < vstr_t > ());

        if (var_.count (JSONLD VERSION))
        {   ::std::string ver (var_ [JSONLD VERSION].as < ::std::string > ());
            if (ver.empty ())
                nits.pick (nit_config_version, es_warning, ec_init, "missing json-ld version");
            else
            {   if (ver == "1.0") context.jsonld_version (jsonld_1_0);
                else if (ver == "1.1") context.jsonld_version (jsonld_1_1);
                else nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid json-ld version"); } }

        if (var_.count (LINKS CHECK)) context.links (onoff (nits, var_ [LINKS CHECK].as < ::std::string > ()));
        if (var_.count (LINKS EXTERNAL)) context.external (onoff (nits, var_ [LINKS EXTERNAL].as < ::std::string > ()));
        if (var_.count (LINKS FORWARD)) context.forwarded (onoff (nits, var_ [LINKS FORWARD].as < ::std::string > ()));
        if (var_.count (LINKS ONCE)) context.once (onoff (nits, var_ [LINKS ONCE].as < ::std::string > ()));
        if (var_.count (LINKS REVOKE)) context.revoke (onoff (nits, var_ [LINKS REVOKE].as < ::std::string > ()));
        if (var_.count (LINKS XLINK)) context.crosslinks (onoff (nits, var_ [LINKS XLINK].as < ::std::string > ()));

        if (var_.count (MATH VERSION))
        {   int n = var_ [MATH VERSION].as < int > ();
            if ((n > 0) && (n < 5)) context.math_version (static_cast < e_math_version > (n)); }

        if (var_.count (MF EXPORT)) context.mf_export (onoff (nits, var_ [MF EXPORT].as < ::std::string > ()));

        if (var_.count (MICRODATA EXPORT)) context.md_export (onoff (nits, var_ [MICRODATA EXPORT].as < ::std::string > ()));
        if (var_.count (MICRODATA VERIFY)) context.schema (onoff (nits, var_ [MICRODATA VERIFY].as < ::std::string > ()));
        else if (var_.count (MICRODATA MICRODATAARG)) context.schema (onoff (nits, var_ [MICRODATA MICRODATAARG].as < ::std::string > ()));
        if (var_.count (MICRODATA ROOT)) context.export_root (nix_path_to_local (var_ [MICRODATA ROOT].as < ::std::string > ()));
        if (var_.count (MICRODATA VIRTUAL)) context.exports (var_ [MICRODATA VIRTUAL].as < vstr_t > ());

        if (var_.count (NITS CODES)) context.codes (onoff (nits, var_ [NITS CODES].as < ::std::string > ()));
        if (var_.count (NITS NIDS)) context.nids (onoff (nits, var_ [NITS NIDS].as < ::std::string > ()));
        if (var_.count (NITS FORMAT)) context.nit_format (var_ [NITS FORMAT].as < ::std::string > ());
        if (var_.count (NITS QUOTE))
        {   e_quote_style qs = examine_value < t_quote_style > (nits, html_default, var_ [NITS QUOTE].as < ::std::string > ());
            context.quote_style (qs); }
        if (var_.count (NITS UNIQUE)) context.nits_nits_nits (onoff (nits, var_ [NITS UNIQUE].as < ::std::string > ()));
        if (var_.count (NITS ROOT)) context.not_root (onoff (nits, var_ [NITS ROOT].as < ::std::string > ()));
        if (var_.count (NITS SPEC)) context.spec (onoff (nits, var_ [NITS SPEC].as < ::std::string > ()));
        if (var_.count (NITS WATCH)) context.nits (onoff (nits, var_ [NITS WATCH].as < ::std::string > ()));

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
                if (! nitpick::modify_severity (s, es_silence))
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

        if (var_.count (SHADOW COMMENT)) context.shadow_comment (onoff (nits, var_ [SHADOW COMMENT].as < ::std::string > ()));
        if (var_.count (SHADOW CHANGED)) context.shadow_changed (onoff (nits, var_ [SHADOW CHANGED].as < ::std::string > ()));

        if (var_.count (SHADOW COPY))
        {   nitpick nuts;
            ::std::string s (var_ [SHADOW COPY].as < ::std::string  > ());
            e_shadow sh = examine_value < t_shadow > (nuts, html_tags, s);
            if (sh == sh_error)
                if ((s.length () == 1) && (::gsl::at (s, 0) >= '0') && (::gsl::at (s, 0) <= '7'))
                {   sh = static_cast < e_shadow > (::gsl::at (s, 0) - '0' + 1);
#ifdef NOLYNX
                    if ((sh == sh_hard) || (sh == sh_soft)) sh = sh_copy;
#endif // NOLYNX
                                                                           }
            if (sh != sh_error) context.copy (static_cast < int > (sh) - 1);
            else nits.pick (nit_config_shadow, es_error, ec_init, "invalid " SHADOW COPY " option"); }

        if (var_.count (SHADOW ENABLE)) context.shadow_comment (onoff (nits, var_ [SHADOW ENABLE].as < ::std::string > ()));
        if (var_.count (SHADOW FICHIER)) context.shadow_persist (nix_path_to_local (var_ [SHADOW FICHIER].as < ::std::string > ()));
        if (var_.count (SHADOW IGNORED)) context.shadow_ignore (var_ [SHADOW IGNORED].as < vstr_t > ());
        if (var_.count (SHADOW INFO)) context.info (onoff (nits, var_ [SHADOW INFO].as < ::std::string > ()));
        if (var_.count (SHADOW MSG)) context.msg (var_ [SHADOW MSG].as < ::std::string > ());
        if (var_.count (SHADOW ROOT)) context.shadow_root (nix_path_to_local (var_ [SHADOW ROOT].as < ::std::string > ()));
        if (var_.count (SHADOW SPACING)) context.shadow_space (onoff (nits, var_ [SHADOW SPACING].as < ::std::string > ()));
        if (var_.count (SHADOW SSI)) context.shadow_ssi (onoff (nits, var_ [SHADOW SSI].as < ::std::string > ()));
        if (var_.count (SHADOW UPDATE)) context.update (onoff (nits, var_ [SHADOW UPDATE].as < ::std::string > ()));
        if (var_.count (SHADOW VIRTUAL)) context.virtuals (var_ [SHADOW VIRTUAL].as < vstr_t > ());

        if (var_.count (SPELL ACCEPT)) context.spellings (var_ [SPELL ACCEPT].as < vstr_t > ());
        if (var_.count (SPELL CHECK)) context.spell (onoff (nits, var_ [SPELL CHECK].as < ::std::string > ()));
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
#ifdef GENNIX
        if (var_.count (SPELL PATH))
        {   ::boost::filesystem::path hunspell (var_ [SPELL PATH].as < ::std::string > ());
            if (! ::boost::filesystem::exists (hunspell)) nits.pick (nit_no_exec, es_error, ec_init, "Cannot find ", hunspell.string ());
            else if (! ::boost::filesystem::is_directory (hunspell)) nits.pick (nit_no_exec, es_error, ec_init, hunspell.string (), " is not a directory");
            else context.spell_path (hunspell); }
        if (var_.count (SPELL DICT))
        {   vstr_t lds (var_ [SPELL DICT].as < vstr_t > ());
            for (auto ld : lds)
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
#endif // GENNIC

        if (var_.count (STATS EXPORT)) context.stats (var_ [STATS EXPORT].as < ::std::string > ());
        if (var_.count (STATS META)) context.meta (onoff (nits, var_ [STATS META].as < ::std::string > ()));
        if (var_.count (STATS PAGE)) context.stats_page (onoff (nits, var_ [STATS PAGE].as < ::std::string > ()));
        if (var_.count (STATS SUMMARY)) context.stats_summary (onoff (nits, var_ [STATS SUMMARY].as < ::std::string > ()));

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

        if (var_.count (WEBSITE INDEX)) context.index (var_ [WEBSITE INDEX].as < ::std::string > ());
        if (var_.count (WEBSITE EXTENSION)) context.extensions (var_ [WEBSITE EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back ("html"); context.extensions (ex); }
        if (var_.count (WEBSITE SITE)) context.site (var_ [WEBSITE SITE].as < vstr_t > ());
        if (var_.count (WEBSITE VIRTUAL)) context.virtuals (var_ [WEBSITE VIRTUAL].as < vstr_t > ());

        if (! context.cgi ())
        {   if (var_.count (WMIN WRITE)) context.write_path (var_ [WMIN WRITE].as < ::std::string > ());
            if (var_.count (WMIN STUB)) context.stub (var_ [WMIN STUB].as < ::std::string > ());
            if (var_.count (WMIN DATAPATH)) context.incoming (path_in_context (nix_path_to_local (var_ [WMIN DATAPATH].as < ::std::string > ())));
            if (var_.count (WMIN HOOK)) context.hook (var_ [WMIN HOOK].as < ::std::string > ());
            if (var_.count (WMIN MENTION)) context.mentions (var_ [WMIN MENTION].as < vstr_t > ());
            if (var_.count (WMIN TEMPLATE)) context.templates ( var_ [WMIN TEMPLATE].as < vstr_t > ());
            if (var_.count (WMIN TEST_HEADER)) context.test_header (var_ [WMIN TEST_HEADER].as < ::std::string > ());

            if (var_.count (WMOUT NOTIFY)) context.notify (onoff (nits, var_ [WMOUT NOTIFY].as < ::std::string > ()));
            if (var_.count (WMOUT RESET)) context.reset (onoff (nits, var_ [WMOUT RESET].as < ::std::string > ()));
            if (var_.count (WMOUT SECRET)) context.secret (var_ [WMOUT SECRET].as < ::std::string > ()); }

        if (var_.count (VALIDATION ATTRIB)) add_attributes (var_ [VALIDATION ATTRIB].as < vstr_t > ());
        if (var_.count (VALIDATION CHARSET)) type_master < t_charset > :: extend (var_ [VALIDATION CHARSET].as < vstr_t > ());
        if (var_.count (VALIDATION CLASS)) type_master < t_class > :: extend (var_ [VALIDATION CLASS].as < vstr_t > ());
        if (var_.count (VALIDATION COLOR)) type_master < t_fixedcolour > :: extend (var_ [VALIDATION COLOR].as < vstr_t > ());
        if (var_.count (VALIDATION COLOUR)) type_master < t_fixedcolour > :: extend (var_ [VALIDATION COLOUR].as < vstr_t > ());
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

        if (context.write_path ().empty ()) context.write_path (context.root ()); }
    context.consolidate_jsonld (); }

void pvs (::std::ostringstream& res, const vstr_t& data)
{   for (auto i : data)
        res << i << " "; }

::std::string options::report () const
{   ::std::ostringstream res;
    if (context.test ()) return res.str ();

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

    if (var_.count (HELP)) res << HELP "\n";
    if (var_.count (VERSION)) res << VERSION "\n";

    if (var_.count (CORPUS ARTICLE)) res << CORPUS ARTICLE "\n";
    if (var_.count (CORPUS BODY)) res << CORPUS BODY "\n";
    if (var_.count (CORPUS MAIN)) res << CORPUS MAIN "\n";
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

    if (var_.count (GENERAL CGI)) res << GENERAL CGI "\n";
    if (var_.count (GENERAL CLASS)) res << GENERAL CLASS "\n";
    if (var_.count (GENERAL CSS_OPTION)) res << GENERAL CSS_OPTION "\n";
    if (var_.count (GENERAL CUSTOM)) { res << GENERAL CUSTOM ": "; pvs (res, var_ [GENERAL CUSTOM].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL DATAPATH)) res << GENERAL DATAPATH ": " << var_ [GENERAL DATAPATH].as < ::std::string > () << "\n";
    if (var_.count (GENERAL ERR)) res << GENERAL ERR ": " << var_ [GENERAL ERR].as < ::std::string > () << "\n";
    if (var_.count (GENERAL ENVIRONMENT)) { res << GENERAL ENVIRONMENT ": "; pvs (res, var_ [GENERAL ENVIRONMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL FICHIER)) res << GENERAL FICHIER ": " << var_ [GENERAL FICHIER].as < ::std::string > () << "\n";
    if (var_.count (GENERAL IGNORED)) { res << GENERAL IGNORED ": "; pvs (res, var_ [GENERAL IGNORED].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL LANG)) res << GENERAL LANG ": " << var_ [GENERAL LANG].as < ::std::string > () << "\n";
    if (var_.count (GENERAL MACROEND)) res << GENERAL MACROEND ": " << var_ [GENERAL MACROEND].as < ::std::string > () << "\n";
    if (var_.count (GENERAL MACROSTART)) res << GENERAL MACROSTART ": " << var_ [GENERAL MACROSTART].as < ::std::string > () << "\n";
    if (var_.count (GENERAL MAXFILESIZE)) res << GENERAL MAXFILESIZE ": " << var_ [GENERAL MAXFILESIZE].as < int > () << "\n";
    if (var_.count (GENERAL NOCHANGE)) res << GENERAL NOCHANGE "\n";
    if (var_.count (GENERAL PROGRESS)) res << GENERAL PROGRESS "\n";
    if (var_.count (GENERAL RDFA_)) res << GENERAL RDFA_ "\n";
    if (var_.count (GENERAL RPT)) res << GENERAL RPT "\n";
    if (var_.count (GENERAL SSI)) res << GENERAL SSI "\n";
    if (var_.count (GENERAL TEST)) res << GENERAL TEST "\n";
    if (var_.count (GENERAL USER)) res << GENERAL USER ": " << var_ [GENERAL USER].as < ::std::string > () << "\n";
    if (var_.count (GENERAL VERBOSE)) res << GENERAL VERBOSE ": " << var_ [GENERAL VERBOSE].as < ::std::string > () << "\n";
    if (var_.count (GENERAL WEBMENTION)) res << GENERAL WEBMENTION "\n";

    if (var_.count (HTML TAGS)) res << HTML TAGS "\n";
    if (var_.count (HTML RFC1867)) res << HTML RFC1867 "\n";
    if (var_.count (HTML RFC1942)) res << HTML RFC1942 "\n";
    if (var_.count (HTML RFC1980)) res << HTML RFC1980 "\n";
    if (var_.count (HTML RFC2070)) res << HTML RFC2070 "\n";
    if (var_.count (HTML SNIPPET)) res << HTML SNIPPET ": " << var_ [HTML SNIPPET].as < ::std::string > () << "\n";
    if (var_.count (HTML TITLE)) res << HTML TITLE ": " << var_ [HTML TITLE].as < int > () << "\n";
    if (var_.count (HTML VERSION)) res << HTML VERSION ": " << var_ [HTML VERSION].as < ::std::string > () << "\n";

    if (var_.count (JSONLD EXTENSION)) { res << JSONLD EXTENSION ": "; pvs (res, var_ [JSONLD EXTENSION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (JSONLD VERIFY)) res << JSONLD VERIFY "\n";
    if (var_.count (JSONLD VERSION)) res << JSONLD VERSION ": " << var_ [JSONLD VERSION].as < ::std::string > () << "\n";

    if (var_.count (LINKS EXTERNAL)) res << LINKS EXTERNAL "\n";
    if (var_.count (LINKS FORWARD)) res << LINKS FORWARD "\n";
    if (var_.count (LINKS CHECK)) res << LINKS CHECK "\n";
    if (var_.count (LINKS ONCE)) res << LINKS ONCE "\n";
    if (var_.count (LINKS REVOKE)) res << LINKS REVOKE "\n";
    if (var_.count (LINKS XLINK)) res << LINKS XLINK "\n";

    if (var_.count (MATH VERSION)) res << MATH VERSION ": " << var_ [MATH VERSION].as < int > () << "\n";

    if (var_.count (MICRODATA EXPORT)) res << MICRODATA EXPORT "\n";
    if (var_.count (MICRODATA VERIFY)) res << MICRODATA VERIFY "\n";
    if (var_.count (MICRODATA MICRODATAARG)) res << MICRODATA MICRODATAARG "\n";
    if (var_.count (MICRODATA ROOT)) res << MICRODATA ROOT ": " << var_ [MICRODATA ROOT].as < ::std::string > () << "\n";
    if (var_.count (MICRODATA VIRTUAL)) { res << MICRODATA VIRTUAL ": "; pvs (res, var_ [MICRODATA VIRTUAL].as < vstr_t > ()); res << "\n"; }

    if (var_.count (NITS CATASTROPHE)) { res << NITS CATASTROPHE ": "; pvs (res, var_ [NITS CATASTROPHE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS COMMENT)) { res << NITS COMMENT ": "; pvs (res, var_ [NITS COMMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS DBG)) { res << NITS DBG ": "; pvs (res, var_ [NITS DBG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS ERR)) { res << NITS ERR ": "; pvs (res, var_ [NITS ERR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS FORMAT)) res << NITS FORMAT ": " << var_ [NITS FORMAT].as < ::std::string > () << "\n";
    if (var_.count (NITS INFO)) { res << NITS INFO ": "; pvs (res, var_ [NITS INFO].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS NIDS)) res << NITS NIDS "\n";
    if (var_.count (NITS OVERRIDE)) res << NITS OVERRIDE ": " << var_ [NITS OVERRIDE].as < ::std::string > () << "\n";
    if (var_.count (NITS SILENCE)) { res << NITS SILENCE ": "; pvs (res, var_ [NITS SILENCE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS SPEC)) res << NITS SPEC "\n";
    if (var_.count (NITS UNIQUE)) res << NITS UNIQUE "\n";
    if (var_.count (NITS WARNING)) { res << NITS WARNING ": "; pvs (res, var_ [NITS WARNING].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS WATCH)) res << NITS WATCH "\n";

    if (var_.count (MF EXPORT)) res << MF EXPORT "\n";
    if (var_.count (MF VERIFY)) res << MF VERIFY "\n";
    if (var_.count (MF VERSION)) res << MF VERSION ": " << var_ [MF VERSION].as < int > () << "\n";

    if (var_.count (RDFA DC)) res << RDFA DC ": " << var_ [RDFA DC].as < int > () <<  "\n";
    if (var_.count (RDFA FOAF)) res << RDFA FOAF ": " << var_ [RDFA FOAF].as < int > () <<  "\n";
    if (var_.count (RDFA VERSION)) res << RDFA VERSION ": " << var_ [RDFA VERSION].as < ::std::string > () <<  "\n";
    if (var_.count (RDFA XSD)) res << RDFA XSD ": " << var_ [RDFA XSD].as < int > () <<  "\n";

    if (var_.count (ONTOLOGY LIST)) res << ONTOLOGY LIST "\n";

    for (int i = s_none + 1; i < s_error; ++i)
    {   const e_schema es = static_cast < e_schema > (i);
        if (is_faux_schema (es)) continue;
        if (get_schema_version_count (es) < 2) continue;
        const ::std::string naam (schema_names.get (es, SCHEMA_NAME));
        ::std::string arg (ONTOLOGY);
        arg += naam;
        if (var_.count (arg))
            res << arg << ": " << var_ [arg].as < ::std::string > () << "\n"; }

    if (var_.count (SHADOW CHANGED)) res << SHADOW CHANGED "\n";
    if (var_.count (SHADOW COMMENT)) res << SHADOW COMMENT "\n";
    if (var_.count (SHADOW COPY)) res << SHADOW COPY ": " << var_ [SHADOW COPY].as < ::std::string > () << "\n";
    if (var_.count (SHADOW ENABLE)) res << SHADOW ENABLE "\n";
    if (var_.count (SHADOW FICHIER)) res << SHADOW FICHIER ": " << var_ [SHADOW FICHIER].as < ::std::string > () << "\n";
    if (var_.count (SHADOW IGNORED)) { res << SHADOW IGNORED ": "; pvs (res, var_ [SHADOW IGNORED].as < vstr_t > ()); res << "\n"; }
    if (var_.count (SHADOW MSG)) res << SHADOW MSG ": " << var_ [SHADOW MSG].as < ::std::string > () << "\n";
    if (var_.count (SHADOW ROOT)) res << SHADOW ROOT ": " << var_ [SHADOW ROOT].as < ::std::string > () << "\n";
    if (var_.count (SHADOW SPACING)) res << SHADOW SPACING "\n";
    if (var_.count (SHADOW SSI)) res << SHADOW SSI "\n";
    if (var_.count (SHADOW UPDATE)) res << SHADOW UPDATE "\n";
    if (var_.count (SHADOW VIRTUAL)) { res << SHADOW VIRTUAL ": "; pvs (res, var_ [SHADOW VIRTUAL].as < vstr_t > ()); res << "\n"; }

    if (var_.count (SPELL ACCEPT)) { res << SPELL ACCEPT ": "; pvs (res, var_ [SPELL ACCEPT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (SPELL CHECK)) res << SPELL CHECK "\n";
#ifdef GENNIX
    if (var_.count (SPELL DICT)) { res << SPELL DICT ": "; pvs (res, var_ [SPELL DICT].as < vstr_t > ()); res << "\n"; }
#endif // GENNIX
    if (var_.count (SPELL LIST)) { res << SPELL LIST ": "; pvs (res, var_ [SPELL LIST].as < vstr_t > ()); res << "\n"; }
#ifdef GENNIX
    if (var_.count (SPELL PATH)) res << SPELL PATH ": " << var_ [SPELL PATH].as < ::std::string > () << "\n";
#endif // GENNIX

    if (var_.count (STATS EXPORT)) res << STATS EXPORT ": " << var_ [STATS EXPORT].as < ::std::string > () << "\n";
    if (var_.count (STATS META)) res << STATS META "\n";
    if (var_.count (STATS PAGE)) res << STATS PAGE "\n";
    if (var_.count (STATS SUMMARY)) res << STATS SUMMARY "\n";

    if (var_.count (SVG VERSION)) res << SVG VERSION "\n";

    if (var_.count (VALIDATION ATTRIB)) { res << VALIDATION ATTRIB ": "; pvs (res, var_ [VALIDATION ATTRIB].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION CHARSET)) { res << VALIDATION CHARSET ": "; pvs (res, var_ [VALIDATION CHARSET].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION CLASS)) { res << VALIDATION CLASS ": "; pvs (res, var_ [VALIDATION CLASS].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION COLOR)) { res << VALIDATION COLOUR ": "; pvs (res, var_ [VALIDATION COLOR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION COLOUR)) { res << VALIDATION COLOUR ": "; pvs (res, var_ [VALIDATION COLOUR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION CURRENCY)) { res << VALIDATION CURRENCY ": "; pvs (res, var_ [VALIDATION CURRENCY].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION DINGBATARG)) { res << VALIDATION DINGBATARG ": "; pvs (res, var_ [VALIDATION DINGBATARG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION ELEMENT)) { res << VALIDATION ELEMENT ": "; pvs (res, var_ [VALIDATION ELEMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION ELEMATTR)) { res << VALIDATION ELEMATTR ": "; pvs (res, var_ [VALIDATION ELEMATTR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION HTTPEQUIV)) { res << VALIDATION HTTPEQUIV ": "; pvs (res, var_ [VALIDATION HTTPEQUIV].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION LANG)) { res << VALIDATION LANG ": "; pvs (res, var_ [VALIDATION LANG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION MINOR)) res << VALIDATION MINOR ": " << var_ [VALIDATION MINOR].as < int > () << "\n";
    if (var_.count (VALIDATION METANAME)) { res << VALIDATION METANAME ": "; pvs (res, var_ [VALIDATION MIMETYPE].as < vstr_t > ()); res << "\n"; }
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

    if (var_.count (WEBSITE EXTENSION)) { res << WEBSITE EXTENSION ": "; pvs (res, var_ [WEBSITE EXTENSION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WEBSITE INDEX)) res << WEBSITE INDEX ": " << var_ [WEBSITE INDEX].as < ::std::string > () << "\n";
    if (var_.count (WEBSITE SITE)) { res << WEBSITE SITE ": "; pvs (res, var_ [WEBSITE SITE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WEBSITE ROOT)) res << WEBSITE ROOT ": " << var_ [WEBSITE ROOT].as < ::std::string > () << "\n";
    if (var_.count (WEBSITE VIRTUAL)) { res << WEBSITE VIRTUAL ": "; pvs (res, var_ [WEBSITE VIRTUAL].as < vstr_t > ()); res << "\n"; }

    if (var_.count (WMIN WRITE)) { res << WMIN WRITE ": "; var_ [WMIN WRITE].as < ::std::string > (); res << "\n"; }
    if (var_.count (WMIN STUB)) res << WMIN STUB ": " << var_ [WMIN STUB].as < ::std::string > () << "\n";
    if (var_.count (WMIN DATAPATH)) res << WMIN DATAPATH ": " << var_ [WMIN DATAPATH].as < ::std::string > () << "\n";
    if (var_.count (WMIN HOOK)) res << WMIN HOOK ": " << var_ [WMIN HOOK].as < ::std::string > () << "\n";
    if (var_.count (WMIN MENTION)) { res << WMIN MENTION ": "; pvs (res, var_ [WMIN MENTION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WMIN TEMPLATE)) { res << WMIN TEMPLATE ": "; pvs (res, var_ [WMIN TEMPLATE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WMIN TEST_HEADER)) res << WMIN TEST_HEADER ": " << var_ [WMIN TEST_HEADER].as < ::std::string > () << "\n";

    if (var_.count (WMOUT CLEAR)) res << WMOUT CLEAR "\n";
    if (var_.count (WMOUT NOTIFY)) res << WMOUT NOTIFY "\n";
    if (var_.count (WMOUT RESET)) res << WMOUT RESET "\n";
    if (var_.count (WMOUT SECRET)) res << WMOUT SECRET ": " << var_ [WMOUT SECRET].as < ::std::string > () << "\n";

    return res.str (); }
