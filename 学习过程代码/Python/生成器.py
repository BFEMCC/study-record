# 生成器可以节省大量的内存控件
# 本质 --> 可以记录函数的执行状态


a = [x for x in range(100)]  # 列表推导式
print(a)

# 生成器推导式
a = (x for x in range(100))
print(a)
print(next(a))
print(next(a))
print(next(a))
print(next(a))  # 用一个生成一次


def func():
    for i in range(5):
        print("star")
        yield i  # 如果函数中有 yield 那么这个函数成为一个生成器
        print("end")


a = func()  # a是一个生成器

# next可以执行生成器
# next会将yield后的数值返回（和return相似）
# next超出范围会抛出异常
ret = next(a)
print(ret)

ret = next(a)
print(ret)

# 可以使用循环
for i in func():
    print(i)
