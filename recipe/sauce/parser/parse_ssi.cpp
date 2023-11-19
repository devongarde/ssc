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
#include "utility/common.h"
#include "utility/filesystem.h"
#include "parser/parse_ssi.h"
#include "url/url.h"
#include "url/url_sanitise.h"
#include "webpage/page.h"
#include "webpage/directory.h"
#include "main/context.h"
#include "utility/quote.h"
#include "type/type.h"
#include "coop/lox.h"
#include "utility/cache.h"

CONSTEXPR ::std::size_t max_separation = 30;

ssi_compedium::ssi_compedium ()
    :   echomsg_ ("[Value Undefined]"), errmsg_ ("[Oops, something broke.]"), timefmt_ ("%Y %b %d %R"),
        sizefmt_abbrev_ (true)
    { }

void ssi_compedium::swap (ssi_compedium& ssi) noexcept
{   var_.swap (ssi.var_);
    dx_.swap (ssi.dx_);
    ::std::swap (echomsg_, ssi.echomsg_);
    ::std::swap (errmsg_, ssi.errmsg_);
    ::std::swap (timefmt_, ssi.timefmt_);
    ::std::swap (filename_, ssi.filename_);
    ::std::swap (sizefmt_abbrev_, ssi.sizefmt_abbrev_);
    ::std::swap (if_, ssi.if_);
    ::std::swap (iffed_, ssi.iffed_); }

void set_ssi_context (::std::string& ln, nitpick& nits, e_severity )
{   if (ln.empty ()) return;
    nits.set_context (0, ln);
    ln.clear (); }

template < class ENUM, e_type TYPE > bool value (::std::string& ln, nitpick& nits, const html_version& v, ENUM& e, const ::std::string& arg, bool required = false)
{   type_master < TYPE > x;
    nitpick knots;
    x.set_value (knots, v, uq (arg));
    if (x.good ())
    {   e = x.get ();
        return true; }
    if (required)
    {   set_ssi_context (ln, nits, es_error);
        nits.merge (knots); }
    return false; }

template < class ENUM, e_type TYPE > bool attribute_assign (::std::string& ln, nitpick& nits, const html_version& v, ENUM& e, ::std::string& arg, const ::std::string& assign)
{   vstr_t args (split_by_charset (assign, "="));
    if (args.size () != 2)
    {   set_ssi_context (ln, nits, es_error);
        nits.pick (nit_attribute_assignment, es_error, ec_ssi, "attribute assignment expected"); }
    else if (value < ENUM, TYPE > (ln, nits, v, e, uq (args.at (0)), true))
    {   arg = uq (args.at (1));
        return true; }
    return false; }

bool encoding (::std::string& ln, nitpick& nits, const html_version& v, e_ssi_encoding& e, const ::std::string& arg)
{   if (value < e_ssi_encoding, t_ssi_encoding > (ln, nits, v, e, uq (arg), true))
    {   if ((e == ssi_encoding_none) || (e == ssi_encoding_url)) return true;
        set_ssi_context (ln, nits, es_error);
        nits.pick (nit_unsupported_code, es_error, ec_ssi, "apologies, but " PROG " only supports the " QNONE " and 'url' encodings"); }
    return false; }

