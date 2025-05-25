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

#pragma once
#include "main/version.h"
#include "feedback/nitpick.h"
#include "webpage/page.h"

struct vtt_timestamp
{   unsigned int hour_ = 0;
    unsigned short minute_ = 0, second_ = 0, millisecond_ = 0; };

inline bool operator == (const vtt_timestamp& from, const vtt_timestamp& to)
{   return (from.hour_ == to.hour_) && (from.minute_ == to.minute_) && (from.second_ == to.second_) && (from.millisecond_ == to.millisecond_); }

bool operator < (const vtt_timestamp& from, const vtt_timestamp& to);

inline bool operator <= (const vtt_timestamp& from, const vtt_timestamp& to)
{   return from < to || from == to; }

inline bool operator > (const vtt_timestamp& from, const vtt_timestamp& to)
{   return ! (from <= to); }

inline bool operator >= (const vtt_timestamp& from, const vtt_timestamp& to)
{   return ! (from < to); }

struct vtt_line
{   ::std::string collect_;
    nitpick nits_;
    explicit vtt_line (const int line) : nits_ (line, collect_) { }
    vtt_line (const int line, const ::std::string::const_iterator b, const ::std::string::const_iterator e)
        : collect_ (b, e), nits_ (line, collect_) { } };

typedef ::std::vector < vtt_line > vvtt_line;

class vtt_t
{   e_vtt_state status_ = vs_start;
    nitpick& nits_;
    vvtt_line lines_;
    const html_version& v_;
    const ::std::string collect_;
    int line_ = 0, gather_from_ = 0;
    const ::std::string::const_iterator b_;
    const ::std::string::const_iterator e_;
    ::std::string::const_iterator i_;
    ::std::string::const_iterator w_;
    ::std::string::const_iterator z_;
    bool invalid_ = true;
    css_group& css_;
    msid_t sid_, sregion_, class_;
    e_vtt_gathering gather_ = vg_nowt;
    vtt_timestamp prev_;
    ::std::vector < e_vtt_token > payloads_;
    ::std::string gather_string (const int i, const char* sit, const char* sep);
    vstr_t gather_block (const int i, const char* sit, const char* sep);
    void note (const int i);
    bool parse ();
    void percent_pair (const int i, const ::std::string& s, const ::std::string& setting);
    void prepare_common (const int i, const char* sz, e_vtt_gathering g, e_nit ne, const html_version& v);
    void prepare_css (const int i);
    void prepare_cue (const int i);
    void prepare_region (const int i);
    void process_cue (const int i);
    void process_cue_part (const int i, const ::std::string& setting, bool& preused);
    void process_cue_payloads (const int x, const ::std::string::const_iterator& f, const ::std::string::const_iterator& t);
    void close_cue_payload (const int x, const e_vtt_token tkn);
    void open_cue_payload (const int x, const e_vtt_token tkn, const vstr_t& space, const vstr_t& dotty);
    void process_css (const int i);
    void process_region (const int i);
    void process_region_part (const int i, const ::std::string& setting, bool& preused);
    bool process_timestamp (const int i, const ::std::string& ss, vtt_timestamp& ts);
    bool process_setting_value (const int i, const ::std::string& s, e_vtt_token& tkn, ::std::string& setting, ::std::string& value);
public:
    DELETE_CONSTRUCTORS (vtt_t);
    vtt_t (nitpick& nits, const html_version& v, const ::std::string& s, css_group& css);
    void accumulate (stats_t* s);
    ::std::string review (mmac_t& mac) const; };
