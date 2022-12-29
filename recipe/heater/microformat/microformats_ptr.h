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

#pragma once
#include "microformat/microformats.h"

typedef ::std::shared_ptr < microformats > microformats_ptr;

template < class VOCAB, class PROPERTY > ::std::string get_microformat_property_value (const microformats_ptr& pmf)
{   ::std::string res;
    if (pmf)
        if (pmf -> has < VOCAB > ())
            {   VOCAB& mirt = pmf -> get < VOCAB > ();
                PROPERTY* pirt = nullptr;
                mirt. template get < PROPERTY > (&pirt);
                if (pirt != nullptr) res = pirt -> get_string (); }
    return res; }

template < class VOCAB, class PROPERTY > bool is_microformat_property_empty (const microformats_ptr& pmf)
{   if (! pmf) return true;
    if (! pmf -> has < VOCAB > ()) return true;
    VOCAB& mirt = pmf -> get < VOCAB > ();
    PROPERTY* pirt = nullptr;
    mirt. template get < PROPERTY > (&pirt);
    if (pirt == nullptr) return true;
    return pirt -> empty (); }

template < class VOCAB, class PROPERTY > bool is_microformat_relation_illegal (const microformats_ptr& pmf)
{   if (! pmf) return false;
    if (! pmf -> has < VOCAB > ()) return false;
    VOCAB& mirt = pmf -> get < VOCAB > ();
    PROPERTY* pirt = nullptr;
    mirt. template get < PROPERTY > (&pirt);
    if (pirt == nullptr) return false;
    return pirt -> is_illegal (); }

template < class VOCAB, class PROPERTY > bool is_microformat_relation_obsolete (const microformats_ptr& pmf)
{   if (! pmf) return false;
    if (! pmf -> has < VOCAB > ()) return false;
    VOCAB& mirt = pmf -> get < VOCAB > ();
    PROPERTY* pirt = nullptr;
    mirt. template get < PROPERTY > (&pirt);
    if (pirt == nullptr) return false;
    return pirt -> is_obsolete (); }
