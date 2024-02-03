#include <iostream>
#include <string>
#include<regex>//正则库C++11
using std::cout;
using std::cin;
using std::string;
using std::endl;

//字符串匹配 regex_match
void  testMatch()
{
    //regex_matfh(需要匹配的字符串，正则对象)，满足匹配返回true，否则false

    //判断用户名输入是否是邮箱
    string username = "";
    while(1)
    {
        cout << "请输入用户名：";
        cin >> username;
        std::regex reg("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");//创建正则对象，单斜杠变为双斜杠
        bool result = std::regex_match(username, reg);
        if (result)
        {
            cout << "输入的是邮箱" << endl;
        }
        else
        {
            cout << "输入的不是邮箱，请重新输入" << endl;
        }
    }
}

//完全匹配问题
void test02()
{
    string str{ "HelloWorld1314" };
    std::regex reg("[(a-z0-9]+");//最少一次的a-z或者0-9
    bool result{ std::regex_match(str,reg) };//不完全匹配，因为有大写
    if (result)
        cout << "完全匹配" << endl;
    else
        cout << "不完全匹配" << endl;


    str = "HelloWorld1314";
    std::regex reg2("[a-zA-Z0-9]+");//最少一次的a-z或者A-Z或者0-9
    result = std::regex_match(str, reg2);//完全匹配
    if (result)
        cout << "完全匹配" << endl;
    else
        cout << "不完全匹配" << endl;


    str = "HelloWorld1314";
    std::regex reg3("[a-z0-9]+",std::regex_constants::icase);//最少一次的a-z或者0-9，忽略大小写
    result = std::regex_match(str, reg3);//完全匹配，因为忽略了大小写
    if (result)
        cout << "完全匹配" << endl;
    else
        cout << "不完全匹配" << endl;

}

//字符串捕获 regex_search
void test03()
{
    //参数：需要捕获的字符串，用于存储结果的smatch对象，正则对象

    //捕获第一次满足条件的
    string str{ "I Love You 13 you 14" };

    std::smatch result;
    bool flag = std::regex_search(str, result, std::regex("\\d+"));//至少一个数字

    if (flag)
    {

        cout << "size：" << result.size() << endl;

        cout << result.str() << endl;//存放已经匹配到的字符串

        cout << "匹配到的字符串的前缀：" << result.prefix() << endl;
        cout << "匹配到的字符串的后缀：" << result.suffix() << endl;
    }
    cout << endl;

    //捕获后续能够匹配的字符串
    //通过sregex_iterator迭代器做遍历
    std::regex reg{"\\d+"};
    std::sregex_iterator pos(str.begin(),str.end(), reg);

    std::sregex_iterator end;//默认构造的结果是空

    while (pos != end)
    {
        cout << pos->str() << endl;
        pos++;
    }
    cout << endl;

    //获取每一段的内容 sregex_token_iteartor(字符串开始位置，字符串结束位置，正则对象，flag标记（0：存储所有匹配到的，-1：存储所有的不匹配的）)
    std::regex reg2("\\d+");
    std::sregex_token_iterator pos1(str.begin(), str.end(), reg2, -1);
    std::sregex_token_iterator end2;
    while (pos1 != end2)
    {
        cout << pos1->str() << "\t";
        pos1++;
    }
    cout << endl;

}

//正则替换 regex_replace
void test04()
{
    //基本用法
    //regex_replace(待处理的字符串，正则对象，需要替换的内容字符串)
    string str{ "ILoveYou13love14" };
    std::regex reg("\\d+");
    string newstr = std::regex_replace(str, reg, "。。");
    cout << newstr << endl;

    //按照特定条件做替换
    //regex_replace(待处理的字符串，正则对象，需要替换的内容字符串，匹配方式（regex_constants宏）)
    //std::regex_constants::format_first_only;


}

int main()
{

    //testMatch();
    //test02();
    //test03();
    test04();

    system("pause>nul");
    return 0;
}
