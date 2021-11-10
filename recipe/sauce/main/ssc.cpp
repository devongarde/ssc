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

#include "main/standard.h"
#include "main/context.h"
#include "feedback/nitout.h"
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
#include "type/type_csp.h"
#include "schema/schema_structure.h"
#include "schema/schema_property.h"
#include "schema/schema_name.h"
#include "symbol/nstr.h"
#include "webpage/root.h"
#include "webpage/corpus.h"
#include "webpage/fileindex.h"
#include "webpage/page.h"
#include "parser/text.h"
#include "type/type.h"
#include "url/url.h"
#include "url/url_sanitise.h"
#include "webpage/fileindex.h"

void init (nitpick& nits)
{   init_nit_macros ();
    nits_init ();
    nits.set_context (0, PROG " initialisation");
    state_init ();
    attr::init (nits);
    avm_init (nits);
    code_map_init (nits);
    csp_directive_init (nits);
    csp_keyword_init (nits);
    elem::init (nits);
    elements_init (nits);
    fields_init (nits);
    fileindex_init ();
    family_init (nits);
    sibling_init (nits);
    types_init (nits);
    parentage_init (nits);
    protocol::init (nits);
    sch::init (nits);
    schema_name_init (nits);
    schema_property_init (nits);
    init_nstrs (nits);
    svg_feature_init (nits);
    hierarchy_init (nits);
    microdata_init (nits);
    url::init (nits);
    wotsit_init (nits);
#ifdef DEBUG
    // avm_elem_crosscheck ();
#endif
}

int ciao ()
{   if (context.progress ()) ::std::cout << "\nFinishing\n";
    if (context.unknown_class () && context.tell (e_warning))
    {   ::std::ostringstream ss;
        context.css ().report_usage (ss);
        if (context.crosslinks ())
        {   nitpick nits;
            reconcile_crosslinks (nits);
            if (! nits.empty ()) dump_nits (nits, ns_link, ns_link_head, ns_link_foot);
            context.out () << ::std::endl; }
        {   if (! ss.str ().empty ())
                context.out (ss.str ());
            if (! empty_itemid ())
                context.out (report_itemids ()); } }
    if (context.stats_summary ()) context.report_stats (true);
    if (context.tell (e_debug)) context.out (fileindex_report ());
    if (context.severity_exceeded ()) return ERROR_STATE;
    return VALID_RESULT; }

int examine (nitpick& nits)
{   int res = VALID_RESULT;
    if (context.cgi ())
    {   page web (context.snippet (), cc_utf8);
        if (! web.invalid ()) web.examine ();
        ::std::string s (web.nits ().review ());
        s += web.report ();
        if (context.test ()) context.out (START_OF_SECTION " " SNIPPET "\n");
        context.out (s);
        return res; }
    open_corpus (nits, context.corpus ());
    paths_root virt (paths_root::virtual_roots ());
    virt.add_root (nix_path_to_local (context.root ()), "/");
    nitpick shadow, exp;
    if (! context.shadow_root ().empty ())
    {   VERIFY_NOT_NULL (virt.at (0), __FILE__, __LINE__);
        if (! virt.at (0) -> shadow_root (shadow, context.shadow_root ()))
            res = ERROR_STATE; }
    if (res != ERROR_STATE)
        if (! context.export_root ().empty ())
        {   VERIFY_NOT_NULL (virt.at (0), __FILE__, __LINE__);
            if (! virt.at (0) -> set_export (exp, context.export_root ()))
                res = ERROR_STATE; }
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
        {   if (context.progress ())
            {   VERIFY_NOT_NULL (virt.at (n), __FILE__, __LINE__);
                ::std::cout << "Scanning " << virt.at (n) -> get_disk_path ().string () << " ."; }
            try
            {   VERIFY_NOT_NULL (vd.at (n), __FILE__, __LINE__);
                VERIFY_NOT_NULL (virt.at (n), __FILE__, __LINE__);
                if (! vd.at (n) -> scan (nits, virt.at (n) -> get_site_path ()))
                {   nits.pick (nit_scan_failed, es_catastrophic, ec_init, "scan of ", virt.at (n) -> get_disk_path (), " failed");
                    res = ERROR_STATE; } }
            catch (const ::std::system_error& e)
            {   nits.pick (nit_scan_failed, es_catastrophic, ec_init, "scanning ", virt.at (n) -> get_disk_path (), " raised system error ", e.what ());
                res = ERROR_STATE; }
            catch (const ::std::exception& e)
            {   nits.pick (nit_scan_failed, es_catastrophic, ec_init, "scanning ", virt.at (n) -> get_disk_path (), " raised the exception ", e.what ());
                res = ERROR_STATE; }
            catch (...)
            {   nits.pick (nit_scan_failed, es_catastrophic, ec_init, "scanning ", virt.at (n) -> get_disk_path (), " raised an exception");
                res = ERROR_STATE; }
            if (context.progress ()) ::std::cout << ::std::endl; }
        if (res == VALID_RESULT)
        {   PRESUME (vd.size () > 0, __FILE__, __LINE__);
            ::std::size_t n = integrate_virtuals (virt, vd);
            if (n != 0)
            {   nits.pick (nit_bad_path, es_catastrophic, ec_init, "cannot integrate ", virt.at (n) -> get_disk_path ());
                res = ERROR_STATE; }
            else
            {   if (context.dodedu ()) dedu (shadow);
                for (n = 0; n < vmax; ++n)
                {   if (context.progress ())
                    {   VERIFY_NOT_NULL (virt.at (n), __FILE__, __LINE__);
                        ::std::cout << "Checking " << virt.at (n) -> get_disk_path ().string () << ::std::endl; }
                    try
                    {   VERIFY_NOT_NULL (vd.at (n), __FILE__, __LINE__);
                        VERIFY_NOT_NULL (virt.at (n), __FILE__, __LINE__);
                        if (vd.at (n) -> empty ())
                            nits.pick (nit_no_content, es_comment, ec_init, virt.at (n) -> get_disk_path (), " has no content.");
                        else
                            vd.at (n) -> examine (nits); }
                    catch (const ::std::system_error& e)
                    {   nits.pick (nit_examine_failed, es_catastrophic, ec_init, "examining ", virt.at (n) -> get_disk_path (), " raise the system error ", e.what ());
                        res = ERROR_STATE; }
                    catch (const ::std::exception& e)
                    {   nits.pick (nit_examine_failed, es_catastrophic, ec_init, "examining ", virt.at (n) -> get_disk_path (), " raised the exception ", e.what ());
                        res = ERROR_STATE; }
                    catch (...)
                    {   nits.pick (nit_examine_failed, es_catastrophic, ec_init, "examining ", virt.at (n) -> get_disk_path (), " raised an exception");
                        res = ERROR_STATE; } } } } }
    close_corpus (nits);
    fileindex_save_and_close (nits);
    dump_nits (nits, ns_update, ns_update_head, ns_update_foot);
    dump_nits (exp, ns_export, ns_export_head, ns_export_foot);
    dump_nits (shadow, ns_shadow, ns_shadow_head, ns_shadow_foot);
    return res; };

