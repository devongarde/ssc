/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

#include "main/standard.h"
#include "attribute/avm_data.h"

hav_t havt_rdf [] =
{   STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_1),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_2),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_3),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_4),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_5),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_6),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_7),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_8),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_9),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_about),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_abouteach),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_abouteachprefix),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_alt),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_bag),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_bagid),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_datatype),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_description),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_id),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_li),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_nodeid),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_parsetype),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_rdf),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_resource),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_rdf_seq),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
