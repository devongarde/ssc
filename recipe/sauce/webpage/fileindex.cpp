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
#include "main/context.h"
#include "utility/filesystem.h"
#include "utility/quote.h"
#include "webpage/fileindex.h"
#include "webpage/directory.h"
#include "coop/lox.h"

#define PERSIST_SPECIAL 0
#define PERSIST_SIZE (PERSIST_SPECIAL + 1)
#define PERSIST_LAST_WRITE (PERSIST_SIZE + 1)
#define PERSIST_FLAGS (PERSIST_LAST_WRITE + 1)
#define PERSIST_CRC (PERSIST_FLAGS + 1)
#define PERSIST_DEPENDENCIES (PERSIST_CRC + 1)
#define PERSIST_LYNX (PERSIST_DEPENDENCIES + 1)
#define PERSIST_ARG_COUNT (PERSIST_LYNX + 1)

#define MJR_LYNX_N_DEPEND 0
#define MNR_LYNX_N_DEPEND 1
#define REL_LYNX_N_DEPEND 7
#define LYNX_N_DEPEND_XTRA 7

#define VX_RESERVE 16384

typedef ssc_map < fileindex_t, fileindex_t > mndx_t;

void inner_set_flag (const fileindex_t ndx, const fileindex_flags flag);
void inner_reset_flag (const fileindex_t ndx, const fileindex_flags flag);
bool inner_get_any_flag (const fileindex_t ndx, const fileindex_flags flag);
bool inner_get_every_flag (const fileindex_t ndx, const fileindex_flags flag);

struct index_t
{   fileindex_t mummy_ = nullfileindex;
    ::std::string name_;
    short v_ = -1;
    fileindex_flags flags_ = 0;
    uintmax_t size_ = 0;
    crc_t crc_ = crc_initrem;
    fileindex_t dedu_ = nullfileindex;
    ::std::time_t last_write_ = 0;
    sndx_t dx_, lx_;
    DEFAULT_CONSTRUCTORS (index_t);
    explicit index_t (const fileindex_t mummy, const ::std::string& name)
        :   mummy_ (mummy), name_ (name) { }
    explicit index_t (const fileindex_t mummy, const ::std::string& name, const fileindex_flags flags)
        :   mummy_ (mummy), name_ (name), flags_ (flags) { }
    explicit index_t (const ::std::string& name, const short v)
        :   mummy_ (nullfileindex), name_ (name), v_ (v), flags_ (FX_DIR | FX_EXISTS) { }
    index_t (const fileindex_t mummy, const ::std::string& name, const fileindex_flags flags, const uintmax_t size, const ::std::time_t& last_write)
        :   mummy_ (mummy), name_ (name), flags_ (flags), size_ (size), last_write_ (last_write) { }
    index_t (const fileindex_t mummy, const ::std::string& name, const fileindex_flags flags, const uintmax_t size, const ::std::time_t& last_write, const crc_t& crc, const sndx_t& dx, const sndx_t& lx)
        :   mummy_ (mummy), name_ (name), flags_ (flags), size_ (size), crc_ (crc), last_write_ (last_write), dx_ (dx), lx_ (lx) { }
    ::boost::filesystem::path disk_path () const;
    ::std::string site_path () const;
    void swap (index_t& i) noexcept;
    void reset ()
    {   index_t i;
        swap (i); }
    void reset (const index_t& ii)
    {   index_t i (ii);
        swap (i); }
    bool needs_update (const ::std::time_t& st) const; };

typedef ::std::vector < index_t > vx_t;
typedef ssc_map < ::std::string, fileindex_t > mxp_t;
typedef ::std::map < crc_t, fileindex_t > mcrc_t;

vx_t vx;
mxp_t site_x, disk_x;  // note ::boost::filesystem::path and ::std::map are not pals
mcrc_t mcrc;

::boost::filesystem::path index_t::disk_path () const
{   if (v_ < 0) return GSL_AT (vx, mummy_).disk_path () / name_;
    if (v_ == 0) return context.rootp ();
    return paths_root::virtual_roots ().at (v_) -> get_disk_path (); }

::std::string index_t::site_path () const
{   if (v_ < 0) return join_site_paths (GSL_AT (vx, mummy_).site_path (), name_);
    if (v_ == 0) return "/";
    return paths_root::virtual_roots ().at (v_) -> get_site_path (); }

void index_t::swap (index_t& i) noexcept
{   ::std::swap (crc_, i.crc_);
    ::std::swap (dedu_, i.dedu_);
    dx_.swap (i.dx_);
    ::std::swap (flags_, i.flags_);
    ::std::swap (last_write_, i.last_write_);
    lx_.swap (i.lx_);
    ::std::swap (mummy_, i.mummy_);
    name_.swap (i.name_);
    ::std::swap (size_, i.size_); }

