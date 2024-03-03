#include <wx/wx.h>

#include "TabPanel.h"
#include "TradeTracker.h"

TabPanel::TabPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    main_window_ptr = (MainWindow*) parent;

    this->SetBackgroundColour(wxColor(100,100,200));

    wxButton* btn_active_trades = new wxButton(this, wxID_ANY, "Active");
	btn_active_trades->Bind(wxEVT_BUTTON, &TabPanel::ActiveTradesClicked, this);

    wxButton* btn_closed_trades = new wxButton(this, wxID_ANY, "Closed");
	btn_closed_trades->Bind(wxEVT_BUTTON, &TabPanel::ClosedTradesClicked, this);

    wxButton* btn_transactions = new wxButton(this, wxID_ANY, "Transactions");
	btn_transactions->Bind(wxEVT_BUTTON, &TabPanel::TransactionsClicked, this);

    wxButton* btn_trade_history = new wxButton(this, wxID_ANY, "TradeHistory");
	btn_trade_history->Bind(wxEVT_BUTTON, &TabPanel::TradeHistoryClicked, this);

    wxButton* btn_ticker_totals = new wxButton(this, wxID_ANY, "TickerTotals");
	btn_ticker_totals->Bind(wxEVT_BUTTON, &TabPanel::TickerTotalsClicked, this);

    wxButton* btn_journal_notes = new wxButton(this, wxID_ANY, "JournalNotes");
	btn_journal_notes->Bind(wxEVT_BUTTON, &TabPanel::JournalNotesClicked, this);

    wxButton* btn_trade_plan = new wxButton(this, wxID_ANY, "TradePlan");
	btn_trade_plan->Bind(wxEVT_BUTTON, &TabPanel::TradePlanClicked, this);

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(btn_active_trades);
    sizer->Add(btn_closed_trades);
    sizer->Add(btn_transactions);
    sizer->Add(btn_trade_history);
    sizer->Add(btn_ticker_totals);
    sizer->Add(btn_journal_notes);
    sizer->Add(btn_trade_plan);

    this->SetSizerAndFit(sizer);

}


void TabPanel::ActiveTradesClicked(wxCommandEvent& event) {
    wxLogDebug("ActiveTrades Clicked");
    main_window_ptr->SetLeftPanel(main_window_ptr->active_trades_panel);
    event.Skip();
}

void TabPanel::ClosedTradesClicked(wxCommandEvent& event) {
    wxLogDebug("ClosedTrades Clicked");
    main_window_ptr->SetLeftPanel(main_window_ptr->closed_trades_panel);
    event.Skip();
}

void TabPanel::TransactionsClicked(wxCommandEvent& event) {
    wxLogDebug("Transactions Clicked");
    main_window_ptr->SetLeftPanel(main_window_ptr->transactions_panel);
    event.Skip();
}

void TabPanel::TradeHistoryClicked(wxCommandEvent& event) {
    wxLogDebug("TradeHistory Clicked");
    main_window_ptr->SetRightPanel(main_window_ptr->trade_history_panel);
    event.Skip();
}

void TabPanel::TickerTotalsClicked(wxCommandEvent& event) {
    wxLogDebug("TickerTotals Clicked");
    main_window_ptr->SetRightPanel(main_window_ptr->ticker_totals_panel);
    event.Skip();
}

void TabPanel::JournalNotesClicked(wxCommandEvent& event) {
    wxLogDebug("JournalNotes Clicked");
    main_window_ptr->SetRightPanel(main_window_ptr->journal_notes_panel);
    event.Skip();
}

void TabPanel::TradePlanClicked(wxCommandEvent& event) {
    wxLogDebug("TradePlan Clicked");
    main_window_ptr->SetRightPanel(main_window_ptr->trade_plan_panel);
    event.Skip();
}

