/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

#pragma once
#include "microformat/microformat.h"

typedef microformat < html_class, c_error, c_generic, ela_ok, ela_ok, name_at > mf_unknown;

typedef microformat < html_class, h1_adr, c_mf1, ela_ok, ela_ok, post_office_box_at1, extended_address_at1, street_address_at1, locality_at1, region_at1,
                        postal_code_at1, country_name_at1 > mf_adr_v1;
typedef microformat < html_class, h1_aggregate, c_mf1, ela_ok, ela_ok, item_at1, fn_at1, url_at1, photo_at1, rating_at1, worst_at1, best_at1, average_at1, count_at1,
                        votes_at1, summary_at1 > mf_aggregate_v1;
typedef microformat < html_class, h1_atom, c_mf1, ela_ok, ela_ok, feed_at1, hentry_at1, entry_category_at1, entry_title_at1, entry_content_at1, entry_summary_at1, updated_at1,
                        published_at1, author_at1, bookmark_at1, tag_at1 > mf_atom_v1;
typedef microformat < html_class, h1_audio, c_mf1, ela_ok, ela_ok, fn_at1, album_at1, contributor_at1, duration_at1, item_at1, position_at1, category_at1,
                        published_at1, photo_at1, description_at1, sample_at1, enclosure_at1, payment_at1, price_at1, currency_at1, amount_at1 > mf_audio_v1;
typedef microformat < html_class, h1_calendar, c_mf1, ela_ok, ela_ok, dtstart_at1, summary_at1, location_at1, url_at1, dtend_at1, duration_at1, rdate_at1, rrule_at1,
                        category_at1, description_at1, uid_at1, geo_at1, latitude_at1, longitude_at1, attendee_at1, partstat_at1, role_at1, contact_at1,
                        organiser_at1, attach_at1, status_at1, profile_at1 > mf_calendar_v1;
typedef microformat < html_class, h1_card, c_mf1, ela_ok, ela_ok, fn_at1, n_at1, honorific_prefix_at1, given_name_at1, additional_name_at1, family_name_at1,
                        honorific_suffix_at1, adr_at1, post_office_box_at1, extended_address_at1, street_address_at1, locality_at1, region_at1,
                        postal_code_at1, country_name_at1, type_at1, value_at1, agent_at1, bday_at1, category_at1, class_at1, email_at1, geo_at1,
                        latitude_at1, longitude_at1, key_at1, label_at1, logo_at1, mailer_at1, nickname_at1, note_at1, org_at1, organisation_name_at1,
                        organisation_unit_at1, photo_at1, rev_at1, role_at1, sort_string_at1, sound_at1, tel_at1, title_at1, tz_at1, uid_at1, url_at1 > mf_card_v1;
typedef microformat < html_class, h1_geo, c_mf1, ela_ok, ela_ok, latitude_at1, longitude_at1 > mf_geo_v1;
typedef microformat < html_class, h1_listing, c_mf1, ela_ok, ela_ok, version_at1, sell_at1, rent_at1, meet_at1, announce_at1, offer_at1, wanted_at1, event_at1,
                        service_at1, lister_at1, fn_at1, email_at1, url_at1, tel_at1, dtlisted_at1, dtexpired_at1, price_at1, opening_at1, housing_at1,
                        product_at1, business_at1, event_at1, person_at1, place_at1, website_at1, url_at1, item_at1, photo_at1, geo_at1, adr_at1, summary_at1,
                        description_at1, item_at1, permalink_at1 > mf_listing_v1;
typedef microformat < html_class, h1_media, c_mf1, ela_ok, ela_ok, fn_at1, contributor_at1, photo_at1, player_at1, enclosure_at1 > mf_media_v1;
typedef microformat < html_class, h1_news, c_mf1, ela_ok, ela_ok, source_org_at1, dateline_at1, geo_at1, item_licence_at1, principles_at1 > mf_news_v1;
typedef microformat < html_class, h1_product, c_mf1, ela_ok, ela_ok, brand_at1, category_at1, price_at1, description_at1, fn_at1, photo_at1,  url_at1, review_at1,
                        listing_at1, identifier_at1, type_at1, value_at1 > mf_product_v1;
typedef microformat < html_class, h1_recipe, c_mf1, ela_ok, ela_ok, fn_at1, ingredient_at1, value_at1, type_at1, yield_at1, instructions_at1, duration_at1, photo_at1,
                        summary_at1, author_at1, published_at1, nutrition_at1, tag_at1, licence_at1 > mf_recipe_v1;
typedef microformat < html_class, h1_resume, c_mf1, ela_ok, ela_ok, summary_at1, contact_at1, education_at, experience_at1, skill_at1, affliation_at1,
                        publications_at1 > mf_resume_v1;
typedef microformat < html_class, h1_review, c_mf1, ela_ok, ela_ok, item_at1, product_at1, business_at1, event_at1, person_at1, place_at1, website_at1, url_at1, fn_at1,
                        url_at1, reviewer_at1, dtreviewed_at1, photo_at1, rating_at1, worst_at1, best_at1, description_at1, tag_at1, permalink_at1,
                        licence_at1 > mf_review_v1;

typedef microformat < html_class, h_adr, c_microformat, ela_ok, ela_ok, altitude_at, country_name_at, extended_address_at, geo_at, ugeo_at, label_at, latitude_at, locality_at,
                        longitude_at, post_office_box_at, postal_code_at, region_at, street_address_at, geo_ht > mf_adr;
typedef microformat < html_class, h_aggregate, c_microformat, ela_ok, ela_ok, average_at, best_at, category_at, count_at, item_at, name_at, rating_at, votes_at, worst_at >
                        mf_aggregate;
typedef microformat < html_class, h_breadcrumb, c_microformat, ela_ok, ela_ok, name_at, url_at > mf_breadcrumb;
typedef microformat < html_class, h_card, c_microformat, ela_ok, ela_ok, anniversary_at, bday_at, rev_at, additional_name_at, adr_at, altitude_at, category_at, country_name_at,
                        extended_address_at, family_name_at, gender_identity_at, geo_at, ugeo_at, given_name_at, honorific_prefix_at,
                        honorific_suffix_at, impp_at, job_title_at, key_at, label_at, latitude_at, locality_at, longitude_at,
                        name_at, nickname_at, note_at, org_at, organisation_name_at, organisation_unit_at, post_office_box_at,
                        postal_code_at, region_at, role_at, sex_at, sort_string_at, street_address_at, tel_at, tz_at,
                        email_at, ugeo_at, impp_at, key_at, logo_at, photo_at, sound_at, uid_at, url_at > mf_card;
typedef microformat < html_class, h_cite, c_microformat, ela_ok, ela_ok, accessed_at, published_at, author_at, content_at, name_at, publication_at, uid_at, url_at > mf_hcite;
typedef microformat < html_class, h_entry, c_microformat, ela_ok, ela_ok, published_at, updated_at, bookmark_of_at, comment_at, content_et, content_ht, author_at, category_at, geo_ht,
                        like_of_at, latitude_at, location_at, longitude_at, name_at, repost_of_at, rsvp_at, summary_at,
                        audio_at, featured_at, in_reply_to_at, like_at, photo_at, repost_at, syndication_at,
                        uid_at, url_at, video_at > mf_entry;
typedef microformat < html_class, h_event, c_microformat, ela_ok, ela_ok, duration_at, end_at, start_at, attendee_at, category_at, content_ht, description_at, geo_ht,
                        latitude_at, location_at, longitude_at, name_at, summary_at, url_at > mf_event;
typedef microformat < html_class, h_feed, c_microformat, ela_ok, ela_ok, name_at, author_at, url_at, photo_at, summary_at, entry_at > mf_feed;
typedef microformat < html_class, h_geo, c_microformat, ela_ok, ela_ok, latitude_at, longitude_at, altitude_at > mf_geo;
typedef microformat < html_class, h_item, c_microformat, ela_ok, ela_ok, name_at, url_at, photo_at > mf_item;
typedef microformat < html_class, h_listing, c_microformat, ela_ok, ela_ok, lister_at, listed_at, expired_at, price_at, category_at, action_at, url_at > mf_listing;
typedef microformat < html_class, h_product, c_microformat, ela_ok, ela_ok, description_ht, brand_at, category_at, name_at, price_at, review_at, identifier_at, photo_at,
                        url_at > mf_product;
typedef microformat < html_class, h_recipe, c_microformat, ela_ok, ela_ok, duration_at, published_at, instructions_at, author_at, category_at, ingredient_at, name_at,
                        nutrition_at, summary_at, yield_at, photo_at > mf_recipe;
typedef microformat < html_class, h_resume, c_microformat, ela_ok, ela_ok, affiliation_at, contact_at, education_at, experience_at, name_at, skill_at, summary_at > mf_resume;
typedef microformat < html_class, h_review, c_microformat, ela_ok, ela_ok, author_at, best_at, category_at, content_et, item_at, location_at, name_at, published_at,
                        rating_at, summary_at, syndication_at, url_at, worst_at > mf_review;

