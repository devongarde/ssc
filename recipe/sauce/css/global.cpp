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
#include "css/global.h"
#include "coop/fred.h"

css_global global_css;

dst_ptr css_global::get_or_preinsert (const ::std::string& s)
{   dst_ptr cp = get (s);
    if (cp.get () == nullptr)
    {   cp = dst_ptr (new distilled (true));
        mdst_.emplace (mdst_t::value_type (s, cp)); }
    return cp; }

dst_ptr css_global::inner_get (const ::std::string& s) const
{   mdst_t::const_iterator i = mdst_.find (s);
    if (i != mdst_.cend ()) return i -> second;
    return dst_ptr (); }

void css_global::release (dst_ptr cp)
{   lox l (lox_css);
    cp -> in_progress_ = false; }

dst_ptr css_global::get (const ::std::string& s) const
{   PRESUME (fred.started (), __FILE__, __LINE__);
    while (! fred.abandoned ())
    {   {   lox l (lox_css);
            dst_ptr pt (inner_get (s));
            if (pt.get () == nullptr) return pt;
            if (! pt -> wait ()) return pt; }
        ::std::this_thread::yield (); }
    return dst_ptr (); }
