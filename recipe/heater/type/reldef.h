/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

// NOTE: if x appears in source A and source B, it'll be declared in the first, only.
// also note all ids specified in lower case, because in fact they're case independent, but this code compares in lower case

// HTML x: https://www.w3.org/Architecture/NOTE-link.html

// HTML5: https://dev.w3.org/html5/spec-LC/links.html#linkTypes
#define R_ALTERNATIVE "alternate"
#define R_AUTHOR "author"
#define R_BOOKMARK "bookmark"
#define R_EXTERNAL "external"
#define R_HELP "help"
#define R_ICON "icon"
#define R_LICENCE "license"
#define R_NEXT "next"
#define R_NOFOLLOW "nofollow"
#define R_NOREFERRER "noreferrer"
#define R_PINGBACK "pingback"
#define R_PREFETCH "prefetch"
#define R_PREV "prev"
#define R_SEARCH "search"
#define R_SIDEBAR "sidebar"
#define R_STYLESHEET "stylesheet"
#define R_TAG "tag"

// HTML4  https://www.w3.org/TR/REC-html40/types.html#type-links and http://microformats.org/wiki/existing-rel-values
#define R_APPENDIX "appendix"
#define R_BEGIN "begin"
#define R_BIBLIOENTRY "biblioentry"
#define R_BIBLIOGRAPHY "bibliography"
#define R_CHAPTER "chapter"
#define R_CHILD "child"
#define R_CITATION "citation"
#define R_COLLECTION "collection"
#define R_CONTENTS "contents"
#define R_COPYRIGHT "copyright"
#define R_DEFINITION "definition"
#define R_DISCLAIMER "disclaimer"
#define R_EDITOR "editor"
#define R_END "end"
#define R_FIRST "first"
#define R_FOOTNOTE "footnote"
#define R_GLOSSARY "glossary"
#define R_INDEX "index"
#define R_LAST "last"
#define R_ORIGIN "origin"
#define R_PARENT "parent"
#define R_POINTER "pointer"
#define R_PREVIOUS "previous"
#define R_PUBLISHER "publisher"
#define R_SECTION "section"
#define R_SIBLING "sibling"
#define R_START "start"
#define R_SUBSECTION "subsection"
#define R_TOC "toc"
#define R_TOP "top"
#define R_TRADEMARK "trademark"
#define R_TRANSLATION "translation"
#define R_URC "urc"
#define R_UP "up"

// HTML3: https://www.w3.org/MarkUp/html3/dochead.html and http://microformats.org/wiki/existing-rel-values, dropped
#define R_BANNER "banner"
#define R_HOME "home"
#define R_NAVIGATE "navigate"

// GRDDL : https://www.w3.org/TR/grddl/#transformation
#define R_TRANSFORMATION "transformation"

// IANA: http://www.iana.org/assignments/link-relations/link-relations.xhtml
#define R_ABOUT "about"
#define R_ARCHIVES "archives"
#define R_BLOCKED_BY "blocked-by"
#define R_CANONICAL "canonical"
#define R_CITE_AS "cite-as"
#define R_CONVERTED_FROM "convertedFrom"
#define R_CREATE_FORM "create-form"
#define R_CURRENT "current"
#define R_DESCRIBED_BY "describedby"
#define R_DESCRIBES "describes"
#define R_DNSPREFETCH "dns-prefetch"
#define R_DUPLICATE "duplicate"
#define R_EDIT "edit"
#define R_EDIT_FORM "edit-form"
#define R_EDIT_MEDIA "edit-media"
#define R_ENCLOSURE "enclosure"
#define R_HOSTS "hosts"
#define R_HUB "hub"
#define R_INTERVAL_AFTER "intervalAfter"
#define R_INTERVAL_BEFORE "intervalBefore"
#define R_INTERVAL_CONTAINS "intervalContains"
#define R_INTERVAL_DISJOINT "intervalDisjoint"
#define R_INTERVAL_DURING "intervalDuring"
#define R_INTERVAL_EQUALS "intervalEquals"
#define R_INTERVAL_FINISHED_BY "intervalFinishedBy"
#define R_INTERVAL_FINISHES "intervalFinishes"
#define R_INTERVAL_IN "intervalIn"
#define R_INTERVAL_MEETS "intervalMeets"
#define R_INTERVAL_MET_BY "intervalMetBy"
#define R_INTERVAL_OVERLAPPED_BY "intervalOverlappedBy"
#define R_INTERVAL_OVERLAPS "intervalOverlaps"
#define R_INTERVAL_STARTED_BY "intervalStartedBy"
#define R_INTERVAL_STARTS "intervalStarts"
#define R_ITEM "item"
#define R_LATEST_VERSION "latest-version"
#define R_LRDD "lrdd" // Link-based Resource Descriptor Document
#define R_MEMENTO "memento"
#define R_MONITOR "monitor"
#define R_MONITOR_GROUP "monitor-group"
#define R_NEXT_ARCHIVE "next-archive"
#define R_ORIGINAL "original"
#define R_PAYMENT "payment"
#define R_PRECONNECT "preconnect"
#define R_PREDECESSOR_VERSION "predecessor-version"
#define R_PRELOAD "preload"
#define R_PRERENDER "prerender"
#define R_PREVIEW "preview"
#define R_PREV_ARCHIVE "prev-archive"
#define R_PRIVACY_POLICY "privacy-policy"
#define R_PROFILE "profile"
#define R_RELATED "related"
#define R_RESTCONF "restconf"
#define R_REPLIES "replies"
#define R_SELF "self"
#define R_SERVICE "service"
#define R_SERVICE_DESC "service-desc"
#define R_SERVICE_DOC "service-doc"
#define R_SERVICE_META "service-meta"
#define R_START "start"
#define R_STATUS "status"
#define R_SUCCESSOR_VERSION "successor-version"
#define R_SUNSET "sunset"
#define R_TERMS_OF_SERVICE "terms-of-service"
#define R_TIMEGATE "timegate"
#define R_TIMEMAP "timemap"
#define R_TYPE "type"
#define R_VERSION_HISTORY "version-history"
#define R_VIA "via"
#define R_WEBMENTION "webmention"
#define R_WORKING_COPY "working-copy"
#define R_WORKING_COPY_OF "working-copy-of"

