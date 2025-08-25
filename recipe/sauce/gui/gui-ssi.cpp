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
#include "type/type.h"
#include "gui/gui-app.h"
#include "gui/gui-stats.h"

#define SSI_STYLE   DEF_STYLE
#define SSI_X       100
#define SSI_Y       100
#define SSI_WIDTH   600
#define SSI_HEIGHT  425

BEGIN_EVENT_TABLE (ssi_t, d1_t)
  EVT_CHECKBOX (check_ssi_lastmod, ssi_t::OnLastMod)
  EVT_CHECKBOX (check_ssi_now, ssi_t::OnNow)
  EVT_CHECKBOX (check_ssi_process, ssi_t::OnProcess)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (ssi_t, d1_t)

ssi_t :: ssi_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (SSI_X, SSI_Y), wxSize (SSI_WIDTH, SSI_HEIGHT))
{	Create (mummy, id, caption); } 

bool ssi_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (SSI_X, SSI_Y), wxSize (SSI_WIDTH, SSI_HEIGHT), SSI_STYLE)) return false;
    CreateControls ();
    return true; }

void ssi_t :: create_controls (wxWindow *parent)
{	process_.concoct (parent, box_, check_ssi_process, "Process Server Side Includes");

    if (args_.concoct (parent, box_, wxID_ANY, "DOCUMENT_ARGS: "))
        if (echomsg_.concoct (parent, box_, wxID_ANY, "echomsg: "))
            if (errmsg_.concoct (parent, box_, wxID_ANY, "errmsg: "))
                if (query_.concoct (parent, box_, wxID_ANY, "QUERY_STRING_UNESCAPED: "))
                    if (timefmt_.concoct (parent, box_, wxID_ANY, "TIMEFMT: "))
                        if (user_.concoct (parent, box_, wxID_ANY, "USER_NAME: "))
                            text_line_.concoct (parent, box_);

    if (exec_.concoct (parent, box_, check_ssi_exec, "Run <!--#exec ... -->", "Or say: "))
        exec_line_.concoct (parent, box_); 

    if (lastmod_.concoct (parent, box_, check_ssi_lastmod, "Last Modification Time:"))
        now_.concoct (parent, box_, check_ssi_now, "'Current' Time: ");  }

void ssi_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    PRESUME (invalid (), __FILE__, __LINE__);
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH);  }

void ssi_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help (hp_ssi); }

void ssi_t :: OnExec (wxCommandEvent& )
{	if (invalid ()) return;
    exec_.click (); }

void ssi_t :: OnLastMod (wxCommandEvent& )
{	if (invalid ()) return;
    lastmod_.click (); }

void ssi_t :: OnNow (wxCommandEvent& )
{	if (invalid ()) return;
    now_.click (); }

void ssi_t :: OnProcess (wxCommandEvent& )
{	if (invalid ()) return;
    const bool b = process_.selected ();
    args_.enable (b);
    echomsg_.enable (b);
    errmsg_.enable (b);
    lastmod_.enable (b);
    now_.enable (b);
    exec_.enable (b);
    query_.enable (b);
    timefmt_.enable (b);
    user_.enable (b); }

bool ssi_t :: TransferDataToWindow ()
{	return	now_.TransferDataToWindow () &&
            lastmod_.TransferDataToWindow () &&
            process_.TransferDataToWindow () &&
            exec_.TransferDataToWindow () &&
            args_.TransferDataToWindow () &&
            echomsg_.TransferDataToWindow () &&
            errmsg_.TransferDataToWindow () &&
            query_.TransferDataToWindow () &&
            timefmt_.TransferDataToWindow () &&
            user_.TransferDataToWindow (); }

bool ssi_t :: TransferDataFromWindow ()
{	return	now_.TransferDataFromWindow () &&
            lastmod_.TransferDataFromWindow () &&
            process_.TransferDataFromWindow () &&
            exec_.TransferDataFromWindow () &&
            args_.TransferDataFromWindow () &&
            echomsg_.TransferDataFromWindow () &&
            errmsg_.TransferDataFromWindow () &&
            query_.TransferDataFromWindow () &&
            timefmt_.TransferDataFromWindow () &&
            user_.TransferDataFromWindow (); }

bool ssi_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

void ssi_t :: load_from_context (const context_t& c)
{	if (invalid ()) return;	
    process_.check_.set_ = c.ssi ();
    lastmod_.datetime_.datetime_ = c.ssi_lastmod ();
    lastmod_.check_.set_ = (c.ssi_lastmod () == 0);
    now_.datetime_.datetime_ = c.ssi_date ();
    now_.check_.set_ = (c.ssi_date () == 0);
    exec_.check_.set_ = c.ssi_exec_run ();
    exec_.text_.value_ = c.ssi_exec_text ();
    args_.text_.value_ = c.ssi_doc_args ();
    echomsg_.text_.value_ = c.ssi_echomsg ();
    errmsg_.text_.value_ = c.ssi_errmsg ();
    query_.text_.value_ = c.ssi_query_string ();
    timefmt_.text_.value_ = c.ssi_timefmt ();
    user_.text_.value_ = c.ssi_user_name (); }

void ssi_t :: save_to_context (nitpick& nits, context_t& c) const
{	if (invalid ()) return;	
    c.ssi (process_.check_.set_);
    if (lastmod_.check_.set_) c.ssi_lastmod (lastmod_.datetime_.datetime_);
    else c.ssi_lastmod (0);
    if (now_.check_.set_) c.ssi_date (now_.datetime_.datetime_);
    else c.ssi_date (0);
    c.ssi_exec_run (exec_.check_.set_);
    c.ssi_exec_text (nits, exec_.text_.value_);
    c.ssi_doc_args (nits, args_.text_.value_);
    c.ssi_echomsg (nits, echomsg_.text_.value_);
    c.ssi_errmsg (nits, errmsg_.text_.value_);
    c.ssi_query_string (nits, query_.text_.value_);
    c.ssi_timefmt (nits, timefmt_.text_.value_);
    c.ssi_user_name (nits, user_.text_.value_); }

#endif // WX
