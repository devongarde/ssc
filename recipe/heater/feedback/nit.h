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
#include "main/include.h"
#include "main/enum.h"
#include "feedback/nitnames.h"
#include "feedback/nitout.h"

class nit
{   e_nit code_ = nit_free;
    e_severity severity_ = es_illegal;
    e_category category_ = ec_undefined;
    e_doc doc_ = ed_mishmash;
    ::std::string ref_; // location in doc; presumes hard coded string
    ::std::string msg_;
    friend bool operator < (const nit& lhs, const nit& rhs);
    ::std::string level_symbol () const;
public:
    nit ();
    DEFAULT_COPY_CONSTRUCTORS (nit);
    nit (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, const ::std::string& msg);
    nit (const e_nit code, const e_severity severity, const e_category category, const ::std::string& msg);
	~nit() = default;
    void swap (nit& n) noexcept;
    void reset ();
    void reset (const nit& n);
    ::std::string review (const e_nit_section& entry, const mmac_t& mac, const mmac_t& outer) const;
    e_nit code () const noexcept { return code_; }
    e_severity severity () const noexcept { return severity_; }
    e_category category () const noexcept { return category_; }
    e_doc doc () const noexcept { return doc_; }
    ::std::string msg () const { return msg_; }
    bool empty () const noexcept { return code_ == nit_free; } };

#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning ( disable : 26440 )
#endif // _MSC_VER
inline bool operator < (const nit& lhs, const nit& rhs)
{   if (lhs.severity_ < rhs.severity_) return true;
    if (lhs.severity_ > rhs.severity_) return false;
    if (lhs.code_ < rhs.code_) return true;
    if (lhs.code_ > rhs.code_) return false;
    return (lhs.msg_.compare (rhs.msg_) < 0); }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

::std::string doc_title (const e_doc doc);
::std::string doc_ref (const e_doc doc);
