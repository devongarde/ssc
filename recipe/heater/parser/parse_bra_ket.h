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
#include "type/enum.h"
#include "feedback/nitpick.h"

class bra_element_ket
{   friend class elements_node;
    ::std::string arg_; // must occur before start_, eofe_ & end_
    ::std::string::const_iterator start_;
    ::std::string::const_iterator eofe_;
    ::std::string::const_iterator end_;
    int line_ = 0;
    bk_status status_ = bk_text;
    e_element suspender_ = elem_undefined;
    bool closure_ = false, closed_ = false, tested_ = false;
    nitpick nits_;
    void test_specific ();
public:
    bra_element_ket () = delete;
    bra_element_ket (nitpick& nits, const int line, const ::std::string::const_iterator s, const ::std::string::const_iterator eofe, const ::std::string::const_iterator e, const bool closure, const bool closed)
        : start_ (s), eofe_ (eofe), end_ (e), line_ (line), status_ (bk_node), closure_ (closure), closed_ (closed), tested_ (false), nits_ (nits.nick ())
    { }
    bra_element_ket (nitpick& nits, const int line, const bk_status bks, const ::std::string::const_iterator s, const ::std::string::const_iterator e)
        : start_ (s), eofe_ (e), end_ (e), line_ (line), status_ (bks), closure_ (false), closed_ (true), tested_ (false), nits_ (nits.nick ())
    { }
    bra_element_ket (nitpick& nits, const int line, const bk_status bks, const ::std::string arg)
        : arg_ (arg), start_ (arg_.begin ()), eofe_ (arg_.end ()), end_ (arg_.end ()), line_ (line), status_ (bks), closure_ (false), closed_ (true), tested_ (false), nits_ (nits.nick ())
    { }
    bra_element_ket (nitpick& nits, const int line, const ::std::string::const_iterator s, const ::std::string::const_iterator e)
        : start_ (s), eofe_ (e), end_ (e), line_ (line), status_ (bk_text), closure_ (false), closed_ (true), tested_ (false), nits_ (nits.nick ())
    { }
    bra_element_ket (const bra_element_ket& bek) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	bra_element_ket(bra_element_ket&& bek) = default;
#endif
	~bra_element_ket () = default;
    bra_element_ket& operator = (const bra_element_ket& bek) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	bra_element_ket& operator = (bra_element_ket&& bek) = default;
#endif
    e_element suspender ();
    bool is_xmp ();
    bool is_plaintext ();
    bool is_whitespace () const;
    bool is_silent_content ();
    bool is_closed () const { return closed_; }
    bool is_closure () const { return closure_; }
    ::std::string arg () const { return arg_; }
    ::std::string text () const;
    ::std::string rpt () const; };
