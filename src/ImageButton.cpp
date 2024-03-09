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

#include "ImageButton.h"

#include "wx/dcsvg.h"

ImageButton::ImageButton(wxWindow* parent, wxWindowID id, const ImageButtonStruct& image,
                         const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, id, pos, size)
{
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->image = image;

	this->Bind(wxEVT_PAINT, &ImageButton::OnPaint, this);
	this->Bind(wxEVT_LEFT_DOWN, &ImageButton::OnClick, this);
	this->Bind(wxEVT_ENTER_WINDOW, &ImageButton::OnMouseEnter, this);
	this->Bind(wxEVT_LEAVE_WINDOW, &ImageButton::OnMouseLeave, this);
}


void ImageButton::OnClick(wxMouseEvent& e) {
    e.Skip();
}


void ImageButton::OnMouseEnter(wxMouseEvent& e) {
    this->is_hot = true;
    this->Refresh();
    e.Skip();
}


void ImageButton::OnMouseLeave(wxMouseEvent& e) {
    this->is_hot = false;
    this->Refresh();
    e.Skip();
}


void ImageButton::OnPaint(wxPaintEvent& e) {
    wxAutoBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    dc.Clear();


    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc) {
        int width = GetClientRect().GetWidth();
        int height = GetClientRect().GetHeight();

        gc->SetBrush(this->image.color_back_normal);
        gc->DrawRectangle(0,0,width,height);

        if (this->is_hot) {
            gc->SetBrush(this->image.color_back_hot);
        } else {
            gc->SetBrush(this->image.color_back_normal);
        }

        gc->DrawRectangle(0,0,width,height);

        // wxCoord text_width;
        // wxCoord text_height;

        // if (this->is_selected) {
        //     wxPen pen{Colors_Green, FromDIP(2)};
        //     gc->SetPen(pen);
        //     wxGraphicsPath path = gc->CreatePath();
        //     wxDouble line_left = text_left;
        //     wxDouble line_top = height - FromDIP(6);
        //     path.MoveToPoint(line_left, line_top);
        //     path.AddLineToPoint(line_left+text_width, line_top);
        //     gc->StrokePath(path);
        // }

        delete gc;
    }
}
