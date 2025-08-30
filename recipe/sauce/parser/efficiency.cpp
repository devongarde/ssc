/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "parser/parse_elements.h"
#include "main/context.h"
#include "parser/text.h"
#include "parser/efficiency.h"
#include "element/parentage.h"

bool closure_required (const e_element e, bool allow_no, const element_bitset& bs)
{   const bool pos = bs.test (e);
    if (allow_no) return ! pos;
    return pos; }

bool uppity_closure_required (const element_node& current, bool uppity_allow_no, const element_bitset& uppity)
{   PRESUME (current.has_parent (), __FILE__, __LINE__);
    return closure_required (current.parent ().id ().get (), uppity_allow_no, uppity); } 

bool next_closure_required (const element_node& current, bool next_allow_no, const element_bitset& next)
{   PRESUME (current.has_next (), __FILE__, __LINE__);
    return closure_required (current.next ().id ().get (), next_allow_no, next); } 

bool closure_required (const element_node& current, bool next_allow_no, const element_bitset& next, bool uppity_allow_no, const element_bitset& uppity)
{   if (current.has_next ())
        if (! current.next ().is_closure ())
            return next_closure_required (current, next_allow_no, next);
    return uppity_closure_required (current, uppity_allow_no, uppity); }

bool not_nice_neighbour (const element_node& current, bool next_allow_now, const element_bitset& post)
{   if (! current.has_next ()) return true;
    if (current.next ().is_closure ()) return true;
    return next_closure_required (current, next_allow_now, post); }

bool not_nice_neighbour_orphaned (const element_node& current, bool next_allow_now, const element_bitset& post)
{   if (current.has_next ())
        if (! current.next ().is_closure ())
            return next_closure_required (current, next_allow_now, post);
    PRESUME (current.has_parent (), __FILE__, __LINE__);
    return current.parent ().has_next (); }

bool is_closure_required (const element_node& current)
{   if (current.id ().unknown ()) return true;
    switch (current.id ().get ())
    {   case elem_body :
        case elem_html :   
        {   const element_bitset post_html = empty_element_bitset | elem_faux_comment; 
            if (! current.has_next ()) return false;
            if (! current.next ().is_closure ()) return next_closure_required (current, false, post_html);
            return false; }
        case elem_caption :   
        case elem_colgroup :   
        case elem_head :   
        {   const element_bitset post_col = empty_element_bitset | elem_faux_comment | elem_faux_whitespace; 
            if (! current.has_next ()) return false;
            if (! current.next ().is_closure ()) return next_closure_required (current, false, post_col);
            return false; }
        case elem_dd :
            return not_nice_neighbour_orphaned (current, true, empty_element_bitset | elem_dd | elem_dt); 
        case elem_dt :   
            return not_nice_neighbour (current, true, empty_element_bitset | elem_dd | elem_dt); 
        case elem_li :   
            return not_nice_neighbour_orphaned (current, true, empty_element_bitset | elem_li);
        case elem_optgroup :
            return not_nice_neighbour_orphaned (current, true, empty_element_bitset | elem_hr | elem_optgroup);
        case elem_option :
            return not_nice_neighbour_orphaned (current, true, empty_element_bitset | elem_hr | elem_optgroup | elem_option);
        case elem_p :   
        {   const element_bitset post_p = empty_element_bitset |
                elem_address | elem_article | elem_aside | elem_blockquote | elem_details | elem_dialogue | elem_div | elem_dl | elem_fieldset |
                elem_figcaption | elem_figure | elem_footer | elem_form | elem_h1 | elem_h2 | elem_h3 | elem_h4 | elem_h5 | elem_h6 | elem_header |
                elem_hgroup | elem_hr | elem_main | elem_menu | elem_nav | elem_ol | elem_p | elem_pre | elem_search | elem_section | elem_table | elem_ul; 
            const element_bitset nasty_p_mummy =  empty_element_bitset |
                elem_a | elem_audio | elem_custom | elem_del | elem_ins | elem_map | elem_noscript | elem_video;
            return closure_required (current, true, post_p, false, nasty_p_mummy); }
        case elem_rp :   
        case elem_rt :   
            return not_nice_neighbour_orphaned (current, true, empty_element_bitset | elem_rp | elem_rt); 
        case elem_tbody :   
            return not_nice_neighbour_orphaned (current, true, empty_element_bitset | elem_tbody | elem_tfoot); 
        case elem_td :   
        case elem_th :   
            return not_nice_neighbour_orphaned (current, true, empty_element_bitset | elem_td | elem_th); 
        case elem_tfoot :   
            PRESUME (current.has_parent (), __FILE__, __LINE__);
            return current.parent ().has_next ();
        case elem_thead :
            return not_nice_neighbour (current, true, empty_element_bitset | elem_tbody | elem_tfoot); 
        case elem_tr :   
            return not_nice_neighbour_orphaned (current, true, empty_element_bitset | elem_tr); 
        default :
            break; }
    return true; }

void report_closure (nitpick& nits, const e_nit nit, const html_version& v, const element_node& current)
{   if (context.analysis () == anal_original)
        nits.pick (nit, es_warning, ec_element, "</", current.id ().name (), "> is missing");
    else if (! current.id ().is_lazy (v))
        nits.pick (nit, es_error, ec_element, "</", current.id ().name (), "> is missing and required");
    else if (is_closure_required (current))
        nits.pick (nit, es_error, ec_element, "</", current.id ().name (), "> is missing and required in this case");
    else if (context.efficient ())
        nits.pick (nit_inefficient, ed_jun23, "1.11.2: Errors that result in disproportionately poor performance", es_info, ec_element,
            "</", elem :: name (current.tag ()), "> is optional, but its absence may waste browser resources"); }

bool is_open_required (const elem& id, const element_node& current)
{   if (context.analysis () == anal_original) return false;
    if (! current.has_child ()) return false;
    switch (id.get ())
    {   case elem_body :
        {   const element_bitset post_body = empty_element_bitset |
                elem_faux_comment | elem_meta | elem_noscript | elem_link | elem_script | elem_style | elem_template;
            return post_body.test (current.child ().id ()); }
        case elem_colgroup :
        {   if (! current.has_previous ()) break;
            const element_bitset pre_cg = empty_element_bitset | elem_colgroup;
            if (! pre_cg.test (current.previous ().id ())) break;
            if (! current.previous ().has_child ()) break;
            if (! current.previous ().child ().is_closure ()) break;
            const element_bitset post_cg = empty_element_bitset | elem_col;
            return post_cg.test (current.child ().id ()); }
        case elem_head :
            return faux_bitset.test (current.child ().id ());
        case elem_html :
        {   const element_bitset post_html = empty_element_bitset | elem_faux_comment;
            return post_html.test (current.child ().id ()); }
        case elem_tbody :
        {   if (! current.has_previous ()) break;
            const element_bitset pre_tbody = empty_element_bitset | elem_tbody | elem_thead | elem_tfoot;
            if (! pre_tbody.test (current.previous ().id ())) break;
            if (! current.previous ().has_child ()) break;
            if (! current.previous ().child ().is_closure ()) break;
            const element_bitset post_tbody = empty_element_bitset | elem_tr;
            return post_tbody.test (current.child ().id ()); }
        default : break; }
    return true; }
