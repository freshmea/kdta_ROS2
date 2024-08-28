import datetime


def main():
    present_clock = datetime.datetime.now()
    print(present_clock.hour)
    print(present_clock)
    
    if present_clock.hour < 12:
        print("오전입니다.")
    else:
        print("오후입니다.")

if __name__ == "__main__":
    main()