/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "spell/spell.h"
#include "main/context.h"

// for those who habitually spell correctly (unlike me)
bool check_identifier_spelling (nitpick& nits, const html_version& , const ::std::string& s)
{   typedef enum { d_none, d_johnson, d_anaesthesia, d_oz, d_collins, d_wiki } e_dictionary;
    const char* const dictionary [] =
    {   nullptr,
        "Samuel Johnson, A Dictionary of the English Language, first edition, Longman etc., MDCCLV",
        "A Dictionary of Anaesthesia, second edition, Oxford University Press, 2017",
        "Australian Oxford Dictionary, second edition, Oxford University Press, 2004",
        "Collins English Dictionary",
        "wikipedia, https://en.wikipedia.org/" };
    struct spellings
    {   const char* spell_ = nullptr;
        e_dictionary dict_ = d_none;
        const char* ref_ = nullptr;
        bool dialect_ = false; };
    spellings word [] =
    {   { "centre", d_johnson, "348" },
        { "color", d_none, nullptr, true },
        { "colour", d_johnson, "409" },
        { "organisation", d_none, nullptr },
        { "alternative", d_none, nullptr },
        { "anaesthesia", d_anaesthesia, nullptr },
        { "autocapitalise", d_none, nullptr },
        { "authorise", d_oz, nullptr },
        { "behaviour", d_johnson, "225" },
        { "catalogue", d_johnson, "340" },
        { "colourist", d_none, nullptr },
        { "coworker", d_none, nullptr },
        { "dialogue", d_johnson, "585" },
        { "grey", d_collins, nullptr },
        { "gynaecologic", d_wiki, "https://en.wikipedia.org/wiki/Gynaecology" },
        { "haematologic", d_none, nullptr },
        { "honour", d_none, nullptr },
        { "licence", d_none, nullptr },
        { "motorised", d_none, nullptr },
        { "neighbour", d_johnson, "1356" },
        { "normalise", d_none, nullptr },
        { "optimise", d_none, nullptr },
        { "organiser", d_none, nullptr },
        { "organise", d_none, nullptr },
        { "paediatric", d_none, nullptr },
        { "parlour", d_johnson, "1452" },
        { "penciller", d_none, nullptr },
        { "randomised", d_none, nullptr },
        { "referrer", d_wiki, "https://en.wikipedia.org/wiki/HTTP_referer#Etymology" },
        { "speciality", d_johnson, "1895" },
        { "sought", d_none, nullptr },
        { "theatre", d_johnson, "2042" },
        { "tyre", d_none, nullptr },
        { nullptr, d_none, nullptr } };
    typedef ssc_map < ::std::string, spellings > mdst_t;
    static mdst_t ms;
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26446 26482)
#endif // _MSC_VER
    if (ms.empty ())
        for (::std::size_t i = 0; word [i].spell_ != nullptr; ++i)
            ms.insert (mdst_t::value_type (word [i].spell_, word [i]));
    ::std::string ss (::boost::algorithm::to_lower_copy (trim_the_lot_off (s)));
    mdst_t::const_iterator i = ms.find (ss);
    if (i != ms.cend ())
    {   if (i -> second.dict_ != d_none)
            if (dictionary [i -> second.dict_] != nullptr)
            {   ::std::string ref (dictionary [i -> second.dict_]);
                if (i -> second.ref_ != nullptr)
                {   ref += ", page ";
                    ref += i -> second.ref_; }
                if (i -> second.dialect_)
                    nits.pick (nit_dialect, ed_dict, ref, es_info, ec_incorrectness, quote (i -> second.spell_), ", which is unrecognised, is American English: is standard English required?");
                else
                    nits.pick (nit_correct_spelling, ed_dict, ref, es_info, ec_incorrectness, quote (i -> second.spell_), " is standard English, not American English");
                return true; }
        if (i -> second.dialect_)
            nits.pick (nit_dialect, es_info, ec_incorrectness, quote (i -> second.spell_), ", which is unrecognised, is American English: is standard English required?");
        else
            nits.pick (nit_correct_spelling, es_info, ec_incorrectness, quote (i -> second.spell_), " is standard English, not American English");
        return true; }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
    ::std::string sss (ss);
    if (sss.length () > 60) sss = "text";
    for (::std::size_t x = 0; GSL_AT (word, x).spell_ != nullptr; ++x)
        if (ss.find (GSL_AT (word, x).spell_) != ::std::string::npos)
        {   if (GSL_AT (word, x).dict_ != d_none)
            {   PRESUME (GSL_AT (word, x).dict_ <= d_wiki, __FILE__, __LINE__);
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 6387 26446 26482) // unless, of course, you consider the preceding conditions, linter.
#endif // _MSC_VER
                ::std::string ref (dictionary [GSL_AT (word, x).dict_]);
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
                if (GSL_AT (word, x).ref_ != nullptr)
                {   ref += ", page ";
                    ref += GSL_AT (word, x).ref_; }
                if (GSL_AT (word, x).dialect_)
                    nits.pick (nit_dialect, ed_dict, ref, es_info, ec_incorrectness, quote (sss), " is unrecognised. It contains ", quote (GSL_AT (word, x).spell_), " which is American English. Is standard English required?");
                else
                    nits.pick (nit_correct_spelling, ed_dict, ref, es_info, ec_incorrectness, quote (sss), " is unrecognised. It contains ", quote (GSL_AT (word, x).spell_), ", which is standard English. Is American English required?"); }
            else if (GSL_AT (word, x).dialect_)
                nits.pick (nit_dialect, es_info, ec_incorrectness, quote (sss), " is unrecognised. It contains ", quote (GSL_AT (word, x).spell_), ", which is American English. Is standard English required?");
            else
                nits.pick (nit_correct_spelling, es_info, ec_incorrectness, quote (sss), " is unrecognised. It contains ", quote (GSL_AT (word, x).spell_), ", which is standard English. Is American English required?");
            return true; }
    return false; }

mssfl_uptr mssfl;

#ifndef NOSPELL
#include "base/type_master.h"
#include "utility/filesystem.h"
#include "parser/text.h"
#include "icu/lingo.h"
#include "icu/charset.h"
#include "icu/converter.h"
#include "utility/cache.h"

void add_spell_list (nitpick& nits, const ::std::string& lang, const ::boost::filesystem::path& fn)
{   ::std::string list;
    if (! cached_file (nits, fn, list, false) || list.empty ())
        nits.pick (nit_cannot_open, es_error, ec_init, quote (fn.string ()), " is missing, is inaccessible, is not text, is too big, or is empty");
    else
    {   VERIFY_NOT_NULL (mssfl.get (), __FILE__, __LINE__);
        mssfl -> insert (mssfl_t::value_type (lang, split_by_whitespace_and (list))); } }

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
{   PRESUME (context.spell (), __FILE__, __LINE__);
    for (auto a : alt)
        if (lang.no_case_compare (a, word))
        {   if (context.cased ()) nits.pick (nit_case, es_error, ec_spell, "should ", quote (word), " be ", quote (a), "?");
            return; }
    nits.pick (nit_misspelt, es_error, ec_spell, quote (enwotsit (word)), " may be misspelt");
    if (context.tell (es_info)) switch (alt.size ())
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
