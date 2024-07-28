/*
ssc (static site checker)
File Info
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

#ifdef BEASTIES
#include "main/context.h"
#include "main/server.h"
#include "base/type_master.h"
#include "type/type.h"
#include "utility/filesystem.h"

void naughty (nitpick& nits, const ::std::string& s, const ::boost::system::error_code& ec)
{   ::std::string msg (quote (s));
    msg += " is a bad address: ";
    msg += ec.message ();
    nits.pick (nit_bad_address, es_error, ec_init, msg); }

void server_t::port (nitpick& nits, const int n) noexcept
{   if ((n < 0) || (n > 65535)) nits.pick (nit_bad_port, es_error, ec_init, n, " is an invalid port.");
    else port_ = GSL_NARROW_CAST < unsigned short > (n); }

void server_t::root (nitpick& nits, const ::boost::filesystem::path& s)
{   if (! ::boost::filesystem::is_directory (s))
        nits.pick (nit_no_such_folder, es_error, ec_init, quote (s.string ()), " doesn't exist, or is not a " REPERTOIRE ".");     
    else root_ = s; }

bool server_t::address (nitpick& nits, const ::std::string& s)
{   if (s == "*")
    {   if (! address_.is_unspecified ()) address_ == ::boost::asio::ip::address ();
        return true; }
    ::boost::system::error_code ec;
    address_ = ::boost::asio::ip::make_address (s, ec);
    if (! ec.failed ()) return true;
    naughty (nits, s, ec);
    return false; }

bool server_t::accept (nitpick& nits, const ::std::string& from, const ::std::string& to)
{   ::boost::asio::ip::address f, t;
    ::boost::system::error_code ec1, ec2;
    
    if (from.empty ())
    {   f = t = ::boost::asio::ip::make_address ("127.0.0.1", ec1);
        if (ec1.failed ()) { naughty (nits, "127.0.0.1", ec1); return false; } }
    else
    {   f = ::boost::asio::ip::make_address (from, ec1);
        if (ec1.failed ()) { naughty (nits, from, ec1); return false; }
        if (f.is_unspecified ())
        {   nits.pick (nit_bad_address, es_error, ec_init, quote (from), ": problematic address.");
            return false; }
        if (to.empty ()) t = f;
        else
        {   t = ::boost::asio::ip::make_address (to, ec2);
            if (ec2.failed ()) { naughty (nits, to, ec2); return false; }
            if (t.is_unspecified ()) t = f; }
        if (t.is_v4 () != f.is_v4 ())
        {   nits.pick (nit_bad_address, es_error, ec_init, quote (from), ",", quote (to), ": cannot mix IPv4 with IPv6.");
            return false; }
        if (t.is_multicast () || f.is_multicast ())
        {   nits.pick (nit_bad_address, es_error, ec_init, quote (from), ",", quote (to), ": multicast address? Really? Sorry, but no.");
            return false; }
        if (t < f) ::std::swap (t, f); }
    from_.push_back (f);
    to_.push_back (t);
    PRESUME (from_.size () == to_.size (), __FILE__, __LINE__);
    return true; }

void server_t::passfile (nitpick& nits, const ::boost::filesystem::path& s)
{   bool borked = false;
    ::std::string p = read_text_file (nits, s, borked);
    if (! borked) { passfile_ = s; password_ = p; } }

void server_t::parameters_cert (nitpick& nits, const ::std::string& s)
{   if (s.empty ()) nits.pick (nit_empty, es_error, ec_init, "certificate parameters cannot be empty");
    else parameters_ = s; }

void server_t::password (nitpick& , const ::std::string& s)
{   password_ = s; }

void server_t::private_cert (nitpick& nits, const ::std::string& s)
{   if (s.empty ()) nits.pick (nit_empty, es_error, ec_init, "a private certificate cannot be empty");
    else private_ = s; }

void server_t::public_cert (nitpick& nits, const ::std::string& s)
{   if (s.empty ()) nits.pick (nit_empty, es_error, ec_init, "a public certificate cannot be empty");
    else public_ = s; }

//
// Based on code by Vinnie Falco. See licence.txt for the boost software licence.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//
// all errors are mine
//

// Return a reasonable mime type based on the extension of a file.
::boost::beast::string_view mime_type (::boost::beast::string_view path)
{   nitpick nits;
    const html_version& v (context.html_ver ());
    using ::boost::beast::iequals;
    auto const ext = [&path]
    {
        auto const pos = path.rfind (".");
        if (pos == ::boost::beast::string_view::npos) return ::boost::beast::string_view {};
        if (pos >= (path.size () - 1)) return ::boost::beast::string_view {};
        return path.substr (pos+1);
    }();
    const ::std::string x (ext);
    if (! x.empty ())
    {   enum_n < t_format, e_format > fmt;
        fmt.set_value (nits, v, x);
        if (fmt.good ())
        {   e_mimetype f = static_cast < e_mimetype > (fmt.get_int ());
            enum_n < t_mime, e_mimetype > mt;
            mt.set (f);
            if (mt.good ()) mt.get_string (); } }
    return "application/text"; }

// Append an HTTP rel-path to a local filesystem path.
// The returned path is normalized for the platform.
::std::string path_cat (::boost::beast::string_view base, ::boost::beast::string_view path)
{   if (base.empty ()) return ::std::string (path);
    ::std::string result (base);
#ifdef BOOST_MSVC
    char constexpr path_separator = '\\';
    if (result.back() == path_separator) result.resize (result.size () - 1);
    result.append (path.data (), path.size ());
    for (auto& c : result)
        if (c == '/')
            c = path_separator;
#else // BOOST_MSVC
    char constexpr path_separator = '/';
    if (result.back () == path_separator)
        result.resize (result.size () - 1);
    result.append (path.data (), path.size ());
#endif // BOOST_MSVC
    return result; }

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template < class Body, class Allocator, class Send>
    void handle_request (   ::boost::beast::string_view doc_root,
                            ::boost::beast::http::request < Body, ::boost::beast::http::basic_fields < Allocator > >&& req,
                            Send&& send)
{   // Returns a bad request response
    auto const bad_request =
    [&req] (::boost::beast::string_view why)
    {   ::boost::beast::http::response < ::boost::beast::http::string_body > res { ::boost::beast::http::status::bad_request, req.version () };
        res.set ( ::boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set ( ::boost::beast::http::field::content_type, "text/html");
        res.keep_alive (req.keep_alive());
        res.body () = std::string (why);
        res.prepare_payload ();
        return res; };
    // Returns a not found response
    auto const not_found =
    [&req] (::boost::beast::string_view target)
    {   ::boost::beast::http::response < ::boost::beast::http::string_body > res { ::boost::beast::http::status::not_found, req.version () };
        res.set ( ::boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set ( ::boost::beast::http::field::content_type, "text/html");
        res.keep_alive (req.keep_alive());
        res.body () = "The resource '" + ::std::string (target) + "' was not found.";
        res.prepare_payload ();
        return res; };
    // Returns a server error response
    auto const server_error =
    [&req] ( ::boost::beast::string_view what)
    {
        ::boost::beast::http::response < ::boost::beast::http::string_body> res { ::boost::beast::http::status::internal_server_error, req.version () };
        res.set ( ::boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set ( ::boost::beast::http::field::content_type, "text/html");
        res.keep_alive (req.keep_alive());
        res.body () = "An error occurred: '" + std::string(what) + "'";
        res.prepare_payload ();
        return res; };
    // Make sure we can handle the method
    if (req.method () != ::boost::beast::http::verb::get &&
        req.method () != ::boost::beast::http::verb::head)
        return send (bad_request ("Unknown HTTP-method"));

    // Request path must be absolute and not contain "..".
    if (req.target ().empty() ||
        req.target () [0] != '/' ||
        req.target ().find ("..") != ::boost::beast::string_view::npos)
        return send (bad_request ("Illegal request-target"));

    // Build the path to the requested file
    std::string path = path_cat (doc_root, req.target ());
    if (req.target().back() == '/')
        path.append ("index.html");

    // Attempt to open the file
    ::boost::beast::error_code ec;
    ::boost::beast::http::file_body::value_type body;
    body.open (path.c_str (), ::boost::beast::file_mode::scan, ec);

    // Handle the case where the file doesn't exist
    if (ec == ::boost::beast::errc::no_such_file_or_directory)
        return send (not_found (req.target ()));

    // Handle an unknown error
    if (ec) return send (server_error (ec.message()));

    // Cache the size since we need it after the move
    auto const size = body.size();

    // Respond to HEAD request
    if (req.method () == ::boost::beast::http::verb::head)
    {   ::boost::beast::http::response < ::boost::beast::http::empty_body > res { ::boost::beast::http::status::ok, req.version () };
        res.set ( ::boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set (::boost::beast:: http::field::content_type, mime_type (path));
        res.content_length (size);
        res.keep_alive (req.keep_alive ());
        return send (std::move (res)); }

    // Respond to GET request
    ::boost::beast::http::response < ::boost::beast::http::file_body > res {
        ::std::piecewise_construct,
        ::std::make_tuple (std::move (body)),
        ::std::make_tuple (::boost::beast::http::status::ok, req.version ()) };
    res.set (::boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set (::boost::beast::http::field::content_type, mime_type (path));
    res.content_length (size);
    res.keep_alive (req.keep_alive ());
    return send (::std::move (res)); }

//------------------------------------------------------------------------------

// Report a failure
void fail (::boost::beast::error_code ec, char const* what)
{
    // ssl::error::stream_truncated, also known as an SSL "short read",
    // indicates the peer closed the connection without performing the
    // required closing handshake (for example, Google does this to
    // improve performance). Generally this can be a security issue,
    // but if your communication protocol is self-terminated (as
    // it is with both HTTP and WebSocket) then you may simply
    // ignore the lack of close_notify.
    //
    // https://github.com/boostorg/beast/issues/38
    //
    // https://security.stackexchange.com/questions/91435/how-to-handle-a-malicious-ssl-tls-shutdown
    //
    // When a short read would cut off the end of an HTTP message,
    // Beast returns the error beast::http::error::partial_message.
    // Therefore, if we see a short read here, it has occurred
    // after the message has been completed, so it is safe to ignore it.

    if (ec == ::boost::asio::ssl::error::stream_truncated) return;
    ::std::cerr << what << ": " << ec.message() << "\n"; }

//------------------------------------------------------------------------------

// Echoes back all received WebSocket messages.
// This uses the Curiously Recurring Template Pattern so that
// the same code works with both SSL streams and regular sockets.
template < class Derived > class websocket_session
{
    // Access the derived class, this is part of
    // the Curiously Recurring Template Pattern idiom.
    Derived& derived()
    { return static_cast < Derived& > (*this); }

    ::boost::beast::flat_buffer buffer_;

    // Start the asynchronous operation
    template < class Body, class Allocator >
    void do_accept (::boost::beast::http::request < Body, ::boost::beast::http::basic_fields < Allocator >> req)
    {   // Set suggested timeout settings for the websocket
        derived ().ws ().set_option (::boost::beast::websocket::stream_base::timeout::suggested (::boost::beast::role_type::server));

        // Set a decorator to change the Server of the handshake
        derived ().ws ().set_option (::boost::beast::websocket::stream_base::decorator ([] (::boost::beast::websocket::response_type& res)
            {   res.set (::boost::beast::http::field::server, ::std::string (BOOST_BEAST_VERSION_STRING) + " advanced-server-flex"); } ));

        // Accept the websocket handshake
        derived ().ws ().async_accept (req, ::boost::beast::bind_front_handler ( &websocket_session::on_accept, derived ().shared_from_this ())); }

    void on_accept (::boost::beast::error_code ec)
    {   if (ec) return fail(ec, "accept");
        // Read a message
        do_read (); }

    void do_read ()
    {   // Read a message into our buffer
        derived ().ws ().async_read (buffer_, ::boost::beast::bind_front_handler (&websocket_session::on_read, derived ().shared_from_this ()));}

    void on_read ( ::boost::beast::error_code ec, ::std::size_t bytes_transferred)
    {   ::boost::ignore_unused(bytes_transferred);

        // This indicates that the websocket_session was closed
        if (ec == ::boost::beast::websocket::error::closed) return;

        if (ec) return fail (ec, "read");

        // Echo the message
        derived ().ws ().text (derived ().ws ().got_text ());
        derived ().ws ().async_write (buffer_.data (), ::boost::beast::bind_front_handler ( &websocket_session::on_write, derived().shared_from_this ())); }

    void on_write (::boost::beast::error_code ec, ::std::size_t bytes_transferred)
    {   ::boost::ignore_unused(bytes_transferred);
        if (ec) return fail(ec, "write");
        // Clear the buffer
        buffer_.consume (buffer_.size ());
        // Do another read
        do_read(); }
public:
    // Start the asynchronous operation
    template <class Body, class Allocator >
    void run (::boost::beast::http::request <Body, ::boost::beast::http::basic_fields <Allocator>> req)
    {   // Accept the WebSocket upgrade request
        do_accept (::std::move (req)); } };

//------------------------------------------------------------------------------

// Handles a plain WebSocket connection
class plain_websocket_session : public websocket_session < plain_websocket_session >, public ::std::enable_shared_from_this < plain_websocket_session >
{   ::boost::beast::websocket::stream < ::boost::beast::tcp_stream > ws_;
public:
    // Create the session
    explicit plain_websocket_session (::boost::beast::tcp_stream&& stream) : ws_(std::move (stream)) { }
    // Called by the base class
    ::boost::beast::websocket::stream < ::boost::beast::tcp_stream >&
    ws () { return ws_; } };

//------------------------------------------------------------------------------

// Handles an SSL WebSocket connection
class ssl_websocket_session : public websocket_session < ssl_websocket_session >, public ::std::enable_shared_from_this < ssl_websocket_session >
{   ::boost::beast::websocket::stream < ::boost::beast::ssl_stream < ::boost::beast::tcp_stream > > ws_;
public:
    // Create the ssl_websocket_session
    explicit ssl_websocket_session (::boost::beast::ssl_stream < ::boost::beast::tcp_stream >&& stream) : ws_ (::std::move(stream)) { }
    // Called by the base class
    ::boost::beast::websocket::stream < ::boost::beast::ssl_stream < ::boost::beast::tcp_stream >>& ws ()
    { return ws_; } };

//------------------------------------------------------------------------------

template < class Body, class Allocator >
void make_websocket_session ( ::boost::beast::tcp_stream stream, ::boost::beast::http::request<Body, ::boost::beast::http::basic_fields < Allocator >> req)
{   ::std::make_shared < plain_websocket_session > (::std::move(stream)) -> run (::std::move (req)); }

template < class Body, class Allocator>
void make_websocket_session( ::boost::beast::ssl_stream <::boost::beast::tcp_stream > stream,::boost::beast::http::request  <Body, ::boost::beast::http::basic_fields < Allocator >> req)
{   ::std::make_shared <ssl_websocket_session > (::std::move (stream)) -> run (::std::move (req)); }

//------------------------------------------------------------------------------

// Handles an HTTP server connection.
// This uses the Curiously Recurring Template Pattern so that
// the same code works with both SSL streams and regular sockets.
template < class Derived > class http_session
{
    // Access the derived class, this is part of
    // the Curiously Recurring Template Pattern idiom.
    Derived& derived()
    { return static_cast < Derived& > (*this); }

    // This queue is used for HTTP pipelining.
    class queue
    {
        enum
        {   // Maximum number of responses we will queue
            limit = 8 };

        // The type-erased, saved work item
        struct work
        {   virtual ~work () = default;
            virtual void operator ()() = 0; };

        http_session& self_;
        ::std::vector < ::std::unique_ptr < work >> items_;

    public:
        explicit queue (http_session& self) : self_(self)
        {   static_assert (limit > 0, "queue limit must be positive");
            items_.reserve (limit); }

        // Returns `true` if we have reached the queue limit
        bool is_full () const
        {   return items_.size() >= limit; }

        // Called when a message finishes sending
        // Returns `true` if the caller should initiate a read
        bool on_write ()
        {   BOOST_ASSERT (! items_.empty ());
            auto const was_full = is_full ();
            items_.erase (items_.begin ());
            if (! items_.empty ()) (*items_.front ())();
            return was_full; }

        // Called by the HTTP handler to send a response.
        template < bool isRequest, class Body, class Fields>
            void operator () (::boost::beast::http::message < isRequest, Body, Fields > && msg)
        {   // This holds a work item
            struct work_impl : work
            {   http_session& self_;
                ::boost::beast::http::message < isRequest, Body, Fields > msg_;
                work_impl( http_session& self, ::boost::beast::http::message<isRequest, Body, Fields >&& msg)
                    : self_(self) , msg_ (::std::move (msg)) { }

                void operator ()()
                {   ::boost::beast::http::async_write (
                        self_.derived ().stream (),
                        msg_,
                        ::boost::beast::bind_front_handler (&http_session::on_write, self_.derived ().shared_from_this (), msg_.need_eof ())); } };

            // Allocate and store the work
            items_.push_back (::boost::make_unique < work_impl > (self_, ::std::move (msg)));

            // If there was no previous work, start this one
            if (items_.size() == 1) (*items_.front ()) (); } };

    ::std::shared_ptr < ::std::string const > doc_root_;
    queue queue_;

    // The parser is stored in an optional container so we can
    // construct it from scratch it at the beginning of each new message.
    ::boost::optional < ::boost::beast::http::request_parser < ::boost::beast::http::string_body >> parser_;

protected:
    ::boost::beast::flat_buffer buffer_;

public:
    // Construct the session
    http_session ( ::boost::beast::flat_buffer buffer,::std::shared_ptr < ::std::string const > const& doc_root)
        : doc_root_(doc_root), queue_(*this), buffer_ (::std::move(buffer)) { }

    void do_read ()
    {   // Construct a new parser for each message
        parser_.emplace ();

        // Apply a reasonable limit to the allowed size
        // of the body in bytes to prevent abuse.
        parser_ -> body_limit (10000);

        // Set the timeout.
        ::boost::beast::get_lowest_layer (derived ().stream ()).expires_after (::std::chrono::seconds (30));

        // Read a request using the parser-oriented interface
        ::boost::beast::http::async_read (derived ().stream (), buffer_, *parser_,
            ::boost::beast::bind_front_handler (&http_session::on_read, derived ().shared_from_this ()));}

    void on_read (::boost::beast::error_code ec, ::std::size_t bytes_transferred)
    {   ::boost::ignore_unused (bytes_transferred);

        // This means they closed the connection
        if (ec == ::boost::beast::http::error::end_of_stream) return derived ().do_eof ();

        if (ec) return fail(ec, "read");

        // See if it is a WebSocket Upgrade
        if (::boost::beast::websocket::is_upgrade (parser_->get ()))
        {   // Disable the timeout.
            // The websocket::stream uses its own timeout settings.
            ::boost::beast::get_lowest_layer (derived ().stream ()).expires_never ();

            // Create a websocket session, transferring ownership
            // of both the socket and the HTTP request.
            return make_websocket_session (derived ().release_stream (), parser_->release ()); }

        // Send the response
        handle_request (*doc_root_, parser_->release(), queue_);

        // If we aren't at the queue limit, try to pipeline another request
        if (! queue_.is_full ()) do_read(); }

    void on_write (bool close, ::boost::beast::error_code ec, ::std::size_t bytes_transferred)
    {   ::boost::ignore_unused(bytes_transferred);
        if (ec) return fail (ec, "write");
        if(close)
        {   // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            return derived ().do_eof (); }

        // Inform the queue that a write completed
        if (queue_.on_write ())
        {   // Read another request
            do_read (); } } };

//------------------------------------------------------------------------------

// Handles a plain HTTP connection
class plain_http_session : public http_session < plain_http_session >, public ::std::enable_shared_from_this < plain_http_session >
{   ::boost::beast::tcp_stream stream_;
public:
    // Create the session
    plain_http_session (::boost::beast::tcp_stream&& stream, ::boost::beast::flat_buffer&& buffer, ::std::shared_ptr < std::string const > const& doc_root)
        : http_session < plain_http_session > (::std::move(buffer), doc_root), stream_(std::move(stream)) { }
    // Start the session
    void run () { this -> do_read (); }
    // Called by the base class
    ::boost::beast::tcp_stream& stream () { return stream_; }
    // Called by the base class
    ::boost::beast::tcp_stream release_stream () { return ::std::move(stream_); }
    // Called by the base class
    void do_eof ()
    {   // Send a TCP shutdown
        ::boost::beast::error_code ec;
        // At this point the connection is closed gracefully
        stream_.socket().shutdown (::boost::asio::ip::tcp::socket::shutdown_send, ec); } };

//------------------------------------------------------------------------------

// Handles an SSL HTTP connection
class ssl_http_session : public http_session < ssl_http_session > , public ::std::enable_shared_from_this <ssl_http_session>
{   ::boost::beast::ssl_stream < ::boost::beast::tcp_stream > stream_;
public:
    // Create the http_session
    ssl_http_session (::boost::beast::tcp_stream&& stream, ::boost::asio::ssl::context& ctx, ::boost::beast::flat_buffer&& buffer, ::std::shared_ptr<std::string const> const& doc_root)
        : http_session<ssl_http_session> (::std::move(buffer), doc_root), stream_(::std::move(stream), ctx) { }
    // Start the session
    void run ( )
    {   // Set the timeout.
        ::boost::beast::get_lowest_layer (stream_).expires_after (::std::chrono::seconds (30));
        // Perform the SSL handshake
        // Note, this is the buffered version of the handshake.
        stream_.async_handshake (::boost::asio::ssl::stream_base::server, buffer_.data(), ::boost::beast::bind_front_handler (&ssl_http_session::on_handshake, shared_from_this ())); }
    // Called by the base class
    ::boost::beast::ssl_stream < ::boost::beast::tcp_stream >& stream () { return stream_; }
    // Called by the base class
    ::boost::beast::ssl_stream < ::boost::beast::tcp_stream > release_stream () { return ::std::move(stream_); }
    // Called by the base class
    void do_eof ()
    {   // Set the timeout.
        ::boost::beast::get_lowest_layer (stream_).expires_after (::std::chrono::seconds (30));
        // Perform the SSL shutdown
        stream_.async_shutdown (::boost::beast::bind_front_handler (&ssl_http_session::on_shutdown,shared_from_this ())); }
private:
    void on_handshake ( ::boost::beast::error_code ec, ::std::size_t bytes_used)
    {   if (ec)return fail (ec, "handshake");
        // Consume the portion of the buffer used by the handshake
        buffer_.consume (bytes_used);
        do_read ();}
    void on_shutdown (::boost::beast::error_code ec)
    {   // At this point the connection is closed gracefully (!)
        if (ec) return fail (ec, "shutdown"); } };

//------------------------------------------------------------------------------

// Detects SSL handshakes
class detect_session : public ::std::enable_shared_from_this < detect_session >
{   ::boost::beast::tcp_stream stream_;
    ::boost::asio::ssl::context& ctx_;
    ::std::shared_ptr<std::string const> doc_root_;
    ::boost::beast::flat_buffer buffer_;
public:
    explicit detect_session (::boost::asio::ip::tcp::socket&& socket, ::boost::asio::ssl::context& ctx, ::std::shared_ptr<std::string const> const& doc_root)
        : stream_ (::std::move (socket)) , ctx_ (ctx), doc_root_ (doc_root) { }
    // Launch the detector
    void run ()
    {   // We need to be executing within a strand to perform async operations
        // on the I/O objects in this session. Although not strictly necessary
        // for single-threaded contexts, this example code is written to be
        // thread-safe by default.
        ::boost::asio::dispatch (stream_.get_executor (),::boost::beast::bind_front_handler (&detect_session::on_run, this -> shared_from_this ())); }
    void on_run ()
    {   // Set the timeout.
        stream_.expires_after(std::chrono::seconds(30));
        ::boost::beast::async_detect_ssl (stream_, buffer_, ::boost::beast::bind_front_handler (&detect_session::on_detect,this -> shared_from_this ())); }
    void on_detect (::boost::beast::error_code ec, bool result)
    {   if (ec)return fail(ec, "detect");
        if (result)
        {   // Launch SSL session
            ::std::make_shared<ssl_http_session> (::std::move(stream_),ctx_,::std::move (buffer_),doc_root_) -> run ();
            return; }
        // Launch plain session
        ::std::make_shared<plain_http_session> (::std::move (stream_),::std::move (buffer_),doc_root_) -> run (); } };

// Accepts incoming connections and launches the sessions
class listener : public std::enable_shared_from_this < listener >
{   ::boost::asio::io_context& ioc_;
    ::boost::asio::ssl::context& ctx_;
    ::boost::asio::ip::tcp::acceptor acceptor_;
    ::std::shared_ptr < ::std::string const> doc_root_;
public:
    listener (::boost::asio::io_context& ioc, ::boost::asio::ssl::context& ctx, ::boost::asio::ip::tcp::endpoint endpoint, ::std::shared_ptr < ::std::string const > const& doc_root)
        : ioc_(ioc), ctx_(ctx), acceptor_ (::boost::asio::make_strand (ioc)), doc_root_ (doc_root)
    {   ::boost::beast::error_code ec;
        // Open the acceptor
        acceptor_.open (endpoint.protocol (), ec);
        if (ec) { fail(ec, "open"); return; }
        // Allow address reuse
        acceptor_.set_option (::boost::asio::socket_base::reuse_address (true), ec);
        if (ec) { fail(ec, "set_option"); return;}
        // Bind to the server address
        acceptor_.bind (endpoint, ec);
        if (ec) { fail(ec, "bind"); return; }
        // Start listening for connections
        acceptor_.listen (::boost::asio::socket_base::max_listen_connections, ec);
        if (ec) { fail(ec, "listen"); return; } }
    // Start accepting incoming connections
    void run () { do_accept (); }
private:
    void do_accept ()
    {   // The new connection gets its own strand
        acceptor_.async_accept (
            ::boost::asio::make_strand (ioc_), ::boost::beast::bind_front_handler ( &listener::on_accept, shared_from_this ())); }
    void on_accept (::boost::beast::error_code ec, ::boost::asio::ip::tcp::socket socket)
    {   if (ec) { fail(ec, "accept"); }
        else
        {   // Create the detector http_session and run it
            ::std::make_shared < detect_session > ( ::std::move(socket), ctx_, doc_root_) -> run(); }
        // Accept another connection
        do_accept (); } };
/*
int serve (const ::std::string& addr, const unsigned short port, const ::boost::filesystem::path& site, const int threads, const ::boost::filesystem::path& cert)
{   auto const address = ::boost::asio::ip::make_address (addr);
    auto const doc_root = ::std::make_shared <std::string> (site);
    ::boost::asio::io_context ioc { threads };
    ::boost::asio::ssl::context ctx { ::boost::asio::ssl::context::tlsv12 };

}
*/
//------------------------------------------------------------------------------
/*
int main(int argc, char* argv[])
{
    // Check command line arguments.
    if (argc != 5)
    {
        std::cerr <<
            "Usage: advanced-server-flex <address> <port> <doc_root> <threads>\n" <<
            "Example:\n" <<
            "    advanced-server-flex 0.0.0.0 8080 . 1\n";
        return EXIT_FAILURE;
    }
    auto const address = net::ip::make_address(argv[1]);
    auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
    auto const doc_root = std::make_shared<std::string>(argv[3]);
    auto const threads = std::max<int>(1, std::atoi(argv[4]));

    // The io_context is required for all I/O
    net::io_context ioc{threads};

    // The SSL context is required, and holds certificates
    ssl::context ctx{ssl::context::tlsv12};

    // This holds the self-signed certificate used by the server
    load_server_certificate(ctx);

    // Create and launch a listening port
    std::make_shared<listener>(
        ioc,
        ctx,
        tcp::endpoint{address, port},
        doc_root)->run();

    // Capture SIGINT and SIGTERM to perform a clean shutdown
    net::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait(
        [&](beast::error_code const&, int)
        {
            // Stop the `io_context`. This will cause `run()`
            // to return immediately, eventually destroying the
            // `io_context` and all of the sockets in it.
            ioc.stop();
        });

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for(auto i = threads - 1; i > 0; --i)
        v.emplace_back(
        [&ioc]
        {
            ioc.run();
        });
    ioc.run();

    // (If we get here, it means we got a SIGINT or SIGTERM)

    // Block until all the threads exit
    for(auto& t : v)
        t.join();

    return EXIT_SUCCESS;
}
*/

