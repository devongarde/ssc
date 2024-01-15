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

#include "main/standard.h"
#include "type/type.h"
#include "css/arguments.h"
#include "css/weight.h"
#include "css/statement.h"

void weight::parse (nitpick& nits, const arguments& a, const ::std::string& s)
{   if ((a.st_ != nullptr) && (a.st_ -> get () == css_keyframes))
    {   valid_ = false;
        nits.pick (nit_css_keyframes, ed_css_animation_3, "3. Keyframes", es_error, ec_css, "@keyframes rules are not in the cascade, so can have no weight"); }
    else valid_ = test_value < t_css_earnest > (nits, a.v_, s); }

::std::string weight::rpt () const
{   if (! valid_) return "";
    return "! important"; }  

void weight::shadow (::std::stringstream& ss, arguments& )
{   if (valid_) ss << " ! important";  }
