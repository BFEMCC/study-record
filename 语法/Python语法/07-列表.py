# 根据数据容器的特点不同，可以划分为5列：列表list、元组tuple、字符串str、集合set、字典dict
# 数据容器可以存储多个变量，方便管理和使用

# 列表

# 列表的初始化
my_list = list()  # 空列表
my_list2 = []  # 空列表

name_list = ["小明", "小刚", "小雨", "小红"]  # 简单的字符串列表

my_list3 = [1, 2, 3.14, "hello", False, name_list]  # 可以存储不同的类型

my_list4 = [my_list, my_list2, my_list3]  # 列表可以嵌套

print(type(my_list4))  # 类型名是  <class 'list'>

# 从左向右下表索引从0开始
print(name_list[2])  # 打印：小雨
# 从右向左下表索引从-1开始，不断减1
print(name_list[-4])  # 打印小明
# 下标越界运行报错

my_list.append("123")  # 尾部添加元素，不限制类型，
my_list.extend(name_list)  # 追加一个列表中的所有元素到尾部（将列表拆开，将各元素分别添加到尾部）
print(my_list[0])  # 打印第一个元素
print(my_list[len(my_list)-1])  # 打印最后一个元素
print(my_list[-1])  # 打印最后一个元素

print(my_list.index("小雨"))  # 打印元素”小雨“的下索引值
print(my_list[my_list.index("小雨")])


# 列表的循环遍历
# 两种方式，for循环和while循环
for i in my_list4:
    index = 0
    while index < len(i):
        print(i[index], " ", end='')
        index += 1
