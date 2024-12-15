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
#include "gui/gui-ctrl.h"

bool check_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	check_ -> SetValue (set_);
	return true; }

bool check_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	set_ = check_ -> GetValue ();
	return true; }

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

bool text_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
	text_ -> SetValue (wxString (value_.c_str ()));
	return true; }

bool text_t :: TransferDataFromWindow ()
{	if (invalid ()) return false;
	value_ = text_ -> GetValue ();
	return true; }

#endif // WX
