#ifndef SRC_TICKERTOTALS_H
#define SRC_TICKERTOTALS_H

#include <wx/wx.h>

class TickerTotals : public wxPanel {
public:
    TickerTotals( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,	long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr );

};


#endif  /* SRC_TICKERTOTALS_H */
