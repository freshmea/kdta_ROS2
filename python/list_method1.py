def main():
    li1 = [1, 2, 3, 4]
    li2 = [3.14, 1.4, 7, "number"]
    print(li1 + li2)
    print(li1.__add__(li2))
    print(li1 * 3)
    print(len(li2))
    print(li2.__len__())

    print("extend: ")
    print(li1)
    li2.append("kim")
    print(li2)
    li2.insert(4, "Jo")
    print(li2)


if __name__ == "__main__":
    main()
