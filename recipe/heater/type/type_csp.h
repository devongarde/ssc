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
#include "feedback/nitpick.h"
#include "parser/html_version.h"

#define CSP_1 HTML_2012, (HTML_NOV + 7)
#define CSP_2 HTML_2016, (HTML_DEC + 7)
#define CSP_3 HTML_2018, (HTML_OCT + 7)

const html_version csp_c1 (CSP_1, 0, HV_CSP_1);
const html_version csp_c2 (CSP_2, 0, HV_CSP_2);
const html_version csp_c3 (CSP_3, 0, HV_CSP_3);

void csp_directive_init (nitpick& nits);
void csp_keyword_init (nitpick& nits);
