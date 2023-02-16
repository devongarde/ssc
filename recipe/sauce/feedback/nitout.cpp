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
#include "feedback/nitout.h"
#include "main/context.h"
#include "type/type_enum.h"
#include "type/type_master.h"
#include "coop/lox.h"

macro_uptr macro;

vstr_t sections;

#define MACID ALPHANUMERIC "-_"

#define SPEC_NIT \
    "[class]\n" \
    "{{class-name}} {{class-int}}\n" \
    "\n" \
    "[class-head]\n" \
    "\n" \
    START_OF_SECTION " classes\n" \
    "\n" \
    "[class-foot]\n" \
    "\n" \
    "[tally]\n" \
    "    {{tally-name}}: {{tally-int}}\n" \
    "\n" \
    "[tally-head]\n" \
    "{{tally-title:CSS ::}}\n" \
    "\n" \
    "[tally-foot]\n" \
    "  {{tally-count}} {{tally-title}} used {{tally-total}}\n" \
    "\n" \
    "[config]\n" \
    "\n" \
    "[config-head]\n" \
    "\n" \
    START_OF_SECTION " configuration\n" \
    "\n" \
    "[config-foot]\n" \
    "\n" \
    "[doc-head]\n" \
    "-f {{config}}\n" \
    "\n" \
    "[doc-foot]\n" \
    "\n" \
    "[export]\n" \
    "\n" \
    "[export-head]\n" \
    "\n" \
    START_OF_SECTION " exports\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[export-foot]\n" \
    "\n" \
    "[grand-head]\n" \
    "\n" \
    START_OF_SECTION " {{grand-title}}\n" \
    "\n" \
    "[grand-foot]\n" \
    END_OF_STATS "\n" \
    "\n" \
    "[itemid]\n" \
    "{{itemid-name}} ({{itemid-page}}:{{itemid-line}})\n" \
    "\n" \
    "[itemid-head]\n" \
    "\n" \
    START_OF_SECTION " itemids\n" \
    "\n" \
    "[itemid-foot]\n" \
    "\n" \
    "[init]\n" \
    "{{nit-explanation}} [{{nit-id}}]\n" \
    "\n" \
    "[init-head]\n" \
    "\n" \
    START_OF_SECTION " initialisation\n" \
    "\n" \
    "[init-foot]\n" \
    "\n" \
    "[link]\n" \
    "\n" \
    "[link-head]\n" \
    "\n" \
    START_OF_SECTION " link errors\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[link-foot]\n" \
    "\n" \
    "[nit]\n" \
    "\n" \
    "[nits-head]\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[nits-page]\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[nits-foot]\n" \
    "{{nits-lost:(:)\n}}" \
    "\n" \
    "[page-head]\n" \
    "\n" \
    "PASS {{page-disk-path}}\n" \
    "\n" \
    "[page-foot]\n" \
    "\n" \
    "[shadow]\n" \
    "\n" \
    "[shadow-head]\n" \
    "\n" \
    START_OF_SECTION " shadow\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[shadow-foot]\n" \
    "\n" \
    "[stat]\n" \
    "    {{stat-name||: }}{{stat-count}} {{stat-detail}}\n" \
    "\n" \
    "[stats-head]\n" \
    "{{stats-title||:}}\n" \
    "\n" \
    "[stats-foot]\n" \
    "  {{stats-total}}\n" \
    "\n" \
    "[stat-sub]\n" \
    "      {{stat-subname||: }}{{stat-subcount}} {{stat-subdetail}}\n" \
    "\n" \
    "[stats-subhead]\n" \
    "  {{stats-subtitle||:}}\n" \
    "\n" \
    "[stats-subfoot]\n" \
    "\n" \
    "[update]\n" \
    "\n" \
    "[update-head]\n" \
    "\n" \
    START_OF_SECTION " update\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[update-foot]\n" \
    "\n"

