/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
{   ::std::cout << PROG " [switch...] file/dir.\n\n";
    ::std::cout << PROG " is an opinionated HTML nit-picker, intended for people, like me, who hand code websites.\n";
    ::std::cout << "It doesn't just check static websites for broken links, dubious syntax, and bad semantic data,\n";
    ::std::cout << "it will actively complain about things that are perfectly legal but just a little bit untidy.\n";
    ::std::cout << aid << "\n\n";
    ::std::cout << "If a configuration file is specified, it should be in INI file format with these optional sections:\n";
    ::std::cout << GENERAL_ ", " LINKS_ ", " MF_ ", " MICRODATA_ ", " STATS ", " VALIDATION " and " WEBSITE_ "\n";
    ::std::cout << "Each section contains individual assignments using the identifiers (after the dot) noted above.\n";
    ::std::cout << "Such a file might contain:\n\n";
    ::std::cout << "[" GENERAL_ "]\n";
    ::std::cout << VERBOSE "=2\n\n";
    ::std::cout << "[" LINKS_ "]\n";
    ::std::cout << CHECK "=1\n\n";
    ::std::cout << "[" WEBSITE_ "]\n";
    ::std::cout << EXTENSION "=shtml\n";
    ::std::cout << EXTENSION "=html\n";
    ::std::cout << INDEX "=index.shtml\n";
    ::std::cout << SITE "=" DEFAULT_DOMAIN "\n\n"; }

