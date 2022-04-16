/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "stats/stats.h"
#include "stats/stats_impl.h"
#include "main/context.h"
#include "feedback/nitpick.h"
#include "microdata/microdata_itemprop.h"
#include "microdata/microdata_itemtype.h"
#include "schema/schema_name.h"
#include "type/type_httpequiv.h"
#include "type/type_metaname.h"

void stats::mark_file (const unsigned size) noexcept
{   ++file_count_;
    if (size < smallest_) smallest_ = size;
    if (size > biggest_) biggest_ = size;
    file_size_ += size; }

::std::string times (const uint64_t n)
{   switch (n)
    {   case 0: return "none";
        case 1: return "once";
        case 2: return "twice";
        case 3: return "thrice";
        default: return ::boost::lexical_cast < ::std::string > (n) + " times"; } }

::std::string saybe (const unsigned n, const ::std::string& msg)
{   if (n == 0) return ::std::string ();
    return msg + ": " + times (n) + "\n"; }

mmac_t mac_init (const ::std::string& naam, const ::std::string& detail = ::std::string ())
{   mmac_t mac;
    mac.emplace (nm_stat_name, naam);
    mac.emplace (nm_stat_count, "");
    mac.emplace (nm_stat_int, "");
    mac.emplace (nm_stat_detail, detail);
    return mac; }

mmac_t mac_init (const ::std::string& naam, const int n, const ::std::string& detail = ::std::string ())
{   mmac_t mac;
    mac.emplace (nm_stat_name, naam);
    mac.emplace (nm_stat_count, times (n));
    mac.emplace (nm_stat_int, ::boost::lexical_cast < ::std::string > (n));
    mac.emplace (nm_stat_detail, detail);
    return mac; }

mmac_t mac_subinit (const ::std::string& naam, const ::std::string& detail = ::std::string ())
{   mmac_t mac;
    mac.emplace (nm_stat_subname, naam);
    mac.emplace (nm_stat_subcount, "");
    mac.emplace (nm_stat_subint, "");
    mac.emplace (nm_stat_subdetail, detail);
    return mac; }

mmac_t mac_subinit (const ::std::string& naam, const int n, const ::std::string& detail = ::std::string ())
{   mmac_t mac;
    mac.emplace (nm_stat_subname, naam);
    mac.emplace (nm_stat_subcount, times (n));
    mac.emplace (nm_stat_subint, ::boost::lexical_cast < ::std::string > (n));
    mac.emplace (nm_stat_subdetail, detail);
    return mac; }

::std::string saybe (const mmac_t& table, const unsigned n, const ::std::string& msg)
{   ::std::string res;
    if (n > 0)
        res += macro.apply (ns_stat, table, mac_init (msg, n));
    return res; }

mmac_t mac_title (const ::std::string& title, const ::std::string& total = ::std::string ())
{   mmac_t mac;
    mac.emplace (nm_stats_title, title);
    mac.emplace (nm_stats_total, total);
    return mac; }

mmac_t mac_subtitle (const ::std::string& title)
{   mmac_t mac;
    mac.emplace (nm_stats_subtitle, title);
    return mac; }

::std::string stats::ontology_report () const
{   mmac_t table = mac_title ("Ontology");
    ::std::string res;
    uint64_t total = 0;
    unsigned count = 0;
    for (unsigned i = 0; i < sty_illegal; ++i)
    {   const unsigned n = schema_.at (static_cast < e_schema_type > (i));
        if (n == 0) continue;
        ++total;
        count += n;
        if (context.tell (es_error))
        {   mmac_t stat = mac_init (itemtype_index_name (make_itemtype_index (static_cast < e_schema_type > (i))), n);
            const unsigned x = schema_property_.family (static_cast < e_schema_type > (i));
            if (x > 0) stat.emplace (nm_stat_detail, ::boost::lexical_cast < ::std::string > (x / n));
            res += macro.apply (ns_stat, table, stat);
            if (context.tell (es_info))
                for (unsigned m = 0; m < sp_illegal; ++m)
                {   const unsigned y = schema_property_.at (static_cast < e_schema_type > (i), static_cast <e_schema_property> (m));
                    if (y > 0)
                    {   mmac_t mac = mac_subinit (itemprop_index_name (make_itemprop_index (static_cast <e_schema_property> (m))), y);
                        res += macro.apply (ns_substat, table, stat, mac); } } } }
    if (context.tell (es_warning))
    {   mmac_t stat = mac_subtitle ("Property counts");
        ::std::string att;
        for (unsigned m = 0; m < sp_illegal; ++m)
        {   const unsigned x = schema_property_.member (static_cast <e_schema_property> (m));
            if (x > 0)
            {   mmac_t item = mac_init (schema_property_name (static_cast <e_schema_property> (m)), x);
                att += macro.apply (ns_stat, table, stat, item); } }
        if (! att.empty ())
            res += macro.apply (ns_stats_subhead, table, stat) + att + macro.apply (ns_stats_subfoot, table, stat); }
    mmac_t finish;
    ::std::string sum (::boost::lexical_cast < ::std::string > (total) + " itemtype");
    if (total != 1) sum += "s";
    sum += " used " + times (count);
    finish.emplace (nm_stats_total, sum);
    if (! res.empty ()) res = macro.apply (ns_stats_head, finish, table) + res + macro.apply (ns_stats_foot, finish, table);
    return res; }

