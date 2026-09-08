/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "utility/common.h"
#include "utility/fileio.h"
#include "utility/filesystem.h"
#include "utility/byteorder.h"
#include "utility/lexical.h"
#include "main/context.h"
#include "main/args.h"
#include "icu/converter.h"

bool test_file (nitpick& nits, const ::boost::filesystem::path& name, uintmax_t& mz)
{   using namespace ::boost::filesystem;
    try
    {   path p (name);
        if (! exists (p)) nits.pick (nit_cannot_open, es_catastrophic, ec_io, PROG " cannot access ", name.string ());
        else if (! is_normal_file (p)) nits.pick (nit_cannot_open, es_catastrophic, ec_io, name.string (), " is not a normal file");
        else
        {   mz = file_size (p);
            if ((context.max_file_size () == 0) || (mz <= context.max_file_size ())) return true;
            nits.pick (nit_too_big, es_catastrophic, ec_io, name.string (), " is too big (reconfigure with " GENERAL MAXFILESIZE ")"); } }
    catch (...) { }
    return false; }

::std::string read_text_file (nitpick& nits, const ::boost::filesystem::path& name, bool& borked)
{   borked = false;
    try
    {   ::boost::filesystem::path p (name);
        uintmax_t mz = 0;
        if (test_file (nits, p, mz))
            if (mz == 0) nits.pick (nit_empty, es_comment, ec_io, name.string (), " is empty");
            else
            {   BOOST_IFSTREAM_CNSTRO (f, name, ::std::ios_base::in);
                if (! f.bad ())
                {   ::std::stringstream sss;
                    sss << f.rdbuf ();
                    f.close ();
                    ::std::string res (sss.str ());
                    const e_charcode encoding = bom_to_encoding (get_byte_order (res));
                    if (encoding != cc_ansi)
#ifndef NOICU
                        if (! context.icu ())
#endif // NOICU
                        {   if (encoding != cc_utf8)
                            {   if (encoding == cc_fkd) nits.pick (nit_convert, es_error, ec_file, p.string (), " is in a strange format, so " PROG " cannot process it; " PROG " likes ASCII, ANSI & UTF-8");
                                else nits.pick (nit_convert, es_error, ec_file,  PROG " cannot convert ", p.string (), " to UTF-8, so cannot to process it");
                                borked = true;
                                res.clear (); } }
#ifndef NOICU
                        else if (encoding == cc_utf8)
                        {   nitpick nuts;
                            ::std::string norm = normalise_utf8 (nuts, res);
                            if ((norm != res) && ! context.test ()) // dependent on host system, ignore in tests
                            {   nits.pick (nit_normalise, es_warning, ec_icu, quote (p.string ()), " does not appear to be normalised UTF-8");
                                nits.pick (nit_normalise, es_debug, ec_icu, "differences: ", string_diff (res, norm, true));
                                res = norm; } }
                        else
                        {   res.clear ();
                            uintmax_t sz = 0;
                            void_ptr vp (read_binary_file (nits, p, sz));
                            if (sz != 0)
                            {   VERIFY_NOT_NULL (vp.get (), __FILE__, __LINE__);
                                res = convert_to_utf8 (nits, p.string (), vp, sz);
                                if (res.empty ())
                                {   nits.pick (nit_convert, es_error, ec_file, PROG " cannot analyse ", p.string (), " because it's in a weird format; " PROG " likes ASCII, ANSI, UTF-8, & UTF-16");
                                    borked = true; }
                                else
                                    nits.pick (nit_convert, es_comment, ec_page, "Converted ", p.string (), " to UTF-8 internally"); } }
#endif // NOICU
                    return res; } } }
    catch (const ::std::exception& e)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "exception when reading ", name.string (), ": ", e.what ()); }
    catch (...)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "unknown exception when reading ", name.string ()); }
    borked = true;
    return ::std::string (); }

::std::string read_text_file (nitpick& nits, const ::std::string& name, bool& borked)
{   return read_text_file (nits, ::boost::filesystem::path (name), borked); }

