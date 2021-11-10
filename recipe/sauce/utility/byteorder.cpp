/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#include "utility/byteorder.h"

// replace with ICU functionality


byte_order_mark get_byte_order (::std::string& str)
{   // https://en.wikipedia.org/wiki/Byte_order_mark
    const ::std::size_t len = str.length ();
    if (len > 1)
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26490)
#endif //  _MSC_VER
    {   const auto s = ::gsl::span (reinterpret_cast < const unsigned char* > (str.data ()), len);
#ifdef _MSC_VER
#pragma warning (pop)
#endif //  _MSC_VER
            switch (static_cast < int > (s[0]))
            {   case 0x00 :
                    if (len >= 4)
                        if ((s[1] == 0x00) && (s[2] == 0xFE) && (s[3] == 0xFF))
                        {   str = str.substr (4);
                            return bm_utf32_be; }
                    break;
                case 0x0E :
                    if (len >= 3)
                        if ((s[1] == 0xFE) && (s[2] == 0xFF))
                        {   str = str.substr (3);
                            return bm_scsu; }
                    break;
                case 0x2B :
                    if (len >= 3)
                        if ((s[1] == 0x2F) && (s[2] == 0x76))
                        {   switch (s[4])
                            {   case 0x2B :
                                case 0x2F :
                                case 0x38 :
                                case 0x39 :
                                    return bm_utf7;
                                default : break; } // unsupported
                            return bm_scsu; }
                    break;
                case 0x84 :
                    if (len >= 4)
                        if ((s[1] == 0x31) && (s[2] == 0x95) && (s[3] == 0x33))
                        {   str = str.substr (4);
                            return bm_gb_1830; }
                    break;
                case 0xDD :
                    if (len >= 4)
                        if ((s[1] == 0x73) && (s[2] == 0x66) && (s[3] == 0x73))
                        {   str = str.substr (4);
                            return bm_utf_ebcdic; }
                    break;
                case 0xEF :
                    if (len >= 3)
                        if ((s[1] == 0xBB) && (s[2] == 0xBF))
                        {   str = str.substr (3);
                            return bm_utf8; }
                    break;
                case 0xF7 :
                    if (len >= 3)
                        if ((s[1] == 0x64) && (s[2] == 0x4C))
                        {   str = str.substr (3);
                            return bm_utf1; }
                    break;
                case 0xFB :
                    if (len >= 3)
                        if ((s[1] == 0xEE) && (s[2] == 0x28))
                        {   str = str.substr (3);
                            return bm_bocu_1; }
                    break;
                case 0xFE :
                    if (len >= 2)
                        if (s[1] == 0xFF)
                        {   str = str.substr (2);
                            return bm_utf16_be; }
                    break;
                case 0xFF :
                    if (len >= 2)
                        if (s[1] == 0xFE)
                        {   str = str.substr (2);
                            return bm_utf16_le; }
                    break;
                default : break; } }
    return bm_ansi; }

e_charcode bom_to_encoding (const byte_order_mark bom) noexcept
{   switch (bom)
    {   case bm_utf8 : return cc_utf8;
        case bm_utf16_be : return cc_utf16be;
        case bm_utf16_le : return cc_utf16le;
        case bm_gb_1830 : return cc_gb;
        case bm_ansi :
        case bm_error: break;
        case bm_utf32_be :
        case bm_utf32_le :
        case bm_utf7 :
        case bm_utf1 :
        case bm_utf_ebcdic :
        case bm_scsu :
        case bm_bocu_1 : return cc_fkd; }
    return cc_ansi; }
