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
#include "utility/common.h"
#include "type/enum.h"
#include "parser/html_version.h"
#include "feedback/nitpick.h"

// ensure last entry id_ == ERR
template < typename ENUM, ::std::size_t N > struct n_string_entry
{   html_version from_, to_;
    ENUM id_;
    flags_t flags_;
    const char* sz_ [N]; };

template < typename ENUM, ENUM ERROR_VALUE, ::std::size_t N, ::std::size_t INDICES > class n_string_table
{   BOOST_STATIC_ASSERT (INDICES <= N);
    typedef ssc_mm < ::std::string, ::std::size_t > mnse_t;
    typedef ssc_map < ENUM, ::std::size_t > meid_t;
    typedef n_string_entry < ENUM, N > data_t;
    typedef ::std::array < mnse_t, INDICES > amnse_t;
    const data_t* data_ = nullptr;
    amnse_t mixed_, lower_;
    meid_t ids_;
    ::std::size_t max_ = 0;
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26446 26481 26482) // Suggested solution breaks the compilation, plus ::std::array can't be length initialised by the initiliser
#endif // _MSC_VER
    const data_t* piece (const ENUM id) const
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
            if (ids_.find (data_ [max_].id_) == ids_.cend ())
                ids_.insert (typename meid_t::value_type (data_ [max_].id_, max_));
        for (::std::size_t n = 1; n < ERROR_VALUE; ++n)
        {   typename meid_t::const_iterator i = ids_.find (static_cast < ENUM > (n));
            if (i == ids_.cend ()) nits.pick (nit_missing_id, es_catastrophic, ec_init, "NSTR initialisation ", n, " missing"); }
        for (max_ = 0; data_ [max_].id_ != ERROR_VALUE; ++max_)
            for (::std::size_t n = 0; n < INDICES; ++n)
                if (data_ [max_].sz_ [n] != nullptr)
                {   ::std::string rpt (data_ [max_].sz_ [n]);
                    typename meid_t::const_iterator i = ids_.find (data_ [max_].id_);
                    if (i != ids_.cend ())
                    {   ::std::string mix (data_ [max_].sz_ [n]);
                        ::std::string low (::boost::to_lower_copy(::std::string (data_ [max_].sz_ [n])));
                        mixed_.at (n).insert (typename mnse_t::value_type (mix, i -> second));
                        lower_ .at (n).insert (typename mnse_t::value_type (low, i -> second)); } } }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
    ENUM err () const { return ERROR_VALUE; }
    const char* get (const ENUM id, const ::std::size_t n) const
    {   PRESUME (n < N, __FILE__, __LINE__);
        const data_t *pd = piece (id);
        VERIFY_NOT_NULL (pd, __FILE__, __LINE__);
        return ::gsl::at (pd -> sz_, n); }
    html_version from (const ENUM id) const
    {   const data_t *pd = piece (id);
        VERIFY_NOT_NULL (pd, __FILE__, __LINE__);
        return pd -> from_; }
    html_version to (const ENUM id) const
    {   const data_t *pd = piece (id);
        VERIFY_NOT_NULL (pd, __FILE__, __LINE__);
        return pd -> to_; }
    flags_t flags (const ENUM id) const
    {   const data_t *pd = piece (id);
        VERIFY_NOT_NULL (pd, __FILE__, __LINE__);
        return pd -> flags_; }
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26481) // ::std::array can't be length initialised by the initiliser
#endif // _MSC_VER
    ENUM find_mixed (const html_version& v, const ::std::size_t n, const ::std::string& s) const
    {   PRESUME (n < INDICES, __FILE__, __LINE__);
        ENUM id = ERROR_VALUE;
        for (typename mnse_t::const_iterator pos = ::gsl::at (mixed_, n).find (s.c_str ()); pos != ::gsl::at (mixed_, n).cend (); ++pos)
        {   PRESUME (pos -> second < max_, __FILE__, __LINE__);
            const data_t& d = data_ [pos -> second];
            if (id == ERROR_VALUE) id = d.id_;
            else if (id != d.id_) break;
            if (may_apply (v, d.from_, d.to_)) return d.id_; }
        return ERROR_VALUE; }
    ENUM find_lower (const html_version& v, const ::std::size_t n, const ::std::string& s) const
    {   PRESUME (n < INDICES, __FILE__, __LINE__);
        ::std::string ss (::boost::to_lower_copy (s));
        ENUM id = ERROR_VALUE;
        for (typename mnse_t::const_iterator pos = ::gsl::at (lower_, n).find (ss.c_str ()); pos != ::gsl::at (lower_, n).cend (); ++pos)
        {   PRESUME (pos -> second < max_, __FILE__, __LINE__);
            const data_t& d = data_ [pos -> second];
            if (id == ERROR_VALUE) id = d.id_;
            else if (id != d.id_) break;
            if (may_apply (v, d.from_, d.to_)) return d.id_; }
        return ERROR_VALUE; }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
    ENUM find (const html_version& v, const ::std::size_t n, const ::std::string& s, const bool lower) const
    {   if (lower) return find_lower (v, n, s);
        return find_mixed (v, n, s); }
    ENUM starts_with_lower (const ::std::size_t n, const ::std::string& s, ::std::string::size_type* ends_at = nullptr) const
    {   ::std::string ss (::boost::to_lower_copy (s));
        const ::std::size_t len = ss.length ();
        if (len > 0)
            for (typename mnse_t::const_iterator i = ::gsl::at (lower_, n).cbegin (); i != ::gsl::at (lower_, n).cend (); ++i)
            {   ::std::string::size_type max = i -> first.length ();
                if ((max > 0) && (max <= len))
                    if (ss.substr (0, max) == i -> first)
                    {   PRESUME (i -> second < max_, __FILE__, __LINE__);
                        if (ends_at != nullptr) *ends_at = max;
 #ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26481) // proposed solution doesn't compile
#endif //  _MSC_VER
                       return data_ [i -> second].id_; } }
#ifdef _MSC_VER
#pragma warning (pop)
#endif //  _MSC_VER
        return ERROR_VALUE; }
    ENUM starts_with_mixed (const ::std::size_t n, const ::std::string& s, ::std::string::size_type* ends_at = nullptr) const
    {   const ::std::size_t len = s.length ();
        if (len > 0)
            for (typename mnse_t::const_iterator i = ::gsl::at (mixed_, n).cbegin (); i != ::gsl::at (mixed_, n).cend (); ++i)
            {   ::std::string::size_type max = i -> first.length ();
                if ((max > 0) && (max <= len))
                    if (s.substr (0, max) == i -> first)
                    {   PRESUME (i -> second < max_, __FILE__, __LINE__);
                        if (ends_at != nullptr) *ends_at = max;
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26481) // proposed solution doesn't compile
#endif //  _MSC_VER
                        return data_ [i -> second].id_; } }