#define TEST_NIT \
    "[class]\n" \
    "{{class-name}} {{class-int}}\n" \
    "\n" \
    "[class-head]\n" \
    "\n" \
    START_OF_SECTION " classes\n" \
    "\n" \
    "[class-foot]\n" \
    "\n" \
    "[tally]\n" \
    "    {{tally-name}}: {{tally-int}}\n" \
    "\n" \
    "[tally-head]\n" \
    "{{tally-title:CSS ::}}\n" \
    "\n" \
    "[tally-foot]\n" \
    "  {{tally-count}} {{tally-title}} used {{tally-total}}\n" \
    "\n" \
    "[config]\n" \
    "\n" \
    "[config-head]\n" \
    "\n" \
    START_OF_SECTION " configuration\n" \
    "\n" \
    "[config-foot]\n" \
    "\n" \
    "[doc-head]\n" \
    "{{prog-abbrev}}\n" \
    "{{prog-version}}\n" \
    "{{copyright-text}} ({{copyright-addr}})\n" \
    "\n" \
    "[doc-foot]\n" \
    "\n" \
    "[export]\n" \
    "\n" \
    "[export-head]\n" \
    "\n" \
    START_OF_SECTION " exports\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[export-foot]\n" \
    "\n" \
    "[grand-head]\n" \
    "\n" \
    START_OF_SECTION " {{grand-title}}\n" \
    "\n" \
    "[grand-foot]\n" \
    END_OF_STATS "\n" \
    "\n" \
    "[itemid]\n" \
    "{{itemid-name}} ({{id-page}}:{{itemid-line}})\n" \
    "\n" \
    "[itemid-head]\n" \
    "\n" \
    START_OF_SECTION " itemids\n" \
    "\n" \
    "[itemid-foot]\n" \
    "\n" \
    "[init]\n" \
    "{{nit-explanation}} [{{nit-id}}]\n" \
    "\n" \
    "[init-head]\n" \
    "\n" \
    START_OF_SECTION " initialisation\n" \
    "\n" \
    "[init-foot]\n" \
    "\n" \
    "[link]\n" \
    "\n" \
    "[link-head]\n" \
    "\n" \
    START_OF_SECTION " link errors\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[link-foot]\n" \
    "\n" \
    "[nit]\n" \
    "\n" \
    "[nits-head]\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[nits-page]\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[nits-foot]\n" \
    "{{nits-lost:(:)\n}}" \
    "\n" \
    "[page-head]\n" \
    "\n" \
    "\n" \
    START_OF_SECTION " {{page-disk-path}}\n" \
    "\n" \
    "[page-foot]\n" \
    "\n" \
    "[shadow]\n" \
    "\n" \
    "[shadow-head]\n" \
    "\n" \
    START_OF_SECTION " shadow\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[shadow-foot]\n" \
    "\n" \
    "[stat]\n" \
    "    {{stat-name||: }}{{stat-count}} {{stat-detail}}\n" \
    "\n" \
    "[stats-head]\n" \
    "{{stats-title||:}}\n" \
    "\n" \
    "[stats-foot]\n" \
    "  {{stats-total}}\n" \
    "\n" \
    "[stat-sub]\n" \
    "      {{stat-subname||: }}{{stat-subcount}} {{stat-subdetail}}\n" \
    "\n" \
    "[stats-subhead]\n" \
    "  {{stats-subtitle||:}}\n" \
    "\n" \
    "[stats-subfoot]\n" \
    "\n" \
    "[update]\n" \
    "\n" \
    "[update-head]\n" \
    "\n" \
    START_OF_SECTION " update\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[update-foot]\n" \
    "\n"

