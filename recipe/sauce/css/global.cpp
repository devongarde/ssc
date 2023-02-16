/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

#include "main/standard.h"
#include "css/global.h"
#include "coop/fred.h"
#include "main/context.h"
#include "utility/common.h"
#include "css/css.h"

css_global global_css;

dst_ptr css_global::get_or_preinsert (const ::std::string& s)
{   dst_ptr dsp = get (s);
    if (dsp.get () == nullptr)
    {   dsp = dst_ptr (new distilled (true));
        mdst_.emplace (mdst_t::value_type (s, dsp)); }
    return dsp; }

dst_ptr css_global::inner_get (const ::std::string& s) const
{   mdst_t::const_iterator i = mdst_.find (s);
    if (i != mdst_.cend ()) return i -> second;
    return dst_ptr (); }

void css_global::release (dst_ptr cp)
{   lox l (lox_css);
    cp -> in_progress_ = false; }

dst_ptr css_global::get (const ::std::string& s) const
{   PRESUME (fred.started (), __FILE__, __LINE__);
    while (! fred.abandoned ())
    {   {   lox l (lox_css);
            dst_ptr dsp (inner_get (s));
            if (dsp.get () == nullptr) return dsp;
            if (! dsp -> wait ()) return dsp; }
        ::std::this_thread::yield (); }
    return dst_ptr (); }

css_ptr css_global::get_cp (const ::std::string& s) const
{   PRESUME (fred.started (), __FILE__, __LINE__);
    css_ptr cp;
    while (! fred.abandoned ())
    {   {   lox l (lox_css);
            dst_ptr dsp (inner_get (s));
            if (dsp.get () == nullptr) break;
            if (! dsp -> wait ())
                return dsp -> expel (); }
        ::std::this_thread::yield (); }
    return css_ptr (); }

void css_global::report_stragglers (::std::ostringstream& ss, const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot, const e_nit_section& page_head, const bool unfiltered) const
{   PRESUME (! fred.activity (), __FILE__, __LINE__);
    for (auto i : mdst_)
        if (i.second != nullptr)
            if (i.second -> css ().get () != nullptr)
            {   mmac_t mac;
                mac.emplace (nm_page_name, i.first);
                mac.emplace (nm_page_disk_path, i.first);
                mac.emplace (nm_page_site_path, i.first);
                ss << i.second -> css () -> review (mac, entry, head, foot, page_head, unfiltered); 
                i.second -> expel (); } }

void css_global::report_usage (::std::ostringstream& ss) const
{   PRESUME (! fred.activity (), __FILE__, __LINE__);
    if (context.tell (es_warning))
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        smsid_t sum_;
        for (auto i : mdst_)
            if (i.second != nullptr)
                merge_smsid (sum_, i.second -> class_);
        ::std::string cls;
        for (auto i : sum_)
        {   mmac_t mac;
            ::std::string lex (::boost::lexical_cast < ::std::string > (i.second));
            mac.emplace (nm_class_name, i.first);
            mac.emplace (nm_class_int, lex);
            mac.emplace (nm_class_count, once_twice_thrice < ::std::size_t > (i.second));
            cls += macro -> apply (ns_class, mac); }
        if (! cls.empty ())
            ss << macro -> apply (ns_class_head) << cls << macro -> apply (ns_class_foot); } }
