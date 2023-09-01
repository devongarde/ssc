/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "type/type.h"
#include "css/flags.h"


struct symbol_entry < html_version, e_accrual_method > accrual_method_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:deposit", am_deposit },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:donation", am_donation },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:purchase", am_purchase },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:loan", am_loan },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:license", am_licence },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accmeth:itemcreation", am_item_creation },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/deposit", am_deposit },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/donation", am_donation },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/purchase", am_purchase },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/loan", am_loan },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/license", am_licence },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accmeth/itemcreation", am_item_creation } };

struct symbol_entry < html_version, e_accrual_periodicity > accrual_periodicity_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "freq:triennial", ap_triennial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:biennial", ap_biennial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:annual", ap_annual },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:semiannual", ap_semiannual },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:threeTimesAYear", ap_thriceyearly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:quarterly", ap_quarterly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:bimonthly", ap_bimonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:monthly", ap_monthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:semimonthly", ap_semimonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:biweekly", ap_biweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:threeTimesAMonth", ap_thricemonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:weekly", ap_weekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:semiweekly", ap_semiweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:threeTimesAWeek", ap_thriceweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:daily", ap_daily },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:continuous", ap_continuous },
    { { XHTML_1_0 }, { HTML_UNDEF }, "freq:irregular", ap_irregular },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/triennial", ap_triennial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/biennial", ap_biennial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/annual", ap_annual },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/semiannual", ap_semiannual },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/threeTimesAYear", ap_thriceyearly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/quarterly", ap_quarterly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/bimonthly", ap_bimonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/monthly", ap_monthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/semimonthly", ap_semimonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/biweekly", ap_biweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/threeTimesAMonth", ap_thricemonthly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/weekly", ap_weekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/semiweekly", ap_semiweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/threeTimesAWeek", ap_thriceweekly },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/daily", ap_daily },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/continuous", ap_continuous },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/freq/irregular", ap_irregular } };

struct symbol_entry < html_version, e_accrual_policy > accrual_policy_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "accpol:closed", ap_closed },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accpol:passive", ap_active },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accpol:active", ap_passive },
    { { XHTML_1_0 }, { HTML_UNDEF }, "accpol:partial", ap_partial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accpol/closed", ap_closed },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accpol/passive", ap_active },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accpol/active", ap_passive },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/cld/accpol/partial ", ap_partial } };

struct symbol_entry < html_version, e_action > action_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "sell", av_sell },
    { { HTML_UNDEF }, { HTML_UNDEF }, "rent", av_rent },
    { { HTML_UNDEF }, { HTML_UNDEF }, "trade", av_trade },
    { { HTML_UNDEF }, { HTML_UNDEF }, "meet", av_meet },
    { { HTML_UNDEF }, { HTML_UNDEF }, "announce", av_announce },
    { { HTML_UNDEF }, { HTML_UNDEF }, "offer", av_offer },
    { { HTML_UNDEF }, { HTML_UNDEF }, "wanted", av_wanted },
    { { HTML_UNDEF }, { HTML_UNDEF }, "event", av_event },
    { { HTML_UNDEF }, { HTML_UNDEF }, "service", av_service } };

struct symbol_entry < html_version, e_align3 > align3_symbol_table [] =
{   { { HTML_3_0 }, { HTML_UNDEF }, "top", a3_top },
    { { HTML_3_0 }, { HTML_UNDEF }, "middle", a3_middle },
    { { HTML_3_0 }, { HTML_UNDEF }, "bottom", a3_bottom },
    { { HTML_3_0 }, { HTML_UNDEF }, "left", a3_left },
    { { HTML_3_0 }, { HTML_UNDEF }, "right", a3_right } };

struct symbol_entry < html_version, e_alignment_baseline > alignment_baseline_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "after-edge", ab_afteredge },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "alphabetic", ab_alphabetic },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "auto",  ab_auto },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "baseline", ab_baseline },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "before-edge", ab_beforeedge },
    { { HTML_SVG10, 0, HE_SVG_10 | HE_SVG_DEPR_10 }, { HTML_UNDEF }, "bottom", ab_bottom },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, "central", ab_central },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "hanging", ab_hanging },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "ideographic", ab_ideographic },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, "inherit", ab_inherit },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "mathematical", ab_mathematical },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "middle", ab_middle },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "text-after-edge", ab_textafteredge },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20 }, { HTML_UNDEF }, "text-before-edge", ab_textbeforeedge },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "text-bottom", ab_textbottom },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "text-top", ab_texttop },
    { { HTML_SVG10, 0, HE_SVG_10 | HE_SVG_DEPR_10 }, { HTML_UNDEF }, "top", ab_top } };

struct symbol_entry < html_version, e_alignplus > alignplus_symbol_table [] =
{   { { HTML_PLUS }, { HTML_PLUS }, "center", ap_centre },
    { { HTML_PLUS }, { HTML_PLUS }, "indent", ap_indent },
    { { HTML_PLUS }, { HTML_PLUS }, "justify", ap_justify },
    { { HTML_PLUS }, { HTML_PLUS }, "left", ap_left },
    { { HTML_PLUS }, { HTML_PLUS }, "right", ap_right } };

struct symbol_entry < html_version, e_as > as_symbol_table [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, "audio", as_audio },
    { { HTML_JAN05 }, { HTML_UNDEF }, "document", as_document },
    { { HTML_JAN05 }, { HTML_UNDEF }, "embed", as_embed },
    { { HTML_JAN05 }, { HTML_UNDEF }, "fetch", as_fetch },
    { { HTML_JAN05 }, { HTML_UNDEF }, "font", as_font },
    { { HTML_JAN05 }, { HTML_UNDEF }, "image", as_image },
    { { HTML_JAN05 }, { HTML_UNDEF }, "object", as_object },
    { { HTML_JAN05 }, { HTML_UNDEF }, "script", as_script },
    { { HTML_JAN05 }, { HTML_UNDEF }, "style", as_style },
    { { HTML_JAN05 }, { HTML_UNDEF }, "track", as_track },
    { { HTML_JAN05 }, { HTML_UNDEF }, "video", as_video },
    { { HTML_JAN05 }, { HTML_UNDEF }, "worker", as_worker } };

struct symbol_entry < html_version, e_as_units > as_units_symbol_table [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, "cm", asu_cm },
    { { HTML_JAN05 }, { HTML_UNDEF }, "feet", asu_feet },
    { { HTML_JAN05 }, { HTML_UNDEF }, "asu_inches", asu_inches },
    { { HTML_JAN05 }, { HTML_UNDEF }, "km", asu_km },
    { { HTML_JAN05 }, { HTML_UNDEF }, "m", asu_m },
    { { HTML_JAN05 }, { HTML_UNDEF }, "miles", asu_miles } };

struct symbol_entry < html_version, e_autocapitalise > autocapitalise_symbol_table [] =
{   { { HTML_5_3 }, { HTML_UNDEF }, "characters", ac4_characters },
    { { HTML_JUL20 }, { HTML_UNDEF }, "default", ec4_default },
    { { HTML_JUL20 }, { HTML_UNDEF }, "none", ac4_none },
    { { HTML_5_3 }, { HTML_UNDEF }, "sentences", ac4_sentences },
    { { HTML_5_3 }, { HTML_UNDEF }, "words", ac4_words } };

struct symbol_entry < html_version, e_autocomplete > autocomplete_symbol_table [] =
{   { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "additional-name", aco_additional_name },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-level1", aco_address_level1 },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-level2", aco_address_level2 },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-level3", aco_address_level3 },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-level4", aco_address_level4 },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-line1", aco_address_line1 },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-line2", aco_address_line2 },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "address-line3", aco_address_line3 },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "bday", aco_bday },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "bday-day", aco_bday_day },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "bday-month", aco_bday_month },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "bday-year", aco_bday_year },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "billing", aco_billing },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-additional-name", aco_cc_additional_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-csc", aco_cc_csc },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-exp", aco_cc_exp },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-exp-month", aco_cc_exp_month },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-exp-year", aco_cc_exp_year },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-family-name", aco_cc_family_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-given-name", aco_cc_given_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-name", aco_cc_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-number", aco_cc_number },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "cc-type", aco_cc_type },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "country", aco_country },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "country-name", aco_country_name },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "current-password", aco_current_password },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "email", aco_email },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "family-name", aco_family_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "fax", aco_fax },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "given-name", aco_given_name },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "home", aco_home },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "honorific-prefix", aco_honorific_prefix },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "honorific-suffix", aco_honorific_suffix },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "impp", aco_impp },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "language", aco_language },
    { { HTML_JAN13 }, { HTML_DEC14 }, "locality", aco_locality },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "mobile", aco_mobile },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "name", aco_name },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "new-password", aco_new_password },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "nickname", aco_nickname },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "off", aco_off },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "on", aco_on },
    { { HTML_JAN20 }, { HTML_UNDEF }, "one-time-code", aco_one_time_code },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "organization", aco_organization },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "organization-title", aco_organization_title },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "pager", aco_pager },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "photo", aco_photo },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "postal-code", aco_postal_code },
    { { HTML_JAN13 }, { HTML_DEC14 }, "region", aco_region },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "sex", aco_sex },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "shipping", aco_shipping },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "street-address", aco_street_address },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel", aco_tel },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-area-code", aco_tel_area_code },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-country-code", aco_tel_country_code },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-extension", aco_tel_extension },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-local", aco_tel_local },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-local-prefix", aco_tel_local_prefix },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-local-suffix", aco_tel_local_suffix },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "tel-national", aco_tel_national },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "transaction-amount", aco_transaction_amount },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "transaction-currency", aco_transaction_currency },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "url", aco_url },
    { { HTML_JAN15, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "username", aco_username },
    { { HTML_JAN13, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "work", aco_work } };

struct symbol_entry < html_version, e_baselineshift > baselineshift_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "baseline", bsb_baseline },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "bottom", bsb_bottom },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "center", bsb_centre },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "top", bsb_top },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "sub", bsb_sub },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "super", bsb_super },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", bsb_inherit } };

struct symbol_entry < html_version, e_cachekey > cachekey_symbol_table [] =
{   { { HTML_JAN15 }, { HTML_UNDEF }, "max-age", ck_maxage },
    { { HTML_JAN15 }, { HTML_UNDEF }, "max-stale", ck_maxstale },
    { { HTML_JAN15 }, { HTML_UNDEF }, "min-fresh", ck_minfresh },
    { { HTML_JAN15 }, { HTML_UNDEF }, "no-cache", ck_nocache },
    { { HTML_JAN15 }, { HTML_UNDEF }, "no-store", ck_nostore },
    { { HTML_JAN15 }, { HTML_UNDEF }, "no-transform", ck_notransform },
    { { HTML_JAN15 }, { HTML_UNDEF }, "only-if-cached", ck_onlyifcached } };

struct symbol_entry < html_version, e_citype > citype_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "integer", ci_integer },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rational", ci_rational },
    { { XHTML_1_0 }, { HTML_UNDEF }, "real", ci_real },
    { { XHTML_1_0 }, { HTML_UNDEF }, "complex-polar", ci_complexpolar },
    { { XHTML_1_0 }, { HTML_UNDEF }, "complex-cartesian", ci_complexcartesian },
    { { XHTML_1_0 }, { HTML_UNDEF }, "constant", ci_constant },
    { { HTML_5_2 }, { HTML_UNDEF }, "complex", ci_complex },
    { { HTML_5_2 }, { HTML_UNDEF }, "function", ci_function },
    { { HTML_5_2 }, { HTML_UNDEF }, "vector", ci_vector },
    { { HTML_5_2 }, { HTML_UNDEF }, "list", ci_list },
    { { HTML_5_2 }, { HTML_UNDEF }, "set", ci_set },
    { { HTML_5_2 }, { HTML_UNDEF }, "matrix", ci_matrix } };

struct symbol_entry < html_version, e_colour_interpolation > colour_interpolation_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "auto", ci_auto },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "sRGB", ci_srgb },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "linearRGB", ci_linearrgb },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", ci_inherit } };

struct symbol_entry < html_version, e_colour_rendering > colour_rendering_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "auto", cr_auto },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeSpeed", cr_optimisespeed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimiseQuality", cr_optimisequality },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", cr_inherit } };

struct symbol_entry < html_version, e_cookieid > cookieid_symbol_table [] =
{   { { HTML_JAN15 }, { HTML_UNDEF }, "expires", coo_expires },
    { { HTML_JAN15 }, { HTML_UNDEF }, "max-age", coo_maxage },
    { { HTML_JAN15 }, { HTML_UNDEF }, "domain", coo_domain },
    { { HTML_JAN15 }, { HTML_UNDEF }, "path", coo_path },
    { { HTML_JAN15 }, { HTML_UNDEF }, "secure", coo_secure },
    { { HTML_JAN15 }, { HTML_UNDEF }, "httponly", coo_httponly } };

struct symbol_entry < html_version, e_comp_op > comp_op_symbol_table [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "clear",  cop_clear },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "src", cop_src },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "dst", cop_dst },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "src-over", cop_src_over },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "dst-over", cop_dst_over },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "src-in", cop_src_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "dst-in", cop_dst_in },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "src-out", cop_src_out },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "dst-out", cop_dst_out },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "src-atop", cop_src_atop },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "dst-atop", cop_dst_atop },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "xor", cop_xor },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "plus", cop_plus },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "multiply", cop_multiply },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "screen", cop_screen },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "overlay", cop_overlay },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "darken", cop_darken },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "lighten", cop_lighten },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "color-dodge", cop_colour_dodge },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "color-burn", cop_colour_burn },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "hard-light", cop_hard_light },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "soft-light", cop_soft_light },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "difference", cop_difference },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "inherit", cop_inherit } };

struct symbol_entry < html_version, e_composite_operator > composite_operator_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "arithmetic",  co_arithmetic },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "atop", co_atop },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "in", co_in },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "lighter", co_lighter },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "out", co_out },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "over", co_over },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "xor", co_xor } };

struct symbol_entry < html_version, e_cntype > cntype_symbol_table [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, "double", cn_double },
    { { XHTML_1_0 }, { HTML_UNDEF }, "e-notation", cn_enotation },
    { { HTML_5_2 }, { HTML_UNDEF }, "hexdouble", cn_hexdouble },
    { { XHTML_1_0 }, { HTML_UNDEF }, "integer", cn_integer },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rational", cn_rational },
    { { XHTML_1_0 }, { HTML_UNDEF }, "real", cn_real },
    { { XHTML_1_0 }, { HTML_UNDEF }, "complex-polar", cn_complexpolar },
    { { XHTML_1_0 }, { HTML_UNDEF }, "complex-cartesian", cn_complexcartesian },
    { { XHTML_1_0 }, { HTML_UNDEF }, "constant", cn_constant } };

struct symbol_entry < html_version, e_crossout > crossout_symbol_table [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, "none", co_none },
    { { HTML_5_2 }, { HTML_UNDEF }, "updiagonalstrike", co_updiagonalstrike },
    { { HTML_5_2 }, { HTML_UNDEF }, "downdiagonalstrike", co_downdiagonalstrike },
    { { HTML_5_2 }, { HTML_UNDEF }, "verticalstrike", co_verticalstrike },
    { { HTML_5_2 }, { HTML_UNDEF }, "horizontalstrike", co_horizontalstrike } };

struct symbol_entry < html_version, e_css_aaalri > css_aaalri_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "always", caa_always },
    { { HTML_CSS }, { HTML_UNDEF }, "auto", caa_auto },
    { { HTML_CSS }, { HTML_UNDEF }, "avoid", caa_avoid },
    { { HTML_CSS }, { HTML_UNDEF }, "inherit", caa_inherit },
    { { HTML_CSS }, { HTML_UNDEF }, "left", caa_left },
    { { HTML_CSS }, { HTML_UNDEF }, "right", caa_right } };

struct symbol_entry < html_version, e_css_absolute_size > css_absolute_size_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecas_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "xx-small", eca_xx_small },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "x-small", eca_x_small },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "small", eca_small },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "medium", eca_medium },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "large", eca_large },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "x-large", eca_x_large },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "xx-large", eca_xx_large },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "xxx-large", eca_xxx_large } };

struct symbol_entry < html_version, e_css_align_content > css_align_content_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "baseline", ecac_baseline },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "center", ecac_centre },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "flex-end", ecac_flex_end },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "flex-start", ecac_flex_start },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "space-around", ecac_space_around },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "space-between", ecac_space_between },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "space-evenly", ecac_space_evenly },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "stretch", ecac_stretch } };

struct symbol_entry < html_version, e_css_align_items > css_align_items_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "baseline", ecai_baseline },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "center", ecai_centre },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "flex-end", ecai_flex_end },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "flex-start", ecai_flex_start },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "stretch", ecai_stretch } };

struct symbol_entry < html_version, e_css_appearance > css_appearance_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", eca_inherit },
    { { HTML_CSS }, { HTML_UNDEF }, "auto", eca_auto },
    { { HTML_CSS }, { HTML_UNDEF }, "button", eca_button },
    { { HTML_CSS }, { HTML_UNDEF }, "checkbox", eca_checkbox },
    { { HTML_CSS }, { HTML_UNDEF }, "listbox", eca_listbox },
    { { HTML_CSS }, { HTML_UNDEF }, "menulist", eca_menulist },
    { { HTML_CSS }, { HTML_UNDEF }, "menulist-button", eca_menulist_button },
    { { HTML_CSS }, { HTML_UNDEF }, "meter", eca_meter },
    { { HTML_CSS }, { HTML_UNDEF }, "none", eca_none },
    { { HTML_CSS }, { HTML_UNDEF }, "progress-bar", eca_progress_bar },
    { { HTML_CSS }, { HTML_UNDEF }, "push-button", eca_push_button },
    { { HTML_CSS }, { HTML_UNDEF }, "radio", eca_radio },
    { { HTML_CSS }, { HTML_UNDEF }, "searchfield", eca_searchfield },
    { { HTML_CSS }, { HTML_UNDEF }, "slider-horizontal", eca_slider_horizontal },
    { { HTML_CSS }, { HTML_UNDEF }, "square-button", eca_square_button },
    { { HTML_CSS }, { HTML_UNDEF }, "textarea", eca_textarea },
    { { HTML_CSS }, { HTML_UNDEF }, "textfield", eca_textfield } };

struct symbol_entry < html_version, e_css_azimuth_e > css_azimuth_e_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "center", cae_centre },
    { { HTML_CSS }, { HTML_UNDEF }, "center-left", cae_centre_left },
    { { HTML_CSS }, { HTML_UNDEF }, "center-right", cae_centre_right },
    { { HTML_CSS }, { HTML_UNDEF }, "far-left", cae_far_left },
    { { HTML_CSS }, { HTML_UNDEF }, "far-right", cae_far_right },
    { { HTML_CSS }, { HTML_UNDEF }, "left", cae_left },
    { { HTML_CSS }, { HTML_UNDEF }, "left-side", cae_left_side },
    { { HTML_CSS }, { HTML_UNDEF }, "right", cae_right },
    { { HTML_CSS }, { HTML_UNDEF }, "right-side", cae_right_side } };

struct symbol_entry < html_version, e_css_background_attachment > css_background_attachment_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecba_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "fixed", ecba_fixed },
    { { HTML_CSS, 0, 0, H2_CSS_BACKGROUND }, { HTML_UNDEF }, "local", ecba_local },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "scroll", ecba_scroll } };

struct symbol_entry < html_version, e_css_background_repeat > css_background_repeat_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecbr_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "no-repeat", ecbr_no_repeat },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "repeat", ecbr_repeat },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "repeat-x", ecbr_repeat_x },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "repeat-y", ecbr_repeat_y },
    { { HTML_CSS, 0, 0, H2_CSS_BACKGROUND }, { HTML_UNDEF }, "round", ecbr_round },
    { { HTML_CSS, 0, 0, H2_CSS_BACKGROUND }, { HTML_UNDEF }, "space", ecbr_space } };

struct symbol_entry < html_version, e_css_blend_mode > css_blend_mode_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "colour", ecbm_colour },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "colour-burn", ecbm_colour_burn },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "colour-dodge", ecbm_colour_dodge },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "darken", ecbm_darken },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "difference", ecbm_difference },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "exclusion", ecbm_exclusion },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "hard-light", ecbm_hard_light },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "hue", ecbm_hue },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "lighten", ecbm_lighten },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "luminosity", ecbm_luminosity },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "multiply", ecbm_multiply },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "normal", ecbm_normal },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "overlay", ecbm_overlay },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "saturation", ecbm_saturation },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "screen", ecbm_screen },
    { { HTML_CSS, 0, 0, H2_CSS_COMPOSITING }, { HTML_UNDEF }, "soft-light", ecbm_soft_light } };

struct symbol_entry < html_version, e_css_border_style > css_border_style_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecbs_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "dashed", ecb_dashed },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "dotted", ecb_dotted },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "double", ecb_double },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "groove", ecb_groove },
    { { HTML_CSS }, { HTML_UNDEF }, "hidden", ecb_hidden },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "inset", ecb_inset },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecb_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "outset", ecb_outset },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "ridge", ecb_ridge },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "solid", ecb_solid } };

struct symbol_entry < html_version, e_css_border_width > css_border_width_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecb_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "medium", ecb_medium },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "thick", ecb_thick },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "thin", ecb_thin } };

struct symbol_entry < html_version, e_css_box_alignself_mess > css_box_alignself_mess_symbol_table [] =
{   { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "auto", ebam_auto },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "baseline", ebam_baseline },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "center", ebam_centre },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "flex-end", ebam_flex_end },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "flex-start", ebam_flex_start },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "normal", ebam_normal },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "stretch", ebam_stretch } };

struct symbol_entry < html_version, e_css_break > css_break_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FRAG_4 }, { HTML_UNDEF }, "all", ecb_all },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_4 }, { HTML_UNDEF }, "always", ecb_always },
    { { HTML_CSS }, { HTML_UNDEF }, "auto", ecb_auto },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "avoid-column", ecb_avoid_column },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "avoid-page", ecb_avoid_page },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "avoid-region", ecb_avoid_region },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "column", ecb_column },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "left", ecb_left },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "page", ecb_page },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "region", ecb_region },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_4 }, { HTML_UNDEF }, "recto", ecb_recto },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "right", ecb_right },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "verso", ecb_verso } };

struct symbol_entry < html_version, e_css_break_inside > css_break_inside_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "auto", ecbi_auto },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "avoid", ecbi_avoid },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "avoid-column", ecbi_avoid_column },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "avoid-page", ecbi_avoid_page },
    { { HTML_CSS, 0, 0, H2_CSS_FRAG_3 }, { HTML_UNDEF }, "avoid-region", ecbi_avoid_region } };

struct symbol_entry < html_version, e_css_caret_shape > css_caret_shape_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "auto", ecsc_auto },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "bar", ecsc_bar },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "block", ecsc_block },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "inherit", ecsc_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "underscore", ecsc_underscore } };

struct symbol_entry < html_version, e_css_clear > css_clear_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecc_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "both", ecc_both },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "left", ecc_left },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecc_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "right", ecc_right } };

struct symbol_entry < html_version, e_css_content_enum > css_content_enum_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "attr", econ_attr },
    { { HTML_CSS }, { HTML_UNDEF }, "close-quote", econ_close_quote },
    { { HTML_CSS }, { HTML_UNDEF }, "counter", econ_counter },
    { { HTML_CSS }, { HTML_UNDEF }, "counters", econ_counters },
    { { HTML_CSS }, { HTML_UNDEF }, "inherit", econ_inherit },
    { { HTML_CSS }, { HTML_UNDEF }, "open-quote", econ_open_quote },
    { { HTML_CSS }, { HTML_UNDEF }, "no-close-quote", econ_no_close_quote },
    { { HTML_CSS }, { HTML_UNDEF }, "no-open-quote", econ_no_open_quote },
    { { HTML_CSS }, { HTML_UNDEF }, "url", econ_url } };

struct symbol_entry < html_version, e_css_content_position > css_content_position_symbol_table [] =
{   { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "center", eccp_centre },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "end", eccp_end },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "flex-end", eccp_flex_end },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "flex-start", eccp_flex_start },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "start", eccp_start } };

struct symbol_entry < html_version, e_css_coord_box > css_coord_box_symbol_table [] =
{   { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "border-box", eccb_border_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "content-box", eccb_content_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "fill-box", eccb_fill_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "padding-box", eccb_padding_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "stroke-box", eccb_stroke_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "view-box", eccb_view_box } };

struct symbol_entry < html_version, e_css_counter_style > css_counter_style_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "arabic-indic", eccs_arabic_indic, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "armenian", eccs_armenian, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "bengali", eccs_bengali, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "cambodian", eccs_cambodian, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "circle", eccs_circle, ns_default, CF_CS_PREDEFINED | CF_CS_NAUGHTY },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "cjk-decimal", eccs_cjk_decimal, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "cjk-earthly-branch", eccs_cjk_earthly_branch, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "cjk-heavenly-stem", eccs_cjk_heavenly_stem, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "decimal", eccs_decimal, ns_default, CF_CS_PREDEFINED | CF_CS_NAUGHTY },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "decimal-leading-zero", eccs_decimal_leading_zero, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "devanagari", eccs_devanagari, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "disc", eccs_disc, ns_default, CF_CS_PREDEFINED | CF_CS_NAUGHTY },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "disclosure-closed", eccs_disclosure_closed, ns_default, CF_CS_PREDEFINED | CF_CS_NAUGHTY },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "disclosure-open", eccs_disclosure_open, ns_default, CF_CS_PREDEFINED | CF_CS_NAUGHTY },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "ethiopic-numeric", eccs_ethiopic_numeric, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "georgian", eccs_georgian, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "gujarati", eccs_gujarati, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "gurmukhi", eccs_gurmukhi, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "hebrew", eccs_hebrew, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "hiragana", eccs_hiragana, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "hiragana-iroha", eccs_hiragana_iroha, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "inherit", eccs_inherit, ns_default, CF_CS_CASCADE },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "initial", eccs_initial, ns_default, CF_CS_CASCADE },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "japanese-formal", eccs_japanese_formal, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "japanese-informal", eccs_japanese_informal, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "kannada", eccs_kannada, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "katakana", eccs_katakana, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "katakana-iroha", eccs_katakana_iroha, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "khmer", eccs_khmer, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "korean-hangul-formal", eccs_korean_hangul_formal, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "korean-hanja-formal", eccs_korean_hanja_formal, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "korean-hanja-informal", eccs_korean_hanja_informal, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "lao", eccs_lao, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "lower-alpha", eccs_lower_alpha, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "lower-armenian", eccs_lower_armenian, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "lower-greek", eccs_lower_greek, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "lower-latin", eccs_lower_latin, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "lower-roman", eccs_lower_roman, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "malayalam", eccs_malayalam, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "mongolian", eccs_mongolian, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "myanmar", eccs_myanmar, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "oriya", eccs_oriya, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "persian", eccs_persian, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "revert", eccs_revert, ns_default, CF_CS_CASCADE },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "revert-layer", eccs_revert_layer, ns_default, CF_CS_CASCADE },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "simp-chinese-formal", eccs_simp_chinese_formal, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "simp-chinese-informal", eccs_simp_chinese_informal, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "square", eccs_square, ns_default, CF_CS_PREDEFINED | CF_CS_NAUGHTY },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "tamil", eccs_tamil, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "telugu", eccs_telugu, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "thai", eccs_thai, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "tibetan", eccs_tibetan, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "trad-chinese-formal", eccs_trad_chinese_formal, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "trad-chinese-informal", eccs_trad_chinese_informal, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "unset", eccs_unset, ns_default, CF_CS_CASCADE },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "upper-alpha", eccs_upper_alpha, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "upper-armenian", eccs_upper_armenian, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "upper-latin", eccs_upper_latin, ns_default, CF_CS_PREDEFINED },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "upper-roman", eccs_upper_roman, ns_default, CF_CS_PREDEFINED } };