#define TEXT_NIT \
    "[class]\n" \
    "class \"{{class-name}}\" is used {{class-count}}\n" \
    "\n" \
    "[class-head]\n" \
    "\n" \
    START_OF_SECTION " classes\n" \
    "\n" \
    "[class-foot]\n" \
    "\n" \
    "[tally]\n" \
    "    {{tally-name}}: {{tally-int}}\n" \
    "\n" \
    "[tally-head]\n" \
    "{{tally-title:CSS ::}}\n" \
    "\n" \
    "[tally-foot]\n" \
    "  {{tally-count}} {{tally-title}} used {{tally-sum}}\n" \
    "\n" \
    "[config]\n" \
    "{{nit-explanation}}\n" \
    "\n" \
    "[config-head]\n" \
    "\n" \
    START_OF_SECTION " configuration\n" \
    "\n" \
    "[config-foot]\n" \
    "\n" \
    "[doc-head]\n" \
    "{{prog-fullname}} version {{prog-version}}\n" \
    "{{copyright-text}}\n" \
    "{{time-start}}\n" \
    "\n" \
    "[doc-foot]\n" \
    "\n" \
    "[export]\n" \
    "{{nit-explanation}} [{{nit-id}}]\n" \
    "\n" \
    "[export-head]\n" \
    "\n" \
    START_OF_SECTION " exports\n" \
    "\n" \
    "[export-foot]\n" \
    "\n" \
    "[grand-head]\n" \
    "\n" \
    START_OF_SECTION " {{grand-title}}\n" \
    "\n" \
    "[grand-foot]\n" \
    "\n" \
    "[itemid]\n" \
    "{{itemid-name}} ({{itemid-page}}:{{itemid-line}})\n" \
    "\n" \
    "[itemid-head]\n" \
    "\n" \
    START_OF_SECTION " itemids\n" \
    "\n" \
    "[itemid-foot]\n" \
    "\n" \
    "[init]\n" \
    "{{nit-explanation}} [{{nit-id}}]\n" \
    "\n" \
    "[init-head]\n" \
    "\n" \
    START_OF_SECTION " initialisation\n" \
    "\n" \
    "[init-foot]\n" \
    "\n" \
    "[link]\n" \
    "{{nit-explanation}} [{{nit-id}}]\n" \
    "\n" \
    "[link-head]\n" \
    "\n" \
    START_OF_SECTION " link errors\n" \
    "\n" \
    "[link-foot]\n" \
    "\n" \
    "[nit]\n" \
    "{{level-symbol}} {{nit-explanation}} [{{nit-id}}]\n" \
    "\n" \
    "[nits-head]\n" \
    "\n" \
    "{{nit-line}} {{nit-before}} {{nit-mote}} {{nit-after}}\n" \
    "\n" \
    "[nits-page]\n" \
    "\n" \
    "[nits-foot]\n" \
    "{{nits-lost:(:)\n}}" \
    "\n" \
    "[page-head]\n" \
    "\n" \
    "\n" \
    START_OF_SECTION " {{page-disk-path}}\n" \
    "\n" \
    "[page-foot]\n" \
    "\n" \
    "[shadow]\n" \
    "\n" \
    "[shadow-head]\n" \
    "\n" \
    "[shadow-foot]\n" \
    "\n" \
    "[stat]\n" \
    "    {{stat-name||: }}{{stat-count}} {{stat-detail}}\n" \
    "\n" \
    "[stats-head]\n" \
    "{{stats-title||:}}\n" \
    "\n" \
    "[stats-foot]\n" \
    "  {{stats-total}}\n" \
    "\n" \
    "[stat-sub]\n" \
    "      {{stat-subname||: }}{{stat-subcount}} {{stat-subdetail}}\n" \
    "\n" \
    "[stats-subhead]\n" \
    "  {{stats-subtitle||:}}\n" \
    "\n" \
    "[stats-subfoot]\n" \
    "\n" \
    "[update]\n" \
    "{{nit-explanation}} [{{nit-id}}]\n" \
    "\n" \
    "[update-head]\n" \
    "\n" \
    START_OF_SECTION " update\n" \
    "\n" \
    "[update-foot]\n" \
    "\n"

