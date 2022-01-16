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
#include "symbol/symbol.h"
#include "element/state.h"
#include "attribute/namespace.h"

#define EP_CLOSED           0x0000000000000100
#define EP_SIMPLE           0x0000000000000200 // open, but only text content
#define EP_TOP              0x0000000000000400 // cannot have parents
#define EP_IGNORE           0x0000000000000800 // ignore if found
#define EP_ONLYELEMENTS     0x0000000000001000 // no text etc. inside, only elements
#define EP_XMP              0x0000000000002000 // like XMP, content is ignored until corresponding close is encountered
#define EP_LAZY             0x0000000000004000
#define DENY                0x0000000000008000

#define EP_UNCLOSEDTAGS     0x0000000000010000
#define EP_UNCLOSED1        0x0000000000020000
#define EP_UNCLOSED1T       0x0000000000030000
#define EP_UNCLOSEDPLUS     0x0000000000040000
#define EP_UNCLOSED1TP      0x0000000000070000
#define EP_UNCLOSED2        0x0000000000080000

#define EP_UNCLOSEDSVG12    0x0000000000200000
#define EP_UNCLOSED12       0x00000000000A0000
#define EP_UNCLOSED1P2      0x00000000000E0000

#define EP_NOSPELL          0x0000000000800000

#define EP_5_DYNAMIC        0x0000000001000000
#define EP_5_REFRESHED      0x0000000002000000
#define EP_5_TRANSPARENT    0x0000000004000000
#define EP_5_WILDATTR       0x0000000008000000

#define EP_4_OPEN           0x0000000010000000
#define EP_PRE_X_OPEN       0x0000000020000000
#define EP_X2_OPEN          0x0000000040000000
#define EP_5_OPEN           0x0000000080000000

#define EP_ARGS_0           0x0000000100000000
#define EP_ARGS_1           0x0000000200000000
#define EP_ARGS_2           0x0000000400000000
#define EP_ARGS_3           0x0000000800000000
#define EP_ARGS_COUNT_MASK  0x0000000F00000000
#define EP_ARGS_MORE        0x0000001000000000

#define EP_SVG_12_TRANS     0x0000002000000000
#define EP_NO_WHINGE        0x0000004000000000
#define EP_HOLDS_ALL        0x0000008000000000

// corresponds to e_category_sought
#define EP_XLINK_TYPE_MASK  0x0000FF0000000000
#define EP_XLINK_TYPE_SHIFT 40

#define EP_SET_XLINKCAT(XXX)  ((flags_t) (XXX) << EP_XLINK_TYPE_SHIFT)
#define EP_GET_XLINKCAT(XXX)  (((XXX) & EP_XLINK_TYPE_MASK) >> EP_XLINK_TYPE_SHIFT)

// categories

#define EF_DOCUMENT         0x0000000000000001
#define EF_FAUX             0x0000000000000002
#define EF_METADATA         0x0000000000000004
#define EF_RDF              0x0000000000000008

#define EF_EMPH             0x0000000000000010
#define EF_MISC             0x0000000000000020
#define EF_TEXT             0x0000000000000040
#define EF_PARA             0x0000000000000080
#define EF_LIST             0x0000000000000100
#define EF_BLOK             0x0000000000000200
#define EF_HEAD             0x0000000000000400
#define EF_TABLE            0x0000000000000800
#define EF_MATH             0x0000000000001000
#define EF_LIT              0x0000000000002000
#define EF_LL               0x0000000000004000
#define EF_BODY             0x0000000000008000
#define EF_FONT             0x0000000000010000
#define EF_PHRASE           0x0000000000020000
#define EF_PRE              0x0000000000040000
#define EF_M_DQ             0x0000000000080000

#define EF_3_LIST           0x0000000000100000
#define EF_3_BQ             0x0000000000200000
#define EF_3_FONT           0x0000000000400000
#define EF_3_MISC           0x0000000000800000
#define EF_SPECIAL          0x0000000001000000
#define EF_3_TEXT           0x0000000002000000
#define EF_3_BLOCK          0x0000000004000000
#define EF_3_BODY           0x0000000008000000
#define EF_3_MATHVC         0x0000000010000000
#define EF_32_FONT          0x0000000020000000
#define EF_32_FORM          0x0000000040000000
#define EF_32_BLOCK         0x0000000080000000
#define EF_4_BLOCK          0x0000000100000000
#define EF_4_FORM           0x0000000200000000
#define EF_4_SPECIAL        0x0000000400000000
#define EF_4_PHRASE         0x0000000800000000
#define EF_4_FONT           0x0000001000000000

