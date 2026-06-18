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
#include "main/context.h"
#include "main/options.h"
#include "stats/stats.h"
#include "element/elem.h"
#include "utility/common.h"
#include "utility/quote.h"
#include "utility/filesystem.h"
#include "utility/fileio.h"
#include "parser/text.h"
#include "coop/fred.h"
#include "url/fetch.h"
#include "parser/ads.h"
#include "parser/jsonic.h"
#include "parser/robotic.h"
#include "parser/security.h"

::std::string context_t::update_info_;

context_t context;
ustr_t context_t::validation_;
::boost::filesystem::path context_t::cwd_;

#ifdef LEAK_SEEK
_CrtMemState context_t::ls_old_;
#endif // LEAK_SEEK

ssc_set < ::std::string > excludable_filenames;

context_t::context_t (nitpick& nits, const ::boost::filesystem::path& fn)
{   init ();
    options o (*this, nits, fn);
    if (nits.worst () <= es_error) valid_ = false;
    else
    {
#ifdef DARWIN
        if (context.excl_def_excl ()) excludable_filenames.insert (".DS_Store");
#endif // DARWIN
        o.contextualise (*this, nits);
        check_consistency (nits);
        if (! test () && tell (es_debug))
        {   ::std::string s (o.report (gr_config));
            mac (nm_context_output, s); }
        valid_ = ! root ().empty (); } }

void context_t::swap (context_t& c)
{   context_t t (*this);
    try
    {   *this = c;
        c = t; } 
    catch (...)
    {   *this = t; } }

void context_t::reset ()
{   context_t c;
    *this = c; } 

void context_t::reset (const context_t& c)
{   context_t t (c);
    swap (t); }

void context_t::init ()
{   os_ = os_ptr (new outstream ());
    VERIFY_NOT_NULL (os_.get (), __FILE__, __LINE__);
    environment_.resize (env_max);
    if (cwd_.empty ()) cwd_ = get_working_directory ();
    def_conf_path_ = cwd_ / DEF_DATAPATH;
    path_ = def_conf_path_.string ();
    def_conf_file_ = def_conf_path_ / DEF_CONF_FILE; }

void context_t::done ()
try
{   if (os_) 
    {   nitpick nits ("signature status");
        os_ -> done (nits); 
        if (! nits.empty ())
            if (nits.worst () <= report_error_)
                ::std::cerr << nits.kwik ();
            else if (nits.worst () <= verbose_)
                ::std::cout << nits.kwik (); } }
catch (const ::std::system_error& e)
{   ::std::cerr << "system exception signing/verifying: " << e.what () << "\n"; }
catch (const ::std::exception& e)
{   ::std::cerr << "exception signing/verifying: " << e.what () << "\n"; }
catch (...)
{   ::std::cerr << "unknown exception signing/verifying.\n"; }

void context_t::mac (const e_nit_macro ns, const sstr_t& s)
{   ::std::string ss;
    for (auto sss: s)
    {   if (! ss.empty ()) ss += ",";
        ss += quote (sss); }
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> set (ns, ss); }

void context_t::mac (const e_nit_macro ns, const vstr_t& s)
{   ::std::string ss;
    for (auto sss: s)
    {   if (! ss.empty ()) ss += ",";
        ss += quote (sss); }
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> set (ns, ss); }

void context_t::mac (const e_nit_macro ns, const vbp_t& s)
{   ::std::string ss;
    for (auto sss: s)
    {   if (! ss.empty ()) ss += ",";
        ss += quote (sss.string ()); }
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> set (ns, ss); }

context_t& context_t::copy (const int c)
{   if ((c > c_none) && (c <= c_rpt)) copy_ = static_cast < e_copy > (c);
    else copy_ = c_none;
    mac < int > (nm_context_copy, c);
    return *this; }

context_t& context_t::external (const bool b)
{   external_ = b;
    if (b) links (b);
    else { forwarded (false); once (false); revoke (false); microdata (false); }
    return *this; }

context_t& context_t::forwarded (const bool b)
{   forwarded_ = b;
    if (b) external (b);
    mac (nm_context_forward, b);
    return *this; }

context_t& context_t::html_ver (const html_version& v)
{   versioned (true);
    version_ = v;
    mac (nm_context_version, version_.name ());
    return *this; }

