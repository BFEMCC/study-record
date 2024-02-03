import socket

# 创建tcp socket
# socket.AF_INET  指定IPv4
# socket.SOCK_STREAM  指定TCP协议
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 设置进程退出时端口立即释放(端口复用选项)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)

# 绑定
# 参数：一个两个元素的元组，本别是服务端IP和端口
server_socket.bind(("127.0.0.1", 12345))

# 设置监听
# 参数：同时最大监听个数（排队处理的最大等待数量）
server_socket.listen(128)

# 等待连接
# 阻塞等待
# 返回值：一个有两个元素的元组，元素1：客户端socket，元素2：客户端的地址信息（一个元组，元素1：客户端IP，元素2：客户端端口号）
client_socket, IP_port = server_socket.accept()  # 元组拆包语法，接收返回值


# 向客户端发送数据
# 发送的数据必须是二进制bit数据，需要转码
# 字符串转换成二进制：encode("字符编码")
# 二进制转换成二进制：decode("字符编码")
# 返回的是发送的字节数
send_size = client_socket.send("hello".encode("utf8"))
print("发送字节数：", send_size)

# 接收数据
# 参数：接收大小
# 接收到的也是二进制bit数据，需要进行解码
# 如果编码不一致会抛出异常，根据异常进行不同编码的解码
# recv会阻塞等待数据到来
while True:
    date = client_socket.recv(1024)

    # 接收数据为0字节表示断开连接
    if len(date) == 0:
        print("断开连接")
        break

    try:
        print("utf8:", date.decode("utf8"))
    except:
        print("gbk:", date.decode("gbk"))

# 关闭套接字
client_socket.close()
server_socket.close()


