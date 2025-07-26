/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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

#pragma once

class nitpick;

#ifdef SIGNING
#include "utility/filesystem.h"

template < class XYZ, void (*FN) (XYZ*) > struct signing_key : fcn_dtor < XYZ, FN >
{   typedef ::std::shared_ptr < signing_key < XYZ, FN > > ptr;
    NO_DEFCON (signing_key);
    signing_key (nitpick& nits, const ::boost::filesystem::path& src, const ::std::string& pw) : fcn_dtor < XYZ, FN > ()
    {   fancy_FILE f (nits, src);
        if (! f.invalid ())
            if (pw.empty ()) fcn_dtor < XYZ, FN > :: reset (PEM_read_PrivateKey (f.fp (), nullptr, nullptr, nullptr));
            else fcn_dtor < XYZ, FN > :: reset (PEM_read_PrivateKey (f.fp (), nullptr, nullptr, (void *) pw.data ())); } };

typedef signing_key < EVP_PKEY, EVP_PKEY_free > evp_key;
typedef ::std::shared_ptr < evp_key > evp_key_ptr;

template < class XYZ, void (*FN) (XYZ*) > struct verify_key : fcn_dtor < XYZ, FN >
{   typedef ::std::shared_ptr < verify_key < XYZ, FN > > ptr;
    NO_DEFCON (verify_key);
    verify_key (nitpick& nits, const ::boost::filesystem::path& src) : fcn_dtor < XYZ, FN > ()
    {   fancy_FILE f (nits, src);
        if (! f.invalid ())
            fcn_dtor < XYZ, FN > :: reset (PEM_read_PUBKEY (f.fp (), nullptr, nullptr, nullptr)); } };

typedef verify_key < EVP_PKEY, EVP_PKEY_free > evf_key;
typedef ::std::shared_ptr < evf_key > evf_key_ptr;

template < class KEY, class XYZ, void (*FN_CTX) (XYZ*) > struct key_use
{   typedef ::std::shared_ptr < KEY > key_ptr;
    typedef fcn_dtor < XYZ, FN_CTX > ctx_t;
    ctx_t ctx_;
    nitpick nits_;
    key_ptr key_;
    ::std::size_t data_count_ = 0;
    explicit key_use (const key_ptr& key) : key_ (key)
    {   if (! key) return;
        PRESUME (! key_ -> invalid (), __FILE__, __LINE__);
        ctx_.reset (EVP_MD_CTX_new ());
        if (ctx_.invalid ()) nits_.pick (nit_ssl_sulking, es_catastrophic, ec_signing, "SSL preparation failure"); }
    void reset ()
    {   ctx_.reset (); }
    void step (const unsigned char* puc, const ::std::size_t sz)
    {   if (! invalid ())
        {   data_count_ += sz;
            if (EVP_DigestUpdate (ctx_.data (), puc, sz) != 1)
            {   nits_.pick (nit_ssl_sulking, es_catastrophic, ec_signing, "SSL failure while signing");
                ctx_.reset (); } } }
    const nitpick& nits () const { return nits_; }
    const XYZ* data () const { return ctx_.data (); }
    XYZ* data () { return ctx_.data (); }
    operator bool () const { return ctx_.data () != nullptr; }
    ::std::size_t data_count () const { return data_count_; }
    bool invalid () const { return ctx_.invalid (); } };