bool index_t::needs_update (const ::std::time_t& st) const
{   for (auto x : dx_)
        if (last_write (x) > st) return true;
    for (auto x : lx_)
        if (last_write (x) > st) return true;
    return false; }

void fileindex_init ()
{   PRESUME (disk_x.empty (), __FILE__, __LINE__);
    PRESUME (site_x.empty (), __FILE__, __LINE__);
#ifndef ORDERED
    disk_x.reserve (VX_RESERVE);
    site_x.reserve (VX_RESERVE);
#endif // ORDERED
}

void reset_fileindices () noexcept
{   vx.clear ();
    site_x.clear ();
    disk_x.clear ();
    mcrc.clear (); }

void unindex (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    site_x.erase (GSL_AT (vx, ndx).site_path ());
    disk_x.erase (GSL_AT (vx, ndx).disk_path ().string ());
    if (GSL_AT (vx, ndx).crc_ != crc_initrem) mcrc.erase (GSL_AT (vx, ndx).crc_); }

void reindex (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    unindex (ndx);
    site_x.emplace (mxp_t::value_type (GSL_AT (vx, ndx).site_path (), ndx));
    disk_x.emplace (mxp_t::value_type (GSL_AT (vx, ndx).disk_path ().string (), ndx));
    if (inner_get_any_flag (ndx, FX_CRC))
        if (! inner_get_any_flag (ndx, (FX_DELETED | FX_BORKED | FX_DIR)))
            if (GSL_AT (vx, ndx).crc_ != crc_initrem)
            {   mcrc.emplace (mcrc_t::value_type (GSL_AT (vx, ndx).crc_, ndx)); return; }
    inner_reset_flag (ndx, FX_CRC); }

void note_deleted (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    inner_reset_flag (ndx, FX_STALE);
    if (! inner_get_any_flag (ndx, FX_DELETED))
    {   inner_set_flag (ndx, FX_DELETED);
        unindex (ndx); } }

void update_fileindex (const fileindex_t ndx, const fileindex_flags ff, const bool locked = false)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    ::boost::filesystem::path name;
    {   lox l (lox_fileindex, locked);
        const index_t& xx = GSL_AT (vx, ndx);
        name = xx.disk_path (); }
    fileindex_flags f (ff);
    uintmax_t s = 0;
    ::std::time_t lw = 0;
    if (((f & FX_DELETED) == FX_DELETED) || ! file_exists (name))
    {   lox l (lox_fileindex, locked);
        f |= FX_DELETED;
        note_deleted (ndx); }
    else if (is_folder (name)) f |= FX_DIR;
#ifndef NOLYNX
    else if (! is_file_linked (name)) f |= FX_LINKED;
#endif // NOLYNX
    else if (! is_file (name)) f |= FX_BORKED;
    else
    {   s = get_file_size (name);
        lw = get_last_write_time (name); }
    lox l (lox_fileindex, locked);
    index_t& x = GSL_AT (vx, ndx);
    x.flags_ = f;
    if ((x.size_ != s) || (GSL_AT (vx, ndx).last_write_ != lw))
    {   if (x.crc_ != crc_initrem)
        {   mcrc.erase (x.crc_); x.crc_ = crc_initrem; }
        x.flags_ &= ~FX_CRC; }
    inner_reset_flag (ndx, FX_STALE);
    x.size_ = s;
    x.last_write_ = lw; }

fileindex_t inner_insert_disk_path (const fileindex_t mummy, const ::boost::filesystem::path& name, const fileindex_flags flags, const bool locked = false)
{   if (name.empty ()) return nullfileindex;
    fileindex_t xin = nullfileindex;
    {   ::boost::filesystem::path canon (canonical_name (name));
        lox l (lox_fileindex, locked);
        mxp_t::iterator i = disk_x.find (canon.string ());
        if (i != disk_x.cend ()) xin = i -> second;
        else
        {   if (mummy == nullfileindex)
                vx.emplace_back (mummy, canon.string (), flags);
            else
            {   const ::boost::filesystem::path dp = GSL_AT (vx, mummy).disk_path ();
                const ::boost::filesystem::path pp = canon.parent_path ();
    #ifdef _MSC_VER
                if (pp.size () <= 2) return nullfileindex;
    #endif // WINDOWS
                PRESUME (pp.size () < canon.size (), __FILE__, __LINE__);
                if (dp == pp)
                    vx.emplace_back (mummy, canon.filename ().string (), flags);
                else
                {   const mxp_t :: const_iterator ii = disk_x.find (pp.string ());
                    if (ii != disk_x.cend ()) vx.emplace_back (ii -> second, canon.filename ().string (), flags);
                    else
                    {   const fileindex_t ndx = inner_insert_disk_path (mummy, pp, FX_DIR | FX_EXISTS, true);
                        if (ndx == nullfileindex) return ndx;
                        vx.emplace_back (ndx, canon.filename ().string (), flags); } } }
            PRESUME (vx.size () > 0, __FILE__, __LINE__);
            xin = vx.size () - 1;
            PRESUME ((xin != 0) && (xin >= context.virtuals ().size ()), __FILE__, __LINE__); } }
    update_fileindex (xin, flags, locked);
    {   lox l (lox_fileindex, locked);
        reindex (xin); }
    return xin; }

