/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#pragma once
#include "enum.h"

template < class ENUM, ENUM max_enum, ENUM undefined_enum > class stats1
{   typedef ::std::vector < unsigned > counter_t;
    counter_t count_;
public:
    stats1 ()
    {   count_.resize (static_cast <::std::size_t> (max_enum + 1), 0); }
    unsigned at (const ENUM e) const
    {   return count_.at (e); }
    void mark (const ENUM e)
    {   if (e <= max_enum) ++count_.at (e);
        else ++(count_.at (undefined_enum)); } };
