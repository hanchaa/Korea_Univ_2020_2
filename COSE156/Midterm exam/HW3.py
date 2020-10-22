score_data = [32, 54, 45, 89, 60, 68, 77, 35, 90, 81, 70, 81, 76, 68, 90, 80]

score_sum = 0
cnt = 0

for i in score_data:
    if 80 <= i <= 90:
        cnt += 1
        score_sum += i

print(">> 추출된 개수:", cnt)
print(">> 평균 값: %.2f" % (score_sum / cnt))
