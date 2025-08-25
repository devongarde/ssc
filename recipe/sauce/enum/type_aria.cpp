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

#define ARIA_WITH_HREF          0x0000000000000001
#define ARIA_WITHOUT_HREF       0x0000000000000002
#define ARIA_NO_DISABLED        0x0000000000000004
#define ARIA_NO_CAPTION         0x0000000000000008
#define ARIA_FUSINESS           0x0000000000000010
#define ARIA_NAMED              0x0000000000000040
#define ARIA_GOOD_ALT           0x0000000000000080
#define ARIA_EMPTY_ALT          0x0000000000000100
#define ARIA_NO_ALT             0x0000000000000200
#define ARIA_HAS_LIST           0x0000000000000400
#define ARIA_MULTIPLE_SIZE      0x0000000000000800
#define ARIA_NO_MULTIPLE_SIZE   0x0000000000001000
#define ARIA_IF_TABLE_GRID      0x0000000000002000
#define ARIA_NOT_TABLE_GRID     0x0000000000004000
#define ARIA_NO_MULTISELECT     0x0000000000008000
#define ARIA_SVG                0x0000000000010000

struct symbol_entry < html_version, e_aria_role > role_symbol_table [] =
{   { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "alert", role_alert, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "alertdialog", role_alertdialogue, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "application", role_application, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "article", role_article, ns_default, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "banner", role_banner, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "blockquote", role_blockquote, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "button", role_button, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "caption", role_caption, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "cell", role_cell, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "checkbox", role_checkbox, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "code", role_code, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "columnheader", role_columnheader },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "combobox", role_combobox, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "command", role_command },
    { { HTML_ARIA_1_3, HV_ARIA }, { HTML_UNDEF }, "comment", role_comment },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "complementary", role_complementary, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "composite", role_complementary },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "contentinfo", role_contentinfo, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "definition", role_definition, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "deletion", role_deletion, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "dialog", role_dialogue, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA | HV_DEPRECATED54 }, { HTML_ARIA_1_1 }, "directory", role_directory, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-abstract", role_doc_abstract },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-acknowledgments", role_doc_acknowledgments },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-afterword", role_doc_afterword },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-appendix", role_doc_appendix },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-backlink", role_doc_backlink, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_ARIA_DP_1_0 }, "doc-biblioentry", role_doc_biblioentry },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-bibliography", role_doc_bibliography },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-biblioref", role_doc_biblioref, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-chapter", role_doc_chapter },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-colophon", role_doc_colophon },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-conclusion", role_doc_conclusion },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-cover", role_doc_cover, ns_default, EF_5_FLOW, EF_5_PHRASE },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-credit", role_doc_credit },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-credits", role_doc_credits },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-dedication", role_doc_dedication },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_ARIA_DP_1_0 }, "doc-endnote", role_doc_endnote, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-endnotes", role_doc_endnotes },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-epigraph", role_doc_epigraph },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-epilogue", role_doc_epilogue },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-errata", role_doc_errata },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-example", role_doc_example, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-footnote", role_doc_footnote },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-foreword", role_doc_foreword },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-glossary", role_doc_glossary },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-glossref", role_doc_glossref, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-index", role_doc_index, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-introduction", role_doc_introduction },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-noteref", role_doc_noteref, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-notice", role_doc_notice, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-pagebreak", role_doc_pagebreak, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_DP_1_1, HV_ARIA }, { HTML_UNDEF }, "doc-pagefooter", role_doc_pagefooter },
    { { HTML_ARIA_DP_1_1, HV_ARIA }, { HTML_UNDEF }, "doc-pageheader", role_doc_pageheader },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-pagelist", role_doc_pagelist, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-part", role_doc_part },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-preface", role_doc_preface },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-prologue", role_doc_prologue },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-pullquote", role_doc_pullquote },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-qna", role_doc_qna },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-subtitle", role_doc_subtitle },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-tip", role_doc_tip, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_DP_1_0, HV_ARIA }, { HTML_UNDEF }, "doc-toc", role_doc_toc, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "document", role_document, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "emphasis", role_emphasis, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "feed", role_feed, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "figure", role_figure, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "form", role_form, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "generic", role_generic, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_GRAPH, HV_ARIA }, { HTML_UNDEF }, "graphics-document", role_graphics_document, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_GRAPH, HV_ARIA }, { HTML_UNDEF }, "graphics-object", role_graphics_object, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_GRAPH, HV_ARIA }, { HTML_UNDEF }, "graphics-symbol", role_graphics_symbol, ns_default, EF_5_FLOW, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "grid", role_grid },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "gridcell", role_gridcell, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "group", role_group, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "heading", role_heading, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "img", role_img, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_3, HV_ARIA }, { HTML_UNDEF }, "image", role_image, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "input", role_input },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "insertion", role_insertion, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "landmark", role_landmark },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "link", role_link, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "list", role_list },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "listbox", role_listbox },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "listitem", role_listitem, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "log", role_log, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "main", role_main, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_3, HV_ARIA }, { HTML_UNDEF }, "mark", role_mark },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "marquee", role_marquee, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "math", role_math, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "menu", role_menu },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "menubar", role_menubar },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "menuitem", role_menuitem, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "menuitemcheckbox", role_menuitemcheckbox, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "menuitemradio", role_menuitemradio, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "meter", role_meter, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "navigation", role_navigation, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "none", role_none },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "note", role_note, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "option", role_option, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "paragraph", role_paragraph, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "presentation", role_presentation },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "progressbar", role_progressbar, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "radio", role_radio, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "radiogroup", role_radiogroup, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "range", role_range },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "region", role_region, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "roletype", role_roletype },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "row", role_row },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "rowgroup", role_rowgroup },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "rowheader", role_rowheader },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "scrollbar", role_scrollbar, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "search", role_search, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "searchbox", role_searchbox, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "section", role_section },
    { { HTML_ARIA_1_3, HV_ARIA }, { HTML_UNDEF }, "sectionfooter", role_sectionfooter },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "sectionhead", role_sectionhead },
    { { HTML_ARIA_1_3, HV_ARIA }, { HTML_UNDEF }, "sectionheader", role_sectionheader },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "select", role_select },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "separator", role_separator, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "slider", role_slider, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "spinbutton", role_spinbutton, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "status", role_status, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "strong", role_strong, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "structure", role_structure },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "subscript", role_subscript, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "superscript", role_superscript, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "switch", role_switch, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "tab", role_tab, ns_default, EF_5_INTERACTIVE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "table", role_table },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "tablist", role_tablist },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "tabpanel", role_tabpanel, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "term", role_term, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "textbox", role_textbox, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_2, HV_ARIA }, { HTML_UNDEF }, "time", role_time, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "timer", role_timer, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "toolbar", role_toolbar, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "tooltip", role_tooltip, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "tree", role_tree, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "treegrid", role_treegrid, ns_default, EF_5_FLOW, EF_5_FLOW },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "treeitem", role_treeitem, ns_default, EF_5_PHRASE, EF_5_PHRASE },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "widget", role_widget },
    { { HTML_ARIA_1_0, HV_ARIA }, { HTML_UNDEF }, "window", role_window } };

