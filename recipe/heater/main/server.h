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

#pragma once

class server_t
{   friend class context_t;
    ::std::string cmd_, o_;
    bool conf_ = false;
    int print ();
    int run ();
    int help ();
public:
    DEFAULT_CONSTRUCTORS (server_t);
    static void init (nitpick& nits);
    static void reinit ();
    static void teardown ();
    int process_and_progress ();
    void clear () { o_.clear (); }
    const vstr_t cmd () const; };

extern server_t server;
