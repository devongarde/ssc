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
#include "main/context.h"
#include "utility/filesystem.h"
#include "utility/quote.h"
#include "webpage/fileindex.h"
#include "webpage/directory.h"

//#define PERSIST_NDX 0
//#define PERSIST_SIZE (PERSIST_NDX + 1)
#define PERSIST_SIZE 0
#define PERSIST_LAST_WRITE (PERSIST_SIZE + 1)
#define PERSIST_FLAGS (PERSIST_LAST_WRITE + 1)
#define PERSIST_CRC (PERSIST_FLAGS + 1)
#define PERSIST_DEPENDENCIES (PERSIST_CRC + 1)
#define PERSIST_LYNX (PERSIST_DEPENDENCIES + 1)
#define PERSIST_ARG_COUNT (PERSIST_LYNX + 1)

#define MJR_LYNX_N_DEPEND 0 // version 0.0.109
#define MNR_LYNX_N_DEPEND 0
#define REL_LYNX_N_DEPEND 109
#define LYNX_N_DEPEND_XTRA 2

#define VX_RESERVE 16384

typedef ssc_map < fileindex_t, fileindex_t > mndx_t;

struct index_t
{   ::boost::filesystem::path disk_path_;
    ::std::string site_path_;
    fileindex_flags flags_ = 0;
    uintmax_t size_ = 0;
    crc_t crc_ = crc_initrem;
    fileindex_t dedu_ = nullfileindex;
    ::std::time_t last_write_ = 0;
    sndx_t dx_, lx_;
    index_t () = default;
    index_t (const index_t& i) = default;
    index_t (index_t&& i) noexcept = default;
    ~index_t () = default;
    index_t& operator = (const index_t& ) = default;
    index_t& operator = (index_t&& ) = default;
    explicit index_t (const ::boost::filesystem::path& p)
        :   disk_path_ (p), flags_ (0), size_ (0), last_write_ (0) { }
    index_t (const ::boost::filesystem::path& p, const fileindex_flags flags, const uintmax_t size, const ::std::time_t& last_write)
        :   disk_path_ (p), flags_ (flags), size_ (size), last_write_ (last_write) { }
    index_t (const ::boost::filesystem::path& p, ::std::string& s, const fileindex_flags flags, const uintmax_t size, const ::std::time_t& last_write, const crc_t& crc, const sndx_t& dx, const sndx_t& lx)
        :   disk_path_ (p), site_path_ (s), flags_ (flags), size_ (size), crc_ (crc), last_write_ (last_write), dx_ (dx), lx_ (lx) { }
    void swap (index_t& i) noexcept
    {   disk_path_.swap (i.disk_path_);
        site_path_.swap (i.site_path_);
        dx_.swap (i.dx_);
        lx_.swap (i.lx_);
        ::std::swap (flags_, i.flags_);
        ::std::swap (size_, i.size_);
        ::std::swap (crc_, i.crc_);
        ::std::swap (dedu_, i.dedu_);
        ::std::swap (last_write_, i.last_write_); }
    void reset ()
    {   index_t i;
        swap (i); }
    void reset (const index_t& ii)
    {   index_t i (ii);
        swap (i); }
    bool needs_update (const ::std::time_t& st) const
    {   for (auto x : dx_)
            if (last_write (x) > st) return true;
        for (auto x : lx_)
            if (last_write (x) > st) return true;
        return false; } };

typedef ::std::vector < index_t > vx_t;
typedef ssc_map < ::std::string, fileindex_t > mxp_t;
typedef ::std::map < crc_t, fileindex_t > mcrc_t;

vx_t vx;
mxp_t site_x, disk_x;  // note ::boost::filesystem::path and ::std::map are not pals
mcrc_t mcrc;

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
    if (! ::gsl::at (vx, ndx).site_path_.empty ()) site_x.erase (::gsl::at (vx, ndx).site_path_);
    if (! ::gsl::at (vx, ndx).disk_path_.empty ()) disk_x.erase (::gsl::at (vx, ndx).disk_path_.string ());
    if (::gsl::at (vx, ndx).crc_ != crc_initrem) mcrc.erase (::gsl::at (vx, ndx).crc_); }

