with open("./test.txt", "w", encoding="UTF-8") as file:  # w模式，覆写
    file.write("hello world.txt\n")  # 写入缓冲区
    file.flush()  # 刷新内容，将缓冲区内容写入文件

file = open("./test.txt", "a", encoding="UTF-8")  # a模式，追加写入
file.write("hello world.txt\n")  # 写入缓冲区
file.write("hello world.txt\n")  # 写入缓冲区
file.write("hello world.txt\n")  # 写入缓冲区
file.write("hello world.txt\n")  # 写入缓冲区
file.write("hello world.txt\n")  # 写入缓冲区

file.flush()  # close会自带flush
