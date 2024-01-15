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
#include "stats/stats.h"
#include "stats/stats_impl.h"
#include "main/context.h"
#include "feedback/nitpick.h"
#include "microdata/microdata_itemprop.h"
#include "microdata/microdata_itemtype.h"
#include "ontology/ontology_name.h"
#include "type/type.h"

void stats::mark_file (const unsigned size) noexcept
{   ++file_count_;
    if (size < smallest_) smallest_ = size;
    if (size > biggest_) biggest_ = size;
    file_size_ += size; }

::std::string saybe (const unsigned n, const ::std::string& msg)
{   if (n == 0) return ::std::string ();
    return msg + ": " + once_twice_thrice (n) + "\n"; }

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
    mac.emplace (nm_stat_count, once_twice_thrice < int, INT_MAX > (n));
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
    mac.emplace (nm_stat_subcount, once_twice_thrice < int, INT_MAX > (n));
    mac.emplace (nm_stat_subint, ::boost::lexical_cast < ::std::string > (n));
    mac.emplace (nm_stat_subdetail, detail);
    return mac; }

::std::string saybe (const mmac_t& table, const unsigned n, const ::std::string& msg)
{   ::std::string res;
    if (n > 0)
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        res += macro -> apply (ns_stat, table, mac_init (msg, n)); }
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
{   mmac_t table = mac_title (REPORT_ONTOLOGY);
    ::std::string res;
    uint64_t total = 0;
    unsigned count = 0;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    if (context.stats_ontology ())
        for (unsigned i = 0; i < ont_illegal; ++i)
        {   const unsigned n = ontology_.at (static_cast < e_ontology_type > (i));
            if (n == 0) continue;
            ++total;
            count += n;
            if (context.tell (es_error))
            {   mmac_t stat = mac_init (itemtype_index_name (make_itemtype_index (static_cast < e_ontology_type > (i))), n);
                const unsigned x = ontology_property_.family (static_cast < e_ontology_type > (i));
                if (x > 0) stat.emplace (nm_stat_detail, ::boost::lexical_cast < ::std::string > (x / n));
                res += macro -> apply (ns_stat, table, stat);
                if (context.tell (es_info))
                    for (unsigned m = 0; m < op_illegal; ++m)
                    {   const unsigned y = ontology_property_.at (static_cast < e_ontology_type > (i), static_cast <e_ontology_property> (m));
                        if (y > 0)
                        {   mmac_t mac = mac_subinit (itemprop_index_name (make_itemprop_index (static_cast <e_ontology_property> (m))), y);
                            res += macro -> apply (ns_substat, table, stat, mac); } } } }
    if (context.stats_property ())
    {   mmac_t stat = mac_subtitle (REPORT_PROPERTY " counts");
        ::std::string att;
        for (unsigned m = 0; m < op_illegal; ++m)
        {   const unsigned x = ontology_property_.member (static_cast <e_ontology_property> (m));
            if (x > 0)
            {   mmac_t item = mac_init (ontology_property_name (static_cast <e_ontology_property> (m)), x);
                att += macro -> apply (ns_stat, table, stat, item); } }
        if (! att.empty ())
            res += macro -> apply (ns_stats_subhead, table, stat) + att + macro -> apply (ns_stats_subfoot, table, stat); }
    mmac_t finish;
    ::std::string sum (::boost::lexical_cast < ::std::string > (total) + " itemtype");
    if (total != 1) sum += "s";
    sum += " used " + once_twice_thrice < unsigned > (count);
    finish.emplace (nm_stats_total, sum);
    if (! res.empty ()) res = macro -> apply (ns_stats_head, finish, table) + res + macro -> apply (ns_stats_foot, finish, table);
    return res; }

