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

hav_t havt_dc [] =
{   STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_contributor),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_coverage),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_creator),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_date),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_description),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_format),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_identifier),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_language),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_publisher),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_relation),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_rights),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_source),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_subject),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_title),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dc_type),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
