/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
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

#ifdef WX
#include "gui/gui-dialogue.h"
#include "gui/gui-data.h"
#include "parser/html_version.h"

#define HTML_CAPTION "HTML"

class html_t : public d1_t < wx_html >
{   check_t article_ctrl_, body_ctrl_, ie_ctrl_, output_ctrl_, main_ctrl_, rfc1867_ctrl_, rfc1942_ctrl_, rfc1980_ctrl_,
            rfc2070_ctrl_, safari_ctrl_, sloven_ctrl_, wx_ctrl_;
    check_file_t file_ctrl_;
    grid_t czech_ctrl_, cheque_ctrl_;
    html_version_t html_ctrl_;
    label_spin_t width_ctrl_;
    label_t wot_ctrl_;
    line_t line_ctrl_, option_ctrl_, title_ctrl_, twixt_ctrl_;
    lingo_t lingo_ctrl_;
    math_version_t math_ctrl_;
    radio_t stray_ctrl_;
    svg_version_t svg_ctrl_;
    bool b1867_ = false, b1942_ = false, b1980_ = false, b2070_ = false, bie_ = false, bsafari_ = false, bsloven_ = false,
        bwx_ = false, art_ = false, bod_ = false, mai_ = false;
    unsigned int max_ = MAX_IDEAL_TITLE_LENGTH;
    e_math_version math_ = math_none;
    e_svg_version svg_ = sv_none;
    ::std::size_t dt_ = 0, hv_ = 0;
    ::std::string lang_ = "en";
    ::boost::filesystem::path path_;
    void enable ();
    void enable_corpus (const bool b);
    void enable_wx (const bool b);
    DECLARE_CLASS (html_t)
    DECLARE_EVENT_TABLE ()
public:
    html_t () = default;
    html_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = HTML_CAPTION);
    ~html_t () = default;
    bool invalid () const noexcept { return main_ctrl_.invalid (); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = HTML_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    void OnOutput (wxCommandEvent& e);
    void OnVersion (wxCommandEvent& event);
    void OnWX (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid_panel () const { return invalid () || (panel_ == nullptr); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;
    html_version ver () const;
    void ver (const html_version& v);
    unsigned int title () const { return max_; }
    void title (const unsigned int l) { max_ = l; }
    ::std::size_t doctype () const { return dt_; }
    void doctype (const ::std::size_t l) { dt_ = l; }
    ::boost::filesystem::path folder () const { return path_; }
    void folder (const ::boost::filesystem::path& p) { path_ = p; }
    bool rfc1867 () const noexcept { return b1867_; }
    void rfc1867 (const bool b) noexcept { b1867_ = b; }
    bool rfc1942 () const noexcept { return b1942_; }
    void rfc1942 (const bool b) noexcept { b1942_ = b; }
    bool rfc1980 () const noexcept { return b1980_; }
    void rfc1980 (const bool b) noexcept { b1980_ = b; }
    bool rfc2070 () const noexcept { return b2070_; }
    void rfc2070 (const bool b) noexcept { b2070_ = b; }
    bool ie () const noexcept { return bie_; }
    void ie (const bool b) noexcept { bie_ = b; }
    ::std::string lingo () const noexcept { return lang_; }
    void lingo (const ::std::string& s) { if (! s.empty ()) lang_ = s; }
    bool sloven () const noexcept { return bsloven_; }
    void sloven (const bool b) noexcept { bsloven_ = b; }
    bool safari () const noexcept { return bsafari_; }
    void safari (const bool b) noexcept { bsafari_ = b; }
    bool wx () const noexcept { return bwx_; }
    void wx (const bool b) noexcept { bwx_ = b; }
    void math_version (const e_math_version m) { math_ = m; }
    e_math_version math_version () const { return math_; }
    void svg_version (const e_svg_version sv) { svg_ = sv; }
    e_svg_version svg_version () const { return svg_; }
    bool article () const noexcept { return art_; }
    void article (const bool b) noexcept { art_ = b; }
    bool body () const noexcept { return bod_; }
    void body (const bool b) noexcept { bod_ = b; }
    bool main () const noexcept { return mai_; }
    void main (const bool b) noexcept { mai_ = b; } };
#endif // WX
