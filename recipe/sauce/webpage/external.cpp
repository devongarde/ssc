/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "webpage/external.h"
#include "utility/common.h"
#include "webpage/headers.h"
#include "url/url.h"
#include "url/fetch.h"
#include "utility/quote.h"
#include "utility/lexical.h"

const vstr_t rfc2606_no_no =
{   // https://datatracker.ietf.org/doc/attribute/rfc2606
    "example",
    "example.com",
    "example.net",
    "example.org",
    "test" };

const vstr_t rfc2606_no_no_no =
{   // https://datatracker.ietf.org/doc/attribute/rfc2606 misinterpreted
    "example.mil", // not actually in rfc2606, but...
    "invalid" };

const vstr_t local_domain =
{   // https://tools.ietf.org/id/draft-chapin-rfc2606bis-00.html
    "corp",
    "domain",
    "home",
    "home.arpa", // https://en.wikipedia.org/wiki/Special-Use_Domain_Name
    "host",
    "internal", // ICANN recommendation, Jan 24
    "lan",
    "local",
    "localdomain",
    "localhost", // https://datatracker.ietf.org/doc/attribute/rfc2606
    // RFC6761
    "10.in-addr.arpa",
    "21.172.in-addr.arpa",
    "26.172.in-addr.arpa",
    "16.172.in-addr.arpa",
    "22.172.in-addr.arpa",
    "27.172.in-addr.arpa",
    "17.172.in-addr.arpa",
    "30.172.in-addr.arpa",
    "28.172.in-addr.arpa",
    "18.172.in-addr.arpa",
    "23.172.in-addr.arpa",
    "29.172.in-addr.arpa",
    "19.172.in-addr.arpa",
    "24.172.in-addr.arpa",
    "31.172.in-addr.arpa",
    "20.172.in-addr.arpa",
    "25.172.in-addr.arpa",
    "168.192.in-addr.arpa",
    // extra
    "127.in-addr.arpa" };

 const vstr_t special_domain =
{   // https://en.wikipedia.org/wiki/Special-Use_Domain_Name
    "alt",
    "6tisch.arpa",
    "170.0.0.192.in-addr.arpa",
    "171.0.0.192.in-addr.arpa",
    "254.169.in-addr.arpa",
    "8.e.f.ip6.arpa",
    "9.e.f.ip6.arpa",
    "a.e.f.ip6.arpa",
    "b.e.f.ip6.arpa",
    "onion",
    // https://en.wikipedia.org/wiki/Top-level_domain#Reserved_domains
    "an",
    "cs",
    "dd",
    "yu",
    "zr",
    // https://en.wikipedia.org/wiki/Top-level_domain#Reserved_domains
    "bit",
    "bitnet",
    "csnet",
    "swift",
    "uucp",
    "oz" };

#define EXAMPLE_START \
    "<!DOCTYPE HTML>" \
    "<HTML lang=\"en-GB\">" \
    "<HEAD>"

#define EXAMPLE_CENTRE \
    "</HEAD>" \
    "<BODY>"

#define EXAMPLE_FINISH \
    "</BODY>" \
    "</HTML>"

#define EXAMPLE_HTML \
    EXAMPLE_START \
    "<!-- example domain specified -->" \
    EXAMPLE_CENTRE \
    "<H1>Example HTML</H1>" \
    EXAMPLE_FINISH

bool is_example_domain (const url& u)
{   return (one_of_domain (u.domain (), rfc2606_no_no)); }

bool is_naughty_domain (const url& u)
{   return (one_of_domain (u.domain (), rfc2606_no_no_no)); }

bool is_lan_domain (const url& u)
{   return (one_of_domain (u.domain (), local_domain)); }

bool is_special_domain (const url& u)
{   return (one_of_domain (u.domain (), special_domain)); }

int test_hypertext (nitpick& nits, const html_version& , const url& u)
{   if (! context.external ()) return 0;
    if (u.has_domain ())
    {   ::std::string d (u.domain ());
        PRESUME (! d.empty (), __FILE__, __LINE__);
        if (::boost::algorithm::iends_with (d, "invalid"))
            return 404;
        if (is_example_domain (u))
        {   if (context.example ()) nits.pick (nit_example, es_warning, ec_link, "link to test domain ", quote (d), " (see RFC 2606)");
            return 200; }
        if (is_naughty_domain (u))
        {   if (context.example ()) nits.pick (nit_example, es_warning, ec_link, "link to dubious domain ", quote (d), " (see RFC 2606)");
            return 404; }
        if (is_lan_domain (u))
        {   if (context.local ()) nits.pick (nit_local, es_info, ec_link, "link to local domain ", quote (d), " (see RFC 2606 bis and RFC 6761)");
            return 200; }
        if (is_special_domain (u))
        {   if (context.special ()) nits.pick (nit_special_domain, es_warning, ec_link, "link to special domain ", quote (d), ", which may respond unexpectedly (see e.g. wikipedia on special-use domains and on reserved top-level domains)");
            return 200; }
        if (one_of_domain (d, context.report ()))
            nits.pick (nit_report, es_info, ec_link, "link to ", quote (d));
        if (one_of_domain (d, context.no_ex_check ()))
            return 200; }
    int code = fetch_test (nits, u, u.is_https () && ! context.revoke ());
    if (! code)
    {   if (context.tell (es_debug)) nits.pick (nit_debug, es_detail, ec_link, "got ", code);
        if (code < 0) code = 0; }
    return code; }

int test_connection (nitpick& nits, const html_version& v, const url& u)
{   if (u.is_usable ()) return test_hypertext (nits, v, u);
    return 0; }

bool external::verify (nitpick& nits, const html_version& v, const url& u, int& code, bool& repeated)
{   ::std::string ua = u.absolute ();
    if (u.empty ())
    {   code = 400; return false; }
    if (! u.is_usable ())
    {   switch (u.get_protocol ())
        {   case pr_ftp :
            case pr_ftps :
                nits.pick (nit_ftp_protocol, es_info, ec_link, "unable to verify ", u.get_component (es_scheme));
                break;
            default :
                nits.pick (nit_protocol, es_info, ec_link, "unable to verify ", u.get_component (es_scheme));
                break; }
        code = 0; }
    else
    {   {   lox l (lox_external);
            auto e = url_.find (ua);
            repeated = (e != url_.cend ());
            if (repeated) code = e -> second; }
        if (! repeated)
        {   code = test_connection (nits, v, u);
            lox l (lox_external);
            url_.insert (value_t (ua, code)); } }
    if ((code >= 400) && (code < 500)) return false;
    if (! context.forwarded ()) return true;
    return ((code != 301) && (code != 308)); };

::std::string external::load (nitpick& nits, const url& u)
{   ::std::string res;
    if (u.empty ()) return res;
    if (fetch_page (nits, u, u.is_https () && ! context.revoke (), res) != 0)
        res.clear ();
    return res; }
