/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "element/element.h"
#include "webpage/page.h"
#include "attribute/attribute_classes.h"

void element::examine_tab ()
{   if (node_.version () == html_3_0)
        if (a_.known (a_indent) && a_.known (a_to))
            pick (nit_chocolate_teapot, ed_3, "Horizontal Tabs (Page 38)", es_warning, ec_element, "TO and INDENT should not be combined in <TAB>"); }

void element::examine_table ()
{   if (! has_child () || (node_.version ().mjr () < 5)) return;
    typedef enum { to_start, to_caption, to_colgroup, to_head, to_foot_start, to_tr, to_foot_end } table_order;
    table_order tor = to_start;
    bool ooo = false, footed = false, doubled = false, mixed = false, body = false, tr = false;
    for (element* p = child_; p != nullptr; p = p -> sibling_)
    {   if (! p -> node_.is_closure ())
        {   switch (p -> tag ())
            {   case elem_caption :
                    doubled = (tor == to_caption);
                    ooo = (tor != to_start);
                    tor = to_caption;
                    break;
                case elem_colgroup :
                    ooo = (tor > to_colgroup);
                    tor = to_colgroup;
                    break;
                case elem_thead :
                    doubled = (tor == to_head);
                    ooo = (tor >= to_head);
                    tor = to_head;
                    break;
                case elem_tbody :
                    mixed = tr;
                    body = true;
                    ooo = (tor > to_tr);
                    tor = to_tr;
                    break;
                case elem_tr :
                    mixed = body;
                    tr = true;
                    ooo = (tor > to_tr);
                    tor = to_tr;
                    break;
                case elem_tfoot :
                    doubled = ooo = footed;
                    if ((w3_minor_5 (node_.version ()) == 0) && (tor < to_tr)) tor = to_foot_start;
                    else tor = to_foot_end;
                    footed = true;
                    break;
                default : break; }
            if (ooo)
                if (w3_minor_5 (node_.version ()) == 0)
                    pick (nit_table_children, ed_50, "4.9.1 The table element", es_error, ec_element, "<TABLE> children in wrong order (<CAPTION>, <COLGROUP>s, <THEAD>, <TFOOT>, <TR>s or <TBODY>s, <TFOOT>, with only one <TFOOT>)");
                else pick (nit_table_children, ed_51, "4.9.1 The table element", es_error, ec_element, "<TABLE> children in wrong order (<CAPTION>, <COLGROUP>s, <THEAD>, <TR>s or <TBODY>s, <TFOOT>)");
            if (doubled) pick (nit_table_children, ed_50, "4.9.1 The table element", es_error, ec_element, "only one <CAPTION>, <THEAD>, <TFOOT> per <TABLE>");
            if (mixed) pick (nit_table_children, ed_50, "4.9.1 The table element", es_error, ec_element, "either <TBODY>s or <TR>s, not both");
            if (ooo || doubled || mixed) break; } } }

void element::examine_td ()
{   if (node_.version ().mjr () < 5) return;
    span_check (); }

void element::examine_textarea ()
{   no_anchor_daddy ();
    if (a_.good (a_wrap))
        if (a_.get_int (a_wrap) == static_cast < int > (w_hard))
            if (! a_.known (a_cols))
                pick (nit_bad_textarea, ed_50, "4.10.11 The textarea element", es_error, ec_element, "When <TEXTAREA> WRAP='hard', COLS is required");
    int max = 0, min = 1;
    if (a_.good (a_maxlength)) max = a_.get_int (a_maxlength);
    if (a_.good (a_minlength)) min = a_.get_int (a_minlength);
    int len = ::gsl::narrow_cast < int > (text ().length ());
    if ((max > 0) && (min > max)) pick (nit_bad_textarea, ed_50, "4.10.11 The textarea element", es_error, ec_element, "<TEXTAREA> MINLENGTH is greater than MAXLENGTH");
    if (len > 0)
    {   if (len < min) pick (nit_bad_textarea, ed_50, "4.10.11 The textarea element", es_warning, ec_element, "<TEXTAREA> content is short than MINLENGTH");
        if ((max > 0) && (len > max)) pick (nit_bad_textarea, ed_50, "4.10.11 The textarea element", es_warning, ec_element, "<TEXTAREA> content is longer than MAXLENGTH"); } }

