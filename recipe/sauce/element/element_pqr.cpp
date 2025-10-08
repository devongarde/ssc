/*
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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

#include "main/standard.h"
#include "element/element.h"
#include "webpage/page.h"

void element::examine_picture ()
{   test_no_role ();
    bool was_img = false, had_img = false, order_warn = false;
    element* prev = nullptr;
    for (element* c = child_; c != nullptr; c = c -> sibling_)
    {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
        if (! c -> node_.is_closure ())
            switch (c -> tag ())
            {   case elem_source :
                    if (was_img) { order_warn = true; was_img = false; }
                    if ((prev != nullptr) && ! prev -> a_.known (a_type))
                    {   bool ok = prev -> a_.known (a_media);
                        if (ok)
                        {   ::std::string val = prev -> a_.get_string (a_media);
                            ok = ! val.empty () && ! compare_complain (nits (), node_.version (), "all", val); }
                        if (! ok)
                            pick (nit_saucy_source, ed_jul20, "4.8.2 The source element", es_warning, ec_element,
                                "All but the last <SOURCE> must have either TYPE or MEDIA, which itself is neither empty nor set to 'all'."); }
                    prev = c;
                    break;
                case elem_img :
                    if (had_img)
                        pick (nit_not_img, ed_52, "4.7.3. The picture element", es_error, ec_element, "<PICTURE> can only have one <IMG> child.");
                    had_img = was_img = true; break;
                default : break; } }
    if (! had_img)
        pick (nit_not_img, ed_52, "4.7.3. The picture element", es_error, ec_element, "<PICTURE> must have one child <IMG>");
    else if (! was_img || order_warn)
        pick (nit_not_img, ed_52, "4.7.3. The picture element", es_error, ec_element, "under <PICTURE>, <SOURCE> must precede <IMG>"); }

void element::examine_piecewise ()
{   bool otherwise = false, noted = false;
    for (element* c = child_; c != nullptr; c = c -> sibling_)
    {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
        if (c -> node_.id ().is_math () && ! c -> node_.is_closure ())
        switch (c -> tag ())
        {   case elem_otherwise :
                otherwise = true; break;
            case elem_piece :
                if (otherwise && ! noted)
                {   pick (nit_bad_piece, ed_math_2, "4.4.2.16 Piecewise declaration (piecewise, piece, otherwise)", es_error, ec_element, "<PIECE> cannot follow <OTHERWISE>");
                    noted = true; }
                break;
            default :
                GRACEFUL_CRASH (__FILE__, __LINE__); } } }

void element::examine_progress ()
{   test_for_no_ancestral_role (no_progress_role_bitset);
    if (node_.version ().is_5 ())
    {   check_ancestors (elem_progress, element_bitset (elem_progress));
        if (a_.known (a_value))
        {   const bool kn = a_.known (a_max);
            double max = 1.0;
            double value = 0.0;
            if (kn)
            {   max = lexical < double > :: cast (a_.get_string (a_max));
                if (max < 0.0) pick (nit_no_progress, ed_50, "4.10.14 The progress element", es_error, ec_element, "<PROGRESS> MAX cannot be negative"); }
            value = lexical < double > :: cast (a_.get_string (a_value));
            if (value < 0.0) pick (nit_no_progress, ed_50, "4.10.14 The progress element", es_error, ec_element, "<PROGRESS> VALUE cannot be negative");
            if (value > max)
                if (kn) pick (nit_no_progress, ed_50, "4.10.14 The progress element", es_warning, ec_element, "<PROGRESS> VALUE exceeds MAX");
                else pick (nit_no_progress, ed_50, "4.10.14 The progress element", es_warning, ec_element, "<PROGRESS> VALUE exceeds 1.0, the default for MAX"); } } }

void element::examine_reln ()
{   if (node_.version ().math () > math_1)
        pick (nit_use_apply, ed_math_2, "4.2.1.3 The apply construct", es_comment, ec_element, "use <APPLY>, not <RELN>"); }

void element::examine_rsl ()
{   if (! a_.known (a_xmlns))
        pick (nit_attribute_required, ed_rsl, "Element: <rsl>", es_error, ec_rsl, "<RSL> requires an XMLNS attribute");
    else if (a_.get_int (a_xmlns) != x_rsl)
        pick (nit_xmlns_namespace, ed_rsl, "Element: <rsl>", es_error, ec_rsl, "Here, XMLNS must be set to \"" NSLS_RSL "\"");
    if (! descendant_elements_.test (elem_rsl_content))
        pick (nit_rsl_missing_child, ed_rsl, "Element: <rsl>", es_error, ec_rsl, "<rsl> requires at least one <content> child"); }

void element::examine_rsl_amount ()
{   test_value < t_real > (nits (), node_.version (), text ()); }

void element::examine_rsl_content ()
{   if (! descendant_elements_.test (elem_rsl_licence))
        pick (nit_rsl_missing_child, ed_rsl, "Element: <content>", es_error, ec_rsl, "<content> requires a <license> child");
    int cop = 0, ter = 0, sch = 0;
    for (element* e = child_; e != nullptr; e = e -> sibling_)
        switch (e -> tag ())
        {   case elem_rsl_copyright : ++cop; break;
            case elem_rsl_terms : ++ter; break;
            case elem_rsl_schema : ++sch; break;
            default: break; }
    if (cop > 1)
        pick (nit_rsl_overpopulation, ed_rsl, "Element: <copyright>", es_error, ec_rsl, "<content> may only have one <copyright> child");
    if (ter > 1)
        pick (nit_rsl_overpopulation, ed_rsl, "Element: <terms>", es_error, ec_rsl, "<content> may only have one <terms> child");
    if (sch > 1)
        pick (nit_rsl_overpopulation, ed_rsl, "Element: <schema>", es_error, ec_rsl, "<content> may only have one <schema> child");
    if (! a_.known (a_rsl_url))
        pick (nit_attribute_required, ed_rsl, "Element: <content>", es_error, ec_rsl, "<content> requires a URL attribute");
    else
    {   const vurl_t& us = a_.get_urls (a_rsl_url);
        for (element* e = parent_; e != nullptr; e = e -> sibling_)
            if (e != this)
                if (e -> tag () == elem_rsl_content)
                    if (e -> a_.known (a_rsl_url))
                    {   const vurl_t& vs = a_.get_urls (a_rsl_url);
                        for (auto u : us)
                            for (auto v : vs)
                                if (u == v)
                                    pick (nit_attribute_repeated, ed_rsl, "Element: <content>", es_error, ec_rsl, quote (u.original ()), ": is duplicated."); } } }

void element::examine_rsl_copyright ()
{   const ::std::string s = text ();
    if (a_.known (a_rsl_type))
        if (a_.good (a_rsl_type))
            switch (a_.get_int (a_rsl_type))
            {   case rpe_geo :
                    test_value < t_countries > (nits (), node_.version (), s);
                    break;
                case rpe_usage :
                    test_value < t_rsl_usages > (nits (), node_.version (), s);
                    break;
                case rpe_user :
                    test_value < t_rsl_users > (nits (), node_.version (), s);
                    break;
                default :
                    GRACEFUL_CRASH (__FILE__, __LINE__); } }

void element::examine_rsl_legal ()
{   const ::std::string s = text ();
    if (a_.known (a_rsl_type))
        if (a_.good (a_rsl_type))
        {   switch (a_.get_int (a_rsl_type))
            {   case rle_disclaimer :
                    test_value < t_rsl_disclaimer > (nits (), node_.version (), s);
                    break;
                case rle_warranty :
                    test_value < t_rsl_warranty > (nits (), node_.version (), s);
                    break;
                default :
                    break; }
            for (element* e = parent_; e != nullptr; e = e -> sibling_)
                if (e != this)
                    if (e -> tag () == elem_rsl_legal)
                        if (e -> a_.known (a_rsl_type) && e -> a_.good (a_rsl_type)) 
                            if (a_.get_int (a_rsl_type) == e -> a_.get_int (a_rsl_type))
                                pick (nit_repeated_value, ed_rsl, "Element: <legal>", es_error, ec_rsl, "<legal> TYPE duplicated."); } }

void element::examine_rsl_licence ()
{   int pay = 0;
    for (element* e = child_; e != nullptr; e = e -> sibling_)
        switch (e -> tag ())
        {   case elem_rsl_payment : ++pay; break;
            default: break; }
    if (pay > 1)
        pick (nit_rsl_overpopulation, ed_rsl, "Element: <payment>", es_error, ec_rsl, "<license> may only have one <payment> child");
    const ::std::string txt = trim_the_lot_off (text ());
    if (txt.empty ())
        pick (nit_empty, ed_rsl, "Element: <license>", es_warning, ec_rsl, "That <license> is rather vague.");
    else for (element* e = parent_; e != nullptr; e = e -> sibling_)
        if (e != this)
            if (e -> tag () == elem_rsl_licence)
                if (compare_no_case (txt, trim_the_lot_off (e -> text ())))
                    pick (nit_repeated_value, ed_rsl, "Element: <license>", es_error, ec_rsl, "Each <license> text must be distinct."); }

void element::examine_rsl_payment ()
{   int amo = 0, cus = 0;
    for (element* e = child_; e != nullptr; e = e -> sibling_)
        switch (e -> tag ())
        {   case elem_rsl_amount : ++amo; break;
            case elem_rsl_custom : ++cus; break;
            default: break; }
    if (amo > 1)
        pick (nit_rsl_overpopulation, ed_rsl, "Element: <amount>", es_error, ec_rsl, "<payment> may only have one <amount> child");
    if (cus > 1)
        pick (nit_rsl_overpopulation, ed_rsl, "Element: <custom>", es_error, ec_rsl, "<payment> may only have one <custom> child");
    const bool known = a_.known (a_rsl_type);
    if (! known || a_.good (a_rsl_type))
        for (element* e = parent_; e != nullptr; e = e -> sibling_)
            if (e != this)
                if (e -> tag () == elem_rsl_payment)
                    if (! known)
                        pick (nit_repeated_value, ed_rsl, "Element: <payment>", es_error, ec_rsl, "<payment> TYPE duplicated (no TYPE means all types).");
                    else if (! e -> a_.known (a_rsl_type))
                        pick (nit_repeated_value, ed_rsl, "Element: <payment>", es_error, ec_rsl, "<payment> TYPE duplicated by another <payment> with no TYPE.");
                    else if (e -> a_.good (a_rsl_type)) 
                        if (a_.get_int (a_rsl_type) == e -> a_.get_int (a_rsl_type))
                            pick (nit_repeated_value, ed_rsl, "Element: <payment>", es_error, ec_rsl, "<payment> TYPE duplicated."); }

void element::common_permits_prohibits (bool& geo, bool& usa, bool& use)
{   const ::std::string s = text ();
    if (! a_.known (a_rsl_type))
        geo = usa = use = true;
    else if (a_.good (a_rsl_type))
        switch (a_.get_int (a_rsl_type))
        {   case rpe_geo :
                test_value < t_countries > (nits (), node_.version (), s);
                geo = true;
                break;
            case rpe_usage :
                test_value < t_rsl_usages > (nits (), node_.version (), s);
                usa = true;
                break;
            case rpe_user :
                test_value < t_rsl_users > (nits (), node_.version (), s);
                use= true;
                break;
            default :
                break; } }

void element::examine_rsl_permits ()
{   bool geo = false, usa = false, use = false;
    common_permits_prohibits (geo, usa, use);
    for (element* e = parent_; e != nullptr; e = e -> sibling_)
        if (e != this)
            if (e -> tag () == elem_rsl_permits)
                if (! e -> a_.known (a_rsl_type))
                {   if (geo || usa || use)
                        pick (nit_repeated_value, ed_rsl, "Element: <permits>", es_error, ec_rsl, "<permits> TYPE duplicated by a TYPEless <permits>."); }
                else switch (a_.get_int (a_rsl_type))
                {   case rpe_geo :
                        pick (nit_repeated_value, ed_rsl, "Element: <permits>", es_error, ec_rsl, "<permits> TYPE geo duplicated.");
                        break;
                    case rpe_usage :
                        pick (nit_repeated_value, ed_rsl, "Element: <permits>", es_error, ec_rsl, "<permits> TYPE usage duplicated.");
                        break;
                    case rpe_user :
                        pick (nit_repeated_value, ed_rsl, "Element: <permits>", es_error, ec_rsl, "<permits> TYPE user duplicated.");
                        break;
                    default :
                        break; } }

void element::examine_rsl_prohibits ()
{   bool geo = false, usa = false, use = false;
    common_permits_prohibits (geo, usa, use);
    for (element* e = parent_; e != nullptr; e = e -> sibling_)
        if (e != this)
            if (e -> tag () == elem_rsl_prohibits)
                if (! e -> a_.known (a_rsl_type))
                {   if (geo || usa || use)
                        pick (nit_repeated_value, ed_rsl, "Element: <prohibits>", es_error, ec_rsl, "<prohibits> TYPE duplicated by a TYPEless <prohibits>."); }
                else switch (a_.get_int (a_rsl_type))
                {   case rpe_geo :
                        pick (nit_repeated_value, ed_rsl, "Element: <prohibits>", es_error, ec_rsl, "<prohibits> TYPE geo duplicated.");
                        break;
                    case rpe_usage :
                        pick (nit_repeated_value, ed_rsl, "Element: <prohibits>", es_error, ec_rsl, "<prohibits> TYPE usage duplicated.");
                        break;
                    case rpe_user :
                        pick (nit_repeated_value, ed_rsl, "Element: <prohibits>", es_error, ec_rsl, "<prohibits> TYPE user duplicated.");
                        break;
                    default :
                        break; } }

void element::examine_rsl_standard ()
{   url u (nits (), node_.version (), text ());
    if (u.valid ())
    {   ::std::string title = "Element: <";
        title += name ();
        title += ">";
        if (! u.is_local () && ! u.is_http () && ! u.is_https ())
           pick (nit_rsl_webpage, ed_rsl, title, es_error, ec_rsl, "<", name (), "> must contain a URL that 'must point to a web page', e.g. be local, HTTP, or HTTPS");
        u.verify (nits (), node_.version (), *this); } }

e_rss_version element::find_rss_version ()
{   const e_rss_version cv = context.rss_version ();
    for (element* e = parent_; e != nullptr; e = e -> parent_)
        if (e -> tag () == elem_rss)
            if (e -> a_.known (a_rss_version))
                if (e -> a_.good (a_rss_version))
                {   const e_rss_version v = static_cast < e_rss_version > (e -> a_.get_int (a_rss_version));
                    if (v != rv_error)
                    {   if (v != rv_20) return v;
                        if (cv <= rv_20) return rv_2011; }
                    break; }
    if (cv != rv_error) return cv;
    return rv_2011; }

void element::examine_rss ()
{   if (! a_.known (a_rss_version))
        pick (nit_attribute_required, ed_rss, "Element: <rss>", es_error, ec_rss, "<rss> requires a VERSION attribute");
    if (! descendant_elements_.test (elem_rss_channel))
        pick (nit_rss_missing_child, ed_rss, "Element: <rss>", es_error, ec_rss, "<rss> requires at least one <channel> child"); }

void element::examine_rss_channel ()
{   const e_rss_version v = find_rss_version ();
    if (! descendant_elements_.test (elem_rss_description))
        pick (nit_rss_missing_child, ed_rss, "Element: <channel>", es_error, ec_rss, "<channel> requires a <description> descendent."); 
    if (! descendant_elements_.test (elem_rss_language) && (v == rv_91))
        pick (nit_rss_missing_child, ed_rss, "Element: <channel>", es_error, ec_rss, "<channel> requires a <language> descendent in RSS 0.91."); 
    if (! descendant_elements_.test (elem_rss_link))
        pick (nit_rss_missing_child, ed_rss, "Element: <channel>", es_error, ec_rss, "<channel> requires a <link> descendent."); 
    if (! descendant_elements_.test (elem_rss_title))
        pick (nit_rss_missing_child, ed_rss, "Element: <channel>", es_error, ec_rss, "<channel> requires a <title> descendent."); 
    if (! descendant_elements_.test (elem_rss_language) && (v == rv_91))
        pick (nit_rss_missing_child, ed_rss, "Element: <channel>", es_warning, ec_rss, "Some flavours of RSS 0.91 require that <channel> has an <image> descendent."); }

void element::examine_rss_date ()
{   verify_rfc822 (nits (), node ().version (), trim_the_lot_off (text ()), true); }

void element::examine_rss_day ()
{   const e_rss_version v = find_rss_version ();
    if (v > rv_92)
        pick (nit_rss, ed_rss, "Element: <day>", es_error, ec_rss, "<DAY> requires RSS 0.91 or 0.92.");
    test_value < t_weekday_english_long > (nits (), node_.version (), text ()); }

void element::examine_rss_docs ()
{   url u (nits (), node_.version (), trim_the_lot_off (text ()));
    u.verify (nits (), node_.version (), *this); }

void element::examine_rss_email ()
{   test_value < t_email > (nits (), context.html_ver (), trim_the_lot_off (text ())); }

void element::examine_rss_category ()
{   const e_rss_version v = find_rss_version ();
    if (v < rv_92)
        pick (nit_rss, ed_rss, "Element: <category>", es_error, ec_rss, "<category> was introduced in RSS 0.92."); }

void element::examine_rss_cloud ()
{   const e_rss_version v = find_rss_version ();
    if (v < rv_92)
        pick (nit_rss, ed_rss, "Element: <cloud>", es_error, ec_rss, "<cloud> was introduced in RSS 0.92."); }

void element::examine_rss_enclosure ()
{   const e_rss_version v = find_rss_version ();
    if (v < rv_92)
        pick (nit_rss, ed_rss, "Element: <enclosure>", es_error, ec_rss, "<enclosure> was introduced in RSS 0.92."); 
    if (! a_.known (a_rss_length))
        pick (nit_rss_missing_attribute, ed_rss, "Element: <enclosure>", es_error, ec_rss, "<source> requires a LENGTH attribute.");
    if (! a_.known (a_rss_type))
        pick (nit_rss_missing_attribute, ed_rss, "Element: <enclosure>", es_error, ec_rss, "<source> requires a TYPE attribute.");
    if (! a_.known (a_rss_url))
        pick (nit_rss_missing_attribute, ed_rss, "Element: <enclosure>", es_error, ec_rss, "<source> requires a URL attribute."); }

void element::examine_rss_height ()
{   const unsigned i = examine_value < t_unsigned > (nits (), node_.version (), trim_the_lot_off (text ())); 
    if (i > 400)
        pick (nit_rss, ed_rss, "Element: <height>", es_error, ec_rss, "The <HEIGHT> value must under 401"); }

void element::examine_rss_hour ()
{   const e_rss_version v = find_rss_version ();
    if (v > rv_92)
        pick (nit_rss, ed_rss, "Element: <hour>", es_error, ec_rss, "<HOUR> requires RSS 0.91 or 0.92");
    const unsigned h = examine_value < t_unsigned > (nits (), node_.version (), trim_the_lot_off (text ())); 
    if (h > 23)
        pick (nit_rss, ed_rss, "Element: <hour>", es_error, ec_rss, "The <HOUR> value should lie between 0 and 23"); }

void element::examine_rss_image ()
{   if (! descendant_elements_.test (elem_rss_link))
        pick (nit_rss_missing_child, ed_rss, "Element: <image>", es_error, ec_rss, "<image> requires a <link> descendent."); 
    if (! descendant_elements_.test (elem_rss_title))
        pick (nit_rss_missing_child, ed_rss, "Element: <image>", es_error, ec_rss, "<image> requires a <title> descendent."); 
    if (! descendant_elements_.test (elem_rss_url))
        pick (nit_rss_missing_child, ed_rss, "Element: <image>", es_error, ec_rss, "<image> requires a <url> descendent."); }

void element::examine_rss_item ()
{   const e_rss_version v = find_rss_version ();
    if (v == rv_91)
    {   if (! descendant_elements_.test (elem_rss_link))
            pick (nit_rss_missing_child, ed_rss, "Element: <item>", es_error, ec_rss, "In RSS 0.91, <item> requires a <link> descendent."); 
        if (! descendant_elements_.test (elem_rss_title))
            pick (nit_rss_missing_child, ed_rss, "Element: <item>", es_error, ec_rss, "In RSS 0.91, <item> requires a <title> descendent."); }
    else if (v >= rv_20)
        if (! descendant_elements_.test (elem_rss_description) && ! descendant_elements_.test (elem_rss_title))
            pick (nit_rss_missing_child, ed_rss, "Element: <item>", es_error, ec_rss, "In RSS 2, <item> requires at least a <description> or a <title> descendent."); }

void element::examine_rss_language ()
{   test_value < t_lang > (nits (), context.html_ver (), trim_the_lot_off (text ())); }

void element::examine_rss_link ()
{   const e_rss_version v = find_rss_version ();
    url u (nits (), node_.version (), trim_the_lot_off (text ()));
    u.verify (nits (), node_.version (), *this);
    switch (v)
    {   case rv_91 :
        case rv_92 :
            if (! u.is_protocol (pr_http) && ! u.is_protocol (pr_ftp))
                if (u.is_protocol (pr_https))
                    pick (nit_invalid_protocol, ed_rss, "Element: <link>", es_comment, ec_rss, "In rss 0.91 and 0.92, <link> officially requires HTTP or FTP, but that's HTTPS, so....");
                else pick (nit_invalid_protocol, ed_rss, "Element: <link>", es_warning, ec_rss, "In rss 0.91 and 0.92, <link> requires HTTP or FTP.");
            break;
        default :
            if (! u.is_protocol (pr_http) && ! u.is_protocol (pr_https))
                pick (nit_invalid_protocol, ed_rss, "Element: <link>", es_info, ec_rss, "Is that protocol correct?");
            break; } }

void element::examine_rss_skipdays ()
{   const e_rss_version v = find_rss_version ();
    if (v < rv_20)
        if (! descendant_elements_.test (elem_rss_day))
            pick (nit_rss_missing_child, ed_rss, "Element: <skipdays>", es_error, ec_rss, "<skipdays> requires at least one <day> descendent."); }

void element::examine_rss_skiphours ()
{   const e_rss_version v = find_rss_version ();
    if (v < rv_20)
        if (! descendant_elements_.test (elem_rss_hour))
            pick (nit_rss_missing_child, ed_rss, "Element: <skiphours>", es_error, ec_rss, "<skiphours> requires at least one <hour> descendent."); }

void element::examine_rss_source ()
{   const e_rss_version v = find_rss_version ();
    if (v < rv_92)
        pick (nit_rss, ed_rss, "Element: <source>", es_error, ec_rss, "<source> was introduced in RSS 0.92."); }

void element::examine_rss_textinput ()
{   if (! descendant_elements_.test (elem_rss_description))
        pick (nit_rss_missing_child, ed_rss, "Element: <textinput>", es_error, ec_rss, "<textinput> requires a <description> descendent."); 
    if (! descendant_elements_.test (elem_rss_link))
        pick (nit_rss_missing_child, ed_rss, "Element: <textinput>", es_error, ec_rss, "<textinput> requires a <link> descendent."); 
    if (! descendant_elements_.test (elem_rss_name))
        pick (nit_rss_missing_child, ed_rss, "Element: <textinput>", es_warning, ec_rss, "<textinput> requires a <name> descendent."); 
    if (! descendant_elements_.test (elem_rss_title))
        pick (nit_rss_missing_child, ed_rss, "Element: <textinput>", es_error, ec_rss, "<textinput> requires a <title> descendent."); }

void element::examine_rss_url ()
{   url u (nits (), node_.version (), trim_the_lot_off (text ()));
    u.verify (nits (), node_.version (), *this); }

void element::examine_rss_width ()
{   const unsigned i = examine_value < t_unsigned > (nits (), node_.version (), trim_the_lot_off (text ())); 
    if (i > 144)
        pick (nit_rss, ed_rss, "Element: <width>", es_error, ec_rss, "The <WIDTH> value must under 145"); }

void element::examine_ruby ()
{   if (node_.version ().mjr () < 5) return;
    test_for_ancestral_role ();
    bool had_ruby = false, had_non_ruby = false, had_rt = false, had_rp = false, rp_mode = false;
    const bool is_whatwg = node_.version ().whatwg ();
    for (element* c = child_; c != nullptr; c = c -> sibling_)
    {   VERIFY_NOT_NULL (c, __FILE__, __LINE__);
        if (is_standard_element (c -> tag ()) && ! c -> node_.is_closure ())
            if (is_whatwg) switch (c -> tag ())
            {   case elem_ruby :
                    if (had_non_ruby) pick (nit_mix_ruby_non, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "do not mix child <RUBY> elements with child phrasal elements");
                    else if (had_ruby) pick (nit_too_many_ruby, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "each child <RUBY> must be separated by an <RT>");
                    if (had_rt || had_rp)
                            pick (nit_no_rp, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "each child <RUBY> must precede any <RT> or <RP> children");
                    had_ruby = true;
                    had_non_ruby = had_rt = had_rp = rp_mode = false;
                    break;
                case elem_rt :
                    if (rp_mode && had_rt)
                        pick (nit_no_rp, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "<RP> should be interleaved with <RT>");
                    had_ruby = had_non_ruby = had_rp = false;
                    had_rt = true;
                    break;
                case elem_rp :
                    if (! rp_mode && had_rt)
                        pick (nit_no_rp, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "<RP> must precede any <RT>");
                    had_ruby = had_non_ruby = had_rt = false;
                    had_rp = rp_mode = true;
                    break;
                default :
                    if (had_ruby) pick (nit_too_many_ruby, ed_jul20, "4.5.10 The ruby element", es_error, ec_element, "Do not mix child <RUBY>s with child phrasal elements");
                    had_non_ruby = true;
                    had_ruby = had_rt = had_rp = false;
                    break; }
            else switch (c -> tag ())
            {   case elem_rt :
                case elem_rtc :
                    if (had_rt)
                        pick (nit_no_rp, ed_51, "4.5.10 The ruby element", es_error, ec_element, "<RP> should immediately precede OR follow <RT> andor <RTC>");
                    else had_rt = true;
                    break;
                case elem_rp :
                    had_rp = true;
                    break;
                default :
                    if (had_rt != had_rp)
                        pick (nit_no_rp, ed_51, "4.5.10 The ruby element", es_error, ec_element, "<RT> and <RTC> elements must precede or follow an <RP>");
                    had_rp = had_rt = false;
                    break; } }
    if (! is_whatwg)
        if (had_rt != had_rp)
            pick (nit_no_rp, ed_51, "4.5.10 The ruby element", es_error, ec_element, "<RP> should immediately precede OR follow <RT> andor <RTC>"); }
