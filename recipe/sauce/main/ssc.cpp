/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "attribute/attr_state.h"
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
#include "enum/type_aria.h"
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
#include "webpage/required.h"
#include "parser/text.h"
#include "parser/parse_ssi.h"
#include "url/fetch.h"
#include "url/url.h"
#include "url/url_sanitise.h"
#include "icu/lingo.h"
#include "utility/filesystem.h"
#include "utility/cache.h"
#include "coop/lox.h"
#include "webpage/q.h"
#include "coop/kew.h"
#include "coop/knickers.h"
#include "main/balloon.h"
#include "main/ssc.h"
#include "main/server.h"
#ifdef WX
#include "gui/gui-data.h"
#include "gui/gui-app.h"
#endif // WX

int cycle_start (nitpick& nits)
{   reset_httpequiv ();
    reset_crosslinks ();
    reset_fileindices ();
    reset_itemid ();
    reset_itemprop ();
    reset_macro ();
    reset_rdfa_prop ();
    reset_spell ();
    overall.reset ();
    directory::reinit ();
    paths_root::reinit ();
    nits.set_context (0, PROG " reinitialisation");
    types_init (nits);
    nitpick::reset_severities ();
    server_t::reinit ();
    return VALID_RESULT; }

void init (nitpick& nits)
{   vstr_t v (split_by_charset (VERSION_STRING, "."));
    PRESUME (v.size () == 3, __FILE__, __LINE__);
    PRESUME (lexical < int > :: cast (v.at (0)) == VERSION_MAJOR, __FILE__, __LINE__);
    PRESUME (lexical < int > :: cast (v.at (1)) == VERSION_MINOR, __FILE__, __LINE__);
    PRESUME (lexical < int > :: cast (v.at (2)) == VERSION_RELEASE, __FILE__, __LINE__);
    output_init ();
    cache_init ();
    state_init ();
    nits_init ();
    cycle_start (nits);
    spell_init (nits);
    lingo::init (nits);
    attr::init (nits);
    as_init ();
    avm_init (nits);
    code_map_init (nits);
    csp_directive_init (nits);
    csp_keyword_init (nits);
    elem::init (nits);
    elements_init (nits);
    fields_init (nits);
    family_init (nits);
    sibling_init (nits);
    parentage_init (nits);
    protocol::init (nits);
    sch::init (nits);
    ontology_name_init (nits);
    ontology_property_init (nits);
    ontology_version::init (nits);
    nstr_init (nits);
    svg_feature_init (nits);
    hierarchy_init (nits);
    microdata_init (nits);
    url::init (nits);
    wotsit_init (nits);
    server_t::init (nits);
    aria_init ();
#ifdef DEBUG
    avm_elem_crosscheck ();
#endif
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__); }

int ciao ()
{   spell_free ();
    server_t::teardown ();
    return VALID_RESULT; }

int cycle_finish ()
{   ::std::ostringstream ss;
    global_css.accumulate (&overall);
    if (context.tell (es_warning))
    {   if (context.classic () && ! context.stats (rcb_summary))
            ss << overall.class_and_id_report ();
        if (context.crosslinks ())
        {   nitpick nits;
            reconcile_crosslinks (nits);
            if (! nits.empty ())
            {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
                macro -> dump_nits (nits, ns_link, ns_link_head, ns_link_foot); }
            nits.accumulate (&overall);
            context.os () -> out ("\n"); } }
    if (! ss.str ().empty ())
        context.os () -> out (ss.str ());
    if (context.stats (rcb_itemid))
        if (! empty_itemid ())
            context.os () -> out (report_itemids ());
    if (context.stats (rcb_summary)) context.os () -> out (report_global_stats (true));
    if (context.tell (es_debug)) context.os () -> out (fileindex_report ());
    if (overall.severity_exceeded ()) return ERROR_STATE;
    global_css.reset ();
    return VALID_RESULT; }

#ifndef NO_FRED
void trundle ()
{   if (context.fred () == 1)
        while (fred.dqe ())
#ifdef WX
        {   if (app != nullptr) app -> Yield (true); }
#else // WX
        ;
#endif // WX
    else
    {   ::std::this_thread::yield ();
        while (fred.dqe () || q.activity ())
        {
#ifdef WX
            if (app != nullptr) app -> Yield (true);
#endif // WX
            ::std::this_thread::yield (); } } }
#endif // NO_FRED

