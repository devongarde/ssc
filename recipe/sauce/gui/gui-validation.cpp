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

//#define BASE_VALID ATTRIB, CHARSET, CLASS, COLOUR, COUNTRY, CURRENCY, DINGBAT, ELEMENT, ELEMATTR, EXTENSION, FF, FV, HTTPEQUIV, LANG, METANAME, MIMETYPE, REL, SGML
#define BASE_VALID "Attribute", "Charset", "Class", "Colour", "Country Code", "Currency Code", "Dingbat", "Element", "Element+Attribute", "Extension", "Font Feature", "Font Variation", "HttpEquiv Macro", \
	"Language Code", "Meta Name", "Mimetype", "REL", "SGML Schema"
#define BASE_COUNT 18

::std::vector < wxString > vld;	// the code presumes this won't be fiddled with whilst a dialogue is open

vv_t :: vv_t (wxWindow *mummy, wxWindowID id, const wxString& caption)
	: d1_t (wxPoint (VALID_X, VALID_Y), wxSize (VALID_WIDTH, VALID_HEIGHT))
{	Create (mummy, id, caption); } 

bool vv_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption)
{	if (! d1_t :: Create (mummy, id, caption, wxPoint (VALID_X, VALID_Y), wxSize (VALID_WIDTH, VALID_HEIGHT), VALID_STYLE)) return false;
	CreateControls ();
	return true; }

void vv_t :: create_virtual_dir_controls (wxWindow *parent, wxGridSizer* grid, wxStaticText*& stat, wxDirPickerCtrl*& dir, const char* const stattxt)
{	VERIFY_NOT_NULL (grid, __FILE__, __LINE__);
	stat = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, stattxt, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT));
	if (stat != nullptr)
	{	dir = GSL_OWNER (wxDirPickerCtrl) (new wxDirPickerCtrl (parent, wxID_ANY, wxEmptyString, RREPERTOIRE, wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE));
		if (dir !=  nullptr)
		{	grid -> Add (stat, 2, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);
			grid -> Add (dir, 5, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, 5); } } }

