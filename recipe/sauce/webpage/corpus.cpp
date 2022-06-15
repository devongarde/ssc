/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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
#include "utility/filesystem.h"
#include "webpage/corpus.h"

::boost::filesystem::path corpus_file;
BOOST_OFSTREAM dump;

bool has_corpus () noexcept
{   return ! corpus_file.empty (); }

void open_corpus (nitpick& nits, const ::boost::filesystem::path& fn)
{   if (fn.empty ()) return;
    if (file_exists (fn))
        if (! delete_file (fn))
        {   nits.pick (nit_cannot_delete, es_catastrophic, ec_microformat, "Cannot remove existing ", corpus_file);
            return; }
    corpus_file = fn;
    try
    {   dump.open (BOOST_PSTR (corpus_file));
        if (! dump.bad ()) return; }
    catch (...) { }
    if (file_exists (fn)) delete_file (fn);
    nits.pick (nit_cannot_create_file, es_catastrophic, ec_microformat, "Cannot create ", corpus_file);
    corpus_file.clear (); }

void close_corpus (nitpick& nits)
{   if (! has_corpus ()) return;
    try
    {   dump.close (); return; }
    catch (...)
    { }
    nits.pick (nit_cannot_update, es_info, ec_microformat, "Cannot close ", corpus_file);
    corpus_file.clear (); }

void extend_corpus (nitpick& nits, const ::std::string& title, const ::std::string& site_path, const ::std::string& text,
    const ::std::string& author, const ::std::string& keywords, const ::std::string& description)
{   if (! has_corpus ()) return;
    if (dump.bad ()) return;
    if (text.empty ()) return;
    try
    {   dump    << "<page>\n<url>" << site_path << "</url>\n"
                << "<content>" << text << "</content>\n";
        if (! dump.bad () && ! title.empty ()) dump << "<title>" << title << "</title>\n";
        if (! dump.bad () && ! author.empty ()) dump << "<author>" << author << "</author>\n";
        if (! dump.bad () && ! description.empty ()) dump << "<description>" << description << "</description>\n";
        if (! dump.bad () && ! keywords.empty ()) dump << "<keywords>" << keywords << "</keywords>\n";
        if (! dump.bad ()) dump << "</page>\n";
        if (! dump.bad ()) return; }
    catch (...) { }
    nits.pick (nit_cannot_update, es_catastrophic, ec_microformat, "Cannot write to ", corpus_file);
    try
    {   dump.close (); }
    catch (...)
    { }
    corpus_file.clear (); }
