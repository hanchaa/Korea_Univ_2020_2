import pytagcloud
import random
from konlpy.tag import Okt
from collections import Counter

file = open('naver_toy3.txt', 'r', encoding='utf-8')
reply_text = file.readlines()
file.close()

ok_twitter = Okt()
nouns = []
tags = []

for sentence in reply_text:
    for noun in ok_twitter.nouns(sentence):
        if noun in ['영화', '때', '내', '편', '이', '것', '나']:
            pass

        else:
            if noun == "앤디":
                noun = "주한"

            nouns.append(noun)

count = Counter(nouns)

for n, c in count.most_common(200):
    tags.append({'color': (random.randint(0, 255),
                           random.randint(0, 255),
                           random.randint(0, 255)),
                 'tag': n,
                 'size': c // 4 + 25})

pytagcloud.create_tag_image(tags, 'wordcloud.png', fontname='Darakbang', size=(1000, 700))
