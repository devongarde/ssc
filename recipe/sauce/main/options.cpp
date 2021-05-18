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

#include "main/standard.h"
#include "main/options.h"
#include "main/context.h"
#include "type/type.h"
#include "main/args.h"
#include "utility/lexical.h"
#include "feedback/nitpick.h"
#include "schema/schema_version.h"
#include "attribute/attributes.h"
#include "element/elem.h"
#include "element/element_classes.h"
#include "url/url_sanitise.h"
#include "type/type_master.h"

/*
-N
picks up web mention links, digs through them, finds notification server, and sends appropriate notifications
Note: will need to keep track of mentions, so changes can be noted as additions, updates or deletes.
Mentions can be identified by their in-reply-tos, and if there are many of them to the same URL, then so be it.
Requires microformat processing

Q: Does app:
    store old pages (where?),
    talk to version control,
    require old and new page parameters,
    or have the user specify precise changes?
Q: When updating, does app:
    presume all web mentions have changed,
    or compare & look for changes?
I lean towards the latter.

-P
Make note of web mention references in files, but don't actually notify the server of changes.
Instead, prime the web mention data store so future updates can be notified

-C
Clear the web mention data store. The next time the app is run, it'll be as thought all the web mentions
are fresh and new.


-M parameters
url parameter style encoded webmention references (https://indieweb.org/Webmention-developer), expects:
source= is site containing mention to this site
target= is specific page on this site that is mentioned
both must be given

Q: Given web mentions are dynamic:
    should the target page be updated in situ
    should a set of HTML snippet be created, one per web mention, to be assembled during page compilation
    should frames or something like it be used (NO!)


sundry switches
-T insert,update,delete,unchanged
web mention HTML snippet templates

-n
tell what it would do, don't actually do it

*/


/*
also useful

1. additional HTML elements (as per data, which I've explicitly coded)
should allow attribute specification too

2. additional rel values
needs rel type and probably context info
*/

#define TYPE_HELP "Type '" PROG " -h' for help."
#define DEFAULT_LINE_LENGTH 120
#define DESCRIPTION_LENGTH 80

