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
#include "main/context.h"
#include "main/args.h"
#include "webpage/root.h"
#include "attribute/attr.h"
#include "element/elem.h"
#include "element/element_classes.h"
#include "type/type.h"
#include "gui/gui-app.h"
#include "gui/gui-validation.h"
#include "utility/filesystem.h"

#define VALID_STYLE   DEF_STYLE
#define VALID_X       100
#define VALID_Y       100
#define VALID_WIDTH   400
#define VALID_HEIGHT  250

BEGIN_EVENT_TABLE (vv_t, d1_t)
  EVT_CHOICE (choice_validation_version, vv_t::OnChoice)
  EVT_BUTTON (wxID_HELP, vv_t::OnHelpClick)
  EVT_BUTTON (button_validation_add, vv_t::OnValAdd)
  EVT_BUTTON (button_validation_erase, vv_t::OnValErase)
  EVT_BUTTON (button_validation_rename, vv_t::OnValRename)
  EVT_DIRPICKER_CHANGED (dir_ontology, vv_t :: OnOntology)
  EVT_DIRPICKER_CHANGED (dir_physical, vv_t :: OnPhys)
  EVT_DIRPICKER_CHANGED (dir_shadow, vv_t :: OnShadow)
  EVT_TEXT (text_validation, vv_t::OnValText)
  EVT_LISTBOX (list_validation, vv_t::OnValSelect)
  EVT_LISTBOX_DCLICK (list_validation, vv_t::OnValImpatience)
  EVT_BUTTON (button_virtual_add, vv_t::OnVirtAdd)
  EVT_BUTTON (button_virtual_erase, vv_t::OnVirtErase)
  EVT_BUTTON (button_virtual_rename, vv_t::OnVirtRename)
  EVT_TEXT (text_virtual, vv_t::OnVirtText)
  EVT_LISTBOX (list_virtual, vv_t::OnVirtSelect)
  EVT_LISTBOX_DCLICK (list_virtual, vv_t::OnVirtImpatience)
END_EVENT_TABLE ()

IMPLEMENT_CLASS (vv_t, d1_t)

// taking class out because of CSS, rel because of MF, plusstyle because, and Element::Attribute because it needs different treatment
#define BASE_VALID "Attribute", "Charset", "Colour", "Country Code", "Currency Code", "Dingbat", "Element", "Extension", "Font Feature", "Font Variation", "HttpEquiv Macro", \
    "Language Code", "Meta Name", "Mimetype", "SGML Schema"
#define BASE_COUNT 15

::std::vector < wxString > vld;	// the code presumes this won't be fiddled with whilst a dialogue is open

vv_t :: vv_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
    : d1_t (wxPoint (VALID_X, VALID_Y), wxSize (VALID_WIDTH, VALID_HEIGHT))
{	Create (mummy, id, caption); } 

bool vv_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (VALID_X, VALID_Y), wxSize (VALID_WIDTH, VALID_HEIGHT), VALID_STYLE)) return false;
    CreateControls ();
    return true; }

void vv_t :: create_virtual_dir_controls (wxWindow *parent, wxGridSizer* grid, wxStaticText*& stat, wxDirPickerCtrl*& dir, const char* const stattxt, const wxWindowID id)
{	VERIFY_NOT_NULL (grid, __FILE__, __LINE__);
    stat = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, stattxt, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
    if (stat != nullptr)
    {	dir = GSL_OWNER (wxDirPickerCtrl) (new wxDirPickerCtrl (parent, id, wxEmptyString, RREPERTOIRE, wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE));
        if (dir !=  nullptr)
        {	grid -> Add (stat, 2, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);
            grid -> Add (dir, 5, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, 5); } } }

void vv_t :: create_controls (wxWindow *parent)
{	virt_.construct (parent, box_, "Virtual " RREPERTOIRES);
    if (! virt_.invalid ())
    {	grid_virt_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));	
        if (grid_virt_ != nullptr)
        {	create_virtual_dir_controls (parent, grid_virt_, stat_folder_, dir_folder_, "Physical " REPERTOIRE ":", dir_physical);
            create_virtual_dir_controls (parent, grid_virt_, stat_shadow_, dir_shadow_, "Shadow output " REPERTOIRE ":", dir_shadow);
            create_virtual_dir_controls (parent, grid_virt_, stat_ontology_, dir_ontology_, "Ontology output " REPERTOIRE ":", dir_ontology);
            stat_note_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, " ", wxDefaultPosition, wxDefaultSize, 0));
            if (stat_note_ != nullptr)
            {	box_ -> Add (grid_virt_, 0, wxEXPAND, 1);
                box_ -> Add (stat_note_, 0, wxEXPAND | wxALL, 5); } } }

    line_valid_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_valid_ != nullptr)
        box_ -> Add (line_valid_, 0, wxEXPAND | wxALL, 5);

    box_for_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
    if (box_for_ != nullptr)
    {	stat_for_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Validation    ", wxDefaultPosition, wxDefaultSize, 0));
        if (stat_for_ != nullptr)
        {	box_for_ -> Add (stat_for_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
            if (vld.empty ())
            {	vld.assign ( { BASE_VALID } );
                for (auto& o : context.validation ())
                {	const ::std::string s (o.first);
                    if (! s.empty ())
                    {	const ::std::string::size_type pos = s.find ('.');
                        if ((pos != ::std::string::npos) && (pos < s.length () - 1))
                             vld.push_back (s.substr (pos+1)); } }
                PRESUME ((vld.size () == context.validation ().size () + BASE_COUNT), __FILE__, __LINE__);
                ::std::sort (vld.begin (), vld.end ()); }
            choice_for_ = GSL_OWNER (wxChoice) (new wxChoice (parent, choice_validation_version, wxDefaultPosition, wxDefaultSize, GSL_NARROW_CAST < int > (vld.size ()), vld.data (), 0));
            if (choice_for_ != nullptr)
            {	choice_for_ -> SetSelection (0);
                box_for_ -> Add (choice_for_, 0, wxALL, 5);
                box_ -> Add (box_for_, 0, wxALIGN_CENTER_HORIZONTAL, 5); } } }

    val_.construct (parent, box_, "");

    line_base_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (line_base_ != nullptr)
        box_ -> Add (line_base_, 0, wxEXPAND | wxALL, 5); }

void vv_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
    d1_t :: CreateButtons (1);
    SetSizer (box_);
    Layout ();
    Centre (wxBOTH); }

void vv_t :: depopulate ()
{   PRESUME (! invalid (), __FILE__, __LINE__);
    if (prior_ != wxNOT_FOUND)
    {	const e_css_version sel = GSL_NARROW_CAST < e_css_version > (prior_);
        const ::std::size_t fm = vvfix_.size ();
        const ::std::size_t sz = val_.list_ -> GetCount ();
        PRESUME (sel < fm, __FILE__, __LINE__);
        PRESUME (sel < vvextra_.size (), __FILE__, __LINE__);
        const ::std::size_t fr = vvfix_.at (sel).size ();
        if (sz >= fr)
        {   vvextra_.at (sel).clear ();
            for (::std::size_t i = fr; i < sz; ++i)
                vvextra_.at (sel).push_back (::std::string (val_.list_ -> GetString (GSL_NARROW_CAST < unsigned int > (i)).c_str ())); }
        prior_ = wxNOT_FOUND; } }

void vv_t :: repopulate ()
{   PRESUME (! invalid (), __FILE__, __LINE__);
    prior_ = choice_for_ -> GetSelection ();
    if (prior_ != wxNOT_FOUND)
    {	const e_css_version sel = GSL_NARROW_CAST < e_css_version > (prior_);
        PRESUME (sel < vvfix_.size (), __FILE__, __LINE__);
        PRESUME (sel < vvextra_.size (), __FILE__, __LINE__);
        vstr_t vv (vvfix_.at (sel));
        for (auto& x : vvextra_.at (sel)) vv.push_back (x);
        val_.preload (vv); } }

