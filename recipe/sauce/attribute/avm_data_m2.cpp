/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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

hav_t havt_mpadded [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_mpadded, a_lspace },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4_C }, { HTML_UNDEF }, elem_mpadded, a_voffset },
    MATH_SIZEINFO_ATTRIBUTES (elem_mpadded),
    MATH4_PRES_ATTRIBUTES (elem_mpadded),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mpadded),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mpath [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_mpath, a_externalresourcesrequired },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, elem_mpath, a_href },
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_mpath, HE_SVG_2),
    SVG_HTML_ATTRIBUTES (elem_mpath),
    SVG_XLINK_ATTRIBUTES_EX (elem_mpath, HE_SVG_1),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mphantom [] =
{   MATH4_PRES_ATTRIBUTES (elem_mphantom),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mphantom),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mprescripts [] =
{   { { HTML_MATH1, 0, 0, H2_MATH_1_2_3 }, { HTML_UNDEF }, elem_mprescripts, a_xmlns },
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mprescripts),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mroot [] =
{   MATH4_PRES_ATTRIBUTES (elem_mroot),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mroot),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrow [] =
{   MATH4_PRES_ATTRIBUTES (elem_mrow),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mrow),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_adult [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_adult),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_backlink [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_backlink),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_backlinks [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_backlinks),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_category [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_category, a_mrss_scheme },
    RDFa_META_ATTRIBUTES (elem_mrss_category),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_comment [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_comment),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_comments [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_comments),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_community [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_community),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_content [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_bitrate },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_channels },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_duration },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_expression },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_filesize },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_framerate },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_height },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_isdefault },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_lang },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_medium },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_samplingrate },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_type },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_url },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_content, a_mrss_width },
    RDFa_META_ATTRIBUTES (elem_mrss_content),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_copyright [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_copyright, a_mrss_url },
    RDFa_META_ATTRIBUTES (elem_mrss_copyright),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_credit [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_credit, a_mrss_role },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_credit, a_mrss_scheme },
    RDFa_META_ATTRIBUTES (elem_mrss_credit),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_description [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_description, a_mrss_type },
    RDFa_META_ATTRIBUTES (elem_mrss_description),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_embed [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_embed, a_mrss_height },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_embed, a_mrss_url },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_embed, a_mrss_width },
    RDFa_META_ATTRIBUTES (elem_mrss_embed),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_group [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_group),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_hash [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_hash, a_mrss_algo },
    RDFa_META_ATTRIBUTES (elem_mrss_hash),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_keywords [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_keywords),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_licence [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_licence, a_mrss_type },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_licence, a_href },
    RDFa_META_ATTRIBUTES (elem_mrss_licence),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_location [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_location, a_mrss_description },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_location, a_mrss_end },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_location, a_mrss_start },
    RDFa_META_ATTRIBUTES (elem_mrss_location),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_param [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_param, a_mrss_name },
    RDFa_META_ATTRIBUTES (elem_mrss_param),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_peerlink [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_peerlink, a_mrss_type },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_peerlink, a_href },
    RDFa_META_ATTRIBUTES (elem_mrss_peerlink),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_player [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_player, a_mrss_height },
    { { HTML_MRSS, HV_REQUIRED }, { HTML_UNDEF }, elem_mrss_player, a_mrss_url },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_player, a_mrss_width },
    RDFa_META_ATTRIBUTES (elem_mrss_player),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_price [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_price, a_mrss_currency },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_price, a_mrss_info },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_price, a_mrss_price },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_price, a_mrss_type },
    RDFa_META_ATTRIBUTES (elem_mrss_price),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_rating [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_rating, a_mrss_scheme },
    RDFa_META_ATTRIBUTES (elem_mrss_rating),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_response [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_response),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_responses [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_responses),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_rights [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_rights, a_mrss_status },
    RDFa_META_ATTRIBUTES (elem_mrss_rights),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_restriction [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_restriction, a_mrss_relationship },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_restriction, a_mrss_type },
    RDFa_META_ATTRIBUTES (elem_mrss_restriction),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_scene [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_scene),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_scenedescription [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_scenedescription),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_sceneendtime [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_sceneendtime),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_scenes [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_scenes),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_scenestarttime [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_scenestarttime),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_scenetitle [] =
{   RDFa_META_ATTRIBUTES (elem_mrss_scenetitle),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_starrating [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_starrating, a_mrss_average },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_starrating, a_mrss_count },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_starrating, a_mrss_max },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_starrating, a_mrss_min },
    RDFa_META_ATTRIBUTES (elem_mrss_starrating),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_statistics [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_statistics, a_mrss_favourites },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_statistics, a_mrss_views },
    RDFa_META_ATTRIBUTES (elem_mrss_statistics),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_status [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_status, a_mrss_reason },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_status, a_mrss_state },
    RDFa_META_ATTRIBUTES (elem_mrss_status),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_subtitle [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_subtitle, a_mrss_type },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_subtitle, a_mrss_lang },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_subtitle, a_href },
    RDFa_META_ATTRIBUTES (elem_mrss_subtitle),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_thumbnail [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_thumbnail, a_mrss_height },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_thumbnail, a_mrss_time },
    { { HTML_MRSS, HV_REQUIRED }, { HTML_UNDEF }, elem_mrss_thumbnail, a_mrss_url },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_thumbnail, a_mrss_width },
    RDFa_META_ATTRIBUTES (elem_mrss_thumbnail),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_text [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_text, a_mrss_end },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_text, a_mrss_lang },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_text, a_mrss_start },
    { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_text, a_mrss_type },
    RDFa_META_ATTRIBUTES (elem_mrss_text),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mrss_title [] =
{   { { HTML_MRSS }, { HTML_UNDEF }, elem_mrss_title, a_mrss_type },
    RDFa_META_ATTRIBUTES (elem_mrss_title),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_ms [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_ms, a_lquote },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_ms, a_rquote },
    MATH4_PRES_ATTRIBUTES (elem_ms),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_ms),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mscarries [] =
{   { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mscarries, a_crossout },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mscarries, a_location },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mscarries, a_scriptsizemultiplier },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mscarries, a_position },
    MATH4_PRES_ATTRIBUTES (elem_mscarries),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mscarry [] =
{   { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mscarry, a_crossout },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mscarry, a_location },
    MATH4_PRES_ATTRIBUTES (elem_mscarry),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msgroup [] =
{   { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msgroup, a_position },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msgroup, a_shift },
    MATH4_PRES_ATTRIBUTES (elem_msgroup),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msline [] =
{   { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msline, a_leftoverhang },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msline, a_length },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msline, a_mslinethickness },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msline, a_position },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msline, a_position },
    MATH4_PRES_ATTRIBUTES (elem_msline),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mspace [] =
{   { { HTML_MATH1, 0, 0, H2_MATH_1_2_3 }, { HTML_UNDEF }, elem_mspace, a_linebreak },
    MATH3_TOKEN_ATTRIBUTES (elem_mspace),
    MATH3_INDENT_ATTRIBUTES (elem_mspace),
    MATH_SIZEINFO_ATTRIBUTES (elem_mspace),
    MATH4_PRES_ATTRIBUTES (elem_mspace),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mspace),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msqrt [] =
{   MATH4_PRES_ATTRIBUTES (elem_msqrt),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_msqrt),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msrow [] =
{   { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_msrow, a_position },
    MATH4_PRES_ATTRIBUTES (elem_msrow),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mstack [] =
{   { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstack, a_align },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstack, a_charalign },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstack, a_charspacing },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstack, a_stackalign },
    MATH4_PRES_ATTRIBUTES (elem_mstack),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mstyle [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_accentunder },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mstyle, a_background },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_bevelled },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_charalign },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_charspacing },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_close },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_columnspan },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_crossout },
    { { HTML_JAN26, 0, 0, H2_MATH_4 }, { HTML_UNDEF }, elem_mstyle, a_decimalcharacter },
    { { HTML_MATH3, 0, 0, H2_MATH_3 }, { HTML_UNDEF }, elem_mstyle, a_decimalpoint },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_denomalign },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_depth },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2_3 }, { HTML_UNDEF }, elem_mstyle, a_displaystyle },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_edge },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_height },
    { { HTML_MATH3, 0, 0, H2_MATH_3 }, { HTML_UNDEF }, elem_mstyle, a_infixlinebreakstyle },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_leftoverhang },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_length },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_linethickness },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_location },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_longdivstyle },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_lquote },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mstyle, a_mediummathspace },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_mslinethickness },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_notation },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_numalign },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_open },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_position },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_rightoverhang },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_rowspan },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_rquote },
    { { HTML_MATH1, 0, 0, H2_MATH }, { HTML_UNDEF }, elem_mstyle, a_scriptlevel },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2_3 }, { HTML_UNDEF }, elem_mstyle, a_scriptminsize },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2_3 }, { HTML_UNDEF }, elem_mstyle, a_scriptsizemultiplier },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_selection },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_separators },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_shift },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_stackalign },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_subscriptshift },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mstyle, a_superscriptshift },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mstyle, a_thickmathspace },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mstyle, a_thinmathspace },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_mstyle, a_valign },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mstyle, a_verythickmathspace },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mstyle, a_verythinmathspace },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mstyle, a_veryverythickmathspace },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2 }, { HTML_UNDEF }, elem_mstyle, a_veryverythinmathspace },
    MATH3_INDENTBREAK_ATTRIBUTES (elem_mstyle),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mstyle),
    MATH_OPINFO_ATTRIBUTES (elem_mstyle),
    MATH3_TABLE_ATTRIBUTES (elem_mstyle),
    MATH4_PRES_ATTRIBUTES (elem_mstyle),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mstyle),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msub [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_msub, a_subscriptshift },
    MATH4_PRES_ATTRIBUTES (elem_msub),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_msub),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msubsup [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_msubsup, a_subscriptshift },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_msubsup, a_superscriptshift },
    MATH4_PRES_ATTRIBUTES (elem_msubsup),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_msubsup),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_msup [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_msup, a_superscriptshift },
    MATH4_PRES_ATTRIBUTES (elem_msup),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_msup),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mtable [] =
{   MATH3_TABLE_ATTRIBUTES (elem_mtable),
    MATH4_PRES_ATTRIBUTES (elem_mtable),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mtable),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mtd [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mtd, a_columnalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_columnspan },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2_3 }, { HTML_UNDEF }, elem_mtd, a_groupalign },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mtd, a_rowalign },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_mtd, a_rowspan },
    MATH4_PRES_ATTRIBUTES (elem_mtd),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mtd),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mtext [] =
{   MATH4_PRES_ATTRIBUTES (elem_mtext),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mtext),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_mtr [] =
{   { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mtr, a_columnalign },
    { { HTML_MATH1, 0, 0, H2_MATH_1_2_3 }, { HTML_UNDEF }, elem_mtr, a_groupalign },
    { { HTML_MATH1, 0, 0, H2_MATHML }, { HTML_UNDEF }, elem_mtr, a_rowalign },
    MATH4_PRES_ATTRIBUTES (elem_mtr),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_mtr),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_munder [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_munder, a_accentunder },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_munder, a_align },
    MATH4_PRES_ATTRIBUTES (elem_munder),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_munder),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_munderover [] =
{   { { HTML_MATH1 }, { HTML_UNDEF }, elem_munderover, a_accent },
    { { HTML_MATH1 }, { HTML_UNDEF }, elem_munderover, a_accentunder },
    { { HTML_MATH3, 0, 0, H2_MATH_3_4 }, { HTML_UNDEF }, elem_munderover, a_align },
    MATH4_PRES_ATTRIBUTES (elem_munderover),
    STANDARD_MATH_CORE_ATTRIBUTES (elem_munderover),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
