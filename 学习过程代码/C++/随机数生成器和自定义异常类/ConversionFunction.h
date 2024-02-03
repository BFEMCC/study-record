/*
 * @file       ConversionFunction
 * @brief      ת��������ȫ�֣�
 * @author     EMC��
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
    * @brief    char����ת����wstring
    * @param    char*
    * @return   wstring
    */
	std::wstring charTowstring(char* charstr);

    /*
    * @brief    stringת����wstring
    * @param    string
    * @return   wstring
    */
	std::wstring stringTowstring(std::string str);

    /*
    * @brief    wstringת����string
    * @param    wstring
    * @return   string
    */
    std::string wstringTostring(std::wstring wstr);

    /*
    * @brief    �����ֵ�wstringתint
    * @param    ��Ҫת����wstring
    * @param    ��ת�������int
    * @return   bool�Ƿ�ת���ɹ�
    */
    bool wstringWithOnlyNumbersToint(std::wstring str, int& intstr);

    /*
    * @brief    ����λʮ����ת���ɶ�����
    * @param    string
    * @return   string
    */
    std::string DecimalToBinary(std::string n);

    /*
    * @brief    ��������תint
    * @param    string
    * @return   int
    */
    int RomanToint(std::string s);
}