void_ptr read_binary_file (nitpick& nits, const ::boost::filesystem::path& name, ::std::size_t& sz, const bool zero_ok)
{   using namespace ::boost::filesystem;
    if (name.empty ())
    {   context.os () -> err ("No filename to read\n");
        nits.pick (nit_cannot_open, es_catastrophic, ec_io, "No filename to read"); } 
    else
    {   FILE* fp = nullptr;
        sz = 0;
        try
        {   path p (name);
            uintmax_t daft = 0;
            if (test_file (nits, p, daft))
                if (daft == 0)
                    if (zero_ok) nits.pick (nit_empty, es_comment, ec_io, name.string (), " is empty");
                    else nits.pick (nit_empty, es_error, ec_io, name.string (), " is empty");
                else if (daft >= UINT_MAX)
                    nits.pick (nit_too_big, es_catastrophic, ec_io, name.string (), " is too big");
                else
                {   const ::std::size_t mz = GSL_NARROW_CAST < ::std::size_t > (daft);
                    void_ptr vp (alloc_void_ptr (mz));
                    if (vp.get () == nullptr) nits.pick (nit_out_of_memory, es_catastrophic, ec_io, "out of memory reading ", name.string ());
                    else
                    {   fp = fopen (name.string ().c_str (), "rb");
                        if (fp == nullptr) nits.pick (nit_cannot_open, es_catastrophic, ec_io, "cannot open ", quote (name.string ()), " [1]");
                        else
                        {   const ::std::size_t rd = fread (vp.get (), 1, mz, fp);
                            fclose (fp); // if this fails there's sod all we can do about it, so ... :-)
                            fp = nullptr;
                            if (rd == mz) { sz = mz; return vp; }
                            if (rd == 0) nits.pick (nit_cannot_read, es_catastrophic, ec_io, "cannot read any of ", name.string ());
                            else nits.pick (nit_cannot_read, es_catastrophic, ec_io, "cannot read all of ", name.string ()); } } } }
        catch (const ::std::exception& e)
        {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "exception when reading ", name.string (), ": ", e.what ());
            return void_ptr (); }
        catch (...)
        {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "unknown exception when reading ", name.string ());
            return void_ptr (); }
        if (fp != nullptr) fclose (fp); }
    return void_ptr (); }

bool write_text_file (nitpick& nits, const ::boost::filesystem::path& n, const ::std::string& content)
{   using namespace ::boost::filesystem;
    if (n.empty ()) nits.pick (nit_cannot_open, es_catastrophic, ec_io, "No filename to write");
    else
    {   path p (n);
        p += ".tmp";
        try
        {   BOOST_OFSTREAM_CNSTR (f, p);
            if (f.bad ())
            {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "Cannot open temporary file ", p.string ()); 
                return false; }
            try
            {   f << content; }
            catch (...)
            {   nits.pick (nit_cannot_write, es_catastrophic, ec_io, "Cannot write to temporary file ", p.string ());
                return false; }
            f.close ();
            if (file_exists (n))
                if (! delete_file (n))
                {   nits.pick (nit_cannot_delete, es_catastrophic, ec_io, "Cannot delete existing file ", p.string ());
                    return false; }
            rename_file (p, n);
            return true; }
        catch (...) { }
        if (file_exists (p)) delete_file (p);
        if (context.tell (es_error))
            nits.pick (nit_cannot_update, es_catastrophic, ec_io, "Cannot update ", p.string ()); }
    return false; }

bool write_text_file (nitpick& nits, const ::std::string& name, const ::std::string& content)
{   return write_text_file (nits, ::boost::filesystem::path (name), content); }

bool write_binary_file (nitpick& nits, const ::boost::filesystem::path& n, const void* content, const ::std::size_t sz)
{   using namespace ::boost::filesystem;
    VERIFY_NOT_NULL (content, __FILE__, __LINE__);
    if (n.empty ())
        nits.pick (nit_cannot_open, es_catastrophic, ec_io, "No filename to write");
    else
    {   FILE* fp = nullptr;
        path p (n);
        p += ".tmp";
        try
        {   fp = fopen (p.string ().c_str (), "wb");
            if (fp == nullptr)
            {   nits.pick (nit_cannot_open, es_catastrophic, ec_io, "cannot open ", quote (n.string ()), " to write [1]");
                return false; }
            else try
            {   const ::std::size_t rd = fwrite (content, 1, sz, fp);
                if (rd < sz)
                {   nits.pick (nit_cannot_write, es_catastrophic, ec_io, "Cannot write all content to temporary file ", p.string ());
                    fclose (fp);
                    return false; } }
            catch (...)
            {   try { fclose (fp); } catch (...) { }
                nits.pick (nit_cannot_write, es_catastrophic, ec_io, "Cannot write to temporary file ", p.string ());
                return false; }
            try
            {   fclose (fp); } // if this fails there's sod all we can do about it, so ... :-)
            catch (...)
            {   nits.pick (nit_cannot_write, es_catastrophic, ec_io, "Cannot close temporary file ", p.string ());
                return false; }
            fp = nullptr;
            if (file_exists (n))
                if (! delete_file (n))
                {   nits.pick (nit_cannot_delete, es_catastrophic, ec_io, "Cannot delete existing file ", p.string ());
                    return false; }
            rename_file (p, n);
            return true; }
        catch (...) { }
        if (file_exists (p)) delete_file (p);
        if (context.tell (es_error))
            nits.pick (nit_cannot_update, es_catastrophic, ec_io, "Cannot update ", p.string ()); }
    return false; }
