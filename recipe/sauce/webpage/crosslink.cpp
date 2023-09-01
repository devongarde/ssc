/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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

#include "main/standard.h"
#include "webpage/crosslink.h"
#include "main/context.h"
#include "ontology/ontology_type.h"
#include "utility/quote.h"

struct crosslink_t
{   ::std::string id_;          // id sought on sought page
    ::std::size_t line_ = 0;    // line in seeker where id is sought
    bool hidden_ = false;       // whether seeker element is hidden, etc.
    vit_t type_;                // itemtypes sought, if any
    e_element e_ = elem_undefined; // element that declared id / seeker element
    crosslink_t (const ::std::string& id, const ::std::size_t n, const bool hidden, const vit_t& itemtypes, const e_element e)
        :   id_ (id), line_ (n), hidden_ (hidden), type_ (itemtypes), e_ (e) { } };

typedef ::std::vector < crosslink_t > vcl_t;
typedef ::std::vector < e_sought_category > vsc_t;

struct seeker_t
{   fileindex_t page_;    // seeker page
    vcl_t ids_;           // ids being sought
    vsc_t cats_;          // categories of elements sought
    explicit seeker_t (const fileindex_t n) noexcept : page_ (n) { }
    void emplace_back (const ::std::string& id, const ::std::size_t line, const bool hidden, const vit_t& itemtypes, const e_element e)
    {   ids_.emplace_back (id, line, hidden, itemtypes, e);
        cats_.emplace_back (elem::link_category_sought (e));
        PRESUME (ids_.size () == cats_.size (), __FILE__, __LINE__); } };

typedef ::std::map < fileindex_t, seeker_t > vsk_t;

inline bool operator == (const seeker_t& lhs, const seeker_t& rhs) noexcept { return lhs.page_ == rhs.page_; }
inline bool operator != (const seeker_t& lhs, const seeker_t& rhs) noexcept { return lhs.page_ != rhs.page_; }
inline bool operator < (const seeker_t& lhs, const seeker_t& rhs) noexcept { return lhs.page_ < rhs.page_; }
inline bool operator <= (const seeker_t& lhs, const seeker_t& rhs) noexcept { return lhs.page_ <= rhs.page_; }
inline bool operator > (const seeker_t& lhs, const seeker_t& rhs) noexcept { return lhs.page_ > rhs.page_; }
inline bool operator >= (const seeker_t& lhs, const seeker_t& rhs) noexcept { return lhs.page_ >= rhs.page_; }

struct sought_t
{   fileindex_t page_;    // sought page
    vcl_t declared_;      // ids declared on sought page
    vsk_t seekers_;       // list of seekers searching for ids on this page
    sought_t (const fileindex_t p) : page_ (p) { } };

inline bool operator == (const sought_t& lhs, const sought_t& rhs) noexcept { return lhs.page_ == rhs.page_; }
inline bool operator != (const sought_t& lhs, const sought_t& rhs) noexcept { return lhs.page_ != rhs.page_; }
inline bool operator < (const sought_t& lhs, const sought_t& rhs) noexcept { return lhs.page_ < rhs.page_; }
inline bool operator <= (const sought_t& lhs, const sought_t& rhs) noexcept { return lhs.page_ <= rhs.page_; }
inline bool operator > (const sought_t& lhs, const sought_t& rhs) noexcept { return lhs.page_ > rhs.page_; }
inline bool operator >= (const sought_t& lhs, const sought_t& rhs) noexcept { return lhs.page_ >= rhs.page_; }

typedef ::std::map < fileindex_t, sought_t > vx_t;
typedef ::std::unique_ptr < vx_t > vx_ptr;
vx_ptr xlynx;

void init_crosslinks ()
{   xlynx = vx_ptr (new vx_t); }

void declare_crosslinks (const fileindex_t sought, const ids_t& ids)
{   if (! context.crosslinks ()) return;
    if (ids.empty ()) return;
    lox l (lox_xlynx);
    vcl_t declare;
    vx_t::iterator i = xlynx -> find (sought);
    if (i == xlynx -> cend ())
    {   auto p = xlynx -> emplace (::std::pair < fileindex_t, sought_t > (sought, sought_t (ids.ndx ())));
        PRESUME (p.second, __FILE__, __LINE__);
        i = p.first; }
    for (auto d : ids.mif ())
        declare.emplace_back (d.first, 0, d.second.hidden_, d.second.types_, d.second.elem_);
    i -> second.declared_.swap (declare); }

void declare_crosslinks (const ::boost::filesystem::path& sought, const ids_t& ids)
{   if (context.crosslinks ())
        declare_crosslinks (get_fileindex (sought), ids); }

void add_sought (const fileindex_t seeker, const ::std::size_t line, const fileindex_t sought, const ::std::string& id, const bool hidden, const vit_t& itemtypes, const e_element e)
{   if (! context.crosslinks ()) return;
    if (seeker == sought) return;
    lox l (lox_xlynx);
    vx_t::iterator sought_i = xlynx -> find (sought);
    if (sought_i == xlynx -> cend ())
    {   auto xe = xlynx -> emplace (::std::pair < fileindex_t, sought_t > (sought, sought_t (sought)));
        sought_i = xe.first; }
    vsk_t& seek (sought_i -> second.seekers_);
    vsk_t::iterator seek_i = seek.find (seeker);
    if (seek_i == seek.cend ())
    {   auto se = seek.emplace (seeker, seeker_t (seeker));
        seek_i = se.first; }
    seek_i -> second.emplace_back (id, line, hidden, itemtypes, e); }

