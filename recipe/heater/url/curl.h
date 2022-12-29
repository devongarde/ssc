/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "main/context.h"

#ifdef NOCURL
inline void curl_init () { }
inline void curl_done () { }
inline int curl_test (nitpick& , const url& , bool ) { return 0; }
inline int curl_fetch (nitpick& , const url& , bool , ::std::string& content)
{   content.clear (); return 0; }
#else // NOCURL
void curl_init ();
void curl_done ();
int curl_test (nitpick& nits, const url& u, bool verify_ssl);
int curl_fetch (nitpick& nits, const url& u, bool verify_ssl, ::std::string& content);
#endif // NOCURL
