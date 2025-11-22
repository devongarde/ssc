/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "webpage/vtt.h"
#include "parser/html_version.h"
#include "main/context.h"
#include "css/group.h"

#define VTT_NOTE        "NOTE"
#define VTT_REGION      "REGION"
#define VTT_STYLE       "STYLE"
#define VTT_WEBVTT      "WEBVTT"
#define VTT_CUE         "-->"

bool operator < (const vtt_timestamp& from, const vtt_timestamp& to)
{   if (from.hour_ < to.hour_) return true;
    if (from.hour_ > to.hour_) return false;   
    if (from.minute_ < to.minute_) return true;
    if (from.minute_ > to.minute_) return false;   
    if (from.second_ < to.second_) return true;
    if (from.second_ > to.second_) return false;   
    return from.millisecond_ < to.millisecond_; }

vtt_t::vtt_t (nitpick& nits, const html_version& v, const ::std::string& content, css_group& css)
    : nits_ (nits), v_ (v), b_ (content.cbegin ()), e_ (content.cend ()), i_ (b_), w_ (b_), z_ (e_), css_ (css)
{   if (lt  (v_, html_vtt_14))
        nits_.pick (nit_version, ed_vtt, "W3C First Public Working Draft 13 November 2014", es_error, ec_vtt, "WebVTT files postdate ", v_.name ());
    else if (content.empty ())
        nits_.pick (nit_empty, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "a valid WebVTT file cannot be empty");
    else invalid_ = parse (); }

::std::string vtt_t::gather_string (const int i, const char* sit, const char* sep)
{   ::std::string snippet;
    for (int n = gather_from_; n < i; ++n)
    {   if (lines_.at (n).collect_.find (VTT_CUE) != ::std::string::npos)
            lines_.at (n).nits_.pick (nit_vtt_bad_cue, ed_vtt, "4.3. WebVTT region settings", es_error, ec_vtt, sit, " settings must not contain \"" VTT_CUE "\"");
        snippet += lines_.at (n).collect_;
        snippet += sep; }
    return snippet; }

vstr_t vtt_t::gather_block (const int i, const char* sit, const char* sep)
{   return uq5 (gather_string (i, sit, sep)); }

void vtt_t::process_css (const int i)
{   const ::std::string snippet = gather_string (i, VTT_STYLE, "\n");
    css_.parse (snippet, v_, namespaces_ptr (), empty_element_bitset, gather_from_);
    gather_ = vg_nowt; }

bool vtt_t::process_setting_value (const int i, const ::std::string& s, e_vtt_token& tkn, ::std::string& setting, ::std::string& value)
{   const ::std::string::size_type pos = s.find (':');
    bool res = true;
    if (pos == ::std::string::npos)
    {   lines_.at (i).nits_.pick (nit_vtt_region, ed_vtt, "4.3. WebVTT region settings", es_error, ec_vtt, "", quote (s), " is missing a value");
        setting = s; value.clear ();
        res = false; }
    else if (pos == s.size () - 1)
    {   lines_.at (i).nits_.pick (nit_vtt_region, ed_vtt, "4.3. WebVTT region settings", es_error, ec_vtt, "", quote (s), " has an empty value");
        setting = s.substr (0, pos); value.clear ();
        res = false; }
    else if (pos == 0)
    {   lines_.at (i).nits_.pick (nit_vtt_region, ed_vtt, "4.3. WebVTT region settings", es_error, ec_vtt, "", quote (s), " is missing a setting name");
        return false; }
    else
    {   setting = s.substr (0, pos);
        value = s.substr (pos+1); }
    tkn = examine_value < t_vtt_token > (lines_.at (i).nits_, v_, setting);
    return res; }

void vtt_t::process_cue_part (const int i, const ::std::string& setting, bool& preused)
{   if (preused) lines_.at (i).nits_.pick (nit_vtt_cue, ed_vtt, "4.4. WebVTT cue settings", es_error, ec_vtt, "only one ", quote (setting), " per cue");
    preused = true; }

void vtt_t::process_region_part (const int i, const ::std::string& setting, bool& preused)
{   if (preused) lines_.at (i).nits_.pick (nit_vtt_region, ed_vtt, "4.3. WebVTT region settings", es_error, ec_vtt, "only one ", quote (setting), " per REGION");
    preused = true; }