struct elem_role {
    html_version from_, to_;
    e_element elem_;
    e_aria_role role_;
    flags_t flags_ = 0;
    elem_role (const html_version& from, const html_version& to, const e_element elem, const e_aria_role role, const flags_t flags = 0) noexcept
        : from_ (from), to_ (to), elem_ (elem), role_ (role), flags_ (flags) { } };

struct role_key {
    e_element elem_;
    e_aria_role role_;
    role_key (const e_element elem, const e_aria_role role) noexcept
        : elem_ (elem), role_ (role) { } };

elem_role default_role [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, elem_a, role_link, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_5_2 }, { HTML_5_2 }, elem_address, role_group },
    { { HTML_JAN05 }, { HTML_5_3 }, elem_area, role_link, ARIA_WITH_HREF },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_article, role_article },
    { { HTML_JUL05 }, { HTML_UNDEF }, elem_aside, role_complementary },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_blockquote, role_blockquote },
    { { HTML_JAN05 }, { HTML_JAN25 }, elem_body, role_document },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_button, role_button },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_caption, role_caption },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_circle, role_graphics_symbol },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_code, role_code },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_datalist, role_listbox },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_dd, role_definition },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_del, role_deletion },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_details, role_group },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_dfn, role_term },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_dialogue, role_dialogue },
    { { HTML_5_1 }, { HTML_5_2 }, elem_dl, role_list },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_dt, role_term },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_ellipse, role_graphics_symbol },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_em, role_emphasis },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_fieldset, role_group },
    { { HTML_5_2 }, { HTML_5_3 }, elem_figure, role_figure },
    { { HTML_JAN05 }, { HTML_MAR21 }, elem_footer, role_contentinfo },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_footer, role_contentinfo, ARIA_FUSINESS },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_foreignobject, role_group },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_form, role_form, ARIA_NAMED },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_g, role_group },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h1, role_heading },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h2, role_heading },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h3, role_heading },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h4, role_heading },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h5, role_heading },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h6, role_heading },
    { { HTML_JAN05 }, { HTML_MAR21 }, elem_header, role_banner },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_header, role_banner, ARIA_FUSINESS },
    { { HTML_JAN25 }, { HTML_UNDEF }, elem_hgroup, role_group },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_hr, role_separator },
    { { HTML_JAN25 }, { HTML_UNDEF }, elem_html, role_document },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_image, role_img },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_image, role_image },
    { { HTML_JAN05 }, { HTML_JUN05 }, elem_img, role_presentation },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_img, role_img, ARIA_GOOD_ALT | ARIA_NO_ALT },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_img, role_image, ARIA_GOOD_ALT | ARIA_NO_ALT },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_ins, role_insertion },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_li, role_listitem },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_line, role_graphics_symbol },
    { { HTML_JAN05 }, { HTML_MAR21 }, elem_link, role_link },
    { { HTML_JUL13 }, { HTML_5_3 }, elem_main, role_main },
    { { HTML_JAN05 }, { HTML_MAR21 }, elem_map, role_link },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_math, role_math },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_menu, role_list },
    { { HTML_JAN13 }, { HTML_JUN17 }, elem_menuitem, role_menuitem },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_meter, role_meter },
    { { HTML_JUL05 }, { HTML_UNDEF }, elem_nav, role_navigation },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ol, role_list },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_optgroup, role_group },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_option, role_option, ARIA_HAS_LIST },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_output, role_status },
    { { HTML_JAN25 }, { HTML_UNDEF }, elem_p, role_paragraph },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_path, role_graphics_symbol },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_polygon, role_graphics_symbol },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_polyline, role_graphics_symbol },
    { { HTML_JAN10 }, { HTML_UNDEF }, elem_progress, role_progressbar },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_rect, role_graphics_symbol },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_s, role_deletion },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_region, ARIA_NAMED },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_select, role_listbox }, // ARIA_MULTIPLE_SIZE
    { { HTML_APR21 }, { HTML_UNDEF }, elem_select, role_listbox, ARIA_MULTIPLE_SIZE | ARIA_NO_MULTISELECT },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_select, role_combobox, ARIA_NO_MULTISELECT },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_strong, role_strong },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_sub, role_subscript },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_summary, role_button },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_sup, role_superscript },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_svg, role_graphics_document },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_symbol, role_graphics_object },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_table, role_table },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_tbody, role_rowgroup },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_td, role_gridcell, ARIA_IF_TABLE_GRID },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_td, role_cell },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_text, role_group },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_textarea, role_textbox },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_textpath, role_group },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_tfoot, role_rowgroup },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_th, role_columnheader },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_th, role_rowheader },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_th, role_gridcell, ARIA_IF_TABLE_GRID },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_th, role_cell },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_thead, role_rowgroup },
    { { HTML_ARIA_1_2 }, { HTML_UNDEF }, elem_time, role_time },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_tr, role_row },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_tspan, role_group },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ul, role_list },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_use, role_graphics_object },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, role_any } };

