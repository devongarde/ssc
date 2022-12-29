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
#include "type/type.h"

class element;
::std::string find_date_value (const element& e);
::std::string find_text_value (const element& e);
::std::string find_url_value (const element& e);
::std::string find_html_value (const element& e);

template < e_type T > ::std::string find_value (const element& e)
{   return find_text_value (e); }

template < > inline ::std::string find_value < t_datetime > (const element& e)
{   return find_date_value (e); }

template < > inline ::std::string find_value < t_html > (const element& e)
{   return find_html_value (e); }

template < > inline ::std::string find_value < t_marked_up > (const element& e)
{   return find_html_value (e); }

template < > inline ::std::string find_value < t_rel > (const element& e)
{   return find_url_value (e); }

template < > inline ::std::string find_value < t_rel_a > (const element& e)
{   return find_url_value (e); }

template < > inline ::std::string find_value < t_rel_avoid > (const element& e)
{   return find_url_value (e); }

template < > inline ::std::string find_value < t_rel_illegal > (const element& e)
{   return find_url_value (e); }

template < > inline ::std::string find_value < t_rel_link > (const element& e)
{   return find_url_value (e); }

template < > inline ::std::string find_value < t_rel_obsolete > (const element& e)
{   return find_url_value (e); }

template < > inline ::std::string find_value < t_url > (const element& e)
{   return find_url_value (e); }

template < > inline ::std::string find_value < t_urls > (const element& e)
{   return find_url_value (e); }
