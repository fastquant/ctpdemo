#include <iostream>
#include "ThostFtdcMdApi.h"
#include "mdspi.h"

using namespace std;
char mdFront[] = "tcp://180.168.212.79:31213";
int main()
{
   CThostFtdcMdApi* api = CThostFtdcMdApi::CreateFtdcMdApi();
   MdSpi* spi = new MdSpi(api);
   api->RegisterSpi(spi);
   api->RegisterFront(mdFront);
   api->Init();
   TThostFtdcBrokerIDType	appId = "8000";
   TThostFtdcUserIDType	userId = "40022870";
   TThostFtdcPasswordType passwd = "141537";
 //  ShowMdCommand(spi,true);
    spi->ReqUserLogin(appId,userId,passwd);
   api->Join();
   api->Release();
   delete spi;
}