struct symbol_entry < html_version, e_css_cursor_e > css_cursor_e_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "alias", ece_alias },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "all-scroll", ece_all_scroll },
    { { HTML_CSS }, { HTML_UNDEF }, "auto", ece_auto },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "cell", ece_cell },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "context-menu", ece_context_menu },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "copy", ece_copy },
    { { HTML_CSS }, { HTML_UNDEF }, "crosshair", ece_crosshair },
    { { HTML_CSS }, { HTML_UNDEF }, "default", ece_default },
    { { HTML_CSS }, { HTML_UNDEF }, "e-resize", ece_e_resize },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "ew-resize", ece_ew_resize },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "grab", ece_grab },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "grabbing", ece_grabbing },
    { { HTML_CSS }, { HTML_UNDEF }, "help", ece_help },
    { { HTML_CSS }, { HTML_UNDEF }, "move", ece_move },
    { { HTML_CSS }, { HTML_UNDEF }, "n-resize", ece_n_resize },
    { { HTML_CSS }, { HTML_UNDEF }, "ne-resize", ece_ne_resize },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "nesw-resize", ece_nesw_resize },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "ns-resize", ece_ns_resize },
    { { HTML_CSS }, { HTML_UNDEF }, "nw-resize", ece_nw_resize },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "nwse-resize", ece_nwse_resize },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "no-drop", ece_no_drop },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "none", ece_none },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "not-allowed", ece_not_allowed },
    { { HTML_CSS }, { HTML_UNDEF }, "pointer", ece_pointer },
    { { HTML_CSS, 0, 0, H2_CSS_21_PLUS }, { HTML_UNDEF }, "progress", ece_progress },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "resize", ece_resize },
    { { HTML_CSS }, { HTML_UNDEF }, "s-resize", ece_s_resize },
    { { HTML_CSS }, { HTML_UNDEF }, "se-resize", ece_se_resize },
    { { HTML_CSS }, { HTML_UNDEF }, "sw-resize", ece_sw_resize },
    { { HTML_CSS }, { HTML_UNDEF }, "text", ece_text },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "vertical-text", ece_vertical_text },
    { { HTML_CSS }, { HTML_UNDEF }, "w-resize", ece_w_resize },
    { { HTML_CSS }, { HTML_UNDEF }, "wait", ece_wait },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "zoom-in", ece_zoom_in },
    { { HTML_CSS, 0, 0, H2_CSS_UI_3 }, { HTML_UNDEF }, "zoom-out", ece_zoom_out } };

struct symbol_entry < html_version, e_css_display > css_display_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "block", ecd_block },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "compact", ecd_compact },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "flex", ecd_flex },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "flex-inline", ecd_flex_inline },
    { { HTML_CSS, 0, 0, 0, H3_CSS_GRID }, { HTML_UNDEF }, "grid", ecd_flex },
    { { HTML_CSS, 0, 0, 0, H3_CSS_GRID }, { HTML_UNDEF }, "grid-inline", ecd_flex_inline },
    { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecd_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "inline", ecd_inline },
    { { HTML_CSS, 0, 0, H2_CSS_21_PLUS }, { HTML_UNDEF }, "inline-block", ecd_inline_block },
    { { HTML_CSS }, { HTML_UNDEF }, "inline-table", ecd_inline_table },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "list-item", ecd_list_item },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "marker", ecd_marker },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecd_none },
    { { HTML_CSS }, { HTML_UNDEF }, "run-in", ecd_run_in },
    { { HTML_CSS }, { HTML_UNDEF }, "table", ecd_table },
    { { HTML_CSS }, { HTML_UNDEF }, "table-caption", ecd_table_caption },
    { { HTML_CSS }, { HTML_UNDEF }, "table-cell", ecd_table_cell },
    { { HTML_CSS }, { HTML_UNDEF }, "table-column", ecd_table_column },
    { { HTML_CSS }, { HTML_UNDEF }, "table-column-group", ecd_table_column_group },
    { { HTML_CSS }, { HTML_UNDEF }, "table-footer-group", ecd_table_footer_group },
    { { HTML_CSS }, { HTML_UNDEF }, "table-header-group", ecd_table_header_group },
    { { HTML_CSS }, { HTML_UNDEF }, "table-row", ecd_table_row },
    { { HTML_CSS }, { HTML_UNDEF }, "table-row-group", ecd_table_row_group } };

struct symbol_entry < html_version, e_css_display_inside > css_display_inside_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FBL_3, H3_CSS_DISPLAY }, { HTML_UNDEF }, "flex", ecdi_flex },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3, H3_CSS_DISPLAY }, { HTML_UNDEF }, "flex-inline", ecdi_flex_inline },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "flow", ecdi_flow },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "flow-root", ecdi_flow_root },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY | H3_CSS_GRID }, { HTML_UNDEF }, "grid", ecdi_grid },
    { { HTML_CSS, 0, 0, 0, H3_CSS_GRID }, { HTML_UNDEF }, "grid-inline", ecdi_grid_inline },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "ruby", ecdi_ruby },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "table", ecdi_table } };

struct symbol_entry < html_version, e_css_display_internal > css_display_internal_symbol_table [] =
{   { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "ruby-base", ecdi_ruby_base },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "ruby-base-container", ecdi_ruby_base_container },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "ruby-text", ecdi_ruby_text },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "text-container", ecdi_text_container },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "table-caption", ecdi_table_caption },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "table-cell", ecdi_table_cell },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "table-column", ecdi_table_column },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "table-column-group", ecdi_table_column_group },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "table-footer-group", ecdi_table_footer_group },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "table-header-group", ecdi_table_header_group },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "table-row", ecdi_table_row },
    { { HTML_CSS, 0, 0, 0, H3_CSS_DISPLAY }, { HTML_UNDEF }, "table-row-group", ecdi_table_row_group } };

struct symbol_entry < html_version, e_css_elevation_e > css_elevation_e_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "above", cee_above },
    { { HTML_CSS }, { HTML_UNDEF }, "below", cee_below },
    { { HTML_CSS }, { HTML_UNDEF }, "higher", cee_higher },
    { { HTML_CSS }, { HTML_UNDEF }, "inherit", cee_inherit },
    { { HTML_CSS }, { HTML_UNDEF }, "level", cee_level },
    { { HTML_CSS }, { HTML_UNDEF }, "lower", cee_lower } };

struct symbol_entry < html_version, e_css_float > css_float_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecf_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "left", ecf_left },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecf_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "right", ecf_right } };

struct symbol_entry < html_version, e_css_font_display > css_font_display_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "auto", ecfd_auto },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "block", ecfd_block },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "fallback", ecfd_fallback },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "optional", ecfd_optional },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "right", ecfd_swap } };

// https://learn.microsoft.com/lb-lu/typography/opentype/spec/featurelist
struct symbol_entry < html_version, e_css_font_feature > css_font_feature_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "aalt", ecff_aalt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "abvf", ecff_abvf },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "abvm", ecff_abvm },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "abvs", ecff_abvs },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "afrc", ecff_afrc },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "akhn", ecff_akhn },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "blwf", ecff_blwf },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "blwm", ecff_blwm },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "blws", ecff_blws },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "calt", ecff_calt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "case", ecff_case },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ccmp", ecff_ccmp },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cfar", ecff_cfar },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "chws", ecff_chws },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cjct", ecff_cjct },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "clig", ecff_clig },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cpct", ecff_cpct },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cpsp", ecff_cpsp },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cswh", ecff_cswh },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "curs", ecff_curs },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv01", ecff_cv01 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv02", ecff_cv02 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv03", ecff_cv03 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv04", ecff_cv04 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv05", ecff_cv05 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv06", ecff_cv06 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv07", ecff_cv07 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv08", ecff_cv08 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv09", ecff_cv09 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv10", ecff_cv10 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv11", ecff_cv11 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv12", ecff_cv12 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv13", ecff_cv13 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv14", ecff_cv14 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv15", ecff_cv15 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv16", ecff_cv16 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv17", ecff_cv17 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv18", ecff_cv18 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv19", ecff_cv19 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv20", ecff_cv20 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv21", ecff_cv21 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv22", ecff_cv22 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv23", ecff_cv23 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv24", ecff_cv24 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv25", ecff_cv25 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv26", ecff_cv26 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv27", ecff_cv27 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv28", ecff_cv28 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv29", ecff_cv29 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv30", ecff_cv30 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv31", ecff_cv31 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv32", ecff_cv32 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv33", ecff_cv33 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv34", ecff_cv34 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv35", ecff_cv35 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv36", ecff_cv36 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv37", ecff_cv37 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv38", ecff_cv38 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv39", ecff_cv39 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv40", ecff_cv40 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv41", ecff_cv41 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv42", ecff_cv42 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv43", ecff_cv43 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv44", ecff_cv44 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv45", ecff_cv45 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv46", ecff_cv46 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv47", ecff_cv47 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv48", ecff_cv48 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv49", ecff_cv49 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv50", ecff_cv50 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv51", ecff_cv51 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv52", ecff_cv52 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv53", ecff_cv53 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv54", ecff_cv54 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv55", ecff_cv55 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv56", ecff_cv56 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv57", ecff_cv57 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv58", ecff_cv58 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv59", ecff_cv59 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv60", ecff_cv60 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv61", ecff_cv61 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv62", ecff_cv62 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv63", ecff_cv63 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv64", ecff_cv64 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv65", ecff_cv65 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv66", ecff_cv66 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv67", ecff_cv67 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv68", ecff_cv68 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv69", ecff_cv69 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv70", ecff_cv70 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv71", ecff_cv71 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv72", ecff_cv72 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv73", ecff_cv73 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv74", ecff_cv74 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv75", ecff_cv75 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv76", ecff_cv76 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv77", ecff_cv77 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv78", ecff_cv78 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv79", ecff_cv79 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv80", ecff_cv80 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv81", ecff_cv81 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv82", ecff_cv82 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv83", ecff_cv83 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv84", ecff_cv84 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv85", ecff_cv85 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv86", ecff_cv86 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv87", ecff_cv87 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv88", ecff_cv88 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv89", ecff_cv89 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv90", ecff_cv90 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv91", ecff_cv91 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv92", ecff_cv92 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv93", ecff_cv93 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv94", ecff_cv94 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv95", ecff_cv95 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv96", ecff_cv96 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv97", ecff_cv97 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv98", ecff_cv98 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "cv99", ecff_cv99 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "c2pc", ecff_c2pc },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "c2sc", ecff_c2sc },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "dist", ecff_dist },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "dlig", ecff_dlig },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "dnom", ecff_dnom },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "dtls", ecff_dtls },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "expt", ecff_expt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "falt", ecff_falt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "fin2", ecff_fin2 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "fin3", ecff_fin3 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "fina", ecff_fina },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "flac", ecff_flac },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "frac", ecff_frac },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "fwid", ecff_fwid },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "half", ecff_half },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "haln", ecff_haln },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "halt", ecff_halt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "hist", ecff_hist },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "hkna", ecff_hkna },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "hlig", ecff_hlig },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "hngl", ecff_hngl },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "hojo", ecff_hojo },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "hwid", ecff_hwid },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "init", ecff_init },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "isol", ecff_isol },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ital", ecff_ital },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "jalt", ecff_jalt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "jp78", ecff_jp78 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "jp83", ecff_jp83 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "jp90", ecff_jp90 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "jp04", ecff_jp04 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "kern", ecff_kern },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "lfbd", ecff_lfbd },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "liga", ecff_liga },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ljmo", ecff_ljmo },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "lnum", ecff_lnum },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "locl", ecff_locl },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ltra", ecff_ltra },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ltrm", ecff_ltrm },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "mark", ecff_mark },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "med2", ecff_med2 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "medi", ecff_medi },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "mgrk", ecff_mgrk },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "mkmk", ecff_mkmk },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "mset", ecff_mset },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "nalt", ecff_nalt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "nlck", ecff_nlck },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "nukt", ecff_nukt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "numr", ecff_numr },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "onum", ecff_onum },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "opbd", ecff_opbd },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ordn", ecff_ordn },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ornm", ecff_ornm },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "palt", ecff_palt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "pcap", ecff_pcap },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "pkna", ecff_pkna },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "pnum", ecff_pnum },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "pref", ecff_pref },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "pres", ecff_pres },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "pstf", ecff_pstf },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "psts", ecff_psts },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "pwid", ecff_pwid },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "qwid", ecff_qwid },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "rand", ecff_rand },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "rclt", ecff_rclt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "rkrf", ecff_rkrf },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "rlig", ecff_rlig },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "rphf", ecff_rphf },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "rtbd", ecff_rtbd },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "rtla", ecff_rtla },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "rtlm", ecff_rtlm },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ruby", ecff_ruby },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "rvrn", ecff_rvrn },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "salt", ecff_salt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "sinf", ecff_sinf },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "size", ecff_size },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "smcp", ecff_smcp },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "smpl", ecff_smpl },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss01", ecff_ss01 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss02", ecff_ss02 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss03", ecff_ss03 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss04", ecff_ss04 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss05", ecff_ss05 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss06", ecff_ss06 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss07", ecff_ss07 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss08", ecff_ss08 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss09", ecff_ss09 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss10", ecff_ss10 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss11", ecff_ss11 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss12", ecff_ss12 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss13", ecff_ss13 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss14", ecff_ss14 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss15", ecff_ss15 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss16", ecff_ss16 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss17", ecff_ss17 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss18", ecff_ss18 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss19", ecff_ss19 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ss20", ecff_ss20 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "ssty", ecff_ssty },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "stch", ecff_stch },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "subs", ecff_subs },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "sups", ecff_sups },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "swsh", ecff_swsh },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "titl", ecff_titl },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "tjmo", ecff_tjmo },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "tnam", ecff_tnam },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "tnum", ecff_tnum },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "trad", ecff_trad },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "twid", ecff_twid },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "unic", ecff_unic },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "valt", ecff_valt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "vatu", ecff_vatu },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "vchw", ecff_vchw },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "vert", ecff_vert },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "vhal", ecff_vhal },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "vjmo", ecff_vjmo },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "vkna", ecff_vkna },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "vkrn", ecff_vkrn },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "vpal", ecff_vpal },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "vrt2", ecff_vrt2 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "vrtr", ecff_vrtr },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "zero", ecff_zero } };

struct symbol_entry < html_version, e_css_font_format > css_font_format_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FONT_5 }, { HTML_UNDEF }, "collection", ecff_collection },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 | H2_CSS_FONT }, { HTML_UNDEF }, "embedded-opentype", ecff_embedded_opentype },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "intellifont", ecff_intellifont },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 | H2_CSS_FONT }, { HTML_UNDEF }, "opentype", ecff_opentype },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "speedo", ecff_speedo },
    { { HTML_CSS, 0, 0, H2_CSS_FONT }, { HTML_UNDEF }, "svg", ecff_svg },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "truedoc-pfr", ecf_truedoc_pfr },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 | H2_CSS_FONT }, { HTML_UNDEF }, "truetype", ecff_truetype },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "truetype-gx", ecff_truetype_gx },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "type-1", ecff_type_1 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT }, { HTML_UNDEF }, "woff", ecff_woff },
    { { HTML_CSS, 0, 0, H2_CSS_FONT }, { HTML_UNDEF }, "woff2", ecff_woff2 } };

struct symbol_entry < html_version, e_css_font_size_adjust_e > css_font_size_adjust_e_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FONT_5 }, { HTML_UNDEF }, "cap-height", efsa_cap_height },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_5 }, { HTML_UNDEF }, "ch-width", efsa_ch_width },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_5 }, { HTML_UNDEF }, "ex-height", efsa_ex_height },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_5 }, { HTML_UNDEF }, "ic-height", efsa_ic_height },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_5 }, { HTML_UNDEF }, "ic-width", efsa_ic_width } };

struct symbol_entry < html_version, e_css_font_tech > css_font_tech_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "color-CBDT", ecft_colour_cbdt },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "color-COLRv0", ecft_colour_colrv0 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "color-COLRv1", ecft_colour_colrv1 },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "color-sbix", ecft_colour_sbix },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "color-SVG", ecft_colour_svg },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "feature-aat", ecft_feature_aat },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "feature-graphite", ecft_feature_graphite },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "feature-opentype", ecft_feature_opentype },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "incremental", ecft_incremental },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "palette", ecft_palette },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_45 }, { HTML_UNDEF }, "variations", ecft_variations } };

// https://learn.microsoft.com/lb-lu/typography/opentype/spec/fvar
// https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6fvar.html
struct symbol_entry < html_version, e_css_font_variation > css_font_variation_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "BASE", ecfv_base, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "CBDT", ecfv_cbdt, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "CBLC", ecfv_cblc, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "CFF", ecfv_cff, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "CFF2", ecfv_cff2, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "COLR", ecfv_colr, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "CPAL", ecfv_cpal, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "DSIG", ecfv_dsig, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "EBDT", ecfv_ebdt, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "EBLC", ecfv_eblc, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "EBSC", ecfv_ebsc, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "GDEF", ecfv_gdef, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "GPOS", ecfv_gpos, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "GSUB", ecfv_gsub, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "HVAR", ecfv_hvar, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "JSTF", ecfv_jstf, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "LTSH", ecfv_ltsh, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "MATH", ecfv_math, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "MERG", ecfv_merg, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "MVAR", ecfv_mvar, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "OS/2", ecfv_os_2, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "PCLT", ecfv_pclt, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "STAT", ecfv_stat, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "SVG", ecfv_svg, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "VDMX", ecfv_vdmx, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "VORG", ecfv_vorg, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "VVAR", ecfv_vvar, ns_default, CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "Zapf", ecfv_zapf, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "acnt", ecfv_acnt, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ankr", ecfv_ankr, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "avar", ecfv_avar, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "bdat", ecfv_bdat, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "bhed", ecfv_bhed, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "bloc", ecfv_bloc, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "bsln", ecfv_bsln, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "cmap", ecfv_cmap, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "cvar", ecfv_cvar, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "cvt", ecfv_cvt, ns_default, CF_TRUETYPE | CF_OPENTYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "fdsc", ecfv_fdsc, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "feat", ecfv_feat, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "fmtx", ecfv_fmtx, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "fond", ecfv_fond, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "fpgm", ecfv_fpgm, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "fvar", ecfv_fvar, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "gasp", ecfv_gasp, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "gcid", ecfv_gcid, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "glyf", ecfv_glyf, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "gvar", ecfv_gvar, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "hdmx", ecfv_hdmx, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "head", ecfv_head, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "hhea", ecfv_hhea, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "hmtx", ecfv_hmtx, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "just", ecfv_just, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "kern", ecfv_kern, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "kerx", ecfv_kerx, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "lcar", ecfv_lcar, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "loca", ecfv_loca, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ltag", ecfv_ltag, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "maxp", ecfv_maxp, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "meta", ecfv_meta, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "mort", ecfv_mort, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "morx", ecfv_morx, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "name", ecfv_name, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "opbd", ecfv_opbd, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "post", ecfv_post, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "prep", ecfv_prep, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "prop", ecfv_prop, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "sbix", ecfv_sbix, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "trak", ecfv_trak, ns_default, CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "vhea", ecfv_vhea, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "vmtx", ecfv_vmtx, ns_default, CF_OPENTYPE | CF_TRUETYPE },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "xref", ecfv_xref, ns_default, CF_TRUETYPE } };

struct symbol_entry < html_version, e_css_font_weight > css_font_weight_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "all",  ecfw_all },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "normal",  ecfw_normal },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "bold", ecfw_bold },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "bolder", ecfw_bolder },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "lighter", ecfw_lighter },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "100", ecfw_100 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "200", ecfw_200 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "300", ecfw_300 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "400", ecfw_400 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "500", ecfw_500 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "600", ecfw_600 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "700", ecfw_700 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "800", ecfw_800 },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "900", ecfw_900 },
    { { HTML_CSS, 0, 0, H2_CSS_2_PLUS }, { HTML_UNDEF }, "inherit", ecfw_inherit } };

struct symbol_entry < html_version, e_css_fn > css_fn_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "(unknown)", efn_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "active", efn_active },
    { { HTML_CSS, 0, 0, H2_CSS | H2_CSS_COCO }, { HTML_UNDEF }, "after", efn_after },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "any-link", efn_any_link },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "autofill", efn_autofill },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "backdrop", efn_backdrop },
    { { HTML_CSS, 0, 0, H2_CSS | H2_CSS_COCO }, { HTML_UNDEF }, "before", efn_before },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "blank", efn_blank },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "buffering", efn_buffering },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "checked", efn_checked },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "circle", efn_circle },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "closed", efn_closed, ns_default, CF_NOT_LV_STD_JUL23 },
    { { HTML_CSS, 0, 0, H2_CSS_EASE }, { HTML_UNDEF }, "cubic-bezier", efn_cubic_bezier },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "cue", efn_cue },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "cue-region", efn_cue_region },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 | H2_CSS_N_ARGS }, { HTML_UNDEF }, "current", efn_current },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "default", efn_default },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "defined", efn_defined },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "dir", efn_dir },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "disabled", efn_disabled },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "ellipse", efn_ellipse },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "empty", efn_empty },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "enabled", efn_enabled, },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "file-selector-button", efn_file_selector_button },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "first", efn_first, ns_default, CF_PAGE },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "first-child", efn_first_child },
    { { HTML_CSS, 0, 0, H2_CSS | H2_CSS_COCO }, { HTML_UNDEF }, "first-letter", efn_first_letter },
    { { HTML_CSS, 0, 0, H2_CSS | H2_CSS_COCO }, { HTML_UNDEF }, "first-line", efn_first_line },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "first-of-type", efn_first_of_type },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "focus", efn_focus },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "focus-visible", efn_focus_visible },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "focus-within", efn_focus_within },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "fullscreen", efn_fullscreen },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "future", efn_future },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "grammar-error", efn_grammar_error },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_N_ARGS }, { HTML_UNDEF }, "has", efn_has },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "host", efn_host },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "host-context", efn_host_context },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "hover", efn_hover, },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "indeterminate", efn_indeterminate },
    { { HTML_CSS, 0, 0, 0, H3_CSS_IMAGE }, { HTML_UNDEF }, "image", efn_image },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "in-range", efn_in_range },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "inset", efn_inset },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "invalid", efn_invalid },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_N_ARGS }, { HTML_UNDEF }, "is", efn_is },
    { { HTML_CSS, 0, 0, H2_CSS_1_2_ARGS }, { HTML_UNDEF }, "lang", efn_lang },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "last-child", efn_last_child },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "last-of-type", efn_last_of_type },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "left", efn_left, ns_default, CF_PAGE },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "link", efn_link },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "local-link", efn_local_link },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "marker", efn_marker },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "modal", efn_modal },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "muted", efn_muted },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_N_ARGS }, { HTML_UNDEF }, "not", efn_not },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-child", efn_nth_child },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-col", efn_nth_col, },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-last-child", efn_nth_last_child },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-last-col", efn_nth_last_col },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-last-of-type", efn_nth_last_of_type },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_1_ARG }, { HTML_UNDEF }, "nth-of-type", efn_nth_of_type },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "only-child", efn_only_child },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "only-of-type", efn_only_of_type },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "open", efn_open, ns_default, CF_NOT_LV_STD_JUL23 },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "optional", efn_optional },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "out-of-range", efn_out_of_range },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "paused", efn_paused },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "part", efn_part },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "past", efn_past },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "picture-in-picture", efn_picture_in_picture },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "placeholder", efn_placeholder },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "placeholder-shown", efn_placeholder_shown },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "playing", efn_playing },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "polygon", efn_polygon },
    { { HTML_JUL23, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "popover-open", efn_popover_open, ns_default, CF_LV_STD_JUL23 },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "read-only", efn_read_only },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "read-write", efn_read_write },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "required", efn_required },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "right", efn_right, ns_default, CF_PAGE },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "root", efn_root },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "scope", efn_scope },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "seeking", efn_seeking },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "selection", efn_selection },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "slotted", efn_slotted },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "spelling-error", efn_spelling_error },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "stalled", efn_stalled },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "state", efn_state },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "target", efn_target },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_COCO }, { HTML_UNDEF }, "target-text", efn_target_text },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "target-within", efn_target_within },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "user-invalid", efn_user_invalid, },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "user-valid", efn_user_valid, },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "valid", efn_valid },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "visited", efn_visited },
    { { HTML_CSS, 0, 0, H2_CSS_SELECTOR_4 }, { HTML_UNDEF }, "volume-locked", efn_volume_locked },
    { { HTML_CSS, 0, 0, H2_CSS_3 | H2_CSS_N_ARGS }, { HTML_UNDEF }, "where", efn_where },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "xywh", efn_xywh } };

struct symbol_entry < html_version, e_css_generic_family > css_generic_family_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecgf_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "cursive", ecf_cursive },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "emoji", ecf_emoji },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "fangsong", ecf_fangsong },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "fantasy", ecf_fantasy },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "math", ecf_math },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "monospace", ecf_monospace },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "sans-serif", ecf_sans_serif },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "serif", ecf_serif },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "system-ui", ecf_system_ui },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ui-monospace", ecf_ui_monospace },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ui-rounded", ecf_ui_rounded },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ui-sans-serif", ecf_ui_sans_serif },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ui-serif", ecf_ui_serif } };

struct symbol_entry < html_version, e_css_justify_content > css_justify_content_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "center", ejc_centre },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "flex-end", ejc_flex_end },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3 }, { HTML_UNDEF }, "flex-start", ejc_flex_start },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "space-around", ejc_space_around },
    { { HTML_CSS, 0, 0, H2_CSS_FBL_3, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "space-between", ejc_space_between },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "space-evenly", ejc_space_evenly },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "stretch", ejc_stretch } };

struct symbol_entry < html_version, e_css_layout_box > css_layout_box_symbol_table [] =
{   { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "border-box", eclb_border_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "content-box", eclb_content_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "margin-box", eclb_margin_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "padding-box", eclb_padding_box } };

struct symbol_entry < html_version, e_css_list_style_position > css_list_style_position_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", eclp_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "inside", ecp_inside },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "outside", ecp_outside } };

struct symbol_entry < html_version, e_css_list_style_type > css_list_style_type_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecls_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "circle", ecl_circle },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "decimal", ecl_decimal },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "disc", ecl_disc },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "lower-alpha", ecl_lower_alpha },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "lower-roman", ecl_lower_roman },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecl_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "square", ecl_square },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "upper-alpha", ecl_upper_alpha },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "upper-roman", ecl_upper_roman },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "hebrew", ecl_hebrew },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "armenian", ecl_armenian },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "georgian", ecl_georgian },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "cjk-ideographic", ecl_cjk_ideographic },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "hiragana", ecl_hiragana },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "katakana", ecl_katakana },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "hira-gana-iroha", ecl_hira_gana_iroha },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "katakana-iroha", ecl_katakana_iroha } };

