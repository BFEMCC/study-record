my_list = [1, 2, 3, 4, 5, 6]
my_tuple = (1, 2, 3, 4, 5, 6)
my_str = "abcdefg"
my_set = {1, 2, 3, 4, 5, 6}
my_dict = {"key1": 1, "key2": 2, "key3": 3, "key4": 4, "key5": 5}

# 获取最大元素
print(max(my_list))
print(max(my_tuple))
print(max(my_str))
print(max(my_set))
print(max(my_dict))

# 获取最小元素
print(min(my_list))
print(min(my_tuple))
print(min(my_str))
print(min(my_set))
print(min(my_dict))

# 将给定容器转换成列表
print(type(list(my_list)))  # 将list转换成list
print(type(list(my_tuple)))  # 将tuple转换成list，元组转列表
print(type(list(my_str)))  # 将str转换成list，字符串转列表
print(type(list(my_set)))  # 将set转换成list，集合转列表
print(type(list(my_dict)))  # 将dict转换成list，字典转列表

print(list(my_list))
print(list(my_tuple))
print(list(my_str))
print(list(my_set))
print(list(my_dict))

# 将给定容器转换成字符串
print(type(str(my_list)))  # 将list转换成str，列表转字符串
print(type(str(my_tuple)))  # 将tuple转换成str，元组转列字符串
print(type(str(my_str)))  # 将str转换成str，字符串转字符串
print(type(str(my_set)))  # 将set转换成str，集合转字符串
print(type(str(my_dict)))  # 将dict转换成str，字典转字符串

print(str(my_list))
print(str(my_tuple))
print(str(my_str))
print(str(my_set))
print(str(my_dict))

# 无法转字典

# 通用排序 sorted 不会修改原来容器，返回新的列表对象
my_list = [1, 3, 54, 656, 123, 2, 567, 5, 8, 9, 456, 54, 345, 32, 454, 4, 56, 7, ]
print(sorted(my_list))  # 正向排序
print(sorted(my_list, reverse=True))  # 反向排序
