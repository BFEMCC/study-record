#include <map>
#include <iostream>
#include <string>

/*C++17结构化绑定详解:
https://www.bilibili.com/video/BV1NH4y1X7q6/?share_source=copy_web&vd_source=03da7de0e80f9ff60fdeca7b512ba3f5
https://www.bilibili.com/video/BV14h4y1K7Qs/?share_source=copy_web&vd_source=03da7de0e80f9ff60fdeca7b512ba3f5
*/

// 绑定原生数组
void arr()
{
    int arr1[] = {1, 2, 3};
    auto [a, b, c] = arr1; // 复制，而不是引用
    std::cout << a << b << std::endl;
    // 如果是类，会调用复制构造函数

    // 如果不想发发生复制，在定义时就是用引用
    int arr2[] = {1, 2, 3};
    auto &[x, y, z] = arr2; // 引用，没有发生复制
    std::cout << x << y << z << std::endl;
}

// 绑定结构体或类
void s_c()
{
    struct A
    {
        int x = 10;
        std::string y = "100";
    };
    A a = A();
    auto &[x, y] = a;
    std::cout << x << y << std::endl;

    class B
    {
    public: // C++20前必须是public才能绑定
        int x = 10;
        std::string y = "100";
    };
    B b = B();
    auto &[m, n] = b;
    std::cout << m << n << std::endl;
}

// 绑定到标准库容器，以map举例
// 遍历map，插入元素
void e_map()
{
    std::map<std::string, int> map{
        {"key1", 1}, {"key2", 2}, {"key3", 3}};

    // 优雅的遍历map
    for (const auto &[key, value] : map)
    {
        std::cout << key << ":" << value << std::endl;
    }

    // 优雅的检查map是否插入成功
    if (const auto [inter, bool_]{map.insert({"key3", 3})}; bool_)
    { // 不存在，插入成功
        std::cout << "successful:" << std::endl;
        auto [k, v] = *inter;
        std::cout << "new:  " << k << ":" << v << std::endl;
    }
    else
    { // 已经存在
        std::cout << "defeated:" << std::endl;
        auto [k, v] = *inter;
        std::cout << "old:  " << k << ":" << v << std::endl;
    }
}

int main()
{
    arr();
    s_c();
    e_map();
}