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

#pragma once
#include "coop/tls.h"

class fred_t
{   mid_t tls_; // must not be modified once threading starts
    vtls_t vtls_;
    ::std::atomic_int count_ = 0;
    ::std::atomic_int active_ = 0;
    ::std::atomic_bool started_ = false;
    ::std::atomic_bool abandon_ = false;
    vth_t vt_;
    int tls_int () const;
    void fred_minion (nitpick* ticks);
public:
    bool init (nitpick& nits);
    void done ();
    bool inited () const noexcept { return ! tls_.empty (); }
    bool abandoned () const noexcept { return abandon_; }
    bool started () const noexcept { return started_; }
    void abandon ();
    void active () noexcept { try { active_ += 1; } catch (...) { /* abort */ } }
    void inactive () noexcept { try { active_ -= 1; } catch (...) { /* abort */ } }
    bool activity () const noexcept { return active_ > 0; }
    fred_tls& tls ();
    const fred_tls& tls () const;
    void insert_tls (const int n, const ::std::thread::id& fid);
    bool dqe ();
    const mid_t& mid () const noexcept { return tls_; }
    e_fred get_fred () const { return tls ().fred_; }
    e_lox get_lox () const { return static_cast < e_lox > (static_cast < int > (tls ().lox_)); }
    void set_lox (const e_lox l) { tls ().lox_ = static_cast < int > (l); }
    bool get_flox () const { return inited () && tls ().flox_; }
    void set_flox (const bool b) { if (inited ()) tls ().flox_ = b; }
    bool get_dear () const { return inited () && tls ().dear_; }
    void set_dear (const bool b) { if (inited ()) tls ().dear_ = b; }
    int count () const noexcept { return count_; }
    void one_more () noexcept { ++count_; }
    void one_less () noexcept;
    static int suggested ();
    static int no_more_than (); };

extern fred_t fred;

struct faffing
{   faffing () { fred.inactive (); }
    faffing (const faffing& ) = delete;
    faffing (faffing&& ) = delete;
    ~faffing () { fred.active (); }
    faffing operator = (const faffing& ) = delete;
    faffing operator = (faffing&& ) = delete; };

struct counting
{   counting () { fred.one_more (); fred.active (); }
    counting (const counting& ) = delete;
    counting (counting&& ) = delete;
    ~counting () { fred.inactive (); fred.one_less (); }
    counting operator = (const counting& ) = delete;
    counting operator = (counting&& ) = delete; };