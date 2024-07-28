/*
ssc (static site checker)
File Info
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

::boost::program_options::options_description
        options::aid_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::basic_ ("Command line options", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::cgi_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::cmd_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::config_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::environ_ (DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH),
        options::hidden_,
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
#define INSERT_PATH(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < ::std::string > (SECT VAR, c.FN ().string ());
#define INSERT_STATS(VAR,ST) \
    if (def.stats (ST) != c.stats (ST)) \
        if (c.stats (ST)) insert < bool > (STATS VAR, true); \
        else insert < bool > (STATS DONT VAR, false);
#define INSERT_STRING(SECT,VAR,FN) \
    if (def.FN () != c.FN ()) insert < ::std::string > (SECT VAR, c.FN ());
#define INSERT_VALID(VAR,TY,EN) \
    {   const ::std::size_t xtra = type_master < TY > :: extra_values (); \
        if (xtra > 0) \
        {   vstr_t v; \
            const ::std::size_t count = enum_base_count (TY); \
            for (::std::size_t i = count; i < count + xtra; ++i) \
                v.push_back (type_master < TY > :: name (static_cast < EN > (i))); \
            if (! v.empty ()) { const ::boost::any a = v; insert < ::boost::any > (VALIDATION VAR, a); } } }
#define INSERT_VALID2(VAR,TY,EN) \
    INSERT_VALID ( #VAR , TY, EN)
#define INSERT_VSTR(SECT,VAR,FN) \
    { const vstr_t& v = c.FN (); if (! v.empty ()) { const ::boost::any a = v; insert < ::boost::any > (SECT VAR, a); } }

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

    INSERT_PATH (CORPUS, OUTPUT, corpus);
    INSERT_BOOL (CORPUS, ARTICLE, article);
    INSERT_BOOL (CORPUS, BODY, body);
    INSERT_BOOL (CORPUS, MAIN, main);

    if (c.css_extension () != def.css_extension ())
        INSERT_VSTR (CSS, EXTENSION, css_extension);
    INSERT_BOOL (CSS, EXTERNAL, ext_css);
    INSERT_BOOL (CSS, VERIFY, load_css);
    INSERT_ENUM (t_css_version, CSS, VERSION, css_version);

    const ::std::string css (CSS);

    for (int i = 0; i < c_bad; ++i)
    {   const e_css_module m = static_cast < e_css_module > (i);
        if (def.css_module (m) != c.css_module (m))
            insert < int > (css + type_master < t_css_module > :: name (m), c.css_module (m)); }

    INSERT_BOOL (GENERAL, CGI, cgi);
    INSERT_BOOL (GENERAL, CLASS, unknown_class);
    INSERT_BOOL (GENERAL, CLASSIC, classic);
    INSERT_STRING (GENERAL, DATAPATH, path);
    INSERT_VSTR (GENERAL, EXCLUDE, exclude);
    INSERT_STRING (GENERAL, MACROEND, macro_end);
    INSERT_STRING (GENERAL, MACROSTART, macro_start);
    INSERT_INT (GENERAL, MAXFILESIZE, max_file_size);
    INSERT_STRING (GENERAL, OUTPUT, out_name);
    INSERT_BOOL (GENERAL, PROGRESS, progress);
    INSERT_BOOL (GENERAL, RDFA, rdfa);
    INSERT_BOOL (GENERAL, RPT, rpt_opens);
    INSERT_BOOL (GENERAL, TEST, test);
#ifndef NO_FRED
    INSERT (::std::size_t, GENERAL, THREAD, fred);
#endif // NO_FRED
    INSERT_BOOL (GENERAL, VCS, vcs);
    INSERT_BOOL (GENERAL, YGGDRISIL, yggdrisil);

    INSERT_VSTR (HTML, CUSTOM, custom_elements);
    INSERT_BOOL (HTML, FORCE, force_version);
    INSERT_BOOL (HTML, IE, ie);
    INSERT_VSTR (HTML, IGNORED, ignore);
    INSERT_STRING (HTML, LANG, lang);
    INSERT_BOOL (HTML, REL, rel);
    INSERT_BOOL (HTML, RFC1867, rfc_1867);
    INSERT_BOOL (HTML, RFC1942, rfc_1942);
    INSERT_BOOL (HTML, RFC1980, rfc_1980);
    INSERT_BOOL (HTML, RFC2070, rfc_2070);
    INSERT_BOOL (HTML, RUBY, ruby);
    INSERT_BOOL (HTML, SAFARI, safari);
    INSERT_BOOL (HTML, SLOVEN, sloven);
    // HTML SNIPPET
    INSERT_BOOL (HTML, SSI, ssi);
    INSERT_BOOL (HTML, TAGS, presume_tags);
    INSERT (::std::size_t, HTML, TITLE, title);
    if (def.html_ver () != c.html_ver ()) insert < ::std::string > (HTML VERSION, c.html_ver ().name ());

    INSERT_BOOL (JSONLD, VERIFY, jsonld);
    if (c.jsonld_extension () != def.jsonld_extension ())
        INSERT_VSTR (JSONLD, EXTENSION, jsonld_extension);
    INSERT_ENUM (t_js_version, JSONLD, VERSION, jsonld_version);

    INSERT_BOOL (LINKS, CHECK, links);
    INSERT_BOOL (LINKS, EXAMPLE, example);
    INSERT_BOOL (LINKS, EXTERNAL, external);
    INSERT_BOOL (LINKS, FORWARD, forwarded);
    INSERT_VSTR (LINKS, IGNORED, no_ex_check);
    INSERT_BOOL (LINKS, LOCAL, local);
    INSERT_BOOL (LINKS, ONCE, once);
    INSERT_VSTR (LINKS, PRETEND, pretend);
    INSERT_VSTR (LINKS, REPORT, report);
    INSERT_BOOL (LINKS, REVOKE, revoke);
    INSERT_BOOL (LINKS, XLINK, crosslinks);

    INSERT_ENUM (t_math_version, MATH, VERSION, math_version);

    INSERT_BOOL (MF, EXPORT, mf_export);
    INSERT_BOOL (MF, VERIFY, mf_verify);
    INSERT_INT (MF, VERSION, mf_version);

    INSERT_BOOL (MICRODATA, EXPORT, md_export);
    INSERT_BOOL (MICRODATA, VERIFY, ontology);
    INSERT_STRING (MICRODATA, VERIFY, export_root);
    INSERT_VSTR (MICRODATA, VERIFY, exports);

    INSERT_VSTR (NITS, ABHORRENT, abhorrent);
    INSERT_STRING (NITS, CACHE, cache);
    INSERT_VSTR (NITS, CATASTROPHE, catastrophe);
    INSERT_VSTR (NITS, COMMENT, comment);
    INSERT_VSTR (NITS, DBG, debug);
    INSERT_BOOL (NITS, EXTRA, extra);
    INSERT_STRING (NITS, FORMAT, nit_format);
    INSERT_VSTR (NITS, INFO, inform);
    INSERT_BOOL (NITS, NIDS, nids);
//    INSERT_STRING (NITS, FORMAT, nit_format);
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

#ifdef BEASTIES
    INSERT_STRING (SERVER, ACCEPT, accept);
    INSERT_STRING (SERVER, ADDRESS, server_address);
    INSERT_BOOL (SERVER, ENABLE, serve);
    INSERT_INT (SERVER, PORT, server_port);
    INSERT_STRING (SERVER, ROOT, server_root);
    INSERT_STRING (SERVER, PARAMETERS, server_parameters);
    INSERT_STRING (SERVER, PASSFILE, server_passfile);
    INSERT_STRING (SERVER, PUBLIC, server_public);
    // passwords and private keys not written; use a passfile
#endif // BEASTIES

    INSERT_BOOL (SHADOW, CHANGED, shadow_changed);
    INSERT_BOOL (SHADOW, COMMENT, shadow_comment);
    INSERT_ENUM (t_copy, SHADOW, COPY, copy);
    INSERT_BOOL (SHADOW, ENABLE, shadow_enable);
    INSERT_STRING (SHADOW, FICHIER, shadow_persist);
    INSERT_VSTR (SHADOW, IGNORED, shadow_ignore);
    INSERT_BOOL (SHADOW, INFO, info);
    INSERT_STRING (SHADOW, MSG, msg);
    INSERT_STRING (SHADOW, ROOT, shadow_root);
    INSERT_BOOL (SHADOW, SPACING, shadow_space);
    INSERT_BOOL (SHADOW, SSI, shadow_ssi);
    INSERT_BOOL (SHADOW, UPDATE, update);
    INSERT_VSTR (SHADOW, VIRTUAL, shadows);

    if (c.extensions () != def.extensions ())
        INSERT_VSTR (WEBSITE, EXTENSION, extensions);
    INSERT_STRING (SHADOW, INDEX, index);
    INSERT_VSTR (WEBSITE, SITE, site);
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
    INSERT_VALID2 (align3, t_align3, e_align3);
    INSERT_VALID2 (alignplus, t_alignplus, e_alignplus);
    INSERT_VALID2 (as, t_as, e_as);
    INSERT_VALID2 (as_units, t_as_units, e_as_units);
    INSERT_VALID2 (autocapitalise, t_autocapitalise, e_autocapitalise);
    INSERT_VALID2 (autocomplete, t_autocomplete, e_autocomplete);
    INSERT_VALID2 (baselineshift, t_baselineshift, e_baselineshift);
    INSERT_VALID2 (citype, t_citype, e_citype);
    INSERT_VALID2 (cntype, t_cntype, e_cntype);
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
    INSERT_VALID2 (rules, t_rules, e_rules);
    INSERT_VALID2 (sandbox, t_sandbox, e_sandbox);
    INSERT_VALID2 (shape7, t_shape7, e_shape7);
    INSERT_VALID2 (shape_rendering, t_shape_rendering, e_shape_rendering);
    INSERT_VALID2 (ssi, t_ssi, e_ssi);
    INSERT_VALID2 (ssi_comparison, t_ssi_comparison, e_ssi_comparison);
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
            GENERAL ", " LINKS "," WEBSITE "\n"
            ", etc.). Option names follow them. For example:\n\n"
            "[" GENERAL "]\n"
            VERBOSE "=2\n\n"
            "[" LINKS "]\n"
            CHECK "=1\n\n"
            "[" WEBSITE "]\n"
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

void options::yea_nay (context_t& c, context_t& (context_t::*fn) (const bool ), nitpick& nits, const char* yea, const char* nay)
{   VERIFY_NOT_NULL (fn, __FILE__, __LINE__);
    const bool on = var_ [yea].as <bool> ();
    const bool off = var_ [nay].as <bool> ();
    if (off)
    {   if (on) nits.pick (nit_yea_nay, es_info, ec_init, "when both ", nay, " and ", yea, " are used, ", nay, " applies");
        (c.*fn) (false); }
    else if (on) (c.*fn) (true); }

void options::yea_nay (context_t& c, const e_report r, nitpick& nits, const char* yea, const char* nay)
{   const bool on = var_ [yea].as <bool> ();
    const bool off = var_ [nay].as <bool> ();
    if (off)
    {   if (on) nits.pick (nit_yea_nay, es_info, ec_init, "when both ", nay, " and ", yea, " are used, ", nay, " applies");
        c.stats (r, false); }
    else if (on) c.stats (r, true); }

void options::yea_nay (context_t& c, const e_css_module m, nitpick& nits, const char* yea, const char* nay)
{   const bool on = var_ [yea].as <bool> ();
    const bool off = var_ [nay].as <bool> ();
    if (off)
    {   if (on) nits.pick (nit_yea_nay, es_info, ec_init, "when both ", nay, " and ", yea, " are used, ", nay, " applies");
        c.css_module (m, false); }
    else if (on) c.css_module (m, true); }

void options::init (context_t& c)
{   /*  a ask & answer   A reports params & exit
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
        n GENERAL THREAD N GENERAL DEFTHRD              
        o output         O rpt ext once
        p                P NIT OVERRIDE
        q
        r no revoke chks R HTML revision
        s domain name    S stats
        t template       T test mode
        u update         U unique
        v verbose        V version
        w                W cgi
        x extensions     X check crosslinked ids
        y GENERAL THREAD Y GENERAL DEFTHRD              
        z title max      Z spec
        0 dont ask
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
    if (cmd_.options ().size () > 0) return;
    pos_.add (WEBSITE ROOT, 1);
    basic_.add_options ()
        (ASK ",a", ::boost::program_options::bool_switch (), "Ask for parameters")
        (CONFIG ",f", ::boost::program_options::value < ::std::string > (), "Load configuration from this file.")
        (DEFCONF ",F", ::boost::program_options::bool_switch (), "Load configuration from " CONFIGURATION ".")
        (HELP ",h", ::boost::program_options::bool_switch (), "Output this information and exit.")
        (HTML SNIPPET ",H", ::boost::program_options::value < ::std::string > (), "Only nitpick the given snippet of HTML.")
        (ONTOLOGY LIST, ::boost::program_options::bool_switch (), "List known ontology schema for microdata andor RDFa, then exit.")
        (SWITCHES ",A", ::boost::program_options::bool_switch (), "Report switches seen, and exit.")
        (VALIDATION, ::boost::program_options::bool_switch (), "List attribute types that can be given additional 'valid' values, then exit.")
        (VERSION ",V", ::boost::program_options::bool_switch (), "Display version and copyright gen, then exit.")
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
        (DONT ASK ",0", ::boost::program_options::bool_switch (), "Stop asking for parameters")

        (GENERAL CUSTOM, ::boost::program_options::value < vstr_t > () -> composing (), "Define a custom element for checking the 'is' attribute; may be repeated.")
#ifdef NO_FRED
        (GENERAL DEFTHRD ",Y", ::boost::program_options::value < int > (), "If no setting specifies the thread count, set it to this.")
#endif // NO_FRED
        (GENERAL WHOOPS, ::boost::program_options::value < ::std::string > () -> composing (), "Exit with an error if nits of this severity or worse are generated. Values: '"
            CATASTROPHE "', '" WHOOPS "' (default), '" WARNING "', '" INFO  "', or '" COMMENT  "'.")
        (GENERAL IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore attributes and content of specified element; may be repeated.")
        (GENERAL LANG, ::boost::program_options::value < ::std::string > () -> composing (), "Default language (such as 'en_GB', 'lb_LU', etc.).")
        (GENERAL MACROSTART, ::boost::program_options::value < ::std::string > () -> default_value (def_macrostart), "Start of template macro (by default, the '{{' in '{{macro}}').")
        (GENERAL MACROEND, ::boost::program_options::value < ::std::string > () -> default_value (def_macroend), "End of template macro (by default, the '}}' in '{{macro}}').")
        (GENERAL REL, ::boost::program_options::bool_switch (), "Ignore recognised but non-standard <LINK> REL values.")
        (GENERAL DONT REL, ::boost::program_options::bool_switch (), "Nitpick recognised but non-standard <LINK> REL values.")
        (GENERAL RPT, ::boost::program_options::bool_switch (), "Report when CSS files opened.")
        (GENERAL DONT RPT, ::boost::program_options::bool_switch (), "Say nowt when CSS files opened.")
        (GENERAL SLOVEN, ::boost::program_options::bool_switch (), "Do not nitpick slovenly HTML such as missing closures, slovenly typography, etc..")
        (GENERAL DONT SLOVEN, ::boost::program_options::bool_switch (), "Nitpick slovenly HTML such as missing closures, slovenly typography, etc..")
        (GENERAL SSI, ::boost::program_options::bool_switch (), "Process (simple) Server Side Includes.")
        (GENERAL DONT SSI, ::boost::program_options::bool_switch (), "Do not process Server Side Includes.")
#ifdef NO_FRED
        (GENERAL THREAD ",y", ::boost::program_options::value < int > (), "Number of threads (default appropriate for the hardware).")
#endif // NO_FRED
        (GENERAL VERBOSE, ::boost::program_options::value < ::std::string > (), "Output these nits and worse. Values: '"
            CATASTROPHE "', '" WHOOPS "', '" WARNING "' (default), '" INFO  "', '" COMMENT  "', or 0 for silence.")
        (GENERAL YGGDRISIL, ::boost::program_options::bool_switch (), "Sniff yggdrisil.")

        (MATH CORE, ::boost::program_options::bool_switch (), "MathML Core (May 2022 draft).")
        (MATH DONT CORE, ::boost::program_options::bool_switch (), "Avoid MathML Core.")
        (MATH DRAFT, ::boost::program_options::value < int > (), "For MathML 4 only, which draft (2020 or 2022).")

        (MICRODATA EXPORT, ::boost::program_options::bool_switch (), "Export microdata (only verified data if --" ONTOLOGY VERIFY " is set).")
        (MICRODATA DONT EXPORT, ::boost::program_options::bool_switch (), "Do not export microdata data.")
        (MICRODATA VERIFY ",m", ::boost::program_options::bool_switch (), "Check microdata (" PROG " only understands certain microdata schemas).")
        (MICRODATA DONT VERIFY, ::boost::program_options::bool_switch (), "Do not check microdata.")
        (MICRODATA ROOT, ::boost::program_options::value < ::std::string > (), "Microdata export root directory (requires --" ONTOLOGY EXPORT ").")
        (MICRODATA VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "Export virtual directory, syntax virtual=directory. Must correspond to --" WEBSITE VIRTUAL ".")

        (NITS CACHE, ::boost::program_options::value < ::std::string > (), "Output nits on cache usage of filenames containing argument (no wildcards, except use \"*\" for all; empty for no report).")
        (NITS SPEC, ::boost::program_options::bool_switch (), "Output nits in test spec format (requires -T).")
        (NITS DONT SPEC, ::boost::program_options::bool_switch (), "Do not output nits in test spec format.")
        (NITS XXX, ::boost::program_options::value < ::std::string > (), "Output nits on cache usage from page names containing argument (empty for no report); may be combined with " NITS CACHE ".")

#ifndef BEASTIES
        (SERVER ACCEPT, ::boost::program_options::value < ::std::string > (), "Accept connections from this address range; format: 'addr/mask', default '127.0.0.1/32', non-local addresses rejected (use a proxy)")
        (SERVER ADDRESS, ::boost::program_options::value < ::std::string > (), "Server serves on this ip address (default '*', e.g. all available on machine).")
        (SERVER ENABLE, ::boost::program_options::bool_switch (), "Enable web server and sockets")
        (SERVER DONT ENABLE, ::boost::program_options::bool_switch (), "Disable web server and sockets .")
        (SERVER PARAMETERS, ::boost::program_options::value < ::std::string > (), "File containing SSL certificate parameters.")
        (SERVER PASSFILE, ::boost::program_options::value < ::std::string > (), "File containing SSL certificate password, if any.")
        (SERVER PASSWORD, ::boost::program_options::value < ::std::string > (), "SSL certificate password (not accepted on the command line).")
        (SERVER PORT, ::boost::program_options::value < ::std::string > () -> composing (), "Server serves on these ports (default 80,443); may be repeated.")
        (SERVER PRIVATE, ::boost::program_options::value < ::std::string > (), "File containing SSL private key.")
        (SERVER PUBLIC, ::boost::program_options::value < ::std::string > (), "File containing SSL public key.")
        (SERVER ROOT, ::boost::program_options::value < ::std::string > (), "Server serves pages from this " REPERTOIRE " (default '.').")
#endif // BEASTIES

#ifdef NOSPELL
        (SPELL ACCEPT, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore this word in spell checks; may be repeated.")
        (SPELL CASED, ::boost::program_options::bool_switch (), "Nitpick wrongly cased but correctly spelt words.")
        (SPELL DONT CASED, ::boost::program_options::bool_switch (), "Ignore case when checking spelling.")
        (SPELL CHECK ",G", ::boost::program_options::bool_switch (), "Check spelling (see also --" HTML LANG ").")
        (SPELL DONT CHECK, ::boost::program_options::bool_switch (), "Do not check spelling.")
        (SPELL DICT, ::boost::program_options::value < vstr_t > () -> composing (), "LANG,DICT: associate (hunspell) dictionary with language, e.g. 'en-US,en_US-large'; may be repeated (ignored in Windows).")
        (SPELL ICU, ::boost::program_options::bool_switch (), "Use the International Components for Unicode (ICU) text libraries (high quality but slow).")
        (SPELL DONT ICU, ::boost::program_options::bool_switch (), "Use standard text libraries (fast but inaccurate).")
        (SPELL LIST, ::boost::program_options::value < vstr_t > () -> composing (), "FILE,LANG: FILE contains additional valid spellings in LANG; may be repeated.")
        (SPELL PATH, ::boost::program_options::value < ::std::string > (), "Path to (hunspell) dictionaries (ignored in Windows).")
#endif // NOSPELL

        (SPELL DDICT, ::boost::program_options::value < vstr_t > () -> composing (), "hunspell dictionary; must have corresponding DLANG (ignored in Windows).")
        (SPELL DLANG, ::boost::program_options::value < vstr_t > () -> composing (), "language for corresponding DDICT dictionary (ignored in Windows).")

        // these are output by the config file writer. They're intended for debugging and maintenance.
        (SSC BUILD, ::boost::program_options::value < ::std::string > () -> default_value (BUILD_INFO), "SSC configuration used to write config file.")
        (SSC VERSION, ::boost::program_options::value < ::std::string > (), "config file written by this version of SSC.")
        (SSC OPTBOOST, ::boost::program_options::value < ::std::string > (), "boost version used by config file writer.")
        (SSC OPTCOMP, ::boost::program_options::value < ::std::string > (), "compiler used to build config file writer.")
        (SSC OPTCURL, ::boost::program_options::value < ::std::string > (), "if config file writer used curl.")
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
        (GENERAL CLASS, ::boost::program_options::bool_switch (), "Report unrecognised classes (requires CSS).")
        (GENERAL DONT CLASS, ::boost::program_options::bool_switch (), "Do not report unrecognised classes.")
        (GENERAL CLASSIC, ::boost::program_options::bool_switch (), "Report all classes used, not just those in .CSS files (requires --" GENERAL CLASS ").")
        (GENERAL DONT CLASSIC, ::boost::program_options::bool_switch (), "Do not report all classes used.")
        (GENERAL CGI ",W", ::boost::program_options::bool_switch (), "Process HTML snippets (for OpenBSD's httpd <FORM METHOD=GET ...>; disables most features).")
        (GENERAL DONT CGI, ::boost::program_options::bool_switch (), "Process a local static website.")
        (GENERAL DATAPATH ",C", ::boost::program_options::value < ::std::string > () -> default_value (def_path), "Root directory for most " PROG " files.")
#ifndef NO_FRED
        (GENERAL DEFTHRD ",Y", ::boost::program_options::value < int > (), "If no setting specifies the thread count, set it to this.")
#endif // NO_FRED
        (GENERAL EXCLUDE, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore files that end with this string; may be repeated.")
        (GENERAL FICHIER ",c", ::boost::program_options::value < ::std::string > () -> default_value (def_persisted), "File for persistent data (note --" GENERAL DATAPATH ").")
        (GENERAL INFO ",J", ::boost::program_options::bool_switch (), "Report " PROG " launch context at startup.")
        (GENERAL MAXFILESIZE, ::boost::program_options::value < int > (), "Maximum file size to read, in megabytes (zero for no limit).")
        (GENERAL OUTPUT ",o", ::boost::program_options::value < ::std::string > (), "Output file (default to the console).")
        (GENERAL PROGRESS ",D", ::boost::program_options::bool_switch (), "Report progress")
        (GENERAL DONT PROGRESS, ::boost::program_options::bool_switch (), "Don't be quite so noisy.")
        (GENERAL RDFA, ::boost::program_options::bool_switch (), "Check RDFa attributes.")
        (GENERAL DONT RDFA, ::boost::program_options::bool_switch (), "Do not check RDFa attributes.")
        (GENERAL SPEC ",j", ::boost::program_options::bool_switch (), "Reset default values of most switches to false.")
        (GENERAL TEST ",T", ::boost::program_options::bool_switch (), "Output in format useful for automated tests.")
        (GENERAL DONT TEST, ::boost::program_options::bool_switch (), "Output in format specified by other switches.")
#ifndef NO_FRED
        (GENERAL THREAD ",y", ::boost::program_options::value < int > () -> default_value  (def_fred), "Number of threads (default 1, zero for whatever is appropriate for the hardware).")
#endif // NO_FRED
        (GENERAL VCS, ::boost::program_options::bool_switch (), "Exclude file and directory names associated with certain version control systems.")
        (GENERAL DONT VCS, ::boost::program_options::bool_switch (), "Do not exclude file and directory names associated with certain version control systems.")

        (CORPUS ARTICLE, ::boost::program_options::bool_switch (), "Prefer the content of <ARTICLE> when gather page corpus.")
        (CORPUS DONT ARTICLE, ::boost::program_options::bool_switch (), "Avoid the content of <ARTICLE> when gather page corpus.")
        (CORPUS BODY, ::boost::program_options::bool_switch (), "Prefer the content of <BODY> when gather page corpus.")
        (CORPUS DONT BODY, ::boost::program_options::bool_switch (), "Avoid the content of <BODY> when gather page corpus.")
        (CORPUS MAIN, ::boost::program_options::bool_switch (), "Prefer the content of <MAIN> when gather page corpus.")
        (CORPUS DONT MAIN, ::boost::program_options::bool_switch (), "Avoid the content of <MAIN> when gather page corpus.")
        (CORPUS OUTPUT ",d", ::boost::program_options::value < ::std::string > (), "Dump corpus of site content to specified file.")

        (CSS ADJUST, ::boost::program_options::value < int > (), "CSS Colour Adjust level (0 or 3).")
        (CSS ADVLAY, ::boost::program_options::value < int > (), "CSS Advanced Layout level (0 or 3).")
        (CSS ANCHOR, ::boost::program_options::value < int > (), "CSS Scroll Anchoring level (0 or 3).")
        (CSS ANCHOR_POS, ::boost::program_options::value < int > (), "CSS Anchoring Positioning level (0 or 3).")
        (CSS ANIMATION, ::boost::program_options::value < int > (), "CSS Animation level (0 or 3).")
        (CSS BACKGROUND, ::boost::program_options::value < int > (), "CSS Background Borders level (0 or 3).")
        (CSS BOX_ALIGN, ::boost::program_options::value < int > (), "CSS Box Alignment level (0 or 3).")
        (CSS BOX_MODEL, ::boost::program_options::value < int > (), "CSS Box Model level (0, 3 or 4).")
        (CSS BOX_SIZING, ::boost::program_options::value < int > (), "CSS Box Sizing level (0, 3 or 4).")
        (CSS CASCADE, ::boost::program_options::value < int > (), "CSS Cascade & Inheritance level (0, 3, 4, 5 or 6).")
        (CSS COLOUR, ::boost::program_options::value < int > (), "CSS Colour level (0, 3, 4, 5, or 6).")
        (CSS COMPOSITING, ::boost::program_options::value < int > (), "CSS Compositing and Blending level (0 or 3).")
        (CSS COND_RULE, ::boost::program_options::value < int > (), "CSS Conditional Rule level (0, 3, 4, or 5).")
        (CSS CONTAIN, ::boost::program_options::value < int > (), "CSS Contain level (0, 3, 4, or 5).")
        (CSS CON_TENT, ::boost::program_options::value < int > (), "CSS Generated Content level (0 or 3).")
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
        (CSS FILL, ::boost::program_options::value < int > (), "CSS Fill and Stroke level (0 or 3).")
        (CSS FILTER, ::boost::program_options::value < int > (), "CSS Filter Effects level (0 or 3).")
        (CSS FLOAT, ::boost::program_options::value < int > (), "CSS Page Floats level (0 or 3).")
        (CSS FONT, ::boost::program_options::value < int > (), "CSS Font level (0, 3, 4, or 5).")
        (CSS FRAG, ::boost::program_options::value < int > (), "CSS Fragmentation level (0, 3, or 4).")
        (CSS GRID, ::boost::program_options::value < int > (), "CSS Grid level (0, 3, or 4).")
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
        (CSS PSEUDO, ::boost::program_options::value < int > (), "CSS Pseudo-Elements level (0 or 4).")
        (CSS REGION, ::boost::program_options::value < int > (), "CSS Regions level (0 or 3).")
        (CSS RHYTHM, ::boost::program_options::value < int > (), "CSS Rhythmic Sizing level (0 or 3).")
        (CSS ROUND, ::boost::program_options::value < int > (), "CSS Round Display level (0 or 3).")
        (CSS RUBY, ::boost::program_options::value < int > (), "CSS Ruby Annotation Layout level (0 or 3).")
        (CSS SCOPE, ::boost::program_options::value < int > (), "CSS Scoping level (0 or 3).")
        (CSS SCROLLBAR, ::boost::program_options::value < int > (), "CSS Scrollbar Styling level (0 or 3).")
        (CSS SDA, ::boost::program_options::value < int > (), "CSS Scroll Driven Animations level (0 or 3).")
        (CSS SELECTOR, ::boost::program_options::value < int > (), "CSS Selector level (0, 3, or 4).")
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
            "all modules of a given level (3, 4, 5, 6); "
            "solid snapshot modules by year (07, 10, 15, 17, 18, 20, 21, 22, 23, 24); "
            "solid and wobbly snapshot modules by year (15+, 17+, 18+, 20+, 21+, 22+, 23+, 24+); "
            "all snapshot modules by year (15++, 17++, 18++, 20++, 21++, 22++, 23++, 24++): "
            "default appropriate for HTML version.")
        (CSS VIEW, ::boost::program_options::value < int > (), "CSS View Transitions level (0 or 3).")
        (CSS VIEWPORT, ::boost::program_options::value < int > (), "CSS Viewport level (0 or 3).")
        (CSS WC, ::boost::program_options::value < int > (), "CSS Will Change level (0 or 3).")
        (CSS WRITING, ::boost::program_options::value < int > (), "CSS Writing Mode level (0, 3 or 4).")

        (HTML CUSTOM, ::boost::program_options::value < vstr_t > () -> composing (), "Define a custom element for checking the 'is' attribute; may be repeated.")
        (HTML FORCE, ::boost::program_options::bool_switch (), "When <!DOCTYPE...> is missing, forcibly presume HTML version as per --html.version.")
        (HTML DONT FORCE, ::boost::program_options::bool_switch (), "When <!DOCTYPE...> is missing, correctly presume HTML 1 or HTML tags, as per --html.tags.")
        (HTML IE, ::boost::program_options::bool_switch (), "Ignore certain naughtitudes accepted by versions of Internet Explorer.")
        (HTML DONT IE, ::boost::program_options::bool_switch (), "Mention certain naughtitudes accepted by versions of Internet Explorer.")
        (HTML IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "Ignore attributes and content of specified element; may be repeated.")
        (HTML LANG, ::boost::program_options::value < ::std::string > () -> composing (), "Default language (such as 'en_GB', 'lb_LU', etc.).")
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
        (HTML SLOVEN, ::boost::program_options::bool_switch (), "Do not nitpick slovenly HTML such as missing closures, slovenly typography, etc..")
        (HTML DONT SLOVEN, ::boost::program_options::bool_switch (), "Nitpick slovenly HTML such as missing closures, slovenly typography, etc..")
        (HTML SSI ",I", ::boost::program_options::bool_switch (), "Process (simple) Server Side Includes.")
        (HTML DONT SSI, ::boost::program_options::bool_switch (), "Do not process Server Side Includes.")
        (HTML TAGS, ::boost::program_options::bool_switch (), "Presume HTML with no DOCTYPE is HTML Tags (CERN version).")
        (HTML DONT TAGS, ::boost::program_options::bool_switch (), "Presume HTML with no DOCTYPE is HTML 1.0.")
        (HTML TITLE ",z", ::boost::program_options::value < int > () -> default_value (def_htmltitle), "Maximum advisable length of <TITLE> text.")
        (HTML VERSION ",R", ::boost::program_options::value < ::std::string > (),
            "Set the specific version of HTML with DOCTYPE (default '2022/7/1'). "
            "For a W3 standard, give its version (e.g. '5.2'). "
            "For a WhatWG living standard, give its date (e.g. '2015/7/1'). "
            "For XHTML, use XHTML plus version, e.g. 'XHTML 1.0'. "
            "For HTML+, use '+'. For HTML tags, use 'tags'.")
 
        (JSONLD EXTENSION, ::boost::program_options::value < vstr_t > () -> composing (), "Extension for JSON-LD files (default jld); may be repeated.")
        (JSONLD VERIFY, ::boost::program_options::bool_switch (), "Experimental: Verify JSON-LD (incomplete).")
        (JSONLD DONT VERIFY, ::boost::program_options::bool_switch (), "Do not verify JSON-LD.")
        (JSONLD VERSION, ::boost::program_options::value < ::std::string > (), "Presume this version of JSON-LD (1.0 or 1.1, default 1.0).")

        (LINKS CHECK ",l", ::boost::program_options::bool_switch (), "Check internal links.")
        (LINKS DONT CHECK, ::boost::program_options::bool_switch (), "Ignore internal links.")
        (LINKS EXAMPLE, ::boost::program_options::bool_switch (), "Issue warning if link to faux domain, such as example.com, found.")
        (LINKS DONT EXAMPLE, ::boost::program_options::bool_switch (), "Say nothing if link to faux domain, such as example.com, found.")
        (LINKS EXTERNAL ",e", ::boost::program_options::bool_switch (), "Check external links (sets --" LINKS CHECK ").")
        (LINKS DONT EXTERNAL, ::boost::program_options::bool_switch (), "Ignore external links.")
        (LINKS FORWARD ",3", ::boost::program_options::bool_switch (), "Report http forwarding errors, e.g. 301 and 308 (sets --" LINKS EXTERNAL ").")
        (LINKS DONT FORWARD, ::boost::program_options::bool_switch (), "Ignore http forwarding errors, e.g. 301 and 308.")
        (LINKS IGNORED, ::boost::program_options::value < vstr_t > () -> composing (), "When checking external links, ignore this domain; may be repeated.")
        (LINKS LOCAL, ::boost::program_options::bool_switch (), "Issue warning if link to local domain, such as ???.internal or ???.lan, found.")
        (LINKS DONT LOCAL, ::boost::program_options::bool_switch (), "Don't mention links to local domains.")
        (LINKS PRETEND, ::boost::program_options::value < vstr_t > () -> composing (), "Pretend files that end with this string exist; may be repeated.")
        (LINKS ONCE ",O", ::boost::program_options::bool_switch (), "Report each broken external link once (sets --" LINKS EXTERNAL ").")
        (LINKS DONT ONCE, ::boost::program_options::bool_switch (), "Report broken links whenever they are found.")
        (LINKS REPORT, ::boost::program_options::value < vstr_t > () -> composing (), "Report links to this domain and its descendants; may be repeated.")
        (LINKS REVOKE ",r", ::boost::program_options::bool_switch (), "Do not check whether https certificates have been revoked (sets --" LINKS EXTERNAL ").")
        (LINKS DONT REVOKE, ::boost::program_options::bool_switch (), "Check whether https certificates have been revoked (sets --" LINKS EXTERNAL ").")
        (LINKS XLINK ",X", ::boost::program_options::bool_switch (), "Check crosslink IDs.")
        (LINKS DONT XLINK, ::boost::program_options::bool_switch (), "Do not check crosslink IDs.")

        (MATH VERSION, ::boost::program_options::value < ::std::string > (), "preferred version of MathML; one of 0/1/2/3/4.20/4/core (default: determined by HTML version).")

        (ONTOLOGY EXPORT, ::boost::program_options::bool_switch (), "Export ontology data (only verified data if --" ONTOLOGY VERIFY " is set).")
        (ONTOLOGY DONT EXPORT, ::boost::program_options::bool_switch (), "Do not export ontology data.")
        (ONTOLOGY VERIFY ",m", ::boost::program_options::bool_switch (), "Check ontology (" PROG " only understands certain ontologies).")
        (ONTOLOGY DONT VERIFY, ::boost::program_options::bool_switch (), "Do not check ontology data.")
        (ONTOLOGY ROOT, ::boost::program_options::value < ::std::string > (), "Ontology export root directory (requires --" ONTOLOGY EXPORT ").")
        (ONTOLOGY VIRTUAL, ::boost::program_options::value < vstr_t > () -> composing (), "Export virtual directory content, syntax virtual=directory. Must correspond to --" WEBSITE VIRTUAL ".")

        (MF VERIFY ",M", ::boost::program_options::bool_switch (), "Check microformats in class and rel attributes (see https://" MICROFORMATS_ORG "/).")
        (MF DONT VERIFY, ::boost::program_options::bool_switch (), "Do not check microformats in class and rel attributes.")
        (MF VERSION, ::boost::program_options::value < int > (), "Check this version of microformats (1, 2, or 3 for both).")
        (MF EXPORT, ::boost::program_options::bool_switch (), "Export microformat data (requires --" MF VERIFY ").")
        (MF DONT EXPORT, ::boost::program_options::bool_switch (), "Do not export microformat data.")

        (NITS ABHORRENT, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as an abhorrence; may be repeated.")
        (NITS CATASTROPHE, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a catastrophe; may be repeated.")
        (NITS COMMENT, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a comment; may be repeated.")
        (NITS DBG, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as a debug message; may be repeated.")
        (NITS WHOOPS, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine nit as an error; may be repeated.")
        (NITS ERROREXIT ",E", ::boost::program_options::value < ::std::string > () -> composing (), "Exit with an error if nits of this severity or worse are generated. Values: '"
            CATASTROPHE "', '" WHOOPS "' (default), '" WARNING "', '" INFO  "', or '" COMMENT  "'.")
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
        (NITS VERBOSE, ::boost::program_options::value < ::std::string > (), "Output these nits and worse. Values: '"
            CATASTROPHE "', '" WHOOPS "', '" WARNING "' (default), '" INFO  "', '" COMMENT  "', or 0 for silence.")
        (NITS WARNING, ::boost::program_options::value < vstr_t > () -> composing (), "Redefine specified nit as a warning; may be repeated.")
        (NITS WATCH, ::boost::program_options::bool_switch (), "Output debug nits (for automation).")
        (NITS DONT WATCH, ::boost::program_options::bool_switch (), "Do not output debug nits.")

#ifdef BEASTIES
        (SERVER ACCEPT, ::boost::program_options::value < ::std::string > (), "Accept connections from this address range; format: 'addr/mask', default '127.0.0.1/32', non-local addresses rejected (use a proxy)")
        (SERVER ADDRESS, ::boost::program_options::value < ::std::string > (), "Server serves on this ip address (default '*', e.g. all available on machine).")
        (SERVER ENABLE, ::boost::program_options::bool_switch (), "Enable web server and sockets")
        (SERVER DONT ENABLE, ::boost::program_options::bool_switch (), "Disable web server and sockets .")
        (SERVER PARAMETERS, ::boost::program_options::value < ::std::string > (), "File containing SSL certificate parameters.")
        (SERVER PASSFILE, ::boost::program_options::value < ::std::string > (), "File containing SSL certificate password, if any.")
        (SERVER PORT, ::boost::program_options::value < ::std::string > () -> composing (), "Server serves on these ports (default 80,443); may be repeated.")
        (SERVER PRIVATE, ::boost::program_options::value < ::std::string > (), "File containing SSL private key.")
        (SERVER PUBLIC, ::boost::program_options::value < ::std::string > (), "File containing SSL public key.")
        (SERVER ROOT, ::boost::program_options::value < ::std::string > (), "Server serves pages from this " REPERTOIRE " (default '.').")
#endif // BEASTIES

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
        (SHADOW SSI, ::boost::program_options::bool_switch (), "Resolve SSIs on shadow pages when --" HTML SSI " is set.")
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
        (SPELL CHECK ",G", ::boost::program_options::bool_switch (), "Check spelling (see also --" HTML LANG ").")
        (SPELL DONT CHECK, ::boost::program_options::bool_switch (), "Do not check spelling.")
        (SPELL DICT, ::boost::program_options::value < vstr_t > () -> composing (), "LANG,DICT: associate (hunspell) dictionary with language, e.g. 'en-US,en_US-large'; may be repeated (ignored in Windows).")
        (SPELL ICU, ::boost::program_options::bool_switch (), "Use the International Components for Unicode (ICU) text libraries (high quality but slow).")
        (SPELL DONT ICU, ::boost::program_options::bool_switch (), "Use standard text libraries (fast but inaccurate).")
        (SPELL LIST, ::boost::program_options::value < vstr_t > () -> composing (), "FILE,LANG: FILE contains additional valid spellings in LANG; may be repeated.")
        (SPELL PATH, ::boost::program_options::value < ::std::string > (), "Path to (hunspell) dictionaries (ignored in Windows).")
#endif // NOSPELL

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
        (STATS SUMMARY ",S", ::boost::program_options::bool_switch (), "Report overall statistics.")
        (STATS DONT SUMMARY, ::boost::program_options::bool_switch (), "Do not report overall statistics.")
        (STATS SWASH, ::boost::program_options::bool_switch (), "Output swash report.")
        (STATS DONT SWASH, ::boost::program_options::bool_switch (), "Do not output swash report.")
        (STATS VERSION, ::boost::program_options::bool_switch (), "Output version report.")
        (STATS DONT VERSION, ::boost::program_options::bool_switch (), "Do not output version report.")
        (STATS VIEW, ::boost::program_options::bool_switch (), "Output view report.")
        (STATS DONT VIEW, ::boost::program_options::bool_switch (), "Do not output view report.")

        (SVG VERSION, ::boost::program_options::value < ::std::string > (), "Presumed this version of SVG if version attribute missing (requires HTML 4 or greater).")

        (VALIDATION MINOR ",m", ::boost::program_options::value < int > (), "Validate HTML 5 with this w3 minor version (e.g. 2 for HTML 5.2).")
        (VALIDATION MICRODATAARG, ::boost::program_options::bool_switch (), "Validate HTML5 microdata.")
        (VALIDATION DONT MICRODATAARG, ::boost::program_options::bool_switch (), "Do not validate HTML5 microdata.")
        	;

#ifdef BEASTIES
    risky_.add_options ()
        (SERVER PASSWORD, ::boost::program_options::value < ::std::string > (), "SSL certificate password (not accepted on the command line).")
            ;
#endif // BEASTIES

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

void options::parse (context_t& c, output_streams_t& o, nitpick& nits, const vstr_t& vs)
{   ::std::string loaded;
    init (c);
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
        {   c.cgi (true).article (false).body (false).cased (false).classic (false).crosslinks (false).example (false).ext_css (false)
                .external (false).forwarded (false).ie (false).icu (true).info (true).jsonld (false).links (false).load_css (false).main (false)
                .md_export (false).mf_verify (true).microdata (true).not_root (false).once (true).ontology (true).presume_tags (false)
                .progress (false) .rdfa (false).rel (true).revoke (false).rfc_1867 (true).rfc_1942 (true).rfc_1980 (true).rfc_2070 (true).rpt_opens (false)
                .shadow_changed (false).shadow_comment (false).shadow_enable (false).shadow_space (false).shadow_ssi (false).spell (false).ssi (false)
                .stats (rcb_page, false).stats (rcb_summary, false).unknown_class (false).update (false);
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
            o.console ("Environment: ", q, "\n");
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
    {   ::boost::filesystem::path file (CONFIGURATION);
        if (var_.count (CONFIG)) file = var_ [CONFIG].as < ::std::string > ();
        else if ((! var_ [DEFCONF].as <bool > ()) && env_var_.count (ENV_CONFIG)) file = env_var_ [ENV_CONFIG].as < ::std::string > ();
        nits.set_context (0, file.string ());
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (nm_config, file.string ());
        if (file_exists (file))
        {   nits.pick (nit_configuration, es_debug, ec_init, ::std::string ("Loading configuration ") + file.string () + "...");
            try
            {   c.config (canonical_name (absolute_name (file))); }
            catch (...)
            {   nits.pick (nit_configuration, es_error, ec_init, ::std::string ("Cannot canonise ") + file.string ());
                return; } }
        else
        {   nits.pick (nit_configuration, es_error, ec_init, ::std::string ("Cannot find ") + file.string ());
            return; }
        if (! parse (nits, file)) return; }
/*        vstr_t unrecognised;
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
            return; }
        catch (...)
        {   nits.pick (nit_configuration, es_error, ec_init, "Unknown exception when processing ", file.string ());
            return; }
        for (auto u : unrecognised)
            nits.pick (nit_unknown_option, es_warning, ec_init, "Unknown configuration option ", quote (u), " ignored"); }
    ::boost::program_options::notify (var_);
*/
    if (var_ [GENERAL INFO].as <bool > ())
        o.console (c.general_info (), "\n");
    if (var_ [VERSION].as < bool > ())
    {   c.todo (do_simple);
        return; }
    if (var_ [HELP].as < bool > ())
    {   help (aid_);
        return; }
    if (var_ [SWITCHES].as < bool > ())
    {   c.yggdrisil (true);
        c.domsg (report ());
        c.todo (do_simple);
        return; }
    if (var_ [VALIDATION].as < bool > ())
    {   ::std::ostringstream waste_of_space;
        waste_of_space << valid_;
        c.domsg (waste_of_space.str ());
        c.todo (do_simple);
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
        c.domsg (res);
        c.todo (do_simple);
        return; }

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
            o.console ("Config: ", q, "\n");
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
    else if (! var_.count (WEBSITE ROOT))
    {   c.domsg ("\n" TYPE_HELP "\n");
        c.todo (do_simple);
        return; }
    else c.todo (do_examine); }