struct symbol_entry < html_version, e_css_paint_box > css_paint_box_symbol_table [] =
{   { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "border-box", ecpb_border_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "content-box", ecpb_content_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "fill-box", ecpb_fill_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "padding-box", ecpb_padding_box },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_MODEL }, { HTML_UNDEF }, "stroke-box", ecpb_stroke_box } };

struct symbol_entry < html_version, e_css_overflow > css_overflow_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "auto", eco_auto },
    { { HTML_CSS }, { HTML_UNDEF }, "hidden", eco_hidden },
    { { HTML_CSS }, { HTML_UNDEF }, "inherit", eco_inherit },
    { { HTML_CSS }, { HTML_UNDEF }, "scroll", eco_scroll },
    { { HTML_CSS }, { HTML_UNDEF }, "visible", eco_visible } };

struct symbol_entry < html_version, e_css_pitch_e > css_pitch_e_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "high", epi_high },
    { { HTML_CSS }, { HTML_UNDEF }, "inherit", epi_inherit },
    { { HTML_CSS }, { HTML_UNDEF }, "low", epi_low },
    { { HTML_CSS }, { HTML_UNDEF }, "medium", epi_medium },
    { { HTML_CSS }, { HTML_UNDEF }, "x-high", epi_x_high },
    { { HTML_CSS }, { HTML_UNDEF }, "x-low", epi_x_low } };

struct symbol_entry < html_version, e_css_position > css_position_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "absolute", ecp_absolute },
    { { HTML_CSS }, { HTML_UNDEF }, "fixed", ecp_fixed },
    { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecp_inherit },
    { { HTML_CSS }, { HTML_UNDEF }, "relative", ecp_relative },
    { { HTML_CSS }, { HTML_UNDEF }, "static", ecp_static },
    { { HTML_CSS, 0, 0, 0, H3_CSS_POSITION }, { HTML_UNDEF }, "sticky", ecp_sticky } };

struct symbol_entry < html_version, e_css_rgb_xyz > css_rgb_xyz_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "a98-rgb", crx_a98_rgb },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "display-p3", crx_display_p3 },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "prophoto-rgb", crx_prophoto_rgb },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "rec2020", crx_rec2020 },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "srgb", crx_srgb },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "srgb-linear", crx_srgb_linear },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "xyz", crx_xyz },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "xyz-d50", crx_xyz_d50 },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "xyz-d65", crx_xyz_d65 } };

struct symbol_entry < html_version, e_css_rect > css_rect_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "lab", ec4_lab },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "oklab", ec4_oklab },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "srgb", ec4_srgb },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "srgb-linear", ec4_srgb_linear },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "xyz", ec4_xyz },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "xyz-d50", ec4_xyz_d50 },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "xyz-d65", ec4_xyz_d65 } };

struct symbol_entry < html_version, e_css_relative_size > css_relative_size_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecr_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "larger", ecr_larger },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "smaller", ecr_smaller } };

struct symbol_entry < html_version, e_css_resize > css_resize_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_UI_4 }, { HTML_UNDEF }, "block", ecz_block },
    { { HTML_CSS, 0, 0, H2_CSS_UI }, { HTML_UNDEF }, "both", ecz_both },
    { { HTML_CSS, 0, 0, H2_CSS_UI }, { HTML_UNDEF }, "horizontal", ecz_horizontal },
    { { HTML_CSS, 0, 0, H2_CSS_UI }, { HTML_UNDEF }, "inherit", ecz_inherit },
    { { HTML_CSS, 0, 0, H2_CSS_UI_4 }, { HTML_UNDEF }, "inline", ecz_inline },
    { { HTML_CSS, 0, 0, H2_CSS_UI }, { HTML_UNDEF }, "none", ecz_none },
    { { HTML_CSS, 0, 0, H2_CSS_UI }, { HTML_UNDEF }, "vertical", ecz_vertical } };

struct symbol_entry < html_version, e_css_self_position > css_self_position_symbol_table [] =
{   { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "center", ecsp_centre },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "end", ecsp_end },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "flex-end", ecsp_flex_end },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "flex-start", ecsp_flex_start },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "self-end", ecsp_self_end },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "self-start", ecsp_self_start },
    { { HTML_CSS, 0, 0, 0, H3_CSS_BOX_ALIGN | H3_CSS_GRID }, { HTML_UNDEF }, "start", ecsp_start } };

struct symbol_entry < html_version, e_css_speak_as_e > css_speak_as_e_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "auto", csae_auto },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "bullets", csae_bullets },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "numbers", csae_numbers },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "spell-out", csae_spell_out },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "words", csae_words } };

struct symbol_entry < html_version, e_css_speech_rate_e > css_speech_rate_e_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "fast", esr_fast },
    { { HTML_CSS }, { HTML_UNDEF }, "faster", esr_faster },
    { { HTML_CSS }, { HTML_UNDEF }, "inherit", esr_inherit },
    { { HTML_CSS }, { HTML_UNDEF }, "medium", esr_medium },
    { { HTML_CSS }, { HTML_UNDEF }, "slow", esr_slow },
    { { HTML_CSS }, { HTML_UNDEF }, "slower", esr_slower },
    { { HTML_CSS }, { HTML_UNDEF }, "x-fast", esr_x_fast },
    { { HTML_CSS }, { HTML_UNDEF }, "x-slow", est_x_slow } };

struct symbol_entry < html_version, e_css_statement > css_statement_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "annotation", css_annotation, ns_default, CF_MUST_FONT_FV },
    { { HTML_CSS }, { HTML_UNDEF }, "bottom-center", css_bottom_centre, ns_default, CF_PRINT },
    { { HTML_CSS }, { HTML_UNDEF }, "bottom-left", css_bottom_left, ns_default, CF_PRINT },
    { { HTML_CSS }, { HTML_UNDEF }, "bottom-left-corner", css_bottom_left_corner, ns_default, CF_PRINT },
    { { HTML_CSS }, { HTML_UNDEF }, "bottom-right", css_bottom_right, ns_default, CF_PRINT },
    { { HTML_CSS }, { HTML_UNDEF }, "bottom-right-corner", css_bottom_right_corner, ns_default, CF_PRINT },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "character-variant", css_character_variant, ns_default, CF_MUST_FONT_FV },
    { { HTML_CSS }, { HTML_UNDEF }, "charset", css_charset },
    { { HTML_SVG11, 0, HE_SVG }, { HTML_UNDEF }, "color-profile", css_colour_profile },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "counter-style", css_counter_style },
    { { HTML_CSS, 0, 0, H2_CSS_MEDIA_5 }, { HTML_UNDEF }, "custom-media", css_custom_media },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "document", css_document },
    { { HTML_CSS, 0, 0, H2_CSS_COND_RULE_5 }, { HTML_UNDEF }, "else", css_else },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "font-feature-values", css_font_feature_values },
    { { HTML_CSS, 0, 0, H2_CSS_2 }, { HTML_UNDEF }, "font-face", css_font_face },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "font-palette-values", css_font_palette_values },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "historical-forms", css_historical_forms, ns_default, CF_MUST_FONT_FV },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "import", css_import },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "keyframes", css_keyframes },
    { { HTML_CSS, 0, 0, H2_CSS_CASCADE_5 }, { HTML_UNDEF }, "layer", css_layer },
    { { HTML_CSS }, { HTML_UNDEF }, "media", css_media },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "namespace", css_namespace },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ornaments", css_ornaments, ns_default, CF_MUST_FONT_FV },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "page", css_page },
    { { HTML_JAN22, 0, 0, H2_CSS_6 }, { HTML_UNDEF }, "scope", css_scope },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "swash", css_swash, ns_default, CF_MUST_FONT_FV },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "styleset", css_styleset, ns_default, CF_MUST_FONT_FV },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "stylistic", css_stylistic, ns_default, CF_MUST_FONT_FV },
    { { HTML_CSS, 0, 0, H2_CSS_CASCADE_4 | H2_CSS_COND_RULE_3 }, { HTML_UNDEF }, "supports", css_supports },
    { { HTML_CSS }, { HTML_UNDEF }, "top-center", css_top_centre, ns_default, CF_PRINT },
    { { HTML_CSS }, { HTML_UNDEF }, "top-left", css_top_left, ns_default, CF_PRINT },
    { { HTML_CSS }, { HTML_UNDEF }, "top-left-corner", css_top_left_corner, ns_default, CF_PRINT },
    { { HTML_CSS }, { HTML_UNDEF }, "top-right", css_top_right, ns_default, CF_PRINT },
    { { HTML_CSS }, { HTML_UNDEF }, "top-right-corner", css_top_right_corner, ns_default, CF_PRINT },
    { { HTML_CSS, 0, 0, H2_CSS_3 }, { HTML_UNDEF }, "viewport", css_viewport },
    { { HTML_CSS, 0, 0, H2_CSS_COND_RULE_5 }, { HTML_UNDEF }, "when", css_when } };

struct symbol_entry < html_version, e_css_system_e > css_system_e_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "additive", cse_additive },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "alphabetic", cse_alphabetic },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "cyclic", cse_cyclic },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "numeric", cse_numeric },
    { { HTML_CSS, 0, 0, H2_CSS_CS_3 }, { HTML_UNDEF }, "symbolic", cse_symbolic } };

struct symbol_entry < html_version, e_css_text_align > css_text_align_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "center", ecta_centre },
    { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecta_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "justify", ecta_justify },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "left", ecta_left },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "right", ecta_right } };

struct symbol_entry < html_version, e_css_text_decoration > css_text_decoration_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ectd_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ectd_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "underline", ectd_underline },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "overline", ectd_overline },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "line-through", ectd_linethrough },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "blink", ectd_blink } };

struct symbol_entry < html_version, e_css_text_transform > css_text_transform_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ect_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "capitalize", ect_capitalise },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "lowercase", ect_lowercase },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ect_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "uppercase", ect_uppercase } };

struct symbol_entry < html_version, e_css_user_select > css_user_select_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "all", ecu_all },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "auto", ecu_auto },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "contain", ecu_contain },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "inherit", ecu_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "none", ecu_none },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "text", ecu_text } };

struct symbol_entry < html_version, e_css_val_fn > css_val_fn_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "abs", cvf_abs },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "acos", cvf_acos },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "annotation", cvf_annotation },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "asin", cvf_asin },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "atan", cvf_atan },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "atan2", cvf_atan2 },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE }, { HTML_UNDEF }, "calc", cvf_calc },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "character-variant", cvf_character_variant },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "circle", cvf_circle },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "clamp", cvf_clamp },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "color", cvf_colour },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE | H2_CSS_COLOUR_5 }, { HTML_UNDEF }, "color-mix", cvf_colour_mix },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "cos", cvf_cos },
    { { HTML_CSS, 0, 0, H2_CSS_EASE }, { HTML_UNDEF }, "cubic-bezier", cvf_cubic_bezier },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE | H2_CSS_COLOUR_5 }, { HTML_UNDEF }, "device-cmyk", cvf_device_cmyk },
    { { HTML_CSS, 0, 0, H2_CSS_EASE }, { HTML_UNDEF }, "ease", cvf_ease, ns_default, CF_NO_PARAMS },
    { { HTML_CSS, 0, 0, H2_CSS_EASE }, { HTML_UNDEF }, "ease-in", cvf_ease_in, ns_default, CF_NO_PARAMS },
    { { HTML_CSS, 0, 0, H2_CSS_EASE }, { HTML_UNDEF }, "ease-in-out", cvf_ease_in_out, ns_default, CF_NO_PARAMS },
    { { HTML_CSS, 0, 0, H2_CSS_EASE }, { HTML_UNDEF }, "ease-out", cvf_ease_out, ns_default, CF_NO_PARAMS },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "ellipse", cvf_ellipse },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "exp", cvf_exp },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "format", cvf_format },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "historical-forms", cvf_historical_forms },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_3 }, { HTML_UNDEF }, "hsl", cvf_hsl },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_3 }, { HTML_UNDEF }, "hsla", cvf_hsla },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "hwb", cvf_hwb },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "hypot", cvf_hypot },
    { { HTML_CSS, 0, 0, 0, H3_CSS_IMAGE }, { HTML_UNDEF }, "image", cvf_image },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "inset", cvf_inset },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "lab", cvf_lab },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "lch", cvf_lch },
    { { HTML_CSS, 0, 0, H2_CSS_EASE }, { HTML_UNDEF }, "linear", cvf_linear, ns_default, CF_NO_PARAMS },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_3 }, { HTML_UNDEF }, "local", cvf_local },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "log", cvf_log },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "max", cvf_max },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "min", cvf_min },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "mix", cvf_mix },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "mod", cvf_mod },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "oklab", cvf_oklab },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_4 }, { HTML_UNDEF }, "oklch", cvf_oklch },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ornaments", cvf_ornaments },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "path", cvf_path },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "polygon", cvf_polygon },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "pow", cvf_pow },
    { { HTML_CSS }, { HTML_UNDEF }, "rgb", cvf_rgb },
    { { HTML_CSS, 0, 0, H2_CSS_COLOUR_3 }, { HTML_UNDEF }, "rgba", cvf_rgba },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "rect", cvf_rect },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "rem", cvf_rem },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "round", cvf_round },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "sign", cvf_sign },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "sin", cvf_sin },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "sqrt", cvf_sqrt },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "src", cvf_src },
    { { HTML_CSS, 0, 0, H2_CSS_EASE }, { HTML_UNDEF }, "step-end", cvf_step_end, ns_default, CF_NO_PARAMS },
    { { HTML_CSS, 0, 0, H2_CSS_EASE }, { HTML_UNDEF }, "step-start", cvf_step_start, ns_default, CF_NO_PARAMS },
    { { HTML_CSS, 0, 0, H2_CSS_EASE }, { HTML_UNDEF }, "steps", cvf_steps },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "styleset", cvf_styleset },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "stylistic", cvf_stylistic },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "swash", cvf_swash },
    { { HTML_CSS, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "tan", cvf_tan },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "tech", cvf_tech },
    { { HTML_CSS }, { HTML_UNDEF }, "url", cvf_url },
    { { HTML_CSS, 0, 0, H2_CSS_CUSTOM }, { HTML_UNDEF }, "var", cvf_var },
    { { HTML_CSS, 0, 0, 0, H3_CSS_SHAPE }, { HTML_UNDEF }, "xywh", cvf_xywh } };

struct symbol_entry < html_version, e_css_vertical_align > css_vertical_align_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecva_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "baseline", ecv_baseline },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "bottom", ecv_bottom },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "middle", ecv_middle },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "sub", ecv_sub },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "super", ecv_super },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "text-bottom", ecv_text_bottom },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "text-top", ecv_text_top },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "top", ecv_top } };

struct symbol_entry < html_version, e_css_visual_box > css_visual_box_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_BACKGROUND, H3_CSS_BOX_MODEL | H3_CSS_DISPLAY }, { HTML_UNDEF }, "border-box", eccl_border_box },
    { { HTML_CSS, 0, 0, H2_CSS_BACKGROUND, H3_CSS_BOX_MODEL | H3_CSS_DISPLAY }, { HTML_UNDEF }, "content-box", eccl_content_box },
    { { HTML_CSS, 0, 0, H2_CSS_BACKGROUND, H3_CSS_BOX_MODEL | H3_CSS_DISPLAY }, { HTML_UNDEF }, "padding-box", eccl_padding_box } };

struct symbol_entry < html_version, e_css_volume_e > css_volume_e_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", cve_inherit },
    { { HTML_CSS }, { HTML_UNDEF }, "loud", cve_loud },
    { { HTML_CSS }, { HTML_UNDEF }, "medium", cve_medium },
    { { HTML_CSS }, { HTML_UNDEF }, "silent", cve_silent },
    { { HTML_CSS }, { HTML_UNDEF }, "soft", cve_soft },
    { { HTML_CSS }, { HTML_UNDEF }, "x-loud", cve_x_loud },
    { { HTML_CSS }, { HTML_UNDEF }, "x-soft", cve_x_soft } };

struct symbol_entry < html_version, e_css_whitespace > css_whitespace_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "inherit", ecwh_inherit },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "normal", ecwh_normal },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "nowrap", ecwh_nowrap },
    { { HTML_CSS, 0, 0, H2_CSS }, { HTML_UNDEF }, "pre", ecwh_pre },
    { { HTML_CSS }, { HTML_UNDEF }, "pre-line", ecwh_preline },
    { { HTML_CSS }, { HTML_UNDEF }, "pre-wrap", ecwh_prewrap } };

struct symbol_entry < html_version, e_css_wide > css_wide_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_2 | H2_CSS_CASCADE }, { HTML_UNDEF }, "default", cw_default },
    { { HTML_CSS, 0, 0, H2_CSS_2 | H2_CSS_CASCADE }, { HTML_UNDEF }, "inherit", cw_inherit },
    { { HTML_CSS, 0, 0, H2_CSS_CASCADE }, { HTML_UNDEF }, "initial", cw_initial },
    { { HTML_CSS, 0, 0, H2_CSS_CASCADE_456 }, { HTML_UNDEF }, "revert", cw_revert },
    { { HTML_CSS, 0, 0, H2_CSS_CASCADE_56 }, { HTML_UNDEF }, "revert-layer", cw_revert_layer },
    { { HTML_CSS, 0, 0, H2_CSS_CASCADE }, { HTML_UNDEF }, "unset", cw_unset } };

struct symbol_entry < html_version, e_cursor > cursor_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "auto",  cu_auto },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "crosshair", cu_crosshair },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "default", cu_default },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "pointer", cu_pointer },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "move", cu_move },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "e-resize", cu_eresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "ne-resize", cu_neresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "nw-resize", cu_nwresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "n-resize", cu_nresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "se-resize", cu_seresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "sw-resize", cu_swresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "s-resize", cu_sresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "w-resize", cu_wresize },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "text", cu_text },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "wait", cu_wait },
    { { HTML_SVG10, 0, HE_SVG_10_11_FULL }, { HTML_UNDEF }, "help", cu_help },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "progress", cu_progress } };

struct symbol_entry < html_version, e_dcmitype > dcmitype_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "Collection", dt_collection },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Dataset", dt_dataset },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Event", dt_event },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Image", dt_image },
    { { XHTML_1_0 }, { HTML_UNDEF }, "InteractiveResource", dt_interactiveresource },
    { { XHTML_1_0 }, { HTML_UNDEF }, "MovingImage", dt_movingimage },
    { { XHTML_1_0 }, { HTML_UNDEF }, "PhysicalObject", dt_physicalobject },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Service", dt_service },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Software", dt_software },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Sound", dt_sound },
    { { XHTML_1_0 }, { HTML_UNDEF }, "StillImage", dt_stillimage },
    { { XHTML_1_0 }, { HTML_UNDEF }, "Text", dt_text },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Collection", dt_collection },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Dataset", dt_dataset },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Event", dt_event },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Image", dt_image },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/InteractiveResource", dt_interactiveresource },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/MovingImage", dt_movingimage },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/PhysicalObject", dt_physicalobject },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Service", dt_service },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Software", dt_software },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Sound", dt_sound },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/StillImage", dt_stillimage },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://purl.org/dc/dcmitype/Text", dt_text } };

struct symbol_entry < html_version, e_decalign > decalign_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "left", dec_left },
    { { HTML_2_0 }, { HTML_UNDEF }, "center", dec_center },
    { { HTML_2_0 }, { HTML_UNDEF }, "right", dec_right },
    { { HTML_2_0 }, { HTML_UNDEF }, "justify", dec_justify },
    { { HTML_2_0 }, { HTML_UNDEF }, "decimal", dec_decimal } };

struct symbol_entry < html_version, e_determiner > determiner_symbol_table [] =
{   { { HTML_OG_2012 }, { HTML_UNDEF }, "a", dt_a },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "an", dt_an },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "the", dt_the },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "auto", dt_auto } };

struct symbol_entry < html_version, e_dingbat > dingbat_symbol_table [] =
{   { { HTML_3_0 }, { HTML_3_0 }, "ftp", db_ftp },
    { { HTML_3_0 }, { HTML_3_0 }, "gopher", db_gopher },
    { { HTML_3_0 }, { HTML_3_0 }, "telnet", db_telnet },
    { { HTML_3_0 }, { HTML_3_0 }, "archive", db_archive },
    { { HTML_3_0 }, { HTML_3_0 }, "filing.cabinet", db_filing_cabinet },
    { { HTML_3_0 }, { HTML_3_0 }, "folder", db_folder },
    { { HTML_3_0 }, { HTML_3_0 }, "fixed.disk", db_fixed_disk },
    { { HTML_3_0 }, { HTML_3_0 }, "disk.drive", db_disk_drive },
    { { HTML_3_0 }, { HTML_3_0 }, "document", db_document },
    { { HTML_3_0 }, { HTML_3_0 }, "unknown.document", db_unknown_document },
    { { HTML_3_0 }, { HTML_3_0 }, "text.document", db_text_document },
    { { HTML_3_0 }, { HTML_3_0 }, "binary.document", db_binary_document },
    { { HTML_3_0 }, { HTML_3_0 }, "binhex.document", db_binhex_document },
    { { HTML_3_0 }, { HTML_3_0 }, "audio", db_audio },
    { { HTML_3_0 }, { HTML_3_0 }, "film", db_film },
    { { HTML_3_0 }, { HTML_3_0 }, "image", db_image },
    { { HTML_3_0 }, { HTML_3_0 }, "map", db_map },
    { { HTML_3_0 }, { HTML_3_0 }, "form", db_form },
    { { HTML_3_0 }, { HTML_3_0 }, "mail", db_mail },
    { { HTML_3_0 }, { HTML_3_0 }, "parent", db_parent },
    { { HTML_3_0 }, { HTML_3_0 }, "next", db_next },
    { { HTML_3_0 }, { HTML_3_0 }, "previous", db_previous },
    { { HTML_3_0 }, { HTML_3_0 }, "home", db_home },
    { { HTML_3_0 }, { HTML_3_0 }, "toc", db_toc },
    { { HTML_3_0 }, { HTML_3_0 }, "glossary", db_glossary },
    { { HTML_3_0 }, { HTML_3_0 }, "index", db_index },
    { { HTML_3_0 }, { HTML_3_0 }, "summary", db_summary },
    { { HTML_3_0 }, { HTML_3_0 }, "calculator", db_calculator },
    { { HTML_3_0 }, { HTML_3_0 }, "caution", db_caution },
    { { HTML_3_0 }, { HTML_3_0 }, "clock", db_clock },
    { { HTML_3_0 }, { HTML_3_0 }, "compressed.document", db_compressed_document },
    { { HTML_3_0 }, { HTML_3_0 }, "diskette", db_diskette },
    { { HTML_3_0 }, { HTML_3_0 }, "display", db_display },
    { { HTML_3_0 }, { HTML_3_0 }, "fax", db_fax },
    { { HTML_3_0 }, { HTML_3_0 }, "mail.in", db_mail_in },
    { { HTML_3_0 }, { HTML_3_0 }, "mail.out", db_mail_out },
    { { HTML_3_0 }, { HTML_3_0 }, "mouse", db_mouse },
    { { HTML_3_0 }, { HTML_3_0 }, "printer", db_printer },
    { { HTML_3_0 }, { HTML_3_0 }, "tn3270", db_tn3270 },
    { { HTML_3_0 }, { HTML_3_0 }, "trash", db_trash } };

struct symbol_entry < html_version, e_dir > dir_symbol_table [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, "auto",  di_auto },
    { { XHTML_2_0 }, { XHTML_2_0 }, "lro", di_lro },
    { { XHTML_2_0 }, { XHTML_2_0 }, "rlo", di_rlo },
    { { HTML_2_0 }, { HTML_UNDEF }, "ltr", di_ltr },
    { { HTML_2_0 }, { HTML_UNDEF }, "rtl", di_rtl },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "forward", di_forward },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "reverse", di_reverse } };

struct symbol_entry < html_version, e_display_align > display_align_symbol_table [] =
{   { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "auto",  da_auto },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "before", da_before },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "center", da_centre },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "after", da_after },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "inherit", da_inherit } };

struct symbol_entry < html_version, e_dominantbaseline > dominantbaseline_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "auto",  db_auto },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "use-script", db_usescript },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "no-change", db_nochange },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "reset-size", db_resetsize },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "ideographic", db_ideographic },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "alphabetic", db_alphabetic },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "hanging", db_hanging },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "mathematical", db_mathematical },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "central", db_central },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "middle", db_middle },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "text-after-edge", db_textafteredge },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "text-before-edge", db_textbeforeedge },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "inherit", db_inherit } };

struct symbol_entry < html_version, e_enterkeyhint > enterkeyhint_symbol_table [] =
{   { { HTML_JUL20 }, { HTML_UNDEF }, "done", ekh_done },
    { { HTML_JUL20 }, { HTML_UNDEF }, "enter", ekh_enter },
    { { HTML_JUL20 }, { HTML_UNDEF }, "go", ekh_go },
    { { HTML_JUL20 }, { HTML_UNDEF }, "next", ekh_next },
    { { HTML_JUL20 }, { HTML_UNDEF }, "previous", ekh_previous },
    { { HTML_JUL20 }, { HTML_UNDEF }, "search", ekh_search },
    { { HTML_JUL20 }, { HTML_UNDEF }, "send", ekh_send } };

struct symbol_entry < html_version, e_figalign > figalign_symbol_table [] =
{   { { HTML_3_0 }, { HTML_3_0 }, "bleedleft", fa_bleedleft },
    { { HTML_3_0 }, { HTML_3_0 }, "left", fa_left },
    { { HTML_3_0 }, { HTML_3_0 }, "center", fa_centre },
    { { HTML_3_0 }, { HTML_3_0 }, "right", fa_right },
    { { HTML_3_0 }, { HTML_3_0 }, "bleedright", fa_bleedright },
    { { HTML_3_0 }, { HTML_3_0 }, "justify", fa_justify } };

struct symbol_entry < html_version, e_filter_in > filter_in_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "SourceGraphic", fi_sourcegraphic },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "SourceAlpha", fi_sourcealpha },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "BackgroundImage", fi_backgroundimage },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "BackgroundAlpha", fi_backgroundalpha },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "FillPaint", fi_fillpaint },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "StrokePaint", fi_strokepaint } };

