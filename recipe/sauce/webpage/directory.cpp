/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "utility/common.h"
#include "utility/filesystem.h"
#include "main/context.h"
#include "webpage/external.h"
#include "webpage/page.h"
#include "webpage/directory.h"
#include "url/url.h"
#include "url/url_sanitise.h"
#include "webpage/crosslink.h"
#include "schema/jsonld.h"
#include "icu/converter.h"
#include "webpage/q.h"
#include "coop/kew.h"
#include "coop/knickers.h"

external directory::external_;

directory::directory (nitpick* ticks, const ::std::string& name, const fileindex_t ndx, directory* mummy, const ::std::string& site, const bool check)
    : name_ (name), offsite_ (false), mummy_ (mummy), ndx_ (ndx)
{   PRESUME (ndx_ != nullfileindex, __FILE__, __LINE__);
    PRESUME (mummy_ != nullptr, __FILE__, __LINE__);
    PRESUME (name_ == get_name (ndx), __FILE__, __LINE__);
    if (check) scan (ticks, site); }

directory::directory (const path_root_ptr& root, const short v)
    : name_ (root -> get_site_path ()), offsite_ (false), mummy_ (nullptr), root_ (root)
{   VERIFY_NOT_NULL (root, __FILE__, __LINE__);
    ndx_ = insert_root_path (root -> get_disk_path (), v); }

directory::directory (const fileindex_t parent_ndx, const ::std::string& name, const bool offsite)
    : name_ (name), offsite_ (offsite), mummy_ (nullptr)
{   if (! offsite) ndx_ = insert_directory_path (parent_ndx, get_disk_path ()); }

void directory::swap (directory& d) noexcept
{   name_.swap (d.name_);
    content_.swap (d.content_);
    ::std::swap (offsite_, d.offsite_);
    ::std::swap (mummy_, d.mummy_);
    ::std::swap (ndx_, d.ndx_);
    ::std::swap (root_, d.root_); }

::std::string directory::get_site_path () const
{   if (mummy_ == nullptr) return "/";
    ::std::string res = mummy_ -> get_site_path ();
    res += name_;
    res += "/";
    return res; }

::std::string directory::internal_get_site_path (nitpick& nits, const ::std::string& item) const
{   if (item.empty ())
    {   auto i = content_.find (context.index ());
        if (i == content_.end ()) return get_site_path ();
        return join_site_paths (get_site_path (), context.index ()); }
    if (item.at (0) == '/')
    {   if (mummy_ != nullptr) return mummy_ -> internal_get_site_path (nits, item);
        return internal_get_site_path (nits, item.substr (1)); }
    ::std::string lhs, rhs;
    const bool sep = separate_first (item, lhs, rhs, '/');
    if (lhs == ".") return internal_get_site_path (nits, rhs);
    if (lhs == "..")
    {   if (mummy_ != nullptr) return mummy_ -> internal_get_site_path (nits, rhs);
        nits.pick (nit_attempted_escape, es_error, ec_directory, "blocking access to root's parent folder");
        return internal_get_site_path (nits, rhs); }
    auto i = content_.find (lhs);
    if (i != content_.end ())
        if (i -> second != nullptr) return i -> second -> internal_get_site_path (nits, rhs);
    if (sep) nits.pick (nit_no_such_folder, es_error, ec_directory, quote (lhs), " is no child of ", quote (name_));
    return join_site_paths (get_site_path (), item); }

::std::string directory::get_site_path (nitpick& nits, const ::std::string& item) const
{   ::std::string res = internal_get_site_path (nits, item);
    return res; }

::boost::filesystem::path directory::get_disk_path () const
{   if (root_.get () != nullptr)
        return root_ -> get_disk_path ();
    VERIFY_NOT_NULL (mummy_, __FILE__, __LINE__);
    return mummy_ -> get_disk_path () / name_; }

