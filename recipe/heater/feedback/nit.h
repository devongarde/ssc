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
#include "main/include.h"
#include "type/enum.h"

class nit
{   e_nit code_ = nit_free;
    e_severity severity_ = es_undefined;
    e_category category_ = ec_undefined;
    e_doc doc_ = ed_mishmash;
    ::std::string ref_; // location in doc; presumes hard coded string
    ::std::string msg_;
public:
    nit ();
    nit (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, const ::std::string& msg);
    nit (const e_nit code, const e_severity severity, const e_category category, const ::std::string& msg);
    nit (const nit& n) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	nit (nit&& n) = default;
#endif
	~nit() = default;
    nit& operator = (const nit& n) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	nit& operator = (nit&& n) = default;
#endif
	static void init();
    void swap (nit& n) NOEXCEPT;
    void reset ();
    void reset (const nit& n);
    ::std::string review () const;
    void notify () const;
    e_nit code () const { return code_; }
    e_severity severity () const { return severity_; }
    ::std::string msg () const { return msg_; }
    bool empty () const { return code_ == nit_free; } };

::std::string doc_title (const e_doc doc);
