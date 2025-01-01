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

int cycle_start (nitpick& nits);
void init (nitpick& nits);
int ciao ();
int cycle_finish ();
#ifndef NO_FRED
void trundle ();
#endif // NO_FRED
int examine (nitpick& nits);
int cycle (nitpick& nits, const int argc, char** argv = nullptr);
int ssc_main (int argc, char** argv);
#ifdef WX
void ssc_getset ();
#else // WX
inline void ssc_getset () { }
#endif // WX
void ssc_console (const ::std::string& s);
inline void ssc_console (const ::std::string& s1, const ::std::string& s2)
{   ssc_console (s1 + s2); }
inline void ssc_console (const ::std::string& s1, const ::std::string& s2, const ::std::string& s3)
{   ssc_console (s1 + s2 + s3); }
