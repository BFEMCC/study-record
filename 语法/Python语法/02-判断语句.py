import random

num = random.randint(1, 10)
guess_num = int(input("请输入猜测的数字："))
if guess_num == num:
    print("第一次就猜中了")
else:
    if guess_num > num:
        print("猜大了")
    elif guess_num < num:
        print("猜小了")
    guess_num = int(input("请再次输入猜测的数字："))
    if guess_num == num:
        print("猜中了")
    else:
        if guess_num > num:
            print("猜大了")
        elif guess_num < num:
            print("猜小了")
        guess_num = int(input("请再次输入猜测的数字："))
        if guess_num == num:
            print("猜中了")
        else:
            if guess_num > num:
                print("猜大了")
            elif guess_num < num:
                print("猜小了")
            print("猜了三次，都没猜对，程序结束")
