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
#include "utility/common.h"
#include "main/context.h"
#include "webpage/external.h"
#include "webpage/page.h"
#include "webpage/directory.h"
#include "url/url.h"
#include "webpage/crosslink.h"

external directory::external_;

directory::directory (const ::std::string& name, const fileindex_t ndx, directory* mummy, const ::std::string& site, const bool check)
    : name_ (name), offsite_ (false), mummy_ (mummy), ndx_ (ndx)
{   assert (mummy_ != nullptr);
    if (check) scan (site); }

directory::directory (const path_root_ptr& root)
    : name_ (root -> get_site_path ()), offsite_ (false), mummy_ (nullptr), root_ (root)
{   ndx_ = get_fileindex (root -> get_disk_path ()); }

directory::directory (const ::std::string& name, const bool offsite)
    : name_ (name), offsite_ (offsite), mummy_ (nullptr)
{   if (! offsite) ndx_ = insert_disk_path (get_disk_path (), 0, this); }

void directory::swap (directory& d) NOEXCEPT
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
    bool sep = separate_first (item, lhs, rhs, '/');
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
    assert (mummy_ != nullptr);
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
    bool sep = separate_first (item, lhs, rhs, '/');
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

bool directory::scan (const ::std::string& site)
{   assert (! offsite_);
    for (::boost::filesystem::directory_entry& x : ::boost::filesystem::directory_iterator (get_disk_path ()))
        if (! add_to_content (x, site)) return false;
    return true; }

bool directory::add_to_content (::boost::filesystem::directory_entry& i, const ::std::string& site)
{   ::boost::filesystem::path q (i.path ());
    fileindex_t ndx = insert_disk_path (q, 0, this);
    ::std::string p;
    if (site.empty ()) p = get_site_path ();
    else p = site;
    ::std::string f (local_path_to_nix (q.filename ().string ()));
    p = join_site_paths (p, f);
    add_site_path (p, ndx);
    if (is_regular_file (q))
        return content_.insert (value_t (f, nullptr)).second;
    if (is_directory (q))
        return content_.insert (value_t (f, self_ptr (new directory (f, ndx, this, p)))).second;
    return false; }

void directory::examine ()
{   assert (! offsite_);
    for (auto i : content_)
        if (i.second != nullptr)
            i.second -> examine ();
        else if (is_webpage (i.first, context.extensions ()))
        {   ::std::ostringstream ss;
            ::boost::filesystem::path p (get_disk_path ());
            ::std::string sp (get_site_path () + i.first);
            p /= i.first;
            fileindex_t ndx (get_fileindex (p));
            if (! get_flag (ndx, FX_SCANNED))
            {   context.filename (sp);
                try
                {   ::std::string content (read_text_file (p));
                    if (! content.empty ())
                    {   e_charcode encoding = bom_to_encoding (get_byte_order (content));
                        if (encoding == cc_fkd) ss << "Unsupported byte order (ASCII, ANSI, UTF-8 or UTF-16, please)\n";
                        else
                        {   page web (i.first, content, ndx, this, encoding);
                            if (! web.invalid ())
                            {   web.examine (*this);
                                web.mf_write (p);
                                web.lynx ();
                                ss << web.report (); }
                            ss << web.nits ().review (); } } }
                catch (...)
                {   if (context.tell (e_error)) ss << "Cannot parse " << context.filename () << "\n"; }
                if (! ss.str ().empty ()) context.out () << "\n\n*** " << local_path_to_nix (p.string ()) << "\n" << ss.str ();
                else if (context.tell (e_comment)) context.out () << "\n\n*** " << local_path_to_nix (p.string ()) << "\n";
                context.css ().post_process ();
                context.out () << ::std::flush;
                set_flag (ndx, FX_SCANNED); } } }

::boost::filesystem::path directory::get_disk_path (nitpick& nits, const url& u) const
{   ::std::string p (join_site_paths (u.path (), u.filename ()));
    return get_disk_path (nits, p); }

bool directory::unguarded_verify_url (nitpick& nits, const html_version& v, const url& u, const attribute_bitset& state, const vit_t& itemtypes) const
{   if (u.empty ()) return false; // self?
    if (u.has_protocol ())
    {   if (u.get_scheme () != pt_rfc3986) return true;
        if (u.has_domain () && ! is_one_of (u.domain (), context.site ()))
            return verify_external (nits, v, u, state, itemtypes); }
    ::boost::filesystem::path p (get_disk_path (nits, u));
    if (p.empty ())
        if (u.has_query () || u.is_simple_id ())
            return true;
    fileindex_t ndx (get_fileindex (p));
    if (get_flag (ndx, (FX_SCANNED | FX_EXISTS))) return true;
    if (! get_flag (ndx, FX_TESTED))
    {   set_flag (ndx, FX_TESTED);
        if (::boost::filesystem::exists (p))
        {   bool vrai = ::boost::filesystem::is_regular_file (p);
            if (! vrai)
                if (::boost::filesystem::is_directory (p))
                {   p /= context.index ();
                    vrai = ::boost::filesystem::is_regular_file (p); }
            if (vrai)
            {   set_flag (ndx, FX_EXISTS);
                return true; } } }
    nits.pick (nit_url_not_found, es_error, ec_url, quote (u.original ()), " not found");
    return false; }

