/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "type/type_class.h"

// microformats1: http://microformats.org/wiki/Main_Page#Specifications
#define H1_ATOM "hatom"
#define H1_AUDIO "haudio"
#define H1_CALENDAR "vcalendar"
#define H1_CARD "vcard"
#define H1_ENTRY "hentry"
#define H1_EVENT "vevent"
#define H1_MEDIA "hmedia"
#define H1_LISTING "hlisting"
#define H1_PRODUCT "hproduct"
#define H1_RECIPE "hrecipe"
#define H1_RESUME "hresume"
#define H1_REVIEW "hreview"
#define H1_REVIEW_AGGREGATE "hreview-aggregate"
#define H1_ADR "adr"
#define H1_GEO "geo"
#define H1_NEWS "hnews"
#define H1_XMDP "xmdp"
#define H1_XOXO "xoxo"

// microformats2: http://microformats.org/wiki/Main_Page
#define H_ADR "h-adr"
#define H_BREADCRUMB "h-breadcrumb"
#define H_BREADCRUMBS "h-breadcrumbs"
#define H_CARD "h-card"
#define H_CITE "h-cite"
#define H_ENTRY "h-entry"
#define H_EVENT "h-event"
#define H_FEED "h-feed"
#define H_GEO "h-geo"
#define H_ITEM "h-item"
#define H_LISTING "h-listing"
#define H_PRODUCT "h-product"
#define H_RECIPE "h-recipe"
#define H_RESUME "h-resume"
#define H_REVIEW "h-review"
#define H_AGGREGATE "h-review-aggregate"

// for those who habitually spell correctly (unlike me)
#define H_CV "h-cv"
#define H_ADDR "h-addr"
#define H_CALENDAR "h-calendar"
#define H1_ADDR "addr"

