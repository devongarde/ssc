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

typedef ::std::size_t ns_id, ns_ndx;
typedef ::std::string ns_name;

struct namespace_identifier
{   ns_name         name_;
    ns_id           id_;
    e_namespace     standard_ = ns_default;
    bool            automatic_ = false;
    namespace_identifier (const ns_name& n, const ns_id id, const e_namespace standard, const bool automatic)
        : name_ (n), id_ (id), standard_ (standard), automatic_ (automatic) { } };

typedef ::std::vector < namespace_identifier > vns_t;
typedef ssc_map < ns_name, ns_ndx > midni_t;
typedef ssc_map < e_namespace, ns_ndx > meni_t;
typedef ssc_map < ::std::string, ns_ndx > mxni_t;

struct namespace_stack
{   vns_t   vns_;
    midni_t names_;
    meni_t  ens_;
    mxni_t  xs_;
    namespace_stack () = default;
    namespace_stack (const namespace_stack& ns) = default;
    namespace_stack (namespace_stack&& ns) = default;
    ns_id add (nitpick& nits, const html_version& v, const ::std::string& xmlns, const ::std::string& schema);
    ns_id find (const ::std::string& s) const;
    ns_id find (const e_namespace ns) const;
    ns_name name (const ns_id ns) const;
    e_namespace standard (const ns_id ns) const; };

typedef ::std::shared_ptr < namespace_stack > ns_ptr;
ns_ptr initialise_namespace_stack (const html_version& v, const ns_ptr& orig);
ns_ptr new_namespace_stack (const html_version& v);
ns_ptr copy_namespace_stack (const ns_ptr& orig);
e_namespace examine_namespace (nitpick& nits, const html_version& v, ns_ptr& ns_stack, ::std::string& s, ::std::string& n);
ns_id namespace_declaration (nitpick& nits, const html_version& v, ns_ptr& ns_stack, const ::std::string& name, const ::std::string& schema);
