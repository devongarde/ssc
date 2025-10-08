/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "type/type.h"

e_nit grab_whitespace (const ::std::string::const_iterator e, ::std::string::const_iterator& i) noexcept
{   if ((i == e) || (! ::std::iswspace (*i))) return nit_time_space;
    ++i; return nit_free; }

e_nit grab_char (const ::std::string::const_iterator e, ::std::string::const_iterator& i, const char ch) noexcept
{   if ((i == e) || (*i != ch)) return nit_time_char;
    ++i; return nit_free; }

e_nit grab_char (const ::std::string::const_iterator e, ::std::string::const_iterator& i, const ::std::string& s) noexcept
{   if (i == e) return nit_time_char;
    if (s.find_first_of (*i) == ::std::string::npos) return nit_time_char;
    ++i; return nit_free; }

template < typename INT > e_nit grab_digits (const ::std::string::const_iterator e, ::std::string::const_iterator& c, const INT len, const INT max, bool zero, INT& val) noexcept
{   if (c == e) return nit_time_digit;
    ::std::string::const_iterator i = c;
    INT v = 0, count = 0;
    while ((i != e) && (*i >= '0') && (*i <= '9') && (++count <= len))
    {   v *= 10; v += static_cast < INT > (*i) - '0'; ++i; }
    if (count == 0) return nit_time_digit;
    if ((max > 0) && (v > max)) return nit_time_digit;
    if (! zero && (v == 0)) return nit_time_digit;
    val = v; c = i; return nit_free; }

e_nit grab_short_year (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& year) noexcept
{   if (grab_digits < int > (e, i, 2, 0, true, year) != nit_free) return nit_bad_year;
    return nit_free; }

e_nit grab_year (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& year) noexcept
{   if (grab_digits < int > (e, i, 4, 0, true, year) != nit_free) return nit_bad_year;
    return nit_free; }

e_nit grab_month (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& month) noexcept
{   if (grab_digits < int > (e, i, 2, 12, false, month) != nit_free) return nit_bad_month;
    return nit_free; }

e_nit grab_week (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int year, int& week) noexcept
{   if (grab_digits < int > (e, i, 2, 53, false, week) != nit_free) return nit_bad_week;
    if (week < 53) return nit_free;
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
#ifdef _MSC_VER
#pragma warning (push, 3)
#pragma warning (disable : 26446 26482) // Suggested solution breaks the compilation, plus ::std::array can't be length initialised by the initiliser
#endif // _MSC_VER
    for (::std::size_t x = 0; y53 [x] != 0; ++x)
        if (year == y53 [x]) return nit_free;
    return nit_bad_week; }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER

e_nit check_date (const int year, const int month, const int day)
{   if ((day < 1) || (day > 31)) return nit_bad_date;
    switch (month)
    {   case 4 :
        case 6 :
        case 9 :
        case 11 :
            if (day > 30) return nit_bad_date;
            break;
        case 2 :
            if (day > 29) return nit_bad_date;
            if ((day == 29) && (year > 0))
            {   if (year % 4 != 0) return nit_bad_date;
                if ((year % 100 == 0) && (year % 400 != 0)) return nit_bad_date; }
            break;
        default :
            if ((month < 1) || (month > 12)) return nit_bad_date;
            break; }
    return nit_free; }

e_nit grab_day (const ::std::string::const_iterator e, ::std::string::const_iterator& c, const int year, const int month, int& day) noexcept
{   int d;
    ::std::string::const_iterator i = c;
    const e_nit n = grab_digits < int > (e, i, 2, 31, false, d);
    if (n != nit_free) return n;
    ::std::size_t count = 0;
    while ((i != e) && (*i >= '0') && (*i <= '9'))
    {   if (++count > 2) return nit_bad_day;
        d *= 10; d += (*i - '0'); ++i; }
    if ((d == 0) || (d > 31)) return nit_bad_day;
    switch (month)
    {   case 4 :
        case 6 :
        case 9 :
        case 11 :
            if (d > 30) return nit_bad_day; break;
        case 2 :
            if (d > 29) return nit_bad_day;
            if ((d == 29) && (year > 0))
            {   if (year % 4 != 0) return nit_bad_day;
                if ((year % 100 == 0) && (year % 400 != 0)) return nit_bad_day; }
            break;
        default :
            if (d > 31) return nit_bad_day; }
    day = d;
    c = i;
    return nit_free; }

e_nit grab_hour (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& hour) noexcept
{   if (grab_digits < int > (e, i, 2, 23, true, hour) == nit_free) return nit_free;
    return nit_bad_hour; }

e_nit grab_minute (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& minute) noexcept
{   if (grab_digits < int > (e, i, 2, 59, true, minute) == nit_free) return nit_free;
    return nit_bad_minute; }

