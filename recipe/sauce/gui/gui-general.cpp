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

#ifdef WX
#include "gui/gui-app.h"
#include "gui/gui-general.h"
#include "utility/filesystem.h"

#define GEN_STYLE   DEF_STYLE
#define GEN_X       100
#define GEN_Y       100
#define GEN_WIDTH   400
#define GEN_HEIGHT  360
#define MIN_FILE_SIZE 1024
#define STRINGIZE_BORKED_MIN_FILE_SIZE "1024"

#define DEFAULT_PERSIST_FN "www.ssc"

BEGIN_EVENT_TABLE (general_t, d1_t)
  EVT_BUTTON (wxID_HELP, general_t::OnHelpClick)
  EVT_BUTTON (button_general_add, general_t::OnAdd)
  EVT_BUTTON (button_general_erase, general_t::OnErase)
  EVT_LISTBOX (list_general_ext, general_t::OnExclude)
  EVT_LISTBOX_DCLICK (list_general_ext, general_t::OnImpatience)
  EVT_BUTTON (button_general_rename, general_t::OnRename)
  EVT_CHECKBOX (check_file_size, general_t::OnMax)
#ifndef NO_FRED
  EVT_CHECKBOX (check_fred, general_t::OnFred)
#endif // NO_FRED
  EVT_CHECKBOX (check_file_persist, general_t::OnPersist)
  EVT_CHECKBOX (file_general_name, general_t::OnConfig)
  EVT_TEXT (text_general_ext, general_t::OnText)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (general_t, d1_t)

general_t :: general_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (GEN_X, GEN_Y), wxSize (GEN_WIDTH, GEN_HEIGHT))
{	Create (mummy, id, caption); } 

bool general_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (GEN_X, GEN_Y), wxSize (GEN_WIDTH, GEN_HEIGHT), GEN_STYLE)) return false;
    CreateControls ();
    return true; }

void general_t :: create_controls (wxWindow *parent)
{	cwd_ = get_working_directory () / ".ssc";
    if (    check_box_.template concoct < wxBoxSizer > (parent, box_, wxALIGN_CENTRE) &&
            check_static_.concoct < wxBoxSizer > (parent, check_box_.box_, "verify:   ") &&
            class_ctrl_.concoct (parent, check_box_.box_, wxID_ANY, "styled classes  ", wxALIGN_CENTRE_VERTICAL) &&
            other_ctrl_.concoct (parent, check_box_.box_, wxID_ANY, "every class  ", wxALIGN_CENTRE_VERTICAL) &&
            l5_.concoct (parent, box_) &&
            type_box_.template concoct < wxBoxSizer > (parent, box_, wxALIGN_CENTRE) &&
            rdfa_ctrl_.concoct (parent, type_box_.box_, wxID_ANY, "nitpick RDFa files   ", wxALIGN_CENTRE_VERTICAL) &&
            vtt_ctrl_.concoct (parent, type_box_.box_, wxID_ANY, "nitpick VTT files", wxALIGN_CENTRE_VERTICAL) &&
            vcs_ctrl_.concoct (parent, box_, wxID_ANY, "ignore version control files", wxALL | wxALIGN_CENTRE_HORIZONTAL) &&
#ifndef NO_FRED
            l1_.concoct (parent, box_) &&
            fred_box_.template concoct < wxBoxSizer > (parent, box_, wxALIGN_CENTRE) &&
            fred_ctrl_.concoct (parent, fred_box_.box_, check_fred, "limit thread count", wxALIGN_CENTRE_VERTICAL) &&
            fred_spin_.concoct (parent, fred_box_.box_, spin_fred, ::std::string ("max:"), ::std::string ("1"), 1, 1, GSL_NARROW_CAST < int > (fred_t :: no_more_than ())) &&
#endif // NO_FRED
            l2_.concoct (parent, box_) &&
            exclude_.concoct (parent, box_, "exclude these extensions:", "tmp") &&
            l3_.concoct (parent, box_) &&
            max_box_.template concoct < wxBoxSizer > (parent, box_, wxALIGN_CENTRE) &&
            max_ctrl_.concoct (parent, max_box_.box_, check_file_size, "limit file size", wxALIGN_CENTRE_VERTICAL) &&
            max_spin_.concoct (parent, max_box_.box_, spin_file_size, ::std::string ("max bytes:"), ::std::string (STRINGIZE_BORKED_MIN_FILE_SIZE), def_max_file_size, MIN_FILE_SIZE, def_max_file_size) &&
            l4_.concoct (parent, box_) &&
            config_folder_.concoct (parent, box_, file_general_name, "Configuration " REPERTOIRE ":", ::boost::filesystem::path (), cwd_.string ()) &&
            l6_.concoct (parent, box_) &&
            persist_file_.concoct (parent, box_, check_file_persist, "Cache scan results", "cache.ssc", "cache file:", "*.ssc"))
        l7_.concoct (parent, box_); }

