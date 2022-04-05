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
#include "main/context.h"
#include "url/url_scheme.h"
#include "url/url_sanitise.h"
#include "utility/quote.h"
#include "utility/lexical.h"
#include "type/type_mime.h"

bool is_authority_local (const ::std::string& authority)
{   if (authority.empty ()) return true;
    return is_one_of (authority, context.site ()); }

bool is_ipv4_local (const ::std::string& ipv4)
{   if (ipv4.empty ()) return true;
    if (ipv4.length () > 3)
    {   if (ipv4.substr (0, 3) == "10.") return true;
        if (ipv4.length () >= 4)
        {   if (ipv4.substr (0, 4) == "127.") return true;
            if (ipv4.length () == 7) return ipv4 == "0.0.0.0";
            else if (ipv4.length () > 7)
            {   if (ipv4.substr (0, 4) == "192.")
                {   if (ipv4.substr (4, 4) == "168.") return true;
                    if (ipv4.substr (4, 3) == "18.") return true;
                    if (ipv4.substr (4, 3) == "19.") return true;
                    if (ipv4.substr (4, 4) == "0.0.") return true;
                    if (ipv4.substr (4, 4) == "0.2.") return true;
                    if (ipv4.substr (4, 6) == "192.88.99.") return true;
                    return false; }
                if (ipv4.substr (0, 4) == "172.")
                {   if (ipv4.at (6) == '.')
                        switch (ipv4.at (4))
                        {   case '1' : return ipv4.at (5) >= '6';
                            case '2' : return true;
                            case '3' : return ipv4.at (5) <= '1';
                            default : break; }
                    return false; }
                if (ipv4.substr (0, 7) == "100.64.") return true;
                if (ipv4.length () > 8)
                {   if (ipv4.substr (0, 8) == "169.254.") return true;
                    if (ipv4.length () > 10)
                    {   if (ipv4.substr (0, 10) == "203.0.113.") return true;
                        if (ipv4.length () > 11)
                            if (ipv4.substr (0, 11) == "198.51.100.") return true; } } } } }
    return false; }

bool is_ipv6_local (const ::std::string& ipv6)
{   if (ipv6.empty ()) return true;
    if (ipv6.length () > 3)
        if ((ipv6.at (0) == 'f') && (ipv6.at (3) == '0'))
            if (ipv6.substr (1, 2) == "c0") return true;
            else if (ipv6.substr (1, 2) == "ec") return true;
            else if (ipv6.substr (1, 2) == "d0") return true;
            else if (ipv6.substr (1, 2) == "e8") return true;
    return (ipv6 == "::1"); }

bool is_local (const ::std::string& authority, const ::std::string& ipv4, const ::std::string& ipv6)
{   return is_authority_local (authority) && is_ipv4_local (ipv4) && is_ipv6_local (ipv6); }

bool equivalent_rfc3986 (const vc_t& lhs, const vc_t& rhs)
{   PRESUME (lhs.size () > last_component, __FILE__, __LINE__);
    PRESUME (rhs.size () > last_component, __FILE__, __LINE__);
    if (::gsl::at (lhs, es_authority) != ::gsl::at (rhs, es_authority)) return false;
    if (::gsl::at (lhs, es_server) != ::gsl::at (rhs, es_server)) return false;
    if (::gsl::at (lhs, es_path) != ::gsl::at (rhs, es_path))
    if (::gsl::at (lhs, es_file) != ::gsl::at (rhs, es_file))
    {   if (::gsl::at (lhs, es_file).empty ()) { if (::gsl::at (rhs, es_file) != context.index ()) return false; }
        else if (::gsl::at (rhs, es_file).empty ()) { if (::gsl::at (lhs, es_file) != context.index ()) return false; }
        else return false; }
    return (::gsl::at (lhs, es_fragment) == ::gsl::at (rhs, es_fragment) ); }

