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
#include "utility/quote.h"
#include "webpage/fileindex.h"
#include "webpage/directory.h"

#define PERSIST_SIZE 0
#define PERSIST_LAST_WRITE 1
#define PERSIST_FLAGS 2
#define PERSIST_CRC 3
#define PERSIST_PATH 4
#define PERSIST_ARG_COUNT 5

struct index_t
{   ::boost::filesystem::path disk_path_;
    ::std::string site_path_;
    fileindex_flags flags_ = 0;
    directory* pd_ = nullptr;
    uintmax_t size_ = 0;
    crc_t crc_ = crc_initrem;
    fileindex_t dedu_ = nullfileindex;
    ::std::time_t last_write_;
    index_t (const ::boost::filesystem::path& p, const fileindex_flags flags, directory* d, const uintmax_t size, const ::std::time_t& last_write)
        :   disk_path_ (p), flags_ (flags), pd_ (d), size_ (size), last_write_ (last_write) { }
    ::std::string persist () const
    {   ::std::string res;
        res = ::boost::lexical_cast < ::std::string > (size_);  // ensure this write order matches #defines above
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (last_write_);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (flags_);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (crc_);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (disk_path_);
        return res; }
    void reload (const uintmax_t size, const ::std::time_t last_write, const crc_t crc)
    {   if ((size == size_) && (last_write_ == last_write))
        {   crc_ = crc; flags_ |= FX_CRC; } } };

typedef ::std::vector < index_t > vx_t;
typedef ssc_map < ::std::string, fileindex_t > mxp_t;
typedef ::std::map < crc_t, fileindex_t > mcrc_t;

vx_t vx;
mxp_t site_x, disk_x;  // note ::boost::filesystem::path and ::std::map are not pals
mcrc_t mcrc;

#if defined (UNIX)
::std::string local_path_to_nix (const ::std::string& s) { return s; }
::std::string nix_path_to_local (const ::std::string& s) { return s; }
#else // presuming if not unix then windows
::std::string local_path_to_nix (const ::std::string& s)
{   ::std::string res (s);
    ::boost::replace_all (res, "\\", "/");
    if ((res.length () >= 2) && (res.at (1) == ':')) res = res.substr (2);
    return res; }

::std::string nix_path_to_local (const ::std::string& s)
{   if (s.empty ()) return s;
    ::std::string res (s);
    ::boost::replace_all (res, "/", "\\");
    return res; }
#endif // UNIX

void fileindex_init ()
{   assert (disk_x.empty ());
    assert (site_x.empty ());
#ifndef ORDERED
    disk_x.reserve (16384);
    site_x.reserve (16384);
#endif // ORDERED
 }

fileindex_t insert_disk_path (const ::boost::filesystem::path& name, fileindex_flags flags, directory* pd, const uintmax_t size, const ::std::time_t& last_write)
{   if (name.empty ()) return nullfileindex;
    mxp_t::iterator i = disk_x.find (name.string ());
    if (i != disk_x.cend ())
    {   assert (i -> second < vx.size ());
        if (vx [i -> second].pd_ == nullptr)
            vx [i -> second].pd_ = pd;
        return i -> second; }
    vx.emplace_back (name, flags, pd, size, last_write);
    assert (vx.size () > 0);
    fileindex_t xin = vx.size () - 1;
    disk_x.emplace (name.string (), xin);
    return xin; }

fileindex_t insert_directory_path (const ::boost::filesystem::path& name, const fileindex_flags flags, directory* pd)
{   fileindex_t res = insert_disk_path (name, flags, pd, 0, 0);
    if (res != nullfileindex) set_flag (res, FX_DIR);
    return res; }

fileindex_t insert_borked_path (const ::boost::filesystem::path& name, const fileindex_flags flags, directory* pd)
{   fileindex_t res = insert_disk_path (name, flags, pd, 0, 0);
    if (res != nullfileindex) set_flag (res, FX_BORKED);
    return res; }

void add_site_path (const ::std::string& name, const fileindex_t s)
{   assert (s < vx.size ());
    auto i = site_x.emplace (name, s);
    if (! i.second) i.first -> second = s;
    if (vx [s].site_path_.empty ()) vx [s].site_path_ = name; }

fileindex_t get_fileindex (const ::boost::filesystem::path& name)
{   mxp_t :: const_iterator i = disk_x.find (name.string ());
    if (i != disk_x.cend ()) return i -> second;
    return insert_disk_path (name, 0, nullptr, 0, 0); }

fileindex_t get_fileindex (const ::std::string& name)
{   mxp_t :: const_iterator i = site_x.find (name);
    if (i != site_x.cend ()) return i -> second;
    return nullfileindex; }

::boost::filesystem::path get_disk_path (const fileindex_t ndx)
{   if (ndx >= vx.size ()) return ::boost::filesystem::path ();
    return vx [ndx].disk_path_; }

::std::string get_site_path (const fileindex_t ndx)
{   if (ndx >= vx.size ()) return ::std::string ();
    return vx [ndx].site_path_; }

fileindex_flags get_flags (const fileindex_t ndx)
{   assert (ndx < vx.size ());
    return vx [ndx].flags_; }

