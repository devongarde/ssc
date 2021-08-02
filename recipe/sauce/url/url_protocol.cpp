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
#include "url/url_protocol.h"
#include "url/url_schemes.h"

// RFC 3986

struct symbol_entry < html_version, e_protocol > protocol_symbol_table [] =
{   { { HTML_TAGS }, { HTML_UNDEF }, "aaa", pr_aaa },
    { { HTML_TAGS }, { HTML_UNDEF }, "aaas", pr_aaas },
    { { HTML_TAGS }, { HTML_UNDEF }, "about", pr_about },
    { { HTML_TAGS }, { HTML_UNDEF }, "acap", pr_acap },
    { { HTML_TAGS }, { HTML_UNDEF }, "acct", pr_acct },
    { { HTML_TAGS }, { HTML_UNDEF }, "acr", pr_acr },
    { { HTML_TAGS }, { HTML_UNDEF }, "adiumxtra", pr_adiumxtra },
    { { HTML_TAGS }, { HTML_UNDEF }, "admin", pr_admin },
    { { HTML_TAGS }, { HTML_UNDEF }, "afp", pr_afp },
    { { HTML_TAGS }, { HTML_UNDEF }, "afs", pr_afs },
    { { HTML_TAGS }, { HTML_UNDEF }, "aim", pr_aim },
    { { HTML_TAGS }, { HTML_UNDEF }, "apt", pr_apt },
    { { HTML_TAGS }, { HTML_UNDEF }, "app", pr_app },
    { { HTML_TAGS }, { HTML_UNDEF }, "attachment", pr_attachment },
    { { HTML_TAGS }, { HTML_UNDEF }, "aw", pr_aw },
    { { HTML_TAGS }, { HTML_UNDEF }, "amss", pr_amss },
    { { HTML_TAGS }, { HTML_UNDEF }, "barian", pr_barian },
    { { HTML_TAGS }, { HTML_UNDEF }, "beshare", pr_beshare },
    { { HTML_TAGS }, { HTML_UNDEF }, "bitcoin", pr_bitcoin },
    { { HTML_TAGS }, { HTML_UNDEF }, "blob", pr_blob },
    { { HTML_TAGS }, { HTML_UNDEF }, "bolo", pr_bolo },
    { { HTML_TAGS }, { HTML_UNDEF }, "callto", pr_callto },
    { { HTML_TAGS }, { HTML_UNDEF }, "cap", pr_cap },
    { { HTML_TAGS }, { HTML_UNDEF }, "chrome", pr_chrome },
    { { HTML_TAGS }, { HTML_UNDEF }, "chrome-extension", pr_chrome_extension },
    { { HTML_TAGS }, { HTML_UNDEF }, "clsid", pr_clsid },
    { { HTML_TAGS }, { HTML_UNDEF }, "cid", pr_cid },
    { { HTML_TAGS }, { HTML_UNDEF }, "coap", pr_coap },
    { { HTML_TAGS }, { HTML_UNDEF }, "coaps", pr_coaps },
    { { HTML_TAGS }, { HTML_UNDEF }, "com-eventbrite-attendee", pr_com_eventbrite_attendee },
    { { HTML_TAGS }, { HTML_UNDEF }, "content", pr_content },
    { { HTML_TAGS }, { HTML_UNDEF }, "crid", pr_crid },
    { { HTML_TAGS }, { HTML_UNDEF }, "cvs", pr_cvs },
    { { HTML_TAGS }, { HTML_UNDEF }, "dab", pr_dab },
    { { HTML_TAGS }, { HTML_UNDEF }, "data", pr_data },
    { { HTML_TAGS }, { HTML_UNDEF }, "dav", pr_dav },
    { { HTML_TAGS }, { HTML_UNDEF }, "dict", pr_dict },
    { { HTML_TAGS }, { HTML_UNDEF }, "dina-playsingle", pr_dina_playsingle },
    { { HTML_TAGS }, { HTML_UNDEF }, "dina-playcontainer", pr_dina_playcontainer },
    { { HTML_TAGS }, { HTML_UNDEF }, "dns", pr_dns },
    { { HTML_TAGS }, { HTML_UNDEF }, "dntp", pr_dntp },
    { { HTML_TAGS }, { HTML_UNDEF }, "doi", pr_doi },
    { { HTML_TAGS }, { HTML_UNDEF }, "drm", pr_drm },
    { { HTML_TAGS }, { HTML_UNDEF }, "dtn", pr_dtn },
    { { HTML_TAGS }, { HTML_UNDEF }, "dvb", pr_dvb },
    { { HTML_TAGS }, { HTML_UNDEF }, "ed2k", pr_ed2k },
    { { HTML_TAGS }, { HTML_UNDEF }, "example", pr_example },
    { { HTML_TAGS }, { HTML_UNDEF }, "facetime", pr_facetime },
    { { HTML_TAGS }, { HTML_UNDEF }, "fax", pr_fax },
    { { HTML_TAGS }, { HTML_UNDEF }, "feed", pr_feed },
    { { HTML_2_0 }, { HTML_UNDEF }, PR_FILE, pr_file },
    { { HTML_TAGS }, { HTML_UNDEF }, "filesystem", pr_filesystem },
    { { HTML_TAGS }, { HTML_UNDEF }, "finger", pr_finger },
    { { HTML_TAGS }, { HTML_UNDEF }, "fish", pr_fish },
    { { HTML_TAGS }, { HTML_UNDEF }, "fm", pr_fm },
    { { HTML_TAGS }, { HTML_UNDEF }, PR_FTP, pr_ftp },
    { { HTML_4_0 }, { HTML_UNDEF }, PR_FTPS, pr_ftps },
    { { HTML_TAGS }, { HTML_UNDEF }, "gemini", pr_gemini },
    { { HTML_JAN05 }, { HTML_UNDEF }, PR_GEO, pr_geo },
    { { HTML_TAGS }, { HTML_UNDEF }, "gg", pr_gg },
    { { HTML_TAGS }, { HTML_UNDEF }, "git", pr_git },
    { { HTML_TAGS }, { HTML_UNDEF }, "gizmoproject", pr_gizmoproject },
    { { HTML_TAGS }, { HTML_UNDEF }, "go", pr_go },
    { { HTML_TAGS }, { HTML_UNDEF }, "gopher", pr_gopher },
    { { HTML_TAGS }, { HTML_UNDEF }, "gtalk", pr_gtalk },
    { { HTML_TAGS }, { HTML_UNDEF }, "h323", pr_h323 },
    { { HTML_TAGS }, { HTML_UNDEF }, "hcp", pr_hcp },
    { { HTML_TAGS }, { HTML_UNDEF }, PR_HTTP, pr_http },
    { { HTML_3_0 }, { HTML_UNDEF }, PR_HTTPS, pr_https },
    { { HTML_TAGS }, { HTML_UNDEF }, "iax", pr_iax },
    { { HTML_TAGS }, { HTML_UNDEF }, "icap", pr_icap },
    { { HTML_TAGS }, { HTML_UNDEF }, "icon", pr_icon },
    { { HTML_TAGS }, { HTML_UNDEF }, "im", pr_im },
    { { HTML_TAGS }, { HTML_UNDEF }, "imap", pr_imap },
    { { HTML_TAGS }, { HTML_UNDEF }, "info", pr_info },
    { { HTML_TAGS }, { HTML_UNDEF }, "iotdisco", pr_iotdisco },
    { { HTML_TAGS }, { HTML_UNDEF }, "ipn", pr_ipn },
    { { HTML_TAGS }, { HTML_UNDEF }, "ipp", pr_ipp },
    { { HTML_TAGS }, { HTML_UNDEF }, "ipps", pr_ipps },
    { { HTML_TAGS }, { HTML_UNDEF }, "irc", pr_irc },
    { { HTML_TAGS }, { HTML_UNDEF }, "irc6", pr_irc6 },
    { { HTML_TAGS }, { HTML_UNDEF }, "ircs", pr_ircs },
    { { HTML_TAGS }, { HTML_UNDEF }, "iris", pr_iris },
    { { HTML_TAGS }, { HTML_UNDEF }, "iris.beep", pr_iris_beep },
    { { HTML_TAGS }, { HTML_UNDEF }, "iris.xpc", pr_iris_xpc },
    { { HTML_TAGS }, { HTML_UNDEF }, "iris.xpcs", pr_iris_xpcs },
    { { HTML_TAGS }, { HTML_UNDEF }, "iris.lws", pr_iris_lws },
    { { HTML_TAGS }, { HTML_UNDEF }, "itms", pr_itms },
    { { HTML_TAGS }, { HTML_UNDEF }, "jabber", pr_jabber },
    { { HTML_TAGS }, { HTML_UNDEF }, "jar", pr_jar },
    { { HTML_TAGS }, { HTML_UNDEF }, "javascript", pr_javascript },
    { { HTML_TAGS }, { HTML_UNDEF }, "jdbc", pr_jdbc },
    { { HTML_TAGS }, { HTML_UNDEF }, "jms", pr_jms },
    { { HTML_TAGS }, { HTML_UNDEF }, "keyparc", pr_keyparc },
    { { HTML_TAGS }, { HTML_UNDEF }, "lastfm", pr_lastfm },
    { { HTML_3_0 }, { HTML_UNDEF }, PR_LDAP, pr_ldap },
    { { HTML_3_0 }, { HTML_UNDEF }, "ldaps", pr_ldaps },
    { { HTML_TAGS }, { HTML_UNDEF }, "magnet", pr_magnet },
    { { HTML_TAGS }, { HTML_UNDEF }, "mailserver", pr_mailserver },
    { { HTML_TAGS }, { HTML_UNDEF }, PR_MAILTO, pr_mailto },
    { { HTML_TAGS }, { HTML_UNDEF }, "maps", pr_maps },
    { { HTML_TAGS }, { HTML_UNDEF }, "market", pr_market },
    { { HTML_TAGS }, { HTML_UNDEF }, "message", pr_message },
    { { HTML_TAGS }, { HTML_UNDEF }, "mid", pr_mid },
    { { HTML_TAGS }, { HTML_UNDEF }, "mms", pr_mms },
    { { HTML_TAGS }, { HTML_UNDEF }, "modem", pr_modem },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-help", pr_ms_help },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings", pr_ms_settings },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-airplanemode", pr_ms_settings_airplanemode },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-bluetooth", pr_ms_settings_bluetooth },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-camera", pr_ms_settings_camera },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-cellular", pr_ms_settings_cellular },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-cloudstorage", pr_ms_settings_cloudstorage },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-emailandaccounts", pr_ms_settings_emailandaccounts },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-languauge", pr_ms_settings_language },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-location", pr_ms_settings_location },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-lock", pr_ms_settings_lock },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-nfctransactions", pr_ms_settings_nfctransactions },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-notifications", pr_ms_settings_notifications },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-power", pr_ms_settings_power },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-privacy", pr_ms_settings_privacy },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-proximity", pr_ms_settings_proximity },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-screenrotation", pr_ms_settings_screenrotation },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-wifi", pr_ms_settings_wifi },
    { { HTML_TAGS }, { HTML_UNDEF }, "ms-settings-workplace", pr_ms_settings_workplace },
    { { HTML_TAGS }, { HTML_UNDEF }, "msnum", pr_msnum },
    { { HTML_TAGS }, { HTML_UNDEF }, "msrp", pr_msrp },
    { { HTML_TAGS }, { HTML_UNDEF }, "msrps", pr_msrps },
    { { HTML_TAGS }, { HTML_UNDEF }, "mtqp", pr_mtqp },
    { { HTML_TAGS }, { HTML_UNDEF }, "mumble", pr_mumble },
    { { HTML_TAGS }, { HTML_UNDEF }, "mupdate", pr_mupdate },
    { { HTML_TAGS }, { HTML_UNDEF }, "mvn", pr_mvn },
    { { HTML_TAGS }, { HTML_4_01 }, PR_NEWS, pr_news },
    { { HTML_TAGS }, { HTML_UNDEF }, "nfs", pr_nfs },
    { { HTML_TAGS }, { HTML_UNDEF }, "ni", pr_ni },
    { { HTML_TAGS }, { HTML_UNDEF }, "nih", pr_nih },
    { { HTML_TAGS }, { HTML_UNDEF }, "nntp", pr_nntp },
    { { HTML_TAGS }, { HTML_UNDEF }, "notes", pr_notes },
    { { HTML_TAGS }, { HTML_UNDEF }, "ocsp", pr_ocsp },
    { { HTML_TAGS }, { HTML_UNDEF }, "odbc", pr_odbc },
    { { HTML_TAGS }, { HTML_UNDEF }, "oid", pr_oid },
    { { HTML_TAGS }, { HTML_UNDEF }, "opaquelocktoken", pr_opaquelocktoken },
    { { HTML_TAGS }, { HTML_UNDEF }, "openpgp4fpr", pr_openpgp4fpr },
    { { HTML_TAGS }, { HTML_UNDEF }, "pack", pr_pack },
    { { HTML_TAGS }, { HTML_UNDEF }, "palm", pr_palm },
    { { HTML_TAGS }, { HTML_UNDEF }, "paparazzi", pr_paparazzi },
    { { HTML_TAGS }, { HTML_UNDEF }, "payto", pr_payto },
    { { HTML_TAGS }, { HTML_UNDEF }, "pkcs11", pr_pkcs11 },
    { { HTML_TAGS }, { HTML_UNDEF }, "platform", pr_platform },
    { { HTML_TAGS }, { HTML_UNDEF }, "pop", pr_pop },
    { { HTML_TAGS }, { HTML_UNDEF }, "pres", pr_pres },
    { { HTML_TAGS }, { HTML_UNDEF }, "prospero", pr_prospero },
    { { HTML_TAGS }, { HTML_UNDEF }, "proxy", pr_proxy },
    { { HTML_TAGS }, { HTML_UNDEF }, "psyc", pr_psyc },
    { { HTML_TAGS }, { HTML_UNDEF }, "query", pr_query },
    { { HTML_TAGS }, { HTML_UNDEF }, "redis", pr_redis },
    { { HTML_TAGS }, { HTML_UNDEF }, "rediss", pr_rediss },
    { { HTML_TAGS }, { HTML_UNDEF }, "reload", pr_reload },
    { { HTML_TAGS }, { HTML_UNDEF }, "res", pr_res },
    { { HTML_TAGS }, { HTML_UNDEF }, "resource", pr_resource },
    { { HTML_TAGS }, { HTML_UNDEF }, "rmi", pr_rmi },
    { { HTML_TAGS }, { HTML_UNDEF }, "rsync", pr_rsync },
    { { HTML_TAGS }, { HTML_UNDEF }, "rtmfp", pr_rtmfp },
    { { HTML_TAGS }, { HTML_UNDEF }, "rtmp", pr_rtmp },
    { { HTML_SVG12 }, { HTML_UNDEF }, PR_RTSP, pr_rtsp },
    { { HTML_TAGS }, { HTML_UNDEF }, "s3", pr_s3 },
    { { HTML_TAGS }, { HTML_UNDEF }, "secondlife", pr_secondlife },
    { { HTML_TAGS }, { HTML_UNDEF }, "service", pr_service },
    { { HTML_TAGS }, { HTML_UNDEF }, "session", pr_session },
    { { HTML_4_0 }, { HTML_UNDEF }, PR_SFTP, pr_sftp },
    { { HTML_TAGS }, { HTML_UNDEF }, "sgn", pr_sgn },
    { { HTML_TAGS }, { HTML_UNDEF }, "shttp", pr_shttp },
    { { HTML_TAGS }, { HTML_UNDEF }, "sieve", pr_sieve },
    { { HTML_TAGS }, { HTML_UNDEF }, "sip", pr_sip },
    { { HTML_TAGS }, { HTML_UNDEF }, "sips", pr_sips },
    { { HTML_TAGS }, { HTML_UNDEF }, "skype", pr_skype },
    { { HTML_TAGS }, { HTML_UNDEF }, "slack", pr_slack },
    { { HTML_TAGS }, { HTML_UNDEF }, "smb", pr_smb },
    { { HTML_TAGS }, { HTML_UNDEF }, "sms", pr_sms },
    { { HTML_TAGS }, { HTML_UNDEF }, "snews", pr_snews },
    { { HTML_TAGS }, { HTML_UNDEF }, "snmp", pr_snmp },
    { { HTML_TAGS }, { HTML_UNDEF }, "soap.beep", pr_soap_beep },
    { { HTML_TAGS }, { HTML_UNDEF }, "soap.beeps", pr_soap_beeps },
    { { HTML_TAGS }, { HTML_UNDEF }, "soldat", pr_soldat },
    { { HTML_TAGS }, { HTML_UNDEF }, "spotify", pr_spotify },
    { { HTML_4_0 }, { HTML_UNDEF }, PR_SSH, pr_ssh },
    { { HTML_TAGS }, { HTML_UNDEF }, "steam", pr_steam },
    { { HTML_TAGS }, { HTML_UNDEF }, "stratum", pr_stratum },
    { { HTML_TAGS }, { HTML_UNDEF }, "stun", pr_stun },
    { { HTML_TAGS }, { HTML_UNDEF }, "stuns", pr_stuns },
    { { HTML_TAGS }, { HTML_UNDEF }, "snv", pr_snv },
    { { HTML_TAGS }, { HTML_UNDEF }, "tag", pr_tag },
    { { HTML_TAGS }, { HTML_UNDEF }, "teamspeak", pr_teamspeak },
    { { HTML_2_0 }, { HTML_UNDEF }, PR_TEL, pr_tel },
    { { HTML_TAGS }, { HTML_4_01 }, PR_TELNET, pr_telnet },
    { { HTML_TAGS }, { HTML_UNDEF }, "tftp", pr_tftp },
    { { HTML_TAGS }, { HTML_UNDEF }, "things", pr_things },
    { { HTML_TAGS }, { HTML_UNDEF }, "thismessage", pr_thismessage },
    { { HTML_TAGS }, { HTML_UNDEF }, "tn3270", pr_tn3270 },
    { { HTML_TAGS }, { HTML_UNDEF }, "tip", pr_tip },
    { { HTML_TAGS }, { HTML_UNDEF }, "trueconf", pr_trueconf },
    { { HTML_TAGS }, { HTML_UNDEF }, "turn", pr_turn },
    { { HTML_TAGS }, { HTML_UNDEF }, "turns", pr_turns },
    { { HTML_TAGS }, { HTML_UNDEF }, "tv", pr_tv },
    { { HTML_TAGS }, { HTML_UNDEF }, "udp", pr_udp },
    { { HTML_TAGS }, { HTML_UNDEF }, "unreal", pr_unreal },
    { { HTML_TAGS }, { HTML_UNDEF }, PR_URN, pr_urn },
    { { HTML_TAGS }, { HTML_UNDEF }, "ut2004", pr_ut2004 },
    { { HTML_TAGS }, { HTML_UNDEF }, "vemmi", pr_vemmi },
    { { HTML_TAGS }, { HTML_UNDEF }, "ventrilo", pr_ventrilo },
    { { HTML_TAGS }, { HTML_UNDEF }, "videotex", pr_videotex },
    { { HTML_TAGS }, { HTML_UNDEF }, "view-source", pr_view_source },
    { { HTML_TAGS }, { HTML_UNDEF }, "vnc", pr_vnc },
    { { HTML_TAGS }, { HTML_UNDEF }, "wais", pr_wais },
    { { HTML_TAGS }, { HTML_UNDEF }, "webcal", pr_webcal },
    { { HTML_TAGS }, { HTML_UNDEF }, "webplus", pr_webplus },
    { { HTML_TAGS }, { HTML_UNDEF }, "ws", pr_ws },
    { { HTML_TAGS }, { HTML_UNDEF }, "wss", pr_wss },
    { { HTML_TAGS }, { HTML_UNDEF }, "wtai", pr_wtai },
    { { HTML_TAGS }, { HTML_UNDEF }, "wyciwyg", pr_wyciwyg },
    { { HTML_TAGS }, { HTML_UNDEF }, "xcon", pr_xcon },
    { { HTML_TAGS }, { HTML_UNDEF }, "xcon-userid", pr_xcon_userid },
    { { HTML_TAGS }, { HTML_UNDEF }, "xfire", pr_xfire },
    { { HTML_TAGS }, { HTML_UNDEF }, "xmlrpc.beep", pr_xmlrpc_beep },
    { { HTML_TAGS }, { HTML_UNDEF }, "xmlrpc.beeps", pr_xmlrpc_beeps },
    { { HTML_TAGS }, { HTML_UNDEF }, "xmpp", pr_xmpp },
    { { HTML_TAGS }, { HTML_UNDEF }, "xri", pr_xri },
    { { HTML_TAGS }, { HTML_UNDEF }, "ymsgr", pr_ymsgr },
    { { HTML_TAGS }, { HTML_UNDEF }, "z39.50", pr_z39_50 },
    { { HTML_TAGS }, { HTML_UNDEF }, "z39.50r", pr_z39_50r },
    { { HTML_TAGS }, { HTML_UNDEF }, "z39.50s", pr_z39_50s },
    { { HTML_TAGS }, { HTML_UNDEF }, "zoommtg", pr_zoommtg },
    { { HTML_TAGS }, { HTML_UNDEF }, "zoomus", pr_zoomus } };