elem_role permitted_role [] =
{   { { HTML_JAN05 }, { HTML_UNDEF }, elem_a, role_button, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_a, role_checkbox, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_a, role_doc_backlink, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_a, role_doc_biblioref, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_a, role_doc_glossref, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_a, role_doc_noteref, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_a, role_menuitem },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_a, role_menuitem, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_a, role_menuitemcheckbox },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_a, role_menuitemcheckbox, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_a, role_menuitemradio },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_a, role_menuitemradio, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_a, role_option, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_a, role_radio, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_a, role_switch, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_a, role_tab, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_a, role_treeitem, ARIA_WITH_HREF | ARIA_NO_DISABLED },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_a, role_any, ARIA_WITHOUT_HREF },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_a, role_any, ARIA_SVG },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_abbr, role_any },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_address, role_contentinfo },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_address, role_any },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_area, role_any, ARIA_WITHOUT_HREF },
    { { HTML_JUL09 }, { HTML_5_3 }, elem_article, role_application },
    { { HTML_JUL09 }, { HTML_5_3 }, elem_article, role_document },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_article, role_feed },
    { { HTML_JUL09 }, { HTML_5_3 }, elem_article, role_main },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_article, role_none },
    { { HTML_JUL09 }, { HTML_MAR21 }, elem_article, role_note },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_article, role_presentation },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_article, role_region },
    { { HTML_JUL09 }, { HTML_MAR21 }, elem_article, role_search },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_aside, role_feed },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_aside, role_none },
    { { HTML_JUL05 }, { HTML_UNDEF }, elem_aside, role_note },
    { { HTML_JUL05 }, { HTML_UNDEF }, elem_aside, role_presentation },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_aside, role_region },
    { { HTML_JUL05 }, { HTML_UNDEF }, elem_aside, role_search },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_aside, role_doc_dedication },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_aside, role_doc_example },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_aside, role_doc_footnote },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_aside, role_doc_glossary },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_aside, role_doc_pullquote },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_aside, role_doc_tip },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_audio, role_application },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_b, role_any },
    { { HTML_JAN11 }, { HTML_UNDEF }, elem_bdi, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_bdo, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_blockquote, role_any },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_body, role_application },
    { { HTML_JAN05 }, { HTML_MAR21 }, elem_br, role_any },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_br, role_presentation },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_button, role_checkbox },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_button, role_combobox },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_button, role_gridcell },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_button, role_link },
    { { HTML_JAN05 }, { HTML_JUN17 }, elem_button, role_menuitem },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_button, role_menuitem },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_button, role_menuitemcheckbox },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_button, role_menuitemcheckbox },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_button, role_menuitemradio },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_button, role_menuitemradio },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_button, role_option },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_button, role_radio },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_button, role_separator },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_button, role_slider },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_button, role_switch },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_button, role_tab },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_button, role_treeitem },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_canvas, role_any },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_caption, role_any },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_circle, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_cite, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_code, role_any },
    { { HTML_JAN12 }, { HTML_UNDEF }, elem_data, role_any },
    { { HTML_JAN05 }, { HTML_JAN05 }, elem_dd, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_del, role_any },
    { { HTML_5_1 }, { HTML_5_1 }, elem_details, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_dfn, role_any },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_dialogue, role_alertdialogue },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_div, role_any },
    { { HTML_JAN05 }, { HTML_JAN05 }, elem_dl, role_any },
    { { HTML_5_1 }, { HTML_5_1 }, elem_dl, role_directory},
    { { HTML_5_1 }, { HTML_UNDEF }, elem_dl, role_group },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_dl, role_list },
    { { HTML_5_1 }, { HTML_5_1 }, elem_dl, role_listbox },
    { { HTML_5_1 }, { HTML_5_1 }, elem_dl, role_menu },
    { { HTML_5_1 }, { HTML_5_1 }, elem_dl, role_menubar },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_dl, role_none },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_dl, role_presentation },
    { { HTML_5_1 }, { HTML_5_1 }, elem_dl, role_radiogroup },
    { { HTML_5_1 }, { HTML_5_1 }, elem_dl, role_tablist },
    { { HTML_5_1 }, { HTML_5_1 }, elem_dl, role_toolbar },
    { { HTML_5_1 }, { HTML_5_1 }, elem_dl, role_tree },
    { { HTML_JAN05 }, { HTML_JAN05 }, elem_dt, role_any },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_dt, role_listitem },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_ellipse, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_em, role_any },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, role_application },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, role_document },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, role_img },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_embed, role_image },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_embed, role_none },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_embed, role_presentation },
    { { HTML_AUG25 }, { HTML_UNDEF }, elem_fencedframe, role_application },
    { { HTML_AUG25 }, { HTML_UNDEF }, elem_fencedframe, role_document },
    { { HTML_AUG25 }, { HTML_UNDEF }, elem_fencedframe, role_img },
    { { HTML_AUG25 }, { HTML_UNDEF }, elem_fencedframe, role_image },
    { { HTML_AUG25 }, { HTML_UNDEF }, elem_fencedframe, role_none },
    { { HTML_AUG25 }, { HTML_JUN05 }, elem_fencedframe, role_presentation },
    { { HTML_AUG25 }, { HTML_UNDEF }, elem_fencedframe, role_presentation },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_fieldset, role_none },
    { { HTML_JAN09 }, { HTML_UNDEF }, elem_fieldset, role_presentation },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_fieldset, role_radiogroup },
    { { HTML_JUL10 }, { HTML_5_1 }, elem_figcaption, role_any },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_figcaption, role_group },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_figcaption, role_none },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_figcaption, role_presentation },
    { { HTML_JAN07 }, { HTML_5_1 }, elem_figure, role_any },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_figure, role_any, ARIA_NO_CAPTION },
    { { HTML_5_2 }, { HTML_5_3 }, elem_figure, role_group },
    { { HTML_5_3 }, { HTML_5_3 }, elem_figure, role_none },
    { { HTML_5_2 }, { HTML_5_3 }, elem_figure, role_presentation },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_footer, role_doc_footnote },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_footer, role_group },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_footer, role_none },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_footer, role_presentation },
    { { HTML_JUL20 }, { HTML_MAR21 }, elem_footer, role_any },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_foreignobject, role_any },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_form, role_search },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_form, role_none },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_form, role_presentation },
    { { HTML_JAN05 }, { HTML_MAR21 }, elem_form, role_any },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_g, role_any },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_h1, role_none },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h1, role_presentation },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h1, role_tab },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_h1, role_doc_subtitle },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_h2, role_none },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h2, role_presentation },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h2, role_tab },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_h2, role_doc_subtitle },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_h3, role_none },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h3, role_presentation },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h3, role_tab },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_h3, role_doc_subtitle },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_h4, role_none },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h4, role_presentation },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h4, role_tab },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_h4, role_doc_subtitle },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_h5, role_none },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h5, role_presentation },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h5, role_tab },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_h5, role_doc_subtitle },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_h6, role_none },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h6, role_presentation },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_h6, role_tab },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_h6, role_doc_subtitle },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_header, role_group },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_header, role_none },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_header, role_presentation },
    { { HTML_JUL09 }, { HTML_UNDEF }, elem_hgroup, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_hr, role_presentation },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_hr, role_none },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_hr, role_doc_pagebreak },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_i, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_iframe, role_application },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_iframe, role_document },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_iframe, role_img },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_iframe, role_image },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_iframe, role_none },
    { { HTML_JAN05 }, { HTML_JUN05 }, elem_iframe, role_presentation },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_iframe, role_presentation },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_image, role_any },
    { { HTML_JAN05 }, { HTML_5_3 }, elem_img, role_any },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_button, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_checkbox, ARIA_GOOD_ALT },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_h6, role_doc_cover },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_link, ARIA_GOOD_ALT },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_img, role_math, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_menuitem, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_menuitemcheckbox, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_menuitemradio, ARIA_GOOD_ALT },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_img, role_meter, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_option, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_progressbar, ARIA_GOOD_ALT },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_img, role_radio, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_scrollbar, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_separator, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_slider, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_switch, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_tab, ARIA_GOOD_ALT },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_img, role_treeitem, ARIA_GOOD_ALT },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_button },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_checkbox },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_combobox },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_input, role_gridcell },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_link },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_menuitem },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_menuitemcheckbox },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_menuitemradio },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_input, role_option },
    { { HTML_JUL20 }, { HTML_JAN25 }, elem_input, role_none },
    { { HTML_JUL20 }, { HTML_JAN25 }, elem_input, role_presentation },
    { { HTML_JUL20 }, { HTML_JAN25 }, elem_input, role_progressbar },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_radio },
    { { HTML_JUL20 }, { HTML_JAN25 }, elem_input, role_scrollbar },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_input, role_searchbox },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_input, role_separator },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_slider },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_spinbutton },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_input, role_switch },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_input, role_tab },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_input, role_textbox },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_input, role_treeitem },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ins, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_kbd, role_any },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_legend, role_any },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_li, role_any },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_li, role_menuitem },
    { { HTML_5_3 }, { HTML_JAN25 }, elem_li, role_menuitem },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_li, role_menuitemcheckbox },
    { { HTML_5_3 }, { HTML_JAN25 }, elem_li, role_menuitemcheckbox },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_li, role_menuitemradio },
    { { HTML_5_3 }, { HTML_JAN25 }, elem_li, role_menuitemradio },
    { { HTML_JAN05 }, { HTML_JAN25 }, elem_li, role_option },
    { { HTML_5_3 }, { HTML_JAN25 }, elem_li, role_none },
    { { HTML_JAN05 }, { HTML_JAN25 }, elem_li, role_presentation },
    { { HTML_5_1 }, { HTML_JAN25 }, elem_li, role_radio },
    { { HTML_5_1 }, { HTML_JAN25 }, elem_li, role_separator },
    { { HTML_JAN05 }, { HTML_JAN25 }, elem_li, role_tab },
    { { HTML_JAN05 }, { HTML_JAN25 }, elem_li, role_treeitem },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_line, role_any },
    { { HTML_JUL13 }, { HTML_5_2 }, elem_main, role_presentation },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_mark, role_any },
    { { HTML_5_1 }, { HTML_JAN25 }, elem_menu, role_directory },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_menu, role_group },
    { { HTML_5_1 }, { HTML_JAN25 }, elem_menu, role_list },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_menu, role_listbox },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_menu, role_menu },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_menu, role_menubar },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_menu, role_none },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_menu, role_presentation },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_menu, role_radiogroup },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_menu, role_tablist },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_menu, role_tabpanel },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_menu, role_toolbar },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_menu, role_tree },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_nav, role_doc_index },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_nav, role_doc_pagelist },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_nav, role_doc_toc },
    { { HTML_JUL05 }, { HTML_5_1 }, elem_nav, role_presentation },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_nav, role_menu},
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_nav, role_menubar },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_nav, role_none },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_nav, role_presentation },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_nav, role_tablist },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_object, role_application },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_object, role_document },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_object, role_image },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_object, role_img },
    { { HTML_JAN05 }, { HTML_5_2 }, elem_object, role_presentation },
    { { HTML_JAN05 }, { HTML_JAN25 }, elem_ol, role_directory },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_ol, role_group },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ol, role_listbox },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_ol, role_menu },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_ol, role_menu },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ol, role_menubar },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_ol, role_none },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ol, role_presentation },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_ol, role_radiogroup },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ol, role_tablist },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ol, role_toolbar },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ol, role_tree },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_option, role_menuitem },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_option, role_menuitemradio },
    { { HTML_JAN05 }, { HTML_5_2 }, elem_option, role_separator },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_output, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_p, role_any },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_path, role_any },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_polygon, role_any },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_polyline, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_pre, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_q, role_any },
    { { HTML_JAN05 }, { HTML_MAR21 }, elem_rb, role_any },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_rect, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_rp, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_rt, role_any },
    { { HTML_JAN05 }, { HTML_MAR21 }, elem_rtc, role_any },
    { { HTML_JUL08 }, { HTML_UNDEF }, elem_ruby, role_any },
    { { HTML_JAN11 }, { HTML_UNDEF }, elem_s, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_samp, role_any },
    { { HTML_APR23 }, { HTML_JAN25 }, elem_search, role_any },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_search, role_form },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_search, role_group },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_search, role_none },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_search, role_presentation },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_search, role_region },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_alert },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_alertdialogue },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_application },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_section, role_banner },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_section, role_complementary },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_contentinfo },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_abstract },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_acknowledgments },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_afterword },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_appendix },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_bibliography },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_chapter },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_colophon },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_conclusion },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_credit },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_credits },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_dedication },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_endnotes },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_epigraph },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_epilogue },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_errata },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_example },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_foreword },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_glossary },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_index },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_introduction },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_notice },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_pagelist },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_part },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_preface },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_prologue },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_pullquote },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_qna },
    { { HTML_ARIA_DP_1_0 }, { HTML_UNDEF }, elem_section, role_doc_toc },  
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_dialogue },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_document },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_section, role_feed },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_section, role_group },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_log },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_main },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_marquee },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_section, role_navigation },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_section, role_none },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_section, role_note },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_presentation },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_search },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_section, role_status },
    { { HTML_5_2 }, { HTML_UNDEF }, elem_section, role_tabpanel },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_select, role_menu },
    { { HTML_5_3 }, { HTML_MAR21 }, elem_select, role_menu },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_select, role_menu, ARIA_NO_MULTIPLE_SIZE },
    { { HTML_AUG25 }, { HTML_UNDEF }, elem_selectedcontent, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_small, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_span, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_strong, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_sub, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_sup, role_any },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_summary, role_any },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_svg, role_any },
    { { HTML_JAN19 }, { HTML_JAN25 }, elem_symbol, role_any },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_table, role_any },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_tbody, role_any },
    { { HTML_JAN07 }, { HTML_MAR21 }, elem_td, role_any },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_td, role_any, ARIA_NOT_TABLE_GRID },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_text, role_any },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_textpath, role_any },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_tfoot, role_any },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_thead, role_any },
    { { HTML_JAN07 }, { HTML_MAR21 }, elem_th, role_any },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_th, role_any, ARIA_NOT_TABLE_GRID },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_think, role_any },
    { { HTML_JAN07 }, { HTML_UNDEF }, elem_time, role_any },
    { { HTML_JAN07 }, { HTML_MAR21 }, elem_tr, role_any },
    { { HTML_APR21 }, { HTML_UNDEF }, elem_tr, role_any, ARIA_NOT_TABLE_GRID },
    { { HTML_JAN19 }, { HTML_JAN25 }, elem_tspan, role_any },
    { { HTML_JUL11 }, { HTML_UNDEF }, elem_u, role_any },
    { { HTML_JAN05 }, { HTML_JAN25 }, elem_ul, role_directory },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_ul, role_group },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ul, role_listbox },
    { { HTML_JAN05 }, { HTML_5_1 }, elem_ul, role_menu },
    { { HTML_5_3 }, { HTML_UNDEF }, elem_ul, role_menu },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ul, role_menubar },
    { { HTML_JUL20 }, { HTML_UNDEF }, elem_ul, role_none },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ul, role_presentation },
    { { HTML_5_1 }, { HTML_UNDEF }, elem_ul, role_radiogroup },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ul, role_tablist },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ul, role_toolbar },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_ul, role_tree },
    { { HTML_JAN19 }, { HTML_UNDEF }, elem_use, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_var, role_any },
    { { HTML_JAN05 }, { HTML_UNDEF }, elem_video, role_application },
    { { HTML_JUL06 }, { HTML_JAN25 }, elem_wbr, role_any },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_wbr, role_none },
    { { HTML_ARIA_1_3 }, { HTML_UNDEF }, elem_wbr, role_presentation },
    { { HTML_UNDEF }, { HTML_UNDEF }, elem_undefined, role_any } };