context_t& context_t::links (const bool b)
{   links_ = b;
    mac (nm_context_links, b);
    if (! b) { external (false); }
    return *this; }

context_t& context_t::mf_version (const unsigned char n)
{   mf_version_ = n;
    mac < int > (nm_context_mf_version, n);
    if (n <= 1) set_default_ontology_version (s_microformats, 1, 0);
    else set_default_ontology_version (s_microformats, 2, 0);
    return *this; }

context_t& context_t::microdata (const bool b)
{   microdata_ = b;
    mac (nm_context_microdata, b);
    if (b) links (b);
    return *this; }

context_t& context_t::once (const bool b)
{   once_ = b;
    mac (nm_context_once, b);
    if (b) external (b);
    return *this; }

context_t& context_t::ontology (const bool b)
{   ontology_ = b;
    mac (nm_context_schema, b);
    return *this; }

context_t& context_t::ont_ver (const e_ontology o, const ::std::string& s)
{   PRESUME (o < s_error, __FILE__, __LINE__);
    if (vont_.size () == 0) vont_.resize (s_error);
    vont_.at (o) = s;
    return *this; }

context_t& context_t::output_format (const ::std::string& nf)
{   output_format_ = nf;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> set (nm_output_format, nf);
    return *this; }

context_t& context_t::path (const ::std::string& s)
{   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    path_ = s;
    macro -> set (nm_general_path, s);
    return *this; }

int context_t::parameters (nitpick& nits, const vstr_t& vs)
{   options o (*this, nits, vs);
    switch (todo ())
    {   case do_booboo :
            return ERROR_STATE;
        case do_examine :
        case do_cgi :
            break;
        default :
            return STOP_OK; }
#ifdef DARWIN
    if (context.excl_def_excl ()) excludable_filenames.insert (".DS_Store");
#endif // DARWIN
    o.contextualise (*this, nits);
    check_consistency (nits);
    if (! test () && tell (es_debug))
    {   ::std::string s (o.report (gr_config));
        mac (nm_context_output, s); }
    valid_ = cgi () || (! root ().empty ());
    return valid_ ? VALID_RESULT : ERROR_STATE; }

context_t& context_t::title (const ::std::size_t n)
{   if (n <= 0) title_ = 0; 
    else title_ = n; 
    mac < ::std::size_t > (nm_context_title, title_); 
    return *this; }

::std::string context_t::make_absolute_url (const ::std::string& link, bool can_use_index ) const
{    ::std::string res, srv;
    if (site_.size () > 0)
    {   srv = HTTPS;
        srv += *site_.cbegin ();
        srv += SLASH; }
    if (link.empty ()) res = srv;
    else
    {   if (link.find (COLON) != link.npos) res = link;
        else
        {   res = srv;
            if (link.at (0) != SLASH) res += link;
            else res += link.substr (1); } }
    const ::std::size_t last = res.length () - 1;
    if (can_use_index )
    {   const bool slashed = res.at (last) == SLASH;
        if (slashed) if (! index ().empty ()) res += index (); }
    return res; }

context_t& context_t::shadow_ignore (const vstr_t& s)
{   shadow_enable (true);
    shadow_ignore_.clear ();
    for (auto ss : s)
        if (! ss.empty ())
            if (ss.at (0) == '.') shadow_ignore_.emplace_back (ss);
            else shadow_ignore_.emplace_back (::std::string (1, '.') + ss);
    mac (nm_context_shadow_ignore, shadow_ignore_);
    return *this; }

context_t& context_t::css_version (const int mjr, const int mnr)
{   e_css_version v = css_none;
    switch (mjr)
    {   case 1 :
            if (mnr == 0) v = css_1;
            break;
        case 2 :
            switch (mnr)
            {   case 0 : v = css_2_0; break;
                case 1 : v = css_2_1; break;
                case 2 : v = css_2_2; break;
                default : break; }
            break;
        case 3 :
            v = css_3;
            break;
        case 4 :
            v = css_4;
            break;
        case 5 :
            v = css_5;
            break;
        case 6 :
            v = css_6;
            break;
        default :
            break; }
    css_version (v);
    return *this; }