void reindex (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    unindex (ndx);
    if (! ::gsl::at (vx, ndx).site_path_.empty ()) site_x.emplace (mxp_t::value_type (::gsl::at (vx, ndx).site_path_, ndx));
    if (! ::gsl::at (vx, ndx).disk_path_.empty ()) disk_x.emplace (mxp_t::value_type (::gsl::at (vx, ndx).disk_path_.string (), ndx));
    if (get_flag (ndx, FX_CRC))
        if (! get_flag (ndx, (FX_DELETED | FX_BORKED | FX_DIR)))
            if (::gsl::at (vx, ndx).crc_ != crc_initrem)
            {   mcrc.emplace (mcrc_t::value_type (::gsl::at (vx, ndx).crc_, ndx)); return; }
    reset_flag (ndx, FX_CRC); }

void note_deleted (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    reset_flag (ndx, FX_STALE);
    if (! get_flag (ndx, FX_DELETED))
    {   set_flag (ndx, FX_DELETED);
        unindex (ndx); } }

void update_fileindex (const fileindex_t ndx, const fileindex_flags ff)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    index_t& x = ::gsl::at (vx, ndx);
    const ::boost::filesystem::path& name (x.disk_path_);
    fileindex_flags f (ff);
    uintmax_t s = 0;
    ::std::time_t lw = 0;
    if (((f & FX_DELETED) == FX_DELETED) || ! file_exists (name))
    {   f |= FX_DELETED;
        note_deleted (ndx); }
    else if (is_folder (name)) f |= FX_DIR;
#ifndef NOLYNX
    else if (! is_file_linked (name)) f |= FX_LINKED;
#endif // NOLYNX
    else if (! is_file (name)) f |= FX_BORKED;
    else
    {   s = get_file_size (name);
        lw = get_last_write_time (name); }
    x.flags_ = f;
    if ((x.size_ != s) || (::gsl::at (vx, ndx).last_write_ != lw))
    {   if (x.crc_ != crc_initrem)
        {   mcrc.erase (x.crc_); x.crc_ = crc_initrem; }
        x.flags_ &= ~FX_CRC; }
    reset_flag (ndx, FX_STALE);
    x.size_ = s;
    x.last_write_ = lw; }

fileindex_t insert_disk_path (const ::boost::filesystem::path& name, const fileindex_flags flags)
{   if (name.empty ()) return nullfileindex;
    ::boost::filesystem::path canon (canonical_name (name));
    fileindex_t xin = nullfileindex;
    mxp_t::iterator i = disk_x.find (canon.string ());
    if (i != disk_x.cend ()) xin = i -> second;
    else
    {   vx.emplace_back (canon);
        PRESUME (vx.size () > 0, __FILE__, __LINE__);
        xin = vx.size () - 1; }
    update_fileindex (xin, flags);
    reindex (xin);
    return xin; }

fileindex_t insert_directory_path (const ::boost::filesystem::path& name)
{   return insert_disk_path (name, FX_DIR); }

void add_site_path (const ::std::string& name, const fileindex_t s)
{   PRESUME (s < vx.size (), __FILE__, __LINE__);
    if (! compare_no_case (name, ::gsl::at (vx, s).site_path_))
    {   site_x.erase (::gsl::at (vx, s).site_path_);
        ::gsl::at (vx, s).site_path_ = name; }
    auto i = site_x.emplace (name, s);
    if (! i.second) i.first -> second = s; }

fileindex_t get_fileindex (const ::boost::filesystem::path& name)
{   mxp_t :: const_iterator i = disk_x.find (name.string ());
    if (i != disk_x.cend ()) return i -> second;
    return insert_disk_path (name); }

fileindex_t get_fileindex (const ::std::string& name)
{   mxp_t :: const_iterator i = site_x.find (name);
    if (i != site_x.cend ()) return i -> second;
    return nullfileindex; }

::boost::filesystem::path get_disk_path (const fileindex_t ndx)
{   if (ndx >= vx.size ()) return ::boost::filesystem::path ();
    return ::gsl::at (vx, ndx).disk_path_; }

::std::string get_site_path (const fileindex_t ndx)
{   if (ndx >= vx.size ()) return ::std::string ();
    return ::gsl::at (vx, ndx).site_path_; }

fileindex_flags get_flags (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return ::gsl::at (vx, ndx).flags_; }

bool get_flag (const fileindex_t ndx, const fileindex_flags flag)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return (::gsl::at (vx, ndx).flags_ & flag) != 0; }

void set_flag (const fileindex_t ndx, const fileindex_flags flag)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    ::gsl::at (vx, ndx).flags_ |= flag; }