struct required_owner_t
{   html_version from_, to_;
    e_aria_role role_, child_;
    required_owner_t (const html_version& from, const html_version& to, const e_aria_role role, const e_aria_role child) noexcept
        : from_ (from), to_ (to), role_ (role), child_ (child) { } };

required_owner_t required_owner [] =
{   { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_grid, role_row },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_grid, role_rowgroup },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_list, role_listitem },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_listbox, role_group },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_listbox, role_option },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_menu, role_group },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_menu, role_menuitem },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_menu, role_menuitemcheckbox },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_menu, role_menuitemradio },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_row, role_cell },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_row, role_columnheader },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_row, role_gridcell },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_row, role_rowheader },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_rowgroup, role_row },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_table, role_row },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_table, role_rowgroup },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_tablist, role_tab },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_tree, role_group },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_tree, role_treeitem },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_treeitem, role_row },
    { { HTML_ARIA_HTML }, { HTML_UNDEF }, role_treeitem, role_rowgroup },
    { { HTML_UNDEF }, { HTML_UNDEF }, role_any, role_any } };

bool operator == (const role_key& lhs, const role_key& rhs) noexcept
{   return (lhs.elem_ == rhs.elem_) && (lhs.role_ == rhs.role_); }

bool operator != (const role_key& lhs, const role_key& rhs) noexcept
{   return ! (lhs == rhs); }

