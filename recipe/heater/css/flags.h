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

#pragma once

#define CF_BEF_AFT          0x0000000000000001
#define CF_PAGE             0x0000000000000002
#define CF_PAGE_NAME        0x0000000000000004
#define CF_EXPECT_KEYWORDS  0x0000000000000010
#define CF_EXPECT_NUMBER    0x0000000000000020
#define CF_EXPECT_STRING    0x0000000000000040
#define CF_EXPECT_FN        0x0000000000000080
#define CF_NOT_STRING       0x0000000000000100
#define CF_MUST_FONT_FACE   0x0000000000000200
#define CF_MAY_FONT_FACE    0x0000000000000400
#define CF_SVG              0x0000000000000800

#define CF_PRINT            0x0000000000001000
#define CF_TV               0x0000000000002000
#define CF_HANDHELD         0x0000000000004000
#define CF_MEDIA            0x0000000000007000

#define CF_DEPRECATED       0x0000000000008000

#define CF_LV_STD_JUL23     0x0000000000010000
#define CF_NOT_LV_STD_JUL23 0x0000000000020000

#define CF_NO_PARAMS        0x0000000000040000

#define CF_FACE_OR_PROFILE  0x0000000000080000

#define CF_MAY_FONT_FV      0x0000000000100000
#define CF_MUST_FONT_FV     0x0000000000200000

#define CF_MAY_PALETTE      0x0000000000400000
#define CF_MUST_PALETTE     0x0000000000800000

#define CF_OPENTYPE         0x0000000001000000
#define CF_TRUETYPE         0x0000000002000000

#define CF_CS_NAUGHTY       0x0000000004000000
#define CF_CS_CASCADE       0x0000000008000000
#define CF_CS_PREDEFINED    0x0000000010000000

#define CF_MUST_COUNTER     0x0000000020000000
#define CF_MAY_COUNTER      0x0000000040000000
