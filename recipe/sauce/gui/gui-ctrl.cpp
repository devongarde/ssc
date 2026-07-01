/*
ssc (static site checker)
Copyright (c) 2020-2026 Dylan Harris
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
#include "gui/gui-ctrl.h"

bool check_t :: selected () const
{	if (invalid ()) return false;
    set_ = ctrl_ -> GetValue ();
    return set_; }

void check_t :: select (const bool b)
{	if (invalid ()) return;
    set_ = b;
    ctrl_ -> SetValue (b); }

bool check_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	ctrl_ -> SetValue (set_);
	return true; }

bool check_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	set_ = ctrl_ -> GetValue ();
	return true; }

void datetime_t :: enable (const bool b)
{	if (! invalid ())
    {	date_ -> Enable (b);
        time_ -> Enable (b); } }

bool datetime_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	wxDateTime dt (datetime_);
	dt.ResetTime ();
	date_ -> SetValue (dt);
	const wxDateTime tm (datetime_);
	const wxTimeSpan ts = tm.Subtract (dt);
	const wxDateTime dt0 (static_cast < time_t > (0));
	time_ -> SetValue (dt0 + ts);
	return true; }

bool datetime_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	wxDateTime dt (datetime_);
	dt.ResetTime ();
	date_ -> SetValue (dt);
	const wxDateTime tm (datetime_);
	const wxTimeSpan ts = tm.Subtract (dt);
	const wxDateTime dt0 (static_cast < time_t > (0));
	time_ -> SetValue (dt0 + ts);
	return true; }

bool filepick_t :: TransferDataToWindow ()
{	if (pathpick_t < wxFilePickerCtrl > :: invalid ()) return false;
    wxFileName fn (value_.string ());
    pathpick_t < wxFilePickerCtrl > :: ctrl_ -> SetFileName (fn);
    return true; }

bool filepick_t :: TransferDataFromWindow ()
{	if (pathpick_t < wxFilePickerCtrl > :: invalid ()) return false;
    wxFileName fn (pathpick_t < wxFilePickerCtrl > :: ctrl_ -> GetFileName ());
    value_ = ::std::string (fn.GetName ().c_str ());
    return true; }

bool folder_t :: TransferDataToWindow ()
{	if (pathpick_t < wxDirPickerCtrl > :: invalid ()) return false;
    wxFileName fn (value_.string ());
    pathpick_t < wxDirPickerCtrl > :: ctrl_ -> SetDirName (fn);
    return true; }

bool folder_t :: TransferDataFromWindow ()
{	if (pathpick_t < wxDirPickerCtrl > :: invalid ()) return false;
    value_ = ::std::string (pathpick_t < wxDirPickerCtrl > :: ctrl_ -> GetPath ().c_str ());
    return true; }

bool spin_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	ctrl_ -> SetValue (value_);
	return true; }

bool spin_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	value_ = ctrl_ -> GetValue ();
	return true; }

bool text_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	ctrl_ -> SetValue (wxString (value_.c_str ()));
	return true; }

bool text_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	value_ = ctrl_ -> GetValue ();
	return true; }
#endif // WX
