#define MIB_IF_TYPE_IEEE80211 71
#include <Windows.h>
#include <iphlpapi.h>
#include <string>
#pragma comment(lib, "iphlpapi.lib")

std::string getWirelessAdapterIPV4Address()
{
    std::string ipAddress = "";
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    DWORD dwRetVal = 0;

    pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL)
    {
        return ipAddress;
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL)
        {
            return ipAddress;
        }
    }
    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
    {
        pAdapter = pAdapterInfo;
        while (pAdapter) {
            if (pAdapter->Type == MIB_IF_TYPE_IEEE80211)
            {
                IP_ADDR_STRING* pIpAddrString = &(pAdapter->IpAddressList);
                while (pIpAddrString) {
                    if (pIpAddrString->IpAddress.String[0] != '0')
                    {
                        ipAddress = pIpAddrString->IpAddress.String;
                        break;
                    }
                    pIpAddrString = pIpAddrString->Next;
                }
                break;
            }
            pAdapter = pAdapter->Next;
        }
    }

    if (pAdapterInfo) {
        free(pAdapterInfo);
    }

    return ipAddress;
}

int main()
{
    printf(getWirelessAdapterIPV4Address().c_str());

    system("pause>nul");

}