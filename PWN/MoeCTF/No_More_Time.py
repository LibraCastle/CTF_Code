from pwn import *

context(arch = 'amd64', os = 'linux', log_level = 'debug')

io = remote("192.168.31.103", 54710)

io.sendlineafter(b"=",b"2\n")
io.sendlineafter(b"=",b"0\n")
io.recvuntil(b"PREPARED!\n")

while(True):
    fms = io.recvuntil(b"=",timeout = 6)
    # 格式化表达式
    fms = fms[:-1].decode()     # 去掉最后的=
    fms = fms.replace(" ","")   # 去掉空格
    fms = fms.replace("/","//") # 替换除号
    fms = fms.replace("\n","")   # 去掉换行符

    # 开始计算
    res = eval(fms)
    print(f"表达式：{fms} = {res}")
    io.sendline(str(res))

