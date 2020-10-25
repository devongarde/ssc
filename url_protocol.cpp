/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

#include "standard.h"
#include "url_protocol.h"
#include "url_schemes.h"

// RFC 3986

struct symbol_entry < e_protocol > protocol_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, PR_FILE, pr_file },
    { { HTML_TAGS }, { HTML_UNDEF }, PR_FTP, pr_ftp },
    { { HTML_4_0 }, { HTML_UNDEF }, PR_FTPS, pr_ftps },
    { { HTML_5_0 }, { HTML_UNDEF }, PR_GEO, pr_geo },
    { { HTML_TAGS }, { HTML_UNDEF }, PR_HTTP, pr_http },
    { { HTML_3_0 }, { HTML_UNDEF }, PR_HTTPS, pr_https },
    { { HTML_3_0 }, { HTML_UNDEF }, PR_LDAP, pr_ldap },
    { { HTML_TAGS }, { HTML_UNDEF }, PR_MAILTO, pr_mailto },
    { { HTML_TAGS }, { HTML_4_01 }, PR_NEWS, pr_news },
    { { HTML_4_0 }, { HTML_UNDEF }, PR_SFTP, pr_sftp },
    { { HTML_4_0 }, { HTML_UNDEF }, PR_SSH, pr_ssh },
    { { HTML_TAGS }, { HTML_4_01 }, PR_TELNET, pr_telnet },
    { { HTML_2_0 }, { HTML_UNDEF }, PR_TEL, pr_tel },
    { { HTML_TAGS }, { HTML_UNDEF }, PR_URN, pr_urn } };

struct protocol_server
{   e_protocol protocol_;
    e_scheme scheme_; };

protocol_server ps [] =
{   {   pr_other,   pt_rfc3986_ignore },
    {   pr_file,    pt_local },
    {   pr_ftp,     pt_rfc3986  },
    {   pr_ftps,    pt_rfc3986  },
    {   pr_geo,     pt_geo   },
    {   pr_http,    pt_rfc3986  },
    {   pr_https,   pt_rfc3986  },
    {   pr_ldap,    pt_rfc3986_ignore  },
    {   pr_mailto,  pt_rfc3986_ignore },
    {   pr_news,    pt_news  },
    {   pr_sftp,    pt_rfc3986_ignore  },
    {   pr_ssh,     pt_rfc3986_ignore  },
    {   pr_tel,     pt_tel   },
    {   pr_telnet,  pt_rfc3986_ignore  },
    {   pr_urn,     pt_urn   } };

void protocol::init (nitpick& nits)
{   symbol::init (nits, protocol_symbol_table, sizeof (protocol_symbol_table) / sizeof (struct symbol_entry < e_protocol >)); }

e_scheme protocol::scheme () const
{   e_protocol prot = symbol < e_protocol > :: get ();
    assert (ps [prot].protocol_ == prot);
    return ps [prot].scheme_; }

bool protocol::parse (nitpick& nits, const html_version& v, const ::std::string& x, const e_protocol current)
{   ::std::string lc (::boost::algorithm::to_lower_copy (trim_the_lot_off (x)));
    if (lc.empty ()) set (v, current);
    else
    {   ::std::string::size_type colon = lc.find (COLON);
        default_ = (colon == ::std::string::npos);
        if (default_) set (v, current);
        else if (colon == 0 || colon == lc.length () - 1)
        {   nits.pick (nit_invalid_protocol, es_error, ec_url, "invalid protocol and/or missing address");
            return false; }
        else
        {   e_protocol prot;
            if (! symbol < e_protocol > :: parse (nits, v, lc.substr (0, colon), prot)) set (v, pr_other);
            else set (v, prot); }
        if (! url_schemes < SCHEMES > :: parse (nits, v, scheme (), symbol < e_protocol > :: get (), x, component_))
            return false; }
    return true; }

bool protocol::is_valid () const
{   return url_schemes < SCHEMES > :: is_valid (scheme (), component_, default_); }

::std::string protocol::get () const
{   return url_schemes < SCHEMES > :: get (scheme (), component_, default_); }

::std::string protocol::absolute (bool can_use_index) const
{   return url_schemes < SCHEMES > :: absolute (scheme (), component_, can_use_index, default_); }

bool protocol::operator == (const protocol& rhs) const
{   if (scheme () != rhs.scheme ()) return false;
    return url_schemes < SCHEMES > :: similar (scheme (), component_, rhs.component_); }
