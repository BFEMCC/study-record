"""
每一条数据都有一个唯一的key，一个key对应一个value，key值不允许重复
即：键值对
不可以使用下标索引，只能通过key值来获取value
key和value是可以为任何类型，但key不可以是字典
"""

# 字典的定义：{key:value, key:value, ...}
my_dict = {}  # 空字典
my_dict2 = dict()  # 空字典
duct1 = {"小明": "一班", "小芳": "二班", "小刚": "一班"}

# 获取元素
print(duct1["小明"])  # 一班

# 新增元素和修改元素
duct1["小明"] = "二班"  # 如果key值存在，就是修改元素
duct1["小美"] = "三班"  # 如果key值不存在，就是添加新元素
print(duct1)

# 删除元素，并返回value值
value = duct1.pop("小刚")
print(value)
print(duct1)

# 获取全部key,并返回一个dict_keys类，类似list列表容器
key_list = duct1.keys()
print(type(key_list))
print(key_list)

# 遍历字典，通过keys遍历
for k in duct1.keys():
    print(f"{k}:{duct1[k]}")

# 遍历字典，直接for循环，每次循环都是直接得到key
for k in duct1:
    print(f"{k}:{duct1[k]}")

# 字典不支持下标索引，不能用while循环

# 统计元素数量
print(len(duct1))

# 清空元素
duct1.clear()
print(duct1)
