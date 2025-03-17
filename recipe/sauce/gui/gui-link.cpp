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
#include "gui/gui-link.h"
#include "utility/filesystem.h"
#include "type/type.h"

#define LINK_STYLE   DEF_STYLE
#define LINK_X       100
#define LINK_Y       100
#define LINK_WIDTH   430
#define LINK_HEIGHT  360

BEGIN_EVENT_TABLE (link_t, d1_t)
  EVT_BUTTON (wxID_HELP, link_t::OnHelpClick)
  EVT_BUTTON (button_req_add, link_t::OnAdd)
  EVT_BUTTON (button_req_erase, link_t::OnErase)
  EVT_LISTBOX (button_req_rename, link_t::OnExtension)
  EVT_CHECKBOX (check_external, link_t::OnExternal)
  EVT_LISTBOX_DCLICK (button_req_rename, link_t::OnImpatience)
  EVT_CHECKBOX (check_internal, link_t::OnInternal)
  EVT_BUTTON (button_req_rename, link_t::OnRename)
  EVT_TEXT (button_req_rename, link_t::OnTap)
  EVT_TEXT (text_req_ext, link_t::OnText)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (link_t, d1_t)

link_t :: link_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (LINK_X, LINK_Y), wxSize (LINK_WIDTH, LINK_HEIGHT))
{	Create (mummy, id, caption); } 

bool link_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (LINK_X, LINK_Y), wxSize (LINK_WIDTH, LINK_HEIGHT), LINK_STYLE)) return false;
    CreateControls ();
    return true; }

void link_t :: create_controls (wxWindow *parent)
{	grid_check_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 4, 0, 0));
    if (grid_check_ != nullptr)
    {	check_internal_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_internal, "Check links", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
        if (check_internal_ != nullptr)
        {	grid_check_ -> Add (check_internal_, 0, wxALIGN_RIGHT | wxALL, 5);
            check_external_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, check_external, "Externals", wxDefaultPosition, wxDefaultSize, 0));
            if (check_external_ != nullptr)
            {	grid_check_ -> Add (check_external_, 0, wxALL, 5);
                check_example_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Examples", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
                if (check_example_ != nullptr)
                {	grid_check_ -> Add (check_example_, 0, wxALIGN_RIGHT | wxALL, 5);
                    check_forwarded_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Fowards", wxDefaultPosition, wxDefaultSize, 0));
                    if (check_forwarded_ != nullptr)
                    {	grid_check_ -> Add (check_forwarded_, 0, wxALL, 5);
                        check_local_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Locals", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
                        if (check_local_ != nullptr)
                        {	grid_check_ -> Add (check_local_, 0, wxALIGN_RIGHT | wxALL, 5);
                            check_special_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Specials", wxDefaultPosition, wxDefaultSize, 0));
                            if (check_special_ != nullptr)
                            {	grid_check_ -> Add (check_special_, 0,wxALL, 5);
                                check_once_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Test once", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
                                if (check_once_ != nullptr)
                                {	grid_check_ -> Add (check_once_, 0,  wxALIGN_RIGHT | wxALL, 5);
                                    check_id_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "IDs", wxDefaultPosition, wxDefaultSize, 0));
                                    if (check_id_ != nullptr)
                                    {	grid_check_ -> Add (check_id_, 0,wxALL, 5); 
                                        check_revoke_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Revocation", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
                                        if (check_revoke_ != nullptr)
                                            grid_check_ -> Add (check_revoke_, 0,  wxALIGN_RIGHT | wxALL, 5);
                                            box_ -> Add (grid_check_, 0, wxEXPAND, 5); } } } } } } } } }
        
    required_.construct (parent, box_, "Required link/s:", "", false, true, true);

    grid_req_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 4, 0, 0));
    if (grid_req_ != nullptr)
    {   static_page_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Type:", wxDefaultPosition, wxDefaultSize, 0));
        if (static_page_ != nullptr)
        {	static_page_ -> Wrap (-1);
            grid_req_ -> Add (static_page_, 0, wxALIGN_CENTER_VERTICAL, 5);
            choice_page_ = GSL_OWNER (wxChoice) (new wxChoice (parent, choice_req_page, wxDefaultPosition, wxDefaultSize));
            if (choice_page_ != nullptr)
            {	for (::std::size_t n = 0; n < type_master < t_required_page > :: value_count (); ++n)
                    choice_page_ -> Append (type_master < t_required_page > :: name (static_cast < e_required_page > (n)));
                choice_page_ -> SetSelection (0);
                grid_req_ -> Add (choice_page_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
                static_lang_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Lang:", wxDefaultPosition, wxDefaultSize, 0));
                if (static_lang_ != nullptr)
                {	static_lang_ -> Wrap (-1);
                    grid_req_ -> Add (static_lang_, 0, wxALIGN_CENTER_VERTICAL, 5);
                    choice_lang_ = GSL_OWNER (wxChoice) (new wxChoice (parent, choice_req_lang, wxDefaultPosition, wxDefaultSize));
                    if (choice_lang_ != nullptr)
                    {	choice_lang_ -> Append ("*");
                        for (int n = 0; selection_lang [n] != nullptr; ++n)
                            choice_lang_ -> Append (selection_lang [n]);
                        choice_lang_ -> SetSelection (0);
                        grid_req_ -> Add (choice_lang_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
                        box_ -> Add (grid_req_, 0, wxALIGN_CENTER_HORIZONTAL, 5); } } } } }

    grid_desc_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));
    if (grid_desc_ != nullptr)
    {   static_from_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "From:", wxDefaultPosition, wxDefaultSize, 0));
        if (static_from_ != nullptr)
        {	static_from_ -> Wrap (-1);
            grid_desc_ -> Add (static_from_, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL, 5);
            choice_from_ = GSL_OWNER (wxChoice) (new wxChoice (parent, choice_req_from, wxDefaultPosition, wxDefaultSize));
            if (choice_from_ != nullptr)
            {	PRESUME (selection_count > 0, __FILE__, __LINE__);
                for (::std::size_t n = 0; n < selection_count; ++n)
                    choice_from_ -> Append (selection_version [n].nice_name ());
                choice_from_ -> SetSelection (0);
                grid_desc_ -> Add (choice_from_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
                static_to_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "To:", wxDefaultPosition, wxDefaultSize, 0));
                if (static_to_ != nullptr)
                {	static_to_ -> Wrap (-1);
                    grid_desc_ -> Add (static_to_, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL, 5);
                    choice_to_ = GSL_OWNER (wxChoice) (new wxChoice (parent, choice_req_to, wxDefaultPosition, wxDefaultSize));
                    if (choice_to_ != nullptr)
                    {	for (::std::size_t n = 0; n < selection_count; ++n)
                            choice_to_ -> Append (selection_version [n].nice_name ());
                        choice_to_ -> SetSelection (GSL_NARROW_CAST < int > (selection_count)-1);
                        grid_desc_ -> Add (choice_to_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
                                box_ -> Add (grid_desc_, 0, wxALIGN_CENTER_HORIZONTAL, 5); } } } } }

    static_desc_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Description:", wxDefaultPosition, wxDefaultSize, 0));
    if (static_desc_ != nullptr)
    {	static_desc_ -> Wrap (-1);
        box_ -> Add (static_desc_, 0, wxALL, 5);
        text_desc_ = GSL_OWNER (wxTextCtrl) (new wxTextCtrl (parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize ((LINK_WIDTH - 20), -1), 0));
        if (text_desc_ != nullptr)
        {	text_desc_ -> SetMinSize (wxSize ((LINK_WIDTH - 20), -1));
            box_ -> Add (text_desc_, 0, wxALL, 5); } }

    line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_ != nullptr)
        box_ -> Add (line_, 0, wxEXPAND | wxALL, 5); }

