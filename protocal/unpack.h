#pragma once
#ifndef UNPACK_H
#define UNPACK_H
#include "protocal.h"
#include "pack.h"
#include <muduo/net/Buffer.h>

class MyProtoDecode
{
public:
    MyProtoMsg* decode(muduo::net::Buffer* buf);
};
#endif
