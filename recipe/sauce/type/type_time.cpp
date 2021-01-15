/*
ssc (static site checker)
Copyright (c) 2020,2021 Dylan Harris
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
#include "type/type_time.h"

bool grab_whitespace (const ::std::string::const_iterator e, ::std::string::const_iterator& i)
{   if ((i == e) || (! ::std::iswspace (*i))) return false;
    ++i; return true; }

bool grab_char (const ::std::string::const_iterator e, ::std::string::const_iterator& i, const char ch)
{   if ((i == e) || (*i != ch)) return false;
    ++i; return true; }

bool grab_char (const ::std::string::const_iterator e, ::std::string::const_iterator& i, const ::std::string& s)
{   if (i == e) return false;
    if (s.find_first_of (*i) == ::std::string::npos) return false;
    ++i; return true; }

template < typename INT > bool grab_digits (const ::std::string::const_iterator e, ::std::string::const_iterator& c, const INT len, const INT max, bool zero, INT& val)
{   if (c == e) return false;
    ::std::string::const_iterator i = c;
    INT v = 0, count = 0;
    while ((i != e) && (*i >= '0') && (*i <= '9') && (++count <= len))
    {   v *= 10; v += static_cast < INT > (*i) - '0'; ++i; }
    if (count == 0) return false;
    if ((max > 0) && (v > max)) return false;
    if (! zero && (v == 0)) return false;
    val = v; c = i; return true; }

bool grab_year (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& year)
{   return grab_digits < int > (e, i, 4, 0, true, year); }

bool grab_month (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& month)
{   return grab_digits < int > (e, i, 2, 12, false, month); }

bool grab_week (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int year, int& week)
{   if (! grab_digits < int > (e, i, 2, 53, false, week)) return false;
    if (week < 53) return true;
    const int y53 [] = {// https://en.wikipedia.org/wiki/Common_year_starting_on_Thursday,
                        // https://en.wikipedia.org/wiki/Leap_year_starting_on_Thursday,
                        // https://en.wikipedia.org/wiki/Leap_year_starting_on_Wednesday
                        // NOTE I suspect the 16th century is incomplete, and I'm dubious about the 18th at that
        1587, 1598,
        1604, 1609, 1615, 1626, 1620, 1632, 1637, 1643, 1648, 1654, 1660, 1665, 1671, 1676, 1682, 1688, 1693, 1699,
        1705, 1711, 1716, 1722, 1728, 1733, 1744, 1750, 1756, 1761, 1767, 1772, 1778, 1784, 1789, 1795,
        1801, 1807, 1812, 1818, 1824, 1829, 1835, 1840, 1846, 1852, 1857, 1863, 1868, 1874, 1880, 1885, 1891, 1896,
        1903, 1908, 1914, 1920, 1925, 1931, 1936, 1942, 1948, 1953, 1959, 1964, 1970, 1976, 1981, 1987, 1992, 1998,
        2004, 2009, 2015, 2020, 2026, 2032, 2037, 2043, 2048, 2054, 2060, 2065, 2071, 2076, 2082, 2088, 2093, 2099,
        0 };
    for (::std::size_t x = 0; y53 [x] != 0; ++x)
        if (year == y53 [x]) return true;
    return false; }

bool grab_day (const ::std::string::const_iterator e, ::std::string::const_iterator& c, const int year, const int month, int& day)
{   int d;
    ::std::string::const_iterator i = c;
    if (! grab_digits < int > (e, i, 2, 31, false, d)) return false;
    ::std::size_t count = 0;
    while ((i != e) && (*i >= '0') && (*i <= '9'))
    {   if (++count > 2) return false;
        d *= 10; d += (*i - '0'); ++i; }
    if ((d == 0) || (d > 31)) return false;
    switch (month)
    {   case 4 :
        case 6 :
        case 9 :
        case 11 :
            if (d > 30) return false; break;
        case 2 :
            if (d > 29) return false;
            if ((d == 29) && (year > 0))
            {   if (year % 4 != 0) return false;
                if ((year % 100 == 0) && (year % 400 != 0)) return false; }
            break;
        default :
            if (d > 31) return false; }
    day = d;
    c = i;
    return true; }

bool grab_hour (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& hour)
{   return grab_digits < int > (e, i, 2, 23, true, hour); }

bool grab_minute (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& minute)
{   return grab_digits < int > (e, i, 2, 59, true, minute); }

bool grab_second (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& second)
{   return grab_digits < int > (e, i, 2, 59, true, second); }

bool grab_leap_second (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& second)
{   return grab_digits < int > (e, i, 2, 60, true, second); }

bool grab_microsecond (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& ms)
{   return grab_digits < int > (e, i, 3, 0, true, ms); }

bool grab_chars (const ::std::string::const_iterator e, ::std::string::const_iterator& c, const ::std::string& what, const int max)
{   int count = 0;
    ::std::string::const_iterator i = c;
    while ((i != e) && (what.find (*i) != ::std::string::npos))
    {   if (++count > max) return false;
        ++i; }
    i = c; return true; }

bool verify_simply_year (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year)
{   ::std::string::const_iterator i = c;
    if (! grab_year (e, i, year)) return false;
    c = i; return true; }

bool verify_month (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month)
{   ::std::string::const_iterator i = c;
    if (! grab_year (e, i, year)) return false;
    if (! grab_char (e, i, '-')) return false;
    if (! grab_month (e, i, month)) return false;
    c = i; return true; }

bool verify_year (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month, int& day)
{   ::std::string::const_iterator i = c;
    if (! grab_year (e, i, year)) return false;
    if (! grab_char (e, i, '-')) return false;
    if (! grab_month (e, i, month)) return false;
    if (! grab_char (e, i, '-')) return false;
    if (! grab_day (e, i, year, month, day)) return false;
    c = i; return true; }

bool verify_yearless_date  (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& month, int& day)
{   ::std::string::const_iterator i = c;
    if (! grab_chars (e, i, "-", 2)) return false;
    if (! grab_month (e, i, month)) return false;
    if (! grab_char (e, i, '-')) return false;
    if (! grab_day (e, i, 0, month, day)) return false;
    c = i; return true; }

bool verify_week_year (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& week)
{   ::std::string::const_iterator i = c;
    if (! grab_year (e, i, year)) return false;
    if (! grab_char (e, i, '-')) return false;
    if (! grab_char (e, i, 'W')) return false;
    if (! grab_week (e, i, year, week)) return false;
    c = i; return true; }

bool verify_coarse_time (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& hour, int& minute, int& second)
{   ::std::string::const_iterator i = c;
    int h = 0, m = 0, s = 0;
    if (! grab_hour (e, i, h)) return false;
    if (! grab_char (e, i, ':')) return false;
    if (! grab_minute (e, i, m)) return false;
    second = s;
    hour = h;
    minute = m;
    c = i;
    return true; }

bool verify_time (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& hour, int& minute, int& second, int& micro)
{   ::std::string::const_iterator i = c;
    int h = 0, m = 0, s = 0, ms = 0;
    if (! verify_coarse_time (e, i, h, m, s)) return false;
    if (i != e)
    {   if (! grab_char (e, i, ':')) return false;
        if (! grab_second (e, i, s)) return false;
        if (i == e) return true;
        if (! grab_char (e, i, '.')) return false;
        if (! grab_microsecond (e, i, ms)) return false; }
    micro = ms;
    second = s;
    hour = h;
    minute = m;
    c = i;
    return true; }

bool verify_floating_datetime (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month, int& day, int& hour, int& minute, int& second, int& micro)
{   ::std::string::const_iterator i = c;
    if (! verify_year (e, i, year, month, day)) return false;
    if (! grab_char (e, i, "T ")) return false;
    if (! verify_time (e, i, hour, minute, second, micro)) return false;
    c = i; return true; }

bool verify_timezone (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& hour_offset, int& minute_offset)
{   if (c == e) return false;
    ::std::string::const_iterator i = c;
    if (grab_char (e, i, 'Z'))
    {   hour_offset = minute_offset = 0;
        c = i;
        return true; }
    bool negative = false;
    if (*i == '-') negative = true;
    else if (*i != '+') return false;
    ++i;
    int h = 0, m = 0;
    if (! grab_hour (e, i, h)) return false;
    if (i == e) return false;
    if (*i == ':') ++i;
    if (! grab_minute (e, i, m)) return false;
    hour_offset = negative ? (-1 * h) : h;
    minute_offset = m;
    c = i;
    return true; }

bool verify_coarse_time_tz (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& hour, int& minute, int& second, int& hour_offset, int& minute_offset)
{   ::std::string::const_iterator i = c;
    if (! verify_coarse_time (e, i, hour, minute, second)) return false;
    if (! verify_timezone (e, i, hour_offset, minute_offset)) hour_offset = minute_offset = 0;
    c = i; return true; }

bool verify_global_datetime (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month, int& day, int& hour, int& minute, int& second, int& micro, int& hour_offset, int& minute_offset)
{   ::std::string::const_iterator i = c;
    if (! verify_year (e, i, year, month, day)) return false;
    if (! grab_char (e, i, "T ")) return false;
    if (! verify_time (e, i, hour, minute, second, micro)) return false;
    if (! verify_timezone (e, i, hour_offset, minute_offset)) return false;
    c = i; return true; }

bool verify_duration (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& day, int& hour, int& minute, int& second, int& micro)
{   if (c == e) return false;
    ::std::string::const_iterator i = c;
    if (! grab_char (e, i, 'P')) return false;
    int d = 0, h = 0, m = 0, s = 0, ms = 0;
    if (! grab_digits (e, i, 4, 0, true, d)) return false;
    if (! grab_char (e, i, 'T')) return false;
    if (! grab_digits (e, i, 4, 0, true, h)) return false;
    if (! grab_char (e, i, 'H')) return false;
    if (! grab_digits (e, i, 4, 0, true, m)) return false;
    if (! grab_char (e, i, 'M')) return false;
    if (! grab_digits (e, i, 4, 0, true, s)) return false;
    if (grab_char (e, i, '.'))
        if (! grab_digits (e, i, 4, 0, true, ms)) return false;
    if (! grab_char (e, i, 'S')) return false;
    day = d;
    hour = h;
    minute = m;
    second = s;
    micro = ms;
    c = i;
    return true; }

bool verify_duration (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int64_t& second, int& micro)
{   if (c == e) return false;
    ::std::string::const_iterator i = c;
    if (! grab_char (e, i, 'P')) return false;
    int64_t x = 0, s = 0;
    int ms = 0;
    bool got = false;
    bool time = grab_char (e, i, 'T') || grab_char (e, i, 't');
    bool week = false;
    bool year = false;
    while (grab_digits < int64_t > (e, i, 12, 0, true, x) && (i < e))
    {   while (grab_whitespace (e, i)); // yup, no loop content
        if (i == e) break;
        if (grab_char (e, i, '.'))
        {   if (week) return false;
            if (! grab_digits < int > (e, i, 3, 0, true, ms)) return false;
            while (grab_whitespace (e, i)); // similarly
            if (i == e) return false;
            if (! grab_char (e, i, "Ss")) return false;
            s += x; }
        else switch (*i)
        {   case 'Y' :
            case 'y' :  if (time) return false;
                        year = true;
                        if (INT64_MAX - (x * 86400 * 365) < s) return false;
                        s += x * 86400 * 365; break;
            case 'W' :
            case 'w' :  if (time) return false;
                        week = true; year = false;
                        if (INT64_MAX - (x * 604800) < s) return false;
                        s += x * 604800; break;
            case 'D' :
            case 'd' :  if (time) return false;
                        year = false;
                        if (INT64_MAX - (x * 86400) < s) return false;
                        s += x * 86400; break;
            case 'H' :
            case 'h' :  if (INT64_MAX - (x * 3600) < s) return false;
                        year = false;
                        s += x * 3600; break;
            case 'M' :
            case 'm' :  if (year)
                        {   if (INT64_MAX - (x * 86400 * 30) < s) return false;
                            s += x * 86400 * 30; }
                        else
                        {   if (INT64_MAX - (x * 60) < s) return false;
                            s += x * 60; }
                        break;
            case 'S' :
            case 's' :  if (INT64_MAX - x < s) return false;
                        year = false;
                        s += x; break;
            case 'T' :
            case 't' :  if (week) return false;
                        year = false;
                        time = true; break;
            default :   return false; }
        got = true; ++i; }
    if (! got) return false;
    while (grab_whitespace (e, i)); // as above
    second = s;
    micro = ms;
    c = i;
    return true; }

bool verify_svg_duration (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& hour, int& minute, int& second, int& micro)
{   if (c == e) return false;
    ::std::string::const_iterator i = c;
    int h = 0, m = 0, s = 0, ms = 0;
    if (! grab_digits (e, i, 4, 0, true, h)) return false;
    if (! grab_char (e, i, ':')) return false;
    if (! grab_digits (e, i, 4, 0, true, m)) return false;
    if (! grab_char (e, i, ':')) return false;
    if (! grab_digits (e, i, 4, 0, true, s)) return false;
    if (grab_char (e, i, '.'))
        if (! grab_digits (e, i, 4, 0, true, ms)) return false;
    hour = h;
    minute = m;
    second = s;
    micro = ms;
    c = i;
    return true; }

bool verify_svg_duration (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& minute, int& second, int& micro)
{   if (c == e) return false;
    ::std::string::const_iterator i = c;
    int m = 0, s = 0, ms = 0;
    if (! grab_digits (e, i, 4, 0, true, m)) return false;
    if (! grab_char (e, i, ':')) return false;
    if (! grab_digits (e, i, 4, 0, true, s)) return false;
    if (grab_char (e, i, '.'))
        if (! grab_digits (e, i, 4, 0, true, ms)) return false;
    minute = m;
    second = s;
    micro = ms;
    c = i;
    return true; }

bool verify_svg_duration (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int64_t& second, int& micro)
{   if (c == e) return false;
    ::std::string::const_iterator i = c;
    int ms = 0;
    int64_t s = 0;
    if (! grab_digits < int64_t > (e, i, 4, 0, true, s)) return false;
    if (grab_char (e, i, '.'))
        if (! grab_digits (e, i, 4, 0, true, ms)) return false;
    if (grab_char (e, i, 'h')) { micro = 0; second = s * 3600; }
    else if (grab_char (e, i, 's')) { micro = 0; second = s; }
    else if (grab_char (e, i, 'm'))
        if (grab_char (e, i, 'i'))
            if (grab_char (e, i, 'n')) { micro = 0; second = s * 60; } else return false;
        else if (grab_char (e, i, 's')) { micro = ms; second = 0; } else return false;
    c = i;
    return true; }

bool verify_vague (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month, int& week, int& day, int& hour, int& minute, int& second, int& micro, int& hour_offset, int& minute_offset, int64_t& duration)
{   ::std::string::const_iterator i = c;
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, ms = 0, ho = 0, mo = 0, w = 0;
    int64_t s64 = 0;
    if (! verify_global_datetime (e, i, y, m, d, h, mn, s, ms, ho, mo))
        if (! verify_floating_datetime (e, i, y, m, d, h, mn, s, ms))
            if (! verify_time (e, i, h, mn, s, ms))
                if (! verify_year (e, i, y, m, d))
                    if (! verify_week_year (e, i, y, w))
                        if (! verify_yearless_date (e, i, m, d))
                            if (! verify_month (e, i, y, m))
                                if (! verify_timezone (e, i, ho, mo))
                                    if (! verify_duration (e, i, d, h, mn, s, ms))
                                        if (! verify_duration (e, i, s64, ms))
                                            if (! verify_simply_year (e, i, y))
                                                return false;
    c = i;
    year = y;
    month = m;
    week = w;
    day = d;
    hour = h;
    minute = mn;
    second = s;
    micro = ms;
    hour_offset = ho;
    minute_offset = mo;
    duration = s64;
    return true; }

bool verify_vague (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, ms = 0, ho = 0, mo = 0, w = 0;
    int64_t s64 = 0;
    return verify_vague (e, i, y, m, w, d, h, mn, s, ms, ho, mo, s64); }

bool verify_local_datetime (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, ms = 0, ho = 0, mo = 0, w = 0;
    int64_t s64 = 0;
    if (! verify_vague (e, i, y, m, w, d, h, mn, s, ms, ho, mo, s64)) return false;
    return ((ho == 0) && (mo == 0)); }

bool verify_absolute (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, ms = 0, ho = 0, mo = 0, w = 0;
    if (! verify_global_datetime (e, i, y, m, d, h, mn, s, ms, ho, mo))
        if (! verify_year (e, i, y, m, d))
            if (! verify_week_year (e, i, y, w))
                return false;
    return true; }

bool verify_duration (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int d = 0, h = 0, mn = 0, s = 0, ms = 0;
    int64_t i64 = 0;
    if (! verify_duration (e, i, d, h, mn, s, ms))
        if (! verify_duration (e, i, i64, ms))
            return false;
    return true; }

bool verify_svg_duration (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int  h = 0, mn = 0, s = 0, ms = 0;
    int64_t i64 = 0;
    if (! verify_svg_duration (e, i, h, mn, s, ms))
        if (! verify_svg_duration (e, i, mn, s, ms))
            if (! verify_svg_duration (e, i, i64, ms))
            return false;
    return true; }

bool verify_coarse_time_tz (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int h = 0, m = 0, s = 0, ho = 0, mo = 0;
    return verify_coarse_time_tz (e, i, h, m, s, ho, mo); }

bool verify_month (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0;
    return verify_month (e, i, y, m); }

bool verify_timezone (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int ho = 0, mo = 0;
    return verify_timezone (e, i, ho, mo); }

bool verify_week (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0;
    return verify_week_year (e, i, y, m); }

bool verify_year (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0, d = 0;
    return verify_year (e, i, y, m, d); }

bool verify_time_4 (nitpick& nits, const html_version& v, const ::std::string& s)
{   if (verify_absolute (s)) return true;
    if (v.mjr () < 4)
        nits.pick (nit_bad_datetime, es_warning, ec_type, quote (s), " is dubious: ISO-8601 datetime format is 'yyyy-mm-ddThh:mm:ssTZD', where TZD is 'Z' or 'Shh:mm', and S is '+' or '-'");
    else nits.pick (nit_bad_datetime, ed_4, "6.11 Dates and times", es_error, ec_type, quote (s), " is not in ISO-8601 datetime format: 'yyyy-mm-ddThh:mm:ssTZD', where TZD is 'Z' or 'Shh:mm', and S is '+' or '-'");
    return false; }

bool verify_time_5 (nitpick& nits, const html_version& , const ::std::string& s)
{   if (verify_vague (s)) return true;
    nits.pick (nit_bad_datetime, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid datetime");
    return false; }

bool verify_absolute (nitpick& nits, const html_version& , const ::std::string& s)
{   if (verify_absolute (s)) return true;
    nits.pick (nit_bad_datetime, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " must be an absolute datetime");
    return false; }

bool verify_duration (nitpick& nits, const html_version& , const ::std::string& s)
{   if (verify_duration (s)) return true;
    nits.pick (nit_bad_datetime, ed_50, "2.4.5.9 Durations", es_error, ec_type, quote (s), " is an invalid duration");
    return false; }

bool verify_month (nitpick& nits, const html_version& , const ::std::string& s)
{   if (verify_month (s)) return true;
    nits.pick (nit_bad_datetime, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid month");
    return false; }

bool verify_local_datetime (nitpick& nits, const html_version& , const ::std::string& s)
{   if (s.find_first_of ("Zz") == ::std::string::npos) if (verify_local_datetime (s)) return true;
    nits.pick (nit_bad_datetime, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid local date (no timezones)");
    return false; }

bool verify_week (nitpick& nits, const html_version& , const ::std::string& s)
{   if (verify_week (s)) return true;
    nits.pick (nit_bad_datetime, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid week");
    return false; }

bool verify_timezone (nitpick& nits, const html_version& , const ::std::string& s)
{   if (verify_timezone (s)) return true;
    nits.pick (nit_timezone, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid timezone");
    return false; }

bool verify_plain_date (nitpick& nits, const html_version& , const ::std::string& s)
{   if (verify_year (s)) return true;
    nits.pick (nit_bad_datetime, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is not a plain and simple date");
    return false; }

bool verify_coarse_time (nitpick& nits, const html_version& , const ::std::string& s)
{   if (verify_coarse_time_tz (s)) return true;
    nits.pick (nit_bad_datetime, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid time (hh:mm:ss[Z|(+|-)hh:mm])");
    return false; }

bool verify_svg_duration (nitpick& nits, const html_version& , const ::std::string& s)
{   if (verify_svg_duration (s)) return true;
    nits.pick (nit_bad_datetime, ed_svg_1_1, "19.2.8.1 Clock values", es_error, ec_type, quote (s), " is an invalid duration");
    return false; }

bool test_animation_timing (nitpick& , const html_version& , const ::std::string& , const bool )
{   // 19.2.8 Attributes to control the timing of the animation
    return true; }