context_t& context_t::svg_version (const int mjr, const int mnr)
{   e_svg_version v = sv_none;
    switch (mjr)
    {   case 2 :
            switch (mnr)
            {   case 0 : v = sv_2_0; break;
                case 1 : v = sv_2_1; break;
                default : break; }
            break;
        case 1 :
            switch (mnr)
            {   case 0 : v = sv_1_0; break;
                case 1 : v = sv_1_1; break;
                case 2 : v = sv_1_2_tiny; break;
                case 3 : v = sv_1_2_full; break;
                default : break; }
            break;
        default : break; }
    svg_version (v);
    return *this; }

context_t& context_t::math_version (const int v)
{   switch (v)
    {   case 1 : version_.math_version (math_1); break;
        case 2 : version_.math_version (math_2); break;
        case 3 : version_.math_version (math_3); break;
        case 4 : version_.math_version (math_4); break;
        default : version_.math_version (math_none); }
    mac < int > (nm_context_math, version_.math_version ());
    return *this; }

context_t& context_t::ignore (nitpick& nits, const vstr_t& s)
{   e_element e = elem_undefined;
    for (auto ss : s)
        if (elem :: find (html_0, ss, e)) { elem :: ignore (e); ignore_.push_back (ss); }
        else nits.pick (nit_unknown_element, es_error, ec_init, quote (ss), " is not an element");
    mac (nm_context_ignore, s);
    return *this; }

html_version context_t::html_ver (const int major, const int minor) noexcept
{   versioned (true);
    switch (major)
    {   case 0 :
            version_ = html_tags;
            break;
        case 1 :
            if (minor == 1) version_ = html_plus; else version_ = html_1;
            break;
        case 2 :
            version_ = html_2;
            break;
        case 3 :
            if (minor == 0) version_ = html_3_0; else version_ = html_3_2;
            break;
        case 4 :
            switch (minor)
            {   case 0 : version_ = html_4_0; break;
                case 2 : version_ = xhtml_1_0; break;
                case 3 : version_ = xhtml_1_1; break;
                case 4 : version_ = xhtml_2; break;
                default : version_ = html_4_1; break; }
            break;
        case 5 :
            switch (minor)
            {   case 0 : version_ = html_5_0; break;
                case 1 : version_ = html_5_1; break;
                case 2 : version_ = html_5_2; break;
                case 3 : version_ = html_5_3; break;
                case 4 : version_ = html_jul20; break;
                default : version_ = html_current; break; }
            break;
        default :
            version_ = html_default;
            break; }
    return version_; }

context_t& context_t::environment (const e_environment e, const ::std::string& s)
{   environment_.at (e) = s.substr (0, ARGLEN_MAX);
    return *this; }

bool context_t::rdfa () const noexcept
{   if (rdfa_) return true;
    if (version_.is_svg_12 ()) return true;
    return (version_ == xhtml_2); }

context_t& context_t::exclude (nitpick& , const ::std::string& s)
{   exclude_.push_back (s);
    return *this; }

context_t& context_t::pretend (nitpick& , const ::std::string& s)
{   pretend_.push_back (s);
    return *this; }

context_t& context_t::silence (nitpick& , const ::std::string& s)
{   silence_.push_back (::boost::regex (s));
    return *this; }

context_t& context_t::exclude (nitpick& nits, const vstr_t& s)
{   for (auto ss : s)
#ifdef WIN32
        exclude (nits, ::boost::to_lower_copy (ss));
#else // WIN32
        exclude (nits, ss);
#endif // WIN32
    return *this; }

context_t& context_t::pretend (nitpick& nits, const vstr_t& s)
{   for (auto ss : s)
        pretend (nits, ss);
    return *this; }

context_t& context_t::silence (nitpick& nits, const vstr_t& s)
{   for (auto ss : s)
#ifdef WIN32
        silence (nits, ::boost::to_lower_copy (ss));
#else // WIN32
        silence (nits, ss);
#endif // WIN32
    return *this; }

bool context_t::silenced (const ::std::string& site_path)
{   for (auto s : silence_)
        if (::boost::regex_search (site_path, s))
            return true;
    return false; }