#if 0
/*  Load a signed certificate into the ssl context, and configure
    the context for use with a server.

    For this to work with the browser or operating system, it is
    necessary to import the "Beast Test CA" certificate into
    the local certificate store, browser, or operating system
    depending on your environment Please see the documentation
    accompanying the Beast certificate for more details.
*/
inline
void
load_server_certificate(boost::asio::ssl::context& ctx)
{
    /*
        The certificate was generated from CMD.EXE on Windows 10 using:

        winpty openssl dhparam -out dh.pem 2048
        winpty openssl req -newkey rsa:2048 -nodes -keyout key.pem -x509 -days 10000 -out cert.pem -subj "//C=US\ST=CA\L=Los Angeles\O=Beast\CN=www.example.com"
    */

    std::string const cert =
        "-----BEGIN CERTIFICATE-----\n"
        "MIIDaDCCAlCgAwIBAgIJAO8vBu8i8exWMA0GCSqGSIb3DQEBCwUAMEkxCzAJBgNV\n"
        "BAYTAlVTMQswCQYDVQQIDAJDQTEtMCsGA1UEBwwkTG9zIEFuZ2VsZXNPPUJlYXN0\n"
        "Q049d3d3LmV4YW1wbGUuY29tMB4XDTE3MDUwMzE4MzkxMloXDTQ0MDkxODE4Mzkx\n"
        "MlowSTELMAkGA1UEBhMCVVMxCzAJBgNVBAgMAkNBMS0wKwYDVQQHDCRMb3MgQW5n\n"
        "ZWxlc089QmVhc3RDTj13d3cuZXhhbXBsZS5jb20wggEiMA0GCSqGSIb3DQEBAQUA\n"
        "A4IBDwAwggEKAoIBAQDJ7BRKFO8fqmsEXw8v9YOVXyrQVsVbjSSGEs4Vzs4cJgcF\n"
        "xqGitbnLIrOgiJpRAPLy5MNcAXE1strVGfdEf7xMYSZ/4wOrxUyVw/Ltgsft8m7b\n"
        "Fu8TsCzO6XrxpnVtWk506YZ7ToTa5UjHfBi2+pWTxbpN12UhiZNUcrRsqTFW+6fO\n"
        "9d7xm5wlaZG8cMdg0cO1bhkz45JSl3wWKIES7t3EfKePZbNlQ5hPy7Pd5JTmdGBp\n"
        "yY8anC8u4LPbmgW0/U31PH0rRVfGcBbZsAoQw5Tc5dnb6N2GEIbq3ehSfdDHGnrv\n"
        "enu2tOK9Qx6GEzXh3sekZkxcgh+NlIxCNxu//Dk9AgMBAAGjUzBRMB0GA1UdDgQW\n"
        "BBTZh0N9Ne1OD7GBGJYz4PNESHuXezAfBgNVHSMEGDAWgBTZh0N9Ne1OD7GBGJYz\n"
        "4PNESHuXezAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQCmTJVT\n"
        "LH5Cru1vXtzb3N9dyolcVH82xFVwPewArchgq+CEkajOU9bnzCqvhM4CryBb4cUs\n"
        "gqXWp85hAh55uBOqXb2yyESEleMCJEiVTwm/m26FdONvEGptsiCmF5Gxi0YRtn8N\n"
        "V+KhrQaAyLrLdPYI7TrwAOisq2I1cD0mt+xgwuv/654Rl3IhOMx+fKWKJ9qLAiaE\n"
        "fQyshjlPP9mYVxWOxqctUdQ8UnsUKKGEUcVrA08i1OAnVKlPFjKBvk+r7jpsTPcr\n"
        "9pWXTO9JrYMML7d+XRSZA1n3856OqZDX4403+9FnXCvfcLZLLKTBvwwFgEFGpzjK\n"
        "UEVbkhd5qstF6qWK\n"
        "-----END CERTIFICATE-----\n";

    std::string const key =
        "-----BEGIN PRIVATE KEY-----\n"
        "MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDJ7BRKFO8fqmsE\n"
        "Xw8v9YOVXyrQVsVbjSSGEs4Vzs4cJgcFxqGitbnLIrOgiJpRAPLy5MNcAXE1strV\n"
        "GfdEf7xMYSZ/4wOrxUyVw/Ltgsft8m7bFu8TsCzO6XrxpnVtWk506YZ7ToTa5UjH\n"
        "fBi2+pWTxbpN12UhiZNUcrRsqTFW+6fO9d7xm5wlaZG8cMdg0cO1bhkz45JSl3wW\n"
        "KIES7t3EfKePZbNlQ5hPy7Pd5JTmdGBpyY8anC8u4LPbmgW0/U31PH0rRVfGcBbZ\n"
        "sAoQw5Tc5dnb6N2GEIbq3ehSfdDHGnrvenu2tOK9Qx6GEzXh3sekZkxcgh+NlIxC\n"
        "Nxu//Dk9AgMBAAECggEBAK1gV8uETg4SdfE67f9v/5uyK0DYQH1ro4C7hNiUycTB\n"
        "oiYDd6YOA4m4MiQVJuuGtRR5+IR3eI1zFRMFSJs4UqYChNwqQGys7CVsKpplQOW+\n"
        "1BCqkH2HN/Ix5662Dv3mHJemLCKUON77IJKoq0/xuZ04mc9csykox6grFWB3pjXY\n"
        "OEn9U8pt5KNldWfpfAZ7xu9WfyvthGXlhfwKEetOuHfAQv7FF6s25UIEU6Hmnwp9\n"
        "VmYp2twfMGdztz/gfFjKOGxf92RG+FMSkyAPq/vhyB7oQWxa+vdBn6BSdsfn27Qs\n"
        "bTvXrGe4FYcbuw4WkAKTljZX7TUegkXiwFoSps0jegECgYEA7o5AcRTZVUmmSs8W\n"
        "PUHn89UEuDAMFVk7grG1bg8exLQSpugCykcqXt1WNrqB7x6nB+dbVANWNhSmhgCg\n"
        "VrV941vbx8ketqZ9YInSbGPWIU/tss3r8Yx2Ct3mQpvpGC6iGHzEc/NHJP8Efvh/\n"
        "CcUWmLjLGJYYeP5oNu5cncC3fXUCgYEA2LANATm0A6sFVGe3sSLO9un1brA4zlZE\n"
        "Hjd3KOZnMPt73B426qUOcw5B2wIS8GJsUES0P94pKg83oyzmoUV9vJpJLjHA4qmL\n"
        "CDAd6CjAmE5ea4dFdZwDDS8F9FntJMdPQJA9vq+JaeS+k7ds3+7oiNe+RUIHR1Sz\n"
        "VEAKh3Xw66kCgYB7KO/2Mchesu5qku2tZJhHF4QfP5cNcos511uO3bmJ3ln+16uR\n"
        "GRqz7Vu0V6f7dvzPJM/O2QYqV5D9f9dHzN2YgvU9+QSlUeFK9PyxPv3vJt/WP1//\n"
        "zf+nbpaRbwLxnCnNsKSQJFpnrE166/pSZfFbmZQpNlyeIuJU8czZGQTifQKBgHXe\n"
        "/pQGEZhVNab+bHwdFTxXdDzr+1qyrodJYLaM7uFES9InVXQ6qSuJO+WosSi2QXlA\n"
        "hlSfwwCwGnHXAPYFWSp5Owm34tbpp0mi8wHQ+UNgjhgsE2qwnTBUvgZ3zHpPORtD\n"
        "23KZBkTmO40bIEyIJ1IZGdWO32q79nkEBTY+v/lRAoGBAI1rbouFYPBrTYQ9kcjt\n"
        "1yfu4JF5MvO9JrHQ9tOwkqDmNCWx9xWXbgydsn/eFtuUMULWsG3lNjfst/Esb8ch\n"
        "k5cZd6pdJZa4/vhEwrYYSuEjMCnRb0lUsm7TsHxQrUd6Fi/mUuFU/haC0o0chLq7\n"
        "pVOUFq5mW8p0zbtfHbjkgxyF\n"
        "-----END PRIVATE KEY-----\n";

    std::string const dh =
        "-----BEGIN DH PARAMETERS-----\n"
        "MIIBCAKCAQEArzQc5mpm0Fs8yahDeySj31JZlwEphUdZ9StM2D8+Fo7TMduGtSi+\n"
        "/HRWVwHcTFAgrxVdm+dl474mOUqqaz4MpzIb6+6OVfWHbQJmXPepZKyu4LgUPvY/\n"
        "4q3/iDMjIS0fLOu/bLuObwU5ccZmDgfhmz1GanRlTQOiYRty3FiOATWZBRh6uv4u\n"
        "tff4A9Bm3V9tLx9S6djq31w31Gl7OQhryodW28kc16t9TvO1BzcV3HjRPwpe701X\n"
        "oEEZdnZWANkkpR/m/pfgdmGPU66S2sXMHgsliViQWpDCYeehrvFRHEdR9NV+XJfC\n"
        "QMUk26jPTIVTLfXmmwU0u8vUkpR7LQKkwwIBAg==\n"
        "-----END DH PARAMETERS-----\n";
    
    ctx.set_password_callback(
        [](std::size_t,
            boost::asio::ssl::context_base::password_purpose)
        {
            return "test";
        });

    ctx.set_options(
        boost::asio::ssl::context::default_workarounds |
        boost::asio::ssl::context::no_sslv2 |
        boost::asio::ssl::context::single_dh_use);

    ctx.use_certificate_chain(
        boost::asio::buffer(cert.data(), cert.size()));

    ctx.use_private_key(
        boost::asio::buffer(key.data(), key.size()),
        boost::asio::ssl::context::file_format::pem);

    ctx.use_tmp_dh(
        boost::asio::buffer(dh.data(), dh.size()));
}
#endif

#endif // BEASTIES
