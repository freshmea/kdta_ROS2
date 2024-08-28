def main():
#   for(int i=0;i<10;i++){
#        printf("%d", i+1);
#    }
# for(auto i: li){...}
    for i in range(10):
        print(i+1)

    li2 = [123, 3.14, 1.4, 7, "number"]

    for ele in li2:
        print(ele)

    for i, ele in enumerate(li2):
        print(f"index: {i}, element: {ele}")

if __name__ == "__main__":
    main()