void reset_flag (const fileindex_t ndx, const fileindex_flags flag)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    ::gsl::at (vx, ndx).flags_ &= ~flag; }

uintmax_t get_size (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return ::gsl::at (vx, ndx).size_; }

::std::time_t last_write (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return ::gsl::at (vx, ndx).last_write_; }

crc_t get_crc (nitpick& nits, const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    if (! get_flag (ndx, FX_CRC))
    {   crc_calc crc;
        ::boost::filesystem::ifstream f (::gsl::at (vx, ndx).disk_path_, ::std::ios_base::in);
        if (f.bad ())
        {   nits.pick (nit_cannot_read, es_error, ec_crc, "cannot read ", ::gsl::at (vx, ndx).disk_path_);
            set_crc (ndx, 0);
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
            nits.pick (nit_out_of_memory, es_error, ec_crc, "out of memory reading ", ::gsl::at (vx, ndx).disk_path_);
            set_crc (ndx, 0);
            return crc_initrem; }
#ifdef CLEAN_SHAREDPTR_ARRAY
        while (! f.eof ())
        {   f.read (buf.get (), max);
            const ::std::streamsize s = f.gcount ();
            if (s == 0) break;
            crc.process_bytes (buf.get (), ::gsl::narrow_cast < ::std::size_t > (s)); }
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
    return ::gsl::at (vx, ndx).crc_; }

void set_crc (const fileindex_t ndx, const crc_t& crc)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    ::gsl::at (vx, ndx).crc_ = crc;
    set_flag (ndx, FX_CRC); }

