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

#pragma once
#include "feedback/nitpick.h"
#include "feedback/nitout.h"
#include "webmention/irt.h"
#include "webmention/hook.h"
#include "css/css_cache.h"
#include "stats/stats.h"
#include "parser/html_version.h"
#include "schema/schema_version.h"

#define VALID_RESULT 0
#define STOP_OK 1
#define NOTHING_TO_DO 2
#define ERROR_STATE 3
#define DEFAULT_MAX_FILE_SIZE 4
#define DMFS_BYTES (DEFAULT_MAX_FILE_SIZE * 1024 * 1024)

constexpr e_verbose default_output = e_warning;
class hook;
class replies;
class corpus;

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i);
::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator from, ::std::string::const_iterator to);
::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i, const ::std::string& msg, const e_verbose level = e_comment);

class context_t
{   bool            article_ = false, body_ = true, case_ = true, cgi_ = false, checking_urls_ = false, clear_ = false, codes_ = false, crosslinks_ = true, example_ = true,
                    external_ = false, fe_ = false, forwarded_ = true, icu_ = true, info_ = false, jsonld_ = false, local_ = true, load_css_ = true, links_ = true, main_ = false,
                    md_export_ = false, meta_ = false, mf_export_ = false, mf_verify_ = true, microdata_ = true, nids_ = false, nits_ = false, nits_nits_nits_ = false,
                    notify_ = false, not_root_ = false, once_ = true, presume_tags_ = false, process_webmentions_ = false, progress_ = false, rdfa_ = true, rel_ = false,
                    repeated_ = false, revoke_ = false, rfc_1867_ = true, rfc_1942_ = true, rfc_1980_ = true, rfc_2070_ = true, rpt_opens_ = false, sarcasm_ = false,
                    schema_ = true, shadow_comment_ = true, shadow_changed_ = false, shadow_enable_ = false, shadow_ssi_ = true, shadow_space_ = true, slob_ = false,
                    spell_ = true, spell_deduced_ = false, ssi_ = true, stats_page_ = false, stats_summary_ = false, test_ = false, unknown_class_ = true, update_ = false,
                    valid_ = false, versioned_ = false;
    int             code_ = 0, title_ = MAX_IDEAL_TITLE_LENGTH;
    e_copy          copy_ = c_none;
    unsigned char   mf_version_ = 3;
    html_version    version_;
    long            max_file_size_ = DMFS_BYTES;
    e_verbose       verbose_ = default_output;
    e_severity      report_error_ = es_error;
    ::std::string   domsg_, export_root_, filename_, general_info_, incoming_, index_, lang_, macro_end_ = "}}", macro_start_ = "{{", msg_, nit_format_,
                    nit_override_, output_, path_, persisted_, root_, secret_, server_, shadow_, shadow_persist_, snippet_, stats_, stub_, test_header_, user_,
                    webmention_, write_path_;
    ::boost::filesystem::path config_, corpus_, spell_path_;
    e_wm_status     wm_status_ = wm_undefined;
    vstr_t          custom_elements_, environment_, exports_, extensions_, jsonld_ext_, mentions_, no_ex_check_, report_, shadow_ignore_, shadows_, site_, spellings_, templates_, virtuals_;
    replies         replies_;
    hooks           hooks_;
    css_cache       css_;
    ::std::unique_ptr < ::std::ofstream > fos_;
    stats_t         data_;
    ::boost::program_options::options_description validation_;
    e_svg_processing_mode svg_mode_ = spm_none;
    mmac_t          mmac_;
    e_quote_style   quote_style_ = qs_none;
    e_do            do_ = do_booboo;
    unsigned        dot_ = 0;
    ::std::string ensane (const ::std::string& s) const;
    template < typename T > void mac (const e_nit_macro ns, const T n)
    {   mmac_.emplace (ns, ::boost::lexical_cast < ::std::string > (n)); }
    void mac (const e_nit_macro ns, const bool b)
    {   if (b) mmac_.emplace (ns, "true");
        else mmac_.emplace (ns, "false"); }
    void mac (const e_nit_macro ns, const ::std::string& s)
    {   mmac_.emplace (ns, s); }
   void mac (const e_nit_macro ns, const char *sz)
    {   mmac_.emplace (ns, ::std::string (sz)); }
    void mac (const e_nit_macro ns, const vstr_t& s)
    {   ::std::string ss;
        for (auto sss: s)
        {   if (! ss.empty ()) ss += ",";
            ss += quote (sss); }
        mmac_.emplace (ns, ss); }
public:
    context_t ();
    int parameters (nitpick& nits, int argc, char** argv);
    bool article () const noexcept { return article_; }
    bool body () const noexcept { return body_; }
    bool cased () const noexcept { return case_; }
    bool cgi () const noexcept { return cgi_; }
    bool checking_urls () const noexcept { return checking_urls_; }
    bool clear () const noexcept { return clear_; }
    int code () const noexcept { return code_; }
    bool codes () const noexcept { return codes_; }
    ::boost::filesystem::path config () const { return config_; }
    e_copy copy () const noexcept { return copy_; }
    ::boost::filesystem::path corpus () const { return corpus_; }
    bool crosslinks () const noexcept { return crosslinks_; }
    const vstr_t custom_elements () const { return custom_elements_; }
    bool dodedu () const noexcept { return (copy_ >= c_deduplicate); }
    const ::std::string domsg () const { return domsg_; }
    const ::std::string environment (const e_environment e) const { return environment_.at (e); }
    bool example () const noexcept { return example_; }
    bool export_defined () const noexcept { return ! export_root_.empty (); }
    const ::std::string export_root () const { return export_root_; }
    const vstr_t exports () const { return exports_; }
    const vstr_t extensions () const { return extensions_; }
    bool external () const noexcept { return external_; }
    bool fe () const noexcept { return fe_; }
    const ::std::string filename () const { return filename_; }
    bool forwarded () const  noexcept{ return forwarded_; }
    const ::std::string general_info () const { return general_info_; }
    bool has_math () const noexcept { return version_.has_math (); }
    bool has_rdfa () const noexcept { return rdfa () || (version_.is_svg_12 ()) || (version_ == xhtml_2); }
    bool has_svg () const noexcept { return version_.has_svg (); }
    html_version html_ver () const noexcept { return version_; }
    html_version& html_ver () noexcept { return version_; }
    html_version html_ver (const int major, const int minor) noexcept;
    bool icu () const noexcept { return icu_; }
    const ::std::string incoming () const { return incoming_; }
    const ::std::string index () const { return index_; }
    bool info () const noexcept { return info_; }
    bool invalid () const noexcept { return ! valid_; }
    bool jsonld () const noexcept { return jsonld_; }
    const vstr_t jsonld_extension () const { return jsonld_ext_; }
    e_jsonld_version jsonld_version () const noexcept { return version_.jsonld_version (); }
    ::std::string lang () const { return lang_; }
    bool local () const noexcept { return local_; }
    bool links () const noexcept { return links_; }
    bool load_css () const noexcept { return load_css_; }
    const ::std::string macro_end () const { return macro_end_; }
    const ::std::string macro_start () const { return macro_start_; }
    const mmac_t& macros () const noexcept { return mmac_; }
    mmac_t& macros () noexcept { return mmac_; }
    bool main () const noexcept { return main_; }
    e_math_version math_version () const noexcept { return version_.math_version (); }
    unsigned long max_file_size () const noexcept { return ::gsl::narrow_cast < unsigned long > (max_file_size_); }
    bool md_export () const noexcept { return md_export_; }
    const vstr_t mentions () const { return mentions_; }
    bool meta () const noexcept { return meta_; }
    bool mf_export () const noexcept { return mf_export_; }
    bool mf_verify () const noexcept { return mf_verify_; }
    bool mf_version1 () const noexcept { return (mf_version_ & 1) != 0; }
    bool mf_version2 () const noexcept { return (mf_version_ & 2) != 0; }
    bool microdata () const noexcept { return microdata_; }
    bool microformats () const noexcept { return mf_verify_ || mf_export_; }
    ::std::string msg () const { return msg_; }
    bool nids () const noexcept { return nids_; }
    ::std::string nit_format () const
    {   if (nit_override_.empty () && ! test ()) return nit_format_;
        return nit_override_; }
    bool nits () const noexcept { return nits_; }
    bool nits_nits_nits () const noexcept { return nits_nits_nits_; }
    const vstr_t no_ex_check () const { return no_ex_check_; }
    bool notify () const noexcept { return notify_; }
    bool not_root () const noexcept { return not_root_; }
    bool once () const noexcept { return once_; }
    ::std::string output () const { return output_; }
    bool presume_tags () const noexcept { return presume_tags_; }
    ::std::string path () const { return path_; }
    const ::std::string persisted () const { return persisted_; }
    bool process_webmentions () const noexcept { return process_webmentions_; }
    bool progress () const noexcept { return progress_; }
    e_quote_style quote_style () const noexcept { return quote_style_; }
    bool rdfa () const noexcept;
    e_rdf_version rdf_version () const noexcept { return version_.rdf_version (); }
    bool rel () const noexcept { return rel_; }
    bool repeated () const noexcept { return repeated_; }
    const vstr_t report () const { return report_; }
    e_severity report_error () const noexcept { return report_error_; }
    bool revoke () const noexcept { return revoke_; }
    bool rfc_1867 () const noexcept { return rfc_1867_; }
    bool rfc_1942 () const noexcept { return rfc_1942_; }
    bool rfc_1980 () const noexcept { return rfc_1980_; }
    bool rfc_2070 () const noexcept { return rfc_2070_; }
    bool rpt_opens () const noexcept { return rpt_opens_; }
    const ::std::string root () const { return root_; }
    bool sarcasm () const noexcept { return sarcasm_; }
    bool schema () const noexcept { return schema_; }
    schema_version schema_ver (const e_schema es = s_schema) const
    {   return get_default_schema_version (es); }
    const ::std::string secret () const { return secret_; }
    const ::std::string server () const { return server_; }
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
    const vstr_t site () const { return site_; }
    bool slob () const noexcept { return slob_; }
    bool spell () const noexcept { return spell_; }
    bool spell_deduced () const noexcept { return spell_deduced_; }
    const vstr_t spellings () const { return spellings_; }
    ::boost::filesystem::path spell_path () const { return spell_path_; }
    ::std::string snippet () const { return snippet_; }
    bool ssi () const noexcept { return ssi_; }
    const ::std::string stats () const { return stats_; }
    bool stats_summary () const noexcept { return stats_summary_; }
    bool stats_page () const noexcept { return stats_page_; }
    const ::std::string stub () const { return stub_; }
    e_svg_processing_mode svg_mode () const noexcept { return svg_mode_; }
    e_svg_version svg_version () const noexcept { return version_.svg_version (); }
    const vstr_t templates () const { return templates_; }
    bool test () const noexcept { return test_ && nit_override_.empty (); }
    const ::std::string test_header () const { return test_header_; }
    int title () const noexcept { return title_; }
    e_do todo () const noexcept { return do_; }
    bool unknown_class () const noexcept { return unknown_class_; }
    const ::std::string user () const { return user_; }
    e_verbose verbose () const noexcept { return verbose_; }
    const vstr_t virtuals () const { return virtuals_; }
    const ::std::string webmention () const { return webmention_; }
    const ::std::string write_path () const { return write_path_; }
    bool update () const noexcept { return update_; }
    bool versioned () const noexcept { return versioned_; }
    context_t& article (const bool b) { article_ = b; mac (nm_context_article, b); return *this; }
    context_t& body (const bool b) { body_ = b; mac (nm_context_body, b); return *this; }
    context_t& cased (const bool b) { case_ = b; mac (nm_context_case, b); return *this; }
    context_t& cgi (const bool b) { cgi_ = b; mac (nm_context_cgi, b); return *this; }
    context_t& checking_urls (const bool b) noexcept { checking_urls_ = b; return *this; }
    context_t& clear (const bool b) { clear_ = b; mac (nm_context_clear, b); return *this; }
    context_t& code (const int i) { code_ = i; mac < int > (nm_context_code, i); return *this; }
    context_t& codes (const bool b) noexcept { codes_ = b; return *this; }
    context_t& config (const ::boost::filesystem::path& c) { config_ = c; mac (nm_context_config, c.string ()); return *this; }
    context_t& copy (const int c)
    {   if ((c > c_none) && (c <= c_rpt)) copy_ = static_cast < e_copy > (c);
        else copy_ = c_none;
        mac < int > (nm_context_code, c);
        return *this; }
    context_t& corpus (const ::boost::filesystem::path& f) { corpus_ = f; mac (nm_context_corpus, f.string ()); return *this; }
    context_t& crosslinks (const bool b) { crosslinks_ = b; mac (nm_context_crosslinks, b); return *this; }
    css_cache& css () noexcept { return css_; }
    const css_cache& css () const noexcept { return css_; }
    context_t& custom_elements (const vstr_t& s) { custom_elements_ = s; mac (nm_context_custom_elements, s); return *this; }
    context_t& domsg (const ::std::string& s) { domsg_ = s; return *this; }
    context_t& environment (const e_environment e, const ::std::string& s);
    context_t& example (const bool b) { example_ = b; mac (nm_context_example, b); return *this; }
    context_t& export_root (const ::std::string& s) { export_root_ = s; mac (nm_context_export_root, s); return *this; }
    context_t& exports (const vstr_t& s) { exports_ = s; mac (nm_context_exports, s); return *this; }
    context_t& extensions (const vstr_t& s) { extensions_ = s; mac (nm_context_extensions, s); return *this; }
    context_t& external (const bool b)
    {   external_ = b;
        if (b) links (b);
        else { forwarded (false); once (false); revoke (false); microdata (false); }
        return *this; }
    context_t& fe (const bool b) { fe_ = b; mac (nm_context_fe, b); return *this; }
    context_t& filename (const ::std::string& s) { filename_ = s; mac (nm_context_filename, s); return *this; }
    context_t& forwarded (const bool b)
    {   forwarded_ = b;
        mac (nm_context_forward, b);
        if (b) external (b);
        return *this; }
    context_t& general_info (const ::std::string& s) { general_info_ = s; mac (nm_general_info, s); return *this; }
    context_t& html_ver (const html_version& v)
    {   versioned (true); version_ = v; mac (nm_context_version, version_.name ()); return *this; }
    context_t& icu (const bool b) { icu_ = b; mac (nm_context_info, b); return *this; }
    context_t& ignore (nitpick& nits, const vstr_t& s);
    context_t& incoming (const ::std::string& s) { incoming_ = s; return *this; }
    context_t& index (const ::std::string& s) { index_ = s; mac (nm_context_index, s); return *this; }
    context_t& info (const bool b) { info_ = b; mac (nm_context_info, b); return *this; }
    context_t& jsonld (const bool b) { jsonld_ = b; mac (nm_context_jsonld, b); return *this; }
    context_t& jsonld_extension (const vstr_t& s) { jsonld_ext_ = s; mac (nm_context_jsonld_extension, s); return *this; }
    context_t& jsonld_version (const e_jsonld_version v)
    {   version_.jsonld_version (v);
        mac < int > (nm_context_jsonld_version, v);
        return *this; }
    context_t& lang (const ::std::string& s) { lang_ = s; mac (nm_context_lang, s); return *this; }
    context_t& links (const bool b)
    {   links_ = b;
        if (! b) { external (false); }
        mac (nm_context_links, b);
        return *this; }
    context_t& load_css (const bool b) { load_css_ = b; mac (nm_context_css, b); return *this; }
    context_t& local (const bool b) { local_ = b; mac (nm_context_local, b); return *this; }
    context_t& macro_end (const ::std::string& s) { macro_end_ = s; return *this; }
    context_t& macro_start (const ::std::string& s) { macro_start_ = s; return *this; }
    context_t& main (const bool b) { main_ = b; mac (nm_context_main, b); return *this; }
    context_t& math_version (const int v)
    {   if ((v >= 1) && (v <= 4)) version_.math_version (static_cast < e_math_version > (v));
        else version_.math_version (math_none);
        mac < int > (nm_context_math, version_.math_version ());
        return *this; }
    context_t& math_version (const e_math_version v) noexcept { version_.math_version (v); return *this; }
    context_t& max_file_size (const long l) { max_file_size_ = l; mac < long > (nm_context_max_file_size, l);return *this; }
    context_t& md_export (const bool b) { md_export_ = b; mac (nm_context_md_export, b); return *this; }
    context_t& mentions (const vstr_t& s) { mentions_ = s; return *this; }
    context_t& meta (const bool b) { meta_ = b; mac (nm_context_meta, b); return *this; }
    context_t& mf_export (const bool b) { mf_export_ = b; mac (nm_context_mf_export, b); return *this; }
    context_t& mf_verify (const bool b) { mf_verify_ = b; mac (nm_context_mf_verify, b); return *this; }
    context_t& mf_version (const unsigned char n)
    {   mf_version_ = n;
        mac < int > (nm_context_mf_version, n);
        if (n <= 1) set_default_schema_version (s_microformats, 1, 0);
        else set_default_schema_version (s_microformats, 2, 0);
        return *this; }
    context_t& microdata (const bool b)
    {   microdata_ = b;
        if (b) external (b);
        mac (nm_context_microdata, b);
        return *this; }
    context_t& msg (const ::std::string& s) { msg_ = s; return *this; }
    context_t& nids (const bool b) noexcept { nids_ = b; return *this; }
    context_t& nit_format (const ::std::string& nf)
    {   nit_format_ = nf;
        mmac_.emplace (mn_nits_format, nf);
        return *this; }
    context_t& nit_override (const ::std::string& nf) { nit_override_ = nf; return *this; }
    context_t& nits (const bool b) noexcept { nits_ = b; return *this; }
    context_t& nits_nits_nits (const bool b) noexcept { nits_nits_nits_ = b; return *this; }
    context_t& no_ex_check (const vstr_t& s) { no_ex_check_ = s; mac (nm_context_no_ex_check, s); return *this; }
    context_t& notify (const bool b) noexcept { notify_ = b; return *this; }
    context_t& not_root (const bool b) noexcept { not_root_ = b; return *this; }
    context_t& once (const bool b)
    {   once_ = b;
        if (b) external (b);
        mac (nm_context_once, b);
        return *this; }
    context_t& output (nitpick& nits, const ::std::string& s);
    context_t& path (const ::std::string& s) { path_ = s; mmac_.emplace (nm_general_path, s); return *this; }
    context_t& persisted (const ::std::string& s) { persisted_ = s; mac (nm_context_persisted, s); return *this; }
    context_t& presume_tags (const bool b) { presume_tags_ = b; mac (nm_context_tags, b); return *this; }
    context_t& process_webmentions (const bool b) { process_webmentions_ = b; mac (nm_context_process_webmentions, b); return *this; }
    context_t& progress (const bool b) noexcept { progress_ = b; return *this; }
    context_t& quote_style (const e_quote_style qs) noexcept { quote_style_ = qs; return *this; }
    context_t& rdfa (const bool b) { rdfa_ = b; mac (nm_context_rdfa, b); return *this; }
    context_t& rdf_version (const e_rdf_version v) { version_.rdf_version (v); mac < int > (nm_context_rdf_version, v); return *this; }
    context_t& rel (const bool b) { rel_ = b; mac (nm_context_rel, b); return *this; }
    context_t& repeated (const bool b) noexcept { repeated_ = b; return *this; }
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
    context_t& root (const ::std::string& s) { root_ = s; mac (nm_context_root, s); return *this; }
    context_t& rpt_opens (const bool b) noexcept { rpt_opens_ = b; return *this; }
    context_t& sarcasm (const bool b) { sarcasm_ = b; mac (nm_context_sarcasm, b); return *this; }
    context_t& schema (const bool b)
    {   schema_ = b;
        mac (nm_context_schema, b);
        return *this; }
    context_t& secret (const ::std::string& s) { secret_ = s; return *this; }
    context_t& server (const ::std::string& s) { server_ = s; return *this; }
    context_t& shadow_comment (const bool b) { shadow_comment_ = b; if (b) shadow_enable (true); mac (nm_context_shadow_comment, b); return *this; }
    context_t& shadow_changed (const bool b) { shadow_changed_ = b; if (b) shadow_enable (true); mac (nm_context_shadow_changed, b); return *this; }
    context_t& shadow_enable (const bool b) { shadow_enable_ = b; mac (nm_context_shadow_enable, b); return *this; }
    context_t& shadow_ignore (const vstr_t& s);
    context_t& shadow_persist (const ::std::string& s) { shadow_persist_ = s; shadow_enable (true); mac (nm_context_shadow_persist, s); return *this; }
    context_t& shadow_root (const ::std::string& s) { shadow_ = s; shadow_enable (true); mac (nm_context_shadow_root, s); return *this; }
    context_t& shadow_ssi (const bool b) { shadow_ssi_ = b; if (b) shadow_enable (true); mac (nm_context_shadow_ssi, b); return *this; }
    context_t& shadow_space (const bool b) { shadow_space_ = b; if (b) shadow_enable (true); mac (nm_context_shadow_space, b); return *this; }
    context_t& shadows (const vstr_t& s) { shadows_ = s; mac (nm_context_shadows, s); shadow_enable (true); return *this; }
    context_t& site (const vstr_t& s) { site_ = s; mac (nm_context_site, s); return *this; }
    context_t& slob (const bool b) { slob_ = b; mac (nm_context_slob, b); return *this; }
    context_t& snippet (const ::std::string& s)
    {   snippet_ = s;
        mmac_.emplace (nm_context_root, "");
        mmac_.emplace (nm_html_snippet, s);
        quote_style (qs_html);
        return *this; }
    context_t& spell (const bool b) { spell_ = b; mac (nm_context_spell, b); return *this; }
    context_t& spell_deduced (const bool b) { spell_deduced_ = b; return *this; }
    context_t& spellings (const vstr_t& s) { spellings_ = s; mac (nm_context_spellings, s); return *this; }
    context_t& spell_path (const ::boost::filesystem::path& f) { spell_path_ = f; mac (nm_context_spell_path, f); return *this; }
    context_t& ssi (const bool b) { ssi_ = b; mac (nm_context_ssi, b); return *this; }
    context_t& stats (const ::std::string& s) { stats_ = s; mac (nm_context_stats_export, s); return *this; }
    context_t& stats_page (const bool b) { stats_page_ = b; mac (nm_context_stats_page, b); return *this; }
    context_t& stats_summary (const bool b) { stats_summary_ = b; mac (nm_context_stats_summary, b); return *this; }
    context_t& stub (const ::std::string& s) { stub_ = s; return *this; }
    context_t& svg_mode (const e_svg_processing_mode m) noexcept { svg_mode_ = m; return *this; }
    context_t& svg_version (const int mjr, const int mnr) noexcept;
    context_t& svg_version (const e_svg_version v) { version_.svg_version (v); mac < int > (nm_context_svg_version, v); return *this; }
    context_t& templates (const vstr_t& s) { templates_ = s; mac (nm_context_templates, s); return *this; }
    context_t& test (const bool b) { test_ = b; mac (nm_context_test, b); return *this; }
    context_t& test_header (const ::std::string& s) { test_header_ = s; return *this; }
    context_t& title (const int n)
    { if (n <= 0) title_ = 0; else title_ = n; mac < int > (nm_context_title, title_); return *this; }
    context_t& todo (const e_do e) noexcept { do_ = e; return *this; }
    context_t& unknown_class (const bool b) noexcept { unknown_class_ = b; return *this; }
    context_t& user (const ::std::string& s) { user_ = s; mac (nm_context_user, s); return *this; }
    context_t& update (const bool b) noexcept { update_ = b; return *this; }
    context_t& verbose (const e_verbose i) noexcept { verbose_ = i; return *this; }
    context_t& versioned (const bool b) noexcept { versioned_ = b; return *this; }
    context_t& virtuals (const vstr_t& s) { virtuals_ = s; mac (nm_context_virtuals, s); return *this; }
    context_t& webmention (nitpick& nits, const ::std::string& w, const e_wm_status status);
    context_t& write_path (const ::std::string& s) { write_path_ = s; mac (nm_context_write_path, s); return *this; }
    void reset_webmention () noexcept
    {   webmention_.clear ();
        wm_status_ = wm_undefined; }
    void note_reply (const ::std::string& file, const ::std::string& id, const ::std::string& target, const ::std::string& content)
    {   if (notify ()) replies_.append (file, id, target, content); }
    replies& get_replies () noexcept { return replies_; }
    void process_outgoing_webmention (nitpick& nits, const html_version& v, const lingo& lang);
    void process_incoming_webmention (nitpick& nits, const html_version& v);
    bool tell (const e_verbose n) const noexcept { return n <= verbose_; }
    void out (const ::std::string& s) const { out () << s; }
    void err (const ::std::string& s) const { err () << ensane (s); }
    ::std::ostream& out () const noexcept { if (fos_) return *fos_; return ::std::cout; }
    ::std::ostream& err () const noexcept { if (fos_) return *fos_; return ::std::cerr; }
    void dot ();
    void dedot () noexcept { dot_ = 0; }
    void mark (const e_element e)
    {   data_.mark (e); }
    void visible (const e_element e)
    {   data_.visible (e); }
    void mark_abbr (const ::std::string& a, const ::std::string& b)
    {   data_.mark_abbr (a, b); }
    void mark_dfn (const ::std::string& a, const ::std::string& b)
    {   data_.mark_dfn (a, b); }
    void mark_dtdd (const ::std::string& a, const ::std::string& b)
    {   data_.mark_dtdd (a, b); }
    void mark (const e_severity s)
    {   data_.mark (s); }
    void mark (const e_category c)
    {   data_.mark (c); }
    void mark (const e_doc d)
    {   data_.mark (d); }
    void mark (const e_element f, const e_attribute m)
    {   data_.mark (f, m); }
    void mark (const html_version& v)
    {   data_.mark (v); }
    void mark (const e_schema_type s)
    {   data_.mark (s); }
    void mark (const e_schema_type s, const e_schema_property p)
    {   data_.mark (s, p); }
    void mark_file (const unsigned size)
    {   data_.mark_file (size); }
    void mark_meta (const e_httpequiv he)
    {   data_.mark_meta (he); }
    void mark_meta (const e_metaname mn)
    {   data_.mark_meta (mn); }
    void mark_meta (const e_metaname mn, const ::std::string& val)
    {   data_.mark_meta (mn, val); }
   void report_stats (const bool grand)
    {   out (data_.report (grand)); }
    uint64_t file_count () const
    {   return data_.file_count (); }
    bool severity_exceeded () const;
    ::boost::program_options::options_description& validation () noexcept { return validation_; }
    const ::boost::program_options::options_description& validation () const noexcept { return validation_; }
    void consolidate_jsonld ()
    {   for (auto j : jsonld_ext_) extensions_.push_back (j); }
    ::std::string make_absolute_url (const ::std::string& link, bool can_use_index = true) const; };

extern context_t context;
