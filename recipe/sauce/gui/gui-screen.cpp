/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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

#ifdef WX
#include "gui/gui-screen.h"
#define MIN_WINDOW_X    640
#define MIN_WINDOW_Y    480

bool get_centre (unsigned& x, unsigned& y, const unsigned obj_width, const unsigned obj_height, const unsigned env_width, const unsigned env_height) noexcept
{   if (obj_width > env_width) return false;
    if (obj_height > env_height) return false;
    x = (env_width - obj_width) / 2;
    y = (env_height - obj_height) / 2;
    return true; }

bool centre_on_screen (unsigned& x, unsigned& y, const unsigned obj_width, const unsigned obj_height)
{   const wxSize ss = wxGetDisplaySize ();
    if ((ss.x < 0) || (ss.y < 0)) return false;
    return get_centre (x, y, obj_width, obj_height, GSL_NARROW_CAST < unsigned > (ss.x), GSL_NARROW_CAST < unsigned > (ss.y)); }

bool get_default_window_size (unsigned& x, unsigned& y)
{   switch (wxSystemSettings::GetScreenType ())
    {   case wxSYS_SCREEN_NONE :
            return false;
        case wxSYS_SCREEN_PDA :
        case wxSYS_SCREEN_TINY :
            {   const wxSize ss = wxGetDisplaySize ();
                x = ss.x;
                y = ss.y; }
            break;
        case wxSYS_SCREEN_SMALL :
            x = MIN_WINDOW_X;
            y = MIN_WINDOW_Y;
            break;
        default :
            {   const wxSize ss = wxGetDisplaySize ();
                x = ::std::max (MIN_WINDOW_X, ss.x / 2);
                y = ::std::max (MIN_WINDOW_Y, ss.y / 2); }
            break; }
    return true; }

bool get_default_window_position (unsigned& x, unsigned& y, unsigned& w, unsigned& h)
{   if (! get_default_window_size (w, h)) return false;
    return centre_on_screen (x, y, w, h); }

#endif // WX
