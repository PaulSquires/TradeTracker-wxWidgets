/*

MIT License

Copyright(c) 2023-2024 Paul Squires

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef TRADE_H
#define TRADE_H

#include <wx/wx.h>
#include <vector>


//  The hierarchy of the data is:
//      Trade
//          |-> Transaction
//                        |-> Legs

//  All open and closed Trades are stored in the global Trades vector. We differentiate
//  between them by iterating the vector and testing the isOpen() boolean method.
//

//#include "Utilities/Colors.h"


typedef long TickerId;

class Transaction;   // forward declare

enum class PutCall {
    Put,
    Call,
    Count,     // used in StrategyButton when toggling state
    Nothing     // always put last for historical reasons saving to database
};

enum class LongShort {
    Long = 0,
    Short,
    Count,
    Nothing
};

enum class Underlying {
    Options,
    Shares,
    Futures,
    Dividend,
    Other,
    Nothing     // always put last for historical reasons saving to database
};

enum class Action {
    STO,
    BTO,
    STC,
    BTC,
    Nothing     // always put last for historical reasons saving to database
};


class Leg {
public:
    bool         isOpen();                 // method to calc if leg quantity is not zero
    int          contract_id = 0;          // Contract ID received from IBKR 
    int          leg_id = 0;               // Unique id for this leg within the Trade (see Trade nextleg_id) 
    int          leg_back_pointer_id = 0;  // If transaction is CLOSE, EXPIRE, ROLL this points back to leg where quantity modified
    int          original_quantity = 0;
    int          open_quantity = 0;
    wxString     expiry_date   = "";
    wxString     strike_price  = "";
    PutCall      put_call      = PutCall::Nothing;
    Action       action        = Action::Nothing;          // STO,BTO,STC,BTC
    Underlying   underlying    = Underlying::Nothing;      // OPTIONS, STOCKS, FUTURES, DIVIDEND, OTHER
    std::shared_ptr<Transaction> trans = nullptr;          // back pointer to transaction that this leg belongs to

    double calculated_leg_cost = 0;        // refer to CalculateLegCosting(). Alternative for position_cost.

    double position_cost  = 0;             // ACB as calculated CalculateLegCosting()
    double market_value   = 0;             // real time data receive via updatePortfolio
    double percentage     = 0;             // real time data receive via updatePortfolio
    double unrealized_pnl = 0;             // real time data receive via updatePortfolio

    double position_cost_tws = 0;          // position cost received from incoming IB/TWS data
    double position_cost_ratio = 0;        // position cost ratio to overall trade acb
    int    listbox_index = -1;             // index of the ownerdraw listbox
};


class Transaction {
public:
    Underlying    underlying  = Underlying::Nothing;      // OPTIONS,STOCKS,FUTURES,DIVIDEND
    wxString      description = "";                       // Iron Condor, Strangle, Roll, Expired, Closed, Exercised, etc
    wxString      trans_date  = "";                       // YYYY-MM-DD
    int           quantity    = 0;
    double        price       = 0;
    double        multiplier  = 0;
    double        fees        = 0;
    double        total       = 0;
    double        share_average_cost = 0;
    Action        share_action = Action::BTO;

    std::vector<std::shared_ptr<Leg>> legs;            //  pointer list for all legs in the transaction
};


class SharesHistory {
public:
    std::shared_ptr<Transaction> trans;
    Action       leg_action = Action::Nothing;
    int          open_quantity = 0;
    double       average_cost  = 0;
};


class Trade {
public:
    bool          is_open   = true;                // false if all legs are closed
    bool          ticker_data_requested = false;   // ticker data already requested
    TickerId      ticker_id = -1;
    wxString      ticker_symbol = "";
    wxString      ticker_name   = "";
    wxString      future_expiry = "";        // YYYYMM of Futures contract expiry
    wxString      notes         = "";     
    int           category      = 0;         // Category number
    int           nextleg_id    = 0;         // Incrementing counter that gets unique ID for legs being generated in TransDetail.    

    int           aggregate_shares   = 0;    // Calculated from all transactions roll-up
    int           aggregate_futures  = 0;    // Calculated from all transactions roll-up
    double        acb_total          = 0;    // adjusted cost base of entire trade (shares + non-shares items)
    double        acb_shares         = 0;    // adjusted cost base for shares/futures (may include/exclude costs like dividends)
    double        acb_non_shares     = 0;    // all non-shares items (dividends, options, etc)
    double        total_share_profit = 0;    // total shares/futures profit/loss (total income less total average costs for all shares transactions in the trade)
    double        trade_bp           = 0;    // Buying Power for the entire trade 
    double        multiplier         = 0;    // Retrieved from Transaction and needed for updatePortfolio real time calculations

    double        ticker_last_price  = 0;
    double        ticker_close_price = 0;
    int           ticker_decimals    = 2;    // upated via data from Config. 

    // Vector holding all the data related to how shares/futures are allocated during a buy/sell. This
    // vector is created during the CalculateAdjustedCostBase method. We use this vector when displaying
    // the Trade history.
    std::vector<SharesHistory> shares_history;
    void AddSharesHistory(std::shared_ptr<Transaction> trans, Action leg_action, int open_quantity, double average_cost);
    void CalculateTotalSharesProfit();

    // The earliest DTE from the Legs of the Trade are calculated in the SetTradeOpenStatus() function
    // and is used when displaying ActiveTrades with the ExpiryDate filter set.
    int earliest_legs_DTE = 9999999;

    // The following are string representations of the marketdata and updatePortfolio values. We save them here
    // so that the Active Trades lists gets visually updated immediately after a new Trade or close trade.
    // The ticker data would not be updated until a new price occurs so we simply display the most recent price
    // rather than blank text.
    wxString itm_text = "";
//    DWORD itm_color = COLOR_WHITELIGHT;

    wxString ticker_column_1;
    wxString ticker_column_2;
    wxString ticker_column_3;
    
    DWORD ticker_column_1_clr{};
    DWORD ticker_column_2_clr{};
    DWORD ticker_column_3_clr{};

    // Dates used to calculate ROI on TradeBP.
    wxString  bp_start_date = L"99999999";            // YYYYMMDD  First transaction date
    wxString  bp_end_date = L"00000000";              // YYYYMMDD  Last trans expiry date or trade close date if earlier) 
    wxString  oldest_trade_trans_date = L"00000000";  // If Trade is closed then this trans will be the BPendDate

    std::vector<std::shared_ptr<Transaction>> transactions;     // pointer list for all transactions in the trade
    std::vector<std::shared_ptr<Leg>> open_legs;                // sorted list of open legs for this trade

    void SetTradeOpenStatus();
    void CalculateAdjustedCostBase();
    void CreateOpenLegsVector();
};


// pointer list for all trades (initially loaded from database)
extern std::vector<std::shared_ptr<Trade>> trades;

#endif //TRADE_H