void vv_t :: populate ()
{   if (invalid ()) return;
    depopulate ();  
    repopulate (); }

void vv_t :: OnChoice (wxCommandEvent& )
{   populate (); }

void vv_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help (hp_validation); }

void vv_t :: OnValAdd (wxCommandEvent& e)
{ if (! invalid ()) { val_.OnAdd (e); reval (); } }

void vv_t :: OnValErase (wxCommandEvent& e)
{ if (! invalid ()) { val_.OnErase (e); reval (); } }

void vv_t :: OnValRename (wxCommandEvent& e)
{ if (! invalid ()) { val_.OnRename (e); reval (); } }

void vv_t :: OnValSelect (wxCommandEvent& e)
{ if (! invalid ()) { val_.OnTap (e); reval (); } }

void vv_t :: OnValText (wxCommandEvent& e)
{ if (! invalid ()) { val_.OnText (e); reval (); } }

void vv_t :: OnValImpatience (wxCommandEvent& e)
{ if (! invalid ()) { val_.OnImpatience (e); reval (); } }

void vv_t :: OnVirtAdd (wxCommandEvent& e)
{   if (! invalid ())
    {   virt_.OnAdd (e);
        pvirt_ = virt_.sel ();
        part_de_virt (pvirt_);
        en_virt (); } }

void vv_t :: OnVirtErase (wxCommandEvent& e)
{   // this, it must be said, is dismal
    if (! invalid ())
    {   const ::std::size_t zap = virt_.list_ -> GetSelection ();
        const ::std::size_t mx = virts_.size () - 1;
        virt_.OnErase (e);
        if (mx == 0)
        {   virts_.clear ();
            shadow_.clear ();
            phys_.clear ();
            export_.clear (); }
        else
        {   vstr_t vs;
            vbp_t ps, ss, es;
            es.reserve (mx);
            ps.reserve (mx);
            ss.reserve (mx);
            vs.reserve (mx);
            for (::std::size_t n = 0; n < virts_.size (); ++n)
                if (n != zap)
                {   es.emplace_back (export_.at (n));
                    ps.emplace_back (phys_.at (n));
                    ss.emplace_back (shadow_.at (n));
                    vs.emplace_back (virts_.at (n)); }
            export_ = es;
            phys_ = ps;
            shadow_ = ss;
            virts_ = vs; }
        en_virt (); } }

void vv_t :: OnVirtRename (wxCommandEvent& e)
{ if (! invalid ()) { virt_.OnRename (e); en_virt (); } }

void vv_t :: OnVirtSelect (wxCommandEvent& e)
{   if (! invalid ())
    {   virt_.OnTap (e); en_virt (); } }

void vv_t :: OnVirtImpatience (wxCommandEvent& e)
{ if (! invalid ()) { virt_.OnTap (e); en_virt (); } }

void vv_t :: OnVirtText (wxCommandEvent& e)
{ if (! invalid ()) { virt_.OnTap (e); en_virt (); } }

void vv_t :: OnPhys (wxFileDirPickerEvent& )
{   if (! invalid ())
    {   const ::std::size_t sel = virt_.sel ();
        bpsize (sel + 1);
        phys_.at (sel) = ::boost::filesystem::path (dir_folder_ -> GetPath ().c_str ());
        en_virt (); } }

void vv_t :: OnOntology (wxFileDirPickerEvent& )
{   if (! invalid ())
    {   const ::std::size_t sel = virt_.sel ();
        bpsize (sel + 1);
        export_.at (sel) = ::boost::filesystem::path (dir_folder_ -> GetPath ().c_str ());
        en_virt (); } }

void vv_t :: OnShadow (wxFileDirPickerEvent& )
{   if (! invalid ())
    {   const ::std::size_t sel = virt_.sel ();
        bpsize (sel + 1);
        shadow_.at (sel) = ::boost::filesystem::path (dir_folder_ -> GetPath ().c_str ());
        en_virt (); } }

void vv_t :: bpsize (const ::std::size_t z)
{   PRESUME ((phys_.size () == export_.size ()) && (phys_.size () == shadow_.size ()) && (phys_.size () == virts_.size ()), __FILE__, __LINE__);
    if (z >= phys_.size ())
    {   virts_.resize (z + 1);
        phys_.resize (z + 1);
        export_.resize (z + 1);
        shadow_.resize (z + 1); } }

void vv_t :: part_de_virt (const int z)
{   if (z != wxNOT_FOUND)
    {   const ::std::size_t sz = z;
        bpsize (sz);
        phys_.at (sz) = ::boost::filesystem::path (dir_folder_ -> GetPath ().c_str ());
        export_.at (sz) = ::boost::filesystem::path (dir_ontology_ -> GetPath ().c_str ());
        shadow_.at (sz) = ::boost::filesystem::path (dir_shadow_ -> GetPath ().c_str ()); } }

void vv_t :: en_virt ()
{	PRESUME (! invalid (), __FILE__, __LINE__);
    const bool txt = ! virt_.text_ -> GetValue ().empty ();
    const int sel = virt_.sel ();
    const bool sltd = (sel >= 0);
    if (pvirt_ != sel)
    {   part_de_virt (pvirt_);
        if (sel != wxNOT_FOUND)
        {   bpsize (sel);
            dir_folder_ -> SetPath (phys_.at (sel).string ());
            dir_ontology_ -> SetPath (export_.at (sel).string ());
            dir_shadow_ -> SetPath (shadow_.at (sel).string ()); }
        pvirt_ = sel; }
    virt_check ();
    const bool f = dir_folder_ -> GetDirName ().DirExists ();
    dir_ontology_ -> Enable (sltd || txt);
    dir_folder_ -> Enable (sltd || txt);
    dir_shadow_ -> Enable (sltd || txt);
    stat_ontology_ -> Enable (sltd || txt);
    stat_folder_ -> Enable (sltd || txt);
    stat_shadow_ -> Enable (sltd || txt);
    if (virt_.able_enable ()) virt_.add_ -> Enable (txt && f); }

bool same_dirs (::std::string& note, const ::std::string& m, const ::std::string& n, const ::boost::filesystem::path& lhs, const ::boost::filesystem::path& rhs, const char* const ln, const char* const rn)
{   ::std::stringstream ss;
    if (lhs.empty () || rhs.empty ()) return false;
    if (lhs != rhs) return false;
    if (n == m) ss << "Warning: " << ln << " and " << rn << " " << REPERTOIRES << " for " << m << " match.";
    else ss << "Warning: " << m << " " << ln << " matches " << n << " " << rn << ".";
    note += ss.str ();
    return true; }

