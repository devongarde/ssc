/*
ssc (static site checker)
Copyright (c) 2020-2024 Dylan Harris
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
#include "main/abort.h"
#include "main/output.h"
#include "main/context.h"
#include "feedback/nitpick.h"
#include "main/ssc.h"
#ifndef NOSPELL
#include "spell/spell.h"
#endif // NOSPELL
#include "gui/gui-app.h"
#include "gui/gui-corpus.h"
#include "gui/gui-css.h"
#include "gui/gui-file.h"
#include "gui/gui-frame.h"
#include "gui/gui-general.h"
#include "gui/gui-html.h"
#include "gui/gui-icon.h"
#include "gui/gui-lynx.h"
#include "gui/gui-math.h"
#include "gui/gui-mf.h"
#include "gui/gui-nits.h"
#include "gui/gui-ontology.h"
#include "gui/gui-shadow.h"
#include "gui/gui-site.h"
#include "gui/gui-snippet.h"
#include "gui/gui-spell.h"
#include "gui/gui-stats.h"
#include "gui/gui-svg.h"
#include "gui/gui-validation.h"
#include "gui/gui-whizz.h"

BEGIN_EVENT_TABLE (frame_t, wxFrame)
    EVT_FIND (wxID_ANY, frame_t::Find)
    EVT_FIND_NEXT (wxID_ANY, frame_t::Next)
    EVT_MENU (wxID_ABOUT, frame_t::OnAbout)
    EVT_MENU (wxID_COPY, frame_t::OnCopy)
    EVT_MENU (menu_conf_open, frame_t::OnConfigOpen)
    EVT_MENU (menu_conf_save, frame_t::OnConfigSave)
    EVT_MENU (menu_conf_save_as, frame_t::OnConfigSaveAs)
    EVT_MENU (menu_corpus, frame_t::OnCorpus)
    EVT_MENU (menu_css, frame_t::OnCSS)
    EVT_UPDATE_UI (wxID_COPY, frame_t::OnUpdateCopy)
    EVT_MENU (menu_spin, frame_t::OnSpin)
    EVT_MENU (wxID_EXIT, frame_t::OnExit)
    EVT_MENU (menu_file, frame_t::OnFile)
    EVT_MENU (wxID_FIND, frame_t::OnFind)
    EVT_FIND_CLOSE(wxID_ANY, frame_t::OnFindClose)
    EVT_MENU (menu_general, frame_t::OnGeneral)
    EVT_MENU (menu_help, frame_t::OnHelp)
    EVT_MENU (menu_html, frame_t::OnHTML)
    EVT_MENU (menu_lynx, frame_t::OnLynx)
    EVT_MENU (menu_math, frame_t::OnMath)
    EVT_MENU (menu_mf, frame_t::OnMF)
    EVT_MENU (menu_next, frame_t::OnNext)
    EVT_MENU (menu_nits, frame_t::OnNits)
    EVT_MENU (wxID_PREVIEW, frame_t::OnPreview)
    EVT_MENU (wxID_PRINT, frame_t::OnPrint)
    EVT_MENU (menu_prior, frame_t::OnPrior)
    EVT_MENU (menu_print_setup, frame_t::OnPrintSetup)
    EVT_MENU (menu_ontology, frame_t::OnOntology)
    EVT_MENU (menu_root, frame_t::OnRoot)
    EVT_MENU (wxID_SAVE, frame_t::OnFileSave)
    EVT_MENU (wxID_SAVEAS, frame_t::OnFileSaveAs)
    EVT_MENU (wxID_SELECTALL, frame_t::OnSelectAll)
    EVT_MENU (menu_shadow, frame_t::OnShadow)
    EVT_MENU (menu_site, frame_t::OnSite)
    EVT_MENU (menu_snippet, frame_t::OnSnippet)
#ifndef NOSPELL
    EVT_MENU (menu_spell, frame_t::OnSpell)
#endif // NOSPELL
    EVT_MENU (menu_stats, frame_t::OnStats)
    EVT_MENU (menu_svg, frame_t::OnSVG)
    EVT_SIZE (frame_t::OnSize)
    EVT_UPDATE_UI (wxID_SELECTALL, frame_t::OnUpdateSelectAll)
    EVT_MENU (menu_validation, frame_t::OnValidation)
    EVT_MENU (menu_wizzard, frame_t::OnWizzard)
END_EVENT_TABLE ()

frame_t::frame_t (const wxPoint& pt, const wxSize& sz, const context_t& c)
    : wxFrame (nullptr, wxID_ANY, FULLNAME, pt, sz, wxDEFAULT_FRAME_STYLE), context_ (c)
{   SetIcon (teapot ());
    SetMenuBar (bar_.gimme ());
    CreateStatusBar ();
    wxFileSystem::AddHandler (new wxZipFSHandler);
    output_ = GSL_OWNER (output_t) (new output_t (this));
    print_ = GSL_OWNER (wxHtmlEasyPrinting) (new wxHtmlEasyPrinting (FULLNAME, this));
    if (print_ != nullptr) print_ -> SetFooter ("<hr>Page @PAGENUM@ of @PAGESCNT@", wxPAGE_ALL);
    SetStatusText (FORMALNAME " says 'er ... what?'"); }

frame_t::~frame_t ()
{   delete print_; }

void frame_t :: append (const ::std::string& text)
{   if (output_ != nullptr) output_ -> append (text); }

void frame_t :: clear ()
{   if (output_ != nullptr) output_ -> clear (); }

void frame_t :: status (const ::std::string& s)
{    SetStatusText (s.c_str ()); }

bool frame_t::process_config (const nitpick& nits, const ::boost::filesystem::path& fn)
{   if (! nits.empty ())
        wxMessageBox (wxString (nits.review ()));
    if (nits.worst () > es_error)
    {   new_config_ = true;
        config_ = fn;
        return true; }
    return false; }

void frame_t :: load ()
{   wxFileDialog dialogue (this, "Load Configuration",
        wxEmptyString, "config.conf", "Configuration files (*.conf)|*.conf", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dialogue.ShowModal () == wxID_OK)
    {   nitpick nits ("configuration load");
        const ::boost::filesystem::path fn (::std::string (dialogue.GetPath ().c_str ()));
        context_t c (nits, fn);
        if (process_config (nits, fn)) context_ = c; } }

void frame_t :: save () const
{   nitpick nits ("configuration save");
    if (! config_.empty ())
        if (! context_.write (nits, config_))
            wxMessageBox (wxString (nits.review ())); }

void frame_t :: save_as ()
{   wxFileDialog dialogue (this, "Save Configuration",
        wxEmptyString, "config.conf", "Configuration files (*.conf)|*.conf", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialogue.ShowModal () == wxID_OK)
    {   nitpick nits ("configuration save");
        const ::boost::filesystem::path fn (::std::string (dialogue.GetPath ().c_str ()));
        context_.write (nits, fn);
        process_config (nits, fn); } }

void frame_t :: Find (wxFindDialogEvent& e)
{   if ((find_ != nullptr) && (find_data_!= nullptr))
    {   const ::std::string wot (e.GetFindString ().c_str ());
        const int fussitudes = e.GetFlags ();
        if (output_ != nullptr) output_ -> Find (wot, fussitudes);
        OnFindClose (e); } }

void frame_t :: Next (wxFindDialogEvent& e)
{   if (find_data_!= nullptr)
    {   const ::std::string wot (e.GetFindString ().c_str ());
        const int fussitudes = e.GetFlags ();
        if (output_ != nullptr) output_ -> Find (wot, fussitudes); } }

void frame_t :: OnAbout (wxCommandEvent& )
{   if (app != nullptr) app -> help ("about"); }

void frame_t :: OnConfigOpen (wxCommandEvent& )
{   load (); }

void frame_t :: OnConfigSave (wxCommandEvent& )
{   save (); }

void frame_t :: OnConfigSaveAs (wxCommandEvent& )
{   save_as (); }
 
void frame_t :: OnCopy (wxCommandEvent& e)
{   if (output_ != nullptr) output_ -> OnCopy (e); }

void frame_t :: OnCorpus (wxCommandEvent& )
{   corpus_t c (this);
    c.folder (context_.corpus ());
    c.article (context_.article ());
    c.body (context_.body ());
    c.main (context_.main ());
    if (c.ShowModal () == wxID_OK)
    {   context_.corpus (c.folder ());
        context_.article (c.article ());
        context_.body (c.body ());
        context_.main (c.main ()); } }

void frame_t :: OnCSS (wxCommandEvent& )
{   css_t c (this);
    c.ext (context_.css_extension ());
    c.version (context_.html_ver ());
    if (c.ShowModal () == wxID_OK)
    {   context_.css_extension (c.ext ());
        context_.html_ver (c.version ()); } }

void frame_t :: OnExit (wxCommandEvent& )
{   if (find_ != nullptr)
    {   find_ -> Destroy ();
        find_ = nullptr; }
    delete find_data_;
    find_data_ = nullptr;
    Close (true); }

void frame_t :: OnFile (wxCommandEvent& )
{   file_t f (this);
    f.config (context_.path ().c_str ());
    f.persist (context_.persisted ());
    if (f.ShowModal () == wxID_OK)
    {   context_.path (f.config ().string ());
        context_.persisted (f.persist ().string ()); } }

void frame_t :: OnFileSave (wxCommandEvent& )
{   if (output_ != nullptr) output_ -> FileSave (this); }

void frame_t :: OnFileSaveAs (wxCommandEvent& )
{   if (output_ != nullptr) output_ -> FileSaveAs (this); }
 
void frame_t :: OnFind (wxCommandEvent& )
{   if (find_ == nullptr)
    {   if (find_data_ == nullptr)
        {   find_data_ = GSL_OWNER (wxFindReplaceData) (new wxFindReplaceData (0));
            if (find_data_ == nullptr) return;
            find_data_ -> SetFlags (wxFR_DOWN | wxFR_MATCHCASE); }
        find_ = GSL_OWNER (wxFindReplaceDialog)
                (new wxFindReplaceDialog (this, find_data_, "find text", 0));
        if (find_ != nullptr) find_ -> Show (true); } }

void frame_t :: OnFindClose (wxFindDialogEvent& )
{   if (find_ != nullptr)
    {   find_ -> Destroy ();
        find_ = nullptr; } }

void frame_t :: OnGeneral (wxCommandEvent& )
{   general_t g (this);
    g.css (context_.unknown_class ());
    g.other (context_.classic ());
    g.rdfa (context_.rdfa ());
    g.vcs (context_.vcs ());
#ifndef NO_FRED
    g.fred (GSL_NARROW_CAST < unsigned short > (context_.fred ()));
#endif // NO_FRED
    g.max_file_size (GSL_NARROW_CAST < unsigned int > (context_.max_file_size ()));
    if (g.ShowModal () == wxID_OK)
    {   context_.unknown_class (g.css ());
        context_.classic (g.other ());
        context_.rdfa (g.rdfa ());
        context_.vcs (g.vcs ());
#ifndef NO_FRED
        context_.fred (g.fred ());
#endif // NO_FRED
        context_.max_file_size (g.max_file_size ()); } }

void frame_t :: OnHelp (wxCommandEvent& e)
{   if (output_ != nullptr) output_ -> OnHelp (e); }

void frame_t :: OnHTML (wxCommandEvent& )
{   html_t h (this);
    h.ie (context_.ie ());
    h.rfc1867 (context_.rfc_1867 ());
    h.rfc1942 (context_.rfc_1942 ());
    h.rfc1980 (context_.rfc_1980 ());
    h.rfc2070 (context_.rfc_2070 ());
    h.safari (context_.safari ());
    h.sloven (context_.sloven ());
    h.ssi (context_.ssi ());
    h.title (GSL_NARROW_CAST < unsigned int > (context_.title ()));
    h.ver (context_.html_ver ());
    if (context_.force_version ()) h.doctype (2);
    else if (context_.presume_tags ()) h.doctype (0);
    else h.doctype (1);
    h.lingo (context_.lang ());
    if (h.ShowModal () == wxID_OK)
    {   context_.ie (h.ie ());
        context_.rfc_1867 (h.rfc1867 ());
        context_.rfc_1942 (h.rfc1942 ());
        context_.rfc_1980 (h.rfc1980 ());
        context_.rfc_2070 (h.rfc2070 ());
        context_.safari (h.safari ());
        context_.sloven (h.sloven ());
        context_.ssi (h.ssi ());
        context_.title (h.title ());
        context_.html_ver (h.ver ());
        context_.lang (h.lingo ());
        switch (h.doctype ())
        {   case 0 : context_.force_version (false); context_.presume_tags (true); break;
            case 2 : context_.force_version (true); context_.presume_tags (false); break;
            default : context_.force_version (false); context_.presume_tags (false); break; } } }

void frame_t :: OnLoad (wxCommandEvent& )
{   load (); }

void frame_t :: OnLynx (wxCommandEvent& )
{   lynx_t lynx (this);
    lynx.example (context_.example ());
    lynx.external (context_.external ());
    lynx.forwarded (context_.forwarded ());
    lynx.id (context_.crosslinks ());
    lynx.inter (context_.links ());
    lynx.local (context_.local ());
    lynx.once (context_.once ());
    lynx.revoke (context_.revoke ());
    if (lynx.ShowModal () == wxID_OK)
    {   context_.example (lynx.example ());
        context_.external (lynx.external ());
        context_.forwarded (lynx.forwarded ());
        context_.crosslinks (lynx.id ());
        context_.links (lynx.inter ());
        context_.local (lynx.local ());
        context_.once (lynx.once ());
        context_.revoke (lynx.revoke ()); } }

void frame_t :: OnMath (wxCommandEvent& )
{   math_t math (this);
    math.version (context_.math_version ());
    if (math.ShowModal () == wxID_OK)
        context_.math_version (math.version ()); }

void frame_t :: OnMF (wxCommandEvent& )
{   mf_t mf (this);
    mf.version (context_.mf_version ());
    mf.exp (context_.mf_export ());
    mf.verify (context_.mf_verify ());
    if (mf.ShowModal () == wxID_OK)
    {   context_.mf_version (GSL_NARROW_CAST < const unsigned char > (mf.version () & 0x0F));
        context_.mf_export (mf.exp ());
        context_.mf_verify (mf.verify ()); } }

void frame_t :: OnNext (wxCommandEvent& e)
{   if (find_data_ == nullptr) OnFind (e);
    else if (output_ != nullptr) output_ -> Next (); }

void frame_t :: OnNits (wxCommandEvent& )
{   nits_t n (this);
    n.id (context_.nids ());
    n.repeat (context_.nits_nits_nits ());
    n.severity (nitpick::mns ());
    n.verbosity (context_.verbose ());
    if (n.ShowModal () == wxID_OK)
    {   context_.nids (n.id ());
        context_.nits_nits_nits (n.repeat ());
        context_.verbose (n.verbosity ());
        nitpick::mns (n.severity ()); } }

void frame_t :: OnOntology (wxCommandEvent& )
{   ontology_t o (this);
    o.verify (context_.ontology ());
    o.exp (context_.md_export ());
    o.path (context_.export_root ());
    o.lvsv (vsv);
    if (o.ShowModal () == wxID_OK)
    {   context_.export_root (o.path ().string ());
        context_.md_export (o.exp ());
        context_.ontology (o.verify ());
        vsv = o.lvsv (); } }

void frame_t :: OnPreview (wxCommandEvent& )
{   if ((output_ != nullptr) && (print_ != nullptr))
        output_ -> Preview (print_); }

void frame_t :: OnPrint (wxCommandEvent& )
{   if ((output_ != nullptr) && (print_ != nullptr))
        output_ -> Print (print_); }

void frame_t :: OnPrior (wxCommandEvent& e)
{   if (find_data_ == nullptr) OnFind (e);
    else if (output_ != nullptr) output_ -> Prior (); }

void frame_t :: OnPrintSetup (wxCommandEvent& )
{   if (print_ != nullptr) print_ -> PageSetup (); }

void frame_t :: OnRoot (wxCommandEvent& )
{   wxDirDialog dir (this, "select site root", root_.c_str ());
    if (dir.ShowModal () == wxID_OK)
    {   new_site_ = true;
        root_ = ::std::string (dir.GetPath ().c_str ()); } }

void frame_t :: OnSelectAll (wxCommandEvent& e)
{   if (output_ != nullptr) output_ -> OnSelectAll (e); }

void frame_t :: OnShadow (wxCommandEvent& )
{   shadow_t shad (this);
    shad.cache (context_.shadow_persist ());
    shad.change (context_.shadow_changed ());
    shad.comment (context_.msg ());
    shad.keep (context_.shadow_comment ());
    shad.ignore (context_.shadow_ignore ());
    shad.shadow (context_.shadow_root ());
    shad.site (context_.shadow_enable ());
    shad.ssi (context_.shadow_ssi ());
    shad.strategy (context_.copy ());
    shad.time (context_.info ());
    shad.whitespace (context_.shadow_space ());
    if (shad.ShowModal () == wxID_OK)
    {   context_.shadow_changed (shad.change ());
        context_.copy (shad.strategy ());
        context_.info (shad.time ());
        context_.msg (shad.comment ());
        context_.shadow_comment (shad.keep ());
        context_.shadow_enable (shad.site ());
        context_.shadow_ignore (shad.ignore ());
        context_.shadow_persist (shad.cache ().string ());
        context_.shadow_root (shad.shadow ().string ());
        context_.shadow_space (shad.whitespace ());
        context_.shadow_ssi (shad.ssi ()); } }

void frame_t :: OnSite (wxCommandEvent& )
{   site_t dlg (this);
    dlg.site (context_.site ());
    dlg.def (context_.rootp ());
    if (dlg.ShowModal () == wxID_OK)
    {   context_.site (dlg.site ());
        context_.root (dlg.def ().string ()); } }

void frame_t :: OnSize (wxSizeEvent &event)
{   event.Skip(); }

#ifndef NOSPELL
void frame_t :: OnSpell (wxCommandEvent& )
{   spell_t dlg (this);
    dlg.cased (context_.cased ());
    dlg.check (context_.spell ());
    dlg.dict (get_spell_list ());
#ifndef NOICU
    dlg.icu (context_.icu ());
#endif // NOICU
    dlg.word (context_.spellings ());
    if (dlg.ShowModal ())
    {   context_.cased (dlg.cased ());
#ifndef NOICU
        context_.icu (dlg.icu ());
#endif // NOICU
        context_.spell (dlg.check ());
        context_.spellings (dlg.word ());
        spell_reset ();
        nitpick nits;
        add_spell_list (nits, dlg.dict ()); } }
#endif // NOSPELL

void frame_t :: OnSnippet (wxCommandEvent& )
{   snippet_t s (this);
    s.snippet (snippet_);
    if (s.ShowModal () == wxID_OK)   
    {   snippet_ = s.snippet ();
        new_snippet_ = ! snippet_.empty (); } }

void frame_t :: OnStats (wxCommandEvent& )
{   report_t stats (this);
    for (int i = 0; i < rcb_max; ++i)
    {   const e_report r = GSL_NARROW_CAST < e_report > (i);
        stats.report (r, context_.stats_report (r)); }
    stats.dump (context_.stats ());
    if (stats.ShowModal () == wxID_OK)
    {   for (int i = 0; i < rcb_max; ++i)
        {   const e_report r = GSL_NARROW_CAST < e_report > (i);
            context_.stats_report (r, stats.report (r)); }
        context_.stats (stats.dump ().string ()); } }

void frame_t :: OnSVG (wxCommandEvent& )
{   svg_t svg (this);
    svg.version (context_.svg_version ());
    if (svg.ShowModal () == wxID_OK)
        context_.svg_version (svg.version ()); }

void frame_t :: OnUpdateCopy (wxUpdateUIEvent& e)
{   if (output_ != nullptr) output_ -> OnUpdateCopy (e); }

void frame_t :: OnUpdateSelectAll (wxUpdateUIEvent& e)
{   if (output_ != nullptr) output_ -> OnUpdateSelectAll (e); }

void frame_t :: OnValidation (wxCommandEvent& )
{   valid_t dlg (this);
    
    dlg.ShowModal ();
}

void frame_t :: OnWizzard (wxCommandEvent& ) // angel fingers
{   whizz_t w (this);

    w.run ();
}

void frame_t :: OnSpin (wxCommandEvent& )
{   rational_ = bar_.config () -> IsChecked (menu_spin); }

#endif // WX
