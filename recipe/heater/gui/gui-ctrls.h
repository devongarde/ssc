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
#include "parser/html_version.h"

struct check_datetime_t
{   grid_t box_;
    check_t check_;
    datetime_t datetime_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    template < typename BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& caption)
    {	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        return  check_.concoct < BOX > (mummy, pen, id, caption, wxALL | wxALIGN_CENTRE_HORIZONTAL) &&
                box_.concoct < BOX > (mummy, pen, 2) &&
                datetime_.concoct < grid_t::box_ptr > (mummy, box_.box_); }
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
    template < typename BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& caption, const ::boost::filesystem::path& value, const ::std::string& text, const ::std::string& pattern)
    {	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        return  box_.concoct < BOX > (mummy, pen, 1) &&
                check_.concoct < grid_t::box_ptr > (mummy, box_.box_, id, caption, wxALL | wxALIGN_CENTRE_HORIZONTAL) &&
                file_.concoct < grid_t::box_ptr > (mummy, box_.box_, wxID_ANY, value, text, pattern); }
    void click () { if (! invalid ()) file_.enable (check_.selected ()); }
    void enable (const bool b) { if (invalid ()) return; check_.enable (b); file_.enable (b && check_.selected ()); }
    void value (const ::boost::filesystem::path& p) { file_.value (p); }
    ::boost::filesystem::path value () const
    {   if (invalid () || ! check_.selected ()) return ::boost::filesystem::path ();
        return file_.value (); }
    void select (const bool b) { if (invalid ()) return; check_.select (b); click (); }
    bool selected () const { if (invalid ()) return false; return check_.selected (); }
    bool invalid () const noexcept { return file_.invalid () || check_.invalid () || box_.invalid (); } };

struct check_folder_t
{   grid_t box_;
    check_t check_;
    folder_t folder_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    template < typename BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& caption, const ::boost::filesystem::path& value, const ::std::string& text)
    {	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        return  box_.concoct < BOX > (mummy, pen, 1) &&
                check_.concoct < grid_t::box_ptr > (mummy, box_.box_, id, caption, wxALL | wxALIGN_CENTRE_HORIZONTAL) &&
                folder_.concoct < grid_t::box_ptr > (mummy, box_.box_, wxID_ANY, value, text); }
    void click () { if (! invalid ()) folder_.enable (check_.selected ()); }
    void enable (const bool b) { if (invalid ()) return; check_.enable (b); folder_.enable (b && check_.selected ()); }
    void value (const ::boost::filesystem::path& p) { folder_.value (p); }
    ::boost::filesystem::path value () const
    {   if (invalid () || ! check_.selected ()) return ::boost::filesystem::path ();
        return folder_.value (); }
    void select (const bool b) { if (invalid ()) return; check_.select (b); click (); }
    bool selected () const { if (invalid ()) return false; return check_.selected (); }
    bool invalid () const noexcept { return folder_.invalid () || check_.invalid () || box_.invalid (); } };

struct check_line_t
{   check_t check_;
    line_t line_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    template < typename BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& caption)
    {	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        PRESUME (! caption.empty (), __FILE__, __LINE__);
        return  check_.concoct < BOX > (mummy, pen, id, caption) &&
                line_.concoct < BOX > (mummy, pen);	 }
    void enable (const bool b) { check_.enable (b); }
    bool selected () const { if (invalid ()) return false; return check_.selected (); }
    bool invalid () const noexcept { return check_.invalid () || line_.invalid (); } };

