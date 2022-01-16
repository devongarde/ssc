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
#include "spell/spell.h"
#include "main/context.h"
#include "type/type_master.h"
#include "utility/filesystem.h"

mssfl_t mssfl;

// for example http://www.lingoes.net/en/translator/langcode.htm , https://www.andiamo.co.uk/resources/iso-language-codes/
struct ab_t
{   const char* const a_;
    const char* const b_; };

ab_t ab [] =
{   {   "ar", "ar-TN" },
    {   "bg", "bg-BG" },
    {   "de", "de-DE" },
    {   "en", "en-GB" },
    {   "es", "es-ES" },
    {   "fr", "fr-FR" },
    {   "hr", "hr-HR" },
    {   "it", "it-IT" },
    {   "ms", "ms-MY" },
    {   "nl", "nl-NL" },
    {   "pt", "pt-PT" },
    {   "qu", "qu-PE" },
    {   "ro", "ro-RO" },
    {   "se", "se-FI" },
    {   "sr", "sr-SP" },
    {   "sv", "sr-SE" },
    {   "zh", "zh-CN" },
    {   nullptr, nullptr } };

typedef ssc_map < ::std::string, ::std::string > mab_t;
mab_t mab;

void init_ab ()
{   if (mab.empty ())
        for (int i = 0; ab [i].a_ != nullptr; ++i)
#ifdef DEBUG
            if (mab.find (::std::string (ab [i].a_)) != mab.cend ())
                context.err () << ::std::string (ab [i].a_) << " repeated in standard language table.\n";
            else
#endif // DEBUG
            mab.insert (::std::pair (::std::string (ab [i].a_), ::std::string (ab [i].b_))); }

::std::string precise_language (const ::std::string& l)
{   if (l.empty ()) return "en-US";
    PRESUME (! mab.empty (), __FILE__, __LINE__);
    mab_t::const_iterator i = mab.find (l);
    if (i != mab.cend ()) return i -> second;
    return l; }

void add_spell_list (nitpick& nits, const ::std::string& lang, const ::boost::filesystem::path& fn)
{   if (! lang.empty ())
    {   if (! test_value < t_lang > (nits, context.html_ver (), lang))
            nits.pick (nit_spell_lang, es_info, ec_init, PROG " doesn't know about ", quote (lang)); }
    ::std::string list (read_text_file (fn));
    if (list.empty ())
        nits.pick (nit_cannot_open, es_error, ec_init, quote (fn.string ()), " is missing, is inaccessible, is not text, is too big, or is empty");
    else mssfl.insert (mssfl_t::value_type (lang, split_by_whitespace_and (list))); }

#ifndef NOSPELL
ustr_t langdict;

::std::string get_dict (const ::std::string& lang)
{   ustr_t::const_iterator i = langdict.find (lang);
    if (i == langdict.cend ()) return ::std::string ();
    return i -> second; }

void add_dict (const ::std::string& lang, const ::std::string& dict)
{   langdict.emplace (lang, dict); }

::std::string sweeten (const ::std::string& s)
{   ::std::string res;
    for (auto ch : s)
        if ((ch == '-') || (ch == '\'') || (ch == '`') || iswlower (ch) || iswupper (ch) || iswdigit (ch)) res += ch;
        else res += ' ';
    return res; }

#endif // NOSPELL