int examine (nitpick& nits)
{   int res = VALID_RESULT;
    if (context.cgi () || ! context.snippet ().empty ())
    {   page web (context.snippet ());
        try
        {   if (! web.invalid ()) web.examine ();
            ::std::string s (web.nits ().review ());
            web.nits ().accumulate (&overall);
            s += web.report ();
            web.cleanup ();
            if (context.test ()) context.os () -> out (START_OF_SECTION " " SNIPPET "\n");
            context.os () -> out (s); }
        catch (...)
        {   web.cleanup (); throw; }
        return res; }
    nitpick shadow, exp;
    open_corpus (nits, context.corpus ());
    paths_root& virt (paths_root::virtual_roots ());
    virt.add_root (absolute_name (canonical_name (nix_path_to_local (context.root ()))), "/");
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
            vd.emplace_back (new directory (virt.at (n), GSL_NARROW_CAST < short > (n)));
        nitpick nuts, gnats;
        knickers k (nuts, &nits);
#ifndef NO_FRED
        if (! fred.reinit (nits)) res = ERROR_STATE;
        else
#endif // NO_FRED
        try
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
#ifdef WX
                if (app != nullptr) app -> console_check ();
#endif // WX
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
                        else q.push (q_entry (&nits, vd.at (n), st_folder, vf_directory));
                    trundle (); } }
            nits.merge (nuts);
            fred.await ();
#else // NO_FRED
                        else examine (&nits, vd.at (n));
                    if (app != nullptr) app -> console_check (); } }
            nits.merge (nuts);
#endif // NO_FRED
            close_corpus (gnats);
            fileindex_save_and_close (gnats); }
        catch (const ::std::system_error& e)
        {   gnats.pick (nit_scan_failed, es_catastrophic, ec_init, "system error ", e.what ());
            res = ERROR_STATE; }
        catch (const ::std::exception& e)
        {   gnats.pick (nit_scan_failed, es_catastrophic, ec_init, "exception ", e.what ());
            res = ERROR_STATE; }
        catch (...)
        {   gnats.pick (nit_scan_failed, es_catastrophic, ec_init, "unknown exception");
            res = ERROR_STATE; }
        nits.merge (gnats); }
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> dump_nits (nits, ns_update, ns_update_head, ns_update_foot);
    macro -> dump_nits (exp, ns_export, ns_export_head, ns_export_foot);
    macro -> dump_nits (shadow, ns_shadow, ns_shadow_head, ns_shadow_foot);
    return res; };

int cycle (nitpick& nits, const int argc, char** argv)
{   int res = NOTHING_TO_DO;
    context.todo (do_booboo);
    time_balloon balloon;
    ::std::string args, msg;
    bool enfooten = false;
    vstr_t vs;
    try
    {   if (context.loop ()) cycle_start (nits);
        context.started (balloon.inflate_time ());
        if (argc > 0)
        {   VERIFY_NOT_NULL (argv, __FILE__, __LINE__);
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26481)
#endif // _MSC_VER
            for (int i = 1; i < argc; ++i)
            {   args += " ";
                args += argv [i];
                vs.push_back (argv [i]); } }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
        else if (! context.cmd ().empty ())
        {   vs = context.cmd ();
            args = enquote (vs, "\" ");
            context.gui (true);
            context.cmd ().clear (); }
        else if (context.serve ())
        {   res = server.process_and_progress ();
            switch (res)
            {   case STOP_NOW :
                case ERROR_STATE :
                    return res;
                case NOTHING_TO_DO :
                    ::std::this_thread::yield ();
                    return res;
                default :
                    vs = server.cmd ();
                    args = enquote (vs, "\" ");
                    server.clear ();
                    break; } }
        else
        {   constexpr ::std::size_t max_len = 65536;
            context.os () -> out ("\n" PROG " ");
            char* psz = new char [max_len];
            if (psz != nullptr) try
            {   *psz = 0;
                ::std::cin.getline (psz, max_len-1);
                psz [max_len-1] = 0;
                args = ::std::string (psz);
                delete [] psz; }
            catch (...)
            {   delete [] psz;
                throw; }
            psz = nullptr;
            if (args.empty ()) return STOP_NOW;
            vs = uq2 (args, UQ_TRIM | UQ_SQ | UQ_DQ | UQ_BS | UQ_REPEATQ | UQ_UNIFY, " "); }
        VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
        macro -> set (nm_context_build, BUILD_INFO);
        macro -> set (nm_run_args, args);
        context.general_info (context.cwd ().string () + "\n" + args + "\n" VERSION_STRING " [" __DATE__  " " __TIME__ "] [" + BUILD_INFO + "]\n");
        macro -> set (nm_output_build, BUILD_INFO);
        nitpick nuts;
        res = context.parameters (nuts, vs);
        if (context.verify () && ! context.sign ())
        {   ::std::cout << nuts.kwik ();
            switch (nuts.worst ())
            {   case es_undefined :
                case es_catastrophic : return CATASTROPHIC_STATE;
                case es_abhorrent :
                case es_error : return ERROR_STATE;
                default : return res; } }
        if (context.build ().empty ()) macro -> set (nm_compile_time, __DATE__ " " __TIME__);
        else macro -> set (nm_compile_time, context.build ());
        macro -> set (nm_output_account, get_account ());
        macro -> set (nm_output_description, context.output_description ());
        macro -> set (nm_output_operator, context.username ());
        if (context.output_time ().empty ()) macro -> set (nm_output_time, context.started ());
        else macro -> set (nm_output_time, context.output_time ());
        if (! macro -> is_template_loaded ()) macro -> load_template (nuts, html_default);
        macro -> set (nm_ssc_update, context.update_info ());
        if ((context.todo () == do_simple) || context.yggdrisil ())
        {   if (context.yggdrisil ()) context.os () -> console (SIMPLE_TITLE);
            else context.os () -> console (FULL_TITLE);
            if (! context.update_info ().empty ())
                context.os () -> console (context.update_info () + "\n");
            nuts.merge (nits);
            macro -> dump_nits (nuts, ns_config, ns_config_head, ns_config_foot);
            context.os () -> console (context.domsg ());
            context.os () -> aborting ();
            switch (nuts.worst ())
            {   case es_undefined :
                case es_catastrophic : return CATASTROPHIC_STATE;
                case es_abhorrent :
                case es_error : return ERROR_STATE;
                default : return res; } }
        context.apply_vcs (nuts);
        ssc_console ("\npreparing\n");
        ssc_getset ();
        if (! context.gui ()) context.os () -> out (macro -> apply (ns_doc_head));
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
            nits.accumulate (&overall); }
        const int cr = cycle_finish ();
        if (cr > res) res = cr;
        balloon.pop ();
        macro -> set (nm_time_finish, balloon.pop_time ());
        macro -> set (nm_time_duration, balloon.duration ()); }
    catch (const ::std::system_error& e)
    {   msg = "catastrophic cycle system error: ";
        msg += e.what ();
        res = CATASTROPHIC_STATE; }
    catch (const ::std::exception& e)
    {   msg = "catastrophic cycle exception: ";
        msg += e.what ();
        res = CATASTROPHIC_STATE; }
    catch (...)
    {   msg = "catastrophic cycle unknown exception";
        res = CATASTROPHIC_STATE; }
    if (! enfooten)
    {   if (! msg.empty ()) context.os () -> err (msg, "\n"); }
    else try
    {   if (! msg.empty ()) macro -> set (nm_run_catastrophe, msg);
        context.os () -> out (macro -> apply (ns_doc_foot));
        if (! msg.empty ()) context.os () -> err (msg, "\n");
        if (context.os () -> name ().empty ()) ssc_console ("finished\n");
        else ssc_console ("results written to ", context.os () -> name (), "\n"); }
    catch (...)
    {   if (msg.empty ()) msg = "catastrophic cycle footers exception\n";
        context.os () -> err (msg, "\n");
        res = CATASTROPHIC_STATE; }
    if (res >= ERROR_STATE) context.os () -> aborting ();
    return res; }

