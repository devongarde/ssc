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
#include "main/args.h"
#include "gui/gui-app.h"
#include "gui/gui-nits.h"
#include "feedback/nitnames.h"
#include "type/type.h"

#define NIT_STYLE   DEF_STYLE
#define NIT_X       100
#define NIT_Y       100
#define NIT_WIT     400
#ifdef DEBUG
#define NIT_HIT     490
#else // DEBUG
#define NIT_HIT     450
#endif // DEBUG

BEGIN_EVENT_TABLE (nits_t, d1_t)
  EVT_BUTTON (wxID_HELP, nits_t::OnHelpClick)
  EVT_LISTBOX (list_level, nits_t::OnListLevel)
  EVT_RADIOBOX (radio_nits_level, nits_t::OnRadioLevel)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (nits_t, d1_t)

#define BASVRB "none", CATASTROPHE, ABHORRENT, WHOOPS, WARNING, INFORMATION, COMMENT, DBG
#define BASLVL  "default", CATASTROPHE, ABHORRENT, WHOOPS, WARNING, INFORMATION, COMMENT, DBG
#define DBGVL	VARIABLE, STRUCTURE2, DETAIL, SPLURGE, ALL
#define LSTLVL	SILENCE

#ifdef DEBUG
#define SELVRB	BASVRB, DBGVL
#define SELLVL	BASLVL, DBGVL, LSTLVL
#else // DEBUG
#define SELVRB	BASVRB
#define SELLVL	BASLVL, LSTLVL
#endif // DEBUG

const wxString vrb [] = { SELVRB };
const wxString lvl [] = { SELLVL };

nits_t :: nits_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (NIT_X, NIT_Y), wxSize (NIT_WIT, NIT_HIT))
{	Create (mummy, id, caption); } 

bool nits_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (NIT_X, NIT_Y), wxSize (NIT_WIT, NIT_HIT), NIT_STYLE)) return false;
    CreateControls ();
    return true; }

void nits_t :: create_controls (wxWindow *parent)
{	box_verbosity_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_verbosity_ != nullptr)
    {	static_verbosity_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Output verbosity:", wxDefaultPosition, wxDefaultSize, 0));
        if (static_verbosity_ != nullptr)
        {	static_verbosity_ -> Wrap (-1);
            box_verbosity_ -> Add (static_verbosity_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
            constexpr int count = sizeof (vrb) / sizeof (wxString);
            choice_verbosity_ = GSL_OWNER (wxChoice) (new wxChoice (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, count, vrb, 0));
            if (choice_verbosity_ != nullptr)
            {	choice_verbosity_ -> SetSelection (0);
                box_verbosity_ -> Add (choice_verbosity_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5); } }
        box_ -> Add (box_verbosity_, 0, wxALIGN_CENTER_HORIZONTAL, 5); }

    box_output_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_output_ != nullptr)
    {	static_output_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Output file format:", wxDefaultPosition, wxDefaultSize, 0));
        if (static_output_ != nullptr)
        {	static_output_ -> Wrap (-1);
            box_output_ -> Add (static_output_, 0, wxALIGN_CENTER_VERTICAL, 5);
            file_output_ = GSL_OWNER (wxFilePickerCtrl) (new wxFilePickerCtrl ( parent, wxID_ANY, wxEmptyString, "Select output template", "*.nit",
                                                                                wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE | wxFLP_FILE_MUST_EXIST | wxFLP_OPEN));
            if (file_output_ != nullptr)
                box_output_ -> Add (file_output_, 0, wxALL, 5); }
        box_ -> Add (box_output_, 0, wxALIGN_CENTER_HORIZONTAL, 5); }

    line1_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line1_ != nullptr) box_ -> Add (line1_, 0, wxEXPAND | wxALL, 5);

    list_level_ = GSL_OWNER (wxListBox) (new wxListBox (parent, list_level, wxDefaultPosition, wxDefaultSize, 0, NULL, wxVSCROLL));
    if (list_level_ != nullptr)
    {	for (int i = 1; i < nit_off; ++i)
        {	const ::std::string nn = lookup_name (static_cast < e_nit > (i));
            list_level_ -> Append (nn.c_str ()); }
        list_level_ ->  SetSelection (0);
        box_ -> Add (list_level_, 0, wxALL | wxEXPAND, 5);
        constexpr int count = sizeof (lvl) / sizeof (wxString);
        radio_level_ = GSL_OWNER (wxRadioBox) (new wxRadioBox (parent, radio_nits_level, "set nit level to", wxDefaultPosition, wxDefaultSize, count, lvl, 4, wxRA_SPECIFY_COLS));
        if (radio_level_ != nullptr)
        {	radio_level_ ->  SetSelection (0);
            box_ -> Add (radio_level_, 0, wxALL, 5); } }

    line2_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line2_ != nullptr) box_ -> Add (line2_, 0, wxEXPAND | wxALL, 5);

    box_options_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_options_ != nullptr)
    {	check_id_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Output nit IDs", wxDefaultPosition, wxDefaultSize, 0));
        if (check_id_ != nullptr)
        {	box_options_ -> Add (check_id_, 0, wxALL, 5);
            check_repeat_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (parent, wxID_ANY, "Do not repeat nits", wxDefaultPosition, wxDefaultSize, 0));
            if (check_repeat_ != nullptr)
            {	box_options_ -> Add (check_repeat_, 0, wxALL, 5);
                box_ -> Add (box_options_, 0, wxALIGN_CENTER_HORIZONTAL, 5); } } }

    line3_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line3_ != nullptr) box_ -> Add (line3_, 0, wxEXPAND | wxALL, 5); }

