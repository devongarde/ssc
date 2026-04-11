/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "utility/fileio.h"
#include "feedback/nitpick.h"
#include "ontology/ontology_version.h"
#include "attribute/attributes.h"
#include "element/elem.h"
#include "element/element_classes.h"
#include "url/url_sanitise.h"
#include "parser/html_version.h"
#include "spell/spell.h"
#include "webpage/required.h"

#define GOTCHA  "WARNING: The examination of RDFa and ontologies (but for schema.org &\n" \
                "the living standard) is experimental, and even less trustworthy than\n" \
                PROG " per se."
#define ARGSEP ","

::boost::program_options::options_description
        options::aid_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::basic_ ("Command line options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::cgi_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::cmd_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::config_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::environ_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::hidden_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::ontology_ ("Set default ontology version", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::primary_ ("General options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::risky_ ("Additional configuration file options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::valid_ ("Extend types/attributes/elements", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH);
::boost::program_options::positional_options_description options::pos_;

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
  
options::options (const context_t& c)
{   context_t def;

#define INSERT(TYPE,SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < TYPE > (SECT VAR, c.FN ());
#define INSERT_BOOL(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) \
        if (c.FN ()) insert < bool > (SECT VAR, true); \
        else insert < bool > (SECT DONT VAR, false);
#define INSERT_ENUM(TYPE,SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < ::std::string > (SECT VAR, type_master < TYPE > :: name (c.FN ()));
#define INSERT_ENV(VAR,e) \
    if (! c.environment (e).empty ()) insert < ::std::string > (ENVIRONMENT VAR, c.environment (e))
#define INSERT_INT(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < int > (SECT VAR, c.FN ());
#define INSERT_INVERTED_BOOL(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) \
        if (! c.FN ()) insert < bool > (SECT VAR, true); \
        else insert < bool > (SECT DONT VAR, false);
#define INSERT_LONG(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < long > (SECT VAR, c.FN ());
#define INSERT_PATH(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < ::std::string > (SECT VAR, c.FN ().string ());
#define INSERT_STATS(VAR,ST) \
    if (def.stats (ST) != c.stats (ST)) \
        if (c.stats (ST)) insert < bool > (STATS VAR, true); \
        else insert < bool > (STATS DONT VAR, false);
#define INSERT_STRING(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < ::std::string > (SECT VAR, c.FN ());
#define INSERT_TIME(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < ::std::time_t > (SECT VAR, c.FN ());
#define INSERT_USHORT(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < unsigned short > (SECT VAR, c.FN ());
#define INSERT_VALID(VAR,TY,EN) \
    {   const ::std::size_t xtra = type_master < TY > :: extra_values (); \
        if (xtra > 0) \
        {   vstr_t v; \
            const ::std::size_t count = enum_base_count (TY); \
            for (::std::size_t i = count; i < count + xtra; ++i) \
                v.push_back (type_master < TY > :: name (static_cast < EN > (i))); \
            if (! v.empty ()) { const ::boost::any a = v; insert < ::boost::any > (VALIDATION VAR, a); } } }
#define INSERT_VALID2(VAR,TY,EN) \
    INSERT_VALID (#VAR, TY, EN)
#define INSERT_VBP(SECT,VAR,FN) \
    { const vbp_t& v = c.FN (); if (! v.empty ()) { const ::boost::any a = v; insert < ::boost::any > (SECT VAR, a); } }
#define INSERT_VSTR(SECT,VAR,FN) \
    { const vstr_t& v = c.FN (); if (! v.empty ()) { const ::boost::any a = v; insert < ::boost::any > (SECT VAR, a); } }
#define INSERT_VREG(SECT,VAR,FN) \
    { const vreg_t& v = c.FN (); if (! v.empty ()) { const ::boost::any a = v; insert < ::boost::any > (SECT VAR, a); } }
#define INSERT_SSTR(SECT,VAR,FN) \
    { const sstr_t& v = c.FN (); if (! v.empty ()) { const ::boost::any a = v; insert < ::boost::any > (SECT VAR, a); } }
#define INSERT_UNSIGNED(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < unsigned > (SECT VAR, c.FN ());

    if (! c.environment (env_query_string).empty ())
    {   insert < ::std::string > (ENVIRONMENT QUERY_STRING, c.environment (env_query_string));
        INSERT_ENV (AUTH_TYPE, env_auth_type);
        INSERT_ENV (CONTENT_LENGTH, env_content_length);
        INSERT_ENV (CONTENT_TYPE, env_content_type);
        INSERT_ENV (GATEWAY_INTERFACE, env_gateway_interface);
        INSERT_ENV (HTTP_ACCEPT, env_http_accept);
        INSERT_ENV (PATH_INFO, env_path_info);
        INSERT_ENV (PATH_TRANSLATED, env_path_translated);
        INSERT_ENV (REMOTE_ADDR, env_remote_addr);
        INSERT_ENV (REMOTE_HOST, env_remote_host);
        INSERT_ENV (REMOTE_USER, env_remote_user);
        INSERT_ENV (REQUEST_METHOD, env_request_method);
        INSERT_ENV (SCRIPT_NAME, env_script_name);
        INSERT_ENV (SERVER_NAME, env_server_name);
        INSERT_ENV (SERVER_PORT, env_server_port);
        INSERT_ENV (SERVER_PROTOCOL, env_server_protocol);
        INSERT_ENV (SERVER_SOFTWARE, env_server_software); }  

    if (c.atomic_ext () != def.atomic_ext ())
        INSERT_SSTR (ATOMIC, EXTENSION, atomic_ext);
    INSERT_BOOL (ATOMIC, VERIFY, atomic_verify);

    INSERT_PATH (CORPUS, OUTPUT_, corpus);
    INSERT_BOOL (CORPUS, ARTICLE, article);
    INSERT_BOOL (CORPUS, BODY, body);
    INSERT_BOOL (CORPUS, MAIN, main);

    if (c.css_extension () != def.css_extension ())
        INSERT_SSTR (CSS, EXTENSION, css_extension);
    INSERT_BOOL (CSS, EXTERNAL, ext_css);
    INSERT_BOOL (CSS, VERIFY, load_css);
    INSERT_ENUM (t_css_version, CSS, VERSION, css_version);

    const ::std::string css (CSS);

    for (int i = 0; i < c_bad; ++i)
    {   const e_css_module m = static_cast < e_css_module > (i);
        if (def.css_module (m) != c.css_module (m))
            insert < int > (css + type_master < t_css_module > :: name (m), c.css_module (m)); }

    INSERT_BOOL (GENERAL, ADS, adstxt);
    INSERT_BOOL (GENERAL, CGI, cgi);
    INSERT_BOOL (GENERAL, CLASS, unknown_class);
    INSERT_BOOL (GENERAL, CLASSIC, classic);
    INSERT_BOOL (GENERAL, COMMS, comms);
    INSERT_STRING (GENERAL, COPY, out_copy);
    INSERT_STRING (GENERAL, DATAPATH, path);
    INSERT_BOOL (GENERAL, EDE, excl_def_excl);
    INSERT_VSTR (GENERAL, EXCLUDE, exclude);
    INSERT_STRING (GENERAL, HELPSITE, help);
    INSERT_LONG (GENERAL, LINE_LENGTH, line_length);
    INSERT_STRING (GENERAL, MACROEND, macro_end);
    INSERT_STRING (GENERAL, MACROSTART, macro_start);
    INSERT_INT (GENERAL, MAXFILESIZE, max_file_size);
    INSERT_STRING (GENERAL, OUTPUT_, out_name);
    INSERT_BOOL (GENERAL, PROGRESS, progress);
    INSERT_BOOL (GENERAL, RDFA, rdfa);
    INSERT_BOOL (GENERAL, ROBOTS, robtxt);
    INSERT_BOOL (GENERAL, RPT, rpt_opens);
    INSERT_BOOL (GENERAL, SECURITY, sectxt);
    INSERT_VREG (GENERAL, SILENCE, silence);
    INSERT_BOOL (GENERAL, TEST, test);
#ifndef NO_FRED
    INSERT (::std::size_t, GENERAL, THREAD, fred);
#endif // NO_FRED
    INSERT_BOOL (GENERAL, UPDATE, vcs);
    INSERT_VSTR (GENERAL, URL_VAR, urlvar);
    INSERT_BOOL (GENERAL, VCS, vcs);
    INSERT_ENUM (t_severity, GENERAL, VERBOSE, verbose);
    INSERT_BOOL (GENERAL, YGGDRISIL, yggdrisil);

    if (def.analysis () != c.analysis ())
        insert < ::std::string > (HTML ANALYSIS, ::boost::lexical_cast < ::std::string > (static_cast < int > (c.analysis ())));
    INSERT_BOOL (HTML, ARIA, aria);
    INSERT_BOOL (HTML, CHROME, chrome);
    INSERT_SSTR (HTML, CUSTOM, custom_elements);
    INSERT_BOOL (HTML, EFFICIENT, efficient);
    INSERT_BOOL (HTML, FORCE, force_version);
    INSERT_BOOL (HTML, IE, ie);
    INSERT_VSTR (HTML, IGNORED, ignore);
    INSERT_STRING (HTML, LANG, lang);
    INSERT_BOOL (HTML, MOZILLA, mozilla);
    INSERT_BOOL (HTML, OPERA, opera);
    INSERT_BOOL (HTML, NETSCAPE, netscape);
    INSERT_BOOL (HTML, REL, rel);
    INSERT_BOOL (HTML, RFC1867, rfc_1867);
    INSERT_BOOL (HTML, RFC1942, rfc_1942);
    INSERT_BOOL (HTML, RFC1980, rfc_1980);
    INSERT_BOOL (HTML, RFC2070, rfc_2070);
    INSERT_BOOL (HTML, RUBY, ruby);
    INSERT_BOOL (HTML, SAFARI, safari);
    // HTML SNIPPET
    INSERT_BOOL (HTML, TAGS, presume_tags);
    INSERT (::std::size_t, HTML, TITLE, title);
    if (def.html_ver () != c.html_ver ()) insert < ::std::string > (HTML VERSION, c.html_ver ().name ());
    INSERT_BOOL (HTML, WXARG, wx);
    INSERT_STRING (HTML, WX_SNIPPET, wx_snippet);

    if (c.jsonld_extension () != def.jsonld_extension ()) INSERT_SSTR (JSONLD, EXTENSION, jsonld_extension);
    INSERT_VSTR (JSONLD, ONTOLOGY_, jsonld_ontology);
    INSERT_BOOL (JSONLD, PRETTY, pretty);
    INSERT_BOOL (JSONLD, VERIFY, jsonld);
    INSERT_ENUM (t_js_version, JSONLD, VERSION, jsonld_version);

    INSERT_BOOL (LINKS, CHECK, links);
    INSERT_BOOL (LINKS, EXAMPLE, example);
    INSERT_BOOL (LINKS, EXTERNAL, external);
    INSERT_BOOL (LINKS, FORWARD, forwarded);
    INSERT_SSTR (LINKS, IGNORED, no_ex_check);
    INSERT_BOOL (LINKS, LOCAL, local);
    INSERT_BOOL (LINKS, ONCE, once);
    INSERT_VSTR (LINKS, PRETEND, pretend);
    INSERT_VSTR (LINKS, REPORT, report);
    { const vstr_t& v = required_page_list (); if (! v.empty ()) { const ::boost::any a = v; insert < ::boost::any > (LINKS REQUIRED, a); } }
    INSERT_BOOL (LINKS, REVOKE, revoke);
    INSERT_BOOL (LINKS, SPECIAL, special);
    INSERT_BOOL (LINKS, XLINK, crosslinks);

    INSERT_ENUM (t_math_version, MATH, VERSION, math_version);

    INSERT_BOOL (MF, EXPORT, mf_export);
    INSERT_BOOL (MF, PRETTY, mf_pretty);
    INSERT_BOOL (MF, VERIFY, mf_verify);
    INSERT_INT (MF, VERSION, mf_version);

    INSERT_VSTR (NITS, ABHORRENT, abhorrent);
    INSERT_STRING (NITS, CACHE, cache);
    INSERT_VSTR (NITS, CATASTROPHE, catastrophe);
    INSERT_VSTR (NITS, COMMENT, comment);
    INSERT_VSTR (NITS, DBG, debug);
    INSERT_BOOL (NITS, EXPAND, expand);
    INSERT_BOOL (NITS, EXTRA, extra);
    INSERT_VSTR (NITS, INFO, inform);
    INSERT_BOOL (NITS, NIDS, nids);
    INSERT_ENUM (t_quote_style, NITS, QUOTE, quote_style);
    INSERT_INVERTED_BOOL (NITS, ROOT, not_root);
    INSERT_BOOL (NITS, SPEC, spec);
    INSERT_VSTR (NITS, SILENCE, silent);
    INSERT_BOOL (NITS, UNIQUE, nits_nits_nits);
    INSERT_ENUM (t_severity, NITS, VERBOSE, verbose);
    INSERT_VSTR (NITS, WARNING, warning);
    INSERT_BOOL (NITS, WATCH, nits);
    INSERT_VSTR (NITS, WHOOPS, error);
    INSERT_STRING (NITS, XXX, x);
    INSERT_ENUM (t_severity, NITS, ERROREXIT, report_error);

    INSERT_BOOL (ONTOLOGY, EXPORT, md_export);
    INSERT_BOOL (ONTOLOGY, VERIFY, ontology);
    INSERT_STRING (ONTOLOGY, ROOT, export_root);
    INSERT_VSTR (ONTOLOGY, VIRTUAL, exports);
    for (int i = s_none + 1; i < s_error; ++i)
    {   const e_ontology es = static_cast < e_ontology > (i);
        if (is_faux_schema (es)) continue;
        if (get_ontology_version_count (es) < 1) continue;
        ::std::string arg (ONTOLOGY);
        arg += ontology_names.get (es, ONTOLOGY_NAME);
        if (corresponding_ontology_version (es, c.html_ver ()) != c.ontology_ver (es))
            insert < ::std::string > (arg, c.ont_ver (es)); }

    INSERT_BOOL (OUTPUT, APATH, absolute_path);
    INSERT_STRING (OUTPUT, ACCOUNT, account);
    INSERT_PATH (OUTPUT, BACK, back);
    INSERT_STRING (OUTPUT, BUILD, build);
    INSERT_VSTR (OUTPUT, DESCRIPTION, output_description);
    INSERT_STRING (OUTPUT, FORMAT, output_format);
    INSERT_PATH (OUTPUT, HOME, home);
    INSERT_STRING (OUTPUT, OVERRIDE, output_override);
#ifdef SIGNING
    INSERT_PATH (OUTPUT, PASSWORD, output_password);
    INSERT_PATH (OUTPUT, PRIVATE, output_private);
    INSERT_PATH (OUTPUT, PUBLIC, output_public);
    INSERT_BOOL (OUTPUT, SIGN, sign);
    INSERT_PATH (OUTPUT, SIGNATURE, output_signature);
#endif // SIGNING
    INSERT_PATH (OUTPUT, STYLESHEET, stylesheet);
    INSERT_STRING (OUTPUT, TIME, output_time);
    INSERT_STRING (OUTPUT, USERNAME, username);
    INSERT_BOOL (OUTPUT, VERIFY, verify);

    if (c.rsl_ext () != def.rsl_ext ())
        INSERT_SSTR (RSL, EXTENSION, rsl_ext);
    INSERT_BOOL (RSL, VERIFY, rsl_verify);

    if (c.rss_ext () != def.rss_ext ())
        INSERT_SSTR (RSS, EXTENSION, rss_ext);
    INSERT_BOOL (RSS, VERIFY, rss_verify);
    INSERT_ENUM (t_rss_version, RSS, VERSION, rss_version);

    INSERT_BOOL (SHADOW, CHANGED, shadow_changed);
    INSERT_BOOL (SHADOW, COMMENT, shadow_comment);
    INSERT_ENUM (t_copy, SHADOW, COPY, copy);
    INSERT_BOOL (SHADOW, ENABLE, shadow_enable);
    INSERT_STRING (SHADOW, FICHIER, shadow_persist);
    INSERT_VSTR (SHADOW, IGNORED, shadow_ignore);
    INSERT_BOOL (SHADOW, INFO, info);
    INSERT_STRING (SHADOW, MSG, msg);
    INSERT_VSTR (SHADOW, NAUGHTY, naughty);
    INSERT_VSTR (SHADOW, NICE, nice);
    INSERT_VSTR (SHADOW, NOTE, note);
    INSERT_VSTR (SHADOW, REPLACE, replace);
    INSERT_STRING (SHADOW, ROOT, shadow_root);
    INSERT_BOOL (SHADOW, SPACING, shadow_space);
    INSERT_BOOL (SHADOW, SSI_, shadow_ssi);
    INSERT_BOOL (SHADOW, UPDATE, update);
    INSERT_VSTR (SHADOW, VIRTUAL, shadows);
    INSERT_STRING (SHADOW, INDEX, index);

    if (c.extensions () != def.extensions ())
        INSERT_SSTR (WEBSITE, EXTENSION, extensions);
    INSERT_STRING (WEBSITE, INDEX, index);
    INSERT_STRING (WEBSITE, ROOT, root);
    INSERT_SSTR (WEBSITE, SITE, site);
    INSERT_VSTR (WEBSITE, VIRTUAL, virtuals);

#ifndef NOSPELL
    INSERT_VSTR (SPELL, ACCEPT, spellings);
    INSERT_BOOL (SPELL, CASED, cased);
    INSERT_BOOL (SPELL, CHECK, spell);
    INSERT_BOOL (SPELL, ICU, icu);
    INSERT_VSTR (SPELL, LIST, spell_list);
#ifdef HUNSPELL
    INSERT_PATH (SPELL, PATH, spell_path);
    INSERT_VSTR (SPELL, DDICT, dict);
    INSERT_VSTR (SPELL, DLANG, dlang);
#endif // HUNSPELL
#endif // NOSPELL

    INSERT_BOOL (SSI, VERIFY, ssi);
    INSERT_TIME (SSI, DATETIME, ssi_date);
    INSERT_STRING (SSI, DOCARGS, ssi_doc_args);
    INSERT_STRING (SSI, ECHOMSG, ssi_echomsg);
    INSERT_STRING (SSI, ERRMSG, ssi_errmsg);
    INSERT_BOOL (SSI, EXECRUN, ssi_exec_run);
    INSERT_STRING (SSI, EXECTEXT, ssi_exec_text);
    INSERT_TIME (SSI, LASTMOD, ssi_lastmod);
    INSERT_STRING (SSI, QUERYSTRING, ssi_query_string);
    INSERT_STRING (SSI, TIMEFMT, ssi_timefmt);
    INSERT_STRING (SSI, USERNAME, ssi_user_name);

    INSERT_STATS (ABBR, rcb_abbreviation);
    INSERT_STATS (ANNOTATION, rcb_annotation);
    INSERT_STATS (ATTRIB, rcb_attribute);
    INSERT_STATS (CAT, rcb_category);
    INSERT_STATS (CHARVAR, rcb_character_variant);
    INSERT_STATS (CLASS, rcb_class);
    INSERT_STATS (CONNAME, rcb_content_name);
    INSERT_STATS (COUSTYLE, rcb_counter_style);
    INSERT_STATS (CSSPROP, rcb_css_property);
    INSERT_STATS (CUSTMED, rcb_custom_media);
    INSERT_STATS (CUSTPROP, rcb_custom_property);
    INSERT_STATS (DFN, rcb_definition);
    INSERT_STATS (DTDD, rcb_name_value);
    INSERT_STATS (ELEMENT, rcb_element);
    INSERT_STATS (WHOOPS, rcb_error);
    INSERT_STRING (STATS, EXPORT, stats);
    INSERT_STATS (FICHIER, rcb_file);
    INSERT_STATS (FONT, rcb_font);
    INSERT_STATS (FONT_FAMILY, rcb_font_family);
    INSERT_STATS (HIGHLIGHT, rcb_highlight);
    INSERT_STATS (HISTFORM, rcb_historical_form);
    INSERT_STATS (ID, rcb_id);
    INSERT_STATS (ITEMID, rcb_itemid);
    INSERT_STATS (KEYFRAME, rcb_keyframe);
    INSERT_STATS (LAYER, rcb_layer);
    INSERT_STATS (META, rcb_meta);
    INSERT_STATS (ONT, rcb_ontology);
    INSERT_STATS (ORNAMENT, rcb_ornament);
    INSERT_STATS (PAGE, rcb_page);
    INSERT_STATS (PAGE_NAME, rcb_page_name);
    INSERT_STATS (PALETTE, rcb_palette);
    INSERT_STATS (PROPER, rcb_property);
    INSERT_STATS (REFERENCE, rcb_reference);
    INSERT_STATS (REGION, rcb_region);
    INSERT_STATS (SCROLL_ANIM, rcb_scroll_animation);
    INSERT_STATS (STATEMENT, rcb_statement);
    INSERT_STATS (STYLESET, rcb_styleset);
    INSERT_STATS (STYLISTIC, rcb_stylistic);
    INSERT_STATS (SUMMARY, rcb_summary);
    INSERT_STATS (SWASH, rcb_swash);
    INSERT_STATS (VERSION, rcb_version);
    INSERT_STATS (VIEW, rcb_view);

    INSERT_STRING (SVG, VERSION, svg);

    INSERT_VSTR (VALIDATION, ATTRIB, attrib);
    INSERT_BOOL (VALIDATION, MICRODATAARG, microdata);
    INSERT_VSTR (VALIDATION, ELEMENT, elem);
    INSERT_VSTR (VALIDATION, ELEMATTR, elem_attrib);

    INSERT_VALID (CHARSET, t_charset, e_charset);
    INSERT_VALID (CLASS, t_class, e_class);
    INSERT_VALID (COLOR, t_fixedcolour, e_fixedcolour);
    INSERT_VALID (COLOUR, t_fixedcolour, e_fixedcolour);
    INSERT_VALID (COUNTRY, t_country, e_country);
    INSERT_VALID (CURRENCY, t_currency, e_currency);
    INSERT_VALID (DINGBATARG, t_dingbat, e_dingbat);
    INSERT_VALID (EXTENSION, t_format, e_format);
    INSERT_VALID (FF, t_css_font_feature, e_css_font_feature);
    INSERT_VALID (FV, t_css_font_variation, e_css_font_variation);
    INSERT_VALID (HTTPEQUIV, t_httpequiv, e_httpequiv);
    INSERT_VALID (LANG, t_lang, e_lang);
    INSERT_VALID (REL, t_rel, e_rel);
    INSERT_VALID (METANAME, t_metaname, e_metaname);
    INSERT_VALID (MIMETYPE, t_mime, e_mimetype);
    INSERT_VALID (SGML, t_sgml, e_sgml); 

    INSERT_VALID2 (accrual_method, t_accrual_method, e_accrual_method);
    INSERT_VALID2 (accrual_periodicity, t_accrual_periodicity, e_accrual_periodicity);
    INSERT_VALID2 (accrual_policy, t_accrual_policy, e_accrual_policy);
    INSERT_VALID2 (action, t_action, e_action);
    INSERT_VALID2 (advar, t_advar, e_advar);
    INSERT_VALID2 (align3, t_align3, e_align3);
    INSERT_VALID2 (alignplus, t_alignplus, e_alignplus);
    INSERT_VALID2 (as, t_as, e_as);
    INSERT_VALID2 (as_units, t_as_units, e_as_units);
    INSERT_VALID2 (autocapitalise, t_autocapitalise, e_autocapitalise);
    INSERT_VALID2 (autocomplete, t_autocomplete, e_autocomplete);
    INSERT_VALID2 (baselineshift, t_baselineshift, e_baselineshift);
    INSERT_VALID2 (citype, t_citype, e_citype);
    INSERT_VALID2 (cntype, t_cntype, e_cntype);
    INSERT_VALID2 (command2, t_command2, e_command2);
    INSERT_VALID2 (composite_operator, t_composite_operator, e_composite_operator);
    INSERT_VALID2 (crs_whitebalance, t_crs_whitebalance, e_crs_whitebalance);
    INSERT_VALID2 (decalign, t_decalign, e_decalign);
    INSERT_VALID2 (dingbat, t_dingbat, e_dingbat);
    INSERT_VALID2 (dir, t_dir, e_dir);
    INSERT_VALID2 (display_align, t_display_align, e_display_align);
    INSERT_VALID2 (dominantbaseline, t_dominantbaseline, e_dominantbaseline);
    INSERT_VALID2 (enterkeyhint, t_enterkeyhint, e_enterkeyhint);
    INSERT_VALID2 (evt_action, t_evt_action, e_evt_action);
    INSERT_VALID2 (figalign, t_figalign, e_figalign);
    INSERT_VALID2 (fontname, t_fontname, e_fontname);
    INSERT_VALID2 (halign, t_halign, e_halign);
    INSERT_VALID2 (icc, t_icc, e_icc);
    INSERT_VALID2 (inputmode, t_inputmode, e_inputmode);
    INSERT_VALID2 (inputplus, t_inputplus, e_inputplus);
    INSERT_VALID2 (inputtype, t_inputtype, e_inputtype);
    INSERT_VALID2 (inputtype3, t_inputtype3, e_inputtype3);
    INSERT_VALID2 (inputtype32, t_inputtype32, e_inputtype32);
    INSERT_VALID2 (inputtype4, t_inputtype4, e_inputtype4);
    INSERT_VALID2 (inputtype5, t_inputtype5, e_inputtype5);
    INSERT_VALID2 (kind, t_kind, e_kind);
    INSERT_VALID2 (linebreak, t_linebreak, e_linebreak);
    INSERT_VALID2 (listtype, t_listtype, e_listtype);
    INSERT_VALID2 (mah, t_mah, e_mah);
    INSERT_VALID2 (mathalign, t_mathalign, e_mathalign);
    INSERT_VALID2 (mathvariant, t_mathvariant, e_mathvariant);
    INSERT_VALID2 (matrixtype, t_matrixtype, e_matrixtype);
    INSERT_VALID2 (media, t_media, e_media);
    INSERT_VALID2 (method, t_method, e_method);
    INSERT_VALID2 (mf_identifier, t_mf_identifier, e_mf_identifier);
    INSERT_VALID2 (mf_itemtype, t_mf_itemtype, e_mf_itemtype);
    INSERT_VALID2 (mf_listing_action, t_mf_listing_action, e_mf_listing_action);
    INSERT_VALID2 (mf_method, t_mf_method, e_mf_method);
    INSERT_VALID2 (mf_reviewtype, t_mf_reviewtype, e_mf_reviewtype);
    INSERT_VALID2 (musickey, t_musickey, e_musickey);
    INSERT_VALID2 (namedspace, t_namedspace, e_namedspace);
    INSERT_VALID2 (mathnotation, t_mathnotation, e_mathnotation);
    INSERT_VALID2 (ogtype, t_ogtype, e_ogtype);
    INSERT_VALID2 (paintkeyword, t_paintkeyword, e_paintkeyword);
    INSERT_VALID2 (pam_ccv, t_pam_ccv, e_pam_ccv);
    INSERT_VALID2 (pcmm_status, t_pcmm_status, e_pcmm_status);
    INSERT_VALID2 (plusstyle, t_plusstyle, e_plusstyle);
    INSERT_VALID2 (pointer_events, t_pointer_events, e_pointer_events);
    INSERT_VALID2 (pri_img_colour, t_pri_img_colour, e_pri_img_colour);
    INSERT_VALID2 (pri_img_technique, t_pri_img_technique, e_pri_img_technique);
    INSERT_VALID2 (pri_img_viewpoint, t_pri_img_viewpoint, e_pri_img_viewpoint);
    INSERT_VALID2 (print, t_print, e_print);
    INSERT_VALID2 (prism_ad_pos, t_prism_ad_pos, e_prism_ad_pos);
    INSERT_VALID2 (prism_ad_type, t_prism_ad_type, e_prism_ad_type);
    INSERT_VALID2 (prism_ag_type, t_prism_ag_type, e_prism_ag_type);
    INSERT_VALID2 (prism_audience_sector, t_prism_audience_sector, e_prism_audience_sector);
    INSERT_VALID2 (prism_ccv, t_prism_ccv, e_prism_ccv);
    INSERT_VALID2 (prism_class, t_prism_class, e_prism_class);
    INSERT_VALID2 (prism_contenttype, t_prism_contenttype, e_prism_contenttype);
    INSERT_VALID2 (prism_cvp, t_prism_cvp, e_prism_cvp);
    INSERT_VALID2 (prism_genre, t_prism_genre, e_prism_genre);
    INSERT_VALID2 (prism_icv, t_prism_icv, e_prism_icv);
    INSERT_VALID2 (prism_pasv, t_prism_pasv, e_prism_pasv);
    INSERT_VALID2 (prism_pcv, t_prism_pcv, e_prism_pcv);
    INSERT_VALID2 (prism_pfv, t_prism_pfv, e_prism_pfv);
    INSERT_VALID2 (prism_ptv, t_prism_ptv, e_prism_ptv);
    INSERT_VALID2 (prism_rcv, t_prism_rcv, e_prism_rcv);
    INSERT_VALID2 (prism_role, t_prism_role, e_prism_role);
    INSERT_VALID2 (prs_action, t_prs_action, e_prs_action);
    INSERT_VALID2 (quote_style, t_quote_style, e_quote_style);
    INSERT_VALID2 (recipe_content, t_recipe_content, e_recipe_content);
    INSERT_VALID2 (recipe_course, t_recipe_course, e_recipe_course);
    INSERT_VALID2 (recipe_cuisine, t_recipe_cuisine, e_recipe_cuisine);
    INSERT_VALID2 (recipe_dietary, t_recipe_dietary, e_recipe_dietary);
    INSERT_VALID2 (recipe_dish, t_recipe_dish, e_recipe_dish);
    INSERT_VALID2 (recipe_exclusion, t_recipe_exclusion, e_recipe_exclusion);
    INSERT_VALID2 (recipe_kit, t_recipe_kit, e_recipe_kit);
    INSERT_VALID2 (recipe_meal, t_recipe_meal, e_recipe_meal);
    INSERT_VALID2 (recipe_method, t_recipe_method, e_recipe_method);
    INSERT_VALID2 (recipe_source, t_recipe_source, e_recipe_source);
    INSERT_VALID2 (recipe_special, t_recipe_special, e_recipe_special);
    INSERT_VALID2 (recipe_time, t_recipe_time, e_recipe_time);
    INSERT_VALID2 (referrer, t_referrer, e_referrer);
    INSERT_VALID2 (rendering_in_tents, t_rendering_in_tents, e_rendering_in_tents);
    INSERT_VALID2 (robotic, t_robotic, e_robotic);
    INSERT_VALID2 (rsl_disclaimer, t_rsl_disclaimer, e_rsl_disclaimer);
    INSERT_VALID2 (rsl_payment, t_rsl_payment, e_rsl_payment);
    INSERT_VALID2 (rsl_usage, t_rsl_usage, e_rsl_usage);
    INSERT_VALID2 (rsl_user, t_rsl_user, e_rsl_user);
    INSERT_VALID2 (rsl_warranty, t_rsl_warranty, e_rsl_warranty);
    INSERT_VALID2 (rss_version, t_rss_version, e_rss_version);
    INSERT_VALID2 (rules, t_rules, e_rules);
    INSERT_VALID2 (sandbox, t_sandbox, e_sandbox);
    INSERT_VALID2 (security, t_security, e_security);
    INSERT_VALID2 (shape7, t_shape7, e_shape7);
    INSERT_VALID2 (shape_rendering, t_shape_rendering, e_shape_rendering);
    INSERT_VALID2 (ssi, t_ssi, e_ssi);
    INSERT_VALID2 (ssi_comparison, t_ssi_comparison, e_ssi_comparison);
    INSERT_VALID2 (ssi_config, t_ssi_config, e_ssi_config);
    INSERT_VALID2 (ssi_encoding, t_ssi_encoding, e_ssi_encoding);
    INSERT_VALID2 (ssi_env, t_ssi_env, e_ssi_env);
    INSERT_VALID2 (svg_align, t_svg_align, e_svg_align);
    INSERT_VALID2 (svg_display, t_svg_display, e_svg_display);
    INSERT_VALID2 (svg_feature, t_svg_feature, e_svg_feature);
    INSERT_VALID2 (svg_fontstretch, t_svg_fontstretch, e_svg_fontstretch);
    INSERT_VALID2 (svg_fontstretch_ff, t_svg_fontstretch_ff, e_svg_fontstretch_ff);
    INSERT_VALID2 (svg_fontstyle, t_svg_fontstyle, e_svg_fontstyle);
    INSERT_VALID2 (svg_fontweight, t_svg_fontweight, e_svg_fontweight);
    INSERT_VALID2 (svg_fontweight_ff, t_svg_fontweight_ff, e_svg_fontweight_ff);
    INSERT_VALID2 (svg_mode, t_svg_mode, e_svg_mode);
    INSERT_VALID2 (svg_overflow, t_svg_overflow, e_svg_overflow);
    INSERT_VALID2 (svg_version, t_svg_version, e_svg_version);
    INSERT_VALID2 (svg_version_grand, t_svg_version_grand, e_svg_version_grand);
    INSERT_VALID2 (tableframe, t_tableframe, e_tableframe);
    INSERT_VALID2 (text_decoration, t_text_decoration, e_text_decoration);
    INSERT_VALID2 (text_rendering, t_text_rendering, e_text_rendering);
    INSERT_VALID2 (tld, t_tld, e_tld);
    INSERT_VALID2 (transform_anim, t_transform_anim, e_transform_anim);
    INSERT_VALID2 (transform_fn, t_transform_fn, e_transform_fn);
    INSERT_VALID2 (turbulence_type, t_turbulence_type, e_turbulence_type);
    INSERT_VALID2 (unicode_bidi, t_unicode_bidi, e_unicode_bidi);
    INSERT_VALID2 (vector_effect_2, t_vector_effect_2, e_vector_effect_2);
    INSERT_VALID2 (xmlns, t_xmlns, e_xmlns);
    INSERT_VALID2 (xmpdm_audio_channel, t_xmpdm_audio_channel, e_xmpdm_audio_channel);
    INSERT_VALID2 (xmpdm_audio_sample, t_xmpdm_audio_sample, e_xmpdm_audio_sample);
    INSERT_VALID2 (xmpdm_camera_angle, t_xmpdm_camera_angle, e_xmpdm_camera_angle);
    INSERT_VALID2 (xmpdm_camera_move, t_xmpdm_camera_move, e_xmpdm_camera_move);
    INSERT_VALID2 (xmpdm_pulldown, t_xmpdm_pulldown, e_xmpdm_pulldown);
    INSERT_VALID2 (xmpdm_shotsize, t_xmpdm_shotsize, e_xmpdm_shotsize);
    INSERT_VALID2 (xmpdm_stretchmode, t_xmpdm_stretchmode, e_xmpdm_stretchmode);
    INSERT_VALID2 (xmpdm_time_format, t_xmpdm_time_format, e_xmpdm_time_format);
    INSERT_VALID2 (xmpdm_time_signature, t_xmpdm_time_signature, e_xmpdm_time_signature);
    INSERT_VALID2 (xmpdm_video_pixeldepth, t_xmpdm_video_pixeldepth, e_xmpdm_video_pixeldepth);

    if (c.vtt_extension () != def.vtt_extension ())
        INSERT_SSTR (VTT, EXTENSION, vtt_extension);
    INSERT_BOOL (VTT, VERIFY, load_vtt);

#undef INSERT
#undef INSERT_BOOL
#undef INSERT_ENUM
#undef INSERT_ENV
#undef INSERT_INT
#undef INSERT_INVERTED_BOOL
#undef INSERT_PATH
#undef INSERT_STATS
#undef INSERT_STRING
#undef INSERT_VALID
#undef INSERT_VALID2
#undef INSERT_VSTR
}

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

void options::process_css_level (context_t& c, const e_css_module m, int& n, nitpick& nits, const char* opt, const char* name, const int maxlevel, const bool accept_1)
{   if (get_css_level (n, nits, opt, name, maxlevel, accept_1))
        c.css_module (m, n); }

bool options::is_be (const char* yo)
{   try
    {   if (var_ [yo].as <bool> ()) return true; }
    catch (...)
    { }
    return false; }

void options::yea_nay (context_t& con, context_t& (context_t::*fn) (const bool ), nitpick& nits, const char* yea, const char* nay)
{   VERIFY_NOT_NULL (fn, __FILE__, __LINE__);
    try
    {   const bool on = var_ [yea].as <bool> ();
        const bool off = var_ [nay].as <bool> ();
        if (off)
        {   if (on) nits.pick (nit_yea_nay, es_info, ec_init, "when both ", nay, " and ", yea, " are used, ", nay, " applies");
            (con.*fn) (false); }
        else if (on) (con.*fn) (true); }
    catch (...) { } }

void options::yea_nay (context_t& c, const e_report r, nitpick& nits, const char* yea, const char* nay)
{   try
    {   const bool on = var_ [yea].as <bool> ();
        const bool off = var_ [nay].as <bool> ();
        if (off)
        {   if (on) nits.pick (nit_yea_nay, es_info, ec_init, "when both ", nay, " and ", yea, " are used, ", nay, " applies");
            c.stats (r, false); }
        else if (on) c.stats (r, true); }
    catch (...) { } }

void options::yea_nay (context_t& c, const e_css_module m, nitpick& nits, const char* yea, const char* nay)
{   try
    {   const bool on = var_ [yea].as <bool> ();
        const bool off = var_ [nay].as <bool> ();
        if (off)
        {   if (on) nits.pick (nit_yea_nay, es_info, ec_init, "when both ", nay, " and ", yea, " are used, ", nay, " applies");
            c.css_module (m, false); }
        else if (on) c.css_module (m, true); }
    catch (...) { } }

void options::init (context_t& c)
{   if (cmd_.options ().size () > 0) return;
    pos_.add (WEBSITE ROOT, 1);
    ::std::string defconf ("Load configuration from ");
    defconf += context.default_config_file ().string ();
    defconf += ".";
    basic_.add_options ()
        (ASK ARGSEP ASK_SW_, ::boost::program_options::bool_switch (), "Ask for parameters")
        (CONFIG ARGSEP FILE_SW_, ::boost::program_options::value < ::std::string > (), "Load configuration from this file.")
        (DEFCONF ARGSEP DEFCONF_SW_, ::boost::program_options::bool_switch (), defconf.c_str ())
        (HELP ARGSEP HELP_SW_, ::boost::program_options::bool_switch (), "Output this information and exit.")
        (HTML SNIPPET ARGSEP SNIPPET_SW_, ::boost::program_options::value < ::std::string > (), "Only nitpick the given snippet of HTML.")
        (ONTOLOGY LIST, ::boost::program_options::bool_switch (), "List known ontology schema for microdata andor RDFa, then exit.")
        (SHELL ARGSEP SHELL_SW_, ::boost::program_options::bool_switch (), "Use simple shell (h for help, q to quit).")
        (SWITCHES ARGSEP SWITCH_SW_, ::boost::program_options::bool_switch (), "Report switches seen, and exit.")
        (VALIDATION, ::boost::program_options::bool_switch (), "List attribute types that can be given additional 'valid' values, then exit.")
        (VERSION ARGSEP VERSION_SW_, ::boost::program_options::bool_switch (), "Display version and copyright gen, then exit.")
        ;
    cgi_.add_options ()
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
    environ_.add_options ()
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
    hidden_.add_options ()
        (DONT ASK ARGSEP DONTASK_SW_, ::boost::program_options::bool_switch (), "Stop asking for parameters")

#ifdef NO_FRED
        (GENERAL DEFTHRD ARGSEP DFTHRD_SW_, ::boost::program_options::value < int > (), "If no setting specifies the thread count, set it to this.")
#endif // NO_FRED
        (GENERAL HELPSITE, ::boost::program_options::value < ::std::string > () -> default_value (WEBADDR "help/"), "web address of " PROG " help content.")
        (GENERAL COPY, ::boost::program_options::value < ::std::string > (), "Copy output from this file (intended for testing).")
        (GENERAL RPT, ::boost::program_options::bool_switch (), "Report when CSS files opened.")
        (GENERAL DONT RPT, ::boost::program_options::bool_switch (), "Say nowt when CSS files opened.")
#ifdef NO_FRED
        (GENERAL THREAD ARGSEP THREAD_SW_, ::boost::program_options::value < int > (), "Number of threads (default appropriate for the hardware).")
#endif // NO_FRED
        (GENERAL VERBOSE, ::boost::program_options::value < ::std::string > (), "Use --" NITS VERBOSE)
        (GENERAL YGGDRISIL, ::boost::program_options::bool_switch (), "Sniff yggdrisil.")

        (HTML ANALYSIS ARGSEP ANAL_SW_, ::boost::program_options::value < ::std::string > (), "Style of nitpick analysis: one of default, original, aug25, or dec25 (intended for testing).")
        (HTML SLOVEN, ::boost::program_options::bool_switch (), "Do not nitpick slovenly HTML such as missing closures, slovenly typography, etc..")
        (HTML DONT SLOVEN, ::boost::program_options::bool_switch (), "Nitpick slovenly HTML such as missing closures, slovenly typography, etc..")
        (HTML WX_SNIPPET, ::boost::program_options::value < ::std::string > (), "Snippet seen in wx intro dialogue.")

        (NITS CACHE, ::boost::program_options::value < ::std::string > (), "Output nits on cache usage of filenames containing argument (no wildcards, except use \"*\" for all; empty for no report).")
        (NITS FORMAT, ::boost::program_options::value < ::std::string > (), "Produce output in this format: \"html\", \"text\" (default), \"xhtml\", or a filename (see docs for layout).")
        (NITS OVERRIDE, ::boost::program_options::value < ::std::string > (), "Output nits in this format (overrides " NITS FORMAT "; for automation).")
        (NITS SPEC, ::boost::program_options::bool_switch (), "Output nits in test spec format (requires -T).")
        (NITS DONT SPEC, ::boost::program_options::bool_switch (), "Do not output nits in test spec format.")
        (NITS XXX, ::boost::program_options::value < ::std::string > (), "Output nits on cache usage from page names containing argument (empty for no report); may be combined with " NITS CACHE ".")

        (OUTPUT BUILD, ::boost::program_options::value < ::std::string > (), "Output this as the compile time rather than the actual compile time (used for testing).")
#ifndef SIGNING
        (OUTPUT PASSWORD, ::boost::program_options::value < ::std::string > (), "the file containing the password for the private key, if any (ignored, signing not available)")
        (OUTPUT PRIVATE, ::boost::program_options::value < ::std::string > (), "the file containing the private key used for the signature (ignored, signing not available)")
        (OUTPUT PUBLIC, ::boost::program_options::value < ::std::string > (), "the file containing the public key used to verify the signature (ignored, signing not available)")
        (OUTPUT SIGN, ::boost::program_options::bool_switch (), "Sign the output (requires --" OUTPUT SIGNATURE ", --" OUTPUT PRIVATE ", and --" OUTPUT PUBLIC ") (ignored, signing not available)")
        (OUTPUT DONT SIGN, ::boost::program_options::bool_switch (), "Do not sign the output (ignored, signing not available)")
        (OUTPUT SIGNATURE, ::boost::program_options::value < ::std::string > (), "output the signature to this file (requires --" OUTPUT PRIVATE ") (ignored, signing not available)")
#endif // SIGNING
        (OUTPUT TIME, ::boost::program_options::value < ::std::string > (), "The date/time when the output was produced (used for testing; default: now)")

#ifdef NOSPELL
        (SPELL ACCEPT, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore this word in spell checks; may be repeated.")
        (SPELL CASED, ::boost::program_options::bool_switch (), "Nitpick wrongly cased but correctly spelt words.")
        (SPELL DONT CASED, ::boost::program_options::bool_switch (), "Ignore case when checking spelling.")
        (SPELL CHECK ARGSEP SPELL_SW_, ::boost::program_options::bool_switch (), "Check spelling (see also --" HTML LANG ").")
        (SPELL DONT CHECK, ::boost::program_options::bool_switch (), "Do not check spelling.")
        (SPELL DICT, ::boost::program_options::value < vstr_t > () -> composing (), "LANG,DICT: associate (hunspell) dictionary with language, e.g. 'en-US,en_US-large'; may be repeated (ignored in Windows).")
        (SPELL ICU, ::boost::program_options::bool_switch (), "Use the International Components for Unicode (ICU) text libraries (high quality but slow).")
        (SPELL DONT ICU, ::boost::program_options::bool_switch (), "Use standard text libraries (fast but inaccurate).")
        (SPELL LIST, ::boost::program_options::value < vstr_t > () -> composing (), "FILE,LANG: FILE contains additional valid spellings in LANG; may be repeated.")
        (SPELL PATH, ::boost::program_options::value < ::std::string > (), "Path to (hunspell) dictionaries (ignored in Windows).")
#endif // NOSPELL

        (SPELL DDICT, ::boost::program_options::value < vstr_t > () -> composing (), "hunspell dictionary; must have corresponding DLANG (ignored in Windows).")
        (SPELL DLANG, ::boost::program_options::value < vstr_t > () -> composing (), "language for corresponding DDICT dictionary (ignored in Windows).")

        // these are output by the config file writer. They're intended for debugging and maintenance. They're noted here to avoid unnecessary error messages.
        (SSC BUILD, ::boost::program_options::value < ::std::string > () -> default_value (BUILD_INFO), "SSC configuration used to write config file.")
        (SSC VERSION, ::boost::program_options::value < ::std::string > (), "config file written by this version of SSC.")
        (SSC OPTBOOST, ::boost::program_options::value < ::std::string > (), "boost version used by config file writer.")
        (SSC OPTCOMP, ::boost::program_options::value < ::std::string > (), "compiler used to build config file writer.")
        (SSC OPTDEBUG, ::boost::program_options::value < ::std::string > (), "if config file writer was a debug version.")
        (SSC OPTFUDDY, ::boost::program_options::value < ::std::string > (), "if config file writer was fuddy")
        (SSC OPTICU, ::boost::program_options::value < ::std::string > (), "if config file writer used ICU")
        (SSC OPTGUI, ::boost::program_options::value < ::std::string > (), "if config file writer used a gui (WX)")
        (SSC OPTJSON, ::boost::program_options::value < ::std::string > (), "if config file writer could use json")
        (SSC OPTNPS, ::boost::program_options::value < ::std::string > (), "if config file writer could use options streams")
        (SSC OPTPROC, ::boost::program_options::value < ::std::string > (), "config file writer's processor size")
        (SSC OPTOS, ::boost::program_options::value < ::std::string > (), "if config file writer's program options had streams")
        (SSC OPTSERVER, ::boost::program_options::value < ::std::string > (), "if config file writer was a server version")
        (SSC OPTSPELL, ::boost::program_options::value < ::std::string > (), "if config file writer could spell check")
    ;

    primary_.add_options ()
        (GENERAL ADS, ::boost::program_options::bool_switch (), "Verify .well-known/ads.txt.")
        (GENERAL DONT ADS, ::boost::program_options::bool_switch (), "Do not verify ads.txt.")
        (GENERAL CGI ARGSEP CGI_SW_, ::boost::program_options::bool_switch (), "Process HTML snippets (for OpenBSD's httpd <FORM METHOD=GET ...>; disables most features).")
        (GENERAL DONT CGI, ::boost::program_options::bool_switch (), "Process a local static website.")
        (GENERAL CLASS, ::boost::program_options::bool_switch (), "Report unrecognised classes (requires CSS).")
        (GENERAL DONT CLASS, ::boost::program_options::bool_switch (), "Do not report unrecognised classes.")
        (GENERAL CLASSIC, ::boost::program_options::bool_switch (), "Report all classes used, not just those in .CSS files (requires --" GENERAL CLASS ").")
        (GENERAL DONT CLASSIC, ::boost::program_options::bool_switch (), "Do not report all classes used.")
        (GENERAL COMMS, ::boost::program_options::bool_switch (), "Do not block network communications.")
        (GENERAL DONT COMMS, ::boost::program_options::bool_switch (), "Block network communications.")
        (GENERAL DATAPATH ARGSEP DTPTH_SW_, ::boost::program_options::value < ::std::string > () -> default_value (def_path), "Root directory for most " PROG " files.")
#ifndef NO_FRED
        (GENERAL DEFTHRD ARGSEP DFTHRD_SW_, ::boost::program_options::value < int > (), "If no setting specifies the thread count, set it to this.")
#endif // NO_FRED
        (GENERAL EDE, ::boost::program_options::bool_switch (), "Ignore certain platform specific files.")
        (GENERAL DONT EDE, ::boost::program_options::bool_switch (), "Do not ignore certain platform specific files.")
        (GENERAL EXCLUDE, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore files that end with this string; may be repeated.")
        (GENERAL FICHIER ARGSEP PERSIST_SW_, ::boost::program_options::value < ::std::string > () -> default_value (def_persisted), "File for persistent data (note --" GENERAL DATAPATH ").")
        (GENERAL INFO, ::boost::program_options::bool_switch (), "Report " PROG " launch context at startup.")
        (GENERAL LINE_LENGTH, ::boost::program_options::value < long > () -> default_value (DEFAULT_LINE_LENGTH), "Maximum line length for output (default 72).")
        (GENERAL MACROSTART, ::boost::program_options::value < ::std::string > () -> default_value (def_macrostart), "Start of template macro (by default, the '{{' in '{{macro}}').")
        (GENERAL MACROEND, ::boost::program_options::value < ::std::string > () -> default_value (def_macroend), "End of template macro (by default, the '}}' in '{{macro}}').")
        (GENERAL MAXFILESIZE, ::boost::program_options::value < int > (), "Maximum file size to read, in megabytes (zero for no limit).")
        (GENERAL OUTPUT_ ARGSEP OUTPUT_SW_, ::boost::program_options::value < ::std::string > (), "Output file (default to the console).")
        (GENERAL PROGRESS ARGSEP PRGRSS_SW_, ::boost::program_options::bool_switch (), "Report progress")
        (GENERAL DONT PROGRESS, ::boost::program_options::bool_switch (), "Don't be quite so noisy.")
        (GENERAL RDFA, ::boost::program_options::bool_switch (), "Check RDFa attributes.")
        (GENERAL DONT RDFA, ::boost::program_options::bool_switch (), "Do not check RDFa attributes.")
        (GENERAL ROBOTS, ::boost::program_options::bool_switch (), "Verify /robots.txt.")
        (GENERAL DONT ROBOTS, ::boost::program_options::bool_switch (), "Do not verify /robots.txt.")
        (GENERAL SECURITY, ::boost::program_options::bool_switch (), "Verify .well-known/security.txt.")
        (GENERAL DONT SECURITY, ::boost::program_options::bool_switch (), "Do not verify .well-known/security.txt.")
        (GENERAL SILENCE, ::boost::program_options::value < vstr_t > () -> composing (), "Process files and directories which match this name, but do not report their nits.")
        (GENERAL SPEC ARGSEP SPEC_SW_, ::boost::program_options::bool_switch (), "Reset default values of most switches to false.")
        (GENERAL TEST ARGSEP TEST_SW_, ::boost::program_options::bool_switch (), "Output in format useful for automated tests.")
        (GENERAL DONT TEST, ::boost::program_options::bool_switch (), "Output in format specified by other switches.")
#ifndef NO_FRED
        (GENERAL THREAD ARGSEP THREAD_SW_, ::boost::program_options::value < int > () -> default_value (def_fred), "Number of threads (default " MIN_FRED_S ", zero for hardware appropriate).")
#endif // NO_FRED
        (GENERAL UPDATE, ::boost::program_options::bool_switch (), "Check for updates to " PROG ".")
        (GENERAL DONT UPDATE, ::boost::program_options::bool_switch (), "Do not check for updates to " PROG ".")
        (GENERAL URL_VAR, ::boost::program_options::value < vstr_t > () -> composing (), "Set a URL template variable (see RFC 6570), format VAR=VAL; may be repeated.")
        (GENERAL VCS, ::boost::program_options::bool_switch (), "Exclude file and directory names associated with certain version control systems.")
        (GENERAL DONT VCS, ::boost::program_options::bool_switch (), "Do not exclude file and directory names associated with certain version control systems.")

        (ATOMIC EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "atom files have this extension (default atom); may be repeated.")
        (ATOMIC VERIFY, ::boost::program_options::bool_switch (), "verify atom files.")
        (ATOMIC DONT VERIFY, ::boost::program_options::bool_switch (), "verify atom files.")

        (CORPUS ARTICLE, ::boost::program_options::bool_switch (), "Prefer the content of <ARTICLE> when gather page corpus.")
        (CORPUS DONT ARTICLE, ::boost::program_options::bool_switch (), "Avoid the content of <ARTICLE> when gather page corpus.")
        (CORPUS BODY, ::boost::program_options::bool_switch (), "Prefer the content of <BODY> when gather page corpus.")
        (CORPUS DONT BODY, ::boost::program_options::bool_switch (), "Avoid the content of <BODY> when gather page corpus.")
        (CORPUS MAIN, ::boost::program_options::bool_switch (), "Prefer the content of <MAIN> when gather page corpus.")
        (CORPUS DONT MAIN, ::boost::program_options::bool_switch (), "Avoid the content of <MAIN> when gather page corpus.")
        (CORPUS OUTPUT_ ARGSEP DUMP_SW_, ::boost::program_options::value < ::std::string > (), "Dump corpus of site content to specified file.")

        (CSS ADJUST, ::boost::program_options::value < int > (), "CSS Colour Adjust level (0 or 3).")
        (CSS ADVLAY, ::boost::program_options::value < int > (), "CSS Advanced Layout level (0 or 3).")
        (CSS ANCHOR, ::boost::program_options::value < int > (), "CSS Scroll Anchoring level (0 or 3).")
        (CSS ANCHOR_POS, ::boost::program_options::value < int > (), "CSS Anchoring Positioning level (0 or 3).")
        (CSS ANIMATION, ::boost::program_options::value < int > (), "CSS Animation level (0 or 3).")
        (CSS BACKGROUND, ::boost::program_options::value < int > (), "CSS Background (and Borders) level (0, 3 or 4).")
        (CSS BORDER, ::boost::program_options::value < int > (), "CSS Borders and Boxes level (0 or 4).")
        (CSS BOX_ALIGN, ::boost::program_options::value < int > (), "CSS Box Alignment level (0 or 3).")
        (CSS BOX_MODEL, ::boost::program_options::value < int > (), "CSS Box Model level (0, 3 or 4).")
        (CSS BOX_SIZING, ::boost::program_options::value < int > (), "CSS Box Sizing level (0, 3 or 4).")
        (CSS CASCADE, ::boost::program_options::value < int > (), "CSS Cascade & Inheritance level (0, 3, 4, 5 or 6).")
        (CSS COLOUR, ::boost::program_options::value < int > (), "CSS Colour level (0, 3, 4, 5, or 6).")
        (CSS COMPOSITING, ::boost::program_options::value < int > (), "CSS Compositing and Blending level (0, 3 or 4).")
        (CSS COND_RULE, ::boost::program_options::value < int > (), "CSS Conditional Rule level (0, 3, 4, or 5).")
        (CSS CONTAIN, ::boost::program_options::value < int > (), "CSS Contain level (0, 3, 4, or 5).")
        (CSS CON_TENT, ::boost::program_options::value < int > (), "CSS Generated Content level (0 or 3).")
        (CSS CS, ::boost::program_options::value < int > (), "CSS Counter Style level (0 or 3).")
        (CSS CUSTOM, ::boost::program_options::value < int > (), "CSS Custom level (0 or 3).")
        (CSS DEVICE, ::boost::program_options::value < int > (), "CSS Device Adaption level (0 or 3).")
        (CSS DISPLAY, ::boost::program_options::value < int > (), "CSS Display level (0 or 3).")
        (CSS EASE, ::boost::program_options::value < int > (), "CSS Ease level (0, 3 or 4).")
        (CSS ENVIRONMENT, ::boost::program_options::value < int > (), "CSS Environment level (0 or 3).")
        (CSS EXCLUDE, ::boost::program_options::value < int > (), "CSS Exclusions level (0 or 3).")
        (CSS EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "CSS files have this extension (default css); may be repeated.")
        (CSS EXTERNAL, ::boost::program_options::bool_switch (), "Nitpick css files imported from external sites.")
        (CSS DONT EXTERNAL, ::boost::program_options::bool_switch (), "Do not nitpick imported CSS files.")
        (CSS FBL, ::boost::program_options::value < int > (), "CSS Flexible Box Layout level (0 or 3).")
        (CSS FILL, ::boost::program_options::value < int > (), "CSS Fill and Stroke level (0 or 3).")
        (CSS FILTER, ::boost::program_options::value < int > (), "CSS Filter Effects level (0 or 3).")
        (CSS FLOAT, ::boost::program_options::value < int > (), "CSS Page Floats level (0 or 3).")
        (CSS FONT, ::boost::program_options::value < int > (), "CSS Font level (0, 3, 4, or 5).")
        (CSS FRAG, ::boost::program_options::value < int > (), "CSS Fragmentation level (0, 3, or 4).")
        (CSS GRID, ::boost::program_options::value < int > (), "CSS Grid level (0, 3, or 4).")
        (CSS HDR, ::boost::program_options::value < int > (), "CSS HDR level (0 or 3).")
        (CSS HIGHLIGHT, ::boost::program_options::value < int > (), "CSS Custom Highlight level (0, 3, or 4).")
        (CSS HYPERLINK, ::boost::program_options::value < int > (), "CSS Hyperlink level (0 or 3).")
        (CSS IMAGE, ::boost::program_options::value < int > (), "CSS Images level (0, 3, or 4).")
        (CSS INLINE, ::boost::program_options::value < int > (), "CSS Inline Layout level (0 or 3).")
        (CSS LINE_GRID, ::boost::program_options::value < int > (), "CSS Line Grid level (0 or 3).")
        (CSS LIST, ::boost::program_options::value < int > (), "CSS Lists and Counters level (0 or 3).")
        (CSS LOGIC, ::boost::program_options::value < int > (), "CSS Logical Properties and Values level (0 or 3).")
        (CSS MARQUEE, ::boost::program_options::value < int > (), "CSS Marquee level (0 or 3).")
        (CSS MASKING, ::boost::program_options::value < int > (), "CSS Masking level (0 or 3).")
        (CSS MEDIA, ::boost::program_options::value < int > (), "CSS Media level (0, 3, 4, or 5).")
        (CSS MIXIN, ::boost::program_options::value < int > (), "CSS Functions and Mixin level (0 or 3).")
        (CSS MOBILE, ::boost::program_options::bool_switch (), "Notify if some CSS conflicts with the CSS Mobile Profile.")
        (CSS DONT MOBILE, ::boost::program_options::bool_switch (), "Do not notify CSS Mobile Profile matters.")
        (CSS MOTION, ::boost::program_options::value < int > (), "CSS Motion Path level (0 or 3).")
        (CSS MULTI_COLUMN, ::boost::program_options::value < int > (), "CSS Multi-Column level (0 or 3).")
        (CSS NAMESPACE, ::boost::program_options::value < int > (), "CSS Namespace level (0 or 3).")
        (CSS NES, ::boost::program_options::value < int > (), "CSS Non-Element Selectors level (0 or 3).")
        (CSS NESTING, ::boost::program_options::value < int > (), "CSS Nesting level (0 or 3).")
        (CSS OVERFLOH, ::boost::program_options::value < int > (), "CSS Overflow level (0, 3 or 4).")
        (CSS OVERSCROLL, ::boost::program_options::value < int > (), "CSS Overscroll Behaviour level (0 or 3).")
        (CSS PAGE, ::boost::program_options::value < int > (), "CSS Paged Media level (0 or 3).")
        (CSS POSITION, ::boost::program_options::value < int > (), "CSS Positions level (0 or 3).")
        (CSS PRESENT, ::boost::program_options::value < int > (), "CSS Presentation Levels level (0 or 3).")
        (CSS PRINT, ::boost::program_options::bool_switch (), "Notify if some CSS conflicts with the CSS Print Profile.")
        (CSS DONT PRINT, ::boost::program_options::bool_switch (), "No not notify CSS Print Profile matters.")
        (CSS PSEUDO, ::boost::program_options::value < int > (), "CSS Pseudo-Elements level (0, 3, or 4).")
        (CSS REGION, ::boost::program_options::value < int > (), "CSS Regions level (0 or 3).")
        (CSS RHYTHM, ::boost::program_options::value < int > (), "CSS Rhythmic Sizing level (0 or 3).")
        (CSS ROUND, ::boost::program_options::value < int > (), "CSS Round Display level (0 or 3).")
        (CSS RUBY, ::boost::program_options::value < int > (), "CSS Ruby Annotation Layout level (0 or 3).")
        (CSS SCOPE, ::boost::program_options::value < int > (), "CSS Scoping level (0 or 3).")
        (CSS SCROLLBAR, ::boost::program_options::value < int > (), "CSS Scrollbar Styling level (0 or 3).")
        (CSS SDA, ::boost::program_options::value < int > (), "CSS Scroll Driven Animations level (0 or 3).")
        (CSS SELECTOR, ::boost::program_options::value < int > (), "CSS Selector level (0, 3, 4, or 5).")
        (CSS SHAPE, ::boost::program_options::value < int > (), "CSS Shapes level (0, 3, or 4).")
        (CSS SNAP, ::boost::program_options::value < int > (), "CSS Scroll Snap level (0 or 3).")
        (CSS SNAP_POINTS, ::boost::program_options::value < int > (), "CSS Scroll Snap Points level (0 or 3).")
        (CSS SP, ::boost::program_options::value < int > (), "CSS Shadow Parts level (0, 3, or 4).")
        (CSS SPATIAL, ::boost::program_options::value < int > (), "CSS Spatial Navigation level (0 or 3).")
        (CSS SPEECH, ::boost::program_options::value < int > (), "CSS Speech level (0 or 3).")
        (CSS STYLE, ::boost::program_options::value < int > (), "CSS Style level (0 or 3).")
        (CSS SYNTAX, ::boost::program_options::value < int > (), "CSS Syntax level (0 or 3).")
        (CSS TABLE, ::boost::program_options::value < int > (), "CSS Table level (0 or 3).")
        (CSS TEXT_ARG, ::boost::program_options::value < int > (), "CSS Text level (0, 3, or 4).")
        (CSS TEXT_DEC, ::boost::program_options::value < int > (), "CSS Text Decoration level (0, 3, or 4).")
        (CSS TRANSFORM, ::boost::program_options::value < int > (), "CSS Transform level (0, 3 or 4).")
        (CSS TRANSITION, ::boost::program_options::value < int > (), "CSS Transitions level (0 or 3).")
        (CSS TV, ::boost::program_options::bool_switch (), "Notify if some CSS conflicts with the CSS TV Profile.")
        (CSS DONT TV, ::boost::program_options::bool_switch (), "No notify CSS TV Profile matters.")
        (CSS UI, ::boost::program_options::value < int > (), " CSS UI level (0, 3, or 4).")
        (CSS VAL, ::boost::program_options::value < int > (), "CSS Values and Units level (0, 3, or 4).")
        (CSS VERIFY, ::boost::program_options::bool_switch (), "Process .css files.")
        (CSS DONT VERIFY, ::boost::program_options::bool_switch (), "Do not process .css files.")
        (CSS VERSION, ::boost::program_options::value < ::std::string > (),
            "Select no CSS (0); "
            "a specific version (1, 2.0, 2.1, 2.2); "
            "all modules of a given level (3 to 6); "
            "solid snapshot modules by year (07, 10, 15, 17, 18, 20 to 26); "
            "solid and + snapshot modules by year (15+, 17+, 18+, 20+ to 26+); "
            "all snapshot modules by year (15++, 17++, 18++, 20++ to 26++,); "
            "hairy snapshot modules by year (24+++ to 26+++); "
            "HTML5 Living Standard requirements (HTML5): "
            "default appropriate for HTML version.")
        (CSS VIEW, ::boost::program_options::value < int > (), "CSS View Transitions level (0 or 3).")
        (CSS VIEWPORT, ::boost::program_options::value < int > (), "CSS Viewport level (0 or 3).")
        (CSS WC, ::boost::program_options::value < int > (), "CSS Will Change level (0 or 3).")
        (CSS WRITING, ::boost::program_options::value < int > (), "CSS Writing Mode level (0, 3 or 4).")

        (HTML ARIA, ::boost::program_options::bool_switch (), "Report ARIA issues.")
        (HTML DONT ARIA, ::boost::program_options::bool_switch (), "Ignore ARIA issues.")
        (HTML CHROME, ::boost::program_options::bool_switch (), "Ignore certain naughtitudes accepted by versions of Chrome.")
        (HTML DONT CHROME, ::boost::program_options::bool_switch (), "Mention certain naughtitudes accepted by versions of Chrome.")
        (HTML CUSTOM, ::boost::program_options::value < vstr_t > () -> composing (), "Define a custom element for checking the 'is' attribute; may be repeated.")
        (HTML EFFICIENT, ::boost::program_options::bool_switch (), "Warn about valid but inefficient HTML.")
        (HTML DONT EFFICIENT, ::boost::program_options::bool_switch (), "Do not warn about inefficient HTML")
        (HTML FORCE, ::boost::program_options::bool_switch (), "When <!DOCTYPE...> is missing, forcibly presume HTML version as per --html.version.")
        (HTML DONT FORCE, ::boost::program_options::bool_switch (), "When <!DOCTYPE...> is missing, correctly presume HTML 1 or HTML tags, as per --html.tags.")
        (HTML IE, ::boost::program_options::bool_switch (), "Ignore certain naughtitudes accepted by versions of Internet Explorer.")
        (HTML DONT IE, ::boost::program_options::bool_switch (), "Mention certain naughtitudes accepted by versions of Internet Explorer.")
        (HTML IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore attributes and content of specified element; may be repeated.")
        (HTML LANG, ::boost::program_options::value < ::std::string > () -> composing (), "Default language (such as 'en_GB', 'lb_LU', etc.).")
        (HTML MOZILLA, ::boost::program_options::bool_switch (), "Ignore certain naughtitudes accepted by versions of Firefox.")
        (HTML DONT MOZILLA, ::boost::program_options::bool_switch (), "Mention certain naughtitudes accepted by versions of Firefox.")
        (HTML NETSCAPE, ::boost::program_options::bool_switch (), "Ignore certain naughtitudes accepted by versions of Netscape.")
        (HTML DONT NETSCAPE, ::boost::program_options::bool_switch (), "Mention certain naughtitudes accepted by versions of Netscape.")
        (HTML OPERA, ::boost::program_options::bool_switch (), "Ignore certain naughtitudes accepted by versions of Opera.")
        (HTML DONT OPERA, ::boost::program_options::bool_switch (), "Mention certain naughtitudes accepted by versions of Opera.")
        (HTML REL, ::boost::program_options::bool_switch (), "Ignore recognised but non-standard <LINK> REL values.")
        (HTML DONT REL, ::boost::program_options::bool_switch (), "Nitpick recognised but non-standard <LINK> REL values.")
        (HTML RFC1867, ::boost::program_options::bool_switch (), "Consider RFC 1867 (INPUT=FILE) when processing HTML 2.0.")
        (HTML DONT RFC1867, ::boost::program_options::bool_switch (), "Ignore RFC 1867 (INPUT=FILE) when processing HTML 2.0.")
        (HTML RFC1942, ::boost::program_options::bool_switch (), "Consider RFC 1867 RFC 1942 (tables) when processing HTML 2.0.")
        (HTML DONT RFC1942, ::boost::program_options::bool_switch (), "Ignore RFC 1867 RFC 1942 (tables) when processing HTML 2.0.")
        (HTML RFC1980, ::boost::program_options::bool_switch (), "Consider RFC 1867 RFC 1980 (client side image maps) when processing HTML 2.0.")
        (HTML DONT RFC1980, ::boost::program_options::bool_switch (), "Ignore RFC 1867 RFC 1980 (client side image maps) when processing HTML 2.0.")
        (HTML RFC2070, ::boost::program_options::bool_switch (), "Consider RFC 1867 RFC 2070 (internationalisation) when processing HTML 2.0.")
        (HTML DONT RFC2070, ::boost::program_options::bool_switch (), "Ignore RFC 1867 RFC 2070 (internationalisation) when processing HTML 2.0.")
        (HTML RUBY, ::boost::program_options::bool_switch (), "Accept Ruby Markup extensions (from May 2024).")
        (HTML DONT RUBY, ::boost::program_options::bool_switch (), "Do not accept Ruby Markup extensions.")
        (HTML SAFARI, ::boost::program_options::bool_switch (), "Ignore certain naughtitudes accepted by versions of Safari.")
        (HTML DONT SAFARI, ::boost::program_options::bool_switch (), "Mention certain naughtitudes accepted by versions of Safari.")
        (HTML TAGS, ::boost::program_options::bool_switch (), "Presume HTML with no DOCTYPE is HTML Tags (CERN version).")
        (HTML DONT TAGS, ::boost::program_options::bool_switch (), "Presume HTML with no DOCTYPE is HTML 1.0.")
        (HTML TITLE ARGSEP TITLE_SW_, ::boost::program_options::value < int > () -> default_value (def_htmltitle), "Maximum advisable length of <TITLE> text.")
        (HTML VERSION ARGSEP HTMLVER_SW_, ::boost::program_options::value < ::std::string > (),
            "Set the specific version of HTML with DOCTYPE (default '2022/7/1'). "
            "For a W3 standard, give its version (e.g. '5.2'). "
            "For a WhatWG living standard, give its date (e.g. '2015/7/1'). "
            "For XHTML, use XHTML plus version, e.g. 'XHTML 1.0'. "
            "For HTML+, use '+'. For HTML tags, use 'tags'.")
        (HTML WXARG, ::boost::program_options::bool_switch (), "Warn about HTML tags and attributes unsupported by wxWidgets' HTML engine.")
        (HTML DONT WXARG, ::boost::program_options::bool_switch (), "Do not warn about HTML tags and attributes unsupported by wxWidgets' HTML engine.")

        (JSONLD EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "Extension for JSON-LD files (default jld); may be repeated.")
        (JSONLD ONTOLOGY_, ::boost::program_options::value < vstr_t > () -> composing (), "Predefine JSON-LD ontology context, format \"shortname:URL\": may be repeated")
        (JSONLD PRETTY, ::boost::program_options::bool_switch (), "Output pretty JSON.")
        (JSONLD DONT PRETTY, ::boost::program_options::bool_switch (), "Output ugly JSON.")
        (JSONLD VERIFY, ::boost::program_options::bool_switch (), "Experimental: Verify JSON-LD (incomplete).")
        (JSONLD DONT VERIFY, ::boost::program_options::bool_switch (), "Do not verify JSON-LD.")
        (JSONLD VERSION, ::boost::program_options::value < ::std::string > (), "Presume this version of JSON-LD (1.0 or 1.1, default 1.0).")

        (LINKS CHECK ARGSEP CHECK_SW_, ::boost::program_options::bool_switch (), "Check internal links.")
        (LINKS DONT CHECK, ::boost::program_options::bool_switch (), "Ignore internal links.")
        (LINKS EXAMPLE, ::boost::program_options::bool_switch (), "Issue warning if link to faux domain, such as example.com, found.")
        (LINKS DONT EXAMPLE, ::boost::program_options::bool_switch (), "Say nothing if link to faux domain, such as example.com, found.")
        (LINKS EXTERNAL ARGSEP EXTERN_SW_, ::boost::program_options::bool_switch (), "Check external links (sets --" LINKS CHECK ").")
        (LINKS DONT EXTERNAL, ::boost::program_options::bool_switch (), "Ignore external links.")
        (LINKS FORWARD ARGSEP FORWARD_SW_, ::boost::program_options::bool_switch (), "Report http forwarding errors, e.g. 301 and 308 (sets --" LINKS EXTERNAL ").")
        (LINKS DONT FORWARD, ::boost::program_options::bool_switch (), "Ignore http forwarding errors, e.g. 301 and 308.")
        (LINKS IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "When checking external links, ignore this domain; may be repeated.")
        (LINKS LOCAL, ::boost::program_options::bool_switch (), "Issue warning if link to local domain, such as ???.internal or ???.lan, found.")
        (LINKS DONT LOCAL, ::boost::program_options::bool_switch (), "Don't mention links to local domains.")
        (LINKS PRETEND, ::boost::program_options::value < vstr_t > () -> composing (), "Pretend files that end with this string exist; may be repeated.")
        (LINKS ONCE ARGSEP ONCE_SW_, ::boost::program_options::bool_switch (), "Report each broken external link once (sets --" LINKS EXTERNAL ").")
        (LINKS DONT ONCE, ::boost::program_options::bool_switch (), "Report broken links whenever they are found.")
        (LINKS REPORT, ::boost::program_options::value < vstr_t > () -> composing (), "Report links to this domain and its descendants; may be repeated.")
        (LINKS REQUIRED, ::boost::program_options::value < vstr_t > () -> composing (), "Set required link to URL,lang,page-type,element,from,to,desc (see docs for details). May be repeated.")
        (LINKS REVOKE ARGSEP REVOKE_SW_, ::boost::program_options::bool_switch (), "Do not check whether https certificates have been revoked (sets --" LINKS EXTERNAL ").")
        (LINKS DONT REVOKE, ::boost::program_options::bool_switch (), "Check whether https certificates have been revoked (sets --" LINKS EXTERNAL ").")
        (LINKS SPECIAL, ::boost::program_options::bool_switch (), "Issue warning if link to a special domain, such as ???.onion, found.")
        (LINKS DONT SPECIAL, ::boost::program_options::bool_switch (), "Don't mention links to special domains.")
        (LINKS XLINK ARGSEP XLINK_SW_, ::boost::program_options::bool_switch (), "Check cross-link IDs.")
        (LINKS DONT XLINK, ::boost::program_options::bool_switch (), "Do not check cross-link IDs.")

        (MATH VERSION, ::boost::program_options::value < ::std::string > (), "preferred version of MathML; one of 0/1/2/3/4.20/4/core (default: determined by HTML version).")

        (MF EXPORT, ::boost::program_options::bool_switch (), "Export microformat data (requires --" MF VERIFY ") in JSON format.")
        (MF DONT EXPORT, ::boost::program_options::bool_switch (), "Do not export microformat data.")
        (MF PRETTY, ::boost::program_options::bool_switch (), "Output pretty JSON.")
        (MF DONT PRETTY, ::boost::program_options::bool_switch (), "Output ugly JSON.")
        (MF VERIFY ARGSEP MFVER_SW_, ::boost::program_options::bool_switch (), "Check microformats in class and rel attributes (see https://" MICROFORMATS_ORG "/).")
        (MF DONT VERIFY, ::boost::program_options::bool_switch (), "Do not check microformats in class and rel attributes.")
        (MF VERSION, ::boost::program_options::value < int > (), "Check this version of microformats (1, 2, or 3 for both).")

        (NITS ABHORRENT, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as an abhorrence; may be repeated.")
        (NITS CATASTROPHE, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a catastrophe; may be repeated.")
        (NITS COMMENT, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a comment; may be repeated.")
        (NITS DBG, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a debug message; may be repeated.")
        (NITS WHOOPS, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as an error; may be repeated.")
        (NITS ERROREXIT ARGSEP ERREXT_SW_, ::boost::program_options::value < ::std::string > () -> composing (), "Exit with an error if nits of this severity or worse are generated. Values: '"
            CATASTROPHE "', '" WHOOPS "' (default), '" WARNING "', '" INFO  "', or '" COMMENT  "'.")
        (NITS EXPAND, ::boost::program_options::bool_switch (), "Expand content of some nits.")
        (NITS DONT EXPAND, ::boost::program_options::bool_switch (), "Keep nit text curt.")
        (NITS EXTRA, ::boost::program_options::bool_switch (), "Report additional nits.")
        (NITS DONT EXTRA, ::boost::program_options::bool_switch (), "Do not report additional nits.")
        (NITS INFO, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as info; may be repeated.")
        (NITS NIDS, ::boost::program_options::bool_switch (), "Output nit identifiers (used to recategorise nits).")
        (NITS DONT NIDS, ::boost::program_options::bool_switch (), "Do not output nit identifiers.")
        (NITS QUOTE, ::boost::program_options::value < ::std::string > (), "Quote nits in this format: \"c\", \"csv\", \"double\", \"html\", \"none\" (default), or \"single\".")
        (NITS ROOT, ::boost::program_options::bool_switch (), "By default, seek nit output template files in --" WEBSITE ROOT ".")
        (NITS DONT ROOT, ::boost::program_options::bool_switch (), "Do not seek nit output template files in --" WEBSITE ROOT ", unless explicitly specified.")
        (NITS SILENCE, ::boost::program_options::value < vstr_t > () -> composing (), "Silence nit; may be repeated.")
        (NITS UNIQUE ARGSEP UNIQUE_SW_, ::boost::program_options::bool_switch (), "Do not report repeated nits, even if they give more information.")
        (NITS DONT UNIQUE, ::boost::program_options::bool_switch (), "Report repeated nits.")
        (NITS VERBOSE ARGSEP VERBOSE_SW_, ::boost::program_options::value < ::std::string > (), "Output these nits and worse. Values: '"
            CATASTROPHE "', '" WHOOPS "', '" WARNING "' (default), '" INFO  "', '" COMMENT  "', or 0 for silence.")
        (NITS WARNING, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine specified nit as a warning; may be repeated.")
        (NITS WATCH, ::boost::program_options::bool_switch (), "Output debug nits (for automation).")
        (NITS DONT WATCH, ::boost::program_options::bool_switch (), "Do not output debug nits.")

        (ONTOLOGY EXPORT, ::boost::program_options::bool_switch (), "Export ontology data (only verified data if --" ONTOLOGY VERIFY " is set) in JSON format.")
        (ONTOLOGY DONT EXPORT, ::boost::program_options::bool_switch (), "Do not export ontology data.")
        (ONTOLOGY PRETTY, ::boost::program_options::bool_switch (), "Output pretty JSON.")
        (ONTOLOGY DONT PRETTY, ::boost::program_options::bool_switch (), "Output ugly JSON.")
        (ONTOLOGY ROOT, ::boost::program_options::value < ::std::string > (), "Ontology export root directory (requires --" ONTOLOGY EXPORT ").")
        (ONTOLOGY VERIFY ARGSEP MDATA_SW_, ::boost::program_options::bool_switch (), "Check ontology (" PROG " only understands certain ontologies).")
        (ONTOLOGY DONT VERIFY, ::boost::program_options::bool_switch (), "Do not check ontology data.")
        (ONTOLOGY VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "Export virtual directory content, syntax virtual=directory. Must correspond to --" WEBSITE VIRTUAL ".")

        (OUTPUT APATH, ::boost::program_options::bool_switch (), "Output local filesystem path of files scanned.")
        (OUTPUT ACCOUNT, ::boost::program_options::value < ::std::string > (), "the account name using " PROG " (by default, obtained from the OS)")
        (OUTPUT BACK, ::boost::program_options::value < ::std::string > (), "Add this link as back when reporting on snippet result.")
        (OUTPUT DESCRIPTION, ::boost::program_options::value < vstr_t > () -> composing (), "Output this contextual description (may be repeated)")
        (OUTPUT FORMAT, ::boost::program_options::value < ::std::string > (), "Produce output in this format: \"html\", \"stylesheet\", \"text\" (default), \"xhtml\", or a filename (see docs for layout).")
        (OUTPUT HOME, ::boost::program_options::value < ::std::string > (), "Add this link as home when reporting on snippet result.")
        (OUTPUT OVERRIDE ARGSEP OVRRD_SW_, ::boost::program_options::value < ::std::string > (), "Output nits in this format (overrides --" OUTPUT FORMAT "; for automation).")
#ifdef SIGNING
        (OUTPUT PASSWORD, ::boost::program_options::value < ::std::string > (), "the file containing the password for the private key, if any")
        (OUTPUT PRIVATE, ::boost::program_options::value < ::std::string > (), "the file containing the private key used for the signature")
        (OUTPUT PUBLIC, ::boost::program_options::value < ::std::string > (), "the file containing the public key used to verify the signature")
#endif // SIGNING
        (OUTPUT RPATH, ::boost::program_options::bool_switch (), "Output web address relative path of files scanned.")
#ifdef SIGNING
        (OUTPUT SIGN, ::boost::program_options::bool_switch (), "Sign the output (requires --" OUTPUT SIGNATURE ", --" OUTPUT PRIVATE ", and --" OUTPUT PUBLIC ")")
        (OUTPUT DONT SIGN, ::boost::program_options::bool_switch (), "Do not sign the output")
        (OUTPUT SIGNATURE, ::boost::program_options::value < ::std::string > (), "output the signature to this file (requires --" OUTPUT PRIVATE ")")
#endif // SIGNING
        (OUTPUT STYLESHEET, ::boost::program_options::value < ::std::string > (), "when reporting snippets using stylesheet format, use this stylesheet")
        (OUTPUT USERNAME, ::boost::program_options::value < ::std::string > (), "the operator of " PROG " (by default, obtained from the OS)")
        (OUTPUT VERIFY, ::boost::program_options::bool_switch (), "Verify signed output (requires --" OUTPUT PUBLIC " and --" OUTPUT SIGNATURE ")")
        (OUTPUT DONT VERIFY, ::boost::program_options::bool_switch (), "Do not verify signed output (verification cannot be blocked when signing)")

        (RSL EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "Extension for RSL files (default rsl); may be repeated.")
        (RSL VERIFY, ::boost::program_options::bool_switch (), "Verify signed output (requires --" OUTPUT PUBLIC " and --" OUTPUT SIGNATURE ")")
        (RSL DONT VERIFY, ::boost::program_options::bool_switch (), "Do not verify signed output (verification cannot be blocked when signing)")

        (RSS EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "Extension for RSS files (default rss); may be repeated.")
        (RSS VERIFY, ::boost::program_options::bool_switch (), "Verify signed output (requires --" OUTPUT PUBLIC " and --" OUTPUT SIGNATURE ")")
        (RSS DONT VERIFY, ::boost::program_options::bool_switch (), "Do not verify signed output (verification cannot be blocked when signing)")
        (RSS VERSION, ::boost::program_options::value < ::std::string > (), "Presume this version of RSS (default 2.0).")

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
        (SHADOW ENABLE, ::boost::program_options::bool_switch (), "Enable shadowing (set by all other SHADOW options).")
        (SHADOW DONT ENABLE, ::boost::program_options::bool_switch (), "Disable shadowing.")
        (SHADOW FICHIER, ::boost::program_options::value < ::std::string > (), "File for persisting deduplication and update data.")
        (SHADOW IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore files with this extension; may be repeated.")
        (SHADOW INFO, ::boost::program_options::bool_switch (), "Insert the generation time in a comment at the top of shadowed pages (after --" SHADOW MSG ").")
        (SHADOW DONT INFO, ::boost::program_options::bool_switch (), "Do not insert the generation time in a comment at the top of shadowed pages.")
        (SHADOW MSG, ::boost::program_options::value < ::std::string > (), "Insert this text in a comment at the top of shadowed pages.")
        (SHADOW NAUGHTY, ::boost::program_options::value < vstr_t > () -> composing (), "add to naughty list; may be repeated. See docs for details.")
        (SHADOW NICE, ::boost::program_options::value < vstr_t > () -> composing (), "add to nice list; may be repeated. See docs for details.")
        (SHADOW NOTE, ::boost::program_options::value < vstr_t > () -> composing (), "when something is naughty or not nice, use this instead; may be repeated. See docs for details.")
        (SHADOW REPLACE, ::boost::program_options::value < vstr_t > () -> composing (), "when a specific value is encountered, replace it with another. See docs for details.")
        (SHADOW ROOT, ::boost::program_options::value < ::std::string > (), "Shadow output root directory.")
        (SHADOW SPACING, ::boost::program_options::bool_switch (), "Merge whitespace on shadow pages. Without this option, nit line-numbers may not match shadow pages.")
        (SHADOW DONT SPACING, ::boost::program_options::bool_switch (), "Do not merge whitespace on shadow pages.")
        (SHADOW SSI_, ::boost::program_options::bool_switch (), "Resolve SSIs on shadow pages. Requires --" SSI VERIFY ".")
        (SHADOW DONT SSI_, ::boost::program_options::bool_switch (), "Do not resolve SSIs on shadow pages.")
        (SHADOW UPDATE, ::boost::program_options::bool_switch (), "Only examine changed pages, or pages with changed dependencies (requires --" SHADOW FICHIER ")")
        (SHADOW DONT UPDATE, ::boost::program_options::bool_switch (), "Examine all pages.")
        (SHADOW VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "Shadow virtual directory, syntax virtual=shadow; must correspond to --" WEBSITE VIRTUAL "; may be repeated.")

        (WEBSITE EXTENSION ARGSEP EXT_SW_, ::boost::program_options::value < vstr_t > () -> composing (), "Check files with this extension (default html); may be repeated.")
        (WEBSITE INDEX ARGSEP INDEX_SW_, ::boost::program_options::value < ::std::string > (), "Index file in directories (default: none).")
        (WEBSITE ROOT ARGSEP ROOT_SW_, ::boost::program_options::value < ::std::string > (), "Website root directory (default: current directory).")
        (WEBSITE SITE ARGSEP SITE_SW_, ::boost::program_options::value < vstr_t > () -> composing (), "Domain name(s) for local site (default none); may be repeated.")
        (WEBSITE VIRTUAL ARGSEP VIRTUAL_SW_, ::boost::program_options::value < vstr_t > () -> composing (), "Define virtual directory, arg syntax virtual=physical; may be repeated.")

#ifndef NOSPELL
        (SPELL ACCEPT, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore this word in spell checks; may be repeated.")
        (SPELL CASED, ::boost::program_options::bool_switch (), "Nitpick wrongly cased but correctly spelt words.")
        (SPELL DONT CASED, ::boost::program_options::bool_switch (), "Ignore case when checking spelling.")
        (SPELL CHECK ARGSEP SPELL_SW_, ::boost::program_options::bool_switch (), "Check spelling (see also --" HTML LANG ").")
        (SPELL DONT CHECK, ::boost::program_options::bool_switch (), "Do not check spelling.")
        (SPELL DICT, ::boost::program_options::value < vstr_t > () -> composing (), "LANG,DICT: associate (hunspell) dictionary with language, e.g. 'en-US,en_US-large'; may be repeated (ignored in Windows).")
        (SPELL ICU, ::boost::program_options::bool_switch (), "Use the International Components for Unicode (ICU) text libraries (high quality but slow).")
        (SPELL DONT ICU, ::boost::program_options::bool_switch (), "Use standard text libraries (fast but inaccurate).")
        (SPELL LIST, ::boost::program_options::value < vstr_t > () -> composing (), "FILE,LANG: FILE contains additional valid spellings in LANG; may be repeated.")
        (SPELL PATH, ::boost::program_options::value < ::std::string > (), "Path to (hunspell) dictionaries (ignored in Windows).")
#endif // NOSPELL

        (SSI DATETIME, ::boost::program_options::value < ::std::string > () -> composing (), "The SSI date environment variables should return this value.")
        (SSI DOCARGS, ::boost::program_options::value < ::std::string > () -> composing (), "Set the SSI DOCUMENT_ARGS variable to this value.")
        (SSI ECHOMSG, ::boost::program_options::value < ::std::string > () -> composing (), "Set the initial SSI default echo message (by default, " DEFAULT_ECHOMSG ").")
        (SSI ERRMSG, ::boost::program_options::value < ::std::string > () -> composing (), "Set the initial SSI default error message (by default, " DEFAULT_ERRMSG ").")
        (SSI EXECRUN, ::boost::program_options::bool_switch (), "Obey SSI <!--#exec ..> elements. Warning: this is dangerous when processing untrusted sources.")
        (SSI DONT EXECRUN, ::boost::program_options::bool_switch (), "Ignore SSI <!--#exec ..> elements. This is the default behaviour.")
        (SSI EXECTEXT, ::boost::program_options::value < ::std::string > () -> composing (), "When SSI <!--#exec ..> elements are being ignored, and one is found, return this string.")
        (SSI LASTMOD, ::boost::program_options::value < ::std::string > () -> composing (), "The SSI last modification time environment variable should return this value.")
        (SSI QUERYSTRING, ::boost::program_options::value < ::std::string > () -> composing (), "Set the SSI QUERY_STRING_UNESCAPED variable to this value.")
        (SSI TIMEFMT, ::boost::program_options::value < ::std::string > () -> composing (), "Set the SSI TIMEFMT variable to this value.")
        (SSI USERNAME, ::boost::program_options::value < ::std::string > () -> composing (), "Set the SSI USER_NAME variable to this value.")
        (SSI VERIFY ARGSEP SSI_SW_, ::boost::program_options::bool_switch (), "Verify (simple) Server Side Includes. See also --" SHADOW SSI_ ".")
        (SSI DONT VERIFY, ::boost::program_options::bool_switch (), "Do not verify Server Side Includes.")

        (STATS ABBR, ::boost::program_options::bool_switch (), "Output abbr report.")
        (STATS DONT ABBR, ::boost::program_options::bool_switch (), "Do not output abbr report.")
        (STATS ALL, ::boost::program_options::bool_switch (), "Output all stats reports.")
        (STATS DONT ALL, ::boost::program_options::bool_switch (), "Output no stats reports.")
        (STATS ANNOTATION, ::boost::program_options::bool_switch (), "Output annotation report.")
        (STATS DONT ANNOTATION, ::boost::program_options::bool_switch (), "Do not output annotation report.")
        (STATS ATTRIB, ::boost::program_options::bool_switch (), "Output element attribute report.")
        (STATS DONT ATTRIB, ::boost::program_options::bool_switch (), "Do not output element attribute report.")
        (STATS CAT, ::boost::program_options::bool_switch (), "Output category report.")
        (STATS DONT CAT, ::boost::program_options::bool_switch (), "Do not output category report.")
        (STATS CHARVAR, ::boost::program_options::bool_switch (), "Output character_variant report.")
        (STATS DONT CHARVAR, ::boost::program_options::bool_switch (), "Do not output character_variant report.")
        (STATS CLASS, ::boost::program_options::bool_switch (), "Output class report.")
        (STATS DONT CLASS, ::boost::program_options::bool_switch (), "Do not output class report.")
        (STATS CONNAME, ::boost::program_options::bool_switch (), "Output content_name report.")
        (STATS DONT CONNAME, ::boost::program_options::bool_switch (), "Do not output content_name report.")
        (STATS COUSTYLE, ::boost::program_options::bool_switch (), "Output counter_style report.")
        (STATS DONT COUSTYLE, ::boost::program_options::bool_switch (), "Do not output counter_style report.")
        (STATS CSSPROP, ::boost::program_options::bool_switch (), "Output css_property report.")
        (STATS DONT CSSPROP, ::boost::program_options::bool_switch (), "Do not output css_property report.")
        (STATS CUSTMED, ::boost::program_options::bool_switch (), "Output custom_media report.")
        (STATS DONT CUSTMED, ::boost::program_options::bool_switch (), "Do not output custom_media report.")
        (STATS CUSTPROP, ::boost::program_options::bool_switch (), "Output custom_property report.")
        (STATS DONT CUSTPROP, ::boost::program_options::bool_switch (), "Do not output custom_property report.")
        (STATS DFN, ::boost::program_options::bool_switch (), "Output dfn report.")
        (STATS DONT DFN, ::boost::program_options::bool_switch (), "Do not output dfn report.")
        (STATS DTDD, ::boost::program_options::bool_switch (), "Output dtdd report.")
        (STATS DONT DTDD, ::boost::program_options::bool_switch (), "Do not output dtdd report.")
        (STATS ELEMENT, ::boost::program_options::bool_switch (), "Output element report.")
        (STATS DONT ELEMENT, ::boost::program_options::bool_switch (), "Do not output element report.")
        (STATS WHOOPS, ::boost::program_options::bool_switch (), "Output counts of errors, warnings, etc..")
        (STATS DONT WHOOPS, ::boost::program_options::bool_switch (), "Do not output counts of errors, warnings, etc..")
        (STATS EXPORT, ::boost::program_options::value < ::std::string > (), "Export collected statistical data here.")
        (STATS FICHIER, ::boost::program_options::bool_switch (), "Output file report.")
        (STATS DONT FICHIER, ::boost::program_options::bool_switch (), "Do not output file report.")
        (STATS FONT, ::boost::program_options::bool_switch (), "Output font report.")
        (STATS DONT FONT, ::boost::program_options::bool_switch (), "Do not output font report.")
        (STATS FONT_FAMILY, ::boost::program_options::bool_switch (), "Output font_family report.")
        (STATS DONT FONT_FAMILY, ::boost::program_options::bool_switch (), "Do not output font_family report.")
        (STATS HIGHLIGHT, ::boost::program_options::bool_switch (), "Output highlight report.")
        (STATS DONT HIGHLIGHT, ::boost::program_options::bool_switch (), "Do not output highlight report.")
        (STATS HISTFORM, ::boost::program_options::bool_switch (), "Output historical_form report.")
        (STATS DONT HISTFORM, ::boost::program_options::bool_switch (), "Do not output historical_form report.")
        (STATS ID, ::boost::program_options::bool_switch (), "Output ID report.")
        (STATS DONT ID, ::boost::program_options::bool_switch (), "Do not output ID report.")
        (STATS ITEMID, ::boost::program_options::bool_switch (), "Output itemid report.")
        (STATS DONT ITEMID, ::boost::program_options::bool_switch (), "Do not output itemid report.")
        (STATS KEYFRAME, ::boost::program_options::bool_switch (), "Output keyframe report.")
        (STATS DONT KEYFRAME, ::boost::program_options::bool_switch (), "Do not output keyframe report.")
        (STATS LAYER, ::boost::program_options::bool_switch (), "Output layer report.")
        (STATS DONT LAYER, ::boost::program_options::bool_switch (), "Do not output layer report.")
        (STATS META, ::boost::program_options::bool_switch (), "Output meta report.")
        (STATS DONT META, ::boost::program_options::bool_switch (), "Do not output meta report.")
        (STATS ONT, ::boost::program_options::bool_switch (), "Output ontology report.")
        (STATS DONT ONT, ::boost::program_options::bool_switch (), "Do not output ontology report.")
        (STATS ORNAMENT, ::boost::program_options::bool_switch (), "Output ornament report.")
        (STATS DONT ORNAMENT, ::boost::program_options::bool_switch (), "Do not output ornament report.")
        (STATS PAGE, ::boost::program_options::bool_switch (), "Report individual page statistics.")
        (STATS DONT PAGE, ::boost::program_options::bool_switch (), "Do not report individual page statistics.")
        (STATS PAGE_NAME, ::boost::program_options::bool_switch (), "Output page_name report.")
        (STATS DONT PAGE_NAME, ::boost::program_options::bool_switch (), "Do not output page_name report.")
        (STATS PALETTE, ::boost::program_options::bool_switch (), "Output palette report.")
        (STATS DONT PALETTE, ::boost::program_options::bool_switch (), "Do not output palette report.")
        (STATS PROPER, ::boost::program_options::bool_switch (), "Output ontology property count report.")
        (STATS DONT PROPER, ::boost::program_options::bool_switch (), "Do not output ontology property count report.")
        (STATS REFERENCE, ::boost::program_options::bool_switch (), "Output reference report.")
        (STATS DONT REFERENCE, ::boost::program_options::bool_switch (), "Do not output reference report.")
        (STATS REGION, ::boost::program_options::bool_switch (), "Output region report.")
        (STATS DONT REGION, ::boost::program_options::bool_switch (), "Do not output region report.")
        (STATS SCROLL_ANIM, ::boost::program_options::bool_switch (), "Output scroll_anim report.")
        (STATS DONT SCROLL_ANIM, ::boost::program_options::bool_switch (), "Do not output scroll_anim report.")
        (STATS SELECTED, ::boost::program_options::bool_switch (), "Output a selected set of reports.")
        (STATS STATEMENT, ::boost::program_options::bool_switch (), "Output css statement report.")
        (STATS DONT STATEMENT, ::boost::program_options::bool_switch (), "Do not output css statement report.")
        (STATS STYLESET, ::boost::program_options::bool_switch (), "Output styleset report.")
        (STATS DONT STYLESET, ::boost::program_options::bool_switch (), "Do not output styleset report.")
        (STATS STYLISTIC, ::boost::program_options::bool_switch (), "Output stylistic report.")
        (STATS DONT STYLISTIC, ::boost::program_options::bool_switch (), "Do not output stylistic report.")
        (STATS SUMMARY ARGSEP SUMMARY_SW_, ::boost::program_options::bool_switch (), "Report overall statistics.")
        (STATS DONT SUMMARY, ::boost::program_options::bool_switch (), "Do not report overall statistics.")
        (STATS SWASH, ::boost::program_options::bool_switch (), "Output swash report.")
        (STATS DONT SWASH, ::boost::program_options::bool_switch (), "Do not output swash report.")
        (STATS VERSION, ::boost::program_options::bool_switch (), "Output version report.")
        (STATS DONT VERSION, ::boost::program_options::bool_switch (), "Do not output version report.")
        (STATS VIEW, ::boost::program_options::bool_switch (), "Output view report.")
        (STATS DONT VIEW, ::boost::program_options::bool_switch (), "Do not output view report.")

        (SVG VERSION, ::boost::program_options::value < ::std::string > (), "Presumed this version of SVG if version attribute missing (requires HTML 4 or greater).")

        (VALIDATION MINOR ARGSEP MINOR_SW_, ::boost::program_options::value < int > (), "Validate HTML 5 with this w3 minor version (e.g. 2 for HTML 5.2).")
        (VALIDATION MICRODATAARG, ::boost::program_options::bool_switch (), "Validate HTML5 microdata.")
        (VALIDATION DONT MICRODATAARG, ::boost::program_options::bool_switch (), "Do not validate HTML5 microdata.")

        (VTT EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "Extension for WebVTT files (default vtt); may be repeated.")
        (VTT VERIFY, ::boost::program_options::bool_switch (), "Verify WebVTT files.")
        (VTT DONT VERIFY, ::boost::program_options::bool_switch (), "Do not verify WebVTT files.")
        	;

    for (int i = s_none + 1; i < s_error; ++i)
    {   const e_ontology es = static_cast < e_ontology > (i);
        if (is_faux_schema (es)) continue;
        ::std::string naam (ontology_names.get (es, ONTOLOGY_NAME));
        ::std::string arg = ONTOLOGY;
        arg += naam;
        ::std::string desc (ontology_names.get (es, ONTOLOGY_DESCRIPTION));
        desc += ", ";
        if (get_ontology_version_count (es) == 2)
        {   desc += "either ";
            desc += get_first_ontology_version (es).ver ();
            desc += " or "; }
        else if (get_ontology_version_count (es) > 1)
        {   desc += "between ";
            desc += get_first_ontology_version (es).ver ();
            desc += " and "; }
        desc += get_last_ontology_version (es).ver ();
        desc += " (experimental)";
        ontology_.add_options ()
            (arg.c_str (), ::boost::program_options::value < ::std::string > (), desc.c_str ()); }

    valid_.add_options ()
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
    for (auto ss : c.validation ())
        valid_.add_options () (ss.first.c_str (), ::boost::program_options::value < vstr_t > () -> composing (), ss.second.c_str ());

    cmd_.add (basic_).add (primary_).add (ontology_).add (valid_).add (hidden_);
    config_.add (primary_).add (risky_).add (ontology_).add (valid_).add (hidden_).add (cgi_);
    aid_.add (basic_).add (primary_).add (risky_).add (ontology_); }

bool options::parse (nitpick& nits, const ::boost::filesystem::path& file)
{   vstr_t unrecognised;
    try
#ifdef  NO_PCF_STR
    {   ::std::ifstream fis (file.string ().c_str ());
        auto opt = ::boost::program_options::parse_config_file (fis, config_, true);
#else
    {   auto opt = ::boost::program_options::parse_config_file (file.string ().c_str (), config_, true);
#endif
        ::boost::program_options::store (opt, var_);
        unrecognised = ::boost::program_options::collect_unrecognized (opt.options, ::boost::program_options::include_positional); }
    catch (const ::boost::program_options::error& err)
    {   nits.pick (nit_configuration, es_error, ec_init, "Exception ", quote (err.what ()), " when processing ", file.string ());
        return false; }
    catch (...)
    {   nits.pick (nit_configuration, es_error, ec_init, "Unknown exception when processing ", file.string ());
        return false; }
    for (auto u : unrecognised)
        nits.pick (nit_unknown_option, es_warning, ec_init, "Unknown configuration option ", quote (u), " ignored");
    ::boost::program_options::notify (var_);
    return true; }

bool options::parse (context_t& c, nitpick& nits, const ::boost::filesystem::path& file)
{   init (c);
    return parse (nits, file); }

void options::parse (context_t& c, nitpick& nits, const vstr_t& vs)
{   ::std::string loaded;
    init (c);
    if (! context.gui () && ! context.serve ())
        try
        {   ::boost::program_options::store (::boost::program_options::parse_environment (environ_, ::boost::function1 < ::std::string, ::std::string> (env_mapper)), env_var_);
            if (env_var_.count (ENV_ARGS))
            {   ::std::string e (env_var_ [ENV_ARGS].as < ::std::string > ());
                vstr_t env_args (split_by_space (e));
                if (! env_args.empty ())
                {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
                    macro -> set (nm_run_environment, e);
                    ::boost::program_options::store (::boost::program_options::command_line_parser (env_args).options (cmd_).positional (pos_).run (), var_); } } }
        catch (const ::boost::program_options::error& err)
        {   nits.pick (nit_configuration, es_error, ec_init, "Environment error: ", err.what ());
            nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
            return; }
        catch (...)
        {   nits.pick (nit_configuration, es_error, ec_init, "Environment error");
            nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
            return; }

    ::boost::program_options::notify (env_var_);

    if (env_var_.count (ENV_CONFIG)) c.environment (env_config, env_var_ [ENV_CONFIG].as < ::std::string > ());
    if (env_var_.count (ENV_ARGS)) c.environment (env_args, env_var_ [ENV_ARGS].as < ::std::string > ());

    if (env_var_.count (QUERY_STRING))
    {   ::std::string qu (env_var_ [QUERY_STRING].as < ::std::string > ());
        c.environment (env_query_string, qu);
        if (! c.environment (env_query_string).empty ()) try
        {   c.cgi (true).article (false).body (false).cased (false).classic (false).crosslinks (false).example (false).ext_css (false).external (false)
                .forwarded (false).ie (false).icu (true).info (true).jsonld (false).links (false).load_css (false).load_vtt (false).main (false)
                .md_export (false).mf_verify (true).microdata (true).not_root (false).once (true).ontology (true).presume_tags (false).progress (false)
                .rdfa (false).rel (true).revoke (false).rfc_1867 (true).rfc_1942 (true).rfc_1980 (true).rfc_2070 (true).rpt_opens (false).shadow_changed (false)
                .shadow_comment (false).shadow_enable (false).shadow_space (false).shadow_ssi (false).sign (false).spell (false).ssi (false).stats (rcb_page, false)
                .stats (rcb_summary, false).unknown_class (false).update (false).verify (false);
            VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
            macro -> set (nm_query, qu);
            if (env_var_.count (SERVER_SOFTWARE)) c.environment (env_server_software, env_var_ [SERVER_SOFTWARE].as < ::std::string > ());
            if (env_var_.count (SERVER_NAME)) c.environment (env_server_name, env_var_ [SERVER_NAME].as < ::std::string > ());
            if (env_var_.count (GATEWAY_INTERFACE)) c.environment (env_gateway_interface, env_var_ [GATEWAY_INTERFACE].as < ::std::string > ());
            if (env_var_.count (SERVER_PROTOCOL)) c.environment (env_server_protocol, env_var_ [SERVER_PROTOCOL].as < ::std::string > ());
            if (env_var_.count (SERVER_PORT)) c.environment (env_server_port, env_var_ [SERVER_PORT].as < ::std::string > ());
            if (env_var_.count (REQUEST_METHOD)) c.environment (env_request_method, env_var_ [REQUEST_METHOD].as < ::std::string > ());
            if (env_var_.count (HTTP_ACCEPT)) c.environment (env_http_accept, env_var_ [HTTP_ACCEPT].as < ::std::string > ());
            if (env_var_.count (PATH_INFO)) c.environment (env_path_info, env_var_ [PATH_INFO].as < ::std::string > ());
            if (env_var_.count (PATH_TRANSLATED)) c.environment (env_path_translated, env_var_ [PATH_TRANSLATED].as < ::std::string > ());
            if (env_var_.count (SCRIPT_NAME)) c.environment (env_script_name, env_var_ [SCRIPT_NAME].as < ::std::string > ());
            if (env_var_.count (REMOTE_HOST)) c.environment (env_remote_host, env_var_ [REMOTE_HOST].as < ::std::string > ());
            if (env_var_.count (REMOTE_ADDR)) c.environment (env_remote_addr, env_var_ [REMOTE_ADDR].as < ::std::string > ());
            if (env_var_.count (REMOTE_USER)) c.environment (env_remote_user, env_var_ [REMOTE_USER].as < ::std::string > ());
            if (env_var_.count (AUTH_TYPE)) c.environment (env_auth_type, env_var_ [AUTH_TYPE].as < ::std::string > ());
            if (env_var_.count (CONTENT_TYPE)) c.environment (env_content_type, env_var_ [CONTENT_TYPE].as < ::std::string > ());
            if (env_var_.count (CONTENT_LENGTH)) c.environment (env_content_length, env_var_ [CONTENT_LENGTH].as < ::std::string > ());
            ::std::string q (query_to_switches (c.environment (env_query_string)));
#ifdef XTRA_DEBUG
            context.os () -> console ("Environment: ", q, "\n");
#endif // XTRA_DEBUG
            vstr_t query (split_quoted_by_space (q));
            ::boost::program_options::store (::boost::program_options::command_line_parser (query).options (cmd_).positional (pos_).run (), var_);
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
    {   ::boost::program_options::store (::boost::program_options::command_line_parser (vs).options (cmd_).positional (pos_).run (), var_); }
    catch (const ::boost::program_options::error& err)
    {   nits.pick (nit_configuration, es_error, ec_init, "Command line parameter exception: ", err.what ());
        nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
        return; }
    catch (...)
    {   nits.pick (nit_configuration, es_error, ec_init, "Command line parameter error.");
        nits.pick (nit_help, es_info, ec_init, TYPE_HELP);
        return; }

    yea_nay (c, &context_t::iterate, nits, ASK, DONT ASK);

    if (var_.count (CONFIG) || var_ [DEFCONF].as <bool > () || env_var_.count (ENV_CONFIG))
    {   ::boost::filesystem::path file (context.default_config_file ());
        if (var_.count (CONFIG)) file = var_ [CONFIG].as < ::std::string > ();
        else if ((! var_ [DEFCONF].as <bool > ()) && env_var_.count (ENV_CONFIG)) file = env_var_ [ENV_CONFIG].as < ::std::string > ();
        nits.set_context (0, file.string ());
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (nm_config, file.string ());
        if (file_exists (file))
        {   nits.pick (nit_configuration, es_debug, ec_init, ::std::string ("Loading configuration ") + file.string () + " " ELLIPSES);
            try
            {   c.config (canonical_name (absolute_name (file))); }
            catch (...)
            {   nits.pick (nit_configuration, es_error, ec_init, ::std::string ("Cannot canonise ") + file.string ());
                c.todo (do_simple);
                return; } }
        else
        {   nits.pick (nit_configuration, es_error, ec_init, ::std::string ("Cannot find ") + file.string ());
            c.todo (do_simple);
            return; }
        if (! parse (nits, file)) return; }
    if (var_ [GENERAL INFO].as <bool > ())
        c.os () -> console (c.general_info (), "\n");
    if (var_ [VERSION].as < bool > ())
    {   c.todo (do_simple);
        return; }
    if (var_ [HELP].as < bool > ())
    {   help (aid_);
        return; }
    if (var_ [SWITCHES].as < bool > ())
    {   c.yggdrisil (true);
        c.domsg (report (gr_config));
        c.todo (do_simple);
        return; }
    if (var_ [VALIDATION].as < bool > ())
    {   ::std::ostringstream waste_of_space;
        waste_of_space << valid_;
        c.domsg (waste_of_space.str ());
        c.todo (do_simple);
        return; }
    if (var_ [ONTOLOGY LIST].as < bool > ())
    {   ::std::string res, whoopsie;
        for (int i = s_none + 1; i < s_error; ++i)
        {   const e_ontology es = static_cast < e_ontology > (i);
            if (is_faux_schema (es)) continue;
            const ::std::string& naam = ontology_names.get (es, ONTOLOGY_NAME);
            res += naam;
            const ontology_version x (get_first_ontology_version (es));
            const ontology_version y (get_last_ontology_version (es));
            const int count = get_ontology_version_count (es);
            PRESUME (count >= 1, __FILE__, __LINE__);
            if (count == 1)
            {   if (x != y)
                {   if (! whoopsie.empty ()) whoopsie += ", ";
                    whoopsie += naam;
                    whoopsie += " (";
                    whoopsie += x.ver ();
                    whoopsie += ", ";
                    whoopsie += y.ver ();
                    whoopsie += ")"; }
                res += " ";
                res += x_dot_y (x.mjr (), x.mnr ()); }
            else if (count > 1)
            {   if (x == y)
                {   if (! whoopsie.empty ()) whoopsie += ", ";
                    whoopsie += naam;
                    whoopsie += " (";
                    whoopsie += x.ver ();
                    whoopsie += ")"; }
                res += " ";
                res += x_dot_y (x.mjr (), x.mnr ());
                if (count == 2) res += ","; else res += "-";
                res += x_dot_y (y.mjr (), y.mnr ()); }
            res += "\n"; }
        PRESUME (whoopsie.empty (), __FILE__, __LINE__);
        c.domsg (res);
        c.todo (do_simple);
        return; }

    if (var_ [SHELL].as < bool > ())
        context.serve (true);
    
    if (! c.cgi () && var_.count (ENVIRONMENT QUERY_STRING))
    {   nits.set_context (0, "Environment");
        c.environment (env_query_string, var_ [ENVIRONMENT QUERY_STRING].as < ::std::string > ());
        if (! c.environment (env_query_string).empty ()) try
        {   c.cgi (true);
            if (var_.count (ENVIRONMENT SERVER_SOFTWARE)) c.environment (env_server_software, var_ [ENVIRONMENT SERVER_SOFTWARE].as < ::std::string > ());
            if (var_.count (ENVIRONMENT SERVER_NAME)) c.environment (env_server_name, var_ [ENVIRONMENT SERVER_NAME].as < ::std::string > ());
            if (var_.count (ENVIRONMENT GATEWAY_INTERFACE)) c.environment (env_gateway_interface, var_ [ENVIRONMENT GATEWAY_INTERFACE].as < ::std::string > ());
            if (var_.count (ENVIRONMENT SERVER_PROTOCOL)) c.environment (env_server_protocol, var_ [ENVIRONMENT SERVER_PROTOCOL].as < ::std::string > ());
            if (var_.count (ENVIRONMENT SERVER_PORT)) c.environment (env_server_port, var_ [ENVIRONMENT SERVER_PORT].as < ::std::string > ());
            if (var_.count (ENVIRONMENT REQUEST_METHOD)) c.environment (env_request_method, var_ [ENVIRONMENT REQUEST_METHOD].as < ::std::string > ());
            if (var_.count (ENVIRONMENT HTTP_ACCEPT)) c.environment (env_http_accept, var_ [ENVIRONMENT HTTP_ACCEPT].as < ::std::string > ());
            if (var_.count (ENVIRONMENT PATH_INFO)) c.environment (env_path_info, var_ [ENVIRONMENT PATH_INFO].as < ::std::string > ());
            if (var_.count (ENVIRONMENT PATH_TRANSLATED)) c.environment (env_path_translated, var_ [ENVIRONMENT PATH_TRANSLATED].as < ::std::string > ());
            if (var_.count (ENVIRONMENT SCRIPT_NAME)) c.environment (env_script_name, var_ [ENVIRONMENT SCRIPT_NAME].as < ::std::string > ());
            if (var_.count (ENVIRONMENT REMOTE_HOST)) c.environment (env_remote_host, var_ [ENVIRONMENT REMOTE_HOST].as < ::std::string > ());
            if (var_.count (ENVIRONMENT REMOTE_ADDR)) c.environment (env_remote_addr, var_ [ENVIRONMENT REMOTE_ADDR].as < ::std::string > ());
            if (var_.count (ENVIRONMENT REMOTE_USER)) c.environment (env_remote_user, var_ [ENVIRONMENT REMOTE_USER].as < ::std::string > ());
            if (var_.count (ENVIRONMENT AUTH_TYPE)) c.environment (env_auth_type, var_ [ENVIRONMENT AUTH_TYPE].as < ::std::string > ());
            if (var_.count (ENVIRONMENT CONTENT_TYPE)) c.environment (env_content_type, var_ [ENVIRONMENT CONTENT_TYPE].as < ::std::string > ());
            if (var_.count (ENVIRONMENT CONTENT_LENGTH)) c.environment (env_content_length, var_ [ENVIRONMENT CONTENT_LENGTH].as < ::std::string > ());
            ::std::string q (query_to_switches (c.environment (env_query_string)));
#ifdef XTRA_DEBUG
            c.os () -> console ("Config: ", q, "\n");
#endif // XTRA_DEBUG
            vstr_t query (split_quoted_by_space (q));
            ::boost::program_options::store (::boost::program_options::command_line_parser (query).options (cmd_).positional (pos_).run (), var_);
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

    if (! c.cgi ()) yea_nay (c, &context_t::cgi, nits, GENERAL CGI, GENERAL DONT CGI);
    nits.set_context (0, "Configuration");

    if (c.cgi ()) c.todo (do_cgi);
    else if ((! context.serve ()) && (! var_.count (WEBSITE ROOT)) && (! var_.count (HTML SNIPPET)) && ! var_.count (OUTPUT VERIFY))
    {   c.domsg ("\n" TYPE_HELP "\n");
        c.todo (do_simple);
        return; }
    else c.todo (do_examine); }

void options::contextualise (context_t& c, nitpick& nits)
{   yea_nay (c, &context_t::test, nits, GENERAL TEST, GENERAL DONT TEST);
    yea_nay (c, &context_t::spec, nits, NITS SPEC, NITS DONT SPEC);

    if (c.test () || is_be (GENERAL SPEC))
        c.adstxt (false).article (false).atomic_verify (false).body (false).cased (false).classic (false).crosslinks (false).example (false).external (false).ext_css (false)
            .forwarded (false)
            .icu (true).info (false).jsonld (false).links (false).load_css (true).load_vtt (true).main (false).md_export (false).mf_verify (false)
            .microdata (false).nids (true).nits (false).nits_nits_nits (true).not_root (false).once (false).ontology (true).presume_tags (false).progress (false).rdfa (false)
            .rel (false).revoke (false).rfc_1867 (true).rfc_1942 (true).rfc_1980 (true).rfc_2070 (true).robtxt (false).rpt_opens (false).rsl_verify (false).rss_verify (false)
            .sectxt (false).serve (false).shadow_changed (false).shadow_comment (false).shadow_enable (false).shadow_space (false).shadow_ssi (false).sign (false)
            .spell (false).ssi (false).stats (rcb_page, false).stats (rcb_summary, false).unknown_class (false).update (false).verify (false);

#ifndef NO_FRED
    if (var_.count (GENERAL THREAD)) c.fred (var_ [GENERAL THREAD].as < int > ());
    else if (var_.count (GENERAL DEFTHRD)) c.fred (var_ [GENERAL DEFTHRD].as < int > ());
    else c.fred (1);
#endif // NO_FRED

    if (var_.count (OUTPUT FORMAT)) c.output_format (var_ [OUTPUT FORMAT].as < ::std::string > ());
    if (var_.count (OUTPUT OVERRIDE)) c.output_override (var_ [OUTPUT OVERRIDE].as < ::std::string > ());

    if (var_.count (NITS VERBOSE)) c.verbose (decode_severity (nits, var_ [NITS VERBOSE].as < ::std::string > ()));
    else if (var_.count (GENERAL VERBOSE)) c.verbose (decode_severity (nits, var_ [GENERAL VERBOSE].as < ::std::string > ()));
    if (var_.count (HTML SNIPPET)) c.snippet (var_ [HTML SNIPPET].as < ::std::string > ());
    yea_nay (c, &context_t::mf_verify, nits, MF VERIFY, MF DONT VERIFY);

    if (c.test () || ! c.cgi ())
    {   ::std::string gen_out, gen_copy, outpout;
        if (var_.count (GENERAL OUTPUT_))
        {   gen_out = nix_path_to_local (var_ [GENERAL OUTPUT_].as < ::std::string > ());
            c.out_name (gen_out); }
        if (var_.count (GENERAL COPY))
        {   gen_copy = nix_path_to_local (var_ [GENERAL COPY].as < ::std::string > ());
            c.out_copy (gen_copy); }

        if (! gen_copy.empty ()) outpout = gen_copy;
        else outpout = gen_out;
        
        if (! outpout.empty ())
        {   c.os () -> init (nits, outpout);
#ifndef EXPAND_TEST
            if (! c.test ())
                if (gen_copy.empty ()) nits.pick (nit_configuration, es_debug, ec_init, ::std::string ("Writing to ") + outpout);
                else nits.pick (nit_configuration, es_debug, ec_init, ::std::string ("Writing to ") + gen_out + ::std::string (" & ") + gen_copy);
#endif // EXPAND_TEST
        }
        if ((! is_be (GENERAL DONT PROGRESS)) && is_be (GENERAL PROGRESS))
            if (c.test ()) c.os () -> console (TEST_TITLE);
            else if (c.tell (es_info)) c.os () -> console (FULL_TITLE);
            else c.os () -> console (SIMPLE_TITLE); }

    if (! c.cgi ())
    {   ::std::string datapath (nix_path_to_local (var_ [GENERAL DATAPATH].as < ::std::string > ()));
        if (! file_exists (datapath))
        {   nits.pick (nit_create_folder, es_comment, ec_init, "creating ", datapath);
            if (! make_directories (datapath))
            {   nits.pick (nit_cannot_create_file, es_catastrophic, ec_init, "cannot create ", datapath);
                datapath.clear (); } }
        c.path (datapath); }

    if (var_.count (MF VERSION))
    {   int n = var_ [MF VERSION].as < int > ();
        if ((n < 1) || (n > 3))
        {   nits.pick (nit_mf_version, es_warning, ec_init, "invalid microformats version; presuming version 2");
            n = 2; }
        c.mf_version (GSL_NARROW_CAST < unsigned char > (n)); }

    if (var_.count (HTML VERSION) != 0)
        c.html_ver (html_version (nits, var_ [HTML VERSION].as < ::std::string > ()));

    if (var_.count (OUTPUT STYLESHEET)) c.stylesheet (var_ [OUTPUT STYLESHEET].as < ::std::string > ());

    if (! c.cgi ())
        if (var_.count (WEBSITE ROOT) != 0)
        {   const ::std::string arg = trim_the_lot_off (var_ [WEBSITE ROOT].as < ::std::string > ());
            if (arg.empty ()) nits.pick (nit_no_such_folder, es_error, ec_init, "that --" WEBSITE ROOT " is a little too spaced out for " PROG);
            else
            {   const ::std::string local = nix_path_to_local (arg);
                if (! file_exists (local))
                    nits.pick (nit_no_such_folder, es_error, ec_init, PROG " cannot access the directory ", quote (local));
                else if (is_folder (local))
                    c.root (local);
                else nits.pick (nit_not_directory, es_error, ec_init, "expecting a directory containing a static website, not ", quote (local)); } }

    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> load_template (nits, c.html_ver ());

    for (int i = s_none + 1; i < s_error; ++i)
    {   const e_ontology es = static_cast < e_ontology > (i);
        if (is_faux_schema (es)) continue;
        if (get_ontology_version_count (es) < 1) continue;
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
                nits.pick (nit_config_version, es_error, ec_init, PROG " dislikes the ", quote (x.name ()), " version specified; use " ONTOLOGY LIST " to get a list of known versions.");
            else c.ont_ver (es, ver); } }

    if (var_.count (VALIDATION MICRODATAARG)) c.microdata (true);
    if (var_.count (VALIDATION DONT MICRODATAARG)) c.microdata (false);

    if (! c.cgi ())
    {   yea_nay (c, &context_t::adstxt, nits, GENERAL ADS, GENERAL DONT ADS);
        yea_nay (c, &context_t::unknown_class, nits, GENERAL CLASS, GENERAL DONT CLASS);
        yea_nay (c, &context_t::classic, nits, GENERAL CLASSIC, GENERAL DONT CLASSIC);
        yea_nay (c, &context_t::comms, nits, GENERAL DONT COMMS, GENERAL COMMS);
        yea_nay (c, &context_t::excl_def_excl, nits, GENERAL EDE, GENERAL DONT EDE);
        yea_nay (c, &context_t::progress, nits, GENERAL PROGRESS, GENERAL DONT PROGRESS);
        yea_nay (c, &context_t::rdfa, nits, GENERAL RDFA, GENERAL DONT RDFA);
        yea_nay (c, &context_t::robtxt, nits, GENERAL ROBOTS, GENERAL DONT ROBOTS);
        yea_nay (c, &context_t::rpt_opens, nits, GENERAL RPT, GENERAL DONT RPT);
        yea_nay (c, &context_t::sectxt, nits, GENERAL SECURITY, GENERAL DONT SECURITY);
        c.persisted (path_in_context (nix_path_to_local (var_ [GENERAL FICHIER].as < ::std::string > ())));

        CONSTEXPR long meg = 1024*1024;

        if (! var_.count (GENERAL MAXFILESIZE))
            c.max_file_size (4 * meg);
        else
        {   long max = static_cast < long > (var_ [GENERAL MAXFILESIZE].as < int > ());
            if (max < 0 || (max > (LONG_MAX / meg))) max = DMFS_BYTES;
            c.max_file_size (max * meg); }

        if (var_.count (GENERAL EXCLUDE)) c.exclude (nits, var_ [GENERAL EXCLUDE].as < vstr_t > ());
        if (var_.count (GENERAL HELPSITE)) c.help (var_ [GENERAL HELPSITE].as < ::std::string > ());
        if (var_.count (GENERAL LINE_LENGTH)) c.line_length (var_ [GENERAL LINE_LENGTH].as < long > ());
        if (var_.count (GENERAL MACROEND)) c.macro_end (var_ [GENERAL MACROEND].as < ::std::string > ());
        if (var_.count (GENERAL MACROSTART)) c.macro_start (var_ [GENERAL MACROSTART].as < ::std::string > ());
        if (var_.count (GENERAL SILENCE)) c.silence (nits, var_ [GENERAL SILENCE].as < vstr_t > ());
        if (var_.count (GENERAL URL_VAR)) c.urlvar (var_ [GENERAL URL_VAR].as < vstr_t > ());
        yea_nay (c, &context_t::update_check, nits, GENERAL UPDATE, GENERAL DONT UPDATE);
        yea_nay (c, &context_t::vcs, nits, GENERAL VCS, GENERAL DONT VCS);

        if (is_be (GENERAL YGGDRISIL)) c.yggdrisil (true);

        yea_nay (c, &context_t::atomic_verify, nits, ATOMIC VERIFY, ATOMIC DONT VERIFY);
        if (var_.count (ATOMIC EXTENSION)) c.atomic_ext (var_ [ATOMIC EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back (ATOMIC_EXT); c.atomic_ext (ex); }

        if (var_.count (CORPUS OUTPUT_)) c.corpus (nix_path_to_local (var_ [CORPUS OUTPUT_].as < ::std::string > ()));
        yea_nay (c, &context_t::article, nits, CORPUS ARTICLE, CORPUS DONT ARTICLE);
        yea_nay (c, &context_t::body, nits, CORPUS BODY, CORPUS DONT BODY);
        yea_nay (c, &context_t::main, nits, CORPUS MAIN, CORPUS DONT MAIN);

        if (var_.count (CSS EXTENSION)) c.css_extension (var_ [CSS EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back (CSS_EXT); c.css_extension (ex); }
        yea_nay (c, &context_t::load_css, nits, CSS VERIFY, CSS DONT VERIFY);
        yea_nay (c, &context_t::ext_css, nits, CSS EXTERNAL, CSS DONT EXTERNAL);
        
        if (var_.count (CSS VERSION) != 0)
        {   ::std::string ver (var_ [CSS VERSION].as < ::std::string > ());
            if (ver.empty ()) nits.pick (nit_config_version, es_warning, ec_init, "missing CSS version");
            else c.css_version (examine_value < t_css_version > (nits, html_default, ver)); }

        int n = 0;
        process_css_level (c, c_colour_adjustment, n, nits, CSS ADJUST, "Colour Adjust", 4);
        process_css_level (c, c_advanced_layout, n, nits, CSS ADVLAY, "Advanced Layout", 3);
        process_css_level (c, c_scroll_anchoring, n, nits, CSS ANCHOR, "Scrollbar Anchoring", 4);
        process_css_level (c, c_anchor_pos, n, nits, CSS ANCHOR_POS, "Anchor Positioning", 3);
        process_css_level (c, c_animation, n, nits, CSS ANIMATION, "Animation", 4);
        process_css_level (c, c_background_border, n, nits, CSS BACKGROUND, "Background Border", 4);
        process_css_level (c, c_box_alignment, n, nits, CSS BOX_ALIGN, "Background Alignment", 3);
        process_css_level (c, c_border_box, n, nits, CSS BORDER, "Border Box", 4);
        process_css_level (c, c_box_model, n, nits, CSS BOX_MODEL, "Box Model", 4);
        process_css_level (c, c_box_sizing, n, nits, CSS BOX_SIZING, "Background Sizing", 4);
        process_css_level (c, c_cascade_inheritance, n, nits, CSS CASCADE, "Cascade & Inheritance", 6);
        process_css_level (c, c_colour, n, nits, CSS COLOUR, "Colour", 6);
        process_css_level (c, c_compositing_blending, n, nits, CSS COMPOSITING, "Compositing & Blending", 4);
        process_css_level (c, c_conditional_rule, n, nits, CSS COND_RULE, "Conditional Rule", 5);
        process_css_level (c, c_containment, n, nits, CSS CONTAIN, "Contain", 5);
        process_css_level (c, c_generated_content, n, nits, CSS CON_TENT, "Generated Content", 3);
        process_css_level (c, c_counter_style, n, nits, CSS CS, "Counter Style", 3);
        process_css_level (c, c_custom_property, n, nits, CSS CUSTOM, "Custom", 3, true);
        process_css_level (c, c_device_adaption, n, nits, CSS DEVICE, "Device Adaption", 3);
        process_css_level (c, c_display, n, nits, CSS DISPLAY, "Display", 3);
        process_css_level (c, c_easing_function, n, nits, CSS EASE, "Ease", 4);
        process_css_level (c, c_environment, n, nits, CSS ENVIRONMENT, "Environment", 3);
        process_css_level (c, c_exclusion, n, nits, CSS EXCLUDE, "Exclusions", 3);
        process_css_level (c, c_flexible_box_layout, n, nits, CSS FBL, "Flexible Box Layout", 3);
        process_css_level (c, c_fill_stroke, n, nits, CSS FILL, "Fill and Stroke", 3);
        process_css_level (c, c_filter_effect, n, nits, CSS FILTER, "Filter Effects", 3);
        process_css_level (c, c_page_float, n, nits, CSS FLOAT, "Page Floats", 3);
        process_css_level (c, c_font, n, nits, CSS FONT, "Font", 5);
        process_css_level (c, c_fragmentation, n, nits, CSS FRAG, "Fragmentation", 4);
        process_css_level (c, c_grid_layout, n, nits, CSS GRID, "Grid", 4);
        process_css_level (c, c_hdr, n, nits, CSS HDR, "HDR", 3);
        process_css_level (c, c_custom_highlight, n, nits, CSS HIGHLIGHT, "Custom Highlight", 4);
        process_css_level (c, c_hyperlink_presentation, n, nits, CSS HYPERLINK, "Hyperlink", 5);
        process_css_level (c, c_image, n, nits, CSS IMAGE, "Image", 4);
        process_css_level (c, c_inline_layout, n, nits, CSS INLINE, "Inline Layout", 3);
        process_css_level (c, c_list_counter, n, nits, CSS LIST, "Lists and Counters", 3);
        process_css_level (c, c_line_grid, n, nits, CSS LINE_GRID, "Line Grid", 3);
        process_css_level (c, c_logical_property, n, nits, CSS LOGIC, "Logical Properties and Values", 3);
        process_css_level (c, c_marquee, n, nits, CSS MARQUEE, "Marquee", 3);
        process_css_level (c, c_math_core, n, nits, CSS MATHCORE, "Math Core", 3);
        process_css_level (c, c_masking, n, nits, CSS MASKING, "Masking", 3);
        process_css_level (c, c_media_query, n, nits, CSS MEDIA, "Media", 5);
        process_css_level (c, c_mixin, n, nits, CSS MIXIN, "Mixin", 3);
        yea_nay (c, &context_t::mobile_profile, nits, CSS MOBILE, CSS DONT MOBILE);
        process_css_level (c, c_motion_path, n, nits, CSS MOTION, "Motion Path", 3);
        process_css_level (c, c_multicolumn, n, nits, CSS MULTI_COLUMN, "Multi-Column", 3);
        process_css_level (c, c_namespace, n, nits, CSS NAMESPACE, "Namespace", 3);
        process_css_level (c, c_non_element_selector, n, nits, CSS NES, "non-Element Selectors", 3);
        process_css_level (c, c_nesting, n, nits, CSS NESTING, "Nesting", 3);
        process_css_level (c, c_overflow, n, nits, CSS OVERFLOH, "Overflow", 4);
        process_css_level (c, c_overscroll_behaviour, n, nits, CSS OVERSCROLL, "Overscroll Behaviour", 3);
        process_css_level (c, c_paged_media, n, nits, CSS PAGE, "Paged Media", 3);
        process_css_level (c, c_positioned_layout, n, nits, CSS POSITION, "Position", 3);
        process_css_level (c, c_presentation_level, n, nits, CSS PRESENT, "Presentation Levels", 3);
        yea_nay (c, &context_t::print_profile, nits, CSS PRINT, CSS DONT PRINT);
        process_css_level (c, c_pseudo_element, n, nits, CSS PSEUDO, "Pseudo-Elements", 4);
        process_css_level (c, c_region, n, nits, CSS REGION, "Regions", 3);
        process_css_level (c, c_rhythmic_sizing, n, nits, CSS RHYTHM, "Rhythmic Sizing", 4);
        process_css_level (c, c_round_display, n, nits, CSS ROUND, "Round Display", 4);
        process_css_level (c, c_ruby_annotation, n, nits, CSS RUBY, "Ruby Annotation Layout", 4);
        process_css_level (c, c_scoping, n, nits, CSS SCOPE, "Scoping", 3);
        process_css_level (c, c_scrollbar_styling, n, nits, CSS SCROLLBAR, "Scrollbar Styling", 3);
        process_css_level (c, c_scroll_driven_animation, n, nits, CSS SDA, "Scroll Driven Animations", 3);
        process_css_level (c, c_selector, n, nits, CSS SELECTOR, "Selector", 5);
        process_css_level (c, c_shadow_part, n, nits, CSS SP, "Shadow Parts", 4);
        process_css_level (c, c_shape, n, nits, CSS SHAPE, "Shape", 4);
        process_css_level (c, c_scroll_snap, n, nits, CSS SNAP, "Scroll Snap", 3);  // 
        process_css_level (c, c_scroll_snap_point, n, nits, CSS SNAP_POINTS, "Scroll Snap Points", 3);
        process_css_level (c, c_spatial_navigation, n, nits, CSS SPATIAL, "Spatial Navigation", 3);
        process_css_level (c, c_speech, n, nits, CSS SPEECH, "Speech", 3);
        process_css_level (c, c_style_attribute, n, nits, CSS STYLE, "Style", 3);
        process_css_level (c, c_syntax, n, nits, CSS SYNTAX, "Syntax", 3);
        process_css_level (c, c_text, n, nits, CSS TEXT_ARG, "Text", 4);
        process_css_level (c, c_text_decoration, n, nits, CSS TEXT_DEC, "Text Decoration", 4);
        process_css_level (c, c_table, n, nits, CSS TABLE, "Table", 3);
        process_css_level (c, c_transform, n, nits, CSS TRANSFORM, "Transform", 4, true);
        process_css_level (c, c_transition, n, nits, CSS TRANSITION, "Transition", 4, true);
        yea_nay (c, &context_t::tv_profile, nits, CSS TV, CSS DONT TV);
        process_css_level (c, c_basic_user_interface, n, nits, CSS UI, "UI", 4);
        process_css_level (c, c_value_unit, n, nits, CSS VAL, "Values and Units", 4);
        process_css_level (c, c_view_transition, n, nits, CSS VIEW, "View Transitions", 3);
        process_css_level (c, c_viewport, n, nits, CSS VIEWPORT, "Viewport", 3);
        process_css_level (c, c_will_change, n, nits, CSS WC, "Will Change", 3);
        process_css_level (c, c_writing_mode, n, nits, CSS WRITING, "Writing Mode", 4);

        if (var_.count (HTML ANALYSIS))
        {   const ::std::string av = var_ [HTML ANALYSIS].as < ::std::string > ();
            int e = 0;
            if (! av.empty ())
                if (av.size () == 1)
                {   e = lexical < int > :: cast (av);
                    if ((e < 0) || (e > max_analysis)) e = 0; }
                else e = examine_value < t_analysis > (nits, html_default, av);
            c.analysis (static_cast < e_analysis > (e)); }
        yea_nay (c, &context_t::aria, nits, HTML ARIA, HTML DONT ARIA);
        yea_nay (c, &context_t::chrome, nits, HTML CHROME, HTML DONT CHROME);
        if (var_.count (HTML CUSTOM)) c.custom_elements (nits, var_ [HTML CUSTOM].as < vstr_t > ());
        yea_nay (c, &context_t::efficient, nits, HTML EFFICIENT, HTML DONT EFFICIENT);
        yea_nay (c, &context_t::force_version, nits, HTML FORCE, HTML DONT FORCE);
        yea_nay (c, &context_t::ie, nits, HTML IE, HTML DONT IE);
        if (var_.count (HTML IGNORED)) c.ignore (nits, var_ [HTML IGNORED].as < vstr_t > ());
        if (var_.count (HTML LANG)) c.lang (var_ [HTML LANG].as < ::std::string > ());
        yea_nay (c, &context_t::mozilla, nits, HTML MOZILLA, HTML DONT MOZILLA);
        yea_nay (c, &context_t::netscape, nits, HTML NETSCAPE, HTML DONT NETSCAPE);
        yea_nay (c, &context_t::opera, nits, HTML OPERA, HTML DONT OPERA);
        yea_nay (c, &context_t::rel, nits, HTML REL, HTML DONT REL);
        yea_nay (c, &context_t::rfc_1867, nits, HTML RFC1867, HTML DONT RFC1867);
        yea_nay (c, &context_t::rfc_1942, nits, HTML RFC1942, HTML DONT RFC1942);
        yea_nay (c, &context_t::rfc_1980, nits, HTML RFC1980, HTML DONT RFC1980);
        yea_nay (c, &context_t::rfc_2070, nits, HTML RFC2070, HTML DONT RFC2070);
        yea_nay (c, &context_t::ruby, nits, HTML RUBY, HTML DONT RUBY);
        yea_nay (c, &context_t::presume_tags, nits, HTML TAGS, HTML DONT TAGS);
        yea_nay (c, &context_t::safari, nits, HTML SAFARI, HTML DONT SAFARI);
        yea_nay (c, &context_t::sloven, nits, HTML SLOVEN, HTML DONT SLOVEN);
        if (var_.count (HTML TITLE)) c.title (static_cast < unsigned char > (var_ [HTML TITLE].as < int > ()));
        yea_nay (c, &context_t::wx, nits, HTML WXARG, HTML DONT WXARG);
        if (var_.count (HTML WX_SNIPPET)) c.wx_snippet (var_ [HTML WX_SNIPPET].as < ::std::string > ());

        yea_nay (c, &context_t::pretty, nits, JSONLD PRETTY, JSONLD DONT PRETTY);
        yea_nay (c, &context_t::jsonld, nits, JSONLD VERIFY, JSONLD DONT VERIFY);
        if (var_.count (JSONLD EXTENSION)) c.jsonld_extension (var_ [JSONLD EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back (JSONLD_EXT); c.jsonld_extension (ex); }
        if (var_.count (JSONLD ONTOLOGY_)) c.jsonld_ontology (var_ [JSONLD ONTOLOGY_].as < vstr_t > ());

        if (var_.count (JSONLD VERSION))
        {   ::std::string ver (var_ [JSONLD VERSION].as < ::std::string > ());
            if (ver.empty ())
                nits.pick (nit_config_version, es_warning, ec_init, "missing json-ld version");
            else
            {   if (ver == "1.0") c.jsonld_version (jsonld_1_0);
                else if (ver == "1.1") c.jsonld_version (jsonld_1_1);
                else nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid json-ld version"); } }

        yea_nay (c, &context_t::links, nits, LINKS CHECK, LINKS DONT CHECK);
        yea_nay (c, &context_t::example, nits, LINKS EXAMPLE, LINKS DONT EXAMPLE);
        yea_nay (c, &context_t::external, nits, LINKS EXTERNAL, LINKS DONT EXTERNAL);
        yea_nay (c, &context_t::forwarded, nits, LINKS FORWARD, LINKS DONT FORWARD);
        if (var_.count (LINKS IGNORED)) c.no_ex_check (var_ [LINKS IGNORED].as < vstr_t > ());
        yea_nay (c, &context_t::local, nits, LINKS LOCAL, LINKS DONT LOCAL);
        yea_nay (c, &context_t::once, nits, LINKS ONCE, LINKS DONT ONCE);
        if (var_.count (LINKS PRETEND)) c.pretend (nits, var_ [LINKS PRETEND].as < vstr_t > ());
        if (var_.count (LINKS REPORT)) c.report (var_ [LINKS REPORT].as < vstr_t > ());
        if (var_.count (LINKS REQUIRED)) add_required_pages (nits, var_ [LINKS REQUIRED].as < vstr_t > ());
        yea_nay (c, &context_t::revoke, nits, LINKS REVOKE, LINKS DONT REVOKE);
        yea_nay (c, &context_t::special, nits, LINKS SPECIAL, LINKS DONT SPECIAL);
        yea_nay (c, &context_t::crosslinks, nits, LINKS XLINK, LINKS DONT XLINK);

        if (var_.count (MATH VERSION))
        {   ::std::string s = var_ [MATH VERSION].as < ::std::string > ();
            if (compare_no_case ("core", s)) c.math_version (math_core);
            else if (s == "4") c.math_version (math_4);
            else if (s == "3") c.math_version (math_3);
            else if (s == "2") c.math_version (math_2);
            else if (s == "1") c.math_version (math_1);
            else if (s == "0") c.math_version (math_none);
            else 
            {   nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid MathML version");
                c.math_version (math_none); } }

        yea_nay (c, &context_t::mf_export, nits, MF EXPORT, MF DONT EXPORT);
        yea_nay (c, &context_t::mf_pretty, nits, MF PRETTY, MF DONT PRETTY);

        if (var_.count (NITS CACHE)) c.cache (var_ [NITS CACHE].as < ::std::string > ());
        yea_nay (c, &context_t::nids, nits, NITS NIDS, NITS DONT NIDS);
        yea_nay (c, &context_t::extra, nits, NITS EXTRA, NITS DONT EXTRA);
        if (var_.count (NITS FORMAT)) c.output_format (var_ [NITS FORMAT].as < ::std::string > ());
        if (var_.count (NITS QUOTE))
        {   const e_quote_style qs = examine_value < t_quote_style > (nits, html_default, var_ [NITS QUOTE].as < ::std::string > ());
            c.quote_style (qs); }
        yea_nay (c, &context_t::not_root, nits, NITS DONT ROOT, NITS ROOT); // note reversal
        yea_nay (c, &context_t::nits_nits_nits, nits, NITS UNIQUE, NITS DONT UNIQUE);
        yea_nay (c, &context_t::nits, nits, NITS WATCH, NITS DONT WATCH);
        if (var_.count (NITS XXX)) c.x (var_ [NITS XXX].as < ::std::string > ());

#define KNITTING(NAME,SEV,KNIT) \
        if (var_.count (NITS NAME)) \
            for (auto s : var_ [NITS NAME].as < vstr_t > ()) \
                if (nitpick::modify_severity (s, SEV)) c.KNIT (s);\
                else nits.pick (nit_config_nit, es_error, ec_init, quote (s), ": no such nit.");

        KNITTING (CATASTROPHE, es_catastrophic, catastrophe); 
        KNITTING (ABHORRENT, es_abhorrent, abhorrent); 
        KNITTING (COMMENT, es_comment, comment); 
        KNITTING (DBG, es_debug, debug); 
        KNITTING (WHOOPS, es_error, error); 
        KNITTING (INFO, es_info, inform); 
        KNITTING (SILENCE, es_illegal, silent); 
        KNITTING (WARNING, es_warning, warning); 
#undef KNITTING

        if (var_.count (NITS ERROREXIT))
        {   const e_severity sev = decode_severity (nits, var_ [NITS ERROREXIT].as < ::std::string > ());
            if (sev != es_undefined) c.report_error (sev); }

        yea_nay (c, &context_t::md_export, nits, ONTOLOGY EXPORT, ONTOLOGY DONT EXPORT);
        yea_nay (c, &context_t::md_pretty, nits, ONTOLOGY PRETTY, ONTOLOGY DONT PRETTY);
        yea_nay (c, &context_t::ontology, nits, ONTOLOGY VERIFY, ONTOLOGY DONT VERIFY);
        if (var_.count (ONTOLOGY ROOT)) c.export_root (nix_path_to_local (var_ [ONTOLOGY ROOT].as < ::std::string > ()));
        if (var_.count (ONTOLOGY VIRTUAL)) c.exports (var_ [ONTOLOGY VIRTUAL].as < vstr_t > ());

        yea_nay (c, &context_t::absolute_path, nits, OUTPUT APATH, OUTPUT RPATH);
        if (var_.count (OUTPUT ACCOUNT)) c.account (var_ [OUTPUT ACCOUNT].as < ::std::string > ());
        if (var_.count (OUTPUT BACK)) c.back (var_ [OUTPUT BACK].as < ::std::string > ());
        if (var_.count (OUTPUT BUILD)) c.build (var_ [OUTPUT BUILD].as < ::std::string > ());
        if (var_.count (OUTPUT DESCRIPTION)) c.output_description (var_ [OUTPUT DESCRIPTION].as < vstr_t > ());
        if (var_.count (OUTPUT FORMAT)) c.output_format (var_ [OUTPUT FORMAT].as < ::std::string > ());
        if (var_.count (OUTPUT HOME)) c.home (var_ [OUTPUT HOME].as < ::std::string > ());
#ifdef SIGNING
        if (var_.count (OUTPUT PASSWORD)) c.output_password (absolute_name (var_ [OUTPUT PASSWORD].as < ::std::string > ()));
        if (var_.count (OUTPUT PRIVATE)) c.output_private (absolute_name (var_ [OUTPUT PRIVATE].as < ::std::string > ()));
        if (var_.count (OUTPUT PUBLIC)) c.output_public (absolute_name (var_ [OUTPUT PUBLIC].as < ::std::string > ()));
        yea_nay (c, &context_t::sign, nits, OUTPUT SIGN, OUTPUT DONT SIGN);
        if (var_.count (OUTPUT SIGNATURE)) c.output_signature (absolute_name (var_ [OUTPUT SIGNATURE].as < ::std::string > ()));
#endif // SIGNING 
        if (var_.count (OUTPUT TIME)) c.output_time (var_ [OUTPUT TIME].as < ::std::string > ());
        if (var_.count (OUTPUT USERNAME)) c.username (var_ [OUTPUT USERNAME].as < ::std::string > ());
        yea_nay (c, &context_t::verify, nits, OUTPUT VERIFY, OUTPUT DONT VERIFY);

        yea_nay (c, &context_t::rsl_verify, nits, RSL VERIFY, RSL DONT VERIFY);
        if (var_.count (RSL EXTENSION)) c.rsl_ext (var_ [RSL EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back (RSL_EXT); c.rsl_ext (ex); }

        yea_nay (c, &context_t::rss_verify, nits, RSS VERIFY, RSS DONT VERIFY);
        if (var_.count (RSS EXTENSION)) c.rss_ext (var_ [RSS EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back (RSS_EXT); c.rss_ext (ex); }

        if (var_.count (RSS VERSION))
        {   const e_rss_version rsvp = examine_value < t_rss_version > (nits, html_tags, var_ [RSS VERSION].as < ::std::string > ());
            if (rsvp != rv_error) c.rss_version (rsvp); }

        yea_nay (c, &context_t::shadow_changed, nits, SHADOW CHANGED, SHADOW DONT CHANGED);
        yea_nay (c, &context_t::shadow_comment, nits, SHADOW COMMENT, SHADOW DONT COMMENT);

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
            if (sh != sh_error) c.copy (static_cast < int > (sh) - 1);
            else nits.pick (nit_config_shadow, es_error, ec_init, "invalid " SHADOW COPY " option"); }

        yea_nay (c, &context_t::shadow_enable, nits, SHADOW ENABLE, SHADOW DONT ENABLE);
        if (var_.count (SHADOW FICHIER)) c.shadow_persist (nix_path_to_local (var_ [SHADOW FICHIER].as < ::std::string > ()));
        if (var_.count (SHADOW IGNORED)) c.shadow_ignore (var_ [SHADOW IGNORED].as < vstr_t > ());
        yea_nay (c, &context_t::info, nits, SHADOW INFO, SHADOW DONT INFO);
        if (var_.count (SHADOW MSG)) c.msg (var_ [SHADOW MSG].as < ::std::string > ());
        if (var_.count (SHADOW NAUGHTY)) c.naughty (var_ [SHADOW NAUGHTY].as < vstr_t > ());
        if (var_.count (SHADOW NICE)) c.nice (var_ [SHADOW NICE].as < vstr_t > ());
        if (var_.count (SHADOW NOTE)) c.note (var_ [SHADOW NOTE].as < vstr_t > ());
        if (var_.count (SHADOW REPLACE)) c.replace (var_ [SHADOW REPLACE].as < vstr_t > ());
        if (var_.count (SHADOW ROOT)) c.shadow_root (nix_path_to_local (var_ [SHADOW ROOT].as < ::std::string > ()));
        yea_nay (c, &context_t::shadow_space, nits, SHADOW SPACING, SHADOW DONT SPACING);
        yea_nay (c, &context_t::shadow_ssi, nits, SHADOW SSI_, SHADOW DONT SSI_);
        yea_nay (c, &context_t::update, nits, SHADOW UPDATE, SHADOW DONT UPDATE);
        if (var_.count (SHADOW VIRTUAL)) c.shadows (var_ [SHADOW VIRTUAL].as < vstr_t > ());

        if (var_.count (WEBSITE INDEX)) c.index (var_ [WEBSITE INDEX].as < ::std::string > ());
        if (var_.count (WEBSITE EXTENSION)) c.extensions (var_ [WEBSITE EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back (HTML_EXT); c.extensions (ex); }

        if (var_.count (WEBSITE SITE))
        {   const vstr_t v (var_ [WEBSITE SITE].as < vstr_t > ());
            vstr_t g;
            for (const ::std::string& name : v)
                if (name.find_first_not_of (DOMAINNAME) != ::std::string::npos)
                    nits.pick (nit_invalid_domain, es_error, ec_init, quote (name), " is not a valid domain name (do not include protocols)");
                else g.push_back (name);
            c.site (g); }

        if (var_.count (WEBSITE VIRTUAL)) c.virtuals (var_ [WEBSITE VIRTUAL].as < vstr_t > ());

#ifdef NOSPELL
        c.spell (false);
#else // NOSPELL
        yea_nay (c, &context_t::spell, nits, SPELL CHECK, SPELL DONT CHECK);
        yea_nay (c, &context_t::cased, nits, SPELL CASED, SPELL DONT CASED);
        yea_nay (c, &context_t::icu, nits, SPELL ICU, SPELL DONT ICU);
        if (c.spell ())
        {   if (var_.count (SPELL ACCEPT)) c.spellings (var_ [SPELL ACCEPT].as < vstr_t > ());
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
                    add_spell_list (nits, lang, fn);
                    c.spell_list (fn.string ()); } }
#ifdef HUNSPELL
            if (var_.count (SPELL PATH))
            {   ::boost::filesystem::path hunspell (var_ [SPELL PATH].as < ::std::string > ());
                if (! file_exists (hunspell)) { nits.pick (nit_no_spell, es_error, ec_init, "Cannot find ", hunspell.string ()); c.spell (false); }
                else if (! is_folder (hunspell)) { nits.pick (nit_no_spell, es_error, ec_init, hunspell.string (), " is not a directory"); c.spell (false); }
                else c.spell_path (hunspell); }
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
                    if (file_exists (dd))
                        if (is_folder (dd))
                        {   c.spell_path (dd);
                            found = true; }
                if (found) c.spell_deduced (true);
                else
                {   nits.pick (nit_no_spell, es_error, ec_init, "Cannot find dictionaries");
                    c.spell (false); } }
            if (c.spell () && var_.count (SPELL DICT))
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
                    add_dict (lang, dict);
                    c.dict (dict);
                    c.dlang (lang); } }
#endif // HUNSPELL
            lingo::identify_dialects (nits); }
#endif // NOSPELL

        yea_nay (c, &context_t::ssi, nits, SSI VERIFY, SSI DONT VERIFY);
        if (var_.count (SSI DATETIME)) c.ssi_date (string_to_time (nits, var_ [SSI DATETIME].as < ::std::string > ()));
        if (var_.count (SSI DOCARGS)) c.ssi_doc_args (nits, var_ [SSI DOCARGS].as < ::std::string > ());
        if (var_.count (SSI ECHOMSG)) c.ssi_echomsg (nits, var_ [SSI ECHOMSG].as < ::std::string > ());
        if (var_.count (SSI ERRMSG)) c.ssi_errmsg (nits, var_ [SSI ERRMSG].as < ::std::string > ());
        yea_nay (c, &context_t::ssi_exec_run, nits, SSI EXECRUN, SSI DONT EXECRUN);
        if (var_.count (SSI EXECTEXT)) c.ssi_exec_text (nits, var_ [SSI EXECTEXT].as < ::std::string > ());
        if (var_.count (SSI LASTMOD)) c.ssi_lastmod (string_to_time (nits, var_ [SSI LASTMOD].as < ::std::string > ()));
        if (var_.count (SSI QUERYSTRING)) c.ssi_query_string (nits, var_ [SSI QUERYSTRING].as < ::std::string > ());
        if (var_.count (SSI TIMEFMT)) c.ssi_timefmt (nits, var_ [SSI TIMEFMT].as < ::std::string > ());
        if (var_.count (SSI USERNAME)) c.ssi_user_name (nits, var_ [SSI USERNAME].as < ::std::string > ());

        if (is_be (STATS SELECTED))
            c.stats (rcb_error, true).stats (rcb_file, true).stats (rcb_summary, true);

        if (is_be (STATS DONT ALL)) c.stats_all (false);
        else if (is_be (STATS ALL)) c.stats_all (true);
        yea_nay (c, rcb_abbreviation, nits, STATS ABBR, STATS DONT ABBR);
        yea_nay (c, rcb_annotation, nits, STATS ANNOTATION, STATS DONT ANNOTATION);
        yea_nay (c, rcb_attribute, nits, STATS ATTRIB, STATS DONT ATTRIB);
        yea_nay (c, rcb_category, nits, STATS CAT, STATS DONT CAT);
        yea_nay (c, rcb_character_variant, nits, STATS CHARVAR, STATS DONT CHARVAR);
        yea_nay (c, rcb_class, nits, STATS CLASS, STATS DONT CLASS);
        yea_nay (c, rcb_content_name, nits, STATS CONNAME, STATS DONT CONNAME);
        yea_nay (c, rcb_counter_style, nits, STATS COUSTYLE, STATS DONT COUSTYLE);
        yea_nay (c, rcb_css_property, nits, STATS CSSPROP, STATS DONT CSSPROP);
        yea_nay (c, rcb_custom_media, nits, STATS CUSTMED, STATS DONT CUSTMED);
        yea_nay (c, rcb_custom_property, nits, STATS CUSTPROP, STATS DONT CUSTPROP);
        yea_nay (c, rcb_definition, nits, STATS DFN, STATS DONT DFN);
        yea_nay (c, rcb_name_value, nits, STATS DTDD, STATS DONT DTDD);
        yea_nay (c, rcb_element, nits, STATS ELEMENT, STATS DONT ELEMENT);
        yea_nay (c, rcb_error, nits, STATS WHOOPS, STATS DONT WHOOPS);
        if (var_.count (STATS EXPORT)) c.stats (var_ [STATS EXPORT].as < ::std::string > ());
        yea_nay (c, rcb_file, nits, STATS FICHIER, STATS DONT FICHIER);
        yea_nay (c, rcb_font, nits, STATS FONT, STATS DONT FONT);
        yea_nay (c, rcb_font_family, nits, STATS FONT_FAMILY, STATS DONT FONT_FAMILY);
        yea_nay (c, rcb_highlight, nits, STATS HIGHLIGHT, STATS DONT HIGHLIGHT);
        yea_nay (c, rcb_historical_form, nits, STATS HISTFORM, STATS DONT HISTFORM);
        yea_nay (c, rcb_id, nits, STATS ID, STATS DONT ID);
        yea_nay (c, rcb_itemid, nits, STATS ITEMID, STATS DONT ITEMID);
        yea_nay (c, rcb_keyframe, nits, STATS KEYFRAME, STATS DONT KEYFRAME);
        yea_nay (c, rcb_layer, nits, STATS LAYER, STATS DONT LAYER);
        yea_nay (c, rcb_meta, nits, STATS META, STATS DONT META);
        yea_nay (c, rcb_ontology, nits, STATS ONT, STATS DONT ONT);
        yea_nay (c, rcb_ornament, nits, STATS ORNAMENT, STATS DONT ORNAMENT);
        yea_nay (c, rcb_page, nits, STATS PAGE, STATS DONT PAGE);
        yea_nay (c, rcb_page_name, nits, STATS PAGE_NAME, STATS DONT PAGE_NAME);
        yea_nay (c, rcb_palette, nits, STATS PALETTE, STATS DONT PALETTE);
        yea_nay (c, rcb_property, nits, STATS PROPER, STATS DONT PROPER);
        yea_nay (c, rcb_reference, nits, STATS REFERENCE, STATS DONT REFERENCE);
        yea_nay (c, rcb_region, nits, STATS REGION, STATS DONT REGION);
        yea_nay (c, rcb_scroll_animation, nits, STATS SCROLL_ANIM, STATS DONT SCROLL_ANIM);
        yea_nay (c, rcb_statement, nits, STATS STATEMENT, STATS DONT STATEMENT);
        yea_nay (c, rcb_styleset, nits, STATS STYLESET, STATS DONT STYLESET);
        yea_nay (c, rcb_stylistic, nits, STATS STYLISTIC, STATS DONT STYLISTIC);
        yea_nay (c, rcb_summary, nits, STATS SUMMARY, STATS DONT SUMMARY);
        yea_nay (c, rcb_swash, nits, STATS SWASH, STATS DONT SWASH);
        yea_nay (c, rcb_version, nits, STATS VERSION, STATS DONT VERSION);
        yea_nay (c, rcb_view, nits, STATS VIEW, STATS DONT VIEW);

        if (var_.count (SVG VERSION))
        {   ::std::string ver (var_ [SVG VERSION].as < ::std::string > ());
            {   const ::std::string::size_type slash = ver.find ('/');
                ::std::string ps;
                if (slash != ::std::string::npos)
                {   ps = ver.substr (slash+1);
                    ver = ver.substr (0, slash); }
                const ::std::string::size_type pos = ver.find ('.');
                if (pos == ::std::string::npos) c.svg_version (lexical < int > :: cast (ver), 0);
                else if (pos == ver.length () - 1) c.svg_version (lexical < int > :: cast (ver.substr (0, pos)), 0);
                else if (pos == 0) c.svg_version (sv_none);
                else c.svg_version (lexical < int > :: cast (ver.substr (0, pos)), lexical < int > :: cast (ver.substr (pos+1)));
                if ((slash != ::std::string::npos) && (c.svg_version () == sv_1_2_tiny) && compare_no_case (ps, "full")) c.svg_version (sv_1_2_full);
                if (c.svg_version () == sv_none)
                    nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid SVG version");
                else c.svg (ver); } }

        if (var_.count (VALIDATION ATTRIB))
        {  const vstr_t& v = var_ [VALIDATION ATTRIB].as < vstr_t > (); add_attributes (nits, v); c.attrib (v); }
        if (var_.count (VALIDATION CHARSET)) vvextend < t_charset > (c, VALIDATION CHARSET);
        if (var_.count (VALIDATION CLASS)) vvextend < t_class > (c, VALIDATION CLASS);
        if (var_.count (VALIDATION COLOR) || var_.count (VALIDATION COLOUR)) vvextend < t_fixedcolour > (c, VALIDATION COLOR, VALIDATION COLOUR);
        if (var_.count (VALIDATION COUNTRY))  vvextend < t_country > (c, VALIDATION COUNTRY);
        if (var_.count (VALIDATION CURRENCY)) vvextend < t_currency > (c, VALIDATION CURRENCY);
        if (var_.count (VALIDATION DINGBATARG)) vvextend < t_dingbat > (c, VALIDATION DINGBATARG);
        if (var_.count (VALIDATION ELEMENT))
          { const vstr_t& v = var_ [VALIDATION ELEMENT].as < vstr_t > (); add_elements (nits, v); c.elem (v); }
        if (var_.count (VALIDATION ELEMATTR))
          { const vstr_t& v = var_ [VALIDATION ELEMATTR].as < vstr_t > (); add_element_attributes (nits, v); c.elem_attrib (v); }
        if (var_.count (VALIDATION EXTENSION)) vvextend < t_format > (c, VALIDATION EXTENSION);
        if (var_.count (VALIDATION FF)) vvextend < t_css_font_feature > (c, VALIDATION FF);
        if (var_.count (VALIDATION FV)) vvextend < t_css_font_variation > (c, VALIDATION FV);
        if (var_.count (VALIDATION HTTPEQUIV)) vvextend < t_httpequiv > (c, VALIDATION HTTPEQUIV);
        if (var_.count (VALIDATION LANG)) vvextend < t_lang > (c, VALIDATION LANG);
        if (var_.count (VALIDATION REL)) vvextend < t_rel > (c, VALIDATION REL);
        if (var_.count (VALIDATION METANAME)) vvextend < t_metaname > (c, VALIDATION METANAME);
        if (var_.count (VALIDATION MIMETYPE)) vvextend < t_mime > (c, VALIDATION MIMETYPE);
        if (var_.count (VALIDATION SGML)) vvextend < t_sgml > (c, VALIDATION SGML);

        if (var_.count (VTT EXTENSION)) c.vtt_extension (var_ [VTT EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back (VTT_EXT); c.vtt_extension (ex); }
        yea_nay (c, &context_t::load_vtt, nits, VTT VERIFY, VTT DONT VERIFY);

#define TEST_VAR(XX) if (var_.count (VALIDATION #XX)) vvextend < t_##XX > (c, VALIDATION #XX);
        TEST_VAR (accrual_method);
        TEST_VAR (accrual_periodicity);
        TEST_VAR (accrual_policy);
        TEST_VAR (action);
        TEST_VAR (advar);
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
        TEST_VAR (robotic);
        TEST_VAR (rsl_disclaimer);
        TEST_VAR (rsl_payment);
        TEST_VAR (rsl_usage);
        TEST_VAR (rsl_user);
        TEST_VAR (rsl_warranty);
        TEST_VAR (rss_version);
        TEST_VAR (rules);
        TEST_VAR (sandbox);
        TEST_VAR (security);
        TEST_VAR (shape7);
        TEST_VAR (shape_rendering);
        TEST_VAR (ssi);
        TEST_VAR (ssi_comparison);
        TEST_VAR (ssi_config);
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
        TEST_VAR (tld);
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
    var_.clear ();
    env_var_.clear (); }

template < e_type TT > void options::vvextend (context_t& c, const char* const arg)
{   if (var_.count (arg))
    {   const vstr_t& vv (var_ [arg].as < vstr_t > ());
        type_master < TT > :: extend (vv);
        c.vvext (TT, vv); } }

template < e_type TT > void options::vvextend (context_t& c, const char* const a1, const char* const a2)
{   vstr_t vs;
    if (var_.count (a1)) vs = var_ [a1].as < vstr_t > ();
    if (var_.count (a2)) for (auto v : var_ [a2].as < vstr_t > ()) vs.push_back (v);
    type_master < TT > :: extend (vs);
    c.vvext (TT, vs); }


void pvs (::std::ostringstream& res, const vstr_t& data)
{   for (auto i : data)
        res << i << " "; }

::std::string pvs (const vstr_t& data)
{   ::std::string res;
    for (auto i : data)
        res += i + " ";
    return res; }

::std::string gubbins_config (const char* section, int& count, const char* variable)
{   ::std::string res;
    if (count++ == 0)
    {   ::std::string sect (section);
        const ::std::string::size_type pos = sect.length ();
        PRESUME (pos > 0, __FILE__, __LINE__);
        if (sect.at (pos - 1) == '.') sect = sect.substr (0, pos-1);
        res += "["; 
        res += sect;
        res += "]\n"; }
    res += variable;
    res += "=";
    return res; }

::std::string gubbins_switch (const char* section, int& , const char* variable)
{   ::std::string res ("--");
    res += section;
    const ::std::string sect (section);
    if (! sect.empty ())
    {   const ::std::string::size_type pos = sect.length ();
        if (sect.at (pos - 1) != '.') res += "."; }
    res += variable;
    res += " ";
    return res; }

::std::string gubbins (const e_gui_report gr, const char* section, int& count, const char* variable)
{   VERIFY_NOT_NULL (section, __FILE__, __LINE__);
    VERIFY_NOT_NULL (variable, __FILE__, __LINE__);
    switch (gr)
    {   case gr_config : return gubbins_config (section, count, variable);
        case gr_summary : return ::std::string ();
        case gr_switches : return gubbins_switch (section, count, variable);
        default : GRACEFUL_CRASH (__FILE__, __LINE__); } }

::std::string report_value (const e_gui_report gr, const char* section, int& count, const char* variable, const ::std::string& val)
{   if (gr == gr_switches) return gubbins (gr, section, count, variable) + enquote (val) + " ";
    return gubbins (gr, section, count, variable) + val + "\n"; }

::std::string report_value (const e_gui_report gr, const char* section, int& count, const char* variable)
{   if (gr == gr_switches) return gubbins (gr, section, count, variable) + " ";
    return gubbins (gr, section, count, variable) + "\n"; }

template < class T > void options::report_variable (const e_gui_report gr, ::std::ostringstream& res, const char* wot, const char* section, int& count, const char* variable) const
{   if (var_.count (wot)) try
    {   res << report_value (gr, section, count, variable, var_ [wot].as < ::std::string > ()); }
    catch (...)
    {   context.os () -> err (section, wot, " is incompatible with ::std::string\n"); } }

template < > void options::report_variable < vbp_t > (const e_gui_report gr, ::std::ostringstream& res, const char* wot, const char* section, int& count, const char* variable) const
{   if (var_.count (wot)) try
    {   vbp_t vs = var_ [wot].as < vbp_t > ();
        for (auto s : vs)
            res << report_value (gr, section, count, variable, s.string ()); }
    catch (...)
    {   context.os () -> err (section, wot, " is no vstr_t\n"); } }

template < > void options::report_variable < vstr_t > (const e_gui_report gr, ::std::ostringstream& res, const char* wot, const char* section, int& count, const char* variable) const
{   if (var_.count (wot)) try
    {   vstr_t vs = var_ [wot].as < vstr_t > ();
        for (auto s : vs)
            res << report_value (gr, section, count, variable, s); }
    catch (...)
    {   context.os () -> err (section, wot, " is no vstr_t\n"); } }

template < > void options::report_variable < bool > (const e_gui_report gr, ::std::ostringstream& res, const char* wot, const char* section, int& count, const char* variable) const
{   if (var_.count (wot)) try
    {   if (var_ [wot].as < bool > ())
            res << report_value (gr, section, count, variable); }
    catch (...)
    {   context.os () -> err (section, wot, " is no bool\n"); } }

void options::report_bool (const e_gui_report gr, ::std::ostringstream& res, const char* yay, const char* nay, const char* section, int& count, const char* ja, const char* nein) const
{   report_variable < bool > (gr, res, yay, section, count, ja);   
    report_variable < bool > (gr, res, nay, section, count, nein); }

#define RB(GR,RES,SECT,VAR,COUNT) report_bool (GR, RES, SECT VAR, SECT DONT VAR, SECT, COUNT, VAR, DONT VAR)
#define RBX(GR,RES,SECT,VAR,VAR2,COUNT) report_bool (GR, RES, SECT VAR, SECT VAR2, SECT, COUNT, VAR, VAR2)
#define RG(GR,RES,TYPE,SECT,VAR,COUNT) report_variable < TYPE > (GR, RES, SECT VAR, SECT, COUNT, VAR)
#define RI(GR,RES,SECT,VAR,DEF,COUNT) \
    if (var_.count (SECT VAR)) \
        if (var_ [SECT VAR].as < ::std::string > () != DEF) \
            RG (GR, RES, ::std::string, SECT, VAR, COUNT);
#define RII(GR,RES,SECT,VAR,DEF,COUNT) \
    if (var_.count (SECT VAR)) \
        if (var_ [SECT VAR].as < int > () != DEF) \
            RG (GR, RES, int, SECT, VAR, COUNT);
#define RP(GR,RES,SECT,VAR,COUNT) \
    if (var_.count (SECT VAR)) \
        RG (GR, RES, ::std::string, SECT, "*****", COUNT);
#define REOS(COUNT,RES) if (COUNT > 0) RES << "\n";

::std::string options::report (const e_gui_report gr, const bool file, const bool wibble) const
{   ::std::ostringstream res;
#ifndef EXPAND_TEST
    if (context.test ()) return res.str ();
#endif // EXPAND_TEST

    int atomic = 0, corpus = 0, css = 0, env = 0, general = 0, html = 0,
        jsonld = 0, lynx = 0, math = 0, mf = 0, nitty = 0, ontology = 0, output = 0,
        rsl = 0, rss = 0, shadow = 0, site = 0, ssc = 0, ssi = 0, stats = 0, svg = 0,
        validate = 0, vtt = 0;
#ifndef NOSPELL
    int spell = 0;
#endif // NOSPELL

    if (file)
        res << report_value (gr, PROG, ssc, VERSION, VERSION_STRING)
            << report_value (gr, PROG, ssc, OPTBOOST, BOOST_LIB_VERSION)
            << report_value (gr, PROG, ssc, OPTCOMP, COMPNAME)
#ifdef DEBUG
            << report_value (gr, PROG, ssc, OPTDEBUG, "yes")
#else // DEBUG
            << report_value (gr, PROG, ssc, OPTDEBUG, "no")
#endif // DEBUG
#ifdef FUDDY
            << report_value (gr, PROG, ssc, OPTFUDDY, "yes")
#else // FUDDY
            << report_value (gr, PROG, ssc, OPTFUDDY, "no")
#endif // FUDDY
#ifdef WX
            << report_value (gr, PROG, ssc, OPTGUI, "yes")
#else // WX
            << report_value (gr, PROG, ssc, OPTGUI, "no")
#endif // WX
#ifndef NOICU
            << report_value (gr, PROG, ssc, OPTICU, U_ICU_VERSION)
#endif // NOICU
#ifdef JSNIC
            << report_value (gr, PROG, ssc, OPTJSON, "yes")
#else // JSNIC
            << report_value (gr, PROG, ssc, OPTJSON, "no")
#endif // JSNIC
#ifdef NPS_GEN
            << report_value (gr, PROG, ssc, OPTNPS, "yes")
#else // NPS_GEN
            << report_value (gr, PROG, ssc, OPTNPS, "no")
#endif // NPS_GEN
            << report_value (gr, PROG, ssc, OPTPROC, "x" PROCSIZE)
            << report_value (gr, PROG, ssc, OPTOS, TARGET_OS)
#ifdef SPELT
            << report_value (gr, PROG, ssc, OPTSPELL, "yes")
#else // SPELT
            << report_value (gr, PROG, ssc, OPTSPELL, "no")
#endif // SPELT
            ;
    else if (wibble)
    {   ::std::ostringstream e;
        if (env_var_.count (ENV_CONFIG)) e << ENV_CONFIG ": " << env_var_ [ENV_CONFIG].as < ::std::string > () << "\n";
        if (env_var_.count (ENV_ARGS)) e << ENV_ARGS ": " << env_var_ [ENV_ARGS].as < ::std::string > () << "\n";

        if (env_var_.count (QUERY_STRING))
        {   if (env_var_.count (SERVER_SOFTWARE)) e << SERVER_SOFTWARE ": " << env_var_ [SERVER_SOFTWARE].as < ::std::string > () << "\n";
            if (env_var_.count (SERVER_NAME)) e << SERVER_NAME ": " << env_var_ [SERVER_NAME].as < ::std::string > () << "\n";
            if (env_var_.count (GATEWAY_INTERFACE)) e << GATEWAY_INTERFACE ": " << env_var_ [GATEWAY_INTERFACE].as < ::std::string > () << "\n";
            if (env_var_.count (SERVER_PROTOCOL)) e << SERVER_PROTOCOL ": " << env_var_ [SERVER_PROTOCOL].as < ::std::string > () << "\n";
            if (env_var_.count (SERVER_PORT)) e << SERVER_PORT ": " << env_var_ [SERVER_PORT].as < ::std::string > () << "\n";
            if (env_var_.count (REQUEST_METHOD)) e << REQUEST_METHOD ": " << env_var_ [REQUEST_METHOD].as < ::std::string > () << "\n";
            if (env_var_.count (HTTP_ACCEPT)) e << HTTP_ACCEPT ": " << env_var_ [HTTP_ACCEPT].as < ::std::string > () << "\n";
            if (env_var_.count (PATH_INFO)) e << PATH_INFO ": " << env_var_ [PATH_INFO].as < ::std::string > () << "\n";
            if (env_var_.count (PATH_TRANSLATED)) e << PATH_TRANSLATED ": " << env_var_ [PATH_TRANSLATED].as < ::std::string > () << "\n";
            if (env_var_.count (SCRIPT_NAME)) e << SCRIPT_NAME ": " << env_var_ [SCRIPT_NAME].as < ::std::string > () << "\n";
            if (env_var_.count (REMOTE_HOST)) e << REMOTE_HOST ": " << env_var_ [REMOTE_HOST].as < ::std::string > () << "\n";
            if (env_var_.count (REMOTE_ADDR)) e << REMOTE_ADDR ": " << env_var_ [REMOTE_ADDR].as < ::std::string > () << "\n";
            if (env_var_.count (REMOTE_USER)) e << REMOTE_USER ": " << env_var_ [REMOTE_USER].as < ::std::string > () << "\n";
            if (env_var_.count (AUTH_TYPE)) e << AUTH_TYPE ": " << env_var_ [AUTH_TYPE].as < ::std::string > () << "\n";
            if (env_var_.count (CONTENT_TYPE)) e << CONTENT_TYPE ": " << env_var_ [CONTENT_TYPE].as < ::std::string > () << "\n";
            if (env_var_.count (CONTENT_LENGTH)) e << CONTENT_LENGTH ": " << env_var_ [CONTENT_LENGTH].as < ::std::string > () << "\n";

            ::std::string qs (env_var_ [QUERY_STRING].as < ::std::string > ());
            e << QUERY_STRING ": " << qs << "\n            : " << query_to_switches (qs) << "\n"; }

        const ::std::string x (e.str ());
        if (! x.empty ()) res << "\n" START_OF_SUBSECTION " Environment:\n" << x << "\n";
        res << "\n" START_OF_SUBSECTION " Arguments:\n";

        // these should NOT throw (the var_s ARE bool), but they do
        try { if (var_ [ASK].as < bool > ()) res << ASK "\n"; } catch (...) { }
        try { if (var_ [DONT ASK].as < bool > ()) res << DONT ASK "\n"; } catch (...) { }

        try { if (var_ [HELP].as < bool > ()) res << HELP "\n"; } catch (...) { }
        try { if (var_ [VERSION].as < bool > ()) res << VERSION "\n"; } catch (...) { } }

    RG (gr, res, vstr_t, ATOMIC, EXTENSION, atomic);
    RB (gr, res, ATOMIC, VERIFY, atomic);
    REOS (atomic, res);

    RB (gr, res, CORPUS, ARTICLE, corpus);
    RB (gr, res, CORPUS, BODY, corpus);
    RB (gr, res, CORPUS, MAIN, corpus);
    RG (gr, res, ::std::string, CORPUS, OUTPUT_, corpus);
    REOS (corpus, res);

    RG (gr, res, int, CSS, ADJUST, css);
    RG (gr, res, int, CSS, ADVLAY, css);
    RG (gr, res, int, CSS, ANCHOR, css);
    RG (gr, res, int, CSS, ANCHOR_POS, css);
    RG (gr, res, int, CSS, ANIMATION, css);
    RG (gr, res, int, CSS, BACKGROUND, css);
    RG (gr, res, int, CSS, BORDER, css);
    RG (gr, res, int, CSS, BOX_ALIGN, css);
    RG (gr, res, int, CSS, BOX_MODEL, css);
    RG (gr, res, int, CSS, BOX_SIZING, css);
    RG (gr, res, int, CSS, CASCADE, css);
    RG (gr, res, int, CSS, COLOUR, css);
    RG (gr, res, int, CSS, COMPOSITING, css);
    RG (gr, res, int, CSS, COND_RULE, css);
    RG (gr, res, int, CSS, CS, css);
    RG (gr, res, int, CSS, CONTAIN, css);
    RG (gr, res, int, CSS, CON_TENT, css);
    RG (gr, res, int, CSS, CUSTOM, css);
    RG (gr, res, int, CSS, DEVICE, css);
    RG (gr, res, int, CSS, DISPLAY, css);
    RG (gr, res, int, CSS, ENVIRONMENT, css);
    RG (gr, res, int, CSS, EASE, css);
    RG (gr, res, int, CSS, EXCLUDE, css);
    RG (gr, res, vstr_t, CSS, EXTENSION, css);
    RG (gr, res, int, CSS, FBL, css);
    RG (gr, res, int, CSS, FILL, css);
    RG (gr, res, int, CSS, FILTER, css);
    RG (gr, res, int, CSS, FLOAT, css);
    RG (gr, res, int, CSS, FONT, css);
    RG (gr, res, int, CSS, FRAG, css);
    RG (gr, res, int, CSS, GRID, css);
    RG (gr, res, int, CSS, HDR, css);
    RG (gr, res, int, CSS, HIGHLIGHT, css);
    RG (gr, res, int, CSS, HYPERLINK, css);
    RG (gr, res, int, CSS, IMAGE, css);
    RG (gr, res, int, CSS, INLINE, css);
    RG (gr, res, int, CSS, LIST, css);
    RG (gr, res, int, CSS, LINE_GRID, css);
    RG (gr, res, int, CSS, LOGIC, css);
    RG (gr, res, int, CSS, MARQUEE, css);
    RG (gr, res, int, CSS, MASKING, css);
    RG (gr, res, int, CSS, MEDIA, css);
    RG (gr, res, int, CSS, MIXIN, css);
    RB (gr, res, CSS, MOBILE, css);
    RG (gr, res, int, CSS, MOTION, css);
    RG (gr, res, int, CSS, MULTI_COLUMN, css);
    RG (gr, res, int, CSS, NAMESPACE, css);
    RG (gr, res, int, CSS, NES, css);
    RG (gr, res, int, CSS, NESTING, css);
    RG (gr, res, int, CSS, OVERFLOH, css);
    RG (gr, res, int, CSS, OVERSCROLL, css);
    RG (gr, res, int, CSS, PAGE, css);
    RG (gr, res, int, CSS, POSITION, css);
    RG (gr, res, int, CSS, PRESENT, css);      
    RB (gr, res, CSS, PRINT, css);
    RG (gr, res, int, CSS, PSEUDO, css);
    RG (gr, res, int, CSS, REGION, css);
    RG (gr, res, int, CSS, RHYTHM, css);
    RG (gr, res, int, CSS, ROUND, css);
    RG (gr, res, int, CSS, RUBY, css);
    RG (gr, res, int, CSS, SCOPE, css);
    RG (gr, res, int, CSS, SCROLLBAR, css);
    RG (gr, res, int, CSS, SDA, css);
    RG (gr, res, int, CSS, SELECTOR, css);
    RG (gr, res, int, CSS, SP, css);
    RG (gr, res, int, CSS, SHAPE, css);
    RG (gr, res, int, CSS, SPATIAL, css);
    RG (gr, res, int, CSS, SPEECH, css);
    RG (gr, res, int, CSS, SNAP, css);
    RG (gr, res, int, CSS, SNAP_POINTS, css);
    RG (gr, res, int, CSS, STYLE, css);
    RG (gr, res, int, CSS, SYNTAX, css);
    RG (gr, res, int, CSS, TABLE, css);
    RG (gr, res, int, CSS, TEXT_ARG, css);
    RG (gr, res, int, CSS, TEXT_DEC, css);
    RG (gr, res, int, CSS, TRANSFORM, css);
    RG (gr, res, int, CSS, TRANSITION, css);
    RB (gr, res, CSS, TV, css);
    RG (gr, res, int, CSS, UI, css);
    RG (gr, res, int, CSS, VAL, css);
    RB (gr, res, CSS, VERIFY, css);
    RG (gr, res, ::std::string, CSS, VERSION, css);
    RG (gr, res, int, CSS, VIEW, css);
    RG (gr, res, int, CSS, VIEWPORT, css);
    RG (gr, res, int, CSS, WRITING, css);
    RG (gr, res, int, CSS, WC, css);
    REOS (css, res);

    if (var_.count (ENVIRONMENT QUERY_STRING))
    {   RG (gr, res, ::std::string, ENVIRONMENT, AUTH_TYPE, env);
        RG (gr, res, ::std::string, ENVIRONMENT, CONTENT_TYPE, env);
        RG (gr, res, ::std::string, ENVIRONMENT, CONTENT_LENGTH, env);
        RG (gr, res, ::std::string, ENVIRONMENT, GATEWAY_INTERFACE, env);
        RG (gr, res, ::std::string, ENVIRONMENT, HTTP_ACCEPT, env);
        RG (gr, res, ::std::string, ENVIRONMENT, PATH_INFO, env);
        RG (gr, res, ::std::string, ENVIRONMENT, PATH_TRANSLATED, env);
        if (file) RG (gr, res, ::std::string, ENVIRONMENT, QUERY_STRING, env);
        RG (gr, res, ::std::string, ENVIRONMENT, REMOTE_ADDR, env);
        RG (gr, res, ::std::string, ENVIRONMENT, REMOTE_HOST, env);
        RG (gr, res, ::std::string, ENVIRONMENT, REMOTE_USER, env);
        RG (gr, res, ::std::string, ENVIRONMENT, REQUEST_METHOD, env);
        RG (gr, res, ::std::string, ENVIRONMENT, SCRIPT_NAME, env);
        RG (gr, res, ::std::string, ENVIRONMENT, SERVER_NAME, env);
        RG (gr, res, ::std::string, ENVIRONMENT, SERVER_PORT, env);
        RG (gr, res, ::std::string, ENVIRONMENT, SERVER_PROTOCOL, env);
        RG (gr, res, ::std::string, ENVIRONMENT, SERVER_SOFTWARE, env);
        if (! file)
        {  ::std::string qs (var_ [ENVIRONMENT QUERY_STRING].as < ::std::string > ());
            res << ENVIRONMENT QUERY_STRING ": " << qs << "\n            : " << query_to_switches (qs) << "\n"; }
        REOS (env, res); }

    RB (gr, res, GENERAL, ADS, general);
    RB (gr, res, GENERAL, CGI, general);
    RB (gr, res, GENERAL, CLASS, general);
    RB (gr, res, GENERAL, CLASSIC, general);
    RB (gr, res, GENERAL, COMMS, general);
    RI (gr, res, GENERAL, DATAPATH, def_path, general);
    RG (gr, res, int, GENERAL, DEFTHRD, general);
    RG (gr, res, vstr_t, GENERAL, ENVIRONMENT, general);
    RG (gr, res, vstr_t, GENERAL, EXCLUDE, general);
    RI (gr, res, GENERAL, FICHIER, def_persisted, general);
    RB (gr, res, GENERAL, INFO, general);
    RG (gr, res, ::std::string, GENERAL, HELPSITE, general);
    RG (gr, res, long, GENERAL, LINE_LENGTH, general);
    RI (gr, res, GENERAL, MACROEND, def_macroend, general);
    RI (gr, res, GENERAL, MACROSTART, def_macrostart, general);
    RG (gr, res, int, GENERAL, MAXFILESIZE, general);
    RB (gr, res, GENERAL, PROGRESS, general);
    RB (gr, res, GENERAL, RDFA, general);
    RB (gr, res, GENERAL, ROBOTS, general);
    RB (gr, res, GENERAL, RPT, general);
    RB (gr, res, GENERAL, SECURITY, general);
    RG (gr, res, vreg_t, GENERAL, SILENCE, general);
    RB (gr, res, GENERAL, SPEC, general);
    RB (gr, res, GENERAL, TEST, general);
#ifndef NO_FRED
    RG (gr, res, int, GENERAL, THREAD, general);
#endif // NO_FRED
    RB (gr, res, GENERAL, UPDATE, general);
    RG (gr, res, vstr_t, GENERAL, URL_VAR, general);
    RB (gr, res, GENERAL, VCS, general);
    RB (gr, res, GENERAL, YGGDRISIL, general);
    REOS (general, res);

    RG (gr, res, ::std::string, HTML, ANALYSIS, html);
    RB (gr, res, HTML, ARIA, html);
    RB (gr, res, HTML, CHROME, html);
    RG (gr, res, vstr_t, HTML, CUSTOM, html);
    RB (gr, res, HTML, EFFICIENT, html);
    RB (gr, res, HTML, FORCE, html);
    RB (gr, res, HTML, IE, html);
    RG (gr, res, vstr_t, HTML, IGNORED, html);
    RG (gr, res, ::std::string, HTML, LANG, html);
    RB (gr, res, HTML, MOZILLA, html);
    RB (gr, res, HTML, NETSCAPE, html);
    RB (gr, res, HTML, OPERA, html);
    RB (gr, res, HTML, REL, html);
    RB (gr, res, HTML, RFC1867, html);
    RB (gr, res, HTML, RFC1942, html);
    RB (gr, res, HTML, RFC1980, html);
    RB (gr, res, HTML, RFC2070, html);
    RB (gr, res, HTML, RUBY, html);
    RB (gr, res, HTML, SAFARI, html);
    RB (gr, res, HTML, SLOVEN, html);
    RG (gr, res, ::std::string, HTML, SNIPPET, html);
    RB (gr, res, HTML, TAGS, html);
    RII (gr, res, HTML, TITLE, def_htmltitle, html);
    RG (gr, res, ::std::string, HTML, VERSION, html);
    RB (gr, res, HTML, WXARG, html);
    RG (gr, res, ::std::string, HTML, WX_SNIPPET, html);
    REOS (html, res);

    RG (gr, res, vstr_t, JSONLD, EXTENSION, jsonld);
    RG (gr, res, vstr_t, JSONLD, ONTOLOGY_, jsonld);
    RB (gr, res, JSONLD, PRETTY, jsonld);
    RB (gr, res, JSONLD, VERIFY, jsonld);
    RG (gr, res, ::std::string, JSONLD, VERSION, jsonld);
    REOS (jsonld, res);

    RB (gr, res, LINKS, CHECK, lynx);
    RB (gr, res, LINKS, EXAMPLE, lynx);
    RB (gr, res, LINKS, EXTERNAL, lynx);
    RB (gr, res, LINKS, FORWARD, lynx);
    RG (gr, res, vstr_t, LINKS, IGNORED, lynx);
    RB (gr, res, LINKS, LOCAL, lynx);
    RB (gr, res, LINKS, ONCE, lynx);
    RG (gr, res, vstr_t, LINKS, PRETEND, lynx);
    RG (gr, res, vstr_t, LINKS, REPORT, lynx);
    RG (gr, res, vstr_t, LINKS, REQUIRED, site);
    RB (gr, res, LINKS, REVOKE, lynx);
    RB (gr, res, LINKS, SPECIAL, lynx);
    RB (gr, res, LINKS, XLINK, lynx);
    REOS (lynx, res);

    RG (gr, res, int, MATH, VERSION, math);
    REOS (math, res);

    RB (gr, res, MF, EXPORT, mf);
    RB (gr, res, MF, PRETTY, mf);
    RB (gr, res, MF, VERIFY, mf);
    RG (gr, res, int, MF, VERSION, mf);
    REOS (mf, res);

    RG (gr, res, vstr_t, NITS, ABHORRENT, nitty);
    RG (gr, res, ::std::string, NITS, CACHE, nitty);
    RG (gr, res, vstr_t, NITS, CATASTROPHE, nitty);
    RG (gr, res, vstr_t, NITS, COMMENT, nitty);
    RG (gr, res, vstr_t, NITS, DBG, nitty);
    RG (gr, res, vstr_t, NITS, WHOOPS, nitty);
    RG (gr, res, ::std::string, NITS, ERROREXIT, nitty);
    RB (gr, res, NITS, EXPAND, nitty);
    RB (gr, res, NITS, EXTRA, nitty);
    RG (gr, res, vstr_t, NITS, INFO, nitty);
    RB (gr, res, NITS, NIDS, nitty);
    RG (gr, res, vstr_t, NITS, SILENCE, nitty);
    RB (gr, res, NITS, SPEC, nitty);
    RB (gr, res, NITS, UNIQUE, nitty);
    RG (gr, res, ::std::string, NITS, VERBOSE, nitty);
    RG (gr, res, vstr_t, NITS, WARNING, nitty);
    RB (gr, res, NITS, WATCH, nitty);
    RG (gr, res, ::std::string, NITS, XXX, nitty);
    REOS (nitty, res);

    RB (gr, res, ONTOLOGY, EXPORT, ontology);
    RB (gr, res, ONTOLOGY, PRETTY, ontology);
    RB (gr, res, ONTOLOGY, VERIFY, ontology);
    RG (gr, res, ::std::string, ONTOLOGY, ROOT, ontology);
    RG (gr, res, vstr_t, ONTOLOGY, VIRTUAL, ontology);
    for (int i = s_none + 1; i < s_error; ++i)
    {   const e_ontology es = static_cast < e_ontology > (i);
        if (is_faux_schema (es)) continue;
        if (get_ontology_version_count (es) < 2) continue;
        const ::std::string naam (ontology_names.get (es, ONTOLOGY_NAME));
        ::std::string arg (ONTOLOGY);
        arg += naam;
        if (var_.count (arg))
            res << report_value (gr, ONTOLOGY, ontology, naam.c_str (), var_ [arg].as < ::std::string > ()); }
    REOS (ontology, res);

    RBX (gr, res, OUTPUT, APATH, RPATH, output);
    RG (gr, res, ::std::string, OUTPUT, ACCOUNT, output);
    RG (gr, res, ::std::string, OUTPUT, BACK, output);
    RG (gr, res, ::std::string, OUTPUT, BUILD, output);
    RG (gr, res, vstr_t, OUTPUT, DESCRIPTION, output);
    RG (gr, res, ::std::string, OUTPUT, FORMAT, output);
    RG (gr, res, ::std::string, OUTPUT, HOME, output);
    RG (gr, res, ::std::string, OUTPUT, OVERRIDE, output);
#ifdef SIGNING
    RG (gr, res, ::std::string, OUTPUT, PASSWORD, output);
    RG (gr, res, ::std::string, OUTPUT, PRIVATE, output);
    RG (gr, res, ::std::string, OUTPUT, PUBLIC, output);
#endif // SIGNING
    RB (gr, res, OUTPUT, RPATH, output);
#ifdef SIGNING
    RB (gr, res, OUTPUT, SIGN, output);
    RG (gr, res, ::std::string, OUTPUT, SIGNATURE, output);
    RG (gr, res, ::std::string, OUTPUT, STYLESHEET, output);
#endif // SIGNING
    RG (gr, res, ::std::string, OUTPUT, TIME, output);
    RG (gr, res, ::std::string, OUTPUT, USERNAME, output);
    RB (gr, res, OUTPUT, VERIFY, output);
    REOS (output, res);

    RG (gr, res, vstr_t, RSL, EXTENSION, rsl);
    RB (gr, res, RSL, VERIFY, rsl);
    REOS (rsl, res);

    RG (gr, res, vstr_t, RSS, EXTENSION, rss);
    RB (gr, res, RSS, VERIFY, rss);
    RG (gr, res, ::std::string, RSS, VERSION, rss);
    REOS (rss, res);

    RB (gr, res, SHADOW, CHANGED, shadow);
    RB (gr, res, SHADOW, COMMENT, shadow);
    RG (gr, res, ::std::string, SHADOW, COPY, shadow);
    RB (gr, res, SHADOW, ENABLE, shadow);
    RG (gr, res, ::std::string, SHADOW, FICHIER, shadow);
    RG (gr, res, vstr_t, SHADOW, IGNORED, shadow);
    RB (gr, res, SHADOW, INFO, shadow);
    RG (gr, res, ::std::string, SHADOW, MSG, shadow);
    RG (gr, res, vstr_t, SHADOW, NAUGHTY, shadow);
    RG (gr, res, vstr_t, SHADOW, NICE, shadow);
    RG (gr, res, vstr_t, SHADOW, NOTE, shadow);
    RG (gr, res, vstr_t, SHADOW, REPLACE, shadow);
    RG (gr, res, ::std::string, SHADOW, ROOT, shadow);
    RB (gr, res, SHADOW, SPACING, shadow);
    RB (gr, res, SHADOW, SSI_, shadow);
    RB (gr, res, SHADOW, UPDATE, shadow);
    RG (gr, res, vstr_t, SHADOW, VIRTUAL, shadow);
    REOS (shadow, res);

    RG (gr, res, ::std::string, WEBSITE, EXTENSION, site);
    RG (gr, res, ::std::string, WEBSITE, INDEX, site);
    RG (gr, res, ::std::string, WEBSITE, ROOT, site);
    RG (gr, res, vstr_t, WEBSITE, SITE, site);
    RG (gr, res, vstr_t, WEBSITE, VIRTUAL, site);
    REOS (site, res);

#ifndef NOSPELL
    RG (gr, res, vstr_t, SPELL, ACCEPT, spell);
    RB (gr, res, SPELL, CASED, spell);
    RB (gr, res, SPELL, CHECK, spell);
    RG (gr, res, vstr_t, SPELL, DICT, spell);
    RB (gr, res, SPELL, ICU, spell);
    RG (gr, res, vstr_t, SPELL, LIST, spell);
    RG (gr, res, ::std::string, SPELL, PATH, spell);
    REOS (spell, res);
#endif // NOSPELL

    RB (gr, res, SSI, VERIFY, ssi);
    RG (gr, res, ::std::string, SSI, DATETIME, ssi);
    RG (gr, res, ::std::string, SSI, DOCARGS, ssi);
    RG (gr, res, ::std::string, SSI, ECHOMSG, ssi);
    RG (gr, res, ::std::string, SSI, ERRMSG, ssi);
    RB (gr, res, SSI, EXECRUN, ssi);
    RG (gr, res, ::std::string, SSI, EXECTEXT, ssi);
    RG (gr, res, ::std::string, SSI, LASTMOD, ssi);
    RG (gr, res, ::std::string, SSI, QUERYSTRING, ssi);
    RG (gr, res, ::std::string, SSI, TIMEFMT, ssi);
    RG (gr, res, ::std::string, SSI, USERNAME, ssi);
    REOS (ssi, res);

    RB (gr, res, STATS, ABBR, stats);
    RB (gr, res, STATS, ALL, stats);
    RB (gr, res, STATS, ANNOTATION, stats);
    RB (gr, res, STATS, ATTRIB, stats);
    RB (gr, res, STATS, CAT, stats);
    RB (gr, res, STATS, CHARVAR, stats);
    RB (gr, res, STATS, CLASS, stats);
    RB (gr, res, STATS, CONNAME, stats);
    RB (gr, res, STATS, COUSTYLE, stats);
    RB (gr, res, STATS, CSSPROP, stats);
    RB (gr, res, STATS, CUSTMED, stats);
    RB (gr, res, STATS, CUSTPROP, stats);
    RB (gr, res, STATS, DFN, stats);
    RB (gr, res, STATS, DTDD, stats);
    RB (gr, res, STATS, ELEMENT, stats);
    RB (gr, res, STATS, WHOOPS, stats);
    RG (gr, res, ::std::string, STATS, EXPORT, stats);
    RB (gr, res, STATS, FICHIER, stats);
    RB (gr, res, STATS, FONT, stats);
    RB (gr, res, STATS, FONT_FAMILY, stats);
    RB (gr, res, STATS, HIGHLIGHT, stats);
    RB (gr, res, STATS, HISTFORM, stats);
    RB (gr, res, STATS, ID, stats);
    RB (gr, res, STATS, ITEMID, stats);
    RB (gr, res, STATS, KEYFRAME, stats);
    RB (gr, res, STATS, LAYER, stats);
    RB (gr, res, STATS, META, stats);
    RB (gr, res, STATS, ONT, stats);
    RB (gr, res, STATS, ORNAMENT, stats);
    RB (gr, res, STATS, PAGE, stats);
    RB (gr, res, STATS, PAGE_NAME, stats);
    RB (gr, res, STATS, PALETTE, stats);
    RB (gr, res, STATS, PROPER, stats);
    RB (gr, res, STATS, REFERENCE, stats);
    RB (gr, res, STATS, REGION, stats);
    RB (gr, res, STATS, SCROLL_ANIM, stats);
    RB (gr, res, STATS, SELECTED, stats);
    RB (gr, res, STATS, STATEMENT, stats);
    RB (gr, res, STATS, STYLESET, stats);
    RB (gr, res, STATS, STYLISTIC, stats);
    RB (gr, res, STATS, SUMMARY, stats);
    RB (gr, res, STATS, SWASH, stats);
    RB (gr, res, STATS, VERSION, stats);
    RB (gr, res, STATS, VIEW, stats);
    REOS (stats, res);

    RG (gr, res, ::std::string, SVG, VERSION, svg);
    REOS (svg, res);

    RG (gr, res, vstr_t, VALIDATION, ATTRIB, validate);
    RG (gr, res, vstr_t, VALIDATION, CHARSET, validate);
    RG (gr, res, vstr_t, VALIDATION, CLASS, validate);
    RG (gr, res, vstr_t, VALIDATION, COLOR, validate);
    RG (gr, res, vstr_t, VALIDATION, COLOUR, validate);
    RG (gr, res, vstr_t, VALIDATION, COUNTRY, validate);
    RG (gr, res, vstr_t, VALIDATION, CURRENCY, validate);
    RG (gr, res, vstr_t, VALIDATION, DINGBATARG, validate);
    RG (gr, res, vstr_t, VALIDATION, ELEMENT, validate);
    RG (gr, res, vstr_t, VALIDATION, ELEMATTR, validate);
    RG (gr, res, vstr_t, VALIDATION, EXTENSION, validate);
    RG (gr, res, vstr_t, VALIDATION, FF, validate);
    RG (gr, res, vstr_t, VALIDATION, FV, validate);
    RG (gr, res, vstr_t, VALIDATION, HTTPEQUIV, validate);
    RG (gr, res, vstr_t, VALIDATION, LANG, validate);
    RG (gr, res, int, VALIDATION, MINOR, validate);
    RG (gr, res, vstr_t, VALIDATION, METANAME, validate);
    RB (gr, res, VALIDATION, MICRODATAARG, validate);
    RG (gr, res, vstr_t, VALIDATION, MIMETYPE, validate);
    RG (gr, res, vstr_t, VALIDATION, REL, validate);
    RG (gr, res, vstr_t, VALIDATION, SGML, validate);

#define RPT_VAR(GR,XX) RG (GR, res, vstr_t, VALIDATION, #XX, validate)
    RPT_VAR (gr, accrual_method);
    RPT_VAR (gr, accrual_periodicity);
    RPT_VAR (gr, accrual_policy);
    RPT_VAR (gr, action);
    RPT_VAR (gr, advar);
    RPT_VAR (gr, align3);
    RPT_VAR (gr, alignplus);
    RPT_VAR (gr, as);
    RPT_VAR (gr, as_units);
    RPT_VAR (gr, autocapitalise);
    RPT_VAR (gr, autocomplete);
    RPT_VAR (gr, baselineshift);
    RPT_VAR (gr, citype);
    RPT_VAR (gr, cntype);
    RPT_VAR (gr, composite_operator);
    RPT_VAR (gr, crs_whitebalance);
    RPT_VAR (gr, dcmitype);
    RPT_VAR (gr, decalign);
    RPT_VAR (gr, dingbat);
    RPT_VAR (gr, dir);
    RPT_VAR (gr, display_align);
    RPT_VAR (gr, dominantbaseline);
    RPT_VAR (gr, enterkeyhint);
    RPT_VAR (gr, evt_action);
    RPT_VAR (gr, figalign);
    RPT_VAR (gr, fontname);
    RPT_VAR (gr, halign);
    RPT_VAR (gr, icc);
    RPT_VAR (gr, inputmode);
    RPT_VAR (gr, inputplus);
    RPT_VAR (gr, inputtype);
    RPT_VAR (gr, inputtype3);
    RPT_VAR (gr, inputtype32);
    RPT_VAR (gr, inputtype4);
    RPT_VAR (gr, inputtype5);
    RPT_VAR (gr, kind);
    RPT_VAR (gr, linebreak);
    RPT_VAR (gr, listtype);
    RPT_VAR (gr, mah);
    RPT_VAR (gr, mathalign);
    RPT_VAR (gr, mathvariant);
    RPT_VAR (gr, matrixtype);
    RPT_VAR (gr, media);
    RPT_VAR (gr, mediafeature);
    RPT_VAR (gr, mediakeyword);
    RPT_VAR (gr, method);
    RPT_VAR (gr, mf_identifier);
    RPT_VAR (gr, mf_itemtype);
    RPT_VAR (gr, mf_listing_action);
    RPT_VAR (gr, mf_method);
    RPT_VAR (gr, mf_reviewtype);
    RPT_VAR (gr, musickey);
    RPT_VAR (gr, namedspace);
    RPT_VAR (gr, namespace);
    RPT_VAR (gr, mathnotation);
    RPT_VAR (gr, ogtype);
    RPT_VAR (gr, paintkeyword);
    RPT_VAR (gr, pam_ccv);
    RPT_VAR (gr, pcmm_status);
    RPT_VAR (gr, plusstyle);
    RPT_VAR (gr, pointer_events);
    RPT_VAR (gr, pri_img_colour);
    RPT_VAR (gr, pri_img_technique);
    RPT_VAR (gr, pri_img_viewpoint);
    RPT_VAR (gr, print);
    RPT_VAR (gr, prism_ad_pos);
    RPT_VAR (gr, prism_ad_type);
    RPT_VAR (gr, prism_ag_type);
    RPT_VAR (gr, prism_audience_sector);
    RPT_VAR (gr, prism_ccv);
    RPT_VAR (gr, prism_class);
    RPT_VAR (gr, prism_contenttype);
    RPT_VAR (gr, prism_cvp);
    RPT_VAR (gr, prism_genre);
    RPT_VAR (gr, prism_icv);
    RPT_VAR (gr, prism_pasv);
    RPT_VAR (gr, prism_pcv);
    RPT_VAR (gr, prism_pfv);
    RPT_VAR (gr, prism_ptv);
    RPT_VAR (gr, prism_rcv);
    RPT_VAR (gr, prism_role);
    RPT_VAR (gr, prs_action);
    RPT_VAR (gr, quote_style);
    RPT_VAR (gr, recipe_content);
    RPT_VAR (gr, recipe_course);
    RPT_VAR (gr, recipe_cuisine);
    RPT_VAR (gr, recipe_dietary);
    RPT_VAR (gr, recipe_dish);
    RPT_VAR (gr, recipe_exclusion);
    RPT_VAR (gr, recipe_kit);
    RPT_VAR (gr, recipe_meal);
    RPT_VAR (gr, recipe_method);
    RPT_VAR (gr, recipe_source);
    RPT_VAR (gr, recipe_special);
    RPT_VAR (gr, recipe_time);
    RPT_VAR (gr, referrer);
    RPT_VAR (gr, rendering_in_tents);
    RPT_VAR (gr, robotic);
    RPT_VAR (gr, rsl_disclaimer);
    RPT_VAR (gr, rsl_payment);
    RPT_VAR (gr, rsl_usage);
    RPT_VAR (gr, rsl_user);
    RPT_VAR (gr, rsl_warranty);
    RPT_VAR (gr, rss_version);
    RPT_VAR (gr, rules);
    RPT_VAR (gr, sandbox);
    RPT_VAR (gr, schema);
    RPT_VAR (gr, security);
    RPT_VAR (gr, shape7);
    RPT_VAR (gr, shape_rendering);
    RPT_VAR (gr, ssi);
    RPT_VAR (gr, ssi_comparison);
    RPT_VAR (gr, ssi_config);
    RPT_VAR (gr, ssi_encoding);
    RPT_VAR (gr, ssi_env);
    RPT_VAR (gr, svg_align);
    RPT_VAR (gr, svg_display);
    RPT_VAR (gr, svg_feature);
    RPT_VAR (gr, svg_fontstretch);
    RPT_VAR (gr, svg_fontstretch_ff);
    RPT_VAR (gr, svg_fontstyle);
    RPT_VAR (gr, svg_fontweight);
    RPT_VAR (gr, svg_fontweight_ff);
    RPT_VAR (gr, svg_mode);
    RPT_VAR (gr, svg_overflow);
    RPT_VAR (gr, svg_version);
    RPT_VAR (gr, svg_version_grand);
    RPT_VAR (gr, tableframe);
    RPT_VAR (gr, text_decoration);
    RPT_VAR (gr, text_rendering);
    RPT_VAR (gr, tld);
    RPT_VAR (gr, transform_anim);
    RPT_VAR (gr, transform_fn);
    RPT_VAR (gr, turbulence_type);
    RPT_VAR (gr, unicode_bidi);
    RPT_VAR (gr, vector_effect_2);
    RPT_VAR (gr, xmlns);
    RPT_VAR (gr, xmpdm_audio_channel);
    RPT_VAR (gr, xmpdm_audio_sample);
    RPT_VAR (gr, xmpdm_camera_angle);
    RPT_VAR (gr, xmpdm_camera_move);
    RPT_VAR (gr, xmpdm_pulldown);
    RPT_VAR (gr, xmpdm_shotsize);
    RPT_VAR (gr, xmpdm_stretchmode);
    RPT_VAR (gr, xmpdm_time_format);
    RPT_VAR (gr, xmpdm_time_signature);
    RPT_VAR (gr, xmpdm_video_pixeldepth);

    RG (gr, res, vstr_t, VTT, EXTENSION, vtt);
    RB (gr, res, VTT, VERIFY, vtt);

#undef RPT_VAR
#undef RB
#undef RG
#undef RI
#undef RII
#undef REOS

    return res.str (); }

bool options::write (nitpick& nits, const ::boost::filesystem::path& fn) const
{   const ::std::string s (report (gr_config, true));
    return write_text_file (nits, fn, s); }