template < class PRIVATE, class PUBLIC, const EVP_MD* (*CODE) (), class XYZ, void (*FN_CTX) (XYZ*) > class signature_stream 
{   
public:
    typedef ::std::shared_ptr < PRIVATE > pri_ptr;
    typedef ::std::shared_ptr < PUBLIC > pub_ptr;
private:
    void_ptr signature_;
    ::std::size_t sig_sz_ = 0;
    nitpick nits_;
    bool success_ = false;
    const bool signing_ = false;
    key_use < PRIVATE, XYZ, FN_CTX > private_;
    key_use < PUBLIC, XYZ, FN_CTX > public_;
    void private_init (pri_ptr& pri)
    {   if (pri)
            if (! private_.invalid ())
                if (EVP_DigestSignInit (private_.data (), nullptr, (*CODE) (), nullptr, pri -> data ()) != 1)
                {   nits_.pick (nit_ssl_sulking, es_error, ec_signing, "SSL verification failure: is the private key valid?");
                    private_.reset (); } }
    void public_init (pub_ptr& pub)
    {   if (pub)
            if (! public_.invalid ())
            {   if (EVP_DigestVerifyInit (public_.data (), nullptr, (*CODE) (), nullptr, pub -> data ()) == 1) return;
                else nits_.pick (nit_ssl_sulking, es_error, ec_signing, "SSL verification failure: is the public key valid?");
                public_.reset (); } }
public:
    DELETE_CONSTRUCTORS (signature_stream);
    explicit signature_stream (pri_ptr& pri, pub_ptr& pub) : public_ (pub), private_ (pri), signing_ (true)
    {   private_init (pri);
        public_init (pub); }
    explicit signature_stream (pub_ptr& pub) : public_ (pub), private_ (nullptr), signing_ (false)
    {   public_init (pub); }
    void process (fstr_p& fos)
    {   PRESUME (fos -> is_open (), __FILE__, __LINE__);
        PRESUME (fos -> good () || fos -> eof (), __FILE__, __LINE__);
        if (! invalid ())
        {   void_ptr buf (alloc_void_ptr (DMFS_BYTES));
            ::std::streamsize sz = DMFS_BYTES;
            if (buf)
            {   do
                {   fos -> get ((char *) buf.get (), DMFS_BYTES, 0);
                    if (! fos -> good ()) sz = fos -> gcount ();
                    if (sz > 0) 
                    {   if (signing_) private_.step ((unsigned char *) buf.get (), sz);
                        public_.step ((unsigned char *) buf.get (), sz); } 
                } while ((sz == DMFS_BYTES) && ! invalid ()); } } }
    void done () noexcept
    {   try
        {   nits_.merge (private_.nits ());
            nits_.merge (public_.nits ()); }
        catch (...)
        {   success_ = false; }
        try
        {   if (signing_ && ! private_.invalid ())
                if (EVP_DigestSignFinal (private_.data (), nullptr, &sig_sz_) != 1)
                    nits_.pick (nit_ssl_sulking, es_catastrophic, ec_signing, "SSL failure calculating signature size");
                else
                {   signature_ = alloc_void_ptr (sig_sz_);
                    if (EVP_DigestSignFinal (private_.data (), (unsigned char *) signature_.get (), &sig_sz_) == 1)
                    {   success_ = ! public_.invalid ();
                        nits_.pick (nit_sign_status, es_info, ec_signing, "output signed"); }
                    else
                    {   nits_.pick (nit_sign_status, es_error, ec_signing, "output signing failure");
                        signature_.reset (); } }
            if ((success_ || ! signing_) && ! public_.invalid ())
            {   PRESUME (sig_sz_ > 0, __FILE__, __LINE__);
                success_ = false;
                if (EVP_DigestVerifyFinal (public_.data (), (unsigned char *) signature_.get (), sig_sz_) == 1)
                {   nits_.pick (nit_verify_status, es_info, ec_signing, "output signature verified");
                    success_ = true; }
                else nits_.pick (nit_verify_status, es_error, ec_signing, "output signature verification failure"); }
            nits_.pick (nit_signature_key, es_debug, ec_signing, "verify data: ", private_.data_count (), ", signature: ", sig_sz_); }
        catch (...)
        {   success_ = false; } }
    const void_ptr signature (::std::size_t* sz = nullptr) const { if (sz != nullptr) *sz = sig_sz_; return signature_; }
    void signature (void_ptr ptr, const ::std::size_t sz) // unclean
    try
    {   sig_sz_ = sz;
        signature_ = ptr; }
    catch (...)
    {   signature_.reset (); sig_sz_ = 0; }
    bool invalid () const { return (signing_ && private_.invalid ()) || public_.invalid (); }
    bool success () const noexcept { return success_; }
    bool signing () const noexcept { return signing_; }
    const nitpick& nits () const { return nits_; }
    nitpick& nits () { return nits_; } };

