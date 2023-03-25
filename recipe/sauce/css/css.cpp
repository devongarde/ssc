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

#include "main/standard.h"
#include "css/css.h"
#include "css/css_parse.h"
#include "utility/quote.h"
#include "utility/filesystem.h"
#include "utility/byteorder.h"
#include "main/context.h"
#include "microformat/prop.h"
#include "type/type.h"
#include "url/url.h"
#include "webpage/page.h"

// css::parse () is in css_parse.cpp

css::css (const html_version& v, const namespaces_ptr& namespaces, dst_ptr dst, page& p, const ::std::string& abs, bool state_version, bool snippet, int line, const e_element styled, const element_bitset eb)
    :   args_ (v, namespaces, p.css (), state_version, snippet, abs, dst, styled, eb), page_ (p), abs_ (abs), line_ (line)
{   if (abs.find (':') == ::std::string::npos) ndx_ = get_fileindex (abs); }

css::css (const html_version& v, const ::std::string& content, const namespaces_ptr& namespaces, dst_ptr dst, page& p, const ::std::string& abs, bool state_version, bool snippet, int line, const e_element styled, const element_bitset eb)
    :   args_ (v, namespaces, p.css (), state_version, snippet, abs, dst, styled, eb), page_ (p), abs_ (abs), line_ (line)
{   if (args_.abs_.find (':') == ::std::string::npos) ndx_ = get_fileindex (args_.abs_);
    parse (content, true); }

void css::check_for_standard_classes (const html_version& v)
{   nitpick nits;
    page_.check_for_standard_classes (nits, v);
    if (! nits.empty ()) ticks_.push_back (nits); }

::std::string css::review (mmac_t& mac, const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot, const e_nit_section& page_head, const bool unfiltered) const
{   ::std::string res;
    if (page_.dot_css () || snippet ())
        if (! reviewed_)
        {   if (! ticks_.empty ())
            {   if (ndx_ != nullfileindex)
                {   mac.emplace (nm_page_name, get_name (ndx_));
                    mac.emplace (nm_page_disk_path, get_disk_path (ndx_).string ());
                    mac.emplace (nm_page_site_path, get_site_path (ndx_)); }
                else if (! abs_.empty ())
                {   const ::std::string::size_type pos = abs_.find_last_of ("/");
                    if ((pos == ::std::string::npos) || (pos == abs_.length () - 1))
                        mac.emplace (nm_page_name, abs_);
                    else mac.emplace (nm_page_name, abs_.substr (pos));
                    mac.emplace (nm_page_disk_path, abs_);
                    mac.emplace (nm_page_site_path, abs_); }
                else
                {   mac.emplace (nm_page_name, "???.css");
                    mac.emplace (nm_page_disk_path, "???.css");
                    mac.emplace (nm_page_site_path, "???.css"); } }
            for (auto n : ticks_)
                res += n.review (mac, entry, head, foot, page_head, unfiltered);
            reviewed_ = true; }
    return res; }

void css::accumulate (nitpick& accumulator) const
{   for (auto n : ticks_)
        n.accumulate (accumulator); }

void css::accumulate (stats_t* s)
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    st_.accumulate (s); }

void css::validate ()
{   st_.validate (args_);
    for (auto t : args_.t_)
        if (! t.nits_.empty ())
            ticks_.push_back (t.nits_); }

void css::shadow (::std::stringstream& ss)
{   st_.shadow (ss, args_); }
