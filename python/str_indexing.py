# c/cpp type var(type var_name, ...)
# {
#      ...
# }

def main():
    str1 = "안녕하세요"
    print(str1)
    print(str1[0])
    print(type(str1))
    print(type(str1[0]))
    print(str1[1])
    print(str1[2])
    print(str1[3])
    print(str1[4])
    
    print(str1[-1])
    print(str1[-2])
    print(str1[-3])
    print(str1[-4])
    print(str1[-5])
    
    # slicing
    str2 = str1 * 3
    print(str2[5:10])
    print(str2[-3:])
    print(str2[5:15:2])
    print(str2[-1::-1])
    
    # len()
    print(len(str2))

if __name__ == "__main__":
    main()