::std::string fileindex_report ()
{   if (context.test ()) return ::std::string ();
    ::std::string res ("\nFile Indices\n");
    if (vx.size () == 0) return ::std::string ();
    for (::std::size_t i = 0; i < vx.size (); ++i)
    {   res += "  ";
        res += ::boost::lexical_cast < ::std::string > (i);
        res += ": ";
        res += ::gsl::at (vx, i).disk_path_.string ();
        res += " (";
        ::std::string flg;
        if ((::gsl::at (vx, i).flags_ & FX_SCANNED) == FX_SCANNED) flg += "S";
        if ((::gsl::at (vx, i).flags_ & FX_EXISTS) == FX_EXISTS) flg += "E";
        if ((::gsl::at (vx, i).flags_ & FX_TESTED) == FX_TESTED) flg += "T";
        if ((::gsl::at (vx, i).flags_ & FX_CRC) == FX_CRC) flg += "C";
        if ((::gsl::at (vx, i).flags_ & FX_DIR) == FX_DIR) flg += "D";
        if ((::gsl::at (vx, i).flags_ & FX_BORKED) == FX_BORKED) flg += "B";
        if ((::gsl::at (vx, i).flags_ & FX_STALE) == FX_STALE) flg += "s";
        if ((::gsl::at (vx, i).flags_ & FX_DELETED) == FX_DELETED) flg += "d";
        if ((::gsl::at (vx, i).flags_ & FX_LINKED) == FX_LINKED) flg += "L";
        if (flg.empty ()) res += "-"; else res += flg;
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (::gsl::at (vx, i).size_);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (::gsl::at (vx, i).crc_);
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (::gsl::at (vx, i).dx_.size ());
        for (auto dx : ::gsl::at (vx, i).dx_)
        {   res += " ";
            res += ::boost::lexical_cast < ::std::string > (dx); }
        res += ",";
        res += ::boost::lexical_cast < ::std::string > (::gsl::at (vx, i).lx_.size ());
        for (auto lx : ::gsl::at (vx, i).lx_)
        {   res += " ";
            res += ::boost::lexical_cast < ::std::string > (lx); }
        res += ",";
        res += ::gsl::at (vx, i).site_path_;
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
{   ::boost::filesystem::path p (persist_path ());
    if (! file_exists (p)) return true;
    ::boost::filesystem::fstream f (p, ::std::ios::in);
    if (f.fail ())
    {   nits.pick (nit_cannot_read, es_error, ec_crc, "cannot open ", p.string ());
        return false; }
    reset_fileindices ();
    enum { fl_prog, fl_version, fl_root, fl_virtual_count, fl_virtual, fl_count, fl_site, fl_disk, fl_data } status = fl_prog;
    constexpr int max = 4096;
    char buf [max] = { 0 };
    fileindex_t count = 0;
    ::std::size_t virtual_count = 0, got = 0;
    ::std::string site;
    ::boost::filesystem::path disk;
    bool whoops = false;
    while (! f.eof ())
    {   buf [0] = 0;
        f.getline (&buf [0], max - 1);
        if (f.eof ()) break;
        if (f.fail ())
        {   nits.pick (nit_cannot_read, es_error, ec_crc, "error reading from ", p.string ());
            ok = false; return false; }
        if ((buf [0] == 0) || (buf [0] == '#')) continue;
        buf [max - 1] = 0;
        switch (status)
        {   case fl_prog :
                if (strcmp (FULLNAME, buf) != 0)
                {   nits.pick (nit_wrong_version, es_error, ec_crc, p.string (), " was not written by " PROG);
                    ok = true; return false; }
                status = fl_version; break;
            case fl_version :
                {   vstr_t a (split_by_charset (&buf [0], "."));
                    if (a.size () != 3)
                    {   nits.pick (nit_cannot_read, es_error, ec_crc, p.string (), " appears corrupt");
                        return false; }
                    else
                    {   vstr_t v (split_by_charset (VERSION_STRING, "."));
                        PRESUME (v.size () == 3, __FILE__, __LINE__);
                        const int mjr = lexical < int > :: cast (a.at (0));
                        const int mnr = lexical < int > :: cast (a.at (1));
                        const int rel = lexical < int > :: cast (a.at (2));
                        if ((VERSION_MAJOR < mjr) || (VERSION_MINOR < mnr) || (VERSION_RELEASE < rel))
                        {   nits.pick (nit_wrong_version, es_error, ec_crc, p.string (), " was written by a more recent version of " PROG);
                            ok = true; return false; }
                        if ((mjr == 0) && (mnr == 0) && (rel < REL_LYNX_N_DEPEND))
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
                if ((buf [0] == '-') && (buf [1] == 0))
                {   if (got < virtual_count)
                    {   nits.pick (nit_virtual_change, es_error, ec_crc, "missing virtual roots; ", p.string (), " appears to be corrupt");
                        whoops = true; }
                    while (got < context.virtuals ().size ())
                    {   nits.pick (nit_virtual_change, es_error, ec_crc, "virtual root ", quote (context.virtuals ().at (got)), " is new");
                        ok = true; whoops = true; ++got; }
                    if (whoops)
                    {   nits.pick (nit_abandon, es_info, ec_crc, p.string (), " is incompatible with " PROG " version " VERSION_STRING "; abandoning load");
                        return false; }
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
                {   vstr_t args (split_by_charset (&buf [0], ","));
                    if (args.size () != PERSIST_ARG_COUNT) break;
                    {   uintmax_t size = lexical < uintmax_t > :: cast (args.at (PERSIST_SIZE));
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
                        vx.emplace_back (disk, site, flags, size, last_write, crc, dx, lx);
                        site.clear (); disk.clear (); }
                    status = fl_site; }
                break;
            default :
                GRACEFUL_CRASH (__FILE__, __LINE__);
                UNREACHABLE (return false); } }
    if (status != fl_site)
    {   vx.clear (); site_x.clear (); disk_x.clear (); mcrc.clear ();
        nits.pick (nit_cannot_read, es_error, ec_crc, p.string (), " is corrupt or truncated; abandoning load");
        reset_fileindices (); return false; }
    vx.shrink_to_fit ();
    if (count < vx.size ())
    {   vx.clear (); site_x.clear (); disk_x.clear (); mcrc.clear ();
        nits.pick (nit_cannot_read, es_catastrophic, ec_crc, p.string (), " is inconsistent; abandoning load");
        reset_fileindices (); return false; }
    count = vx.size ();
    for (fileindex_t ndx = 0; ndx < count; ++ndx)
    {   if (! ::gsl::at (vx, ndx).site_path_.empty ()) site_x.emplace (mxp_t::value_type (::gsl::at (vx, ndx).site_path_, ndx));
        if (! ::gsl::at (vx, ndx).disk_path_.empty ()) disk_x.emplace (mxp_t::value_type (::gsl::at (vx, ndx).disk_path_.string (), ndx));
        if ((::gsl::at (vx, ndx).flags_ & FX_CRC) == FX_CRC)
            if (::gsl::at (vx, ndx).crc_ != crc_initrem)
                mcrc.emplace (mcrc_t::value_type (::gsl::at (vx, ndx).crc_, ndx)); }
    return true; }

bool fileindex_load (nitpick& nits)
{   if (! context.shadow_enable ()) return true;
    bool ok = false;
    if (fileindex_load_internal (nits, ok))
    {   if (context.tell (es_splurge)) context.out () << fileindex_report ();
        return true; }
    if (! ok)
    {   ::boost::filesystem::path p (persist_path ());
        if (file_exists (p))
            if (delete_file (p)) nits.pick (nit_deleted_bad_file, es_info, ec_crc, "deleted bad file ", p.string ());
            else nits.pick (nit_cannot_delete, es_error, ec_crc, "cannot delete bad file ", p.string ()); }
    return false; }

void fileindex_save_and_close (nitpick& nits)
{   if (! context.shadow_enable ()) return;
    site_x.clear ();
    disk_x.clear ();
    mcrc.clear ();
    if (context.tell (es_all)) context.out () << fileindex_report ();
    ::boost::filesystem::path name (persist_path ());
    ::boost::filesystem::fstream f (name, ::std::ios::out | ::std::ios::trunc);
    if (f.fail ()) nits.pick (nit_cannot_update, es_error, ec_crc, "cannot open ", name.string ());
    else
    {   mndx_t mndx; ::std::size_t x = 0;
        for (::std::size_t n = 0; n < vx.size (); ++n)
            if ((::gsl::at (vx, n).flags_ & (FX_DELETED | FX_STALE | FX_DIR)) == 0)
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
        else for (::std::size_t n = 0; n < vx.size (); ++n)
            if ((::gsl::at (vx, n).flags_ & (FX_DELETED | FX_STALE | FX_DIR)) == 0)
            {   index_t& v = ::gsl::at (vx, n);
                ln = ::boost::lexical_cast < ::std::string > (v.site_path_);
                ln += "\n";
                ln += ::boost::lexical_cast < ::std::string > (v.disk_path_.string ());
                ln += "\n";
                ln += ::boost::lexical_cast < ::std::string > (v.size_);  // ensure this write order matches PERSIST_... #defines above
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
                    break; } } } }

void dedu (nitpick& nits)
{   if (context.progress ())
    {   ::std::cout << "Deduplicating ."; context.dedot (); }
    for (fileindex_t i = 0; i < vx.size (); ++i)
    {   index_t& x = vx.at (i);
        if ((x.flags_ & (FX_DIR | FX_BORKED | FX_SCANNED)) == 0)
            if (! is_webpage (x.site_path_, context.extensions ()))
            {   context.dot ();
                crc_t crc = get_crc (nits, i);
                if (crc == crc_initrem) continue;
                mcrc_t::const_iterator ci = mcrc.find (crc);
                if (ci != mcrc.cend ())
                    if (ci -> second != i)
                    {   const index_t& y = vx.at (ci -> second);
                        if (x.size_ == y.size_)
                        {   if (y.dedu_ == nullfileindex) x.dedu_ = ci -> second;
                            else x.dedu_ = y.dedu_;
                            nits.pick (nit_duplicate, es_info, ec_crc, x.disk_path_, " duplicates ", vx.at (x.dedu_).disk_path_);
                            continue; } }
                mcrc.emplace (crc, i); } }
    if (context.progress ())  ::std::cout << ::std::endl; }

bool isdu (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return ::gsl::at (vx, ndx).dedu_ != nullfileindex; }

fileindex_t du (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return ::gsl::at (vx, ndx).dedu_; }

void add_dependency (const fileindex_t ndx, const fileindex_t dependency)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    ::gsl::at (vx, ndx).dx_.emplace (dependency); }

void clear_dependencies (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    ::gsl::at (vx, ndx).dx_.clear (); }

sndx_t get_dependencies (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return ::gsl::at (vx, ndx).dx_; }

void set_lynx (const fileindex_t ndx, const fileindex_t l)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    ::gsl::at (vx, ndx).lx_.emplace (l); }

void clear_lynx (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    ::gsl::at (vx, ndx).lx_.clear (); }

sndx_t get_lynx (const fileindex_t ndx)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return ::gsl::at (vx, ndx).lx_; }

bool needs_update (const fileindex_t ndx, const ::std::time_t& st)
{   PRESUME (ndx < vx.size (), __FILE__, __LINE__);
    return ::gsl::at (vx, ndx).needs_update (st); }
