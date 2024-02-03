# Python 版本：3.11
import multiprocessing
import time


def func():
    for i in range(10000):
        time.sleep(0.1)
        print(i)


if __name__ == "__main__":
    # 创建两个进程
    process1 = multiprocessing.Process(target=func, daemon=True)
    process2 = multiprocessing.Process(target=func)
    process2.daemon = True

    # 启动进程
    process1.start()
    process2.start()
