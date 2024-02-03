import socket

# 创建tcp socket
# socket.AF_INET  指定IPv4
# socket.SOCK_STREAM  指定TCP协议
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 和服务端建立连接
# 参数：一个两个元素的元组，本别是服务端IP和端口
client_socket.connect(("127.0.0.1", 12345))

# 发送数据
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
    data = client_socket.recv(100)

    # 接收数据为0字节表示断开连接
    if len(data) == 0:
        print("断开连接")
        break

    # try:
    #     print("utf8:", data.decode("utf8"))
    # except:
    #     print("gbk:", data.decode("gbk"))
    print(data)


# 关闭套接字
client_socket.close()

