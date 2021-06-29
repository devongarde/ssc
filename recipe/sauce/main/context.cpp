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
#include "main/context.h"
#include "main/options.h"
#include "webmention/irt.h"
#include "webmention/hook.h"
#include "stats/stats.h"
#include "element/elem.h"
#include "utility/quote.h"
#include "parser/text.h"

context_t context;

context_t::context_t ()
    :   validation_ ("Additional attribute values (check " PROG "'s source code for context)", DEFAULT_LINE_LENGTH, DESCRIPTION_LENGTH)
{   environment_.resize (env_max); };

context_t& context_t::output (const ::std::string& s)
{   output_ = s;
    fos_.reset (new ::std::ofstream (s));
    if (fos_ -> fail ())
    {   ::std::cerr << "cannot open " << s << " for output.\n";
        fos_.reset (); }
    return *this; }

int context_t::parameters (int argc, char** argv)
{   options o (argc, argv);
    if (o.stop ()) return STOP_OK;
    if (o.invalid ()) return ERROR_STATE;
    o.contextualise ();
    if (! test () && tell (e_debug)) out (o.report ());
    for (const ::std::string& name : site_)
        if (name.find_first_not_of (ALPHADDD) != ::std::string::npos)
        {   valid_ = false;
            context.err (quote (name));
            context.err (" is not a valid domain name (do not include protocols)\n");
            return false; }
    valid_ = context.cgi () || (! root ().empty ());
    return valid_ ? VALID_RESULT : ERROR_STATE; }

context_t& context_t::webmention (const ::std::string& w, const e_wm_status status)
{   if (! w.empty () && status > wm_status_)
    {   webmention_ = w;
        if (tell (e_variable))
        {   out ("setting context_t " WEBMENTION " to ");
            out (quote (w));
            out ("\n"); }
        wm_status_ = status; }
    return *this; }

::std::string context_t::make_absolute_url (const ::std::string& link, bool can_use_index ) const
{    ::std::string res, srv;
    if (site_.size () > 0)
    {   srv = HTTPS;
        srv += site_ [0];
        srv += SLASH; }
    if (link.empty ()) res = srv;
    else
    {   if (link.find (COLON) != link.npos) res = link;
        else
        {   res = srv;
            if (link [0] != SLASH) res += link;
            else res += link.substr (1); } }
    ::std::size_t last = res.length () - 1;
    if (can_use_index )
    {   bool slashed = res [last] == SLASH;
        if (slashed) if (! index ().empty ()) res += index (); }
    return res; }

void context_t::process_outgoing_webmention (nitpick& nits, const html_version& v)
{   if (notify ()) replies_.process (nits, v); }

void context_t::process_incoming_webmention (nitpick& nits, const html_version& v)
{   if (! mentions_.empty ()) hooks_.process (nits, v); }

schema_version context_t::mf_ver () const
{   switch (mf_version_)
    {   case 1 : return mf_1;
        case 2 : return mf_2;
        default : return mf_all; } }

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator from, ::std::string::const_iterator to)
{   BOOST_STATIC_ASSERT (DEFAULT_LINE_LENGTH - 16 <= INT8_MAX);
    int maxish = DEFAULT_LINE_LENGTH - 16;
    if ((to - from) > INT8_MAX) return ::std::string (from, to);
    int len = static_cast < int > (to - from);
    if (len >= maxish) return ::std::string (from, to);
    int halfish = (maxish - len) / 2;
    ::std::string pre, post;
    ::std::string::const_iterator mb, me;
    if ((e - b) <= maxish) { me = e; mb = b; }
    else
    {   if ((b + halfish) >= from) mb = b; else { mb = from - halfish; pre = "..."; }
        if ((e - halfish) <= to) me = e; else { me = to + halfish; post = "..."; } }
    return pre + ::std::string (mb, from) + " *** " + ::std::string (from, to) + " *** " + ::std::string (to, me) + post; }

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i)
{   return near_here (b, e, i, i); }

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i, const ::std::string& msg, const e_verbose level)
{   if (msg.empty () || ! context.tell (level)) return ::std::string ();
    ::std::string res (near_here (b, e, i));
    if (! res.empty ()) res += "\n";
    res += fyi () + msg + "\n";
    return res; }

context_t& context_t::shadow_ignore (const vstr_t& s)
{   shadow_ignore_.clear ();
    for (auto ss : s)
        if (! ss.empty ())
            if (ss.at (0) == '.') shadow_ignore_.emplace_back (ss);
            else shadow_ignore_.emplace_back (::std::string (1, '.') + ss);
    return *this; }

context_t& context_t::svg_version (const int mjr, const int mnr)
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
        default : break; }
    version_.svg_version (sv_none);
    return *this; }

context_t& context_t::ignore (const vstr_t& s)
{   e_element e = elem_undefined;
    for (auto ss : s)
        if (elem :: find (html_0, ss, e)) elem :: ignore (e);
        else
        {   err (quote (ss));
            err (" is not an element\n"); }
    return *this; }

html_version context_t::html_ver (const int major, const int minor)
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

::std::string context_t::ensane (const ::std::string& s) const
{   if (cgi ()) return enwotsit (s);
    return s; }

context_t& context_t::environment (const e_environment e, const ::std::string& s)
{   environment_.at (e) = s.substr (0, ARGLEN_MAX);
    return *this; }

bool context_t::severity_exceeded () const
{   for (int x = 1; x <= static_cast < int > (report_error_); ++x)
        if (data_.count (static_cast < e_severity> (x))) return true;
    return false; }
