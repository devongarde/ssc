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
#include "type/type_enum.h"
#include "type/type_master.h"

template < > struct type_master < t_cookie > : public tidy_string < t_cookie >
{   void set_value (nitpick& nits, const html_version& v, const ::std::string& s)
    {   tidy_string < t_cookie > :: set_value (nits, v, trim_the_lot_off (s));
        const ::std::string& ss = tidy_string < t_cookie > :: get_string ();
        if (s.empty ())
        {   nits.pick (nit_empty, es_error, ec_type, "value required");
            tidy_string < t_cookie > :: status (s_invalid); }
        else if (good ())
        {   ::std::string::size_type pos = ss.find ('=');
            nitpick nuts;
            if (pos == ::std::string::npos)
                switch (examine_value < t_cookieid > (nuts, v, ss))
                {   case coo_secure :
                    case coo_httponly :
                        return;
                    default :
                        nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_comment, ec_type, quote (ss), " is unknown to " PROG);
                        return; }
            if (pos > 0)
            {   ::std::string id (ss.substr (0, pos));
                ::std::string arg (ss.substr (pos+1));
                if (! test_value < t_cookieid > (nuts, v, id))
                {   nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_comment, ec_type, quote (ss), " is unknown to " PROG " here");
                    return; }
                switch (examine_value < t_cookieid > (nuts, v, id))
                {   case coo_expires :
                        if (! test_value < t_datetime > (nuts, v, arg))
                            nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_warning, ec_type, quote (arg), " may not be a valid date");
                        return;
                    case coo_maxage :
                        if (arg.find_first_not_of (DENARY) == ::std::string::npos) return;
                        nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_error, ec_type, quote (arg), " is not an integer");
                        break;
                    case coo_domain :
                        if (arg.find_first_not_of (ALPHABET DENARY "-.") == ::std::string::npos) return;
                        nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_error, ec_type, quote (arg), " is an invalid domain");
                        break;
                    case coo_path :
                        if (arg.find_first_of (";") == ::std::string::npos) return;
                        nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_error, ec_type, quote (arg), " is an invalid path");
                        break;
                    case coo_secure :
                    case coo_httponly :
                        nits.pick (nit_bad_cookie, ed_rfc_6265, "4.1.1. Syntax", es_error, ec_type, id, " takes no argument");
                        break;
                    default :
                        assert (false); // should not get here; unexpected cookie type
                        nits.pick (nit_internal_parsing_error, ed_rfc_6265, "4.1.1. Syntax", es_warning, ec_type, quote (arg), " is unexpected and unverified");
                        break; } } }
        tidy_string < t_cookie > :: status (s_invalid); } };

template < > struct type_master < t_cookies > : type_at_least_one < t_cookies, sz_semicolon, t_cookie > { };
