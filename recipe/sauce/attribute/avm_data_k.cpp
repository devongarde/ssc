/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "attribute/avm_data.h"

hav_t havt_kbd [] =
{   HTMLPLUS_ATTRIBUTES (elem_kbd),
    HTML23_CLID_ATTRIBUTES (elem_kbd),
    STANDARD_HTML5_ATTRIBUTES (elem_kbd),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };

hav_t havt_keygen [] =
{   { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_autofocus },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_challenge },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_disabled },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_form },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_keytype },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_keygen, a_name },
    STANDARD_HTML5_ATTRIBUTES (elem_keygen),
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_error, a_unknown } };
