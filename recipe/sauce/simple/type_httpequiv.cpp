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
#include "utility/quote.h"
#include "webpage/page.h"

struct symbol_entry < html_version, e_httpequiv > httpequiv_symbol_table [] =
{   { { HTML_4_0 }, { HTML_UNDEF },  "context", he_context },

    // sources:
    // mozilla (2020/2022) https://developer.mozilla.org/en-US/docs/Web/HTML/Element/meta
    // standardista (2008) http://www.standardista.com/html5/http-equiv-the-meta-attribute-explained/
    // whatwg (??) (https://html.spec.whatwg.org/multipage/semantics.html#pragma-directives)
    // HTML 4.01 spec
    // RFC 1866
    // Living standard (Jan 2021 and earlier)
    // https://www.iana.org/assignments/message-headers/message-headers.xhtml
    // https://www.iana.org/assignments/http-fields/http-fields.xhtml

    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "A-IM", he_aim },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "ARC-Authentication-Results", he_arc_authentication_results },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "ARC-Message-Signature", he_arc_message_signature },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "ARC-Seal", he_arc_seal },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept", he_accept },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-Additions", he_accept_additions },
    { { HTML_FEB21, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-CH", he_accept_ch },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-CH-Lifetime", he_accept_ch_lifetime },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-Charset", he_accept_charset },
    { { HTML_DEC13, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-Datetime", he_accept_datetime },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-Encoding", he_accept_encoding },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-Features", he_accept_features },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-Language", he_accept_language },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-Patch", he_accept_patch },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-Post", he_accept_post },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Accept-Ranges", he_accept_ranges },
    { { HTML_NOV07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Access-Control", he_access_control },
    { { HTML_DEC14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Access-Control-Allow-Credentials", he_access_control_allow_credentials },
    { { HTML_DEC14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Access-Control-Allow-Headers", he_access_control_allow_headers },
    { { HTML_DEC14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Access-Control-Allow-Methods", he_access_control_allow_methods },
    { { HTML_DEC14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Access-Control-Allow-Origin", he_access_control_allow_origin },
    { { HTML_DEC14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Access-Control-Expose-Headers", he_access_control_expose_headers },
    { { HTML_DEC14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Access-Control-Max-Age", he_access_control_max_age },
    { { HTML_DEC14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Access-Control-Request-Headers", he_access_control_request_headers },
    { { HTML_DEC14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Access-Control-Request-Method", he_access_control_request_method },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Age", he_age },
    { { HTML_2_0 }, { HTML_UNDEF }, "Allow", he_allow },
    { { HTML_AUG15, HV_OUTOFSCOPE }, { HTML_UNDEF }, "ALPN", he_alpn },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Also-Control", he_also_control },
    { { HTML_APR16 }, { HTML_UNDEF }, "Alt-Svc", he_alt_svc },
    { { HTML_APR16, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Alt-Used", he_alt_used },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Alternates", he_alternatives },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Alternate-Recipient", he_alternate_recipient },
    { { HTML_JUN22, HV_OUTOFSCOPE }, { HTML_UNDEF }, "AMP-Cache-Transformation", he_amp_cache_transformation },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Apparently-To", he_apparently_to },
    { { HTML_MAR06, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Apply-To-Redirect-Ref", he_apply_to_redirect_ref },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Approved", he_approved },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Archive", he_archive },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Archived-At", he_archived_at },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Article-Names", he_article_names },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Article-Updates", he_article_updates },
    { { HTML_JAN17, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Authentication-Control", he_authentication_control },
    { { HTML_JAN15, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Authentication-Info", he_authentication_info },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Authentication-Results", he_authentication_results },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Author", he_author },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Authorization", he_authorisation },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Auto-Submitted", he_auto_submitted },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Autoforwarded", he_autoforwarded },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Autosubmitted", he_autosubmitted },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Base", he_base },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Bcc", he_bcc },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Body", he_body },
    { { HTML_2_0 }, { HTML_UNDEF }, "Cache-Control", he_cache_control },
    { { HTML_JUN22, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cache-Status", he_cache_status },
    { { HTML_JUN19, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cal-Managed-ID", he_cal_managed_id },
    { { HTML_MAR16, HV_OUTOFSCOPE }, { HTML_UNDEF }, "CalDAV-Timezones", he_caldav_timezones },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cancel-Key", he_cancel_key },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cancel-Lock", he_cancel_lock },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cc", he_cc },
    { { HTML_JUN22, HV_OUTOFSCOPE }, { HTML_UNDEF }, "CDN-Cache-Control", he_cdn_cache_control },
    { { HTML_APR19, HV_OUTOFSCOPE }, { HTML_UNDEF }, "CDN-Loop", he_cdn_loop },
    { { HTML_4_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "C-Ext", he_c_ext },
    { { HTML_MAR20, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cert-Not-After", he_cert_not_after },
    { { HTML_MAR20, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cert-Not-Before", he_cert_not_before },
    { { HTML_AUG15, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Clear-Site-Data", he_clear_site_data },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Close", he_close },
    { { HTML_4_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "C-Man", he_c_man },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Comments", he_comments },
    { { HTML_SEP21, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Configuration-Context", he_configuration_context },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Connection", he_connection },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-Alternative", he_content_alternative },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-Base", he_content_base },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-DPR", he_content_dpr },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-Description", he_content_description },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_UNDEF }, "Content-Disposition", he_content_disposition },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-Duration", he_content_duration },
    { { HTML_2_0 }, { HTML_UNDEF }, "Content-Encoding", he_content_encoding },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-features", he_content_features },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-ID", he_content_id },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-Identifier", he_content_identifier },
    { { HTML_2_0 }, { HTML_UNDEF }, "Content-Language", he_content_language },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-Length", he_content_length },
    { { HTML_2_0 }, { HTML_UNDEF }, "Content-Location", he_content_location },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-MD5", he_content_md5 },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-Range", he_content_range },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-Return", he_content_return },
    { { HTML_4_0, 0, HE_BESPOKE }, { HTML_UNDEF }, "Content-Script-Type", he_content_script_type },
    { { CSP_1 }, { HTML_UNDEF }, "Content-Security-Policy", he_content_security_policy },
    { { CSP_1 }, { HTML_UNDEF }, "Content-Security-Policy-Report-Only", he_content_security_policy_report_only },
    { { HTML_4_0, 0, HE_BESPOKE }, { HTML_UNDEF }, "Content-Style-Type", he_content_style_type },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-Transfer-Encoding", he_content_transfer_encoding },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Content-Translation-Type", he_content_translation_type },
    { { HTML_2_0 }, { HTML_UNDEF }, "Content-Type", he_content_type },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_UNDEF }, "Content-Version", he_content_version },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Control", he_control },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Conversion", he_conversion },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Conversion-With-Loss", he_conversion_with_loss },
    { { HTML_2_0 }, { HTML_UNDEF }, "Cookie", he_cookie },
    { { HTML_4_0, HV_DINOSAUR }, { HTML_UNDEF }, "Cookie2", he_cookie2 },
    { { HTML_4_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "C-Opt", he_c_opt },
    { { HTML_4_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "C-PEP", he_c_pep },
    { { HTML_4_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "C-PEP-Info", he_c_pep_info },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cross-Origin-Embedder-Policy", he_cross_origin_embedder_policy },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cross-Origin-Embedder-Policy-Report-Only", he_cross_origin_embedder_policy_report_only },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cross-Origin-Opener-Policy", he_cross_origin_opener_policy },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Cross-Origin-Opener-Policy-Report-Only", he_cross_origin_opener_policy_report_only },
    { { HTML_JAN15 }, { HTML_UNDEF }, "Cross-Origin-Resource-Policy", he_cross_origin_resource_policy },
    { { HTML_NOV08, HV_OUTOFSCOPE }, { HTML_UNDEF }, "DASL", he_dasl },
    { { HTML_2_0 }, { HTML_UNDEF }, "Date", he_date },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Date-Received", he_date_received },
    { { HTML_JUN07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "DAV", he_dav },
    { { HTML_4_01, HV_DINOSAUR }, { HTML_UNDEF }, "Default-Style", he_default_style },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Deferred-Delivery", he_deferred_delivery },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Delivered-To", he_delivered_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Delivery-Date", he_delivery_date },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Delta-Base", he_delta_base },
    { { HTML_JUN07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Depth", he_depth },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Derived-From", he_derived_from },
    { { HTML_JUN07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Destination", he_destination },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Device-Memory", he_device_memory },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Differential-ID", he_differential_id },
    { { HTML_4_01, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Digest", he_digest },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Discarded-X400-IPMS-Extensions", he_discarded_x400_ipms_extensions },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Discarded-X400-MTS-Extensions", he_discarded_x400_mts_extensions },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Disclose-Recipients", he_disclose_recipients },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Disposition-Notification-Options", he_disposition_notification_options },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Disposition-Notification-To", he_disposition_notification_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Distribution", he_distribution },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "DKIM-Signature", he_dkim_signature },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "DL-Expansion-History", he_dl_expansion_history },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "DNT", he_dnt },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Bcc", he_downgraded_bcc },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Cc", he_downgraded_cc },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Disposition-Notification-To", he_downgraded_disposition_notification_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Final-Recipient", he_downgraded_final_recipient },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-From", he_downgraded_from },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-In-Reply-To", he_downgraded_in_reply_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Mail-From", he_downgraded_mail_from },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Message-Id", he_downgraded_message_id },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Original-Recipient", he_downgraded_original_recipient },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Rcpt-To", he_downgraded_rcpt_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-References", he_downgraded_references },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Reply-To", he_downgraded_reply_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Resent-Bcc", he_downgraded_resent_bcc },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Resent-Cc", he_downgraded_resent_cc },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Resent-From", he_downgraded_resent_from },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Resent-Reply-To", he_downgraded_resent_reply_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Resent-Sender", he_downgraded_resent_sender },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Resent-To", he_downgraded_resent_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Return-Path", he_downgraded_return_path },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-Sender", he_downgraded_sender },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downgraded-To", he_downgraded_to },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Downlink", he_downlink },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "DPR", he_dpr },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Early-Data", he_early_data },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "ECT", he_ect },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "EDIINT-Features", he_ediint_features },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Eesst-Version", he_eesst_version },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Encoding", he_encoding },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Encrypted", he_encrypted },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Errors-To", he_errors_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "ETag", he_etag },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Expect", he_expect },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Expect-CT", he_expect_ct },
    { { HTML_2_0 }, { HTML_UNDEF }, "Expires", he_expires },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Expiry-Date", he_expiry_date },
    { { HTML_2_0, 0, HE_BESPOKE }, { HTML_UNDEF }, "Ext", he_ext },
    { { HTML_2_0, 0, HE_BESPOKE }, { HTML_UNDEF }, "Ext-Cache", he_ext_cache },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Feature-Policy", he_feature_policy },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Followup-To", he_followup_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Form-Sub", he_form_sub },
    { { HTML_JUN14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Forwarded", he_forwarded },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "From", he_from },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Generate-Delivery-Report", he_generate_delivery_report },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Get-Profile", he_get_profile },
    { { HTML_MAR15, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Hobareg", he_hobareg },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Host", he_host },
    { { HTML_MAY15, HV_DINOSAUR }, { HTML_UNDEF }, "HTTP2-Settings", he_http2_settings },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Human", he_human },
    { { HTML_JUN07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "If", he_if },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "If-Match", he_if_match },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "If-Modified-Since", he_if_modified_since },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "If-None-Match", he_if_none_match },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "If-Range", he_if_range },
    { { HTML_JUN12, HV_OUTOFSCOPE }, { HTML_UNDEF }, "If-Schedule-Tag-Match", he_if_schedule_tag_match },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "If-Unmodified-Since", he_if_unmodified_since },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "IM", he_im },
    { { HTML_JAN05, 0, HE_BESPOKE }, { HTML_UNDEF }, "Imagetoolbar", he_imagetoolbar },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Importance", he_importance },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "In-Reply-To", he_in_reply_to },
    { { HTML_OCT18, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Include-Referred-Token-Binding-ID", he_include_referred_token_binding_id },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Incomplete-Copy", he_incomplete_copy },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Injection-Date", he_injection_date },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Injection-Info", he_injection_info },
    { { HTML_APR20, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Isolation", he_isolation },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Jabber-ID", he_jabber_id },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Keep-Alive", he_keep_alive },
    { { HTML_2_0 }, { HTML_3_0 }, "Keywords", he_keywords },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Label", he_label },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Language", he_language },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Large-Allocation", he_large_allocation },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Last-Event-ID", he_last_event_id },
    { { HTML_2_0 }, { HTML_UNDEF }, "Last-Modified", he_last_modified },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Latest-Delivery-Time", he_latest_delivery_time },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Lines", he_lines },
    { { HTML_NOV17 }, { HTML_UNDEF }, "Link", he_link },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "List-Archive", he_list_archive },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "List-Help", he_list_help },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "List-ID", he_list_id },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "List-Owner", he_list_owner },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "List-Post", he_list_post },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "List-Subscribe", he_list_subscribe },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "List-Unsubscribe", he_list_unsubscribe },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "List-Unsubscribe-Post", he_list_unsubscribe_post },
    { { HTML_2_0 }, { HTML_UNDEF }, "Location", he_location },
    { { HTML_JUN07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Lock-Token", he_lock_token },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Man", he_man },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Max-Forwards", he_max_forwards },
    { { HTML_DEC13, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Memento-Datetime", he_memento_datetime },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Message-Context", he_message_context },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Message-ID", he_message_id },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Message-Type", he_message_type },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Meter", he_meter },
    { { HTML_NOV07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Method-Check", he_method_check },
    { { HTML_NOV07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Method-Check-Expires", he_method_check_expires },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MIME-Version", he_mime_version },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Acp127-Message-Identifier", he_mmhs_acp127_message_identifier },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Authorizing-Users", he_mmhs_authorising_users },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Codress-Message-Indicator", he_mmhs_codress_message_indicator },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Copy-Precedence", he_mmhs_copy_precedence },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Exempted-Address", he_mmhs_exempted_address },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Extended-Authorisation-Info", he_mmhs_extended_authorisation_info },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Handling-Instructions", he_mmhs_handling_instructions },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Message-Instructions", he_mmhs_message_instructions },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Message-Type", he_mmhs_message_type },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Originator-PLAD", he_mmhs_originator_plad },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Originator-Reference", he_mmhs_originator_reference },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Other-Recipients-Indicator-CC", he_mmhs_other_recipients_indicator_cc },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Other-Recipients-Indicator-To", he_mmhs_other_recipients_indicator_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Primary-Precedence", he_mmhs_primary_precedence },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MMHS-Subject-Indicator-Codes", he_mmhs_subject_indicator_codes },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "MT-Priority", he_mt_priority },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Negotiate", he_negotiate },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "NEL", he_nel },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Newsgroups", he_newsgroups },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "NNTP-Posting-Date", he_nntp_posting_date },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "NNTP-Posting-Host", he_nntp_posting_host },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Obsoletes", he_obsoletes },
    { { HTML_JUN19, HV_OUTOFSCOPE }, { HTML_UNDEF }, "OData-EntityId", he_odata_entityid },
    { { HTML_JUN19, HV_OUTOFSCOPE }, { HTML_UNDEF }, "OData-Isolation", he_odata_isolation },
    { { HTML_JUN19, HV_OUTOFSCOPE }, { HTML_UNDEF }, "OData-MaxVersion", he_odata_maxversion },
    { { HTML_JUN19, HV_OUTOFSCOPE }, { HTML_UNDEF }, "OData-Version", he_odata_version },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Opt", he_opt },
    { { HTML_JAN17, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Optional-WWW-Authenticate", he_optional_www_authenticate },
    { { HTML_4_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Ordering-Type", he_ordering_type },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Organization", he_organisation },
    { { HTML_JAN15 }, { HTML_UNDEF }, "Origin", he_origin },
    { { HTML_JAN15, HV_OUTOFSCOPE  }, { HTML_UNDEF }, "Origin-Agent-Cluster", he_origin_agent_cluster },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Original-Encoded-Information-Types", he_original_encoded_information_types },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Original-From", he_original_from },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Original-Message-ID", he_original_message_id },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Original-Recipient", he_original_recipient },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Original-Sender", he_original_sender },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Original-Subject", he_original_subject },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Originator-Return-Address", he_originator_return_address },
    { { HTML_JUL19, HV_OUTOFSCOPE }, { HTML_UNDEF }, "OSCORE", he_oscore },
    { { HTML_AUG21, HV_OUTOFSCOPE }, { HTML_UNDEF }, "OSLC-Core-Version", he_oslc_core_version },
    { { HTML_JUN07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Overwrite", he_overwrite },
    { { HTML_4_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "P3P", he_p3p },
    { { HTML_3_2, 0, HE_BESPOKE }, { HTML_UNDEF }, "Page-Enter", he_page_enter },
    { { HTML_3_2, 0, HE_BESPOKE }, { HTML_UNDEF }, "Page-Exit", he_page_exit },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Path", he_path },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "PEP", he_pep },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Pep-Info", he_pep_info },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_UNDEF }, "PICS-Label", he_pics_label },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Ping-From", he_ping_from },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Ping-To", he_ping_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Position", he_position },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Posting-Version", he_posting_version },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_UNDEF }, "Pragma", he_pragma },
    { { HTML_JUN14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Prefer", he_prefer },
    { { HTML_JUN14, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Preference-Applied", he_preference_applied },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Prevent-NonDelivery-Report", he_prevent_nondelivery_report },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Priority", he_priority },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Privicon", he_privicon },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Profile-Object", he_profile_object },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Protocol", he_protocol },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Protocol-Info", he_protocol_info },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Protocol-Query", he_protocol_query },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Protocol-Request", he_protocol_request },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Proxy-Authenticate", he_proxy_authenticate },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Proxy-Authenticate-Info", he_proxy_authenticate_info },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Proxy-Authorization", he_proxy_authorisation },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Proxy-Features", he_proxy_features },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Proxy-Instruction", he_proxy_instruction },
    { { HTML_JUN22, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Proxy-Status", he_proxy_status },
    { { HTML_2_0, HV_DINOSAUR }, { HTML_UNDEF }, "Public", he_public },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Public-Key-Pins", he_public_key_pins },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Public-Key-Pins-Report-Only", he_public_key_pins_report_only },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "RTT", he_rtt },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Range", he_range },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Received", he_received },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Received-SPF", he_received_spf },
    { { HTML_MAR06, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Redirect-Ref", he_redirect_ref },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "References", he_references },
    { { HTML_2_0 }, { HTML_UNDEF }, "Referer", he_referrer },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Referer-Root", he_referrer_root },
    { { HTML_JAN15 }, { HTML_UNDEF }, "Referrer-Policy", he_referrer_policy },
    { { HTML_2_0 }, { HTML_UNDEF }, "Refresh", he_refresh },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Relay-Version", he_relay_version },
    { { HTML_JUL20, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Repeatability-Client-ID", he_repeatability_client_id },
    { { HTML_JUL20, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Repeatability-First-Sent", he_repeatability_first_sent },
    { { HTML_JUL20, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Repeatability-Request-ID", he_repeatability_request_id },
    { { HTML_JUL20, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Repeatability-Result", he_repeatability_result },
    { { HTML_MAR19, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Replay-Nonce", he_replay_nonce }, // detestable language
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Reply-By", he_reply_by },
    { { HTML_2_0 }, { HTML_3_0 }, "Reply-To", he_reply_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Require-Recipient-Valid-Since", he_require_recipient_valid_since },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Resent-Bcc", he_resent_bcc },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Resent-Cc", he_resent_cc },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Resent-Date", he_resent_date },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Resent-From", he_resent_from },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Resent-Message-ID", he_resent_message_id },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Resent-Reply-To", he_resent_reply_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Resent-Sender", he_resent_sender },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Resent-To", he_resent_to },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Retry-After", he_retry_after },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Return-Path", he_return_path },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Safe", he_safe },
    { { HTML_JUN12, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Schedule-Reply", he_schedule_reply },
    { { HTML_JUN12, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Schedule-Tag", he_schedule_tag },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Save-Data", he_save_data },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-CH-UA", he_sec_ch_ua },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-CH-UA-Arch", he_sec_ch_ua_arch },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-CH-UA-Bitness", he_sec_ch_ua_bitness },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-CH-UA-Full-Version", he_sec_ch_ua_full_version },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-CH-UA-Full-Version-List", he_sec_ch_ua_full_version_list },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-CH-UA-Mobile", he_sec_ch_ua_mobile },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-CH-UA-Model", he_sec_ch_ua_model },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-CH-UA-Platform", he_sec_ch_ua_platform },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-CH-UA-Platform-Version", he_sec_ch_ua_platform_version },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-Fetch-Dest", he_sec_fetch_dest },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-Fetch-Mode", he_sec_fetch_mode },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-Fetch-Site", he_sec_fetch_site },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-Fetch-User", he_sec_fetch_user },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-GPC", he_sec_gpc },
    { { HTML_DEC11, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-WebSocket-Accept", he_sec_websocket_accept },
    { { HTML_DEC11, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-WebSocket-Extensions", he_sec_websocket_extensions },
    { { HTML_DEC11, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-WebSocket-Key", he_sec_websocket_key },
    { { HTML_DEC11, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-WebSocket-Protocol", he_sec_websocket_protocol },
    { { HTML_DEC11, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sec-WebSocket-Version", he_sec_websocket_version },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Security-Scheme", he_security_scheme },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "See-Also", he_see_also },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sender", he_sender },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sensitivity", he_sensitivity },
    { { HTML_2_0 }, { HTML_UNDEF }, "Server", he_server },
    { { HTML_APR21, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Server-Timing", he_server_timing },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Service-Worker-Navigation-Preload", he_service_worker_navigation_preload },
    { { HTML_2_0 }, { HTML_5_2 }, "Set-Cookie", he_set_cookie },
    { { HTML_4_0, HV_DINOSAUR }, { HTML_UNDEF }, "Set-Cookie2", he_set_cookie2 },
    { { HTML_4_0, HV_DINOSAUR }, { HTML_UNDEF }, "SetProfile", he_setprofile },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "SIO-Label", he_sio_label },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "SIO-Label-History", he_sio_label_history },
    { { HTML_3_2, 0, HE_BESPOKE }, { HTML_UNDEF }, "Site-Enter", he_site_enter },
    { { HTML_3_2, 0, HE_BESPOKE }, { HTML_UNDEF }, "Site-Exit", he_site_exit },
    { { HTML_OCT07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "SLUG", he_slug },
    { { HTML_4_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "SoapAction", he_soapaction },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Solicitation", he_solicitation },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "SourceMap", he_sourcemap },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Status-URI", he_status_uri },
    { { HTML_NOV12, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Strict-Transport-Security", he_strict_transport_security },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Subject", he_subject },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Summary", he_summary },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Sunset", he_sunset },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Supersedes", he_supersedes },
    { { HTML_4_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Surrogate-Capability", he_surrogate_capability },
    { { HTML_4_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Surrogate-Control", he_surrogate_control },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "TCN", he_tcn },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "TE", he_te },
    { { HTML_JUN07, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Timeout", he_timeout },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Timing-Allow-Origin", he_timing_allow_origin },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Tk", he_tk },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "TLS-Report-Domain", he_tls_report_domain },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "TLS-Report-Submitter", he_tls_report_submitter },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "TLS-Required", he_tls_required },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "To", he_to },
    { { HTML_DEC16, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Topic", he_topic },
    { { HTML_NOV21, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Traceparent", he_traceparent },
    { { HTML_NOV21, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Tracestate", he_tracestate },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Trailer", he_trailer },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Transfer-Encoding", he_transfer_encoding },
    { { HTML_DEC16, HV_OUTOFSCOPE }, { HTML_UNDEF }, "TTL", he_ttl },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Upgrade", he_upgrade },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Upgrade-Insecure-Requests", he_upgrade_insecure_requests },
    { { HTML_DEC16, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Urgency", he_urgency },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "URI", he_uri },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "User-Agent", he_user_agent },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Variant-Vary", he_variant_vary },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_5_2 }, "Vary", he_vary },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "VBR-Info", he_vbr_info },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Via", he_via },
    { { HTML_JAN05, HV_DINOSAUR, HE_BESPOKE }, { HTML_UNDEF }, "Viewport-Width", he_viewport_width },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Want-Digest", he_want_digest },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Warning", he_warning },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Width", he_width },
    { { HTML_4_0, 0, HE_BESPOKE }, { HTML_UNDEF }, "Window-Target", he_window_target },
    { { HTML_JAN05 }, { HTML_UNDEF }, "WWW-Authenticate", he_www_authenticate },
    { { HTML_2_0, 0, HE_BESPOKE }, { HTML_UNDEF }, "X-Archived-At", he_x_archived_at },
    { { HTML_2_0, 0, 0, H2_CLACKS,  }, { HTML_UNDEF }, "X-Clacks-Overhead", he_x_clacks_overhead },
    { { HTML_JAN11 }, { HTML_AUG13 }, "X-Content-Security-Policy", he_x_content_security_policy },
    { { HTML_JAN15 }, { HTML_UNDEF }, "X-Content-Type-Options", he_x_content_type_options },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-DNS-Prefetch-Control", he_x_dns_prefetch_control },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-Forwarded-For", he_x_forwarded_for },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-Forwarded-Host", he_x_forwarded_host },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-Forwarded-Proto", he_x_forwarded_proto },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-Frame-Options", he_x_frame_options },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-Mittente", he_x_mittente },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-PGP-Sig", he_x_pgp_sig },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-Ricevuta", he_x_ricevuta },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-Riferimento-Message-ID", he_x_riferimento_message_id },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-TipoRicevuta", he_x_tiporicevuta },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-Trasporto", he_x_trasporto },
    { { HTML_JAN05, 0, HE_BESPOKE }, { HTML_UNDEF }, "X-UA-Compatible", he_x_ua_compatible },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-VerificaSicurezza", he_x_verificasicurezza },
    { { HTML_JAN11, 0, HE_BESPOKE }, { HTML_FEB13 }, "X-Webkit-CSP", he_webkit_csp },
    { { HTML_JAN05, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X-XSS-Protection", he_x_xss_protection },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X400-Content-Identifier", he_x400_content_identifier },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X400-Content-Return", he_x400_content_return },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X400-Content-Type", he_x400_content_type },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X400-MTS-Identifier", he_x400_mts_identifier },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X400-Originator", he_x400_originator },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X400-Received", he_x400_received },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X400-Recipients", he_x400_recipients },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "X400-Trace", he_x400_trace },
    { { HTML_2_0, HV_OUTOFSCOPE }, { HTML_UNDEF }, "Xref", he_xref } };

void httpequiv_init (nitpick& nits)
{   type_master < t_httpequiv > :: init (nits, httpequiv_symbol_table, sizeof (httpequiv_symbol_table) / sizeof (symbol_entry < html_version, e_httpequiv >)); }

template < e_type TYPE > ::std::string validate_he_content (nitpick& nits, const html_version& v, const ::std::string& content, page& )
{   type_master < TYPE > t;
    t.set_value (nits, v, content);
    if (! t.good ()) return ::std::string ();
    return t.get_string (); }

template < > ::std::string validate_he_content < t_content_type > (nitpick& nits, const html_version& v, const ::std::string& content, page& p)
{   type_master < t_content_type > t;
    t.set_value (nits, v, content);
    if (! t.good ()) return ::std::string ();
    ::std::string cs (t.get_charset ());
    p.charset (nits, v, cs);
    return t.get_string (); }

template < > ::std::string validate_he_content < t_lang > (nitpick& nits, const html_version& v, const ::std::string& content, page& p)
{   type_master < t_lang > t;
    t.set_value (nits, v, content);
    if (! t.good ()) return ::std::string ();
    ::std::string l (t.get_string ());
    p.lang (nits, v, l);
    return t.get_string (); }

::std::string validate_httpequiv_content (nitpick& nits, const html_version& v, const e_httpequiv he, const ::std::string& content, page& p)
{   p.mark_meta (he);
    switch (he)
    {  case he_alt_svc : break;
        case he_cache_control : return validate_he_content < t_cache > (nits, v, content, p);
        case he_content_encoding : return validate_he_content < t_content_encoding > (nits, v, content, p);
        case he_content_disposition : break;
        case he_content_language : return validate_he_content < t_lang > (nits, v, content, p);
        case he_content_location :
        case he_referrer : return validate_he_content < t_url > (nits, v, content, p);
        case he_content_script_type : return validate_he_content < t_mime > (nits, v, content, p);
        case he_content_security_policy :
        case he_content_security_policy_report_only :
        case he_x_content_security_policy :
        case he_webkit_csp : return validate_he_content < t_csp > (nits, v, content, p);
        case he_cookie :
        case he_set_cookie : return validate_he_content < t_cookies > (nits, v, content, p);
        case he_cookie2 :
        case he_set_cookie2 : break;
        case he_content_style_type : return validate_he_content < t_mime > (nits, v, content, p);
        case he_content_type : return validate_he_content < t_content_type > (nits, v, content, p);
        case he_context : break;
        case he_corp : return validate_he_content < t_corp > (nits, v, content, p);
        case he_date :
        case he_expires :
        case he_last_modified : return validate_he_content < t_datetime > (nits, v, content, p);
        case he_default_style :  return validate_he_content < t_compact > (nits, v, content, p);
        case he_etag :
        case he_www_authenticate : return validate_he_content < t_existential > (nits, v, content, p);
        case he_ext_cache : break;
        case he_imagetoolbar : return validate_he_content < t_yesno > (nits, v, content,p);
        case he_keywords :
        case he_reply_to :
            nits.pick (nit_use_metaname, es_warning, ec_type, "use the NAME attribute, not HTTP-EQUIV, for this information");
            break;
        case he_link :
            if (! content.empty () && (content.find ("rel=") == ::std::string::npos))
                nits.pick (nit_bad_link_pragma, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_error, ec_type, "rel is required");
            return validate_he_content < t_links > (nits, v, content, p);
        case he_location : return validate_he_content < t_location > (nits, v, content, p);
        case he_origin : return validate_he_content < t_root_url > (nits, v, content, p);
        case he_page_enter :
        case he_page_exit :
        case he_site_enter :
        case he_site_exit : return validate_he_content < t_reveal_trans > (nits, v, content, p);
        case he_pics_label : return validate_he_content < t_pics > (nits, v, content, p);
        case he_public : break;
        case he_pragma : return validate_he_content < t_pragma > (nits, v, content, p);
        case he_referrer_policy :
            if (content.empty ()) break;
            return validate_he_content < t_referrer > (nits, v, content, p);
        case he_refresh : return validate_he_content < t_refresh > (nits, v, content, p);
        case he_server : break;
        case he_window_target : break;
        case he_x_content_type_options : return validate_he_content < t_x_content_type_options > (nits, v, content, p);
        case he_x_ua_compatible : return validate_he_content < t_x_ua_compatible > (nits, v, content, p);
        case he_x_clacks_overhead :
            if (! content.empty ()) nits.pick (nit_clacks, es_comment, ec_type, content);
            else nits.pick (nit_clacks, ed_clacks, "A man is not dead while his name is still spoken", es_comment, ec_type, "GNU Sir Terry Pratchett");
            break;
        default : break; }
    return ::std::string (); }

vstr_t split_sides_at_semi (nitpick& nits, const ::std::string& s, const ::std::size_t min_args, const ::std::size_t max_args)
{   vstr_t res (split_by_charset (s, ";"));
    if ((min_args > 0) && (res.size () < min_args))
        nits.pick (nit_missing_content, es_warning, ec_type, "at least ", min_args, " arguments expected in content");
    else if ((max_args > 0) && (res.size () > max_args))
        nits.pick (nit_ignoring_extra_content, es_warning, ec_type, "ignoring excess arguments in content (no more than ", max_args, " expected)");
    return res; }

bool linkarg_set_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   const ::std::string::size_type pos = s.find ('=');
    if ((pos == ::std::string::npos) || (pos == s.length () - 1))
        nits.pick (nit_bad_link_pragma, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_error, ec_type, "missing argument");
    else if (pos == 0)
        nits.pick (nit_bad_link_pragma, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_error, ec_type, "missing keyword");
    else
    {   ::std::string param (s.substr (0, pos));
        ::std::string arg (uq (s.substr (pos+1)));
        if (! test_value < t_linkparam > (nits, v, param))
        {   nits.pick (nit_nocando, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_info, ec_type, quote (param), " is not recognised, so is not verified");
            return true; }
        switch (examine_value < t_linkparam > (nits, v, param))
        {   case lp_rev :
                nits.pick (nit_bad_link_pragma, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_warning, ec_type, "rev is deprecated");
                FALLTHROUGH;
            case lp_rel :
                if (arg.find_first_not_of (ALPHANUMERIC) != ::std::string::npos)
                {   nits.pick (nit_nocando, ed_rfc_8288, "3. Link Serialisation in HTTP Headers", es_info, ec_type, "apologies, but ", PROG, " cannot verify this rel/rev");
                    return true; }
                if (test_value < t_rel > (nits, v, arg)) return true;
                break;
            case lp_anchor :
                if (test_value < t_url > (nits, v, arg)) return true;
                break;
            case lp_hreflang :
                if (test_value < t_lang > (nits, v, arg)) return true;
                break;
            case lp_media :
                if (test_value < t_mql > (nits, v, arg)) return true;
                break;
            case lp_type :
                if (test_value < t_mime > (nits, v, arg)) return true;
                break;
            default : return true; } }
    return false; }

e_status set_cache_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   if (ss.empty ())
        nits.pick (nit_empty, es_error, ec_type, "cache value required");
    else
    {   const ::std::string::size_type pos = ss.find ('=');
        ::std::string arg, s (ss);
        bool booboo = false;
        if (pos != ::std::string::npos)
        {   if ((pos == 0) || (pos == ss.length () - 1)) booboo = true;
            else
            {   arg = ss.substr (pos+1);
                s = ss.substr (0, pos);
                if (arg.find_first_not_of (DENARY) != ::std::string::npos) booboo = true; }
            if (booboo) nits.pick (nit_bad_cache, ed_rfc_7234, "5.2.1. Request Cache-Control Directives", es_error, ec_type, "bad syntax or bad integer"); }
        if (! booboo)
            if (! test_value < t_cachekey > (nits, v, s))
                nits.pick (nit_bad_cache, ed_rfc_7234, "5.2.1. Request Cache-Control Directives", es_error, ec_type, quote (s), " is not a valid cache keyword");
            else switch (examine_value < t_cachekey > (nits, v, s))
            {   case ck_maxage :
                case ck_minfresh :
                    if (arg.empty ())
                    {   nits.pick (nit_bad_cache, ed_rfc_7234, "5.2.1. Request Cache-Control Directives", es_error, ec_type, quote (s), " requires an integer argument (for example, 'max-sausages=5')");
                        booboo = true; }
                    break;
                case ck_nocache :
                case ck_nostore :
                case ck_notransform :
                case ck_onlyifcached :
                    if (! arg.empty ())
                    {   nits.pick (nit_bad_cache, ed_rfc_7234, "5.2.1. Request Cache-Control Directives", es_error, ec_type, quote (s), " takes no argument");
                        booboo = true; }
                    break;
                default : break; }
        if (! booboo) return s_good; }
    return s_invalid; }

e_status set_content_type_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& charset)
{   if (s.empty ()) return s_empty;
    vstr_t sides (split_sides_at_semi (nits, s));
    if (sides.size () > 0)
    {   if (! compare_no_case (sides.at (0), HTML_TYPE))
            nits.pick (nit_text_html_expected, es_error, ec_type, "content type should be '" HTML_TYPE ";charset=...'");
        if (sides.size () == 1)
            nits.pick (nit_charset_missing, es_error, ec_type, "the charset is missing");
        else
        {   ::std::string ss (trim_the_lot_off (sides.at (1)));
            const ::std::string::size_type pos = ss.find ('=');
            if ((pos != ::std::string::npos) && compare_no_case (ss.substr (0, pos), "charset"))
            {   type_master < t_charset > cs;
                ::std::string sss (ss.substr (pos+1));
                cs.set_value (nits, v, sss);
                if (cs.good ())
                {   charset = sss; return s_good; } } } }
    return s_invalid; }

e_status set_csp_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ()) return s_empty;
    vstr_t sides (split_sides_at_semi (nits, s, 1, 0));
    bool res = true;
    for (auto ss : sides)
    {   ::std::string sss (trim_the_lot_off (ss));
        if (! sss.empty ())
        {   vstr_t csp (split_by_space (sss));
            if (csp.size () > 0)
                if (! test_value < t_csp_directive > (nits, v, csp.at (0)))
                    res = false;
                else
                {   const e_csp_directive cd = examine_value < t_csp_directive > (nits, v, csp.at (0));
                    switch (cd)
                    {   case csp_plugin_types :
                            if (! compare_no_case (csp.at (1), QNONE))
                                for (::std::size_t i = 1; i < csp.size (); ++i)
                                    if (! test_value < t_mime > (nits, v, csp.at (i))) res = false;
                            break;
                        case csp_sandbox :
                            for (::std::size_t i = 10; i < csp.size (); ++i)
                                if (! test_value < t_sandbox > (nits, v, csp.at (i))) res = false;
                            break;
                        case csp_frame_ancestors :
                            if (csp.size () < 2)
                                nits.pick (nit_bad_csp_directive, ed_csp, "Content Security Policy Directives", es_error, ec_type, quote (csp.at (0)), " requires arguments");
                            else for (::std::size_t i = 1; i < csp.size (); ++i)
                                if (! test_value < t_csp_ancestor > (nits, v, csp.at (i))) res = false;
                            break;
                        case csp_report_uri :
                            for (::std::size_t i = 10; i < csp.size (); ++i)
                                if (! test_value < t_url > (nits, v, csp.at (i))) res = false;
                            break;
                        case csp_report_to :
                        case csp_block_all_mixed_content :
                        case csp_update_insecure_requests :
                        case csp_require_sri_for :
                            break;
                        default :
                            if (csp.size () < 2)
                                nits.pick (nit_bad_csp_directive, ed_csp, "Content Security Policy Directives", es_error, ec_type, quote (csp.at (0)), " requires arguments");
                            else if ((csp.size () != 2) || ! compare_no_case (csp.at (1), QNONE))
                                for (::std::size_t i = 1; i < csp.size (); ++i)
                                    if (! test_value < t_csp_source > (nits, v, csp.at (i))) res = false; } } } }
    if (res) return s_good;
    return s_invalid; }

e_status set_csp_sauce_value (nitpick& nits, const html_version& v, const ::std::string& ss)
{   if (ss.empty ()) return s_empty;
    ::std::string s (ss);
    const ::std::string::size_type len = s.length ();
    if ((len > 1) && (s.at (0) == '\'') && (s.at (len - 1) == '\''))
    {   if (v >= csp_c2)
        {   s = s.substr (1, len - 2);
            const ::std::string::size_type pos = s.find ('-');
            if (pos != ::std::string::npos)
            {   if ((pos == 5) && compare_no_case (EVIL, s.substr (0, 5)))
                {   if (s.substr (6).find_first_not_of (ALPHABET DENARY "+/-_*") == ::std::string::npos) return s_good;
                    nits.pick (nit_bad_number_once, ed_csp, "Content Security Policy Directives", es_error, ec_attribute, "invalid number once"); }
                else if (pos != 6)
                    nits.pick (nit_bad_csp_source, ed_csp, "Content Security Policy Directives", es_error, ec_attribute, quote (s.substr (0, pos)), " is an unrecognised source");
                else
                {   ::std::string algo (s.substr (0, 6));
                    if (compare_no_case (algo, "sha256") ||
                        compare_no_case (algo, "sha384") ||
                        compare_no_case (algo, "sha512")) return s_good;
                    nits.pick (nit_invalid_algorithm, ed_csp, "Content Security Policy Directives", es_error, ec_attribute, quote (s.substr (0, 6)), " is an unrecognised digest"); } } } }
    else
    if (ss.at (len - 1) == ':')
    {   e_protocol prot;
        if (symbol < html_version, e_protocol > :: parse (nits, v, ss.substr (0, len - 1), prot)) return s_good; }
    else
    {   if (ss.find ('*') != ::std::string::npos) return s_good;
        url u (nits, v, ss, pr_https);
        if (! u.invalid ()) return s_good; }
    return s_invalid; }

e_status set_linkarg_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "value required (", type_name (t_linkarg), ")");
    else if (linkarg_set_value (nits, v, s)) return s_good;
    return s_invalid; }

