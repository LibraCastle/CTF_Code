# /bin/sh

# 限制 core.dump
ulimit -c 0

# 只提供执行权限
chown -R pwn:pwn /home/pwn
chmod 555 /home/pwn/vuln

# 启动程序服务，同时监听9087端口,fork表示支持多连接
exec socat tcp-listen:9087,fork,reuseaddr exec:"/home/pwn/vuln",stderr


