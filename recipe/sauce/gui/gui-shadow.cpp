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
#include "gui/gui-shadow.h"
#include "utility/filesystem.h"

#define DEFAULT_SHADOW_FN PROG ".shadow"

#define SHADOW_STYLE   DEF_STYLE
#define SHADOW_X       100
#define SHADOW_Y       100
#define SHADOW_WIDTH   500
#define SHADOW_HEIGHT  475

BEGIN_EVENT_TABLE (shadow_t, d1_t)
  EVT_BUTTON (wxID_HELP, shadow_t::OnHelpClick)
  EVT_CHECKBOX (check_site, shadow_t::OnShadow)
  EVT_BUTTON (button_shadow_add, shadow_t::OnIgnoreAdd)
  EVT_BUTTON (button_shadow_erase, shadow_t::OnIgnoreErase)
  EVT_BUTTON (button_shadow_rename, shadow_t::OnIgnoreRename)
  EVT_TEXT (text_shadow_ext, shadow_t::OnIgnoreTap)
  EVT_LISTBOX (list_shadow_ext, shadow_t::OnIgnoreExtension)
  EVT_LISTBOX_DCLICK (list_shadow_ext, shadow_t::OnIgnoreImpatience)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (shadow_t, d1_t)

shadow_t :: shadow_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (SHADOW_X, SHADOW_Y), wxSize (SHADOW_WIDTH, SHADOW_HEIGHT))
{	Create (mummy, id, caption); } 

bool shadow_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (SHADOW_X, SHADOW_Y), wxSize (SHADOW_WIDTH, SHADOW_HEIGHT), SHADOW_STYLE)) return false;
    CreateControls ();
    return true; }

