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

hav_t havt_dct_b [] =
{   STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_identifier),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_instructionalmethod),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_isformatof),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_ispartof),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_isreferencedby),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_isreplacedby),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_isrequiredby),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_issued),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_isversionof),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_language),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_licence),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_mediator),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_medium),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_modified),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_provenance),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_publisher),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_references),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_relation),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_replaces),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_requires),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_rights),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_rightsholder),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_source),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_spatial),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_subject),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_tableofcontents),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_temporal),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_title),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_type),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_valid),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
