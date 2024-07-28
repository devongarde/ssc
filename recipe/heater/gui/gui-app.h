/*                                                                 ,
ssc (static site checker)
File Info
https://dylanharris.org/

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public Licence as published by
the Free Software Foundation, either version 3 of the Licence, or
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

#ifdef WX
#include "gui/gui-frame.h"

class app_t : public wxApp
{   frame_pt frame_ = nullptr; 
    int res_ = 0;
    bool argled_ = false;
    wxHtmlHelpController* help_ = nullptr;
    ::std::string help_path_;
protected:
    DECLARE_EVENT_TABLE ();   
public:
    void append (const ::std::string& text);
    void help (const char* wot) const;
    void display_contents () const;
    bool invalid () const { return (frame_ == nullptr) || (help_ == nullptr); }
#ifdef wxUSE_ON_FATAL_EXCEPTION
    void OnFatalException ();
#endif // wxUSE_ON_FATAL_EXCEPTION
    void OnIdle (wxIdleEvent& event);
    const frame_pt& frame () const { return frame_; }
    frame_pt& frame () { return frame_; }
    virtual bool OnInit ();
    virtual int OnExit (); };

DECLARE_APP (app_t)
extern app_t* app;

#endif // WX
