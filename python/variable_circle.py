def main():
    pi = 3.141592
    r = 10
    r += 1
    r *= 2
    r = r * 2

    print("원주율 : ", pi)
    print("반지름 : ", r)
    print("원의 넓이 : ", pi*r**2)
    print("원의 둘레 : ", 2*pi*r)
    
    print("원주율 : {:.2}".format(pi)) # old style
    print(f"원주율 : {pi*3:.5}")

if __name__ == '__main__':
    main()
