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

#pragma once

#ifdef BEASTIES
#define DEFAULT_PORT 80
typedef ::std::vector < ::boost::asio::ip::address > vadr_t;

class server_t
{   friend class context_t;
     unsigned short port_ = DEFAULT_PORT;
    ::boost::filesystem::path root_, passfile_;
    ::boost::asio::ip::address address_;
    vadr_t from_, to_;
    ::std::string parameters_, private_, public_, password_;

    bool address (nitpick& nits, const ::std::string& s);
    bool accept (nitpick& nits, const ::std::string& from, const ::std::string& to = ::std::string ());
    void passfile (nitpick& nits, const ::boost::filesystem::path& s);
    void parameters_cert (nitpick& nits, const ::std::string& s);
    void password (nitpick& nits, const ::std::string& s);
    void private_cert (nitpick& nits, const ::std::string& s);
    void public_cert (nitpick& nits, const ::std::string& s);
    void port (nitpick& nits, const int n) noexcept;
    void root (nitpick& nits, const ::boost::filesystem::path& s);
public:
    DEFAULT_CONSTRUCTORS (server_t);
    ::std::string address () const { return address_.to_string (); }
    unsigned short port () const noexcept { return port_; }
    const ::boost::filesystem::path& root () const noexcept { return root_; }
};

#endif // BEASTIES