void options::contextualise (context_t& c, output_streams_t& o, nitpick& nits)
{   yea_nay (c, &context_t::test, nits, GENERAL TEST, GENERAL DONT TEST);
    yea_nay (c, &context_t::spec, nits, NITS SPEC, NITS DONT SPEC);

    if (c.test () || var_ [GENERAL SPEC].as <bool> ())
        c.article (false).body (false).cased (false).classic (false).crosslinks (false).example (false).external (false).ext_css (false).forwarded (false)
            .icu (true).info (false).jsonld (false).links (false).load_css (true).main (false).md_export (false).mf_verify (false)
            .microdata (false).nids (true).nits (false).nits_nits_nits (true).not_root (false).once (false).ontology (true).presume_tags (false)
            .progress (false).rdfa (false).rel (false).revoke (false).rfc_1867 (true).rfc_1942 (true).rfc_1980 (true).rfc_2070 (true).rpt_opens (false)
            .shadow_changed (false).shadow_comment (false).shadow_enable (false).shadow_space (false).shadow_ssi (false).spell (false).ssi (false)
            .stats (rcb_page, false).stats (rcb_summary, false).unknown_class (false).update (false);

#ifndef NO_FRED
    if (var_.count (GENERAL THREAD)) c.fred (var_ [GENERAL THREAD].as < int > ());
    else if (var_.count (GENERAL DEFTHRD)) c.fred (var_ [GENERAL DEFTHRD].as < int > ());
    else c.fred (1);
#endif // NO_FRED

    if (! c.cgi ())
    {   if (var_.count (NITS FORMAT)) c.nit_format (var_ [NITS FORMAT].as < ::std::string > ());
        if (var_.count (NITS OVERRIDE)) c.nit_override (var_ [NITS OVERRIDE].as < ::std::string > ()); }

    if (var_.count (GENERAL VERBOSE)) c.verbose (decode_severity (nits, var_ [GENERAL VERBOSE].as < ::std::string > ()));
    if (var_.count (NITS VERBOSE)) c.verbose (decode_severity (nits, var_ [NITS VERBOSE].as < ::std::string > ()));
    if (var_.count (HTML SNIPPET)) c.snippet (var_ [HTML SNIPPET].as < ::std::string > ());
    yea_nay (c, &context_t::mf_verify, nits, MF VERIFY, MF DONT VERIFY);

    if (c.test () || ! c.cgi ())
    {   if (var_.count (GENERAL OUTPUT))
        {   c.out_name (var_ [GENERAL OUTPUT].as < ::std::string > ());
            o.init (nits, nix_path_to_local (var_ [GENERAL OUTPUT].as < ::std::string > ()));
#ifndef EXPAND_TEST
            if (! c.test ())
                nits.pick (nit_configuration, es_debug, ec_init, ::std::string ("Writing to ") + var_ [GENERAL OUTPUT].as < ::std::string > ());
#endif // EXPAND_TEST
        }
        if ((! var_ [GENERAL DONT PROGRESS].as <bool > ()) && var_ [GENERAL PROGRESS].as <bool > ())
            if (c.test ()) o.console (test_title);
            else if (c.tell (es_info)) o.console (full_title);
            else o.console (simple_title); }

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
        {   nits.pick (nit_mf_version, es_warning, ec_init, "invalid microformats version ", quote (n), "; presuming version 2");
            n = 2; }
        c.mf_version (GSL_NARROW_CAST < unsigned char > (n)); }

    if (var_.count (HTML VERSION) != 0)
    {   ::std::string ver (var_ [HTML VERSION].as < ::std::string > ());
        if (! ver.empty ())
        {   bool xhtml = false;
            if (ver.length () >= 4)
                if (compare_no_case (ver.substr (0, 4), HTML_EXT)) ver = trim_the_lot_off (ver.substr (4));
                else if (compare_no_case (ver.substr (0, 5), XHTML_EXT)) { ver = trim_the_lot_off (ver.substr (5)); xhtml = true; }
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
                c.html_ver (mjr, mnr);
                if (xhtml) c.html_ver ().set_flags (HV_XHTML); }
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
                            c.html_ver (html_jan05); }
                        else if ((y > HTML_LATEST_YEAR) || ((y == HTML_LATEST_YEAR) && (m > HTML_LATEST_MONTH)))
                        {   nits.pick (nit_config_date, es_warning, ec_init, quote (ver), " is too recent, presuming ", HTML_LATEST_YEAR, "/", HTML_LATEST_MONTH, "/1");
                            c.html_ver (html_current); }
                        else c.html_ver (html_version (d));
                        if (xhtml)
                            c.html_ver ().set_flags (HV_XHTML); } }
            else switch (lexical < int > :: cast (ver))
            {   case 1 : c.html_ver (html_1); break;
                case 2 : c.html_ver (html_2); break;
                case 3 : c.html_ver (html_3_2); break;
                case 4 : c.html_ver (html_4_1); break;
                case 5 : c.html_ver (html_default); break;
                default : 
                    if (ver == "+") c.html_ver (html_plus);
                    else if (compare_no_case (ver, "plus")) c.html_ver (html_plus);
                    else if (compare_no_case (ver, "tags")) c.html_ver (html_tags);
                    else nits.pick (nit_config_version, es_error, ec_init, quote (ver), ": bad HTML version"); } } }
    if (! c.cgi ())
        if (var_.count (WEBSITE ROOT) == 0) c.root (nix_path_to_local ("."));
        else
        {   const ::std::string arg = trim_the_lot_off (var_ [WEBSITE ROOT].as < ::std::string > ());
            if (arg.empty ()) nits.pick (nit_no_such_folder, es_error, ec_init, "that --" WEBSITE ROOT " is a little too spaced out for " PROG);
            else
            {   const ::std::string local = nix_path_to_local (arg);
                if (! ::boost::filesystem::exists (local))
                    nits.pick (nit_no_such_folder, es_error, ec_init, PROG " cannot access the directory ", quote (local));
                else if (::boost::filesystem::is_directory (local))
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
    {   yea_nay (c, &context_t::unknown_class, nits, GENERAL CLASS, GENERAL DONT CLASS);
        yea_nay (c, &context_t::classic, nits, GENERAL CLASSIC, GENERAL DONT CLASSIC);
        yea_nay (c, &context_t::progress, nits, GENERAL PROGRESS, GENERAL DONT PROGRESS);
        yea_nay (c, &context_t::rdfa, nits, GENERAL RDFA, GENERAL DONT RDFA);
        yea_nay (c, &context_t::rel, nits, GENERAL REL, GENERAL DONT REL);
        yea_nay (c, &context_t::rpt_opens, nits, GENERAL RPT, GENERAL DONT RPT);
        yea_nay (c, &context_t::sloven, nits, GENERAL SLOVEN, GENERAL DONT SLOVEN);
        yea_nay (c, &context_t::ssi, nits, GENERAL SSI, GENERAL DONT SSI);
        c.persisted (path_in_context (nix_path_to_local (var_ [GENERAL FICHIER].as < ::std::string > ())));

        CONSTEXPR long meg = 1024*1024;

        if (! var_.count (GENERAL MAXFILESIZE))
            c.max_file_size (4 * meg);
        else
        {   long max = static_cast < long > (var_ [GENERAL MAXFILESIZE].as < int > ());
            if (max < 0 || (max > (LONG_MAX / meg))) max = DEFAULT_MAX_FILE_SIZE;
            c.max_file_size (max * meg); }

        if (var_.count (GENERAL CUSTOM)) c.custom_elements ( var_ [GENERAL CUSTOM].as < vstr_t > ());
        if (var_.count (GENERAL WHOOPS))
        {   const e_severity sev = decode_severity (nits, var_ [GENERAL WHOOPS].as < ::std::string > ());
            if (sev != es_undefined) c.report_error (sev); }
        if (var_.count (GENERAL EXCLUDE)) c.exclude (nits, var_ [GENERAL EXCLUDE].as < vstr_t > ());
        yea_nay (c, &context_t::vcs, nits, GENERAL VCS, GENERAL DONT VCS);
        if (var_.count (GENERAL IGNORED)) c.ignore (nits, var_ [GENERAL IGNORED].as < vstr_t > ());
        if (var_.count (GENERAL LANG)) c.lang (var_ [GENERAL LANG].as < ::std::string > ());
        if (var_.count (GENERAL MACROEND)) c.macro_end (var_ [GENERAL MACROEND].as < ::std::string > ());
        if (var_.count (GENERAL MACROSTART)) c.macro_start (var_ [GENERAL MACROSTART].as < ::std::string > ());

        if (var_ [GENERAL YGGDRISIL].as <bool> ()) c.yggdrisil (true);

        if (var_.count (CORPUS OUTPUT)) c.corpus (nix_path_to_local (var_ [CORPUS OUTPUT].as < ::std::string > ()));
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
        process_css_level (c, c_background_border, n, nits, CSS BACKGROUND, "Background Border", 3, true);
        process_css_level (c, c_box_alignment, n, nits, CSS BOX_ALIGN, "Background Alignment", 3);
        process_css_level (c, c_box_model, n, nits, CSS BOX_MODEL, "Box Model", 4);
        process_css_level (c, c_box_sizing, n, nits, CSS BOX_SIZING, "Background Sizing", 4);
        process_css_level (c, c_cascade_inheritance, n, nits, CSS CASCADE, "Cascade & Inheritance", 6);
        process_css_level (c, c_colour, n, nits, CSS COLOUR, "Colour", 6);
        process_css_level (c, c_compositing_blending, n, nits, CSS COMPOSITING, "Compositing", 3, true);
        process_css_level (c, c_conditional_rule, n, nits, CSS COND_RULE, "Conditional Rule", 5);
        process_css_level (c, c_containment, n, nits, CSS CONTAIN, "Contain", 5);
        process_css_level (c, c_generated_content, n, nits, CSS CON_TENT, "Generated Content", 3);
        process_css_level (c, c_counter_style, n, nits, CSS CS, "Counter Style", 3);
        process_css_level (c, c_custom_property, n, nits, CSS CUSTOM, "Custom", 3, true);
        process_css_level (c, c_device_adaption, n, nits, CSS DEVICE, "Device Adaption", 3);
        process_css_level (c, c_display, n, nits, CSS DISPLAY, "Display", 3);
        process_css_level (c, c_easing_function, n, nits, CSS EASE, "Ease", 4, true);
        process_css_level (c, c_exclusion, n, nits, CSS EXCLUDE, "Exclusions", 3);
        process_css_level (c, c_flexible_box_layout, n, nits, CSS FBL, "Flexible Box Layout", 3);
        process_css_level (c, c_fill_stroke, n, nits, CSS FILL, "Fill and Stroke", 3);
        process_css_level (c, c_filter_effect, n, nits, CSS FILTER, "Filter Effects", 3);
        process_css_level (c, c_page_float, n, nits, CSS FLOAT, "Page Floats", 3);
        process_css_level (c, c_font, n, nits, CSS FONT, "Font", 5);
        process_css_level (c, c_fragmentation, n, nits, CSS FRAG, "Fragmentation", 4);
        process_css_level (c, c_grid_layout, n, nits, CSS GRID, "Grid", 4);
        process_css_level (c, c_custom_highlight, n, nits, CSS HIGHLIGHT, "Custom Highlight", 4);
        process_css_level (c, c_hyperlink_presentation, n, nits, CSS HYPERLINK, "Hyperlink", 5);
        process_css_level (c, c_image, n, nits, CSS IMAGE, "Image", 4);
        process_css_level (c, c_inline_layout, n, nits, CSS INLINE, "Inline Layout", 3);
        process_css_level (c, c_list_counter, n, nits, CSS LIST, "Lists and Counters", 3);
        process_css_level (c, c_line_grid, n, nits, CSS LINE_GRID, "Line Grid", 3);
        process_css_level (c, c_logical_property, n, nits, CSS LOGIC, "Logical Properties and Values", 3);
        process_css_level (c, c_marquee, n, nits, CSS MARQUEE, "Marquee", 3);
        process_css_level (c, c_masking, n, nits, CSS MASKING, "Masking", 3);
        process_css_level (c, c_media_query, n, nits, CSS MEDIA, "Media", 5);
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
        process_css_level (c, c_selector, n, nits, CSS SELECTOR, "Selector", 4);
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
        process_css_level (c, c_transition, n, nits, CSS TRANSITION, "Transition", 3, true);
        yea_nay (c, &context_t::tv_profile, nits, CSS TV, CSS DONT TV);
        process_css_level (c, c_basic_user_interface, n, nits, CSS UI, "UI", 4);
        process_css_level (c, c_value_unit, n, nits, CSS VAL, "Values and Units", 4);
        process_css_level (c, c_view_transition, n, nits, CSS VIEW, "View Transitions", 3);
        process_css_level (c, c_viewport, n, nits, CSS VIEWPORT, "Viewport", 3);
        process_css_level (c, c_will_change, n, nits, CSS WC, "Will Change", 3);
        process_css_level (c, c_writing_mode, n, nits, CSS WRITING, "Writing Mode", 4);

        if (var_.count (HTML CUSTOM)) c.custom_elements ( var_ [HTML CUSTOM].as < vstr_t > ());
        yea_nay (c, &context_t::force_version, nits, HTML FORCE, HTML DONT FORCE);
        yea_nay (c, &context_t::ie, nits, HTML IE, HTML DONT IE);
        if (var_.count (HTML IGNORED)) c.ignore (nits, var_ [HTML IGNORED].as < vstr_t > ());
        if (var_.count (HTML LANG)) c.lang (var_ [HTML LANG].as < ::std::string > ());
        yea_nay (c, &context_t::rel, nits, HTML REL, HTML DONT REL);
        yea_nay (c, &context_t::rfc_1867, nits, HTML RFC1867, HTML DONT RFC1867);
        yea_nay (c, &context_t::rfc_1942, nits, HTML RFC1942, HTML DONT RFC1942);
        yea_nay (c, &context_t::rfc_1980, nits, HTML RFC1980, HTML DONT RFC1980);
        yea_nay (c, &context_t::rfc_2070, nits, HTML RFC2070, HTML DONT RFC2070);
        yea_nay (c, &context_t::ruby, nits, HTML RUBY, HTML DONT RUBY);
        yea_nay (c, &context_t::presume_tags, nits, HTML TAGS, HTML DONT TAGS);
        yea_nay (c, &context_t::safari, nits, HTML SAFARI, HTML DONT SAFARI);
        yea_nay (c, &context_t::sloven, nits, HTML SLOVEN, HTML DONT SLOVEN);
        yea_nay (c, &context_t::ssi, nits, HTML SSI, HTML DONT SSI);
        if (var_.count (HTML TITLE)) c.title (static_cast < unsigned char > (var_ [HTML TITLE].as < int > ()));

        yea_nay (c, &context_t::jsonld, nits, JSONLD VERIFY, JSONLD DONT VERIFY);
        if (var_.count (JSONLD EXTENSION)) c.jsonld_extension (var_ [JSONLD EXTENSION].as < vstr_t > ());
        else { vstr_t ex; ex.push_back (JSONLD_EXT); c.jsonld_extension (ex); }

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
        yea_nay (c, &context_t::revoke, nits, LINKS REVOKE, LINKS DONT REVOKE);
        yea_nay (c, &context_t::crosslinks, nits, LINKS XLINK, LINKS DONT XLINK);

        if (var_.count (MATH VERSION))
        {   ::std::string s = var_ [MATH VERSION].as < ::std::string > ();
            if (compare_no_case ("core", s)) c.math_version (math_core);
            else if ((s == "4") || (s == "4.22")) c.math_version (math_4_22);
            else if (s == "4.20") c.math_version (math_4_20);
            else if (s == "3") c.math_version (math_3);
            else if (s == "2") c.math_version (math_2);
            else if (s == "1") c.math_version (math_1);
            else if (s == "0") c.math_version (math_none);
            else 
            {   nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid MathML version");
                c.math_version (math_none); } }

        if (var_ [MATH CORE].as < bool > () && ! var_ [MATH DONT CORE].as < bool > ()) c.math_version (math_core);

        if (var_.count (MATH DRAFT))
        {   const int nn = var_ [MATH DRAFT].as < int > ();
            switch (nn)
            {   case 0 : break;
                case 2020: case 20 : if (c.math_version () > math_3) c.math_version (math_4_20); break;
                case 2022: case 22 : if (c.math_version () > math_3) c.math_version (math_4_22); break;
                default : nits.pick (nit_config_version, es_warning, ec_init, "ignoring invalid MathML 4 draft"); break; } }

        yea_nay (c, &context_t::mf_export, nits, MF EXPORT, MF DONT EXPORT);

        yea_nay (c, &context_t::md_export, nits, MICRODATA EXPORT, MICRODATA DONT EXPORT);
        yea_nay (c, &context_t::ontology, nits, MICRODATA VERIFY, MICRODATA DONT VERIFY);
        if (var_.count (MICRODATA ROOT)) c.export_root (nix_path_to_local (var_ [MICRODATA ROOT].as < ::std::string > ()));
        if (var_.count (MICRODATA VIRTUAL)) c.exports (var_ [MICRODATA VIRTUAL].as < vstr_t > ());

        if (var_.count (NITS CACHE)) c.cache (var_ [NITS CACHE].as < ::std::string > ());
        yea_nay (c, &context_t::nids, nits, NITS NIDS, NITS DONT NIDS);
        yea_nay (c, &context_t::extra, nits, NITS EXTRA, NITS DONT EXTRA);
        if (var_.count (NITS FORMAT)) c.nit_format (var_ [NITS FORMAT].as < ::std::string > ());
        if (var_.count (NITS QUOTE))
        {   const e_quote_style qs = examine_value < t_quote_style > (nits, html_default, var_ [NITS QUOTE].as < ::std::string > ());
            c.quote_style (qs); }
        yea_nay (c, &context_t::nits_nits_nits, nits, NITS UNIQUE, NITS DONT UNIQUE);
        yea_nay (c, &context_t::not_root, nits, NITS DONT ROOT, NITS ROOT); // note reversal
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
        yea_nay (c, &context_t::ontology, nits, ONTOLOGY VERIFY, ONTOLOGY DONT VERIFY);
        if (var_.count (ONTOLOGY ROOT)) c.export_root (nix_path_to_local (var_ [ONTOLOGY ROOT].as < ::std::string > ()));
        if (var_.count (ONTOLOGY VIRTUAL)) c.exports (var_ [ONTOLOGY VIRTUAL].as < vstr_t > ());

#ifdef BEASTIES
        yea_nay (c, &context_t::serve, nits, SERVER ENABLE, SERVER DONT ENABLE);
        if (var_.count (SERVER ACCEPT))
        {   ::std::string s = var_ [SERVER ACCEPT].as < ::std::string > ();
            if (s.empty ()) nits.pick (nit_bad_address, es_error, ec_init, SERVER ACCEPT " requires an ip address");
            else
            {   ::std::string::size_type pos = s.find_first_of (',');
                if (pos == ::std::string::npos) c.server_accept (nits, s);
                else if ((pos == 0) || (pos == s.length () - 1))
                    nits.pick (nit_bad_address, es_error, ec_init, "invalid address range; excepting addr,addr");
                else
                {   c.accept (s);
                    c.server_accept (nits, s.substr (0, pos), s.substr (pos+1)); } } }
        if (var_.count (SERVER ADDRESS)) c.server_address (nits, var_ [SERVER ADDRESS].as < ::std::string > ());
        if (var_.count (SERVER PORT)) c.server_port (nits, var_ [SERVER PORT].as < int > ());
        if (var_.count (SERVER ROOT)) c.server_root (nits, var_ [SERVER ROOT].as < ::std::string > ());
        if (var_.count (SERVER PARAMETERS)) c.server_parameters (nits, var_ [SERVER PARAMETERS].as < ::std::string > ());
        if (var_.count (SERVER PASSFILE)) c.server_passfile (nits, var_ [SERVER PASSFILE].as < ::std::string > ());
        if (var_.count (SERVER PASSWORD)) c.server_password (nits, var_ [SERVER PASSWORD].as < ::std::string > ());
        if (var_.count (SERVER PRIVATE)) c.server_private (nits, var_ [SERVER PRIVATE].as < ::std::string > ());
        if (var_.count (SERVER PUBLIC)) c.server_public (nits, var_ [SERVER PUBLIC].as < ::std::string > ());
#endif // BEASTIES

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
        if (var_.count (SHADOW ROOT)) c.shadow_root (nix_path_to_local (var_ [SHADOW ROOT].as < ::std::string > ()));
        yea_nay (c, &context_t::shadow_space, nits, SHADOW SPACING, SHADOW DONT SPACING);
        yea_nay (c, &context_t::shadow_ssi, nits, SHADOW SSI, SHADOW DONT SSI);
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
                if (! ::boost::filesystem::exists (hunspell)) { nits.pick (nit_no_spell, es_error, ec_init, "Cannot find ", hunspell.string ()); c.spell (false); }
                else if (! ::boost::filesystem::is_directory (hunspell)) { nits.pick (nit_no_spell, es_error, ec_init, hunspell.string (), " is not a directory"); c.spell (false); }
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
                    if (::boost::filesystem::exists (dd))
                        if (::boost::filesystem::is_directory (dd))
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

        if (var_ [STATS SELECTED].as <bool> ())
            c.stats (rcb_error, true).stats (rcb_file, true).stats (rcb_summary, true);

        if (var_ [STATS DONT ALL].as <bool> ()) c.stats_all (false);
        else if (var_ [STATS ALL].as <bool> ()) c.stats_all (true);
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
        if (var_.count (VALIDATION CHARSET)) type_master < t_charset > :: extend (var_ [VALIDATION CHARSET].as < vstr_t > ());
        if (var_.count (VALIDATION CLASS)) type_master < t_class > :: extend (var_ [VALIDATION CLASS].as < vstr_t > ());
        if (var_.count (VALIDATION COLOR)) type_master < t_fixedcolour > :: extend (var_ [VALIDATION COLOR].as < vstr_t > ());
        if (var_.count (VALIDATION COLOUR)) type_master < t_fixedcolour > :: extend (var_ [VALIDATION COLOUR].as < vstr_t > ());
        if (var_.count (VALIDATION COUNTRY)) type_master < t_country > :: extend (var_ [VALIDATION COUNTRY].as < vstr_t > ());
        if (var_.count (VALIDATION CURRENCY)) type_master < t_currency > :: extend (var_ [VALIDATION CURRENCY].as < vstr_t > ());
        if (var_.count (VALIDATION DINGBATARG)) type_master < t_dingbat > :: extend (var_ [VALIDATION DINGBATARG].as < vstr_t > ());
        if (var_.count (VALIDATION ELEMENT))
        {   const vstr_t& v = var_ [VALIDATION ELEMENT].as < vstr_t > (); add_elements (nits, v);  c.elem (v); }
        if (var_.count (VALIDATION ELEMATTR))
        {   const vstr_t& v = var_ [VALIDATION ELEMATTR].as < vstr_t > (); add_element_attributes (nits, v);  c.elem_attrib (v); }
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
    c.consolidate_jsonld ();
#ifdef NOCURL
    if (c.external ())
        nits.pick (nit_no_curl, es_warning, ec_init, "Unfortunately, this build of " PROG " cannot verify external links");
#endif // NOCURL
    var_.clear ();
    env_var_.clear (); }

void pvs (::std::ostringstream& res, const vstr_t& data)
{   for (auto i : data)
        res << i << " "; }

::std::string pvs (const vstr_t& data)
{   ::std::string res;
    for (auto i : data)
        res += i + " ";
    return res; }

::std::string gubbins (const char* section, int& count, const char* variable)
{   VERIFY_NOT_NULL (section, __FILE__, __LINE__);
    VERIFY_NOT_NULL (variable, __FILE__, __LINE__);
    ::std::string res;
    if (count++ == 0)
    {   ::std::string sect (section);
        const ::std::string::size_type pos = sect.length ();
        PRESUME (pos > 0, __FILE__, __LINE__);
        if (sect.at (pos - 1) == '.') sect = sect.substr (0, pos-1);
        res += "\n["; 
        res += sect;
        res += "]\n"; }
    res += variable;
    res += '=';
    return res; }

::std::string report_value (const char* section, int& count, const char* variable, const ::std::string& val)
{   return gubbins (section, count, variable) + val + "\n"; }

::std::string report_value (const char* section, int& count, const char* variable)
{   return gubbins (section, count, variable) + "\n"; }

template < class T > void options::report_variable (::std::ostringstream& res, const char* wot, const char* section, int& count, const char* variable) const
{   if (var_.count (wot)) try
    {   res << report_value (section, count, variable, var_ [wot].as < ::std::string > ()); }
    catch (...)
    {   outstr.err (section, wot, " is incompatible with ::std::string\n"); } }

template < > void options::report_variable < vstr_t > (::std::ostringstream& res, const char* wot, const char* section, int& count, const char* variable) const
{   if (var_.count (wot)) try
    {   res << report_value (section, count, variable, pvs (var_ [wot].as < vstr_t > ())); }
    catch (...)
    {   outstr.err (section, wot, " is no vstr_t\n"); } }

template < > void options::report_variable < bool > (::std::ostringstream& res, const char* wot, const char* section, int& count, const char* variable) const
{   if (var_.count (wot)) try
    {   if (var_ [wot].as < bool > ())
            res << report_value (section, count, variable); }
    catch (...)
    {   outstr.err (section, wot, " is no bool\n"); } }

void options::report_bool (::std::ostringstream& res, const char* yay, const char* nay, const char* section, int& count, const char* ja, const char* nein) const
{   
    report_variable < bool > (res, yay, section, count, ja);   
    report_variable < bool > (res, nay, section, count, nein); }

#define RB(RES,SECT,VAR,COUNT) report_bool (RES, SECT VAR, SECT DONT VAR, SECT, COUNT, VAR, DONT VAR)
#define RG(RES,TYPE,SECT,VAR,COUNT) report_variable < TYPE > (RES, SECT VAR, SECT, COUNT, VAR)
#define RI(RES,SECT,VAR,DEF,COUNT) \
    if (var_.count (SECT VAR)) \
        if (var_ [SECT VAR].as < ::std::string > () != DEF) \
            RG (res, ::std::string, SECT, VAR, COUNT);
#define RII(RES,SECT,VAR,DEF,COUNT) \
    if (var_.count (SECT VAR)) \
        if (var_ [SECT VAR].as < int > () != DEF) \
            RG (res, int, SECT, VAR, COUNT);
#define RP(RES,SECT,VAR,COUNT) \
    if (var_.count (SECT VAR)) \
        RG (res, ::std::string, SECT, "*****", COUNT);

::std::string options::report (const bool file) const
{   ::std::ostringstream res;
#ifndef EXPAND_TEST
    if (context.test ()) return res.str ();
#endif // EXPAND_TEST

    int corpus = 0, css = 0, env = 0, general = 0, html = 0, jsonld = 0, lynx = 0, math = 0, mf = 0, microdata = 0, nitty = 0,
        ontology = 0, shadow = 0, site = 0, spell = 0, ssc = 0, stats = 0, svg = 0, validate = 0;
#ifdef BEASTIES
    int server = 0;
#endif // BEASTIES

    if (file)
        res << report_value (PROG, ssc, VERSION, VERSION_STRING)
            << report_value (PROG, ssc, OPTBOOST, BOOST_LIB_VERSION)
            << report_value (PROG, ssc, OPTCOMP, COMPNAME)
#ifdef CURLY
            << report_value (PROG, ssc, OPTCURL, "yes")
#else // CURLY
            << report_value (PROG, ssc, OPTCURL, "no")
#endif // CURLY
#ifdef DEBUG
            << report_value (PROG, ssc, OPTDEBUG, "yes")
#else // DEBUG
            << report_value (PROG, ssc, OPTDEBUG, "no")
#endif // DEBUG
#ifdef FUDDY
            << report_value (PROG, ssc, OPTFUDDY, "yes")
#else // FUDDY
            << report_value (PROG, ssc, OPTFUDDY, "no")
#endif // FUDDY
#ifdef WX
            << report_value (PROG, ssc, OPTGUI, "yes")
#else // WX
            << report_value (PROG, ssc, OPTGUI, "no")
#endif // WX
            << report_value (PROG, ssc, OPTICU, U_ICU_VERSION)
#ifdef JSNIC
            << report_value (PROG, ssc, OPTJSON, "yes")
#else // JSNIC
            << report_value (PROG, ssc, OPTJSON, "no")
#endif // JSNIC
#ifdef NPS_GEN
            << report_value (PROG, ssc, OPTNPS, "yes")
#else // NPS_GEN
            << report_value (PROG, ssc, OPTNPS, "no")
#endif // NPS_GEN
            << report_value (PROG, ssc, OPTPROC, "x" PROCSIZE)
            << report_value (PROG, ssc, OPTOS, BUILD_OS)
#ifdef BEASTIES
#ifdef BEASTCHAR
            << report_value (PROG, ssc, OPTSERVER, "wide")
#else // BEASTCHAR
            << report_value (PROG, ssc, OPTSERVER, "narrow")
#endif // BEASTCHAR
#else // BEASTIES
            << report_value (PROG, ssc, OPTSERVER, "no")
#endif // BEASTIES
#ifdef SPELT
            << report_value (PROG, ssc, OPTSPELL, "yes")
#else // SPELT
            << report_value (PROG, ssc, OPTSPELL, "no")
#endif // SPELT
            ;
    else
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

        if (var_ [ASK].as < bool > ()) res << ASK "\n";
        if (var_ [DONT ASK].as < bool > ()) res << DONT ASK "\n";

        if (var_ [HELP].as < bool > ()) res << HELP "\n";
        if (var_ [VERSION].as < bool > ()) res << VERSION "\n"; }

    RB (res, CORPUS, ARTICLE, corpus);
    RB (res, CORPUS, BODY, corpus);
    RB (res, CORPUS, MAIN, corpus);
    RG (res, ::std::string, CORPUS, OUTPUT, corpus);
//    if (var_ [CORPUS ARTICLE].as < bool > ()) res << CORPUS ARTICLE "\n";
//    if (var_ [CORPUS DONT ARTICLE].as < bool > ()) res << CORPUS DONT ARTICLE "\n";
//    if (var_ [CORPUS BODY].as < bool > ()) res << CORPUS BODY "\n";
//    if (var_ [CORPUS DONT BODY].as < bool > ()) res << CORPUS DONT BODY "\n";
//    if (var_ [CORPUS MAIN].as < bool > ()) res << CORPUS MAIN "\n";
//    if (var_ [CORPUS DONT MAIN].as < bool > ()) res << CORPUS DONT MAIN "\n";
//    if (var_.count (CORPUS OUTPUT)) res << CORPUS OUTPUT ": " << var_ [CORPUS OUTPUT].as < ::std::string > () << "\n";

    RG (res, int, CSS, ADJUST, css);
    RG (res, int, CSS, ADVLAY, css);
    RG (res, int, CSS, ANCHOR, css);
    RG (res, int, CSS, ANCHOR_POS, css);
    RG (res, int, CSS, ANIMATION, css);
    RG (res, int, CSS, BACKGROUND, css);
    RG (res, int, CSS, BOX_ALIGN, css);
    RG (res, int, CSS, BOX_MODEL, css);
    RG (res, int, CSS, BOX_SIZING, css);
    RG (res, int, CSS, CASCADE, css);
    RG (res, int, CSS, COLOUR, css);
    RG (res, int, CSS, COMPOSITING, css);
    RG (res, int, CSS, COND_RULE, css);
    RG (res, int, CSS, CS, css);
    RG (res, int, CSS, CONTAIN, css);
    RG (res, int, CSS, CON_TENT, css);
    RG (res, int, CSS, CUSTOM, css);
    RG (res, int, CSS, DEVICE, css);
    RG (res, int, CSS, DISPLAY, css);
    RG (res, int, CSS, EASE, css);
    RG (res, int, CSS, EXCLUDE, css);
    RG (res, vstr_t, CSS, EXTENSION, css);
    RG (res, int, CSS, FBL, css);
    RG (res, int, CSS, FILL, css);
    RG (res, int, CSS, FILTER, css);
    RG (res, int, CSS, FLOAT, css);
    RG (res, int, CSS, FONT, css);
    RG (res, int, CSS, FRAG, css);
    RG (res, int, CSS, GRID, css);
    RG (res, int, CSS, HIGHLIGHT, css);
    RG (res, int, CSS, HYPERLINK, css);
    RG (res, int, CSS, IMAGE, css);                                                                                                                                         RG (res, int, CSS, INLINE, css);
    RG (res, int, CSS, LIST, css);
    RG (res, int, CSS, LINE_GRID, css);
    RG (res, int, CSS, LOGIC, css);
    RG (res, int, CSS, MARQUEE, css);
    RG (res, int, CSS, MASKING, css);
    RG (res, int, CSS, MEDIA, css);
    RB (res, CSS, MOBILE, css);
    RG (res, int, CSS, MOTION, css);
    RG (res, int, CSS, MULTI_COLUMN, css);
    RG (res, int, CSS, NAMESPACE, css);
    RG (res, int, CSS, NES, css);
    RG (res, int, CSS, NESTING, css);
    RG (res, int, CSS, OVERFLOH, css);
    RG (res, int, CSS, OVERSCROLL, css);
    RG (res, int, CSS, PAGE, css);
    RG (res, int, CSS, POSITION, css);
    RG (res, int, CSS, PRESENT, css);      
    RB (res, CSS, PRINT, css);
    RG (res, int, CSS, PSEUDO, css);
    RG (res, int, CSS, REGION, css);
    RG (res, int, CSS, RHYTHM, css);
    RG (res, int, CSS, ROUND, css);
    RG (res, int, CSS, RUBY, css);
    RG (res, int, CSS, SCOPE, css);
    RG (res, int, CSS, SCROLLBAR, css);
    RG (res, int, CSS, SDA, css);
    RG (res, int, CSS, SELECTOR, css);
    RG (res, int, CSS, SP, css);
    RG (res, int, CSS, SHAPE, css);
    RG (res, int, CSS, SPATIAL, css);
    RG (res, int, CSS, SPEECH, css);
    RG (res, int, CSS, SNAP, css);
    RG (res, int, CSS, SNAP_POINTS, css);                                                                                                                                   RG (res, int, CSS, STYLE, css);
    RG (res, int, CSS, SYNTAX, css);
    RG (res, int, CSS, TABLE, css);
    RG (res, int, CSS, TEXT_ARG, css);
    RG (res, int, CSS, TEXT_DEC, css);
    RG (res, int, CSS, TRANSFORM, css);
    RG (res, int, CSS, TRANSITION, css);
    RB (res, CSS, TV, css);
    RG (res, int, CSS, UI, css);
    RG (res, int, CSS, VAL, css);
    RB (res, CSS, VERIFY, css);
//    RG (res, int, CSS, VERSION, css);
    RG (res, ::std::string, CSS, VERSION, css);
    RG (res, int, CSS, VIEW, css);
    RG (res, int, CSS, VIEWPORT, css);
    RG (res, int, CSS, WRITING, css);
    RG (res, int, CSS, WC, css);
/*                                                                                                                                                                       ~                                                                                                                                                                       ~                                                                                                                                                                       ~                                                                                                                                                                       ~                                                                                                                                                                       ~                                                                                                                                                                       ~                                                                                                                                                                       ~                                                                                                                                                                       ~                                                                                                                                                                                                                                                                                                                             40,0-1        All 
    if (var_.count (CSS ADJUST)) res << CSS ADJUST ": " << var_ [CSS ADJUST].as < int > () << "\n";
    if (var_.count (CSS ADVLAY)) res << CSS ADVLAY ": " << var_ [CSS ADVLAY].as < int > () << "\n";
    if (var_.count (CSS ANCHOR)) res << CSS ANCHOR ": " << var_ [CSS ANCHOR].as < int > () << "\n";
    if (var_.count (CSS ANCHOR_POS)) res << CSS ANCHOR_POS ": " << var_ [CSS ANCHOR_POS].as < int > () << "\n";
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
    if (var_.count (CSS CON_TENT)) res << CSS CON_TENT ": " << var_ [CSS CON_TENT].as < int > () << "\n";
    if (var_.count (CSS CUSTOM)) res << CSS CUSTOM ": " << var_ [CSS CUSTOM].as < int > () << "\n";
    if (var_.count (CSS DEVICE)) res << CSS DEVICE ": " << var_ [CSS DEVICE].as < int > () << "\n";
    if (var_.count (CSS DISPLAY)) res << CSS DISPLAY ": " << var_ [CSS DISPLAY].as < int > () << "\n";
    if (var_.count (CSS EASE)) res << CSS EASE ": " << var_ [CSS EASE].as < int > () << "\n";
    if (var_.count (CSS EXCLUDE)) res << CSS EXCLUDE ": " << var_ [CSS EXCLUDE].as < int > () << "\n";
    if (var_.count (CSS EXTENSION)) { res << CSS EXTENSION ": "; pvs (res, var_ [CSS EXTENSION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (CSS FBL)) res << CSS FBL ": " << var_ [CSS FBL].as < int > () << "\n";
    if (var_.count (CSS FILL)) res << CSS FILL ": " << var_ [CSS FILL].as < int > () << "\n";
    if (var_.count (CSS FILTER)) res << CSS FILTER ": " << var_ [CSS FILTER].as < int > () << "\n";
    if (var_.count (CSS FLOAT)) res << CSS FLOAT ": " << var_ [CSS FLOAT].as < int > () << "\n";
    if (var_.count (CSS FONT)) res << CSS FONT ": " << var_ [CSS FONT].as < int > () << "\n";
    if (var_.count (CSS FRAG)) res << CSS FRAG ": " << var_ [CSS FRAG].as < int > () << "\n";
    if (var_.count (CSS GRID)) res << CSS GRID ": " << var_ [CSS GRID].as < int > () << "\n";
    if (var_.count (CSS HIGHLIGHT)) res << CSS HIGHLIGHT ": " << var_ [CSS HIGHLIGHT].as < int > () << "\n";
    if (var_.count (CSS HYPERLINK)) res << CSS HYPERLINK ": " << var_ [CSS HYPERLINK].as < int > () << "\n";
    if (var_.count (CSS IMAGE)) res << CSS IMAGE ": " << var_ [CSS IMAGE].as < int > () << "\n";
    if (var_.count (CSS INLINE)) res << CSS INLINE ": " << var_ [CSS INLINE].as < int > () << "\n";
    if (var_.count (CSS LIST)) res << CSS LIST ": " << var_ [CSS LIST].as < int > () << "\n";
    if (var_.count (CSS LINE_GRID)) res << CSS LINE_GRID ": " << var_ [CSS LINE_GRID].as < int > () << "\n";
    if (var_.count (CSS LOGIC)) res << CSS LOGIC ": " << var_ [CSS LOGIC].as < int > () << "\n";
    if (var_.count (CSS MARQUEE)) res << CSS MARQUEE ": " << var_ [CSS MARQUEE].as < int > () << "\n";
    if (var_.count (CSS MASKING)) res << CSS MASKING ": " << var_ [CSS MASKING].as < int > () << "\n";
    if (var_.count (CSS MEDIA)) res << CSS MEDIA ": " << var_ [CSS MEDIA].as < int > () << "\n";
    if (var_ [CSS MOBILE].as < bool > ()) res << CSS MOBILE ": " << var_ [CSS MOBILE].as < bool > () << "\n";
    if (var_ [CSS DONT MOBILE].as < bool > ()) res << CSS DONT MOBILE ": " << var_ [CSS DONT MOBILE].as < bool > () << "\n";
    if (var_.count (CSS MOTION)) res << CSS MOTION ": " << var_ [CSS MOTION].as < int > () << "\n";
    if (var_.count (CSS MULTI_COLUMN)) res << CSS MULTI_COLUMN ": " << var_ [CSS MULTI_COLUMN].as < int > () << "\n";
    if (var_.count (CSS NAMESPACE)) res << CSS NAMESPACE ": " << var_ [CSS NAMESPACE].as < int > () << "\n";
    if (var_.count (CSS NES)) res << CSS NES ": " << var_ [CSS NES].as < int > () << "\n";
    if (var_.count (CSS NESTING)) res << CSS NESTING ": " << var_ [CSS NESTING].as < int > () << "\n";
    if (var_.count (CSS OVERFLOH)) res << CSS OVERFLOH ": " << var_ [CSS OVERFLOH].as < int > () << "\n";
    if (var_.count (CSS OVERSCROLL)) res << CSS OVERSCROLL ": " << var_ [CSS OVERSCROLL].as < int > () << "\n";
    if (var_.count (CSS PAGE)) res << CSS PAGE ": " << var_ [CSS PAGE].as < int > () << "\n";
    if (var_.count (CSS POSITION)) res << CSS POSITION ": " << var_ [CSS POSITION].as < int > () << "\n";
    if (var_.count (CSS PRESENT)) res << CSS PRESENT ": " << var_ [CSS PRESENT].as < int > () << "\n";
    if (var_ [CSS PRINT].as < bool > ()) res << CSS PRINT ": " << var_ [CSS PRINT].as < bool > () << "\n";
    if (var_ [CSS DONT PRINT].as < bool > ()) res << CSS DONT PRINT ": " << var_ [CSS DONT PRINT].as < bool > () << "\n";
    if (var_.count (CSS PSEUDO)) res << CSS PSEUDO ": " << var_ [CSS PSEUDO].as < int > () << "\n";
    if (var_.count (CSS REGION)) res << CSS REGION ": " << var_ [CSS REGION].as < int > () << "\n";
    if (var_.count (CSS RHYTHM)) res << CSS RHYTHM ": " << var_ [CSS RHYTHM].as < int > () << "\n";
    if (var_.count (CSS ROUND)) res << CSS ROUND ": " << var_ [CSS ROUND].as < int > () << "\n";
    if (var_.count (CSS RUBY)) res << CSS RUBY ": " << var_ [CSS RUBY].as < int > () << "\n";
    if (var_.count (CSS SCOPE)) res << CSS SCOPE ": " << var_ [CSS SCOPE].as < int > () << "\n";
    if (var_.count (CSS SCROLLBAR)) res << CSS SCROLLBAR ": " << var_ [CSS SCROLLBAR].as < int > () << "\n";
    if (var_.count (CSS SDA)) res << CSS SDA ": " << var_ [CSS SDA].as < int > () << "\n";
    if (var_.count (CSS SELECTOR)) res << CSS SELECTOR ": " << var_ [CSS SELECTOR].as < int > () << "\n";
    if (var_.count (CSS SP)) res << CSS SP ": " << var_ [CSS SP].as < int > () << "\n";
    if (var_.count (CSS SHAPE)) res << CSS SHAPE ": " << var_ [CSS SHAPE].as < int > () << "\n";
    if (var_.count (CSS SPATIAL)) res << CSS SPATIAL ": " << var_ [CSS SPATIAL].as < int > () << "\n";
    if (var_.count (CSS SPEECH)) res << CSS SPEECH ": " << var_ [CSS SPEECH].as < int > () << "\n";
    if (var_.count (CSS SNAP)) res << CSS SNAP ": " << var_ [CSS SNAP].as < int > () << "\n";
    if (var_.count (CSS SNAP_POINTS)) res << CSS SNAP_POINTS ": " << var_ [CSS SNAP_POINTS].as < int > () << "\n";
    if (var_.count (CSS STYLE)) res << CSS STYLE ": " << var_ [CSS STYLE].as < int > () << "\n";
    if (var_.count (CSS SYNTAX)) res << CSS SYNTAX ": " << var_ [CSS SYNTAX].as < int > () << "\n";
    if (var_.count (CSS TABLE)) res << CSS TABLE ": " << var_ [CSS TABLE].as < int > () << "\n";
    if (var_.count (CSS TEXT_ARG)) res << CSS TEXT_ARG ": " << var_ [CSS TEXT_ARG].as < int > () << "\n";
    if (var_.count (CSS TEXT_DEC)) res << CSS TEXT_DEC ": " << var_ [CSS TEXT_DEC].as < int > () << "\n";
    if (var_.count (CSS TRANSFORM)) res << CSS TRANSFORM ": " << var_ [CSS TRANSFORM].as < int > () << "\n";
    if (var_.count (CSS TRANSITION)) res << CSS TRANSITION ": " << var_ [CSS TRANSITION].as < int > () << "\n";
    if (var_ [CSS TV].as < bool > ()) res << CSS TV ": " << var_ [CSS TV].as < bool > () << "\n";
    if (var_ [CSS DONT TV].as < bool > ()) res << CSS DONT TV ": " << var_ [CSS DONT TV].as < bool > () << "\n";
    if (var_.count (CSS UI)) res << CSS UI ": " << var_ [CSS UI].as < int > () << "\n";
    if (var_.count (CSS VAL)) res << CSS VAL ": " << var_ [CSS VAL].as < int > () << "\n";
    if (var_ [CSS VERIFY].as < bool > ()) res << CSS VERIFY ": " << var_ [CSS VERIFY].as < bool > () << "\n";
    if (var_ [CSS DONT VERIFY].as < bool > ()) res << CSS DONT VERIFY ": " << var_ [CSS DONT VERIFY].as < bool > () << "\n";
    if (var_.count (CSS VERSION)) res << CSS VERSION ": " << var_ [CSS VERSION].as < ::std::string > () << "\n";
    if (var_.count (CSS VIEW)) res << CSS VIEW ": " << var_ [CSS VIEW].as < int > () << "\n";
    if (var_.count (CSS VIEWPORT)) res << CSS VIEWPORT ": " << var_ [CSS VIEWPORT].as < int > () << "\n";
    if (var_.count (CSS WRITING)) res << CSS WRITING ": " << var_ [CSS WRITING].as < int > () << "\n";
    if (var_.count (CSS WC)) res << CSS WC ": " << var_ [CSS WC].as < int > () << "\n";
*/

    if (var_.count (ENVIRONMENT QUERY_STRING))
    {   RG (res, ::std::string, ENVIRONMENT, AUTH_TYPE, env);
        RG (res, ::std::string, ENVIRONMENT, CONTENT_TYPE, env);
        RG (res, ::std::string, ENVIRONMENT, CONTENT_LENGTH, env);
        RG (res, ::std::string, ENVIRONMENT, GATEWAY_INTERFACE, env);
        RG (res, ::std::string, ENVIRONMENT, HTTP_ACCEPT, env);
        RG (res, ::std::string, ENVIRONMENT, PATH_INFO, env);
        RG (res, ::std::string, ENVIRONMENT, PATH_TRANSLATED, env);
        if (file) RG (res, ::std::string, ENVIRONMENT, QUERY_STRING, env);
        RG (res, ::std::string, ENVIRONMENT, REMOTE_ADDR, env);
        RG (res, ::std::string, ENVIRONMENT, REMOTE_HOST, env);
        RG (res, ::std::string, ENVIRONMENT, REMOTE_USER, env);
        RG (res, ::std::string, ENVIRONMENT, REQUEST_METHOD, env);
        RG (res, ::std::string, ENVIRONMENT, SCRIPT_NAME, env);
        RG (res, ::std::string, ENVIRONMENT, SERVER_NAME, env);
        RG (res, ::std::string, ENVIRONMENT, SERVER_PORT, env);
        RG (res, ::std::string, ENVIRONMENT, SERVER_PROTOCOL, env);
        RG (res, ::std::string, ENVIRONMENT, SERVER_SOFTWARE, env);
        if (! file)
        {  ::std::string qs (var_ [ENVIRONMENT QUERY_STRING].as < ::std::string > ());
            res << ENVIRONMENT QUERY_STRING ": " << qs << "\n            : " << query_to_switches (qs) << "\n"; } }
/*
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
*/

    RB (res, GENERAL, CGI, general);
    RB (res, GENERAL, CLASS, general);
    RB (res, GENERAL, CLASSIC, general);
    RG (res, vstr_t, GENERAL, CUSTOM, general);
    RI (res, GENERAL, DATAPATH, def_path, general);
    RG (res, int, GENERAL, DEFTHRD, general);
    RG (res, ::std::string, GENERAL, WHOOPS, general);
    RG (res, vstr_t, GENERAL, ENVIRONMENT, general);
    RI (res, GENERAL, FICHIER, def_persisted, general);
    RB (res, GENERAL, INFO, general);
    RG (res, vstr_t, GENERAL, IGNORED, general);
    RG (res, ::std::string, GENERAL, LANG, general);
    RI (res, GENERAL, MACROEND, def_macroend, general);
    RI (res, GENERAL, MACROSTART, def_macrostart, general);
    RG (res, int, GENERAL, MAXFILESIZE, general);
    RB (res, GENERAL, PROGRESS, general);
    RB (res, GENERAL, RDFA, general);
    RB (res, GENERAL, REL, general);
    RB (res, GENERAL, RPT, general);
    RB (res, GENERAL, SLOVEN, general);
    RB (res, GENERAL, SPEC, general);
    RB (res, GENERAL, SSI, general);
    RB (res, GENERAL, TEST, general);
#ifndef NO_FRED
    RG (res, int, GENERAL, THREAD, general);
#endif // NO_FRED
    RB (res, GENERAL, VCS, general);
    RG (res, ::std::string, GENERAL, VERBOSE, general);
    RB (res, GENERAL, YGGDRISIL, general);
/*
    if (var_ [GENERAL CGI].as < bool > ()) res << GENERAL CGI "\n";
    if (var_ [GENERAL DONT CGI].as < bool > ()) res << GENERAL DONT CGI "\n";
    if (var_ [GENERAL CLASS].as < bool > ()) res << GENERAL CLASS "\n";
    if (var_ [GENERAL DONT CLASS].as < bool > ()) res << GENERAL DONT CLASS "\n";
    if (var_ [GENERAL CLASSIC].as < bool > ()) res << GENERAL CLASSIC "\n";
    if (var_ [GENERAL DONT CLASSIC].as < bool > ()) res << GENERAL DONT CLASSIC "\n";
    if (var_.count (GENERAL CUSTOM)) { res << GENERAL CUSTOM ": "; pvs (res, var_ [GENERAL CUSTOM].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL DATAPATH))
        if (var_ [GENERAL DATAPATH].as < ::std::string > () != def_path)
            res << GENERAL DATAPATH ": " << var_ [GENERAL DATAPATH].as < ::std::string > () << "\n";
    if (var_.count (GENERAL DEFTHRD)) res << GENERAL DEFTHRD ": " << var_ [GENERAL DEFTHRD].as < int > () << "\n";
    if (var_.count (GENERAL WHOOPS)) res << GENERAL WHOOPS ": " << var_ [GENERAL WHOOPS].as < ::std::string > () << "\n";
    if (var_.count (GENERAL ENVIRONMENT)) { res << GENERAL ENVIRONMENT ": "; pvs (res, var_ [GENERAL ENVIRONMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL EXCLUDE)) { res << GENERAL EXCLUDE ": "; pvs (res, var_ [GENERAL EXCLUDE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL FICHIER))
        if (var_ [GENERAL FICHIER].as < ::std::string > () != def_persisted)
            res << GENERAL FICHIER ": " << var_ [GENERAL FICHIER].as < ::std::string > () << "\n";
    if (var_ [GENERAL INFO].as < bool > ()) res << GENERAL INFO "\n";
    if (var_.count (GENERAL IGNORED)) { res << GENERAL IGNORED ": "; pvs (res, var_ [GENERAL IGNORED].as < vstr_t > ()); res << "\n"; }
    if (var_.count (GENERAL LANG)) res << GENERAL LANG ": " << var_ [GENERAL LANG].as < ::std::string > () << "\n";
    if (var_.count (GENERAL MACROEND))
        if (var_ [GENERAL MACROEND].as < ::std::string > () != def_macroend)
             res << GENERAL MACROEND ": " << var_ [GENERAL MACROEND].as < ::std::string > () << "\n";
    if (var_.count (GENERAL MACROSTART))
        if (var_ [GENERAL MACROSTART].as < ::std::string > () != def_macrostart)
            res << GENERAL MACROSTART ": " << var_ [GENERAL MACROSTART].as < ::std::string > () << "\n";
    if (var_.count (GENERAL MAXFILESIZE)) res << GENERAL MAXFILESIZE ": " << var_ [GENERAL MAXFILESIZE].as < int > () << "\n";
    if (var_ [GENERAL PROGRESS].as < bool > ()) res << GENERAL PROGRESS "\n";
    if (var_ [GENERAL DONT PROGRESS].as < bool > ()) res << GENERAL DONT PROGRESS "\n";
    if (var_ [GENERAL RDFA].as < bool > ()) res << GENERAL RDFA "\n";
    if (var_ [GENERAL DONT RDFA].as < bool > ()) res << GENERAL DONT RDFA "\n";
    if (var_ [GENERAL REL].as < bool > ()) res << GENERAL REL "\n";
    if (var_ [GENERAL DONT REL].as < bool > ()) res << GENERAL DONT REL "\n";
    if (var_ [GENERAL RPT].as < bool > ()) res << GENERAL RPT "\n";
    if (var_ [GENERAL DONT RPT].as < bool > ()) res << GENERAL DONT RPT "\n";
    if (var_ [GENERAL SLOVEN].as < bool > ()) res << GENERAL SLOVEN "\n";
    if (var_ [GENERAL DONT SLOVEN].as < bool > ()) res << GENERAL DONT SLOVEN "\n";
    if (var_ [GENERAL SPEC].as < bool > ()) res << GENERAL SPEC "\n";
    if (var_ [GENERAL SSI].as < bool > ()) res << GENERAL SSI "\n";
    if (var_ [GENERAL DONT SSI].as < bool > ()) res << GENERAL DONT SSI "\n";
    if (var_ [GENERAL TEST].as < bool > ()) res << GENERAL TEST "\n";
    if (var_ [GENERAL DONT TEST].as < bool > ()) res << GENERAL DONT TEST "\n";
#ifndef NO_FRED
    if (var_.count (GENERAL THREAD)) res << GENERAL THREAD ": " << var_ [GENERAL THREAD].as < int > () << "\n";
#endif // NO_FRED
    if (var_ [GENERAL VCS].as < bool > ()) res << GENERAL VCS "\n";
    if (var_.count (GENERAL VERBOSE)) res << GENERAL VERBOSE ": " << var_ [GENERAL VERBOSE].as < ::std::string > () << "\n";
    if (var_ [GENERAL YGGDRISIL].as < bool > ()) res << GENERAL YGGDRISIL "\n";
*/

    RG (res, vstr_t, HTML, CUSTOM, html);
    RB (res, HTML, FORCE, html);
    RB (res, HTML, IE, html);
    RG (res, vstr_t, HTML, IGNORED, html);
    RG (res, ::std::string, HTML, LANG, html);
    RB (res, HTML, REL, html);
    RB (res, HTML, RFC1867, html);
    RB (res, HTML, RFC1942, html);
    RB (res, HTML, RFC1980, html);
    RB (res, HTML, RFC2070, html);
    RB (res, HTML, RUBY, html);
    RB (res, HTML, SAFARI, html);
    RB (res, HTML, SLOVEN, html);
    RG (res, ::std::string, HTML, SNIPPET, html);
    RB (res, HTML, SSI, html);
    RB (res, HTML, TAGS, html);
    RII (res, HTML, TITLE, def_htmltitle, html);
    RG (res, ::std::string, HTML, VERSION, html);
/*
    if (var_.count (HTML CUSTOM)) { res << HTML CUSTOM ": "; pvs (res, var_ [HTML CUSTOM].as < vstr_t > ()); res << "\n"; }
    if (var_ [HTML FORCE].as < bool > ()) res << HTML FORCE "\n";
    if (var_ [HTML DONT FORCE].as < bool > ()) res << HTML DONT FORCE "\n";
    if (var_ [HTML IE].as < bool > ()) res << HTML IE "\n";
    if (var_ [HTML DONT IE].as < bool > ()) res << HTML DONT IE "\n";
    if (var_.count (HTML IGNORED)) { res << HTML IGNORED ": "; pvs (res, var_ [HTML IGNORED].as < vstr_t > ()); res << "\n"; }
    if (var_.count (HTML LANG)) res << HTML LANG ": " << var_ [HTML LANG].as < ::std::string > () << "\n";
    if (var_ [HTML REL].as < bool > ()) res << HTML REL "\n";
    if (var_ [HTML DONT REL].as < bool > ()) res << HTML DONT REL "\n";
    if (var_ [HTML RFC1867].as < bool > ()) res << HTML RFC1867 "\n";
    if (var_ [HTML DONT RFC1867].as < bool > ()) res << HTML DONT RFC1867 "\n";
    if (var_ [HTML RFC1942].as < bool > ()) res << HTML RFC1942 "\n";
    if (var_ [HTML DONT RFC1942].as < bool > ()) res << HTML DONT RFC1942 "\n";
    if (var_ [HTML RFC1980].as < bool > ()) res << HTML RFC1980 "\n";
    if (var_ [HTML DONT RFC1980].as < bool > ()) res << HTML DONT RFC1980 "\n";
    if (var_ [HTML RFC2070].as < bool > ()) res << HTML RFC2070 "\n";
    if (var_ [HTML DONT RFC2070].as < bool > ()) res << HTML DONT RFC2070 "\n";
    if (var_ [HTML RUBY].as < bool > ()) res << HTML RUBY "\n";
    if (var_ [HTML DONT RUBY].as < bool > ()) res << HTML DONT RUBY "\n";
    if (var_ [HTML SAFARI].as < bool > ()) res << HTML SAFARI "\n";
    if (var_ [HTML DONT SAFARI].as < bool > ()) res << HTML DONT SAFARI "\n";
    if (var_ [HTML SLOVEN].as < bool > ()) res << HTML SLOVEN "\n";
    if (var_ [HTML DONT SLOVEN].as < bool > ()) res << HTML DONT SLOVEN "\n";
    if (var_.count (HTML SNIPPET)) res << HTML SNIPPET ": " << var_ [HTML SNIPPET].as < ::std::string > () << "\n";
    if (var_ [HTML SSI].as < bool > ()) res << HTML SSI "\n";
    if (var_ [HTML DONT SSI].as < bool > ()) res << HTML DONT SSI "\n";
    if (var_ [HTML TAGS].as < bool > ()) res << HTML TAGS "\n";
    if (var_ [HTML DONT TAGS].as < bool > ()) res << HTML DONT TAGS "\n";
    if (var_.count (HTML TITLE))
        if (var_ [HTML TITLE].as < int > () != def_htmltitle)
            res << HTML TITLE ": " << var_ [HTML TITLE].as < int > () << "\n";
    if (var_.count (HTML VERSION)) res << HTML VERSION ": " << var_ [HTML VERSION].as < ::std::string > () << "\n";
*/

    RG (res, vstr_t, JSONLD, EXTENSION, jsonld);
    RB (res, JSONLD, VERIFY, jsonld);
    RG (res, ::std::string, JSONLD, VERSION, jsonld);
/*
    if (var_.count (JSONLD EXTENSION)) { res << JSONLD EXTENSION ": "; pvs (res, var_ [JSONLD EXTENSION].as < vstr_t > ()); res << "\n"; }
    if (var_ [JSONLD VERIFY].as < bool > ()) res << JSONLD VERIFY "\n";
    if (var_ [JSONLD DONT VERIFY].as < bool > ()) res << JSONLD DONT VERIFY "\n";
    if (var_.count (JSONLD VERSION)) res << JSONLD VERSION ": " << var_ [JSONLD VERSION].as < ::std::string > () << "\n";
*/

    RB (res, LINKS, CHECK, lynx);
    RB (res, LINKS, EXAMPLE, lynx);
    RB (res, LINKS, EXTERNAL, lynx);
    RB (res, LINKS, FORWARD, lynx);
    RG (res, vstr_t, LINKS, IGNORED, lynx);
    RB (res, LINKS, LOCAL, lynx);
    RB (res, LINKS, ONCE, lynx);
    RG (res, vstr_t, LINKS, PRETEND, lynx);
    RG (res, vstr_t, LINKS, REPORT, lynx);
    RB (res, LINKS, REVOKE, lynx);
    RB (res, LINKS, XLINK, lynx);
/*
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
    if (var_.count (LINKS PRETEND)) { res << LINKS PRETEND ": "; pvs (res, var_ [LINKS PRETEND].as < vstr_t > ()); res << "\n"; }
    if (var_.count (LINKS REPORT)) { res << LINKS REPORT ": "; pvs (res, var_ [LINKS REPORT].as < vstr_t > ()); res << "\n"; }
    if (var_ [LINKS REVOKE].as < bool > ()) res << LINKS REVOKE "\n";
    if (var_ [LINKS DONT REVOKE].as < bool > ()) res << LINKS DONT REVOKE "\n";
    if (var_ [LINKS XLINK].as < bool > ()) res << LINKS XLINK "\n";
    if (var_ [LINKS DONT XLINK].as < bool > ()) res << LINKS DONT XLINK "\n";

*/

    RB (res, MATH, CORE, math);
    RG (res, int, MATH, DRAFT, math);
    RG (res, int, MATH, VERSION, math);
/*
    if (var_ [MATH CORE].as < bool > ()) res << MATH CORE ": " << var_ [MATH CORE].as < bool > () << "\n";
    if (var_ [MATH DONT CORE].as < bool > ()) res << MATH DONT CORE ": " << var_ [MATH DONT CORE].as < bool > () << "\n";
    if (var_.count (MATH DRAFT)) res << MATH DRAFT ": " << var_ [MATH DRAFT].as < int > () << "\n";
    if (var_.count (MATH VERSION)) res << MATH VERSION ": " << var_ [MATH VERSION].as < int > () << "\n";

*/

    RB (res, MF, EXPORT, mf);
    RB (res, MF, VERIFY, mf);
    RG (res, int, MF, VERSION, mf);
/*
    if (var_ [MF EXPORT].as < bool > ()) res << MF EXPORT "\n";
    if (var_ [MF DONT EXPORT].as < bool > ()) res << MF DONT EXPORT "\n";
    if (var_ [MF VERIFY].as < bool > ()) res << MF VERIFY "\n";
    if (var_ [MF DONT VERIFY].as < bool > ()) res << MF DONT VERIFY "\n";
    if (var_.count (MF VERSION)) res << MF VERSION ": " << var_ [MF VERSION].as < int > () << "\n";
*/

    RB (res, MICRODATA, EXPORT, microdata);
    RB (res, MICRODATA, VERIFY, microdata);
    RG (res, ::std::string, MICRODATA, ROOT, microdata);
    RG (res, vstr_t, MICRODATA, VIRTUAL, microdata);
/*
    if (var_ [MICRODATA EXPORT].as < bool > ()) res << MICRODATA EXPORT "\n";
    if (var_ [MICRODATA DONT EXPORT].as < bool > ()) res << MICRODATA DONT EXPORT "\n";
    if (var_ [MICRODATA VERIFY].as < bool > ()) res << MICRODATA VERIFY "\n";
    if (var_ [MICRODATA DONT VERIFY].as < bool > ()) res << MICRODATA DONT VERIFY "\n";
    if (var_.count (MICRODATA ROOT)) res << MICRODATA ROOT ": " << var_ [MICRODATA ROOT].as < ::std::string > () << "\n";
    if (var_.count (MICRODATA VIRTUAL)) { res << MICRODATA VIRTUAL ": "; pvs (res, var_ [MICRODATA VIRTUAL].as < vstr_t > ()); res << "\n"; }

*/

    RG (res, vstr_t, NITS, ABHORRENT, nitty);
    RG (res, ::std::string, NITS, CACHE, nitty);
    RG (res, vstr_t, NITS, CATASTROPHE, nitty);
    RG (res, vstr_t, NITS, COMMENT, nitty);
    RG (res, vstr_t, NITS, DBG, nitty);
    RG (res, vstr_t, NITS, WHOOPS, nitty);
    RG (res, ::std::string, NITS, ERROREXIT, nitty);
    RB (res, NITS, EXTRA, nitty);
    RG (res, ::std::string, NITS, FORMAT, nitty);
    RG (res, vstr_t, NITS, INFO, nitty);
    RB (res, NITS, NIDS, nitty);
    RG (res, ::std::string, NITS, OVERRIDE, nitty);
    RG (res, vstr_t, NITS, SILENCE, nitty);
    RB (res, NITS, SPEC, nitty);
    RB (res, NITS, UNIQUE, nitty);
    RG (res, ::std::string, NITS, VERBOSE, nitty);
    RG (res, vstr_t, NITS, WARNING, nitty);
    RB (res, NITS, WATCH, nitty);
    RG (res, ::std::string, NITS, XXX, nitty);
/*
    if (var_.count (NITS ABHORRENT)) { res << NITS ABHORRENT ": "; pvs (res, var_ [NITS ABHORRENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS CACHE)) res << NITS CACHE ": " << var_ [NITS CACHE].as < ::std::string > () << "\n";
    if (var_.count (NITS CATASTROPHE)) { res << NITS CATASTROPHE ": "; pvs (res, var_ [NITS CATASTROPHE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS COMMENT)) { res << NITS COMMENT ": "; pvs (res, var_ [NITS COMMENT].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS DBG)) { res << NITS DBG ": "; pvs (res, var_ [NITS DBG].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS WHOOPS)) { res << NITS WHOOPS ": "; pvs (res, var_ [NITS WHOOPS].as < vstr_t > ()); res << "\n"; }
    if (var_.count (NITS ERROREXIT)) res << NITS ERROREXIT ": " << var_ [NITS ERROREXIT].as < ::std::string > () << "\n";
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
    if (var_.count (NITS VERBOSE)) res << NITS VERBOSE ": " << var_ [NITS VERBOSE].as < ::std::string > () << "\n";
    if (var_.count (NITS WARNING)) { res << NITS WARNING ": "; pvs (res, var_ [NITS WARNING].as < vstr_t > ()); res << "\n"; }
    if (var_ [NITS WATCH].as < bool > ()) res << NITS WATCH "\n";
    if (var_ [NITS DONT WATCH].as < bool > ()) res << NITS DONT WATCH "\n";
    if (var_.count (NITS XXX)) res << NITS XXX ": " << var_ [NITS XXX].as < ::std::string > () << "\n";
*/

    RB (res, ONTOLOGY, EXPORT, ontology);
    RB (res, ONTOLOGY, VERIFY, ontology);
    RG (res, ::std::string, ONTOLOGY, ROOT, ontology);
    RG (res, vstr_t, ONTOLOGY, VIRTUAL, ontology);
/*
    if (var_ [ONTOLOGY EXPORT].as < bool > ()) res << ONTOLOGY EXPORT "\n";
    if (var_ [ONTOLOGY DONT EXPORT].as < bool > ()) res << ONTOLOGY DONT EXPORT "\n";
    if (var_ [ONTOLOGY VERIFY].as < bool > ()) res << ONTOLOGY VERIFY "\n";
    if (var_ [ONTOLOGY DONT VERIFY].as < bool > ()) res << ONTOLOGY DONT VERIFY "\n";
    if (var_.count (ONTOLOGY ROOT)) res << ONTOLOGY ROOT ": " << var_ [ONTOLOGY ROOT].as < ::std::string > () << "\n";
    if (var_.count (ONTOLOGY VIRTUAL)) { res << ONTOLOGY VIRTUAL ": "; pvs (res, var_ [ONTOLOGY VIRTUAL].as < vstr_t > ()); res << "\n"; }

*/

    for (int i = s_none + 1; i < s_error; ++i)
    {   const e_ontology es = static_cast < e_ontology > (i);
        if (is_faux_schema (es)) continue;
        if (get_ontology_version_count (es) < 2) continue;
        const ::std::string naam (ontology_names.get (es, ONTOLOGY_NAME));
        ::std::string arg (ONTOLOGY);
        arg += naam;
        if (var_.count (arg))
            res << report_value (ONTOLOGY, ontology, naam.c_str (), var_ [arg].as < ::std::string > ()); }
//            res << arg << ": " << var_ [arg].as < ::std::string > () << "\n"; }

#ifdef BEASTIES
    RG (res, ::std::string, SERVER, ACCEPT, server);
    RG (res, ::std::string, SERVER, ADDRESS, server);
    RB (res, SERVER, ENABLE, server);
    RP (res, SERVER, PARAMETERS, server);
    RP (res, SERVER, PASSFILE, server);
    RP (res, SERVER, PASSWORD, server);
    RG (res, ::std::string, SERVER, PORT, server);
    RP (res, SERVER, PRIVATE, server);
    RP (res, SERVER, PUBLIC, server);
    RG (res, ::std::string, SERVER, ROOT, server);
/*
    if (var_.count (SERVER ACCEPT)) res << SERVER ACCEPT ": " << var_ [SERVER ACCEPT].as < ::std::string > () << "\n";
    if (var_.count (SERVER ADDRESS)) res << SERVER ADDRESS ": " << var_ [SERVER ADDRESS].as < ::std::string > () << "\n";
    if (var_ [SERVER ENABLE].as < bool > ()) res << SERVER ENABLE "\n";
    if (var_ [SERVER DONT ENABLE].as < bool > ()) res << SERVER DONT ENABLE "\n";
    if (var_.count (SERVER PARAMETERS)) res << SERVER PARAMETERS ": provided\n";
    if (var_.count (SERVER PASSFILE)) res << SERVER PASSFILE ": provided\n";
    if (var_.count (SERVER PASSWORD)) res << SERVER PASSWORD ": provided\n";
    if (var_.count (SERVER PORT)) res << SERVER PORT ": " << var_ [SERVER PORT].as < ::std::string > () << "\n";
    if (var_.count (SERVER PRIVATE)) res << SERVER PRIVATE ": provided\n";
    if (var_.count (SERVER PUBLIC)) res << SERVER PUBLIC ": provided\n";
    if (var_.count (SERVER ROOT)) res << SERVER ROOT ": " << var_ [SERVER ROOT].as < ::std::string > () << "\n";
*/
#endif // BEASTIES

    RB (res, SHADOW, CHANGED, shadow);
    RB (res, SHADOW, COMMENT, shadow);
    RG (res, ::std::string, SHADOW, COPY, shadow);
    RB (res, SHADOW, ENABLE, shadow);
    RG (res, ::std::string, SHADOW, FICHIER, shadow);
    RG (res, vstr_t, SHADOW, IGNORED, shadow);
    RB (res, SHADOW, INFO, shadow);
    RG (res, ::std::string, SHADOW, MSG, shadow);
    RG (res, ::std::string, SHADOW, ROOT, shadow);
    RB (res, SHADOW, SPACING, shadow);
    RB (res, SHADOW, SSI, shadow);
    RB (res, SHADOW, UPDATE, shadow);
    RG (res, vstr_t, SHADOW, VIRTUAL, shadow);
/*
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
*/

    RG (res, ::std::string, WEBSITE, EXTENSION, site);
    RG (res, ::std::string, WEBSITE, INDEX, site);
    RG (res, vstr_t, WEBSITE, SITE, site);
    RG (res, ::std::string, WEBSITE, ROOT, site);
    RG (res, vstr_t, WEBSITE, VIRTUAL, site);
/*
    if (var_.count (WEBSITE EXTENSION)) { res << WEBSITE EXTENSION ": "; pvs (res, var_ [WEBSITE EXTENSION].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WEBSITE INDEX)) res << WEBSITE INDEX ": " << var_ [WEBSITE INDEX].as < ::std::string > () << "\n";
    if (var_.count (WEBSITE SITE)) { res << WEBSITE SITE ": "; pvs (res, var_ [WEBSITE SITE].as < vstr_t > ()); res << "\n"; }
    if (var_.count (WEBSITE ROOT)) res << WEBSITE ROOT ": " << var_ [WEBSITE ROOT].as < ::std::string > () << "\n";
    if (var_.count (WEBSITE VIRTUAL)) { res << WEBSITE VIRTUAL ": "; pvs (res, var_ [WEBSITE VIRTUAL].as < vstr_t > ()); res << "\n"; }
*/

#ifndef NOSPELL
    RG (res, vstr_t, SPELL, ACCEPT, spell);
    RB (res, SPELL, CASED, spell);
    RB (res, SPELL, CHECK, spell);
    RG (res, vstr_t, SPELL, DICT, spell);
    RB (res, SPELL, ICU, spell);
    RG (res, vstr_t, SPELL, LIST, spell);
    RG (res, ::std::string, SPELL, PATH, spell);
/*
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
*/
#endif // NOSPELL

    RB (res, STATS, ABBR, stats);
    RB (res, STATS, ALL, stats);
    RB (res, STATS, ANNOTATION, stats);
    RB (res, STATS, ATTRIB, stats);
    RB (res, STATS, CAT, stats);
    RB (res, STATS, CHARVAR, stats);
    RB (res, STATS, CLASS, stats);
    RB (res, STATS, CONNAME, stats);
    RB (res, STATS, COUSTYLE, stats);
    RB (res, STATS, CSSPROP, stats);
    RB (res, STATS, CUSTMED, stats);
    RB (res, STATS, CUSTPROP, stats);
    RB (res, STATS, DFN, stats);
    RB (res, STATS, DTDD, stats);
    RB (res, STATS, ELEMENT, stats);
    RB (res, STATS, WHOOPS, stats);
    RG (res, ::std::string, STATS, EXPORT, stats);
    RB (res, STATS, FICHIER, stats);
    RB (res, STATS, FONT, stats);
    RB (res, STATS, FONT_FAMILY, stats);
    RB (res, STATS, HIGHLIGHT, stats);
    RB (res, STATS, HISTFORM, stats);
    RB (res, STATS, ID, stats);
    RB (res, STATS, ITEMID, stats);
    RB (res, STATS, KEYFRAME, stats);
    RB (res, STATS, LAYER, stats);
    RB (res, STATS, META, stats);
    RB (res, STATS, ONT, stats);
    RB (res, STATS, ORNAMENT, stats);
    RB (res, STATS, PAGE, stats);
    RB (res, STATS, PAGE_NAME, stats);
    RB (res, STATS, PALETTE, stats);
    RB (res, STATS, PROPER, stats);
    RB (res, STATS, REFERENCE, stats);
    RB (res, STATS, REGION, stats);
    RB (res, STATS, SCROLL_ANIM, stats);
    RB (res, STATS, SELECTED, stats);
    RB (res, STATS, STATEMENT, stats);
    RB (res, STATS, STYLESET, stats);
    RB (res, STATS, STYLISTIC, stats);
    RB (res, STATS, SUMMARY, stats);
    RB (res, STATS, SWASH, stats);
    RB (res, STATS, VERSION, stats);
    RB (res, STATS, VIEW, stats);
/*
    if (var_ [STATS ABBR].as < bool > ()) res << STATS ABBR "\n";
    if (var_ [STATS DONT ABBR].as < bool > ()) res << STATS DONT ABBR "\n";
    if (var_ [STATS ALL].as < bool > ()) res << STATS ALL "\n";
    if (var_ [STATS DONT ALL].as < bool > ()) res << STATS DONT ALL "\n";
    if (var_ [STATS ANNOTATION].as < bool > ()) res << STATS ANNOTATION "\n";
    if (var_ [STATS DONT ANNOTATION].as < bool > ()) res << STATS DONT ANNOTATION "\n";
    if (var_ [STATS ATTRIB].as < bool > ()) res << STATS ATTRIB "\n";
    if (var_ [STATS DONT ATTRIB].as < bool > ()) res << STATS DONT ATTRIB "\n";
    if (var_ [STATS CAT].as < bool > ()) res << STATS CAT "\n";
    if (var_ [STATS DONT CAT].as < bool > ()) res << STATS DONT CAT "\n";
    if (var_ [STATS CHARVAR].as < bool > ()) res << STATS CHARVAR "\n";
    if (var_ [STATS DONT CHARVAR].as < bool > ()) res << STATS DONT CHARVAR "\n";
    if (var_ [STATS CLASS].as < bool > ()) res << STATS CLASS "\n";
    if (var_ [STATS DONT CLASS].as < bool > ()) res << STATS DONT CLASS "\n";
    if (var_ [STATS CONNAME].as < bool > ()) res << STATS CONNAME "\n";
    if (var_ [STATS DONT CONNAME].as < bool > ()) res << STATS DONT CONNAME "\n";
    if (var_ [STATS COUSTYLE].as < bool > ()) res << STATS COUSTYLE "\n";
    if (var_ [STATS DONT COUSTYLE].as < bool > ()) res << STATS DONT COUSTYLE "\n";
    if (var_ [STATS CSSPROP].as < bool > ()) res << STATS CSSPROP "\n";
    if (var_ [STATS DONT CSSPROP].as < bool > ()) res << STATS DONT CSSPROP "\n";
    if (var_ [STATS CUSTMED].as < bool > ()) res << STATS CUSTMED "\n";
    if (var_ [STATS DONT CUSTMED].as < bool > ()) res << STATS DONT CUSTMED "\n";
    if (var_ [STATS CUSTPROP].as < bool > ()) res << STATS CUSTPROP "\n";
    if (var_ [STATS DONT CUSTPROP].as < bool > ()) res << STATS DONT CUSTPROP "\n";
    if (var_ [STATS DFN].as < bool > ()) res << STATS DFN "\n";
    if (var_ [STATS DONT DFN].as < bool > ()) res << STATS DONT DFN "\n";
    if (var_ [STATS DTDD].as < bool > ()) res << STATS DTDD "\n";
    if (var_ [STATS DONT DTDD].as < bool > ()) res << STATS DONT DTDD "\n";
    if (var_ [STATS ELEMENT].as < bool > ()) res << STATS ELEMENT "\n";
    if (var_ [STATS DONT ELEMENT].as < bool > ()) res << STATS DONT ELEMENT "\n";
    if (var_ [STATS WHOOPS].as < bool > ()) res << STATS WHOOPS "\n";
    if (var_ [STATS DONT WHOOPS].as < bool > ()) res << STATS DONT WHOOPS "\n";
    if (var_.count (STATS EXPORT)) res << STATS EXPORT ": " << var_ [STATS EXPORT].as < ::std::string > () << "\n";
    if (var_ [STATS FICHIER].as < bool > ()) res << STATS FICHIER "\n";
    if (var_ [STATS DONT FICHIER].as < bool > ()) res << STATS DONT FICHIER "\n";
    if (var_ [STATS FONT].as < bool > ()) res << STATS FONT "\n";
    if (var_ [STATS DONT FONT].as < bool > ()) res << STATS DONT FONT "\n";
    if (var_ [STATS FONT_FAMILY].as < bool > ()) res << STATS FONT_FAMILY "\n";
    if (var_ [STATS DONT FONT_FAMILY].as < bool > ()) res << STATS DONT FONT_FAMILY "\n";
    if (var_ [STATS HIGHLIGHT].as < bool > ()) res << STATS HIGHLIGHT "\n";
    if (var_ [STATS DONT HIGHLIGHT].as < bool > ()) res << STATS DONT HIGHLIGHT "\n";
    if (var_ [STATS HISTFORM].as < bool > ()) res << STATS HISTFORM "\n";
    if (var_ [STATS DONT HISTFORM].as < bool > ()) res << STATS DONT HISTFORM "\n";
    if (var_ [STATS ID].as < bool > ()) res << STATS ID "\n";
    if (var_ [STATS DONT ID].as < bool > ()) res << STATS DONT ID "\n";
    if (var_ [STATS ITEMID].as < bool > ()) res << STATS ITEMID "\n";
    if (var_ [STATS DONT ITEMID].as < bool > ()) res << STATS DONT ITEMID "\n";
    if (var_ [STATS KEYFRAME].as < bool > ()) res << STATS KEYFRAME "\n";
    if (var_ [STATS DONT KEYFRAME].as < bool > ()) res << STATS DONT KEYFRAME "\n";
    if (var_ [STATS LAYER].as < bool > ()) res << STATS LAYER "\n";
    if (var_ [STATS DONT LAYER].as < bool > ()) res << STATS DONT LAYER "\n";
    if (var_ [STATS META].as < bool > ()) res << STATS META "\n";
    if (var_ [STATS DONT META].as < bool > ()) res << STATS DONT META "\n";
    if (var_ [STATS ONT].as < bool > ()) res << STATS ONT "\n";
    if (var_ [STATS DONT ONT].as < bool > ()) res << STATS DONT ONT "\n";
    if (var_ [STATS ORNAMENT].as < bool > ()) res << STATS ORNAMENT "\n";
    if (var_ [STATS DONT ORNAMENT].as < bool > ()) res << STATS DONT ORNAMENT "\n";
    if (var_ [STATS PAGE].as < bool > ()) res << STATS PAGE "\n";
    if (var_ [STATS DONT PAGE].as < bool > ()) res << STATS DONT PAGE "\n";
    if (var_ [STATS PAGE_NAME].as < bool > ()) res << STATS PAGE_NAME "\n";
    if (var_ [STATS DONT PAGE_NAME].as < bool > ()) res << STATS DONT PAGE_NAME "\n";
    if (var_ [STATS PALETTE].as < bool > ()) res << STATS PALETTE "\n";
    if (var_ [STATS DONT PALETTE].as < bool > ()) res << STATS DONT PALETTE "\n";
    if (var_ [STATS PROPER].as < bool > ()) res << STATS PROPER "\n";
    if (var_ [STATS DONT PROPER].as < bool > ()) res << STATS DONT PROPER "\n";
    if (var_ [STATS REFERENCE].as < bool > ()) res << STATS REFERENCE "\n";
    if (var_ [STATS DONT REFERENCE].as < bool > ()) res << STATS DONT REFERENCE "\n";
    if (var_ [STATS REGION].as < bool > ()) res << STATS REGION "\n";
    if (var_ [STATS DONT REGION].as < bool > ()) res << STATS DONT REGION "\n";
    if (var_ [STATS SCROLL_ANIM].as < bool > ()) res << STATS SCROLL_ANIM "\n";
    if (var_ [STATS DONT SCROLL_ANIM].as < bool > ()) res << STATS DONT SCROLL_ANIM "\n";
    if (var_ [STATS SELECTED].as < bool > ()) res << STATS SELECTED "\n";
    if (var_ [STATS STATEMENT].as < bool > ()) res << STATS STATEMENT "\n";
    if (var_ [STATS DONT STATEMENT].as < bool > ()) res << STATS DONT STATEMENT "\n";
    if (var_ [STATS STYLESET].as < bool > ()) res << STATS STYLESET "\n";
    if (var_ [STATS DONT STYLESET].as < bool > ()) res << STATS DONT STYLESET "\n";
    if (var_ [STATS STYLISTIC].as < bool > ()) res << STATS STYLISTIC "\n";
    if (var_ [STATS DONT STYLISTIC].as < bool > ()) res << STATS DONT STYLISTIC "\n";
    if (var_ [STATS SUMMARY].as < bool > ()) res << STATS SUMMARY "\n";
    if (var_ [STATS DONT SUMMARY].as < bool > ()) res << STATS DONT SUMMARY "\n";
    if (var_ [STATS SWASH].as < bool > ()) res << STATS SWASH "\n";
    if (var_ [STATS DONT SWASH].as < bool > ()) res << STATS DONT SWASH "\n";
    if (var_ [STATS VERSION].as < bool > ()) res << STATS VERSION "\n";
    if (var_ [STATS DONT VERSION].as < bool > ()) res << STATS DONT VERSION "\n";
    if (var_ [STATS VIEW].as < bool > ()) res << STATS VIEW "\n";
    if (var_ [STATS DONT VIEW].as < bool > ()) res << STATS DONT VIEW "\n";
    if (var_.count (SVG VERSION)) res << SVG VERSION ": " << var_ [SVG VERSION].as < ::std::string > () << "\n";

*/

    RG (res, ::std::string, SVG, VERSION, svg);
//    if (var_.count (SVG VERSION)) res << SVG VERSION ": " << var_ [SVG VERSION].as < ::std::string > () << "\n";

    RG (res, vstr_t, VALIDATION, ATTRIB, validate);
    RG (res, vstr_t, VALIDATION, CHARSET, validate);
    RG (res, vstr_t, VALIDATION, CLASS, validate);
    RG (res, vstr_t, VALIDATION, COLOR, validate);
    RG (res, vstr_t, VALIDATION, COLOUR, validate);
    RG (res, vstr_t, VALIDATION, COUNTRY, validate);
    RG (res, vstr_t, VALIDATION, CURRENCY, validate);
    RG (res, vstr_t, VALIDATION, DINGBATARG, validate);
    RG (res, vstr_t, VALIDATION, ELEMENT, validate);
    RG (res, vstr_t, VALIDATION, ELEMATTR, validate);
    RG (res, vstr_t, VALIDATION, EXTENSION, validate);
    RG (res, vstr_t, VALIDATION, FF, validate);
    RG (res, vstr_t, VALIDATION, FV, validate);
    RG (res, vstr_t, VALIDATION, HTTPEQUIV, validate);
    RG (res, vstr_t, VALIDATION, LANG, validate);
    RG (res, int, VALIDATION, MINOR, validate);
    RG (res, vstr_t, VALIDATION, METANAME, validate);
    RB (res, VALIDATION, MICRODATAARG, validate);
    RG (res, vstr_t, VALIDATION, MIMETYPE, validate);
    RG (res, vstr_t, VALIDATION, REL, validate);
    RG (res, vstr_t, VALIDATION, SGML, validate);
/*
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
*/

#define RPT_VAR(XX) RG (res, vstr_t, VALIDATION, #XX, validate)
// #define RPT_VAR(XX) if (var_.count (VALIDATION #XX)) { res << VALIDATION #XX ": "; pvs (res, var_ [VALIDATION #XX].as < vstr_t > ()); res << "\n"; }
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
    RPT_VAR (tld);
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
#undef RB
#undef RG
#undef RI
#undef RII

    return res.str (); }

bool options::write (nitpick& nits, const ::boost::filesystem::path& fn) const
{   const ::std::string s (report (true));
    return write_text_file (nits, fn, s); }
