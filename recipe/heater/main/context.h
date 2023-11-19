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

#pragma once
#include "feedback/nitpick.h"
#include "feedback/nitout.h"
#include "main/output.h"
#include "stats/stats.h"
#include "parser/html_version.h"
#include "ontology/ontology_version.h"
#include "feedback/nitout.h"

#define VALID_RESULT 0
#define STOP_OK 1
#define NOTHING_TO_DO 2
#define ERROR_STATE 3
#define DEFAULT_MAX_FILE_SIZE 4
#define DMFS_BYTES (DEFAULT_MAX_FILE_SIZE * 1024 * 1024)

CONSTEXPR e_severity default_output = es_warning;
class replies;
class corpus;

class context_t
{   bool            article_ = false, body_ = true, case_ = false, cgi_ = false, classic_ = false, clear_ = false, crosslinks_ = true, example_ = true,
                    external_ = false, ext_css_ = false, extra_ = false, force_version_ = false, forwarded_ = true, icu_ = true, ie_ = false,
                    info_ = false, jsonld_ = false, local_ = true, load_css_ = true, links_ = true, main_ = false, md_export_ = false, meta_ = false,
                    mf_export_ = false, mf_verify_ = true, microdata_ = true, nids_ = false, nits_ = false, nits_nits_nits_ = false, not_root_ = false,
                    once_ = true, presume_tags_ = false, progress_ = false, rdfa_ = false, rel_ = false, revoke_ = false, rfc_1867_ = true, 
                    rfc_1942_ = true, rfc_1980_ = true, rfc_2070_ = true, rpt_opens_ = false, ontology_ = true, safari_ = false, 
                    shadow_changed_ = false, shadow_comment_ = true, shadow_enable_ = false, shadow_space_ = true, shadow_ssi_ = true, sloven_ = false, 
                    spec_ = false, spell_ = true, spell_deduced_ = false, ssi_ = true, stats_abbr_ = true, stats_annotation_ = true, 
                    stats_category_ = true, stats_character_variant_ = true, stats_class_ = true, stats_content_name_ = true,
                    stats_counter_style_ = true, stats_css_property_ = true, stats_custom_media_ = true, stats_custom_property_ = true,
                    stats_dfn_ = false, stats_dtdd_ = false, stats_element_ = true, stats_file_ = true, stats_font_ = true, stats_font_family_ = true, 
                    stats_highlight_ = false, stats_historical_form_ = false, stats_itemid_ = true, stats_keyframe_ = false, stats_layer_ = false, 
                    stats_meta_ = true, stats_ontology_ = true, stats_ornament_ = false, stats_page_name_ = true, stats_page_ = false, 
                    stats_palette_ = false, stats_reference_ = true, stats_region_ = false, stats_scroll_anim_ = false, stats_statement_ = true, 
                    stats_styleset_ = false, stats_stylistic_ = false, stats_summary_ = false, stats_swash_ = false, stats_version_ = true, 
                    stats_view_ = false, test_ = false, unknown_class_ = true, update_ = false, valid_ = false, versioned_ = false, yggdrisil_ = false;
    int             fred_ = 0, title_ = MAX_IDEAL_TITLE_LENGTH;
    e_copy          copy_ = c_none;
    unsigned char   mf_version_ = 3;
    html_version    version_;
    long            max_file_size_ = DMFS_BYTES;
    e_severity      verbose_ = default_output;
    e_severity      report_error_ = es_error;
    ::std::string   build_, cache_, domsg_, export_root_, general_info_, index_, lang_, macro_end_ = "}}", macro_start_ = "{{", msg_, nit_format_,
                    nit_override_, path_, persisted_, root_, secret_, shadow_, shadow_persist_, snippet_, started_, stats_, x_;
    ::boost::filesystem::path config_, corpus_, spell_path_;
    vstr_t          css_ext_, custom_elements_, environment_, exports_, extensions_, jsonld_ext_, no_ex_check_, report_, shadow_ignore_, shadows_, site_,
                    spellings_, virtuals_;
    ::boost::program_options::options_description validation_;
    vstr_t          exclude_, pretend_;
    e_svg_processing_mode svg_mode_ = spm_none;
    e_quote_style   quote_style_ = qs_none;
    e_do            do_ = do_booboo;
    ::boost::filesystem::path proot_;
    friend class options;
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
    context_t& article (const bool b) { article_ = b; mac (nm_context_article, b); return *this; }
    context_t& body (const bool b) { body_ = b; mac (nm_context_body, b); return *this; }
    context_t& cache (const ::std::string& s) { cache_ = s; return *this; }
    context_t& cased (const bool b) { case_ = b; mac (nm_context_case, b); return *this; }
    context_t& cgi (const bool b) { cgi_ = b; mac (nm_context_cgi, b); spell (false); return *this; }
    context_t& classic (const bool b) { classic_ = b; mac (nm_context_classic, b); return *this; }
    context_t& clear (const bool b) { clear_ = b; mac (nm_context_clear, b); return *this; }
    context_t& config (const ::boost::filesystem::path& c) { config_ = c; mac (nm_context_config, c.string ()); return *this; }
    context_t& copy (const int c)
    {   if ((c > c_none) && (c <= c_rpt)) copy_ = static_cast < e_copy > (c);
        else copy_ = c_none;
        mac < int > (nm_context_copy, c);
        return *this; }
    context_t& corpus (const ::boost::filesystem::path& f) { corpus_ = f; mac (nm_context_corpus, f.string ()); return *this; }
    context_t& crosslinks (const bool b) { crosslinks_ = b; mac (nm_context_crosslinks, b); return *this; }
    context_t& css_adjust (const int n) { version_.css_adjust (n); mac (nm_context_css_adjust, n); return *this; }
    context_t& css_advanced_layout (const int n) { version_.css_advanced_layout (n); mac (nm_context_advanced_layout, n); return *this; }
    context_t& css_anchor (const int n) { version_.css_anchor (n); mac (nm_context_css_anchor, n); return *this; }
    context_t& css_anchor_pos (const int n) { version_.css_anchor_pos (n); mac (nm_context_css_anchor_pos, n); return *this; }
    context_t& css_animation (const int n) { version_.css_animation (n); mac (nm_context_css_animation, n); return *this; }
    context_t& css_background (const int n) { version_.css_background (n); mac (nm_context_css_background, n); return *this; }
    context_t& css_box_alignment (const int n) { version_.css_box_alignment (n); mac (nm_context_css_box_align, n); return *this; }
    context_t& css_box_model (const int n) { version_.css_box_model (n); mac (nm_context_css_box_model, n); return *this; }
    context_t& css_box_sizing (const int n) { version_.css_box_sizing (n); mac (nm_context_css_box_sizing, n); return *this; }
    context_t& css_cascade (const int n) { version_.css_cascade (n); mac (nm_context_css_cascade, n); return *this; }
    context_t& css_colour (const int n) { version_.css_colour (n); mac (nm_context_css_colour, n); return *this; }
    context_t& css_compositing (const int n) { version_.css_compositing (n); mac (nm_context_css_compositing, n); return *this; }
    context_t& css_conditional_rule (const int n) { version_.css_conditional_rule (n); mac (nm_context_css_cond_rule, n); return *this; }
    context_t& css_contain (const int n) { version_.css_contain (n); mac (nm_context_css_contain, n); return *this; }
    context_t& css_content (const int n) { version_.css_content (n); mac (nm_context_css_content, n); return *this; }
    context_t& css_counter_style (const int n) { version_.css_counter_style (n); mac (nm_context_css_cs, n); return *this; }
    context_t& css_custom (const int n) { version_.css_custom (n); mac (nm_context_css_custom, n); return *this; }
    context_t& css_device (const int n) { version_.css_device (n); mac (nm_context_css_device, n); return *this; }
    context_t& css_display (const int n) { version_.css_display (n); mac (nm_context_css_display, n); return *this; }
    context_t& css_ease (const int n) { version_.css_ease (n); mac (nm_context_css_ease, n); return *this; }
    context_t& css_exclude (const int n) { version_.css_exclude (n); mac (nm_context_css_exclude, n); return *this; }
    context_t& css_extension (const vstr_t& s) { css_ext_ = s; mac (nm_context_css_extension, s); return *this; }
    context_t& css_fbl (const int n) { version_.css_fbl (n); mac (nm_context_css_fbl, n); return *this; }
    context_t& css_fill (const int n) { version_.css_fill (n); mac (nm_context_css_fill, n); return *this; }
    context_t& css_filter (const int n) { version_.css_filter (n); mac (nm_context_css_filter, n); return *this; }
    context_t& css_float (const int n) { version_.css_float (n); mac (nm_context_css_float, n); return *this; }
    context_t& css_font (const int n) { version_.css_font (n); mac (nm_context_css_font, n); return *this; }
    context_t& css_fragmentation (const int n) { version_.css_fragmentation (n); mac (nm_context_css_fragmentation, n); return *this; }
    context_t& css_grid (const int n) { version_.css_grid (n); mac (nm_context_css_grid, n); return *this; }
    context_t& css_highlight (const int n) { version_.css_highlight (n); mac (nm_context_css_highlight, n); return *this; }
    context_t& css_hyperlink (const int n) { version_.css_hyperlink (n); mac (nm_context_css_hyperlink, n); return *this; }
    context_t& css_image (const int n) { version_.css_image (n); mac (nm_context_css_image, n); return *this; }
    context_t& css_inline (const int n) { version_.css_inline (n); mac (nm_context_css_inline, n); return *this; }
    context_t& css_line_grid (const int n) { version_.css_line_grid (n); mac (nm_context_css_line_grid, n); return *this; }
    context_t& css_list (const int n) { version_.css_list (n); mac (nm_context_css_lists, n); return *this; }
    context_t& css_logic (const int n) { version_.css_logic (n); mac (nm_context_css_logic, n); return *this; }
    context_t& css_marquee (const int n) { version_.css_marquee (n); mac (nm_context_css_marquee, n); return *this; }
    context_t& css_masking (const int n) { version_.css_masking (n); mac (nm_context_css_masking, n); return *this; }
    context_t& css_media (const int n) { version_.css_media (n); mac (nm_context_css_media, n); return *this; }
    context_t& css_motion (const int n) { version_.css_motion (n); mac (nm_context_css_motion, n); return *this; }
    context_t& css_multi_column (const int n) { version_.css_multi_column (n); mac (nm_context_css_multi_column, n); return *this; }
    context_t& css_namespace (const int n) { version_.css_namespace (n); mac (nm_context_css_namespace, n); return *this; }
    context_t& css_nes (const int n) { version_.css_nes (n); mac (nm_context_css_nes, n); return *this; }
    context_t& css_nesting (const int n) { version_.css_nesting (n); mac (nm_context_css_nesting, n); return *this; }
    context_t& css_overflow (const int n) { version_.css_overflow (n); mac (nm_context_css_overflow, n); return *this; }
    context_t& css_overscroll (const int n) { version_.css_overscroll (n); mac (nm_context_css_overscroll, n); return *this; }
    context_t& css_page (const int n) { version_.css_page (n); mac (nm_context_css_page, n); return *this; }
    context_t& css_position (const int n) { version_.css_position (n); mac (nm_context_css_position, n); return *this; }
    context_t& css_present (const int n) { version_.css_present (n); mac (nm_context_css_present, n); return *this; }
    context_t& css_pseudo (const int n) { version_.css_pseudo (n); mac (nm_context_css_pseudo, n); return *this; }
    context_t& css_region (const int n) { version_.css_region (n); mac (nm_context_css_region, n); return *this; }
    context_t& css_rhythm (const int n) { version_.css_rhythm (n); mac (nm_context_css_rhythm, n); return *this; }
    context_t& css_round (const int n) { version_.css_round (n); mac (nm_context_css_round, n); return *this; }
    context_t& css_ruby (const int n) { version_.css_ruby (n); mac (nm_context_css_ruby, n); return *this; }
    context_t& css_scope (const int n) { version_.css_scope (n); mac (nm_context_css_scope, n); return *this; }
    context_t& css_scrollbar (const int n) { version_.css_scrollbar (n); mac (nm_context_css_scrollbar, n); return *this; }
    context_t& css_sda (const int n) { version_.css_sda (n); mac (nm_context_css_sda, n); return *this; }
    context_t& css_selector (const int n) { version_.css_selector (n); mac (nm_context_css_selector, n); return *this; }
    context_t& css_shadow (const int n) { version_.css_shadow (n); mac (nm_context_css_shadow, n); return *this; }
    context_t& css_shape (const int n) { version_.css_shape (n); mac (nm_context_css_shape, n); return *this; }
    context_t& css_snap (const int n) { version_.css_snap (n); mac (nm_context_css_snap, n); return *this; }
    context_t& css_snap_points (const int n) { version_.css_snap_points (n); mac (nm_context_css_snap_points, n); return *this; }
    context_t& css_spatial (const int n) { version_.css_spatial (n); mac (nm_context_css_spatial, n); return *this; }
    context_t& css_speech (const int n) { version_.css_speech (n); mac (nm_context_css_speech, n); return *this; }
    context_t& css_style (const int n) { version_.css_style (n); mac (nm_context_css_style, n); return *this; }
    context_t& css_syntax (const int n) { version_.css_syntax (n); mac (nm_context_css_syntax, n); return *this; }
    context_t& css_table (const int n) { version_.css_table (n); mac (nm_context_css_table, n); return *this; }
    context_t& css_text (const int n) { version_.css_text (n); mac (nm_context_css_text, n); return *this; }
    context_t& css_text_decoration (const int n) { version_.css_text_decoration (n); mac (nm_context_css_text_decoration, n); return *this; }
    context_t& css_transform (const int n) { version_.css_transform (n); mac (nm_context_css_transform, n); return *this; }
    context_t& css_transition (const int n) { version_.css_transition (n); mac (nm_context_css_transition, n); return *this; }
    context_t& css_ui (const int n) { version_.css_ui (n); mac (nm_context_css_ui, n); return *this; }
    context_t& css_value (const int n) { version_.css_value (n); mac (nm_context_css_value, n); return *this; }
    context_t& css_version (const int mjr, const int mnr);
    context_t& css_version (const e_css_version v) { version_.css_version (v); mac < int > (nm_context_css_version, v); return *this; }
    context_t& css_view (const int n) { version_.css_view (n); mac (nm_context_css_view, n); return *this; }
    context_t& css_writing_mode (const int n) { version_.css_writing_mode (n); mac (nm_context_css_writing_mode, n); return *this; }
    context_t& css_will_change (const int n) { version_.css_will_change (n); mac (nm_context_css_will_change, n); return *this; }
    context_t& custom_elements (const vstr_t& s) { custom_elements_ = s; mac (nm_context_custom_elements, s); return *this; }
    context_t& domsg (const ::std::string& s) { domsg_ = s; return *this; }
    context_t& environment (const e_environment e, const ::std::string& s);
    context_t& example (const bool b) { example_ = b; mac (nm_context_example, b); return *this; }
    context_t& exclude (nitpick& nits, const vstr_t& s);
    context_t& exclude (nitpick& nits, const ::std::string& s);
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
    context_t& fred (const int i);
    context_t& html_ver (const html_version& v)
    {   versioned (true); version_ = v; mac (nm_context_version, version_.name ()); return *this; }
    context_t& icu (const bool b) { icu_ = b; mac (nm_context_icu, b); return *this; }
    context_t& ie (const bool b) { ie_ = b; mac (nm_context_ie, b); return *this; }
    context_t& ignore (nitpick& nits, const vstr_t& s);
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
        mac (nm_context_links, b);
        if (! b) { external (false); }
        return *this; }
    context_t& load_css (const bool b) { load_css_ = b; mac (nm_context_css, b); return *this; }
    context_t& local (const bool b) { local_ = b; mac (nm_context_local, b); return *this; }
    context_t& macro_end (const ::std::string& s) { macro_end_ = s; return *this; }
    context_t& macro_start (const ::std::string& s) { macro_start_ = s; return *this; }
    context_t& main (const bool b) { main_ = b; mac (nm_context_main, b); return *this; }
    bool matches (const ::std::string& s, const ::std::string& w, const char sep = '/') const;
    context_t& math_version (const int v);
    context_t& math_version (const e_math_version v) noexcept { version_.math_version (v); return *this; }
    context_t& max_file_size (const long l) { max_file_size_ = l; mac < long > (nm_context_max_file_size, l);return *this; }
    context_t& md_export (const bool b) { md_export_ = b; mac (nm_context_md_export, b); return *this; }
    context_t& meta (const bool b) { meta_ = b; mac (nm_context_meta, b); return *this; }
    context_t& mf_export (const bool b) { mf_export_ = b; mac (nm_context_mf_export, b); return *this; }
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
    context_t& msg (const ::std::string& s) { msg_ = s; return *this; }
    context_t& nids (const bool b) noexcept { nids_ = b; return *this; }
    context_t& nit_format (const ::std::string& nf)
    {   nit_format_ = nf;
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (mn_nits_format, nf);
        return *this; }
    context_t& nit_override (const ::std::string& nf) { nit_override_ = nf; return *this; }
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
    context_t& path (const ::std::string& s)
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        path_ = s;
        macro -> set (nm_general_path, s);
        return *this; }
    context_t& persisted (const ::std::string& s) { persisted_ = s; mac (nm_context_persisted, s); return *this; }
    context_t& presume_tags (const bool b) { presume_tags_ = b; mac (nm_context_tags, b); return *this; }
    context_t& pretend (nitpick& nits, const vstr_t& s);
    context_t& pretend (nitpick& nits, const ::std::string& s);
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
    context_t& safari (const bool b) { safari_ = b; mac (nm_context_safari, b); return *this; }
    context_t& secret (const ::std::string& s) { secret_ = s; return *this; }
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
    context_t& site (const vstr_t& s) { site_ = s; mac (nm_context_site, s); return *this; }
    context_t& sloven (const bool b) { sloven_ = b; mac (nm_context_sloven, b); return *this; }
    context_t& snippet (const ::std::string& s)
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        snippet_ = s;
        macro -> set (nm_context_root, "");
        macro -> set (nm_html_snippet, s);
        quote_style (qs_html);
        return *this; }
    context_t& spec (const bool b) { spec_ = b; return *this; }
    context_t& spell_deduced (const bool b) { spell_deduced_ = b; return *this; }
    context_t& spellings (const vstr_t& s) { spellings_ = s; mac (nm_context_spellings, s); return *this; }
    context_t& spell_path (const ::boost::filesystem::path& f) { spell_path_ = f; mac (nm_context_spell_path, f); return *this; }
    context_t& ssi (const bool b) { ssi_ = b; mac (nm_context_ssi, b); return *this; }
    context_t& stats (const ::std::string& s) { stats_ = s; mac (nm_context_stats_export, s); return *this; }
    context_t& stats_all (const bool b);
    context_t& stats_abbr (const bool b) { stats_abbr_ = b; mac (nm_context_stats_abbr, b); return *this; }
    context_t& stats_annotation (const bool b) { stats_annotation_ = b; mac (nm_context_stats_annotation, b); return *this; }
    context_t& stats_category (const bool b) { stats_category_ = b; mac (nm_context_stats_category, b); return *this; }
    context_t& stats_character_variant (const bool b) { stats_character_variant_ = b; mac (nm_context_stats_character_variant, b); return *this; }
    context_t& stats_class (const bool b) { stats_class_ = b; mac (nm_context_stats_class, b); return *this; }
    context_t& stats_content_name (const bool b) { stats_content_name_ = b; mac (nm_context_stats_content_name, b); return *this; }
    context_t& stats_counter_style (const bool b) { stats_counter_style_ = b; mac (nm_context_stats_counter_style, b); return *this; }
    context_t& stats_css_property (const bool b) { stats_css_property_ = b; mac (nm_context_stats_css_property, b); return *this; }
    context_t& stats_custom_media (const bool b) { stats_custom_media_ = b; mac (nm_context_stats_custom_media, b); return *this; }
    context_t& stats_custom_property (const bool b) { stats_custom_property_ = b; mac (nm_context_stats_custom_property, b); return *this; }
    context_t& stats_dfn (const bool b) { stats_dfn_ = b; mac (nm_context_stats_dfn, b); return *this; }
    context_t& stats_dtdd (const bool b) { stats_dtdd_ = b; mac (nm_context_stats_dtdd, b); return *this; }
    context_t& stats_element (const bool b) { stats_element_ = b; mac (nm_context_stats_element, b); return *this; }
    context_t& stats_file (const bool b) { stats_file_ = b; mac (nm_context_stats_file, b); return *this; }
    context_t& stats_font (const bool b) { stats_font_ = b; mac (nm_context_stats_font, b); return *this; }
    context_t& stats_font_family (const bool b) { stats_font_family_ = b; mac (nm_context_stats_font_family, b); return *this; }
    context_t& stats_highlight (const bool b) { stats_highlight_ = b; mac (nm_context_stats_highlight, b); return *this; }
    context_t& stats_historical_form (const bool b) { stats_historical_form_ = b; mac (nm_context_stats_historical_form, b); return *this; }
    context_t& stats_itemid (const bool b) { stats_itemid_ = b; mac (nm_context_stats_itemid, b); return *this; }
    context_t& stats_keyframe (const bool b) { stats_keyframe_ = b; mac (nm_context_stats_keyframe, b); return *this; }
    context_t& stats_layer (const bool b) { stats_layer_ = b; mac (nm_context_stats_layer, b); return *this; }
    context_t& stats_meta (const bool b) { stats_meta_ = b; mac (nm_context_stats_meta, b); return *this; }
    context_t& stats_ontology (const bool b) { stats_ontology_ = b; mac (nm_context_stats_ontology, b); return *this; }
    context_t& stats_ornament (const bool b) { stats_ornament_ = b; mac (nm_context_stats_ornament, b); return *this; }
    context_t& stats_page (const bool b) { stats_page_ = b; mac (nm_context_stats_page, b); return *this; }
    context_t& stats_page_name (const bool b) { stats_page_name_ = b; mac (nm_context_stats_page_name, b); return *this; }
    context_t& stats_palette (const bool b) { stats_palette_ = b; mac (nm_context_stats_palette, b); return *this; }
    context_t& stats_reference (const bool b) { stats_reference_ = b; mac (nm_context_stats_reference, b); return *this; }
    context_t& stats_region (const bool b) { stats_region_ = b; mac (nm_context_stats_region, b); return *this; }
    context_t& stats_scroll_anim (const bool b) { stats_scroll_anim_ = b; mac (nm_context_stats_scroll_anim, b); return *this; }
    context_t& stats_statement (const bool b) { stats_statement_ = b; mac (nm_context_stats_statement, b); return *this; }
    context_t& stats_summary (const bool b) { stats_summary_ = b; mac (nm_context_stats_summary, b); return *this; }
    context_t& stats_styleset (const bool b) { stats_styleset_ = b; mac (nm_context_stats_styleset, b); return *this; }
    context_t& stats_stylistic (const bool b) { stats_stylistic_ = b; mac (nm_context_stats_stylistic, b); return *this; }
    context_t& stats_swash (const bool b) { stats_swash_ = b; mac (nm_context_stats_swash, b); return *this; }
    context_t& stats_version (const bool b) { stats_version_ = b; mac (nm_context_stats_version, b); return *this; }
    context_t& stats_view (const bool b) { stats_view_ = b; mac (nm_context_stats_view, b); return *this; }
    context_t& svg_mode (const e_svg_processing_mode m) noexcept { svg_mode_ = m; return *this; }
    context_t& svg_version (const int mjr, const int mnr);
    context_t& svg_version (const e_svg_version v) { version_.svg_version (v); mac < int > (nm_context_svg_version, v); return *this; }
    context_t& test (const bool b) { test_ = b; mac (nm_context_test, b); return *this; }
    context_t& title (const int n)
    { if (n <= 0) title_ = 0; else title_ = n; mac < int > (nm_context_title, title_); return *this; }
    context_t& todo (const e_do e) noexcept { do_ = e; return *this; }
    context_t& unknown_class (const bool b) { unknown_class_ = b; mac (nm_context_unknown_class, b); return *this; }
    context_t& update (const bool b) noexcept { update_ = b; return *this; }
    context_t& verbose (const e_severity i) noexcept { verbose_ = i; return *this; }
    context_t& versioned (const bool b) noexcept { versioned_ = b; return *this; }
    context_t& virtuals (const vstr_t& s) { virtuals_ = s; mac (nm_context_virtuals, s); return *this; }
    context_t& x (const ::std::string& s) { x_ = s; return *this; }
    context_t& yggdrisil (const bool b) { yggdrisil_ = b; return *this; }
    context_t& mobile_profile (const bool b) { if (b) version_.set_profile (H3_NOT_MOBILE); else version_.reset_profile (H3_NOT_MOBILE); return *this; }
    context_t& print_profile (const bool b) { if (b) version_.set_profile (H3_NOT_PRINT); else version_.reset_profile (H3_NOT_PRINT); return *this; }
    context_t& tv_profile (const bool b) { if (b) version_.set_profile (H3_NOT_TV); else version_.reset_profile (H3_NOT_TV); return *this; }
    void consolidate_jsonld ()
    {   for (auto j : jsonld_ext_) extensions_.push_back (j); }
