def main():
    li1 = [1, 2, 3, 4]
    li2 = [li1, 3.14, 1.4, 7, "number"]
    del li1[0]
    print(li1)
    del li2[0]
    print(li2)
    # del li1
    # print(li1)

    re = li2.pop()
    print(li2)
    print(re)
    re = li2.pop(0)
    print(li2)
    print(re)

    li1.remove(3)
    print(li1)

    if 4 in li1:
        print("4 있음")

    if 3 in li1:
        print("3 있음")
    else:
        print("3 없음")


if __name__ == "__main__":
    main()