// non-MF rels need stripping out
typedef microformat < rel, r_about, c_generic, ela_ok, ela_ok, about_rt > mf_about;
typedef microformat < rel, r_accessibility, c_draft, ela_ok, ela_ok, accessibility_rt > mf_accessibility;
typedef microformat < rel, r_acquaintance, c_xfn, ela_no, ela_external, acquaintance_rt > mf_acquaintance;
typedef microformat < rel, r_alternative, c_html4 | c_atom, ela_external, ela_external, alternative_rt > mf_alternative;
typedef microformat < rel, r_amphtml, 0x0100, ela_hyperlink, ela_hyperlink, amphtml_rt > mf_amphtml; // https://github.com/ampproject/amphtml
typedef microformat < rel, r_appendix, c_html4, ela_ok, ela_ok, appendix_rt > mf_appendix;
typedef microformat < rel, r_apple_touch_icon, c_safari, ela_external, ela_no, apple_touch_icon_rt > mf_apple_touch_icon;
typedef microformat < rel, r_apple_touch_icon_precomposed, c_safari, ela_external, ela_no, apple_touch_icon_precomposed_rt > mf_apple_touch_icon_precomposed;
typedef microformat < rel, r_apple_touch_startup_image, c_safari, ela_external, ela_no, apple_touch_startup_image_rt > mf_apple_touch_startup_image;
typedef microformat < rel, r_archived, c_generic, ela_external, ela_hyperlink, archived_rt > mf_archived;     // https://sitemorse.com/rel-archived/
typedef microformat < rel, r_archives, c_generic, ela_ok, ela_ok, archives_rt > mf_archives;
typedef microformat < rel, r_attachment, c_generic, ela_hyperlink, ela_hyperlink, attachment_rt > mf_attachment;
typedef microformat < rel, r_author, c_microformat, ela_ok, ela_ok, author_rt > mf_author;
typedef microformat < rel, r_authorisation_endpoint, c_indieauth, ela_external, ela_no, authorisation_endpoint_rt > mf_authorisation_endpoint;
typedef microformat < rel, r_banner, c_html3 | c_dropped, ela_ok, ela_ok, banner_rt > mf_banner;
typedef microformat < rel, r_begin, c_html4 | c_dropped, ela_ok, ela_ok, begin_rt > mf_begin;
typedef microformat < rel, r_biblioentry, c_html4 | c_dropped, ela_ok, ela_ok, biblioentry_rt > mf_biblioentry;
typedef microformat < rel, r_bibliography, c_draft | c_html4 | c_dropped, ela_ok, ela_ok, bibliography_rt > mf_bibliography;
typedef microformat < rel, r_blocked_by, c_generic, ela_ok, ela_ok, blocked_by_rt > mf_blocked_by;
typedef microformat < rel, r_bookmark, c_html4, ela_no, ela_ok, bookmark_rt > mf_bookmark;
typedef microformat < rel, r_canonical, c_generic, ela_hyperlink, ela_hyperlink, canonical_rt > mf_canonical;
typedef microformat < rel, r_category, c_generic, ela_hyperlink, ela_hyperlink, category_rt > mf_category;

typedef microformat < rel, r_cc_permits, c_cc, ela_ok, ela_ok, cc_permits_rt > mf_cc_permits;
typedef microformat < rel, r_cc_requires, c_cc, ela_ok, ela_ok, cc_requires_rt > mf_cc_requires;
typedef microformat < rel, r_cc_prohibits, c_cc, ela_ok, ela_ok, cc_prohibits_rt > mf_cc_prohibits;
typedef microformat < rel, r_cc_jurisdiction, c_cc, ela_ok, ela_ok, cc_jurisdiction_rt > mf_cc_jurisdiction;
typedef microformat < rel, r_cc_legalcode, c_cc, ela_ok, ela_ok, cc_legalcode_rt > mf_cc_legalcode;
typedef microformat < rel, r_cc_deprecatedon, c_cc, ela_ok, ela_ok, cc_deprecatedon_rt > mf_cc_deprecatedon;
typedef microformat < rel, r_cc_licence, c_cc, ela_ok, ela_ok, cc_licence_rt > mf_cc_licence;
typedef microformat < rel, r_cc_morepermissions, c_cc, ela_ok, ela_ok, cc_morepermissions_rt > mf_cc_morepermissions;
typedef microformat < rel, r_cc_attributionname, c_cc, ela_ok, ela_ok, cc_attributionname_rt > mf_cc_attributionname;   // illustrates ssc design issue; mf needs reworking
typedef microformat < rel, r_cc_attributionurl, c_cc, ela_ok, ela_ok, cc_attributionurl_rt > mf_cc_attributionurl;
typedef microformat < rel, r_cc_useguidelines, c_cc, ela_ok, ela_ok, cc_useguidelines_rt > mf_cc_useguidelines;

