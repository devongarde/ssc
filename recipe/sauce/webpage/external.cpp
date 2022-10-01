/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "url/curl.h"
#include "utility/quote.h"
#include "utility/lexical.h"

// https://datatracker.ietf.org/doc/html/rfc2606
const vstr_t rfc2606_no_no =
{   "example",
    "example.com",
    "example.edu", // technically not included, but seen in the wild
    "example.gov", // to be consistent
    "example.mil", // & to complete the set
    "example.net",
    "example.org",
    "invalid",
    "localhost",
    "test" };

// https://tools.ietf.org/id/draft-chapin-rfc2606bis-00.html
const vstr_t rfc2606_local =
{   "corp",
    "domain",
    "home",
    "host",
    "lan",
    "local",
    "localdomain" };

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

bool is_local_domain (const url& u)
{   return (one_of_domain (u.domain (), rfc2606_local)); }

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
        if (is_local_domain (u))
        {   if (context.local ()) nits.pick (nit_local, es_info, ec_link, "link to local domain ", quote (d), " (see RFC 2606 bis)");
            return 200; }
        if (one_of_domain (d, context.report ()))
            nits.pick (nit_report, es_info, ec_link, "link to ", quote (d));
        if (one_of_domain (d, context.no_ex_check ()))
            return 200; }
    int code = curl_test (nits, u, u.is_https () && ! context.revoke ());
    if (code != 0)
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
    {   nits.pick (nit_protocol, es_info, ec_link, "unable to verify ", u.get_component (es_scheme));
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
    return ((code != 301) && (code != 308)); };   // consider checking for ids

::std::string external::load (nitpick& nits, const url& u)
{   ::std::string res;
    if (u.empty ()) return res;
    if (curl_fetch (nits, u, u.is_https () && ! context.revoke (), res) != 0)
        res.clear ();
    return res; }
