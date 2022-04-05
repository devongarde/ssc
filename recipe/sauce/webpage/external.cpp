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
    "example.edu", // technically ok, but seen in the wild
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

#define EXAMPLE_SOURCE \
    EXAMPLE_START \
    "<!-- example webmention source -->" \
    EXAMPLE_CENTRE \
    "<H1>Example Source</H1>" \
    "<a href=\"https://example.net/subdirectory/target.html\">This is a grate post</a>" \
    EXAMPLE_FINISH

#define EXAMPLE_TARGET \
    EXAMPLE_START \
    "<!-- example webmention target -->" \
    "<link href=\"https://example.net/endpoint.html\" rel=\"webmention\" />" \
    EXAMPLE_CENTRE \
    "<H1>Example Target</H1>" \
    "<P>How to grate water...</P>" \
    EXAMPLE_FINISH

#define EXAMPLE_RELATIVE \
    EXAMPLE_START \
    "<!-- example webmention target -->" \
    "<link href=\"../endpoint.html\" rel=\"webmention\" />" \
    EXAMPLE_CENTRE \
    "<H1>Example Target</H1>" \
    "<P>How to grate water...</P>" \
    EXAMPLE_FINISH

#define EXAMPLE_ENDPOINT \
    EXAMPLE_START \
    "<!-- example webmention endpoint -->" \
    EXAMPLE_CENTRE \
    "<H1>Example Endpoint</H1>" \
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
        code = oops;
        context.external (false); }
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

void test_hypertext (nitpick& nits, const html_version& v, const url& u)
{   if (u.has_domain ())
    {   ::std::string d (u.domain ());
        PRESUME (! d.empty (), __FILE__, __LINE__);
        if (::boost::algorithm::iends_with (d, "invalid"))
        {   context.code (404); return; }
        if (is_example_domain (u))
        {   if (context.example ()) nits.pick (nit_example, es_warning, ec_link, "link to test domain ", quote (d), " (see RFC 2606)");
            context.code (200); return; }
        if (is_local_domain (u))
        {   if (context.local ()) nits.pick (nit_local, es_info, ec_link, "link to local domain ", quote (d), " (see RFC 2606 bis)");
            context.code (200); return; }
        if (one_of_domain (d, context.report ()))
            nits.pick (nit_report, es_info, ec_link, "link to ", quote (d));
        if (one_of_domain (d, context.no_ex_check ()))
            context.code (200); return; }
    ::std::string cmdline ("curl -o NUL --silent --head --write-out %{http_code} ");
    if (u.is_https () && ! context.revoke ()) cmdline += "--ssl-norevoke ";
    cmdline += u.original ();
    nits.pick (nit_debug, es_debug, ec_link, context.filename (),  " : ",  quote (cmdline), "\n");
    const int code = call_curl (nits, v, cmdline, 599, true);
    if (code)
    {   context.code (code);
        nits.pick (nit_debug, es_detail, ec_link, "got ", code, "\n"); } }

void test_connection (nitpick& nits, const html_version& v, const url& u)
{   if (u.is_usable ()) test_hypertext (nits, v, u);
    else nits.pick (nit_protocol, es_info, ec_link, context.filename (), " : unable to test ", u.original ()); }

bool external::verify (nitpick& nits, const html_version& v, const url& u)
{   if (! context.external ()) return true;
    if (u.empty ()) { context.code (400); return false; }
    auto e = url_.find (u.absolute ());
    context.repeated (e != url_.end ());
    if (context.repeated ()) context.code (e -> second);
    else
    {   test_connection (nits, v, u);
        url_.insert (value_t (u.absolute (), context.code ())); }
    if ((context.code () >= 400) && (context.code () < 500)) return false;
    if (! context.forwarded ()) return true;
    return ((context.code () != 301) && (context.code () != 308)); };   // consider checking for ids

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

bool fetch_common (nitpick& nits, const html_version& v, const url& u, const ::boost::filesystem::path& file, const char* curl)
{   if (! u.is_usable ())
    {   nits.pick (nit_cannot_open, es_error, ec_webmention, "Unable to open ", quote (u.original ()), " to find " WEBMENTION "");
        return false; }
    if (is_example_domain (u))
    {   ::std::string fn (u.filename ());
        if (fn == "source.html") { if (write_text_file (file, EXAMPLE_SOURCE)) return true; }
        if (fn == "target.html") { if (write_text_file (file, EXAMPLE_TARGET)) return true; }
        if (fn == "endpoint.html") { if (write_text_file (file, EXAMPLE_ENDPOINT)) return true; }
        if (fn == "relative.html") { if (write_text_file (file, EXAMPLE_RELATIVE)) return true; }
        if (write_text_file (file, EXAMPLE_HTML)) return true;
        nits.pick (nit_cannot_write, es_error, ec_webmention, "Unable to write example HTML to ", quote (file.string ()));
        return false; }
    ::std::string cmdline (curl);
    cmdline += file.string ();
    cmdline += " ";
    if (u.is_https () && context.revoke ()) cmdline += "--ssl-norevoke ";
    cmdline += u.absolute ();
    if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_webmention, WEBMENTION " http headers sought with ", quote (cmdline));
    const int code = call_curl (nits, v, cmdline, 599, false);
    if (context.tell (es_variable)) nits.pick (nit_debug, es_detail, ec_link, "got ", code, "\n");
    return (code < 300); }

bool fetch_http (nitpick& nits, const html_version& v, const url& u, const ::boost::filesystem::path& file)
{   return fetch_common (nits, v, u, file, "curl -I -o "); }

bool fetch (nitpick& nits, const html_version& v, const url& u, const ::boost::filesystem::path& file)
{   return fetch_common (nits, v, u, file, "curl -o "); }

bool mention (nitpick& nits, const html_version& v, const url& source, const url& target, const url& server)
{   typedef ssc_map < ::std::string, bool > validity_t;
    static validity_t validity;
    auto x = validity.find (server.absolute ());
    if ((x != validity.end ())) if (! x -> second) return false;
    ::std::string cmdline ("curl -i -d source=");
    cmdline += source.absolute (true);
    cmdline += " -d target=";
    cmdline += target.absolute ();
    cmdline += " ";
    if (server.is_https () && ! context.revoke ()) cmdline += "--ssl-norevoke ";
    cmdline += server.absolute ();
    if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_link, quote (cmdline));
    const int code = call_curl (nits, v, cmdline, 599, false);
    if (context.tell (es_variable)) nits.pick (nit_debug, es_detail, ec_link, "got ", code, "\n");
    validity.insert (validity_t::value_type (server.absolute (), code < 300));
    return (code < 300); }