struct check_or_files_t
{   grid_t box_;
    check_t check_;
    label_t label1_, label2_, spacer_;
    filepick_t file1_, file2_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void click ();
    void enable (const bool b);
    template < typename BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& caption, const ::std::string& label1, const ::std::string& label2,
        const ::boost::filesystem::path& def1 = ::boost::filesystem::path (), const ::std::string& val1 = ::std::string (), const ::std::string& pat1 = ::std::string (),
        const ::boost::filesystem::path& def2 = ::boost::filesystem::path (), const ::std::string& val2 = ::std::string (), const ::std::string& pat2 = ::std::string ())
    {	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        PRESUME (! caption.empty (), __FILE__, __LINE__);
        return  box_.concoct < BOX > (mummy, pen, 2) &&
                check_.concoct < grid_t::box_ptr > (mummy, box_.box_, id, caption) &&
                spacer_.concoct < grid_t::box_ptr > (mummy, box_.box_, "", wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
                label1_.concoct < grid_t::box_ptr > (mummy, box_.box_, label1, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
                file1_.concoct < grid_t::box_ptr > (mummy, box_.box_, wxID_ANY, def1, val1, pat1) &&
                label2_.concoct < grid_t::box_ptr > (mummy, box_.box_, label2, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
                file2_.concoct < grid_t::box_ptr > (mummy, box_.box_, wxID_ANY, def2, val2, pat2); }
    void select (const bool b);
    bool selected () const;
    ::boost::filesystem::path value1 () const;
    ::boost::filesystem::path value2 () const;
    bool invalid () const noexcept;
    void value1 (const ::boost::filesystem::path& s)
    {   file1_.value (s); }
    void value2 (const ::boost::filesystem::path& s)
    {   file2_.value (s); } };

struct check_or_text_t
{   grid_t box_;
    check_t check_;
    label_t label_;
    text_t text_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void click ();
    void enable (const bool b);
    template < typename BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& caption, const ::std::string& label, const ::std::string& def = ::std::string ())
    {	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        PRESUME (! caption.empty (), __FILE__, __LINE__);
        return  box_.concoct < BOX > (mummy, pen, 3) &&
                check_.concoct < grid_t::box_ptr > (mummy, box_.box_, id, caption) &&
                label_.concoct < grid_t::box_ptr > (mummy, box_.box_, label, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
                text_.concoct < grid_t::box_ptr > (mummy, box_.box_, wxID_ANY, def, 200); }

    void select (const bool b);
    bool selected () const;
    ::std::string value () const;
    void value (const ::std::string& s);
    bool invalid () const noexcept; };

struct label_spin_t
{   grid_t box_;
    label_t label_;
    spin_t spin_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    template < typename BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& label, const ::std::string& def = ::std::string (), const int init = 0, const int mini = 0, const int maxi = 75)
    {	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        PRESUME (! label.empty (), __FILE__, __LINE__);
        return  box_.concoct < BOX > (mummy, pen, 2) &&
                label_.concoct < grid_t::box_ptr > (mummy, box_.box_, label, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
                spin_.concoct < grid_t::box_ptr > (mummy, box_.box_, id, def, init, mini, maxi); }
    void value (const int v) noexcept
    { spin_.value (v); }
    int value () const noexcept
    { return spin_.value (); }
    void enable (const bool b)
    { label_.enable (b); spin_.enable (b); }
    bool invalid () const noexcept
    { return spin_.invalid () || box_.invalid () || label_.invalid (); } };

struct label_text_t
{   grid_t box_;
    label_t label_;
    text_t text_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void value (const ::std::string& i) { text_.value (i); }
    ::std::string value () const { return text_.value (); }
    template < typename BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& label, const ::std::string& def = ::std::string ())
    {	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        PRESUME (! label.empty (), __FILE__, __LINE__);
        return  box_.concoct < BOX > (mummy, pen, 2) &&
                label_.concoct < grid_t::box_ptr > (mummy, box_.box_, label, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
                text_.concoct < grid_t::box_ptr > (mummy, box_.box_, id, def, 225); }
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
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& label, const vstr_t& values, const int sel = -1, const int width = 100)
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        PRESUME (! label.empty (), __FILE__, __LINE__);
        return  box_.template concoct < BOX > (mummy, pen, 2) &&
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
    vstr_t inner_concoct () const;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& label, const data_t sel = def_sel ())
    {	return text_drop_t < choice_t > :: concoct < BOX > (mummy, pen, id, label, inner_concoct (), sel, 100); }
    data_t selected () const { return GSL_NARROW_CAST < data_t > (text_drop_t < choice_t >::selected ()); }
    void select (const data_t sel) { text_drop_t < choice_t >::select (sel); } };

