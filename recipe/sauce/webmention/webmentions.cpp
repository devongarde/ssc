/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public Licence for more details.

You should have received a copy of the GNU General Public
Licence along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "main/standard.h"
#ifdef HAS_WM
#include "webmention/webmentions.h"
#include "main/context.h"
#include "utility/filesystem.h"

// file should be:
// current state of webmentions
// thus contains full list of all current mentions at a specific point (page or page#id)

// Structure:
//  ssc
//  version
//  generated_include_filename?
//  count
//  [ source
//    target
//    content
//    when
//    ... ]
//  ...

// in HTML substitution
//
// maybe <!--#webmention id="xxxx" -->
//
// problem; requires writing ssi interpreter
//
// or have code produce an HTML snippet for inclusion in some manner
//
// or amend html directly
//
// <... class="xxxx">
//
// where xxxx is defined in config, default webmention. The mentions are inserted immediate after the > . any html element in a page's body can be used.
// when a mention has an id, swlc looks for an occurrence of xxxx in the id's HTML, or, if not found, the first occurrence of xxxx after the id is declared.
// problem: complex id behaviour
//
// or a new common attribute, webmention, optionally webmention="id", behaviour as noted above  (e.g. insert immediately after >) (alternatively, data-webmention)
//
// or a new element, <webmention ref="xxxx" />
//
// or a piece of magic text
//
// final alternative, requires fixing html parser to parse new elements, add element webmention. Maybe not. problem needs solving.
//
// or leave it to website author to define an include, e.g. <!--#include or <link rel="include" etc., & write file to be included
//

webmentions::webmentions (nitpick& nits, const ::boost::json::object& jo)
{

}

bool webmentions::save (nitpick& nits, ::boost::json::object& jo)
{

    return true; }


/*
bool webmentions::read (nitpick& nits, const ::boost::filesystem::path& filename)
{   if (filename.string ().empty ()) return false; // no webmention
    control_filename_ = filename;
    if (! file_exists (filename)) return true; // new webmention!
    invalid_ = true;
    ::boost::property_tree::ptree json;
    try
    {   ::boost::property_tree::read_json (filename.string (), json); }
    catch (...)
    {   nits.pick (nit_cannot_open, es_catastrophic, ec_webmention, "cannot open ", filename, ", or it is not in json format");
        return false; }
    if (! json.empty ()) try
    {   ::std::string version;
        control_filename_ = filename;
        if (! read_header (json, WM, version, control_filename_.string ())) return false;
        include_filename_ = read_field < ::std::string > (json, WM SEP GENERATE);
        const ::std::size_t count = read_field < ::std::size_t > (json, WM SEP COUNT);
        invalid_ = false;
        if (count <= 0) return true;
        w_.reserve (count);
        for (::std::size_t i = 0; i < count; ++i)
        {   ::std::string c = WM SEP;
            c += ::boost::lexical_cast < ::std::string > (i);
            w_.emplace_back (nits, json, c); } }
    catch (...)
    {   invalid_ = true; }
    if (any_invalid ())
    {   nits.pick (nit_cannot_read, es_catastrophic, ec_webmention, "Cannot read ", filename, "; are you sure it's a valid " PROG " file?");
        invalid_ = true;
        w_.clear ();
        return false; }
    return true; }

bool webmentions::write (nitpick& nits)
{   if (invalid_) return false;
    ::boost::property_tree::ptree json;
    try
    {   write_header (json, WM);
        write_field < ::std::size_t > (json, WM SEP COUNT, w_.size ());
        if (! include_filename_.empty ()) write_field < ::std::string > (json, WM SEP GENERATE, include_filename_.string ());
        for (::std::size_t i = 0; i < w_.size (); ++i)
        {   ::std::string count = WM SEP;
            count += ::boost::lexical_cast < ::std::string > (i);
            w_.at (i).write (json, count); } }
    catch (...)
    {   nits.pick (nit_cannot_write, es_catastrophic, ec_webmention, "Failure when preparing ", control_filename_);
        return false; }
    return replace_file (json, control_filename_); }

bool webmentions::exists (const webmention& mensh)
{   for (auto w : w_)
        if (w.compare (mensh) == 0)
        {   w.activity (act_static);
            return true; }
        else if (w.compare_updated (mensh) == 0)
        {   w.activity (act_update);
            return true; }
    return false; }

void webmentions::merge (webmention& mensh)
{   if (! mensh.invalid ())
        if (! exists (mensh))
        {   mensh.activity (act_insert);
            w_.push_back (mensh); } }
*/
bool webmentions::any_invalid () const
{   if (invalid_) return true;
    for (auto wm : w_)
    {   if (wm.invalid ()) return true; }
    return false; }

::std::string webmentions::report () const
{   ::std::string res ("webmentions:\n");
    for (::std::size_t i = 0; i < w_.size (); ++i)
    {   res += ::boost::lexical_cast < ::std::string > (i);
        res += ":";
        res += w_.at (i).report (); }
    return res; }
/*
void webmentions::make_include_filename (const url& target)
{   if (! include_filename_.empty ()) return;
    ::boost::filesystem::path base_path = context.write_path ();
    base_path /= target.path ();
    ::boost::filesystem::path filename = target.page ();
    if (filename.empty ()) filename = context.index ();
    ::std::string stub = filename.stem ().string ();
    ::std::string ext = filename.extension ().string ();
    ::std::string id = target.id ();
    if (! id.empty ())
    {   stub += "_";
        stub += id; }
    stub += context.stub ();
    stub += ext;
    stub += context.mention_extension ();
    include_filename_ = nix_path_to_local (base_path.string ()); // path can get /= wrong, mixing / & \: Windows handles it, dunno about other OSs.
    include_filename_ /= stub; }

::std::string webmentions::load_template (nitpick& nits, const ::std::string& supplied, const char* defname, const char* deftmp)
{   ::std::string res (template_path (nits, defname, supplied));
    if (! res.empty ()) return res;
    return deftmp; }

void webmentions::load_templates (nitpick& nits, vstr_t& templates)
{   templates = context.templates ();
    if (templates.size () <= 4) templates.resize (4);
    ::gsl::at (templates, act_insert) = load_template (nits, ::gsl::at (templates, act_insert), "new.tpl", NEW_SNIPPET);
    ::gsl::at (templates, act_update) = load_template (nits, ::gsl::at (templates, act_update), "change.tpl", CHANGE_SNIPPET);
    ::gsl::at (templates, act_delete) = load_template (nits, ::gsl::at (templates, act_delete), "delete.tpl", DELETE_SNIPPET);
    ::gsl::at (templates, act_static) = load_template (nits, ::gsl::at (templates, act_static), "static.tpl", STATIC_SNIPPET); }

bool webmentions::create_html (nitpick& nits)
{   vstr_t templates;
    load_templates (nits, templates);
    ::std::string content;
    for (auto wm : w_)
        content += wm.apply_template (templates);
    return write_text_file (include_filename_.string (), content); }
 */
#endif // HAS_WM
