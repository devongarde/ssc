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
#include "feedback/nitpick.h"
#include "feedback/nitout.h"
#include "main/output.h"
#include "stats/stats.h"
#include "parser/html_version.h"
#include "ontology/ontology_version.h"

#define STOP_NOW -1
#define VALID_RESULT 0
#define STOP_OK 1
#define NOTHING_TO_DO 2
#define ERROR_STATE 3
#define CATASTROPHIC_STATE 4
#define DEFAULT_MAX_FILE_SIZE 4
#define DMFS_BYTES (DEFAULT_MAX_FILE_SIZE * 1024 * 1024)


CONSTEXPR e_severity default_output = es_warning;
CONSTEXPR bool def_absolute_path = true, def_article = false, def_body = true, def_case = false, def_cgi = false, def_chrome = false,
    def_classic = false, def_clear = false, def_comms = true, def_crosslinks = true, def_expand = false, def_example = true,
    def_excl = true, def_external = false, def_ext_css = false, def_extra = false, def_force_version = false, def_forwarded = true,
    def_gui = false, def_icu = true, def_ie = false, def_info = false, def_iterate = false, def_jsonld = false, def_local = true,
    def_links = true, def_load_css = true, def_load_vtt = true, def_main = false, def_md_export = false, def_md_pretty = true,
    def_meta_all = true, def_meta_sign = true, def_mf_export = false, def_mf_pretty = true, def_mf_verify = true, def_microdata = true,
    def_mozilla = false, def_netscape = false, def_nids = false, def_nits = false, def_nits_nits_nits = false, def_not_root = false,
    def_opera = false, def_once = true, def_presume_tags = false, def_pretty = true, def_progress = false, def_rdfa = false, def_rel = false,
    def_revoke = false, def_rfc_1867 = true, def_rfc_1942 = true, def_rfc_1980 = true, def_rfc_2070 = true, def_rpt_opens = false,
    def_ruby = false, def_ontology = true, def_safari = false, def_serve = false, def_shadow_changed = false, def_shadow_comment = true,
    def_shadow_enable = false, def_shadow_space = true, def_shadow_ssi = true, def_sloven = false, def_spec = false, def_special = true,
    def_spell = true, def_spell_deduced = false, def_ssi = true, def_ssi_exec_run = false, def_test = false, def_unknown_class = true,
    def_update = false, def_valid = false, def_vcs = false, def_versioned = false, def_wx = false, def_yggdrisil = false;
CONSTEXPR const char* const def_macrostart = "{{";
CONSTEXPR const char* const def_macroend = "}}";
CONSTEXPR const char* const def_path = DEF_DATAPATH;
CONSTEXPR const char* const def_persisted = PROG DEF_PERSIST_EXT;
CONSTEXPR ::std::size_t def_htmltitle = MAX_IDEAL_TITLE_LENGTH;
CONSTEXPR ::std::size_t def_fred = 1;
CONSTEXPR unsigned char def_mf = 3;
CONSTEXPR long def_max_file_size = DMFS_BYTES;
CONSTEXPR const char* const def_css_ext = CSS_EXT;
CONSTEXPR const char* const def_html_ext = HTML_EXT;
CONSTEXPR const char* const def_jsonld_ext = JSONLD_EXT;

