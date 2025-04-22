# 伪造一个java.class文件
with open('test.class','wb')as f:
    f.write(b'\xca\xfe\xba\xbe'+ b'\x61'*100)

# 伪造一个ws-dos文件
with open('test.ws-dos','wb')as f:
    f.write(b'WZ')

