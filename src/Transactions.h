#ifndef SRC_TRANSACTIONS_H
#define SRC_TRANSACTIONS_H

#include <wx/wx.h>

class Transactions : public wxPanel {
public:
    Transactions( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,	long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr );

};


#endif  /* SRC_TRANSACTIONS_H */
