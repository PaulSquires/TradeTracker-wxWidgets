#include <wx/wx.h>

class TabPanel : public wxPanel {
public:
    TabPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,	long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr);

};

