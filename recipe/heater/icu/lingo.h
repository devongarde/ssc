/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "main/include.h"

#ifndef NOICU
#include "main/context.h"
#include "icu/wrapper.h"
#include "icu/charset.h"

#define DOT_UTF8 ".UTF-8"

class lingo
{   ::std::string locale_id_, orig_;
    int32_t uloc_ = 0;
    ::std::locale locale_;
    static bool borked_;
    static vstr_t dicts_;
public:
    lingo () = default;
    explicit lingo (nitpick& nits, const ::std::string& lang);
    static void init (nitpick& nits);
    static void identify_dialects (nitpick& nits);
    static ::std::string standard_dialect (const ::std::string& l);
    bool invalid () const { return borked_ || (uloc_ == 0); }
    const ::std::string& original () const { return orig_; }
    ::std::locale& locale () { return locale_; }
    const ::std::locale& locale () const { return locale_; }
    ::std::string language () const;
    ::std::string region () const;
    ::std::string dialect () const;
    bool is_upper (const ::std::string& s) const;
    bool is_lower (const ::std::string& s) const;
    bool is_alpha (const ::std::string& s) const;
    bool is_space (const ::std::string& s) const;
    ::std::string to_upper (const ::std::string& s) const;
    ::std::string to_lower (const ::std::string& s) const;
    ::std::string to_title (const ::std::string& s) const;
    ::std::string to_fold (const ::std::string& s) const;
    bool compare (const ::std::string& lhs, const ::std::string& rhs) const;
    bool no_case_compare (const ::std::string& lhs, const ::std::string& rhs) const;
    vstr_t to_words (nitpick& nits, const ::std::string& s) const; };
#endif // NOICU