::std::string stats::element_report () const
{   mmac_t table = mac_title (REPORT_ELEMENT);
    ::std::string res;
    uint64_t total = 0;
    unsigned count = 0;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    if (context.stats_element ())
        for (unsigned i = 0; i < last_element_tag; ++i)
        {   const unsigned n = element_.at (i);
            if (n == 0) continue;
            ++total;
            count += n;
            if (context.tell (es_comment) || ((elem::categories (i) & EF_FAUX) == 0))
            {   mmac_t stat = mac_init (elem::name (i), n);
                if (! context.stats_attribute ())
                {   const unsigned x = attribute_.family (i);
                    if (x > 0)
                    {   ::std::string average ("on average ");
                        average += ::boost::lexical_cast < ::std::string > (x / n);
                        average += " attribute";
                        if (x > 1) average += "s";
                        stat.emplace (nm_stat_detail, average); }
                    res += macro -> apply (ns_stat, table, stat); }
                else
                {   res += macro -> apply (ns_stat, table, stat);
                    for (unsigned m = 0; m < last_attribute; ++m)
                    {   const unsigned y = attribute_.at (i, static_cast <e_attribute> (m));
                        if (y > 0)
                        {   mmac_t mac = mac_subinit (attr::name (static_cast <e_attribute> (m)), y);
                            res += macro -> apply (ns_substat, table, stat, mac); } } } } }
    if (context.stats_attribute ())
    {   mmac_t stat = mac_subtitle (REPORT_ATTRIBUTE " count");
        ::std::string att;
        for (unsigned m = 0; m < last_attribute; ++m)
        {   const unsigned x = attribute_.member (static_cast <e_attribute> (m));
            if (x > 0)
            {   mmac_t item = mac_init (attr::name (static_cast <e_attribute> (m)), x);
                att += macro -> apply (ns_stat, table, stat, item); } }
        if (! att.empty ()) res += macro -> apply (ns_stats_subhead, table, stat) + att + macro -> apply (ns_stats_subfoot, table, stat); }
    mmac_t finish;
    ::std::string sum = ::boost::lexical_cast < ::std::string > (total) + " elements used " + once_twice_thrice < uint64_t > (count);
    finish.emplace (nm_stats_total, sum);
    if (! res.empty ()) res = macro -> apply (ns_stats_head, finish, table) + res + macro -> apply (ns_stats_foot, finish, table);
    return res; }

::std::string stats::version_report () const
{   mmac_t table = mac_title (REPORT_VERSION);
    ::std::string res;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    for (auto ii = version_.count_.cbegin (); ii != version_.count_.cend (); ++ii)
        if (ii -> second > 0)
            res += macro -> apply (ns_stat, macro -> macros (), table, mac_init (ii -> first.report (), ii -> second));
    if (! res.empty ()) res = macro -> apply (ns_stats_head, table) + res + macro -> apply (ns_stats_foot, table);
    return res; }

::std::string stats::abbr_report () const
{   mmac_t table = mac_title (REPORT_ABRREVIATION);
    ::std::string res;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    for (auto i : abbr_.count_)
        if (i.second > 0) res += macro -> apply (ns_stat, macro -> macros (), table, mac_init (i.first.a_, i.second, quote (i.first.b_)));
    if (! res.empty ())  res = macro -> apply (ns_stats_head, table) + res + macro -> apply (ns_stats_foot, table);
    return res; }

::std::string stats::custom_media_report () const
{   mmac_t table = mac_title (REPORT_CUSTARD_MEDIA);
    ::std::string res;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    for (auto i : custom_media_.count_)
        if (i.second > 0)
        {   mmac_t stat = mac_init (i.first.a_, i.second, i.first.b_);
            res += macro -> apply (ns_stat, macro -> macros (), table, stat); }
    if (! res.empty ()) res = macro -> apply (ns_stats_head, table) + res + macro -> apply (ns_stats_foot, table);
    return res; }

::std::string stats::definition_report () const
{   mmac_t table = mac_title (REPORT_DEFINITION);
    ::std::string res;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    for (auto i : dfn_.count_)
        if (i.second > 0)
        {   mmac_t stat = mac_init (i.first.a_, i.second, quote (i.first.b_));
            res += macro -> apply (ns_stat, macro -> macros (), table, stat); }
    if (! res.empty ()) res = macro -> apply (ns_stats_head, table) + res + macro -> apply (ns_stats_foot, table);
    return res; }

