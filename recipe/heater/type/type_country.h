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
#include "type/type_enum.h"
#include "type/type_master.h"

template < > inline void enum_n < t_country, e_country > :: set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty () || (s.length () > 2))
    {   enum_base < e_country, t_country > :: status (s_invalid); return; }
    original_ = s;
    ::std::string c (trim_the_lot_off (s));
    if ((c.length () >= 1) && (c.length () < 3))
        if (symbol < html_version, e_country >  :: parse (nits, v, c, enum_base < e_country, t_country > :: value_))
        {   enum_base < e_country, t_country > :: status (s_good);
            return; }
    nits.pick (nit_country, es_warning, ec_type, quote (s), " is a rare or invalid country code");
    enum_base < e_country, t_country > :: status (s_invalid); };