::std::string env_mapper (::std::string env)
{  // boost environment variable translator
    ::std::transform (env.begin(), env.end(), env.begin(), ::toupper);
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

void options::title (const char* addendum) const
{   if (! context.test ())
        ::std::cout << FULLNAME " " VERSION_STRING ", " WEBADDR "\n" COPYRIGHT "\n(" __DATE__ " " __TIME__ ")\n";

    if (context.tell (e_severe))
    {   if (addendum != nullptr) ::std::cout << addendum; }
    else ::std::cout << "\n"; }

void options::help (const ::boost::program_options::options_description& aid) const
{   ::std::cout << PROG " [switch...] path.\n\n";
    ::std::cout << PROG " is an opinionated HTML nit-picker. It notes broken links, dubious syntax, bad semantics,\n";
    ::std::cout << "etc.. It highlights legal but untidy code.\n";
    ::std::cout << aid << "\n\n";
    ::std::cout << "Configuration file section names precede each switch dot above (e.g. " GENERAL_ ", " LINKS_ ",\n" ;
    ::std::cout << WEBSITE_ ", etc.). Option names follow them. For example:\n\n";
    ::std::cout << "[" GENERAL_ "]\n";
    ::std::cout << VERBOSE "=2\n\n";
    ::std::cout << "[" LINKS_ "]\n";
    ::std::cout << CHECK "=1\n\n";
    ::std::cout << "[" WEBSITE_ "]\n";
    ::std::cout << EXTENSION "=html\n";
    ::std::cout << INDEX "=index.shtml\n";
    ::std::cout << SITE "=" DEFAULT_DOMAIN "\n\n"; }

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

void options::process (int argc, char** argv)
{   /*  a
        b
        c persist file   C clear webmention
        d dump corpus
        e external check
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
        p prog dir
        q
        r no revoke chks R reset webmention
        s domain name    S stats
        t template       T test mode
        u
        v verbose        V version
        w webmention     W cgi
        x extensions     X check crosslinked ids
        y
        z title max      Z spec
        0
        1
        2
        3 rpt forwards (30x)
        4
        5 HTML 5 mnr
        6
        7
        8
        9
*/
    ::boost::program_options::options_description
        aid (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        basic ("Console Options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        cgi (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        cmd (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        config (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        env (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        hidden,
        line (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        primary ("Standard Options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        valid ("validation options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH);
    ::boost::program_options::positional_options_description pos;
    pos.add (WEBSITE ROOT, 1);
    basic.add_options ()
        (HELP ",h", "output this information and exit")
        (VALIDATION_, "list attribute extensions and exit")
        (VERSION ",V", "display version & copyright info, then exit")
        ;
    cgi.add_options ()
        (ENVIRONMENT SERVER_SOFTWARE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_SOFTWARE)
        (ENVIRONMENT SERVER_NAME, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_NAME)
        (ENVIRONMENT GATEWAY_INTERFACE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " GATEWAY_INTERFACE)
        (ENVIRONMENT SERVER_PROTOCOL, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_PROTOCOL)
        (ENVIRONMENT SERVER_PORT, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_PORT)
        (ENVIRONMENT REQUEST_METHOD, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REQUEST_METHOD)
        (ENVIRONMENT HTTP_ACCEPT, ::boost::program_options::value < ::std::string > (), "CGI environment variable " HTTP_ACCEPT)
        (ENVIRONMENT PATH_INFO, ::boost::program_options::value < ::std::string > (), "CGI environment variable " PATH_INFO)
        (ENVIRONMENT PATH_TRANSLATED, ::boost::program_options::value < ::std::string > (), "CGI environment variable " PATH_TRANSLATED)
        (ENVIRONMENT SCRIPT_NAME, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SCRIPT_NAME)
        (ENVIRONMENT QUERY_STRING, ::boost::program_options::value < ::std::string > (), "CGI environment variable " QUERY_STRING)
        (ENVIRONMENT REMOTE_HOST, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_HOST)
        (ENVIRONMENT REMOTE_ADDR, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_ADDR)
        (ENVIRONMENT REMOTE_USER, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_USER)
        (ENVIRONMENT AUTH_TYPE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " AUTH_TYPE)
        (ENVIRONMENT CONTENT_TYPE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " CONTENT_TYPE)
        (ENVIRONMENT CONTENT_LENGTH, ::boost::program_options::value < ::std::string > (), "CGI environment variable " CONTENT_LENGTH)
        ;
    env.add_options ()
        (SERVER_SOFTWARE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_SOFTWARE)
        (SERVER_NAME, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_NAME)
        (GATEWAY_INTERFACE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " GATEWAY_INTERFACE)
        (SERVER_PROTOCOL, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_PROTOCOL)
        (SERVER_PORT, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SERVER_PORT)
        (REQUEST_METHOD, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REQUEST_METHOD)
        (HTTP_ACCEPT, ::boost::program_options::value < ::std::string > (), "CGI environment variable " HTTP_ACCEPT)
        (PATH_INFO, ::boost::program_options::value < ::std::string > (), "CGI environment variable " PATH_INFO)
        (PATH_TRANSLATED, ::boost::program_options::value < ::std::string > (), "CGI environment variable " PATH_TRANSLATED)
        (SCRIPT_NAME, ::boost::program_options::value < ::std::string > (), "CGI environment variable " SCRIPT_NAME)
        (QUERY_STRING, ::boost::program_options::value < ::std::string > (), "CGI environment variable " QUERY_STRING)
        (REMOTE_HOST, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_HOST)
        (REMOTE_ADDR, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_ADDR)
        (REMOTE_USER, ::boost::program_options::value < ::std::string > (), "CGI environment variable " REMOTE_USER)
        (AUTH_TYPE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " AUTH_TYPE)
        (CONTENT_TYPE, ::boost::program_options::value < ::std::string > (), "CGI environment variable " CONTENT_TYPE)
        (CONTENT_LENGTH, ::boost::program_options::value < ::std::string > (), "CGI environment variable " CONTENT_LENGTH)
        (ENV_CONFIG, ::boost::program_options::value < ::std::string > (), "load configuration from this file")
        (ENV_ARGS, ::boost::program_options::value < ::std::string > (), "alternative command line parameters")
        ;
    hidden.add_options ()
        (GENERAL CGI ",W", "process OpenBSD httpd <FORM METHOD=GET ...> (incompatible with " GENERAL WEBMENTION ")")
        (GENERAL CLASS, "do not report unrecognised classes")
        (GENERAL FICHIER ",c", ::boost::program_options::value < ::std::string > () -> default_value (PROG EXT), "file for persistent data, requires -N (note " GENERAL PATH ")")
        (GENERAL RPT, "report when CSS files opened")
        (GENERAL TEST ",T", "output format for automated tests")
        (GENERAL USER, ::boost::program_options::value < ::std::string > () -> default_value ("scroggins"), "user name to supply when requested (for webmentions)")
        (GENERAL WEBMENTION, "process webmentions (experimental, incompatible with " GENERAL CGI ")")
        (NITS SPEC ",Z", "output nit codes, not numbers, in tests (scc-test rejects this format)")
        (NITS WATCH, "output debug nits, which you'll need to manage particular error messages")
        (WMIN TEST_HEADER, ::boost::program_options::value < ::std::string > (), "use this file to test header parsing code")
        (WMIN HOOK, ::boost::program_options::value < ::std::string > (), "process incoming " WEBMENTION ", in JSON format, in specified file")
        (WMIN STUB, ::boost::program_options::value < ::std::string > () -> default_value ("_" PROG), "mask for file containing " WEBMENTION " HTML snippet")
        (WMIN MACROSTART, ::boost::program_options::value < ::std::string > () -> default_value ("{{"), "start of " WEBMENTION " template macro")
        (WMIN MACROEND, ::boost::program_options::value < ::std::string > () -> default_value ("}}"), "end of " WEBMENTION " template macro")
        (WMIN WRITE , ::boost::program_options::value < ::std::string > (), "when writing " WEBMENTION " includes, write them to this path (default: site.root)")
        (WMIN MENTION, ::boost::program_options::value < vstr_t > () -> composing (), "a " WEBMENTION ", string must be source=url,target=url; may be repeated")
        (WMIN PATH, ::boost::program_options::value < ::std::string > () -> default_value (MENTION), "path for incoming web mention data files (note " GENERAL PATH ")") // not yet noted below
        (WMIN TEMPLATE ",t", ::boost::program_options::value < vstr_t > () -> composing (), "HTML snippets for adding mentions (new, changed, deleted, unchanged, unknown); may be repeated")
        (WMOUT CLEAR ",C", "clear out all web mention data")
        (WMOUT NOTIFY ",N", "notify appropriate servers of web mention updates")
        (WMOUT RESET ",R", "reset web mention data")
        (WMOUT SECRET, ::boost::program_options::value < ::std::string > (), WEBMENTION " secret")
        ;
    line.add_options ()
        (CONFIG ",f", ::boost::program_options::value < ::std::string > (), "load configuration from this file")
        (DEFCONF ",F", "load configuration from " CONFIGURATION)
        (HTML SNIPPET ",H", ::boost::program_options::value < ::std::string > (), "only nitpick the given snippet of HTML")
        ;
    primary.add_options ()
        (GENERAL CSS_OPTION, "do NOT process .css files")
        (GENERAL CORPUS ",d", ::boost::program_options::value < ::std::string > (), "Dump corpus of site content to specified file")
        (GENERAL CUSTOM, ::boost::program_options::value < vstr_t > () -> composing (), "Define a custom element for checking the 'is' attribute; may be repeated")
        (GENERAL IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "ignore attributes and content of specified element; may be repeated")
        (GENERAL LANG, ::boost::program_options::value < ::std::string > () -> composing (), "default language (such as 'en_GB', 'lb_LU', etc.)")
        (GENERAL MAXFILESIZE, ::boost::program_options::value < int > (), "maximum file size to read, in megabytes (zero for no limit)")
        (GENERAL NOCHANGE ",n", "report what will do, but do not do it")
        (GENERAL OUTPUT ",o", ::boost::program_options::value < ::std::string > (), "output file (default to the console)")
        (GENERAL PATH ",p", ::boost::program_options::value < ::std::string > () -> default_value ("." PROG), "root directory for all " PROG " files")
        (GENERAL RDF, "check RDFa attributes")
        (GENERAL REL, "ignore recognised but non-standard <LINK> REL values")
        (GENERAL SLOB, "ignore inefficient HTML such as missing closures")
        (GENERAL SSI ",I", "process (simple) Server Side Includes")
        (GENERAL VERBOSE ",v", ::boost::program_options::value < int > () -> default_value (static_cast <int> (default_output)), "output extra information")

        (HTML RFC1867, "Reject RFC 1867 (INPUT=FILE) when processing HTML 2.0")
        (HTML RFC1942, "Reject RFC 1942 (tables) when processing HTML 2.0")
        (HTML RFC1980, "Reject RFC 1980 (client side image maps) when processing HTML 2.0")
        (HTML RFC2070, "Reject RFC 2070 (internationalisation) when processing HTML 2.0")
        (HTML TAGS, "presume HTML files with no DOCTYPE declaration are HTML Tags, not HTML 1.0")
        (HTML TITLE ",z", ::boost::program_options::value < int > () -> default_value (MAX_IDEAL_TITLE_LENGTH), "Maximum advisable length of <TITLE> text")
        (HTML VERSION, ::boost::program_options::value < ::std::string > (),
            "specific X.Y version of HTML 5.y (default '5.3'), or if no DOCTYPE found (default: '1.0'). "
            "For specific WhatWG living standard, give date (e.g. '2020/7/1'). "
            "For HTML+, use '+'. For HTML tags, use 'tags'.")

        (LINKS EXTERNAL ",e", "check external links (requires curl, sets " LINKS CHECK ")")
        (LINKS FORWARD ",3", "report http forwarding errors, e.g. 301 and 308 (sets " LINKS EXTERNAL ")")
        (LINKS CHECK ",l", "check internal links")
        (LINKS ONCE ",O", "report each broken external link once (sets " LINKS EXTERNAL ")")
        (LINKS REVOKE ",r", "do not check whether https certificates have been revoked (sets " LINKS EXTERNAL ")")
        (LINKS XLINK ",X", "check crosslink ids")

        (MF VERIFY ",M", "check microformats in class and rel attributes (see https://" MICROFORMATS_ORG "/)")
        (MF VERSION, ::boost::program_options::value < int > () -> default_value (3), "check this version of microformats (1, 2, or 3 for both)")
        (MF EXPORT, "export microformat data (requires " MF VERIFY ")")

        (MATH VERSION, ::boost::program_options::value < int > () -> default_value (0), "preferred version of MathML (0 to determine by HTML version)")

        (MICRODATA EXPORT, "export microformat data (only verified data if " MICRODATA MICRODATAARG " is set)")
        (MICRODATA MICRODATAARG ",m", "check microdata (" PROG " only understands certain microdata schemas)")
        (MICRODATA ROOT, ::boost::program_options::value < ::std::string > (), "export root directory (requires " MICRODATA EXPORT ")")
        (MICRODATA VERSION, ::boost::program_options::value < ::std::string > (), "set default " SCHEMA_ORG " version (default: " DEFAULT_SCHEMA_VERSION ")")
        (MICRODATA VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "export virtual directory, syntax virtual=directory. Must correspond to " WEBSITE VIRTUAL)

        (NITS CATASTROPHE, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as a catastrophe; may be repeated")
        (NITS CODES, "output nit codes")
        (NITS COMMENT, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as a comment; may be repeated")
        (NITS DBG, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as a debug message; may be repeated")
        (NITS ERR, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as an error; may be repeated")
        (NITS INFO, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as info; may be repeated")
        (NITS NIDS, "output nit identifiers (used to recategorise nits)")
        (NITS SILENCE, ::boost::program_options::value < vstr_t > () -> composing (), "silence nit; may be repeated")
        (NITS WARNING, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as a warning; may be repeated")

        (SHADOW COMMENT, "do NOT squish comments on shadow pages")
#ifdef NOLYNX
        (SHADOW COPY, ::boost::program_options::value < int > (), "copy non-HTML files: 0=no (default), 1=pages, 2/3/4=copy all, 5=copy+deduplicate, 6=only report duplicates")
#else // NOLYNX
        (SHADOW COPY, ::boost::program_options::value < int > (), "copy non-HTML files: 0=no (default), 1=pages, 2=hard link all, 3=soft link all, 4=copy all, 5=copy+deduplicate, 6=only report duplicates")
#endif // NOLYNX
        (SHADOW FICHIER, ::boost::program_options::value < ::std::string > (), "where to persist deduplication data")
        (SHADOW CHANGED, "only link/copy shadow files when the target doesn't exist, or is older than the original")
        (SHADOW IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "ignore files with this extension; may be repeated (do not forget the dot)")
        (SHADOW INFO, "add a comment to generated shadow HTML files noting their time of generation")
        (SHADOW MSG, ::boost::program_options::value < ::std::string > (), "insert this as comment to generated shadow files")
        (SHADOW ROOT, ::boost::program_options::value < ::std::string > (), "shadow output root directory")
        (SHADOW SSI, "do NOT resolve SSIs on shadow pages when " GENERAL SSI " is set")
        (SHADOW SPACING, "do NOT merge spacing on shadow pages")
        (SHADOW VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "shadow virtual directory, syntax virtual=shadow; must correspond to " WEBSITE VIRTUAL "; may be repeated")

        (WEBSITE ROOT ",g", ::boost::program_options::value < ::std::string > (), "website root directory (default: current directory)")
        (WEBSITE EXTENSION ",x", ::boost::program_options::value < vstr_t > () -> composing (), "check files with this extension (default html); may be repeated")
        (WEBSITE INDEX ",i", ::boost::program_options::value < ::std::string > (), "index file in directories (default: none)")
        (WEBSITE SITE ",s", ::boost::program_options::value < vstr_t > () -> composing (), "domain name(s) for local site (default none); may be repeated")
        (WEBSITE VIRTUAL ",L", ::boost::program_options::value < vstr_t > () -> composing (), "define virtual directory, arg syntax virtual=physical; may be repeated")

        (STATS EXPORT, ::boost::program_options::value < ::std::string > (), "export collected statistical data")
        (STATS META, "report on <META> data")
        (STATS PAGE, "report individual page statistics")
        (STATS SUMMARY ",S", "report overall statistics")

        (SVG MODE, "SVG 2.0 processing mode (0=dynamic, 1-animated, 2=secure_animated, 3=static, 4=secure_static)")
        (SVG VERSION, ::boost::program_options::value < ::std::string > (), "presumed version of SVG if version attribute missing (requires HTML 4 or greater)")

        (VALIDATION MINOR ",m", ::boost::program_options::value < int > (), "validate HTML 5 with this w3 minor version (e.g. 3 for HTML 5.3)")
        (VALIDATION MICRODATAARG, "validate HTML5 microdata")
        	;
    valid.add_options ()
        (VALIDATION ATTRIB, ::boost::program_options::value < vstr_t > () -> composing (), "add a custom attribute (name namespace flags ext); may be repeated")
        (VALIDATION CHARSET, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid charset; may be repeated")
        (VALIDATION CLASS, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid class; may be repeated")
        (VALIDATION COLOUR, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid colour; may be repeated")
        (VALIDATION CURRENCY, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid currency; may be repeated")
        (VALIDATION ELEMENT, ::boost::program_options::value < vstr_t > () -> composing (), "add a custom element (name namespace flags ext]]]); may be repeated")
        (VALIDATION ELEMATTR, ::boost::program_options::value < vstr_t > () -> composing (), "add an attribute to an element (element attribute); may be repeated")
        (VALIDATION EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "add a mimetype file extension; may be repeated")
        (VALIDATION HTTPEQUIV, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid meta httpequiv; may be repeated")
        (VALIDATION LANG, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid language code (such as ma for marain); may be repeated")
        (VALIDATION METANAME, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid meta name; may be repeated")
        (VALIDATION MIMETYPE, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid mimetype; may be repeated")
        (VALIDATION REL, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid rel; may be repeated")
        (VALIDATION SGML, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid SGML schema identification; may be repeated")
        ;
    valid.add (context.validation ());

    cmd.add (basic).add (primary).add (valid).add (line).add (hidden);
    config.add (primary).add (valid).add (hidden).add (cgi);
    aid.add (basic).add (line).add (primary);
    ::std::string loaded;

    try
    {   ::boost::program_options::store (::boost::program_options::parse_environment (env, ::boost::function1 < ::std::string, ::std::string> (env_mapper)), env_);
        if (env_.count (ENV_ARGS))
        {   vstr_t env_args (split_by_space (env_ [ENV_ARGS].as < ::std::string > ()));
            if (! env_args.empty ())
                ::boost::program_options::store (::boost::program_options::command_line_parser (env_args).options (cmd).positional (pos).run (), var_); } }
    catch (const ::boost::program_options::error& err)
    {   loaded = "\nEnvironment error: ";
        loaded += err.what ();
        loaded += "\n" TYPE_HELP "\n";
        title (loaded.c_str ());
        return; }
    catch (...)
    {   title ("\nEnvironment error.\n");
        return; }

    ::boost::program_options::notify (env_);

    if (env_.count (ENV_CONFIG)) context.environment (env_config, env_ [ENV_CONFIG].as < ::std::string > ());
    if (env_.count (ENV_ARGS)) context.environment (env_args, env_ [ENV_ARGS].as < ::std::string > ());

    if (env_.count (QUERY_STRING))
    {   context.environment (env_query_string, env_ [QUERY_STRING].as < ::std::string > ());
        if (! context.environment (env_query_string).empty ()) try
        {   context.cgi (true);
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
            {   title ("\nAn environment " QUERY_STRING " must include html.snippet. " TYPE_HELP "\n");
                return; } }
#ifdef DEBUG
        catch (const ::boost::program_options::error& err)
        {   loaded = "\nQuery error: ";
            loaded += err.what ();
            loaded += "\n" TYPE_HELP "\n";
            title (loaded.c_str ());
            return; }
#endif // DEBUG
        catch (...)
        {   ::std::cerr << "\nEnvironment query exception.\n";
            return; } }

    try
    {   ::boost::program_options::store (::boost::program_options::command_line_parser (argc, argv).options (cmd).positional (pos).run (), var_); }
    catch (const ::boost::program_options::error& err)
    {   loaded = "\n";
        loaded += err.what ();
        loaded += "\n" TYPE_HELP "\n";
        title (loaded.c_str ());
        return; }
    catch (...)
    {   title ("\nCommand line parameter error. " TYPE_HELP "\n");
        return; }
    if (var_.count (CONFIG) || var_.count (DEFCONF) || env_.count (ENV_CONFIG))
    {   ::boost::filesystem::path file (CONFIGURATION);
        if (var_.count (CONFIG)) file = var_ [CONFIG].as < ::std::string > ();
        else if ((var_.count (DEFCONF) == 0) && env_.count (ENV_CONFIG)) file = env_ [ ENV_CONFIG ].as < ::std::string > ();
        if (var_.count (GENERAL TEST) == 0)
        {   loaded = "\nLoading configuration "; loaded += file.string () + " ...\n"; }
        if (::boost::filesystem::exists (file)) context.config (canonical (file));
        else
        {   loaded += "Cannot find "; loaded += file.string () + "\n";
            title (loaded.c_str ()); return; }
        try
#ifdef  NO_PCF_STR
        {   ::std::ifstream fis (file.string ().c_str ());
            ::boost::program_options::store (::boost::program_options::parse_config_file (fis, config, true), var_); }
#else
        {   ::boost::program_options::store (::boost::program_options::parse_config_file (file.string ().c_str (), config, true), var_); }
#endif
        catch (const ::boost::program_options::error& err)
        {   loaded += err.what ();
            loaded += " in ";
            loaded += file.string ();
            loaded += "\n";
            title (loaded.c_str ());
            return; }
        catch (...)
        {   loaded += "Error in ";
            loaded += file.string () + "\n";
            title (loaded.c_str ()); return; } }
    ::boost::program_options::notify (var_);
    if (var_.count (VERSION)) { title (); valid_ = true; return; }
    if (var_.count (HELP)) { title (); help (aid); valid_ = true; return; }
    if (var_.count (VALIDATION_)) { title (); ::std::cout << "\n" << valid; valid_ = true; return; }

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
            {   title ("\n" ENVIRONMENT QUERY_STRING " must include html.snippet. " TYPE_HELP "\n");
                return; }
            ::boost::program_options::notify (var_); }
#ifdef DEBUG
        catch (const ::boost::program_options::error& err)
        {   loaded = "\nConfiguration " ENVIRONMENT_ " error: ";
            loaded += err.what ();
            loaded += "\n" TYPE_HELP "\n";
            title (loaded.c_str ());
            return; }
#endif // DEBUG
        catch (...)
        {   ::std::cerr << "\nConfiguration " ENVIRONMENT_ " query exception.\n";
            return; } }

    if (! context.cgi ()) context.cgi (var_.count (GENERAL CGI));

    if (context.cgi ()) valid_ = true;
    else
    {   valid_ = var_.count (WEBSITE ROOT);
        if (! valid_) { loaded += "\n" TYPE_HELP "\n"; title (loaded.c_str ()); return; }
        if (var_.count (GENERAL TEST) == 0) title (loaded.c_str ()); }
    stop_ = false; }

void options::contextualise ()
{   context.clear (var_.count (WMOUT CLEAR));
    context.test (var_.count (GENERAL TEST));

    if (context.test () || ! context.cgi ())
    {   if (var_.count (GENERAL OUTPUT))
        {   context.output (nix_path_to_local (var_ [GENERAL OUTPUT].as < ::std::string > ()));
            if (! context.test ())
                ::std::cout << "Writing to " << var_ [GENERAL OUTPUT].as < ::std::string > () << "\n"; }

        if (context.test ()) context.out (PROG "\n" VERSION_STRING "\n" COPYRIGHT"\n");
        else context.out (FULLNAME " version " VERSION_STRING " (" __DATE__ " " __TIME__ ")\n" COPYRIGHT "\n");

        if (! context.cgi ())
        {   context.path (nix_path_to_local (var_ [GENERAL PATH].as < ::std::string > ()));

            if (! ::boost::filesystem::exists (context.path ()))
            {   context.err (context.path ());
                context.err (" does not exist, am creating it.\n");
                try
                {   ::boost::filesystem::create_directories (context.path ()); }
                catch (...)
                {   context.err ("cannot create ");
                    context.err (context.path ());
                    context.err (".\n"); } } } }

    if (var_.count (HTML SNIPPET)) context.snippet (var_ [HTML SNIPPET].as < ::std::string > ());

    context.mf_verify (var_.count (MF VERIFY));
    if (var_.count (MF VERSION)) context.mf_version (static_cast < unsigned char > (var_ [MF VERSION].as < int > ()));

    if (var_.count (HTML VERSION))
    {   ::std::string ver (var_ [HTML VERSION].as < ::std::string > ());
        if (! ver.empty ())
        {   ::std::string::size_type pos = ver.find ('.');
            if (pos != ::std::string::npos)
                if (pos == ver.length () - 1) context.html_ver (lexical < int > :: cast (ver.substr (0, pos)), 0xFF);
                else if (pos == 0) context.html_ver (html_tags);
                else context.html_ver (lexical < int > :: cast (ver.substr (0, pos)), lexical < int > :: cast (ver.substr (pos+1)));
            else if (ver.find ('/') != ::std::string::npos)
                if ((ver.length () != 10) || (ver.at (4) != '/') || (ver.at (7) != '/') || (ver.find_first_not_of (DENARY "/") != ::std::string::npos))
                {   context.err ("bad date ");
                    context.err (quote (ver));
                    context.err (" ignored ('YYYY/MM/DD' expected)\n"); }
                else
                {   ::boost::gregorian::date d (::boost::gregorian::from_string (ver));
                    if (d.is_not_a_date ())
                    {   context.err ("invalid date ");
                        context.err (quote (ver));
                        context.err (" ignored\n"); }
                    else
                    {   int y = d.year (); int m = d.month ();
                        if (y > 2000) y -= 2000;
                        else if (y > 99) y = 99;
                        if ((y < HTML_5_EARLIEST_YEAR) || ((y == HTML_5_EARLIEST_YEAR) && (m < HTML_5_EARLIEST_MONTH)))
                        {   ::std::ostringstream ss;
                            ss << quote (ver) << " is too early, presuming " << HTML_5_EARLIEST_YEAR << "/" << HTML_5_EARLIEST_MONTH << "/1\n";
                            context.err (ss.str ());
                            context.html_ver (html_jan05); }
                        else if ((y > HTML_LATEST_YEAR) || ((y == HTML_LATEST_YEAR) && (m > HTML_LATEST_MONTH)))
                        {   ::std::ostringstream ss;
                            ss << quote (ver) << " is too recent, presuming " << HTML_LATEST_YEAR << "/" << HTML_LATEST_MONTH << "/1\n";
                            context.err (ss.str ());
                            context.html_ver (html_current); }
                        else context.html_ver (d); } }
            else if (ver == "+") context.html_ver (html_plus);
            else if (compare_no_case (ver, "plus")) context.html_ver (html_plus);
            else if (compare_no_case (ver, "tags")) context.html_ver (html_tags);
            else
            {   context.err ("bad version ");
                context.err (quote (ver));
                context.err (" ignored\n"); } } }

    if (var_.count (MICRODATA VERSION))
    {   ::std::string ver (var_ [MICRODATA VERSION].as < ::std::string > ());
        if (ver.empty ())
        {   context.schema_ver (schema_version (mdr_schema, DEFAULT_SCHEMA_MAJOR, DEFAULT_SCHEMA_MINOR));
            ::std::ostringstream ss;
            ss << "missing schema version; presuming " << DEFAULT_SCHEMA_MAJOR << "." << DEFAULT_SCHEMA_MINOR << "\n";
            context.err (ss.str ()); }
        else
        {   ::std::string::size_type pos = ver.find ('.');
            // boost lexical cast, bless its little cotton socks, doesn't process unsigned char as a number
            if (pos == ::std::string::npos)
                context.schema_ver (schema_version (mdr_schema, static_cast < unsigned char > (lexical < unsigned int > :: cast (ver)), 0));
            else if (pos == 0)
            {   context.schema_ver (schema_version (mdr_schema, DEFAULT_SCHEMA_MAJOR, DEFAULT_SCHEMA_MINOR));
                ::std::ostringstream ss;
                ss << "missing schema version; presuming " << DEFAULT_SCHEMA_MAJOR << "." << DEFAULT_SCHEMA_MINOR << "\n";
                context.err (ss.str ()); }
            else if (pos == ver.length () - 1)
                context.schema_ver (schema_version (mdr_schema, static_cast < unsigned char > (lexical < unsigned int > :: cast (ver.substr (0, pos))), 0));
            else if (pos > 0)
                context.schema_ver (schema_version (mdr_schema, static_cast < unsigned char > (lexical < unsigned int > :: cast (ver.substr (0, pos))),
                                                                static_cast < unsigned char > (lexical < unsigned int > :: cast (ver.substr (pos+1))))); } }

    context.microdata (var_.count (VALIDATION MICRODATAARG));

    if (! context.cgi ())
    {   context.load_css (var_.count (GENERAL CSS_OPTION) == 0);
        context.nochange (var_.count (GENERAL NOCHANGE));
        context.rdf (var_.count (GENERAL RDF));
        context.rel (var_.count (GENERAL REL));
        context.rpt_opens (var_.count (GENERAL RPT));
        context.ssi (var_.count (GENERAL SSI));
        context.persisted (path_in_context (nix_path_to_local (var_ [GENERAL FICHIER].as < ::std::string > ())));

        const long meg = 1024*1024;

        if (! var_.count (GENERAL MAXFILESIZE))
            context.max_file_size (4 * meg);
        else
        {   long max = static_cast < long > (var_ [GENERAL MAXFILESIZE].as < int > ());
            if (max < 0 || (max > (LONG_MAX / meg))) max = DEFAULT_MAX_FILE_SIZE;
            context.max_file_size (max * meg); }

        context.unknown_class (var_.count (GENERAL CLASS));
        if (var_.count (GENERAL CORPUS)) context.corpus (nix_path_to_local (var_ [GENERAL CORPUS].as < ::std::string > ()));
        if (var_.count (GENERAL CUSTOM)) context.custom_elements ( var_ [GENERAL CUSTOM].as < vstr_t > ());
        if (var_.count (GENERAL IGNORED)) context.ignore (var_ [GENERAL IGNORED].as < vstr_t > ());
        if (var_.count (GENERAL LANG)) context.lang (var_ [GENERAL LANG].as < ::std::string > ());
        if (var_.count (GENERAL USER)) context.user (var_ [GENERAL USER].as < ::std::string > ());
        if (var_.count (GENERAL VERBOSE)) context.verbose (static_cast < e_verbose > (var_ [GENERAL VERBOSE].as < int > ()));
        context.process_webmentions (var_.count (GENERAL WEBMENTION));

        context.rfc_1867 (! var_.count (HTML RFC1867));
        context.rfc_1942 (! var_.count (HTML RFC1942));
        context.rfc_1980 (! var_.count (HTML RFC1980));
        context.rfc_2070 (! var_.count (HTML RFC2070));
        context.presume_tags (var_.count (HTML TAGS));
        if (var_.count (HTML TITLE)) context.title (static_cast < unsigned char > (var_ [HTML TITLE].as < int > ()));

        context.links (var_.count (LINKS CHECK));
        context.external (var_.count (LINKS EXTERNAL));
        context.forwarded (var_.count (LINKS FORWARD));
        context.once (var_.count (LINKS ONCE));
        context.revoke (var_.count (LINKS REVOKE));
        context.crosslinks (var_.count (LINKS XLINK));

        if (var_.count (MATH VERSION))
        {   int n = var_ [MATH VERSION].as < int > ();
            if ((n > 0) && (n < 5)) context.math_version (static_cast < e_math_version > (n)); }

        context.mf_export (var_.count (MF EXPORT));

        context.md_export (var_.count (MICRODATA EXPORT));
        context.schema (var_.count (MICRODATA MICRODATAARG));
        if (var_.count (MICRODATA ROOT)) context.export_root (nix_path_to_local (var_ [MICRODATA ROOT].as < ::std::string > ()));
        if (var_.count (MICRODATA VIRTUAL)) context.exports (var_ [MICRODATA VIRTUAL].as < vstr_t > ());

        context.codes (var_.count (NITS CODES));
        context.nids (var_.count (NITS NIDS));
        context.spec (var_.count (NITS SPEC));
        context.nits (var_.count (NITS WATCH));

        if (var_.count (NITS CATASTROPHE))
            for (auto s : var_ [NITS CATASTROPHE].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_catastrophic))
                {   context.err (quote (s));
                    context.err (": no such nit.\n"); }

        if (var_.count (NITS COMMENT))
            for (auto s : var_ [NITS COMMENT].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_comment))
                {   context.err (quote (s));
                    context.err (": no such nit.\n"); }

        if (var_.count (NITS DBG))
            for (auto s : var_ [NITS DBG].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_debug))
                {   context.err (quote (s));
                    context.err (": no such nit.\n"); }

        if (var_.count (NITS ERR))
            for (auto s : var_ [NITS ERR].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_error))
                {   context.err (quote (s));
                    context.err (": no such nit.\n"); }

        if (var_.count (NITS INFO))
            for (auto s : var_ [NITS INFO].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_info))
                {   context.err (quote (s));
                    context.err (": no such nit.\n"); }

        if (var_.count (NITS SILENCE))
            for (auto s : var_ [NITS SILENCE].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_silence))
                {   context.err (quote (s));
                    context.err (": no such nit.\n"); }

        if (var_.count (NITS WARNING))
            for (auto s : var_ [NITS WARNING].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_warning))
                {   context.err (quote (s));
                    context.err (": no such nit.\n"); }

        context.shadow_comment (var_.count (SHADOW COMMENT));
        context.shadow_changed (var_.count (SHADOW CHANGED));
#ifdef NOLYNX
        if (var_.count (SHADOW COPY))
        {   int n = var_ [SHADOW COPY].as < int > ();
            if ((n == 2) || (n == 3)) n = 4;
            context.copy (n); }
#else // NOLYNX
        if (var_.count (SHADOW COPY)) context.copy (var_ [SHADOW COPY].as < int > ());
#endif // NOLYNX
        if (var_.count (SHADOW FICHIER)) context.shadow_persist (nix_path_to_local (var_ [SHADOW FICHIER].as < ::std::string > ()));
        if (var_.count (SHADOW IGNORED)) context.shadow_ignore (var_ [SHADOW IGNORED].as < vstr_t > ());
        context.info (var_.count (SHADOW INFO));
        if (var_.count (SHADOW ROOT)) context.shadow_root (nix_path_to_local (var_ [SHADOW ROOT].as < ::std::string > ()));
        context.shadow_space (var_.count (SHADOW SPACING));
        context.shadow_ssi (var_.count (SHADOW SSI));
        if (var_.count (SHADOW VIRTUAL)) context.virtuals (var_ [SHADOW VIRTUAL].as < vstr_t > ());

        if (var_.count (STATS EXPORT)) context.stats (var_ [STATS EXPORT].as < ::std::string > ());
        context.meta (var_.count (STATS META));
        context.stats_page (var_.count (STATS PAGE));
        context.stats_summary (var_.count (STATS SUMMARY));

        context.svg_mode (static_cast < e_svg_processing_mode > (var_.count (SVG MODE)));
        if (var_.count (SVG MODE))
        {   int n = var_ [SVG MODE].as < int > ();
            if ((n >= 0) && (n < 5)) context.svg_mode (static_cast < e_svg_processing_mode > (n)); }

        if (var_.count (SVG VERSION))
        {   ::std::string ver (var_ [SVG VERSION].as < ::std::string > ());
            if (! ver.empty ())
            {   ::std::string::size_type pos = ver.find ('.');
                if (pos == ::std::string::npos)
                    if (ver.length () == 1) context.svg_version (sv_none);
                    else context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), 0);
                else if (pos == ver.length () - 1) context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), 0);
                else if (pos == 0) context.svg_version (sv_none);
                else context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), lexical < int > :: cast (ver.substr (pos+1))); } }

        if (var_.count (WEBSITE INDEX)) context.index (var_ [WEBSITE INDEX].as < ::std::string > ());
        if (var_.count (WEBSITE EXTENSION)) context.extensions (var_ [WEBSITE EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back ("html"); context.extensions (ex); }
        if (var_.count (WEBSITE ROOT)) context.root (nix_path_to_local (var_ [WEBSITE ROOT].as < ::std::string > ()));
        if (var_.count (WEBSITE SITE)) context.site (var_ [WEBSITE SITE].as < vstr_t > ());
        if (var_.count (WEBSITE VIRTUAL)) context.virtuals (var_ [WEBSITE VIRTUAL].as < vstr_t > ());

        if (! context.cgi ())
        {   if (var_.count (WMIN WRITE)) context.write_path (var_ [WMIN WRITE].as < ::std::string > ());
            if (var_.count (WMIN STUB)) context.stub (var_ [WMIN STUB].as < ::std::string > ());
            if (var_.count (WMIN HOOK)) context.hook (var_ [WMIN HOOK].as < ::std::string > ());
            if (var_.count (WMIN MACROEND)) context.macro_end (var_ [WMIN MACROEND].as < ::std::string > ());
            if (var_.count (WMIN MACROSTART)) context.macro_start (var_ [WMIN MACROSTART].as < ::std::string > ());
            if (var_.count (WMIN PATH)) context.incoming (path_in_context (nix_path_to_local (var_ [WMIN PATH].as < ::std::string > ())));
            if (var_.count (WMIN MENTION)) context.mentions (var_ [WMIN MENTION].as < vstr_t > ());
            if (var_.count (WMIN TEMPLATE)) context.templates ( var_ [WMIN TEMPLATE].as < vstr_t > ());
            if (var_.count (WMIN TEST_HEADER)) context.test_header (var_ [WMIN TEST_HEADER].as < ::std::string > ());

            context.notify (var_.count (WMOUT NOTIFY));
            context.reset (var_.count (WMOUT RESET));
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
        if (var_.count (VALIDATION METANAME)) type_master < t_metaname  > :: extend (var_ [VALIDATION METANAME].as < vstr_t > ());
        if (var_.count (VALIDATION MIMETYPE)) type_master < t_mime > :: extend (var_ [VALIDATION MIMETYPE].as < vstr_t > ());
        if (var_.count (VALIDATION REL)) type_master < t_rel > :: extend (var_ [VALIDATION REL].as < vstr_t > ());
        if (var_.count (VALIDATION SGML)) type_master < t_sgml > :: extend (var_ [VALIDATION SGML].as < vstr_t > (), static_cast < ::std::size_t > (doc_context));

#define TEST_VAR(XX) if (var_.count (VALIDATION #XX)) type_master < t_##XX > :: extend (var_ [VALIDATION #XX].as < vstr_t > ())
        TEST_VAR (action);
        TEST_VAR (align3);
        TEST_VAR (alignplus);
        TEST_VAR (as);
        TEST_VAR (autocapitalise);
        TEST_VAR (autocomplete);
        TEST_VAR (beginfn);
        TEST_VAR (baselineshift);
        TEST_VAR (citype);
        TEST_VAR (cntype);
        TEST_VAR (composite_operator);
        TEST_VAR (decalign);
        TEST_VAR (dingbat);
        TEST_VAR (dir);
        TEST_VAR (display_align);
        TEST_VAR (dominantbaseline);
        TEST_VAR (enterkeyhint);
        TEST_VAR (figalign);
        TEST_VAR (fontname);
        TEST_VAR (halign);
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
        TEST_VAR (microdata_domain);
        TEST_VAR (microdata_root);
        TEST_VAR (namedspace);
        TEST_VAR (namespace);
        TEST_VAR (mathnotation);
        TEST_VAR (ogtype);
        TEST_VAR (paintkeyword);
        TEST_VAR (plusstyle);
        TEST_VAR (pointer_events);
        TEST_VAR (print);
        TEST_VAR (referrer);
        TEST_VAR (renderingintent);
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
        TEST_VAR (vectoreffect_2);
        TEST_VAR (xmlns);
#undef TEST_VAR

        if (context.write_path ().empty ()) context.write_path (context.root ()); }
    schema_version::init (); }

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
        if (env_.count (AUTH_TYPE)) e << AUTH_TYPE ": " << env_ [AUTH_TYPE].as < ::std::string > () << "\n";;
        if (env_.count (CONTENT_TYPE)) e << CONTENT_TYPE ": " << env_ [CONTENT_TYPE].as < ::std::string > () << "\n";
        if (env_.count (CONTENT_LENGTH)) e << CONTENT_LENGTH ": " << env_ [CONTENT_LENGTH].as < ::std::string > () << "\n";

        ::std::string qs (env_ [QUERY_STRING].as < ::std::string > ());
        e << QUERY_STRING ": " << qs << "\n            : " << query_to_switches (qs) << "\n"; }

    ::std::string x (e.str ());
    if (! x.empty ()) res << "\n** Environment:\n" << x << "\n";

    res << "\n** Arguments:\n";

    if (var_.count (HELP)) res << HELP "\n";
    if (var_.count (VERSION)) res << VERSION "\n";

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
        if (var_.count (ENVIRONMENT AUTH_TYPE)) res << ENVIRONMENT AUTH_TYPE ": " << var_ [ENVIRONMENT AUTH_TYPE].as < ::std::string > () << "\n";;
        if (var_.count (ENVIRONMENT CONTENT_TYPE)) res << ENVIRONMENT CONTENT_TYPE ": " << var_ [ENVIRONMENT CONTENT_TYPE].as < ::std::string > () << "\n";
        if (var_.count (ENVIRONMENT CONTENT_LENGTH)) res << ENVIRONMENT CONTENT_LENGTH ": " << var_ [ENVIRONMENT CONTENT_LENGTH].as < ::std::string > () << "\n";

        ::std::string qs (var_ [ENVIRONMENT QUERY_STRING].as < ::std::string > ());
        res << ENVIRONMENT QUERY_STRING ": " << qs << "\n            : " << query_to_switches (qs) << "\n"; }

    if (var_.count (GENERAL CGI)) res << GENERAL CGI "\n";
    if (var_.count (GENERAL CLASS)) res << GENERAL CLASS "\n";
    if (var_.count (GENERAL CORPUS)) res << GENERAL CORPUS ": " << var_ [GENERAL CORPUS].as < ::std::string > () << "\n";
    if (var_.count (GENERAL CSS_OPTION)) res << GENERAL CSS_OPTION "\n";
    if (var_.count (GENERAL CUSTOM)) { res << GENERAL CUSTOM ": "; pvs (res, var_ [GENERAL CUSTOM].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL ENVIRONMENT)) { res << GENERAL ENVIRONMENT ": "; pvs (res, var_ [GENERAL ENVIRONMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL FICHIER)) res << GENERAL FICHIER ": " << var_ [GENERAL FICHIER].as < ::std::string > () << "\n";
    if (var_.count (GENERAL IGNORED)) { res << GENERAL IGNORED ": "; pvs (res, var_ [GENERAL IGNORED].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL LANG)) res << GENERAL LANG ": " << var_ [GENERAL LANG].as < ::std::string > () << "\n";
    if (var_.count (GENERAL MAXFILESIZE)) res << GENERAL MAXFILESIZE ": " << var_ [GENERAL MAXFILESIZE].as < int > () << "\n";
    if (var_.count (GENERAL NOCHANGE)) res << GENERAL NOCHANGE "\n";
    if (var_.count (GENERAL PATH)) res << GENERAL PATH ": " << var_ [GENERAL PATH].as < ::std::string > () << "\n";
    if (var_.count (GENERAL RDF)) res << GENERAL RDF "\n";
    if (var_.count (GENERAL RPT)) res << GENERAL RPT "\n";
    if (var_.count (GENERAL SSI)) res << GENERAL SSI "\n";
    if (var_.count (GENERAL TEST)) res << GENERAL TEST "\n";
    if (var_.count (GENERAL USER)) res << GENERAL USER ": " << var_ [GENERAL USER].as < ::std::string > () << "\n";
    if (var_.count (GENERAL VERBOSE)) res << GENERAL VERBOSE ": " << var_ [GENERAL VERBOSE].as < int > () << "\n";
    if (var_.count (GENERAL WEBMENTION)) res << GENERAL WEBMENTION "\n";

    if (var_.count (HTML TAGS)) res << HTML TAGS "\n";
    if (var_.count (HTML RFC1867)) res << HTML RFC1867 "\n";
    if (var_.count (HTML RFC1942)) res << HTML RFC1942 "\n";
    if (var_.count (HTML RFC1980)) res << HTML RFC1980 "\n";
    if (var_.count (HTML RFC2070)) res << HTML RFC2070 "\n";
    if (var_.count (HTML SNIPPET)) res << HTML SNIPPET ": " << var_ [HTML SNIPPET].as < ::std::string > () << "\n";
    if (var_.count (HTML TITLE)) res << HTML TITLE ": " << var_ [HTML TITLE].as < int > () << "\n";
    if (var_.count (HTML VERSION)) res << HTML VERSION ": " << var_ [HTML VERSION].as < ::std::string > () << "\n";

    if (var_.count (LINKS EXTERNAL)) res << LINKS EXTERNAL "\n";
    if (var_.count (LINKS FORWARD)) res << LINKS FORWARD "\n";
    if (var_.count (LINKS CHECK)) res << LINKS CHECK "\n";
    if (var_.count (LINKS ONCE)) res << LINKS ONCE "\n";
    if (var_.count (LINKS REVOKE)) res << LINKS REVOKE "\n";
    if (var_.count (LINKS XLINK)) res << LINKS XLINK "\n";

    if (var_.count (MATH VERSION)) res << MATH VERSION ": " << var_ [MATH VERSION].as < int > () << "\n";

    if (var_.count (NITS CATASTROPHE)) { res << NITS CATASTROPHE ": "; pvs (res, var_ [NITS CATASTROPHE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS COMMENT)) { res << NITS COMMENT ": "; pvs (res, var_ [NITS COMMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS DBG)) { res << NITS DBG ": "; pvs (res, var_ [NITS DBG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS ERR)) { res << NITS ERR ": "; pvs (res, var_ [NITS ERR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS INFO)) { res << NITS INFO ": "; pvs (res, var_ [NITS INFO].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS NIDS)) res << NITS NIDS "\n";
    if (var_.count (NITS SILENCE)) { res << NITS SILENCE ": "; pvs (res, var_ [NITS SILENCE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS SPEC)) res << NITS SPEC "\n";
    if (var_.count (NITS WARNING)) { res << NITS WARNING ": "; pvs (res, var_ [NITS WARNING].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS WATCH)) res << NITS WATCH "\n";

    if (var_.count (MF EXPORT)) res << MF EXPORT "\n";
    if (var_.count (MF VERIFY)) res << MF VERIFY "\n";
    if (var_.count (MF VERSION)) res << MF VERSION ": " << var_ [MF VERSION].as < int > () << "\n";

    if (var_.count (MICRODATA EXPORT)) res << MICRODATA EXPORT "\n";
    if (var_.count (MICRODATA MICRODATAARG)) res << MICRODATA MICRODATAARG "\n";
    if (var_.count (MICRODATA ROOT)) res << MICRODATA ROOT ": " << var_ [MICRODATA ROOT].as < ::std::string > () << "\n";
    if (var_.count (MICRODATA VERSION)) res << MICRODATA VERSION ": " << var_ [MICRODATA VERSION].as < ::std::string > () << "\n";
    if (var_.count (MICRODATA VIRTUAL)) { res << MICRODATA VIRTUAL ": "; pvs (res, var_ [MICRODATA VIRTUAL].as < vstr_t > ()); res << "\n"; }

    if (var_.count (SHADOW COMMENT)) res << SHADOW COMMENT "\n";
    if (var_.count (SHADOW COPY)) res << SHADOW COPY ": " << var_ [SHADOW COPY].as < int > () << "\n";
    if (var_.count (SHADOW FICHIER)) res << SHADOW FICHIER ": " << var_ [SHADOW FICHIER].as < ::std::string > () << "\n";
    if (var_.count (SHADOW CHANGED)) res << SHADOW CHANGED "\n";
    if (var_.count (SHADOW IGNORED)) { res << SHADOW IGNORED ": "; pvs (res, var_ [SHADOW IGNORED].as < vstr_t > ()); res << "\n"; }
    if (var_.count (SHADOW ROOT)) res << SHADOW ROOT ": " << var_ [SHADOW ROOT].as < ::std::string > () << "\n";
    if (var_.count (SHADOW SPACING)) res << SHADOW SPACING "\n";
    if (var_.count (SHADOW SSI)) res << SHADOW SSI "\n";
    if (var_.count (SHADOW VIRTUAL)) { res << SHADOW VIRTUAL ": "; pvs (res, var_ [SHADOW VIRTUAL].as < vstr_t > ()); res << "\n"; }

    if (var_.count (STATS EXPORT)) res << STATS EXPORT ": " << var_ [STATS EXPORT].as < ::std::string > () << "\n";
    if (var_.count (STATS META)) res << STATS META "\n";
    if (var_.count (STATS PAGE)) res << STATS PAGE "\n";
    if (var_.count (STATS SUMMARY)) res << STATS SUMMARY "\n";

    if (var_.count (SVG MODE)) res << SVG MODE "\n";
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
    RPT_VAR (action);
    RPT_VAR (align3);
    RPT_VAR (alignplus);
    RPT_VAR (as);
    RPT_VAR (autocapitalise);
    RPT_VAR (autocomplete);
    RPT_VAR (baselineshift);
    RPT_VAR (beginfn);
    RPT_VAR (citype);
    RPT_VAR (cntype);
    RPT_VAR (composite_operator);
    RPT_VAR (decalign);
    RPT_VAR (dingbat);
    RPT_VAR (dir);
    RPT_VAR (display_align);
    RPT_VAR (dominantbaseline);
    RPT_VAR (enterkeyhint);
    RPT_VAR (figalign);
    RPT_VAR (fontname);
    RPT_VAR (halign);
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
    RPT_VAR (microdata_domain);
    RPT_VAR (microdata_root);
    RPT_VAR (namedspace);
    RPT_VAR (namespace);
    RPT_VAR (mathnotation);
    RPT_VAR (ogtype);
    RPT_VAR (paintkeyword);
    RPT_VAR (plusstyle);
    RPT_VAR (pointer_events);
    RPT_VAR (print);
    RPT_VAR (referrer);
    RPT_VAR (renderingintent);
    RPT_VAR (rules);
    RPT_VAR (sandbox);
    RPT_VAR (shape7);
    RPT_VAR (shape_rendering);
    RPT_VAR (ssi);
    RPT_VAR (ssi_comparison);
    RPT_VAR (ssi_encoding);
    RPT_VAR (ssi_env);
    RPT_VAR (svg_align);
    RPT_VAR (svg_display);
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
    RPT_VAR (vectoreffect_2);
    RPT_VAR (xmlns);
#undef RPT_VAR

    if (var_.count (WEBSITE EXTENSION)) { res << WEBSITE EXTENSION ": "; pvs (res, var_ [WEBSITE EXTENSION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WEBSITE INDEX)) res << WEBSITE INDEX ": " << var_ [WEBSITE INDEX].as < ::std::string > () << "\n";
    if (var_.count (WEBSITE SITE)) { res << WEBSITE SITE ": "; pvs (res, var_ [WEBSITE SITE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WEBSITE ROOT)) res << WEBSITE ROOT ": " << var_ [WEBSITE ROOT].as < ::std::string > () << "\n";
    if (var_.count (WEBSITE VIRTUAL)) { res << WEBSITE VIRTUAL ": "; pvs (res, var_ [WEBSITE VIRTUAL].as < vstr_t > ()); res << "\n"; }

    if (var_.count (WMIN WRITE)) { res << WMIN WRITE ": "; var_ [WMIN WRITE].as < ::std::string > (); res << "\n"; }
    if (var_.count (WMIN STUB)) res << WMIN STUB ": " << var_ [WMIN STUB].as < ::std::string > () << "\n";
    if (var_.count (WMIN HOOK)) res << WMIN HOOK ": " << var_ [WMIN HOOK].as < ::std::string > () << "\n";
    if (var_.count (WMIN MACROEND)) res << WMIN MACROEND ": " << var_ [WMIN MACROEND].as < ::std::string > () << "\n";
    if (var_.count (WMIN MACROSTART)) res << WMIN MACROSTART ": " << var_ [WMIN MACROSTART].as < ::std::string > () << "\n";
    if (var_.count (WMIN PATH)) res << WMIN PATH ": " << var_ [WMIN PATH].as < ::std::string > () << "\n";
    if (var_.count (WMIN MENTION)) { res << WMIN MENTION ": "; pvs (res, var_ [WMIN MENTION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WMIN TEMPLATE)) { res << WMIN TEMPLATE ": "; pvs (res, var_ [WMIN TEMPLATE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WMIN TEST_HEADER)) res << WMIN TEST_HEADER ": " << var_ [WMIN TEST_HEADER].as < ::std::string > () << "\n";

    if (var_.count (WMOUT CLEAR)) res << WMOUT CLEAR "\n";
    if (var_.count (WMOUT NOTIFY)) res << WMOUT NOTIFY "\n";
    if (var_.count (WMOUT RESET)) res << WMOUT RESET "\n";
    if (var_.count (WMOUT SECRET)) res << WMOUT SECRET ": " << var_ [WMOUT SECRET].as < ::std::string > () << "\n";

    return res.str (); }
