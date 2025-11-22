/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "webpage/required.h"

static req_vt req_g;

void reset_required ()
{   req_g.clear (); }

::std::size_t required_count ()
{   return req_g.size (); }

bool decode_required_page (nitpick& nits, required_t& rq)
{   vstr_t a = uq2_sep (rq.s_,  UQ_DQ | UQ_SQ | UQ_BS | UQ_BLANK);
    if (a.size () == 0)
    {   nits.pick (nit_url_empty, es_error, ec_init, "expecting at least a URL");
        return false; }
    if (a.size () > 7) nits.pick (nit_too_many, es_error, ec_init, "ignoring extra values");
    rq.url_ = url (nits, html_default, a.at (0));
    bool res = ! rq.url_.invalid ();
    if (a.size () > 1)
    {   if (a.at (1).empty ()) rq.lang_ = la_illegal; else
        {   rq.lang_ = examine_value < t_lang > (nits, html_default, a.at (1));
            if ((rq.lang_ == la_illegal) || (rq.lang_ == la_context))
                rq.rq_lang_ = a.at (1); }
        if (a.size () > 2)
        {   if (a.at (2).empty ()) rq.rq_ = rqp_none; else
            {   nitpick knots;
                rq.rq_ = examine_value < t_required_page > (knots, html_default, a.at (2));
                if (rq.rq_ == rqp_none) rq.rq_page_ = a.at (2); }
            if (a.size () > 3)
            {   if (! a.at (3).empty ())
                {   const elem e (nits, html_default, namespaces_ptr (), a.at (3), false, nullptr);
                    if (! e.invalid ()) rq.e_ = e.get ();
                    else res = false; }
                if (a.size () > 4)
                    if (! a.at (4).empty ())
                    {   const html_version from (nits, a.at (4));
                        if (! from.empty ()) rq.from_ = from;
                        if (a.size () > 5)
                            if (! a.at (5).empty ())
                            {   const html_version to (nits, a.at (5));
                                if (! to.empty ()) rq.to_ = to;
                                if (a.size () > 6)
                                    rq.desc_ = a.at (6); } } } } }
    return res; }

bool add_required_page (nitpick& nits, const ::std::string& arg)
{   required_t rq;
    rq.s_ = arg;
    if (! decode_required_page (nits, rq)) return false;
    req_g.push_back (rq);
    return true; }

bool add_required_pages (nitpick& nits, const vstr_t& arg)
{   bool res = true;
    for (auto s : arg) if (! add_required_page (nits, s)) res = false;
    return res; }

int check_required_pages (const html_version& v, const e_required_page rqp_type, const ::std::string& page_name, const vurl_t& uref, const element_bitset ancestral_elements, const e_lang l)
{   for (::std::size_t i = 0; i < required_count (); ++i)
    {   const required_t& rq = GSL_AT (req_g, i);
        if ((rq.lang_ == la_context) || (rq.lang_ == l))
            if ((rq.e_ == elem_undefined) || ancestral_elements.test (rq.e_))
                if (rq.from_.unknown () || (rq.from_ <= v))
                    if (rq.to_.unknown () || (rq.to_ >= v))
                    {   switch (rq.rq_)
                        {   case rqp_all :
                                break;
                            case rqp_index :
                                if ((rqp_type != rqp_index) && (rqp_type != rqp_front)) continue;
                                break;
                            case rqp_front :
                                if (rqp_type != rqp_front) continue;
                                break;
                            case rqp_none :
                                if (! compare_no_case (page_name, rq.s_)) continue;
                                break;
                            default :
                                GRACEFUL_CRASH (__FILE__, __LINE__);
                                continue; }
                        for (auto u : uref)
                            if (u == rq.url_)
                                return static_cast < int > (i); } }
    return -1; }

vstr_t required_page_list ()
{   vstr_t res;
    for (auto rq : req_g)
        res.push_back (rq.s_);
    return res; }

e_required_page get_required_page_type (const ::std::string& page_name, const bool root, faux_vb_t& req, faux_vb_t& check)
{   req.resize (required_count ());
    check.resize (required_count ());
    e_required_page res = rqp_all;
    if (! compare_no_case (page_name, context.index ())) res = rqp_none;
    else if (root) res = rqp_front;
    else res = rqp_index;
    for (::std::size_t n = 0; n < required_count (); ++n)
        switch (GSL_AT (req_g, n).rq_)
        {   case rqp_all : GSL_AT (check, n) = true; break;
            case rqp_front : if (res == rqp_front) GSL_AT (check, n) = true; break;
            case rqp_index : if ((res == rqp_front) || (res == rqp_index)) GSL_AT (check, n) = true; break;
            default : break; }
    return res; }

void check_required_state (nitpick& nits, const ::std::string& name, const faux_vb_t& req, const faux_vb_t& check)
{   for (int i = 0; i < GSL_NARROW_CAST < int > (required_count ()); ++i)
        if (GSL_AT (check, i) && ! GSL_AT (req, i))
            if (GSL_AT (req_g, i).rq_ > rqp_none)
            {   ::std::string rqt;
                if (GSL_AT (req_g, i).rq_ > rqp_all)
                    rqt = type_master < t_required_page > :: name (GSL_AT (req_g, i).rq_) + " ";
                if (! GSL_AT (req_g, i).desc_.empty ())
                    nits.pick (nit_required, es_error, ec_page, name, ": missing required ", rqt, "link for ", GSL_AT (req_g, i).desc_);
                else nits.pick (nit_required, es_error, ec_page, name, ": missing required ", rqt, "link to ", GSL_AT (req_g, i).url_.absolute ()); } }
