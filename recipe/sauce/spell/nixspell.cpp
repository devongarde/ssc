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

#ifdef GENNIX
#include "main/context.h"
#include <hunspell.hxx>
::boost::filesystem::path dicts;

class hun
{   typedef ::std::shared_ptr < Hunspell > hp_t;
    hp_t hun_;
public:
    bool valid () const { return (hun_.get () != nullptr); }
    void set_dead ()
    {   if (valid ()) hun_.reset (); }
    explicit hun (nitpick& nits, const ::boost::filesystem::path& p, const ::std::string& lang);
    int add (const ::std::string& word)
    {   PRESUME (valid (), __FILE__, __LINE__);
        return hun_ -> add (word); } // delightfully, the return value is undocumented
    const ::std::string& version () const
    {   PRESUME (valid (), __FILE__, __LINE__);
        return hun_ -> get_version_cpp (); }
    bool spell (const ::std::string& word) const
    {   PRESUME (valid (), __FILE__, __LINE__);
        return hun_ -> spell (word); }
    vstr_t suggestions (const ::std::string& word) const
    {   PRESUME (valid (), __FILE__, __LINE__);
        return hun_ -> suggest (word); } };

typedef ssc_mm < ::std::string, hun > mhun_t;
mhun_t mh;

::std::string fix_hunspell_lang_param (const ::std::string& lang)
    // hunspell almost but not quite uses ISO IDs for many dictionary names; it often switches '-' for '_'
{   ::std::string res (get_dict (lang));
    if (res.empty ())
    {   res = lang;
        ::std::string::size_type pos = res.find ('-');
        if (pos != ::std::string::npos)
            res.replace (pos, 1, "_"); }
    return res; }

hun::hun (nitpick& nits, const ::boost::filesystem::path& p, const ::std::string& lang)
{   ::std::string base (fix_hunspell_lang_param (lang));
    ::boost::filesystem::path aff (p);
    aff /= base; aff += ".aff";
    ::boost::filesystem::path dic (p);
    dic /= base; dic += ".dic";
    if (! ::boost::filesystem::exists (dic))
    {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot find the dictionary for ", quote (lang), " (seeking ", quote (dic.string ()), ")");
        return; }
    if (! ::boost::filesystem::exists (aff))
    {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot find the affices for ", quote (lang), " (seeking ", quote (aff.string ()), ")");
        return; }
    hun_ = hp_t (new Hunspell (aff.c_str (), dic.c_str ()));
    if (hun_ == nullptr)
    {   nits.pick (nit_no_spell, es_error, ec_spell, "Cannot create ", quote (lang), " spellchecker");
        return; } }

void spell_init (nitpick& )
{   void init_ab ();
    init_ab (); }

void spell_free ()
{   for (mhun_t::iterator i = mh.begin (); i != mh.end (); ++i)
        i -> second.set_dead (); }  // Control-C

void spell_terminate ()
{ }

void apply_wordlist (mhun_t::iterator& hi, const vstr_t& list)
{   for (auto s : list)
        if (! s.empty ())
            for (auto ss : split_by_whitespace_and (s, PUNCTUATION))
                hi -> second.add (ss); }

void apply_wordlists (mhun_t::iterator& hi, const ::std::string& lang)
{   for (mssfl_t::const_iterator i = mssfl.find (lang); i != mssfl.cend (); ++i)
        apply_wordlist (hi, i -> second); }

void spell (nitpick& nits, const ::std::string& lang, const ::std::string& text)
{   PRESUME (! lang.empty (), __FILE__, __LINE__);
    if (! context.spell ()) return;
    if (text.empty () || tart (text).empty ()) return;
    mhun_t::iterator hi = mh.find (lang);
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
        if (ha.valid ()) hi = mh.emplace (mhun_t::value_type (lang, ha));
        if (hi == mh.end ())
        {   nits.pick (nit_no_exec, es_error, ec_spell, "Attempt to prepare spellchecker for ", lang, " failed badly");
            context.spell (false);
            return; }
        if (! hi -> second.valid ())
        {   nits.pick (nit_no_exec, es_error, ec_spell, "Attempt to prepare spellchecker for ", lang, " failed");
            context.spell (false);
            return; }
        if (! hi -> second.valid ()) return;
        nits.pick (nit_no_exec, es_debug, ec_spell, "Spellchecker ", hi -> second.version (), " for ", lang, " launched");
        apply_wordlist (hi, context.spellings ());
        apply_wordlists (hi, "");
        apply_wordlists (hi, lang);
        const ::std::string::size_type pos = lang.find ('-');
        if (pos != ::std::string::npos) apply_wordlists (hi, lang.substr (0, pos));
        else apply_wordlists (hi, precise_language (lang)); }
    catch (const ::std::system_error& ex)
    {   nits.pick (nit_no_exec, es_error, ec_spell, "Exception when launching spellchecker for ", lang, " (", ex.what (), ")");
        context.spell (false);
        return; }
    catch (...)
    {   nits.pick (nit_no_exec, es_error, ec_spell, "Unknown exception when launching spellchecker for ", lang);
        context.spell (false);
        return; }
    PRESUME (! text.empty (), __FILE__, __LINE__);
    vstr_t tx (split_by_whitespace_and (sweeten (text), PUNCTUATION));
    for (auto t : tx)
    {   ::std::string respell;
        if (! hi -> second.valid ()) break;
        if (! hi -> second.spell (t))
        {   nits.pick (nit_misspelt, es_error, ec_spell, quote (t), " may be misspelt");
            vstr_t alts = hi -> second.suggestions (t);
            switch (alts.size ())
            {   case 0 : break;
                case 1 :
                    nits.pick (nit_spell_perhaps, es_info, ec_spell, "was ", quote (alts.at (0)), " intended?");
                    break;
                case 2 :
                    nits.pick (nit_spell_perhaps, es_info, ec_spell, "was either ", quote (alts.at (0)), " or ", quote (alts.at (1)), " intended?");
                    break;
                default :
                    {   ::std::string msg ("was ");
                        ::std::size_t q = alts.size () - 1;
                        for (::std::size_t i = 0; i < q; ++i) msg += quote (alts.at (i)) + ", ";
                        msg += " or " + quote (alts.at (q)) + " intended?";
                        nits.pick (nit_spell_perhaps, es_info, ec_spell, msg);
                        break; } } } } }
#endif // GENNIX
