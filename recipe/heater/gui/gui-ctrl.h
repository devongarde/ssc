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

struct box_t
{   typename typedef wxBoxSizer box_ptr;
	typename box_ptr* box_ = nullptr;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen)
	{	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
		VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
		box_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxHORIZONTAL));
		if (box_ == nullptr) return false;
		pen -> Add (box_, 0, wxEXPAND, 5);
		return true; }
    bool invalid () const noexcept { return box_ == nullptr; } };

struct check_t
{   wxCheckBox* check_ = nullptr;
    bool set_ = false;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& caption, const long style = wxALL)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
	    VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
	    check_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (mummy, id, caption.c_str (), wxDefaultPosition, wxDefaultSize, 0));
	    if (check_ == nullptr) return false;
	    pen -> Add (check_, 0, style, 5);
	    return true; }
	void enable (const bool b)
	{	if (! invalid ()) check_ -> Enable (b); }
	bool selected () const
	{	if (invalid ()) return false;
		return check_ -> GetValue () != 0; }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid () const noexcept { return check_ == nullptr; } };

struct datetime_t
{   wxDatePickerCtrl* date_ = nullptr;
    wxTimePickerCtrl* time_ = nullptr;
    time_t datetime_ = 0;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
	    VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
	    date_ = GSL_OWNER (wxDatePickerCtrl) (new wxDatePickerCtrl (mummy, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT));
	    if (date_ != nullptr)
	    {	time_ = GSL_OWNER (wxTimePickerCtrl) (new wxTimePickerCtrl (mummy, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT));
		    if (time_ != nullptr)
		    {	pen -> Add (date_, 0, wxALIGN_CENTER_VERTICAL | wxALL | wxALIGN_RIGHT, 5);
			    pen -> Add (time_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
			    return true; } }
		return false; }
	void enable (const bool b)
	{	if (! invalid ())
		{	date_ -> Enable (b);
			time_ -> Enable (b); } }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid () const noexcept { return time_ == nullptr || date_ == nullptr; } };

struct grid_t
{   typename typedef wxGridSizer box_ptr;
	box_ptr* box_ = nullptr;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int across)
	{	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
		VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
		box_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, across, 0, 0));
		if (box_ == nullptr) return false;
		pen -> Add (box_, 0, wxEXPAND, 5);
		return true; }
    bool invalid () const noexcept { return box_ == nullptr; } };

struct label_t
{   wxStaticText* label_ = nullptr;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const ::std::string& text, const long style = wxALIGN_CENTER_VERTICAL | wxALL)
	{	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
		VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
		label_ = GSL_OWNER (wxStaticText) (new wxStaticText (mummy, wxID_ANY, text.c_str (), wxDefaultPosition, wxDefaultSize, 0));
		if (label_ == nullptr) return false;
		label_ -> Wrap (-1);
		pen -> Add (label_, 0, style, 5);
		return true; }
	void enable (const bool b)
	{	if (! invalid ()) label_ -> Enable (b); }
    bool invalid () const noexcept { return label_ == nullptr; } };

struct line_t
{   wxStaticLine* line_ = nullptr;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen)
	{	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
		VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
		line_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (mummy, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
		if (line_ == nullptr) return false;
		pen -> Add (line_, 0, wxEXPAND | wxALL, 5);
		return true; }
	bool invalid () const noexcept { return line_ == nullptr; } };

struct text_t
{   wxTextCtrl* text_ = nullptr;
    ::std::string value_;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id = wxID_ANY, const ::std::string& def = ::std::string (), const int width = -1)
	{	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
		VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
		text_ = GSL_OWNER (wxTextCtrl) (new wxTextCtrl (mummy, id, def.c_str (), wxDefaultPosition, wxDefaultSize, 0));
		if (text_ == nullptr) return false;
		if (width > 0) text_ -> SetMinSize (wxSize (width, -1));
		pen -> Add (text_, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
		return true; }
	void enable (const bool b)
	{	if (! invalid ()) text_ -> Enable (b); }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid () const noexcept { return text_ == nullptr; } };

#endif // WX