e_nit grab_second (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& second) noexcept
{   if (grab_digits < int > (e, i, 2, 59, true, second) == nit_free) return nit_free;
    return nit_bad_second; }

e_nit grab_leap_second (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& second) noexcept
{   if (grab_digits < int > (e, i, 2, 60, true, second) == nit_free) return nit_free;
    return nit_bad_kangeroo; }

e_nit grab_microsecond (const ::std::string::const_iterator e, ::std::string::const_iterator& i, int& ms) noexcept
{   if (grab_digits < int > (e, i, 3, 0, true, ms) == nit_free) return nit_free;
    return nit_bad_microsecond; }

e_nit grab_chars (const ::std::string::const_iterator e, ::std::string::const_iterator& c, const ::std::string& what, const int max) noexcept
{   int count = 0;
    ::std::string::const_iterator i = c;
    while ((i != e) && (what.find (*i) != ::std::string::npos))
    {   if (++count > max) return nit_time_char;
        ++i; }
    c = i; return nit_free; }

e_nit verify_simply_year (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year) noexcept
{   ::std::string::const_iterator i = c;
    const e_nit n = grab_year (e, i, year);
    if (n == nit_free) c = i;
    return n; }

e_nit verify_month (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month) noexcept
{   ::std::string::const_iterator i = c;
    e_nit n = grab_year (e, i, year);
    if (n == nit_free) n = grab_char (e, i, '-');
    if (n == nit_free) n = grab_month (e, i, month);
    if (n == nit_free) c = i;
    return n; }

e_nit verify_monthday (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& month, int& day) noexcept
{   ::std::string::const_iterator i = c;
    e_nit n = grab_month (e, i, month);
    if (n == nit_free) n = grab_char (e, i, '-');
    if (n == nit_free) n = grab_day (e, i, 0, month, day);
    if (n == nit_free) c = i;
    return n; }

e_nit verify_day (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& day) noexcept
{   ::std::string::const_iterator i = c;
    const e_nit n = grab_day (e, i, 0, 0, day);
    if (n == nit_free) c = i;
    return n; }

template < e_type E > e_nit verify_enum (const ::std::string::const_iterator e, ::std::string::const_iterator& c, const int mx, int& v) noexcept
{   ::std::string::const_iterator i = c;
    try
    {   const e_nit n = grab_chars (e, i, ALPHABET, mx);
        if (n != nit_free) return n;
        nitpick nits;
        if (! test_value < E > (nits, html_default, ::std::string (c, i)))
        {   return nit_bad_value; }
        v = static_cast < int > (examine_value < E > (nits, html_default, ::std::string (c, i))); }
    catch (...)
    {   return nit_bad_value; }
    c = i; return nit_free; }

e_nit verify_english_weekday_short (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& day) noexcept
{   if (verify_enum < t_weekday_english_short > (e, c, 3, day) == nit_free) return nit_free;
    return nit_bad_weekday; }

e_nit verify_english_weekday_long (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& day) noexcept
{   if (verify_enum < t_weekday_english_long > (e, c, 9, day) == nit_free) return nit_free;
    return nit_bad_weekday; }

e_nit verify_english_month_short (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& month) noexcept
{   if (verify_enum < t_month_english_short > (e, c, 3, month) != nit_free) return nit_bad_monthname;
    month += 1;
    return nit_free; }

e_nit verify_english_month_long (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& month) noexcept
{   if (verify_enum < t_month_english_long > (e, c, 9, month) != nit_free) return nit_bad_monthname;
    month += 1;
    return nit_free; }

e_nit verify_rfc822_zone (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& z)
{   if (verify_enum < t_rfc822_zone > (e, c, 9, z) == nit_free) return nit_free;
    return nit_bad_zone; }

e_nit verify_year (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month, int& day) noexcept
{   ::std::string::const_iterator i = c;
    e_nit n = grab_year (e, i, year);
    if (n == nit_free) n = grab_char (e, i, '-');
    if (n == nit_free) n = grab_month (e, i, month);
    if (n == nit_free) n = grab_char (e, i, '-');
    if (n == nit_free) n = grab_day (e, i, year, month, day);
    if (n == nit_free) c = i;
    return n; }

e_nit verify_yearmonth (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month) noexcept
{   ::std::string::const_iterator i = c;
    e_nit n = grab_year (e, i, year);
    if (n == nit_free) n = grab_char (e, i, '-');
    if (n == nit_free) n = grab_month (e, i, month);
    if (n == nit_free) c = i;
    return n; }

e_nit verify_year (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year) noexcept
{   ::std::string::const_iterator i = c;
    const e_nit n = grab_year (e, i, year);
    if (n == nit_free) c = i;
    return n; }

