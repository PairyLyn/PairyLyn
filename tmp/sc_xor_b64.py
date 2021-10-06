import base64
import random

# 加密
#sc = bytes(input("请输入shellcode："),encoding='UTF-8')
#sc = codecs.escape_decode(sc, 'hex-escape')[0]
sc = b'sc'
print("原sc：")
print(sc)
print()

# xor
i = 0
# 定义xor的key值
key = []
#print(sc)
# 将sc的bytes类型转换为bytearray--bytes数组类型
sc = bytearray(sc)
# 取每个字节与key进行异或
while i < len(sc):
    key.append(random.randint(1, 255))
    sc[i] = sc[i] ^ key[i]
    i += 1

sc = bytes(sc)
sc = base64.b64encode(sc)

print(sc)
print(key)

'''
# 解密

# sc = b'en-sc'

sc = base64.b64decode(sc)

sc = bytearray(sc)
i = 0
while i < len(sc):
    sc[i] = sc[i] ^ key[i]
    i += 1
sc = bytes(sc)
#sc = codecs.escape_decode(sc, 'hex-escape')[0]
print("解：")
print(sc)

'''