void element::examine_th ()
{   if (node_.version ().mjr () < 5) return;
    const bool is3 = (w3_minor_5 (node_.version ()) == 3);
    element_bitset bs (descendant_elements_);
    if (is3) bs &= sectioning_bitset | header_bitset | elem_header | elem_footer | elem_main;
    else bs &= sectioning_bitset | header_bitset | elem_header | elem_footer;
    if (bs.any ())
        if (is3) pick (nit_bad_descendant, ed_53, "4.9.10 The th element ", es_error, ec_element, "<TH> cannot have <MAIN>, <HEADER>, <FOOTER>, sectioning or header descendants");
        else pick (nit_bad_descendant, ed_50, "4.9.10 The th element ", es_error, ec_element, "<TH> cannot have <HEADER>, <FOOTER>, sectioning or header descendants");
    if (a_.known (a_sorted))
    {   bs = descendant_elements_;
        bs &= interactive_bitset;
        if (bs.any ()) pick (nit_bad_descendant, ed_jan14, "4.9.10 The th element ", es_error, ec_element, "<TH> with SORTED cannot have interactive element descendants"); }
    span_check (); }

void element::examine_time ()
{   if (! a_.known (a_datetime))
    {   element_bitset bs (descendant_elements_);
        bs &= ~non_standard_bitset;
        if (bs.any ())
            pick (nit_use_datetime, ed_50, "4.5.11 The time element", es_error, ec_element, "<TIME> without DATETIME cannot have descendant elements");
        type_master < t_datetime_5 > dt;
        dt.set_value (node_.nits (), node_.version (), text ());
        if (! dt.good ())
            pick (nit_use_datetime, es_warning, ec_element, "<TIME>'s descendant text is not particularly timely; perhaps use a DATETIME attribute"); } }

void element::examine_title ()
{   if (! node_.version ().has_svg ()) only_one_of ();
    ::std::string ttl (text ());
    if (! ancestral_elements_.test (elem_head)) return;
    page_ -> title (ttl);
    if (is_whitespace (ttl))
        pick (nit_text_content, es_warning, ec_element, "<TITLE> text should be more than whitespace");
    else if (ttl.length () > ::gsl::narrow_cast < unsigned int > (context.title ()))
        pick (nit_long_title, ed_tags, "TITLE section", es_warning, ec_element, "the TITLE text (", quote (ttl.substr (0, context.title ())), "...) is too long");
    page_ -> confirm_title (); }

void element::examine_track ()
{   if (node_.version ().is_5 ())
    {   const bool has_src = a_.known (a_src);
        const vurl_t& vu = a_.get_urls (a_src);
        const e_kind k = static_cast < e_kind > (a_.get_int (a_kind));
        if (a_.known (a_kind))
        {   if ((k == k_subtitles) && ! a_.known (a_srclang))
                pick (nit_data_type, ed_50, "4.7.9 The track element", es_error, ec_element, "<TRACK> with KIND=subtitles requires SRCLANG");
            if (has_src)
                switch (k)
                {   case k_chapters :
                    case k_metadata :
                        check_extension_compatibility (nits (), node_.version (), vu, MIME_TEXT);
                        break;
                    default :
                        check_extension_compatibility (nits (), node_.version (), vu, mime_text_vtt); } }
        else if (has_src)
            check_extension_compatibility (nits (), node_.version (), vu, MIME_TEXT);
        if (a_.known (a_label))
            if (a_.get_string (a_label).empty ())
                pick (nit_empty, ed_50, "4.7.9 The track element", es_error, ec_element, "If LABEL is present, it cannot be empty"); } }

void element::examine_video ()
{   if (! node_.version ().is_5 () && ! node_.version ().is_svg_12 ())
        pick (nit_unknown_element, es_error, ec_element, "<VIDEO> requires HTML 5 or SVG 1.2");
    else
    {   examine_media_element (elem_video, "4.7.6 The video element", "<VIDEO>", MIME_VIDEO);
        if (a_.known (a_autoplay)) pick (nit_autoplay, es_warning, ec_rudeness, "AUTOPLAY on <VIDEO> is unspeakably rude"); } }
