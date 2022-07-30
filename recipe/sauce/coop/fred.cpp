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
#include "type/enum.h"
#include "main/context.h"
#include "coop/fred.h"
#include "webpage/q.h"
#include "coop/kew.h"
#include "coop/knickers.h"
 
fred_t fred;

int fred_t::tls_int () const
{   const ::std::thread::id f (::std::this_thread::get_id ());
    const auto i = tls_.find (f);
    PRESUME (i != tls_.cend (), __FILE__, __LINE__);
    const int n = i -> second;
    PRESUME ((n >= 0) && (static_cast < ::std::size_t > (n) < vtls_.size ()), __FILE__, __LINE__);
    VERIFY_NOT_NULL (vtls_.at (n), __FILE__, __LINE__);
    return n; }

fred_tls& fred_t::tls ()
{   return *vtls_.at (tls_int ()); }

const fred_tls& fred_t::tls () const
{   return *vtls_.at (tls_int ()); }

void fred_t::insert_tls (const int n, const ::std::thread::id& fid)
{   mid_t::value_type mvt (fid, n);
    auto p = tls_.insert (mvt);
    PRESUME (p.second, __FILE__, __LINE__); }

bool fred_t::dqe ()
{   q_entry t (st_max);
    if (! q.pop (t))
        ::std::this_thread::yield ();
    else if (t.valid ())
    {   if (context.tell (es_detail))
        {   lox l (lox_nits);
            t.ticks_ -> pick (nit_detail, es_detail, ec_fred, "Fred ", ::std::this_thread::get_id (), " stage ", t.stage_, " processing ", t.dir_ -> get_site_path ()); }
        if (! d_q (t)) return false; }
    else if (t.ticks_ != nullptr)
    {   lox l (lox_nits);
        t.ticks_ -> pick (nit_kew_borked, es_error, ec_fred, "Fred ", ::std::this_thread::get_id (), " stage ", t.stage_, ", got borked directory"); }
    return ! abandon_; }

void fred_t::fred_minion (nitpick* ticks)
{   counting c;
    const ::std::thread::id i = ::std::this_thread::get_id ();
    ::std::this_thread::yield ();
    while (! started_)
        if (abandon_) return;
        else ::std::this_thread::yield (); // yuk on stilts
    nitpick nits;
    knickers k (nits, ticks);
    if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_fred, "Starting fred ", i);
    try
    {   while (! abandon_) dqe (); }
    catch (const ::std::system_error& e)
    {   nits.pick (nit_fred_borked, es_catastrophic, ec_fred, "minion system error ", e.what ()); }
    catch (const ::std::exception& e)
    {   nits.pick (nit_fred_borked, es_catastrophic, ec_fred, "minion exception ", e.what ()); }
    catch (...)
    {   nits.pick (nit_fred_borked, es_catastrophic, ec_fred, "unknown minion exception"); }
    if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_fred, "Ending fred ", ::std::this_thread::get_id ()); }

void fred_t::abandon ()
{   abandon_ = true;
    for (int i = 0; i < context.fred (); ++i)
        q.push (q_entry (st_finish));
    ::std::this_thread::yield (); }

bool fred_t::init (nitpick& nits)
{   PRESUME (! fred.inited (), __FILE__, __LINE__);
    const int qu = context.fred ();
    if (context.tell (es_detail)) nits.pick (nit_detail, es_detail, ec_fred, qu, " threads");
    const ::std::thread::id f = ::std::this_thread::get_id ();
    if (context.tell (es_detail)) nits.pick (nit_detail, es_detail, ec_fred, "Maestro fred: ", f);
    vtls_.resize (qu);
    tls_ptr ptr (new fred_tls (fred_maestro));
    vtls_.at (0) = ptr;
    insert_tls (0, f);
    for (int i = 1; i < qu; ++i)
    {   tls_ptr p (new fred_tls ());
        vtls_.at (i) = p; }
    nitpick nuts;
    knickers k (nuts, &nits);
    for (int i = 1; i < qu; ++i)
    {   try
        {   vt_.emplace_back (::std::thread (&fred_t::fred_minion, this, &nits));
            const ::std::thread::id d = vt_.at (vt_.size () - 1).get_id ();
            insert_tls (i, d);
            ::std::this_thread::yield ();
            if (context.tell (es_detail)) nuts.pick (nit_detail, es_detail, ec_fred, "Minion fred ", i, ": ", d); }
        catch (const ::std::system_error& e)
        {   nuts.pick (nit_fred_borked, es_catastrophic, ec_fred, "cannot create fred, system error: ", e.what ()); return false; }
        catch (const ::std::exception& e)
        {   nuts.pick (nit_fred_borked, es_catastrophic, ec_fred, "cannot create fred, exception: ", e.what ()); return false; }
        catch (...)
        {   nuts.pick (nit_fred_borked, es_catastrophic, ec_fred, "cannot create fred: unknown exception"); return false; } }
    started_ = true;
    ::std::this_thread::yield (); 
    return true; }

void fred_t::one_less () noexcept
{   if (count_ > 0)
    {   --count_;
        if (count_ == 0)
            try
            {   abandon (); }
            catch (...)
            { } } }

void fred_t::done ()
{   abandon ();
    for (auto i = vt_.begin (); i != vt_.end (); ++i)
        if (i -> get_id () != ::std::this_thread::get_id ())
            if (i -> joinable ())
                i -> join ();  }