e_nit verify_yearless_date  (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& month, int& day)
{   ::std::string::const_iterator i = c;
    e_nit n = grab_chars (e, i, "-", 2);
    if (n == nit_free) n = grab_month (e, i, month);
    if (n == nit_free) n = grab_char (e, i, '-');
    if (n == nit_free) n = grab_day (e, i, 0, month, day);
    if (n == nit_free) c = i;
    return n; }

e_nit verify_week_year (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& week) noexcept
{   ::std::string::const_iterator i = c;
    e_nit n = grab_year (e, i, year);
    if (n == nit_free) n = grab_char (e, i, '-');
    if (n == nit_free) n = grab_char (e, i, 'W');
    if (n == nit_free) n = grab_week (e, i, year, week);
    if (n == nit_free) c = i;
    return n; }

e_nit verify_coarse_time (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& hour, int& minute, int& second) noexcept
{   ::std::string::const_iterator i = c;
    int h = 0, m = 0, s = 0;
    e_nit n =  grab_hour (e, i, h);
    if (n == nit_free) n = grab_char (e, i, ':');
    if (n == nit_free) n = grab_minute (e, i, m);
    if (n == nit_free)
    {   second = s;
        hour = h;
        minute = m;
        c = i; }
    return n; }

e_nit verify_hms (const ::std::string::const_iterator e, ::std::string::const_iterator& c, bool man_sec, int& hour, int& minute, int& second) noexcept
{   ::std::string::const_iterator i = c;
    int h = 0, m = 0, s = 0;
    e_nit n = grab_hour (e, i, h);
    if (n == nit_free) n = grab_char (e, i, ':');
    if (n == nit_free) n = grab_minute (e, i, m);
    if (n == nit_free)
    {   n = grab_char (e, i, ':');
        if (n != nit_free)
            if (man_sec) n = nit_bad_second;
            else n = nit_free;
        else n = grab_second (e, i, s); }
    if (n == nit_free)
    {   second = s;
        hour = h;
        minute = m;
        c = i; }
    return n; }

e_nit verify_time (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& hour, int& minute, int& second, int& micro) noexcept
{   ::std::string::const_iterator i = c;
    int h = 0, m = 0, s = 0, ms = 0;
    e_nit n = verify_coarse_time (e, i, h, m, s);
    if (n != nit_free) return n;
    if (i != e)
    {   n = grab_char (e, i, ':');
        if (n == nit_free) n = grab_second (e, i, s);
        if (n != nit_free) return n;
        if (i == e) return n;
        n = grab_char (e, i, '.');
        if (n == nit_free) n = grab_microsecond (e, i, ms); }
    if (n == nit_free)
    {   micro = ms;
        second = s;
        hour = h;
        minute = m;
        c = i; }
    return n; }

e_nit verify_floating_datetime (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month, int& day, int& hour, int& minute, int& second, int& micro)
{   ::std::string::const_iterator i = c;
    e_nit n = verify_year (e, i, year, month, day);
    if (n == nit_free) n = grab_char (e, i, "T ");
    if (n == nit_free) n = verify_time (e, i, hour, minute, second, micro);
    if (n == nit_free) c = i;
    return n; }

e_nit verify_timezone (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& hour_offset, int& minute_offset) noexcept
{   if (c == e) return nit_bad_zone;
    ::std::string::const_iterator i = c;
    if (grab_char (e, i, 'Z') == nit_free)
    {   hour_offset = minute_offset = 0;
        c = i;
        return nit_free; }
    bool negative = false;
    if (*i == '-') negative = true;
    else if (*i != '+') return nit_bad_zone;
    if (++i == e) return nit_bad_zone;
    int h = 0, m = 0;
    e_nit n = grab_hour (e, i, h);
    if (n != nit_free) return n;
    if (i == e) return nit_bad_zone;
    if (*i == ':') ++i;
    n = grab_minute (e, i, m);
    if (n != nit_free) return n;
    hour_offset = negative ? (-1 * h) : h;
    minute_offset = m;
    c = i;
    return n; }

e_nit verify_coarse_time_tz (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& hour, int& minute, int& second, int& hour_offset, int& minute_offset) noexcept
{   ::std::string::const_iterator i = c;
    const e_nit n = verify_coarse_time (e, i, hour, minute, second);
    if (n == nit_free)
    {   if (verify_timezone (e, i, hour_offset, minute_offset) != nit_free) hour_offset = minute_offset = 0;
        c = i; }
    return n; }

e_nit verify_global_datetime (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month, int& day, int& hour, int& minute, int& second, int& micro, int& hour_offset, int& minute_offset)
{   ::std::string::const_iterator i = c;
    e_nit n = verify_year (e, i, year, month, day);
    if (n == nit_free) n = grab_char (e, i, "T ");
    if (n == nit_free) n = verify_time (e, i, hour, minute, second, micro);
    if (n == nit_free) n = verify_timezone (e, i, hour_offset, minute_offset);
    if (n == nit_free) c = i;
    return n; }

