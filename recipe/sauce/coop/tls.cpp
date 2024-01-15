/*
ssc (static site checker)
File Info
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
#include "main/enum.h"
#include "feedback/nitpick.h"
#include "coop/fred.h"

#ifdef NO_FRED
vesii_t vesii;

void set_esii (const e_statii sii, const ::std::string& s)
{   PRESUME (sii < max_statii, __FILE__, __LINE__);
    PRESUME (! s.empty (), __FILE__, __LINE__);
    PRESUME (! test_esii (sii, s), __FILE__, __LINE__);
    if (vsesii.size () == 0) vsesii_.resize (max_statii);
    vsesii.at (sii).insert (s); }

void reset_esii (const e_statii sii)
{   PRESUME (sii < max_statii, __FILE__, __LINE__);
    if (vsesii.size () > sii)
        vsesii.at (sii).clear (); }

bool test_esii (const e_statii sii, const ::std::string& s)
{   PRESUME (vsesii.size () == max_statii, __FILE__, __LINE__);
    PRESUME (sii < max_statii, __FILE__, __LINE__);
    return vsesii_.at (sii).find (s) != vsesii_.at (sii).cend (); }
#else // NO_FRED
void set_esii (const e_statii sii, const ::std::string& s)
{   PRESUME (sii < max_statii, __FILE__, __LINE__);
    PRESUME (! test_esii (sii, s), __FILE__, __LINE__);
    if (fred.tls ().vsesii_.empty ())
        fred.tls ().vsesii_.resize (max_statii);
    fred.tls ().vsesii_.at (sii).insert (s); }

void reset_esii (const e_statii sii)
{   PRESUME (sii < max_statii, __FILE__, __LINE__);
    if (! fred.tls ().vsesii_.empty ())
        fred.tls ().vsesii_.at (sii).clear (); }

bool test_esii (const e_statii sii, const ::std::string& s)
{   PRESUME (sii < max_statii, __FILE__, __LINE__);
    if (fred.tls ().vsesii_.empty ()) return false;
    vsstr_t& vse = fred.tls ().vsesii_;
    return vse.at (sii).find (s) != vse.at (sii).cend (); }
#endif // NO_FRED
