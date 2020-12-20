/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

context_t context;

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
    if (! test () && tell (e_debug)) out () << o.report ();
    for (const ::std::string& name : site_)
        if (name.find_first_not_of (ALPHABET DDD) != ::std::string::npos)
        {   valid_ = false;
            context.err () << quote (name) << " is not a valid domain name (do not include protocols)\n";
            return false; }
    valid_ = ! root ().empty ();
    return valid_ ? VALID_RESULT : ERROR_STATE; }

context_t& context_t::webmention (const ::std::string& w, const e_wm_status status)
{   if (! w.empty () && status > wm_status_)
    {   webmention_ = w;
        if (tell (e_variable)) out () << "setting context_t " WEBMENTION " to " << quote (w) << "\n";
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

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i)
{   ::std::string res;
    ::std::string::const_iterator mb, me;
    if (e - b <= 60) { me = e; mb = b; }
    else
    {   if (b + 30 >= i) mb = b; else mb = i - 30;
        if (e - 30 <= i) me = e; else me = i + 30; }
    bool en = false;
    bool nudged = false;
    bool nonblank = false;
    for (::std::string::const_iterator j = mb; j < i; ++j)
        if (::std::iswspace (*j) || ::std::iswcntrl (*j)) { mb = j+1; nudged = true; } else nonblank = true;
    if (! nudged && nonblank) res += "... ";
    nonblank = false;
    for (::std::string::const_iterator j = i; j < e; ++j)
        if (::std::iswspace (*j) || ::std::iswcntrl (*j)) { me = j; en = true; break; } else nonblank = true;
    res += ::std::string (mb, me);
    if (! en && nonblank) res += " ...";
    return res; }

::std::string near_here (::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i, const ::std::string& msg, const e_verbose level)
{   if (msg.empty () || ! context.tell (level)) return ::std::string ();
    ::std::string res (near_here (b, e, i));
    if (! res.empty ()) res += "\n";
    res += fyi () + msg + "\n";
    return res; }

context_t& context_t::html_minor (const int i)
{   if ((i < 0) || (i > 255)) { html_major_ = 0; html_minor_ = 1; }
    else
    {   html_minor_ = static_cast < unsigned char > (i);
        if ((sch_major_ == 0) && (html_major_ >= 5))
        {   schema_version v (html_to_schema_version (html_ver ()));
            sch_major_ = v.mjr ();
            sch_minor_ = v.mnr (); } }
    return *this; }

context_t& context_t::html_major (const int i)
{   if ((i < 0) || (i > 255)) { html_major_ = 0; html_minor_ = 1; }
    else
    {   html_major_ = static_cast < unsigned char > (i);
        if ((sch_major_ == 0) && (i >= 5))
        {   schema_version v (html_to_schema_version (html_ver ()));
            sch_major_ = v.mjr ();
            sch_minor_ = v.mnr (); } }
    return *this; }

context_t& context_t::svg_version (const int mjr, const int mnr)
{   if (html_major_ > 3)
    {  if (mjr == 2)
        {   if (mnr == 0)
            {   svg_version_ = sv_2_0; return *this; } }
        else if (mjr == 1)
            switch (mnr)
            {   case 0 : svg_version_ = sv_1_0; return *this;
                case 1 : svg_version_ = sv_1_1; return *this;
                case 2 : svg_version_ = sv_1_2_tiny; return *this;
                case 3 : svg_version_ = sv_1_2_full; return *this;
                default : break; }
        if (html_major_ > 4) { svg_version_ = sv_2_0; return *this; } }
    else svg_version_ = sv_none;
    return *this; }

html_version context_t::html_ver () const
{   html_version res (html_major (), html_minor ());
    res.svg_version (svg_version_);
    res.math_version (math_version_);
    return res; }

context_t& context_t::ignore (const vstr_t& s)
{   e_element e = elem_undefined;
    for (auto ss : s)
        if (elem :: find (html_0, ss, e)) elem :: ignore (e);
        else err () << quote (ss) << " is not an element\n";
    return *this; }
