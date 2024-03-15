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

#include <wx/wx.h>
#include <wx/file.h>
#include <wx/textfile.h>
#include "wx/string.h"
#include "wx/arrstr.h"

#include <vector>
#include <unordered_map>


// #include "CustomMessageBox/CustomMessageBox.h"
// #include "Utilities/AfxHelper.h"
// #include "Config/Config.h"

#include "trade.h"
#include "database.h"


// ========================================================================================
// Remove all leading whitespace characters from a string
// ========================================================================================
wxString AfxLTrim(const wxString& input) {
    wxString result = input;
    return result.Trim(false);   // left side only (true = right side (default))
}


// ========================================================================================
// Function to split the string to words in a vector separated by the delimiter
// ========================================================================================
std::vector<wxString> AfxSplit(const wxString& input, wchar_t delimiter) 
{
    wxArrayString result = wxSplit(input, delimiter);
    return result;
}


// ========================================================================================
// Convert wstring to integer catching any exceptions
// ========================================================================================
int AfxValInteger(const wxString& st)  {
    int result = 0;
    if (!st.ToInt(&result)) result = 0;
    return result;
}


// ========================================================================================
// Convert wstring to double catching any exceptions
// ========================================================================================
double AfxValDouble(const wxString& st) {
    double result = 0;
    if (!st.ToDouble(&result)) result = 0;
    return result;
}


// ========================================================================================
// Insert embedded hyphen "-" into a date string.
// e.g.  20230728 would be returned as 2023-07-28
// ========================================================================================
wxString AfxInsertDateHyphens(const wxString& date_string) {
    if (date_string.length() != 8) return "";

    wxString new_date = date_string;
    // YYYYMMDD
    // 01234567

    new_date.insert(4, "-");
    // YYYY-MMDD
    // 012345678

    new_date.insert(7, "-");
    // YYYY-MM-DD
    // 0123456789

    return new_date;
}


// ========================================================================================
// Replace one char/string another char/string. Return a copy.
// ========================================================================================
wxString AfxReplace(const wxString& str, const wxString& from, const wxString& to) {
    wxString text_string = str;
    if (str.empty()) return text_string;
    if (from.empty()) return text_string;
    text_string.Replace(from, to, true);
    return text_string;
}



// ========================================================================================
// Returns the path of the program which is currently executing.
// The path name will not contain a trailing backslash.
// ========================================================================================
#ifdef _WIN32
#include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#include <limits.h>
#endif

wxString AfxGetExePath() {
    wxString path;
#ifdef _WIN32
    // The following retrieves the full path *and* exe name and extension.
    std::wstring buffer(MAX_PATH, NULL);
    GetModuleFileName(NULL, (LPWSTR)buffer.c_str(), MAX_PATH);
    // Remove everything after the last trailing backslash
    std::size_t found = buffer.find_last_of(L"/\\");
    path = buffer.substr(0, found);
#elif defined(__linux__) || defined(__APPLE__)
    char buffer[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer));
    if (count != -1) {
        path.assign(buffer, count);
        std::size_t found = buffer.find_last_of("/\\");
        path = buffer.substr(0, found);
    }
#endif
    return path;
}






// Pointer list for all trades (initially loaded from database)
// This variable is accessed via extern in other files that require it.
std::vector<std::shared_ptr<Trade>> trades;


CDatabase::CDatabase() {
    dbFilename = AfxGetExePath() + "/tt-database.db";
    //dbTradePlan = AfxGetExePath() + "/tt-tradeplan.txt";
    //dbJournalNotes = AfxGetExePath() + "/tt-journalnotes.txt";
}


wxString CDatabase::PutCallToString(const PutCall e) {
    if (e == PutCall::Put) return "P";
    if (e == PutCall::Call) return "C";
    return "";
}


PutCall CDatabase::StringToPutCall(const wxString& text) {
    if (text == "P") return PutCall::Put;
    if (text == "C") return PutCall::Call;
    if (text.length() == 0) return PutCall::Nothing;
    return PutCall::Nothing;
}


Underlying CDatabase::StringToUnderlying(const wxString& text) {
    static const std::unordered_map<wxString, Underlying> map = {
        {"0", Underlying::Options}, {"1", Underlying::Shares}, 
        {"2", Underlying::Futures}, {"3", Underlying::Dividend},
        {"4", Underlying::Other}
    };

    if (text.length() == 0) return Underlying::Nothing;

    // Search for an element in the map
    auto it = map.find(text);
    return (it != map.end()) ? it->second : Underlying::Nothing;
}


