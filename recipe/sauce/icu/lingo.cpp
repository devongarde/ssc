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
#ifndef NOICU
#include "icu/lingo.h"
#include "icu/converter.h"
#include "icu/charset.h"
#include "spell/spell.h"

const int32_t arbitrary_max = 2048;
vstr_t lingo::dicts_;
bool lingo::borked_ = false;

// for example http://www.lingoes.net/en/translator/langcode.htm , https://www.andiamo.co.uk/resources/iso-language-codes/
struct ab_t
{   const char* const a_;
    const char* const b_; };

ab_t ab [] =
{   {   "ar", "ar-TN" },
    {   "bg", "bg-BG" },
    {   "de", "de-DE" },
    {   "en", STANDARD_ENGLISH },
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

int32_t from_utf8 (const ::std::string& s, UChar *sz, const int32_t len)
{   PRESUME (context.icu (), __FILE__, __LINE__);
    VERIFY_NOT_NULL (sz, __FILE__, __LINE__);
    UErrorCode err = U_ZERO_ERROR;
    int32_t actual = 0;
    u_strFromUTF8 (sz, len, &actual, s.c_str (), GSL_NARROW_CAST < int32_t > (s.length ()), &err);
    if (U_SUCCESS (err))
    {   sz [len-1] = 0;
        if (actual < len) return actual; }
    return 0; }

int32_t to_utf8 (UChar *sz, const int32_t len, ::std::string& s)
{   PRESUME (context.icu (), __FILE__, __LINE__);
    VERIFY_NOT_NULL (sz, __FILE__, __LINE__);
    UErrorCode err = U_ZERO_ERROR;
    int32_t actual = 0;
    char res [arbitrary_max] = { 0 };
    u_strToUTF8 (&GSL_AT (res, 0), arbitrary_max, &actual, sz, len, &err);
    if (U_SUCCESS (err))
        if (actual < arbitrary_max)
        {   s = res; return actual; }
    return 0; }

bool set_locale (::std::locale& loc, const ::std::string& lang)
{   try
    {   loc = ::std::locale (lang);
        return true; }
    catch (...) { }
    return false; }

lingo::lingo (nitpick& nits, const ::std::string& lang) : orig_ (lang)
{   if (lang.empty () || ! set_locale (locale_, lang))
        if (! set_locale (locale_, STANDARD_ENGLISH))
            locale_ = ::std::locale::classic ();
    if (context.icu ())
    {   int32_t actual = 0;
        UErrorCode err = U_ZERO_ERROR;
        char locale_id [arbitrary_max]; // Reminder to self: ICU locale_id is in non-standard format, namely _ not -.
        const int32_t uloc = uloc_forLanguageTag (standard_dialect (lang).c_str (), locale_id, arbitrary_max, &actual, &err);
        if ((actual == 0) || (actual >= arbitrary_max) || U_FAILURE (err))
            nits.pick (nit_locale, es_warning, ec_spell, "Unknown or unsupported dialect ", quote (lang));
        else
        {   locale_id_ = ::std::string (&GSL_AT (locale_id, 0));
            nits.pick (nit_locale, es_comment, ec_icu, "Half recognised ", lang);
            uloc_ = uloc; } } }

void lingo::init (nitpick& )
{   for (int i = 0; GSL_AT (ab, i).a_ != nullptr; ++i)
#ifdef DEBUG
        if (mab.find (::std::string (GSL_AT (ab, i).a_)) != mab.cend ())
            outstr.err (::std::string (GSL_AT (ab, i).a_) + " repeated in standard language table.\n");
        else
#endif // DEBUG
            mab.insert (::std::pair < ::std::string, ::std::string > (::std::string (GSL_AT (ab, i).a_), ::std::string (ab [i].b_))); }

void lingo::identify_dialects (nitpick& nits)
{   if (context.spell ()) dicts_ = load_dictionaries (nits); }

::std::string lingo::standard_dialect (const ::std::string& l)
{   if (l.empty ()) return STANDARD_ENGLISH;
    PRESUME (! mab.empty (), __FILE__, __LINE__);
    mab_t::const_iterator i = mab.find (l);
    if (i != mab.cend ()) return i -> second;
    return l; }

bool lingo::is_upper (const ::std::string& s) const
{   if (invalid () || ! context.icu ()) return iswupper (s.at (0));
    const int32_t len = GSL_NARROW_CAST < int32_t > (s.length ());
    const uint8_t* psz = reinterpret_cast <const uint8_t*> (s.c_str ());
    for (int32_t pos = 0; pos < len; )
    {   UChar32 ch;
        U8_NEXT_OR_FFFD (psz, pos, len, ch);
        if ((ch != 0xFFFD) && u_isULowercase (ch)) return false; }
    return true; }

bool lingo::is_lower (const ::std::string& s) const
{   if (invalid () || ! context.icu ()) return iswlower (s.at (0));
    const int32_t len = GSL_NARROW_CAST < int32_t > (s.length ());
    const uint8_t* psz = reinterpret_cast <const uint8_t*> (s.c_str ());
    for (int32_t pos = 0; pos < len; )
    {   UChar32 ch;
        U8_NEXT_OR_FFFD (psz, pos, len, ch);
        if ((ch != 0xFFFD) && u_isUUppercase (ch)) return false; }
    return true; }

bool lingo::is_alpha (const ::std::string& s) const
{   if (invalid () || ! context.icu ()) return iswalpha (s.at (0));
    const int32_t len = GSL_NARROW_CAST < int32_t > (s.length ());
    const uint8_t* psz = reinterpret_cast <const uint8_t*> (s.c_str ());
    for (int32_t pos = 0; pos < len; )
    {   UChar32 ch;
        U8_NEXT_OR_FFFD (psz, pos, len, ch);
        if ((ch != 0xFFFD) && ! u_isUAlphabetic (ch)) return false; }
    return true; }

bool lingo::is_space (const ::std::string& s) const
{   if (invalid () || ! context.icu ()) return iswspace (s.at (0));
    const int32_t len = GSL_NARROW_CAST < int32_t > (s.length ());
    const uint8_t* psz = reinterpret_cast <const uint8_t*> (s.c_str ());
    for (int32_t pos = 0; pos < len; )
    {   UChar32 ch;
        U8_NEXT_OR_FFFD (psz, pos, len, ch);
        if ((ch != 0xFFFD) && ! u_isUWhiteSpace (ch)) return false; }
    return true; }

::std::string lingo::to_upper (const ::std::string& s) const
{   if (invalid () || ! context.icu ()) return ::boost::to_upper_copy (s);
    UChar tmp [arbitrary_max] = { 0 };
    int32_t len = from_utf8 (s, &GSL_AT (tmp, 0), arbitrary_max);
    if (len > 0)
    {   UErrorCode err = U_ZERO_ERROR;
        UChar upc [arbitrary_max] = { 0 };
        const int32_t actual = u_strToUpper (&GSL_AT (upc, 0), arbitrary_max, tmp, len, locale_id_.c_str (), &err);
        if (U_SUCCESS (err))
        {   if (actual < arbitrary_max)
            {   GSL_AT (upc, arbitrary_max - 1) = 0;
                ::std::string res;
                len = to_utf8 (upc, actual, res);
                if (len > 0) return res; } } }
    return ::boost::to_upper_copy (s); }

::std::string lingo::to_lower (const ::std::string& s) const
{   if (invalid () || ! context.icu ()) return ::boost::to_lower_copy (s);
    UChar tmp [arbitrary_max] = { 0 };
    int32_t len = from_utf8 (s, &GSL_AT (tmp, 0), arbitrary_max);
    if (len > 0)
    {   UErrorCode err = U_ZERO_ERROR;
        UChar upc [arbitrary_max] = { 0 };
        const int32_t actual = u_strToLower (&GSL_AT (upc, 0), arbitrary_max, tmp, len, locale_id_.c_str (), &err);
        if (U_SUCCESS (err))
        {   if (actual < arbitrary_max)
            {   GSL_AT (upc, arbitrary_max - 1) = 0;
                ::std::string res;
                len = to_utf8 (upc, actual, res);
                if (len > 0) return res; } } }
    return ::boost::to_lower_copy (s); }

::std::string lingo::to_fold (const ::std::string& s) const
{   if (invalid () || ! context.icu ()) return s;
    UChar tmp [arbitrary_max] = { 0 };
    int32_t len = from_utf8 (s, &GSL_AT (tmp, 0), arbitrary_max);
    if (len > 0)
    {   UErrorCode err = U_ZERO_ERROR;
        UChar upc [arbitrary_max] = { 0 };
        const int32_t actual = u_strFoldCase (&GSL_AT (upc, 0), arbitrary_max, tmp, len, U_FOLD_CASE_DEFAULT, &err);
        if (U_SUCCESS (err))
        {   if (actual < arbitrary_max)
            {   GSL_AT (upc, arbitrary_max - 1) = 0;
                ::std::string res;
                len = to_utf8 (upc, actual, res);
                if (len > 0) return res; } } }
    return s; }

::std::string lingo::to_title (const ::std::string& s) const
{   if (invalid () || ! context.icu ()) return s;
    UChar tmp [arbitrary_max] = { 0 };
    int32_t len = from_utf8 (s, &GSL_AT (tmp, 0), arbitrary_max);
    if (len > 0)
    {   UErrorCode err = U_ZERO_ERROR;
        UChar ttl [arbitrary_max] = { 0 };
        UBreakIterator* pb = ubrk_open (UBRK_WORD, locale_id_.c_str (), &GSL_AT (tmp, 0), len, &err);
        if (U_SUCCESS (err) && (pb != nullptr)) try
        {   const int32_t actual = u_strToTitle (&GSL_AT (ttl, 0), arbitrary_max, tmp, len, pb, locale_id_.c_str (), &err);
            if (U_SUCCESS (err))
                if (actual < arbitrary_max)
                {   GSL_AT (ttl, arbitrary_max - 1) = 0;
                    ::std::string res;
                    len = to_utf8 (ttl, actual, res);
                    if (len > 0)
                    {   ubrk_close (pb);
                        pb = nullptr;
                        return res; } } }
        catch (...)
        {   if (pb != nullptr) ubrk_close (pb);
            throw; }
        if (pb != nullptr) ubrk_close (pb); }
    return s; }

bool lingo::compare (const ::std::string& lhs, const ::std::string& rhs) const
{   if (invalid () || ! context.icu ()) return lhs == rhs;
    UChar l [arbitrary_max] = { 0 };
    UChar r [arbitrary_max] = { 0 };
    const int32_t llen = from_utf8 (lhs, &GSL_AT (l, 0), arbitrary_max);
    const int32_t rlen = from_utf8 (rhs, &GSL_AT (r, 0), arbitrary_max);
    if (llen != rlen) return false;
    for (int32_t n = 0; n < llen; ++n)
        if (GSL_AT (l, n) != GSL_AT (r, n)) return false;
    return true; }

bool lingo::no_case_compare (const ::std::string& lhs, const ::std::string& rhs) const
{   if (invalid () || ! context.icu ()) return compare_no_case (lhs, rhs);
    UChar tmp [arbitrary_max] = { 0 };
    UChar l [arbitrary_max] = { 0 };
    UChar r [arbitrary_max] = { 0 };
    int32_t len = from_utf8 (lhs, &GSL_AT (tmp, 0), arbitrary_max);
    UErrorCode err = U_ZERO_ERROR;
    const int32_t llen = u_strToUpper (&GSL_AT (l, 0), arbitrary_max, tmp, len, locale_id_.c_str (), &err);
    if (U_FAILURE (err)) return compare_no_case (lhs, rhs);
    len = from_utf8 (rhs, &GSL_AT (tmp, 0), arbitrary_max);
    err = U_ZERO_ERROR;
    const int32_t rlen = u_strToUpper (&GSL_AT (r, 0), arbitrary_max, tmp, len, locale_id_.c_str (), &err);
    if (U_FAILURE (err)) return compare_no_case (lhs, rhs);
    if (llen != rlen) return false;
    for (int32_t n = 0; n < llen; ++n)
        if (GSL_AT (l, n) != GSL_AT (r, n)) return false;
    return true; }

vstr_t lingo::to_words (nitpick& nits, const ::std::string& s) const
{   if (invalid () || ! context.icu ()) return split_by_whitespace_and (s);
    vstr_t res;
    if (! s.empty ())
    {   UChar tmp [arbitrary_max] = { 0 };
        int32_t len = from_utf8 (s, &tmp [0], arbitrary_max);
        if (len > 0)
        {   UErrorCode err = U_ZERO_ERROR;
            UBreakIterator* pb = ubrk_open (UBRK_WORD, locale_id_.c_str (), &tmp [0], len, &err);
            if ((pb == nullptr) || ! U_SUCCESS (err))
            {   if (! borked_)
                    switch (err)
                    {   case U_MISSING_RESOURCE_ERROR :
                        case U_INTERNAL_PROGRAM_ERROR :
                        case U_MEMORY_ALLOCATION_ERROR :
                        case U_INVALID_TABLE_FORMAT :
                        case U_INVALID_TABLE_FILE :
                        case U_NO_SPACE_AVAILABLE :
                        case U_TOO_MANY_ALIASES_ERROR :
                        case U_COLLATOR_VERSION_MISMATCH :
                        case U_USELESS_COLLATOR_ERROR :
                            if (! context.test ()) nits.pick (nit_icu_installation, es_warning, ec_spell, "ICU error ", err, ": reverting to non-ICU processing");
                            borked_ = true;
                            break;
                        default : break; }
                return split_by_whitespace_and (s); }
            try
            {   int32_t prev = 0;
                for (int32_t pos = ubrk_first (pb); pos != UBRK_DONE; pos = ubrk_next (pb))
                {   bool ws = true;
                    UChar word [arbitrary_max] = { 0 };
                    for (int32_t i = prev; i < pos; ++i)
                    {   GSL_AT (word, i - prev) = GSL_AT (tmp, i);
                        if (ws) ws = u_isUWhiteSpace (GSL_AT (tmp, i)) || u_isspace (GSL_AT (tmp, i)); }
                    if (! ws)
                    {   GSL_AT (word, pos - prev) = 0;
                        ::std::string ss;
                        len = to_utf8 (word, pos - prev, ss);
                        if (len > 0) res.emplace_back (ss); }
                    prev = pos; } }
            catch (...)
            {   if (pb != nullptr) ubrk_close (pb);
                throw; }
            if (pb != nullptr) ubrk_close (pb); } }
    return res; }

::std::string lingo::language () const
{   if (invalid () || ! context.icu ())
    {   ::std::string::size_type pos = orig_.find_first_of ("_-");
        if (pos == ::std::string::npos) return orig_;
        return orig_.substr (0, pos); }
    ::std::string res;
    UErrorCode err = U_ZERO_ERROR;
    char l [arbitrary_max] = { 0 };
    const int32_t n = uloc_getLanguage (locale_id_.c_str (), &l [0], arbitrary_max, &err);
    if (U_SUCCESS (err))
    if (n < arbitrary_max) res = l;
    return res; }

::std::string lingo::region () const
{   if (invalid () || ! context.icu ())
    {   ::std::string::size_type pos = orig_.find_first_of ("_-");
        if (pos == ::std::string::npos) return ::std::string ();
        ::std::string::size_type pos2 = orig_.find_first_not_of (ALPHANUMERIC, pos);
        if (pos2 == ::std::string::npos) return orig_.substr (pos+1);
        return orig_.substr (pos+1, pos2-pos); }
    ::std::string res;
    UErrorCode err = U_ZERO_ERROR;
    char l [arbitrary_max] = { 0 };
    const int32_t n = uloc_getCountry (locale_id_.c_str (), &l [0], arbitrary_max, &err);
    if (U_SUCCESS (err))
    if (n < arbitrary_max) res = l;
    return res; }

::std::string lingo::dialect () const
{   if (region ().empty ()) return language ();
    return language () + "-" + region (); }

#endif // NOICU