fileindex_t insert_disk_path (const fileindex_t mummy, const ::boost::filesystem::path& name, const fileindex_flags flags)
{   fileindex_t ndx = inner_insert_disk_path (mummy, name, flags);
    if (ndx == nullfileindex) ndx = inner_insert_disk_path (nullfileindex, name, flags);
    return ndx; }

fileindex_t insert_directory_path (const fileindex_t mummy, const ::boost::filesystem::path& name)
{   fileindex_t ndx = inner_insert_disk_path (mummy, name, FX_DIR);
    if (ndx == nullfileindex) ndx = inner_insert_disk_path (nullfileindex, name, FX_DIR);
    return ndx; }

fileindex_t insert_root_path (const ::boost::filesystem::path& name, const short v)
{   PRESUME (! fred.started (), __FILE__, __LINE__);
    ::boost::filesystem::path canon (canonical_name (absolute_name (name)));
    fileindex_t xin = get_fileindex (canon);
    if (xin != nullfileindex)
        GSL_AT (vx, xin).v_ = v;
    else
    {   vx.emplace_back (canon.string (), v);
        PRESUME (vx.size () > 0, __FILE__, __LINE__);
        xin = vx.size () - 1; }
    update_fileindex (xin, FX_DIR | FX_EXISTS);
    reindex (xin);
    PRESUME ((v >= 0) && (static_cast < ::std::size_t > (v) < paths_root::virtual_roots ().size ()), __FILE__, __LINE__);
    paths_root::virtual_roots ().at (v) -> fileindex (xin);
    return xin; }

fileindex_t get_fileindex (const fileindex_t mummy, const ::boost::filesystem::path& name)
{   {   lox l (lox_fileindex);
        mxp_t :: const_iterator i = disk_x.find (name.string ());
        if (i != disk_x.cend ()) return i -> second; }
    return inner_insert_disk_path (mummy, name, 0); }

fileindex_t get_fileindex (const ::boost::filesystem::path& name)
{   lox l (lox_fileindex);
    mxp_t :: const_iterator i = disk_x.find (name.string ());
    if (i != disk_x.cend ()) return i -> second;
    return nullfileindex; }

fileindex_t get_fileindex (const ::std::string& name)
{   lox l (lox_fileindex);
    mxp_t :: const_iterator i = site_x.find (name);
    if (i != site_x.cend ()) return i -> second;
    return nullfileindex; }

::boost::filesystem::path get_disk_path (const fileindex_t ndx)
{   if (ndx >= vx.size ()) return ::boost::filesystem::path ();
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).disk_path (); }

::std::string get_site_path (const fileindex_t ndx)
{   if (ndx >= vx.size ()) return ::std::string ();
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).site_path (); }

fileindex_flags get_flags (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).flags_; }

::std::string get_name (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).name_; }

bool inner_get_any_flag (const fileindex_t ndx, const fileindex_flags flag)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return (GSL_AT (vx, ndx).flags_ & flag) != 0; }

bool get_any_flag (const fileindex_t ndx, const fileindex_flags flag)
{   lox l (lox_fileindex);
    return inner_get_any_flag (ndx, flag); }

bool inner_get_every_flag (const fileindex_t ndx, const fileindex_flags flag)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return (GSL_AT (vx, ndx).flags_ & flag) == flag; }

bool get_every_flag (const fileindex_t ndx, const fileindex_flags flag)
{   lox l (lox_fileindex);
    return inner_get_every_flag (ndx, flag); }

void inner_set_flag (const fileindex_t ndx, const fileindex_flags flag)
{   GSL_AT (vx, ndx).flags_ |= flag; }

void set_flag (const fileindex_t ndx, const fileindex_flags flag)
{   lox l (lox_fileindex);
    inner_set_flag (ndx, flag); }

void inner_reset_flag (const fileindex_t ndx, const fileindex_flags flag)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    GSL_AT (vx, ndx).flags_ &= ~flag; }

void reset_flag (const fileindex_t ndx, const fileindex_flags flag)
{   lox l (lox_fileindex);
    inner_reset_flag (ndx, flag); }

uintmax_t get_size (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).size_; }

::std::time_t last_write (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).last_write_; }