wxString CDatabase::UnderlyingToString(const Underlying e) {
    return std::to_wstring((int)e);
}


Action CDatabase::StringDescriptionToAction(const wxString& text) {
    static const std::unordered_map<wxString, Action> map = {
        {"STO", Action::STO}, {"BTO", Action::BTO}, 
        {"STC", Action::STC}, {"BTC", Action::BTC},
        {"", Action::Nothing}
    };

    if (text.length() == 0) return Action::Nothing;

    // Search for an element in the map
    auto it = map.find(text);
    return (it != map.end()) ? it->second : Action::Nothing;
}

Action CDatabase::StringToAction(const wxString& text) {
    static const std::unordered_map<wxString, Action> map = {
        {"0", Action::STO}, {"1", Action::BTO}, 
        {"2", Action::STC}, {"3", Action::BTC},
        {"", Action::Nothing}
    };

    if (text.length() == 0) return Action::Nothing;

    // Search for an element in the map
    auto it = map.find(text);
    return (it != map.end()) ? it->second : Action::Nothing;
}


wxString CDatabase::ActionToString(const Action e) {
    return std::to_wstring((int)e);
}

wxString CDatabase::ActionToStringDescription(const Action e) {
    switch (e) {
    case Action::STO: return "STO";
    case Action::BTO: return "BTO";
    case Action::STC: return "STC";
    case Action::BTC: return "BTC";
    case Action::Nothing : return "";
    default: return "";
    } 
}


// ========================================================================================
// Get the JournalNotes text.
// ========================================================================================
wxString CDatabase::GetJournalNotesText() {
    static bool is_journal_notes_loaded = false;

    if (!is_journal_notes_loaded) {
        wxFile db;
        db.Open(dbJournalNotes);

        if (db.IsOpened()) {
            db.ReadAll(&this->journal_notes_text);
            is_journal_notes_loaded = true;
        }
        db.Close();
    }

    return this->journal_notes_text;
}


// ========================================================================================
// Set and save the JournalNotes text.
// ========================================================================================
void CDatabase::SetJournalNotesText(const wxString& text) {
    wxFile db;
    db.Open(dbJournalNotes);

    if (!db.IsOpened()) {
        // CustomMessageBox.Show(
        //     NULL,
        //     "Could not save Journal Notes text to file",
        //     "Warning",
        //     MB_ICONWARNING
        // );
        return;
    }

    db.Write(text);
    db.Close();

    this->journal_notes_text = text;
}


// ========================================================================================
// Get the TradePlan text.
// ========================================================================================
wxString CDatabase::GetTradePlanText() {
    static bool is_trade_plan_loaded = false;

    if (!is_trade_plan_loaded) {
        wxFile db;
        db.Open(dbTradePlan);

        if (db.IsOpened()) {
            db.ReadAll(&this->trade_plan_text);
            is_trade_plan_loaded = true;
        }
        db.Close();
    }

    return this->trade_plan_text;
}


// ========================================================================================
// Set and save the TradePlan text.
// ========================================================================================
void CDatabase::SetTradePlanText(const wxString& text) {
    wxFile db;

    db.Open(dbTradePlan);

    if (!db.IsOpened()) {
        // CustomMessageBox.Show(
        //     NULL,
        //     "Could not save Trade Plan text to file",
        //     "Warning",
        //     MB_ICONWARNING
        //);
        return;
    }

    db.Write(text);
    db.Close();

    this->trade_plan_text = text;
}