void vtt_t::percent_pair (const int i, const ::std::string& s, const ::std::string& setting)
{   const ::std::string::size_type pos = s.find (',');
    if ((pos == ::std::string::npos) || (pos == 0) || (pos == s.size () - 1))
        lines_.at (i).nits_.pick (nit_vtt_region, es_error, ec_vtt, quote (setting), ": expecting x%,y%");
    else
    {   test_value < t_percent > (lines_.at (i).nits_, v_, s.substr (0, pos));
        test_value < t_percent > (lines_.at (i).nits_, v_, s.substr (pos+1)); } }

void vtt_t::process_region (const int i)
{   vstr_t vs = gather_block (i, VTT_REGION, " ");
    bool id = false, width = false, lines = false, ra = false, va = false, scr = false;
    msid_t::const_iterator ii = sregion_.cend ();
    for (auto &s : vs)
    {   e_vtt_token tkn;
        ::std::string setting, value;
        if (! process_setting_value (gather_from_, s, tkn, setting, value)) continue;
        switch (tkn)
        {   case vtk_identifier :
                process_region_part (gather_from_, setting, id);
                ii = sregion_.find (value);
                if (ii != sregion_.cend ())
                {   lines_.at (gather_from_).nits_.pick (nit_vtt_region_id, ed_vtt, "4.3. WebVTT region settings", es_error, ec_vtt, quote (value), " must be unique; it was previously used on or near line ", ii -> second);
                    lines_.at (ii -> second).nits_.pick (nit_vtt_region_id, ed_vtt, "4.3. WebVTT region settings", es_error, ec_vtt, quote (value), " must be unique, yet it is also used on or near line ", i); }
                else
                    sregion_.insert (msid_t::value_type (setting, i));
                break;
            case vtk_width : 
                process_region_part (gather_from_, setting, width);
                test_value < t_percent > (lines_.at (i).nits_, v_, value);
                break;
            case vtk_lines : 
                process_region_part (gather_from_, setting, lines);
                test_value < t_unsigned > (lines_.at (i).nits_, v_, value);
                break;
            case vtk_region_anchor : 
                process_region_part (gather_from_, setting, ra);
                percent_pair  (gather_from_, value, setting);
                break;
            case vtk_viewport_anchor :
                process_region_part (gather_from_, setting, va);
                percent_pair  (gather_from_, value, setting);
                break;
            case vtk_scroll :
                process_region_part (gather_from_, setting, scr);
                if (value != "up") lines_.at (gather_from_).nits_.pick (nit_vtt_region_value, ed_vtt, "4.3. WebVTT region settings", es_error, ec_vtt, quote (setting), ": the required value is \"up\".");
                break;
            default :
                lines_.at (gather_from_).nits_.pick (nit_vtt_region, ed_vtt, "4.3. WebVTT region settings", es_error, ec_vtt, "", quote (setting), " is an unknown region setting");
                break; } }
    if (! id) lines_.at (gather_from_).nits_.pick (nit_vtt_region_id, ed_vtt, "4.3. WebVTT region settings", es_error, ec_vtt, "an identifier setting is required");
    gather_ = vg_nowt; }

bool vtt_t::process_timestamp (const int i, const ::std::string& ss, vtt_timestamp& ts)
{   bool res = true;
    ::std::string s (ss);
    const ::std::string::size_type dp = s.find ('.');
    if (dp != ::std::string::npos)
    {   res = false;
        if ((dp == 0) || (dp == s.size () - 1))
            lines_.at (i).nits_.pick (nit_vtt_timestamp, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "", quote (ss), " has malformed milliseconds.");  
        else
        {   const ::std::string& ms = s.substr (dp+1);
            if (test_value < t_unsigned > (lines_.at (i).nits_, v_, ms))
            {   ts.millisecond_ = lexical < unsigned int > :: cast (ms);
                res = true; } }
        if (dp == 0) s = s.substr (1);
        else s = s.substr (0, dp); }
    ::std::string::size_type colon = s.find (':');
    if ((colon == ::std::string::npos) || (colon == 0) || (colon == s.size () - 1))
    {   lines_.at (i).nits_.pick (nit_vtt_timestamp, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "", quote (ss), " has a malformed time (1).");
        return false; }
    const ::std::string::size_type pos2 = s.substr (colon+1).find (':');
    if ((pos2 == 0) || (pos2 == s.size () - colon - 1))
    {   lines_.at (i).nits_.pick (nit_vtt_timestamp, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "", quote (ss), " has a malformed time (2).");
        return false; }
    if (pos2 != ::std::string::npos)
    {   ts.hour_ = lexical < unsigned int > :: cast (s.substr (0, colon-1));
        s = s.substr (colon+1);
        colon = s.find (':');
        PRESUME (colon != ::std::string::npos, __FILE__, __LINE__);
        PRESUME (colon != 0, __FILE__, __LINE__);
        PRESUME (colon != s.size () - 1, __FILE__, __LINE__); }
    ts.minute_ = lexical < unsigned short > :: cast (s.substr (0, colon));
    ts.second_ = lexical < unsigned short > :: cast (s.substr (colon+1));
    if (ts.minute_ > 59)
    {   lines_.at (i).nits_.pick (nit_vtt_timestamp, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, quote (ss), ": those minutes are daft.");
        res = false; }
    if (ts.second_ == 60)
    {   lines_.at (i).nits_.pick (nit_vtt_timestamp, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, quote (ss), ": no leap seconds in a VTT file.");
        res = false; }
    else if (ts.second_ > 59)
    {   lines_.at (i).nits_.pick (nit_vtt_timestamp, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, quote (ss), ": those seconds are daft.");
        res = false; }
    return res; }

