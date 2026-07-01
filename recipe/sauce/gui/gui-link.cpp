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
  EVT_LISTBOX (list_req_ext, link_t::OnExtension)
  EVT_CHECKBOX (check_external, link_t::OnExternal)
  EVT_LISTBOX_DCLICK (list_req_ext, link_t::OnImpatience)
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
{	vstr_t type_vals;
    for (::std::size_t n = 0; n < type_master < t_required_page > :: value_count (); ++n)
        type_vals.push_back (type_master < t_required_page > :: name (static_cast < e_required_page > (n)));
    if (    check_grid_.concoct < wxBoxSizer > (parent, box_, 4) &&
            internal_check_.concoct (parent, check_grid_.box_, check_internal, "Check links") &&
            example_check_.concoct (parent, check_grid_.box_, wxID_ANY, "Examples") &&
            local_check_.concoct (parent, check_grid_.box_, wxID_ANY, "Locals") &&
            special_check_.concoct (parent, check_grid_.box_, wxID_ANY, "Specials") &&
            id_check_.concoct (parent, check_grid_.box_, wxID_ANY, "IDs") &&
            external_check_.concoct (parent, check_grid_.box_, check_external, "Externals") &&
            forwarded_check_.concoct (parent, check_grid_.box_, wxID_ANY, "Forwards") &&
            once_check_.concoct (parent, check_grid_.box_, wxID_ANY, "Test once") &&
            revoke_check_.concoct (parent, check_grid_.box_, wxID_ANY, "Revocation") &&
            required_.concoct (parent, box_, "Required link/s:", "", false, true, true) &&
            type_choice_.concoct < wxBoxSizer > (parent, box_, choice_req_page, "Type:", type_vals, 0) &&
            lingo_.concoct < wxBoxSizer > (parent, box_, context.html_ver (), choice_req_lang, "Lang:", 0, true) &&
            from_html_.concoct < wxBoxSizer > (parent, box_, choice_req_from, "From:", 0) &&
            to_html_.concoct < wxBoxSizer > (parent, box_, choice_req_to, "To:") &&
            element_choice_.concoct < wxBoxSizer > (parent, box_, choice_req_element, "Element:", 0) &&
            desc_text_.concoct (parent, box_, wxID_ANY, "Description:"))
        l_.concoct < wxBoxSizer > (parent, box_); }

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
{   required_.OnAdd (e);
    TransferDataFromWindow ();
    required_t req = gather_require (sel_);
    if (! required_.value ().empty ())
        vreq_.push_back (req); }

void link_t :: OnErase (wxCommandEvent& e)
{	sel_ = required_.selected ();
    const int sz = GSL_NARROW_CAST < int > (vreq_.size ());
    if ((sel_ >= 0) && (sel_ < sz))
    {   req_vt ffs;
        for (int i = 0; i < sz; ++i)
            if (i != sel_) ffs.push_back (vreq_.at (i));
        vreq_.swap (ffs); }
    required_.OnErase (e);
    fill_require (0); }

void link_t :: OnExtension (wxCommandEvent& e)
{	required_.OnText (e);
    select_require (required_.selected ()); }

void link_t :: select_require (const int sel)
{   const int sz = GSL_NARROW_CAST < int > (vreq_.size ());
    if ((sel < 0) || (sel >= sz)) return;
    auto req = vreq_.at (sel);
    wxMessageBox (req.rpt ());
    desc_text_.value (req.desc_);
    from_html_.select (which_standard (req.from_));
    element_choice_.select (req.e_);
    lingo_.select (req.lang_);
    to_html_.select (which_standard (req.to_));
    type_choice_.select (req.rq_); }

