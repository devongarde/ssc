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

#include "main/standard.h"
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
        // I don't know whether GCC is right, but I do know it's annoying. If GCC can't be bothered to behave,
        // then neither shall I. Code on well-behaved compilers is well-behaved.
    {   ::std::cerr << "GCC C++ compiler annoyance revealed by charset_detector_matches overflow. Aborting.\n";
        ::std::exit (3); }
#else //  __GNUC__
        // meanwhile, pragmatic compilers work
        throw ::std::exception ("charset_detector_match at () out of bounds error");
#endif // __GNUC__
    return charset_detector_match (match_ [i]); }

bool charset_detector::set_text (const char *in, int32_t len)
{   PRESUME (detector_ != nullptr, __FILE__, __LINE__);
    ucsdet_setText (detector_, in, len, &err_);
    return valid (); }

bool converter::convert_to (void_ptr& vp, uintmax_t& sz)
{   char* from = reinterpret_cast <char*> (vp.get ());
    int32_t len = ucnv_toUChars (conv_, nullptr, 0, from, static_cast < int32_t > (sz), &err_);
    if (err_ <= 0)
    {   ::std::size_t buflen = static_cast < ::std::size_t > (len) * sizeof (UChar);
        void_ptr res (alloc_void_ptr (buflen));
        UChar* to_uc = reinterpret_cast <UChar*> (res.get ());
        if (res.get () != nullptr)
        {   int32_t l2 = ucnv_toUChars (conv_, to_uc, len, from, static_cast < int32_t > (sz), &err_);
            if ((l2 <= len) && (err_ <= 0))
            {   vp = res; sz = buflen; return true; } } }
    return false; }