#define HTML_NIT \
    "[class]\n" \
    "<SPAN class=\"nit-name\">{{class-name}}</SPAN> <SPAN class=\"nit-count\">{{class-count}}</SPAN><BR>\n" \
    "\n" \
    "[class-head]\n" \
    "<H2 class=\"nit-section\">classes</H2>\n" \
    "<P>\n" \
    "\n" \
    "[class-foot]\n" \
    "</P>\n" \
    "\n" \
    "[tally]\n" \
    "<SPAN class=\"nit-name\">{{tally-name}}</SPAN> <SPAN class=\"nit-count\">{{tally-count}}</SPAN><BR>\n" \
    "\n" \
    "[tally-head]\n" \
    "{{tally-title:<H2 class=\"nit-section\">: CSS/HTML:</H2>\n}}" \
    "<P>\n" \
    "\n" \
    "[tally-foot]\n" \
    "<SPAN class=\"nit-name\">{{tally-count}} {{tally-title}}:</SPAN> <SPAN class=\"nit-count\">{{tally-total}}</SPAN>\n" \
    "</P>\n" \
    "\n" \
    "[config]\n" \
    "<SPAN class=\"nit-name\">{{nit-explanation}}</SPAN><BR>\n" \
    "\n" \
    "[config-head]\n" \
    "<H2 class=\"nit-section\">configuration</H2>\n" \
    "<P>\n" \
    "\n" \
    "[config-foot]\n" \
    "</P>\n" \
    "\n" \
    "[doc-head]\n" \
    "<!DOCTYPE HTML>\n" \
    "<HTML lang=en>\n" \
    "<HEAD>\n" \
    "<TITLE>{{prog-abbrev}} report{{context-root: for :}}</TITLE>\n" \
    "<STYLE TYPE=\"text/css\">\n" \
    "A { color:#9999BB }\n" \
    "H1,H2,H3,H4,H5,H6 { margin-bottom: 0; padding-bottom: 0; }\n" \
    "H1 { color:#66BB66; font-size: 140%; }\n" \
    "H2 { color:#66BB66; font-size: 120% }\n" \
    "H3 { color:#99BB99; font-size: 100% }\n" \
    "P { margin-top: 0; padding-top: 0; }\n" \
    "FOOTER,HEADER,LI,MAIN,P,PRE { color:#999999 }\n" \
    ".smaller { font-size: 80% }\n" \
    ".nit-before,.nit-after { color: #CCCCCC }\n" \
    ".nit-catastrophe { color: #FF0000 }\n" \
    ".nit-doc { font-style: italic; }\n" \
    ".nit-error { color: #FF6666 }\n" \
    ".nit-explanation { color: #9999CC }\n" \
    ".nit-info { color: #666666 }\n" \
    ".nit-line { color: #666666 }\n" \
    ".nit-mote { color: #CC3333 }\n" \
    ".nit-ref { font-style: italic; }\n" \
    ".nit-warning { color: #CC6666 }\n" \
    "</STYLE>\n" \
    "</HEAD>\n" \
    "<BODY>\n" \
    "<HEADER>\n" \
    "<H1 class=\"nit-title\">{{prog-abbrev}} report{{context-root: for :}}</H1>\n" \
    "</HEADER>\n" \
    "<MAIN>\n" \
    "\n" \
    "[doc-foot]\n" \
    "<A href=\"/index.html\">previous page</A>\n" \
    "</MAIN>\n" \
    "<HR>\n" \
    "<FOOTER class=\"smaller\">\n" \
    "<A href=\"{{prog-addr}}\" class=\"ssc-name\">{{prog-fullname}}</A> version {{prog-version}} ({{compile-time}})<BR>\n" \
    "<A href=\"{{copyright-addr}}\" class=\"ssc-copyright\">{{copyright-text}}</A>\n" \
    "</FOOTER>\n" \
    "</BODY>\n" \
    "</HTML>\n" \
    "\n" \
    "[export]\n" \
    "<SPAN class=\"nit-name\">{{nit-explanation}}</SPAN><BR>\n" \
    "\n" \
    "[export-head]\n" \
    "<H2 class=\"nit-section\">exports</H2>\n" \
    "<P>\n" \
    "\n" \
    "[export-foot]\n" \
    "</P>\n" \
    "\n" \
    "[grand-head]\n" \
    "<H3 class=\"nit-subsection\">{{grand-title}}</H3>\n" \
    "<P>\n" \
    "\n" \
    "[grand-foot]\n" \
    "</P>\n" \
    "\n" \
    "[itemid]\n" \
    "<SPAN class=\"nit-name\">{{itemid-name}}</SPAN> <SPAN class=\"nit-id\">({{itemid-page}}:{{itemid-line}})</SPAN><BR>\n" \
    "\n" \
    "[itemid-head]\n" \
    "<H2 class=\"nit-section\">Item IDs</H2>\n" \
    "<P>\n" \
    "\n" \
    "[itemid-foot]\n" \
    "</P>\n" \
    "\n" \
    "[init]\n" \
    "<SPAN class=\"nit-name\">{{nit-explanation}}</SPAN> <SPAN class=\"nit-id\">[{{nit-id}}]</SPAN><BR>\n" \
    "\n" \
    "[init-head]\n" \
    "\n" \
    "<H2 class=\"nit-section\">initialisation</H2>\n" \
    "\n" \
    "[init-foot]\n" \
    "</P>\n" \
    "\n" \
    "[link]\n" \
    "<SPAN class=\"nit-name\">{{nit-explanation}}</SPAN> <SPAN class=\"nit-id\">[{{nit-id}}]</SPAN><BR>\n" \
    "\n" \
    "[link-head]\n" \
    "<H2 class=\"nit-section\">link errors</H2>\n" \
    "<P>\n" \
    "\n" \
    "[link-foot]\n" \
    "</P>\n" \
    "\n" \
    "[nit]\n" \
    "<SPAN class=\"nit-{{level-name}}\">{{level-name}}</SPAN>: <SPAN class=\"nit-explanation\">{{nit-explanation}}</SPAN>{{nit-ref:<BR><SPAN class=\"nit-ref\">:</SPAN>}}{{nit-long: <SPAN class=\"nit-doc\">(:)</SPAN>}}<BR>\n" \
    "\n" \
    "[nits-head]\n" \
    "<H3>{{nit-before:<SPAN class=\"nit-before\">:</SPAN> }}<SPAN class=\"nit-mote\">{{nit-mote}}</SPAN>{{nit-after: <SPAN class=\"nit-after\">:</SPAN>}}</H3>\n" \
    "<P>\n" \
    "\n" \
    "[nits-page]\n" \
    "<P>\n" \
    "\n" \
    "[nits-foot]\n" \
    "{{nits-lost:<BR><SPAN class=\"nit-error\">(:)</SPAN>}}" \
    "</P>\n" \
    "\n" \
    "[page-head]\n" \
    "<H2 class=\"nit-section\">{{page-site-path}}</H2>\n" \
    "\n" \
    "[page-foot]\n" \
    "<BR><BR>\n" \
    "\n" \
    "[shadow]\n" \
    "<SPAN class=\"nit-name\">{{nit-explanation}}</SPAN> <SPAN class=\"nit-id\">[{{nit-id}}]</SPAN><BR>\n" \
    "\n" \
    "[shadow-head]\n" \
    "<H2 class=\"nit-section\">shadow</H2>\n" \
    "<P>\n" \
    "\n" \
    "[shadow-foot]\n" \
    "</P>\n" \
    "\n" \
    "[stat]\n" \
    "<SPAN class=\"nit-name\">{{stat-name}}</SPAN> <SPAN class=\"nit-count\">{{stat-count}}</SPAN> <SPAN class=\"nit-detail\">{{stat-detail}}</SPAN><BR>\n" \
    "\n" \
    "[stats-head]\n" \
    "<H3 class=\"nit-section\">{{stats-title}}</H3>\n" \
    "<P>\n" \
    "\n" \
    "[stats-foot]\n" \
    "<SPAN class=\"nit-name\">Total:</SPAN> <SPAN class=\"nit-count\">{{stats-total}}</SPAN>\n" \
    "</P>\n" \
    "\n" \
    "[stat-sub]\n" \
    "<SPAN class=\"nit-subname\">{{stat-subname}}</SPAN> <SPAN class=\"nit-subcount\">{{stat-subcount}} <SPAN class=\"nit-subdetail\">{{stat-subdetail}}</SPAN></SPAN><BR>\n" \
    "\n" \
    "[stats-subhead]\n" \
    "<H4 class=\"nit-subsection\">{{stats-subtitle}}</H4>\n" \
    "<P>\n" \
    "\n" \
    "[stats-subfoot]\n" \
    "</P>\n" \
    "\n" \
    "[update]\n" \
    "<SPAN class=\"nit-name\">{{nit-explanation}}</SPAN> <SPAN class=\"nit-id\">[{{nit-id}}]</SPAN><BR>\n" \
    "\n" \
    "[update-head]\n" \
    "<H2 class=\"nit-section\">update</H2>\n" \
    "<P>\n" \
    "\n" \
    "[update-foot]\n" \
    "</P>\n" \
    "\n"

