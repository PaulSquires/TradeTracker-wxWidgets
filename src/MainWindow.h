#ifndef SRC_MAINWINDOW_H
#define SRC_MAINWINDOW_H

#include <wx/wx.h>
#include <wx/splitter.h>

class MainWindow : public wxFrame {
public:
    MainWindow(const wxString &title, const wxPoint &pos, const wxSize &size);

    wxSplitterWindow* splitter = nullptr;
    wxPanel* left_panel = nullptr;
    wxPanel* right_panel = nullptr;
    wxPanel* bottom_panel = nullptr;
    wxBoxSizer* sizer = nullptr;
};



#endif  /* SRC_MAINWINDOW_H */