int ssc_main (int argc, char** argv)
{   int res = NOTHING_TO_DO;
#ifdef LEAK_SEEK
    _CrtMemCheckpoint (&context.ls_old_);
#endif // LEAK_SEEK
    ::std::string msg;
    PRESUME (argc > 0, __FILE__, __LINE__);
    VERIFY_NOT_NULL (argv, __FILE__, __LINE__);
    try
    {   nitpick nits;
        init (nits);
        do
        {   res = cycle (nits, argc, argv);
            if (res == STOP_NOW) { res = VALID_RESULT; break; }
            argc = 0; }
        while (context.loop ()); }
    catch (const ::std::system_error& e)
    {   msg = "catastrophic exit system error: ";
        msg += e.what ();
        res = CATASTROPHIC_STATE; }
    catch (const ::std::exception& e)
    {   msg = "catastrophic exit exception: ";
        msg += e.what ();
        res = CATASTROPHIC_STATE; }
    catch (...)
    {   msg = "catastrophic exit unknown exception";
        res = CATASTROPHIC_STATE; }
    try
    {   fred.done (); }
    catch (...)
    {   res = CATASTROPHIC_STATE; }
    try
    {   const int c = ciao ();
        if (res < c) res = c; }
    catch (...)
    {   res = CATASTROPHIC_STATE; }
#ifdef LEAK_SEEK
    _CrtMemState ls_new;
    _CrtMemState ls_diff;
    _CrtMemCheckpoint (&ls_new); //take a snapshot 
    if (_CrtMemDifference (&ls_diff, &context.ls_old_, &ls_new)) // if there is a difference
    {   OutputDebugString (L"*** _CrtMemDumpStatistics ***");
        _CrtMemDumpStatistics (&ls_diff);
        OutputDebugString (L"*** _CrtMemDumpAllObjectsSince ***");
        _CrtMemDumpAllObjectsSince (&context.ls_old_);
        OutputDebugString (L"*** _CrtDumpMemoryLeaks ***");
        _CrtDumpMemoryLeaks (); }
#endif // LEAK_SEEK
    if (! msg.empty ())
        try
        {   ::std::cerr << msg << ::std::endl; }
        catch (...)
        {   /* well and truly f***ed */ }
    return res; };

void ssc_console (const ::std::string& s)
{
#ifndef WX
    if (context.progress ())
#endif
        context.os () -> console (s); }

#ifdef WX
void ssc_getset ()
{   if (app != nullptr) app -> get_set (); }
#endif // WX

#if defined (_MSC_VER) || ! defined (WX)
int main (int argc, char** argv)
{   return ssc_main (argc, argv); }
#endif // _MSC_VER
