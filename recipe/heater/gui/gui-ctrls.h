/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2024 Dylan Harris
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
#include "gui/gui-ctrl.h"

struct check_datetime_t
{   grid_t box_;
    check_t check_;
    datetime_t datetime_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& caption);
    void click () { if (! invalid ()) datetime_.enable (check_.selected ()); }
    void enable (const bool b) { check_.enable (b); datetime_.enable (b); }
    bool invalid () const noexcept { return datetime_.invalid () || check_.invalid () || box_.invalid (); } };

struct check_line_t
{   check_t check_;
    line_t line_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& caption);
    void enable (const bool b) { check_.enable (b); }
    bool selected () const { return check_.selected (); }
    bool invalid () const noexcept { return check_.invalid () || line_.invalid (); } };

struct check_or_text_t
{   grid_t box_;
    check_t check_;
    label_t label_;
    text_t text_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void click () { if (! invalid ()) { const bool b = ! check_.selected (); label_.enable (b); text_.enable (b); } }
    void enable (const bool b) { check_.enable (b); label_.enable (b); text_.enable (b); }
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& caption, const ::std::string& label, const ::std::string& def = ::std::string ());
    bool invalid () const noexcept { return text_.invalid () || box_.invalid () || check_.invalid () || label_.invalid (); } };

struct label_text_t
{   grid_t box_;
    label_t label_;
    text_t text_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const ::std::string& label, const ::std::string& def = ::std::string ());
    void enable (const bool b) {label_.enable (b); text_.enable (b); }
    bool invalid () const noexcept { return text_.invalid () || box_.invalid () || label_.invalid (); } };

#endif // WX
