/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "parser/security.h"
#include "main/context.h"
#include "type/type.h"

bool sec_txt::parse (nitpick& nits, const ::std::string& site_path, const ::std::string& s, const directory* const d)
{   if (::boost::filesystem::path (site_path).filename ().string () != "security.txt")
        return false;
    if (::boost::filesystem::path (site_path).parent_path ().string () != "/" WELL_KNOWN)
    {   nits.pick (nit_robotic, ed_security, "3. Location of security.txt", es_error, ec_robotic, "security.txt should be in " WELL_KNOWN_PATH);
        return false; }
    if (! context.sectxt ()) return true;
    c_.parse (s);
    bool con = false, lang = false, exp = false;
    for (vi_colic i = c_.l_.begin (); i != c_.l_.end (); ++i)
    {   switch (i -> cmd_)
        {   case sec_csaf :
                nits.pick (nit_security, ed_security, "6.1. Well-Known URIs Registry ", es_info, ec_security, "CSAF is an extension to security.txt, so might not be recognised");
                FALLTHROUGH;
            case sec_encryption :
                if (i -> arg_.find ("://") == ::std::string::npos) break;
                FALLTHROUGH;
            case sec_acknowledgements :
            case sec_canonical :
            case sec_hiring :
            {   url u (i -> nits_, context.html_ver (), i -> arg_);
                if (u.get_protocol () != pr_https)
                    i -> nits_.pick (nit_security, ed_security, "2.5 Field Definitions", es_error, ec_security, "URLs must use HTTPS");
                if (u.valid ())
                    u.verify (i -> nits_, context.html_ver (), d);
                break; }
            case sec_contact :
            {   con = true;
                url u (i -> nits_, context.html_ver (), i -> arg_);
                switch (u.get_protocol ())
                {   case pr_email :
                    case pr_https :
                    case pr_mailto :
                    case pr_tel :
                        break;
                    default :
                        nits.pick (nit_security, ed_security, "2.5.3 Contact", es_error, ec_security, "A contact should be HTTPS, MAILTO, or TEL");
                        break; }
                if (u.valid ())
                    u.verify (i -> nits_, context.html_ver (), d);
                break; }
            case sec_expires :
                if (exp)
                    i -> nits_.pick (nit_security, ed_security, "2.5.5 Expires", es_error, ec_security, "Expires may only occur once");
                else exp = true;
                test_value < t_datetime_4 > (i -> nits_, context.html_ver (), i -> arg_);
                break;
            case sec_preflang :
                if (lang)
                    i -> nits_.pick (nit_security, ed_security, "2.5.8 Preferred=Languages", es_error, ec_security, "Preferred-Languages may only occur once");
                else lang = true;
                test_value < t_langs > (i -> nits_, context.html_ver (), i -> arg_);
                break;
            default :
                break; } }
    if (! con)
        nits.pick (nit_security, ed_security, "2.5.3 Contact", es_error, ec_security, "Contact is required and missing");
    if (! exp)
        nits.pick (nit_security, ed_security, "2.5.5 Expires", es_error, ec_security, "Expires is required and missing");
    return true; }

void sec_txt::review (::std::ostringstream& ss, const mmac_t& mac, nitpick& nits)
{   ss << nits.review (mac);
    for (vic_colic i = c_.l_.cbegin (); i != c_.l_.cend (); ++i)
    {   ss << i -> nits_.review (mac);
        i -> nits_.accumulate (nits); } }
