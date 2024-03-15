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

#ifndef AFXHELPER_H
#define AFXHELPER_H

#include <wx/wx.h>

std::vector<wxString> AfxSplit(const wxString& input, wchar_t delimiter);
wxString AfxLTrim(const wxString& s);
wxString AfxReplace(const wxString& str, const wxString& from, const wxString& to);

int AfxValInteger(const wxString& st);
double AfxValDouble(const wxString& st);


wxString AfxInsertDateHyphens(const wxString& date_string);

wxString AfxGetExePath();


#if 0

#include <Windows.h>
#include <commctrl.h>
#include <string>


wxString AfxClean(const wxString& text);

bool AfxCreateNestedFolder(const wxString& folderPath);
wxString AfxGetProgramFilesFolder();
wxString AfxGetLocalAppDataFolder();
wxString AfxExecCmd(const wxString& cmd);

void AfxCenterWindow(HWND hwnd = NULL, HWND hwndParent = NULL);
void AfxCenterWindowMonitorAware(HWND hwnd = NULL, HWND hwndParent = NULL);


wxString AfxCurrentDate();
std::string AfxInsertDateHyphens(const std::string& date_string);
bool AfxIsLeapYear(int year);
int AfxDaysInMonth(int month, int year);
int AfxDaysInMonthISODate(const wxString& date_text);
wxString AfxShortDate(const wxString& date_text);
wxString AfxGetShortMonthName(const wxString& date_text);
wxString AfxGetLongMonthName(const wxString& date_text);
wxString AfxGetShortDayName(const wxString& date_text);
wxString AfxGetLongDayName(const wxString& date_text);
wxString AfxMakeISODate(int year, int month, int day);
wxString AfxFormatFuturesDate(const wxString& date_text);
std::string AfxFormatFuturesDateMarketData(const wxString& date_text);
int AfxGetYear(const wxString& date_text);
int AfxGetMonth(const wxString& date_text);
int AfxGetDay(const wxString& date_text);
int AfxLocalYear();
int AfxLocalMonth();
int AfxLocalDay();
int AfxLocalDayOfWeek();
int AfxDateWeekday(int day, int month, int year);
unsigned int AfxUnixTime(const wxString& date_text);
int AfxDaysBetween(const wxString& date1, const wxString& date2);
wxString AfxDateAddDays(const wxString& date_text, int num_days_to_add);
wxString AfxLongDate(const wxString& date_text);


std::string unicode2ansi(const wxString& wstr);
wxString ansi2unicode(const std::string& str);
wxString AfxMoney(double value, bool use_minus_sign = true, int num_decimal_places = 2);
bool AfxStringCompareI(const std::string& s1, const std::string& s2);
bool AfxWStringCompareI(const wxString& s1, const wxString& s2);
bool AfxFileExists(const wxString& wszFileSpec);
wxString AfxRemove(const wxString& text, const wxString& repl);
wxString AfxRTrim(const wxString& s);
wxString AfxTrim(const wxString& s);
wxString AfxUpper(const wxString& text);
wxString AfxLower(const wxString& text);
wxString AfxRSet(const wxString& text, int width);
std::string AfxRSet(const std::string& text, int width);
wxString AfxLSet(const wxString& text, int width);

#endif

#endif //AFXHELPER_H

