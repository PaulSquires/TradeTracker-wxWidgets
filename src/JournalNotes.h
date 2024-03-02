#ifndef SRC_JOURNALNOTES_H
#define SRC_JOURNALNOTES_H

#include <wx/wx.h>

class JournalNotes : public wxPanel {
public:
    JournalNotes( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,	long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr );

};


#endif  /* SRC_JOURNALNOTES_H */
