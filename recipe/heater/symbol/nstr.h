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
#include "type/enum.h"
#include "feedback/nitpick.h"
#include "parser/html_version.h"

// ensure last entry id_ == ERR
template < typename ENUM, ::std::size_t N > struct n_string_entry
{   html_version from_, to_;
    ENUM id_;
    flags_t flags_;
    const char* sz_ [N];
#ifdef REQUIRE_CONSTRUCTOR
    n_string_entry (const html_version& from, const html_version& to, const ENUM id, const flags_t f, const char* const sz [])
        : from_ (from), to_ (to), id_ (id), flags_ (f), sz_ (sz) { }
#endif //  REQUIRE_CONSTRUCTOR
};

template < typename ENUM, ENUM ERROR_VALUE, ::std::size_t N, ::std::size_t INDICES > class n_string_table
{   BOOST_STATIC_ASSERT (INDICES <= N);
    typedef ssc_mm < ::std::string, ENUM > mnse_t;
    typedef ssc_map < ENUM, ::std::size_t > meid_t;
    typedef n_string_entry < ENUM, N > data_t;
    const data_t* data_ = nullptr;
    mnse_t mixed_ [INDICES], lower_ [INDICES];
    meid_t ids_;
    ::std::size_t max_ = 0;
    const data_t* datum (const ENUM id) const  // with apologies to English language purists
    {   PRESUME (id < ERROR_VALUE, __FILE__, __LINE__);
        PRESUME (id != 0, __FILE__, __LINE__);
        typename meid_t::const_iterator i = ids_.find (id);
        PRESUME (i != ids_.cend (), __FILE__, __LINE__);
        PRESUME (i -> second <= max_, __FILE__, __LINE__);
        return &data_ [i -> second]; }
public:
    void init (nitpick& nits, const n_string_entry < ENUM, N >* data)
    {   VERIFY_NOT_NULL (data, __FILE__, __LINE__);
        data_ = data;
        for (max_ = 0; data_ [max_].id_ != ERROR_VALUE; ++max_)
        {   ids_.insert (typename meid_t::value_type (data_ [max_].id_, max_));
            for (::std::size_t n = 0; n < INDICES; ++n)
                if (data_ [max_].sz_ [n] != nullptr)
                {   //  ::std::string rpt (data_ [max_].sz_ [n]); // thanx, vc++ debugger, for refusing to report anything but data_ [1].
                    mixed_ [n].insert (typename mnse_t::value_type (::std::string (data_ [max_].sz_ [n]), static_cast < ENUM > (max_)));
                    lower_ [n].insert (typename mnse_t::value_type (::boost::to_lower_copy (::std::string (data_ [max_].sz_ [n])), static_cast < ENUM > (max_))); } }
        for (::std::size_t n = 1; n < ERROR_VALUE; ++n)
        {   typename meid_t::const_iterator i = ids_.find (static_cast < ENUM > (n));
            if (i == ids_.cend ()) nits.pick (nit_missing_id, es_catastrophic, ec_init, "NSTR initialisation ", n, " missing"); } }
    ENUM err () const { return ERROR_VALUE; }
    const char* get (const ENUM id, const ::std::size_t n) const
    {   PRESUME (n < N, __FILE__, __LINE__);
        const data_t *pd = datum (id);
        return pd -> sz_ [n]; }
    html_version from (const ENUM id) const
    {   const data_t *pd = datum (id);
        return pd -> from_; }
    html_version to (const ENUM id) const
    {   const data_t *pd = datum (id);
        return pd -> to_; }
    flags_t flags (const ENUM id) const
    {   const data_t *pd = datum (id);
        return pd -> flags_; }
    ENUM find_mixed (const html_version& v, const ::std::size_t n, const ::std::string& s) const
    {   PRESUME (n < INDICES, __FILE__, __LINE__);
        for (typename mnse_t::const_iterator pos = mixed_ [n].find (s.c_str ()); pos != mixed_ [n].cend (); ++pos)
        {   const data_t& pd = data_ [pos -> second];
            if (may_apply (v, pd.from_, pd.to_)) return pd.id_; }
        return ERROR_VALUE; }
    ENUM find_lower (const html_version& v, const ::std::size_t n, const ::std::string& s) const
    {   PRESUME (n < INDICES, __FILE__, __LINE__);
        for (typename mnse_t::const_iterator pos = lower_ [n].find (s.c_str ()); pos != lower_ [n].cend (); ++pos)
        {   const data_t& pd = data_ [pos -> second];
            if (may_apply (v, pd.from_, pd.to_)) return pd.id_; }
        return ERROR_VALUE; }
    ENUM find (const html_version& v, const ::std::size_t n, const ::std::string& s, const bool lower) const
    {   if (lower) return find_lower (v, n, s);
        return find_mixed (v, n, s); } };

#define ABB_SHORTFORM 0
#define ABB_LONGFORM 1

#define PROTOCOL_NAME ABB_SHORTFORM
#define PROTOCOL_DESCRIPTION 1

#define PREFIX_NAME ABB_SHORTFORM
#define PREFIX_CURIE ABB_LONGFORM
#define PREFIX_DESCRIPTION 2

#define NAMESPACE_NAME ABB_SHORTFORM
#define NAMESPACE_SCHEMA ABB_LONGFORM
#define NAMESPACE_DESCRIPTION 2

#define NS_DEFAULT          0x0000000000000001
#define NS_DEPRECATED       0x0000000000000002
#define NS_UNDECLARABLE     0x0000000000000004
#define NS_PREDECLARED      0x0000000000000008

typedef n_string_table < e_namespace, ns_error, 3, 2 > namespace_names_t;
typedef n_string_table < e_protocol, pr_error, 2, 1 > protocol_names_t;
typedef n_string_table < e_rdfa_context, pre_error, 3, 2 > prefix_names_t;
extern namespace_names_t namespace_names;
extern protocol_names_t protocol_names;
extern prefix_names_t prefix_names;

void init_nstrs (nitpick& nits);