e_nit acquire_global_datetime (const ::std::string& s, int& year, int& month, int& day, int& hour, int& minute, int& second)
{   ::std::string::const_iterator i = s.cbegin ();
    const ::std::string::const_iterator e = s.cend ();
    e_nit n = verify_year (e, i, year, month, day);
    if (e == i) return n;
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free) n = verify_hms (e, i, true, hour, minute, second);
    return n; }

e_nit verify_duration (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month, int& week, int& day, int& hour, int& minute, int& second, int& micro) noexcept
{   if (c == e) return nit_duration;
    ::std::string::const_iterator i = c;
    e_nit n = grab_char (e, i, 'P');
    if (n != nit_free) return n;
    int y = 0, mo = 0, w = 0, d = 0, h = 0, m = 0, s = 0, ms = 0, x = 0, nx = 0;
    bool dotty = false, tea = false;
    if (grab_char (e, i, 'T') == nit_free) { tea = true; nx = 5; }
    while (i < e)
    {   if (dotty) return nit_duration;
        n = grab_digits (e, i, 4, 0, true, x);
        if (n != nit_free) break;
        e_nit nk = grab_char (e, i, '.');
        if (nk != nit_free)
        {   nk = grab_char (e, i, ',');
            if (nk == nit_free)
            {   n = grab_digits (e, i, 4, 0, true, ms);
                if (n != nit_free) break;
                dotty = true; } }
        if (nx == 0)
            if (grab_char (e, i, 'Y') == nit_free)
            { y = x; nx = 1; continue; }
        if (nx < 2)
            if (grab_char (e, i, 'M') == nit_free)
            { mo = x; nx = 2; continue; }
        if (nx < 3)
            if (grab_char (e, i, 'W') == nit_free)
            { w = x; nx = 3; continue; }
        if (nx < 4)
            if (grab_char (e, i, 'D') == nit_free)
            { d = x; nx = 4; continue; }
        if (nx < 5)
            if (grab_char (e, i, 'T') == nit_free)
            {   nx = 5;
                if (tea) return nit_duration;
                else tea = true; }
        if (nx < 6)
            if (grab_char (e, i, 'H') == nit_free)
            { h = x; nx = 6; continue; }
        if (nx < 7)
            if (grab_char (e, i, 'M') == nit_free)
            { m = x; nx = 7; continue; }
        if (nx < 8)
            if (grab_char (e, i, 'S') == nit_free)
            { s = x; nx = 8; break; }
        return nit_duration; }
    if (nx == 0) return nit_duration;
    if (n == nit_free)
    {   year = y;
        month = mo;
        week = w;
        day = d;
        hour = h;
        minute = m;
        second = s;
        micro = ms;
        c = i; }
    return n; }

e_nit verify_duration (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int64_t& second, int& micro)
{   if (c == e) return nit_duration;
    ::std::string::const_iterator i = c;
    e_nit n = grab_char (e, i, 'P');
    if (n != nit_free) return n;
    int64_t x = 0, s = 0;
    int ms = 0;
    bool got = false;
    bool time = grab_char (e, i, 'T') || grab_char (e, i, 't');
    bool week = false;
    bool year = false;
    while (i < e)
    {   const e_nit nx = grab_digits < int64_t > (e, i, 12, 0, true, x);
        if (nx != nit_free) break;
        if (i == e) break;
        while (grab_whitespace (e, i) == nit_free); // yup, no loop content
        if (i == e) break;
        if (grab_char (e, i, '.') == nit_free)
        {   if (week) return nit_duration;
            n =  grab_digits < int > (e, i, 3, 0, true, ms);
            if (n != nit_free) return n;
            while (grab_whitespace (e, i) == nit_free); // similarly
            if (i == e) return nit_duration;
            n = grab_char (e, i, "Ss");
            if (n != nit_free) return n;
            s += x; }
        else switch (*i)
        {   case 'Y' :
            case 'y' :  if (time) return nit_duration;
                        year = true;
                        if (INT64_MAX - (x * 86400 * 365) < s) return nit_bad_year;
                        s += x * 86400 * 365; break;
            case 'W' :
            case 'w' :  if (time) return nit_duration;
                        week = true; year = false;
                        if (INT64_MAX - (x * 604800) < s) return nit_bad_week;
                        s += x * 604800; break;
            case 'D' :
            case 'd' :  if (time) return nit_duration;
                        year = false;
                        if (INT64_MAX - (x * 86400) < s) return nit_bad_day;
                        s += x * 86400; break;
            case 'H' :
            case 'h' :  if (INT64_MAX - (x * 3600) < s) return nit_bad_hour;
                        year = false;
                        s += x * 3600; break;
            case 'M' :
            case 'm' :  if (year)
                        {   if (INT64_MAX - (x * 86400 * 30) < s) return nit_bad_minute;
                            s += x * 86400 * 30; }
                        else
                        {   if (INT64_MAX - (x * 60) < s) return nit_bad_minute;
                            s += x * 60; }
                        break;
            case 'S' :
            case 's' :  if (INT64_MAX - x < s) return nit_bad_second;
                        year = false;
                        s += x; break;
            case 'T' :
            case 't' :  if (week) return nit_duration;
                        year = false;
                        time = true; break;
            default :   return nit_duration; }
        got = true; ++i; }
    if (! got) return nit_duration;
    while (grab_whitespace (e, i) == nit_free); // as above
    if (n == nit_free)
    {   second = s;
        micro = ms;
        c = i; }
    return n; }