void add_sought (   const ::boost::filesystem::path& seeker, const ::std::size_t line, const ::boost::filesystem::path& sought,
                    const ::std::string& id, const bool hidden, const vit_t& itemtypes, const e_element e)
{   if (context.crosslinks ()) add_sought (get_fileindex (seeker), line, get_fileindex (sought), id, hidden, itemtypes, e); }

bool null_intersection (const vit_t& lhs, const vit_t& rhs) noexcept
{   for (auto i : lhs)
        for (auto j : rhs)
            if (i == j) return false;
    return true; };

// i suspect these should be optimised! --- but, to quote C.A.R. Hoare ...

bool has_id (const vcl_t& v, const ::std::string& id)
{   for (auto i : v)
        if (i.id_ == id) return true;
    return false; }

bool has_itemtype (const vcl_t& vc, const vit_t& vi)
{   for (auto i : vc)
        for (auto j : i.type_)
            for (auto k : vi)
                if (j == k) return true;
    return false; }

bool is_hidden (const vcl_t& v, const ::std::string& id)
{   for (auto i : v)
        if (i.id_ == id) return i.hidden_;
    return false; }

e_element get_element (const vcl_t& v, const ::std::string& id)
{   for (auto i : v)
        if (i.id_ == id) return i.e_;
    return false; }

void append_typename (::std::string& res, const itemtype_index it, bool& first)
{   if (! first) res += ", ";
    if (type_category (it) != itemtype_schema)
        res += "other";
    res += quote (sch::name (static_cast < e_ontology_type > (ndx_item (it))));
    first = false; }

::std::string itemtype_string (const vit_t& vi)
{   ::std::string res;
    bool first = true;
    for (auto it : vi)
        append_typename (res, it, first);
    if (res.empty ()) res = "nothing";
    return res; }

::std::string itemtype_string (const vcl_t& c)
{   ::std::string res;
    bool first = true;
    for (auto i : c)
        for (auto it : i.type_)
            append_typename (res, it, first);
    if (res.empty ()) res = "nothing";
    return res; }

void reconcile_crosslinks (nitpick& nits)
{   if (context.crosslinks ())
    {   PRESUME (! fred.activity (), __FILE__, __LINE__);
        for (auto ix : *xlynx)
            for (auto is : ix.second.seekers_)
                if (ix.second.page_ != is.second.page_)
                    for (auto c : is.second.ids_)
					{   if (! has_id (ix.second.declared_, c.id_))
                            if (context.test ()) nits.pick (nit_url_id_unfound, es_error, ec_link, is.second.page_, " ", c.line_, " ", ix.second.page_ , " ", c.id_);
                            else nits.pick (nit_url_id_unfound, es_error, ec_link, get_disk_path (is.second.page_).string (), " ", c.line_, ": ", get_disk_path (ix.second.page_).string (), "#", c.id_, " is undefined");
                        else if (! c.type_.empty ())
                        {   if (! has_itemtype (ix.second.declared_, c.type_))
                                if (context.test ()) nits.pick (nit_incompatible_itemtype, es_error, ec_link, is.second.page_, " ", c.line_, " ", ix.second.page_ , " ", c.id_);
                                else
                                {   ::std::string msg ("the itemprop(s) at " + get_disk_path (is.second.page_).string () + ":" + ::boost::lexical_cast < ::std::string > (c.line_) + " seeks ");
                                    msg += itemtype_string (c.type_);
                                    msg += "; " + get_disk_path (ix.second.page_).string () + "#" + c.id_ + " offers ";
                                    msg += itemtype_string (ix.second.declared_);
                                    nits.pick (nit_incompatible_itemtype, es_error, ec_link, msg); } }
                        else if (! compatible_id_state (c.hidden_, is_hidden (ix.second.declared_, c.id_)))
                            if (context.test ()) nits.pick (nit_id_hidden, es_error, ec_link, is.second.page_, " ", c.line_, " ", ix.second.page_ , " ", c.id_);
                            else nits.pick (nit_id_hidden, es_error, ec_link, get_disk_path (is.second.page_).string (), " ", c.line_, ": ", get_disk_path (ix.second.page_).string (), "#", c.id_, " is hidden");
                        else if (! elem::fits_link_category (context.html_ver (), get_element (ix.second.declared_, c.id_), elem::link_category_sought (c.e_)))
                            if (context.test ()) nits.pick (nit_id_category, es_error, ec_link, is.second.page_, " ", c.line_, " ", ix.second.page_ , " ", c.id_);
                            else nits.pick (nit_id_category, ed_svg_1_1, "17.1.4 Processing of IRI references", es_error, ec_link,
                                get_disk_path (is.second.page_).string (), " ", c.line_, ": ", get_disk_path (ix.second.page_).string (),
                                    "#", c.id_, ": <", elem::name (get_element (ix.second.declared_, c.id_)), "> is an unsuitable target for <", elem::name (c.e_), ">"); } } }
