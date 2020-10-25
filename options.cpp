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

#include "standard.h"
#include "options.h"
#include "context.h"
#include "type.h"
#include "args.h"
#include "lexical.h"

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

::std::string path_in_context (const ::std::string& file)
{   ::boost::filesystem::path res (context.path ());
    res /= file;
    return res.string (); }

void options::title (const char* addendum) const
{   if (context.tell (e_severe))
    {   ::std::cout << FULLNAME " version " VERSION_STRING  " (" __DATE__ " " __TIME__ ")\n" COPYRIGHT "\n";
        if (addendum != nullptr) ::std::cout << addendum; }
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
        5 HTML 5 minor
        6
        7
        8
        9
*/

    ::boost::program_options::options_description basic ("Console Options"), primary ("Standard Options"), hidden, cmd, config, aid, line;
    ::boost::program_options::positional_options_description pos;
    pos.add (WEBSITE ROOT, 1);
    basic.add_options ()
        (HELP ",h", "output this information and exit")
        (VERSION ",V", "display version & copyright info, then exit")
        ;
    hidden.add_options ()
        (GENERAL CLASS, "do not report unrecognised classes")
        (GENERAL WEBMENTION ",w", "process webmentions")
        (GENERAL MAXFILESIZE, ::boost::program_options::value < int > (), "maximum file size to read, in megabytes (zero to set no limit)")
        (GENERAL NIDS, "output nit identifiers")
        (GENERAL NITS, "debug nits (error reporting mechanism)")
        (GENERAL RDF, "check RDFa attributes")
        (GENERAL TEST ",T", "machine readable output formatted for tests")
        (GENERAL USER, ::boost::program_options::value < ::std::string > () -> default_value ("scroggins"), "user name to supply when requested")
        (VALIDATION MINOR ",4", ::boost::program_options::value < int > (), "Validate HTML5 with this minor version (e.g. 3 for HTML 5.3)")
        (WMIN TEST_HEADER, ::boost::program_options::value < ::std::string > (), "use this file to test header parsing code")
        (WMIN HOOK, ::boost::program_options::value < ::std::string > (), "process incoming " WEBMENTION ", in JSON format, in specified file")
        (WMIN STUB, ::boost::program_options::value < ::std::string > () -> default_value ("_" PROG), "mask for file containing " WEBMENTION " HTML snippet")
        (WMIN MACROSTART, ::boost::program_options::value < ::std::string > () -> default_value ("{{"), "start of template macro")
        (WMIN MACROEND, ::boost::program_options::value < ::std::string > () -> default_value ("}}"), "start of template macro")
        (WMOUT SECRET, ::boost::program_options::value < ::std::string > (), WEBMENTION " secret")
        (WMIN WRITE , ::boost::program_options::value < ::std::string > (), "when writing " WEBMENTION " includes, write them to this path (default: site.root)")
        (WMIN MENTION, ::boost::program_options::value < vstr_t > () -> composing (), "a " WEBMENTION ", string must be source=url,target=url. May be repeated")
        (WMIN PATH, ::boost::program_options::value < ::std::string > () -> default_value (MENTION), "path for incoming web mention data files (note " GENERAL PATH ")") // not yet noted below
        (WMIN TEMPLATE ",t", ::boost::program_options::value < vstr_t > () -> composing (), "HTML snippets for adding mentions (new, changed, deleted, unchanged, unknown). May be repeated")
        (WMOUT CLEAR ",C", "clear out all web mention data")
        (WMOUT NOTIFY ",N", "notify appropriate servers of web mention updates")
        (WMOUT RESET ",R", "reset web mention data")
        ;
    line.add_options ()
        (CONFIG ",f", ::boost::program_options::value < ::std::string > (), "load configuration from this file")
        (DEFCONF ",F", "load configuration from " CONFIGURATION)
        ;
    primary.add_options ()
        (GENERAL CODES, "output feedback codes")
        (GENERAL CSS_OPTION, "do NOT load css files")
        (GENERAL CUSTOM, ::boost::program_options::value < vstr_t > () -> composing (), "Define a custom element for checking the 'is' attribute. May be repeated.")
        (GENERAL FILE ",c", ::boost::program_options::value < ::std::string > () -> default_value (PROG EXT), "file for persistent data, requires -N (note " GENERAL PATH ")")
        (GENERAL OUTPUT ",o", ::boost::program_options::value < ::std::string > (), "output file (default to the console)")
        (GENERAL NOCHANGE ",n", "report what will do, but do not actually do it")
        (GENERAL PATH ",p", ::boost::program_options::value < ::std::string > () -> default_value ("." PROG), "root directory for all " PROG " files")
        (GENERAL SLOB, "ignore slob HTML, such as forgotten closures")
        (GENERAL SSI ",I", "process simple Server Side Includes")
        (GENERAL VERBOSE ",v", ::boost::program_options::value < int > () -> default_value (static_cast <int> (default_output)), "output extra information")

        (HTML TAGS, "presume HTML files with no DOCTYPE declaration are HTML Tags, not HTML 1.0")
        (HTML RFC1867, "Reject RFC 1867 (INPUT=FILE) when processing HTML 2.0.")
        (HTML RFC1942, "Reject RFC 1942 (tables) when processing HTML 2.0.")
        (HTML RFC1980, "Reject RFC 1980 (client side image maps) when processing HTML 2.0.")
        (HTML RFC2070, "Reject RFC 2070 (internationalisation) when processing HTML 2.0.")
        (HTML VERSION, ::boost::program_options::value < ::std::string > (), "default version of HTML if no DOCTYPE is encountered (default '1.0').")

        (LINKS EXTERNAL ",e", "check external links (requires curl, sets " LINKS CHECK ")")
        (LINKS FORWARD ",3", "report http forwarding errors, e.g. 301 and 308 (sets " LINKS EXTERNAL ")")
        (LINKS CHECK ",l", "check links")
        (LINKS ONCE ",O", "report each broken external link once (sets " LINKS EXTERNAL ")")
        (LINKS REVOKE ",r", "do not check whether https certificates have been revoked (sets " LINKS EXTERNAL ")")
        (LINKS XLINK ",X", "check crosslinked ids (uses additional memory)")

        (MF VERIFY ",M", "check microformats (see https://microformats.org/)")
        (MF VERSION, ::boost::program_options::value < int > () -> default_value (3), "check this version of microformats (1, 2, or 3 for both)")
        (MF EXPORT, "export microformat data (only verified data if " MF VERIFY " is set)")

        (MICRODATA MICRODATAARG ",m", "check microdata (" PROG " only understands schema.org microdata)")
        (MICRODATA VERSION, ::boost::program_options::value < int > (), "set default schema.org major version (default 10)")
        (MICRODATA MINOR, ::boost::program_options::value < int > (), "set default schema.org minor version (default 0)")
        (MICRODATA EXPORT, "export microformat data (only verified data if " MICRODATA MICRODATAARG " is set)")

        (STATS PAGE, "report statistics for each page")
        (STATS SUMMARY ",S", "report site statistics")

        (SVG VERSION, ::boost::program_options::value < ::std::string > (), "default version of SVG if version attribute missing (requires HTML 4 or greater).")

        (VALIDATION CHARSET, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid charset. May be repeated")
        (VALIDATION CLASS, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid class. May be repeated")
        (VALIDATION CURRENCY, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid currency. May be repeated")
        (VALIDATION DINGBATARG, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid dingbat (HTML 3.0 only). May be repeated")
        (VALIDATION HTTPEQUIV, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid meta httpequiv. May be repeated")
        (VALIDATION MICRODATAARG, "Validate HTML5 microdata")
        (VALIDATION METANAME, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid meta name. May be repeated")
        (VALIDATION MIMETYPE, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid mimetype. May be repeated")
        (VALIDATION REL, ::boost::program_options::value < vstr_t > () -> composing (), "Add a valid rel. May be repeated")

        (WEBSITE ROOT ",g", ::boost::program_options::value < ::std::string > (), "website root directory (default current directory)")
        (WEBSITE EXTENSION ",x", ::boost::program_options::value < vstr_t > () -> composing (), "check files with this extension (default html). May be repeated")
        (WEBSITE INDEX ",i", ::boost::program_options::value < ::std::string > (), "index file in directories (default none)")
        (WEBSITE SITE ",s", ::boost::program_options::value < vstr_t > () -> composing (), "domain name(s) for local site (default none). May be repeated")
        (WEBSITE VIRTUAL ",L", ::boost::program_options::value < vstr_t > () -> composing (), "define virtual directory, arg syntax virtual=physical. May be repeated")
        	;
    cmd.add (basic).add (primary).add (line).add (hidden);
    config.add (primary).add (hidden);
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
        {   ::boost::program_options::store (::boost::program_options::parse_config_file (file.string ().c_str (), config, true), var_); }
        catch (...)
        {   loaded += "Error in "; loaded += file.string () + "\n";
            title (loaded.c_str ()); return; } }
    ::boost::program_options::notify (var_);
    if (var_.count (VERSION)) { title (); valid_ = true; return; }
    if (var_.count (HELP)) { title (); help (aid); valid_ = true; return; }
    valid_ = var_.count (WEBSITE ROOT);
    if (! valid_) { loaded += "\n" TYPE_HELP "\n"; title (loaded.c_str ()); return; }
    if (var_.count (GENERAL TEST) == 0) title (loaded.c_str ());
    stop_ = false; }

void options::contextualise ()
{   context.clear (var_.count (WMOUT CLEAR));

    if (var_.count (GENERAL OUTPUT))
    {   context.output (var_ [GENERAL OUTPUT].as < ::std::string > ());
        if (var_.count (GENERAL TEST) == 0) ::std::cout << "Writing to " << var_ [GENERAL OUTPUT].as < ::std::string > () << "\n"; }

    context.path (var_ [GENERAL PATH].as < ::std::string > ());
    if (! ::boost::filesystem::exists (context.path ()))
    {   context.err () << context.path () << " does not exist, am creating it.";
        ::boost::filesystem::create_directories (context.path ()); }   // if throws, then exit

    context.load_css (var_.count (GENERAL CSS_OPTION) == 0);
    context.nids (var_.count (GENERAL NIDS));
    context.nits (var_.count (GENERAL NITS));
    context.nochange (var_.count (GENERAL NOCHANGE));
    context.rdf (var_.count (GENERAL RDF));
    context.ssi (var_.count (GENERAL SSI));
    context.test (var_.count (GENERAL TEST));
    context.persisted (path_in_context (var_ [GENERAL FILE].as < ::std::string > ()));
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
    if (var_.count (GENERAL USER)) context.user (var_ [GENERAL USER].as < ::std::string > ());
    if (var_.count (GENERAL VERBOSE)) context.verbose (static_cast < e_verbose > (var_ [GENERAL VERBOSE].as < int > ()));

    if (var_.count (MF VERSION)) context.mf_version (static_cast < BYTE > (var_ [MF VERSION].as < int > ()));

    if (var_.count (MICRODATA VERSION)) context.schema_major (static_cast < BYTE > (var_ [MICRODATA VERSION].as < int > ()));
    if (var_.count (MICRODATA MINOR)) context.schema_minor (static_cast < BYTE > (var_ [MICRODATA MINOR].as < int > ()));

    if (var_.count (VALIDATION CHARSET)) type_master < t_charset > :: extend (var_ [VALIDATION CHARSET].as < vstr_t > ());
    if (var_.count (VALIDATION CLASS)) type_master < t_class > :: extend (var_ [VALIDATION CLASS].as < vstr_t > ());
    if (var_.count (VALIDATION CURRENCY)) type_master < t_currency > :: extend (var_ [VALIDATION CURRENCY].as < vstr_t > ());
    if (var_.count (VALIDATION DINGBATARG)) type_master < t_dingbat > :: extend (var_ [VALIDATION DINGBATARG].as < vstr_t > ());
    if (var_.count (VALIDATION HTTPEQUIV)) type_master < t_httpequiv > :: extend (var_ [VALIDATION HTTPEQUIV].as < vstr_t > ());
    context.microdata (var_.count (VALIDATION MICRODATAARG));
    if (var_.count (VALIDATION MINOR)) context.html_minor (static_cast < BYTE > (var_ [VALIDATION MINOR].as < int > ()));
    if (var_.count (VALIDATION METANAME)) type_master < t_metaname  > :: extend (var_ [VALIDATION METANAME].as < vstr_t > ());
    if (var_.count (VALIDATION MIMETYPE)) type_master < t_mime > :: extend (var_ [VALIDATION MIMETYPE].as < vstr_t > ());
    if (var_.count (VALIDATION REL)) type_master < t_rel > :: extend (var_ [VALIDATION REL].as < vstr_t > ());

    if (var_.count (WEBSITE INDEX)) context.index (var_ [WEBSITE INDEX].as < ::std::string > ());
    if (var_.count (WEBSITE EXTENSION)) context.extensions (var_ [WEBSITE EXTENSION].as < vstr_t > ());
    else { vstr_t ex; ex.push_back ("html"); context.extensions (ex); }
    if (var_.count (WEBSITE ROOT)) context.root (var_ [WEBSITE ROOT].as < ::std::string > ());
    if (var_.count (WEBSITE SITE)) context.site (var_ [WEBSITE SITE].as < vstr_t > ());
    if (var_.count (WEBSITE VIRTUAL)) context.virtuals (var_ [WEBSITE VIRTUAL].as < vstr_t > ());

    if (var_.count (WMIN WRITE)) context.write_path (var_ [WMIN WRITE].as < ::std::string > ());
    if (var_.count (WMIN STUB)) context.stub (var_ [WMIN STUB].as < ::std::string > ());
    if (var_.count (WMIN HOOK)) context.hook (var_ [WMIN HOOK].as < ::std::string > ());
    if (var_.count (WMIN MACROEND)) context.macro_end (var_ [WMIN MACROEND].as < ::std::string > ());
    if (var_.count (WMIN MACROSTART)) context.macro_start (var_ [WMIN MACROSTART].as < ::std::string > ());
    if (var_.count (WMIN PATH)) context.incoming (path_in_context (var_ [WMIN PATH].as < ::std::string > ()));
    if (var_.count (WMIN MENTION)) context.mentions (var_ [WMIN MENTION].as < vstr_t > ());
    if (var_.count (WMIN TEMPLATE)) context.templates ( var_ [WMIN TEMPLATE].as < vstr_t > ());
    if (var_.count (WMIN TEST_HEADER)) context.test_header (var_ [WMIN TEST_HEADER].as < ::std::string > ());

    context.notify (var_.count (WMOUT NOTIFY));
    context.reset (var_.count (WMOUT RESET));
    if (var_.count (WMOUT SECRET)) context.secret (var_ [WMOUT SECRET].as < ::std::string > ());

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
    if (var_.count (GENERAL FILE)) res << GENERAL FILE ": " << var_ [GENERAL FILE].as< ::std::string > () << "\n";
    if (var_.count (GENERAL MAXFILESIZE)) res << GENERAL MAXFILESIZE ": " << var_ [GENERAL MAXFILESIZE].as < int > () << "\n";
    if (var_.count (GENERAL NIDS)) res << GENERAL NIDS "\n";
    if (var_.count (GENERAL NITS)) res << GENERAL NITS "\n";
    if (var_.count (GENERAL NOCHANGE)) res << GENERAL NOCHANGE "\n";
    if (var_.count (GENERAL PATH)) res << GENERAL PATH ": " << var_ [GENERAL PATH].as< ::std::string > () << "\n";
    if (var_.count (GENERAL RDF)) res << GENERAL RDF "\n";
    if (var_.count (GENERAL SSI)) res << GENERAL SSI "\n";
    if (var_.count (GENERAL TEST)) res << GENERAL TEST "\n";
    if (var_.count (GENERAL USER)) res << GENERAL USER ": " << var_ [GENERAL USER].as< ::std::string > () << "\n";
    if (var_.count (GENERAL VERBOSE)) res << GENERAL VERBOSE ": " << var_ [GENERAL VERBOSE].as < int > () << "\n";
    if (var_.count (GENERAL WEBMENTION)) res << GENERAL WEBMENTION "\n";

    if (var_.count (HTML TAGS)) res << HTML TAGS "\n";
    if (var_.count (HTML RFC1867)) res << HTML RFC1867 "\n";
    if (var_.count (HTML RFC1942)) res << HTML RFC1942 "\n";
    if (var_.count (HTML RFC1980)) res << HTML RFC1980 "\n";
    if (var_.count (HTML RFC2070)) res << HTML RFC2070 "\n";
    if (var_.count (HTML VERSION)) res << HTML VERSION "\n";

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

    if (var_.count (VALIDATION CHARSET)) { res << VALIDATION CHARSET ": "; pvs (res, var_ [VALIDATION CHARSET].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION CLASS)) { res << VALIDATION CLASS ": "; pvs (res, var_ [VALIDATION CLASS].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION CURRENCY)) { res << VALIDATION CURRENCY ": "; pvs (res, var_ [VALIDATION CURRENCY].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION DINGBATARG)) { res << VALIDATION DINGBATARG ": "; pvs (res, var_ [VALIDATION DINGBATARG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION HTTPEQUIV)) { res << VALIDATION HTTPEQUIV ": "; pvs (res, var_ [VALIDATION HTTPEQUIV].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION MINOR)) res << VALIDATION MINOR ": " << var_ [VALIDATION MINOR].as < int > () << "\n";
    if (var_.count (VALIDATION METANAME)) { res << VALIDATION METANAME ": "; pvs (res, var_ [VALIDATION MIMETYPE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION MIMETYPE)) { res << VALIDATION MIMETYPE ": "; pvs (res, var_ [VALIDATION METANAME].as < vstr_t > ()); res << "\n"; }
    if (var_.count (VALIDATION REL)) { res << VALIDATION REL ": "; pvs (res, var_ [VALIDATION REL].as < vstr_t > ()); res << "\n"; }

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