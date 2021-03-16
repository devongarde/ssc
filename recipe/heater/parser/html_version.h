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
#include "feedback/nitpick.h"
#include "schema/schema_version.h"

// HTML 5 is a living standard form WhatWG, constantly changing.
// The WhatWG website appeared in 2004, with their first draft
// of their HTML 5 standard published in June 2007. Many have followed!
// The W3C HTML standards appeared as follows:
//   HTML 5.0 28 October 2014
//   HTML 5.1 first version 1 November 2016
//   HTML 5.1 second version 3 October 2017
//   HTML 5.2 14 December 2017
//   HTML 5.3 18 October 2018
// The internal versions of HTML5 are thus:
//   major = year-2000
//   minor:
//     high nibble = month
//      low nibble = day / 2

// use these ids even though their value is obvious; there is no guarantee that
// the values will continue to be obvious, e.g., for example, if very erly webapp
// specs should be integrated (not expected, which is why I'm not doing it, but...)
#define HTML_2005    5
#define HTML_2006    6
#define HTML_2007    7
#define HTML_2008    8
#define HTML_2009    9
#define HTML_2010   10
#define HTML_2011   11
#define HTML_2012   12
#define HTML_2013   13
#define HTML_2014   14
#define HTML_2015   15
#define HTML_2016   16
#define HTML_2017   17
#define HTML_2018   18
#define HTML_2019   19
#define HTML_2020   20
#define HTML_2021   21

#define MAJOR_TAGS   0
#define MAJOR_1_0    1
#define MAJOR_PLUS   1
#define MAJOR_2_0    2
#define MAJOR_3_0    3
#define MAJOR_3_2    3
#define MAJOR_4_0    4
#define MAJOR_4_01   4
#define MAJOR_X1_0   4
#define MAJOR_X1_1   4
#define MAJOR_X2_0   4

#define HTML_JAN     (1 << 4)
#define HTML_FEB     (2 << 4)
#define HTML_MAR     (3 << 4)
#define HTML_APR     (4 << 4)
#define HTML_MAY     (5 << 4)
#define HTML_JUN     (6 << 4)
#define HTML_JUL     (7 << 4)
#define HTML_AUG     (8 << 4)
#define HTML_SEP     (9 << 4)
#define HTML_OCT     (10 << 4)
#define HTML_NOV     (11 << 4)
#define HTML_DEC     (12 << 4)

#define MINOR_TAGS   1
#define MINOR_1_0    0
#define MINOR_PLUS   1
#define MINOR_2_0    0
#define MINOR_3_0    0
#define MINOR_3_2    2
#define MINOR_4_0    0
#define MINOR_4_01   1
#define MINOR_X1_0   2
#define MINOR_X1_1   3
#define MINOR_X2_0   4

#define HTML_TAGS   MAJOR_TAGS, MINOR_TAGS
#define HTML_1_0    MAJOR_1_0, MINOR_1_0
#define HTML_PLUS   MAJOR_PLUS, MINOR_PLUS
#define HTML_2_0    MAJOR_2_0, MINOR_2_0
#define HTML_3_0    MAJOR_3_0, MINOR_3_0
#define HTML_3_2    MAJOR_3_2, MINOR_3_2
#define HTML_4_0    MAJOR_4_0, MINOR_4_0
#define HTML_4_01   MAJOR_4_01, MINOR_4_01
#define XHTML_1_0   MAJOR_X1_0, MINOR_X1_0
#define XHTML_1_1   MAJOR_X1_1, MINOR_X1_1
#define XHTML_2_0   MAJOR_X2_0, MINOR_X2_0

#define MAJOR_5_0   HTML_2014
#define MAJOR_5_1   HTML_2016
#define MAJOR_5_2   HTML_2017
#define MAJOR_5_3   HTML_2018
#define MINOR_5_0   (HTML_OCT + 14)
#define MINOR_5_1   (HTML_OCT + 1)
#define MINOR_5_2   (HTML_DEC + 7)
#define MINOR_5_3   (HTML_OCT + 9)
#define HTML_5_0    MAJOR_5_0, MINOR_5_0
#define HTML_5_1    MAJOR_5_1, MINOR_5_1
#define HTML_5_2    MAJOR_5_2, MINOR_5_2
#define HTML_5_3    MAJOR_5_3, MINOR_5_3