void nits_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH); }

void nits_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("nits"); }

void nits_t :: OnListLevel (wxCommandEvent& )
{	if (invalid ()) return;
    const int ll = list_level_ -> GetSelection ();
    if (ll == wxNOT_FOUND)
        radio_level_ -> Enable (false);
    else
    {	radio_level_ -> Enable (true);
        const e_nit nit = static_cast < e_nit > (ll + 1);
        const mns_t::const_iterator i = current_.find (nit);
        if (i == current_.cend ()) radio_level_ -> SetSelection (0);
        else radio_level_ -> SetSelection (i -> second); } }

void nits_t :: OnRadioLevel (wxCommandEvent& )
{	if (invalid ()) return;
    const int ll = list_level_ -> GetSelection ();
    const e_nit nit = static_cast < e_nit > (ll + 1);
    const int rl = radio_level_ -> GetSelection ();
    const e_severity s = static_cast < e_severity > (rl);
    PRESUME (rl != wxNOT_FOUND, __FILE__, __LINE__);
    const mns_t::const_iterator i = current_.find (nit);
    bool leave = (s == es_undefined);
    if (i != current_.cend ())
        if (i -> second == s) leave = true;
        else current_.erase (nit);
    if (! leave) current_.insert (mns_t::value_type (nit, s)); }

bool nits_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    check_id_ -> SetValue (id_);
    check_repeat_ -> SetValue (repeat_);
    file_output_ -> SetFileName (wxFileName (output_.string ().c_str ()));
    choice_verbosity_ -> SetSelection (verbosity_);
    current_ = stable_;
    const int ll = list_level_ -> GetSelection ();
    const e_nit nit = static_cast < e_nit > (ll + 1);
    const int rl = radio_level_ -> GetSelection ();
    const e_severity s = static_cast < e_severity > (rl);
    const mns_t::const_iterator i = current_.find (nit);
    if (i == current_.cend ())
    {	if (s != es_undefined) radio_level_ -> SetSelection (0); }
    else if (s != i -> second) radio_level_ -> SetSelection (i -> second);	
    return true; }

bool nits_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
    id_ = check_id_ -> GetValue ();
    repeat_ = check_repeat_ -> GetValue ();
    verbosity_ = static_cast < e_severity > (choice_verbosity_ -> GetSelection ());
    output_ = file_output_ -> GetFileName ().GetFullPath ().c_str ().AsChar ();
    stable_ = current_;	
    return true; }

bool nits_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

void nits_t :: load_from_context (const context_t& c)
{	id (c.nids ());
    repeat (c.nits_nits_nits ());
    severity (nitpick::mns ());
    verbosity (c.verbose ()); }

void nits_t :: save_to_context (context_t& c) const
{   c.nids (id ());
    c.nits_nits_nits (repeat ());
    c.verbose (verbosity ());
    nitpick::mns (severity ()); }

#endif // WX
