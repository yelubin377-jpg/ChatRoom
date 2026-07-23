#include "pack.h"
#include "protocal.h"
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <json/json.h>
#include <map>
void MyProtoEncode::headEncode(uint8_t* pData,MyProtoMsg* pMsg) //把server和len写入pData的6字节缓冲区
{
    *(uint16_t*)pData = pMsg->head.server;
    pData += 2;
    *(uint32_t*)pData = pMsg->head.len;
}
uint8_t* MyProtoEncode::encode(MyProtoMsg* pMsg,uint32_t& len)
{
    uint8_t* pData = NULL;
    Json::FastWriter fwriter; // 读取Json::Value数据，转换为可以写入文件的字符串

    //协议Json体序列化
    std::string bodyStr = fwriter.write(pMsg->body);

    //计算消息序列化后的新长度
    len = MY_PROTO_HEAD_SIZE + (uint32_t)bodyStr.size();
    pMsg->head.len = len;
    //申请一块新的空间，用于保存消息
    pData = new uint8_t[len];
    //编码协议头
    headEncode(pData,pMsg); // 函数内部没有通过二级指针修改pData的数据，修改的是临时数据
    //打包协议体
    memcpy(pData + MY_PROTO_HEAD_SIZE,bodyStr.c_str(),bodyStr.size());
    return pData; //返回消息首部地址
}

