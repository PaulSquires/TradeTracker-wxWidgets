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

#include <wx/wx.h>
#include <wx/splitter.h>

#include "MainWindow.h"


CMainWindow::CMainWindow(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    splitter = new wxSplitterWindow(this, wxID_ANY,
        wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

    active_trades_panel = new CActiveTrades(splitter);
    closed_trades_panel = new CClosedTrades(splitter);
    transactions_panel  = new CTransactions(splitter);
    trade_history_panel = new CTradeHistory(splitter);
    ticker_totals_panel = new CTickerTotals(splitter);
    journal_notes_panel = new CJournalNotes(splitter);
    trade_plan_panel    = new CTradePlan(splitter);
    tab_panel           = new CTabPanel(this, wxID_ANY, wxDefaultPosition, wxWindow::FromDIP(wxSize(500,36)));

    current_left_panel  = active_trades_panel;
    current_right_panel = trade_history_panel;

    splitter->SetMinimumPaneSize(wxWindow::FromDIP(200));
    splitter->SetSashGravity(1);
    splitter->SplitVertically(current_left_panel, current_right_panel);
    tab_panel->SetSelectedLinkButton(id_active_trades);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(splitter, 1, wxEXPAND);
    sizer->Add(tab_panel, 0, wxEXPAND);

    this->SetSizerAndFit(sizer);

    this->Bind(wxEVT_CLOSE_WINDOW, &CMainWindow::OnClose, this);
}


void CMainWindow::OnClose(wxCloseEvent& event) {
    // Hide the main window just prior to the destroy in order
    // to avoid seeing a flash from the window being destroyed.
    this->Hide();

    // you may also do:  event.Skip();
    // since the default event handler does call Destroy(), too
    //Destroy();  
    event.Skip();
}


void CMainWindow::SetLeftPanel(wxPanel* new_left_panel) {
    splitter->ReplaceWindow(current_left_panel, new_left_panel);
    current_left_panel->Hide();
    new_left_panel->Show();
    current_left_panel = new_left_panel;
}


void CMainWindow::SetRightPanel(wxPanel* new_right_panel) {
    splitter->ReplaceWindow(current_right_panel, new_right_panel);
    current_right_panel->Hide();
    new_right_panel->Show();
    current_right_panel = new_right_panel;
}
