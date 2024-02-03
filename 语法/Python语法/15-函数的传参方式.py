# 位置参数
def printf(name, age, height):
    print(name)
    print(age)
    print(height)


# 根据位置一一对应，传入参数
printf("小明", 15, 170)

# 关键字传参
printf(age=15, name="小明", height=180)  # 指定关键字进行传参，可以不随意顺序

# 位置传参和关键字传参可以混用，但位置参数必须在前面
printf("小明", height=160, age=15)  # 关键字传参顺序可随意


# 缺省参数，函数带有默认值，可不传入对应的参数
def add(x, y=1):  # 默认参数必须在组后面
    return x + y


print(add(1))  # y有默认参数，所以第二个参数可以不传入参数
print(add(1, 3))  # 如果传入参数，就会覆盖修改默认参数


# 不定长参数，可变参数（可变参模板？

# 位置传递的不定长参数
def func(*args):  # 当传入多个参数时，所有参数都会被args接收，args默认是一个不可修改的元组类型
    print(args)
    print(type(args))


func(1, 2, 3, 4, "hello", "world", [123, "hello"])


# 关键字传递


def func2(**kwargs):  # 参数按照：key=value的形式传入，按照key和value组成字典
    print(kwargs)
    print(type(kwargs))


func2(name="小明", age=18, height=180)