uint64_t directory::url_size (nitpick& nits, const url& u) const
{   if (! u.empty () && ! u.has_protocol ()) try
    {   return ::boost::filesystem::file_size (get_disk_path (nits, u)); }
    catch (...) { }
    return 0; }

::std::time_t directory::url_last_write_time (nitpick& nits, const url& u) const
{   if (! u.empty () && ! u.has_protocol ()) try
    {   return ::boost::filesystem::last_write_time (get_disk_path (nits, u)); }
    catch (...) { }
    return 0; }

::std::string directory::load_url (nitpick& nits, const url& u) const
{   try
    {   if (! u.empty ())
            if (! u.has_protocol ())
                return read_text_file (get_disk_path (nits, u));
            else if (u.get_scheme () == pt_rfc3986)
                if (u.has_domain () && is_one_of (u.domain (), context.site ()))
                    return read_text_file (get_disk_path (nits, u));
                else return external_.load (u); }
    catch (...) { }
    return ::std::string (); }

bool directory::verify_url (nitpick& nits, const html_version& v, const url& u, const attribute_bitset& flags, const vit_t& itemtypes) const
{   if (! context.links ()) return true;
    if (context.checking_urls ()) return true;
    bool res = false;
    try
    {   context.checking_urls (true);
        res = unguarded_verify_url (nits, v, u, flags, itemtypes);
        context.checking_urls (false); }
    catch (...)
    {   nits.pick (nit_virtual_exception, es_catastrophic, ec_directory, "verify_url ", quote (u.original ()));
        context.checking_urls (false);
        throw;  }
    return res; }

bool directory::verify_external (nitpick& nits, const html_version& v, const url& u, const attribute_bitset& flags, const vit_t& itemtypes) const
{   if (! context.external ()) return true;
    bool res = external_.verify (nits, v, u, flags, itemtypes);
    if (res) return true;
    if (context.code () < 300) return true;
    if (context.repeated () && context.once ()) return false;
    if (! context.tell (e_error)) return false;
    switch (context.code ())
    {   case 301 :
        case 308 :
            nits.pick (nit_308, es_info, ec_link, quote (u.original ()), " has moved (", context.code (), ")");
            break;
        case 400 :
            nits.pick (nit_400, es_error, ec_link, quote (u.original ()), " is a malformed or bad link (", context.code (), ")");
            break;
        case 401 :
            nits.pick (nit_401, es_warning, ec_link, quote (u.original ()), " is unauthorised (", context.code (), ")");
            break;
        case 403 :
            nits.pick (nit_403, es_warning, ec_link, quote (u.original ()), " is forbidden (", context.code (), ")");
            break;
        case 404 :
        case 410 :
            nits.pick (nit_404, es_error, ec_link, quote (u.original ()), " is broken (", context.code (), ")");
            break;
        case 407 :
            nits.pick (nit_407, es_info, ec_link, quote (u.original ()), " is blocked by a proxy (", context.code (), ")");
            break;
        case 408 :
            nits.pick (nit_408, es_comment, ec_link, quote (u.original ()), " has timed out (", context.code (), ")");
            break;
        case 451 :
            nits.pick (nit_451, es_warning, ec_link, quote (u.original ()), " is censored (", context.code (), ")");
            break;
        default :
            nits.pick (nit_link, es_warning, ec_link, quote (u.original ()), " is unavailable (", context.code (), ")");
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
        p -> mummy_ = this;
        e = content_.find (lhs); }
    else if (e -> second == nullptr) return false; // ordinary file
    if (! rhs.empty ()) return e -> second -> integrate_virtual (rhs, disk, p);
    if (e -> second -> root_.get () == nullptr)
        e -> second -> root_ = disk;
    return true; }

::std::size_t integrate_virtuals (paths_root& virt, vd_t& vd)
{   assert (virt.size () == vd.size ());
    for (::std::size_t n = 1; n < virt.size (); ++n)
        if (! vd.at (0) -> integrate_virtual (virt.at (n) -> get_site_path (), virt.at (n), vd.at (n)))
            return n;
    return 0; }

bool is_webpage (const ::std::string& name, const vstr_t& extensions)
{   ::std::string ext (::boost::filesystem::path (name).extension ().string ());
    if (ext.empty ()) return false;
    return is_one_of (ext.substr (1), extensions); }
