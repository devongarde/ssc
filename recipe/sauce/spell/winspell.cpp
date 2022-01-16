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

#ifdef _MSC_VER
#include "main/context.h"
#include <spellcheck.h>

ISpellCheckerFactory* scf = nullptr;

// https://docs.microsoft.com/en-us/windows/win32/intl/spell-checker-api

const int sweetmax = 8192;

typedef ssc_map < ::std::string, ISpellChecker* > mlf_t;
mlf_t mlf;
bool com = false;

void spell_init (nitpick& nits)
{   void init_ab ();
    init_ab ();
    HRESULT hr = CoInitializeEx (nullptr, COINIT_MULTITHREADED);
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
    ::std::string res;
    try
    {   WideCharToMultiByte (codepage, 0, pwsz, -1, p, len, NULL, NULL);
        res = ::std::string (p); }
    catch (...) { }
    delete [] p;
    return res; }

void spell (nitpick& nits, const ::std::string& lang, const ::std::string& text)
{   if (scf == nullptr) return;
    PRESUME (! lang.empty (), __FILE__, __LINE__);
    if (! context.spell ()) return;
    if (text.empty () || tart (text).empty ()) return;
    auto i = mlf.find (lang);
    ISpellChecker* isp = nullptr;
    HRESULT hr = 0;
    if (i == mlf.cend ())
    {   ::std::wstring wlang = ::std::wstring_convert <::std::codecvt_utf8 <wchar_t>> ().from_bytes (lang);
        hr = scf -> CreateSpellChecker (wlang.c_str (), &isp);
        if (FAILED (hr))
        {   mlf.insert (mlf_t::value_type (lang, nullptr));
            nits.pick (nit_no_spell, es_info, ec_spell, "No spelling checks available for ", lang);
            return; }
        VERIFY_NOT_NULL (isp, __FILE__, __LINE__);
        apply_wordlists (isp, lang);
        const ::std::string::size_type pos = lang.find ('-');
        if (pos != ::std::string::npos) apply_wordlists (isp, lang.substr (0, pos));
        else apply_wordlists (isp, precise_language (lang));
        apply_wordlists (isp, "");
        apply_wordlist (isp, context.spellings ());
        mlf.insert (mlf_t::value_type (lang, isp)); }
    else if (i -> second == nullptr) return;
    else isp = i -> second;
    PRESUME (! text.empty (), __FILE__, __LINE__);
    vstr_t tx (split_by_space (sweeten (text)));
    for (auto t : tx)
    {   IEnumSpellingError* whoopsie = nullptr;
        ::std::wstring w = ::std::wstring_convert <::std::codecvt_utf8 <wchar_t>> ().from_bytes (t);
        hr = isp -> ComprehensiveCheck (w.c_str (), &whoopsie);
        if (FAILED (hr)) continue;
        ISpellingError* typo = nullptr;
        IEnumString* suggested = nullptr;
        LPOLESTR rgelt = nullptr;
        ULONG pos = 0;
        ULONG len = 0;
        try
        {   for (;;)
            {   if (FAILED (whoopsie -> Next (&typo))) break;
                if (typo == nullptr) break;
                if (FAILED (typo -> get_StartIndex (&pos))) break;
                if (FAILED (typo -> get_Length (&len))) break;
                typo -> Release ();
                typo = nullptr;
                ::std::string booboo = t.substr (pos, len);
                nits.pick (nit_misspelt, es_error, ec_spell, quote (booboo), " may be misspelt");
                if (context.tell (e_info))
                {   hr = isp -> Suggest (w.c_str (), &suggested);
                    if (FAILED (hr)) suggested = nullptr;
                    else if (suggested != nullptr)
                    {   ::std::string alternatives, latest;
                        for (;;)
                        {   ULONG fetched = 0;
                            hr = suggested -> Next (1, &rgelt, &fetched);
                            if (fetched == 0) break;
                            if (! latest.empty ()) append (alternatives, ", ", quote (latest));
                            latest = ole2string (rgelt);
                            CoTaskMemFree (rgelt);
                            rgelt = nullptr; }
                        if (! latest.empty ()) append (alternatives, ", or ", quote (latest));
                        if (suggested != nullptr)
                        {   suggested -> Release ();
                            suggested = nullptr; }
                        if (! alternatives.empty ())
                            nits.pick (nit_spell_perhaps, es_info, ec_spell, "should ", quote (booboo), " be ", alternatives, "?"); } } } }
        catch (...)
        {   if (rgelt != nullptr) CoTaskMemFree (rgelt);
            if (suggested != nullptr) suggested -> Release ();
            if (typo != nullptr) typo -> Release (); }
        whoopsie -> Release (); } }
#endif // _MSC_VER
