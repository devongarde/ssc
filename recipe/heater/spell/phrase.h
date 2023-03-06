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
#include "feedback/nitpick.h"
#include "utility/common.h"
#include "spell/spell.h"
#include "icu/lingo.h"

class phrase
{   lingo lang_;
    ::std::string text_;
public:
    void extend (const lingo& lang, const ::std::string& s)
    {   lang_ = lang;
        text_ += s; }
    void complete (nitpick& nits, const html_version& v)
    {   if (! text_.empty ())
        {   check_spelling (nits, v, lang_, text_);
            text_.clear (); } } };

