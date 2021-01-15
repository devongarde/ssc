/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

class context;

class options
{   bool valid_ = false, stop_ = false;
	::boost::program_options::variables_map var_;
    void title (const char* addendum = nullptr) const;
    void help (const ::boost::program_options::options_description& aid) const;
	void process (int argc, char** argv);
public:
	options (int argc, char** argv) : valid_ (false), stop_ (true) { process (argc, argv); }
 	bool invalid () const { return ! valid_; }
    bool stop () const { return stop_; }
    void contextualise ();
    ::std::string report () const; };
