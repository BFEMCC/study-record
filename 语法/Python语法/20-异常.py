"""
当代码错误时运行，解释器就会抛出异常
如果不进行处理，那么程序就会停止在异常代码处并退出
如果捕获异常并处理后，程序可以继续运行
"""
# open("./text", "r", encoding="UTF-8")
# print("hello")  # 不会运行

# 基本语法
try:  # 将可能发生异常的代码写在try语句块中
    open("./text", "r", encoding="UTF-8")  # 发生异常，抛出异常，抛出异常后不继续执行后续代码
    print(12345)
except:  # 将如果出现异常后的执行的代码写在except语句块中，一个try语句必须有一个except语句与之对应
    print("error")
print("hello")

# 指定捕获的异常
try:
    print(name)
except NameError as error:  # 指定，只捕获NameError类型的异常，其他类型的异常忽略，并将异常命名为error
    print(error)

# # 指定捕获的异常
# try:
#     1/0
# except NameError as error:  # 抛出的不是NameError异常，不会被捕获
#     print(error)

# 指定多个捕获的异常
try:
    print(name)
    1/0
except (NameError, ZeroDivisionError) as error:  # 将多个异常组成为一个元组，命名为error
    print(error)

# 捕获全部异常
# 不指定异常类型可捕获异常
# 指定捕获异常为Exception可捕获所有异常，Exception是顶级异常，即所有异常类的父类
try:
    print(name)  # 率先抛出异常，后续代码不会运行
    1/0
    open("./text", "r", encoding="UTF-8")

except Exception as error:  # 将多个异常组成为一个元组，命名为error
    print(error)


try:
    1/2

except Exception as error:
    print(error)

else:  # 如果没有抛出异常，执行else里的代码，else是可选的
    print("no error")


try:
    1 / 0

except Exception as error:  # 如果抛出异常就执行这段代码块
    print(error)

else:  # 如果没有抛出异常，执行else里的代码，else是可选的
    print("no error")

finally:  # 无论是否抛出异常都会执行finally里的代码，finally是可选的
    print("hello")
