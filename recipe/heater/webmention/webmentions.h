/*
ssc (static site checker)
Copyright (c) 2020 Dylan Harris
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

#pragma once
#include "webmention/webmention.h"

class webmentions
{   ::std::vector < webmention > w_;
    bool invalid_ = true;
    ::boost::filesystem::path control_filename_, generated_filename_;
    void make_generated_filename (const url& target);
    bool load_templates (vstr_t& templates);
public:
    webmentions () : invalid_ (true) { }
    webmentions (nitpick& nits, const ::boost::filesystem::path& filename, const url& target)
    {   invalid_ = ! read (nits, filename);
        make_generated_filename (target); }
    void swap (webmentions& w) noexcept
    {   w_.swap (w.w_);
        ::std::swap (invalid_, w.invalid_); }
    void reset ()
    {   w_.clear ();
        generated_filename_.clear ();
        invalid_ = control_filename_.string ().empty (); }
    bool exists (webmention& mensh);
    void merge (webmention& mensh);
    bool read (nitpick& nits, const ::boost::filesystem::path& filename);
    bool write (nitpick& nits);
    bool any_invalid () const;
    bool invalid () const { return invalid_; }
    bool create_html ();
    ::std::string report () const; };
