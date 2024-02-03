#include "emcException.h"

emc::emcException::emcException(const std::string& message) :message_(message)
{
}

emc::emcException::emcException(const char* message) :message_(message)
{
}

emc::emcException::emcException(const int& message) :message_(std::to_string(message))
{
}

emc::emcException::emcException(const double& message) :message_(std::to_string(message))
{
}

emc::emcException::emcException(const std::wstring& message) :message_(emc::wstringTostring(message))
{
}

emc::emcException::emcException(const wchar_t* message) :message_(emc::wstringTostring(message))
{
}

#ifdef _UNICODE
void emc::emcException::PopupPrompt(HWND Parent, std::string title)
{
    MessageBox(Parent, emc::stringTowstring(message_).c_str(), emc::stringTowstring(title).c_str(), MB_OK | MB_ICONERROR);
}
#elif  _MBCS
void emc::emcException::PopupPrompt(HWND Parent, std::string title)
{
    MessageBox(Parent, message_.c_str(), title.c_str(), MB_OK | MB_ICONERROR);
}
#endif


