/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
    explicit charset_detector_match (const UCharsetMatch* m) : match_ (m) { }
    UErrorCode error () const { return err_; }
    bool valid () const { return error () <= U_ZERO_ERROR; }
    bool content () const { return match_ != nullptr; }
    bool might_be (const ::std::string& s);
    const char *name () { return ucsdet_getName (match_, &err_); }
    int32_t confidence () { return ucsdet_getConfidence (match_, &err_); }
    const char *language () { return ucsdet_getLanguage (match_, &err_); } };

class charset_detector_matches
{   const UCharsetMatch** match_;
    int32_t count_ = 0;
public:
    charset_detector_matches () = delete;
    charset_detector_matches (const UCharsetMatch** m, int32_t n) : match_ (m), count_ (n) { }
    explicit charset_detector_matches (const UCharsetMatch** m) : match_ (m), count_ (0) { }
    int32_t count () const { return count_; }
    void count (const int32_t n) { count_ = n; }
    bool content () const { return match_ != nullptr; }
    charset_detector_match at (const int32_t i) const;
    charset_detector_match operator [] (const int32_t i) const
    {   return charset_detector_match (match_ [i]); } };

class charset_detector
{   UCharsetDetector* detector_ = nullptr;
    UErrorCode err_ = U_ZERO_ERROR;
    const UCharsetMatch** charset_match_ = nullptr;
    int32_t charset_match_count_ = 0;
public:
    charset_detector ()
    {   detector_ = ucsdet_open (&err_); }
    charset_detector (const charset_detector& cd) = default;
    charset_detector (charset_detector&& cd) = default;
    charset_detector& operator = (const charset_detector& cd) = default;
    charset_detector& operator = (charset_detector&& cd) = default;
    ~charset_detector ()
    {   if (detector_ != nullptr) ucsdet_close (detector_); }
    void swap (charset_detector& cd)
    {   UCharsetDetector* tmp = detector_;
        detector_ = cd.detector_;
        cd.detector_ = tmp; }
    void reset ()
    {   if (detector_ != nullptr) ucsdet_close (detector_);
        detector_ = ucsdet_open (&err_); }
    void reset (const charset_detector& cd)
    {   charset_detector tmp (cd);
        swap (tmp); }
    UCharsetDetector*& operator () () { return detector_; }
    const UCharsetDetector* operator () () const { return detector_; }
    UErrorCode error () const { return err_; }
    bool valid () const { return error () <= U_ZERO_ERROR; }
    bool set_text (const char *in, int32_t len);
    charset_detector_matches match_all ()
    {   charset_match_ = ucsdet_detectAll (detector_, &charset_match_count_, &err_);
        return charset_detector_matches (charset_match_, charset_match_count_); }
    int32_t match_count () const {  return charset_match_count_; } };

class converter
{   UConverter* conv_ = nullptr;
    UErrorCode err_ = U_ZERO_ERROR;
public:
    converter () = delete;
    explicit converter (const ::std::string& name)
    {   conv_ = ucnv_open (name.c_str (), &err_); }
    converter (const converter& c) = delete;
    converter (converter&& c) = default;
    converter& operator = (const converter& c) = delete;
    converter& operator = (converter&& c) = default;
    ~converter ()
    {   ucnv_close (conv_); }
    void swap (converter& c)
    {   UConverter* tmp = conv_;
        conv_ = c.conv_;
        c.conv_ = tmp; }
    void reset () { ucnv_reset (conv_); }
    bool convert_to (void_ptr& vp, uintmax_t& sz);
    UErrorCode error () const { return err_; }
    bool valid () const { return error () <= U_ZERO_ERROR; } };
