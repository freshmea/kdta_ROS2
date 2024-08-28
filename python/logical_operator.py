
def main():
    # (! true) -> false 
    # (! false) - >true
    print(not True) # False
    print(not False) # True

    # true && true -> true
    # false  || false -> false
    print( True and True)
    print( False or False)

    # if (boolean){
    #    
    # }
    if False:
        print("이것은 True 에서만 보이는 문장")
        print("이것은 True 에서만 보이는 문장")
        print("이것은 True 에서만 보이는 문장")
    else:
        print("이것은 False 에서만 보이는 문장")
        print("이것은 False 에서만 보이는 문장")
        print("이것은 False 에서만 보이는 문장")
    
    a = int(input("숫자를 넣으세요."))
    if a < 0:
        print( "a는 음수")
    elif a > 0:
        print( "a는 양수")
    else:
        print( "a 는 0")

if __name__ == "__main__":
    main()