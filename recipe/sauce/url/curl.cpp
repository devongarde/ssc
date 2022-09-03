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
#include "url/url.h"
#include "coop/lox.h"

#ifndef NOCURL
typedef ::std::unique_ptr < char [] > curl_buf_t;
::std::size_t buf_rite (char *buffer, ::std::size_t size, ::std::size_t nmemb, char *stream);

class curly  // presumes lox_curl surrounding the whole thing / must move to curl_share once this code goes
{   static CURL* c_;
    static ::std::size_t pos_;
    curl_buf_t buf_;
public:
    curly ()
    {   pos_ = 0;
        PRESUME (valid (), __FILE__, __LINE__); } 
    curly (const curly& ) = delete;
    curly (curly&& ) = delete;
    curly& operator = (const curly& ) = delete;
    curly& operator = (curly&& ) = delete;
    ~curly ()
    {   if (c_ != nullptr) curl_easy_reset (c_); }
    static void init ()
    {   PRESUME (c_ == nullptr, __FILE__, __LINE__);
        curl_global_init (CURL_GLOBAL_DEFAULT);
        c_ = curl_easy_init (); }
    static void done ()
    {   curl_easy_cleanup (c_);
        c_ = nullptr;
        curl_global_cleanup (); }
    CURLcode opt (CURLoption option, const ::std::string& s)
    {   PRESUME (valid (), __FILE__, __LINE__);
        return curl_easy_setopt (c_, option, s.c_str ()); }
    CURLcode opt (CURLoption option, int i)
    {   PRESUME (valid (), __FILE__, __LINE__);
        return curl_easy_setopt (c_, option, static_cast < long > (i)); }
    bool set_write_buffer ()
    {   PRESUME (valid (), __FILE__, __LINE__);
        PRESUME (buf_.get () == nullptr, __FILE__, __LINE__);
        const long size = context.max_file_size ();
        buf_ = curl_buf_t (new char [size]);
        pos_ = 0;
        return  (curl_easy_setopt (c_, CURLOPT_INFILESIZE, size) == CURLE_OK) &&
                (curl_easy_setopt (c_, CURLOPT_WRITEDATA, buf_.get ()) == CURLE_OK) &&
                (curl_easy_setopt (c_, CURLOPT_WRITEFUNCTION, &buf_rite) == CURLE_OK); }
    const curl_buf_t& buf () const { return buf_; }
    static ::std::size_t pos () { return pos_; }
    static void pos (const ::std::size_t p) { pos_ = p; }
    CURLcode engage ()
    {   PRESUME (valid (), __FILE__, __LINE__);
        return curl_easy_perform (c_); }
    int status ()
    {   PRESUME (valid (), __FILE__, __LINE__);
        long status = 0;
        curl_easy_getinfo (c_, CURLINFO_RESPONSE_CODE, &status);
        return static_cast <int > (status); }
    bool valid () const { return c_ != nullptr; } };

CURL* curly::c_ = nullptr;
::std::size_t curly::pos_ = 0;

void curl_init ()
{   PRESUME (! fred.started (), __FILE__, __LINE__);
    curly::init (); }

void curl_done ()
{   curly::done (); }

::std::size_t buf_rite (char *buffer, ::std::size_t size, ::std::size_t nmemb, char *stream)
{   const ::std::size_t r = size * nmemb;
    const ::std::size_t offset = curly::pos ();
    if (offset + r > context.max_file_size ()) return 0; // lie through our e***ing teeth
    memcpy (stream + offset, buffer, r);
    curly::pos (offset + r);  
    return r; }

int curl_do (curly& c, nitpick& nits, const url&u, bool verify_ssl, ::std::string* content = nullptr)
{   if (verify_ssl || (c.opt (CURLOPT_SSL_OPTIONS, CURLSSLOPT_NO_REVOKE) == CURLE_OK))
    {   const CURLcode res = c.engage ();
        switch (c.engage ())
        {   case CURLE_OK :
                if ((content != nullptr) && (c.pos () > 0))
                {   VERIFY_NOT_NULL (content, __FILE__, __LINE__);
                    *content = ::std::string (c.buf ().get (), c.pos ()); }
                return 0;
            case CURLE_HTTP_RETURNED_ERROR :
                return c.status ();
            default :
                {   const char *msg = curl_easy_strerror (res);
                    if (msg == nullptr) nits.pick (nit_http_error, es_error, ec_crc, "unknown error accessing ", u.original ());
                    else nits.pick (nit_http_error, es_error, ec_crc, "error accessing ", u.original (), ": ", msg);
                    break; } } }
    return -1; }

int curl_test (nitpick& nits, const url& u, bool verify_ssl)
{   curly c;
#ifdef CURL_SSL_NOT_THREADSAFE
    lox l (lox_curl);
#endif // CURL_SSL_NOT_THREADSAFE
    if (c.valid ())
        if ((c.opt (CURLOPT_URL, u.original ()) == CURLE_OK) &&
            (c.opt (CURLOPT_FOLLOWLOCATION, 0) == CURLE_OK) &&
            (c.opt (CURLOPT_NOBODY, 1) == CURLE_OK) &&
            (c.opt (CURLOPT_FAILONERROR, 1) == CURLE_OK) &&
            (c.opt (CURLOPT_NOPROGRESS, 1) == CURLE_OK))
                return curl_do (c, nits, u, verify_ssl);
    return -1; }

int curl_fetch (nitpick& nits, const url& u, bool verify_ssl, ::std::string& content)
{   curly c;
#ifdef CURL_SSL_NOT_THREADSAFE
    lox l (lox_curl);
#endif // CURL_SSL_NOT_THREADSAFE
    if (c.valid ())
        if ((c.opt (CURLOPT_URL, u.original ()) == CURLE_OK) &&
            (c.opt (CURLOPT_FOLLOWLOCATION, 1) == CURLE_OK) &&
            (c.opt (CURLOPT_FAILONERROR, 1) == CURLE_OK) &&
            (c.opt (CURLOPT_NOPROGRESS, 1) == CURLE_OK) &&
            (c.opt (CURLOPT_INFILESIZE, context.max_file_size ()) == CURLE_OK))
                return curl_do (c, nits, u, verify_ssl, &content);
    return -1; }
#endif //NOCURL
