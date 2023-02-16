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
#include "type/enum.h"
#include "element/elem.h"
#include "css/css_class.h"
#include "css/id.h"
#include "css/css_attribute.h"
#include "css/fn.h"
#include "css/weight.h"

class unset { };

class decoration
{   typedef enum { dt_unset, dt_attribute, dt_class, dt_fn, dt_id } e_dec;
    typedef ssc_variant < unset, css_attribute, css_class, css_fn, css_id > sparkle_t;
    sparkle_t sparkle_;
public:
    decoration () : sparkle_ (unset ()) { }
    DEFAULT_COPY_CONSTRUCTORS (decoration);
    decoration (arguments& args, const int from, const int to = -1)
    {   parse (args, from, to); }
    ~decoration () = default;
    void parse (arguments& args, const int from, const int to = -1);
    bool bef_aft () const;
    void validate (arguments& args);
    void accumulate (stats_t* s, const e_element e) const;
    ::std::string rpt () const; };

typedef ::std::vector < decoration > vcd_t;
