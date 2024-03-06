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

    int left = this->FromDIP(10);
    int top = 0;
    int width = 0;
    int height = this->FromDIP(54);
    int margin = 20;
    int vertline_panel_width = this->FromDIP(7);

    wxString label = "Active Trades";
    width = GetTextExtent(label).x + margin;
    TabPanelLinkButton* btn_active_trades =
        new TabPanelLinkButton(this, id_active_trades, label, wxPoint(left,top), wxSize(width,height));
    link_buttons.push_back(btn_active_trades);

    left += width;
    new TabPanelVerticalLine(this, wxPoint(left,top), wxSize(vertline_panel_width,height));

    left += vertline_panel_width;
    label = "Closed Trades";
    width = GetTextExtent(label).x + margin;
    TabPanelLinkButton* btn_closed_trades =
        new TabPanelLinkButton(this, id_closed_trades, label, wxPoint(left,top), wxSize(width,height));
    link_buttons.push_back(btn_closed_trades);

    left += width;
    new TabPanelVerticalLine(this, wxPoint(left,top), wxSize(vertline_panel_width,height));

    left += vertline_panel_width;
    label = "Transactions";
    width = GetTextExtent(label).x + margin;
    TabPanelLinkButton* btn_transactions =
        new TabPanelLinkButton(this, id_transactions, label, wxPoint(left,top), wxSize(width,height));
    link_buttons.push_back(btn_transactions);

    left += width;
    new TabPanelVerticalLine(this, wxPoint(left,top), wxSize(vertline_panel_width,height));

    left += vertline_panel_width;
    label = "Ticker Totals";
    width = GetTextExtent(label).x + margin;
    TabPanelLinkButton* btn_ticker_totals =
        new TabPanelLinkButton(this, id_ticker_totals, label, wxPoint(left,top), wxSize(width,height));
    link_buttons.push_back(btn_ticker_totals);

    left += width;
    new TabPanelVerticalLine(this, wxPoint(left,top), wxSize(vertline_panel_width,height));

    left += vertline_panel_width;
    label = "Journal Notes";
    width = GetTextExtent(label).x + margin;
    TabPanelLinkButton* btn_journal_notes =
        new TabPanelLinkButton(this, id_journal_notes, label, wxPoint(left,top), wxSize(width,height));
    link_buttons.push_back(btn_journal_notes);

    left += width;
    new TabPanelVerticalLine(this, wxPoint(left,top), wxSize(vertline_panel_width,height));

    left += vertline_panel_width;
    label = "Trade Plan";
    width = GetTextExtent(label).x + margin;
    TabPanelLinkButton* btn_trade_plan =
        new TabPanelLinkButton(this, id_trade_plan, label, wxPoint(left,top), wxSize(vertline_panel_width,height));
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

        int width = GetClientRect().GetWidth();
        int height = GetClientRect().GetHeight();

        if (this->is_hot || this->is_selected) {
            gc->SetFont(*wxNORMAL_FONT, this->color_text_selected);
        } else {
            gc->SetFont(*wxNORMAL_FONT, color_text_normal);
        }

        if (this->is_selected) {
            gc->SetBrush(this->color_back_selected);
        } else {
            gc->SetBrush(this->color_back_normal);
        }

        gc->DrawRectangle(0,0,width,height);

        wxCoord text_width;
        wxCoord text_height;
        dc.GetTextExtent(this->label_text, &text_width, &text_height);

        wxCoord text_left = (width-text_width) / 2;
        wxCoord text_top = (height-text_height) / 2;
        gc->DrawText(this->label_text, text_left, text_top);

        if (this->is_selected) {
            wxPen pen{this->color_selected_line, FromDIP(2)};
            gc->SetPen(pen);
            wxGraphicsPath path = gc->CreatePath();
            wxDouble line_left = text_left;
            wxDouble line_top = height - FromDIP(6);
            path.MoveToPoint(line_left, line_top);
            path.AddLineToPoint(line_left+text_width, line_top);
            gc->StrokePath(path);
        }

        delete gc;
    }
}


TabPanelVerticalLine::TabPanelVerticalLine(TabPanel* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    main_window_ptr = parent->main_window_ptr;
    tab_panel_ptr = (TabPanel*) parent;

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

	this->Bind(wxEVT_PAINT, &TabPanelVerticalLine::OnPaint, this);
}


void TabPanelVerticalLine::OnPaint(wxPaintEvent& e) {
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc) {
        int width = GetClientRect().GetWidth();
        int height = GetClientRect().GetHeight();
        gc->SetBrush(this->color_back_normal);

        gc->DrawRectangle(0,0,width,height);

        wxPen pen{this->color_text_normal};
        gc->SetPen(pen);
        wxGraphicsPath path = gc->CreatePath();
        wxDouble line_left = (width / 2);
        wxDouble line_top = FromDIP(6);
        path.MoveToPoint(line_left, line_top);
        path.AddLineToPoint(line_left, line_top+FromDIP(22));
        gc->StrokePath(path);

        delete gc;
    }
}
