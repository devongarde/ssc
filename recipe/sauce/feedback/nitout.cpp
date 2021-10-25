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
#include "feedback/nitout.h"
#include "main/context.h"
#include "type/type_enum.h"
#include "type/type_master.h"

vstr_t sections;

#define MACID ALPHADDD "-_"

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
    "[config]\n" \
    "\n" \
    "[config-head]\n" \
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
    "[id]\n" \
    "{{id-name}} ({{id-page}}:{{id-line}})\n" \
    "\n" \
    "[id-head]\n" \
    "\n" \
    START_OF_SECTION " itemids\n" \
    "\n" \
    "[id-foot]\n" \
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
    "\n" \
    "[page-head]\n" \
    "\n" \
    "\n" \
    START_OF_SECTION " {{page-path}}\n" \
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
    "\n" \
    "[webmention]\n" \
    "\n" \
    "[webmention-head]\n" \
    "\n" \
    START_OF_SECTION " webmentions\n" \
    "{{nit-line}} {{nit-ns}}\n" \
    "\n" \
    "[webmention-foot]\n" \
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
    "[id]\n" \
    "{{id-name}} ({{id-page}}:{{id-line}})\n" \
    "\n" \
    "[id-head]\n" \
    "\n" \
    START_OF_SECTION " itemids\n" \
    "\n" \
    "[id-foot]\n" \
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
    "{{nit-line}} {{nit-before}} " BEFORE_MOTE " {{nit-mote}} " AFTER_MOTE " {{nit-after}}\n" \
    "\n" \
    "[nits-page]\n" \
    "\n" \
    "[nits-foot]\n" \
    "\n" \
    "[page-head]\n" \
    "\n" \
    "\n" \
    START_OF_SECTION " {{page-path}}\n" \
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
    "\n" \
    "[webmention]\n" \
    "{{nit-explanation}} [{{nit-id}}]\n" \
    "\n" \
    "[webmention-head]\n" \
    "\n" \
    START_OF_SECTION " webmentions\n" \
    "\n" \
    "[webmention-foot]\n" \
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
    "<TITLE>{{prog-abbrev}} report for {{context-root}}</TITLE>\n" \
    "<STYLE TYPE=\"text/css\">\n" \
    "H1 { color:#66BB66; font-size: 140% }\n" \
    "H2 { color:#66BB66; font-size: 120% }\n" \
    "H3 { color:#99BB99; font-size: 100% }\n" \
    "A { color:#9999BB }\n" \
    "FOOTER,HEADER,LI,MAIN,P,PRE { color:#999999 }\n" \
    ".smaller { font-size: 80% }\n" \
    ".nit-before,.nit-after { color: #BBBBBB }\n" \
    ".nit-mote { color: #BB3333 }\n" \
    ".nit-line { color: #666666 }\n" \
    "</STYLE>\n" \
    "</HEAD>\n" \
    "<BODY>\n" \
    "<HEADER>\n" \
    "<H1 class=\"nit-title\">{{prog-abbrev}} report for {{context-root}}</H1>\n" \
    "</HEADER>\n" \
    "<MAIN>\n" \
    "<BR><BR>\n" \
    "\n" \
    "[doc-foot]\n" \
    "<BR><BR>\n" \
    "<A href=\"/index.html\">previous page</A>\n" \
    "</MAIN>\n" \
    "<HR>\n" \
    "<FOOTER class=\"smaller\">\n" \
    "<A href=\"{{prog-addr}}\" class=\"ssc-name\">{{prog-fullname}}</A> version {{prog-version}}<BR>\n" \
    "<A href=\"{{copyright-addr}}\" class=\"ssc-copyright\">{{copyright-text}}</A>\n" \
    "</FOOTER>\n" \
    "</BODY>\n" \
    "</HTML>\n" \
    "\n" \
    "[export]\n" \
    "<SPAN class=\"nit-name\">{{nit-explanation}}</SPAN> <SPAN class=\"nit-id\">[{{nit-id}}]</SPAN><BR>\n" \
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
    "[id]\n" \
    "<SPAN class=\"nit-name\">{{id-name}}</SPAN> <SPAN class=\"nit-id\">({{id-page}}:{{id-line}})</SPAN><BR>\n" \
    "\n" \
    "[id-head]\n" \
    "<H2 class=\"nit-section\">Item IDs</H2>\n" \
    "<P>\n" \
    "\n" \
    "[id-foot]\n" \
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
    "<SPAN class=\"nit-level\">{{level-symbol}}</SPAN> <SPAN class=\"nit-explanation\">{{nit-explanation}}</SPAN> <SPAN class=\"nit-id\">[{{nit-id}}]</SPAN><BR>\n" \
    "\n" \
    "[nits-head]\n" \
    "<H3><SPAN class=\"nit-line\">{{nit-line}}</SPAN> {{nit-before:<SPAN class=\"nit-before\">:</SPAN> }}<SPAN class=\"nit-mote\">{{nit-mote}}</SPAN>{{nit-after: <SPAN class=\"nit-after\">:</SPAN>}}</H3>\n" \
    "<P>\n" \
    "\n" \
    "[nits-page]\n" \
    "<P>\n" \
    "\n" \
    "[nits-foot]\n" \
    "</P>\n" \
    "\n" \
    "[page-head]\n" \
    "<H2 class=\"nit-section\">{{page-path}}</H2>\n" \
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
    "\n" \
    "[webmention]\n" \
    "<SPAN class=\"nit-name\">{{nit-explanation}}</SPAN> <SPAN class=\"nit-id\">[{{nit-id}}]</SPAN><BR>\n" \
    "\n" \
    "[webmention-head]\n" \
    "<H2 class=\"nit-section\">webmentions</H2>\n" \
    "<P>\n" \
    "\n" \
    "[webmention-foot]\n" \
    "</P>\n" \
    "\n" \


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
    res += '\"';
    return res; }

