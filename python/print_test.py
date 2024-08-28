
def main():
    print("hellow python")
    print(type(1))
    a = int()
    a = 1
    # a = 'hello'
    print(type(a))
    b = int()
    print(type(b))
    print(a, b, sep=":",end="")
    print(end="\t")
    print(a,b)
    # 'a', 'b'..... -> str() type
    # 'abc' -> str() type
    # 'a', "abc", 'abc' 구분 없음.

if __name__ == "__main__":
    main()
