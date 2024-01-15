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
#include "utility/common.h"
#include "feedback/nitpick.h"
#include "webpage/fileindex.h"
#include "css/distilled.h"
#include "css/statements.h"
#include "css/arguments.h"

class url;
class page;
class css_group;

class css
{   friend struct arguments;
    arguments args_;
    mutable bool reviewed_ = false;
    statements st_;
    page& page_;
    fileindex_t ndx_ = nullfileindex;
    ::std::string abs_;
    const ::boost::filesystem::path dp_ = ::boost::filesystem::path ();
    v_np ticks_;
    int line_ = 0;
    void check_for_standard_classes (const html_version& v);
public:
    explicit css (  const html_version& v, const namespaces_ptr& namespaces, dst_ptr dst, page& p, const ::std::string& abs, bool state_version, bool snippet, int line, const e_element styled,
                    const element_bitset eb, const ::boost::filesystem::path dp = ::boost::filesystem::path ());
    explicit css (  const html_version& v, const ::std::string& content, const namespaces_ptr& namespaces, dst_ptr dst, page& p, const ::std::string& abs, bool state_version, bool snippet,
                    int line, const e_element styled, const element_bitset eb, const ::boost::filesystem::path dp = ::boost::filesystem::path (), const bool mdm = false);
    DELETE_CONSTRUCTORS (css);
    bool invalid () const noexcept { return false; }
    bool snippet () const noexcept { return args_.snippet_; }
    void snippet (const bool b)  noexcept { args_.snippet_ = b; }
    bool style_att () const noexcept { return args_.styled_ != elem_undefined; }
    bool has_class (const ::std::string& s) const
    {   VERIFY_NOT_NULL (args_.dst_.get (), __FILE__, __LINE__);
        return args_.dst_ -> has_class (s); }
    bool has_custom_prop (const ::std::string& s) const
    {   VERIFY_NOT_NULL (args_.dst_.get (), __FILE__, __LINE__);
        return args_.dst_ -> has_custom_prop (s); }
    bool has_id (const ::std::string& s) const
    {   VERIFY_NOT_NULL (args_.dst_.get (), __FILE__, __LINE__);
        return args_.dst_ -> has_id (s); }
    bool has_element_class (const ::std::string& s) const
    {   VERIFY_NOT_NULL (args_.dst_.get (), __FILE__, __LINE__);
        return args_.dst_ -> has_element_class (s); }
    bool has_element_id (const ::std::string& s) const
    {   VERIFY_NOT_NULL (args_.dst_.get (), __FILE__, __LINE__);
        return args_.dst_ -> has_element_id (s); }
    bool has_namespace (const ::std::string& ) const
    {   return false; }
    bool has_custom_media (const ::std::string& name) const
    {   VERIFY_NOT_NULL (args_.dst_.get (), __FILE__, __LINE__);
        return args_.dst_ -> has_custom_media (name); }
    void note_custom_media (const ::std::string& name, const ::std::string& def)
    {   VERIFY_NOT_NULL (args_.dst_.get (), __FILE__, __LINE__);
        args_.dst_ -> note_custom_media (name, def); }
    void note_str (const e_gsstr g, const ::std::string& s)
    {   VERIFY_NOT_NULL (args_.dst_.get (), __FILE__, __LINE__);
        args_.dst_ -> note_str (g, s); }
    bool has_str (const e_gsstr g, const ::std::string& s) const
    {   VERIFY_NOT_NULL (args_.dst_.get (), __FILE__, __LINE__);
        return args_.dst_ -> has_str (g, s); }
    const sstr_t& get_str (const e_gsstr g) const
    {   VERIFY_NOT_NULL (args_.dst_.get (), __FILE__, __LINE__);
        return args_.dst_ -> get_str (g); }
    bool parse (const ::std::string& content, const bool x, const bool mdm = false); // in css_parse.cpp
    ::std::string review (mmac_t& mac, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none, const bool unfiltered = false) const;
    void accumulate (nitpick& accumulator) const;
    void accumulate (stats_t* s);
    void validate ();
    void shadow (::std::stringstream& ss);
    const ::boost::filesystem::path disk_path () const { return dp_; }
    void nick_nits (nitpick& nits);
    const arguments& args () const { return args_; }
    arguments& args () { return args_; }
    const statements& stms () const { return st_; }
    statements& stms () { return st_; }
    const element_bitset get_elements () const { return st_.get_elements (); } };

typedef ::std::shared_ptr < css > css_ptr;
