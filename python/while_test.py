
def main():
    i = int()
    while i < 10:
        i += 1
        print(f"{i} 번째 실행 중 ...")
        
    li = [1,2,3,4,5,6,7,2,4,3,2]
    while 2 in li:
        print("2 지우는 중")
        li.remove(2)
    print(li)

    string = "this is a python class in a Daejeon city"
    while "a" in string:
        print(string.find("a"))
        string = string.replace("a", "A", 1)
    print(string)

if __name__ == "__main__":
    main()
