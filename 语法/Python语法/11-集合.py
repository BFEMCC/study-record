"""
列表、元组、字符串都是支持重复元素的，当不需要重复元素或需要去重时，就不方便了，且是有序的
而集合，不支持重复元素，且内部是无序的
集合定义使用大括号{}
"""
my_set = {1, 2, 3, 1, 2, 3, "hello", "world"}
set_empty1 = {}  # 这样创建空集合是错误的，这是一个空字典 # error
set_empty2 = set()  # 空集合
print(my_set)  # 集合是无序的，集合不允许重复元素

# 集合不支持下标索引访问，所以集合不是序列
# 集合和列表一样，允许修改

# 添加元素 add
my_set.add("你好")
my_set.add("hello")
my_set.add(123456)
print(my_set)

# 移除元素 remove
my_set.remove("hello")
print(my_set)

# 随机取出一个元素，并移除
print(my_set.pop())
print(my_set)  # 取出后原来的集合中就不存在这个元素了

# 清空集合
my_set.clear()
print(my_set)  # 清空了后只有set(),表示空集合

# 取集合1对于集合2的差集,得到一个新集合,原来的两个集合不变
set1 = {1, 2, 3}
set2 = {1, 5, 6}
set_new = set1.difference(set2)  # 集合1有的，而集合2没有的
print(set_new)

# 删去集合1中的两个集合的交集，集合1改变，集合2不发生改变
set1 = {1, 2, 3}
set2 = {1, 5, 6}
set1.difference_update(set2)  # 删去集合1和集合2中都有的元素
print(set1)
print(set2)

# 取并集，得到新集合，原集合不变，不包含重复元素
set1 = {1, 2, 3}
set2 = {1, 5, 6}
set_new = set1.union(set2)
print(set_new)

# 获取集合元素数量
set1 = {1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}
print(len(set1))

# 循环遍历，不能用while循环
for i in set1:
    print(i)
