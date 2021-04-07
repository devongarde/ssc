/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

#pragma once
#include "element/state.h"
#include "webpage/id.h"
#include "microformat/microformats_ptr.h"
#include "attribute/attributes.h"
#include "parser/parse_element.h"
#include "microformat/microformat_export.h"
#include "microdata/microdata_itemscope.h"

#define MAX_IDEAL_PLACEHOLDER_LENGTH 24

class page;
class element;
typedef ::std::vector < element* > velptr_t;
typedef ::std::pair < element*, e_class > found_farm;
typedef ::std::shared_ptr < element > element_ptr;

class element
{   element_node& node_;
    attributes a_;
    bool examined_ = false, icarus_ = false, reconstructed_ = false;
    page& page_;
    element* parent_ = nullptr;
    element_ptr sibling_ = nullptr, child_ = nullptr;
    element* autofocus_ = nullptr;
    microformats_ptr mf_ = nullptr;
    ::std::string name_;
    sstr_t* access_ = nullptr;
    element_bitset ancestral_elements_, sibling_elements_, descendant_elements_;
    attribute_bitset ancestral_attributes_, own_attributes_, sibling_attributes_, descendant_attributes_;
    uid_t uid_ = 0, closure_uid_ = 0;
    velptr_t radio_kids_;
    itemscope_ptr itemscope_;
    vit_t vit_;
    sstr_t results_;
    nitpick& nits () { return node_.nits (); }
    nitpick& nits () const { return node_.nits (); }
    found_farm find_farm (const e_property prop, element* starter = nullptr);
    void seek_webmention (::std::string& mention, e_wm_status& wms);
    bool to_sibling (element_ptr& e, const bool canreconstruct = true);
    element* next_element (element* previous);
    template < class PROPERTY > void note_reply ();
    template < e_type T > void val_min_max (const bool cyclic = false);
    void activate_microformats () { if (! mf_) mf_.reset (new microformats ()); }
    void dddt (const char* ref1, const char* ref2, const char* el);
    void check_required_type (const e_element tag);
    void mf_put_vocab (const e_class v, const prop& p, const ::std::string& itemtype = ::std::string (EXPORT_ITEMTYPE), const ::std::string& itemprop = ::std::string (EXPORT_ITEMPROP));
    void mf_put_rel (const e_class v, const prop& p, const vstr_t& rels);
    void verify ();
    void verify_children ();
    bool only_one_of (const e_element e);
    bool only_one_visible_of (const e_element e);
    void congeal_dynamism ();
    bool has_this_child (const e_element e) const;
    bool has_this_descendant (const e_element e) const;
    void remove_category (const uint64_t c);
    void check_ancestors (const e_element self, const element_bitset& gf);
    void check_descendants (const e_element self, const element_bitset& gf, const bool absent = true);
    bool has_invalid_child (const element_bitset& gf);
    void check_mscarries_pos (const e_element self);
    bool check_math_children (const int expected, const bool or_more = false);
    void check_math_children (const int from, const int to);
    void do_shadow (::std::stringstream& ss, const html_version& v, bool& was_closure, bool& allspace, bool& was_nl);
    bool naughty_label_descendents (const element* e, const uid_t uid, bool& first);
    void no_anchor_daddy ();
    template < typename ATTRIBUTE > element* ancestor_known (const e_attribute a) const;
    void verify_microdata ();
    bool report_script_comment (element_ptr parent);
    void walk_itemprop (itemscope_ptr itemscope);
    vit_t supplied_itemtypes ();
    vit_t sought_itemtypes ();
    void span_check ();
    void pre_examine_element (const e_element tag);
    void post_examine_element (const e_element tag);
    void examine_media_element (e_element elem, const char* ref, const char* name, const uint64_t family);
    void examine_accesskey ();
    void examine_autofocus ();
    bool examine_class ();
    void examine_clip ();
    void examine_content ();
    void examine_draggable ();
    void examine_font ();
    void examine_href ();
    void examine_headers ();
    void examine_descendant_in (const element* filter);
    itemscope_ptr examine_itemscope (itemscope_ptr& itemscope);
    void examine_itemprop (itemscope_ptr& itemscope);
    void examine_itemref (itemscope_ptr& itemscope);
    void examine_itemtype (itemscope_ptr& itemscope);
    void examine_other ();
    void examine_ref ();
    void examine_registrationmark ();
    bool examine_rel (const ::std::string& content);
    void examine_style_attr ();
    void examine_xlinkhref ();
    void validate_input_id ();
    ::std::string text () const { return node_.text (); }
    ::std::string term () const;
    void examine_abbr ();
    void examine_address ();
    void examine_animatemotion ();
    void examine_annotation (const e_element e);
    void examine_area ();
    void examine_article ();
    void examine_aside ();
    void examine_audio ();
    void examine_anchor ();
    void examine_base ();
    void examine_bind ();
    void examine_button ();
    void examine_card ();
    void examine_caption ();
    void examine_command ();
    void examine_col ();
    void examine_colgroup ();
    void examine_data ();
    void examine_datagrid ();
    void examine_datalist ();
    void examine_details ();
    void examine_dd ();
    void examine_dfn ();
    void examine_dialogue ();
    void examine_div ();
    void examine_dl ();
    void examine_dt ();
    void examine_embed ();
    void examine_equation ();
    void examine_fecolourmatrix ();
    void examine_felighting ();
    void examine_fieldset ();
    void examine_figcaption ();
    void examine_figure ();
    void examine_filter ();
    void examine_fn ();
    void examine_fontymacfontface ();
    void examine_footer ();
    void examine_form ();
    void examine_h123456 ();
    void examine_header ();
    void examine_hgroup ();
    void examine_html ();
    void examine_iframe ();
    void examine_img ();
    void examine_input ();
    void examine_label ();
    void examine_lambda ();
    void examine_li ();
    void examine_link ();
    void examine_main ();
    void examine_map ();
    void examine_math ();
    void examine_menu ();
    void examine_menubar ();
    void examine_meta ();
    void examine_meter ();
    void examine_mglyph ();
    void examine_mstyle ();
    void examine_nav ();
    void examine_nest ();
    void examine_noscript ();
    void examine_object ();
    void examine_option ();
    void examine_output ();
    void examine_picture ();
    void examine_piecewise ();
    void examine_progress ();
    void examine_reln ();
    void examine_ruby ();
    void examine_script ();
    void examine_section ();
    void examine_select ();
    void examine_share ();
    void examine_source ();
    void examine_style ();
    void examine_svg ();
    void examine_svg_shape ();
    void examine_switch ();
    void examine_summary ();
    void examine_tab ();
    void examine_table ();
    void examine_td ();
    void examine_textarea ();
    void examine_th ();
    void examine_time ();
    void examine_title ();
    void examine_track ();
    void examine_video ();
public:
    element () = delete;
    element (const ::std::string& name, element_node& en, element* parent, page& p);
    ~element () = default;
    void swap (element& e) NOEXCEPT;

