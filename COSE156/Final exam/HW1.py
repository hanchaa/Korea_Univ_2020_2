def cal_sum(para):
    hap = 0
    for i in para:
        hap += int(i)

    return hap


input_list = input("더할 수를 입력하시오 (여러개 입력가능) > ").split()
total = cal_sum(input_list)
print('입력한 수의 합계: ', total)
