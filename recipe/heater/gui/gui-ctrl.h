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
template < typename CTRL > struct base_ctrl_t
{   CTRL* ctrl_ = nullptr;
    template < class BOX > bool concocted (BOX* pen, const int window = 0, const int flag = 0, const int border = 0)
    {   VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        if (ctrl_ == nullptr) return false;
        pen -> Add (ctrl_, window, flag, border);
        return true; }
    void enable (const bool b)
    {   if (! invalid ()) ctrl_ -> Enable (b); }
    bool enabled () const
    {   if (invalid ()) return false;
        return ctrl_ -> IsEnabled (); }
    bool invalid () const noexcept
    {   return ctrl_ == nullptr; } };

template < typename CTRL > struct group_ctrl_t : base_ctrl_t < CTRL >
{   int value_ = -1;
    bool concoct (const int sel, const int def = -1)
    {   if (base_ctrl_t < CTRL > :: ctrl_ == nullptr) return false;
        value_ = sel;
        if (sel > 0) base_ctrl_t < CTRL > :: ctrl_ -> SetSelection (sel);
        else if (def >= 0) base_ctrl_t < CTRL > :: ctrl_ -> SetSelection (def);
        return true; }
    void select (const int n)
    {	if (! base_ctrl_t < CTRL > :: invalid ()) base_ctrl_t < CTRL > :: ctrl_ -> SetSelection (n); }
    int selected () const
    {	if (base_ctrl_t < CTRL > :: invalid ()) return 0;
        return base_ctrl_t < CTRL > :: ctrl_ -> GetSelection (); }
    int count () const
    {	if (base_ctrl_t < CTRL > :: invalid ()) return 0;
        return base_ctrl_t < CTRL > :: ctrl_ -> GetCount (); }
    bool TransferDataToWindow ()
    {	if (base_ctrl_t < CTRL > :: invalid ()) return false;
        base_ctrl_t < CTRL > :: ctrl_ -> SetSelection (value_);
        return true; }
    bool TransferDataFromWindow ()
    {	if (base_ctrl_t < CTRL > :: invalid ()) return false;
        value_ = base_ctrl_t < CTRL > :: ctrl_ -> GetSelection ();
        return true; } };

template < typename CTRL > struct select_ctrl_t : group_ctrl_t < CTRL >
{   bool concoct (const vstr_t& vs, const int sel)
    {   if (base_ctrl_t < CTRL > :: ctrl_ == nullptr) return false;
        for (int n = 0; n < GSL_NARROW_CAST < int > (vs.size ()); ++n)
            base_ctrl_t < CTRL > :: ctrl_ -> Append (vs.at (n));
        return group_ctrl_t < CTRL > :: concoct (sel); }
    ::std::string value (const int n) const
    {	if (base_ctrl_t < CTRL > :: invalid ()) return ::std::string ();
        return ::std::string (base_ctrl_t < CTRL > :: ctrl_ -> GetString (n).c_str ()); }
    void clear ()
    {   if (base_ctrl_t < CTRL > :: invalid ()) return;
        base_ctrl_t < CTRL > :: ctrl_ -> Clear (); }
    void append (const ::std::string& s)
    {	if (! base_ctrl_t < CTRL > :: invalid ()) base_ctrl_t < CTRL > :: ctrl_ -> Append (s); } };

struct box_t
{   typedef wxBoxSizer box_ptr;
    box_ptr* box_ = nullptr;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const long style = wxEXPAND, const wxOrientation oriental = wxHORIZONTAL, const int n = 0)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        box_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (oriental));
        if (box_ == nullptr) return false;
        pen -> Add (box_, n, style, 5);
        return true; }
    bool invalid () const noexcept { return box_ == nullptr; } };

struct button_t : base_ctrl_t < wxButton >
{   template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& caption, const wxSize& sz = wxDefaultSize, const long style = wxALL)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        ctrl_ = GSL_OWNER (wxButton) (new wxButton (mummy, id, caption.c_str (), wxDefaultPosition, sz, 0));
        return base_ctrl_t < wxButton > :: concocted (pen, 0, style, 5); } };