::std::string stats::value_pair_report () const
{   mmac_t table = mac_title (REPORT_NAME_VALUE " Pair");
    ::std::string res;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    for (auto i : dtdd_.count_)
        if (i.second > 0)
        {   mmac_t stat = mac_init (i.first.a_, i.second, quote (i.first.b_));
            res += macro -> apply (ns_stat, macro -> macros (), table, stat); }
    if (! res.empty ()) res = macro -> apply (ns_stats_head, table) + res + macro -> apply (ns_stats_foot, table);
    return res; }

::std::string stats::error_report () const
{   mmac_t table = mac_title (REPORT_NITS " Reported");
    ::std::string res;
    res += saybe (table, severity_.at (es_catastrophic), "Catastrophes");
    if (context.tell (es_abhorrent)) { res += saybe (table, severity_.at (es_abhorrent), "Abhorrences");
        if (context.tell (es_error)) { res += saybe (table, severity_.at (es_error), "Errors");
            if (context.tell (es_warning)) { res += saybe (table, severity_.at (es_warning), "Warnings");
                if (context.tell (es_info)) { res += saybe (table, severity_.at (es_info), "Info");
                    if (context.tell (es_comment)) { res += saybe (table, severity_.at (es_comment), "Comments");
#ifdef _DEBUG
                        if (context.tell (es_debug)) { res += saybe (table, severity_.at (es_debug), "Debug");
                            if (context.tell (es_variable)) { res += saybe (table, severity_.at (es_variable), "Variables");
                                if (context.tell (es_structure)) { res += saybe (table, severity_.at (es_structure), "Structure");
                                    if (context.tell (es_detail)) { res += saybe (table, severity_.at (es_detail), "Details");
                                        if (context.tell (es_splurge)) { res += saybe (table, severity_.at (es_splurge), "Splurge");
                                            if (context.tell (es_all)) res += saybe (table, severity_.at (es_all), "All");
                                        } } } } }
#endif // _DEBUG
                    } } } } }
    if (! res.empty ())
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        res = macro -> apply (ns_stats_head, table) + res + macro -> apply (ns_stats_foot, table); }
    return res; }

::std::string stats::property_report () const
{   mmac_t table = mac_title (REPORT_PROPERTY);
    ::std::string res;
    unsigned count = 0, total = 0;
    for (unsigned int d = 1; d <= ec_error; ++d)
    {   const int x = css_property_.at (static_cast <e_css_property> (d));
        if (x > 0)
        {   ++total;
            count += x;
            mmac_t stat = mac_init (enum_n < t_css_property, e_css_property > :: name (static_cast < e_css_property > (d)), x);
            res += macro -> apply (ns_stat, macro -> macros (), table, stat); } }
    mmac_t finish;
    ::std::string sum = ::boost::lexical_cast < ::std::string > (total) + " properties used " + once_twice_thrice < uint64_t > (count);
    finish.emplace (nm_stats_total, sum);
    if (! res.empty ()) res = macro -> apply (ns_stats_head, finish, table) + res + macro -> apply (ns_stats_foot, finish, table);
    return res; }

::std::string stats::statement_report () const
{   mmac_t table = mac_title (REPORT_STATEMENT);
    ::std::string res;
    unsigned count = 0, total = 0;
    for (unsigned int d = 1; d <= css_error; ++d)
    {   const int x = css_statement_.at (static_cast <e_css_statement> (d));
        if (x > 0)
        {   ++total;
            count += x;
            mmac_t stat = mac_init (enum_n < t_css_statement, e_css_statement > :: name (static_cast < e_css_statement > (d)), x);
            res += macro -> apply (ns_stat, macro -> macros (), table, stat); } }
    mmac_t finish;
    ::std::string sum = ::boost::lexical_cast < ::std::string > (total) + " statements used " + once_twice_thrice < uint64_t > (count);
    finish.emplace (nm_stats_total, sum);
    if (! res.empty ()) res = macro -> apply (ns_stats_head, finish, table) + res +macro -> apply (ns_stats_foot, finish, table);
    return res; }

const char* str_name [] =
{   REPORT_ANNOTATION,
    REPORT_CHARACTER,
    REPORT_CONTENT,
    REPORT_COUNTER,
    REPORT_FAMILY,
    REPORT_HIGHLIGHT,
    REPORT_HISTORICAL,
    REPORT_KEYFRAME,
    REPORT_LAYER,
    REPORT_ORNAMENT,
    REPORT_PAGE_NAME,
    REPORT_PALETTE,
    REPORT_REGION,
    REPORT_SCROLL,
    REPORT_STYLESET,
    REPORT_STYLISTIC,
    REPORT_SWASH,
    REPORT_VIEW,
    nullptr };

