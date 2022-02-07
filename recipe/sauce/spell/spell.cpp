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
#ifndef NOSPELL
#include "spell/spell.h"
#include "main/context.h"
#include "type/type_master.h"
#include "utility/filesystem.h"
#include "parser/text.h"
#include "icu/lingo.h"
#include "icu/charset.h"
#include "icu/converter.h"

mssfl_t mssfl;

void add_spell_list (nitpick& nits, const ::std::string& lang, const ::boost::filesystem::path& fn)
{   ::std::string list (normalise_utf8 (nits, read_text_file (nits, fn)));
    if (list.empty ())
        nits.pick (nit_cannot_open, es_error, ec_init, quote (fn.string ()), " is missing, is inaccessible, is not text, is too big, or is empty");
    else mssfl.insert (mssfl_t::value_type (lang, split_by_whitespace_and (list))); }

ustr_t langdict, dictlang;

void add_dict (const ::std::string& lang, const ::std::string& dict)
{   dictlang.emplace (dict, lang);
    langdict.emplace (lang, dict); }

::std::string get_dict_lang (const ::std::string& dict)
{   ustr_t::const_iterator i = dictlang.find (dict);
    if (i == dictlang.cend ()) return "";
    return i -> second; }

::std::string get_lang_dict (const ::std::string& lang)
{   ustr_t::const_iterator i = langdict.find (lang);
    if (i == langdict.cend ()) return "";
    return i -> second; }

void spell_tell (nitpick& nits, const lingo& lang, const ::std::string& word, const vstr_t& alt)
{   for (auto a : alt)
        if (lang.no_case_compare (a, word))
        {   if (context.cased ()) nits.pick (nit_case, es_error, ec_spell, "should ", quote (word), " be ", quote (a), "?");
            return; }
    nits.pick (nit_misspelt, es_error, ec_spell, quote (word), " may be misspelt");
    if (context.tell (e_info)) switch (alt.size ())
    {   case 0 : break;
        case 1 :
            nits.pick (nit_spell_perhaps, es_info, ec_spell, "was ", quote (alt.at (0)), " intended?");
            break;
        case 2 :
            nits.pick (nit_spell_perhaps, es_info, ec_spell, "was ", quote (alt.at (0)), " or ", quote (alt.at (1)), " intended?");
            break;
        default :
            {   ::std::string msg ("was ");
                const ::std::size_t q = alt.size () - 1;
                for (::std::size_t i = 0; i < q; ++i) msg += quote (alt.at (i)) + ", ";
                msg += " or " + quote (alt.at (q)) + " intended?";
                nits.pick (nit_spell_perhaps, es_info, ec_spell, msg);
                break; } } }
#endif // NOSPELL
