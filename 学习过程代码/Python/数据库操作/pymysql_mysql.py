import pymysql


class OperationMySql:
    def __init__(self, host: str, port: int, user: str, password: str, database: str):
        self.db = pymysql.connect(host=host,  # 地址
                                  port=port,  # 端口
                                  user=user,  # 用户名
                                  password=password,  # 密码
                                  database=database,  # 数据库名
                                  charset='utf8'  # 字符集
                                  )  # 连接数据库
        self.cursor = self.db.cursor()  # 获取游标对象

    # 关闭数据库
    def close(self):
        self.cursor.close()
        self.db.close()

    # 执行SQL语句
    def doSql(self, SQL: str):
        return self.cursor.execute(SQL)  # 使用execute()方法执行SQL语句,返回执行过程中影响的行数

    # 获取单条数据
    def getLine(self):
        return self.cursor.fetchone()  # 使用fetchone()获取单条数据

    # 获取所有数据
    def getaLL(self):
        return self.cursor.fetchall()  # 取出结果的所有数据

    # 手动提交修改
    def commit(self):
        self.db.commit()


if __name__ == '__main__':
    operator = OperationMySql(host='localhost',
                              port=3306,
                              user='root',
                              password='123456',
                              database='学生信息')
    operator.doSql("select version()")  # 查询版本
    print("数据库版本：", operator.getLine()[0])

    operator.close()
