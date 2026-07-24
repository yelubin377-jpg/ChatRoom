### socket.h

- ###### noncopyable 防止Fd乱拷贝，拷贝后的Fd在原Fd被关掉后会继续拥有功能，可能会误关文件

- SOMAXCONN listen()第二参数，等待队列最多排多少人 – 拉满

- SOCK——NONBLOCK 非阻塞，没有新链接函数就立刻返回-1,后面程序跑

- SOCK——CLOEXEC  Close On Exec 关掉