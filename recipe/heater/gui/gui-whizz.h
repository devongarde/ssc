/*                                                                 ,
ssc (static site checker)
Copyright (c) 2020-2024 Dylan Harris
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
#include "gui/gui-dialogue.h"
#include "gui/gui-setting.h"

#define WIZZARD_CAPTION "Wizard" // Wizzard Brew

class whizz_t;

template < class SUPER > struct whizz_page : SUPER
{   using SUPER::SUPER;
    wxBoxSizer* box_ = nullptr;
    wxStaticText* static_ = nullptr;
    whizz_t* mummy_ = nullptr;
    bool invalid () const noexcept
    {   return (static_ == nullptr) || (box_ == nullptr); }
    bool create_controls (whizz_t* mummy, const char* sz)
    {	VERIFY_NOT_NULL (sz, __FILE__, __LINE__);
        mummy_ = mummy;
	    box_ = GSL_OWNER (wxBoxSizer) (new wxBoxSizer (wxVERTICAL));
	    if (box_ != nullptr)
	    {	static_ = GSL_OWNER (wxStaticText) (new wxStaticText (this, wxID_ANY, sz, wxDefaultPosition, wxDefaultSize, 0));
		    if (static_ != nullptr)
		    {	static_ -> Wrap (-1);
			    box_ -> Add (static_, 0, wxALL, 5);
			    return true; } }
	    return false; }
    void finish_create ()
    {	SUPER::SetSizer (box_);
	    SUPER::Layout ();
	    box_ -> Fit (this); } };

typedef whizz_page < wxWizardPageSimple > whizz_intro;
typedef whizz_page < wxWizardPageSimple > whizz_end;

struct whizz_ffs : whizz_page < wxWizardPage >
{   using whizz_page::whizz_page;
    wxWizardPage* next_ = nullptr;
    wxWizardPage* prev_ = nullptr;
    virtual void SetNext (wxWizardPage* p) noexcept { next_ = p; }
    virtual void SetPrev (wxWizardPage* p) noexcept { prev_ = p; }
    virtual wxWizardPage* GetNext () const noexcept { return next_; }
    virtual wxWizardPage* GetPrev () const noexcept { return prev_; } };

struct whizz_choice : whizz_ffs
{   using whizz_ffs::whizz_ffs;
    wxRadioBox* radio_choice_ = nullptr;
    bool rooted_ = false;
    bool invalid () const noexcept { return whizz_page :: invalid () || radio_choice_ == nullptr; }
    void arrange_page_order (whizz_t& wiz);
    bool create_controls (whizz_t* mummy, const char* sz);
    void OnChoice (wxCommandEvent& event);
private:
    DECLARE_EVENT_TABLE (); };

struct whizz_root : whizz_ffs
{   using whizz_ffs::whizz_ffs;
    wxDirPickerCtrl* dir_root_ = nullptr;
    bool invalid () const noexcept { return whizz_page :: invalid () || dir_root_ == nullptr; }
    bool create_controls (whizz_t* mummy, const char* sz); };

struct whizz_snippet : whizz_ffs
{   using whizz_ffs::whizz_ffs;
    wxTextCtrl* text_snippet_ = nullptr;
    bool invalid () const noexcept { return whizz_page :: invalid () || text_snippet_ == nullptr; }
    bool create_controls (whizz_t* mummy, const char* sz); };

template < class T > struct pagemaker : T
{   static T* create (T*& p, whizz_t& wz, const char* sz)
    {   p = nullptr;
        T* res = GSL_OWNER (T) (new T (&wz));
        if (res != nullptr)
            if (res -> create_controls (&wz, sz))
                p = res;
        return res; } };

class whizz_t : public whizzo_t
{   DECLARE_CLASS (whizz_t)
    DECLARE_EVENT_TABLE ()
public:
    bool muggle_ = true;
    whizz_choice* choice_ = nullptr;
    whizz_end* end_ = nullptr;
    whizz_intro* intro_ = nullptr;
    whizz_root* root_ = nullptr;
    whizz_snippet* snippet_ = nullptr;
    whizz_t () = default;
    whizz_t (const whizz_t& w) = default;
    whizz_t (whizz_t&& w) = default;
    whizz_t (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = WIZZARD_CAPTION);
    whizz_t& operator = (const whizz_t& w) = default;
    whizz_t& operator = (whizz_t&& w) = default;
    ~whizz_t () { try { Destroy (); } catch (...) { } }
    bool invalid () const noexcept
    {   return muggle_ || (end_ == nullptr) || (end_ -> invalid ()) || 
                          (snippet_ == nullptr) || (snippet_ -> invalid ()) || 
                          (root_ == nullptr) || (root_ -> invalid ()) || 
                          (choice_ == nullptr) || (choice_ -> invalid ()) || 
                          (intro_ == nullptr) || (intro_ -> invalid ()); }
    void Init () noexcept { }
    bool Create (wxWindow *mummy, wxWindowID id = wxID_ANY, const wxString& caption = WIZZARD_CAPTION);
    void CreateControls ();
    void OnCancel (wxWizardEvent& event);
    void OnChanged (wxWizardEvent& event);
    void OnChanging (wxWizardEvent& event);
    void OnDone (wxWizardEvent& event);
    void OnHelpClick (wxWizardEvent& event);
    bool run ();
    bool TransferDataToWindow ();
    bool TransferDataFromWindow ();
    void set_size (); };

#endif // WX
