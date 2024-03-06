#ifndef SRC_TABPANEL_H
#define SRC_TABPANEL_H

#include <wx/wx.h>
#include <vector>
#include "MainWindow.h"

enum ButtonID {
    id_active_trades = wxID_LAST + 1,
    id_closed_trades,
    id_transactions,
    id_journal_notes,
    id_trade_plan,
    id_ticker_totals
};

class TabPanel;

class TabPanelLinkButton : public wxPanel {
public:
    TabPanelLinkButton( TabPanel* parent, wxWindowID id = wxID_ANY, const wxString& label = "",
    const wxPoint& pos = wxDefaultPosition,	const wxSize& size = wxDefaultSize);

    MainWindow* main_window_ptr = nullptr;
    TabPanel* tab_panel_ptr = nullptr;
    wxString label_text;

    bool is_selected = false;
    bool is_hot = false;

    wxColor color_back_normal = wxColor(0,0,0);
    wxColor color_back_selected = wxColor(22,26,27);
    wxColor color_text_normal = wxColor(157,165,180);
    wxColor color_text_selected = wxColor(255,255,255);
    wxColor color_selected_line = wxColor(72,151,13);

private:
  void OnPaint(wxPaintEvent& e);
  void OnClick(wxMouseEvent& e);
  void OnMouseEnter(wxMouseEvent& e);
  void OnMouseLeave(wxMouseEvent& e);
};


class TabPanelVerticalLine : public wxPanel {
public:
    TabPanelVerticalLine( TabPanel* parent,
      const wxPoint& pos = wxDefaultPosition,	const wxSize& size = wxDefaultSize);

    MainWindow* main_window_ptr = nullptr;
    TabPanel* tab_panel_ptr = nullptr;

    wxColor color_back_normal = wxColor(0,0,0);
    wxColor color_text_normal = wxColor(157,165,180);

private:
  void OnPaint(wxPaintEvent& e);
};


class TabPanel : public wxPanel {
public:
    TabPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,	long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);

    MainWindow* main_window_ptr = nullptr;

    std::vector<TabPanelLinkButton*> link_buttons;

    void SetSelectedLinkButton(wxWindowID id);

};


#endif  /* SRC_TABPANEL_H */