::std::string stats::css_str_report (const e_gsstr gst) const
{   PRESUME (gst < gst_max, __FILE__, __LINE__);
    VERIFY_NOT_NULL (GSL_AT (str_name, gst), __FILE__, __LINE__);
    const ::std::string name (GSL_AT (str_name, gst));
    mmac_t table;
    table.emplace (nm_note_title, name);
    ::std::string res;
    if (! str_.at (gst).empty ())
    {   int n = 0;
        for (auto i = str_.at (gst).cbegin (); i != str_.at (gst).cend (); ++i)
        {   ++n;
            mmac_t stat;
            stat.emplace (nm_note_content, *i);
            res += macro -> apply (ns_note, macro -> macros (), table, stat); }
        if (n < 2) table.emplace (nm_note_note, "");
        else
        {   const ::std::string sum = ::std::string ("Used ") + once_twice_thrice (str_.at (gst).size ());
            table.emplace (nm_note_note, sum); }
        res = macro -> apply (ns_note_head, table) + res + macro -> apply (ns_note_foot, table); }
    return res; }

::std::string stats::category_report () const
{   mmac_t table = mac_title (REPORT_CAREGORY);
    ::std::string res;
    res += saybe (table, category_.at (ec_html), "HTML");
    res += saybe (table, category_.at (ec_aria), "Aria");
    res += saybe (table, category_.at (ec_attribute), "Attribute");
    res += saybe (table, category_.at (ec_cache), "Cache");
    res += saybe (table, category_.at (ec_corpus), "Corpus");
    res += saybe (table, category_.at (ec_crc), "CRC");
    res += saybe (table, category_.at (ec_css), "CSS");
    res += saybe (table, category_.at (ec_directory), "Directory");
    res += saybe (table, category_.at (ec_element), "Element");
    res += saybe (table, category_.at (ec_file), "File");
    res += saybe (table, category_.at (ec_icu), "ICU");
    res += saybe (table, category_.at (ec_incorrectness), "Incorrectness");
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
    res += saybe (table, category_.at (ec_fred), "Thread");
    res += saybe (table, category_.at (ec_tidyness), "Tidyness");
    res += saybe (table, category_.at (ec_type), "Type");
    res += saybe (table, category_.at (ec_url), "URx");
    res += saybe (table, category_.at (ec_utility), "Utility");
    if (! res.empty ())
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        res = macro -> apply (ns_stats_head, table) + res + macro -> apply (ns_stats_foot, table); }
    return res; }

::std::string stats::file_report () const
{   ::std::string res;
    mmac_t stat, s2;
    mmac_t table;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    table.emplace (nm_note_title, "File Info");
    table.emplace (nm_note_note, "");
    if (file_count_ == 1)
    {   res = ::boost::lexical_cast < ::std::string > (file_size_) + " bytes read in one file";
        stat.emplace (nm_note_content, res);
        res = macro -> apply (ns_note, stat); }
    else
    {   const ::std::string r  = ::boost::lexical_cast < ::std::string > (file_size_) + " bytes read in " +
                                 ::boost::lexical_cast < ::std::string > (file_count_) + " files, with an average of roughly " +
                                 ::boost::lexical_cast < ::std::string > (static_cast < int > (floor (file_size_ / file_count_ + 0.5))) +
                                 " bytes per file";
        const ::std::string sl = "smallest file: " + ::boost::lexical_cast < ::std::string > (smallest_) + " bytes, largest file: " + 
                                 ::boost::lexical_cast < ::std::string > (biggest_) + " bytes";
        stat.emplace (nm_note_content, r);
        s2.emplace (nm_note_content, sl);
        res = macro -> apply (ns_note, stat) + macro -> apply (ns_note, s2); }
    res = macro -> apply (ns_note_head, table) + res + macro -> apply (ns_note_foot, table);
    return res; }