#define EF_S_G              0x0000002000000000
#define EF_SVG_ANIM         0x0000004000000000
#define EF_SVG_DESC         0x0000008000000000
#define EF_SVG_SHAPE        0x0000010000000000
#define EF_SVG_STR          0x0000020000000000
#define EF_SVG_PSGRAD       0x0000040000000000
#define EF_SVG_GRAPH        0x0000080000000000
#define EF_SVG_FILTER       0x0000100000000000
#define EF_SVG_CONTAIN      0x0000200000000000
#define EF_SVG_TEXT         0x0000400000000000
#define EF_SVG2_GRAPH       0x0000800000000000

#define EF_M_PRESINCONTENT  0x0001000000000000
#define EF_M_CONTENT        0x0002000000000000
#define EF_M_CONTINPRES     0x0004000000000000
#define EF_M_PRES           0x0008000000000000

#define EF_X2_STRUCT        0x0010000000000000
#define EF_X2_TEXT          0x0020000000000000
#define EF_X2_LIST          0x0040000000000000
#define EF_5_SCRIPT         0x0080000000000000
#define EF_5_PALPABLE       0x0100000000000000
#define EF_5_FLOW           0x0200000000000000
#define EF_5_PHRASE         0x0400000000000000
#define EF_5_INTERACTIVE    0x0800000000000000
#define EF_5_EMBEDDED       0x1000000000000000
#define EF_5_SECTION        0x2000000000000000
#define EF_5_FORM           0x4000000000000000

#define EF_CUSTOM           0xFFF0FFFFFFFFFFF4

#define EF_3_NOTMATH        ( EF_3_FONT | EF_PHRASE | EF_SPECIAL | EF_3_MISC )
#define EF_3_TEXTIN         ( EF_3_TEXT | EF_3_NOTMATH )
#define EF_3_BLK            ( EF_3_LIST | EF_3_BQ | EF_3_BLOCK )
#define EF_3_FLOW           ( EF_3_TEXTIN | EF_3_BLK )
#define EF_3_BODYIN         ( EF_HEAD | EF_3_FLOW | EF_3_BODY )
#define EF_3_MATHIN         ( EF_3_MATHVC | EF_MATH )

#define EF_32_TEXTIN        ( EF_32_FONT | EF_PHRASE | EF_SPECIAL | EF_32_FORM )
#define EF_32_FLOW          ( EF_32_TEXTIN | EF_32_BLOCK | EF_LIST )
#define EF_32_BODY          ( EF_32_FLOW | EF_HEAD )

#define EF_4_INLINE         ( EF_4_FORM | EF_4_SPECIAL | EF_4_PHRASE | EF_4_FONT )
#define EF_4_FLOW           ( EF_4_INLINE | EF_4_BLOCK )

#define EF_X_MATH           ( EF_M_PRESINCONTENT | EF_M_CONTENT | EF_M_CONTINPRES | EF_M_PRES )
#define EF_M_CONTENTEXPR    ( EF_M_PRESINCONTENT | EF_M_CONTENT )
#define EF_M_PRESEXPR       ( EF_M_PRESINCONTENT | EF_M_CONTINPRES | EF_M_PRES )
#define EF_M_MATH           ( EF_M_PRESINCONTENT | EF_M_CONTINPRES )

#define EF_SVG_CATMASK      ( EF_SVG_ANIM | EF_SVG_DESC | EF_SVG_SHAPE | EF_SVG_STR | EF_SVG_PSGRAD | EF_SVG_GRAPH | EF_SVG_FILTER | EF_SVG_CONTAIN | EF_SVG_TEXT )

#define EF_X2_FLOW          ( EF_X2_STRUCT | EF_HEAD | EF_X2_TEXT )
#define EF_X2_FLOWLIST      ( EF_X2_FLOW | EF_X2_LIST )

