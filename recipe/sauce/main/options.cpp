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

#include "main/standard.h"
#include "main/options.h"
#include "type/type.h"
#include "main/args.h"
#include "utility/filesystem.h"
#include "utility/lexical.h"
#include "feedback/nitpick.h"
#include "ontology/ontology_version.h"
#include "attribute/attributes.h"
#include "element/elem.h"
#include "element/element_classes.h"
#include "url/url_sanitise.h"
#include "parser/html_version.h"
#include "spell/spell.h"

#define GOTCHA  "WARNING: The examination of RDFa and ontologies (but for schema.org &\n" \
                "the living standard) is experimental, and even less trustworthy than\n" \
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
            "bad semantics, odd ontologies, slobby stuff, abhorant rudeness, etc..\n";
    ::std::ostringstream waste_of_space;
    waste_of_space << aid;
    res +=  waste_of_space.str ();
    res +=  "\n\n"
            "Configuration file section names precede each switch dot above (e.g.\n"
            GENERAL_ ", " LINK_ "," WEBSITE_ "\n"
            ", etc.). Option names follow them. For example:\n\n"
            "[" GENERAL_ "]\n"
            VERBOSE "=2\n\n"
            "[" LINK_ "]\n"
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

bool options::get_css_level (int& n, nitpick& nits, const char* opt, const char* name, const int maxlevel, const bool accept_1)
{   VERIFY_NOT_NULL (opt, __FILE__, __LINE__);
    VERIFY_NOT_NULL (name, __FILE__, __LINE__);
    if (var_.count (opt))
    {   n = var_ [opt].as < int > ();
        switch (n)
        {   case 0 : return true;
            case 1 : if (accept_1) { n = 3; return true; } break;
            case 2 : if (accept_1 && (maxlevel > 3)) { n = 4; return true; } break;
            case 3 :
            case 4 :
            case 5 :
            case 6 : if (n <= maxlevel) return true; break;
            default : break; }
        nits.pick (nit_config_version, es_warning, ec_init, "ignoring non-existent CSS ", name, " level ", n); }
    return false; }

void options::yea_nay (context_t& (context_t::*fn) (const bool ), nitpick& nits, const char* yea, const char* nay)
{   VERIFY_NOT_NULL (fn, __FILE__, __LINE__);
    const bool on = var_ [yea].as <bool> ();
    const bool off = var_ [nay].as <bool> ();
    if (off)
    {   if (on) nits.pick (nit_yea_nay, es_info, ec_init, "when both ", nay, " and ", yea, " are used, ", nay, " applies");
        (context.*fn) (false); }
    else if (on) (context.*fn) (true); }

void options::parse (nitpick& nits, int argc, char* const * argv)
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
        (ONTOLOGY LIST, ::boost::program_options::bool_switch (), "List known ontology schema for microdata andor RDFa, then exit.")
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
        (GENERAL CSS_OPTION, ::boost::program_options::bool_switch (), "Process .css files.")
        (GENERAL DONT CSS_OPTION, ::boost::program_options::bool_switch (), "Do not process .css files.")