void vv_t :: virt_check ()
{   ::std::string note;
    bool stop = false;
    for (::std::size_t x = 0; (! stop) && (x < virts_.size ()); ++x)
    {   stop =  same_dirs (note, virts_.at (x), "yer actual", phys_.at (x), yer_root_, "physical", "root") ||
                same_dirs (note, virts_.at (x), "yer actual", phys_.at (x), yer_shadow_, "physical", "shadow") ||
                same_dirs (note, virts_.at (x), "yer actual", phys_.at (x), yer_export_, "physical", "ontology") ||
                same_dirs (note, virts_.at (x), "yer actual", shadow_.at (x), yer_root_, "shadow", "root") ||
                same_dirs (note, virts_.at (x), "yer actual", shadow_.at (x), yer_shadow_, "shadow", "shadow") ||
                same_dirs (note, virts_.at (x), "yer actual", shadow_.at (x), yer_export_, "shadow", "ontology") ||
                same_dirs (note, virts_.at (x), "yer actual", export_.at (x), yer_root_, "ontology", "root") ||
                same_dirs (note, virts_.at (x), "yer actual", export_.at (x), yer_shadow_, "ontology", "shadow") ||
                same_dirs (note, virts_.at (x), "yer actual", export_.at (x), yer_export_, "ontology", "ontology") ||
                same_dirs (note, virts_.at (x), virts_.at (x), phys_.at (x), shadow_.at (x), "physical", "shadow") ||
                same_dirs (note, virts_.at (x), virts_.at (x), phys_.at (x), export_.at (x), "physical", "ontology") ||
                same_dirs (note, virts_.at (x), virts_.at (x), shadow_.at (x), export_.at (x), "shadow", "ontology");
        for (::std::size_t y = x+1; (! stop) && (y < virts_.size ()); ++y)
            stop =  same_dirs (note, virts_.at (x), virts_.at (y), phys_.at (x), phys_.at (y), "physical", "physical") ||
                    same_dirs (note, virts_.at (x), virts_.at (y), phys_.at (x), shadow_.at (y), "physical", "shadow") ||
                    same_dirs (note, virts_.at (x), virts_.at (y), phys_.at (x), export_.at (y), "physical", "ontology") ||
                    same_dirs (note, virts_.at (x), virts_.at (y), shadow_.at (x), phys_.at (y), "shadow", "physical") ||
                    same_dirs (note, virts_.at (x), virts_.at (y), shadow_.at (x), shadow_.at (y), "shadow", "shadow") ||
                    same_dirs (note, virts_.at (x), virts_.at (y), shadow_.at (x), export_.at (y), "shadow", "ontology") ||
                    same_dirs (note, virts_.at (x), virts_.at (y), export_.at (x), phys_.at (y), "ontology", "physical") ||
                    same_dirs (note, virts_.at (x), virts_.at (y), export_.at (x), shadow_.at (y), "ontology", "shadow") ||
                    same_dirs (note, virts_.at (x), virts_.at (y), export_.at (x), export_.at (y), "ontology", "export"); }
    stat_note_ -> SetLabel (note.c_str ()); }

void vv_t :: reval ()
{	PRESUME (! invalid (), __FILE__, __LINE__);
    const int sel = choice_for_ -> GetSelection ();
    PRESUME (sel < GSL_NARROW_CAST < int > (vvfix_.size ()), __FILE__, __LINE__);
    PRESUME (sel < GSL_NARROW_CAST < int > (vvextra_.size ()), __FILE__, __LINE__);
    const int vv = val_.sel ();
    const ::std::string txt (val_.text_ -> GetValue ());
    if (sel < 0) val_.add_ -> Enable (false);
    if ((sel < 0) || (vv < 0))
    {   val_.erase_ -> Enable (false);        
        val_.rename_ -> Enable (false); }       
    else
    {   const bool bes = (vv >= GSL_NARROW_CAST < int > (vvfix_.at (sel).size ()));
        val_.erase_ -> Enable (bes);
        if (val_.rename_ -> IsEnabled ()) // already tested by listedit
            val_.rename_ -> Enable (bes && ! txt.empty ()); } }

bool vv_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    virt_.preload (virts_);
    en_virt ();
    vstr_t vv (*vvfix_.cbegin ());
    for (auto& x : *vvextra_.cbegin ()) if (! x.empty ()) vv.push_back (x);
    val_.preload (vv);
    if (prior_ == wxNOT_FOUND) prior_ = 0;
    choice_for_ -> Select (prior_); 
    repopulate ();
    return true; }

bool vv_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
    virts_ = virt_.unload < vstr_t > ();
    part_de_virt (pvirt_);	
    depopulate ();
    return true; }

