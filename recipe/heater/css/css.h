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
#include "utility/common.h"
#include "feedback/nitpick.h"
#include "webpage/fileindex.h"
#include "css/distilled.h"
#include "css/statements.h"

class url;
class page;

class css
{   bool snippet_ = false, state_version_ = false;
    mutable bool reviewed_ = false, gathered_ = false;
    statements st_;
    page* page_ = nullptr;
    fileindex_t ndx_ = nullfileindex;
    ::std::string abs_;
    nitpick nits_;
    int line_ = 0;
    dst_ptr dst_;
    void check_for_standard_classes (const html_version& v);
public:
    explicit css (const html_version& v, dst_ptr cp, page* p, const ::std::string& abs, bool state_version, bool snippet, int line);
    explicit css (arguments& args, dst_ptr cp, const ::std::string& content, int line);
    DEFAULT_CONSTRUCTORS_NO_EMPTY (css);
    void swap (css& c) noexcept;
    void reset () noexcept { st_.clear (); }
    bool invalid () const noexcept { return false; }
    bool snippet () const noexcept { return snippet_; }
    void snippet (const bool b)  noexcept{ snippet_ = b; }
    bool has_class (const ::std::string& s) const
    {   VERIFY_NOT_NULL (dst_.get (), __FILE__, __LINE__);
        return dst_ -> has_class (s); }
    bool has_id (const ::std::string& s) const
    {   VERIFY_NOT_NULL (dst_.get (), __FILE__, __LINE__);
        return dst_ -> has_id (s); }
    bool has_element_class (const ::std::string& s) const
    {   VERIFY_NOT_NULL (dst_.get (), __FILE__, __LINE__);
        return dst_ -> has_element_class (s); }
    bool has_element_id (const ::std::string& s) const
    {   VERIFY_NOT_NULL (dst_.get (), __FILE__, __LINE__);
        return dst_ -> has_element_id (s); }
    bool has_namespace (const ::std::string& ) const
    {   return false; }
    bool parse (arguments& args, const ::std::string& content);
    ::std::string review (mmac_t& mac, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none, const bool unfiltered = false) const;
    void accumulate (nitpick& accumulator) const;
    void accumulate (stats_t* s) const;
    void merge (nitpick& nits); 
    const element_bitset get_elements () const { return st_.get_elements (); } };

typedef ::std::shared_ptr < css > css_ptr;