::std::string stats::reference_report () const
{   mmac_t table = mac_title (REPORT_REFERENCE);
    ::std::string res;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    for (unsigned int d = 1; d <= last_doc; ++d)
    {   const int x = ref_.at (static_cast <e_doc> (d));
        if (x > 0)
        {   mmac_t stat = mac_init (doc_title (static_cast <e_doc> (d)), x);
            res += macro -> apply (ns_stat, macro -> macros (), table, stat); } }
    if (! res.empty ()) res = macro -> apply (ns_stats_head, table) + res + macro -> apply (ns_stats_foot, table);
    return res; }

::std::string stats::meta_report () const
{   mmac_t table = mac_title (REPORT_HEADER);
    ::std::string res;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    if (context.stats_meta ())
    {   ::std::string sub;
        mmac_t stat1 = mac_subtitle ("pragma");
        for (unsigned i = 0; i < he_error; ++i)
        {   const unsigned n = httpequiv_.at (static_cast < e_httpequiv > (i));
            if (n)
            {   mmac_t item = mac_init (enum_n < t_httpequiv, e_httpequiv > :: name (static_cast < e_httpequiv > (i)), n);
                sub += macro -> apply (ns_stat, table, stat1, item); } }
        if (! sub.empty ())
        {   res += macro -> apply (ns_stats_subhead, table, stat1) + sub + macro -> apply (ns_stats_subfoot, table, stat1);
            sub.clear (); }
        mmac_t stat2 = mac_subtitle ("metadata");
        for (unsigned i = 0; i < mn_illegal; ++i)
        {   const unsigned n = metaname_.at (static_cast < e_metaname > (i));
            if (n)
            {   mmac_t item = mac_init (enum_n < t_metaname, e_metaname > :: name (static_cast < e_metaname > (i)), n);
                sub += macro -> apply (ns_stat, table, stat2, item); } }
        if (! sub.empty ())
        {   res += macro -> apply (ns_stats_subhead, table, stat2) + sub + macro -> apply (ns_stats_subfoot, table, stat2);
            sub.clear (); }
        mmac_t stat3 = mac_subtitle ("name");
        for (unsigned i = 0; i < mn_illegal; ++i)
        {   mmac_t layer = mac_init (enum_n < t_metaname, e_metaname > :: name (static_cast < e_metaname > (i)));
            ::std::string ss;
            for (   auto k = meta_value_.at (static_cast < e_metaname > (i)).cbegin ();
                    k != meta_value_.at (static_cast < e_metaname > (i)).cend ();
                    ++k)
            {   mmac_t item = mac_subinit (k -> first, k -> second);
                ss += macro -> apply (ns_substat, table, stat3, layer, item); }
            if (! ss.empty ())
            {   sub += macro -> apply (ns_stat, table, stat3, layer) + ss;
                ss.clear (); } }
        if (! sub.empty ())
        {   res += macro -> apply (ns_stats_subhead, table, stat3) + sub + macro -> apply (ns_stats_subfoot, table, stat3);
            sub.clear (); } }
    if (! res.empty ()) res = macro -> apply (ns_stats_head, table) + res + macro -> apply (ns_stats_foot, table);
    return res; }

::std::string stats::report_usage (const ::std::string& category, const smsid_stats& sum) const
{   ::std::string s;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    ::std::size_t count = 0, grand = 0;
    for (smsid_t::const_iterator i = sum.cbegin (); i != sum.cend (); ++i)
    {   mmac_t mac;
        ::std::string lex (once_twice_thrice < ::std::size_t > (i -> second));
        mac.emplace (nm_tally_name, i -> first);
        mac.emplace (nm_tally_int, lex);
        mac.emplace (nm_tally_use_int, "");
        mac.emplace (nm_tally_count, once_twice_thrice < ::std::size_t > (i -> second));
        mac.emplace (nm_tally_use_count, "");
        ++count; grand += i -> second;
        s += macro -> apply (ns_tally, mac); }
    if (! s.empty ())
    {   mmac_t mac = mac_title (category);
        ::std::string lex (once_twice_thrice < ::std::size_t > (grand));
        mac.emplace (nm_tally_count, ::boost::lexical_cast < ::std::string > (count));
        mac.emplace (nm_tally_title, category);
        mac.emplace (nm_tally_title, "");
        mac.emplace (nm_tally_sum, lex);
        mac.emplace (nm_tally_total, once_twice_thrice < ::std::size_t > (grand));
        mac.emplace (nm_tally_use_sum, "");
        mac.emplace (nm_tally_use_total, "");
        s = macro -> apply (ns_tally_head, mac) + s + macro -> apply (ns_tally_foot, mac) + "\n"; }
    return s; }

