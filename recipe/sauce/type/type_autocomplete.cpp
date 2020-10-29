/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "type/type_autocomplete.h"
#include "element/element.h"

bool set_autocomplete_value (vaco_t& vaco, nitpick& nits, const html_version& v, const ::std::string& s)
{   vstr_t args (split_by_space (s));
    ::std::size_t len = args.size ();
    if (len == 0)
    {   nits.pick (nit_empty, ed_52, "4.10.18.7.1. ... the autocomplete attribute", es_error, ec_type, "AUTOCOMPLETE cannot be empty");
        return false; }
    bool allgood = true;
    vaco.resize (len);
    for (::std::size_t x = 0; x < len; ++x)
    {   const ::std::string& arg = args.at (x);
        type_master < t_autocomplete > t;
        nitpick knots;
        t.set_value (knots, v, arg);
        if (t.good ())
        {   nits.merge (knots); vaco.at (x) = t.get (); continue; }
        if ((args.at (x).length () > 8) && compare_no_case (arg.substr (0, 8), "section-"))
        {   if (x == 0)
            {   vaco.at (x) = aco_section; continue; }
            nits.pick (nit_bad_autocomplete, ed_52, "4.10.18.7.1. ... the autocomplete attribute", es_error, ec_type, quote (args.at (x)), " can only be the first AUTOCOMPLETE value"); }
        else nits.merge (knots);
        allgood = false; }
    if (! allgood) return false;
    ::std::size_t start = 0;
    if (len > 1)
        if (vaco.at (0) == aco_section)
            ++start;
    if (start < len + 1)
        if ((vaco.at (start) == aco_shipping) || (vaco.at (start) == aco_billing))
            ++start;
    switch (vaco.at (start))
    {   case aco_home :
        case aco_work :
        case aco_mobile :
        case aco_fax :
        case aco_pager :
            if (start + 1 == len)
            {   nits.pick (nit_bad_autocomplete, ed_52, "4.10.18.7.1. ... the autocomplete attribute", es_error, ec_type, quote (args.at (start)), " cannot be the last AUTOCOMPLETE value");
                break; }
            switch (vaco.at (start + 1))
            {   case aco_tel :
                case aco_tel_country_code :
                case aco_tel_national :
                case aco_tel_area_code :
                case aco_tel_local :
                case aco_tel_local_prefix :
                case aco_tel_local_suffix :
                case aco_tel_extension :
                case aco_email :
                case aco_impp :
                    return true;
                default :
                    nits.pick (nit_bad_autocomplete, ed_52, "4.10.18.7.1. ... the autocomplete attribute", es_error, ec_type, "AUTOCOMPLETE ", quote (args.at (start+1)), " cannot follow ", quote (args.at (start)));
                    break; }
            break;
        case aco_on :
        case aco_off :
            if (len == 1) return true;
            nits.pick (nit_solo, ed_52, "4.10.18.7.1. ... the autocomplete attribute", es_error, ec_type, "AUTOCOMPLETE ", quote (args.at (start)), " must be solo");
            break;
        default :
            if (len == start + 1) return true;
            nits.pick (nit_bad_autocomplete, ed_52, "4.10.18.7.1. ... the autocomplete attribute", es_error, ec_type, "AUTOCOMPLETE has too many values");
            break; }
    return false; }

bool invalid_autocomplete (nitpick& nits, const html_version& , const element* e, const vaco_t& vaco)
{   assert (e != nullptr);
    switch (e -> tag ())
    {   case elem_textarea :
        case elem_select :
            return true;
        case elem_input :
            break;
        default :
            assert (false);
            nits.pick (nit_snafu, ed_52, "4.10.18.7.1. ... the autocomplete attribute", es_error, ec_type, "internal error: AUTOCOMPLETE is on the wrong element!");
            return false; }
    e_inputtype5 i5 = e -> get_input_type ();
    bool res = true;
    for (auto aco : vaco)
    {   switch (aco)
        {   case aco_new_password :
            case aco_current_password :
            case aco_one_time_code :
                switch (i5)
                {   case i5_text :
                    case i5_search :
                    case i5_password :
                    case i5_hidden :
                        break;
                    default :
                        res = false;
                        break; }
                break;
            case aco_street_address :
                    if (i5 != i5_hidden) res = false;
                    break;
            case aco_cc_exp :
                switch (i5)
                {   case i5_text :
                    case i5_search :
                    case i5_month :
                    case i5_hidden :
                        break;
                    default :
                        res = false;
                        break; }
                break;
            case aco_bday_day :
            case aco_bday_month :
            case aco_bday_year :
            case aco_cc_exp_month :
            case aco_cc_exp_year :
            case aco_transaction_amount :
                switch (i5)
                {   case i5_text :
                    case i5_search :
                    case i5_number :
                    case i5_hidden :
                       break;
                    default :
                        res = false;
                        break; }
                break;
            case aco_bday :
                switch (i5)
                {   case i5_text :
                    case i5_search :
                    case i5_date :
                    case i5_hidden :
                       break;
                    default :
                        res = false;
                        break; }
                break;
            case aco_impp :
            case aco_photo :
            case aco_url :
                switch (i5)
                {   case i5_text :
                    case i5_search :
                    case i5_url :
                    case i5_hidden :
                        break;
                    default :
                        res = false;
                        break; }
                break;
            case aco_tel :
                switch (i5)
                {   case i5_text :
                    case i5_search :
                    case i5_tel :
                    case i5_hidden :
                        break;
                    default :
                        res = false;
                        break; }
                break;
            case aco_email :
                switch (i5)
                {   case i5_text :
                    case i5_search :
                    case i5_email :
                    case i5_hidden :
                        break;
                    default :
                        res = false;
                        break; }
                break;
            case aco_on :
            case aco_off :
                if (i5 == i5_hidden) res = false;
                break;
            case aco_home :
            case aco_work :
            case aco_mobile :
            case aco_fax :
            case aco_pager :
            case aco_shipping :
            case aco_billing :
            case aco_section :
                break;
            default :
                switch (i5)
                {   case i5_text :
                    case i5_search :
                    case i5_hidden :
                        break;
                    default :
                        res = false;
                        break; } }
        if (! res)
            nits.pick (nit_bad_autocomplete, ed_52, "4.10.18.7.1. ... the autocomplete attribute", es_error, ec_type,
                "AUTOCOMPLETE ", quote (type_master < t_autocomplete > :: name (aco)), " doesn't work with TYPE ", quote (type_master < t_inputtype5 > :: name (i5))); }
    return res; }