e_nit verify_svg_duration (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& hour, int& minute, int& second, int& micro) noexcept
{   if (c == e) return nit_svg_duration;
    ::std::string::const_iterator i = c;
    int h = 0, m = 0, s = 0, ms = 0;
    e_nit n = grab_digits (e, i, 4, 0, true, h);
    if (n == nit_free) n = grab_char (e, i, ':');
    if (n == nit_free) n = grab_digits (e, i, 4, 0, true, m);
    if (n == nit_free) n = grab_char (e, i, ':');
    if (n == nit_free) n = grab_digits (e, i, 4, 0, true, s);
    if (n == nit_free)
        if (grab_char (e, i, '.') == nit_free)
            n = grab_digits (e, i, 4, 0, true, ms);
    if (n == nit_free)
    {   hour = h;
        minute = m;
        second = s;
        micro = ms;
        c = i; }
    return n; }

e_nit verify_svg_duration (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& minute, int& second, int& micro) noexcept
{   if (c == e) return nit_svg_duration;
    ::std::string::const_iterator i = c;
    int m = 0, s = 0, ms = 0;
    e_nit n = grab_digits (e, i, 4, 0, true, m);
    if (n == nit_free) n = grab_char (e, i, ':');
    if (n == nit_free) n = grab_digits (e, i, 4, 0, true, s);
    if (n == nit_free)
        if (grab_char (e, i, '.') == nit_free)
            n = grab_digits (e, i, 4, 0, true, ms);
    if (n == nit_free)
    {   minute = m;
        second = s;
        micro = ms;
        c = i; }
    return n; }

e_nit verify_svg_duration (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int64_t& second, int& micro) noexcept
{   if (c == e) return nit_svg_duration;
    ::std::string::const_iterator i = c;
    int ms = 0;
    int64_t s = 0;
    e_nit n = grab_digits < int64_t > (e, i, 4, 0, true, s);
    if (n == nit_free)
        if (grab_char (e, i, '.') == nit_free)
            n = grab_digits (e, i, 4, 0, true, ms);
    if (n == nit_free)
        if (grab_char (e, i, 'h') == nit_free)
        {   micro = 0; second = s * 3600; }
        else if (grab_char (e, i, 's') == nit_free)
        {   micro = 0; second = s; }
        else if (grab_char (e, i, 'm') == nit_free)
        {   n = grab_char (e, i, 'i');
            if (n == nit_free)
            {   n = grab_char (e, i, 'n');
                if (n == nit_free)
                {   micro = 0; second = s * 60; }
                else n = nit_svg_duration; }
            else
            {   n = grab_char (e, i, 's');
                if (n == nit_free)
                {   micro = ms; second = 0; }
                else n = nit_svg_duration;  } }
    if (n == nit_free) c = i;
    return n; }

e_nit verify_vague (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& year, int& month, int& week, int& day, int& hour, int& minute, int& second, int& micro, int& hour_offset, int& minute_offset, int64_t& duration)
{   ::std::string::const_iterator i = c;
    int y = 0, m = 0, w = 0, d = 0, h = 0, mn = 0, s = 0, ms = 0, ho = 0, mo = 0;
    int64_t s64 = 0; 
    if (verify_global_datetime (e, i, y, m, d, h, mn, s, ms, ho, mo) != nit_free)
        if (verify_floating_datetime (e, i, y, m, d, h, mn, s, ms) != nit_free)
            if (verify_time (e, i, h, mn, s, ms) != nit_free)
                if (verify_year (e, i, y, m, d) != nit_free)
                    if (verify_week_year (e, i, y, w) != nit_free)
                        if (verify_yearless_date (e, i, m, d) != nit_free)
                            if (verify_month (e, i, y, m))
                                if (verify_timezone (e, i, ho, mo))
                                    if (verify_duration (e, i, y, m, w, d, h, mn, s, ms) != nit_free)
                                        if (verify_duration (e, i, s64, ms) != nit_free)
                                            if (verify_simply_year (e, i, y) != nit_free)
                                                return nit_rather_too_vague;
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
    return nit_free; }

