"""
打开文件
使用open函数可以打开一个已经存在的文件或创建一个新文件
语法：open(name, mode, encoding)"
name：要打开文件的文件名字符串，使用绝对路径或相对路径
mode：设置打开文件的模式(访问模式)：只读、写入、追加、等
encoding：编码格式（推荐使用UTF-8）

mode的常用三种模式：
r 只读，这是默认模式，从头开始
w 覆写，写入模式，原来的内容会被删除，直接覆写新内容，如果文件不存在，直接创建一个新文件
a 追加，如果文件存在则在原文件末尾内容之后追加写入，如果文件不存在，则创建一个新文件
"""
file = open("./06-函数.py", "r", encoding="UTF-8")
print(file.read(10))  # 读取文件，用read方法，参数是指定读取的字节数，空为读取全部内容
print(file.read())  # 多次读取，会在上一次读取的内容的结尾继续读取

# 读取全部行，将每一行存储在一个list列表中，继续接着上一次读取的内容的结尾继续读取
print(file.readlines())  # 空，因为上一次已经读取完了

file2 = open("./07-列表.py", "r", encoding="UTF-8")
print(file2.readlines())  # 空，因为上一次已经读取完了

# 读取一行
file3 = open("./08-元组.py", "r", encoding="UTF-8")
print(file3.readline())

# for循环读取行
file4 = open("./09-字符串.py", "r", encoding="UTF-8")
for line in file4:
    print(f"for循环读取每一行：{line}")


# 文件关闭
file.close()
file2.close()
file3.close()
file4.close()


# with open,自动关闭文件
# 通过在with open的语句块中对文件进行操作，可以在操作完成后自动关闭文件，避免忘记close方法
with open("./09-字符串.py", "r", encoding="UTF-8") as file:
    print(file.readlines())

# with open块运行结束后会自动关闭文件
