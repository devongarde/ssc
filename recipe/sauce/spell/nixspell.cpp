/*
ssc (static site checker)
File Info
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

#ifdef HUNSPELL
#include <hunspell.hxx>
#include "spell/spell.h"
#include "main/context.h"
#include "parser/text.h"
#include "icu/lingo.h"
::boost::filesystem::path dicts;

#define AFFINITY_EXTENSION ".aff"
#define DICTIONARY_EXTENSION ".dic"

class hun
{   typedef ::std::shared_ptr < Hunspell > hp_t;
    hp_t hun_;
public:
    bool valid () const { return (hun_.get () != nullptr); }
    void set_dead ()
    {   if (valid ()) hun_.reset (); }
    explicit hun (nitpick& nits, const ::boost::filesystem::path& p, const lingo& lang);
    int add (nitpick& nits, const ::std::string& word)
    {   PRESUME (valid (), __FILE__, __LINE__);
        int n = 0;
        try
        {   n = hun_ -> add (word); } // delightfully, the return value is undocumented
        catch (::std::exception& e)
        {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot add ", quote (word), " to dictionary (", e.what (), ")");
            n = -1; }
        catch (...)
        {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot add ", quote (word), " to dictionary (unknown exception)");
            n = -1; }
        return n; }
    const ::std::string version (nitpick& nits) const
    {   PRESUME (valid (), __FILE__, __LINE__);
        try
        {   return hun_ -> get_version_cpp (); }
        catch (::std::exception& e)
        {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot get hunspell version (", e.what (), ")"); }
        catch (...)
        {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot hunspell version (unknown exception)"); }
         return ""; }
    bool spell (nitpick& nits, const ::std::string& word) const
    {   PRESUME (valid (), __FILE__, __LINE__);
        try
        {   return hun_ -> spell (word); }
        catch (::std::exception& e)
        {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot check spelling of ", quote (word), " (", e.what (), ")"); }
        catch (...)
        {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot check spelling of ", quote (word), " (unknown exception)"); }
        return true; }
    vstr_t suggestions (nitpick& nits, const ::std::string& word) const
    {   PRESUME (valid (), __FILE__, __LINE__);
        try
        {   return hun_ -> suggest (word); }
        catch (::std::exception& e)
        {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot get suggestions for ", quote (word), " (", e.what (), ")"); }
        catch (...)
        {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot get suggestions for ", quote (word), " (unknown exception)"); }
       return vstr_t (); } };

typedef ssc_mm < ::std::string, hun > mhun_t;
mhun_t mh;

::std::string fix_hunspell_lang_param (const ::std::string& s)
    // hunspell almost but not quite uses ISO IDs for many dictionary names; it often switches '-' for '_'
{   ::std::string res (s);
    ::std::string::size_type pos = res.find ('_');
    if ((pos == 2) || (pos == 3)) res.replace (pos, 1, "-");
    return res; }

::std::string make_hunspell_lang_param (const ::std::string& s)
    // hunspell almost but not quite uses ISO IDs for many dictionary names; it often switches '-' for '_'
{   ::std::string res (s);
    ::std::string::size_type pos = res.find ('-');
    if ((pos == 2) || (pos == 3)) res.replace (pos, 1, "_");
    return res; }

hun::hun (nitpick& nits, const ::boost::filesystem::path& p, const lingo& lang)
{   ::std::string dialect (lingo::standard_dialect (lang.dialect ()));
    ::std::string base (get_lang_dict (dialect));
    if (base.empty ()) base = make_hunspell_lang_param (dialect);
    ::boost::filesystem::path aff (p);
    aff /= base; aff += AFFINITY_EXTENSION;
    ::boost::filesystem::path dic (p);
    dic /= base; dic += DICTIONARY_EXTENSION;
    if (! ::boost::filesystem::exists (dic))
    {   if (context.spell_deduced ())
            nits.pick (nit_no_spell, es_comment, ec_spell, "Cannot find the dictionary for ", quote (lang.dialect ()), " (seeking ", quote (dic.string ()), ")");
        else nits.pick (nit_no_spell, es_error, ec_spell, "Cannot find the dictionary for ", quote (lang.dialect ()), " (seeking ", quote (dic.string ()), ")");
        return; }
    if (! ::boost::filesystem::exists (aff))
    {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot find the affixes for ", quote (lang.dialect ()), " (seeking ", quote (aff.string ()), ")");
        return; }
    try
    {   hun_ = hp_t (new Hunspell (aff.string ().c_str (), dic.string ().c_str (), nullptr)); }
    catch (::std::exception& e)
    {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot create ", quote (lang.dialect ()), " spellchecker (", e.what (), ")");
        hun_ = nullptr;
        return; }
    catch (...)
    {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot create ", quote (lang.dialect ()), " spellchecker (unknown exception)");
        hun_ = nullptr;
        return; }
    if (hun_ == nullptr)
    {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot create ", quote (lang.dialect ()), " spellchecker");
        return; }
    nits.pick (nit_dictionary, es_comment, ec_spell, "Found dictionary for ", quote (lang.dialect ())); }

void spell_reset ()
{   mssfl = mssfl_uptr (new mssfl_t); }

void spell_init (nitpick& )
{   spell_reset (); }

void spell_free ()
{   for (mhun_t::iterator i = mh.begin (); i != mh.end (); ++i)
        i -> second.set_dead (); }  // Control-C

void apply_wordlist (nitpick& nits, mhun_t::iterator& hi, const vstr_t& list)
{   for (auto s : list)
        if (! s.empty ())
            for (auto ss : split_by_whitespace_and (s, PUNCTUATION))
                hi -> second.add (nits, ss); }

void apply_wordlists (nitpick& nits, mhun_t::iterator& hi, const ::std::string& lang)
{   VERIFY_NOT_NULL (mssfl.get (), __FILE__, __LINE__);
    for (mssfl_t::const_iterator i = mssfl -> find (lang); i != mssfl -> cend (); ++i)
        apply_wordlist (nits, hi, i -> second); }

void check_spelling (nitpick& nits, const html_version& v, const lingo& lang, const ::std::string& text)
{   if (! context.spell ()) return;
    if (text.empty () || tart (text).empty () || lang.invalid ()) return;
    ::std::string l (lang.dialect ());
    mhun_t::iterator hi = mh.find (l);
    if (hi != mh.end ())
    {   if (! hi -> second.valid ()) return; }
    else try
    {   if (dicts.empty ())
        {   dicts = context.spell_path ();
            if (dicts.empty ())
            {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot find dictionaries: use --spell.path to specify their location");
                context.spell (false);
                return; }
            if (! ::boost::filesystem::exists (dicts))
            {   nits.pick (nit_no_spell, es_error, ec_spell, dicts.string (), " does not exist");
                context.spell (false);
                return; }
            if (! ::boost::filesystem::is_directory (dicts))
            {   nits.pick (nit_no_spell, es_error, ec_spell, dicts.string (), " is not a directory");
                context.spell (false);
                return; } }
        hun ha (nits, dicts, lang);
        hi = mh.emplace (mhun_t::value_type (l, ha));
        if (! ha.valid ())
        {   ha.set_dead ();
            if (context.spell_deduced ()) nits.pick (nit_no_exec, es_comment, ec_spell, "Unable to initialise spellchecker for ", lang.original ());
            else nits.pick (nit_no_exec, es_error, ec_spell, "Unable to initialise spellchecker for ", lang.original ());
            return; }
        if (hi == mh.end ())
        {   if ((l.size () < 8) && (l.find_first_of ("-_") == ::std::string::npos))
            {   ::std::string standard = lingo::standard_dialect (l);
                if (standard != l) hi = mh.emplace (mhun_t::value_type (standard, ha)); }
            if (hi == mh.end ())
            {   nits.pick (nit_no_exec, es_error, ec_spell, "Attempt to prepare spellchecker for ", lang.original (), " failed badly");
                context.spell (false);
                return; } }
        if (! hi -> second.valid ())
        {   nits.pick (nit_no_exec, es_error, ec_spell, "Attempt to prepare spellchecker for ", lang.original (), " failed");
            hi -> second.set_dead ();
            return; }
        if (! hi -> second.valid ()) return;
        nits.pick (nit_no_exec, es_debug, ec_spell, "Spellchecker ", hi -> second.version (nits), " for ", lang.original (), " launched");
        apply_wordlist (nits, hi, context.spellings ());
        apply_wordlists (nits, hi, "");
        apply_wordlists (nits, hi, l);
        const ::std::string::size_type pos = l.find ('-');
        if (pos != ::std::string::npos) apply_wordlists (nits, hi, l.substr (0, pos));
        else apply_wordlists (nits, hi, l); }
    catch (const ::std::system_error& ex)
    {   nits.pick (nit_no_exec, es_error, ec_spell, "Exception when launching spellchecker for ", lang.original (), " (", ex.what (), ")");
        context.spell (false);
        return; }
    catch (...)
    {   nits.pick (nit_no_exec, es_error, ec_spell, "Unknown exception when launching spellchecker for ", lang.original ());
        context.spell (false);
        return; }
    PRESUME (! text.empty (), __FILE__, __LINE__);
    ::std::string i (interpret_string (nits, v, text));
    vstr_t tx (lang.to_words (nits, i));
    for (auto t : tx)
    {   if (t.empty ()) continue;
        if (! lang.is_alpha (t)) continue;
        if (! hi -> second.valid ()) break;
        if (! hi -> second.spell (nits, t)) spell_tell (nits, lang, t, hi -> second.suggestions (nits, t)); } }

vstr_t load_dictionaries (nitpick& nits)
{   if (! context.spell ()) return vstr_t ();
    ::boost::filesystem::path p (context.spell_path ());
    PRESUME (! p.empty (), __FILE__, __LINE__);
    if (!::boost::filesystem::exists (p) || ! ::boost::filesystem::is_directory (p))
    {   nits.pick (nit_no_spell, es_error, ec_spell, "well, that's weird: ", quote (p.string ()), " has been transmogrified");
        context.spell (false);
        return vstr_t (); }
    vstr_t res;
#ifdef NO_DIROPTS
    for (const ::boost::filesystem::directory_entry& i : ::boost::filesystem::directory_iterator (p))
#else // NO_DIROPTS
    for (const ::boost::filesystem::directory_entry& i : ::boost::filesystem::directory_iterator (p, ::boost::filesystem::directory_options::skip_permission_denied))
#endif // NO_DIROPTS
    {   ::boost::filesystem::path d (i.path ());
        if (! ::boost::filesystem::is_regular_file (d)) continue;
        if (BOOST_EXTENSION (d) != DICTIONARY_EXTENSION) continue;
        ::std::string s (d.stem ().string ());
        ::std::string l (get_dict_lang (s));
        if (l.empty ())
            switch (s.length ())
            {   case 0 :
		case 1 : continue;
		case 2 :
                case 3 : l = s; break;
                case 5 :
                case 6 :
                case 7 :
                case 8 : l = fix_hunspell_lang_param (s);
                         break;
                default : break; }
        if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_spell, "Found dictionary for ", l, " (", d.string (), ")");
        res.emplace_back (l); }
    return res; }

::std::string get_supported_locales (nitpick& )
{   return ""; }

#endif // HUNSPELL
