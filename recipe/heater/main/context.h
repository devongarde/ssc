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

#pragma once
#include "feedback/nitpick.h"
#include "feedback/nitout.h"
#include "main/output.h"
#include "stats/stats.h"
#include "parser/html_version.h"
#include "ontology/ontology_version.h"
#include "utility/filesystem.h"
#include "utility/list.h"

CONSTEXPR e_severity default_output = es_warning;
CONSTEXPR bool def_absolute_path = true, def_ads = true, def_aria = true, def_article = false, def_atom_verify = true,
    def_body = true, def_case = false, def_cgi = false,
    def_chrome = false, def_classic = false, def_clear = false, def_comms = true, def_crosslinks = true, def_expand = false, def_example = true,
    def_excl = true, def_external = false, def_ext_css = false, def_extra = false, def_force_version = false, def_forwarded = true,
    def_gui = false, def_icu = true, def_ie = false, def_info = false, def_iterate = false, def_jsonld = false, def_local = true,
    def_links = true, def_load_css = true, def_load_vtt = true, def_main = false, def_md_export = false, def_md_pretty = true,
    def_meta_all = true, def_meta_sign = true, def_mf_export = false, def_mf_pretty = true, def_mf_verify = true, def_microdata = true,
    def_mozilla = false, def_netscape = false, def_nids = false, def_nits = false, def_nits_nits_nits = false, def_not_root = false,
    def_opera = false, def_once = true, def_presume_tags = false, def_pretty = true, def_progress = false, def_rdfa = false, def_rel = false,
    def_revoke = false, def_rfc_1867 = true, def_rfc_1942 = true, def_rfc_1980 = true, def_rfc_2070 = true, def_robots = true, def_rpt_opens = false, def_rsl_verify = true, def_rss_verify = true,
    def_ruby = false, def_ontology = true, def_safari = false, def_sectxt = true, def_serve = false, def_shadow_changed = false, def_shadow_comment = true,
    def_shadow_enable = false, def_shadow_space = true, def_shadow_ssi = true, def_sign = false, def_sloven = false, def_spec = false,
    def_special = true, def_spell = true, def_spell_deduced = false, def_ssi = true, def_ssi_exec_run = false, def_test = false,
    def_unknown_class = true, def_update = false, def_update_check = true, def_valid = false, def_vcs = false, def_verify = false,
    def_versioned = false, def_wx = false, def_yggdrisil = false;
CONSTEXPR const char* const def_macrostart = "{{";
CONSTEXPR const char* const def_macroend = "}}";
CONSTEXPR const char* const def_path = DEF_DATAPATH;
CONSTEXPR const char* const def_port = DEFAULT_PORT_S;
CONSTEXPR const char* const def_persisted = PROG DEF_PERSIST_EXT;
CONSTEXPR ::std::size_t def_htmltitle = MAX_IDEAL_TITLE_LENGTH;
CONSTEXPR ::std::size_t def_fred = MIN_FRED;
CONSTEXPR unsigned char def_mf = 3;
CONSTEXPR long def_max_file_size = DMFS_BYTES;
CONSTEXPR const char* const def_css_ext = CSS_EXT;
CONSTEXPR const char* const def_html_ext = HTML_EXT;
CONSTEXPR const char* const def_jsonld_ext = JSONLD_EXT;
CONSTEXPR const char* const def_rsl_ext = RSL_EXT;
CONSTEXPR const char* const def_rss_ext = RSS_EXT;
CONSTEXPR const char* const def_rss_ver = "2.0";
CONSTEXPR const char* const def_stylesheet = "stylesheet.css";

class ads;
class robotic;
class sec_txt;
typedef ::std::shared_ptr < ads > ads_ptr;
typedef ::std::shared_ptr < robotic > robotic_ptr;
typedef ::std::shared_ptr < sec_txt > sec_ptr;