::std::string stats::single_usage (const ::std::string name, const ::std::size_t dn, const ::std::size_t un,
        e_nit_section sc, e_nit_macro n, e_nit_macro i1, e_nit_macro i2, e_nit_macro c1, e_nit_macro c2) const
{   mmac_t mac;
    mac.emplace (n, name);
    mac.emplace (i1, ::boost::lexical_cast < ::std::string > (dn));
    mac.emplace (i2, ::boost::lexical_cast < ::std::string > (un));
    mac.emplace (c1, once_twice_thrice < ::std::size_t > (dn));
    mac.emplace (c2, once_twice_thrice < ::std::size_t > (un));
    return macro -> apply (sc, mac); }

::std::string stats::report_usage (const ::std::string& category, const smsid_stats& dcl, const smsid_stats& used,
        e_nit_section sc, e_nit_section h, e_nit_section f, e_nit_macro n,
        e_nit_macro i1, e_nit_macro i2, e_nit_macro c1, e_nit_macro c2,
        e_nit_macro ttl, e_nit_macro t1, e_nit_macro t2, e_nit_macro sum1, e_nit_macro sum2) const
{   mmac_t table = mac_title (category);
    ::std::string s;
    ::smsid_t::const_iterator di = dcl.cbegin ();
    ::smsid_t::const_iterator ui = used.cbegin ();
    ::std::size_t count = 0, gd = 0, gu = 0;
    for (;;)
    {   if (di == dcl.cend ())
        {   if (ui == used.cend ()) break; 
            s += single_usage (ui -> first, 0, ui -> second, sc, n, i1, i2, c1, c2);
            gu += ui -> second; 
            ++ui; }
        else if (ui == used.cend ())
        {   s += single_usage (di -> first, di -> second, 0, sc, n, i1, i2, c1, c2);
            gd += di -> second; 
            ++di; }
        else if (di -> first < ui -> first)
        {   s += single_usage (di -> first, di -> second, 0, sc, n, i1, i2, c1, c2);
            gd += di -> second; 
            ++di; }
        else if (ui -> first < di -> first)
        {   s += single_usage (ui -> first, 0, ui -> second, sc, n, i1, i2, c1, c2);
            gu += ui -> second; 
            ++ui; }
        else
        {   PRESUME (ui -> first == di -> first, __FILE__, __LINE__);
            s += single_usage (ui -> first, di -> second, ui -> second, sc, n, i1, i2, c1, c2);
            gu += ui -> second; 
            gd += di -> second; 
            ++ui; ++di; }
        ++count; }
    if (! s.empty ())
    {   mmac_t mac;
        mac.emplace (c1, ::boost::lexical_cast < ::std::string > (count));
        mac.emplace (sum1, once_twice_thrice < ::std::size_t > (gd));
        mac.emplace (ttl, category);
        mac.emplace (t1, once_twice_thrice < ::std::size_t > (gd));
        mac.emplace (sum2, once_twice_thrice < ::std::size_t > (gu));
        mac.emplace (t2, once_twice_thrice < ::std::size_t > (gu));
        s = macro -> apply (h, table, mac) + s + macro -> apply (f, table, mac) + "\n"; }
    return s; }

::std::string stats::font_report () const
{   return report_usage (REPORT_FONT, font_); }

::std::string stats::class_report () const
{   return  report_usage (REPORT_CLASS, dcl_class_, use_class_, ns_du, ns_du_head, ns_du_foot,
                nm_tally_name, nm_tally_decl_count, nm_tally_use_count, nm_tally_decl_int, nm_tally_use_int, nm_tally_title) +
            report_usage (REPORT_ELEMENT_CLASS, dcl_element_class_, use_element_class_, ns_du, ns_du_head, ns_du_foot,
                nm_tally_name, nm_tally_decl_count, nm_tally_use_count, nm_tally_decl_int, nm_tally_use_int, nm_tally_title); }