#define CSTR_dt_anniversary "dt-anniversary"
#define CSTR_dt_accessed "dt-accessed"
#define CSTR_dt_bday "dt-bday"
#define CSTR_dt_duration "dt-duration"
#define CSTR_dt_end "dt-end"
#define CSTR_dt_expired "dt-expired"
#define CSTR_dt_listed "dt-listed"
#define CSTR_dt_published "dt-published"
#define CSTR_dt_rev "dt-rev"
#define CSTR_dt_reviewed "dt-reviewed"
#define CSTR_dt_start "dt-start"
#define CSTR_dt_updated "dt-updated"
#define CSTR_e_content "e-content"
#define CSTR_e_description "e-description"
#define CSTR_e_instructions "e-instructions"
#define CSTR_p_action "p-action"
#define CSTR_p_additional_name "p-additional-name"
#define CSTR_p_adr "p-adr"
#define CSTR_p_affiliation "p-affiliation"
#define CSTR_p_altitude "p-altitude"
#define CSTR_p_attendee "p-attendee"
#define CSTR_p_author "p-author"
#define CSTR_p_average "p-average"
#define CSTR_p_best "p-best"
#define CSTR_p_brand "p-brand"
#define CSTR_p_category "p-category"
#define CSTR_p_comment "p-comment"
#define CSTR_p_contact "p-contact"
#define CSTR_p_content "p-content"
#define CSTR_p_count "p-count"
#define CSTR_p_country_name "p-country-name"
#define CSTR_p_description "p-description"
#define CSTR_p_education "p-education"
#define CSTR_p_entry "p-entry"
#define CSTR_p_experience "p-experience"
#define CSTR_p_extended_address "p-extended-address"
#define CSTR_p_family_name "p-family-name"
#define CSTR_p_gender_identity "p-gender-identity"
#define CSTR_p_geo "p-geo"
#define CSTR_p_given_name "p-given-name"
#define CSTR_p_honorific_prefix "p-honorific-prefix"
#define CSTR_p_honorific_suffix "p-honorific-suffix"
#define CSTR_p_ingredient "p-ingredient"
#define CSTR_p_item "p-item"
#define CSTR_p_job_title "p-job-title"
#define CSTR_p_label "p-label"
#define CSTR_p_latitude "p-latitude"
#define CSTR_p_lister "p-lister"
#define CSTR_p_locality "p-locality"
#define CSTR_p_location "p-location"
#define CSTR_p_longitude "p-longitude"
#define CSTR_p_name "p-name"
#define CSTR_p_nickname "p-nickname"
#define CSTR_p_note "p-note"
#define CSTR_p_nutrition "p-nutrition"
#define CSTR_p_org "p-org"
#define CSTR_p_organisation_name "p-organization-name"
#define CSTR_p_organisation_unit "p-organization-unit"
#define CSTR_p_organiser "p-organizer"
#define CSTR_p_post_office_box "p-post-office-box"
#define CSTR_p_postal_code "p-postal-code"
#define CSTR_p_price "p-price"
#define CSTR_p_publication "p-publication"
#define CSTR_p_rating "p-rating"
#define CSTR_p_region "p-region"
#define CSTR_p_review "p-review"
#define CSTR_p_reviewer "p-reviewer"
#define CSTR_p_role "p-role"
#define CSTR_p_rsvp "p-rsvp"
#define CSTR_p_sex "p-sex"
#define CSTR_p_skill "p-skill"
#define CSTR_p_sort_string "p-sort-string"
#define CSTR_p_street_address "p-street-address"
#define CSTR_p_summary "p-summary"
#define CSTR_p_tel "p-tel"
#define CSTR_p_tz "p-tz"
#define CSTR_p_votes "p-votes"
#define CSTR_p_worst "p-worst"
#define CSTR_p_yield "p-yield"
#define CSTR_u_audio "u-audio"
#define CSTR_u_bookmark_of "u-bookmark-of"
#define CSTR_u_email "u-email"
#define CSTR_u_featured "u-featured"
#define CSTR_u_geo "u-geo"
#define CSTR_u_identifier "u-identifier"
#define CSTR_u_impp "u-impp"
#define CSTR_u_in_reply_to "u-in-reply-to"
#define CSTR_u_key "u-key"
#define CSTR_u_like "u-like"
#define CSTR_u_like_of "u-like-of"
#define CSTR_u_logo "u-logo"
#define CSTR_u_photo "u-photo"
#define CSTR_u_repost "u-repost"
#define CSTR_u_repost_of "u-repost-of"
#define CSTR_u_sound "u-sound"
#define CSTR_u_syndication "u-syndication"
#define CSTR_u_uid "u-uid"
#define CSTR_u_url "u-url"
#define CSTR_u_video "u-video"
#define CSTR_u_dnsprefetch "u-dnsprefetch"
#define CSTR_u_external "u-external"
#define CSTR_u_icon "u-icon"
#define CSTR_u_noopener "u-noopener"
#define CSTR_u_noreferrer "u-noreferrer"
#define CSTR_u_preconnect "u-preconnect"
#define CSTR_u_prefetch "u-prefetch"
#define CSTR_u_preload "u-preload"
#define CSTR_u_prerender "u-prerender"
#define CSTR_u_search "u-search"


struct symbol_entry < e_class > class_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF }, H1_ATOM, h1_atom },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_AUDIO, h1_audio },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_CALENDAR, h1_calendar },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_CARD, h1_card },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_ENTRY, h1_atom },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_EVENT, h1_calendar },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_MEDIA, h1_media },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_LISTING, h1_listing },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_PRODUCT, h1_product },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_RECIPE, h1_recipe },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_RESUME, h1_resume },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_REVIEW, h1_review },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_REVIEW_AGGREGATE, h1_aggregate },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_ADR, h1_adr },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_GEO, h1_geo },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_NEWS, h1_news },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_XMDP, h1_xmdp },
    { { HTML_UNDEF }, { HTML_UNDEF }, H1_XOXO, h1_xoxo },

    { { HTML_UNDEF }, { HTML_UNDEF }, H_ADR, h_adr },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_BREADCRUMB, h_breadcrumb },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_CARD, h_card },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_CITE, h_cite },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_ENTRY, h_entry },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_EVENT, h_event },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_FEED, h_feed },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_GEO, h_geo },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_ITEM, h_item },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_LISTING, h_listing },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_PRODUCT, h_product },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_RECIPE, h_recipe },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_RESUME, h_resume },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_REVIEW, h_review },
    { { HTML_UNDEF }, { HTML_UNDEF }, H_AGGREGATE, h_aggregate },

    { { HTML_JAN07 }, { HTML_UNDEF }, "copyright", h5d_copyright },
    { { HTML_JAN07 }, { HTML_UNDEF }, "error", h5d_error },
    { { HTML_JAN07 }, { HTML_UNDEF }, "example", h5d_example },
    { { HTML_JAN07 }, { HTML_UNDEF }, "issue", h5d_issue },
