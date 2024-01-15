/*
ssc (static site checker)
File Info
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

// microformats1: http://microformats.org/wiki/Main_Page#Specifications
#define H1_ATOM "hatom"
#define H1_AUDIO "haudio"
#define H1_CALENDAR "vcalendar"
#define H1_CARD "vcard"
#define H1_ENTRY "hentry"
#define H1_FEED "hfeed"
#define H1_EVENT "vevent"
#define H1_LISTING "hlisting"
#define H1_MEDIA "hmedia"
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