typedef signature_stream < evp_key, evf_key, EVP_sha256, EVP_MD_CTX, EVP_MD_CTX_free > sv_sha256;
typedef signature_stream < evp_key, evf_key, EVP_sha512, EVP_MD_CTX, EVP_MD_CTX_free > sv_sha512;
typedef ::std::shared_ptr < sv_sha256 > sv_sha256_ptr;
typedef ::std::shared_ptr < sv_sha512 > sv_sha512_ptr;

template < class PRIVATE, class PUBLIC, const EVP_MD* (*CODE) (), class XYZ, void (*FN_CTX) (XYZ*) > class signature_file 
{   typedef signature_stream < PRIVATE, PUBLIC, CODE, XYZ, FN_CTX > sf_ss_t;
    typedef ::std::shared_ptr < sf_ss_t > ss_sf_ptr;
    typename sf_ss_t::pri_ptr pri_;
    typename sf_ss_t::pub_ptr pub_;
    ss_sf_ptr ss_;
public:
    DELETE_CONSTRUCTORS (signature_file);
    explicit signature_file (nitpick& nits, const ::boost::filesystem::path& pri, const ::boost::filesystem::path& pub, const ::std::string& pw = ::std::string ())
    {   pri_ = sf_ss_t::pri_ptr (new PRIVATE (nits, pri, pw)); 
        pub_ = sf_ss_t::pub_ptr (new PUBLIC (nits, pub));
        if (pri_ && pub_)
            if (! pri_ -> invalid () && ! pub_ -> invalid ())
                ss_ = ss_sf_ptr (new sf_ss_t (pri_, pub_)); }
    explicit signature_file (nitpick& nits, const ::boost::filesystem::path& pub)
    {   pub_ = sf_ss_t::pub_ptr (new PUBLIC (nits, pub));
        if (pub_)
            if (! pub_ -> invalid ())
                ss_ = ss_sf_ptr (new sf_ss_t (pub_)); }
    void process (fstr_p& fos)
    {   if (! invalid ())
            ss_ -> process (fos); }
    void done () 
    {   if (! invalid ())
            ss_ -> done (); }
    bool invalid () const
    {   return (ss_.get () == nullptr) || ss_ -> invalid (); }
    const void_ptr signature (::std::size_t& sz) const
    {   PRESUME (! invalid (), __FILE__, __LINE__);
        return ss_ -> signature (&sz); }
    bool read_sig (const ::boost::filesystem::path& f)
    {   if (! invalid ())
        {   ::std::size_t sz = 0;
            void_ptr v = read_binary_file (ss_ -> nits (), f, sz);
            if (v)
            {   ss_ -> signature (v, sz);
                return true; } }
        return false; }
    bool write_sig (const ::boost::filesystem::path& f)
    {   if (! invalid ())
        {   ::std::size_t sz = 0;
            void_ptr sig (ss_ -> signature (&sz));
            if (sz > 0)
                return write_binary_file (ss_ -> nits (), f, sig, sz); }
        return false; }
    bool success () const noexcept
    {   return ! invalid () && ss_ -> success (); }
    bool signing () const noexcept
    {   return ! invalid () && ss_ -> signing (); }
    const nitpick& nits () const
    {   PRESUME (! invalid (), __FILE__, __LINE__);
        return ss_ -> nits (); } };

typedef signature_file < evp_key, evf_key, EVP_sha256, EVP_MD_CTX, EVP_MD_CTX_free > svf_sha256;
typedef signature_file < evp_key, evf_key, EVP_sha512, EVP_MD_CTX, EVP_MD_CTX_free > svf_sha512;
typedef ::std::shared_ptr < svf_sha256 > svf_sha256_ptr;
typedef ::std::shared_ptr < svf_sha512 > svf_sha512_ptr;

#endif // SIGNING
