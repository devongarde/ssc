/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "utility/lexical.h"

#ifdef SIGNING
#include "utility/ssl.h"
#endif // SIGNING

class nitpick;

#ifdef WX
class wxLogWindow;
#endif // WX

class outstream
{   fstr_p fos_;
#ifdef WX
    bool wx_ = false;
#endif // WX
    ::std::string name_;
    bool inited_ = false;
    mutable ::std::string pre_;
#ifdef SIGNING
    typedef ::std::atomic < e_signing_status > atomic_signing_status;
    atomic_signing_status status_ = sis_unknown;
    svf_sha256_ptr sf_;
    ::boost::filesystem::path pub_, pri_, sig_;
#endif // SIGNING
    ::std::string ensane (const ::std::string& s) const;
    static void dup () noexcept;
public:
    outstream () = default;
    NO_COPY_NO_MOVE (outstream);
    ~outstream () { dup (); }
    void init (nitpick& nits, const ::std::string& s);
    const ::std::string& name () const noexcept { return name_; }
#ifdef WX
    void enloggen (const bool b) noexcept { wx_ = b; }
#endif // WX
#ifndef SIGNING
    void aborting () noexcept { }
    void consolidate (nitpick& nits, const ::boost::filesystem::path& , const ::boost::filesystem::path& , const ::std::string& , const ::boost::filesystem::path& )
    {   depre (nits); }
    bool done (nitpick& ) noexcept { return true; }
    bool verifying () const noexcept { return false; }
    bool signing () const noexcept { return false; }
    bool sigout (nitpick& ) noexcept { return true; }
#else // SIGNING
    void aborting ();
    void consolidate (nitpick& nits, const ::boost::filesystem::path& pub, const ::boost::filesystem::path& pri, const ::std::string& pw, const ::boost::filesystem::path& signature);
    bool done (nitpick& nits) noexcept;
    bool verifying () const noexcept { return status_ == sis_verifying; }
    bool signing () const noexcept { return status_ == sis_signing; }
    bool sigout (nitpick& nits);
#endif // SIGNING
    bool depre (nitpick& nits);
    void out (const ::std::string& s) const;
    void console (const ::std::string& s) const { out (s); }
    void err (const ::std::string& s) const { out (s); }
    bool invalid () const noexcept { return fos_.get () == nullptr; }
    template < typename... Ts > void out (const ::std::string& s, Ts... msg) const
    {   out (s + com < Ts... > :: bine (msg...)); }
    template < typename... Ts > void console (const ::std::string& s, Ts... msg) const
    {   console (s + com < Ts... > :: bine (msg...)); }
    template < typename... Ts > void err (const ::std::string& s, Ts... msg) const
    {   err (s + com < Ts... > :: bine (msg...)); } };

typedef ::std::shared_ptr < outstream > os_ptr;