#ifdef _MSC_VER
#pragma warning (pop)
#endif //  _MSC_VER
        return ERROR_VALUE; }
    ENUM starts_with (const ::std::size_t n, const bool lower, const ::std::string& s, ::std::string::size_type* ends_at = nullptr) const
    {   if (lower) return starts_with_lower (n, s, ends_at);
        else return starts_with_mixed (n, s, ends_at); }
    ::std::string after_start_lower (const ::std::size_t n, const ::std::string& s) const
    {   const ::std::size_t len = s.length ();
        if (len > 0)
            for (typename mnse_t::const_iterator i = lower_.at (n).cbegin (); i != lower_.at (n).cend (); ++i)
            {   const ::std::string::size_type max = i -> first.length ();
                if ((max > 0) && (max <= len))
                    if (s.substr (0, max) == i -> first)
                        return s.substr (max); }
        return s; }
    ::std::string after_start_mixed (const ::std::size_t n, const ::std::string& s) const
    {   const ::std::size_t len = s.length ();
        if (len > 0)
            for (typename mnse_t::const_iterator i = mixed_.at (n).cbegin (); i != mixed_.at (n).cend (); ++i)
            {   const ::std::string::size_type max = i -> first.length ();
                if ((max > 0) && (max <= len))
                    if (s.substr (0, max) == i -> first)
                        return s.substr (max); }
        return s; }
    ::std::string after_start (const ::std::size_t n, const ::std::string& s, const bool lower) const
    {   if (lower) return after_start_lower (n, s);
        else return after_start_mixed (n, s); } };

#define ABB_SHORTFORM 0
#define ABB_LONGFORM ( ABB_SHORTFORM + 1 )

#define NAMESPACE_NAME ABB_SHORTFORM
#define NAMESPACE_SCHEMA ABB_LONGFORM
#define NAMESPACE_DESCRIPTION ( NAMESPACE_SCHEMA + 1 )
#define NAMESPACE_COUNT ( NAMESPACE_DESCRIPTION + 1 )

#define NS_DEFAULT          0x0000000000000001
#define NS_DEPRECATED       0x0000000000000002
#define NS_UNDECLARABLE     0x0000000000000004
#define NS_PREDECLARED      0x0000000000000008

#define PROTOCOL_NAME ABB_SHORTFORM
#define PROTOCOL_DESCRIPTION ( PROTOCOL_NAME + 1 )
#define PROTOCOL_COUNT ( PROTOCOL_DESCRIPTION + 1 )

#define SCHEMA_NAME ABB_SHORTFORM
#define SCHEMA_CURIE ABB_LONGFORM
#define SCHEMA_DESCRIPTION ( SCHEMA_CURIE + 1 )
#define SCHEMA_COUNT ( SCHEMA_DESCRIPTION + 1 )

#define SCHEMA_PREFIX_CONTEXT   0x0000000000000001
#define SCHEMA_BESPOKE          0x0000000000000002
#define SCHEMA_CRAPSPEC         0x0000000000000004

typedef n_string_table < e_namespace, ns_error, NAMESPACE_COUNT, 2 > namespace_names_t;
typedef n_string_table < e_protocol, pr_error, PROTOCOL_COUNT, 1 > protocol_names_t;
typedef n_string_table < e_schema, s_error, SCHEMA_COUNT, 2 > schema_names_t;
extern namespace_names_t namespace_names;
extern protocol_names_t protocol_names;
extern schema_names_t schema_names;

vsh_t rdfa_schema_context ();
void init_nstrs (nitpick& nits);
