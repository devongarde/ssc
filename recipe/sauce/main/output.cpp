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
#include "main/output.h"
#include "main/context.h"
#include "parser/text.h"
#include "feedback/nitpick.h"
#include "feedback/nitout.h"
#include "coop/lox.h"
#include "gui/gui-app.h"
#include "utility/fileio.h"

void outstream::dup ()
{   try
    {   const ::std::string on = context.out_name ();
        const ::std::string oc = context.out_copy ();
        if (! oc.empty ())
            if (oc != on)
                if (! duplicate_file (nix_path_to_local (oc), nix_path_to_local (on), BOOST_COPY_OPTION::BOOST_OVERWRITE))
                    ::std::cerr << "cannot copy " << oc << " to " << on << ::std::endl;
                else if (context.tell (es_info)) ::std::cout << oc << " copied to " << on << ::std::endl; }
    catch (const ::std::system_error& e)
    {   ::std::cerr << "system exception " << e.what () << " when closing output." << ::std::endl; }
    catch (const ::std::exception& e)
    {   ::std::cerr << "general exception " << e.what () << " when closing output." << ::std::endl; }
    catch (...)
    {   ::std::cerr << "unknown exception when closing output" << ::std::endl; } }

void outstream::init (nitpick& , const ::std::string& s)
{   name_ = s;
    VERIFY_NOT_NULL (macro.get (), __FILE__, __LINE__);
    macro -> set (nm_general_output, s); }

::std::string outstream::ensane (const ::std::string& s) const
{   if (context.cgi ()) return enwotsit (s);
    return s; }

bool outstream::depre (nitpick& nits)
{   if (! name_.empty () && ! inited_)
    {   
#ifdef SIGNING
        if (status_ == sis_verifying)
        {   if (! ::boost::filesystem::exists (name_))
            {   nits.pick (nit_cannot_open, es_catastrophic, ec_init, "cannot open ", quote (name_), " [5].");
                return false; }
            fos_.reset (new ::std::fstream (name_, ::std::ios_base::binary | ::std::ios_base::in)); }
        else
            fos_.reset (new ::std::fstream (name_, ::std::ios_base::binary | ::std::ios_base::in | ::std::ios_base::out | ::std::ios_base::trunc));
#else // SIGNING
        fos_.reset (new ::std::fstream (name_, ::std::ios_base::out | ::std::ios_base::trunc));
#endif // SIGNING
        if (fos_ -> fail ())
        {   nits.pick (nit_cannot_open, es_catastrophic, ec_init, "cannot open ", quote (name_), " [4].");
            fos_.reset ();
            return false; }
        inited_ = true; }
    if (! pre_.empty ())
    {   
#ifdef SIGNING
        if (status_ == sis_unknown) status_ = sis_none;
#endif // SIGNING
        out (pre_);
        pre_.clear (); }
    return true; }

#ifdef SIGNING
void outstream::consolidate (nitpick& nits, const ::boost::filesystem::path& pub, const ::boost::filesystem::path& pri, const ::std::string& pw, const ::boost::filesystem::path& signature)
{   status_ = sis_none;
    if (! signature.empty ())
        if (pub.empty ()) nits.pick (nit_cannot_read, es_catastrophic, ec_signing, "signing requires both private and public keys; verification requires a public key"); 
        else if (! is_normal_file (pub)) nits.pick (nit_cannot_read, es_catastrophic, ec_signing, pub.string (), ": invalid public key file");
        {   pub_ = pub;
            sig_ = signature;
            if (pri.empty ())
            {   sf_ = svf_sha256_ptr (new svf_sha256 (nits, pub_));
                if (sf_ && ! sf_ -> invalid ())
                    if (! sf_ -> read_sig (sig_))
                        nits.pick (nit_cannot_read, es_catastrophic, ec_signing, sig_.string (), ": invalid signature file");
                    else
                    {   status_ = sis_verifying;
                        if (depre (nits))
                        {   sf_ -> process (fos_); 
                            sf_ -> done ();
                            nits.merge (sf_ -> nits ()); } } }
            else if (! is_normal_file (pri)) nits.pick (nit_cannot_read, es_catastrophic, ec_signing, pri.string (), ": invalid private key file"); 
            else
            {   pri_ = pri;
                sf_ = svf_sha256_ptr (new svf_sha256 (nits, pri_, pub_, pw));
                if (sf_ && ! sf_ -> invalid ())
                    status_ = sis_signing; } }
    depre (nits); }

bool outstream::done (nitpick& nits) noexcept
{   bool ok = false;
    try
    {   if (depre (nits) && (status_ == sis_signing) && ! fos_ -> fail ())
        {   try
            {   VERIFY_NOT_NULL (sf_, __FILE__, __LINE__);
                fos_ -> seekg (0);
                sf_ -> process (fos_);
                if (! sf_ -> invalid ())
                {   sf_ -> done ();
                    sf_ -> write_sig (sig_); }
                nits.merge (sf_ -> nits ());
                ok = sf_ -> success () && ! fos_ -> fail (); } 
            catch (...)
            {   if (sf_) try
                {   nits.merge (sf_ -> nits ()); }
                catch (...) { }
                throw; } } }
    catch (...)
    {   ok = false; }
    if (ok) try
    {   if (fos_ -> is_open ()) fos_ -> close (); }
    catch (...)
    {   ok = false; }
    return ok; }

void outstream::aborting ()
{   if (invalid () && ! pre_.empty ())
    {   ::std::cout << pre_;
        pre_.clear (); } }
#endif // SIGNING

void outstream::out (const ::std::string& s) const
{   lox l (lox_out);
#ifdef WX
    const ::std::string ss (ensane (s));
#else // WX
    const ::std::string ss (s);
#endif // WX
#ifdef SIGNING
    if (status_ == sis_unknown)
    {   pre_ += ss;
        return; }
    if ((status_ != sis_verifying) && ! invalid () && ! context.serve ())
#else // SIGNING
    if (! invalid () && ! context.serve ())
#endif // SIGNING
        *fos_ << ss;
#ifdef WX
    else if (wx_) app -> console (ss);
#endif // WX
    else ::std::cout << ss; }
