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
#include <wx/fdrepdlg.h>
#include "main/output.h"
#include "utility/common.h"
#include "gui/gui-app.h"
#include "gui/gui-output.h"
#include "url/url_sanitise.h"

BEGIN_EVENT_TABLE (output_t, wxTextCtrl)
    EVT_TEXT (text_output, output_t::OnUpdate)
    EVT_MENU (wxID_COPY, output_t::OnCopy)
    EVT_MENU (wxID_HELP, output_t::OnHelp)
    EVT_MENU (wxID_SELECTALL, output_t::OnSelectAll)
    EVT_UPDATE_UI (wxID_COPY, output_t::OnUpdateCopy)
    EVT_UPDATE_UI (wxID_SELECTALL, output_t::OnUpdateSelectAll)
END_EVENT_TABLE ()

#define NO_IDEA_WHY_THIS_OFFSET_IS_NECESSARY    4

constexpr bool not_in_word (const char ch)
{   return (((ch < '0') || (ch > '9')) &&
            ((ch < 'A') || (ch > 'Z')) &&
            ((ch < 'a') || (ch > 'z'))); }

bool is_word (const ::std::string& con, const ::std::size_t f, const ::std::size_t m)
{   if (f > 0) if (! not_in_word (con.at (f-1))) return false;
    const ::std::size_t n = f+m+1;
    if (n >= con.length ()) return true;
    return not_in_word (con.at (n)); }

output_t::output_t (wxWindow *mummy)
    : wxTextCtrl (mummy, text_output, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxTE_MULTILINE | wxTE_READONLY | wxTE_DONTWRAP | wxTE_LEFT | wxTE_RICH | wxTE_RICH2)
{   VERIFY_NOT_NULL (mummy, __FILE__, __LINE__); } 

void output_t::append (const ::std::string& text)
{   if (text.length () > 0)
    {   PRESUME (text.length () < ULONG_MAX, __FILE__, __LINE__);
        const unsigned long l = GSL_NARROW_CAST < unsigned long > (text.length ()) + NO_IDEA_WHY_THIS_OFFSET_IS_NECESSARY;
        if (ULONG_MAX > text.length () + NO_IDEA_WHY_THIS_OFFSET_IS_NECESSARY + GSL_NARROW_CAST < ::std::size_t > (max_))
            max_ += l;
        else clear ();
        SetMaxLength (GSL_NARROW_CAST < unsigned long > (max_));
        AppendText (text.c_str ());
        CanCopy (); } }

void output_t::clear ()
{   RemoveSelection ();
    Clear ();
    max_ = 1; }

::std::string output_t::pre () const
{   ::std::string res = "<PRE>\n";
    res += enhtml (static_cast < ::std::string > (GetValue ().c_str ()));
    res += "</PRE>\n";
    return res; }

bool output_t::save_file (frame_t* frame)
{   if (frame == nullptr) return false;
    nitpick nits;
    if (write_text_file (nits, file_, ::std::string (GetValue ().c_str ()))) return true;
    ::std::string msg ("save to ");
    msg += file_.string ();
    msg += " failed";
    frame -> status (msg);
    return false; }

void output_t :: Find (const ::std::string& wot, const int fussitudes)
{   fussitudes_ = fussitudes;
    found_ = 0;
    if ((fussitudes_ & wxFR_MATCHCASE) == wxFR_MATCHCASE) find_ = wot;
    find_ = ::boost::to_lower_copy (wot);
    if ((fussitudes_ & wxFR_DOWN) == wxFR_DOWN) Next ();
    else Prior (); } 

::std::string output_t :: presearch ()
{   if ((fussitudes_ & wxFR_MATCHCASE) == wxFR_MATCHCASE) return ::std::string (GetValue ().c_str ());
    return ::boost::to_lower_copy (::std::string (GetValue ().c_str ())); }

void output_t :: Next ()
{   ::std::string con (presearch ());
    if (con.empty ()) return;
    if (GSL_NARROW_CAST < ::std::size_t > (GetInsertionPoint ()) >= con.length ()) SetInsertionPoint (0);
    ::std::size_t f = found_;
    constexpr ::std::size_t cycle = 0;
    for (;;)
    {   ::std::size_t start = 0;
        if (f == con.length () - 1) start = cycle; 
        else start = f + 1;
        f = con.find (find_, start);
        if (f == ::std::string::npos)
        {   if (start == cycle) return;
            f = con.find (find_, cycle);
            if (f == ::std::string::npos) return; }
        if (f == found_) break;
        if ((fussitudes_ & wxFR_WHOLEWORD) == 0) break;
        if (is_word (con, f, find_.length ())) break; }
    SetSelection (GSL_NARROW_CAST < unsigned long > (f), GSL_NARROW_CAST < unsigned long > (f + find_.length ()));
    ShowPosition (GSL_NARROW_CAST < unsigned long > (f));
    found_ = f; }

void output_t :: Prior ()
{   ::std::string con (presearch ());
    if (con.empty ()) return;
    if (GSL_NARROW_CAST < ::std::size_t > (GetInsertionPoint ()) >= con.length ()) SetInsertionPoint (0);
    ::std::size_t f = found_;
    const ::std::size_t cycle = con.length () - 1;
    for (;;)
    {   ::std::size_t start = 0;
        if (f == 0) start = cycle; 
        else start = f - 1;
        f = con.rfind (find_, start);
        if (f == ::std::string::npos)
        {   if (start == cycle) return;
            f = con.rfind (find_, cycle);
            if (f == ::std::string::npos) return; }
        if (f == found_) break;
        if ((fussitudes_ & wxFR_WHOLEWORD) == 0) break;
        if (is_word (con, f, find_.length ())) break; }
    SetSelection (GSL_NARROW_CAST < unsigned long > (f), GSL_NARROW_CAST < unsigned long > (f + find_.length ()));
    ShowPosition (GSL_NARROW_CAST < unsigned long > (f));
    found_ = f; }

void output_t :: OnUpdate (wxCommandEvent& e)
{   e.Skip (); }

void output_t :: OnCopy (wxCommandEvent& )
{   Copy (); }

void output_t :: FileSave (frame_t* frame)
{   if (frame != nullptr)
        if (file_.string ().empty ()) FileSaveAs (frame);
        else save_file (frame); }

void output_t :: FileSaveAs (frame_t* frame)
{   if (frame == nullptr) return;
    wxFileDialog dialogue (frame, "Write Log",
        wxEmptyString, "output.txt", "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialogue.ShowModal () == wxID_OK)
    {   file_ = ::std::string (dialogue.GetPath ().c_str ());
        save_file (frame); } }

void output_t :: OnHelp (wxCommandEvent& e)
{   if (app != nullptr) app -> display_contents ();
    e.Skip (); }

void output_t :: Preview (wxHtmlEasyPrinting* print)
{   if (print != nullptr) print -> PreviewText (pre ().c_str ()); }

void output_t :: Print (wxHtmlEasyPrinting* print)
{   if (print != nullptr) print -> PrintText (pre ().c_str ()); }

void output_t :: OnSelectAll (wxCommandEvent& )
{   SetSelection (-1, -1); }

void output_t :: OnUpdateCopy (wxUpdateUIEvent& event)
{   event.Enable (CanCopy ()); }

void output_t :: OnUpdateSelectAll (wxUpdateUIEvent& event)
{   event.Enable (GetLastPosition () > 0); }

#endif // WX