void general_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH); }

void general_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help (hp_bobs); }

#ifndef NO_FRED
void general_t :: enable_fred (const bool b)
{	fred_spin_.enable (b); }
#endif // NO_FRED

void general_t :: enable_max (const bool b)
{	max_spin_.enable (b); }

void general_t :: OnConfig (wxCommandEvent& )
{	if (invalid ()) return;
    config_folder_.click (); }

void general_t :: OnPersist (wxCommandEvent& )
{	if (invalid ()) return;
    persist_file_.click (); }

void general_t :: OnMax (wxCommandEvent& )
{	if (invalid ()) return;
    enable_max (max_ctrl_.selected ()); }

#ifndef NO_FRED
void general_t :: OnFred (wxCommandEvent& )
{	if (invalid ()) return;
    enable_fred (fred_ctrl_.selected ()); }
#endif // NO_FRED

void general_t :: OnAdd (wxCommandEvent& e)
{	exclude_.OnAdd (e); }

void general_t :: OnErase (wxCommandEvent& e)
{	exclude_.OnErase (e); }

void general_t :: OnExclude (wxCommandEvent& e)
{	exclude_.OnTap (e); }

void general_t :: OnImpatience (wxCommandEvent& e)
{	exclude_.OnImpatience (e); }

void general_t :: OnRename (wxCommandEvent& e)
{	exclude_.OnRename (e); }

void general_t :: OnText (wxCommandEvent& e)
{	exclude_.OnText (e); }

bool general_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    class_ctrl_.select (class_);
    other_ctrl_.select (other_);
    rdfa_ctrl_.select (rdfa_);
    vcs_ctrl_.select (vcs_);
    vtt_ctrl_.select (vtt_);
    max_spin_.value (max_);
    max_ctrl_.select (max_ != 0);
#ifndef NO_FRED
    fred_spin_.value (fred_);
    fred_ctrl_.select (fred_ != 0);
#endif // NO_FRED
    if (config_.empty ()) config_ = cwd_;
    config_folder_.value (config_);
    exclude_.preload < vstr_t > (exc_);
    persist_file_.value (persist_);
    config_folder_.TransferDataToWindow ();
    persist_file_.TransferDataToWindow ();
    return true; }

bool general_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
    config_folder_.TransferDataFromWindow ();
    persist_file_.TransferDataFromWindow ();
    other_ = other_ctrl_.selected ();
    class_ = class_ctrl_.selected ();
    rdfa_ = rdfa_ctrl_.selected ();
    vcs_ = vcs_ctrl_.selected ();
    vtt_ = vtt_ctrl_.selected ();
    if (! max_ctrl_.selected ()) max_ = 0;
    else max_ = max_spin_.value ();
#ifndef NO_FRED
    if (! fred_ctrl_.selected ()) fred_ = 0;
    else fred_ = fred_spin_.value ();
#endif // NO_FRED
    config_ = config_folder_.value ();
    persist_ = persist_file_.value ();
    exclude_.acquire < vstr_t > (exc_);
    return true; }

void general_t :: max_file_size (const unsigned int& m)
{   PRESUME (m >= MIN_FILE_SIZE, __FILE__, __LINE__);
    max_ = m; }    

#ifndef NO_FRED
void general_t :: fred (const unsigned short& t)
{   PRESUME (t <= fred_t :: no_more_than (), __FILE__, __LINE__);
    fred_ = t; }    
#endif // NO_FRED

bool general_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

void general_t :: load_from_context (const context_t& c)
{	clss (c.unknown_class ());
    other (c.classic ());
    rdfa (c.rdfa ());
    vcs (c.vcs ());
    vtt (c.load_vtt ());
#ifndef NO_FRED
    fred (GSL_NARROW_CAST < unsigned short > (c.fred ()));
#endif // NO_FRED
    max_file_size (GSL_NARROW_CAST < unsigned int > (c.max_file_size ()));
    config (c.path ().c_str ());
    exc (c.exclude ());
    persist (c.persisted ()); }

void general_t :: save_to_context (context_t& c) const
{	c.unknown_class (clss ());
    c.classic (other ());
    c.rdfa (rdfa ());
    c.vcs (vcs ());
    c.load_vtt (vtt ());
#ifndef NO_FRED
    c.fred (fred ());
#endif // NO_FRED
    c.max_file_size (max_file_size ());
    c.path (config ().string ());
    nitpick nits;
    c.exclude (nits, exc ());
    c.persisted (persist ().string ()); }

#endif // WX
