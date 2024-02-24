#include <wx/wx.h>

#include "TradeTracker.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainWindow* frame = new MainWindow("Hello Everyone!", wxDefaultPosition, wxDefaultSize);
    frame->SetClientSize(frame->FromDIP(wxSize(800, 600)));
    frame->Show(true);
    return true;
}