void vv_t :: create_controls (wxWindow *parent)
{	virt_.construct (parent, box_, "Virtual " RREPERTOIRES);
	if (! virt_.invalid ())
	{	grid_virt_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 2, 0, 0));	
		if (grid_virt_ != nullptr)
		{	create_virtual_dir_controls (parent, grid_virt_, stat_folder_, dir_folder_, "Physical " REPERTOIRE ":");
			create_virtual_dir_controls (parent, grid_virt_, stat_shadow_, dir_shadow_, "Shadow output " REPERTOIRE ":");
			create_virtual_dir_controls (parent, grid_virt_, stat_ontology_, dir_ontology_, "Ontology output " REPERTOIRE ":");
			box_ -> Add (grid_virt_, 0, wxEXPAND, 1); } }

	line_valid_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
	if (line_valid_ != nullptr)
		box_ -> Add (line_valid_, 0, wxEXPAND | wxALL, 5);

	box_for_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
	if (box_for_ != nullptr)
	{	stat_for_ = GSL_OWNER (wxStaticText) (new wxStaticText (parent, wxID_ANY, "Additional valid values for:", wxDefaultPosition, wxDefaultSize, 0));
		if (stat_for_ != nullptr)
		{	box_for_ -> Add (stat_for_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
			if (vld.empty ())
			{	vld.assign ( { BASE_VALID } );
				for (auto o : context.validation ())
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

	val_.construct (parent, box_, "values"); }

void vv_t :: CreateControls ()
{	if (d1_t :: invalid ()) return;
    create_controls (this);
	d1_t :: CreateButtons (1);
	SetSizer (box_);
	Layout ();
	Centre (wxBOTH); }

void vv_t :: populate ()
{   if (invalid ()) return;
    const int l = choice_for_ -> GetSelection ();
	if (l != wxNOT_FOUND)
	{	const e_css_version sel = GSL_NARROW_CAST < e_css_version > (l);
        PRESUME (sel < vvfix_.size (), __FILE__, __LINE__);
        PRESUME (sel < vvextra_.size (), __FILE__, __LINE__);
        vstr_t vv (vvfix_.at (sel));
        for (auto x : vvextra_.at (sel)) vv.push_back (x);
        val_.preload (vv); } }

void vv_t :: OnChoice (wxCommandEvent& )
{   populate (); }

void vv_t :: OnHelpClick (wxCommandEvent& )
{	if (app != nullptr) app -> help ("validation"); }

void vv_t :: OnValAdd (wxCommandEvent& ) { }
void vv_t :: OnValErase (wxCommandEvent& ) { }
void vv_t :: OnValRename (wxCommandEvent& ) { }
void vv_t :: OnValSelect (wxCommandEvent& ) { }
void vv_t :: OnValText (wxCommandEvent& ) { }
void vv_t :: OnValImpatience (wxCommandEvent& ) { }
void vv_t :: OnVirtAdd (wxCommandEvent& ) { }
void vv_t :: OnVirtErase (wxCommandEvent& ) { }
void vv_t :: OnVirtRename (wxCommandEvent& ) { }
void vv_t :: OnVirtSelect (wxCommandEvent& ) { }
void vv_t :: OnVirtText (wxCommandEvent& ) { }
void vv_t :: OnVirtImpatience (wxCommandEvent& ) { }

void vv_t :: en_virt ()
{	const bool en = (virt_.sel () >= 0);
	dir_ontology_ -> Enable (en);
	dir_folder_ -> Enable (en);
	dir_shadow_ -> Enable (en);
	stat_ontology_ -> Enable (en);
	stat_folder_ -> Enable (en);
	stat_shadow_ -> Enable (en); }

bool vv_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	virt_.preload (virts_);
	en_virt ();
    vstr_t vv (vvfix_.at (0));
    for (auto x : vvextra_.at (0)) if (! x.empty ()) vv.push_back (x);
    val_.preload (vv);


	return true; }

bool vv_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;	

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

void vv_t :: load_from_context (const context_t& c)
{	virts_ = c.virtuals ();
    int count = 0;
	const paths_root& pr = paths_root :: virtual_roots ();
	PRESUME (pr.size () == virts_.size (), __FILE__, __LINE__);
	for (auto s : virts_)
	{	phys_.emplace_back (pr.get_filename (s));
		export_.emplace_back (pr.get_export (s));
		shadow_.emplace_back (pr.get_shadow (s)); }

#define VVPREFIX \
    vvfix_.push_back (vstr_t ()); \
    PRESUME (vvfix_.size () > count, __FILE__, __LINE__)

#define VVPOSTFIX ++count

#define VVFOX(XXX,ZZZ,FFF,TTT) \
    {   VVPREFIX; \
        for (::std::size_t x = FFF; x < TTT; ++x) \
        {   const ::std::string cc = XXX::name (static_cast < ZZZ > (x)); \
            if (! cc.empty ()) vvfix_.at (count).push_back (cc); } \
        VVPOSTFIX; }

#define VVFIX(XXX,ZZZ) VVFOX(XXX,ZZZ,0,XXX::value_count ())

    VVFOX (attr, e_attribute, first_attribute, last_attribute);    
    VVFIX (type_master < t_charset >, e_charset);    
    VVFIX (type_master < t_class >, e_class);
    VVFIX (type_master < t_fixedcolour >, e_fixedcolour);
    VVFIX (type_master < t_country >, e_country);
    VVFIX (type_master < t_currency >, e_currency);
    VVFIX (type_master < t_dingbat >, e_dingbat);
    VVFOX (elem, e_element, first_element_tag, last_element_tag);

    VVPREFIX;
    for (::std::size_t e = first_element_tag; e < last_element_tag; ++e)
        for (::std::size_t a = first_attribute; a < last_attribute; ++a)
        {   const e_element ee = static_cast < e_element > (e);
            const e_attribute aa = static_cast < e_attribute > (a);
            if (has_attribute (ee, aa))
            {   ::std::string s (elem::name (ee));
                s += " ";
                s += attr::name (aa);
                vvfix_.at (8).push_back (s); } }
    VVPOSTFIX;

    VVFIX (type_master < t_format >, e_format);
    VVFIX (type_master < t_css_font_feature >, e_css_font_feature);
    VVFIX (type_master < t_css_font_variation >, e_css_font_variation);
    VVFIX (type_master < t_httpequiv >, e_httpequiv);
    VVFIX (type_master < t_lang >, e_lang);
    VVFIX (type_master < t_metaname  >, e_metaname );
    VVFIX (type_master < t_mime >, e_mimetype);
    VVFIX (type_master < t_rel >, e_rel);
    VVFIX (type_master < t_sgml >, e_sgml);

//    const ustr_t& valid = context.validation ();

    VVFIX (type_master < t_abfmt >, e_abfmt);
    VVFIX (type_master < t_accrual_method >, e_accrual_method);
    VVFIX (type_master < t_accrual_periodicity >, e_accrual_periodicity);
    VVFIX (type_master < t_accrual_policy >, e_accrual_policy);
    VVFIX (type_master < t_action >, e_action);
    VVFIX (type_master < t_align3 >, e_align3);
    VVFIX (type_master < t_alignment_baseline >, e_alignment_baseline);
    VVFIX (type_master < t_alignplus >, e_alignplus);
    VVFIX (type_master < t_as >, e_as);
    VVFIX (type_master < t_as_units >, e_as_units);
    VVFIX (type_master < t_attr_unit >, e_attr_unit);
    VVFIX (type_master < t_autocapitalise >, e_autocapitalise);
    VVFIX (type_master < t_autocomplete >, e_autocomplete);
    VVFIX (type_master < t_baselineshift >, e_baselineshift);
    VVFIX (type_master < t_cachekey >, e_cachekey);
    VVFIX (type_master < t_celnrs >, e_celnrs);
    VVFIX (type_master < t_citype >, e_citype);
    VVFIX (type_master < t_colour_interpolation >, e_colour_interpolation);
    VVFIX (type_master < t_colour_rendering >, e_colour_rendering);
    VVFIX (type_master < t_cookieid >, e_cookieid);
    VVFIX (type_master < t_copy >, e_copy);
    VVFIX (type_master < t_cntype >, e_cntype);
    VVFIX (type_master < t_comp_op >, e_comp_op);
    VVFIX (type_master < t_composite_operator >, e_composite_operator);
    VVFIX (type_master < t_cr_fileproperty >, e_cr_fileproperty);
    VVFIX (type_master < t_crossout >, e_crossout);
    VVFIX (type_master < t_crs_whitebalance >, e_crs_whitebalance);
    VVFIX (type_master < t_css_aaalri >, e_css_aaalri);
    VVFIX (type_master < t_css_absolute_size >, e_css_absolute_size);
    VVFIX (type_master < t_css_align_content >, e_css_align_content);
    VVFIX (type_master < t_css_align_items >, e_css_align_items);
    VVFIX (type_master < t_css_all_2 >, e_css_all_2);
    VVFIX (type_master < t_css_appearance >, e_css_appearance);
    VVFIX (type_master < t_css_azimuth_e >, e_css_azimuth_e);
    VVFIX (type_master < t_css_background_attachment >, e_css_background_attachment);
    VVFIX (type_master < t_css_background_repeat >, e_css_background_repeat);
    VVFIX (type_master < t_css_blend_mode >, e_css_blend_mode);
    VVFIX (type_master < t_css_border_style >, e_css_border_style);
    VVFIX (type_master < t_css_border_width >, e_css_border_width);
    VVFIX (type_master < t_css_box_alignself_mess >, e_css_box_alignself_mess);
    VVFIX (type_master < t_css_box_snap >, e_css_box_snap);
    VVFIX (type_master < t_css_break >, e_css_break);
    VVFIX (type_master < t_css_break_inside >, e_css_break_inside);
    VVFIX (type_master < t_css_caret_shape >, e_css_caret_shape);
    VVFIX (type_master < t_css_clear >, e_css_clear);
    VVFIX (type_master < t_css_contain_e >, e_css_contain_e);
    VVFIX (type_master < t_css_content_enum >, e_css_content_enum);
    VVFIX (type_master < t_css_container_feature >, e_css_container_feature);
    VVFIX (type_master < t_css_content_position >, e_css_content_position);
    VVFIX (type_master < t_css_continue >, e_css_continue);
    VVFIX (type_master < t_css_coord_box >, e_css_coord_box);
    VVFIX (type_master < t_css_control_break >, e_css_control_break);
    VVFIX (type_master < t_css_counter_style >, e_css_counter_style);
    VVFIX (type_master < t_css_cursor_e >, e_css_cursor_e);
    VVFIX (type_master < t_css_display >, e_css_display);
    VVFIX (type_master < t_css_display_inside >, e_css_display_inside);
    VVFIX (type_master < t_css_display_internal >, e_css_display_internal);
    VVFIX (type_master < t_css_elevation_e >, e_css_elevation_e);
    VVFIX (type_master < t_css_float >, e_css_float);
    VVFIX (type_master < t_css_fn >, e_css_fn);
    VVFIX (type_master < t_css_font_display >, e_css_font_display);
    VVFIX (type_master < t_css_font_feature >, e_css_font_feature);
    VVFIX (type_master < t_css_font_format >, e_css_font_format);
    VVFIX (type_master < t_css_font_size_adjust_e >, e_css_font_size_adjust_e);
    VVFIX (type_master < t_css_font_tech >, e_css_font_tech);
    VVFIX (type_master < t_css_font_variation >, e_css_font_variation);
    VVFIX (type_master < t_css_font_weight >, e_css_font_weight);
    VVFIX (type_master < t_css_generic_family >, e_css_generic_family);
    VVFIX (type_master < t_css_hll >, e_css_hll);
    VVFIX (type_master < t_css_inline_bem_1 >, e_css_inline_bem_1);
    VVFIX (type_master < t_css_inline_bem_2 >, e_css_inline_bem_2);
    VVFIX (type_master < t_css_justify_content >, e_css_justify_content);
    VVFIX (type_master < t_css_layout_box >, e_css_layout_box);
    VVFIX (type_master < t_css_line_break >, e_css_line_break);
    VVFIX (type_master < t_css_list_style_position >, e_css_list_style_position);
    VVFIX (type_master < t_css_list_style_type >, e_css_list_style_type);
    VVFIX (type_master < t_css_module >, e_css_module);
    VVFIX (type_master < t_css_paint_box >, e_css_paint_box);
    VVFIX (type_master < t_css_overflow >, e_css_overflow);
    VVFIX (type_master < t_css_size_e >, e_css_size_e);
    VVFIX (type_master < t_css_sizing >, e_css_sizing);
    VVFIX (type_master < t_css_pause_3_e >, e_css_pause_3_e);
    VVFIX (type_master < t_css_pitch_e >, e_css_pitch_e);
    VVFIX (type_master < t_css_position >, e_css_position);
    VVFIX (type_master < t_css_ray_size >, e_css_ray_size);
    VVFIX (type_master < t_css_rgb_xyz >, e_css_rgb_xyz);
    VVFIX (type_master < t_css_rect >, e_css_rect);
    VVFIX (type_master < t_css_relative_size >, e_css_relative_size);
    VVFIX (type_master < t_css_resize >, e_css_resize);
    VVFIX (type_master < t_css_ss_type_e >, e_css_ss_type_e);
    VVFIX (type_master < t_css_self_position >, e_css_self_position);
    VVFIX (type_master < t_css_speak_as_e >, e_css_speak_as_e);
    VVFIX (type_master < t_css_statement >, e_css_statement);
    VVFIX (type_master < t_css_speech_rate_e >, e_css_speech_rate_e);
    VVFIX (type_master < t_css_system_e >, e_css_system_e);
    VVFIX (type_master < t_css_text_align >, e_css_text_align);
    VVFIX (type_master < t_css_text_align_all >, e_css_text_align_all);
    VVFIX (type_master < t_css_text_align_last >, e_css_text_align_last);
    VVFIX (type_master < t_css_text_autospace >, e_css_text_autospace);
    VVFIX (type_master < t_css_text_decoration >, e_css_text_decoration);
    VVFIX (type_master < t_css_text_transform >, e_css_text_transform);
    VVFIX (type_master < t_css_textdec_line_e >, e_css_textdec_line_e);
    VVFIX (type_master < t_css_textdec_style >, e_css_textdec_style);
    VVFIX (type_master < t_css_textemph_shape >, e_css_textemph_shape);
    VVFIX (type_master < t_css_transform_box >, e_css_transform_box);
    VVFIX (type_master < t_css_user_select >, e_css_user_select);
    VVFIX (type_master < t_css_text_wrap >, e_css_text_wrap);
    VVFIX (type_master < t_css_val_fn >, e_css_val_fn);
    VVFIX (type_master < t_css_version >, e_css_version);
    VVFIX (type_master < t_css_vertical_align >, e_css_vertical_align);
    VVFIX (type_master < t_css_visual_box >, e_css_visual_box);
    VVFIX (type_master < t_css_voice_balance_e >, e_css_voice_balance_e);
    VVFIX (type_master < t_css_volume_e >, e_css_volume_e);
    VVFIX (type_master < t_css_whitespace >, e_css_whitespace);
    VVFIX (type_master < t_css_wide >, e_css_wide);
    VVFIX (type_master < t_css_wrap_flow >, e_css_wrap_flow);
    VVFIX (type_master < t_css_wsc >, e_css_wsc);
    VVFIX (type_master < t_css_wst >, e_css_wst);
    VVFIX (type_master < t_cursor >, e_cursor);
    VVFIX (type_master < t_decalign >, e_decalign);
    VVFIX (type_master < t_determiner >, e_determiner);
    VVFIX (type_master < t_dingbat >, e_dingbat);
    VVFIX (type_master < t_dir >, e_dir);
    VVFIX (type_master < t_display_align >, e_display_align);
    VVFIX (type_master < t_dominantbaseline >, e_dominantbaseline);
    VVFIX (type_master < t_enterkeyhint >, e_enterkeyhint);
    VVFIX (type_master < t_evt_action >, e_evt_action);
    VVFIX (type_master < t_figalign >, e_figalign);
    VVFIX (type_master < t_filter_in >, e_filter_in);
    VVFIX (type_master < t_fontname >, e_fontname);
    VVFIX (type_master < t_font_enum >, e_font_enum);
    VVFIX (type_master < t_font_variant_2 >, e_font_variant_2);
    VVFIX (type_master < t_font_variant_caps >, e_font_variant_caps);
    VVFIX (type_master < t_font_variant_east_asian >, e_font_variant_east_asian);
    VVFIX (type_master < t_font_variant_ligature >, e_font_variant_ligature);
    VVFIX (type_master < t_font_variant_numeric >, e_font_variant_numeric);
    VVFIX (type_master < t_formaturi >, e_formaturi);
    VVFIX (type_master < t_halign >, e_halign);
    VVFIX (type_master < t_icalfreq >, e_icalfreq);
    VVFIX (type_master < t_image_rendering >, e_image_rendering);
    VVFIX (type_master < t_icc >, e_icc);
    VVFIX (type_master < t_indentalign >, e_indentalign);
    VVFIX (type_master < t_inky >, e_inky);
    VVFIX (type_master < t_inputmode >, e_inputmode);
    VVFIX (type_master < t_inputplus >, e_inputplus);
    VVFIX (type_master < t_inputtype >, e_inputtype);
    VVFIX (type_master < t_inputtype3 >, e_inputtype3);
    VVFIX (type_master < t_inputtype32 >, e_inputtype32);
    VVFIX (type_master < t_inputtype4 >, e_inputtype4);
    VVFIX (type_master < t_inputtype5 >, e_inputtype5);
    VVFIX (type_master < t_jtoken >, e_jtoken);
    VVFIX (type_master < t_kind >, e_kind);
    VVFIX (type_master < t_length_absolute >, e_length_absolute);
    VVFIX (type_master < t_length_relative >, e_length_relative);
    VVFIX (type_master < t_linebreak >, e_linebreak);
    VVFIX (type_master < t_linkparam >, e_linkparam);
    VVFIX (type_master < t_listtype >, e_listtype);
    VVFIX (type_master < t_lrnialign >, e_lrnialign);
    VVFIX (type_master < t_longdivstyle >, e_longdivstyle);
    VVFIX (type_master < t_mah >, e_mah);
    VVFIX (type_master < t_mathalign >, e_mathalign);
    VVFIX (type_master < t_mathlocation >, e_mathlocation);
    VVFIX (type_master < t_mathnotation >, e_mathnotation);
    VVFIX (type_master < t_mathoverflow >, e_mathoverflow);
    VVFIX (type_master < t_mathvariant >, e_mathvariant);
    VVFIX (type_master < t_math_version >, e_math_version);
    VVFIX (type_master < t_matrixtype >, e_matrixtype);
    VVFIX (type_master < t_method >, e_method);
    VVFIX (type_master < t_mf_identifier >, e_mf_identifier);
    VVFIX (type_master < t_mf_itemtype >, e_mf_itemtype);
    VVFIX (type_master < t_mf_listing_action >, e_mf_listing_action);
    VVFIX (type_master < t_mf_method >, e_mf_method);
    VVFIX (type_master < t_mf_reviewtype >, e_mf_reviewtype);
    VVFIX (type_master < t_month_english_long >, e_month_english_long);
    VVFIX (type_master < t_month_english_short >, e_month_english_short);
    VVFIX (type_master < t_musickey >, e_musickey);
    VVFIX (type_master < t_myersbriggs >, e_myersbriggs);
    VVFIX (type_master < t_namedspace >, e_namedspace);
    VVFIX (type_master < t_namespace >, e_namespace);
    VVFIX (type_master < t_nit_macro >, e_nit_macro);
    VVFIX (type_master < t_nit_section >, e_nit_section);
    VVFIX (type_master < t_ogtype >, e_ogtype);
    VVFIX (type_master < t_page_orientation >, e_page_orientation);
    VVFIX (type_master < t_paintkeyword >, e_paintkeyword);
    VVFIX (type_master < t_pam_ccv >, e_pam_ccv);
    VVFIX (type_master < t_pcmm_status >, e_pcmm_status);
    VVFIX (type_master < t_plusstyle >, e_plusstyle);
    VVFIX (type_master < t_pointer_events >, e_pointer_events);
    VVFIX (type_master < t_pri_img_colour >, e_pri_img_colour);
    VVFIX (type_master < t_pri_img_technique >, e_pri_img_technique);
    VVFIX (type_master < t_pri_img_viewpoint >, e_pri_img_viewpoint);
    VVFIX (type_master < t_print >, e_print);
    VVFIX (type_master < t_prism_ad_pos >, e_prism_ad_pos);
    VVFIX (type_master < t_prism_ad_type >, e_prism_ad_type);
    VVFIX (type_master < t_prism_ag_type >, e_prism_ag_type);
    VVFIX (type_master < t_prism_audience_sector >, e_prism_audience_sector);
    VVFIX (type_master < t_prism_ccv >, e_prism_ccv);
    VVFIX (type_master < t_prism_class >, e_prism_class);
    VVFIX (type_master < t_prism_contenttype >, e_prism_contenttype);
    VVFIX (type_master < t_prism_cvp >, e_prism_cvp);
    VVFIX (type_master < t_prism_genre >, e_prism_genre);
    VVFIX (type_master < t_prism_icv >, e_prism_icv);
    VVFIX (type_master < t_prism_pasv >, e_prism_pasv);
    VVFIX (type_master < t_prism_pcv >, e_prism_pcv);
    VVFIX (type_master < t_prism_pfv >, e_prism_pfv);
    VVFIX (type_master < t_prism_ptv >, e_prism_ptv);
    VVFIX (type_master < t_prism_rcv >, e_prism_rcv);
    VVFIX (type_master < t_prism_role >, e_prism_role);
    VVFIX (type_master < t_prs_action >, e_prs_action);
    VVFIX (type_master < t_quote_style >, e_quote_style);
    VVFIX (type_master < t_recipe_content >, e_recipe_content);
    VVFIX (type_master < t_recipe_course >, e_recipe_course);
    VVFIX (type_master < t_recipe_cuisine >, e_recipe_cuisine);
    VVFIX (type_master < t_recipe_dietary >, e_recipe_dietary);
    VVFIX (type_master < t_recipe_dish >, e_recipe_dish);
    VVFIX (type_master < t_recipe_exclusion >, e_recipe_exclusion);
    VVFIX (type_master < t_recipe_kit >, e_recipe_kit);
    VVFIX (type_master < t_recipe_meal >, e_recipe_meal);
    VVFIX (type_master < t_recipe_method >, e_recipe_method);
    VVFIX (type_master < t_recipe_source >, e_recipe_source);
    VVFIX (type_master < t_recipe_special >, e_recipe_special);
    VVFIX (type_master < t_recipe_time >, e_recipe_time);
    VVFIX (type_master < t_referrer >, e_referrer);
    VVFIX (type_master < t_rendering_in_tents >, e_rendering_in_tents);
    VVFIX (type_master < t_report >, e_report);
    VVFIX (type_master < t_rules >, e_rules);
    VVFIX (type_master < t_sandbox >, e_sandbox);
    VVFIX (type_master < t_scei >, e_scei);
    VVFIX (type_master < t_severity >, e_severity);
    VVFIX (type_master < t_shadow >, e_shadow);
    VVFIX (type_master < t_shape7 >, e_shape7);
    VVFIX (type_master < t_shape_rendering >, e_shape_rendering);
    VVFIX (type_master < t_smei >, e_smei);
    VVFIX (type_master < t_ssi >, e_ssi);
    VVFIX (type_master < t_ssi_comparison >, e_ssi_comparison);
    VVFIX (type_master < t_ssi_config >, e_ssi_config);
    VVFIX (type_master < t_ssi_encoding >, e_ssi_encoding);
    VVFIX (type_master < t_ssi_env >, e_ssi_env);
    VVFIX (type_master < t_step_position >, e_step_position);
    VVFIX (type_master < t_stress >, e_stress);
    VVFIX (type_master < t_supports >, e_supports);
    VVFIX (type_master < t_svg_align >, e_svg_align);
    VVFIX (type_master < t_svg_display >, e_svg_display);
    VVFIX (type_master < t_svg_fontstretch >, e_svg_fontstretch);
    VVFIX (type_master < t_svg_fontstretch_ff >, e_svg_fontstretch_ff);
    VVFIX (type_master < t_svg_fontstyle >, e_svg_fontstyle);
    VVFIX (type_master < t_svg_fontweight >, e_svg_fontweight);
    VVFIX (type_master < t_svg_fontweight_ff >, e_svg_fontweight_ff);
    VVFIX (type_master < t_svg_mode >, e_svg_mode);
    VVFIX (type_master < t_svg_overflow >, e_svg_overflow);
    VVFIX (type_master < t_svg_rendering_intent >, e_svg_rendering_intent);
    VVFIX (type_master < t_svg_type >, e_svg_type);
    VVFIX (type_master < t_svg_version >, e_svg_version);
    VVFIX (type_master < t_svg_version_grand >, e_svg_version_grand);
    VVFIX (type_master < t_tableframe >, e_tableframe);
    VVFIX (type_master < t_tblri >, e_tblri);
    VVFIX (type_master < t_text_decoration >, e_text_decoration);
    VVFIX (type_master < t_text_rendering >, e_text_rendering);
    VVFIX (type_master < t_tld >, e_tld);
    VVFIX (type_master < t_transform_anim >, e_transform_anim);
    VVFIX (type_master < t_transformbehaviour >, e_transformbehaviour);
    VVFIX (type_master < t_transform_fn >, e_transform_fn);
    VVFIX (type_master < t_turbulence_type >, e_turbulence_type);
    VVFIX (type_master < t_unit >, e_unit);
    VVFIX (type_master < t_unit_abs_len >, e_unit_abs_len);
    VVFIX (type_master < t_unit_angle >, e_unit_angle);
    VVFIX (type_master < t_unit_freq >, e_unit_freq);
    VVFIX (type_master < t_unit_rel_len >, e_unit_rel_len);
    VVFIX (type_master < t_unit_res >, e_unit_res);
    VVFIX (type_master < t_unit_time >, e_unit_time);
    VVFIX (type_master < t_unicode_bidi >, e_unicode_bidi);
    VVFIX (type_master < t_vector_effect_2 >, e_vector_effect_2);
    VVFIX (type_master < t_vertical_align_enum >, e_vertical_align_enum);
    VVFIX (type_master < t_vgender >, e_vgender);
    VVFIX (type_master < t_vrel >, e_vrel);
    VVFIX (type_master < t_vtt >, e_vtt);
    VVFIX (type_master < t_weekday_english_long >, e_weekday_english_long);
    VVFIX (type_master < t_weekday_english_short >, e_weekday_english_short);
    VVFIX (type_master < t_whitespace >, e_whitespace);
    VVFIX (type_master < t_writingmode >, e_writingmode);
    VVFIX (type_master < t_xmlns >, e_xmlns);
    VVFIX (type_master < t_xmpdm_audio_channel >, e_xmpdm_audio_channel);
    VVFIX (type_master < t_xmpdm_audio_sample >, e_xmpdm_audio_sample);
    VVFIX (type_master < t_xmpdm_camera_angle >, e_xmpdm_camera_angle);
    VVFIX (type_master < t_xmpdm_camera_move >, e_xmpdm_camera_move);
    VVFIX (type_master < t_xmpdm_pulldown >, e_xmpdm_pulldown);
    VVFIX (type_master < t_xmpdm_shotsize >, e_xmpdm_shotsize);
    VVFIX (type_master < t_xmpdm_stretchmode >, e_xmpdm_stretchmode);
    VVFIX (type_master < t_xmpdm_time_format >, e_xmpdm_time_format);
    VVFIX (type_master < t_xmpdm_time_signature >, e_xmpdm_time_signature);
    VVFIX (type_master < t_xmpdm_video_pixeldepth >, e_xmpdm_video_pixeldepth);
#undef VVPREFIX
#undef VVFIX
#undef VVFOX
#undef VVPOSTFIX
    vvextra_.resize (vvfix_.size ());

}

void vv_t :: save_to_context (context_t& c) const
{	PRESUME (virts_.size () == phys_.size (), __FILE__, __LINE__);
	PRESUME (virts_.size () == export_.size (), __FILE__, __LINE__);
	PRESUME (virts_.size () == shadow_.size (), __FILE__, __LINE__);
	if (virts_.size () == 0) return;
	c.virtuals (virts_);
	paths_root& pr = paths_root :: virtual_roots ();
	pr.reinit ();
	nitpick nits;
	for (int i = 0; i < virts_.size (); ++i)
    {	pr.add_root (phys_.at (i), virts_.at (i));
		pr.at (i) -> set_export (nits, export_.at (i));
		pr.at (i) -> shadow_root (nits, shadow_.at (i)); }


	/* to do */	}

#endif // WX
