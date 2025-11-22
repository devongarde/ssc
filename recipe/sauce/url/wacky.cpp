/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "utility/quote.h"
#include "url/wacky.h"
#include "url/url_sanitise.h"

bool wacky_url::parse (nitpick& nits, const ::std::string& site_path)
{   if (site_path.empty ())
        nits.pick (nit_empty, es_error, ec_url, "path spec cannot be empty");
    else if (site_path.find_first_of (":") != ::std::string::npos)
        nits.pick (nit_wacky, es_error, ec_url, "expecting an local URL");
    else if (site_path.at (0) == '*')
    {   layers_.push_back ("*");
        return true; }
    if (site_path.at (0) != '/')
        nits.pick (nit_wacky, es_error, ec_url, "expecting an absolute local wildcard URL");
    else
    {   layers_ = uq2 (site_path, UQ_DQ | UQ_SQ | UQ_BS, "/");
        for (auto l : layers_)
            l = decode (l);
        return true; }
    return false; }

bool wacky_url::verify (nitpick& nits)
{   ::std::string p;
    bool stop = false;
    for (auto l : layers_)
    {   if (l.empty ()) continue;
        const ::std::string::size_type splat = l.find ('*');
        if (splat == 0) return true;
        if (splat != ::std::string::npos) continue;
        const ::std::string::size_type sz = l.size ();
        if (l.at (sz - 1) == '$')
        {   l = l.substr (0, sz);
            stop = true; }
        const ::std::string::size_type pos = l.find_first_of ("?");
        if (pos != ::std::string::npos)
        {   l = l.substr (0, pos);
            stop = true; }
        if (l != "/")
        {   if (l.at (0) != '/') p += "/";
            p += l;
            if (get_fileindex (p) == nullfileindex)
            {   nits.pick (nit_wacky, es_error, ec_url, quote (p), ": not found");
                return false; } }
        if (stop) break; }
    return true; }
