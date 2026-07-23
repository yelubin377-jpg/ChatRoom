#pragma once
#ifndef MY_PROTOCAL_H
#define MY_PROTOCAL_H
#include <stdint.h>
#include <json/json.h>
const uint32_t MY_PROTO_HEAD_SIZE = 6;
const uint32_t MY_PROTO_MAX_SIZE = 10*1024*1024;
class MyProtoHead //协议头部
{
public:
    uint16_t server; //协议复用的服务号
    uint32_t len; //协议长度（协议头部+变长json协议体 = 总长度） 
};

class MyProtoMsg // 协议消息体
{
public:
    MyProtoHead head; //协议头
    Json::Value body; //协议体
};

#endif
