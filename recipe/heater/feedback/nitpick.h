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
#include "feedback/nit.h"
#include "utility/lexical.h"

class nitpick
{   typedef ::std::vector < nit > vn_t;
    typedef ssc_map < e_nit, e_severity > mns_t;
    vn_t nits_;
    static mns_t mns_;
    ::std::string before_, mote_, after_;
    int line_ = 0;
    static bool fe_, sarcasm_;
    static e_severity user_severity (const e_nit code, const e_severity s)
    {   mns_t::const_iterator i = mns_.find (code);
        if (i != mns_.cend ()) return i -> second;
        return s; }
    template < class T > ::std::string inner_review (const e_nit_section& entry, const T& t, const mmac_t& mac, mmac_t& outer, bool& quote, bool& dq, bool& infoed, bool& eol, bool& hasns, const bool unfiltered) const;
public:
    nitpick () = default;
    nitpick (const nitpick& np) = default;
	nitpick(nitpick&& np) = default;
	explicit nitpick (const ::std::string& c) : mote_ (c) { }
    explicit nitpick (const int line, const ::std::string& c) : mote_ (c), line_ (line) { }
    explicit nitpick (const int line, const ::std::string& b, const ::std::string& m, const ::std::string& a)
        :   before_ (b), mote_ (m), after_ (a), line_ (line) { }
	~nitpick() = default;
    nitpick& operator = (const nitpick& np) = default;
	nitpick& operator = (nitpick&& np) = default;
    nitpick& operator += (const nitpick& np) { merge (np); return *this; }
    nitpick& operator += (nitpick&& np) { merge (np); return *this; }
    static void modify_severity (const e_nit code, const e_severity s)
    {   mns_.emplace (mns_t::value_type (code, s)); }
    static bool modify_severity (const ::std::string& name, const e_severity s);
    void swap (nitpick& np) noexcept;
    void reset ();
    void reset (const nitpick& np);
    void merge (const nitpick& np);
    void merge (nitpick&& np);
    nitpick nick ();

    template < typename... Ts > void pick (const e_nit code, const e_doc doc, const ::std::string& ref, const e_severity severity, const e_category category, Ts... msg)
    {   nits_.emplace_back (code, doc, ref, user_severity (code, severity), category, com < Ts... > :: bine (msg...)); }
    template < typename... Ts > void pick (const e_nit code, const e_doc doc, const e_severity severity, const e_category category, Ts... msg)
    {   nits_.emplace_back (code, doc, ::std::string (), user_severity (code, severity), category, com < Ts... > :: bine (msg...)); }
    template < typename... Ts > void pick (const e_nit code, const e_severity severity, const e_category category, Ts... msg)
    {   nits_.emplace_back (code, user_severity (code, severity), category, com < Ts... > :: bine (msg...)); }

    void pick (const nit& n);
    void pick (nit&& n);
    void set_context (const int line, const ::std::string& c);
    void set_context (const int line, const ::std::string::const_iterator b, ::std::string::const_iterator e);
    void set_context (const int line, ::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i);
    void set_context (const int line, ::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator from, ::std::string::const_iterator to);
    void set_context (const int line, ::std::string::const_iterator b, ::std::string::const_iterator e, ::std::string::const_iterator i, const ::std::string& msg, const e_severity level = es_comment);
    ::std::string get_context () const { return mote_; }
    int get_line () const  noexcept{ return line_; }
    ::std::string review (const mmac_t& mac, const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none, const bool unfiltered = false) const;
    ::std::string review (const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none) const;
    ::std::string unfiltered (const e_nit_section& entry = ns_nit, const e_nit_section& head = ns_nits_head, const e_nit_section& foot = ns_nits_foot, const e_nit_section& page_head = ns_none) const;
    e_severity worst () const;
    ::std::size_t size () const { return nits_.size (); }
    bool empty () const noexcept { return nits_.empty (); }

    static void fe (const bool b) noexcept { fe_ = b; }
    static bool fe () noexcept { return fe_; }
    static void sarcasm (const bool b) noexcept { sarcasm_ = b; }
    static bool sarcasm () noexcept { return sarcasm_; } };
