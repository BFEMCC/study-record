import socket
import threading
import sys


class webServer:

    def __init__(self, port=80):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 创建socket
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)  # 断开连接立即释放端口,方便复用
        self.server_socket.bind(("127.0.0.1", port))  # 绑定地址
        self.server_socket.listen(128)  # 设置监听,最大同时连接数量128
        self.response = "HTTP/1.1 200 OK\r\nserver : localhost\r\n\r\n"  # 正常访问,响应头
        self.error = "HTTP/1.1 404 NOT FOUND\r\nserver : localhost\r\n\r\n"  # 404响应头

    def star(self):
        while True:
            client_socket, client_addr = self.server_socket.accept()  # 接受连接,获取客户端socket,客户端IP+端口

            # 使用多线程,处理对应客户端的请求
            requests_thread = threading.Thread(target=self.handling_requests, args=(client_socket,), daemon=True)
            requests_thread.start()

    def handling_requests(self, client: socket):
        recv_data = client.recv(102400).decode("utf-8")  # 接收数据

        if len(recv_data) == 0:
            print("客户端断开连接")
            return

        # 对请求报文进行切割
        path = recv_data.split(" ")[1]  # 按空格进行分割
        print("请求资源路径：", path)

        # 设置主页面
        if path == "/":
            path = "/index.html"

        try:
            # 读取资源文件
            with open("./static resource"f"{path}", "rb") as f:
                body = f.read()

            client.send(self.response.encode("utf8") + body)  # 发送数据,响应头+响应体
            client.close()

        except FileNotFoundError:
            # 若没有指定文件,返回404
            with open("static resource/404NOT FUOND.html", "rb") as f:
                body = f.read()

            client.send(self.error.encode("utf8") + body)
            client.close()


if __name__ == "__main__":

    if len(sys.argv) > 2:
        print("启动参数错误,正确格式：\n\tpython 文件名 [端口号(可选)]")
        exit(-1)
    try:
        server = webServer(int(sys.argv[1]))
    except ValueError:
        print("启动参数:端口号错误,正确格式：\n\tpython 文件名 [int: 端口号(可选)]")
        exit(-1)
    except IndexError:
        server = webServer()

    server.star()