#define HTML_JAN05  HTML_2005, (HTML_JAN + 15)
#define HTML_JUN05  HTML_2005, (HTML_JUN + 15)
#define HTML_JUL05  HTML_2005, HTML_JUL
#define HTML_DEC05  HTML_2005, (HTML_DEC + 15)
#define HTML_JAN06  HTML_2006, HTML_JAN
#define HTML_JUN06  HTML_2006, (HTML_JUN + 13)
#define HTML_JUL06  HTML_2006, HTML_JUL
#define HTML_DEC06  HTML_2006, (HTML_DEC + 15)
#define HTML_JAN07  HTML_2007, HTML_JAN
#define HTML_JUN07  HTML_2007, (HTML_JUN + 15)
#define HTML_JUL07  HTML_2007, HTML_JUL
#define HTML_OCT07  HTML_2007, HTML_OCT
#define HTML_DEC07  HTML_2007, (HTML_DEC + 15)
#define HTML_JAN08  HTML_2008, HTML_JAN
#define HTML_JUN08  HTML_2008, (HTML_JUN + 13)
#define HTML_JUL08  HTML_2008, HTML_JUL
#define HTML_DEC08  HTML_2008, (HTML_DEC + 15)
#define HTML_JAN09  HTML_2009, HTML_JAN
#define HTML_JUN09  HTML_2009, (HTML_JUN + 15)
#define HTML_JUL09  HTML_2009, HTML_JUL
#define HTML_DEC09  HTML_2009, (HTML_DEC + 15)
#define HTML_JAN10  HTML_2010, HTML_JAN
#define HTML_JUN10  HTML_2010, (HTML_JUN + 15)
#define HTML_JUL10  HTML_2010, HTML_JUL
#define HTML_DEC10  HTML_2010, (HTML_DEC + 15)
#define HTML_JAN11  HTML_2011, HTML_JAN
#define HTML_JUN11  HTML_2011, (HTML_JUN + 15)
#define HTML_JUL11  HTML_2011, HTML_JUL
#define HTML_DEC11  HTML_2011, (HTML_DEC + 15)
#define HTML_JAN12  HTML_2012, HTML_JAN
#define HTML_JUN12  HTML_2012, (HTML_JUN + 15)
#define HTML_JUL12  HTML_2012, HTML_JUL
#define HTML_DEC12  HTML_2012, (HTML_DEC + 15)
#define HTML_JAN13  HTML_2013, HTML_JAN
#define HTML_JUN13  HTML_2013, (HTML_JUN + 15)
#define HTML_FEB13  HTML_2013, (HTML_AUG + 14)
#define HTML_JUL13  HTML_2013, HTML_JUL
#define HTML_AUG13  HTML_2013, (HTML_AUG + 3)
#define HTML_DEC13  HTML_2013, (HTML_DEC + 15)
#define HTML_JAN14  HTML_2014, HTML_JAN
#define HTML_JUN14  HTML_2014, (HTML_JUN + 15)
#define HTML_JUL14  HTML_2014, HTML_JUL
#define HTML_DEC14  HTML_2014, (HTML_DEC + 15)
#define HTML_JAN15  HTML_2015, HTML_JAN
#define HTML_JUN15  HTML_2015, (HTML_JUN + 15)
#define HTML_JUL15  HTML_2015, HTML_JUL
#define HTML_DEC15  HTML_2015, (HTML_DEC + 15)
#define HTML_JAN16  HTML_2016, HTML_JAN
#define HTML_JUN16  HTML_2016, (HTML_JUN  + 15)
#define HTML_JUL16  HTML_2016, HTML_JUL
#define HTML_DEC16  HTML_2016, (HTML_DEC + 15)
#define HTML_JAN17  HTML_2017, HTML_JAN
#define HTML_JUN17  HTML_2017, (HTML_JUN + 15)
#define HTML_JUL17  HTML_2017, HTML_JUL
#define HTML_NOV17  HTML_2017, HTML_NOV
#define HTML_DEC17  HTML_2017, (HTML_DEC + 15)
#define HTML_JAN18  HTML_2018, HTML_JAN
#define HTML_JUN18  HTML_2018, (HTML_JUN + 15)
#define HTML_JUL18  HTML_2018, HTML_JUL
#define HTML_DEC18  HTML_2018, (HTML_DEC + 15)
#define HTML_JAN19  HTML_2019, HTML_JAN
#define HTML_JUN19  HTML_2019, (HTML_JUN + 15)
#define HTML_JUL19  HTML_2019, HTML_JUL
#define HTML_DEC19  HTML_2019, (HTML_DEC + 15)
#define HTML_JAN20  HTML_2020, HTML_JAN
#define HTML_JUN20  HTML_2020, (HTML_JUN + 15)
#define HTML_JUL20  HTML_2020, HTML_JUL
#define HTML_DEC20  HTML_2020, (HTML_DEC + 15)
#define HTML_JAN21  HTML_2021, HTML_JAN
#define HTML_EOJ21  HTML_2021, (HTML_JAN + 15)
#define HTML_FEB21  HTML_2021, HTML_FEB

