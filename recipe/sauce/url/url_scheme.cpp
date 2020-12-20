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

#include "main/standard.h"
#include "main/context.h"
#include "url/url_scheme.h"
#include "url/url_sanitise.h"
#include "utility/quote.h"
#include "utility/lexical.h"

bool equivalent_rfc3986 (const vc_t& lhs, const vc_t& rhs)
{   if (lhs [es_authority] != rhs [es_authority]) return false;
    if (lhs [es_server] != rhs [es_server]) return false;
    if (lhs [es_path] != rhs [es_path])
    if (lhs [es_file] != rhs [es_file])
    {   if (lhs [es_file].empty ()) { if (rhs [es_file] != context.index ()) return false; }
        else if (rhs [es_file].empty ()) { if (lhs [es_file] != context.index ()) return false; }
        else return false; }
    return (lhs [es_fragment] == rhs [es_fragment] ); }

bool parse_rfc3986 (nitpick& nits, const html_version& , const e_protocol prot, const ::std::string& s, vc_t& component)
{   // RFC 3986
    //       URI         = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
    assert (component.size () > last_component);
    ::std::string url (s);
    ::std::string scheme, hier_part, authority, path, file, user, insecure_password, ipv6, ipv4, domain, host, port;
    bool absolute = false;

    if (url.empty ())
    {   nits.pick (nit_url_empty, es_error, ec_url, "empty URL"); return false; }

    if (url.find ('!') != ::std::string::npos)
    {   nits.pick (nit_bang_path, es_warning, ec_type, "apologies, but " PROG " does not understand bang paths"); return false; }

    ::std::string fore, queries;
    if (! separate_first (url, fore, queries, QUESTION)) fore = url;
    if (! separate_first (fore, scheme, hier_part, COLON))
    {   scheme = PR_HTTP;
        hier_part = fore;
        absolute = (hier_part [0] == '/'); }
    else
    {   if (scheme.empty ())
        {   nits.pick (nit_protocol_empty, ed_rfc_3986, "3.1. Scheme", es_error, ec_url, "protocol cannot be empty"); return false; }
        ::std::string::size_type pos = scheme.find_first_not_of (ALPHABET DENARY "+-");
        if (pos != ::std::string::npos)
        {   nits.pick (nit_bad_char, ed_rfc_3986, "2. Characters", es_error, ec_url, "illegal character ('", scheme.at (pos), "') in protocol"); return false; }
        if (scheme.substr (0, 1).find_first_not_of (ALPHABET) != ::std::string::npos)
        {   nits.pick (nit_bad_char, ed_rfc_3986, "3.1. Scheme", es_error, ec_url, "first character of protocol  ('", scheme.at (0), "') must be a letter"); return false; }
        if (prot == pr_other)
        {   nits.pick (nit_unknown_protocol, es_warning, ec_url, PROG " doesn't know about the ", quote (scheme), " protocol"); return false; } }

    if (hier_part.empty () && queries.empty ())
    {   nits.pick (nit_not_just_protocol, ed_rfc_3986, "3. Syntax Components", es_error, ec_url, "a URL needs more than just a protocol"); return false; }

    ::std::string fragments = remove_tail (hier_part, HASH);

    if ((hier_part.length () > 1) && (hier_part [0] == SLASH) && (hier_part [1] == SLASH))
    {   authority = trim_the_lot_off (hier_part.substr (2));
        absolute = true;
        path = remove_tail (authority, SLASH); }
    else
        path = hier_part;

    bool authority_empty = authority.empty ();
    if (! authority_empty)
    {   if (remove_head (authority, user, AT))
        {   if (remove_tail (user, insecure_password, COLON))
            {   if (insecure_password.empty ()) nits.pick (nit_url_empty_password, es_info, ec_url, "the URL password is empty");
                else nits.pick (nit_url_insecure_password, ed_rfc_3986, "3.2. Authority", es_warning, ec_url, "passwords in URLs are deprecated, prefer an alternative authentication mechanism"); }
            if (user.empty ())
            {   nits.pick (nit_url_missing_username, ed_rfc_3986, "3.2. Authority", es_warning, ec_url, "URL username missing"); return false; } }
        if (authority [0] == SQOPEN)
        {   authority = authority.substr (1);
            if (! separate_first (authority, host, port, SQCLOSE))
            {   nits.pick (nit_malformed_ipv6, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "malformed ip6 address (no ']' found)"); return false; }
            if (! port.empty ())
            {   if (port [0] != COLON)
                {   nits.pick (nit_invalid_ipv6, ed_rfc_3986, "3.2. Authority", es_error, ec_url, "unexpected characters follow ip6 address"); return false; }
                port = port.substr (1); }
            if (host.empty ())
            {   nits.pick (nit_empty_ipv6, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "empty ipv6 address"); return false; }
            if ((host [0] != 'v') && (host [0] != 'V') && (host.find_first_not_of (HEX ":") != host.npos))
            {   nits.pick (nit_invalid_ipv6, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "invalid ipv6 address"); return false; }
            ipv6 = host; }
        else if (separate_last (authority, host, port, COLON))
            if (! port.empty ())
                if (port.find_first_not_of (DENARY) != port.npos)
                {   nits.pick (nit_bad_port, ed_rfc_3986, "3.2.3. Port", es_error, ec_url, "port must be an unsigned integer"); return false; }
                else
                {   int tst = lexical < int > :: cast (port, 65536);
                    if ((tst < 0) || (tst > 65535))
                    {   nits.pick (nit_bad_port, ed_rfc_3986, "3.2.3. Port", es_error, ec_url, "port out of range"); return false; } }

        if (ipv6.empty ())
            if (host.empty ())
            {   nits.pick (nit_empty_host, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "host cannot be empty"); return false; }
            else if ((host [0] >= '0') && (host [0] <= '9'))
            {   if (host.find_first_not_of (DENARY ".") != host.npos)
                {   nits.pick (nit_invalid_ipv4, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "illegal character in ipv4 address"); return false; }
                vstr_t octal;
                octal.resize (4);
                for (int i = 0; i < 4; ++i)
                {   ::std::string::size_type dot = host.find (DOT);
                    if ((dot == host.npos) && (i < 3))
                    {   nits.pick (nit_invalid_ipv4, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "invalid ipv4 address"); return false; }
                    octal [i] = host.substr (0, dot);
                    if (lexical < int > :: cast (octal [i], 256) > 255) // yeah, yeah, I know, but it's just a value check
                    {   nits.pick (nit_invalid_ipv4, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "all four ipv4 octals must be present and none may exceed 255"); return false; }
                    host = host.substr (dot+1); }
                if (octal [3].empty ())
                {   nits.pick (nit_invalid_ipv4, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "incomplete ipv4 address"); return false; }
                ipv4 = host; }
            else
            {   if (host.find_first_not_of (ALPHABET DDD) != host.npos)
                {   nits.pick (nit_invalid_domain, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "illegal character in domain"); return false; }
                domain = host; } }

    if (! path.empty ())
    {   ::std::string pp (path);
        path.clear ();
        bool slashed = false;
        for (auto ch : pp)  // replaces repeated slashes with singletons
        {   if (ch != SLASH) slashed = false;
            else if (slashed) continue;
            else slashed = true;
            path += ch; }
        ::std::string::size_type len = path.length ();
        if (len > 0)
            if (path [len - 1] != SLASH)
            {   ::std::string::size_type pos = path.find_last_of (SLASH);
                if (pos == ::std::string::npos)
                {   file = path;
                    path.clear (); }
                else
                {   file = path.substr (pos + 1);
                    path = path.substr (0, pos); } } }

    if (absolute)
        if (path.empty ()) path = SLASH;
        else if (path [0] != SLASH)
            path = ::std::string (1, SLASH) + path;

    component [es_scheme] = scheme;
    component [es_query] = queries;
    component [es_fragment] = fragments;
    component [es_authority] = authority;
    component [es_path] = path;
    component [es_file] = file;
    component [es_user] = user;
    component [es_password] = insecure_password;
    component [es_port] = port;

    if (! domain.empty ()) component [es_server] = domain;
    else if (! ipv4.empty ()) component [es_server] = ipv4;
    else if (! ipv6.empty ()) component [es_server] = ipv6;

    return true; }