::std::string get_variable_value (::std::string& ln, nitpick& nits, const html_version& v, const page& p, const ssi_compedium& c, const ::std::string& var, bool required = false, bool noenv = false)
{   ::std::string arg (uq (var));
    ustr_t::const_iterator i = c.var_.find (arg);
    if (i != c.var_.cend ())
        arg = i -> second;
    else
    {   e_ssi_env env = ssi_error;
        time_t t = 0;
        if (value < e_ssi_env, t_ssi_env > (ln, nits, v, env, arg, required))
            if (noenv)
            {   set_ssi_context (ln, nits, es_error);
                nits.pick (nit_invalid_set, es_error, ec_ssi, "apologies, but " PROG " cannot set environment variables"); }
            else switch (env)
            {   case ssi_DATE_GMT :
                    {   ::std::ostringstream ss;
#ifndef NO_BOOST_DATE_FACET
                        GSL_OWNER (::boost::gregorian::date_input_facet) facet (new ::boost::gregorian::date_input_facet ("%D %T %Z"));
                        ss.imbue (::std::locale (::std::locale (), facet));
                        ss << ::boost::posix_time::second_clock::universal_time ();
#else // NO_BOOST_DATE_FACET
                        ss << ::boost::gregorian::to_iso_extended_string (::boost::gregorian::day_clock::universal_day ());
#endif // NO_BOOST_DATE_FACET
                        arg = ss.str (); }
                    break;
                case ssi_DATE_LOCAL :
                    {   ::std::ostringstream ss;
#ifndef NO_BOOST_DATE_FACET
                        GSL_OWNER (::boost::gregorian::date_input_facet) facet (new ::boost::gregorian::date_input_facet ("%D %T %Z"));
                        ss.imbue (::std::locale (::std::locale (), facet));
                        ss << ::boost::posix_time::second_clock::local_time ();
#else // NO_BOOST_DATE_FACET
                        ss << ::boost::gregorian::to_iso_extended_string (::boost::gregorian::day_clock::local_day ());
#endif // NO_BOOST_DATE_FACET
                        arg = ss.str (); }
                    break;
                case ssi_DOCUMENT_NAME :
                    arg = c.filename_;
                    break;
                case ssi_DOCUMENT_PATH_INFO :
                    VERIFY_NOT_NULL (p.get_directory (), __FILE__, __LINE__);
                    arg = p.get_directory () -> get_site_path ();
                    break;
                case ssi_DOCUMENT_URI :
                    {   arg = p.get_directory () -> get_site_path ();
                        if ((c.filename_.length () > 0) && (c.filename_.at (0) != '/'))
                            if (arg.length () == 0) arg = "/";
                            else if (arg.at (arg.length () - 1) != '/') arg += '/';
                        arg += c.filename_; }
                    break;
                case ssi_LAST_MODIFIED :
                    {   ::boost::filesystem::path x (p.get_directory () -> get_disk_path ());
                        x /= c.filename_;
                        t = get_last_write_time (x);
                        ::std::ostringstream ss;
#ifndef NO_BOOST_DATE_FACET
                        GSL_OWNER (::boost::gregorian::date_input_facet) facet (new ::boost::gregorian::date_input_facet ("%D %T %Z"));
                        ss.imbue (::std::locale (::std::locale (), facet));
                        ss << ::boost::posix_time::from_time_t (t);
#else // NO_BOOST_DATE_FACET
                        ss << ::boost::posix_time::to_iso_extended_string (::boost::posix_time::from_time_t (t));
#endif // NO_BOOST_DATE_FACET
                        arg = ss.str (); }
                    break;
                case ssi_error :
                    GRACEFUL_CRASH (__FILE__, __LINE__);
                    UNBREAKABLE;
                default : break; } }
    if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_ssi, "get_variable_value: ", quote (var), " == ", quote (arg));
    return arg; }

bool validate_file (::std::string& ln, nitpick& nits, const page& p, const ::std::string& f)
{   ::std::string file (uq (f));
    ::boost::filesystem::path af (p.get_directory () -> get_disk_path (nits, file));
    if (! file.empty ())
        if ((file.find ("../") != ::std::string::npos) || (file.at (0) == '/'))
        {   set_ssi_context (ln, nits, es_error);
            nits.pick (nit_ssi_include_error, ed_apache, "mod_include, https://httpd.apache.org/docs/current/mod/mod_include.html", es_error, ec_ssi, "the filename cannot contain \"../\", nor can it be an absolute path"); }
        else if (! file_exists (af))
        {   set_ssi_context (ln, nits, es_catastrophic);
            nits.pick (nit_cannot_read, es_catastrophic, ec_ssi, PROG " cannot find ", file); }
        else return true;
    return false; }

