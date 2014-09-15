#ifndef MD_SPI_H
#define MD_SPI_H

#include "ThostFtdcMdApi.h"


#include <cinttypes>

enum {
    FTDTypeNone =       0x00,
    FTDTypeFTDC =       0x01,
    FTDTypeCompressed = 0x02
};

enum {
    FTDTagNone =           0x00,
    FTDTagDatetime =       0x01,
    FTDTagCompressMethod = 0x02,
    FTDTagSessionState =   0x03,
    FTDTagKeepAlive =      0x04,
    FTDTagTradedate =      0x05,
    FTDTagTarget =         0x06
};

enum {T_REQ_LOGIN=0x1002,T_RSP_LOGIN=0x1003,T_SETCONFIRM=0x40f,T_QRY_ORDER=0x700,T_QRY_TRADE=0x701,T_QRY_INVPOS=0x702,
T_RSP_INVPOS=0xd,T_QRY_TDACC=0x703,T_RSP_TDACC=0xc,T_QRY_INST=0x717,T_RSP_INST=0x03,T_QRY_MD=0x718,T_RSP_MD=0x12,
T_QRY_TDCODE=0x705,T_QRY_MGR=0x707,T_RSP_MGR=0xe,T_QRY_FEE=0x708,T_RSP_TDCODE=0x7,T_REQ_CANCEL=0x404,T_REQ_ORDINSERT=0x400,
T_RTN_ORDER=0x401,T_RTN_TRADE=0x409,T_REQ_MODPASS=0x304,T_REQ_SUBMD=0x2441,T_QRY_CFMMC=0x2503,T_QRY_SMI=0x70c,
T_REQ_BFT=0x2807,T_RSP_BFT=0x2808,T_QRY_BKYE=0x2819,T_RSP_BKYE=0x300b,T_QRY_BFLOG=0x300d,T_RSP_BFLOG=0x100e,
T_QRY_ACCREG=0x3011,T_RSP_ACCREG=0x3012};
enum {T_SEQ_EXH = 0x30010000,T_SEQ_CTP=0xf1020000};
enum {CHAIN_SINGLE='S',CHAIN_FIRST='F',CHAIN_CENTER='C',CHAIN_LAST='L'};
enum {FTD_HDRLEN=0x1E};

typedef uint8_t FTDCharType;
typedef uint32_t FTDIntType;
typedef uint16_t FTDWordType;

typedef uint8_t FTDType;
typedef uint8_t FTDTag;

struct FtdHdr
{
    FTDType type;
    uint8_t   extHdrLength;
    uint16_t  length;
};

struct FtdExtHdr
{
    FTDTag tagType;
    uint8_t  tagLength;
    char  *data;
};

struct FtdcHdr
{
    uint8_t Version;
    uint32_t TransactionId;
    char Chain;
    uint16_t SequenceSeries;
    uint32_t SequenceNumber;
    uint16_t FieldCount;
    uint16_t FTDCContentLength;
};

struct FtdcDataEntry
{
    uint32_t FieldId;
    uint16_t FieldLength;
    char *DataItem;
};

struct FtdMessage
{
    FtdHdr hdr;
    FtdExtHdr extHdr;
};

struct FtdcMessage
{
    FtdcHdr hdr;
    FtdcDataEntry *data;
};

static char ddd[] = { 0x0, 0x6, 0x0, 0x0, 0x7, 0x4, 0x0, 0x0, 0x0, 0x27 };

static char HeartBeat[] = { 0, 2, 0, 0, 5, 0 };

class MdSpi : public ::CThostFtdcMdSpi
{
public:
    MdSpi(CThostFtdcMdApi* api) : pUserApi(api) {};
    virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
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