e_nit verify_ansi (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& weekday, int& year, int& month, int& week, int& day, int& hour, int& minute, int& second)
{   ::std::string::const_iterator i = c;
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, w = 0, wd = 0;
    e_nit n = verify_english_weekday_short (e, i, wd);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free) n = verify_english_month_short (e, i, mn);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free)
        if (grab_digits < int > (e, i, 2, 31, false, d) != nit_free)
        {   n = grab_char (e, i, ' ');
            if (n == nit_free) n = grab_digits < int > (e, i, 1, 9, false, d); }
    if (n == nit_free) n =  grab_char (e, i, ' ');
    if (n == nit_free) n = verify_hms (e, i, true, h, m, s);
    if (n == nit_free) n =  grab_char (e, i, ' ');
    if (n == nit_free) n = grab_year (e, i, y);
    if (n == nit_free) n = check_date (y, mn, d);
    if (n == nit_free)
    {   c = i;
        year = y;
        month = m;
        week = w;
        weekday = wd;
        day = d;
        hour = h;
        minute = mn;
        second = s; }
    return n; }

e_nit verify_rfc_822 (   const ::std::string::const_iterator e, ::std::string::const_iterator& c, bool longyear,
                        int& weekday, int& year, int& month, int& day, int& hour, int& minute, int& second, e_rfc822_zone& zone)
{   ::std::string::const_iterator i = c;
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, wd = 0, z = 0, zh = 0, zm = 0;
    e_nit n = nit_free;
    if (verify_english_weekday_short (e, i, wd) == nit_free)
    {   grab_char (e, i, ',');
        grab_char (e, i, ' '); }
    if (n == nit_free) n = grab_digits < int > (e, i, 2, 31, false, d);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free) n = verify_english_month_short (e, i, mn);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free)
    {   if (longyear) n = grab_year (e, i, y);
        else if (grab_short_year (e, i, y) != nit_free)
            n = grab_year (e, i, y); }
    if (n == nit_free) n = check_date (y, mn, d);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free) n = verify_hms (e, i, false, h, m, s);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (verify_rfc822_zone (e, i, z) == nit_free)
        zone = static_cast < e_rfc822_zone > (z);
    else
    {   if (grab_char (e, i, '+') != nit_free)
            grab_char (e, i, '-');
        if (n == nit_free) n = grab_digits < int > (e, i, 2, 23, false, zh);
        if (n == nit_free) n = grab_digits < int > (e, i, 2, 59, false, zm);
        zone = e8z_other; }
    if (n == nit_free)
    {   c = i;
        year = y;
        month = m;
        weekday = wd;
        day = d;
        hour = h;
        minute = mn;
        second = s; }
    return n; }

e_nit verify_rfc_850 (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& weekday, int& year, int& month, int& day, int& hour, int& minute, int& second)
{   ::std::string::const_iterator i = c;
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, wd = 0;
    if (verify_english_weekday_long (e, i, wd) == nit_free)
    {   grab_char (e, i, ',');
        grab_char (e, i, ' '); }
    e_nit n = grab_digits < int > (e, i, 2, 31, false, d);
    if (n == nit_free) n = grab_char (e, i, '-');
    if (n == nit_free) n = verify_english_month_short (e, i, mn);
    if (n == nit_free) n = grab_char (e, i, '-');
    if (n == nit_free) n = grab_year (e, i, y);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free) n = verify_hms (e, i, true, h, m, s);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free) n = grab_char (e, i, 'G');
    if (n == nit_free) n = grab_char (e, i, 'M');
    if (n == nit_free) n = grab_char (e, i, 'T');
    if (n == nit_free) n = check_date (y, mn, d);
    if (n == nit_free)
    {   c = i;
        year = y;
        month = m;
        weekday = wd;
        day = d;
        hour = h;
        minute = mn;
        second = s; }
    return n; }

e_nit verify_rfc_1123 (const ::std::string::const_iterator e, ::std::string::const_iterator& c, int& weekday, int& year, int& month, int& week, int& day, int& hour, int& minute, int& second)
{   ::std::string::const_iterator i = c;
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, w = 0, wd = 0;
    if (verify_english_weekday_short (e, i, wd) == nit_free)
    {   grab_char (e, i, ',');
        grab_char (e, i, ' '); }
    e_nit n = grab_digits < int > (e, i, 2, 31, false, d);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free) n = verify_english_month_short (e, i, mn);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free) n = grab_year (e, i, y);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free) n = verify_hms (e, i, true, h, m, s);
    if (n == nit_free) n = grab_char (e, i, ' ');
    if (n == nit_free) n = grab_char (e, i, 'G');
    if (n == nit_free) n = grab_char (e, i, 'M');
    if (n == nit_free) n = grab_char (e, i, 'T');
    if (n == nit_free) n = check_date (y, mn, d);
    if (n == nit_free)
    {   c = i;
        year = y;
        month = m;
        week = w;
        weekday = wd;
        day = d;
        hour = h;
        minute = mn;
        second = s; }
    return n; }

