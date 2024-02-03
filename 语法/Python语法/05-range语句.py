# range作用：获取一个数字序列（数组？
# 基本作用，个人理解：执行指定次数的for循环，类似for(int i=0; i < 10; i++)这种

# 语法1：range(num)，从0开始到num结束，不包括num
for x in range(10):
    print(x)  # 打印0-9

# 语法2：range(num1,num2)，从num1开始到num2，不包括num2
for x in range(5, 16):
    print(x)  # 打印5-15

# 语法3：range(num1,num2,step)，从num1开始到num2，不包括num2，进步为step，即数字间的间隔为step
for x in range(5, 50, 2):
    print(x)  # 打印5、7、9、11、13.....一直到不超过50的符合规律的数为止

'''
for循环配合range打印九九乘法表
'''
# 外层循环控制行数
for x in range(1, 10):
    # 内层循环控制每一行的数据
    for y in range(1, x + 1):
        print(f"{y}*{x}={y * x}\t", end='')
    print()


