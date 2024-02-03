def func():
    return 1, 2, True, "hello"  # 返回多个返回值，用逗号分隔，支持多个返回值


a, b, c, d = func()  # 用多个变量接收返回值，用逗号分隔
print(a)
print(b)
print(c)
print(d)
