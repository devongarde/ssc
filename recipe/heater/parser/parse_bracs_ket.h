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
#include "parser/parse_brac_ket.h"
#include "main/context.h"

class bracs_ket
{   friend class elements_node;
    typedef ::std::vector < brac_element_ket > ve_t;
    ve_t ve_;
    int line_ = 0;
    nitpick form_;
    void nodoctype (nitpick& nits, html_version& v, ::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i);
    void mixed_mess (nitpick& nits, ::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i, const char* item, const char* inside);
public:
    void swap (bracs_ket& bk) noexcept
    {   ve_.swap (bk.ve_);
        form_.swap (bk.form_);
        ::std::swap (line_, bk.line_); }
    html_version parse (const ::std::string& content);
    html_version parse (const nitpick& nits, const ::std::string& content)
    {   form_.reset (nits);
        return parse (content); }
    ::std::string rpt () const; };
