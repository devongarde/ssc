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

#pragma once
#include "feedback/nitpick.h"
#include "utility/common.h"

#define PUNCTUATION ",/;:"

typedef ssc_mm < ::std::string, vstr_t > mssfl_t;
extern mssfl_t mssfl;

::std::string precise_language (const ::std::string& l);
void add_spell_list (nitpick& nits, const ::std::string& lang, const ::boost::filesystem::path& fn);

#ifndef NOSPELL
void spell (nitpick& nits, const ::std::string& lang, const ::std::string& text);
void spell_init (nitpick& nits);
void spell_free ();
void spell_terminate ();
void add_dict (const ::std::string& lang, const ::std::string& dict);
::std::string get_dict (const ::std::string& lang);
::std::string sweeten (const ::std::string& s);
#else // NOSPELL
inline void spell (nitpick& , const ::std::string& , const ::std::string& ) { }
inline void spell_init (nitpick& nits)
{   nits.pick (nit_no_spell, es_comment, ec_spell, "Spelling checks are unavailable"); }
inline void spell_free () { }
inline void spell_terminate () { }
inline void add_dict (const ::std::string& , const ::std::string& ) { }
inline ::std::string get_dict (const ::std::string& ) { return ::std::string (); }
#endif // NOSPELL