bool context_t::matches (const ::std::string& s, const ::std::string& w, const char sep) const
{   const ::std::string::size_type slen = s.length ();
    const ::std::string::size_type wlen = w.length ();
    if (slen == 0) return (wlen == 0);
    if (wlen == 0) return true;
    if (slen < wlen) return false;
    if (wlen == slen) return (w == s);
    const ::std::string::size_type pos = s.find (w);
    if (pos == ::std::string::npos) return false;
    if ((pos > 0) && (sep != 0) && (s.at (pos-1) != sep)) return false;
    if (pos + wlen >= slen) return true;
    return (s.at (pos+wlen) == sep); }

bool context_t::excluded (nitpick& nits, const ::boost::filesystem::path& p) const
{   if (! p.empty () && (excludable_filenames.find (p.filename ().string ()) == excludable_filenames.cend ()))
        for (auto w : exclude_)
            if (matches (p.string (), w, ::boost::filesystem::path::preferred_separator))
            {   nits.pick (nit_excluded, es_comment, ec_file, "excluding ", p.string ());
                return true; }
    return false; }

bool context_t::pretended (const ::std::string& s) const
{   for (auto w : pretend_)
        if (matches (s, w, 0))
            return true;
    return false; }

context_t& context_t::fred (const ::std::size_t i)
{   const ::std::size_t nmt = fred_t::no_more_than (); // <=> :-(
    if (i > nmt) fred_ = nmt;
    else if (i >= MIN_FRED) fred_ = i;
    else fred_ = fred_t::suggested ();
    mac (nm_context_info, fred_);
    return *this; }

context_t& context_t::root (const ::std::string& s)
{   root_ = s;
    mac (nm_context_root, s);
    proot_ = canonical_name (absolute_name (::boost::filesystem::path (s)));
    return *this; }

bool context_t::stats_gst (const e_gsstr gst)
{   switch (gst)
    {   case gst_anchor : return stats (rcb_anchor);
        case gst_annotation : return stats (rcb_annotation);
        case gst_character_variant : return stats (rcb_character_variant) ;
        case gst_content_name : return stats (rcb_content_name);
        case gst_counter_style : return stats (rcb_counter_style);
        case gst_font_family : return stats (rcb_font_family);
        case gst_function : return stats (rcb_function);
        case gst_highlight : return stats (rcb_highlight);
        case gst_historical_form : return stats (rcb_historical_form);
        case gst_keyframe : return stats (rcb_keyframe);
        case gst_layer : return stats (rcb_layer);
        case gst_ornament : return stats (rcb_ornament);
        case gst_page_name : return stats (rcb_page_name);
        case gst_palette : return stats (rcb_palette);
        case gst_param : return stats (rcb_param);
        case gst_region : return stats (rcb_region);
        case gst_scroll_anim : return stats (rcb_scroll_animation);
        case gst_styleset : return stats (rcb_styleset);
        case gst_stylistic : return stats (rcb_stylistic);
        case gst_swash : return stats (rcb_swash);
        case gst_view : return stats (rcb_view);
        default : break; }
    GRACEFUL_CRASH (__FILE__, __LINE__); }

context_t& context_t::stats_all (const bool b)
{   for (int i = 0; i < rcb_max; ++i)
        stats (static_cast < e_report > (i), b);
    return *this; }

bool context_t::stats_any () const
{   for (auto b : rpt_)
        if (b) return true;
    return false; }

context_t& context_t::stats (const e_report r, const bool b)
{   rpt_.at (r) = b;
    mac (enum_n < t_report, e_report, e_nit_macro, nm_none > :: category (r), b);
    return *this; }

context_t& context_t::css_module (const e_css_module m, const int n)
{   mac (enum_n < t_css_module, e_css_module, e_nit_macro, nm_none > :: category (m), n);
    version_.css_module (m, n);
    return *this; }

void context_t::apply_vcs (nitpick& nits)
{   if (vcs ())
    {   exclude (nits, ".bazaar");
        exclude (nits, ".bk");
        exclude (nits, "CVS");
        exclude (nits, ".cvsignore");
        exclude (nits, "_darcs");
        exclude (nits, ".fslckout");
        exclude (nits, ".git");
        exclude (nits, ".gitattributes");
        exclude (nits, ".gitignore");
        exclude (nits, ".gitmodules");
        exclude (nits, ".monotone");
        exclude (nits, ".pijul");
        exclude (nits, "RCS");
        exclude (nits, "SCCS");
        exclude (nits, ".svn"); } }