bool validate_virtual (::std::string& ln, nitpick& nits, const html_version& v, const ::std::string& vrt, url& u)
{   if (! vrt.empty ())
    {   u = url (nits, v, uq (vrt));
        if (u.invalid ())
        {   set_ssi_context (ln, nits, es_catastrophic);
            nits.pick (nit_cannot_read, es_catastrophic, ec_ssi, PROG " cannot find ", vrt);
            return false; }
        else if (! u.is_local ())
        {   set_ssi_context (ln, nits, es_error);
            nits.pick (nit_cannot_access, es_error, ec_ssi, "here, " PROG " can only access local files");
            return false; } }
    return true; }

::std::string config_command (::std::string& ln, nitpick& nits, const html_version& v, ssi_compedium& c, const vstr_t& args)
{   for (auto s : args)
    {   e_ssi_config e = ssi_config_echomsg;
        ::std::string arg;
        if (attribute_assign < e_ssi_config, t_ssi_config > (ln, nits, v, e, arg, s))
            switch (e)
            {   case ssi_config_errmsg : c.errmsg_ = arg; break;
                case ssi_config_echomsg : c.echomsg_ = arg; break;
                case ssi_config_sizefmt :
                    {   e_ssi_sizefmt f;
                        if (value < e_ssi_sizefmt, t_ssi_sizefmt > (ln, nits, v, f, arg, true))
                            c.sizefmt_abbrev_ = (f == ssi_size_abbrev); }
                    break;
                case ssi_config_timefmt :
                    {   if ((arg.length () > 48) || (arg.find ('%') == ::std::string::npos))
                        {   set_ssi_context (ln, nits, es_warning);
                            nits.pick (nit_invalid_config, es_warning, ec_ssi, "that timefmt value is dubious"); }
                        else c.timefmt_ = arg; } } }
    return ::std::string (); }

::std::string echo_command (::std::string& ln, nitpick& nits, const html_version& v, page& p, ssi_compedium& c, const vstr_t& args, ::std::time_t& updated)
{   ::std::string var, arg;
    e_ssi_encoding dec = ssi_encoding_none, enc = ssi_encoding_none;
    for (auto s : args)
    {   e_ssi_echo e = ssi_echo_decoding;
        if (attribute_assign < e_ssi_echo, t_ssi_echo > (ln, nits, v, e, arg, s))
            switch (e)
            {   case ssi_echo_var : var = arg; break;
                case ssi_echo_decoding : encoding (ln, nits, v, dec, arg); break;
                case ssi_echo_encoding : encoding (ln, nits, v, enc, arg); break; } }
    if (var.empty ())
    {   set_ssi_context (ln, nits, es_error);
        nits.pick (nit_invalid_echo, es_error, ec_ssi, "it is difficult to display the value of a variable without naming it.");
        return ::std::string (); }
    arg = get_variable_value (ln, nits, v, p, c, var, true);
    if (arg.empty ()) return c.echomsg_;
    if (dec == ssi_encoding_url) arg = decode (arg);
    if (enc == ssi_encoding_url) arg = sanitise (arg);
    if (arg.find ("<!--#") == ::std::string::npos) return arg;
    return parse_ssi (nits, v, p, c, arg, updated, false); }

