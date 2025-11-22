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
#include "gui/gui-ctrls.h"
#include "type/type.h"
#include "gui/gui-data.h"

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

bool check_file_t::concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& caption, const ::boost::filesystem::path& value, const ::std::string& text, const ::std::string& pattern)
{	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
    return  box_.concoct < wxBoxSizer > (mummy, pen, 1) &&
            check_.concoct < grid_t::box_ptr > (mummy, box_.box_, id, caption, wxALL | wxALIGN_CENTRE_HORIZONTAL) &&
            file_.concoct < grid_t::box_ptr > (mummy, box_.box_, wxID_ANY, value, text, pattern); }

bool check_file_t::TransferDataToWindow ()
{   if	(invalid () ||
        ! file_.TransferDataToWindow ()) return false;
    click ();
    return true; }

bool check_file_t::TransferDataFromWindow ()
{   return	(! invalid ()) &&
            file_.TransferDataFromWindow (); }

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

bool css_version_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const e_css_version sel)
{	vstr_t vs;
    vs.push_back ("none");
    for (int n = 1; n <= css_version_max; ++n)
    {   ::std::string nm = type_master < t_css_version > :: base_name (static_cast < e_css_version > (n));
        if (nm == "2") nm = "2.1";
        else if ((nm.length () > 1) && (nm.at (1) >= '0') && (nm.at (1) <= '9')) nm = ::std::string ("20") + nm;
        vs.push_back (nm); }
    return text_drop_t < choice_t > :: concoct (mummy, pen, id, label, vs, sel, 80); }

bool html_version_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const int sel)
{	vstr_t vs;
    PRESUME (selection_count > 0, __FILE__, __LINE__)
    vs.reserve (selection_count);
    for (::std::size_t n = 0; n < selection_count; ++n)
        vs.push_back (selection_version [n].nice_name ());
    return text_drop_t < choice_t > :: concoct (mummy, pen, id, label, vs, (sel >= 0) ? sel : (GSL_NARROW_CAST < int  > (selection_count-1)), 125); }

bool label_spin_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const ::std::string& def, const int init, const int mini, const int maxi)
{	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
    PRESUME (! label.empty (), __FILE__, __LINE__);
    return  box_.concoct < wxBoxSizer > (mummy, pen, 2) &&
            label_.concoct < grid_t::box_ptr > (mummy, box_.box_, label, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
            spin_.concoct < grid_t::box_ptr > (mummy, box_.box_, id, def, init, mini, maxi); }

bool label_spin_t :: TransferDataToWindow ()
{	return	(! invalid ()) &&
            spin_.TransferDataToWindow ();  }

bool label_spin_t :: TransferDataFromWindow ()
{	return	(! invalid ()) &&
            spin_.TransferDataFromWindow (); }

bool label_text_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const ::std::string& def)
{	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
    PRESUME (! label.empty (), __FILE__, __LINE__);
    return  box_.concoct < wxBoxSizer > (mummy, pen, 2) &&
            label_.concoct < grid_t::box_ptr > (mummy, box_.box_, label, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL) &&
            text_.concoct < grid_t::box_ptr > (mummy, box_.box_, id, def, 250); }

bool label_text_t :: TransferDataToWindow ()
{	return	(! invalid ()) &&
            text_.TransferDataToWindow ();  }

bool label_text_t :: TransferDataFromWindow ()
{	return	(! invalid ()) &&
            text_.TransferDataFromWindow (); }

bool lingo_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const int sel)
{	vstr_t vs;
    for (::std::size_t n = 0; selection_lang [n] != nullptr; ++n)
        vs.push_back (selection_lang [n]);
    return text_drop_t < combo_t > :: concoct (mummy, pen, id, label, vs, (sel >= 0) ? sel : (GSL_NARROW_CAST < int  > (selection_count-1)), 75); }

::std::string lingo_t :: chosen () const
{   if (invalid ()) return ::std::string ();
    return ::std::string (drop_.ctrl_ -> GetValue ().c_str ()); } /* works elsewhere, not here. why? */

bool math_version_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const e_math_version sel)
{	vstr_t vs;
    PRESUME (selection_count > 0, __FILE__, __LINE__)
    vs.push_back ("none (derive from X/HTML)");
    vs.push_back ("MathML 1");
    vs.push_back ("MathML 2");
    vs.push_back ("MathML 3");
    vs.push_back ("MathML 4");
    vs.push_back ("MathML 4 core");
    return text_drop_t < choice_t > :: concoct (mummy, pen, id, label, vs, sel, 175); }

bool svg_version_t :: concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::std::string& label, const e_svg_version sel)
{	vstr_t vs;
    PRESUME (selection_count > 0, __FILE__, __LINE__)
    vs.push_back ("none (derive from HTML version)");
    vs.push_back ("SVG 1.0");
    vs.push_back ("SVG 1.1");
    vs.push_back ("SVG 1.2 Tiny");
    vs.push_back ("SVG 1.2 Full (May 2004 draft)");
    vs.push_back ("SVG 2.0");
    vs.push_back ("SVG 2.1 (November 2024 draft)");
    return text_drop_t < choice_t > :: concoct (mummy, pen, id, label, vs, sel, 185); }

bool text_folder_t::TransferDataToWindow ()
{   return	(! invalid ()) &&
            folder_.TransferDataToWindow (); }

bool text_folder_t::TransferDataFromWindow ()
{   return	(! invalid ()) &&
            folder_.TransferDataFromWindow (); }

bool text_folder_t::concoct (wxWindow *mummy, wxBoxSizer* pen, const int id, const ::boost::filesystem::path& value, const ::std::string& text)
{	VERIFY_NOT_NULL (pen, __FILE__, __LINE__);
    return  label_.concoct < wxBoxSizer > (mummy, pen, text.c_str (), wxALL) &&
            folder_.concoct < wxBoxSizer > (mummy, pen, id, value); }

#endif // WX
