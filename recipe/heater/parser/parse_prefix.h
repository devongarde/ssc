/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "symbol/nstr.h"
#include "utility/quote.h"

// note: first n values correspond to e_rdfa_context, remainder refer to vpre_t (below)
typedef ::std::size_t prefix_id;

struct prefix_t
{   prefix_id id_;
    ::std::string name_, curie_;
    prefix_t (const prefix_id id, const ::std::string& name, const ::std::string& curie)
        :   id_ (id), name_ (name), curie_ (curie) { }
    ::std::string rpt () const
    {   return ::boost::lexical_cast < ::std::string > (id_) + " (" + name_ + ": " + curie_ + ")"; } };

typedef ::std::vector < prefix_t > vpre_t;

class prefixes
{   typedef ::std::map < ::std::string, prefix_id > mp_t;
    vpre_t vpre_;
    mp_t names_, curies_;
    prefix_id offset_ = 0;
    prefixes* up_ = nullptr;
    bool lower_ = true;
public:
    void up (prefixes* up) // presumes up already set up
    {   PRESUME (vpre_.empty (), __FILE__, __LINE__);
        up_ = up;
        if (up_ != nullptr) offset_ = up_ -> maximum ();
        else offset_ = pre_error; }
    prefixes* up () { return up_; }
    const prefixes* up () const { return up_; }
    prefix_id maximum () const
    {   return vpre_.size () + offset_; }
    prefix_id find_name (const ::std::string& name) const
    {   PRESUME (! name.empty (), __FILE__, __LINE__);
        prefix_id res = prefix_names.find (PREFIX_NAME, name, lower_);
        if (res != pre_error) return res;
        if (up_ != nullptr) return up_ -> find_name (name);
        mp_t::const_iterator i = names_.find (name);
        if (i != names_.cend ()) return i -> second;
        return 0; }
    prefix_id find_curie (const ::std::string& curie) const
    {   PRESUME (! curie.empty (), __FILE__, __LINE__);
        prefix_id res = prefix_names.find (PREFIX_CURIE, curie, lower_);
        if (res != pre_error) return res;
        if (up_ != nullptr) return up_ -> find_curie (curie);
        mp_t::const_iterator i = curies_.find (curie);
        if (i != curies_.cend ()) return i -> second;
        return 0; }
    ::std::string name (const prefix_id id) const
    {   PRESUME (id < offset_ + vpre_.size (), __FILE__, __LINE__);
        PRESUME (id != 0, __FILE__, __LINE__);
        if (id >= offset_) return vpre_.at (id - offset_).name_;
        if (up_ != nullptr) return up_ -> name (id);
        if (id < pre_error) return prefix_names.get (static_cast < e_rdfa_context > (id), PREFIX_NAME);
        return ::std::string (); }
    ::std::string curie (const prefix_id id) const
    {   PRESUME (id < offset_ + vpre_.size (), __FILE__, __LINE__);
        PRESUME (id != 0, __FILE__, __LINE__);
        if (id >= offset_) return vpre_.at (id - offset_).curie_;
        if (up_ != nullptr) return up_ -> curie (id);
        if (id < pre_error) return prefix_names.get (static_cast < e_rdfa_context > (id), PREFIX_CURIE);
        return ::std::string (); }
    prefix_id declare (const ::std::string& name, const ::std::string& curie)
    {   PRESUME (offset_ > 0, __FILE__, __LINE__);
        PRESUME (! name.empty (), __FILE__, __LINE__);
        PRESUME (! curie.empty (), __FILE__, __LINE__);
        prefix_id id = vpre_.size () + offset_;
        try
        {   vpre_.push_back (prefix_t (id, name, curie));
            PRESUME (vpre_.at (vpre_.size () - 1).id_ == id, __FILE__, __LINE__);
            names_.insert (mp_t::value_type (name, id));
            curies_.insert (mp_t::value_type (curie, id)); }
        catch (...)
        {   GRACEFUL_CRASH (__FILE__, __LINE__); }
        return id; }
    prefix_id declare (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& curie)
    {   if (name.empty () || curie.empty ())
            nits.pick (nit_empty, es_error, ec_rdfa, "Neither PREFIX names nor values can be empty");
        else
        {   if (find_name (name) != 0)
                nits.pick (nit_prefix_again, es_error, ec_rdfa, "repeated definition of ", quote (name));
            else
                nits.pick (nit_prefix_unknown, es_info, ec_rdfa, PROG " does not know about ", quote (name), ", so cannot verify its content");
            if (find_curie (curie) != 0)
                nits.pick (nit_prefix_again, es_error, ec_rdfa, "repeated definition of ", quote (curie));
            lower_ = ! v.xhtml ();
            return declare (name, curie); }
        return 0; }
    ::std::string rpt (const int level) const
    {   ::std::string res, indent (::boost::lexical_cast < ::std::string > (level));
        for (auto p : vpre_)
            res += indent + p.rpt () + "\n";
        return res; } };

typedef ::std::shared_ptr < prefixes > pre_ptr;
