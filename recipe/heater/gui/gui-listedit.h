/*                                                                 ,
ssc (static site checker)
File Info
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

#ifdef WX
#define ADD_TEXT    "+"
#define REMOVE_TEXT "-"
#define RENAME_TEXT "- +"

struct listedit_manager
{   wxBoxSizer* box_ext_ = nullptr;
    wxBoxSizer* box_ext_bloc_ = nullptr;
    wxBoxSizer* box_ext_butt_ = nullptr;
    wxBoxSizer* box_file_text_ = nullptr;
    wxButton* add_ = nullptr;
    wxButton* erase_ = nullptr;
    wxButton* rename_ = nullptr;
    wxFilePickerCtrl* filename_ = nullptr;
    wxListBox* list_ = nullptr;
    wxStaticLine* line_ = nullptr;
    wxStaticText* stat_ext_ = nullptr;   
    wxTextCtrl* text_ = nullptr;
    wxWindowID add_id_, erase_id_, file_id_, list_id_, rename_id_, text_id_;
    bool has_file_ = false, has_text_ = true;
    void fex ();
    ::std::string tiswot () const;
    listedit_manager (  const wxWindowID add_id = button_add, const wxWindowID erase_id = button_erase, const wxWindowID file_id = file_name,
                        const wxWindowID list_id = list_ext, const wxWindowID rename_id = button_rename, const wxWindowID text_id = text_ext)
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
    bool construct (dialogue_t& mummy, const char* desc, const char* def = nullptr, bool file = false, bool comma = false, bool line = false);
    void enable (const bool e);
    void preload (const vstr_t& vs);
    vstr_t acquire () const;
    bool invalid () const noexcept; };

#endif // WX
