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
#include "parser/robotic.h"
#include "main/context.h"
#include "type/type.h"
#include "element/element.h"

bool robotic::parse (nitpick& nits, const ::std::string& site_path, const ::std::string& s, const directory* const d)
{   if (! is_in_root (nits, site_path, "robots.txt")) return false;
    c_.parse (s);
    if (context.tell (es_all))
        context.os () -> out (c_.rpt ());
    bool ua = false;
    for (vi_colic i = c_.l_.begin (); i != c_.l_.end (); ++i)
    {   switch (i -> cmd_)
        {   case rob_disallow :
                if (compare_no_case (i -> arg_, "/robots.txt"))
                    i -> nits_.pick (nit_robotic, es_warning, ec_robotic, "Really?");
                FALLTHROUGH;
            case rob_allow :
                if (! ua)
                    i -> nits_.pick (nit_robotic, es_warning, ec_robotic,  "User-Agent has not been mentioned; this will be ignored");
                if (i -> arg_.empty ())
                    i -> nits_.pick (nit_empty, es_error, ec_robotic, "URL expected");
                else
                {   wacky_url wacky (i -> nits_, i -> arg_);
                    if (wacky.valid ())
                        wacky.verify (i -> nits_); }
                break;
            case rob_crawl_delay :
            {   test_value < t_unsigned > (i -> nits_, context.html_ver (), i -> arg_);
                break; }
            case rob_licence :
            case rob_sitemaps :
            {   url u (i -> nits_, context.html_ver (), i -> arg_);
                if (u.valid ())
                    u.verify (i -> nits_, context.html_ver (), d);
                break; }
            case rob_user_agent :
                ua = true;
                if (i -> arg_ != "*")
                    if (i -> arg_.find_first_not_of (ALPHABET "-_") != ::std::string::npos)
                        i -> nits_.pick (nit_robotic, ed_robotic, " 2.2.1 The User Agent Line", es_error, ec_robotic, "User agent values may only contain letters, minuses, and underlines");
                break;
            default :
                break; } }
    return true; }

void robotic::review (::std::ostringstream& ss, mmac_t& mac, nitpick& nits)
{   ss << nits.review (mac);
    for (vic_colic i = c_.l_.cbegin (); i != c_.l_.cend (); ++i)
    {   ss << i -> nits_.review (mac);
        i -> nits_.accumulate (nits); } }
