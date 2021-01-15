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
#include "utility/quote.h"

#define EXPORT_HREFLANG "hreflang"
#define EXPORT_ITEM  "item"
#define EXPORT_MEDIA "media"
#define EXPORT_RELS "rels"
#define EXPORT_TEXT "text"
#define EXPORT_TITLE "title"
#define EXPORT_TYPE "type"

#define EXPORT_SEP      '"'
#define EXPORT_STRSEP   "\""

struct url_export
{   ::std::string hreflang_, media_, text_, title_, type_;
    vstr_t rels_;
    url_export () = default;
    url_export (const ::std::string& hreflang, const ::std::string& media, const vstr_t& rels, const ::std::string& text, const ::std::string& title, const ::std::string& type)
        : hreflang_ (hreflang), media_ (media), text_ (text), title_ (title), type_ (type), rels_ (rels) {}
    url_export (const ::std::string& str) { reset (str); }
    url_export (const url_export& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
    url_export (url_export&& ) = default;
#endif
    ~url_export () = default;
    url_export& operator = (const url_export& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
    url_export& operator = (url_export&& ) = default;
#endif
    bool operator == (const url_export& u) const { return rels_ == u.rels_; }
    bool operator != (const url_export& u) const { return rels_ != u.rels_; }
    bool operator < (const url_export& u) const { return rels_ < u.rels_; }
    bool operator > (const url_export& u) const { return rels_ > u.rels_; }
    bool operator <= (const url_export& u) const { return rels_ <= u.rels_; }
    bool operator >= (const url_export& u) const { return rels_ >= u.rels_; }
    void swap (url_export& u) NOEXCEPT
    {   hreflang_.swap (u.hreflang_);
        media_.swap (u.media_);
        text_.swap (u.text_);
        title_.swap (u.title_);
        type_.swap (u.type_);
        rels_.swap (u.rels_); }
    ::std::string str () const
    {   ::std::ostringstream ss;
        ss << quote (hreflang_) << quote (media_) << quote (rels_) << quote (text_) << quote (title_) << quote (type_);
        return ss.str (); }
    operator ::std::string () const { return str (); }
    void reset (const ::std::string& str)
    {   vstr_t tmp (unquote (str, 6));
        type_ = tmp.at (5);
        title_ = tmp.at (4);
        text_ = tmp.at (3);
        rels_ = unquote (tmp.at (2));
        media_ = tmp.at (1);
        hreflang_ = tmp.at (0); } };

template < class T > class t_export
// http://microformats.org/wiki/microformats2-json
{   typedef ::std::set < T > us_t;
    typedef ssc_map < ::std::string, us_t > target_t;
    typedef ::std::pair < ::std::string, us_t > pus_t;
    typedef typename target_t::iterator ti_t;
    typedef typename target_t::const_iterator tci_t;
    typedef ::std::pair < ti_t, bool > tins_t;
    target_t target_;
    const char* export_;
    void put_data (::boost::property_tree::ptree& tree, const T& data);
public:
    t_export () = delete;
    explicit t_export (const char* ex) : export_ (ex) { }
    void swap (t_export < T >& e) NOEXCEPT
    {   target_.swap (e.target_);
        ::std::swap (export_, e.export_); }
    void insert (const ::std::string& key, const T& data)
    {   if (target_.find (key) == target_.cend ())
        {   us_t v;
            v.insert (data);
            tins_t tin = target_.insert (pus_t (key, v));
            if (! tin.second)
            {   if (context.tell (e_splurge)) context.err () << "t_export insert 1 failed\n";
                return; } }
        us_t& ss = target_.at (key); // phew, single threaded!
        if (! ss.insert (data).second) if (context.tell (e_splurge)) context.err () << "t_export insert 2 failed\n"; }
    void put (::boost::property_tree::ptree& tree)
    // https://stackoverflow.com/questions/2114466/creating-json-arrays-in-boost-using-property-trees
    {   for (auto i : target_)
        {   ::boost::property_tree::ptree kiddywinks;
            for (auto j : i.second)
                put_data (kiddywinks, j);
            ::std::string wo (export_);
            wo += EXPORT_STRSEP;
            wo += i.first;
            tree.add_child (::boost::property_tree::path (wo, EXPORT_SEP), kiddywinks); } } };

template < class T > inline void t_export < T >::put_data (::boost::property_tree::ptree& tree, const T& data)
{   ::boost::property_tree::ptree kiddywink;
    kiddywink.put ("", data);
    tree.push_back (::std::make_pair ("", kiddywink)); }

template < > inline void t_export < url_export >::put_data (::boost::property_tree::ptree& tree, const url_export& data)
{   ::boost::property_tree::ptree kiddywink;
    if (! data.rels_.empty ())
    {   ::boost::property_tree::ptree twins;
        for (::std::string rel : data.rels_)
        {   ::boost::property_tree::ptree twin;
            twin.put ("", rel);
            twins.push_back (::std::make_pair ("", twin)); }
        kiddywink.add_child (::boost::property_tree::path (EXPORT_RELS, EXPORT_SEP), twins); }
    if (! data.hreflang_.empty ()) kiddywink.put (EXPORT_HREFLANG, data.hreflang_);
    if (! data.media_.empty ()) kiddywink.put (EXPORT_MEDIA, data.media_);
    if (! data.text_.empty ()) kiddywink.put (EXPORT_TEXT, data.text_);
    if (! data.title_.empty ()) kiddywink.put (EXPORT_TITLE, data.title_);
    if (! data.type_.empty ()) kiddywink.put (EXPORT_TYPE, data.type_);
    tree.push_back (::std::make_pair ("", kiddywink)); }