int main (int argc, char** argv)
{   int res = NOTHING_TO_DO;
    bool enfooten = false;
    ::std::string msg;
    try
    {   const auto start = ::std::chrono::system_clock::now ();
        const std::time_t start_time = ::std::chrono::system_clock::to_time_t (start);
        ::std::string t (::std::ctime (&start_time));
        t = t.substr (0, t.length () - 1);
        context.macros ().emplace (nm_time_start, t);
        context.macros ().emplace (nm_compile_time, __DATE__ " " __TIME__);
        vstr_t v (split_by_charset (VERSION_STRING, "."));
        PRESUME (v.size () == 3, __FILE__, __LINE__);
        PRESUME (lexical < int > :: cast (v.at (0)) == VERSION_MAJOR, __FILE__, __LINE__);
        PRESUME (lexical < int > :: cast (v.at (1)) == VERSION_MINOR, __FILE__, __LINE__);
        PRESUME (lexical < int > :: cast (v.at (2)) == VERSION_RELEASE, __FILE__, __LINE__);
        nitpick nits, nuts;
        init (nits);
        PRESUME (argc > 0, __FILE__, __LINE__);
        VERIFY_NOT_NULL (argv, __FILE__, __LINE__);
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26481) // erm, linter, you do know about the C++ main function's signature, don't you?
#endif // _MSC_VER
        ::std::string args (argv [0]);
        for (int i = 1; i < argc; ++i)
        {   args += " ";
            args += argv [i]; }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
        context.macros ().emplace (nm_run_args, args);
        res = context.parameters (nuts, argc, argv);
        if (context.todo () == do_simple)
        {   ::std::cout << SIMPLE_TITLE << context.domsg ();
            return VALID_RESULT; }
        if (! is_template_loaded ()) load_template (nits, html_default);
        context.out () << apply_macros (ns_doc_head);
        enfooten = true;
        dump_nits (nits, ns_init, ns_init_head, ns_init_foot);
        if (context.todo () == do_booboo) res = ERROR_STATE;
        else
        {   if (! fileindex_load (nuts)) res = ERROR_STATE;
            dump_nits (nuts, ns_config, ns_config_head, ns_config_foot);
            res = examine (nits);
            if ((res == VALID_RESULT) && context.process_webmentions ())
            {   context.process_outgoing_webmention (nits, html_current);
                context.process_incoming_webmention (nits, html_current);
                dump_nits (nits, ns_webmention, ns_webmention_head, ns_webmention_foot); }
            const int cr = ciao ();
            if (cr > res) res = cr; }
        const auto fin = std::chrono :: system_clock :: now ();
        const std::chrono::duration <double> elapsed_seconds = fin - start;
        const std::time_t end_time = std::chrono::system_clock::to_time_t (fin);
        t = ::std::ctime (&end_time);
        t = t.substr (0, t.length () - 1);
        context.macros ().emplace (nm_time_finish, t);
        context.macros ().emplace (nm_time_duration, ::boost::lexical_cast < ::std::string > (floor ((elapsed_seconds.count () * 1000.0) + 0.5) / 1000.0)); }
    catch (const ::std::system_error& e)
    {   msg = "catastrophic exit with system error ";
        msg += e.what ();
        res = ERROR_STATE; }
    catch (const ::std::exception& e)
    {   msg = "catastrophic exit with the exception ";
        msg += e.what ();
        res = ERROR_STATE; }
    catch (...)
    {   msg = "catastrophic exit with an unknown exception";
        res = ERROR_STATE; }
    if (! enfooten)
    {   if (! msg.empty ()) ::std::cerr << msg << "\n"; }
    else try
    {   if (! msg.empty ()) context.macros ().emplace (nm_run_catastrophe, msg);
        context.out () << apply_macros (ns_doc_foot); }
    catch (...)
    {   if (msg.empty ()) msg = "catastrophic exception writing footers\n";
        ::std::cerr << msg << "\n";
        res = ERROR_STATE; }
    return res; };
