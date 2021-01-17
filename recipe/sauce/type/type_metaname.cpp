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
#include "type/type_metaname.h"
#include "type/type_enum_vec.h"
#include "webpage/page.h"

// note HTML 5, 2.6.5, extracting character encodings from meta elements

#define MN_CONTEXT "user-provided"

#define MN_APPLICATION "application"
#define MN_AUTHOR "author"
#define MN_DESCRIPTION "description"
#define MN_KEYWORDS "keywords"

#define MN_CLASSIFICATION "classification"

#define MN_AGLSTERMS_ACCESSMODE "aglsterms.accessmode"
#define MN_AGLSTERMS_ACCESSIBILITY "aglsterms.accessibility"
#define MN_AGLSTERMS_ACT "aglsterms.act"
#define MN_AGLSTERMS_AGGREGATIONLEVEL "aglsterms.aggregationlevel"
#define MN_AGLSTERMS_ALLOW_SEARCH "aglsterms.allow-search"
#define MN_AGLSTERMS_AVAILABILITY "aglsterms.availability"
#define MN_AGLSTERMS_CASE "aglsterms.case"
#define MN_AGLSTERMS_CATEGORY "aglsterms.category"
#define MN_AGLSTERMS_DATELICENSED "aglsterms.datelicensed"
#define MN_AGLSTERMS_DOCUMENTTYPE "aglsterms.documenttype"
#define MN_AGLSTERMS_FUNCTION "aglsterms.function"
#define MN_AGLSTERMS_ISBASEDON "aglsterms.isbasedon"
#define MN_AGLSTERMS_ISBASISFOR "aglsterms.isbasisfor"
#define MN_AGLSTERMS_JURISDICTION "aglsterms.jurisdiction"
#define MN_AGLSTERMS_MANDATE "aglsterms.mandate"
#define MN_AGLSTERMS_PROTECTIVEMARKING "aglsterms.protectivemarking"
#define MN_AGLSTERMS_REGULATION "aglsterms.regulation"
#define MN_AGLSTERMS_SERVICETYPE "aglsterms.servicetype"
#define MN_DCS_DCSSTA "dcs.dcssta"
#define MN_ESSAYDIRECTORY "essaydirectory"
#define MN_FLBLOGAUTHOR "flblogauthor"
#define MN_FSDATECREATION "fsdatecreation"
#define MN_FSDATEPUBLISH "fsdatepublish"
#define MN_FSFLCONTENT "fsflcontent"
#define MN_FSLANGUAGE "fslanguage"
#define MN_FSONSITEMAP "fsonsitemap"
#define MN_FSPAGEDESCRIPTION "fspagedescription"
#define MN_FSPAGENAME "fspagename"
#define MN_FSSEARCHABLE "fssearchable"
#define MN_FSSECTION "fssection"
#define MN_FSWRITERTOOLPAGETYPE "fswritertoolpagetype"
#define MN_IE_RM_OFF "ie_rm_off"
#define MN_MSSMARTTAGSPREVENTPARSING "mssmarttagspreventparsing"
#define MN_REPOSTUSAPIKEY "Repostusapikey"
#define MN_RESOURCELOADERDYNAMICSTYLES "resourceloaderdynamicstyles"
#define MN_WT_SI_N "wt.si_n"
#define MN_WT_SI_P "wt.si_p"
#define MN_WT_SI_X "wt.si_x"
#define MN_ZOOMCATEGORY "zoomcategory"
#define MN_ZOOMDESCRIPTION "zoomdescription"
#define MN_ZOOMIMAGE "zoomimage"
#define MN_ZOOMPAGEBOOST "zoompageboost"
#define MN_ZOOMTITLE "zoomtitle"
#define MN_ZOOMWORDS "zoomwords"
#define MN_ALEXAVERIFYID "alexaverifyid"
#define MN_APPLE_ITUNES_APP "apple-itunes-app"
#define MN_APPLE_MOBILE_WEB_APP_CAPABLE "apple-mobile-web-app-capable"
#define MN_APPLE_MOBILE_WEB_APP_STATUS_BAR_STYLE "apple-mobile-web-app-status-bar-style"
#define MN_APPLE_MOBILE_WEB_APP_TITLE "apple-mobile-web-app-title"
#define MN_APPLE_TOUCH_FULLSCREEN "apple-touch-fullscreen"
#define MN_APPLICATION_NAME "application-name"
#define MN_APPLICATION_URL "application-url"
#define MN_APPSTORE_BUNDLE_ID "appstore:bundle_id"
#define MN_APPSTORE_DEVELOPER_URL "appstore:developer_url"
#define MN_APPSTORE_STORE_ID "appstore:store_id"
#define MN_AUDIENCE "audience"
#define MN_BITCOIN "bitcoin"
#define MN_BLAZERR_SECURE "blazerr-secure"
#define MN_BLAZERR_SEO "blazerr-seo"
#define MN_BLAZERR_SSL "blazerr-ssl"
#define MN_BLAZERR_SUPPORT_ID_NONCOOKIES "blazerr-support-id-noncookies"
#define MN_BLAZERR_SUPPORT_IDENTIFIER "blazerr-support-identifier"
#define MN_BLOGCATALOG "blogcatalog"
#define MN_BUG_BLOCKED "bug.blocked"
#define MN_BUG_COMMENT "bug.comment"
#define MN_BUG_COMPONENT "bug.component"
#define MN_BUG_PRODUCT "bug.product"
#define MN_BUG_SHORT_DESC "bug.short_desc"
#define MN_CACHE "cache"
#define MN_CFIA_GDR_ACTIVITY "cfia.gdr.activity"
#define MN_CFIA_GDR_COMMODITY "cfia.gdr.commodity"
#define MN_CFIA_GDR_INCLUDE "cfia.gdr.include"
#define MN_CFIA_GDR_PROGRAM "cfia.gdr.program"
#define MN_CITATION_AUTHOR "citation_author"
#define MN_CITATION_AUTHOR_EMAIL "citation_author_email"
#define MN_CITATION_AUTHOR_INSTITUTION "citation_author_institution"
#define MN_CITATION_CONFERENCE_TITLE "citation_conference_title"
#define MN_CITATION_DATE "citation_date"
#define MN_CITATION_DISSERTATION_INSTITUTION "citation_dissertation_institution"
#define MN_CITATION_DOI "citation_doi"
#define MN_CITATION_FIRSTPAGE "citation_firstpage"
#define MN_CITATION_FULLTEXT_HTML_URL "citation_fulltext_html_url"
#define MN_CITATION_ISBN "citation_isbn"
#define MN_CITATION_ISSN "citation_issn"
#define MN_CITATION_ISSUE "citation_issue"
#define MN_CITATION_JOURNAL_ABBREV "citation_journal_abbrev"
#define MN_CITATION_JOURNAL_TITLE "citation_journal_title"
#define MN_CITATION_KEYWORDS "citation_keywords"
#define MN_CITATION_LANGUAGE "citation_language"
#define MN_CITATION_LASTPAGE "citation_lastpage"
#define MN_CITATION_PDF_URL "citation_pdf_url"
#define MN_CITATION_PUBLICATION_DATE "citation_publication_date"
#define MN_CITATION_PUBLISHER "citation_publisher"
#define MN_CITATION_TECHNICAL_REPORT_INSTITUTION "citation_technical_report_institution"
#define MN_CITATION_TECHNICAL_REPORT_NUMBER "citation_technical_report_number"
#define MN_CITATION_TITLE "citation_title"
#define MN_CITATION_VOLUME "citation_volume"
#define MN_COLLECTION "collection"
#define MN_CONTACT "contact"
#define MN_CREATED "created"
#define MN_CREATOR "creator"
#define MN_CSRF_PARAM "csrf-param"
#define MN_CSRF_TOKEN "csrf-token"
#define MN_DA_ANONYMISEIP "da_anonymiseip"
#define MN_DA_CONTACTCOMPANY "da_contactcompany"
#define MN_DA_CONTACTEMAIL "da_contactemail"
#define MN_DA_CONTACTFIRSTNAME "da_contactfirstname"
#define MN_DA_CONTACTLASTNAME "da_contactlastname"
#define MN_DA_CONTACTNAME "da_contactname"
#define MN_DA_CONTACTTELEPHONE "da_contacttelephone"
#define MN_DA_CONVERSIONCURRENCY "da_conversioncurrency"
#define MN_DA_CONVERSIONID "da_conversionid"
#define MN_DA_CONVERSIONVALUE "da_conversionvalue"
#define MN_DA_GOALCURRENCY "da_goalcurrency"
#define MN_DA_GOALID "da_goalid"
#define MN_DA_GOALVALUE "da_goalvalue"
#define MN_DA_INTERACTIONSELECTOR "da_interactionselector"
#define MN_DA_PAGEROLE "da_pagerole"
#define MN_DA_PAGETAXONOMY "da_pagetaxonomy"
#define MN_DA_PAGETITLE "da_pagetitle"
#define MN_DA_PAGEVERSION "da_pageversion"
#define MN_DA_SESSIONID "da_sessionid"
#define MN_DA_USERID "da_userid"

