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

    link_buttons = {
        {id_active_trades, {"Active Trades", true,  main_window_ptr->active_trades_panel, nullptr}},
        {id_closed_trades, {"Closed Trades", true,  main_window_ptr->closed_trades_panel, nullptr}},
        {id_transactions,  {"Transactions",  true,  main_window_ptr->transactions_panel,  nullptr}},
        {id_ticker_totals, {"Ticker Totals", false, main_window_ptr->ticker_totals_panel, nullptr}},
        {id_journal_notes, {"Journal Notes", false, main_window_ptr->journal_notes_panel, nullptr}},
        {id_trade_plan,    {"Trade Plan",    false, main_window_ptr->trade_plan_panel,    nullptr}}
    };


    int left = this->FromDIP(10);
    int width = 0;
    int height = this->FromDIP(54);
    int margin = 20;
    int vertline_panel_width = this->FromDIP(7);

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);

    for (auto& [id, btn] : link_buttons) {
        width = GetTextExtent(btn.label_text).x + margin;
        btn.button_ptr = new TabPanelLinkButton(this, id, btn.label_text, wxPoint(left,0), wxSize(width,height));
        sizer->Add(btn.button_ptr);
        left += width;
        auto vertline_ptr = new TabPanelVerticalLine(this, wxPoint(left,0), wxSize(vertline_panel_width,height));
        sizer->Add(vertline_ptr);
        left += vertline_panel_width;
    }

    this->SetSizer(sizer);

}


void TabPanel::SetSelectedLinkButton(const wxWindowID id_clicked) {
    for (auto& [id, btn] : this->link_buttons) {
        btn.button_ptr->is_selected = false;
        if (btn.button_ptr->GetId() == id_clicked) btn.button_ptr->is_selected = true;
        btn.button_ptr->Refresh();
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
    auto& btn = this->tab_panel_ptr->link_buttons.at(e.GetId());
    btn.is_left_panel ?
        main_window_ptr->SetLeftPanel(btn.panel) : main_window_ptr->SetRightPanel(btn.panel);
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
