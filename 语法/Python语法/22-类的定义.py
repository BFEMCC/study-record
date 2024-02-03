class student:
    # 成员变量
    name = None
    age = None
    __height = None  # 私有成员变量就需要用两个下划线作为变量名开头

    """
    所有成员函数的第一个参数都必须是self
    调用传参时，self不会接收参数，但是必须要写，想要访问类内变量，要使用 self.
    （self相当于this？bushi
    """

    def __testfunc(self):  # 私有成员方法也需要用两个下划线作为变量名开头
        print(f"this is private function,test:{self.__height}")

    # 构造方法（构造函数），会自动执行
    def __init__(self, name, age, height):
        self.name = name
        self.age = age
        self.height = height
        """
        如果写了构造方法，那么成员变量可以不写，可省略
        那么构造方法中的语句相当于定义成员变量
        写了就相当于赋值
        """

    # 成员函数
    def printmessage(self):
        print(self.name, self.age, self.height)
        """
        类的构造方法属于类的内置方法，除了构造方法外，类还有许多内置方法
        （类似与重载操作符？bushi
        如：
            字符串方法 __str__
            小于号,大于号比较方法 __lt__
            小于等于，大于等于比较方法 __le__
            等于号比较方法 __eq__
            类还有很多需要重写的方法，这些方法统称为魔术方法
        """

    def __str__(self):
        return f"name:{self.name} age:{self.age} height:{self.height}"

    def __lt__(self, other):
        return self.age < other.age

    def __le__(self, other):
        return self.age <= other.age

    def __eq__(self, other):
        return self.age == other.age


stu1 = student("小明", 18, 170)
stu1.printmessage()
print(stu1)  # 如果没有重写字符串方法，那么会直接打印地址
print(stu1.name)
stu2 = student("小红", 16, 168)
print(stu2 < stu1)
print(stu2 > stu1)
stu3 = student("小芳", 16, 165)
print(stu3 >= stu2)
print(stu3 <= stu2)
print(stu3 == stu2)
print(stu1 == stu2)
