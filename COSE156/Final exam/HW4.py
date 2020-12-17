import random

ox = 'o'
i = 1
while ox == 'o':
    x = random.randint(1, 9)
    y = random.randint(1, 9)

    hap = [0, x, y]
    hap[0] = sum(hap)
    print('문제 : %d ' % i)
    i += 1
    answer = int(input('%d + %d = ' % (x, y)))

    if answer == hap[0]:
        print('정답입니다. \n')
    else:
        print('아쉽군요 \n')
        ox = 'x'
