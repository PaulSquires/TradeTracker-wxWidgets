#ifndef SRC_TRADETRACKER_H
#define SRC_TRADETRACKER_H

#include <wx/wx.h>
#include "MainWindow.h"

class TradeTracker : public wxApp {
public:
    virtual bool OnInit();

    MainWindow* MainFrame = nullptr;
};


#endif  /* SRC_TRADETRACKER_H */