void directory::internal_get_disk_path (const ::std::string& item, ::boost::filesystem::path& res) const
{   if (item.empty ()) { res = get_disk_path (); return; }
    if (item.at (0) == '/')
    {   if (mummy_ != nullptr) mummy_ -> internal_get_disk_path (item, res);
        else internal_get_disk_path (item.substr (1), res);
        return; }
    ::std::string lhs, rhs;
    if (root_.get () == nullptr) res /= name_;
    else res = root_ -> get_disk_path ();
    const bool sep = separate_first (item, lhs, rhs, '/');
    auto i = content_.find (lhs);
    if (i == content_.end ()) res /= nix_path_to_local (item);
    else if (i -> second != nullptr) i -> second -> internal_get_disk_path (rhs, res);
    else if (sep) res /= nix_path_to_local (item);
    else res /= lhs;
    return; }

::boost::filesystem::path directory::get_disk_path (nitpick& nits, const ::std::string& item) const
{   ::boost::filesystem::path res;
    internal_get_disk_path (get_site_path (nits, item), res);
    return res; }

::boost::filesystem::path directory::get_disk_path (nitpick& nits, const url& u) const
{   ::std::string p (join_site_paths (u.path (), u.filename ()));
    return get_disk_path (nits, p); }

::boost::filesystem::path directory::get_shadow_path () const
{   if (root_.get () != nullptr)
        return root_ -> shadow_root ();
    VERIFY_NOT_NULL (mummy_, __FILE__, __LINE__);
    return mummy_ -> get_shadow_path () / name_; }

::boost::filesystem::path directory::get_export_path () const
{   if (root_.get () != nullptr)
        return root_ -> get_export ();
    VERIFY_NOT_NULL (mummy_, __FILE__, __LINE__);
    return mummy_ -> get_export_path () / name_; }

void directory::internal_get_shadow_path (const ::std::string& item, ::boost::filesystem::path& res) const
{   if (item.empty ()) { res = get_shadow_path (); return; }
    if (item.at (0) == '/')
    {   if (mummy_ != nullptr) mummy_ -> internal_get_shadow_path (item, res);
        else internal_get_shadow_path (item.substr (1), res);
        return; }
    ::std::string lhs, rhs;
    if (root_.get () == nullptr) res /= name_;
    else res = root_ -> get_disk_path ();
    const bool sep = separate_first (item, lhs, rhs, '/');
    auto i = content_.find (lhs);
    if (i == content_.end ()) res /= nix_path_to_local (item);
    else if (i -> second != nullptr) i -> second -> internal_get_shadow_path (rhs, res);
    else if (sep) res /= nix_path_to_local (item);
    else res /= lhs;
    return; }

void directory::internal_get_export_path (const ::std::string& item, ::boost::filesystem::path& res) const
{   if (item.empty ()) { res = get_export_path (); return; }
    if (item.at (0) == '/')
    {   if (mummy_ != nullptr) mummy_ -> internal_get_export_path (item, res);
        else internal_get_export_path (item.substr (1), res);
        return; }
    ::std::string lhs, rhs;
    if (root_.get () == nullptr) res /= name_;
    else res = root_ -> get_disk_path ();
    const bool sep = separate_first (item, lhs, rhs, '/');
    auto i = content_.find (lhs);
    if (i == content_.end ()) res /= nix_path_to_local (item);
    else if (i -> second != nullptr) i -> second -> internal_get_export_path (rhs, res);
    else if (sep) res /= nix_path_to_local (item);
    else res /= lhs;
    return; }

::boost::filesystem::path directory::get_export_path (nitpick& nits, const ::std::string& item) const
{   ::boost::filesystem::path res;
    internal_get_export_path (get_site_path (nits, item), res);
    return res; }

::boost::filesystem::path directory::get_export_path (nitpick& nits, const url& u) const
{   ::std::string p (join_site_paths (u.path (), u.filename ()));
    return get_export_path (nits, p); }