struct check_t : base_ctrl_t < wxCheckBox >
{   mutable bool set_ = false;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& caption, const long style = wxALL, const long chst = 0)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        ctrl_ = GSL_OWNER (wxCheckBox) (new wxCheckBox (mummy, id, caption.c_str (), wxDefaultPosition, wxDefaultSize, chst));
        return base_ctrl_t < wxCheckBox > :: concocted (pen, 0, style, 5); }
    bool selected () const;
    void select (const bool b);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };

struct choice_t : select_ctrl_t < wxChoice >
{   template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const vstr_t& values, const int sel = -1, const int width = 100, const long style = wxALIGN_CENTRE_VERTICAL)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        ctrl_ = GSL_OWNER (wxChoice) (new wxChoice (mummy, id, wxDefaultPosition, wxSize (width, -1)));
        if (ctrl_ == nullptr) return false;
        if (! select_ctrl_t < wxChoice > :: concoct (values, sel)) return false;
        return select_ctrl_t < wxChoice > :: concocted (pen, 2, style, 5); } };

struct combo_t : select_ctrl_t < wxComboBox >
{  template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const vstr_t& values, const int sel = -1, const int width = 100, const ::std::string& def = ::std::string (), const long style = wxALIGN_CENTRE_VERTICAL)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        ctrl_ = GSL_OWNER (wxComboBox) (new wxComboBox (mummy, id, def, wxDefaultPosition, wxSize (width, -1), 0, NULL, wxCB_DROPDOWN | wxCB_SORT));
        if (ctrl_ == nullptr) return false;
        if (! select_ctrl_t < wxComboBox > :: concoct (values, sel)) return false;
        return select_ctrl_t < wxComboBox > :: concocted (pen, 2, style, 5); } };

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
                return true; }
            delete date_;
            date_ = nullptr; }
        return false; }
    void enable (const bool b);
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool invalid () const noexcept { return time_ == nullptr || date_ == nullptr; } };

template < class CTRL > struct pathpick_t : base_ctrl_t < CTRL >
{   ::boost::filesystem::path value_;
    void value (const ::boost::filesystem::path& p) { value_ = p; }
    ::boost::filesystem::path value () const { return value_; } };

struct filepick_t : pathpick_t < wxFilePickerCtrl >
{   template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::boost::filesystem::path& value, const ::std::string& text, const ::std::string& pattern, const long style = wxFLP_OVERWRITE_PROMPT | wxFLP_SAVE | wxFLP_USE_TEXTCTRL, const long ppstyle = wxALL | wxALIGN_CENTRE_HORIZONTAL)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        value_ = value;
        ctrl_ = GSL_OWNER (wxFilePickerCtrl) (new wxFilePickerCtrl (mummy, id, value.string ().c_str (), text.c_str (), pattern.c_str (), wxDefaultPosition, wxDefaultSize, style));
        return pathpick_t < wxFilePickerCtrl > :: concocted (pen, 0, ppstyle, 5); }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };

struct folder_t : pathpick_t < wxDirPickerCtrl >
{   template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::boost::filesystem::path& value, const ::std::string& text = ::std::string (), const long style = wxDIRP_DEFAULT_STYLE)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        value_ = value;
        ctrl_ = GSL_OWNER (wxDirPickerCtrl) (new wxDirPickerCtrl (mummy, id, value.string ().c_str (), text.c_str (), wxDefaultPosition, wxDefaultSize, style));
        return pathpick_t < wxDirPickerCtrl > :: concocted (pen, 0, wxALL | wxEXPAND, 5); }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };

struct grid_t
{   typedef wxGridSizer box_ptr;
    box_ptr* box_ = nullptr;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int across, const long style = wxEXPAND)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        box_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, across, 0, 0));
        if (box_ == nullptr) return false;
        pen -> Add (box_, 0, style, 5);
        return true; }
    bool invalid () const noexcept { return box_ == nullptr; } };