bool context_t::write (nitpick& nits, const ::boost::filesystem::path& fn) const
{   options opt (*this);
    return opt.write (nits, fn); }

::std::string context_t::summarise () const
{   ::std::string res (version_.nice_name ());
    if (css_version () != css_none)
    {   res += "; CSS "; res += version_.long_css_version_name (); }
    if (math_version () != math_none)
    {   res += "; MathML "; res += version_.math_version_name (); }
    if (rdfa ()) res += "; RDFa";
    if (svg_version () != sv_none)
    {   res += "; SVG "; res += version_.svg_version_name (); }
    switch (virtuals ().size ())
    {   case 0 : break;
        case 1 : res += "; virtual directory"; break;
        default : res += "; virtual directories"; }
    if (load_vtt ()) res += "; WebVTT";
    if (ssi ()) res += "; resolve Server Side Includes";
    if (classic () || unknown_class ())
    {   res += "; verify";
        if (unknown_class ()) res += " all";
        else res += " declared";
        res += " CLASS values"; }
    if (ontology ())
    {   res += "; verify";
        if (md_export ()) res += " and export";
        res += " ontologies"; }
    if (! corpus ().empty ())
        res += "; export corpus";
    if (mf_verify () && (mf_version () > 0))
    {   res += "; verify microformats ";
        switch (mf_version ())
        {   case 1 :
                res += "v1";
                break;
            case 2 :
                res += "v2";
                break;
            case 3 :
                res += "v1 & v2";
                break;
            default :
                GRACEFUL_CRASH (__FILE__, __LINE__); } }
    if (shadow_enable ()) res += "; shadowing";
#ifndef NOSPELL
    if (spell ()) res += "; check spelling";
#endif // NOSPELL
    if (stats_any ()) res += "; produce statistics";
    return res; }

::std::string context_t::report (const e_gui_report gr, const bool wibble) const
{   if (gr == gr_summary) return summarise ();
    options opt (*this);
    return opt.report (gr, false, wibble); }

context_t& context_t::serve (const bool b)
{   serve_ = b;
    mac (nm_context_server, b);
    return *this; }

context_t& context_t::snippet (const ::std::string& s)
{   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    snippet_ = s;
    macro -> set (nm_context_root, "");
    macro -> set (nm_html_snippet, s);
    if (! context.gui ()) quote_style (qs_html);
    return *this; }

void context_t::check_ssi_naughtiness (nitpick& nits, const ::std::string& s)
{   nitpick knots;
    const ::std::string::size_type pos = s.find ("<!--#");
    if (pos != ::std::string::npos)
    {   type_master < t_ssi > ssi;
        ssi.set_value (knots, html_default, s.substr (pos+5));
        if (ssi.good ())
        {   if (s.substr (pos+5).find ("-->") == ::std::string::npos)
                nits.pick (nit_ssi_exec, es_warning, ec_ssi, "The substitute string ", quote (s), " contains an unclosed SSI element");
            switch (ssi.get ())
            {   case ssi_exec :
                    nits.pick (nit_ssi_exec, es_warning, ec_ssi, "The substitute string ", quote (s), " contains <!--#exec ...>, which is extremely naughty and characteristic of malignant hackery");
                    break;
                case ssi_comment :
                    break;
                case ssi_config :
                    nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains <!--#config ...>, which may harm web pages");
                    break;
                case ssi_echo :
                    nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains <!--#echo ...>, which may imply malignant hackery");
                    break;
                case ssi_if :
                case ssi_else :
                case ssi_elif :
                case ssi_endif :
                    nits.pick (nit_ssi_if, es_warning, ec_ssi, "The substitute string ", quote (s), " contains an SSI conditional element, which is rather naughty");
                    break;
                case ssi_include :
                    nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains <!--#include ...>, which is extremely naughty and characteristic of malignant hackery");
                    break;
                case ssi_set :
                    nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains <!--#set ...>, which is rather naughty, and may change the value of a significant variable");
                    break;
                default :            
                    nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains an SSI element, which is rather naughty");
                    break; } } }
    const ::std::string::size_type pos2 = s.find ("<");
    if (pos2 != pos)
        if (s.substr (pos2+1).find ('>') != ::std::string::npos)
            switch (elem::find (html_default, s.substr (pos2+1)))
            {   case elem_a :
                    nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains an <A ...>, which is characteristic of malignant hackery");
                    break;
                case elem_error :
                case elem_undefined :
                    break;
                case elem_fencedframe :
                    nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains a <FENCEDFRAME ...>, which is characteristic of optimistic hackery");
                    break;
                case elem_iframe :
                    nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains an <IFRAME ...>, which is characteristic of malignant hackery");
                    break;
                case elem_link :
                    nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains a <LINK ...>, which is somewhat naughty");
                    break;
                case elem_meta :
                    if (s.substr (pos2+1).find ("http-equiv") || s.substr (pos2+1).find ("HTTP-EQUIV"))
                        if (s.substr (pos2+10).find ("refresh") || s.substr (pos2+10).find ("REFRESH"))
                            nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains a <META ...> element and a REFRESH, which is characteristic of malignant hackery");
                        else
                            nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains a <META ...> element with an HTTP-EQUIV, which is very naughty");
                    else
                        nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains a <META ...>, which is rather naughty");
                    break;
                default :            
                    nits.pick (nit_ssi_naughty, es_warning, ec_ssi, "The substitute string ", quote (s), " contains HTML element/s, which is rather naughty");
                    break; } }

