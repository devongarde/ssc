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
#include "stats/stats.h"
#include "stats/stats_impl.h"
#include "main/context.h"
#include "feedback/nitpick.h"
#include "microdata/microdata_itemprop.h"
#include "microdata/microdata_itemtype.h"
#include "type/type_httpequiv.h"
#include "type/type_metaname.h"

void stats::mark_file (const unsigned size)
{   ++file_count_;
    if (size < smallest_) smallest_ = size;
    if (size > biggest_) biggest_ = size;
    file_size_ += size; }

::std::string stats::times (const uint64_t n) const
{   switch (n)
    {   case 0: return "none";
        case 1: return "once";
        case 2: return "twice";
        case 3: return "thrice";
        default: return ::boost::lexical_cast < ::std::string > (n) + " times"; } }

::std::string stats::saybe (const unsigned n, const ::std::string& msg) const
{   if (n == 0) return ::std::string ();
    return msg + ": " + times (n) + "\n"; }

::std::string stats::microdata_report () const
{   uint64_t total = 0;
    unsigned count = 0;
    ::std::string res;
    for (unsigned i = 0; i < sch_illegal; ++i)
    {   unsigned n = schema_.at (static_cast < e_schema > (i));
        if (n == 0) continue;
        ++total;
        count += n;
        if (context.tell (e_error))
        {   const ::std::string naam (itemtype_index_name (make_itemtype_index (static_cast < e_schema > (i))));
            res += "    ";
            res += naam + ": " + times (n);
            if (context.tell (e_warning) && ! context.tell (e_info))
            {   unsigned x = schema_property_.family (static_cast < e_schema > (i));
                if (x > 0)
                {   res += ", with, on average, ";
                    res += ::boost::lexical_cast < ::std::string > (x / n);
                    res += " propert";
                    if (x == 1) res += "y"; else res += "ies"; } }
            res += "\n";
            if (context.tell (e_info))
                for (unsigned m = 0; m < sp_illegal; ++m)
                {   unsigned y = schema_property_.at (static_cast < e_schema > (i), static_cast <e_schema_property> (m));
                    if (y > 0)
                    {   res += "      ";
                        res += itemprop_index_name (make_itemprop_index (static_cast <e_schema_property> (m))) + ": ";
                        res += times (y) + "\n"; } } } }
    if (context.tell (e_warning))
    {   ::std::string pr;
        for (unsigned m = 0; m < sp_illegal; ++m)
        {   unsigned x = schema_property_.member (static_cast <e_schema_property> (m));
            if (x > 0)
            {   pr += "    ";
                pr += itemprop_index_name (make_itemprop_index (static_cast <e_schema_property> (m))) + ": used ";
                pr += times (x) + "\n"; } }
        if (! pr.empty ())
        {   res += "  Property counts:\n";
            res += pr; } }
    if (! res.empty ())
    {   res += "  ";
        res += ::boost::lexical_cast < ::std::string > (total);
        res += " itemtype";
        if (total != 1) res += "s";
        res += " used ";
        res += times (count) + "\n";
        res = ::std::string ("Microdata:\n") + res; }
    return res; }

::std::string stats::element_report () const
{   ::std::string res ("Elements:\n");
    uint64_t total = 0;
    unsigned count = 0;
    for (unsigned i = 0; i < last_element_tag; ++i)
    {   unsigned n = element_.at (i);
        if (n == 0) continue;
        ++total;
        count += n;
        if (context.tell (e_comment) || (context.tell (e_error) && ((elem::categories (i) & EF_FAUX) == 0)))
        {   const ::std::string naam (elem::name (i));
            res += "    ";
            res += naam + ": " + times (n);
            if (context.tell (e_warning) && ! context.tell (e_info))
            {   unsigned x = attribute_.family (i);
                if (x > 0)
                {   res += ", with, on average, ";
                    res += ::boost::lexical_cast < ::std::string > (x / n);
                    res += " attribute";
                    if (x != 1) res += "s"; } }
            res += "\n";
            if (context.tell (e_info))
                for (unsigned m = 0; m < last_attribute; ++m)
                {   unsigned y = attribute_.at (i, static_cast <e_attribute> (m));
                    if (y > 0)
                    {   res += "      ";
                        res += attr::name (static_cast <e_attribute> (m)) + ": ";
                        res += times (y) + "\n"; } } } }
    if (context.tell (e_warning))
    {   ::std::string att;
        for (unsigned m = 0; m < last_attribute; ++m)
        {   unsigned x = attribute_.member (static_cast <e_attribute> (m));
            if (x > 0)
            {   att += "    ";
                att += attr::name (static_cast <e_attribute> (m)) + ": used ";
                att += times (x) + "\n"; } }
        if (! att.empty ())
        {   res += "  Attribute counts:\n";
            res += att; } }
    res += "  ";
    res += ::boost::lexical_cast < ::std::string > (total);
    res += " element";
    if (total != 1) res += "s";
    res += " used ";
    res += times (count) + "\n";
    return res; }

::std::string stats::version_report () const
{   ::std::string res ("Versions:\n");
    for (auto i : version_.count_)
        if (i.second > 0)
        {   res += "  ";
            res += i.first.report ();
            res += ": ";
            res += ::boost::lexical_cast < ::std::string > (i.second);
            res += "\n"; }
    return res; }

