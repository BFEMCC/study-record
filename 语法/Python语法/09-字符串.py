# 字符串也是数据容器，每一个元素就是对应的单个字符
# string和char的关系?

s = "hello world.txt"

# 通过下标索引获取单个元素
print(s[0])  # h
print(s[-1])  # d

# 和元组一样，字符串是不可以修改元素的，无法追加、移除

# index方法查找
i = s.index("wor")  # 在字符串s中查找wor子串，返回起始下标
print(i)

# 字符串替换 replace
new_s = s.replace("hello", "你好")  # 将hello替换成你好，返回一个新的字符串，不会修改原来的字符串
print(s)
print(new_s)

# 字符串分割 split
# 按照指定的分隔字符串，将原字符串分割成多个字符串，并存入列表中
# 原字符串不改变，返回一个列表对象
s = "hello world.txt hello Python"
L = s.split(" ")  # 按照空格进行分割，分成四个子串
print(L)

# 字符串规整 去除前后空格 strip
s = "  hello world.txt    "
print(s.strip())  # 返回新字符串："hello world.txt"
print(s)
# 去除指定的字符串
s = "123hello world3112123123123131231323"
print(s.strip("123"))  # 把头和尾只要出现1或2或3的子串全删了，返回一个新的字符串

# 统计某个子串出现的次数
s = "aa basd aa b aa b aa dfasdfsd aa sdfasdf aa"
print(s.count("aa"))  # 统计子串aa出现的次数

# 获取字符串长度
print(len(s))

# 循环遍历输出每一个字符
for i in s:
    print(i, end='')
