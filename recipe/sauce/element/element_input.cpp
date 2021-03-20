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

template < e_type T > void element::val_min_max (const bool cyclic)
{   type_master < T > t;
    typename type_master < T > :: value_type val (t.default_value ()), n (t.default_value ()), x (t.default_value ());
    bool val_known = false, min_known = false, max_known = false;
    if (a_.known (a_value))
    {   t.set_value (nits (), node_.version (), a_.get_string (a_value));
        if (t.good ())
        {   val_known = true;
            val = t.get (); } }
    if (a_.known (a_min))
    {   t.set_value (nits (), node_.version (), a_.get_string (a_min));
        if (t.empty ()) pick (nit_illegal_value, es_error, ec_attribute, "MIN cannot be empty");
        else if (t.good ())
        {   min_known = true;
            n = t.get (); } }
    if (a_.known (a_max))
    {   t.set_value (nits (), node_.version (), a_.get_string (a_max));
        if (t.empty ()) pick (nit_illegal_value, es_error, ec_attribute, "MAX cannot be empty");
        else if (t.good ())
        {   max_known = true;
            x = t.get (); } }
    if (cyclic)
    {   if (min_known && max_known) if (n > x) pick (nit_minmax, ed_50, "4.10.5.3.7 The min & max attributes", es_info, ec_element, "MIN exceeds MAX?");
        if (val_known && max_known) if (val > x) pick (nit_minmax, ed_50, "4.10.5.3.7 The min & max attributes", es_info, ec_element, "VALUE exceeds MAX?");
        if (min_known && val_known) if (val < n) pick (nit_minmax, ed_50, "4.10.5.3.7 The min & max attributes", es_info, ec_element, "MIN exceeds VALUE?"); }
    else
    {   if (min_known && max_known) if (n > x) pick (nit_minmax, ed_50, "4.10.5.3.7 The min & max attributes", es_warning, ec_element, "MIN should be less than MAX");
        if (val_known && max_known) if (val > x) pick (nit_minmax, ed_50, "4.10.5.3.7 The min & max attributes", es_warning, ec_element, "VALUE should be less than MAX");
        if (min_known && val_known) if (val < n) pick (nit_minmax, ed_50, "4.10.5.3.7 The min & max attributes", es_warning, ec_element, "MIN should be less than VALUE"); } };

e_inputtype5 element::get_input_type () const
{   e_inputtype5 res = i5_text;
    if ((tag () == elem_input) && a_.known (a_type))
        res = static_cast < e_inputtype5 > (a_.type (a_type));
    return res; }