bool CDatabase::SaveDatabase() {
    wxFile db;
    if (!db.Exists(dbFilename)) db.Create(dbFilename);

    db.Open(dbFilename);

    if (!db.IsOpened()) {
        // CustomMessageBox.Show(
        //     NULL,
        //     "Could not save trades database",
        //     "Warning",
        //     MB_ICONWARNING
        // );
        return false;
    }

    wxString text;

    text << "// TRADE          T|isOpen|nextleg_id|TickerSymbol|TickerName|FutureExpiry|Category|TradeBP|Notes\n"
         << "// TRANS          X|transDate|description|underlying|quantity|price|multiplier|fees|total|SharesAction\n"
         << "// LEG            L|leg_id|leg_back_pointer_id|original_quantity|open_quantity|expiry_date|strike_price|PutCall|action|underlying\n"
         << "// isOpen:        0:false, 1:true\n"
         << "// FutureExpiry:  YYYYMMDD (do not insert hyphens)\n"
         << "// Category:      0,1,2,3,4, etc (integer value)\n"
         << "// underlying:    0:OPTIONS, 1:SHARES, 2:FUTURES, 3:DIVIDEND, 4:OTHER\n"
         << "// action:        0:STO, 1:BTO, 2:STC, 3:BTC\n"
         << "// Dates are all in YYYYMMDD format with no embedded separators.\n";

    bool prev_trade_was_open = false;

    for (const auto& trade : trades) {
        // Insert a blank line if the trade is open in order to give some visual breathing room
        if (trade->is_open || prev_trade_was_open) text << "\n";
        prev_trade_was_open = trade->is_open;

        text << "T|"
             << wxString(trade->is_open ? "1|" : "0|")
             << trade->nextleg_id << "|"
             << trade->ticker_symbol << "|"
             << trade->ticker_name << "|"
             << AfxReplace(trade->future_expiry, "-", "") << "|"
             << trade->category << "|"
             << wxString::Format("%.0f", trade->trade_bp)  << "|"
             << AfxReplace(trade->notes, "\r\n", "~~") 
             << "\n";

        static wxString p0 = "";
        static wxString p2 = "  ";
        static wxString p4 = "    ";

        for (const auto& trans : trade->transactions) {
            text << (trade->is_open ? p2 : p0) << "X|" 
                 << AfxReplace(trans->trans_date, "-", "") << "|"
                 << trans->description << "|"
                 << UnderlyingToString(trans->underlying) << "|"
                 << trans->quantity << "|"
                 << wxString::Format("%.4f", trans->price) << "|"
                 << wxString::Format("%.4f", trans->multiplier) << "|"
                 << wxString::Format("%.4f", trans->fees) << "|"
                 << wxString::Format("%.4f", trans->total) << "|"
                 << ActionToString(trans->share_action)
                 << "\n";

            for (const auto& leg : trans->legs) {
                 text << (trade->is_open ? p4 : p0) << "L|"
                      << leg->leg_id << "|"
                      << leg->leg_back_pointer_id << "|"
                      << leg->original_quantity << "|"
                      << leg->open_quantity << "|"
                      << AfxReplace(leg->expiry_date, "-", "") << "|"
                      << leg->strike_price << "|"
                      << PutCallToString(leg->put_call) << "|"
                      << ActionToString(leg->action) << "|"
                      << UnderlyingToString(leg->underlying)
                      << "\n";
            }
        }
    }

    db.Write(text);
    db.Close();

    return true;
}


inline static wxString try_catch_wstring(const std::vector<wxString>& st, const int idx) {
    if (idx >= st.size() || idx < 0) return "";
    return st.at(idx);
}


inline static int try_catch_int(const std::vector<wxString>& st, const int idx) {
    wxString text = try_catch_wstring(st, idx);
    return AfxValInteger(text);
}


inline static double try_catch_double(const std::vector<wxString>& st, const int idx) {
    wxString text = try_catch_wstring(st, idx);
    return AfxValDouble(text);
}


