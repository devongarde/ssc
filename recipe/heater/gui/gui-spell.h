/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2024 Dylan Harris
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
#ifndef NOSPELL

#ifdef HUNSPELL
#define HUNDO
#elsif defined (DEBUG) // HUNSPELL
// #define HUNDO    // for dialogue testing under windows
#endif // HUNSPELL

#include "gui/gui-dialogue.h"
#include "gui/gui-listedit.h"

#define SPELL_CAPTION "Spelling"

class spell_t : public dialogue_t
{   wxBoxSizer* box_check_ = nullptr;
#ifdef HUNDO
    wxBoxSizer* box_hun_ = nullptr;
    wxBoxSizer* box_hun_vert_ = nullptr;
    wxBoxSizer* box_hun_horz1_ = nullptr;
    wxBoxSizer* box_hun_horz2_ = nullptr;
#endif // HUNDO
    wxBoxSizer* box_word_ = nullptr;
    wxButton* but_add_ = nullptr;
    wxButton* but_erase_ = nullptr;
    wxButton* but_rename_ = nullptr;
    wxCheckBox* check_case_ = nullptr;
#ifndef NOICU
    wxCheckBox* check_icu_ = nullptr;
#endif // NOICU
    wxCheckBox* check_spell_ = nullptr;
#ifdef HUNDO
    wxFilePickerCtrl* file_hun_ = nullptr;
    wxListBox* list_hun_ = nullptr;
#endif // HUNDO
    wxStaticLine* line_check_ = nullptr;
#ifdef HUNDO
    wxStaticLine* line_hun_ = nullptr;
#endif // HUNDO
    wxStaticLine* line_dict_ = nullptr;
#ifdef HUNDO
    wxStaticText* stat_hun_ = nullptr;
#endif // HUNDO
    wxTextCtrl* text_lingo_ = nullptr;
    listedit_manager dict_;
#ifdef HUNDO
    listedit_manager hun_ = listedit_manager (button_add_2, button_erase_2, file_name_2, list_ext_2, button_rename_2, text_ext_2);
#endif // HUNDO
    listedit_manager word_ = listedit_manager (button_add_3, button_erase_3, file_name_3, list_ext_3, button_rename_3, text_ext_3);
    bool case_ = false, check_ = false;
#ifndef NOICU
    bool icu_ = false;
#endif // NOICU
    vstr_t dicts_, words_;
#ifdef HUNDO
    vstr_t huns_;
#endif // HUNDO
    void OnCheck (wxCommandEvent& event);
    void OnDictAdd (wxCommandEvent& event);
    void OnDictErase (wxCommandEvent& event);
    void OnDictRename (wxCommandEvent& event);
    void OnDictExtension (wxCommandEvent& event);
    void OnDictTap (wxCommandEvent& event);
    void OnDictImpatience (wxCommandEvent& event);
    void OnDictFileName (wxFileDirPickerEvent& event);
#ifdef HUNDO
    void OnHunAdd (wxCommandEvent& event);
    void OnHunErase (wxCommandEvent& event);
    void OnHunRename (wxCommandEvent& event);
    void OnHunExtension (wxCommandEvent& event);
    void OnHunFileName (wxFileDirPickerEvent& event);
    void OnHunImpatience (wxCommandEvent& event);
    void OnHunTap (wxCommandEvent& event);
#endif // HUNDO
    void OnWordAdd (wxCommandEvent& event);
    void OnWordErase (wxCommandEvent& event);
    void OnWordRename (wxCommandEvent& event);
    void OnWordExtension (wxCommandEvent& event);
    void OnWordTap (wxCommandEvent& event);
    void OnWordImpatience (wxCommandEvent& event);
    DECLARE_CLASS (spell_t)
    DECLARE_EVENT_TABLE ()
public:
    spell_t () { }
    spell_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SPELL_CAPTION);
    ~spell_t () { }
    bool invalid () const noexcept
    {   return  dialogue_t::invalid () ||
                dict_.invalid () ||
#ifdef HUNDO
                hun_.invalid () ||
#endif // HUNDO
                word_.invalid () ||
                (check_icu_ == nullptr); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SPELL_CAPTION);
    void CreateControls ();
    void OnHelpClick (wxCommandEvent& event);
    bool cased () const noexcept { return case_; }
    void cased (const bool b) noexcept { case_ = b; }
    bool check () const noexcept { return check_; }
    void check (const bool b) noexcept { check_ = b; }
    void enable ();
#ifndef NOICU
    bool icu () const noexcept { return icu_; }
    void icu (const bool b) noexcept { icu_ = b; }
#endif // NOICU
    const vstr_t& dict () const { return dicts_; }
    void dict (const vstr_t& d) { dicts_ = d; }
#ifdef HUNDO
    const vstr_t& hun () const { return huns_; }
    void hun (const vstr_t& d) { huns_ = d; }
#endif // HUNDO
    const vstr_t& word () const { return words_; }
    void word (const vstr_t& d) { words_ = d; }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };
#endif // NOSPELL

#endif // WX
