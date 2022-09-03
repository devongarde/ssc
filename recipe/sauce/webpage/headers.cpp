/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "webpage/headers.h"
#include "utility/common.h"
#include "utility/lexical.h"

#define LINK "Link"
#define REL  "rel"
#define P3P  "P3P"

void headers::parse (nitpick& nits, const html_version& , const ::std::string& header)
{   if (header.empty ())
    {   nits.pick (nit_header_empty, es_info, ec_link, "empty HTTP header ignored"); return; }
    vstr_t lines (split_by_newline (header));
    vstr_t status (split_by_space (GSL_AT (lines, 0)));
    if (status.size () < 2)
    {   nits.pick (nit_header_malformed, es_warning, ec_link, "malformed HTTP header has no status: ignored"); return; }
    code_ = lexical < int > :: cast (status.at (1), 300);
    if (code_ >= 300)
    {   nits.pick (nit_http_error, es_info, ec_link, "header expresses HTTP error ", code_, ": rejected"); return; }
    if (lines.size () < 2)
    {   nits.pick (nit_header_malformed, es_warning, ec_link, "malformed HTTP header too small: ignored"); return; }
    for (auto ln : lines)
    {   const ::std::size_t pos (ln.find (':'));
        if ((pos != ln.npos) && (pos > 0) && (pos < ln.length () - 1))
        {   ::std::string key (trim_the_lot_off (ln.substr (0, pos)));
            ::std::string value (trim_the_lot_off (ln.substr (pos + 1)));
            header_.insert (ustrv_t (key, value));
            if (context.tell (es_detail)) nits.pick (nit_detail, es_detail, ec_link, "Noted header line ", quote (key), ":", quote (value));
            if (key == LINK) process_rels (nits, value); } }
    if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_link, header_.size (), " lines processed in HTTP header"); }

void headers::process_rels (nitpick& nits, const ::std::string& value)
{   vstr_t links (split_by_charset (value, ";"));
    const ::std::size_t len = links.size ();
    if (len < 2) return;
    ::std::string target (trim_the_lot_off (GSL_AT (links, 0)));
    const ::std::size_t left = target.find ('<');
    const ::std::size_t right = target.find ('>');
    if (left == target.npos) return;
    if (right == target.npos) return;
    if (right <= left)
    {   if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_link, PROG " is confused by this header text: ", quote (target));
        return; }
    ::std::string arg0 (trim_the_lot_off (target.substr (left + 1, right - left - 1)));
    for (::std::size_t n = 1; n < len; ++n)
    {   ::std::string arg = trim_the_lot_off (GSL_AT (links, n));
        const ::std::size_t semi = arg.find ("=");
        if (semi == arg.npos) continue;
        ::std::string lhs = trim_the_lot_off (arg.substr (0, semi));
        if (lhs == P3P) { abusive_site_ = true; continue; }
        if (lhs != REL) continue;
        ::std::string rhs = trim_the_lot_off (arg.substr (semi+1));
        if (rhs.empty ()) continue;
        if (GSL_AT (rhs, 0) == '"')
        {   const ::std::size_t last = rhs.length () - 1;
            if (GSL_AT (rhs, last) != '"') continue;
            rhs = rhs.substr (1, last - 2); }
        nits.pick (nit_found_rel, es_info, ec_link, "found rel ", rhs, ", link ", arg0);
        links_.insert (ustrv_t (rhs, arg0)); } }

const ::std::string headers::link (const char * rel) const
{   auto i = links_.find (rel);
    if (i != links_.end ()) return i -> second;
    return ::std::string (); }

const ::std::string headers::get (const ::std::string key) const
{   auto i = header_.find (key);
    if (i != header_.end ()) return i -> second;
    return ::std::string (); }
