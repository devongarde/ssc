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
#include "main/context.h"
#include "gui/gui-menu.h"
#include "gui/gui-output.h"

class frame_t : public wxFrame
{   bar_t bar_;
    output_t* output_ = nullptr;
    wxHtmlEasyPrinting* print_ = nullptr;
    wxFindReplaceDialog* find_ = nullptr;
    wxFindReplaceData* find_data_ = nullptr;
    ::boost::filesystem::path config_, root_;
    ::std::string snippet_;
    bool new_config_ = false, new_snippet_ = false, new_site_ = false, rational_ = true;
    context_t context_;
    bool process_config (const nitpick& nits, const ::boost::filesystem::path& fn);
    DECLARE_EVENT_TABLE ()
public:
    frame_t () = default;
    frame_t (const wxPoint& pt, const wxSize& sz, const context_t& c);
    frame_t (const frame_t& f) = default;
    frame_t (frame_t&& f) = default;
    ~frame_t ();
    frame_t& operator = (const frame_t& f) = default;
    frame_t& operator = (frame_t&& f) = default;
    void append (const ::std::string& text);
    void clear ();
    context_t& context () { return context_; }
    const context_t& context () const { return context_; }
    void load ();
    void save () const;
    void save_as ();
    void status (const ::std::string& s);
    ::boost::filesystem::path config ()
    {   new_config_ = false;
        return config_; }
    ::boost::filesystem::path site ()
    {   new_site_ = false;
        return root_; }
    ::std::string snippet ()
    {   if (! new_snippet_) return ::std::string ();
        new_snippet_ = false;
        return snippet_; }
    bool new_config () const { return new_config_; }
    bool new_site () const { return new_site_; }
    bool new_snippet () const { return new_snippet_; }
    void Find (wxFindDialogEvent& e);
    void Next (wxFindDialogEvent& e);
    void OnAbout (wxCommandEvent& e);
    void OnConfigOpen (wxCommandEvent& e);
    void OnConfigSave (wxCommandEvent& e);
    void OnConfigSaveAs (wxCommandEvent& e);
    void OnCorpus (wxCommandEvent& e);
    void OnCopy (wxCommandEvent& e);
    void OnCSS (wxCommandEvent& e);
    void OnExit (wxCommandEvent& e);
    void OnFile (wxCommandEvent& e);
    void OnFileSave (wxCommandEvent& e);
    void OnFileSaveAs (wxCommandEvent& e);
    void OnFind (wxCommandEvent& e);
    void OnFindClose (wxFindDialogEvent& e);
    void OnGeneral (wxCommandEvent& e);
    void OnHelp (wxCommandEvent& e);
    void OnHTML (wxCommandEvent& e);
    void OnLoad (wxCommandEvent& e);
    void OnLynx (wxCommandEvent& e);
    void OnMath (wxCommandEvent& e);
    void OnMF (wxCommandEvent& e);
    void OnNext (wxCommandEvent& e);
    void OnNits (wxCommandEvent& e);
    void OnOntology (wxCommandEvent& e);
    void OnPreview (wxCommandEvent& e);
    void OnPrint (wxCommandEvent& e);
    void OnPrior (wxCommandEvent& e);
    void OnPrintSetup (wxCommandEvent& e);
    void OnRoot (wxCommandEvent& e);
    void OnSelectAll (wxCommandEvent& e);
    void OnShadow (wxCommandEvent& e);
    void OnSite (wxCommandEvent& e);
    void OnSize (wxSizeEvent& e);
    void OnSnippet (wxCommandEvent& e);
#ifndef NOSPELL
    void OnSpell (wxCommandEvent& e);
#endif // NOSPELL
    void OnSpin (wxCommandEvent& e);
    void OnStats (wxCommandEvent& e);
    void OnSVG (wxCommandEvent& e);
    void OnUpdateCopy (wxUpdateUIEvent& e);
    void OnUpdateSelectAll (wxUpdateUIEvent& e);
    void OnValidation (wxCommandEvent& e);
    void OnWizzard (wxCommandEvent& e); // see my baby jive
    bool rational () const noexcept { return rational_; } };

typedef frame_t* frame_pt;

#endif // WX
