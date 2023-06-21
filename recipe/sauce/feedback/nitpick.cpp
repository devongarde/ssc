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
#include "feedback/nitpick.h"
#include "main/context.h"
#include "main/options.h"
#include "feedback/nitout.h"
#include "stats/stats.h"
#include "coop/lox.h"

nitpick::mns_t nitpick::mns_;
bool nitpick::fe_ = false;
bool nitpick::sarcasm_ = false;

void nitpick::swap (nitpick& np) noexcept
{   ::std::swap (line_, np.line_);
    nits_.swap (np.nits_);
    after_.swap (np.after_);
    before_.swap (np.before_);
    mote_.swap (np.mote_);
    severity_.swap (np.severity_);
    category_.swap (np.category_);
    doc_.swap (np.doc_); }

void nitpick::reset () noexcept
{   nitpick np;
    swap (np); }

void nitpick::reset (const nitpick& np)
{   nitpick tmp (np);
    swap (tmp); }

void nitpick::merge (const nitpick& np)
{   lox l (lox_nits);
    if (mote_.empty ())
    {   before_ = np.before_; after_ = np.after_; mote_ = np.mote_; }
    nits_.insert (nits_.end (), np.nits_.cbegin (), np.nits_.cend ());
    np.accumulate (*this); }

template < class T > ::std::string nitpick::inner_review (const e_nit_section& entry, const T& t, const mmac_t& mac, mmac_t& outer, bool& quote, bool& dq, bool& infoed, bool& eol, bool& hasns, const bool unfiltered) const
{   extern bool ignore_this_slob_stuff (const e_nit code);
    hasns = false;
    ::std::string res, ns;
    for (auto n : t)
        if (unfiltered || (context.tell (n.severity ()) && ! ignore_this_slob_stuff (n.code ())))
        {   switch (n.code ())
            {   case nit_context:
                    infoed = true;
                    break;
                case nit_use_double_quote_code :
                    if (dq) continue;
                    dq = true;
                    break;
                case nit_use_quote_code :
                    if (quote) continue;
                    quote = true;
                    break;
                case nit_newline_in_string :
                    if (eol) continue;
                    eol = true;
                    break;
                default : break; }
            if (n.code () != nit_context)
            {   notify (n);
                if (hasns) ns += " "; else hasns = true;
                if (context.spec ()) ns += lookup_name (n.code ());
                else ns += ::boost::lexical_cast < ::std::string > (n.code ());
                res += n.review (entry, mac, outer); } }
    if (hasns) outer.emplace (nm_nit_ns, ns);
    return res; }

::std::string nitpick::review (const mmac_t& mac, const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot, const e_nit_section& page_head, const bool unfiltered) const
{   bool quote = false, dq = false, infoed = false, eol = false, hasns = false;
    ::std::string res;
    if (! empty () || stuffed_)
    {   mmac_t inner;
        inner.emplace (nm_nit_line, ::boost::lexical_cast < ::std::string > (line_));
        if (mote_.empty () || is_whitespace (mote_))
        {   inner.emplace (nm_nit_before, "");
            if (mote_.empty ()) inner.emplace (nm_nit_mote, before_);
            else inner.emplace (nm_nit_mote, before_);
            inner.emplace (nm_nit_after, ""); }
        else
        {   inner.emplace (nm_nit_before, before_);
            inner.emplace (nm_nit_mote, mote_);
            inner.emplace (nm_nit_after, after_); }
        if (stuffed_) inner.emplace (mn_nits_lost, "some nits were lost");
        else inner.emplace (mn_nits_lost, "");
        ::std::string nitbit;
        if (context.nits_nits_nits ())
            nitbit = inner_review (entry, nits_, mac, inner, quote, dq, infoed, eol, hasns, unfiltered);
        else
        {   ::std::set < nit > sn;
            for (auto n : nits_)
                if (sn.find (n) == sn.end ())
                    sn.insert (n);
            nitbit = inner_review (entry, sn, mac, inner, quote, dq, infoed, eol, hasns, unfiltered); }
        if (hasns || ! nitbit.empty ())
        {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
            if ((page_head != ns_none) && (line_ == 0) && ! context.test ())
                res = macro -> apply (page_head, mac, inner) + nitbit + macro -> apply (foot, mac, inner);
            else res = macro -> apply (head, mac, inner) + nitbit + macro -> apply (foot, mac, inner); } }
    return res; }

::std::string nitpick::review (const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot, const e_nit_section& page_head) const
{   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    return review (macro -> macros (), entry, head, foot, page_head); }

::std::string nitpick::unfiltered (const e_nit_section& entry, const e_nit_section& head, const e_nit_section& foot, const e_nit_section& page_head) const
{   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    return review (macro -> macros (), entry, head, foot, page_head, true); }

nitpick nitpick::nick ()
{   nitpick tmp;
    swap (tmp);
    return tmp; }

void nitpick::pick (const nit& n) noexcept
{   try
    {   lox l (lox_nits);
        nits_.emplace_back (n); }
    catch (...)
    {   stuffed_ = true; } }

void nitpick::pick (nit&& n) noexcept
{   try
    {   lox l (lox_nits);
        nits_.emplace_back (n); }
    catch (...)
    {   stuffed_ = true; } }

