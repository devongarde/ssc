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
#include "feedback/nitpick.h"

void open_corpus (nitpick& nits, const ::boost::filesystem::path& fn);
void close_corpus (nitpick& nits);
void extend_corpus (nitpick& nits, const ::std::string& title, const ::std::string& site_path, const ::std::string& text,
    const ::std::string& author,  const ::std::string& keywords, const ::std::string& description);
bool has_corpus () noexcept;
