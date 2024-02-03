# property属性可以将方法当成属性使用

class Person:
    def __init__(self, age: int):
        self.__age = age

    @property
    def age(self):
        return self.__age

    @age.setter
    def age(self, new_age: int):
        if new_age > 200 or new_age < 0:
            print("年龄错误")
        else:
            self.__age = new_age


p = Person(100)
print(p.age)

p.age = 20
print(p.age)

p.age = 250
print(p.age)


class Person2:
    def __init__(self, age: int):
        self.__age = age

    def get_age(self):
        return self.__age

    def set_age(self, new_age: int):
        self.__age = new_age

    # age就是property属性
    # 参数1：获取property属性的方法
    # 参数2：设置property属性的方法
    age = property(get_age, set_age)


p = Person2(100)
print(p.age)

p.age = 9999
print(p.age)
