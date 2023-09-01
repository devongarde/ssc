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
#include "feedback/nitout.h"
#include "main/context.h"
#include "webpage/directory.h"
#include "attribute/attr.h"
#include "attribute/avm.h"
#include "element/elem.h"
#include "element/element_classes.h"
#include "microformat/family.h"
#include "microformat/field.h"
#include "microformat/sibling.h"
#include "element/parentage.h"
#include "microformat/property.h"
#include "ontology/ontology_hierarchy.h"
#include "microdata/microdata_itemid.h"
#include "type/type.h"
#include "ontology/ontology_version.h"
#include "ontology/ontology_structure.h"
#include "ontology/ontology_property.h"
#include "ontology/ontology_name.h"
#include "spell/spell.h"
#include "symbol/nstr.h"
#include "webpage/root.h"
#include "webpage/corpus.h"
#include "webpage/fileindex.h"
#include "webpage/page.h"
#include "parser/text.h"
#include "parser/parse_ssi.h"
#include "url/curl.h"
#include "url/url.h"
#include "url/url_sanitise.h"
#include "webpage/fileindex.h"
#include "icu/lingo.h"
#include "utility/filesystem.h"
#include "utility/cache.h"
#include "coop/lox.h"
#include "webpage/q.h"
#include "coop/kew.h"
#include "coop/knickers.h"
#include "main/balloon.h"

const char* build_info = BUILD_INFO;
const char* test_title = TEST_TITLE;
const char* simple_title = SIMPLE_TITLE;
const char* full_title = FULL_TITLE;

void init (nitpick& nits)
{   init_cache ();
    state_init ();
    init_macro ();
    init_itemid ();
    init_itemprop ();
    init_rdfa_prop ();
    init_crosslinks ();
    nits_init ();
    nits.set_context (0, PROG " initialisation");
    types_init (nits);
    spell_init (nits);
    lingo::init (nits);
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
    parentage_init (nits);
    protocol::init (nits);
    sch::init (nits);
    ontology_name_init (nits);
    ontology_property_init (nits);
    ontology_version::init (nits);
    init_nstrs (nits);
    svg_feature_init (nits);
    hierarchy_init (nits);
    microdata_init (nits);
    url::init (nits);
    wotsit_init (nits);
    curl_init (); }

int ciao ()
{   ::std::ostringstream ss;
    curl_done ();
    global_css.accumulate (&overall);
    if (context.tell (es_warning))
    {   if (context.classic () && ! context.stats_summary ())
            ss << overall.class_and_id_report ();
        if (context.crosslinks ())
        {   nitpick nits;
            reconcile_crosslinks (nits);
            if (! nits.empty ())
            {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
                macro -> dump_nits (nits, ns_link, ns_link_head, ns_link_foot); }
            nits.accumulate (&overall);
            outstr.out ("\n"); } }
    if (! ss.str ().empty ())
        outstr.out (ss.str ());
    if (context.tell (es_warning))
        if (! empty_itemid ())
            outstr.out (report_itemids ());
    if (context.stats_summary ()) report_global_stats (true);
    if (context.tell (es_debug)) outstr.out (fileindex_report ());
    spell_terminate ();
    if (overall.severity_exceeded ()) return ERROR_STATE;
    return VALID_RESULT; }

#ifndef NO_FRED
void trundle ()
{   if (context.fred () == 1)
        while (fred.dqe ());
    else
    {   ::std::this_thread::yield ();
        while (fred.dqe () || q.activity ())
            ::std::this_thread::yield (); } }
#endif // NO_FRED

