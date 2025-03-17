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

#include "main/standard.h"

#ifdef WX
#include "gui/gui-app.h"
#include "gui/gui-html.h"
#include "utility/filesystem.h"

#define HTML_STYLE   DEF_STYLE
#define HTML_X       100
#define HTML_Y       100
#define HTML_WIDTH   600
#define HTML_HEIGHT  350

BEGIN_EVENT_TABLE (html_t, d1_t)
  EVT_BUTTON (wxID_HELP, html_t::OnHelpClick)
  EVT_CHOICE (choice_html_version, html_t::OnVersion)
  EVT_CHOICE (check_wx, html_t::OnWX)
  EVT_CHECKBOX (check_corpus_output, html_t::OnOutput)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (html_t, d1_t)

#define DEFAULT_CORPUS_FN	"corpus.xml"

html_t :: html_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (HTML_X, HTML_Y), wxSize (HTML_WIDTH, HTML_HEIGHT)), hv_ (selection_count - 1)
{	Create (mummy, id, caption); } 

bool html_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (HTML_X, HTML_Y), wxSize (HTML_WIDTH, HTML_HEIGHT), HTML_STYLE)) return false;
    CreateControls ();
    return true; }

void html_t :: create_controls (wxWindow *parent)
{	//bool rational = true;
    //if (parent == this) rational = app -> frame () -> rational ();

    const long rg = (wxALL | wxALIGN_RIGHT);
    const long al = wxALIGN_RIGHT;

    if (    html_ctrl_.concoct (parent, box_, choice_html_version, "&X/HTML version: ") &&
            math_ctrl_.concoct (parent, box_, choice_math_version, "&MathML version: ") &&
            svg_ctrl_.concoct (parent, box_, choice_svg_version, "S&VG version: ") &&
            line_ctrl_.concoct < wxBoxSizer > (parent, box_) &&
            stray_ctrl_.concoct (parent, box_, wxID_ANY, "if no <!DOCTYPE...>, presume", { "H&TML Tags", "HT&ML 1.0", "&default" }) &&
            title_ctrl_.concoct < wxBoxSizer > (parent, box_) &&
            lingo_ctrl_.concoct (parent, box_, wxID_ANY, "default &language: ") &&
            width_ctrl_.concoct (parent, box_, wxID_ANY, "<TITLE> less than (chars.):", ::std::string (), max_, 0, 75) &&
            option_ctrl_.concoct < wxBoxSizer > (parent, box_) &&
            czech_ctrl_.concoct (parent, box_, 2) &&
            sloven_ctrl_.concoct < typename grid_t::box_ptr > (parent, czech_ctrl_.box_, wxID_ANY, "warn of inefficient HTML", rg, al) &&
            wx_ctrl_.concoct < typename grid_t::box_ptr > (parent, czech_ctrl_.box_, check_wx, "wxWidgets compatibility") &&
            ie_ctrl_.concoct < typename grid_t::box_ptr > (parent, czech_ctrl_.box_, wxID_ANY, "ignore IE oddities", rg, al) &&
            safari_ctrl_.concoct < typename grid_t::box_ptr > (parent, czech_ctrl_.box_, wxID_ANY, "ignore Sa&fari oddities") &&
            rfc1867_ctrl_.concoct < typename grid_t::box_ptr > (parent, czech_ctrl_.box_, wxID_ANY, "INPUT=FILE (RFC 1867)", rg, al) &&
            rfc1942_ctrl_.concoct < typename grid_t::box_ptr > (parent, czech_ctrl_.box_, wxID_ANY, "tables (RFC 1942") &&
            rfc1980_ctrl_.concoct < typename grid_t::box_ptr > (parent, czech_ctrl_.box_, wxID_ANY, "image maps (RFC 1980)", rg, al) &&
            rfc2070_ctrl_.concoct < typename grid_t::box_ptr > (parent, czech_ctrl_.box_, wxID_ANY, "international (RFC 2070)") &&
            twixt_ctrl_.concoct < wxBoxSizer > (parent, box_) &&
            file_ctrl_.concoct (parent, box_, check_corpus_output, "output search engine corpus (XML)", "corpus.xml", "output XML to", "*.xml") &&
            wot_ctrl_.concoct (parent, box_, "acquire corpus data from content of:", wxALL | wxALIGN_CENTRE_HORIZONTAL) &&
            cheque_ctrl_.concoct (parent, box_, 3, wxALL | wxALIGN_CENTRE_HORIZONTAL) &&
            article_ctrl_.concoct < typename grid_t::box_ptr > (parent, cheque_ctrl_.box_, wxID_ANY, "<article>", wxALL | wxEXPAND) &&
            body_ctrl_.concoct < typename grid_t::box_ptr > (parent, cheque_ctrl_.box_, wxID_ANY, "<body>", wxALL | wxEXPAND))
        main_ctrl_.concoct < typename grid_t::box_ptr > (parent, cheque_ctrl_.box_, wxID_ANY, "<main>", wxALL | wxEXPAND); }