bool directory::scan (nitpick* ticks, const ::std::string& site)
{   PRESUME (! offsite_, __FILE__, __LINE__);
    const ::boost::filesystem::path disk (get_disk_path ());
    for (const ::boost::filesystem::directory_entry& x : ::boost::filesystem::directory_iterator (disk))
        if (! context.excluded (*ticks, x.path ()))
            add_to_content (ticks, x, site);
    return true; }

bool directory::add_to_content (nitpick* ticks, const ::boost::filesystem::directory_entry& i, const ::std::string& site)
{   VERIFY_NOT_NULL (ticks, __FILE__, __LINE__);
    ::boost::filesystem::path qp (i.path ());
    fileindex_t ndx = nullfileindex;
    if (is_folder (qp)) ndx = insert_directory_path (ndx_, qp);
    else ndx = insert_disk_path (ndx_, qp, 0);
    ::std::string p;
    if (site.empty ()) p = get_site_path ();
    else p = site;
    ::std::string f (local_path_to_nix (qp.filename ().string ()));
    p = join_site_paths (p, f);
    if (is_regular_file (qp))
    {   if (context.dodedu ())
            get_crc (*ticks, ndx);
        return content_.insert (value_t (f, nullptr)).second; }
    if (is_directory (qp))
    {   dir_ptr dp (new directory (ticks, f, ndx, this, p, false)); 
        if (content_.insert (value_t (f, dp)).second)
#ifndef NO_FRED
        {   q.push (q_entry (ticks, dp, st_scan));
            return true; } }
#else // NO_FRED
        return dp -> scan (ticks, p); }
#endif // NO_FRED
    set_flag (ndx, FX_BORKED);
    nitpick nits;
    knickers k (nits, ticks);
    nits.pick (nit_cannot_scan, es_warning, ec_directory, "Cannot scan ", quote (p));
    return false; }

void directory::examine_page (nitpick* ticks, const ::std::string& file) const
{   nitpick nits;
    knickers k (nits, ticks);
    if (! is_webpage (file, context.extensions ()))
    {   PRESUME (context.shadow_files (), __FILE__, __LINE__);
        shadow_file (nits, file); }
    else
    {   ::std::ostringstream ss;
        const ::boost::filesystem::path p (get_disk_path () / file);
        const fileindex_t ndx (get_fileindex (ndx_, p));
        if (! get_any_flag (ndx, FX_SCANNED))
        {   ::std::string sp (get_site_path () + file);
            if (avoid_update (file, true))
            {   if (context.tell (es_comment)) nits.pick (nit_shadow_unnecessary, es_comment, ec_directory, quote (p.string ()), " is up-to-date"); }
            else
            {   mmac_t mac;
                mac.emplace (nm_page_name, file);
                mac.emplace (nm_page_disk_path, p.string ());
                mac.emplace (nm_page_site_path, sp);
                try
                {   ::std::string content (read_text_file (nits, p));
                    const bool jld = is_one_of (::boost::filesystem::path (p).extension ().string ().substr (1), context.jsonld_extension ());
                    if (jld) parse_json_ld (nits, context.html_ver (), content);
                    ss << nits.review (mac);
                    if (! jld)
                    {   page web (file, last_write (ndx), content, ndx, this);
                        try
                        {   if (web.invalid ()) ss << web.nits ().review (mac);
                            else
                            {   web.examine ();
                                web.verify_locale (p);
                                web.mf_write (p);
                                web.lynx ();
                                web.css ().accumulate ();
                                if (context.shadow_pages ()) web.shadow (nits, get_shadow_path () / file);
                                ss << web.nits ().review (mac);
                                ss << web.report (); }
                            web.nits ().accumulate (nits);
                            web.cleanup (); }
                        catch (...)
                        {   web.cleanup (); throw; } } }
                catch (const ::std::system_error& e)
                {   if (context.tell (es_error)) mac.emplace (nm_page_error, ::std::string ("System error ") + e.what () + " when parsing " + sp); }
                catch (const ::std::exception& e)
                {   if (context.tell (es_error)) mac.emplace (nm_page_error, ::std::string ("Exception ") + e.what () + " when parsing " + sp); }
                catch (...)
                {   if (context.tell (es_error)) mac.emplace (nm_page_error, ::std::string ("Unknown exception when parsing ") + sp); }
                if (! ss.str ().empty ())
                {   VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
                    outstr.out (macro -> apply (ns_page_head, mac), ss.str (), macro -> apply (ns_page_foot, mac)); }
                k.accumulate_and_clear (); }
            set_flag (ndx, FX_SCANNED); } } }

