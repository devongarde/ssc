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
    bool selected () const { return check_.selected (); }
    bool invalid () const noexcept { return datetime_.invalid () || check_.invalid () || box_.invalid (); } };

struct check_file_t
{   grid_t box_;
    check_t check_;
    filepick_t file_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& caption, const ::boost::filesystem::path& value, const ::std::string& text, const ::std::string& pattern);
    void click () { if (! invalid ()) file_.enable (check_.selected ()); }
    void enable (const bool b) { if (invalid ()) return; check_.enable (b); file_.enable (b && check_.selected ()); }
    void value (const ::boost::filesystem::path& p) { file_.value (p); }
    ::boost::filesystem::path value () const
    {   if (invalid () || ! check_.selected ()) return ::boost::filesystem::path ();
        return file_.value (); }
    void select (const bool b) { if (invalid ()) return; check_.select (b); click (); }
    bool selected () const { if (invalid ()) return false; return check_.selected (); }
    bool invalid () const noexcept { return file_.invalid () || check_.invalid () || box_.invalid (); } };

struct check_line_t
{   check_t check_;
    line_t line_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& caption);
    void enable (const bool b) { check_.enable (b); }
    bool selected () const { if (invalid ()) return false; return check_.selected (); }
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
    void select (const bool b) { if (invalid ()) return; check_.select (b); click (); }
    bool selected () const { if (invalid ()) return false; return check_.selected (); }
    void value (const ::std::string& s) { text_.value (s); }
    ::std::string value () const
    {   if (invalid () || ! check_.selected ()) return ::std::string ();
        return text_.value (); }
    bool invalid () const noexcept { return text_.invalid () || box_.invalid () || check_.invalid () || label_.invalid (); } };

struct label_spin_t
{   grid_t box_;
    label_t label_;
    spin_t spin_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void value (const int v) noexcept { spin_.value (v); }
    int value () const noexcept { return spin_.value (); }
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const ::std::string& def = ::std::string (), const int init = 0, const int mini = 0, const int maxi = 75);
    void enable (const bool b) { label_.enable (b); spin_.enable (b); }
    bool invalid () const noexcept { return spin_.invalid () || box_.invalid () || label_.invalid (); } };

struct label_text_t
{   grid_t box_;
    label_t label_;
    text_t text_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void value (const ::std::string& i) { text_.value (i); }
    ::std::string value () const { return text_.value (); }
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const ::std::string& def = ::std::string ());
    void enable (const bool b) { label_.enable (b); text_.enable (b); }
    bool invalid () const noexcept { return text_.invalid () || box_.invalid () || label_.invalid (); } };

template < typename DROP > struct text_drop_t
{   grid_t box_;
    label_t label_;
    DROP drop_;
    bool TransferDataToWindow ()
    {	return	(! invalid ()) &&
                drop_.TransferDataToWindow ();  }
    bool TransferDataFromWindow ()
    {	return	(! invalid ()) &&
                drop_.TransferDataFromWindow ();  }
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const vstr_t& values, const int sel = -1, const int width = 100)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        PRESUME (! label.empty (), __FILE__, __LINE__);
        return  box_.template concoct < wxBoxSizer > (mummy, pen, 2) &&
                label_.template concoct < grid_t::box_ptr > (mummy, box_.box_, label, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
                drop_.template concoct < grid_t::box_ptr > (mummy, box_.box_, id, values, sel, width); }
    void append (const ::std::string& s) { drop_.append (s); }
    void enable (const bool b) { drop_.enable (b); label_.enable (b); }
    int selected () const { return drop_.selected (); }
    void select (const int sel) { drop_.select (sel); }
    bool invalid () const noexcept { return label_.invalid () || box_.invalid () || drop_.invalid (); } };

struct css_version_t : text_drop_t < choice_t >
{   typedef e_css_version data_t;
    static data_t def_sel () noexcept { return css_none; }
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const data_t sel = def_sel ());
    data_t selected () const { return GSL_NARROW_CAST < data_t > (text_drop_t < choice_t >::selected ()); }
    void select (const data_t sel) { text_drop_t < choice_t >::select (sel); } };

struct html_version_t : text_drop_t < choice_t >
{   bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const int sel = -1); };

struct lingo_t : text_drop_t < combo_t >
{   bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const int sel = -1);
    int find (const ::std::string& s) const { return drop_.ctrl_ -> FindString (s.c_str ()); }
    ::std::string chosen () const; };

struct math_version_t : text_drop_t < choice_t >
{   typedef e_math_version data_t;
    static data_t def_sel () noexcept { return math_none; }
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const data_t sel = def_sel ());
    data_t selected () const { return GSL_NARROW_CAST < data_t > (text_drop_t < choice_t >::selected ()); }
    void select (const data_t sel) { text_drop_t < choice_t >::select (sel); } };

struct svg_version_t : text_drop_t < choice_t >
{   typedef e_svg_version data_t;
    static data_t def_sel () noexcept { return sv_none; }
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const data_t sel = def_sel ());
    data_t selected () const { return GSL_NARROW_CAST < data_t > (text_drop_t < choice_t >::selected ()); }
    void select (const data_t sel) { text_drop_t < choice_t >::select (sel); } };

template < class DROP > struct drop_box_t
{   box_t box_;
    DROP drop_;
    bool TransferDataToWindow ()
    {	return (! invalid () && drop_.TransferDataToWindow ()); }
    bool TransferDataFromWindow ()
    {	return (! invalid () && drop_.TransferDataFromWindow()); }
    void value (const typename DROP::data_t v) { drop_.value (v); }
    typename DROP::data_t value () const { return drop_.value (); }
    void enable (const bool b) { drop_.enable (b); }
    typename DROP::data_t selected () const { return drop_.selected (); }
    void select (typename DROP::data_t x) { drop_.select (x); }
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& caption, const typename DROP::data_t sel = DROP::def_sel ())
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        return  box_.template concoct < wxBoxSizer > (mummy, pen, wxALIGN_CENTRE) &&
                drop_.concoct (mummy, box_.box_, id, caption, sel); }
    bool invalid () const noexcept { return drop_.invalid () || box_.invalid () ; } };

struct text_folder_t
{   folder_t folder_;
    label_t label_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    bool concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::boost::filesystem::path& value, const ::std::string& text);
    void value (const ::boost::filesystem::path& v) { folder_.value (v); }
    ::boost::filesystem::path value () const { return folder_.value (); }
    void enable (const bool b) { label_.enable (b); folder_.enable (b); }
    bool invalid () const noexcept { return folder_.invalid () || label_.invalid (); } };

#endif // WX
