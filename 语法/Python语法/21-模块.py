"""
模块就是一个py文件，模块能定义函数、变量、类等，模块里也能包含可执行代码
（头文件?bushi

基本语法：
[from 模块名] import [模块名 | 类 | 变量 | 函数 | *] [as 别名]
中括号中的是可选内容

常用组合形式：
import 模块名
from 模块名 import 类、变量、方法等
from 模块名 import *
import 模块名 as 别名
form 模块名 import 功能名 as 别名
"""

# # 示例：导入自带的time模块，这样导入后，使用模块中的内容语法：模块名.功能名或类名等
# import time
# print("hello")
# time.sleep(3)  # 睡眠3秒
# print("world")

# 单独导入某个功能
# # 单独导入time模块中的sleep函数
# from time import sleep  # 可以是类、函数、变量、模块
# print("hello")
# sleep(3)  # 睡眠3秒，不需要写 time. ，直接使用即可
# print("world")

# # 使用*号导入time模块中的所有功能
# from time import *
# print("hello")
# sleep(3)  # 睡眠3秒，也不需要写 time. ，直接使用即可
# print("world")

# 单独导入time模块中的sleep函数，并给sleep函数重命名为sl
from time import sleep as sl
print("hello")
sl(3)  # 睡眠3秒，也不需要写 time. ，直接使用即可
# sleep(3)  # 原来的名称不可用
print("world")

"""
当导入多个模块时，且模块具有同名功能，当调用这个同名功能时，调用的是后面导入的模块功能
"""