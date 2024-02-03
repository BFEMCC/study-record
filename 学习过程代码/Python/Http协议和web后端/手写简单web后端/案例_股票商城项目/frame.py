from ....数据库操作.pymysql_mysql import OperationMySql
import json

func_list = {}  # 函数列表


# 路由装饰器
def route(path: str):
    def func_out(func):
        func_list[path] = func

        def func_in():
            func()

        return func_in

    return func_out


def readFile(path: str):
    # 读取资源文件
    with open(path, "rb") as f:
        return f.read()


# 从数据库获取数据
def getSqlData(SQL: str):
    # 使用数据库数据
    operator = OperationMySql(host='localhost',
                              port=3306,
                              user='root',
                              password='123456',
                              database='stock_db')
    operator.doSql(SQL)
    stock_data = operator.getaLL()  # (元组类型数据)
    operator.close()
    return stock_data


@route("/index.html")
def index():
    temp = """
                <tr>
                    <td>%s</td>
                    <td>%s</td>
                    <td>%s</td>
                    <td>%s</td>
                    <td>%s</td>
                    <td>%s</td>
                    <td>%s</td>
                    <td>%s</td>
                    <td>
                        <input type="button" value="添加" id="toAdd" name="toAdd" systemidvule="000007">
                    </td>
                </tr>
            """
    html = ""
    for i in getSqlData("select * from info"):  # (元组类型数据)
        html += temp % (i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7])

    return readFile("./template/index.html").replace("{%content%}".encode("utf8"), html.encode("utf8"))


@route("/center.html")
def center():
    return readFile("./template/center.html")


# 返回股票数据
@route("/center_data.html")
def center_data():  # Ajax数据采用json格式
    # [{"key": value},{"key": value},{"key": value},......] 字典装元组才能转json
    # 字符串要用双引号,value值如果也是字符串也必须用双引号引起来
    stock_data = getSqlData("""select 
                    info.code, info.short, info.chg, info.turnover, info.price, info.highs, focus.note_info
                    from info inner join focus on info.id=focus.id;""")
    center_data_list = [{"code": x[0],
                         "short": x[1],
                         "chg": x[2],
                         "turnover": x[3],
                         "price": str(x[4]),
                         "highs": str(x[5]),
                         "note_info": x[6],
                         } for x in stock_data]

    return json.dumps(center_data_list).encode("utf8")


@route("/404NOT FUOND.html")
def notFound():
    return readFile("template/404NOT FUOND.html")


# 接口函数,处理动态资源请求
def application(path: str):
    func = func_list[path]
    return func()