typedef microformat < rel, r_chapter, c_html4, ela_ok, ela_ok, chapter_rt > mf_chapter;
typedef microformat < rel, r_child, c_xfn | c_html4 | c_dropped, ela_external, ela_external, child_rt > mf_child;
typedef microformat < rel, r_chrome_webstore_item, c_generic, ela_external, ela_no, chrome_webstore_item_rt > mf_chrome_webstore_item;
typedef microformat < rel, r_citation, c_html4 | c_dropped, ela_ok, ela_ok, citation_rt > mf_citation;
typedef microformat < rel, r_cite, c_draft, ela_ok, ela_ok, cite_rt > mf_relcite;
typedef microformat < rel, r_cite_as, c_generic, ela_ok, ela_ok, cite_as_rt > mf_cite_as;
typedef microformat < rel, r_code_licence, c_generic, ela_hyperlink, ela_hyperlink, code_licence_rt > mf_code_licence;
typedef microformat < rel, r_code_repository, c_generic, ela_hyperlink, ela_hyperlink, code_licence_rt > mf_code_repository;
typedef microformat < rel, r_colleague, c_xfn, ela_no, ela_external, colleague_rt > mf_colleague;
typedef microformat < rel, r_collection, c_html4 | c_dropped, ela_ok, ela_ok, collection_rt > mf_collection;
typedef microformat < rel, r_comment, c_generic, ela_ok, ela_ok, comment_rt > mf_comment;
typedef microformat < rel, r_component, c_generic, ela_external, ela_no, component_rt > mf_component;
typedef microformat < rel, r_contact, c_xfn, ela_no, ela_external, contact_rt > mf_contact;
typedef microformat < rel, r_content_licence, c_generic, ela_ok, ela_ok, content_licence_rt > mf_content_licence;
typedef microformat < rel, r_content_repository, c_generic, ela_hyperlink, ela_hyperlink, content_repository_rt > mf_content_repository;
typedef microformat < rel, r_contents, c_html4, ela_ok, ela_ok, contents_rt > mf_contents;
typedef microformat < rel, r_contribution, c_generic, ela_ok, ela_ok, contribution_rt > mf_contribution;
typedef microformat < rel, r_convertedfrom, c_generic, ela_ok, ela_ok, convertedfrom_rt > mf_convertedfrom;
typedef microformat < rel, r_copyright, c_html4, ela_ok, ela_ok, copyright_rt > mf_copyright;
typedef microformat < rel, r_coresident, c_xfn, ela_no, ela_external, coresident_rt > mf_coresident;
typedef microformat < rel, r_coworker, c_xfn, ela_no, ela_external, coworker_rt > mf_coworker;
typedef microformat < rel, r_create_form, c_generic, ela_ok, ela_ok, create_form_rt > mf_create_form;
typedef microformat < rel, r_crush, c_xfn, ela_no, ela_external, crush_rt > mf_crush;
typedef microformat < rel, r_current, c_generic, ela_ok, ela_ok, current_rt > mf_current;
typedef microformat < rel, r_date, c_xfn, ela_no, ela_external, date_rt > mf_date;
typedef microformat < rel, r_dcterms_conformsto, c_dcterms, ela_external, ela_no, dcterms_conformsto_rt > mf_dcterms_conformsto;
typedef microformat < rel, r_dcterms_contributor, c_dcterms, ela_external, ela_no, dcterms_contributor_rt > mf_dcterms_contributor;
typedef microformat < rel, r_dcterms_creator, c_dcterms, ela_external, ela_no, dcterms_creator_rt > mf_dcterms_creator;
typedef microformat < rel, r_dcterms_description, c_dcterms, ela_external, ela_no, dcterms_description_rt > mf_dcterms_description;
typedef microformat < rel, r_dcterms_hasformat, c_dcterms, ela_external, ela_no, dcterms_hasformat_rt > mf_dcterms_hasformat;
typedef microformat < rel, r_dcterms_haspart, c_dcterms, ela_external, ela_no, dcterms_haspart_rt > mf_dcterms_haspart;
typedef microformat < rel, r_dcterms_hasversion, c_dcterms, ela_external, ela_no, dcterms_hasversion_rt > mf_dcterms_hasversion;
typedef microformat < rel, r_dcterms_isformatof, c_dcterms, ela_external, ela_no, dcterms_isformatof_rt > mf_dcterms_isformatof;
typedef microformat < rel, r_dcterms_ispartof, c_dcterms, ela_external, ela_no, dcterms_ispartof_rt > mf_dcterms_ispartof;
typedef microformat < rel, r_dcterms_isreferencedby, c_dcterms, ela_external, ela_no, dcterms_isreferencedby_rt > mf_dcterms_isreferencedby;
typedef microformat < rel, r_dcterms_isreplacedby, c_dcterms, ela_external, ela_no, dcterms_isreplacedby_rt > mf_dcterms_isreplacedby;
typedef microformat < rel, r_dcterms_isrequiredby, c_dcterms, ela_external, ela_no, dcterms_isrequiredby_rt > mf_dcterms_isrequiredby;
typedef microformat < rel, r_dcterms_isversionof, c_dcterms, ela_external, ela_no, dcterms_isversionof_rt > mf_dcterms_isversionof;
typedef microformat < rel, r_dcterms_licence, c_dcterms, ela_external, ela_no, dcterms_licence_rt > mf_dcterms_licence;
typedef microformat < rel, r_dcterms_mediator, c_dcterms, ela_external, ela_no, dcterms_mediator_rt > mf_dcterms_mediator;
typedef microformat < rel, r_dcterms_publisher, c_dcterms, ela_external, ela_no, dcterms_publisher_rt > mf_dcterms_publisher;
typedef microformat < rel, r_dcterms_references, c_dcterms, ela_external, ela_no, dcterms_references_rt > mf_dcterms_references;
typedef microformat < rel, r_dcterms_relation, c_dcterms, ela_external, ela_no, dcterms_relation_rt > mf_dcterms_relation;
typedef microformat < rel, r_dcterms_replaces, c_dcterms, ela_external, ela_no, dcterms_replaces_rt > mf_dcterms_replaces;
typedef microformat < rel, r_dcterms_requires, c_dcterms, ela_external, ela_no, dcterms_requires_rt > mf_dcterms_requires;
typedef microformat < rel, r_dcterms_rightsholder, c_dcterms, ela_external, ela_no, dcterms_rightsholder_rt > mf_dcterms_rightsholder;
typedef microformat < rel, r_dcterms_source, c_dcterms, ela_external, ela_no, dcterms_source_rt > mf_dcterms_source;
typedef microformat < rel, r_dcterms_subject, c_dcterms, ela_external, ela_no, dcterms_subject_rt > mf_dcterms_subject;
typedef microformat < rel, r_definition, c_html4 | c_dropped, ela_ok, ela_ok, definition_rt > mf_definition;
typedef microformat < rel, r_describedby, c_generic, ela_ok, ela_ok, describedby_rt > mf_describedby;
typedef microformat < rel, r_describes, c_generic, ela_ok, ela_ok, describes_rt > mf_describes;
typedef microformat < rel, r_directory, c_draft | c_microformat, ela_ok, ela_ok, directory_rt > mf_directory;
typedef microformat < rel, r_disclaimer, c_html4 | c_dropped, ela_ok, ela_ok, disclaimer_rt > mf_disclaimer;
typedef microformat < rel, r_disclosure, c_generic, ela_no, ela_external, disclosure_rt > mf_disclosure;
typedef microformat < rel, r_discussion, c_draft | c_microformat, ela_hyperlink, ela_hyperlink, discussion_rt > mf_discussion;
typedef microformat < rel, r_dnsprefetch, c_generic, ela_external, ela_no, dnsprefetch_rt > mf_dnsprefetch;
typedef microformat < rel, r_docs_oasis_open_org_ns_cmis_link_200908_acl, c_generic, ela_external, ela_external, docs_oasis_open_org_ns_cmis_link_200908_acl_rt > mf_docs_oasis_open_org_ns_cmis_link_200908_acl;
typedef microformat < rel, r_duplicate, c_generic, ela_ok, ela_ok, duplicate_rt > mf_duplicate;
typedef microformat < rel, r_edit, c_generic, ela_hyperlink, ela_no, edit_rt > mf_edit;
typedef microformat < rel, r_edit_form, c_generic, ela_ok, ela_ok, edit_form_rt > mf_edit_form;
typedef microformat < rel, r_edit_media, c_generic, ela_ok, ela_ok, edit_media_rt > mf_edit_media;
typedef microformat < rel, r_editor, c_html4 | c_dropped, ela_ok, ela_ok, editor_rt > mf_editor;
typedef microformat < rel, r_edituri, c_atom, ela_external, ela_no, edituri_rt > mf_edituri;
typedef microformat < rel, r_enclosure, c_draft | c_microformat | c_atom, ela_external, ela_external, enclosure_rt > mf_enclosure;
typedef microformat < rel, r_end, c_html4 | c_dropped, ela_ok, ela_ok, end_rt > mf_end;
typedef microformat < rel, r_endorsed, c_generic, ela_ok, ela_ok, endorsed_rt > mf_endorsed;
typedef microformat < rel, r_entry_content, c_generic, ela_ok, ela_ok, entry_content_rt > mf_entry_content;
typedef microformat < rel, r_external, c_generic, ela_ok, ela_ok, external_rt > mf_external;
typedef microformat < rel, r_fan, c_generic, ela_ok, ela_ok, fan_rt > mf_fan;
typedef microformat < rel, r_feed, c_generic, ela_ok, ela_ok, feed_rt > mf_relfeed;
typedef microformat < rel, r_first, c_html4 | c_dropped, ela_hyperlink, ela_hyperlink, first_rt > mf_first;
typedef microformat < rel, r_footnote, c_html4 | c_dropped, ela_ok, ela_ok, footnote_rt > mf_footnote;
typedef microformat < rel, r_friend, c_xfn, ela_no, ela_external, friend_rt > mf_friend;
typedef microformat < rel, r_gbfs, c_generic, ela_external, ela_no, gbfs_rt > mf_gbfs;
typedef microformat < rel, r_gtfs_realtime, c_generic, ela_external, ela_no, gtfs_realtime_rt > mf_gtfs_realtime;
typedef microformat < rel, r_gtfs_static, c_generic, ela_external, ela_no, gtfs_static_rt > mf_gtfs_static;
typedef microformat < rel, r_glossary, c_html4, ela_ok, ela_ok, glossary_rt > mf_glossary;
typedef microformat < rel, r_group, c_draft, ela_ok, ela_ok, group_rt > mf_group;
typedef microformat < rel, r_help, c_html4, ela_ok, ela_ok, help_rt > mf_help;
typedef microformat < rel, r_home, c_draft | c_microformat, ela_hyperlink, ela_hyperlink, home_rt > mf_home;
typedef microformat < rel, r_hosts, c_generic, ela_ok, ela_ok, hosts_rt > mf_hosts;
typedef microformat < rel, r_hub, c_generic, ela_hyperlink, ela_hyperlink, hub_rt > mf_hub;
typedef microformat < rel, r_icon, c_generic, ela_ok, ela_ok, icon_rt > mf_icon;
typedef microformat < rel, r_image_src, c_generic, ela_external, ela_no, image_src_rt > mf_image_src;
typedef microformat < rel, r_import, c_generic, ela_external, ela_no, import_rt > mf_import;
typedef microformat < rel, r_in_reply_to, c_generic, ela_hyperlink, ela_hyperlink, in_reply_to_rt > mf_in_reply_to;
typedef microformat < rel, r_index, c_html4 | c_dropped, ela_hyperlink, ela_hyperlink, index_rt > mf_index;
typedef microformat < rel, r_intervalafter, c_generic, ela_ok, ela_ok, intervalafter_rt > mf_intervalafter;
typedef microformat < rel, r_intervalbefore, c_generic, ela_ok, ela_ok, intervalbefore_rt > mf_intervalbefore;
typedef microformat < rel, r_intervalcontains, c_generic, ela_ok, ela_ok, intervalcontains_rt > mf_intervalcontains;
typedef microformat < rel, r_intervaldisjoint, c_generic, ela_ok, ela_ok, intervaldisjoint_rt > mf_intervaldisjoint;
typedef microformat < rel, r_intervalduring, c_generic, ela_ok, ela_ok, intervalduring_rt > mf_intervalduring;
typedef microformat < rel, r_intervalequals, c_generic, ela_ok, ela_ok, intervalequals_rt > mf_intervalequals;
typedef microformat < rel, r_intervalfinishedby, c_generic, ela_ok, ela_ok, intervalfinishedby_rt > mf_intervalfinishedby;
typedef microformat < rel, r_intervalfinishes, c_generic, ela_ok, ela_ok, intervalfinishes_rt > mf_intervalfinishes;
typedef microformat < rel, r_intervalin, c_generic, ela_ok, ela_ok, intervalin_rt > mf_intervalin;
typedef microformat < rel, r_intervalmeets, c_generic, ela_ok, ela_ok, intervalmeets_rt > mf_intervalmeets;
typedef microformat < rel, r_intervalmetby, c_generic, ela_ok, ela_ok, intervalmetby_rt > mf_intervalmetby;
typedef microformat < rel, r_intervaloverlappedby, c_generic, ela_ok, ela_ok, intervaloverlappedby_rt > mf_intervaloverlappedby;
typedef microformat < rel, r_intervaloverlaps, c_generic, ela_ok, ela_ok, intervaloverlaps_rt > mf_intervaloverlaps;
typedef microformat < rel, r_intervalstartedby, c_generic, ela_ok, ela_ok, intervalstartedby_rt > mf_intervalstartedby;
typedef microformat < rel, r_intervalstarts, c_generic, ela_ok, ela_ok, intervalstarts_rt > mf_intervalstarts;
typedef microformat < rel, r_issues, c_generic, ela_hyperlink, ela_hyperlink, issues_rt > mf_issues;
typedef microformat < rel, r_item, c_generic, ela_ok, ela_ok, item_rt > mf_relitem;
typedef microformat < rel, r_item, c_generic, ela_ok, ela_ok, item_rt > mf_rtitem;
typedef microformat < rel, r_item_licence, c_microformat, ela_no, ela_ok, item_licence_rt > mf_item_licence;
typedef microformat < rel, r_its_rules, c_its, ela_ok, ela_no, its_rules_rt > mf_its_rules;
typedef microformat < rel, r_jslicence, c_generic, ela_hyperlink, ela_hyperlink, jslicence_rt > mf_jslicence;
typedef microformat < rel, r_kin, c_xfn, ela_no, ela_external, kin_rt > mf_kin;
typedef microformat < rel, r_kinetic_stylesheet, c_generic, ela_ok, ela_ok, kinetic_stylesheet_rt > mf_kinetic_stylesheet;
typedef microformat < rel, r_last, c_html4 | c_dropped, ela_hyperlink, ela_hyperlink, last_rt > mf_last;
typedef microformat < rel, r_latest_version, c_generic, ela_ok, ela_ok, latest_version_rt > mf_latest_version;
typedef microformat < rel, r_licence, c_microformat, ela_ok, ela_ok, licence_rt > mf_licence;
typedef microformat < rel, r_lightbox, c_lightbox, ela_no, ela_popup, lightbox_rt > mf_lightbox;
typedef microformat < rel, r_lightvideo, c_lightbox, ela_no, ela_popup, lightvideo_rt > mf_lightvideo;
typedef microformat < rel, r_logo, c_rejected, ela_ok, ela_ok, logo_rt > mf_logo;
typedef microformat < rel, r_longdesc, c_draft, ela_ok, ela_ok, longdesc_rt > mf_longdesc;
typedef microformat < rel, r_lrdd, c_generic, ela_ok, ela_ok, lrdd_rt > mf_lrdd;
typedef microformat < rel, r_m_pagescroll2id, c_generic, ela_ok, ela_ok, m_pagescroll2id_rt > mf_m_pagescroll2id;
typedef microformat < rel, r_made, c_generic, ela_ok, ela_ok, made_rt > mf_made;
typedef microformat < rel, r_manifest, c_generic, ela_external, ela_no, manifest_rt > mf_manifest;
typedef microformat < rel, r_map, c_draft, ela_ok, ela_ok, map_rt > mf_map;
typedef microformat < rel, r_maskicon, c_safari, ela_external, ela_no, maskicon_rt > mf_maskicon;
typedef microformat < rel, r_me, c_xfn | c_microformat, ela_ok, ela_ok, me_rt > mf_me;
typedef microformat < rel, r_member, c_draft, ela_ok, ela_ok, member_rt > mf_member;
typedef microformat < rel, r_memento, c_generic, ela_ok, ela_ok, memento_rt > mf_memento;
typedef microformat < rel, r_met, c_xfn, ela_no, ela_external, met_rt > mf_met;
typedef microformat < rel, r_meta, c_generic, ela_external, ela_no, meta_rt > mf_meta;
typedef microformat < rel, r_micropub, c_generic, ela_external, ela_no, micropub_rt > mf_micropub;
typedef microformat < rel, r_microsummary, c_generic, ela_ok, ela_ok, microsummary_rt > mf_microsummary;
typedef microformat < rel, r_monitor, c_generic, ela_ok, ela_ok, monitor_rt > mf_monitor;
typedef microformat < rel, r_monitor_group, c_generic, ela_ok, ela_ok, monitor_group_rt > mf_monitor_group;
typedef microformat < rel, r_muse, c_xfn, ela_no, ela_external, muse_rt > mf_muse;
typedef microformat < rel, r_navigate, c_html4 | c_dropped, ela_ok, ela_ok, navigate_rt > mf_navigate;
typedef microformat < rel, r_neighbour, c_xfn, ela_no, ela_external, neighbour_rt > mf_neighbour;
typedef microformat < rel, r_next, c_html4, ela_external, ela_external, next_rt > mf_next;
typedef microformat < rel, r_next_archive, c_generic, ela_ok, ela_ok, next_archive_rt > mf_next_archive;
typedef microformat < rel, r_nofollow, c_microformat, ela_no, ela_external, nofollow_rt > mf_nofollow;
typedef microformat < rel, r_noopener, c_generic, ela_no, c_annotation, noopener_rt > mf_noopener;
typedef microformat < rel, r_noreferrer, c_generic, ela_ok, ela_ok, noreferrer_rt > mf_noreferrer;
typedef microformat < rel, r_openid2_local_id, c_openid, ela_external, ela_no, openid2_local_id_rt > mf_openid2_local_id;
typedef microformat < rel, r_openid2_provider, c_openid, ela_external, ela_no, openid2_provider_rt > mf_openid2_provider;
typedef microformat < rel, r_openid_delegate, c_openid, ela_external, ela_no, openid_delegate_rt > mf_openid_delegate;
typedef microformat < rel, r_openid_server, c_openid, ela_external, ela_no, openid_server_rt > mf_openid_server;
typedef microformat < rel, r_origin, c_html4 | c_dropped, ela_ok, ela_ok, origin_rt > mf_origin;
typedef microformat < rel, r_original, c_generic, ela_ok, ela_ok, original_rt > mf_original;
typedef microformat < rel, r_p3pv1, c_generic, ela_external, ela_no, p3pv1_rt > mf_p3pv1;
typedef microformat < rel, r_parent, c_xfn | c_html4 | c_dropped, ela_external, ela_external, parent_rt > mf_parent;
typedef microformat < rel, r_pavatar, c_rejected, ela_ok, ela_ok, pavatar_rt > mf_pavatar;
typedef microformat < rel, r_payment, c_draft | c_microformat, ela_ok, ela_ok, payment_rt > mf_payment;
typedef microformat < rel, r_permalink, c_generic, ela_ok, ela_ok, permalink_rt > mf_permalink;
typedef microformat < rel, r_pgpkey, c_generic, ela_external, ela_no, pgpkey_rt > mf_pgpkey;
typedef microformat < rel, r_pingback, c_generic, ela_external, ela_no, pingback_rt > mf_pingback;
typedef microformat < rel, r_pointer, c_html4 | c_dropped, ela_ok, ela_ok, pointer_rt > mf_pointer;
typedef microformat < rel, r_popover, c_generic, ela_ok, ela_ok, popover_rt > mf_popover;
typedef microformat < rel, r_preconnect, c_generic, ela_external, ela_no, preconnect_rt > mf_preconnect;
typedef microformat < rel, r_predecessor_version, c_generic, ela_ok, ela_ok, predecessor_version_rt > mf_predecessor_version;
typedef microformat < rel, r_prefetch, c_draft, ela_ok, ela_ok, prefetch_rt > mf_prefetch;
typedef microformat < rel, r_preload, c_draft, ela_ok, ela_ok, preload_rt > mf_preload;
typedef microformat < rel, r_prerender, c_draft, ela_external, ela_external, prerender_rt > mf_prerender;
typedef microformat < rel, r_prev, c_html4, ela_external, ela_external, prev_rt > mf_prev;
typedef microformat < rel, r_prev_archive, c_generic, ela_ok, ela_ok, prev_archive_rt > mf_prev_archive;
typedef microformat < rel, r_preview, c_html4, ela_external, ela_external, preview_rt > mf_preview;
typedef microformat < rel, r_principles, c_microformat, ela_no, ela_ok, principles_rt > mf_principles;
typedef microformat < rel, r_privacy, c_generic, ela_ok, ela_ok, privacy_rt > mf_privacy;
typedef microformat < rel, r_privacy_policy, c_generic, ela_ok, ela_ok, privacy_policy_rt > mf_privacy_policy;
typedef microformat < rel, r_profile, c_draft, ela_external, ela_external_contextual, profile_rt > mf_profile;
typedef microformat < rel, r_pronunciation, c_draft | c_microformat, ela_ok, ela_ok, pronunciation_rt > mf_pronunciation;
typedef microformat < rel, r_publickey, c_generic, ela_ok, ela_ok, publickey_rt > mf_publickey;
typedef microformat < rel, r_publisher, c_html4 | c_dropped, ela_external, ela_external, publisher_rt > mf_publisher;
typedef microformat < rel, r_radioepg, c_generic, ela_external, ela_external, radioepg_rt > mf_radioepg;
typedef microformat < rel, r_referral, c_generic, ela_ok, ela_ok, referral_rt > mf_referral;
typedef microformat < rel, r_related, c_atom, ela_ok, ela_ok, related_rt > mf_related;
typedef microformat < rel, r_rendition, c_generic, ela_external, ela_external, rendition_rt > mf_rendition;
typedef microformat < rel, r_replies, c_generic, ela_ok, ela_ok, replies_rt > mf_replies;
typedef microformat < rel, r_reply_to, c_generic, ela_external, ela_hyperlink, reply_to_rt > mf_reply_to;
typedef microformat < rel, r_resource, c_generic, ela_ok, ela_ok, resource_rt > mf_resource;
typedef microformat < rel, r_respond_proxy, c_generic, ela_ok, ela_ok, respond_proxy_rt > mf_respond_proxy;
typedef microformat < rel, r_respond_redirect, c_generic, ela_ok, ela_ok, respond_redirect_rt > mf_respond_redirect;
typedef microformat < rel, r_restconf, c_generic, ela_ok, ela_ok, restconf_rt > mf_restconf;
typedef microformat < rel, r_root, c_generic, ela_hyperlink, ela_hyperlink, root_rt > mf_root;
typedef microformat < rel, r_ontology_dc, c_dcterms, ela_external, ela_no, ontology_dc_rt > mf_ontology_dc;
typedef microformat < rel, r_ontology_dcterms, c_dcterms, ela_external, ela_no, ontology_dcterms_rt > mf_ontology_dcterms;
typedef microformat < rel, r_search, c_generic, ela_ok, ela_ok, search_rt > mf_search;
typedef microformat < rel, r_section, c_html4, ela_ok, ela_ok, section_rt > mf_section;
typedef microformat < rel, r_self, c_atom, ela_ok, ela_ok, self_rt > mf_self;
typedef microformat < rel, r_service, c_atom,  ela_external, ela_no, service_rt > mf_service;
typedef microformat < rel, r_service_desc, c_generic, ela_ok, ela_ok, service_desc_rt > mf_service_desc;
typedef microformat < rel, r_service_doc, c_generic, ela_ok, ela_ok, service_doc_rt > mf_service_doc;
typedef microformat < rel, r_service_meta, c_generic, ela_ok, ela_ok, service_meta_rt > mf_service_meta;
typedef microformat < rel, r_shortlink, c_draft,  ela_external, ela_no, shortlink_rt > mf_shortlink;
typedef microformat < rel, r_sibling, c_xfn | c_html4 | c_dropped, ela_no, ela_external, sibling_rt > mf_sibling;
typedef microformat < rel, r_sidebar, c_generic, ela_hyperlink, ela_hyperlink, sidebar_rt > mf_sidebar;
typedef microformat < rel, r_sitemap, c_generic, ela_external, ela_no, sitemap_rt > mf_sitemap;
typedef microformat < rel, r_source, c_draft, ela_ok, ela_ok, source_rt > mf_source;
typedef microformat < rel, r_sponsor, c_generic, ela_ok, ela_ok, sponsor_rt > mf_sponsor;
typedef microformat < rel, r_spouse, c_xfn, ela_no, ela_external, spouse_rt > mf_spouse;
typedef microformat < rel, r_start, c_html4, ela_ok, ela_ok, start_rt > mf_start;
typedef microformat < rel, r_status, c_draft, ela_ok, ela_ok, status_rt > mf_status;
typedef microformat < rel, r_stylesheet, c_html4, ela_external, ela_no, stylesheet_rt > mf_stylesheet;
typedef microformat < rel, r_stylesheetless, c_generic, ela_external, ela_no, stylesheetless_rt > mf_stylesheetless;
typedef microformat < rel, r_subresource, c_generic, ela_external, ela_no, subresource_rt > mf_subresource;
typedef microformat < rel, r_subsection, c_html4, ela_ok, ela_ok, subsection_rt > mf_subsection;
typedef microformat < rel, r_successor_version, c_generic, ela_ok, ela_ok, successor_version_rt > mf_successor_version;
typedef microformat < rel, r_sunset, c_generic, ela_ok, ela_ok, sunset_rt > mf_sunset;
typedef microformat < rel, r_supercedes, c_generic, ela_ok, ela_ok, supercedes_rt > mf_supercedes;
typedef microformat < rel, r_sweetheart, c_xfn, ela_no, ela_external, sweetheart_rt > mf_sweetheart;
typedef microformat < rel, r_sword, c_generic, ela_hyperlink, ela_no, sword_rt > mf_sword;
typedef microformat < rel, r_syndication, c_generic, ela_hyperlink, ela_hyperlink, syndication_rt > mf_syndication;
typedef microformat < rel, r_tag, c_microformat, ela_no, ela_ok, tag_rt > mf_tag;
typedef microformat < rel, r_terms_of_service, c_generic, ela_ok, ela_ok, terms_of_service_rt > mf_terms_of_service;
typedef microformat < rel, r_timegate, c_generic, ela_ok, ela_ok, timegate_rt > mf_timegate;
typedef microformat < rel, r_timemap, c_generic, ela_ok, ela_ok, timemap_rt > mf_timemap;
typedef microformat < rel, r_timesheet, c_generic, ela_external, ela_no, timesheet_rt > mf_timesheet;
typedef microformat < rel, r_toc, c_html4, ela_ok, ela_ok, toc_rt > mf_toc;
typedef microformat < rel, r_token_endpoint, c_generic, ela_external, ela_no, token_endpoint_rt > mf_token_endpoint;
typedef microformat < rel, r_tooltip, c_generic, ela_ok, ela_ok, tooltip_rt > mf_tooltip;
typedef microformat < rel, r_top, c_html4 | c_dropped, ela_ok, ela_ok, top_rt > mf_top;
typedef microformat < rel, r_trackback, c_generic, ela_ok, ela_ok, trackback_rt > mf_trackback;
typedef microformat < rel, r_trademark, c_html4 | c_dropped, ela_ok, ela_ok, trademark_rt > mf_trademark;
typedef microformat < rel, r_transformation, c_grddl, ela_ok, ela_ok, transformation_rt > mf_transformation;
typedef microformat < rel, r_translation, c_html4 | c_dropped, ela_ok, ela_ok, translation_rt > mf_translation;
typedef microformat < rel, r_type, c_generic, ela_ok, ela_ok, type_rt > mf_type;
typedef microformat < rel, r_unendorsed, c_generic, ela_ok, ela_ok, unendorsed_rt > mf_unendorsed;
typedef microformat < rel, r_up, c_html4 | c_dropped, ela_ok, ela_ok, up_rt > mf_up;
typedef microformat < rel, r_urc, c_html4 | c_dropped, ela_ok, ela_ok, urc_rt > mf_urc;
typedef microformat < rel, r_user, c_generic, ela_ok, ela_ok, user_rt > mf_user;
typedef microformat < rel, r_vcalendar_child, c_draft | c_hcal, ela_ok, ela_ok, vcalendar_child_rt > mf_vcalendar_child;
typedef microformat < rel, r_vcalendar_parent, c_draft | c_hcal, ela_ok, ela_ok, vcalendar_parent_rt > mf_vcalendar_parent;
typedef microformat < rel, r_vcalendar_sibling, c_draft | c_hcal, ela_ok, ela_ok, vcalendar_sibling_rt > mf_vcalendar_sibling;
typedef microformat < rel, r_vcs_git, c_vcs, ela_ok, ela_ok, vcs_git_rt > mf_vcs_git;
typedef microformat < rel, r_vcs_svn, c_vcs, ela_ok, ela_ok, vcs_svn_rt > mf_vcs_svn;
typedef microformat < rel, r_version_history, c_generic, ela_ok, ela_ok, version_history_rt > mf_version_history;
typedef microformat < rel, r_via, c_atom, ela_ok, ela_ok, via_rt > mf_via;
typedef microformat < rel, r_w_api_org, c_draft, ela_ok, ela_ok, w_api_org_rt > mf_w_api_org;
typedef microformat < rel, r_webmention, c_generic, ela_external, ela_hyperlink, webmention_rt > mf_webmention;
typedef microformat < rel, r_widget, c_generic, ela_external, ela_external, widget_rt > mf_widget;
typedef microformat < rel, r_wlwmanifest, c_generic, ela_external, ela_no, wlwmanifest_rt > mf_wlwmanifest;
typedef microformat < rel, r_working_copy, c_generic, ela_ok, ela_ok, working_copy_rt > mf_working_copy;
typedef microformat < rel, r_working_copy_of, c_generic, ela_ok, ela_ok, working_copy_of_rt > mf_working_copy_of;
typedef microformat < rel, r_yandex_tableau_widget, c_generic, ela_external, ela_no, yandex_tableau_widget_rt > mf_yandex_tableau_widget;
typedef microformat < html_class, c_error, c_rejected, ela_ok, ela_ok, name_at > mf_error;


