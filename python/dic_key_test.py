def main():
    dict_a = {"a": 100, "b": 200, "c": 40, "d":400}
    print(dict_a["a"])
    # print(dict_a["e"])
    
    # 확인하기
    if "e" in dict_a:
        print(dict_a["e"])
    else:
        pass
    
    # get 메소드로 접근하기
    print(dict_a.get("e"))

if __name__ == "__main__":
    main()