#define MN_DCTERMS_ABSTRACT "dcterms.abstract"
#define MN_DCTERMS_ACCESSRIGHTS "dcterms.accessrights"
#define MN_DCTERMS_ACCRUALMETHOD "dcterms.accrualmethod"
#define MN_DCTERMS_ACCRUALPERIODICITY "dcterms.accrualperiodicity"
#define MN_DCTERMS_ACCRUALPOLICY "dcterms.accrualpolicy"
#define MN_DCTERMS_ALTERNATIVE "dcterms.alternative"
#define MN_DCTERMS_AUDIENCE "dcterms.audience"
#define MN_DCTERMS_AVAILABLE "dcterms.available"
#define MN_DCTERMS_BIBLIOGRAPHICCITATION "dcterms.bibliographiccitation"
#define MN_DCTERMS_CONFORMSTO "dcterms.conformsto"
#define MN_DCTERMS_CONTRIBUTOR "dcterms.contributor"
#define MN_DCTERMS_COVERAGE "dcterms.coverage"
#define MN_DCTERMS_CREATED "dcterms.created"
#define MN_DCTERMS_CREATOR "dcterms.creator"
#define MN_DCTERMS_DATE "dcterms.date"
#define MN_DCTERMS_DATEACCEPTED "dcterms.dateaccepted"
#define MN_DCTERMS_DATECOPYRIGHTED "dcterms.datecopyrighted"
#define MN_DCTERMS_DATESUBMITTED "dcterms.datesubmitted"
#define MN_DCTERMS_DESCRIPTION "dcterms.description"
#define MN_DCTERMS_EDUCATIONLEVEL "dcterms.educationlevel"
#define MN_DCTERMS_EXTENT "dcterms.extent"
#define MN_DCTERMS_FORMAT "dcterms.format"
#define MN_DCTERMS_HASFORMAT "dcterms.hasformat"
#define MN_DCTERMS_HASPART "dcterms.haspart"
#define MN_DCTERMS_HASVERSION "dcterms.hasversion"
#define MN_DCTERMS_IDENTIFIER "dcterms.identifier"
#define MN_DCTERMS_INSTRUCTIONALMETHOD "dcterms.instructionalmethod"
#define MN_DCTERMS_ISFORMATOF "dcterms.isformatof"
#define MN_DCTERMS_ISPARTOF "dcterms.ispartof"
#define MN_DCTERMS_ISREFERENCEDBY "dcterms.isreferencedby"
#define MN_DCTERMS_ISREPLACEDBY "dcterms.isreplacedby"
#define MN_DCTERMS_ISREQUIREDBY "dcterms.isrequiredby"
#define MN_DCTERMS_ISSUED "dcterms.issued"
#define MN_DCTERMS_ISVERSIONOF "dcterms.isversionof"
#define MN_DCTERMS_LANGUAGE "dcterms.language"
#define MN_DCTERMS_LICENSE "dcterms.license"
#define MN_DCTERMS_MEDIATOR "dcterms.mediator"
#define MN_DCTERMS_MEDIUM "dcterms.medium"
#define MN_DCTERMS_MODIFIED "dcterms.modified"
#define MN_DCTERMS_PROVENANCE "dcterms.provenance"
#define MN_DCTERMS_PUBLISHER "dcterms.publisher"
#define MN_DCTERMS_REFERENCES "dcterms.references"
#define MN_DCTERMS_RELATION "dcterms.relation"
#define MN_DCTERMS_REPLACES "dcterms.replaces"
#define MN_DCTERMS_REQUIRES "dcterms.requires"
#define MN_DCTERMS_RIGHTS "dcterms.rights"
#define MN_DCTERMS_RIGHTSHOLDER "dcterms.rightsholder"
#define MN_DCTERMS_SOURCE "dcterms.source"
#define MN_DCTERMS_SPATIAL "dcterms.spatial"
#define MN_DCTERMS_SUBJECT "dcterms.subject"
#define MN_DCTERMS_TABLEOFCONTENTS "dcterms.tableofcontents"
#define MN_DCTERMS_TEMPORAL "dcterms.temporal"
#define MN_DCTERMS_TITLE "dcterms.title"
#define MN_DCTERMS_TYPE "dcterms.type"
#define MN_DCTERMS_VALID "dcterms.valid"
#define MN_DESIGNER "designer"
#define MN_DETECTIFY_VERIFICATION "detectify-verification"
#define MN_DIR_CONTENT_POINTER "dir-content-pointer"
#define MN_ENTITY "entity"
#define MN_EXPIRES "expires"
#define MN_FB_ADMINS "fb:admins"
#define MN_FB_PAGE_ID "fb:page_id"
#define MN_FDSE_DESCRIPTION "fdse-description"
#define MN_FDSE_INDEX_AS "fdse-index-as"
#define MN_FDSE_KEYWORDS "fdse-keywords"
#define MN_FDSE_REFRESH "fdse-refresh"
#define MN_FDSE_ROBOTS "fdse-robots"
#define MN_FORMAT_DETECTION "format-detection"
#define MN_FORMAT_PRINT "format-print"
#define MN_FRAGMENT "fragment"
#define MN_GCTERMS_TOPICTAXONOMY "gcterms.topictaxonomy"
#define MN_GEO_A1 "geo.a1"
#define MN_GEO_A2 "geo.a2"
#define MN_GEO_A3 "geo.a3"
#define MN_GEO_COUNTRY "geo.country"
#define MN_GEO_LMK "geo.lmk"
#define MN_GEO_PLACENAME "geo.placename"
#define MN_GEO_POSITION "geo.position"
#define MN_GEO_REGION "geo.region"
#define MN_GLOBRIX_BATHROOMS "globrix.bathrooms"
#define MN_GLOBRIX_BEDROOMS "globrix.bedrooms"
#define MN_GLOBRIX_CONDITION "globrix.condition"
#define MN_GLOBRIX_FEATURES "globrix.features"
#define MN_GLOBRIX_INSTRUCTION "globrix.instruction"
#define MN_GLOBRIX_LATITUDE "globrix.latitude"
#define MN_GLOBRIX_LONGITUDE "globrix.longitude"
#define MN_GLOBRIX_OUTSIDESPACE "globrix.outsidespace"
#define MN_GLOBRIX_PARKING "globrix.parking"
#define MN_GLOBRIX_PERIOD "globrix.period"
#define MN_GLOBRIX_POA "globrix.poa"
#define MN_GLOBRIX_POSTCODE "globrix.postcode"
#define MN_GLOBRIX_PRICE "globrix.price"
#define MN_GLOBRIX_PRICEPROXIMITY "globrix.priceproximity"
#define MN_GLOBRIX_TENURE "globrix.tenure"
#define MN_GLOBRIX_TYPE "globrix.type"
#define MN_GLOBRIX_UNDEROFFER "globrix.underoffer"
#define MN_GM_GPX_V "gm-gpx-v"
#define MN_GO_IMPORT "go-import"
#define MN_GOOGLE "google"
#define MN_GOOGLE_PLAY_APP "google-play-app"
#define MN_GOOGLE_SITE_VERIFICATION "google-site-verification"
#define MN_GOOGLE_TRANSLATE_CUSTOMIZATION "google-translate-customization"
#define MN_GWT_PROPERTY "gwt:property"
#define MN_HANDHELDFRIENDLY "handheldfriendly"
#define MN_ICAS_DATETIME "icas.datetime"
#define MN_ICAS_DATETIME_ABBR "icas.datetime.abbr"
#define MN_ICAS_DATETIME_DAY "icas.datetime.day"
#define MN_ICAS_DATETIME_LONG "icas.datetime.long"
#define MN_ICBM "icbm"
#define MN_ITEMSPERPAGE "itemsPerPage"
#define MN_KEYWORDS_NOT "keywords-not"
#define MN_META_DATE "meta_date"
#define MN_MICROTIP "microtip"
#define MN_MOBILE_AGENT "mobile-agent"
#define MN_MOBILE_WEB_APP_CAPABLE "mobile-web-app-capable"
#define MN_MOBILEOPTIMIZED "mobileoptimized"
#define MN_MSAPPLICATION_TILECOLOR "msapplication-tilecolor"
#define MN_MSAPPLICATION_TILEIMAGE "msapplication-tileimage"
#define MN_MSAPPLICATION_CONFIG "msapplication-config"
#define MN_MSAPPLICATION_NAVBUTTON_COLOR "msapplication-navbutton-color"
#define MN_MSAPPLICATION_NOTIFICATION "msapplication-notification"
#define MN_MSAPPLICATION_SQUARE150X150LOGO "msapplication-square150x150logo"
#define MN_MSAPPLICATION_SQUARE310X310LOGO "msapplication-square310x310logo"
#define MN_MSAPPLICATION_SQUARE70X70LOGO "msapplication-square70x70logo"
#define MN_MSAPPLICATION_STARTURL "msapplication-starturl"
#define MN_MSAPPLICATION_TAP_HIGHLIGHT "msapplication-tap-highlight"
#define MN_MSAPPLICATION_TASK "msapplication-task"
#define MN_MSAPPLICATION_TOOLTIP "msapplication-tooltip"
#define MN_MSAPPLICATION_WIDE310X150LOGO "msapplication-wide310x150logo"
#define MN_MSAPPLICATION_WINDOW "msapplication-window"
#define MN_MSVALIDATE_01 "msvalidate.01"
#define MN_NEXTGEN "nextgen"
#define MN_NIBBLER_SITE_VERIFICATION "nibbler-site-verification"
#define MN_NO_EMAIL_COLLECTION "no-email-collection"
#define MN_NONFICTION "nonfiction"
#define MN_NORTON_SAFEWEB_SITE_VERIFICATION "norton-safeweb-site-verification"
#define MN_OG_DESCRIPTION "og:description"
#define MN_OG_IMAGE "og:image"
#define MN_OG_LOCALE "og:locale"
#define MN_OG_SITE_NAME "og:site_name"
#define MN_OG_TITLE "og:title"
#define MN_OG_TYPE "og:type"
#define MN_OG_URL "og:url"
#define MN_ORIGIN "origin"
#define MN_ORIGIN_TRIALS "origin-trials"
#define MN_P_DOMAIN_VERIFY "p:domain_verify"
#define MN_PAGE_VERSION "page-version"
#define MN_PINGDOM "pingdom"
#define MN_PINTEREST "pinterest"
#define MN_PRISM_ALTERNATETITLE "prism:alternatetitle"
#define MN_PRO "pro"
#define MN_PRO_AUTH "pro-auth"
#define MN_PRO_AUTH_FIELD "pro-auth-field"
#define MN_PRO_AUTH_FRAGMENT "pro-auth-fragment"
#define MN_RATING "rating"
#define MN_REFERRER "referrer"
#define MN_RESOLUTIONS "resolutions"
#define MN_REVIEW_DATE "review_date"
#define MN_REVISION "revision"
#define MN_REVISIT_AFTER "revisit-after"
#define MN_RIGHTS "rights"
#define MN_RIGHTS_STANDARD "rights-standard"
#define MN_ROBOTS "robots"
#define MN_RPUPLUGIN "rpuPlugin"
#define MN_RQID "rqid"
#define MN_SHAREAHOLIC_ANALYTICS "shareaholic:analytics"
#define MN_SHAREAHOLIC_ARTICLE_AUTHOR "shareaholic:article_author"
#define MN_SHAREAHOLIC_ARTICLE_AUTHOR_NAME "shareaholic:article_author_name"
#define MN_SHAREAHOLIC_ARTICLE_MODIFIED_TIME "shareaholic:article_modified_time"
#define MN_SHAREAHOLIC_ARTICLE_PUBLISHED_TIME "shareaholic:article_published_time"
#define MN_SHAREAHOLIC_ARTICLE_VISIBILITY "shareaholic:article_visibility"
#define MN_SHAREAHOLIC_DRUPAL_VERSION "shareaholic:drupal_version"
#define MN_SHAREAHOLIC_IMAGE "shareaholic:image"
#define MN_SHAREAHOLIC_KEYWORDS "shareaholic:keywords"
#define MN_SHAREAHOLIC_LANGUAGE "shareaholic:language"
#define MN_SHAREAHOLIC_OUTSTREAMADS "shareaholic:outstreamads"
#define MN_SHAREAHOLIC_SHAREABLE_PAGE "shareaholic:shareable_page"
#define MN_SHAREAHOLIC_SITE_ID "shareaholic:site_id"
#define MN_SHAREAHOLIC_SITE_NAME "shareaholic:site_name"
#define MN_SHAREAHOLIC_URL "shareaholic:url"
#define MN_SHAREAHOLIC_WP_VERSION "shareaholic:wp_version"
#define MN_SIGNET_AUTHORS "signet:authors"
#define MN_SIGNET_LINKS "signet:links"
#define MN_SKYPE_TOOLBAR "skype_toolbar"
#define MN_STARTINDEX "startIndex"
#define MN_STARTVER "startver"
#define MN_SUBJECT_DATETIME "subject-datetime"
#define MN_SUBJECT_SYSTEM "subject-system"
#define MN_THEME_COLOUR "theme-color"
#define MN_THUMBNAIL "thumbnail"
#define MN_TOPPER "topper"
#define MN_TOPPER_MAJOR "topper-major"
#define MN_TOPPER_MINOR "topper-minor"
#define MN_TOTALRESULTS "totalResults"
#define MN_TRANSLATOR "translator"
#define MN_TWITTER_APP_COUNTRY "twitter:app:country"
#define MN_TWITTER_APP_ID_GOOGLEPLAY "twitter:app:id:googleplay"
#define MN_TWITTER_APP_ID_IPAD "twitter:app:id:ipad"
#define MN_TWITTER_APP_ID_IPHONE "twitter:app:id:iphone"
#define MN_TWITTER_APP_NAME_GOOGLEPLAY "twitter:app:name:googleplay"
#define MN_TWITTER_APP_NAME_IPAD "twitter:app:name:ipad"
#define MN_TWITTER_APP_NAME_IPHONE "twitter:app:name:iphone"
#define MN_TWITTER_APP_URL_GOOGLEPLAY "twitter:app:url:googleplay"
#define MN_TWITTER_APP_URL_IPAD "twitter:app:url:ipad"
#define MN_TWITTER_APP_URL_IPHONE "twitter:app:url:iphone"
#define MN_TWITTER_CARD "twitter:card"
#define MN_TWITTER_CREATOR "twitter:creator"
#define MN_TWITTER_CREATOR_ID "twitter:creator:id"
#define MN_TWITTER_DATA1 "twitter:data1"
#define MN_TWITTER_DATA2 "twitter:data2"
#define MN_TWITTER_DESCRIPTION "twitter:description"
#define MN_TWITTER_DOMAIN "twitter:domain"
#define MN_TWITTER_IMAGE "twitter:image"
#define MN_TWITTER_IMAGE0 "twitter:image0"
#define MN_TWITTER_IMAGE1 "twitter:image1"
#define MN_TWITTER_IMAGE2 "twitter:image2"
#define MN_TWITTER_IMAGE3 "twitter:image3"
#define MN_TWITTER_IMAGE_HEIGHT "twitter:image:height"
#define MN_TWITTER_IMAGE_SRC "twitter:image:src"
#define MN_TWITTER_IMAGE_WIDTH "twitter:image:width"
#define MN_TWITTER_LABEL1 "twitter:label1"
#define MN_TWITTER_LABEL2 "twitter:label2"
#define MN_TWITTER_PLAYER "twitter:player"
#define MN_TWITTER_PLAYER_HEIGHT "twitter:player:height"
#define MN_TWITTER_PLAYER_STREAM "twitter:player:stream"
#define MN_TWITTER_PLAYER_STREAM_CONTENT_TYPE "twitter:player:stream:content_type"
#define MN_TWITTER_PLAYER_WIDTH "twitter:player:width"
#define MN_TWITTER_SITE "twitter:site"
#define MN_TWITTER_SITE_ID "twitter:site:id"
#define MN_TWITTER_TITLE "twitter:title"
#define MN_TWITTER_URL "twitter:url"
#define MN_TYPEMETAL_FORMATPREFS "typemetal.formatprefs"
#define MN_VERIFY_V1 "verify-v1"
#define MN_VERSION "version"
#define MN_VFB_VERSION "vfb-version"
#define MN_VIEWPORT "viewport"
#define MN_WEB_AUTHOR "web_author"
#define MN_WITGET "witget"
#define MN_WOT_VERIFICATION "wot-verification"
#define MN_WT_AC "wt.ac"
#define MN_WT_AD "wt.ad"
#define MN_WT_CG_N "wt.cg_n"
#define MN_WT_CG_S "wt.cg_s"
#define MN_WT_MC_ID "wt.mc_id"
#define MN_WT_SV "wt.sv"
#define MN_WT_TI "wt.ti"
#define MN_Y_KEY "y_key"
#define MN_YANDEX_VERIFICATION "yandex-verification"

