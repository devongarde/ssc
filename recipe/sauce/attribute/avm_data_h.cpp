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

hav_t havt_h [] =
{   XHTML2_ATTRIBUTES (elem_h),
    STANDARD_H_ATTRIBUTES (elem_h1),
    STANDARD_H_ATTRIBUTES (elem_h2),
    STANDARD_H_ATTRIBUTES (elem_h3),
    STANDARD_H_ATTRIBUTES (elem_h4),
    STANDARD_H_ATTRIBUTES (elem_h5),
    STANDARD_H_ATTRIBUTES (elem_h6),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_handler [] =
{   { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_handler, a_evevent },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_handler, a_externalresourcesrequired },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_handler, a_type },
    SVG_CONDITIONAL_ATTRIBUTES (elem_handler),
    SVG_HTML_ATTRIBUTES (elem_handler),
    SVG_XLINK_ATTRIBUTES (elem_handler),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_hat [] =
{   HTML3_CLID_ATTRIBUTES (elem_hat),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_head [] =
{   { { HTML_4_0 }, { HTML_DEC06 }, elem_head, a_profile },
    HTML2_CLID_ATTRIBUTES (elem_head),
    HTML4_STANDARD_LANG_ATTRIBUTES (elem_head, MAJOR_4_0, MINOR_4_0),
    HTML4_STANDARD_SCRIPT_ATTRIBUTES (elem_head, HTML_2005, 0),
    EXTRA_HTML5_ATTRIBUTES (elem_head),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_header [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_header),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_hgroup [] =
{   STANDARD_HTML5_ATTRIBUTES (elem_hgroup),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_hint [] =
{   SVG_HTML_ATTRIBUTES (elem_hint),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_hkern [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_hkern, a_g1 },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_hkern, a_g2 },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_hkern, a_k },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_hkern, a_u1 },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_hkern, a_u2 },
    SVG_HTML_ATTRIBUTES (elem_hkern),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_hr [] =
{   { { HTML_2_0, HV_DEPRECATED4 | HV_RFC_2070 | HV_NOT30 }, { XHTML_2_0 }, elem_hr, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_hr, a_clear },
    { { HTML_2_0, 0, HE_BESPOKE }, { XHTML_2_0 }, elem_hr, a_colour },
    { { HTML_3_0 }, { HTML_3_0 }, elem_hr, a_md },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_hr, a_noshade },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_hr, a_size },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_hr, a_width },
    { { HTML_3_0 }, { HTML_3_0 }, elem_hr, a_src },
    HTMLPLUS_ATTRIBUTES (elem_hr),
    HTML3_CLID_ATTRIBUTES (elem_hr),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_hr),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_html [] =
{   { { HTML_3_0 }, { HTML_3_0 }, elem_html, a_class },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_html, a_dir },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_html, a_lang },
    { { HTML_JAN08, HV_DEPRECATED51 }, { HTML_DEC16 }, elem_html, a_manifest },
    { { HTML_JAN17, HV_DEPRECATED52x }, { HTML_DEC20 }, elem_html, a_manifest },
    { { HTML_3_0 }, { HTML_3_0 }, elem_html, a_role },
    { { HTML_3_0 }, { HTML_3_0 }, elem_html, a_urn },
    { { HTML_3_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_html, a_version },
    { { XHTML_2_0 }, { XHTML_2_0 }, elem_html, a_xsischemaloc },
    HTML2_CLID_ATTRIBUTES (elem_html),
    XHTML1_STANDARD_ATTRIBUTES (elem_html),
    EXTRA_HTML5_ATTRIBUTES (elem_html),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_htmlplus [] =
{   { { HTML_PLUS }, { HTML_PLUS }, elem_htmlplus, a_forms },
    { { HTML_PLUS }, { HTML_PLUS }, elem_htmlplus, a_version },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