crc_t calc_crc (nitpick& nits, const ::boost::filesystem::path& dp)
{   crc_calc crc;
    BOOST_IFSTREAM_CNSTRO (f, dp, ::std::ios_base::in);
    if (f.bad ())
    {   nits.pick (nit_cannot_read, es_error, ec_crc, "cannot read ", dp);
        return crc_initrem; }
    unsigned long max = context.max_file_size ();
    if (max == 0) max = DMFS_BYTES;
#ifdef CLEAN_SHAREDPTR_ARRAY
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26414) // isn't that precisely what the code does?
#endif // _MSC_VER
    ::std::shared_ptr < char [] > buf (new char [max]);
    if (buf.get () == nullptr)
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
#else // CLEAN_SHAREDPTR_ARRAY
	char* buf = (char *) malloc (max);
    if (buf == nullptr)
#endif // CLEAN_SHAREDPTR_ARRAY
    {   f.close ();
        nits.pick (nit_out_of_memory, es_error, ec_crc, "out of memory reading ", dp);
        return crc_initrem; }
#ifdef CLEAN_SHAREDPTR_ARRAY
    while (! f.eof ())
    {   f.read (buf.get (), max);
        const ::std::streamsize s = f.gcount ();
        if (s == 0) break;
        crc.process_bytes (buf.get (), GSL_NARROW_CAST < ::std::size_t > (s)); }
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
    return crc.checksum (); }

crc_t get_crc (nitpick& nits, const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    if (! inner_get_any_flag (ndx, FX_CRC)) // only one thread looks at a file, once in scanning once in examining; so this shouldn't need locking
    {   crc_t crc = calc_crc (nits, GSL_AT (vx, ndx).disk_path ());
        set_crc (ndx, crc);
        return crc; }
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).crc_; }

void set_crc (const fileindex_t ndx, const crc_t& crc)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    GSL_AT (vx, ndx).crc_ = crc;
    inner_set_flag (ndx, FX_CRC); }

