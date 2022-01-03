/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

hav_t havt_dct_a [] =
{   STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_abstract),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_accessrights),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_accrualmethod),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_accrualperiodicity),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_accrualpolicy),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_alternative),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_audience),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_available),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_bibliographiccitation),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_conformsto),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_contributor),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_coverage),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_created),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_creator),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_date),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_dateaccepted),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_datecopyrighted),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_datesubmitted),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_description),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_educationlevel),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_extent),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_format),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_hasformat),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_haspart),

    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dct_hasversion),

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
