/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "css/distilled.h"
#include "css/css_parse.h"
#include "element/state.h"

class page;
class selectors;
class statement;
class css_group;
class properties;
class font_features;

struct arguments
{   css_group& g_;
    html_version v_;
    namespaces_ptr ns_;
    bool sv_ = true;
    bool snippet_ = false;
    bool had_rule_ = false;
    e_element styled_ = elem_undefined;
    ::std::string abs_;
    dst_ptr dst_;
    vtt_t t_;
    selectors* ss_ = nullptr;
    statement* st_ = nullptr;
    properties* ps_ = nullptr;
    font_features* ffs_ = nullptr;
    element_bitset eb_;
    arguments (const html_version& v, const namespaces_ptr& namespaces, css_group& g);
    arguments (const html_version& v, const namespaces_ptr& namespaces, css_group& g, bool sv, bool snippet, const e_element styled, const element_bitset eb);
    arguments (const html_version& v, const namespaces_ptr& namespaces, css_group& g, bool sv, bool snippet, const ::std::string& abs, dst_ptr dst, const e_element styled, const element_bitset eb);
    bool prep_for_make (nitpick& nits, const int from, int& b, const int to, int& var, int& bang, css_token& p, bool& xs, bool& xk, bool& xn, bool& xi, bool& fn, bool& clean, int& kc, ::std::string& val);
    void check_flags (nitpick& nits, const flags_t f, const ::std::string& s) const;
    void check_flags (nitpick& nits, const flags_t f, const ::std::string& s, const bool xk, const bool xi, const bool xn, const bool xs, const bool fn, const bool clean, const int kc, const ::std::string& item, const ::std::string& val) const;
    const ustr_t& custom_media () const; 
    ustr_t& custom_media ();
    const sstr_t& font_family () const; 
    sstr_t& font_family ();
    const sstr_t& font_feature (const e_css_statement st) const; 
    sstr_t& font_feature (const e_css_statement st);
    const sstr_t& palette () const; 
    sstr_t& palette ();
    e_css_statement cs () const;
    bool styled () const noexcept { return styled_ != elem_undefined; }
    void validate (nitpick& nits, const flags_t f, const ::std::string& p, const ::std::string& v) const; };
