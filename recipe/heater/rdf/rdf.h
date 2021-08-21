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
#include "utility/common.h"
#include "type/enum.h"
#include "parser/parse_abb.h"
#include "rdf/rdfa_type.h"
#include "rdf/rdfa_prop.h"

class rdf_t;
class page;

typedef ssc_variant < rdf_t*, ::std::string > prop_value;
typedef ssc_mm < prop_index, prop_value > mrv_t;
typedef ::std::set < e_schema > vsh_t;

class rdf_t
{   mrv_t prop_;
    vty_t type_;
    rdf_t* up_ = nullptr;
    prefixes_t* prefixes_ = nullptr;
    vsh_t vocab_;
    prop_indices prepare_prop_indices (nitpick& nits, const html_version& v, const ::std::string& name);
    bool use_parent () const { return (up_ != nullptr); }
    template < typename ENUM > ENUM fit_vocab (const html_version& v, const ::std::string& name) const;
    bool is_vocab_defined (const e_schema s)
    {   if (vocab_.find (s) != vocab_.cend ()) return true;
        if (up_ != nullptr) return up_ -> is_vocab_defined (s);
        return false; }
public:
    rdf_t () = default;
    rdf_t (const rdf_t& r) = default;
    rdf_t (rdf_t&& r) = default;
    rdf_t& operator = (const rdf_t& r) = default;
    rdf_t& operator = (rdf_t&& r) = default;
    ~rdf_t () = default;

    void prefixes (prefixes_t* ptr)
    {   PRESUME (type_.empty (), __FILE__, __LINE__);
        PRESUME (prop_.empty (), __FILE__, __LINE__);
        prefixes_ = ptr; }
    void up (rdf_t* u) // presumes *u already set up
    {   PRESUME (type_.empty (), __FILE__, __LINE__);
        PRESUME (prop_.empty (), __FILE__, __LINE__);
        up_ = u; }
    rdf_t* up () { return up_; }
    const rdf_t* up () const { return up_; }

    vty_t type () const
    {   if (use_parent ())
        {   VERIFY_NOT_NULL (up_, __FILE__, __LINE__);
            return up_ -> type (); }
        return type_; }

    bool note_prop (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value, const bool is_link, page& p);
    bool note_prop (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& value, rdf_t* scope, page& p);
    e_schema_type note_type (nitpick& nits, const html_version& v, const ::std::string& name, page& p);
    bool verify_value (nitpick& nits, const html_version& v, const e_schema_type t, const ::std::string& value);
    e_schema note_vocab (nitpick& nits, const html_version& v, const ::std::string& name, page& p);
    vty_t sought_types (const html_version& v, const ::std::string& name) const;
    ::std::string expand_prefix (const html_version& v, const ::std::string& s) const;
    ::std::string report (const ::std::size_t offset = 0) const; };

typedef ::std::shared_ptr < rdf_t > rdf_ptr;
