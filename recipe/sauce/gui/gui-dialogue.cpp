/*
ssc (static site checker)
File Info
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

bool dialogue_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, const long style)
{	preCreate (mummy, pos);
	if (size_ == wxDefaultSize) size_ = size;
	if (! wxDialog :: Create (mummy, id, caption, point_, size_, style)) return false;
	CreateBox ();
	return true; }

bool whizzo_t :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption, const wxPoint& pos, const long style)
{	preCreate (mummy, pos);
	return wxWizard :: Create (mummy, id, caption, wxBitmapBundle (), point_, style); }

#endif // WX
