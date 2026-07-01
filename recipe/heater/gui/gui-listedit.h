/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include "gui/gui-ctrl.h"

#ifdef WX
#define ADD_TEXT    "&add"
#define REMOVE_TEXT "&del"
#define RENAME_TEXT "&ren"

class listedit_manager
{   box_t ext_, bloc_, but_, file_text_;
    button_t add_, del_, ren_;
    filepick_t file_;
    label_t label_;
    line_t l_;
    list_t list_;
    text_t t_;
    int add_id_ = -1, erase_id_ = -1, file_id_ = -1, list_id_ = -1, rename_id_ = -1, text_id_ = -1;
    bool has_file_ = false, has_text_ = true;
    void fex ();
    ::std::string tiswot ();
public:
    listedit_manager () = default;
    listedit_manager (  const int add_id, const int erase_id, const int rename_id,
                        const int file_id, const int list_id, const int text_id) noexcept
        : add_id_ (add_id), erase_id_ (erase_id), file_id_ (file_id), list_id_ (list_id), rename_id_ (rename_id), text_id_ (text_id)
    { }
    listedit_manager (const listedit_manager& l) = default;
    listedit_manager (listedit_manager&& l) = default;
    ~listedit_manager () = default;
    listedit_manager& operator = (const listedit_manager& l) = default;
    listedit_manager& operator = (listedit_manager&& l) = default;
    void OnAdd (wxCommandEvent& event);
    void OnErase (wxCommandEvent& event);
    void OnFile (wxFileDirPickerEvent& event);
    void OnRename (wxCommandEvent& event);
    void OnText (wxCommandEvent& event);
    void OnTap (wxCommandEvent& event);
    void OnImpatience (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool able_enable ();
    bool concoct (wxWindow* parent, wxBoxSizer* box, const char* desc, const char* def = nullptr, bool file = false, bool comma = false, bool line = false);
    void enable (const bool e);
    bool invalid () const noexcept; 
    int selected () const
    {	if (invalid ()) return -1;
        return list_.selected (); }
    void select (const int n)
    {   list_.select (n); }
    ::std::string value ()
    {   return tiswot (); }
    ::std::string value (const int n) const
    {   return list_.value (n); }
    void value (const ::std::string& s, const ::std::string& t = ::std::string ());
    int count () const
    {   return list_.count (); }
    ::std::size_t size () const
    {   if (invalid ()) return 0;
        return list_.count (); }
    vstr_t acquire () const;
    template < class T > inline void acquire (T& s)
    {	if (list_.invalid ()) return;
        TransferDataFromWindow ();
        s.clear ();
        const unsigned int nx = list_.count ();
        for (unsigned int i = 0; i < nx; ++i)
            s.emplace (list_.value (i)); }
    template < > inline void acquire < vstr_t > (vstr_t& s)
    {	if (list_.invalid ()) return;
        TransferDataFromWindow ();
        s.clear ();
        const unsigned int nx = list_.count ();
        for (unsigned int i = 0; i < nx; ++i)
            s.push_back (list_.value (i)); }
    template < class VT > void preload (const VT& vs)
    {	if (list_.invalid ()) return;
        list_.clear ();
        for (auto s : vs) list_.append (s);
        TransferDataToWindow ();
        fex (); }
    template < class VT > VT unload ()
    {	PRESUME (! list_.invalid (), __FILE__, __LINE__);
        VT res;
        TransferDataFromWindow ();
        const unsigned int m = list_.count ();
        for (unsigned int u = 0; u < m; ++u)
            res.push_back (typename VT::value_type (list_.value (u)));
        return res; } };
#endif // WX
