/*
ssc (static site checker)
File Info
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
#include "main/context.h"

struct symbol_entry < html_version, e_sgml > doctype_symbol_table [] =
{   { { HTML_UNDEF }, { HTML_UNDEF },  "html", doc_html },
    { { HTML_UNDEF }, { HTML_UNDEF },  "htmlplus", doc_htmlplus },
    { { HTML_UNDEF }, { HTML_UNDEF },  "math", doc_math },
    { { HTML_UNDEF }, { HTML_UNDEF },  "rdfa", doc_rdf },
    { { HTML_UNDEF }, { HTML_UNDEF },  "public", doc_public },
    { { HTML_UNDEF }, { HTML_UNDEF },  "system", doc_system },
    { { HTML_UNDEF }, { HTML_UNDEF },  "svg", doc_svg },
    { { HTML_PLUS }, { HTML_UNDEF },  "[", doc_sqopen },
    { { HTML_PLUS }, { HTML_UNDEF },  "]", doc_sqclose },

    // https://html.spec.whatwg.org/dev/syntax.html
    { { HTML_JAN05 }, { HTML_UNDEF }, "-//WHATWG//NONSGML HTML5//EN", doc_jan05 },
    { { HTML_5_0 }, { HTML_UNDEF },   "about:legacy-compat", doc_html5 },

    // https://www.w3.org/QA/2002/04/valid-dtd-list.html
    { { HTML_4_01 }, { HTML_UNDEF },  "-//W3C//DTD HTML 4.01//EN", doc_html401_strict },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/html4/strict.dtd", doc_html401_strict_superseded },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/html4/strict.dtd", doc_html401_strict_superseded },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/html40/strict.dtd", doc_html401_strict },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/html40/strict.dtd", doc_html401_strict },
    { { HTML_4_01 }, { HTML_UNDEF },  "-//W3C//DTD HTML 4.01 Transitional//EN", doc_html401_loose },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/html4/loose.dtd", doc_html401_loose_superseded, },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/html4/loose.dtd", doc_html401_loose_superseded },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/html40/loose.dtd", doc_html401_loose },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/html40/loose.dtd", doc_html401_loose },
    { { HTML_4_01 }, { HTML_UNDEF },  "-//W3C//DTD HTML 4.01 Frameset//EN", doc_html401_frameset },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/html4/frameset.dtd", doc_html401_frameset_superseded },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/html4/frameset.dtd", doc_html401_frameset_superseded },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/html40/frameset.dtd", doc_html401_frameset },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/html40/frameset.dtd", doc_html401_frameset },

    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/1999/PR-html40-19990824/strict.dtd", doc_html401_strict },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/1999/PR-html40-19990824/loose.dtd", doc_html401_loose },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/1999/PR-html40-19990824/frameset.dtd", doc_html401_frameset },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/1999/PR-html40-19990824/strict.dtd", doc_html401_strict },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/1999/PR-html40-19990824/loose.dtd", doc_html401_loose },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/1999/PR-html40-19990824/frameset.dtd", doc_html401_frameset },

    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/html40/HTMLlat1.ent", doc_latin },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/html40/HTMLspecial.ent", doc_special },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTP_W3 "/TR/html40/HTMLsymbol.ent", doc_symbols },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/html40/HTMLlat1.ent", doc_latin },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/html40/HTMLspecial.ent", doc_special },
    { { HTML_4_01 }, { HTML_UNDEF },  HTTPS_W3 "/TR/html40/HTMLsymbol.ent", doc_symbols },

    { { HTML_4_0 }, { HTML_UNDEF },  "-//W3C//DTD HTML 4.0//EN", doc_html400_strict },
    { { HTML_4_0 }, { HTML_UNDEF },  HTTP_W3 "/TR/REC-html40/strict.dtd", doc_html400_strict },
    { { HTML_4_0 }, { HTML_UNDEF },  HTTPS_W3 "/TR/REC-html40/strict.dtd", doc_html400_strict },
    { { HTML_4_0 }, { HTML_UNDEF },  "-//W3C//DTD HTML 4.0 Transitional//EN", doc_html400_loose },
    { { HTML_4_0 }, { HTML_UNDEF },  HTTP_W3 "/TR/REC-html40/loose.dtd", doc_html400_loose },
    { { HTML_4_0 }, { HTML_UNDEF },  HTTPS_W3 "/TR/REC-html40/loose.dtd", doc_html400_loose },
    { { HTML_4_0 }, { HTML_UNDEF },  "-//W3C//DTD HTML 4.0 Frameset//EN", doc_html400_frameset },
    { { HTML_4_0 }, { HTML_UNDEF },  HTTP_W3 "/TR/REC-html40/frameset.dtd", doc_html400_frameset },
    { { HTML_4_0 }, { HTML_UNDEF },  HTTPS_W3 "/TR/REC-html40/frameset.dtd", doc_html400_frameset },

    { { HTML_4_0 }, { HTML_UNDEF },  "-//W3C//ENTITIES Latin1//EN//HTML", doc_latin },
    { { HTML_4_0 }, { HTML_UNDEF },  "-//W3C//ENTITIES Special//EN//HTML", doc_special },
    { { HTML_4_0 }, { HTML_UNDEF },  "-//W3C//ENTITIES Symbols//EN//HTML", doc_symbols },

    { { HTML_3_2 }, { HTML_UNDEF },  "-//W3C//DTD HTML 3.2 Draft//EN", doc_html32 },
    { { HTML_3_2 }, { HTML_UNDEF },  "-//W3C//DTD HTML 3.2 Final//EN", doc_html32 },
    { { HTML_3_2 }, { HTML_UNDEF },  "-//W3C//DTD HTML 3.2//EN", doc_html32 },

    { { HTML_3_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML 3.0//EN", doc_html30 },
    { { HTML_3_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML 3.0//EN//", doc_html30 },

    { { HTML_4_0 }, { HTML_UNDEF },  "ISO 8879-1986//ENTITIES Added Latin 1//EN//HTML", doc_latin },

    { { HTML_1_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML//EN", doc_html1 }, // https://www.w3.org/MarkUp/html-spec/html.dtd

    { { HTML_PLUS }, { HTML_UNDEF }, "-//Internet/RFC xxxx//EN", doc_htmlplus },
    { { HTML_PLUS }, { HTML_UNDEF }, "HTMLPLUS.DTD", doc_htmlplus },

    { { HTML_2_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML 2.0//EN", doc_html20 },
    { { HTML_2_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML Strict//EN", doc_html20_strict },
    { { HTML_2_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML 2.0 Strict//EN", doc_html20_strict },
    { { HTML_2_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML Level 1//EN", doc_html21 },
    { { HTML_2_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML 2.0 Level 1//EN", doc_html21 },
    { { HTML_2_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML Strict Level 1//EN", doc_html21_strict },
    { { HTML_2_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML 2.0 Strict Level 1//EN", doc_html21_strict },
    { { HTML_2_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML Level 2//EN", doc_html22 },
    { { HTML_2_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML 2.0 Level 2//EN", doc_html22 },
    { { HTML_2_0 }, { HTML_UNDEF },  "-//IETF//DTD HTML i18n//EN", doc_html20_int },

    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF }, "-//W3C//DTD XHTML Basic 1.0//EN", doc_xhtml10_basic },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/TR/xhtml-basic/xhtml-basic10.dtd", doc_xhtml10_basic },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/TR/xhtml-basic/xhtml-basic10.dtd", doc_xhtml10_basic },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  "-//W3C//DTD XHTML 1.0 Strict//EN", doc_xhtml10_strict },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/TR/xhtml1/DTD/xhtml1-strict.dtd", doc_xhtml10_strict },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/TR/xhtml1/DTD/xhtml1-strict.dtd", doc_xhtml10_strict },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/TR/xhtml1/DTD/strict.dtd", doc_xhtml10_strict_superseded },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/TR/xhtml1/DTD/strict.dtd", doc_xhtml10_strict_superseded },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  "-//W3C//DTD XHTML 1.0 Transitional//EN", doc_xhtml10_loose },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/TR/xhtml1/DTD/xhtml1-loose.dtd", doc_xhtml10_loose },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/TR/xhtml1/DTD/xhtml1-loose.dtd", doc_xhtml10_loose },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/TR/xhtml1/DTD/xhtml1-transitional.dtd", doc_xhtml10_loose_superseded },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/TR/xhtml1/DTD/xhtml1-transitional.dtd", doc_xhtml10_loose_superseded },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/TR/xhtml1/DTD/transitional.dtd", doc_xhtml10_loose_superseded },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/TR/xhtml1/DTD/transitional.dtd", doc_xhtml10_loose_superseded },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  "-//W3C//DTD XHTML 1.0 Frameset//EN", doc_xhtml10_frameset },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/TR/xhtml1/DTD/xhtml1-frameset.dtd", doc_xhtml10_frameset },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/TR/xhtml1/DTD/xhtml1-frameset.dtd", doc_xhtml10_frameset },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/TR/xhtml1/DTD/frameset.dtd", doc_xhtml10_frameset_superseded },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/TR/xhtml1/DTD/frameset.dtd", doc_xhtml10_frameset_superseded },
    { { XHTML_1_0, HV_XHTML }, { HTML_UNDEF }, "-//WAPFORUM//DTD XHTML Mobile 1.0//EN", doc_xhtml10_mobile },

    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//DTD XHTML 1.1//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/TR/xhtml11/DTD/xhtml11.dtd", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/TR/xhtml11/DTD/xhtml11.dtd", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML BDO Element 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Base Architecture 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Base Element 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Basic Forms 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Basic Tables 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Block Phrasal 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Block Presentation 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Block Structural 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Character Entities 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Client-side Image Maps 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Common Attributes 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Datatypes 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Document Structure 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Editing Markup 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Embedded Object 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Frames 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Forms 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Hypertext 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Images 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Inline Frame Element 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Inline Phrasal 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Inline Presentation 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Inline Structural 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Inline Style 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Intrinsic Events 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Legacy Markup 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Legacy Redeclarations 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Link Element 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Lists 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ELEMENTS XHTML Java Applets 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Metainformation  1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Modular Framework 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Name Identifier 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Notations 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Param Element 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Presentation 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Qualified Names 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Scripting  1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Server-side Image Maps 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Style Sheets 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Tables 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Target 1.0//EN", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  "-//W3C//ENTITIES XHTML Text 1.0//EN", doc_xhtml11 },

    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-arch-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-arch-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-applet-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-applet-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-base-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-base-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-basic-form-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-basic-form-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-basic-table-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-basic-table-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-bdo-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-bdo-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-blkphras-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-blkphras-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-blkpres-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-blkpres-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-blkstruct-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-blkstruct-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-charent-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-charent-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-csismap-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-csismap-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-datatypes-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-datatypes-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-edit-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-edit-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-events-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-events-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-form-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-form-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-frames-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-frames-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-framework-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-framework-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-hypertext-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-hypertext-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-image-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-image-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-iframe-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-iframe-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-inlphras-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-inlphras-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-inlpres-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-inlpres-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-inlstruct-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-inlstruct-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-inlstyle-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-inlstyle-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-legacy-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-legacy-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-legacy-redecl-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-legacy-redecl-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-link-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-link-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-list-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-list-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-meta-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-meta-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-nameident-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-nameident-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-notations-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-notations-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-object-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-object-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-param-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-param-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-pres-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-pres-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-qname-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-qname-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-script-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-script-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-ssismap-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-ssismap-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-struct-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-struct-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-style-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-style-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-table-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-table-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-target-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-target-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml-text-1.mod", doc_xhtml11 },
    { { XHTML_1_1, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml-text-1.mod", doc_xhtml11 },

    { { XHTML_2_0, HV_XHTML }, { HTML_UNDEF },  "-//W3C//DTD XHTML 2.0//EN", doc_xhtml2 },
    { { XHTML_2_0, HV_XHTML }, { HTML_UNDEF },  HTTP_W3 "/MarkUp/DTD/xhtml2.dtd", doc_xhtml2 },
    { { XHTML_2_0, HV_XHTML }, { HTML_UNDEF },  HTTPS_W3 "/MarkUp/DTD/xhtml2.dtd", doc_xhtml2 },

    { { HTML_MATH4_20, 0, 0, H2_MATH_4 }, { HTML_UNDEF }, "-//W3C//DTD MathML 4.0//EN", doc_math4 },
    { { HTML_MATH4_20, 0, 0, H2_MATH_4 }, { HTML_UNDEF }, "-//W3C//ENTITIES MathML 4.0 Qualified Names 1.0//EN", doc_math4 },
    { { HTML_MATH3, 0, 0, H2_MATH_3 }, { HTML_UNDEF }, "-//W3C//DTD MathML 3.0//EN", doc_math3 },
    { { HTML_MATH3, 0, 0, H2_MATH_3 }, { HTML_UNDEF }, "-//W3C//ENTITIES MathML 3.0 Qualified Names 1.0//EN", doc_math3 },
    { { HTML_MATH3, 0, 0, H2_MATH_3 }, { HTML_UNDEF }, "-//W3C//ENTITIES HTML MathML Set//EN//XML", doc_math3 },
    { { HTML_MATH2, 0, 0, H2_MATH_2 }, { HTML_UNDEF }, "-//W3C//DTD MathML 2.0//EN", doc_math2 },
    { { HTML_MATH2, 0, 0, H2_MATH_2 }, { HTML_UNDEF }, HTTP_W3 "/Math/DTD/mathml2/mathml2.dtd", doc_math2 },
    { { HTML_MATH2, 0, 0, H2_MATH_2 }, { HTML_UNDEF }, HTTPS_W3 "/Math/DTD/mathml2/mathml2.dtd", doc_math2 },
    { { HTML_MATH1, 0, 0, H2_MATH_1 }, { HTML_UNDEF }, HTTP_W3 "/Math/DTD/mathml1/mathml.dtd", doc_math1 },
    { { HTML_MATH1, 0, 0, H2_MATH_1 }, { HTML_UNDEF }, HTTPS_W3 "/Math/DTD/mathml1/mathml.dtd", doc_math1 },
    { { HTML_MATH1, 0, 0, H2_MATH_1 }, { HTML_UNDEF }, HTTP_W3 "/TR/REC-MathML-19980407", doc_math1 },
    { { HTML_MATH1, 0, 0, H2_MATH_1 }, { HTML_UNDEF }, HTTPS_W3 "/TR/REC-MathML-19980407", doc_math1 },

    { { XHTML_1_0, 0, HE_RDF }, { HTML_UNDEF }, "-//W3C//DTD XHTML+RDFa 1.0//EN", doc_rdfa_1_0 },
    { { XHTML_1_0, 0, HE_RDF }, { HTML_UNDEF }, HTTP_W3 "/MarkUp/DTD/xhtml-rdfa-1.dtd", doc_rdfa_1_0 },
    { { XHTML_1_0, 0, HE_RDF }, { HTML_UNDEF }, HTTPS_W3 "/MarkUp/DTD/xhtml-rdfa-1.dtd", doc_rdfa_1_0 },
    { { XHTML_1_1, 0, HE_RDF }, { HTML_UNDEF }, "-//W3C//DTD XHTML+RDFa 1.1//EN", doc_rdfa_1_1 },
    { { XHTML_1_1, 0, HE_RDF }, { HTML_UNDEF }, HTTP_W3 "/MarkUp/DTD/xhtml-rdfa-2.dtd", doc_rdfa_1_1 },
    { { XHTML_1_1, 0, HE_RDF }, { HTML_UNDEF }, HTTPS_W3 "/MarkUp/DTD/xhtml-rdfa-2.dtd", doc_rdfa_1_1 },

    { { XHTML_1_1, 0, 0, H2_MATH_2 }, { HTML_UNDEF }, "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN", doc_compound_m },
    { { XHTML_1_1, 0, HE_SVG_10, H2_MATH_2 }, { HTML_UNDEF }, "-//W3C//DTD XHTML 1.1 plus MathML 2.0 plus SVG 1.0//EN", doc_compound_1_0 },
    { { XHTML_1_1, 0, HE_SVG_11, H2_MATH_2 }, { HTML_UNDEF }, HTTP_W3 "/2002/04/xhtml-math-svg/xhtml-math-svg.dtd", doc_compound_1_1 },
    { { XHTML_1_1, 0, HE_SVG_11, H2_MATH_2 }, { HTML_UNDEF }, HTTPS_W3 "/2002/04/xhtml-math-svg/xhtml-math-svg.dtd", doc_compound_1_1 },

    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, "-//W3C//DTD SVG 20010904//EN", doc_svg10 },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, "-//W3C//DTD SVG 1.1//EN", doc_svg11 },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/1.1/DTD/svg11.dtd", doc_svg11 },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTPS_W3 "/Graphics/SVG/1.1/DTD/svg11.dtd", doc_svg11 },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, "-//W3C//DTD SVG 1.0//EN", doc_svg10 },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, HTTP_W3 "/TR/2001/REC-SVG-20010904/DTD/svg10.dtd", doc_svg10 },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, HTTPS_W3 "/TR/2001/REC-SVG-20010904/DTD/svg10.dtd", doc_svg10 },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, "-//W3C//DTD SVG July 1999//EN", doc_svg10 },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/svg-19990706.dtd", doc_svg10 },
    { { HTML_SVG10, 0, HE_SVG_10 }, { HTML_UNDEF }, HTTPS_W3 "/Graphics/SVG/svg-19990706.dtd", doc_svg10 },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, "-//W3C//DTD SVG 1.1 Basic//EN", doc_svg11 },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/1.1/DTD/svg11-basic.dtd", doc_svg11 },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTPS_W3 "/Graphics/SVG/1.1/DTD/svg11-basic.dtd", doc_svg11 },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, "-//W3C//DTD SVG 1.1 Tiny//EN", doc_svg11 },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTP_W3 "/Graphics/SVG/1.1/DTD/svg11-tiny.dtd", doc_svg11 },
    { { HTML_SVG11, 0, HE_SVG_11 }, { HTML_UNDEF }, HTTPS_W3 "/Graphics/SVG/1.1/DTD/svg11-tiny.dtd", doc_svg11 } };

void sgml_init (nitpick& nits)
{   type_master < t_sgml > :: init (nits, doctype_symbol_table, sizeof (doctype_symbol_table) / sizeof (symbol_entry < html_version, e_sgml >)); }
