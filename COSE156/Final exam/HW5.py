filename = input("읽을 txt파일을 입력하여 주십시오 >")

try:
    file = open(filename, 'r', encoding='utf-8')
    sentences = file.read()
    words = sentences.split(' ')
    print('%s에 포함된 총 단어 수는 약 %d개 입니다' % (filename, len(words)))
    file.close()

except:
    print(filename, "파일이 없거나 잘못 입력하였습니다. 다시 확인하여 주십시오")
