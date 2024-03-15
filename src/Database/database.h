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

#ifndef DATABASE_H
#define DATABASE_H

#include <wx/wx.h>

//#include "trade.h"


class CDatabase {
public:
	wxString GetJournalNotesText();
	void SetJournalNotesText(const wxString& text);

	wxString GetTradePlanText();
	void SetTradePlanText(const wxString& text);

	wxString PutCallToString(const PutCall e);
	PutCall StringToPutCall(const wxString& text);

	Underlying StringToUnderlying(const wxString& underlying);
	wxString UnderlyingToString(const Underlying e);

	Action StringToAction(const wxString& action);
	Action StringDescriptionToAction(const wxString& action);
	wxString ActionToString(const Action e);
	wxString ActionToStringDescription(const Action e);

	bool LoadDatabase();
	bool SaveDatabase();

private:
	wxString dbFilename = "tt-database.db";
	wxString dbTradePlan = "tt-tradeplan.txt";
	wxString dbJournalNotes = "tt-journalnotes.txt";

	wxString journal_notes_text = "";
	wxString trade_plan_text = "";

};

extern CDatabase db;


#endif DATABASE_H