required_t link_t :: gather_require (int& )
{   required_t res, yuk;
    res.desc_ = desc_text_.value ();
    res.from_ = standard_html_ver.at (from_html_.selected ());
    res.e_ = element_choice_.selected ();
    res.lang_ = GSL_NARROW_CAST < e_lang > (lingo_.selected ());
    res.to_ = standard_html_ver.at (to_html_.selected ());
    res.rq_ = GSL_NARROW_CAST < e_required_page > (type_choice_.selected ());
    nitpick nits;
    res.url_ = url (nits, res.to_, required_.value ());
    wxMessageBox (res.rpt ());
    if ((res.to_ < res.from_) || (nits.worst () <= es_error) || required_.value ().empty ())
        return yuk;
    return res; }

void link_t :: fill_require (const int sel)
{   vstr_t con;
    for (auto req : vreq_)
        con.push_back (req.url_.get ());
    required_.preload < vstr_t > (con);
    select_require (sel); }  

void link_t :: externaliser ()
{   if (invalid ()) return;
    const bool e = external_check_.selected ();
    forwarded_check_.enable (e);
    once_check_.enable (e);
    revoke_check_.enable (e); }

void link_t :: internaliser ()
{	if (invalid ()) return;
    const bool e = internal_check_.selected ();
    example_check_.enable (e);
    id_check_.enable (e);
    local_check_.enable (e);
    special_check_.enable (e);
    external_check_.enable (e);
    externaliser (); }

void link_t :: OnExternal (wxCommandEvent& )
{	externaliser (); }

void link_t :: OnImpatience (wxCommandEvent& e)
{	required_.OnImpatience (e);
    select_require (required_.selected ()); }

void link_t :: OnInternal (wxCommandEvent& )
{	internaliser (); }

void link_t :: OnRename (wxCommandEvent& e)
{	required_.OnRename (e); }

void link_t :: OnTap (wxCommandEvent& e)
{	//const int sz = GSL_NARROW_CAST < int > (vreq_.size ());
    required_.OnTap (e);
    sel_ = required_.selected ();
    select_require (sel_); }

void link_t :: OnText (wxCommandEvent& e)
{	required_.OnText (e); }

bool link_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    example_check_.select (example_);
    external_check_.select (external_);
    forwarded_check_.select (forwarded_);
    id_check_.select (id_);
    internal_check_.select (internal_);
    local_check_.select (local_);
    once_check_.select (once_);
    revoke_check_.select (revoke_);
    special_check_.select (special_);
    internaliser ();
    select_require (sel_);
    desc_text_.TransferDataToWindow ();
    element_choice_.TransferDataToWindow ();
    from_html_.TransferDataToWindow ();
    lingo_.TransferDataToWindow ();
    to_html_.TransferDataToWindow ();
    type_choice_.TransferDataToWindow ();
    return true; }

bool link_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
    example_ = example_check_.selected ();
    external_ = external_check_.selected ();
    forwarded_ = forwarded_check_.selected ();
    id_ = id_check_.selected ();
    internal_ = internal_check_.selected ();
    local_ = local_check_.selected ();
    once_ = once_check_.selected ();
    revoke_ = revoke_check_.selected ();
    special_ = special_check_.selected ();
    desc_text_.TransferDataFromWindow ();
    element_choice_.TransferDataFromWindow ();
    from_html_.TransferDataFromWindow ();
    lingo_.TransferDataFromWindow ();
    to_html_.TransferDataFromWindow ();
    type_choice_.TransferDataFromWindow ();
    sanitise ();
    return true; }

void link_t :: sanitise ()
{   if (from_html_.selected () > to_html_.selected ())
    {   const int f = from_html_.selected ();
        from_html_.select (to_html_.selected ());
        to_html_.select (f);
        TransferDataToWindow (); } }

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
{	def_lang_ = c.lang ();
    example (c.example ());
    external (c.external ());
    forwarded (c.forwarded ());
    id (c.crosslinks ());
    inter (c.links ());
    local (c.local ());
    once (c.once ());
    required () = c.required ();
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
    c.required () = required ();
    c.revoke (revoke ());
    c.special (special ()); }
#endif // WX
