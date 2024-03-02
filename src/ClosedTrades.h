#ifndef SRC_CLOSEDTRADES_H
#define SRC_CLOSEDTRADES_H

#include <wx/wx.h>

class ClosedTrades : public wxPanel {
public:
    ClosedTrades( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,	long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr );

};


#endif  /* SRC_CLOSEDTRADES_H */
