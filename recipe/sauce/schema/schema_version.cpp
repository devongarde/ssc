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
#include "main/context.h"
#include "schema/schema_version.h"
#include "parser/html_version.h"
#include "symbol/nstr.h"

vsv_t vsv;

schema_version::schema_version (const html_version& v)
{   schema_version sv;
    set_mjr (v.mjr (), v.mnr ());
    if (! sv.invalid ()) swap (sv); }

void schema_version::init () // call after context construction
{   vsv.resize (schema_size);
    vsv [s_article] = article_schema;
    vsv [s_book] = book_schema;
    vsv [s_cc] = creative_commons;
    vsv [s_ctag] = common_tag;
    vsv [s_dc] = dc_1_1;
    vsv [s_dcam] = dcam;
    vsv [s_dcmi] = dcmi;
    vsv [s_dct] = dublin_core_terms;
    vsv [s_foaf] = foaf_schema;
    vsv [s_ical] = ical_schema;
    vsv [s_icaltzd] = icaltzd_schema;
    vsv [s_microformats] = context.mf_ver ();
    vsv [s_music] = music_schema;
    vsv [s_og] = open_graph;
    vsv [s_poetry] = poetry_schema;
    vsv [s_profile] = profile_schema;
    vsv [s_rdf] = rdf_schema;
    vsv [s_rdfa] = rdfa_1_1_3;
    vsv [s_rdfs] = rdfs_schema;
    vsv [s_schema] = context.schema_ver ();
    vsv [s_video] = video_schema;
    vsv [s_wdrs] = wdrs_schema;
    vsv [s_website] = website_schema;
    vsv [s_whatwg] = whatwg_schema;
    vsv [s_xsd] = xsd_1_1; }

::std::string schema_version::report () const
{   ::std::ostringstream res;
    if (known ())
    {   e_schema r = root ();
        PRESUME (r < s_error, __FILE__, __LINE__);
        switch (r)
        {   case s_article :
                res << "open graph article";
                break;
            case s_book :
                res << "open graph book";
                break;
            case s_cc :
                res << "creative commons";
                break;
            case s_ctag :
                res << "common tag";
                break;
            case s_dc :
                res << "dublin core";
                break;
            case s_dcam :
                res << "DCAM";
                break;
            case s_dcmi :
                res << "DCMI";
                break;
            case s_dct :
                res << "dublin core terms";
                break;
            case s_foaf :
                res << "foaf v" << static_cast < int > (mjr ()) << "." << static_cast < int > (mnr ());
                break;
            case s_gr:
                res << "good relations";
                break;
            case s_ical:
                res << "ical";
                break;
            case s_icaltzd:
                res << "icaltzd";
                break;
            case s_microformats :
                res << "microformats.org";
                if (! any_flags (SV_WILDCARD))
                    res << " v" << static_cast < int > (mjr ());
                break;
            case s_none :
                break;
            case s_og :
                res << "open graph";
                break;
            case s_poetry :
                res << "poetry";
                break;
            case s_profile :
                res << "open graph profile";
                break;
            case s_rdf :
                res << "RDF";
                break;
            case s_rdfa :
                res << "RDFa v1.";
                if (mnr () == 0) res << "0";
                else res << "1." << static_cast < int > (mnr ());
                break;
            case s_rdfs :
                res << "RDFs";
                break;
            case s_schema :
                res << "schema.org v";
                if (mjr () == 7)
                    res << static_cast < int > (mjr ()) << ".0" << static_cast < int > (mnr ());
                else res << static_cast < int > (mjr ()) << "." << static_cast < int > (mnr ());
                break;
            case s_video :
                res << "open graph video";
                break;
             case s_wdrs :
                res << "WDRS";
                break;
            case s_website :
                res << "open graph website";
                break;
            case s_whatwg :
                res << "WhatWG";
                break;
            case s_xsd :
                res << "XML Schema Type";
                break;
            default :
                res << schema_names.get (r, SCHEMA_NAME);
                break; } }
    return res.str (); }

bool overlap (const schema_version& lhs_from, const schema_version& lhs_to, const schema_version& rhs_from, const schema_version& rhs_to)
{   PRESUME (lhs_from.unknown () || lhs_to.unknown () || (lhs_from.root () == lhs_to.root ()), __FILE__, __LINE__);
    PRESUME (rhs_from.unknown () || rhs_to.unknown () || (rhs_from.root () == rhs_to.root ()), __FILE__, __LINE__);
    if (! lhs_from.unknown ()) if (! rhs_from.unknown ()) if (lhs_from.root () != rhs_from.root ()) return false;
    if ((lhs_from > rhs_to) && ! rhs_to.unknown ()) return false;
    return (lhs_to.unknown () || (lhs_to >= rhs_from)); }

bool is_valid_schema_version (const e_schema root, const unsigned char j, const unsigned char n)
{   switch (root)
    {   case s_article :
        case s_book :
        case s_cc :
        case s_ctag :
        case s_gr :
        case s_ical :
        case s_icaltzd :
        case s_music :
        case s_og :
        case s_poetry :
        case s_profile :
        case s_rdf :
        case s_rdfs :
        case s_video :
        case s_wdrs :
        case s_website :
        case s_whatwg :
            return ((j == 1) && (n == 0));
        case s_dc :
        case s_dcam :
        case s_dcmi  :
        case s_dct  :
        case s_xsd  :
            return ((j == 1) && (n < 2));
        case s_foaf :
            return ((j == 0) && (n < 100));
        case s_microformats :
            if (n != 0) return false;
            return (j <= 2);
        case s_none :
            return true;
        case s_rdfa :
            if (j != 1) return false;
            return (n < 4);
        case s_schema :
            if ((j == 0) && (n == 0)) return true;
            if ((j > schema_major_max) || (j < 2)) return false;
            switch (j)
            {   case 2 : return n < 3;
                case 3 : return true;
                case 7 : return n < 5;
                default : return n == 0; }
        default :
            return false; } }

bool does_schema_apply (const schema_version& v, const schema_version& from, const schema_version& to)
{   if (v.any_flags (SV_WILDCARD)) return true;
    return does_apply < version > (v, from, to); }