void element::examine_input ()
{   if (node_.version ().mjr () < 5) return;
    element* form_daddy = get_ancestor (elem_form);
    CONSTEXPR unsigned it_text_search = (1 << static_cast < unsigned > (i5_search)) + (1 << static_cast < unsigned > (i5_text));
    CONSTEXPR unsigned it_url_tel = (1 << static_cast < unsigned > (i5_tel)) + (1 << static_cast < unsigned > (i5_url));
    CONSTEXPR unsigned it_hidden = 1 << static_cast < unsigned > (i5_hidden);
    CONSTEXPR unsigned it_url = 1 << static_cast < unsigned > (i5_url);
    CONSTEXPR unsigned it_email = 1 << static_cast < unsigned > (i5_email);
    CONSTEXPR unsigned it_password = 1 << static_cast < unsigned > (i5_password);
    CONSTEXPR unsigned it_date_time = (1 << static_cast < unsigned > (i5_date)) + (1 << static_cast < unsigned > (i5_datetime)) + (1 << static_cast < unsigned > (i5_datetime_local)) +
                                      (1 << static_cast < unsigned > (i5_month)) + (1 << static_cast < unsigned > (i5_time)) + (1 << static_cast < unsigned > (i5_week));
    CONSTEXPR unsigned it_number = 1 << static_cast < unsigned > (i5_number);
    CONSTEXPR unsigned it_range = 1 << static_cast < unsigned > (i5_range);
    CONSTEXPR unsigned it_colour = 1 << static_cast < unsigned > (i5_colour);
    CONSTEXPR unsigned it_check_radio = (1 << static_cast < unsigned > (i5_checkbox)) + (1 << static_cast < unsigned > (i5_radio));
    CONSTEXPR unsigned it_file = 1 << static_cast < unsigned > (i5_file);
    CONSTEXPR unsigned it_submit = 1 << static_cast < unsigned > (i5_submit);
    CONSTEXPR unsigned it_image = 1 << static_cast < unsigned > (i5_image);
    e_inputtype5 i5 = get_input_type ();
    bool alt_known = a_.known (a_alt);
    bool alt_empty = trim_the_lot_off (a_.get_string (a_alt)).empty ();
    bool list_known = a_.known (a_list);
    bool src_known = a_.known (a_src);
    bool val_known = a_.known (a_value);
    switch (i5)
    {   case i5_button :
            break;
        case i5_checkbox :
            break;
        case i5_colour :
            if (val_known)
            {   ::std::string val (a_.get_string (a_value));
                type_master < t_colour > c;
                c.set_value (nits (), node_.version (), val); }
            break;
        case i5_date :
            val_min_max < t_just_date > ();
            break;
        case i5_datetime :
            val_min_max < t_datetime > ();
            break;
        case i5_datetime_local :
            val_min_max < t_datetime_local > ();
            break;
        case i5_email :
            if (val_known)
            {   ::std::string val (a_.get_string (a_value));
                if (val.find_first_of ("\x0A\x0D") != ::std::string::npos)
                    pick (nit_illegal_value, ed_50, "4.10.5.1.5 E-mail state", es_error, ec_attribute, "when <INPUT> TYPE is 'email', VALUE may not contain newline");
                else
                if (a_.known (a_multiple))
                {   type_master < t_emails > e;
                    e.set_value (nits (), node_.version (), val); }
                else if (val.find (','))
                    pick (nit_bad_email, ed_50, "4.10.5.1.5 E-mail state", es_error, ec_attribute, "when <INPUT> MULTIPLE is omitted, VALUE may only contain one email address, not a comma separated list" );
                else
                {   type_master < t_email > e;
                    e.set_value (nits (), node_.version (), val); } }
            break;
        case i5_file :
            if (a_.known (a_accept))
            {   type_master < t_inputaccept > ia;
                ia.set_value (nits (), node_.version (), a_.get_string (a_accept)); }
            break;
        case i5_hidden :
            if (compare_no_case (a_.get_string (a_name), "_charset_") && a_.known (a_value))
                pick (nit_illegal_value, ed_50, "4.10.5.1.1 Hidden state", es_error, ec_attribute, "when <INPUT> TYPE is 'hidden' and NAME is \"_charset_\", VALUE cannot be specified");
            if (a_.known (a_autofocus))
                pick (nit_bad_type_attribute,  es_info, ec_attribute, "Perhaps it's me, but I do suspect AUTOFOCUS is questionable when <INPUT> TYPE set to 'hidden'");
            break;
        case i5_image :
            if (! src_known)
                pick (nit_src_required, ed_50, "4.10.5.1.16 Image Button State", es_error, ec_element, "<INPUT> TYPE 'image' requires SRC");
            if (! alt_known)
                pick (nit_naughty_alt, ed_50, "4.10.5.1.16 Image Button State", es_error, ec_element, "<INPUT> TYPE 'image' requires ALT");
            else if (alt_empty)
                pick (nit_naughty_alt, ed_50, "4.10.5.1.16 Image Button State", es_error, ec_element, "<INPUT> TYPE 'image' requires that ALT is not empty");
            break;
        case i5_month :
            val_min_max < t_month > ();
            break;
        case i5_number :
            val_min_max < t_real > ();
            break;
        case i5_range :
            val_min_max < t_real > ();
            break;
        case i5_radio :
            if (form_daddy != nullptr) form_daddy -> radio_kids_.push_back (this);
            break;
        case i5_reset :
            break;
        case i5_search :
        case i5_text :
            if (a_.known (a_value))
                if (a_.get_string (a_value).find_first_of ("\x0A\x0D") != ::std::string::npos)
                    pick (nit_illegal_value, es_error, ec_attribute, "<INPUT> VALUE may not contain newline when TYPE is 'text' or 'search'");
            break;
        case i5_submit :
            break;
        case i5_tel :
            if (a_.known (a_value))
                if (a_.get_string (a_value).find_first_of ("\x0A\x0D") != ::std::string::npos)
                    pick (nit_illegal_value, es_error, ec_attribute, "<INPUT> VALUE may not contain newline when <INPUT> TYPE is 'tel'");
            break;
        case i5_password :
            if (a_.known (a_value))
                if (a_.get_string (a_value).find_first_of ("\x0A\x0D") != ::std::string::npos)
                    pick (nit_illegal_value, es_error, ec_attribute, "<INPUT> VALUE may not contain newline when <INPUT> TYPE is 'password'");
            break;
        case i5_time :
            val_min_max < t_just_time > (true);
            break;
        case i5_url :
            if (val_known)
            {   ::std::string val (a_.get_string (a_value));
                if (val.find_first_of ("\x0A\x0D") != ::std::string::npos)
                    pick (nit_illegal_value, ed_50, "4.10.5.1.4 URL state", es_error, ec_attribute, "when <INPUT> TYPE is 'url', VALUE may not contain newline");
                else
                {   url u (nits (), node_.version (), val);
                    if (! u.invalid () && ! u.empty ())
                        if (! u.has_absolute_path ())
                            pick (nit_relative_path, ed_50, "4.10.5.1.4 URL state", es_error, ec_attribute, "when <INPUT> TYPE is 'url', VALUE cannot be a relative URL"); } }
            break;
        case i5_week :
            val_min_max < t_week > ();
            break;
        default : break; }
    bool maxlen_known = a_.known (a_maxlength);
    bool minlen_known = a_.known (a_minlength);
    if (maxlen_known || minlen_known)
    {   ::std::size_t x = maxlen_known ? a_.get_int (a_maxlength) : 0;
        ::std::size_t n = minlen_known ? a_.get_int (a_minlength) : 0;
        ::std::size_t v = val_known ? a_.get_string (a_value).length () : 0;
        if (maxlen_known && minlen_known) if (n > x) pick (nit_minmax, ed_50, "4.10.5.3.1 The maxlength and minlength attributes", es_error, ec_attribute, "MINLENGTH (", n, ") should not exceed MAXLENGTH (", x, ")");
        if (maxlen_known && val_known) if (v > x) pick (nit_minmax, ed_50, "4.10.5.3.1 The maxlength and minlength attributes", es_error, ec_attribute, "VALUE length (", v, ") should not exceed MAXLENGTH (", x, ")");
        if (val_known && minlen_known) if (n > v) pick (nit_minmax, ed_50, "4.10.5.3.1 The maxlength and minlength attributes", es_error, ec_attribute, "MINLENGTH (", n, ") should not exceed VALUE length (", v, ")"); }
    if (a_.known (a_pattern))
        if (! a_.known (a_title) || a_.get_string (a_title).empty ())
            pick (nit_pattern, ed_50, "4.10.5.3.6 The pattern attribute", es_warning, ec_attribute, "use TITLE to describe the contraints of PATTERN");
    if (a_.known (a_placeholder))
    {   ::std::string val (a_.get_string (a_placeholder));
        if (val.find_first_of ("\x0A\x0D") != ::std::string::npos)
            pick (nit_illegal_value, ed_50, "4.10.5.3.10 The placeholder attribute", es_error, ec_attribute, "PLACEHOLDER may not contain a newline");
        if (val.length () > MAX_IDEAL_PLACEHOLDER_LENGTH)
            pick (nit_placeholder, ed_50, "4.10.5.3.10 The placeholder attribute", es_warning, ec_attribute, "PLACEHOLDER should have a *short* value"); }
    unsigned t = 1 << static_cast < unsigned > (i5);
    ::std::string n (a_.get_string (a_type));
    if (a_.known (a_accept) && ((t & it_file) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "ACCEPT is ignored by type ", quote (n));
    if (a_.known (a_alt) && ((t & it_image) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "ALT is ignored by type ", quote (n));
    if (a_.known (a_autocomplete))
        if (node_.version () < html_5_3)
        {   if ((t & (it_text_search | it_url_tel | it_email | it_password | it_date_time | it_number | it_range | it_colour)) == 0)
                pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "AUTOCOMPLETE is ignored by type ", quote (n)); }
        else if ((t & (it_hidden | it_text_search | it_url_tel | it_email | it_password | it_date_time | it_number | it_range | it_colour)) == 0)
            pick (nit_input_bad_mix, ed_53, "4.10.5 The input element", es_warning, ec_element, "AUTOCOMPLETE is ignored by type ", quote (n));
    if (a_.known (a_autocapitalise) && ((t & (it_text_search | it_url | it_email | it_password)) == 0))
        pick (nit_input_bad_mix, ed_53, "4.10.5 The input element", es_warning, ec_element, "AUTOCAPITALIZE (sic) is ignored by type ", quote (n));
    if (a_.known (a_capture) && ((t & it_check_radio) == 0))
        pick (nit_input_bad_mix, ed_53, "4.10.5 The input element", es_warning, ec_element, "CAPTURE is ignored by type ", quote (n));
    if (a_.known (a_checked) && ((t & it_check_radio) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "CHECKED is ignored by type ", quote (n));
    if (a_.known (a_dirname) && ((t & it_text_search) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "DIRNAME is ignored by type ", quote (n));
    if (   (a_.known (a_formaction) || a_.known (a_formenctype) ||  a_.known (a_formmethod) || a_.known (a_formnovalidate) || a_.known (a_formtarget) ||
            a_.known (a_action) || a_.known (a_enctype) ||  a_.known (a_method) || a_.known (a_novalidate) || a_.known (a_target)) &&
           ((t & (it_submit | it_image)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "all FORM... attributes are ignored by type ", quote (n));
    if (a_.known (a_height) && ((t & it_image) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "HEIGHT is ignored by type ", quote (n));
     if (a_.known (a_hidden) && ((t & it_hidden) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "HIDDEN is ignored by type ", quote (n));
   if (a_.known (a_inputmode) && ((t & (it_text_search | it_password)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "INPUTMODE is ignored by type ", quote (n));
    if (a_.known (a_list) && ((t & (it_text_search | it_url_tel | it_email | it_date_time | it_number | it_range | it_colour)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "LIST is ignored by type ", quote (n));
    if (a_.known (a_max) && ((t & (it_date_time | it_number | it_range)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "MAX is ignored by type ", quote (n));
    if (a_.known (a_maxlength) && ((t & (it_text_search | it_url_tel | it_email | it_password)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "MAXLENGTH is ignored by type ", quote (n));
    if (a_.known (a_min) && ((t & (it_date_time | it_number | it_range)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "MIN is ignored by type ", quote (n));
    if (a_.known (a_minlength) && ((t & (it_text_search | it_url_tel | it_email | it_password)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "MINLENGTH is ignored by type ", quote (n));
    if (a_.known (a_multiple) && ((t & (it_email | it_file)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "MULTIPLE is ignored by type ", quote (n));
    if (a_.known (a_pattern) && ((t & (it_text_search | it_url_tel | it_email | it_password)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "PATTERN is ignored by type ", quote (n));
    if (a_.known (a_placeholder) && ((t & (it_text_search | it_url_tel | it_email | it_password | it_number)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "PLACEHOLDER is ignored by type ", quote (n));
    if (a_.known (a_readonly) && ((t & (it_text_search | it_url_tel | it_email | it_password | it_date_time | it_number)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "READONLY is ignored by type ", quote (n));
    if (a_.known (a_required) && ((t & (it_text_search | it_url_tel | it_email | it_password | it_date_time | it_number | it_check_radio | it_file)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "REQUIRED is ignored by type ", quote (n));
    if (a_.known (a_size) && ((t & (it_text_search | it_url_tel | it_email | it_password)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "SIZE is ignored by type ", quote (n));
    if (a_.known (a_src) && ((t & it_image) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "SRC is ignored by type ", quote (n));
    if (a_.known (a_step) && ((t & (it_date_time | it_number | it_range)) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "STEP is ignored by type ", quote (n));
    if (a_.known (a_width) && ((t & it_image) == 0))
        pick (nit_input_bad_mix, ed_50, "4.10.5 The input element", es_warning, ec_element, "WIDTH is ignored by type ", quote (n));
    if (a_.known (a_role))
    {   e_aria_role r = static_cast < e_aria_role > (a_.get_int (a_role));
        // I considered using bitsets here, but decided they'd be a bugger to maintain. Having said that, I'm not sure this approach is that much better.
        switch (i5)
        {   case i5_button :
                switch (r)
                {   case role_button :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.18 Button state", es_error, ec_attribute, "when <INPUT> TYPE is 'button' do not set ROLE to 'button', it is the default");
                        break;
                    case role_link :
                    case role_radio :
                        break;
                    case role_menuitem :
                    case role_menuitemcheckbox :
                    case role_menuitemradio :
                        if (node_.version () == html_5_2) pick (nit_input_bad_aria, ed_52, "4.10.5.1.21 Button state", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'button'");
                        break;
                    case role_switch :
                        if (node_.version () == html_5_2) pick (nit_input_bad_aria, ed_50, "4.10.5.1.18 Button state", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'button'");
                        break;
                    case role_option :
                    case role_tab :
                        if (node_.version ().w3 ()) pick (nit_input_bad_aria, ed_50, "4.10.5.1.18 Button state", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'button'");
                        break;
                    default :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.18 Button state", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'button'");
                        break; }
                    break;
            case i5_checkbox :
                switch (r)
                {   case role_checkbox :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.12 Checkbox state", es_error, ec_attribute, "when <INPUT> TYPE is 'checkbox' do not set ROLE to 'checkbox', it is the default");
                        break;
                    case role_button :
                        if (node_.version () < html_5_3) pick (nit_input_bad_aria, ed_52, "4.10.5.1.12 Checkbox state", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'checkbox'");
                        break;
                    case role_menuitemcheckbox :
                        if (node_.version () == html_5_2) pick (nit_input_bad_aria, ed_52, "4.10.5.1.15 Checkbox state", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'checkbox'");
                        break;
                    case role_option :
                    case role_switch :
                        if (node_.version () < html_5_2) pick (nit_input_bad_aria, ed_52, "4.10.5.1.12 Checkbox state", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'checkbox'");
                        break;
                    default :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.12 Checkbox state", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'checkbox'");
                        break; }
                break;
            case i5_email :
            case i5_tel :
            case i5_url :
                switch (r)
                {   case role_textbox :
                        if ((node_.version () < html_5_2) || ! list_known) pick (nit_input_bad_aria, ed_50, "4.10.5.1.3 Telephone state", es_error, ec_attribute, "do not set ROLE to 'textbox', it is the default");
                        else pick (nit_input_bad_aria, ed_53, "4.10.5.1.3 Telephone state", es_error, ec_attribute, "invalid <INPUT> ROLE");
                        break;
                    case role_combobox :
                        if (node_.version () >= html_5_2)
                            if (list_known) pick (nit_input_bad_aria, ed_53, "4.10.5.1.3 Telephone state", es_error, ec_attribute, "do not set ROLE to 'combobox', it is the default");
                            else pick (nit_input_bad_aria, ed_53, "4.10.5.1.3 Telephone state", es_error, ec_attribute, "invalid <INPUT> ROLE'");
                        break;
                    default :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.3 Telephone state", es_error, ec_attribute, "invalid <INPUT> ROLE");
                        break; }
                break;
            case i5_image :
                if (! alt_known)
                {   pick (nit_input_bad_aria, ed_50, "4.10.5.1.16 Image Button", es_error, ec_attribute, "<INPUT> with TYPE 'image' can have no ROLE when ALT is erroneously omitted");
                    break; }
                if (alt_empty)
                {   if ((r != role_none) && (r != role_presentation))
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.16 Image Button", es_error, ec_attribute, "<INPUT> with TYPE 'image' cannot have that ROLE when ALT is erroneously empty");
                    break; }
                switch (r)
                {   case role_button :
                        if (node_.version ().w3 ()) pick (nit_input_bad_aria, ed_50, "4.10.5.1.16 Image Button", es_error, ec_attribute, "do not set <INPUT> ROLE to 'button' when TYPE is image, it is the default");
                        break;
                    case role_img :
                        if (node_.version ().whatwg ()) pick (nit_input_bad_aria, ed_ariaAug2020, "conformance requirements", es_error, ec_attribute, "do not set <INPUT> ROLE to 'img' when TYPE is image, it is the default");
                        break;
                    case role_link :
                    case role_radio :
                        break;
                    case role_menuitem :
                    case role_menuitemcheckbox :
                    case role_menuitemradio :
                        if (node_.version () == html_5_2) pick (nit_input_bad_aria, ed_53, "4.10.5.1.19 Image Button", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE image");
                        break;
                    case role_switch :
                        if (node_.version () < html_5_3) pick (nit_input_bad_aria, ed_50, "4.10.5.1.16 Image Button", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE image");
                        break;
                    case role_checkbox :
                    case role_option :
                    case role_progressbar :
                    case role_scrollbar :
                    case role_separator :
                    case role_slider :
                    case role_tab :
                    case role_treeitem :
                        if (node_.version ().w3 ()) pick (nit_input_bad_aria, ed_50, "4.10.5.1.16 Image Button", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE image");
                        break;
                    default :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.16 Image Button", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE image");
                        break; }
                break;
            case i5_password :
                switch (r)
                {   case role_textbox :
                        if (node_.version () < html_5_2)
                        {   pick (nit_input_bad_aria, ed_50, "4.10.5.1.6 Password state", es_error, ec_attribute, "do not set ROLE to 'textbox', it is the default");
                            break; }
                        // drop thru'
                    default :
                        pick (nit_input_bad_aria, ed_52, "4.10.5.1.6 Password state", es_error, ec_attribute, "invalid <INPUT> ROLE");
                        break; }
                break;
            case i5_number :
                switch (r)
                {   case role_spinbutton :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.9 Number state", es_error, ec_attribute, "do not set ROLE to 'spinbutton', it is the default");
                        break;
                    default :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.9 Number state", es_error, ec_attribute, "invalid <INPUT> ROLE");
                        break; }
                break;
            case i5_range :
                switch (r)
                {   case role_slider :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.10 Range state", es_error, ec_attribute, "do not set ROLE to 'slider', it is the default");
                        break;
                    default :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.10 Range state", es_error, ec_attribute, "invalid <INPUT> ROLE");
                        break; }
                break;
            case i5_radio :
                switch (r)
                {   case role_radio :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.13 Radio Button state", es_error, ec_attribute, "when <INPUT> TYPE is 'radio' do not set ROLE to 'radio', it is the default");
                        break;
                    case role_menuitemradio :
                        if (node_.version () == html_5_2)
                            pick (nit_input_bad_aria, ed_52, "4.10.5.1.13 Radio Button state", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'radio'");
                        break;
                    default :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.13 Radio Button state", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'radio'");
                        break; }
                break;
            case i5_reset :
            case i5_submit :
                switch (r)
                {   case role_button :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.15 Submit Button state", es_error, ec_attribute, "do not set ROLE to 'button', it is the default");
                        break;
                    default :
                        pick (nit_input_bad_aria, ed_50, "4.10.5.1.15 Submit Button state", es_error, ec_attribute, "invalid <INPUT> ROLE");
                        break; }
                break;
            case i5_search :
            case i5_text :
                switch (w3_minor_5 (node_.version ()))
                {   case 0 :
                    case 1 :
                        if (r == role_combobox) break;
                        if (r == role_textbox) pick (nit_input_bad_aria, ed_50, "4.10.5.1.2 Text (type=text) and State (type=search)", es_error, ec_attribute, "when <INPUT> TYPE is 'text'/'search' do not set ROLE to 'textbox', it is the default");
                        else pick (nit_input_bad_aria, ed_50, "4.10.5.1.2 Text (type=text) and State (type=search)", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'text'/'search'");
                        break;
                    case 2 :
                        if (r == role_textbox) break;
                        if ((i5 == i5_search) && (r == role_combobox)) pick (nit_input_bad_aria, ed_52, "4.10.5.1.2 Text (type=text) and State (type=search)", es_error, ec_attribute, "when <INPUT> TYPE is 'search' do not set ROLE to 'combobox', it is the default");
                        else pick (nit_input_bad_aria, ed_52, "4.10.5.1.2 Text (type=text) and State (type=search)", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'text'/'search'");
                        break;
                    case 3 :
                        switch (r)
                        {   case role_textbox :
                            case role_searchbox :
                                break;
                            case role_spinbutton :
                                if (! list_known) pick (nit_input_bad_aria, ed_53, "4.10.5.1.2 Text (type=text) and State (type=search)", es_error, ec_attribute, "when <INPUT> TYPE is 'text'/'search' do not set ROLE to 'spinbutton', it is the default");
                                else pick (nit_input_bad_aria, ed_53, "4.10.5.1.2 Text (type=text) and State (type=search)", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'search'");
                                break;
                            case role_combobox :
                                if (list_known) pick (nit_input_bad_aria, ed_53, "4.10.5.1.2 Text (type=text) and State (type=search)", es_error, ec_attribute, "when <INPUT> TYPE is 'text'/'search' do not set ROLE to 'combobox', it is the default");
                                else pick (nit_input_bad_aria, ed_53, "4.10.5.1.2 Text (type=text) and State (type=search)", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'text'/'search'");
                                break;
                            default :
                                pick (nit_input_bad_aria, ed_53, "4.10.5.1.2 Text (type=text) and State (type=search)", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'text'/'search'");
                                break; }
                        break;
                    case 4 :
                        if ((i5 == i5_text) && ! list_known)
                        switch (r)
                        {   case role_textbox :
                                pick (nit_input_bad_aria, ed_ariaAug2020, "conformance requirements", es_error, ec_attribute, "when <INPUT> TYPE is 'text' do not set ROLE to 'textbox', it is the default");
                                break;
                            case role_combobox :
                            case role_searchbox :
                            case role_spinbutton :
                                break;
                            default :
                                pick (nit_input_bad_aria, ed_ariaAug2020, "conformance requirements", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'text'");
                                break; }
                        else if (r == role_combobox)
                            pick (nit_input_bad_aria, ed_ariaAug2020, "conformance requirements", es_error, ec_attribute, "when <INPUT> TYPE is 'search' or 'text' do not set ROLE to 'combobox', it is the default");
                        else
                            pick (nit_input_bad_aria, ed_ariaAug2020, "conformance requirements", es_error, ec_attribute, "invalid <INPUT> ROLE for TYPE 'search'");
                        break;
                    default : assert (false); }
                break;
            default :
                pick (nit_input_bad_aria, ed_50, "4.10.5 The Input element", es_error, ec_attribute, "<INPUT> can have no ROLE with the specified TYPE");
                break; } } }

void element::validate_input_id ()
{   assert (a_.has (a_list));
    if (a_.good (a_list))
    {   ::std::string id = a_.get_string (a_list);
        if (get_ids ().has_id (id))
        {   e_element e = get_ids ().get_tag (id);
            if (e != elem_datalist) pick (nit_bad_datalist_id, ed_50, "4.10.5.3.9 The list attribute", es_error, ec_attribute, quote (id), " is not on a <DATALIST>");
            else
            {   uid_t tuid_first = 0, tuid_last = 0;
                if (family_uids (elem_form, tuid_first, tuid_last))
                {   uid_t uid = get_ids ().get_uid (id);
                    if ((uid < tuid_first) || (uid > tuid_last))
                        pick (nit_bad_datalist_id, ed_50, "4.10.5.3.9 The list attribute", es_error, ec_attribute, "id ", quote (id), " is on a different <FORM>"); } } } } }