struct symbol_entry < html_version, e_font_enum > font_enum_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG, H2_CSS_2 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "caption",  fe_caption },
    { { HTML_SVG10, 0, HE_SVG, H2_CSS_2 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "icon",  fe_icon },
    { { HTML_SVG10, 0, HE_SVG, H2_CSS_2 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "menu", fe_menu },
    { { HTML_SVG10, 0, HE_SVG, H2_CSS_2 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "message-box", fe_message_box },
    { { HTML_SVG10, 0, HE_SVG, H2_CSS_2 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "small-caption", fe_small_caption },
    { { HTML_SVG10, 0, HE_SVG, H2_CSS_2 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "status-bar", fe_status_bar },
    { { HTML_SVG10, 0, HE_SVG_1, H2_CSS_2 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "inherit", fe_inherit } };

struct symbol_entry < html_version, e_fontname > fontname_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "serif", fn_serif },
    { { HTML_2_0 }, { HTML_UNDEF }, "sans-serif", fn_sans_serif },
    { { HTML_2_0 }, { HTML_UNDEF }, "cursive", fn_cursive },
    { { HTML_2_0 }, { HTML_UNDEF }, "fantasy", fn_fantasy },
    { { HTML_2_0 }, { HTML_UNDEF }, "monospace", fn_monospace },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "emoji", fn_emoji },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "fangsong", fn_fangsong },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "math", fn_math },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "system-ui", fn_system_ui },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ui-monospace", fn_ui_monospace },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ui-rounded", fn_ui_rounded },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ui-sans-serif", fn_ui_sans_serif },
    { { HTML_CSS, 0, 0, H2_CSS_FONT_4 }, { HTML_UNDEF }, "ui-serif", fn_ui_serif },
    { { HTML_2_0 }, { HTML_UNDEF }, "Al Bayan", fn_al_bayan },
    { { HTML_2_0 }, { HTML_UNDEF }, "American Typewriter", fn_american_typewriter },
    { { HTML_2_0 }, { HTML_UNDEF }, "Andale Mono", fn_andale_mono },
    { { HTML_2_0 }, { HTML_UNDEF }, "Apple Casual", fn_apple_casual },
    { { HTML_2_0 }, { HTML_UNDEF }, "Apple Chancery", fn_apple_chancery },
    { { HTML_2_0 }, { HTML_UNDEF }, "Apple Garamond", fn_apple_garamond },
    { { HTML_2_0 }, { HTML_UNDEF }, "Apple Gothic", fn_apple_gothic },
    { { HTML_2_0 }, { HTML_UNDEF }, "Apple LiGothic", fn_apple_ligothic },
    { { HTML_2_0 }, { HTML_UNDEF }, "Apple LiSung", fn_apple_lisung },
    { { HTML_2_0 }, { HTML_UNDEF }, "Apple Myungjo", fn_apple_myungjo },
    { { HTML_2_0 }, { HTML_UNDEF }, "Apple Symbols", fn_apple_symbols },
    { { HTML_2_0 }, { HTML_UNDEF }, "AquaKana", fn_aquakana },
    { { HTML_2_0 }, { HTML_UNDEF }, "Arial", fn_arial },
    { { HTML_2_0 }, { HTML_UNDEF }, "Arial Black", fn_arial_black },
    { { HTML_2_0 }, { HTML_UNDEF }, "Arial Hebrew", fn_arial_hebrew },
    { { HTML_2_0 }, { HTML_UNDEF }, "Ayuthaya", fn_ayuthaya },
    { { HTML_2_0 }, { HTML_UNDEF }, "Baghdad", fn_baghdad },
    { { HTML_2_0 }, { HTML_UNDEF }, "Bahnschrift", fn_bahnschrift },
    { { HTML_2_0 }, { HTML_UNDEF }, "Baskerville", fn_baskerville },
    { { HTML_2_0 }, { HTML_UNDEF }, "Beijing", fn_beijing },
    { { HTML_2_0 }, { HTML_UNDEF }, "BiauKai", fn_biaukai },
    { { HTML_2_0 }, { HTML_UNDEF }, "Big Caslon", fn_big_caslon },
    { { HTML_2_0 }, { HTML_UNDEF }, "Browallia New", fn_browallia_new },
    { { HTML_2_0 }, { HTML_UNDEF }, "BrowalliaUPC", fn_browalliaupc },
    { { HTML_2_0 }, { HTML_UNDEF }, "Brush Script", fn_brush_script },
    { { HTML_2_0 }, { HTML_UNDEF }, "Calibri", fn_calibri },
    { { HTML_2_0 }, { HTML_UNDEF }, "Cambria", fn_cambria },
    { { HTML_2_0 }, { HTML_UNDEF }, "Cambria Math", fn_cambria_math },
    { { HTML_2_0 }, { HTML_UNDEF }, "Candara", fn_candara },
    { { HTML_2_0 }, { HTML_UNDEF }, "Cascadia Code", fn_cascadia_code },
    { { HTML_2_0 }, { HTML_UNDEF }, "Cascadia Mono", fn_cascadia_mono },
    { { HTML_2_0 }, { HTML_UNDEF }, "Chalkboard", fn_chalkboard },
    { { HTML_2_0 }, { HTML_UNDEF }, "Chalkduster", fn_chalkduster },
    { { HTML_2_0 }, { HTML_UNDEF }, "Charcoal", fn_charcoal },
    { { HTML_2_0 }, { HTML_UNDEF }, "Charcoal CY", fn_charcoal_cy },
    { { HTML_2_0 }, { HTML_UNDEF }, "Chicago", fn_chicago },
    { { HTML_2_0 }, { HTML_UNDEF }, "Cochin", fn_cochin },
    { { HTML_2_0 }, { HTML_UNDEF }, "Comic Sans", fn_comic_sans },
    { { HTML_2_0 }, { HTML_UNDEF }, "Comic Sans MS", fn_comic_sans_ms },
    { { HTML_2_0 }, { HTML_UNDEF }, "Consolas", fn_consolas },
    { { HTML_2_0 }, { HTML_UNDEF }, "Constantia", fn_constantia },
    { { HTML_2_0 }, { HTML_UNDEF }, "Cooper", fn_cooper },
    { { HTML_2_0 }, { HTML_UNDEF }, "Copperplate", fn_copperplate },
    { { HTML_2_0 }, { HTML_UNDEF }, "Corbel", fn_corbel },
    { { HTML_2_0 }, { HTML_UNDEF }, "Corsiva Hebrew", fn_corsiva_hebrew },
    { { HTML_2_0 }, { HTML_UNDEF }, "Courier", fn_courier },
    { { HTML_2_0 }, { HTML_UNDEF }, "Courier New", fn_courier_new },
    { { HTML_2_0 }, { HTML_UNDEF }, "DecoType Naskh", fn_decotype_naskh },
    { { HTML_2_0 }, { HTML_UNDEF }, "Devanagari", fn_devanagari },
    { { HTML_2_0 }, { HTML_UNDEF }, "Didot", fn_didot },
    { { HTML_2_0 }, { HTML_UNDEF }, "Droid Sans", fn_droid_sans },
    { { HTML_2_0 }, { HTML_UNDEF }, "Droid Sans Mono", fn_droid_sans_mono },
    { { HTML_2_0 }, { HTML_UNDEF }, "Droid Serifs", fn_droid_serif },
    { { HTML_2_0 }, { HTML_UNDEF }, "Ebrima", fn_ebrima },
    { { HTML_2_0 }, { HTML_UNDEF }, "Euphemia UCAS", fn_euphemia_ucas },
    { { HTML_2_0 }, { HTML_UNDEF }, "Franklin Gothic Medium", fn_franklin_gothic_medium },
    { { HTML_2_0 }, { HTML_UNDEF }, "Futura", fn_futura },
    { { HTML_2_0 }, { HTML_UNDEF }, "Gabriola", fn_gabriola },
    { { HTML_2_0 }, { HTML_UNDEF }, "Gadget", fn_gadget },
    { { HTML_2_0 }, { HTML_UNDEF }, "Gadugi", fn_gadugi },
    { { HTML_2_0 }, { HTML_UNDEF }, "Geeza Pro", fn_geeza_pro },
    { { HTML_2_0 }, { HTML_UNDEF }, "Geezah", fn_geezah },
    { { HTML_2_0 }, { HTML_UNDEF }, "Geneva", fn_geneva },
    { { HTML_2_0 }, { HTML_UNDEF }, "Geneva CY", fn_geneva_cy },
    { { HTML_2_0 }, { HTML_UNDEF }, "Georgia", fn_georgia },
    { { HTML_2_0 }, { HTML_UNDEF }, "Gill Sans", fn_gill_sans },
    { { HTML_2_0 }, { HTML_UNDEF }, "Gujarati", fn_gujarati },
    { { HTML_2_0 }, { HTML_UNDEF }, "Gung Seoche", fn_gung_seoche },
    { { HTML_2_0 }, { HTML_UNDEF }, "Gurmukhi", fn_gurmukhi },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hangangche", fn_hangangche },
    { { HTML_2_0 }, { HTML_UNDEF }, "HeadlineA", fn_headlinea },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hei", fn_hei },
    { { HTML_2_0 }, { HTML_UNDEF }, "Helvetica", fn_helvetica },
    { { HTML_2_0 }, { HTML_UNDEF }, "Helvetica CY", fn_helvetica_cy },
    { { HTML_2_0 }, { HTML_UNDEF }, "Helvetica Neue", fn_helvetica_neue },
    { { HTML_2_0 }, { HTML_UNDEF }, "Herculanum", fn_herculanum },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hiragino Kaku Gothic Pro", fn_hiragino_kaku_gothic_pro },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hiragino Kaku Gothic ProN", fn_hiragino_kaku_gothic_pron },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hiragino Kaku Gothic Std", fn_hiragino_kaku_gothic_std },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hiragino Kaku Gothic StdN", fn_hiragino_kaku_gothic_stdn },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hiragino Maru Gothic Pro", fn_hiragino_maru_gothic_pro },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hiragino Maru Gothic ProN", fn_hiragino_maru_gothic_pron },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hiragino Mincho Pro", fn_hiragino_mincho_pro },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hiragino Mincho ProN", fn_hiragino_mincho_pron },
    { { HTML_2_0 }, { HTML_UNDEF }, "Hoefler Text", fn_hoefler_text },
    { { HTML_2_0 }, { HTML_UNDEF }, "HoloLens MDL2 Assets", fn_hololens_mdl2_assets },
    { { HTML_2_0 }, { HTML_UNDEF }, "Impact", fn_impact },
    { { HTML_2_0 }, { HTML_UNDEF }, "Inai Mathi", fn_inai_mathi },
    { { HTML_2_0 }, { HTML_UNDEF }, "Ink Free", fn_ink_free },
    { { HTML_2_0 }, { HTML_UNDEF }, "Javanese Text", fn_javanese_text },
    { { HTML_2_0 }, { HTML_UNDEF }, "Jung Gothic", fn_jung_gothic },
    { { HTML_2_0 }, { HTML_UNDEF }, "Kai", fn_kai },
    { { HTML_2_0 }, { HTML_UNDEF }, "Keyboard", fn_keyboard },
    { { HTML_2_0 }, { HTML_UNDEF }, "Krungthep", fn_krungthep },
    { { HTML_2_0 }, { HTML_UNDEF }, "Kuenstler Script", fn_kuenstler_script },
    { { HTML_2_0 }, { HTML_UNDEF }, "KufiStandard GK", fn_kufistandard_gk },
    { { HTML_2_0 }, { HTML_UNDEF }, "LastResort", fn_lastresort },
    { { HTML_2_0 }, { HTML_UNDEF }, "Leelawadee UI", fn_leelawadee_ui },
    { { HTML_2_0 }, { HTML_UNDEF }, "LiHei Pro", fn_lihei_pro },
    { { HTML_2_0 }, { HTML_UNDEF }, "LiSong Pro", fn_lisong_pro },
    { { HTML_2_0 }, { HTML_UNDEF }, "Lucida Console", fn_lucida_console },
    { { HTML_2_0 }, { HTML_UNDEF }, "Lucida Sans", fn_lucida_sans },
    { { HTML_2_0 }, { HTML_UNDEF }, "Lucida Sans Unicode", fn_lucida_sans_unicode },
    { { HTML_2_0 }, { HTML_UNDEF }, "MS Gothic", fn_ms_gothic },
    { { HTML_2_0 }, { HTML_UNDEF }, "MV Boli", fn_mv_boli },
    { { HTML_2_0 }, { HTML_UNDEF }, "Malgun Gothic", fn_malgun_gothic },
    { { HTML_2_0 }, { HTML_UNDEF }, "Marker Felt", fn_marker_felt },
    { { HTML_2_0 }, { HTML_UNDEF }, "Marlett", fn_marlett },
    { { HTML_2_0 }, { HTML_UNDEF }, "Menlo", fn_menlo },
    { { HTML_2_0 }, { HTML_UNDEF }, "Microsoft Himalaya", fn_microsoft_himalaya },
    { { HTML_2_0 }, { HTML_UNDEF }, "Microsoft JhengHei", fn_microsoft_jhenghei },
    { { HTML_2_0 }, { HTML_UNDEF }, "Microsoft New Tai Lue", fn_microsoft_new_tai_lue },
    { { HTML_2_0 }, { HTML_UNDEF }, "Microsoft PhagsPa", fn_microsoft_phagspa },
    { { HTML_2_0 }, { HTML_UNDEF }, "Microsoft Sans Serif", fn_microsoft_sans_serif },
    { { HTML_2_0 }, { HTML_UNDEF }, "Microsoft Tai Le", fn_microsoft_tai_le },
    { { HTML_2_0 }, { HTML_UNDEF }, "Microsoft YaHei", fn_microsoft_yahei },
    { { HTML_2_0 }, { HTML_UNDEF }, "Microsoft Yi Baiti", fn_microsoft_yi_baiti },
    { { HTML_2_0 }, { HTML_UNDEF }, "MingLiU-ExtB", fn_mingliu_extb },
    { { HTML_2_0 }, { HTML_UNDEF }, "Monaco", fn_monaco },
    { { HTML_2_0 }, { HTML_UNDEF }, "Monaco CY", fn_monaco_cy },
    { { HTML_2_0 }, { HTML_UNDEF }, "Mongolian Baiti", fn_mongolian_baiti },
    { { HTML_2_0 }, { HTML_UNDEF }, "Mshtakan", fn_mshtakan },
    { { HTML_2_0 }, { HTML_UNDEF }, "Myanmar Text", fn_myanmar_text },
    { { HTML_2_0 }, { HTML_UNDEF }, "NISC GB18030", fn_nisc_gb18030 },
    { { HTML_2_0 }, { HTML_UNDEF }, "Nadeem", fn_nadeem },
    { { HTML_2_0 }, { HTML_UNDEF }, "New Peninim", fn_new_peninim },
    { { HTML_2_0 }, { HTML_UNDEF }, "New York", fn_new_york },
    { { HTML_2_0 }, { HTML_UNDEF }, "Nirmala UI", fn_nirmala_ui },
    { { HTML_2_0 }, { HTML_UNDEF }, "Noto", fn_noto },
    { { HTML_2_0 }, { HTML_UNDEF }, "Optima", fn_optima },
    { { HTML_2_0 }, { HTML_UNDEF }, "Osaka", fn_osaka },
    { { HTML_2_0 }, { HTML_UNDEF }, "PC Myungjo", fn_pc_myungjo },
    { { HTML_2_0 }, { HTML_UNDEF }, "Palatino", fn_palatino },
    { { HTML_2_0 }, { HTML_UNDEF }, "Palatino Linotype", fn_palatino_linotype },
    { { HTML_2_0 }, { HTML_UNDEF }, "Papyrus", fn_papyrus },
    { { HTML_2_0 }, { HTML_UNDEF }, "Pilgiche", fn_pilgiche },
    { { HTML_2_0 }, { HTML_UNDEF }, "Plantagenet Cherokee", fn_plantagenet_cherokee },
    { { HTML_2_0 }, { HTML_UNDEF }, "Raanana", fn_raanana },
    { { HTML_2_0 }, { HTML_UNDEF }, "Roboto", fn_roboto },
    { { HTML_2_0 }, { HTML_UNDEF }, "ST FangSong", fn_st_fangsong },
    { { HTML_2_0 }, { HTML_UNDEF }, "ST FangSong 2", fn_st_fangsong_2 },
    { { HTML_2_0 }, { HTML_UNDEF }, "ST Heiti", fn_st_heiti },
    { { HTML_2_0 }, { HTML_UNDEF }, "ST Kaiti", fn_st_kaiti },
    { { HTML_2_0 }, { HTML_UNDEF }, "ST Song", fn_st_song },
    { { HTML_2_0 }, { HTML_UNDEF }, "Sand", fn_sand },
    { { HTML_2_0 }, { HTML_UNDEF }, "Sathu", fn_sathu },
    { { HTML_2_0 }, { HTML_UNDEF }, "Segoe Fluent Icons", fn_segoe_fluent_icons },
    { { HTML_2_0 }, { HTML_UNDEF }, "Segoe MDL2 Assets", fn_segoe_mdl2_assets },
    { { HTML_2_0 }, { HTML_UNDEF }, "Segoe Print", fn_segoe_print },
    { { HTML_2_0 }, { HTML_UNDEF }, "Segoe Script", fn_segoe_script },
    { { HTML_2_0 }, { HTML_UNDEF }, "Segoe UI", fn_segoe_ui },
    { { HTML_2_0 }, { HTML_UNDEF }, "Segoe UI Emoji", fn_segoe_ui_emoji },
    { { HTML_2_0 }, { HTML_UNDEF }, "Segoe UI Historic", fn_segoe_ui_historic },
    { { HTML_2_0 }, { HTML_UNDEF }, "Segoe UI Symbol", fn_segoe_ui_symbol },
    { { HTML_2_0 }, { HTML_UNDEF }, "Segoe UI Variable", fn_segoe_ui_variable },
    { { HTML_2_0 }, { HTML_UNDEF }, "Seoul", fn_seoul },
    { { HTML_2_0 }, { HTML_UNDEF }, "Shin Myungjo Neue", fn_shin_myungjo_neue },
    { { HTML_2_0 }, { HTML_UNDEF }, "Silom", fn_silom },
    { { HTML_2_0 }, { HTML_UNDEF }, "SimSun", fn_simsun },
    { { HTML_2_0 }, { HTML_UNDEF }, "Sitka", fn_sitka },
    { { HTML_2_0 }, { HTML_UNDEF }, "Skia", fn_skia },
    { { HTML_2_0 }, { HTML_UNDEF }, "Snell Roundhand", fn_snell_roundhand },
    { { HTML_2_0 }, { HTML_UNDEF }, "Sylfaen", fn_sylfaen },
    { { HTML_2_0 }, { HTML_UNDEF }, "Symbol", fn_symbol },
    { { HTML_2_0 }, { HTML_UNDEF }, "Tae Graphic", fn_tae_graphic },
    { { HTML_2_0 }, { HTML_UNDEF }, "Tahoma", fn_tahoma },
    { { HTML_2_0 }, { HTML_UNDEF }, "Taipei", fn_taipei },
    { { HTML_2_0 }, { HTML_UNDEF }, "Techno", fn_techno },
    { { HTML_2_0 }, { HTML_UNDEF }, "Textile", fn_textile },
    { { HTML_2_0 }, { HTML_UNDEF }, "Thonburi", fn_thonburi },
    { { HTML_2_0 }, { HTML_UNDEF }, "Times", fn_times },
    { { HTML_2_0 }, { HTML_UNDEF }, "Times CY", fn_times_cy },
    { { HTML_2_0 }, { HTML_UNDEF }, "Times New Roman", fn_times_new_roman },
    { { HTML_2_0 }, { HTML_UNDEF }, "Trebuchet MS", fn_trebuchet_ms },
    { { HTML_2_0 }, { HTML_UNDEF }, "Verdana", fn_verdana },
    { { HTML_2_0 }, { HTML_UNDEF }, "Webdings", fn_webdings },
    { { HTML_2_0 }, { HTML_UNDEF }, "Wingdings", fn_wingdings },
    { { HTML_2_0 }, { HTML_UNDEF }, "Yu Gothic", fn_yu_gothic },
    { { HTML_2_0 }, { HTML_UNDEF }, "Zapf Chancery", fn_zapf_chancery },
    { { HTML_2_0 }, { HTML_UNDEF }, "Zapf Dingbats", fn_zapf_dingbats },
    { { HTML_2_0 }, { HTML_UNDEF }, "Zapfino", fn_zapfino } };

struct symbol_entry < html_version, e_font_variant_2 > font_variant_2_symbol_table [] =
{   { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "none", fv2_none },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "common", fv2_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "common-ligatures", fv2_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "no-common", fv2_no_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "no-common-ligatures", fv2_no_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2), H2_CSS_FONT_34 }, { HTML_UNDEF }, "discretionary-ligatures", fv2_discretionary },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2), H2_CSS_FONT_34 }, { HTML_UNDEF }, "no-discretionary-ligatures", fv2_no_discretionary },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3), H2_CSS_FONT_34 }, { HTML_UNDEF }, "historical-ligatures", fv2_historical },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3), H2_CSS_FONT_34 }, { HTML_UNDEF }, "no-historical-ligatures", fv2_no_historical },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4), H2_CSS_FONT_34 }, { HTML_UNDEF }, "contextual", fv2_contextual },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4) }, { HTML_UNDEF }, "contextual-ligatures", fv2_contextual },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4), H2_CSS_FONT_34 }, { HTML_UNDEF }, "no-contextual", fv2_no_contextual },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4) }, { HTML_UNDEF }, "no-contextual-ligatures", fv2_no_contextual },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5), H2_CSS_FONT_34 }, { HTML_UNDEF }, "jis78", fv2_jis78 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5), H2_CSS_FONT_34 }, { HTML_UNDEF }, "jis83", fv2_jis83 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5), H2_CSS_FONT_34 }, { HTML_UNDEF }, "jis90", fv2_jis90 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5), H2_CSS_FONT_34 }, { HTML_UNDEF }, "jis04", fv2_jis04 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5), H2_CSS_FONT_34 }, { HTML_UNDEF }, "simplified", fv2_simplified },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (5), H2_CSS_FONT_34 }, { HTML_UNDEF }, "traditional", fv2_traditional },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (6), H2_CSS_FONT_34 }, { HTML_UNDEF }, "full-width", fv2_full_width },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (6), H2_CSS_FONT_34 }, { HTML_UNDEF }, "proportional-width", fv2_proportional_width },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (7), H2_CSS_FONT_34 }, { HTML_UNDEF }, "lining-nums", fv2_lining_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (7), H2_CSS_FONT_34 }, { HTML_UNDEF }, "oldstyle-nums", fv2_oldstyle_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (8), H2_CSS_FONT_34 }, { HTML_UNDEF }, "proportional-nums", fv2_proportional_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (8), H2_CSS_FONT_34 }, { HTML_UNDEF }, "tabular-nums", fv2_tabular_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (9), H2_CSS_FONT_34 }, { HTML_UNDEF }, "diagonal-fractions", fv2_diagonal_fractions },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (9), H2_CSS_FONT_34 }, { HTML_UNDEF }, "stacked-fractions", fv2_stacked_fractions },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10), H2_CSS_FONT_34 }, { HTML_UNDEF }, "normal", fv2_normal },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10), H2_CSS_FONT_34 }, { HTML_UNDEF }, "small-caps", fv2_small_caps },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10), H2_CSS_FONT_34 }, { HTML_UNDEF }, "all-small-caps", fv2_all_small_caps },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10), H2_CSS_FONT_34 }, { HTML_UNDEF }, "petite-caps", fv2_petite_caps },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10), H2_CSS_FONT_34 }, { HTML_UNDEF }, "all-petite-caps", fv2_all_petite_caps },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10), H2_CSS_FONT_34 }, { HTML_UNDEF }, "unicase", fv2_unicase },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (10), H2_CSS_FONT_34 }, { HTML_UNDEF }, "titling-caps", fv2_titling_caps },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (11), H2_CSS_FONT_34 }, { HTML_UNDEF }, "sub", fv2_sub },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (11), H2_CSS_FONT_34 }, { HTML_UNDEF }, "super", fv2_super },
    { { HTML_SVG20, 0, HE_COMBINES, H2_CSS_FONT_34 }, { HTML_UNDEF }, "ordinal", fv2_ordinal },
    { { HTML_SVG20, 0, HE_COMBINES, H2_CSS_FONT_34 }, { HTML_UNDEF }, "slashed-zero", fv2_slashed_zero },
    { { HTML_SVG20, 0, HE_COMBINES, H2_CSS_FONT_34 }, { HTML_UNDEF }, "ruby", fv2_ruby } };

struct symbol_entry < html_version, e_font_variant_caps > font_variant_caps_symbol_table [] =
{   { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "normal", fvc_normal },
    { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "small-caps", fvc_small_caps },
    { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "all-small-caps", fvc_all_small_caps },
    { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "petite-caps", fvc_petite_caps },
    { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "all-petite-caps", fvc_all_petite_caps },
    { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "unicase", fvc_unicase },
    { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "titling-caps", fvc_titling_caps } };

struct symbol_entry < html_version, e_font_variant_east_asian > font_variant_east_asian_symbol_table [] =
{   { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "normal", fvea_normal },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "jis78", fvea_jis78 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "jis83", fvea_jis83 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "jis90", fvea_jis90 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "jis04", fvea_jis04 },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "simplified", fvea_simplified },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "traditional", fvea_traditional },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2), H2_CSS_FONT_34 }, { HTML_UNDEF }, "full-width", fvea_full_width },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2), H2_CSS_FONT_34 }, { HTML_UNDEF }, "proportional-width", fvea_proportional_width },
    { { HTML_SVG20, 0, HE_COMBINES, H2_CSS_FONT_34 }, { HTML_UNDEF }, "ruby", fvea_ruby } };

struct symbol_entry < html_version, e_font_variant_ligature > font_variant_ligature_symbol_table [] =
{   { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "normal", fvl_normal },
    { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "none", fvl_none },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "common", fvl_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "common-ligatures", fvl_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1) }, { HTML_UNDEF }, "no-common", fvl_no_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "no-common-ligatures", fvl_no_common },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2), H2_CSS_FONT_34 }, { HTML_UNDEF }, "discretionary-ligatures", fvl_discretionary },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2), H2_CSS_FONT_34 }, { HTML_UNDEF }, "no-discretionary-ligatures", fvl_no_discretionary },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3), H2_CSS_FONT_34 }, { HTML_UNDEF }, "historical-ligatures", fvl_historical },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3), H2_CSS_FONT_34 }, { HTML_UNDEF }, "no-historical-ligatures", fvl_no_historical },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4), H2_CSS_FONT_34 }, { HTML_UNDEF }, "contextual", fvl_contextual },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4) }, { HTML_UNDEF }, "contextual-ligatures", fvl_contextual },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4), H2_CSS_FONT_34 }, { HTML_UNDEF }, "no-contextual", fvl_no_contextual },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (4) }, { HTML_UNDEF }, "no-contextual-ligatures", fvl_no_contextual } };

struct symbol_entry < html_version, e_font_variant_numeric > font_variant_numeric_symbol_table [] =
{   { { HTML_SVG20, 0, 0, H2_CSS_FONT_34 }, { HTML_UNDEF }, "normal", fvn_normal },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "lining-nums", fvn_lining_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (1), H2_CSS_FONT_34 }, { HTML_UNDEF }, "oldstyle-nums", fvn_oldstyle_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2), H2_CSS_FONT_34 }, { HTML_UNDEF }, "proportional-nums", fvn_proportional_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (2), H2_CSS_FONT_34 }, { HTML_UNDEF }, "tabular-nums", fvn_tabular_nums },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3), H2_CSS_FONT_34 }, { HTML_UNDEF }, "diagonal-fractions", fvn_diagonal_fractions },
    { { HTML_SVG20, 0, HE_COMBINES | HE_GROUP (3), H2_CSS_FONT_34 }, { HTML_UNDEF }, "stacked-fractions", fvn_stacked_fractions },
    { { HTML_SVG20, 0, HE_COMBINES, H2_CSS_FONT_34 }, { HTML_UNDEF }, "ordinal", fvn_ordinal },
    { { HTML_SVG20, 0, HE_COMBINES, H2_CSS_FONT_34 }, { HTML_UNDEF }, "slashed-zero", fvn_slashed_zero } };

