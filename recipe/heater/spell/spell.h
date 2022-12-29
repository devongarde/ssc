/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "icu/lingo.h"

#define PUNCTUATION ",/;:"

typedef ssc_mm < ::std::string, vstr_t > mssfl_t;
typedef ::std::unique_ptr < mssfl_t > mssfl_uptr;
extern mssfl_uptr mssfl;

bool check_identifier_spelling (nitpick& nits, const html_version& v, const ::std::string& s);
void add_spell_list (nitpick& nits, const ::std::string& lang, const ::boost::filesystem::path& fn);

#ifndef NOSPELL
void check_spelling (nitpick& nits, const html_version& v, const lingo& lang, const ::std::string& text);
void spell_init (nitpick& nits);
vstr_t load_dictionaries (nitpick& nits);
void spell_free ();
void spell_terminate ();
void add_dict (const ::std::string& lang, const ::std::string& dict);
::std::string get_dict_lang (const ::std::string& dict);
::std::string get_lang_dict (const ::std::string& lang);
void spell_tell (nitpick& nits, const lingo& lang, const ::std::string& word, const vstr_t& alt);
::std::string get_supported_locales (nitpick& nits);
#else // NOSPELL
inline void check_spelling (nitpick& , const html_version& , const lingo& , const ::std::string& ) { }
inline void spell_init (nitpick& nits)
{   mssfl = mssfl_uptr (new mssfl_t);
    nits.pick (nit_no_spell, es_comment, ec_spell, "spell check unavailable"); }
inline vstr_t load_dictionaries (nitpick& ) { return vstr_t (); }
inline void spell_free () { }
inline void spell_terminate () { }
inline void add_dict (const lingo& , const ::std::string& ) { }
inline ::std::string get_lang_dict (const ::std::string& ) { return ::std::string (); }
inline ::std::string get_dict_lang (const ::std::string& ) { return ::std::string (); }
inline void spell_tell (nitpick& , const lingo& , const ::std::string& , const vstr_t& ) { }
inline ::std::string get_supported_locales (nitpick& ) { return ""; }
#endif // NOSPELL
