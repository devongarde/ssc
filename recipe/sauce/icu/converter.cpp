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

#include "main/standard.h"

#ifndef NOICU
#include "main/context.h"
#include "icu/converter.h"
#include "icu/charset.h"
#include "icu/wrapper.h"
#include "utility/common.h"
#include "utility/quote.h"

::std::string get_standard_converter_name (nitpick& nits, const ::std::string& name)
{   if (context.icu ())
    {   static ::std::atomic_int converter_count (0);
        if (converter_count == 0)
        {   converter_count = ucnv_countAvailable ();
            if (converter_count == 0)
            {   nits.pick (nit_no_converters, es_info, ec_icu, "no ICU converters available");
                return ::std::string (); } } // or should SSC drop out?
        UErrorCode err = U_ZERO_ERROR;
        ::std::string res (ucnv_getStandardName (name.c_str (), "IANA", &err));
        if (err <= U_ZERO_ERROR) return res;
        nits.pick (nit_icu, es_catastrophic, ec_icu, "ICU ucnv_getStandardName error ", static_cast < int > (err)); }
    return ::std::string (); }

::std::string convert_to_utf8 (nitpick& nits, const ::std::string& name, const void_ptr& vp, const uintmax_t& sz)
{   PRESUME (context.icu (), __FILE__, __LINE__);
    PRESUME (sz > 0, __FILE__, __LINE__);
    PRESUME (vp != nullptr, __FILE__, __LINE__);
    ::std::string cs (identify_probable_charset (vp, sz));
    if (cs.empty ())
        nits.pick (nit_icu, es_error, ec_icu, "cannot identify charset in ", name, "; will hope for the best");
    else
    {   if (cs == UTF_8) return cs;
        converter conv (cs);
        if (! conv.valid ())
            nits.pick (nit_icu, es_catastrophic, ec_icu, "ICU constructor error ", static_cast < int > (conv.error ()), " converting ", name);
        else
        {   void_ptr res (conv.convert_to (vp, sz));
            if (res.get () != nullptr)
            {   ::std::string s (static_cast < char* > (res.get ()));
                return s; }
            nits.pick (nit_icu, es_catastrophic, ec_icu, "ICU error ", static_cast < int > (conv.error ()), " converting ", name); } }
    return ::std::string (); }

::std::string convert_to_utf8 (const unsigned int n)
{   const ::std::wstring u1 (1, GSL_NARROW_CAST < wchar_t > (n));
    ::std::wstring_convert < ::std::codecvt_utf8 <wchar_t>, wchar_t > conv;
    return conv.to_bytes (u1); }

::std::string convert_to_utf8 (const ::std::wstring& s)
{   ::std::wstring_convert < ::std::codecvt_utf8 <wchar_t>, wchar_t > conv;
    return conv.to_bytes (s); }

::std::wstring convert_from_utf8 (const ::std::string& s)
{   ::std::wstring_convert < ::std::codecvt_utf8 <wchar_t>, wchar_t > conv;
    return conv.from_bytes (s); }

#ifdef _MSC_VER
::std::string normalise_utf8 (nitpick& nits, const ::std::string& s)
{   if (! context.icu ()) return s;
    ::std::wstring res16, s16 = convert_from_utf8 (s);
    const ::std::wstring::size_type mx = s16.length () * 4;  // because life's a bitch
    GSL_OWNER (wchar_t) pch = new wchar_t [mx];
    try
    {   const int len = ::NormalizeString (NormalizationC , s16.c_str (), GSL_NARROW_CAST < int > (s16.length ()), pch, GSL_NARROW_CAST < int > (mx));
        if ((len == 0) || (len >= mx))
            nits.pick (nit_icu_barf, es_comment, ec_icu, "Cannot normalised ", quote (s));
        else
        {   pch [len] = 0;
            res16 = pch; }
        delete [] pch; }
    catch (...)
    {   delete [] pch; }
    return convert_to_utf8 (res16); }
#else // _MSC_VER
::std::string normalise_utf8 (nitpick& nits, const ::std::string& s)
{   if (! context.icu ()) return s;
    static ::std::atomic_bool bad_normaliser (false);
    if (bad_normaliser) return s;
    icu::UnicodeString us (icu::UnicodeString::fromUTF8 (icu::StringPiece (s.c_str ())));
    icu::UnicodeString out;
    UErrorCode err = U_ZERO_ERROR;
    const icu::Normalizer2* norm = icu::Normalizer2::getNFCInstance (err);
    if ((norm == nullptr) || ! U_SUCCESS (err))
    {   nits.pick (nit_icu_barf, es_warning, ec_icu, "Cannot get Normalizer2::NFC (error ", static_cast < int > (err), "); abandoning normalisation");
        bad_normaliser = true;
        return s; }
    err = U_ZERO_ERROR;
    norm -> normalize (us, out, err);
    if (U_FAILURE (err))
    {   nits.pick (nit_icu_barf, es_comment, ec_icu, "Cannot normalised ", quote (s), " (error ", static_cast < int > (err), ")");
        return s; }
    ::std::string res;
    out.toUTF8String (res);
    return res; }
#endif // _MSC_VER

#ifdef _MSC_VER
#ifndef VS2017
::std::wstring convert_to_wstring (const ::std::string& s)
{   ::std::wstring_convert < ::std::codecvt_utf8_utf16 < wchar_t > > converter;
    return converter.from_bytes (s); }
#endif // VS2017
#endif // _MSC_VER
#endif // NOICU
