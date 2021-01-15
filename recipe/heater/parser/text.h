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

#pragma once
#include "main/context.h"
#include "type/type.h"

const int max_wotsit_len = 32;

void wotsit_init (nitpick& nits);
void text_check (nitpick& nits, const html_version& v, const ::std::string& text);
void examine_character_code (const html_version& v, const ::std::string& text, bool& known, bool& invalid);

::std::string interpret_character_code (const html_version& v, const ::std::string& text);
::std::string interpret_character_number (const ::std::string& text);
::std::string interpret_character_hex (const ::std::string& text);

::std::string interpret_character_code (nitpick& nits, const html_version& v, const ::std::string& text);
::std::string interpret_character_number (nitpick& nits, const ::std::string& text);
::std::string interpret_character_hex (nitpick& nits, const ::std::string& text);
