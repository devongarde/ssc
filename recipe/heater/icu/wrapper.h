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

#pragma once

class charset_detector_match
{   const UCharsetMatch* match_;
    UErrorCode err_ = U_ZERO_ERROR;
public:
    charset_detector_match () = delete;
    explicit charset_detector_match (const UCharsetMatch* m) : match_ (m) { }
    UErrorCode error () const { return err_; }
    bool valid () const { return error () == U_ZERO_ERROR; }
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
    charset_detector_match at (const int32_t i) const
    {   if ((i < 0) || (i >= count_))
#ifdef __GNUC__
            // I'm not wasting time fighting a f**king gcc bug. If that id**tic compiler can't suss a C string, it can *ff right *ff.
        {   ::std::cerr << "GCC C++ compiler design error revealed by charset_detector_matches overflow. Aborting.\n";
            ::std::exit (3); }
#else //  __GNUC__
            // meanwhile, pragmatic compilers work
            throw ::std::exception ("charset_detector_match at () out of bounds error");
#endif // __GNUC__
        return charset_detector_match (match_ [i]); }
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
    ~charset_detector ()
    {   if (detector_ != nullptr) ucsdet_close (detector_); }
    UCharsetDetector*& operator () () { return detector_; }
    const UCharsetDetector* operator () () const { return detector_; }
    UErrorCode error () const { return err_; }
    bool valid () const { return error () == U_ZERO_ERROR; }
    bool set_text (const char *in, int32_t len)
    {   assert (detector_ != nullptr);
        ucsdet_setText (detector_, in, len, &err_);
        return valid (); }
    charset_detector_matches match_all ()
    {   charset_match_ = ucsdet_detectAll (detector_, &charset_match_count_, &err_);
        return charset_detector_matches (charset_match_, charset_match_count_); }
    int32_t match_count () const {  return charset_match_count_; } };