e_status set_linkitself_value (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (s.empty ())
        nits.pick (nit_bad_link_pragma, es_error, ec_type, "oddly, a link pragma needs a link");
    else if ((s.length () < 3) || (s.at (0) != '<') || (s.at (s.length () -1) != '>'))
        nits.pick (nit_bad_link_pragma, es_error, ec_type, "the URL must be enclosed in angular brackets");
    else if (test_value < t_url > (nits, v, s.substr (1, s.length ()-2))) return s_good;
    return s_invalid; }

e_status set_location_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& val)
{   if (s.empty ()) return s_empty;
    vstr_t sides (split_sides_at_semi (nits, s));
    if (sides.size () > 0)
    {   if (! compare_no_case (sides.at (0), "0"))
            nits.pick (nit_text_html_expected, ed_w3, HTTPS_W3 "/TR/2016/NOTE-WCAG20-TECHS-20161007/F41", es_error, ec_type, "do not use location with any period but zero, to avoid causing some users significant problems");
        if (sides.size () == 1)
            nits.pick (nit_url_empty, es_error, ec_type, "the url is missing");
        else
        {   url u (nits, v, trim_the_lot_off (sides.at (2)));
            if (! u.invalid ()) { val = u.original (); return s_good; } } }
    return s_invalid; }

e_status set_refresh_value (nitpick& nits, const html_version& v, const ::std::string& s, ::std::string& val)
{   if (s.empty ())
        nits.pick (nit_empty, es_error, ec_type, "value required (", type_name (t_refresh), ")");
    else
    {   vstr_t sides (split_sides_at_semi (nits, s, 1));
        if (sides.size () > 0)
        {   if (sides.size () < 2) return s_good;
            if (! compare_no_case (sides.at (0), "0"))
                nits.pick (nit_refresh_zero, ed_w3, HTTPS_W3 "/TR/2016/NOTE-WCAG20-TECHS-20161007/F41", es_error, ec_type, "do not use refresh with any period but zero, to avoid causing some users significant problems");
            const int ulen = 4;
            ::std::string x (trim_the_lot_off (sides.at (1)));
            if (x.length () < 5 || ! compare_no_case (x.substr (0, ulen), "url="))
                nits.pick (nit_url_empty, es_error, ec_type, "the refresh url must be preceded by 'url='");
            else
            {   url u (nits, v, x.substr (ulen));
                if (! u.invalid ())
                {   val = u.original (); return s_good; } } } }
    return s_invalid; }