void directory::examine (nitpick* ticks, dir_ptr me_me_me) const
{   PRESUME (! offsite_, __FILE__, __LINE__);
    nitpick nits;
    knickers k (nits, ticks);
    if (context.shadow_any ()) shadow_folder (nits);
    sstr_t shadowed;
    for (auto i : content_)
        if (i.second != nullptr) 
#ifndef NO_FRED
            q.push (q_entry (ticks, i.second, st_folder));
#else // NO_FRED
            examine (ticks, i.second);
#endif // NO_FRED
        else
        {   shadowed.emplace ((get_shadow_path () / i.first).string ());
            if (context.shadow_files () || is_webpage (i.first, context.extensions ()))
#ifndef NO_FRED
                q.push (q_entry (ticks, me_me_me, st_file, i.first)); }
#else // NO_FRED
                examine_page (ticks, i.first)); }
#endif // NO_FRED
    ::std::this_thread::yield ();
    if (context.shadow_files ())
    {   sstr_t delete_me;
#ifdef NO_DIROPTS
        ::boost::filesystem::directory_iterator i (get_shadow_path ());
#else // NO_DIROPTS
        ::boost::filesystem::directory_iterator i (get_shadow_path (), ::boost::filesystem::directory_options::skip_permission_denied);
#endif // NO_DIROPTS
        for (   i = ::boost::filesystem::begin (i);
                i != ::boost::filesystem::end (i);
                ++i)
            if (shadowed.find (i -> path ().string ()) == shadowed.cend ())
                delete_me.emplace (i -> path ().string ());
        for (auto z : delete_me)
        {   if (context.tell (es_comment)) nits.pick (nit_shadow_delete, es_comment, ec_shadow, "removing ", z);
            delete_file (z); } } }

uint64_t directory::url_size (nitpick& nits, const url& u) const
{   if (! u.empty () && ! u.has_protocol ()) try
    {   return get_file_size (get_disk_path (nits, u)); }
    catch (...) { }
    return 0; }

::std::time_t directory::url_last_write_time (nitpick& nits, const url& u) const
{   if (! u.empty () && ! u.has_protocol ()) try
    {   return get_last_write_time (get_disk_path (nits, u)); }
    catch (...) { }
    return 0; }

::std::string directory::load_url (nitpick& nits, const url& u, ::std::time_t* updated) const
{   try
    {   if (! u.empty ())
            if (! u.has_protocol ())
            {   ::boost::filesystem::path p (get_disk_path (nits, u));
                if (updated != nullptr)
                {   ::std::time_t when = get_last_write_time (p);
                    if (when > *updated) *updated = when; }
                return read_text_file (nits, p); }
            else if (u.get_scheme () == pt_rfc3986)
                if (u.has_domain () && is_one_of (u.domain (), context.site ()))
                {   ::boost::filesystem::path p (get_disk_path (nits, u));
                    if (updated != nullptr)
                    {   ::std::time_t when = get_last_write_time (p);
                        if (when > *updated) *updated = when; }
                    return read_text_file (nits, p); }
                else
                {   if (updated != nullptr) time (updated);
                    return external_.load (nits, u); } }
    catch (...) { }
    return ::std::string (); }

void directory::maintain_fileindex (nitpick& , const ::boost::filesystem::path& p, const ::std::string& , fileindex_t ndx, const fileindex_flags flags) const
{   if (ndx == nullfileindex)
        ndx = insert_disk_path (ndx_, p, flags);
    else set_flag (ndx, flags); }

