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

#define ANY_LINGO "*"

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

bool check_file_t::TransferDataToWindow ()
{   if	(invalid () ||
        ! file_.TransferDataToWindow ()) return false;
    click ();
    return true; }

bool check_file_t::TransferDataFromWindow ()
{   return	(! invalid ()) &&
            file_.TransferDataFromWindow (); }

bool check_folder_t::TransferDataToWindow ()
{   if	(invalid () ||
        ! folder_.TransferDataToWindow ()) return false;
    click ();
    return true; }

bool check_folder_t::TransferDataFromWindow ()
{   return	(! invalid ()) &&
            folder_.TransferDataFromWindow (); }

bool check_line_t :: TransferDataToWindow ()
{	return	(! invalid ()) &&
            check_.TransferDataToWindow (); }

bool check_line_t :: TransferDataFromWindow ()
{	return	(! invalid ()) &&
            check_.TransferDataFromWindow (); }

bool check_or_files_t :: TransferDataToWindow ()
{	if	(invalid () ||
        (! check_.TransferDataToWindow ()) ||
        (! file1_.TransferDataToWindow ()) ||
        (! file2_.TransferDataToWindow ())) return false;
    click ();
    return true;  }

bool check_or_files_t :: TransferDataFromWindow ()
{	return	(! invalid ()) &&
            check_.TransferDataFromWindow () &&
            file2_.TransferDataFromWindow (); }

void check_or_files_t::click ()
{   if (invalid ()) return;
    const bool b = check_.selected ();
    label1_.enable (b); file1_.enable (b);
    label2_.enable (b); file2_.enable (b); }

void check_or_files_t::enable (const bool b)
{   check_.enable (b);
    const bool bb = b && check_.selected ();
    label1_.enable (bb); file1_.enable (bb);
    label2_.enable (bb); file2_.enable (bb); }

void check_or_files_t::select (const bool b)
{   if (invalid ()) return;
    check_.select (b);
    click (); }

bool check_or_files_t::selected () const
{   if (invalid ()) return false;
    return check_.selected (); }

::boost::filesystem::path check_or_files_t::value1 () const
{   if (invalid () || ! check_.selected ()) return ::std::string ();
    return file1_.value (); }

::boost::filesystem::path check_or_files_t::value2 () const
{   if (invalid () || ! check_.selected ()) return ::std::string ();
    return file2_.value (); }

bool check_or_files_t::invalid () const noexcept
{   return  file1_.invalid () || file2_.invalid () || box_.invalid () || check_.invalid () ||
            label1_.invalid () || label2_.invalid (); }

bool check_or_text_t :: TransferDataToWindow ()
{	if (invalid ()) return false;
    check_.select (text_.value ().empty ());
    if ((! check_.TransferDataToWindow ()) ||
        (! text_.TransferDataToWindow ())) return false;
    click ();
    return true;  }

bool check_or_text_t :: TransferDataFromWindow ()
{	if (invalid () ||
        (! check_.TransferDataFromWindow ())) return false;
    if (! check_.selected ()) return text_.TransferDataFromWindow ();
    text_.clear (); return true; }

void check_or_text_t :: click ()
{   if (invalid ()) return;
    const bool b = ! check_.selected ();
    label_.enable (b);
    text_.enable (b); }

void check_or_text_t :: enable (const bool b)
{   check_.enable (b);
    const bool bb = b && (! check_.selected ());
    label_.enable (bb);
    text_.enable (bb); }

void check_or_text_t :: select (const bool b)
{   if (invalid ()) return;
    check_.select (b);
    if (b) text_.clear ();
    click (); }

bool check_or_text_t :: selected () const
{   if (invalid ()) return false;
    return check_.selected (); }

void check_or_text_t :: value (const ::std::string& s)
{   check_.select (s.empty ());
    text_.value (s); }

::std::string check_or_text_t :: value () const
{   if (invalid () || check_.selected ()) return ::std::string ();
    return text_.value (); }

