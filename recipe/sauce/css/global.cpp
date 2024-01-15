/*
ssc (static site checker)
File Info
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

css_global::css_global ()
{   reset (); } // it looks like some stuff was optimised away that shouldn't have been, so ...

void css_global::reset ()
{   mdst_.clear (); }

dst_ptr css_global::get_or_preinsert (const ::std::string& s)
{   dst_ptr dsp = get (s);
    if (dsp.get () == nullptr)
    {   dsp = dst_ptr (new distilled (true));
        lox l (lox_css);
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

css_ptr css_global::expel_cp (const ::std::string& s) const
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

void css_global::report_usage (::std::ostringstream& ss) const
{   PRESUME (! fred.activity (), __FILE__, __LINE__);
    if (context.tell (es_warning))
    {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        smsid_t sum;
        for (auto i : mdst_)
            if (i.second != nullptr)
                merge_smsid (sum, i.second -> class_);
        ::std::string cls;
        for (auto i : sum)
        {   mmac_t mac;
            ::std::string lex (::boost::lexical_cast < ::std::string > (i.second));
            mac.emplace (nm_class_name, i.first);
            mac.emplace (nm_class_int, lex);
            mac.emplace (nm_class_count, once_twice_thrice < ::std::size_t > (i.second));
            cls += macro -> apply (ns_class, mac); }
        if (! cls.empty ())
            ss << macro -> apply (ns_class_head) << cls << macro -> apply (ns_class_foot); } }

void css_global::accumulate (stats_t* s) const
{   for (auto i : mdst_)
        if (i.second != nullptr)
            i.second -> accumulate (s); }

::std::string css_global::report () const
{   ::std::string res;
    if (context.tell (es_detail))
        if (mdst_.empty ()) res += "No CSSs preloaded\n";
        else for (auto m : mdst_)
        {   res += m.first;
            if (! context.tell (es_detail)) res += "\n";
            else if (m.second.get () == nullptr) res += ": NULL\n";
            else
            {   res += ":\n";
                res += m.second -> report (); } }
    return res; }