void vtt_t::close_cue_payload (const int x, const e_vtt_token tkn)
{   while (payloads_.size () > 0)
    {   const bool ok = payloads_.at (payloads_.size () - 1) == tkn;
        payloads_.pop_back ();
        if (ok) return;
        lines_.at (x).nits_.pick (nit_vtt_heirarchy, ed_vtt, "4.2.2. WebVTT caption or subtitle cue text", es_error, ec_vtt, "missing </", type_master < t_vtt_token > :: name (tkn), ">"); }
    lines_.at (x).nits_.pick (nit_vtt_heirarchy, ed_vtt, "4.2.2. WebVTT caption or subtitle cue text", es_error, ec_vtt, "cannot find </", type_master < t_vtt_token > :: name (tkn), ">"); }

void vtt_t::open_cue_payload (const int x, const e_vtt_token tkn, const vstr_t& space, const vstr_t& dotty)
{   payloads_.push_back (tkn);
    bool rup = false;
    switch (tkn)
    {   case vtk_lang_span:
            if (space.size () < 2)
                lines_.at (x).nits_.pick (nit_vtt_annotation, ed_vtt, "4.4. WebVTT cue settings", es_error, ec_vtt, "lang requires a language");
            else 
            {   test_value < t_lang > (lines_.at (x).nits_, v_, space.at (1));
                if (space.size () > 2)
                    lines_.at (x).nits_.pick (nit_vtt_annotation, ed_vtt, "4.4. WebVTT cue settings", es_error, ec_vtt, "lang requires one language only"); }
            break;
        case vtk_voice_span:
            if (space.size () < 2)
                lines_.at (x).nits_.pick (nit_vtt_annotation, ed_vtt, "4.4. WebVTT cue settings", es_error, ec_vtt, "v requires a (speaker) name");
            break;
        case vtk_rt_span :
            rup = false;
            for (auto evt : payloads_)
                if (evt == vtk_ruby_span)
                {   rup = true; break; }
            if (! rup) lines_.at (x).nits_.pick (nit_vtt_heirarchy, ed_vtt, "4.4. WebVTT cue settings", es_error, ec_vtt, "<rt> requires a <ruby> parent");
            FALLTHROUGH;
        default :
            if (space.size () > 1)
                lines_.at (x).nits_.pick (nit_vtt_annotation, ed_vtt, "4.4. WebVTT cue settings", es_error, ec_vtt, type_master < t_vtt_token > :: name (tkn), " cannot be annotated");
            break; }
    for (unsigned int n = 1; n < dotty.size (); ++n)
        if (dotty.at (n).empty ())
            lines_.at (x).nits_.pick (nit_vtt_class, ed_vtt, "4.4. WebVTT cue settings", es_error, ec_vtt, "empty class name found");
        else
        {   const ::std::string& c = dotty.at (n);
            msid_t::iterator i = class_.find (c);
            if (i != class_.end ()) i -> second += 1;
            else class_.insert (msid_t::value_type (c, 1));
            nitpick nuts;
            const e_vtt_token col = examine_value < t_vtt_token > (nuts, v_, c);
            switch (col)
            {   case vtk_bg_black :
                case vtk_bg_blue :
                case vtk_bg_cyan :
                case vtk_bg_lime :
                case vtk_bg_magenta :
                case vtk_bg_red :
                case vtk_bg_white :
                case vtk_bg_yellow :
                    lines_.at (x).nits_.merge (nuts);
                    if ((n != 2) && (n != 4))
                        lines_.at (x).nits_.pick (nit_vtt_class, ed_vtt, "4.4. WebVTT cue settings", es_warning, ec_vtt, type_master < t_vtt_token > :: name (col), ": use of background colour in foreground");
                    break;    
                case vtk_black :
                case vtk_blue :
                case vtk_cyan :
                case vtk_lime :
                case vtk_magenta :
                case vtk_red :
                case vtk_white :
                case vtk_yellow :
                    lines_.at (x).nits_.merge (nuts);
                    if ((n != 1) && (n != 3))
                        lines_.at (x).nits_.pick (nit_vtt_class, ed_vtt, "4.4. WebVTT cue settings", es_warning, ec_vtt, type_master < t_vtt_token > :: name (col), ": use of foreground colour in background");
                    break;    
                default :
                    if (! css_.has_class (dotty.at (n)))
                        lines_.at (x).nits_.pick (nit_vtt_class, ed_vtt, "4.4. WebVTT cue settings", es_warning, ec_vtt, quote (dotty.at (n)), ": unknown class");
                    break; } } }

