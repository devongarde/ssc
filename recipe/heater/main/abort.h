/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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

[[noreturn]] void throw_bad_dereference (const char* const var, const char* const fn, const ::std::size_t line);
[[noreturn]] void throw_bad_presumption (const char* const var, const char* const fn, const ::std::size_t line);
[[noreturn]] void graceful_crash (const char* const fn, const ::std::size_t line);

#define VERIFY_NOT_NULL(PTR,FILE,LINE) { if (nullptr == PTR) throw_bad_dereference (#PTR, FILE, LINE); }
#define PRESUME(WOT,FILE,LINE) { if (! (WOT)) throw_bad_presumption (#WOT, FILE, LINE); }
#define GRACEFUL_CRASH(FILE,LINE) { graceful_crash (FILE, LINE); }

#ifdef _MSC_VER
#define UNREACHABLE(x)
#define UNBREAKABLE
#else
#define UNREACHABLE(x) x
#define UNBREAKABLE break
#endif

#ifdef _DEBUG
#define DEBUGONLY(x) x
#else
#define DEBUGONLY(x)
#endif