bool nitpick::modify_severity (const ::std::string& name, const e_severity s)
{   const e_nit code = lookup_code (name);
    if (code == nit_off) return false;
    modify_severity (code, s);
    return true; }

e_severity nitpick::worst () const noexcept
{   if (! stuffed_) try
    {   e_severity res = es_illegal;
        lox l (lox_nits);
        for (auto n : nits_)
            if (n.severity () < res)
                res = n.severity ();
        return res; }
    catch (...)
    { }
    return es_catastrophic; }

void nitpick::reset_context (const int line, const ::std::string& c)
{   ::std::string r (tart (c));
    if (context.nits ())
    {   ::std::ostringstream ss;
        ss << "set context to " << r << " (line " << line << ")\n";
        outstr.out (ss.str ()); }
    line_ = line;
    stuffed_ = false;
    before_.clear (); after_.clear ();
    mote_.assign (r); }

void nitpick::set_context (const int line, const ::std::string& c)
{   if (mote_.empty ()) reset_context (line, delined (c));
    else if (line_ == 0) line_ = line; }

void nitpick::set_context (const int line, ::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator from, ::std::string::const_iterator to)
{   BOOST_STATIC_ASSERT (DEFAULT_LINE_LENGTH - 16 <= INT8_MAX);
    CONSTEXPR int maxish = DEFAULT_LINE_LENGTH - 16;
    const int len = GSL_NARROW_CAST < int > (to - from);
    const int maxlen = GSL_NARROW_CAST < int > (e - from);
    before_.clear (); after_.clear ();
    if (maxlen == 0)
        mote_.clear ();
    else
    {   if (len >= maxish) mote_ = ::std::string (from, from + maxish) + "...";
        else
        {   const int halfish = (maxish - len) / 2;
            if (len == 0)
            {   int last = halfish, x = 0;
                bool hell = true;
                const ::std::string ls (LINE_SEPARATORS);
                while ((from + x < to) && (::std::iswspace (*(from + x)) || ::std::iswcntrl (*(from + x)) || (ls.find (*(from + x)) != ::std::string::npos)) && (x < maxlen)) ++x;
                if (x >= maxlen-1) x = 0;
                if (x + last > maxlen)
                {   last = maxlen;
                    hell = false; }
                for (int i = x + 1; i < last; ++i)
                    if (ls.find (*(from + i)) != ::std::string::npos)
                    {   last = i - 1;
                        hell = false;
                        break; }
                mote_ = delined (from + x, from + last);
                if (hell) mote_ += "..."; }
            else
            {   mote_ = delined (from, to);
                ::std::string::const_iterator mb, me;
                if ((e - b) <= maxish) { me = e; mb = b; }
                else
                {   if ((b + halfish) >= from) mb = b;
                    else { mb = from - halfish; before_ = "..."; }
                    if ((e - halfish) <= to) me = e;
                    else { me = to + halfish; after_ = "..."; } }
                before_ += delined (mb, from);
                after_ = delined (to, me) + after_;
                ::std::string::size_type pos = before_.find_last_of (LINE_SEPARATORS);
                if (pos != ::std::string::npos) before_ = before_.substr (pos+1);
                pos = after_.find_first_of (LINE_SEPARATORS);
                if (pos != ::std::string::npos) after_ = after_.substr (0, pos); } } }
    line_ = line; }

void nitpick::set_context (const int line, const ::std::string::const_iterator b, ::std::string::const_iterator e)
{   set_context (line, ::std::string (b, e)); }

void nitpick::set_context (const int line, ::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i)
{   return set_context (line, b, e, i, i); }

void nitpick::set_context (const int , ::std::string::const_iterator , ::std::string::const_iterator , ::std::string::const_iterator , const ::std::string& , const e_severity )
{   GRACEFUL_CRASH (__FILE__, __LINE__); }

void nitpick::accumulate (nitpick& n) const
{   for (unsigned i = 0; i < severity_.size (); ++i) n.severity_.mark (static_cast < e_severity > (i), severity_.at (static_cast < e_severity > (i)));
    for (unsigned i = 0; i < category_.size (); ++i) n.category_.mark (static_cast < e_category > (i), category_.at (static_cast < e_category > (i)));
    for (unsigned i = 0; i < doc_.size (); ++i) n.doc_.mark (static_cast < e_doc > (i), doc_.at (static_cast < e_doc > (i))); }

void nitpick::accumulate (stats_t* s) const
{   VERIFY_NOT_NULL (s, __FILE__, __LINE__);
    for (unsigned i = 0; i < severity_.size (); ++i)
        if (severity_.at (static_cast < e_severity > (i)) > 0)
            s -> mark (static_cast < e_severity > (i), severity_.at (static_cast < e_severity > (i)));
    for (unsigned i = 0; i < category_.size (); ++i)
        if (category_.at (static_cast < e_category > (i)) > 0)
            s -> mark (static_cast < e_category > (i), category_.at (static_cast < e_category > (i)));
    for (unsigned i = 0; i < doc_.size (); ++i)
        if (doc_.at (static_cast < e_doc > (i)) > 0)
            s -> mark (static_cast < e_doc > (i), doc_.at (static_cast < e_doc > (i))); }

void nitpick::notify (const nit& n) const
{   severity_.mark (n.severity ());
    category_.mark (n.category ());
    doc_.mark (n.doc ()); }
