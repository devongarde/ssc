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
#include "webpage/page.h"

void element::examine_picture ()
{   bool was_img = false, had_img = false, order_warn = false;
    element* prev = nullptr;
    for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
        if (! c -> node_.is_closure ())
            switch (c -> tag ())
            {   case elem_source :
                    if (was_img) { order_warn = true; was_img = false; }
                    if ((prev != nullptr) && ! prev -> a_.known (a_type))
                    {   bool ok = prev -> a_.known (a_media);
                        if (ok)
                        {   ::std::string val = prev -> a_.get_string (a_media);
                            ok = ! val.empty () && ! compare_no_case ("all", val); }
                        if (! ok)
                            pick (nit_saucy_source, ed_jul20, "4.8.2 The source element", es_warning, ec_element,
                                "All but the last <SOURCE> must have either TYPE or MEDIA, which itself is neither empty nor set to 'all'."); }
                    prev = c;
                    break;
                case elem_img :
                    if (had_img)
                        pick (nit_not_img, ed_52, "4.7.3. The picture element", es_error, ec_element, "<PICTURE> can only have one <IMG> child.");
                    had_img = was_img = true; break;
                default : break; }
    if (! had_img)
        pick (nit_not_img, ed_52, "4.7.3. The picture element", es_error, ec_element, "<PICTURE> must have one child <IMG>");
    else if (! was_img || order_warn)
        pick (nit_not_img, ed_52, "4.7.3. The picture element", es_error, ec_element, "under <PICTURE>, <SOURCE> must precede <IMG>"); }

void element::examine_piecewise ()
{   bool otherwise = false, noted = false;
    for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
        if (c -> node_.id ().is_math () && ! c -> node_.is_closure ())
        switch (c -> tag ())
        {   case elem_otherwise :
                otherwise = true; break;
            case elem_piece :
                if (otherwise && ! noted)
                {   pick (nit_bad_piece, ed_math_2, "4.4.2.16 Piecewise declaration (piecewise, piece, otherwise)", es_error, ec_element, "<PIECE> cannot follow <OTHERWISE>");
                    noted = true; }
                break;
            default :
                assert (false);
                break; } }

void element::examine_progress ()
{   if (node_.version ().is_5 ())
    {   check_ancestors (elem_progress, element_bit_set (elem_progress));
        if (a_.known (a_value))
        {   bool kn = a_.known (a_max);
            double max = 1.0;
            double value = 0.0;
            if (kn)
            {   max = lexical < double > :: cast (a_.get_string (a_max));
                if (max < 0.0) pick (nit_no_progress, ed_50, "4.10.14 The progress element", es_error, ec_element, "<PROGRESS> MAX cannot be negative"); }
            value = lexical < double > :: cast (a_.get_string (a_value));
            if (value < 0.0) pick (nit_no_progress, ed_50, "4.10.14 The progress element", es_error, ec_element, "<PROGRESS> VALUE cannot be negative");
            if (value > max)
                if (kn) pick (nit_no_progress, ed_50, "4.10.14 The progress element", es_warning, ec_element, "<PROGRESS> VALUE exceeds MAX");
                else pick (nit_no_progress, ed_50, "4.10.14 The progress element", es_warning, ec_element, "<PROGRESS> VALUE exceeds 1.0, the default for MAX"); } } }

void element::examine_reln ()
{   if (page_.version ().math () > math_1)
        pick (nit_use_apply, ed_math_2, "4.2.1.3 The apply construct", es_comment, ec_element, "use <APPLY>, not <RELN>"); }

void element::examine_ruby ()
{   if (node_.version ().mjr () < 5) return;
    bool had_ruby = false, had_non_ruby = false, had_rt = false, had_rp = false, rp_mode = false;
    bool is_whatwg = node_.version ().whatwg ();
    for (element* c = child_.get (); c != nullptr; c = c -> sibling_.get ())
        if (is_standard_element (c -> tag ()) && ! c -> node_.is_closure ())
            if (is_whatwg)
                switch (c -> tag ())
                {   case elem_ruby :
                        if (had_non_ruby) pick (nit_mix_ruby_non, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "do not mix child <RUBY> elements with child phrasal elements");
                        else if (had_ruby) pick (nit_too_many_ruby, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "each child <RUBY> must be separated by an <RT>");
                        if (had_rt || had_rp)
                                pick (nit_no_rp, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "each child <RUBY> must precede any <RT> or <RP> children");
                        had_ruby = true;
                        had_non_ruby = had_rt = had_rp = rp_mode = false;
                        break;
                    case elem_rt :
                        if (rp_mode && had_rt)
                            pick (nit_no_rp, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "<RP> should be interleaved with <RT>");
                        had_ruby = had_non_ruby = had_rp = false;
                        had_rt = true;
                        break;
                    case elem_rp :
                        if (! rp_mode && had_rt)
                            pick (nit_no_rp, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "<RP> must precede any <RT>");
//                        else if (had_rp)
//                            pick (nit_no_rp, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "<RP> should interleave with <RT>");
                        had_ruby = had_non_ruby = had_rt = false;
                        had_rp = rp_mode = true;
                        break;
                    default :
                        if (had_ruby) pick (nit_too_many_ruby, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "Do not mix child <RUBY>s with child phrasal elements");
                        had_non_ruby = true;
                        had_ruby = had_rt = had_rp = false;
                        break; }
                else switch (c -> tag ())
                {   case elem_rt :
                    case elem_rtc :
                        if (had_rt)
                            pick (nit_no_rp, ed_51, "4.5.10 The ruby element", es_error, ec_element, "<RP> should immediately precede OR follow <RT> and/or <RTC>");
                        else had_rt = true;
                        break;
                    case elem_rp :
                        had_rp = true;
                        break;
                    default :
                        if (had_rt != had_rp)
                            pick (nit_no_rp, ed_51, "4.5.10 The ruby element", es_error, ec_element, "<RT> and <RTC> elements must precede or follow an <RP>");
                        had_rp = had_rt = false;
                        break; }
    if (! is_whatwg)
        if (had_rt != had_rp)
            pick (nit_no_rp, ed_51, "4.5.10 The ruby element", es_error, ec_element, "<RP> should immediately precede OR follow <RT> and/or <RTC>"); }
