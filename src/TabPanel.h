/*

MIT License

Copyright(c) 2023-2024 Paul Squires

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef TABPANEL_H
#define TABPANEL_H

#include <wx/wx.h>
#include <map>
//#include "MainWindow.h"
//#include "ImageButton.h"


enum ButtonID {
    id_active_trades = wxID_LAST + 1,
    id_closed_trades,
    id_transactions,
    id_journal_notes,
    id_trade_plan,
    id_ticker_totals
};

//class MainWindow;
class TabPanel;

class TabPanelLinkButton : public wxPanel {
public:
    explicit TabPanelLinkButton( TabPanel* parent, wxWindowID id = wxID_ANY, const wxString& label = "",
    const wxPoint& pos = wxDefaultPosition,	const wxSize& size = wxDefaultSize);

    wxString label_text;

    bool is_selected = false;
    bool is_hot = false;

private:
  void OnPaint(wxPaintEvent& e);
  void OnClick(wxMouseEvent& e);
  void OnMouseEnter(wxMouseEvent& e);
  void OnMouseLeave(wxMouseEvent& e);
};


class TabPanelVerticalLine : public wxPanel {
public:
    explicit TabPanelVerticalLine( TabPanel* parent,
      const wxPoint& pos = wxDefaultPosition,	const wxSize& size = wxDefaultSize);

private:
  void OnPaint(wxPaintEvent& e);
};


struct TabPanelLinkButtonStruct {
    wxString label_text;
    bool is_left_panel = true;;
    wxPanel* panel = nullptr;   // the panel to display in main_window splitter
    TabPanelLinkButton* button = nullptr;
};


class TabPanel : public wxPanel {
public:
    explicit TabPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,	long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);

    // wxWindow id is the key
    std::map<int, TabPanelLinkButtonStruct> link_buttons;

    void SetSelectedLinkButton(wxWindowID id);
};


#endif //TABPANEL_H
