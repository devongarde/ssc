/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "main/context.h"
#include "url/url.h"
#include "coop/lox.h"
#include "type/type.h"

::boost::asio::io_context ioc;
::boost::asio::ip::tcp::resolver resolver (ioc);

void fetch_init ()
{ }

void fetch_done ()
{ }

static bool oh_dear (nitpick& nits, const url& u, const ::boost::beast::error_code& ec)
{   switch (ec.value ())
    {   case ::boost::beast::errc::address_in_use :
        case ::boost::beast::errc::already_connected :
        case ::boost::beast::errc::broken_pipe :
        case ::boost::beast::errc::no_buffer_space :
        case ::boost::beast::errc::no_child_process :
        case ::boost::beast::errc::no_lock_available :
        case ::boost::beast::errc::no_space_on_device :
        case ::boost::beast::errc::no_stream_resources :
        case ::boost::beast::errc::not_enough_memory :
#ifndef UNIX
        case ::boost::beast::errc::operation_would_block :
#endif // UNIX
        case ::boost::beast::errc::resource_deadlock_would_occur :
        case ::boost::beast::errc::too_many_files_open_in_system :
        case ::boost::beast::errc::too_many_files_open :
        case ::boost::beast::errc::too_many_links :
            nits.pick (nit_http_error, es_comment, ec_ip, "system overwhelmed; abandoning network activity (", ec.message (), ")");
            context.comms (false);
            break;
        case ::boost::beast::errc::connection_aborted :
        case ::boost::beast::errc::connection_reset :
        case ::boost::beast::errc::host_unreachable :
        case ::boost::beast::errc::interrupted :
        case ::boost::beast::errc::message_size :
        case ::boost::beast::errc::network_reset :
        case ::boost::beast::errc::operation_canceled :
            nits.pick (nit_http_error, es_comment, ec_ip, "wonky connectivity at ", u.original (), " (", ec.message (), ")");
            break;
        case ::boost::beast::errc::device_or_resource_busy :
        case ::boost::beast::errc::network_down :
        case ::boost::beast::errc::no_link :
        case ::boost::beast::errc::no_message :
        case ::boost::beast::errc::not_connected :
        case ::boost::beast::errc::state_not_recoverable :
            nits.pick (nit_http_error, es_comment, ec_ip, "network down; abandoning network activity (", ec.message (), ")");
            context.comms (false);
            break;
        case ::boost::beast::errc::address_family_not_supported :
        case ::boost::beast::errc::argument_out_of_domain :
        case ::boost::beast::errc::resource_unavailable_try_again :
        case ::boost::beast::errc::result_out_of_range :
        case ::boost::beast::errc::text_file_busy :
        case ::boost::beast::errc::value_too_large :
        case ::boost::beast::errc::wrong_protocol_type :
            nits.pick (nit_http_error, es_warning, ec_ip, ec.message (), " at ", u.original ());
            break;
        case ::boost::beast::errc::destination_address_required :
            nits.pick (nit_missing_code, es_catastrophic, ec_ip, "coding error (", ec.message (), ") connecting to ", u.original ());
            context.comms (false);
            break;
        case ::boost::beast::errc::address_not_available :
        case ::boost::beast::errc::argument_list_too_long :
        case ::boost::beast::errc::bad_message :
        case ::boost::beast::errc::connection_already_in_progress :
        case ::boost::beast::errc::cross_device_link :
        case ::boost::beast::errc::directory_not_empty :
        case ::boost::beast::errc::identifier_removed :
        case ::boost::beast::errc::invalid_argument :
        case ::boost::beast::errc::io_error :
        case ::boost::beast::errc::network_unreachable :
        case ::boost::beast::errc::no_message_available :
        case ::boost::beast::errc::no_such_device :
        case ::boost::beast::errc::not_supported :
        case ::boost::beast::errc::operation_in_progress :
        case ::boost::beast::errc::protocol_error :
        case ::boost::beast::errc::protocol_not_supported :
            nits.pick (nit_http_error, es_comment, ec_ip, "system misbehaving; abandoning network activity (", ec.message (), ")");
            context.comms (false);
            break;
        case ::boost::beast::errc::executable_format_error :
        case ::boost::beast::errc::file_exists :
        case ::boost::beast::errc::file_too_large :
        case ::boost::beast::errc::filename_too_long :
        case ::boost::beast::errc::function_not_supported :
        case ::boost::beast::errc::illegal_byte_sequence :
        case ::boost::beast::errc::inappropriate_io_control_operation :
        case ::boost::beast::errc::invalid_seek :
        case ::boost::beast::errc::no_protocol_option :
        case ::boost::beast::errc::no_such_process :
        case ::boost::beast::errc::not_a_directory :
        case ::boost::beast::errc::not_a_socket :
        case ::boost::beast::errc::not_a_stream :
        case ::boost::beast::errc::owner_dead :
        case ::boost::beast::errc::read_only_file_system :
        case ::boost::beast::errc::too_many_symbolic_link_levels :
        case ::boost::beast::errc::operation_not_supported :
            nits.pick (nit_http_error, es_comment, ec_ip, "unexpected error; abandoning network activity (", ec.message (), ")");
            context.comms (false);
            break;
        case ::boost::beast::errc::connection_refused :
        case ::boost::beast::errc::operation_not_permitted :
        case ::boost::beast::errc::permission_denied :
            nits.pick (nit_403, es_warning, ec_ip, ec.message (), " connecting to ", u.original ());
            break;
        case ::boost::beast::errc::no_such_file_or_directory :
        case ::boost::beast::errc::bad_address :
        case ::boost::beast::errc::is_a_directory :
            nits.pick (nit_404, es_warning, ec_ip, ec.message (), " connecting to ", u.original ());
            break;
        case ::boost::beast::errc::stream_timeout :
        case ::boost::beast::errc::timed_out :
            nits.pick (nit_408, es_info, ec_ip, ec.message (), " connecting to ", u.original ());
            break;
        default :
            nits.pick (nit_http_error, es_error, ec_ip, "exception ", ec.message (), " accessing ", u.original ());
            break; }
    return false; }