//    { { HTML_JAN07 }, { HTML_UNDEF }, "note", h5d_note },
    { { HTML_JAN07 }, { HTML_UNDEF }, "search", h5d_search },
    { { HTML_JAN07 }, { HTML_UNDEF }, "warning", h5d_warning },

    { { HTML_UNDEF }, { HTML_UNDEF }, "additional-name", mf1_additional_name },
//    { { HTML_UNDEF }, { HTML_UNDEF }, "adr", mf1_adr },
    { { HTML_UNDEF }, { HTML_UNDEF }, "affliation", mf1_affliation },
    { { HTML_UNDEF }, { HTML_UNDEF }, "agent", mf1_agent },
    { { HTML_UNDEF }, { HTML_UNDEF }, "album", mf1_album },
    { { HTML_UNDEF }, { HTML_UNDEF }, "amount", mf1_amount },
    { { HTML_UNDEF }, { HTML_UNDEF }, "announce", mf1_announce },
    { { HTML_UNDEF }, { HTML_UNDEF }, "attach", mf1_attach },
    { { HTML_UNDEF }, { HTML_UNDEF }, "attendee", mf1_attendee },
    { { HTML_UNDEF }, { HTML_UNDEF }, "author", mf1_author },
    { { HTML_UNDEF }, { HTML_UNDEF }, "average", mf1_average },
    { { HTML_UNDEF }, { HTML_UNDEF }, "bday", mf1_bday },
    { { HTML_UNDEF }, { HTML_UNDEF }, "best", mf1_best },
    { { HTML_UNDEF }, { HTML_UNDEF }, "brand", mf1_brand },
    { { HTML_UNDEF }, { HTML_UNDEF }, "business", mf1_business },
    { { HTML_UNDEF }, { HTML_UNDEF }, "category", mf1_category },
    { { HTML_UNDEF }, { HTML_UNDEF }, "class", mf1_class },
    { { HTML_UNDEF }, { HTML_UNDEF }, "contact", mf1_contact },
    { { HTML_UNDEF }, { HTML_UNDEF }, "contributor", mf1_contributor },
    { { HTML_UNDEF }, { HTML_UNDEF }, "count", mf1_count },
    { { HTML_UNDEF }, { HTML_UNDEF }, "country-name", mf1_country_name },
    { { HTML_UNDEF }, { HTML_UNDEF }, "currency", mf1_currency },
    { { HTML_UNDEF }, { HTML_UNDEF }, "dateline", mf1_dateline },
    { { HTML_UNDEF }, { HTML_UNDEF }, "dtend", mf1_dtend },
    { { HTML_UNDEF }, { HTML_UNDEF }, "dtexpired", mf1_dtexpired },
    { { HTML_UNDEF }, { HTML_UNDEF }, "dtlisted", mf1_dtlisted },
    { { HTML_UNDEF }, { HTML_UNDEF }, "dtreviewed", mf1_dtreviewed },
    { { HTML_UNDEF }, { HTML_UNDEF }, "dtstart", mf1_dtstart },
    { { HTML_UNDEF }, { HTML_UNDEF }, "description", mf1_description },
    { { HTML_UNDEF }, { HTML_UNDEF }, "duration", mf1_duration },
    { { HTML_UNDEF }, { HTML_UNDEF }, "education", mf1_education },
    { { HTML_UNDEF }, { HTML_UNDEF }, "email", mf1_email },
    { { HTML_UNDEF }, { HTML_UNDEF }, "entry-content", mf1_entry_content },
    { { HTML_UNDEF }, { HTML_UNDEF }, "entry-summary", mf1_entry_summary },
    { { HTML_UNDEF }, { HTML_UNDEF }, "entry-title", mf1_entry_title },
    { { HTML_UNDEF }, { HTML_UNDEF }, "event", mf1_event },
    { { HTML_UNDEF }, { HTML_UNDEF }, "experience", mf1_experience },
    { { HTML_UNDEF }, { HTML_UNDEF }, "extended-address", mf1_extended_address },
    { { HTML_UNDEF }, { HTML_UNDEF }, "family-name", mf1_family_name },
    { { HTML_UNDEF }, { HTML_UNDEF }, "fn", mf1_fn },
    { { HTML_UNDEF }, { HTML_UNDEF }, "given-name", mf1_given_name },