void context_t::populate_jsonld_ont (const vstr_t& vs)
{   jsonld_ont_ = vs;
    for (auto s : vs)
    {   const ::std::string::size_type pos = s.find (':');
        if ((pos == 0) || (pos == s.length () - 1)) continue;
        if (pos == ::std::string::npos)
            if (compare_no_case ("standard", s))
                for (int o = s_none + 1; o < s_error; ++o)
                {   if ((ontology_names.flags (static_cast < e_ontology > (o)) & ONTOLOGY_PREFIX_CONTEXT) == ONTOLOGY_PREFIX_CONTEXT)
                    {   jsonld_key_.push_back (ontology_names.get (static_cast < e_ontology > (o), ONTOLOGY_NAME));
                        jsonld_val_.push_back (ontology_names.get (static_cast < e_ontology > (o), ONTOLOGY_CURIE)); } }
            else if (compare_no_case ("all", s))
            {   for (int o = s_none + 1; o < s_error; ++o)
                {   jsonld_key_.push_back (ontology_names.get (static_cast < e_ontology > (o), ONTOLOGY_NAME));
                    jsonld_val_.push_back (ontology_names.get (static_cast < e_ontology > (o), ONTOLOGY_CURIE)); } }
            else
            {   const e_ontology id = ontology_names.find (version_, ONTOLOGY_NAME, s, ! version_.xhtml ());
                if (id != s_error)
                {   jsonld_key_.push_back (s);
                    jsonld_val_.push_back (ontology_names.get (id, ONTOLOGY_CURIE));
                } }
        else
        {   jsonld_key_.push_back (s.substr (0, pos));
            jsonld_val_.push_back (s.substr (pos + 1)); } } }

context_t& context_t::custom_elements (nitpick& nits, const vstr_t& sss)
{  for (auto s : sss)
        if (test_value < t_custom_element > (nits, html_ver (), s))
            custom_elements_.insert (s);
    mac (nm_context_custom_elements, custom_elements_); 
    return *this; }

void context_t::check_consistency (nitpick& nits)
{   if (anal_ == anal_default)
        if (html_ver () >= html_dec25) anal_ = anal_dec25;
        else if (html_ver () >= html_aug25) anal_ = anal_aug25;
        else anal_ = anal_original;
#ifdef SIGNING
    if (context.sign () || context.verify ())
        if (output_signature_.empty ())
        {   nits.pick (nit_signature_key, es_error, ec_init, "signing andor verifying require a signature file");
            valid_ = false; }
        else if (output_public_.empty ()) 
        {   nits.pick (nit_signature_key, es_error, ec_init, "a signature needs a public key");
            valid_ = false; }
        else if (output_password_.empty ())
            os_ -> consolidate (nits, output_public_, output_private_, ::std::string (), output_signature_);
        else
        {   bool borked = true;
            const ::std::string pw = read_text_file (nits, output_password_, borked);
            if (! borked)
                os_ -> consolidate (nits, output_public_, output_private_, pw, output_signature_); }
#endif // SIGNING
    os_ -> depre (nits);
    tim_.init (version_, nits, naughty_, nice_, note_);
    process_url_vars (nits);
    check_for_update (nits); }

