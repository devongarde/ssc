/*
ssc (static site checker)
Copyright (c) 2020-2024 Dylan Harris
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

#ifdef WX
#include "gui/gui-menu.h"
#include "gui/gui-app.h"

#define CONFIG_OPEN "&load configuration..."
#define CONFIG_OPEN_DESC "load a configuration file"
#define CONFIG_SAVE "&save configuration"
#define CONFIG_SAVE_DESC "write to the previously named configuration file"
#define CONFIG_SAVE_AS "save configuration &as..."
#define CONFIG_SAVE_AS_DESC "write to a named configuration file"
#define EXIT_DESC PROG " begone"
#define EXIT_TEXT "e&xit"
#define HELP_DESC "go see the burble"
#define HELP_TEXT "view &help..."
#define NEXT_DESC "find next found text"
#define NEXT_TEXT "ne&xt"
#define PRIOR_DESC "find prior found text"
#define PRIOR_TEXT "pr&ior"
#define PRINT_DESC "slaughter more innocent trees"
#define PRINT_TEXT "&print..."
#define PRINT_PREVIEW_DESC "print to screen and scream"
#define PRINT_PREVIEW_TEXT "print pre&view..."
#define PRINT_SETUP_DESC "gurgle the layout"
#define PRINT_SETUP_TEXT "pa&ge setup..."
#define ROOT_DESC "nitpick a site"
#define ROOT_TEXT "nitpick site &root..."
#define SAVE_DESC "output output to a previous output"
#define SAVE_TEXT "&save"
#define SAVE_AS_DESC "output output to a named file"
#define SAVE_AS_TEXT "save &as..."
#define SNIPPET_DESC "nitpick a snippet"
#define SNIPPET_TEXT "nitpick s&nippet..."
#define WHIZZ_DESC "start here (pick me!)"
#define WHIZZ_TEXT "wi&zard..."

// A      H      O      V
// B      I      P      W
// C      J      Q      X
// D      K      R      Y
// E      L      S      Z
// F      M      T
// G      N      U

void bar_t :: init ()
{   PRESUME (invalid (), __FILE__, __LINE__);

// A      H      O      V
// B      I      P      W
// C      J      Q      X
// D      K      R      Y
// E      L      S      Z
// F      M      T
// G      N      U

    file_ = GSL_OWNER (wxMenu) (new wxMenu);
    if (file_ == nullptr) return;
#ifdef DARWIN
    file_ -> Append (menu_site, ROOT_TEXT, ROOT_DESC);
    file_ -> Append (menu_snippet, SNIPPET_TEXT, SNIPPET_DESC);
#else // DARWIN
    file_ -> Append (menu_root, ROOT_TEXT "\tctrl+I", ROOT_DESC);
    file_ -> Append (menu_snippet, SNIPPET_TEXT "\tctrl+N", SNIPPET_DESC);
#endif // DARWIN
//    file_ -> Append (menu_wizzard, WHIZZ_TEXT, WHIZZ_DESC);
    file_ -> AppendSeparator ();
    file_ -> Append (wxID_SAVE, SAVE_TEXT, SAVE_DESC);
    file_ -> Append (wxID_SAVEAS, SAVE_AS_TEXT, SAVE_AS_DESC);
    file_ -> AppendSeparator ();
    file_ -> Append (menu_print_setup, PRINT_SETUP_TEXT, PRINT_SETUP_DESC);
    file_ -> Append (wxID_PREVIEW, PRINT_PREVIEW_TEXT, PRINT_PREVIEW_DESC);
    file_ -> Append (wxID_PRINT, PRINT_TEXT, PRINT_DESC);
    file_ -> AppendSeparator ();
    file_ -> Append (wxID_EXIT, EXIT_TEXT, EXIT_DESC);

// A x    H      O      V
// B      I      P      W
// C x    J      Q      X
// D      K      R      Y
// E      L      S      Z
// F x    M      T
// G      N      U
 
    edit_ = GSL_OWNER (wxMenu) (new wxMenu);
    if (edit_ == nullptr) return;
    edit_ -> Append (wxID_FIND, "&find...", "find some text (" PROG " knows no pots of gold, sorry)");
#ifdef DARWIN
    edit_ -> Append (menu_next, NEXT_TEXT, NEXT_DESC);
    edit_ -> Append (menu_prior, PRIOR_TEXT, PRIOR_DESC);
#else // DARWIN
    edit_ -> Append (menu_next, NEXT_TEXT "\tF3", NEXT_DESC);
    edit_ -> Append (menu_prior, PRIOR_TEXT "\tShift+F3", PRIOR_DESC);
#endif // DARWIN
    edit_ -> AppendSeparator ();
    edit_ -> Append (wxID_COPY, "&copy", "copy selection to clipboard");
    edit_ -> Append (wxID_SELECTALL, "select &all", "select the entire output");
 
// A x    H x    O      V x
// B      I x    P x    W x
// C x    J      Q      X
// D x    K x    R x    Y
// E      L x    S x    Z
// F x    M x    T x
// G x    N x    U

    config_ = GSL_OWNER (wxMenu) (new wxMenu);
    if (config_ == nullptr) return;
    config_ -> Append (menu_html, "&HTML...", "configure HTML and other markup");
    config_ -> Append (menu_css, "&CSS...", "configure CSS nitpicking");
    config_ -> Append (menu_general, "&general...", "configure the stuff that doesn't go in another dialogue");
    config_ -> Append (menu_nits, "&nits...", "configure the nits themselves");
    config_ -> Append (menu_ontology, "&data...", "configure ontology and microformats");
    config_ -> Append (menu_shadow, "sha&dow...", "configure shadow output");
    config_ -> Append (menu_site, "si&te...", "configure website nitpicking");
#ifndef NOSPELL
    config_ -> Append (menu_spell, "spe&ll...", "configure spelling verification");
#endif // NOSPELL
    config_ -> Append (menu_stats, "&reports...", "select and configure reports");
#ifdef DEBUG
    config_ -> Append (menu_validation, "v&alidation...", "configure type validation");
#endif // DEBUG
    config_ -> AppendSeparator ();
    config_ -> Append (menu_conf_open, CONFIG_OPEN, CONFIG_OPEN_DESC);
    config_ -> Append (menu_conf_save, CONFIG_SAVE, CONFIG_SAVE_DESC);
    config_ -> Append (menu_conf_save_as, CONFIG_SAVE_AS, CONFIG_SAVE_AS_DESC);
    config_ -> AppendSeparator ();
    config_ -> AppendCheckItem (menu_spin, "spin do&wn is count down", "when you click down on a spin button, should the value decrease?");
    config_ -> Check (menu_spin, true);

// A x    H      O      V
// B      I      P      W
// C      J      Q      X
// D      K      R      Y
// E      L      S      Z
// F      M      T
// G      N      U

    help_ = GSL_OWNER (wxMenu) (new wxMenu);
    if (help_ == nullptr) return;
#ifdef DARWIN
    help_ -> Append (menu_help, HELP_TEXT, HELP_DESC);
#else // DARWIN
    help_ -> Append (menu_help, HELP_TEXT "\tctrl+F1", HELP_DESC);
#endif // DARWIN
    help_ -> AppendSeparator ();
    help_ -> Append (wxID_ABOUT, "&about...", "who to blame, who to praise, in what pantheon shall we blaze");

// A      H x    O      V
// B      I      P      W
// C x    J      Q      X
// D      K      R      Y
// E x    L      S      Z
// F x    M      T
// G      N      U
 
    bar_ = GSL_OWNER (wxMenuBar) (new wxMenuBar);
    if (bar_ == nullptr) return;
    bar_ -> Append (file_, "&file");
    bar_ -> Append (edit_, "&edit");
    bar_ -> Append (config_, "&configure");
    bar_ -> Append (help_, "&help"); }

#endif // WX