::std::string stats::class_report2 () const
{   return  report_usage (REPORT_CLASS, dcl_class_, use_class_, ns_class, ns_class_head, ns_class_foot,
                nm_class_name, nm_class_decl_int, nm_class_int, nm_class_decl_count, nm_class_count, nm_class_title) +
            report_usage (REPORT_ELEMENT_CLASS, dcl_element_class_, use_element_class_, ns_class, ns_class_head, ns_class_foot,
                nm_class_name, nm_class_decl_int, nm_class_int, nm_class_decl_count, nm_class_count, nm_class_title); }

::std::string stats::itemid_report () const
{   return report_usage (REPORT_ITEMID, dcl_id_, use_id_) ; }

::std::string stats::id_report () const
{   return  report_usage (REPORT_ID, dcl_id_, use_id_, ns_du, ns_du_head, ns_du_foot,
                nm_tally_name, nm_tally_decl_count, nm_tally_use_count, nm_tally_decl_int, nm_tally_use_int, nm_tally_title) +
            report_usage (REPORT_ELEMENT_ID, dcl_element_id_, use_element_id_, ns_du, ns_du_head, ns_du_foot,
                nm_tally_name, nm_tally_decl_count, nm_tally_use_count, nm_tally_decl_int, nm_tally_use_int, nm_tally_title); }

::std::string stats::id_report2 () const
{   return  report_usage (REPORT_ID, dcl_id_, use_id_, ns_nsid, ns_id_head, ns_id_foot,
                nm_id_name, nm_id_decl_int, nm_id_int, nm_id_decl_count, nm_id_count, nm_id_title) +
            report_usage (REPORT_ELEMENT_ID, dcl_element_id_, use_element_id_, ns_nsid, ns_id_head, ns_id_foot,
                nm_id_name, nm_id_decl_int, nm_id_int, nm_id_decl_count, nm_id_count, nm_id_title); }

::std::string stats::custom_property_report () const
{   return report_usage (REPORT_CUSTARD_PROPERTY, dcl_custom_prop_, use_custom_prop_); }

::std::string stats::report (const bool grand) const
{   ::std::string res;
    if ((context.verbose () == es_undefined) || (context.verbose () == es_illegal)) return res;
    mmac_t g;
    if (grand) g.emplace (nm_grand_title, REPORT_GRAND " Total");
    else g.emplace (nm_grand_title, REPORT_STAT);
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    res += macro -> apply (ns_grand_head, g);
    if (context.stats_abbr ()) res += abbr_report ();
    if (context.stats_gst (gst_annotation)) res += css_str_report (gst_annotation);
    if (grand && context.stats_category ()) res += category_report ();
    if (context.stats_gst (gst_character_variant)) res += css_str_report (gst_character_variant);
    if (context.stats_class ()) res += class_report ();
    if (context.stats_gst (gst_content_name)) res += css_str_report (gst_content_name);
    if (context.stats_gst (gst_counter_style)) res += css_str_report (gst_counter_style);
    if (context.stats_custom_media ()) res += custom_media_report ();
    if (context.stats_custom_property ()) res += custom_property_report ();
    if (context.stats_definition ()) res += definition_report ();
    if (context.stats_element ()) res += element_report ();
    if (grand && context.stats_error ()) res += error_report ();
    if (grand && (file_count_ > 1) && context.stats_file ()) res += file_report ();
    if (context.stats_font ()) res += font_report ();
    if (context.stats_gst (gst_font_family)) res += css_str_report (gst_font_family);
    if (context.stats_gst (gst_highlight)) res += css_str_report (gst_highlight);
    if (context.stats_gst (gst_historical_form)) res += css_str_report (gst_historical_form);
    if (context.stats_id ()) res += id_report ();
    if (context.stats_itemid ()) res += itemid_report ();
    if (context.stats_gst (gst_keyframe)) res += css_str_report (gst_keyframe);
    if (context.stats_gst (gst_layer)) res += css_str_report (gst_layer);
    if (context.stats_meta ()) res += meta_report ();
    if (context.stats_ontology ()) res += ontology_report ();
    if (context.stats_gst (gst_ornament)) res += css_str_report (gst_ornament);
    if (context.stats_gst (gst_page_name)) res += css_str_report (gst_page_name);
    if (context.stats_gst (gst_palette)) res += css_str_report (gst_palette);
    if (context.stats_css_property ()) res += property_report ();
    if (grand && (file_count_ > 1) && context.stats_reference ()) res += reference_report ();
    if (context.stats_gst (gst_region)) res += css_str_report (gst_region);
    if (context.stats_gst (gst_scroll_anim)) res += css_str_report (gst_scroll_anim);
    if (context.stats_statement ()) res += statement_report ();
    if (context.stats_gst (gst_styleset)) res += css_str_report (gst_styleset);
    if (context.stats_gst (gst_stylistic)) res += css_str_report (gst_stylistic);
    if (context.stats_gst (gst_swash)) res += css_str_report (gst_swash);
    if (context.stats_value_pair ()) res += value_pair_report ();
    if (grand && (file_count_ > 1) && context.stats_version ()) res += version_report ();
    if (context.stats_gst (gst_view)) res += css_str_report (gst_view);
    res += macro -> apply (ns_grand_foot, g);
    return res; }