void context_t::process_url_vars (nitpick& nits)
{   for (auto s : url_var_)
    {   const ::std::string::size_type pos = s.find (':');
        if (pos == ::std::string::npos)
            nits.pick (nit_syntax, es_error, ec_init, "url-var requires VAR:VAL, and ", quote (s), " has no ':'");
        else if (pos == 0)
            nits.pick (nit_syntax, es_error, ec_init, "url-var requires VAR:VAL, and ", quote (s), " has no variable");
        else
        {   const ::std::string var = trim_the_lot_off (::boost::to_lower_copy (s.substr (0, pos)));
            if (uvar_.find (var) != uvar_.cend ())
                nits.pick (nit_symbol_aleady_defined, es_error, ec_init, quote (s), " defined again; ignored");
            else if (var.find_first_not_of (URL_TEMPLATE_VAR) != ::std::string::npos)
                nits.pick (nit_template_variable, ed_rfc_6570, "2.3. Variables", es_error, ec_init, quote (var), " contains invalid characters");
            else
            {   const ::std::string val = s.substr (pos+1);
                const ::std::string::size_type sz = val.size ();
                PRESUME (! var.empty (), __FILE__, __LINE__);
                if (context.tell (es_debug))
                    nits.pick (nit_url_template, es_debug, ec_init, "setting URL template variable ", quote (var), " to ", quote (val));
                if ((sz > 1) &&
                    (   ((val.at (0) == '(') && (val.at (sz - 1) == ')')) || 
                        ((val.at (0) == '[') && (val.at (sz - 1) == ']'))))
                    nits.pick (nit_unimplemented, ed_rfc_6570, "1.2. Levels and Expression Types", es_warning, ec_init,
                        quote (var), ": regretfully, " PROG " does not support lists or arrays in url templates");
                else uvar_.emplace (var, val); } } } }

::std::string context_t::url_var_value (nitpick& nits, const ::std::string& var, const bool sauce, const bool zeq)
{   if (var.find_first_not_of (URL_TEMPLATE_VAR) != ::std::string::npos)
    {   nits.pick (nit_template_variable, ed_rfc_6570, "2.3. Variables", es_error, ec_init, quote (var), " contains invalid characters");
        return ::std::string (); }
    const ustr_t::const_iterator i = uvar_.find (trim_the_lot_off (::boost::to_lower_copy (var)));
    if (i != uvar_.cend ())
        if (! sauce) return i -> second;
        else return var + "=" + i -> second;
    nits.pick (nit_url_template, es_warning, ec_url, quote (var), " is not defined");
    if (! sauce) return ::std::string ();
    else if (! zeq) return var;
    return var + "="; }

#ifdef NO_JSONIC
void context_t::check_for_update (nitpick& ) // should be run in a separate thread
{ }
#else // NO_JSONIC
void context_t::check_for_update (nitpick& nits) // should be run in a separate thread
{   if (! update_info_.empty () || ! update_check_) return;
    try
    {   ::std::string content;
        nitpick nuts;
        url u (nuts, html_current, UPDATE_URL_1);
#ifdef UPDATE_URL_2
        url u2 (nuts, html_current, UPDATE_URL_2);
#endif // UPDATE_URL_2
        update_info_.clear ();
        if (! fetch_page (nuts, u, true, content))
#ifdef UPDATE_URL_2
            if (! fetch_page (nuts, u2, true, content))
#endif // UPDATE_URL_2
            {   mac (nm_update_info, "");
                return; }
        if (! content.empty ())
        {   jsonic j (nits, content, cc_utf8);
            if (! j.invalid ())
            {   ::boost::json::value v = j.val ();
                if (v.kind () == ::boost::json::kind::array)
                    for (   ::boost::json::array::const_iterator i = v.as_array ().cbegin ();
                            (i != nullptr) && (i != v.as_array ().cend ());
                            ++i)
                        if ( i -> kind () == ::boost::json::kind::object)
                        {   const ::std::int64_t mjr = i -> as_object ().at ("MJR").as_int64 ();
                            const ::std::int64_t mnr = i -> as_object ().at ("MNR").as_int64 ();   
                            const ::std::int64_t rel = i -> as_object ().at ("REL").as_int64 ();
                            if (mjr < VERSION_MAJOR) continue;
                            if ((mjr == VERSION_MAJOR) && (mnr < VERSION_MINOR)) continue;   
                            if ((mjr == VERSION_MAJOR) && (mnr == VERSION_MINOR) && (rel <= VERSION_RELEASE)) continue;
                            const ::std::string_view ver = i -> as_object ().at ("VER").as_string (); // I don't see the need to introduce string_view's riskiness here, but ...
                            const ::std::string_view notes = i -> as_object ().at ("NOTES").as_string ();
                            if (! ver.empty ())
                            {   update_info_ += PROG " version ";
                                update_info_ += ver; }
                            else update_info_ = "An update to " PROG;
                            update_info_ += "is available at ";
                            if (notes.empty ()) update_info_ += WEBADDR;
                            else update_info_ += notes;
                            break; } } } }
    catch (...)
    {   update_info_.clear (); }
    mac (nm_update_info, update_info_); }
