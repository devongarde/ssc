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
#include "type/type_rel.h"
#include "element/elem.h"

template < > struct type_master < t_rel_a > : type_master < t_rel >
{   using type_master < t_rel > :: type_master;
    void verify_attribute (nitpick& nits, const html_version& , const elem& e, element* , const ::std::string& situation)
    {   if ((e.get () != elem_a) && (e.get () != elem_area))
        {   if (context.mf_verify ()) nits.pick (nit_a_area, es_warning, ec_microformat, "REL should be used on <A> or <AREA> only (", situation, ")");
            type_master < t_rel > :: status (s_invalid); } } };

template < > struct type_master < t_rel_avoid > : type_master < t_rel >
{   using type_master < t_rel > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_rel > :: set_value (nits, v, s);
        if (context.mf_verify ()) nits.pick (nit_unadvised, ed_microformats, "http://microformats.org/wiki/existing-rel-values", es_warning, ec_microformat, quote (s), " is not recommended");
        type_master < t_rel > :: status (s_invalid); } };

template < > struct type_master < t_rel_illegal > : type_master < t_rel >
{   using type_master < t_rel > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_rel > :: set_value (nits, v, s);
        if (context.mf_verify ()) nits.pick (nit_rejected, ed_microformats, "http://microformats.org/wiki/existing-rel-values", es_error, ec_microformat, quote (s), " has been rejected by the standards authorities");
        type_master < t_rel > :: status (s_invalid); } };

template < > struct type_master < t_rel_link > : type_master < t_rel >
{   using type_master < t_rel > :: type_master;
    void verify_attribute (nitpick& nits, const html_version& , const elem& e, element* , const ::std::string& situation)
    {   if ((e.get () != elem_link))
        {   if (context.mf_verify ()) nits.pick (nit_a_area, es_error, ec_microformat, "REL value should be used on <LINK> only (", situation, ")");
            type_master < t_rel > :: status (s_invalid); } } };

template < > struct type_master < t_rel_obsolete > : type_master < t_rel >
{   using type_master < t_rel > :: type_master;
    void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   type_master < t_rel > :: set_value (nits, v, s);
        if (context.mf_verify ()) nits.pick (nit_unadvised, ed_microformats, "http://microformats.org/wiki/existing-rel-values", es_warning, ec_microformat, quote (s), " is obsolete");
        type_master < t_rel > :: status (s_invalid); } };