struct element_choice_t : text_drop_t < choice_t >
{   typedef e_element data_t;
    static data_t def_sel () noexcept { return GSL_NARROW_CAST < data_t > (elem_body - first_element_tag + 1); }
    vstr_t inner_concoct () const;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& label, const data_t sel = def_sel ())
    {	return text_drop_t < choice_t > :: concoct < BOX > (mummy, pen, id, label, inner_concoct (), sel, 180); }
    data_t selected () const { return GSL_NARROW_CAST < data_t > (text_drop_t < choice_t >::selected ()); }
    void select (const data_t sel) { text_drop_t < choice_t >::select (sel); } };

struct html_version_t : text_drop_t < choice_t >
{   vstr_t inner_concoct () const;
    int max_sel () const;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& label, const int sel = -1)
    {	return text_drop_t < choice_t > :: concoct < BOX > (mummy, pen, id, label, inner_concoct (), (sel >= 0) ? sel : max_sel (), 120); } };

struct lingo_t : text_drop_t < combo_t >
{   bool wild_ = false;
    vstr_t inner_concoct (const html_version& v) const;
    int max_sel () const;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const html_version& v, const int id, const ::std::string& label, const int sel = -1, const bool wild = false)
    {	wild_ = wild;
        return text_drop_t < combo_t > :: concoct < BOX > (mummy, pen, id, label, inner_concoct (v), (sel >= 0) ? sel : max_sel (), 100); }
    int find (const ::std::string& s) const { return drop_.ctrl_ -> FindString (s.c_str ()); }
    ::std::string chosen () const; };

struct math_version_t : text_drop_t < choice_t >
{   typedef e_math_version data_t;
    static data_t def_sel () noexcept { return math_none; }
    vstr_t inner_concoct () const;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& label, const data_t sel = def_sel ())
    {	return text_drop_t < choice_t > :: concoct < BOX > (mummy, pen, id, label, inner_concoct (), sel, 100); }
    data_t selected () const { return GSL_NARROW_CAST < data_t > (text_drop_t < choice_t >::selected ()); }
    void select (const data_t sel) { text_drop_t < choice_t >::select (sel); } };

struct svg_version_t : text_drop_t < choice_t >
{   typedef e_svg_version data_t;
    static data_t def_sel () noexcept { return sv_none; }
    vstr_t inner_concoct () const;
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& label, const data_t sel = def_sel ())
    {	return text_drop_t < choice_t > :: concoct < BOX > (mummy, pen, id, label, inner_concoct (), sel, 100); }
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
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::std::string& caption, const typename DROP::data_t sel = DROP::def_sel ())
    {	VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
        VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        return  box_.template concoct < BOX > (mummy, pen, wxALIGN_CENTRE) &&
                drop_.concoct (mummy, box_.box_, id, caption, sel); }
    bool invalid () const noexcept { return drop_.invalid () || box_.invalid () ; } };

struct text_folder_t
{   folder_t folder_;
    label_t label_;
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    template < class BOX > bool concoct (wxWindow *mummy, BOX* pen, const int id, const ::boost::filesystem::path& value, const ::std::string& text)
    {	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
        return  label_.concoct < BOX > (mummy, pen, text.c_str (), wxALL) &&
                folder_.concoct < BOX > (mummy, pen, id, value); }
    void value (const ::boost::filesystem::path& v) { folder_.value (v); }
    ::boost::filesystem::path value () const { return folder_.value (); }
    void enable (const bool b) { label_.enable (b); folder_.enable (b); }
    bool invalid () const noexcept { return folder_.invalid () || label_.invalid (); } };

#endif // WX