::std::string flastmod_command (::std::string& ln, nitpick& nits, const html_version& v, const page& p, const ssi_compedium& c, const vstr_t& args)
{   ::std::string file, vrt, arg;
    ::std::time_t lwt = 0;
    url u;
    for (auto s : args)
    {   e_ssi_f e = ssi_f_file;
        if (attribute_assign < e_ssi_f, t_ssi_f > (ln, nits, v, e, arg, s))
            switch (e)
            {   case ssi_f_file : file = arg; break;
                case ssi_f_virtual : vrt = arg; break; } }
    if (file.empty () && vrt.empty ())
    {   set_ssi_context (ln, nits, es_error);
        nits.pick (nit_invalid_flastmod, es_error, ec_ssi, "<!--#FLASTMOD ... --> requires one of 'file' or 'virtual'"); }
    else if (validate_file (ln, nits, p, file)) try
        {       VERIFY_NOT_NULL (p.get_directory (), __FILE__, __LINE__);
                lwt = get_last_write_time (p.get_directory () -> get_disk_path (nits, file)); }
        catch (...) { }
    else if (validate_virtual (ln, nits, v, vrt, u))
    {   VERIFY_NOT_NULL (p.get_directory (), __FILE__, __LINE__);
        lwt = p.get_directory () -> url_last_write_time (nits, u); }
    else return c.errmsg_;

    if (lwt == 0)
    {   set_ssi_context (ln, nits, es_error);
        nits.pick (nit_ssi_include_error, es_error, ec_ssi, PROG " cannot determine that information");
        return c.errmsg_; }

    ::std::ostringstream ss;
#ifndef NO_BOOST_DATE_FACET
    const GSL_OWNER (::boost::gregorian::date_input_facet) facet (new ::boost::gregorian::date_input_facet ("%D %T %Z"));
    ss.imbue (::std::locale (::std::locale (), facet));
    ss << ::boost::posix_time::from_time_t (lwt);
#else // NO_BOOST_DATE_FACET
    ss << ::boost::posix_time::to_iso_extended_string (::boost::posix_time::from_time_t (lwt));
#endif // NO_BOOST_DATE_FACET
    return ss.str (); }

::std::string fsize_command (::std::string& ln, nitpick& nits, const html_version& v, const page& p, const ssi_compedium& c, const vstr_t& args)
{   ::std::string file, vrt, arg;
    uint64_t size = 0;
    url u;
    for (auto s : args)
    {   e_ssi_f e = ssi_f_file;
        if (attribute_assign < e_ssi_f, t_ssi_f > (ln, nits, v, e, arg, s))
            switch (e)
            {   case ssi_f_file : file = arg; break;
                case ssi_f_virtual : vrt = arg; break; } }
    if (vrt.empty () && file.empty ())
    {   set_ssi_context (ln, nits, es_error);
        nits.pick (nit_invalid_fsize, es_error, ec_ssi, "<!--#FSIZE ... --> requires one of 'file' or 'virtual'"); }
    else if (validate_file (ln, nits, p, file)) try
        {   VERIFY_NOT_NULL (p.get_directory (), __FILE__, __LINE__);
            size = get_file_size (p.get_directory () -> get_disk_path (nits, file)); }
        catch (...) { }
    else if (validate_virtual (ln, nits, v, vrt, u))
    {   VERIFY_NOT_NULL (p.get_directory (), __FILE__, __LINE__);
        size = p.get_directory () -> url_size (nits, u); }
    else return c.echomsg_;

    if (! c.sizefmt_abbrev_)
        return ::boost :: lexical_cast < ::std::string > (size);

    CONSTEXPR uint64_t k = 1024;
    CONSTEXPR uint64_t m = k * 1024;
    CONSTEXPR uint64_t g = m * 1024;
    CONSTEXPR uint64_t t = g * 1024;
    if (size > t) return ::boost::lexical_cast < ::std::string > (size / t) + "T";
    if (size > g) return ::boost::lexical_cast < ::std::string > (size / g) + "G";
    if (size > m) return ::boost::lexical_cast < ::std::string > (size / m) + "M";
    if (size > k) return ::boost::lexical_cast < ::std::string > (size / k) + "K";
    return ::boost::lexical_cast < ::std::string > (size); }