::std::string fileindex_report ()
{   if (context.test ()) return ::std::string ();
    ::std::string res ("\nFile Indices\n");
    if (vx.size () == 0) return ::std::string ();
    for (::std::size_t i = 0; i < vx.size (); ++i)
    {   res += "  ";
        res += ::boost::lexical_cast < ::std::string > (i);
        res += ": ";
        res += GSL_AT (vx, i).name_;
        res += " (";
        if (GSL_AT (vx, i).mummy_ == nullfileindex) res += "-";
        else res += ::boost::lexical_cast < ::std::string > (GSL_AT (vx, i).mummy_);
        res += ",";
        if (GSL_AT (vx, i).v_ < 0) res += "-";
        else res += ::boost::lexical_cast < ::std::string > (GSL_AT (vx, i).v_);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (GSL_AT (vx, i).size_);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (GSL_AT (vx, i).last_write_);
        res += ",";
        ::std::string flg;
        if ((GSL_AT (vx, i).flags_ & FX_SCANNED) == FX_SCANNED) flg += "S";
        if ((GSL_AT (vx, i).flags_ & FX_EXISTS) == FX_EXISTS) flg += "E";
        if ((GSL_AT (vx, i).flags_ & FX_TESTED) == FX_TESTED) flg += "T";
        if ((GSL_AT (vx, i).flags_ & FX_CRC) == FX_CRC) flg += "C";
        if ((GSL_AT (vx, i).flags_ & FX_DIR) == FX_DIR) flg += "D";
        if ((GSL_AT (vx, i).flags_ & FX_BORKED) == FX_BORKED) flg += "B";
        if ((GSL_AT (vx, i).flags_ & FX_STALE) == FX_STALE) flg += "s";
        if ((GSL_AT (vx, i).flags_ & FX_DELETED) == FX_DELETED) flg += "d";
        if ((GSL_AT (vx, i).flags_ & FX_LINKED) == FX_LINKED) flg += "L";
        if (flg.empty ()) res += "-"; else res += flg;
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (GSL_AT (vx, i).crc_);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (GSL_AT (vx, i).dx_.size ());
        for (auto dx : GSL_AT (vx, i).dx_)
        {   res += " ";
            res += ::boost::lexical_cast < ::std::string > (dx); }
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (GSL_AT (vx, i).lx_.size ());
        for (auto lx : GSL_AT (vx, i).lx_)
        {   res += " ";
            res += ::boost::lexical_cast < ::std::string > (lx); }
        res += ",";
        res += GSL_AT (vx, i).site_path ();
        res += ",";
        res += GSL_AT (vx, i).disk_path ().string ();
       res += ")\n"; }
    res += "\nSite:\n";
    for (auto i : site_x)
    {   res += "  ";
        res += i.first;
        res += " -> ";
        res += ::boost::lexical_cast < ::std::string > (i.second);
        res += "\n"; }
    res += "\nDisk index:\n";
    for (auto i : disk_x)
    {   res += "  ";
        res += i.first;
        res += " -> ";
        res += ::boost::lexical_cast < ::std::string > (i.second);
        res += "\n"; }
    res += "\nCRC index:\n";
    for (auto i : mcrc)
    {   res += "  ";
        res += ::boost::lexical_cast < ::std::string > (i.first);
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
    const ::std::string::size_type len = l.size ();
    if (l.at (len - 1) == '/')
    {   if (len == 1) return r;
        l = l.substr (0, len - 1); }
    return l + r; }

::std::string join_site_paths (const ::std::string& lhs, const ::std::string& rhs)
{   return ::boost::replace_all_copy (inner_join_site_paths (lhs, rhs), "//", "/"); }

::std::string::size_type crap_find_last_of_that_works (const ::std::string& s, const ::std::string& ss, const ::std::string::size_type pos = ::std::string::npos)
    // I don't understand why some systems' find_last_of returns 0 when failing to find "/.." ; I would expect npos.
{   ::std::string::size_type smax = pos;
    if (smax == ::std::string::npos) smax = s.length ();
    const ::std::string::size_type ssmax = ss.length ();
    if (smax >= ssmax)
    {   smax -= ssmax;
        ++smax;
        while (smax > 0)
            if (s.at (--smax) == ss.at (0))
                if (s.substr (smax, ssmax) == ss) return smax; }
    return ::std::string::npos; }

::std::string join_and_sanatise_site_paths (const ::std::string& lhs, const ::std::string& rhs)
{   ::std::string res = join_site_paths (lhs, rhs);
    ::boost::replace_all (res, "/./", "/");
    int paranoia = 0;
    for (   ::std::string::size_type pos = crap_find_last_of_that_works (res, "/..");
            pos != ::std::string::npos;
            pos = crap_find_last_of_that_works (res, "/.."))
    {   if (pos == 0) break;
        ::std::string::size_type prepos = res.substr (0, pos).find_last_of ('/');
        if (prepos == ::std::string::npos) res = res.substr (pos);
        else res = res.substr (0, prepos) + res.substr (pos + 3);
        if (++paranoia == 10) break; }
    return res; }

::boost::filesystem::path persist_path ()
{   ::boost::filesystem::path p;
    ::std::string s (context.shadow_persist ());
    if (! s.empty ()) p = s;
    else p = context.config ().replace_extension ("ndx");
    return p; }

bool fileindex_load_internal (nitpick& nits, bool& ok)
{   PRESUME (! fred.inited (), __FILE__, __LINE__);
    ::boost::filesystem::path p (persist_path ());
    if (! file_exists (p)) return true;
    if (context.progress ()) ::std::cout << "loading " << p.string () << " ...\n";
    BOOST_FSTREAM_CNSTRO (f, p, ::std::ios::in);
    if (f.fail ())
    {   nits.pick (nit_cannot_read, es_error, ec_crc, "cannot open ", p.string ());
        ok = true; return false; }
    reset_fileindices ();
    enum { fl_prog, fl_version, fl_root, fl_virtual_count, fl_virtual, fl_count, fl_site, fl_disk, fl_data } status = fl_prog;
#define BUFLEN 32767
#if BUFLEN < 255
#error fileindex BUFLEN is too short 
#endif
    CONSTEXPR size_t buflen = BUFLEN;
#undef BUFLEN
    auto up = ::std::unique_ptr <char []> (new char [buflen]);
    char* buf = up.get ();
    fileindex_t count = 0;
    ::std::size_t virtual_count = 0, got = 0;
    ::std::string site;
    ::boost::filesystem::path disk;
    bool whoops = false;
    while (! f.eof ())
    {   *buf = 0;
        f.getline (buf, buflen - 1);
        if (f.eof ()) break;
        if (f.fail ())
        {   nits.pick (nit_cannot_read, es_error, ec_crc, "error reading from ", p.string ());
            nits.pick (nit_cannot_read, es_debug, ec_crc, "perhaps increase the value of max in fileindex_load_internal");
            ok = false; return false; }
        if ((*buf == 0) || (*buf == '#')) continue;
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26481)
#endif // _MSC_VER
        buf [buflen-1] = 0;
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
        switch (status)
        {   case fl_prog :
                if (strcmp (FULLNAME, buf) != 0)
                {   nits.pick (nit_wrong_version, es_error, ec_crc, p.string (), " was not written by " PROG);
                    ok = true; return false; }
                status = fl_version; break;
            case fl_version :
                {   vstr_t a (split_by_charset (buf, "."));
                    if (a.size () != 3)
                    {   nits.pick (nit_cannot_read, es_error, ec_crc, p.string (), " appears corrupt");
                        ok = false; return false; }
                    else
                    {   const int mjr = lexical < int > :: cast (a.at (0));
                        const int mnr = lexical < int > :: cast (a.at (1));
                        const int rel = lexical < int > :: cast (a.at (2));
                        if ((VERSION_MAJOR < mjr) || ((VERSION_MAJOR == mjr) && (VERSION_MINOR < mnr)) || ((VERSION_MAJOR == mjr) && (VERSION_MINOR == mnr) && (VERSION_RELEASE < rel)))
                        {   nits.pick (nit_wrong_version, es_error, ec_crc, p.string (), " was written by a more recent version of " PROG);
                            ok = true; return false; }
                        if ((mjr < MJR_LYNX_N_DEPEND) || ((MJR_LYNX_N_DEPEND == mjr) && (mnr < MNR_LYNX_N_DEPEND)) || ((MJR_LYNX_N_DEPEND == mjr) && (MNR_LYNX_N_DEPEND == mnr) && (rel < REL_LYNX_N_DEPEND)))
                        {   nits.pick (nit_wrong_version, es_error, ec_crc, p.string (), " was written by an incompatible version of " PROG);
                            ok = true; return false; } } }
                status = fl_root;
                break;
            case fl_root :
                if (! compare_no_case (context.root (), buf))
                {   nits.pick (nit_root_change, es_error, ec_crc, "site root changed from ", quote (buf), " to ", quote (context.root ()));
                    ok = true; return false; }
                status = fl_virtual_count; break;
            case fl_virtual_count :
                {   virtual_count = lexical < unsigned > :: cast (buf, 0);
                    if (virtual_count != context.virtuals ().size ())
                    {   nits.pick (nit_virtual_change, es_error, ec_crc, "number of virtuals changed from ", virtual_count, " to ", context.virtuals ().size ());
                        ok = true; return false; } }
                status = fl_virtual; break;
            case fl_virtual :
#if _MSC_VER >= 1930
#pragma warning (push, 3)
#pragma warning (disable : 26481)
#endif
                if ((*buf == '-') && (buf [1] == 0))
#if _MSC_VER >= 1930
#pragma warning (pop)
#endif // _MSC_VER
                {   if (got < virtual_count)
                    {   nits.pick (nit_virtual_change, es_error, ec_crc, "missing virtual roots; ", p.string (), " appears to be corrupt");
                        whoops = true; ok = true; return false; }
                    while (got < context.virtuals ().size ())
                    {   nits.pick (nit_virtual_change, es_error, ec_crc, "virtual root ", quote (context.virtuals ().at (got)), " is new");
                        ok = true; whoops = true; ++got; }
                    if (whoops)
                    {   nits.pick (nit_abandon, es_info, ec_crc, p.string (), " is incompatible with " PROG " version " VERSION_STRING "; abandoning load");
                        ok = true; return false; }
                    status = fl_count; }
                else if (got < context.virtuals ().size ())
                {   if (! compare_no_case (context.virtuals ().at (got), buf))
                    {   nits.pick (nit_virtual_change, es_error, ec_crc, "virtual root changed from ", quote (buf), " to ", quote (context.virtuals ().at (got)));
                        ok = true; whoops = true; }
                    ++got; }
                else
                {   nits.pick (nit_virtual_change, es_error, ec_crc, "virtual root ", quote (buf), " no longer applied.");
                    ok = true; whoops = true; ++got; }
                break;
            case fl_count :
                count = lexical < fileindex_t > :: cast (buf);
                if (count > 0)
                {   vx.reserve (count);
#ifndef ORDERED
                    site_x.reserve (count);
                    disk_x.reserve (count);
#endif // ORDERED
                                            }
                status = fl_site; break;
            case fl_site :
                site = buf;
                status = fl_disk; break;
            case fl_disk :
                disk = buf;
                status = fl_data; break;
            case fl_data :
                {   vstr_t args (split_by_charset (buf, ","));
                    if (args.size () != PERSIST_ARG_COUNT) break;
                    const short v = lexical < short > :: cast (args.at (PERSIST_SPECIAL));
                    uintmax_t size = lexical < uintmax_t > :: cast (args.at (PERSIST_SIZE));
                    ::std::time_t last_write = lexical < ::std::time_t > :: cast (args.at (PERSIST_LAST_WRITE));
                    crc_t crc = lexical < crc_t > :: cast (args.at (PERSIST_CRC));
                    fileindex_flags flags = lexical < fileindex_flags > :: cast (args.at (PERSIST_FLAGS)) | FX_STALE;
                    sndx_t dx, lx;
                    {   vstr_t sdx (split_by_space (args.at (PERSIST_DEPENDENCIES)));
                        if (sdx.size () > 0)
                        {   ::std::size_t most = lexical < ::std::size_t > :: cast (sdx.at (0));
                            if (most >= sdx.size ()) most = sdx.size ()-1;
                            for (::std::size_t i = 0; i < most; ++i)
                                dx.emplace (lexical < fileindex_t > :: cast (sdx.at (i+1))); }
                        sdx = split_by_space (args.at (PERSIST_LYNX));
                        if (sdx.size () > 0)
                        {   ::std::size_t most = lexical < ::std::size_t > :: cast (sdx.at (0));
                            if (most >= sdx.size ()) most = sdx.size ()-1;
                            for (::std::size_t i = 0; i < most; ++i)
                                lx.emplace (lexical < fileindex_t > :: cast (sdx.at (i+1))); } }
                    fileindex_t mummy = get_fileindex (disk.parent_path ());
                    vx.emplace_back (mummy, site, flags, size, last_write, crc, dx, lx);
                    fileindex_t moi = vx.size () - 1;
                    PRESUME (GSL_AT (vx, moi).name_ == site, __FILE__, __LINE__);
                    if (v >= 0) GSL_AT (vx, moi).v_ = v;
                    site_x.emplace (mxp_t::value_type (GSL_AT (vx, moi).site_path (), moi));
                    disk_x.emplace (mxp_t::value_type (GSL_AT (vx, moi).disk_path ().string (), moi));
                    if ((GSL_AT (vx, moi).flags_ & FX_CRC) == FX_CRC)
                        if (GSL_AT (vx, moi).crc_ != crc_initrem)
                            mcrc.emplace (mcrc_t::value_type (GSL_AT (vx, moi).crc_, moi)); }
                site.clear (); disk.clear ();
                status = fl_site;
                break;
            default :
                 nits.pick (nit_cannot_read, es_error, ec_crc, p.string (), " appears corrupt, or was not written by " PROG);
                 ok = true; return false; } }
    if (status != fl_site)
    {   nits.pick (nit_cannot_read, es_error, ec_crc, p.string (), " is corrupt or truncated; abandoning load");
        ok = false; return false; }
    vx.shrink_to_fit ();
    if (count < vx.size ())
    {   nits.pick (nit_cannot_read, es_catastrophic, ec_crc, p.string (), " is inconsistent; abandoning load");
        ok = false; return false; }
    count = vx.size ();
    return true; }

