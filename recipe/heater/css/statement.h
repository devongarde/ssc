/*
ssc (static site checker)
File Info
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
#include "css/properties.h"
#include "css/rules.h"
#include "css/ffvs.h"
#include "css/descriptors.h"
#include "css/media.h"
#include "css/css_pre.h"

class statement
{   type_master < t_css_statement > st_;
    properties prop_;
    rules rules_;
    vpst_t vst_;
    selectors sel_;
    descriptors dsc_;
    media_t media_;
    font_features annotation_, character_variant_, historical_form_, ornament_, swash_, styleset_, stylistic_;
    e_css_statement prev_ = css_error;
    bool blank_else_ = false;
    void parse_charset (arguments& args, nitpick& nits, const int from, const int to);
    void parse_colour_profile (arguments& args, nitpick& nits, const int from, const int to);
    void parse_counter_style (arguments& args, nitpick& nits, const int from, const int to);
    void parse_container (arguments& args, nitpick& nits, const int from, const int to);
    void parse_custom_media (arguments& args, nitpick& nits, const int from, const int to);
    void parse_else (arguments& args, nitpick& nits, const int from, const int to);
    void parse_feature_value (arguments& args, nitpick& nits, const int to, const e_css_statement cs, font_features& ffv);
    void parse_font_feature_values (arguments& args, nitpick& nits, const int from, const int to);
    void parse_font_face (arguments& args, nitpick& nits, const int to);
    void parse_font_palette_values (arguments& args, nitpick& nits, const int from, const int to);
    void parse_import (arguments& args, nitpick& nits, const int from, const int to);
    void parse_keyframes (arguments& args, nitpick& nits, const int from, const int to);
    void parse_layer (arguments& args, nitpick& nits, const int from, const int to);
    void parse_margin (arguments& args, nitpick& nits, const int from, const int to, const e_css_statement cs);
    void parse_media (arguments& args, nitpick& nits, const int from, const int to);
    void parse_namespace (arguments& args, nitpick& nits, const int from, const int to);
    void parse_page (arguments& args, nitpick& nits, const int from, const int to);
    void parse_scope (arguments& args, nitpick& nits, const int from, const int to);
    void parse_supports (arguments& args, nitpick& nits, const int from, const int to);
    void parse_viewport (arguments& args, nitpick& nits, const int from, const int to);
    void parse_when (arguments& args, nitpick& nits, const int from, const int to);
    void bracketed_property (arguments& args, nitpick& nits, const int to, int& i, const bool atsupports = false, const e_supports su = su_none);
    void conditional (arguments& args, nitpick& nits, const int from, const int to);
public:
    DEFAULT_CONSTRUCTORS (statement);
    statement (arguments& args, const int from, const int to)
    {   parse (args, from, to); }
    e_css_statement get () const;
    void parse (arguments& args, const int from, const int to);
    void add_child (pst_t ps) { vst_.push_back (ps); }
    void validate (arguments& args);
    void accumulate (stats_t* s) const;
    void shadow (::std::stringstream& ss, arguments& args);
    ::std::string rpt () const; };

typedef ::std::vector < statement > vst_t;
