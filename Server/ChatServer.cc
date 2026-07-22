#include "ChatServer.h"
#include <muduo/base/Logging.h>
#include <boost/bind/bind.hpp>  //只能给C++用
#include "../protocal/protocal.h"
#include "../protocal/pack.h"
#include "../protocal/unpack.h"
ChatServer::ChatServer(muduo::net::EventLoop* loop,
                       const muduo::net::InetAddress& listenAddr)
    :_loop(loop),
    _server(loop,listenAddr,"ChatServer")
{
    _server.setConnectionCallback(
        std::bind(&ChatServer::onConnection, this,
                  std::placeholders::_1));
    _server.setMessageCallback(
        std::bind(&ChatServer::onMessage, this,
                  std::placeholders::_1,
                  std::placeholders::_2,
                  std::placeholders::_3));
    registerHandlers();
}
void ChatServer::start()
{
    _server.start();
}
void ChatServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
    LOG_INFO << "ChatServer(onConnection) - " << conn->peerAddress().toIpPort()
             << " -> " << conn-> localAddress().toIpPort() 
             << " is "
             << (conn->connected() ? "UP" : "DOWN");
    if(conn->connected())
    {
        _conns.insert(conn);
    }
    else
    {
        _conns.erase(conn);
    }
}
void ChatServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf,
                           muduo::Timestamp time)
{
    MyProtoMsg *pMsg = _decode.decode(buf);
    if(pMsg == nullptr)
    {
        return;//继续等待,后面会再次触发
    }
    uint16_t type = pMsg->head.server;
    _router.dispatch(type,conn,*pMsg,this);
    delete pMsg;
}

void handleEcho(const muduo::net::TcpConnectionPtr& conn,
                const MyProtoMsg& msg,
                void* ctx)
{
    MyProtoEncode encoder;
    uint32_t len = 0;
    uint8_t* data = encoder.encode(
        const_cast<MyProtoMsg*>(&msg),len);
    conn->send(data,len);
    delete[] data;
}
void ChatServer::registerHandlers()
{
    _router.on(1,handleEcho);
} 