#define MN_IDENTIFIER_URL "identifier-url"
#define MN_DISTRIBUTION "distribution"
#define MN_NOTE "note"
#define MN_SUBJECT "subject"
#define MN_COPYRIGHT "copyright"
#define MN_LANGUAGE "language"
#define MN_GENERATOR "generator"
#define MN_ID "id"
#define MN_PRESDATE "presdate"
#define MN_TEMPLATE "template"
#define MN_OPERATOR "operator"
#define MN_CREATION "creation"
#define MN_HOST "host"
#define MN_HOST_ADMIN "host-admin"
#define MN_CONTACTNAME "contactname"
#define MN_CONTACTORGANIZATION "contactorganization"
#define MN_CONTACTSTREETADDRESS1 "contactstreetaddress1"
#define MN_CONTACTZIPCODE "contactzipcode"
#define MN_CONTACTCITY "contactcity"
#define MN_CONTACTCOUNTRY "contactcountry"
#define MN_CONTACTPHONENUMBER "contactphonenumber"
#define MN_CONTACTFAXNUMBER "contactfaxnumber"
#define MN_CONTACTNETWORKADDRESS "contactnetworkaddress"
#define MN_LINKAGE "linkage"

#define MN_ABSTRACT "abstract"
#define MN_COVERAGE "coverage"
#define MN_OG_EMAIL "og:email"
#define MN_OG_PHONE_NUMBER "og:phone_number"
#define MN_OG_FAX_NUMBER "og:fax_number"
#define MN_OG_LATITUDE "og:latitude"
#define MN_OG_LONGITUDE "og:longitude"
#define MN_OG_STREET_ADDRESS "og:street-address"
#define MN_OG_LOCALITY "og:locality"
#define MN_OG_REGION "og:region"
#define MN_OG_POSTAL_CODE "og:postal-code"
#define MN_OG_COUNTRY_NAME "og:country-name"
#define MN_MICROID "microid"
#define MN_OWNER "owner"
#define MN_REVISED "revised"
#define MN_TOPIC "topic"
#define MN_SUMMARY "summary"
#define MN_TWEETMEME_TITLE "tweetmeme-title"

