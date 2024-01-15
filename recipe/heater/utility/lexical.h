/*
ssc (static site checker)
File Info
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
#include "main/include.h"

template < typename TYPE > struct lexical
{   static bool test (const ::std::string& s)
    {   if (s.empty ()) return true;
        try
        {   ::boost::lexical_cast < TYPE > (s); return true; }
        catch (...)
        {   return false; } }
    static TYPE cast (const ::std::string& s)
    {   try
        {   return ::boost::lexical_cast < TYPE > (s); }
        catch (...)
        {   return TYPE (); } }
    static TYPE cast (const ::std::string& s, const TYPE def)
    {   try
        {   return ::boost::lexical_cast < TYPE > (s); }
        catch (...)
        {   return def; } }
    static TYPE cast2 (const ::std::string& s, bool& b)
    try
    {   b = true;
        return ::boost::lexical_cast < TYPE > (s); }
    catch (...)
    {   b = false;
        return TYPE (); } };

template < typename T > struct en
{   static ::std::string str (const T t)
    {   return ::std::string (::boost::lexical_cast < ::std::string > (t)); } };

template < > struct en < ::std::string >
{   static ::std::string str (const ::std::string& t)
    {   return ::std::string (t); } };

template < > struct en < char >
{   static ::std::string str (const char ch)
    {   return ::std::string (1, ch); } };

template < > struct en < const char* >
{   static ::std::string str (const char* t)
    {   if (t == nullptr) return "(NULL)"; return ::std::string (t); } };

template < > struct en < bool >
{   static ::std::string str (const bool b)
    {   if (b) return "true"; return "false"; } };

template < typename T, typename... Ts > struct com
{   static ::std::string bine (T t, Ts... ts)
    {   return en < T > :: str (t) + com < Ts... > :: bine (ts...); } };

template < typename T > struct com < T >
{   static ::std::string bine (T t)
    {   return en < T > :: str (t); } };
