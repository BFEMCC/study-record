# pandas连接access

import pyodbc
import pandas
import sqlalchemy_access
from sqlalchemy import create_engine, Engine  # 创建与数据库连接引擎的函数
from sqlalchemy import MetaData, Table, Column, String, Integer


class accessConnect:
    def __init__(self, file_path: str):
        self.DBQ = file_path  # 数据库文件路径
        self.engine = None

    def __Connection(self):
        # 环境检查
        var = [x for x in pyodbc.drivers() if x.startswith('Microsoft Access Driver')]
        if var != ['Microsoft Access Driver (*.mdb, *.accdb)']:  # ['Microsoft Access Driver (*.mdb, *.accdb)'] 表示没问题
            return
        return pyodbc.connect("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};" + "DBQ={};".format(self.DBQ))

    def Connect(self):
        """
        连接数据库
        :return: 引擎
        """
        self.engine = create_engine("access+pyodbc:///", creator=self.__Connection)  # 创建引擎
        self.engine.connect()  # 连接
        return self.engine


def create_table(engine: Engine, table_name: str, columns):
    """
    创建一个具有指定名称和列的表。
    如果表已存在无操作
    示例: [{'name': '列1', 'type': Integer}, {'name': '列2', 'type': String(255)}]
    :param engine: 引擎
    :param table_name: 要创建的表的名称
    :param columns: 包含列名和数据类型定义的字典列表
    :return: None
    """
    metadata = MetaData()
    # 使用列表推导式创建列对象，并将其传递给 Table 构造函数
    table = Table(table_name, metadata, *[Column(col['name'], col['type']) for col in columns])
    metadata.create_all(engine)  # 创建表


def drop_table(engine, table_name):
    """
    删除指定名称的表，如果表不存在则忽略操作。

    :param engine: 引擎
    :param table_name: 要删除的表的名称
    :return: None
    """
    metadata = MetaData()
    metadata.reflect(bind=engine)

    if table_name in metadata.tables:  # 检查表是否存在
        table = metadata.tables[table_name]
        table.drop(engine)  # 删除表


if __name__ == '__main__':
    engine = accessConnect('./myacces.accdb').Connect()  # 连接数据库

    # 查询
    data = pandas.read_sql("select * from student", engine)  # 读取,参数1：sql语句,参数2:引擎
    print(data)

    # 建表
    create_table(engine=engine, table_name="学生信息", columns=[
        {'name': '学号', 'type': Integer, 'primary_key': True},
        {'name': '姓名', 'type': String(255)},
        {'name': '年龄', 'type': Integer}])

    # 查询
    data = pandas.read_sql("select * from test", engine)  # 读取,参数1：sql语句,参数2:引擎
    print(data)

    # 删表
    drop_table(engine=engine, table_name="学生信息")