bool stats::severity_exceeded () const
{   for (int x = 1; x <= static_cast < int > (context.report_error ()); ++x)
        if (element_count (static_cast < e_severity> (x))) return true;
    return false; }

void stats::check_for_standard_classes (nitpick& nits, const html_version& v) const
{   for (auto id = dcl_class_.cbegin (); id != dcl_class_.cend (); ++id)
    {   html_class c (nits, v, id -> first);
        if (c.is_microformat_property ())
            nits.pick (nit_class_microformat_property, es_warning, ec_css, "CSS identifier ", quote (id -> first), " is a microformat property");
        else if (c.is_microformat_vocabulary ())
            nits.pick (nit_class_microformat_vocabulary, es_warning, ec_css, "CSS identifier ", quote (id -> first), " is a microformat vocabulary"); } }

void stats::accumulate (stats& o) const
{   element_.accumulate (o.element_);
    visible_.accumulate (o.visible_);
    dfn_.accumulate (o.dfn_);
    abbr_.accumulate (o.abbr_);
    custom_media_.accumulate (o.custom_media_);
    dtdd_.accumulate (o.dtdd_);
    severity_ .accumulate (o.severity_);
    category_.accumulate (o.category_);
    ref_.accumulate (o.ref_);
    version_.accumulate (o.version_);
    attribute_.accumulate (o.attribute_);
    ontology_.accumulate (o.ontology_);
    ontology_property_.accumulate (o.ontology_property_);
    httpequiv_.accumulate (o.httpequiv_);
    metaname_.accumulate (o.metaname_);
    meta_value_.accumulate (o.meta_value_);
    dcl_class_.accumulate (o.dcl_class_);
    dcl_custom_prop_.accumulate (o.dcl_custom_prop_);
    dcl_id_.accumulate (o.dcl_id_);
    dcl_element_class_.accumulate (o.dcl_element_class_);
    dcl_element_id_.accumulate (o.dcl_element_id_);
    css_property_.accumulate (o.css_property_);
    css_statement_.accumulate (o.css_statement_);
    font_.accumulate (o.font_);
    use_class_.accumulate (o.use_class_);
    use_custom_prop_.accumulate (o.use_custom_prop_);
    use_id_.accumulate (o.use_id_);
    use_element_class_.accumulate (o.use_element_class_);
    use_element_id_.accumulate (o.use_element_id_);
    for (int i = 0; i < gst_max; ++i)
        str_.at (static_cast < e_gsstr > (i)).accumulate (o.str_.at (static_cast < e_gsstr > (i)));
    if (smallest_ < o.smallest_) o.smallest_ = smallest_;
    if (biggest_ > o.biggest_) o.biggest_ = biggest_;
    o.file_size_ += file_size_;
    o.file_count_ += file_count_; }

::std::string stats::class_and_id_report () const
{   ::std::string res;
    if (context.stats_class ()) res = class_report2 ();
    if (context.stats_id ()) res += id_report2 ();
    return res; }
