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

struct wx_css { CONSTEXPR static char const* sz () { return "CSS"; } };
struct wx_default { CONSTEXPR static char const* sz () { return "welcome"; } };
struct wx_general { CONSTEXPR static char const* sz () { return "general"; } };
struct wx_html { CONSTEXPR static char const* sz () { return "HTML"; } };
struct wx_nits { CONSTEXPR static char const* sz () { return "nits"; } };
struct wx_ontology { CONSTEXPR static char const* sz () { return "ontology"; } };
struct wx_shadow { CONSTEXPR static char const* sz () { return "shadow"; } };
struct wx_site { CONSTEXPR static char const* sz () { return "site"; } };
struct wx_snippet { CONSTEXPR static char const* sz () { return "snippet"; } };
struct wx_spell { CONSTEXPR static char const* sz () { return "spell"; } };
struct wx_ssi { CONSTEXPR static char const* sz () { return "SSI"; } };
struct wx_stats { CONSTEXPR static char const* sz () { return "stats"; } };
struct wx_summary { CONSTEXPR static char const* sz () { return "summary"; } };
struct wx_valid { CONSTEXPR static char const* sz () { return "validation"; } };

#define DEF_CAPTION "missing caption"
#define DEF_STYLE   wxDEFAULT_DIALOG_STYLE

template < typename SUPER > struct interrogate : SUPER
{   wxBoxSizer* box_ = nullptr;
    wxButton* cancel_ = nullptr;
    wxButton* help_ = nullptr;
    wxButton* ok_ = nullptr;
    wxPoint point_ = wxDefaultPosition;
    wxSize size_ = wxDefaultSize;
    wxWindow* mummy_ = nullptr;
    interrogate () = default;
    interrogate (const wxPoint& pos, const wxSize& size) : point_ (pos), size_ (size) { }
    ~interrogate () = default;
    bool invalid_panel () const noexcept { return (box_ == nullptr); }
    bool invalid () const noexcept { return invalid_panel () || (cancel_ == nullptr); }
    void pre_create (wxWindow *mummy, const wxPoint& pos, const wxSize& size)
    {	VERIFY_NULL (mummy_, __FILE__, __LINE__);
        mummy_ = mummy;
        if (point_ == wxDefaultPosition) point_ = pos;
        if (size_ == wxDefaultSize) size_ = size;
        if (mummy != nullptr) mummy_ -> SetSizeHints (size_, size_); }
    bool preCreate (wxWindow *mummy, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, const long style)
    {	pre_create (mummy, pos, size);
        return wxDialog :: Create (mummy, id, caption, point_, size_, style); }
    void OnClose (const wxPoint point, const wxSize size) noexcept
    {   interrogate < wxDialog > :: OnClose (point);
        size_ = size; } };

template < class NAME > struct d1_t : interrogate < wxDialog >
{   wxStdDialogButtonSizer* sbs_ = nullptr;
    wxPanel* panel_ = nullptr;
    d1_t () = default;
    d1_t (const wxPoint& pos, const wxSize& size) : interrogate < wxDialog > (pos, size) { }
    ~d1_t () = default;
    wxPanel* panel () { return panel_; }
    bool create_panel_itself (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, const long style = DEF_STYLE)
    {   panel_ = GSL_OWNER (wxPanel) (new wxPanel (mummy, id, pos, size, style));
        return (panel_ != nullptr); }
    bool invalid_panel () const noexcept { return interrogate < wxDialog > :: invalid_panel (); }
    bool invalid () const noexcept { return invalid_panel () || (sbs_ == nullptr); }
    void create_box (wxWindow *mummy, const wxPoint& pos, const wxSize& size);
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = DEF_CAPTION,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, const long style = DEF_STYLE);
    void CreateBox ();
    void CreateButtons (const int bs = 1, wxBoxSizer* box = nullptr);
    ::std::string summary (const e_gui_report ) const { return ::std::string (); }
    static const ::std::string name () { return NAME::sz (); } };

template < class NAME > void d1_t < NAME > :: create_box (wxWindow *mummy, const wxPoint& pos, const wxSize& size)
{   VERIFY_NOT_NULL (mummy, __FILE__, __LINE__);
    pre_create (mummy, pos, size);
    box_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxVERTICAL)); }

template < class NAME > bool d1_t < NAME > :: Create (wxWindow *mummy, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, const long style)
{	if (! preCreate (mummy, id, caption, pos, size, style)) return false;
    CreateBox ();
    return true; }

template < class NAME > void d1_t < NAME > :: CreateBox ()
{	box_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxVERTICAL));
    if (box_ != nullptr)
    {	sbs_ = GSL_OWNER (wxStdDialogButtonSizer) (new wxStdDialogButtonSizer ());
        if (sbs_ != nullptr)
            cancel_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_CANCEL)); } }

template < class NAME > void d1_t < NAME > :: CreateButtons (const int bs, wxBoxSizer* box)
{	if (invalid ()) return;
    sbs_ -> AddButton (cancel_);
    help_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_HELP));
    if (help_ != nullptr)
    {   sbs_ -> AddButton (help_);
        ok_ = GSL_OWNER (wxButton) (new wxButton (this, wxID_OK));
        if (ok_ != nullptr)
        {   sbs_ -> AddButton (ok_);
            sbs_ -> Realize ();
            if (box == nullptr) box_ -> Add (sbs_, bs, wxEXPAND, 1);
            else box -> Add (sbs_, bs, wxEXPAND, 1); } } }

struct d2_t : interrogate < wxDialog >
{   wxButton* about_ = nullptr;
    wxGridSizer* grid_ = nullptr;
    d2_t () = default;
    d2_t (const wxPoint& pos, const wxSize& size) : interrogate < wxDialog > (pos, size) { }
    ~d2_t () = default;
    bool invalid () const noexcept { return interrogate < wxDialog > :: invalid () || (grid_ == nullptr) || (about_ == nullptr); }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = DEF_CAPTION,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, const long style = DEF_STYLE);
    void CreateBox ();
    void CreateButtons (const int bs = 1); };

struct d3_t : interrogate < wxDialog >
{   wxButton* load_ = nullptr;
    wxButton* save_ = nullptr;
    wxButton* save_as_ = nullptr;
    wxGridSizer* grid_ = nullptr;
    wxGridSizer* grid_ls_ = nullptr;
    wxStaticLine* divider_ = nullptr;
    d3_t () = default;
    d3_t (const wxPoint& pos, const wxSize& size) : interrogate < wxDialog > (pos, size) { }
    ~d3_t () = default;
    bool invalid () const noexcept { return interrogate < wxDialog > :: invalid () || (grid_ == nullptr) || (load_ == nullptr); }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = DEF_CAPTION,
        const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, const long style = DEF_STYLE);
    void CreateBox ();
    void CreateButtons (const int bs = 1); };
#endif // WX
