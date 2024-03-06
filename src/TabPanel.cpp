#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include "TabPanel.h"
#include "MainWindow.h"


TabPanel::TabPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    main_window_ptr = (MainWindow*) parent;

    this->SetBackgroundColour(wxColor(0,0,0));

    size_t left = 10;
    size_t top = 0;
    size_t width = 90;
    size_t height = 36;

    TabPanelLinkButton* btn_active_trades =
    new TabPanelLinkButton(this, id_active_trades, "Active Trades",
        this->FromDIP(wxPoint(left,top)), this->FromDIP(wxSize(width,height)));
    link_buttons.push_back(btn_active_trades);

    left += width;
    width = 90;
    TabPanelLinkButton* btn_closed_trades =
    new TabPanelLinkButton(this, id_closed_trades, "Closed Trades",
        this->FromDIP(wxPoint(left,top)), this->FromDIP(wxSize(width,height)));
    link_buttons.push_back(btn_closed_trades);

    left += width;
    width = 84;
    TabPanelLinkButton* btn_transactions =
    new TabPanelLinkButton(this, id_transactions, "Transactions",
        this->FromDIP(wxPoint(left,top)), this->FromDIP(wxSize(width,height)));
    link_buttons.push_back(btn_transactions);

    left += width;
    width = 84;
    TabPanelLinkButton* btn_ticker_totals =
    new TabPanelLinkButton(this, id_ticker_totals, "Ticker Totals",
        this->FromDIP(wxPoint(left,top)), this->FromDIP(wxSize(width,height)));
    link_buttons.push_back(btn_ticker_totals);

    left += width;
    width = 90;
    TabPanelLinkButton* btn_journal_notes =
    new TabPanelLinkButton(this, id_journal_notes, "Journal Notes",
        this->FromDIP(wxPoint(left,top)), this->FromDIP(wxSize(width,height)));
    link_buttons.push_back(btn_journal_notes);

    left += width;
    width = 76;
    TabPanelLinkButton* btn_trade_plan =
    new TabPanelLinkButton(this, id_trade_plan, "Trade Plan",
        this->FromDIP(wxPoint(left,top)), this->FromDIP(wxSize(width,height)));
    link_buttons.push_back(btn_trade_plan);

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(btn_active_trades);
    sizer->Add(btn_closed_trades);
    sizer->Add(btn_transactions);
    sizer->Add(btn_ticker_totals);
    sizer->Add(btn_journal_notes);
    sizer->Add(btn_trade_plan);

    this->SetSizer(sizer);

}


void TabPanel::SetSelectedLinkButton(wxWindowID id) {
    for (auto item : this->link_buttons) {
        item->is_selected = false;
        if (item->GetId() == id) item->is_selected = true;
        item->Refresh();
    }
}


TabPanelLinkButton::TabPanelLinkButton(TabPanel* parent, wxWindowID id, const wxString& label,
    const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    main_window_ptr = parent->main_window_ptr;
    tab_panel_ptr = (TabPanel*) parent;

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    label_text = label;

	this->Bind(wxEVT_PAINT, &TabPanelLinkButton::OnPaint, this);
	this->Bind(wxEVT_LEFT_DOWN, &TabPanelLinkButton::OnClick, this);
	this->Bind(wxEVT_ENTER_WINDOW, &TabPanelLinkButton::OnMouseEnter, this);
	this->Bind(wxEVT_LEAVE_WINDOW, &TabPanelLinkButton::OnMouseLeave, this);
}


void TabPanelLinkButton::OnClick(wxMouseEvent& e) {
    switch (e.GetId()) {
        case id_active_trades:
            main_window_ptr->SetLeftPanel(main_window_ptr->active_trades_panel);
            break;
        case id_closed_trades:
            main_window_ptr->SetLeftPanel(main_window_ptr->closed_trades_panel);
            break;
        case id_transactions:
            main_window_ptr->SetLeftPanel(main_window_ptr->transactions_panel);
            break;
        case id_journal_notes:
            main_window_ptr->SetRightPanel(main_window_ptr->journal_notes_panel);
            break;
        case id_trade_plan:
            main_window_ptr->SetRightPanel(main_window_ptr->trade_plan_panel);
            break;
        case id_ticker_totals:
            main_window_ptr->SetRightPanel(main_window_ptr->ticker_totals_panel);
            break;
    }
    tab_panel_ptr->SetSelectedLinkButton(e.GetId());
    e.Skip();
}


void TabPanelLinkButton::OnMouseEnter(wxMouseEvent& e) {
    this->is_hot = true;
    this->Refresh();
    e.Skip();
}


void TabPanelLinkButton::OnMouseLeave(wxMouseEvent& e) {
    this->is_hot = false;
    this->Refresh();
    e.Skip();
}


void TabPanelLinkButton::OnPaint(wxPaintEvent& e) {
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc) {

        size_t width = GetClientRect().GetWidth();
        size_t height = GetClientRect().GetHeight();

        if (this->is_hot || this->is_selected) {
            gc->SetFont(*wxNORMAL_FONT, this->text_color_selected);
        } else {
            gc->SetFont(*wxNORMAL_FONT, text_color_normal);
        }

        if (this->is_selected) {
            gc->SetBrush(this->back_color_selected);
        } else {
            gc->SetBrush(this->back_color_normal);
        }

        gc->DrawRectangle(0,0,width,height);
        gc->DrawText(this->label_text, 0, 0);

        delete gc;
    }
}

