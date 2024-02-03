/*
 * @file       ConversionFunction
 * @brief      转换函数（全局）
 * @author     EMC方
 * @version    1.0
 * @date       2023/08/02
*/
#ifndef CONVERSIONFUNCTION_H
#define CONVERSIONFUNCTION_H
#pragma once
#include <iostream>
#include <comdef.h>
#include <unordered_map>
#endif
namespace emc
{
    /*
    * @brief    char数组转换成wstring
    * @param    char*
    * @return   wstring
    */
	std::wstring charTowstring(char* charstr);

    /*
    * @brief    string转换成wstring
    * @param    string
    * @return   wstring
    */
	std::wstring stringTowstring(std::string str);

    /*
    * @brief    wstring转换成string
    * @param    wstring
    * @return   string
    */
    std::string wstringTostring(std::wstring wstr);

    /*
    * @brief    仅数字的wstring转int
    * @param    需要转换的wstring
    * @param    储转换结果的int
    * @return   bool是否转换成功
    */
    bool wstringWithOnlyNumbersToint(std::wstring str, int& intstr);

    /*
    * @brief    任意位十进制转换成二进制
    * @param    string
    * @return   string
    */
    std::string DecimalToBinary(std::string n);

    /*
    * @brief    罗马数字转int
    * @param    string
    * @return   int
    */
    int RomanToint(std::string s);
}

