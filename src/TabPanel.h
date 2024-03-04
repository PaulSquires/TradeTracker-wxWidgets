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

    wxColor back_color_normal = wxColor(0,0,0);
    wxColor back_color_selected = wxColor(22,26,27);
    wxColor text_color_normal = wxColor(157,165,180);
    wxColor text_color_selected = wxColor(255,255,255);

private:
  void OnPaint(wxPaintEvent& e);
  void OnClick(wxMouseEvent& e);
  void OnMouseEnter(wxMouseEvent& e);
  void OnMouseLeave(wxMouseEvent& e);
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