    void reconstruct (sstr_t* access);
    const element_node& node () const
    {   return node_; }
    const ::std::string name () const { return name_; }
    bool has_child () const
    {   return node_.has_child (); }
    bool has_next () const
    {   return node_.has_next (); }
    ::std::string content () const;
    element_ptr child (const bool canreconstruct = true);
    element_ptr next (const bool canreconstruct = true);
    e_element tag () const
    {   return node_.tag (); }
    bool invalid () const
    {   return node_.invalid (); }
    bool is_top () const
    {   return parent_ == nullptr; }
    bool hidden () const
    {   if (own_attributes_.test (a_hidden)) return true;
        return ancestral_attributes_.test (a_hidden); }
    void examine_self ( const directory& d, const itemscope_ptr& itemscope = itemscope_ptr (),
                        const attribute_bitset& ancestral_attributes = attribute_bitset (), const attribute_bitset& sibling_attributes = attribute_bitset ());
    void examine_children (const directory& d);
    ::std::string make_children (const int depth, const element_bitset& gf = element_bitset ());
    void verify_document ();
    ::std::string find_date_value () const;
    ::std::string find_text_value () const;
    ::std::string find_url_value () const;
    ::std::string find_html_value () const;
    ::std::string find_webmention ();
    ::std::string find_mention_info (const url& u, bool text, bool anything);
    ids_t& get_ids ();
    const ids_t& get_ids () const;
    ids_t& get_names ();
    const ids_t& get_names () const;
    element* parent () const
    {   DBG_ASSERT (! is_top ());
        return parent_; }
    bool reportable () const
    {   return ((tag () != elem_undefined) || context.tell (e_splurge) || (child_ != nullptr)); }
#if VS >= 17
    void pick (const e_nit code, const e_doc doc, char* const ref, const e_severity severity, const e_category category, char* const msg)
    {   node_.pick (code, doc, ref, severity, category, msg); }
    void pick (const e_nit code, const e_severity severity, const e_category category, const char* msg)
    {   node_.pick (code, severity, category, msg); }
#endif // VS
    template < typename ... Ts > void pick (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, Ts... msg)
    {   node_.pick (code, doc, ref, severity, category, msg...); }
    template < typename ... Ts > void pick (const e_nit code, const e_severity severity, const e_category category, Ts... msg)
    {   node_.pick (code, severity, category, msg...); }
    element* find_first (const e_element e);
    element* find_next (const e_element e, element* previous);
    element* get_ancestor (const e_element e) const;
    void add_result (const ::std::string& s)
    {   DBG_ASSERT (! s.empty ());
        results_.insert (s); }
    bool has_result (const ::std::string& s) const
    {   DBG_ASSERT (! s.empty ());
        return (results_.find (s) != results_.cend ()); }
    int line () const;
    uid_t uid () const { return uid_; }
    bool family_uids (const e_element e, uid_t& from, uid_t& to) const;
    e_inputtype5 get_input_type () const;
    itemscope_ptr itemscope () const { return itemscope_; }
    vit_t own_itemtype () const;
    attribute_bitset own_attributes () const { return own_attributes_; }
    ::std::string get_microdata_value () const;
    void shadow (::std::stringstream& ss, const html_version& v);
    const page& get_page () const { return page_; }
    ::std::string report (); };

template < class PROPERTY > void element::note_reply ()
{   if (! mf_) return;
    if (is_microformat_property_empty < mf_entry, PROPERTY> (mf_)) return;
    context.note_reply (name_, a_.get_string (a_id), get_microformat_property_value < mf_entry, PROPERTY > (mf_), text ()); }
