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
#include "main/abort.h"
#include "main/args.h"
#include "parser/text.h"
#include "main/output.h"
#include "feedback/nitpick.h"
#include "main/context.h"
#include "main/ssc.h"
#include "gui/gui-app.h"
#include "gui/gui-screen.h"
#include "gui/gui-frame.h"
#include "gui/gui-welcome.h"
#include "../../tea/resource.h"

IMPLEMENT_APP (app_t)

#define HELP_FN "help.htb"

app_t* app = nullptr;

BEGIN_EVENT_TABLE (app_t, wxApp)
    EVT_IDLE (app_t::OnIdle)
END_EVENT_TABLE ()

bool app_t::OnInit ()
{   nitpick nits;
    init (nits);
    SetAppName (FULLNAME);
    SetAppDisplayName (FULLNAME " v" VERSION_STRING " (" WEBADDR ")");
    SetVendorName (COPYRIGHT_FORENAME " " COPYRIGHT_SURNAME);
    SetVendorDisplayName (COPYRIGHT_FORENAME " " COPYRIGHT_SURNAME " " COPYRIGHT_BRADDR);
    SetCLocale ();
    app = this;
    wxFileSystem::AddHandler(new wxZipFSHandler);
    context_t c (context);
    c.html_ver (html_default);
    help_path_ = c.help ();
#ifdef _MSC_VER
    if (help_path_.empty ())
    {   const HRSRC src = FindResource (nullptr, MAKEINTRESOURCE (IDR_HELP), RT_RCDATA);
        if (src != INVALID_HANDLE_VALUE)
        {   const HGLOBAL load = LoadResource (nullptr, src);
            if ((load != INVALID_HANDLE_VALUE) && (load != 0))
            {   const LPVOID lock = LockResource (load);
                if (lock != nullptr)
                {   const DWORD size = SizeofResource (nullptr, src);
                    if (size > 0)
                    {   ::boost::filesystem::path datapath = c.path ();
                        datapath /= "help.htb";
                        const HANDLE file = CreateFileA (datapath.string ().c_str (), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                        if (file != INVALID_HANDLE_VALUE)
                        {   DWORD written = 0;
                            if (WriteFile (file, lock, size, &written, nullptr))
                                if (written == size)
                                {   help_path_ = datapath;
                                    c.help (help_path_.string ()); } }
                        CloseHandle (file); } }
                FreeResource (load); } } }
#endif // _MSC_VER
    help_ = GSL_OWNER (wxHtmlHelpController) (new wxHtmlHelpController ());
    if (help_ == nullptr) return false;
    help_ -> Initialize (help_path_.c_str ());
    wxSize sz (wxDefaultSize);
    wxPoint pt (wxDefaultPosition);
    unsigned x = 0, y = 0, w = 0, h = 0;
    if (get_default_window_position (x, y, w, h))
    {   pt.x = GSL_NARROW_CAST < int > (x);
        pt.y = GSL_NARROW_CAST < int > (y);
        sz.x = GSL_NARROW_CAST < int > (w);
        sz.y = GSL_NARROW_CAST < int > (h); }
    if ((argc <= 1) && (Welcome (c) != IDOK)) return false;
    frame_ = GSL_OWNER (frame_t) (new frame_t (pt, sz, c));
    if (frame_ == nullptr) return false;
#ifdef _MSC_VER
    outstr.enloggen (true);
#ifdef wxUSE_ON_FATAL_EXCEPTION
    wxHandleFatalExceptions (true);
#endif // wxUSE_ON_FATAL_EXCEPTION
#endif // _MSC_VER
    frame_ -> Show (true);
    return true; }

bool app_t :: Welcome (context_t& c)
{   welcome_t w (nullptr, c);
    w.set_default ();
    if (w.ShowModal () == wxID_CANCEL) return false;
    cmd_ = w.cmd ();
    c = w.c ();
    return true; }

#ifdef wxUSE_ON_FATAL_EXCEPTION
void app_t::OnFatalException ()
{   DEBUG_BREAK;
    GRACEFUL_CRASH (__FILE__, __LINE__); }
#endif // wxUSE_ON_FATAL_EXCEPTION

void app_t::OnIdle (wxIdleEvent& event)
{   nitpick nits;   
    if (frame_ != nullptr)
        if (argc > 1)
        {   frame_ -> shush (false);
            res_ = cycle (nits, argc, argv);
            if (res_ == STOP_NOW) res_ = VALID_RESULT;
            argc = 0; }
        else if (! cmd_.empty ())
        {   context.cmd (cmd_);
            cmd_.clear ();
#ifdef _MSC_VER
            outstr.enloggen (true);
#endif // _MSC_VER
            frame_ -> shush (false);
            res_ = cycle (nits, 0, nullptr);
            if (res_ == STOP_NOW) res_ = VALID_RESULT; }
        else if (frame_ -> new_site () || frame_ -> new_config ())
        {   ::std::string s (frame_ -> site ().string ());
            ::std::string cf (frame_ -> config ().string ());
            PRESUME ((! s.empty ()) || (! cf.empty ()), __FILE__, __LINE__);
            vstr_t c;
            if (! cf.empty ())
            {   c.push_back (FILE_SW);
                c.push_back (frame_ -> config ().string ()); }
            if (! s.empty ())
                c.push_back (s);
            context.cmd (c);
            frame_ -> clear ();
#ifdef _MSC_VER
            outstr.enloggen (true);
#endif // _MSC_VER
            frame_ -> shush (false);
            res_ = cycle (nits, 0, nullptr); }
        else if (frame_ -> new_snippet ())
        {   ::std::string s (frame_ -> snippet ());
            PRESUME (! s.empty (), __FILE__, __LINE__);
            vstr_t c;
            c.push_back (FNCYSWTCH HTML SNIPPET);
            c.push_back (s);
            context.cmd (c);
            frame_ -> clear ();
#ifdef _MSC_VER
            outstr.enloggen (true);
#endif // _MSC_VER
            frame_ -> shush (false);
            res_ = cycle (nits, argc, argv); }
    event.Skip (); }

void app_t::append (const ::std::string& text)
{   if (frame_ != nullptr) frame_ -> append (text); }

void app_t::help (const char* wot) const
{   if (help_ != nullptr) help_ -> DisplaySection (wot); }

void app_t::display_contents () const
{   if (help_ != nullptr)  help_ -> DisplayContents (); }

int app_t::OnExit ()
{   if (help_ != nullptr)
    {   delete help_;
        help_ = nullptr; }
    app = nullptr;
    frame_ = nullptr;
    fred.done ();
    const int c = ciao ();
    if (res_ < c) res_ = c;
    return res_; }

void app_t::nits_msgbox (wxWindow* mummy, const ::std::string& title, nitpick& nits, const e_severity worst)
{   if ((! nits.empty ()) && (nits.worst () <= worst))
    {   long style = wxOK | wxCENTRE;
		switch (nits.worst ())
		{	case es_catastrophic :
			case es_abhorrent :
				style |= wxICON_ERROR;
				break;
			case es_error :
			case es_warning :
				style |= wxICON_WARNING;
				break;
            default :
				style |= wxICON_INFORMATION;
				break; }		
		macro_t mac;
		mac.load_template (nits, html_default, nf_text);
		wxMessageDialog msg (mummy, mac.report (nits).c_str (), title.c_str (), style);
		msg.ShowModal (); } }

bool app_t::load_conf (wxWindow* mummy, context_t& ct, ::boost::filesystem::path& fn)
{   wxFileDialog dialogue (mummy, "Load Configuration",
        fn.string().c_str (), DEF_CONF_FILE, DEF_CONF_WILD, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dialogue.ShowModal () == wxID_OK)
    {   nitpick nits ("configuration load");
        ::boost::filesystem::path f2 (fn);
        f2 = ::std::string (dialogue.GetPath ().c_str ());
        context_t c (nits, f2);
        if (! nits.empty ()) app_t::nits_msgbox (mummy, "Load...", nits, es_error);
        if (nits.worst () > es_error)
        {   ct = c;
            fn = f2;
            return true; } }
    return false; }

bool app_t::save_conf (wxWindow* mummy, context_t& c, const ::boost::filesystem::path& fn)
{   nitpick nits ("configuration save");
    if (! c.write (nits, fn))
	{   if (! nits.empty ()) app_t::nits_msgbox (mummy, "Saving...", nits);
        return false; }
    return true; }

bool app_t::save_conf_as (wxWindow* mummy, context_t& c, ::boost::filesystem::path& fn)
{   wxFileDialog dialogue (mummy, "Save Configuration",
        fn.string().c_str (), "config.conf", "Configuration files (*.conf)|*.conf", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (dialogue.ShowModal () != wxID_OK) return false;
    const ::boost::filesystem::path f2 = ::std::string (dialogue.GetPath ().c_str ());
    if (! save_conf (mummy, c, f2)) return false;
    fn = f2;
    return true; }

#endif // WX
