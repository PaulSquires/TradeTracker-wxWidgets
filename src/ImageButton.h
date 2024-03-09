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

struct ImageButtonStruct {
    wxString image_data;
    wxString image_name = "";
    wxSize image_size = wxDefaultSize;
    wxColor color_back_normal = Colors_BackDarkBlack;
    wxColor color_back_hot = Colors_BackDarkGray;
    wxColor color_text_normal = Colors_TextLightWhite;
    wxColor color_text_hot = Colors_TextBrightWhite;
};

class ImageButton : public wxPanel {
public:
    explicit ImageButton(
        wxWindow* parent, wxWindowID id, const ImageButtonStruct& image, const wxPoint& pos, const wxSize& size);

    ImageButtonStruct image;

    bool is_hot = false;
    bool is_selected = false;

private:
  void OnPaint(wxPaintEvent& e);
  void OnClick(wxMouseEvent& e);
  void OnMouseEnter(wxMouseEvent& e);
  void OnMouseLeave(wxMouseEvent& e);
};


#endif //IMAGEBUTTON_H