bool get_flag (const fileindex_t ndx, const fileindex_flags flag)
{   assert (ndx < vx.size ());
    return (vx [ndx].flags_ & flag) != 0; }

void set_flag (const fileindex_t ndx, const fileindex_flags flag)
{   assert (ndx < vx.size ());
    vx [ndx].flags_ |= flag; }

void reset_flag (const fileindex_t ndx, const fileindex_flags flag)
{   assert (ndx < vx.size ());
    vx [ndx].flags_ &= ~flag; }

uintmax_t get_size (const fileindex_t ndx)
{   assert (ndx < vx.size ());
    return vx [ndx].size_; }

::std::time_t last_write (const fileindex_t ndx)
{   assert (ndx < vx.size ());
    return vx [ndx].last_write_; }

crc_t get_crc (nitpick& nits, const fileindex_t ndx)
{   assert (ndx < vx.size ());
    if (! get_flag (ndx, FX_CRC))
    {   crc_calc crc;
        ::boost::filesystem::ifstream f (vx [ndx].disk_path_, ::std::ios_base::in);
        if (f.bad ())
        {   nits.pick (nit_cannot_read, es_error, ec_crc, "cannot read ", vx [ndx].disk_path_);
            set_crc (ndx, 0);
            return crc_initrem; }
        unsigned long max = context.max_file_size ();
        if (max == 0) max = DMFS_BYTES;
#ifdef CLEAN_SHAREDPTR_ARRAY
        ::std::shared_ptr < char [] > buf (new char [max]);
        if (buf.get () == nullptr)
#else // CLEAN_SHAREDPTR_ARRAY
	    char* buf = (char *) malloc (max);
        if (buf == nullptr)
#endif // CLEAN_SHAREDPTR_ARRAY
        {   f.close ();
            nits.pick (nit_out_of_memory, es_error, ec_crc, "out of memory reading ", vx [ndx].disk_path_);
            set_crc (ndx, 0);
            return crc_initrem; }
#ifdef CLEAN_SHAREDPTR_ARRAY
        while (! f.eof ())
        {   f.read (buf.get (), max);
            ::std::streamsize s = f.gcount ();
            if (s == 0) break;
            crc.process_bytes (buf.get (), s); }
#else // CLEAN_SHAREDPTR_ARRAY
        try
        {   while (! f.eof ())
            {   f.read (buf, max);
                ::std::streamsize s = f.gcount ();
                if (s == 0) break;
                crc.process_bytes (buf, s); } }
        catch (...)
        {   free (buf); throw; }
        free (buf); buf = nullptr;
#endif // CLEAN_SHAREDPTR_ARRAY
        set_crc (ndx, crc.checksum ()); }
    return vx [ndx].crc_; }

void set_crc (const fileindex_t ndx, const crc_t& crc)
{   assert (ndx < vx.size ());
    vx [ndx].crc_ = crc;
    set_flag (ndx, FX_CRC); }

::std::string fileindex_report ()
{   ::std::string res ("\nFile Indices\n");
    if (vx.size () == 0) return ::std::string ();
    for (::std::size_t i = 0; i < vx.size (); ++i)
    {   res += ::boost::lexical_cast < ::std::string > (i);
        res += ": ";
        res += vx [i].disk_path_.string ();
        res += " (";
        res += ::boost::lexical_cast < ::std::string > (vx [i].flags_);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (vx [i].size_);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (vx [i].crc_);
        res += ")\n"; }
    res += "\nSite:\n";
    for (auto i : site_x)
    {   res += i.first;
        res += " -> ";
        res += ::boost::lexical_cast < ::std::string > (i.second);
        res += "\n"; }
    res += "\nDisk index:\n";
    for (auto i : disk_x)
    {   res += i.first;
        res += " -> ";
        res += ::boost::lexical_cast < ::std::string > (i.second);
        res += "\n"; }
    res += "\n";
    return res; }

::std::string inner_join_site_paths (const ::std::string& lhs, const ::std::string& rhs)
{   if (lhs.empty ()) return rhs;
    if (rhs.empty ()) return lhs;
    ::std::string l (lhs);
    ::std::string r (rhs);
    if (r.at (0) != '/') r = ::std::string ("/") + r;
    ::std::string::size_type len = l.size ();
    if (l.at (len - 1) == '/')
    {   if (len == 1) return r;
        l = l.substr (0, len - 1); }
    return l + r; }

::std::string join_site_paths (const ::std::string& lhs, const ::std::string& rhs)
{   return ::boost::replace_all_copy (inner_join_site_paths (lhs, rhs), "//", "/"); }

