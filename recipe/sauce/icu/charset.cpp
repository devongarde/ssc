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

#ifndef NOICU
#include "main/context.h"
#include "icu/charset.h"
#include "icu/wrapper.h"
#include "main/context.h"
#include "feedback/nitpick.h"

::std::string identify_probable_charset (const void* vp, const uintmax_t sz)
{   VERIFY_NOT_NULL (vp, __FILE__, __LINE__);
    if (context.icu ()) try
    {   charset_detector detector;
        if (detector.valid ())
            if (detector.set_text (static_cast < const char * > (vp), ::gsl::narrow_cast < int32_t > (sz)))
            {   const charset_detector_matches matched (detector.match_all ());
                if (detector.valid () && (matched.count () > 0) && matched.content ())
                    return matched.at (0).name (); } }
    catch (...) { }
    return ::std::string (); }

void verify_file_charset (nitpick& nits, const html_version& v, const ::std::string& name, const ::std::string& charset, const void* vp, const uintmax_t sz)
{   if (! context.icu ()) return;
    if (v.mjr () < 2) return;
    VERIFY_NOT_NULL (vp, __FILE__, __LINE__);
    ::std::string dcs (v.default_charset ());
    ::std::string acs (v.alternative_charset ());
    ::std::string errmsg ("cannot determine character format of '");
    errmsg += name;
    errmsg += "'";
    try
    {   charset_detector detector;
        const int32_t input_length = ::gsl::narrow_cast < int32_t > (sz);
        if (! detector.valid ())
           nits.pick (nit_icu, es_catastrophic, ec_icu, errmsg, ": ICU ucsdet_open error ", static_cast < int > (detector.error ()));
        else
        {   const char* pch = static_cast < const char * > (vp);
            if (! detector.set_text (pch, input_length))
                nits.pick (nit_icu, es_catastrophic, ec_icu, errmsg, ": ICU ucsdet_setText error ", static_cast < int > (detector.error ()));
            else
            {   const charset_detector_matches matched (detector.match_all ());
                if (! detector.valid ())
                    nits.pick (nit_icu, es_catastrophic, ec_icu, errmsg, ": ICU ucsdet_detect error ", static_cast < int > (detector.error ()));
                else if (matched.count () == 0)
                    nits.pick (nit_icu, es_error, ec_icu, name, "; is not a text file");
                else if (! matched.content ())
                    nits.pick (nit_icu, es_catastrophic, ec_icu, errmsg, ": internal ICU ucsdet_detect error (nullptr return)");
                else
                {   ::std::stringstream rpt;
                    bool match_found = false;
                    bool validated = ! v.restricted_charset ();
                    for (int i = 0; i < matched.count (); ++i)
                       if (! matched.at (i).content ())
                            nits.pick (nit_icu, es_catastrophic, ec_icu, errmsg, ": internal ICU ucsdet_detect error (nullptr return)");
                        else
                        {   if (context.tell (e_debug))
                            {   if (i > 0) rpt << ";";
                                rpt << i << ":" << matched.at (i).name ();
                                if (! matched.at (i).valid ()) rpt << " (error " << static_cast < int > (matched.at (i).error ()) << ")";
                                rpt << "," << matched.at (i).confidence ();
                                if (! matched.at (i).valid ()) rpt << " (error " << static_cast < int > (matched.at (i).error ()) << ")";
                                rpt << "," << matched.at (i).language ();
                                if (! matched.at (i).valid ()) rpt << " (error " << static_cast < int > (matched.at (i).error ()) << ")"; }
                            if (! match_found)
                                if (charset.empty ()) match_found = matched.at (i).might_be (dcs) || matched.at (i).might_be (acs);
                                else match_found = matched.at (i).might_be (charset);
                            if (! validated)
                                validated = v.valid_charset (matched.at (i).name ()); }
                    if (! match_found)
                    {   if (charset.empty ())
                            nits.pick (nit_charset_mismatch, es_warning, ec_page, "The charset of '", name, "' is neither declared nor ", dcs, " (the default for ", v.name (), ")");
                        else nits.pick (nit_charset_mismatch, es_warning, ec_page, "The content of '", name, "' does not match its declared charset, ", charset);
                        nits.pick (nit_charset_used, es_info, ec_page, "'", name, "' appears to use ", matched.at (0).name ()); }
                    if (! validated)
                        nits.pick (nit_charset_invalid, es_error, ec_page, "The actual charset of '", name, "', ", matched.at (0).name (), ", is invalid in ", v.name (), "; prefer ", dcs);
                    if (context.tell (e_debug)) nits.pick (nit_icu, es_debug, ec_icu, rpt.str ()); } } } }
    catch (...)
    {   nits.pick (nit_page_charset, es_error, ec_page, name, " is incompatible with charset ", charset); } }

void verify_file_charset (nitpick& nits, const html_version& v, const ::boost::filesystem::path& p, const ::std::string& charset)
{   if (! context.icu ()) return;
    uintmax_t sz = 0;
    void_ptr vp (read_binary_file (nits, p, sz));
    if (sz == 0) return;
    verify_file_charset (nits, v, p.string (), charset, vp.get (), sz); }
#endif // NOICU
