class Myclass:
    pass

def main():
    li1 = list()
    li2 = []
    li3 = [1, 2, 3]
    print(type(li1))
    print(type(li2))
    print(type(li3))
    li4 = [1, 3.14, "choi", Myclass()]
    print(type(li4))
    print(li4)

if __name__ == "__main__":
    main()
