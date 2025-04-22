FROM ubuntu:16.04

ARG http_proxy=http://192.168.31.103:7897
ARG https_proxy=http://192.168.31.103:7897

RUN apt update && apt install -y socat


# # 配置SSH 如果只需要提供pwn环境，可以不配置SSH
# RUN apt-get update && apt-get install -y openssh-server
# RUN sed -ri 's/^#?PermitRootLogin\s+.*/PermitRootLogin yes/' /etc/ssh/sshd_config &&\
#     sed -ri 's/#UseDNS\ no/UseDNS\ no/g' /etc/ssh/sshd_config &&\
#     sed -ri 's/StrictModes yes/StrictModes no/g' /etc/ssh/sshd_config &&\
#     sed -ri 's/UsePAM yes/UsePAM no/g' /etc/ssh/sshd_config 

RUN echo 'PermitAuthentication yes' >> /etc/sshd_config

# 设置root,pwn用户

RUN useradd -m -s /bin/bash pwn && \
    echo "root:123456" | chpasswd && \
    echo "pwn:123456" | chpasswd

RUN usermod -aG sudo root && \ 
    usermod -aG sudo pwn && 
   

# 下载python3,pwndbg,这里为了最小化容器体积，暂时不予下载
# RUN 

# 拷贝文件到容器中
# COPY  .././ret2text.c /home/pwn
COPY  ./vuln  /home/pwn
COPY  ./run.sh  /home/pwn

# 设置文件权限,可以由run.sh配置，这里不重复了
# RUN  chown -R pwn:pwn /home/pwn && chmod +x /home/pwn/run.sh
RUN chmod +x /home/pwn/run.sh

# 设置工作端口，由run.sh配置，这里不重复了
# EXPOSE 9087

# 以PWN用户身份运行
USER pwn 
WORKDIR /home/pwn

# 设置默认命令
CMD ["./run.sh"]