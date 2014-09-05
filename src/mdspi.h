#ifndef MD_SPI_H
#define MD_SPI_H

#include "ThostFtdcMdApi.h"

class MdSpi : public ::CThostFtdcMdSpi
{
public:
    MdSpi(CThostFtdcMdApi* api) : pUserApi(api){};

    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo,
                            int nRequestID, bool bIsLast);

    virtual void OnFrontDisconnected(int nReason);

    virtual void OnHeartBeatWarning(int nTimeLapse);

    virtual void OnFrontConnected();

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

public:
    void ReqUserLogin(TThostFtdcBrokerIDType appId, TThostFtdcUserIDType userId, TThostFtdcPasswordType	passwd);
    void SubscribeMarketData(char* instIdList);
    bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);
private:
    CThostFtdcMdApi* pUserApi;
};

#endif