public:
    context_t ();
    int parameters (nitpick& nits, int argc, char** argv);
    bool article () const noexcept { return article_; }
    bool body () const noexcept { return body_; }
    const ::std::string build () const { return build_; }
    context_t& build (const ::std::string& s) { build_ = s; mac (nm_compile_time, s); return *this; }
    const ::std::string& cache () const noexcept { return cache_; }
    bool cased () const noexcept { return case_; }
    bool cgi () const noexcept { return cgi_; }
    bool classic () const noexcept { return classic_; }
    bool clear () const noexcept { return clear_; }
    ::boost::filesystem::path config () const { return config_; }
    e_copy copy () const noexcept { return copy_; }
    ::boost::filesystem::path corpus () const { return corpus_; }
    bool crosslinks () const noexcept { return crosslinks_; }
    int css_adjust () const { return version_.css_adjust (); }
    int css_advanced_layout () const { return version_.css_advanced_layout (); }
    int css_anchor () const { return version_.css_anchor (); }
    int css_anchor_pos () const { return version_.css_anchor_pos (); }
    int css_animation () const { return version_.css_animation (); }
    int css_background () const { return version_.css_background (); }
    int css_box_alignment () const { return version_.css_box_alignment (); }
    int css_box_model () const { return version_.css_box_model (); }
    int css_box_sizing () const { return version_.css_box_sizing (); }
    int css_cascade () const { return version_.css_cascade (); }
    int css_colour () const { return version_.css_colour (); }
    int css_compositing () const { return version_.css_compositing (); }
    int css_conditional_rule () const { return version_.css_conditional_rule (); }
    int css_contain () const { return version_.css_contain (); }
    int css_content () const { return version_.css_content (); }
    int css_counter_style () const { return version_.css_counter_style (); }
    int css_custom () const { return version_.css_custom (); }
    int css_device () const { return version_.css_device (); }
    int css_display () const { return version_.css_display (); }
    int css_ease () const { return version_.css_ease (); }
    int css_exclude () const { return version_.css_exclude (); }
    const vstr_t css_extension () const { return css_ext_; }
    int css_fbl () const { return version_.css_fbl (); }
    int css_filter () const { return version_.css_filter (); }
    int css_fill () const { return version_.css_fill (); }
    int css_float () const { return version_.css_float (); }
    int css_font () const { return version_.css_font (); }
    int css_fragmentation () const { return version_.css_fragmentation (); }
    int css_grid () const { return version_.css_grid (); }
    int css_highlight () const { return version_.css_highlight (); }
    int css_hyperlink () const { return version_.css_hyperlink (); }
    int css_line_grid () const { return version_.css_line_grid (); }
    int css_list () const { return version_.css_list (); }
    int css_logic () const { return version_.css_logic (); }
    int css_image () const { return version_.css_image (); }
    int css_inline () const { return version_.css_inline (); }
    int css_marquee () const { return version_.css_marquee (); }
    int css_masking () const { return version_.css_masking (); }
    int css_media () const { return version_.css_media (); }
    int css_motion () const { return version_.css_motion (); }
    int css_multi_column () const { return version_.css_multi_column (); }
    int css_namespace () const { return version_.css_namespace (); }
    int css_nes () const { return version_.css_nes (); }
    int css_nesting () const { return version_.css_nesting (); }
    int css_overflow () const { return version_.css_overflow (); }
    int css_overscroll () const { return version_.css_overscroll (); }
    int css_page () const { return version_.css_page (); }
    int css_position () const { return version_.css_position (); }
    int css_present () const { return version_.css_present (); }
    int css_pseudo () const { return version_.css_pseudo (); }
    int css_region () const { return version_.css_region (); }
    int css_rhythm () const { return version_.css_rhythm (); }
    int css_round () const { return version_.css_round (); }
    int css_ruby () const { return version_.css_ruby (); }
    int css_scope () const { return version_.css_scope (); }
    int css_scrollbar () const { return version_.css_scrollbar (); }
    int css_sda () const { return version_.css_sda (); }
    int css_selector () const { return version_.css_selector (); }
    int css_shadow () const { return version_.css_shadow (); }
    int css_shape () const { return version_.css_shape (); }
    int css_snap () const { return version_.css_snap (); }
    int css_snap_points () const { return version_.css_snap_points (); }
    int css_spatial () const { return version_.css_spatial (); }
    int css_speech () const { return version_.css_speech (); }
    int css_style () const { return version_.css_style (); }
    int css_syntax () const { return version_.css_syntax (); }
    int css_table () const { return version_.css_table (); }
    int css_text () const { return version_.css_text(); }
    int css_text_decoration () const { return version_.css_text_decoration (); }
    int css_transform () const { return version_.css_transform (); }
    int css_transition () const { return version_.css_transition (); }
    int css_ui () const { return version_.css_ui (); }
    int css_value () const { return version_.css_value (); }
    e_css_version css_version () const noexcept { return version_.css_version (); }
    int css_view () const { return version_.css_view (); }
    int css_writing_mode () const { return version_.css_writing_mode (); }
    int css_will_change () const { return version_.css_will_change (); }
    const vstr_t custom_elements () const { return custom_elements_; }
    bool dodedu () const noexcept { return (copy_ >= c_deduplicate); }
    const ::std::string domsg () const { return domsg_; }
    const ::std::string environment (const e_environment e) const { return environment_.at (e); }
    bool example () const noexcept { return example_; }
    bool excluded (nitpick& nits, const ::boost::filesystem::path& p) const;
    bool export_defined () const noexcept { return ! export_root_.empty (); }
    const ::std::string export_root () const { return export_root_; }
    const vstr_t exports () const { return exports_; }
    const vstr_t extensions () const { return extensions_; }
    bool external () const noexcept { return external_; }
    bool ext_css () const noexcept { return ext_css_; }
    bool extra () const noexcept { return extra_; }
    bool force_version () const noexcept { return force_version_; }
    bool forwarded () const noexcept{ return forwarded_; }
    int fred () const noexcept{ return fred_; }
    const ::std::string& general_info () const { return general_info_; }
    context_t& general_info (const ::std::string& s) { general_info_ = s; mac (nm_general_info, s); return *this; }
    bool has_math () const noexcept { return version_.has_math (); }
    bool has_rdfa () const noexcept { return rdfa () || (version_.is_svg_12 ()) || (version_ == xhtml_2); }
    bool has_svg () const noexcept { return version_.has_svg (); }
    html_version html_ver () const noexcept { return version_; }
    html_version& html_ver () noexcept { return version_; }
    html_version html_ver (const int major, const int minor) noexcept;
    bool icu () const noexcept { return icu_; }
    bool ie () const noexcept { return ie_; }
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
    bool main () const noexcept { return main_; }
    e_math_version math_version () const noexcept { return version_.math_version (); }
    unsigned long max_file_size () const noexcept { return GSL_NARROW_CAST < unsigned long > (max_file_size_); }
    bool md_export () const noexcept { return md_export_; }
    bool meta () const noexcept { return meta_; }
    bool mf_export () const noexcept { return mf_export_; }
    bool mf_verify () const noexcept { return mf_verify_; }
    bool mf_version1 () const noexcept { return (mf_version_ & 1) != 0; }
    bool mf_version2 () const noexcept { return (mf_version_ & 2) != 0; }
    bool microdata () const noexcept { return microdata_; }
    bool microformats () const noexcept { return mf_verify_ || mf_export_; }
    const ::std::string& msg () const { return msg_; }
    bool nids () const noexcept { return nids_; }
    const ::std::string& nit_format () const
    {   if (nit_override_.empty () && ! test ()) return nit_format_;
        return nit_override_; }
    bool nits () const noexcept { return nits_; }
    bool nits_nits_nits () const noexcept { return nits_nits_nits_; }
    const vstr_t no_ex_check () const { return no_ex_check_; }
    bool not_root () const noexcept { return not_root_; }
    bool once () const noexcept { return once_; }
    bool ontology () const noexcept { return ontology_; }
    const ::std::string& path () const { return path_; }
    const ::std::string persisted () const { return persisted_; }
    bool presume_tags () const noexcept { return presume_tags_; }
    bool pretended (const ::std::string& s) const;
    bool progress () const noexcept { return progress_; }
    e_quote_style quote_style () const noexcept { return quote_style_; }
    bool rdfa () const noexcept;
    e_rdf_version rdf_version () const noexcept { return version_.rdf_version (); }
    bool rel () const noexcept { return rel_; }
    const vstr_t report () const { return report_; }
    e_severity report_error () const noexcept { return report_error_; }
    bool revoke () const noexcept { return revoke_; }
    bool rfc_1867 () const noexcept { return rfc_1867_; }
    bool rfc_1942 () const noexcept { return rfc_1942_; }
    bool rfc_1980 () const noexcept { return rfc_1980_; }
    bool rfc_2070 () const noexcept { return rfc_2070_; }
    bool rpt_opens () const noexcept { return rpt_opens_; }
    const ::std::string& root () const { return root_; }
    const ::boost::filesystem::path& rootp () const { return proot_; }
    bool safari () const noexcept { return safari_; }
    ontology_version ontology_ver (const e_ontology es = s_schema) const
    {   return get_default_ontology_version (es); }
    const ::std::string& secret () const { return secret_; }
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
    bool sloven () const noexcept { return sloven_; }
    bool spell () const noexcept { return spell_; }
    context_t& spell (const bool b) { spell_ = b; mac (nm_context_spell, b); return *this; }
    bool spell_deduced () const noexcept { return spell_deduced_; }
    const vstr_t spellings () const { return spellings_; }
    const ::boost::filesystem::path& spell_path () const { return spell_path_; }
    const ::std::string& snippet () const { return snippet_; }
    bool spec () const noexcept { return spec_; }
    bool ssi () const noexcept { return ssi_; }
    const ::std::string& started () const { return started_; }
    context_t& started (const ::std::string& s) { started_ = s; mac (nm_time_start, s); return *this; }
    const ::std::string& stats () const { return stats_; }
    bool stats_summary () const noexcept { return stats_summary_; }
    bool stats_page () const noexcept { return stats_page_; }
    bool stats_abbr () const noexcept { return stats_abbr_; }
    bool stats_annotation () const noexcept { return stats_annotation_; }
    bool stats_category () const noexcept { return stats_category_; }
    bool stats_character_variant () const noexcept { return stats_character_variant_; }
    bool stats_class () const noexcept { return stats_class_; }
    bool stats_content_name () const noexcept { return stats_content_name_; }
    bool stats_counter_style () const noexcept { return stats_counter_style_; }
    bool stats_css_property () const noexcept { return stats_css_property_; }
    bool stats_custom_media () const noexcept { return stats_custom_media_; }
    bool stats_custom_property () const noexcept { return stats_custom_property_; }
    bool stats_dfn () const noexcept { return stats_dfn_; }
    bool stats_dtdd () const noexcept { return stats_dtdd_; }
    bool stats_element () const noexcept { return stats_element_; }
    bool stats_file () const noexcept { return stats_file_; }
    bool stats_font () const noexcept { return stats_font_; }
    bool stats_font_family () const noexcept { return stats_font_family_; }
    bool stats_gst (const e_gsstr gst);
    bool stats_highlight () const noexcept { return stats_highlight_; }
    bool stats_historical_form () const noexcept { return stats_historical_form_; }
    bool stats_itemid () const noexcept { return stats_itemid_; }
    bool stats_keyframe () const noexcept { return stats_keyframe_; }
    bool stats_layer () const noexcept { return stats_layer_; }
    bool stats_meta () const noexcept { return stats_meta_; }
    bool stats_ontology () const noexcept { return stats_ontology_; }
    bool stats_ornament () const noexcept { return stats_ornament_; }
    bool stats_page_name () const noexcept { return stats_page_name_; }
    bool stats_palette () const noexcept { return stats_palette_; }
    bool stats_reference () const noexcept { return stats_reference_; }
    bool stats_region () const noexcept { return stats_region_; }
    bool stats_scroll_anim () const noexcept { return stats_scroll_anim_; }
    bool stats_statement () const noexcept { return stats_statement_; }
    bool stats_styleset () const noexcept { return stats_styleset_; }
    bool stats_stylistic () const noexcept { return stats_stylistic_; }
    bool stats_swash () const noexcept { return stats_swash_; }
    bool stats_version () const noexcept { return stats_version_; }
    bool stats_view () const noexcept { return stats_view_; }
    e_svg_processing_mode svg_mode () const noexcept { return svg_mode_; }
    e_svg_version svg_version () const noexcept { return version_.svg_version (); }
    bool test () const noexcept { return test_ && nit_override_.empty (); }
    int title () const noexcept { return title_; }
    e_do todo () const noexcept { return do_; }
    bool unknown_class () const noexcept { return unknown_class_; }
    e_severity verbose () const noexcept { return verbose_; }
    const vstr_t virtuals () const { return virtuals_; }
    bool update () const noexcept { return update_; }
    bool versioned () const noexcept { return versioned_; }
    const ::std::string& x () const { return x_; }
    bool yggdrisil () const { return yggdrisil_; }
    bool tell (const e_severity n) const noexcept
    {   if (n == es_undefined) return false;
        return n <= verbose_; }
    ::boost::program_options::options_description& validation () noexcept { return validation_; }
    const ::boost::program_options::options_description& validation () const noexcept { return validation_; }
    bool profile_checks () const { return version_.profile_checks (); }
    bool mobile_profile () const { return version_.mobile_profile (); }
    bool print_profile () const { return version_.print_profile (); }
    bool tv_profile () const { return version_.tv_profile (); }
    ::std::string make_absolute_url (const ::std::string& link, bool can_use_index = true) const; };

extern context_t context;