struct symbol_entry < html_version, e_formaturi > formaturi_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/JSON-LD", furi_json_ld },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/N3", furi_n3 },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/N-Triples", furi_n_triples },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/N-Quads", furi_n_quads },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/LD_Patch", furi_ldpatch },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/microdata", furi_microdata },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/OWL_XML", furi_owlxmlserialization },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/OWL_Functional", furi_owlfunctionalsyntax },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/OWL_Manchester", furi_owlmanchestersyntax },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/POWDER", furi_powder },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/POWDER-S", furi_powder_s },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/PROV-N", furi_prov_n },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/PROV-XML", furi_prov_xml },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/RDFa", furi_rdfa },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/RDF_JSON", furi_rdf_json },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/RDF_XML", furi_rdf_xml },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/RIF_XML", furi_rifxmlsyntax },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/SPARQL_Results_XML", furi_sparqlresultsinxml },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/SPARQL_Results_JSON", furi_sparqlresultsinjson },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/SPARQL_Results_CSV", furi_sparqlresultsincsv },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/SPARQL_Results_TSV", furi_sparqlresultsintsv },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/Turtle", furi_turtle },
    { { XHTML_1_0 }, { HTML_UNDEF }, "http://www.w3.org/ns/formats/TriG", furi_trig } };

struct symbol_entry < html_version, e_halign > halign_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "left", al_left },
    { { HTML_2_0 }, { HTML_UNDEF }, "center", al_center },
    { { HTML_2_0 }, { HTML_UNDEF }, "right", al_right },
    { { HTML_2_0 }, { HTML_UNDEF }, "justify", al_justify },
    { { HTML_2_0 }, { HTML_UNDEF }, "char", al_char } };

struct symbol_entry < html_version, e_icalfreq > icalfreq_symbol_table [] =
{   { { HTML_RDF10 }, { HTML_UNDEF }, "secondly", if_sec },
    { { HTML_RDF10 }, { HTML_UNDEF }, "minutely", ical_min }, // not that it means minutely!!
    { { HTML_RDF10 }, { HTML_UNDEF }, "hourly", ical_hour },
    { { HTML_RDF10 }, { HTML_UNDEF }, "daily", ical_day },
    { { HTML_RDF10 }, { HTML_UNDEF }, "weekly", ical_week },
    { { HTML_RDF10 }, { HTML_UNDEF }, "monthly", ical_month },
    { { HTML_RDF10 }, { HTML_UNDEF }, "yearly", ical_year } };

struct symbol_entry < html_version, e_icc > icc_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS/GRACoL TR006 2007", icc_CGATS_GRACoL_TR006_2007 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS/SNAP TR002 2007", icc_CGATS_SNAP_TR002_2007 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS/SWOP TR003 2007", icc_CGATS_SWOP_TR003_2007 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS/SWOP TR005 2007", icc_CGATS_SWOP_TR005_2007 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC1", icc_CGATS21_2_CRPC1 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC2", icc_CGATS21_2_CRPC2 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC3", icc_CGATS21_2_CRPC3 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC4", icc_CGATS21_2_CRPC4 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC5", icc_CGATS21_2_CRPC5 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC6", icc_CGATS21_2_CRPC6 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "CGATS21-2-CRPC7", icc_CGATS21_2_CRPC7 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA39", icc_FOGRA39 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA40", icc_FOGRA40 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA47", icc_FOGRA47 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA51", icc_FOGRA51 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA52", icc_FOGRA52 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "FOGRA54", icc_FOGRA54 },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "Japan Color 2011", icc_Japan_Color_2011 } };

struct symbol_entry < html_version, e_image_rendering > image_rendering_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "auto", ir_auto },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeSpeed", ir_optimisespeed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeQuality", ir_optimisequality },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", ir_inherit } };

struct symbol_entry < html_version, e_indentalign > indentalign_symbol_table [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, "left", ia_left },
    { { HTML_5_2 }, { HTML_UNDEF }, "center", ia_centre },
    { { HTML_5_2 }, { HTML_UNDEF }, "right", ia_right },
    { { HTML_5_2 }, { HTML_UNDEF }, "auto", ia_auto },
    { { HTML_5_2 }, { HTML_UNDEF }, "id", ia_id } };

struct symbol_entry < html_version, e_inky > inky_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "sourcegraphic", ink_sourcegraphic },
    { { HTML_2_0 }, { HTML_UNDEF }, "sourcealpha", ink_sourcealpha },
    { { HTML_2_0 }, { HTML_UNDEF }, "backgroundimage", ink_backgroundimage },
    { { HTML_2_0 }, { HTML_UNDEF }, "backgroundalpha", ink_backgroundalpha },
    { { HTML_2_0 }, { HTML_UNDEF }, "fillpaint", ink_fillpaint },
    { { HTML_2_0 }, { HTML_UNDEF }, "strokepaint", ink_strokepaint } };

struct symbol_entry < html_version, e_inputmode > inputmode_symbol_table [] =
{   { { HTML_JAN18 }, { HTML_UNDEF }, "decimal", im_decimal },
    { { HTML_JAN13, HV_NOT52 }, { HTML_UNDEF }, "email", im_email },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "full-width-latin", im_fullwidthlatin },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "katakana", im_katakana },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "kana", im_kana },
    { { HTML_JAN15, HV_NOT52 }, { HTML_DEC17 }, "kana-name", im_kananame },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "latin", im_latin },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "latin-name", im_latinname },
    { { HTML_JAN13, HV_NOT52 }, { HTML_DEC17 }, "latin-prose", im_latinprose },
    { { HTML_JAN18 }, { HTML_UNDEF }, "none", im_none },
    { { HTML_JAN13 }, { HTML_UNDEF }, "numeric", im_numeric  },
    { { HTML_JAN18 }, { HTML_UNDEF }, "search", im_search },
    { { HTML_JAN13 }, { HTML_UNDEF }, "tel", im_tel },
    { { HTML_JAN18 }, { HTML_UNDEF }, "text", im_text },
    { { HTML_JAN13 }, { HTML_UNDEF }, "verbatim", im_verbatim },
    { { HTML_JAN13 }, { HTML_UNDEF }, "url", im_url } };

struct symbol_entry < html_version, e_inputplus > inputplus_symbol_table [] =
{   { { HTML_PLUS }, { HTML_PLUS }, "audio", ip_audio },
    { { HTML_PLUS }, { HTML_PLUS }, "checkbox", ip_checkbox },
    { { HTML_PLUS }, { HTML_PLUS }, "date", ip_date },
    { { HTML_PLUS }, { HTML_PLUS }, "float", ip_float },
    { { HTML_PLUS }, { HTML_PLUS }, "image", ip_image },
    { { HTML_PLUS }, { HTML_PLUS }, "int", ip_int },
    { { HTML_PLUS }, { HTML_PLUS }, "radio", ip_radio },
    { { HTML_PLUS }, { HTML_PLUS }, "range", ip_range },
    { { HTML_PLUS }, { HTML_PLUS }, "reset", ip_reset },
    { { HTML_PLUS }, { HTML_PLUS }, "scribble", ip_scribble },
    { { HTML_PLUS }, { HTML_PLUS }, "submit", ip_submit },
    { { HTML_PLUS }, { HTML_PLUS }, "text", ip_text },
    { { HTML_PLUS }, { HTML_PLUS }, "url", ip_url } };

struct symbol_entry < html_version, e_inputtype > inputtype_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "checkbox", it_checkbox },
    { { HTML_2_0 }, { HTML_UNDEF }, "file", it_file },
    { { HTML_2_0 }, { HTML_UNDEF }, "hidden", it_hidden },
    { { HTML_2_0 }, { HTML_UNDEF }, "image", it_image },
    { { HTML_2_0 }, { HTML_UNDEF }, "password", it_password },
    { { HTML_2_0 }, { HTML_UNDEF }, "radio", it_radio },
    { { HTML_2_0 }, { HTML_UNDEF }, "reset", it_reset },
    { { HTML_2_0 }, { HTML_UNDEF }, "submit", it_submit },
    { { HTML_2_0 }, { HTML_UNDEF }, "text", it_text } };

struct symbol_entry < html_version, e_inputtype3 > inputtype3_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "checkbox", i3_checkbox },
    { { HTML_2_0, HV_RFC_1867 }, { HTML_UNDEF }, "file", i3_file },
    { { HTML_2_0 }, { HTML_UNDEF }, "hidden", i3_hidden },
    { { HTML_2_0 }, { HTML_UNDEF }, "image", i3_image },
    { { HTML_2_0 }, { HTML_UNDEF }, "password", i3_password },
    { { HTML_2_0 }, { HTML_UNDEF }, "radio", i3_radio },
    { { HTML_3_0 }, { HTML_3_0 }, "range", i3_range },
    { { HTML_2_0 }, { HTML_UNDEF }, "reset", i3_reset },
    { { HTML_3_0 }, { HTML_3_0 }, "scribble", i3_scribble },
    { { HTML_2_0 }, { HTML_UNDEF }, "submit", i3_submit },
    { { HTML_2_0 }, { HTML_UNDEF }, "text", i3_text } };

struct symbol_entry < html_version, e_inputtype32 > inputtype32_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "checkbox", i2_checkbox },
    { { HTML_2_0 }, { HTML_UNDEF }, "file", i2_file },
    { { HTML_2_0 }, { HTML_UNDEF }, "hidden", i2_hidden },
    { { HTML_2_0 }, { HTML_UNDEF }, "image", i2_image },
    { { HTML_2_0 }, { HTML_UNDEF }, "password", i2_password },
    { { HTML_2_0 }, { HTML_UNDEF }, "radio", i2_radio },
    { { HTML_2_0 }, { HTML_UNDEF }, "reset", i2_reset },
    { { HTML_2_0 }, { HTML_UNDEF }, "submit", i2_submit },
    { { HTML_2_0 }, { HTML_UNDEF }, "text", i2_text } };

struct symbol_entry < html_version, e_inputtype4 > inputtype4_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "button", i4_button },
    { { HTML_2_0 }, { HTML_UNDEF }, "checkbox", i4_checkbox },
    { { HTML_2_0 }, { HTML_UNDEF }, "file", i4_file },
    { { HTML_2_0 }, { HTML_UNDEF }, "hidden", i4_hidden },
    { { HTML_2_0 }, { HTML_UNDEF }, "image", i4_image },
    { { HTML_2_0 }, { HTML_UNDEF }, "password", i4_password },
    { { HTML_2_0 }, { HTML_UNDEF }, "radio", i4_radio },
    { { HTML_2_0 }, { HTML_UNDEF }, "reset", i4_reset },
    { { HTML_2_0 }, { HTML_UNDEF }, "submit", i4_submit },
    { { HTML_2_0 }, { HTML_UNDEF }, "text", i4_text } };

struct symbol_entry < html_version, e_inputtype5 > inputtype5_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "button", i5_button },
    { { HTML_2_0 }, { HTML_UNDEF }, "checkbox", i5_checkbox },
    { { HTML_JAN05 }, { HTML_UNDEF }, "color", i5_colour },
    { { HTML_JAN05 }, { HTML_UNDEF }, "date", i5_date },
    { { HTML_JAN05, HV_NOT50 }, { HTML_UNDEF }, "datetime", i5_datetime },
    { { HTML_JAN05, HV_NOT50 }, { HTML_UNDEF }, "datetime-local", i5_datetime_local },
    { { HTML_JAN05 }, { HTML_UNDEF }, "email", i5_email },
    { { 2, 1 }, { HTML_UNDEF }, "file", i5_file },
    { { HTML_2_0 }, { HTML_UNDEF }, "hidden", i5_hidden },
    { { HTML_2_0 }, { HTML_UNDEF }, "image", i5_image },
    { { HTML_JAN05, HV_NOT50 }, { HTML_UNDEF }, "month", i5_month },
    { { HTML_JAN05 }, { HTML_UNDEF }, "number", i5_number },
    { { HTML_2_0 }, { HTML_UNDEF }, "password", i5_password },
    { { HTML_2_0 }, { HTML_UNDEF }, "radio", i5_radio },
    { { HTML_2_0 }, { HTML_UNDEF }, "reset", i5_reset },
    { { HTML_3_0 }, { HTML_UNDEF }, "range", i5_range },
    { { HTML_JAN05 }, { HTML_UNDEF }, "search", i5_search },
    { { HTML_2_0 }, { HTML_UNDEF }, "submit", i5_submit },
    { { HTML_JAN05 }, { HTML_UNDEF }, "tel", i5_tel },
    { { HTML_2_0 }, { HTML_UNDEF }, "text", i5_text },
    { { HTML_JAN05 }, { HTML_UNDEF }, "time", i5_time },
    { { HTML_JAN05 }, { HTML_UNDEF }, "url", i5_url },
    { { HTML_JAN05, HV_NOT50 }, { HTML_UNDEF }, "week", i5_week } };

struct symbol_entry < html_version, e_jtoken > jtoken_symbol_table [] =
{   { { HTML_JAN14 }, { HTML_UNDEF }, "@base", jt_base },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@container", jt_container },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@context", jt_context },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@direction", jt_direction },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@graph", jt_graph },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@id", jt_id },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@import", jt_import },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@included", jt_included },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@index", jt_index },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@json", jt_json },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@language", jt_language },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@list", jt_list },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@nest", jt_nest },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@none", jt_none },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@prefix", jt_prefix },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@propagate", jt_propagate },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@protected", jt_protected },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@reverse", jt_reverse },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@set", jt_set },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@type", jt_type },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@value", jt_value },
    { { HTML_JUL20 }, { HTML_UNDEF }, "@version", jt_version },
    { { HTML_JAN14 }, { HTML_UNDEF }, "@vocab", jt_vocab } };

struct symbol_entry < html_version, e_kind > kind_symbol_table [] =
{   { { HTML_JUL10 }, { HTML_UNDEF }, "subtitles", k_subtitles },
    { { HTML_JUL10 }, { HTML_UNDEF }, "captions", k_captions },
    { { HTML_JUL10 }, { HTML_UNDEF }, "descriptions", k_descriptions },
    { { HTML_JUL10 }, { HTML_UNDEF }, "chapters", k_chapters },
    { { HTML_JUL10 }, { HTML_UNDEF }, "metadata", k_metadata } };

struct symbol_entry < html_version, e_length_absolute > length_absolute_symbol_table [] =
{   { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "cm", l_cm },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "mm", l_mm },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "q", l_q },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "in", l_in },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "pc", l_pc },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "pt", l_pt },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "px", l_px } };

struct symbol_entry < html_version, e_length_relative > length_relative_symbol_table [] =
{   { { HTML_3_2, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "%", l_percent },
    { { HTML_4_0 }, { HTML_4_01 }, "*", l_star },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "em", l_em },
    { { HTML_4_0, 0, 0, H2_CSS_ALL }, { HTML_UNDEF }, "ex", l_ex },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "cap", l_cap },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "ch", l_ch },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "ic", l_ic },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "rem", l_rem },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "lh", l_lh },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "rlh", l_rlh },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "vw", l_vw },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "vh", l_vh },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "vi", l_vi },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_4 }, { HTML_UNDEF }, "vb", l_vb },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "vmin", l_vmin },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "vmax", l_vmax } };

struct symbol_entry < html_version, e_linebreak > linebreak_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "auto", lb_auto },
    { { XHTML_1_0 }, { HTML_UNDEF }, "newline", lb_newline },
    { { XHTML_1_0 }, { HTML_UNDEF }, "indentingnewline", lb_indentingnewline },
    { { XHTML_1_0 }, { HTML_UNDEF }, "nobreak", lb_nobreak },
    { { XHTML_1_0 }, { HTML_UNDEF }, "goodbreak", lb_goodbreak },
    { { XHTML_1_0 }, { HTML_UNDEF }, "badbreak", lb_badbreak } };

struct symbol_entry < html_version, e_linkparam > linkparam_symbol_table [] =
{   { { HTML_NOV17 }, { HTML_UNDEF }, "anchor", lp_anchor },
    { { HTML_NOV17 }, { HTML_UNDEF }, "hreflang", lp_hreflang },
    { { HTML_NOV17 }, { HTML_UNDEF }, "media", lp_media },
    { { HTML_NOV17 }, { HTML_UNDEF }, "rel", lp_rel },
    { { HTML_NOV17 }, { HTML_UNDEF }, "rev", lp_rev },
    { { HTML_NOV17 }, { HTML_UNDEF }, "title", lp_title },
    { { HTML_NOV17 }, { HTML_UNDEF }, "title*", lp_titlestar },
    { { HTML_NOV17 }, { HTML_UNDEF }, "type", lp_type } };

struct symbol_entry < html_version, e_listtype > listtype_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "1", li_1 },
    { { HTML_UNDEF }, { HTML_UNDEF }, "a", li_a },
    { { HTML_UNDEF }, { HTML_UNDEF }, "A", li_A },
    { { HTML_UNDEF }, { HTML_UNDEF }, "i", li_i },
    { { HTML_UNDEF }, { HTML_UNDEF }, "I", li_I } };

struct symbol_entry < html_version, e_longdivstyle > longdivstyle_symbol_table [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, "lefttop", ls_lefttop },
    { { HTML_5_2 }, { HTML_UNDEF }, "stackedrightright", ls_stackedrightright },
    { { HTML_5_2 }, { HTML_UNDEF }, "mediumstackedrightright", ls_mediumstackedrightright },
    { { HTML_5_2 }, { HTML_UNDEF }, "shortstackedrightright", ls_shortstackedrightright },
    { { HTML_5_2 }, { HTML_UNDEF }, "righttop", ls_righttop },
    { { HTML_5_2 }, { HTML_UNDEF }, "left/\\right", ls_leftslashright },
    { { HTML_5_2 }, { HTML_UNDEF }, "left)(right", ls_leftketbraright },
    { { HTML_5_2 }, { HTML_UNDEF }, ":right=right", ls_rightequalright },
    { { HTML_5_2 }, { HTML_UNDEF }, "stackedleftleft", ls_stackedleftleft },
    { { HTML_5_2 }, { HTML_UNDEF }, "stackedleftlinetop", ls_stackedleftlinetop } };

struct symbol_entry < html_version, e_mah > mah_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "go", mah_go },
    { { HTML_UNDEF }, { HTML_UNDEF }, "done", mah_done },
    { { HTML_UNDEF }, { HTML_UNDEF }, "next", mah_next },
    { { HTML_UNDEF }, { HTML_UNDEF }, "search", mah_search },
    { { HTML_UNDEF }, { HTML_UNDEF }, "send", mah_send } };

struct symbol_entry < html_version, e_mathalign > mathalign_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "axis", ma_axis },
    { { XHTML_1_0 }, { HTML_UNDEF }, "baseline", ma_baseline },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bottom", ma_bottom },
    { { XHTML_1_0 }, { HTML_UNDEF }, "center", ma_centre },
    { { XHTML_1_0 }, { HTML_UNDEF }, "top", ma_top } };

struct symbol_entry < html_version, e_mathlocation > mathlocation_symbol_table [] =
{   { { HTML_5_2 }, { HTML_UNDEF }, "w", ml_w },
    { { HTML_5_2 }, { HTML_UNDEF }, "nw", ml_nw },
    { { HTML_5_2 }, { HTML_UNDEF }, "n", ml_n },
    { { HTML_5_2 }, { HTML_UNDEF }, "ne", ml_ne },
    { { HTML_5_2 }, { HTML_UNDEF }, "e", ml_e },
    { { HTML_5_2 }, { HTML_UNDEF }, "se", ml_se },
    { { HTML_5_2 }, { HTML_UNDEF }, "s", ml_s },
    { { HTML_5_2 }, { HTML_UNDEF }, "sw", ml_sw } };

struct symbol_entry < html_version, e_mathoverflow > mathoverflow_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "elide", ov_elide },
    { { HTML_5_2 }, { HTML_UNDEF }, "linebreak", ov_linebreak },
    { { XHTML_1_0 }, { HTML_UNDEF }, "scale", ov_scale },
    { { XHTML_1_0 }, { HTML_UNDEF }, "scroll", ov_scroll },
    { { XHTML_1_0 }, { HTML_UNDEF }, "truncate", ov_truncate } };

struct symbol_entry < html_version, e_mathnotation > mathnotation_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "longdiv", mn_longdiv },
    { { XHTML_1_0 }, { HTML_UNDEF }, "actuarial", mn_actuarial },
    { { XHTML_1_0 }, { HTML_UNDEF }, "radical", mn_radical },
    { { XHTML_1_0 }, { HTML_UNDEF }, "box", mn_box },
    { { XHTML_1_0 }, { HTML_UNDEF }, "roundedbox", mn_roundedbox },
    { { XHTML_1_0 }, { HTML_UNDEF }, "circle", mn_circle },
    { { XHTML_1_0 }, { HTML_UNDEF }, "left", mn_left },
    { { XHTML_1_0 }, { HTML_UNDEF }, "right", mn_right },
    { { XHTML_1_0 }, { HTML_UNDEF }, "top", mn_top },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bottom", mn_bottom },
    { { XHTML_1_0 }, { HTML_UNDEF }, "updiagonalstrike", mn_updiagonalstrike },
    { { XHTML_1_0 }, { HTML_UNDEF }, "downdiagonalstrike", mn_downdiagonalstrike },
    { { XHTML_1_0 }, { HTML_UNDEF }, "verticalstrike", mn_verticalstrike },
    { { XHTML_1_0 }, { HTML_UNDEF }, "horizontalstrike", mn_horizontalstrike },
    { { HTML_5_2 }, { HTML_UNDEF }, "phasorangle", mn_phasorangle },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_uparrow", mn_uparrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_rightarrow", mn_rightarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_downarrow", mn_downarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_leftarrow", mn_leftarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_northwestarrow", mn_northwestarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_southwestarrow", mn_southwestarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_southeastarrow", mn_southeastarrow },
    { { HTML_5_2 }, { HTML_UNDEF }, "northeastarrow", mn_northeastarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_updownarrow", mn_updownarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_leftrightarrow", mn_leftrightarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_northwestsoutheastarrow", mn_northwestsoutheastarrow },
    { { HTML_5_2, 0, HE_M3_NONSTAND }, { HTML_UNDEF }, "mn_northeastsouthwestarrow", mn_northeastsouthwestarrow },
    { { HTML_5_2 }, { HTML_UNDEF }, "madruwb", mn_madruwb } };

struct symbol_entry < html_version, e_mathvariant > mathvariant_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "normal", mv_normal },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bold", mv_bold },
    { { XHTML_1_0 }, { HTML_UNDEF }, "italic", mv_italic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bold-italic", mv_bolditalic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "double-struck", mv_doublestruck },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bold-fraktur", mv_boldfraktur },
    { { XHTML_1_0 }, { HTML_UNDEF }, "script", mv_script },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bold-script", mv_boldscript },
    { { XHTML_1_0 }, { HTML_UNDEF }, "fraktur", mv_fraktur },
    { { XHTML_1_0 }, { HTML_UNDEF }, "sans-serif", mv_sansserif },
    { { XHTML_1_0 }, { HTML_UNDEF }, "bold-sans-serif", mv_boldsansserif },
    { { XHTML_1_0 }, { HTML_UNDEF }, "sans-serif-italic", mv_sansserifitalic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "sans-serif-bold-italic", mv_sansserifbolditalic },
    { { XHTML_1_0 }, { HTML_UNDEF }, "monospace", mv_monospace },
    { { HTML_5_2 }, { HTML_UNDEF }, "initial", mv_initial },
    { { HTML_5_2 }, { HTML_UNDEF }, "tailed", mv_tailed },
    { { HTML_5_2 }, { HTML_UNDEF }, "looped", mv_looped },
    { { HTML_5_2 }, { HTML_UNDEF }, "stretched", mv_stretched } };

struct symbol_entry < html_version, e_matrixtype > matrixtype_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "matrix", mt_matrix },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "saturate", mt_saturate },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "hueRotate", mt_huerotate },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "luminanceToAlpha", mt_luminancetoalpha } };

struct symbol_entry < html_version, e_method > method_symbol_table [] =
{   { { HTML_PLUS }, { HTML_PLUS }, "delete", md_delete },
    { { HTML_JUL12, HV_NOT50 | HV_NOT51 }, { HTML_UNDEF }, "dialog", md_dialogue },
    { { HTML_PLUS }, { HTML_UNDEF }, "get", md_get },
    { { HTML_PLUS }, { HTML_UNDEF }, "post", md_post },
    { { HTML_PLUS }, { HTML_PLUS }, "put", md_put } };

struct symbol_entry < html_version, e_mf_identifier > mf_identifier_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "model", mfi_model },
    { { HTML_4_0 }, { HTML_UNDEF }, "mpn", mfi_mpn },
    { { HTML_4_0 }, { HTML_UNDEF }, "upc", mfi_upc },
    { { HTML_4_0 }, { HTML_UNDEF }, "isbn", mfi_isbn },
    { { HTML_4_0 }, { HTML_UNDEF }, "issn", mfi_issn },
    { { HTML_4_0 }, { HTML_UNDEF }, "ean", mfi_ean },
    { { HTML_4_0 }, { HTML_UNDEF }, "jan", mfi_jan },
    { { HTML_4_0 }, { HTML_UNDEF }, "place", mfi_sn },
    { { HTML_4_0 }, { HTML_UNDEF }, "mvin", mfi_vin },
    { { HTML_4_0 }, { HTML_UNDEF }, "msku", mfi_sku } };

struct symbol_entry < html_version, e_mf_itemtype > mf_itemtype_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "opening", mfit_opening },
    { { HTML_4_0 }, { HTML_UNDEF }, "housing", mfit_housing },
    { { HTML_4_0 }, { HTML_UNDEF }, "product", mfit_product },
    { { HTML_4_0 }, { HTML_UNDEF }, "business", mfit_business },
    { { HTML_4_0 }, { HTML_UNDEF }, "event", mfit_event },
    { { HTML_4_0 }, { HTML_UNDEF }, "person", mfit_person },
    { { HTML_4_0 }, { HTML_UNDEF }, "place", mfit_place },
    { { HTML_4_0 }, { HTML_UNDEF }, "website", mfit_website },
    { { HTML_4_0 }, { HTML_UNDEF }, "url", mfit_url } };

struct symbol_entry < html_version, e_mf_listing_action > mf_listing_action_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "sell", mfla_sell },
    { { HTML_4_0 }, { HTML_UNDEF }, "rent", mfla_rent },
    { { HTML_4_0 }, { HTML_UNDEF }, "trade", mfla_trade },
    { { HTML_4_0 }, { HTML_UNDEF }, "meet", mfla_meet },
    { { HTML_4_0 }, { HTML_UNDEF }, "announce", mfla_announce },
    { { HTML_4_0 }, { HTML_UNDEF }, "offer", mfla_offer },
    { { HTML_4_0 }, { HTML_UNDEF }, "wanted", mfla_wanted },
    { { HTML_4_0 }, { HTML_UNDEF }, "event", mfla_event },
    { { HTML_4_0 }, { HTML_UNDEF }, "service", mfla_service } };