::std::string include_command (::std::string& ln, nitpick& nits, const html_version& v, page& p, ssi_compedium& c, const vstr_t& args, ::std::time_t& updated)
{   ::std::string file, vrt, onerror, arg, content;
    bool borked = false;
    url u;
    for (auto s : args)
    {   e_ssi_include e = ssi_include_file;
        if (attribute_assign < e_ssi_include, t_ssi_include > (ln, nits, v, e, arg, s))
            switch (e)
            {   case ssi_include_onerror :  set_ssi_context (ln, nits, es_error);
                                            nits.pick (nit_ssi_include_error, es_error, ec_ssi, "apologies, but " PROG " does not currently process 'onerror'");
                                            break;
                case ssi_include_file : file = arg; break;
                case ssi_include_virtual : vrt = arg; break; } }
    if (file.empty () && vrt.empty ())
    {   set_ssi_context (ln, nits, es_error);
        nits.pick (nit_ssi_include_error, es_error, ec_ssi, "<!--#INCLUDE ... --> requires one of 'file' or 'virtual'"); }
    else
    {   if (validate_file (ln, nits, p, file))
        {   VERIFY_NOT_NULL (p.get_directory (), __FILE__, __LINE__);
            ::boost::filesystem::path pt (p.get_directory () -> get_disk_path (nits, file));
            if (cached_file (nits, pt, content, borked))
                if (! borked) return parse_ssi (nits, v, p, c, content, updated); }
        else if (validate_virtual (ln, nits, v, vrt, u))
            if (! u.invalid ())
            {   ::std::time_t when = updated;
                VERIFY_NOT_NULL (p.get_directory (), __FILE__, __LINE__);
                if (cached_url (nits, v, p.get_directory (), u, content, when, borked))
                    if (! borked)
                    {   if (context.shadow_changed ())
                        {   nitpick knots;
                            nits.pick (nit_ssi, es_debug, ec_shadow, "SSI virtual ", p.get_directory () -> get_disk_path (knots, u), " last updated ", when);
                            if (when > updated) updated = when; }
                        if (! content.empty ())
                            return parse_ssi (nits, v, p, c, content, updated); } }
        set_ssi_context (ln, nits, es_error);
        if (! file.empty ()) nits.pick (nit_ssi_include_error, es_error, ec_ssi, PROG " cannot verify ", file);
        else if (! vrt.empty ()) nits.pick (nit_ssi_include_error, es_error, ec_ssi, PROG " cannot verify ", vrt); }
    return c.errmsg_; }

::std::string printenv_command (nitpick& , const ssi_compedium& c, const vstr_t& )
{   ::std::string res;
    bool started = false;
    for (ustr_t::const_iterator i = c.var_.cbegin (); i != c.var_.cend (); ++i)
    {   if (started) res += '\n'; else started = true;
        res += ::boost::algorithm::to_upper_copy (i -> first) + " = " + i -> second; }
    return res; }

::std::string set_command (::std::string& ln, nitpick& nits, const html_version& v, page& , ssi_compedium& c, const vstr_t& args)
{   ::std::string var, value, arg;
    e_ssi_encoding dec = ssi_encoding_none, enc = ssi_encoding_none;
    for (auto s : args)
    {   e_ssi_set e = ssi_set_decoding;
        if (attribute_assign < e_ssi_set, t_ssi_set > (ln, nits, v, e, arg, s))
            switch (e)
            {   case ssi_set_var : var = arg; break;
                case ssi_set_value : value = arg; break;
                case ssi_set_decoding : encoding (ln, nits, v, dec, arg); break;
                case ssi_set_encoding : encoding (ln, nits, v, enc, arg); break; } }
    if (var.empty ())
    {   set_ssi_context (ln, nits, es_error);
        nits.pick (nit_invalid_set, es_error, ec_ssi, "it is difficult to set the value of a variable without naming it"); }
    else
    {   if (dec == ssi_encoding_url) value = decode (value);
        if (enc == ssi_encoding_url) value = sanitise (value);
        ustr_t::iterator i = c.var_.find (var);
        if (context.tell (es_debug)) nits.pick (nit_debug, es_debug, ec_ssi, "setting ", quote (var), " to ", quote (value));
        if (i == c.var_.end ())
            c.var_.insert (ustr_t::value_type (var, value));
        else
            i -> second = value; }
    return ::std::string (); }