::std::string get_rfc3986 (const vc_t& component, bool defaulted)
{   ::std::string res;
    PRESUME (component.size () > last_component, __FILE__, __LINE__);
    if (! defaulted)
    {   res += component.at (es_scheme);
        if (! component.at (es_path).empty () || ! component.at (es_file).empty ()) res += CSS;
        else res += COLON; }
    if (! component.at (es_user).empty ())
    {   res += component.at (es_user);
        if (! component.at (es_password).empty ())
        {   res += COLON;
            res += component.at (es_password); }
        res += AT; }
    if (! component.at (es_authority).empty ())
    {   res += component.at (es_authority);
        if (! component.at (es_path).empty ())
            if (::gsl::at (component.at (es_path), 0) != SLASH)
                res += SLASH; }
    if (! component.at (es_path).empty ())
    {   res += component.at (es_path);
        const ::std::string::size_type len = component.at (es_path).length () - 1;
        if (::gsl::at (component.at (es_path), len) != SLASH)
            res += SLASH; }
    res += component.at (es_file);
    if (! component.at (es_query).empty ())
    {   res += QUESTION;
        res += component.at (es_query); }
    if (! component.at (es_fragment).empty ())
    {   res += HASH;
        res += component.at (es_fragment); }
    return res; }

::std::string absolute_rfc3986 (const vc_t& component, bool can_use_index, bool defaulted)
{   ::std::string res;
    PRESUME (component.size () > last_component, __FILE__, __LINE__);
    if (! defaulted)  // perhaps rewrite with boost path??
    {   res += component.at (es_scheme);
        if (! component.at (es_path).empty () || ! component.at (es_file).empty ()) res += CSS;
        else res += COLON; }
    if (! component.at (es_user).empty ())
    {   res += component.at (es_user);
        if (! component.at (es_password).empty ())
        {   res += COLON;
            res += component.at (es_password); }
        res += AT; }
    if (! component.at (es_authority).empty ())
        res += component.at (es_authority);
    else if (context.site ().empty ()) // FFS!
        res += DEFAULT_DOMAIN;
    else res += context.site ().at (0);
    if (! component.at (es_path).empty ())
    {   if (::gsl::at (component.at (es_path), 0) != SLASH)
            res += SLASH;
        res += component.at (es_path);
        ::std::string::size_type len = component.at (es_path).length () - 1;
        if (::gsl::at (component.at (es_path), len) != SLASH)
            res += SLASH;
        if (! component.at (es_file).empty ())
            res += component.at (es_file);
        else if (can_use_index)
        {   len = component.at (es_path).length () - 1;
            if (::gsl::at (component.at (es_path), len) != SLASH)
                res += SLASH;
            res += context.index (); } }
    else if (! component.at (es_file).empty ())
        res += component.at (es_file);
    else if (can_use_index)
        res += context.index ();
    if (! component.at (es_query).empty ())
    {   res += QUESTION;
        res += component.at (es_query); }
    if (! component.at (es_fragment).empty ())
    {   res += HASH;
        res += component.at (es_fragment); }
    return res; }

