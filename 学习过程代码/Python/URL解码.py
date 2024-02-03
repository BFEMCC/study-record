# s = "%.txt"
# print("utf8: ", s.encode("utf8"))
# print("gbk: ", s.encode("gbk"))
# print("Unicode: ", s.encode("unicode"))
# print("utf16: ", s.encode("utf16"))

from PySide6.QtCore import QByteArray
encodedString = "%E7%A8%8D%E5%90%8E%E5%86%8D%E7%9C%8B"
print(QByteArray.fromPercentEncoding(encodedString.encode("utf8")).data().decode("utf8"))

from PySide6.QtCore import QUrl
encoded_string = "%E7%A8%8D%E5%90%8E%E5%86%8D%E7%9C%8B"
print(QUrl.fromPercentEncoding(encoded_string.encode('utf-8')))

from urllib.parse import unquote
encoded_string = "%E7%A8%8D%E5%90%8E%E5%86%8D%E7%9C%8B"
print(unquote(encoded_string, 'utf-8'))
