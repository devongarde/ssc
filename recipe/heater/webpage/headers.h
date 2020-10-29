/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "main/context.h"

class headers
{   ustr_t header_, links_;
    int code_ = 0;
    bool abusive_site_ = false;
    void parse (nitpick& nits,const html_version& v, const ::std::string& header);
    void process_rels (nitpick& nits,const ::std::string& value);
public:
    headers (nitpick& nits,const html_version& v, const ::std::string http) : code_ (0), abusive_site_ (false)
    {   parse (nits, v, http); }
    void swap (headers& h) noexcept
    {   header_.swap (h.header_);
        links_.swap (h.links_);
        ::std::swap (code_, h.code_);
        ::std::swap (abusive_site_, h.abusive_site_); }
    bool abusive_site () const { return abusive_site_; }
    int code () const { return code_; }
    const ::std::string link (const char * rel) const;
    const ::std::string get (const ::std::string key) const; };
