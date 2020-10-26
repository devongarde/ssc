/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

#include "standard.h"
#include "microformat_constructor.h"

template < class MICROFORMAT, class... X > struct microformat_constructor : public microformat_constructor < X... >
{   static void alloc_microformat_pv (microformat_pv& mf)
    {   if (mf.index_ == static_cast < size_t > (MICROFORMAT :: whoami ())) mf.microformat_.reset (new MICROFORMAT ());
        else microformat_constructor < X... > :: alloc_microformat_pv (mf); } };

template < > struct microformat_constructor < mf_error >
{   static void alloc_microformat_pv (microformat_pv& ) { } };

microformat_pv microformat_pv::alloc_microformat_pv (const ::std::size_t v)
{   microformat_pv res;
    res.index_ = v;
    microformat_constructor < MICROFORMATS > :: alloc_microformat_pv (res);
    return res; }
