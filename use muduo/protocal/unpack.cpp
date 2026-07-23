#include "unpack.h"
#include <muduo/net/Buffer.h>
#include <json/json.h>
MyProtoMsg* MyProtoDecode::decode(muduo::net::Buffer* buf)
{
    if(buf->readableBytes() < MY_PROTO_HEAD_SIZE)
        return nullptr;
    uint8_t* headPtr = (uint8_t*)buf->peek();
    uint16_t server = *(uint16_t*)(headPtr);
    uint32_t msgLen = *(uint32_t*)(headPtr + 2);
    if(buf->readableBytes() < msgLen)
        return nullptr;
    std::string bodyStr((char*)buf->peek() + MY_PROTO_HEAD_SIZE,
                        msgLen - MY_PROTO_HEAD_SIZE);
    Json::Reader  reader;
    MyProtoMsg* pMsg = new MyProtoMsg();
    reader.parse(bodyStr,pMsg->body);
    pMsg->head.server = server;
    pMsg->head.len = msgLen;
    
    buf->retrieve(msgLen);
    return pMsg;
}