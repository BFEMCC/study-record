print("圆的面积是：" "50.24")  # 正确，都是字符串，可以不用加逗号
print("圆的面积是：" + "50.24")  # 正确，字符串之间也可以用加号连接
print("圆的面积是：", "50.24")  # 正确，字符串之间也可以用逗号

message = "你好"
message2 = "世界"
# print(message message2)  # 错误
print(message, message2)
print(message + message2)  # 但是两个字符串变量之间必须用加号或者逗号

# print("圆的面积是：" 100)  # 错误，一个是字符串类型，一个是整数类型，类型不一样，必须要用逗号分隔，运行会报错
print("圆的面积是：", 100)  # 正确

message = "圆的面积是：%s" % 50.24
print(message)  # 正确，将50.24格式化成字符串，替换到%s的位置

message = "圆的半径是：%s，面积是：%s" % (7, 50.24)
print(message)  # 正确，将多个数字类型的变量格式化成字符串，按顺序替换原先%s的位置，使用括号括住，用逗号分隔

message = "圆的半径是：%s，面积是：%s" % ("7", 50.24)
print(message)  # 正确，将字符串形式的7和小数形式的50.24格式化成字符串，按顺序替换原先%s的位置，使用括号括住，用逗号分隔

message = "圆的半径是：%s，面积是：%s" % ("7", 3 + 7j)
print(message)  # 正确，支持整数，小数，字符串，虚数，等（

# message = "圆的半径是：%d，面积是：%s" % ("7", 100)
# print(message)  # 错误，不能将字符串形式的7格式化成整数形式的7

message = "圆的半径是：%6d" % 7
print(message)  # 将7格式化成宽度位6，宽度不足用空格填充

message = "圆的半径是：%6d" % 1234567
print(message)  # 当被格式化数的宽度大于设置的宽度，忽略，格式化不生效

message = "圆的半径是：%6d" % 1.83
print(message)  # 格式化成整数宽度位6位，，小数位直接舍弃，宽度不足补空格

message = "圆的半径是：%6.3f" % 1.8346
print(message)  # 格式化成6位宽度，保留3位小数，小数部分自动四舍五入，宽度不足补空格，小数点同样算一个宽度

message = "圆的半径是：%.3f" % 1.8346
print(message)  # 保留3位小数，自动四舍五入，宽度无限制

message = "圆的半径是：%.10f" % 1.8346
print(message)  # 保留10位小数，自动四舍五入，宽度无限制，位数不足自动补0

# 综合使用
baba = 5.6789
message = "圆的半径是：%.10f，半径是：%4d，其他：%9.10f" % (1.8346, 6.790, baba)
print(message + "   ?????", 12345)  # 保留10位小数，自动四舍五入，宽度无限制，位数不足自动补0

# 快速格式化
name = "xxxx"
age = 20
height = 180.75
print(f"我是：{name}，年龄：{age}，身高：{height}")  # 快速格式化不能进行精度控制，只能原样输出

# 输入
name = input("请输入你的名字：")  # input可以自带提示文字
print("你的名字是：", name)

age = input("请输入你的年龄：")  # input的返回值是字符串类型
print(type(age))
print("你的名字是：", int(age))  # 可以用对应函数转换成需要的类型
