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

#include "TabPanel.h"
#include "ActiveTrades.h"
#include "ClosedTrades.h"
#include "Transactions.h"
#include "TradeHistory.h"
#include "TickerTotals.h"
#include "JournalNotes.h"
#include "TradePlan.h"

class TabPanel;

class MainWindow : public wxFrame {
public:
    MainWindow(const wxString &title, const wxPoint &pos, const wxSize &size);

    wxSplitterWindow* splitter = nullptr;
    ActiveTrades* active_trades_panel = nullptr;
    ClosedTrades* closed_trades_panel = nullptr;
    Transactions* transactions_panel = nullptr;
    TradeHistory* trade_history_panel = nullptr;
    TabPanel* tab_panel = nullptr;
    TickerTotals* ticker_totals_panel = nullptr;
    TradePlan* trade_plan_panel = nullptr;
    JournalNotes* journal_notes_panel = nullptr;
    wxBoxSizer* sizer = nullptr;

    wxPanel* current_left_panel = nullptr;
    wxPanel* current_right_panel = nullptr;

    void SetLeftPanel(wxPanel* new_left_panel);
    void SetRightPanel(wxPanel* new_right_panel);
};



#endif //MAINWINDOW_H