bool operator < (const role_key& lhs, const role_key& rhs) noexcept
{   if (lhs.elem_ < rhs.elem_) return true;
    if (lhs.elem_ > rhs.elem_) return false;
    return (lhs.role_ < rhs.role_); }

bool operator >= (const role_key& lhs, const role_key& rhs) noexcept
{   return ! (lhs < rhs); }

bool operator <= (const role_key& lhs, const role_key& rhs) noexcept
{   return (lhs < rhs) || (lhs == rhs); }

bool operator > (const role_key& lhs, const role_key& rhs) noexcept
{   return ! (lhs <= rhs); }

typedef ::std::multimap < role_key, elem_role > rolemap;
typedef rolemap::value_type rmv;
typedef rolemap::const_iterator rmi;
rolemap default_roles, permitted_roles;

typedef ::std::vector < ::std::size_t > reqmap_t;
reqmap_t furq;

const role_bitset empty_role_bitset;
role_bitset abstract_role_bitset = empty_role_bitset;
role_bitset any_none_bitset = empty_role_bitset;
role_bitset application_role_bitset = empty_role_bitset;
role_bitset adii_role_bitset = empty_role_bitset;
role_bitset adiinp_role_bitset = empty_role_bitset;
role_bitset glnp_role_bitset = empty_role_bitset;
role_bitset gnp_role_bitset = empty_role_bitset;
role_bitset listitem_role_bitset = empty_role_bitset;
role_bitset no_form_role_bitset = empty_role_bitset;
role_bitset no_hf_role_bitset = empty_role_bitset;
role_bitset no_main_role_bitset = empty_role_bitset;
role_bitset no_meter_role_bitset = empty_role_bitset;
role_bitset no_progress_role_bitset = empty_role_bitset;
role_bitset no_table_role_bitset = empty_role_bitset;
role_bitset no_tabindex_role_bitset = empty_role_bitset;
role_bitset none_pres_role_bitset = empty_role_bitset;