void init_macro ()
{   macro = macro_uptr (new macro_t);
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> init (); }

::std::string enc (const ::std::string& s)
{   ::std::string res (1, '"');
    for (::std::string::const_iterator i = s.begin (); i != s.end (); ++i)
        switch (*i)
        {   case '\t' : res += "\\t"; break;
            case '\n' : res += "\\n"; break;
            case '\f' : res += "\\f"; break;
            case '\r' : res += "\\r"; break;
            case '\b' : res += "\\b"; break;
            case '\\' : res += "\\\\"; break;
            default :   if (*i >= ' ')
                            if (*i == '\"') res += "\\\"";
                            else res += *i;
                        break; }
    res += '"';
    return res; }

::std::string encsv (const ::std::string& s)
{   if (s.find (',') == ::std::string::npos) return s;
    ::std::string res (1, '"');
    for (::std::string::const_iterator i = s.begin (); i != s.end (); ++i)
        if (*i == '\"') res += "\"\"";
        else if (*i == '\\') res += "\\\\";
        else res += *i;
    res += '"';
    return res; }

::std::string endouble (const ::std::string& s, const char q)
{   ::std::string res (1, q);
    for (::std::string::const_iterator i = s.begin (); i != s.end (); ++i)
    {   if (*i == q) res += q;
        res += *i; }
    res += q;
    return res; }

