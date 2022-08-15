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
#include "symbol/nstr.h"
#include "utility/quote.h"

struct abb_t
{   ident_t id_;
    ::std::string short_, long_;
    abb_t (const ident_t id, const ::std::string& shortform, const ::std::string& longform)
        :   id_ (id), short_ (shortform), long_ (longform) { }
    void swap (abb_t& a)
    {   ::std::swap (id_, a.id_);
        short_.swap (a.short_);
        long_.swap (a.long_); }
    ::std::string rpt () const
    {   return ::boost::lexical_cast < ::std::string > (id_) + " (" + short_ + ": " + long_ + ")"; } };

typedef ::std::vector < abb_t > vabb_t;

template < typename ENUM, class STANDARD, ENUM DEFAULT, ENUM ERR > class abbs_t
{   typedef ::std::map < ::std::string, ident_t > msab_t;
    vabb_t vabb_;
    msab_t shorts_, longs_;
    ident_t offset_ = 0;
    abbs_t* up_ = nullptr;
    bool lower_ = true;
public:
    void up (abbs_t* up) // presumes up already set up
    {   PRESUME (vabb_.empty (), __FILE__, __LINE__);
        up_ = up;
        if (up_ != nullptr) offset_ = up_ -> maximum ();
        else offset_ = ERR + 1; }
    abbs_t* up () noexcept { return up_; }
    const abbs_t* up () const noexcept { return up_; }
    ident_t maximum () const noexcept
    {   return vabb_.size () + offset_; }
    ident_t find_shortform (const html_version& v, const STANDARD& predefined, const ::std::string& shortform, const bool standard = true) const
    {   PRESUME (! shortform.empty (), __FILE__, __LINE__);
        msab_t::const_iterator i = shorts_.find (shortform);
        if (i != shorts_.cend ()) return i -> second;
        if (up_ != nullptr) return up_ -> find_shortform (v, predefined, shortform, standard);
        if (standard)
        {   const ident_t res = predefined.find (v, ABB_SHORTFORM, shortform, lower_);
            if (res != ERR) return res; }
        return DEFAULT; }
    ident_t find_longform (const html_version& v, const STANDARD& predefined, const ::std::string& longform, const bool standard = true) const
    {   PRESUME (! longform.empty (), __FILE__, __LINE__);
        msab_t::const_iterator i = longs_.find (longform);
        if (i != longs_.cend ()) return i -> second;
        if (up_ != nullptr) return up_ -> find_longform (v, predefined, longform, standard);
        if (standard)
        {   const ident_t res = predefined.find (v, ABB_LONGFORM, longform, lower_);
            if (res != ERR) return res; }
        return DEFAULT; }
    ::std::string shortform (const STANDARD& predefined, const ident_t id) const
    {   PRESUME (id < offset_ + vabb_.size (), __FILE__, __LINE__);
        PRESUME (id != DEFAULT, __FILE__, __LINE__);
        if (id >= offset_) return vabb_.at (::gsl::narrow_cast < unsigned int > (id - offset_)).short_;
        if (up_ != nullptr) return up_ -> shortform (predefined, id);
        if (id < s_error) return predefined.get (static_cast < ENUM > (id), ABB_SHORTFORM);
        return ::std::string (); }
    ::std::string longform (const STANDARD& predefined, const ident_t id) const
    {   PRESUME (id < offset_ + vabb_.size (), __FILE__, __LINE__);
        PRESUME (id != DEFAULT, __FILE__, __LINE__);
        if (id >= offset_) return vabb_.at (::gsl::narrow_cast < unsigned int > (id - offset_)).long_;
        if (up_ != nullptr) return up_ -> longform (predefined, id);
        if (id < s_error) return predefined.get (::gsl::narrow_cast < ENUM > (id), ABB_LONGFORM);
        return ::std::string (); }
    ident_t declare (const html_version& v, const STANDARD& predefined, const ::std::string& shortform, const ::std::string& longform)
    {   PRESUME (offset_ > 0, __FILE__, __LINE__);
        PRESUME (! longform.empty (), __FILE__, __LINE__);
        ident_t id = predefined.find (v, ABB_LONGFORM, longform, lower_);
        if (id == ERR) id = vabb_.size () + offset_;
        try
        {   vabb_.push_back (abb_t (id, shortform, longform));
            PRESUME (vabb_.at (vabb_.size () - 1).id_ == id, __FILE__, __LINE__);
            if (! shortform.empty ()) shorts_.insert (msab_t::value_type (shortform, id));
            if (! longform.empty ()) longs_.insert (msab_t::value_type (longform, id)); }
        catch (...)
        {   GRACEFUL_CRASH (__FILE__, __LINE__); }
        return id; }
    ident_t declare (nitpick& nits, const html_version& v, const STANDARD& predefined, const ::std::string& shortform, const ::std::string& longform, const bool standard = true)
    {   if (shortform.empty () && longform.empty ())
            nits.pick (nit_empty, es_error, ec_rdfa, "At least one of the short or long form must have content");
        else
        {   if (! shortform.empty ())
                if (find_shortform (v, predefined, shortform, standard) != DEFAULT)
                    nits.pick (nit_prefix_again, es_error, ec_rdfa, "repeated definition of ", quote (shortform));
                else
                    nits.pick (nit_prefix_unknown, es_info, ec_rdfa, PROG " does not know about ", quote (shortform), ", so cannot verify its content");
            if (! longform.empty ())
                if (find_longform (v, predefined, longform, standard) != DEFAULT)
                    nits.pick (nit_prefix_again, es_error, ec_rdfa, "repeated definition of ", quote (longform));
            lower_ = ! v.xhtml ();
            return declare (v, predefined, shortform, longform); }
        return 0; }
    ::std::string rpt (const int level) const
    {   ::std::string res, indent (::boost::lexical_cast < ::std::string > (level));
        for (auto p : vabb_)
            res += indent + p.rpt () + "\n";
        return res; } };

typedef abbs_t < e_namespace, namespace_names_t, ns_default, ns_error > namespaces_t;
typedef abbs_t < e_schema, schema_names_t, s_none, s_error > prefixes_t;
typedef ::std::shared_ptr < namespaces_t > namespaces_ptr;
typedef ::std::shared_ptr < prefixes_t > prefixes_ptr;
