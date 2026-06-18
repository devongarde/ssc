/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "feedback/nitpick.h"
//#include "type/type.h"
#include "url/url.h"

struct required_t
{   e_element e_ = elem_body;
    e_lang lang_ = la_context;
    e_required_page rq_ = rqp_none;
    html_version from_ = html_0, to_ = html_max;
    url url_;
    ::std::string s_, rq_lang_, rq_page_, desc_;
    ::std::string rpt () const; };
typedef ::std::vector < required_t > req_vt;

bool decode_required_page (nitpick& nits, required_t& rq);
bool add_required_page (req_vt& req, nitpick& nits, const ::std::string& arg);
bool add_required_pages (req_vt& req, nitpick& nits, const vstr_t& arg);
int check_required_pages (const req_vt& req, const html_version& v, const e_required_page rqp_type, const ::std::string& page_name, const vurl_t& uref, const element_bitset ancestral_elements, const e_lang l); 
vstr_t required_page_list (const req_vt& req);
e_required_page get_required_page_type (const req_vt& rq, const ::std::string& page_name, const bool root, faux_vb_t& req, faux_vb_t& check);
void check_required_state (const req_vt& rq, nitpick& nits, const ::std::string& name, const faux_vb_t& req, const faux_vb_t& check);