::std::string enhtml (const ::std::string& s)
{   ::std::string res;
    for (::std::string::const_iterator i = s.begin (); i != s.end (); ++i)
        switch (*i)
        {   case '<' : res += "&lt;"; break;
            case '>' : res += "&gt;"; break;
            case '&' : res += "&amp;"; break;
            case ' ' : res += "&nbsp;"; break;
            default :  res += *i; break; }
    return res; }

void macro_t::set (const e_nit_macro m, const ::std::string& s)
{   flox f (lox_flox);
    mmac_.emplace (m, s); }

void macro_t::set (const e_nit_macro m, ::std::string&& s)
{   flox f (lox_flox);
    mmac_.emplace (m, s); }

::std::string macro_t::nit_content (const ::std::string& s)
{   switch (context.quote_style ())
    {   case qs_c : return enc (s);
        case qs_csv : return encsv (s);
        case qs_double : return endouble (s, '"');
        case qs_html : return enhtml (s);
        case qs_single : return endouble (s, '\'');
        default : return s; } }

bool macro_t::is_template_loaded ()
{   PRESUME (! fred.inited (), __FILE__, __LINE__);
    return ! sections.empty (); }

void macro_t::init ()
{   PRESUME (! fred.inited (), __FILE__, __LINE__);
    mmac_.emplace (nm_prog_abbrev, PROG);
    mmac_.emplace (nm_copy_addr, COPYRIGHT_WEBADDR);
    mmac_.emplace (nm_copy_html, COPYRIGHT_HTML);
    mmac_.emplace (nm_copy_text, COPYRIGHT_TEXT);
    mmac_.emplace (nm_prog_fullname, FULLNAME);
    mmac_.emplace (nm_prog_version, VERSION_STRING);
    mmac_.emplace (nm_prog_webaddr, WEBADDR); }

bool macro_t::load_template_int (nitpick& nits, const html_version& v, const ::std::string& config)
{   sections.clear ();
    sections.resize (ns_max);
    bool newline = true, apres = false, res = false;
    e_nit_section ns = ns_none;
    ::std::string::const_iterator sq_begin = config.cend (), sect_begin = config.cend ();
    for (::std::string::const_iterator i = config.cbegin (); i != config.cend (); ++i)
        switch (*i)
        {   case '[' :
                if (newline)
                {   sq_begin = i+1;
                    if (ns != ns_none)
                    {   PRESUME (sect_begin != config.cend (), __FILE__, __LINE__);
                        sections.at (ns) = ::std::string (sect_begin, i-1);
                        ns = ns_none;
                        sect_begin = config.cend (); }
                    continue; }
                newline = false;
                break;
            case ']' :
                newline = false;
                if (sq_begin != config.cend ())
                {   ::std::string nom (::std::string (sq_begin, i));
                    ns = examine_value < t_nit_section > (nits, v, nom);
                    if ((ns == ns_max) || (ns == ns_none))
                    {   ::std::string msg ("unrecognised section [");
                        msg += nom;
                        msg += "] ignored\n";
                        outstr.err (msg);
                        ns = ns_none; }
                    else res = true;
                    sq_begin = config.cend ();
                    apres = true;
                    continue; }
                break;
            case ' ' :
            case '\t' :
                break;
            case '\r' :
            case '\n' :
            case '\f' :
            case '\v' :
                newline = true;
                if (apres)
                {   sect_begin = i+1;
                    apres = false; }
                break;
            default :
                newline = false;
                break; }
    return res; }