struct symbol_entry < html_version, e_mf_method > mf_method_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "publish", mfm_publish },
    { { HTML_4_0 }, { HTML_UNDEF }, "request", mfm_request },
    { { HTML_4_0 }, { HTML_UNDEF }, "reply", mfm_reply },
    { { HTML_4_0 }, { HTML_UNDEF }, "add", mfm_add },
    { { HTML_4_0 }, { HTML_UNDEF }, "cancel", mfm_cancel },
    { { HTML_4_0 }, { HTML_UNDEF }, "refresh", mfm_refresh },
    { { HTML_4_0 }, { HTML_UNDEF }, "counter", mfm_counter },
    { { HTML_4_0 }, { HTML_UNDEF }, "declinecounter", mfm_declinecounter } };

struct symbol_entry < html_version, e_mf_reviewtype > mf_reviewtype_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, "product", mfr_product },
    { { HTML_4_0 }, { HTML_UNDEF }, "business", mfr_business },
    { { HTML_4_0 }, { HTML_UNDEF }, "event", mfr_event },
    { { HTML_4_0 }, { HTML_UNDEF }, "person", mfr_person },
    { { HTML_4_0 }, { HTML_UNDEF }, "place", mfr_place },
    { { HTML_4_0 }, { HTML_UNDEF }, "website", mfr_website },
    { { HTML_4_0 }, { HTML_UNDEF }, "url", mfr_url } };

struct symbol_entry < html_version, e_myersbriggs > myersbriggs_symbol_table [] =
        // why not the astrology stuff too?
{   { { XHTML_1_0 }, { HTML_UNDEF }, "INFP", mb_INFP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ESFP", mb_ESFP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "INTJ", mb_INTJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ESFJ", mb_ESFJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "INTP", mb_INTP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ENFP", mb_ENFP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ISTJ", mb_ISTJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ESTP", mb_ESTP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "INFJ", mb_INFJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ENFJ", mb_ENFJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ISTP", mb_ISTP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ENTJ", mb_ENTJ },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ISFP", mb_ISFP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ENTP", mb_ENTP },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ISFJ", mb_ISFJ } };

struct symbol_entry < html_version, e_namedspace > namedspace_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "negativeveryverythinmathspace", nd_negativeveryverythinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativeverythinmathspace", nd_negativeverythinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativethinmathspace", nd_negativethinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativemediummathspace", nd_negativemediummathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativethickmathspace", nd_negativethickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativeverythickmathspace", nd_negativeverythickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "negativeveryverythickmathspace", nd_negativeveryverythickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "veryverythinmathspace", nd_veryverythinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "verythinmathspace", nd_verythinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "thinmathspace", nd_thinmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "mediummathspace", nd_mediummathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "thickmathspace", nd_thickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "verythickmathspace", nd_verythickmathspace },
    { { XHTML_1_0 }, { HTML_UNDEF }, "veryverythickmathspace", nd_veryverythickmathspace } };

struct symbol_entry < html_version, e_namespace > namespace_symbol_table [] =
{   { { XHTML_1_0 }, { HTML_UNDEF }, "bibo", ns_bibo },
    { { XHTML_1_0 }, { HTML_UNDEF }, "cc", ns_cc },
    { { XHTML_1_0 }, { HTML_UNDEF }, "crs", ns_crs },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dbp", ns_dbp },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dbp_owl", ns_dbp_owl },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dbr", ns_dbr },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dc", ns_dc },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dcterms", ns_dcterms },
    { { XHTML_1_0 }, { HTML_UNDEF }, "dt", ns_dt },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ebuttm", ns_ebuttm },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ebutts", ns_ebutts },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ex", ns_ex },
    { { XHTML_1_0 }, { HTML_UNDEF }, "exsl", ns_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, "fn", ns_fn },
    { { XHTML_1_0 }, { HTML_UNDEF }, "fo", ns_fo },
    { { XHTML_1_0 }, { HTML_UNDEF }, "foaf", ns_foaf },
    { { XHTML_1_0 }, { HTML_UNDEF }, "html", ns_html },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ims", ns_ims },
    { { XHTML_1_0 }, { HTML_UNDEF }, "its", ns_its },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ittm", ns_ittm },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ittp", ns_ittp },
    { { XHTML_1_0 }, { HTML_UNDEF }, "itts", ns_itts },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ittx", ns_ittx },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ittxi", ns_ittxi },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ittxt", ns_ittxt },
    { { XHTML_1_0 }, { HTML_UNDEF }, "math", ns_math },
    { { XHTML_1_0 }, { HTML_UNDEF }, "odd", ns_odd },
    { { XHTML_1_0 }, { HTML_UNDEF }, "oex", ns_oex },
    { { XHTML_1_0 }, { HTML_UNDEF }, "owl", ns_owl },
    { { XHTML_1_0 }, { HTML_UNDEF }, "owlxml", ns_owlxml },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rddl", ns_rddl },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rdf", ns_rdf },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rdfa", ns_rdfa },
    { { XHTML_1_0 }, { HTML_UNDEF }, "rdfs", ns_rdfs },
    { { XHTML_1_0 }, { HTML_UNDEF }, "saxon", ns_saxon },
    { { XHTML_1_0 }, { HTML_UNDEF }, "smil", ns_smil },
    { { XHTML_1_0 }, { HTML_UNDEF }, "smpte", ns_smpte },
    { { XHTML_1_0 }, { HTML_UNDEF }, "svg", ns_svg },
    { { XHTML_1_0 }, { HTML_UNDEF }, "tt", ns_tt },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ttf", ns_ttf },
    { { XHTML_1_0 }, { HTML_UNDEF }, "ttp", ns_ttp },
    { { XHTML_1_0 }, { HTML_UNDEF }, "tts", ns_tts },
    { { XHTML_1_0 }, { HTML_UNDEF }, "v", ns_v },
    { { XHTML_1_0 }, { HTML_UNDEF }, "vcard", ns_vcard },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xalan", ns_xalan },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xf", ns_xf },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xhtml", ns_xhtml },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xhv", ns_xhv },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xi", ns_xi },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xlink", ns_xlink },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xmlevents", ns_xmlevents },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xmlns", ns_xmlns },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xs", ns_xs },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xsi", ns_xsi },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xslt", ns_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, "xtm", ns_xtm } };

struct symbol_entry < html_version, e_nit_macro > nit_macro_symbol_table [] =
{   { { HTML_TAGS }, { HTML_UNDEF }, "class-count", nm_class_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-decl-count", nm_class_decl_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-decl-int", nm_class_decl_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-int", nm_class_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-name", nm_class_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-title", nm_class_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "compile-time", nm_compile_time },
    { { HTML_TAGS }, { HTML_UNDEF }, "config", nm_config },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-article", nm_context_article },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-body", nm_context_body },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-build", nm_context_build },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-case", nm_context_case },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-cgi", nm_context_cgi },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-classic", nm_context_classic },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-clear", nm_context_clear },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-config", nm_context_config },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-copy", nm_context_copy },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-corpus", nm_context_corpus },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-crosslinks", nm_context_crosslinks },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css", nm_context_css },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-animation", nm_context_css_animation },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-background", nm_context_css_background },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-box-alignment", nm_context_css_box_align },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-box-model", nm_context_css_box_model },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-box-sizing", nm_context_css_box_sizing },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-cascade", nm_context_css_cascade },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-colour", nm_context_css_colour },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-compositing", nm_context_css_compositing },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-conditional-rule", nm_context_css_cond_rule },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-counter-style", nm_context_css_cs },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-custom", nm_context_css_custom },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-display", nm_context_css_display },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-ease", nm_context_css_ease },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-extension", nm_context_css_extension },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-fbl", nm_context_css_fbl },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-font", nm_context_css_font },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-fragmentation", nm_context_css_fragmentation },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-grid", nm_context_css_grid },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-image", nm_context_css_image },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-media", nm_context_css_media },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-multi-column", nm_context_css_multi_column },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-namespace", nm_context_css_namespace },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-overflow", nm_context_css_overflow },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-position", nm_context_css_position },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-selector", nm_context_css_selector },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-shape", nm_context_css_shape },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-style", nm_context_css_style },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-syntax", nm_context_css_syntax },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-table", nm_context_css_table },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-transition", nm_context_css_transition },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-ui", nm_context_css_ui },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-value", nm_context_css_value },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-version", nm_context_css_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-css-writing-mode", nm_context_css_writing_mode },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-custom-elements", nm_context_custom_elements },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-dc", nm_context_dc },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-example", nm_context_example },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-export-root", nm_context_export_root },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-exports", nm_context_exports },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-extensions", nm_context_extensions },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-ext-css", nm_context_ext_css },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-extra", nm_context_extra },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-foaf", nm_context_foaf },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-force-version", nm_context_force_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-forward", nm_context_forward },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-thread", nm_context_fred },
    { { HTML_TAGS }, { HTML_UNDEF }, "general-info", nm_general_info },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-icu", nm_context_icu },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-ignore", nm_context_ignore },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-info", nm_context_info },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-index", nm_context_index },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-jsonld", nm_context_jsonld },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-jsonld-extension", nm_context_jsonld_extension },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-jsonld-version", nm_context_jsonld_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-lang", nm_context_lang },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-links", nm_context_links },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-local", nm_context_local },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-main", nm_context_main },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-math", nm_context_math },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-max-file-size", nm_context_max_file_size },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-md-export", nm_context_md_export },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-meta", nm_context_meta },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-mf-export", nm_context_mf_export },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-mf-verify", nm_context_mf_verify },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-mf-version", nm_context_mf_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-microdata", nm_context_microdata },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-msg", nm_context_msg },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-no-ex-check", nm_context_no_ex_check },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-once", nm_context_once },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-output", nm_context_output },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-persisted", nm_context_persisted },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rdfa", nm_context_rdfa },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rdf-version", nm_context_rdf_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rel", nm_context_rel },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-report", nm_context_report },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rfc-1867", nm_context_rfc_1867 },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rfc-1942", nm_context_rfc_1942 },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rfc-1980", nm_context_rfc_1980 },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-rfc-2070", nm_context_rfc_2070 },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-root", nm_context_root },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-schema", nm_context_schema },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-schema-version", nm_context_ontology_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-comment", nm_context_shadow_comment },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-changed", nm_context_shadow_changed },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-enable", nm_context_shadow_enable },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-ignore", nm_context_shadow_ignore },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-persist", nm_context_shadow_persist },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-root", nm_context_shadow_root },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-ssi", nm_context_shadow_ssi },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadow-space", nm_context_shadow_space },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-shadows", nm_context_shadows },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-site", nm_context_site },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-slob", nm_context_slob },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-spec", nm_context_spec },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-spell", nm_context_spell },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-spell-path", nm_context_spell_path },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-spellings", nm_context_spellings },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-ssi", nm_context_ssi },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-stats-export", nm_context_stats_export },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-stats-page", nm_context_stats_page },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-stats-summary", nm_context_stats_summary },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-svg-version", nm_context_svg_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-tags", nm_context_tags },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-test", nm_context_test },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-title", nm_context_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-unknown-class", nm_context_unknown_class },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-virtuals", nm_context_virtuals },
    { { HTML_TAGS }, { HTML_UNDEF }, "context-xsd", nm_context_xsd },
    { { HTML_TAGS }, { HTML_UNDEF }, "copyright-addr", nm_copy_addr },
    { { HTML_TAGS }, { HTML_UNDEF }, "copyright-html", nm_copy_html },
    { { HTML_TAGS }, { HTML_UNDEF }, "copyright-text", nm_copy_text },
    { { HTML_TAGS }, { HTML_UNDEF }, "general-output", nm_general_output },
    { { HTML_TAGS }, { HTML_UNDEF }, "general-path", nm_general_path },
    { { HTML_TAGS }, { HTML_UNDEF }, "grand-title", nm_grand_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "html-snippet", nm_html_snippet },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-count", nm_id_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-decl-count", nm_id_decl_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-decl-int", nm_id_decl_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-int", nm_id_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-name", nm_id_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-title", nm_id_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-line", nm_itemid_line },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-name", nm_itemid_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-page", nm_itemid_page },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-title", nm_itemid_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "level-name", nm_level_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "level-symbol", nm_level_symbol },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-after", nm_nit_after },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-before", nm_nit_before },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-code", nm_nit_code },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-doc", nm_nit_doc },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-long", nm_nit_doc_long },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-explanation", nm_nit_explanation },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-id", nm_nit_id },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-line", nm_nit_line },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-mote", nm_nit_mote },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-ns", nm_nit_ns },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit-ref", nm_nit_ref },
    { { HTML_TAGS }, { HTML_UNDEF }, "nits-format", mn_nits_format },
    { { HTML_TAGS }, { HTML_UNDEF }, "nits-lost", mn_nits_lost },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-error", nm_page_error },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-name", nm_page_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-disk-path", nm_page_disk_path },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-site-path", nm_page_site_path },
    { { HTML_TAGS }, { HTML_UNDEF }, "prog-abbrev", nm_prog_abbrev },
    { { HTML_TAGS }, { HTML_UNDEF }, "prog-build", nm_prog_build },
    { { HTML_TAGS }, { HTML_UNDEF }, "prog-fullname", nm_prog_fullname },
    { { HTML_TAGS }, { HTML_UNDEF }, "prog-version", nm_prog_version },
    { { HTML_TAGS }, { HTML_UNDEF }, "prog-addr", nm_prog_webaddr },
    { { HTML_TAGS }, { HTML_UNDEF }, "query", nm_query },
    { { HTML_TAGS }, { HTML_UNDEF }, "run-args", nm_run_args },
    { { HTML_TAGS }, { HTML_UNDEF }, "run-catastrophe", nm_run_catastrophe },
    { { HTML_TAGS }, { HTML_UNDEF }, "run-environment", nm_run_environment },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-count", nm_stat_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-detail", nm_stat_detail },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-int", nm_stat_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-name", nm_stat_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-subname", nm_stat_subname },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-subcount", nm_stat_subcount },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-subdetail", nm_stat_subdetail },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-subint", nm_stat_subint },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-subtitle", nm_stats_subtitle },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-title", nm_stats_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-total", nm_stats_total },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-count", nm_tally_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-decl-count", nm_tally_decl_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-decl-int", nm_tally_decl_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-int", nm_tally_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-name", nm_tally_name },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-sum", nm_tally_sum },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-title", nm_tally_title },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-total", nm_tally_total },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-use-count", nm_tally_use_count },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-use-int", nm_tally_use_int },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-use-sum", nm_tally_use_sum },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-use-total", nm_tally_use_total },
    { { HTML_TAGS }, { HTML_UNDEF }, "time-duration", nm_time_duration },
    { { HTML_TAGS }, { HTML_UNDEF }, "time-finish", nm_time_finish },
    { { HTML_TAGS }, { HTML_UNDEF }, "time-start", nm_time_start } };

struct symbol_entry < html_version, e_nit_section > nit_section_symbol_table [] =
{   { { HTML_TAGS }, { HTML_UNDEF }, "class", ns_class },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-foot", ns_class_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "class-head", ns_class_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "config", ns_config },
    { { HTML_TAGS }, { HTML_UNDEF }, "config-foot", ns_config_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "config-head", ns_config_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "doc-foot", ns_doc_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "doc-head", ns_doc_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "export", ns_export },
    { { HTML_TAGS }, { HTML_UNDEF }, "export-foot", ns_export_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "export-head", ns_export_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "grand-foot", ns_grand_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "grand-head", ns_grand_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "id", ns_nsid },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-foot", ns_id_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "id-head", ns_id_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid", ns_itemid },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-foot", ns_itemid_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "itemid-head", ns_itemid_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "init", ns_init },
    { { HTML_TAGS }, { HTML_UNDEF }, "init-foot", ns_init_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "init-head", ns_init_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "link", ns_link },
    { { HTML_TAGS }, { HTML_UNDEF }, "link-foot", ns_link_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "link-head", ns_link_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "nit", ns_nit },
    { { HTML_TAGS }, { HTML_UNDEF }, "nits-foot", ns_nits_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "nits-head", ns_nits_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "nits-page", ns_nits_page },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-foot", ns_page_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "page-head", ns_page_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "shadow", ns_shadow },
    { { HTML_TAGS }, { HTML_UNDEF }, "shadow-foot", ns_shadow_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "shadow-head", ns_shadow_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat", ns_stat },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-foot", ns_stats_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-head", ns_stats_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "stat-sub", ns_substat },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-subfoot", ns_stats_subfoot },
    { { HTML_TAGS }, { HTML_UNDEF }, "stats-subhead", ns_stats_subhead },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally", ns_tally },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-foot", ns_tally_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "tally-head", ns_tally_head },
    { { HTML_TAGS }, { HTML_UNDEF }, "update", ns_update },
    { { HTML_TAGS }, { HTML_UNDEF }, "update-foot", ns_update_foot },
    { { HTML_TAGS }, { HTML_UNDEF }, "update-head", ns_update_head } };

struct symbol_entry < html_version, e_ogtype > ogtype_symbol_table [] =
{   { { HTML_OG_2010 }, { HTML_DEC11 }, "activity", og_activity },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "actor", og_actor },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "album", og_album },
    { { HTML_OG_2010 }, { HTML_UNDEF }, "article", og_article },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "athlete", og_athlete },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "author", og_author },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "band", og_band },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "bar", og_bar },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "blog", og_blog },
    { { HTML_OG_2010 }, { HTML_UNDEF }, "book", og_book },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "cafe", og_cafe },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "cause", og_cause },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "company", og_company },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "city", og_city },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "country", og_country },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "director", og_director },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "drink", og_drink },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "food", og_food },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "game", og_game },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "government", og_government },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "hotel", og_hotel },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "landmark", og_landmark },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "movie", og_movie },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "musician", og_musician },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "music.song", og_musicsong },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "music.album", og_musicalbum },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "music.playlist", og_musicplaylist },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "music.radio_station", og_musicradiostation },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "product", og_product },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "non_profit", og_non_profit },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "politician", og_politician },
    { { HTML_OG_2010 }, { HTML_UNDEF }, "profile", og_profile },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "public_figure", og_public_figure },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "restaurant", og_restaurant },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "school", og_school },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "song", og_song },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "sport", og_sport },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "sports_league", og_sports_league },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "sports_team", og_sports_team },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "state_province", og_state_province },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "tv_show", og_tv_show },
    { { HTML_OG_2010 }, { HTML_DEC11 }, "university", og_university },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "video.movie", og_videomovie },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "video.episode", og_videoepisode },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "video.tv_show", og_videotvshow },
    { { HTML_OG_2012 }, { HTML_UNDEF }, "video.other", og_videoother },
    { { HTML_OG_2010 }, { HTML_UNDEF }, "website", og_website } };

struct symbol_entry < html_version, e_page_orientation > page_orientation_symbol_table [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "-270", po_270 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "-180", po_180 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "-90-fill", po_90  },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "0", po0 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "90", po90 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "180", po180 },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "270", po270 } };

struct symbol_entry < html_version, e_paintkeyword > paintkeyword_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "none", pk_none },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "child", pk_child },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "context-fill", pk_contextfill  },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "context-stroke", pk_contextstroke },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "currentColor", pk_currentcolour },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "inherit", pk_inherit },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "icc-colour", pk_icccolour },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "url", pk_url } };

struct symbol_entry < html_version, e_plusstyle > plusstyle_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "b", ps_b },
    { { HTML_UNDEF }, { HTML_UNDEF }, "i", ps_i },
    { { HTML_UNDEF }, { HTML_UNDEF }, "p", ps_p },
    { { HTML_UNDEF }, { HTML_UNDEF }, "s", ps_s },
    { { HTML_UNDEF }, { HTML_UNDEF }, "sub", ps_sub },
    { { HTML_UNDEF }, { HTML_UNDEF }, "sup", ps_sup },
    { { HTML_UNDEF }, { HTML_UNDEF }, "tt", ps_tt },
    { { HTML_UNDEF }, { HTML_UNDEF }, "u", ps_u } };

struct symbol_entry < html_version, e_pointer_events > pointer_events_symbol_table [] =
{   { { HTML_SVG21, 0, HE_SVG_21 }, { HTML_UNDEF }, "auto", pe_auto },
    { { HTML_SVG12, 0, HE_SVG_12 }, { HTML_UNDEF }, "boundingBox", pe_boundingbox },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "bounding-box", pe_bounding_box },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "visiblePainted", pe_visiblepainted },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "visibleFill", pe_visiblefill },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "visibleStroke", pe_visiblestroke },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "visible", pe_visible },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "painted", pe_painted },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "fill", pe_fill },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "stroke", pe_stroke },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "all", pe_all },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "none", pe_none },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", pe_inherit } };

// a couple of these are only defined in the HTML+ text, not the DTD
struct symbol_entry < html_version, e_print > print_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "footnote", pt_footnote },
    { { HTML_UNDEF }, { HTML_UNDEF }, "reference", pt_reference },
    { { HTML_UNDEF }, { HTML_UNDEF }, "section", pt_section },
    { { HTML_UNDEF }, { HTML_UNDEF }, "sidebar", pt_sidebar },
    { { HTML_UNDEF }, { HTML_UNDEF }, "silent", pt_silent } };

struct symbol_entry < html_version, e_quote_style > quote_style_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "none", qs_none },
    { { HTML_UNDEF }, { HTML_UNDEF }, "c", qs_c },
    { { HTML_UNDEF }, { HTML_UNDEF }, "csv", qs_csv },
    { { HTML_UNDEF }, { HTML_UNDEF }, "double", qs_double },
    { { HTML_UNDEF }, { HTML_UNDEF }, "html", qs_html },
    { { HTML_UNDEF }, { HTML_UNDEF }, "single", qs_single } };

struct symbol_entry < html_version, e_referrer > referrer_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "no-referrer", rf_no },
    { { HTML_UNDEF }, { HTML_UNDEF }, "no-referrer-when-downgrade", rf_downgrade },
    { { HTML_UNDEF }, { HTML_UNDEF }, "same-origin", rf_same },
    { { HTML_UNDEF }, { HTML_UNDEF }, "origin", rf_origin },
    { { HTML_UNDEF }, { HTML_UNDEF }, "strict-origin", rf_strict },
    { { HTML_UNDEF }, { HTML_UNDEF }, "strict-origin-when-cross-origin", rf_strictcross },
    { { HTML_UNDEF }, { HTML_UNDEF }, "origin-when-cross-origin", rf_cross },
    { { HTML_UNDEF }, { HTML_UNDEF }, "unsafe-url", rf_unsafe } };

struct symbol_entry < html_version, e_rendering_in_tents > rendering_in_tents_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "auto", ri_auto },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "perceptual", ri_perceptual },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "relative-colorimetric", ri_relativecolourimetric },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "saturation", ri_saturation },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "absolute-colorimetric", ri_absolutecolourimetric } };

struct symbol_entry < html_version, e_rules > rules_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "none", ru_none },
    { { HTML_2_0 }, { HTML_UNDEF }, "groups", ru_groups },
    { { HTML_2_0 }, { HTML_UNDEF }, "rows", ru_rows },
    { { HTML_2_0 }, { HTML_UNDEF }, "cols", ru_cols },
    { { HTML_2_0 }, { HTML_UNDEF }, "all", ru_all } };

