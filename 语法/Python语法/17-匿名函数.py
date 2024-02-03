"""
def 可以定义带有名称的函数
lambda 可以定义匿名函数

有名称的函数可以重复使用
匿名函数只能使用1次

语法：
lambda 传入参数: 函数体（一行代码）
lambda 函数不用写return，默认直接返回
"""


def printf(func):
    print(func(1, 3))


def add(x, y):
    return x + y


printf(lambda x, y: x + y)