void html_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH); }

void html_t :: OnHelpClick (wxCommandEvent& )
{	app -> help (hp_HTML); }

void html_t :: enable ()
{	bool h2 = false;
    bool ms = true;
    const bool nowx = wx_ctrl_.selected ();
    switch (html_ctrl_.selected ())
    {	case 0 :
        case 1 :
        case 6 :
        case 7 :
            ms = false;
            break;
        case 3 : //html_2
        case 4 : //html_2_level_1
        case 5 : //html_2_level_2
            h2 = true;
            ms = nowx;
            break;
        default :
            ms = nowx;
            h2 = false;
            break; }
    rfc1867_ctrl_.enable (h2);
    rfc1942_ctrl_.enable (h2);
    rfc1980_ctrl_.enable (h2);
    rfc2070_ctrl_.enable (h2);
    math_ctrl_.enable (ms);	
    svg_ctrl_.enable (ms); }

void html_t :: enable_corpus (const bool b)
{	file_ctrl_.select (b);
    article_ctrl_.enable (b);
    body_ctrl_.enable (b);
    main_ctrl_.enable (b);
    wot_ctrl_.enable (b); }

void html_t :: enable_wx (const bool b)
{	math_ctrl_.enable (b);	
    svg_ctrl_.enable (b);	}

void html_t :: OnWX (wxCommandEvent& )
{	if (invalid ()) return;
    if (wx_ctrl_.selected ()) enable_wx (false);
    else switch (html_ctrl_.selected ())
    {	case 0 :
        case 1 :
        case 6 :
        case 7 :
            enable_wx (false);
            break;
        default :
            enable_wx (true);
            break; } }

void html_t :: OnOutput (wxCommandEvent& )
{	if (invalid ()) return;
    const bool outed = file_ctrl_.selected ();
    if (path_.empty () && outed)
    {	path_ = get_working_directory ();
        path_ /= DEFAULT_CORPUS_FN;
        file_ctrl_.value (path_); }
    enable_corpus (outed); }

void html_t :: OnVersion (wxCommandEvent& )
{	if (invalid ()) return;
    enable (); }

bool html_t :: TransferDataToWindow ()
{	if (invalid ()) return false;	
    switch (dt_)
    {	case 0 :
        case 2 : stray_ctrl_.select (static_cast < int > (dt_)); break;
        default : stray_ctrl_.select (1); break; }
    width_ctrl_.value (max_);
    sloven_ctrl_.select (bsloven_);
    ie_ctrl_.select (bie_);
    safari_ctrl_.select (bsafari_);
    rfc1867_ctrl_.select (b1867_);
    rfc1942_ctrl_.select (b1942_);
    rfc1980_ctrl_.select (b1980_);
    rfc2070_ctrl_.select (b2070_);
    wx_ctrl_.select (bwx_);
    if (lang_.empty ()) lang_ = "en";
    int ls = lingo_ctrl_.find (lang_);
    if (ls == wxNOT_FOUND)
    {   lingo_ctrl_.append (lang_);
        ls = lingo_ctrl_.find (lang_);
        PRESUME (ls != wxNOT_FOUND, __FILE__, __LINE__); }
    lingo_ctrl_.select (ls);
    PRESUME (selection_count > 0, __FILE__, __LINE__);
    if (hv_ >= selection_count)
        html_ctrl_.select (GSL_NARROW_CAST < int > (selection_count - 1));
    else html_ctrl_.select (GSL_NARROW_CAST < int > (hv_));
    math_ctrl_.select (math_);
    svg_ctrl_.select (svg_);
    enable ();
    article_ctrl_.select (art_);
    body_ctrl_.select (bod_);
    main_ctrl_.select (mai_);
    const bool outed = file_ctrl_.selected ();
    file_ctrl_.value (path_);
    enable_corpus (outed);
    return true; }