#define HTML_5_EARLIEST_YEAR    HTML_2005
#define HTML_5_EARLIEST_MONTH   1

#define HTML_LATEST_YEAR    HTML_2021
#define HTML_LATEST_MONTH   2

#define HTML_CURRENT HTML_LATEST_YEAR, HTML_LATEST_MONTH

#define HTML_UNDEF  0, 0

#define HV_LEVEL1       0x0000000000000001
#define HV_LEVEL2       0x0000000000000002
#define HV_LEVEL3       0x0000000000000004
#define HV_LEVEL_MASK   0x0000000000000007

#define HV_XHTML        0x0000000000000020
#define HV_ARIA         0x0000000000000040

#define HR_A_AREA       0x0000000000000100
#define HR_LINKHEAD     0x0000000000000200
#define HR_LINKBODY     0x0000000000000400
#define HR_LINK         ( HR_LINKHEAD | HR_LINKBODY )
#define HR_EXTERNAL     0x0000000000000800
#define HR_FORM         0x0000000000001000
#define HR_ALL          0x0000000000001F00
#define HR_MF1          0x0000000000002000
#define HR_MF2          0x0000000000004000
#define HR_MF           ( HR_MF1 | HR_MF2 )

#define HL_CSS1         0x0000000000001000
#define HL_CSS2         0x0000000000002000
#define HL_CSS3         0x0000000000004000
#define HL_CSS4         0x0000000000008000
#define HL_CSS5         0x0000000000010000
#define HL_CSS_45       ( HL_CSS4 | HL_CSS5 )
#define HL_CSS_345      ( HL_CSS3 | HL_CSS_45 )
#define HL_CSS_ALL      ( HL_CSS1 | HL_CSS2 | HL_CSS_345 )

#define HV_CSP_1        0x0000000000001000
#define HV_CSP_2        0x0000000000002000
#define HV_CSP_3        0x0000000000004000

#define HV_WHATWG       0x0000000000100000
#define HV_W3           0x0000000000200000

#define HV_DEPRECATED2  0x0000000000800000
#define HV_DEPRECATED30 0x0000000001000000
#define HV_DEPRECATED32 0x0000000002000000
#define HV_DEPRECATED4  0x0000000004000000
#define HV_DEPRECATED50 0x0000000008000000
#define HV_DEPRECATED51 0x0000000010000000
#define HV_DEPRECATED52 0x0000000020000000
#define HV_DEPRECATED53 0x0000000040000000
#define HV_DEPRECATED54 0x0000000080000000
#define HV_DEPRECATED1  0x0000000100000000
#define HV_DEPRECATEDX1 0x0000000200000000
#define HV_DEPRECATEDX11 0x0000000400000000
#define HV_DEPRECATEDX2 0x0000000800000000

#define HV_DINOSAUR     0x0000001000000000
#define REJECT          0x0000002000000000
#define REQUIRED        0x0000004000000000

