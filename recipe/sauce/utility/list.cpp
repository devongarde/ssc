/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "utility/list.h"
#include "symbol/nstr.h"
#include "parser/html_version.h"
#include "element/elem.h"
#include "element/element_classes.h"
#include "attribute/attr.h"
#include "ontology/ontology_type.h"
#include "ontology/ontology_property.h"
#include "ontology/ontology_structure.h"
#include "enum/type_class.h"
#include "microformat/field.h"
#include "type/type.h"

constexpr const char* const naughty_list_sep = ",";

::std::string wblist::inner_sub (const ::std::size_t n) const
{   const misd_t::const_iterator i = dim_.find (n);
    if (i != dim_.cend ()) return i -> second;
    return ::std::string (); }

bool wblist::inner_test (const ::std::size_t n, const ::std::string& s) const
{   if (empty ()) return false;
    szreg_t::const_iterator nice = nice_.find (n);
    if (nice != nice_.cend ())
    {   bool bad = true;
        for (sstr_t::const_iterator i = nice -> second.cbegin (); bad && (i != nice -> second.cend ()); ++i)
            if (::boost::regex_match (s, ::boost::regex (*i))) bad = false;
        if (bad) return true; }
    szreg_t::const_iterator naughty = naughty_.find (n);
    if (naughty != naughty_.cend ())
       for (sstr_t::const_iterator i = naughty -> second.cbegin (); (i != naughty -> second.cend ()); ++i)
            if (::boost::regex_match (s, ::boost::regex (*i))) return true;
    if (n == 0) return false;
    return inner_test (static_cast < ::std::size_t > (0), s); }

bool wblist::test_element (const html_version& v, nitpick& nits, const e_element e, const ::std::string& s, const ::std::string& ss, const bool no_close) const
{   if (is_error_element (e) || is_undefined_element (e))
        nits.pick (nit_naughty_init, es_warning, ec_init, "unknown element ", quote (s), " in fussiness ", quote (ss));
    else if (is_faux_element (e))
        nits.pick (nit_naughty_init, es_warning, ec_init, "naughty element ", quote (s), " in fussiness ", quote (ss));
    else if (is_css_element (e))
        nits.pick (nit_naughty_init, es_warning, ec_init, "CSS element ", quote (s), " in fussiness ", quote (ss));
    else
    {   const elem el (e);
        if (el.is_rdf ())
            nits.pick (nit_naughty_init, es_warning, ec_init, "RDF element ", quote (s), " in fussiness ", quote (ss));
        if (el.is_rsl ())
            nits.pick (nit_naughty_init, es_warning, ec_init, "RSL element ", quote (s), " in fussiness ", quote (ss));
        if (el.is_rss ())
            nits.pick (nit_naughty_init, es_warning, ec_init, "RSS element ", quote (s), " in fussiness ", quote (ss));
        else if (no_close && el.is_closed (v))
            nits.pick (nit_naughty_init, es_warning, ec_init, "closed element ", quote (s), " in fussiness ", quote (ss));
        else return true; }
    return false; }

