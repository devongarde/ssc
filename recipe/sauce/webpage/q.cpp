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
#include "main/abort.h"
#include "main/context.h"
#include "coop/lox.h"
#include "coop/knickers.h"
#include "webpage/q.h"

const char* stage_name [] =
{   "initialising ", "scanning ", "processing ", "finishing ", "max " };

bool d_q (q_entry& qe)
{   VERIFY_NOT_NULL (qe.ticks_, __FILE__, __LINE__);
    VERIFY_NOT_NULL (qe.dir_, __FILE__, __LINE__);
    bool res = true;
    nitpick nits;
    knickers k (nits, qe.ticks_);
    if (context.progress ())
    {   ::std::string msg;
        if (qe.page_.empty ())
        {   msg = ::gsl::at (stage_name, qe.stage_);
            msg += qe.dir_ -> get_disk_path ().string (); }
        else
        {   msg = "reviewing ";
            msg += (qe.dir_ -> get_disk_path () / qe.page_).string (); }
        msg += "\n";
        ::std::cout << msg; }
    try
    {   switch (qe.stage_)
        {   case st_scan :
                qe.dir_ -> scan (qe.ticks_, qe.dir_ -> get_site_path ());
                break;
            case st_examine :
                if (qe.page_.empty ()) qe.dir_ -> examine (qe.ticks_, qe.dir_);
                else qe.dir_ -> examine_page (qe.ticks_, qe.page_);
                break;
            case st_finish :
                res = false;
                break;
            default :
                nits.pick (nit_scan_failed, es_catastrophic, ec_fred, "internal error: invalid queue stage ", qe.stage_);
                res = false;
                break; } }
    catch (const ::std::system_error& e)
    {   nits.pick (nit_scan_failed, es_catastrophic, ec_fred, qe.stage_, " ", qe.dir_ -> get_disk_path (), " raised system error ", e.what ());
        res = false; }
    catch (const ::std::exception& e)
    {   nits.pick (nit_scan_failed, es_catastrophic, ec_fred, qe.stage_, " ", qe.dir_ -> get_disk_path (), " raised the exception ", e.what ());
        res = false; }
    catch (...)
    {   nits.pick (nit_scan_failed, es_catastrophic, ec_fred, qe.stage_, " ", qe.dir_ -> get_disk_path (), " raised an unknown exception");
        res = false; }
    return res; }