::std::string stats::element_report () const
{   mmac_t table = mac_title ("Elements");
    ::std::string res;
    uint64_t total = 0;
    unsigned count = 0;
    for (unsigned i = 0; i < last_element_tag; ++i)
    {   const unsigned n = element_.at (i);
        if (n == 0) continue;
        ++total;
        count += n;
        if (context.tell (es_comment) || (context.tell (es_error) && ((elem::categories (i) & EF_FAUX) == 0)))
        {   mmac_t stat = mac_init (elem::name (i), n);
            if (! context.tell (es_info))
            {   const unsigned x = attribute_.family (i);
                if (x > 0)
                {   ::std::string average ("on average ");
                    average += ::boost::lexical_cast < ::std::string > (x / n);
                    average += " attribute";
                    if (x > 1) average += "s";
                    stat.emplace (nm_stat_detail, average); }
                res += macro.apply (ns_stat, table, stat); }
            else
            {   res += macro.apply (ns_stat, table, stat);
                for (unsigned m = 0; m < last_attribute; ++m)
                {   const unsigned y = attribute_.at (i, static_cast <e_attribute> (m));
                    if (y > 0)
                    {   mmac_t mac = mac_subinit (attr::name (static_cast <e_attribute> (m)), y);
                        res += macro.apply (ns_substat, table, stat, mac); } } } } }
    if (context.tell (es_warning))
    {   mmac_t stat = mac_subtitle ("Attribute counts");
        ::std::string att;
        for (unsigned m = 0; m < last_attribute; ++m)
        {   const unsigned x = attribute_.member (static_cast <e_attribute> (m));
            if (x > 0)
            {   mmac_t item = mac_init (attr::name (static_cast <e_attribute> (m)), x);
                att += macro.apply (ns_stat, table, stat, item); } }
        if (! att.empty ()) res += macro.apply (ns_stats_subhead, table, stat) + att + macro.apply (ns_stats_subfoot, table, stat); }
    mmac_t finish;
    ::std::string sum = ::boost::lexical_cast < ::std::string > (total) + " elements used " + times (count);
    finish.emplace (nm_stats_total, sum);
    if (! res.empty ()) res = macro.apply (ns_stats_head, finish, table) + res + macro.apply (ns_stats_foot, finish, table);
    return res; }

::std::string stats::version_report () const
{   mmac_t table = mac_title ("Versions");
    ::std::string res;
    for (auto ii = version_.count_.cbegin (); ii != version_.count_.cend (); ++ii)
        if (ii -> second > 0)
            res += macro.apply (ns_stat, macro.macros (), table, mac_init (ii -> first.report (), ii -> second));
    if (! res.empty ()) res = macro.apply (ns_stats_head, table) + res + macro.apply (ns_stats_foot, table);
    return res; }

::std::string stats::abbr_report () const
{   mmac_t table = mac_title ("Abbreviations");
    ::std::string res;
    for (auto i : abbr_.count_)
        if (i.second > 0) res += macro.apply (ns_stat, macro.macros (), table, mac_init (i.first.a_, i.second, i.first.b_));
    if (! res.empty ())  res = macro.apply (ns_stats_head, table) + res + macro.apply (ns_stats_foot, table);
    return res; }

::std::string stats::dfn_report () const
{   mmac_t table = mac_title ("Definitions");
    ::std::string res;
    for (auto i : dfn_.count_)
        if (i.second > 0)
        {   mmac_t stat = mac_init (i.first.a_, i.second, i.first.b_);
            res += macro.apply (ns_stat, macro.macros (), table, stat); }
    if (! res.empty ()) res = macro.apply (ns_stats_head, table) + res + macro.apply (ns_stats_foot, table);
    return res; }

