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

#include "standard.h"
#include "field.h"
#include "connection.h"

typedef connection < e_class, e_property > prop_field;
typedef connection < e_class, e_rel > rel_field;

prop_field standard_props [] =
{   { h1_adr, mf1_country_name },
    { h1_adr, mf1_extended_address },
    { h1_adr, mf1_locality },
    { h1_adr, mf1_postal_code },
    { h1_adr, mf1_post_office_box },
    { h1_adr, mf1_region },
    { h1_adr, mf1_street_address },

    { h1_aggregate, mf1_count },
    { h1_aggregate, mf1_item },
    { h1_aggregate, mf1_photo },
    { h1_aggregate, mf1_summary },
    { h1_aggregate, mf1_url },
    { h1_aggregate, mf1_votes },

    { h1_atom, mf1_author },
    { h1_atom, mf1_entry_content },
    { h1_atom, mf1_entry_summary },
    { h1_atom, mf1_entry_title },
    { h1_atom, mf1_hentry },
    { h1_atom, mf1_published },
    { h1_atom, mf1_updated },

    { h1_audio, mf1_album },
    { h1_audio, mf1_amount },
    { h1_audio, mf1_category },
    { h1_audio, mf1_contributor },
    { h1_audio, mf1_currency },
    { h1_audio, mf1_description },
    { h1_audio, mf1_duration },
    { h1_audio, mf1_fn },
    { h1_audio, mf1_item },
    { h1_audio, mf1_photo },
    { h1_audio, mf1_price },
    { h1_audio, mf1_position },
    { h1_audio, mf1_published },
    { h1_audio, mf1_sample },

    { h1_calendar, mf1_attach },
    { h1_calendar, mf1_attendee },
    { h1_calendar, mf1_category },
    { h1_calendar, mf1_contact },
    { h1_calendar, mf1_dtend },
    { h1_calendar, mf1_dtstart },
    { h1_calendar, mf1_description },
    { h1_calendar, mf1_duration },
    { h1_calendar, mf1_geo },
    { h1_calendar, mf1_latitude },
    { h1_calendar, mf1_location },
    { h1_calendar, mf1_longitude },
    { h1_calendar, mf1_organiser },
    { h1_calendar, mf1_partstat },
    { h1_calendar, mf1_rdate },
    { h1_calendar, mf1_role },
    { h1_calendar, mf1_rrule },
    { h1_calendar, mf1_status },
    { h1_calendar, mf1_summary },
    { h1_calendar, mf1_uid },
    { h1_calendar, mf1_url },

    { h1_card, mf1_additional_name },
    { h1_card, mf1_adr },
    { h1_card, mf1_agent },
    { h1_card, mf1_bday },
    { h1_card, mf1_category },
    { h1_card, mf1_class },
    { h1_card, mf1_country_name },
    { h1_card, mf1_email },
    { h1_card, mf1_extended_address },
    { h1_card, mf1_family_name },
    { h1_card, mf1_fn },
    { h1_card, mf1_given_name },
    { h1_card, mf1_geo },
    { h1_card, mf1_honorific_prefix },
    { h1_card, mf1_honorific_suffix },
    { h1_card, mf1_key },
    { h1_card, mf1_label },
    { h1_card, mf1_latitude },
    { h1_card, mf1_locality },
    { h1_card, mf1_logo },
    { h1_card, mf1_longitude },
    { h1_card, mf1_mailer },
    { h1_card, mf1_n },
    { h1_card, mf1_nickname },
    { h1_card, mf1_note },
    { h1_card, mf1_org },
    { h1_card, mf1_organisation_name },
    { h1_card, mf1_organisation_unit },
    { h1_card, mf1_photo },
    { h1_card, mf1_postal_code },
    { h1_card, mf1_post_office_box },
    { h1_card, mf1_region },
    { h1_card, mf1_rev },
    { h1_card, mf1_role },
    { h1_card, mf1_sort_string },
    { h1_card, mf1_sound },
    { h1_card, mf1_street_address },
    { h1_card, mf1_tel },
    { h1_card, mf1_title },
    { h1_card, mf1_type },
    { h1_card, mf1_tz },
    { h1_card, mf1_uid },
    { h1_card, mf1_url },
    { h1_card, mf1_value },

    { h1_geo, mf1_latitude },
    { h1_geo, mf1_longitude },

    { h1_listing, mf1_adr },
    { h1_listing, mf1_announce },
    { h1_listing, mf1_business },
    { h1_listing, mf1_description },
    { h1_listing, mf1_dtexpired },
    { h1_listing, mf1_dtlisted },
    { h1_listing, mf1_email },
    { h1_listing, mf1_event },
    { h1_listing, mf1_fn },
    { h1_listing, mf1_geo },
    { h1_listing, mf1_housing },
    { h1_listing, mf1_item },
    { h1_listing, mf1_lister },
    { h1_listing, mf1_meet },
    { h1_listing, mf1_offer },
    { h1_listing, mf1_opening },
    { h1_listing, mf1_permalink },
    { h1_listing, mf1_person },
    { h1_listing, mf1_photo },
    { h1_listing, mf1_place },
    { h1_listing, mf1_price },
    { h1_listing, mf1_product },
    { h1_listing, mf1_rent },
    { h1_listing, mf1_sell },
    { h1_listing, mf1_service },
    { h1_listing, mf1_summary },
    { h1_listing, mf1_tel },
    { h1_listing, mf1_trade },
    { h1_listing, mf1_version },
    { h1_listing, mf1_url },
    { h1_listing, mf1_wanted },
    { h1_listing, mf1_website },

    { h1_media, mf1_contributor },
//    { h1_media, mf1_enclosure },
    { h1_media, mf1_fn },
    { h1_media, mf1_photo },
    { h1_media, mf1_player },

    { h1_news, mf1_source_org },
    { h1_news, mf1_dateline },
    { h1_news, mf1_geo },

    { h1_product, mf1_brand },
    { h1_product, mf1_category },
    { h1_product, mf1_price },
    { h1_product, mf1_description },
    { h1_product, mf1_fn },
    { h1_product, mf1_photo },
    { h1_product, mf1_url },
    { h1_product, mf1_review },
    { h1_product, mf1_listing },
    { h1_product, mf1_identifier },
    { h1_product, mf1_type },
    { h1_product, mf1_value },

    { h1_recipe, mf1_fn },
    { h1_recipe, mf1_ingredient },
    { h1_recipe, mf1_value },
    { h1_recipe, mf1_type },
    { h1_recipe, mf1_instructions },
    { h1_recipe, mf1_duration },
    { h1_recipe, mf1_photo },
    { h1_recipe, mf1_summary },
    { h1_recipe, mf1_author },
    { h1_recipe, mf1_published },
    { h1_recipe, mf1_nutrition },

    { h1_resume, mf1_summary },
    { h1_resume, mf1_contact },
    { h1_resume, mf1_education },
    { h1_resume, mf1_experience },
    { h1_resume, mf1_skill },
    { h1_resume, mf1_affliation },
    { h1_resume, mf1_publications },

    { h1_review, mf1_best },
    { h1_review, mf1_business },
    { h1_review, mf1_description },
    { h1_review, mf1_dtreviewed },
    { h1_review, mf1_event },
    { h1_review, mf1_fn },
    { h1_review, mf1_item },
    { h1_review, mf1_person },
    { h1_review, mf1_photo },
    { h1_review, mf1_place },
    { h1_review, mf1_product },
    { h1_review, mf1_rating },
    { h1_review, mf1_reviewer },
    { h1_review, mf1_summary },
    { h1_review, mf1_url },
    { h1_review, mf1_value },
    { h1_review, mf1_worst },
    { h1_review, mf1_website },

    { h_adr, p_altitude },
    { h_adr, p_country_name },
    { h_adr, p_extended_address },
    { h_adr, p_geo },
    { h_adr, p_label },
    { h_adr, p_latitude },
    { h_adr, p_locality },
    { h_adr, p_longitude },
    { h_adr, p_post_office_box },
    { h_adr, p_postal_code },
    { h_adr, p_region },
    { h_adr, p_street_address },
    { h_adr, u_geo },

    { h_aggregate, p_average },
    { h_aggregate, p_best },
    { h_aggregate, p_count },
    { h_aggregate, p_item },
    { h_aggregate, p_name },
    { h_aggregate, p_votes },
    { h_aggregate, p_worst },

    { h_breadcrumb, p_name },
    { h_breadcrumb, u_url },

    { h_card, dt_anniversary },
    { h_card, dt_bday },
    { h_card, dt_rev },
    { h_card, p_additional_name },
    { h_card, p_adr },
    { h_card, p_altitude },
    { h_card, p_category },
    { h_card, p_country_name },
    { h_card, p_extended_address },
    { h_card, p_family_name },
    { h_card, p_gender_identity },
    { h_card, p_geo },
    { h_card, p_given_name },
    { h_card, p_honorific_prefix },
    { h_card, p_honorific_suffix },
    { h_card, p_job_title },
    { h_card, p_label },
    { h_card, p_latitude },
    { h_card, p_locality },
    { h_card, p_longitude },
    { h_card, p_name },
    { h_card, p_nickname },
    { h_card, p_note },
    { h_card, p_org },
    { h_card, p_organisation_name },
    { h_card, p_organisation_unit },
    { h_card, p_post_office_box },
    { h_card, p_postal_code },
    { h_card, p_region },
    { h_card, p_role },
    { h_card, p_sex },
    { h_card, p_sort_string },
    { h_card, p_street_address },
    { h_card, p_tel },
    { h_card, p_tz },
    { h_card, u_email },
    { h_card, u_geo },
    { h_card, u_impp },
    { h_card, u_key },
    { h_card, u_logo },
    { h_card, u_photo },
    { h_card, u_uid },
    { h_card, u_url },

    { h_cite, dt_accessed },
    { h_cite, dt_published },
    { h_cite, p_author },
    { h_cite, p_content },
    { h_cite, p_name },
    { h_cite, p_publication },
    { h_cite, u_uid },
    { h_cite, u_url },

    { h_entry, dt_published },
    { h_entry, dt_updated },
    { h_entry, e_content },
    { h_entry, p_author },
    { h_entry, p_category },
    { h_entry, p_comment },
    { h_entry, p_geo },
    { h_entry, p_latitude },
    { h_entry, p_location },
    { h_entry, p_longitude },
    { h_entry, p_name },
    { h_entry, p_rsvp },
    { h_entry, p_summary },
    { h_entry, u_audio },
    { h_entry, u_bookmark_of },
    { h_entry, u_featured },
    { h_entry, u_in_reply_to },
    { h_entry, u_like },
    { h_entry, u_like_of },
    { h_entry, u_photo },
    { h_entry, u_repost },
    { h_entry, u_repost_of },
    { h_entry, u_syndication },
    { h_entry, u_uid },
    { h_entry, u_url },
    { h_entry, u_video },

    { h_event, dt_duration },
    { h_event, dt_end },
    { h_event, dt_start },
    { h_event, e_content },
    { h_event, p_attendee },
    { h_event, p_category },
    { h_event, p_description },
    { h_event, p_geo },
    { h_event, p_latitude },
    { h_event, p_location },
    { h_event, p_longitude },
    { h_event, p_name },
    { h_event, p_summary },
    { h_event, u_url },

    { h_feed, p_author },
    { h_feed, p_entry },
    { h_feed, p_name },
    { h_feed, p_summary },
    { h_feed, u_photo },
    { h_feed, u_url },

    { h_geo, p_altitude },
    { h_geo, p_latitude },
    { h_geo, p_longitude },

    { h_item, p_name },
    { h_item, u_photo },
    { h_item, u_url },

    { h_listing, p_action },
    { h_listing, p_category },
    { h_listing, dt_expired },
    { h_listing, dt_listed },
    { h_listing, p_lister },
    { h_listing, p_price },
    { h_listing, u_url },

    { h_product, e_description },
    { h_product, p_brand },
    { h_product, p_category },
    { h_product, p_name },
    { h_product, p_price },
    { h_product, p_review },
    { h_product, u_identifier },
    { h_product, u_photo },
    { h_product, u_url },

    { h_recipe, dt_duration },
    { h_recipe, dt_published },
    { h_recipe, e_instructions },
    { h_recipe, p_author },
    { h_recipe, p_ingredient },
    { h_recipe, p_name },
    { h_recipe, p_nutrition },
    { h_recipe, p_summary },
    { h_recipe, p_yield },
    { h_recipe, u_photo },

    { h_resume, p_affiliation },
    { h_resume, p_contact },
    { h_resume, p_education },
    { h_resume, p_experience },
    { h_resume, p_name },
    { h_resume, p_skill },
    { h_resume, p_summary },

    { h_review, p_author },
    { h_review, p_best },
    { h_review, p_category },
    { h_review, e_content },
    { h_review, p_item },
    { h_review, p_location },
    { h_review, p_name },
    { h_review, dt_published },
    { h_review, p_rating },
    { h_review, p_summary },
    { h_review, p_worst },
    { h_review, u_syndication },
    { h_review, u_url } };

rel_field standard_rels [] =
{   { h1_atom, r_bookmark },
    { h1_atom, r_feed },
    { h1_atom, r_tag },

    { h1_audio, r_enclosure },
    { h1_audio, r_payment },

    { h1_calendar, r_profile },

    { h1_listing, r_tag },

    { h1_media, r_enclosure },

    { h1_news, r_principles },
    { h1_news, r_item_licence },

//    { h1_product, r_product },

    { h1_recipe, r_tag },
    { h1_recipe, r_licence },

    { h1_resume, r_tag },

    { h1_review, r_bookmark },
    { h1_review, r_licence },
    { h1_review, r_self },
    { h1_review, r_tag }
};

connections < prop_field > farm;
connections < rel_field > stock;

void fields_init (nitpick& nits)
{   farm.init (nits, standard_props, sizeof (standard_props));
    stock.init (nits, standard_rels, sizeof (standard_rels)); }

bool is_plausible_field (const e_class container, const e_property p)
{   return farm.is_plausible_connection (container, p); }

bool is_possible_rel_field (const e_rel r)
{   return stock.is_possible_member (r); }

bool is_plausible_field (const e_class container, const e_rel r)
{   return stock.is_plausible_connection (container, r); }