void vtt_t::process_cue_payloads (const int x, const ::std::string::const_iterator& f, const ::std::string::const_iterator& t)
{   bool closure = false;
    vstr_t space, dotty;
    e_vtt_token tkn = vtk_none;
    if (*f == '/')
    {   const ::std::string::const_iterator f2 = f + 1;
        if (*f2 == '>')
            lines_.at (x).nits_.pick (nit_empty, ed_vtt, "4.2.2. WebVTT caption or subtitle cue text", es_error, ec_vtt, "'</>' ??");
        else closure = true;
        tkn = examine_value < t_vtt_token > (lines_.at (x).nits_, v_, ::std::string (f2, t)); }
    else
    {   space = split_by_space (::std::string (f, t));
        if (space.empty ())
            lines_.at (x).nits_.pick (nit_vtt_cue, ed_vtt, "4.2.2. WebVTT caption or subtitle cue text", es_error, ec_vtt, "'< ?? >'");
        else dotty = split_by_charset (space.at (0), ".");
        if (dotty.at (0).empty ())
            lines_.at (x).nits_.pick (nit_vtt_cue, ed_vtt, "4.2.2. WebVTT caption or subtitle cue text", es_error, ec_vtt, "malformed cue span");
        else tkn = examine_value < t_vtt_token > (lines_.at (x).nits_, v_, dotty.at (0)); }
    switch (tkn)
    {   case vtk_bold_span :
        case vtk_class_span :
        case vtk_italics_span :
        case vtk_lang_span :
        case vtk_rt_span :
        case vtk_ruby_span :
        case vtk_underline_span :
        case vtk_voice_span :
            if (closure) close_cue_payload (x, tkn);
            else open_cue_payload (x, tkn, space, dotty);
            break;
        default :  
            lines_.at (x).nits_.pick (nit_vtt_cue, ed_vtt, "4.2.2. WebVTT caption or subtitle cue text", es_warning, ec_vtt, quote (::std::string (f, t)), " is either an unknown cue payload, or perhaps consider using &lt; / &gt;?");
            break; } }

