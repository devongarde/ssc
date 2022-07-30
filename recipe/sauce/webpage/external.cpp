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
#include "utility/quote.h"
#include "utility/lexical.h"

#ifndef NO_BOOST_PROCESS
using namespace ::boost::process;
using ::boost::lexical_cast;
using ::boost::bad_lexical_cast;
#endif // NO_BOOST_PROCESS

// https://datatracker.ietf.org/doc/html/rfc2606
const vstr_t rfc2606_no_no =
{   "example",
    "example.com",
    "example.edu", // technically invalid, but seen in the wild
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

int process_curl_result (nitpick& nits, const html_version& v, const vstr_t& r, bool pure_code)
{   int code = 0;
    bool first = true;
    for (auto line : r)
    {   if (! line.empty () && pure_code)
            code = lexical < int > :: cast (line, 3);
        else if (first && ! line.empty ())
        {   headers h (nits, v, line);
            code = h.code ();
            first = false; }
        if (code > 0) break; }
    return code; }

#ifndef NO_BOOST_PROCESS
int call_curl (nitpick& nits, const html_version& v, const ::std::string& cmdline, const int oops, bool pure_code)
{   int code = 0;
    nits.pick (nit_launch, es_debug, ec_link, cmdline);
    try
    {   ipstream pipe_stream;
        child ext (cmdline, std_out > pipe_stream);
        if (ext.valid () && pipe_stream)
        {   ::std::string line;
            vstr_t vs;
            while (pipe_stream && ::std::getline (pipe_stream, line))
                vs.push_back (line);
            code = process_curl_result (nits, v, vs, pure_code); }
        ext.wait (); }
    catch (...)
    {   nits.pick (nit_no_curl, es_catastrophic, ec_link, "Cannot check external links. Please verify your installation of curl");
        return oops; }
    return code; }
#else // NO_BOOST_PROCESS
int call_curl (nitpick& nits, const html_version& v, const ::std::string& cmdline, const int oops, bool pure_code)
{   ::boost::filesystem::path tmp = get_tmp_filename ();
    if (::boost::filesystem::exists (tmp)) ::boost::filesystem::remove (tmp);
    ::std::string cmd = cmdline + " >" + tmp.string ();
    nits.pick (nit_launch, es_debug, ec_link, cmd);
    const int res = system (cmd.c_str ()); // really must use libcurl
    if (res != 0)
    {   nits.pick (nit_no_curl, es_catastrophic, ec_link, "Cannot check external links. Please verify your installation of curl");
        return oops; }
    if (! ::boost::filesystem::exists (tmp))
    {   nits.pick (nit_no_curl, es_catastrophic, ec_link, "Cannot find curl results (cannot find ", quote (tmp.string ()), ")");
        return oops; }
    vstr_t vs;
    int code = 3;
    {   ::std::ifstream sif (tmp.string ().c_str ());
        constexpr int maxln = 512;
        char ln [maxln] = { 0 };
        while (sif.good () && ! sif.eof ())
        {   sif.getline (ln, maxln - 1);
            ln [maxln - 1] = 0;
            vs.push_back (ln); } }
    ::boost::filesystem::remove (tmp);
    if (! vs.empty ())
        code = process_curl_result (nits, v, vs, pure_code);
    return code; }
#endif // NO_BOOST_PROCESS

bool is_example_domain (const url& u)
{   return (one_of_domain (u.domain (), rfc2606_no_no)); }

bool is_local_domain (const url& u)
{   return (one_of_domain (u.domain (), rfc2606_local)); }

int test_hypertext (nitpick& nits, const html_version& v, const url& u)
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
    ::std::string cmdline ("curl -o NUL --silent --head --write-out %{http_code} ");
    if (u.is_https () && ! context.revoke ()) cmdline += "--ssl-norevoke ";
    cmdline += u.original ();
    if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_link, quote (cmdline));
    int code = call_curl (nits, v, cmdline, 599, true);
    if (code != 0)
    {   if (context.tell (es_debug)) nits.pick (nit_debug, es_detail, ec_link, "got ", code);
        if (code < 0) code = 0; }
    return code; }

int test_connection (nitpick& nits, const html_version& v, const url& u)
{   if (u.is_usable ()) return test_hypertext (nits, v, u);
    nits.pick (nit_protocol, es_info, ec_link, "unable to check ", u.get_component (es_scheme));
    return 0; }

bool external::verify (nitpick& nits, const html_version& v, const url& u, int& code, bool& repeated)
{   ::std::string ua = u.absolute ();
    if (u.empty ()) { code = 400; return false; }
    {   lox l (lox_external);
        auto e = url_.find (ua);
        repeated = (e != url_.cend ());
        if (repeated) code = e -> second; }
    if (! repeated)
    {   code = test_connection (nits, v, u);
        lox l (lox_external);
        url_.insert (value_t (ua, code)); }
    if ((code >= 400) && (code < 500)) return false;
    if (! context.forwarded ()) return true;
    return ((code != 301) && (code != 308)); };   // consider checking for ids

#ifdef NO_BOOST_PROCESS
::std::string external::load (const url& ) noexcept
{   return ::std::string (); }
#else // NO_BOOST_PROCESS
::std::string external::load (const url& u)
{   ::std::string res;
    if (u.empty ()) return res;
    ::std::string cmdline ("curl ");
    if (context.max_file_size () != 0)
    {   cmdline += "--max-filesize ";
        cmdline += ::boost::lexical_cast < ::std::string > (context.max_file_size ());
        cmdline += " "; }
    cmdline += u.original ();
    try
    {   ipstream pipe_stream;
        child ext (cmdline, std_out > pipe_stream);
        if (ext.valid () && pipe_stream)
        {   ::std::string line;
            while (pipe_stream && ::std::getline (pipe_stream, line))
                res += line; }
        ext.wait (); }
    catch (...)
    {  res.clear (); }
    return res; }
#endif // NO_BOOST_PROCESS