bool fileindex_load (nitpick& nits)
{   if (! context.shadow_enable ()) return true;
    bool ok = false;
    if (fileindex_load_internal (nits, ok))
    {   if (context.tell (es_splurge)) outstr.out (fileindex_report ());
        return true; }
    reset_fileindices (); 
    if (! ok)
    {   ::boost::filesystem::path p (persist_path ());
        if (file_exists (p))
            if (delete_file (p)) nits.pick (nit_deleted_bad_file, es_info, ec_crc, "deleted bad file ", p.string ());
            else nits.pick (nit_cannot_delete, es_error, ec_crc, "cannot delete bad file ", p.string ()); }
    return false; }

bool write_fileindex_record (nitpick& nits, BOOST_FSTREAM& f, const ::boost::filesystem::path& name, const ::std::size_t n, const mndx_t& mndx)
{   index_t& v = GSL_AT (vx, n);
    ::std::string ln;
    ln = ::boost::lexical_cast < ::std::string > (v.name_);
    ln += "\n";
    ln += ::boost::lexical_cast < ::std::string > (v.disk_path ().string ());
    ln += "\n";
    ln += ::boost::lexical_cast < ::std::string > (v.v_); // ensure this write order matches PERSIST_... #defines above
    ln += ",";
    ln += ::boost::lexical_cast < ::std::string > (v.size_);
    ln += ",";
    ln += ::boost::lexical_cast < ::std::string > (v.last_write_);
    ln += ",";
    ln += ::boost::lexical_cast < ::std::string > (v.flags_);
    ln += ",";
    if ((v.flags_ & FX_CRC) == FX_CRC) ln += ::boost::lexical_cast < ::std::string > (v.crc_);
    else ln += "0";
    ln += ",";
    ln += ::boost::lexical_cast < ::std::string > (v.dx_.size ());
    for (auto dx : v.dx_)
    {   ln += " ";
        mndx_t::const_iterator i = mndx.find (dx);
        if (i == mndx.cend ()) ln += ::boost::lexical_cast < ::std::string > (nullfileindex);
        else ln += ::boost::lexical_cast < ::std::string > (i -> second); }
    ln += ",";
    ln += ::boost::lexical_cast < ::std::string > (v.lx_.size ());
    for (auto lx : v.lx_)
    {   ln += " ";
        mndx_t::const_iterator i = mndx.find (lx);
        if (i == mndx.cend ()) ln += ::boost::lexical_cast < ::std::string > (nullfileindex);
        else ln += ::boost::lexical_cast < ::std::string > (i -> second); }
    ln += "\n";
    f.write (ln.c_str (), ln.length ());
    if (f.fail ())
    {   nits.pick (nit_cannot_write, es_error, ec_crc, "cannot write to ", name.string ());
        return false; }
    return true; }

