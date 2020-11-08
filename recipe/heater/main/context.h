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

#pragma once
#include "webmention/irt.h"
#include "webmention/hook.h"
#include "css/css_cache.h"
#include "stats/stats.h"
#include "parser/html_version.h"
#include "schema/schema_version.h"

const e_verbose default_output = e_warning;

#define VALID_RESULT 0
#define STOP_OK 1
#define NOTHING_TO_DO 2
#define ERROR_STATE 3

#define DEFAULT_MAX_FILE_SIZE 4

class hook;
class replies;

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i);
::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i, const ::std::string& msg, const e_verbose level = e_comment);

class context_t
{   bool            checking_urls_ = false, clear_ = false, codes_ = false, crosslinks_ = false, external_ = false, forwarded_ = false, load_css_ = false, links_ = false,
                    md_export_ = false, mf_export_ = false, mf_verify_ = false,
                    microdata_ = false, nids_ = false, nits_ = false, nochange_ = false, notify_ = false, once_ = false, presume_tags_ = false, process_webmentions_ = false, rdf_ = false,
                    repeated_ = false, reset_ = false, revoke_ = false, rfc_1867_ = true, rfc_1942_ = true, rfc_1980_ = true, rfc_2070_ = true, schema_ = false, slob_ = false, ssi_ = false,
                    stats_page_ = false, stats_summary_ = false, test_ = false, unknown_class_ = false, valid_ = false;
    int             code_ = 0;
    unsigned char            html_major_ = 5, html_minor_ = 4, mf_version_ = 3, sch_major_ = 0, sch_minor_ = 0;
    e_svg_version   svg_version_ = sv_none;
    e_math_version  math_version_ = math_none;
    long            max_file_size_ = DEFAULT_MAX_FILE_SIZE * 1024 * 1024;
    e_verbose       verbose_ = default_output;
    ::std::string   base_, filename_, stub_, hook_, incoming_, index_, macro_end_, macro_start_, output_, path_, persisted_, root_, secret_, server_,
                    test_header_, user_, webmention_, write_path_;
    e_wm_status     wm_status_ = wm_undefined;
    vstr_t          custom_elements_, extensions_, mentions_, site_, templates_, virtuals_;
    replies         replies_;
    hooks           hooks_;
    css_cache       css_;
    ::std::unique_ptr < ::std::ofstream > fos_;
    stats_t         data_;
public:
    context_t () = default;
    int parameters (int argc, char** argv);
    const ::std::string base () const { return base_; }
    bool checking_urls () const { return checking_urls_; }
    bool clear () const { return clear_; }
    bool crosslinks () const { return crosslinks_; }
    int code () const { return code_; }
    bool codes () const { return codes_; }
    const vstr_t custom_elements () const { return custom_elements_; }
    const vstr_t extensions () const { return extensions_; }
    bool external () const { return external_; }
    const ::std::string filename () const { return filename_; }
    bool forwarded () const { return forwarded_; }
    unsigned char html_major () const { return html_major_; }
    unsigned char html_minor () const { return html_minor_; }
    html_version html_ver () const;
    const ::std::string incoming () const { return incoming_; }
    const ::std::string index () const { return index_; }
    bool invalid () const { return ! valid_; }
    bool load_css () const { return ! load_css_; }
    bool links () const { return links_; }
    const ::std::string macro_end () const { return macro_end_; }
    const ::std::string macro_start () const { return macro_start_; }
    unsigned long max_file_size () const { return static_cast < unsigned long > (max_file_size_); }
    const vstr_t mentions () const { return mentions_; }
    bool md_export () const { return md_export_; }
    bool mf_export () const { return mf_export_; }
    bool mf_verify () const { return mf_verify_; }
    bool mf_version1 () const { return (mf_version_ & 1) != 0; }
    bool mf_version2 () const { return (mf_version_ & 2) != 0; }
    bool microdata () const { return microdata_; }
    bool microformats () const { return mf_verify_ || mf_export_; }
    bool nids () const { return nids_; }
    bool nits () const { return nits_; }
    bool nochange () const { return nochange_; }
    bool notify () const { return notify_; }
    bool once () const { return once_; }
    ::std::string output () const { return output_; }
    bool presume_tags () const { return presume_tags_; }
    ::std::string path () const { return path_; }
    const ::std::string persisted () const { return persisted_; }
    bool process_webmentions () const { return process_webmentions_; }
    bool rdf () const { return rdf_; }
    bool repeated () const { return repeated_; }
    bool reset () const { return reset_; }
    bool revoke () const { return revoke_; }
    bool rfc_1867 () const { return rfc_1867_; }
    bool rfc_1942 () const { return rfc_1942_; }
    bool rfc_1980 () const { return rfc_1980_; }
    bool rfc_2070 () const { return rfc_2070_; }
    const ::std::string root () const { return root_; }
    bool schema () const { return schema_; }
    unsigned char schema_major () const
    {   if (! is_valid_schema_version (sch_major_, sch_minor_)) return 0;
        return sch_major_; }
    unsigned char schema_minor () const
    {   if (! is_valid_schema_version (sch_major_, sch_minor_)) return 0;
        return sch_minor_; }
    schema_version schema_ver () const
    {   return schema_version (schema_major (), schema_minor ()); }
    const ::std::string secret () const { return secret_; }
    const ::std::string server () const { return server_; }
    const vstr_t site () const { return site_; }
    bool slob () const { return slob_; }
    bool ssi () const { return ssi_; }
    bool stats_summary () const { return stats_summary_; }
    bool stats_page () const { return stats_page_; }
    const ::std::string stub () const { return stub_; }
    bool has_svg () const { return ((html_major_ > 3) || (svg_version_ != sv_none)); }
    e_svg_version svg_version () const { return svg_version_; }
    bool has_math () const { return ((html_major_ > 3) || (math_version_ != math_none)); }
    e_math_version math_version () const { return math_version_; }
    const vstr_t templates () const { return templates_; }
    bool test () const { return test_; }
    const ::std::string test_header () const { return test_header_; }
    bool unknown_class () const { return ! unknown_class_; }
    const ::std::string user () const { return user_; }
    e_verbose verbose () const { return verbose_; }
    const vstr_t virtuals () const { return virtuals_; }
    const ::std::string webmention () const { return webmention_; }
    const ::std::string write_path () const { return write_path_; }
    context_t& base (const ::std::string& s) { base_ = s; return *this; }
    context_t& checking_urls (const bool b) { checking_urls_ = b; return *this; }
    context_t& clear (const bool b) { clear_ = b; return *this; }
    context_t& crosslinks (const bool b) { crosslinks_ = b; return *this; }
    context_t& code (const int i) { code_ = i; return *this; }
    context_t& codes (const bool b) { codes_ = b; return *this; }
    context_t& custom_elements (const vstr_t& s) { custom_elements_ = s; return *this; }
    context_t& extensions (const vstr_t& s) { extensions_ = s; return *this; }
    context_t& external (const bool b)
    {   external_ = b;
        if (b) links (b);
        else { forwarded (false); once (false); revoke (false); microdata (false); }
        return *this; }
    context_t& filename (const ::std::string& s) { filename_ = s; return *this; }
    context_t& forwarded (const bool b)
    {   forwarded_ = b;
        if (b) external (b);
        return *this; }
    context_t& hook (const ::std::string& s) { hook_ = s; return *this; }
    context_t& html_major (const int i);
    context_t& html_minor (const int i);
    context_t& incoming (const ::std::string& s) { incoming_ = s; return *this; }
    context_t& index (const ::std::string& s) { index_ = s; return *this; }
    context_t& load_css (const bool b) { load_css_ = ! b; return *this; }
    context_t& links (const bool b)
    {   links_ = b;
        if (! b) { external (false); }
        return *this; }
    context_t& macro_end (const ::std::string& s) { macro_end_ = s; return *this; }
    context_t& macro_start (const ::std::string& s) { macro_start_ = s; return *this; }
    context_t& max_file_size (const long l) { max_file_size_ = l; return *this; }
    context_t& mentions (const vstr_t& s) { mentions_ = s; return *this; }
    context_t& md_export (const bool b) { md_export_ = b; return *this; }
    context_t& mf_export (const bool b) { mf_export_ = b; return *this; }
    context_t& mf_verify (const bool b) { mf_verify_ = b; return *this; }
    context_t& mf_version (const unsigned char n) { mf_version_ = n; return *this; }
    context_t& microdata (const bool b)
    {   microdata_ = b;
        if (b) external (b);
        return *this; }
    context_t& nids (const bool b) { nids_ = b; return *this; }
    context_t& nits (const bool b) { nits_ = b; return *this; }
    context_t& nochange (const bool b) { nochange_ = b; return *this; }
    context_t& notify (const bool b) { notify_ = b; return *this; }
    context_t& once (const bool b)
    {   once_ = b;
        if (b) external (b);
        return *this; }
    context_t& output (const ::std::string& s)
    {   output_ = s;
        fos_.reset (new ::std::ofstream (s));
        return *this; }
    context_t& path (const ::std::string& s) { path_ = s; return *this; }
    context_t& persisted (const ::std::string& s) { persisted_ = s; return *this; }
    context_t& presume_tags (const bool b) { presume_tags_ = b; return *this; }
    context_t& process_webmentions (const bool b) { process_webmentions_ = b; return *this; }
    context_t& rdf (const bool b) { rdf_ = b; return *this; }
    context_t& repeated (const bool b) { repeated_ = b; return *this; }
    context_t& reset (const bool b) { reset_ = b; return *this; }
    context_t& revoke (const bool b)
    {   revoke_ = b;
        if (b) external (b);
        return *this; }
    context_t& rfc_1867 (const bool b) { rfc_1867_ = b; return *this; }
    context_t& rfc_1942 (const bool b) { rfc_1942_ = b; return *this; }
    context_t& rfc_1980 (const bool b) { rfc_1980_ = b; return *this; }
    context_t& rfc_2070 (const bool b) { rfc_2070_ = b; return *this; }
    context_t& root (const ::std::string& s) { root_ = s; return *this; }
    context_t& schema (const bool b)
    {   schema_ = b;
        if (sch_major_ == 0)
        {   sch_major_ = schema_major_max;
            sch_minor_ = 0; }
        return *this; }
    context_t& schema_major (const unsigned char n) { sch_major_ = (n > schema_major_max) ? 0 : n; return *this; }
    context_t& schema_minor (const unsigned char n) { sch_minor_ = (n > 9) ? 0 : n; return *this; }
    context_t& secret (const ::std::string& s) { secret_ = s; return *this; }
    context_t& server (const ::std::string& s) { server_ = s; return *this; }
    context_t& site (const vstr_t& s) { site_ = s; return *this; }
    context_t& slob (const bool b) { slob_ = b; return *this; }
    context_t& ssi (const bool b) { ssi_ = b; return *this; }
    context_t& stats_summary (const bool b) { stats_summary_ = b; return *this; }
    context_t& stats_page (const bool b) { stats_page_ = b; return *this; }
    context_t& stub (const ::std::string& s) { stub_ = s; return *this; }
    context_t& svg_version (const int mjr, const int mnr);
    context_t& svg_version (const e_svg_version v) { svg_version_ = v; return *this; }
    context_t& math_version (const int v)
    {   if ((v >= 1) && (v <= 4)) math_version_ = static_cast < e_math_version > (v);
        else math_version_ = math_none;
        return *this; }
    context_t& math_version (const e_math_version v) { math_version_ = v; return *this; }
    context_t& templates (const vstr_t& s) { templates_ = s; return *this; }
    context_t& test (const bool b) { test_ = b; return *this; }
    context_t& test_header (const ::std::string& s) { test_header_ = s; return *this; }
    context_t& unknown_class (const bool b) { unknown_class_ = ! b; return *this; }
    context_t& user (const ::std::string& s) { user_ = s; return *this; }
    context_t& verbose (const e_verbose i) { verbose_ = i; return *this; }
    context_t& virtuals (const vstr_t& s) { virtuals_ = s; return *this; }
    context_t& webmention (const ::std::string& w, const e_wm_status status);
    context_t& write_path (const ::std::string& s) { write_path_ = s; return *this; }
    css_cache& css () { return css_; }
    const css_cache& css () const { return css_; }
    void reset_webmention ()
    {   webmention_.clear ();
        wm_status_ = wm_undefined; }
    void note_reply (const ::std::string& file, const ::std::string& id, const ::std::string& target, const ::std::string& content)
    {   if (notify ()) replies_.append (file, id, target, content); }
    replies& get_replies () { return replies_; }
    void process_outgoing_webmention (nitpick& nits, const html_version& v);
    void process_incoming_webmention (nitpick& nits, const html_version& v);
    bool tell (const e_verbose n) const { return n <= verbose_; }
    ::std::ostream& out () { if (fos_) return *fos_; return ::std::cout; }
    ::std::ostream& err () { if (fos_) return *fos_; return ::std::cerr; }
    void mark (const e_element e)
    {   data_.mark (e); }
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
    void mark (const e_schema s)
    {   data_.mark (s); }
    void mark (const e_schema s, const e_schema_property p)
    {   data_.mark (s, p); }
    void mark_file (const unsigned size)
    {   data_.mark_file (size); }
    void report_stats ()
    {   out () << data_.report (true); }
    uint64_t file_count () const
    {   return data_.file_count (); }
    ::std::string make_absolute_url (const ::std::string& link, bool can_use_index = true) const; };

extern context_t context;
