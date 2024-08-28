def main():
    dict_a = {}
    dict_b = dict()
    dict_c = {"a": 100, "b": 200, "c": 40, "d":400}
    print(type(dict_a))
    print(type(dict_b))
    print(type(dict_c))
    print(dict_c)

    # 추가
    dict_c["e"] = 300
    print(dict_c)

    # 제거
    del dict_c["e"]
    print(dict_c)
    re = dict_c.pop("d")
    print(dict_c)
    print(re)

    for key in dict_c:
        print(f"key: {key}, value: {dict_c[key]}")

    for key, value in dict_c.items():
        print(f"key: {key}, value: {value}")

if __name__ == "__main__":
    main()