void aria_init ()
{   abstract_role_bitset = empty_role_bitset | role_comment | role_composite | role_input | role_landmark | role_range | role_roletype |
                            role_section | role_sectionhead | role_select | role_structure| role_widget | role_window;
    any_none_bitset = empty_role_bitset | role_any | role_none;
    application_role_bitset = empty_role_bitset | role_application;
    adii_role_bitset = empty_role_bitset | role_application | role_document | role_img | role_image;
    adiinp_role_bitset = empty_role_bitset | role_application | role_document | role_img | role_image | role_none | role_presentation;
    glnp_role_bitset = empty_role_bitset | role_group | role_list | role_none | role_presentation;
    gnp_role_bitset = empty_role_bitset | role_group | role_none | role_presentation;
    listitem_role_bitset = empty_role_bitset | role_listitem;
    no_form_role_bitset = empty_role_bitset | role_form;
    no_hf_role_bitset = empty_role_bitset | role_banner | role_columnheader | role_contentinfo;
    no_main_role_bitset = empty_role_bitset | role_alert | role_banner | role_blockquote | role_caption | role_cell | role_columnheader |
                            role_combobox | role_complementary | role_contentinfo | role_directory | role_feed | role_figure | role_gridcell | role_listitem |
                            role_main | role_marquee | role_navigation | role_note | role_region | role_rowheader | role_search |
                            role_searchbox | role_spinbutton | role_status | role_textbox | role_timer | role_toolbar;
    no_meter_role_bitset = empty_role_bitset | role_meter;
    no_progress_role_bitset = empty_role_bitset | role_progressbar;
    no_table_role_bitset = empty_role_bitset | role_caption;
    no_tabindex_role_bitset = empty_role_bitset | role_button | role_checkbox | role_link | role_menuitem | role_menuitemcheckbox | role_menuitemradio |
                            role_option | role_radio | role_switch | role_tab;
    none_pres_role_bitset = empty_role_bitset | role_none | role_presentation; }

