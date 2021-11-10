/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "webmention/webmention.h"
#include "utility/common.h"
#include "main/context.h"

#define SOURCE "source"
#define TARGET "target"
#define CONTENT "content"
#define WHEN "when"

void webmention::read (nitpick& nits, const ::boost::property_tree::ptree& tree, const ::std::string& container)
{   source_.reset (nits, read_field < ::std::string > (tree, container, SOURCE));
    target_.reset (nits, read_field < ::std::string > (tree, container, TARGET));
    html_ = read_field < ::std::string > (tree, container, CONTENT);
    when_ = read_field < ::std::string > (tree, container, WHEN);
    activity_ = act_static;
    invalid_ = false; }

void webmention::write (::boost::property_tree::ptree& tree, const ::std::string& container)
{   if (invalid_) return;
    write_field < ::std::string > (tree, container, SOURCE, source_.original ());
    write_field < ::std::string > (tree, container, TARGET, target_.original ());
    write_field < ::std::string > (tree, container, CONTENT, html_);
    write_field < ::std::string > (tree, container, WHEN, when_); }

webmention::webmention (const url& source, const url& target, const ::std::string& html)
    : source_ (source), target_ (target), html_ (html), invalid_ (false), activity_ (act_unknown)
{   when_ = ::boost::posix_time::to_iso_extended_string (::boost::posix_time::second_clock::universal_time ()); }

int webmention::compare (const webmention& w)
{   int res = source_.compare (w.source_);
    if (res == 0) res = target_.compare (w.target_);
    if (res == 0) res = html_.compare (w.html_);
    return res; }

int webmention::compare_updated (const webmention& w)
{   int res = source_.compare (w.source_);
    if (res == 0) res = target_.compare (w.target_);
    return res; }

::std::string webmention::report () const
{   ::std::string res ("source=");
    res += source_.original ();
    res += ",target=";
    res += target_.original ();
    res += ",when=";
    res += when_;
    res += ", html size=";
    res += ::boost::lexical_cast < ::std::string > (html_.length ());
    res += "\n";
    return res; }

::std::string webmention::apply_template (const vstr_t& templates)
{   static const char* const keywords [] = { SOURCE, TARGET, CONTENT, WHEN };
    ::std::string res;
    if (activity_ != act_unknown)
    {   res = templates.at (activity_);
        for (::std::size_t i = 0; i < 4; ++i)
        {   ::std::string macro = context.macro_start ();
            macro += ::gsl::at (keywords, i);
            macro += context.macro_end ();
            for (;;)
            {   const ::std::size_t loc = res.find (macro);
                if (loc == res.npos) break;
                ::std::string x = res.substr (0, loc);
                switch (i)
                {   case 0 : x += source_.absolute (); break;
                    case 1 : x += target_.absolute (); break;
                    case 2 : x += html_; break;
                    case 3 : x += when_; break;
                    default : break; }
                x += res.substr (loc + macro.length ());
                res = x; } } }
    return res; }
