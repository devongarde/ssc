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
#include "webpage/page.h"

struct symbol_entry < html_version, e_csp_directive > csp_directive_symbol_table [] =
{   { { CSP_2 }, { HTML_UNDEF }, "base-uri", csp_base_uri },
    { { CSP_3 }, { HTML_UNDEF }, "block-all-mixed-content", csp_block_all_mixed_content },
    { { CSP_2 }, { HTML_UNDEF }, "child-src", csp_child },
    { { CSP_1 }, { HTML_UNDEF }, "connect-src", csp_connect },
    { { CSP_1 }, { HTML_UNDEF }, "default-src", csp_default },
    { { CSP_1 }, { HTML_UNDEF }, "frame-src", csp_frame },
    { { CSP_1 }, { HTML_UNDEF }, "font-src", csp_font },
    { { CSP_2 }, { HTML_UNDEF }, "form-action", csp_form_action },
    { { CSP_2 }, { HTML_UNDEF }, "frame-ancestors", csp_frame_ancestors },
    { { CSP_1 }, { HTML_UNDEF }, "img-src", csp_img },
    { { CSP_3 }, { HTML_UNDEF }, "manifest-src", csp_manifest },
    { { CSP_1 }, { HTML_UNDEF }, "media-src", csp_media },
    { { CSP_3 }, { HTML_UNDEF }, "navigate-to", csp_navigate_to },
    { { CSP_2 }, { HTML_UNDEF }, "plugin-types", csp_plugin_types },
    { { CSP_3 }, { HTML_UNDEF }, "prefetch-src", csp_prefetch },
    { { CSP_1 }, { HTML_UNDEF }, "object-src", csp_object },
    { { CSP_3 }, { HTML_UNDEF }, "report-to", csp_report_to },
    { { CSP_1 }, { HTML_UNDEF }, "report-uri", csp_report_uri },
    { { CSP_3 }, { HTML_UNDEF }, "require-sri-for", csp_require_sri_for },
    { { CSP_1 }, { HTML_UNDEF }, "sandbox", csp_sandbox },
    { { CSP_1 }, { HTML_UNDEF }, "script-src", csp_script },
    { { CSP_3 }, { HTML_UNDEF }, "script-src-elem", csp_script_elem },
    { { CSP_3 }, { HTML_UNDEF }, "script-src-attr", csp_script_attr },
    { { CSP_1 }, { HTML_UNDEF }, "style-src", csp_style },
    { { CSP_3 }, { HTML_UNDEF }, "style-src-elem", csp_style_elem },
    { { CSP_3 }, { HTML_UNDEF }, "style-src-attr", csp_style_attr },
    { { CSP_3 }, { HTML_UNDEF }, "update-insecure-requests", csp_update_insecure_requests },
    { { CSP_3 }, { HTML_UNDEF }, "worker-src", csp_worker } };

struct symbol_entry < html_version, e_csp_keyword > csp_keyword_symbol_table [] =
{   { { CSP_1 }, { HTML_UNDEF },  "'self'", csk_self },
    { { CSP_1 }, { HTML_UNDEF },  "'unsafe-inline'", csk_unsafe_inline },
    { { CSP_1 }, { HTML_UNDEF },  "'unsafe-eval'", csk_unsafe_eval },
    { { CSP_3 }, { HTML_UNDEF },  "'strict-dynamic'", csk_strict_dynamic },
    { { CSP_3 }, { HTML_UNDEF },  "'unsafe-hashes'", csk_unsafe_hashes },
    { { CSP_3 }, { HTML_UNDEF },  "'report-sample'", csk_report_sample },
    { { CSP_3 }, { HTML_UNDEF },  "'unsafe-allow-redirects'", csk_unsafe_allow_redirects } };

void csp_directive_init (nitpick& nits)
{   type_master < t_csp_directive > :: init (nits, csp_directive_symbol_table, sizeof (csp_directive_symbol_table) / sizeof (symbol_entry < html_version, e_csp_directive >)); }

void csp_keyword_init (nitpick& nits)
{   type_master < t_csp_keyword > :: init (nits, csp_keyword_symbol_table, sizeof (csp_keyword_symbol_table) / sizeof (symbol_entry < html_version, e_csp_keyword >)); }
