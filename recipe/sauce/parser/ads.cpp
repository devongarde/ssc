/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "parser/ads.h"
#include "parser/colonic.h"

bool is_domain_connected (const ::std::string& s)
{   for (auto d : context.site ())
    {   if (d.find (s) != ::std::string::npos) return true;
        if (s.find (d) != ::std::string::npos) return true; }
    return false; }

bool ad_rec::parse (const ::std::string& l, const unsigned line)
{   if (! context.adstxt ()) return true;
    nits_.set_context (line, l);
    vstr_t args = split_by_comma (l);   
    if (args.size () < 3)
        nits_.pick (nit_con, ed_con, "3.3. The Data Record", es_error, ec_con, "expecting three or four comma separated values");
    if (args.size () > 2)
    {   const ::std::string a2 = trim_the_lot_off (args.at (2));
        if (compare_no_case (a2, "DIRECT"))
            direct_ = true;
        else if (compare_no_case (a2, "RESELLER"))
            direct_ = false;
        else
            nits_.pick (nit_con, ed_con, "3.3. The Data Record", es_error, ec_con, quote (a2), " should be DIRECT or RESELLER");
        domain_ = trim_the_lot_off (args.at (0));
        if (! is_domain_connected (domain_))
            nits_.pick (nit_con, es_warning, ec_con, "the domain ", quote (domain_), " is not a website domain");
        acc_ = trim_the_lot_off (args.at (1));
        if (args.size () > 3) cert_ = trim_the_lot_off (args.at (3)); }
    return true; }

bool ads::parse_variable (const ::std::string l, const ::std::string::size_type pos, const unsigned line)
{   nitpick nuts;
    nuts.set_context (line, l);
    bool res = true;
    if (pos == 0)
    {   nuts.pick (nit_con, ed_con, "3.5. Variable Declaration", es_error, ec_con, "variable name required");
        res = false; }
    else
    {   const ::std::string var (l.substr (0, pos));
        const ::std::string val (l.substr (pos+1));
        const e_advar v = examine_value < t_advar > (nuts, context.html_ver (), var);
        switch (v)
        {   case adv_sub :
                if (! is_domain_connected (val))
                    nuts.pick (nit_con, es_warning, ec_con, "the subdomain ", quote (val), " is not a subdomain of the website");
                res = false;
                break;
            default : break; }
        vars_.insert (::std::pair (var, val)); }
    if (! nuts.empty ())
        var_nits_.emplace_back (nuts);
    return res; }

bool ads::parse (nitpick& nits, const ::std::string& site_path, const ::std::string& content)
{   if (! is_in_root (nits, site_path, "ads.txt")) return false;
    const ::boost::filesystem::path sp (site_path);
    if (sp.filename ().string () != "ads.txt")
        return false;
    vstr_t ls (lineate (content));
    unsigned line = 0;
    bool res = true;
    for (auto l : ls)
    {   ++line;
        const ::std::string::size_type semi = l.find (';');
        if (semi != ::std::string::npos) l = l.substr (0, semi);
        if (! l.empty ())
            if (l.at (0) != '#')
            {   const ::std::string::size_type pos = l.find ('=');
                if (pos != ::std::string::npos)
                {   if (! parse_variable (l, pos, line))
                        res = false; }
                else rec_.emplace_back (l, line); } }
    return res; }

void ads::review (::std::ostringstream& ss, const mmac_t& mac, nitpick& nits)
{   ss << nits.review (mac);  
    for (adrec_v::const_iterator i = rec_.cbegin (); i != rec_.cend (); ++i)
    {   ss << i -> nits ().review (mac);
        i -> nits ().accumulate (nits); } 
    for (v_np::const_iterator i = var_nits_.cbegin (); i != var_nits_.cend (); ++i)
    {   ss << i -> review (mac);
        i -> accumulate (nits); } }
