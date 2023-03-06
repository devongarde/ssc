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

#include "main/standard.h"
#include "type/type.h"
#include "css/arguments.h"
#include "css/weight.h"

void weight::parse (nitpick& nits, const arguments& a, const ::std::string& s)
{   valid_ = test_value < t_css_earnest > (nits, a.v_, s); }

::std::string weight::rpt () const
{   if (! valid_) return "";
    return "! important"; }  

void weight::shadow (::std::stringstream& ss, arguments& )
{   if (valid_) ss << " ! important";  }
