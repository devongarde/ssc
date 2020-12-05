/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "element/state.h"
#include "element/elem.h"
#include "attribute/attr.h"

const element_bitset empty_element_bitset;
const attribute_bitset empty_attribute_bitset;
const element_bitset autocapitalise_bitset = empty_element_bitset | elem_button | elem_fieldset | elem_input | elem_output | elem_select | elem_textarea;
const element_bitset faux_bitset = empty_element_bitset | elem_faux_document | elem_faux_asp | elem_faux_cdata | elem_faux_char | elem_faux_code | elem_faux_comment |
        elem_faux_doctype | elem_faux_php | elem_faux_ssi | elem_faux_stylesheet | elem_faux_text | elem_faux_xml | elem_faux_whitespace;
const element_bitset form_bitset = empty_element_bitset | elem_button | elem_fieldset | elem_input | elem_object | elem_output | elem_select | elem_textarea | elem_img;
const element_bitset header_bitset = empty_element_bitset | elem_h1 | elem_h2 | elem_h3 | elem_h4 | elem_h5 | elem_h6 | elem_hgroup;
const element_bitset interactive_bitset = empty_element_bitset | elem_a | elem_audio | elem_button | elem_details | elem_embed | elem_iframe |
        elem_img | elem_input | elem_label | elem_object | elem_select | elem_textarea | elem_video;
const element_bitset label_bitset = empty_element_bitset | elem_button | elem_input | elem_meter | elem_output | elem_progress | elem_select | elem_textarea;
const element_bitset listed_bitset = empty_element_bitset | elem_button | elem_fieldset | elem_input | elem_object | elem_output | elem_select | elem_textarea;
const element_bitset media_bitset = empty_element_bitset | elem_audio | elem_video;
const element_bitset sectioning_bitset = empty_element_bitset | elem_article | elem_aside | elem_nav | elem_section;
const element_bitset non_standard_bitset = faux_bitset | elem_undefined;


::std::string nameset (const element_bitset& bs)
{   ::std::string res;
    for (::std::size_t i = 0; i < last_element_tag; ++i)
        if (bs.test (i))
        {   if (! res.empty ()) res += ", ";
            res += "<";
            res += elem::name (static_cast < e_element > (i));
            res += ">";}
    return res; }

::std::string nameset (const attribute_bitset& bs)
{   ::std::string res;
    for (::std::size_t i = 0; i < last_attribute; ++i)
        if (bs.test (i))
        {   if (! res.empty ()) res += ", ";
            res += attr::name (static_cast < e_attribute > (i)); }
    return res; }