::std::string rpt_role_bitset (const role_bitset& rb)
{   ::std::string res;
    for (::std::size_t x = 0; x < rb.size (); ++x)
        if (rb.test (x))
        {   if (! res.empty ()) res += ", ";
            res += enum_n < t_role, e_aria_role > :: name (static_cast < e_aria_role > (x)); }
    return res; }

void role_init (nitpick& nits)
{   type_master < t_role > :: init (nits, role_symbol_table, sizeof (role_symbol_table) / sizeof (symbol_entry < html_version, e_aria_role >));
    for (::std::size_t i = 0; GSL_AT (default_role, i).elem_ != elem_undefined; ++i)
        default_roles.insert (rmv (role_key (GSL_AT (default_role, i).elem_, GSL_AT (default_role, i).role_), GSL_AT (default_role, i)));
    for (::std::size_t i = 0; GSL_AT (permitted_role, i).elem_ != elem_undefined; ++i)
        permitted_roles.insert (rmv (role_key (GSL_AT (permitted_role, i).elem_, GSL_AT (permitted_role, i).role_), GSL_AT (permitted_role, i)));
    furq.resize (last_role);
    for (::std::size_t i = 0; GSL_AT (required_owner, i).role_ != role_any; ++i)
    {   const e_aria_role r = GSL_AT (required_owner, i).role_;
        if (GSL_AT (furq, r) == 0) GSL_AT (furq, r) = i; } }