::std::size_t wblist::init_params (const html_version& v, nitpick& nits, const ::std::string& ss, ::std::string& value)
{   ::std::string s (trim_the_lot_off (ss));
    if (! s.empty ())
    {   const ::std::string sect = split_at_first_of (s, naughty_list_sep);
        if (! sect.empty ())
            switch (sect.at (0))
            {   case 'A' :
                case 'a' :
                {   const ::std::string es = split_at_first_of (s, naughty_list_sep);
                    const e_element e = elem::find (v, es);
                    if (test_element (v, nits, e, es, ss, false))
                    {   const ::std::string as = split_at_first_of (s, naughty_list_sep);
                        const e_attribute a = attr::find (v, as);
                        if (is_error_attribute (a) || is_unknown_attribute (a))
                            nits.pick (nit_naughty_init, es_warning, ec_init, "unknown attribute ", as, " in fussiness ", quote (ss)); 
                        else if (! has_attribute (e, a))
                            nits.pick (nit_naughty_init, es_warning, ec_init, "element ", es, " has no attribute ", as, ", re fussiness ", quote (ss));
                        else if (s.empty ())
                            nits.pick (nit_naughty_init, es_warning, ec_init, "missing value in fussiness ", quote (ss));
                        else
                        {   value = s;
                            attributal_ = true;
                            return get_n (e, a); } }
                    break; }
                case 'C' :
                case 'c' :
                    if (! s.empty ())
                    {   value = s;
                        communal_ = true;
                        return 0; }
                    nits.pick (nit_naughty_init, es_warning, ec_init, "missing value in fussiness ", quote (ss));
                    break;
                case 'E' :
                case 'e' :
                {   const ::std::string es = split_at_first_of (s, naughty_list_sep);
                    const e_element e = elem::find (v, es);
                    if (test_element (v, nits, e, es, ss, true))
                        if (s.empty ())
                            nits.pick (nit_naughty_init, es_warning, ec_init, "missing value in fussiness ", quote (ss));
                        else
                        {   value = s;
                            elemental_ = true;
                            return get_n (e); }
                    break; }
                case 'M' :
                case 'm' :
                {   const ::std::string cs = split_at_first_of (s, naughty_list_sep);
                    html_class c (nits, v, cs);
                    if (! c.is_microformat_vocabulary ())
                        nits.pick (nit_naughty_init, es_warning, ec_init, "unknown microformat class ", cs, " in fussiness ", quote (ss));
                    else
                    {   const ::std::string ps = split_at_first_of (s, naughty_list_sep);
                        html_class p (nits, v, ps);
                        if (! p.is_microformat_property ())
                            nits.pick (nit_naughty_init, es_warning, ec_init, "unknown microformat property ", ps, " in fussiness ", quote (ss));
                        else if (! is_plausible_field (static_cast < e_class > (c.get ()), static_cast < e_property > (p.get ())))
                            nits.pick (nit_naughty_init, es_warning, ec_init, "class ", cs, " has no property ", ps, ", re fussiness ", quote (ss));
                        else if (s.empty ())
                            nits.pick (nit_naughty_init, es_warning, ec_init, "missing value in fussiness ", quote (ss));
                        else
                        {   value = s;
                            microformulaic_ = true;
                            return get_n (static_cast < e_property > (p.get ())); } }
                    break; }
                case 'O' :
                case 'o' :
                {   const ::std::string os = split_at_first_of (s, naughty_list_sep);
                    e_ontology o = ontology_names.find_mixed (v, ONTOLOGY_NAME, os);
                    if ((o == s_none) || (o == s_error))
                        o = ontology_names.find_mixed (v, ONTOLOGY_CURIE, os);
                    if ((o == s_none) || (o == s_error))
                        nits.pick (nit_naughty_init, es_warning, ec_init, "unknown ontology ", os, " in fussiness ", quote (ss));
                    else
                    {   const ::std::string ts = split_at_first_of (s, naughty_list_sep);
                        const e_ontology_type t = sch::parse (nits, v, ts, o);
                        if ((t != ont_context) && (t != ont_illegal))
                            if (sch::root (t) != o)
                                nits.pick (nit_naughty_init, es_warning, ec_init, "type ", ts, " is not associated with ontology ", os, " in fussiness ", quote (ss));
                            else
                            {   const ::std::string ps = split_at_first_of (s, naughty_list_sep);
                                const e_ontology_property p = identify_ontology_property (ps, o);
                                if ((p == op_context) || (p == op_illegal))
                                    nits.pick (nit_naughty_init, es_warning, ec_init, "unknown ontology property ", ps, " in fussiness ", quote (ss));
                                else if (! is_valid_ontology_property (v, t, p))
                                    nits.pick (nit_naughty_init, es_warning, ec_init, "ontology type ", ts, " has no property ", ps, ", re fussiness ", quote (ss));
                                else if (s.empty ())
                                    nits.pick (nit_naughty_init, es_warning, ec_init, "missing value in fussiness ", quote (ss));
                                else
                                {   value = s;
                                    ontological_ = true;
                                    return get_n (p); } } }
                    break; }
                case 'T' :
                case 't' :
                {   const ::std::string ts = split_at_first_of (s, naughty_list_sep);
                    e_type t = type_jag (ts);
                    if (t == t_unknown) t = static_cast < e_type > (lexical < int > :: cast (ts, t_unknown));
                    if ((t == t_unknown) || (t >= t_error))
                        nits.pick (nit_naughty_init, es_warning, ec_init, "unknown type ", ts, " in fussiness ", quote (ss));
                    else if (s.empty ())
                        nits.pick (nit_naughty_init, es_warning, ec_init, "missing value in fussiness ", quote (ss));
                    else if (test_value (nits, v, t, s))
                    {   value = s;
                        typical_ = true;
                        return get_n (t); }
                    break; }
                default :
                    nits.pick (nit_naughty_init, es_warning, ec_init, "expecting ATTRIBUTE, COMMON, ELEMENT, MICROFORMAT or ONTOLOGY at the start of ", quote (ss));
                    break; } }
    return 0; }

void wblist::init_nn (const html_version& v, nitpick& nits, szreg_t& reg, const ::std::string& s)
{   ::std::string value;
    const ::std::size_t n = init_params (v, nits, s, value);
    if ((n != 0) || (! value.empty ()))
    {   szreg_t::iterator i = reg.find (n);
        if (i != reg.cend ())
            i -> second.insert (value);
        else
        {   sstr_t l;
            l.insert (value);
            reg.insert (szreg_t::value_type (n, l)); } } }

void wblist::init_dim (const html_version& v, nitpick& nits, misd_t& ms, const ::std::string& s)
{   ::std::string value;
    const ::std::size_t n = init_params (v, nits, s, value);
    if ((n != 0) || (! value.empty ()))
        ms.insert (misd_t::value_type (n, value)); }

void wblist::init (const html_version& v, nitpick& nits, const vstr_t& naughty, const vstr_t& nice, const vstr_t& note)
{   for (auto s : naughty) init_nn (v, nits, naughty_, s);
    for (auto s : nice) init_nn (v, nits, nice_, s);
    for (auto s : note) init_dim (v, nits, dim_, s); }
