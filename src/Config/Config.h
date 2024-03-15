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

#ifndef CONFIG_H
#define CONFIG_H

#include <wx/wx.h>

#include <unordered_map>
#include "Utilities/AfxHelper.h"


const wxString version = "4.1.0";

enum class NumberFormatType {
    American,
    European
};

enum class CostingMethod{
    AverageCost,
    fifo
};

enum class StartWeekdayType {
    Sunday,
    Monday
};


class CConfig {
public:
    bool SaveConfig();
    bool LoadConfig();

    wxString GetDataFilesFolder();
    StartWeekdayType GetStartWeekday();
    void SetStartWeekday(StartWeekdayType value);
    CostingMethod GetCostingMethod();
    void SetCostingMethod(CostingMethod value);
    bool GetExcludeNonStockCosts(); 
    void SetExcludeNonStockCosts(bool value);
    NumberFormatType GetNumberFormatType();
    void SetNumberFormatType(NumberFormatType value);
    bool GetDisplayLicense();
    void SetDisplayLicense(bool value);
    void DisplayLicense();
    bool GetAllowUpdateCheck();
    void SetAllowUpdateCheck(bool value);
    bool GetAllowPortfolioDisplay();
    void SetAllowPortfolioDisplay(bool value);
    int GetTickerDecimals(const wxString& underlying);
    void SetTickerDecimals(const wxString& underlying, int decimals);
    wxString GetMultiplier(const wxString& wunderlying);
    void SetMultiplier(const wxString& wunderlying, const wxString& multiplier);
    std::string GetFuturesExchange(const std::string& underlying);
    void SetFuturesExchange(const std::string& underlying, const std::string& exchange);
    wxString GetCategoryDescription(int index);
    void SetCategoryDescription(int index, const wxString& description);
    bool IsFuturesTicker(const wxString& ticker);
    int GetStartupWidth();
    int GetStartupHeight();
    int GetStartupRightPanelWidth();
    void SetStartupWidth(int width);
    void SetStartupHeight(int height);
    void SetStartupRightPanelWidth(int width);


private:
    // Filenames used on and after Version 4.0.0
    wxString dbConfig_new = L"\\tt-config.txt";
    wxString exe_new = L"\\TradeTracker.exe";

    wxString dbConfig;

    int startup_width = 0;
    int startup_height = 0;
    int startup_right_panel_width = 0;

    bool display_open_source_license = true;
    bool show_portfolio_value = true;
    bool allow_update_check = true;
    bool exclude_nonstock_costs = false;

    NumberFormatType number_format_type = NumberFormatType::American;
    CostingMethod costing_method = CostingMethod::AverageCost;
    StartWeekdayType start_weekday = StartWeekdayType::Monday;

    std::unordered_map<int, wxString> mapCategoryDescriptions{
        { 0, L"Category 0"},
        { 1, L"Category 1" },
        { 2, L"Category 2" },
        { 3, L"Category 3" },
        { 4, L"Category 4" },
        { 5, L"Category 5" },
        { 6, L"Category 6" },
        { 7, L"Category 7" },
        { 8, L"Category 8" },
        { 9, L"Category 9" },
        { 10, L"Category 10" },
        { 11, L"Category 11" },
        { 12, L"Category 12" },
        { 13, L"Category 13" },
        { 14, L"Category 14" },
        { 15, L"Category 15" },
        { 99, L"All Categories" },
        {100, L"Other Income/Expense" }
    };

    std::unordered_map<std::string, std::string> mapFuturesExchanges{
        { "/AUD", "CME" },
        { "/EUR", "CME" },
        { "/GBP", "CME" },
        { "/ES",  "CME" },
        { "/MES", "CME" },
        { "/HE",  "CME" },
        { "/LE",  "CME" },
        { "/GC",  "COMEX" },
        { "/HG",  "COMEX" },
        { "/NG",  "NYMEX" },
        { "/CL",  "NYMEX" },
        { "/MCL", "NYMEX" },
        { "/ZB",  "CBOT" },
        { "/ZC",  "CBOT" },
        { "/ZS",  "CBOT" }
    };

    std::unordered_map<wxString, wxString> mapMultipliers{
        { L"/AUD", L"100000" },
        { L"/EUR", L"125000" },
        { L"/GBP", L"62500" },
        { L"/ES",  L"50" },
        { L"/MES", L"5" },
        { L"/CL",  L"1000" },
        { L"/HE",  L"400" },
        { L"/LE",  L"400" },
        { L"/HG",  L"25000" },
        { L"/ZB",  L"1000" }
    };

    std::unordered_map<wxString, int> mapTickerDecimals{
        { L"/AUD", 5 },
        { L"/EUR", 5 },
        { L"/GBP", 4 },
        { L"/ZB", 3 },
        { L"/ZC", 3 },
        { L"/LE", 3 },
        { L"/HE", 4 },
        { L"/ZS", 4 }
    };
    
};

extern CConfig config;

#endif CONFIG_H