typedef ::std::shared_ptr < mf_about > about_ptr;
typedef ::std::shared_ptr < mf_accessibility > accessibility_ptr;
typedef ::std::shared_ptr < mf_acquaintance > acquaintance_ptr;
typedef ::std::shared_ptr < mf_adr > adr_ptr;
typedef ::std::shared_ptr < mf_adr_v1 > adr_v1_ptr;
typedef ::std::shared_ptr < mf_aggregate > aggregate_ptr;
typedef ::std::shared_ptr < mf_aggregate_v1 > aggregate_v1_ptr;
typedef ::std::shared_ptr < mf_alternative > alternative_ptr;
typedef ::std::shared_ptr < mf_amphtml > amphtml_ptr;
typedef ::std::shared_ptr < mf_appendix > appendix_ptr;
typedef ::std::shared_ptr < mf_apple_touch_icon > apple_touch_icon_ptr;
typedef ::std::shared_ptr < mf_apple_touch_icon_precomposed > apple_touch_icon_precomposed_ptr;
typedef ::std::shared_ptr < mf_apple_touch_startup_image > apple_touch_startup_image_ptr;
typedef ::std::shared_ptr < mf_archived > archived_ptr;
typedef ::std::shared_ptr < mf_archives > archives_ptr;
typedef ::std::shared_ptr < mf_atom_v1 > atom_v1_ptr;
typedef ::std::shared_ptr < mf_attachment > attachment_ptr;
typedef ::std::shared_ptr < mf_audio_v1 > audio_v1_ptr;
typedef ::std::shared_ptr < mf_author > author_ptr;
typedef ::std::shared_ptr < mf_authorisation_endpoint > authorisation_endpoint_ptr;
typedef ::std::shared_ptr < mf_banner > banner_ptr;
typedef ::std::shared_ptr < mf_begin > begin_ptr;
typedef ::std::shared_ptr < mf_biblioentry > biblioentry_ptr;
typedef ::std::shared_ptr < mf_bibliography > bibliography_ptr;
typedef ::std::shared_ptr < mf_bibliography > bibliography_ptr;
typedef ::std::shared_ptr < mf_blocked_by > blocked_by_ptr;
typedef ::std::shared_ptr < mf_bookmark > bookmark_ptr;
typedef ::std::shared_ptr < mf_breadcrumb > breadcrumb_ptr;
typedef ::std::shared_ptr < mf_canonical > canonical_ptr;
typedef ::std::shared_ptr < mf_card > card_ptr;
typedef ::std::shared_ptr < mf_calendar_v1 > calendar_v1_ptr;
typedef ::std::shared_ptr < mf_card_v1 > card_v1_ptr;
typedef ::std::shared_ptr < mf_category > category_ptr;

