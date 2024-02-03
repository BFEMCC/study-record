#include <iostream>
#include <Windows.h>
#include <winnt.h>
#include <stdexcept>
typedef NTSTATUS(NTAPI *RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

bool isGreaterEqualWin10()
{
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    RtlGetVersionPtr RtlGetVersion;

    if (ntdll)
    {
        RtlGetVersion = (RtlGetVersionPtr)GetProcAddress(ntdll, "RtlGetVersion");
        if (RtlGetVersion)
        {
            RTL_OSVERSIONINFOW rovi = {sizeof(rovi)};

            if (RtlGetVersion(&rovi) == 0)
            {
                if (rovi.dwMajorVersion == 10 && rovi.dwMinorVersion == 0)
                    return true;
                else
                    return false;
            }
            else
                throw std::runtime_error("Error getting Windows version information");
        }
        else
            throw std::runtime_error("RtlGetVersion failed to get");
    }
    else
        throw std::runtime_error("ntdll.dll is missing");
}
bool isGreaterEqualWin11()
{
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    RtlGetVersionPtr RtlGetVersion;

    if (ntdll)
    {
        RtlGetVersion = (RtlGetVersionPtr)GetProcAddress(ntdll, "RtlGetVersion");
        if (RtlGetVersion)
        {
            RTL_OSVERSIONINFOW rovi = {sizeof(rovi)};

            if (RtlGetVersion(&rovi) == 0)
            {
                if (rovi.dwMajorVersion == 10 &&
                    rovi.dwMinorVersion == 0 &&
                    rovi.dwBuildNumber >= 22000)
                    return true;
                else
                    return false;
            }
            else
                throw std::runtime_error("Error getting Windows version information");
        }
        else
            throw std::runtime_error("RtlGetVersion failed to get");
    }
    else
        throw std::runtime_error("ntdll.dll is missing");
}

DWORD getwindowbuild()
{
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    RtlGetVersionPtr RtlGetVersion;

    if (ntdll)
    {
        RtlGetVersion = (RtlGetVersionPtr)GetProcAddress(ntdll, "RtlGetVersion");
        if (RtlGetVersion)
        {
            RTL_OSVERSIONINFOW rovi = {sizeof(rovi)};

            if (RtlGetVersion(&rovi) == 0)
                return rovi.dwBuildNumber;
            else
                throw std::runtime_error("Error getting Windows version information");
        }
        else
            throw std::runtime_error("RtlGetVersion failed to get");
    }
    else
        throw std::runtime_error("ntdll.dll is missing");
}

int main()
{
    // std::cout << isGreaterEqualWin10() << std::endl;
    // std::cout << isGreaterEqualWin11() << std::endl;
    std::cout << getwindowbuild() << std::endl;


    system("pause");
    return 0;
}
// https://www.cnblogs.com/xenophon/p/6093780.html