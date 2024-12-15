/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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

class bar_t
{   wxMenu* config_ = nullptr;
    wxMenu* edit_ = nullptr;
    wxMenu* file_ = nullptr;
    wxMenu* help_ = nullptr;
    wxMenuBar* bar_ = nullptr; 
    wxMenuItem* sub_advanced_ = nullptr; 
    void init ();
public:
    bool invalid () const noexcept
    {   return (bar_ == nullptr) || (config_ == nullptr) || (edit_ == nullptr) || (file_ == nullptr) || (help_ == nullptr); }
    wxMenuBar* gimme ()
    {   if (bar_ == nullptr)
        {   init ();
            VERIFY_NOT_NULL (bar_, __FILE__, __LINE__); }
        return bar_; }
    wxMenu* config ()
    {   VERIFY_NOT_NULL (config_, __FILE__, __LINE__);
        return config_; } };

#endif // WX
