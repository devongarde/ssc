/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "main/context.h"
#include "main/options.h"
#include "stats/stats.h"
#include "element/elem.h"
#include "utility/quote.h"
#include "parser/text.h"
#include "coop/fred.h"

context_t context;

context_t::context_t ()
    :   validation_ ("Additional attribute values (check " PROG "'s source code for context)", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH)
{   environment_.resize (env_max); };

int context_t::parameters (nitpick& nits, int argc, char** argv)
{   options o (nits, argc, argv);
    if (context.todo () == do_booboo) return ERROR_STATE;
    if ((context.todo () != do_examine) && (context.todo () != do_cgi)) return STOP_OK;
    o.contextualise (nits);
    if (! test () && tell (es_debug))
    {   ::std::string s (o.report ());
        outstr.init (nits, s);
        mac (nm_context_output, s); }

    for (const ::std::string& name : site_)
        if (name.find_first_not_of (ALPHANUMERIC) != ::std::string::npos)
        {   valid_ = false;
            nits.pick (nit_invalid_domain, es_error, ec_init, quote (name), " is not a valid domain name (do not include protocols)");
            return ERROR_STATE; }
    valid_ = context.cgi () || (! root ().empty ());
    return valid_ ? VALID_RESULT : ERROR_STATE; }

::std::string context_t::make_absolute_url (const ::std::string& link, bool can_use_index ) const
{    ::std::string res, srv;
    if (site_.size () > 0)
    {   srv = HTTPS;
        srv += site_.at (0);
        srv += SLASH; }
    if (link.empty ()) res = srv;
    else
    {   if (link.find (COLON) != link.npos) res = link;
        else
        {   res = srv;
            if (link.at (0) != SLASH) res += link;
            else res += link.substr (1); } }
    const ::std::size_t last = res.length () - 1;
    if (can_use_index )
    {   const bool slashed = res.at (last) == SLASH;
        if (slashed) if (! index ().empty ()) res += index (); }
    return res; }

context_t& context_t::shadow_ignore (const vstr_t& s)
{   shadow_enable (true);
    shadow_ignore_.clear ();
    for (auto ss : s)
        if (! ss.empty ())
            if (ss.at (0) == '.') shadow_ignore_.emplace_back (ss);
            else shadow_ignore_.emplace_back (::std::string (1, '.') + ss);
    mac (nm_context_shadow_ignore, shadow_ignore_);
    return *this; }

context_t& context_t::svg_version (const int mjr, const int mnr) noexcept
{   switch (mjr)
    {   case 2 :
            switch (mnr)
            {   case 0 : version_.svg_version (sv_2_0); return *this;
                case 1 : version_.svg_version (sv_2_1); return *this;
                default : break; }
            break;
        case 1 :
            switch (mnr)
            {   case 0 : version_.svg_version (sv_1_0); return *this;
                case 1 : version_.svg_version (sv_1_1); return *this;
                case 2 : version_.svg_version (sv_1_2_tiny); return *this;
                case 3 : version_.svg_version (sv_1_2_full); return *this;
                default : break; }
            break;
        default : break; }
    version_.svg_version (sv_none);
    return *this; }

context_t& context_t::math_version (const int v)
{   switch (v)
    {   case 1 : version_.math_version (math_1); break;
        case 2 : version_.math_version (math_2); break;
        case 3 : version_.math_version (math_3); break;
        case 4 : version_.math_version (math_4_22); break;
        default : version_.math_version (math_none); }
    mac < int > (nm_context_math, version_.math_version ());
    return *this; }

context_t& context_t::ignore (nitpick& nits, const vstr_t& s)
{   e_element e = elem_undefined;
    for (auto ss : s)
        if (elem :: find (html_0, ss, e)) elem :: ignore (e);
        else nits.pick (nit_unknown_element, es_error, ec_init, quote (ss), " is not an element");
    mac (nm_context_ignore, s);
    return *this; }

html_version context_t::html_ver (const int major, const int minor) noexcept
{   versioned (true);
    switch (major)
    {   case 0 :
            version_ = html_tags;
            break;
        case 1 :
            if (minor == 1) version_ = html_plus; else version_ = html_1;
            break;
        case 2 :
            version_ = html_2;
            break;
        case 3 :
            if (minor == 0) version_ = html_3_0; else version_ = html_3_2;
            break;
        case 4 :
            switch (minor)
            {   case 0 : version_ = html_4_0; break;
                case 2 : version_ = xhtml_1_0; break;
                case 3 : version_ = xhtml_1_1; break;
                case 4 : version_ = xhtml_2; break;
                default : version_ = html_4_1; break; }
            break;
        case 5 :
            switch (minor)
            {   case 0 : version_ = html_5_0; break;
                case 1 : version_ = html_5_1; break;
                case 2 : version_ = html_5_2; break;
                case 3 : version_ = html_5_3; break;
                case 4 : version_ = html_jul20; break;
                default : version_ = html_current; break; }
            break;
        default :
            version_ = html_default;
            break; }
    return version_; }

context_t& context_t::environment (const e_environment e, const ::std::string& s)
{   environment_.at (e) = s.substr (0, ARGLEN_MAX);
    return *this; }

bool context_t::rdfa () const noexcept
{   if (rdfa_) return true;
    if (version_.is_svg_12 ()) return true;
    return (version_ == xhtml_2); }

context_t& context_t::exclude (nitpick& nits, const ::std::string& s)
{   try
    {   wild_t w (s, ::boost::regex::basic_regex::extended);
        exclude_.push_back (w); }
    catch (...)
    {   nits.pick (nit_regex, es_error, ec_init, "ignoring the invalid regular expression ", quote (s)); }
    return *this; }

context_t& context_t::exclude (nitpick& nits, const vstr_t& s)
{   for (auto ss : s)
        exclude (nits, ss);
    return *this; }

bool context_t::excluded (const ::boost::filesystem::path& p) const
{   for (auto w : exclude_)
        if (::boost::regex_search (p.string (), w))
            return true;
    return false; }

context_t& context_t::fred (const int i)
{   int nmt = fred_t::no_more_than (); // <=> :-(
    if (i > nmt) fred_ = nmt;
    else if (i > 0) fred_ = i;
    else fred_ = fred_t::suggested ();
    mac (nm_context_info, fred_);
    return *this; }
