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

hav_t havt_var [] =
{   HTMLPLUS_ATTRIBUTES (elem_var),
    HTML23_CLID_ATTRIBUTES (elem_var),
    STANDARD_HTMLS_4_5_ATTRIBUTES (elem_var),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_variance [] =
{   MATH3_DEFS_ATTRIBUTES (elem_variance),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_veaffine [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veaffine, a_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veaffine, a_result },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veaffine, a_transformpath },
    SVG_HTML_ATTRIBUTES (elem_veaffine),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vec [] =
{   HTML3_CLID_ATTRIBUTES (elem_vec),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vector [] =
{   MATH3_STANDARD_ATTRIBUTES (elem_vector),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vectoreffect [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, a_compositing },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vectoreffect, a_vectoreffectunits },
    SVG_HTML_ATTRIBUTES (elem_vectoreffect),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vectorproduct [] =
{   MATH3_DEFS_ATTRIBUTES (elem_vectorproduct),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_veexclude [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veexclude, a_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veexclude, a_in2 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veexclude, a_result },
    SVG_HTML_ATTRIBUTES (elem_veexclude),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vefill [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vefill, a_fill },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vefill, a_in2 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vefill, a_transform },
    SVG_HTML_ATTRIBUTES (elem_vefill),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vejoin [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vejoin, a_connect },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vejoin, a_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vejoin, a_in2 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vejoin, a_result },
    SVG_HTML_ATTRIBUTES (elem_vejoin),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_veintersect [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veintersect, a_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veintersect, a_in2 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veintersect, a_result },
    SVG_HTML_ATTRIBUTES (elem_veintersect),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vemarker [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vemarker, a_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vemarker, a_marker_end },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vemarker, a_marker_mid },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vemarker, a_marker_start },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vemarker, a_transform },
    SVG_HTML_ATTRIBUTES (elem_vemarker),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vepath [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vepath, a_result },
    SVG_HTML_ATTRIBUTES (elem_vepath),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vepathref [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vepathref, a_connect },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vepathref, a_reverse },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vepathref, a_transform },
    SVG_HTML_ATTRIBUTES (elem_vepathref),
    SVG_XLINK_ATTRIBUTES (elem_vepathref),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vereverse [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vereverse, a_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vereverse, a_result },
    SVG_HTML_ATTRIBUTES (elem_vereverse),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vesetback [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vesetback, a_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vesetback, a_result },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vesetback, a_setback_offset },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vesetback, a_transform },
    SVG_HTML_ATTRIBUTES (elem_vesetback),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vestroke [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestroke, a_fill },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestroke, a_in2 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestroke, a_transform },
    SVG_HTML_ATTRIBUTES (elem_vestroke),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vestrokepath [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestrokepath, a_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestrokepath, a_result },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestrokepath, a_stroke_dasharray },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestrokepath, a_stroke_dashoffset },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestrokepath, a_stroke_linecap },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestrokepath, a_stroke_linejoin },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestrokepath, a_stroke_miterlimit },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestrokepath, a_stroke_width },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_vestrokepath, a_transform },
    SVG_HTML_ATTRIBUTES (elem_vestrokepath),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_veunion [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veunion, a_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veunion, a_in2 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_veunion, a_result },
    SVG_HTML_ATTRIBUTES (elem_veunion),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_video [] =
{   { { HTML_JAN11 }, { HTML_JUN11 }, elem_video, a_audio },
    { { HTML_JUL09 }, { HTML_JUN10 }, elem_video, a_autobuffer },
    { { HTML_JUL07, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_video, a_autopictureinpicture },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_video, a_autoplay },
    { { HTML_JUL07, 0, HE_MOZILLA | HE_OPERA }, { HTML_UNDEF }, elem_video, a_buffered },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_video, a_controls },
    { { HTML_JUL07, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_video, a_controlslist },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_video, a_crossorigin },
    { { HTML_JUL07, 0, HE_BESPOKE }, { HTML_UNDEF }, elem_video, a_currenttime },
    { { HTML_JUL07, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, elem_video, a_disablepictureinpicture },
    { { HTML_5_3, HV_W3 }, { HTML_5_3 }, elem_video, a_disableremoteplayback },
    { { HTML_JUL07, 0, HE_BESPOKE }, { HTML_UNDEF }, elem_video, a_duration },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_end },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_externalresourcesrequired },
    { { HTML_JAN08 }, { HTML_UNDEF }, elem_video, a_height },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_initialvisibility },
    { { HTML_JUL07, 0, HE_CHROME | HE_OPERA }, { HTML_UNDEF }, elem_video, a_intrinsicsize },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_video, a_loop },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_loopcount },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_loopend },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_loopstart },
    { { HTML_JUL11 }, { HTML_JUN16 }, elem_video, a_mediagroup },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_video, a_muted },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_overlay },
    { { HTML_JAN08 }, { HTML_DEC08 }, elem_video, a_playcount },
    { { HTML_JAN17, HV_NOT5W3 }, { HTML_UNDEF }, elem_video, a_playsinline },
    { { HTML_JAN08 }, { HTML_UNDEF }, elem_video, a_poster },
    { { HTML_JUL10 }, { HTML_UNDEF }, elem_video, a_preload },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_preserveaspectratio },
    { { HTML_JUL07 }, { HTML_UNDEF }, elem_video, a_src },
    { { HTML_JUL07 }, { HTML_DEC08 }, elem_video, a_start },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_transformbehaviour },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_video, a_transin },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, elem_video, a_transout },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, elem_video, a_type },
    { { HTML_JAN08 }, { HTML_UNDEF }, elem_video, a_width },
    SVG_ANIMATION_TIMING_ATTRIBUTES (elem_video),
    SVG_BOX_ATTRIBUTES (elem_video),
    SVG_CONDITIONAL_ATTRIBUTES (elem_video),
    SVG_HTML_ATTRIBUTES (elem_video),
    SVG_PRESENTATION_ATTRIBUTES (elem_video),
    SVG_SYNC_ATTRIBUTES (elem_video),
    SVG_XLINK_ATTRIBUTES (elem_video),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_view [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, elem_view, a_externalresourcesrequired },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_view, a_preserveaspectratio },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, elem_view, a_viewbox },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_view, a_viewtarget },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 }, { HTML_UNDEF }, elem_view, a_zoomandpan },
    SVG_DOCUMENT_EVENT_ATTRIBUTES_EX (elem_view, HE_SVG_2),
    SVG_HTML_ATTRIBUTES (elem_view),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_vkern [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_vkern, a_g1 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_vkern, a_g2 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_vkern, a_k },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_vkern, a_u1 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, elem_vkern, a_u2 },
    SVG_HTML_ATTRIBUTES (elem_vkern),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