#define HV_INT          0x0000008000000000
#define HV_STRICT       0x0000010000000000
#define HV_TRANSITIONAL 0x0000020000000000
#define HV_FRAMESET     0x0000040000000000
#define HV_BASIC        0x0000080000000000

#define HV_RFC_1867     0x0000100000000000
#define HV_RFC_1942     0x0000200000000000
#define HV_RFC_1980     0x0000400000000000
#define HV_RFC_2070     0x0000800000000000

#define HV_NOT10        0x0001000000000000
#define HV_NOT2L1       0x0002000000000000
#define HV_NOTPLUS      0x0004000000000000
#define HV_NOT2         0x0008000000000000
#define HV_NOT30        0x0010000000000000
#define HV_NOT32        0x0020000000000000
#define HV_NOT4         0x0040000000000000
#define HV_NOTX1        0x0080000000000000
#define HV_NOTX2        0x0100000000000000
#define HV_NOT50        0x0200000000000000
#define HV_NOT51        0x0400000000000000
#define HV_NOT52        0x0800000000000000
#define HV_NOT53        0x1000000000000000
#define HV_NOTX5        0x2000000000000000

#define HV_NOT3         ( HV_NOT30 | HV_NOT32 )
#define HV_NOT234       ( HV_NOT2 | HV_NOT3 | HV_NOT32 | HV_NOT4 )
#define HV_NOT324       ( HV_NOT32 | HV_NOT4 | HV_NOTX1 )
#define HV_NOT324XX     ( HV_NOT324 | HV_NOTX2 )
#define HV_NOT4XX       ( HV_NOT4 | HV_NOTX1 | HV_NOTX2 )
#define HV_NOTXX        ( HV_NOTX1 | HV_NOTX2 )
#define HV_NOTXXX       ( HV_NOTXX | HV_NOTX5 )
#define HV_NOT5W3       ( HV_NOT50 | HV_NOT51 | HV_NOT52 | HV_NOT53 )
#define HV_NOT5123      ( HV_NOT51 | HV_NOT52 | HV_NOT53 )

#define HV_DEPRECATED123 ( HV_DEPRECATED1 | HV_DEPRECATED2 | HV_DEPRECATED30 | HV_DEPRECATED32 )
#define HV_DEPRECATED23  ( HV_DEPRECATED2 | HV_DEPRECATED30 | HV_DEPRECATED32 )
#define HV_DEPRECATED234 ( HV_DEPRECATED23 | HV_DEPRECATED4 )
#define HV_DEPRECATED54x ( HV_DEPRECATED54 )
#define HV_DEPRECATED53x ( HV_DEPRECATED53 | HV_DEPRECATED54x )
#define HV_DEPRECATED52x ( HV_DEPRECATED52 | HV_DEPRECATED53x )
#define HV_DEPRECATED51x ( HV_DEPRECATED51 | HV_DEPRECATED52x )
#define HV_DEPRECATED50x ( HV_DEPRECATED50 | HV_DEPRECATED51x )
#define HV_DEPRECATED5   ( HV_DEPRECATED50x )
#define HV_DEPRECATEDWWG ( HV_DEPRECATED54x )
#define HV_DEPRECATED45  ( HV_DEPRECATED4 | HV_DEPRECATED50x )

#define HV_DEPRECATED_MASK 0x0000000FFF800000

#define HE_MATH_1       0x0000000000000001
#define HE_MATH_2       0x0000000000000002
#define HE_MATH_3       0x0000000000000004
#define HE_MATH_4       0x0000000000000008
#define HE_SVG_1_0      0x0000000000000010
#define HE_SVG_1_1      0x0000000000000020
#define HE_SVG_1_2_TINY 0x0000000000000040
#define HE_SVG_1_2_FULL 0x0000000000000080
#define HE_SVG_2_0      0x0000000000000100
#define HE_XLINK_1_0    0x0000000000000200
#define HE_XLINK_1_1    0x0000000000000400
#define HE_RDF_1_0      0x0000000000001000
#define HE_RDF_1_1      0x0000000000002000
#define HE_MICRODATA    0x0000000000010000
#define HE_SVG_X1       0x0000000000100000
#define HE_SVG_X2       0x0000000000200000
#define HE_SVG_OLD_H    0x0000000000400000
#define HE_NOT_SVG      0x0000000000800000
#define HE_M2_DEPRECAT  0x0000000001000000
#define HE_M3_DEPRECAT  0x0000000002000000
#define HE_M3_NONSTAND  0x0000000010000000

