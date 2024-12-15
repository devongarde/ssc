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

#ifdef WX
#include "gui/gui-menu.h"
#include "gui/gui-app.h"

#define CONFIG_EDIT "&edit..."
#define CONFIG_EDIT_DESC "edit the current configuration"
#define CONFIG_OPEN "&load..."
#define CONFIG_OPEN_DESC "load a configuration file"
#define CONFIG_SAVE "&save"
#define CONFIG_SAVE_DESC "write to the previously named configuration file"
#define CONFIG_SAVE_AS "save &as..."
#define CONFIG_SAVE_AS_DESC "write to a named configuration file"
#define COPY_DESC "copy selection to clipboard"
#define COPY_TEXT "&copy"
#define DOWN_DESC "on a spin control, click down to count down"
#define DOWN_TEXT "&down down"
#define EXIT_DESC PROG " begone"
#define EXIT_TEXT "e&xit"
#define FIND_DESC "find some text (" PROG " knows no pots of gold, sorry)"
#define FIND_TEXT "&find..."
#define HELP_DESC "go see the burble"
#define HELP_TEXT "view &help..."
#define NEXT_DESC "find next found text"
#define NEXT_TEXT "ne&xt"
#define NEW_ROOT_DESC "new site root nickpickery"
#define NEW_ROOT_TEXT "new &root..."
#define NEW_SNIPPET_DESC "new HTML snippet nickpickery"
#define NEW_SNIPPET_TEXT "new s&nippet..."
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
#define SAVE_TEXT "&save output"
#define SAVE_AS_DESC "output output to a named file"
#define SAVE_AS_TEXT "save output &as..."
#define SELECTALL_DESC "select all text"
#define SELECTALL_TEXT "select &all"


void bar_t :: init ()
{   PRESUME (invalid (), __FILE__, __LINE__);

// A as     H      O      V preview
// B      I      P print     W
// C copy     J      Q      X exit
// D      K      R root     Y
// E      L      S save     Z
// F      M      T
// G print setup     N snippet     U

    file_ = GSL_OWNER (wxMenu) (new wxMenu);
    if (file_ == nullptr) return;
    file_ -> Append (menu_root, NEW_ROOT_TEXT, NEW_ROOT_DESC);
    file_ -> Append (menu_snippet, NEW_SNIPPET_TEXT, NEW_SNIPPET_DESC);
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
// B      I x    P      W
// C x    J      Q      X x
// D x    K      R      Y
// E      L      S      Z
// F x    M      T
// G      N      U
 
    edit_ = GSL_OWNER (wxMenu) (new wxMenu);
    if (edit_ == nullptr) return;
    edit_ -> Append (wxID_FIND, FIND_TEXT, FIND_DESC);
#ifdef DARWIN
    edit_ -> Append (menu_next, NEXT_TEXT, NEXT_DESC);
    edit_ -> Append (menu_prior, PRIOR_TEXT, PRIOR_DESC);
#else // DARWIN
    edit_ -> Append (menu_next, NEXT_TEXT "\tF3", NEXT_DESC);
    edit_ -> Append (menu_prior, PRIOR_TEXT "\tShift+F3", PRIOR_DESC);
#endif // DARWIN
    edit_ -> AppendSeparator ();
    edit_ -> Append (wxID_COPY, COPY_TEXT, COPY_DESC);
    edit_ -> Append (wxID_SELECTALL, SELECTALL_TEXT, SELECTALL_DESC);
 
// A x    H x    O      V x
// B      I x    P x    W x
// C x    J      Q      X
// D x    K x    R x    Y
// E      L x    S x    Z
// F x    M x    T x
// G x    N x    U

    config_ = GSL_OWNER (wxMenu) (new wxMenu);
    if (config_ == nullptr) return;

    config_ -> Append (menu_conf_edit, CONFIG_EDIT, CONFIG_EDIT_DESC);
    config_ -> AppendSeparator ();
    config_ -> Append (menu_conf_open, CONFIG_OPEN, CONFIG_OPEN_DESC);
    config_ -> Append (menu_conf_save, CONFIG_SAVE, CONFIG_SAVE_DESC);
    config_ -> Append (menu_conf_save_as, CONFIG_SAVE_AS, CONFIG_SAVE_AS_DESC);
    config_ -> AppendSeparator ();
    config_ -> AppendCheckItem (menu_spin, DOWN_TEXT, DOWN_DESC);
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