bool check_or_text_t :: invalid () const noexcept
{   return text_.invalid () || box_.invalid () || check_.invalid () || label_.invalid (); }

vstr_t css_version_t::inner_concoct () const
{	vstr_t vs;
    vs.push_back ("none");
    for (int n = 1; n <= css_version_max; ++n)
    {   ::std::string nm = type_master < t_css_version > :: base_name (GSL_NARROW_CAST < e_css_version > (n));
        if (nm == "2") nm = "2.1";
        else if ((nm.length () > 1) && (nm.at (1) >= '0') && (nm.at (1) <= '9')) nm = ::std::string ("20") + nm;
        vs.push_back (nm); }
    return vs; }

vstr_t element_choice_t::inner_concoct () const
{	vstr_t vs;
    vs.push_back ("any");
    for (int n = first_element_tag; n < last_element_tag; ++n)
        vs.push_back (::std::string ("<") + elem :: name (GSL_NARROW_CAST < e_element > (n)) + ">");
    return vs; }

int html_version_t::max_sel () const
{   return GSL_NARROW_CAST < int > (standard_html_ver.size () - 1); }

vstr_t html_version_t::inner_concoct () const
{	vstr_t vs;
    vs.reserve (standard_html_ver.size ());
    for (::std::size_t n = 0; n < standard_html_ver.size (); ++n)
        vs.push_back (standard_html_ver.at (n).nice_name ());
    return vs; }

bool label_spin_t :: TransferDataToWindow ()
{	return	(! invalid ()) &&
            spin_.TransferDataToWindow ();  }

bool label_spin_t :: TransferDataFromWindow ()
{	return	(! invalid ()) &&
            spin_.TransferDataFromWindow (); }

bool label_text_t :: TransferDataToWindow ()
{	return	(! invalid ()) &&
            text_.TransferDataToWindow ();  }

bool label_text_t :: TransferDataFromWindow ()
{	return	(! invalid ()) &&
            text_.TransferDataFromWindow (); }

int lingo_t::max_sel () const
{   return GSL_NARROW_CAST < int > (enum_n < t_lang, e_lang > :: value_count () + (wild_ ? 1 : 0)); }

vstr_t lingo_t::inner_concoct (const html_version& v) const
{	vstr_t vs;
    if (wild_) vs.push_back (ANY_LINGO);
    for (auto s : enum_n < t_lang, e_lang > :: value_vector (v))
        vs.push_back (s);
    return vs; }

::std::string lingo_t :: chosen () const
{   if (invalid ()) return ::std::string ();
    const int sel = selected ();
    if (sel < 0) return ::std::string (drop_.ctrl_ -> GetValue ().c_str ()); 
    if (! wild_) return drop_.value (sel);
    if (sel == 0) return ANY_LINGO;
    return drop_.value (sel-1); }

vstr_t math_version_t::inner_concoct () const
{	vstr_t vs;
    vs.push_back ("none (derive from X/HTML)");
    vs.push_back ("MathML 1");
    vs.push_back ("MathML 2");
    vs.push_back ("MathML 3");
    vs.push_back ("MathML 4");
    vs.push_back ("MathML 4 core");
    return vs; }

vstr_t svg_version_t::inner_concoct () const
{	vstr_t vs;
    vs.push_back ("none (derive from HTML version)");
    vs.push_back ("SVG 1.0");
    vs.push_back ("SVG 1.1");
    vs.push_back ("SVG 1.2 Tiny");
    vs.push_back ("SVG 1.2 Full (May 2004 draft)");
    vs.push_back ("SVG 2.0");
    vs.push_back ("SVG 2.1 (November 2024 draft)");
    return vs; }

bool text_folder_t::TransferDataToWindow ()
{   return	(! invalid ()) &&
            folder_.TransferDataToWindow (); }

bool text_folder_t::TransferDataFromWindow ()
{   return	(! invalid ()) &&
            folder_.TransferDataFromWindow (); }
#endif // WX
