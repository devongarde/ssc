/*
ssc (static site checker)
File Info
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
#include "webpage/page.h"
#include "element/element.h"
#include "attribute/attribute_classes.h"

void element::verify_rdfa ()
{
    // FFS, work this
}

::std::string element::get_rdfa_value () const
{   if (a_.known (a_content))
        return a_.get_string (a_content);
    switch (tag ())
    {   case elem_a :
        case elem_area :
        case elem_link :
            return a_.get_string (a_href);
        case elem_audio :
        case elem_embed :
        case elem_iframe :
        case elem_img :
        case elem_source :
        case elem_track :
        case elem_video :
            return a_.get_string (a_src);
        case elem_data :
        case elem_meter :
            return a_.get_string (a_value);
        case elem_object :
            return a_.get_string (a_data);
        case elem_t :
        case elem_time :
            return a_.get_string (a_datetime);
        default :
            return node_.text (); } }

void element::examine_about ()
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
    if (a_.good (a_about))
    {   node_.prepare_rdfa ();
        VERIFY_NOT_NULL (node_.rdfa (), __FILE__, __LINE__);
        ::std::string s (a_.get_string (a_about));
        if (s.find (':') == ::std::string::npos) s = page_ -> get_absolute_url (s); } }

void element::examine_datatype (flags_t& flags)
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
    const bool nowt = a_.empty (a_datatype);
    if (nowt || a_.good (a_datatype))
    {   node_.prepare_rdfa ();
        rdf_ptr ptr = node_.rdfa ();
        VERIFY_NOT_NULL (ptr.get (), __FILE__, __LINE__);
        if (nowt) flags |= EF_NULL_DATATYPE;
        else
        {   ::std::string dt (tart (a_.get_string (a_datatype)));
            const e_ontology_type t = ptr -> note_type (node_.nits (), node_.version (), dt, *page_);
            switch (t)
            {   case rdf_xmlliteral :
                    flags |= EF_XL_DATATYPE;
                    break;
                case ont_illegal :
                    pick (nit_unknown_datatype, ed_rdfa, "6.3.1.3. XML Literals", es_error, ec_rdfa, "Unknown RDFa DATATYPE ", quote (dt));
                    break;
                default :
                    ptr -> verify_value (node_.nits (), node_.version (), t, get_rdfa_value ());
                    break; } } } }

void element::examine_inlist ()
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
}

void element::examine_instanceof ()
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
}

void element::examine_prefix ()
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
}

void element::examine_property ()
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
    if (a_.good (a_property))
    {   node_.prepare_rdfa ();
        rdf_ptr ptr = node_.rdfa ();
        VERIFY_NOT_NULL (ptr.get (), __FILE__, __LINE__);
        ::std::string value (get_rdfa_value ());
        const bool is_link = (tag () == elem_a) || (tag () == elem_link) || (tag () == elem_area);
        vstr_t props (split_by_space (a_.get_string (a_property)));
        nitpick knots;
        for (auto p : props)
            ptr -> note_prop (node_.nits (), node_.version (), p, value, is_link, *page_); } }

// I need to distinguish rev and rel
void element::examine_rdfa_rel (const ::std::string& prop)
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
    if (a_.good (a_rel))
    {   node_.prepare_rdfa ();
        rdf_ptr ptr = node_.rdfa ();
        VERIFY_NOT_NULL (ptr.get (), __FILE__, __LINE__);
        ::std::string value (get_rdfa_value ());
        const bool is_link = (tag () == elem_a) || (tag () == elem_link) || (tag () == elem_area);
        vstr_t rels (split_by_space (prop));
        nitpick knots;
        for (auto r : rels)
            ptr -> note_prop (knots, node_.version (), r, value, is_link, *page_);
        if (! context.microformats ()) nits ().merge (knots); } }

void element::examine_rdfa_rev (const ::std::string& prop)
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
    if (a_.good (a_rel))
    {   node_.prepare_rdfa ();
        rdf_ptr ptr = node_.rdfa ();
        VERIFY_NOT_NULL (ptr.get (), __FILE__, __LINE__);
        ::std::string value (get_rdfa_value ());
        const bool is_link = (tag () == elem_a) || (tag () == elem_link) || (tag () == elem_area);
        vstr_t revs (split_by_space (prop));
        nitpick knots;
        for (auto r : revs)
            ptr -> note_prop (node_.nits (), node_.version (), r, value, is_link, *page_);
        if (! context.microformats ()) nits ().merge (knots); } }

void element::examine_resource ()
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
}

void element::examine_typeof ()
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
    if (a_.good (a_typeof))
    {   node_.prepare_rdfa ();
        rdf_ptr ptr = node_.rdfa ();
        VERIFY_NOT_NULL (ptr.get (), __FILE__, __LINE__);
        ::std::string value (a_.get_string (a_typeof));
        vstr_t vals (split_by_space (value));
        nitpick knots;
        for (auto r : vals)
            ptr -> note_type (node_.nits (), node_.version (), r, *page_); } }

void element::examine_vocab ()
{   PRESUME (context.has_rdfa (), __FILE__, __LINE__);
    PRESUME (node_.version () >= xhtml_1_0, __FILE__, __LINE__);
    if (a_.good (a_vocab))
    {   node_.prepare_rdfa ();
        rdf_ptr ptr = node_.rdfa ();
        VERIFY_NOT_NULL (ptr.get (), __FILE__, __LINE__);
        ptr -> note_vocab (node_.nits (), node_.version (), a_.get_string (a_vocab), *page_); } }

