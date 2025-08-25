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
#include "gui/gui-site.h"
#include "utility/filesystem.h"
#include "type/type.h"

#define SITE_STYLE   DEF_STYLE
#define SITE_X       100
#define SITE_Y       100
#define SITE_WIDTH   430
#define SITE_HEIGHT  360

BEGIN_EVENT_TABLE (site_t, d1_t)
  EVT_BUTTON (wxID_HELP, site_t::OnHelpClick)
  EVT_BUTTON (button_site_add, site_t::OnAdd)
  EVT_BUTTON (button_site_erase, site_t::OnErase)
  EVT_BUTTON (button_site_rename, site_t::OnRename)
  EVT_TEXT (button_site_rename, site_t::OnTap)
  EVT_TEXT (text_site_ext, site_t::OnText)
  EVT_LISTBOX (button_site_rename, site_t::OnExtension)
  EVT_LISTBOX_DCLICK (button_site_rename, site_t::OnImpatience)
  EVT_CHECKBOX (check_account, site_t::OnAccount)
  EVT_CHECKBOX (check_username, site_t::OnUsername)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (site_t, d1_t)

site_t :: site_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (SITE_X, SITE_Y), wxSize (SITE_WIDTH, SITE_HEIGHT))
{	Create (mummy, id, caption); } 

bool site_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (SITE_X, SITE_Y), wxSize (SITE_WIDTH, SITE_HEIGHT), SITE_STYLE)) return false;
    CreateControls ();
    return true; }

void site_t :: create_controls (wxWindow *parent)
{	if (default_.concoct (parent, box_, wxID_ANY, def_, "Default root " REPERTOIRE ": ") &&
        domain_.construct (parent, box_, "Site domain/s:") &&
        mid_.concoct (parent, box_) &&
        account_.concoct (parent, box_, check_account, "Name the actual account used to run " PROG, "False account: ") &&
        username_.concoct (parent, box_, check_username, "Name the actual user running " PROG, "False username: ") &&
        line_.concoct (parent, box_) &&
        description_.concoct (parent, box_, wxID_ANY, "Report description: ") &&
        relative_.concoct (parent, box_, wxID_ANY, "Report relative paths", wxALL | wxALIGN_CENTRE_HORIZONTAL) &&
        base_.concoct (parent, box_))
    {   account_.select (acc_.empty ());
        username_.select (user_.empty ()); } }

void site_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH); }

void site_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help (hp_general); }

void site_t :: OnAccount (wxCommandEvent& )
{	account_.click (); }

void site_t :: OnAdd (wxCommandEvent& e)
{	domain_.OnAdd (e); }

void site_t :: OnErase (wxCommandEvent& e)
{	domain_.OnErase (e); }

void site_t :: OnExtension (wxCommandEvent& e)
{	domain_.OnText (e); }

void site_t :: OnImpatience (wxCommandEvent& e)
{	domain_.OnImpatience (e); }

void site_t :: OnRename (wxCommandEvent& e)
{	domain_.OnRename (e); }

void site_t :: OnTap (wxCommandEvent& e)
{	domain_.OnTap (e); }

void site_t :: OnText (wxCommandEvent& e)
{	domain_.OnText (e); }

void site_t :: OnUsername (wxCommandEvent& )
{	username_.click (); }

bool site_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    if (def_.empty ()) def_ = get_working_directory ();
    default_.value (def_);
    domain_.preload (stov (site_));
    account_.value (acc_);
    description_.value (desc_);
    username_.value (user_);
    return true; }

bool site_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
    def_ = default_.value ();
    site_ = vtos (domain_.acquire ());
    absolute_ = ! relative_.selected ();
    acc_ = account_.value ();
    desc_ = description_.value ();
    user_ = username_.value ();
    return true; }

bool site_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

void site_t :: load_from_context (const context_t& c)
{	site (c.site ());
    def (c.rootp ());
    absolute_ = c.absolute_path ();
    acc_ = c.account ();
    for (auto s : c.output_description ())
        desc_ += s;
    user_ = c.username (); }

void site_t :: save_to_context (context_t& c) const
{   c.site (site ());
    c.root (def ().string ());
    c.absolute_path (absolute_);
    c.account (acc_);
    vstr_t vs;
    vs.push_back (desc_);
    c.output_description (vs);
    c.username (user_); }

#endif // WX
