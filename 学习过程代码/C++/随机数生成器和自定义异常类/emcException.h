/*
 * @file       emcException
 * @brief      自定义异常类
 * @author     EMC方
 * @version    1.0
 * @date       2023/08/02
*/
#ifndef EMCEXCEPTION_H
#define EMCEXCEPTION_H
#pragma once
#include <exception>
#include <string>
#include "ConversionFunction.h"
#include <Windows.h>
#endif

namespace emc
{
    class emcException
        : public std::exception
    {
    public:
        emcException() = default;
        emcException(const std::string& message);
        emcException(const char* message);
        emcException(const int& message);
        emcException(const double& message);
        emcException(const std::wstring& message);
        emcException(const wchar_t* message);
        
        virtual const char* what() const noexcept override
        {
            return message_.c_str();
        }
#ifdef _UNICODE
        /*
        * @brief    错误提示弹窗
        * @param    （可选）父窗口句柄
        * @param    （可选）窗口标题  
        */
        void PopupPrompt(HWND Parent = nullptr, std::string title = " Exception");

#elif  _MBCS
        /*
        * @brief    错误提示弹窗
        * @param    （可选）父窗口句柄
        * @param    （可选）窗口标题  
        */
        void PopupPrompt(HWND Parent = nullptr, std::string title = " Exception");

#endif
    protected:
        std::string message_ = "Unknown exception";

    };
}