void shadow_t :: create_controls (wxWindow *parent)
{	grid_check_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));
    if (grid_check_ != nullptr)
    {	check_site_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_site, "Enable shadowing", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
        if (check_site_ != nullptr)
        {	grid_check_ -> Add (check_site_, 0, wxALIGN_RIGHT|wxALL, 5);
            check_change_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Ignore unchanged files", wxDefaultPosition, wxDefaultSize));
            if (check_change_ != nullptr)
            {	grid_check_ -> Add (check_change_, 0, wxALL, 5);
                check_keep_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Preserve comments", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
                if (check_keep_ != nullptr)
                {	grid_check_ -> Add (check_keep_, 0, wxALIGN_RIGHT|wxALL, 5);
                    check_time_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Note generated time", wxDefaultPosition, wxDefaultSize));
                    if (check_time_ != nullptr)
                    {	grid_check_ -> Add (check_time_, 0, wxALL, 5);
                        check_whitespace_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Merge whitespace", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
                        if (check_whitespace_ != nullptr)
                        {	grid_check_ -> Add (check_whitespace_, 0, wxALIGN_RIGHT|wxALL, 5);
                            check_ssi_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Server Side Includes", wxDefaultPosition, wxDefaultSize));
                            if (check_ssi_ != nullptr)
                            {	grid_check_ -> Add (check_ssi_, 0, wxALL, 5);
                                box_ -> Add (grid_check_, 0, wxEXPAND, 5);
                                line_check_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
                                if (line_check_ != nullptr)
                                    box_ -> Add (line_check_, 0, wxEXPAND | wxALL, 5); } } } } } } }

    box_strat_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_strat_ != nullptr)
    {	stat_strat_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Shadow Strategy:", wxDefaultPosition, wxDefaultSize, 0));
        if (stat_strat_ != nullptr)
        {	box_strat_ -> Add (stat_strat_, 0, wxALIGN_CENTER_VERTICAL, 5);
            stat_strat_ -> Wrap (-1);
            wxString strategies [] = { "Do Nothing", "Write pages only",
#ifndef NOLYNX
                "Hard links to unchanged files", "Soft links to unchanged files",
#endif // NOLYNX
                "Copy all files", "Copy and deduplicate files", "Report duplicates only" };
            strat_count_ = sizeof (strategies) / sizeof (wxString);
            choice_strat_ = GSL_OWNER (wxChoice) (new wxChoice (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, strat_count_, strategies, 0));
            if (choice_strat_ != nullptr)
            {	choice_strat_ -> SetSelection (0);
                box_strat_ -> Add (choice_strat_, 0, wxALL, 5);
                box_ -> Add (box_strat_, 0, wxALIGN_CENTER_HORIZONTAL, 5); } } }

    box_site_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_site_ != nullptr)
    {	stat_site_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Create shadow site in ", wxDefaultPosition, wxDefaultSize, 0));
        if (stat_site_ != nullptr)
        {	box_site_ -> Add (stat_site_, 0, wxALIGN_CENTER_VERTICAL, 5);
            dir_site_ = GSL_OWNER (wxDirPickerCtrl) (new wxDirPickerCtrl( parent, wxID_ANY, wxEmptyString, "Select a " REPERTOIRE, wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE));
            if (dir_site_ !=  nullptr)
                box_site_ -> Add (dir_site_, 0, wxALL, 5); }
        box_ -> Add (box_site_, 0, wxALIGN_CENTER_HORIZONTAL, 5);
        line_site_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
        if (line_site_ != nullptr)
            box_ -> Add (line_site_, 0, wxEXPAND | wxALL, 5); }

    box_comment_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_comment_ != nullptr)
    {	stat_comment_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Insert parent comment in pages:", wxDefaultPosition, wxDefaultSize, 0));
        if (stat_comment_ != nullptr)
        {	box_comment_ -> Add (stat_comment_, 0, wxALIGN_CENTER_VERTICAL, 5);
            text_comment_ = GSL_OWNER (wxTextCtrl) (new wxTextCtrl (parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0));
            if (text_comment_ != nullptr)
            {	box_comment_ -> Add (text_comment_, 0, wxALL, 5);
                box_ -> Add (box_comment_, 0, wxALIGN_CENTER_HORIZONTAL, 5);
                line_comment_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
                if (line_comment_ != nullptr)
                    box_ -> Add (line_comment_, 0, wxEXPAND | wxALL, 5); } } }

    box_cache_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_cache_ != nullptr)
    {	stat_cache_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Shadow cache:", wxDefaultPosition, wxDefaultSize, 0));
        if (stat_cache_ != nullptr)
        {	box_cache_ -> Add (stat_cache_, 0, wxALIGN_CENTER_VERTICAL, 5);
            file_cache_ = GSL_OWNER (wxFilePickerCtrl) (new wxFilePickerCtrl( parent, wxID_ANY, wxEmptyString, "Select a file", "*.ndx", wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT | wxFLP_SAVE | wxFLP_USE_TEXTCTRL));
            if (file_cache_ != nullptr)
            {	box_cache_ -> Add (file_cache_, 0, wxALL, 5);
                box_ -> Add (box_cache_, 0, wxALIGN_CENTER_HORIZONTAL, 5);
                line_cache_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
                if (line_cache_ != nullptr)
                    box_ -> Add (line_cache_, 0, wxEXPAND | wxALL, 5); } } }

    ignore_.construct (parent, box_, "ignore files with extensions:");

    line_base_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
        if (line_base_ != nullptr)
            box_ -> Add (line_base_, 0, wxEXPAND | wxALL, 5); }

void shadow_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH); }

void shadow_t :: enable ()
{	PRESUME (! invalid (), __FILE__, __LINE__);
    const bool checked = check_site_ -> IsChecked ();
    check_change_ -> Enable (checked);
    check_keep_ -> Enable (checked);
    check_ssi_ -> Enable (checked);
    check_time_ -> Enable (checked);
    check_time_ -> Enable (checked);
    check_whitespace_ -> Enable (checked);
    dir_site_ -> Enable (checked);
    file_cache_ -> Enable (checked);
    choice_strat_ -> Enable (checked);
    text_comment_ -> Enable (checked);
    stat_cache_ -> Enable (checked);
    stat_comment_ -> Enable (checked);
    stat_site_ -> Enable (checked);
    stat_strat_ -> Enable (checked);
    ignore_.enable (checked); }

void shadow_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("shadow"); }

void shadow_t :: OnIgnoreAdd (wxCommandEvent& e)
{	if (invalid ()) return;
    ignore_.OnAdd (e); }

void shadow_t :: OnIgnoreErase (wxCommandEvent& e)
{	if (invalid ()) return;
    ignore_.OnErase (e); }

void shadow_t :: OnIgnoreRename (wxCommandEvent& e)
{	if (invalid ()) return;
    ignore_.OnRename (e); }