int examine (nitpick& nits)
{   int res = VALID_RESULT;
    if (context.cgi ())
    {   page web (context.snippet ());
        try
        {   if (! web.invalid ()) web.examine ();
            ::std::string s (web.nits ().review ());
                web.nits ().accumulate (&overall);
            s += web.report ();
            web.cleanup ();
            if (context.test ()) outstr.out (START_OF_SECTION " " SNIPPET "\n");
            outstr.out (s); }
        catch (...)
        {   web.cleanup (); throw; }
        return res; }
    nitpick shadow, exp;
    open_corpus (nits, context.corpus ());
    paths_root& virt (paths_root::virtual_roots ());
    virt.add_root (absolute_name ( canonical_name (nix_path_to_local (context.root ()))), "/");
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
            virt.add_virtual (shadow, canonical_name (absolute_name (nix_path_to_local (v))).string ());
        for (auto vv : context.shadows ())
            if (! virt.add_shadow (shadow, canonical_name (absolute_name (nix_path_to_local (vv))).string ()))
            {   res = ERROR_STATE; break; } }
    if (res != ERROR_STATE)
        for (auto v : context.exports ())
            if (! virt.add_export (exp, canonical_name (absolute_name (nix_path_to_local (v))).string ()))
            {   res = ERROR_STATE; break; }
    if (res != ERROR_STATE)
    {   const ::std::size_t vmax (virt.size ());
        vd_t vd;
        vd.reserve (vmax);
        for (::std::size_t n = 0; n < vmax; ++n)
            vd.emplace_back (new directory (virt.at (n), GSL_NARROW_CAST < short > (n)));
        nitpick nuts;
        knickers k (nuts, &nits);
#ifndef NO_FRED
        if (! fred.init (nits)) res = ERROR_STATE;
#endif // NO_FRED
        else try
        {   for (::std::size_t x = 0; (res != ERROR_STATE) && (x < vmax); ++x)
            {   VERIFY_NOT_NULL (vd.at (x), __FILE__, __LINE__);
                VERIFY_NOT_NULL (virt.at (x), __FILE__, __LINE__);
                if (! vd.at (x) -> scan (&nits, virt.at (x) -> get_site_path ()))
                {   nuts.pick (nit_scan_failed, es_catastrophic, ec_init, "scan of ", virt.at (x) -> get_disk_path (), " failed");
                    res = ERROR_STATE; } }
#ifndef NO_FRED
            if (res != VALID_RESULT) fred.abandon ();
            else
            {   trundle ();
#else // NO_FRED
            if (res == VALID_RESULT)
            {
#endif // NO_FRED
                PRESUME (vd.size () > 0, __FILE__, __LINE__);
                ::std::size_t n = integrate_virtuals (virt, vd);
                if (n != 0)
                {   nuts.pick (nit_bad_path, es_catastrophic, ec_init, "cannot integrate ", virt.at (n) -> get_disk_path ());
                    res = ERROR_STATE; }
                else
                {   if (context.dodedu ()) dedu (shadow);
                    for (n = 0; n < vmax; ++n)
                        if (vd.at (n) -> empty ())
                            nuts.pick (nit_no_content, es_comment, ec_init, virt.at (n) -> get_disk_path (), " has no content.");
#ifndef NO_FRED
                        else q.push (q_entry (&nits, vd.at (n), st_folder));
                    trundle (); } }
            fred.await ();
#else // NO_FRED
                        examine (&nits, vd.at (n));
                    trundle (); } }
#endif // NO_FRED
            spell_free ();
            close_corpus (nuts);
            fileindex_save_and_close (nuts); }
        catch (const ::std::system_error& e)
        {   nuts.pick (nit_scan_failed, es_catastrophic, ec_init, "system error ", e.what ());
            res = ERROR_STATE; }
        catch (const ::std::exception& e)
        {   nuts.pick (nit_scan_failed, es_catastrophic, ec_init, "exception ", e.what ());
            res = ERROR_STATE; }
        catch (...)
        {   nuts.pick (nit_scan_failed, es_catastrophic, ec_init, "unknown exception");
            res = ERROR_STATE; } }
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> dump_nits (nits, ns_update, ns_update_head, ns_update_foot);
    macro -> dump_nits (exp, ns_export, ns_export_head, ns_export_foot);
    macro -> dump_nits (shadow, ns_shadow, ns_shadow_head, ns_shadow_foot);
    return res; };

