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
#include "utility/common.h"
#include "feedback/nitpick.h"
#include "url/url.h"
#include "main/context.h"
#include "type/type.h"

bool is_in_root (nitpick& nits, const ::std::string& site_path, const char* const name);
bool demangle_line (const ::std::string& l, ::std::string& cmd, ::std::string& arg, bool& valid);

class url;
class directory;

template < class ENUM, e_type TYPE > struct colony
{   nitpick nits_;
    ENUM cmd_ = static_cast < ENUM > (0);
    ::std::string orig_, arg_;
    bool valid_ = false;
    url u_;
    unsigned line_ = 0;
    void parse (const unsigned line, const ::std::string& l)
    {   ::std::string cmd;
        line_ = line;
        orig_ = trim_the_lot_off (l);
        nits_.set_context (line, orig_);
        if (demangle_line (orig_, cmd, arg_, valid_))
        {   cmd_ = examine_value < TYPE > (nits_, context.html_ver (), cmd);
            if (cmd_ == 0) valid_ = false; } }
    explicit colony (const unsigned line, const ::std::string& l)
    {   parse (line, l); }
    colony () = delete;
    DEFAULT_COPY_CONSTRUCTORS (colony);
    ::std::string rpt () const
    {   ::std::string res (::boost::lexical_cast < ::std::string > (line_) + ": ");
        res += ::boost::lexical_cast < ::std::string > (static_cast < int > (cmd_));
        res += " ";
        res += arg_ + " (" + ::boost::lexical_cast < ::std::string > (nits_.size ()) + " nits) [" + orig_ + "]";
        return res; } };

template < class ENUM, e_type TYPE > struct colonic
{   typedef ::std::vector < colony < ENUM, TYPE > > v_col;
    typedef typename v_col::iterator vi_col;
    typedef typename v_col::const_iterator vic_col;
    v_col l_;
    bool valid_ = false;
    DEFAULT_CONSTRUCTORS (colonic);
    void reset ()
    {   valid_ = false;
        l_.clear (); }
    void swap (colonic < ENUM, TYPE >& r)
    {   ::std::swap (valid_, r.valid_);
        l_.swap (r.l_); }
    bool empty () const
    {   return l_.empty (); }
    void parse (const ::std::string& content)
    {   ::std::string l;
        valid_ = true;
        unsigned line = 0;
        for (auto ch : content)
            switch (ch)
            {   case '\n' :
                case '\r' : 
                case '\v' :
                    ++line;
                    if (! l.empty ())
                    {   l_.push_back (colony < ENUM, TYPE > (line, l));
                        l.clear (); }
                    break;
                default :
                    if (ch >= ' ') l += ch;
                    break; }
        if (! l.empty ())
            l_.push_back (colony < ENUM, TYPE > (++line, l));
        valid_ = true;
        for (auto ll : l_)
            if (! ll.valid_)
                valid_ = false; }
    explicit colonic (const ::std::string& content)
    {   parse (content); }
    void merge (nitpick& nits)
    {   for (auto l : l_)
            nits.merge (l.nits_); }
    ::std::string rpt () const
    {   ::std::string res ("robots.txx:\n");
        for (auto l : l_) 
            res += l.rpt () + "\n";
        return res; } };
