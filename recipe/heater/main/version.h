/*
ssc (static site checker)
Copyright (c) 2020-2022 Dylan Harris
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

// use these date ids even though their value is obvious; there is no guarantee that
// the values will continue to be obvious, e.g., if very early webapp (pre 2005) specs
// should be integrated (not expected, which is why I'm not doing it, but...)
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
#define HTML_2022   22

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

#define HTML_1ST     0
#define HTML_2ND     0
#define HTML_3RD     1
#define HTML_4TH     1
#define HTML_5TH     2
#define HTML_6TH     2
#define HTML_7TH     3
#define HTML_8TH     3
#define HTML_9TH     4
#define HTML_10TH    4
#define HTML_11TH    5
#define HTML_12TH    5
#define HTML_13TH    6
#define HTML_14TH    6
#define HTML_15TH    7
#define HTML_16TH    7
#define HTML_17TH    8
#define HTML_18TH    8
#define HTML_19TH    9
#define HTML_20TH    9
#define HTML_21ST    10
#define HTML_22ND    10
#define HTML_23RD    11
#define HTML_24TH    11
#define HTML_25TH    12
#define HTML_26TH    12
#define HTML_27TH    13
#define HTML_28TH    13
#define HTML_29TH    14
#define HTML_30TH    14
#define HTML_31ST    15

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
#define MINOR_5_0   (HTML_OCT + HTML_30TH)
#define MINOR_5_1   (HTML_OCT + HTML_3RD)
#define MINOR_5_2   (HTML_DEC + HTML_15TH)
#define MINOR_5_3   (HTML_OCT + HTML_19TH)
#define HTML_5_0    MAJOR_5_0, MINOR_5_0
#define HTML_5_1    MAJOR_5_1, MINOR_5_1
#define HTML_5_2    MAJOR_5_2, MINOR_5_2
#define HTML_5_3    MAJOR_5_3, MINOR_5_3

#define HTML_JAN05  HTML_2005, (HTML_JAN + HTML_31ST)
#define HTML_JUN05  HTML_2005, (HTML_JUN + HTML_31ST)
#define HTML_JUL05  HTML_2005, HTML_JUL
#define HTML_DEC05  HTML_2005, (HTML_DEC + HTML_31ST)
#define HTML_JAN06  HTML_2006, HTML_JAN
#define HTML_MAR06  HTML_2006, HTML_MAR
#define HTML_JUN06  HTML_2006, (HTML_JUN + HTML_30TH)
#define HTML_JUL06  HTML_2006, HTML_JUL
#define HTML_OCT06  HTML_2006, HTML_OCT
#define HTML_DEC06  HTML_2006, (HTML_DEC + HTML_31ST)
#define HTML_JAN07  HTML_2007, HTML_JAN
#define HTML_JUN07  HTML_2007, (HTML_JUN + HTML_31ST)
#define HTML_JUL07  HTML_2007, HTML_JUL
#define HTML_OCT07  HTML_2007, HTML_OCT
#define HTML_NOV07  HTML_2007, HTML_NOV
#define HTML_DEC07  HTML_2007, (HTML_DEC + HTML_31ST)
#define HTML_JAN08  HTML_2008, HTML_JAN
#define HTML_JUN08  HTML_2008, (HTML_JUN + HTML_30TH)
#define HTML_JUL08  HTML_2008, HTML_JUL
#define HTML_NOV08  HTML_2008, HTML_NOV
#define HTML_DEC08  HTML_2008, (HTML_DEC + HTML_31ST)
#define HTML_JAN09  HTML_2009, HTML_JAN
#define HTML_JUN09  HTML_2009, (HTML_JUN + HTML_30TH)
#define HTML_JUL09  HTML_2009, HTML_JUL
#define HTML_DEC09  HTML_2009, (HTML_DEC + HTML_31ST)
#define HTML_JAN10  HTML_2010, HTML_JAN
#define HTML_JUN10  HTML_2010, (HTML_JUN + HTML_30TH)
#define HTML_JUL10  HTML_2010, HTML_JUL
#define HTML_DEC10  HTML_2010, (HTML_DEC + HTML_31ST)
#define HTML_JAN11  HTML_2011, HTML_JAN
#define HTML_JUN11  HTML_2011, (HTML_JUN + HTML_30TH)
#define HTML_JUL11  HTML_2011, HTML_JUL
#define HTML_DEC11  HTML_2011, (HTML_DEC + HTML_31ST)
#define HTML_JAN12  HTML_2012, HTML_JAN
#define HTML_JUN12  HTML_2012, (HTML_JUN + HTML_30TH)
#define HTML_JUL12  HTML_2012, HTML_JUL
#define HTML_NOV12  HTML_2012, HTML_NOV
#define HTML_DEC12  HTML_2012, (HTML_DEC + HTML_31ST)
#define HTML_JAN13  HTML_2013, HTML_JAN
#define HTML_JUN13  HTML_2013, (HTML_JUN + HTML_30TH)
#define HTML_FEB13  HTML_2013, (HTML_FEB + HTML_28TH)
#define HTML_JUL13  HTML_2013, HTML_JUL
#define HTML_AUG13  HTML_2013, (HTML_AUG + HTML_8TH)
#define HTML_DEC13  HTML_2013, (HTML_DEC + HTML_31ST)
#define HTML_JAN14  HTML_2014, HTML_JAN
#define HTML_JUN14  HTML_2014, (HTML_JUN + HTML_30TH)
#define HTML_JUL14  HTML_2014, HTML_JUL
#define HTML_DEC14  HTML_2014, (HTML_DEC + HTML_31ST)
#define HTML_JAN15  HTML_2015, HTML_JAN
#define HTML_MAR15  HTML_2015, HTML_MAR
#define HTML_MAY15  HTML_2015, HTML_MAY
#define HTML_JUN15  HTML_2015, (HTML_JUN + HTML_30TH)
#define HTML_JUL15  HTML_2015, HTML_JUL
#define HTML_AUG15  HTML_2015, HTML_AUG
#define HTML_DEC15  HTML_2015, (HTML_DEC + HTML_31ST)
#define HTML_JAN16  HTML_2016, HTML_JAN
#define HTML_MAR16  HTML_2016, HTML_MAR
#define HTML_APR16  HTML_2016, HTML_APR
#define HTML_JUN16  HTML_2016, (HTML_JUN + HTML_30TH)
#define HTML_JUL16  HTML_2016, HTML_JUL
#define HTML_DEC16  HTML_2016, (HTML_DEC + HTML_31ST)
#define HTML_JAN17  HTML_2017, HTML_JAN
#define HTML_JUN17  HTML_2017, (HTML_JUN + HTML_30TH)
#define HTML_JUL17  HTML_2017, HTML_JUL
#define HTML_NOV17  HTML_2017, HTML_NOV
#define HTML_DEC17  HTML_2017, (HTML_DEC + HTML_31ST)
#define HTML_JAN18  HTML_2018, HTML_JAN
#define HTML_JUN18  HTML_2018, (HTML_JUN + HTML_30TH)
#define HTML_JUL18  HTML_2018, HTML_JUL
#define HTML_OCT18  HTML_2018, HTML_OCT
#define HTML_DEC18  HTML_2018, (HTML_DEC + HTML_31ST)
#define HTML_JAN19  HTML_2019, HTML_JAN
#define HTML_MAR19  HTML_2019, HTML_MAR
#define HTML_APR19  HTML_2019, HTML_APR
#define HTML_JUN19  HTML_2019, (HTML_JUN + HTML_30TH)
#define HTML_JUL19  HTML_2019, HTML_JUL
#define HTML_DEC19  HTML_2019, (HTML_DEC + HTML_31ST)
#define HTML_JAN20  HTML_2020, HTML_JAN
#define HTML_FEB20  HTML_2020, HTML_FEB
#define HTML_MAR20  HTML_2020, HTML_MAR
#define HTML_APR20  HTML_2020, HTML_APR
#define HTML_JUN20  HTML_2020, (HTML_JUN + HTML_30TH)
#define HTML_JUL20  HTML_2020, HTML_JUL
#define HTML_DEC20  HTML_2020, (HTML_DEC + HTML_31ST)
#define HTML_JAN21  HTML_2021, HTML_JAN
#define HTML_EOJ21  HTML_2021, (HTML_JAN + HTML_31ST)
#define HTML_FEB21  HTML_2021, HTML_FEB
#define HTML_MAR21  HTML_2021, (HTML_MAR + HTML_31ST)
#define HTML_APR21  HTML_2021, HTML_APR
#define HTML_JUN21  HTML_2021, (HTML_JUN + HTML_30TH)
#define HTML_JUL21  HTML_2021, HTML_JUL
#define HTML_AUG21  HTML_2021, HTML_AUG
#define HTML_SEP21  HTML_2021, HTML_SEP
#define HTML_OCT21  HTML_2021, HTML_OCT
#define HTML_NOV21  HTML_2021, HTML_NOV
#define HTML_JAN22  HTML_2022, HTML_JAN
#define HTML_APR22  HTML_2022, HTML_APR
#define HTML_JUN22  HTML_2022, (HTML_JUN + HTML_30TH)

#define HTML_5_EARLIEST_YEAR    HTML_2005
#define HTML_5_EARLIEST_MONTH   1

#define HTML_LATEST_YEAR    HTML_2022
#define HTML_LATEST_MONTH   4

#define HTML_CURRENT        HTML_APR22

#define HTML_UNDEF  0, 0

#define HTML_MATH1      HTML_4_0
#define HTML_MATH2      XHTML_1_0
#define HTML_MATH3      HTML_5_0
#define HTML_MATH4      HTML_APR21

#define HTML_RDF10      XHTML_1_0
#define HTML_RDF10_CON  HTML_JAN11
#define HTML_RDF11      HTML_JUL12
#define HTML_RDF11_1    HTML_JUL12
#define HTML_RDF11_2    HTML_JUL13
#define HTML_RDF11_3    HTML_JAN15

#define HTML_RDFA10     HTML_2008, HTML_OCT
#define HTML_RDFA11     HTML_2012, HTML_JUN
#define HTML_RDFA111    HTML_2012, HTML_JUN
#define HTML_RDFA112    HTML_2013, HTML_AUG
#define HTML_RDFA113    HTML_2015, HTML_MAR
#define HTML_RDFA       HTML_RDFA10

#define HTML_SVG10      XHTML_1_0
#define HTML_SVG11      XHTML_1_1
#define HTML_SVG12      XHTML_1_1
#define HTML_SVG20      HTML_OCT18
#define HTML_SVG21      HTML_APR21

#define HTML_OG_2010    HTML_JAN10
#define HTML_OG_2010_END HTML_DEC11
#define HTML_OG_2012    HTML_JAN12
#define HTML_OG_2014    HTML_JAN14
#define HTML_OG_2018    HTML_JAN18

#define HTML_ARTICLE    HTML_OG_2012
#define HTML_AS_1_0     HTML_RDF10_CON
#define HTML_AS_2_0     HTML_2017, HTML_MAY
#define HTML_AS         HTML_AS_1_0
#define HTML_BIBO       HTML_RDF11
#define HTML_BOOK       HTML_OG_2012
#define HTML_CC         HTML_2008, HTML_MAR
#define HTML_CONTENT    HTML_RDF10
#define HTML_CSVW       HTML_JAN16
#define HTML_CTAG       HTML_RDF10_CON
#define HTML_DAQ        HTML_RDF10_CON
#define HTML_DBD        HTML_RDF10
#define HTML_DBO        HTML_RDF10
#define HTML_DBP        HTML_RDF10
#define HTML_DBP_OWL    HTML_RDF10
#define HTML_DBR        HTML_RDF10
#define HTML_DC_1_0     XHTML_1_0
#define HTML_DC_1_1     XHTML_1_1
#define HTML_DCTERMS_1_0 XHTML_1_0
#define HTML_DCTERMS_1_1 XHTML_1_1
#define HTML_DC         HTML_DC_1_0
#define HTML_DCTERMS    HTML_DCTERMS_1_0
#define HTML_DOAP       HTML_RDF10
#define HTML_DQV        HTML_RDF10_CON
#define HTML_DESC_BY    HTML_RDF10
#define HTML_DUV        HTML_RDF10_CON
#define HTML_EARL       HTML_RDF10_CON
#define HTML_EVENT      HTML_RDF10_CON
#define HTML_FAUX       HTML_RDF10
#define HTML_FOAF       HTML_RDF10
#define HTML_FRBR       HTML_RDF10
#define HTML_GR         HTML_RDF10
#define HTML_GRDDL      HTML_RDF10_CON
#define HTML_GS10       HTML_JAN15
#define HTML_GS11       HTML_DEC16
#define HTML_GS12       HTML_DEC17
#define HTML_GS13       HTML_FEB20
#define HTML_GS14       HTML_FEB21
#define HTML_GS15       HTML_MAR21
#define HTML_GS151      HTML_SEP21
#define HTML_ICAL       HTML_RDF10_CON
#define HTML_ICALTZD    HTML_RDF10_CON
#define HTML_JSONLD_1_0 HTML_JAN14
#define HTML_JSONLD_1_1 HTML_JUL20
#define HTML_JSONLD     HTML_JSONLD_1_0
#define HTML_LDP        HTML_RDF10_CON
#define HTML_LICENCE    HTML_RDF10
#define HTML_LOCN       HTML_RDF10_CON
#define HTML_MA         HTML_RDF10_CON
#define HTML_MF         HTML_RDF10
#define HTML_MUSIC      HTML_OG_2012
#define HTML_OA         HTML_RDF10_CON
#define HTML_ODRL       HTML_RDF10
#define HTML_OG         HTML_OG_2014
#define HTML_ORG        HTML_RDF10_CON
#define HTML_OWL10      HTML_RDF10
#define HTML_OWL11      HTML_JAN07
#define HTML_OWL20      HTML_JAN13
#define HTML_OWL        HTML_OWL10
#define HTML_PROFILE    HTML_OG_2012
#define HTML_PROV       HTML_RDF10_CON
#define HTML_POETRY     HTML_JAN17
#define HTML_PTR        HTML_RDF10_CON
#define HTML_QB         HTML_RDF10_CON
#define HTML_RDFG       HTML_RDF10
#define HTML_RDFS       HTML_RDF10
#define HTML_REVIEW     HTML_RDF10
#define HTML_RIF        HTML_JAN07
#define HTML_ROLE       HTML_RDF10_CON
#define HTML_RR         HTML_RDF10_CON
#define HTML_SCHEMA_0     HTML_JUN11
#define HTML_SCHEMA_JUN11 HTML_2011, ( HTML_JUN + HTML_6TH )
#define HTML_SCHEMA_JUL11 HTML_2011, HTML_JUL
#define HTML_SCHEMA_AUG11 HTML_2011, HTML_AUG
#define HTML_SCHEMA_SEP11 HTML_2011, HTML_SEP
#define HTML_SCHEMA_OCT11 HTML_2011, HTML_OCT
#define HTML_SCHEMA_NOV11 HTML_2011, HTML_NOV
#define HTML_SCHEMA_DEC11 HTML_2011, HTML_DEC
#define HTML_SCHEMA_JAN12 HTML_2012, HTML_JAN
#define HTML_SCHEMA_FEB12 HTML_2012, HTML_FEB
#define HTML_SCHEMA_MAR12 HTML_2012, HTML_MAR
#define HTML_SCHEMA_APR12 HTML_2012, HTML_APR
#define HTML_SCHEMA_0_91  HTML_2012, ( HTML_APR + HTML_21ST )
#define HTML_SCHEMA_0_93  HTML_2012, HTML_MAY
#define HTML_SCHEMA_0_94  HTML_2012, ( HTML_MAY + HTML_17TH )
#define HTML_SCHEMA_0_95  HTML_2012, ( HTML_JUN + HTML_26TH )
#define HTML_SCHEMA_0_96  HTML_2012, ( HTML_JUL + HTML_18TH )
#define HTML_SCHEMA_0_97  HTML_2012, ( HTML_JUL + HTML_26TH )
#define HTML_SCHEMA_0_98  HTML_2012, HTML_OCT
#define HTML_SCHEMA_0_99  HTML_2012, HTML_NOV
#define HTML_SCHEMA_1_0A  HTML_2013, HTML_APR
#define HTML_SCHEMA_1_0B  HTML_2013, HTML_JUL
#define HTML_SCHEMA_1_0C  HTML_2013, HTML_AUG
#define HTML_SCHEMA_1_0D  HTML_2013, HTML_NOV
#define HTML_SCHEMA_1_0E  HTML_2013, HTML_DEC
#define HTML_SCHEMA_1_0F  HTML_2014, HTML_FEB
#define HTML_SCHEMA_1_1   HTML_2014, HTML_APR
#define HTML_SCHEMA_1_2   HTML_2014, ( HTML_APR + HTML_14TH )
#define HTML_SCHEMA_1_3   HTML_2014, HTML_MAY
#define HTML_SCHEMA_1_4   HTML_2014, ( HTML_MAY + HTML_10TH )
#define HTML_SCHEMA_1_5   HTML_2014, ( HTML_MAY + HTML_20TH )
#define HTML_SCHEMA_1_6   HTML_2014, HTML_JUN
#define HTML_SCHEMA_1_7   HTML_2014, HTML_JUL
#define HTML_SCHEMA_1_8   HTML_2014, ( HTML_JUL + HTML_28TH )
#define HTML_SCHEMA_1_9   HTML_2014, ( HTML_AUG + HTML_18TH )
#define HTML_SCHEMA_1_91  HTML_2014, HTML_SEP
#define HTML_SCHEMA_1_92  HTML_2014, HTML_DEC
#define HTML_SCHEMA_1_93  HTML_2015, HTML_FEB
#define HTML_SCHEMA_2_0   HTML_2015, HTML_MAY
#define HTML_SCHEMA_2_1   HTML_2015, HTML_AUG
#define HTML_SCHEMA_2_2   HTML_2015, HTML_NOV
#define HTML_SCHEMA_3_0   HTML_2016, HTML_MAY
#define HTML_SCHEMA_3_1   HTML_2016, HTML_AUG
#define HTML_SCHEMA_3_2   HTML_2017, HTML_MAR
#define HTML_SCHEMA_3_3   HTML_2017, HTML_AUG
#define HTML_SCHEMA_3_4   HTML_2018, HTML_JUN
#define HTML_SCHEMA_3_5   HTML_2019, HTML_APR
#define HTML_SCHEMA_3_6   HTML_2019, HTML_MAY
#define HTML_SCHEMA_3_7   HTML_2019, HTML_JUN
#define HTML_SCHEMA_3_8   HTML_2019, HTML_JUL
#define HTML_SCHEMA_3_9   HTML_2019, HTML_AUG
#define HTML_SCHEMA_4     HTML_2019, HTML_OCT
#define HTML_SCHEMA_5     HTML_2019, HTML_NOV
#define HTML_SCHEMA_6     HTML_JAN20
#define HTML_SCHEMA_7_00  HTML_2020, HTML_MAR
#define HTML_SCHEMA_7_01  HTML_2020, HTML_MAR
#define HTML_SCHEMA_7_02  HTML_2020, HTML_MAR
#define HTML_SCHEMA_7_03  HTML_2020, HTML_APR
#define HTML_SCHEMA_7_04  HTML_2020, HTML_APR
#define HTML_SCHEMA_8     HTML_2020, HTML_MAY
#define HTML_SCHEMA_9     HTML_JUL20
#define HTML_SCHEMA_10    HTML_2020, HTML_SEP
#define HTML_SCHEMA_11    HTML_DEC20
#define HTML_SCHEMA_12    HTML_MAR21
#define HTML_SCHEMA_13    HTML_JUL21
#define HTML_SCHEMA_14    HTML_APR22
#define HTML_SCHEMA       HTML_SCHEMA_0
#define HTML_SD         HTML_RDF10_CON
#define HTML_SIOC       HTML_RDF10
#define HTML_SKOS       HTML_JUN08
#define HTML_SKOSXL     HTML_JUN08
#define HTML_SSN        HTML_RDF10_CON
#define HTML_SOSA       HTML_RDF10_CON
#define HTML_TAXO       HTML_RDF10
#define HTML_TIME       HTML_RDF10_CON
#define HTML_V          HTML_RDF10_CON
#define HTML_VANN_1_0   HTML_RDF10
#define HTML_VANN_1_1   HTML_JAN06
#define HTML_VANN       HTML_VANN_1_0
#define HTML_VCARD_2001 HTML_RDF10
#define HTML_VCARD_2006 HTML_OCT06
#define HTML_VCARD_2010 HTML_JAN10
#define HTML_VCARD_2014 HTML_JUN14
#define HTML_VCARD      HTML_VCARD_2001
#define HTML_VIDEO      HTML_OG_2012
#define HTML_VOID       HTML_RDF10_CON
#define HTML_WDR        HTML_RDF10_CON
#define HTML_WDRS       HTML_RDF10_CON
#define HTML_WEBSITE    HTML_OG_2012
#define HTML_WHATWG     HTML_JAN09
#define HTML_XHV        HTML_RDF10
#define HTML_XML        HTML_RDF10
#define HTML_XSD_10     HTML_RDF10
#define HTML_XSD_11     HTML_RDF10
#define HTML_XSD        HTML_XSD_10

#define HTML_TTML       HTML_JAN14

#define HTML_XLINK10    XHTML_1_0
#define HTML_XLINK11    HTML_JUN10


class version
{   unsigned char mjr_ = 0, mnr_ = 0;
    flags_t flags_ = NOFLAGS;
public:
    version () = default;
    version (const unsigned char mjr, const unsigned char mnr, const flags_t flags = NOFLAGS) noexcept
        :   mjr_ (mjr), mnr_ (mnr), flags_ (flags) { }
	version (const version& ) = default;
	version (version&& ) = default;
	~version () = default;
    version& operator = (const version& ) = default;
	version& operator = (version&& ) = default;
    void swap (version& v) noexcept
    {   ::std::swap (mjr_, v.mjr_);
        ::std::swap (mnr_, v.mnr_);
        ::std::swap (flags_, v.flags_); }
    void reset () noexcept { version v; swap (v); }
    void reset (const version& v) noexcept { version vv (v); swap (vv); }
    void set_mjr (const unsigned char mjr, const unsigned char mnr = 0) noexcept
    {   mjr_ = mjr; mnr_ = mnr; }
    bool unknown () const noexcept { return (mjr_ == 0) && (mnr_ == 0); }
    bool known () const noexcept { return ! unknown (); }
    unsigned char mjr () const noexcept { return mjr_; }
    unsigned char mnr () const noexcept { return mnr_; }
    void set_flags (const flags_t u) noexcept { flags_ |= u; }
    void reset_flags (const flags_t u) noexcept { flags_ &= ~u; }
    bool all_flags (const flags_t u) const noexcept { return ((flags_ & u) == u); }
    bool any_flags (const flags_t u) const noexcept { return ((flags_ & u) != 0); }
    bool no_flags (const flags_t u) const noexcept { return ((flags_ & u) == 0); }
    flags_t flags () const noexcept { return flags_; }
    bool empty () const noexcept { return (mjr_ == 0) && (mnr_ == 0); }
    ::std::string name () const;
    ::std::string report () const; };

bool operator == (const version& lhs, const version& rhs) noexcept;
bool operator != (const version& lhs, const version& rhs) noexcept;
bool operator < (const version& lhs, const version& rhs) noexcept;
bool operator > (const version& lhs, const version& rhs) noexcept;
bool operator <= (const version& lhs, const version& rhs) noexcept;
bool operator >= (const version& lhs, const version& rhs) noexcept;

template < class V > inline bool does_apply (const V& v, const V& from, const V& to) MSVC_NOEXCEPT
{   if (! from.unknown () && (v < from)) return false;
    if (! to.unknown () && (v > to)) return false;
    return true; }

#ifdef _MSC_VER
#pragma warning (disable : 26440)
#pragma warning (push, 3)
#endif // _MSC_VER
template < class V > inline bool may_apply (const V& v, const V& from, const V& to)
{   return (v.unknown () || does_apply < V > (v, from, to)); }
#ifdef _MSC_VER
#pragma warning (pop)
#endif // _MSC_VER
