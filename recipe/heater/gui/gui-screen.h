/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
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

#ifdef WX
bool get_centre (unsigned& x, unsigned& y, const unsigned obj_width, const unsigned obj_height, const unsigned env_width, const unsigned env_height) noexcept;
bool centre_on_screen (unsigned& x, unsigned& y, const unsigned obj_width, const unsigned obj_height);
bool get_default_window_size (unsigned& x, unsigned& y);
bool get_default_window_position (unsigned& x, unsigned& y, unsigned& w, unsigned& h);
#endif // WX
