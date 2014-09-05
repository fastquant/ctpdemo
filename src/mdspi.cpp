#include <iostream>
#include <vector>
#include "mdspi.h"

using namespace std;
#pragma warning(disable : 4996)

extern int requestId;  
extern HANDLE g_hEvent;

void CtpMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
		int nRequestID, bool bIsLast)
{
  IsErrorRspInfo(pRspInfo);
}

void CtpMdSpi::OnFrontDisconnected(int nReason)
{
  cerr<<" ��Ӧ | �����ж�..." 
    << " reason=" << nReason << endl;
}
		
void CtpMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
  cerr<<" ��Ӧ | ������ʱ����..." 
    << " TimerLapse = " << nTimeLapse << endl;
}

void CtpMdSpi::OnFrontConnected()
{
	cerr<<" ���ӽ���ǰ��...�ɹ�"<<endl;
  SetEvent(g_hEvent);
}

void CtpMdSpi::ReqUserLogin(TThostFtdcBrokerIDType	appId,
	        TThostFtdcUserIDType	userId,	TThostFtdcPasswordType	passwd)
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, appId);
	strcpy(req.UserID, userId);
	strcpy(req.Password, passwd);
	int ret = pUserApi->ReqUserLogin(&req, ++requestId);
  cerr<<" ���� | ���͵�¼..."<<((ret == 0) ? "�ɹ�" :"ʧ��") << endl;	
  SetEvent(g_hEvent);
}

void CtpMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
		CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	if (!IsErrorRspInfo(pRspInfo) && pRspUserLogin)
	{
    cerr<<" ��Ӧ | ��¼�ɹ�...��ǰ������:"
      <<pRspUserLogin->TradingDay<<endl;
	}
  if(bIsLast) SetEvent(g_hEvent);
}

void CtpMdSpi::SubscribeMarketData(char* instIdList)
{
  vector<char*> list;
  char *token = strtok(instIdList, ",");
  while( token != NULL ){
    list.push_back(token); 
    token = strtok(NULL, ",");
  }
  unsigned int len = list.size();
  char** pInstId = new char* [len];  
  for(unsigned int i=0; i<len;i++)  pInstId[i]=list[i]; 
	int ret=pUserApi->SubscribeMarketData(pInstId, len);
  cerr<<" ���� | �������鶩��... "<<((ret == 0) ? "�ɹ�" : "ʧ��")<< endl;
  SetEvent(g_hEvent);
}

void CtpMdSpi::OnRspSubMarketData(
         CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
         CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr<<" ��Ӧ |  ���鶩��...�ɹ�"<<endl;
  if(bIsLast)  SetEvent(g_hEvent);
}

void CtpMdSpi::OnRspUnSubMarketData(
             CThostFtdcSpecificInstrumentField *pSpecificInstrument,
             CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr<<" ��Ӧ |  ����ȡ������...�ɹ�"<<endl;
  if(bIsLast)  SetEvent(g_hEvent);
}

void CtpMdSpi::OnRtnDepthMarketData(
             CThostFtdcDepthMarketDataField *pDepthMarketData)
{
  cerr<<" ���� | ��Լ:"<<pDepthMarketData->InstrumentID
    <<" �ּ�:"<<pDepthMarketData->LastPrice
    <<" ��߼�:" << pDepthMarketData->HighestPrice
    <<" ��ͼ�:" << pDepthMarketData->LowestPrice
    <<" ��һ��:" << pDepthMarketData->AskPrice1 
    <<" ��һ��:" << pDepthMarketData->AskVolume1 
    <<" ��һ��:" << pDepthMarketData->BidPrice1
    <<" ��һ��:" << pDepthMarketData->BidVolume1
    <<" �ֲ���:"<< pDepthMarketData->OpenInterest <<endl;
}

bool CtpMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{	
  bool ret = ((pRspInfo) && (pRspInfo->ErrorID != 0));
  if (ret){
    cerr<<" ��Ӧ | "<<pRspInfo->ErrorMsg<<endl;
  }
  return ret;
}
