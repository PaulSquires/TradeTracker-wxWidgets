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
#include <wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/gbsizer.h>

#include "Colors.h"
#include "ImageButton.h"
#include "TabPanel.h"
#include "MainWindow.h"


void CreateImageButtons(TabPanel* parent, wxBoxSizer* sizer) {
    int width = parent->FromDIP(26);
    int height = parent->FromDIP(26);
    int top_padding = parent->FromDIP(5);
    int left_spacer = parent->FromDIP(10);
    int right_spacer = parent->FromDIP(5);

    ImageButtonStruct image;
    image.image_name = "";
    image.image_size = parent->FromDIP(wxSize(20,20));
    image.color_back_normal = Colors_BackDarkBlack;
    image.color_back_hot = Colors_BackLightGray;
    image.color_text_normal = Colors_TextLightWhite;
    image.color_text_hot = Colors_TextBrightWhite;

    auto btn = new ImageButton(parent, wxID_ANY, image, wxPoint(0,0), wxSize(width, height));
    sizer->InsertSpacer(0, left_spacer);
    sizer->Add(btn, 0, wxTOP, top_padding);
    sizer->AddSpacer(right_spacer);

    btn = new ImageButton(parent, wxID_ANY, image, wxPoint(0, 0), wxSize(width,height));
    sizer->Add(btn, 0, wxTOP, top_padding);
    sizer->AddSpacer(right_spacer);

    btn = new ImageButton(parent, wxID_ANY, image, wxPoint(0,0), wxSize(width,height));
    sizer->Add(btn, 0, wxTOP, top_padding);
}


void CreateLinkButtons(TabPanel* parent, wxBoxSizer* sizer) {
    auto main_window = (MainWindow*) parent->GetParent();
    parent->link_buttons = {
        {id_active_trades, {"Active Trades", true,  main_window->active_trades_panel, nullptr}},
        {id_closed_trades, {"Closed Trades", true,  main_window->closed_trades_panel, nullptr}},
        {id_transactions,  {"Transactions",  true,  main_window->transactions_panel,  nullptr}},
        {id_ticker_totals, {"Ticker Totals", false, main_window->ticker_totals_panel, nullptr}},
        {id_journal_notes, {"Journal Notes", false, main_window->journal_notes_panel, nullptr}},
        {id_trade_plan,    {"Trade Plan",    false, main_window->trade_plan_panel,    nullptr}}
    };

    int margin = 20;
    int height = parent->FromDIP(54);
    int vertline_panel_width = parent->FromDIP(7);

    int left_spacer = parent->FromDIP(12);
    sizer->AddSpacer(left_spacer);

    for (auto& [id, btn] : parent->link_buttons) {
        int width = parent->GetTextExtent(btn.label_text).x + margin;
        btn.button = new TabPanelLinkButton(parent, id, btn.label_text, wxPoint(0,0), wxSize(width,height));
        sizer->Add(btn.button);
        auto vertline_ptr = new TabPanelVerticalLine(parent, wxPoint(0,0), wxSize(vertline_panel_width,height));
        sizer->Add(vertline_ptr);
    }

}


TabPanel::TabPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                   const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    this->SetBackgroundColour(Colors_BackDarkBlack);

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    CreateImageButtons(this, sizer);
    CreateLinkButtons(this, sizer);
    this->SetSizer(sizer);
}


void TabPanel::SetSelectedLinkButton(wxWindowID id_clicked) {
    for (auto& [id, btn] : this->link_buttons) {
        btn.button->is_selected = false;
        if (btn.button->GetId() == id_clicked) btn.button->is_selected = true;
        btn.button->Refresh();
    }
}


TabPanelLinkButton::TabPanelLinkButton(TabPanel* parent, wxWindowID id, const wxString& label,
    const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    label_text = label;

	this->Bind(wxEVT_PAINT, &TabPanelLinkButton::OnPaint, this);
	this->Bind(wxEVT_LEFT_DOWN, &TabPanelLinkButton::OnClick, this);
	this->Bind(wxEVT_ENTER_WINDOW, &TabPanelLinkButton::OnMouseEnter, this);
	this->Bind(wxEVT_LEAVE_WINDOW, &TabPanelLinkButton::OnMouseLeave, this);
}


void TabPanelLinkButton::OnClick(wxMouseEvent& e) {
    auto panel = (TabPanel*) this->GetParent();
    auto main_window = (MainWindow*) panel->GetParent();

    auto& btn = panel->link_buttons.at(e.GetId());
    btn.is_left_panel ?
        main_window->SetLeftPanel(btn.panel) : main_window->SetRightPanel(btn.panel);
    panel->SetSelectedLinkButton(e.GetId());
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
    this->PrepareDC(dc);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc) {
        int width = GetClientRect().GetWidth();
        int height = GetClientRect().GetHeight();

        if (this->is_hot || this->is_selected) {
            gc->SetFont(*wxNORMAL_FONT, Colors_TextBrightWhite);
        } else {
            gc->SetFont(*wxNORMAL_FONT, Colors_TextMediumWhite);
        }

        if (this->is_selected) {
            gc->SetBrush(Colors_BackDarkGray);
        } else {
            gc->SetBrush(Colors_BackDarkBlack);
        }

        gc->DrawRectangle(0,0,width,height);

        wxCoord text_width;
        wxCoord text_height;
        dc.GetTextExtent(this->label_text, &text_width, &text_height);

        wxCoord text_left = (width-text_width) / 2;
        wxCoord text_top = (height-text_height) / 2;
        gc->DrawText(this->label_text, text_left, text_top);

        if (this->is_selected) {
            wxPen pen{Colors_Green, FromDIP(1)};
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
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

	this->Bind(wxEVT_PAINT, &TabPanelVerticalLine::OnPaint, this);
}


void TabPanelVerticalLine::OnPaint(wxPaintEvent& e) {
    wxAutoBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    dc.Clear();

    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc) {
        int width = GetClientRect().GetWidth();
        int height = GetClientRect().GetHeight();
        gc->SetBrush(Colors_BackDarkBlack);

        gc->DrawRectangle(0,0,width,height);

        wxPen pen{Colors_TextMediumWhite};
        gc->SetPen(pen);
        wxGraphicsPath path = gc->CreatePath();
        wxDouble line_left = (width / 2);
        wxDouble line_top = FromDIP(7);
        path.MoveToPoint(line_left, line_top);
        path.AddLineToPoint(line_left, line_top+FromDIP(22));
        gc->StrokePath(path);

        delete gc;
    }
}
