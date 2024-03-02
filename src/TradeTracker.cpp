#include <wx/wx.h>

#include "TradeTracker.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(TradeTracker);

bool TradeTracker::OnInit()
{
    MainWindow* frame = new MainWindow("TradeTracker-wxWidgets", wxDefaultPosition, wxDefaultSize);
    frame->SetClientSize(frame->FromDIP(wxSize(800, 600)));
    frame->Show(true);
    return true;
}