bool if_args (::std::string& ln, nitpick& nits, const html_version& v, const page& p, const ssi_compedium& c, const vstr_t& args)
{   ::std::string res;
    if (args.empty ())
    {   set_ssi_context (ln, nits, es_error);
        nits.pick (nit_ssi_if, es_error, ec_ssi, "<!--#IF--> needs a condition!");
        return true; }
    vstr_t z;
    for (auto s : args)
        z.push_back (get_variable_value (ln, nits, v, p, c, s));
    if (z.size () == 1)
        return ! z.at (0).empty ();
    if (z.size () == 2)
    {   if (z.at (0) == "!") return z.at (1).empty (); }
    else if (z.size () == 3)
    {   e_ssi_comparison e = ssi_comparison_and;
        if (value < e_ssi_comparison, t_ssi_comparison > (ln, nits, v, e, z.at (1)))
            switch (e)
            {   case ssi_comparison_and : return ! (z.at (0).empty () || z.at (2).empty ());
                case ssi_comparison_eq :  return (compare_no_case (z.at (0), z.at (2)));
                case ssi_comparison_ne :  return (! compare_no_case (z.at (0), z.at (2)));
                case ssi_comparison_ge :  return (z.at (0) >= z.at (2));
                case ssi_comparison_gt :  return (z.at (0) > z.at (2));
                case ssi_comparison_le :  return (z.at (0) <= z.at (2));
                case ssi_comparison_lt :  return (z.at (0) < z.at (2));
                case ssi_comparison_or :  return ! (z.at (0).empty () && z.at (2).empty ()); } }
    return false; }

::std::string if_command (::std::string& ln, nitpick& nits, const html_version& v, const page& p, ssi_compedium& c, const vstr_t& args, bool& inif)
{   if (inif)
        nits.pick (nit_ssi_if, es_error, ec_ssi, "Apologies, but " PROG, " does not support nested SSI conditionals.");
    else
    {   c.iffed_ = c.if_ = if_args (ln, nits, v, p, c, args);
        inif = true; }
    return ::std::string (); }

::std::string elif_command (::std::string& ln, nitpick& nits, const html_version& v, const page& p, ssi_compedium& c, const vstr_t& args, const bool inif)
{   if (! inif)
        nits.pick (nit_no_if, es_error, ec_ssi, "<!--#ELIF--> requires a preceding <!--#IF-->");
    else if (! c.iffed_)
        c.if_ = c.iffed_ = if_args (ln, nits, v, p, c, args);
    return ::std::string (); }

::std::string else_command (nitpick& nits, ssi_compedium& c, const bool inif)
{   if (! inif)
        nits.pick (nit_no_if, es_error, ec_ssi, "<!--#ELSE--> requires a preceding <!--#IF-->");
    else
        c.if_ = ! c.iffed_;
    return ::std::string (); }

::std::string endif_command (nitpick& nits, ssi_compedium& c, bool& inif)
{   if (! inif)
        nits.pick (nit_no_if, es_error, ec_ssi, "<!--#ENDIF--> requires a preceding <!--#IF-->");
    else
        c.if_ = true; c.iffed_ = inif = false;
    return ::std::string (); }