struct label_t : base_ctrl_t < wxStaticText >
{  template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const ::std::string& text, const long style = wxALIGN_CENTER_VERTICAL | wxALL)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        ctrl_ = GSL_OWNER (wxStaticText) (new wxStaticText (mummy, wxID_ANY, text.c_str (), wxDefaultPosition, wxDefaultSize, 0));
        if (ctrl_ == nullptr) return false;
        ctrl_ -> Wrap (-1);
        pen -> Add (ctrl_, 0, style, 5);
        return true; } };

struct line_t : base_ctrl_t < wxStaticLine >
{   template < class BOX > bool concoct (wxWindow *mummy, BOX* pen)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        ctrl_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (mummy, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
        return base_ctrl_t < wxStaticLine > :: concocted (pen, 0, wxALL | wxEXPAND, 5); } };

struct list_t : select_ctrl_t < wxListBox >
{   template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const vstr_t& values, const int sel = -1, const int width = 100, const long style = wxALIGN_CENTRE_VERTICAL)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        ctrl_ = GSL_OWNER (wxListBox) (new wxListBox (mummy, id, wxDefaultPosition, wxSize (width, 100)));
        if (ctrl_ == nullptr) return false;
        if (! select_ctrl_t < wxListBox > :: concoct (values, sel)) return false;
        return select_ctrl_t < wxListBox > :: concocted (pen, 2, style, 5); }
    void erase (const int n)
    {   PRESUME (! invalid (), __FILE__, __LINE__);
        ctrl_ -> Delete (n); }
    void scroll (const int n) const
    {   PRESUME (! invalid (), __FILE__, __LINE__);
        ctrl_ -> EnsureVisible (n); }
    int find (const ::std::string& s, const bool mixed = false) const
    {   PRESUME (! invalid (), __FILE__, __LINE__);
        return ctrl_ -> FindString (s.c_str (), ! mixed); } };

struct radio_t : group_ctrl_t < wxRadioBox >
{   template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& text, const vstr_t& vs, const int sel = -1, const int dim = 1, const long style = wxRA_SPECIFY_ROWS)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        vws_t vws;
        for (auto s : vs) vws.push_back (s.c_str ());
        ctrl_ = GSL_OWNER (wxRadioBox) (new wxRadioBox (mummy, id, text.c_str (), wxDefaultPosition, wxDefaultSize, GSL_NARROW_CAST < int > (vws.size ()), vws.data (), dim, style));
        if (ctrl_ == nullptr) return false;
        if (! group_ctrl_t < wxRadioBox > :: concoct (sel)) return false;
        return group_ctrl_t < wxRadioBox > :: concocted (pen, 0, wxALIGN_CENTRE_HORIZONTAL, 5); }
    void enable (const bool b)
    {   group_ctrl_t < wxRadioBox >::enable (b); }
    void enable (const int n, const bool b)
    {   if (! invalid ()) ctrl_ -> Enable (n, b); } };

struct spin_t : base_ctrl_t < wxSpinCtrl >
{   int value_ = 0;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id = wxID_ANY, const ::std::string& def = ::std::string (), const int init = 0, const int mini = 0, const int maxi = 75)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        value_ = init;
        ctrl_ = GSL_OWNER (wxSpinCtrl) (new wxSpinCtrl (mummy, id, def.c_str (), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, mini, maxi, init));
        return base_ctrl_t < wxSpinCtrl > :: concocted (pen, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5); }
    void value (const int i) noexcept { value_ = i; }
    int value () const noexcept { return value_; }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };

struct text_t : base_ctrl_t < wxTextCtrl >
{   ::std::string value_;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id = wxID_ANY, const ::std::string& def = ::std::string (), const int width = 75)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        ctrl_ = GSL_OWNER (wxTextCtrl) (new wxTextCtrl (mummy, id, def.c_str (), wxDefaultPosition, wxDefaultSize, 0));
        if (ctrl_ == nullptr) return false;
        if (width > 0) ctrl_ -> SetMinSize (wxSize (width, -1));
        pen -> Add (ctrl_, 0, wxALL, 5);
        return true; }
    void clear () noexcept { value_.clear (); }
    void value (const ::std::string& i) { value_ = i; }
    ::std::string value () const { return value_; }
    bool TransferDataToWindow ();
    bool TransferDataFromWindow (); };
#endif // WX
