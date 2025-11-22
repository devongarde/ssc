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
#include "url/url.h"

class ad_rec
{   ::std::string domain_, acc_, cert_;
    nitpick nits_;
    bool direct_ = true;
public:
    DEFAULT_CONSTRUCTORS (ad_rec);
    explicit ad_rec (const ::std::string& s, const unsigned line)
    {   parse (s, line); }
    nitpick& nits () { return nits_; }
    const nitpick& nits () const { return nits_; }
    bool parse (const ::std::string& s, const unsigned line); };

typedef ::std::vector < ad_rec > adrec_v;

class ads
{   adrec_v rec_;
    ustr_t vars_;
    v_np var_nits_;
    bool valid_ = false;
public:
    DEFAULT_CONSTRUCTORS (ads);
    explicit ads (::std::ostringstream& ss, mmac_t& mac, nitpick& nits, const ::std::string& site_path, const ::std::string& content)
    {   parse (ss, mac, nits, site_path, content); }
    bool parse (nitpick& nits, const ::std::string& site_path, const ::std::string& content);
    bool parse (::std::ostringstream& ss, const mmac_t& mac, nitpick& nits, const ::std::string& site_path, const ::std::string& content)
    {   const bool res = parse (nits, site_path, content);
        review (ss, mac, nits);
        return res; }
    void review (::std::ostringstream& ss, const mmac_t& mac, nitpick& nits);
    bool invalid () const { return ! valid_; }
    bool parse_variable (const ::std::string l, const ::std::string::size_type pos, const unsigned line);
    void reset ()
    {   rec_.clear ();
        vars_.clear ();
        var_nits_.clear ();
        valid_ = false; } };

bool is_domain_connected (const ::std::string& s);
