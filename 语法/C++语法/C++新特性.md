# 结构化绑定(C++17)



```cpp
int arr[] = {1,2,3};
auto [a,b,c] = arr; // 复制，而不是引用
std::cout << a << b << c; 
// 如果是类，会调用复制构造函数


//如果不想发发生复制，在定义时就是用引用
int arr[] = {1,2,3};
auto& [a,b,c] = arr; // 引用，没有发生复制
std::cout << a << b << c; 
```