::std::string process_ssi (::std::string& ln, nitpick& nits, const html_version& v, page& p, ssi_compedium& c, const ::std::string& cmd, const ::std::string& a, bool& linechange, bool& inif, ::std::time_t& updated)
{   vstr_t args (split_quoted_by_space (a));
    if (! cmd.empty ())
    {   type_master < t_ssi > todo;
        todo.set_value (nits, v, cmd);
        if (todo.good ())
        if (! c.if_) switch (todo.get ())
        {   case ssi_else :     return else_command (nits, c, inif);
            case ssi_elif :     return elif_command (ln, nits, v, p, c, args, inif);
            case ssi_endif :    return endif_command (nits, c, inif);
            case ssi_if :       return if_command (ln, nits, v, p, c, args, inif);
            default : break; }
        else switch (todo.get ())
        {   case ssi_comment :  return ::std::string ();
            case ssi_config :   return config_command (ln, nits, v, c, args);
            case ssi_echo :     return echo_command (ln, nits, v, p, c, args, updated);
            case ssi_else :     return else_command (nits, c, inif);
            case ssi_elif :     return elif_command (ln, nits, v, p, c, args, inif);
            case ssi_endif :    return endif_command (nits, c, inif);
            case ssi_exec :     set_ssi_context (ln, nits, es_warning);
                                nits.pick (nit_no_exec, es_warning, ec_ssi, "apologies, but ", PROG, " cannot process <!--#EXEC-->");
                                return ::std::string ();
            case ssi_fsize :    return fsize_command (ln, nits, v, p, c, args);
            case ssi_flastmod : return flastmod_command (ln, nits, v, p, c, args);
            case ssi_include :  linechange = true; return include_command (ln, nits, v, p, c, args, updated);
            case ssi_if :       linechange = true; return if_command (ln, nits, v, p, c, args, inif);
            case ssi_printenv : linechange = true; return printenv_command (nits, c, args);
            case ssi_set :      return set_command (ln, nits, v, p, c, args); } }
    return ::std::string (); }

::std::string hereabouts (const ::std::string::const_iterator b, ::std::string::const_iterator e)
{   if (GSL_NARROW_CAST <::std::size_t> (e - b) > max_separation)
        return unify_whitespace (::std::string (b, b + max_separation - 1));
    return unify_whitespace (::std::string (b, e)); }

void test_for_oops (nitpick& nits, int line, ::std::string::const_iterator b, const ::std::string::const_iterator i, ::std::string::const_iterator e, bool& warned)
{   if (i >= e - 1) return;
    if (e - b <= 5) return;
    ::std::string msg;
    e_severity severity = es_error;
    switch (*i)
    {   case '<' :  if ((e - i <= 6) || (::std::string (i, i+5) != "<!--#")) return;
                    if (*(i-1) == '>') return;
                    msg = "one SSID element starts inside another";
                    break;
        case '-' :  if ((e - i <= 5) || (::std::string (i, i+3) != "-->")) return;
                    if (::std::iswspace (*(i-1))) return;
                    msg = "space missing before attempted end of SSI"; severity = es_warning;
                    break;
        default :   if (((*i >= 'A') && (*i <= 'Z')) || ((*i >= 'a') && (*i <= 'z')) || ((*i >= '0') && (*i <= '9')) || (*i == '=') || ::std::iswspace (*i)) return;
                    if ((*i < 32) && ::std::iscntrl (*i)) return; }
    if (msg.empty ())
    {   if (warned) return;
        msg = "is '";
        msg += *i;
        msg += "' intended here?";
        severity = es_comment;
        warned = true; }
    if (GSL_NARROW_CAST <::std::size_t> (i - b) > max_separation) b = i - max_separation;
    if (GSL_NARROW_CAST <::std::size_t> (e - i) > max_separation) e = i + max_separation;
    nits.set_context (line, unify_whitespace (::std::string (b, e)));
    nits.pick (nit_ssi_syntax, severity, ec_ssi, msg); }