::std::string stats::dtdd_report () const
{   mmac_t table = mac_title ("Name/Value pairs");
    ::std::string res;
    for (auto i : dtdd_.count_)
        if (i.second > 0)
        {   mmac_t stat = mac_init (i.first.a_, i.second, i.first.b_);
            res += macro.apply (ns_stat, macro.macros (), table, stat); }
    if (! res.empty ()) res = macro.apply (ns_stats_head, table) + res + macro.apply (ns_stats_foot, table);
    return res; }

::std::string stats::error_report () const
{   mmac_t table = mac_title ("Nits Reported");
    ::std::string res;
    res += saybe (table, severity_.at (es_catastrophic), "Catastrophes");
    if (context.tell (es_error)) res += saybe (table, severity_.at (es_error), "Errors");
    if (context.tell (es_warning)) res += saybe (table, severity_.at (es_warning), "Warnings");
    if (context.tell (es_info)) res += saybe (table, severity_.at (es_info), "Info");
    if (context.tell (es_comment)) res += saybe (table, severity_.at (es_comment), "Comments");
    if (! res.empty ())
        res = macro.apply (ns_stats_head, table) + res + macro.apply (ns_stats_foot, table);
    return res; }

::std::string stats::category_report () const
{   mmac_t table = mac_title ("Nit Categories");
    ::std::string res;
    res += saybe (table, category_.at (ec_html), "HTML");
    res += saybe (table, category_.at (ec_aria), "Aria");
    res += saybe (table, category_.at (ec_attribute), "Attribute");
    res += saybe (table, category_.at (ec_crc), "CRC");
    res += saybe (table, category_.at (ec_css), "CSS");
    res += saybe (table, category_.at (ec_directory), "Directory");
    res += saybe (table, category_.at (ec_element), "Element");
    res += saybe (table, category_.at (ec_file), "File");
    res += saybe (table, category_.at (ec_incorrectness), "Incorrectness");
    res += saybe (table, category_.at (ec_icu), "ICU");
    res += saybe (table, category_.at (ec_init), "Init");
    res += saybe (table, category_.at (ec_io), "I/O");
    res += saybe (table, category_.at (ec_json), "JSON");
    res += saybe (table, category_.at (ec_link), "Link");
    res += saybe (table, category_.at (ec_microdata), "Microdata");
    res += saybe (table, category_.at (ec_microformat), "Microformat");
    res += saybe (table, category_.at (ec_mime), "Mimetype");
    res += saybe (table, category_.at (ec_mql), "Media Query");
    res += saybe (table, category_.at (ec_namespace), "Namespace");
    res += saybe (table, category_.at (ec_page), "Page");
    res += saybe (table, category_.at (ec_parser), "Parser");
    res += saybe (table, category_.at (ec_program), "Program");
    res += saybe (table, category_.at (ec_rdfa), "RDFa");
    res += saybe (table, category_.at (ec_regex), "Regex");
    res += saybe (table, category_.at (ec_rudeness), "Rudeness");
    res += saybe (table, category_.at (ec_schema), "Schema");
    res += saybe (table, category_.at (ec_shadow), "Shadow");
    res += saybe (table, category_.at (ec_spell), "Spelling");
    res += saybe (table, category_.at (ec_ssi), "SSI");
    res += saybe (table, category_.at (ec_tidyness), "Tidyness");
    res += saybe (table, category_.at (ec_type), "Type");
    res += saybe (table, category_.at (ec_url), "URx");
    res += saybe (table, category_.at (ec_utility), "Utility");
    if (! res.empty ()) res = macro.apply (ns_stats_head, table) + res + macro.apply (ns_stats_foot, table);
    return res; }

::std::string stats::file_report () const
{   ::std::string res;
    if (context.tell (es_warning)) res = ::boost::lexical_cast < ::std::string > (file_size_) + " bytes read in ";
    res += ::boost::lexical_cast < ::std::string > (file_count_) + " HTML files, with an average of roughly ";
    res += ::boost::lexical_cast < ::std::string > (static_cast < int > (floor (file_size_ / file_count_ + 0.5)));
    res += " bytes per file";
    mmac_t table = mac_title ("File info");
    mmac_t stat = mac_init ("", res);
    res = macro.apply (ns_stat, table, stat);
    if (context.tell (es_error))
    {   ::std::string app = "smallest file: " + ::boost::lexical_cast < ::std::string > (smallest_) + " bytes, ";
        app += "largest file: " + ::boost::lexical_cast < ::std::string > (biggest_) + " bytes";
        mmac_t x = mac_init ("", app);
        res += macro.apply (ns_stat, table, x); }
    res = macro.apply (ns_stats_head, table) + res + macro.apply (ns_stats_foot, table);
    return res; }