//    { { HTML_UNDEF }, { HTML_UNDEF }, "geo", mf1_geo },
//    { { HTML_UNDEF }, { HTML_UNDEF }, "hentry", mf1_hentry },
    { { HTML_UNDEF }, { HTML_UNDEF }, "honorific-prefix", mf1_honorific_prefix },
    { { HTML_UNDEF }, { HTML_UNDEF }, "honorific-suffix", mf1_honorific_suffix },
    { { HTML_UNDEF }, { HTML_UNDEF }, "housing", mf1_housing },
    { { HTML_UNDEF }, { HTML_UNDEF }, "identifier", mf1_identifier },
    { { HTML_UNDEF }, { HTML_UNDEF }, "ingredient", mf1_ingredient },
    { { HTML_UNDEF }, { HTML_UNDEF }, "instructions", mf1_instructions },
    { { HTML_UNDEF }, { HTML_UNDEF }, "item", mf1_item },
    { { HTML_UNDEF }, { HTML_UNDEF }, "item-info", mf1_item_info },
    { { HTML_UNDEF }, { HTML_UNDEF }, "item-license", mf1_item_licence },
    { { HTML_UNDEF }, { HTML_UNDEF }, "item-tags", mf1_item_tags },
    { { HTML_UNDEF }, { HTML_UNDEF }, "item-type", mf1_item_type },
    { { HTML_UNDEF }, { HTML_UNDEF }, "key", mf1_key },
    { { HTML_UNDEF }, { HTML_UNDEF }, "label", mf1_label },
    { { HTML_UNDEF }, { HTML_UNDEF }, "latitude", mf1_latitude },
    { { HTML_UNDEF }, { HTML_UNDEF }, "license", mf1_licence },
    { { HTML_UNDEF }, { HTML_UNDEF }, "lister", mf1_lister },
    { { HTML_UNDEF }, { HTML_UNDEF }, "listing", mf1_listing },
    { { HTML_UNDEF }, { HTML_UNDEF }, "locality", mf1_locality },
    { { HTML_UNDEF }, { HTML_UNDEF }, "location", mf1_location },
    { { HTML_UNDEF }, { HTML_UNDEF }, "logo", mf1_logo },
    { { HTML_UNDEF }, { HTML_UNDEF }, "longitude", mf1_longitude },
    { { HTML_UNDEF }, { HTML_UNDEF }, "mailer", mf1_mailer },
    { { HTML_UNDEF }, { HTML_UNDEF }, "meet", mf1_meet },
    { { HTML_UNDEF }, { HTML_UNDEF }, "n", mf1_n },
    { { HTML_UNDEF }, { HTML_UNDEF }, "nickname", mf1_nickname },
    { { HTML_UNDEF }, { HTML_UNDEF }, "note", mf1_note },
    { { HTML_UNDEF }, { HTML_UNDEF }, "nutrition", mf1_nutrition },
    { { HTML_UNDEF }, { HTML_UNDEF }, "offer", mf1_offer },
    { { HTML_UNDEF }, { HTML_UNDEF }, "opening", mf1_opening },
    { { HTML_UNDEF }, { HTML_UNDEF }, "org", mf1_org },
    { { HTML_UNDEF }, { HTML_UNDEF }, "organization-name", mf1_organisation_name },
    { { HTML_UNDEF }, { HTML_UNDEF }, "organization-unit", mf1_organisation_unit },
    { { HTML_UNDEF }, { HTML_UNDEF }, "organizer", mf1_organiser },
    { { HTML_UNDEF }, { HTML_UNDEF }, "partstat", mf1_partstat },
    { { HTML_UNDEF }, { HTML_UNDEF }, "payment", mf1_payment },
    { { HTML_UNDEF }, { HTML_UNDEF }, "permalink", mf1_permalink },
    { { HTML_UNDEF }, { HTML_UNDEF }, "person", mf1_person },
    { { HTML_UNDEF }, { HTML_UNDEF }, "photo", mf1_photo },
    { { HTML_UNDEF }, { HTML_UNDEF }, "place", mf1_place },
    { { HTML_UNDEF }, { HTML_UNDEF }, "player", mf1_player },
    { { HTML_UNDEF }, { HTML_UNDEF }, "position", mf1_position },
    { { HTML_UNDEF }, { HTML_UNDEF }, "postal-code", mf1_postal_code },
    { { HTML_UNDEF }, { HTML_UNDEF }, "post-office-box", mf1_post_office_box },
    { { HTML_UNDEF }, { HTML_UNDEF }, "price", mf1_price },
    { { HTML_UNDEF }, { HTML_UNDEF }, "principles", mf1_principles },
    { { HTML_UNDEF }, { HTML_UNDEF }, "product", mf1_product },
    { { HTML_UNDEF }, { HTML_UNDEF }, "publications", mf1_publications },
    { { HTML_UNDEF }, { HTML_UNDEF }, "published", mf1_published },
    { { HTML_UNDEF }, { HTML_UNDEF }, "rating", mf1_rating },
    { { HTML_UNDEF }, { HTML_UNDEF }, "rdate", mf1_rdate },
    { { HTML_UNDEF }, { HTML_UNDEF }, "region", mf1_region },
    { { HTML_UNDEF }, { HTML_UNDEF }, "rent", mf1_rent },
    { { HTML_UNDEF }, { HTML_UNDEF }, "rev", mf1_rev },
    { { HTML_UNDEF }, { HTML_UNDEF }, "review", mf1_review },
    { { HTML_UNDEF }, { HTML_UNDEF }, "reviewer", mf1_reviewer },
    { { HTML_UNDEF }, { HTML_UNDEF }, "role", mf1_role },
    { { HTML_UNDEF }, { HTML_UNDEF }, "rrule", mf1_rrule },
    { { HTML_UNDEF }, { HTML_UNDEF }, "sample", mf1_sample },
    { { HTML_UNDEF }, { HTML_UNDEF }, "sell", mf1_sell },
    { { HTML_UNDEF }, { HTML_UNDEF }, "service", mf1_service },
    { { HTML_UNDEF }, { HTML_UNDEF }, "skill", mf1_skill },
    { { HTML_UNDEF }, { HTML_UNDEF }, "sort-string", mf1_sort_string },
    { { HTML_UNDEF }, { HTML_UNDEF }, "sound", mf1_sound },
    { { HTML_UNDEF }, { HTML_UNDEF }, "source-org", mf1_source_org },
    { { HTML_UNDEF }, { HTML_UNDEF }, "status", mf1_status },
    { { HTML_UNDEF }, { HTML_UNDEF }, "street-address", mf1_street_address },
    { { HTML_UNDEF }, { HTML_UNDEF }, "summary", mf1_summary },
    { { HTML_UNDEF }, { HTML_UNDEF }, "tel", mf1_tel },
    { { HTML_UNDEF }, { HTML_UNDEF }, "title", mf1_title },
    { { HTML_UNDEF }, { HTML_UNDEF }, "trade", mf1_trade },
    { { HTML_UNDEF }, { HTML_UNDEF }, "type", mf1_type },
    { { HTML_UNDEF }, { HTML_UNDEF }, "tz", mf1_tz },
    { { HTML_UNDEF }, { HTML_UNDEF }, "uid", mf1_uid },
    { { HTML_UNDEF }, { HTML_UNDEF }, "updated", mf1_updated },
    { { HTML_UNDEF }, { HTML_UNDEF }, "url", mf1_url },
    { { HTML_UNDEF }, { HTML_UNDEF }, "value", mf1_value },
    { { HTML_UNDEF }, { HTML_UNDEF }, "version", mf1_version },
    { { HTML_UNDEF }, { HTML_UNDEF }, "votes", mf1_votes },
    { { HTML_UNDEF }, { HTML_UNDEF }, "wanted", mf1_wanted },
    { { HTML_UNDEF }, { HTML_UNDEF }, "website", mf1_website },
    { { HTML_UNDEF }, { HTML_UNDEF }, "worst", mf1_worst },
    { { HTML_UNDEF }, { HTML_UNDEF }, "yield", mf1_yield },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_anniversary, dt_anniversary },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_accessed, dt_accessed },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_bday, dt_bday },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_duration, dt_duration },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_end, dt_end },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_expired, dt_expired },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_listed, dt_listed },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_published, dt_published },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_rev, dt_rev },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_reviewed, dt_reviewed },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_start, dt_start },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_dt_updated, dt_updated },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_e_content, e_content },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_e_description, e_description },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_e_instructions, e_instructions },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_action, p_action },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_additional_name, p_additional_name },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_adr, p_adr },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_affiliation, p_affiliation },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_altitude, p_altitude },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_attendee, p_attendee },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_author, p_author },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_average, p_average },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_best, p_best },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_brand, p_brand },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_category, p_category },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_comment, p_comment },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_contact, p_contact },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_content, p_content },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_count, p_count },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_country_name, p_country_name },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_description, p_description },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_education, p_education },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_entry, p_entry },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_experience, p_experience },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_extended_address, p_extended_address },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_family_name, p_family_name },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_gender_identity, p_gender_identity },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_geo, p_geo },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_given_name, p_given_name },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_honorific_prefix, p_honorific_prefix },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_honorific_suffix, p_honorific_suffix },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_ingredient, p_ingredient },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_item, p_item },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_job_title, p_job_title },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_label, p_label },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_latitude, p_latitude },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_lister, p_lister },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_locality, p_locality },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_location, p_location },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_longitude, p_longitude },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_name, p_name },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_nickname, p_nickname },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_note, p_note },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_nutrition, p_nutrition },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_org, p_org },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_organisation_name, p_organisation_name },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_organisation_unit, p_organisation_unit },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_organiser, p_organiser },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_post_office_box, p_post_office_box },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_postal_code, p_postal_code },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_price, p_price },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_publication, p_publication },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_rating, p_rating },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_region, p_region },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_review, p_review },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_reviewer, p_reviewer },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_role, p_role },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_rsvp, p_rsvp },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_sex, p_sex },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_skill, p_skill },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_sort_string, p_sort_string },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_street_address, p_street_address },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_summary, p_summary },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_tel, p_tel },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_tz, p_tz },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_votes, p_votes },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_worst, p_worst },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_p_yield, p_yield },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_audio, u_audio },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_bookmark_of, u_bookmark_of },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_email, u_email },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_featured, u_featured },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_geo, u_geo },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_identifier, u_identifier },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_impp, u_impp },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_in_reply_to, u_in_reply_to },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_key, u_key },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_like, u_like },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_like_of, u_like_of },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_logo, u_logo },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_photo, u_photo },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_repost, u_repost },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_repost_of, u_repost_of },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_sound, u_sound },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_syndication, u_syndication },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_uid, u_uid },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_url, u_url },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_video, u_video },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_dnsprefetch, u_dnsprefetch },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_external, u_external },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_icon, u_icon },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_noopener, u_noopener },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_noreferrer, u_noreferrer },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_preconnect, u_preconnect },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_prefetch, u_prefetch },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_preload, u_preload },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_prerender, u_prerender },
    { { HTML_UNDEF }, { HTML_UNDEF }, CSTR_u_search, u_search } };

