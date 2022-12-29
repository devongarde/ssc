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
#include "utility/common.h"
#include "feedback/nitpick.h"
#include "webpage/fileindex.h"

class page;

struct ssi_compedium
{   ::std::string echomsg_, errmsg_, timefmt_, filename_;
    sndx_t dx_;
    bool sizefmt_abbrev_ = true;
    bool if_ = true, iffed_ = false;
    ustr_t var_;
    ssi_compedium ();
    void swap (ssi_compedium& ssi) noexcept; };

::std::string parse_ssi (nitpick& nits, const html_version& v, page& p, ssi_compedium& c, const ::std::string& input, ::std::time_t& updated, bool shush = false);