class context_t
{   friend class options;
    bool            absolute_path_ = def_absolute_path, adstxt_ = def_ads, aria_ = def_aria, article_ = def_article, atom_verify_ = def_atom_verify,
                    body_ = def_body, case_ = def_case, cgi_ = def_cgi, chrome_ = def_chrome, classic_ = def_classic, clear_ = def_clear, comms_ = def_comms,
                    crosslinks_ = def_crosslinks, example_ = def_example, excl_ = def_excl, expand_ = def_expand, external_ = def_external,
                    ext_css_ = def_ext_css, extra_ = def_extra, force_version_ = def_force_version, forwarded_ = def_forwarded, gui_ = def_gui,
                    icu_ = def_icu, ie_ = def_ie, info_ = def_info, iterate_ = def_iterate, jsonld_ = def_jsonld, local_ = def_local, load_css_ = def_load_css,
                    load_vtt_ = def_load_vtt,links_ = def_links, main_ = def_main, md_export_ = def_md_export, md_pretty_ = def_md_pretty,
                    output_sign_ = def_meta_sign, mf_export_ = def_mf_export, mf_pretty_ = def_mf_pretty, mf_verify_ = def_mf_verify,
                    microdata_ = def_microdata, mozilla_ = def_mozilla, netscape_ = def_netscape, nids_ = def_nids, nits_ = def_nits,
                    nits_nits_nits_ = def_nits_nits_nits, not_root_ = def_not_root, once_ = def_once, ontology_ = def_ontology, opera_ = def_opera,
                    presume_tags_ = def_presume_tags, pretty_ = def_pretty, progress_ = def_progress, rdfa_ = def_rdfa, rel_ = def_rel, revoke_ = def_revoke,
                    rfc_1867_ = def_rfc_1867, rfc_1942_ = def_rfc_1942, rfc_1980_ = def_rfc_1980, rfc_2070_ = def_rfc_2070, robots_ = def_robots,
                    rpt_opens_ = def_rpt_opens, rsl_verify_ = def_rsl_verify, rss_verify_ = def_rss_verify, ruby_ = def_ruby, safari_ = def_safari,
                    sectxt_ = def_sectxt, serve_ = def_serve, shadow_changed_ = def_shadow_changed, shadow_comment_ = def_shadow_comment,
                    shadow_enable_ = def_shadow_enable, shadow_space_ = def_shadow_space, shadow_ssi_ = def_shadow_ssi, sign_ = def_sign,
                    sloven_ = def_sloven, spec_ = def_spec, special_ = def_special, spell_ = def_spell, spell_deduced_ = def_spell_deduced,
                    ssi_ = def_ssi, ssi_exec_run_ = def_ssi_exec_run, test_ = def_test, unknown_class_ = def_unknown_class, update_ = def_update,
                    update_check_ = def_update_check, verify_ = def_verify, valid_ = def_valid, vcs_ = def_vcs, versioned_ = def_versioned, wx_ = def_wx,
                    yggdrisil_ = def_yggdrisil;
    ::std::size_t   fred_ = def_fred, title_ = def_htmltitle;
    e_copy          copy_ = c_none;
    unsigned char   mf_version_ = def_mf;
    html_version    version_;
    long            max_file_size_ = def_max_file_size, line_length_ = DEFAULT_LINE_LENGTH;
    e_severity      report_error_ = es_error, verbose_ = default_output;
    ::std::string   accept_, account_, build_, cache_, domsg_, export_root_, general_info_, help_, index_, lang_, macro_end_ = def_macroend,
                    macro_start_ = def_macrostart, msg_, out_, out_copy_, output_format_, output_override_, output_time_, path_ = def_path,
                    persisted_, port_ = def_port, root_, shadow_, shadow_persist_, snippet_, ssi_doc_args_, ssi_echomsg_, ssi_errmsg_,
                    ssi_exec_text_, ssi_query_string_, ssi_timefmt_, ssi_user_name_, started_, stats_, svg_, username_, wx_snippet_, x_;
    ::boost::filesystem::path   back_, config_, corpus_, def_conf_path_, def_conf_file_, home_, output_password_, output_private_, output_public_,
                                proot_, output_signature_, spell_path_, stylesheet_ = def_stylesheet;
    static ::boost::filesystem::path cwd_;
    sstr_t          atomic_ext_ = { ATOMIC_EXT }, css_ext_ = { CSS_EXT }, custom_elements_, extensions_ = { HTML_EXT }, jsonld_ext_ = { JSONLD_EXT },
                    no_ex_check_, rsl_ext_ = { RSL_EXT }, rss_ext_ = { RSS_EXT }, site_, vtt_ext_ = { VTT_EXT };
    vstr_t          abhorrent_, attrib_, catastrophe_, cmd_, comment_, debug_, dict_, dlang_, elem_, elem_attrib_, environment_, error_, exclude_,
                    exports_, inform_, ignore_, jsonld_key_, jsonld_ont_, jsonld_val_, output_description_, naughty_, nice_, note_,
                    pretend_, replace_, report_, shadow_ignore_, shadows_, silent_, spell_list_, spellings_, url_var_, virtuals_, vont_, warning_;
    ustr_t          uvar_;
    vvstr_t         vvext_;
    static ustr_t   validation_;
    e_analysis      anal_ = anal_default;
    e_svg_processing_mode svg_mode_ = spm_none;
    e_quote_style   quote_style_ = qs_none;
    e_do            do_ = do_booboo;
    aset_t          rpt_;
    ::std::time_t   ssi_date_ = 0, ssi_lastmod_ = 0;
    os_ptr          os_;
    wblist          tim_;
    vreg_t          silence_;
    e_rss_version   rss_version_ = rv_2011;
    mutable ads_ptr         ads_;
    mutable robotic_ptr     robbie_;
    mutable sec_ptr         security_;
    static ::std::string update_info_;
#ifdef LEAK_SEEK
public:
    static _CrtMemState ls_old_;
private:
#endif // LEAK_SEEK
    void init ();
    void done ();
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
    void mac (const e_nit_macro ns, const sstr_t& s);
    void mac (const e_nit_macro ns, const vstr_t& s);
    void mac (const e_nit_macro ns, const vbp_t& s);
    ::std::string summarise () const;
    void populate_jsonld_ont (const vstr_t& vs);
    void check_consistency (nitpick& nits);
    void check_for_update (nitpick& nits);
public:
    context_t () { init (); }
    context_t (nitpick& nits, const ::boost::filesystem::path& fn);
    DEFAULT_COPY_CONSTRUCTORS (context_t);
    ~context_t () { try { done (); } catch (...) { } };
    void reset ();
    void reset (const context_t& c);
    void swap (context_t& c);
    os_ptr& os ()
    {   VERIFY_NOT_NULL (os_.get (), __FILE__, __LINE__);
        return os_; }
    const os_ptr& os () const
    {   VERIFY_NOT_NULL (os_.get (), __FILE__, __LINE__);
        return os_; }
    context_t& abhorrent (const ::std::string& s) { abhorrent_.push_back (s); return *this; }
    context_t& absolute_path (const bool b) { absolute_path_ = b; mac (nm_context_absolute_path, b); return *this; }
    context_t& accept (const ::std::string& s) { accept_ = s; return *this; }
    context_t& account (const ::std::string& s) { account_ = s; mac (nm_context_account, s); return *this; }
    context_t& adstxt (const bool b) { adstxt_ = b; mac (nm_context_ads, b); return *this; }
    context_t& analysis (const e_analysis a) { anal_ = a; mac (nm_context_analysis, static_cast < int > (a)); return *this; }
    context_t& aria (const bool b) { aria_ = b; mac (nm_context_role, b); return *this; }
    context_t& article (const bool b) { article_ = b; mac (nm_context_article, b); return *this; }
    context_t& atomic_ext (const vstr_t& s) { atomic_ext_ = vtos (s); mac (nm_context_atom_exts, s); return *this; }
    context_t& atomic_verify (const bool b) { atom_verify_ = b; mac (nm_context_atom_ver, b); return *this; }
    context_t& attrib (const vstr_t& s) { attrib_ = s; return *this; }
    context_t& back (const ::boost::filesystem::path& s) { back_ = s; mac (nm_context_back, s); return *this; }
    context_t& body (const bool b) { body_ = b; mac (nm_context_body, b); return *this; }
    context_t& build (const ::std::string& s) { build_ = s; mac (nm_compile_time, s); return *this; }
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
    context_t& copy (const int c);
    context_t& corpus (const ::boost::filesystem::path& f) { corpus_ = f; mac (nm_context_corpus, f.string ()); return *this; }
    context_t& crosslinks (const bool b) { crosslinks_ = b; mac (nm_context_crosslinks, b); return *this; }
    context_t& css_extension (const vstr_t& s) { css_ext_ = vtos (s); mac (nm_context_css_extension, s); return *this; }
    context_t& css_extension (const sstr_t& s) { css_ext_ = s; mac (nm_context_css_extension, s); return *this; }
    context_t& css_module (const e_css_module r, const int n);
    context_t& css_version (const int mjr, const int mnr);
    context_t& css_version (const e_css_version v) { version_.css_version (v); mac < int > (nm_context_css_version, v); return *this; }
    context_t& custom_elements (nitpick& nits, const vstr_t& s);
    context_t& debug (const ::std::string& s) { debug_.push_back (s); return *this; }
    context_t& dict (const ::std::string& s) { dict_.push_back (s); return *this; }
    context_t& dlang (const ::std::string& s) { dlang_.push_back (s); return *this; }
    context_t& domsg (const ::std::string& s) { domsg_ = s; return *this; }
    context_t& efficient (const bool b) { sloven_ = ! b; mac (nm_context_efficient, b); return *this; }
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
    context_t& extensions (const vstr_t& s) { extensions_ = vtos (s); mac (nm_context_extensions, s); return *this; }
    context_t& external (const bool b);
    context_t& ext_css (const bool b) { ext_css_ = b; mac (nm_context_ext_css, b); return *this; }
    context_t& extra (const bool b) { extra_ = b; mac (nm_context_extra, b); return *this; }
    context_t& force_version (const bool b) { force_version_ = b; mac (nm_context_force_version, b); return *this; }
    context_t& forwarded (const bool b);
    context_t& fred (const ::std::size_t i);
    context_t& general_info (const ::std::string& s) { general_info_ = s; mac (nm_general_info, s); return *this; }
    void gui (const bool b) { gui_ = b; }
    context_t& help (const ::std::string& s) { help_ = s; mac (nm_context_help, s); return *this; }
    context_t& home (const ::boost::filesystem::path& s) { home_ = s; mac (nm_context_home, s); return *this; }
    context_t& html_ver (const html_version& v);
    context_t& icu (const bool b) { icu_ = b; mac (nm_context_icu, b); return *this; }
    context_t& ie (const bool b) { ie_ = b; mac (nm_context_ie, b); return *this; }
    context_t& ignore (nitpick& nits, const vstr_t& s);
    context_t& info (const bool b) { info_ = b; mac (nm_context_info, b); return *this; }
    context_t& inform (const ::std::string& s) { inform_.push_back (s); return *this; }
    context_t& index (const ::std::string& s) { index_ = s; mac (nm_context_index, s); return *this; }
    context_t& iterate (const bool b) { iterate_ = b; mac (nm_context_iterate, b); return *this; }
    context_t& jsonld (const bool b) { jsonld_ = b; mac (nm_context_jsonld, b); return *this; }
    context_t& jsonld_extension (const vstr_t& s) { jsonld_ext_ = vtos (s); mac (nm_context_jsonld_extension, s); return *this; }
    context_t& jsonld_ontology (const vstr_t& vs) { populate_jsonld_ont (vs); mac (nm_context_jsonld_ontology, vs); return *this; }
    context_t& jsonld_version (const e_jsonld_version v) { version_.jsonld_version (v); mac < int > (nm_context_jsonld_version, v); return *this; }
    context_t& lang (const ::std::string& s) { lang_ = s; mac (nm_context_lang, s); return *this; }
    context_t& line_length (const long l) { if ((l >= MIN_LINE_LENGTH) && (l < (INT8_MAX - 16))) line_length_ = l; mac (nm_contect_line_length, l); return *this; }
    context_t& links (const bool b);
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
    context_t& output_time (const ::std::string& s) { output_time_ = s; mac (nm_context_output_time, s); return *this; }
    context_t& mf_export (const bool b) { mf_export_ = b; mac (nm_context_mf_export, b); return *this; }
    context_t& mf_pretty (const bool b) { mf_pretty_ = b; mac (nm_context_mf_pretty, b); return *this; }
    context_t& mf_verify (const bool b) { mf_verify_ = b; mac (nm_context_mf_verify, b); return *this; }
    context_t& mf_version (const unsigned char n);
    context_t& microdata (const bool b);
    context_t& mozilla (const bool b) { mozilla_ = b; mac (nm_context_mozilla, b); return *this; }
    context_t& msg (const ::std::string& s) { msg_ = s; return *this; }
    context_t& netscape (const bool b) { netscape_ = b; mac (nm_context_netscape, b); return *this; }
    context_t& naughty (const vstr_t& s) { naughty_ = s; mac (nm_context_naughty, s); return *this; }
    context_t& nice (const vstr_t& s) { nice_ = s; mac (nm_context_nice, s); return *this; }
    context_t& nids (const bool b) noexcept { nids_ = b; return *this; }
    context_t& note (const vstr_t& s) { note_ = s; mac (nm_context_note, s); return *this; }
    context_t& nits (const bool b) noexcept { nits_ = b; return *this; }
    context_t& nits_nits_nits (const bool b) noexcept { nits_nits_nits_ = b; return *this; }
    context_t& no_ex_check (const vstr_t& s) { no_ex_check_ = vtos (s); mac (nm_context_no_ex_check, s); return *this; }
    context_t& not_root (const bool b) noexcept { not_root_ = b; return *this; }
    context_t& once (const bool b);
    context_t& ontology (const bool b);
    context_t& ont_ver (const e_ontology o, const ::std::string& s);
    context_t& opera (const bool b) { opera_ = b; mac (nm_context_opera, b); return *this; }
    context_t& out_copy (const ::std::string& s) { out_copy_ = s; return *this; }
    context_t& out_name (const ::std::string& s) { out_ = s; return *this; }
    context_t& output_format (const ::std::string& nf);
    context_t& output_override (const ::std::string& nf) { output_override_ = nf; return *this; }
    context_t& output_password (const ::boost::filesystem::path& s) { output_password_ = s; mac (nm_context_output_password, s); return *this; }
    context_t& output_private (const ::boost::filesystem::path& s) { output_private_ = s; sign_ = true; mac (nm_context_output_private, s); return *this; }
    context_t& output_public (const ::boost::filesystem::path& s) { output_public_ = s; verify_ = true; mac (nm_context_output_public, s); return *this; }
    context_t& output_signature (const ::boost::filesystem::path& s) { output_signature_ = s; mac (nm_context_signature, s); return *this; }
    context_t& path (const ::std::string& s);
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
    context_t& replace (const vstr_t& s) { replace_ = s; mac (nm_context_replace, s); return *this; }
    context_t& report (const vstr_t& s) { report_ = s; mac (nm_context_report, s); return *this; }
    context_t& report_error (const e_severity sev) noexcept { report_error_ = sev; return *this; }
    context_t& revoke (const bool b) { revoke_ = b; if (b) external (b); return *this; }
    context_t& rfc_1867 (const bool b) { rfc_1867_ = b; mac (nm_context_rfc_1867, b); return *this; }
    context_t& rfc_1942 (const bool b) { rfc_1942_ = b; mac (nm_context_rfc_1942, b); return *this; }
    context_t& rfc_1980 (const bool b) { rfc_1980_ = b; mac (nm_context_rfc_1980, b); return *this; }
    context_t& rfc_2070 (const bool b) { rfc_2070_ = b; mac (nm_context_rfc_2070, b); return *this; }
    context_t& robtxt (const bool b) { robots_ = b; mac (nm_context_robots, b); return *this; }
    context_t& root (const ::std::string& s);
    context_t& rpt_opens (const bool b) noexcept { rpt_opens_ = b; return *this; }
    context_t& rsl_ext (const vstr_t& s) { rsl_ext_ = vtos (s); mac (nm_context_rsl_exts, s); return *this; }
    context_t& rsl_verify (const bool b) { rsl_verify_ = b; mac (nm_context_rsl_ver, b); return *this; }
    context_t& rss_ext (const vstr_t& s) { rss_ext_ = vtos (s); mac (nm_context_rss_exts, s); return *this; }
    context_t& rss_verify (const bool b) { rss_verify_ = b; mac (nm_context_rss_ver, b); return *this; }
    context_t& rss_version (const e_rss_version v) { rss_version_ = v; mac < int > (nm_context_rss_version, v); return *this; }
    context_t& ruby (const bool b) { ruby_ = b; mac (nm_context_ruby, b); return *this; }
    context_t& safari (const bool b) { safari_ = b; mac (nm_context_safari, b); return *this; }
    context_t& sectxt (const bool b) { sectxt_ = b; mac (nm_context_security, b); return *this; }
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
    context_t& sign (const bool b) { verify_ = sign_ = b; mac (nm_context_sign, b); return *this; }
    context_t& silence (nitpick& nits, const vstr_t& s);
    context_t& silence (nitpick& nits, const ::std::string& s);
    context_t& silent (const ::std::string& s) { silent_.push_back (s); return *this; }
    context_t& site (const vstr_t& s) { site_ = vtos (s); mac (nm_context_site, s); return *this; }
    context_t& site (const sstr_t& s) { site_ = s; mac (nm_context_site, s); return *this; }
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
    context_t& stylesheet (const ::boost::filesystem::path& s) { stylesheet_ = s; mac (nm_context_stylesheet, s); return *this; }
    context_t& svg (const ::std::string& s) { svg_ = s; return *this; }
    context_t& svg_mode (const e_svg_processing_mode m) noexcept { svg_mode_ = m; return *this; }
    context_t& svg_version (const int mjr, const int mnr);
    context_t& svg_version (const e_svg_version v) { version_.svg_version (v); mac < int > (nm_context_svg_version, v); return *this; }
    context_t& test (const bool b) { test_ = b; mac (nm_context_test, b); return *this; }
    context_t& title (const ::std::size_t n);
    context_t& todo (const e_do e) noexcept { do_ = e; return *this; }
    context_t& unknown_class (const bool b) { unknown_class_ = b; mac (nm_context_unknown_class, b); return *this; }
    context_t& update (const bool b) noexcept { update_ = b; return *this; }
    context_t& update_check (const bool b) noexcept { update_check_ = b; return *this; }
    context_t& urlvar (const vstr_t& s) { url_var_ = s; mac (nm_context_url_var, s); return *this; }
    context_t& username (const ::std::string& s) { username_ = s; return *this; }
    context_t& vcs (const bool b) { vcs_ = b; mac (nm_context_vcs, b); return *this; }
    context_t& verbose (const e_severity i) noexcept { verbose_ = i; return *this; }
    context_t& verify (const bool b) { verify_ = b; mac (nm_context_verify, b); return *this; }
    context_t& versioned (const bool b) noexcept { versioned_ = b; return *this; }
    context_t& virtuals (const vstr_t& s) { virtuals_ = s; mac (nm_context_virtuals, s); return *this; }
    context_t& vtt_extension (const vstr_t& s) { vtt_ext_ = vtos (s); mac (nm_context_vtt_extension, s); return *this; }
    context_t& vvext (const ::std::size_t n, const vstr_t& v) { if (vvext_.size () <= n) vvext_.resize (n+1); vvext_.at (n) = v; return *this; }
    context_t& warning (const ::std::string& s) { warning_.push_back (s); return *this; }
    context_t& wx (const bool b) { wx_ = b; mac (nm_context_wx, b); return *this; }
    context_t& wx_snippet (const ::std::string& s) { wx_snippet_ = s; return *this; }
    context_t& x (const ::std::string& s) { x_ = s; return *this; }
    context_t& yggdrisil (const bool b) { yggdrisil_ = b; return *this; }
    context_t& mobile_profile (const bool b) { if (b) version_.set_profile (H3_NOT_MOBILE); else version_.reset_profile (H3_NOT_MOBILE); return *this; }
    context_t& print_profile (const bool b) { if (b) version_.set_profile (H3_NOT_PRINT); else version_.reset_profile (H3_NOT_PRINT); return *this; }
    context_t& tv_profile (const bool b) { if (b) version_.set_profile (H3_NOT_TV); else version_.reset_profile (H3_NOT_TV); return *this; }
    int parameters (nitpick& nits, const vstr_t& vs);
    const vstr_t& abhorrent () const { return abhorrent_; }
    bool absolute_path () const noexcept { return absolute_path_; }
    const ::std::string& accept () const { return accept_; }
    const ::std::string& account () const { return account_; }
    const ads& con () const;
    ads& con ();
    bool adstxt () const noexcept { return adstxt_; }
    e_analysis analysis () const noexcept { return anal_; }
    void apply_vcs (nitpick& nits);
    bool aria () const noexcept { return aria_; }
    bool article () const noexcept { return article_; }
    const sstr_t& atomic_ext () const { return atomic_ext_; }
    bool atomic_verify () const noexcept { return atom_verify_; }
    const vstr_t& attrib () const { return attrib_; }
    const ::boost::filesystem::path& back () const { return back_; }
    bool body () const noexcept { return body_; }
    const ::std::string& build () const { return build_; }
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
    const ::boost::filesystem::path& config () const { return config_; }
    ::boost::filesystem::path& config () { return config_; }
    e_copy copy () const noexcept { return copy_; }
    const ::boost::filesystem::path& corpus () const { return corpus_; }
    bool crosslinks () const noexcept { return crosslinks_; }
    const sstr_t& css_extension () const { return css_ext_; }
    int css_module (const e_css_module m) const { return version_.css_module (m); }
    e_css_version css_version () const noexcept { return version_.css_version (); }
    const sstr_t& custom_elements () const { return custom_elements_; }
    const ::boost::filesystem::path& cwd () const { return cwd_; }
    const vstr_t& debug () const { return debug_; }
    const ::boost::filesystem::path& default_config_file () const { return def_conf_file_; }
    const ::boost::filesystem::path& default_config_path () const { return def_conf_path_; }
    const vstr_t& dict () const { return dict_; }
    const vstr_t& dlang () const { return dlang_; }
    bool dodedu () const noexcept { return (copy_ >= c_deduplicate); }
    const ::std::string& domsg () const { return domsg_; }
    bool efficient () const noexcept { return ! sloven_; }
    const vstr_t& elem () const { return elem_; }
    const vstr_t& elem_attrib () const { return elem_attrib_; }
    const ::std::string& environment (const e_environment e) const { return environment_.at (e); }
    const vstr_t& error () const { return error_; }
    bool example () const noexcept { return example_; }
    bool excl_def_excl () const noexcept { return excl_; }
    const vstr_t& exclude () const { return exclude_; }
    bool excluded (nitpick& nits, const ::boost::filesystem::path& p) const;
    bool expand () const noexcept { return expand_; }
    bool export_defined () const noexcept { return ! export_root_.empty (); }
    const ::std::string& export_root () const { return export_root_; }
    const vstr_t& exports () const { return exports_; }
    const sstr_t& extensions () const { return extensions_; }
    bool external () const noexcept { return external_; }
    bool ext_css () const noexcept { return ext_css_; }
    bool extra () const noexcept { return extra_; }
    bool force_version () const noexcept { return force_version_; }
    bool forwarded () const noexcept{ return forwarded_; }
    ::std::size_t fred () const noexcept{ return fred_; }
    const ::std::string& general_info () const { return general_info_; }
    bool gui () const noexcept { return gui_; }
    bool has_math () const noexcept { return version_.has_math (); }
    bool has_rdfa () const noexcept { return rdfa () || (version_.is_svg_12 ()) || (version_ == xhtml_2); }
    bool has_svg () const noexcept { return version_.has_svg (); }
    const ::std::string& help () const { return help_; }
    const ::boost::filesystem::path& home () const { return home_; }
    const html_version& html_ver () const noexcept { return version_; }
    html_version& html_ver () noexcept { return version_; }
    html_version html_ver (const int major, const int minor) noexcept;
    bool icu () const noexcept { return icu_; }
    bool ie () const noexcept { return ie_; }
    const vstr_t& ignore () const { return ignore_; }
    bool info () const noexcept { return info_; }
    const vstr_t& inform () const { return inform_; }
    const ::std::string& index () const { return index_; }
    bool iterate () const noexcept { return iterate_; }
    bool invalid () const noexcept { return ! valid_; }
    bool jsonld () const noexcept { return jsonld_; }
    const sstr_t& jsonld_extension () const { return jsonld_ext_; }
    const vstr_t& jsonld_key () { return jsonld_key_; }
    const vstr_t& jsonld_ontology () const { return jsonld_ont_; }
    const vstr_t& jsonld_value () { return jsonld_val_; }
    e_jsonld_version jsonld_version () const noexcept { return version_.jsonld_version (); }
    const ::std::string& lang () const { return lang_; }
    bool local () const noexcept { return local_; }
    long line_length () const noexcept { return line_length_; }
    bool links () const noexcept { return links_; }
    bool load_css () const noexcept { return load_css_; }
    bool load_vtt () const noexcept { return load_vtt_; }
    const ::std::string& macro_end () const { return macro_end_; }
    const ::std::string& macro_start () const { return macro_start_; }
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
    const vstr_t& naughty () const { return naughty_; }
    bool netscape () const noexcept { return netscape_; }
    const vstr_t& nice () const { return nice_; }
    bool nids () const noexcept { return nids_; }
    bool nits () const noexcept { return nits_; }
    bool nits_nits_nits () const noexcept { return nits_nits_nits_; }
    const sstr_t& no_ex_check () const { return no_ex_check_; }
    bool not_root () const noexcept { return not_root_; }
    const vstr_t& note () const { return note_; }
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
    const ::std::string& out_copy () const { return out_copy_; }
    const ::std::string& out_name () const { return out_; }
    const vstr_t& output_description () const { return output_description_; }
    const ::std::string& output_format () const
    {   if (output_override_.empty ()) return output_format_;
        return output_override_; }
    const ::std::string& output_override () const { return output_override_; }
    const ::std::string& output_time () const { return output_time_; }
    ::boost::filesystem::path output_password () const { return output_password_; }
    const ::boost::filesystem::path& output_private () const { return output_private_; }
    const ::boost::filesystem::path& output_public () const { return output_public_; }
    const ::boost::filesystem::path& output_signature () const { return output_signature_; }
    const ::std::string& path () const { return path_; }
    const ::std::string& persisted () const { return persisted_; }
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
    const vstr_t& replace () const { return replace_; }
    const vstr_t& report () const { return report_; }
    e_severity report_error () const noexcept { return report_error_; }
    bool revoke () const noexcept { return revoke_; }
    bool rfc_1867 () const noexcept { return rfc_1867_; }
    bool rfc_1942 () const noexcept { return rfc_1942_; }
    bool rfc_1980 () const noexcept { return rfc_1980_; }
    bool rfc_2070 () const noexcept { return rfc_2070_; }
    const robotic& robbie () const;
    robotic& robbie ();
    bool robtxt () const noexcept { return robots_; }
    const ::std::string& root () const { return root_; }
    bool rpt_opens () const noexcept { return rpt_opens_; }
    const sstr_t& rsl_ext () const { return rsl_ext_; }
    bool rsl_verify () const noexcept { return rsl_verify_; }
    const sstr_t& rss_ext () const { return rss_ext_; }
    bool rss_verify () const noexcept { return rss_verify_; }
    e_rss_version rss_version () const { return rss_version_; }
    bool ruby () const noexcept { return ruby_; }
    const ::boost::filesystem::path& rootp () const { return proot_; }
    bool safari () const noexcept { return safari_; }
    const sec_txt& security () const;
    sec_txt& security ();
    bool sectxt () const noexcept { return sectxt_; }
    bool serve () const noexcept { return serve_; }
    bool shadow_any () const noexcept { return shadow_pages (); }
    bool shadow_comment () const noexcept { return shadow_comment_; }
    bool shadow_changed () const noexcept { return shadow_changed_; }
    bool shadow_enable () const noexcept { return shadow_enable_; }
    bool shadow_files () const noexcept { return ((copy_ > c_html) && (copy_ <= c_deduplicate)); }
    const vstr_t& shadow_ignore () const { return shadow_ignore_; }
    bool shadow_pages () const noexcept { return ((copy_ > c_none) && (copy_ <= c_deduplicate)); }
    const ::std::string& shadow_persist () const { return shadow_persist_; }
    const ::std::string& shadow_root () const { return shadow_; }
    bool shadow_ssi () const noexcept { return shadow_ssi_; }
    bool shadow_space () const noexcept { return shadow_space_; }
    const vstr_t& shadows () const { return shadows_; }
    bool sign () const noexcept { return sign_; }
    const vreg_t& silence () const { return silence_; }
    bool silenced (const ::std::string& site_path);
    const vstr_t& silent () const { return silent_; }
    const sstr_t& site () const { return site_; }
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
    const ::boost::filesystem::path& stylesheet () const { return stylesheet_; }
    const ::std::string& svg () const { return svg_; }
    e_svg_processing_mode svg_mode () const noexcept { return svg_mode_; }
    e_svg_version svg_version () const noexcept { return version_.svg_version (); }
    bool test () const noexcept { return test_ && output_override_.empty (); }
    ::std::size_t title () const noexcept { return title_; }
    e_do todo () const noexcept { return do_; }
    bool unknown_class () const noexcept { return unknown_class_; }
    bool update () const noexcept { return update_; }
    bool update_check () const noexcept { return update_check_; }
    const ::std::string& update_info () const noexcept { return update_info_; }
    const vstr_t& urlvar () const { return url_var_; }
    const ::std::string& username () const { return username_; }
    bool vcs () const noexcept { return vcs_; }
    e_severity verbose () const noexcept { return verbose_; }
    bool verify () const noexcept { return verify_; }
    bool versioned () const noexcept { return versioned_; }
    const vstr_t& virtuals () const { return virtuals_; }
    const sstr_t& vtt_extension () const { return vtt_ext_; }
    const vstr_t vvext (const ::std::size_t n) const
    {   if (vvext_.size () <= n) return vstr_t ();
        return vvext_.at (n); }
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
    bool lists () const
    {   return ! tim_.empty (); }
    bool naughty_test (const ::std::string& s) const
    {   return tim_.test (s); }
    bool naughty_test (const e_element e, const ::std::string& s) const
    {   return tim_.test (e, s); }
    bool naughty_test (const e_element e, const e_attribute a, const ::std::string& s) const
    {   return tim_.test (e, a, s); }
    bool naughty_test (const e_ontology_property p, const ::std::string& s) const 
    {   return tim_.test (p, s); }
    bool naughty_test (const e_property c, const ::std::string& s) const 
    {   return tim_.test (c, s); }
    bool naughty_test (const e_type t, const ::std::string& s) const 
    {   return tim_.test (t, s); }
    const ::std::string naughty_sub () const
    {   return tim_.sub (); }
    ::std::string naughty_sub (const e_element e) const
    {   return tim_.sub (e); }
    ::std::string naughty_sub ( const e_element e, const e_attribute a) const
    {   return tim_.sub (e, a); }
    ::std::string naughty_sub (const e_ontology_property p) const
    {   return tim_.sub (p); }
    ::std::string naughty_sub (const e_property c) const
    {   return tim_.sub (c); }
    ::std::string naughty_sub (const e_type t) const
    {   return tim_.sub (t); }
    bool profile_checks () const { return version_.profile_checks (); }
    bool mobile_profile () const { return version_.mobile_profile (); }
    bool print_profile () const { return version_.print_profile (); }
    bool tv_profile () const { return version_.tv_profile (); }
    bool has_extension (const ::std::string& name, const sstr_t& extensions) const;
    bool is_ads (const ::std::string& name) const;
    bool is_atomic (const ::std::string& name) const;
    bool is_css (const ::std::string& name) const;
    bool is_jsonld (const ::std::string& name) const;
    bool is_robotic (const ::std::string& name) const;
    bool is_rsl (const ::std::string& name) const;
    bool is_rss (const ::std::string& name) const;
    bool is_sec_txt (const ::std::string& name) const;
    bool is_vtt (const ::std::string& name) const;
    bool is_webpage (const ::std::string& name) const;
    bool loop () const noexcept { return (iterate () || serve ()); }
    e_verifiable_file verifiable_file_type (const ::std::string& name) const;
    static void check_ssi_naughtiness (nitpick& nits, const ::std::string& s);
    ::std::string make_absolute_url (const ::std::string& link, bool can_use_index = true) const;
    void process_url_vars (nitpick& nits);
    ::std::string url_var_value (nitpick& nits, const ::std::string& var, const bool sauce = false, const bool zeq = false);
    ::std::string report (const e_gui_report gr, const bool wibble) const;
    bool write (nitpick& nits, const ::boost::filesystem::path& fn) const; };

extern context_t context;
