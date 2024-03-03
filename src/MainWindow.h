#ifndef SRC_MAINWINDOW_H
#define SRC_MAINWINDOW_H

#include <wx/wx.h>
#include <wx/splitter.h>

class MainWindow : public wxFrame {
public:
    MainWindow(const wxString &title, const wxPoint &pos, const wxSize &size);

    wxSplitterWindow* splitter = nullptr;
    wxPanel* active_trades_panel = nullptr;
    wxPanel* closed_trades_panel = nullptr;
    wxPanel* transactions_panel = nullptr;
    wxPanel* trade_history_panel = nullptr;
    wxPanel* tab_panel = nullptr;
    wxPanel* ticker_totals_panel = nullptr;
    wxPanel* trade_plan_panel = nullptr;
    wxPanel* journal_notes_panel = nullptr;
    wxBoxSizer* sizer = nullptr;

    wxPanel* current_left_panel = nullptr;
    wxPanel* current_right_panel = nullptr;

    void SetLeftPanel(wxPanel* new_left_panel);
    void SetRightPanel(wxPanel* new_right_panel);
};



#endif  /* SRC_MAINWINDOW_H */