void shadow_t :: OnIgnoreExtension (wxCommandEvent& e)
{	if (invalid ()) return;
    ignore_.OnText (e); }

void shadow_t :: OnIgnoreTap (wxCommandEvent& e)
{	if (invalid ()) return;
    ignore_.OnTap (e); }

void shadow_t :: OnIgnoreImpatience (wxCommandEvent& e)
{	if (invalid ()) return;
    ignore_.OnImpatience (e); }

void shadow_t :: OnShadow (wxCommandEvent& )
{	if (invalid ()) return;
    enable (); }

bool shadow_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    if (change_) check_change_ -> Set3StateValue (wxCHK_CHECKED);
    else check_change_ -> Set3StateValue (wxCHK_UNCHECKED);
    if (keep_) check_keep_ -> Set3StateValue (wxCHK_CHECKED);
    else check_keep_ -> Set3StateValue (wxCHK_UNCHECKED);
    if (site_) check_site_ -> Set3StateValue (wxCHK_CHECKED);
    else check_site_ -> Set3StateValue (wxCHK_UNCHECKED);
    if (ssi_) check_ssi_ -> Set3StateValue (wxCHK_CHECKED);
    else check_ssi_ -> Set3StateValue (wxCHK_UNCHECKED);
    if (time_) check_time_ -> Set3StateValue (wxCHK_CHECKED);
    else check_time_ -> Set3StateValue (wxCHK_UNCHECKED);
    if (whitespace_) check_whitespace_ -> Set3StateValue (wxCHK_CHECKED);
    else check_whitespace_ -> Set3StateValue (wxCHK_UNCHECKED);
    if (shadow_.empty ()) shadow_ = get_working_directory ();
    dir_site_ -> SetPath (shadow_.string ().c_str ()); 
    if (cache_.empty ())
    {	cache_ = get_working_directory ();
        cache_ /= DEFAULT_SHADOW_FN; }
    wxFileName c (cache_.string ());
    file_cache_ -> SetFileName (c);
    ignore_.preload (ext_);
#ifdef NOLYNX
    const int strat = (strat_ <= c_html) ? strat_ : (strat_ - 2);
    choice_strat_ -> SetSelection (strat);
#else // NOLYNX
    choice_strat_ -> SetSelection (strat_);
#endif // NOLYNX
    text_comment_ -> SetValue (comment_.c_str ());
    enable ();
    return true; }

bool shadow_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	
    change_ = check_change_ -> IsChecked ();
    keep_ = check_keep_ -> IsChecked ();
    site_ = check_site_ -> IsChecked ();
    ssi_ = check_ssi_ -> IsChecked ();
    whitespace_ = check_whitespace_ -> IsChecked ();
    shadow_ = ::std::string (dir_site_ -> GetPath ().c_str ());
    cache_ = ::std::string (file_cache_ -> GetFileName ().GetFullPath ().c_str ());
    ext_ = ignore_.acquire ();
#ifdef NOLYNX
    const int sel = choice_strat_ -> GetSelection ();
    strat_ = GSL_NARROW_CAST < e_copy > ((sel < 2) ? sel : (sel + 2));
#else // NOLYNX
    strat_ = static_cast < e_copy > (choice_strat_ -> GetSelection ());
#endif // NOLYNX
    comment_ = text_comment_ -> GetValue ().c_str (); 
    return true; }

bool shadow_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

void shadow_t :: load_from_context (const context_t& c)
{	cache (c.shadow_persist ());
    change (c.shadow_changed ());
    comment (c.msg ());
    keep (c.shadow_comment ());
    ignore (c.shadow_ignore ());
    shadow (c.shadow_root ());
    site (c.shadow_enable ());
    ssi (c.shadow_ssi ());
    strategy (c.copy ());
    time (c.info ());
    whitespace (c.shadow_space ()); }

void shadow_t :: save_to_context (context_t& c) const
{   c.shadow_changed (change ());
    c.copy (strategy ());
    c.info (time ());
    c.msg (comment ());
    c.shadow_comment (keep ());
    c.shadow_enable (site ());
    c.shadow_ignore (ignore ());
    c.shadow_persist (cache ().string ());
    c.shadow_root (shadow ().string ());
    c.shadow_space (whitespace ());
    c.shadow_ssi (ssi ()); }

#endif // WX
