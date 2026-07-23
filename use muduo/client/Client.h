#pragma once
#include <muduo/net/TcpClient.h>
#include <muduo/net/EventLoop.h>
#include "../server/Router.h"
#include "../protocal/pack.h"
#include "../protocal/unpack.h"
#include <json/json.h>
class MyProtoMsg;
class ChatClient
{
public:
    ChatClient(muduo::net::EventLoop* loop,
               const muduo::net::InetAddress& ServerAddr);
    void send(uint16_t type, const Json::Value& body);
    void start();
private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buf,
                   muduo::Timestamp time);
    void registerHandlers();
    muduo::net::TcpClient _client;
    muduo::net::EventLoop* _loop;
    Router _router;
    MyProtoEncode _encode;
    MyProtoDecode _decode;
    muduo::net::TcpConnectionPtr _conn;

};
    