bool parse_rfc3986 (nitpick& nits, const html_version& v, const e_protocol prot, const ::std::string& s, vc_t& component)
{   // RFC 3986
    //       URI         = scheme ":" hier-part [ "?" query ] [ "#" fragment ]
    PRESUME (component.size () > last_component, __FILE__, __LINE__);
    ::std::string url (s);
    ::std::string scheme, hier_part, authority, path, file, user, insecure_password, ipv6, ipv4, domain, host, port, ext;
    bool absolute = false;

    if (url.empty ())
    {   nits.pick (nit_url_empty, es_error, ec_url, "empty URL"); return false; }

    const ::std::string::size_type bang = url.find ('!');
    if (bang != ::std::string::npos)
    {   if (url.find ('.') == ::std::string::npos)
        {   if ((bang == 0) || (bang == url.size () - 1))
                nits.pick (nit_bang_path, es_warning, ec_type, "if ", quote (url), " is a bang path, it's broken");
            else nits.pick (nit_bang_path, es_comment, ec_type, PROG " cannot verify bang paths"); }
        else if (s.find ('!') != ::std::string::npos)
            nits.pick (nit_bad_char, ed_rfc_3986, "2. Characters", es_error, ec_url, "bad bang ('!')");
        return false; }

    ::std::string fore, queries;
    if (! separate_first (url, fore, queries, QUESTION)) fore = url;
    if (! separate_first (fore, scheme, hier_part, COLON))
    {   if ((prot == pr_error) || (prot == pr_other)) scheme = PR_HTTPS;  // should it be PRESUME?
        else scheme = protocol_names.get (prot, PROTOCOL_NAME);
        hier_part = fore;
        absolute = (! hier_part.empty ()) && (hier_part.at (0) == '/'); }
    else
    {   if (scheme.empty ())
        {   nits.pick (nit_protocol_empty, ed_rfc_3986, "3.1. Scheme", es_error, ec_url, "protocol cannot be empty"); return false; }
        const ::std::string::size_type pos = scheme.find_first_not_of (ALPHABET DENARY "+-");
        if (pos != ::std::string::npos)
        {   nits.pick (nit_bad_char, ed_rfc_3986, "2. Characters", es_error, ec_url, "illegal character ('", scheme.at (pos), "') in protocol"); return false; }
        if (scheme.substr (0, 1).find_first_not_of (ALPHABET) != ::std::string::npos)
        {   nits.pick (nit_bad_char, ed_rfc_3986, "3.1. Scheme", es_error, ec_url, "first character of protocol  ('", scheme.at (0), "') must be a letter"); return false; }
        if (prot == pr_other)
        {   nits.pick (nit_unknown_protocol, es_warning, ec_url, PROG " doesn't know about the ", quote (scheme), " protocol"); return false; } }

    if (hier_part.empty () && queries.empty ())
    {   nits.pick (nit_not_just_protocol, ed_rfc_3986, "3. Syntax Components", es_error, ec_url, "a URL needs more than just a protocol"); return false; }

    ::std::string fragments = remove_tail (hier_part, HASH);

    if ((hier_part.length () > 1) && (hier_part.at (0) == SLASH) && (hier_part.at (1) == SLASH))
    {   authority = trim_the_lot_off (hier_part.substr (2));
        absolute = true;
        path = remove_tail (authority, SLASH); }
    else
        path = hier_part;

    const bool authority_empty = authority.empty ();
    if (! authority_empty)
    {   if (remove_head (authority, user, AT))
        {   if (remove_tail (user, insecure_password, COLON))
            {   if (insecure_password.empty ()) nits.pick (nit_url_empty_password, es_info, ec_url, "the URL password is empty");
                else nits.pick (nit_url_insecure_password, ed_rfc_3986, "3.2. Authority", es_warning, ec_url, "passwords in URLs are deprecated, prefer an alternative authentication mechanism"); }
            if (user.empty ())
            {   nits.pick (nit_url_missing_username, ed_rfc_3986, "3.2. Authority", es_warning, ec_url, "URL username missing"); return false; } }
        if (! authority.empty ())
            if (authority.at (0) == SQOPEN)
            {   authority = authority.substr (1);
                if (! separate_first (authority, host, port, SQCLOSE))
                {   nits.pick (nit_malformed_ipv6, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "malformed ip6 address (no ']' found)"); return false; }
                if (! port.empty ())
                {   if (port.at (0) != COLON)
                    {   nits.pick (nit_invalid_ipv6, ed_rfc_3986, "3.2. Authority", es_error, ec_url, "unexpected characters follow ip6 address"); return false; }
                    port = port.substr (1); }
                if (host.empty ())
                {   nits.pick (nit_empty_ipv6, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "empty ipv6 address"); return false; }
                if ((host.at (0) != 'v') && (host.at (0) != 'V') && (host.find_first_not_of (HEX ":") != host.npos))
                {   nits.pick (nit_invalid_ipv6, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "invalid ipv6 address"); return false; }
                ipv6 = host; }
            else if (separate_last (authority, host, port, COLON))
                if (! port.empty ())
                    if (port.find_first_not_of (DENARY) != port.npos)
                    {   nits.pick (nit_bad_port, ed_rfc_3986, "3.2.3. Port", es_error, ec_url, "port must be an unsigned integer"); return false; }
                    else
                    {   const int tst = lexical < int > :: cast (port, 65536);
                        if ((tst < 0) || (tst > 65535))
                        {   nits.pick (nit_bad_port, ed_rfc_3986, "3.2.3. Port", es_error, ec_url, "port out of range"); return false; } }

        if (ipv6.empty ())
            if (host.empty ())
            {   nits.pick (nit_empty_host, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "host cannot be empty"); return false; }
            else if ((host.at (0) >= '0') && (host.at (0) <= '9'))
            {   if (host.find_first_not_of (DENARY ".") != host.npos)
                {   nits.pick (nit_invalid_ipv4, ed_rfc_3986, "3.2.2. Host", es_warning, ec_url, "illegal character in ipv4 address"); return false; }
                vstr_t octal;
                octal.resize (4);
                for (int i = 0; i < 4; ++i)
                {   const ::std::string::size_type dot = host.find (DOT);
                    if ((dot == host.npos) && (i < 3))
                    {   nits.pick (nit_invalid_ipv4, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "invalid ipv4 address"); return false; }
                    octal.at (i) = host.substr (0, dot);
                    if (lexical < int > :: cast (octal.at (i), 256) > 255) // yeah, yeah, I know, but it's just a value check
                    {   nits.pick (nit_invalid_ipv4, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "all four ipv4 octals must be present and none may exceed 255"); return false; }
                    host = host.substr (dot+1); }
                if (octal.at (3).empty ())
                {   nits.pick (nit_invalid_ipv4, ed_rfc_3986, "3.2.2. Host", es_error, ec_url, "incomplete ipv4 address"); return false; }
                ipv4 = host; }
            else
            {   if (host.find_first_not_of (ALPHANUMERIC) != host.npos)
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
        const ::std::string::size_type len = path.length ();
        if (len > 0)
            if (path.at (len - 1) != SLASH)
            {   const ::std::string::size_type pos = path.find_last_of (SLASH);
                if (pos == ::std::string::npos)
                {   file = path;
                    path.clear (); }
                else
                {   file = path.substr (pos + 1);
                    path = path.substr (0, pos); }
                if (! file.empty ())
                {   const ::std::string::size_type dot = file.find_last_of ('.');
                    if (dot != ::std::string::npos)
                        if ((dot == 0) || (dot < file.length () - 1))
                        {   ext = ::boost::algorithm::to_lower_copy (file.substr (dot + 1));
                            check_extension_vulnerability (nits, v, ext, is_local (authority, ipv4, ipv6)); } } } }

    if (absolute)
        if (path.empty ()) path = SLASH;
        else if (path.at (0) != SLASH)
            path = ::std::string (1, SLASH) + path;

    component.at (es_scheme) = scheme;
    component.at (es_query) = queries;
    component.at (es_fragment) = fragments;
    component.at (es_authority) = authority;
    component.at (es_path) = path;
    component.at (es_file) = file;
    component.at (es_extension) = ext;
    component.at (es_user) = user;
    component.at (es_password) = insecure_password;
    component.at (es_port) = port;

    if (! domain.empty ()) component.at (es_server) = domain;
    else if (! ipv4.empty ()) component.at (es_server) = ipv4;
    else if (! ipv6.empty ()) component.at (es_server) = ipv6;

    return true; }