bool vv_t :: create_panel (wxWindow *mummy, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{	PRESUME (invalid_panel (), __FILE__, __LINE__);
    create_box (mummy, pos, size);
    if (! create_panel_itself (mummy, id, pos, size, style)) return false;
    create_controls (panel_);
    if (invalid_panel ()) return false;
    panel_ -> SetSizer (box_);
    panel_ -> Layout ();
    box_ -> Fit (panel_);
    return true; }

template < class Z, e_type T > void vv_t :: vvfox (::std::size_t& count, const context_t& c, const ::std::size_t from)
{   vvfix_.push_back (vstr_t ());
    vvextra_.push_back (vstr_t ());
    PRESUME (vvfix_.size () > count, __FILE__, __LINE__);
    for (::std::size_t x = from; x < type_master < T > :: value_count (); ++x)
    {   const ::std::string& cc = type_master < T > :: name (GSL_NARROW_CAST < Z > (x));
        if (! cc.empty ()) vvfix_.at (count).push_back (cc); }
    for (auto& cc : c.vvext (T))
        if (! cc.empty ())
            vvextra_.at (count).push_back (cc);
    ++count; }

template < class Z, class T > void vv_t :: vvfox (::std::size_t& count, const ::std::size_t from, const ::std::size_t to, const vstr_t& feed)
{   vvfix_.push_back (vstr_t ());
    vvextra_.push_back (vstr_t ());
    PRESUME (vvfix_.size () > count, __FILE__, __LINE__);
    for (::std::size_t x = from; x < to; ++x)
    {   const ::std::string& cc = Z::name (GSL_NARROW_CAST < T > (x));
        if (! cc.empty ()) vvfix_.at (count).push_back (cc); }
    for (auto& cc : feed)
        vvextra_.at (count).push_back (cc);
    ++count; }

void vv_t :: load_from_context (const context_t& c)
{   ::std::size_t count = 0;
    virts_.clear (); phys_.clear (); export_.clear (); virts_.clear ();
    const ::std::size_t mx = c.virtuals ().size ();
    if (mx > 0)
    {   msid_t ss;
        vstr_t vs;
        vbp_t ps, shs, exs;
        vs.reserve (mx);
        ps.reserve (mx);
        for (::std::size_t n = 0; n < mx; ++n)
        {   const ::std::string s = c.virtuals ().at (n);
            if (s.size () > 0)
            {   const ::std::string::size_type pos = s.find_first_of ('=');
                if ((pos > 0) && (pos < s.length () - 1))
                {   const ::std::string lhs = s.substr (0, pos);
                    const ::std::string rhs = s.substr (pos+1);
                    if (ss.find (lhs) == ss.cend ())
                    {   vs.push_back (lhs);
                        ps.push_back (rhs);
                        ss.insert (::std::pair (lhs, vs.size () - 1)); } } } }
        shs.resize (vs.size ());
        exs.resize (vs.size ());
        for (auto& s : c.exports ())
        {   const ::std::string::size_type pos = s.find_first_of ('=');
            if ((pos > 0) && (pos < s.length () - 1))
            {   const ::std::string lhs = s.substr (0, pos);
                const ::std::string rhs = s.substr (pos+1);
                msid_t::const_iterator i = ss.find (lhs);
                if (i != ss.cend ())
                    exs.at (i -> second) = rhs; } }
        for (auto& s : c.shadows ())
        {   const ::std::string::size_type pos = s.find_first_of ('=');
            if ((pos > 0) && (pos < s.length () - 1))
            {   const ::std::string lhs = s.substr (0, pos);
                const ::std::string rhs = s.substr (pos+1);
                msid_t::const_iterator i = ss.find (lhs);
                if (i != ss.cend ())
                    shs.at (i -> second) = rhs; } }
        virts_ = vs;
        phys_ = ps;
        export_ = exs;
        shadow_ = shs; }
    const paths_root& pr = paths_root :: virtual_roots ();
    for (::std::size_t i = 1; i < pr.size (); ++i)
    {   export_.emplace_back (pr.at (i) -> get_export ());   
        phys_.emplace_back (pr.at (i) -> get_disk_path ());
        shadow_.emplace_back (pr.at (i) -> shadow_root ());
        virts_.emplace_back (pr.at (i) -> get_site_path ()); }
 
    vvfox < attr, e_attribute > (count, first_attribute, last_attribute, c.attrib ());
    vvfox < e_charset, t_charset > (count, c);    
    vvfox < e_fixedcolour, t_fixedcolour > (count, c);
    vvfox < e_country, t_country > (count, c);
    vvfox < e_currency, t_currency > (count, c);
    vvfox < e_dingbat, t_dingbat > (count, c);
    vvfox < elem, e_element > (count, first_element_tag, last_element_tag, c.elem ());

    vvfox < e_format, t_format > (count, c);
    vvfox < e_css_font_feature, t_css_font_feature > (count, c);
    vvfox < e_css_font_variation, t_css_font_variation > (count, c);
    vvfox < e_httpequiv, t_httpequiv > (count, c);
    vvfox < e_lang, t_lang > (count, c);
    vvfox < e_metaname, t_metaname > (count, c);
    vvfox < e_mimetype, t_mime > (count, c);
    vvfox < e_sgml, t_sgml > (count, c);

    vvfox < e_abfmt, t_abfmt > (count, c);
    vvfox < e_accrual_method, t_accrual_method > (count, c);
    vvfox < e_accrual_periodicity, t_accrual_periodicity > (count, c);
    vvfox < e_accrual_policy, t_accrual_policy > (count, c);
    vvfox < e_action, t_action > (count, c);
    vvfox < e_align3, t_align3 > (count, c);
    vvfox < e_alignment_baseline, t_alignment_baseline > (count, c);
    vvfox < e_alignplus, t_alignplus > (count, c);
    vvfox < e_as, t_as > (count, c);
    vvfox < e_as_units, t_as_units > (count, c);
    vvfox < e_attr_unit, t_attr_unit > (count, c);
    vvfox < e_autocapitalise, t_autocapitalise > (count, c);
    vvfox < e_autocomplete, t_autocomplete > (count, c);
    vvfox < e_baselineshift, t_baselineshift > (count, c);
    vvfox < e_cachekey, t_cachekey > (count, c);
    vvfox < e_celnrs, t_celnrs > (count, c);
    vvfox < e_citype, t_citype > (count, c);
    vvfox < e_cntype, t_cntype > (count, c);
    vvfox < e_colour_interpolation, t_colour_interpolation > (count, c);
    vvfox < e_colour_rendering, t_colour_rendering > (count, c);
    vvfox < e_cookieid, t_cookieid > (count, c);
    vvfox < e_command2, t_command2 > (count, c);
    vvfox < e_copy, t_copy > (count, c);
    vvfox < e_comp_op, t_comp_op > (count, c);
    vvfox < e_composite_operator, t_composite_operator > (count, c);
    vvfox < e_cr_fileproperty, t_cr_fileproperty > (count, c);
    vvfox < e_crossout, t_crossout > (count, c);
    vvfox < e_crs_whitebalance, t_crs_whitebalance > (count, c);
    vvfox < e_css_aaalri, t_css_aaalri > (count, c);
    vvfox < e_css_absolute_size, t_css_absolute_size > (count, c);
    vvfox < e_css_align_content, t_css_align_content > (count, c);
    vvfox < e_css_align_items, t_css_align_items > (count, c);
    vvfox < e_css_all_2, t_css_all_2 > (count, c);
    vvfox < e_css_appearance, t_css_appearance > (count, c);
    vvfox < e_css_azimuth_e, t_css_azimuth_e > (count, c);
    vvfox < e_css_background_attachment, t_css_background_attachment > (count, c);
    vvfox < e_css_background_repeat, t_css_background_repeat > (count, c);
    vvfox < e_css_blend_mode, t_css_blend_mode > (count, c);
    vvfox < e_css_border_style, t_css_border_style > (count, c);
    vvfox < e_css_border_width, t_css_border_width > (count, c);
    vvfox < e_css_box_alignself_mess, t_css_box_alignself_mess > (count, c);
    vvfox < e_css_box_snap, t_css_box_snap > (count, c);
    vvfox < e_css_break, t_css_break > (count, c);
    vvfox < e_css_break_inside, t_css_break_inside > (count, c);
    vvfox < e_css_caret_shape, t_css_caret_shape > (count, c);
    vvfox < e_css_clear, t_css_clear > (count, c);
    vvfox < e_css_contain_e, t_css_contain_e > (count, c);
    vvfox < e_css_content_enum, t_css_content_enum > (count, c);
    vvfox < e_css_container_feature, t_css_container_feature > (count, c);
    vvfox < e_css_content_position, t_css_content_position > (count, c);
    vvfox < e_css_continue, t_css_continue > (count, c);
    vvfox < e_css_coord_box, t_css_coord_box > (count, c);
    vvfox < e_css_control_break, t_css_control_break > (count, c);
    vvfox < e_css_counter_style, t_css_counter_style > (count, c);
    vvfox < e_css_cursor_e, t_css_cursor_e > (count, c);
    vvfox < e_css_display, t_css_display > (count, c);
    vvfox < e_css_display_inside, t_css_display_inside > (count, c);
    vvfox < e_css_display_internal, t_css_display_internal > (count, c);
    vvfox < e_css_elevation_e, t_css_elevation_e > (count, c);
    vvfox < e_css_float, t_css_float > (count, c);
    vvfox < e_css_fn, t_css_fn > (count, c);
    vvfox < e_css_font_display, t_css_font_display > (count, c);
    vvfox < e_css_font_feature, t_css_font_feature > (count, c);
    vvfox < e_css_font_format, t_css_font_format > (count, c);
    vvfox < e_css_font_size_adjust_e, t_css_font_size_adjust_e > (count, c);
    vvfox < e_css_font_tech, t_css_font_tech > (count, c);
    vvfox < e_css_font_variation, t_css_font_variation > (count, c);
    vvfox < e_css_font_weight, t_css_font_weight > (count, c);
    vvfox < e_css_generic_family, t_css_generic_family > (count, c);
    vvfox < e_css_hll, t_css_hll > (count, c);
    vvfox < e_css_inline_bem_1, t_css_inline_bem_1 > (count, c);
    vvfox < e_css_inline_bem_2, t_css_inline_bem_2 > (count, c);
    vvfox < e_css_justify_content, t_css_justify_content > (count, c);
    vvfox < e_css_layout_box, t_css_layout_box > (count, c);
    vvfox < e_css_line_break, t_css_line_break > (count, c);
    vvfox < e_css_list_style_position, t_css_list_style_position > (count, c);
    vvfox < e_css_list_style_type, t_css_list_style_type > (count, c);
    vvfox < e_css_module, t_css_module > (count, c);
    vvfox < e_css_paint_box, t_css_paint_box > (count, c);
    vvfox < e_css_overflow, t_css_overflow > (count, c);
    vvfox < e_css_size_e, t_css_size_e > (count, c);
    vvfox < e_css_sizing, t_css_sizing > (count, c);
    vvfox < e_css_pause_3_e, t_css_pause_3_e > (count, c);
    vvfox < e_css_pitch_e, t_css_pitch_e > (count, c);
    vvfox < e_css_position, t_css_position > (count, c);
    vvfox < e_css_ray_size, t_css_ray_size > (count, c);
    vvfox < e_css_rgb_xyz, t_css_rgb_xyz > (count, c);
    vvfox < e_css_rect, t_css_rect > (count, c);
    vvfox < e_css_relative_size, t_css_relative_size > (count, c);
    vvfox < e_css_resize, t_css_resize > (count, c);
    vvfox < e_css_ss_type_e, t_css_ss_type_e > (count, c);
    vvfox < e_css_self_position, t_css_self_position > (count, c);
    vvfox < e_css_speak_as_e, t_css_speak_as_e > (count, c);
    vvfox < e_css_statement, t_css_statement > (count, c);
    vvfox < e_css_speech_rate_e, t_css_speech_rate_e > (count, c);
    vvfox < e_css_system_e, t_css_system_e > (count, c);
    vvfox < e_css_text_align, t_css_text_align > (count, c);
    vvfox < e_css_text_align_all, t_css_text_align_all > (count, c);
    vvfox < e_css_text_align_last, t_css_text_align_last > (count, c);
    vvfox < e_css_text_autospace, t_css_text_autospace > (count, c);
    vvfox < e_css_text_decoration, t_css_text_decoration > (count, c);
    vvfox < e_css_text_transform, t_css_text_transform > (count, c);
    vvfox < e_css_textdec_line_e, t_css_textdec_line_e > (count, c);
    vvfox < e_css_textdec_style, t_css_textdec_style > (count, c);
    vvfox < e_css_textemph_shape, t_css_textemph_shape > (count, c);
    vvfox < e_css_transform_box, t_css_transform_box > (count, c);
    vvfox < e_css_user_select, t_css_user_select > (count, c);
    vvfox < e_css_text_wrap, t_css_text_wrap > (count, c);
    vvfox < e_css_val_fn, t_css_val_fn > (count, c);
    vvfox < e_css_version, t_css_version > (count, c);
    vvfox < e_css_vertical_align, t_css_vertical_align > (count, c);
    vvfox < e_css_visual_box, t_css_visual_box > (count, c);
    vvfox < e_css_voice_balance_e, t_css_voice_balance_e > (count, c);
    vvfox < e_css_volume_e, t_css_volume_e > (count, c);
    vvfox < e_css_whitespace, t_css_whitespace > (count, c);
    vvfox < e_css_wide, t_css_wide > (count, c);
    vvfox < e_css_wrap_flow, t_css_wrap_flow > (count, c);
    vvfox < e_css_wsc, t_css_wsc > (count, c);
    vvfox < e_css_wst, t_css_wst > (count, c);
    vvfox < e_cursor, t_cursor > (count, c);
    vvfox < e_decalign, t_decalign > (count, c);
    vvfox < e_determiner, t_determiner > (count, c);
    vvfox < e_dingbat, t_dingbat > (count, c);
    vvfox < e_dir, t_dir > (count, c);
    vvfox < e_display_align, t_display_align > (count, c);
    vvfox < e_dominantbaseline, t_dominantbaseline > (count, c);
    vvfox < e_enterkeyhint, t_enterkeyhint > (count, c);
    vvfox < e_evt_action, t_evt_action > (count, c);
    vvfox < e_figalign, t_figalign > (count, c);
    vvfox < e_filter_in, t_filter_in > (count, c);
    vvfox < e_fontname, t_fontname > (count, c);
    vvfox < e_font_enum, t_font_enum > (count, c);
    vvfox < e_font_variant_2, t_font_variant_2 > (count, c);
    vvfox < e_font_variant_caps, t_font_variant_caps > (count, c);
    vvfox < e_font_variant_east_asian, t_font_variant_east_asian > (count, c);
    vvfox < e_font_variant_ligature, t_font_variant_ligature > (count, c);
    vvfox < e_font_variant_numeric, t_font_variant_numeric > (count, c);
    vvfox < e_formaturi, t_formaturi > (count, c);
    vvfox < e_halign, t_halign > (count, c);
    vvfox < e_icalfreq, t_icalfreq > (count, c);
    vvfox < e_image_rendering, t_image_rendering > (count, c);
    vvfox < e_icc, t_icc > (count, c);
    vvfox < e_indentalign, t_indentalign > (count, c);
    vvfox < e_inky, t_inky > (count, c);
    vvfox < e_inputmode, t_inputmode > (count, c);
    vvfox < e_inputplus, t_inputplus > (count, c);
    vvfox < e_inputtype, t_inputtype > (count, c);
    vvfox < e_inputtype3, t_inputtype3 > (count, c);
    vvfox < e_inputtype32, t_inputtype32 > (count, c);
    vvfox < e_inputtype4, t_inputtype4 > (count, c);
    vvfox < e_inputtype5, t_inputtype5 > (count, c);
    vvfox < e_jtoken, t_jtoken > (count, c);
    vvfox < e_kind, t_kind > (count, c);
    vvfox < e_length_absolute, t_length_absolute > (count, c);
    vvfox < e_length_relative, t_length_relative > (count, c);
    vvfox < e_linebreak, t_linebreak > (count, c);
    vvfox < e_linkparam, t_linkparam > (count, c);
    vvfox < e_listtype, t_listtype > (count, c);
    vvfox < e_lrnialign, t_lrnialign > (count, c);
    vvfox < e_longdivstyle, t_longdivstyle > (count, c);
    vvfox < e_mah, t_mah > (count, c);
    vvfox < e_mathalign, t_mathalign > (count, c);
    vvfox < e_mathlocation, t_mathlocation > (count, c);
    vvfox < e_mathnotation, t_mathnotation > (count, c);
    vvfox < e_mathoverflow, t_mathoverflow > (count, c);
    vvfox < e_mathvariant, t_mathvariant > (count, c);
    vvfox < e_math_version, t_math_version > (count, c);
    vvfox < e_matrixtype, t_matrixtype > (count, c);
    vvfox < e_method, t_method > (count, c);
    vvfox < e_mf_identifier, t_mf_identifier > (count, c);
    vvfox < e_mf_itemtype, t_mf_itemtype > (count, c);
    vvfox < e_mf_listing_action, t_mf_listing_action > (count, c);
    vvfox < e_mf_method, t_mf_method > (count, c);
    vvfox < e_mf_reviewtype, t_mf_reviewtype > (count, c);
    vvfox < e_month_english_long, t_month_english_long > (count, c);
    vvfox < e_month_english_short, t_month_english_short > (count, c);
    vvfox < e_musickey, t_musickey > (count, c);
    vvfox < e_myersbriggs, t_myersbriggs > (count, c);
    vvfox < e_namedspace, t_namedspace > (count, c);
    vvfox < e_namespace, t_namespace > (count, c);
    vvfox < e_nit_macro, t_nit_macro > (count, c);
    vvfox < e_nit_section, t_nit_section > (count, c);
    vvfox < e_ogtype, t_ogtype > (count, c);
    vvfox < e_page_orientation, t_page_orientation > (count, c);
    vvfox < e_paintkeyword, t_paintkeyword > (count, c);
    vvfox < e_pam_ccv, t_pam_ccv > (count, c);
    vvfox < e_pcmm_status, t_pcmm_status > (count, c);
    vvfox < e_pointer_events, t_pointer_events > (count, c);
    vvfox < e_pri_img_colour, t_pri_img_colour > (count, c);
    vvfox < e_pri_img_technique, t_pri_img_technique > (count, c);
    vvfox < e_pri_img_viewpoint, t_pri_img_viewpoint > (count, c);
    vvfox < e_print, t_print > (count, c);
    vvfox < e_prism_ad_pos, t_prism_ad_pos > (count, c);
    vvfox < e_prism_ad_type, t_prism_ad_type > (count, c);
    vvfox < e_prism_ag_type, t_prism_ag_type > (count, c);
    vvfox < e_prism_audience_sector, t_prism_audience_sector > (count, c);
    vvfox < e_prism_ccv, t_prism_ccv > (count, c);
    vvfox < e_prism_class, t_prism_class > (count, c);
    vvfox < e_prism_contenttype, t_prism_contenttype > (count, c);
    vvfox < e_prism_cvp, t_prism_cvp > (count, c);
    vvfox < e_prism_genre, t_prism_genre > (count, c);
    vvfox < e_prism_icv, t_prism_icv > (count, c);
    vvfox < e_prism_pasv, t_prism_pasv > (count, c);
    vvfox < e_prism_pcv, t_prism_pcv > (count, c);
    vvfox < e_prism_pfv, t_prism_pfv > (count, c);
    vvfox < e_prism_ptv, t_prism_ptv > (count, c);
    vvfox < e_prism_rcv, t_prism_rcv > (count, c);
    vvfox < e_prism_role, t_prism_role > (count, c);
    vvfox < e_prs_action, t_prs_action > (count, c);
    vvfox < e_quote_style, t_quote_style > (count, c);
    vvfox < e_recipe_content, t_recipe_content > (count, c);
    vvfox < e_recipe_course, t_recipe_course > (count, c);
    vvfox < e_recipe_cuisine, t_recipe_cuisine > (count, c);
    vvfox < e_recipe_dietary, t_recipe_dietary > (count, c);
    vvfox < e_recipe_dish, t_recipe_dish > (count, c);
    vvfox < e_recipe_exclusion, t_recipe_exclusion > (count, c);
    vvfox < e_recipe_kit, t_recipe_kit > (count, c);
    vvfox < e_recipe_meal, t_recipe_meal > (count, c);
    vvfox < e_recipe_method, t_recipe_method > (count, c);
    vvfox < e_recipe_source, t_recipe_source > (count, c);
    vvfox < e_recipe_special, t_recipe_special > (count, c);
    vvfox < e_recipe_time, t_recipe_time > (count, c);
    vvfox < e_referrer, t_referrer > (count, c);
    vvfox < e_rendering_in_tents, t_rendering_in_tents > (count, c);
    vvfox < e_report, t_report > (count, c);
    vvfox < e_rules, t_rules > (count, c);
    vvfox < e_sandbox, t_sandbox > (count, c);
    vvfox < e_scei, t_scei > (count, c);
    vvfox < e_severity, t_severity > (count, c);
    vvfox < e_shadow, t_shadow > (count, c);
    vvfox < e_shape7, t_shape7 > (count, c);
    vvfox < e_shape_rendering, t_shape_rendering > (count, c);
    vvfox < e_smei, t_smei > (count, c);
    vvfox < e_ssi, t_ssi > (count, c);
    vvfox < e_ssi_comparison, t_ssi_comparison > (count, c);
    vvfox < e_ssi_config, t_ssi_config > (count, c);
    vvfox < e_ssi_encoding, t_ssi_encoding > (count, c);
    vvfox < e_ssi_env, t_ssi_env > (count, c);
    vvfox < e_step_position, t_step_position > (count, c);
    vvfox < e_stress, t_stress > (count, c);
    vvfox < e_supports, t_supports > (count, c);
    vvfox < e_svg_align, t_svg_align > (count, c);
    vvfox < e_svg_display, t_svg_display > (count, c);
    vvfox < e_svg_fontstretch, t_svg_fontstretch > (count, c);
    vvfox < e_svg_fontstretch_ff, t_svg_fontstretch_ff > (count, c);
    vvfox < e_svg_fontstyle, t_svg_fontstyle > (count, c);
    vvfox < e_svg_fontweight, t_svg_fontweight > (count, c);
    vvfox < e_svg_fontweight_ff, t_svg_fontweight_ff > (count, c);
    vvfox < e_svg_mode, t_svg_mode > (count, c);
    vvfox < e_svg_overflow, t_svg_overflow > (count, c);
    vvfox < e_svg_rendering_intent, t_svg_rendering_intent > (count, c);
    vvfox < e_svg_type, t_svg_type > (count, c);
    vvfox < e_svg_version, t_svg_version > (count, c);
    vvfox < e_svg_version_grand, t_svg_version_grand > (count, c);
    vvfox < e_tableframe, t_tableframe > (count, c);
    vvfox < e_tblri, t_tblri > (count, c);
    vvfox < e_text_decoration, t_text_decoration > (count, c);
    vvfox < e_text_rendering, t_text_rendering > (count, c);
    vvfox < e_tld, t_tld > (count, c);
    vvfox < e_transform_anim, t_transform_anim > (count, c);
    vvfox < e_transformbehaviour, t_transformbehaviour > (count, c);
    vvfox < e_transform_fn, t_transform_fn > (count, c);
    vvfox < e_turbulence_type, t_turbulence_type > (count, c);
    vvfox < e_unit, t_unit > (count, c);
    vvfox < e_unit_abs_len, t_unit_abs_len > (count, c);
    vvfox < e_unit_angle, t_unit_angle > (count, c);
    vvfox < e_unit_freq, t_unit_freq > (count, c);
    vvfox < e_unit_rel_len, t_unit_rel_len > (count, c);
    vvfox < e_unit_res, t_unit_res > (count, c);
    vvfox < e_unit_time, t_unit_time > (count, c);
    vvfox < e_unicode_bidi, t_unicode_bidi > (count, c);
    vvfox < e_vector_effect_2, t_vector_effect_2 > (count, c);
    vvfox < e_vertical_align_enum, t_vertical_align_enum > (count, c);
    vvfox < e_vgender, t_vgender > (count, c);
    vvfox < e_vrel, t_vrel > (count, c);
    vvfox < e_vctelecomms, t_vctelecomms > (count, c);
    vvfox < e_weekday_english_long, t_weekday_english_long > (count, c);
    vvfox < e_weekday_english_short, t_weekday_english_short > (count, c);
    vvfox < e_whitespace, t_whitespace > (count, c);
    vvfox < e_writingmode, t_writingmode > (count, c);
    vvfox < e_xmlns, t_xmlns > (count, c);
    vvfox < e_xmpdm_audio_channel, t_xmpdm_audio_channel > (count, c);
    vvfox < e_xmpdm_audio_sample, t_xmpdm_audio_sample > (count, c);
    vvfox < e_xmpdm_camera_angle, t_xmpdm_camera_angle > (count, c);
    vvfox < e_xmpdm_camera_move, t_xmpdm_camera_move > (count, c);
    vvfox < e_xmpdm_pulldown, t_xmpdm_pulldown > (count, c);
    vvfox < e_xmpdm_shotsize, t_xmpdm_shotsize > (count, c);
    vvfox < e_xmpdm_stretchmode, t_xmpdm_stretchmode > (count, c);
    vvfox < e_xmpdm_time_format, t_xmpdm_time_format > (count, c);
    vvfox < e_xmpdm_time_signature, t_xmpdm_time_signature > (count, c);
    vvfox < e_xmpdm_video_pixeldepth, t_xmpdm_video_pixeldepth > (count, c); }

template < e_type T > void vv_t :: foxvv (::std::size_t& count, context_t& c, const ::std::size_t let) const
{   type_master < T >::remove_any_extras ();
    for (::std::size_t x = let; x < vvextra_.at (count).size (); ++x)
    {   const ::std::string& s = vvextra_.at (count).at (x);
        if (! type_master < T >::exists (s))
            type_master < T >::extend (s, x); }
    c.vvext (T, vvextra_.at (count));
    ++count; }

template < class Z > vstr_t vv_t :: foxvv (::std::size_t& count, const ::std::size_t let) const
{   Z::remove_any_extras ();
    for (::std::size_t x = let; x < vvextra_.at (count).size (); ++x)
    {   const ::std::string& s = vvextra_.at (count).at (x);
        if (! Z::exists (s)) \
            Z::extend (s, x); }
    return vvextra_.at (count++); }

void vv_t :: save_to_context (context_t& c) const
{	PRESUME (virts_.size () == phys_.size (), __FILE__, __LINE__);
    PRESUME (virts_.size () == export_.size (), __FILE__, __LINE__);
    PRESUME (virts_.size () == shadow_.size (), __FILE__, __LINE__);

    if (virts_.size () > 0)
    {   vstr_t exps, shads, vs;
        exps.reserve (virts_.size ());
        shads.reserve (virts_.size ());
        vs.reserve (virts_.size ());
        for (::std::size_t n = 0; n < virts_.size (); ++n)
        {   ::std::string arse (virts_.at (n));
            arse += "=";
            vs.push_back (arse + canonical_name (absolute_name (phys_.at (n))).string ());
            if (export_.at (n).empty ()) exps.push_back (::std::string ());
            else exps.push_back (arse + canonical_name (absolute_name (export_.at (n))).string ());
            if (shadow_.at (n).empty ()) shads.push_back (::std::string ());
            else shads.push_back (arse + canonical_name (absolute_name (shadow_.at (n))).string ()); }
        c.virtuals (vs);
        c.shadows (shads);
        c.exports (exps); }
    ::std::size_t count = 0;

    c.attrib (foxvv < attr > (count));
    foxvv < t_charset > (count, c);
    foxvv < t_fixedcolour > (count, c);
    foxvv < t_country > (count, c);
    foxvv < t_currency > (count, c);
    foxvv < t_dingbat > (count, c);
    c.elem (foxvv < elem > (count, 1));

    foxvv < t_format > (count, c);
    foxvv < t_css_font_feature > (count, c);
    foxvv < t_css_font_variation > (count, c);
    foxvv < t_httpequiv > (count, c);
    foxvv < t_lang > (count, c);
    foxvv < t_metaname  > (count, c);
    foxvv < t_mime > (count, c);
    foxvv < t_sgml > (count, c);

    foxvv < t_abfmt > (count, c);
    foxvv < t_accrual_method > (count, c);
    foxvv < t_accrual_periodicity > (count, c);
    foxvv < t_accrual_policy > (count, c);
    foxvv < t_action > (count, c);
    foxvv < t_align3 > (count, c);
    foxvv < t_alignment_baseline > (count, c);
    foxvv < t_alignplus > (count, c);
    foxvv < t_as > (count, c);
    foxvv < t_as_units > (count, c);
    foxvv < t_attr_unit > (count, c);
    foxvv < t_autocapitalise > (count, c);
    foxvv < t_autocomplete > (count, c);
    foxvv < t_baselineshift > (count, c);
    foxvv < t_cachekey > (count, c);
    foxvv < t_celnrs > (count, c);
    foxvv < t_citype > (count, c);
    foxvv < t_colour_interpolation > (count, c);
    foxvv < t_colour_rendering > (count, c);
    foxvv < t_cookieid > (count, c);
    foxvv < t_copy > (count, c);
    foxvv < t_cntype > (count, c);
    foxvv < t_comp_op > (count, c);
    foxvv < t_composite_operator > (count, c);
    foxvv < t_cr_fileproperty > (count, c);
    foxvv < t_crossout > (count, c);
    foxvv < t_crs_whitebalance > (count, c);
    foxvv < t_css_aaalri > (count, c);
    foxvv < t_css_absolute_size > (count, c);
    foxvv < t_css_align_content > (count, c);
    foxvv < t_css_align_items > (count, c);
    foxvv < t_css_all_2 > (count, c);
    foxvv < t_css_appearance > (count, c);
    foxvv < t_css_azimuth_e > (count, c);
    foxvv < t_css_background_attachment > (count, c);
    foxvv < t_css_background_repeat > (count, c);
    foxvv < t_css_blend_mode > (count, c);
    foxvv < t_css_border_style > (count, c);
    foxvv < t_css_border_width > (count, c);
    foxvv < t_css_box_alignself_mess > (count, c);
    foxvv < t_css_box_snap > (count, c);
    foxvv < t_css_break > (count, c);
    foxvv < t_css_break_inside > (count, c);
    foxvv < t_css_caret_shape > (count, c);
    foxvv < t_css_clear > (count, c);
    foxvv < t_css_contain_e > (count, c);
    foxvv < t_css_content_enum > (count, c);
    foxvv < t_css_container_feature > (count, c);
    foxvv < t_css_content_position > (count, c);
    foxvv < t_css_continue > (count, c);
    foxvv < t_css_coord_box > (count, c);
    foxvv < t_css_control_break > (count, c);
    foxvv < t_css_counter_style > (count, c);
    foxvv < t_css_cursor_e > (count, c);
    foxvv < t_css_display > (count, c);
    foxvv < t_css_display_inside > (count, c);
    foxvv < t_css_display_internal > (count, c);
    foxvv < t_css_elevation_e > (count, c);
    foxvv < t_css_float > (count, c);
    foxvv < t_css_fn > (count, c);
    foxvv < t_css_font_display > (count, c);
    foxvv < t_css_font_feature > (count, c);
    foxvv < t_css_font_format > (count, c);
    foxvv < t_css_font_size_adjust_e > (count, c);
    foxvv < t_css_font_tech > (count, c);
    foxvv < t_css_font_variation > (count, c);
    foxvv < t_css_font_weight > (count, c);
    foxvv < t_css_generic_family > (count, c);
    foxvv < t_css_hll > (count, c);
    foxvv < t_css_inline_bem_1 > (count, c);
    foxvv < t_css_inline_bem_2 > (count, c);
    foxvv < t_css_justify_content > (count, c);
    foxvv < t_css_layout_box > (count, c);
    foxvv < t_css_line_break > (count, c);
    foxvv < t_css_list_style_position > (count, c);
    foxvv < t_css_list_style_type > (count, c);
    foxvv < t_css_module > (count, c);
    foxvv < t_css_paint_box > (count, c);
    foxvv < t_css_overflow > (count, c);
    foxvv < t_css_size_e > (count, c);
    foxvv < t_css_sizing > (count, c);
    foxvv < t_css_pause_3_e > (count, c);
    foxvv < t_css_pitch_e > (count, c);
    foxvv < t_css_position > (count, c);
    foxvv < t_css_ray_size > (count, c);
    foxvv < t_css_rgb_xyz > (count, c);
    foxvv < t_css_rect > (count, c);
    foxvv < t_css_relative_size > (count, c);
    foxvv < t_css_resize > (count, c);
    foxvv < t_css_ss_type_e > (count, c);
    foxvv < t_css_self_position > (count, c);
    foxvv < t_css_speak_as_e > (count, c);
    foxvv < t_css_statement > (count, c);
    foxvv < t_css_speech_rate_e > (count, c);
    foxvv < t_css_system_e > (count, c);
    foxvv < t_css_text_align > (count, c);
    foxvv < t_css_text_align_all > (count, c);
    foxvv < t_css_text_align_last > (count, c);
    foxvv < t_css_text_autospace > (count, c);
    foxvv < t_css_text_decoration > (count, c);
    foxvv < t_css_text_transform > (count, c);
    foxvv < t_css_textdec_line_e > (count, c);
    foxvv < t_css_textdec_style > (count, c);
    foxvv < t_css_textemph_shape > (count, c);
    foxvv < t_css_transform_box > (count, c);
    foxvv < t_css_user_select > (count, c);
    foxvv < t_css_text_wrap > (count, c);
    foxvv < t_css_val_fn > (count, c);
    foxvv < t_css_version > (count, c);
    foxvv < t_css_vertical_align > (count, c);
    foxvv < t_css_visual_box > (count, c);
    foxvv < t_css_voice_balance_e > (count, c);
    foxvv < t_css_volume_e > (count, c);
    foxvv < t_css_whitespace > (count, c);
    foxvv < t_css_wide > (count, c);
    foxvv < t_css_wrap_flow > (count, c);
    foxvv < t_css_wsc > (count, c);
    foxvv < t_css_wst > (count, c);
    foxvv < t_cursor > (count, c);
    foxvv < t_decalign > (count, c);
    foxvv < t_determiner > (count, c);
    foxvv < t_dingbat > (count, c);
    foxvv < t_dir > (count, c);
    foxvv < t_display_align > (count, c);
    foxvv < t_dominantbaseline > (count, c);
    foxvv < t_enterkeyhint > (count, c);
    foxvv < t_evt_action > (count, c);
    foxvv < t_figalign > (count, c);
    foxvv < t_filter_in > (count, c);
    foxvv < t_fontname > (count, c);
    foxvv < t_font_enum > (count, c);
    foxvv < t_font_variant_2 > (count, c);
    foxvv < t_font_variant_caps > (count, c);
    foxvv < t_font_variant_east_asian > (count, c);
    foxvv < t_font_variant_ligature > (count, c);
    foxvv < t_font_variant_numeric > (count, c);
    foxvv < t_formaturi > (count, c);
    foxvv < t_halign > (count, c);
    foxvv < t_icalfreq > (count, c);
    foxvv < t_image_rendering > (count, c);
    foxvv < t_icc > (count, c);
    foxvv < t_indentalign > (count, c);
    foxvv < t_inky > (count, c);
    foxvv < t_inputmode > (count, c);
    foxvv < t_inputplus > (count, c);
    foxvv < t_inputtype > (count, c);
    foxvv < t_inputtype3 > (count, c);
    foxvv < t_inputtype32 > (count, c);
    foxvv < t_inputtype4 > (count, c);
    foxvv < t_inputtype5 > (count, c);
    foxvv < t_jtoken > (count, c);
    foxvv < t_kind > (count, c);
    foxvv < t_length_absolute > (count, c);
    foxvv < t_length_relative > (count, c);
    foxvv < t_linebreak > (count, c);
    foxvv < t_linkparam > (count, c);
    foxvv < t_listtype > (count, c);
    foxvv < t_lrnialign > (count, c);
    foxvv < t_longdivstyle > (count, c);
    foxvv < t_mah > (count, c);
    foxvv < t_mathalign > (count, c);
    foxvv < t_mathlocation > (count, c);
    foxvv < t_mathnotation > (count, c);
    foxvv < t_mathoverflow > (count, c);
    foxvv < t_mathvariant > (count, c);
    foxvv < t_math_version > (count, c);
    foxvv < t_matrixtype > (count, c);
    foxvv < t_method > (count, c);
    foxvv < t_mf_identifier > (count, c);
    foxvv < t_mf_itemtype > (count, c);
    foxvv < t_mf_listing_action > (count, c);
    foxvv < t_mf_method > (count, c);
    foxvv < t_mf_reviewtype > (count, c);
    foxvv < t_month_english_long > (count, c);
    foxvv < t_month_english_short > (count, c);
    foxvv < t_musickey > (count, c);
    foxvv < t_myersbriggs > (count, c);
    foxvv < t_namedspace > (count, c);
    foxvv < t_namespace > (count, c);
    foxvv < t_nit_macro > (count, c);
    foxvv < t_nit_section > (count, c);
    foxvv < t_ogtype > (count, c);
    foxvv < t_page_orientation > (count, c);
    foxvv < t_paintkeyword > (count, c);
    foxvv < t_pam_ccv > (count, c);
    foxvv < t_pcmm_status > (count, c);
    foxvv < t_pointer_events > (count, c);
    foxvv < t_pri_img_colour > (count, c);
    foxvv < t_pri_img_technique > (count, c);
    foxvv < t_pri_img_viewpoint > (count, c);
    foxvv < t_print > (count, c);
    foxvv < t_prism_ad_pos > (count, c);
    foxvv < t_prism_ad_type > (count, c);
    foxvv < t_prism_ag_type > (count, c);
    foxvv < t_prism_audience_sector > (count, c);
    foxvv < t_prism_ccv > (count, c);
    foxvv < t_prism_class > (count, c);
    foxvv < t_prism_contenttype > (count, c);
    foxvv < t_prism_cvp > (count, c);
    foxvv < t_prism_genre > (count, c);
    foxvv < t_prism_icv > (count, c);
    foxvv < t_prism_pasv > (count, c);
    foxvv < t_prism_pcv > (count, c);
    foxvv < t_prism_pfv > (count, c);
    foxvv < t_prism_ptv > (count, c);
    foxvv < t_prism_rcv > (count, c);
    foxvv < t_prism_role > (count, c);
    foxvv < t_prs_action > (count, c);
    foxvv < t_quote_style > (count, c);
    foxvv < t_recipe_content > (count, c);
    foxvv < t_recipe_course > (count, c);
    foxvv < t_recipe_cuisine > (count, c);
    foxvv < t_recipe_dietary > (count, c);
    foxvv < t_recipe_dish > (count, c);
    foxvv < t_recipe_exclusion > (count, c);
    foxvv < t_recipe_kit > (count, c);
    foxvv < t_recipe_meal > (count, c);
    foxvv < t_recipe_method > (count, c);
    foxvv < t_recipe_source > (count, c);
    foxvv < t_recipe_special > (count, c);
    foxvv < t_recipe_time > (count, c);
    foxvv < t_referrer > (count, c);
    foxvv < t_rendering_in_tents > (count, c);
    foxvv < t_report > (count, c);
    foxvv < t_rules > (count, c);
    foxvv < t_sandbox > (count, c);
    foxvv < t_scei > (count, c);
    foxvv < t_severity > (count, c);
    foxvv < t_shadow > (count, c);
    foxvv < t_shape7 > (count, c);
    foxvv < t_shape_rendering > (count, c);
    foxvv < t_smei > (count, c);
    foxvv < t_ssi > (count, c);
    foxvv < t_ssi_comparison > (count, c);
    foxvv < t_ssi_config > (count, c);
    foxvv < t_ssi_encoding > (count, c);
    foxvv < t_ssi_env > (count, c);
    foxvv < t_step_position > (count, c);
    foxvv < t_stress > (count, c);
    foxvv < t_supports > (count, c);
    foxvv < t_svg_align > (count, c);
    foxvv < t_svg_display > (count, c);
    foxvv < t_svg_fontstretch > (count, c);
    foxvv < t_svg_fontstretch_ff > (count, c);
    foxvv < t_svg_fontstyle > (count, c);
    foxvv < t_svg_fontweight > (count, c);
    foxvv < t_svg_fontweight_ff > (count, c);
    foxvv < t_svg_mode > (count, c);
    foxvv < t_svg_overflow > (count, c);
    foxvv < t_svg_rendering_intent > (count, c);
    foxvv < t_svg_type > (count, c);
    foxvv < t_svg_version > (count, c);
    foxvv < t_svg_version_grand > (count, c);
    foxvv < t_tableframe > (count, c);
    foxvv < t_tblri > (count, c);
    foxvv < t_text_decoration > (count, c);
    foxvv < t_text_rendering > (count, c);
    foxvv < t_tld > (count, c);
    foxvv < t_transform_anim > (count, c);
    foxvv < t_transformbehaviour > (count, c);
    foxvv < t_transform_fn > (count, c);
    foxvv < t_turbulence_type > (count, c);
    foxvv < t_unit > (count, c);
    foxvv < t_unit_abs_len > (count, c);
    foxvv < t_unit_angle > (count, c);
    foxvv < t_unit_freq > (count, c);
    foxvv < t_unit_rel_len > (count, c);
    foxvv < t_unit_res > (count, c);
    foxvv < t_unit_time > (count, c);
    foxvv < t_unicode_bidi > (count, c);
    foxvv < t_vector_effect_2 > (count, c);
    foxvv < t_vertical_align_enum > (count, c);
    foxvv < t_vgender > (count, c);
    foxvv < t_vrel > (count, c);
    foxvv < t_vctelecomms > (count, c);
    foxvv < t_weekday_english_long > (count, c);
    foxvv < t_weekday_english_short > (count, c);
    foxvv < t_whitespace > (count, c);
    foxvv < t_writingmode > (count, c);
    foxvv < t_xmlns > (count, c);
    foxvv < t_xmpdm_audio_channel > (count, c);
    foxvv < t_xmpdm_audio_sample > (count, c);
    foxvv < t_xmpdm_camera_angle > (count, c);
    foxvv < t_xmpdm_camera_move > (count, c);
    foxvv < t_xmpdm_pulldown > (count, c);
    foxvv < t_xmpdm_shotsize > (count, c);
    foxvv < t_xmpdm_stretchmode > (count, c);
    foxvv < t_xmpdm_time_format > (count, c);
    foxvv < t_xmpdm_time_signature > (count, c);
    foxvv < t_xmpdm_video_pixeldepth > (count, c); }

#endif // WX
