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
#include "utility/common.h"
#include "main/context.h"

class options
{   ::boost::program_options::variables_map var_, env_;
    void help (const ::boost::program_options::options_description& aid) const;
	void parse (nitpick& nits, int argc, char* const * argv);
    void yea_nay (context_t& (context_t::*fn) (const bool ), nitpick& nits, const char* yea, const char* nay);
    bool get_css_level (int& n, nitpick& nits, const char* opt, const char* name, const int maxlevel, const bool accept_1 = false);
public:
	options (nitpick& nits, int argc, char** argv)
    {   parse (nits, argc, argv); }
    void contextualise (nitpick& nits);
    ::std::string report () const; };