#define MATH_MASK       ( HE_MATH_1 | HE_MATH_2 | HE_MATH_3 | HE_MATH_4 )
#define MATH_1_2        ( HE_MATH_1 | HE_MATH_2 )
#define MATH_1_2_3      ( HE_MATH_1 | HE_MATH_2 | HE_MATH_3 )
#define MATH_2_3        ( HE_MATH_2 | HE_MATH_3 )
#define HE_SVG_1_2      ( HE_SVG_1_2_TINY | HE_SVG_1_2_FULL )
#define HE_SVG_1        ( HE_SVG_1_0 | HE_SVG_1_1 | HE_SVG_1_2 )
#define HE_SVG_1x2      ( HE_SVG_1_1 | HE_SVG_1_2 | HE_SVG_2_0 )
#define HE_SVG          ( HE_SVG_1 | HE_SVG_2_0 )
#define SVG_MASK        HE_SVG
#define HE_SVG_X_MASK   ( HE_SVG_X1 | HE_SVG_X2 )
#define XLINK_MASK      ( HE_XLINK_1_0 | HE_XLINK_1_1 )
#define RDF_MASK        ( HE_RDF_1_0 | HE_RDF_1_1 )

#define MATH_SHIFT      0
#define SVG_SHIFT       4
#define XLINK_SHIFT     9
#define RDF_SHIFT       12

#define HE_EXPERIMENTAL 0x0000000010000000

#define HE_NETSCAPE     0x0000000100000000
#define HE_IE           0x0000000200000000
#define HE_WEBCOMP      0x0000000400000000
#define HE_BESPOKE      0x0000000800000000
#define HE_MOZILLA      0x0000001000000000
#define HE_CHROME       0x0000002000000000
#define HE_OPERA        0x0000004000000000
#define HE_SAFARI       0x0000008000000000