void load_crcs (nitpick& nits, const ::boost::filesystem::path& persist)
{   if (! ::boost::filesystem::exists (persist)) return;
    const int max = 4096;
    char buf [max];
    ::boost::filesystem::fstream f (persist, ::std::ios::in);
    if (f.fail ())
        nits.pick (nit_cannot_read, es_error, ec_crc, "cannot open ", persist.string ());
    else
    {   buf [0] = 0;
        f.getline (&buf [0], max - 1);
        if (f.fail ())
            nits.pick (nit_cannot_read, es_error, ec_crc, "error reading title from ", persist.string ());
        else
        {   buf [max - 1] = 0;
            if (strcmp (FULLNAME, buf) != 0)
                nits.pick (nit_wrong_version, es_error, ec_crc, persist.string (), " was not written by " PROG);
            else
            {   f.getline (&buf [0], max - 1);
                if (f.fail ())
                    nits.pick (nit_cannot_read, es_error, ec_crc, "error reading version from ", persist.string ());
                else
                {   buf [max - 1] = 0;
                    vstr_t a (split_by_charset (&buf [0], "."));
                    if (a.size () != 3)
                        nits.pick (nit_cannot_read, es_error, ec_crc, persist.string (), " appears corrupt");
                    else
                    {   vstr_t v (split_by_charset (VERSION_STRING, "."));
                        assert (v.size () == 3);
                        if ((lexical < int > :: cast (v.at (0)) < lexical < int > :: cast (a.at (0))) ||
                            (lexical < int > :: cast (v.at (1)) < lexical < int > :: cast (a.at (1))) ||
                            (lexical < int > :: cast (v.at (2)) < lexical < int > :: cast (a.at (2))))
                            nits.pick (nit_wrong_version, es_error, ec_crc, persist.string (), " was written by a more recent version of " PROG);
                        else while (! f.eof ())
                        {   buf [0] = 0;
                            f.getline (&buf [0], max - 1);
                            if (! f.eof ())
                                if (f.fail ())
                                {   nits.pick (nit_cannot_read, es_error, ec_crc, "error reading content from ", persist.string ());
                                    break; }
                                if (buf [0] != 0)
                                {   buf [max-1] = 0;
                                    vstr_t args (split_by_charset (&buf [0], ","));
                                    if (args.size () >= PERSIST_ARG_COUNT)
                                    {   ::boost::filesystem::path disk_path (uq (args.at (PERSIST_PATH)));
                                        fileindex_t ndx = get_fileindex (disk_path);
                                        if (ndx != nullfileindex)
                                        {   uintmax_t size = lexical < uintmax_t > :: cast (args.at (PERSIST_SIZE));
                                            ::std::time_t last_write = lexical < ::std::time_t > :: cast (args.at (PERSIST_LAST_WRITE));
                                            crc_t crc = lexical < crc_t > :: cast (args.at (PERSIST_CRC));
                                            vx [ndx].reload (size, last_write, crc); } } } } } } } } } }

void write_crcs (nitpick& nits, const ::boost::filesystem::path& persist)
{   ::boost::filesystem::fstream f (persist, ::std::ios::out | ::std::ios::trunc);
    if (f.fail ())
        nits.pick (nit_cannot_update, es_error, ec_crc, "cannot open ", persist.string ());
    else
    {   ::std::string ln (FULLNAME "\n" VERSION_STRING "\n");
        f.write (ln.c_str (), ln.length ());
        if (f.fail ())
            nits.pick (nit_cannot_write, es_error, ec_crc, "cannot write to ", persist.string ());
        else for (auto v : vx)
            if ((v.flags_ & (FX_DIR | FX_BORKED | FX_SCANNED)) == 0)
                if ((v.crc_ != crc_initrem) && (v.crc_ != 0))
                {   ln = v.persist ();
                    if (! ln.empty ())
                    {   ln += "\n";
                        f.write (ln.c_str (), ln.length ());
                        if (f.fail ())
                        {   nits.pick (nit_cannot_write, es_error, ec_crc, "cannot write to ", persist.string ());
                            break; } } } } }

void dedu (nitpick& nits)
{   ::std::string s (context.shadow_persist ());
    if (s.empty ()) s = "fileindex.asc";
    ::boost::filesystem::path persist (s);
    if (persist.is_relative ())
        persist = ::boost::filesystem::path (context.path ()) / persist;
    if (::boost::filesystem::exists (persist)) load_crcs (nits, persist);
    for (fileindex_t i = 0; i < vx.size (); ++i)
    {   index_t& x = vx.at (i);
        if ((x.flags_ & (FX_DIR | FX_BORKED | FX_SCANNED)) == 0)
        {   crc_t crc = get_crc (nits, i);
            if ((crc == 0) || (crc == crc_initrem)) continue;
            mcrc_t::const_iterator ci = mcrc.find (crc);
            if (ci != mcrc.cend ())
            {   index_t& y = vx.at (ci -> second);
                if (x.size_ == y.size_)
                {   if (y.dedu_ == nullfileindex) x.dedu_ = ci -> second;
                    else x.dedu_ = y.dedu_;
                    nits.pick (nit_duplicate, es_info, ec_crc, x.disk_path_, " duplicates ", vx.at (x.dedu_).disk_path_);
                    continue; } }
            mcrc.emplace (crc, i); } }
    write_crcs (nits, persist); }

bool isdu (const fileindex_t ndx)
{   assert (ndx < vx.size ());
    return vx [ndx].dedu_ != nullfileindex; }

fileindex_t du (const fileindex_t ndx)
{   assert (ndx < vx.size ());
    return vx [ndx].dedu_; }
