/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

#ifndef NO_PROCESS
using namespace boost::process;
using boost::lexical_cast;
using boost::bad_lexical_cast;
#endif // NO_PROCESS

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

#ifndef NO_PROCESS
int call_curl (nitpick& nits, const html_version& v, const ::std::string& cmdline, const int oops, bool pure_code)
{   int code = 0;
    try
    {   ipstream pipe_stream;
        child ext (cmdline, std_out > pipe_stream);
        if (ext.valid () && pipe_stream)
        {   ::std::string line;
//            bool first = true;
            vstr_t vs;
            while (pipe_stream && ::std::getline (pipe_stream, line))
                vs.push_back (line);
            code = process_curl_result (nits, v, vs, pure_code); }
//            {   if (! line.empty () && pure_code)
//                    code = lexical < int > :: cast (line, 3);
//                else if (first && ! line.empty ())
//                {   headers h (nits, v, line);
//                    code = h.code ();
//                    first = false; }
//                if (code > 0) break; } }
        ext.wait (); }
    catch (...)
    {   nits.pick (nit_no_curl, es_catastrophic, ec_link, "Cannot check external links. Please verify your installation of curl");
        code = oops;
        context.external (false); }
    return code; }
#else // NO_PROCESS
int call_curl (nitpick& nits, const html_version& v, const ::std::string& cmdline, const int oops, bool pure_code)
{   ::boost::filesystem::path tmp = get_tmp_filename ();
    if (::boost::filesystem::exists (tmp)) ::boost::filesystem::remove (tmp);
    ::std::string cmd = cmdline + " >" + tmp.string ();
    int res = system (cmd.c_str ());
    if (res != 0)
    {   nits.pick (nit_no_curl, es_catastrophic, ec_link, "Cannot check external links. Please verify your installation of curl");
        return oops; }
    if (! ::boost::filesystem::exists (tmp))
    {   nits.pick (nit_no_curl, es_catastrophic, ec_link, "Cannot find curl results (cannot find ", quote (tmp.string ()), ")");
        return oops; }
    vstr_t vs;
    int code = 3;
    {   ::std::ifstream sif (tmp.string ().c_str ());
        const int maxln = 512;
        char ln [maxln];
        while (sif.good () && ! sif.eof ())
        {   sif.getline (ln, maxln - 1);
            ln [maxln - 1] = 0;
            vs.push_back (ln); } }
    ::boost::filesystem::remove (tmp);
    if (! vs.empty ())
        code = process_curl_result (nits, v, vs, pure_code);
    return code; }
#endif // NO_PROCESS

void test_hypertext (nitpick& nits, const html_version& v, const url& u)
{   if (u.has_domain ())
    {   ::std::string d (u.domain ());
        PRESUME (! d.empty (), __FILE__, __LINE__);
        if (::boost::algorithm::iends_with (d, "invalid"))
        {   context.code (404); return; }
        if (ends_with_example (d))
        {   context.code (200); return; } }
    ::std::string cmdline ("curl -o NUL --silent --head --write-out %{http_code} ");
    if (u.is_https () && ! context.revoke ()) cmdline += "--ssl-norevoke ";
    cmdline += u.original ();
    nits.pick (nit_debug, es_debug, ec_link, context.filename (),  " : ",  quote (cmdline), "\n");
    int code = call_curl (nits, v, cmdline, 599, true);
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

#ifndef NO_PROCESS
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
#else // NO_PROCESS
::std::string external::load (const url& )
{   return ::std::string (); }
#endif // NO_PROCESS

bool fetch_common (nitpick& nits, const html_version& v, const url& u, const ::boost::filesystem::path& file, const char* curl)
{   if (! u.is_usable ())
    {   nits.pick (nit_cannot_open, es_error, ec_webmention, "Unable to open ", quote (u.original ()), " to find " WEBMENTION "");
        return false; }
    ::std::string cmdline (curl);
    cmdline += file.string ();
    cmdline += " ";
    if (u.is_https () && context.revoke ()) cmdline += "--ssl-norevoke ";
    cmdline += u.absolute ();
    if (context.tell (e_debug)) nits.pick (nit_debug, es_debug, ec_webmention, WEBMENTION " http headers sought with ", quote (cmdline));
    int code = call_curl (nits, v, cmdline, 599, false);
    if (context.tell (e_variable)) nits.pick (nit_debug, es_detail, ec_link, "got ", code, "\n");
    return (code < 300); }

bool fetch_http (nitpick& nits, const html_version& v, const url& u, const ::boost::filesystem::path& file)
{   return fetch_common (nits, v, u, file, "curl -I -o "); }

bool fetch (nitpick& nits, const html_version& v, const url& u, const ::boost::filesystem::path& file)
{   return fetch_common (nits, v, u, file, "curl -o "); }

bool mention (nitpick& nits, const html_version& v, const url& source, const url& target, const url& server)
{   typedef ssc_map < ::std::string, bool > validity_t;
    static validity_t validity;
    if (! context.nochange ())
    {   auto x = validity.find (server.absolute ());
        if ((x != validity.end ())) if (! x -> second) return false; }
    ::std::string cmdline ("curl -i -d source=");
    cmdline += source.absolute (true);
    cmdline += " -d target=";
    cmdline += target.absolute ();
    cmdline += " ";
    if (server.is_https () && ! context.revoke ()) cmdline += "--ssl-norevoke ";
    cmdline += server.absolute ();
    if (context.tell (e_debug)) nits.pick (nit_debug, es_debug, ec_link, quote (cmdline));
    if (context.nochange ()) return true;
    int code = call_curl (nits, v, cmdline, 599, false);
    if (context.tell (e_variable)) nits.pick (nit_debug, es_detail, ec_link, "got ", code, "\n");
    validity.insert (validity_t::value_type (server.absolute (), code < 300));
    return (code < 300); }
