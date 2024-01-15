/*
ssc (static site checker)
File Info
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

#pragma once
#ifndef NO_FRED

#include "coop/tls.h"

class fred_t
{   mid_t tls_; // must not be modified once threading starts
    vtls_t vtls_;
    ::std::atomic_uint count_;
    ::std::atomic_uint inactive_;
    ::std::atomic_bool started_;
    ::std::atomic_bool abandon_;
    vth_t vt_;
    ::std::size_t tls_int () const;
    void fred_minion (nitpick* ticks);
public:
    fred_t () : count_ (0), inactive_ (0), started_ (false), abandon_ (false) { }
    NO_COPY_CONSTRUCTORS (fred_t);
    ~fred_t () = default;
    bool init (nitpick& nits);
    bool reinit (nitpick& nits);
    void await ();
    void done ();
    bool inited () const noexcept { return ! tls_.empty (); }
    bool abandoned () const noexcept { return abandon_; }
    bool started () const noexcept { return started_; }
    void abandon ();
    void activate () noexcept
    {   try
        {   PRESUME (inactive_ > 0, __FILE__ , __LINE__);
            inactive_ -= 1; }
        catch (...) { /* abort? */ } }
    void inactivate () noexcept
    {   try
        {   inactive_ += 1; }
        catch (...) { /* abort? */ } }
    bool activity () const noexcept
    {   return (count_ > 0) && (inactive_ < count_); }
    bool relaxed () const noexcept;
    fred_tls& tls ();
    const fred_tls& tls () const;
    void insert_tls (const ::std::size_t n, const ::std::thread::id& fid);
    bool dqe ();
    const mid_t& mid () const noexcept { return tls_; }
    e_fred get_fred () const { return tls ().fred_; }
    e_lox get_lox () const { return static_cast < e_lox > (static_cast < int > (tls ().lox_)); }
    void set_lox (const e_lox l) { tls ().lox_ = static_cast < int > (l); }
    bool get_flox () const { return inited () && tls ().flox_; }
    void set_flox (const bool b) { if (inited ()) tls ().flox_ = b; }
    bool get_dear () const { return inited () && tls ().dear_; }
    void set_dear (const bool b) { if (inited ()) tls ().dear_ = b; }
    bool get_eleanor () const { return inited () && tls ().eleanor_; }
    void set_eleanor (const bool b) { if (inited ()) tls ().eleanor_ = b; }
    unsigned count () const noexcept { return count_; }
    void one_more () noexcept { ++count_; }
    void one_less () noexcept { if (count_ > 0) --count_; }
    void yield () noexcept
    {   if (count_ > 0) ::std::this_thread::yield (); }
    static void onexit ();
    static ::std::size_t suggested ();
    static ::std::size_t no_more_than (); };

extern fred_t fred;

struct faffing
{   faffing () { fred.inactivate (); }
    NO_COPY_CONSTRUCTORS (faffing);
    ~faffing () { fred.activate (); } };

struct counting
{   counting () { fred.one_more (); }
    NO_COPY_CONSTRUCTORS (counting);
    ~counting () { fred.one_less (); } };
#endif // NO_FRED