::std::string encsv (const ::std::string& s)
{   if (s.find (',') == ::std::string::npos) return s;
    ::std::string res (1, '"');
    for (::std::string::const_iterator i = s.begin (); i != s.end (); ++i)
        if (*i == '\"') res += "\"\"";
        else if (*i == '\\') res += "\\\\";
        else res += *i;
    res += '\"';
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

::std::string nit_content (const ::std::string& s)
{   switch (context.quote_style ())
    {   case qs_c : return enc (s);
        case qs_csv : return encsv (s);
        case qs_double : return endouble (s, '"');
        case qs_html : return enhtml (s);
        case qs_single : return endouble (s, '\'');
        default : return s; } }

bool is_template_loaded ()
{ return ! sections.empty (); }

void init_nit_macros ()
{   mmac_t& m = context.macros ();
    m.emplace (nm_prog_abbrev, PROG);
    m.emplace (nm_copy_addr, COPYRIGHT_WEBADDR);
    m.emplace (nm_copy_html, COPYRIGHT_HTML);
    m.emplace (nm_copy_text, COPYRIGHT_TEXT);
    m.emplace (nm_prog_fullname, FULLNAME);
    m.emplace (nm_prog_version, VERSION_STRING);
    m.emplace (nm_prog_webaddr, WEBADDR); }

bool load_template_int (nitpick& nits, const html_version& v, const ::std::string& config)
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
                        sections [ns] = ::std::string (sect_begin, i-1);
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
                        context.err (msg);
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
                newline = true;
                if (apres)
                {   sect_begin = i+1;
                    apres = false; }
                break;
            default :
                newline = false;
                break; }
    return res; }

bool load_template (nitpick& nits, const html_version& v)
{   const ::std::string& format = context.nit_format ();
    ::std::string config;
    bool res = false;
    if (context.test ()) res = load_template_int (nits, v, TEST_NIT);
    else
    {   if (! format.empty ())
        {   config = template_path ("out.nit", format);
            if (! config.empty ()) res = load_template_int (nits, v, config);
            if (! res)
            {   context.err () << "Cannot process " << quote (format) << ", reverting to default output format.\n";
                nits.pick (nit_template_file, es_catastrophic, ec_init, "Cannot process ", quote (format), ", reverting to default output format)"); } }
        if (! res)
            if (! context.snippet ().empty ()) res = load_template_int (nits, v, HTML_NIT);
            else res = load_template_int (nits, v, TEXT_NIT); }
    PRESUME (res, __FILE__, __LINE__);
    return res; }

::std::string apply_macros_int (const ::std::string& tpl, const mmac_t& values)
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
        ::std::string macro = tpl.substr (pos+len, epos-pos-len);
        if (! macro.empty ())
        {   ::std::string b,a;
            ::std::string::size_type bp = macro.find_first_not_of (MACID);
            if (bp != ::std::string::npos)
            {   char ch = macro [bp];
                b = macro.substr (bp+1);
                macro = macro.substr (0, bp);
                ::std::string::size_type ap = b.find (ch);
                if (ap != ::std::string::npos)
                {   a = b.substr (ap+1);
                    b = b.substr (0, ap); } }
            e_nit_macro m = examine_value < t_nit_macro > (nuts, html_default, macro);
            if (m != nm_none)
            {   mmac_t::const_iterator ci = values.find (m);
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

::std::string apply_macros (const e_nit_section& sct)
{   PRESUME (static_cast < ::std::size_t > (sct) < sections.size (), __FILE__, __LINE__);
    return apply_macros_int (sections.at (sct), context.macros ()); }

::std::string apply_macros (const e_nit_section& sct, const mmac_t& values)
{   PRESUME (static_cast < ::std::size_t > (sct) < sections.size (), __FILE__, __LINE__);
    return apply_macros_int (apply_macros (sct), values); }

::std::string apply_macros (const e_nit_section& sct, const mmac_t& values1, const mmac_t& values2)
{   PRESUME (static_cast < ::std::size_t > (sct) < sections.size (), __FILE__, __LINE__);
    return apply_macros_int (apply_macros (sct, values1), values2); }

::std::string apply_macros (const e_nit_section& sct, const mmac_t& values1, const mmac_t& values2, const mmac_t& values3)
{   PRESUME (static_cast < ::std::size_t > (sct) < sections.size (), __FILE__, __LINE__);
    return apply_macros_int (apply_macros (sct, values1, values2), values3); }

::std::string apply_macros (const e_nit_section& sct, const mmac_t& values1, const mmac_t& values2, const mmac_t& values3, const mmac_t& values4)
{   PRESUME (static_cast < ::std::size_t > (sct) < sections.size (), __FILE__, __LINE__);
    return apply_macros_int (apply_macros (sct, values1, values2, values3), values4); }

void dump_nits (nitpick& nits, const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot)
{   if (! nits.empty ())
#ifdef NDEBUG
        if (context.tell (static_cast < e_verbose > (nits.worst ())))
#endif // NDEBUG
            context.out () << nits.review (entry, head, foot);
    nits.reset (); }
