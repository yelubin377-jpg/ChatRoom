#pragma once
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <set>
#include "Router.h"
#include "../protocal/unpack.h"
class MyProtoMsg;
class ChatServer
{
public:
    ChatServer(muduo::net::EventLoop* loop,
               const muduo::net::InetAddress& listenAddr);
    void start();
private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buf,
                   muduo::Timestamp time);
    void registerHandlers();
    muduo::net::EventLoop* _loop;
    muduo::net::TcpServer _server;
    Router _router;
    MyProtoDecode _decode;
    std::set<muduo::net::TcpConnectionPtr> _conns;
};