void class_init (nitpick& nits)
{   type_master < t_class > :: init (nits, class_symbol_table, sizeof (class_symbol_table) / sizeof (symbol_entry < e_class >)); }

bool check_class_spelling (nitpick& nits, const html_version& , const ::std::string& original)
{   // if (check_spelling (nits, v, original)) return true;
    ::std::string s (quote (original));
    if (original == "h-cv") nits.pick (nit_confusion, es_warning, ec_microformat, quote (s), ": it's " H_RESUME " (unaccented), not h-cv");
    else if (   (original == "h-addr") ||
                (original == "p-addr") ||
                (original == "addr")) nits.pick (nit_abbreviated_correctly, es_warning, ec_microformat, quote (s), ": address is abbreviated correctly");
    else if (original == H_BREADCRUMBS) nits.pick (nit_confusion, es_warning, ec_microformat, quote (s), ": it's not " H_BREADCRUMBS ", it's " H_BREADCRUMB " when embedded");
    else if (original == "hcalendar") nits.pick (nit_confusion, es_warning, ec_microformat, quote (s), ": use vcalendar, not hCalendar");
    else if (original == "hcard") nits.pick (nit_confusion, es_warning, ec_microformat, quote (s), ": use vcard, not hCard");
    else if (original == "hevent") nits.pick (nit_confusion, es_warning, ec_microformat, quote (s), ": use vevent, not hEvent");
    else if (original == "h-calendar") nits.pick (nit_confusion, es_warning, ec_microformat, quote (s), ": it's " H_EVENT ", not h-calendar");
    else return false;
    return true; }
