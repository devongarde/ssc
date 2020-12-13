/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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
#include "main/context.h"
#include "webpage/directory.h"
#include "attribute/attr.h"
#include "attribute/avm.h"
#include "css/css_cache.h"
#include "element/elem.h"
#include "element/element_classes.h"
#include "microformat/family.h"
#include "microformat/field.h"
#include "microformat/sibling.h"
#include "element/parentage.h"
#include "microformat/property.h"
#include "schema/schema_hierarchy.h"
#include "microdata/microdata_itemid.h"
#include "schema/schema_structure.h"
#include "schema/schema_property.h"
#include "schema/schema_name.h"
#include "webpage/root.h"
#include "parser/text.h"
#include "type/type.h"
#include "url/url.h"
#include "url/url_sanitise.h"
#include "webpage/fileindex.h"

void init (nitpick& nits)
{   nit::init ();
    attr::init (nits);
    avm_init (nits);
    code_map_init (nits);
    elem::init (nits);
    elements_init (nits);
    fields_init (nits);
    family_init (nits);
    sibling_init (nits);
    types_init (nits);
    parentage_init (nits);
    protocol::init (nits);
    sch::init (nits);
    schema_name_init (nits);
    schema_property_init (nits);
    hierarchy_init (nits);
    microdata_init (nits);
    url::init (nits);
    wotsit_init (nits); }

void dump_nits (nitpick& nits, const char* burble)
{   if (! nits.empty ())
        if (context.tell (static_cast < e_verbose > (nits.worst ())))
        {   context.out () << "\n\n*** " << burble << "\n";
            context.out () << nits.review (); }
    nits.reset (); }

void configure (std::time_t& start_time)
{   if (! context.test ())
    {   if (context.tell (e_severe)) context.out () << "\nStart: " << ::std::ctime (&start_time);
        if (context.tell (e_info)) context.out () << "Gathering site information...\n"; } }

void ciao ()
{   if (context.unknown_class () && context.tell (e_warning))
    {   ::std::ostringstream ss;
        context.css ().report_usage (ss);
        if (context.crosslinks ())
        {   nitpick nits;
            reconcile_crosslinks (nits);
            if (! nits.empty ())
            {   context.out () << "\n\n*** link errors\n";
                context.out () << nits.review (); } }
        if (! ss.str ().empty ())
        {   context.out () << "\n\n*** classes\n";
            context.out () << ss.str (); }
        if (! empty_itemid ())
        {   context.out () << "\n\n*** itemids\n";
            context.out () << report_itemids (); } }
    if (context.stats_summary ()) context.report_stats ();
    if (context.tell (e_debug)) context.out () << fileindex_report (); }

int examine (nitpick& nits)
{   int res = VALID_RESULT;
    paths_root virt (paths_root::virtual_roots ());
    virt.add_root (nix_path_to_local (context.root ()), "/");
    nitpick shadow, exp;
    if (! context.shadow ().empty ())
        if (! virt.at (0) -> shadow (shadow, context.shadow ()))
            res = ERROR_STATE;
    if (res != ERROR_STATE)
        if (! context.export_root ().empty ())
            if (! virt.at (0) -> set_export (exp, context.export_root ()))
                res = ERROR_STATE;
    if (res != ERROR_STATE)
    {   for (auto v : context.virtuals ())
            virt.add_virtual (shadow, v);
        for (auto vv : context.shadows ())
            if (! virt.add_shadow (shadow, vv))
            {   res = ERROR_STATE; break; } }
    if (res != ERROR_STATE)
       for (auto v : context.exports ())
            if (! virt.add_export (exp, v))
            {   res = ERROR_STATE; break; }
    if (res != ERROR_STATE)
    {   const ::std::size_t vmax (virt.size ());
        vd_t vd;
        vd.reserve (vmax);
        for (::std::size_t n = 0; n < vmax; ++n)
            vd.emplace_back (new directory (virt.at (n)));
        for (::std::size_t n = 0; n < vmax; ++n)
        {   if (context.tell (e_info) && ! context.test ()) context.out () << "Scanning " << virt.at (n) -> get_disk_path () << " ...\n";
            try
            {   if (! vd [n] -> scan (nits, virt.at (n) -> get_site_path ()))
                {   nits.pick (nit_scan_failed, es_catastrophic, ec_init, "scan of ", virt.at (n) -> get_disk_path (), " failed");
                    res = ERROR_STATE; } }
            catch (const ::std::system_error& e)
            {   nits.pick (nit_scan_failed, es_catastrophic, ec_init, "scan of ", virt.at (n) -> get_disk_path (), " caused ", e.what ());
                res = ERROR_STATE; }
            catch (...)
            {   nits.pick (nit_scan_failed, es_catastrophic, ec_init, "scan of ", virt.at (n) -> get_disk_path (), " caused an exception");
                res = ERROR_STATE; } }
        if (res == VALID_RESULT)
        {   assert (vd.size () > 0);
            ::std::size_t n = integrate_virtuals (virt, vd);
            if (n != 0)
            {   nits.pick (nit_bad_path, es_catastrophic, ec_init, "cannot integrate ", virt.at (n) -> get_disk_path ());
                res = ERROR_STATE; }
            else
            {   if (context.dodedu ()) dedu (shadow);
                for (n = 0; n < vmax; ++n)
                {   if (context.tell (e_info) && ! context.test ()) context.out () << "Checking " << virt.at (n) -> get_disk_path () <<  "...\n";
                    try
                    {   if (vd.at (n) -> empty ())
                            nits.pick (nit_no_content, es_comment, ec_init, virt.at (n) -> get_disk_path (), " has no content.");
                        else
                            vd.at (n) -> examine (nits); }
                    catch (const ::std::system_error& e)
                    {   nits.pick (nit_examine_failed, es_catastrophic, ec_init, "examination of ", virt.at (n) -> get_disk_path (), " caused ", e.what ());
                        res = ERROR_STATE; }
                    catch (...)
                    {   nits.pick (nit_examine_failed, es_catastrophic, ec_init, "examination of ", virt.at (n) -> get_disk_path (), " caused an exception");
                        res = ERROR_STATE; } } } } }
    dump_nits (nits, "examine");
    dump_nits (exp, "exports");
    dump_nits (shadow, "shadow");
    return res; };

int main (int argc, char** argv)
{   auto start = ::std::chrono::system_clock::now ();
    std::time_t start_time = ::std::chrono::system_clock::to_time_t (start);
    nitpick nits;
    nits.set_context (0, PROG " initialisation");
    init (nits);
    dump_nits (nits, "initialisation");
    int res = context.parameters (argc, argv);
    if (res == VALID_RESULT)
    {   configure (start_time);
        res = examine (nits);
        if ((res == VALID_RESULT) && context.process_webmentions ())
        {   html_version v (5, context.html_minor ());
            context.process_outgoing_webmention (nits, v);
            context.process_incoming_webmention (nits, v);
            dump_nits (nits, "webmention"); }
        ciao ();
        if (! context.test ())
        {   auto fin = std::chrono :: system_clock :: now();
            std::chrono::duration<double> elapsed_seconds = fin - start;
            std::time_t end_time = std::chrono::system_clock::to_time_t (fin);
            if (context.tell (e_severe)) context.out ()  << "\nFinish: " << ::std::ctime (&end_time);
            if (context.tell (e_warning)) context.out () << "Duration: " << elapsed_seconds.count () << " seconds\n"; } }
    return res; };
