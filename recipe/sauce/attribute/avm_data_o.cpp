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

hav_t havt_o [] =
{   { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_archive },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_object, a_align },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_object, a_border },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_classid },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_codebase },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_codetype },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_object, a_data },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_datafld },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_dataformatas },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_datasrc },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_declare },
    { { HTML_JAN09, HV_NOT53 }, { HTML_5_2 }, elem_object, a_form },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_object, a_height },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_object, a_hspace },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_name },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_object, a_name },
    { { HTML_4_0 }, { XHTML_2_0 }, elem_object, a_standby },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_object, a_type },
    { { HTML_JAN11 }, { HTML_JUN19 }, elem_object, a_typemustmatch },
    { { HTML_4_0, HV_NOT5123 }, { HTML_MAR21 }, elem_object, a_usemap },
    { { HTML_4_0, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_object, a_vspace },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_object, a_width },
    HTML4_FORM_ATTRIBUTES (elem_object),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_object),

    { { HTML_2_0, HV_RFC_2070 }, { HTML_2_0 }, elem_ol, a_align },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ol, a_clear },
    { { HTML_PLUS, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ol, a_compact },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ol, a_continue },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_ol, a_reversed },
    { { HTML_3_0 }, { HTML_3_0 }, elem_ol, a_seqnum },
    { { HTML_3_2, HV_DEPRECATED4 }, { XHTML_2_0 }, elem_ol, a_type },
    { { HTML_JAN11 }, { HTML_UNDEF }, elem_ol, a_type },
    { { HTML_3_2, HV_DEPRECATED4 }, { HTML_UNDEF }, elem_ol, a_start },
    HTMLPLUS_ATTRIBUTES (elem_ol),
    HTML23_CLID_ATTRIBUTES (elem_ol),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_ol),

    { { HTML_4_0 }, { HTML_UNDEF }, elem_optgroup, a_disabled },
    { { HTML_4_0, REQUIRED }, { HTML_UNDEF }, elem_optgroup, a_label },
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_optgroup),

    { { HTML_JAN05 }, { HTML_DEC05 }, elem_option, a_command },
    { { HTML_PLUS, HV_NOT2 | HV_NOT32 }, { HTML_UNDEF }, elem_option, a_disabled },
    { { HTML_3_0 }, { HTML_3_0 }, elem_option, a_error },
    { { HTML_4_0 }, { HTML_UNDEF }, elem_option, a_label },
    { { HTML_PLUS }, { HTML_UNDEF }, elem_option, a_selected },
    { { HTML_3_0 }, { HTML_3_0 }, elem_option, a_shape },
    { { HTML_2_0 }, { HTML_UNDEF }, elem_option, a_value },
    HTML23_CLID_ATTRIBUTES (elem_option),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_option),

    MATH3_DEFS_ATTRIBUTES (elem_or),

    MATH3_STANDARD_ATTRIBUTES (elem_otherwise),

    MATH3_DEFS_ATTRIBUTES (elem_outerproduct),

    { { HTML_JAN09 }, { HTML_UNDEF }, elem_output, a_for },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_output, a_form },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_output, a_name },
    STANDARD_HTML5_ATTRIBUTES (elem_output),

    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_height },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_imagemap },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_md },
    { { HTML_3_0, REQUIRED }, { HTML_3_0 }, elem_overlay, a_src },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_units },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_width },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_x },
    { { HTML_3_0 }, { HTML_3_0 }, elem_overlay, a_y },

    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
