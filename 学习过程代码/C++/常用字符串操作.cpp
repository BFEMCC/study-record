#include <iostream>
#include <string>
#include <regex>

// 去除所有空格
void removeSpaces(std::string &str)
{
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

// 字符串替换
// 原字符串
// 要被替换的字符串
// 用来替换的字符串
void replaceAll(std::string &str, const std::string &from, const std::string &to)
{
    size_t startPos = 0;
    while ((startPos = str.find(from, startPos)) != std::string::npos)
    {
        str.replace(startPos, from.length(), to);
        startPos += to.length();
    }
}

// 找到第一个与指定字符串相同的子串，并删除
// 原字符串
// 需要删除的子串
void removeFirstOccurrence(std::string &mainStr, const std::string &substr)
{
    size_t found = mainStr.find(substr);
    if (found != std::string::npos)
        mainStr.erase(found, substr.length());
}

// 找到第一个与指定字符串相同的子串，并替换成另一个指定的字符串
// 原字符串
// 要替换的子串
// 替换的字符串
void replaceFirstOccurrence(std::string &mainStr, const std::string &toReplace, const std::string &replacement)
{
    size_t found = mainStr.find(toReplace);
    if (found != std::string::npos)
        mainStr.replace(found, toReplace.length(), replacement);
}

// 查找原字符串中和需要删除的字符串一样的子串，并删除
// 原字符串
// 需要删除的字符串
void deleteSubstring(std::string &originalString, const std::string &stringToDelete)
{
    size_t pos = 0;

    while ((pos = originalString.find(stringToDelete, pos)) != std::string::npos)
    {
        originalString.erase(pos, stringToDelete.length());
    }
}

// 提取数学算式中的数字
std::vector<std::string> extractNumbersFromMathExpression(const std::string &expression)
{
    std::vector<std::string> numbers;
    std::regex reg("-?\\d+(\\.\\d+)?"); // 定义匹配数字的正则表达式模式，包括整数和小数
    std::smatch match;

    // 使用正则表达式匹配数字，并将匹配结果存储在vector中
    auto words_begin = std::sregex_iterator(expression.begin(), expression.end(), reg);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    {
        std::smatch match = *i;
        numbers.push_back(match.str()); // 将匹配到的数字存储在vector中
    }

    return numbers;
}