bool directory::verify_local (nitpick& nits, const html_version& , const url& u, const bool fancy) const
{   ::boost::filesystem::path p (get_disk_path (nits, u));
    if (context.tell (es_detail)) nits.pick (nit_detail, es_detail, ec_ssi, "seeking ", p.string ());
    if (p.empty ())
        if (u.has_query () || u.is_simple_id ())
            return fancy;
    dear d (lox_dear);
    const fileindex_t ndx (get_fileindex (ndx_, p));
    if (ndx != nullfileindex)
        if (get_any_flag (ndx, FX_BORKED)) return false;
        else if ((! fancy) && get_any_flag (ndx, FX_DIR)) return false;
        else if (get_any_flag (ndx, FX_TESTED))
            return (get_any_flag (ndx, (FX_SCANNED | FX_EXISTS)));
    if (is_file (p))
    {   maintain_fileindex (nits, p, u.absolute (), ndx, FX_TESTED | FX_EXISTS);
        return true; }
    if (fancy)
        if (is_folder (p))
        {   ::boost::filesystem::path p2 = p / context.index ();
            if (is_file (p2))
            {   maintain_fileindex (nits, p, u.absolute (), ndx, FX_TESTED | FX_EXISTS | FX_DIR);
                maintain_fileindex (nits, p2, sanitise (u.absolute () + "/" + context.index ()), ndx, FX_TESTED | FX_EXISTS);
                return true; }
            maintain_fileindex (nits, p, u.absolute (), ndx, FX_TESTED | FX_EXISTS | FX_DIR);
            maintain_fileindex (nits, p2, sanitise (u.absolute () + "/" + context.index ()), ndx, FX_TESTED);
            return false; }
    maintain_fileindex (nits, p, u.absolute (), ndx, FX_TESTED);
    return false; }

bool directory::verify_url (nitpick& nits, const html_version& v, const url& u, const bool fancy) const
{   if (! context.links ()) return true;
    if (u.is_self ()) return fancy;
    if (u.empty ()) return false; // self?
    if (u.has_protocol ())
    {   if (u.get_scheme () != pt_rfc3986) return true;
        if (u.has_domain () && ! is_one_of (u.domain (), context.site ()))
            return verify_external (nits, v, u); }
    if (verify_local (nits, v, u, fancy)) return true;
    nits.pick (nit_url_not_found, es_error, ec_url, quote (u.original ()), " not found");
    return false; }

bool directory::verify_external (nitpick& nits, const html_version& v, const url& u) const
{   int code = 0;
    bool repeated = false;
    if (external_.verify (nits, v, u, code, repeated)) return true;
    if (code < 300) return true;
    if (repeated && context.once ()) return false;
    if (! context.tell (es_error)) return false;
    switch (code)
    {   case 301 :
        case 308 :
            nits.pick (nit_308, es_info, ec_link, quote (u.original ()), " has moved (", code, ")");
            break;
        case 400 :
            nits.pick (nit_400, es_error, ec_link, quote (u.original ()), " is a malformed or bad link (", code, ")");
            break;
        case 401 :
            nits.pick (nit_401, es_warning, ec_link, quote (u.original ()), " is unauthorised (", code, ")");
            break;
        case 403 :
            nits.pick (nit_403, es_warning, ec_link, quote (u.original ()), " is forbidden (", code, ")");
            break;
        case 404 :
        case 410 :
            nits.pick (nit_404, es_error, ec_link, quote (u.original ()), " is broken (", code, ")");
            break;
        case 407 :
            nits.pick (nit_407, es_info, ec_link, quote (u.original ()), " is blocked by a proxy (", code, ")");
            break;
        case 408 :
            nits.pick (nit_408, es_comment, ec_link, quote (u.original ()), " has timed out (", code, ")");
            break;
        case 451 :
            nits.pick (nit_451, es_warning, ec_link, quote (u.original ()), " is censored (", code, ")");
            break;
        default :
            nits.pick (nit_link, es_warning, ec_link, quote (u.original ()), " is unavailable (", code, ")");
            break; }
    return false;}

