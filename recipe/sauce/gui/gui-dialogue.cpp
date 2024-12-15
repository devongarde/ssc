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
#include "gui/gui-dialogue.h"

bool d2_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, const long style)
{	if (! preCreate (mummy, id, caption, pos, size, style)) return false;
	CreateBox ();
	return true; }

void d2_t :: CreateBox ()
{	box_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxVERTICAL));
    if (box_ != nullptr)
    {   grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 5, 0, 0));
        if (grid_ != nullptr)
            cancel_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_CANCEL)); } }

void d2_t :: CreateButtons (const int bs)
{	if (interrogate < wxDialog > :: invalid ()) return;
    about_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_ABOUT));
    if (about_ != nullptr)
    {   help_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_HELP));
        if (help_ != nullptr)
        {   ok_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_OK));
#ifndef DARWIN
            grid_ -> Add (about_, 0, wxALL, 5);
            grid_ -> Add (help_, 0, wxALL, 5);
            grid_ -> Add (0, 0, 1, wxEXPAND, 5);
            grid_ -> Add (ok_, 0, wxALL | wxDEFAULT, 5);
            grid_ -> Add (cancel_, 0, wxALL, 5);
#else // DARWIN
            grid_ -> Add (help_, 0, wxALL, 5);
            grid_ -> Add (about_, 0, wxALL, 5);
            grid_ -> Add (0, 0, 1, wxEXPAND, 5);
            grid_ -> Add (cancel_, 0, wxALL, 5);
            grid_ -> Add (ok_, 0, wxALL, 5);
#endif // DARWIN
            ok_ -> SetDefault ();
            box_ -> Add (grid_, bs, wxEXPAND, 1); } } }

bool d3_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, const long style)
{	if (! preCreate (mummy, id, caption, pos, size, style)) return false;
	CreateBox ();
	return true; }

void d3_t :: CreateBox ()
{	box_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxVERTICAL));
    if (box_ != nullptr)
    {   grid_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 4, 0, 0));
        if (grid_ != nullptr)
        {   grid_ls_ = GSL_OWNER (wxGridSizer) (new wxGridSizer (0, 4, 0, 0));
            if (grid_ls_ != nullptr)
                cancel_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_CANCEL)); } } }

void d3_t :: CreateButtons (const int bs)
{	if (interrogate < wxDialog > :: invalid_panel ()) return;
	divider_ = GSL_OWNER (wxStaticLine) (new wxStaticLine (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL));
    if (divider_ != nullptr)
	{   save_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_SAVE));
        if (save_ != nullptr)
	    {   save_as_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_SAVEAS));
            if (save_as_ != nullptr)
            {   load_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_OPEN));
                if (load_ != nullptr)
                {   help_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_HELP));
                    if (help_ != nullptr)
                    {   ok_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_OK));
                        box_ -> Add (divider_, 0, wxEXPAND | wxALL, 5);
                        grid_ls_ -> Add (load_, 0, wxALL, 5);
                        grid_ls_ -> Add (0, 0, 1, wxEXPAND, 5);
                        grid_ls_ -> Add (save_, 0, wxALL, 5);
                        grid_ls_ -> Add (save_as_, 0, wxALL, 5);
    #ifndef DARWIN
                        grid_ -> Add (help_, 0, wxALL, 5);
                        grid_ -> Add (0, 0, 1, wxEXPAND, 5);
                        grid_ -> Add (ok_, 0, wxALL | wxDEFAULT, 5);
                        grid_ -> Add (cancel_, 0, wxALL, 5);
    #else // DARWIN
                        grid_ -> Add (help_, 0, wxALL, 5);
                        grid_ -> Add (0, 0, 1, wxEXPAND, 5);
                        grid_ -> Add (cancel_, 0, wxALL, 5);
                        grid_ -> Add (ok_, 0, wxALL, 5);
    #endif // DARWIN
                        ok_ -> SetDefault ();
                        box_ -> Add (grid_ls_, bs, wxEXPAND, 1);
                        box_ -> Add (grid_, bs, wxEXPAND, 1); } } } } } }

#endif // WX
