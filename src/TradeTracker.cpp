#include <wx/wx.h>

#include "TradeTracker.h"
#include "resource/mainicon.xpm"
#include "MainWindow.h"

wxIMPLEMENT_APP(TradeTracker);

bool TradeTracker::OnInit()
{
    MainFrame = new MainWindow("TradeTracker-wxWidgets", wxDefaultPosition, wxDefaultSize);
    MainFrame->SetIcon(wxIcon("mainicon"));
    MainFrame->SetClientSize(MainFrame->FromDIP(wxSize(800, 600)));
    MainFrame->Show(true);
    return true;

}