struct symbol_entry < e_metaname > metaname_symbol_table [] =
{  { { HTML_UNDEF }, { HTML_UNDEF }, MN_CONTEXT, mn_context },

   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPLICATION, mn_application },
   { { HTML_2_0 }, { HTML_UNDEF }, MN_AUTHOR, mn_author },
   { { HTML_2_0 }, { HTML_UNDEF }, MN_DESCRIPTION, mn_description },
   { { HTML_2_0 }, { HTML_UNDEF }, "generator", mn_generator },
   { { HTML_2_0 }, { HTML_UNDEF }, MN_KEYWORDS, mn_keywords },
   { { HTML_2_0 }, { HTML_UNDEF }, "identifier", mn_identifier },

   { { HTML_2_0 }, { HTML_UNDEF }, MN_CLASSIFICATION, mn_classification },

   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_ACCESSMODE, mn_aglsterms_accessmode },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_ACCESSIBILITY, mn_aglsterms_accessibility },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_ACT, mn_aglsterms_act },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_AGGREGATIONLEVEL, mn_aglsterms_aggregationlevel },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_ALLOW_SEARCH, mn_aglsterms_allow_search },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_AVAILABILITY, mn_aglsterms_availability },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_CASE, mn_aglsterms_case },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_CATEGORY, mn_aglsterms_category },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_DATELICENSED, mn_aglsterms_datelicensed },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_DOCUMENTTYPE, mn_aglsterms_documenttype },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_FUNCTION, mn_aglsterms_function },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_ISBASEDON, mn_aglsterms_isbasedon },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_ISBASISFOR, mn_aglsterms_isbasisfor },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_JURISDICTION, mn_aglsterms_jurisdiction },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_MANDATE, mn_aglsterms_mandate },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_PROTECTIVEMARKING, mn_aglsterms_protectivemarking },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_REGULATION, mn_aglsterms_regulation },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AGLSTERMS_SERVICETYPE, mn_aglsterms_servicetype },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCS_DCSSTA, mn_dcs_dcssta },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ESSAYDIRECTORY, mn_essaydirectory },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FLBLOGAUTHOR, mn_flblogauthor },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FSDATECREATION, mn_fsdatecreation },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FSDATEPUBLISH, mn_fsdatepublish },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FSFLCONTENT, mn_fsflcontent },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FSLANGUAGE, mn_fslanguage },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FSONSITEMAP, mn_fsonsitemap },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FSPAGEDESCRIPTION, mn_fspagedescription },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FSPAGENAME, mn_fspagename },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FSSEARCHABLE, mn_fssearchable },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FSSECTION, mn_fssection },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FSWRITERTOOLPAGETYPE, mn_fswritertoolpagetype },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_IE_RM_OFF, mn_ie_rm_off },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSSMARTTAGSPREVENTPARSING, mn_mssmarttagspreventparsing },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_REPOSTUSAPIKEY, mn_repostusapikey },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_RESOURCELOADERDYNAMICSTYLES, mn_resourceloaderdynamicstyles },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WT_SI_N, mn_wt_si_n },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WT_SI_P, mn_wt_si_p },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WT_SI_X, mn_wt_si_x },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ZOOMCATEGORY, mn_zoomcategory },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ZOOMDESCRIPTION, mn_zoomdescription },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ZOOMIMAGE, mn_zoomimage },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ZOOMPAGEBOOST, mn_zoompageboost },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ZOOMTITLE, mn_zoomtitle },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ZOOMWORDS, mn_zoomwords },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ALEXAVERIFYID, mn_alexaverifyid },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPLE_ITUNES_APP, mn_apple_itunes_app },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPLE_MOBILE_WEB_APP_CAPABLE, mn_apple_mobile_web_app_capable },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPLE_MOBILE_WEB_APP_STATUS_BAR_STYLE, mn_apple_mobile_web_app_status_bar_style },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPLE_MOBILE_WEB_APP_TITLE, mn_apple_mobile_web_app_title },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPLE_TOUCH_FULLSCREEN, mn_apple_touch_fullscreen },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPLICATION_NAME, mn_application_name },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPLICATION_URL, mn_application_url },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPSTORE_BUNDLE_ID, mn_appstore_bundle_id },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPSTORE_DEVELOPER_URL, mn_appstore_developer_url },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_APPSTORE_STORE_ID, mn_appstore_store_id },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_AUDIENCE, mn_audience },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BITCOIN, mn_bitcoin },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BLAZERR_SECURE, mn_blazerr_secure },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BLAZERR_SEO, mn_blazerr_seo },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BLAZERR_SSL, mn_blazerr_ssl },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BLAZERR_SUPPORT_ID_NONCOOKIES, mn_blazerr_support_id_noncookies },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BLAZERR_SUPPORT_IDENTIFIER, mn_blazerr_support_identifier },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BLOGCATALOG, mn_blogcatalog },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BUG_BLOCKED, mn_bug_blocked },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BUG_COMMENT, mn_bug_comment },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BUG_COMPONENT, mn_bug_component },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BUG_PRODUCT, mn_bug_product },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_BUG_SHORT_DESC, mn_bug_short_desc },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CACHE, mn_cache },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CFIA_GDR_ACTIVITY, mn_cfia_gdr_activity },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CFIA_GDR_COMMODITY, mn_cfia_gdr_commodity },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CFIA_GDR_INCLUDE, mn_cfia_gdr_include },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CFIA_GDR_PROGRAM, mn_cfia_gdr_program },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_AUTHOR, mn_citation_author },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_AUTHOR_EMAIL, mn_citation_author_email },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_AUTHOR_INSTITUTION, mn_citation_author_institution },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_CONFERENCE_TITLE, mn_citation_conference_title },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_DATE, mn_citation_date },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_DISSERTATION_INSTITUTION, mn_citation_dissertation_institution },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_DOI, mn_citation_doi },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_FIRSTPAGE, mn_citation_firstpage },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_FULLTEXT_HTML_URL, mn_citation_fulltext_html_url },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_ISBN, mn_citation_isbn },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_ISSN, mn_citation_issn },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_ISSUE, mn_citation_issue },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_JOURNAL_ABBREV, mn_citation_journal_abbrev },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_JOURNAL_TITLE, mn_citation_journal_title },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_KEYWORDS, mn_citation_keywords },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_LANGUAGE, mn_citation_language },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_LASTPAGE, mn_citation_lastpage },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_PDF_URL, mn_citation_pdf_url },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_PUBLICATION_DATE, mn_citation_publication_date },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_PUBLISHER, mn_citation_publisher },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_TECHNICAL_REPORT_INSTITUTION, mn_citation_technical_report_institution },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_TECHNICAL_REPORT_NUMBER, mn_citation_technical_report_number },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_TITLE, mn_citation_title },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CITATION_VOLUME, mn_citation_volume },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_COLLECTION, mn_collection },
   { { HTML_JAN21 }, { HTML_UNDEF }, "color-scheme", mn_colour_scheme },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CONTACT, mn_contact },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CREATED, mn_created },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CREATOR, mn_creator },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CSRF_PARAM, mn_csrf_param },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_CSRF_TOKEN, mn_csrf_token },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_ANONYMISEIP, mn_da_anonymiseip },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_CONTACTCOMPANY, mn_da_contactcompany },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_CONTACTEMAIL, mn_da_contactemail },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_CONTACTFIRSTNAME, mn_da_contactfirstname },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_CONTACTLASTNAME, mn_da_contactlastname },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_CONTACTNAME, mn_da_contactname },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_CONTACTTELEPHONE, mn_da_contacttelephone },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_CONVERSIONCURRENCY, mn_da_conversioncurrency },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_CONVERSIONID, mn_da_conversionid },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_CONVERSIONVALUE, mn_da_conversionvalue },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_GOALCURRENCY, mn_da_goalcurrency },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_GOALID, mn_da_goalid },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_GOALVALUE, mn_da_goalvalue },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_INTERACTIONSELECTOR, mn_da_interactionselector },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_PAGEROLE, mn_da_pagerole },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_PAGETAXONOMY, mn_da_pagetaxonomy },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_PAGETITLE, mn_da_pagetitle },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_PAGEVERSION, mn_da_pageversion },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_SESSIONID, mn_da_sessionid },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DA_USERID, mn_da_userid },
   { { HTML_4_0 }, { HTML_UNDEF }, "date", mn_date }, // 4.00 specification
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.contributor", mn_dc_contributor },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.coverage", mn_dc_coverage },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.creator", mn_dc_creator },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.date", mn_dc_date },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.description", mn_dc_description },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.format", mn_dc_format },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.identifier", mn_dc_identifier },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.language", mn_dc_language },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.publisher", mn_dc_publisher },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.relation", mn_dc_relation },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.right", mn_dc_rights },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.source", mn_dc_source },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.subject", mn_dc_subject },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.title", mn_dc_title },
   { { HTML_2_0 }, { HTML_UNDEF }, "dc.type", mn_dc_type },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ABSTRACT, mn_dcterms_abstract },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ACCESSRIGHTS, mn_dcterms_accessrights },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ACCRUALMETHOD, mn_dcterms_accrualmethod },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ACCRUALPERIODICITY, mn_dcterms_accrualperiodicity },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ACCRUALPOLICY, mn_dcterms_accrualpolicy },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ALTERNATIVE, mn_dcterms_alternative },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_AUDIENCE, mn_dcterms_audience },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_AVAILABLE, mn_dcterms_available },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_BIBLIOGRAPHICCITATION, mn_dcterms_bibliographiccitation },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_CONFORMSTO, mn_dcterms_conformsto },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_CONTRIBUTOR, mn_dcterms_contributor },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_COVERAGE, mn_dcterms_coverage },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_CREATED, mn_dcterms_created },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_CREATOR, mn_dcterms_creator },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_DATE, mn_dcterms_date },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_DATEACCEPTED, mn_dcterms_dateaccepted },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_DATECOPYRIGHTED, mn_dcterms_datecopyrighted },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_DATESUBMITTED, mn_dcterms_datesubmitted },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_DESCRIPTION, mn_dcterms_description },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_EDUCATIONLEVEL, mn_dcterms_educationlevel },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_EXTENT, mn_dcterms_extent },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_FORMAT, mn_dcterms_format },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_HASFORMAT, mn_dcterms_hasformat },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_HASPART, mn_dcterms_haspart },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_HASVERSION, mn_dcterms_hasversion },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_IDENTIFIER, mn_dcterms_identifier },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_INSTRUCTIONALMETHOD, mn_dcterms_instructionalmethod },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ISFORMATOF, mn_dcterms_isformatof },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ISPARTOF, mn_dcterms_ispartof },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ISREFERENCEDBY, mn_dcterms_isreferencedby },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ISREPLACEDBY, mn_dcterms_isreplacedby },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ISREQUIREDBY, mn_dcterms_isrequiredby },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ISVERSIONOF, mn_dcterms_isversionof },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_ISSUED, mn_dcterms_issued },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_LANGUAGE, mn_dcterms_language },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_LICENSE, mn_dcterms_license },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_MEDIATOR, mn_dcterms_mediator },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_MEDIUM, mn_dcterms_medium },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_MODIFIED, mn_dcterms_modified },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_PROVENANCE, mn_dcterms_provenance },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_PUBLISHER, mn_dcterms_publisher },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_REFERENCES, mn_dcterms_references },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_RELATION, mn_dcterms_relation },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_REPLACES, mn_dcterms_replaces },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_REQUIRES, mn_dcterms_requires },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_RIGHTS, mn_dcterms_rights },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_RIGHTSHOLDER, mn_dcterms_rightsholder },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_SOURCE, mn_dcterms_source },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_SPATIAL, mn_dcterms_spatial },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_SUBJECT, mn_dcterms_subject },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_TABLEOFCONTENTS, mn_dcterms_tableofcontents },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_TEMPORAL, mn_dcterms_temporal },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_TITLE, mn_dcterms_title },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_TYPE, mn_dcterms_type },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DCTERMS_VALID, mn_dcterms_valid },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DESIGNER, mn_designer },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DETECTIFY_VERIFICATION, mn_detectify_verification },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_DIR_CONTENT_POINTER, mn_dir_content_pointer },
   { { HTML_JUL07 }, { HTML_JUN08 }, "dns", mn_dns },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ENTITY, mn_entity },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_EXPIRES, mn_expires },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FB_ADMINS, mn_fb_admins },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FB_PAGE_ID, mn_fb_page_id },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FDSE_DESCRIPTION, mn_fdse_description },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FDSE_INDEX_AS, mn_fdse_index_as },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FDSE_KEYWORDS, mn_fdse_keywords },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FDSE_REFRESH, mn_fdse_refresh },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FDSE_ROBOTS, mn_fdse_robots },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FORMAT_DETECTION, mn_format_detection },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FORMAT_PRINT, mn_format_print },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_FRAGMENT, mn_fragment },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GCTERMS_TOPICTAXONOMY, mn_gcterms_topictaxonomy },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GEO_A1, mn_geo_a1 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GEO_A2, mn_geo_a2 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GEO_A3, mn_geo_a3 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GEO_COUNTRY, mn_geo_country },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GEO_LMK, mn_geo_lmk },
   { { HTML_2_0 }, { HTML_UNDEF }, MN_GEO_PLACENAME, mn_geo_placename },
   { { HTML_2_0 }, { HTML_UNDEF }, MN_GEO_POSITION, mn_geo_position },
   { { HTML_2_0 }, { HTML_UNDEF }, MN_GEO_REGION, mn_geo_region },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_BATHROOMS, mn_globrix_bathrooms },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_BEDROOMS, mn_globrix_bedrooms },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_CONDITION, mn_globrix_condition },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_FEATURES, mn_globrix_features },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_INSTRUCTION, mn_globrix_instruction },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_LATITUDE, mn_globrix_latitude },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_LONGITUDE, mn_globrix_longitude },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_OUTSIDESPACE, mn_globrix_outsidespace },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_PARKING, mn_globrix_parking },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_PERIOD, mn_globrix_period },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_POA, mn_globrix_poa },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_POSTCODE, mn_globrix_postcode },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_PRICE, mn_globrix_price },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_PRICEPROXIMITY, mn_globrix_priceproximity },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_TENURE, mn_globrix_tenure },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_TYPE, mn_globrix_type },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GLOBRIX_UNDEROFFER, mn_globrix_underoffer },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GM_GPX_V, mn_gm_gpx_v },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GO_IMPORT, mn_go_import },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GOOGLE, mn_google },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GOOGLE_PLAY_APP, mn_google_play_app },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GOOGLE_SITE_VERIFICATION, mn_google_site_verification },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GOOGLE_TRANSLATE_CUSTOMIZATION, mn_google_translate_customization },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_GWT_PROPERTY, mn_gwt_property },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_HANDHELDFRIENDLY, mn_handheldfriendly },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ICAS_DATETIME, mn_icas_datetime },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ICAS_DATETIME_ABBR, mn_icas_datetime_abbr },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ICAS_DATETIME_DAY, mn_icas_datetime_day },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ICAS_DATETIME_LONG, mn_icas_datetime_long },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ICBM, mn_icbm },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ITEMSPERPAGE, mn_itemsperpage },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_KEYWORDS_NOT, mn_keywords_not },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_META_DATE, mn_meta_date },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MICROTIP, mn_microtip },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MOBILE_AGENT, mn_mobile_agent },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MOBILE_WEB_APP_CAPABLE, mn_mobile_web_app_capable },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MOBILEOPTIMIZED, mn_mobileoptimized },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_TILECOLOR, mn_msapplication_tilecolor },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_TILEIMAGE, mn_msapplication_tileimage },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_CONFIG, mn_msapplication_config },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_NAVBUTTON_COLOR, mn_msapplication_navbutton_color },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_NOTIFICATION, mn_msapplication_notification },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_SQUARE150X150LOGO, mn_msapplication_square150x150logo },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_SQUARE310X310LOGO, mn_msapplication_square310x310logo },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_SQUARE70X70LOGO, mn_msapplication_square70x70logo },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_STARTURL, mn_msapplication_starturl },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_TAP_HIGHLIGHT, mn_msapplication_tap_highlight },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_TASK, mn_msapplication_task },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_TOOLTIP, mn_msapplication_tooltip },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_WIDE310X150LOGO, mn_msapplication_wide310x150logo },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSAPPLICATION_WINDOW, mn_msapplication_window },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_MSVALIDATE_01, mn_msvalidate_01 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_NEXTGEN, mn_nextgen },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_NIBBLER_SITE_VERIFICATION, mn_nibbler_site_verification },
   { { HTML_2_0 }, { HTML_UNDEF }, MN_NO_EMAIL_COLLECTION, mn_no_email_collection },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_NONFICTION, mn_nonfiction },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_NORTON_SAFEWEB_SITE_VERIFICATION, mn_norton_safeweb_site_verification },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_DESCRIPTION, mn_og_description },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_IMAGE, mn_og_image },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_LOCALE, mn_og_locale },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_SITE_NAME, mn_og_site_name },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_TITLE, mn_og_title },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_TYPE, mn_og_type },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_URL, mn_og_url },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ORIGIN, mn_origin },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_ORIGIN_TRIALS, mn_origin_trials },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_P_DOMAIN_VERIFY, mn_p_domain_verify },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_PAGE_VERSION, mn_page_version },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_PINGDOM, mn_pingdom },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_PINTEREST, mn_pinterest },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_PRISM_ALTERNATETITLE, mn_prism_alternatetitle },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_PRO, mn_pro },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_PRO_AUTH, mn_pro_auth },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_PRO_AUTH_FIELD, mn_pro_auth_field },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_PRO_AUTH_FRAGMENT, mn_pro_auth_fragment },
   { { HTML_2_0 }, { HTML_UNDEF }, MN_RATING, mn_rating },
   { { HTML_JUL16 }, { HTML_UNDEF }, MN_REFERRER, mn_referrer },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_RESOLUTIONS, mn_resolutions },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_REVIEW_DATE, mn_review_date },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_REVISION, mn_revision },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_REVISIT_AFTER, mn_revisit_after },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_RIGHTS, mn_rights },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_RIGHTS_STANDARD, mn_rights_standard },
   { { HTML_2_0 }, { HTML_UNDEF }, MN_ROBOTS, mn_robots },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_RPUPLUGIN, mn_rpuplugin },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_RQID, mn_rqid },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_ANALYTICS, mn_shareaholic_analytics },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_ARTICLE_AUTHOR, mn_shareaholic_article_author },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_ARTICLE_AUTHOR_NAME, mn_shareaholic_article_author_name },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_ARTICLE_MODIFIED_TIME, mn_shareaholic_article_modified_time },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_ARTICLE_PUBLISHED_TIME, mn_shareaholic_article_published_time },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_ARTICLE_VISIBILITY, mn_shareaholic_article_visibility },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_DRUPAL_VERSION, mn_shareaholic_drupal_version },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_IMAGE, mn_shareaholic_image },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_KEYWORDS, mn_shareaholic_keywords },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_LANGUAGE, mn_shareaholic_language },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_OUTSTREAMADS, mn_shareaholic_outstreamads },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_SHAREABLE_PAGE, mn_shareaholic_shareable_page },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_SITE_ID, mn_shareaholic_site_id },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_SITE_NAME, mn_shareaholic_site_name },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_URL, mn_shareaholic_url },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SHAREAHOLIC_WP_VERSION, mn_shareaholic_wp_version },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SIGNET_AUTHORS, mn_signet_authors },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SIGNET_LINKS, mn_signet_links },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SKYPE_TOOLBAR, mn_skype_toolbar },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_STARTINDEX, mn_startindex },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_STARTVER, mn_startver },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SUBJECT_DATETIME, mn_subject_datetime },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_SUBJECT_SYSTEM, mn_subject_system },
   { { HTML_JUL16 }, { HTML_UNDEF }, MN_THEME_COLOUR, mn_theme_colour },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_THUMBNAIL, mn_thumbnail },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TOPPER, mn_topper },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TOPPER_MAJOR, mn_topper_major },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TOPPER_MINOR, mn_topper_minor },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TOTALRESULTS, mn_totalresults },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TRANSLATOR, mn_translator },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_APP_COUNTRY, mn_twitter_app_country },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_APP_ID_GOOGLEPLAY, mn_twitter_app_id_googleplay },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_APP_ID_IPAD, mn_twitter_app_id_ipad },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_APP_ID_IPHONE, mn_twitter_app_id_iphone },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_APP_NAME_GOOGLEPLAY, mn_twitter_app_name_googleplay },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_APP_NAME_IPAD, mn_twitter_app_name_ipad },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_APP_NAME_IPHONE, mn_twitter_app_name_iphone },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_APP_URL_GOOGLEPLAY, mn_twitter_app_url_googleplay },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_APP_URL_IPAD, mn_twitter_app_url_ipad },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_APP_URL_IPHONE, mn_twitter_app_url_iphone },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_CARD, mn_twitter_card },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_CREATOR, mn_twitter_creator },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_CREATOR_ID, mn_twitter_creator_id },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_DATA1, mn_twitter_data1 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_DATA2, mn_twitter_data2 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_DESCRIPTION, mn_twitter_description },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_DOMAIN, mn_twitter_domain },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_IMAGE, mn_twitter_image },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_IMAGE0, mn_twitter_image0 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_IMAGE1, mn_twitter_image1 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_IMAGE2, mn_twitter_image2 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_IMAGE3, mn_twitter_image3 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_IMAGE_HEIGHT, mn_twitter_image_height },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_IMAGE_SRC, mn_twitter_image_src },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_IMAGE_WIDTH, mn_twitter_image_width },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_LABEL1, mn_twitter_label1 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_LABEL2, mn_twitter_label2 },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_PLAYER, mn_twitter_player },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_PLAYER_HEIGHT, mn_twitter_player_height },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_PLAYER_STREAM, mn_twitter_player_stream },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_PLAYER_STREAM_CONTENT_TYPE, mn_twitter_player_stream_content_type },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_PLAYER_WIDTH, mn_twitter_player_width },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_SITE, mn_twitter_site },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_SITE_ID, mn_twitter_site_id },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_TITLE, mn_twitter_title },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TWITTER_URL, mn_twitter_url },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_TYPEMETAL_FORMATPREFS, mn_typemetal_formatprefs },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_VERIFY_V1, mn_verify_v1 },
   { { HTML_2_0 }, { HTML_UNDEF }, MN_VERSION, mn_version },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_VFB_VERSION, mn_vfb_version },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_VIEWPORT, mn_viewport },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WEB_AUTHOR, mn_web_author },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WITGET, mn_witget },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WOT_VERIFICATION, mn_wot_verification },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WT_AC, mn_wt_ac },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WT_AD, mn_wt_ad },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WT_CG_N, mn_wt_cg_n },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WT_CG_S, mn_wt_cg_s },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WT_MC_ID, mn_wt_mc_id },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WT_SV, mn_wt_sv },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_WT_TI, mn_wt_ti },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_Y_KEY, mn_y_key },
   { { HTML_4_0 }, { HTML_UNDEF }, MN_YANDEX_VERIFICATION, mn_yandex_verification },

    { { HTML_2_0 }, { HTML_UNDEF }, MN_IDENTIFIER_URL, mn_identifier_url },
    { { HTML_2_0 }, { HTML_UNDEF }, MN_DISTRIBUTION, mn_distribution },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_NOTE, mn_note },
    { { HTML_2_0 }, { HTML_UNDEF }, MN_SUBJECT, mn_subject },
    { { HTML_2_0 }, { HTML_UNDEF }, MN_COPYRIGHT, mn_copyright },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_LANGUAGE, mn_language },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_ID, mn_id },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_PRESDATE, mn_presdate },
    { { HTML_2_0 }, { HTML_UNDEF }, MN_TEMPLATE, mn_template },
    { { HTML_2_0 }, { HTML_UNDEF }, MN_OPERATOR, mn_operator },
    { { HTML_2_0 }, { HTML_UNDEF }, MN_CREATION, mn_creation },
    { { HTML_2_0 }, { HTML_UNDEF }, MN_HOST, mn_host },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_HOST_ADMIN, mn_host_admin },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_CONTACTNAME, mn_contactName },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_CONTACTORGANIZATION, mn_contactOrganization },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_CONTACTSTREETADDRESS1, mn_contactStreetAddress1 },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_CONTACTZIPCODE, mn_contactZipcode },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_CONTACTCITY, mn_contactCity },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_CONTACTCOUNTRY, mn_contactCountry },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_CONTACTPHONENUMBER, mn_contactPhoneNumber },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_CONTACTFAXNUMBER, mn_contactFaxNumber },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_CONTACTNETWORKADDRESS, mn_contactNetworkAddress },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_LINKAGE, mn_linkage },

    { { HTML_2_0 }, { HTML_UNDEF }, MN_ABSTRACT, mn_abstract },
    { { HTML_2_0 }, { HTML_UNDEF }, MN_COVERAGE, mn_coverage },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_EMAIL, mn_og_email },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_PHONE_NUMBER, mn_og_phone_number },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_FAX_NUMBER, mn_og_fax_number },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_LATITUDE, mn_og_latitude },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_LONGITUDE, mn_og_longitude },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_STREET_ADDRESS, mn_og_street_address },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_LOCALITY, mn_og_locality },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_REGION, mn_og_region },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_POSTAL_CODE, mn_og_postal_code },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_OG_COUNTRY_NAME, mn_og_country_name },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_MICROID, mn_microid },
    { { HTML_2_0 }, { HTML_UNDEF }, MN_OWNER, mn_owner },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_REVISED, mn_revised },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_TOPIC, mn_topic },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_SUMMARY, mn_summary },
    { { HTML_4_0 }, { HTML_UNDEF }, MN_TWEETMEME_TITLE, mn_tweetmeme_title },

    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "formatter", mn_formatter }, // front page
    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "vw96.objecttype", mn_vw96_object },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "htdig-keywords", mn_htdig_keywords },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "htdig-noindex", mn_htdig_noindex },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "htdig-email", mn_htdig_email },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "htdig-notification-date", mn_htdig_notification_date },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "htdig-email-subject", mn_htdig_email_subject },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "dc-chem", mn_dc_chem },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "searchbc", mn_searchbc },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "author-corporate", mn_author_corporate },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "author-personal", mn_author_personal },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "bookmark", mn_bookmark },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "publisher-email", mn_publisher_email },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "ekbu", mn_ekbu  },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "ekdoctype", mn_ekdoctype  },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "ekdocowner", mn_ekdocowner  },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "ekdoctech", mn_ekdoctech  },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "ekreviewdate", mn_ekreviewdate  },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "ekarea", mn_ekarea },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "alias", mn_alias },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "cc", mn_cc },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "content-type", mn_content_type },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "sic87", mn_sic87 },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "document", mn_document },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "build", mn_build },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "resource-type", mn_resource_type },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "location", mn_location },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "googlebot", mn_googlebot },

    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "contributor", mn_contributor },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "custodian", mn_custodian },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "custodian_contact", mn_custodian_contact },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "custodian_contact_position", mn_custodian_contact_position },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "east_bounding_coordinate", mn_east_bounding_coordinate },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "north_bounding_coordinate", mn_north_bounding_coordinate },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "relation", mn_relation },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "reply-to", mn_reply_to },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "south_bounding_coordinate", mn_south_bounding_coordinate },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_3_2 }, "west_bounding_coordinate", mn_west_bounding_coordinate },

    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.author", mn_mathdmv_author },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.title", mn_mathdmv_title },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.identifier", mn_mathdmv_identifier },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.pclass", mn_mathdmv_pclass },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.sclass", mn_mathdmv_sclass },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.pacs", mn_mathdmv_pacs },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.cr", mn_mathdmv_cr },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.subject", mn_mathdmv_subject },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.keywords", mn_mathdmv_keywords },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.upload", mn_mathdmv_upload },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.update", mn_mathdmv_update },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.objecttype", mn_mathdmv_objecttype },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.series", mn_mathdmv_series  },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.referencejournals", mn_mathdmv_referencejournals },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.contac", mn_mathdmv_contact },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.abstract", mn_mathdmv_abstract },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_4_01 }, "mathmdc.notes", mn_mathdmv_notes } };

