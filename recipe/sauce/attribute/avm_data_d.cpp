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

hav_t havt_data [] =
{   { { HTML_JAN12 }, { HTML_UNDEF }, elem_data, a_value },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_data),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_datagrid [] =
{   { { HTML_JUL05 }, { HTML_DEC09 }, elem_datagrid, a_disabled },
    { { HTML_JUL05 }, { HTML_DEC09 }, elem_datagrid, a_multiple },
    STANDARD_HTML5_ATTRIBUTES (elem_datagrid),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_datalist [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_datalist),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_datatemplate [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_datatemplate),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_dd [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_dd, a_clear },
    HTML23_CLID_ATTRIBUTES (elem_dd),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dd),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_ddot [] =
{   HTML3_CLID_ATTRIBUTES (elem_ddot),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_declare [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_declare, a_nargs },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_declare, a_occurrence },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_declare, a_scope },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_declare, a_type },
    MATH3_DEFS_ATTRIBUTES (elem_declare),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_definition_src [] =
{   SVG_XLINK_ATTRIBUTES (elem_definition_src),
    SVG_HTML_ATTRIBUTES (elem_definition_src),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_defs [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_defs, a_class },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, elem_defs, a_style },
    SVG_PRESENTATION_ATTRIBUTES_2 (elem_defs),
    SVG_HTML_ATTRIBUTES (elem_defs),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_degree [] =
{   MATH3_STANDARD_ATTRIBUTES (elem_degree),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_del [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, elem_del, a_cite },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_del, a_datetime },
    HTML3_CLID_ATTRIBUTES (elem_del),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_del),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_desc [] =
{   SVG_PRESENTATION_ATTRIBUTES_2 (elem_desc),
    SVG_HTML_ATTRIBUTES (elem_desc),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_details [] =
{   { { HTML_JAN07, HV_NOT50 }, { HTML_UNDEF }, elem_details, a_open },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_details),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_determinant [] =
{   MATH3_DEFS_ATTRIBUTES (elem_determinant),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_device [] =
{   { { HTML_JAN10 }, { HTML_JUN11 }, elem_device, a_type },
    STANDARD_HTML5_ATTRIBUTES (elem_device),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_devicecolour [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL | REQUIRED }, { HTML_UNDEF }, elem_devicecolour, a_name },
    SVG_HTML_ATTRIBUTES (elem_devicecolour),
    SVG_XLINK_ATTRIBUTES (elem_devicecolour),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_dfn [] =
{   HTMLPLUS_ATTRIBUTES (elem_dfn),
    HTML3_CLID_ATTRIBUTES (elem_dfn),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dfn),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_di [] =
{   XHTML2_ATTRIBUTES (elem_di),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_dialogue [] =
{   { { HTML_JUL12 }, { HTML_UNDEF }, elem_dialogue, a_open },
    STANDARD_HTML5_ATTRIBUTES (elem_dialogue),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_diff [] =
{   MATH3_DEFS_ATTRIBUTES (elem_diff),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_dir [] =
{   { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_dir, a_align },
    { { HTML_3_2 }, { HTML_3_0 }, elem_dir, a_clear },
    { { HTML_2_0 }, { XHTML_2_0 }, elem_dir, a_compact },
    HTMLPLUS_ATTRIBUTES (elem_dir),
    HTML2_CLID_ATTRIBUTES (elem_dir),
    COMMON_HTML4_ATTRIBUTES (elem_dir),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_discard [] =
{   { { HTML_SVG12, 0, HE_SVG_12_2 }, { HTML_UNDEF }, elem_discard, a_begin },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_discard, a_href },
    SVG_HTML_ATTRIBUTES (elem_discard),
    SVG_XLINK_ATTRIBUTES_EX (elem_discard, HE_SVG_12),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_dispatchevent [] =
{   { { XHTML_2_0 }, { XHTML_2_0 }, elem_dispatchevent, a_bubbles },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_dispatchevent, a_cancelable },
    XHTML2_ATTRIBUTES (elem_dispatchevent),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_div [] =
{   { { HTML_3_0 }, { XHTML_2_0 }, elem_div, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_div, a_clear },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_div, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_div, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_div, a_datasrc },
    { { HTML_3_0 }, { HTML_3_0 }, elem_div, a_nowrap },
    HTML3_CLID_ATTRIBUTES (elem_div),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_div),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_divergence [] =
{   MATH3_DEFS_ATTRIBUTES (elem_divergence),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_divide [] =
{   MATH3_DEFS_ATTRIBUTES (elem_divide),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_dl [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_dl, a_clear },
    { { HTML_1_0 }, { HTML_3_2 }, elem_dl, a_compact },
    HTMLPLUS_ATTRIBUTES (elem_dl),
    HTML23_CLID_ATTRIBUTES (elem_dl),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dl),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_domain [] =
{   MATH3_DEFS_ATTRIBUTES (elem_domain),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_domainofapplication [] =
{   MATH3_DEFS_ATTRIBUTES (elem_domainofapplication),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_dot [] =
{   HTML3_CLID_ATTRIBUTES (elem_dot),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_dt [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_dt, a_clear },
    HTML23_CLID_ATTRIBUTES (elem_dt),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_dt),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