::std::string stats::reference_report () const
{   mmac_t table = mac_title ("References");
    ::std::string res;
    for (unsigned int d = 1; d <= last_doc; ++d)
    {   const int x = ref_.at (static_cast <e_doc> (d));
        if (x > 0)
        {   mmac_t stat = mac_init (doc_title (static_cast <e_doc> (d)), x);
            res += macro.apply (ns_stat, macro.macros (), table, stat); } }
    if (! res.empty ()) res = macro.apply (ns_stats_head, table) + res + macro.apply (ns_stats_foot, table);
    return res; }

::std::string stats::meta_report () const
{   mmac_t table = mac_title ("Headers");
    ::std::string res;
    if (context.meta ())
    {   ::std::string sub;
        mmac_t stat1 = mac_subtitle ("pragma");
        for (unsigned i = 0; i < he_error; ++i)
        {   const unsigned n = httpequiv_.at (static_cast < e_httpequiv > (i));
            if (n)
            {   mmac_t item = mac_init (enum_n < t_httpequiv, e_httpequiv > :: name (static_cast < e_httpequiv > (i)), n);
                sub += macro.apply (ns_stat, table, stat1, item); } }
        if (! sub.empty ())
        {   res += macro.apply (ns_stats_subhead, table, stat1) + sub + macro.apply (ns_stats_subfoot, table, stat1);
            sub.clear (); }
        mmac_t stat2 = mac_subtitle ("metadata");
        for (unsigned i = 0; i < mn_illegal; ++i)
        {   const unsigned n = metaname_.at (static_cast < e_metaname > (i));
            if (n)
            {   mmac_t item = mac_init (enum_n < t_metaname, e_metaname > :: name (static_cast < e_metaname > (i)), n);
                sub += macro.apply (ns_stat, table, stat2, item); } }
        if (! sub.empty ())
        {   res += macro.apply (ns_stats_subhead, table, stat2) + sub + macro.apply (ns_stats_subfoot, table, stat2);
            sub.clear (); }
        mmac_t stat3 = mac_subtitle ("name");
        for (unsigned i = 0; i < mn_illegal; ++i)
        {   mmac_t layer = mac_init (enum_n < t_metaname, e_metaname > :: name (static_cast < e_metaname > (i)));
            ::std::string ss;
            for (   auto k = meta_value_.at (static_cast < e_metaname > (i)).cbegin ();
                    k != meta_value_.at (static_cast < e_metaname > (i)).cend ();
                    ++k)
            {   mmac_t item = mac_subinit (k -> first, k -> second);
                ss += macro.apply (ns_substat, table, stat3, layer, item); }
            if (! ss.empty ())
            {   sub += macro.apply (ns_stat, table, stat3, layer) + ss;
                ss.clear (); } }
        if (! sub.empty ())
        {   res += macro.apply (ns_stats_subhead, table, stat3) + sub + macro.apply (ns_stats_subfoot, table, stat3);
            sub.clear (); } }
    if (! res.empty ()) res = macro.apply (ns_stats_head, table) + res + macro.apply (ns_stats_foot, table);
    return res; }

::std::string stats::report (const bool grand) const
{   ::std::string res;
    if ((context.verbose () == es_undefined) || (context.verbose () == es_illegal)) return res;
    mmac_t g;
    if (grand) g.emplace (nm_grand_title, "Grand Totals");
    else g.emplace (nm_grand_title, "Statistics");
    res += macro.apply (ns_grand_head, g);
    res += element_report ();
    res += ontology_report ();
    res += meta_report ();
    res += abbr_report ();
    res += dfn_report ();
    res += dtdd_report ();
    if (grand)
    {   res += error_report ();
        if (file_count_ > 1)
        {   res += category_report ();
            res += reference_report ();
            res += version_report ();
            res += file_report (); } }
    res += macro.apply (ns_grand_foot, g);
    return res; }

bool stats::severity_exceeded () const
{   for (int x = 1; x <= static_cast < int > (context.report_error ()); ++x)
        if (element_count (static_cast < e_severity> (x))) return true;
    return false; }