bool directory::integrate_virtual (const ::std::string& site, path_root_ptr& disk, dir_ptr p)
{   if (site.empty ()) return false;
    if (site.at (0) == '/') return integrate_virtual (site.substr (1), disk, p);
    ::std::string lhs, rhs;
    if (! separate_first (site, lhs, rhs, '/')) lhs = site;
    if (lhs == ".") return integrate_virtual (rhs, disk, p);
    if (lhs == "..")
    {   if (mummy_ != nullptr) return mummy_ -> integrate_virtual (rhs, disk, p);
        return false; }
    auto e = content_.find (lhs);
    if (e == content_.end ())
    {   content_.insert (value_t (lhs, p));
        VERIFY_NOT_NULL (p, __FILE__, __LINE__);
        p -> mummy_ = this;
        e = content_.find (lhs); }
    else if (e -> second == nullptr) return false; // ordinary file
    VERIFY_NOT_NULL (e -> second, __FILE__, __LINE__);
    if (! rhs.empty ()) return e -> second -> integrate_virtual (rhs, disk, p);
    if (e -> second -> root_.get () == nullptr)
        e -> second -> root_ = disk;
    return true; }

::std::size_t integrate_virtuals (paths_root& virt, vd_t& vd)
{   PRESUME (virt.size () == vd.size (), __FILE__, __LINE__);
    for (::std::size_t n = 1; n < virt.size (); ++n)
    {   VERIFY_NOT_NULL (vd.at (0), __FILE__, __LINE__);
        VERIFY_NOT_NULL (virt.at (n), __FILE__, __LINE__);
        if (! vd.at (0) -> integrate_virtual (virt.at (n) -> get_site_path (), virt.at (n), vd.at (n)))
            return n; }
    return 0; }

bool is_webpage (const ::std::string& name, const vstr_t& extensions)
{   ::std::string ext (::boost::filesystem::path (name).extension ().string ());
    if (ext.empty ()) return false;
    return is_one_of (ext.substr (1), extensions); }

bool directory::shadow_folder (nitpick& nits) const
{   PRESUME (context.shadow_any (), __FILE__, __LINE__);
    ::boost::filesystem::path moi (get_shadow_path ());
    if (! file_exists (moi))
        if (! make_directories (moi))
        {   nits.pick (nit_create_folder, es_catastrophic, ec_shadow, "cannot create ", moi.string ());
            return false; }
    return true; }

