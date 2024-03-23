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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include <wx/splitter.h>

#include "TabPanel/TabPanel.h"
#include "ActiveTrades/ActiveTrades.h"
#include "ClosedTrades/ClosedTrades.h"
#include "Transactions/Transactions.h"
#include "TradeHistory/TradeHistory.h"
#include "TickerTotals/TickerTotals.h"
#include "JournalNotes/JournalNotes.h"
#include "TradePlan/TradePlan.h"

class CTabPanel;

class CMainWindow : public wxFrame {
public:
    CMainWindow(const wxString &title, const wxPoint &pos, const wxSize &size);

    wxSplitterWindow* splitter = nullptr;
    CActiveTrades* active_trades_panel = nullptr;
    CClosedTrades* closed_trades_panel = nullptr;
    CTransactions* transactions_panel = nullptr;
    CTradeHistory* trade_history_panel = nullptr;
    CTabPanel* tab_panel = nullptr;
    CTickerTotals* ticker_totals_panel = nullptr;
    CTradePlan* trade_plan_panel = nullptr;
    CJournalNotes* journal_notes_panel = nullptr;
    wxBoxSizer* sizer = nullptr;

    wxPanel* current_left_panel = nullptr;
    wxPanel* current_right_panel = nullptr;

    void SetLeftPanel(wxPanel* new_left_panel);
    void SetRightPanel(wxPanel* new_right_panel);

private:
    void OnClose(wxCloseEvent& e);

};



#endif //MAINWINDOW_H