void fileindex_save_and_close (nitpick& nits)
{   if (! context.shadow_enable ()) return;
    PRESUME (! fred.activity (), __FILE__, __LINE__);
    site_x.clear ();
    disk_x.clear ();
    mcrc.clear ();
    if (context.tell (es_all)) outstr.out (fileindex_report ());
    ::boost::filesystem::path name (persist_path ());
    BOOST_FSTREAM_CNSTRO (f, name, ::std::ios::out | ::std::ios::trunc);
    if (f.fail ()) nits.pick (nit_cannot_update, es_error, ec_crc, "cannot open ", name.string ());
    else
    {   mndx_t mndx; ::std::size_t x = 0;
        for (::std::size_t n = 0; n < vx.size (); ++n)
            if ((GSL_AT (vx, n).flags_ & (FX_DELETED | FX_STALE)) == 0)
                mndx.emplace (mndx_t::value_type (n, x++));
        ::std::string ln (FULLNAME "\n" VERSION_STRING "\n");
        ln += context.root ();
        ln += "\n";
        ln += ::boost::lexical_cast < ::std::string > (context.virtuals ().size ());
        ln += "\n";
        for (auto s : context.virtuals ()) { ln += s; ln += "\n"; }
        ln += "-\n";
        ln += ::boost::lexical_cast < ::std::string > (x);
        ln += "\n";
        f.write (ln.c_str (), ln.length ());
        if (f.fail ())
            nits.pick (nit_cannot_write, es_error, ec_crc, "cannot write to ", name.string ());
        else
        {   for (::std::size_t v = 0; v < paths_root::virtual_roots ().size (); ++v)
            {   const ::std::size_t n = paths_root::virtual_roots ().at (v) -> fileindex ();
                if (! write_fileindex_record (nits, f, name, n, mndx)) break; }
            for (::std::size_t n = 0; n < vx.size (); ++n)
                if (GSL_AT (vx, n).v_ < 0)
                    if ((GSL_AT (vx, n).flags_ & (FX_DELETED | FX_STALE)) == 0)
                        if (! write_fileindex_record (nits, f, name, n, mndx)) break; } } }

