/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "microformat/family.h"

struct family
{   e_class self_;
    e_class parent_;
    e_property prop_;
    family (const e_class self, const e_class parent, const e_property prop)
        : self_ (self), parent_ (parent), prop_ (prop) { } };

inline bool operator == (const family& lhs, const family& rhs)
{   return  (lhs.self_ == rhs.self_) &&
            (lhs.parent_ == rhs.parent_) &&
            (lhs.prop_ == rhs.prop_); };

inline bool operator != (const family& lhs, const family& rhs)
{   return ! (lhs == rhs); }

inline bool operator < (const family& lhs, const family& rhs)
{   if (lhs.self_ < rhs.self_) return true;
    if (lhs.self_ > rhs.self_) return false;
    if (lhs.parent_ < rhs.parent_) return true;
    if (lhs.parent_ > rhs.parent_) return false;
    return lhs.prop_ < rhs.prop_; }

inline bool operator <= (const family& lhs, const family& rhs)
{   if (lhs < rhs) return true;
    return (lhs == rhs); }

inline bool operator > (const family& lhs, const family& rhs)
{   return ! (lhs <= rhs); }

inline bool operator >= (const family& lhs, const family& rhs)
{   return ! (lhs < rhs); }

template <> struct std::hash <family>
{   ::std::size_t operator() (const family& f) const
    {   return ::std::hash <int> () (
                (static_cast <int> (f.prop_) << 16) +
                (static_cast <int> (f.parent_) << 8) +
                static_cast <int> (f.self_)); } };

family families [] =
{   { h1_adr, h1_card, c_context },

    { h1_aggregate, h1_product, mf1_review },

    { h1_calendar, h1_aggregate, mf1_item },
    { h1_calendar, h1_resume, mf1_education },
    { h1_calendar, h1_resume, mf1_experience },
    { h1_calendar, h1_review, mf1_item },

    { h1_card, h1_aggregate, mf1_item },
    { h1_card, h1_atom, mf1_author },
    { h1_card, h1_audio, mf1_contributor },
    { h1_card, h1_listing, mf1_lister },
    { h1_card, h1_listing, mf1_item },
    { h1_card, h1_media, mf1_contributor },
    { h1_card, h1_news, mf1_dateline },
    { h1_card, h1_news, mf1_source_org },
    { h1_card, h1_product, mf1_brand },
    { h1_card, h1_recipe, mf1_author },
    { h1_card, h1_resume, mf1_affliation },
    { h1_card, h1_resume, mf1_contact },
    { h1_card, h1_review, mf1_item },
    { h1_card, h1_review, mf1_reviewer },

    { h1_listing, h1_product, mf1_listing },

    { h1_product, h1_aggregate, mf1_item },

    { h1_review, h1_product, mf1_review },

    { h_adr, h_card, p_adr },
    { h_adr, h_entry, p_author },
    { h_adr, h_event, p_location },
    { h_adr, h_review, p_item },
    { h_adr, h_aggregate, p_item },
    { h_adr, h_review, p_location },
    { h_card, h_entry, p_location },
    { h_card, h_event, p_location },
    { h_card, h_event, p_attendee },
    { h_card, h_feed, p_author },
    { h_card, h_listing, p_lister },
    { h_card, h_product, p_brand },
    { h_card, h_recipe, p_author },
    { h_card, h_resume, p_contact },
    { h_card, h_resume, p_education },
    { h_card, h_resume, p_experience },
    { h_card, h_review, p_author },
    { h_card, h_review, p_item },
    { h_card, h_review, p_location },
    { h_card, h_aggregate, p_item },
    { h_cite, h_entry, u_in_reply_to },
    { h_cite, h_entry, u_like_of },
    { h_cite, h_entry, u_repost_of },
    { h_cite, h_entry, u_bookmark_of },
    { h_cite, h_entry, p_comment },
    { h_entry, h_feed, c_context },
    { h_event, h_resume, p_education },
    { h_event, h_resume, p_experience },
    { h_event, h_review, p_item },
    { h_event, h_aggregate, p_item },
    { h_geo, h_adr, p_geo },
    { h_geo, h_card, p_geo },
    { h_geo, h_entry, p_location },
    { h_geo, h_event, p_location },
    { h_geo, h_review, p_item },
    { h_geo, h_review, p_location },
    { h_geo, h_aggregate, p_item },
    { h_item, h_review, p_item },
    { h_item, h_aggregate, p_item },
    { h_product, h_review, p_item },
    { h_product, h_aggregate, p_item },
    { h_review, h_product, p_review } };

typedef ssc_set < family > family_t;
family_t tree;

void family_init (nitpick& )
{   for (::std::size_t i = 0; i < sizeof (families) / sizeof (family); ++i)
        tree.insert (families [i]); }

bool is_plausible_parent (const family& f)
{   return tree.find (f) != tree.end (); }

bool is_plausible_parent (nitpick& nits, const e_class self, const e_class parent, const e_property p)
{   if (context.tell (e_detail))
        nits.pick (nit_detail, es_detail, ec_element, "is_plausible_parent", symbol < html_version, e_class > :: name (self), ", ", symbol < html_version, e_class > :: name (parent), ", ", prop :: name (p));
    if (is_plausible_parent (family (self, parent, p))) return true;
    return (parent == h1_card) && (self == h1_adr); }  // special case
