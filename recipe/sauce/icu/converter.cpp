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

::std::string convert_to_utf8 (nitpick& nits, const ::std::string& name, void_ptr& vp, uintmax_t& sz)
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
// https://stackoverflow.com/questions/23322438/how-to-convert-a-unicode-code-point-to-characters-in-c-using-icu
{   ::icu::UnicodeString s (static_cast < UChar32 > (n));
    ::std::string res;
    s.toUTF8String (res);
    return res; }

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

#ifdef _MSC_VER
::std::wstring convert_to_wstring (nitpick& nits, const ::icu::UnicodeString& us)
{   PRESUME (context.icu (), __FILE__, __LINE__);
    if (us.length () > 0)
    {   int32_t len = 0;
        UErrorCode err = U_ZERO_ERROR;
        u_strToWCS (nullptr, 0, &len, us.getBuffer (), us.length (), &err);
        if (U_SUCCESS (err))
        {   ::std::wstring res (len, 0);
            err = U_ZERO_ERROR;
            u_strToWCS (res.data (), GSL_NARROW_CAST < int32_t > (res.size ()), nullptr, us.getBuffer (), us.length (), &err);
            if (U_SUCCESS (err)) return res; }
        nits.pick (nit_convert, es_catastrophic, ec_icu, "Cannot convert to wstring."); }
    return ::std::wstring (); }

::std::wstring convert_to_wstring (const ::std::string& s)
{   ::std::wstring_convert <std::codecvt_utf8_utf16 < wchar_t > > converter;
    return converter.from_bytes (s); }
#endif // _MSC_VER
#endif // NOICU