typedef ::std::shared_ptr < mf_cc_permits > cc_permits_ptr;
typedef ::std::shared_ptr < mf_cc_requires > cc_requires_ptr;
typedef ::std::shared_ptr < mf_cc_prohibits > cc_prohibits_ptr;
typedef ::std::shared_ptr < mf_cc_jurisdiction > cc_jurisdiction_ptr;
typedef ::std::shared_ptr < mf_cc_legalcode > cc_legalcode_ptr;
typedef ::std::shared_ptr < mf_cc_deprecatedon > cc_deprecatedon_ptr;
typedef ::std::shared_ptr < mf_cc_licence > cc_licence_ptr;
typedef ::std::shared_ptr < mf_cc_morepermissions > cc_morepermissions_ptr;
// typedef ::std::shared_ptr < mf_cc_attributionname > cc_attributionname_ptr;
typedef ::std::shared_ptr < mf_cc_attributionurl > cc_attributionurl_ptr;
typedef ::std::shared_ptr < mf_cc_useguidelines > cc_useguidelines_ptr;

typedef ::std::shared_ptr < mf_chapter > chapter_ptr;
typedef ::std::shared_ptr < mf_child > child_ptr;
typedef ::std::shared_ptr < mf_chrome_webstore_item > chrome_webstore_item_ptr;
typedef ::std::shared_ptr < mf_citation > citation_ptr;
typedef ::std::shared_ptr < mf_cite_as > cite_as_ptr;
typedef ::std::shared_ptr < mf_code_licence > code_licence_ptr;
typedef ::std::shared_ptr < mf_code_repository > code_repository_ptr;
typedef ::std::shared_ptr < mf_colleague > colleague_ptr;
typedef ::std::shared_ptr < mf_collection > collection_ptr;
typedef ::std::shared_ptr < mf_comment > comment_ptr;
typedef ::std::shared_ptr < mf_component > component_ptr;
typedef ::std::shared_ptr < mf_contact > contact_ptr;
typedef ::std::shared_ptr < mf_content_licence > content_licence_ptr;
typedef ::std::shared_ptr < mf_content_repository > content_repository_ptr;
typedef ::std::shared_ptr < mf_contents > contents_ptr;
typedef ::std::shared_ptr < mf_contribution > contribution_ptr;
typedef ::std::shared_ptr < mf_convertedfrom > convertedfrom_ptr;
typedef ::std::shared_ptr < mf_copyright > copyright_ptr;
typedef ::std::shared_ptr < mf_coresident > coresident_ptr;
typedef ::std::shared_ptr < mf_coworker > coworker_ptr;
typedef ::std::shared_ptr < mf_create_form > create_form_ptr;
typedef ::std::shared_ptr < mf_crush > crush_ptr;
typedef ::std::shared_ptr < mf_current > current_ptr;
typedef ::std::shared_ptr < mf_date > date_ptr;
typedef ::std::shared_ptr < mf_dcterms_conformsto > dcterms_conformsto_ptr;
typedef ::std::shared_ptr < mf_dcterms_contributor > dcterms_contributor_ptr;
typedef ::std::shared_ptr < mf_dcterms_creator > dcterms_creator_ptr;
typedef ::std::shared_ptr < mf_dcterms_description > dcterms_description_ptr;
typedef ::std::shared_ptr < mf_dcterms_hasformat > dcterms_hasformat_ptr;
typedef ::std::shared_ptr < mf_dcterms_haspart > dcterms_haspart_ptr;
typedef ::std::shared_ptr < mf_dcterms_hasversion > dcterms_hasversion_ptr;
typedef ::std::shared_ptr < mf_dcterms_isformatof > dcterms_isformatof_ptr;
typedef ::std::shared_ptr < mf_dcterms_ispartof > dcterms_ispartof_ptr;
typedef ::std::shared_ptr < mf_dcterms_isreferencedby > dcterms_isreferencedby_ptr;
typedef ::std::shared_ptr < mf_dcterms_isreplacedby > dcterms_isreplacedby_ptr;
typedef ::std::shared_ptr < mf_dcterms_isrequiredby > dcterms_isrequiredby_ptr;
typedef ::std::shared_ptr < mf_dcterms_isversionof > dcterms_isversionof_ptr;
typedef ::std::shared_ptr < mf_dcterms_licence > dcterms_licence_ptr;
typedef ::std::shared_ptr < mf_dcterms_mediator > dcterms_mediator_ptr;
typedef ::std::shared_ptr < mf_dcterms_publisher > dcterms_publisher_ptr;
typedef ::std::shared_ptr < mf_dcterms_references > dcterms_references_ptr;
typedef ::std::shared_ptr < mf_dcterms_relation > dcterms_relation_ptr;
typedef ::std::shared_ptr < mf_dcterms_replaces > dcterms_replaces_ptr;
typedef ::std::shared_ptr < mf_dcterms_requires > dcterms_requires_ptr;
typedef ::std::shared_ptr < mf_dcterms_rightsholder > dcterms_rightsholder_ptr;
typedef ::std::shared_ptr < mf_dcterms_source > dcterms_source_ptr;
typedef ::std::shared_ptr < mf_dcterms_subject > dcterms_subject_ptr;
typedef ::std::shared_ptr < mf_definition > definition_ptr;
typedef ::std::shared_ptr < mf_describedby > describedby_ptr;
typedef ::std::shared_ptr < mf_describes > describes_ptr;
typedef ::std::shared_ptr < mf_directory > directory_ptr;
typedef ::std::shared_ptr < mf_disclaimer > disclaimer_ptr;
typedef ::std::shared_ptr < mf_disclosure > disclosure_ptr;
typedef ::std::shared_ptr < mf_discussion > discussion_ptr;
typedef ::std::shared_ptr < mf_dnsprefetch > dnsprefetch_ptr;
typedef ::std::shared_ptr < mf_docs_oasis_open_org_ns_cmis_link_200908_acl > docs_oasis_open_org_ns_cmis_link_200908_acl_ptr;
typedef ::std::shared_ptr < mf_duplicate > duplicate_ptr;
typedef ::std::shared_ptr < mf_edit > edit_ptr;
typedef ::std::shared_ptr < mf_edit_form > edit_form_ptr;
typedef ::std::shared_ptr < mf_edit_media > edit_media_ptr;
typedef ::std::shared_ptr < mf_editor > editor_ptr;
typedef ::std::shared_ptr < mf_edituri > edituri_ptr;
typedef ::std::shared_ptr < mf_enclosure > enclosure_ptr;
typedef ::std::shared_ptr < mf_end > end_ptr;
typedef ::std::shared_ptr < mf_endorsed > endorsed_ptr;
typedef ::std::shared_ptr < mf_entry > entry_ptr;
typedef ::std::shared_ptr < mf_entry_content > entry_content_ptr;
typedef ::std::shared_ptr < mf_event > event_ptr;
typedef ::std::shared_ptr < mf_external > external_ptr;
typedef ::std::shared_ptr < mf_fan > fan_ptr;
typedef ::std::shared_ptr < mf_feed > feed_ptr;
typedef ::std::shared_ptr < mf_first > first_ptr;
typedef ::std::shared_ptr < mf_footnote > footnote_ptr;
typedef ::std::shared_ptr < mf_friend > friend_ptr;
typedef ::std::shared_ptr < mf_gbfs > gbfs_ptr;
typedef ::std::shared_ptr < mf_gtfs_realtime > gtfs_realtime_ptr;
typedef ::std::shared_ptr < mf_gtfs_static > gtfs_static_ptr;
typedef ::std::shared_ptr < mf_geo > geo_ptr;
typedef ::std::shared_ptr < mf_geo_v1 > geo_v1_ptr;
typedef ::std::shared_ptr < mf_glossary > glossary_ptr;
typedef ::std::shared_ptr < mf_group > group_ptr;
typedef ::std::shared_ptr < mf_hcite > hcite_ptr;
typedef ::std::shared_ptr < mf_help > help_ptr;
typedef ::std::shared_ptr < mf_home > home_ptr;
typedef ::std::shared_ptr < mf_hosts > hosts_ptr;
typedef ::std::shared_ptr < mf_hub > hub_ptr;
typedef ::std::shared_ptr < mf_icon > icon_ptr;
typedef ::std::shared_ptr < mf_image_src > image_src_ptr;
typedef ::std::shared_ptr < mf_import > import_ptr;
typedef ::std::shared_ptr < mf_in_reply_to > in_reply_to_ptr;
typedef ::std::shared_ptr < mf_index > index_ptr;
typedef ::std::shared_ptr < mf_intervalafter > intervalafter_ptr;
typedef ::std::shared_ptr < mf_intervalbefore > intervalbefore_ptr;
typedef ::std::shared_ptr < mf_intervalcontains > intervalcontains_ptr;
typedef ::std::shared_ptr < mf_intervaldisjoint > intervaldisjoint_ptr;
typedef ::std::shared_ptr < mf_intervalduring > intervalduring_ptr;
typedef ::std::shared_ptr < mf_intervalequals > intervalequals_ptr;
typedef ::std::shared_ptr < mf_intervalfinishedby > intervalfinishedby_ptr;
typedef ::std::shared_ptr < mf_intervalfinishes > intervalfinishes_ptr;
typedef ::std::shared_ptr < mf_intervalin > intervalin_ptr;
typedef ::std::shared_ptr < mf_intervalmeets > intervalmeets_ptr;
typedef ::std::shared_ptr < mf_intervalmetby > intervalmetby_ptr;
typedef ::std::shared_ptr < mf_intervaloverlappedby > intervaloverlappedby_ptr;
typedef ::std::shared_ptr < mf_intervaloverlaps > intervaloverlaps_ptr;
typedef ::std::shared_ptr < mf_intervalstartedby > intervalstartedby_ptr;
typedef ::std::shared_ptr < mf_intervalstarts > intervalstarts_ptr;
typedef ::std::shared_ptr < mf_issues > issues_ptr;
typedef ::std::shared_ptr < mf_item > item_ptr;
typedef ::std::shared_ptr < mf_item_licence > item_licence_ptr;
typedef ::std::shared_ptr < mf_its_rules > its_rules_ptr;
typedef ::std::shared_ptr < mf_jslicence > jslicence_ptr;
typedef ::std::shared_ptr < mf_kin > kin_ptr;
typedef ::std::shared_ptr < mf_kinetic_stylesheet > kinetic_stylesheet_ptr;
typedef ::std::shared_ptr < mf_last > last_ptr;
typedef ::std::shared_ptr < mf_latest_version > latest_version_ptr;
typedef ::std::shared_ptr < mf_licence > licence_ptr;
typedef ::std::shared_ptr < mf_lightbox > lightbox_ptr;
typedef ::std::shared_ptr < mf_lightvideo > lightvideo_ptr;
typedef ::std::shared_ptr < mf_listing > listing_ptr;
typedef ::std::shared_ptr < mf_listing_v1 > listing_v1_ptr;
typedef ::std::shared_ptr < mf_logo > logo_ptr;
typedef ::std::shared_ptr < mf_longdesc > longdesc_ptr;
typedef ::std::shared_ptr < mf_lrdd > lrdd_ptr;
typedef ::std::shared_ptr < mf_m_pagescroll2id > m_pagescroll2id_ptr;
typedef ::std::shared_ptr < mf_made > made_ptr;
typedef ::std::shared_ptr < mf_manifest > manifest_ptr;
typedef ::std::shared_ptr < mf_map > map_ptr;
typedef ::std::shared_ptr < mf_maskicon > maskicon_ptr;
typedef ::std::shared_ptr < mf_me > me_ptr;
typedef ::std::shared_ptr < mf_media_v1 > media_v1_ptr;
typedef ::std::shared_ptr < mf_member > member_ptr;
typedef ::std::shared_ptr < mf_memento > memento_ptr;
typedef ::std::shared_ptr < mf_met > met_ptr;
typedef ::std::shared_ptr < mf_meta > meta_ptr;
typedef ::std::shared_ptr < mf_micropub > micropub_ptr;
typedef ::std::shared_ptr < mf_microsummary > microsummary_ptr;
typedef ::std::shared_ptr < mf_monitor > monitor_ptr;
typedef ::std::shared_ptr < mf_monitor_group > monitor_group_ptr;
typedef ::std::shared_ptr < mf_muse > muse_ptr;
typedef ::std::shared_ptr < mf_navigate > navigate_ptr;
typedef ::std::shared_ptr < mf_neighbour > neighbour_ptr;
typedef ::std::shared_ptr < mf_news_v1 > news_v1_ptr;
typedef ::std::shared_ptr < mf_next > next_ptr;
typedef ::std::shared_ptr < mf_next_archive > next_archive_ptr;
typedef ::std::shared_ptr < mf_nofollow > nofollow_ptr;
typedef ::std::shared_ptr < mf_noopener > noopener_ptr;
typedef ::std::shared_ptr < mf_noreferrer > noreferrer_ptr;
typedef ::std::shared_ptr < mf_openid2_local_id > openid2_local_id_ptr;
typedef ::std::shared_ptr < mf_openid2_provider > openid2_provider_ptr;
typedef ::std::shared_ptr < mf_openid_delegate > openid_delegate_ptr;
typedef ::std::shared_ptr < mf_openid_server > openid_server_ptr;
typedef ::std::shared_ptr < mf_origin > origin_ptr;
typedef ::std::shared_ptr < mf_original > original_ptr;
typedef ::std::shared_ptr < mf_p3pv1 > p3pv1_ptr;
typedef ::std::shared_ptr < mf_parent > parent_ptr;
typedef ::std::shared_ptr < mf_pavatar > pavatar_ptr;
typedef ::std::shared_ptr < mf_payment > payment_ptr;
typedef ::std::shared_ptr < mf_permalink > permalink_ptr;
typedef ::std::shared_ptr < mf_pgpkey > pgpkey_ptr;
typedef ::std::shared_ptr < mf_pingback > pingback_ptr;
typedef ::std::shared_ptr < mf_pointer > pointer_ptr;
typedef ::std::shared_ptr < mf_popover > popover_ptr;
typedef ::std::shared_ptr < mf_preconnect > preconnect_ptr;
typedef ::std::shared_ptr < mf_predecessor_version > predecessor_version_ptr;
typedef ::std::shared_ptr < mf_prefetch > prefetch_ptr;
typedef ::std::shared_ptr < mf_preload > preload_ptr;
typedef ::std::shared_ptr < mf_prerender > prerender_ptr;
typedef ::std::shared_ptr < mf_prev > prev_ptr;
typedef ::std::shared_ptr < mf_prev_archive > prev_archive_ptr;
typedef ::std::shared_ptr < mf_preview > preview_ptr;
typedef ::std::shared_ptr < mf_principles > principles_ptr;
typedef ::std::shared_ptr < mf_privacy > privacy_ptr;
typedef ::std::shared_ptr < mf_privacy_policy > privacy_policy_ptr;
typedef ::std::shared_ptr < mf_product > product_ptr;
typedef ::std::shared_ptr < mf_product_v1 > product_v1_ptr;
typedef ::std::shared_ptr < mf_profile > profile_ptr;
typedef ::std::shared_ptr < mf_pronunciation > pronunciation_ptr;
typedef ::std::shared_ptr < mf_publickey > publickey_ptr;
typedef ::std::shared_ptr < mf_publisher > publisher_ptr;
typedef ::std::shared_ptr < mf_radioepg > radioepg_ptr;
typedef ::std::shared_ptr < mf_recipe > recipe_ptr;
typedef ::std::shared_ptr < mf_recipe_v1 > recipe_v1_ptr;
typedef ::std::shared_ptr < mf_referral > referral_ptr;
typedef ::std::shared_ptr < mf_related > related_ptr;
typedef ::std::shared_ptr < mf_relcite > relcite_ptr;
typedef ::std::shared_ptr < mf_relfeed > relfeed_ptr;
typedef ::std::shared_ptr < mf_relitem > relitem_ptr;
typedef ::std::shared_ptr < mf_rendition > rendition_ptr;
typedef ::std::shared_ptr < mf_replies > replies_ptr;
typedef ::std::shared_ptr < mf_reply_to > reply_to_ptr;
typedef ::std::shared_ptr < mf_resource > resource_ptr;
typedef ::std::shared_ptr < mf_respond_proxy > respond_proxy_ptr;
typedef ::std::shared_ptr < mf_respond_redirect > respond_redirect_ptr;
typedef ::std::shared_ptr < mf_restconf > restconf_ptr;
typedef ::std::shared_ptr < mf_resume > resume_ptr;
typedef ::std::shared_ptr < mf_resume_v1 > resume_v1_ptr;
typedef ::std::shared_ptr < mf_review > review_ptr;
typedef ::std::shared_ptr < mf_review_v1 > review_v1_ptr;
typedef ::std::shared_ptr < mf_root > root_ptr;
typedef ::std::shared_ptr < mf_rtitem > rtitem_ptr;
typedef ::std::shared_ptr < mf_ontology_dc > ontology_dc_ptr;
typedef ::std::shared_ptr < mf_ontology_dcterms > ontology_dcterms_ptr;
typedef ::std::shared_ptr < mf_search > search_ptr;
typedef ::std::shared_ptr < mf_section > section_ptr;
typedef ::std::shared_ptr < mf_self > self_ptr;
typedef ::std::shared_ptr < mf_service > service_ptr;
typedef ::std::shared_ptr < mf_service_desc > service_desc_ptr;
typedef ::std::shared_ptr < mf_service_doc > service_doc_ptr;
typedef ::std::shared_ptr < mf_service_meta > service_meta_ptr;
typedef ::std::shared_ptr < mf_shortlink > shortlink_ptr;
typedef ::std::shared_ptr < mf_sibling > sibling_ptr;
typedef ::std::shared_ptr < mf_sidebar > sidebar_ptr;
typedef ::std::shared_ptr < mf_sitemap > sitemap_ptr;
typedef ::std::shared_ptr < mf_source > source_ptr;
typedef ::std::shared_ptr < mf_sponsor > sponsor_ptr;
typedef ::std::shared_ptr < mf_spouse > spouse_ptr;
typedef ::std::shared_ptr < mf_start > start_ptr;
typedef ::std::shared_ptr < mf_status > status_ptr;
typedef ::std::shared_ptr < mf_stylesheet > stylesheet_ptr;
typedef ::std::shared_ptr < mf_stylesheetless > stylesheetless_ptr;
typedef ::std::shared_ptr < mf_subresource > subresource_ptr;
typedef ::std::shared_ptr < mf_subsection > subsection_ptr;
typedef ::std::shared_ptr < mf_successor_version > successor_version_ptr;
typedef ::std::shared_ptr < mf_sunset > sunset_ptr;
typedef ::std::shared_ptr < mf_supercedes > supercedes_ptr;
typedef ::std::shared_ptr < mf_sweetheart > sweetheart_ptr;
typedef ::std::shared_ptr < mf_sword > sword_ptr;
typedef ::std::shared_ptr < mf_syndication > syndication_ptr;
typedef ::std::shared_ptr < mf_tag > tag_ptr;
typedef ::std::shared_ptr < mf_terms_of_service > terms_of_service_ptr;
typedef ::std::shared_ptr < mf_timegate > timegate_ptr;
typedef ::std::shared_ptr < mf_timemap > timemap_ptr;
typedef ::std::shared_ptr < mf_timesheet > timesheet_ptr;
typedef ::std::shared_ptr < mf_toc > toc_ptr;
typedef ::std::shared_ptr < mf_token_endpoint > token_endpoint_ptr;
typedef ::std::shared_ptr < mf_tooltip > tooltip_ptr;
typedef ::std::shared_ptr < mf_top > top_ptr;
typedef ::std::shared_ptr < mf_trackback > trackback_ptr;
typedef ::std::shared_ptr < mf_trademark > trademark_ptr;
typedef ::std::shared_ptr < mf_transformation > transformation_ptr;
typedef ::std::shared_ptr < mf_translation > translation_ptr;
typedef ::std::shared_ptr < mf_type > type_ptr;
typedef ::std::shared_ptr < mf_unendorsed > unendorsed_ptr;
typedef ::std::shared_ptr < mf_unknown > unknown_ptr;
typedef ::std::shared_ptr < mf_up > up_ptr;
typedef ::std::shared_ptr < mf_urc > urc_ptr;
typedef ::std::shared_ptr < mf_user > user_ptr;
typedef ::std::shared_ptr < mf_vcalendar_child > vcalendar_child_ptr;
typedef ::std::shared_ptr < mf_vcalendar_parent > vcalendar_parent_ptr;
typedef ::std::shared_ptr < mf_vcalendar_sibling > vcalendar_sibling_ptr;
typedef ::std::shared_ptr < mf_vcs_git > vcs_git_ptr;
typedef ::std::shared_ptr < mf_vcs_svn > vcs_svn_ptr;
typedef ::std::shared_ptr < mf_version_history > version_history_ptr;
typedef ::std::shared_ptr < mf_via > via_ptr;
typedef ::std::shared_ptr < mf_w_api_org > w_api_org_ptr;
typedef ::std::shared_ptr < mf_webmention > webmention_ptr;
typedef ::std::shared_ptr < mf_widget > widget_ptr;
typedef ::std::shared_ptr < mf_wlwmanifest > wlwmanifest_ptr;
typedef ::std::shared_ptr < mf_working_copy > working_copy_ptr;
typedef ::std::shared_ptr < mf_working_copy_of > working_copy_of_ptr;
typedef ::std::shared_ptr < mf_yandex_tableau_widget > yandex_tableau_widget_ptr;
typedef ::std::shared_ptr < mf_error > error_ptr;

