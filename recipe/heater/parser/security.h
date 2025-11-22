/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "parser/colonic.h"

class sec_txt
{   typedef colonic < e_security, t_security > colic;
    colic c_;
public:
    typedef typename colic::vi_col vi_colic;
    typedef typename colic::vic_col vic_colic;
    sec_txt () = default;
    sec_txt (const sec_txt& j) = delete;
    explicit sec_txt (::std::ostringstream& ss, mmac_t& mac, nitpick& nits, const ::std::string& site_path, const ::std::string& content, const directory* const d)
    {   parse (ss, mac, nits, site_path, content, d); }
    bool parse (::std::ostringstream& ss, const mmac_t& mac, nitpick& nits, const ::std::string& site_path, const ::std::string& content, const directory* const d)
    {   const bool res = parse (nits, site_path, content, d);
        review (ss, mac, nits);
        return res; }
    bool parse (nitpick& nits, const ::std::string& site_path, const ::std::string& content, const directory* const d);
    bool invalid () const { return c_.valid_; }
    void reset ();
    void review (::std::ostringstream& ss, const mmac_t& mac, nitpick& nits);
    void swap (sec_txt& r); };
