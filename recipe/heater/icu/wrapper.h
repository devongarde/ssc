/*
ssc (static site checker)
File Info
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
#include "utility/common.h"

class charset_detector_match
{   const UCharsetMatch* match_;
    UErrorCode err_ = U_ZERO_ERROR;
public:
    charset_detector_match () = delete;
    explicit charset_detector_match (const UCharsetMatch* m) noexcept : match_ (m) { }
    UErrorCode error () const noexcept { return err_; }
    bool valid () const noexcept { return error () <= U_ZERO_ERROR; }
    bool content () const noexcept { return match_ != nullptr; }
    bool might_be (const ::std::string& s);
    const char *name () noexcept { return ucsdet_getName (match_, &err_); }
    int32_t confidence () noexcept { return ucsdet_getConfidence (match_, &err_); }
    const char *language () noexcept { return ucsdet_getLanguage (match_, &err_); } };

class charset_detector_matches
{   const UCharsetMatch** match_;
    int32_t count_ = 0;
public:
    charset_detector_matches () = delete;
    charset_detector_matches (const UCharsetMatch** m, int32_t n) noexcept : match_ (m), count_ (n) { }
    explicit charset_detector_matches (const UCharsetMatch** m) noexcept : match_ (m), count_ (0) { }
    int32_t count () const noexcept { return count_; }
    void count (const int32_t n) noexcept { count_ = n; }
    bool content () const noexcept { return match_ != nullptr; }
    charset_detector_match at (const int32_t i) const;
    charset_detector_match operator [] (const int32_t i) const
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26481)
#endif // _MSC_VER
    {   VERIFY_NOT_NULL (match_, __FILE__, __LINE__);
        return charset_detector_match (match_ [i]); } };
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

class charset_detector
{   UCharsetDetector* detector_ = nullptr;
    UErrorCode err_ = U_ZERO_ERROR;
    const UCharsetMatch** charset_match_ = nullptr;
    int32_t charset_match_count_ = 0;
public:
    charset_detector ()
    {   if (context.icu ()) detector_ = ucsdet_open (&err_); }
    DEFAULT_COPY_CONSTRUCTORS (charset_detector);
    ~charset_detector ()
    {   if (detector_ != nullptr) ucsdet_close (detector_); }
    void swap (charset_detector& cd) noexcept
    {   UCharsetDetector* tmp = detector_;
        detector_ = cd.detector_;
        cd.detector_ = tmp; }
    void reset () noexcept
    {   if (detector_ != nullptr) ucsdet_close (detector_);
        if (context.icu ()) detector_ = ucsdet_open (&err_); }
    void reset (const charset_detector& cd) noexcept
    {   charset_detector tmp (cd);
        swap (tmp); }
    UCharsetDetector*& operator () () noexcept { return detector_; }
    const UCharsetDetector* operator () () const noexcept { return detector_; }
    UErrorCode error () const noexcept { return err_; }
    bool valid () const noexcept { return error () <= U_ZERO_ERROR; }
    bool set_text (const char *in, int32_t len);
    charset_detector_matches match_all () noexcept
    {   UGLY_PRESUME (context.icu (), __FILE__, __LINE__);
        charset_match_ = ucsdet_detectAll (detector_, &charset_match_count_, &err_);
        return charset_detector_matches (charset_match_, charset_match_count_); }
    int32_t match_count () const noexcept {  return charset_match_count_; } };

class converter
{   UConverter* conv_ = nullptr;
    UErrorCode err_ = U_ZERO_ERROR;
public:
    converter () = delete;
    NO_COPY_CONSTRUCTORS (converter);
    explicit converter (const ::std::string& name) noexcept
    {   if (context.icu ()) conv_ = ucnv_open (name.c_str (), &err_); }
    ~converter ()
    {   if (context.icu ()) ucnv_close (conv_); }
    void swap (converter& c) noexcept
    {   UConverter* tmp = conv_;
        conv_ = c.conv_;
        c.conv_ = tmp; }
    void reset () noexcept { if (context.icu ()) ucnv_reset (conv_); }
    void_ptr convert_to (const void_ptr& vp, const uintmax_t sz);
    UErrorCode error () const noexcept { return err_; }
    bool valid () const noexcept
    {   if (! context.icu ()) return false;
        return error () <= U_ZERO_ERROR; } };