#define MICROFORMATS \
    mf_unknown, \
    mf_aggregate_v1, mf_atom_v1, mf_audio_v1, mf_calendar_v1, mf_card_v1, mf_listing_v1, mf_media_v1, mf_product_v1, mf_recipe_v1, mf_resume_v1, \
    mf_review_v1, mf_adr_v1, mf_geo_v1, mf_news_v1, \
    mf_adr, mf_breadcrumb, mf_card, mf_hcite, mf_entry, mf_event, mf_feed, mf_geo, mf_item, mf_listing, mf_product, mf_recipe, mf_resume, mf_review, \
    mf_aggregate, \
    mf_acquaintance, mf_alternative, mf_appendix, mf_author, mf_bibliography, mf_bookmark, mf_canonical, \
    mf_chapter, mf_child, mf_relcite, mf_colleague, mf_code_licence, mf_content_licence, mf_contact, mf_contents, \
    mf_copyright, mf_coresident, mf_coworker, mf_crush, mf_date, mf_directory, mf_discussion, mf_dnsprefetch, \
    mf_enclosure, mf_external, mf_friend, mf_glossary, mf_group, mf_help, mf_home, mf_icon, mf_in_reply_to, mf_index, mf_issues, mf_its_rules, \
    mf_kin, mf_licence, mf_map, mf_me, mf_member, mf_met, mf_micropub, mf_muse, mf_neighbour, mf_next, mf_nofollow, \
    mf_noopener, mf_noreferrer, mf_parent, mf_payment, mf_pingback, mf_preconnect, mf_prefetch, mf_preload, \
    mf_prerender, mf_prev, mf_preview, mf_pronunciation, mf_search, mf_section, mf_sibling, mf_sidebar, mf_spouse, mf_start, mf_stylesheet, \
    mf_subsection, mf_supercedes, mf_sweetheart, mf_tag, mf_toc, mf_top, mf_transformation, mf_vcs_git, mf_vcs_svn, mf_webmention, \
    mf_banner, mf_begin, mf_biblioentry, mf_citation, mf_definition, mf_disclaimer, \
    mf_editor, mf_end, mf_navigate, mf_origin, mf_pointer, mf_trademark, mf_translation, mf_urc, \
    mf_about, mf_archives, mf_blocked_by, mf_cite_as, mf_collection, mf_convertedfrom, \
    mf_create_form, mf_current, mf_describedby, mf_describes, mf_duplicate, mf_edit, mf_edit_form, \
    mf_edit_media, mf_first, mf_hosts, mf_hub, mf_intervalafter, mf_intervalbefore, mf_intervalcontains, \
    mf_intervaldisjoint, mf_intervalduring, mf_intervalequals, mf_intervalfinishedby, mf_intervalfinishes, \
    mf_intervalin, mf_intervalmeets, mf_intervalmetby, mf_intervaloverlappedby, mf_intervaloverlaps, \
    mf_intervalstartedby, mf_intervalstarts, mf_relitem, mf_last, mf_latest_version, mf_lrdd, mf_memento, \
    mf_monitor, mf_monitor_group, mf_next_archive, mf_original, mf_predecessor_version, \
    mf_prev_archive, mf_privacy_policy, mf_profile, mf_related, mf_restconf, mf_replies, mf_self, mf_service, \
    mf_service_desc, mf_service_doc, mf_service_meta, mf_status, mf_successor_version, mf_sunset, \
    mf_terms_of_service, mf_timegate, mf_timemap, mf_type, mf_up, mf_version_history, mf_via, mf_working_copy, \
    mf_working_copy_of, \
    mf_amphtml, mf_apple_touch_icon, mf_apple_touch_icon_precomposed, mf_apple_touch_startup_image, mf_archived, \
    mf_attachment, mf_authorisation_endpoint, mf_category, mf_code_repository, mf_component, mf_chrome_webstore_item, \
    mf_content_repository, mf_dcterms_conformsto, mf_dcterms_contributor, mf_dcterms_creator, mf_dcterms_description, \
    mf_dcterms_hasformat, mf_dcterms_haspart, mf_dcterms_hasversion, mf_dcterms_isformatof, mf_dcterms_ispartof, \
    mf_dcterms_isreferencedby, mf_dcterms_isreplacedby, mf_dcterms_isrequiredby, mf_dcterms_isversionof, mf_dcterms_licence, \
    mf_dcterms_mediator, mf_dcterms_publisher, mf_dcterms_references, mf_dcterms_relation, mf_dcterms_replaces, \
    mf_dcterms_requires, mf_dcterms_rightsholder, mf_dcterms_source, mf_dcterms_subject, mf_disclosure, \
    mf_edituri, mf_entry_content, mf_gbfs, mf_gtfs_static, mf_gtfs_realtime, mf_image_src, mf_import, mf_jslicence, \
    mf_lightbox, mf_lightvideo, mf_manifest, mf_maskicon, mf_meta, mf_openid_delegate, mf_openid_server, \
    mf_openid2_local_id, mf_openid2_provider, mf_p3pv1, mf_pgpkey, mf_publisher, mf_radioepg, mf_rendition, \
    mf_root, mf_reply_to, mf_ontology_dcterms, mf_shortlink, mf_sitemap, mf_subresource, mf_sword, mf_syndication, \
    mf_timesheet, mf_token_endpoint, mf_widget, mf_wlwmanifest, mf_yandex_tableau_widget, \
    mf_docs_oasis_open_org_ns_cmis_link_200908_acl, \
    mf_accessibility, mf_longdesc, mf_m_pagescroll2id, mf_source, mf_vcalendar_parent, mf_vcalendar_child, \
    mf_vcalendar_sibling, mf_w_api_org, \
    mf_comment, mf_contribution, mf_endorsed, mf_fan, mf_relfeed, mf_footnote, mf_kinetic_stylesheet, mf_made, \
    mf_microsummary, mf_permalink, mf_popover, mf_privacy, mf_publickey, mf_referral, mf_respond_proxy, \
    mf_respond_redirect, mf_resource, mf_sponsor, mf_tooltip, mf_trackback, mf_unendorsed, mf_user, \
    mf_ontology_dc, mf_stylesheetless, mf_logo, mf_pavatar, \
    mf_cc_permits, mf_cc_requires, mf_cc_prohibits, mf_cc_jurisdiction, mf_cc_legalcode, mf_cc_deprecatedon, \
    mf_cc_licence, mf_cc_morepermissions, /* mf_cc_attributionname, */ mf_cc_attributionurl, mf_cc_useguidelines, \
    mf_error

