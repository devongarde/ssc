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
#include "utility/common.h"
#include "main/context.h"
#include "type/type.h"

class options
{   static ::boost::program_options::options_description
        aid_, basic_, cgi_, cmd_, config_, environ_, hidden_, ontology_, primary_, risky_, valid_;
    static ::boost::program_options::positional_options_description pos_;
   ::boost::program_options::variables_map var_, env_var_;
    void help (const ::boost::program_options::options_description& aid) const;
    void init (context_t& c);
    void parse (context_t& c, const output_streams_t& o, nitpick& nits, const vstr_t& vs);
    bool parse (nitpick& nits, const ::boost::filesystem::path& file);
    bool parse (context_t& c, nitpick& nits, const ::boost::filesystem::path& file);
    bool is_be (const char* yo);
    void yea_nay (context_t& c, context_t& (context_t::*fn) (const bool ), nitpick& nits, const char* yea, const char* nay);
    void yea_nay (context_t& c, const e_report r, nitpick& nits, const char* yea, const char* nay);
    void yea_nay (context_t& c, const e_css_module m, nitpick& nits, const char* yea, const char* nay);
    bool get_css_level (int& n, nitpick& nits, const char* opt, const char* name, const int maxlevel, const bool accept_1 = false);
    void process_css_level (context_t& c, const e_css_module m, int& n, nitpick& nits, const char* opt, const char* name, const int maxlevel, const bool accept_1 = false);
    template < class T > void report_variable (const e_gui_report gr, ::std::ostringstream& res, const char* wot, const char* section, int& count, const char* variable) const;
    void report_bool (const e_gui_report gr, ::std::ostringstream& res, const char* yay, const char* nay, const char* section, int& count, const char* ja, const char* nein) const;
    template < e_type TT > void vvextend (context_t& c, const char* const arg);
    template < e_type TT > void vvextend (context_t& c, const char* const a1, const char* const a2);
public:
    options (context_t& c, output_streams_t& o, nitpick& nits, const vstr_t& vs)
    {   parse (c, o, nits, vs); }
    options (nitpick& nits, const ::boost::filesystem::path& fn)
    {   parse (nits, fn); }
    options (context_t& c, nitpick& nits, const ::boost::filesystem::path& fn)
    {   parse (c, nits, fn); }
    explicit options (const context_t& c);
    void contextualise (context_t& c, output_streams_t& o, nitpick& nits);
    template < class T > void insert (const ::std::string& k, const T& t);
    bool write (nitpick& nits, const ::boost::filesystem::path& fn) const;
    ::std::string report (const e_gui_report gr, const bool file = false, const bool wibble = true) const; };

// https://stackoverflow.com/questions/56056265/insert-into-boostprogram-optionsvariables-map-by-index-operator#56056772
template < class T > inline void options::insert (const ::std::string& k, const T& t)
{   var_.::std::map < ::std::string, ::boost::program_options::variable_value >::operator [] (k).value () = ::boost::any (t); }

template < > inline void options::insert < ::boost::any > (const ::std::string& k, const ::boost::any& t)
{   var_.::std::map < ::std::string, ::boost::program_options::variable_value >::operator [] (k).value () = t; }

template < > inline void options::insert < ::std::string > (const ::std::string& k, const ::std::string& t)
{   var_.::std::map < ::std::string, ::boost::program_options::variable_value >::operator [] (k).value () = t; }
