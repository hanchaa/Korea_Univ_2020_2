second = int(input("초 단위 시간을 입력하세요: "))

minute = second // 60
second %= 60

print(minute, "분", second, "초 입니다!")