// International Tag Set (its)
#define R_ITSRULES "its-rules" // internationalisation tag set

// microformats: http://microformats.org/wiki/existing-rel-values, XFN/HTML4, etc.
#define R_ACQUAINTANCE "acquaintance"
#define R_COLLEAGUE "colleague"
#define R_CONTACT "contact"
#define R_CORESIDENT "co-resident" // dubious hyphenation required
#define R_COWORKER "co-worker" // erroneous hyphenation required
#define R_CRUSH "crush"
#define R_DATE "date"
#define R_FRIEND "friend"
#define R_KIN "kin"
#define R_ME "me"
#define R_MET "met"
#define R_MUSE "muse"
#define R_NEIGHBOUR "neighbor" // misspelling required
#define R_SPOUSE "spouse"
#define R_SWEETHEART "sweetheart"

// microformats proposals: http://microformats.org/wiki/existing-rel-values
#define R_PRONUNCIATION "pronunciation"
#define R_DIRECTORY "directory"
#define R_VCS_GIT "vcs-git"
#define R_VCS_SVN "vcs-svn"

// microformts HTML5 link-type extensions: http://microformats.org/wiki/existing-rel-values
#define R_AMPHTML "amphtml"
#define R_APPLE_TOUCH_ICON "apple-touch-icon"
#define R_APPLE_TOUCH_ICON_PRECOMPOSED "apple-touch-icon-precomposed"
#define R_APPLE_TOUCH_STARTUP_IMAGE "apple-touch-startup-image"
#define R_ARCHIVED "archived"
#define R_ATTACHMENT "attachment"
#define R_AUTHORISATION_ENDPOINT "authorization-endpoint"
#define R_CATEGORY "category"
#define R_CHROME_WEBSTORE_ITEM "chrome-webstore-item"
#define R_CODE_LICENCE "code-license" // misspelling obligatory
#define R_CODE_REPOSITORY "code-repository"
#define R_COMPONENT "component"
#define R_CONTENT_LICENCE "content-license" // misspelling obligatory
#define R_CONTENT_REPOSITORY "content-repository"
#define R_CMIS "http://docs.oasis-open.org/ns/cmis/link/200908/acl"
#define R_DCTERMS_CONFORMS_TO "dcterms.conformsto"
#define R_DCTERMS_CONTRIBUTOR "dcterms.contributor"
#define R_DCTERMS_CREATOR "dcterms.creator"
#define R_DCTERMS_DESCRIPTION "dcterms.description"
#define R_DCTERMS_HAS_FORMAT "dcterms.hasformat"
#define R_DCTERMS_HAS_PART "dcterms.haspart"
#define R_DCTERMS_HAS_VERSION "dcterms.hasversion"
#define R_DCTERMS_IS_FORMAT_OF "dcterms.isformatof"
#define R_DCTERMS_IS_PART_OF "dcterms.ispartof"
#define R_DCTERMS_IS_REFERENCED_BY "dcterms.isreferencedby"
#define R_DCTERMS_IS_REPLACED_BY "dcterms.isreplacedby"
#define R_DCTERMS_IS_REQUIRED_BY "dcterms.isrequiredby"
#define R_DCTERMS_IS_VERSION_OF "dcterms.isversionof"
#define R_DCTERMS_LICENCE "dcterms.license" // misspelling obligatory
#define R_DCTERMS_MEDIATOR "dcterms.mediator"
#define R_DCTERMS_PUBLISHER "dcterms.publisher"
#define R_DCTERMS_REFERENCES "dcterms.references"
#define R_DCTERMS_RELATION "dcterms.relation"
#define R_DCTERMS_REPLACES "dcterms.replaces"
#define R_DCTERMS_REQUIRES "dcterms.requires"
#define R_DCTERMS_RIGHTS_HOLDER "dcterms.rightsholder"
#define R_DCTERMS_SOURCE "dcterms.source"
#define R_DCTERMS_SUBJECT "dcterms.subject"
#define R_DISCLOSURE "disclosure"
#define R_DISCUSSION "discussion"
#define R_EDIT_URI "edituri"
#define R_ENTRY_CATEGORY "entry-category"
#define R_ENTRY_CONTENT "entry-content"
#define R_GBFS "gbfs"
#define R_GTFS_STATIC "gtfs-static"
#define R_GTFS_REALTIME "gtfs-realtime"
#define R_IMAGE_SRC "image_src"
#define R_IMPORT "import"
#define R_IN_REPLY_TO "in-reply-to"
#define R_ISSUES "issues"
#define R_JSLICENCE "jslicense" // misspelling obligatory
#define R_LIGHTBOX "lightbox"
#define R_LIGHTVIDEO "lightvideo"
#define R_MANIFEST "manifest"
#define R_MASKICON "mask-icon"
#define R_META "meta"
#define R_MICROPUB "micropub"
#define R_NOOPENER "noopener"
#define R_OPENID_DELEGATE "openid.delegate"
#define R_OPENID_SERVER "openid.server"
#define R_OPENID2_LOCAL_ID "openid2.local_id"
#define R_OPENID2_PROVIDER "openid2.provider"
#define R_P3PV1 "P3Pv1"
#define R_PGPKEY "pgpkey"
#define R_RADIOEPG "radioepg"
#define R_RENDITION "rendition"
#define R_REPLY_TO "reply-to"
#define R_ROOT "root"
#define R_SCHEMA_DCTERMS "schema.dcterms"
#define R_SHORTLINK "shortlink"
#define R_SITEMAP "sitemap"
#define R_STYLESHEET_LESS "stylesheet/less"
#define R_SUBRESOURCE "subresource"
#define R_SWORD "sword"
#define R_SYNDICATION "syndication"
#define R_TIMESHEET "timesheet"
#define R_TOKEN_ENDPOINT "token_endpoint"
#define R_WIDGET "widget"
#define R_WLWMANIFEST "wlwmanifest"
#define R_YANDEX_TABLEAU_WIDGET "yandex-tableau-widget"