class elem : public symbol < html_version, e_element >
{   static element_bitset ignored_;
    bool under_parse (nitpick& nits, const html_version& v, const ::std::string& el, const ident_t n);
    bool parse (nitpick& nits, const html_version& v, const namespaces_ptr& namespaces, const ::std::string& x);
public:
    elem () noexcept {}
    elem (const html_version& v, const ::std::string& x) : symbol < html_version, e_element > (v, x) { }
    elem (const elem& e) = default;
    explicit elem (const e_element e) : symbol < html_version, e_element > (e) { }
    elem (nitpick& nits, const html_version& v, const namespaces_ptr& namespaces, const ::std::string& x);
    static void init (nitpick& nits);
    static void ignore (const e_element e) { ignored_.set (e); }
    static bool ignored (const e_element e) { return ignored_.test (e); }
    bool is_unclosed (const html_version& v) const noexcept;
    bool is_closed (const html_version& v) const noexcept;
    bool is_math () const noexcept
    {   return ((categories () & (EF_MATH | EF_X_MATH)) != 0); }
    bool is_svg () const noexcept
    {   return ((categories () & EF_SVG_CATMASK) != 0); }
    bool is_transparent (const html_version& v) const noexcept;
    void swap (elem& e) noexcept
    {   symbol < html_version, e_element > :: swap (e); }
    void reset () noexcept
    {   elem e; swap (e); }
    void reset (const elem& e) noexcept
    {   elem tmp (e); swap (tmp); }
    void reset (const html_version& v, const ::std::string& s)
    {   elem tmp (v, s); swap (tmp); }
    void reset (nitpick& nits, const html_version& v, const namespaces_ptr& namespaces, const ::std::string& x)
    {   elem tmp (nits, v, namespaces, x);
        swap (tmp); }
    void reset (const e_element e)
    {   elem tmp (e);
        swap (tmp); }
    bool is_lazy (const html_version& v) const noexcept;
    bool is_dynamic () const noexcept
    {   return ((flags () & EP_5_DYNAMIC) == EP_5_DYNAMIC); }
    bool refreshed () const noexcept
    {   return ((flags () & EP_5_REFRESHED) == EP_5_REFRESHED); }
    void note_refreshed () noexcept
    {   refresh (EP_5_REFRESHED); }
    bool wild_attributes (const html_version& v) const noexcept
    {   return (v.is_5 () && ((flags () & EP_5_WILDATTR) == EP_5_WILDATTR)); }
    static e_sought_category link_category_sought (const e_element e)
    {   return static_cast < e_sought_category > (EP_GET_XLINKCAT (flags (e))); }
    e_sought_category link_category_sought () const noexcept
    {   return static_cast < e_sought_category > (EP_GET_XLINKCAT (flags ())); }
    static bool fits_link_category (const html_version& v, const e_element e, const e_sought_category cat);
    bool fits_link_category (const html_version& v, const e_sought_category cat) const
    {   return fits_link_category (v, get (), cat); }
    bool unknown () const noexcept
    {   return (symbol < html_version, e_element > :: unknown ()) || (symbol < html_version, e_element > :: get () == elem_undefined); } };

inline bool operator == (const elem& lhs, const elem& rhs) noexcept { return lhs.get () == rhs.get (); }
inline bool operator != (const elem& lhs, const elem& rhs) noexcept { return lhs.get () != rhs.get (); }
inline bool operator < (const elem& lhs, const elem& rhs) noexcept { return lhs.get () < rhs.get (); }
inline bool operator <= (const elem& lhs, const elem& rhs) noexcept { return lhs.get () <= rhs.get (); }
inline bool operator > (const elem& lhs, const elem& rhs) noexcept { return lhs.get () > rhs.get (); }
inline bool operator >= (const elem& lhs, const elem& rhs) noexcept { return lhs.get () >= rhs.get (); }

constexpr inline bool is_faux_element (const e_element e) noexcept { return (e >= elem_faux_document) && (e <= elem_faux_whitespace); }
constexpr inline bool is_custom_element (const e_element e) noexcept { return (e == elem_custom); }
constexpr inline bool is_error_element (const e_element e) noexcept { return (e == elem_error); }
constexpr inline bool is_undefined_element (const e_element e) noexcept { return (e == elem_undefined); }
constexpr inline bool is_standard_element (const e_element e) noexcept { return (e >= elem_custom) && (e < elem_error); }

void add_elements (const vstr_t& v);
