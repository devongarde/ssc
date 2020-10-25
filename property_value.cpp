/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

#include "standard.h"
#include "element.h"
#include "property_value.h"

::std::string find_date_value (const element& e) { return e.find_date_value (); }
::std::string find_text_value (const element& e) { return e.find_text_value (); }
::std::string find_url_value (const element& e) { return e.find_url_value (); }
::std::string find_html_value (const element& e) { return e.find_html_value (); }