// microformats brainstorming:  http://microformats.org/wiki/existing-rel-values
#define R_ACCESSIBILITY "accessibility"
#define R_CITE "cite"
#define R_GROUP "group"
#define R_LONGDESC "longdesc"
#define R_MAP "map"
#define R_MEMBER "member"
#define R_M_PAGESCROLL2ID "m_pagescroll2id"
#define R_SOURCE "source"
#define R_VCALENDAR_PARENT "vcalendar-parent"
#define R_VCALENDAR_CHILD "vcalendar-child"
#define R_VCALENDAR_SIBLING "vcalendar-sibling"
#define R_WORDPRESS_API "https://w.api.org/"

// microformats POSH: http://microformats.org/wiki/existing-rel-values
#define R_COMMENT "comment"
#define R_CONTRIBUTION "contribution"
#define R_ENDORSED "endorsed"
#define R_FAN "fan"
#define R_FEED "feed"
#define R_KINETIC_STYLESHEET "kinetic-stylesheet"
#define R_MADE "made"
#define R_MICROSUMMARY "microsummary"
#define R_PERMALINK "permalink"
#define R_POPOVER "popover"
#define R_PRIVACY "privacy"
#define R_PUBLICKEY "publickey"
#define R_REFERRAL "referral"
#define R_RESPOND_PROXY "respond-proxy"
#define R_RESPOND_REDIRECT "respond-redirect"
#define R_RESOURCE "resource"
#define R_SPONSOR "sponsor"
#define R_TOOLTIP "tooltip"
#define R_TRACKBACK "trackback"
#define R_UNENDORSED "unendorsed"
#define R_USER "user"

// microformats DublinCore extra: http://microformats.org/wiki/existing-rel-value
#define R_SCHEMA_DC "schema.dc"

// microformats rejected: http://microformats.org/wiki/existing-rel-value
#define R_LOGO "logo"
#define R_PAVATAR "pavatar"

// microformats v1 (hNews): http://microformats.org/wiki/hnews
#define R_PRINCIPLES "principles"
#define R_ITEM_LICENCE "item-license"

// HTML 5.4 to be, July 2020
#define R_MODULE_PRELOAD "modulepreload"