::std::string stats::error_report () const
{   ::std::string res;
    res += saybe (severity_.at (es_catastrophic), "    Catastrophes");
    if (context.tell (e_error)) res += saybe (severity_.at (es_error), "    Errors");
    if (context.tell (e_warning)) res += saybe (severity_.at (es_warning), "    Warnings");
    if (context.tell (e_info)) res += saybe (severity_.at (es_info), "    Info");
    if (context.tell (e_comment)) res += saybe (severity_.at (es_comment), "    Comments");
    if (res.empty ()) return "No errors or warnings\n";
    return ::std::string ("Errors:\n  Severity:\n") + res; }

::std::string stats::category_report () const
{   ::std::string res;
    res += saybe (category_.at (ec_html), "    HTML");
    res += saybe (category_.at (ec_attribute), "    Attribute");
    res += saybe (category_.at (ec_crc), "    CRC");
    res += saybe (category_.at (ec_css), "    CSS");
    res += saybe (category_.at (ec_directory), "    Directory");
    res += saybe (category_.at (ec_element), "    Element");
    res += saybe (category_.at (ec_incorrectness), "    Incorrectness");
    res += saybe (category_.at (ec_init), "    Init");
    res += saybe (category_.at (ec_link), "    Link");
    res += saybe (category_.at (ec_microdata), "    Microdata");
    res += saybe (category_.at (ec_microformat), "    Microformat");
    res += saybe (category_.at (ec_mql), "    Media Query");
    res += saybe (category_.at (ec_namespace), "    Namespace");
    res += saybe (category_.at (ec_page), "    Page");
    res += saybe (category_.at (ec_parser), "    Parser");
    res += saybe (category_.at (ec_program), "    Program");
    res += saybe (category_.at (ec_rdf), "    RDFa");
    res += saybe (category_.at (ec_rudeness), "    Rudeness");
    res += saybe (category_.at (ec_shadow), "    Shadow");
    res += saybe (category_.at (ec_ssi), "    SSI");
    res += saybe (category_.at (ec_tidyness), "    Tidyness");
    res += saybe (category_.at (ec_type), "    Type");
    res += saybe (category_.at (ec_url), "    URx");
    res += saybe (category_.at (ec_utility), "    Utility");
    res += saybe (category_.at (ec_webmention), "    Webmention");
    if (res.empty ()) return res;
    return ::std::string ("  Categories:\n") + res; }

::std::string stats::file_report () const
{   ::std::string res ("File info:\n");
    res += ::std::string (2, ' ');
    if (context.tell (e_warning)) res += ::boost::lexical_cast < ::std::string > (file_size_) + " bytes read in ";
    res += ::boost::lexical_cast < ::std::string > (file_count_) + " HTML files with an average of ";
    res += ::boost::lexical_cast < ::std::string > (file_size_ / file_count_);
    res += " bytes per file\n";
    if (context.tell (e_error))
    {   res += "  smallest file: " + ::boost::lexical_cast < ::std::string > (smallest_) + " bytes, ";
        res += "largest file: " + ::boost::lexical_cast < ::std::string > (biggest_) + " bytes\n"; }
    return res; }

::std::string stats::reference_report () const
{   ::std::string res;
    for (unsigned int d = 1; d <= last_doc; ++d)
        res += saybe (ref_.at (static_cast <e_doc> (d)), ::std::string ("    ") + doc_title (static_cast <e_doc> (d)));
    if (res.empty ()) return res;
    return ::std::string ("  References:\n") + res; }

::std::string stats::meta_report () const
{   ::std::string res;
    if (context.meta ())
    {   for (unsigned i = 0; i < he_error; ++i)
        {   unsigned n = httpequiv_.at (static_cast < e_httpequiv > (i));
            if (n)
            {   ::std::string naam ("    ");
                naam += enum_n < t_httpequiv, e_httpequiv > :: name (static_cast < e_httpequiv > (i));
                res += saybe (n, naam); } }
        if (! res.empty ()) res = "  pragma:\n" + res;
        ::std::string rpt;
        for (unsigned i = 0; i < mn_illegal; ++i)
        {   unsigned n = metaname_.at (static_cast < e_metaname > (i));
            if (n)
            {   ::std::string naam ("    ");
                naam += enum_n < t_metaname, e_metaname > :: name (static_cast < e_metaname > (i));
                rpt += saybe (n, naam); } }
        if (! rpt.empty ()) res += "  name:\n" + rpt;
        for (unsigned i = 0; i < mn_illegal; ++i)
        {   bool y = false;
            for (   auto k = meta_value_.at (static_cast < e_metaname > (i)).cbegin ();
                    k != meta_value_.at (static_cast < e_metaname > (i)).cend ();
                    ++k)
            {   if (! y)
                {   res += "    ";
                    res += enum_n < t_metaname, e_metaname > :: name (static_cast < e_metaname > (i));
                    res += ":\n";
                    y = true; }
                res += "      ";
                res += k -> first;
                res += ": ";
                res += times (k -> second);
                res += "\n"; } }
        if (! res.empty ()) res = "Metadata:\n" + res; }
    return res; }

::std::string stats::report (const bool grand) const
{   ::std::string res;
    if (context.verbose () == e_silent) return res;

    if (grand || (file_count_ > 1)) res += "\n\n*** Grand totals\n";
    else res += "\n*** Statistics:\n";

    res += element_report ();
    res += microdata_report ();
    res += meta_report ();
    res += error_report ();

    if (file_count_ > 1)
    {   res += category_report ();
        res += reference_report ();
        res += version_report ();
        res += file_report (); }

    return res; }
