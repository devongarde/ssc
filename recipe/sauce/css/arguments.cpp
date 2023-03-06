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
#include "type/type.h"
#include "css/flags.h"
#include "css/arguments.h"
#include "css/selectors.h"
#include "css/statement.h"
#include "css/group.h"
#include "webpage/page.h"

void arguments::check_flags (nitpick& nits, const flags_t f, const ::std::string& s) const
{   if ((f & CF_MUST_FONT_FACE) == CF_MUST_FONT_FACE)
        if ((st_ == nullptr) || (st_ -> get () != css_font_face))
            nits.pick (nit_naughty_page, es_error, ec_css, s, " requires @font-face");
    if ((f & CF_BEF_AFT) == CF_BEF_AFT)
        if ((ss_ == nullptr) || (! ss_ -> bef_aft ()))
            nits.pick (nit_naughty_content, es_error, ec_css, s, " requires an element with :before andor :after"); }

void arguments::validate (nitpick& nits, const flags_t f, const ::std::string& p, const ::std::string& vl) const
{   if ((f & CF_PAGE) == CF_PAGE)
        if (! ps_ -> state ().test (ec_page_property))
            if ((st_ == nullptr) || ((st_ -> get () != css_page) && (st_ -> get () != css_media)))
                nits.pick (nit_naughty_page, es_error, ec_css, p, " requires @page, @media, or the page property");
    if ((f & CF_PAGE_NAME) == CF_PAGE_NAME)
    {   const sstr_t& pn (g_.page_name ());
        ::std::string vll (trim_the_lot_off (vl));
        if (pn.find (::boost::to_lower_copy (vll)) == pn.cend ())
            nits.pick (nit_no_such_page, es_error, ec_css, quote (vll), " is not a known page name"); } }
