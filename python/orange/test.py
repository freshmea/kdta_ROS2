class Cookies:
    def __init__(self):
        self.colors = 'red'
    def get_color(self):
        return self.colors

def get_cookies():
    return Cookies()
c1 = Cookies()

temp_function = get_cookies
print(c1.colors)
print(type(c1))
print(type(get_cookies))
print(type(c1.get_color))
print(temp_function())
print(temp_function)
temp_function = c1.get_color
print(temp_function())
print(temp_function)
print(type(1))
print(locals())
print(globals())