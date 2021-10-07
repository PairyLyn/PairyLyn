import base64
import random

# 加密
#sc = bytes(input("请输入shellcode："),encoding='UTF-8')
#sc = codecs.escape_decode(sc, 'hex-escape')[0]
sc = b'shellcode'
i = 0
while i < 6:
    sc = base64.b64encode(sc)
    i += 1

#print(sc)

with open(".\\1.ico", 'wb') as file:
    file.write(sc)
'''
i = 0
while i < 6:
    sc = base64.b64decode(sc)
    i += 1
print(sc)
'''