void dedu (nitpick& nits) // presumes run between scan and examine phases
{   if (context.progress ()) ::std::cout << "Deduplicating\n";  
    for (fileindex_t i = 0; i < vx.size (); ++i)
    {   index_t& x = vx.at (i);
        if ((x.flags_ & (FX_DIR | FX_BORKED | FX_SCANNED)) == 0)
            if (! is_verifiable_file (x.site_path ()))
            {   crc_t crc = get_crc (nits, i);
                if (crc == crc_initrem) continue;
                lox l (lox_fileindex);
                mcrc_t::const_iterator ci = mcrc.find (crc);
                if (ci != mcrc.cend ())
                    if (ci -> second != i)
                    {   const index_t& y = vx.at (ci -> second);
                        if (x.size_ == y.size_)
                        {   if (y.dedu_ == nullfileindex) x.dedu_ = ci -> second;
                            else x.dedu_ = y.dedu_;
                            nits.pick (nit_duplicate, es_info, ec_crc, x.disk_path (), " duplicates ", vx.at (x.dedu_).disk_path ());
                            continue; } }
                mcrc.emplace (crc, i); } } }

bool isdu (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).dedu_ != nullfileindex; }

fileindex_t du (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).dedu_; }

void add_dependency (const fileindex_t ndx, const fileindex_t dependency)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    GSL_AT (vx, ndx).dx_.emplace (dependency); }

void clear_dependencies (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    GSL_AT (vx, ndx).dx_.clear (); }

sndx_t get_dependencies (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).dx_; }

void set_lynx (const fileindex_t ndx, const fileindex_t l)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox lx (lox_fileindex);
    GSL_AT (vx, ndx).lx_.emplace (l); }

void clear_lynx (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    GSL_AT (vx, ndx).lx_.clear (); }

sndx_t get_lynx (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    lox l (lox_fileindex);
    return GSL_AT (vx, ndx).lx_; }

bool needs_update (const fileindex_t ndx, const ::std::time_t& st)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return GSL_AT (vx, ndx).needs_update (st); }

fileindex_t get_fileindex_count ()
{   lox l (lox_fileindex);
    return static_cast < fileindex_t > (vx.size ()); }

bool try_set_flag (const fileindex_t ndx, const fileindex_flags flag)
{   lox l (lox_fileindex);
    if (inner_get_any_flag (ndx, flag)) return false;
    inner_set_flag (ndx, flag);
    return true; }
