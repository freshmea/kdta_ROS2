def main():
    str = "Hello, world!"
    print(str.upper())
    print(str.lower())
    print(str)
    str = str.upper()
    print(str)
    
    # strip
    input_a = """
           안녕하세요
문자열의 안녕 함수를 알아봅니다, 안녕
"""
    print(input_a)
    print(input_a.strip())
    
    # find, rfind
    print(input_a.find("안녕"))
    print(input_a.rfind("안녕"))
    
    # split, join
    print(input_a.split())
    split_input_a = input_a.split()
    print("-*".join(split_input_a))

if __name__ == "__main__":
    main()