bool macro_t::load_template (nitpick& nits, const html_version& v)
{   PRESUME (! fred.inited (), __FILE__, __LINE__);
    const ::std::string& format = context.nit_format ();
    ::std::string config;
    bool res = false;
#ifndef EXPAND_TEST
    if (context.test ())
        if (context.spec ()) res = load_template_int (nits, v, SPEC_NIT);
        else res = load_template_int (nits, v, TEST_NIT);
    else
#endif // EXPAND_TEST
    {   if (! format.empty ())
        {   config = template_path (nits, "out.nit", format);
            if (! config.empty ()) res = load_template_int (nits, v, config);
            if (! res)
            {   outstr.err (::std::string ("Cannot process ") + quote (format) + ", reverting to default output format.\n");
                nits.pick (nit_template_file, es_catastrophic, ec_init, "Cannot process ", quote (format), ", reverting to default output format)"); } }
        if (! res)
            if (! context.snippet ().empty ()) res = load_template_int (nits, v, HTML_NIT);
            else res = load_template_int (nits, v, TEXT_NIT); }
    PRESUME (res, __FILE__, __LINE__);
    return res; }

::std::string macro_t::apply_macros_int (const ::std::string& tpl, const mmac_t& values)
{   if (tpl.empty ()) return ::std::string ();
    bool subbed = false;
    ::std::string res;
    ::std::string::size_type len = context.macro_start ().size ();
    PRESUME (len == context.macro_end ().size (), __FILE__, __LINE__);
    ::std::string::size_type prepos = 0;
    nitpick nuts;
    for (   ::std::string::size_type pos = tpl.find (context.macro_start ());
            pos != ::std::string::npos;
            pos = tpl.find (context.macro_start (), pos+len))
    {   res += tpl.substr (prepos, pos-prepos);
        prepos = pos;
        ::std::string::size_type epos = tpl.find (context.macro_end (), pos+len);
        if (epos == ::std::string::npos) break;
        ::std::string m = tpl.substr (pos+len, epos-pos-len);
        if (! m.empty ())
        {   ::std::string b, a;
            const ::std::string::size_type bp = m.find_first_not_of (MACID);
            if (bp != ::std::string::npos)
            {   const char ch = m.at (bp);
                b = m.substr (bp+1);
                m = m.substr (0, bp);
                const ::std::string::size_type ap = b.find (ch);
                if (ap != ::std::string::npos)
                {   a = b.substr (ap+1);
                    b = b.substr (0, ap); } }
            const e_nit_macro mac = examine_value < t_nit_macro > (nuts, html_default, m);
            if (mac != nm_none)
            {   mmac_t::const_iterator ci = values.find (mac);
                if (ci != values.cend ())
                {   if (! ci -> second.empty ())
                        res += b + nit_content (ci -> second) + a;
                    prepos = pos = epos + len;
                    subbed = true;
                    continue; } } }
        ++pos; }
    res += tpl.substr (prepos);
    if (subbed) return apply_macros_int (res, values);
    return res; }

::std::string macro_t::apply (const e_nit_section& sct)
{   PRESUME (static_cast < ::std::size_t > (sct) < sections.size (), __FILE__, __LINE__);
    flox f (lox_flox);
    return apply_macros_int (sections.at (sct), mmac_); }

::std::string macro_t::apply (const e_nit_section& sct, const mmac_t& values)
{   PRESUME (static_cast < ::std::size_t > (sct) < sections.size (), __FILE__, __LINE__);
    return apply_macros_int (apply (sct), values); }

::std::string macro_t::apply (const e_nit_section& sct, const mmac_t& values1, const mmac_t& values2)
{   PRESUME (static_cast < ::std::size_t > (sct) < sections.size (), __FILE__, __LINE__);
    return apply_macros_int (apply (sct, values1), values2); }

::std::string macro_t::apply (const e_nit_section& sct, const mmac_t& values1, const mmac_t& values2, const mmac_t& values3)
{   PRESUME (static_cast < ::std::size_t > (sct) < sections.size (), __FILE__, __LINE__);
    return apply_macros_int (apply (sct, values1, values2), values3); }

::std::string macro_t::apply (const e_nit_section& sct, const mmac_t& values1, const mmac_t& values2, const mmac_t& values3, const mmac_t& values4)
{   PRESUME (static_cast < ::std::size_t > (sct) < sections.size (), __FILE__, __LINE__);
    return apply_macros_int (apply (sct, values1, values2, values3), values4); }

void macro_t::dump_nits (nitpick& nits, const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot)
{   if (! nits.empty ())
#ifdef NDEBUG
        if (context.tell (nits.worst ()))
#endif // NDEBUG
            outstr.out (nits.review (entry, head, foot));
    nits.reset (); }