bool html_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
    dt_ = GSL_NARROW_CAST < unsigned short > (stray_ctrl_.selected ());
    PRESUME (dt_ < 3, __FILE__, __LINE__);
    max_ = width_ctrl_.value ();
    bsloven_ = sloven_ctrl_.selected ();
    bie_ = ie_ctrl_.selected ();
    bsafari_ = safari_ctrl_.selected ();
    b1867_ = rfc1867_ctrl_.selected ();
    b1942_ = rfc1942_ctrl_.selected ();
    b1980_ = rfc1980_ctrl_.selected ();
    b2070_ = rfc2070_ctrl_.selected ();
    bwx_ = wx_ctrl_.selected();
    hv_ = GSL_NARROW_CAST < unsigned short > (html_ctrl_.selected ());
    lang_ = lingo_ctrl_.chosen ();
    math_ = math_ctrl_.selected ();
    svg_ = svg_ctrl_.selected ();
    path_ = file_ctrl_.value ();
    art_ = article_ctrl_.selected ();
    bod_ = body_ctrl_.selected ();
    mai_ = main_ctrl_.selected ();
    return true; }

html_version html_t :: ver () const
{	if (hv_ >= selection_count) return html_current;
    return selection_version [hv_]; }

void html_t :: ver (const html_version& v)
{	for (::std::size_t n = 0; n < selection_count; ++n)
        if (selection_version [n] == v)
        {	hv_ = GSL_NARROW_CAST < unsigned short > (n);
            return; }
    hv_ = selection_count - 1; }

bool html_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

void html_t :: load_from_context (const context_t& c)
{   ie (c.ie ());
    rfc1867 (c.rfc_1867 ());
    rfc1942 (c.rfc_1942 ());
    rfc1980 (c.rfc_1980 ());
    rfc2070 (c.rfc_2070 ());
    safari (c.safari ());
    sloven (c.sloven ());
    title (GSL_NARROW_CAST < unsigned int > (c.title ()));
    ver (c.html_ver ());
    if (c.force_version ()) doctype (2);
    else if (c.presume_tags ()) doctype (0);
    else doctype (1);
    lingo (c.lang ()); 
    wx (c.wx ()); 
    math_version (c.math_version ()); 
    svg_version (c.svg_version ());
    folder (c.corpus ());
    article (c.article ());
    body (c.body ());
    main (c.main ()); }

void html_t :: save_to_context (context_t& c) const
{   c.ie (ie ());
    c.rfc_1867 (rfc1867 ());
    c.rfc_1942 (rfc1942 ());
    c.rfc_1980 (rfc1980 ());
    c.rfc_2070 (rfc2070 ());
    c.safari (safari ());
    c.sloven (sloven ());
    c.title (title ());
    c.html_ver (ver ());
    c.lang (lingo ());
    c.wx (wx ());
    switch (doctype ())
    {   case 0 : c.force_version (false); c.presume_tags (true); break;
        case 2 : c.force_version (true); c.presume_tags (false); break;
        default : c.force_version (false); c.presume_tags (false); break; }
    c.math_version (math_version ());
    c.svg_version (svg_version ());
    c.corpus (folder ());
    c.article (article ());
    c.body (body ());
    c.main (main ()); }

#endif // WX
