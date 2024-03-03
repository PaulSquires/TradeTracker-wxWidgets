#ifndef SRC_TABPANEL_H
#define SRC_TABPANEL_H

#include <wx/wx.h>
#include "MainWindow.h"

class TabPanel : public wxPanel {
public:
    TabPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,	long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);

    MainWindow* main_window_ptr = nullptr;
    void ActiveTradesClicked(wxCommandEvent& event);
    void ClosedTradesClicked(wxCommandEvent& event);
    void TransactionsClicked(wxCommandEvent& event);
    void TradeHistoryClicked(wxCommandEvent& event);
    void TickerTotalsClicked(wxCommandEvent& event);
    void JournalNotesClicked(wxCommandEvent& event);
    void TradePlanClicked(wxCommandEvent& event);
};


#endif  /* SRC_TABPANEL_H */
