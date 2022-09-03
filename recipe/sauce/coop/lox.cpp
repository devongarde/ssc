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
#include "coop/lox.h"

typedef ::std::array < ::std::mutex, lox_error > vmx_t;
vmx_t vmx;

bool dont_bother ()
{   if (context.fred () == 1) return true;
    return ! fred.started (); }

lox::lox (const e_lox l)
    : l_ (lox_none), un_ (false)
{   if (dont_bother ()) return;
    PRESUME (l < lox_error, __FILE__, __LINE__);
    PRESUME (l != lox_flox, __FILE__, __LINE__);
    PRESUME (l != lox_dear, __FILE__, __LINE__);
    PRESUME (fred.get_lox () == lox_none, __FILE__, __LINE__);
    PRESUME (! fred.get_flox (), __FILE__, __LINE__);
    fred.set_lox (l);
    l_ = l;
    un_ = false;
#ifdef RPT_LOX
    ::std::cout << ::std::this_thread::get_id () << " trying to lock " << l_ << ::std::endl;
#endif // RPT_LOX
    vmx.at (l).lock ();
#ifdef RPT_LOX
    ::std::cout << ::std::this_thread::get_id () << " locked " << l_ << ::std::endl;
#endif // RPT_LOX
    }

flox::flox (const e_lox l)
{   if (dont_bother ()) return;
    PRESUME (l == lox_flox, __FILE__, __LINE__);
    PRESUME (! fred.get_flox (), __FILE__, __LINE__);
    fred.set_flox (true);
#ifdef RPT_LOX
   ::std::cout << ::std::this_thread::get_id () << " trying to lock flox" << ::std::endl;
#endif // RPT_LOX
    vmx.at (lox_flox).lock ();
#ifdef RPT_LOX
    ::std::cout << ::std::this_thread::get_id () << " locked flox" << ::std::endl; 
#endif // RPT_LOX
    }

dear::dear (const e_lox l)
{   if (dont_bother ()) return;
    PRESUME (l == lox_dear, __FILE__, __LINE__);
    PRESUME (! fred.get_dear (), __FILE__, __LINE__);
    fred.set_dear (true);
#ifdef RPT_LOX
    ::std::cout << ::std::this_thread::get_id () << " trying to lock dear" << ::std::endl;
#endif // RPT_LOX
    vmx.at (lox_dear).lock ();
#ifdef RPT_LOX
    |::std::cout << ::std::this_thread::get_id () << " locked dear" << ::std::endl;
#endif // RPT_LOX
    }

void whoopsie (const e_lox l, const char * sz, const ::std::exception& e) noexcept
{   try
    {   ::std::cerr << "unlocking mutex " << l << " raised " << sz << " " << e.what () << "; aborting\n"; }
    catch (...)
    {   fprintf (stderr, "exception in mutex exception processing; aborting."); } }

lox::~lox ()
{   if (dont_bother ()) return;
    if (un_) return;
    const e_lox l = l_;
    try
    {   PRESUME (fred.get_lox () == l_, __FILE__, __LINE__);
#ifdef RPT_LOX
        ::std::cout << ::std::this_thread::get_id () << " unlocking " << l_ << ::std::endl;
#endif // RPT_LOX
       l_ = lox_none;
        vmx.at (l).unlock (); // hey, mr. vc, have you spotted that try ... catch construction??
        fred.set_lox (lox_none);
        return; }
    catch (const ::std::system_error& e)
    {   whoopsie (l, "system error", e); }
    catch (const ::std::exception& e)
    {   whoopsie (l, "exception", e); }
    catch (...)
    {   fprintf (stderr, "unknown mutex exception; aborting."); }
    GRACELESS_CRASH (__FILE__, __LINE__); }

flox::~flox ()
{   if (dont_bother ()) return;
    try
    {   PRESUME (fred.get_flox (), __FILE__, __LINE__);
#ifdef RPT_LOX
        ::std::cout << ::std::this_thread::get_id () << " unlocking flox" << ::std::endl;
#endif // RPT_LOX
        vmx.at (lox_flox).unlock ();
        fred.set_flox (false);
        return; }
    catch (const ::std::system_error& e)
    {   whoopsie (lox_flox, "system error", e); }
    catch (const ::std::exception& e)
    {   whoopsie (lox_flox, "exception", e); }
    catch (...)
    {   fprintf (stderr, "unknown flox mutex exception; aborting."); }
    GRACELESS_CRASH (__FILE__, __LINE__); }

dear::~dear ()
{   if (dont_bother ()) return;
    try
    {   PRESUME (fred.get_dear (), __FILE__, __LINE__);
#ifdef RPT_LOX
        ::std::cout << ::std::this_thread::get_id () << " unlocking dear" << ::std::endl;
#endif // RPT_LOX
        vmx.at (lox_dear).unlock ();
        fred.set_dear (false);
        return; }
    catch (const ::std::system_error& e)
    {   whoopsie (lox_dear, "system error", e); }
    catch (const ::std::exception& e)
    {   whoopsie (lox_dear, "exception", e); }
    catch (...)
    {   fprintf (stderr, "unknown dear mutex exception; aborting."); }
    GRACELESS_CRASH (__FILE__, __LINE__); }

::std::mutex& lox::mx (const e_lox l)
{   PRESUME (fred.started (), __FILE__, __LINE__);
    return vmx.at (l); }

::std::mutex& flox::mx ()
{   PRESUME (fred.started (), __FILE__, __LINE__);
    return vmx.at (lox_flox); }
