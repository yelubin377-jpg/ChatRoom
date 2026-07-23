#include "Client.h"
#include "muduo/base/Logging.h"
#include "muduo/net/EventLoop.h"
#include <boost/bind/bind.hpp>
#include "../protocal/protocal.h"
#include "../protocal/pack.h"
#include "../protocal/unpack.h"
ChatClient::ChatClient(muduo::net::EventLoop* loop,
                       const muduo::net::InetAddress& ServerAddr)
        :_loop(loop),
        _client(loop,ServerAddr,"ChatClient")
{
    _client.setConnectionCallback(
        boost::bind(&ChatClient::onConnection,this,
                    std::placeholders::_1)
    );
    _client.setMessageCallback(
        boost::bind(&ChatClient::onMessage,this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3)
    );
    registerHandlers();
}
void ChatClient::start()
{
    _client.connect();
}
void ChatClient::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
    LOG_INFO << "onConnection - (ChatClient)" << conn->peerAddress().toIpPort()
             << " -> " << conn->localAddress().toIpPort()  
             << " is " << (conn->connected() ? "UP" : "DOWN");
    if(conn->connected())
    {
        _conn = conn;
    }
    else
    {
        _conn.reset();
    }
}
void ChatClient::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf,
                           muduo::Timestamp time)
{
    LOG_INFO << "onMessage - (ChatClient)" << conn->peerAddress().toIpPort()
             << " -> " << conn->localAddress().toIpPort()
             << " at " << time.toString();
    MyProtoMsg* pMsg = _decode.decode(buf);
    if(pMsg == nullptr)
    {
        return;
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
void ChatClient::registerHandlers()
{
    _router.on(1,handleEcho);
}       