bool directory::shadow_file (nitpick& nits, const ::std::string& name) const
{   PRESUME (context.shadow_files (), __FILE__, __LINE__);
    ::boost::filesystem::path original (get_disk_path () / name);
    if (contains (context.shadow_ignore (), original.extension ().string ()))
    {   nits.pick (nit_shadow_failed, es_debug, ec_shadow, "not shadowing ", original);
        return true;  }
    const e_copy todo = context.copy ();
    PRESUME (todo > c_none, __FILE__, __LINE__);
    if (todo <= c_html) return true;
    const fileindex_t ndx = get_fileindex (original);
    if (ndx == nullfileindex)
    {   nits.pick (nit_internal_file_error, es_catastrophic, ec_shadow, "internal data error: lost information about ", original.string ());
        return false; }
    if (get_any_flag (ndx, FX_BORKED))
    {   nits.pick (nit_shadow_failed, es_warning, ec_shadow, "cannot shadow borked file ", original.string ());
        return true; }
    ::boost::filesystem::path imitation (get_shadow_path () / name);
    if (file_exists (imitation))
        if (avoid_update (original, imitation, false))
        {   nits.pick (nit_shadow_unnecessary, es_comment, ec_directory, quote (original.string ()), " is up-to-date");
            return true; }
    bool changed = false;
    ::boost::filesystem::file_status stat;
#ifndef NOLYNX
    if (is_file_linked (imitation))
    {   ::boost::filesystem::path target = resolve_link (imitation);
        if (target == original) return true;
        if (! delete_file (imitation))
        {   nits.pick (nit_shadow_failed, es_error, ec_shadow, "cannot unlink ", imitation.string ());
            return false; } }
#endif // NOLYNX
    if (file_exists (imitation))
    {   if (context.shadow_changed ())
        {   const uintmax_t origsize = get_size (ndx);
            const uintmax_t copysize = get_file_size (imitation);
            if (origsize == copysize)
            {   const ::std::time_t origwrite = last_write (ndx);
                const ::std::time_t copywrite = get_last_write_time (imitation);
                if ((copywrite >= origwrite) && context.update ()) return true; } }
        if (todo >= c_copy)
        {   stat = file_data (imitation);
#ifndef NO_PERMS
            if ((stat.permissions () & ::boost::filesystem::perms::owner_write) == 0)
            {   file_permissions (imitation, ::boost::filesystem::perms::owner_write | ::boost::filesystem::perms::add_perms);
                changed = true; }
#endif // NO_PERMS
        }
        else if (! delete_file (imitation))
        {   nits.pick (nit_shadow_failed, es_error, ec_shadow, "cannot remove previous ", imitation.string ());
            return true; } }
    switch (todo)
    {   case c_none :
        case c_html :
        case c_rpt :        GRACEFUL_CRASH (__FILE__, __LINE__);
                            UNBREAKABLE;
        case c_hard :       if (make_hard_link (original, imitation))
                                nits.pick (nit_shadow_link, es_debug, ec_shadow, "hard linked ", original, " and ", imitation);
                            else nits.pick (nit_shadow_link, es_catastrophic, ec_shadow, "cannot make hard link between ", original, " and ", imitation);
                            break;
        case c_soft :       if (make_link (original, imitation))
                                nits.pick (nit_shadow_link, es_debug, ec_shadow, "soft linked ", original, " and ", imitation);
                            else nits.pick (nit_shadow_link, es_catastrophic, ec_shadow, "cannot make soft link between ", original, " and ", imitation);
                            break;
        case c_copy :       if (duplicate_file (original, imitation, BOOST_COPY_OPTION::BOOST_OVERWRITE))
                                nits.pick (nit_shadow_copy, es_debug, ec_shadow, "copied ", original, " to ", imitation);
                            else nits.pick (nit_shadow_copy, es_catastrophic, ec_shadow, "cannot copy ", original, " to ", imitation);
                            break;
        case c_deduplicate :if (isdu (ndx)) break;
                            if (duplicate_file (original, imitation, BOOST_COPY_OPTION::BOOST_OVERWRITE))
                                nits.pick (nit_shadow_copy, es_debug, ec_shadow, "copied ", original, " to ", imitation);
                            else nits.pick (nit_shadow_copy, es_catastrophic, ec_shadow, "cannot copy ", original, " to ", imitation);
                            break; }
#ifndef NO_PERMS
    if (changed)
        if (! file_permissions (imitation, ::boost::filesystem::perms::owner_write | ::boost::filesystem::perms::remove_perms))
        {   nits.pick (nit_shadow_failed, es_error, ec_shadow, "cannot upright ", imitation.string ());
            return false; }
#endif // NO_PERMS
return true; }

bool directory::avoid_update (const ::boost::filesystem::path& original, const ::boost::filesystem::path& shadow, const bool page) const
{   if (! context.update ()) return false;
    ::std::time_t ot = 0, st = 0;
    if (! file_exists (original) || ! file_exists (shadow)) return false;
    const fileindex_t ndx (get_fileindex (original));
    if (ndx == nullfileindex) return false;
    ot = last_write (ndx);
    if (ot == 0) return false;
    st = get_last_write_time (shadow);
    if (ot > st) return false;
    if (! page) return true;
    return ! needs_update (ndx, ot); }

bool directory::avoid_update (const ::std::string& name, const bool page) const
{   if (! context.update ()) return false;
    ::boost::filesystem::path original (get_disk_path ());
    ::boost::filesystem::path imitation (get_shadow_path ());
    original /= name;
    imitation /= name;
    return avoid_update (original, imitation, page); }