#define MICROFORMAT_PTRS \
    unknown_ptr, \
    aggregate_v1_ptr, atom_v1_ptr, audio_v1_ptr, calendar_v1_ptr, card_v1_ptr, listing_v1_ptr, media_v1_ptr, product_v1_ptr, recipe_v1_ptr, \
    resume_v1_ptr, review_v1_ptr, adr_v1_ptr, geo_v1_ptr, news_v1_ptr, \
    adr_ptr, breadcrumb_ptr, card_ptr, hcite_ptr, entry_ptr, event_ptr, feed_ptr, geo_ptr, item_ptr, listing_ptr, product_ptr, recipe_ptr, resume_ptr, review_ptr, \
    aggregate_ptr, \
    acquaintance_ptr, alternative_ptr, appendix_ptr, author_ptr, bibliography_ptr, bookmark_ptr, canonical_ptr, \
    chapter_ptr, child_ptr, relcite_ptr, colleague_ptr, code_licence_ptr, content_licence_ptr, contact_ptr, contents_ptr, \
    copyright_ptr, coresident_ptr, coworker_ptr, crush_ptr, date_ptr, directory_ptr, discussion_ptr, dnsprefetch_ptr, \
    enclosure_ptr, external_ptr, friend_ptr, glossary_ptr, group_ptr, help_ptr, home_ptr, icon_ptr, in_reply_to_ptr, index_ptr, issues_ptr, its_rules_ptr, \
    kin_ptr, licence_ptr, map_ptr, me_ptr, member_ptr, met_ptr, micropub_ptr, muse_ptr, neighbour_ptr, next_ptr, nofollow_ptr, \
    noopener_ptr, noreferrer_ptr, parent_ptr, payment_ptr, pingback_ptr, preconnect_ptr, prefetch_ptr, preload_ptr, \
    prerender_ptr, prev_ptr, preview_ptr, pronunciation_ptr, search_ptr, section_ptr, sibling_ptr, sidebar_ptr, spouse_ptr, start_ptr, stylesheet_ptr, \
    subsection_ptr, supercedes_ptr, sweetheart_ptr, tag_ptr, toc_ptr, top_ptr, transformation_ptr, vcs_git_ptr, vcs_svn_ptr, webmention_ptr, \
    banner_ptr, begin_ptr, biblioentry_ptr, citation_ptr, definition_ptr, disclaimer_ptr, \
    editor_ptr, end_ptr, navigate_ptr, origin_ptr, pointer_ptr, trademark_ptr, translation_ptr, urc_ptr, \
    about_ptr, archives_ptr, blocked_by_ptr, cite_as_ptr, collection_ptr, convertedfrom_ptr, \
    create_form_ptr, current_ptr, describedby_ptr, describes_ptr, duplicate_ptr, edit_ptr, edit_form_ptr, \
    edit_media_ptr, first_ptr, hosts_ptr, hub_ptr, intervalafter_ptr, intervalbefore_ptr, intervalcontains_ptr, \
    intervaldisjoint_ptr, intervalduring_ptr, intervalequals_ptr, intervalfinishedby_ptr, intervalfinishes_ptr, \
    intervalin_ptr, intervalmeets_ptr, intervalmetby_ptr, intervaloverlappedby_ptr, intervaloverlaps_ptr, \
    intervalstartedby_ptr, intervalstarts_ptr, relitem_ptr, last_ptr, latest_version_ptr, lrdd_ptr, memento_ptr, \
    monitor_ptr, monitor_group_ptr, next_archive_ptr, original_ptr, predecessor_version_ptr, \
    prev_archive_ptr, privacy_policy_ptr, profile_ptr, related_ptr, restconf_ptr, replies_ptr, self_ptr, service_ptr, \
    service_desc_ptr, service_doc_ptr, service_meta_ptr, status_ptr, successor_version_ptr, sunset_ptr, \
    terms_of_service_ptr, timegate_ptr, timemap_ptr, type_ptr, up_ptr, version_history_ptr, via_ptr, working_copy_ptr, \
    working_copy_of_ptr, \
    amphtml_ptr, apple_touch_icon_ptr, apple_touch_icon_precomposed_ptr, apple_touch_startup_image_ptr, archived_ptr, \
    attachment_ptr, authorisation_endpoint_ptr, category_ptr, code_repository_ptr, component_ptr, chrome_webstore_item_ptr, \
    content_repository_ptr, dcterms_conformsto_ptr, dcterms_contributor_ptr, dcterms_creator_ptr, dcterms_description_ptr, \
    dcterms_hasformat_ptr, dcterms_haspart_ptr, dcterms_hasversion_ptr, dcterms_isformatof_ptr, dcterms_ispartof_ptr, \
    dcterms_isreferencedby_ptr, dcterms_isreplacedby_ptr, dcterms_isrequiredby_ptr, dcterms_isversionof_ptr, dcterms_licence_ptr, \
    dcterms_mediator_ptr, dcterms_publisher_ptr, dcterms_references_ptr, dcterms_relation_ptr, dcterms_replaces_ptr, \
    dcterms_requires_ptr, dcterms_rightsholder_ptr, dcterms_source_ptr, dcterms_subject_ptr, disclosure_ptr, \
    edituri_ptr, entry_content_ptr, gbfs_ptr, gtfs_static_ptr, gtfs_realtime_ptr, image_src_ptr, import_ptr, jslicence_ptr, \
    lightbox_ptr, lightvideo_ptr, manifest_ptr, maskicon_ptr, meta_ptr, openid_delegate_ptr, openid_server_ptr, \
    openid2_local_id_ptr, openid2_provider_ptr, p3pv1_ptr, pgpkey_ptr, publisher_ptr, radioepg_ptr, rendition_ptr, \
    root_ptr, reply_to_ptr, ontology_dcterms_ptr, shortlink_ptr, sitemap_ptr, subresource_ptr, sword_ptr, syndication_ptr, \
    timesheet_ptr, token_endpoint_ptr, widget_ptr, wlwmanifest_ptr, yandex_tableau_widget_ptr, \
    docs_oasis_open_org_ns_cmis_link_200908_acl_ptr, \
    accessibility_ptr, longdesc_ptr, m_pagescroll2id_ptr, source_ptr, vcalendar_parent_ptr, vcalendar_child_ptr, \
    vcalendar_sibling_ptr, w_api_org_ptr, \
    comment_ptr, contribution_ptr, endorsed_ptr, fan_ptr, relfeed_ptr, footnote_ptr, kinetic_stylesheet_ptr, made_ptr, \
    microsummary_ptr, permalink_ptr, popover_ptr, privacy_ptr, publickey_ptr, referral_ptr, respond_proxy_ptr, \
    respond_redirect_ptr, resource_ptr, sponsor_ptr, tooltip_ptr, trackback_ptr, unendorsed_ptr, user_ptr, \
    ontology_dc_ptr, stylesheetless_ptr, logo_ptr, pavatar_ptr, \
    cc_permits_ptr, cc_requires_ptr, cc_prohibits_ptr, cc_jurisdiction_ptr, cc_legalcode_ptr, cc_deprecatedon_ptr, \
    cc_licence_ptr, cc_morepermissions_ptr, /* cc_attributionname_ptr, */ cc_attributionurl_ptr, cc_useguidelines_ptr, \
    error_ptr
