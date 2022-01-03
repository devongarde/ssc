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
#include "icu/converter.h"
#include "icu/charset.h"
#include "icu/wrapper.h"
#include "utility/common.h"

::std::string get_standard_converter_name (nitpick& nits, const ::std::string& name)
{   static int converter_count = 0;
    if (converter_count == 0)
    {   converter_count = ucnv_countAvailable ();
        if (converter_count == 0)
        {   nits.pick (nit_no_converters, es_info, ec_icu, "no ICU converters available");
            return ::std::string (); } } // or should SSC drop out?
    UErrorCode err = U_ZERO_ERROR;
    ::std::string res (ucnv_getStandardName (name.c_str (), "IANA", &err));
    if (err <= U_ZERO_ERROR) return res;
    nits.pick (nit_icu, es_catastrophic, ec_icu, "ICU ucnv_getStandardName error ", static_cast < int > (err));
    return ::std::string (); }

::std::string convert_to_utf_8 (nitpick& nits, const ::std::string& name, void_ptr& vp, uintmax_t& sz)
{   PRESUME (sz > 0, __FILE__, __LINE__);
    PRESUME (vp.get () != nullptr, __FILE__, __LINE__);
    ::std::string cs (identify_probable_charset (vp, sz));
    if (cs.empty ())
        nits.pick (nit_icu, es_error, ec_icu, "cannot identify charset in ", name, "; will hope for the best");
    else
    {   if (cs == UTF_8) return cs;
        converter conv (cs);
        if (! conv.valid ())
            nits.pick (nit_icu, es_catastrophic, ec_icu, "ICU constructor error ", static_cast < int > (conv.error ()), " converting ", name);
        else
        {   if (conv.convert_to (vp, sz)) return cs;
            nits.pick (nit_icu, es_catastrophic, ec_icu, "ICU error ", static_cast < int > (conv.error ()), " converting ", name); } }
    return ::std::string (); }