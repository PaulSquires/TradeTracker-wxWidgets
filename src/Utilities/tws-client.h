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

#ifndef TWSCLIENT_H
#define TWSCLIENT_H

#if 0

#include "tws-api/EWrapper.h"
#include "tws-api/EReaderOSSignal.h"
#include "tws-api/EReader.h"

// #include "Utilities/ListBoxData.h"
// #include "TabPanel/TabPanel.h"


class EClientSocket;


class TwsClient : public EWrapper
{
public:

	TwsClient();
	~TwsClient();

public:

	bool Connect(const char* host, int port, int clientId = 0);
	void Disconnect() const;
	bool IsConnected() const;
	bool IsSocketOK() const;
	void WaitForSignal();
	void ProcessMsgs();
	void CancelMarketData(TickerId ticker_id);
//	void RequestMarketData(ListBoxData* ld);
	void CancelPositions();
	void RequestPositions();
	void CancelPortfolioUpdates();
	void RequestPortfolioUpdates();
	void RequestAccountSummary();
	void RequestWshMetaData(int reqId);
	void RequestWshEventData(int reqId, const WshEventData & wshEventData);
	void PingTWS() const;

public:
	// events
#include "tws-api/EWrapper_prototypes.h"

	int client_id = 0;
	bool had_previous_socket_exception = false;
//	ConnectionType connection_type = ConnectionType::tws_data_live;

//private:
	//! [socket_declare]
	EReaderOSSignal m_osSignal{};
	//EClientSocket* const m_pClient{};
	EClientSocket* m_pClient{};
	//! [socket_declare]

	std::unique_ptr<EReader> m_pReader{};
	bool m_extraAuth;
	std::string m_bboExchange;
};


struct TickerData {
	double last_price = 0;
	double open_price = 0;
	double close_price = 0;
};
//extern std::unordered_map<TickerId, TickerData> mapTickerData;


struct PortfolioData {
	Decimal position = 0;
	double market_price = 0;
	double market_value = 0;
	double average_cost = 0;
	double unrealized_pnl = 0;
	double realized_pnl = 0;
};
//extern std::unordered_map<int, PortfolioData> mapPortfolioData;


extern TwsClient client;

void tws_StartMonitorThread();
void tws_EndMonitorThread();
void tws_StartTickerUpdateThread();
void tws_EndTickerUpdateThread();
void tws_UpdateTickersWithScrapedData();
bool tws_Connect();
bool tws_Disconnect();
bool tws_IsConnected();
void tws_CancelMarketData(TickerId ticker_id);
//void tws_RequestMarketData(ListBoxData* ld);
void tws_PerformReconciliation();
void tws_RequestAccountSummary();
void tws_RequestMarketUpdates();
void tws_RequestPositions();
void tws_CancelPositions();
void tws_RequestWshMetaData(int req_id);
void tws_RequestWshEventData(int req_id, const WshEventData& wshEventData);

#endif


#endif //TWSCLIENT_H