class context_t
{   friend class options;
    bool            absolute_path_ = def_absolute_path, article_ = def_article, body_ = def_body, case_ = def_case, cgi_ = def_cgi, chrome_ = def_chrome,
                    classic_ = def_classic, clear_ = def_clear, comms_ = def_comms, crosslinks_ = def_crosslinks, example_ = def_example,
                    excl_ = def_excl, expand_ = def_expand, external_ = def_external, ext_css_ = def_ext_css, extra_ = def_extra,
                    force_version_ = def_force_version, forwarded_ = def_forwarded, gui_ = def_gui, icu_ = def_icu, ie_ = def_ie,
                    info_ = def_info, iterate_ = def_iterate, jsonld_ = def_jsonld, local_ = def_local, load_css_ = def_load_css,
                    load_vtt_ = def_load_vtt,links_ = def_links, main_ = def_main, md_export_ = def_md_export, md_pretty_ = def_md_pretty,
                    output_sign_ = def_meta_sign, mf_export_ = def_mf_export, mf_pretty_ = def_mf_pretty, mf_verify_ = def_mf_verify,
                    microdata_ = def_microdata, mozilla_ = def_mozilla, netscape_ = def_netscape, nids_ = def_nids, nits_ = def_nits,
                    nits_nits_nits_ = def_nits_nits_nits, not_root_ = def_not_root, once_ = def_once, ontology_ = def_ontology,
                    opera_ = def_opera, presume_tags_ = def_presume_tags, pretty_ = def_pretty, progress_ = def_progress,
                    rdfa_ = def_rdfa, rel_ = def_rel, revoke_ = def_revoke, rfc_1867_ = def_rfc_1867, rfc_1942_ = def_rfc_1942,
                    rfc_1980_ = def_rfc_1980, rfc_2070_ = def_rfc_2070, rpt_opens_ = def_rpt_opens, ruby_ = def_ruby,
                    safari_ = def_safari, serve_ = def_serve, shadow_changed_ = def_shadow_changed, shadow_comment_ = def_shadow_comment,
                    shadow_enable_ = def_shadow_enable, shadow_space_ = def_shadow_space, shadow_ssi_ = def_shadow_ssi,
                    sloven_ = def_sloven, spec_ = def_spec, special_ = def_special, spell_ = def_spell,
                    spell_deduced_ = def_spell_deduced, ssi_ = def_ssi, ssi_exec_run_ = def_ssi_exec_run, test_ = def_test,
                    unknown_class_ = def_unknown_class, update_ = def_update, valid_ = def_valid, vcs_ = def_vcs,
                    versioned_ = def_versioned, wx_ = def_wx, yggdrisil_ = def_yggdrisil;
    ::std::size_t   fred_ = def_fred, title_ = def_htmltitle;
    e_copy          copy_ = c_none;
    unsigned char   mf_version_ = def_mf;
    html_version    version_;
    long            max_file_size_ = def_max_file_size;
    e_severity      report_error_ = es_error, verbose_ = default_output;
    ::std::string   accept_, account_, build_, cache_, domsg_, export_root_, general_info_, help_, index_, lang_, macro_end_ = def_macroend,
                    macro_start_ = def_macrostart, msg_, out_, output_format_, output_override_, output_time_, path_ = def_path, persisted_,
                    root_, secret_, shadow_, shadow_persist_, snippet_, ssi_doc_args_, ssi_echomsg_, ssi_errmsg_, ssi_exec_text_, ssi_query_string_,
                    ssi_timefmt_, ssi_user_name_, started_, stats_, svg_, username_, wx_snippet_, x_;
    ::boost::filesystem::path config_, corpus_, proot_, spell_path_, def_conf_path_, def_conf_file_;
    static ::boost::filesystem::path cwd_;
    vstr_t          abhorrent_, attrib_, catastrophe_, cmd_, comment_, css_ext_ = { CSS_EXT }, custom_elements_, debug_,
                    dict_, dlang_, elem_, elem_attrib_, environment_, error_, exclude_, exports_, extensions_ = { HTML_EXT },
                    inform_, ignore_, jsonld_ext_, jsonld_key_, jsonld_ont_, jsonld_val_, output_description_, no_ex_check_ = { JSONLD_EXT },
                    pretend_, report_, shadow_ignore_, shadows_, silent_, site_, spell_list_, spellings_, vtt_ext_ = { VTT_EXT },
                    warning_, virtuals_, vont_;
    vvstr_t         vvext_;
    static ustr_t   validation_;
    e_svg_processing_mode svg_mode_ = spm_none;
    e_quote_style   quote_style_ = qs_none;
    e_do            do_ = do_booboo;
    aset_t          rpt_;
    ::std::time_t   ssi_date_ = 0, ssi_lastmod_ = 0;
    void init ();
    template < typename T > void mac (const e_nit_macro ns, const T n)
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (ns, ::boost::lexical_cast < ::std::string > (n)); }
    void mac (const e_nit_macro ns, const bool b)
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        if (b) macro -> set (ns, "true");
        else macro -> set (ns, "false"); }
    void mac (const e_nit_macro ns, const ::std::string& s)
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (ns, s); }
    void mac (const e_nit_macro ns, const char *sz)
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (ns, ::std::string (sz)); }
    void mac (const e_nit_macro ns, const vstr_t& s)
    {   ::std::string ss;
        for (auto sss: s)
        {   if (! ss.empty ()) ss += ",";
            ss += quote (sss); }
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (ns, ss); }
    void mac (const e_nit_macro ns, const vbp_t& s)
    {   ::std::string ss;
        for (auto sss: s)
        {   if (! ss.empty ()) ss += ",";
            ss += quote (sss.string ()); }
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (ns, ss); }
    ::std::string summarise () const;
    void populate_jsonld_ont (const vstr_t& vs);
