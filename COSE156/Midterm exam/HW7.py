answers = [['python', 'Python', 'PYTHON', '파이썬'], 'Tom', '로딩중']

answer_cnt = 0
while answer_cnt < 3:
    answer_cnt = 0
    print('*****************')
    print(' 방 탈출 퀴즈 게임')
    print('*****************')

    ans = input('1. 좋아하는 수업은? ')
    if ans in answers[0]:
        answer_cnt += 1

    ans = input('2. 빌게이츠 회장이 제일 싫어하는 친구의 이름은? ')
    if ans == answers[1]:
        answer_cnt += 1

    ans = input('3. 세상에서 가장 지겨운 중학교는? ')
    if ans == answers[2]:
        answer_cnt += 1

print("!!! 방탈출을 축하합니다. !!!")
