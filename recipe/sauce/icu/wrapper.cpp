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
#include "utility/quote.h"
#include "icu/wrapper.h"

bool charset_detector_match::might_be (const ::std::string& s)
{   if (s.empty ()) return false;
    ::std::string rhs (s);
    ::boost::replace_all (rhs, "_", "-");
    return compare_no_case (name (), rhs); }

charset_detector_match charset_detector_matches::at (const int32_t i) const
{   if ((i < 0) || (i >= count_))
#ifdef __GNUC__
        // GCC won't let me pass a constant C string to a function that requires a constant C string.
        // GCC insist this is because the standard, but mysteriously neither clang nor msvc do the same.
        // I don't know whether GCC is right, but I do know it's annoying. If GCC can't be bothered to cooperate,
        // then neither shall I. Code on well-behaved compilers is well-behaved.
    {   ::std::cerr << "Charset_detector_matchm:at out of bounds error. Exception specification blocked by GCC's C++ compiler. Aborting.\n";
        ::std::exit (3); }
#else //  __GNUC__
        // meanwhile, pragmatic compilers work
        throw ::std::exception ("charset_detector_matchm:at out of bounds error");
#endif // __GNUC__
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26481) // try reading the preceding code, linter
#endif // _MSC_VER
    return charset_detector_match (match_ [i]); }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

bool charset_detector::set_text (const char *in, int32_t len)
{   PRESUME (context.icu (), __FILE__, __LINE__);
    PRESUME (detector_ != nullptr, __FILE__, __LINE__);
    ucsdet_setText (detector_, in, len, &err_);
    return valid (); }

void_ptr converter::convert_to (const void_ptr& vp, const uintmax_t sz)
{   PRESUME (context.icu (), __FILE__, __LINE__);
    const char* const from = static_cast <char*> (vp.get ());
    const int32_t len = ucnv_toUChars (conv_, nullptr, 0, from, GSL_NARROW_CAST < int32_t > (sz), &err_);
    if (err_ <= 0)
    {   const ::std::size_t buflen = static_cast < ::std::size_t > (len) * sizeof (UChar);
        void_ptr res (alloc_void_ptr (buflen));
        UChar* to_uc = static_cast <UChar*> (res.get ());
        if (res.get () != nullptr)
        {   const int32_t l2 = ucnv_toUChars (conv_, to_uc, len, from, GSL_NARROW_CAST < int32_t > (sz), &err_);
            if ((l2 <= len) && (err_ <= 0)) return res; } }
    return void_ptr (); }