void metaname_init (nitpick& nits)
{   type_master < t_metaname > :: init (nits, metaname_symbol_table, sizeof (metaname_symbol_table) / sizeof (symbol_entry < e_metaname >)); }

void validate_metaname_content (nitpick& nits, const html_version& v, const bool in_head, const e_metaname mn, const ::std::string& content, page& p)
{   bool stats = in_head && context.meta ();
    switch (mn)
    {   case mn_keywords :
            if (stats)
            {   vstr_t s (split_by_charset (content, ","));
                for (auto ss : s)
                {   ::std::string sss (trim_the_lot_off (ss));
                    if (! sss.empty ()) p.mark_meta (mn, sss); } }
            break;
        case mn_author :
        case mn_application_name :
        case mn_generator :
        case mn_colour_scheme :
            if (stats)
                p.mark_meta (mn, content);
            break;
        case mn_referrer :
            {   if (stats) p.mark_meta (mn);
                type_master < t_referrer > ref;
                ref.set_value (nits, v, content);
                if (! ref.good ())
                    nits.pick (nit_theme_colour, ed_jul20, "4.2.5.1 Standard metadata names", es_error, ec_attribute, "When using <META> NAME=\"referrer\", CONTENT should be a referrer policy"); }
            break;
        case mn_theme_colour :
            {   if (stats) p.mark_meta (mn);
                type_master < t_colour > col;
                col.set_value (nits, v, content);
                if (! col.good ())
                    nits.pick (nit_theme_colour, ed_jul20, "4.2.5.1 Standard metadata names", es_error, ec_attribute, "When using <META> NAME=\"theme-color\", CONTENT should be a colour"); }
            break;
        default :
            if (stats) p.mark_meta (mn);
            break; } }
