#include <wx/wx.h>
#include <wx/splitter.h>

#include "ActiveTrades.h"
#include "ClosedTrades.h"
#include "Transactions.h"
#include "TradeHistory.h"
#include "TickerTotals.h"
#include "JournalNotes.h"
#include "TradePlan.h"
#include "TabPanel.h"
#include "MainWindow.h"

MainWindow::MainWindow(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    splitter = new wxSplitterWindow(this, wxID_ANY,
        wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

    active_trades_panel = new ActiveTrades(splitter);
    closed_trades_panel = new ClosedTrades(splitter);
    transactions_panel = new Transactions(splitter);
    trade_history_panel = new TradeHistory(splitter);
    ticker_totals_panel = new TickerTotals(splitter);
    journal_notes_panel = new JournalNotes(splitter);
    trade_plan_panel = new TradePlan(splitter);
    tab_panel = new TabPanel(this, wxID_ANY, wxDefaultPosition, wxWindow::FromDIP(wxSize(500,36)));

    current_left_panel = active_trades_panel;
    current_right_panel = trade_history_panel;

    splitter->SetMinimumPaneSize(wxWindow::FromDIP(200));
    splitter->SetSashGravity(1);
    splitter->SplitVertically(current_left_panel, current_right_panel);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(splitter, 1, wxEXPAND);
    sizer->Add(tab_panel, 0, wxEXPAND);

    this->SetSizerAndFit(sizer);
}

void MainWindow::SetLeftPanel(wxPanel* new_left_panel) {
    splitter->ReplaceWindow(current_left_panel, new_left_panel);
    current_left_panel->Hide();
    new_left_panel->Show();
    current_left_panel = new_left_panel;
}

void MainWindow::SetRightPanel(wxPanel* new_right_panel) {
    splitter->ReplaceWindow(current_right_panel, new_right_panel);
    current_right_panel->Hide();
    new_right_panel->Show();
    current_right_panel = new_right_panel;
}
