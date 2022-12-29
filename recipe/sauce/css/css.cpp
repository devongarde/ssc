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
#include "utility/quote.h"
#include "utility/filesystem.h"
#include "utility/byteorder.h"
#include "main/context.h"
#include "microformat/prop.h"
#include "type/type.h"
#include "url/url.h"
#include "webpage/page.h"

css::css (const html_version& v, dst_ptr dst, page* p, const ::std::string& abs, bool state_version, bool snippet, int line)
    :   snippet_ (snippet), state_version_ (state_version), page_ (p), abs_ (abs), line_ (line), dst_ (dst)
{   if (abs.find (':') == ::std::string::npos) ndx_ = get_fileindex (abs); }

css::css (arguments& args, dst_ptr dst, const ::std::string& content, int line)
    :   snippet_ (args.snippet_), state_version_ (args.sv_), page_ (args.p_), abs_ (args.abs_), line_ (line), dst_ (dst)
{   if (args.abs_.find (':') == ::std::string::npos) ndx_ = get_fileindex (args.abs_);
    parse (args, content); }

void css::swap (css& c) noexcept
{   abs_.swap (c.abs_); 
    dst_.swap (c.dst_); 
    ::std::swap (gathered_, c.gathered_);
    ::std::swap (line_, c.line_);
    ::std::swap (ndx_, c.ndx_);
    nits_.swap (c.nits_); 
    ::std::swap (page_, c.page_);
    st_.swap (c.st_);
    ::std::swap (reviewed_, c.reviewed_);
    ::std::swap (snippet_, c.snippet_);
    ::std::swap (state_version_, c.state_version_); }

bool css::parse (arguments& args, const ::std::string& content)
{   if (invalid ()) return false;
    if (content.empty ()) return true;
    if (args.abs_.empty ()) args.abs_ = abs_;
    if (args.p_ == nullptr) args.p_ = page_;
    st_.parse (args, content);
    check_for_standard_classes (args.v_);
    return true; }

void css::check_for_standard_classes (const html_version& v)
{   page_ -> check_for_standard_classes (nits_, v); }

/*
void css::tally (smsid_t& ids) const
{   if (context.classic () || ! snippet_)
        for (auto local : node_.classes ())
            if (local.second > 0)
            {   smsid_t::iterator sum = ids.find (local.first);
                if (sum == ids.end ()) ids.insert (local);
                else TALLY_TO_MAX (sum -> second, local.second, SIZE_MAX); } }
*/
::std::string css::review (mmac_t& mac, const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot, const e_nit_section& page_head, const bool unfiltered) const
{   ::std::string res;
    if (! reviewed_)
    {   if (st_.nitted ())
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
                mac.emplace (nm_page_site_path, "???.css"); }
            res = st_.review (mac, entry, head, foot, page_head, unfiltered); }
        res += nits_.review (mac, entry, head, foot, page_head, unfiltered);
        reviewed_ = true; }
    return res; }

void css::accumulate (nitpick& accumulator) const
{   if (! gathered_)
    {   st_.accumulate (accumulator);
        nits_.accumulate (accumulator); 
        gathered_ = true; } }

void css::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    st_.accumulate (s);
    if (dst_.get () != nullptr) dst_ -> accumulate (s); }

void css::merge (nitpick& nits)
{   st_.merge (nits);
    nits.merge (nits_); }
