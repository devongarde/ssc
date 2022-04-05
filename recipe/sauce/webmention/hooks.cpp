/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#ifdef HAS_WM
#include "main/context.h"
#include "main/args.h"
#include "webmention/hook.h"
#include "webmention/hooks.h"
#include "webmention/wm.h"

#ifdef NO_JSONIC
bool hooks::process (nitpick& nits, const html_version& , const vstr_t& )
{   nits.pick (nit_webmention, es_error, ec_webmention, "Webmentions are not supported by this build of " PROG); }
#else // NO_JSONIC
bool hooks::empty () const noexcept { return hooks_.empty (); }

bool hooks::process (nitpick& nits, const html_version& v, const vstr_t& templates, const vstr_t& mentions)
{   bool res = false;
    for (auto s : mentions)
    {   parameters p (v, s);
        if ((! p.exists (SOURCE)) || (! p.exists (TARGET)))
            nits.pick (nit_invalid_mention, es_error, ec_webmention, "missing '" SOURCE "' or '" TARGET "' in ", quote (s));
        else
        {   hook h (nits, v, p.value (SOURCE), p.value (TARGET));
            if (! h.invalid ())
            {   const url& u = h.target ();
                ::std::string trg = u.get_filepath ();
                if (get_fileindex (trg) == nullfileindex)
                    nits.pick (nit_invalid_mention, es_error, ec_webmention, "invalid incoming " WEBMENTION ": no such page as ", quote (trg));
                else
                {   res = true;
                    if (context.tell (es_info))
                        nits.pick (nit_webmention, es_info, ec_webmention, WEBMENTION " at ", h.source ().domain (), " for ", h.target ().domain (), " found");
                    mh_t::iterator i = hooks_.find (h.page_path ());
                    if (i != hooks_.end ()) i -> second.merge (nits, h);
                    else hooks_.emplace (trg, h); } } } }
    if (res)
        for (auto h : hooks_)
            h.second.process (nits, v, templates);
    return res; }

bool hooks::load (nitpick& nits, const ::boost::json::object& jo)
{   PRESUME (hooks_.empty (), __FILE__, __LINE__);
    if (! jo.at (INPUT).is_array ()) return false;
    const ::boost::json::array& ja (jo.at (INPUT).as_array ());
    for (auto jh : ja)
        if (jh.is_object ())
        {   hook h (nits, jh.as_object ());
            if (! h.invalid ()) hooks_.emplace (h.page_path (), h); }
    return true; }

bool hooks::save (nitpick& nits, ::boost::json::object& jo)
{   ::boost::json::array ja;
    for (auto h : hooks_)
    {   ::boost::json::object jh;
        if (h.second.save (nits, jh))
            ja.emplace_back (jh); }
    if (! ja.empty ())
        jo.emplace (INPUT, ja);
    return true; }
#endif // NO_JSONIC
#endif // HAS_WM