void options::process (int argc, char** argv)
{   /*  a
        b
        c persist file   C clear webmention
        d
        e external check
        f config         F load config file from .ssc/config
        g website root
        h help
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
        w webmention
        x extensions     X check crosslinked ids
        y
        z
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
        basic ("Console Options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        primary ("Standard Options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        hidden,
        cmd (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        config (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        aid (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        line (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        valid("validation options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH);
    ::boost::program_options::positional_options_description pos;
    pos.add (WEBSITE ROOT, 1);
    basic.add_options ()
        (HELP ",h", "output this information and exit")
        (VALIDATION_, "list attribute extensions and exit")
        (VERSION ",V", "display version & copyright info, then exit")
        ;
    hidden.add_options ()
        (GENERAL CLASS, "do not report unrecognised classes.")
        (GENERAL WEBMENTION ",w", "process webmentions.")
        (GENERAL TEST ",T", "machine readable output formatted for tests.")
        (GENERAL USER, ::boost::program_options::value < ::std::string > () -> default_value ("scroggins"), "user name to supply when requested.")
        (NITS WATCH, "debug nits (error reporting mechanism).")
        (WMIN TEST_HEADER, ::boost::program_options::value < ::std::string > (), "use this file to test header parsing code.")
        (WMIN HOOK, ::boost::program_options::value < ::std::string > (), "process incoming " WEBMENTION ", in JSON format, in specified file.")
        (WMIN STUB, ::boost::program_options::value < ::std::string > () -> default_value ("_" PROG), "mask for file containing " WEBMENTION " HTML snippet.")
        (WMIN MACROSTART, ::boost::program_options::value < ::std::string > () -> default_value ("{{"), "start of template macro.")
        (WMIN MACROEND, ::boost::program_options::value < ::std::string > () -> default_value ("}}"), "start of template macro.")
        (WMIN WRITE , ::boost::program_options::value < ::std::string > (), "when writing " WEBMENTION " includes, write them to this path (default: site.root).")
        (WMIN MENTION, ::boost::program_options::value < vstr_t > () -> composing (), "a " WEBMENTION ", string must be source=url,target=url. May be repeated.")
        (WMIN PATH, ::boost::program_options::value < ::std::string > () -> default_value (MENTION), "path for incoming web mention data files (note " GENERAL PATH ").") // not yet noted below
        (WMIN TEMPLATE ",t", ::boost::program_options::value < vstr_t > () -> composing (), "HTML snippets for adding mentions (new, changed, deleted, unchanged, unknown). May be repeated.")
        (WMOUT CLEAR ",C", "clear out all web mention data")
        (WMOUT NOTIFY ",N", "notify appropriate servers of web mention updates")
        (WMOUT RESET ",R", "reset web mention data")
        (WMOUT SECRET, ::boost::program_options::value < ::std::string > (), WEBMENTION " secret.")
        ;
    line.add_options ()
        (CONFIG ",f", ::boost::program_options::value < ::std::string > (), "load configuration from this file.")
        (DEFCONF ",F", "load configuration from " CONFIGURATION ".")
        ;
    primary.add_options ()
        (GENERAL CSS_OPTION, "do NOT load css files.")
        (GENERAL CUSTOM, ::boost::program_options::value < vstr_t > () -> composing (), "Define a custom element for checking the 'is' attribute. May be repeated.")
        (GENERAL FILE ",c", ::boost::program_options::value < ::std::string > () -> default_value (PROG EXT), "file for persistent data, requires -N (note " GENERAL PATH ").")
        (GENERAL IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "ignore attributes and content of specified element. May be repeated.")
        (GENERAL MAXFILESIZE, ::boost::program_options::value < int > (), "maximum file size to read, in megabytes (zero to set no limit).")
        (GENERAL NOCHANGE ",n", "report what will do, but do not actually do it.")
        (GENERAL OUTPUT ",o", ::boost::program_options::value < ::std::string > (), "output file (default to the console).")
        (GENERAL PATH ",p", ::boost::program_options::value < ::std::string > () -> default_value ("." PROG), "root directory for all " PROG " files.")
        (GENERAL RDF, "check RDFa attributes.")
        (GENERAL SLOB, "ignore slob HTML, such as forgotten closures.")
        (GENERAL SSI ",I", "process simple Server Side Includes.")
        (GENERAL VERBOSE ",v", ::boost::program_options::value < int > () -> default_value (static_cast <int> (default_output)), "output extra information.")

        (HTML TAGS, "presume HTML files with no DOCTYPE declaration are HTML Tags, not HTML 1.0.")
        (HTML RFC1867, "Reject RFC 1867 (INPUT=FILE) when processing HTML 2.0.")
        (HTML RFC1942, "Reject RFC 1942 (tables) when processing HTML 2.0.")
        (HTML RFC1980, "Reject RFC 1980 (client side image maps) when processing HTML 2.0.")
        (HTML RFC2070, "Reject RFC 2070 (internationalisation) when processing HTML 2.0.")
        (HTML VERSION, ::boost::program_options::value < ::std::string > (), "version of HTML presumed if no DOCTYPE (default: '1.0', note HTML 5 is year.month).")

        (LINKS EXTERNAL ",e", "check external links (requires curl, sets " LINKS CHECK ").")
        (LINKS FORWARD ",3", "report http forwarding errors, e.g. 301 and 308 (sets " LINKS EXTERNAL ").")
        (LINKS CHECK ",l", "check links.")
        (LINKS ONCE ",O", "report each broken external link once (sets " LINKS EXTERNAL ").")
        (LINKS REVOKE ",r", "do not check whether https certificates have been revoked (sets " LINKS EXTERNAL ").")
        (LINKS XLINK ",X", "check crosslinked ids (uses additional memory).")

        (MF VERIFY ",M", "check microformats (see https://microformats.org/).")
        (MF VERSION, ::boost::program_options::value < int > () -> default_value (3), "check this version of microformats (1, 2, or 3 for both).")
        (MF EXPORT, "export microformat data (only verified data if " MF VERIFY " is set).")

        (MATH VERSION, ::boost::program_options::value < int > () -> default_value (0), "preferred version of MathML (0 for value implied by HTML version).")

        (MICRODATA MICRODATAARG ",m", "check microdata (" PROG " only understands schema.org microdata).")
        (MICRODATA VERSION, ::boost::program_options::value < int > (), "set default schema.org major version (default: 11).")
        (MICRODATA MINOR, ::boost::program_options::value < int > (), "set default schema.org minor version (default: 0).")
        (MICRODATA EXPORT, "export microformat data (only verified data if " MICRODATA MICRODATAARG " is set).")

        (NITS CATASTROPHE, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as a catastrophe. Use nid. May be repeated.")
        (NITS CODES, "output nit codes.")
        (NITS COMMENT, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as a comment. Use nid. May be repeated.")
        (NITS DEBUG, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as a debug message. Use nid. May be repeated.")
        (NITS ERR, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as an error. Use nid. May be repeated.")
        (NITS INFO, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as info. Use nid. May be repeated.")
        (NITS NIDS, "output nit identifiers.")
        (NITS SILENCE, ::boost::program_options::value < vstr_t > () -> composing (), "silence nit. Use nid. May be repeated.")
        (NITS WARNING, ::boost::program_options::value < vstr_t > () -> composing (), "redefine nit as a warning. Use nid. May be repeated.")

        (SHADOW COMMENT, "do NOT squish comments on shadow pages")
#ifdef NOLYNX
        (SHADOW COPY, ::boost::program_options::value < int > (), "copy non-HTML files: 0=no (default), 1=pages, 2/3/4=copy all, 5=copy+dedu, 6=rpt dups.")
#else // NOLYNX
        (SHADOW COPY, ::boost::program_options::value < int > (), "copy non-HTML files: 0=no (default), 1=pages, 2=hard link all, 3=soft link all, 4=copy all, 5=copy+dedu, 6=rpt dups.")
#endif // NOLYNX
        (SHADOW FILE, ::boost::program_options::value < ::std::string > (), "where to persist deduplication data")
        (SHADOW ROOT, ::boost::program_options::value < ::std::string > (), "shadow root directory.")
        (SHADOW SSI, "do NOT resolve SSIs on shadow pages when " GENERAL SSI " is set")
        (SHADOW SPACING, "do NOT merge spacing on shadow pages")
        (SHADOW VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "shadow virtual directory, arg syntax virtual=shadow. Must correspond to " WEBSITE VIRTUAL)

        (WEBSITE ROOT ",g", ::boost::program_options::value < ::std::string > (), "website root directory (default: current directory).")
        (WEBSITE EXTENSION ",x", ::boost::program_options::value < vstr_t > () -> composing (), "check files with this extension (default html). May be repeated.")
        (WEBSITE INDEX ",i", ::boost::program_options::value < ::std::string > (), "index file in directories (default: none).")
        (WEBSITE SITE ",s", ::boost::program_options::value < vstr_t > () -> composing (), "domain name(s) for local site (default none). May be repeated.")
        (WEBSITE VIRTUAL ",L", ::boost::program_options::value < vstr_t > () -> composing (), "define virtual directory, arg syntax virtual=physical. May be repeated.")

        (STATS PAGE, "report statistics for each page.")
        (STATS SUMMARY ",S", "report site statistics.")

        (SVG VERSION, ::boost::program_options::value < ::std::string > (), "preferred version of SVG if version attribute missing (requires HTML 4 or greater).")

        (VALIDATION MINOR ",4", ::boost::program_options::value < int > (), "Validate HTML5 with this mnr version (e.g. 3 for HTML 5.3).")
        (VALIDATION MICRODATAARG, "Validate HTML5 microdata")
        	;
    valid.add_options ()
        (VALIDATION CHARSET, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid charset.")
        (VALIDATION CLASS, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid class.")
        (VALIDATION COLOUR, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid colour.")
        (VALIDATION CURRENCY, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid currency.")
        (VALIDATION HTTPEQUIV, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid meta httpequiv.")
        (VALIDATION LANG, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid language code (such as ma for marain).")
        (VALIDATION METANAME, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid meta name.")
        (VALIDATION MIMETYPE, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid mimetype.")
        (VALIDATION REL, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid rel.")
        (VALIDATION SGML, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid SGML schema identification.")
        ;

    valid.add (context.validation());

    cmd.add (basic).add (primary).add (valid).add (line).add (hidden);
    config.add (primary).add (valid).add (hidden);
    aid.add (basic).add (line).add (primary);
    try
    {   ::boost::program_options::store (::boost::program_options::command_line_parser (argc, argv).options (cmd).positional (pos).run (), var_); }
    catch (...)
    {   title ("\nCommand line parameter error. " TYPE_HELP "\n");
        return; }
    ::std::string loaded;
    if (var_.count (CONFIG) || var_.count (DEFCONF))
    {   ::boost::filesystem::path file (CONFIGURATION);
        if (var_.count (CONFIG)) file = var_ [CONFIG].as < ::std::string > ();
        if (var_.count (GENERAL TEST) == 0)
        {   loaded = "\nLoading configuration "; loaded += file.string () + " ...\n"; }
        if (! ::boost::filesystem::exists (file))
        {   loaded += "Cannot find "; loaded += file.string () + "\n";
            title (loaded.c_str ()); return; }
        try
#ifdef  NO_PCF_STR
        {   ::std::ifstream fis (file.string ().c_str ());
            ::boost::program_options::store (::boost::program_options::parse_config_file (fis, config, true), var_); }
#else
        {   ::boost::program_options::store (::boost::program_options::parse_config_file (file.string ().c_str (), config, true), var_); }
#endif
        catch (...)
        {   loaded += "Error in "; loaded += file.string () + "\n";
            title (loaded.c_str ()); return; } }
    ::boost::program_options::notify (var_);
    if (var_.count (VERSION)) { title (); valid_ = true; return; }
    if (var_.count (HELP)) { title (); help (aid); valid_ = true; return; }
    if (var_.count (VALIDATION_)) { title (); ::std::cout << "\n" << valid; valid_ = true; return; }
    valid_ = var_.count (WEBSITE ROOT);
    if (! valid_) { loaded += "\n" TYPE_HELP "\n"; title (loaded.c_str ()); return; }
    if (var_.count (GENERAL TEST) == 0) title (loaded.c_str ());
    stop_ = false; }

void options::contextualise ()
{   context.clear (var_.count (WMOUT CLEAR));
    context.test (var_.count (GENERAL TEST));

    if (var_.count (GENERAL OUTPUT))
    {   context.output (nix_path_to_local (var_ [GENERAL OUTPUT].as < ::std::string > ()));
        if (! context.test ())
            ::std::cout << "Writing to " << var_ [GENERAL OUTPUT].as < ::std::string > () << "\n"; }

    if (context.test ()) context.out () << PROG "\n" VERSION_STRING "\n" COPYRIGHT"\n";
    else context.out () << FULLNAME " version " VERSION_STRING " (" __DATE__ " " __TIME__ ")\n" COPYRIGHT "\n";

    context.path (nix_path_to_local (var_ [GENERAL PATH].as < ::std::string > ()));
    if (! ::boost::filesystem::exists (context.path ()))
    {   context.err () << context.path () << " does not exist, am creating it.";
        ::boost::filesystem::create_directories (context.path ()); }   // if throws, then exit

    context.load_css (var_.count (GENERAL CSS_OPTION) == 0);
    context.nochange (var_.count (GENERAL NOCHANGE));
    context.rdf (var_.count (GENERAL RDF));
    context.ssi (var_.count (GENERAL SSI));
    context.persisted (path_in_context (nix_path_to_local (var_ [GENERAL FILE].as < ::std::string > ())));
    context.stats_page (var_.count (STATS PAGE));
    context.stats_summary (var_.count (STATS SUMMARY));

    context.presume_tags (var_.count (HTML TAGS));
    context.rfc_1867 (! var_.count (HTML RFC1867));
    context.rfc_1942 (! var_.count (HTML RFC1942));
    context.rfc_1980 (! var_.count (HTML RFC1980));
    context.rfc_2070 (! var_.count (HTML RFC2070));

    if (var_.count (HTML VERSION))
    {   ::std::string ver (var_ [HTML VERSION].as < ::std::string > ());
        if (! ver.empty ())
        {   ::std::string::size_type pos = ver.find ('.');
            if (pos == ::std::string::npos)
                if (ver.length () == 1) context.html_major (0).html_minor (1);
                else context.html_major (lexical < int > :: cast (ver.substr (0, pos)));
            else if (pos == ver.length () - 1) context.html_major (lexical < int > :: cast (ver.substr (0, pos))).html_minor (0);
            else if (pos == 0) context.html_major (0).html_minor (1);
            else context.html_major (lexical < int > :: cast (ver.substr (0, pos))).html_minor (lexical < int > :: cast (ver.substr (pos+1))); } }

    if (var_.count (SVG VERSION))
    {   ::std::string ver (var_ [SVG VERSION].as < ::std::string > ());
        if (! ver.empty ())
        {   ::std::string::size_type pos = ver.find ('.');
            if (pos == ::std::string::npos)
                if (ver.length () == 1) context.svg_version (0, 0);
                else context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), 0);
            else if (pos == ver.length () - 1) context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), 0);
            else if (pos == 0) context.svg_version (0, 0);
            else context.svg_version (lexical < int > :: cast (ver.substr (0, pos)), lexical < int > :: cast (ver.substr (pos+1))); } }

    if (var_.count (MATH VERSION))
    {   int n = var_ [MATH VERSION].as < int > ();
        if ((n > 0) && (n < 5)) context.math_version (static_cast < e_mathversion > (n)); }

    context.forwarded (var_.count (LINKS FORWARD));
    context.revoke (var_.count (LINKS REVOKE));
    context.md_export (var_.count (MICRODATA EXPORT));
    context.mf_export (var_.count (MF EXPORT));
    context.mf_verify (var_.count (MF VERIFY));
    context.schema (var_.count (MICRODATA MICRODATAARG));
    context.once (var_.count (LINKS ONCE));
    context.external (var_.count (LINKS EXTERNAL));
    context.links (var_.count (LINKS CHECK));
    context.process_webmentions (var_.count (GENERAL WEBMENTION));
    context.unknown_class (var_.count (GENERAL CLASS));
    context.crosslinks (var_.count (LINKS XLINK));

    const long meg = 1024*1024;

    if (! var_.count (GENERAL MAXFILESIZE))
        context.max_file_size (4 * meg);
    else
    {   long max = static_cast < long > (var_ [GENERAL MAXFILESIZE].as < int > ());
        if (max < 0 || (max > (LONG_MAX / meg))) max = DEFAULT_MAX_FILE_SIZE;
        context.max_file_size (max * meg); }

    if (var_.count (GENERAL CUSTOM)) context.custom_elements ( var_ [GENERAL CUSTOM].as < vstr_t > ());
    if (var_.count (GENERAL IGNORED)) context.ignore (var_ [GENERAL IGNORED].as < vstr_t > ());
    if (var_.count (GENERAL USER)) context.user (var_ [GENERAL USER].as < ::std::string > ());
    if (var_.count (GENERAL VERBOSE)) context.verbose (static_cast < e_verbose > (var_ [GENERAL VERBOSE].as < int > ()));

    if (var_.count (MF VERSION)) context.mf_version (static_cast < unsigned char > (var_ [MF VERSION].as < int > ()));

    if (var_.count (MICRODATA VERSION)) context.schema_major (static_cast < unsigned char > (var_ [MICRODATA VERSION].as < int > ()));
    if (var_.count (MICRODATA MINOR)) context.schema_minor (static_cast < unsigned char > (var_ [MICRODATA MINOR].as < int > ()));

    context.codes (var_.count (NITS CODES));
    context.nids (var_.count (NITS NIDS));
    context.nits (var_.count (NITS WATCH));

    if (var_.count (NITS CATASTROPHE))
        for (auto s : var_ [NITS CATASTROPHE].as < vstr_t > ())
            if (! nitpick::modify_severity (s, es_catastrophic))
                context.err () << quote (s) << ": no such nit.\n";

    if (var_.count (NITS COMMENT))
        for (auto s : var_ [NITS COMMENT].as < vstr_t > ())
            if (! nitpick::modify_severity (s, es_comment))
                context.err () << quote (s) << ": no such nit.\n";

    if (var_.count (NITS DEBUG))
        for (auto s : var_ [NITS DEBUG].as < vstr_t > ())
            if (! nitpick::modify_severity (s, es_debug))
                context.err () << quote (s) << ": no such nit.\n";

    if (var_.count (NITS ERR))
        for (auto s : var_ [NITS ERR].as < vstr_t > ())
            if (! nitpick::modify_severity (s, es_error))
                context.err () << quote (s) << ": no such nit.\n";

    if (var_.count (NITS INFO))
        for (auto s : var_ [NITS INFO].as < vstr_t > ())
            if (! nitpick::modify_severity (s, es_info))
                context.err () << quote (s) << ": no such nit.\n";

    if (var_.count (NITS SILENCE))
        for (auto s : var_ [NITS SILENCE].as < vstr_t > ())
            if (! nitpick::modify_severity (s, es_silence))
                context.err () << quote (s) << ": no such nit.\n";

    if (var_.count (NITS WARNING))
        for (auto s : var_ [NITS WARNING].as < vstr_t > ())
            if (! nitpick::modify_severity (s, es_warning))
                context.err () << quote (s) << ": no such nit.\n";

    context.microdata (var_.count (VALIDATION MICRODATAARG));

    context.shadow_comment (var_.count (SHADOW COMMENT));
#ifdef NOLYNX
    if (var_.count (SHADOW COPY))
    {   int n = var_ [SHADOW COPY].as < int > ();
        if ((n == 2) || (n == 3)) n = 4;
        context.copy (n); }
#else // NOLYNX
    if (var_.count (SHADOW COPY)) context.copy (var_ [SHADOW COPY].as < int > ());
#endif // NOLYNX
    if (var_.count (SHADOW FILE)) context.shadow_persist (path_in_context (nix_path_to_local (var_ [SHADOW FILE].as < ::std::string > ())));
    if (var_.count (SHADOW ROOT)) context.shadow (nix_path_to_local (var_ [SHADOW ROOT].as < ::std::string > ()));
    context.shadow_space (var_.count (SHADOW SPACING));
    context.shadow_ssi (var_.count (SHADOW SSI));
    if (var_.count (SHADOW VIRTUAL)) context.virtuals (var_ [SHADOW VIRTUAL].as < vstr_t > ());

    if (var_.count (WEBSITE INDEX)) context.index (var_ [WEBSITE INDEX].as < ::std::string > ());
    if (var_.count (WEBSITE EXTENSION)) context.extensions (var_ [WEBSITE EXTENSION].as < vstr_t > ());
    else { vstr_t ex; ex.push_back ("html"); context.extensions (ex); }
    if (var_.count (WEBSITE ROOT)) context.root (nix_path_to_local (var_ [WEBSITE ROOT].as < ::std::string > ()));
    if (var_.count (WEBSITE SITE)) context.site (var_ [WEBSITE SITE].as < vstr_t > ());
    if (var_.count (WEBSITE VIRTUAL)) context.virtuals (var_ [WEBSITE VIRTUAL].as < vstr_t > ());

    if (var_.count (WMIN WRITE)) context.write_path (var_ [WMIN WRITE].as < ::std::string > ());
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
    if (var_.count (WMOUT SECRET)) context.secret (var_ [WMOUT SECRET].as < ::std::string > ());

    if (var_.count (VALIDATION CHARSET)) type_master < t_charset > :: extend (var_ [VALIDATION CHARSET].as < vstr_t > ());
    if (var_.count (VALIDATION CLASS)) type_master < t_class > :: extend (var_ [VALIDATION CLASS].as < vstr_t > ());
    if (var_.count (VALIDATION COLOR)) type_master < t_fixedcolour > :: extend (var_ [VALIDATION COLOR].as < vstr_t > ());
    if (var_.count (VALIDATION COLOUR)) type_master < t_fixedcolour > :: extend (var_ [VALIDATION COLOUR].as < vstr_t > ());
    if (var_.count (VALIDATION CURRENCY)) type_master < t_currency > :: extend (var_ [VALIDATION CURRENCY].as < vstr_t > ());
    if (var_.count (VALIDATION DINGBATARG)) type_master < t_dingbat > :: extend (var_ [VALIDATION DINGBATARG].as < vstr_t > ());
    if (var_.count (VALIDATION HTTPEQUIV)) type_master < t_httpequiv > :: extend (var_ [VALIDATION HTTPEQUIV].as < vstr_t > ());
    if (var_.count (VALIDATION LANG)) type_master < t_lang > :: extend (var_ [VALIDATION LANG].as < vstr_t > ());
    if (var_.count (VALIDATION MINOR)) context.html_minor (static_cast < unsigned char > (var_ [VALIDATION MINOR].as < int > ()));
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
    TEST_VAR (decalign);
    TEST_VAR (citype);
    TEST_VAR (cntype);
    TEST_VAR (composite_operator);
    TEST_VAR (dingbat);
    TEST_VAR (dir);
    TEST_VAR (display);
    TEST_VAR (dominantbaseline);
    TEST_VAR (enterkeyhint);
    TEST_VAR (figalign);
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
    TEST_VAR (microdata_domain);
    TEST_VAR (namedspace);
    TEST_VAR (namespace);
    TEST_VAR (mathnotation);
    TEST_VAR (paintkeyword);
    TEST_VAR (plusstyle);
    TEST_VAR (pointerevents);
    TEST_VAR (print);
    TEST_VAR (referrer);
    TEST_VAR (renderingintent);
    TEST_VAR (rules);
    TEST_VAR (sandbox);
    TEST_VAR (shape7);
    TEST_VAR (shaperendering);
    TEST_VAR (ssi);
    TEST_VAR (ssi_comparison);
    TEST_VAR (ssi_encoding);
    TEST_VAR (ssi_env);
    TEST_VAR (svg_align);
    TEST_VAR (svg_fontstretch);
    TEST_VAR (svg_fontstretch_ff);
    TEST_VAR (svg_fontweight);
    TEST_VAR (svg_fontweight_ff);
    TEST_VAR (svg_mode);
    TEST_VAR (svg_overflow);
    TEST_VAR (svg_version);
    TEST_VAR (tableframe);
    TEST_VAR (textdecoration);
    TEST_VAR (textrendering);
    TEST_VAR (transform_anim);
    TEST_VAR (transform_fn);
    TEST_VAR (turbulence_type);
    TEST_VAR (vectoreffect_2);
    TEST_VAR (xlinkshow);
    TEST_VAR (xmlns);

    if (context.write_path ().empty ()) context.write_path (context.root ()); }

void pvs (::std::ostringstream& res, const vstr_t& data)
{   for (auto i : data)
        res << i << " "; }

::std::string options::report () const
{   ::std::ostringstream res;
    if (context.test ()) return res.str ();
    res << "** Switches:\n";

    if (var_.count (HELP)) res << HELP "\n";
    if (var_.count (VERSION)) res << VERSION "\n";

    if (var_.count (GENERAL CLASS)) res << GENERAL CLASS "\n";
    if (var_.count (GENERAL CSS_OPTION)) res << GENERAL CSS_OPTION "\n";
    if (var_.count (GENERAL CUSTOM)) { res << GENERAL CUSTOM ": "; pvs (res, var_ [GENERAL CUSTOM].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL FILE)) res << GENERAL FILE ": " << var_ [GENERAL FILE].as < ::std::string > () << "\n";
    if (var_.count (GENERAL IGNORED)) { res << GENERAL IGNORED ": "; pvs (res, var_ [GENERAL IGNORED].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL MAXFILESIZE)) res << GENERAL MAXFILESIZE ": " << var_ [GENERAL MAXFILESIZE].as < int > () << "\n";
    if (var_.count (GENERAL NOCHANGE)) res << GENERAL NOCHANGE "\n";
    if (var_.count (GENERAL PATH)) res << GENERAL PATH ": " << var_ [GENERAL PATH].as < ::std::string > () << "\n";
    if (var_.count (GENERAL RDF)) res << GENERAL RDF "\n";
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
    if (var_.count (HTML VERSION)) res << HTML VERSION "\n";

    if (var_.count (MATH VERSION)) res << MATH VERSION ": " << var_ [MATH VERSION].as < int > () << "\n";

    if (var_.count (NITS CATASTROPHE)) { res << NITS CATASTROPHE ": "; pvs (res, var_ [NITS CATASTROPHE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS COMMENT)) { res << NITS COMMENT ": "; pvs (res, var_ [NITS COMMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS DEBUG)) { res << NITS DEBUG ": "; pvs (res, var_ [NITS DEBUG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS ERR)) { res << NITS ERR ": "; pvs (res, var_ [NITS ERR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS INFO)) { res << NITS INFO ": "; pvs (res, var_ [NITS INFO].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS NIDS)) res << NITS NIDS "\n";
    if (var_.count (NITS SILENCE)) { res << NITS SILENCE ": "; pvs (res, var_ [NITS SILENCE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS WARNING)) { res << NITS WARNING ": "; pvs (res, var_ [NITS WARNING].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS WATCH)) res << NITS WATCH "\n";

    if (var_.count (STATS PAGE)) res << STATS PAGE "\n";
    if (var_.count (STATS SUMMARY)) res << STATS SUMMARY "\n";

    if (var_.count (SVG VERSION)) res << SVG VERSION "\n";

    if (var_.count (LINKS EXTERNAL)) res << LINKS EXTERNAL "\n";
    if (var_.count (LINKS FORWARD)) res << LINKS FORWARD "\n";
    if (var_.count (LINKS CHECK)) res << LINKS CHECK "\n";
    if (var_.count (LINKS ONCE)) res << LINKS ONCE "\n";
    if (var_.count (LINKS REVOKE)) res << LINKS REVOKE "\n";
    if (var_.count (LINKS XLINK)) res << LINKS XLINK "\n";

    if (var_.count (MF EXPORT)) res << MF EXPORT "\n";
    if (var_.count (MF VERIFY)) res << MF VERIFY "\n";
    if (var_.count (MF VERSION)) res << MF VERSION ": " << var_ [MF VERSION].as < int > () << "\n";

    if (var_.count (MICRODATA MICRODATAARG)) res << MICRODATA MICRODATAARG "\n";
    if (var_.count (MICRODATA EXPORT)) res << MICRODATA EXPORT "\n";
    if (var_.count (MICRODATA VERSION)) res << MICRODATA VERSION ": " << var_ [MICRODATA VERSION].as < int > () << "\n";
    if (var_.count (MICRODATA MINOR)) res << MICRODATA MINOR ": " << var_ [MICRODATA MINOR].as < int > () << "\n";

    if (var_.count (SHADOW COMMENT)) res << SHADOW COMMENT "\n";
    if (var_.count (SHADOW COPY)) res << SHADOW COPY ": " << var_ [SHADOW COPY].as < int > () << "\n";
    if (var_.count (SHADOW FILE)) res << SHADOW FILE ": " << var_ [SHADOW FILE].as < ::std::string > () << "\n";
    if (var_.count (SHADOW ROOT)) res << SHADOW ROOT ": " << var_ [SHADOW ROOT].as < ::std::string > () << "\n";
    if (var_.count (SHADOW SPACING)) res << SHADOW SPACING "\n";
    if (var_.count (SHADOW SSI)) res << SHADOW SSI "\n";
    if (var_.count (SHADOW VIRTUAL)) { res << SHADOW VIRTUAL ": "; pvs (res, var_ [SHADOW VIRTUAL].as < vstr_t > ()); res << "\n"; }

    if (var_.count (VALIDATION CHARSET)) { res << VALIDATION CHARSET ": "; pvs (res, var_ [VALIDATION CHARSET].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION CLASS)) { res << VALIDATION CLASS ": "; pvs (res, var_ [VALIDATION CLASS].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION COLOR)) { res << VALIDATION COLOUR ": "; pvs (res, var_ [VALIDATION COLOR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION COLOUR)) { res << VALIDATION COLOUR ": "; pvs (res, var_ [VALIDATION COLOUR].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION CURRENCY)) { res << VALIDATION CURRENCY ": "; pvs (res, var_ [VALIDATION CURRENCY].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION DINGBATARG)) { res << VALIDATION DINGBATARG ": "; pvs (res, var_ [VALIDATION DINGBATARG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION HTTPEQUIV)) { res << VALIDATION HTTPEQUIV ": "; pvs (res, var_ [VALIDATION HTTPEQUIV].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION LANG)) { res << VALIDATION LANG ": "; pvs (res, var_ [VALIDATION LANG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION MINOR)) res << VALIDATION MINOR ": " << var_ [VALIDATION MINOR].as < int > () << "\n";
    if (var_.count (VALIDATION METANAME)) { res << VALIDATION METANAME ": "; pvs (res, var_ [VALIDATION MIMETYPE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION MIMETYPE)) { res << VALIDATION MIMETYPE ": "; pvs (res, var_ [VALIDATION METANAME].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION REL)) { res << VALIDATION REL ": "; pvs (res, var_ [VALIDATION REL].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION SGML)) { res << VALIDATION SGML ": "; pvs (res, var_ [VALIDATION SGML].as < vstr_t > ()); res << "\n"; }

    if (var_.count (WEBSITE EXTENSION)) { res << WEBSITE EXTENSION ": "; pvs (res, var_ [WEBSITE EXTENSION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WEBSITE INDEX)) res << WEBSITE INDEX ": " << var_ [WEBSITE INDEX].as < ::std::string > () << "\n";
    if (var_.count (WEBSITE SITE)) { res << WEBSITE SITE ": "; pvs (res, var_ [WEBSITE SITE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WEBSITE ROOT)) res << WEBSITE ROOT ": " << var_ [WEBSITE ROOT].as < ::std::string > () << "\n";
    if (var_.count (WEBSITE VIRTUAL)) { res << WEBSITE VIRTUAL ": "; pvs (res, var_ [WEBSITE VIRTUAL].as < vstr_t > ()); res << "\n"; }

    if (var_.count (WMIN WRITE)) { res << WMIN WRITE ": "; var_ [WMIN WRITE].as < ::std::string > (); res << "\n"; }
    if (var_.count (WMIN STUB)) res << WMIN STUB ": " << var_ [WMIN STUB].as< ::std::string > () << "\n";
    if (var_.count (WMIN HOOK)) res << WMIN HOOK ": " << var_ [WMIN HOOK].as< ::std::string > () << "\n";
    if (var_.count (WMIN MACROEND)) res << WMIN MACROEND ": " << var_ [WMIN MACROEND].as< ::std::string > () << "\n";
    if (var_.count (WMIN MACROSTART)) res << WMIN MACROSTART ": " << var_ [WMIN MACROSTART].as< ::std::string > () << "\n";
    if (var_.count (WMIN PATH)) res << WMIN PATH ": " << var_ [WMIN PATH].as< ::std::string > () << "\n";
    if (var_.count (WMIN MENTION)) { res << WMIN MENTION ": "; pvs (res, var_ [WMIN MENTION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WMIN TEMPLATE)) { res << WMIN TEMPLATE ": "; pvs (res, var_ [WMIN TEMPLATE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WMIN TEST_HEADER)) res << WMIN TEST_HEADER ": " << var_ [WMIN TEST_HEADER].as< ::std::string > () << "\n";

    if (var_.count (WMOUT CLEAR)) res << WMOUT CLEAR "\n";
    if (var_.count (WMOUT NOTIFY)) res << WMOUT NOTIFY "\n";
    if (var_.count (WMOUT RESET)) res << WMOUT RESET "\n";
    if (var_.count (WMOUT SECRET)) res << WMOUT SECRET ": " << var_ [WMOUT SECRET].as< ::std::string > () << "\n";
    res << "\n";
    return res.str (); }
