#include <iostream>
#include <functional>
#include <Windows.h>

std::function<void(void)> func_out()
{
    int a = 10;
    std::cout << "out:" << &a << std::endl;
    std::function<void(void)> func_in = [&]()
    {
        std::cout << "in:" << &a << std::endl;
        std::cout << a << std::endl;
    };
    return func_in;
}

// int *func_in(int *a)
// {
//     std::cout << "in:" << *a << std::endl;
//     return a;
// }

// auto func_out(int *a)
// {
//     std::cout << "out:" << *a << std::endl;

//     return std::bind(func_in, a);
// }

// int *test()
// {
//     int a = 10;
//     auto func = func_out(&a);

//     return func();
// }

int main()
{
    // func_out()();
    HMODULE ptr;
    if (ptr == nullptr)
    {
        std::cout << "nullptr" << std::endl;
    }
    else if (ptr != nullptr)
    {
        std::cout << "nullptr" << std::endl;
    }
}