public:
    context_t () { init (); }
    context_t (nitpick& nits, const ::boost::filesystem::path& fn);
    DEFAULT_COPY_CONSTRUCTORS (context_t);
    ~context_t () = default;
    void reset ();
    void reset (context_t& c);
    void swap (context_t& c);
    context_t& abhorrent (const ::std::string& s) { abhorrent_.push_back (s); return *this; }
    context_t& absolute_path (const bool b) { absolute_path_ = b; mac (nm_context_absolute_path, b); return *this; }
    context_t& accept (const ::std::string& s) { accept_ = s; return *this; }
    context_t& account (const ::std::string& s) { account_ = s; mac (nm_context_account, s); return *this; }
    context_t& article (const bool b) { article_ = b; mac (nm_context_article, b); return *this; }
    context_t& attrib (const vstr_t& s) { attrib_ = s; return *this; }
    context_t& body (const bool b) { body_ = b; mac (nm_context_body, b); return *this; }
    context_t& cache (const ::std::string& s) { cache_ = s; return *this; }
    context_t& cased (const bool b) { case_ = b; mac (nm_context_case, b); return *this; }
    context_t& catastrophe (const ::std::string& s) { catastrophe_.push_back (s); return *this; }
    context_t& cgi (const bool b) { cgi_ = b; mac (nm_context_cgi, b); spell (false); return *this; }
    context_t& chrome (const bool b) { chrome_ = b; mac (nm_context_chrome, b); return *this; }
    context_t& classic (const bool b) { classic_ = b; mac (nm_context_classic, b); return *this; }
    context_t& clear (const bool b) { clear_ = b; mac (nm_context_clear, b); return *this; }
    context_t& comment (const ::std::string& s) { comment_.push_back (s); return *this; }
    context_t& comms (const bool b) { comms_ = b; mac (nm_context_comms, b); return *this; }
    context_t& config (const ::boost::filesystem::path& c) { config_ = c; mac (nm_context_config, c.string ()); return *this; }
    context_t& copy (const int c)
    {   if ((c > c_none) && (c <= c_rpt)) copy_ = static_cast < e_copy > (c);
        else copy_ = c_none;
        mac < int > (nm_context_copy, c);
        return *this; }
    context_t& corpus (const ::boost::filesystem::path& f) { corpus_ = f; mac (nm_context_corpus, f.string ()); return *this; }
    context_t& crosslinks (const bool b) { crosslinks_ = b; mac (nm_context_crosslinks, b); return *this; }
    context_t& css_extension (const vstr_t& s) { css_ext_ = s; mac (nm_context_css_extension, s); return *this; }
    context_t& css_module (const e_css_module r, const int n);
    context_t& css_version (const int mjr, const int mnr);
    context_t& css_version (const e_css_version v) { version_.css_version (v); mac < int > (nm_context_css_version, v); return *this; }
    context_t& custom_elements (const vstr_t& s) { custom_elements_ = s; mac (nm_context_custom_elements, s); return *this; }
    context_t& debug (const ::std::string& s) { debug_.push_back (s); return *this; }
    context_t& dict (const ::std::string& s) { dict_.push_back (s); return *this; }
    context_t& dlang (const ::std::string& s) { dlang_.push_back (s); return *this; }
    context_t& domsg (const ::std::string& s) { domsg_ = s; return *this; }
    context_t& elem (const vstr_t& s) { elem_ = s; return *this; }
    context_t& elem_attrib (const vstr_t& s) { elem_attrib_ = s; return *this; }
    context_t& environment (const e_environment e, const ::std::string& s);
    context_t& error (const ::std::string& s) { error_.push_back (s); return *this; }
    context_t& example (const bool b) { example_ = b; mac (nm_context_example, b); return *this; }
    context_t& excl_def_excl (const bool b) { excl_ = b; mac (nm_context_excl_def_excl, b); return *this; }
    context_t& exclude (nitpick& nits, const vstr_t& s);
    context_t& exclude (nitpick& nits, const ::std::string& s);
    context_t& expand (const bool b) { expand_ = b; mac (nm_context_expand, b); return *this; }
    context_t& export_root (const ::std::string& s) { export_root_ = s; mac (nm_context_export_root, s); return *this; }
    context_t& exports (const vstr_t& s) { exports_ = s; mac (nm_context_exports, s); return *this; }
    context_t& extensions (const vstr_t& s) { extensions_ = s; mac (nm_context_extensions, s); return *this; }
    context_t& external (const bool b)
    {   external_ = b;
        if (b) links (b);
        else { forwarded (false); once (false); revoke (false); microdata (false); }
        return *this; }
    context_t& ext_css (const bool b) { ext_css_ = b; mac (nm_context_ext_css, b); return *this; }
    context_t& extra (const bool b) { extra_ = b; mac (nm_context_extra, b); return *this; }
    context_t& force_version (const bool b) { force_version_ = b; mac (nm_context_force_version, b); return *this; }
    context_t& forwarded (const bool b)
    {   forwarded_ = b;
        if (b) external (b);
        mac (nm_context_forward, b);
        return *this; }
    context_t& fred (const ::std::size_t i);
    void gui (const bool b) { gui_ = b; }
    context_t& help (const ::std::string& s) { help_ = s; mac (nm_context_help, s); return *this; }
    context_t& html_ver (const html_version& v)
    {   versioned (true); version_ = v; mac (nm_context_version, version_.name ()); return *this; }
    context_t& icu (const bool b) { icu_ = b; mac (nm_context_icu, b); return *this; }
    context_t& ie (const bool b) { ie_ = b; mac (nm_context_ie, b); return *this; }
    context_t& ignore (nitpick& nits, const vstr_t& s);
    context_t& info (const bool b) { info_ = b; mac (nm_context_info, b); return *this; }
    context_t& inform (const ::std::string& s) { inform_.push_back (s); return *this; }
    context_t& index (const ::std::string& s) { index_ = s; mac (nm_context_index, s); return *this; }
    context_t& iterate (const bool b) { iterate_ = b; mac (nm_context_iterate, b); return *this; }
    context_t& jsonld (const bool b) { jsonld_ = b; mac (nm_context_jsonld, b); return *this; }
    context_t& jsonld_extension (const vstr_t& s) { jsonld_ext_ = s; mac (nm_context_jsonld_extension, s); return *this; }
    context_t& jsonld_ontology (const vstr_t& vs) { populate_jsonld_ont (vs); mac (nm_context_jsonld_ontology, vs); return *this; }
    context_t& jsonld_version (const e_jsonld_version v)
    {   version_.jsonld_version (v);
        mac < int > (nm_context_jsonld_version, v);
        return *this; }
    context_t& lang (const ::std::string& s) { lang_ = s; mac (nm_context_lang, s); return *this; }
    context_t& links (const bool b)
    {   links_ = b;
        mac (nm_context_links, b);
        if (! b) { external (false); }
        return *this; }
    context_t& load_css (const bool b) { load_css_ = b; mac (nm_context_css, b); return *this; }
    context_t& load_vtt (const bool b) { load_vtt_ = b; mac (nm_context_vtt, b); return *this; }
    context_t& local (const bool b) { local_ = b; mac (nm_context_local, b); return *this; }
    context_t& macro_end (const ::std::string& s) { macro_end_ = s; return *this; }
    context_t& macro_start (const ::std::string& s) { macro_start_ = s; return *this; }
    context_t& main (const bool b) { main_ = b; mac (nm_context_main, b); return *this; }
    bool matches (const ::std::string& s, const ::std::string& w, const char sep = '/') const;
    context_t& math_version (const int v);
    context_t& math_version (const e_math_version v) noexcept { version_.math_version (v); return *this; }
    context_t& max_file_size (const long l) { max_file_size_ = l; mac < long > (nm_context_max_file_size, l);return *this; }
    context_t& md_export (const bool b) { md_export_ = b; mac (nm_context_md_export, b); return *this; }
    context_t& md_pretty (const bool b) { md_pretty_ = b; mac (nm_context_md_pretty, b); return *this; }
    context_t& output_description (const vstr_t& v) { output_description_ = v; mac (nm_context_output_description, v); return *this; }
    context_t& output_sign (const bool b) { output_sign_ = b; mac (nm_context_output_sign, b); return *this; }
    context_t& output_time (const ::std::string& s) { output_time_ = s; mac (nm_context_output_time, s); return *this; }
    context_t& mf_export (const bool b) { mf_export_ = b; mac (nm_context_mf_export, b); return *this; }
    context_t& mf_pretty (const bool b) { mf_pretty_ = b; mac (nm_context_mf_pretty, b); return *this; }
    context_t& mf_verify (const bool b) { mf_verify_ = b; mac (nm_context_mf_verify, b); return *this; }
    context_t& mf_version (const unsigned char n)
    {   mf_version_ = n;
        mac < int > (nm_context_mf_version, n);
        if (n <= 1) set_default_ontology_version (s_microformats, 1, 0);
        else set_default_ontology_version (s_microformats, 2, 0);
        return *this; }
    context_t& microdata (const bool b)
    {   microdata_ = b;
        mac (nm_context_microdata, b);
        if (b) links (b);
        return *this; }
    context_t& mozilla (const bool b) { mozilla_ = b; mac (nm_context_mozilla, b); return *this; }
    context_t& msg (const ::std::string& s) { msg_ = s; return *this; }
    context_t& netscape (const bool b) { netscape_ = b; mac (nm_context_netscape, b); return *this; }
    context_t& nids (const bool b) noexcept { nids_ = b; return *this; }
    context_t& output_format (const ::std::string& nf)
    {   output_format_ = nf;
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (nm_output_format, nf);
        return *this; }
    context_t& output_override (const ::std::string& nf) { output_override_ = nf; return *this; }
    context_t& nits (const bool b) noexcept { nits_ = b; return *this; }
    context_t& nits_nits_nits (const bool b) noexcept { nits_nits_nits_ = b; return *this; }
    context_t& no_ex_check (const vstr_t& s) { no_ex_check_ = s; mac (nm_context_no_ex_check, s); return *this; }
    context_t& not_root (const bool b) noexcept { not_root_ = b; return *this; }
    context_t& once (const bool b)
    {   once_ = b;
        mac (nm_context_once, b);
        if (b) external (b);
        return *this; }
    context_t& ontology (const bool b)
    {   ontology_ = b;
        mac (nm_context_schema, b);
        return *this; }
    context_t& ont_ver (const e_ontology o, const ::std::string& s)
    {   PRESUME (o < s_error, __FILE__, __LINE__);
        if (vont_.size () == 0) vont_.resize (s_error);
        vont_.at (o) = s;
        return *this; }
    context_t& out_name (const ::std::string& s) { out_ = s; return *this; }
    context_t& opera (const bool b) { opera_ = b; mac (nm_context_opera, b); return *this; }
    context_t& path (const ::std::string& s)
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        path_ = s;
        macro -> set (nm_general_path, s);
        return *this; }
    context_t& persisted (const ::std::string& s) { persisted_ = s; mac (nm_context_persisted, s); return *this; }
    context_t& presume_tags (const bool b) { presume_tags_ = b; mac (nm_context_tags, b); return *this; }
    context_t& pretend (nitpick& nits, const vstr_t& s);
    context_t& pretend (nitpick& nits, const ::std::string& s);
    context_t& pretty (const bool b) { pretty_ = b; mac (nm_context_pretty, b); return *this; }
    context_t& progress (const bool b) noexcept { progress_ = b; return *this; }
    context_t& quote_style (const e_quote_style qs) noexcept { quote_style_ = qs; return *this; }
    context_t& rdfa (const bool b) { rdfa_ = b; mac (nm_context_rdfa, b); return *this; }
    context_t& rdf_version (const e_rdf_version v) { version_.rdf_version (v); mac < int > (nm_context_rdf_version, v); return *this; }
    context_t& rel (const bool b) { rel_ = b; mac (nm_context_rel, b); return *this; }
    context_t& report (const vstr_t& s) { report_ = s; mac (nm_context_report, s); return *this; }
    context_t& report_error (const e_severity sev) noexcept { report_error_ = sev; return *this; }
    context_t& revoke (const bool b)
    {   revoke_ = b;
        if (b) external (b);
        return *this; }
    context_t& rfc_1867 (const bool b) { rfc_1867_ = b; mac (nm_context_rfc_1867, b); return *this; }
    context_t& rfc_1942 (const bool b) { rfc_1942_ = b; mac (nm_context_rfc_1942, b); return *this; }
    context_t& rfc_1980 (const bool b) { rfc_1980_ = b; mac (nm_context_rfc_1980, b); return *this; }
    context_t& rfc_2070 (const bool b) { rfc_2070_ = b; mac (nm_context_rfc_2070, b); return *this; }
    context_t& root (const ::std::string& s);
    context_t& rpt_opens (const bool b) noexcept { rpt_opens_ = b; return *this; }
    context_t& ruby (const bool b) { ruby_ = b; mac (nm_context_ruby, b); return *this; }
    context_t& safari (const bool b) { safari_ = b; mac (nm_context_safari, b); return *this; }
    context_t& secret (const ::std::string& s) { secret_ = s; return *this; }
    context_t& serve (const bool b);
    context_t& set_profile (const flags_t f) { version_.set_profile (f); return *this; }
    context_t& shadow_comment (const bool b) { shadow_comment_ = b; if (b) shadow_enable (true); mac (nm_context_shadow_comment, b); return *this; }
    context_t& shadow_changed (const bool b) { shadow_changed_ = b; if (b) shadow_enable (true); mac (nm_context_shadow_changed, b); return *this; }
    context_t& shadow_enable (const bool b) { shadow_enable_ = b; mac (nm_context_shadow_enable, b); return *this; }
    context_t& shadow_ignore (const vstr_t& s);
    context_t& shadow_persist (const ::std::string& s) { shadow_persist_ = s; shadow_enable (true); mac (nm_context_shadow_persist, s); return *this; }
    context_t& shadow_root (const ::std::string& s) { shadow_ = s; shadow_enable (true); mac (nm_context_shadow_root, s); return *this; }
    context_t& shadow_ssi (const bool b) { shadow_ssi_ = b; if (b) shadow_enable (true); mac (nm_context_shadow_ssi, b); return *this; }
    context_t& shadow_space (const bool b) { shadow_space_ = b; if (b) shadow_enable (true); mac (nm_context_shadow_space, b); return *this; }
    context_t& shadows (const vstr_t& s) { shadows_ = s; mac (nm_context_shadows, s); shadow_enable (true); return *this; }
    context_t& silent (const ::std::string& s) { silent_.push_back (s); return *this; }
    context_t& site (const vstr_t& s) { site_ = s; mac (nm_context_site, s); return *this; }
    context_t& sloven (const bool b) { sloven_ = b; mac (nm_context_sloven, b); return *this; }
    context_t& snippet (const ::std::string& s);
    context_t& spec (const bool b) { spec_ = b; return *this; }
    context_t& special (const bool b) { special_ = b; mac (nm_context_special, b); return *this; }
    context_t& spell_deduced (const bool b) { spell_deduced_ = b; return *this; }
    context_t& spell_list (const ::std::string& s) { spell_list_.push_back (s); return *this; }
    context_t& spellings (const vstr_t& s) { spellings_ = s; mac (nm_context_spellings, s); return *this; }
    context_t& spell_path (const ::boost::filesystem::path& f) { spell_path_ = f; mac (nm_context_spell_path, f); return *this; }
    context_t& ssi (const bool b) { ssi_ = b; mac (nm_context_ssi, b); return *this; }
    context_t& ssi_date (const ::std::time_t t) { ssi_date_ = t; mac (nm_context_ssi_date, t); return *this; }
    context_t& ssi_doc_args (nitpick& nits, const ::std::string& s) { check_ssi_naughtiness (nits, s); ssi_doc_args_ = s; mac (nm_context_ssi_doc_args, s); return *this; }
    context_t& ssi_echomsg (nitpick& nits, const ::std::string& s) { check_ssi_naughtiness (nits, s); ssi_echomsg_ = s; mac (nm_context_ssi_echomsg, s); return *this; }
    context_t& ssi_errmsg (nitpick& nits, const ::std::string& s) { check_ssi_naughtiness (nits, s); ssi_errmsg_ = s; mac (nm_context_ssi_errmsg, s); return *this; }
    context_t& ssi_exec_run (const bool b) { ssi_exec_run_ = b; mac (nm_context_ssi_exec_run, b); return *this; }
    context_t& ssi_exec_text (nitpick& nits, const ::std::string& s) { check_ssi_naughtiness (nits, s); ssi_exec_text_ = s; mac (nm_context_ssi_exec_text, s); return *this; }
    context_t& ssi_lastmod (const ::std::time_t t) { ssi_lastmod_ = t; mac (nm_context_ssi_lastmod, t); return *this; }
    context_t& ssi_query_string (nitpick& nits, const ::std::string& s) { check_ssi_naughtiness (nits, s); ssi_query_string_ = s; mac (nm_context_ssi_query_string, s); return *this; }
    context_t& ssi_timefmt (nitpick& nits, const ::std::string& s) { check_ssi_naughtiness (nits, s); ssi_timefmt_ = s; mac (nm_context_ssi_timefmt, s); return *this; }
    context_t& ssi_user_name (nitpick& nits, const ::std::string& s) { check_ssi_naughtiness (nits, s); ssi_user_name_ =s; mac (nm_context_ssi_user_name, s); return *this; }
    context_t& stats (const ::std::string& s) { stats_ = s; mac (nm_context_stats_export, s); return *this; }
    context_t& stats (const e_report r, const bool b);
    context_t& stats_all (const bool b);
    context_t& stats_report (const e_report e, const bool b) { rpt_.at (e) = b; return *this; }
    context_t& svg (const ::std::string& s) { svg_ = s; return *this; }
    context_t& svg_mode (const e_svg_processing_mode m) noexcept { svg_mode_ = m; return *this; }
    context_t& svg_version (const int mjr, const int mnr);
    context_t& svg_version (const e_svg_version v) { version_.svg_version (v); mac < int > (nm_context_svg_version, v); return *this; }
    context_t& test (const bool b) { test_ = b; mac (nm_context_test, b); return *this; }
    context_t& title (const ::std::size_t n)
    { if (n <= 0) title_ = 0; else title_ = n; mac < ::std::size_t > (nm_context_title, title_); return *this; }
    context_t& todo (const e_do e) noexcept { do_ = e; return *this; }
    context_t& unknown_class (const bool b) { unknown_class_ = b; mac (nm_context_unknown_class, b); return *this; }
    context_t& update (const bool b) noexcept { update_ = b; return *this; }
    context_t& username (const ::std::string& s) { username_ = s; return *this; }
    context_t& vcs (const bool b) { vcs_ = b; mac (nm_context_vcs, b); return *this; }
    context_t& verbose (const e_severity i) noexcept { verbose_ = i; return *this; }
    context_t& versioned (const bool b) noexcept { versioned_ = b; return *this; }
    context_t& virtuals (const vstr_t& s) { virtuals_ = s; mac (nm_context_virtuals, s); return *this; }
    context_t& vtt_extension (const vstr_t& s) { vtt_ext_ = s; mac (nm_context_vtt_extension, s); return *this; }
    context_t& vvext (const ::std::size_t n, const vstr_t& v) { if (vvext_.size () <= n) vvext_.resize (n+1); vvext_.at (n) = v; return *this; }
    context_t& warning (const ::std::string& s) { warning_.push_back (s); return *this; }
    context_t& wx (const bool b) { wx_ = b; mac (nm_context_wx, b); return *this; }
    context_t& wx_snippet (const ::std::string& s) { wx_snippet_ = s; return *this; }
    context_t& x (const ::std::string& s) { x_ = s; return *this; }
    context_t& yggdrisil (const bool b) { yggdrisil_ = b; return *this; }
    context_t& mobile_profile (const bool b) { if (b) version_.set_profile (H3_NOT_MOBILE); else version_.reset_profile (H3_NOT_MOBILE); return *this; }
    context_t& print_profile (const bool b) { if (b) version_.set_profile (H3_NOT_PRINT); else version_.reset_profile (H3_NOT_PRINT); return *this; }
    context_t& tv_profile (const bool b) { if (b) version_.set_profile (H3_NOT_TV); else version_.reset_profile (H3_NOT_TV); return *this; }
    void consolidate_jsonld ()
    {   for (auto j : jsonld_ext_) extensions_.push_back (j); }
    int parameters (output_streams_t& ost, nitpick& nits, const vstr_t& vs);
    const vstr_t& abhorrent () const { return abhorrent_; }
    bool absolute_path () const noexcept { return absolute_path_; }
    const ::std::string accept () const { return accept_; }
    const ::std::string account () const { return account_; }
    bool article () const noexcept { return article_; }
    const vstr_t& attrib () const { return attrib_; }
    bool body () const noexcept { return body_; }
    const ::std::string build () const { return build_; }
    context_t& build (const ::std::string& s) { build_ = s; mac (nm_compile_time, s); return *this; }
    const ::std::string& cache () const noexcept { return cache_; }
    bool cased () const noexcept { return case_; }
    const vstr_t& catastrophe () const { return catastrophe_; }
    bool cgi () const noexcept { return cgi_; }
    bool chrome () const noexcept { return chrome_; }
    bool classic () const noexcept { return classic_; }
    bool clear () const noexcept { return clear_; }
    const vstr_t& cmd () const { return cmd_; }
    vstr_t cmd () { return cmd_; }
    void cmd (const vstr_t& v) { cmd_ = v; }
    const vstr_t& comment () const { return comment_; }
    bool comms () const noexcept { return comms_; }
    ::boost::filesystem::path config () const { return config_; }
    e_copy copy () const noexcept { return copy_; }
    ::boost::filesystem::path corpus () const { return corpus_; }
    bool crosslinks () const noexcept { return crosslinks_; }
    const vstr_t css_extension () const { return css_ext_; }
    int css_module (const e_css_module m) const { return version_.css_module (m); }
    e_css_version css_version () const noexcept { return version_.css_version (); }
    const vstr_t custom_elements () const { return custom_elements_; }
    const ::boost::filesystem::path cwd () const { return cwd_; }
    const vstr_t& debug () const { return debug_; }
    const ::boost::filesystem::path& default_config_file () const { return def_conf_file_; }
    const ::boost::filesystem::path& default_config_path () const { return def_conf_path_; }
    const vstr_t& dict () const { return dict_; }
    const vstr_t& dlang () const { return dlang_; }
    bool dodedu () const noexcept { return (copy_ >= c_deduplicate); }
    const ::std::string domsg () const { return domsg_; }
    const vstr_t& elem () const { return elem_; }
    const vstr_t& elem_attrib () const { return elem_attrib_; }
    const ::std::string environment (const e_environment e) const { return environment_.at (e); }
    const vstr_t& error () const { return error_; }
    bool example () const noexcept { return example_; }
    bool excl_def_excl () const noexcept { return excl_; }
    const vstr_t exclude () const { return exclude_; }
    bool excluded (nitpick& nits, const ::boost::filesystem::path& p) const;
    bool expand () const noexcept { return expand_; }
    bool export_defined () const noexcept { return ! export_root_.empty (); }
    const ::std::string export_root () const { return export_root_; }
    const vstr_t exports () const { return exports_; }
    const vstr_t extensions () const { return extensions_; }
    bool external () const noexcept { return external_; }
    bool ext_css () const noexcept { return ext_css_; }
    bool extra () const noexcept { return extra_; }
    bool force_version () const noexcept { return force_version_; }
    bool forwarded () const noexcept{ return forwarded_; }
    ::std::size_t fred () const noexcept{ return fred_; }
    const ::std::string& general_info () const { return general_info_; }
    context_t& general_info (const ::std::string& s) { general_info_ = s; mac (nm_general_info, s); return *this; }
    bool gui () const noexcept { return gui_; }
    bool has_math () const noexcept { return version_.has_math (); }
    bool has_rdfa () const noexcept { return rdfa () || (version_.is_svg_12 ()) || (version_ == xhtml_2); }
    bool has_svg () const noexcept { return version_.has_svg (); }
    const ::std::string help () const { return help_; }
    html_version html_ver () const noexcept { return version_; }
    html_version& html_ver () noexcept { return version_; }
    html_version html_ver (const int major, const int minor) noexcept;
    bool icu () const noexcept { return icu_; }
    bool ie () const noexcept { return ie_; }
    const vstr_t ignore () const { return ignore_; }
    bool info () const noexcept { return info_; }
    const vstr_t& inform () const { return inform_; }
    const ::std::string index () const { return index_; }
    bool iterate () const noexcept { return iterate_; }
    bool invalid () const noexcept { return ! valid_; }
    bool jsonld () const noexcept { return jsonld_; }
    const vstr_t jsonld_extension () const { return jsonld_ext_; }
    const vstr_t jsonld_key () { return jsonld_key_; }
    const vstr_t jsonld_ontology () const { return jsonld_ont_; }
    const vstr_t jsonld_value () { return jsonld_val_; }
    e_jsonld_version jsonld_version () const noexcept { return version_.jsonld_version (); }
    ::std::string lang () const { return lang_; }
    bool local () const noexcept { return local_; }
    bool links () const noexcept { return links_; }
    bool load_css () const noexcept { return load_css_; }
    bool load_vtt () const noexcept { return load_vtt_; }
    const ::std::string macro_end () const { return macro_end_; }
    const ::std::string macro_start () const { return macro_start_; }
    bool main () const noexcept { return main_; }
    e_math_version math_version () const noexcept { return version_.math_version (); }
    unsigned long max_file_size () const noexcept { return GSL_NARROW_CAST < unsigned long > (max_file_size_); }
    bool md_export () const noexcept { return md_export_; }
    bool md_pretty () const noexcept { return md_pretty_; }
    bool mf_export () const noexcept { return mf_export_; }
    bool mf_pretty () const noexcept { return mf_pretty_; }
    bool mf_verify () const noexcept { return mf_verify_; }
    int mf_version () const noexcept { return mf_version_; }
    bool mf_version1 () const noexcept { return (mf_version_ & 1) != 0; }
    bool mf_version2 () const noexcept { return (mf_version_ & 2) != 0; }
    bool microdata () const noexcept { return microdata_; }
    bool microformats () const noexcept { return mf_verify_ || mf_export_; }
    bool mozilla () const noexcept { return mozilla_; }
    const ::std::string& msg () const { return msg_; }
    bool netscape () const noexcept { return netscape_; }
    bool nids () const noexcept { return nids_; }
    const ::std::string& output_format () const
    {   if (output_override_.empty ()) return output_format_;
        return output_override_; }
    bool nits () const noexcept { return nits_; }
    bool nits_nits_nits () const noexcept { return nits_nits_nits_; }
    const ::std::string& output_override () const { return output_override_; }
    const vstr_t no_ex_check () const { return no_ex_check_; }
    bool not_root () const noexcept { return not_root_; }
    bool once () const noexcept { return once_; }
    bool ontology () const noexcept { return ontology_; }
    ontology_version ontology_ver (const e_ontology es = s_schema) const
    {   return get_default_ontology_version (es); }
    ontology_version ontology_ver (const html_version& v, const e_ontology es = s_schema) const
    {   return corresponding_ontology_version (es, v); }
    ::std::string ont_ver (const e_ontology o) const
    {   PRESUME (o < s_error, __FILE__, __LINE__);
        if (vont_.size () > 0) return vont_.at (o);
        return ::std::string (); }
    bool opera () const noexcept { return opera_; }
    const ::std::string& out_name () const { return out_; }
    const vstr_t output_description () const { return output_description_; }
    bool output_sign () const noexcept { return output_sign_; }
    const ::std::string& output_time () const { return output_time_; }
    const ::std::string& path () const { return path_; }
    const ::std::string persisted () const { return persisted_; }
    bool presume_tags () const noexcept { return presume_tags_; }
    const vstr_t& pretend () const { return pretend_; }
    bool pretended (const ::std::string& s) const;
    bool pretty () const noexcept { return pretty_; }
    bool progress () const noexcept { return progress_; }
    e_quote_style quote_style () const noexcept { return quote_style_; }
    bool rdfa () const noexcept;
    e_rdf_version rdf_version () const noexcept { return version_.rdf_version (); }
    bool rel () const noexcept { return rel_; }
    bool repetitive () const noexcept { return serve_ || iterate_; }
    const vstr_t report () const { return report_; }
    e_severity report_error () const noexcept { return report_error_; }
    bool revoke () const noexcept { return revoke_; }
    bool rfc_1867 () const noexcept { return rfc_1867_; }
    bool rfc_1942 () const noexcept { return rfc_1942_; }
    bool rfc_1980 () const noexcept { return rfc_1980_; }
    bool rfc_2070 () const noexcept { return rfc_2070_; }
    bool rpt_opens () const noexcept { return rpt_opens_; }
    const ::std::string& root () const { return root_; }
    bool ruby () const noexcept { return ruby_; }
    const ::boost::filesystem::path& rootp () const { return proot_; }
    bool safari () const noexcept { return safari_; }
    const ::std::string& secret () const { return secret_; }
    bool serve () const noexcept { return serve_; }
    bool shadow_any () const noexcept { return shadow_pages (); }
    bool shadow_comment () const noexcept { return shadow_comment_; }
    bool shadow_changed () const noexcept { return shadow_changed_; }
    bool shadow_enable () const noexcept { return shadow_enable_; }
    bool shadow_files () const noexcept { return ((copy_ > c_html) && (copy_ <= c_deduplicate)); }
    const vstr_t shadow_ignore () const { return shadow_ignore_; }
    bool shadow_pages () const noexcept { return ((copy_ > c_none) && (copy_ <= c_deduplicate)); }
    const ::std::string shadow_persist () const { return shadow_persist_; }
    const ::std::string shadow_root () const { return shadow_; }
    bool shadow_ssi () const noexcept { return shadow_ssi_; }
    bool shadow_space () const noexcept { return shadow_space_; }
    const vstr_t shadows () const { return shadows_; }
    const vstr_t& silent () const { return silent_; }
    const vstr_t site () const { return site_; }
    bool sloven () const noexcept { return sloven_; }
    bool spell () const noexcept { return spell_; }
    context_t& spell (const bool b) { spell_ = b; mac (nm_context_spell, b); return *this; }
    bool spell_deduced () const noexcept { return spell_deduced_; }
    const vstr_t& spell_list () const { return spell_list_; }
    const vstr_t& spellings () const { return spellings_; }
    const ::boost::filesystem::path& spell_path () const { return spell_path_; }
    const ::std::string& snippet () const { return snippet_; }
    bool spec () const noexcept { return spec_; }
    bool special () const noexcept { return special_; }
    bool ssi () const noexcept { return ssi_; }
    ::std::time_t ssi_date () const { return ssi_date_; }
    const ::std::string& ssi_doc_args () const { return ssi_doc_args_; }
    const ::std::string& ssi_echomsg () const { return ssi_echomsg_; }
    const ::std::string& ssi_errmsg () const { return ssi_errmsg_; }
    bool ssi_exec_run () const { return ssi_exec_run_; }
    const ::std::string& ssi_exec_text() const { return ssi_exec_text_; }
    ::std::time_t ssi_lastmod () const { return ssi_lastmod_; }
    const ::std::string& ssi_query_string () const { return ssi_query_string_; }
    const ::std::string& ssi_timefmt () const { return ssi_timefmt_; }
    const ::std::string& ssi_user_name () const { return ssi_user_name_; }
    const ::std::string& started () const { return started_; }
    context_t& started (const ::std::string& s) { started_ = s; mac (nm_time_start, s); return *this; }
    const ::std::string& stats () const { return stats_; }
    bool stats (const e_report r) const { return rpt_.at (r); }
    bool stats_any () const;
    bool stats_gst (const e_gsstr gst);
    bool stats_report (const e_report e) const { return rpt_.at (e); }
    const ::std::string& svg () const { return svg_; }
    e_svg_processing_mode svg_mode () const noexcept { return svg_mode_; }
    e_svg_version svg_version () const noexcept { return version_.svg_version (); }
    bool test () const noexcept { return test_ && output_override_.empty (); }
    ::std::size_t title () const noexcept { return title_; }
    e_do todo () const noexcept { return do_; }
    bool unknown_class () const noexcept { return unknown_class_; }
    e_severity verbose () const noexcept { return verbose_; }
    const vstr_t virtuals () const { return virtuals_; }
    const vstr_t vtt_extension () const { return vtt_ext_; }
    bool update () const noexcept { return update_; }
    ::std::string username () const { return username_; }
    bool vcs () const noexcept { return vcs_; }
    void apply_vcs (nitpick& nits);
    bool versioned () const noexcept { return versioned_; }
    const vstr_t vvext (const ::std::size_t n) const { if (vvext_.size () <= n) return vstr_t (); return (vvext_.at (n)); }
    const vstr_t& warning () const { return warning_; }
    bool wx () const noexcept { return wx_; }
    const ::std::string& wx_snippet () const { return wx_snippet_; }
    const ::std::string& x () const { return x_; }
    bool yggdrisil () const { return yggdrisil_; }
    bool tell (const e_severity n) const noexcept
    {   if (n == es_undefined) return false;
        return n <= verbose_; }
    ustr_t& validation () noexcept { return validation_; }
    const ustr_t& validation () const noexcept { return validation_; }
    bool profile_checks () const { return version_.profile_checks (); }
    bool mobile_profile () const { return version_.mobile_profile (); }
    bool print_profile () const { return version_.print_profile (); }
    bool tv_profile () const { return version_.tv_profile (); }
    static void check_ssi_naughtiness (nitpick& nits, const ::std::string& s);
    ::std::string make_absolute_url (const ::std::string& link, bool can_use_index = true) const;
    ::std::string report (const e_gui_report gr, const bool wibble) const;
    bool write (nitpick& nits, const ::boost::filesystem::path& fn) const; };

extern context_t context;
