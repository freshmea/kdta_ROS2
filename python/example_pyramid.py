
def main():
    li = []
    li.append("*")
    for i in range(1, 10):
        for i2, ele in enumerate(li):
            li[i2] = " " + li[i2] + " "
        li.append("*" * (i*2+1))
    
    for ele in li:
        print(ele)
    

if __name__ == "__main__":
    main()