void vtt_t::process_cue (const int i)
{   PRESUME (gather_from_ > 0 && gather_from_ <= i, __FILE__, __LINE__);
    const ::std::string& cue = lines_.at (gather_from_).collect_;
    const vstr_t vc = uq5 (cue);   
    if (vc.size () < 3)
        lines_.at (gather_from_).nits_.pick (nit_vtt_bad_cue, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "expecting timestamp --> timestamp");
    else if (vc.at (1) != VTT_CUE)
        lines_.at (gather_from_).nits_.pick (nit_vtt_bad_cue, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "expecting timestamp --> timestamp");
    else
    {   vtt_timestamp from, to;
        process_timestamp (gather_from_, vc.at (0), from);
        process_timestamp (gather_from_, vc.at (2), to);
        if (to < from)
        {   lines_.at (gather_from_).nits_.pick (nit_vtt_timestamp, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "", vc.at (0), " follows ", vc.at (2));
            ::std::swap (from, to); }
        if (from < prev_)
            lines_.at (gather_from_).nits_.pick (nit_vtt_timestamp, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "cues must be listed in ascending start time order");
        else prev_ = from;
        bool al = false, li = false, posit = false, reg = false, si = false, vert = false;
        vstr_t vs;
        for (unsigned int n = 3; n < vc.size (); ++n)
        {   e_vtt_token tkn;
            ::std::string setting, value;
            if (! process_setting_value (gather_from_, vc.at (n), tkn, setting, value)) continue;
            switch (tkn)
            {   case vtk_align :
                    process_cue_part (gather_from_, setting, al);
                    test_value < t_celrs > (lines_.at (gather_from_).nits_, v_, value);
                    break;
                case vtk_line :
                    process_cue_part (gather_from_, setting, li);
                    vs = split_by_comma (value);
                    if (vs.size () == 1) test_value < t_percent_or_neg > (lines_.at (gather_from_).nits_, v_, value);
                    else
                    {   test_value < t_percent_or_neg > (lines_.at (gather_from_).nits_, v_, vs.at (0));
                        if (ge (v_, html_vtt_15)) test_value < t_ces > (lines_.at (gather_from_).nits_, v_, vs.at (1));
                        else test_value < t_ems > (lines_.at (gather_from_).nits_, v_, vs.at (1)); }
                    break;
                case vtk_position :
                    process_cue_part (gather_from_, setting, posit);
                    vs = split_by_comma (value);
                    if (vs.size () == 1) test_value < t_percent_or_neg > (lines_.at (gather_from_).nits_, v_, value);
                    else
                    {   test_value < t_percent_or_neg > (lines_.at (gather_from_).nits_, v_, vs.at (0));
                        if (ge (v_,html_vtt_16)) test_value < t_clllr > (lines_.at (gather_from_).nits_, v_, vs.at (1));
                        else if (ge (v_, html_vtt_15)) test_value < t_ces > (lines_.at (gather_from_).nits_, v_, vs.at (1));
                        else test_value < t_ems > (lines_.at (gather_from_).nits_, v_, vs.at (1)); }
                    break;
                case vtk_region_lc :
                    process_cue_part (gather_from_, setting, reg);
                    if (sregion_.find (value) == sregion_.cend ())
                         lines_.at (gather_from_).nits_.pick (nit_vtt_region, ed_vtt, "4.4. WebVTT cue settings", es_warning, ec_vtt, quote (value), ": unknown REGION");
                   break;
                case vtk_size :
                    process_cue_part (gather_from_, setting, si);
                    test_value < t_percent > (lines_.at (gather_from_).nits_, v_, value);
                    break;
                case vtk_vertical :
                    process_cue_part (gather_from_, setting, vert);
                    if ((value != "rl") && (value != "lr"))
                        lines_.at (gather_from_).nits_.pick (nit_vtt_cue, ed_vtt, "4.4. WebVTT cue settings", es_error, ec_vtt, "", quote (setting), " expects 'rl' or 'lr', not ", quote (value));
                    break;
                default:
                    lines_.at (gather_from_).nits_.pick (nit_vtt_cue, ed_vtt, "4.4. WebVTT cue settings", es_error, ec_vtt, "", quote (setting), " is an unknown cue setting");
                    break; } } }
    for (int x = gather_from_ + 1; x < i; ++x)
    {   const ::std::string& l = lines_.at (x).collect_;
        const ::std::string::const_iterator b = l.cbegin ();
        const ::std::string::const_iterator e = l.cend ();
        ::std::string::const_iterator f = e;
        ::std::string::const_iterator t = e;
        for (::std::string::const_iterator ci = b; ci < e; ++ci)
            switch (*ci)
            {   case '<' :
                    f = ci+1;
                    break;
                case '>':
                    if (f < e)
                    {   t = ci;
                        if (t == f) lines_.at (x).nits_.pick (nit_empty, ed_vtt, "4.2.2. WebVTT caption or subtitle cue text", es_error, ec_vtt, "'<>' ??");
                        else process_cue_payloads (x, f, t);
                        f = t = e; }
                    break;
                default :
                    break; }
        if (f != e)
            lines_.at (x).nits_.pick (nit_vtt_cue, ed_vtt, "4.2.2. WebVTT caption or subtitle cue text", es_error, ec_vtt, "'<' without '>'? Should \'&lt;\' be used?"); }
    gather_ = vg_nowt; }

