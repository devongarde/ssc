/*
ssc (static site checker)
Copyright (c) 2020-2024 Dylan Harris
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
#include "gui/gui-ctrls.h"

bool check_datetime_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& caption)
{	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
	return  check_.concoct < wxBoxSizer > (mummy, pen, id, caption, wxALL | wxALIGN_CENTRE_HORIZONTAL) &&
			box_.concoct < wxBoxSizer > (mummy, pen, 2) &&
			datetime_.concoct < grid_t::box_ptr > (mummy, box_.box_); }

bool check_datetime_t :: TransferDataToWindow ()
{	if	(invalid () ||
		! check_.TransferDataToWindow () ||
		! datetime_.TransferDataToWindow ()) return false;
	click ();
	return true; }

bool check_datetime_t :: TransferDataFromWindow ()
{	return	(! invalid ()) &&
			check_.TransferDataFromWindow () &&
			datetime_.TransferDataFromWindow (); }

bool check_line_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& caption)
{	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
	PRESUME (! caption.empty (), __FILE__, __LINE__);
	return  check_.concoct < wxBoxSizer > (mummy, pen, id, caption) &&
			line_.concoct < wxBoxSizer > (mummy, pen);	 }

bool check_line_t :: TransferDataToWindow ()
{	return	(! invalid ()) &&
			check_.TransferDataToWindow (); }

bool check_line_t :: TransferDataFromWindow ()
{	return	(! invalid ()) &&
			check_.TransferDataFromWindow (); }

bool check_or_text_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& caption, const ::std::string& label, const ::std::string& def)
{	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
	PRESUME (! caption.empty (), __FILE__, __LINE__);
	return  check_.concoct < wxBoxSizer > (mummy, pen, id, caption) &&
			box_.concoct < wxBoxSizer > (mummy, pen, 2) &&
			label_.concoct < grid_t::box_ptr > (mummy, box_.box_, label, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
			text_.concoct < grid_t::box_ptr > (mummy, box_.box_, wxID_ANY, def, 200); }

bool check_or_text_t :: TransferDataToWindow ()
{	if	(invalid () ||
		check_.TransferDataToWindow () ||
		text_.TransferDataToWindow ()) return false;
	click ();
	return true;  }

bool check_or_text_t :: TransferDataFromWindow ()
{	return	(! invalid ()) &&
			check_.TransferDataFromWindow () &&
			text_.TransferDataFromWindow (); }

bool label_text_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const ::std::string& label, const ::std::string& def)
{	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
	PRESUME (! label.empty (), __FILE__, __LINE__);
	return  box_.concoct < wxBoxSizer > (mummy, pen, 2) &&
			label_.concoct < grid_t::box_ptr > (mummy, box_.box_, label, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
			text_.concoct < grid_t::box_ptr > (mummy, box_.box_, wxID_ANY, def, 250); }

bool label_text_t :: TransferDataToWindow ()
{	return	(! invalid ()) &&
			text_.TransferDataToWindow ();  }

bool label_text_t :: TransferDataFromWindow ()
{	return	(! invalid ()) &&
			text_.TransferDataFromWindow (); }

#endif // WX