bool CDatabase::LoadDatabase() {
    trades.clear();
    trades.reserve(5000);         // reserve space for 5000 trades

    wxTextFile db(dbFilename);
    if (!db.Exists()) db.Create();


std::cout << dbFilename << std::endl;


    db.Open(dbFilename);

    if (!db.IsOpened()) 
        return false;

    std::shared_ptr<Trade> trade;
    std::shared_ptr<Transaction> trans;
    std::shared_ptr<Leg> leg; 

    wxString line;
    wxString text;
    wxString date_text;
    wxString expiry_date;
    
    std::vector<wxString> st;

    size_t line_count = db.GetLineCount();

    for (size_t i = 0; i < line_count; i++) {
        line = db.GetLine(i);

std::cout << line << std::endl;

        if (line.length() == 0) continue;

        // If this is a Comment line then simply iterate to next line.
        if (line.compare(1, 3, "// ") == 0) continue;

        // Trim leading white space
        line = AfxLTrim(line);

        // Tokenize the line into a vector based on the pipe delimiter
        st = AfxSplit(line, '|');

        if (st.empty()) continue;

        // Check for Trades, Trans, and Legs

        if (try_catch_wstring(st, 0) == "T") {
            trade = std::make_shared<Trade>();
            trade->is_open       = (try_catch_wstring(st, 1) == "0") ? false : true;
            trade->nextleg_id    = try_catch_int(st, 2);
            trade->ticker_symbol = try_catch_wstring(st, 3);
            trade->ticker_name   = try_catch_wstring(st, 4);
            date_text            = try_catch_wstring(st, 5);
            trade->future_expiry = AfxInsertDateHyphens(date_text);
            trade->category      = try_catch_int(st, 6);
            trade->trade_bp      = try_catch_double(st, 7);
            text                 = try_catch_wstring(st, 8);
            trade->notes         = AfxReplace(text, "~~", "\r\n");
            
            trades.emplace_back(trade);
            continue;
        }

        if (try_catch_wstring(st, 0) == "X") {
            trans = std::make_shared<Transaction>();
            date_text            = try_catch_wstring(st, 1);
            trans->trans_date    = AfxInsertDateHyphens(date_text);
            trans->description   = try_catch_wstring(st, 2);
            trans->underlying    = StringToUnderlying(try_catch_wstring(st, 3));
            trans->quantity      = try_catch_int(st, 4);
            trans->price         = try_catch_double(st, 5);
            trans->multiplier    = try_catch_double(st, 6);
            trans->fees          = try_catch_double(st, 7);
            trans->total         = try_catch_double(st, 8);
            trans->share_action  = StringToAction(try_catch_wstring(st, 9));
            if (trans->share_action == Action::Nothing) {
                trans->share_action = (trans->total < 0) ? Action::BTO: Action::STO;
            }

            if (trade) {
                // Determine earliest and latest dates for BP ROI calculation.
                if (AfxValDouble(date_text) < AfxValDouble(trade->bp_start_date)) trade->bp_start_date = date_text;
                if (AfxValDouble(date_text) > AfxValDouble(trade->bp_end_date)) trade->bp_end_date = date_text;
                if (AfxValDouble(date_text) > AfxValDouble(trade->oldest_trade_trans_date)) trade->oldest_trade_trans_date = date_text;
                trade->transactions.emplace_back(trans);
            }
            continue;
        }

        if (try_catch_wstring(st, 0) == "L") {
            leg = std::make_shared<Leg>();
            leg->leg_id              = try_catch_int(st, 1);
            leg->leg_back_pointer_id = try_catch_int(st, 2);
            leg->original_quantity   = try_catch_int(st, 3);
            leg->open_quantity       = try_catch_int(st, 4);
            expiry_date              = try_catch_wstring(st, 5);
            leg->expiry_date         = AfxInsertDateHyphens(expiry_date);
            leg->strike_price        = try_catch_wstring(st, 6);
            leg->put_call            = StringToPutCall(try_catch_wstring(st, 7)); 
            leg->action              = StringToAction(try_catch_wstring(st, 8));
            leg->underlying          = StringToUnderlying(try_catch_wstring(st, 9));
            
            if (trans) {
                leg->trans = trans;
                if (trade) {
                    // Determine latest date for BP ROI calculation.
                    if (AfxValDouble(expiry_date) > AfxValDouble(trade->bp_end_date)) trade->bp_end_date = expiry_date;
                }
                trans->legs.emplace_back(leg);
            }
            continue;
        }
    }

    db.Close();


    // Now that the trades have been constructed, create the open position vector based
    // on a sorted list of open legs. We also calculate the ACB for the entire Trade
    // rather than physically storing that value in the database. This allows us to
    // manually edit individual Transactions externally and not have to go through
    // an error prone process of recalculating the ACB with the new change.
    for (auto& trade : trades) {
        if (trade->is_open) {
            trade->CreateOpenLegsVector();
        }
        else {
            // Trade is closed so set the BPendDate to be the oldest transaction in the Trade
            trade->bp_end_date = trade->oldest_trade_trans_date;
        }

        // Calculate the full trade ACB and also the Shares ACB depending on what costing
        // method has been chosen.
        trade->CalculateAdjustedCostBase();
    }

    return true;
}
