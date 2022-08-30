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
#include "main/context.h"

::std::string file_line (const char* const fn, const ::std::size_t line)
{   ::std::string msg (" in ");
    ::boost::filesystem::path p (fn);
    msg += p.filename ().string ();
    msg += " line ";
    msg += ::boost::lexical_cast < ::std::string > (line);
    msg += " (aborting)";
    return msg; }

[[noreturn]] void throw_bad_dereference (const char* const var, const char* const fn, const ::std::size_t line)
{   ::std::string msg ("null dereference of ");
    msg += var;
    msg += file_line (fn, line);
    ::std::cerr << "\n" << msg << "\n";
    throw ::std::runtime_error (msg); }

[[noreturn]] void throw_bad_presumption (const char* const x, const char* const fn, const ::std::size_t line)
{   ::boost::filesystem::path p (fn);
    ::std::string msg ("presumption " );
    msg += quote (x);
    msg += ::std::string (" failed");
    msg += file_line (fn, line);
    ::std::cerr << "\n" << msg << "\n";
    throw ::std::runtime_error (msg); }

[[noreturn]] void graceful_crash (const char* const fn, const ::std::size_t line)
{   ::std::string msg ("inconsistent internal state");
    msg += file_line (fn, line);
    ::std::cerr << "\n" << msg << "\n";
    throw ::std::runtime_error (msg); }

[[noreturn]] void graceless_crash (const char* const fn, const ::std::size_t line) noexcept
{   try
    {   ::std::string msg ("inconsistent internal state");
        msg += file_line (fn, line);
        ::std::cerr << "\n" << msg << "\n"; }
    catch (...)
    {   ::std::printf ("\ngraceless crash cannot even state origin\n"); }
    ::std::terminate (); }
