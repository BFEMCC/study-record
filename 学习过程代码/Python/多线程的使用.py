# Python 版本：3.11
import threading

# 全局变量
global_variable = 0

# 全局互斥锁
mutex = threading.Lock()


def update_global_variable1():
    global global_variable  # 声明全局变量

    mutex.acquire()  # 上锁

    for _ in range(10000000):
        global_variable += 1

    mutex.release()  # 解锁
    print("自增完毕")


def update_global_variable2():
    global global_variable  # 声明全局变量

    mutex.acquire()  # 上锁

    for _ in range(10000000):
        global_variable += 1

    mutex.release()  # 解锁
    print("自增完毕")


if __name__ == "__main__":
    # 创建两个线程
    thread1 = threading.Thread(target=update_global_variable1)
    thread2 = threading.Thread(target=update_global_variable2)

    # 启动线程
    thread1.start()
    thread2.start()

    # 打印最终的全局变量值
    print("全局变量值：", global_variable)