struct symbol_entry < html_version, e_sandbox > sandbox_symbol_table [] =
{   { { HTML_JUL20, 0, HE_EXPERIMENTAL }, { HTML_UNDEF }, "allow-downloads-without-user-activation", sand_adwua },
    { { HTML_JUL08, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-forms", sand_forms },
    { { HTML_JAN16, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-modals", sand_modals },
    { { HTML_JUL16, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-orientation-lock", sand_orientation },
    { { HTML_JAN13, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-pointer-lock", sand_pointer },
    { { HTML_JUL12, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-popups", sand_popups },
    { { HTML_JAN16, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-popups-to-escape-sandbox", sand_popupescape },
    { { HTML_JUL16, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-presentation", sand_presentation },
    { { HTML_JUL08, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-same-origin", sand_origin },
    { { HTML_JUL08, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-scripts", sand_scripts },
    { { HTML_JUL20, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-storage-access-by-user-activation", sand_asabua },
    { { HTML_JAN11, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-top-navigation", sand_navigation },
    { { HTML_JUL17, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-top-navigation-by-user-activation", sand_atnbua },
    { { HTML_APR22, 0, HV_CSP_1 }, { HTML_UNDEF }, "allow-top-navigation-to-custom-protocols", sand_atntcp },
    { { HTML_JUL20 }, { HTML_UNDEF }, "allow-downloads", sand_ad } };

struct symbol_entry < html_version, e_scei > scei_symbol_table [] =
{   { { HTML_SVG12, 0, HE_SVG_12_FULL  }, { HTML_UNDEF }, "after", scei_after },
    { { HTML_SVG12, 0, HE_SVG_12_FULL  }, { HTML_UNDEF }, "before", scei_before },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "center", scei_centre },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "end", scei_end },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "start", scei_start },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", scei_inherit } };

struct symbol_entry < html_version, e_severity > severity_symbol_table [] =
{   { { HTML_TAGS }, { HTML_UNDEF }, CATASTROPHE, es_catastrophic },
    { { HTML_TAGS }, { HTML_UNDEF }, ERR, es_error },
    { { HTML_TAGS }, { HTML_UNDEF }, WARNING, es_warning },
    { { HTML_TAGS }, { HTML_UNDEF }, INFO, es_info },
    { { HTML_TAGS }, { HTML_UNDEF }, COMMENT, es_comment },
    { { HTML_TAGS }, { HTML_UNDEF }, DBG, es_debug },
    { { HTML_TAGS }, { HTML_UNDEF }, VARIABLE, es_variable },
    { { HTML_TAGS }, { HTML_UNDEF }, STRUCTURE, es_structure },
    { { HTML_TAGS }, { HTML_UNDEF }, DETAIL, es_detail },
    { { HTML_TAGS }, { HTML_UNDEF }, SPLURGE, es_splurge },
    { { HTML_TAGS }, { HTML_UNDEF }, ALL, es_all } };

struct symbol_entry < html_version, e_shadow > shadow_symbol_table [] =
{   { { HTML_TAGS }, { HTML_UNDEF }, "no", sh_no },
    { { HTML_TAGS }, { HTML_UNDEF }, "pages", sh_pages },
#ifndef NOLYNX
    { { HTML_TAGS }, { HTML_UNDEF }, "hard", sh_hard },
    { { HTML_TAGS }, { HTML_UNDEF }, "soft", sh_soft },
#endif // NOLYNX
    { { HTML_TAGS }, { HTML_UNDEF }, "all", sh_copy },
    { { HTML_TAGS }, { HTML_UNDEF }, "dedu", sh_dedu },
    { { HTML_TAGS }, { HTML_UNDEF }, "report", sh_report } };

struct symbol_entry < html_version, e_shape7 > shape7_symbol_table [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, "circle", s7_circ },
    { { HTML_JAN05 }, { HTML_UNDEF }, "circ", s7_circ },
    { { HTML_JAN05 }, { HTML_UNDEF }, "default", s7_default },
    { { HTML_JAN05 }, { HTML_UNDEF }, "poly", s7_poly },
    { { HTML_JAN05 }, { HTML_UNDEF }, "polygon", s7_poly },
    { { HTML_JAN05 }, { HTML_UNDEF }, "rect", s7_rect },
    { { HTML_JAN05 }, { HTML_UNDEF }, "rectangle", s7_rect } };

struct symbol_entry < html_version, e_shape_rendering > shape_rendering_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "auto", sr_auto },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeSpeed", sr_optimisespeed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "crispEdges", sr_crispedges },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "geometricPrecision", sr_geometricprecision },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", sr_inherit } };

 struct symbol_entry < html_version, e_smei > smei_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "start", smei_start },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "middle", smei_middle },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "end", smei_end },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", smei_inherit } };

struct symbol_entry < html_version, e_ssi > ssi_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "comment", ssi_comment },
    { { HTML_UNDEF }, { HTML_UNDEF }, "config", ssi_config },
    { { HTML_UNDEF }, { HTML_UNDEF }, "echo", ssi_echo },
    { { HTML_UNDEF }, { HTML_UNDEF }, "elif", ssi_elif },
    { { HTML_UNDEF }, { HTML_UNDEF }, "else", ssi_else },
    { { HTML_UNDEF }, { HTML_UNDEF }, "endif", ssi_endif },
    { { HTML_UNDEF }, { HTML_UNDEF }, "exec", ssi_exec },
    { { HTML_UNDEF }, { HTML_UNDEF }, "fsize", ssi_fsize },
    { { HTML_UNDEF }, { HTML_UNDEF }, "flastmod", ssi_flastmod },
    { { HTML_UNDEF }, { HTML_UNDEF }, "if", ssi_if },
    { { HTML_UNDEF }, { HTML_UNDEF }, "include", ssi_include },
    { { HTML_UNDEF }, { HTML_UNDEF }, "printenv", ssi_printenv },
    { { HTML_UNDEF }, { HTML_UNDEF }, "set", ssi_set } };

struct symbol_entry < html_version, e_ssi_comparison > ssi_comparison_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "&&", ssi_comparison_and },
    { { HTML_UNDEF }, { HTML_UNDEF }, "=", ssi_comparison_eq },
    { { HTML_UNDEF }, { HTML_UNDEF }, "==", ssi_comparison_eq },
    { { HTML_UNDEF }, { HTML_UNDEF }, ">=", ssi_comparison_ge },
    { { HTML_UNDEF }, { HTML_UNDEF }, ">", ssi_comparison_gt },
    { { HTML_UNDEF }, { HTML_UNDEF }, "<=", ssi_comparison_le },
    { { HTML_UNDEF }, { HTML_UNDEF }, "<", ssi_comparison_lt },
    { { HTML_UNDEF }, { HTML_UNDEF }, "!=", ssi_comparison_ne },
    { { HTML_UNDEF }, { HTML_UNDEF }, "<>", ssi_comparison_ne },
    { { HTML_UNDEF }, { HTML_UNDEF }, "||", ssi_comparison_or } };

struct symbol_entry < html_version, e_ssi_encoding > ssi_encoding_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "base64", ssi_encoding_base64 },
    { { HTML_UNDEF }, { HTML_UNDEF }, "entity", ssi_encoding_entity },
    { { HTML_UNDEF }, { HTML_UNDEF }, "none", ssi_encoding_none },
    { { HTML_UNDEF }, { HTML_UNDEF }, "url", ssi_encoding_url },
    { { HTML_UNDEF }, { HTML_UNDEF }, "urlencoded", ssi_encoding_urlencoded } };

struct symbol_entry < html_version, e_ssi_env > ssi_env_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "date_gmt", ssi_DATE_GMT },
    { { HTML_UNDEF }, { HTML_UNDEF }, "date_local", ssi_DATE_LOCAL },
    { { HTML_UNDEF }, { HTML_UNDEF }, "document_args", ssi_DOCUMENT_ARGS },
    { { HTML_UNDEF }, { HTML_UNDEF }, "document_name", ssi_DOCUMENT_NAME },
    { { HTML_UNDEF }, { HTML_UNDEF }, "document_path_info", ssi_DOCUMENT_PATH_INFO },
    { { HTML_UNDEF }, { HTML_UNDEF }, "document_uri", ssi_DOCUMENT_URI },
    { { HTML_UNDEF }, { HTML_UNDEF }, "last_modified", ssi_LAST_MODIFIED },
    { { HTML_UNDEF }, { HTML_UNDEF }, "query_string_unescaped", ssi_QUERY_STRING_UNESCAPED },
    { { HTML_UNDEF }, { HTML_UNDEF }, "user_name", ssi_USER_NAME } };

struct symbol_entry < html_version, e_step_position > step_position_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, "end", sp_end },
    { { HTML_UNDEF }, { HTML_UNDEF }, "jump-both", sp_jump_both },
    { { HTML_UNDEF }, { HTML_UNDEF }, "jump-end", sp_jump_end },
    { { HTML_UNDEF }, { HTML_UNDEF }, "jump-none", sp_jump_none },
    { { HTML_UNDEF }, { HTML_UNDEF }, "jump-start", sp_jump_start },
    { { HTML_UNDEF }, { HTML_UNDEF }, "start", sp_start } };

struct symbol_entry < html_version, e_svg_align > svg_align_symbol_table [] =
{   { { HTML_SVG10 }, { HTML_UNDEF }, "none", sa_none },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMinYMin", sa_xmin_ymin },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMidYMin", sa_xmid_ymin },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMaxYMin", sa_xmax_ymin },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMinYMid", sa_xmin_ymid },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMidYMid", sa_xmid_ymid },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMaxYMid", sa_xmax_ymid },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMinYMax", sa_xmin_ymax },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMidYMax", sa_xmid_ymax },
    { { HTML_SVG10 }, { HTML_UNDEF }, "xMaxYMax", sa_xmax_ymax } };

struct symbol_entry < html_version, e_svg_display > svg_display_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "inline",  ds_inline },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "block", ds_block },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "list-item", ds_listitem },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "run-in", ds_runin },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "compact", ds_compact },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "marker", ds_marker },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table", ds_table },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "inline-table", ds_inlinetable },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-row-group", ds_tablerowgroup },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-header-group", ds_tableheadergroup },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-footer-group", ds_tablefootergroup },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-row", ds_tablerow },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-column-group", ds_tablecolumngroup },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-column", ds_tablecolumn },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-cell", ds_tablecell },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "table-caption", ds_tablecaption },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "none", ds_none },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "inherit", ds_inherit } };

struct symbol_entry < html_version, e_svg_fontstretch > svg_fontstretch_symbol_table [] =
{   { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "all",  fst_all },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "normal",  fst_normal },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "wider",  fst_wider },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "narrower",  fst_narrower },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "ultra-condensed", fst_ultracondensed },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "extra-condensed", fst_extracondensed },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "condensed", fst_condensed },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "semi-condensed", fst_semicondensed },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "semi-expanded", fst_semiexpanded },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "expanded", fst_expanded },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "extra-expanded", fst_extraexpanded },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2_0 | H2_CSS_FONT_3 }, { HTML_UNDEF }, "ultra-expanded", fst_ultraexpanded },
    { { HTML_4_0, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", fst_inherit } };

struct symbol_entry < html_version, e_svg_fontstretch_ff > svg_fontstretch_ff_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "normal",  fff_normal },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "ultra-condensed",  fff_ultracondensed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "extra-condensed", fff_extracondensed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "condensed", fff_condensed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "semi-condensed", fff_semicondensed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "semi-expanded", fff_semiexpanded },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "expanded", fff_expanded },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "extra-expanded", fff_extraexpanded },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "ultra-expanded", fff_ultraexpanded } };

struct symbol_entry < html_version, e_svg_fontstyle > svg_fontstyle_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "normal",  sfs_normal },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "italic",  sfs_italic },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "oblique",  sfs_oblique },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", sfs_inherit } };

struct symbol_entry < html_version, e_svg_fontweight > svg_fontweight_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "normal",  fsw_normal },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "bold", fsw_bold },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "bolder", fsw_bolder },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "lighter", fsw_lighter },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "100", fsw_100 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "200", fsw_200 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "300", fsw_300 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "400", fsw_400 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "500", fsw_500 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "600", fsw_600 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "700", fsw_700 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "800", fsw_800 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "900", fsw_900 },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", fsw_inherit } };

struct symbol_entry < html_version, e_svg_fontweight_ff > svg_fontweight_ff_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "normal",  fsf_normal },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "bold", fsf_bold },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "100", fsf_100 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "200", fsf_200 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "300", fsf_300 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "400", fsf_400 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "500", fsf_500 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "600", fsf_600 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "700", fsf_700 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "800", fsf_800 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "900", fsf_900 } };

struct symbol_entry < html_version, e_svg_mode > svg_mode_symbol_table [] =
{   { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "color", sm_colour },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "colour-burn", sm_colour_burn },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "colour-dodge", sm_colour_dodge },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "darken", sm_darken },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "difference", sm_difference },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "exclusion", sm_exclusion },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "hard-light", sm_hard_light },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "hue", sm_hue },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "lighten", sm_lighten },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "luminosity", sm_luminosity },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "multiply", sm_multiply },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "normal", sm_normal },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "saturation", sm_saturation },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "screen", sm_screen },
    { { HTML_SVG20, 0, HE_SVG_2 }, { HTML_UNDEF }, "soft-light", sm_soft_light } };

struct symbol_entry < html_version, e_svg_overflow > svg_overflow_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "visible", sov_visible },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "hidden", sov_hidden },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "scroll", sov_scroll },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "auto", sov_auto },
    { { HTML_SVG10, 0, HE_SVG_10_11 }, { HTML_UNDEF }, "inherit", sov_inherit } };

struct symbol_entry < html_version, e_svg_rendering_intent > svg_rendering_intent_symbol_table [] =
{   { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, "absolute-colormetric", sri_absolute_colourmetric },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, "auto", sri_auto },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, "perceptual", sri_perceptual },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, "relative-colormetric", sri_relative_colourmetric },
    { { HTML_SVG11, 0, HE_SVG_11_2 }, { HTML_UNDEF }, "saturation", sri_saturation } };

struct symbol_entry < html_version, e_svg_type > svg_type_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "discrete", tsz_discrete },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "gamma", tsz_gamma },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "identity", tsz_identity },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "linear", tsz_linear },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "table", tsz_table } };

struct symbol_entry < html_version, e_svg_version > svg_version_symbol_table [] =
{   { { HTML_SVG10 }, { HTML_UNDEF }, "1.0", sv_1_0 },
    { { HTML_SVG10 }, { HTML_UNDEF }, "1.1", sv_1_1 },
    { { HTML_SVG10 }, { HTML_UNDEF }, "1.2", sv_1_2_tiny },
    { { HTML_SVG10 }, { HTML_UNDEF }, "1.2/tiny", sv_1_2_tiny },
    { { HTML_SVG10 }, { HTML_UNDEF }, "1.2/full", sv_1_2_full },
    { { HTML_SVG10 }, { HTML_UNDEF }, "2.0", sv_2_0 },
    { { HTML_SVG10 }, { HTML_UNDEF }, "2.1", sv_2_1 } };

struct symbol_entry < html_version, e_svg_version_grand > svg_version_grand_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, HTTP_W3 "/tr/rec-mathml-19980407", svg_1_0 }, // MathML ??
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "http:s//www.w3.org/tr/rec-mathml-19980407", svg_1_0 },
    { { HTML_SVG11, 0, HE_SVG }, { HTML_UNDEF }, HTTP_W3 "/graphics/svg/svg-19990706.dtd", svg_1_1 },
    { { HTML_SVG11, 0, HE_SVG }, { HTML_UNDEF }, HTTPS_W3 "/graphics/svg/svg-19990706.dtd", svg_1_1 },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTP SVG_2000, svg_2_0 },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTPS SVG_2000, svg_2_0 },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTP SVG_2000 "/tiny", svg_1_2_tiny },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTPS SVG_2000 "/tiny", svg_1_2_tiny },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTP SVG_2000 "/full", svg_1_2_full },
    { { HTML_SVG12, 0, HE_SVG }, { HTML_UNDEF }, HTTPS SVG_2000 "/full", svg_1_2_full } };

struct symbol_entry < html_version, e_tableframe > tableframe_symbol_table [] =
{   { { HTML_2_0 }, { HTML_UNDEF }, "void", fr_void },
    { { HTML_2_0 }, { HTML_UNDEF }, "above", fr_above },
    { { HTML_2_0 }, { HTML_UNDEF }, "below", fr_below },
    { { HTML_2_0 }, { HTML_UNDEF }, "hsides", fr_hsides },
    { { HTML_2_0 }, { HTML_UNDEF }, "lhs", fr_lhs },
    { { HTML_2_0 }, { HTML_UNDEF }, "rhs", fr_rhs },
    { { HTML_2_0 }, { HTML_UNDEF }, "vsides", fr_vsides },
    { { HTML_2_0 }, { HTML_UNDEF }, "box", fr_box },
    { { HTML_2_0 }, { HTML_UNDEF }, "border", fr_border } };

struct symbol_entry < html_version, e_tblri > tblri_symbol_table [] =
{   { { HTML_CSS }, { HTML_UNDEF }, "bottom", etb_bottom },
    { { HTML_CSS }, { HTML_UNDEF }, "inherit", etb_inherit },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "left", etb_left },
    { { HTML_CSS, 0, 0, H2_CSS_2_0 }, { HTML_UNDEF }, "right", etb_right },
    { { HTML_CSS }, { HTML_UNDEF }, "top", etb_top } };

struct symbol_entry < html_version, e_text_decoration > text_decoration_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "none", td_none },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "underline", td_underline },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "overline", td_overline },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "line-through", td_linethrough },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "blink", td_blink },
    { { HTML_SVG10, 0, HE_SVG_10_11_2 }, { HTML_UNDEF }, "inherit", td_inherit } };

struct symbol_entry < html_version, e_text_rendering > text_rendering_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "auto", tr_auto },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeSpeed", tr_optimisespeed },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "optimizeLegibility", tr_optimiselegibility },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "geometricPrecision", tr_geometricprecision },
    { { HTML_SVG10, 0, HE_SVG_1 }, { HTML_UNDEF }, "inherit", tr_inherit } };

struct symbol_entry < html_version, e_transform_anim > transform_anim_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "translate", ta_translate },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "scale", ta_scale },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "rotate", ta_rotate },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "skewX", ta_skewx },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "skewY", ta_skewy } };

struct symbol_entry < html_version, e_transformbehaviour > transformbehaviour_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "geometric", tb_geometric },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "pinned", tb_pinned },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "pinned90", tb_pinned90 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "pinned180", tb_pinned180 },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "pinned170", tb_pinned270 } };

struct symbol_entry < html_version, e_transform_fn > transform_fn_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (6) | HE_MAXARGS (6) }, { HTML_UNDEF }, "matrix", tr_matrix },
    { { HTML_SVG12, 0, HE_SVG_12 | HE_MINARGS (1) | HE_MAXARGS (3) }, { HTML_UNDEF }, "ref", tr_ref },
    { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (1) | HE_MAXARGS (2) }, { HTML_UNDEF }, "translate", tr_translate },
    { { HTML_SVG20, 0, HE_SVG_2 | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "translateX", tr_translatex },
    { { HTML_SVG20, 0, HE_SVG_2 | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "translateY", tr_translatey },
    { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (1) | HE_MAXARGS (2) }, { HTML_UNDEF }, "scale", tr_scale },
    { { HTML_SVG20, 0, HE_SVG_2 | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "scaleX", tr_scalex },
    { { HTML_SVG20, 0, HE_SVG_2 | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "scaleY", tr_scaley },
    { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (1) | HE_MAXARGS (3) }, { HTML_UNDEF }, "rotate", tr_rotate },
    { { HTML_SVG20, HV_DEPRECATED45, HE_SVG_2 | HE_MINARGS (2) | HE_MAXARGS (4) }, { HTML_UNDEF }, "skew", tr_skew },
    { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "skewX", tr_skewx },
    { { HTML_SVG10, 0, HE_SVG | HE_MINARGS (1) | HE_MAXARGS (1) }, { HTML_UNDEF }, "skewY", tr_skewy } };

struct symbol_entry < html_version, e_turbulence_type > turbulence_type_symbol_table [] =
{   { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "fractalNoise", tu_fractal_noise },
    { { HTML_SVG10, 0, HE_SVG }, { HTML_UNDEF }, "turbulence", tu_turbulence } };

struct symbol_entry < html_version, e_unicode_bidi > unicode_bidi_symbol_table [] =
 {  { { HTML_4_0, 0, HE_SVG, H2_CSS_2 | H2_CSS_SVG_2, H3_CSS_WRITING_3 }, { HTML_UNDEF }, "bidi-override", ub_bidioverride },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2 | H2_CSS_SVG_2, H3_CSS_WRITING_3 }, { HTML_UNDEF }, "embed", ub_embed },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2 | H2_CSS_SVG_2, H3_CSS_WRITING_3 }, { HTML_UNDEF }, "inherit", ub_inherit },
    { { HTML_SVG20, 0, HE_SVG_2, H2_CSS_2 | H2_CSS_SVG_2, H3_CSS_WRITING_3 }, { HTML_UNDEF }, "isolate", ub_isolate },
    { { HTML_CSS, 0, 0, 0, H3_CSS_WRITING_3 }, { HTML_UNDEF }, "isolate-override", ub_isolate_override },
    { { HTML_4_0, 0, HE_SVG, H2_CSS_2 | H2_CSS_SVG_2, H3_CSS_WRITING_3 }, { HTML_UNDEF }, "normal", ub_normal },
    { { HTML_SVG20, 0, HE_SVG_2, H2_CSS_2 | H2_CSS_SVG_2, H3_CSS_WRITING_3 }, { HTML_UNDEF }, "plaintext", ub_plaintext } };

struct symbol_entry < html_version, e_unit > unit_symbol_table [] =
{   { { HTML_JAN21 }, { HTML_UNDEF }, "cap", eu_cap },
    { { HTML_JUN19 }, { HTML_UNDEF }, "ch", eu_ch },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "cm", eu_cm },
    { { HTML_2_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "dpcm", eu_dpcm },
    { { HTML_2_0, 0, 0, H2_CSS_MEDIA_3 }, { HTML_UNDEF }, "dpi", eu_dpi },
    { { HTML_2_0, 0, 0, H2_CSS_MEDIA_4 }, { HTML_UNDEF }, "dppx", eu_dppx },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "em", eu_em },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "ex", eu_ex },
    { { HTML_JAN21 }, { HTML_UNDEF }, "ic", eu_ic },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "in", eu_in },
    { { HTML_JAN21 }, { HTML_UNDEF }, "lh", eu_lh },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "mm", eu_mm },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "pc", eu_pc },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "pt", eu_pt },
    { { HTML_2_0, 0, 0, H2_CSS }, { HTML_UNDEF }, "px", eu_px },
    { { HTML_JUN19 }, { HTML_UNDEF }, "Q", eu_q },
    { { HTML_JUN19 }, { HTML_UNDEF }, "rem", eu_rem },
    { { HTML_JAN21 }, { HTML_UNDEF }, "rlh", eu_rlh },
    { { HTML_JAN21 }, { HTML_UNDEF }, "vb", eu_vb },
    { { HTML_JUN19 }, { HTML_UNDEF }, "vh", eu_vh },
    { { HTML_JAN21 }, { HTML_UNDEF }, "vi", eu_vi },
    { { HTML_JUN19 }, { HTML_UNDEF }, "vmin", eu_vmin },
    { { HTML_JUN19 }, { HTML_UNDEF }, "vmax", eu_vmax },
    { { HTML_JUN19 }, { HTML_UNDEF }, "vw", eu_vw } };

struct symbol_entry < html_version, e_unit_abs_len > unit_abs_len_symbol_table [] =
{   { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "cm", eua_cm },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "in", eus_in },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "mm", eua_mm },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "pc", eua_mm },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "pt", eua_pt },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "px", eua_px },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "Q", eua_q } };

struct symbol_entry < html_version, e_unit_angle > unit_angle_symbol_table [] =
{   { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "deg", ean_deg },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "grad", ean_grad },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "rad", ean_rad },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "turn", ean_turn } };

struct symbol_entry < html_version, e_unit_freq > unit_freq_symbol_table [] =
{   { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "Hz", euf_hz },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "kHz", euf_khz } };

struct symbol_entry < html_version, e_unit_rel_len > unit_rel_len_symbol_table [] =
{   { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "em", eur_em },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "ex", eur_ex },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "ch", eur_ch },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "rem", eur_rem },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "vh", eur_vh },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "vmax", eur_vmax },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "vmin", eur_vmin },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "vw", eur_vw } };

struct symbol_entry < html_version, e_unit_res > unit_res_symbol_table [] =
{   { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "dpcm", eur_dpcm },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "dpi", eur_dpi },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "dppx", eur_dppx } };

struct symbol_entry < html_version, e_unit_time > unit_time_symbol_table [] =
{   { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "ms", eut_ms  },
    { { HTML_4_0, 0, 0, H2_CSS_VALUE_3 }, { HTML_UNDEF }, "s", eur_s } };

struct symbol_entry < html_version, e_vector_effect_2 > vector_effect_2_symbol_table [] =
{   { { HTML_SVG20 }, { HTML_UNDEF }, "fixed-position", v2_fixedposition },
    { { HTML_SVG20 }, { HTML_UNDEF }, "none", v2_none },
    { { HTML_SVG20 }, { HTML_UNDEF }, "non-rotation", v2_nonrotation },
    { { HTML_SVG20 }, { HTML_UNDEF }, "non-scaling-stroke", v2_nonscalingstroke },
    { { HTML_SVG20 }, { HTML_UNDEF }, "non-scaling-size", v2_nonscalingsize } };

struct symbol_entry < html_version, e_vertical_align_enum > vertical_align_enum_symbol_table [] =
{   { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "baseline", eva_baseline },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "sub", eva_sub },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "super", eva_super },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "text-top", eva_text_top },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "middle", eva_middle },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "bottom", eva_bottom },
    { { HTML_SVG12, 0, HE_SVG_FULL_2 }, { HTML_UNDEF }, "text-bottom", eva_text_bottom },
    { { HTML_SVG12, 0, HE_SVG_12_FULL }, { HTML_UNDEF }, "inherit", eva_inherit } };

struct symbol_entry < html_version, e_vgender > vgender_symbol_table [] =
{   { { HTML_VCARD }, { HTML_UNDEF }, "female", vg_female },
    { { HTML_VCARD }, { HTML_UNDEF }, "male", vg_male },
    { { HTML_VCARD }, { HTML_UNDEF }, "none", vg_none },
    { { HTML_VCARD }, { HTML_UNDEF }, "other", vg_other },
    { { HTML_VCARD }, { HTML_UNDEF }, "unknown", vg_unknown } };

struct symbol_entry < html_version, e_vrel > vrel_symbol_table [] =
{   { { HTML_VCARD }, { HTML_UNDEF }, "acquaintance", vr_acquaintance },
    { { HTML_VCARD }, { HTML_UNDEF }, "agent", vr_agent },
    { { HTML_VCARD }, { HTML_UNDEF }, "child", vr_child },
    { { HTML_VCARD }, { HTML_UNDEF }, "colleague", vr_colleague },
    { { HTML_VCARD }, { HTML_UNDEF }, "contact", vr_contact },
    { { HTML_VCARD }, { HTML_UNDEF }, "coresident", vr_coresident },
    { { HTML_VCARD }, { HTML_UNDEF }, "coworker", vr_coworker },
    { { HTML_VCARD }, { HTML_UNDEF }, "crush", vr_crush },
    { { HTML_VCARD }, { HTML_UNDEF }, "date", vr_date },
    { { HTML_VCARD }, { HTML_UNDEF }, "emergency", vr_emergency },
    { { HTML_VCARD }, { HTML_UNDEF }, "friend", vr_friend },
    { { HTML_VCARD }, { HTML_UNDEF }, "kin", vr_kin },
    { { HTML_VCARD }, { HTML_UNDEF }, "me", vr_me },
    { { HTML_VCARD }, { HTML_UNDEF }, "met", vr_met },
    { { HTML_VCARD }, { HTML_UNDEF }, "muse", vr_muse },
    { { HTML_VCARD }, { HTML_UNDEF }, "neighbor", vr_neighbor },
    { { HTML_VCARD }, { HTML_UNDEF }, "parent", vr_parent },
    { { HTML_VCARD }, { HTML_UNDEF }, "sibling", vr_sibling },
    { { HTML_VCARD }, { HTML_UNDEF }, "spouse", vr_spouse },
    { { HTML_VCARD }, { HTML_UNDEF }, "sweetheart", vr_sweetheart } };

struct symbol_entry < html_version, e_vtt > vtt_symbol_table [] =
{   { { HTML_VCARD }, { HTML_UNDEF }, "cell", vt_mobile },
    { { HTML_VCARD }, { HTML_UNDEF }, "mobile", vt_mobile },
    { { HTML_VCARD }, { HTML_UNDEF }, "fax", vt_fax },
    { { HTML_VCARD }, { HTML_UNDEF }, "pager", vt_pager },
    { { HTML_VCARD }, { HTML_UNDEF }, "text", vt_sms },
    { { HTML_VCARD }, { HTML_UNDEF }, "sms", vt_sms },
    { { HTML_VCARD }, { HTML_UNDEF }, "textphone", vt_textphone },
    { { HTML_VCARD }, { HTML_UNDEF }, "video", vt_video },
    { { HTML_VCARD }, { HTML_UNDEF }, "voice", vt_voice } };

struct symbol_entry < html_version, e_whitespace > whitespace_symbol_table [] =
{   { { HTML_JAN19 }, { HTML_UNDEF }, "normal", ws_normal },
    { { HTML_JAN19 }, { HTML_UNDEF }, "pre", ws_pre },
    { { HTML_JAN19 }, { HTML_UNDEF }, "nowrap", ws_nowrap },
    { { HTML_JAN19 }, { HTML_UNDEF }, "pre-wrap", ws_pre_wrap },
    { { HTML_JAN19 }, { HTML_UNDEF }, "break-spaces", ws_break_spaces },
    { { HTML_JAN19 }, { HTML_UNDEF }, "pre-line", ws_pre_line } };

struct symbol_entry < html_version, e_writingmode > writingmode_symbol_table [] =
{   { { HTML_SVG20, 0, HE_SVG_2, H2_CSS_SVG_2, H3_CSS_WRITING }, { HTML_UNDEF }, "horizontal-tb", wm_htb },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20, H2_CSS_SVG_1 }, { HTML_UNDEF }, "lr-tb", wm_lrtb },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20, H2_CSS_SVG_1 }, { HTML_UNDEF }, "rl-tb", wm_rltb },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20, H2_CSS_SVG_1 }, { HTML_UNDEF }, "tb-rl", wm_tbrl },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20, H2_CSS_SVG_1 }, { HTML_UNDEF }, "lr", wm_lr },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20, H2_CSS_SVG_1 }, { HTML_UNDEF }, "rl", wm_rl },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20, H2_CSS_SVG_1 }, { HTML_UNDEF }, "tb", wm_tb },
    { { HTML_SVG20, 0, 0, 0, H3_CSS_WRITING_4 }, { HTML_UNDEF }, "sideways-lr", wm_sideways_lr },
    { { HTML_SVG20, 0, 0, 0, H3_CSS_WRITING_4 }, { HTML_UNDEF }, "sideways-rl", wm_sideways_rl },
    { { HTML_SVG20, 0, HE_SVG_2, H2_CSS_SVG_2, H3_CSS_WRITING }, { HTML_UNDEF }, "vertical-lr", wm_vlr },
    { { HTML_SVG20, 0, HE_SVG_2, H2_CSS_SVG_2, H3_CSS_WRITING }, { HTML_UNDEF }, "vertical-rl", wm_vrl },
    { { HTML_SVG10, 0, HE_SVG_10_11_20 | HE_SVG_DEPR_20, H2_CSS_SVG_1 }, { HTML_UNDEF }, "inherit", wm_inherit } };