void vtt_t::prepare_common (const int i, const char* sz, e_vtt_gathering g, e_nit ne, const html_version& v)
{   if (gt (v, v_))
        lines_.at (i).nits_.pick (nit_version, es_error, ec_vtt, "", sz, " postdates ", v_.name ());
    if (status_ != vs_prologue)
        lines_.at (i).nits_.pick (ne, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "", sz, "s must precede cues");
    if (trim_the_lot_off (lines_.at (i).collect_) != sz)
        lines_.at (i).nits_.pick (ne, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "", sz, " must be alone on a line");
    gather_ = g;  
    gather_from_ = i+1; }

void vtt_t::prepare_css (const int i)
{   prepare_common (i, VTT_STYLE, vg_css, nit_vtt_css, html_vtt_15); }  

void vtt_t::prepare_region (const int i)
{   prepare_common (i, VTT_REGION, vg_region, nit_vtt_region, html_vtt_16); }  

void vtt_t::prepare_cue (const int i)
{   status_ = vs_cue;
    gather_ = vg_cue;  
    if (lines_.at (i).collect_.find (VTT_CUE) == ::std::string::npos)
    {   gather_from_ = i + 1;
        const ::std::string value (lines_.at (i).collect_);
        msid_t::const_iterator si = sid_.find (value);
        if (si != sid_.cend ())
        {   lines_.at (i).nits_.pick (nit_vtt_bad_id, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "identifier ", quote (value), " is not unique; it was previously used at line ", si -> second);
            lines_.at (si -> second).nits_.pick (nit_vtt_bad_id, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, quote (value), " must be unique, yet it is also used at line ", i); }
        else sid_.insert (msid_t::value_type (value, i)); }
    else gather_from_ = i; }

void vtt_t::note (const int i)
{   if (lines_.at (i).collect_.find (VTT_CUE) != ::std::string::npos)
        lines_.at (i).nits_.pick (nit_vtt_bad_cue, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "a comment must not contain \"-->\""); }

bool vtt_t::parse ()
{   for (; i_ != e_; ++i_)
        switch (*i_)
        {   case '\n' :
            case '\r' : 
            case '\v' :
                if (w_ == i_) lines_.push_back (vtt_line (++line_));
                else
                {   if (i_ > b_) z_ = i_;
                    lines_.push_back (vtt_line (++line_, w_, z_)); }
                if ((i_ < e_ - 1) && (*i_ == '\r') && (*(i_ + 1) == '\n')) ++i_;
                w_ = z_ = i_ + 1;
                break;
            default :
                break; }
    unsigned int i = 0;
    for ( ; i < lines_.size () && lines_.at (i).collect_.empty (); ++i);
    bool preblanked = true;
    if ((lines_.at (i).collect_.size () >= 6) && (lines_.at (i).collect_.substr (0, 6) == VTT_WEBVTT))
    {   status_ = vs_prologue;
        gather_ = vg_nowt;
        while (++i < lines_.size ())
            if (lines_.at (i).collect_.empty ())
            {   switch (gather_)
                {   case vg_css : process_css (i); break;
                    case vg_region : process_region (i); break;
                    case vg_cue : process_cue (i); break;
                    default : break; }
                preblanked = true; }
            else if (preblanked)
            {   if ((lines_.at (i).collect_.size () >= 5) && (lines_.at (i).collect_.substr (0, 5) == VTT_STYLE))
                    prepare_css (i);
                else if ((lines_.at (i).collect_.size () >= 6) && (lines_.at (i).collect_.substr (0, 6) == VTT_REGION))
                    prepare_region (i);
                else if ((lines_.at (i).collect_.size () >= 4) && (lines_.at (i).collect_.substr (0, 4) == VTT_NOTE))
                    note (i);
                else prepare_cue (i);
                preblanked = false; } }
    else    
    {   nits_.pick (nit_webvtt, ed_vtt, "4.1. WebVTT file structure", es_error, ec_vtt, "does not start, as required, with WEBVTT, so this is not a VTT files.");         
        invalid_ = true; }
    return ! invalid_; }

void vtt_t::accumulate (stats_t* s)
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    nits_.accumulate (s);
    for (auto& l : lines_)
        if (! l.nits_.empty ())
            l.nits_.accumulate (s);
    for (auto& c : class_)
        s -> use_class (c.first, c.second); }

::std::string vtt_t::review (const mmac_t& mac) const
{   ::std::string res = nits_.review (mac);
    for (auto& l : lines_)
        if (! l.nits_.empty ())
            res += l.nits_.review (mac);
    return res; }   
   