#ifdef NO_BOOST_REGEX
        (GENERAL EXCLUDE, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore files that match this posix regular expression; may be repeated.")
#endif // NO_BOOST_REGEX
#ifdef NO_FRED
        (GENERAL THREAD ",n", ::boost::program_options::value < int > (), "Number of threads (default appropriate for the hardware).")
#endif // NO_FRED
        (GENERAL MACROSTART, ::boost::program_options::value < ::std::string > () -> default_value ("{{"), "Start of template macro (by default, the '{{' in '{{macro}}').")
        (GENERAL MACROEND, ::boost::program_options::value < ::std::string > () -> default_value ("}}"), "End of template macro (by default, the '}}' in '{{macro}}').")

        (CSS COND_RULE, ::boost::program_options::value < int > (), "CSS Conditional Rule level (0, 3, 4, or 5).")
        (CSS LIST, ::boost::program_options::value < int > (), "CSS Lists and Counters level (0 or 3).")
        (CSS TEXT_ARG, ::boost::program_options::value < int > (), "CSS Text level (0, 3, or 4).")

        (JSONLD EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "Extension for JSON-LD files; may be repeated.")
        (JSONLD VERIFY, ::boost::program_options::bool_switch (), "Experimental: Verify JSON-LD.")
        (JSONLD DONT VERIFY, ::boost::program_options::bool_switch (), "Do not verify JSON-LD.")
        (JSONLD VERSION, ::boost::program_options::value < ::std::string > (), "Presume this version of JSON-LD (1.0 or 1.1, default 1.0).")

#ifdef NO_BOOST_REGEX
        (LINKS PRETEND, ::boost::program_options::value < vstr_t > () -> composing (), "Pretend files that match this posix regular expression exist; may be repeated")
#endif // NO_BOOST_REGEX

        (NITS CACHE, ::boost::program_options::value < ::std::string > (), "Output nits on cache usage of filenames containing argument (no wildcards, except use \"*\" for all; empty for no report).")
        (NITS SPEC, ::boost::program_options::bool_switch (), "Output nits in test spec format (requires -T).")
        (NITS DONT SPEC, ::boost::program_options::bool_switch (), "Do not output nits in test spec format.")
        (NITS XXX, ::boost::program_options::value < ::std::string > (), "Output nits on cache usage from page names containing argument (empty for no report); may be combined with " NITS CACHE ".")

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
        (GENERAL CLASS, ::boost::program_options::bool_switch (), "Report unrecognised classes (requires CSS).")
        (GENERAL DONT CLASS, ::boost::program_options::bool_switch (), "Do not report unrecognised classes.")
        (GENERAL CLASSIC, ::boost::program_options::bool_switch (), "Report all classes used, not just those in .CSS files (requires --" GENERAL CLASS ").")
        (GENERAL DONT CLASSIC, ::boost::program_options::bool_switch (), "Do not report all classes used.")
        (GENERAL CGI ",W", ::boost::program_options::bool_switch (), "Process HTML snippets (for OpenBSD's httpd <FORM METHOD=GET ...>; disables most features).")
        (GENERAL DONT CGI, ::boost::program_options::bool_switch (), "Process a local static website.")
        (GENERAL CUSTOM, ::boost::program_options::value < vstr_t > () -> composing (), "Define a custom element for checking the 'is' attribute; may be repeated.")
        (GENERAL DATAPATH ",p", ::boost::program_options::value < ::std::string > () -> default_value ("." PROG), "Root directory for most " PROG " files.")
        (GENERAL DEFTHRD ",N", ::boost::program_options::value < int > (), "If no setting specifies the thread count, set it to this.")
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

        (CSS ADJUST, ::boost::program_options::value < int > (), "CSS Colour Adjust level (0 or 3).")
        (CSS ANIMATION, ::boost::program_options::value < int > (), "CSS Animation level (0 or 3).")
        (CSS BACKGROUND, ::boost::program_options::value < int > (), "CSS Background Borders level (0 or 3).")
        (CSS BOX_ALIGN, ::boost::program_options::value < int > (), "CSS Box Alignment level (0 or 3).")
        (CSS BOX_MODEL, ::boost::program_options::value < int > (), "CSS Box Model level (0, 3 or 4).")
        (CSS BOX_SIZING, ::boost::program_options::value < int > (), "CSS Box Sizing level (0 or 3).")
        (CSS CASCADE, ::boost::program_options::value < int > (), "CSS Cascade & Inheritance level (0, 3, 4, 5 or 6).")
        (CSS COLOUR, ::boost::program_options::value < int > (), "CSS Colour level (0, 3, 4, or 5).")
        (CSS COMPOSITING, ::boost::program_options::value < int > (), "CSS Compositing and Blending level (0 or 3).")
        (CSS CONTAIN, ::boost::program_options::value < int > (), "CSS Contain level (0, 3, 4, or 5).")
        (CSS CS, ::boost::program_options::value < int > (), "CSS Counter Style level (0 or 3).")
        (CSS CUSTOM, ::boost::program_options::value < int > (), "CSS Custom level (0 or 3).")
        (CSS DEVICE, ::boost::program_options::value < int > (), "CSS Device Adaption level (0 or 3).")
        (CSS DISPLAY, ::boost::program_options::value < int > (), "CSS Display level (0 or 3).")
        (CSS EASE, ::boost::program_options::value < int > (), "CSS Ease level (0 or 3).")
        (CSS EXCLUDE, ::boost::program_options::value < int > (), "CSS Exclusions level (0 or 3).")
        (CSS EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "CSS files have this extension (default css); may be repeated.")
        (CSS EXTERNAL, ::boost::program_options::bool_switch (), "Nitpick css files imported from external sites.")
        (CSS DONT EXTERNAL, ::boost::program_options::bool_switch (), "Do not nitpick imported CSS files.")
        (CSS FBL, ::boost::program_options::value < int > (), "CSS Flexible Box Layout level (0 or 3).")
        (CSS FILTER, ::boost::program_options::value < int > (), "CSS Filter Effects level (0 or 3).")
        (CSS FONT, ::boost::program_options::value < int > (), "CSS Font level (0, 3, 4, or 5).")
        (CSS FRAG, ::boost::program_options::value < int > (), "CSS Fragmentation level (0, 3, or 4).")
        (CSS GRID, ::boost::program_options::value < int > (), "CSS Grid level (0, 3, or 4).")
        (CSS IMAGE, ::boost::program_options::value < int > (), "CSS Images level (0, 3, or 4).")
        (CSS INLINE, ::boost::program_options::value < int > (), "CSS Inline Layout level (0 or 3).")
        (CSS LINE_GRID, ::boost::program_options::value < int > (), "CSS Line Grid level (0 or 3).")
        (CSS LOGIC, ::boost::program_options::value < int > (), "CSS Logical Properties and Values level (0 or 3).")
        (CSS MASKING, ::boost::program_options::value < int > (), "CSS Masking level (0 or 3).")
        (CSS MEDIA, ::boost::program_options::value < int > (), "CSS Media level (0, 3, 4, or 5).")
        (CSS MOBILE, ::boost::program_options::bool_switch (), "Notify if some CSS conflicts with the CSS Mobile Profile.")
        (CSS DONT MOBILE, ::boost::program_options::bool_switch (), "Do not notify CSS Mobile Profile matters.")
        (CSS MULTI_COLUMN, ::boost::program_options::value < int > (), "CSS Multi-Column level (0 or 3).")
        (CSS NAMESPACE, ::boost::program_options::value < int > (), "CSS Namespace level (0 or 3).")
        (CSS OVERFLOH, ::boost::program_options::value < int > (), "CSS Overflow level (0 or 3).")
        (CSS PRINT, ::boost::program_options::bool_switch (), "Notify if some CSS conflicts with the CSS Print Profile.")
        (CSS DONT PRINT, ::boost::program_options::bool_switch (), "No not notify CSS Print Profile matters.")
        (CSS POSITION, ::boost::program_options::value < int > (), "CSS Positions level (0 or 3).")
        (CSS SCROLLBAR, ::boost::program_options::value < int > (), "CSS Scrollbar Styling level (0 or 3).")
        (CSS SELECTOR, ::boost::program_options::value < int > (), "CSS Selector level (0, 3, or 4).")
        (CSS SHAPE, ::boost::program_options::value < int > (), "CSS Shapes level (0, 3, or 4).")
        (CSS SNAP, ::boost::program_options::value < int > (), "CSS Scroll Snap level (0 or 3).")
        (CSS SPEECH, ::boost::program_options::value < int > (), "CSS Speech level (0 or 3).")
        (CSS STYLE, ::boost::program_options::value < int > (), "CSS Style level (0 or 3).")
        (CSS SYNTAX, ::boost::program_options::value < int > (), "CSS Syntax level (0 or 3).")
        (CSS TABLE, ::boost::program_options::value < int > (), "CSS Table level (0 or 3).")
        (CSS TEXT_DEC, ::boost::program_options::value < int > (), "CSS Text Decoration level (0, 3, or 4).")
        (CSS TRANSFORM, ::boost::program_options::value < int > (), "CSS Transform level (0, 3 or 4).")
        (CSS TRANSITION, ::boost::program_options::value < int > (), "CSS Transitions level (0 or 3).")
        (CSS TV, ::boost::program_options::bool_switch (), "Notify if some CSS conflicts with the CSS TV Profile.")
        (CSS DONT TV, ::boost::program_options::bool_switch (), "No notify CSS TV Profile matters.")
        (CSS UI, ::boost::program_options::value < int > (), " CSS UI level (0, 3, or 4).")
        (CSS VALUE, ::boost::program_options::value < int > (), "CSS Values and Units level (0, 3, or 4).")
        (CSS VERIFY, ::boost::program_options::bool_switch (), "Process .css files.")
        (CSS DONT VERIFY, ::boost::program_options::bool_switch (), "Do not process .css files.")
        (CSS VERSION, ::boost::program_options::value < ::std::string > (),
            "Select no CSS (0); "
            "a specific version (1, 2.0, 2.1, 2.2); "
            "all modules of a given level (3, 4, 5, 6); "
            "solid snapshot modules by year (07, 10, 15, 17, 18, 20, 21, 22, 23); "
            "solid and wobbly snapshot modules by year (15+, 17+, 18+, 20+, 21+, 22+, 23+); "
            "all snapshot modules by year (15++, 17++, 18++, 20++, 21++, 22++, 23++): "
            "default appropriate for HTML version.")
        (CSS WC, ::boost::program_options::value < int > (), "CSS Will Change level (0 or 3).")
        (CSS WRITING, ::boost::program_options::value < int > (), "CSS Writing Mode level (0, 3 or 4).")

        (HTML FORCE, ::boost::program_options::bool_switch (), "When <!DOCTYPE...> is missing, forcibly presume HTML version as per --html.version.")
        (HTML DONT FORCE, ::boost::program_options::bool_switch (), "When <!DOCTYPE...> is missing, correctly presume HTML 1 or HTML tags, as per --html.tags.")
        (HTML IE, ::boost::program_options::bool_switch (), "Ignore certain naughtitudes accepted by versions of Internet Explorer.")
        (HTML DONT IE, ::boost::program_options::bool_switch (), "Mention certain naughtitudes accepted by versions of Internet Explorer.")
        (HTML RFC1867, ::boost::program_options::bool_switch (), "Consider RFC 1867 (INPUT=FILE) when processing HTML 2.0.")
        (HTML DONT RFC1867, ::boost::program_options::bool_switch (), "Ignore RFC 1867 (INPUT=FILE) when processing HTML 2.0.")
        (HTML RFC1942, ::boost::program_options::bool_switch (), "Consider RFC 1867 RFC 1942 (tables) when processing HTML 2.0.")
        (HTML DONT RFC1942, ::boost::program_options::bool_switch (), "Ignore RFC 1867 RFC 1942 (tables) when processing HTML 2.0.")
        (HTML RFC1980, ::boost::program_options::bool_switch (), "Consider RFC 1867 RFC 1980 (client side image maps) when processing HTML 2.0.")
        (HTML DONT RFC1980, ::boost::program_options::bool_switch (), "Ignore RFC 1867 RFC 1980 (client side image maps) when processing HTML 2.0.")
        (HTML RFC2070, ::boost::program_options::bool_switch (), "Consider RFC 1867 RFC 2070 (internationalisation) when processing HTML 2.0.")
        (HTML DONT RFC2070, ::boost::program_options::bool_switch (), "Ignore RFC 1867 RFC 2070 (internationalisation) when processing HTML 2.0.")
        (HTML SAFARI, ::boost::program_options::bool_switch (), "Ignore certain naughtitudes accepted by versions of Safari.")
        (HTML DONT SAFARI, ::boost::program_options::bool_switch (), "Mention certain naughtitudes accepted by versions of Safari.")
        (HTML TAGS, ::boost::program_options::bool_switch (), "Presume HTML with no DOCTYPE is HTML Tags (CERN version).")
        (HTML DONT TAGS, ::boost::program_options::bool_switch (), "Presume HTML with no DOCTYPE is HTML 1.0.")
        (HTML TITLE ",z", ::boost::program_options::value < int > () -> default_value (MAX_IDEAL_TITLE_LENGTH), "Maximum advisable length of <TITLE> text.")
        (HTML VERSION, ::boost::program_options::value < ::std::string > (),
            "Set the specific version of HTML with DOCTYPE (default '2022/7/1'). "
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
#ifndef NO_BOOST_REGEX
        (LINKS PRETEND, ::boost::program_options::value < vstr_t > () -> composing (), "Pretend files that match this posix regular expression exist; may be repeated")
#endif // NO_BOOST_REGEX
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

        (NITS ABHORRENT, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as an abhorrence; may be repeated.")
        (NITS CATASTROPHE, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a catastrophe; may be repeated.")
        (NITS COMMENT, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a comment; may be repeated.")
        (NITS DBG, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a debug message; may be repeated.")
        (NITS ERR, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as an error; may be repeated.")
        (NITS EXTRA, ::boost::program_options::bool_switch (), "Report additional nits.")
        (NITS DONT EXTRA, ::boost::program_options::bool_switch (), "Do not report additional nits.")
        (NITS FORMAT, ::boost::program_options::value < ::std::string > (), "Output nits in this format: \"html\", \"text\" (default), or a filename (see docs for format).")
        (NITS INFO, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as info; may be repeated.")
        (NITS NIDS, ::boost::program_options::bool_switch (), "Output nit identifiers (used to recategorise nits).")
        (NITS DONT NIDS, ::boost::program_options::bool_switch (), "Do not output nit identifiers.")
        (NITS OVERRIDE ",P", ::boost::program_options::value < ::std::string > (), "Output nits in this format (overrides " NITS FORMAT "; for automation).")
        (NITS QUOTE, ::boost::program_options::value < ::std::string > (), "Quote nits in this format: \"c\", \"csv\", \"double\", \"html\", \"none\" (default), or \"single\".")
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
    {   const e_ontology es = static_cast < e_ontology > (i);
        if (is_faux_schema (es)) continue;
        if (get_ontology_version_count (es) < 2) continue;
        ::std::string naam (ontology_names.get (es, ONTOLOGY_NAME));
        ::std::string arg = ONTOLOGY;
        arg += naam;
        ::std::string desc (ontology_names.get (es, ONTOLOGY_DESCRIPTION));
        desc += ", ";
        if (get_ontology_version_count (es) == 2)
        {   desc += "either ";
            desc += get_first_ontology_version (es).ver ();
            desc += " or "; }
        else
        {   desc += "between ";
            desc += get_first_ontology_version (es).ver ();
            desc += " and "; }
        desc += get_last_ontology_version (es).ver ();
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
        (VALIDATION FF, ::boost::program_options::value < vstr_t > () -> composing (), "Add a font feature extension (CSS).")
        (VALIDATION FV, ::boost::program_options::value < vstr_t > () -> composing (), "Add a font variation extension (CSS).")
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
        {   context.cgi (true).article (false).body (false).cased (false).classic (false).crosslinks (false).example (false).ext_css (false)
                .external (false).forwarded (false).ie (false).icu (true).info (true).jsonld (false).links (false).load_css (false).main (false)
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
        {   const e_ontology es = static_cast < e_ontology > (i);
            if (is_faux_schema (es)) continue;
            res += ontology_names.get (es, ONTOLOGY_NAME);
            const ontology_version x (get_first_ontology_version (es));
            const ontology_version y (get_last_ontology_version (es));
            const int count = get_ontology_version_count (es);
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
        context.article (false).body (false).cased (false).classic (false).crosslinks (false).example (false).external (false).ext_css (false).forwarded (false)
            .icu (true).info (false).jsonld (false).links (false).load_css (true).main (false).md_export (false).meta (false).mf_verify (false)
            .microdata (false).nids (true).nits (false).nits_nits_nits (true).not_root (false).once (false).presume_tags (false).progress (false)
            .rdfa (false).rel (false).revoke (false).rfc_1867 (true).rfc_1942 (true).rfc_1980 (true).rfc_2070 (true).rpt_opens (false).schema (true)
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

    if (var_.count (HTML VERSION) != 0)
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
            else switch (lexical < int > :: cast (ver))
            {   case 1 : context.html_ver (html_1); break;
                case 2 : context.html_ver (html_2); break;
                case 3 : context.html_ver (html_3_2); break;
                case 4 : context.html_ver (html_4_1); break;
                case 5 : context.html_ver (html_default); break;
                default : 
                    if (ver == "+") context.html_ver (html_plus);
                    else if (compare_no_case (ver, "plus")) context.html_ver (html_plus);
                    else if (compare_no_case (ver, "tags")) context.html_ver (html_tags);
                    else nits.pick (nit_config_version, es_error, ec_init, quote (ver), ": bad HTML version"); } } }
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
    {   const e_ontology es = static_cast < e_ontology > (i);
        if (is_faux_schema (es)) continue;
        if (get_ontology_version_count (es) < 2) continue;
        const ::std::string naam (ontology_names.get (es, ONTOLOGY_NAME));
        ::std::string arg (ONTOLOGY);
        arg += naam;
        if (var_.count (arg))
        {   ::std::string ver (trim_the_lot_off (var_ [arg].as < ::std::string > ()));
            const ::std::string::size_type pos = ver.find ('.');
            // boost lexical cast, bless its little cotton socks, doesn't process unsigned char as a number
            ontology_version x (error_schema);
            if (pos == ::std::string::npos)
                x = ontology_version (es, GSL_NARROW_CAST < unsigned char > (lexical < unsigned int > :: cast (ver)), 0);
            else if (pos == 0)
                nits.pick (nit_config_version, es_warning, ec_init, "missing ontology major version");
            else if (pos == ver.length () - 1)
                x = ontology_version (es, GSL_NARROW_CAST < unsigned char > (lexical < unsigned int > :: cast (ver.substr (0, pos))), 0);
            else if (pos > 0)
                x = ontology_version (es, GSL_NARROW_CAST < unsigned char > (lexical < unsigned int > :: cast (ver.substr (0, pos))),
                                                              GSL_NARROW_CAST < unsigned char > (lexical < unsigned int > :: cast (ver.substr (pos+1))));
            if (x.invalid ())
                nits.pick (nit_config_version, es_error, ec_init, "invalid ontology ", quote (x.name ()), " version; use " ONTOLOGY LIST " to get a list of known versions.");
            else if (! set_default_ontology_version (x.root (), x.mjr (), x.mnr ()))
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
        {   const e_severity sev = decode_severity (nits, var_ [GENERAL ERR].as < ::std::string > ());
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

        if (var_.count (CSS EXTENSION)) context.css_extension (var_ [CSS EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back ("css"); context.css_extension (ex); }
        yea_nay (&context_t::load_css, nits, CSS VERIFY, CSS DONT VERIFY);
        yea_nay (&context_t::ext_css, nits, CSS EXTERNAL, CSS DONT EXTERNAL);
        
        if (var_.count (CSS VERSION) != 0)
        {   ::std::string ver (var_ [CSS VERSION].as < ::std::string > ());
            if (ver.empty ()) nits.pick (nit_config_version, es_warning, ec_init, "missing CSS version");
            else context.css_version (examine_value < t_css_version > (nits, html_default, ver)); }

        int n = 0;
        if (get_css_level (n, nits, CSS ADJUST, "Colour Adjust", 4)) context.css_adjust (n);
        if (get_css_level (n, nits, CSS ANIMATION, "Animation", 4)) context.css_animation (n);
        if (get_css_level (n, nits, CSS BACKGROUND, "Background Border", 3, true)) context.css_background (n);
        if (get_css_level (n, nits, CSS BOX_ALIGN, "Background Alignment", 3)) context.css_box_alignment (n);
        if (get_css_level (n, nits, CSS BOX_MODEL, "Background Model", 4)) context.css_box_model (n);
        if (get_css_level (n, nits, CSS BOX_SIZING, "Background Sizing", 3)) context.css_box_sizing (n);
        if (get_css_level (n, nits, CSS CASCADE, "Cascade & Inheritance", 6)) context.css_cascade (n);
        if (get_css_level (n, nits, CSS COLOUR, "Colour", 5)) context.css_colour (n);
        if (get_css_level (n, nits, CSS COMPOSITING, "Compositing", 3, true)) context.css_compositing (n);
        if (get_css_level (n, nits, CSS COND_RULE, "Conditional Rule", 5)) context.css_conditional_rule (n);
        if (get_css_level (n, nits, CSS CONTAIN, "Contain", 5)) context.css_contain (n);
        if (get_css_level (n, nits, CSS CS, "Counter Style", 3)) context.css_counter_style (n);
        if (get_css_level (n, nits, CSS CUSTOM, "Custom", 3, true)) context.css_custom (n);
        if (get_css_level (n, nits, CSS DEVICE, "Device Adaption", 3)) context.css_device (n);
        if (get_css_level (n, nits, CSS DISPLAY, "Display", 3)) context.css_display (n);
        if (get_css_level (n, nits, CSS EASE, "Ease", 4, true)) context.css_ease (n);
        if (get_css_level (n, nits, CSS EXCLUDE, "Exclusions", 3)) context.css_exclude (n);
        if (get_css_level (n, nits, CSS FBL, "Flexible Box Layout", 3)) context.css_fbl (n);
        if (get_css_level (n, nits, CSS FILTER, "Filter Effects", 3)) context.css_filter (n);
        if (get_css_level (n, nits, CSS FONT, "Font", 5)) context.css_font (n);
        if (get_css_level (n, nits, CSS FRAG, "Fragmentation", 4)) context.css_fragmentation (n);
        if (get_css_level (n, nits, CSS GRID, "Grid", 4)) context.css_grid (n);
        if (get_css_level (n, nits, CSS IMAGE, "Image", 4)) context.css_image (n);
        if (get_css_level (n, nits, CSS INLINE, "Inline Layout", 3)) context.css_inline (n);
        if (get_css_level (n, nits, CSS LIST, "Lists and Counters", 3)) context.css_lists (n);
        if (get_css_level (n, nits, CSS LINE_GRID, "Line Grid", 3)) context.css_line_grid (n);
        if (get_css_level (n, nits, CSS LOGIC, "Logical Properties and Values", 3)) context.css_logic (n);
        if (get_css_level (n, nits, CSS MASKING, "Masking", 3)) context.css_masking (n);
        if (get_css_level (n, nits, CSS MEDIA, "Media", 5)) context.css_media (n);
        yea_nay (&context_t::mobile_profile, nits, CSS MOBILE, CSS DONT MOBILE);
        if (get_css_level (n, nits, CSS NAMESPACE, "Namespace", 3)) context.css_namespace (n);
        if (get_css_level (n, nits, CSS OVERFLOH, "Overflow", 3)) context.css_overflow (n);
        if (get_css_level (n, nits, CSS POSITION, "Overflow", 3)) context.css_position (n);
        yea_nay (&context_t::print_profile, nits, CSS PRINT, CSS DONT PRINT);
        if (get_css_level (n, nits, CSS SCROLLBAR, "Scrollbar Styling", 4)) context.css_scrollbar (n);
        if (get_css_level (n, nits, CSS SELECTOR, "Selector", 4)) context.css_selector (n);
        if (get_css_level (n, nits, CSS SHAPE, "Shape", 4)) context.css_shape (n);
        if (get_css_level (n, nits, CSS SNAP, "Snap", 3)) context.css_snap (n);
        if (get_css_level (n, nits, CSS SPEECH, "Speech", 3)) context.css_speech (n);
        if (get_css_level (n, nits, CSS STYLE, "Style", 3)) context.css_style (n);
        if (get_css_level (n, nits, CSS SYNTAX, "Syntax", 3)) context.css_syntax (n);
        if (get_css_level (n, nits, CSS TEXT_ARG, "Text", 4)) context.css_text (n);
        if (get_css_level (n, nits, CSS TEXT_DEC, "Text Decoration", 4)) context.css_text_decoration (n);
        if (get_css_level (n, nits, CSS TABLE, "Table", 3)) context.css_table (n);
        if (get_css_level (n, nits, CSS TRANSFORM, "Transform", 4, true)) context.css_transform (n);
        if (get_css_level (n, nits, CSS TRANSITION, "Transition", 3, true)) context.css_transition (n);
        yea_nay (&context_t::tv_profile, nits, CSS TV, CSS DONT TV);
        if (get_css_level (n, nits, CSS UI, "UI", 4)) context.css_ui (n);
        if (get_css_level (n, nits, CSS VALUE, "VALUE", 4)) context.css_value (n);
        if (get_css_level (n, nits, CSS WRITING, "Writing Mode", 4)) context.css_writing_mode (n);
        if (get_css_level (n, nits, CSS WC, "Will Change", 3)) context.css_will_change (n);

        yea_nay (&context_t::ie, nits, HTML IE, HTML DONT IE);
        yea_nay (&context_t::force_version, nits, HTML FORCE, HTML DONT FORCE);
        yea_nay (&context_t::rfc_1867, nits, HTML RFC1867, HTML DONT RFC1867);
        yea_nay (&context_t::rfc_1942, nits, HTML RFC1942, HTML DONT RFC1942);
        yea_nay (&context_t::rfc_1980, nits, HTML RFC1980, HTML DONT RFC1980);
        yea_nay (&context_t::rfc_2070, nits, HTML RFC2070, HTML DONT RFC2070);
        yea_nay (&context_t::presume_tags, nits, HTML TAGS, HTML DONT TAGS);
        yea_nay (&context_t::safari, nits, HTML SAFARI, HTML DONT SAFARI);
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
#ifndef NO_BOOST_REGEX
        if (var_.count (LINKS PRETEND)) context.pretend (nits, var_ [LINKS PRETEND].as < vstr_t > ());
#endif // NO_BOOST_REGEX
        if (var_.count (LINKS REPORT)) context.report (var_ [LINKS REPORT].as < vstr_t > ());
        yea_nay (&context_t::revoke, nits, LINKS REVOKE, LINKS DONT REVOKE);
        yea_nay (&context_t::crosslinks, nits, LINKS XLINK, LINKS DONT XLINK);

        if (var_.count (MATH VERSION))
        {   const int n = var_ [MATH VERSION].as < int > ();
            switch (n)
            {   case 0 : break;
                case 1 : context.math_version (math_1); break;
                case 2 : context.math_version (math_2); break;
                case 3 : context.math_version (math_3); break;
                case 4 : context.math_version (math_4_22); break;
                default : nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid MathML version"); context.math_version (math_none); } }

        if (var_ [MATH CORE].as < bool > ()) context.math_version (math_core);

        if (var_.count (MATH DRAFT))
        {   const int n = var_ [MATH DRAFT].as < int > ();
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

        if (var_.count (NITS CACHE)) context.cache (var_ [NITS CACHE].as < ::std::string > ());
        yea_nay (&context_t::nids, nits, NITS NIDS, NITS DONT NIDS);
        yea_nay (&context_t::extra, nits, NITS EXTRA, NITS DONT EXTRA);
        if (var_.count (NITS FORMAT)) context.nit_format (var_ [NITS FORMAT].as < ::std::string > ());
        if (var_.count (NITS QUOTE))
        {   const e_quote_style qs = examine_value < t_quote_style > (nits, html_default, var_ [NITS QUOTE].as < ::std::string > ());
            context.quote_style (qs); }
        yea_nay (&context_t::nits_nits_nits, nits, NITS UNIQUE, NITS DONT UNIQUE);
        yea_nay (&context_t::not_root, nits, NITS DONT ROOT, NITS ROOT); // note reversal
        yea_nay (&context_t::nits, nits, NITS WATCH, NITS DONT WATCH);
        if (var_.count (NITS XXX)) context.x (var_ [NITS XXX].as < ::std::string > ());

        if (var_.count (NITS CATASTROPHE))
            for (auto s : var_ [NITS CATASTROPHE].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_catastrophic))
                    nits.pick (nit_config_nit, es_error, ec_init, quote (s), ": no such nit.");

        if (var_.count (NITS ABHORRENT))
            for (auto s : var_ [NITS ABHORRENT].as < vstr_t > ())
                if (! nitpick::modify_severity (s, es_abhorrent))
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
                if (pos == ::std::string::npos) context.svg_version (lexical < int > :: cast (ver), 0);
                else if (pos == ver.length () - 1) context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), 0);
                else if (pos == 0) context.svg_version (sv_none);
                else context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), lexical < int > :: cast (ver.substr (pos+1)));
                if ((slash != ::std::string::npos) && (context.svg_version () == sv_1_2_tiny) && compare_no_case (ps, "full")) context.svg_version (sv_1_2_full);
                if (context.svg_version () == sv_none)
                    nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid SVG version"); } }

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
        if (var_.count (VALIDATION FF)) type_master < t_css_font_feature > :: extend (var_ [VALIDATION FF].as < vstr_t > ());
        if (var_.count (VALIDATION FV)) type_master < t_css_font_variation > :: extend (var_ [VALIDATION FV].as < vstr_t > ());
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
        TEST_VAR (baselineshift);
        TEST_VAR (citype);
        TEST_VAR (cntype);
        TEST_VAR (composite_operator);
        TEST_VAR (crs_whitebalance);
        TEST_VAR (decalign);
        TEST_VAR (dingbat);
        TEST_VAR (dir);
        TEST_VAR (display_align);
        TEST_VAR (dominantbaseline);
        TEST_VAR (enterkeyhint);
        TEST_VAR (evt_action);
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
        TEST_VAR (method);
        TEST_VAR (mf_identifier);
        TEST_VAR (mf_itemtype);
        TEST_VAR (mf_listing_action);
        TEST_VAR (mf_method);
        TEST_VAR (mf_reviewtype);
        TEST_VAR (musickey);
        TEST_VAR (namedspace);
        TEST_VAR (mathnotation);
        TEST_VAR (ogtype);
        TEST_VAR (paintkeyword);
        TEST_VAR (pam_ccv);
        TEST_VAR (pcmm_status);
        TEST_VAR (plusstyle);
        TEST_VAR (pointer_events);
        TEST_VAR (pri_img_colour);
        TEST_VAR (pri_img_technique);
        TEST_VAR (pri_img_viewpoint);
        TEST_VAR (print);
        TEST_VAR (prism_ad_pos);
        TEST_VAR (prism_ad_type);
        TEST_VAR (prism_ag_type);
        TEST_VAR (prism_audience_sector);
        TEST_VAR (prism_ccv);
        TEST_VAR (prism_class);
        TEST_VAR (prism_contenttype);
        TEST_VAR (prism_cvp);
        TEST_VAR (prism_genre);
        TEST_VAR (prism_icv);
        TEST_VAR (prism_pasv);
        TEST_VAR (prism_pcv);
        TEST_VAR (prism_pfv);
        TEST_VAR (prism_ptv);
        TEST_VAR (prism_rcv);
        TEST_VAR (prism_role);
        TEST_VAR (prs_action);
        TEST_VAR (quote_style);
        TEST_VAR (recipe_content);
        TEST_VAR (recipe_course);
        TEST_VAR (recipe_cuisine);
        TEST_VAR (recipe_dietary);
        TEST_VAR (recipe_dish);
        TEST_VAR (recipe_exclusion);
        TEST_VAR (recipe_kit);
        TEST_VAR (recipe_meal);
        TEST_VAR (recipe_method);
        TEST_VAR (recipe_source);
        TEST_VAR (recipe_special);
        TEST_VAR (recipe_time);
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
        TEST_VAR (xmpdm_audio_channel);
        TEST_VAR (xmpdm_audio_sample);
        TEST_VAR (xmpdm_camera_angle);
        TEST_VAR (xmpdm_camera_move);
        TEST_VAR (xmpdm_pulldown);
        TEST_VAR (xmpdm_shotsize);
        TEST_VAR (xmpdm_stretchmode);
        TEST_VAR (xmpdm_time_format);
        TEST_VAR (xmpdm_time_signature);
        TEST_VAR (xmpdm_video_pixeldepth);
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

    if (var_.count (CSS ADJUST)) res << CSS ADJUST ": " << var_ [CSS ADJUST].as < int > () << "\n";
    if (var_.count (CSS ANIMATION)) res << CSS ANIMATION ": " << var_ [CSS ANIMATION].as < int > () << "\n";
    if (var_.count (CSS BACKGROUND)) res << CSS BACKGROUND ": " << var_ [CSS BACKGROUND].as < int > () << "\n";
    if (var_.count (CSS BOX_ALIGN)) res << CSS BOX_ALIGN ": " << var_ [CSS BOX_ALIGN].as < int > () << "\n";
    if (var_.count (CSS BOX_MODEL)) res << CSS BOX_MODEL ": " << var_ [CSS BOX_MODEL].as < int > () << "\n";
    if (var_.count (CSS BOX_SIZING)) res << CSS BOX_SIZING ": " << var_ [CSS BOX_SIZING].as < int > () << "\n";
    if (var_.count (CSS CASCADE)) res << CSS CASCADE ": " << var_ [CSS CASCADE].as < int > () << "\n";
    if (var_.count (CSS COLOUR)) res << CSS COLOUR ": " << var_ [CSS COLOUR].as < int > () << "\n";
    if (var_.count (CSS COMPOSITING)) res << CSS COMPOSITING ": " << var_ [CSS COMPOSITING].as < int > () << "\n";
    if (var_.count (CSS COND_RULE)) res << CSS COND_RULE ": " << var_ [CSS COND_RULE].as < int > () << "\n";
    if (var_.count (CSS CS)) res << CSS CS ": " << var_ [CSS CS].as < int > () << "\n";
    if (var_.count (CSS CONTAIN)) res << CSS CONTAIN ": " << var_ [CSS CONTAIN].as < int > () << "\n";
    if (var_.count (CSS CUSTOM)) res << CSS CUSTOM ": " << var_ [CSS CUSTOM].as < int > () << "\n";
    if (var_.count (CSS DEVICE)) res << CSS DEVICE ": " << var_ [CSS DEVICE].as < int > () << "\n";
    if (var_.count (CSS DISPLAY)) res << CSS DISPLAY ": " << var_ [CSS DISPLAY].as < int > () << "\n";
    if (var_.count (CSS EASE)) res << CSS EASE ": " << var_ [CSS EASE].as < int > () << "\n";
    if (var_.count (CSS EXCLUDE)) res << CSS EXCLUDE ": " << var_ [CSS EXCLUDE].as < int > () << "\n";
    if (var_.count (CSS EXTENSION)) res << CSS EXTENSION ": "; pvs (res, var_ [CSS EXTENSION].as < vstr_t > ()); res << "\n";
    if (var_.count (CSS FBL)) res << CSS FBL ": " << var_ [CSS FBL].as < int > () << "\n";
    if (var_.count (CSS FILTER)) res << CSS FILTER ": " << var_ [CSS FILTER].as < int > () << "\n";
    if (var_.count (CSS FONT)) res << CSS FONT ": " << var_ [CSS FONT].as < int > () << "\n";
    if (var_.count (CSS FRAG)) res << CSS FRAG ": " << var_ [CSS FRAG].as < int > () << "\n";
    if (var_.count (CSS GRID)) res << CSS GRID ": " << var_ [CSS GRID].as < int > () << "\n";
    if (var_.count (CSS IMAGE)) res << CSS IMAGE ": " << var_ [CSS IMAGE].as < int > () << "\n";
    if (var_.count (CSS INLINE)) res << CSS INLINE ": " << var_ [CSS INLINE].as < int > () << "\n";
    if (var_.count (CSS LIST)) res << CSS LIST ": " << var_ [CSS LIST].as < int > () << "\n";
    if (var_.count (CSS LINE_GRID)) res << CSS LINE_GRID ": " << var_ [CSS LINE_GRID].as < int > () << "\n";
    if (var_.count (CSS LOGIC)) res << CSS LOGIC ": " << var_ [CSS LOGIC].as < int > () << "\n";
    if (var_.count (CSS MASKING)) res << CSS MASKING ": " << var_ [CSS MASKING].as < int > () << "\n";
    if (var_.count (CSS MEDIA)) res << CSS MEDIA ": " << var_ [CSS MEDIA].as < int > () << "\n";
    if (var_.count (CSS MOBILE)) res << CSS MOBILE ": " << var_ [CSS MOBILE].as < int > () << "\n";
    if (var_.count (CSS DONT MOBILE)) res << CSS DONT MOBILE ": " << var_ [CSS DONT MOBILE].as < int > () << "\n";
    if (var_.count (CSS MULTI_COLUMN)) res << CSS MULTI_COLUMN ": " << var_ [CSS MULTI_COLUMN].as < int > () << "\n";
    if (var_.count (CSS NAMESPACE)) res << CSS NAMESPACE ": " << var_ [CSS NAMESPACE].as < int > () << "\n";
    if (var_.count (CSS OVERFLOH)) res << CSS OVERFLOH ": " << var_ [CSS OVERFLOH].as < int > () << "\n";
    if (var_.count (CSS POSITION)) res << CSS POSITION ": " << var_ [CSS POSITION].as < int > () << "\n";
    if (var_.count (CSS PRINT)) res << CSS PRINT ": " << var_ [CSS PRINT].as < int > () << "\n";
    if (var_.count (CSS DONT PRINT)) res << CSS DONT PRINT ": " << var_ [CSS DONT PRINT].as < int > () << "\n";
    if (var_.count (CSS SCROLLBAR)) res << CSS SCROLLBAR ": " << var_ [CSS SCROLLBAR].as < int > () << "\n";
    if (var_.count (CSS SELECTOR)) res << CSS SELECTOR ": " << var_ [CSS SELECTOR].as < int > () << "\n";
    if (var_.count (CSS SHAPE)) res << CSS SHAPE ": " << var_ [CSS SHAPE].as < int > () << "\n";
    if (var_.count (CSS SPEECH)) res << CSS SPEECH ": " << var_ [CSS SPEECH].as < int > () << "\n";
    if (var_.count (CSS SNAP)) res << CSS SNAP ": " << var_ [CSS SNAP].as < int > () << "\n";
    if (var_.count (CSS STYLE)) res << CSS STYLE ": " << var_ [CSS STYLE].as < int > () << "\n";
    if (var_.count (CSS SYNTAX)) res << CSS SYNTAX ": " << var_ [CSS SYNTAX].as < int > () << "\n";
    if (var_.count (CSS TABLE)) res << CSS TABLE ": " << var_ [CSS TABLE].as < int > () << "\n";
    if (var_.count (CSS TEXT_ARG)) res << CSS TEXT_ARG ": " << var_ [CSS TEXT_ARG].as < int > () << "\n";
    if (var_.count (CSS TEXT_DEC)) res << CSS TEXT_DEC ": " << var_ [CSS TEXT_DEC].as < int > () << "\n";
    if (var_.count (CSS TRANSFORM)) res << CSS TRANSFORM ": " << var_ [CSS TRANSFORM].as < int > () << "\n";
    if (var_.count (CSS TRANSITION)) res << CSS TRANSITION ": " << var_ [CSS TRANSITION].as < int > () << "\n";
    if (var_.count (CSS TV)) res << CSS TV ": " << var_ [CSS TV].as < int > () << "\n";
    if (var_.count (CSS DONT TV)) res << CSS DONT TV ": " << var_ [CSS DONT TV].as < int > () << "\n";
    if (var_.count (CSS UI)) res << CSS UI ": " << var_ [CSS UI].as < int > () << "\n";
    if (var_.count (CSS VALUE)) res << CSS VALUE ": " << var_ [CSS VALUE].as < int > () << "\n";
    if (var_.count (CSS VERIFY)) res << CSS VERIFY ": " << var_ [CSS VERIFY].as < bool > () << "\n";
    if (var_.count (CSS DONT VERIFY)) res << CSS DONT VERIFY ": " << var_ [CSS DONT VERIFY].as < bool > () << "\n";
    if (var_.count (CSS VERSION)) res << CSS VERSION ": " << var_ [CSS VERSION].as < ::std::string > () << "\n";
    if (var_.count (CSS WRITING)) res << CSS WRITING ": " << var_ [CSS WRITING].as < int > () << "\n";
    if (var_.count (CSS WC)) res << CSS WC ": " << var_ [CSS WC].as < int > () << "\n";

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

    if (var_.count (HTML FORCE)) res << HTML FORCE "\n";
    if (var_.count (HTML DONT FORCE)) res << HTML DONT FORCE "\n";
    if (var_.count (HTML IE)) res << HTML IE "\n";
    if (var_.count (HTML DONT IE)) res << HTML DONT IE "\n";
    if (var_.count (HTML RFC1867)) res << HTML RFC1867 "\n";
    if (var_.count (HTML DONT RFC1867)) res << HTML DONT RFC1867 "\n";
    if (var_.count (HTML RFC1942)) res << HTML RFC1942 "\n";
    if (var_.count (HTML DONT RFC1942)) res << HTML DONT RFC1942 "\n";
    if (var_.count (HTML RFC1980)) res << HTML RFC1980 "\n";
    if (var_.count (HTML DONT RFC1980)) res << HTML DONT RFC1980 "\n";
    if (var_.count (HTML RFC2070)) res << HTML RFC2070 "\n";
    if (var_.count (HTML DONT RFC2070)) res << HTML DONT RFC2070 "\n";
    if (var_.count (HTML SAFARI)) res << HTML SAFARI "\n";
    if (var_.count (HTML DONT SAFARI)) res << HTML DONT SAFARI "\n";
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
#ifndef NO_BOOST_REGEX
    if (var_.count (LINKS PRETEND)) { res << LINKS PRETEND ": "; pvs (res, var_ [LINKS PRETEND].as < vstr_t > ()); res << "\n"; }
#endif // NO_BOOST_REGEX
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

    if (var_.count (NITS ABHORRENT)) { res << NITS ABHORRENT ": "; pvs (res, var_ [NITS ABHORRENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS CACHE)) res << NITS CACHE ": " << var_ [NITS CACHE].as < ::std::string > () << "\n";
    if (var_.count (NITS CATASTROPHE)) { res << NITS CATASTROPHE ": "; pvs (res, var_ [NITS CATASTROPHE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS COMMENT)) { res << NITS COMMENT ": "; pvs (res, var_ [NITS COMMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS DBG)) { res << NITS DBG ": "; pvs (res, var_ [NITS DBG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS ERR)) { res << NITS ERR ": "; pvs (res, var_ [NITS ERR].as < vstr_t > ()); res << "\n"; }
    if (var_ [NITS EXTRA].as < bool > ()) res << NITS EXTRA "\n";
    if (var_ [NITS DONT EXTRA].as < bool > ()) res << NITS DONT EXTRA "\n";
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
    if (var_.count (NITS XXX)) res << NITS XXX ": " << var_ [NITS XXX].as < ::std::string > () << "\n";

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
    {   const e_ontology es = static_cast < e_ontology > (i);
        if (is_faux_schema (es)) continue;
        if (get_ontology_version_count (es) < 2) continue;
        const ::std::string naam (ontology_names.get (es, ONTOLOGY_NAME));
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
    if (var_.count (VALIDATION EXTENSION)) { res << VALIDATION EXTENSION ": "; pvs (res, var_ [VALIDATION EXTENSION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION FF)) { res << VALIDATION FF ": "; pvs (res, var_ [VALIDATION FF].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION FV)) { res << VALIDATION FV ": "; pvs (res, var_ [VALIDATION FV].as < vstr_t > ()); res << "\n"; }
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
    RPT_VAR (citype);
    RPT_VAR (cntype);
    RPT_VAR (composite_operator);
    RPT_VAR (crs_whitebalance);
    RPT_VAR (dcmitype);
    RPT_VAR (decalign);
    RPT_VAR (dingbat);
    RPT_VAR (dir);
    RPT_VAR (display_align);
    RPT_VAR (dominantbaseline);
    RPT_VAR (enterkeyhint);
    RPT_VAR (evt_action);
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
    RPT_VAR (musickey);
    RPT_VAR (namedspace);
    RPT_VAR (namespace);
    RPT_VAR (mathnotation);
    RPT_VAR (ogtype);
    RPT_VAR (paintkeyword);
    RPT_VAR (pam_ccv);
    RPT_VAR (pcmm_status);
    RPT_VAR (plusstyle);
    RPT_VAR (pointer_events);
    RPT_VAR (pri_img_colour);
    RPT_VAR (pri_img_technique);
    RPT_VAR (pri_img_viewpoint);
    RPT_VAR (print);
    RPT_VAR (prism_ad_pos);
    RPT_VAR (prism_ad_type);
    RPT_VAR (prism_ag_type);
    RPT_VAR (prism_audience_sector);
    RPT_VAR (prism_ccv);
    RPT_VAR (prism_class);
    RPT_VAR (prism_contenttype);
    RPT_VAR (prism_cvp);
    RPT_VAR (prism_genre);
    RPT_VAR (prism_icv);
    RPT_VAR (prism_pasv);
    RPT_VAR (prism_pcv);
    RPT_VAR (prism_pfv);
    RPT_VAR (prism_ptv);
    RPT_VAR (prism_rcv);
    RPT_VAR (prism_role);
    RPT_VAR (prs_action);
    RPT_VAR (quote_style);
    RPT_VAR (recipe_content);
    RPT_VAR (recipe_course);
    RPT_VAR (recipe_cuisine);
    RPT_VAR (recipe_dietary);
    RPT_VAR (recipe_dish);
    RPT_VAR (recipe_exclusion);
    RPT_VAR (recipe_kit);
    RPT_VAR (recipe_meal);
    RPT_VAR (recipe_method);
    RPT_VAR (recipe_source);
    RPT_VAR (recipe_special);
    RPT_VAR (recipe_time);
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
    RPT_VAR (xmpdm_audio_channel);
    RPT_VAR (xmpdm_audio_sample);
    RPT_VAR (xmpdm_camera_angle);
    RPT_VAR (xmpdm_camera_move);
    RPT_VAR (xmpdm_pulldown);
    RPT_VAR (xmpdm_shotsize);
    RPT_VAR (xmpdm_stretchmode);
    RPT_VAR (xmpdm_time_format);
    RPT_VAR (xmpdm_time_signature);
    RPT_VAR (xmpdm_video_pixeldepth);
#undef RPT_VAR

    return res.str (); }
