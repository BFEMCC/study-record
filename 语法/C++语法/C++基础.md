

[TOC]



# 引用（左值引用）

## 基本概念和语法

---

==本章所有内容都是针对C++98标准的左值引用。==

[C++中的引用是一种特殊的变量，它是另一个已存在变量的别名，可以通过引用或原始变量来访问同一块内存空间。](https://www.runoob.com/cplusplus/cpp-references.html)

引用的语法是在变量类型后加上`&`符号，然后给引用一个初始值

**示例：**

~~~c++
int a = 10; // 声明一个普通变量a
int &b = a; // 声明一个引用b，它是a的别名

cout << "a =" << a <<endl;
cout << "b = " << b <<endl;
b = 100; // a和b是同一块内存区域的两个名称，对b进行操作等价于对a进行操作
cout << "a = " << a <<endl;
cout << "b = " << b <<endl;
~~~

**输出结果：**

~~~
a = 10
b = 10
a = 100
b = 100
~~~

**引用的作用有以下几点：**

- 可以简化指针的操作，避免使用`*`和`&`符号来取值或取地址。
- 可以提高函数参数传递的效率，避免复制大量数据。
- 可以使函数返回多个值，而不仅仅是一个。
- 可以实现运算符重载等高级功能。

## 注意事项

---

**引用的注意事项有以下几点：**

- 引用==必须==在声明时==初始化==，不能像指针那样先声明后赋值。

- 引用一旦初始化，就==不能改变指向==其他变量，否则会修改原始变量的值。

- 引用==不能指向空值==或==无效地址==，否则会导致程序崩溃。

- 引用==不占用额外的内存空间==，它只是原始变量的另一个名称。

- 一个变量可以有多个引用，也就是说，可以定义多个引用指向同一个变量。

  **示例：**

  ~~~c++
  int a = 10; 
  int &r1 = a; // r1是a的引用 
  int &r2 = a; // r2也是a的引用 
  cout << r1 << " " << r2 << endl; // 输出10 10
  ~~~

- 引用不能有引用，也就是说，不能定义一个引用指向另一个引用。

  **示例：**

  ~~~c++
  int a = 10; 
  int &r1 = a; // r1是a的引用 
  int &r2 = r1; // 错误，不能定义一个引用指向另一个引用
  ~~~
  
  但是，可以定义一个变量和一个引用同时指向另一个引用。
  
  **示例：**
  
  ```c++
  int a = 10; 
  int &r1 = a; // r1是a的引用 
  int *p = &r1; // p是指向r1的指针 
  int &r2 = *p; // r2是p所指对象的引用，也就是r1的别名 
  cout << *p << " " << r2 << endl; // 输出10 10
  ```

## 引用做函数参数

---

当引用作为函数参数时，需要注意以下几点：

- 如果参数只需要读取而不修改，可以使用常量引用来提高效率和安全性。
- 如果参数需要修改，并且希望修改能够反映到实参上，可以使用普通引用来传递。
- 如果参数是类对象或结构体等复杂类型，并且需要修改其内容或调用其成员函数，可以使用普通引用来传递。

引用的本质是一个常指针（指针常量），在编译器内部实现为指向原始变量地址的常量。引用传递相当于指针传递。

**示例：**

~~~c++
// 值传递
void swap1(int a, int b) 
{ 
    int temp = a; 
    a = b; 
    b = temp; 
}

// 指针传递 
void swap2(int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

// 引用传递 
void swap3(int &a, int &b) 
{ 
    int temp = a; 
    a = b; 
    b = temp; 
}

int main() 
{ 
	int x = 10, y = 20;

	swap1(x, y); // x和y不会交换 
	swap2(&x, &y); // x和y会交换 
	swap3(x, y); // x和y会交换，a是x的别名，b是y的别名
	return 0; 
}
~~~

## 引用做函数返回值

---

**当引用作为函数返回值时，需要注意以下几点：**

- 不要返回局部变量的引用，因为局部变量在函数结束后会被销毁，导致返回无效地址。
- ==不建议==返回堆区对象的引用。
- 可以返回静态局部变量或全局变量的引用，因为这些变量在程序结束前都有效。
- 可以返回类对象或结构体等复杂类型的成员变量或成员函数的引用。

**返回堆区对象的引用是不安全的，有以下几种可能的风险：**

- 如果在函数内部释放了堆区对象的内存，那么返回的引用就是一个空指针，指向一个无效的地址。
- 如果在函数外部释放了堆区对象的内存，那么可能会导致重复释放或者内存泄漏，因为函数外部不一定知道引用指向的是堆区对象。
- 如果在函数外部修改了堆区对象的值，那么可能会影响到其他地方使用该对象的逻辑，因为堆区对象是共享的。

一般来说，不建议返回堆区对象的引用。如果需要返回动态分配的内存，可以使用智能指针或者容器类来管理内存。

**示例：**

~~~c++
// 返回局部变量的引用 
int& func1() 
{ 
    int a = 10; // 局部变量 
    return a; // 错误！ 
} // 局部变量在函数结束后会被销毁，导致返回无效地址

// 返回堆区对象的引用 
int& func2() 
{ 
    int* p = new int(20);
    return p;
} // 不建议
~~~

引用做函数返回值时，如果返回的是一个静态变量，那么这个引用就可以作为左值，也就是可以被赋值或修改。这是因为静态变量在函数结束后不会被销毁，它的生命周期和作用域都延长了，所以返回的引用仍然有效。

**示例：**

~~~c++
// 返回一个静态变量的引用 
int& func() 
{ 
    static int x = 10; // 静态变量 
    return x; // 返回引用 
}

int main() 
{ 
    int& a = func(); // 接收返回的引用 
    cout << a << endl; // 输出10 
    a = 20; // 修改引用指向的值 
    cout << func() << endl; // 输出20
}
~~~

## 引用的本质

---

这一节根据黑马程序员的C++教程（详细在B站搜索”C++“，播放量最高的就是）编写，也许并不正确，请读者自行甄辨。

引用的本质是一种被限制的指针，它在内部实现时是一个指针常量，也就是说，它指向的对象不能改变，但对象的值可以改变。

**引用和指针有以下区别：**

- 引用必须在定义时初始化，并且不能重新赋值，而指针可以在任何时候初始化和赋值。
- 引用不占用额外的内存空间，而指针占用一个存储地址的空间。
- 引用使用起来更加简洁和安全，不需要解引用操作符`*`，也不会出现空指针或野指针的问题。
- 引用只能有一级，不能有多级引用，而指针可以有多级。

**示例：**

~~~c++
// 定义一个变量a和一个引用r 
int a = 10; 
int &r = a; // 相当于 int *const r = &a; //常量指针的指向不可以修改，值可以修改

// 通过r修改a的值 
r = 20; 
cout << a << endl; // 输出20

// 定义一个函数swap，使用引用作为参数 
void swap(int &x, int &y) 
{ 
    int temp = x; 
    x = y; 
    y = temp; 
}

// 调用swap函数 
int m = 10, n = 20; 
swap(m, n); 
cout << m << " " << n << endl; // 输出20 10
~~~

## 常量引用

---

常量引用是对`const`的引用，也就是说，它把它所指向的对象看作是常量，因此不可以通过该引用来修改它所指向的对象的值。

**常量引用的作用有以下几点：**

- 可以避免不必要的拷贝，提高效率。
- 可以保护被引用的对象，防止意外修改。
- 可以接受字面值或表达式作为初始值，而普通引用不行。

**示例：**

~~~c++
int &a = 42; // 错误：普通引用必须绑定到一个对象上，而不能绑定到一个字面值或表达式

const int &r = 42;// 正确：const引用可以绑定到字面值或表达式上，const引用可以让编译器为字面值或表达式创建一个临时变量，并将引用绑定到该临时变量上

// 声明一个普通变量i和一个常量变量ci 
int i = 10; 
const int ci = 20;

// 声明一个常量引用ri，绑定到i 
const int &ri = i;

// 声明一个常量引用rci，绑定到ci 
const int &rci = ci;

rci = 30; // 错误：不能通过常量引用修改被引用的对象 
ri = 40; // 错误：不能通过常量引用修改被引用的对象

i = 50; // 正确：可以直接修改普通变量 
cout << ri << endl; // 输出50

cout << r + ri << endl; // 输出92
~~~

# 函数_高级篇

## 函数重载

---

### 基本使用

---

函数重载是指在同一作用域内，可以有多个同名函数，只要它们的参数个数、类型或参数顺序不同即可。这样，当调用这个函数时，编译器会根据传入的实参自动选择合适的函数进行调用。

下面的示例是三个重载的函数。

**示例：**

```cpp
int add(int a, int b) 
{
    return a + b;
}

double add(int a, double b) 
{
    return a + b;
}
double add(double b, int a) 
{
    return a + b;
}
```

### 注意事项

---

- 函数重载必须在同一作用域内。
- 函数重载的函数名必须相同，但函数的参数列表必须不同。
- 函数重载不能只是函数参数名的不同。
- 参数列表的不同可以包括参数的类型、个数或顺序。
- 重载的函数可以有不同的返回值类型，即函数的返回值不作为函数重载的条件
- 不能仅仅通过为普通变量添加或删除`const`修饰符来重载一个函数
- 可以对函数的常量性进行重载，即可以同时定义一个常量函数和一个非常量函数。
- 可以对类成员函数进行重载。（有关类将在之后的内容中提到）

  **示例：**

  ```c++
  void foo(int x) 
  {
      cout << "foo(int x): " << x << endl;
  }
  
  int foo(int x) // 错误：函数的返回值不作为函数重载的条件
  {
      return 3;
  }
  
  void foo(const int x) // 错误：不能仅通过为普通变量参数添加const修饰符来重载函数
  { 
      cout << "foo(const int x): " << x << endl;
  }
  ```

  **示例：**

  ```c++
  code// 重载函数示例1：参数个数不同
  int sum(int a, int b) {
    return a + b;
  }
  
  int sum(int a, int b, int c) {
    return a + b + c;
  }
  
  // 重载函数示例2：参数类型不同
  double sum(double a, double b) {
    return a + b;
  }
  
  int sum(int a, int b) {
    return a + b;
  }
  
  // 重载函数示例3：常量性重载
  class MyClass {
  public:
    void foo() {
      std::cout << "non-const foo()" << std::endl;
    }
    void foo() const {
      std::cout << "const foo()" << std::endl;
    }
  };
  
  // 重载类成员函数
  class MyClass2 {
  public:
    void foo() {
      std::cout << "non-const foo()" << std::endl;
    }
    void foo() const {
      std::cout << "const foo()" << std::endl;
    }
  };
  
  int main() {
    // 调用重载函数示例1
    int x = sum(1, 2);
    int y = sum(1, 2, 3);
  
    // 调用重载函数示例2
    double a = sum(1.0, 2.0);
    int b = sum(1, 2);
  
    // 调用重载函数示例3
    MyClass obj1;
    const MyClass obj2;
    obj1.foo(); // 调用非常量函数
    obj2.foo(); // 调用常量函数
  
    // 调用重载类成员函数
    MyClass2 obj3;
    const MyClass2 obj4;
    obj3.foo(); // 调用非常量函数
    obj4.foo(); // 调用常量函数
  
    return 0;
  }
  ```

- 引用作为函数参数时，可以使用引用的类型和常量性来进行函数重载。

  使用引用作为函数参数进行函数重载的**示例：**

  ~~~c++
  void foo(int& x) {
      // 处理一个非常量引用
  }
  
  void foo(const int& x) {
      // 处理一个常量引用
  }
  ~~~

- 当有多个函数重载时，==如果某个函数的参数既可以被传递为引用，也可以被传递为值，那么编译器会优先选择传值调用==

  因为传递值可以避免引用的问题，并且可以更好地利用编译器的优化。如果需要显式地调用一个特定的函数重载，可以使用类型转换或显式地声明参数类型来调用该函数。

  **例如：**

  ~~~c++
  void foo(int x) {
      // 处理一个整数
  }
  
  void foo(const int& x) {
      // 处理一个常量引用
  }
  ~~~

  如果我们调用 `foo(42)`，那么编译器会选择第一个函数，因为它可以直接将整数值 42 传递给函数参数 `x`，而不需要创建一个临时的引用对象。这样可以更快地执行，因为传递值比传递引用更高效。

  但是，如果我们调用 `foo(i)`，其中 `i` 是一个整数变量，则编译器会选择第二个函数，因为它可以使用一个引用来访问 `i`，并且这个引用可以被声明为常量引用，从而保证 `i` 的值不会被修改。

  如果我们需要显式地调用一个特定的函数重载，可以使用类型转换或显式地声明参数类型来调用该函数。

  例如，我们可以使用以下方式来调用第一个函数：

  ~~~c++
  foo(static_cast<const int&>(42));
  ~~~

  或者我们可以使用以下方式来调用第二个函数：

  ```c++
  int i = 42;
  foo(static_cast<int>(i));
  ```

  在这两个例子中，我们使用 `static_cast` 强制将值类型转换为引用类型或将引用类型转换为值类型。这样可以显式地指定需要调用的函数版本。

- 两个使用引用作为参数的重载函数**示例**：

  ~~~c++
  void foo(int& x) 
  {   
      // 处理一个非常量引用 
  };
  void foo(const int& x) 
  {  
      // 处理一个常量引用
  };
  ~~~

  对于这两个重载函数，当传入一个字面常量时，编译器会选择调用 `foo(const int& x)`，例如：`foo(10)`，因为字面数值是常量，不能被修改，因此需要传递一个常量引用。

  如果传入一个变量，例如： `int i = 10; foo(i);`，则会选择调用 `foo(int& x)`，因为该函数接受一个非常量引用，可以修改传入的参数。

  如果传入的参数是一个 `const` 类型的变量，则编译器会选择调用 `foo(const int& x)`。

- 不建议在重载函数时使用默认参数，这会非常容易出错，这里不做过多解释

## 函数的默认参数

---

函数的默认参数是指在函数定义或声明时，为形参指定一个默认值，这样在调用函数时，如果没有给这个形参赋值（没有对应的实参），那么就使用这个默认值。

**示例：**

~~~c++
//带默认参数的函数
void func(int n, float b = 1.2, char c = '@') 
{
    cout << n << ", " << b << ", " << c << endl;
}
int main()
{
    func(10); //相当于func(10, 1.2, '@')
	func(20, 9.8); //相当于func(20, 9.8, '@')
	func(30, 5.5, '#'); //不使用任何默认值
    return 0;
}
~~~

**输出结果：**

~~~c++
10, 1.2, @
20, 9.8, @
30, 5.5 #
~~~

**默认参数有以下几个注意事项：**

- 不建议在重载函数时使用默认参数，这会非常容易出错，这里不做过多解释。

- 默认参数必须是常量或常量表达式，在它们前面有一个赋值运算符`=`。

- 一旦为某个形参指定了默认值，那么它后面的所有形参都必须有默认值。

  **示例：**

  ```c++
  // 错误：b有了默认参数，那么b之后的形参都必须有默认参数，而c没有默认参数
  void func(int n, float b = 1.2, char c ,double d=5.2) 
  {
      cout << n << ", " << b << ", " << c << ", " << d << endl;
  }
  //正确，第一个有默认参数的形参之后的所有形参都有默认参数
  void func(int n, float b , char c = '@',double d = 5.2) 
  {
      cout << n << ", " << b << ", " << c << ", " << d << endl;
  }
  ```

- 默认参数应在函数名称最早出现时分配，通常是在函数原型中指定，默认参数只能指定一次。如果函数有声明就会以声明的为准，定义时指出的默认参数就会无效。

  如果函数有声明就会以声明的为准，定义时指出的默认参数就会无效。这是因为编译器在处理函数调用时，需要知道函数的参数类型和数量，以及是否有默认值，如果在声明和定义中都给出了默认参数，那么就会造成冲突和混乱。

  **错误示例：**

  ```c++
  //错误示例
  //声明
  void func(int n = 10); //给n指定了默认值10
  //定义
  void func(int n = 20)//又给n指定了默认值20，即使它们是一样的也是不行
  { 
      cout << n << endl;
  }
  
  //调用
  func(); //这里应该使用哪个默认值呢？
  ```

  这样的代码是不合法的，编译器会报错。正确的做法是只在声明或定义中给出一次默认参数。

  **正确示例：**

  ```c++
  //正确的示例
  //声明
  void func(int n = 10); //给n指定了默认值10
  //定义
  void func(int n) //不再给n指定默认值
  {
      cout << n << endl;
  }
  
  //调用
  func(); //使用声明中的默认值10
  ```

  或者

  ```c++
  //正确的示例
  //声明（没有给出默认参数）
  void func(int n);
  //定义（给出了默认参数）
  void func(int n = 10){
      cout << n << endl;
  }
  //调用（使用定义中的默认值）
  func();
  ```

- 当一个实参在一个函数调用中被遗漏时（因为它有默认值)，它后面的所有实参也必须被省略。不能跳过某个实参而给后面的实参赋值。

  **示例：**

  ```c++
  //带默认参数的函数
  void func(int n, float b = 1.2, char c = '@')
  {
      cout << n << ", " << b << ", " << c << endl;
  }
  int main()
  {
      // 正确
      func(10); //相当于func(10, 1.2, '@')
  	func(20, 9.8); //相当于func(20, 9.8, '@')
  	func(30, 5.5, '#'); //不使用任何默认值
      //错误
      func(10, , '#'); //错误！不能跳过第二个参数而给第三个参数赋值
  }
  ```

- 默认参数与函数重载可能会产生二义性问题。如果有两个重载函数都可以匹配调用语句，那么编译器会报错。

  编译器在处理函数调用时，需要根据实参的类型和数量来确定调用哪个重载函数，如果有多个重载函数都符合条件，那么就会造成歧义。

  **错误示例：**

  ```c++
  //错误的示例
  //声明两个重载函数
  void func(int a, int b = 10);
  void func(int a);
  
  //定义两个重载函数
  void func(int a, int b)
  {
      cout << "func(int a, int b) is called" << endl;
  }
  
  void func(int a)
  {
      cout << "func(int a) is called" << endl;
  }
  
  //调用
  func(10); //这里应该调用哪个重载函数呢？
  ```

  这样的代码是不合法的，编译器会报错。正确的做法是避免使用默认参数和函数重载产生歧义。

  **正确示例：**

  ```c++
  //正确的示例
  //声明两个重载函数
  void func(int a);
  void func(double a);
  
  //定义两个重载函数
  void func(int a)
  {
      cout << "func(int a) is called" << endl;
  }
  
  void func(double a)
  {
      cout << "func(double a) is called" << endl;
  }
  
  //调用
  func(10); //调用func(int a)
  func(10.0); //调用func(double a)
  ```

有关类中成员函数的重载和默认参数将在类的相关笔记中说明

## 函数的占位参数

---

- C++中函数的形参列表可以有占位参数，用来作占位，调用函数时必须填补该位置。

- 占位参数只有参数类型声明，而没有参数名声明。
- 一般情况下，在函数体内部无法使用占位参数。占位参数也可以有默认值。

注意事项有以下几点：

- 占位参数不能只有部分参数类型声明，而没有参数名声明，例如 `void func(int a, int)` 是合法的，但 `void func(int, int b)` 是不合法的
- 占位参数一般用于重载运算符或者实现一些特殊功能，不建议在普通函数中使用

**示例：**

```cpp
//函数占位参数，占位参数也可以有默认值
void func01(int a, int) 
{
    cout << "this is func" << endl;
}
// 有默认参数的占位参数
void func02(int a, int b, int = 20)
{
	cout << "a + b = " << a + b << endl;
}
int main() 
{
    func01(10,10); //占位参数必须填补
    
	func02(10,20); // 错误调用，占位参数也是参数，必须传参数
    
	func02(10,20,30); //正确调用
	func02(10,20); //正确调用
	func02(10, 20, 30); //正确调用
    
    return 0;
}
```

# 类和对象

C++中的类是一种用户==自定义的数据类型==，用于封装数据和函数。类的定义包括数据成员和成员函数，数据成员可以是任何C++数据类型，成员函数可以是普通函数或者操作符重载函数。

==类似于`struct`==，当然实际不一样

对象是类的一个实例，它是由类定义的模板创建的具体实体。对象可以访问类中的成员函数和数据成员，可以通过对象来操作类中的数据。

类和对象是面向对象编程的核心概念，它们可以帮助我们更好地组织和管理程序的数据和代码，提高程序的可读性、可维护性和可扩展性。

C++面向对象的三大特征是封装、继承和多态。

- 封装（Encapsulation）：指将数据和操作数据的函数绑定在一起，形成一个类。封装可以隐藏数据和实现细节，防止外部程序直接访问和修改数据，从而提高程序的安全性和可靠性。
- 继承（Inheritance）：指在一个已有类的基础上，创建一个新类，新类具有原有类的属性和方法。通过继承，可以减少重复代码，提高代码的复用性和可维护性。
- 多态（Polymorphism）：指同一个函数或方法可以根据不同的对象调用产生不同的行为。多态可以提高程序的灵活性和可扩展性，使程序更易于维护和扩展。

这三大特征是C++面向对象编程的核心，也是C++在实现面向对象编程中最重要的手段。

**通俗易懂的解释什么是类和对象：**

- 当我们看到一只狗时，我们可以想象它是“狗”这个大类（狗这个物种）下的一个“对象”。
- 狗类有一些属性，如颜色、品种、体型等，也有一些方法，如叫、跑、吃等。
- 每只狗都具有这些属性和方法，但它们的具体值可能会不同，比如颜色是黑色的、品种是哈士奇的、体型是大型的。
- 但这些不同的狗都是由狗这个类实例化而来的不同对象。

我们可以把类比作一个“图纸”或“模板”，用于描述对象应该具有的属性和方法。而对象则是由这个蓝图创建的具体实例，具有这些属性和方法。就像建筑师会按照图纸来建造房屋一样，我们也可以根据类来创建对象。

另一个比喻是，类就像是一个自定义数据类型，而对象则是这个数据类型的具体实例。就像int是一个数据类型，1、2、3等就是`int`类型的具体实例一样。

**例如：**

1. 车可以作为对象，属性具有品牌、颜色、速度等，行为有加速、刹车、转弯等，每一辆车都属于车这个大的类。
2. 动物可以作为对象，属性具有种类、生活习性、食物喜好等，行为有奔跑、攀爬、捕猎等，每一种动物都属于动物这个大的类。
3. 商品可以作为对象，属性具有名称、价格、规格等，行为有上架、下架、促销等，每一种商品都属于商品这个大的类。
4. 一个人可以作为对象，属性具有姓名、年龄、身高、体重等，行为有走、跑、跳、吃饭等，每一个人都属于人类这个大的类。

## 类的定义和封装

---

**封装是面向对象编程中的重要概念之一，它的作用和意义主要有以下几个方面：**

- 提高安全性：通过封装，我们可以将类的实现细节隐藏起来，只将需要外部访问的接口暴露出来，从而防止外部程序直接访问和修改类的数据，提高程序的安全性和可靠性。
- 提高可维护性：通过封装，我们可以将类的实现细节和外部接口分离开来，使得在修改类的实现细节时，不会对外部程序产生影响，从而提高程序的可维护性和可扩展性。
- 简化编程：通过封装，我们可以将复杂的操作封装成一个函数或方法，从而简化编程，减少代码的冗余和复杂度。
- 提高代码的复用性：通过封装，我们可以将一些通用的功能封装成类或函数，供多个程序复用，从而提高代码的复用性。

类似定义`struct`用户自定义数据类型，定义类的关键字是`class`

**基本语法：**

```c++
class 类名
{
访问权限:
	属性;
	行为;//行为指函数
    ......
};
```

**示例：**

~~~c++
// 定义一个最简单的类
class MyClass 
{
public:
    // 成员函数
    void print() 
    {
        std::cout << "Hello World!" << std::endl;
    }
private:
    // 数据成员
    int num;
};

int main() 
{
    // 创建一个对象
    MyClass obj;
    // 调用成员函数
    obj.print();
    return 0;
}
~~~

**解释：**

- 当我们定义一个类时，我们需要定义它的属性和行为。属性是指该类具有的特征或者状态，行为则是指该类可以执行的操作。

- 在这个例子中，我们定义了一个叫做``MyClass`的类，它具有以下属性和行为：

  - 属性：

    `num`：一个整数类型的私有数据成员。
    
  - 行为：
  
    `print()`：一个公有成员函数，可以输出一条信息到控制台。输出信息就是这个类的行为。

- 在这个类中，`num`是一个私有数据成员，外部程序无法直接访问和修改。
- `print()`是一个公有成员函数，可以在类的外部直接访问和调用。
- 调用`print`函数时，它会输出一条消息到控制台，这条消息是`Hello World!`。

**注意事项和解释：**

- 公有(`public`)、私有(`private`)、保护(`protected`)是访问权限的修饰符，用于控制类中成员的访问权限。

- 公有成员可以被类的外部程序访问和调用，私有成员只能被类的内部程序访问和调用，保护成员可以被该类的派生类的内部程序访问和调用。

- 定义类时，访问权限修饰的顺序建议按照`public`、`protected`、`private`的顺序出现，即`public`在前，`protected`在中间，`private`在后面。

  按照公有、保护、私有的顺序来定义类的成员是一种被广泛接受的，可以使代码更加清晰易读，便于他人理解和维护。

- 在定义一个类时，一般把属性写在前面，成员函数写在后面。按照访问权限的不同，将属性和成员函数分别写在`public`、`protected`、`private`部分。

- 访问权限的顺序并没有硬性规定，但是通常我们会按照公有、保护、私有的顺序来定义类的成员。具体的实现方式可以根据实际情况进行调整。

在实际编写代码时，具体的代码组织方式应该根据实际情况来确定。

**注意事项：**

- 类的成员函数可以在类内定义，也可以在类外定义。
-  如果在类内定义，则默认为内联函数。如果在类外定义，则需要使用作用域解析运算符`::`指明该函数属于哪个类。

**类内定义成员函数示例：**

```c++
class MyClass {
public:
    void myFunc() 
    {
        // 在类内定义成员函数
        // ...
    }
};
```

**类外定义成员函数示例：**

```c++
class MyClass 
{
public:
    void myFunc(); // 在类内声明成员函数
};

void MyClass::myFunc() 
{
    // 在类外定义成员函数
    // ...
}
```

- 如果一个类的成员函数在类外定义，那么在定义之前必须先声明该成员函数，否则编译器会报错。
- 通常，可以在类的头文件中声明成员函数，在源文件中定义成员函数，以实现类的封装性和可维护性。

## `class`和`struct`的区别

---

在C++中，==`class`和`struct`本质上是相同的==，都可以定义成员变量和成员函数，并且都支持封装、继承和多态等面向对象编程的特性。但是，它们之间有以下几个区别：

- 默认访问权限：在class中，默认的访问权限是`private`，而在`struct`中，默认的访问权限是`public`。因此，在class中定义的成员变量和成员函数是默认无法在类外部访问的，需要通过`public`关键字进行公开；而在`struct`中定义的成员变量和成员函数是默认可以在类外部访问的。
- 继承方式：在`class`中，继承方式默认是`private`，即派生类只能通过`public`成员函数访问基类的成员；而在`struct`中，继承方式默认是`public`，即派生类可以直接访问基类的成员。
- 使用习惯：在使用习惯上，`class`通常用于定义复杂的数据类型和对象，而`struct`通常用于定义轻量级的数据类型和数据结构。

需要注意的是，以上区别只是默认情况下的差异，在实际使用中，我们可以通过访问权限和继承方式的调整，使`class`和`struct`之间的区别也会变得比较模糊。

## 构造函数

---

在C++中，构造函数是一种特殊的成员函数，用于==初始化类的对象==。

**注意事项：**

- 构造函数的名称必须与类名相同，且不可有返回值类型。
- 构造函数可以有多个参数，也可以没有参数，以及可以有默认参数。
- 构造函数可以重载，即同一个类中可以有多个不同参数的构造函数。
- 构造函数可以在类的内部或外部进行定义，但必须是公有的。
- 构造函数可以调用其他函数，如成员函数、静态函数等。
- 如果没有定义构造函数，编译器会提供一个默认的构造函数。

以下是一个简单的**示例**，展示了如何定义一个类及其构造函数：

```c++
class MyClass 
{
public:
    // 构造函数
    MyClass() 
    {
        cout<<"构造函数调用"<<endl;
    }
private:
    int x;
    int y;
};
```

- 在上面的示例中，`MyClass`是一个简单的类，包含两个私有成员变量x和y。
- 当创建`MyClass`对象时，编译器会自动调用构造函数，从而输出`“构造函数调用”`

**说明：**

- 构造函数还可以用于执行任何必要的预处理或初始化操作，如打开文件或分配内存等。
- 构造函数可以重载，重载时必须具有不同的参数列表。
- 构造函数重载时根据提供的参数列表，编译器将自动选择正确的构造函数进行调用。
- 构造函数对象创建时自动被调用，用于初始化对象的成员变量。
- 构造函数作用是确保对象被正确地初始化，使程序在使用对象之前具有可预测的状态。

**例如**，有一个`Person`类：

```c++
class Person 
{
public:
    // 构造函数
    Person(string name, int age) 
    {
        this->name = name;
        this->age = age;
    }
    
    // 成员函数
    void display() 
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
    
private:
    string name;
    int age;
};

int main() 
{
    // 创建对象时调用构造函数进行初始化
    Person p("Tom", 20);
    p.display();
    return 0;
}
```

- 上述例子中，定义了一个`Person`类，其中定义了一个构造函数，构造函数有两个参数，分别是`name`和`age`，用于对对象的数据成员进行初始化。
- 在`main`函数中，我们创建了一个`Person`对象，传入了`name`和`age`的值来调用构造函数进行初始化，最后调用`display`函数输出对象的数据成员。

**注意事项：**

- 如果用户没有定义构造函数，则编译器会自动生成一个默认构造函数。
- 这个构造函数没有参数，仅仅是对对象的成员变量进行默认的初始化。
- 如果我们的类需要进行特殊的初始化操作，就需要自己定义构造函数。
- 构造函数可以用于分配内存，但构造函数本身并不执行内存分配操作。

**注意事项：**

在构造函数中进行内存分配等相关操作，存在一定的风险和限制。不建议在构造函数中进行内存分配等操作。如果确实需要进行这些操作，需要做好异常处理。

- 内存分配操作可能失败。在进行内存分配操作时，如果没有足够的内存可用，分配操作会失败并返回一个空指针。如果构造函数无法处理这种情况，可能会导致程序异常或崩溃。
- 内存分配操作可能耗费大量时间。在进行内存分配操作时，如果分配的内存较大或较多，可能需要很长时间才能完成。如果构造函数在这段时间内阻塞，可能会导致程序性能下降或超时。
- 构造函数可能会抛出异常。如果在构造函数中进行内存分配等操作时出现异常，可能会导致对象未能正确创建，从而造成程序错误。
- 创建一个类对象时，首先会为该对象分配内存空间，然后再调用它的构造函数进行初始化。注意顺序。

**重载构造函数示例：**

```c++
class Person 
{
public:
    // 默认构造函数
    Person() 
    {
        name = "";
        age = 0;
    }
    
    // 重载构造函数1，传入姓名
    Person(string name) 
    {
        this->name = name;
        this->age = 0;
    }
    
    // 重载构造函数2，传入姓名和年龄
    Person(string name, int age) 
    {
        this->name = name;
        this->age = age;
    }
    
    // 成员函数
    void display() 
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
    
private:
    string name;
    int age;
};

int main() 
{
    // 调用不同的构造函数进行初始化
    Person p1;
    p1.display();
    
    Person p2("Tom");
    p2.display();
    
    Person p3("Jerry", 20);
    p3.display();
    
    return 0;
}
```

**输出结果：**

```
Name:
Age: 0
Name: Tom
Age: 0
Name: Jerry
Age: 20
```

**带有默认参数的构造函数调用示例：**

```c++
class Person 
{
public:
    // 带有默认参数的构造函数
    Person(string name = "", int age = 0) 
    {
        this->name = name;
        this->age = age;
    }
    
    // 成员函数
    void display() 
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
    
private:
    string name;
    int age;
};

int main() 
{
    // 调用带有默认参数的构造函数进行初始化
    Person p1;
    p1.display();
    
    Person p2("Tom");
    p2.display();
    
    Person p3("Jerry", 20);
    p3.display();
    
    return 0;
}
```

**输出结果：**

```
Name:
Age: 0
Name: Tom
Age: 0
Name: Jerry
Age: 20
```

## 析构函数

---

析构函数是一种特殊类型的成员函数，用于在对象被销毁时进行清理工作。它的作用是在对象生命周期结束时，释放对象所占用的内存资源，包括释放动态分配的内存、关闭文件、释放锁等。

**使用和注意事项：**

- 析构函数的命名必须和类名相同，但需要在名称前添加`~`。

  例如：类名是`MyClass`，则析构函数的名称是`~MyClass`。

- 析构函数不能接有何参数，不能被重载。

- 当类对象被销毁时，编译器会自动调用相应的析构函数。

**示例：**

```cpp
#include <iostream>
using namespace std;

class MyClass 
{
public:
    MyClass() 
    {
        cout << "构造函数被调用" << endl;
    }
    ~MyClass() 
    {
        cout << "析构函数被调用" << endl;
    }
};

int main() {
    MyClass obj; // 创建一个 MyClass 对象
    return 0;
}
```

**输出：**

```
构造函数被调用
析构函数被调用
```

在上面的示例中，当创建`MyClass`对象时，构造函数被调用。当程序结束时，析构函数被自动调用，释放对象所占用的内存资源。

**注意事项：**

- 析构函数可以是虚函数。

  如果一个类有虚函数，那么它的析构函数通常也应该是虚函数。这是因为，如果一个类的指针被转换为一个基类指针，并使用基类指针删除指向派生类对象的内存，那么如果析构函数不是虚函数，那么只会调用基类的析构函数，而不会调用派生类的析构函数。这会导致内存泄漏和其他问题。

- 不要手动调用析构函数。

  析构函数应该由编译器自动调用，在对象被删除时自动调用。不要在代码中显式地调用析构函数，这通常会导致不可预测的行为。

- 析构函数应该处理异常。

  析构函数应该能够处理可能发生的异常。如果析构函数抛出异常并且没有被捕获，那么程序会调用 std::terminate()，导致程序异常终止。

- 在析构函数中不要抛出异常。

  虽然析构函数应该能够处理异常，但最好不要在析构函数中抛出异常。因为在抛出异常后，程序通常不会继续执行，导致可能未完成的清理工作无法完成，从而导致资源泄漏等问题。

- 析构函数中应该释放动态分配的内存。

  如果一个类中有动态分配的内存，那么它的析构函数应该释放这些内存。否则，这些内存将会泄漏。

总之，析构函数是一种非常重要的函数，它用于在对象生命周期结束时进行清理工作。正确编写析构函数可以有效地避免内存泄漏和其他问题。

有关虚函数将在之后的内容中提到。

## 拷贝构造函数

---

拷贝构造函数是C++中一种特殊的构造函数，它用一个同类的对象来初始化新创建的对象。

**拷贝构造函数通常用于以下情况：**

- 通过使用另一个同类型的对象来初始化新创建的对象。

  **示例：**

  ~~~c++
  class Point
  {
  private:
      int x, y;
  public:
      //普通有参构造函数
      Point(int x1, int y1) 
      { 
          x = x1;
          y = y1; 
      }
  
      // 拷贝构造函数
      Point(const Point &p2) 
      {
      	x = p2.x; 
     		y = p2.y; 
      }
  
      int getX()            
      {  
          return x; 
      }
      int getY()            
      {  
          return y; 
      }
  };
  
  int main()
  {
      Point p1(10, 15); // 这里调用了普通的构造函数
      
      Point p2 = p1; // 这里调用了拷贝构造函数
      
   
      // 访问由构造函数赋值的变量
      cout << "p1.x = " << p1.getX() << ", p1.y = " << p1.getY();
      cout << "\np2.x = " << p2.getX() << ", p2.y = " << p2.getY();
  
      return 0;
  }
  ~~~

  **输出：**

  ~~~
  p1.x = 10, p1.y = 15
  p2.x = 10, p2.y = 15
  ~~~

- 复制对象把它作为参数传递给函数，即值传递的方式给函数参数传值

  **示例：**

  ~~~c++
  class Point 
  {
  private:
      int x, y;
  public:
      Point(int x1, int y1) 
      {
          x = x1;
          y = y1;
      }
      Point(const Point& p2) 
      {
          x = p2.x;
          y = p2.y;
      }
      int getX() 
      {
          return x;
      }
      int getY() 
      {
          return y;
      }
  };
  
  void displayPoint(Point p) 
  {
      cout << "x = " << p.getX() << ", y = " << p.getY() << endl;
  }
  
  int main() 
  {
      Point p1(10, 15);
      Point p2 = p1;
      displayPoint(p1);
      displayPoint(p2);
      return 0;
  }
  ~~~

  **输出：**

  ~~~
  x = 10, y = 15
  x = 10, y = 15
  ~~~

  **解释：**

  使用值传递的方式传递对象参数，这意味着函数将接收一个新的对象副本，而不是原始对象本身。这个新对象副本将在函数内部使用，而原始对象本身则不会受到任何影响。

  在 `main` 函数中，我们创建了两个 Point 对象 `p1` 和 `p2`，并将 `p1` 复制到 `p2` 中。然后我们调用 `displayPoint` 函数两次，将 `p1` 和 `p2` 作为参数传递给该函数。在函数内部，我们使用了值传递的方式传递对象参数，因此 `displayPoint` 函数接收到了 `p1` 和 `p2` 的副本，并显示它们的 x 和 y 坐标。

- 复制对象，值传递方式从函数返回这个对象。

  **示例：**

  ~~~c++
  class Point 
  {
  private:
      int x, y;
  public:
      Point(int x1, int y1) 
      {
          x = x1; 
          y = y1; 
      }
      Point(const Point &p) 
      {
          x = p.x; 
          y = p.y; 
      }
      int getX() 
      {
          return x; 
      }
      int getY() 
      { 
          return y; 
      }
  };
  
  // 返回 Point 对象，使用值传递方式
  Point getPoint(int x, int y)
  {
      Point p(x, y);
      return p;
  }
  
  int main() 
  {
      Point p1(10, 15);
      Point p2(p1); // 使用拷贝构造函数复制对象
      Point p3 = getPoint(20, 25);
      cout << "p1: x = " << p1.getX() << ", y = " << p1.getY() << endl;
      cout << "p2: x = " << p2.getX() << ", y = " << p2.getY() << endl;
      cout << "p3: x = " << p3.getX() << ", y = " << p3.getY() << endl;
      return 0;
  }
  ~~~

  **输出：**

  ```
  p1: x = 10, y = 15
  p2: x = 10, y = 15
  p3: x = 20, y = 25
  ```

  **解释：**

  在 `main` 函数中，我们创建了三个 Point 对象 `p1`、`p2` 和 `p3`。我们使用 `p1` 来初始化 `p2`，这里使用了拷贝构造函数。我们还调用了函数 `getPoint`，该函数使用值传递方式返回一个 Point 对象。在 `main` 函数中，我们将该返回值赋值给 `p3`，并将它们的 x 和 y 坐标正确地复制到了它们的副本中，同时使用值传递方式从函数返回对象也没有出现问题。
## 构造函数定义规则

---

- 默认情况下C++编译器会自动给一个类添加至少3个函数

  - 默认构造函数，无参，函数体为空
  - 默认析构函数，无参，函数体为空
  - 默认拷贝构造函数，对属性进行值拷贝

- 构造函数的定义规则：

  - 如果用户定义有参构造函数，C++不再提供默认无参构造函数，但是会提供默认拷贝构造函数
  - 如果用户定义拷贝构造函数，C++不在提供其他任何构造函数

- **示例1：**

  当用户定义有参构造函数时，C++不再提供默认无参构造函数，但是会提供默认拷贝构造函数。

  ~~~C++
  class Person 
  {
  public:
      Person(int age) 
      {
          this->age = age;
      }
  private:
      int age;
  };
  
  int main() 
  {
      Person p;// 编译错误，因为没有默认无参构造函数
      
      Person p2(18);// 正确
      
      return 0;
  }
  ~~~

- **示例2：**

  当用户定义拷贝构造函数时，C++不再提供其他任何构造函数。

  ```cpp
  class Person 
  {
  public:
      Person(const Person& other) 
      {
          this->age = other.age;
      }
  private:
      int age;
  };
  
  int main() 
  {
      Person p;// 编译错误，因为没有默认无参构造函数
      
      Person p2(p);// 编译错误，因为没有默认拷贝构造函数
      
      return 0;
  }
  ```

  **示例3：**

  ~~~c++
  #include <iostream>
  using namespace std;
  
  class MyClass {
  public:
      int num;
      char ch;
  };
  
  int main() 
  {
      MyClass obj1; // 会调用默认构造函数
      obj1.num = 10;
      obj1.ch = 'a';
      MyClass obj2 = obj1; // 会调用默认拷贝构造函数
      cout << "obj1: " << obj1.num << " " << obj1.ch << endl;
      cout << "obj2: " << obj2.num << " " << obj2.ch << endl;
      return 0;
  }
  
  ~~~

  **输出结果：**

  ~~~
  obj1: 10 a
  obj2: 10 a
  ~~~

## 深拷贝与浅拷贝

---

- **浅拷贝**

  - 编译器自动提供的拷贝构造函数属于浅拷贝，浅拷贝会将原对象中成员的值逐字节的复制给新对象中对应成员的值。
  - 当类中含有指针成员时，浅拷贝也会逐字节的将原对象的指针成员所指向的地址复制给新对象中对应的指针成员，使得新对象中的对应的指针成员也指向这块地址，使得两个对象中对应的指针成员共用一个地址。
  - 因此，当修改其中一个对象的指针成员时，另一个对象对应的成指针员也会发生改变。
  - 当手动为指针成员开辟存储空间时，浅拷贝会使得两个对象中对应的指针成员指向同一个地址。
  - 手动开辟的内存空间应该手动释放，当使用过浅拷贝的两个对象的生命周期结束时，容易导致对应指针成员指向的地址空间重复释放，从而使得程序崩溃报错。

  总结：

  - 对象拷贝后，两个对象的某些指针成员共享同一块内存，当其中一个对象的值改变时，另一个对象的值也会跟着改变，这会导致程序出现难以预料的错误。

  - 当对象被释放时，由于两个对象成员共享同一块内存，可能会导致重复释放内存的问题，从而导致程序崩溃。

  - 当对象中存在动态内存分配的指针时，由于两个对象共享同一块内存，可能会导致指针指向的内存被重复释放的问题，从而导致程序崩溃。

  - 因此，在设计类时，如果类的成员中存在指针或动态内存分配的情况，应该尽量避免使用浅拷贝，而应该使用深拷贝来避免上述问题。

  **示例：**

  ~~~c++
  #include <iostream>
  using namespace std;
  class preson
  {
  public:
  	int age;
  	int* height;
  
  	preson(int m_age,int m_height)//preson的有参构造函数
  	{
  		age = m_age;
  		height = new int(m_height);//堆区开辟的内存应该手动释放
  		cout << "preson的有参构造函数调用" << endl;
  	}
  	~preson()
  	{
  		cout << "preson的析构函数调用" << endl;
  		//浅拷贝会导致同一块内存重复释放，导致程序异常
  		if (height != NULL)
  		{
  			delete height;
  			height = NULL;
  		}
  	}
  };
  
  void test01()
  {
  	preson p1(18, 160);
  	cout << "p1年龄的地址：" << (int)&p1.age 
          << "  p1的年龄：" << p1.age 
          << "   p1身高的地址：" << (int)p1.height 
          << "  p1的身高：" << *p1.height << endl;
      
  	preson p2 = p1;//编译器自动提供拷贝构造函数，浅拷贝
      
  	cout << "p2年龄的地址：" << (int)&p2.age 
          << "  p2的年龄：" << p2.age 
          << "   p2身高的地址：" << (int)p2.height 
          << "  p2的身高：" << *p2.height 
          << endl;
  }
  
  int main()
  {
  	test01();
  	system("pause");
  	return 0;
  }
  ~~~

- **深拷贝**

  深拷贝是指在对象复制时，将一个对象的值复制到另一个新的对象中，这两个对象有不同的地址，它们各自占用不同的内存空间，这种复制方式可以避免浅拷贝的问题，同时也能保证原对象和新对象是独立的，互相不会影响。

  深拷贝通常需要手动实现，主要是在对象中存在指针或动态内存分配的情况下，需要手动复制指针指向的内存空间，而不是简单的复制指针本身。

  在实现深拷贝时，可以通过以下几种方式：

  1. 手动实现复制构造函数和赋值运算符重载函数，其中包括创建新的内存空间并复制原对象的值，释放原有内存空间等操作。
  2. 使用C++11中提供的智能指针（如`std::shared_ptr`、`std::unique_ptr`等），这些指针会自动管理内存，可以避免手动释放内存的问题。
  3. 使用标准库中的容器类（如`std::vector`、`std::list`等），这些容器类会自动管理内存，可以避免手动释放内存的问题。

  **示例：**

  ~~~c++
  #include <iostream>
  using namespace std;
  class person
  {
  public:
  	int age;
  	int* height;
  
  	person(int m_age,int m_height)//person的有参构造函数
  	{
  		age = m_age;
  		height = new int(m_height);//堆区开辟的内存应该手动释放
  		cout << "person的有参构造函数调用" << endl;
  	}
  
  	person(const person &p)//person的拷贝构造，手动实现深拷贝
  	{
  		cout << "拷贝构造函数的调用" << endl;
  		age = p.age;
  		//height = p.height;编译器自动提供的拷贝构造实现方式
  		height = new int(*p.height);//深拷贝
  	}
  	~person()
  	{
  		cout << "person的析构函数调用" << endl;
  		//浅拷贝会导致同一块内存重复释放，导致程序异常
  		if (height != NULL)
  		{
  			delete height;
  			height = NULL;
  		}
  	}
  };
  
  void test01()
  {
  	person p1(18, 160);
  	cout << "p1年龄的地址：" << (int)&p1.age 
          << "  p1的年龄：" << p1.age 
          << "   p1身高的地址：" << (int)p1.height 
          << "  p1的身高：" << *p1.height << endl;
      
  	person p2 = p1;//编译器自动提供拷贝构造函数，浅拷贝
      
  	cout << "p2年龄的地址：" << (int)&p2.age 
          << "  p2的年龄：" << p2.age <
          < "   p2身高的地址：" << (int)p2.height 
          << "  p2的身高：" << *p2.height << endl;
  }
  
  int main()
  {
  	test01();
  	system("pause");
  	return 0;
  }
  ~~~

## 初始化列表

---

C++中的初始化列表是用来初始化类成员变量的一种常用方式。

它的语法形式是在构造函数的参数列表后面使用冒号分隔符，然后列出成员变量和它们的初始值，**如下所示：**

```c++
class MyClass 
{
public:
    MyClass(int a, int b) : var1(a), var2(b) 
    {
    }
private:
    int var1;
    int var2;
};
```

在上面的代码中，构造函数的参数列表是 `(int a, int b)`，冒号后面的初始化列表是 `: var1(a), var2(b)`。它的作用是将构造函数的参数 `a` 和 `b` 分别赋值给成员变量 `var1` 和 `var2`。

- 使用初始化列表的好处是可以提高代码的执行效率，因为它避免了在构造函数内部进行赋值操作的额外开销。
- 初始化列表还可以用来初始化常量成员变量和引用类型成员变量，因为这些成员变量只能在初始化列表中被赋值初始化。
- 需要注意的是，初始化列表中的成员变量顺序应该和类定义中的顺序一致，否则会导致编译错误。
- 此外，如果某个成员变量没有在初始化列表中被赋值，它将被默认初始化，这通常是不可预知的，因此建议在初始化列表中为所有成员变量赋初始值。

## 静态成员

---

- 静态成员变量：

  静态成员变量：在类中定义的静态变量，它属于整个类而不是某个对象，所有对象共享同一份数据。它可以通过类名或对象名访问，但必须在类外初始化。

  ~~~C++
  #include <iostream>
  using namespace std;
  class Test
  {
  public:
      static int s_var; // 声明一个静态成员变量 
      void show()
      {
          cout << s_var << endl;
      }
  private:
      static int d;//私有静态成员变量
  };
  
  int Test::s_var = 30; // 必须再在类外初始化
  int Test::d = 40;
  
  int main()
  {
      Test t1;
      cout << t1.s_var << endl;//通过对象访问
      cout << Test::s_var << endl;//通过类名作用域访问
      //cout << Test::d << endl;//私有静态成员变量类外无法访问
      return 0;
  }	
  ~~~

- 静态成员函数

  - 静态成员函数不依赖于任何类对象，因此可以在没有类对象的情况下被调用。
  - 静态成员函数只能访问静态成员变量和静态成员函数。因为非静态成员变量和函数是依赖于类对象的，因此在没有类对象的情况下无法访问。
  -  静态成员函数可以直接通过类名来调用，也可以通过对象来调用。
  - 静态成员函数也有访问权限，`private`作用域下的无法访问

  **示例：**

  ```c++
  class MyClass 
  {
  private:
      int myVar;
  public:
      static int myStaticVar;
  
      MyClass(int var) 
      {
          myVar = var;
      }
  
      void myFunction() 
      {
          cout << "myVar: " << myVar << endl;
      }
  
      static void myStaticFunction() 
      {
          cout << "myStaticVar: " << myStaticVar << endl;
          // cout << "myVar: " << myVar << endl;// 错误：无法访问非静态成员变量myVar
      }
  };
  
  int MyClass::myStaticVar = 0;
  
  int main() 
  {
      MyClass obj1(10);
  
      // obj1.myStaticFunction();// 错误：不能通过对象调用静态成员函数
  
      MyClass::myStaticFunction();
  
      return 0;
  }
  ```

## `this`指针

---

- 在C++中，this指针是一个特殊的指针，它指向当前对象的地址。this指针在成员函数内部使用，它可以访问当前对象的成员变量和成员函数。

  使用this指针可以避免成员变量和局部变量的名字冲突，并且可以方便地在成员函数中访问对象的成员变量。

  **使用示例：**

  在成员函数内部，可以使用this指针来访问对象的成员变量和成员函数。

  ```c++
  #include <iostream>
  using namespace std;
  class MyClass 
  {
  public:
      void setValue(int value) 
      {
          this->value = value; // 使用this指针访问成员变量
      }
      int getValue() 
      {
          return this->value; // 使用this指针访问成员变量
      }
  private:
      int value;
  };
  int main() 
  {
      MyClass obj;
      obj.setValue(10);
      cout << obj.getValue() << endl;
      return 0;
  }
  ```

  在上面的示例中，我们创建了一个`MyClass`对象`obj`，并调用了`setValue`函数来设置`obj`的`value`成员变量的值为`10`，然后调用`getValue`函数来获取`obj`的v`alue`成员变量的值并输出。

  **错误示例：**

  ```c++
  #include <iostream>
  using namespace std;
  class MyClass 
  {
  public:
      void setValue(int value) 
      {
          value = value; // 错误的使用方式，不使用this指针
      }
      int getValue() 
      {
          return value; // 错误的使用方式，不使用this指针
      }
  private:
      int value;
  };
  
  int main()
  {
      MyClass obj;
      obj.setValue(10);
      cout << obj.getValue() << endl;
      return 0;
  }
  ```

  在上面的错误示例中，我们在`setValue`和g`etValue`函数中没有使用this指针来访问成员变量，而是直接使用了函数参数`value`和成员变量`value`。这样会导致函数参数`value`和成员变量`value`混淆，无法正确访问对象的成员变量。

## `const`修饰的成员函数和对象

---

==`this`指针的本质：==`className * const this`，`this`指针的指向不可以修改

- `const`修饰的成员函数：
  - 函数函数名后面加上`const`，称这个成员函数为常函数
  - 常成员函数内不可以修改成员属性
  - 成员属性声明时加上`mutable`关键字后在常成员函数中可以修改

**示例：**

~~~c++
class MyClass 
{
public:
    void setValue(int value) 
    { 
        m_value = value; 
    }
    int getValue() const 
    { 
        return m_value; 
    }
private:
    mutable int m_value; // mutable 修饰的变量
};

int main() 
{
    const MyClass obj; // 声明一个 const 对象
    int value = obj.getValue(); // 可以调用 const 成员函数
    // obj.setValue(10); // 错误：不能调用非 const 成员函数
    return 0;
}
~~~

相当与将`className * const this`改成`const className * const this`，这样`this`指针的指向和`this`指针指向的值都无法修改了

- **`const`修饰的对象：**

  - 声明对象前加上`const`关键字，则该对象定义为常对象
  - 常对象只能调用常成员函数

  示例：

  ```c++
  class MyClass 
  {
  public:
      void setValue(int value) 
      { 
          m_value = value; 
      }
      int getValue() const 
      { 
          return m_value; 
      }
  private:
      int m_value;
      mutable int n_value; // mutable 修饰的变量
  };
  
  int main() 
  {
      const MyClass obj; // 声明一个常对象
      int value = obj.getValue(); // 可以调用常成员函数
      // obj.setValue(10); // 错误：常对象不能调用非常成员函数
      obj.n_value = 100;//常对象可以修改 mutable 修饰的变量
      
      return 0;
  }
  ```

## 成员函数重载

---

### 普通重载

当一个类中有多个成员函数名称相同但参数列表不同的函数时，就会发生类成员函数的重载。

C++中，类成员函数重载的规则和普通函数重载的规则是一样的，必须满足函数名称相同但参数列表不同的条件。

下面是一个类成员函数重载的**示例**：

```c++
cppCopy codeclass MyClass 
{
public:
    void foo(int x) 
    {
        std::cout << "foo(int x) called with " << x << std::endl;
    }
    void foo(double x) 
    {
        std::cout << "foo(double x) called with " << x << std::endl;
    }
};

int main() 
{
    MyClass obj;
    obj.foo(1);      // 调用foo(int x)
    obj.foo(1.234);  // 调用foo(double x)
    return 0;
}
```

### 常量性重载

---

常量性重载是指一个成员函数有常量和非常量两种版本，常量版本的成员函数在其函数名后面加上 `const` 关键字，用于处理常量对象。

常量性重载函数可以让`const`对象调用特定的函数，并且不能修改对象的状态。

下面是一个常量性重载的**示例**：

```c++
cppCopy codeclass MyClass 
{
public:
    void foo() 
    {
        std::cout << "foo() called" << std::endl;
    }
    void foo() const 
    {
        std::cout << "const foo() called" << std::endl;
    }
};

int main() 
{
    MyClass obj1;
    obj1.foo();       // 调用 foo()
    const MyClass obj2;
    obj2.foo();       // 调用 const foo()
    return 0;
}
```

注意，常量性重载的成员函数需要保证其不会修改对象的状态，所以在常量成员函数中只能调用其他常量成员函数或常量数据成员，不能调用非常量成员函数或修改数据成员。

常量性重载函数中，常量类对象可以调用常量版本的成员函数，而非常量类对象则只能调用非常量版本的成员函数。

举个例子，假设我们有一个名为 `MyClass` 的类，它有两个版本的成员函数 `foo()`：

```c++
cppCopy codeclass MyClass 
{
public:
    void foo() 
    {
        std::cout << "foo() called" << std::endl;
    }
    void foo() const 
    {
        std::cout << "const foo() called" << std::endl;
    }
};
```

现在假设我们有一个常量类对象 `const MyClass obj1;` 和一个非常量类对象 `MyClass obj2;`，它们都可以调用 `foo()` 成员函数：

```c++
cppCopy codeobj1.foo(); // 调用 const foo()
obj2.foo(); // 调用 foo()
```

在普通函数的函数名后面加上 `const` 关键字是没有意义的。因为 `const` 关键字用于修饰类的成员函数，它表示该成员函数不会修改类的成员变量。而普通函数没有成员变量，所以 `const` 关键字对它们没有意义。

在普通函数中，如果要实现类似于常量性重载的效果，可以使用函数重载。例如，可以编写一个非常量版本和一个常量版本的同名函数，分别用于处理非常量对象和常量对象。

**例如：**

```c++
cppCopy codevoid foo(int x) 
{
    std::cout << "foo(int x) called with " << x << std::endl;
}

void foo(const int x) 
{
    std::cout << "const foo(const int x) called with " << x << std::endl;
}
```

这样，可以让非常量对象调用非常量版本的函数，常量对象调用常量版本的函数。

在普通函数的函数名后面加上 `const` 是语法上不正确的，编译器在编译时会报错。

这是因为 `const` 关键字只能用于类的成员函数中，表示该成员函数不会修改类的成员变量。普通函数没有成员变量，所以在普通函数名后面加上 `const` 关键字是没有意义的，也是非法的。

以下是一个示例，试图在普通函数中添加 `const` 关键字：

```c++
cppCopy codevoid foo(const int x) const 
{
    // ...
}
```

编译器会报错，因为它不知道如何处理这个语句，它既不是一个成员函数，也不是一个正确的普通函数。

## 友元

---

- 友元是C++中的一种特殊关系，它允许一个类的非成员函数或另一个类的成员函数访问该类的私有成员变量和函数。

**语法：**

- 友元函数的声明：在类的内部，使用关键字`friend`声明一个函数为友元函数，如下所示：

```c++
class MyClass 
{
    //friend void friendFunc();//也可以在这里声明
public:
    friend void friendFunc();
private:
    int x;
};
```

- 友元类的声明：在类的内部，使用关键字`friend`声明一个类为友元类，如下所示：

```c++
class MyClass 
{
    //friend class FriendClass;//也可以在这里声明
public:
    friend class FriendClass;
private:
    int x;
};
```

### 全局函数做友元

---

**示例：**

```C++
class MyClass 
{
    friend void setNum(MyClass& obj, int n);//将全局函数 setNum 声明为友元
private:
    int num;
public:
    MyClass() : num(0)
    {
    }
};

void setNum(MyClass& obj, int n) 
{
    obj.num = n;
}

int main() 
{
    MyClass obj;
    setNum(obj, 10);
    cout << obj.num << endl;
    return 0;
}
```

在上面的代码中，我们定义了一个名为`MyClass`的类，其中包含一个私有变量`num`。

然后我们声明了一个全局函数`setNum`作为`MyClass`的友元函数，这样`setNum`就可以访问`MyClass`的私有变量`num`了。

在主函数中我们创建了一个`MyClass`对象obj，然后调用`setNum`函数并将`obj`和`10`作为参数传递进去，最后输出`obj`的`num`值，即得到了10。

### 类做友元

---

**示例：**其中类`B`被声明为类A的友元，可以访问类`A`的私有成员变量`x`

```c++
class A 
{
    friend class B; // 类B是类A的友元
public:
    A(int value) : x(value) 
    {
    }
private:
    int x;
};

class B 
{
public:
    void printX(A & a) 
    {
        std::cout << "x is " << a.x << std::endl; // 可以访问类A的私有成员变量x
    }
};

int main() 
{
    A a(10);
    B b;
    b.printX(a); // 输出：x is 10
    return 0;
}
```

### 成员函数做友元

---

**示例：：**其中类`A`的成员函数`funcA()`是类`B`的友元函数，可以访问类`B`的私有成员变量

```c++
class B; // 前置声明

class A 
{
public:
    void funcA(B& objB); // 声明 void funcA 函数，用于访问 B 中的私有成员
};

class B 
{
    friend void A::funcA(B& objB); // 声明A的成员函数为友元函数
public:
    B(int x): x(x) 
    {
    }
private:
    int x;
};

void A::funcA(B& objB) //类外定义void funcA 函数
{
    cout << "B的私有成员变量x的值为：" << objB.x << endl;
}

int main() 
{
    B objB(10);
    A objA;
    objA.funcA(objB); // 调用A的成员函数，输出B的私有成员变量x的值
    return 0;
}
```

**输出：**

```
B的私有成员变量x的值为：10
```

# 运算符重载

概念：对已有运算符进行定义，赋予其另一种功能，以适应不同数据类型

## 四则运算符重载

---

`operator+`

`operator-`

`operator*`

`operator/`

```c++
#include <iostream>
using namespace std;
class Vector 
{
public:
    float x, y, z;

    // 构造函数
    Vector(float x = 0, float y = 0, float z = 0) 
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // 重载"+"运算符
    Vector operator+(const Vector& v) const
    {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

    // 重载"-"运算符
    Vector operator-(const Vector& v) const
    {
        return Vector(x - v.x, y - v.y, z - v.z);
    }

    // 重载"<<"运算符
    friend ostream& operator<<(ostream& os, const Vector& v) 
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
};

//全局 重载"*"运算符
Vector operator*(const Vector& v1, const Vector& v2)
{
    return Vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

//全局 重载"/"运算符
Vector operator/(const Vector& v1, const Vector& v2)
{
    // 检查除数是否为0
    if (scalar == 0) 
    {
        cout << "Error: Division by zero!" << endl;
        return v;
    }

    return Vector(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);    // 执行除法运算
}

int main() 
{
    Vector v1(1, 2, 3);
    Vector v2(4, 5, 6);
    Vector v3 = v1 + v2;
    Vector v4 = v1 - v2;
    Vector v5 = v1 * v2;
    Vector v6 = v1 / v2;
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v1 + v2 = " << v3 << endl;
    cout << "v1 - v2 = " << v4 << endl;
    cout << "v1 * v2 = " << v5 << endl;
    cout << "v1 / v2 = " << v6 << endl;  
    return 0;
}
```

## 左移（`<<`）运算符重载

---

左移运算符重载不可以定义在类中作为类的成员函数，只能定义为全局函数，如果定义在类中，需要加上`friend`关键字，但默认是全局函数

`cout`是一个`ostream`对象，重载时需要指定参数类型，并返回这个流对象，使得`<<`可以链式调用。

**代码示例：**

```c++
class Vector 
{
public:
    float x, y, z;
	friend ostream& operator<<(ostream& os, const Vector& v) 
	{
		os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    	return os;
	}
}
```

或者

```c++
class Vector 
{
    friend ostream& operator<<(ostream& os, const Vector& v) 
public:
    float x, y, z;
}

ostream& operator<<(ostream& os, const Vector& v) 
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}
```

## 自增（`++`）运算符重载

---

前置++运算符重载，要返回引用，同样对于前置`--`运算符也一样

**重载前置自增运算符（++）：**

```cpp
class Counter 
{
private:
    int count;

public:
    Counter(int initialCount = 0) : count(initialCount) {}

    // 重载前置自增运算符
    Counter& operator++() 
    {
        count++;
        return *this;
    }

    int getCount() const 
    {
        return count;
    }
};

int main() 
{
    Counter c(5);
    cout << "Initial count: " << c.getCount() << endl;

    ++c;  // 使用前置自增运算符
    cout << "Count after increment: " << c.getCount() << endl;

    return 0;
}
```

后置++运算符重载，要返回值，同样对于前置`--`运算符也一样

**重载后置自增运算符（++）：**

```cpp
class Counter 
{
private:
    int count;

public:
    Counter(int initialCount = 0) : count(initialCount) {}

    // 重载后置自增运算符
    Counter operator++(int) 
    {
        Counter temp(count);  // 创建临时对象保存当前值
        count++;
        return temp;  // 返回保存的临时对象
    }

    int getCount() const 
    {
        return count;
    }
};

int main() 
{
    Counter c(5);
    cout << "Initial count: " << c.getCount() << endl;

    Counter d = c++;  // 使用后置自增运算符
    cout << "Count after increment: " << c.getCount() << endl;
    cout << "Value before increment: " << d.getCount() << endl;

    return 0;
}
```

**重载前置自增运算符时的注意事项：**

- 前置自增运算符的重载函数返回引用，以便允许连续的自增操作。
- 在重载前置自增运算符时，首先对对象进行自增操作，然后返回自增后的对象。

**重载后置自增运算符时的注意事项：**

- 后置自增运算符的重载函数需要使用一个额外的整型参数（`int`）来区分后置自增运算符重载函数和前置自增运算符重载函数。
- 在重载后置自增运算符时，首先创建一个临时对象来保存自增前的对象值，然后对对象进行自增操作，最后返回保存的临时对象。

在使用重载后置自增运算符时，需要注意后置自增运算符返回的是自增之前的值，而不是自增之后的值。

因此，在示例代码中，将后置自增运算符的返回值存储在一个新的`Counter对`象中（变量`d`），以便打印出自增之前的值。

## 赋值（`=`）运算符重载（深拷贝）

---

当重载赋值运算符`=`时，要确保进行的是深拷贝，以防止内存重复释放。

**代码示例：**

```c++
#include <iostream>

class MyClass 
{
private:
    int* data; // 指针成员，动态分配的数据

public:
    MyClass(int value) 
    {
        data = new int;
        *data = value;
    }

    // 拷贝构造函数
    MyClass(const MyClass& other)
    {
        data = new int;
        *data = *(other.data);
    }

    // 赋值运算符重载
    MyClass& operator=(const MyClass& other) 
    {
        // 检查自我赋值
        if (this == &other)
        {
            return *this;
        }
        // 执行深拷贝
        delete data; // 释放原有内存
        data = new int;
        *data = *(other.data);

        return *this;
    }

    ~MyClass() 
    {
        delete data;
    }

    int getData() 
    {
        return *data;
    }
};

int main() 
{
    MyClass obj1(5);
    MyClass obj2(10);

    obj2 = obj1; // 使用赋值运算符重载进行赋值

    std::cout << obj1.getData() << std::endl; // 输出：5
    std::cout << obj2.getData() << std::endl; // 输出：5

    return 0;
}
```

在这个示例中，`MyClass`类包含一个动态分配的整型数据`data`。

在拷贝构造函数中，我们为`data`创建新的内存，并将其值设置为被复制对象的值。

在赋值运算符重载中，首先检查是否是自我赋值，然后执行深拷贝。先删除原有的`data`内存，并为其分配新的内存，然后将其值设置为被赋值对象的值。

通过这样的实现，可以确保在赋值过程中进行深拷贝，从而避免内存重复释放的问题。

## 其他运算符重载的说明

---

以下是C++中常见的运算符及其简单说明和是否能重载：

| 运算符     | 说明                                                         | 是否能重载（只标识不能重载的） |
| ---------- | ------------------------------------------------------------ | ------------------------------ |
| `+`        | 加法运算符，用于执行两个操作数的相加操作。                   |                                |
| `-`        | 减法运算符，用于执行两个操作数的相减操作。                   |                                |
| `*`        | 乘法运算符，用于执行两个操作数的相乘操作。                   |                                |
| `/`        | 除法运算符，用于执行两个操作数的相除操作。                   |                                |
| `%`        | 取模运算符，返回两个操作数相除后的余数。                     |                                |
| `++`       | 自增运算符，用于将操作数的值增加1。                          |                                |
| `--`       | 自减运算符，用于将操作数的值减少1。                          |                                |
| `=`        | 赋值运算符，用于将右侧操作数的值赋给左侧操作数。             |                                |
| `+=`       | 加法赋值运算符，将右侧操作数的值加到左侧操作数上。           |                                |
| `-=`       | 减法赋值运算符，将右侧操作数的值从左侧操作数中减去。         |                                |
| `*=`       | 乘法赋值运算符，将右侧操作数的值乘到左侧操作数上。           |                                |
| `/=`       | 除法赋值运算符，将左侧操作数除以右侧操作数的值。             |                                |
| `%=`       | 取模赋值运算符，将左侧操作数取模右侧操作数的值。             |                                |
| `==`       | 相等运算符，用于比较两个操作数是否相等。                     |                                |
| `!=`       | 不等运算符，用于比较两个操作数是否不相等。                   |                                |
| `>`        | 大于运算符，用于比较左侧操作数是否大于右侧操作数。           |                                |
| `<`        | 小于运算符，用于比较左侧操作数是否小于右侧操作数。           |                                |
| `>=`       | 大于等于运算符，用于比较左侧操作数是否大于或等于右侧操作数。 |                                |
| `<=`       | 小于等于运算符，用于比较左侧操作数是否小于或等于右侧操作数。 |                                |
| `&&`       | 逻辑与运算符，用于执行逻辑与操作。                           |                                |
| `||`       | 逻辑或运算符，用于执行逻辑或操作。                           |                                |
| `!`        | 逻辑非运算符，用于执行逻辑非操作。                           |                                |
| `&`        | 按位与运算符，对操作数的每个位执行逻辑与操作。               |                                |
| `|`        | 按位或运算符，对操作数的每个位执行逻辑或操作。               |                                |
| `^`        | 按位异或运算符，对操作数的每个位执行逻辑异或操作。           |                                |
| `~`        | 按位取反运算符，对操作数的每个位取反。                       |                                |
| `<<`       | 左移运算符，将操作数的位向左移动指定的位数。                 |                                |
| `>>`       | 右移运算符，将操作数的位向右移动指定的位数。                 |                                |
| `&=`       | 按位与赋值运算符，将右侧操作数的值与左侧操作数进行按位与操作。 |                                |
| `|=`       | 按位或赋值运算符，将右侧操作数的值与左侧操作数进行按位或操作。 |                                |
| `^=`       | 按位异或赋值运算符，将右侧操作数的值与左侧操作数进行按位异或操作。 |                                |
| `<<=`      | 左移赋值运算符，将左侧操作数的值向左移动指定的位数。         |                                |
| `>>=`      | 右移赋值运算符，将左侧操作数的值向右移动指定的位数。         |                                |
| `sizeof`   | 大小运算符，用于返回一个对象或数据类型的大小（以字节为单位）。 | 否                             |
| `?:`       | 条件运算符（三目运算符），用于根据条件选择不同的值。         | 否                             |
| `.`        | 成员访问运算符，用于访问结构体或类的成员。                   | 否                             |
| `->`       | 成员指针访问运算符，用于通过指针访问结构体或类的成员。       |                                |
| `[]`       | 下标运算符，用于访问数组或容器中的元素。                     |                                |
| `()`       | 函数调用运算符，用于调用函数。                               |                                |
| `new`      | 动态分配运算符，用于在堆上分配内存空间。                     |                                |
| `delete`   | 动态释放运算符，用于释放动态分配的内存空间。                 |                                |
| `new[]`    | 数组动态内存分配运算符，用于在堆上分配数组内存               |                                |
| `delete[]` | 数组动态内存释放运算符，用于释放先前分配的数组内存           |                                |
| `.*`       | 成员指针运算符，用于通过指针访问类的成员函数或成员变量。     | 否                             |
| `->*`      | 成员指针运算符，用于通过指针访问类的成员函数或成员变量。     |                                |
| `::`       | 作用域解析运算符，用于访问命名空间、类、结构体或枚举的成员。 | 否                             |
| `,`        | 逗号运算符，用于在表达式中分隔多个表达式，并按顺序执行       |                                |

- 上述列表列出了绝大部分常用的运算符，但不是所有运算符的完整列表。还有其他一些运算符它们使用相对较少，这里不列出。

- 对于其余一些简单的运算符如：比较运算符、逻辑运算符等，请以上面四篇运算符重载的示例作为参考。

- 剩下的一些功能较为复杂的运算符如：`new`、`delete`、`,`、`->*`等的重载属于进阶内容，视情况而定，这里不给出示例代码。

# 继承

## 继承方式

---

- 继承方式分为三种：公共继承（public）、保护继承（protected）、私有继承（private）

- 所有继承方式均不可访问父类中的私有成员

- 公共继承父类的子类，其父类的成员的访问属性不变。即：公共继承，父类中的公共成员在子类中仍然是公共成员，父类中的保护成员在子类中仍然是保护成员

- 私有继承的子类中，除了父类中的私有成员，其余所有的成员在子类中都变为私有成员。

## 继承中的对象模型

---

父类中私有成员也是被子类继承下去了，只是由编译器给隐藏后访问不到。

在C++中，子类会继承父类的所有非静态成员，包括私有成员。但是，对于私有成员，编译器会隐藏它们，使其在子类中不可直接访问。这是通过访问权限控制来实现的。

子类继承了父类的私有成员，但无法直接访问这些私有成员。私有成员在子类中仍然存在，并占据相应的内存空间，但无法通过子类对象或指针直接访问。

子类可以通过继承的公有和保护成员来间接访问父类的私有成员。子类可以通过调用父类的公有和保护成员函数来操作父类的私有成员。这样，子类可以间接地使用继承下来的私有成员。

继承使子类拥有了父类的所有非静态成员，但私有成员被编译器隐藏起来，无法直接访问。子类通过父类的公有和保护成员来间接操作和使用继承的私有成员，从而达到了私有成员在子类中不可访问的效果。

私有成员的存在对于子类是有影响的。子类对象会继承父类的私有成员，这些私有成员在子类对象中占据内存空间。如果子类定义了与父类私有成员名称相同的成员，那么子类的成员是不会覆盖父类的私有成员的，父类私有成员仍然存在，仍然占据内存空间。

## 继承中的构造和析构顺序

---

继承中先调用父类构造函数，再调用子类构造函数，析构顺序与构造相反。

先创建父类对象，再创建子类对象。

## 同名成员处理

---

访问子类同名成员直接访问即可

访问父类同名成员需要加作用域

如果子类中出现和父类同名的成员函数，子类的同名成员会隐藏掉父类中所有同名成员函数

如果想访问到父类中被隐藏的同名成员函数，需要加作用域



静态成员和非静态成员出现同名，处理方式一致

- 访问子类同名成员直接访问即可

- 访问父类同名成员需要加作用域

静态成员变量：所有对象都共享同一份数据，编译阶段分配内存，类内声明，类外初始化

静态成员函数：只能访问静态成员变量

## 多继承

---

语法：

 `class子类 : 继承方式 父类1, 继承方式 父类2 ...`

多继承可能会引发父类中有同名成员出现，需要加作用域区分

语法示例：

```c++
class A
{};

class B
{};

class C
{};

class D : public A, protected C, private B 
{};
```



## 菱形继承和虚继承

---

菱形继承带来的主要问题是子类继承两份相同的数据，导致资源浪费以及形同继承内容无意义

![](data:image/png;base64,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)



为了解决多继承时的命名冲突和冗余数据问题，C++ 提出了虚继承，使得在派生类中只保留一份间接基类的成员。

在继承之前加上关键字`virtual`变为虚继承。

![](data:image/png;base64,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)

语法示例：

```c++
class A
{};

class B : virtual public A	//B虚继承A
{};

class C : virtual public A	//C虚继承A
{};

class D : public A, public B
{};
```

这样子，`D`类中就只有一份`A`类中的数据了。

视频讲解：[【黑马程序员匠心之作|C++教程从0到1入门编程,学习编程不再难】](https://www.bilibili.com/video/BV1et411b73Z?p=134&vd_source=03da7de0e80f9ff60fdeca7b512ba3f5)

# 多态

## 多态的概念

---

多态是C++面向对象三大特性之一。它意味着调用成员函数时，会根据调用函数的对象的类型来执行不同的函数。

在C++中，允许通过基类型的指针或引用去访问派生对象中的函数，并允许需要执行的函数在运行时进行延迟绑定 (Late binding)，这称之为多态。

多态的目的是为了==接口重用==。也即，不论传递过来的究竟是类的哪个对象，函数都能够通过同一个接口调用到适应各自对象的实现方法。这样可以提高代码的可扩展性和可维护性。

当类之间存在层次结构，并且类之间是通过继承关联时，就会用到多态。

C++ 多态意味着调用成员函数时，会根据调用函数的对象的类型来执行不同的函数。

多态分为两类

- 静态多态：函数重载和运算符重载属于静态多态，复用函数名

- 动态多态：派生类和虚函数实现运行时多态

静态多态和动态多态区别：

- 静态多态的函数地址早绑定–编译阶段确定函数地址

- 动态多态的函数地址晚绑定–运行阶段确定函数地址

## 虚函数

---

虚函数是 C++ 中的一个重要概念，它允许基类指针能够在运行时动态地绑定到派生类对象的成员函数上。

简单来说，虚函数是一个在基类中声明的函数，在派生类中可以被重写。在运行时，如果使用基类指针调用虚函数，那么实际上会调用指向派生类对象的函数。

使用虚函数可以实现多态性，使得程序能够根据实际的对象类型来调用相应的成员函数，而不是在编译时就确定调用的函数。

在 C++ 中，将函数声明为虚函数的方法是在函数声明前加上关键字`virtual`。

派生类和虚函数实现运行时多态属于动态多态，动态多态的满足条件 ：

- 有继承关系
- 子类重写父类的虚函数

示例代码：

```c++
#include <iostream>
using namespace std;

class animal
{
public:
	virtual void speak01()//虚函数
	{
		cout << "动物在叫" << endl;
	}
	void speak02()
	{
		cout << "动物在叫" << endl;
	}
};

class dog :public animal
{
public:
	void speak01()
	{
		cout << "汪汪汪" << endl;
	}
	void speak02()
	{
		cout << "汪汪汪" << endl;
	}
};

class cat : public animal
{
public:
	void speak01()
	{
		cout << "喵喵喵" << endl;
	}
	void speak02()
	{
		cout << "喵喵喵" << endl;
	}
};

//执行说话的函数
//地址早绑定在编译阶段确定函数地址
//如果想执行让猫喵喵喵，那么这个函数地址就不能提前绑定，需要在运行阶段进行绑定，地址晚绑定

void speak(animal& animal)
{
	animal.speak01();
	animal.speak02();
}

void test01()
{
	cat cat01;
	dog dog01;
	speak(cat01);
	speak(dog01);
}

int main()
{
	test01();

	system("pause>nul");
}
```

## 虚函数原理剖析

---

普通函数（非静态成员函数），不属于类的对象上，下面这个类的大小为1（空类大小为1）：

```c++
class animal
{
public:
    void speak()
    {
        cout << "动物在说话" << endl;
    }
    
}

int main()
{
    cout<< sizeof(animal) << endl;
}
```

输出：

```shell
1
```

当在非静态成员函数前加上`virtual`关键字后，原来的普通函数变成一个虚函数，这时候类的大小变为4。

```c++
class animal
{
public:
   virtual void speak()
    {
        cout << "动物在说话" << endl;
    }
    
}

int main()
{
    cout<< sizeof(animal) << endl;
}
```

输出：

```shell
4
```

实际上，加上`virtual`关键字后，普通函数变成一个虚函数，虚函数实际上是一个指针，这个指针称为虚函数指针或虚函数表指针。因而类中多了一个指针类型的成员，大小发生了变化。

这个指针指向一个虚函数表，表的内部记录着这个类作用域下的对应的函数的地址。当子类继承后，子类成员中同样也有了一个虚函数指针，也指向一个虚函数表，如果没有重写这个虚函数，因为继承关系表中的内容与父类是完全一样的，表中的函数地址仍然是父类中对应的函数地址。当子类重写了这个虚函数，子类中的虚函数表内部会将原先父类中对应的函数地址替换成子类中重写的函数的函数地址。

当父类指针或引用指向子类对象时就发生了多态，当调用虚函数时，就发生了动态的多态，由于是子类对象调用，则从子对象的虚函数表中寻找子类重写后的函数。

## 纯虚函数和抽象类

---

在多态中，通常父类中虚函数的实现是毫无意义的，主要都是调用子类重写的内容

因此可以将虚函数改为纯虚函数

纯虚函数语法：`virtual返回值类型 函数名(参数列表) = 0 ;`

当类中有了纯虚函数，这个类也称为抽象类。

抽象类特点:

- 无法实例化对象

- 抽象类的子类必须要重写父类中的纯虚函数，否则也属于抽象类

## 虚析构和纯虚析构

---

多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码

解决方式:将父类中的析构函数改为虚析构或者纯虚析构

虚析构和纯虚析构共性：

- 可以解决父类指针释放子类对象

- 都需要有具体的函数实现

虚析构和纯虚析构区别：

- 如果是纯虚析构，该类属于抽象类，无法实例化对象。

- 纯虚析构需要有函数定义。



示例（父类指针指向子类对象，会导致子类无法析构）：

```c++
#include <iostream>
using namespace std;

class animal
{
public:
	animal()
	{
		cout << "animal的构造函数" << endl;
	}

	~animal()
	{
		cout << "animal的析构函数" << endl;
	}

	virtual void speak01() = 0;
};


class cat : public animal
{
public:
	cat(string name_)
	{
		cout << "cat的构造函数" << endl;
		name = new string(name_);
	}

	~cat()
	{
		cout << "cat的析构函数" << endl;

		if (name != nullptr)
		{
			cout << "cat成员的内存释放" << endl;
			delete name;
		}
	}
	void speak01()
	{
		cout << "喵喵喵" << endl;
	}
	string* name = nullptr;
};

void test01()
{
	animal* ani = new cat("tom");
	ani->speak01();
	delete ani;
}

int main()
{
	test01();

	system("pause>nul");
}
```

运行结果：

```shell
animal的构造函数
cat的构造函数
喵喵喵
animal的析构函数
```

解决方法：将父类对的析构函数改成虚函数（虚析构）：

```c++
#include <iostream>
using namespace std;

class animal
{
public:
	animal()
	{
		cout << "animal的构造函数" << endl;
	}

	virtual ~animal()
	{
		cout << "animal的析构函数" << endl;
	}

	virtual void speak01() = 0;
};


class cat : public animal
{
public:
	cat(string name_)
	{
		cout << "cat的构造函数" << endl;
		name = new string(name_);
	}

	~cat()
	{
		cout << "cat的析构函数" << endl;

		if (name != nullptr)
		{
			cout << "cat成员的内存释放" << endl;
			delete name;
		}
	}
	void speak01()
	{
		cout << "喵喵喵" << endl;
	}
	string* name = nullptr;
};


void test01()
{
	animal* ani = new cat("tom");
	ani->speak01();
	delete ani;
}

int main()
{
	test01();

	system("pause>nul");
}
```

运行结果：

```shell
animal的构造函数
cat的构造函数
喵喵喵
cat的析构函数
cat成员的内存释放
animal的析构函数
```

如果父类的析构函数是纯虚函数（纯虚析构），则必须要有函数体的实现（定义），需要在类外定义，否则运行报错（链接阶段找不到定义）。

## `override`关键字

---

`override`是C++11中引入的一个新关键字，用于显式地指定某个成员函数为虚函数的重写版本。当你在派生类中重写基类的虚函数时，可以在该函数的声明后面加上`override`关键字，表示该函数是重写基类的虚函数。

使用`override`关键字有两个好处：

- 它能够帮助你避免一些常见的错误。例如，如果你在派生类中重写基类的虚函数时，不小心将函数名或参数列表写错了，编译器会报错，提示你这不是一个有效的重写。

- 它能够提高代码的可读性。当其他人阅读你的代码时，看到`override`关键字，就能够立即知道这是一个重写基类虚函数的函数。

下面是一个简单的例子，演示如何使用`override`关键字：

```c++
#include <iostream>

class Base 
{
public:
    virtual void foo() 
    {
        std::cout << "Base::foo()" << std::endl;
    }
};

class Derived : public Base 
{
public:
    void foo() override 
    {
        std::cout << "Derived::foo()" << std::endl;
    }
};

int main() 
{
    Base* b = new Derived();
    b->foo(); // 输出 "Derived::foo()"
    delete b;
    return 0;
}
```

在上面的例子中，我们在派生类`Derived`中重写了基类`Base`的虚函数`foo()`。在重写该函数时，我们在函数声明后面加上了`override`关键字，表示这是一个重写基类虚函数的函数。

# 异常处理

传统异常处理：

通过返回不同的值来体现或处理异常

缺点：

- 返回值意义不明确

- 返回值返回一个消息

- 返回值可以忽略



## 基本语法

---

示例：

```c++
#include <iostream>
using namespace std;

auto fun(int a,int b)
{
	if (b == 0)
	{
		//throw "被除数为0";
		throw 0;//throw语句抛出异常,抛出异常为int类型 0
		//抛出异常后，直接执行catch里的代码，这里的后续代码不会执行
	}
	return (a / b);
}

void test(int a,int b)
{
	try//将可能出现异常的语句放在try语句中
	{
		cout << a << "除以" << b << "等于" << fun(a, b) << endl;;
	}
    //一个try语句可以与多个catch相匹配，但至少需要有一个catch,catch用于接收异常，可以指定接收的类型
	catch (const char* a)//接收到一个const char* 类型的异常
	{
		cout << a<< endl;
	}
	catch (int a)//接收到int 类型的异常
	{
		switch (a)//使用switch语句判断异常并处理
		{
		case 0:
			cout << "被除数等于0" << endl;
            break;
		case 1:
			//......
            break;
        //case .....
		}
	}
    catch(...)//接收除了上面int和const char*以外的其他所有类型异常，如果只有这个就表示接收所有类型异常
    {
        //...
    }
}


int main()
{
	test(10, 0);
	system("pause");
}
```

`throw`还可以抛出自定义数据类型，从而可以调用抛出对象的成员函数进一步处理。

`try`中的语句如果抛出异常，则必须进行处理，即：必须有对应的`catch`代码段进行接收。

`try`中的语句如果没有抛出异常，则后续对应的所有`catch`代码段都不会执行。

## 异常（接口）声明

---

该语法特性已在C++11后弃用，VS编译器中可以使用，无语法错误，但实际没有任何效果，同时也不建议使用该语法。这里不做介绍。

## `noexcept`关键字

---

`noexcept`用于指定函数是不会抛出异常的。这个关键字对于异常处理和代码优化非常有用。

异常接口声明的语法在C++11被移除，在未被移除之前，声明一个不会抛出异常的函数是这样的：

```c++
void func() throw()//表示这个函数不会抛出异常
{
    //...
}
```

该语法在C++11被移除，C++11后声明一个不会抛出异常的函数就要使用`noexcept`关键字

示例：

```cpp
#include <iostream>

// 声明一个会抛出异常的函数
void mightThrow() 
{
    throw "This function might throw an exception.";
}

// 声明一个不会引发异常的函数
void noThrow() noexcept //noexcept表示函数不会抛出异常
{
    std::cout << "This function will not throw any exception." << std::endl;
}
```

如果在有`noexcept`修饰的函数中抛出了异常，并且在调用时接收了异常程序则会出现断点报错。

## 异常对象的生命周期和栈解旋

---

异常被抛出后，从进入`try`块起，到异常被抛掷前，这期间在栈上构造的所有对象，都会被自动析构。

析构的顺序与构造的顺序相反，这一过程称为栈的解旋（栈解旋）

示例1（过程中会创建3个对象）：

```c++
#include <iostream>
using namespace std;

class myclass
{
public:
	myclass()
	{
		cout << "myclass的默认构造" << endl;
	}
	myclass(const myclass& other)
	{
		cout << "myclass的拷贝构造" << endl;
	}
	~myclass()
	{
		cout << "myclass的析构函数" << endl;
	}
};

void func()
{
	myclass one;	//对象一	默认构造
	throw one;		//对象二	拷贝构造
}

void test01()
{
	try
	{
		func();
	}
    //对象一	在catch接收之前析构
	catch (myclass erro)//对象三	由对象二拷贝构造
	{
		cout << "接收到myclass类型异常" << endl;
	}
    //对象二和对象三在catch段处理完异常后就析构
    	cout << "接收异常后" << endl;
}

int main()
{
	test01();
	system("pause>nul");
}


```

运行结果：

```shell
myclass的默认构造
myclass的拷贝构造
myclass的拷贝构造
myclass的析构函数
接收到myclass类型异常
myclass的析构函数
myclass的析构函数
接收异常后
```

示例2（过程中会创建两个对象）：

```c++
#include <iostream>
using namespace std;

class myclass
{
public:
	myclass()
	{
		cout << "myclass的默认构造" << endl;
	}
	myclass(const myclass& other)
	{
		cout << "myclass的拷贝构造" << endl;
	}
	~myclass()
	{
		cout << "myclass的析构函数" << endl;
	}
};

void func()
{
	throw myclass();//抛出匿名对象，避免拷贝，默认构造
}

void test01()
{
	try
	{
		func();
	}
	catch (myclass erro)//拷贝构造，由匿名对象拷贝
	{
		cout << "接收到myclass类型异常" << endl;
	}
    //匿名对象和erro析构
	cout << "接收异常后" << endl;
}


int main()
{
	test01();
	system("pause>nul");
}
```

运行结果：

```shell
myclass的默认构造
myclass的拷贝构造
接收到myclass类型异常
myclass的析构函数
myclass的析构函数
接收异常后
```

示例3（过程中会创建一个对象）：

```c++
#include <iostream>
using namespace std;

class myclass
{
public:
	myclass()
	{
		cout << "myclass的默认构造" << endl;
	}
	myclass(const myclass& other)
	{
		cout << "myclass的拷贝构造" << endl;
	}
	~myclass()
	{
		cout << "myclass的析构函数" << endl;
	}
};

void func()
{
	throw myclass();//抛出匿名对象

}

void test01()
{
	try
	{
		func();
	}
	catch (myclass& erro)//引用接收throw抛出的匿名对象
	{
		cout << "接收到myclass类型异常" << endl;
	}
	cout << "接收异常后" << endl;
}


int main()
{
	test01();
	system("pause>nul");
}


```

运行结果：

```shell
myclass的默认构造
接收到myclass类型异常
myclass的析构函数
接收异常后
```

总结：

`throw`抛出的异常对象在`catch`处理完后才会被释放，使用`throw`抛出匿名对象可以在整个异常处理过程中只产生一个对象，避免拷贝构造。

抛出的堆区开辟的对象需要在`catch`中手动释放。

## 异常中的多态

---

在`catch`中使用父类的引用接受子类对象，就会发生多态。当父类中有虚函数，并且子类重写后，那么`catch`中调用父类成员函数时就会调用子类中重写的函数。

代码示例：

```c++
#include <iostream>
using namespace std;

class father
{
public:

	virtual void error(){}
};

class son01 : public father
{
public:
	void error()
	{
		cout << "son01异常" << endl;
	}
};

class son02 : public father
{
public:
	void error()
	{
		cout << "son02异常" << endl;
	}
};

void func01(int a, int b)
{
	if (a == 0)
	{
		throw son01();
	}
	if (b == 0)
	{
		throw son02();
	}
}

void test01()
{
	try
	{
		func01(0, 10);
	}
	catch (father& fa)
	{
		fa.error();
	}
	try
	{
		func01(10, 0);

	}
	catch(father& fa)
	{
		fa.error();
	}
}

int main()
{
	test01();
	system("pause>nul");
}
```

运行结果：

```shell
son01异常
son02异常
```

## 标准异常类`std::exception` 

---

提供一致的接口，以通过`throw`表达式处理错误。

标准库所生成的所有异常继承自 `std::exception`



继承关系（C++11前）：



![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAkAAAAHgCAMAAAB6sCJ3AAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAAyhpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuNi1jMDE0IDc5LjE1Njc5NywgMjAxNC8wOC8yMC0wOTo1MzowMiAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RSZWY9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZVJlZiMiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENDIDIwMTQgKE1hY2ludG9zaCkiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6QTQ5MjQ4NkZDMkNCMTFFODhCQ0VENDkyNTk1RTIwNjYiIHhtcE1NOkRvY3VtZW50SUQ9InhtcC5kaWQ6QTQ5MjQ4NzBDMkNCMTFFODhCQ0VENDkyNTk1RTIwNjYiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDpBNDkyNDg2REMyQ0IxMUU4OEJDRUQ0OTI1OTVFMjA2NiIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDpBNDkyNDg2RUMyQ0IxMUU4OEJDRUQ0OTI1OTVFMjA2NiIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/Pr+5vcgAAAGAUExURdbX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)



部分异常类描述：

| 异常类                              | 描述                                                         |
| ----------------------------------- | ------------------------------------------------------------ |
| **`std::exception`**                | **该异常是所有标准 C++ 异常的父类。**                        |
| `std::bad_alloc`                    | 用`new`动态分配空间失败                                      |
| `std::bad_cast`                     | 执行`dynamic_cast`失败                                       |
| `std::bad_typeid`                   | 对某个空指针`p`执行`typeid(*p) `                             |
| `std::bad_exception`                | 当某个函数`fun()`因在执行过程中抛出了异常声明所不允许的异常而调用`unexpected()`函数时，若`unexpected()`函数又一次抛出了`fun()`的异常声明所不允许的异常，且`fun()`的异常声明列表中有`bad_exception`,则会有一个`bad_exception`异常在`fun()`的调用点被抛出 |
| **`std::logic_error`**              | **理论上可以通过读取代码来检测到的异常。**                   |
| `std::domain_error`                 | 执行一段程序所需要的先决条件不满足                           |
| `std::invalid_argument`             | 表示向函数传入无效参数                                       |
| `std::length_error`                 | 尝试创建一个长度超过最大允许值的对象                         |
| `std::out_of_range`                 | 表示一个参数值不在允许的范围之内                             |
| `std::future_error`                 | (C++11起) 它为处理异步执行和共享状态（`std::future`、`std::promise`等）的线程库中的函数在失败时抛出。同 `std::system_error` ，此异常携带与`std::error_code`兼容的错误码。 |
| `std::bad_optional_access`          | (C++17起) 定义 `std::optional::value`在访问不含值的 `optional` 对象时所抛出的异常对象类型。 |
| **`std::runtime_error`**            | **理论上不可以通过读取代码来检测到的异常**                   |
| `std::overflow_error`               | 算术运算时向上溢出                                           |
| `std::range error`                  | 内部计算时发生作用域的错误                                   |
| `std::underflow_error`              | 算术运算时向下溢出                                           |
| `std::regex_error`                  | (C++11起) 定义抛出的异常对象类型，以报告正则表达式库中的错误。 |
| **`std::system_error`**             | (C++11起) `std::system_error` 是多种库函数（通常是与 OS 设施交接的函数，例如 `std::thread`的构造函数）在拥有关联于该异常的 `std::error_code`时抛出的异常类型，同时可能报告该`std::error_code `。 |
| `std::ios_base::failure`            | 用来表示C++的输入输出流执行过程中发生的错误。（C++17起，继承自`std::system_error`） |
| `std::filesystem::filesystem_error` | (C++17起)类 `std::filesystem::filesystem_error` 定义文件系统库中函数的抛出版重载所抛出的异常对象。 |

加粗的表示下方是其子类。

说明：还有相当多的异常类这里未全部列出，大都是C++11及C++11后的新标准定义的，这里不做再做说明，详细请查阅手册有关：标准库标头`<exception>`部分，上述表格已经能满足绝大部分使用场景。

## 标准异常类的使用示例

---

一些C++语法或某些功能在使用时也许会发生错误，这些语法或功能在其内部实现时，也许就会将这些错误作为异常抛出，

这些异常都属于标准异常`std::exception`或其子类，都可以用`std::exception`的引用来接收，从而处理异常。

详细见视频（讲解的很好）：[【C++教程 第十三章（2）异常Exception深入解剖】](https://www.bilibili.com/video/BV16T41167Zr?vd_source=03da7de0e80f9ff60fdeca7b512ba3f5)

示例：

```c++
#include <iostream>
#include <exception>
#include <vector>
using namespace std;

int main() 
{

    try 
    {
        vector<int> a(9999999999999999999);//指定vector容器一个很大很大的空间，在vector内部代码中这将会作为一个错误异常抛出
    }
    catch (exception& erro)//抛出的类都是exception类或其子类，使用父类引用接收（多态）
    {
        cerr << erro.what() << '\n';
    }
    system("pause>nul");
    return 0;
}
```

输出结果：

```
vector too long
```

## 自定义异常类继承标准异常类

---

可以通过继承和重载 `exception`类或其他标准异常类来定义新的异常。

下面的实例演示了如何使用`std::exception`类来实现自己的异常：

```c++
#include <iostream>
#include <exception>
#include <string>
using namespace std;
class MyException : public exception 
{
public:
    MyException(const string& message) : message_(message) {}

    virtual const char* what() const noexcept override //noexcept属于异常（接口）声明
    {
        return message_.c_str();
    }
private:
    std::string message_;
};

int main() 
{

    try 
    {
        throw MyException("!!!");
    }
    catch (exception& erro)
    {
        cerr << erro.what() << '\n';
    }

    system("pause>nul");
    return 0;
}
```

在这里，`what()` 是父异常类`std::exception`提供的一个公共方法，是一个虚函数，它已被所有子异常类重写，同样在自定义异常类中也需要重写，这也体现了C++多态的特性。

输出结果：

```shell
!!!
```

# 模板基础

## 模板和泛型编程的概念

---

泛型编程是一种编程模式，它核心的思想是增加代码的通用性和复用性，使代码能够适用于多种不同的数据类型。

传统的程序设计中，通常会写出多个函数或类来处理不同类型的数据。例如，在C语言中，为了实现针对不同类型的数组排序算法，需要为每一种数据类型编写相应的排序函数，这样会导致代码的冗余和重复。而泛型编程则可以使用单一的函数或类来实现通用的数据操作，避免了这种冗余和重复。

通过使用泛型编程，我们能够实现针对各种类型的数据，使用相同的代码进行处理。这种方式可以带来更高的代码复用性和可维护性，并可以避免出现多个函数或类的代码冗余的情况。

C++语言中的模板就是泛型编程的一种主要实现方式。使用C++模板，我们可以很方便地编写通用的函数或类来处理任意数据类型，极大地提高了代码的复用性、可维护性和可读性。

模板是C++中的一种高级编程特性，简单来说，模板就是一种让程序员编写具有参数类型或参数化表达式的函数和类的机制。利用模板，程序员可以充分利用C++的类型安全和可重用性。

C++中的模板可以分为函数模板和类模板两种。函数模板是将函数定义为泛型的，允许在不同数据类型下共享算法的代码。类模板则是将类定义为泛型的，允许在不同数据类型下共享类的代码实现。

模板的主要用途可以总结为以下几点：

1. 泛型编程：可以使用模板实现通用算法，可以很方便地处理不同类型的数据。

2. 可重用性：可以通过实例化不同类型的模板，实现数值计算、数据结构等算法的一般化处理，从而大大提高代码的可重用性。

3. 类型安全：使用模板的好处在于可以发现编译器在编译期间能够发现类型错误，从而提高程序的错误检测和安全性。

总之，模板是一种非常重要的C++编程特性，它可以使程序员高效地实现通用算法和数据结构，提高程序的可读性、可重用性和安全性。

## 函数模板

---

### 语法规则

---

函数模板是一种用于生成通用代码的功能。模板参数允许将函数的参数和返回类型作为模板的参数进行定义，这样可以将同样的代码用于不同的数据类型，从而减少代码冗余和提高代码的重用性。

函数模板的语法形式如下：

语法：“`template关键字`” + “`<typename T>`” 或 “`<class T>`” ，其中`T`是可自定义的名称，一般用大写字母，对于函数模板来说，`typename `和`class`没有区别。

```c++
template <typename T>//声明接下来将要写一个函数模板
//接下来的一个函数，将作为函数模板
//示例：
T max(T x, T y) 
{
  return (x > y) ? x : y;//返回较大者
}
```

对于上面的例子，使用函数模板时，可以在调用函数时将数据类型作为实参传递给模板参数：

```c++
int a = 5, b = 10;
double c = 3.14, d = 2.718;
int max_int = max<int>(a, b);
double max_double = max<double>(c, d);
```

在调用`max`函数时，使用了尖括号`<>`将数据类型作为实参传递给模板参数`T`，从而实例化了一个特定类型的函数。

在第一次调用`max`时，`T`被指定为`int`类型，在第二次调用`max`时，`T`被指定为`double`类型。这样就可以在不同的数据类型之间进行比较操作，从而提高代码的重用性和可读性。

同样的，也可以不指定`T`的类型，不指定类型时，将由编译器自动根据传入参数推导`T`的类型。

示例：

~~~c++
int a = 5, b = 10;
double c = 3.14, d = 2.718;
int max_int = max(a, b);
double max_double = max(c, d);
~~~

在以上示例中，我们没有显式地指定`T`类型，而是将不同类型的变量`a`和`b`、`c`和`d`传递给了`max`函数。编译器可以推导出`a`和`b`的类型是`int`，而`c`和`d`的类型是`double`，因此编译器会自动实例化一个`max`函数模板，用于比较`int`和`double`类型的数据并返回较大值。

==注意事项：==`T`的类型必须一致，否则会报错。

如下所示：

```c++
auto result = max(1, 2.5);
```

由于`1`和`2.5`的类型不同，编译器进行类型推导时，`T`的类型不一致，因此会报错。

建议在参数类型明确时，显示指定`T`的类型。

### 普通函数和函数模板的调用规则

---

函数模板和普通函数可以发生重载，函数模板间也可以发生重载，当普通函数和模板函数发生重载时，对于传入的参数如果都满足，在没有显示指定模板参数类型的情况下会优先调用普通函数。

示例：

```cpp
void foo(int x) 
{
    std::cout << "foo(int) called with x = " << x << std::endl;
}

template<typename T>
void foo(T x) 
{
    std::cout << "foo(T) called with x = " << x << std::endl;
}

int main() 
{
    foo(123); // 调用普通函数
    foo(3.14); // 调用函数模板
}
```

在此示例中，我们定义了一个名为`foo`的普通函数和一个同名的函数模板。当我们在`main`函数中调用`foo`函数时，编译器会优先选择普通函数而不是函数模板，因为普通函数的匹配级别更高。

通过显示指定模板参数类型或指定模板参数类型为空，可以强制调用函数模板。

示例：

```cpp
int x = 123;
foo(x); // 调用普通函数
foo<int>(x); // 调用函数模板
foo<>(x); // 调用函数模板
```

如果函数模板可以对参数产生更好的匹配，则优先调用函数模板。

示例：

~~~c++
void foo(int x) 
{
    std::cout << "foo(int) called with x = " << x << std::endl;
}

template<typename T>
void foo(T x) 
{
    std::cout << "foo(T) called with x = " << x << std::endl;
}
int main()
{
    char c = 'c';
    foo(c); // 调用函数模板
}
~~~

上述例子中调用普通函数时，需要进行隐式类型转换，而调用函数模板时不需要，则编译器优先调用函数模板。

==！==在实际开发中，不建议普通函数和函数模板重载，容易引起二义性。==！==

### 普通函数和函数模板的区别

---

普通函数可以自动进行隐式类型转换，而函数模板在不显示指定模板参数类型的情况下，不能进行隐式转换。只有在显示指定模板参数类型的情况下才能自动进行隐式类型转换。

示例：

```C++
int add01(int a, int b) 
{
    return a + b;
}

template<typename T>
T add02(T a, T b) 
{
    return a + b;
}
```

当我们调用普通函数`max`时，如果传入的参数不是`int`类型，系统会通过隐式类型转换将其转换为`int`类型：

```C++
int a = 3;
char b = 'c';
int c = add01(a, b); // 系统会自动将 char 类型的 b ，转换成对应的 int 类型的 ASCII码 
```

而对于函数模板`add02`，如果传入的参数不是同一类型，在不显示指定模板参数类型时，会报错：

```C++
int a = 3;
char b = 'c';
//int c = add02(a, b); // 编译器报错
```

当显示指定模板参数类型时，编译器则会自动进行隐式类型转换：

```C++
int a = 3;
char b = 'c';
int c = add02<int>(a, b); // 会进行隐式类型转换，将 b 转成对应的 ASCII码
```



==补充说明：==调用函数模板时，不显示指定模板类型的调用方式，称之为自动类型推导，所以调用函数模板由两种方式：自动类型推导和显示指定模板参数类型

## 类模板

---

### 语法规则

---

类模板允许用户创建一种通用的类，使得类中的某些数据成员或成员函数的参数、返回值可以取任意类型。

语法：“`template关键字`” + “`<class T1,class T2,...>`” ，其中`T`是可自定义的名称，一般用大写字母，"`...`"表示可以有多个自定义的模板参数。

```c++
template<class T1, class T2,...>   
class class_name
{
    //成员变量、函数
};
```

类模板示例：

```c++
template<class T1, class T2>
class Person
{
public:
	Person(T1 name, T2 age)
	{
		this->_name = name;
		this->_age = age;
	}
public:
	T1 _name;
	T2 _age;
};

void test01()
{
	Person<string, int> p1("张三", 20);//指定成员的类型为string和int
	cout << "姓名：" << p1._name << "  年龄：" << p1._age << endl;
}
int main()
{
	test01();
	system("pause>nul");
}
```

输出结果：

```c++
姓名：张三  年龄：20
```

### 类模板和函数模板的区别

---

- 类模板没有自动类型推导的使用方式

  示例：

  ```c++
  template<class T1, class T2>
  class Person
  {
  public:
  	Person(T1 name, T2 age)
  	{
  		this->_name = name;
  		this->_age = age;
  	}
  public:
  	T1 _name;
  	T2 _age;
  };
  
  void test01()
  {
  	Person<string, int> p1("张三", 20);//指定模板参数类型为string和int
      //Person p1("张三", 20);//错误，类模板无法使用自动类型推导
  	cout << "姓名：" << p1._name << "  年龄：" << p1._age << endl;
  }
  int main()
  {
  	test01();
  	system("pause>nul");
  }
  ```

- 类模板在模板参数列表中可以有默认参数

  示例：

  ```c++
  template<class T1, class T2 = int>//指定T2有默认的类型为int
  class Person
  {
  public:
  	Person(T1 name, T2 age)
  	{
  		this->_name = name;
  		this->_age = age;
  	}
  public:
  	T1 _name;
  	T2 _age;
  };
  
  void test01()
  {
  	Person<string> p1("张三", 20);//指定第一个模板参数类型为string，第二个可以不指定，因为模板参数中第二个有默认参数int
  	cout << "姓名：" << p1._name << "  年龄：" << p1._age << endl;
  }
  int main()
  {
  	test01();
  	system("pause>nul");
  }
  ```


### 类模板中成员函数的创建时机

---

类模板中成员函数和普通类中成员函数创建时机是有区别的：

- 普通类中的成员函数—开始就可以创建
- 类模板中的成员函数在调用时才创建

示例：

```c++
class MyClass1
{
public:
	void fun1() 
	{
		cout << "MyClass1的fun1的调用" << endl;
	};
};
class MyClass2
{
public:
	void fun2()
	{
		cout << "MyClass2的fun2的调用" << endl;
	};
};
template<class T1>
class Person
{
public:
    T1 obj;
    
	void fun1()
	{
		obj.fun1();//编译不会报错，但调用时如果T1不是MyClass1类型就会报错
	}

	void fun2()
	{
		obj.fun2();//编译不会报错，但调用时如果T1不是MyClass2类型就会报错
	}
};
//上述两个注释说明，类模板的成员函数是在调用时才创建的

void test01()
{
	//Person<int> p1;//错误
	//p1.fun1();
    
    Person<MyClass1> p1;
	p1.fun1();//显示：MyClass1的fun1的调用
	//p1.fun2();错误，MyClass1没有fun2()成员
    
    Person<MyClass2> p2;
	p2.fun2();//显示：MyClass2的fun2的调用
	//p2.fun1();错误，MyClass2没有fun1()成员
}
int main()
{
    test01();
}
```

输出结果：

```
MyClass1的fun1的调用
MyClass2的fun2的调用
```

### 类模板对象做函数参数

---

类模板实例化出来的对象像函数传参有三种传入方式：

- 指定传入的类型：直接显示对象的数据类型

  ```c++
  template<class T1,class T2>
  class Person
  {
  public:
  	Person(T1 name, T2 age) :name(name), age(age)
  	{}
  	void show()
  	{
  		cout << "姓名：" << this->name << "  年龄：" << this->age << endl;
  	}
  	T1 name;
  	T2 age;
  };
  //指定传入类型
  void printpPerson1(Person<string, int>& p)
  {
  	p.show();
  }
  
  void test01()
  {
  	Person<string, int>p1("张三", 20);
      printpPerson1(p1);
  }
  
  int main()
  {
  	test01();
  	system("pause>nul");
  }
  
  
  ```

  

- 参数模板化：将对象中的参数变为模板进行传递

  ```c++
  template<class T1,class T2>
  class Person
  {
  public:
  	Person(T1 name, T2 age) :name(name), age(age)
  	{}
  	void show()
  	{
  		cout << "姓名：" << this->name << "  年龄：" << this->age << endl;
  	}
  	T1 name;
  	T2 age;
  };
  
  //参数模板化
  template<class T1, class T2>
  void printPerson2(Person<T1, T2>& p)
  {
  	p.show();
  }
  
  void test01()
  {
  	Person<string, int>p1("张三", 20);
      printpPerson2(p1);
  }
  
  int main()
  {
  	test01();
  	system("pause>nul");
  }
  
  ```

  

- 整个类模板化：将这个对象类型模板化进行传递

  ```c++
  template<class T1,class T2>
  class Person
  {
  public:
  	Person(T1 name, T2 age) :name(name), age(age)
  	{}
  	void show()
  	{
  		cout << "姓名：" << this->name << "  年龄：" << this->age << endl;
  	}
  	T1 name;
  	T2 age;
  };
  
  //整个类模板化
  template<class T>
  void printPerson3(T& p)
  {
  	p.show();
  }
  
  void test01()
  {
  	Person<string, int>p1("张三", 20);
      printpPerson3(p1);
  }
  
  int main()
  {
  	test01();
  	system("pause>nul");
  }
  ```


### 类模板与继承

---

- 当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中“`T`”的类型，如果不指定。编译器无法给子类分配内存

  ```c++
  template<class T>
  class father
  {
  public:
  	T m;
  };
  
  //class son :public father //错误，必须要知道父类中的T类型，才能继承给子类
  class son :public father<int>
  {
      
  };
  ```

- 如果想灵活指定出父类中“`T`”的类型，子类也需变为类模板

  ```c++
  template<class T>
  class father
  {
  public:
  	T m;
  };
  
  template<class T1,class T2>
  class son :public father<T2>//T1指定成子类自己的类型，T2指定成父类的类型
  {
  public:
  	T1 obj;
  };
  
  void test01()
  {
  	son<int, string> s1;
  	s1.m = "hello";
  	s1.obj = 10;
  
  	cout << s1.m << endl;
  	cout << s1.obj << endl;
  }
  
  int main()
  {
  	test01();
  	system("pause>nul");
  }
  ```

### 类模板成员函数的类外实现

---

代码示例：

```c++
template<class T1,class T2>
class Person
{
public:
	Person(T1 name, T2 age) :name(name), age(age);

	void show();

	T1 name;
	T2 age;
};

template<class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
}

template<class T1, class T2>
void Person<T1, T2>::show()
{
	cout << "姓名：" << this->name << "  年龄：" << this->age << endl;
}
```

### 类模板的分文件编写

---

普通类的分文件编写是在`.h`中写声明，`.cpp`中写定义，对于类模板如果采用这种写法则会报错。类模板中成员函数创建时机是在调用阶段，如果采用分普通的分文件方式编写，即在`.h`文件中写声明，在`.cpp`文件中写定义，会导致`.cpp`中的定义链接不到。

报错原因：

- 采用普通分文件编写时，首先包含了`.h`头文件，编译器知道了类模板的存在，但是类模板中的成员函数在调用时才会创建，所以此时编译器不会去“寻找”成员函数的定义，之后去调用时，因为没有包含`.cpp`文件`.h`文件中也没有包含`.cpp`文件，因此编译器无法链接到类模板中的成员函数。

解决方案：

- 直接包含`.cpp`源文件。示例（假设有一个Person的类模板，在`.h`中声明，在`.cpp`中定义）：把`#include "Person.h"`变为`#include "Person.cpp"`。
- 将声明`.h`文件和实现`.cpp`文件写到同一个文件中，并更改后缀名为`.hpp`。`hpp`是约定俗成的名称，并不是强制的。
- 采用传统分文件方式编写，在`.h`文件最后包含上`.cpp`文件，同时使用`#pragma once`防止头文件重复包含。在主函数文件中包含`.h`文件即可。

### 类模板与友元

---

在类模板中编写友元函数或友元类时，需要注意以下几点：

- 友元函数或友元类的声明位置：友元函数或友元类的声明应该放在类模板内部，并在需要访问私有或保护成员的地方进行声明。通常，在类模板的定义之前声明友元函数或友元类，以便让编译器知道这些函数或类是模板类的友元。
- 模板参数的传递：如果友元函数或友元类也是一个模板，并且它的模板参数与包含它的类模板的模板参数不同，需要显式传递模板参数。这可以通过将类模板的模板参数列表添加到友元函数或友元类的声明中来实现。
- 定义位置的选择：友元函数或友元类的定义可以放在类模板的内部或外部。如果将定义放在类模板的内部，需要注意它们是每个实例化的模板类的独立定义，而不是共享的。如果将定义放在类模板的外部，通常需要在定义之前使用`template`关键字以指明它是一个类模板的友元。

友元函数：

- 类内声明和定义：直接在类内声明友元并定义即可

  代码示例：

  ```c++
  #include <iostream>
  template<class T1, class T2>
  class Person
  {
  	friend void show(Person<T1, T2>p)
  	{
  		std::cout << "姓名：" << p.name << "  年龄：" << p.age << std::endl;
  	}
  public:
  	Person(T1 name, T2 age)
  	{
  		this->name = name;
  		this->age = age;
  	};
  	T1 name;
  	T2 age;
  };
  
  int main()
  {
      Person<std::string, int>p1("张三",20);
  	show(p1);
  }
  ```

  输出结果：

  ```
  姓名：张三  年龄：20
  ```

- 类内声明类外定义：需要提前让编译器知道友元函数的存在

  代码示例：

  ```c++
  #include <iostream>
  template<class T1, class T2>
  class Person
  {
      //友元函数的声明
      template<class t3, class t4>
      friend void show(Person<t3, t4>p);
  
  public:
      Person(T1 name, T2 age)
      {
          this->name = name;
          this->age = age;
      };
      T1 name;
      T2 age;
  };
  
  //友元函数的定义
  template<class t3, class t4>
  void show(Person<t3, t4>p)
  {
      std::cout << "姓名：" << p.name << "  年龄：" << p.age << std::endl;
  }
  
  int main()
  {
      Person<std::string, int>p1("张三",20);
  	show(p1);  
  }
  ```

友元类：

代码示例：

```c++
template <class T>
class TemplateClass 
{
public:
    TemplateClass(T data)
    {
        this->m_date = date;
    }
    
    // 友元类的声明
    template <class U>
    friend class FriendClass;
    
private:
    T m_data;
};

// 友元类的定义
template <class T>
class FriendClass {
public:
    FriendClass(const TemplateClass<T>& obj)
    {
        std::cout << "Friend Class: " << obj.m_data << std::endl;
    }
};
```

友元函数或友元类的声明应该放在类模板内部，并在需要访问私有或保护成员的地方进行声明。通常，在类模板的定义之前声明友元函数或友元类，以便让编译器知道这些函数或类是模板类的友元。

### 关于`typename`和`class`

---

在C++模板中，`typename`和`class`关键字用于声明模板参数，它们在大多数情况下是可以互换使用的，没有本质的区别。

然而，它们在某些情况下具有一些细微的区别：

- 模板参数的默认关键字：当定义模板参数时，`class`可以使用默认关键字`class`或`typename`。

  例如：`template <class T>` 或 `template <typename T>`。这两者是等效的，可以互换使用。

- 嵌套依赖名称：在模板中使用嵌套依赖名称时，必须使用`typename`关键字。

  例如，当在类模板的成员函数中使用依赖于模板参数的类型时，需要使用`typename`关键字来指示该名称是一个类型。例如：`typename T::value_type`。

- 模板参数作为模板参数：当模板参数本身是一个模板时，必须使用`class`关键字。

  例如，当模板参数是一个模板类时，使用`class`关键字来声明它，如：`template <class Container>`。

`typename`和`class`在大多数情况下可以互换使用，没有本质的区别。在某些特定的情况下，使用`typename`关键字是必要的，例如处理嵌套依赖名称时。

一般来说，根据个人偏好或项目风格指南选择使用`typename`还是`class`。

代码示例：

```c++
#include <iostream>

template <typename T>
class MyContainer 
{
public:
    typedef T value_type;
};

template <typename Container>
void printValueType(Container container) 
{
    // 错误示例：尝试使用未指定类型的依赖名称
    // 此处必须使用 typename 关键字
    // std::cout << Container::value_type << std::endl;  // 编译错误

    // 正确示例：使用 typename 关键字指示依赖名称是类型
    typename Container::value_type value;
    std::cout << typeid(value).name() << std::endl;
}

int main() 
{
    MyContainer<int> container;
    printValueType(container);

    return 0;
}
```

在上述示例中，我们定义了一个模板类 `MyContainer`，其中包含一个内部类型别名 `value_type`。

然后，我们定义了一个模板函数 `printValueType`，该函数接受一个模板参数 `Container`，并尝试访问 `Container` 类型的 `value_type`。

在错误示例中，我们未使用 `typename` 关键字，编译器会报错，因为它无法确定 `Container::value_type` 是一个类型还是一个成员变量。

而在正确示例中，我们使用 `typename` 关键字来明确告诉编译器 `Container::value_type` 是一个类型。

总结：

- 在涉及到嵌套依赖名称时，必须使用 `typename` 关键字来指示该名称是一个类型。
- 在模板参数本身是一个模板时，必须使用 `class` 关键字来声明它，例如 `template <class Container>`。

# STL部分

## ==说明==

本章的编写根据C++98标准，对于新标准的内容只是略有涉及，部章的部分内容在新的标准中也许是不正确的。

本章的大部分内容只编写了常见、常用的内容，对于不常用、不常见的用法或新标准中新增的、更改的内容详细请自行参阅手册。

截止到C++20标准，`STL`（标准模板库）提供了以下容器：

1. `std::array`: 固定大小的数组容器。
2. `std::vector`: 动态数组，可根据需要自动调整大小。
3. `std::deque`: 双端队列，允许在两端高效地添加和删除元素。
4. `std::list`: 双向链表。
5. `std::forward_list`: 单向链表。
6. `std::set`: 按升序排序的唯一元素集合。
7. `std::multiset`: 按升序排序的允许重复元素的集合。
8. `std::map`: 键-值对的有序映射，按键的升序排序。
9. `std::multimap`: 键-值对的有序映射，允许重复的键。
10. `std::unordered_set`: 哈希集合，不保证元素顺序。
11. `std::unordered_multiset`: 哈希集合，允许重复元素，不保证元素顺序。
12. `std::unordered_map`: 键-值对的哈希映射，不保证元素顺序。
13. `std::unordered_multimap`: 键-值对的哈希映射，允许重复的键，不保证元素顺序。
14. `std::stack`: 栈，后进先出（LIFO）的数据结构适配器。
15. `std::queue`: 队列，先进先出（FIFO）的数据结构适配器。
16. `std::priority_queue`: 优先队列，根据优先级进行排序的数据结构适配器。

这些容器提供了不同的功能和性能特点，可以根据具体的需求选择合适的容器。

以下是C++11标准引入的新容器：

1. `std::array`: 固定大小的数组容器。
2. `std::unordered_set`: 哈希集合，不保证元素顺序。
3. `std::unordered_multiset`: 哈希集合，允许重复元素，不保证元素顺序。
4. `std::unordered_map`: 键-值对的哈希映射，不保证元素顺序。
5. `std::unordered_multimap`: 键-值对的哈希映射，允许重复的键，不保证元素顺序。

以下是C++17标准引入的新容器：

1. `std::optional`: 可选值容器，可以表示一个可能存在或不存在的值。
2. `std::variant`: 可变类型容器，可以容纳多个可能的类型中的一个值。
3. `std::any`: 任意类型容器，可以容纳任意类型的值。
4. `std::string_view`: 字符串视图，用于非拥有权的字符串操作。

从C++20开始，没有引入新的容器类型。

## `string`容器

---

### 构造函数

---

```c++
string();							//创建一个空的字符串例如: string str;
string(const char* s);				//使用C风格字符串s初始化
string(const string& str);			//使用一个string对象初始化另一个string对象
string(int n，char c);              //使用n个字符c初始化
```

### 赋值

---

```c++
string& operator=(const char* s);			//char*类型字符串赋值给当前的字符串
string& operator=(const string &s);			//把字符串s赋给当前的字符串
string& operator=(char c);					//字符赋值给当前的字符串
string& assign(const char *s);				//把字符串s赋给当前的字符串
string& assign(const char *s, int n);		//把字符串s的前n个字符赋给当前的字符串
string& assign(const string &s) ;			//把字符串s赋给当前字符串
string& assign(int n，char c);              //用n个字符c赋给当前字符串
```

### 拼接

---

```c++
string& operator+=( const char* str);               //重载+=操作符
string& operator+=( const char c);                  //重载+=操作符
string& operator+=( const string& str);             //重载+=操作符
string& append(const char *s ) ;                    //把字符串s连接到当前字符串结尾
string& append( const char *s, int n);              //把字符串s的前n个字符连接到当前字符串结尾
string& append(const string &s ) ;                  //同operator+=(const string& str)
string& append(const string &s，int pos,int n);     //字符串s中从pos开始的n个字符连接到字符串结尾
void push_back (char c);						//它将字符 c 附加到字符串的末尾，将其长度增加一
```

### 查找、替换

---

```c++
int find(const string& str, int pos = 0) const;         //查找str第一次出现位置,从pos开始查找
int find(const char* s, int pos - e) const;             //查找s第一次出现位置,从pos开始查找
int find(const char* s , int pos， int n) const;        //从pos位置查找s的前n个字符第一次位置
int find(const char c, int pos = e) const;              //查找字符c第一次出现位置
int rfind(const string& str, int pos = npos) const;     //查找str最后一次位置,从pos开始查找
int rfind(const char* s, int pos = npos) const;         //查找s最后一次出现位置,从pos开始查找
int rfind(const char* s, int pos， int n) const;        //从pos查找s的前n个字符最后一次位置
int rfind(const char c, int pos = e) const;             //查找字符c最后一次出现位置

string& replace (size_t pos, size_t len, const string& str); 					//替换从pos开始len个字符为字符串str  
string& replace (size_t pos, size_t len, const char* s);   						//替换从pos开始的len个字符为C风格字符串s
string& replace(size_t pos, size_t len, const char* s, size_t n);  				//用s的前n个字符替换从pos开始长度为len的子串
string& replace (size_t pos, size_t len, size_t n, char c); 					//用n个c字符替换从pos开始长度为len的子串
string& replace (size_t pos, size_t len, const string& str, size_t subpos, size_t sublen);
//用str字符串[subpos,sublen)内的字串替换[pos,len)内的字符

string& replace (const_iterator i1, const_iterator i2, const string& str);		//用str替换迭代器起始位置和结束位置的字符 
string& replace (const_iterator i1, const_iterator i2, const char* s); 			//用C风格字符串s替换迭代器起始位置和结束位置的字符 
string& replace (const_iterator i1, const_iterator i2, const char* s, size_t n); //用s的前n个字符替换指定迭代器位置(从i1到i2)的字符串
string& replace (const_iterator i1, const_iterator i2, size_t n, char c); 		//n个c字符替换从指定迭代器位置(从i1到i2)的字符串

void swap (string& str);	//交换两个字符串的内容
```

### 比较

---

比较方式：字符串比较是按字符的ASCII码进行对比

相等：返回0

前者大于后者：返回1

前者小于后者：返回-1

```c++
int compare(const string &s) const;		//与C++风格字符串s比较
int compare(const char *s ) const;		//与C风格字符串s比较
```

### 获取单个字符

---

`C++11`声明：

```c++
const char& operator[] (size_t pos) const;	//通过[]类似数组下标方式取字符
const char& at (size_t pos) const;			//通过at方法获取第pos个字符
const char& back() const;					//返回对字符串最后一个字符的引用
const char& front() const;					//返回对字符串第一个字符的引用
```

### 插入和删除

---

```c++
string& insert(int pos, const char* s);				//插入字符串
string& insert(int pos, const string& str);			//插入字符串
string& insert(int pos, int n,char c);				//在指定位置插入n个字符c	
```

`C++11`声明：

```c++
string& erase (size_t pos = 0, size_t len = npos);	//删除从pos开始的len个字符
string& erase(const size_t Off = 0);				//删除下标从Off开始直到字符串结尾的元素
iterator erase (iterator position);					//删除迭代器指向的元素，返回值是指向删除元素的下一个元素的迭代器
iterator erase (iterator first, iterator last);		//删除迭代器指定范围[first, last)内的字符串，返回值是指向被删除子串的下一个元素的迭代器
void clear() noexcept;								//擦除字符串的内容，使之变成一个空字符串
void pop_back();									//擦除字符串的最后一个字符，从而有效地将其长度减少一个
```

### 获取子串

---

```c++
string substr (size_t pos = 0, size_t len = npos) const;	//返回由pos开始的n个字符组成的字符串
```

### 长度和容量

---

```c++
size_t size() const noexcept;		//以字节为单位返回字符串的长度，英文返回值等于字符数量，中文翻倍
size_t length() const noexcept;		//和size()作用相同，没有区别
size_t max_size() const noexcept;	//返回字符串可以达到的最大长度
void resize (size_t n, char c);		//将字符串的大小调整为n个字符的长度,可选：如果n大于现有长度，用字符c填充到新的空间
size_t capacity() const noexcept;	//返回当前为字符串分配的存储空间的大小，以字节表示
void reserve (size_t n = 0);		//改变容量，预留n个字节的空间，减少拷贝、复制等操作时的运行时间
void shrink_to_fit();				//使字符串减小其分配容量以适应字符内容的大小
```

### 迭代器

---

待整理：

[C++ 标准库 -  (w3schools.cn)](https://www.w3schools.cn/cpp_standard_library/string.html)

### 其他

---

```c++
const char* c_str() const noexcept;							//用于获得等效的 C风格字符串
const char* data() const noexcept;							//C++11后与c_str等效，没有区别
size_t copy (char* s, size_t len, size_t pos = 0) const;	  //在string对象中从第pos个位置开始，取出len个字符存放到char数组s中
bool empty() const noexcept;								//返回字符串是否为空（即其长度是否为 0）
```

## `vector`容器

---

### 构造函数

---

```c++
vector<T> v;						//采用模板实现类实现，默认构造函数
vector(v.begin() , v.end() ) ;		 //将v[begin(), end())区间中的元素拷贝给本身
vector(n,elem);					    //构造函数将n个elem拷贝给本身
vector( const vector &vek ) ;		//拷贝构造函数。
```

### 赋值

---

```c++
vector& operator=( const vector &vec);//重载等号操作符
assign( beg, end) ;//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n,elem);//将n个elem拷贝赋值给本身。
```

### 容量和大小

---

```c++
empty( ) ;//判断容器是否为空
capacity();//容器的容量
size();//返回容器中元素的个数
resize(int num ) ;//重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
				//如果容器变短，则末尾超出容器长度的元素被删除。
resize(int num，elem);//重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
					//如果容器变短，则末尾超出容器长度的元素被删除
```

###  插入和删除

---

```c++
push_back(ele);//尾部插入元素ele
pop_back();//删除最后一个元素
insert(const_iterator pos, ele) ;//迭代器指向位置pos插入元素ele
insert(const_iterator pos, int count,ele);//迭代器指向位置pos插入count个元素ele
erase( const_iterator pos ) ;//删除迭代器指向的元素
erase(const_iterator start，const_iterator end);//删除迭代器从start到end之间的元素
clear() ;//删除容器中所有元素
```

### 存、取

---

```c++
at(int idx ) ;//返回索引idx所指的数据
operator[];//返回索引idx所指的数据
front( );//返回容器中第一个数据元素
back();//返回容器中最后一个数据元素
```

### 交换

---

```c++
swap(vec);//将vec与本身的元素互换
```

### 预留空间

---

```c++
reserve(int len);//容器预留len个元素长度，预留位置不初始化，元素不可访问。
```

## `deque`容器

---

`deque`容器是双端数组，可以对头和尾进行插入和删除。

与`vector`的区别：

- `vector`对于头部的插入删除效率低，数据量越大，效率越低
- `deque`相对而言，对头部的插入删除速度回比`vector`快
- `vector`访问元素时的速度会比`deque`快,这和两者内部实现有关

### 构造函数

---

```c++
deque<T> deqT;				//默认构造形式
deque(beg, end) ;			//构造函数将[beg, end)区间中的元素拷贝给本身。
deque(n,elem);				//构造函数将n个elem拷贝给本身。
deque(const deque &deq); 	//拷贝构造函数
```

### 赋值

---

```c++
deque& operator=(const deque &deq);			//重载等号操作符
assign(beg, end) ;							//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n,elem ) ;							//将n个elem拷贝赋值给本身。
```

### 容器大小

---

```c++
deque.empty();				//判断容器是否为空
deque.size();				//返回容器中元素的个数
deque.resize(num);			//重新指定容器的长度为num,若容器变长，则以默认值填充新位置。
							//如果容器变短，则末尾超出容器长度的元素被删除。
deque.resize(num，elem) ;	//重新指定容器的长度为num,若容器变长，则以elem值填充新位置。
							//如果容器变短，则末尾超出容器长度的元素被删除。
```

### 插入和删除

---

```c++
push_back(elem) ;			//在容器尾部添加一个数据
push_front(elem) ;			//在容器头部插入一个数据
pop_back() ;				//删除容器最后一个数据
pop_front();				//删除容器第一个数据
insert(pos,elem);			//在pos位置插入一个elem元素的拷贝，返回新数据的位置。
insert(pos,n,elem);			//在pos位置插入n个elem数据，无返回值。
insert( pos,beg,end);		//在pos位置插入[beg,end)区间的数据，无返回值。
clear();					//清空容器的所有数据
erase(beg,end);				//删除[beg,end)区间的数据，返回下一个数据的位置。
erase(pos) ;				//删除pos位置的数据，返回下一个数据的位置。
```

### 存、取

---

```c++
at(int idx);		//返回索引idx所指的数据
operator[];			//返回索引idx所指的数据
front();			//返回容器中第一个数据元素
back();				//返回容器中最后一个数据元素
```

### 排序

---

示例用法，之后会详细讲：

默认从大到小排序：

需要包含头文件`#include <algorithm>`

```c++
sort(iterator beg, iterator end);	//对beg和end区间内元素进行排序
```

## `stack` 容器

---

### 基本概念

---

`stack`是一种先进后出(First In Last Out,FILO)，后进先出（LIFO）的容器，它的数据结构是栈，只有一个出口，只有栈顶元素才可以被访问，因此`stack`容器不允许被遍历。

向栈中插入数据叫入栈或压栈，删除栈中数据叫出栈或弹栈。

![](https://gd-hbimg.huaban.com/8c1c874271d1e5c3649251f076bb2978aeefc8ce42c2-ZHcmVA)

### 构造函数

---

```c++
stack<T> stk;					//stack采用模板类实现， stack对象的默认构造形式
stack(const stack &stk);		//拷贝构造函数
```

### 赋值

---

```c++
stack& operator=( const stack &stk );//重载等号操作符
```

### 存、取

---

```c++
push(elem) ;	//向栈顶添加元素
pop();			//从栈顶移除第一个元素
top( );			//返回栈顶元素
```

### 容器大小

---

```c++
empty();//判断堆栈是否为空
size();//返回栈的大小
```

## `queue`容器

---

### 基本概念

---

`queue`是一种先进先出(First ln First Out,FIFO)的容器，其数据结构是队列，它有两个出口。

![](https://gd-hbimg.huaban.com/d02191ef7703f72efc7df591fb8587d700e2862ea867-pVoRZp)



- 队列容器只允许从一端新增元素，从另一端移除元素。

- 队列中只有队头和队尾才可以被外界使用，因此队列不允许有遍历行为。

队列中进数据称为：入队

队列中出数据称为：出队

### 构造函数

---

```c++
queue<T> que;					//queue采用模板类实现，queue对象的默认构造形式
queue(const queue &que);		//拷贝构造函数
```

### 赋值

---

```c++
queue& operator=( const queue &que);	//重载等号操作符
```

### 存、取

---

```c++
push(elem) ;	//往队尾添加元素
pop();			//从队头移除第一个元素
back();			//返回最后一个元素
front();		//返回第一个元素
```

### 容器大小

---

```c++
empty();	//判断堆栈是否为空
size();		//返回栈的大小
```

## `list`容器

---

### 基本概念

---

`list`容器是一种物理存储单元上非连续的存储结构，数据元素的逻辑顺序是通过链表中的指针链接实现的。其数据结构是双向循环链表。

链表的组成：链表由—系列结点组成。

单链表结点的组成：一个是存储数据元素的数据域，另一个是存储下一个结点地址的指针域。

双向循环链表：其结点指针域有两个指针，分别记录上一个结点和下一个结点的地址。头结点指针域的上一个结点为尾结点，尾结点的下一个指针域为头结点，以此形成循环。

![](https://gd-hbimg.huaban.com/b6b4b891d33f1aa861bdd6ad528a5544c6622faca1d5-NTIgD6_fw1200webp)



由于链表的存储方式并不是连续的内存空间，因此`list`容器中的迭代器只支持前移和后移，属于双向迭代器。

`list`的优点：

- 采用动态存储分配，不会造成内存浪费和溢出。
- 链表执行插入和删除操作十分方便，修改指针即可，不需要移动大量元素。

list的缺点：

- 链表灵活，但是空间(指针域)和时间(遍历）额外耗费较大
- `list`有一个重要的性质，插入操作和删除（非迭代器指向的元素）操作都不会造成原有`list`迭代器的失效，这在vector是不成立的。

### 构造函数

---

```c++
list<T> lst;				//list采用采用模板类实现,对象的默认构造形式:
list(beg,end) ;				//构造函数将[beg, end)区间中的元素拷贝给本身。
list(n,elem);				//构造函数将n个elem拷贝给本身。
list(const list &lst);		//拷贝构造函数。
```

### 赋值和交换

---

```c++
assign(beg, end) ;					//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n,elem);						//将n个elem拷贝赋值给本身。
list& operator=(const list &lst);	 //重载等号操作符
swap(lst);						   //将lst与本身的元素互换。
```

### 容器大小

---

```c++
size();		//返回容器中元素的个数
empty();	//判断容器是否为空

resize(num) ;		  //重新指定容器的长度为num，若容器变长，则以默认值填充新位置。
					//如果容器变短，则末尾超出容器长度的元素被删除。

resize(num,elem);	  //重新指定容器的长度为num，若容器变长，则以elem值填充新位置。
					//如果容器变短，则末尾超出容器长度的元素被删除。
```

### 插入和删除

---

```c++
push_back(elem);		//在容器尾部加入一个元素
pop_back();				//删除容器中最后一个元素
push_front(elem);		//在容器开头插入一个元素
pop_front();			//从容器开头移除第一个元素

insert(pos,elem);		//在pos位置插elem元素的拷贝，返回新数据的位置。
insert(pos,n,elem);		//在pos位置插入n个elem数据，无返回值。
insert(pos,beg,end);	//在pos位置插入[beg,end)区间的数据，无返回值。

clear();			//移除容器的所有数据
erase(beg,end);		//删除[beg,end)区间的数据，返回下一个数据的位置。
erase(pos);			//删除pos位置的数据，返回下一个数据的位置。
remove(elem);		//删除容器中所有与elem值匹配的元素。
```

### 存、取

---

```c++
front();	//返回第一个元素。
back( );	//返回最后一个元素。
```

### 反转和排序

---

将容器中的元素反转，以及将容器中的数据进行排序。

==所有不支持随机访问迭代器的容器，不可以用标准算法==。

不支持随机访问迭代器的容器，内部会提供对应一些算法。

```c++
reverse(;	//反转链表
sort();		//链表排序，该函数是成员函数
```

## `pair`对组

---

对组指：成对出现的数据。利用对组可以使函数返回两个数据，对组嵌套对组时，可使函数返回多个数据。

### 创建

---

```c++
pair<type，type> p (value1, value2);
pair<type, type> p = make_pair(value1, value2);
```

### 数据获取

---

```c++
p.first; 	//获取pair对象p的第一个数据
p.second; 	//获取pair对象p的第二个数据  
```

## `set`容器和`multiset`容器

---

### 基本概念

---

所有元素都会在插入时自动被排序。

`set`和`multiset`属于关联式容器，底层结构是用二叉树实现。

`set`和`multiset`区别：

- `set`不允许容器中有重复的元素 
- `multiset`允许容器中有重复的元素

### 构造函数

---

```c++
set<T> st;				//默认构造函数:
set(const set &st) ;	//拷贝构造函数
```

### 赋值

---

```c++
set& operator=(const set &st);//重载等号操作符
```

### 插入和删除

---

```c++
insert(elem) ;		//在容器中插入元素。
clear();			//清除所有元素
erase(pos);			//删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg，end);		//删除区间[beg,end)的所有元素，返回下一个元素的迭代器。
erase(elem);		//删除容器中值为elem的元素。
```

对于`set`容器，因为不允许插入相同数据，因此插入函数返回值是一个`pair<iterator,bool>`的数据类型，可用于判断是否插入成功。

示例代码：

```c++
set<int> s;
pair<set<int> : :iterator，bool>ret = s.insert(10);if (ret.second) 
{
	cout <<"插入成功!"<<endl;
}
else 
{
	cout <<"插入失败!”<<endl;
}
```

### 容器大小

---

```c++
size( ) ;//返回容器中元素的数目
empty();//判断容器是否为空
```

### 交换

---

```c++
swap(st);//交换两个集合容器
```

### 查找

---

```c++
find(key) ;		//查找key是否存在,若存在，返回该键的元素的迭代器;若不存在，返回set.end(;
count(key);		//统计key的元素个数
```

### 自定义排序规则

---

- 方式1：

  定义一个类，重载`operator()`运算符，定义比较函数，将类名作为`set`容器的第二个类型。同时，这也是传统写法。

  示例：

  ```c++
  class MyCompare
  {
  public:
  	bool operator()(int a, int b) const//新C++标准必须添加const，旧标准可不添加
  	{
  		return a > b;
  	}
  };
  
  void test() 
  {
  	set<int, MyCompare> S1;
  	S1.insert(98);
  	S1.insert(52);
  	S1.insert(25);
  	S1.insert(74);
  	S1.insert(82);
  	S1.insert(78);
  	for (auto& i : S1) 
  	{
  		cout << i << endl;
  	}
  }
  ```

- 方式2：

  定义一个`lambda`表达式，并使用`decltype`获取类型，或者配合`std::function`及`reinterpret_cast`使用，作为`set`容器的第二个类型。

  示例：

  ```c++
  void test() 
  {
  	auto f = [](int a, int b) ->bool {return a > b; };
  	set<int, decltype(f)> S2(f);
  	S2.insert(98);
  	S2.insert(52);
  	S2.insert(25);
  	S2.insert(74);
  	S2.insert(82);
  	S2.insert(78);
  
  	for (auto& i : S2) 
  	{
  		cout << i << endl;
  	}
  }
  ```

- 方式3：

  可以直接定义一个函数，通过转换将函数指针转换为一个类指针，再解引用，作为`set`容器的第二个类型。

  示例：

  ```c++
  bool myCompare(int a, int b) 
  {
      return a > b;
  }
  
  void test() 
  {
      auto f = myCompare;
      using FuncPtr = bool(*)(int, int);
      set<int, std::function<bool(int, int)>> S(reinterpret_cast<FuncPtr&>(f));//需要包含头文件#include <functional>
      S.insert(98); 
      S.insert(52);
      S.insert(25);
      S.insert(74);
      S.insert(82);
      S.insert(78);
      for (auto& i : S) 
      {
          cout << i << endl;
      }
  }
  ```

  这段代码定义了一个函数`myCompare`，它接受两个`int`类型的参数`a`和`b`，并返回一个`bool`类型的值。函数的作用是比较`a`和`b`的大小，如果`a`大于`b`，则返回`true`，否则返回`false`。

  接下来，代码定义了一个变量`f`，它的类型是`myCompare`函数的指针。然后，使用`using`关键字定义了一个别名`FuncPtr`，它表示一个指向`bool`类型函数的指针，该函数接受两个`int`类型的参数。

  最后，代码定义了一个`set`容器`S`，它的元素类型是`int`，比较函数类型是`std::function<bool(int, int)>`。

  在构造`set`对象时，使用`reinterpret_cast`将`f`的类型转换为`FuncPtr&`类型，并将其作为比较函数传递给`set`对象。这样，`set`容器就可以使用`myCompare`函数来比较元素的大小了。

这三段代码的输出结果是一样的，都是按降序输出`set`容器中的元素。

输出结果：

```
98
82
78
74
52
25
```

## `map`容器和`multimap`容器

---

`map`中所有元素都是`pair`

`pair`中第一个元素为`key`(键值)，起到索引作用，第二个元素为`value`(实值)

所有元素都会根据元素的键值自动排

`map/multimap`属于关联式容器，底层结构是用二叉树实现。

可以根据`key`值快速找到`value`值

`map`不允许容器中有重复`key`值元素

`multimap`允许容器中有重复`key`值元素

### 构造和赋值函数

---

```c++
map<T1, T2> mp;			//map默认构造函数:
map(const map &mp);		//拷贝构造函数

map& operator=(const map &mp);//重载等号操作符
```

### 大小和交换

---

```c++
size();		//返回容器中元素的数目
empty();	//判断容器是否为空
swap(st);	//交换两个集合容器
```

### 插入和删除

---

```c++
insert(elem) ;		//在容器中插入元素。
clear();			//清除所有元素
erase(pos);			//删除pos迭代器所指的元素，返回下一个元素的迭代器。
erase(beg,end) ;	//删除区间[beg,end)的所有元素，返回下一个元素的迭代器。
erase(key);		//删除容器中值为key的元素。
```

插入方式示例：

```c++
map<int,int> m;
//插入
//第一种
m.insert(pair<int,int>(1, 10));
//第二种
m.insert(make_pair(2, 20));
//第三种
m.insert(map<int，int>::value_type(3, 30));
//第四种
m[4] = 40;
```

### 查找和删除

---

```c++
find(key); 		//查找key是否存在,若存在，返回该键的元素的迭代器;若不存在，返回set.end();
count(key);		//统计key的元素个数
```

### 自定义排序

---

同`set`容器，定义一个仿函数或`lambda`和函数通过转换后，作为模板参数列表的第三个参数。

## 函数对象

---

### 基本概念

---

- 重载函数调用操作符的类，其对象常称为函数对象。

- 函数对象使用重载的()时，行为类似函数调用，也叫仿函数。

- 函数对象(仿函数)的本质是一个类，不是一个函数。

### 函数对象的使用

---

函数对象在使用时，可以像普通函数那样调用，可以有参数，可以有返回值，函数对象超出普通函数的概念。

函数对象可以有自己的状态（类成员），这叫做”闭包“，也叫“上下文关联的函数”。

函数对象可以作为参数传递。

## 谓词（predicate）的概念

---

在编程中，谓词（Predicate）是指用于判断某个条件是否为真的函数或表达式。

谓词通常返回一个布尔值（True或False），表示某种断言的真假。

在各种编程语言和环境中，谓词都扮演着重要的角色，用于条件判断、过滤、排序、搜索等各种操作。

谓词的概念在逻辑学中也很常见，用于描述命题的真值。

在编程中，谓词是对逻辑思维的一种抽象，让我们能够将复杂的条件逻辑转换为可执行的代码。

在C++中，谓词可以是以下几种形式：

- 函数谓词：一个函数，接受一个或多个参数，并返回布尔值。

  通过调用该函数并传入相应参数，可以判断特定条件是否为真。

  例如，使用一个函数谓词来判断一个数是否是偶数：

  ```c++
  #include <iostream>
  
  // 函数谓词：判断一个数是否是偶数
  bool is_even(int number) 
  {
      return number % 2 == 0;
  }
  
  int main() 
  {
      // 使用谓词函数判断一个数是否为偶数
      bool result = is_even(10);
      std::cout << std::boolalpha << result << std::endl;  // 输出: true
  
      return 0;
  }
  ```

  在这段代码中，定义了一个函数谓词 `is_even` 来判断一个数是否是偶数。

  然后，在 `main` 函数中使用该谓词来判断整数 `10` 是否为偶数，并将结果打印出来。

  并通过 `std::boolalpha` 操纵符来让输出以布尔值形式显示。

  

  在C++中，谓词通常是用于判断条件是否为真的函数或函数对象（仿函数）。

  谓词的主要特点是它返回`bool`类型的结果，用于条件判断。

  - 返回`bool`类型的仿函数也称为谓词。在C++中，谓词通常是一种函数对象（仿函数），它可以是普通函数、Lambda表达式或重载了函数调用运算符`operator()`的类对象。

  - 如果`operator()`接受一个参数，那么谓词被称为一元谓词。一元谓词用于对单个元素进行条件判断。

  - 如果`operator()`接受两个参数，那么谓词被称为二元谓词。二元谓词用于对两个元素进行条件判断，例如在排序算法中用于定义排序顺序。

    以此类推......

- lambda 表达式谓词：一种匿名函数，通常用于简单的条件判断或过滤操作。

  ==（关于lambda表达式将在以后学习，这里可不做了解，直接跳过即可）==

  例如，使用lambda表达式谓词来筛选出列表中的偶数：

  ```c++
  #include <iostream>
  #include <vector>
  #include <algorithm>
  
  int main() 
  {
      std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
      std::vector<int> even_numbers;
  
      // 使用Lambda表达式谓词来筛选出列表中的偶数
      std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(even_numbers),
                   [](int x) { return x % 2 == 0; });
  
      // 输出筛选结果
      for (int num : even_numbers) 
      {
          std::cout << num << " ";
      }
      std::cout << std::endl;  // 输出: 2 4 6
  
      return 0;
  }
  ```

- 逻辑表达式谓词：通过逻辑运算符（如AND、OR、NOT）将多个条件组合成一个复合条件。

  例如，使用逻辑表达式谓词判断一个数是否在某个范围内：

  ```c++
  bool is_in_range(int number) 
  {
      return (number >= 10) && (number <= 20);
  }
  // 使用谓词函数判断一个数是否在特定范围内
  bool result = is_in_range(15);
  cout << result << endl;  // 输出: 1 (True)
  ```

在STL（标准模板库）中，谓词广泛应用于各种算法函数，如`std::find_if`、`std::sort`、`std::remove_if`等。

它们允许我们根据自定义的条件对容器中的元素进行过滤、排序、搜索等操作，提高了代码的灵活性和可复用性。

谓词的使用在STL和现代C++编程中非常常见。

## STL的内建函数对象

---

### 基本概念

---

STL（Standard Template Library）的内建函数对象（Builtin Function Objects）是一组在C++标准库中提供的用于函数对象操作的预定义类模板。

函数对象是类对象，其行为类似于函数，可以像函数一样被调用。

这些内建函数对象封装了常见的操作，如算术运算、逻辑运算、比较运算等，可以在各种算法和容器操作中使用。

STL内建函数对象的概念主要包括以下几个方面：

- 仿函数（Function Object）：

  STL的内建函数对象通常被称为仿函数，因为它们是函数对象的模拟，具有函数调用运算符`operator()`，可以像函数一样被调用。

  STL提供了一些预定义的仿函数类模板，同时也可以自定义自己的仿函数。

- 预定义的函数对象：

  STL标准库中预定义了一些常用的函数对象类模板，这些函数对象用于执行各种操作，如加法、减法、乘法、除法、逻辑与、逻辑或、比较等。

- 函数对象适用于算法：

  STL中的算法往往接受函数对象作为参数，这样就可以在执行算法时，通过函数对象来定义特定的操作逻辑。

  例如，`std::transform`、`std::sort`、`std::find_if`等算法都接受函数对象，从而允许我们以不同的方式处理元素。

STL内建函数对象的使用使得编写更加通用和灵活的代码变得更加容易。

通过使用预定义的函数对象，我们可以避免重复编写某些常见的操作逻辑，并且提高代码的可读性和可维护性。

此外，STL内建函数对象也为编写泛型代码提供了强大的工具，使得算法和容器操作可以适用于不同类型的数据。

STL内建的一些函数对象的分类：

- 算术仿函数
- 关系仿函
- 逻辑仿函数

等等......

这些仿函数所产生的对象，用法和一般函数完全相同，使用内建函数对象，需要包含头文件`#include<functional>`

### 算数仿函数

---

作用：实现四则运算

其中``negate`是一元运算，其他都是二元运算仿函数

模板原型：

```c++
template<class T> T plus<T>			//加法仿函数
template<class T> T minus<T>		//减法仿函数
template<class T> T multiplies<T>	//乘法仿函数
template<class T> T divides<T>		//除法仿函数
template<class T> T modulus<T>		//取模仿函数
template<class T> T negate<T>		//取反仿函数
```

### 关系仿函数

---

功能描述：实现关系对比

模板原型：

```c++
template<class T> bool equal_to<T>		//等于
template<class T> bool not_equal_to<T>	//不等于
template<class T> bool greater<T>		//大于
template<class T> bool greater_equal<T>	//大于等于
template<class T> bool less<T>			//小于
template<class T> bool less_equal<T>	//小于等于
```

### 逻辑仿函数

---

功能：实现逻辑运算

模板原型：

```c++
template<class T> bool logical_and<T>	//逻辑与
template<class T> bool logical_or<T>	//逻辑或
template<class T> bool logical_not<T>	//逻辑非
```

## STL常用算法

---

### 概述

---

算法主要是由头文件`<algorithm>`、`<functional>`、` <numeric>`组成。

- `<algorithm>`是所有`STL`头文件中最大的一个，范围涉及到比较、交换、查找、遍历操作、复制、修改等等

- `<numeric>`体积很小，只包括几个在序列上面进行简单数学运算的模板函数

- `<functional>`定义了一些模板类,用以声明函数对象。

### 常用遍历算法

---

#### `for_each`遍历

---

功能描述：实现遍历容器

函数原型：

```c++
for_each(iterator beg, iterator end, _func );//遍历算法遍历容器元素
// beg开始迭代器
// end结束迭代器
// _func函数或者函数对象
```

### 常用查找算法

---

#### `find` 查找

---

功能：查找指定元素，找到返回指定元素的迭代器，找不到返回结束迭代器`end()`。

函数原型：

```c++
find(iterator beg, iteratbr end, value) ;//按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
// beg开始迭代器
// end结束迭代器
// value查找的元素
```

注意！查找自定义数据类型，需要重载`operator==`。

#### `find_if`按条件查找

---

功能：按条件查找元素函数。

函数原型：

```c++
find_if(iterator beg, iterator end，_Pred);//按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
// beg 开始迭代器
//end结束迭代器
//_Pred函数或者谓词(返回bool类型的仿函数)
```

#### `adjacent_find`查找相邻重复元素

---

功能：查找相邻重复元素。

函数原型：

```c++
adjacent_find(iterator beg， iterator end ) ;//查找相邻重复元素,返回相邻元素的第一个位置的迭代器
//beg 开始迭代器
// end结束迭代器
```

#### `binary_search`二分查找

---

功能：查找指定元素是否存在。

函数原型：

```c++
bool binary_search(iterator beg, iterator end, value);//查找指定的元素，查到返回true否则false
// beg 开始迭代器
// end结束迭代器
// value查找的元素
```

注意！查找的容器或数组必须已经排好序的（有序序列），在无序序列中不可用。

### 常用统计算法

#### `count`统计个数

---

功能：统计相同元素个数。

函数原型：

```c++
count( iterator beg, iterator end，valle);//统计元素出现次数
// beg开始迭代器
// end结束迭代器
// value统计的元素
```

对于自定义数据类型，需要重载`operator==`。

#### `count_if`按条件统计个数

---

功能：按条件统计元素个数

函数原型：

```c++
count_if(iterator beg, iterator end，_pred ) ;//按条件统计元素出现次数
// beg开始迭代器
// end结束迭代器
// _Pred谓词
```

### 常用排序算法

#### `sort`排序

---

功能：对容器内元素进行排序。

函数原型：

```c++
sort(iterator beg, iterator end, _Pred);//按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置
// beg开始迭代器
// end结束迭代器
// _Pred 谓词
```

谓词参数可不指定。不指定则默认升序排序

#### `random_shuffle`随机排序

---

功能：对容器内元素进行随机排序，打乱原有序列。

函数原型：

```c++
random_shuffle(iterator beg, iterator end ) ;//指定范围内的元素随机调整次序
// beg开始迭代器
// end结束迭代器
```

注意！需要指定随机数种子，才能使每次排序顺序都不一样。

### 常用拷贝和替换算法

---

#### `copy`复制

---

功能：将容器内指定范围的元素拷贝到另—容器中。

函数原型：

```c++
copy(iterator beg， iterator end，iterator dest;//按值查找元素，找到返回指定位置迭代器，找不到返回结束迭代器位置ll beg开始迭代器
// end 结束迭代器
// dest目标起始迭代器
```

注意！目标容器需要提前开辟空间。

#### `transform`搬运容器

---

功能描述：搬运容器到另个容器中

函数原型：

```c++
transform(iterator beg1, iterator end1, iterator beg2, _func);//beg1源容器开始迭代器
//end1源容器结束迭代器
//beg2目标容器开始迭代器
//_func函数或者函数对象
```

注意！目标容器需要提前开辟空间。

#### `replace`替换

---

功能：将容器内指定范围的旧元素修改为新元素。

函数原型：

```c++
replace(iterator beg, iterator end,oldvalue，newvalue) ;//将区间内旧元素替换成新元素
// beg开始迭代器
// end结束迭代器
// oldvalue 旧元素
// newvalue 新元素
```

#### `replace_if`按条件替换

---

功能：将区间内满足条件的元素，替换成指定元素。

函数原型：

```c++
replace_if(iterator beg, iterator end, _pred, newvalue);//按条件替换元素，满足条件的替换成指定元素
// beg开始迭代器
// end结束迭代器
//_pred谓词
// newvalue替换的新元素
```

#### `swap`交换

---

功能：互换两个容器的元素。

函数原型：

```c++
swap(container c1,container c2);//互换两个容器的元素
// c1容器1
// c2容器2
```

### 常用算术生成算法

---

算术生成算法属于小型算法，使用时包含的头文件为`#include <numeric>`。

#### `accumulate`累加

---

功能：计算区间内容器元素累计总和。

函数原型：

```c++
accumulate(iterator beg, iterator end, value) ;//计算容器元素累计总和
// beg 开始迭代器
// end结束迭代器
// value起始累加值
```

#### `fill`填充

---

功能：向容器中填充指定的元素。

函数原型：

```c++
fill(iterator beg, iterator end,value);//向容器中填充元素
// beg开始迭代器
// end结束迭代器
// value填充的值
```

注意！目标容器需要提前开辟空间。

### 常用集合算法

---

#### `set_intersection`求交集

---

功能：求两个容器的交集。

函数原型：

```c++
set_intersection(iterator beg1，iterator end1，iterator beg2，iterator end2，iterator dest);//求两个集合的交集
// beg1容器1开始迭代器
// end1容器1结束迭代器
// beg2容器2开始迭代器
// end2容器2结束迭代器
// dest目标容器开始迭代器
```

注意！

- 目标容器需要提前开辟空间。最特殊情况大容器包含小容器开辟空间取小容器的size即可。
- 返回值为一个迭代器，指向交集的最后一个元素。之后可通过该迭代器重新指定容器大小。
- 两个集合必须是有序序列。

#### `set_unionl`求并集

---

功能：求两个容器的并集。

函数原型：

```c++
set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);//求两个集合的并集
// beg1容器1开始迭代霸
// end1容器1结束迭代器
// beg2容器2开始迭代器
// end2容器2结束迭代器
// dest目标容器开始迭代器
```

注意！

- 目标容器需要提前开辟空间。最特殊情况两个容器没有公共元素，开辟空间大小取两个容器size和即可。
- 返回值为一个迭代器，指向并集的最后一个元素。之后可通过该迭代器重新指定容器大小。
- 两个集合必须是有序序列。

#### `set_difference`求差集

---

功能：求两个容器的差集。

函数原型：

```c++
set_difference(iterator beg1, iterator end1 ,iterator beg2, iterator end2, iterator dest);//求两个集合的差集
// beg1容器1开始迭代器
// end1容器1结束迭代器
// beg2容器2开始迭代器
// end2容器2结束迭代器
// dest目标容器开始迭代器
```

注意！

- 目标容器需要提前开辟空间。最特殊情况，两个容器没有交集，取第一个容器的size即可（也可取两个容器中较大的size作为目标容器开辟空间）
- 返回值为一个迭代器，指向差集的最后一个元素。之后可通过该迭代器重新指定容器大小。
- 两个集合必须是有序序列。

### 其他常用算法

---

#### `merge`合并容器

---

功能：将两个容器元素合并，并存储到另—容器中

函数原型：

```c++
merge(iterator beg1，iterator end1， iterator beg2，iterator end2，iterator dest);//容器元素合并，并存储到另一容器中
// beg1容器1开始迭代器
// end1容器1结束迭代器
// beg2容器2开始迭代器
// end2容器2结束迭代器
// dest目标容器开始迭代器
```

注意！原始的两个容器必须是有序的且必须是一致的顺序（同为升序或降序）。

#### `reverse`

---

功能：将容器内元素进行反转

函数原型：

```c++
reverse(iterator beg，iterator end);//反转指定范围的元素
// beg开始迭代器
// end结束迭代器
```



[C语言关键字volatile_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1z24y1b7LZ?vd_source=03da7de0e80f9ff60fdeca7b512ba3f5)

# C++文件操作

## 概述

---

C++中对文件操作需要包含头文件`#include <fstream>`

文件类型分为两种:

- 文本文件-文件以文本的ASCII码形式存储在计算机中
- 二进制文件-文件以文本的二进制形式存储在计算机中，用户一般不能直接读懂它们



操作文件的三大类:

- `ofstream`：写操作
- `ifstream`：读操作
- `fstream`：读写操作



文件操作的一般步骤：

- 包含头文件`#include <fstream>`

- 根据读写需要创建对应的流对象

- 打开文件时要判断文件是否打开成功

  对于写入数据，如果文件打开失败一般会创建一个新文件，因此可能总是打开成功的。

- 读取或写入

- 关闭文件调用

  当程序终止时，系统会自动关闭刷新所有流，释放所有分配的内存，并关闭所有打开的文件。

  但程序员应该养成一个好习惯，在程序终止前关闭所有打开的文件。

## 文件的打开方式

---

在对一个文件进行读或写之前需要将这个文件打开，因此有了打开方式这一说法。

打开方式：

| 打开方式       | 解释                                 |
| :------------- | :----------------------------------- |
| `ios::in`      | 打开文件用于读取                     |
| `ios::out`     | 打开文件用于写入                     |
| `ios::ate	` | 打开文件后的初始位置：文件尾         |
| `ios::app`     | 追加模式，所有写入都追加到文件末尾。 |
| `ios::trunc`   | 如果文件存在先删除，再创建（覆写）   |
| `ios::binary`  | 二进制方式                           |

注意：

- 文件打开方式可以配合使用，利用`|` 操作符。

  例如：用二进制方式写文件`ios::binary | ios::out`

## 文本文件

---

### 写文件

---

写文件步骤如下：

- 包含头文件：`#include <fstream>`

- 创建流对象：`ofstream ofs`

- 打开文件

  指定文件路径和打开方式：`ofs.open("文件路径", 打开方式式)`

- 写数据：`ofs <<"写入的数据"`

- 关闭文件：`ofs.close()`

示例（写入一个文本文件）：

```c++
#include <iostream>
#include <fstream>

int main()
{
    ofstream ofs;//创建流对象
	ofs.open("test.txt", ios::out);//指定打开文件路径和打开方式
	ofs << "Hello world" << endl;//写入 Hello world 并换行
    ofs << "Hello C++"<< endl;//写入 Hello C++ 并换行
	ofs.close();//关闭文件
}
```

要点总结

- 文件操作必须包含头文件`fstream`

- 读文件可以利用`ofstream` ，或者`fstream`类

- 打开文件时候需要指定操作文件的路径，以及打开方式。

- 利用`<<`以向文件中写数据

- 操作完毕，要关闭文件

### 读文件

---

读文件步骤如下:

- 包含头文件`#include <fstream>`
- 创建流对象`ifstream ifs`
- 打开文件并判断文件是否打开成功`ifs.open("文件路径",打开方式)`
- 读数据：四种方式读取
- 关闭文件`ifs.close()`;

读数据四种方式：

- 第一种，将文件中的内容全部放到字符数组中，注意：数组大小必须>=文件内容的字符数量，否则程序崩溃
- 第二种，将文件中的内容一行一行的写入字符数组中，并根据数组大小，写入相应大小的内容
- 第三种，将文件中的内容写入string字符串中
- 第四种，将文件中的内容一个一个的读取并写入到一个`char`字符中，一个一个的输出，效率低

代码示例：

```C++
//读数据，四种方式
void read1() 
{
	ifstream ifs;//创建流对象
	ifs.open("test.txt", ios::in);//打开文件并
	if(!ifs.is_open())//判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}		
	//读数据
		//第一种，将文件中的内容全部放到字符数组中，注意：数组大小必须>=文件内容的字符数量，否则程序崩溃
	char buf[1024] = { 0 };
	while (ifs >> buf)
	{
		cout << buf ;
	}
	cout << endl;
	ifs.close();
}

void read2() 
{
	ifstream ifs;//创建流对象
	ifs.open("test.txt", ios::in);//打开文件并
	if (!ifs.is_open())//判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}
	//读数据
		//第二种，将文件中的内容一行一行的写入字符数组中，并根据数组大小，写入相应大小的内容
	char buf[1024] = { 0 };
	while (ifs.getline(buf, sizeof(buf)))//ifs下的getline()函数，参数一：数组首地址，参数二：数组大小
	{
		cout << buf << endl;
	}
	ifs.close();
}

void read3() 
{
	ifstream ifs;//创建流对象
	ifs.open("test.txt", ios::in);//打开文件并
	if (!ifs.is_open())//判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}
	//读数据
		//第三种，将文件中的内容写入string字符串中
	string buf;
	while (getline(ifs, buf)) //全局函数getline()，参数一：流，这里是文件读取流，参数二：字符串
	{
		cout << buf << endl;
	}
	ifs.close();
}

void read4() 
{
	ifstream ifs;//创建流对象
	ifs.open("test.txt", ios::in);//打开文件并
	if (!ifs.is_open())//判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}
	//读数据
		//第四种，将文件中的内容一个一个的读取并写入到一个char字符中，一个一个的输出，效率低
	char c;
	while ((c = ifs.get()) != EOF)	//EOF	end of file	
        							//使用ifs下的get()函数，获取单个字符，并赋值给字符c，然后输出，并判断是否读取到文章尾部，到尾部则停止
	{
		cout << c;
	}
	ifs.close();
}
```

## 二进制文件

---

### 写文件

---

以二进制的方式对文件进行读写，操作打开方式要指定为`ios:binary`。

二进制方式写文件主要利用流对象调用成员函数`write`。

对于一些复杂数据类型如：`string`，可以正确写入，但无法正确读取，需要避免使用。

整体步骤与上述文本文件读写步骤一样。

- 函数原型:`ostream& write( const char * buffer ,int len)`
- 参数解释:字符指针`buffer`指向内存中一段存储空间。`len`是读写的字节数

示例（以二进制形式写入自定义数据类型）：

```c++
#include <iostream>
#include<fstream>
#include<string>
using namespace std;

class person
{
public:
	unsigned int age = 0;
	char name[64] = "";
};

void write_2()
{
	ofstream ofs("test2.txt", ios::out | ios::binary);
	person 张三{ 20, "张三" };
	ofs.write((const char*)&张三, sizeof(张三));
	ofs.close();
}

int main()
{
	write_2();
	system("pause");
}

```

### 读文件

---

以二进制的方式对文件进行读写，操作打开方式要指定为`ios:binary`。

二进制方式读文件主要利用流对象调用成员函数`read`。

对于一些复杂数据类型如：`string`，无法正确读取，需要避免使用。

整体步骤与上述文本文件读写步骤一样。

- 函数原型:`istream& read(char *buffer,int len) `
- 参数解释:字符指针`buffer`指向内存中一段存储空间。`len`是读写的字节数

示例（将上一个示例中的自定义数据类型读回来）：

```c++
void read_2()
{
	ifstream ifs("test2.txt", ios::in | ios::binary);
	if (!ifs.is_open())//判断文件是否打开成功
	{
		cout << "文件打开失败" << endl;
		return;
	}
	person p2;
	ifs.read((char*)&p2, sizeof(p2));
	ifs.close();
	cout << p2.name << "  " << p2.age << endl;
}
```

## 补充说明

---

C++新标准（C++11及更高版本）引入了一些新特性和库，其中一些与文件操作相关。

下面是一些在C++新标准中与文件操作相关的内容：

1. `std::filesystem`：C++17引入了 `<filesystem>` 头文件，提供了对文件系统的访问和操作。它包含了一组类和函数，使您能够进行文件和目录的创建、复制、移动、重命名等操作，以及获取文件的属性和路径等信息。

2. `std::ifstream::open()` 重载：

   C++11引入了一个新的 `std::ifstream` 成员函数的重载形式，使您能够更方便地打开文件并指定打开模式。

   例如，您可以使用 `std::ifstream::open(const std::string& filename, std::ios_base::openmode mode)` 重载函数来打开文件并指定读取模式、写入模式、二进制模式等。

3. `std::ofstream::open()` 重载：

   类似地，C++11还引入了 `std::ofstream` 的 `open()` 函数重载形式，使您能够更灵活地打开文件并指定打开模式。

4. 移动语义和右值引用：C++11引入了移动语义和右值引用的概念，使您能够更高效地处理文件流对象。通过使用 `std::move()` 函数，您可以将文件流对象的所有权从一个对象转移到另一个对象，而无需执行深拷贝。

5. 等等......

这些是C++新标准中与文件操作相关的主要内容。它们提供了更强大和灵活的文件操作功能，使您能够更方便地处理文件和文件系统。

请注意，具体实现可能会因编译器和标准库的版本而有所不同，因此请查阅相关的参考文档以了解详细的用法和支持情况。

# 预处理

## `#define`

### 简单的文本替换

语法描述：

`#define name stuff`

有了这条指令以后，每当`name`出现在这条指令后面时，预处理器就会把它替换成`stuff`。

替换文本并不限于数值字面值常量。使用`#define`指令，可以把任何文本替换到程序中。

代码示例：

```
#define reg 			register
#define do_fprever 		for(;;)
#define CASE			break;case;
```

第1个定义只是为关键字`register`创建了一个简短的别名。

这个较短的名字使各个声明更容易通过制表符进行排列。

第2条声明用一个更具描述性的符号来代替一种用于实现无限循环的for语句类型。

最后一个`#define`定义了一种简短记法，以便在`switch`语句中使用。它自动地把一个`break`放在每个`case`之前，这使得`switch`语句看上去更像其他语言的`case`语句。

如果定义中的stuff非常长，它可以分成几行，除了最后一行之外，每行的末尾都要加一个反斜杠，如下面的例子所示：

```c++
#define DEBUG_PRINT		printf( "File %s line %d: " \
								"x=%d, y=%d, z=%d", \
								__FTLE__, __LINE_,  \
								x, y，z )
```

这里利用了相邻的字符串常量被自动连接为一个字符串这个特性。当你调试一个存在许多涉及一组变量的不同计算过程的程序时，这种类型的声明非常有用。

你可以很容易地插入一条调试语句打印出它们的当前值。

示例：

```c++
x *= 2;
y += x;
z = x * y;
DEBUG_PRINT;
```

==注意！：==

这条语句在DEBUG_PRINT后面加了一个分号，所以你不应该在宏定义的尾部加上分号。

如果你这样做了，结果就会产生两条语句：一条`printf`语句后面再加一条空语句。

有些场合只允许出现一条语句，如果放入两条语句就会出现问题，例如：

```c++
if(//...
){//...
}
//...
DEBUG_PRINT;
else
{//...
}
```

所以，不要滥用这种技巧。如果相同的代码需要出现在程序的几个地方，通常更好的方法是把它实现为一个函数。后续将详细讨论`#define`宏和函数之间的优劣。

### 宏函数

`#define`机制包括了一个规定，允许把参数替换到文本中，这种实现通常称为宏或宏函数。

下面是宏函数的声明方式：

`#define　name(parameter-list)　 stuff`

其中，`parameter-list`（参数列表）是一个由逗号分隔的符号列表，它们可能出现在`stuff`中。

参数列表的左括号必须与`name`紧邻。如果两者之间有任何空白存在，参数列表就会被解释为`stuff`的一部分。

*==以下内容宏函数全部简称为宏。==*

当宏被调用时，名字后面是一个由逗号分隔的值的列表，每个值都与宏定义中的一个参数相对应，整个列表用一对括号包围。

当参数出现在程序中时，与每个参数对应的实际值都将被替换到`stuff`中。

---

这里有一个宏，它接受一个参数：`#define SQUARE(x)　　x * x`

如果在上述声明之后，你把`SQUARE( 5 )`置于程序中，预处理器就会用下面这个表达式替换上面的表达式：`5 * 5`

==注意！：==

这个宏存在一个问题。

观察下面的代码段：

```c++
a = 5;
printf("%d\n", SQUARE( a + 1 ));
```

你可能觉得这段代码将打印36这个值。事实上，它将打印11。

参数`x`被文本`a + 1`替换，所以这条语句实际上变成了：

````
printf("%d\n", a + 1 * a + 1);
````

可知：由替换产生的表达式并没有按照预想的次序进行求值。

在宏定义中加上两个括号，这个问题便很轻松地解决了：

```c++
#define SQUARE(x)　　(x) * (x)
```

在前面那个例子里，预处理器现在将用下面这条语句执行替换，从而产生预期的结果：

```
printf("%d\n", (a + 1) * (a + 1));
```

---

这里有另外一个宏定义：

```c++
#define　DOUBLE(x)　　(x) + (x)
```

定义中使用了括号，用于避免前面出现的问题。

但是，使用这个宏，可能会出现另外一个不同的错误。下面这段代码将打印出什么值？

```c++
a = 5;
printf("%d\n", 10 * DOUBLE( a ) );
```

看上去，它好像将打印100，但事实上它打印的是55。

再一次，通过观察宏替换产生的文本，我们能够发现问题所在：

```c++
printf("%d\n", 10 * (a) + (a));
```

乘法运算在宏所定义的加法运算之前执行。

这个错误很容易修正：在定义宏时，你只要在整个表达式两边加上一对括号就可以了：

```c++
#define　DOUBLE(x)　　((x) + (x))
```

所有用于对数值表达式进行求值的宏定义都应该用这种方式加上括号，避免在使用宏时，由于参数中的操作符或邻近的操作符之间不可预料的相互作用。

下面是一对有趣的宏：

```c++
#define　repeat　　do
#define　until(x)　　while(!(x))
```

这两个宏创建了一种“新”的循环，其工作过程类似于其他语言中的
`repeat/until`循环。它按照下面这样的方式使用：

```c++
repeat {
	statements
}until( i >= 10);
```

预处理器将用下面的代码进行替换：

```c++
do {
	statements
} while( !(i >= 10));
```

表达式`i>=10`两边的括号用于确保在`!`操作符执行之前先完成这个表达式的求值。



==注意！：==

创建一套`#define`宏，用一种看上去很像其他语言的方式编写C程序是完全可能的。

在绝大多数情况下，你应该避免这种诱惑，因为这样编写出来的程序使其他C程序员很难理解。

他们必须时常查阅这些宏的定义以便弄清实际的代码是什么意思。

即使每个和这个项目生命期各个阶段相关的人都熟悉那种被模仿的语言，这个技巧仍然可能引起混淆，因为准确地模仿其他语言的各个方面是极为困难的。

---

当预处理器搜索`#define`定义的符号时，字符串常量的内容并不进行检查。你如果想把宏参数插入到字符串常量中，可以使用两种技巧：

- 第1个技巧邻近字符串自动连接的特性使我们很容易把一个字符串分成几段，每段实际上都是一个宏参数。这里有一个这种技巧的例子：

```c++
#define PRINT(FORMAT ,VALUE)		\
		printf ( "The value is " FORMAT "n" , VALUE)
		PRINT("%d" ,x +3 ) ;
```

这种技巧只有当字符串常量作为宏参数给出时才能使用。

- 第2个技巧使用预处理器把一个宏参数转换为一个字符串。#argument这种结构
  被预处理器翻译为“argument”。这种翻译可以让你像下面这样编写代码：

  ```c++
  #define PRINT (FORMAT，VALUE)					\
  		printf ( "The value of "#VALUE			\
  		"is " FORMAT " \n", VALUE )	
  		PRINT("%d",x + 3 );
  ```

  它将产生下面的输出：

  ```
  The value of x +3 is 25
  ```

---

`##`结构则执行一种不同的任务：它把位于它两边的符号连接成一个符号。

作为用途之一，它允许宏定义从分离的文本片段创建标识符。

下面这个例子使用这种连接把一个值添加到几个变量之一：

```c++
#define ADD_To_SUM(sum_number, value ) \
		sum##sum_number += value
		ADD_TO_SUM(5,25) ;
```

最后一条语句把值25加到变量sum5。

注意这种连接必须产生一个合法的标识符。否则，其结果就是未定义的。

### 宏的优势缺陷

在程序中扩展`#define`定义符号和宏时，需要涉及几个步骤。

- 在调用宏时，首先对参数进行检查，看看是否包含了任何由`#define`定义的符号。如果是，它们首先被替换。
- 替换文本随后被插入到程序中原来文本的位置。对于宏，参数名被它们的值所替代。
- 最后，再次对结果文本进行扫描，看看它是否包含了任何由`#define`定义的符号。如果是，就重复上述处理过程。

这样，宏参数和`#define`定义可以包含其他`#define`定义的符号。但是，宏不可以出现递归。

---

宏非常频繁地用于执行简单的计算，比如在两个表达式中寻找其中较大（或较小）的一个：

```c++
#define MAX( a, b )　　( (a) > (b) ? (a) : (b) )
```

为什么不用函数来完成这个任务呢？

有两个原因：

- 首先，用于调用和从函数返回的代码很可能比实际执行这个小型计算工作的代码更大，所以使用宏比使用函数在程序的规模和速度方面都更胜一筹。

  但是，更为重要的是，函数的参数必须声明为一种特定的类型，所以它只能在类型合适的表达式上使用。

- 反之，上面这个宏可以用于整型、长整型、单浮点型、双浮点数以及其他任何可以用>操作符比较值大小的类型。

  换句话说，宏是与类型无关的。和使用函数相比，使用宏的不利之处在于每次使用宏时，一份宏定义代码的拷贝都将插入到程序中。

  除非宏非常短，否则使用宏可能会大幅度增加程序的长度。

==还有一些任务根本无法用函数实现。==

这个宏的第2个参数是一种类型，它无法作为函数参数进行传递。

```c++
#define MALLOC(n, type) \
　　　　 ( (type *)malloc( (n) * sizeof( type ) ) )
```

下面这个例子中的第1条语句被预处理器转换为第2条语句。

```
pi = MALLOC( 25, int );
pi = ( ( int * )malloc( ( 25 ) * sizeof( int ) ) );
```

同样，请注意宏定义并没有用一个分号结尾。分号出现在调用这个宏的语句中。

---

当宏参数在宏定义中出现的次数超过一次时，如果这个参数具有副作用，那么当你使用这个宏时就可能出现危险，导致不可预料的结果。

副作用就是在表达式求值时出现的永久性效果。例如，这个表达式`x + 1`可以重复执行几百次，它每次获得的结果都是一样的。这个表达式不具有副作
用。

但是`x++`就具有副作用：它增加`x`的值。当这个表达式下一次执行时，它将产生一个不同的结果。

`MAX`宏可以证明具有副作用的参数所引起的问题：

```c++
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main()
{
    x = 5 ;y = 8 ;
	z = MAX(x++,y++ ) ;
	printf ( "x=%d, y=%d，z=%d\n" , x, y, z );
}
```

其结果是：`x=6，y=10，z=9`

关于为什么，只要检查一下用宏替换后产生的代码，这个奇怪的结果就变得一目了然了：

```
z = ((x++) > (y++) ? (x++) : (y++));
```

虽然那个较小的值只增值了一次，但那个较大的值却增值了两次：第1次是在比较时，第2次在执行?符号后面的表达式时出现。

---

下面这个宏：

```c++
#define EVENPARITY(ch)					\
		(( count__one_bits (ch) & 1 ) ?	\
		(ch) | PARITYBIT : (ch))
```

该函数返回它的参数的二进制位模式中1的个数。这个宏的目的是产生一个具有偶校验的字符。

它首先计数字符中位1的个数，如果结果是一个奇数，PARITYBIT值（一个值为1的位）与该字符执行OR操作，否则该字符就保留不变。

但是，当这个宏以下面这种方式使用时：

`ch = EVENPARITY( getchar() );`

读取一个字符并计算它的校验位。但是，它的结果是失败的，因为它实际上读入了两个字符！

---

宏和函数的不同之处：

|              | `#define`宏                                                  | 函数                                                         |
| :----------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 代码长度     | 每次使用时，宏代码都被插入到程序中。除了非常小的宏之外，程序的长度将大幅度增长 | 函数代码只出现于一个地方；每次使用这个函数时，都调用那个地方的同一份代码 |
| 执行速度     | 更快                                                         | 存在函数调用/返回的额外开销                                  |
| 操作符优先级 | 宏参数的求值是在所有周围表达式的上下文环境里，除非它们加上括号，否则邻近操作符的优先级可能会产生不可预料的结果 | 函数参数只在函数调用时求值一次，它的结果值传递给函数。表达式的求值结果更容易预测 |
| 参数求值     | 参数每次用于宏定义时，它们都将重新求值。由于多次求值，具有副作用的参数可能会产生不可预料的结果 | 参数在函数被调用前只求值一次。在函数中多次使用参数并不会导致多种求值过程。参数的副作用并不会造成任何特殊的问题 |
| 参数类型     | 宏与类型无关。只要对参数的操作是合法的，它可以使用于任何参数类型 | 函数的参数是与类型有关的。如果参数的类型不同，就需要使用不同的函数，即使它们执行的任务是相同的 |

### 命名约定

`#define`宏的行为和真正的函数相比存在一些不同的地方，上表对此进行了总结。

由于这些不同之处，所以让程序员知道一个标识符究竟是一个宏还是一个函数是非常重要的。

但是使用宏的语法和使用函数的语法是完全一样的，所以语言本身并不能帮助你区分这两者。

为宏定义（对于绝大多数由`#define`定义的符号也是如此）采纳一种命名约定是很重要的，上面这种混淆就是促使人们这样做的原因之一。

一个常见的约定就是把宏名字全部大写。

在下面这条语句中：

```c++
value = max( a, b );
```

`max`究竟是一个宏还是一个函数并不明显。

你很可能不得不仔细察看源文件以及它所包含的所有头文件来找出它的真实身份。

另一方面，请看下面这条语句：

```c++
value = MAX( a, b );
```

命名约定使`MAX`的身份一清二楚。

如果宏使用可能具有副作用的参数时，这个约定尤为重要，因为它可以提醒程序员在使用宏之前先把参数存储到临时变量中。

## `#undef`

语法描述：

`#undef　name`

用于移除一个已有的宏定义`name`，让后续代码中无法再使用该宏。

示例：

```c++
#include <stdio.h>

// 定义一个宏，用于计算两个数的平方
#define SQUARE(x) ((x) * (x))

int main() 
{
    int number = 5;
    
    // 使用宏计算5的平方
    int result = SQUARE(number);
    printf("5的平方是: %d\n", result);

    // 取消宏定义
    #undef SQUARE

    // 尝试再次使用宏，现在会报错
    result = SQUARE(number); // Uncommenting this line will cause a compilation error

    return 0;
}
```

代码中使用`#undef SQUARE`取消了宏定义，后续代码中将无法再使用`SQUARE`宏，再次尝试使用宏时会导致编译错误。

如果一个现存的名字需要被重新定义，那么它的旧定义首先必须用`#undef`移除。

示例：

```c++
#include <stdio.h>

// 定义一个宏，表示一个最大值MAXNUM为100
#define MAXNUM 100

int main() 
{
    printf("MAXNUM的值是: %d\n", MAXNUM); //打印100

    // 取消宏定义
    #undef MAXNUM

    // 重新定义宏，MAXNUM为1000
    #define MAXNUM 1000

    // 再次打印
     printf("MAXNUM的值是: %d\n", MAXNUM); //打印1000

    return 0;
}

```

## 条件编译

### 选择性编译

在编译一个程序时，如果我们可以选择只对某些语句进行编译或者忽略，常常会显得很方便。

这些语句不应该出现在程序的产品版本中，但是你可能并不想把这些语句从源代码中物理删除，因为如果需要一些维护性修改时，你可能需要重新调试这个程序，还需要这些语句。

条件编译就是用于实现这个目的。使用条件编译，你可以选择代码的一部分是被正常编译还是完全忽略。

用于条件编译的指令包括：`#if`、`#endif`、`#ifdef`、`#ifndef`、`#else`、`#elif`。

下面显示了它最简单的语法形式：

```c++
#if　constant-expression
　　　　 statements
#endif
```

其中，`constant-expression`是一个常量表达式，由预处理器进行求值。

如果它的值是非零值即真值，那么`statements`部分就被正常编译，否则预处理器就“安静地删除“它们，使得`statements`部分在编译时被忽略。

所谓常量表达式，就是说它或者是字面值常量，或者是一个由`#define`定义的符号。

如果变量在执行期之前无法获得它们的值，那么它们如果出现在常量表达式中就是非法的，不同的编译器可能有不同的处理方式：忽略、报错等，因为它们的值在编译时是不可预测的。

例如：

```c++
#if DEBUG
printf ( "x=%d, y=%dn" , x, y ) ;
#endif
```

`DEBUG`的值并没有指定，这实际上是一种未定义行为，不同的编译器可能有不同的处理方式：有的编译器会将未定义的宏视为零（假），有的编译器会发出警告，有的编译器可能会忽略这段代码或者报错。

为了避免这种未定义行为，正确的做法是在代码中明确地定义 `DEBUG` 宏，如果想要编译它，只要使用：

```c++
#define DEBUG 1  
```

如果想要忽略它，只要把这个符号定义为0就可以了。无论哪种情况，这段代码都可以保留在源文件中。

这样，预处理指令 `#if DEBUG` 就能正确地根据 `DEBUG` 宏的定义与否来决定是否编译相关代码。

当使用条件预处理指令 `#if` 时，可以结合 `#elif` 和 `#else` 子句来实现多个条件的判断。

完整的语法如下所示：

```c++
#include <stdio.h>

#define OPTION 2

int main()
{
#if OPTION == 1
    printf("Option 1 is selected.\n");
#elif OPTION == 2
    printf("Option 2 is selected.\n");
#elif OPTION == 3
    printf("Option 3 is selected.\n");
    
//......
    
#else
    printf("Option is not recognized.\n");
#endif
    
    return 0;
}
```

在这个示例中，我们定义了一个宏 `OPTION`，然后使用条件预处理指令 `#if` 和 `#elif` 来判断不同的选项。

根据 `OPTION` 的值，程序将输出不同的信息。

- 如果 `OPTION` 的值为 `1`，那么编译器会选择第一个条件分支 `#if OPTION == 1`，输出 "Option 1 is selected."
- 如果 `OPTION` 的值为 `2`，那么编译器会选择第二个条件分支 `#elif OPTION == 2`，输出 "Option 2 is selected."
- 如果 `OPTION` 的值既不是 `1` 也不是 `2`，编译器会选择最后的 `#else` 分支，输出 "Option is not recognized."

在实际的项目中，通过调整宏的定义，可以灵活地根据不同的条件编译不同的代码，这在实现跨平台、调试开关等方面非常有用。

### 检查是否定义

当使用条件编译时，我们可以通过`#ifdef`和`#ifndef`来检查符号是否已经被定义。

下面是一个简单的例子：

假设我们有一个程序，其中使用了一个预定义的符号`DEBUG`来控制是否打印调试信息。

如果`DEBUG`已经被定义，则打印调试信息；如果没有定义，则不打印调试信息。

```c
#include <stdio.h>

#ifdef DEBUG // 如果定义了DEBUG符号时，打印调试信息
#define DEBUG_PRINT(x) std::cout<<x;

#else //没有定义就空实现一段代码
#define DEBUG_PRINT(x) do {} while (0)
#endif

int main()
{
    int num = 42;

    // 输出调试信息
    DEBUG_PRINT(("Debug: The value of num is %d\n", num));

    // 其他代码...

    return 0;
}
```

在这个例子中，我们使用了`#ifdef DEBUG`和`#ifndef DEBUG`来检查`DEBUG`符号是否已经被定义。

- `#ifdef DEBUG` 表示：检查是否已经定义了`DEBUG`符号。

  如果已经定义，就会编译`#ifdef`后面的代码块，这里我们定义了一个宏`DEBUG_PRINT(x)`，它会调用`cout`来打印调试信息。

- `#ifndef DEBUG` 表示：检查是否没有定义`DEBUG`符号。

  如果没有定义，就会编译`#ifndef`后面的代码块，这里我们定义了一个空的`DEBUG_PRINT(x)`宏，这样在程序中调用`DEBUG_PRINT`时就不会有任何输出，达到不打印调试信息的目的。

在编译程序时，可以通过在编译命令中加入`-DDEBUG`选项来定义`DEBUG`符号，或者不加该选项则表示没有定义`DEBUG`符号。

这样，程序在不同的编译情况下会根据`DEBUG`符号的定义与否，选择性地打印或不打印调试信息。

### 防止头文件重复包含

可以使用预处理指令来防止头文件重复包含。

头文件重复包含可能导致编译错误或其他问题，因此需要使用预处理指令来确保头文件只被包含一次。

常用的预处理指令有两种：`#ifndef`和`#pragma once`。这里只将使用条件编译的方式。



在每个头文件的开头，我们可以使用`#ifndef`、`#define`和`#endif`组合来防止重复包含。

这样的组合通常被称为“头文件保护”或“宏保护”。

代码示例：

```c
#ifndef MY_HEADER_H  // 检查是否没有定义过MY_HEADER_H
#define MY_HEADER_H  // 如果没有定义，则定义MY_HEADER_H

// 头文件的内容写在这里

#endif  // 结束宏保护
```

当编译器第一次遇到该头文件时，`MY_HEADER_H`还没有被定义，所以`#ifndef`条件为真，然后执行`#define MY_HEADER_H`，将`MY_HEADER_H`定义为一个标识符。

当其他地方再次包含这个头文件时，由于`MY_HEADER_H`已经被定义了，所以`#ifndef`条件为假，头文件的内容就会被跳过，从而避免了重复包含。

### 嵌套指令

当进行条件编译时，的确可以嵌套使用多个条件，这样可以根据多个条件来选择性地编译代码块。

我们使用一个更简单的示例来说明嵌套条件编译的概念：

假设有一个宏 `DEBUG_MODE`，用于控制是否打印调试信息。

还有一个宏 `TEST_MODE`，用于控制是否编译测试相关的代码。

下面是一个简单的示例代码：

```c
#include <stdio.h>

#define DEBUG_MODE
#define TEST_MODE

int main() 
{
    #ifdef DEBUG_MODE
        printf("已启用调试模式。\n");
    #endif

    #ifdef TEST_MODE
        printf("已启用测试模式。\n");
    #endif

    #ifdef DEBUG_MODE
        #ifdef TEST_MODE
            printf("已同时启用调试模式和测试模式。\n");
        #else
            printf("已启用调试模式，但未启用测试模式。\n");
        #endif
    #else
        #ifdef TEST_MODE
            printf("已启用测试模式，但未启用调试模式。\n");
        #else
            printf("未启用调试模式和测试模式。\n");
        #endif
    #endif

    return 0;
}
```

在这个示例中，我们使用了嵌套的条件编译来处理四种情况：

1. 如果只有 `DEBUG_MODE` 被定义，输出：已启用调试模式。
2. 如果只有 `TEST_MODE` 被定义，输出：已同时启用调试模式和测试模式。
3. 如果两者都被定义，输出：已启用调试模式，但未启用测试模式。
4. 如果两者都没有被定义，输出：已启用测试模式，但未启用调试模式。

### 其他注意事项

- `#if defined A`和` #ifdef A`是等价的。
- `#if !defined A`和`#ifndef A`是等价的。

- 每一个条件编译都应以`#endif`结尾。

## `#error`

`#error`指令允许你生成错误信息。编译程序时，只要遇到`#error` 就会生成一个编译错误提示消息，并停止编译。

语法：
`#error　text of error message`

代码示例：

```c++
int main()
{
#if defined A

	cout << "define 了 A" << endl;
#elif defined B
	cout << "define 了 B" << endl;
#elif defined C
	cout << "define 了 C " << endl;
#else
	#error No defined A B C
#endif
    
}
```

这段代码编译无法通过。

在程序运行时，一旦遇到断言不成立，程序即会报错终止，以方便程序调试。`#error`与`#if`搭配使用可以认为是一个用于调试宏的编译期断言。

## `#include`

我们使用`#include`指令来包含头文件，以便在代码中引用其中的函数声明、宏或其他定义。

C/C++语言标准允许编译器自行决定如何处理两种形式的`#include`：一种是本地形式，另一种是函数库形式。

1. 本地形式的`#include`：

   这是指我们在代码中使用相对或绝对路径来引用自己或项目中的头文件。

   例如：`#include "my_header.h"`，其中`my_header.h`就是本地头文件。

2. 函数库形式的`#include`：

   这是指我们引用标准库或第三方库提供的头文件。

   例如：`#include <stdio.h>`，其中`stdio.h`就是函数库头文件。

编译器在处理这两种`#include`时有一个策略：

- 首先，编译器会对本地头文件采用一种特殊的处理方式。它会首先在源文件所在的当前目录中查找要包含的本地头文件。如果能找到，就直接使用这个本地头文件。
- 如果在当前目录中没有找到本地头文件，编译器则会按照函数库头文件的处理方式来处理它们。这就意味着编译器会在标准位置（通常是系统指定的一些标准目录）去查找本地头文件。

---

当我们在代码中使用`#include "my_header.h"`这样的本地头文件引用时，编译器会按照一种特殊的方式来处理它。

举个例子：

假设我们有一个项目，其中有两个文件，一个是`main.c`，另一个是`my_header.h`。

`main.c`文件包含了一些代码，而`my_header.h`文件定义了一些函数和常量。

现在，我们在`main.c`中使用了`#include "my_header.h"`这样的语句来引用`my_header.h`这个本地头文件。

- 如果`main.c`和`my_header.h`都在同一个文件夹内，编译器会首先在这个文件夹中查找`my_header.h`，找到了就直接使用它的内容。

- 如果`my_header.h`在另一个文件夹中，比如在`include`文件夹内，而`main.c`在项目的根目录中，编译器会先在当前根目录中查找`my_header.h`，如果找不到，再去`include`文件夹中找，找到了就使用。

这样的处理方式让我们能够方便地组织项目中的本地头文件，如果在当前目录能找到，就直接使用，找不到再按照标准规则去查找，确保了头文件的引用可以在不同的项目结构中都能正常工作。

这种处理方式的好处是，编译器优先考虑了本地头文件的查找，这样在项目中我们可以方便地使用自定义的头文件。

如果本地头文件不存在，编译器会像处理函数库头文件一样，按照预定的规则去查找它们。

## `#`（空指令）

无效指令（空指令）就是一个`#`符号开头，但后面不跟任何内容的一行。这类指令只是被预处理器简单地删除。

下面例子中的无效指令通过把`#include`与周围的代码分隔开来，凸显它的存在，当然我们也可以通过插入空行取得相同的效果：

```c++
#
#include <stdio.h>
#
```

## `#pragma`

`#pragma` 指令通常用于向编译器发出一些特定的指令或控制命令，以便改变编译器的行为或进行一些特定的操作。

==它并不是C/C++语言标准的一部分，而是由各个编译器厂商提供的扩展功能。==

因此，==不同的编译器可能支持不同的 `#pragma` 指令，并且在不同的编译器中可能会有不同的效果。==

下面是一些常见的 `#pragma` 预处理指令和它们的用途：

- `#pragma once`: 这是一个用于防止头文件重复包含的指令，和使用 `#ifndef` 和 `#define` 进行头文件保护的效果是一样的。

- `#pragma pack`: 这个指令用于设置结构体的字节对齐方式。

  可以通过 `#pragma pack(n)` 将结构体的对齐方式设置为 `n` 字节。在不同的编译器中，可能会有其他指令用于控制结构体的对齐方式。

- `#pragma message`: 这个指令用于在编译过程中输出一条用户定义的消息。例如，用于调试或显示一些编译信息。

  例如：

  ```c++
  #pragma message("Compiling my program...")
  ```

- `#pragma warning`: 这个指令用于控制编译器警告的输出。

  可以通过 `#pragma warning(disable: <warning_code>)` 来禁用特定的警告，或者通过 `#pragma warning(error: <warning_code>)` 将警告转换为错误，中断编译。

  例如：

  ```c++
  #pragma warning(disable: 1234) // 禁用警告编号为1234的警告
  #pragma warning(error: 5678)  // 将警告编号为5678的警告转换为错误
  ```

  示例：

  在MSVC微软旗下的一款编译器中，认为`scanf`函数是不安全的，编译时会报错，编译无法通过，错误代码为：C4996。

  但是可以使用`#pragma warning(disable: 4996)`来禁用这个错误提示，使得编译顺利通过。

  ```c++
  #pragma warning(disable: 4996) // 禁用警告编号为4996的警告
  #include <iostream>
  using namespace std;
  int main()
  {
  	int a;
      
  	scanf("%d", &a);
      
  	cout << a << endl;
      
  	system("pause");
  }
  ```

==需要注意：#pragma` 不是C/C++的标准指令，它的行为和效果可能在不同的编译器中有所不同。==

为了保证代码的可移植性，建议尽量避免过度依赖特定的 `#pragma` 指令。

对于MSVC，详细参阅：[Pragma 指令与 __pragma 和 _Pragma 关键字 | Microsoft Learn](https://learn.microsoft.com/zh-cn/cpp/preprocessor/pragma-directives-and-the-pragma-keyword?view=msvc-170)

## 预定义符号

### 概述

预定义的预处理符号或指令是在编译过程中由编译器自动定义的一些宏或符号。

这些预处理符号可以在代码中使用，用于编写可移植和条件化的代码。

以下是一些常见的预定义的预处理符号或指令：

- `__LINE__`: 这个预处理符号表示当前代码所在的行号，可以在代码中使用，通常用于调试信息输出和错误定位。

- `__FILE__`: 这个预处理符号表示当前代码所在的文件名（包括路径），可以在代码中使用，通常用于调试信息输出。

- `__DATE__`: 这个预处理符号表示代码被编译的日期，以字符串形式表示（通常是"月 日 年"的格式），可以在代码中使用。

- `__TIME__`: 这个预处理符号表示代码被编译的时间，以字符串形式表示（通常是"时:分:秒"的格式），可以在代码中使用。

- `__cplusplus`: 这个预处理符号在C++编译器中定义，用于判断当前代码是否是C++环境。如果代码在C++环境中编译，`__cplusplus` 会被定义为一个非零值，否则未定义。

- `_WIN32`、`_WIN64`: 这些预处理符号通常在Windows平台的编译器中定义，用于判断代码是否在Windows环境中编译。

  `_WIN32` 在32位Windows系统上定义，而 `_WIN64` 在64位Windows系统上定义。

- `__GNUC__`: 这个预处理符号在GNU编译器（例如GCC）中定义，用于判断代码是否在GCC环境中编译。

这些预定义的预处理符号或指令可以帮助程序员获取一些关于编译环境和代码位置的信息，并且在编写可移植和条件化代码时非常有用。

需要注意的是，这些预定义符号的名称通常以双下划线开头和结尾，以避免和用户定义的宏冲突。

### 使用示例

- `__LINE__` 和 `__FILE__` 的使用示例：

  ```c++
  #include <stdio.h>
  
  int main() 
  {
      printf("当前代码位于文件 %s 的第 %d 行。\n", __FILE__, __LINE__);
  
      return 0;
  }
  ```

  运行上述代码，输出可能类似于：

  ```
  当前代码位于文件 main.c 的第 5 行。
  ```

- `__DATE__` 和 `__TIME__` 的使用示例：

  ```c++
  #include <stdio.h>
  
  int main() 
  {
      printf("代码编译日期：%s\n", __DATE__);
      printf("代码编译时间：%s\n", __TIME__);
  
      return 0;
  }
  ```

  运行上述代码，输出可能类似于：

  ```
  代码编译日期：Jul 28 2023
  代码编译时间：18:30:00
  ```

- `__cplusplus` 的使用示例：

  ```c++
  #include <iostream>
  
  int main() 
  {
  #ifdef __cplusplus
      std::cout << "这是C++环境下的代码。" << std::endl;
  #else
      std::cout << "这是C环境下的代码。" << std::endl;
  #endif
  
      return 0;
  }
  ```

  运行上述代码，如果编译器是C++编译器，则输出：

  ```
  这是C++环境下的代码。
  ```

  如果编译器是C编译器，则输出：

  ```
  这是C环境下的代码。
  ```

- `_WIN32` 和 `_WIN64` 的使用示例：

  ```c++
  #include <stdio.h>
  int main() 
  {
  #ifdef _WIN32
      printf("这是在Windows 32位环境下编译的代码。\n");
  #elif defined(_WIN64)
      printf("这是在Windows 64位环境下编译的代码。\n");
  #else
      printf("这不是在Windows环境下编译的代码。\n");
  #endif
  
      return 0;
  }
  ```

  运行上述代码，输出根据编译环境的不同可能有所不同。例如，在Windows 64位系统下编译运行：

  ```
  这是在Windows 64位环境下编译的代码。
  ```

  

==请注意，输出可能因编译环境不同而有所变化。这些预定义的预处理符号在不同的编译器和平台上可能会有不同的定义和行为。==



## `#line`

`#line` 指令是预处理器中的一个特殊指令，用于改变源代码中的行号和文件名信息。

它的主要作用是帮助程序员在预处理阶段中调整行号和文件名，从而在编译错误或调试时提供更准确的信息。

`#line` 指令的语法如下：

```c
#line constant "filename"
```

其中，`constant` 是一个整数常量，表示将当前行号修改为指定的值，`"filename"` 是一个字符串，表示将当前文件名修改为指定的文件名。

通过使用 `#line` 指令，程序员可以在宏展开或其他情况下，手动调整行号和文件名，以便更好地定位问题和调试代码。

`#line`指令与作用域是无关的。

以下是一个简单的代码示例：

```c
#include <stdio.h>

int main()
{
	{
		printf("当前文件：%s，当前行号：%d\n", __FILE__, __LINE__);

#line 100 "my_code.c"
		printf("当前文件：%s，当前行号：%d\n", __FILE__, __LINE__);

		printf("当前文件：%s，当前行号：%d\n", __FILE__, __LINE__);
	}
	printf("当前文件：%s，当前行号：%d\n", __FILE__, __LINE__);

	system("pause");
}
```

输出结果可能类似于：

```
当前文件：main.c，当前行号：6
当前文件：my_code.c，当前行号：100
当前文件：my_code.c，当前行号：102
当前文件：my_code.c，当前行号：104
```