static bool process_status (nitpick& nits, const url& u, const ::boost::beast::http::status st)
{   switch (st)
    {   case ::boost::beast::http::status::moved_permanently :
        case ::boost::beast::http::status::temporary_redirect :
        case ::boost::beast::http::status::permanent_redirect :
            nits.pick (nit_308, es_warning, ec_ip, u.original (), ": forwarded");
            break;
        case ::boost::beast::http::status::forbidden :
            nits.pick (nit_403, es_warning, ec_ip, u.original (), ": forbidden");
            break;
        case ::boost::beast::http::status::not_found :
            nits.pick (nit_404, es_warning, ec_ip, u.original (), ": not found");
            break;
        case ::boost::beast::http::status::proxy_authentication_required :
            nits.pick (nit_407, es_warning, ec_ip, u.original (), ": proxy authentication required");
            break;
        case ::boost::beast::http::status::request_timeout :
            nits.pick (nit_408, es_warning, ec_ip, u.original (), ": timeout");
            break;
        case ::boost::beast::http::status::unavailable_for_legal_reasons :
            nits.pick (nit_451, es_warning, ec_ip, u.original (), ": censored");
            break;
        default :
            if (GSL_NARROW_CAST < int > (st) < 400) return true;
            nits.pick (nit_http_error, es_warning, ec_ip, u.original (), " status ", st);
            break; }
    return false; }

static bool fetch (nitpick& nits, const url& u, const ::boost::beast::http::verb& vrb, ::std::string& content)
{   bool result = false;
    PRESUME (! u.invalid (), __FILE__, __LINE__);
    PRESUME (! u.domain ().empty (), __FILE__, __LINE__);
    ::boost::beast::tcp_stream streamer (ioc);
    ::boost::beast::error_code ec;
    if (context.comms () && u.is_usable ()) try
    {   const ::std::string ds (u.domain ());
        const ::std::string_view dom (ds);
        ::std::string sch (u.scheme ());
        if (sch.empty ()) sch = PR_HTTPS;
        auto const lookup = resolver.resolve (dom, sch, ec);
        if (ec) oh_dear (nits, u, ec);
        else 
        {   streamer.connect (lookup);
            try
            {   ::boost::beast::http::request <::boost::beast::http::string_body> request { vrb, u.get_filepath (), 11 };
#ifdef SULKINGSTRINGVIEW
                request.set (::boost::beast::http::field::host, dom.data ());
#else // SULKINGSTRINGVIEW
                request.set (::boost::beast::http::field::host, dom);
#endif // SULKINGSTRINGVIEW
                request.set (::boost::beast::http::field::user_agent, SSC_USER_AGENT);
                ::boost::beast::http::write (streamer, request, ec);
                if (ec) oh_dear (nits, u, ec);
                else
                {   ::boost::beast::flat_buffer buffer;
                    if (vrb == ::boost::beast::http::verb::head)
                    {   ::boost::beast::http::response_parser < ::boost::beast::http::empty_body > res;
                        if (ec) oh_dear (nits, u, ec);
                        else result = process_status (nits, u, res.get ().result ()); }
                    else
                    {   ::boost::beast::http::response < ::boost::beast::http::dynamic_body > res;
                        const std::size_t sz = ::boost::beast::http::read (streamer, buffer, res, ec);
                        if (ec) oh_dear (nits, u, ec);
                        else if (! process_status (nits, u, res.base ().result ())) result = false;
                        else if (sz == 0) nits.pick (nit_empty, es_info, ec_ip, u.original (), " is empty");
                        else
                        {   ::std::stringstream ss;
                            ss << res;
                            content = ss.str ();
                            result = true; } } } }
                catch (const ::boost::beast::error_code& bec)
                {   context.comms (false);
                    result = oh_dear (nits, u, bec); }
                catch (const ::std::exception& e)
                {   context.comms (false);
                    nits.pick (nit_http_error, es_error, ec_ip, "exception: ", e.what (), " (", u.original (), ")");
                    result = false; }
                catch (...)
                {   context.comms (false);
                    nits.pick (nit_http_error, es_error, ec_ip, "unknown exception accessing ", u.original ());
                    result = false; }
            streamer.socket ().shutdown (::boost::asio::ip::tcp::socket::shutdown_both, ec);
            if (ec && (ec != ::boost::beast::errc::not_connected)) result = oh_dear (nits, u, ec); } }
    catch (const ::boost::beast::error_code& bec)
    {   context.comms (false);
        result = oh_dear (nits, u, bec); }
    catch (const ::std::exception& e)
    {   context.comms (false);
        nits.pick (nit_http_error, es_error, ec_ip, "exception: ", e.what (), " (", u.original (), ")");
        result = false; }
    catch (...)
    {   context.comms (false);
        nits.pick (nit_http_error, es_error, ec_ip, "unknown exception accessing ", u.original ());
        result = false; }
    return result; }

bool fetch_page (nitpick& nits, const url& u, bool , ::std::string& content)
{   return fetch (nits, u, ::boost::beast::http::verb::get, content); } 

bool fetch_test (nitpick& nits, const url& u, bool b)
{   ::std::string s;
    return fetch_page (nits, u, b, s); } 
