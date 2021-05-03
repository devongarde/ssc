/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

#include "main/standard.h"
#include "element/element.h"
#include "element/element_classes.h"

void element::check_inclusion_criteria ()
{   if (node_.version ().svg_version () == sv_2_0)
        if (a_.known (a_role))
            if ((descendant_attributes_ & (empty_attribute_bitset | a_title | a_arialabel | a_arialabelledby)).any ())
                if (is_default_role (node_.version (), node_.id (), static_cast < e_aria_role > (a_.get_int (a_role))))
                    pick (nit_default_role, ed_svg_2_0, "5.12.4. Implicit and Allowed ARIA Semantics", es_warning, ec_type, "do not specify the default role here"); }

void element::examine_aria_checked ()
{   DBG_ASSERT (a_.known (a_ariachecked));
    if (! has_attribute (tag (), a_checked))
        nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                        es_error, ec_aria, "ARIA-CHECKED is only valid where CHECKED is permitted");
    else if (a_.known (a_checked))
        if (a_.good (a_checked) && a_.good (a_ariachecked))
            if (a_.get_int (a_checked) != a_.get_int (a_ariachecked))
                nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_warning, ec_aria, "ARIA-CHECKED should never contradict CHECKED"); }

void element::examine_aria_colspan ()
{   DBG_ASSERT (a_.known (a_ariacolspan));
    if (! has_attribute (tag (), a_colspan))
        nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                        es_error, ec_aria, "ARIA-COLSPAN is only valid where COLSPAN is permitted");
    else if (a_.known (a_colspan))
        if (a_.good (a_ariacolspan))
            if (a_.get_int (a_ariacolspan) == a_.get_int (a_colspan))
                nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_warning, ec_aria, "ARIA-COLSPAN should not be used here");
            else nits ().pick ( nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_error, ec_aria, "ARIA-COLSPAN must never contradict COLSPAN"); }

void element::examine_aria_disabled ()
{   DBG_ASSERT (a_.known (a_ariadisabled));
    if (! has_attribute (tag (), a_disabled))
        nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                        es_error, ec_aria, "ARIA-DISABLED is only valid where DISABLED is permitted");
    else if (a_.known (a_disabled))
        if (a_.good (a_disabled) && a_.good (a_ariadisabled))
            if (a_.get_int (a_disabled) != a_.get_int (a_ariadisabled))
                nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_error, ec_aria, "ARIA-DISABLED must never contradict DISABLED"); }

void element::examine_aria_hidden ()
{   DBG_ASSERT (a_.known (a_ariahidden));
    if (a_.known (a_hidden))
        if (a_.good (a_ariahidden))
            if (a_.get_int (a_ariahidden) == 1)
                nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_warning, ec_aria, "ARIA-HIDDEN should not be used here");
            else nits ().pick ( nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_warning, ec_aria, "ARIA-HIDDEN must never contradict HIDDEN"); }

void element::examine_aria_placeholder ()
{   DBG_ASSERT (a_.known (a_ariaplaceholder));
    if (! has_attribute (tag (), a_checked))
        nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                        es_error, ec_aria, "ARIA-PLACEHOLDER is only valid where PLACEHOLDER is permitted");
    else if (a_.known (a_placeholder))
        if (a_.good (a_placeholder) && a_.good (a_ariaplaceholder))
            nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                            es_error, ec_aria, "ARIA-PLACEHOLDER must not be used where PLACEHOLDER is used"); }

void element::examine_aria_readonly ()
{   DBG_ASSERT (a_.known (a_ariareadonly));
    if (a_.known (a_readonly))
        if (a_.good (a_ariareadonly))
            if (a_.get_int (a_ariareadonly) == 1)
                nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_warning, ec_aria, "ARIA-READONLY should not be used here");
            else nits ().pick ( nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_error, ec_aria, "ARIA-READONLY must never contradict READONLY");
    if (a_.known (a_contenteditable))
        if (a_.good (a_ariareadonly))
            if (a_.get_int (a_ariareadonly) == 1)
                nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_error, ec_aria, "ARIA-READONLY must never contradict CONTENTEDITABLE"); }

void element::examine_aria_required ()
{   DBG_ASSERT (a_.known (a_ariarequired));
    if (! has_attribute (tag (), a_required))
        nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                        es_error, ec_aria, "ARIA-REQUIRED is only valid where REQUIRED is permitted");
    else if (a_.known (a_required))
        if (a_.good (a_ariarequired))
            if (a_.get_int (a_ariarequired) == 1)
                nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_warning, ec_aria, "ARIA-REQUIRED should not be used here");
            else nits ().pick ( nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_error, ec_aria, "ARIA-REQUIRED must never contradict REQUIRED"); }

void element::examine_aria_rowspan ()
{   DBG_ASSERT (a_.known (a_ariarowspan));
    if (! has_attribute (tag (), a_rowspan))
        nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                        es_error, ec_aria, "ARIA-ROWSPAN is only valid where ROWSPAN is permitted");
    else if (a_.known (a_rowspan))
        if (a_.good (a_ariarowspan))
            if (a_.get_int (a_ariarowspan) == a_.get_int (a_rowspan))
                nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_warning, ec_aria, "ARIA-ROWSPAN should not be used here");
            else nits ().pick ( nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                                es_error, ec_aria, "ARIA-ROWSPAN must never contradict ROWSPAN"); }

void element::examine_aria_valuemax ()
{   DBG_ASSERT (a_.known (a_ariavaluemax));
    if (has_attribute (tag (), a_max))
        if (a_.known (a_max))
            nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                            es_error, ec_aria, "ARIA-VALUEMAX must not be used where MAX is used");
        else nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                            es_error, ec_aria, "use MAX, not ARIA-VALUEMAX"); }

void element::examine_aria_valuemin ()
{   DBG_ASSERT (a_.known (a_ariavaluemin));
    if (has_attribute (tag (), a_min))
        if (a_.known (a_max))
            nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                            es_error, ec_aria, "ARIA-VALUEMIN must not be used where MIN is used");
        else nits ().pick (  nit_aria_position, ed_ariaApr2021, "Document conformance requirements for use of ARIA attributes with HTML attributes",
                            es_error, ec_aria, "use MIN, not ARIA-VALUEMIN"); }
