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

#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <wx/wx.h>
#include "Colors.h"


class ImageButton : public wxPanel {
public:
    explicit ImageButton( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& image = "",
    const wxSize& image_size = wxDefaultSize,
    const wxColor& back_normal = Colors_BackDarkBlack, const wxColor& back_hot = Colors_BackDarkGray,
    const wxColor& text_normal = Colors_TextLightWhite, const wxColor& text_hot = Colors_TextBrightWhite,
    const wxPoint& pos = wxDefaultPosition,	const wxSize& size = wxDefaultSize);

    wxString image_name;
    wxColor color_back_normal;
    wxColor color_back_hot;
    wxColor color_text_normal;
    wxColor color_text_hot;
    wxSize image_size;

    bool is_hot = false;

private:
  void OnPaint(wxPaintEvent& e);
  void OnClick(wxMouseEvent& e);
  void OnMouseEnter(wxMouseEvent& e);
  void OnMouseLeave(wxMouseEvent& e);
};


#endif //IMAGEBUTTON_H
