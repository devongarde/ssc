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
#ifdef _MSC_VER
#include <spellcheck.h>
#include "spell/spell.h"
#include "main/context.h"
#include "parser/text.h"
#include "icu/lingo.h"
#include "icu/converter.h"

// https://docs.microsoft.com/en-us/windows/win32/intl/spell-checker-api
typedef ssc_map < ::std::string, ISpellChecker* > mlf_t;
mlf_t mlf;
ISpellCheckerFactory* scf = nullptr;
constexpr int sweetmax = 8192;
bool com = false;

void spell_init (nitpick& nits)
{   HRESULT hr = CoInitializeEx (nullptr, COINIT_MULTITHREADED);
    if (FAILED (hr)) nits.pick (nit_no_spell, es_warning, ec_spell, "Cannot initialise COM (error ", hr, ")");
    else
    {   com = true;
        hr = CoCreateInstance (__uuidof (SpellCheckerFactory), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS (&scf));
        if (FAILED (hr)) nits.pick (nit_no_spell, es_warning, ec_spell, "Cannot initiate spelling factory (error ", hr, ")"); } }

void spell_free ()
{   for (auto f : mlf)
        if (f.second != nullptr) f.second -> Release ();
    mlf.clear ();
    if (scf != nullptr)
    {   scf -> Release ();
        scf = nullptr; }
    if (com)
    {   CoUninitialize();
        com = false; } }

vstr_t load_dictionaries (nitpick& ) { return vstr_t (); }
void spell_terminate () { }

void apply_wordlist (ISpellChecker* isp, const vstr_t& list)
{   VERIFY_NOT_NULL (isp, __FILE__, __LINE__);
    for (auto s : list)
        if (! s.empty ())
            for (auto ss : split_by_whitespace_and (s, PUNCTUATION))
                isp -> Ignore (::std::wstring_convert <::std::codecvt_utf8 <wchar_t>> ().from_bytes (ss).c_str ()); }

void apply_wordlists (ISpellChecker* isp, const ::std::string& lang)
{   for (mssfl_t::const_iterator i = mssfl.find (lang); i != mssfl.cend (); ++i)
        apply_wordlist (isp, i -> second); }

::std::string ole2string (LPOLESTR pwsz, UINT codepage = CP_UTF8)
{   const int len = WideCharToMultiByte (codepage, 0, pwsz, -1, 0, 0, NULL, NULL);
    char* p = new char [len];
    if (p == nullptr) return ::std::string ();
    ::std::string res;
    try
    {   WideCharToMultiByte (codepage, 0, pwsz, -1, p, len, NULL, NULL);
        res = ::std::string (p); }
    catch (...) { }
    delete [] p;
    return res; }

void spell (nitpick& nits, const html_version& v, const lingo& lang, const ::std::string& text)
{   if (scf == nullptr) return;
    if (! context.spell ()) return;
    if (text.empty () || tart (text).empty () || lang.invalid ()) return;
    ::std::string l (lingo::standard_dialect (lang.dialect ()));
    auto i = mlf.find (l);
    ISpellChecker* isp = nullptr;
    HRESULT hr = 0;
    if (i == mlf.cend ())
    {   ::std::wstring wlang = convert_to_wstring (l);
        hr = scf -> CreateSpellChecker (wlang.c_str (), &isp);
        if (FAILED (hr))
        {   mlf.insert (mlf_t::value_type (l, nullptr));
            nits.pick (nit_dictionary, es_info, ec_spell, PROG " cannot spellcheck ", quote (lang.original ()), " for lack of a dictionary.");
            return; }
        VERIFY_NOT_NULL (isp, __FILE__, __LINE__);
        apply_wordlists (isp, l);
        const ::std::string::size_type pos = l.find ('-');
        if (pos != ::std::string::npos) apply_wordlists (isp, l.substr (0, pos));
//        else apply_wordlists (isp, lingo::standard_dialect (l));
        apply_wordlists (isp, "");
        apply_wordlist (isp, context.spellings ());
        mlf.insert (mlf_t::value_type (l, isp)); }
    else if (i -> second == nullptr) return;
    else isp = i -> second;
    PRESUME (! text.empty (), __FILE__, __LINE__);
    vstr_t tx (lang.to_words (interpret_string (nits, v, text)));
    for (auto t : tx)
    {   if (t.empty ()) continue;
        if (! islower (t.at (0), lang.locale ()) && ! isupper (t.at (0), lang.locale ())) continue;
        IEnumSpellingError* whoopsie = nullptr;
        ::std::wstring w = convert_to_wstring (t);
        hr = isp -> ComprehensiveCheck (w.c_str (), &whoopsie);
        if (FAILED (hr)) continue;
        ISpellingError* typo = nullptr;
        IEnumString* suggested = nullptr;
        LPOLESTR word = nullptr;
        ULONG pos = 0;
        ULONG len = 0;
        try
        {   for (;;)
            {   typo = nullptr;
                if (FAILED (whoopsie -> Next (&typo))) break;
                if (typo == nullptr) break;
                if (FAILED (typo -> get_StartIndex (&pos))) break;
                if (FAILED (typo -> get_Length (&len))) break;
                typo -> Release ();
                typo = nullptr;
                ::std::string booboo = t.substr (pos, len);
                vstr_t alt;
                if (context.tell (e_info))
                {   w = convert_to_wstring (booboo);
                    hr = isp -> Suggest (w.c_str (), &suggested);
                    if (FAILED (hr)) suggested = nullptr;
                    else if (suggested != nullptr)
                    {   for (;;)
                        {   ULONG fetched = 0;
                            hr = suggested -> Next (1, &word, &fetched);
                            if (fetched == 0) break;
                            alt.push_back (ole2string (word));
                            CoTaskMemFree (word);
                            word = nullptr; }
                        suggested -> Release ();
                        suggested = nullptr; } }
                spell_tell (nits, lang, booboo, alt); } }
        catch (...)
        {   if (word != nullptr) CoTaskMemFree (word);
            if (suggested != nullptr) suggested -> Release ();
            if (typo != nullptr) typo -> Release (); }
        whoopsie -> Release (); } }

::std::string get_supported_locales (nitpick& nits)
{   if (! com) return "";
    IEnumString* sl = nullptr;
    scf -> get_SupportedLanguages (&sl);
    if (sl == nullptr)
    {   nits.pick (nit_wtf, es_catastrophic, ec_spell, "Windows seems to be broken (SpellCheckerFactory::get_SupportedLanguages returns NULL)");
        return ""; }
    ::std::string res;
    LPOLESTR dialect = nullptr;
    try
    {   for (;;)
        {   ULONG fetched = 0;
            const HRESULT hr = sl -> Next (1, &dialect, &fetched);
            if (fetched == 0) break;
            if (! res.empty ()) res += ", ";
            res += ole2string (dialect);
            CoTaskMemFree (dialect);
            dialect = nullptr; } }
    catch (...)
    {   if (dialect != nullptr) CoTaskMemFree (dialect); }
    return res; }

#endif // _MSC_VER
#endif // NOSPELL