struct symbol_entry < html_version, e_xmlns > xmlns_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF }, HTTP PURL_ORG "g/ontology/bibo/", x_bibo },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "g/ontology/bibo/", x_bibo },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/xhtml", x_xhtml_1 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/xhtml", x_xhtml_1 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/TR/xhtml1/strict", x_xhtml_1_superseded },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/TR/xhtml1/strict", x_xhtml_1_superseded },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/TR/xhtml1/transitional", x_xhtml_1_superseded },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/TR/xhtml1/transitional", x_xhtml_1_superseded },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/TR/xhtml1/frameset", x_xhtml_1_superseded },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/TR/xhtml1/frameset", x_xhtml_1_superseded },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTP_W3 "/2000/xhtml", x_xhtml_11 },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTPS_W3 "/2000/xhtml", x_xhtml_11 },
    { { XHTML_2_0 }, { HTML_UNDEF }, HTTP_W3 "/2004/xhtml", x_xhtml_2 },
    { { XHTML_2_0 }, { HTML_UNDEF }, HTTPS_W3 "/2004/xhtml", x_xhtml_2 },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP CC "/ns#", x_cc },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS CC "/ns#", x_cc },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP OGC "/crs", x_crs },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS OGC "/crs", x_crs },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP DBPEDIA "/property/", x_dbp },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS DBPEDIA "/property/", x_dbp },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP DBPEDIA "/ontology/", x_dbp_owl },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS DBPEDIA "/ontology/", x_dbp_owl },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP DBPEDIA "/resource/", x_dbr },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS DBPEDIA "/resource/", x_dbr },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/dc/terms/", x_dc_terms },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/dc/terms/", x_dc_terms },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP DEFAULT_DOMAIN "/", x_ex },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS DEFAULT_DOMAIN "/", x_ex },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP XCOM "/foaf/0.1/", x_foaf },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS XCOM "/foaf/0.1/", x_foaf },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1998/math/mathml", x_mathml },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1998/math/mathml", x_mathml },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/2002/07/owl/#", x_owl },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/2002/07/owl/#", x_owl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "www.rddl.org/", x_rddl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "www.rddl.org/", x_rddl },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/02/22-rdf-syntax-ns#", x_rdf },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/02/22-rdf-syntax-ns#", x_rdf },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/ns/rdfa#", x_rdfa },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/ns/rdfa#", x_rdfa },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/2000/01/rdf-schema#", x_rdfs },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/2000/01/rdf-schema#", x_rdfs },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP SVG_2000, x_svg },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS SVG_2000, x_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/tr/rec-mathml-19980407", x_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/tr/rec-mathml-19980407", x_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/graphics/svg/svg-19990706.dtd", x_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/graphics/svg/svg-19990706.dtd", x_svg },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/vcard-rdf/3.0#", x_vcard1 },
    { { HTML_4_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/vcard-rdf/3.0#", x_vcard1 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "rdf.data-vocabulary.org/#", x_v },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "rdf.data-vocabulary.org/#", x_v },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2006/vcard/ns#", x_vcard },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2006/vcard/ns#", x_vcard },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/xhtml/vocab#", x_xhv },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/xhtml/vocab#", x_xhv },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/xlink", x_xlink },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/xlink", x_xlink },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/XML/1998/namespace", x_xml },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/XML/1998/namespace", x_xml },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2000/xmlns/", x_xmlns },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2000/xmlns/", x_xmlns },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/XMLSchema#", x_xsd },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/XMLSchema#", x_xsd },

    // many examples, including the living standard
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/html", x_html },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/html", x_html },

    // https://www.informit.com/articles/article.aspx?p=31837&seqNum=10
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/XInclude", x_xi },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/XInclude", x_xi },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/XSL/Transform/1.0", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/XSL/Transform/1.0", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/TR/WD-xsl", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/TR/WD-xsl", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "icl.com/saxon", x_saxon },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "icl.com/saxon", x_saxon },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "xml.apache.org/xslt", x_lxslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "xml.apache.org/xslt", x_lxslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP XOT "common", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS XOT "common", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP XOT "functions", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS XOT "functions", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP XOT "math", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS XOT "math", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP XOT "sets", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS XOT "sets", x_exsl },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/XMLSchema-datatypes", x_dt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/XMLSchema-datatypes", x_dt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/08/xquery-operators", x_xf },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/08/xquery-operators", x_xf },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/SMIL20", x_smil },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/SMIL20", x_smil },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/TR/REC-smil", x_smil },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/TR/REC-smil", x_smil },

    // https://metacpan.org/pod/XML::CommonNS
    { { XHTML_2_0 }, { HTML_UNDEF }, HTTP_W3 "/2006/06/xhtml", x_xhtml_2 },
    { { XHTML_2_0 }, { HTML_UNDEF }, HTTPS_W3 "/2006/06/xhtml", x_xhtml_2 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/xml-events", x_xmlevents },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/xml-events", x_xmlevents },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/dc/elements/1.1/", x_dc },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/dc/elements/1.1/", x_dc },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/vocab/relationship/", x_rel },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/vocab/relationship/", x_rel },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/rss/1.0/", x_rss },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/rss/1.0/", x_rss },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/net/rssmodules/blogcomments/", x_comments },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/net/rssmodules/blogcomments/", x_comments },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP PURL_ORG "/rss/1.0/modules/syndication/", x_syn },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS PURL_ORG "/rss/1.0/modules/syndication/", x_syn },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "relaxng.org/ns/structure/1.0/", x_rng },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "relaxng.org/ns/structure/1.0/", x_rng },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/2001/XMLSchema", x_xsd },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/2001/XMLSchema", x_xsd },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTP_W3 "/2001/XMLSchema-instance", x_xsi },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTPS_W3 "/2001/XMLSchema-instance", x_xsi },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/XSL/Transform", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/XSL/Transform", x_xslt },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP_W3 "/1999/XSL/Format", x_xslfo },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS_W3 "/1999/XSL/Format", x_xslfo },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "schemas.xmlsoap.org/soap/encoding/", x_soapenc11 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "schemas.xmlsoap.org/soap/encoding/", x_soapenc11 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "schemas.xmlsoap.org/soap/envelope/", x_soapenc11 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "schemas.xmlsoap.org/soap/envelope/", x_soapenc11 },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTP_W3 "/2003/05/soap-encoding", x_soapenc12 },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTPS_W3 "/2003/05/soap-encoding", x_soapenc12 },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTP_W3 "/2003/05/soap-envelope", x_soapenc12 },
    { { XHTML_1_1 }, { HTML_UNDEF }, HTTPS_W3 "/2003/05/soap-envelope", x_soapenc12 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTP "schemas.xmlsoap.org/wsdl/", x_wsdl11 },
    { { XHTML_1_0 }, { HTML_UNDEF }, HTTPS "schemas.xmlsoap.org/wsdl/", x_wsdl11 } };

#define INIT_ENUM(XX) \
    type_master < t_##XX > :: init (nits, XX##_symbol_table, sizeof (XX##_symbol_table) / sizeof (symbol_entry < html_version, e_##XX >)); \
    context.validation ().add_options () (VALIDATION #XX, ::boost::program_options::value < vstr_t > () -> composing (), "add a valid '" #XX "'.")

void init_1 ()
{   type_master < t_bb > :: init ();
    type_master < t_blocking > :: init ();
    type_master < t_cc_prohibits > :: init ();
    type_master < t_css_azimuth_be > :: init ();
    type_master < t_css_earnest > :: init ();
    type_master < t_html_boolean > :: init ();
    type_master < t_keygentype > :: init ();
    type_master < t_svg_content > :: init ();
    type_master < t_svg_phase > :: init ();
    type_master < t_xmllink > :: init (); }

void init_2 ()
{   type_master < t_10 > :: init ();
    type_master < t_accumulate > :: init ();
    type_master < t_additive > :: init ();
    type_master < t_all_none > :: init ();
    type_master < t_bool > :: init ();
    type_master < t_capture > :: init ();
    type_master < t_colour_scheme > :: init ();
    type_master < t_compositing > :: init ();
    type_master < t_connect > :: init ();
    type_master < t_coordinatesystem > :: init ();
    type_master < t_cors > :: init ();
    type_master < t_css_anim_play_state > :: init ();
    type_master < t_css_box_sizing > :: init ();
    type_master < t_css_break_box > :: init ();
    type_master < t_css_display_box > :: init ();
    type_master < t_css_display_flow > :: init ();
    type_master < t_css_isolation > :: init ();
    type_master < t_css_mark > :: init ();
    type_master < t_css_shape_fillrule > :: init ();
    type_master < t_css_text_resize > :: init ();
    type_master < t_dataformatas > :: init ();
    type_master < t_defaultaction > :: init ();
    type_master < t_dynamic_range > :: init ();
    type_master < t_editable > :: init ();
    type_master < t_fill_ve > :: init ();
    type_master < t_fillanim > :: init ();
    type_master < t_first_last > :: init ();
    type_master < t_forced_colours > :: init ();
    type_master < t_auto_none > :: init ();
    type_master < t_gender > :: init ();
    type_master < t_hidden > :: init ();
    type_master < t_hv > :: init ();
    type_master < t_initialvisibility > :: init ();
    type_master < t_inverted_colours > :: init ();
    type_master < t_js_version > :: init ();
    type_master < t_layout > :: init ();
    type_master < t_lengthadjust > :: init ();
    type_master < t_loading > :: init ();
    type_master < t_lralign > :: init ();
    type_master < t_ltr_rtl > :: init ();
    type_master < t_markerunits > :: init ();
    type_master < t_mathdisplay > :: init ();
    type_master < t_mathfontstyle > :: init ();
    type_master < t_mathfontweight > :: init ();
    type_master < t_mathmode > :: init ();
    type_master < t_mathorder > :: init ();
    type_master < t_mathscope > :: init ();
    type_master < t_media_hover > :: init ();
    type_master < t_media_inline > :: init ();
    type_master < t_media_orientation > :: init ();
    type_master < t_media_prefers > :: init ();
    type_master < t_meetslice > :: init ();
    type_master < t_morphology_operator > :: init ();
    type_master < t_nav_controls > :: init ();
    type_master < t_notations > :: init ();
    type_master < t_onoff > :: init ();
    type_master < t_orientation > :: init ();
    type_master < t_overlay > :: init ();
    type_master < t_popover > :: init ();
    type_master < t_propagate > :: init ();
    type_master < t_row_column > :: init ();
    type_master < t_safe_unsafe > :: init ();
    type_master < t_scan > :: init ();
    type_master < t_settype > :: init ();
    type_master < t_spacing > :: init ();
    type_master < t_ssi_f > :: init ();
    type_master < t_ssi_sizefmt > :: init ();
    type_master < t_startend > :: init ();
    type_master < t_stitchtiles > :: init ();
    type_master < t_streamedcontents > :: init ();
    type_master < t_svg_fontvariant_ff > :: init ();
    type_master < t_svg_method > :: init ();
    type_master < t_svg_playbackorder > :: init ();
    type_master < t_svg_side > :: init ();
    type_master < t_svg_timelinebegin > :: init ();
    type_master < t_svg_units > :: init ();
    type_master < t_tbalign > :: init ();
    type_master < t_tfn > :: init ();
    type_master < t_transp > :: init ();
    type_master < t_truefalseempty > :: init ();
    type_master < t_viewportscreen > :: init ();
    type_master < t_vtype > :: init ();
    type_master < t_workertype > :: init ();
    type_master < t_wrap > :: init ();
    type_master < t_wrap3 > :: init ();
    type_master < t_xlinkshow_a > :: init ();
    type_master < t_xmlspace > :: init ();
    type_master < t_xorder > :: init ();
    type_master < t_yesno > :: init ();
    type_master < t_yesnoempty > :: init ();
    type_master < t_zoompan > :: init (); }

void init_3 ()
{   type_master < t_aria_live > :: init ();
    type_master < t_attributetype > :: init ();
    type_master < t_behaviour > :: init ();
    type_master < t_button > :: init ();
    type_master < t_cc_permits > :: init ();
    type_master < t_command > :: init ();
    type_master < t_controlslist > :: init ();
    type_master < t_corp > :: init ();
    type_master < t_css_aai > :: init ();
    type_master < t_css_anim_comp > :: init ();
    type_master < t_css_azimuth_lri > :: init ();
    type_master < t_css_border_collapse > :: init ();
    type_master < t_css_column_fill > :: init ();
    type_master < t_css_display_outside > :: init ();
    type_master < t_css_empty_cells > :: init ();
    type_master < t_css_flex_wrap > :: init ();
    type_master < t_css_font_kerning > :: init ();
    type_master < t_css_speak_header > :: init ();
    type_master < t_css_speak_numeral > :: init ();
    type_master < t_css_speak_punctuation > :: init ();
    type_master < t_css_table_layout > :: init ();
    type_master < t_csvw_direction > :: init ();
    type_master < t_decoding > :: init ();
    type_master < t_dsc > :: init ();
    type_master < t_edgemode > :: init ();
    type_master < t_edi > :: init ();
    type_master < t_enctype > :: init ();
    type_master < t_environment_blending > :: init ();
    type_master < t_fill_rule > :: init ();
    type_master < t_font_variant_position > :: init ();
    type_master < t_fontnia > :: init ();
    type_master < t_gamut > :: init ();
    type_master < t_importance > :: init ();
    type_master < t_infixlinebreakstyle > :: init ();
    type_master < t_keytype > :: init ();
    type_master < t_lcralign > :: init ();
    type_master < t_lraalign > :: init ();
    type_master < t_lrnalign > :: init ();
    type_master < t_mathform > :: init ();
    type_master < t_mathframe > :: init ();
    type_master < t_mathoccurence > :: init ();
    type_master < t_media_overflow > :: init ();
    type_master < t_media_pointer > :: init ();
    type_master < t_media_scripting > :: init ();
    type_master < t_media_update > :: init ();
    type_master < t_menuitem > :: init ();
    type_master < t_menutype > :: init ();
    type_master < t_mf_class > :: init ();
    type_master < t_mf_status > :: init ();
    type_master < t_nsd > :: init ();
    type_master < t_nuf > :: init ();
    type_master < t_popovertargetaction > :: init ();
    type_master < t_preload5 > :: init ();
    type_master < t_restart > :: init ();
    type_master < t_scrolling > :: init ();
    type_master < t_shape_rcp > :: init ();
    type_master < t_spacer > :: init ();
    type_master < t_spreadmethod > :: init ();
    type_master < t_ssi_echo > :: init ();
    type_master < t_ssi_include > :: init ();
    type_master < t_svg_direction > :: init ();
    type_master < t_svg_fontvariant > :: init ();
    type_master < t_tendstotype > :: init ();
    type_master < t_tfa > :: init ();
    type_master < t_tfi > :: init ();
    type_master < t_tfu > :: init ();
    type_master < t_units > :: init ();
    type_master < t_valign_tmb > :: init ();
    type_master < t_valuetype > :: init ();
    type_master < t_vector_effect_12 > :: init ();
    type_master < t_visibility10 > :: init (); }

void init_4 ()
{   type_master < t_actiontype2 > :: init ();
    type_master < t_align2070 > :: init ();
    type_master < t_aligndec > :: init ();
    type_master < t_alignfig > :: init ();
    type_master < t_arabicenum > :: init ();
    type_master < t_aria_autocomplete > :: init ();
    type_master < t_aria_invalidity > :: init ();
    type_master < t_aria_sort > :: init ();
    type_master < t_buffered_rendering > :: init ();
    type_master < t_calcmode > :: init ();
    type_master < t_captionalign > :: init ();
    type_master < t_cc_requires > :: init ();
    type_master < t_channelselector > :: init ();
    type_master < t_content_encoding > :: init ();
    type_master < t_css_anim_dir > :: init ();
    type_master < t_css_anim_fill_mode > :: init ();
    type_master < t_css_border_image_repeat > :: init ();
    type_master < t_css_display_legacy > :: init ();
    type_master < t_css_flex_direction > :: init ();
    type_master < t_css_fn_round_t > :: init ();
    type_master < t_css_font_style_e > :: init ();
    type_master < t_css_hue_interpolation > :: init ();
    type_master < t_css_margin_trim_inner > :: init ();
    type_master < t_css_orientation > :: init ();
    type_master < t_css_polar > :: init ();
    type_master < t_css_shape_box > :: init ();
    type_master < t_css_speak > :: init ();
    type_master < t_css_val_con > :: init ();
    type_master < t_device > :: init ();
    type_master < t_edit > :: init ();
    type_master < t_effect > :: init ();
    type_master < t_font_variant_emoji > :: init ();
    type_master < t_frame4 > :: init ();
    type_master < t_intent_hint > :: init ();
    type_master < t_larnalign > :: init ();
    type_master < t_lcrd > :: init ();
    type_master < t_lcrnalign > :: init ();
    type_master < t_linebreakstyle > :: init ();
    type_master < t_linecap > :: init ();
    type_master < t_linejoin > :: init ();
    type_master < t_lrnialign > :: init ();
    type_master < t_mathclosure > :: init ();
    type_master < t_mathside > :: init ();
    type_master < t_media_display_mode > :: init ();
    type_master < t_media_prefers_2 > :: init ();
    type_master < t_mf_availability > :: init ();
    type_master < t_mf_category > :: init ();
    type_master < t_paint_order > :: init ();
    type_master < t_phase_x > :: init ();
    type_master < t_rsvp > :: init ();
    type_master < t_shadowinherit > :: init ();
    type_master < t_shape4 > :: init ();
    type_master < t_size3 > :: init ();
    type_master < t_ssi_config > :: init ();
    type_master < t_ssi_set > :: init ();
    type_master < t_svg_baseprofile > :: init ();
    type_master < t_syncbehaviour > :: init ();
    type_master < t_syncbehaviourdefault > :: init ();
    type_master < t_tdscope > :: init ();
    type_master < t_tfmu > :: init ();
    type_master < t_uplr > :: init ();
    type_master < t_valign3 > :: init ();
    type_master < t_visibility11 > :: init ();
    type_master < t_vkind > :: init ();
    type_master < t_xsdbool > :: init (); };

void enum_init (nitpick& nits)
{   init_1 ();
    init_2 ();
    init_3 ();
    init_4 ();
    INIT_ENUM (accrual_method);
    INIT_ENUM (accrual_periodicity);
    INIT_ENUM (accrual_policy);
    INIT_ENUM (action);
    INIT_ENUM (align3);
    INIT_ENUM (alignment_baseline);
    INIT_ENUM (alignplus);
    INIT_ENUM (as);
    INIT_ENUM (as_units);
    INIT_ENUM (autocapitalise);
    INIT_ENUM (autocomplete);
    INIT_ENUM (baselineshift);
    INIT_ENUM (cachekey);
    INIT_ENUM (citype);
    INIT_ENUM (colour_interpolation);
    INIT_ENUM (colour_rendering);
    INIT_ENUM (cookieid);
    INIT_ENUM (cntype);
    INIT_ENUM (comp_op);
    INIT_ENUM (composite_operator);
    INIT_ENUM (css_aaalri);
    INIT_ENUM (css_absolute_size);
    INIT_ENUM (css_absolute_size);
    INIT_ENUM (css_align_content);
    INIT_ENUM (css_align_items);
    INIT_ENUM (css_appearance);
    INIT_ENUM (css_azimuth_e);
    INIT_ENUM (css_background_attachment);
    INIT_ENUM (css_background_repeat);
    INIT_ENUM (css_blend_mode);
    INIT_ENUM (css_border_style);
    INIT_ENUM (css_border_width);
    INIT_ENUM (css_box_alignself_mess);
    INIT_ENUM (css_break);
    INIT_ENUM (css_break_inside);
    INIT_ENUM (css_caret_shape);
    INIT_ENUM (css_clear);
    INIT_ENUM (css_content_enum);
    INIT_ENUM (css_content_position);
    INIT_ENUM (css_coord_box);
    INIT_ENUM (css_counter_style);
    INIT_ENUM (css_cursor_e);
    INIT_ENUM (css_display);
    INIT_ENUM (css_display_inside);
    INIT_ENUM (css_display_internal);
    INIT_ENUM (css_elevation_e);
    INIT_ENUM (css_fn);
    INIT_ENUM (css_font_display);
    INIT_ENUM (css_font_feature);
    INIT_ENUM (css_font_format);
    INIT_ENUM (css_font_size_adjust_e);
    INIT_ENUM (css_font_tech);
    INIT_ENUM (css_font_variation);
    INIT_ENUM (css_font_weight);
    INIT_ENUM (css_generic_family);
    INIT_ENUM (css_justify_content);
    INIT_ENUM (css_layout_box);
    INIT_ENUM (css_list_style_position);
    INIT_ENUM (css_list_style_type);
    INIT_ENUM (css_paint_box);
    INIT_ENUM (css_overflow);
    INIT_ENUM (css_pitch_e);
    INIT_ENUM (css_position);
    INIT_ENUM (css_rgb_xyz);
    INIT_ENUM (css_rect);
    INIT_ENUM (css_relative_size);
    INIT_ENUM (css_resize);
    INIT_ENUM (css_self_position);
    INIT_ENUM (css_speak_as_e);
    INIT_ENUM (css_statement);
    INIT_ENUM (css_speech_rate_e);
    INIT_ENUM (css_system_e);
    INIT_ENUM (css_text_align);
    INIT_ENUM (css_text_decoration);
    INIT_ENUM (css_text_transform);
    INIT_ENUM (css_user_select);
    INIT_ENUM (css_val_fn);
    INIT_ENUM (css_vertical_align);
    INIT_ENUM (css_visual_box);
    INIT_ENUM (css_volume_e);
    INIT_ENUM (css_whitespace);
    INIT_ENUM (css_wide);
    INIT_ENUM (crossout);
    INIT_ENUM (cursor);
    INIT_ENUM (decalign);
    INIT_ENUM (determiner);
    INIT_ENUM (dingbat);
    INIT_ENUM (dir);
    INIT_ENUM (display_align);
    INIT_ENUM (dominantbaseline);
    INIT_ENUM (enterkeyhint);
    INIT_ENUM (figalign);
    INIT_ENUM (filter_in);
    INIT_ENUM (fontname);
    INIT_ENUM (font_enum);
    INIT_ENUM (font_variant_2);
    INIT_ENUM (font_variant_caps);
    INIT_ENUM (font_variant_east_asian);
    INIT_ENUM (font_variant_ligature);
    INIT_ENUM (font_variant_numeric);
    INIT_ENUM (formaturi);
    INIT_ENUM (halign);
    INIT_ENUM (icalfreq);
    INIT_ENUM (image_rendering);
    INIT_ENUM (icc);
    INIT_ENUM (indentalign);
    INIT_ENUM (inky);
    INIT_ENUM (inputmode);
    INIT_ENUM (inputplus);
    INIT_ENUM (inputtype);
    INIT_ENUM (inputtype3);
    INIT_ENUM (inputtype32);
    INIT_ENUM (inputtype4);
    INIT_ENUM (inputtype5);
    INIT_ENUM (jtoken);
    INIT_ENUM (kind);
    INIT_ENUM (length_absolute);
    INIT_ENUM (length_relative);
    INIT_ENUM (linebreak);
    INIT_ENUM (linkparam);
    INIT_ENUM (listtype);
    INIT_ENUM (longdivstyle);
    INIT_ENUM (mah);
    INIT_ENUM (mathalign);
    INIT_ENUM (mathlocation);
    INIT_ENUM (mathnotation);
    INIT_ENUM (mathoverflow);
    INIT_ENUM (mathvariant);
    INIT_ENUM (matrixtype);
    INIT_ENUM (method);
    INIT_ENUM (mf_identifier);
    INIT_ENUM (mf_itemtype);
    INIT_ENUM (mf_listing_action);
    INIT_ENUM (mf_method);
    INIT_ENUM (mf_reviewtype);
    INIT_ENUM (myersbriggs);
    INIT_ENUM (namedspace);
    INIT_ENUM (namespace);
    INIT_ENUM (nit_macro);
    INIT_ENUM (nit_section);
    INIT_ENUM (ogtype);
    INIT_ENUM (page_orientation);
    INIT_ENUM (paintkeyword);
    INIT_ENUM (plusstyle);
    INIT_ENUM (pointer_events);
    INIT_ENUM (print);
    INIT_ENUM (quote_style);
    INIT_ENUM (referrer);
    INIT_ENUM (rendering_in_tents);
    INIT_ENUM (rules);
    INIT_ENUM (sandbox);
    INIT_ENUM (scei);
    INIT_ENUM (severity);
    INIT_ENUM (shadow);
    INIT_ENUM (shape7);
    INIT_ENUM (shape_rendering);
    INIT_ENUM (smei);
    INIT_ENUM (ssi);
    INIT_ENUM (ssi_comparison);
    INIT_ENUM (ssi_encoding);
    INIT_ENUM (ssi_env);
    INIT_ENUM (step_position);
    INIT_ENUM (svg_align);
    INIT_ENUM (svg_display);
    INIT_ENUM (svg_fontstretch);
    INIT_ENUM (svg_fontstretch_ff);
    INIT_ENUM (svg_fontstyle);
    INIT_ENUM (svg_fontweight);
    INIT_ENUM (svg_fontweight_ff);
    INIT_ENUM (svg_mode);
    INIT_ENUM (svg_overflow);
    INIT_ENUM (svg_rendering_intent);
    INIT_ENUM (svg_type);
    INIT_ENUM (svg_version);
    INIT_ENUM (svg_version_grand);
    INIT_ENUM (tableframe);
    INIT_ENUM (tblri);
    INIT_ENUM (text_decoration);
    INIT_ENUM (text_rendering);
    INIT_ENUM (transform_anim);
    INIT_ENUM (transformbehaviour);
    INIT_ENUM (transform_fn);
    INIT_ENUM (turbulence_type);
    INIT_ENUM (unit);
    INIT_ENUM (unit_abs_len);
    INIT_ENUM (unit_angle);
    INIT_ENUM (unit_freq);
    INIT_ENUM (unit_rel_len);
    INIT_ENUM (unit_res);
    INIT_ENUM (unit_time);
    INIT_ENUM (unicode_bidi);
    INIT_ENUM (vector_effect_2);
    INIT_ENUM (vertical_align_enum);
    INIT_ENUM (vgender);
    INIT_ENUM (vrel);
    INIT_ENUM (vtt);
    INIT_ENUM (whitespace);
    INIT_ENUM (writingmode);
    INIT_ENUM (xmlns); }
