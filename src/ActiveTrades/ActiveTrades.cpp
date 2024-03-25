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

#include "Database/trade.h"
#include "ActiveTrades.h"


CActiveTradesListBox::CActiveTradesListBox(
    wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) :
        wxVListBox(parent, id, pos, size, style) {

    // Load the trades into the listbox
    // for (const auto trade : trades ) {
    //     wxString item = trade->ticker_symbol + "  " + trade->ticker_name;
    //     this->listbox->AppendString(item);
    // }

    // Set the number of items in the list box
    this->SetItemCount(trades.size()); 
}


void CActiveTradesListBox::OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const {
    
    // Example custom drawing: drawing items with alternating background colors
    if (n % 2 == 0)
        dc.SetBrush(*wxLIGHT_GREY_BRUSH);
    else
        dc.SetBrush(*wxWHITE_BRUSH);
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(rect);

    wxString text = "Paul Squires";  //GetString(n);
    dc.DrawText(text, rect.GetX() + this->FromDIP(5), rect.GetY() + (rect.GetHeight() - dc.GetCharHeight()) / 2);
}


wxCoord CActiveTradesListBox::OnMeasureItem(size_t n) const {
    // Example: Adjusting item height
    //return this->OnMeasureItem(n) + 10;
    return this->FromDIP(20); 
}


CActiveTrades::CActiveTrades(wxWindow* parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    this->SetBackgroundColour(wxColor(200,100,100));

    this->listbox = new CActiveTradesListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_EXTENDED);

    //this->listbox->SetItemCount(20);

    wxBoxSizer* sizer = nullptr;
    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(this->listbox, 1, wxEXPAND);

    this->SetSizerAndFit(sizer);

    this->ShowActiveTrades();
}


void CActiveTrades::ShowActiveTrades() {
    // Load the trades into the listbox
    // for (const auto trade : trades ) {
    //     wxString item = trade->ticker_symbol + "  " + trade->ticker_name;
    //     this->listbox->AppendString(item);
    // }

}