bool is_role_lookup (const rolemap& rm, const html_version& v, const e_element elem, const e_aria_role role, flags_t* flags = nullptr)
{   for (   rmi i = rm.find (role_key (elem, role));
            (i != rm.cend ());
            ++i)
        if (does_apply < html_version > (v, i -> second.from_, i -> second.to_))
        {   if (flags != nullptr) *flags = i -> second.flags_;
            return true; }
    return false; }

bool is_x_role (const rolemap& rm, const html_version& v, const e_element elem, const e_aria_role role)
{   return (is_role_lookup (rm, v, elem, role) || is_role_lookup (rm, v, elem, role_any)); }

bool is_default_role (const html_version& v, const e_element elem, const e_aria_role role)
{   return is_x_role (default_roles, v, elem, role); }

bool is_permitted_role (const html_version& v, const e_element elem, const e_aria_role role)
{   return is_x_role (permitted_roles, v, elem, role); }

e_aria_role furq_at (const e_aria_role& parent, const ::std::size_t n)
{   const ::std::size_t ar = furq.at (parent);
    if (ar == 0) return role_any;
    if (ar + n > sizeof (required_owner)) return role_any;
    if (GSL_AT (required_owner, furq.at (ar+n)).role_ != parent) return role_any;
    return GSL_AT (required_owner, furq.at (ar+n)).child_; }