e_nit verify_vague (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, ms = 0, ho = 0, mo = 0, w = 0;
    int64_t s64 = 0;
    return verify_vague (e, i, y, m, w, d, h, mn, s, ms, ho, mo, s64); }

e_nit verify_ansi (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int wd = 0, y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, w = 0;
    return verify_ansi (e, i, wd, y, m, w, d, h, mn, s); }

e_nit verify_rfc_850 (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int wd = 0, y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0;
    return verify_rfc_850 (e, i, wd, y, m, d, h, mn, s); }

e_nit verify_rfc_1123 (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int wd = 0, y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, w = 0;
    return verify_rfc_1123 (e, i, wd, y, m, w, d, h, mn, s); }

e_nit verify_local_datetime (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, ms = 0, ho = 0, mo = 0, w = 0;
    int64_t s64 = 0;
    const e_nit n = verify_vague (e, i, y, m, w, d, h, mn, s, ms, ho, mo, s64);
    if (n != nit_free) return n;
    if ((ho == 0) && (mo == 0)) return nit_free;
    return nit_local_datetime; }

e_nit verify_absolute (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0, d = 0, h = 0, mn = 0, s = 0, ms = 0, ho = 0, mo = 0, w = 0;
    if (verify_global_datetime (e, i, y, m, d, h, mn, s, ms, ho, mo) != nit_free)
        if (verify_year (e, i, y, m, d) != nit_free)
            if (verify_week_year (e, i, y, w) != nit_free)
                return nit_absolute_datetime;
    return nit_free; }

e_nit verify_duration (const ::std::string& str)
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0, w = 0, d = 0, h = 0, mn = 0, s = 0, ms = 0;
    int64_t i64 = 0;
    if (verify_duration (e, i, y, m, w, d, h, mn, s, ms) != nit_free)
        if (verify_duration (e, i, i64, ms) != nit_free)
            return nit_duration;
    return nit_free; }

e_nit verify_svg_duration (const ::std::string& str) noexcept
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int  h = 0, mn = 0, s = 0, ms = 0;
    int64_t i64 = 0;
    if (verify_svg_duration (e, i, h, mn, s, ms) != nit_free)
        if (verify_svg_duration (e, i, mn, s, ms) != nit_free)
            if (verify_svg_duration (e, i, i64, ms) != nit_free)
                return nit_svg_duration;
    return nit_free; }

e_nit verify_coarse_time_tz (const ::std::string& str) noexcept
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int h = 0, m = 0, s = 0, ho = 0, mo = 0;
    return verify_coarse_time_tz (e, i, h, m, s, ho, mo); }

e_nit verify_month (const ::std::string& str) noexcept
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0;
    return verify_month (e, i, y, m); }

e_nit verify_monthday (const ::std::string& str) noexcept
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int m = 0, d = 0;
    return verify_monthday (e, i, m, d); }

e_nit verify_day (const ::std::string& str) noexcept
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int d = 0;
    return verify_day (e, i, d); }

e_nit verify_year (const ::std::string& str) noexcept
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0;
    return verify_year (e, i, y); }

e_nit verify_yearmonth (const ::std::string& str) noexcept
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0;
    return verify_yearmonth (e, i, y, m); }

e_nit verify_timezone (const ::std::string& str) noexcept
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int ho = 0, mo = 0;
    return verify_timezone (e, i, ho, mo); }

e_nit verify_week (const ::std::string& str) noexcept
{   ::std::string::const_iterator i = str.cbegin ();
    ::std::string::const_iterator e = str.cend ();
    int y = 0, m = 0;
    return verify_week_year (e, i, y, m); }

bool verify_time_4 (nitpick& nits, const html_version& v, const ::std::string& s)
{   const e_nit n = verify_absolute (s);
    if (n == nit_free) return true;
    if (v.mjr () < 4)
        nits.pick (n, es_warning, ec_type, quote (s), " is dubious: ISO-8601 datetime format is 'yyyy-mm-ddThh:mm:ssTZD', where TZD is 'Z' or 'Shh:mm', and S is '+' or '-'");
    else nits.pick (n, ed_4, "6.11 Dates and times", es_error, ec_type, quote (s), " is not in ISO-8601 datetime format: 'yyyy-mm-ddThh:mm:ssTZD', where TZD is 'Z' or 'Shh:mm', and S is '+' or '-'");
    return false; }