struct protocol_server
{   e_protocol protocol_;
    e_scheme scheme_; };

protocol_server ps [] =
{   {   pr_other,   pt_rfc3986_ignore },
    { pr_aaa, pt_rfc3986_ignore },
    { pr_aaas, pt_rfc3986_ignore },
    { pr_about, pt_rfc3986_ignore },
    { pr_acap, pt_rfc3986_ignore },
    { pr_acct, pt_rfc3986_ignore },
    { pr_acr, pt_rfc3986_ignore },
    { pr_adiumxtra, pt_rfc3986_ignore },
    { pr_admin, pt_rfc3986_ignore },
    { pr_afp, pt_rfc3986_ignore },
    { pr_afs, pt_rfc3986_ignore },
    { pr_aim, pt_rfc3986_ignore },
    { pr_apt, pt_rfc3986_ignore },
    { pr_app, pt_rfc3986_ignore },
    { pr_attachment, pt_rfc3986_ignore },
    { pr_aw, pt_rfc3986_ignore },
    { pr_amss, pt_rfc3986_ignore },
    { pr_barian, pt_rfc3986_ignore },
    { pr_beshare, pt_rfc3986_ignore },
    { pr_bitcoin, pt_rfc3986_ignore },
    { pr_blob, pt_rfc3986_ignore },
    { pr_bolo, pt_rfc3986_ignore },
    { pr_callto, pt_rfc3986_ignore },
    { pr_cap, pt_rfc3986_ignore },
    { pr_chrome, pt_rfc3986_ignore },
    { pr_chrome_extension, pt_rfc3986_ignore },
    { pr_cid, pt_rfc3986_ignore },
    { pr_clsid, pt_rfc3986_ignore },
    { pr_coap, pt_rfc3986_ignore },
    { pr_coaps, pt_rfc3986_ignore },
    { pr_com_eventbrite_attendee, pt_rfc3986_ignore },
    { pr_content, pt_rfc3986_ignore },
    { pr_crid, pt_rfc3986_ignore },
    { pr_cvs, pt_rfc3986_ignore },
    { pr_dab, pt_rfc3986_ignore },
    { pr_data, pt_rfc3986_ignore },
    { pr_dav, pt_rfc3986_ignore },
    { pr_dict, pt_rfc3986_ignore },
    { pr_dina_playsingle, pt_rfc3986_ignore },
    { pr_dina_playcontainer, pt_rfc3986_ignore },
    { pr_dns, pt_rfc3986_ignore },
    { pr_dntp, pt_rfc3986_ignore },
    { pr_doi, pt_rfc3986_ignore },
    { pr_drm, pt_rfc3986_ignore },
    { pr_dtn, pt_rfc3986_ignore },
    { pr_dvb, pt_rfc3986_ignore },
    { pr_ed2k, pt_rfc3986_ignore },
    { pr_example, pt_rfc3986_ignore },
    { pr_facetime, pt_rfc3986_ignore },
    { pr_fax, pt_rfc3986_ignore },
    { pr_feed, pt_rfc3986_ignore },
    {   pr_file,    pt_local },
     { pr_filesystem, pt_rfc3986_ignore },
    { pr_finger, pt_rfc3986_ignore },
    { pr_fish, pt_rfc3986_ignore },
    { pr_fm, pt_rfc3986_ignore },
   {   pr_ftp,     pt_rfc3986  },
    {   pr_ftps,    pt_rfc3986  },
    { pr_gemini, pt_rfc3986_ignore },
    {   pr_geo,     pt_geo   },
    { pr_gg, pt_rfc3986_ignore },
    { pr_git, pt_rfc3986_ignore },
    { pr_gizmoproject, pt_rfc3986_ignore },
    { pr_go, pt_rfc3986_ignore },
    { pr_gopher, pt_rfc3986_ignore },
    { pr_gtalk, pt_rfc3986_ignore },
    { pr_h323, pt_rfc3986_ignore },
    { pr_hcp, pt_rfc3986_ignore },
    {   pr_http,    pt_rfc3986  },
    {   pr_https,   pt_rfc3986  },
    { pr_iax, pt_rfc3986_ignore },
    { pr_icap, pt_rfc3986_ignore },
    { pr_icon, pt_rfc3986_ignore },
    { pr_im, pt_rfc3986_ignore },
    { pr_imap, pt_rfc3986_ignore },
    { pr_info, pt_rfc3986_ignore },
    { pr_iotdisco, pt_rfc3986_ignore },
    { pr_ipn, pt_rfc3986_ignore },
    { pr_ipp, pt_rfc3986_ignore },
    { pr_ipps, pt_rfc3986_ignore },
    { pr_irc, pt_rfc3986_ignore },
    { pr_irc6, pt_rfc3986_ignore },
    { pr_ircs, pt_rfc3986_ignore },
    { pr_iris, pt_rfc3986_ignore },
    { pr_iris_beep, pt_rfc3986_ignore },
    { pr_iris_xpc, pt_rfc3986_ignore },
    { pr_iris_xpcs, pt_rfc3986_ignore },
    { pr_iris_lws, pt_rfc3986_ignore },
    { pr_itms, pt_rfc3986_ignore },
    { pr_jabber, pt_rfc3986_ignore },
    { pr_jar, pt_rfc3986_ignore },
    { pr_javascript, pt_rfc3986_ignore },
    { pr_jdbc, pt_rfc3986_ignore },
    { pr_jms, pt_rfc3986_ignore },
    { pr_keyparc, pt_rfc3986_ignore },
    { pr_lastfm, pt_rfc3986_ignore },
    {   pr_ldap,    pt_rfc3986_ignore  },
    { pr_ldaps, pt_rfc3986_ignore  },
    { pr_magnet, pt_rfc3986_ignore },
    { pr_mailserver, pt_rfc3986_ignore },
    {   pr_mailto,  pt_rfc3986_ignore },
    { pr_maps, pt_rfc3986_ignore },
    { pr_market, pt_rfc3986_ignore },
    { pr_message, pt_rfc3986_ignore },
    { pr_mid, pt_rfc3986_ignore },
    { pr_mms, pt_rfc3986_ignore },
    { pr_modem, pt_rfc3986_ignore },
    { pr_ms_help, pt_rfc3986_ignore },
    { pr_ms_settings, pt_rfc3986_ignore },
    { pr_ms_settings_airplanemode, pt_rfc3986_ignore },
    { pr_ms_settings_bluetooth, pt_rfc3986_ignore },
    { pr_ms_settings_camera, pt_rfc3986_ignore },
    { pr_ms_settings_cellular, pt_rfc3986_ignore },
    { pr_ms_settings_cloudstorage, pt_rfc3986_ignore },
    { pr_ms_settings_emailandaccounts, pt_rfc3986_ignore },
    { pr_ms_settings_language, pt_rfc3986_ignore },
    { pr_ms_settings_location, pt_rfc3986_ignore },
    { pr_ms_settings_lock, pt_rfc3986_ignore },
    { pr_ms_settings_nfctransactions, pt_rfc3986_ignore },
    { pr_ms_settings_notifications, pt_rfc3986_ignore },
    { pr_ms_settings_power, pt_rfc3986_ignore },
    { pr_ms_settings_privacy, pt_rfc3986_ignore },
    { pr_ms_settings_proximity, pt_rfc3986_ignore },
    { pr_ms_settings_screenrotation, pt_rfc3986_ignore },
    { pr_ms_settings_wifi, pt_rfc3986_ignore },
    { pr_ms_settings_workplace, pt_rfc3986_ignore },
    { pr_msnum, pt_rfc3986_ignore },
    { pr_msrp, pt_rfc3986_ignore },
    { pr_msrps, pt_rfc3986_ignore },
    { pr_mtqp, pt_rfc3986_ignore },
    { pr_mumble, pt_rfc3986_ignore },
    { pr_mupdate, pt_rfc3986_ignore },
    { pr_mvn, pt_rfc3986_ignore },
    {   pr_news,    pt_news  },
    { pr_nfs, pt_rfc3986_ignore },
    { pr_ni, pt_rfc3986_ignore },
    { pr_nih, pt_rfc3986_ignore },
    { pr_nntp, pt_rfc3986_ignore },
    { pr_notes, pt_rfc3986_ignore },
    { pr_ocsp, pt_rfc3986 },
    { pr_odbc, pt_rfc3986_ignore },
    { pr_oid, pt_rfc3986_ignore },
    { pr_opaquelocktoken, pt_rfc3986_ignore },
    { pr_openpgp4fpr, pt_rfc3986_ignore },
    { pr_pack, pt_rfc3986_ignore },
    { pr_palm, pt_rfc3986_ignore },
    { pr_paparazzi, pt_rfc3986_ignore },
    { pr_payto, pt_rfc3986_ignore },
    { pr_pkcs11, pt_rfc3986_ignore },
    { pr_platform, pt_rfc3986_ignore },
    { pr_pop, pt_rfc3986_ignore },
    { pr_pres, pt_rfc3986_ignore },
    { pr_prospero, pt_rfc3986_ignore },
    { pr_proxy, pt_rfc3986_ignore },
    { pr_psyc, pt_rfc3986_ignore },
    { pr_query, pt_rfc3986_ignore },
    { pr_redis, pt_rfc3986_ignore },
    { pr_rediss, pt_rfc3986_ignore },
    { pr_reload, pt_rfc3986_ignore },
    { pr_res, pt_rfc3986_ignore },
    { pr_resource, pt_rfc3986_ignore },
    { pr_rmi, pt_rfc3986_ignore },
    { pr_rsync, pt_rfc3986_ignore },
    { pr_rtmfp, pt_rfc3986_ignore },
    { pr_rtmp, pt_rfc3986_ignore },
    {   pr_rtsp,    pt_rfc3986_ignore  },
    { pr_s3, pt_rfc3986_ignore },
    { pr_secondlife, pt_rfc3986_ignore },
    { pr_service, pt_rfc3986_ignore },
    { pr_session, pt_rfc3986_ignore },
    {   pr_sftp,    pt_rfc3986_ignore  },
    { pr_sgn, pt_rfc3986_ignore },
    { pr_shttp, pt_rfc3986_ignore },
    { pr_sieve, pt_rfc3986_ignore },
    { pr_sip, pt_rfc3986_ignore },
    { pr_sips, pt_rfc3986_ignore },
    { pr_skype, pt_rfc3986_ignore },
    { pr_slack, pt_rfc3986_ignore },
    { pr_smb, pt_rfc3986_ignore },
    { pr_sms, pt_rfc3986_ignore },
    { pr_snews, pt_rfc3986_ignore },
    { pr_snmp, pt_rfc3986_ignore },
    { pr_soap_beep, pt_rfc3986_ignore },
    { pr_soap_beeps, pt_rfc3986_ignore },
    { pr_soldat, pt_rfc3986_ignore },
    { pr_spotify, pt_rfc3986_ignore },
    {   pr_ssh,     pt_rfc3986_ignore  },
    { pr_steam, pt_rfc3986_ignore },
    { pr_stratum, pt_rfc3986_ignore },
    { pr_stun, pt_rfc3986_ignore },
    { pr_stuns, pt_rfc3986_ignore },
    { pr_snv, pt_rfc3986_ignore },
    { pr_tag, pt_rfc3986_ignore },
    { pr_teamspeak, pt_rfc3986_ignore },
    {   pr_tel,     pt_tel   },
    {   pr_telnet,  pt_rfc3986_ignore  },
    { pr_tftp, pt_rfc3986_ignore },
    { pr_things, pt_rfc3986_ignore },
    { pr_thismessage, pt_rfc3986_ignore },
    { pr_tn3270, pt_rfc3986_ignore },
    { pr_tip, pt_rfc3986_ignore },
    { pr_trueconf, pt_rfc3986_ignore },
    { pr_turn, pt_rfc3986_ignore },
    { pr_turns, pt_rfc3986_ignore },
    { pr_tv, pt_rfc3986_ignore },
    { pr_udp, pt_rfc3986_ignore },
    { pr_unreal, pt_rfc3986_ignore },
    {   pr_urn,     pt_urn   },
    { pr_ut2004, pt_rfc3986_ignore },
    { pr_vemmi, pt_rfc3986_ignore },
    { pr_ventrilo, pt_rfc3986_ignore },
    { pr_videotex, pt_rfc3986_ignore },
    { pr_view_source, pt_rfc3986_ignore },
    { pr_vnc, pt_rfc3986_ignore },
    { pr_wais, pt_rfc3986_ignore },
    { pr_webcal, pt_rfc3986_ignore },
    { pr_webplus, pt_rfc3986_ignore },
    { pr_ws, pt_rfc3986_ignore },
    { pr_wss, pt_rfc3986_ignore },
    { pr_wtai, pt_rfc3986_ignore },
    { pr_wyciwyg, pt_rfc3986_ignore },
    { pr_xcon, pt_rfc3986_ignore },
    { pr_xcon_userid, pt_rfc3986_ignore },
    { pr_xfire, pt_rfc3986_ignore },
    { pr_xmlrpc_beep, pt_rfc3986_ignore },
    { pr_xmlrpc_beeps, pt_rfc3986_ignore },
    { pr_xmpp, pt_rfc3986_ignore },
    { pr_xri, pt_rfc3986_ignore },
    { pr_ymsgr, pt_rfc3986_ignore },
    { pr_z39_50, pt_rfc3986_ignore },
    { pr_z39_50r, pt_rfc3986_ignore },
    { pr_z39_50s, pt_rfc3986_ignore },
    { pr_zoommtg, pt_rfc3986_ignore },
    { pr_zoomus, pt_rfc3986_ignore } };

