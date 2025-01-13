/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2025 Dylan Harris
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
#include "gui/gui-welcome.h"

#define DEF_CONF_WILD "Configuration files (*." DEF_CONF_EXT ")|*." DEF_CONF_EXT

class app_t : public wxApp
{   frame_pt frame_ = nullptr; 
    welcome_t* welcome_ = nullptr;
    int res_ = 0;
    wxHtmlHelpController* help_ = nullptr;
    ::boost::filesystem::path help_path_;
    vstr_t cmd_;
    int recycle (nitpick& nits, const int argc, char** argv);
protected:
    DECLARE_EVENT_TABLE ();   
public:
    void append (const ::std::string& text);
    void console (const ::std::string& text);
    void console_check ();
    void get_set ();
    void display_contents () const;
    void help (const char* wot) const;
    bool invalid () const { return (frame_ == nullptr) || (help_ == nullptr); }
    void yield ();
#ifdef wxUSE_ON_FATAL_EXCEPTION
    void OnFatalException ();
#endif // wxUSE_ON_FATAL_EXCEPTION
    void OnIdle (wxIdleEvent& event);
    const frame_pt& frame () const { return frame_; }
    frame_pt& frame () { return frame_; }
    static void nits_msgbox (wxWindow* mummy, const ::std::string& title, nitpick& nits, const e_severity worst =
#ifdef NDEBUG
        es_info
 #else //  NDEBUG
        es_debug
#endif //  NDEBUG      
                    );
    static bool load_conf (wxWindow* mummy, context_t& c, ::boost::filesystem::path& fn);
    static bool save_conf (wxWindow* mummy, const context_t& c, const ::boost::filesystem::path& fn);
    static bool save_conf_as (wxWindow* mummy, context_t& c, ::boost::filesystem::path& fn);
    bool Welcome (context_t& context);
    virtual bool OnInit ();
    virtual int OnExit (); };

DECLARE_APP (app_t)
extern app_t* app;

#endif // WX