bool verify_time_5 (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_vague (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid datetime");
    return false; }

bool verify_http_time (nitpick& nits, const html_version& , const ::std::string& s)
{   e_nit n = verify_rfc_1123 (s);
    if (n != nit_free)
    {   n = verify_rfc_850 (s);
        if (n != nit_free)
        {   n = verify_ansi (s);
            if (n != nit_free)
            {   nits.pick (n, ed_rfc_2616, "3.3 Date/Time Formats", es_error, ec_type, quote (s), " is an invalid hyper datetime");
            return false; } } }
    return true; }

bool verify_absolute (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_absolute (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " must be an absolute datetime");
    return false; }

bool verify_duration (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_duration (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5.9 Durations", es_error, ec_type, quote (s), " is an invalid duration");
    return false; }

bool verify_day (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_day (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid day");
    return false; }

bool verify_month (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_month (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid month");
    return false; }

bool verify_monthday (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_month (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid month");
    return false; }

bool verify_year (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_year (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid year");
    return false; }

bool verify_yearmonth (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_year (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid year");
    return false; }

bool verify_local_datetime (nitpick& nits, const html_version& , const ::std::string& s)
{   e_nit n;
    if (s.find_first_of ("Zz") != ::std::string::npos) n = nit_bad_zone;
    else n = verify_local_datetime (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid local date (no timezones)");
    return false; }

bool verify_week (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_week (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid week");
    return false; }

bool verify_timezone (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_timezone (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid timezone");
    return false; }

bool verify_plain_date (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_year (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is not a plain and simple date");
    return false; }

bool verify_coarse_time (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_coarse_time_tz (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_50, "2.4.5 Dates and times", es_error, ec_type, quote (s), " is an invalid time (hh:mm:ss[Z|(+|-)hh:mm])");
    return false; }

bool verify_svg_duration (nitpick& nits, const html_version& , const ::std::string& s)
{   const e_nit n = verify_svg_duration (s);
    if (n == nit_free) return true;
    nits.pick (n, ed_svg_1_1, "19.2.8.1 Clock values", es_error, ec_type, quote (s), " is an invalid duration");
    return false; }

time_t string_to_time (nitpick& nits, const ::std::string& s)
{   if (s.empty ()) return 0;
    struct tm t = { };
    const e_nit n = acquire_global_datetime (s, t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    if (n != nit_free)
        nits.pick (n, es_error, ec_type, quote (s), ": expecting 'YYYY-MM-DD hh:mm:ss' as valid integers");
    return ::std::mktime (&t); }

bool verify_rfc822 (nitpick& nits, const html_version& , const ::std::string& s, bool longyear)
{   if (s.empty ()) return 0;
    int weekday, year, month, day, hour, minute, second;
    e_rfc822_zone zone;
    ::std::string::const_iterator i = s.cbegin ();
    const e_nit n = verify_rfc_822 (s.cend (), i, longyear, weekday, year, month, day, hour, minute, second, zone);
    if (n != nit_free)
    {   nits.pick (n, es_error, ec_type, quote (s), ": expecting 'DD MMM YY HH:MM:SS ZONE'");
        return false; }
    switch (zone)
    {   case e8z_cdt :
            nits.pick (nit_rfc822_zone, es_warning, ec_type, "CST here is not Cuba Daylight Time, but Central Daylight Time; consider using GMT");
            break;
        case e8z_cst :
            nits.pick (nit_rfc822_zone, es_warning, ec_type, "CST here is neither China Standard Time nor Cuba Standard Time, but Central Standard Time; consider using GMT");
            break;
        case e8z_mst :
            nits.pick (nit_rfc822_zone, es_warning, ec_type, "CST here is not Malaysian Standard Time, but Eastern Stardard Time; consider using GMT");
            break;
        case e8z_pst :
            nits.pick (nit_rfc822_zone, es_comment, ec_type, "CST here is not a shouted comedic whisper, but Pacific Stardard Time; consider using GMT");
            break;
        case e8z_edt :
        case e8z_est :
        case e8z_mdt :
        case e8z_pdt :
        case e8z_a :
        case e8z_m :
        case e8z_n :
        case e8z_y :
        case e8z_z :
            nits.pick (nit_rfc822_zone, es_info, ec_type, ::boost::to_upper_copy (type_master < t_rfc822_zone > :: name (zone)), ": RFC 822 timezones can be ambiguous; consider using GMT");
            break;
        default :
            break; }
    return true; }

// ******************************** note to self: effing well sort this out. FFS.  ********************************
bool test_animation_timing (nitpick& , const html_version& , const ::std::string& , const bool )
{   // 19.2.8 Attributes to control the timing of the animation
//    ::std::string ss (trim_the_lot_off (s));
//    if (ss.empty ())
//        nits.pick (nit_empty, es_error, ec_type, "times should not be empty");
//    else
//    {  ::std::string::size_type pos = ss.find ('.');
//        ::std::string id_value;
//        if (pos != ::std::string::npos)
//        {   id_value = ss.substr (0, pos);
//            ss.substr (pos); }
//    }
//    PRESUME (false, __FILE__, __LINE__);
    return true; }