void protocol::init (nitpick& nits)
{   symbol < html_version, e_protocol > :: init (nits, protocol_symbol_table, sizeof (protocol_symbol_table) / sizeof (struct symbol_entry < html_version, e_protocol >));
#ifdef DEBUG
    for (unsigned i = 1; i < pr_error; ++i)
        PRESUME (ps [i].protocol_ == static_cast < e_protocol > (i), __FILE__, __LINE__);
#endif // DEBUG
}

e_scheme protocol::scheme () const
{   e_protocol prot = symbol < html_version, e_protocol > :: get ();
    PRESUME (ps [prot].protocol_ == prot, __FILE__, __LINE__);
    return ps [prot].scheme_; }

bool protocol::parse (nitpick& nits, const html_version& v, const ::std::string& x, const e_protocol current)
{   ::std::string lc (::boost::algorithm::to_lower_copy (trim_the_lot_off (x)));
    if (lc.empty ()) set (v, current);
    else
    {   ::std::string::size_type colon = lc.find (COLON);
        default_ = (colon == ::std::string::npos);
        if (default_) set (v, current);
        else if (colon == 0 || colon == lc.length () - 1)
        {   nits.pick (nit_invalid_protocol, ed_rfc_3986, "3.1. Scheme", es_error, ec_url, "invalid protocol and/or missing address");
            return false; }
        else
        {   e_protocol prot;
            if (! symbol < html_version, e_protocol > :: parse (nits, v, lc.substr (0, colon), prot)) set (v, pr_other);
            else set (v, prot); }
        if (! url_schemes < SCHEMES > :: parse (nits, v, scheme (), symbol < html_version, e_protocol > :: get (), x, component_))
            return false; }
    return true; }

bool protocol::is_valid () const
{   return url_schemes < SCHEMES > :: is_valid (scheme (), component_, default_); }

::std::string protocol::get () const
{   return url_schemes < SCHEMES > :: get (scheme (), component_, default_); }

::std::string protocol::absolute (bool can_use_index) const
{   return url_schemes < SCHEMES > :: absolute (scheme (), component_, can_use_index, default_); }

bool protocol::operator == (const protocol& rhs) const
{   if (scheme () != rhs.scheme ()) return false;
    return url_schemes < SCHEMES > :: similar (scheme (), component_, rhs.component_); }
