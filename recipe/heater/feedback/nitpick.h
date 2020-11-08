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

#pragma once
#include "feedback/nit.h"
#include "utility/lexical.h"

const char* doc_ref (const e_doc doc);

class nitpick
{   typedef ::std::vector < nit > vn_t;
    vn_t nits_;
    ::std::string context_;
    int line_ = 0;
public:
    nitpick () = default;
    nitpick (const nitpick& np) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	nitpick(nitpick&& np) = default;
#endif
	explicit nitpick(const ::std::string c) : context_(c) { }
    explicit nitpick (const int line, const ::std::string c) : context_ (c), line_ (line) { }
	~nitpick() = default;
    nitpick& operator = (const nitpick& np) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	nitpick& operator = (nitpick&& np) = default;
#endif
    nitpick& operator += (const nitpick& np) { merge (np); return *this; }
    nitpick& operator += (nitpick&& np) { merge (np); return *this; }
    void swap (nitpick& np) NOEXCEPT;
    void reset ();
    void reset (const nitpick& np);
    void merge (const nitpick& np);
    void merge (nitpick&& np);
    nitpick nick ();

    template < typename... Ts > void pick (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, Ts... msg)
    {   nits_.emplace_back (code, doc, ref, severity, category, com < Ts... > :: bine (msg...)); }
    template < typename... Ts > void pick (const e_nit code, const e_doc doc, const e_severity severity, const e_category category, Ts... msg)
    {   nits_.emplace_back (code, doc, ::std::string (), severity, category, com < Ts... > :: bine (msg...)); }
    template < typename... Ts > void pick (const e_nit code, const e_severity severity, const e_category category, Ts... msg)
    {   nits_.emplace_back (code, severity, category, com < Ts... > :: bine (msg...)); }

    void pick (const nit& n);
    void pick (nit&& n);
    void set_context (const int line, const ::std::string& c);
    void set_context (const int line, const ::std::string::const_iterator b, ::std::string::const_iterator e);
    ::std::string get_context () const { return context_; }
    int get_line () const { return line_; }
    ::std::string review () const;
    bool empty () const { return nits_.empty (); } };
