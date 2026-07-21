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

#ifdef WX
#include "main/context.h"
#include "gui/gui-dialogue.h"
#include "gui/gui-listedit.h"

#define GEN_CAPTION "general"

class general_t : public d1_t < wx_general >
{   box_t check_box_, max_box_, persist_box_, type_box_;
#ifndef NO_FRED
    box_t fred_box_;
    check_t fred_ctrl_;
    label_spin_t fred_spin_;
#endif // NO_FRED
    check_t class_ctrl_, max_ctrl_, other_ctrl_, persist_ctrl_, rdfa_ctrl_, vcs_ctrl_, vtt_ctrl_;
    check_folder_t config_folder_;
    check_file_t persist_file_;
    label_spin_t max_spin_;
    label_t check_static_;
    line_t l1_, l2_, l3_, l4_, l5_, l6_, l7_;
    listedit_manager exclude_ = listedit_manager (button_general_add, button_general_erase, button_general_rename, file_general_name, list_general_ext, text_general_ext);
    ::boost::filesystem::path config_, out_, persist_, cwd_; 
    bool class_ = false, other_ = false, rdfa_ = false, vcs_ = true, vtt_ = true;
#ifndef NO_FRED
    unsigned int fred_ = 1;
#endif // NO_FRED
    unsigned int max_ = def_max_file_size;
    vstr_t exc_;
    void enable_max (const bool b);
#ifndef NO_FRED
    void enable_fred (const bool b);
#endif // NO_FRED
    DECLARE_CLASS (general_t)
    DECLARE_EVENT_TABLE ()
public:
    DEFAULT_NO_COPY_NO_MOVE_CONSTRUCTORS (general_t);
    explicit general_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = GEN_CAPTION);
    bool invalid () const noexcept { return l7_.invalid (); }
    void Init () const noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = GEN_CAPTION);
    void CreateControls ();
    void OnAdd (wxCommandEvent& event);
    void OnConfig (wxCommandEvent& event);
    void OnErase (wxCommandEvent& event);
    void OnExclude (wxCommandEvent& event);
#ifdef NO_FRED
    void OnFred (wxCommandEvent& ) CONSTEXPR { }
#else // NO_FRED
    void OnFred (wxCommandEvent& e);
#endif // NO_FRED
    void OnHelpClick (wxCommandEvent& event);
    void OnMax (wxCommandEvent& e);
    void OnImpatience (wxCommandEvent& event);
    void OnPersist (wxCommandEvent& e);
    void OnRename (wxCommandEvent& event);
    void OnText (wxCommandEvent& event);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid_panel () const { return invalid () || (panel_ == nullptr); }
    void create_controls (wxWindow *parent);
    bool create_panel (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER);
    void load_from_context (const context_t& c);
    void save_to_context (context_t& c) const;
    bool clss () const noexcept { return class_; }
    void clss (const bool b) noexcept { class_ = b; }
    bool other () const noexcept { return other_; }
    void other (const bool b) noexcept { other_ = b; }
    bool rdfa () const noexcept { return rdfa_; }
    void rdfa (const bool b) noexcept { rdfa_ = b; }
    bool vcs () const noexcept { return vcs_; }
    void vcs (const bool b) noexcept { vcs_ = b; }
    bool vtt () const noexcept { return vtt_; }
    void vtt (const bool b) noexcept { vtt_ = b; }
    void exc (const vstr_t& vs) { exc_ = vs; }
    vstr_t exc () const { return exc_; }
#ifndef NO_FRED
    unsigned short fred () const noexcept { return GSL_NARROW_CAST < unsigned short > (fred_); }    
    void fred (const unsigned short& t);
#endif // NO_FRED
    void config (const ::boost::filesystem::path& c) { config_ = c; }
    ::boost::filesystem::path config () const { return config_; }
    void persist (const ::boost::filesystem::path& p) { persist_ = p; }
    ::boost::filesystem::path persist () const { return persist_; }
    unsigned int max_file_size () const noexcept { return max_; }    
    void max_file_size (const unsigned int& m); };
#endif // WX
