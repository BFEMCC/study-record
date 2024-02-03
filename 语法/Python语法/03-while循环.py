# 输出1到100的数字
i = 1
while i <= 100:
    print(i)
    i += 1

# 输出1到100的和
i = 1
sum = 0
while i <= 100:
    sum += i
    i += 1
print(sum)

# 输出乘法表
i = 1
while i <= 9:
    j = 1
    while j <= i:
        print(f"{j}*{i}={i*j}\t", end='')
        j += 1
    i += 1
    print()
