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
#include "gui/gui-dialogue.h"
#include "gui/gui-listedit.h"

bool listedit_manager :: concoct (wxWindow* parent, wxBoxSizer* box, const char* desc, const char* def, bool file, bool comma, bool line)
{	VERIFY_NOT_NULL (parent, __FILE__, __LINE__);
    VERIFY_NOT_NULL (box, __FILE__, __LINE__); 
    VERIFY_NOT_NULL (desc, __FILE__, __LINE__);
    const wxSize butt (30, -1);
    const ::std::string d ((def == nullptr) ? "" : def);
    has_file_ = file;
    has_text_ = comma || ! has_file_;
    if (line) l_.concoct < wxBoxSizer > (parent, box);
    if (    ext_.concoct < wxBoxSizer > (parent, box) &&
            bloc_.concoct < wxBoxSizer > (parent, ext_.box_, wxALIGN_CENTRE_VERTICAL, wxVERTICAL, 1) &&
            label_.concoct < wxBoxSizer > (parent, bloc_.box_, desc, wxALL) && 
            file_text_.concoct < wxBoxSizer > (parent, bloc_.box_, wxALIGN_CENTRE_HORIZONTAL) &&
            ((! has_file_) || file_.concoct < wxBoxSizer > (parent, file_text_.box_, file_id_, d, 
                                                            "Select a file", "*.*", wxFLP_DEFAULT_STYLE | wxFLP_FILE_MUST_EXIST | wxFLP_OPEN, wxALL)) &&
            ((! has_text_) || t_.concoct < wxBoxSizer > (parent, file_text_.box_, text_id_, d, 150)) &&
            but_.concoct < wxBoxSizer > (parent, bloc_.box_) &&
            add_.concoct < wxBoxSizer > (parent, but_.box_, add_id_, ADD_TEXT, butt) &&
            del_.concoct < wxBoxSizer > (parent, but_.box_, erase_id_, REMOVE_TEXT, butt) &&
            ren_.concoct < wxBoxSizer > (parent, but_.box_, rename_id_, RENAME_TEXT, butt) &&
            list_.concoct < wxBoxSizer > (parent, ext_.box_, list_id_, vstr_t (), -1, 100))
    {   if (! d.empty ()) list_.append (d);
        fex ();
        return true; }
    return false; }

::std::string listedit_manager :: tiswot ()
{	PRESUME ((! has_file_) || (! file_.invalid ()), __FILE__, __LINE__);
    PRESUME ((! has_text_) || (! t_.invalid ()), __FILE__, __LINE__);
    ::std::string f, s, r;
    if (has_text_)
    {	t_.TransferDataFromWindow ();
        s = t_.value ();
        if (! has_file_) r = s; }
    if (has_file_)
    {	file_.TransferDataFromWindow ();
        f = ::boost::filesystem::absolute (file_.value ()).string ();
        if (! f.empty ()) 
            if (s.empty ()) r = f;
            else r = f + "," + s; }
    return r; }

void listedit_manager :: OnAdd (wxCommandEvent& )
{	if (invalid ()) return;
    const ::std::string s (tiswot ());
    if (! s.empty ())
    {   int n = list_.find (s);
        if (n == wxNOT_FOUND)
        {	list_.append (s);
            n = list_.find (s); }
        list_.select (n);
        list_.scroll (n);
        fex (); } }

void listedit_manager :: OnErase (wxCommandEvent& )
{	if (invalid ()) return;
    const int l = list_.selected ();
    if (l != wxNOT_FOUND)
    {	::std::string s (list_.value (l));
        list_.erase (l);
        t_.value (s);
        fex (); } }

void listedit_manager :: OnRename (wxCommandEvent& )
{	if (invalid ()) return;
    const ::std::string s (tiswot ());
    if (! s.empty ())
    {   int n = list_.find (s);
        if (n == wxNOT_FOUND)
        {	const int l = list_.selected ();
            if (l != wxNOT_FOUND)
            {	list_.erase (l);
                list_.append (s);
                n = list_.find (s);
                list_.select (n);
                list_.scroll (n);
                fex (); } } } }

void listedit_manager :: OnTap (wxCommandEvent& e)
{	if (invalid ()) return;
    const int l = list_.selected ();
    del_.enable (l != wxNOT_FOUND);
    OnText (e); }

bool listedit_manager :: TransferDataToWindow ()
{   if (invalid ()) return false;
    return (((! has_file_) || file_.TransferDataToWindow ()) &&
            ((! has_text_) || t_.TransferDataToWindow ()) &&
            list_.TransferDataToWindow ()); }

bool listedit_manager :: TransferDataFromWindow ()
{   if (invalid ()) return false;
    return (((! has_file_) || file_.TransferDataFromWindow ()) &&
            ((! has_text_) || t_.TransferDataFromWindow ()) &&
            list_.TransferDataFromWindow ()); }

bool listedit_manager :: able_enable ()
{	if (invalid ()) return false;
    const ::std::string r (tiswot ());
    if (r.empty ()) return false;
    return (list_.find (r) == wxNOT_FOUND); }

void listedit_manager :: fex ()
{	PRESUME ((! has_file_) || (! file_.invalid ()), __FILE__, __LINE__);
    PRESUME ((! has_text_) || (! t_.invalid ()), __FILE__, __LINE__);
    if (invalid ()) return;
    const int l = list_.selected ();
    del_.enable (l != wxNOT_FOUND);
    const ::std::string r (tiswot ());
    if (r.empty ())
    {	add_.enable (false);
        ren_.enable (false); }
    else
    {	const int n = list_.find (r);
        add_.enable (n == wxNOT_FOUND);
        ren_.enable ((l != wxNOT_FOUND) && ((l != n) || (n == wxNOT_FOUND))); } }

bool listedit_manager :: invalid () const noexcept
{   if (has_file_ && file_.invalid ()) return true;
    if (has_text_ && t_.invalid ()) return true;
    return list_.invalid (); }

void listedit_manager :: OnText (wxCommandEvent& )
{	fex (); }

void listedit_manager :: OnFile (wxFileDirPickerEvent& )
{	fex (); }

void listedit_manager :: OnImpatience (wxCommandEvent& )
{	fex (); }

void listedit_manager :: enable (const bool e)
{	if (invalid ()) return;
    add_.enable (e);	
    del_.enable (e);	
    list_.enable (e);	
    ren_.enable (e);
    label_.enable (e);
    if (has_file_) file_.enable (e);	
    if (has_text_) t_.enable (e);	
    if (e) fex (); }

vstr_t listedit_manager :: acquire () const
{	if (invalid ()) return vstr_t ();
    vstr_t res;
    const unsigned int nx = list_.count ();
    for (unsigned int i = 0; i < nx; ++i)
        res.push_back (list_.value (i));
    return res; }

void listedit_manager :: value (const ::std::string& s, const ::std::string& t)
{   if (has_text_ && has_file_)
    {   t_.value (s);
        file_.value (t); }
    else if (has_text_) t_.value (s);
    else file_.value (s); }
#endif // WX
