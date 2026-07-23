#include "ChatServer.h"
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>
#include <unistd.h>
int main()
{
    LOG_INFO << "pid = " <<getpid();
    muduo::net::EventLoop loop;
    muduo::net::InetAddress addr(2026);
    ChatServer server(&loop, addr);
    server.start();
    loop.loop();
}