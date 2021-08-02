﻿/*
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
#include "feedback/nitpick.h"
#include "main/context.h"

nitpick::mns_t nitpick::mns_;

void nitpick::swap (nitpick& np) NOEXCEPT
{   ::std::swap (line_, np.line_);
    nits_.swap (np.nits_);
    context_.swap (np.context_); }

void nitpick::reset ()
{   nitpick np;
    swap (np); }

void nitpick::reset (const nitpick& np)
{   nitpick tmp (np);
    swap (tmp); }

void nitpick::merge (const nitpick& np)
{   if (context_.empty ()) context_ = np.context_;
    for (auto n : np.nits_)
        nits_.emplace_back (n); }

void nitpick::merge (nitpick&& np)
{   if (context_.empty ()) context_.assign (np.context_);
   for (auto n : np.nits_)
        nits_.emplace_back (n); }

template < class T > ::std::string nitpick::inner_review (const T& t, bool& quote, bool& dq, bool& infoed, bool& eol) const
{   extern bool ignore_this_slob_stuff (const e_nit code);
    ::std::string res;
    for (auto n : t)
        if (context.tell (static_cast < e_verbose > (n.severity ())) && ! ignore_this_slob_stuff (n.code ()))
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
            bool not_context = (n.code () != nit_context);
            if (not_context) n.notify ();
            if (! context.test ()) res += n.review ();
            else if (not_context)
            {   res += " ";
                if (context.spec ()) res += lookup_name (n.code ());
                else res += ::boost::lexical_cast < ::std::string > (n.code ()); } }
    return res; }

::std::string nitpick::review () const
{   ::std::string res;
    bool quote = false, dq = false, infoed = false, eol = false;
    if (! empty ())
    {   if (context.nits_nits_nits ())
            res = inner_review (nits_, quote, dq, infoed, eol);
        else
        {   ::std::set < nit > sn;
            for (auto n : nits_)
                if (sn.find (n) == sn.end ())
                    sn.insert (n);
            res = inner_review (sn, quote, dq, infoed, eol); }
        if (! res.empty ())
        {   ::std::string ln (::boost::lexical_cast < ::std::string > (line_));
            if (context.test ()) res = ln + " " + res + "\n";
            else if (! infoed)
            {   if (! context_.empty ()) prepend (res, "\n", context_);
                if (line_ > 0) prepend (res, ": ", ::std::string ("\n") + ln); } } }
    return res; }

nitpick nitpick::nick ()
{   nitpick tmp;
    swap (tmp);
    return tmp; }

void nitpick::pick (const nit& n)
{   nits_.emplace_back (n); }

void nitpick::pick (nit&& n)
{   nits_.emplace_back (n); }

void nitpick::set_context (const int line, const ::std::string& c)
{   ::std::string r (trim_the_lot_off (unify_whitespace (c)));
    if (context_.empty ())
    {   if (context.nits ())
        {   ::std::ostringstream ss;
            ss << "set context to " << r << "\n";
            context.out (ss.str ()); }
        line_ = line;
        context_.assign (r); } }

void nitpick::set_context (const int line, const ::std::string::const_iterator b, ::std::string::const_iterator e)
{   set_context (line, ::std::string (b, e)); }

bool nitpick::modify_severity (const ::std::string& name, const e_severity s)
{   e_nit code = lookup_code (name);
    if (code == nit_off) return false;
    modify_severity (code, s);
    return true; }

e_severity nitpick::worst () const
{   e_severity res = es_silence;
    for (auto n : nits_)
        if (n.severity () < res)
            res = n.severity ();
    return res; }
