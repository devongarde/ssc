/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "microformat/sibling.h"
#include "microformat/connection.h"

typedef connection < e_property, e_property > prop_sibling;
typedef connection < e_property, e_rel > rel_sibling;

prop_sibling standard_prop_siblings [] =
{   { mf1_adr, mf1_country_name },
    { mf1_adr, mf1_extended_address },
    { mf1_adr, mf1_locality },
    { mf1_adr, mf1_postal_code },
    { mf1_adr, mf1_post_office_box },
    { mf1_adr, mf1_region },
    { mf1_adr, mf1_street_address },
    { mf1_adr, mf1_type },
    { mf1_adr, mf1_value },

    { mf1_attendee, mf1_partstat },
    { mf1_attendee, mf1_role },

    { mf1_email, mf1_type },
    { mf1_email, mf1_value },

    { mf1_fn, mf1_additional_name },
    { mf1_fn, mf1_family_name },
    { mf1_fn, mf1_given_name },
    { mf1_fn, mf1_honorific_prefix },
    { mf1_fn, mf1_honorific_suffix },

    { mf1_geo, mf1_latitude },
    { mf1_geo, mf1_longitude },

    { mf1_hentry, mf1_author },
    { mf1_hentry, mf1_entry_content },
    { mf1_hentry, mf1_entry_summary },
    { mf1_hentry, mf1_entry_title },
    { mf1_hentry, mf1_published },
    { mf1_hentry, mf1_updated },

    { mf1_identifier, mf1_type },
    { mf1_identifier, mf1_value },

    { mf1_ingredient, mf1_type },
    { mf1_ingredient, mf1_value },

    { mf1_item, mf1_fn },
    { mf1_item, mf1_url },
    { mf1_item, mf1_photo },
    { mf1_item, mf1_geo },
    { mf1_item, mf1_adr },

    { mf1_nutrition, mf1_type },
    { mf1_nutrition, mf1_value },

    { mf1_org, mf1_organisation_name },
    { mf1_org, mf1_organisation_unit },

    { mf1_price, mf1_amount },
    { mf1_price, mf1_currency },

    { mf1_rating, mf1_average },
    { mf1_rating, mf1_best },
    { mf1_rating, mf1_value },
    { mf1_rating, mf1_worst },

    { mf1_tel, mf1_type },
    { mf1_tel, mf1_value } };

rel_sibling standard_rel_siblings [] =
{   { mf1_hentry, r_bookmark },
    { mf1_hentry, r_entry_category },
    { mf1_hentry, r_tag } };

connections < prop_sibling > brothers;
connections < rel_sibling > cousins;

void sibling_init (nitpick& nits)
{   brothers.init (nits, standard_prop_siblings, sizeof (standard_prop_siblings));
    cousins.init (nits, standard_rel_siblings, sizeof (standard_rel_siblings)); }

bool requires_sibling (const e_property prop)
{   return brothers.is_possible_member (prop); }

bool is_plausible_sibling (const e_property sibling, const e_property p)
{   return brothers.is_plausible_connection (sibling, p); }

bool is_plausible_sibling (const e_property sibling, const e_rel r)
{   return cousins.is_plausible_connection (sibling, r); }