int main (int argc, char** argv)
{   int res = NOTHING_TO_DO;
    bool enfooten = false;
    ::std::string msg;
    PRESUME (argc > 0, __FILE__, __LINE__);
    VERIFY_NOT_NULL (argv, __FILE__, __LINE__);
    try
    {   time_balloon balloon;
        vstr_t v (split_by_charset (VERSION_STRING, "."));
        PRESUME (v.size () == 3, __FILE__, __LINE__);
        PRESUME (lexical < int > :: cast (v.at (0)) == VERSION_MAJOR, __FILE__, __LINE__);
        PRESUME (lexical < int > :: cast (v.at (1)) == VERSION_MINOR, __FILE__, __LINE__);
        PRESUME (lexical < int > :: cast (v.at (2)) == VERSION_RELEASE, __FILE__, __LINE__);
        nitpick nits, nuts;
        init (nits);
        context.started (balloon.inflate_time ());
        context.build (__DATE__ " " __TIME__);
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26481)
#endif // _MSC_VER
        ::std::string args (argv [0]);
        for (int i = 1; i < argc; ++i)
        {   args += " ";
            args += argv [i]; }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (nm_context_build, build_info);
        macro -> set (nm_run_args, args);
        context.general_info (::boost::filesystem::current_path ().string () + "\n" + args + "\n" VERSION_STRING " [" __DATE__  " " __TIME__ "] [" + build_info + "]\n");
        res = context.parameters (nuts, argc, argv);
#ifdef DEBUG
        avm_elem_crosscheck ();
#endif
        if (context.todo () == do_simple)
        {   ::std::cout << full_title;
            ::std::cout << context.domsg ();
            return VALID_RESULT; }
        if (context.progress ()) ::std::cout << "\npreparing\n";
        if (! macro -> is_template_loaded ()) macro -> load_template (nuts, html_default);
        outstr.out (macro -> apply (ns_doc_head));
        enfooten = true;
        macro -> dump_nits (nits, ns_init, ns_init_head, ns_init_foot);
        if (context.invalid () || (context.todo () == do_booboo) || (res == ERROR_STATE) || (nuts.worst () <= es_error))
        {   macro -> dump_nits (nuts, ns_config, ns_config_head, ns_config_foot);
            if (msg.empty ()) msg = "\n" TYPE_HELP "\n";
            res = ERROR_STATE; }
        else
        {   if (! fileindex_load (nuts)) res = ERROR_STATE;
            macro -> dump_nits (nuts, ns_config, ns_config_head, ns_config_foot);
            res = examine (nits);
            nits.accumulate (&overall);
            const int cr = ciao ();
            if (cr > res) res = cr; }
        balloon.pop ();
        macro -> set (nm_time_finish, balloon.pop_time ());
        macro -> set (nm_time_duration, balloon.duration ()); }
    catch (const ::std::system_error& e)
    {   msg = "catastrophic exit with system error: ";
        msg += e.what ();
        res = ERROR_STATE; }
    catch (const ::std::exception& e)
    {   msg = "catastrophic exit with exception: ";
        msg += e.what ();
        res = ERROR_STATE; }
    catch (...)
    {   msg = "catastrophic exit with an unknown exception";
        res = ERROR_STATE; }
    if (! enfooten)
    {   if (! msg.empty ()) ::std::cerr << msg << "\n"; }
    else try
    {   if (! msg.empty ()) macro -> set (nm_run_catastrophe, msg);
        outstr.out (macro -> apply (ns_doc_foot));
        if (! msg.empty ()) outstr.err (msg + "\n"); }
    catch (...)
    {   if (msg.empty ()) msg = "catastrophic exception writing footers\n";
        ::std::cerr << msg << "\n";
        res = ERROR_STATE; }
    fred.done ();
    if (context.progress ())
        if (outstr.name ().empty ()) ::std::cout << "finished\n";
        else ::std::cout << "results written to " << outstr.name () << "\n";
    return res; };
