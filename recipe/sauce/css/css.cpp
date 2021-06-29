/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "css/css.h"
#include "utility/quote.h"
#include "utility/filesystem.h"
#include "utility/byteorder.h"
#include "main/context.h"
#include "microformat/prop.h"
#include "type/type.h"
#include "url/url.h"
#include "webpage/page.h"
#include "parser/parse_css.h"

bool css::parsing_ = false;
bool dotty = false;
smsid_t callback_ids;

bool css::parse (nitpick& nits, const html_version& v, const ::std::string& content, const e_charcode encoding)
{   if (invalid ()) return false;
    if (content.empty ()) return true;
    parse_css (nits, v, ids_, content, encoding);
    check_for_standard_classes (nits, v);
    active_ = true;
    return true; }

bool css::parse_file (nitpick& nits, const page& p, const url& u)
{   nits.set_context (0, u.original ());
    if (context.rpt_opens ())
        nits.pick (nit_opening_file, es_debug, ec_css, "Loading ", absolute_name (u.original ()));
    ::std::string content (p.load_url (nits, u));
    if (content.empty ())
    {   nits.pick (nit_cannot_load_css, es_error, ec_css, "Cannot load ", quote (u.original ()), ", or it is empty");
        return false; }
    return parse (nits, p.version (), content, bom_to_encoding (get_byte_order (content))); }

void css::check_for_standard_classes (nitpick& nits, const html_version& v)
{   for (auto id : ids_)
    {   html_class c (nits, v, id.first);
        if (c.is_microformat_property ())
            nits.pick (nit_class_microformat_property, es_warning, ec_css, "CSS identifier ", quote (id.first), " is a microformat property");
        else if (c.is_microformat_vocabulary ())
            nits.pick (nit_class_microformat_vocabulary, es_warning, ec_css, "CSS identifier ", quote (id.first), " is a microformat vocabulary"); } }

bool css::note_usage (const ::std::string& id)
{   if (! active_) return false;
    smsid_t::iterator i = ids_.find (id);
    if (i == ids_.end ()) return false;
    if (i -> second < UINT_MAX)
        i -> second += 1;
    return true; }

void css::tally (smsid_t& ids) const
{   for (auto local : ids_)
        if (local.second > 0)
        {   smsid_t::iterator sum = ids.find (local.first);
            if (sum == ids.end ())
                ids.insert (local);
            else if (sum -> second < UINT_MAX)
                if (UINT_MAX - sum -> second <= local.second)
                    sum -> second = UINT_MAX;
                else sum -> second += local.second; } }