::std::string get_rfc3986 (const vc_t& component, bool defaulted)
{   ::std::string res;
    if (! defaulted)
    {   res += component [es_scheme];
        if (! component [es_path].empty () || ! component [es_file].empty ()) res += CSS;
        else res += COLON; }
    if (! component [es_user].empty ())
    {   res += component [es_user];
        if (! component [es_password].empty ())
        {   res += COLON;
            res += component [es_password]; }
        res += AT; }
    if (! component [es_authority].empty ())
    {   res += component [es_authority];
        if (! component [es_path].empty ())
            if (component [es_path][0] != SLASH)
                res += SLASH; }
    if (! component [es_path].empty ())
    {   res += component [es_path];
        ::std::string::size_type len = component [es_path].length () - 1;
        if (component [es_path][len] != SLASH)
            res += SLASH; }
    res += component [es_file];
    if (! component [es_query].empty ())
    {   res += QUESTION;
        res += component [es_query]; }
    if (! component [es_fragment].empty ())
    {   res += HASH;
        res += component [es_fragment]; }
    return res; }

::std::string absolute_rfc3986 (const vc_t& component, bool can_use_index, bool defaulted)
{   ::std::string res;
    if (! defaulted)  // perhaps rewrite with boost path??
    {   res += component [es_scheme];
        if (! component [es_path].empty () || ! component [es_file].empty ()) res += CSS;
        else res += COLON; }
    if (! component [es_user].empty ())
    {   res += component [es_user];
        if (! component [es_password].empty ())
        {   res += COLON;
            res += component [es_password]; }
        res += AT; }
    if (! component [es_authority].empty ())
        res += component [es_authority];
    else if (context.site ().empty ()) // FFS!
        res += DEFAULT_DOMAIN;
    else res += context.site ().at (0);
    if (! component [es_path].empty ())
    {   if (component [es_path][0] != SLASH)
            res += SLASH;
        res += component [es_path];
        ::std::string::size_type len = component [es_path].length () - 1;
        if (component [es_path][len] != SLASH)
            res += SLASH;
        if (! component [es_file].empty ())
            res += component [es_file];
        else if (can_use_index)
        {   len = component [es_path].length () - 1;
            if (component [es_path][len] != SLASH)
                res += SLASH;
            res += context.index (); } }
    else if (! component [es_file].empty ())
        res += component [es_file];
    else if (can_use_index)
        res += context.index ();
    if (! component [es_query].empty ())
    {   res += QUESTION;
        res += component [es_query]; }
    if (! component [es_fragment].empty ())
    {   res += HASH;
        res += component [es_fragment]; }
    return res; }
