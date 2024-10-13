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
class frame_t;

class output_t : public wxTextCtrl
{   ::std::size_t found_ = 0, max_ = 0;
    ::boost::filesystem::path file_;
    ::std::string find_;
    int fussitudes_ = 0;
    bool save_file (frame_t* frame);
    ::std::string presearch ();
    ::std::string pre () const;
    DECLARE_EVENT_TABLE ();
public:
    output_t () = delete;
    output_t (wxWindow *mummy);
    output_t (const output_t& o) = delete;
    output_t (output_t&& o) = delete;
    ~output_t () = default;
    output_t& operator = (const output_t& o) = delete;
    output_t& operator = (output_t&& o) = delete;
    void append (const ::std::string& text);
    void clear ();
    void OnCopy (wxCommandEvent& e);
    void FileSave (frame_t* frame);
    void Find (const ::std::string& wot, const int fussitudes);
    void OnHelp (wxCommandEvent& e);
    void Preview (wxHtmlEasyPrinting* print);
    void Next ();
    void Print (wxHtmlEasyPrinting* print);
    void Prior ();
    void FileSaveAs (frame_t* frame);
    void OnSelectAll (wxCommandEvent& e);
    void OnUpdateCopy (wxUpdateUIEvent& e);
    void OnUpdateSelectAll (wxUpdateUIEvent& e);
    void OnUpdate (wxCommandEvent& e); };

#endif // WX
