/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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

#include "main/standard.h"
#include "main/context.h"
#include "type/type.h"
#include "element/element.h"
#include "parser/colonic.h"

bool is_in_root (nitpick& nits, const ::std::string& site_path, const char* const name)
{   const ::boost::filesystem::path sp (site_path);
    if (sp.filename ().string () != name)
        return false;
    ::boost::filesystem::path pp = sp.parent_path ();
    if (pp.empty () || (pp.string () == "/")) return true;
    nits.pick (nit_con, ed_con, "3.1. Access Method", es_error, ec_con, name, " must be in the site root, not ", pp.string ());
    return false; }

bool demangle_line (const ::std::string& c, ::std::string& cmd, ::std::string& arg, bool& valid)
{   ::std::string l (trim_the_lot_off (c));
    ::std::string::size_type pos = l.find ('#');
    cmd.clear ();
    arg.clear ();
    valid = true;
    if (pos != ::std::string::npos)
        l = trim_the_lot_off (l.substr (0, pos));
    if (l.empty ()) return false;
    if ((l.at (0) == '-') || (l.at (0) == '[')) return false;
    cmd = decolonise (l);
    arg = l;
    valid = ! cmd.empty ();
    return valid; }
