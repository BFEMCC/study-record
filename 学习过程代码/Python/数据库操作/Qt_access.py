from PySide6.QtSql import QSqlDatabase
from PySide6.QtWidgets import QApplication
from PySide6.QtWidgets import QWidget


def connectAccess(path: str):
    # 数据库连接类:QSqlDatabase
    # QSqlDatabase.addDatabase(驱动名)  # 添加数据库驱动

    db = QSqlDatabase.addDatabase("QODBC")  # 驱动名：QODBC,支持access
    DRIVER = '{Microsoft Access Driver (*.mdb, *.accdb)}'
    dsn = 'DRIVER={};FIL={};DBQ={};'.format(DRIVER, "MS Access", path)
    db.setDatabaseName(dsn)
    return db


if __name__ == '__main__':
    app = QApplication()
    w = QWidget()

    DBQ = './myacces.accdb'  # access数据库文件路径
    db = connectAccess(DBQ)

    # 打开数据库文件
    if db.open():
        print("open success")
        db.close()  # 关闭数据库

    else:
        print("false")

    w.show()
    app.exec()