class html_version
{   unsigned char mjr_ = 0, mnr_ = 0;
    uint64_t flags_ = 0, ext_ = 0;
    bool note_parsed_version (nitpick& nits, const e_nit n, const html_version& got, const ::std::string& gen);
    void init (const unsigned char mjr);
public:
    html_version () : mjr_ (0), mnr_ (0), flags_ (NOFLAGS), ext_ (NOFLAGS) { }
    explicit html_version (const unsigned char mjr) { init (mjr); }
    explicit html_version (const schema_version sv) : mjr_ (sv.mjr ()), mnr_ (sv.mnr ()), flags_ (NOFLAGS), ext_ (NOFLAGS) { }
    html_version (const unsigned char mjr, const unsigned char mnr, const uint64_t flags = NOFLAGS, const uint64_t extensions = NOFLAGS);
    html_version (const ::boost::gregorian::date& whatwg, const uint64_t flags = NOFLAGS, const uint64_t extensions = NOFLAGS);
	html_version (const html_version& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	html_version (html_version&& ) = default;
#endif // VS
	~html_version() = default;
    html_version& operator = (const html_version& ) = default;
#ifndef NO_MOVE_CONSTRUCTOR
	html_version& operator = (html_version&& ) = default;
#endif // VS
    void swap (html_version& v) NOEXCEPT;
    void reset () { html_version v; swap (v); }
    void reset (const html_version& v) { html_version vv (v); swap (vv); }
    bool unknown () const { return (mjr_ == 0) && (mnr_ == 0); }
    bool known () const { return ! unknown (); }
    bool is_not (const unsigned char mjr, const unsigned char mnr = 0xFF) const
    {   if (unknown ()) return false;
        if (mjr != mjr_) return true;
        return ((mnr != 0xFF) && (mnr != mnr_)); }
    bool is_not (const html_version& v) const
    {   return is_not (v.mjr_, v.mnr_); }
    unsigned char mjr () const { return mjr_; }
    unsigned char mnr () const { return mnr_; }
    unsigned char level () const { return (flags_ & HV_LEVEL_MASK); }
    bool is_0 () const { return mjr_ == 0; }
    bool is_1 () const { return mjr_ == 1; }
    bool is_2 () const { return mjr_ == 2; }
    bool is_3 () const { return mjr_ == 3; }
    bool is_4 () const { return mjr_ == 4; }
    bool is_5 () const { return mjr_ > 4; }
    bool is_b4_1 () const { return mjr_ < 1; }
    bool is_b4_2 () const { return mjr_ < 2; }
    bool is_b4_3 () const { return mjr_ < 3; }
    bool is_b4_4 () const { return mjr_ < 4; }
    bool is_b4_5 () const { return mjr_ < 5; }
    bool is_1_or_more () const { return mjr_ >= 1; }
    bool is_2_or_more () const { return mjr_ >= 2; }
    bool is_3_or_more () const { return mjr_ >= 3; }
    bool is_4_or_more () const { return mjr_ >= 4; }
    bool bespoke () const { return ((ext_ & HE_BESPOKE) == HE_BESPOKE); }
    bool chrome () const { return ((ext_ & HE_CHROME) == HE_CHROME); }
    bool dinosaur () const { return ((flags_ & HV_DINOSAUR) == HV_DINOSAUR); }
    bool experimental () const { return ((ext_ & HE_EXPERIMENTAL) == HE_EXPERIMENTAL); }
    bool frameset () const { return ((flags_ & HV_FRAMESET) == HV_FRAMESET); }
    bool ie () const { return ((ext_ & HE_IE) == HE_IE); }
    bool has_math () const { return (ext_ & MATH_MASK) != 0; }
    bool has_rdf () const { return (ext_ & RDF_MASK) != 0; }
    bool has_svg () const { return (ext_ & SVG_MASK) != 0; }
    bool has_xlink () const { return (ext_ & XLINK_MASK) != 0; }
    int math () const { return static_cast < int > ((ext_ & MATH_MASK) >> MATH_SHIFT); }
    int rdf () const { return static_cast < int > ((ext_ & RDF_MASK) >> RDF_SHIFT); }
    int svg () const { return static_cast < int > ((ext_ & SVG_MASK) >> SVG_SHIFT); }
    bool not_svg () const { return (ext_ & HE_NOT_SVG) != 0; }
    e_svg_version svg_version () const;
    void svg_version (const e_svg_version v);
    e_mathversion math_version () const;
    void math_version (const e_mathversion v);
    bool is_plain_html () const;
    int xlink () const { return static_cast < int > ((ext_ & XLINK_MASK) >> XLINK_SHIFT); }
    void ext_set (const uint64_t u) { ext_ |= u; }
    void ext_reset (const uint64_t u) { ext_ &= ~u; }
    bool check_math_svg (nitpick& nits, const html_version& a, const ::std::string& x) const;
    bool microdata () const { return ((ext_ & HE_MICRODATA) == HE_MICRODATA); }
    bool mozilla () const { return ((ext_ & HE_MOZILLA) == HE_MOZILLA); }
    bool netscape () const { return ((ext_ & HE_NETSCAPE) == HE_NETSCAPE); }
    bool not10 () const { return ((flags_ & HV_NOT10) == HV_NOT10); }
    bool not2 () const { return ((flags_ & HV_NOT2) == HV_NOT2); }
    bool not2l1 () const { return ((flags_ & HV_NOT2L1) == HV_NOT2L1); }
    bool not3 () const { return ((flags_ & HV_NOT3) != 0); }
    bool not30 () const { return ((flags_ & HV_NOT30) == HV_NOT30); }
    bool not32 () const { return ((flags_ & HV_NOT32) == HV_NOT32); }
    bool not4 () const { return ((flags_ & HV_NOT4) == HV_NOT4); }
    bool notx1 () const { return ((flags_ & HV_NOTX1) == HV_NOTX1); }
    bool notx2 () const { return ((flags_ & HV_NOTX2) == HV_NOTX2); }
    bool notx5 () const { return ((flags_ & HV_NOTX5) == HV_NOTX5); }
    bool notplus () const { return ((flags_ & HV_NOTPLUS) == HV_NOTPLUS); }
    bool not50 () const { return ((flags_ & HV_NOT50) == HV_NOT50); }
    bool not51 () const { return ((flags_ & HV_NOT51) == HV_NOT51); }
    bool not52 () const { return ((flags_ & HV_NOT52) == HV_NOT52); }
    bool not53 () const { return ((flags_ & HV_NOT53) == HV_NOT53); }
    bool opera () const { return ((ext_ & HE_OPERA) == HE_OPERA); }
    bool reject () const { return ((flags_ & REJECT) == REJECT); }
    bool required () const { return ((flags_ & REQUIRED) == REQUIRED); }
    bool rfc_1867 () const { return ((flags_ & HV_RFC_1867) == HV_RFC_1867); }
    bool rfc_1942 () const { return ((flags_ & HV_RFC_1942) == HV_RFC_1942); }
    bool rfc_1980 () const { return ((flags_ & HV_RFC_1980) == HV_RFC_1980); }
    bool rfc_2070 () const { return ((flags_ & HV_RFC_2070) == HV_RFC_2070); }
    bool safari () const { return ((ext_ & HE_SAFARI) == HE_SAFARI); }
    bool strict () const { return ((flags_ & HV_STRICT) == HV_STRICT); }
    bool w3 () const { return ((flags_ & HV_W3) == HV_W3); }
    bool webcomponents () const { return ((ext_ & HE_WEBCOMP) == HE_WEBCOMP); }
    bool whatwg () const { return ((flags_ & HV_WHATWG) == HV_WHATWG); }
    bool xhtml () const { return ((flags_ & HV_XHTML) == HV_XHTML); }
    bool svg_x1 () const { return ((ext_ & HE_SVG_X1) == HE_SVG_X1); }
    bool svg_x2 () const { return ((ext_ & HE_SVG_X2) == HE_SVG_X2); }
    bool svg_old_html () const { return ((ext_ & HE_SVG_OLD_H) == HE_SVG_OLD_H); }
    bool is_a_area () const { return ((flags_ & HR_A_AREA) == HR_A_AREA); }
    bool is_external () const { return ((flags_ & HR_EXTERNAL) == HR_EXTERNAL); }
    bool is_form () const { return ((flags_ & HR_FORM) == HR_FORM); }
    bool is_linkhead () const { return ((flags_ & HR_LINKHEAD) == HR_LINKHEAD); }
    bool is_linkbody () const { return ((flags_ & HR_LINKBODY) == HR_LINKBODY); }
    bool is_link () const { return ((flags_ & HR_LINK) != 0); }
    bool is_mf () const { return ((flags_ & HR_MF) != 0); }
    bool is_rel () const { return ((flags_ & HR_ALL) != 0); }
    bool invalid_addendum (const html_version& v) const;
    bool deprecated (const html_version& current) const;
    bool parse_doctype (nitpick& nits, const ::std::string& content);
    bool lazy () const;
    uint64_t flags () const { return flags_; }
    uint64_t ext () const { return ext_; }
    bool valid_charset (const ::std::string& charset) const;
    bool restricted_charset () const;
    const char *default_charset () const;
    const char *alternative_charset () const;
    ::std::string get_doctype () const;
    ::std::string name () const;
    ::std::string report () const; };

const html_version html_0;
const html_version html_tags (0, 1);
const html_version html_1 (1, 0);
const html_version html_plus (1, 1);
const html_version html_2 (2, 0);
const html_version html_2_level_1 (2, 0, HV_LEVEL1);
const html_version html_2_level_2 (2, 0, HV_LEVEL2);
const html_version html_3_0 (3, 0);
const html_version html_3_2 (3, 2);
const html_version html_4_0 (4, 0);
const html_version html_4_1 (4, 1);
const html_version xhtml_1_0 (4, 2, HV_XHTML);
const html_version xhtml_1_1 (4, 3, HV_XHTML);
const html_version xhtml_2 (4, 4, HV_XHTML);

const html_version html_jan05 (HTML_JAN05, HV_WHATWG, 0);
const html_version html_jul05 (HTML_JUL05, HV_WHATWG, 0);
const html_version html_jan06 (HTML_JAN06, HV_WHATWG, 0);
const html_version html_jan07 (HTML_JAN07, HV_WHATWG, 0);
const html_version html_jul07 (HTML_JUL07, HV_WHATWG, 0);
const html_version html_jan08 (HTML_JAN08, HV_WHATWG, 0);
const html_version html_jul08 (HTML_JUL08, HV_WHATWG, 0);
const html_version html_jan09 (HTML_JAN09, HV_WHATWG, 0);
const html_version html_jul09 (HTML_JUL09, HV_WHATWG, 0);
const html_version html_jan10 (HTML_JAN10, HV_WHATWG, 0);
const html_version html_jul10 (HTML_JUL10, HV_WHATWG, 0);
const html_version html_jan12 (HTML_JAN12, HV_WHATWG, 0);
const html_version html_jul12 (HTML_JUL12, HV_WHATWG, 0);
const html_version html_jan13 (HTML_JAN13, HV_WHATWG, 0);
const html_version html_jul13 (HTML_JUL13, HV_WHATWG, 0);
const html_version html_jan15 (HTML_JAN15, HV_WHATWG, HE_MATH_2 | HE_SVG_1_0);
const html_version html_jan16 (HTML_JAN16, HV_WHATWG, HE_MATH_2 | HE_SVG_1_0);
const html_version html_jan17 (HTML_JAN17, HV_WHATWG, HE_MATH_2 | HE_SVG_1_0);
const html_version html_jul17 (HTML_JUL17, HV_WHATWG, HE_MATH_2 | HE_SVG_1_1);
const html_version html_jul18 (HTML_JUL18, HV_WHATWG, HE_MATH_3 | HE_SVG_1_1);
const html_version html_jan19 (HTML_JAN19, HV_WHATWG, HE_MATH_3 | HE_SVG_2_0);
const html_version html_jul19 (HTML_JUL19, HV_WHATWG, HE_MATH_3 | HE_SVG_2_0);
const html_version html_jul20 (HTML_JUL20, HV_WHATWG, HE_MATH_4 | HE_SVG_2_0);
const html_version html_jan21 (HTML_JAN21, HV_WHATWG, HE_MATH_4 | HE_SVG_2_0);
const html_version html_feb21 (HTML_FEB21, HV_WHATWG, HE_MATH_4 | HE_SVG_2_0);
const html_version html_5_0 (HTML_5_0, HV_W3, HE_MATH_2 | HE_SVG_1_0);
const html_version html_5_1 (HTML_5_1, HV_W3, HE_MATH_2 | HE_SVG_1_1);
const html_version html_5_2 (HTML_5_2, HV_W3, HE_MATH_3 | HE_SVG_1_1);
const html_version html_5_3 (HTML_5_3, HV_W3, HE_MATH_3 | HE_SVG_1_1);
const html_version html_current (HTML_CURRENT, HV_WHATWG, HE_MATH_4 | HE_SVG_2_0);
const html_version html_default (html_5_3);

bool operator == (const html_version& lhs, const html_version& rhs);
bool operator != (const html_version& lhs, const html_version& rhs);
bool operator < (const html_version& lhs, const html_version& rhs);
bool operator > (const html_version& lhs, const html_version& rhs);
bool operator <= (const html_version& lhs, const html_version& rhs);
bool operator >= (const html_version& lhs, const html_version& rhs);
bool does_apply (const html_version& v, const html_version& from, const html_version& to);
bool may_apply (const html_version& v, const html_version& from, const html_version& to);
bool parse_doctype (nitpick& nits, html_version& version, const ::std::string::const_iterator b, const ::std::string::const_iterator e);
int w3_minor_5 (const html_version& v);
int w3_5_minor (const html_version& v);
e_emi extension_conflict (const html_version& lhs, const html_version& rhs);
const char *default_charset (const html_version& v);
const char *alternative_charset (const html_version& v);
