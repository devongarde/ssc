/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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

class spell_t : public d1_t < wx_spell >
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
    wxStaticLine* base_ = nullptr;
    wxStaticLine* line_check_ = nullptr;
#ifdef HUNDO
    wxStaticLine* line_hun_ = nullptr;
#endif // HUNDO
    wxStaticLine* line_dict_ = nullptr;
#ifdef HUNDO
    wxStaticText* stat_hun_ = nullptr;
#endif // HUNDO
    wxTextCtrl* text_lingo_ = nullptr;
    listedit_manager dict_ = listedit_manager (button_dict_add, button_dict_erase, button_dict_rename, file_dict_name, list_dict_ext, text_dict_ext);
#ifdef HUNDO
    listedit_manager hun_ = listedit_manager (button_hun_add, button_hun_erase, button_hun_rename, file_hun_name, list_hun_ext, text_hun_ext);
#endif // HUNDO
    listedit_manager word_ = listedit_manager (button_word_add, button_word_erase, button_word_rename, file_word_name, list_word_ext, text_word_ext);
    bool case_ = false, check_ = false;
#ifndef NOICU
    bool icu_ = false;
#endif // NOICU
    vstr_t dicts_, words_;
#ifdef HUNDO
    vstr_t huns_;
#endif // HUNDO
    DECLARE_CLASS (spell_t)
    DECLARE_EVENT_TABLE ()
public:
    spell_t () { }
    spell_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SPELL_CAPTION);
    ~spell_t () { }
    bool invalid () const noexcept
    {   return  dict_.invalid () ||
#ifdef HUNDO
                hun_.invalid () ||
#endif // HUNDO
                word_.invalid () ||
                (check_icu_ == nullptr); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = SPELL_CAPTION);
    void CreateControls ();
    void OnCheck (wxCommandEvent& event);
    void OnDictAdd (wxCommandEvent& event);
    void OnDictErase (wxCommandEvent& event);
    void OnDictRename (wxCommandEvent& event);
    void OnDictExtension (wxCommandEvent& event);
    void OnDictTap (wxCommandEvent& event);
    void OnDictImpatience (wxCommandEvent& event);
    void OnDictFileName (wxFileDirPickerEvent& event);
    void OnHelpClick (wxCommandEvent& event);
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
    bool invalid_panel () const { return d1_t :: invalid_panel () || (panel_ == nullptr) || dict_.invalid () ||
#ifdef HUNDO
                                            hun_.invalid () ||
#endif // HUNDO
                                            word_.invalid () || (check_icu_ == nullptr); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;

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