#endif // NO_JSONIC

const robotic& context_t::robbie () const
{   if (robbie_.get () == nullptr) robbie_ = robotic_ptr (new robotic ());
    return *robbie_; }

robotic& context_t::robbie ()
{   if (robbie_.get () == nullptr) robbie_ = robotic_ptr (new robotic ());
    return *robbie_; }

const sec_txt& context_t::security () const
{   if (security_.get () == nullptr) security_ = sec_ptr (new sec_txt ());
    return *security_; }

sec_txt& context_t::security ()
{   if (security_.get () == nullptr) security_ = sec_ptr (new sec_txt ());
    return *security_; }

const ads& context_t::con () const
{   if (ads_.get () == nullptr) ads_ = ads_ptr (new ads ());
    return *ads_; }

ads& context_t::con ()
{   if (ads_.get () == nullptr) ads_ = ads_ptr (new ads ());
    return *ads_; }

bool context_t::has_extension (const ::std::string& name, const sstr_t& extensions) const
{   ::std::string ext (::boost::filesystem::path (name).extension ().string ());
    if (ext.empty ()) return false;
    if (ext.at (0) == '.') return be_it_there (extensions, ext.substr (1));
    return be_it_there (extensions, ext); }

bool context_t::is_ads (const ::std::string& name) const
{   return ::boost::filesystem::path (name).filename ().string () == "ads.txt"; }

bool context_t::is_atomic (const ::std::string& name) const
{   return has_extension (name, atomic_ext ()); }

bool context_t::is_css (const ::std::string& name) const
{   return has_extension (name, css_extension ()); }

bool context_t::is_jsonld (const ::std::string& name) const
{   return has_extension (name, jsonld_extension ()); }

bool context_t::is_robotic (const ::std::string& name) const
{   return ::boost::filesystem::path (name).filename ().string () == "robots.txt"; }

bool context_t::is_rsl (const ::std::string& name) const
{   return has_extension (name, rsl_ext ()); }

bool context_t::is_rss (const ::std::string& name) const
{   return has_extension (name, rss_ext ()); }

bool context_t::is_sec_txt (const ::std::string& name) const
{   return ::boost::filesystem::path (name).filename ().string () == "security.txt"; }

bool context_t::is_vtt (const ::std::string& name) const
{   return has_extension (name, vtt_extension ()); }

bool context_t::is_webpage (const ::std::string& name) const
{   return has_extension (name, extensions ()); }

e_verifiable_file context_t::verifiable_file_type (const ::std::string& name) const
{   if (is_webpage (name))
        return vf_markup;
    if (is_css (name))
        return vf_css;
    if (is_atomic (name))
        return atomic_verify () ? vf_atomic : vf_none;
    if (is_jsonld (name))
        return jsonld () ? vf_jsonld : vf_none;
    if (is_vtt (name))
        return load_vtt () ? vf_vtt : vf_none;
    if (is_rsl (name))
        return rsl_verify () ? vf_rsl : vf_none;
    if (is_rss (name))
        return rss_verify () ? vf_rss : vf_none;
    if (is_robotic (name))
        return robtxt () ? vf_robotic : vf_none;
    if (is_ads (name))
        return adstxt () ? vf_ads : vf_none;
    if (is_sec_txt (name))
        return sectxt () ? vf_security : vf_none;
    return vf_none; }