void link_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH); }

void link_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help (hp_lynx); }

void link_t :: OnAdd (wxCommandEvent& e)
{	required_.OnAdd (e); }

void link_t :: OnErase (wxCommandEvent& e)
{	required_.OnErase (e); }

void link_t :: OnExtension (wxCommandEvent& e)
{	required_.OnText (e); }

void link_t :: OnExternal (wxCommandEvent& )
{	if (invalid ()) return;
    const bool e = check_external_ -> IsChecked ();
    check_forwarded_ -> Enable (e);
    check_once_ -> Enable (e);
    check_revoke_ -> Enable (e); }

void link_t :: OnImpatience (wxCommandEvent& e)
{	required_.OnImpatience (e); }

void link_t :: OnInternal (wxCommandEvent& )
{	if (invalid ()) return;
    const bool e = check_internal_ -> IsChecked ();
    check_example_ -> Enable (e);
    check_id_ -> Enable (e);
    check_local_ -> Enable (e);
    check_special_ -> Enable (e);
    check_external_ -> Enable (e);
    const bool f = check_external_ -> IsChecked ();
    check_forwarded_ -> Enable (f && e);
    check_once_ -> Enable (f && e);
    check_revoke_ -> Enable (f && e); }

void link_t :: OnRename (wxCommandEvent& e)
{	required_.OnRename (e); }

void link_t :: OnTap (wxCommandEvent& e)
{	required_.OnTap (e); }

void link_t :: OnText (wxCommandEvent& e)
{	required_.OnText (e); }

bool link_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    check_example_ -> Set3StateValue (example_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_external_ -> Set3StateValue (external_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_forwarded_ -> Set3StateValue (forwarded_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_id_ -> Set3StateValue (id_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_internal_ -> Set3StateValue (internal_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_local_ -> Set3StateValue (local_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_once_ -> Set3StateValue (once_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    check_revoke_ -> Set3StateValue (revoke_ ? wxCHK_UNCHECKED : wxCHK_CHECKED); // note reversal
    check_special_ -> Set3StateValue (special_ ? wxCHK_CHECKED : wxCHK_UNCHECKED);
    return true; }

bool link_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
    example_ = check_example_ -> IsChecked ();
    external_ = check_external_ -> IsChecked ();
    forwarded_ = check_forwarded_ -> IsChecked ();
    id_ = check_id_ -> IsChecked ();
    internal_ = check_internal_ -> IsChecked ();
    local_ = check_local_ -> IsChecked ();
    once_ = check_once_ -> IsChecked ();
    revoke_ = ! check_revoke_ -> IsChecked ();
    special_ = check_special_ -> IsChecked ();
    return true; }

bool link_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

void link_t :: load_from_context (const context_t& c)
{	example (c.example ());
    external (c.external ());
    forwarded (c.forwarded ());
    id (c.crosslinks ());
    inter (c.links ());
    local (c.local ());
    once (c.once ());
    revoke (c.revoke ());
    special (c.special ()); }

void link_t :: save_to_context (context_t& c) const
{   c.example (example ());
    c.external (external ());
    c.forwarded (forwarded ());
    c.crosslinks (id ());
    c.links (inter ());
    c.local (local ());
    c.once (once ());
    c.revoke (revoke ());
    c.special (special ()); }

#endif // WX
