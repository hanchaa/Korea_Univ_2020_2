import random
num = random.randint(0, 50)
answer = -1
while answer != num:
    answer = int(input('제가 생각하는 수를 입력 하시오 > '))
    if answer == num:
        print('대단하군요. 정답 입니다.')
    elif answer > num:
        print('너무 큽니다. 더 줄이세요 ㅎㅎ')
    elif answer < num:
        print('더 크게 생각해보세요')