::std::string parse_ssi (nitpick& nits, const html_version& v, page& p, ssi_compedium& c, const ::std::string& input, ::std::time_t& updated, bool shush)
{   VERIFY_NOT_NULL (p.get_directory (), __FILE__, __LINE__);
    if (! context.ssi ()) return input;
    typedef enum { es_dull, es_open, es_bang, es_om_1, es_om_2, es_note, es_ssi, es_args, es_cm_1, es_cm_2, es_space, es_am_1, es_am_2 } e_state;
    e_state status = es_dull;
    bool revised = false, linechange = false, inif = false, warned = false;
    ::std::string from (input), to, cmd;
    ::std::string::const_iterator start = from.cbegin (), var = from.cbegin (), args = from.cbegin (), b = from.cbegin (), e = from.cend ();
    int line = 1, nlc = 0;
    bool nr = true;
    c.if_ = true;
    for (::std::string::const_iterator i = b; i != e; ++i)
    {   switch (*i)
        {   case '\f' :
            case '\n' :
                if (++nlc < 3) to += *i;
                ++line; nr = true;
                continue;
            case '\v' :
                if (++nlc < 3) to += '\n';
                ++line; nr = true;
                continue;
            case '\r' :
                if (nr) to += *i;
                nr = false;
                continue;
            case '\t' :
                to += *i; nr = true;
                continue;
            default :
                nr = true; break; }
        if (! ::std::iswspace (*i) && ! ::std::iswcntrl (*i)) nlc = 0;
        switch (status)
        {   case es_dull :
                if (*i == '<') { status = es_open; start = i; }
                else if (c.if_) to += *i;
                break;
            case es_open :
                if (*i == '!') status = es_bang;
                else { if (c.if_) { to += "<"; to += *i; } status = es_dull; }
                break;
            case es_bang :
                if (*i == '-') status = es_om_1;
                else { if (c.if_) { to += "<!"; to += *i; } status = es_dull; }
                break;
            case es_om_1 :
                if (*i == '-') status = es_om_2;
                else { if (c.if_) { to += "<!-"; to += *i; } status = es_dull; }
                break;
            case es_om_2 :
                if (*i == '#') { status = es_ssi; var = i; }
                else status = es_note;
                break;
            case es_ssi :
                if (::std::iswcntrl (*i) || ::std::iswspace (*i))
                {   cmd = trim_the_lot_off (::std::string (var+1, i));
                    status = es_space;
                    args = i; }
                test_for_oops (nits, line, b, i, e, warned);
                break;
            case es_args :
                switch (*i)
                {   case ' ' :  status = es_space; break;
                    case '<' :
                    case '-' :
                    case '>' : test_for_oops (nits, line, b, i, e, warned); break;
                    default : break; }
                break;
            case es_space :
                if (*i == '-') status = es_am_1;
                else status = es_args;
                break;
            case es_am_1 :
                if (*i == '-') status = es_am_2;
                else status = es_args;
                break;
            case es_am_2 : if (*i == '>')
                {   ::std::string a (unify_whitespace (trim_the_lot_off (::std::string (args, i-3))));
                    ::std::string ln (::boost::lexical_cast < ::std::string > (line));
                    ln += ": <!--#";
                    ln += cmd + " " + a + " -->";
                    to += process_ssi (ln, nits, v, p, c, cmd, a, linechange, inif, updated);
                    revised = true; status = es_dull; }
                break;
            case es_note :
                if (*i == '-') status = es_cm_1;
                break;
            case es_cm_1 :
                if (*i == '-') status = es_cm_2;
                else status = es_note;
                break;
            case es_cm_2 :
                if (*i == '>')
                {   status = es_dull;
                    warned = false; }
                else status = es_note;
                break; } }
    switch (status)
    {   case es_ssi :
        case es_args :
        case es_space :
        case es_am_1 :
        case es_am_2 :
        {   nits.set_context (0, hereabouts (start, e));
            nits.pick (nit_ssi_syntax, es_error, ec_ssi, "end of file inside SSI element"); }
            break;
        case es_note :
        case es_cm_1 :
        case es_cm_2 :
        {   nits.set_context (0, hereabouts (start, e));
            nits.pick (nit_ssi_syntax, es_error, ec_ssi, "end of file inside comment"); }
            break;
        default : break; }
    if (linechange)
    {   nits.set_context (0, c.filename_);
        nits.pick (nit_linechange, es_comment, ec_ssi, "SSI substitution may have caused some line numbers to change"); }
    if (! shush && revised && context.tell (es_splurge))
    {   outstr.out ("\nSSI parsing changed content to:\n", to, "\n"); }
    return to; }
