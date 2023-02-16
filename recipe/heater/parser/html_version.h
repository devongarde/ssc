/*
ssc (static site checker)
Copyright (c) 2020-2023 Dylan Harris
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
#include "main/version.h"
#include "feedback/nitpick.h"
#include "schema/schema_version.h"

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

#define HV_CSP_1        0x0000000000020000
#define HV_CSP_2        0x0000000000040000
#define HV_CSP_3        0x0000000000080000

#define HV_WHATWG       0x0000000000100000
#define HV_W3           0x0000000000200000

#define HV_NOTPROD      0x0000000000400000
#define HV_DEPRECATED2  0x0000000000800000
#define HV_DEPRECATED30 0x0000000001000000
#define HV_DEPRECATED32 0x0000000002000000
#define HV_DEPRECATED4  0x0000000004000000
#define HV_DEPRECATED50 0x0000000008000000
#define HV_DEPRECATED51 0x0000000010000000
#define HV_DEPRECATED52 0x0000000020000000
#define HV_DEPRECATED53 0x0000000040000000
#define HV_DEPRECATED54 0x0000000080000000
#define HV_DEPRECATEDX10 0x0000000100000000
#define HV_DEPRECATEDX11 0x0000000200000000
#define HV_DEPRECATEDX2 0x0000000400000000
#define HV_DEPRECATEDX5 0x0000000800000000


#define HV_DEPRECATED123 ( HV_DEPRECATEDX10 | HV_DEPRECATED2 | HV_DEPRECATED30 | HV_DEPRECATED32 )
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

#define HV_DEPRECATEDX1 ( HV_DEPRECATEDX10 | HV_DEPRECATEDX11 )
#define HV_DEPRECATEDX12 ( HV_DEPRECATEDX1 | HV_DEPRECATEDX2 )
#define HV_DEPRECATEDX  ( HV_DEPRECATEDX12 | HV_DEPRECATEDX5 )
#define HV_DEPRECATED5X ( HV_DEPRECATEDX | HV_DEPRECATED5 )

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

#define HV_XHTML_DTD    0x4000000000000000

#define HV_OUTOFSCOPE   0x8000000000000000

#define HV_NOT3         ( HV_NOT30 | HV_NOT32 )
#define HV_NOT234       ( HV_NOT2 | HV_NOT3 | HV_NOT32 | HV_NOT4 )
#define HV_NOT324       ( HV_NOT32 | HV_NOT4 | HV_NOTX1 )
#define HV_NOT324XX     ( HV_NOT324 | HV_NOTX2 )
#define HV_NOT4XX       ( HV_NOT4 | HV_NOTX1 | HV_NOTX2 )
#define HV_NOTXX        ( HV_NOTX1 | HV_NOTX2 )
#define HV_NOTXXX       ( HV_NOTXX | HV_NOTX5 )
#define HV_NOT5W3       ( HV_NOT50 | HV_NOT51 | HV_NOT52 | HV_NOT53 )
#define HV_NOT5123      ( HV_NOT51 | HV_NOT52 | HV_NOT53 )

#define HV_DEPRECATED_MASK 0x0000000FFF800000

#define HE_SVG_10       0x0000000000000001
#define HE_SVG_11       0x0000000000000002
#define HE_SVG_12_TINY  0x0000000000000004
#define HE_SVG_12_FULL  0x0000000000000008
#define HE_SVG_20       0x0000000000000010
#define HE_SVG_21       0x0000000000000020

#define HE_SVG_12       ( HE_SVG_12_TINY | HE_SVG_12_FULL )
#define HE_SVG_10_11    ( HE_SVG_10 | HE_SVG_11 )
#define HE_SVG_11_FULL  ( HE_SVG_11 | HE_SVG_12_FULL )
#define HE_SVG_10_11_FULL ( HE_SVG_10_11 | HE_SVG_12_FULL )
#define HE_SVG_10_12    ( HE_SVG_10 | HE_SVG_12 )
#define HE_SVG_10_20    ( HE_SVG_10 | HE_SVG_20 )
#define HE_SVG_10_2     ( HE_SVG_10_20 | HE_SVG_21 )
#define HE_SVG_10_11_20 ( HE_SVG_10_11 | HE_SVG_20 )
#define HE_SVG_10_11_2  ( HE_SVG_10_11_20 | HE_SVG_21 )
#define HE_SVG_11_12    ( HE_SVG_11 | HE_SVG_12 )
#define HE_SVG_11_20    ( HE_SVG_11 | HE_SVG_20 )
#define HE_SVG_11_2     ( HE_SVG_11_20 | HE_SVG_21 )
#define HE_SVG_11_12_20 ( HE_SVG_11_20 | HE_SVG_12 )
#define HE_SVG_11_12_2  ( HE_SVG_11_2 | HE_SVG_12 )
#define HE_SVG_12_20    ( HE_SVG_12 | HE_SVG_20 )
#define HE_SVG_12_2     ( HE_SVG_12_20 | HE_SVG_21 )
#define HE_SVG_1        ( HE_SVG_10_11 | HE_SVG_12 )
#define HE_SVG_1_20     ( HE_SVG_1 | HE_SVG_20 )
#define HE_SVG_2        ( HE_SVG_20 | HE_SVG_21 )
#define HE_SVG_10_12_2  ( HE_SVG_10_12 | HE_SVG_2 )
#define HE_SVG_FULL_2   ( HE_SVG_12_FULL | HE_SVG_2 )
#define HE_SVG          ( HE_SVG_1 | HE_SVG_2 )
#define SVG_MASK        HE_SVG

#define HE_XLINK_1_0    0x0000000000000100
#define HE_XLINK_1_1    0x0000000000000200

#define XLINK_MASK      ( HE_XLINK_1_0 | HE_XLINK_1_1 )

#define HE_RDF_DEP      0x0000000000001000
#define HE_RDF          0x0000000000002000
#define HE_RDFA         0x0000000000004000
#define RDF_MASK        ( HE_RDF_DEP | HE_RDF | HE_RDFA )

#define HE_MICRODATA    0x0000000000008000
#define HE_SVG_X2       0x0000000000010000

#define HE_SVG_OLD_H    0x0000000000020000

#define HE_ANIM_10      0x0000000000040000
#define HE_ANIM_11      0x0000000000080000
#define HE_ANIM_12      0x0000000000100000
#define HE_ANIM_20      0x0000000000200000
#define HE_ANIM_21      0x0000000000400000

#define HE_ANIM_10_11   ( HE_ANIM_10 | HE_ANIM_11 )
#define HE_ANIM_11_12   ( HE_ANIM_11 | HE_ANIM_12 )
#define HE_ANIM_1       ( HE_ANIM_10_11 | HE_ANIM_12 )
#define HE_ANIM_1_20    ( HE_ANIM_1 | HE_ANIM_20 )
#define HE_ANIM_2       ( HE_ANIM_20 | HE_ANIM_21 )
#define HE_ANIM_11_2    ( HE_ANIM_11 | HE_ANIM_2 )
#define HE_ANIM_10_11_2 ( HE_ANIM_10 | HE_ANIM_11_2 )
#define HE_ANIM_12_2    ( HE_ANIM_12 | HE_ANIM_2 )
#define HE_ANIM         ( HE_ANIM_1 | HE_ANIM_2 )

#define HE_COMBINES     0x0000000000800000
#define HE_A            0x0000000001000000
#define HE_B            0x0000000002000000
#define HE_C            0x0000000003000000
#define HE_D            0x0000000004000000
#define HE_E            0x0000000005000000
#define HE_F            0x0000000006000000
#define HE_G            0x0000000007000000

#define HE_GROUP_MASK   0x000000000F000000
#define HE_GROUP_SHIFT  24
#define HE_GROUP(XXXX)  ((flags_t) XXXX << HE_GROUP_SHIFT)

#define SVG_SHIFT       0
#define XLINK_SHIFT     8
#define RDF_SHIFT       12

#define HE_EXPERIMENTAL 0x0000000080000000

#define HE_NETSCAPE     0x0000000100000000
#define HE_IE           0x0000000200000000
#define HE_WEBCOMP      0x0000000400000000
#define HE_BESPOKE      0x0000000800000000
#define HE_MOZILLA      0x0000001000000000
#define HE_CHROME       0x0000002000000000
#define HE_OPERA        0x0000004000000000
#define HE_SAFARI       0x0000008000000000

#define HE_NOT_SVG_10   0x0000010000000000
#define HE_NOT_SVG_11   0x0000020000000000
#define HE_NOT_SVG_12   0x0000040000000000
#define HE_NOT_SVG_20   0x0000080000000000
#define HE_NOT_SVG_21   0x0000100000000000

#define HE_NOT_SVG_10_11    ( HE_NOT_SVG_10 | HE_NOT_SVG_11 )
#define HE_NOT_SVG_10_12    ( HE_NOT_SVG_10 | HE_NOT_SVG_12 )
#define HE_NOT_SVG_1        ( HE_NOT_SVG_10_11 | HE_NOT_SVG_12 )
#define HE_NOT_SVG_2        ( HE_NOT_SVG_20 | HE_NOT_SVG_21 )
#define HE_NOT_SVG_10_11_20 ( HE_NOT_SVG_10_11 | HE_NOT_SVG_2 )
#define HE_NOT_SVG_10_12_20 ( HE_NOT_SVG_10_12 | HE_NOT_SVG_2 )
#define HE_NOT_SVG          ( HE_NOT_SVG_1 | HE_NOT_SVG_2 )

#define HE_LIMITED_10   0x0000200000000000
#define HE_LIMITED_11   0x0000400000000000
#define HE_LIMITED_12   0x0000800000000000
#define HE_LIMITED_20   0x0001000000000000
#define HE_LIMITED_21   0x0002000000000000

#define HE_LIMITED_10_11 ( HE_LIMITED_10 | HE_LIMITED_11 )
#define HE_LIMITED_1    ( HE_LIMITED_10_11 | HE_LIMITED_12 )
#define HE_LIMITED_2    ( HE_LIMITED_20 | HE_LIMITED_21 )
#define HE_LIMITED_11_2 ( HE_LIMITED_11 | HE_LIMITED_2 )
#define HE_LIMITED_10_11_2 ( HE_LIMITED_10_11 | HE_LIMITED_2 )
#define HE_LIMITED      ( HE_LIMITED_1 | HE_LIMITED_2 )

#define HE_M3_NONSTAND  0x0004000000000000

#define HE_SVG_DEPR_10  0x0008000000000000
#define HE_SVG_DEPR_11  0x0010000000000000
#define HE_SVG_DEPR_12  0x0020000000000000
#define HE_SVG_DEPR_20  0x0040000000000000
#define HE_SVG_DEPR_21  0x0080000000000000

#define HE_SVG_DEPR_1   ( HE_SVG_DEPR_10 | HE_SVG_DEPR_11 | HE_SVG_DEPR_12 )
#define HE_SVG_DEPR_2   ( HE_SVG_DEPR_20 | HE_SVG_DEPR_21 )
#define HE_SVG_DEPR     ( HE_SVG_DEPR_1 | HE_SVG_DEPR_2 )

#define HE_MINARGS_MASK 0x0F00000000000000
#define HE_MINARGS_SHIFT 56
#define HE_MINARGS(XXXX) ((flags_t) XXXX << HE_MINARGS_SHIFT)
#define HE_MAXARGS_MASK 0xF000000000000000
#define HE_MAXARGS_SHIFT 60
#define HE_MAXARGS(XXXX) ((flags_t) XXXX << HE_MAXARGS_SHIFT)

#define H2_JSONLD_1_0   0x0000000000000001
#define H2_JSONLD_1_1   0x0000000000000002

#define JSONLD_MASK     ( H2_JSONLD_1_0 | H2_JSONLD_1_1 )
#define JSONLD_SHIFT    0

#define H2_MATH_1       0x0000000000000010
#define H2_MATH_2       0x0000000000000020
#define H2_MATH_3       0x0000000000000040
#define H2_MATH_4_20    0x0000000000000080
#define H2_MATH_4_22    0x0000000000000100
#define H2_MATH_C       0x0000000000000200

#define H2_MATH_4       ( H2_MATH_4_20 | H2_MATH_4_22 )

#define H2_MATH_1_2     ( H2_MATH_1 | H2_MATH_2 )
#define H2_MATH_1_2_3   ( H2_MATH_1_2 | H2_MATH_3 )
#define H2_MATH_1_2_3_4_20 ( H2_MATH_1_2_3 | H2_MATH_4_20 )
#define H2_MATH_2_3_4   ( H2_MATH_2 | H2_MATH_3 | H2_MATH_4 )
#define H2_MATH_2_3_4_C ( H2_MATH_2_3_4 | H2_MATH_C )
#define H2_MATH_3_4_20  ( H2_MATH_3 | H2_MATH_4_20 )
#define H2_MATH_3_4     ( H2_MATH_3 | H2_MATH_4 )
#define H2_MATH_3_4_C   ( H2_MATH_3_4 | H2_MATH_C )
#define H2_MATH_2_C     ( H2_MATH_2 | H2_MATH_C )
#define H2_MATH_4_22_C  ( H2_MATH_4_22 | H2_MATH_C )
#define H2_MATHML       ( H2_MATH_1_2 | H2_MATH_3_4 )
#define H2_MATH         ( H2_MATHML | H2_MATH_C )
#define MATH_MASK       H2_MATH

#define MATH_SHIFT      4

#define H2_M2_DEPRECAT  0x0000000000001000
#define H2_M3_DEPRECAT  0x0000000000002000
#define H2_M4_DEPRECAT  0x0000000000004000

#define H2_CSS_1        0x0000000000008000
#define H2_CSS_2_0      0x0000000000010000
#define H2_CSS_2_1      0x0000000000020000
#define H2_CSS_2_2      0x0000000000040000
#define H2_CSS_3        0x0000000000080000
#define H2_CSS_4        0x0000000000100000
#define H2_CSS_5        0x0000000000200000
#define H2_CSS_6        0x0000000000400000
#define H2_CSS_2_0_1    ( H2_CSS_2_0 | H2_CSS_2_1 | H2_CSS_2_2 )
#define H2_CSS_2        ( H2_CSS_2_0_1 | H2_CSS_2_2 )
#define H2_CSS_5_PLUS   ( H2_CSS_5 | H2_CSS_6 )
#define H2_CSS_4_PLUS   ( H2_CSS_4 | H2_CSS_5_PLUS )
#define H2_CSS_3_PLUS   ( H2_CSS_3 | H2_CSS_4_PLUS )
#define H2_CSS_2_PLUS   ( H2_CSS_2 | H2_CSS_3_PLUS )
#define H2_CSS_21_PLUS  ( H2_CSS_2_1 | H2_CSS_2_2 | H2_CSS_3_PLUS )
#define H2_CSS_ALL      ( H2_CSS_1 | H2_CSS_2_PLUS )
#define H2_CSS_MASK     H2_CSS_ALL
#define H2_CSS          H2_CSS_ALL

#define H2_CSS_1_ARG    0x0000000001000000
#define H2_CSS_2_ARGS   0x0000000002000000
#define H2_CSS_1_2_ARGS ( H2_CSS_1_ARG | H2_CSS_2_ARGS )
#define H2_CSS_MORE_ARGS 0x0000000008000000
#define H2_CSS_N_ARGS   ( H2_CSS_1_ARG | H2_CSS_MORE_ARGS )
#define H2_CSS_ARG_MASK 0x000000000F000000

#define H2_CSS_CASCADE_3 0x0000000010000000  
#define H2_CSS_CASCADE_4 0x0000000020000000  
#define H2_CSS_CASCADE_5 0x0000000030000000  
#define H2_CSS_CASCADE_6 0x0000000040000000  
#define H2_CSS_CASCADE_MASK 0x0000000070000000  
#define H2_CSS_CASCADE_ROTATE 32

class html_version : public version
{   flags_t ext_ = NOFLAGS, ext2_ = NOFLAGS;
    bool note_parsed_version (nitpick& nits, const e_nit n, const html_version& got, const ::std::string& gen);
    void init (const unsigned short mjr);
    bool test_extension () const noexcept;
public:
    html_version () : ext_ (NOFLAGS), ext2_ (NOFLAGS) { }
    explicit html_version (const unsigned short mjr) { init (mjr); }
    explicit html_version (const schema_version& sv) noexcept : version (sv.mjr (), sv.mnr ()), ext_ (NOFLAGS), ext2_ (NOFLAGS) { }
    html_version (const unsigned short mjr, const unsigned short mnr, const flags_t flags = NOFLAGS, const flags_t extensions = NOFLAGS, const flags_t e2 = NOFLAGS) noexcept
        : version (mjr, mnr, flags), ext_ (extensions), ext2_ (e2) { }
    html_version (const ::boost::gregorian::date& whatwg, const flags_t flags = NOFLAGS, const flags_t extensions = NOFLAGS, const flags_t e2 = NOFLAGS);
    DEFAULT_COPY_CONSTRUCTORS (html_version);
	~html_version () = default;
    void swap (html_version& v) noexcept
    {   version::swap (v);
        ::std::swap (ext_, v.ext_);
        ::std::swap (ext2_, v.ext2_); }
    void reset () noexcept { html_version v; swap (v); }
    void reset (const html_version& v) noexcept { html_version vv (v); swap (vv); }
    void set_ext (const flags_t u) noexcept { ext_ |= u; }
    void reset_ext (const flags_t u) noexcept { ext_ &= ~u; }
    bool all_ext (const flags_t u) const noexcept { return ((ext_ & u) == u); }
    bool any_ext (const flags_t u) const noexcept { return ((ext_ & u) != 0); }
    bool no_ext (const flags_t u) const noexcept { return ((ext_ & u) == 0); }
    flags_t ext () const noexcept { return ext_; }
    void set_ext2 (const flags_t u) noexcept { ext2_ |= u; }
    void set_ext2 (const flags_t m, const flags_t u) noexcept { reset_ext2 (m); set_ext2 (u); }
    void set_ext2 (const flags_t m, const flags_t u, int r) noexcept { reset_ext2 (m); set_ext2 ((u << r) & m); }
    void reset_ext2 (const flags_t u) noexcept { ext2_ &= ~u; }
    bool all_ext2 (const flags_t u) const noexcept { return ((ext2_ & u) == u); }
    bool any_ext2 (const flags_t u) const noexcept { return ((ext2_ & u) != 0); }
    bool no_ext2 (const flags_t u) const noexcept { return ((ext2_ & u) == 0); }
    flags_t ext2 () const noexcept { return ext2_; }
    flags_t ext2 (const flags_t m, int r) const noexcept { return (ext2 () & m) >> r; }
    bool is_not (const unsigned short j, const unsigned short n = USHRT_MAX) const noexcept
    {   if (unknown ()) return false;
        if (j != mjr ()) return true;
        return ((n != USHRT_MAX) && (n != mnr ())); }
    bool is_not (const html_version& v) const noexcept
    {   return is_not (v.mjr (), v.mnr ()); }
    bool any_level () const noexcept { return any_flags (HV_LEVEL_MASK); }
    unsigned short level () const noexcept { return (flags () & HV_LEVEL_MASK); }
    bool is_0 () const noexcept { return mjr () == 0; }
    bool is_1 () const noexcept { return mjr () == 1; }
    bool is_2 () const noexcept { return mjr () == 2; }
    bool is_3 () const noexcept { return mjr () == 3; }
    bool is_4 () const noexcept { return mjr () == 4; }
    bool is_5 () const noexcept { return mjr () > 4; }
    bool is_b4_1 () const noexcept { return mjr () < 1; }
    bool is_b4_2 () const noexcept { return mjr () < 2; }
    bool is_b4_3 () const noexcept { return mjr () < 3; }
    bool is_b4_4 () const noexcept { return mjr () < 4; }
    bool is_b4_5 () const noexcept { return mjr () < 5; }
    bool is_1_or_more () const noexcept { return mjr () >= 1; }
    bool is_2_or_more () const noexcept { return mjr () >= 2; }
    bool is_3_or_more () const  noexcept{ return mjr () >= 3; }
    bool is_4_or_more () const noexcept { return mjr () >= 4; }
    bool bespoke () const noexcept { return all_ext (HE_BESPOKE); }
    bool chrome () const noexcept { return all_ext (HE_CHROME); }
    bool dinosaur () const noexcept { return all_flags (HV_DINOSAUR); }
    bool experimental () const noexcept { return all_ext (HE_EXPERIMENTAL); }
    bool frameset () const noexcept { return all_flags (HV_FRAMESET); }
    bool ie () const noexcept { return all_ext (HE_IE); }
    bool has_css () const noexcept { return any_ext2 (H2_CSS_ALL); }
    bool has_jsonld () const noexcept { return any_ext2 (JSONLD_MASK); }
    bool has_math () const noexcept { return any_ext2 (MATH_MASK); }
    bool has_math_core () const noexcept { return any_ext2 (H2_MATH_C); }
    bool has_math_not_core () const noexcept { return any_ext2 (H2_MATHML) && ! has_math_core (); }
    bool has_rdfa () const noexcept { return any_ext (HE_RDFA); }
    bool has_svg () const noexcept { return any_ext (SVG_MASK); }
    bool has_xlink () const  noexcept{ return any_ext (XLINK_MASK); }
    int jsonld () const noexcept { return GSL_NARROW_CAST < int > ((ext2 () & JSONLD_MASK) >> JSONLD_SHIFT); }
    int math () const noexcept { return GSL_NARROW_CAST < int > ((ext2 () & MATH_MASK) >> MATH_SHIFT); }
    int rdfa () const noexcept { return has_rdfa (); }
    int svg () const noexcept { return GSL_NARROW_CAST < int > ((ext () & SVG_MASK) >> SVG_SHIFT); }
    ::std::size_t minargs () const noexcept { return GSL_NARROW_CAST < ::std::size_t > ((ext () & HE_MINARGS_MASK) >> HE_MINARGS_SHIFT); }
    ::std::size_t maxargs () const noexcept { return GSL_NARROW_CAST < ::std::size_t > ((ext () & HE_MAXARGS_MASK) >> HE_MAXARGS_SHIFT); }
    ::std::size_t group () const noexcept { return GSL_NARROW_CAST < ::std::size_t > ((ext () & HE_GROUP_MASK) >> HE_GROUP_SHIFT); }
    bool is_css_1 () const noexcept { return (any_ext2 (H2_CSS_1)); }
    bool is_css_2 () const noexcept { return (any_ext2 (H2_CSS_2)); }
    bool is_css_2_0 () const noexcept { return (any_ext2 (H2_CSS_2_0)); }
    bool is_css_2_1 () const noexcept { return (any_ext2 (H2_CSS_2_1)); }
    bool is_css_2_2 () const noexcept { return (any_ext2 (H2_CSS_2_2)); }
    bool is_css_3 () const noexcept { return (any_ext2 (H2_CSS_3)); }
    bool is_css_4 () const noexcept { return (any_ext2 (H2_CSS_4)); }
    bool is_css_5 () const noexcept { return (any_ext2 (H2_CSS_5)); }
    bool is_css_6 () const noexcept { return (any_ext2 (H2_CSS_6)); }
    bool is_jsonld_10 () const noexcept { return (ext2 () & H2_JSONLD_1_0) == H2_JSONLD_1_0; }
    bool is_jsonld_11 () const noexcept { return (ext2 () & H2_JSONLD_1_1) == H2_JSONLD_1_1; }
    bool is_rdf () const noexcept { return (ext () & HE_RDF) != 0; }
    bool is_rdf_dep () const noexcept { return (ext () & HE_RDF_DEP) != 0; }
    bool is_svg_1 () const noexcept { return (ext () & HE_SVG_1) != 0; }
    bool is_svg_10 () const noexcept { return (ext () & HE_SVG_10) == HE_SVG_10; }
    bool is_svg_11 () const noexcept { return (ext () & HE_SVG_11) == HE_SVG_11; }
    bool is_svg_12 () const noexcept { return (ext () & HE_SVG_12) != 0; }
    bool is_svg_2 () const noexcept { return (ext () & HE_SVG_2) != 0; }
    bool is_svg_20 () const noexcept { return (ext () & HE_SVG_20) == HE_SVG_20; }
    bool is_svg_21 () const noexcept { return (ext () & HE_SVG_21) == HE_SVG_21; }
    bool not_svg () const noexcept { return (ext () & HE_NOT_SVG) == HE_NOT_SVG; }
    bool not_any_svg () const noexcept { return (ext () & HE_NOT_SVG) != 0; }
    bool not_svg_10 () const noexcept { return (ext () & HE_NOT_SVG_10) != 0; }
    bool not_svg_11 () const noexcept { return (ext () & HE_NOT_SVG_11) != 0; }
    bool not_svg_12 () const noexcept { return (ext () & HE_NOT_SVG_12) != 0; }
    bool not_svg_20 () const noexcept { return (ext () & HE_NOT_SVG_20) != 0; }
    bool not_svg_21 () const noexcept { return (ext () & HE_NOT_SVG_21) != 0; }
    e_css_version css_version () const noexcept;
    ::std::string css_version_name () const;
    void css_version (const e_css_version v) noexcept;
    e_jsonld_version jsonld_version () const noexcept;
    void jsonld_version (const e_jsonld_version v) noexcept;
    bool math_4_core () const noexcept;
    e_math_version math_version () const noexcept;
    ::std::string math_version_name () const;
    void math_version (const e_math_version v) noexcept;
    e_rdf_version rdf_version () const noexcept;
    void rdf_version (const e_rdf_version v) noexcept;
    e_svg_version svg_version () const noexcept;
    void svg_version (const e_svg_version v) noexcept;
    bool requires_extension () const noexcept;
    bool is_plain_html () const noexcept;
    int xlink () const noexcept { return GSL_NARROW_CAST < int > ((ext () & XLINK_MASK) >> XLINK_SHIFT); }
    bool check_math_svg (nitpick& nits, const html_version& a, const ::std::string& x) const;
    bool microdata () const noexcept { return any_ext (HE_MICRODATA); }
    bool mozilla () const noexcept { return any_ext (HE_MOZILLA); }
    bool netscape () const noexcept { return any_ext (HE_NETSCAPE); }
    bool not10 () const noexcept { return all_flags (HV_NOT10); }
    bool not2 () const noexcept { return all_flags (HV_NOT2); }
    bool not2l1 () const noexcept { return all_flags (HV_NOT2L1); }
    bool not3 () const noexcept { return any_flags (HV_NOT3); }
    bool not30 () const noexcept { return all_flags (HV_NOT30); }
    bool not32 () const noexcept { return all_flags (HV_NOT32); }
    bool not4 () const noexcept { return all_flags (HV_NOT4); }
    bool notx1 () const noexcept { return all_flags (HV_NOTX1); }
    bool notx2 () const noexcept { return all_flags (HV_NOTX2); }
    bool notx5 () const noexcept { return all_flags (HV_NOTX5); }
    bool notplus () const noexcept { return all_flags (HV_NOTPLUS); }
    bool not50 () const noexcept { return all_flags (HV_NOT50); }
    bool not51 () const noexcept { return all_flags (HV_NOT51); }
    bool not52 () const noexcept { return all_flags (HV_NOT52); }
    bool not53 () const noexcept { return all_flags (HV_NOT53); }
    bool opera () const noexcept { return any_ext (HE_OPERA); }
    bool out_of_scope () const noexcept { return all_flags (HV_OUTOFSCOPE); }
    bool reject () const noexcept { return all_flags (REJECT); }
    bool required () const noexcept { return all_flags (REQUIRED); }
    bool rfc_1867 () const noexcept { return all_flags (HV_RFC_1867); }
    bool rfc_1942 () const noexcept { return all_flags (HV_RFC_1942); }
    bool rfc_1980 () const noexcept { return all_flags (HV_RFC_1980); }
    bool rfc_2070 () const noexcept { return all_flags (HV_RFC_2070); }
    bool safari () const noexcept { return any_ext (HE_SAFARI); }
    bool strict () const noexcept { return all_flags (HV_STRICT); }
    bool transitional () const noexcept { return all_flags (HV_TRANSITIONAL); }
    bool w3 () const noexcept { return all_flags (HV_W3); }
    bool webcomponents () const noexcept { return any_ext (HE_WEBCOMP); }
    bool whatwg () const noexcept { return all_flags (HV_WHATWG); }
    bool xhtml () const noexcept { return all_flags (HV_XHTML); }
    bool xhtml_dtd () const noexcept { return all_flags (HV_XHTML_DTD); }
    bool svg_anim (const e_svg_version v) const noexcept;
    bool svg_anim () const noexcept { return any_ext (HE_ANIM); }
    bool svg_anim_10 () const noexcept { return any_ext (HE_ANIM_10); }
    bool svg_anim_11 () const noexcept{ return any_ext (HE_ANIM_11); }
    bool svg_anim_12 () const noexcept { return any_ext (HE_ANIM_12); }
    bool svg_anim_20 () const noexcept { return any_ext (HE_ANIM_20); }
    bool svg_anim_21 () const noexcept { return any_ext (HE_ANIM_21); }
    bool svg_limited (const e_svg_version v) const noexcept;
    bool svg_limited () const noexcept { return any_ext (HE_LIMITED); }
    bool svg_limited_10 () const noexcept { return any_ext (HE_LIMITED_10); }
    bool svg_limited_11 () const noexcept { return any_ext (HE_LIMITED_11); }
    bool svg_limited_12 () const noexcept { return any_ext (HE_LIMITED_12); }
    bool svg_limited_20 () const noexcept { return any_ext (HE_LIMITED_20); }
    bool svg_limited_21 () const noexcept { return any_ext (HE_LIMITED_21); }
    bool svg_x2 () const noexcept { return any_ext (HE_SVG_X2); }
    bool svg_old_html () const noexcept { return any_ext (HE_SVG_OLD_H); }
    bool is_a_area () const noexcept { return all_flags (HR_A_AREA); }
    bool is_external () const noexcept { return all_flags (HR_EXTERNAL); }
    bool is_form () const noexcept { return all_flags (HR_FORM); }
    bool is_linkhead () const noexcept { return all_flags (HR_LINKHEAD); }
    bool is_linkbody () const noexcept { return all_flags (HR_LINKBODY); }
    bool is_link () const noexcept { return any_flags (HR_LINK); }
    bool is_mf () const noexcept { return any_flags (HR_MF); }
    bool is_rel () const noexcept { return any_flags (HR_ALL); }
    bool invalid_addendum (const html_version& v) const noexcept;
    bool deprecated (const html_version& current) const;
    bool not_production () const noexcept { return all_flags (HV_NOTPROD); }
    bool parse_doctype (nitpick& nits, const ::std::string& content);
    bool lazy () const noexcept;
    bool valid_charset (const ::std::string& charset) const;
    bool restricted_charset () const noexcept;
    const char *default_charset () const noexcept;
    const char *alternative_charset () const noexcept;
    int css_cascade () const;
    void css_cascade (const int n);
    ::std::string get_doctype () const;
    ::std::string name () const;
    ::std::string report () const; };

const html_version html_0 (HTML_NULL);
const html_version html_tags (HTML_TAGS);
const html_version html_1 (HTML_1_0);
const html_version html_plus (HTML_PLUS);
const html_version html_2 (HTML_2_0, 0, 0, H2_CSS_1);
const html_version html_2_level_1 (HTML_2_0, HV_LEVEL1);
const html_version html_2_level_2 (HTML_2_0, HV_LEVEL2);
const html_version html_3_0 (HTML_3_0, 0, 0, H2_CSS_1);
const html_version html_3_2 (HTML_3_2, 0, 0, H2_CSS_1);
const html_version html_4_0 (HTML_4_0, 0, 0, H2_CSS_2_0);
const html_version html_4_1 (HTML_4_01, 0, 0, H2_CSS_2_1);
const html_version xhtml_1_0 (XHTML_1_0, HV_XHTML, 0, H2_CSS_2_0);
const html_version xhtml_1_1 (XHTML_1_1, HV_XHTML, 0, H2_CSS_2_1);
const html_version xhtml_2 (XHTML_2_0, HV_XHTML, 0, H2_CSS_2_1);

const html_version html_jsonld_1_0 (HTML_JSONLD_1_0, 0, 0, H2_JSONLD_1_0);
const html_version html_jsonld_1_1 (HTML_JSONLD_1_1, 0, 0, H2_JSONLD_1_1);

const html_version html_math_1 (HTML_MATH1, 0, 0, H2_MATH_1 | H2_CSS_2_0);
const html_version xhtml_math_2 (HTML_MATH2, HV_XHTML, 0, H2_MATH_2 | H2_CSS_2_1);
const html_version html_math_3 (HTML_MATH3, 0, 0, H2_MATH_3 | H2_CSS_2_1);
const html_version html_math_4_20 (HTML_MATH4_20, 0, 0, H2_MATH_4_20 | H2_CSS_2_1);
const html_version html_math_core (HTML_MATH4_C, 0, 0, H2_MATH_C | H2_CSS_2_2);
const html_version html_math_4_22 (HTML_MATH4_22, 0, 0, H2_MATH_4_22 | H2_CSS_2_2);

const html_version xhtml_svg_1_0 (HTML_SVG10, HV_XHTML, HE_SVG_10, H2_CSS_2);
const html_version xhtml_svg_1_1 (HTML_SVG11, HV_XHTML, HE_SVG_11, H2_CSS_2_0);
const html_version xhtml_svg_1_2_tiny (HTML_SVG12, HV_XHTML, HE_SVG_12_TINY, H2_CSS_2_1);
const html_version xhtml_svg_1_2_full (HTML_SVG12, HV_XHTML, HE_SVG_12_FULL, H2_CSS_2_1);

const html_version html_svg_2_0 (HTML_SVG20, 0, HE_SVG_20, H2_CSS_2_2);
const html_version html_svg_2_1 (HTML_SVG21, 0, HE_SVG_21, H2_CSS_2_2);

const html_version html_css_1 (HTML_2_0, 0, 0, H2_CSS_1);
const html_version html_css_2_0 (HTML_3_2, 0, 0, H2_CSS_2_0);
const html_version html_css_2_1 (XHTML_1_0, 0, 0, H2_CSS_2_1);
const html_version html_css_2_2 (HTML_JUL16, 0, 0, H2_CSS_2_2);
const html_version html_css_3 (HTML_JAN15, 0, 0, H2_CSS_3);
const html_version html_css_4 (HTML_OCT17, 0, 0, H2_CSS_4);
const html_version html_css_5 (HTML_JAN22, 0, 0, H2_CSS_5);
const html_version html_css_6 (HTML_JAN22, 0, 0, H2_CSS_6);

const html_version html_css_selectors_4 (HTML_JAN21, 0, 0, H2_CSS_4);
const html_version html_css_selectors_5 (HTML_JAN22, 0, 0, H2_CSS_5);
const html_version html_css_selectors_6 (HTML_JAN22, 0, 0, H2_CSS_6);

const html_version html_as_1_0 (HTML_AS_1_0);
const html_version html_as_2_0 (HTML_AS_2_0);
const html_version html_cc (HTML_CC);
const html_version html_dc_1_0 (HTML_DC_1_0);
const html_version html_dc_1_1 (HTML_DC_1_1);
const html_version html_dcterms_1_0 (HTML_DCTERMS_1_0);
const html_version html_dcterms_1_1 (HTML_DCTERMS_1_1);
const html_version html_gs10 (HTML_GS10);
const html_version html_gs11 (HTML_GS11);
const html_version html_gs12 (HTML_GS12);
const html_version html_gs13 (HTML_GS13);
const html_version html_gs14 (HTML_GS14);
const html_version html_gs15 (HTML_GS15);
const html_version html_gs151 (HTML_GS151);
const html_version html_owl_1_0 (HTML_OWL10);
const html_version html_owl_1_1 (HTML_OWL11);
const html_version html_owl_2_0 (HTML_OWL20);
const html_version html_rdf (HTML_RDF10);
const html_version html_rdf_1_0 (HTML_RDF10);
const html_version html_rdf_1_0_con (HTML_RDF10_CON);
const html_version html_rdf_1_1 (HTML_RDF11);
const html_version html_rdf_1_1_1 (HTML_RDF11_1);
const html_version html_rdf_1_1_2 (HTML_RDF11_2);
const html_version html_rdf_1_1_3 (HTML_RDF11_3);
const html_version html_rdfa (HTML_RDFA10);
const html_version html_rdfa_1_0 (HTML_RDFA10);
const html_version html_rdfa_1_1 (HTML_RDFA11);
const html_version html_rdfa_1_1_1 (HTML_RDFA111);
const html_version html_rdfa_1_1_2 (HTML_RDFA112);
const html_version html_rdfa_1_1_3 (HTML_RDFA113);
const html_version html_rdfg (HTML_RDFG);
const html_version html_rdfs (HTML_RDFS);
const html_version html_review (HTML_REVIEW);
const html_version html_rif (HTML_RIF);
const html_version html_role (HTML_ROLE);
const html_version html_rr (HTML_RR);
const html_version html_schema_0 (HTML_SCHEMA_0);
const html_version html_schema_jun11 (HTML_SCHEMA_JUN11);
const html_version html_schema_jul11 (HTML_SCHEMA_JUL11);
const html_version html_schema_aug11 (HTML_SCHEMA_AUG11);
const html_version html_schema_sep11 (HTML_SCHEMA_SEP11);
const html_version html_schema_oct11 (HTML_SCHEMA_OCT11);
const html_version html_schema_nov11 (HTML_SCHEMA_NOV11);
const html_version html_schema_dec11 (HTML_SCHEMA_DEC11);
const html_version html_schema_jan12 (HTML_SCHEMA_JAN12);
const html_version html_schema_feb12 (HTML_SCHEMA_FEB12);
const html_version html_schema_mar12 (HTML_SCHEMA_MAR12);
const html_version html_schema_apr12 (HTML_SCHEMA_APR12);
const html_version html_schema_0_91 (HTML_SCHEMA_0_91);
const html_version html_schema_0_93 (HTML_SCHEMA_0_93);
const html_version html_schema_0_94 (HTML_SCHEMA_0_94);
const html_version html_schema_0_95 (HTML_SCHEMA_0_95);
const html_version html_schema_0_96 (HTML_SCHEMA_0_96);
const html_version html_schema_0_97 (HTML_SCHEMA_0_97);
const html_version html_schema_0_98 (HTML_SCHEMA_0_98);
const html_version html_schema_0_99 (HTML_SCHEMA_0_99);
const html_version html_schema_1_0A (HTML_SCHEMA_1_0A);
const html_version html_schema_1_0B (HTML_SCHEMA_1_0B);
const html_version html_schema_1_0C (HTML_SCHEMA_1_0C);
const html_version html_schema_1_0D (HTML_SCHEMA_1_0D);
const html_version html_schema_1_0E (HTML_SCHEMA_1_0E);
const html_version html_schema_1_0F (HTML_SCHEMA_1_0F);
const html_version html_schema_1_1 (HTML_SCHEMA_1_1);
const html_version html_schema_1_2 (HTML_SCHEMA_1_2);
const html_version html_schema_1_3 (HTML_SCHEMA_1_3);
const html_version html_schema_1_4 (HTML_SCHEMA_1_4);
const html_version html_schema_1_5 (HTML_SCHEMA_1_5);
const html_version html_schema_1_6 (HTML_SCHEMA_1_6);
const html_version html_schema_1_7 (HTML_SCHEMA_1_7);
const html_version html_schema_1_8 (HTML_SCHEMA_1_8);
const html_version html_schema_1_9 (HTML_SCHEMA_1_9);
const html_version html_schema_1_91 (HTML_SCHEMA_1_91);
const html_version html_schema_1_92 (HTML_SCHEMA_1_92);
const html_version html_schema_1_93 (HTML_SCHEMA_1_93);
const html_version html_schema_2_0 (HTML_SCHEMA_2_0);
const html_version html_schema_2_1 (HTML_SCHEMA_2_1);
const html_version html_schema_2_2 (HTML_SCHEMA_2_2);
const html_version html_schema_3_0 (HTML_SCHEMA_3_0);
const html_version html_schema_3_1 (HTML_SCHEMA_3_1);
const html_version html_schema_3_2 (HTML_SCHEMA_3_2);
const html_version html_schema_3_3 (HTML_SCHEMA_3_3);
const html_version html_schema_3_4 (HTML_SCHEMA_3_4);
const html_version html_schema_3_5 (HTML_SCHEMA_3_5);
const html_version html_schema_3_6 (HTML_SCHEMA_3_6);
const html_version html_schema_3_7 (HTML_SCHEMA_3_7);
const html_version html_schema_3_8 (HTML_SCHEMA_3_8);
const html_version html_schema_3_9 (HTML_SCHEMA_3_9);
const html_version html_schema_4 (HTML_SCHEMA_4);
const html_version html_schema_5 (HTML_SCHEMA_5);
const html_version html_schema_6 (HTML_SCHEMA_6);
const html_version html_schema_7_00 (HTML_SCHEMA_7_00);
const html_version html_schema_7_01 (HTML_SCHEMA_7_01);
const html_version html_schema_7_02 (HTML_SCHEMA_7_02);
const html_version html_schema_7_03 (HTML_SCHEMA_7_03);
const html_version html_schema_7_04 (HTML_SCHEMA_7_04);
const html_version html_schema_8 (HTML_SCHEMA_8);
const html_version html_schema_9 (HTML_SCHEMA_9);
const html_version html_schema_10 (HTML_SCHEMA_10);
const html_version html_schema_11 (HTML_SCHEMA_11);
const html_version html_schema_12 (HTML_SCHEMA_12);
const html_version html_schema_13 (HTML_SCHEMA_13);
const html_version html_schema_14 (HTML_SCHEMA_14);
const html_version html_schema_15 (HTML_SCHEMA_15);
const html_version html_sd (HTML_SD);
const html_version html_sioc (HTML_SIOC);
const html_version html_sioc_s (HTML_SIOC);
const html_version html_sioc_t (HTML_SIOC);
const html_version html_skos (HTML_SKOS);
const html_version html_skosxl (HTML_SKOSXL);
const html_version html_ssn (HTML_SKOS);
const html_version html_sosa (HTML_SKOS);
const html_version html_taxo (HTML_SKOS);
const html_version html_time (HTML_SKOS);
const html_version html_v (HTML_V);
const html_version html_vann_1_0 (HTML_VANN_1_0);
const html_version html_vann_1_1 (HTML_VANN_1_1);
const html_version html_vcard_2001 (HTML_VCARD_2001);
const html_version html_vcard_2006 (HTML_VCARD_2006);
const html_version html_vcard_2010 (HTML_VCARD_2010);
const html_version html_vcard_2014 (HTML_VCARD_2014);
const html_version html_video (HTML_VIDEO);
const html_version html_void (HTML_VOID);
const html_version html_wdr (HTML_WDR);
const html_version html_wdrs (HTML_WDRS);
const html_version html_website (HTML_WEBSITE);
const html_version html_whatwg (HTML_WHATWG);
const html_version html_xhv (HTML_XHV);
const html_version html_xml (HTML_XML);
const html_version html_xsd_1_0 (HTML_XSD_10);
const html_version html_xsd_1_1 (HTML_XSD_11);

const html_version html_ttml (HTML_TTML);
const html_version html_xlink_1_0 (HTML_XLINK10);
const html_version html_xlink_1_1 (HTML_XLINK11);

const html_version html_jan05 (HTML_JAN05, HV_WHATWG, HE_MICRODATA, H2_CSS_2_1);
const html_version html_jul05 (HTML_JUL05, HV_WHATWG, HE_MICRODATA, H2_CSS_2_1);
const html_version html_jan06 (HTML_JAN06, HV_WHATWG, HE_MICRODATA, H2_CSS_2_1);
const html_version html_jan07 (HTML_JAN07, HV_WHATWG, HE_MICRODATA, H2_CSS_2_1);
const html_version html_jul07 (HTML_JUL07, HV_WHATWG, HE_MICRODATA, H2_CSS_2_1);
const html_version html_jan08 (HTML_JAN08, HV_WHATWG, HE_MICRODATA, H2_CSS_2_1);
const html_version html_jul08 (HTML_JUL08, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_2 | H2_CSS_2_1);
const html_version html_jan09 (HTML_JAN09, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_2 | H2_CSS_2_1);
const html_version html_jul09 (HTML_JUL09, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_2 | H2_CSS_2_1);
const html_version html_jan10 (HTML_JAN10, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_2 | H2_CSS_3);
const html_version html_jul10 (HTML_JUL10, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_2 | H2_CSS_3);
const html_version html_jan12 (HTML_JAN12, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_2 | H2_CSS_3);
const html_version html_jul12 (HTML_JUL12, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_2 | H2_CSS_3);
const html_version html_jan13 (HTML_JAN13, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_2 | H2_CSS_3);
const html_version html_jul13 (HTML_JUL13, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_2 | H2_CSS_3);
const html_version html_jan14 (HTML_JAN14, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_2 | H2_CSS_3);
const html_version html_jan15 (HTML_JAN15, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_3 | H2_CSS_3);
const html_version html_jan16 (HTML_JAN16, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_3 | H2_CSS_3);
const html_version html_jul16 (HTML_JUL16, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_3 | H2_CSS_3);
const html_version html_jan17 (HTML_JAN17, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_3 | H2_CSS_3);
const html_version html_jul17 (HTML_JUL17, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_3 | H2_CSS_3);
const html_version html_jan18 (HTML_JAN18, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_3 | H2_CSS_3);
const html_version html_jul18 (HTML_OCT18, HV_WHATWG, HE_MICRODATA | HE_SVG_11, H2_MATH_3 | H2_CSS_3);
const html_version html_oct18 (HTML_JUL18, HV_WHATWG, HE_MICRODATA | HE_SVG_20, H2_MATH_3 | H2_CSS_3);
const html_version html_jan19 (HTML_JAN19, HV_WHATWG, HE_MICRODATA | HE_SVG_20, H2_MATH_3 | H2_CSS_3);
const html_version html_jul19 (HTML_JUL19, HV_WHATWG, HE_MICRODATA | HE_SVG_20, H2_MATH_3 | H2_CSS_3);
const html_version html_jul20 (HTML_JUL20, HV_WHATWG, HE_MICRODATA | HE_SVG_20, H2_MATH_3 | H2_CSS_3);
const html_version html_jan21 (HTML_JAN21, HV_WHATWG, HE_MICRODATA | HE_SVG_20, H2_MATH_3 | H2_CSS_3);
const html_version html_feb21 (HTML_FEB21, HV_WHATWG, HE_MICRODATA | HE_SVG_21, H2_MATH_3 | H2_CSS_3);
const html_version html_apr21 (HTML_APR21, HV_WHATWG, HE_MICRODATA | HE_SVG_21, H2_MATH_4_20 | H2_CSS_3);
const html_version html_jul21 (HTML_JUL21, HV_WHATWG, HE_MICRODATA | HE_SVG_21, H2_MATH_4_20 | H2_CSS_3);
const html_version html_oct21 (HTML_OCT21, HV_WHATWG, HE_MICRODATA | HE_SVG_21, H2_MATH_4_20 | H2_CSS_3);
const html_version html_jan22 (HTML_JAN22, HV_WHATWG, HE_MICRODATA | HE_SVG_21, H2_MATH_4_20 | H2_CSS_3);
const html_version html_apr22 (HTML_APR22, HV_WHATWG, HE_MICRODATA | HE_SVG_21, H2_MATH_4_20 | H2_CSS_3);
const html_version html_jul22 (HTML_JUL22, HV_WHATWG, HE_MICRODATA | HE_SVG_21, H2_MATH_C | H2_CSS_3);
const html_version html_oct22 (HTML_OCT22, HV_WHATWG, HE_MICRODATA | HE_SVG_21, H2_MATH_C | H2_CSS_3);
const html_version html_jan23 (HTML_JAN23, HV_WHATWG, HE_MICRODATA | HE_SVG_21, H2_MATH_C | H2_CSS_3);
const html_version html_5_0 (HTML_5_0, HV_W3, HE_SVG_11, H2_MATH_2 | H2_CSS_3);
const html_version html_5_1 (HTML_5_1, HV_W3, HE_SVG_11, H2_MATH_2 | H2_CSS_3);
const html_version html_5_2 (HTML_5_2, HV_W3, HE_SVG_11, H2_MATH_3 | H2_CSS_3);
const html_version html_5_3 (HTML_5_3, HV_W3, HE_SVG_11, H2_MATH_3 | H2_CSS_3);
const html_version html_current (html_oct22);
const html_version html_default (html_current);

bool does_html_apply (const html_version& v, const html_version& from, const html_version& to);
bool parse_doctype (nitpick& nits, html_version& version, const ::std::string::const_iterator b, const ::std::string::const_iterator e);
int w3_minor_5 (const html_version& v) noexcept;
int w3_5_minor (const html_version& v) noexcept;
e_emi extension_conflict (const html_version& lhs, const html_version& rhs);
const char *default_charset (const html_version& v) noexcept;
const char *alternative_charset (const html_version& v) noexcept;
html_version get_min_version (const e_svg_version e) noexcept;
html_version get_min_version (const e_math_version e) noexcept;
html_version get_min_version (const e_jsonld_version e) noexcept;
bool overlap (const html_version& lhs_from, const html_version& lhs_to, const html_version& rhs_from, const html_version& rhs_to);

template < > inline bool does_apply < html_version > (const html_version& v, const html_version& from, const html_version& to)
{   return does_html_apply (v, from, to); }
