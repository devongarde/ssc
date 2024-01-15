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

class time_balloon
{   ::std::chrono::system_clock::time_point start_;
    ::std::time_t start_time_ = 0, end_time_ = 0;
    ::std::chrono::duration <double> elapsed_seconds_;
public:
    time_balloon ()
    {   start_ = ::std::chrono::system_clock::now ();
        start_time_ = ::std::chrono::system_clock::to_time_t (start_); }
    NO_COPY_CONSTRUCTORS (time_balloon);
    ~time_balloon () = default;

    void pop ()
    {   const ::std::chrono::system_clock::time_point fin = ::std::chrono::system_clock::now ();
        elapsed_seconds_ = fin - start_;
        end_time_ = std::chrono::system_clock::to_time_t (fin); }

    ::std::string inflate_time () const
    {   ::std::string t (::std::ctime (&start_time_));
        return t.substr (0, t.length () - 1); }
    ::std::string pop_time () const
    {   ::std::string t (::std::ctime (&end_time_));
        return t.substr (0, t.length () - 1); }
    ::std::string duration () const
    {   return ::boost::lexical_cast < ::std::string > (floor ((elapsed_seconds_.count () * 1000.0) + 0.5) / 1000.0); } };
